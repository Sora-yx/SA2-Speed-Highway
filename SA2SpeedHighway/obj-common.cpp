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

/*void __cdecl DroppedRing_Main(ObjectMaster* a1)
{
    float* v2; // edi
    EntityData1* v3; // esi
    __int16 v4; // ax
    CollisionInfo* v5; // ecx
    double v6; // st7
    double v7; // st7
    double v8; // st7
    Angle v9; // eax
    Angle v10; // ecx
    double v11; // st7
    Angle v12; // ecx
    Angle v13; // eax
    double v14; // st7
    float v15; // edx
    char v16; // al
    bool v17; // sf
    float v18; // ecx
    double v19; // st7
    unsigned __int8 v21; // c0
    unsigned __int8 v22; // c2
    double v23; // st7
    double v24; // st7
    SegaGarbage v25; // edx
    __int16 v26; // ax
    CollisionInfo* v27; // ecx
    float v28; // edx
    float v29; // eax
    float v30; // ecx
    float y; // [esp+0h] [ebp-5Ch]
    float v32; // [esp+18h] [ebp-44h]
    float v33; // [esp+1Ch] [ebp-40h]
    float v34; // [esp+1Ch] [ebp-40h]
    Vector3 vs; // [esp+20h] [ebp-3Ch] BYREF
    Vector3 a2; // [esp+2Ch] [ebp-30h] BYREF
    Vector3 a3; // [esp+38h] [ebp-24h] BYREF
    Vector3 vd; // [esp+44h] [ebp-18h] BYREF
    Vector3 v39; // [esp+50h] [ebp-Ch] BYREF
    float a1a; // [esp+60h] [ebp+4h]
    ObjectMaster* a1b; // [esp+60h] [ebp+4h]
    ObjectMaster* a1c; // [esp+60h] [ebp+4h]

    v3 = a1->Data1.Entity;
    v2 = (float*)a1->UnknownB_ptr;
    v33 = 0.0;
    switch (v3->Action)
    {
    case 0:
        *v2 = v3->Position.y - 100.0;

        Collision_Init(a1, &RingCollision, 1, 7u);
        v3->Position.y = v3->Position.y + 10.0;
        v3->Action = 1;
        v3->Scale.x = 0.30000001;
        v3->Scale.z = 0.30000001;
        v3->Scale.y = 4.5999999;
        v3->LoopData.SInteger = 0x3F800000;
        a1a = (unsigned __int64)((double)rand() * 0.000030517578 * 360.0 * 65536.0 * 0.002777777777777778);
        v3->timer = (int*)0x3F800000;
        v3->field_6 = 0;
        v3->CharIndex.Single = (float)SLODWORD(a1a);
        v3->NextAction = 0;
        v3->Id = 11;
        return;
    case 1:
        v5 = v3->Collision;
        v4 = v5->Flag;
        if ((v4 & 1) != 0)
        {
            v5->Flag = v4 & ~1;
            v3->CharIndex.SInteger = 0;
            v3->Scale.x = -2.0;
            v3->Scale.z = -4.0;

            v6 = v3->Position.y + 3.4400001;
            v3->Action = 4;
            v3->Position.y = v6;
            if ((v3->Collision->CollidingObject->Object == MainCharacter[0]))
            {
                AddRings(0, 1);
            }
            return;
        }
        v7 = v2[1] - 1.0;
        v2[1] = v7;
        if (v7 < 0.0)
        {
            v2[1] = 8.0;
            y = v3->Position.y + 6.8800001;
           // v8 = getShadowPos(v3->Position.x, y, v3->Position.z, &v3->Rotation);
            *v2 = v8;
            if (-1000000.0 == v8)
            {
                *v2 = v3->Position.y - 100.0;
            }
        }
        v10 = v3->Rotation.y;
        ++v3->field_6;
        v11 = njSin(v10);
        v12 = v3->Rotation.y;
        v3->Scale.x = v11 * 0.30000001;
        v3->Scale.z = njCos(v12) * 0.30000001;
        njPushMatrix(_nj_unit_matrix_);
        v9 = v3->Rotation.z;
        if (v9)
        {
            njRotateZ(0, (unsigned __int16)v9);
        }
        v13 = v3->Rotation.x;
        if (v13)
        {
            njRotateX(0, (unsigned __int16)v13);
        }
        if (v3->LoopData.Single < 0.2)
        {
            v19 = *(float*)&v3->timer + 0.079999998;
            *(float*)&v3->timer = v19;
            if (v21 | v22)
            {
                v23 = 0.30000001 / v19;
                v3->Position.x = v23 * v3->Scale.x + v3->Position.x;
                v3->Position.z = v23 * v3->Scale.z + v3->Position.z;
            }
            else if (v19 >= 13.0)
            {
                a2.x = 0.0;
                a2.y = 6.8800001;
                a2.z = 0.0;
                njCalcVector(0, &a2, &vd);
                v24 = vd.x;
                v33 = vd.z;
                goto LABEL_30;
            }
            v24 = 0.0;
        LABEL_30:
            v3->Action = 2;
            v25.Pointer = *(void**)v2;
            v3->Scale.x = v24;
            v3->LoopData = v25;
            v3->Scale.z = v33;
            njPopMatrix(1u);
            return;
        }
        v3->Position.x = v3->Scale.x * v3->LoopData.Single + v3->Position.x;
        v3->Position.z = v3->Scale.z * v3->LoopData.Single + v3->Position.z;
        if (v3->Scale.y < 0.0)
        {
            v3->Position.y = *v2;
        }
        else
        {
            v3->Position.y = (v3->Scale.y - (double)(unsigned __int16)v3->field_6 * 0.33333334)
                * 0.33333334
                + v3->Position.y;
        }
        vs.x = 0.0;
        vs.y = 3.4400001;
        vs.z = 0.0;
        njCalcVector(0, &vs, &vd);
        if (*v2 >= (double)v3->Position.y)
        {
            v14 = v3->LoopData.Single;
            v3->field_6= 0;
            v3->LoopData.Single = v14 - 0.039999999;
            v3->Scale.y = v3->Scale.y - 0.28;
        }
        vs.x = 0.0;
        vs.y = 1.0;
        vs.z = 0.0;
        njCalcVector(0, &vs, &v39);
        if (v39.y < 0.69999999)
        {
            v15 = v3->Scale.z;
            a2.x = v3->Scale.x;
            a2.z = v15;
            a2.y = 1.0;
            njCalcPoint_(&a2, &a3, CURRENT_MATRIX);
            v3->Rotation.y = (unsigned __int64)(atan2(a3.x, a3.z) * 65536.0 * 0.1591549762031479);
        }
        njPopMatrix(1u);
        v16 = v3->NextAction + 1;
        v17 = (char)(v3->NextAction - 45) < 0;
        v3->NextAction = v16;
        if (!(v17 ^ __OFSUB__(v16, 46) | (v16 == 46)))
        {
            v18 = v3->Position.y;
            v3->NextAction = 47;
            a1b = (ObjectMaster*)LODWORD(v18);
            v3->Position.y = v18 + 3.4400001;
            AddToCollisionList(v3);
            LODWORD(v3->Position.y) = a1b;
        }
        sub_44F960(a1, *v2);
        a1->DisplaySub = sub_44FC90;
        return;
    case 2:
        v27 = v3->Collision;
        v26 = v27->Flag;
        if ((v26 & 1) != 0)
        {
            v27->Flag = v26 & 0xFFFE;
            v3->Action = 4;
            v3->CharIndex.SInteger = 0;
            v3->Scale.x = -2.0;
            v3->Scale.z = -4.0;
     
            v3->Position.y = v3->Position.y + 3.4400001;

                AddRings(0, 1);
            
            a1->DisplaySub = Ring_Collect_Maybe;
        }
        else
        {
            v28 = v3->Position.y;
            v29 = v3->Position.x;
            v30 = v3->Position.z;
            v3->Position.y = v28 + 3.4400001;
            a1c = (ObjectMaster*)LODWORD(v28);
            v32 = v29;
            v34 = v30;
            v3->Position.x = v3->Scale.x + v3->Position.x;
            v3->Position.z = v3->Position.z + v3->Scale.z;
            AddToCollisionList(a1);
            ++v3->field_6;
            v3->Position.y = a1c;
            v3->Position.x = v32;
            v3->Position.z = v34;
            if ((FrameCountIngame & 2) != 0)
            {
                sub_44F960(a1, v3->LoopData.Single);
            }
            if (v3->field_6 >= 0x64u)
            {
                v3->Action = 3;
            }
            a1->DisplaySub = sub_44FCE0;
        }
        return;
    case 3:
        a1->MainSub = DeleteObject_;
        return;
    case 4:
        Ring_Collect_Maybe_Again(v3);
        return;
    default:
        return;
    }
}*/

/*void __cdecl SpawnDroppedRings(float x, float y, float z, int count)
{
	int v4; // edi
	int v5; // ebp
	ObjectMaster* v6; // eax
	EntityData1* v7; // esi
	float v8; // [esp+0h] [ebp-4h]

	v8 = (double)rand() * 0.000030517578 * 360.0;
	if (count > 0)
	{
		v4 = 0;
		v5 = count;
		do
		{
			/*v6 = LoadObject(LoadObj_UnknownB | LoadObj_Data1, "DroppedRing_Main", DroppedRing_Main, LoadObj_Data1);
			if (v6)
			{
				v7 = v6->Data1.Entity;
				v7->Position.x = x;
				v7->Position.z = z;
				v7->Position.y = y;
				v7->Rotation.y = (unsigned __int64)(((double)(v4 / count) + v8) * 65536.0 * 0.002777777777777778);
			}
			v4 += 360;
			--v5;
		}         while (v5);
	}
}*/

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