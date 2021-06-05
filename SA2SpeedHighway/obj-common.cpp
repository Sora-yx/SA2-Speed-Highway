#include "pch.h"
#include "obj-common.h"

static Trampoline* goalringt;
static Trampoline* itembox_t;
static Trampoline* airbox_t;
static Trampoline* CountPerfectRings_t;

static const double RingDist = 336200.0;

static void __cdecl CountPerfectRings_r()
{
	VoidFunc(original, CountPerfectRings_t->Target());
	original();

	if (isSADXLevel())
	{
		if (CurrentObjectList && SETEntries)
		{
			for (int i = 0; i < *(int*)SETFile; ++i)
			{
				int flag = CurrentObjectList->List[SETEntries[i].ID & 0x7FFF].ObjectFlags & 0x70;

				if (flag == 0x50) // RingGroup
				{
					PerfectRings += min(static_cast<int>(SETEntries[i].Scale.x) + 1, 8);
				}
				else if (flag == 0x60) // Itemboxes
				{
					switch (static_cast<int>(SETEntries[i].Scale.x))
					{
					case 2:
						PerfectRings += 5;
						break;
					case 3:
						PerfectRings += 10;
						break;
					case 4:
						PerfectRings += 20;
						break;
					}
				}
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
	njRotateZ(_nj_current_matrix_ptr_, data->Rotation.z);
	njRotateX(_nj_current_matrix_ptr_, data->Rotation.x);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	njCalcPoint(&offset, pos, _nj_current_matrix_ptr_);
	njAddVector(pos, &data->Position);
	njPopMatrixEx();
}

static void CalcRingPosLine(EntityData1* data, NJS_VECTOR* pos, int index)
{
	NJS_VECTOR offset = { 0.0f, 0.0f, index % 2 ? ceilf(static_cast<float>(index) * 0.5f) * data->Scale.y : static_cast<float>(index) * data->Scale.y * -0.5f };
	
	njPushUnitMatrix();
	njTranslateV(0, &data->Position);
	njRotateZ(_nj_current_matrix_ptr_, data->Rotation.z);
	njRotateX(_nj_current_matrix_ptr_, data->Rotation.x);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
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
			UpdateSetDataAndDelete(obj);
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

void __cdecl Beetle_Stationary(ObjectMaster* a1)
{
	EntityData1* entity = a1->Data1.Entity;
	entity->Rotation.x = 0;
	entity->Rotation.z = 0xC1;
	entity->Scale = { 0.10, 3.50, 51 };
	a1->MainSub = (ObjectFuncPtr)Beetle_Main;
}

void __cdecl Beetle_Attack(ObjectMaster* a1)
{
	EntityData1* entity = a1->Data1.Entity;
	entity->Rotation.x = 0x1;
	entity->Rotation.z = 0x1C0;
	entity->Scale = { 4, 1, 150 };
	a1->MainSub = (ObjectFuncPtr)Beetle_Main;
}

void __cdecl Beetle_Electric(ObjectMaster* a1)
{
	EntityData1* entity = a1->Data1.Entity;
	entity->Rotation.x = 0;
	entity->Rotation.z = 0x101;
	entity->Scale = { 0.10, 3.50, 51 };
	a1->MainSub = (ObjectFuncPtr)Beetle_Main;
}

void __cdecl Robots(ObjectMaster* a1)
{
	EntityData1* entity = a1->Data1.Entity;
	entity->Rotation.x = 0x1;
	entity->Rotation.z = 0x100;
	entity->Scale = { 0, 1, 126 };
	entity->Position.y -= 6.5;
	a1->MainSub = (ObjectFuncPtr)E_AI;
}

void CommonObjects_Init()
{
	//SADX Fixes
	goalringt = new Trampoline((int)GoalRing_Main, (int)GoalRing_Main + 0x6, GoalRing_r);
	itembox_t = new Trampoline((int)ItemBox_Main, (int)ItemBox_Main + 0x5, ItemBox_r);
	airbox_t = new Trampoline((int)ItemBoxAir_Main, (int)ItemBoxAir_Main + 0x5, AirBox_r);
	CountPerfectRings_t = new Trampoline((int)CountPerfectRings, (int)CountPerfectRings + 0x6, CountPerfectRings_r);

	// Fix Rings draw distance with GroupRing
	WriteData((const double**)0x6C0FA9, &RingDist);
}