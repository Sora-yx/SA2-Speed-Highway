#include "pch.h"
#include "objects.h"
#include "sh-cage.h"

static ModelInfo* SH_Cage;
static ModelInfo* SH_Rail;
static ModelInfo* SH_CageCol;
static ModelInfo* SH_RailCol;

void LoadCraneModels()
{
	SH_Cage = LoadMDL("crane_cage", ModelFormat_Chunk);
	SH_Rail = LoadMDL("crane_rail", ModelFormat_Chunk);

	//Load model collisions
	SH_CageCol = LoadMDL("crane_cage", ModelFormat_Basic);
	SH_RailCol = LoadMDL("crane_rail", ModelFormat_Basic);
	return;
}

void FreeCraneModels()
{
	FreeMDL(SH_Cage);
	FreeMDL(SH_Rail);
	FreeMDL(SH_CageCol);
	FreeMDL(SH_RailCol);
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

void __cdecl DispSHCage(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	njPushMatrixEx();
	njSetTexture(&highwayObj_TEXLIST);
	njTranslateEx(&data->Position);
	njRotateY(CURRENT_MATRIX, data->Rotation.y);
	njTranslate(0, 0.0, 0.0, -30.0f);
	DrawObject(SH_Cage->getmodel());
	njPopMatrixEx();
}

void __cdecl SHExecCage(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity; // ebp
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
	EntityData1* parent; // [esp+14h] [ebp+4h]
	float a2a; // [esp+14h] [ebp+4h]

	v3 = obj->UnknownA_ptr;
	parent = obj->Parent->Data1.Entity;
	switch (data->Action)
	{
	case 0:
		data->Action = 1;
		data->Index = 0;
		//sub_61B130((int)data);

		obj->DeleteSub = DeleteFunc_DynCol;
		obj->DisplaySub = DispSHCage;
		obj->field_4C = SH_Cage->getmodel();

		DynCol_AddFromObject(obj, SH_CageCol->getmodel(), &data->Position, data->Rotation.y, SurfaceFlag_Solid | SurfaceFlag_Dynamic);

		break;
	case 1:
		if (sub_61B060(obj))
		{
			data->Action = 2;
			data->Index = 1;
			//sub_61B130((int)data);
		}
		break;
	case 2:
		if (data->Position.y - parent->Position.y > 100.0f)
		{
			data->Action = 3;
			data->Index = 0;
			v3->field_10 = 0;
			v3->field_14 = 0.0;
			v3->field_18 = 0;
			//sub_61B130((int)data);
			//DoSoundQueueThing(103);
			//PlaySound(104, 0, 0, 0);
		}
		v6 = njSin(data->Rotation.y);
		v3->field_14 = 0.25;
		*(float*)&v3->field_10 = v6 * 1.225;
		v7 = njCos(data->Rotation.y) * 1.225;
		*(float*)&v3->field_18 = v7;
		data->Position.x = data->Position.x + *(float*)&v3->field_10;
		v10 = data->Position.x;
		data->Position.y = v3->field_14 + data->Position.y;
		v11 = data->Position.y;
		a2a = data->Position.z + *(float*)&v3->field_18;
		data->Position.z = a2a;
		//QueueSound_XYZ(103, data, 1, 0, 2, v10, v11, a2a);
	case 3:
		if (sub_61B060(obj))
		{
			/*v8 = data->InvulnerableTime;
			data->InvulnerableTime = v8 + 1;
			if ((unsigned __int16)v8 > 0x78u)
			{
				data->Action = 4;
				data->Index = 1;
				data->InvulnerableTime = 0;
				sub_61B130((int)data);
			}*/
		}
		break;
	case 4:
		if (data->Position.y - parent->Position.y > 0.0f)
		{
			v9 = njSin(data->Rotation.y);
			v3->field_14 = -0.25;
			*(float*)&v3->field_10 = -(v9 * 1.225);
			v7 = -(njCos(data->Rotation.y) * 1.225);
			*(float*)&v3->field_18 = v7;
			data->Position.x = data->Position.x + *(float*)&v3->field_10;
			v10 = data->Position.x;
			data->Position.y = v3->field_14 + data->Position.y;
			v11 = data->Position.y;
			a2a = data->Position.z + *(float*)&v3->field_18;
			data->Position.z = a2a;
			//QueueSound_XYZ(103, data, 1, 0, 2, v10, v11, a2a);
		}
		else
		{
			data->Action = 5;
			data->Index = 0;
			v3->field_10 = 0;
			v3->field_14 = 0.0;
			v3->field_18 = 0;
			//sub_61B130((int)data);
			//DoSoundQueueThing(103);
			//PlaySound(104, 0, 0, 0);
		}
		break;
	case 5:
		if (sub_61B060(obj))
		{
			data->Action = 1;
			//data->InvulnerableTime = 0;
		}
		break;
	}

	//v12 = data->timer;
	/*v13 = data->Scale.x + 0.2;
	data->Scale.x = v13;
	if (v13 >= (double)*(unsigned int*)(v12[1] + 4))
	{
		data->Scale.x = 0.0;
	}*/

	memcpy(&v3->field_1C, v3, 0x1Cu);
	sub_442120(data->Position.x, data->Position.y, data->Position.z, 15.0f);
}

void CheckCraneColli(EntityData1* data) {
	if (IsPlayerInsideSphere(&data->Position, 570.0f))
	{
		data->Status |= 0x100u;
	}
	else
	{
		data->Status &= 0xFEFFu;
	}
}

void __cdecl OCrane_Display(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* object = (NJS_OBJECT*)obj->field_4C;

	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrixEx();
	njTranslateEx(&data->Position);
	njRotateY(0, data->Rotation.y);
	DrawChunkModel(object->chunkmodel);
	njPopMatrixEx();
}

void __cdecl OCrane_Main(ObjectMaster* obj)
{
	if (!ClipSetObject(obj))
	{
		EntityData1* data = obj->Data1.Entity;

		if (!ClipSetObject(obj))
		{
			CheckCraneColli(data);
		}
	}
}

void __cdecl OCrane(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	obj->MainSub = OCrane_Main;
	obj->DeleteSub = DeleteFunc_DynCol;
	obj->DisplaySub = OCrane_Display;
	obj->field_4C = SH_Rail->getmodel();;

	DynCol_AddFromObject(obj, SH_RailCol->getmodel(), &data->Position, data->Rotation.y, SurfaceFlag_Solid);

	LoadChildObject((LoadObj)(LoadObj_UnknownA | LoadObj_Data1), SHExecCage, obj);
}