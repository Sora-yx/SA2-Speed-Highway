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

bool SHCage_isPlayerOnPlatform(ObjectMaster* a1)
{
	EntityData1* v3; // r30
	bool result = false; // r3
	NJS_VECTOR v5; // [sp+50h] [-40h] BYREF
	NJS_VECTOR v6; // [sp+60h] [-30h] BYREF
	NJS_VECTOR a2;

	v3 = a1->Data1.Entity;
	a2.x = MainCharObj1[0]->Position.x - v3->Position.x;
	a2.y = MainCharObj1[0]->Position.y - v3->Position.y - 20.0;
	a2.z = MainCharObj1[0]->Position.z - v3->Position.z;

	if (v3->Rotation.y != 0x10000)
		njRotateY(0, (unsigned __int16)-HIWORD(v3->Rotation.y));

	if (fabs(a2.x) < 20.0 && fabs(a2.y) < 10.0 && fabs(a2.z) < 20.0) {

		if ((v3->Status & 0x100u))
		{
			return true;
		}
	}

	return false;
}

void __cdecl SHDispCage(ObjectMaster* a1)
{
	EntityData1* v1; // esi
	Angle v2; // eax

	v1 = a1->Data1.Entity;
	njControl3D_Backup();
	SetMaterialColor(1, 1, 1, 1);
	njPushMatrix(0);
	njTranslateV(0, &v1->Position);
	v2 = v1->Rotation.y;
	if (v2)
	{
		njRotateY(0, (unsigned __int16)v2);
	}
	njSetTexture(&highwayObj_TEXLIST);
	njTranslate(0, 0.0, 0.0, -30.0);
	//sub_4083F0((NJS_ACTION*)v1->timer, v1->Scale.x, 0, 1.0);
	DrawObject((NJS_OBJECT*)a1->field_4C);
	njPopMatrix(1u);
	ResetMaterialColorOffset();
	njControl3D_Restore();
}

void Cage_UpdatePlayerPos(ObjectMaster* obj, float x, float y, float z) {
	if (SHCage_isPlayerOnPlatform(obj))
	{
		MainCharObj1[0]->Position.x += x;
		MainCharObj1[0]->Position.y += y;
		MainCharObj1[0]->Position.z += z;
	}
}

void SH_DescendCage(float x, float y, float z, ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* dyncol = (NJS_OBJECT*)obj->EntityData2;

	float rotY = njSin(data->Rotation.y);

	x = -(float)((float)rotY * (float)1.225);
	float rotY2 = njCos(data->Rotation.y);

	z = -(float)((float)rotY2 * (float)1.225);

	data->Position.x += x;
	data->Position.y += y;
	data->Position.z += z;

	// Update dyncol position
	*(NJS_VECTOR*)dyncol->pos = data->Position;
	Cage_UpdatePlayerPos(obj, x, y, z);
}

void SH_AscendCage(float x, float y, float z, ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* dyncol = (NJS_OBJECT*)obj->EntityData2;

	x = njSin(data->Rotation.y) * 1.225f;
	z = njCos(data->Rotation.y) * 1.225f;


	data->Position.x += x;
	data->Position.y += y;
	data->Position.z += z;

	// Update dyncol position
	*(NJS_VECTOR*)dyncol->pos = data->Position;

	// Move player
	Cage_UpdatePlayerPos(obj, x, y, z);
}

void __cdecl SHExecCage(ObjectMaster* obj)
{
	EntityData1* data; // ebp
	ObjUnknownA* saveObjPos;
	int* v5; // edx
	double v6; // st7
	double v7; // st7
	__int16 v8; // ax
	double v9; // st7
	float getposX; // edx
	float getposY; // ecx
	NJS_ACTION* alertCageAnim; // ecx
	double animCurFrame; // st7
	EntityData1* parentData; // [esp+14h] [ebp+4h]
	float getposZ; // [esp+14h] [ebp+4h]

	data = obj->Data1.Entity;
	saveObjPos = obj->UnknownA_ptr;
	parentData = obj->Parent->Data1.Entity;

	switch (data->Action)
	{
	case 0:
	{
		data->Rotation.z = 0;
		data->Rotation.x = 0;
		data->Action = 1;

		//data->timer = (int*)&cageAlertAnim;
		obj->field_4C = SH_Cage->getmodel();
		data->Index = 0;
		// SwitchSignal(data);
		obj->DeleteSub = DeleteFunc_DynCol;
		obj->DisplaySub = SHDispCage;

		DynCol_AddFromObject(obj, SH_CageCol->getmodel(), &data->Position, data->Rotation.y, 0x68000001);
		saveObjPos->field_24 = 0.0; //X
		saveObjPos->field_28 = 0.0; //Y
		saveObjPos->field_2C = 0.0; //Z
	}
	break;
	case 1:
		CheckCraneColli(data);

		if (SHCage_isPlayerOnPlatform(obj))
		{
			data->Action = 2;
			data->Index = 1;
			//SwitchSignal(data);
		}
		break;
	case 2:
	{
		CheckCraneColli(data);
		float result = data->Position.y - parentData->Position.y;
		if (result > 100.0)
		{
			PlaySoundProbably(sound_SHCageEnd, 0, 0, 0);
			data->Action = 3;
			data->Index = 0;
			saveObjPos->field_24 = 0.0;
			saveObjPos->field_28 = 0.0;
			saveObjPos->field_2C = 0.0;
		}

		SH_AscendCage(saveObjPos->field_24, 0.25f, saveObjPos->field_2C, obj);

		/*getposY = data->Position.y;
		getposX = (float)(data->Position.x + saveObjPos->x);*/

		//getposZ = data->Position.z;

	}
	break;
	case 3:
		CheckCraneColli(data);

		if (SHCage_isPlayerOnPlatform(obj))
		{
			v8 = data->field_6;
			data->field_6 = v8 + 1;
			if ((unsigned __int16)v8 > 120u)
			{
				data->Action = 4;
				data->Index = 1;
				data->field_6 = 0;
				//SwitchSignal(data);
			}
		}
		break;
	case 4:
	{
		CheckCraneColli(data);
		float result2 = data->Position.y  - parentData->Position.y;
		if (result2 > 0.0)
		{
			SH_DescendCage(saveObjPos->field_24, -0.25f, saveObjPos->field_2C, obj);
			//QueueSound_XYZ(103, data, 1, 0, 2, getposX, getposY, getposZ);
		}
		else
		{
			data->Action = 5;

			data->Index = 0;
			saveObjPos->field_24 = 0.0;
			saveObjPos->field_28 = 0.0;
			saveObjPos->field_2C = 0.0;
			//SwitchSignal(data);
			//DoSoundQueueThing(103);
			PlaySoundProbably(sound_SHCageEnd, 0, 0, 0);
			//PlaySound(104, 0, 0, 0);
		}
	}
		break;
	case 5:
		CheckCraneColli(data);

		if (SHCage_isPlayerOnPlatform(obj))
		{
			data->Action = 1;
			data->field_6 = 0;
		}
		break;
	default:

		break;
	}
	/*alertCageAnim = (NJS_ACTION*)data->timer;
	animCurFrame = data->Scale.x + 0.2;
	data->Scale.x = animCurFrame;
	if (animCurFrame >= (double)alertCageAnim->motion->nbFrame)
	{
		data->Scale.x = 0.0;
	}*/
}

void __cdecl dispSHCrane(ObjectMaster* obj)
{
	EntityData1* data; // esi
	Angle rotY; // eax

	data = obj->Data1.Entity;

	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrix(0);
	njTranslateV(0, &data->Position);
	rotY = data->Rotation.y;
	if (rotY)
	{
		njRotateY(0, (unsigned __int16)rotY);
	}
	DrawObject((NJS_OBJECT*)obj->field_4C);
	njPopMatrix(1u);

}

void __cdecl OCrane(ObjectMaster* obj)
{
	EntityData1* data; // esi
	Angle v2; // eax
	int* getCraneObj; // ecx
	int getCraneObj2; // edx
	ObjectMaster* childObj; // eax
	EntityData1* childData; // eax

	data = obj->Data1.Entity;
	if (!ClipObject(obj, 1020100.0))
	{

		if (data->Action)
		{
			if (data->Action == 1)
			{
				CheckCraneColli(data);

			}
			else
			{
				DeleteFunc_DynCol(obj);
			}
		}
		else
		{
			obj->field_4C = SH_Rail->getmodel();
			obj->DeleteSub = DeleteFunc_DynCol;
			obj->DisplaySub = dispSHCrane;
			data->Rotation.z = 0;
			data->Rotation.x = 0;

			NJS_OBJECT* dyncol = DynCol_AddFromObject(obj, SH_RailCol->getmodel(), &data->Position, data->Rotation.y, SurfaceFlag_Solid);
			dyncol->pos[1] -= 6.0f;

			childObj = LoadChildObject((LoadObj)(LoadObj_UnknownA | LoadObj_Data1), SHExecCage, obj);
			if (childObj)
			{
				childData = childObj->Data1.Entity;
				childData->Rotation.z = 0;
				childData->Rotation.x = 0;
			}

			data->Action = 1;
		}
	}
}