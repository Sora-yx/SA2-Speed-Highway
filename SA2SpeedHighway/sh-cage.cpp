#include "pch.h"

extern NJS_TEXLIST highwayObj_TEXLIST;

static ModelInfo* SH_Cage;
static ModelInfo* SH_Rail;
static ModelInfo* SH_CageCol;
static ModelInfo* SH_RailCol;

void LoadCraneModels() {
	SH_Cage = LoadMDL("crane_cage", ModelFormat_Chunk);
	SH_Rail = LoadMDL("crane_rail", ModelFormat_Chunk);

	//Load model collisions
	SH_CageCol = LoadMDL("crane_cage", ModelFormat_Basic);
	SH_RailCol = LoadMDL("crane_rail", ModelFormat_Basic);
	return;
}

bool sub_61B060(ObjectMaster* a1)
{
	/*EntityData1* v1; // esi
	Vector3 a2; // [esp+4h] [ebp-18h] BYREF
	Vector3 a3; // [esp+10h] [ebp-Ch] BYREF

	v1 = a1->Data1.Entity;
	a2.x = MainCharObj1[0]->Position.x - v1->Position.x;
	a2.y = MainCharObj1[0]->Position.y - v1->Position.y - 20.0;
	a2.z = MainCharObj1[0]->Position.z - v1->Position.z;
	njPushMatrix(_nj_unit_matrix_);
	if (v1->Rotation.y != 0x10000)
	{
		njRotateY(0, (unsigned __int16)-LOWORD(v1->Rotation.y));
	}
	//njCalcVector(0, &a2, &a3, false);
	njPopMatrixEx();
	return (MainCharObj1[0]->Status & 1) != 0 && fabs(a3.x) < 20.0 && fabs(a3.y) < 10.0 && fabs(a3.z) < 20.0;*/
	return false;
}


void __cdecl sub_442120(float a1, float a2, float a3, float a4)
{
	int v4; // edi
	EntityData1* v5; // ecx
	CharObj2Base* v6; // esi
	double v7; // st7
	double v8; // st6
	double v9; // st5
	double v10; // st7
	int v11; // eax
	float v12; // [esp+0h] [ebp-4h]

	v4 = 0;
	while (1)
	{
		v5 = MainCharObj1[v4];
		if (v5)
		{
			if (v5->Position.y >= (double)a2)
			{
				v6 = MainCharObj2[v4];
				v7 = a1 - v5->Position.x;
				v8 = a2 - v5->Position.y;
				v9 = a3 - v5->Position.z;
				v12 = v7 * v7 + v8 * v8 + v9 * v9;
				v10 = sqrt(v12) - a4;
				if (v10 <= 120.0 && (v6->field_12) < 15)
				{
					break;
				}
			}
		}
		if (++v4 >= 2)
		{
			return;
		}
	}
	/*v11 = 32 * (v6->field_12);
	*(float*)((char*)v6->SurfaceInfo. array_15x32 + v11) = a1;
	*(float*)((char*)v6->array_15x32 + v11 + 4) = a2;
	*(float*)((char*)v6->array_15x32 + v11 + 8) = a3;
	*(float*)((char*)v6->array_15x32 + v11 + 12) = a4;
	*(float*)((char*)v6->array_15x32 + v11 + 16) = v10;
	++(v6->field_12);*/
}



void CheckCraneColli(EntityData1* a1) {

	if (IsPlayerInsideSphere(&a1->Position, 570.0)) {
		a1->Status |= 1u;
	}
	else {
		a1->Status &= 0xFEu;
	}
}

void __cdecl DispSHCage(ObjectMaster* a1)
{
	EntityData1* v1; // esi
	Angle v2; // eax

	v1 = a1->Data1.Entity;


	njPushMatrixEx();
	njTranslateV(0, &v1->Position);
	v2 = v1->Rotation.y;
	if (v2)
	{
		njRotateY(0, (unsigned __int16)v2);
	}

	njSetTexture(&highwayObj_TEXLIST);
	njTranslate(0, 0.0, 0.0, -30.0);
	DrawObject(SH_Cage->getmodel());
	njPopMatrixEx();

}



void __cdecl SHExecCage(ObjectMaster* a1)
{
	EntityData1* v2; // ebp
	ObjUnknownA* v3; // ebx
	NJS_OBJECT* v4; // eax
	int* v5; // edx
	double v6; // st7
	double v7; // st7
	__int16 v8; // ax
	double v9; // st7
	float v10; // edx
	float v11; // ecx
	int* v12; // ecx
	double v13; // st7
	EntityData1* a2; // [esp+14h] [ebp+4h]
	float a2a; // [esp+14h] [ebp+4h]

	v2 = a1->Data1.Entity;
	v3 = a1->UnknownA_ptr;
	a2 = a1->Parent->Data1.Entity;
	switch (v2->Action)
	{
	case 0:
	{
		v2->Rotation.z = 0;
		v2->Rotation.x = 0;
		v2->Action = 1;
		//v2->timer = //Stock animation here
		v2->Index = 0;
		//sub_61B130((int)v2);
		a1->DeleteSub = ObjectFunc_DynColDelete;
		a1->DisplaySub = DispSHCage;

		NJS_OBJECT* dynobj = GetFreeDynObject();

		memcpy(dynobj, SH_CageCol->getmodel(), sizeof(NJS_OBJECT));
		dynobj->scl[2] = 1.0;
		dynobj->scl[1] = 1.0;
		dynobj->scl[0] = 1.0;
		dynobj->evalflags &= 0xFFFFFFFC;

		dynobj->ang[0] = v2->Rotation.x;
		dynobj->ang[1] = v2->Rotation.y;
		dynobj->ang[2] = v2->Rotation.z;
		dynobj->pos[0] = v2->Position.x;
		dynobj->pos[1] = v2->Position.y;
		dynobj->pos[2] = v2->Position.z;

		DynCol_Add(SurfaceFlag_Solid, a1, dynobj);
		a1->EntityData2 = (UnknownData2*)dynobj;
	}
		break;
	case 1:
		CheckCraneColli(v2);
		if (sub_61B060(a1))
		{
			v2->Action = 2;
			v2->Index = 1;
			//sub_61B130((int)v2);
		}
		break;
	case 2:
		CheckCraneColli(v2);
		if (v2->Position.y - a2->Position.y > 100.0)
		{
			v2->Action = 3;
			goto LABEL_16;
		}
		v6 = njSin(v2->Rotation.y);
		v3->field_14 = 0.25;
		*(float*)&v3->field_10 = v6 * 1.225;
		v7 = njCos(v2->Rotation.y) * 1.225;
		goto LABEL_18;
	case 3:
		CheckCraneColli(v2);
		if (sub_61B060(a1))
		{
			/*v8 = v2->InvulnerableTime;
			v2->InvulnerableTime = v8 + 1;
			if ((unsigned __int16)v8 > 0x78u)
			{
				v2->Action = 4;
				v2->Index = 1;
				v2->InvulnerableTime = 0;
				sub_61B130((int)v2);
			}*/
		}
		break;
	case 4:
		CheckCraneColli(v2);
		if (v2->Position.y - a2->Position.y > 0.0)
		{
			v9 = njSin(v2->Rotation.y);
			v3->field_14 = -0.25;
			*(float*)&v3->field_10 = -(v9 * 1.225);
			v7 = -(njCos(v2->Rotation.y) * 1.225);
		LABEL_18:
			*(float*)&v3->field_18 = v7;
			v2->Position.x = v2->Position.x + *(float*)&v3->field_10;
			v10 = v2->Position.x;
			v2->Position.y = v3->field_14 + v2->Position.y;
			v11 = v2->Position.y;
			a2a = v2->Position.z + *(float*)&v3->field_18;
			v2->Position.z = a2a;
			//QueueSound_XYZ(103, v2, 1, 0, 2, v10, v11, a2a);
		}
		else
		{
			v2->Action = 5;
		LABEL_16:
			v2->Index = 0;
			v3->field_10 = 0;
			v3->field_14 = 0.0;
			v3->field_18 = 0;
			//sub_61B130((int)v2);
			//DoSoundQueueThing(103);
			//PlaySound(104, 0, 0, 0);
		}
		break;
	case 5:
		CheckCraneColli(v2);
		if (sub_61B060(a1))
		{
			v2->Action = 1;
			//v2->InvulnerableTime = 0;
		}
		break;
	default:

		//remove dyncol

		break;
	}
	//v12 = v2->timer;
	/*v13 = v2->Scale.x + 0.2;
	v2->Scale.x = v13;
	if (v13 >= (double)*(unsigned int*)(v12[1] + 4))
	{
		v2->Scale.x = 0.0;
	}*/
	memcpy(&v3->field_1C, v3, 0x1Cu);
	sub_442120(v2->Position.x, v2->Position.y, v2->Position.z, 15.0);
}



void __cdecl dispSHRail(ObjectMaster* obj)
{
	EntityData1* v1; // esi
	Angle v2; // eax

	v1 = obj->Data1.Entity;

	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrixEx();
	njTranslateV(0, &v1->Position);
	v2 = v1->Rotation.y;
	if (v2)
	{
		njRotateY(0, (unsigned __int16)v2);
	}

	DrawObject(SH_Rail->getmodel());
	njPopMatrixEx();

}

void __cdecl OCrane(ObjectMaster* obj)
{
	EntityData1* v1; // esi
	Angle v2; // eax
	int* v4; // ecx
	int v5; // edx
	ObjectMaster* v6; // eax
	EntityData1* v7; // eax

	v1 = obj->Data1.Entity;
	if (!ClipObject(obj, 1020100.0))
	{
		if (v1->Action)
		{
			if (v1->Action == 1)
			{
				CheckCraneColli(v1);
				//dispCrane(obj);
			}
			else
			{
				ObjectFunc_DynColDelete(obj);
			}
		}
		else
		{
			obj->DeleteSub = ObjectFunc_DynColDelete;
			obj->DisplaySub = dispSHRail;

			v1->Rotation.z = 0;
			v1->Rotation.x = 0;


			NJS_OBJECT* dynobj = GetFreeDynObject();
			
			memcpy(dynobj, SH_RailCol->getmodel(), sizeof(NJS_OBJECT));
			dynobj->scl[2] = 1.0;
			dynobj->scl[1] = 1.0;
			dynobj->scl[0] = 1.0;
			dynobj->evalflags &= 0xFFFFFFFC;

			dynobj->ang[0] = v1->Rotation.x;
			dynobj->ang[1] = v1->Rotation.y;
			dynobj->ang[2] = v1->Rotation.z;
			dynobj->pos[0] = v1->Position.x;
			dynobj->pos[1] = v1->Position.y;
			dynobj->pos[2] = v1->Position.z;

			DynCol_Add(SurfaceFlag_Solid, obj, dynobj);
			obj->EntityData2 = (UnknownData2*)dynobj;


			v6 = LoadChildObject((LoadObj)(LoadObj_UnknownA | LoadObj_Data1), (void(__cdecl*)(ObjectMaster*))SHExecCage, obj);
			if (v6)
			{
				v7 = v6->Data1.Entity;
				v7->Rotation.z = 0;
				v7->Rotation.x = 0;
			}


			v1->Action = 1;
		}
	}
}