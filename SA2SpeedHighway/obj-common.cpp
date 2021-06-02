#include "pch.h"

static Trampoline* goalringt;
static Trampoline* itembox_t;
static Trampoline* airbox_t;
static Trampoline* CountPerfectRings_t;

static const double RingDist = 336200.0;

static void __cdecl CountPerfectRings_r()
{
	VoidFunc(original, CountPerfectRings_t->Target());
	original();

	if (CurrentObjectList && SETEntries)
	{
		for (int i = 0; i < *(int*)SETFile; ++i)
		{
			int flag = CurrentObjectList->List[SETEntries[i].ID & 0x7FFF].ObjectFlags & 0x70;

			if (flag == 0x40)
			{
				PerfectRings += min(static_cast<int>(SETEntries[i].Scale.x) + 1, 8);
			}
		}
	}
}

#pragma region RingGroup

/*
* Param1: Number of rings (float)
* Param2: Distance between rings (float)
* Param3: 0 is line, 1 is circle (float)
*/

static char GetSetDataFlag(ObjectMaster* obj)
{
	return obj->SETData != nullptr ? obj->SETData->field_1 : 0;
}

static void SetSetDataFlag(ObjectMaster* obj, char value)
{
	if (obj->SETData)
	{
		obj->SETData->field_1 = value;
	}
}

static void CalcRingPosCircle(EntityData1* data, NJS_VECTOR* pos, int index)
{
	NJS_VECTOR offset = {
		njCos((static_cast<float>(index) * 360.0f) / data->Scale.x * 65536.0f * 0.00278f) * data->Scale.y,
		0.0f,
		njSin((static_cast<float>(index) * 360.0f) / data->Scale.x * 65536.0f * 0.00278f) * data->Scale.y
	};

	njPushUnitMatrix();
	njTranslateV(0, &data->Position);
	njRotateZ_(_nj_current_matrix_ptr_, data->Rotation.z);
	njRotateX_(_nj_current_matrix_ptr_, data->Rotation.x);
	njRotateY_(_nj_current_matrix_ptr_, data->Rotation.y);
	njCalcPoint(&offset, pos, _nj_current_matrix_ptr_);
	njAddVector(pos, &data->Position);
	njPopMatrixEx();
}

static void CalcRingPosLine(EntityData1* data, NJS_VECTOR* pos, int index)
{
	NJS_VECTOR offset = { 0.0f, 0.0f, index % 2 ? ceilf(static_cast<float>(index) * 0.5f) * data->Scale.y : static_cast<float>(index) * data->Scale.y * -0.5f };
	
	njPushUnitMatrix();
	njTranslateV(0, &data->Position);
	njRotateZ_(_nj_current_matrix_ptr_, data->Rotation.z);
	njRotateX_(_nj_current_matrix_ptr_, data->Rotation.x);
	njRotateY_(_nj_current_matrix_ptr_, data->Rotation.y);
	njCalcPoint(&offset, pos, _nj_current_matrix_ptr_);
	njAddVector(pos, &data->Position);
	njPopMatrixEx();
}

static void __cdecl RingGroup_Main(ObjectMaster* obj)
{
	if (!ClipSetObject(obj))
	{
		// No rings anymore, delete permanently
		if (obj->Child == nullptr)
		{
			UpdateSetDateAndDelete(obj);
			return;
		}

		// Loop through the rings, if the ring is in the delete action, set it as obtained
		const ObjectMaster* orig = obj->Child;
		ObjectMaster* i = obj->Child;

		while (i)
		{
			if (i->Data1.Entity->Action == 3)
			{
				SetSetDataFlag(obj, GetSetDataFlag(obj) | (1 << i->Data1.Entity->Index));
			}

			i = i->PrevObject;
			
			if (i && i == orig)
			{
				break;
			}
		}
	}
}

void __cdecl RingGroup(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	const int ring_count = min(static_cast<int>(data->Scale.x) + 1, 8);
	const bool is_circle = static_cast<bool>(data->Scale.z);

	for (int i = 0; i < ring_count; ++i)
	{
		if (!(GetSetDataFlag(obj) & (1 << i)))
		{
			NJS_VECTOR pos;

			if (is_circle == true)
			{
				CalcRingPosCircle(data, &pos, i);
			}
			else
			{
				CalcRingPosLine(data, &pos, i);
			}

			ObjectMaster* child = LoadChildObject(LoadObj_Data1, RingMain, obj);

			if (child)
			{
				child->Data1.Entity->Index = 1 << i;
				child->Data1.Entity->Position.x = pos.x;
				child->Data1.Entity->Position.y = pos.y;
				child->Data1.Entity->Position.z = pos.z;
				child->Data1.Entity->Rotation.x = 0;
				child->Data1.Entity->Rotation.y = 0;
				child->Data1.Entity->Rotation.z = 0;
			}
		}
	}

	obj->MainSub = RingGroup_Main;
	obj->DeleteSub = DeleteChildObjects;
}

#pragma endregion

static void __cdecl GoalRing_r(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	if (data->Action == 0)
	{
		if (isSADXLevel())
		{
			data->Position.y += 31.0f;
		}
	}

	ObjectFunc(origin, goalringt->Target());
	origin(obj);
}

// SADX uses different itembox ID than SA2
static unsigned int FixItemBoxID(unsigned int id)
{
	switch (id)
	{
	case 1:
		return 10;
	case 2:
		return 1;
	case 6:
		return 2;
	case 7:
		return 6;
	}

	return id;
}

static void __cdecl ItemBox_r(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	if (data->Action == 0)
	{
		if (isSADXLevel())
		{
			if ((unsigned __int64)data->Scale.x >= 9)
			{
				data->Scale.x = 0.0;
			}

			data->Scale.x = FixItemBoxID((unsigned int)data->Scale.x);
		}
	}

	ObjectFunc(origin, itembox_t->Target());
	origin(obj);
}

static void __cdecl AirBox_r(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	if (data->Action == 0)
	{
		if (isSADXLevel())
		{
			if ((unsigned __int64)data->Scale.x >= 9)
			{
				data->Scale.x = 0.0;
			}

			data->Scale.x = FixItemBoxID((unsigned int)data->Scale.x);
		}
	}

	ObjectFunc(origin, airbox_t->Target());
	origin(obj);
}

void Objects_Init()
{
	//SADX Fixes
	goalringt = new Trampoline((int)GoalRing_Main, (int)GoalRing_Main + 0x6, GoalRing_r);
	itembox_t = new Trampoline((int)ItemBox_Main, (int)ItemBox_Main + 0x5, ItemBox_r);
	airbox_t = new Trampoline((int)ItemBoxAir_Main, (int)ItemBoxAir_Main + 0x5, AirBox_r);
	CountPerfectRings_t = new Trampoline((int)CountPerfectRings, (int)CountPerfectRings + 0x6, CountPerfectRings_r);

	// Fix Rings draw distance with GroupRing
	WriteData((const double**)0x6C0FA9, &RingDist);
}