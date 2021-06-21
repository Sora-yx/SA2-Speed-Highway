#include "pch.h"

CollisionData signBCol = { 0, (CollisionShapes)0x3, 0x77, 0xE0, 0x400, {0.0, 0.0, -1.5}, 25.0, 15.0, 1.5, 0.0, 0, 0, 0 };
static ModelInfo* SH_signB[2];

static NJS_TEXNAME signBtexid0[3] = { {(char*)"post01", 0, 0}, { (char*)"ref_red", 0, 0 }, { (char*)"Tokei3", 0, 0 } };
static NJS_TEXLIST signBtexList0 = { arrayptrandlength(signBtexid0, Uint32) };

static NJS_TEXNAME signBtexid1[3] = { {(char*)"post07", 0, 0}, { (char*)"ref_red", 0, 0 }, { (char*)"Tokei3", 0, 0 } }; 
static NJS_TEXLIST signBtexList1 = { arrayptrandlength(signBtexid1, Uint32) };

static NJS_TEXNAME signBtexid2[3] = { {(char*)"poster2", 0, 0}, { (char*)"ref_red", 0, 0 }, { (char*)"Tokei3", 0, 0 } };
static NJS_TEXLIST signBtexList2 = { arrayptrandlength(signBtexid2, Uint32) };

static NJS_TEXNAME signBtexid3[3] = { {(char*)"poster3", 0, 0}, { (char*)"ref_red", 0, 0 }, { (char*)"Tokei3", 0, 0 } };
static NJS_TEXLIST signBtexList3 = { arrayptrandlength(signBtexid3, Uint32) };

static NJS_TEXNAME signBtexid4[3] = { {(char*)"poster4", 0, 0}, { (char*)"ref_red", 0, 0 }, { (char*)"Tokei3", 0, 0 } };  
static NJS_TEXLIST signBtexList4 = { arrayptrandlength(signBtexid4, Uint32) };

NJS_TEXLIST signBtexListArray[5] = {
	signBtexList0,
	signBtexList1,
	signBtexList2,
	signBtexList3,
	signBtexList4,
};


void CheckSignBTexlist(ObjectMaster* a1)
{
	EntityData1* data = a1->Data1.Entity;
	double x = data->Scale.x;

	if (x >= 10.0)
	{
		if (x >= 20.0)
		{
			if (x >= 30.0)
			{
				data->Index = 3;

				if (x >= 40.0)
					data->Index = 4;
			}
			else
			{
				data->Index = 2;
			}
		}
		else
		{
			data->Index = 1;
		}
	}
	else
	{
		data->Index = 0;
	}
}


void __cdecl signbChild_Display(ObjectMaster* a1)
{
	EntityData1* data; // esi
	data = a1->Data1.Entity;
	DoThatThingWhereYouGetCloseAndItLightsUp(data, 8u);
	njSetTexture(&signBtexListArray[data->Index]);
	njPushMatrix(0);
	njTranslateV(0, &data->Position);
	njRotateZXY(&data->Rotation);
	DrawObject((NJS_OBJECT*)a1->field_4C);
	njPopMatrix(1u);
	ResetMaterialColorOffset();
}

void signB_ApplyPosScale(EntityData1* data, EntityData1* parentData) {
	if ((parentData->Status & 0x100) == 0)
	{
		return;
	}
	data->Position.x += parentData->Scale.x;
	data->Position.z += parentData->Scale.z;

	data->Position.x -= parentData->Scale.x;
	data->Position.z -= parentData->Scale.z;
}

void __cdecl signbChild(ObjectMaster* a1)
{
	EntityData1* data; // esi
	EntityData1* parentData; // edi
	__int16 statusParent; // ax
	double v4; // st7
	int v5; // eax
	Angle v6; // edx

	data = a1->Data1.Entity;
	parentData = a1->Parent->Data1.Entity;
	if (!ClipSetObject(a1) && (unsigned int)data->Action <= 5)
	{
		switch (data->Action)
		{
		case 0:
			data->Action = 1;
			a1->field_4C = SH_signB[0]->getmodel();
			data->Index = parentData->Index;
			a1->DeleteSub = j_DeleteChildObjects;
			a1->DisplaySub = signbChild_Display;
			break;
		case 1:

			statusParent = parentData->Status;
			if ((statusParent & 0x200) == 0)
			{
				signB_ApplyPosScale(data, parentData);
				return;
			}
			data->Action = 3;
			a1->field_4C = SH_signB[1]->getmodel(); //broken model

			break;
		case 3:
			statusParent = parentData->Status;
			if ((statusParent & 0x400) != 0)
			{
				v4 = data->Position.x;
				data->Action = 5;
				data->Scale.x = (v4 - MainCharObj1[0]->Position.x) * 0.25;
				data->Scale.z = (data->Position.z - MainCharObj1[0]->Position.z) * 0.25;
				v5 = rand();
				data->Scale.y = (double)v5 * 0.000030517578 + 0.40000001 + (double)v5 * 0.000030517578 + 0.40000001;
				data->Rotation.x = (unsigned __int16)(unsigned __int64)((double)rand() * 0.000030517578 * 65536.0);
				data->Rotation.y = (unsigned __int16)(unsigned __int64)((double)rand() * 0.000030517578 * 65536.0);
				data->Rotation.z = (unsigned __int16)(unsigned __int64)((double)rand() * 0.000030517578 * 65536.0);
			}
			else
			{
				signB_ApplyPosScale(data, parentData);
			}
			break;
		case 5:
			data->Scale.y -= 0.1;

			njAddVector(&data->Position, &data->Scale);
			data->Rotation.x += 4096;
			data->Rotation.z += 592;

			break;
		default:
			return;
		}
	}
}

void __cdecl OSignb(ObjectMaster* obj)
{
	EntityData1* data; // esi
	double v2; // st7
	Angle v3; // eax
	__int16 v5; // ax
	CollisionInfo* v6; // ecx
	CollisionInfo* v7; // ecx
	__int16 v8; // ax
	__int16 v9; // ax
	char nextAction; // al
	double v11; // st7

	data = obj->Data1.Entity;

	if (ClipSetObject(obj))
		return;

	switch (data->Action)
	{
	case 0:
		data->Action = 1;
		data->Rotation.z = 0;
		data->Rotation.x = 0;
		data->Position.z -= 1.5;
		CheckSignBTexlist(obj);
		InitCollision(obj, &signBCol, 1, 4u);
		obj->DeleteSub = j_DeleteChildObjects;
		LoadChildObject(LoadObj_Data1, signbChild, obj);
		// DoObjectThing(&stru_26B2BE8, obj);
		break;
	case 1:
		v5 = data->Status;
		data->NextAction = 0;
		if ((data->Status & 0x900) != 0)
		{
			data->Status = v5 & 0xFEFF;
			AddToCollisionList(obj);
		}
		else
		{
			if ((data->Status & 4) != 0)
			{
				v6 = data->Collision;
				if ((v6->Flag & 1) != 0)
				{
					v7 = v6->CollidingObject;
					if (!v7->Id)
					{
						if ((v5 & 0x400) != 0)
						{
							data->Action = 5;
							v8 = v5 | 0x800;
						}
						else
						{
							v9 = v5 | 0x100;
							data->Action = 2;
							data->Status = v9;
							if ((v9 & 0x200) != 0)
							{
								v8 = v9 | 0x400;
							}
							else
							{
								v8 = v9 | 0x200;
							}
						}
						data->Status = v8;
						return;
						// PlaySound(v12, 0, 0, 0);
					}
				}
			}
			AddToCollisionList(obj);
		}
		break;
	case 2:
		nextAction = data->NextAction;
		data->NextAction = nextAction + 1;
		v11 = 0.0f;

		if (!nextAction || -nextAction == 7) {
			v11 = 0.1f;
		}
		else if (nextAction == 1 || nextAction == 2 || nextAction == 5 || nextAction == 6)
		{
			v11 = 0.2f;
		}
		else if (nextAction == 3 || nextAction == 4) {
			v11 = 0.25f;
		}
		else if (nextAction == 8) {
			data->Action = 1;
			v11 = 0.0f;
		}

		data->Scale.x = (data->Position.x - MainCharObj1[0]->Position.x) * v11;
		data->Scale.z = (data->Position.z - MainCharObj1[0]->Position.z) * v11;

		AddToCollisionList(obj);
		break;
	default:
		j_DeleteChildObjects(obj);
		break;
	}
}

void LoadSignBModels() {
	SH_signB[0] = LoadMDL("SH-signB0", ModelFormat_Chunk);
	SH_signB[1] = LoadMDL("SH-signB1", ModelFormat_Chunk);


	signBtexList0.textures[0] = highwayObj2_TEXLIST.textures[39];
	signBtexList0.textures[1] = highwayObj2_TEXLIST.textures[40];
	signBtexList0.textures[2] = highwayObj2_TEXLIST.textures[41];

	signBtexList1.textures[0] = highwayObj2_TEXLIST.textures[42];
	signBtexList1.textures[1] = highwayObj2_TEXLIST.textures[43];
	signBtexList1.textures[2] = highwayObj2_TEXLIST.textures[44];

	signBtexList2.textures[0] = highwayObj2_TEXLIST.textures[45];
	signBtexList2.textures[1] = highwayObj2_TEXLIST.textures[46];
	signBtexList2.textures[2] = highwayObj2_TEXLIST.textures[47];

	signBtexList3.textures[0] = highwayObj2_TEXLIST.textures[48];
	signBtexList3.textures[1] = highwayObj2_TEXLIST.textures[49];
	signBtexList3.textures[2] = highwayObj2_TEXLIST.textures[50];

	signBtexList4.textures[0] = highwayObj2_TEXLIST.textures[51];
	signBtexList4.textures[1] = highwayObj2_TEXLIST.textures[52];
	signBtexList4.textures[2] = highwayObj2_TEXLIST.textures[53];
}