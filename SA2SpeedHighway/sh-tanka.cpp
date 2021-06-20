#include "pch.h"

//ALL THIS GIANT MESS FOR A STUPID TRASH THAT YOU CAN BREAK, WTF.

static ModelInfo* SH_Pipe;
static ModelInfo* SH_TankA[3];
static ModelInfo* SH_TankABroken[4];
static ModelInfo* SH_TankB[3];
static ModelInfo* SH_TankBBroken[4];
static ModelInfo* SH_TankC[4];
static ModelInfo* SH_TankCBroken[4];


CollisionData tankaCol[] = {

	{0, (CollisionShapes)1, 0x77, 0xE0, 0x2400, {0.0, 8.1199999, 0.0}, 5.0, 8.1199999, 0.0, 0.0, 0, 0, 0 },
	{0, (CollisionShapes)1, 0x77, 0xE0, 0x2400, {0.0, 9.0, 0.0}, 2.0, 9.0, 0.0, 0.0, 0, 0, 0},
	{0, (CollisionShapes)1, 0x77, 0xEC, 0x2000, {0.0, 2.5, 0.0}, 5.0, 2.5, 0.0, 0.0, 0, 0, 0},
	{0, (CollisionShapes)0, 0x77, 0xE0, 0x2400, {0.0, 11.0, 0.0}, 9.0, 0.0, 0.0, 0.0, 0, 0, 0},
	{0, (CollisionShapes)1, 0x77, 0xE0, 0x2400, {0.0, 3.25, 0.0}, 6.75, 3.25, 0.0, 0.0, 0, 0, 0},
	{0, (CollisionShapes)1, 0x77, 0xEC, 0x2000, {0.0, 3.25, 0.0}, 6.75, 3.25, 0.0, 0.0, 0, 0, 0},
	{0, (CollisionShapes)1, 0x77, 0xE0, 0x2400, {0.0, 9.75, 0.0}, 6.0, 9.75, 0.0, 0.0, 0, 0, 0},
	{0, (CollisionShapes)1, 0x77, 0xE0, 0x2400, {0.0, 10.5, 0.0}, 3.0, 10.5, 0.0, 0.0, 0, 0, 0},
	{0, (CollisionShapes)1, 0x77, 0xE0, 0x2400, {8.0, 6.5, 0.0}, 0.80000001, 6.5, 0.0, 0.0, 0, 0, 0},
	{0, (CollisionShapes)1, 0x77, 0xEC, 0x2000, {0.0, 1.74, 0.0}, 4.5799999, 1.74, 0.0, 0.0, 0, 0, 0},
};

enum tankModel {
	tankBase,
	tankBody,
	tankLadder,
	tankDuct
};

void __cdecl tank_display(ObjectMaster* obj)
{
	EntityData1* data; // esi
	Angle v2; // eax
	Angle v3; // eax
	Angle v4; // eax

	data = obj->Data1.Entity;

	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrix(0);
	njTranslateV(0, &data->Position);
	njRotateZXY(&data->Rotation);
	njScaleV_(&data->Scale);
	DrawObject((NJS_OBJECT*)obj->field_4C); ; //weird pipe thing
	njPopMatrix(1u);
}

void Tanka_Brokenpart(ObjectMaster* obj)
{
	EntityData1* data; // esi
	char nextAction; // al
	double v3; // st7
	Angle v4; // edx
	int v5; // ecx
	int v6; // ecx

	data = obj->Data1.Entity;
	nextAction = data->NextAction;
	if (nextAction)
	{
		if (nextAction == 1)
		{
			if (ClipSetObject(obj))
			{
				++data->NextAction;
			}
			v3 = data->Scale.y - 0.059999999;
			v4 = data->Rotation.y;
			v5 = data->Rotation.x + 1280;
			data->Scale.y = v3;
			data->Rotation.x = v5;
			v6 = data->Rotation.z + 1280;
			data->Position.x = data->Scale.x + data->Position.x;
			data->Rotation.y = v4 + 1280;
			data->Rotation.z = v6;
			data->Position.y = v3 + data->Position.y;
			data->Position.z = data->Scale.z + data->Position.z;
		}
		else
		{
			++data->Action;
		}
	}
	else
	{
		data->NextAction = 1;
		data->Scale.x = (double)rand() * 0.000030517578 - 0.5;
		data->Scale.y = (double)rand() * 0.000030517578 + 0.40000001;
		data->Scale.z = (double)rand() * 0.000030517578 - 0.5;
	}
}

void __cdecl execTankDuct(ObjectMaster* obj)
{

	EntityData1* parentData; // ebx
	char index; // al

	EntityData1* data = obj->Data1.Entity;
	parentData = obj->Parent->Data1.Entity;
	if (!ClipSetObject(obj))
	{
		if (data->Action)
		{
			if (data->Action == 1)
			{
				index = parentData->Index;
				if ((index & 0x40) != 0)
				{
					Tanka_Brokenpart(obj);
				}
				else if ((index & 8) != 0)
				{

					data->Position.x = data->Position.x + parentData->Scale.x;
					data->Position.z = data->Position.z + parentData->Scale.z;
					data->Position.x = data->Position.x - parentData->Scale.x;
					data->Position.z = data->Position.z - parentData->Scale.z;
				}
				else
				{
					DoThatThingWhereYouGetCloseAndItLightsUp(data, 8u);
					ResetMaterialColorOffset();
				}
			}
		}
		else
		{
			data->Action = 1;
			data->Scale.z = 0.80000001;
			data->Scale.y = 0.80000001;
			data->Scale.x = 0.80000001;
			data->Rotation.z = 0;
			data->Rotation.x = 0;
			obj->field_4C = SH_TankC[tankDuct]->getmodel();
			obj->DisplaySub = tank_display;
			obj->DeleteSub = DeleteFunc_DynCol;
		}
	}
}

void __cdecl execTankBody(ObjectMaster* obj)
{
	EntityData1* v1; // esi
	EntityData1* v2; // edi
	EntityData1* data; // eax
	EntityData1* parentData; // edx
	char index; // dl
	char indexParent; // dl

	data = obj->Data1.Entity;
	parentData = obj->Parent->Data1.Entity;
	if (data->Action)
	{
		if (data->Action == 1)
		{
			index = parentData->Index;
			if ((index & 0x10) != 0)
			{
				DeleteObject_(obj);
			}
			else if ((index & 8) != 0)
			{
				v1 = obj->Data1.Entity;
				v2 = obj->Parent->Data1.Entity;
				v1->Position.x = v1->Position.x + v2->Scale.x;
				v1->Position.z = v1->Position.z + v2->Scale.z;
				v1->Position.x = v1->Position.x - v2->Scale.x;
				v1->Position.z = v1->Position.z - v2->Scale.z;
			}
			else
			{
				DoThatThingWhereYouGetCloseAndItLightsUp(data, 8u);
				ResetMaterialColorOffset();
			}
		}
	}
	else
	{
		data->Action = 1;
		indexParent = parentData->Index;
		if ((indexParent & 1) != 0)
		{
			obj->field_4C = SH_TankA[tankBody]->getmodel();
		}
		else if ((indexParent & 2) != 0)
		{
			obj->field_4C = SH_TankB[tankBody]->getmodel();
		}
		else
		{
			obj->field_4C = SH_TankC[tankBody]->getmodel();
		}
		data->Scale.z = 1.0;
		data->Scale.y = 1.0;
		data->Scale.x = 1.0;
		data->Rotation.z = 0;
		data->Rotation.x = 0;
		obj->DeleteSub = DeleteFunc_DynCol;
		obj->DisplaySub = tank_display;
	}
}

void __cdecl execTankBase(ObjectMaster* obj)
{
	EntityData1* data1; // esi
	EntityData1* parentData1; // edi
	EntityData1* data; // eax
	EntityData1* parentData; // ecx
	char index; // cl
	char index2; // cl
	ObjectMaster* v7; // eax
	EntityData1* v8; // edi

	data = obj->Data1.Entity;
	parentData = obj->Parent->Data1.Entity;
	switch (data->Action)
	{
	case 0:
		data->Action = 1;
		index = parentData->Index;
		if ((index & 1) != 0)
		{
			obj->field_4C = SH_TankA[tankBase]->getmodel();
		}
		else if ((index & 2) != 0)
		{
			obj->field_4C = SH_TankB[tankBase]->getmodel();
		}
		else
		{
			obj->field_4C = SH_TankC[tankBase]->getmodel();
		}
		data->Scale.z = 1.0;
		data->Scale.y = 1.0;
		data->Scale.x = 1.0;
		data->Rotation.z = 0;
		data->Rotation.x = 0;
		obj->DeleteSub = DeleteFunc_DynCol;
		obj->DisplaySub = tank_display;
		break;
	case 1:
		if ((parentData->Index & 8) != 0)
		{
			data->Action = 2;
		}
		DoThatThingWhereYouGetCloseAndItLightsUp(data, 8u);
		ResetMaterialColorOffset();
		break;
	case 2:
		index2 = parentData->Index;
		if ((index2 & 0x40) != 0)
		{
			data->Action = 4;
			v7 = obj;
		}
		else
		{
			if ((index2 & 8) == 0)
			{
				data->Action = 1;
			}
			v7 = obj;
		}
		data1 = v7->Data1.Entity;
		parentData1 = v7->Parent->Data1.Entity;
		data1->Position.x = data1->Position.x + parentData1->Scale.x;
		data1->Position.z = data1->Position.z + parentData1->Scale.z;
		data1->Position.x = data1->Position.x - parentData1->Scale.x;
		data1->Position.z = data1->Position.z - parentData1->Scale.z;
		break;
	default:
		DeleteChildObjects(obj);
		v8 = obj->Data1.Entity;
		DeleteFunc_DynCol(obj);
		break;
	}
}

void __cdecl tankladder_Main(ObjectMaster* obj)
{
	EntityData1* v1; // esi
	EntityData1* v2; // edi
	EntityData1* data; // esi
	EntityData1* parentData; // ebx
	int v5; // eax
	double scaleX; // st7

	data = obj->Data1.Entity;
	parentData = obj->Parent->Data1.Entity;
	if (!ClipSetObject(obj))
	{
		if (data->Action)
		{
			if (data->Action == 1)
			{
				v5 = (unsigned __int8)parentData->Index;
				if ((v5 & 0x40) != 0)
				{
					Tanka_Brokenpart(obj);
				}
				else if ((v5 & 8) != 0)
				{
					v1 = obj->Data1.Entity;
					v2 = obj->Parent->Data1.Entity;
					v1->Position.x = v1->Position.x + v2->Scale.x;
					v1->Position.z = v1->Position.z + v2->Scale.z;
					v1->Position.x = v1->Position.x - v2->Scale.x;
					v1->Position.z = v1->Position.z - v2->Scale.z;
				}
				else
				{
					DoThatThingWhereYouGetCloseAndItLightsUp(data, 8u);
					ResetMaterialColorOffset();
				}
			}
		}
		else
		{
			scaleX = data->Scale.x;
			data->Action = 1;
			if (scaleX >= 10.0)
			{
				if (data->Scale.x >= 20.0)
				{
					obj->field_4C = SH_TankC[tankLadder]->getmodel();
				}
				else
				{
					obj->field_4C = SH_TankB[tankLadder]->getmodel();
				}
			}
			else
			{
				obj->field_4C = SH_TankA[tankLadder]->getmodel();
			}
			data->Scale.z = 1.0;
			data->Scale.y = 1.0;
			data->Scale.x = 1.0;
			data->Rotation.z = 0;
			data->Rotation.x = 0;
			obj->DisplaySub = tank_display;
			obj->DeleteSub = DeleteFunc_DynCol;
		}
	}
}

void setTankLadder(ObjectMaster* obj)
{
	EntityData1* data; // esi
	ObjectMaster* child; // eax
	EntityData1* childData; // edi
	double v5; // st7
	Angle v6; // eax
	Angle v7; // eax
	Angle v8; // eax
	double v9; // st7
	Vector3 a2; // [esp+8h] [ebp-18h] BYREF
	Vector3 a3; // [esp+14h] [ebp-Ch] BYREF

	data = obj->Data1.Entity;
	child = LoadChildObject(LoadObj_Data1, tankladder_Main, obj);
	if (child)
	{
		obj->Child = child;
		childData = child->Data1.Entity;
		if (data->Scale.x >= 10.0)
		{
			v5 = data->Scale.x;
			a2.x = 9.0;
			if (v5 >= 20.0)
			{
				a2.x = -7.0;
			}
		}
		else
		{
			a2.x = 6.0;
		}
		a2.y = 8.0;
		a2.z = 0.0;
		njPushMatrix(_nj_unit_matrix_);
		njRotateZXY(&data->Rotation),

		njGetTranslation(CURRENT_MATRIX, &a3);
		njPopMatrix(1u);
		childData->Position.x = a3.x + data->Position.x;
		childData->Position.y = a3.y + data->Position.y;
		v9 = a3.z + data->Position.z;
		childData->Rotation.z = 0;
		childData->Rotation.x = 0;
		childData->Position.z = v9;
		childData->Rotation.y = data->Rotation.y;
		childData->Scale.x = data->Scale.x;
	}
}

void __cdecl OTanka(ObjectMaster* obj)
{
	EntityData1* data; // esi
	Angle v2; // eax
	double scaleX; // st7
	int v4; // eax
	CollisionInfo* v5; // eax
	CollisionInfo* v6; // eax
	char v7; // cl
	float* v8; // ebp
	char v9; // al
	char v10; // cl
	double v11; // st7
	char v12; // al
	double v13; // st7
	char v14; // al
	char v15; // al
	float v16; // ecx
	float v17; // eax
	int v18; // eax
	int v19; // ebx
	unsigned __int8 rotZ; // [esp-8h] [ebp-30h]
	float v21; // [esp-4h] [ebp-2Ch]
	float a2; // [esp+0h] [ebp-28h]
	float v23; // [esp+4h] [ebp-24h]
	NJS_VECTOR a1; // [esp+1Ch] [ebp-Ch] BYREF

	data = obj->Data1.Entity;
	if (!ClipSetObject(obj))
	{

		switch (data->Action)
		{
		case 0:
			scaleX = data->Scale.x;
			data->Action = 1;
			data->Index = 0;
			if (scaleX >= 10.0)
			{
				if (data->Scale.x >= 20.0)
				{
					data->Index = 4;
					InitCollision(obj, &tankaCol[6], 3, 4u);
				}
				else
				{
					data->Index = 2;
					InitCollision(obj, &tankaCol[3], 2, 4u);
				}
			}
			else
			{
				data->Index = 1;
				InitCollision(obj, tankaCol, 2, 4u);
			}
			obj->DeleteSub = DeleteFunc_DynCol;
			data->Rotation.x = 0;
			LoadChildObject(LoadObj_Data1, execTankBase, obj);
			setTankLadder(obj);
			if (obj->Data1.Entity->Scale.x >= 20.0)
			{
				LoadChildObject(LoadObj_Data1, execTankDuct, obj);
			}
			LoadChildObject(LoadObj_Data1, execTankBody, obj);
			rotZ = data->Rotation.z;
			data->Scale.x = 1.0;
			//KnuxEmeraldStuff(rotZ, &data->Position);
			break;
		case 1:

			v4 = LOBYTE(data->Status);
			data->NextAction = 0;
			if ((v4 & 4) != 0)
			{
				v5 = data->Collision;
				if ((v5->Flag & 1) != 0)
				{
					v6 = v5->CollidingObject;
					if (!v6->Id)
					{
						v7 = data->Index | 8;
						data->Action = 2;
						data->Index = v7;
					}
				}
			}
			AddToCollisionList(obj);

			//KnuxEmeraldStuff(data->Rotation.z, &data->Position);

			break;
		case 2:
			v8 = &data->Position.x;
			//KnuxEmeraldStuff(data->Rotation.z, &data->Position);
			v9 = data->Index;
			if ((v9 & 8) != 0)
			{
				v10 = data->NextAction;
				data->NextAction = v10 + 1;
				switch (v10)
				{
				case 0:
				case 7:
					v11 = 0.1;
					break;
				case 1:
				case 2:
				case 5:
				case 6:
					v11 = 0.2;
					break;
				case 3:
				case 4:
					v11 = 0.25;
					break;
				case 8:
					v12 = v9 & 0xF7;
					data->Index = v12;
					if ((v12 & 0x20) != 0)
					{
						v13 = data->Position.y + 5.0;
						v23 = data->Position.z;
						data->Index = v12 | 0x40;
						a2 = v13;
						v21 = *v8;
						data->Action = 4;
						/*sub_4CAF80(v21, a2, v23, 1.0);
						sub_477D90(data->Rotation.z, &data->Position);*/
						v14 = data->Index;
						if ((v14 & 1) != 0)
						{
							InitCollision(obj, &tankaCol[2], 1, 4u);
						}
						else if ((v14 & 2) != 0)
						{
							InitCollision(obj, &tankaCol[5], 1, 4u);
						}
						else
						{
							InitCollision(obj, &tankaCol[9], 1, 4u);
						}
					}
					else
					{
						if ((v12 & 0x10) != 0)
						{
							data->Action = 1;
							v15 = v12 | 0x20;
						}
						else
						{
							v15 = v12 | 0x10;
							data->Action = 3;
						}
						data->Index = v15;
					}
					goto LABEL_43;
				default:
				LABEL_43:
					v11 = 0.0;
					break;
				}
				data->Scale.x = (*v8 - MainCharObj1[0]->Position.x) * v11;
				data->Scale.z = (data->Position.z - MainCharObj1[0]->Position.z) * v11;
			}
			else
			{
				data->Action = 1;
			}
			v16 = *v8;
			v17 = data->Position.z;
			a1.y = data->Position.y;
			a1.x = v16;
			a1.z = v17;
			njAddVector(&a1, &MainCharObj1[0]->Position);
			a1.x = a1.x * 0.5;
			a1.z = a1.z * 0.5;
			a1.y = a1.y * 0.5 + 5.0;
			//TrashBreakParticles((int)&a1, 1065353216);
			AddToCollisionList(obj);
			break;
		case 3:
			data->Action = 1;
			v18 = (unsigned __int16)(0x4000
				- (unsigned __int64)(atan2(
					MainCharObj1[0]->Position.z - data->Position.z,
					MainCharObj1[0]->Position.x - data->Position.x)
					* 65536.0
					* 0.1591549762031479)
				- data->Rotation.y);
			if (v18 <= 60074)
			{
				if (v18 <= 49152)
				{
					if (v18 <= 38229)
					{
						if (v18 <= 27306)
						{
							if (v18 <= 0x4000)
							{
								v19 = v18 <= 5461 ? 0 : 0x2AAA;
							}
							else
							{
								v19 = 21845;
							}
						}
						else
						{
							v19 = 0x8000;
						}
					}
					else
					{
						v19 = 43690;
					}
				}
				else
				{
					v19 = 54613;
				}
			}
			else
			{
				v19 = 0;
			}
			data->Rotation.y += v19;
			///sub_61A080(obj); //missing functions which load broken trash with DoObjectThing, lol
			data->Rotation.y -= v19;
			AddToCollisionList(obj);
			//KnuxEmeraldStuff(data->Rotation.z, &data->Position);
			break;
		case 4:
			AddToCollisionList(obj);
			break;
		default:
			return;
		}
	}
}

void LoadTrashModels() {
	for (size_t i = 0; i < LengthOfArray(SH_TankA); i++) {
		std::string str = "sh-tankA" + std::to_string(i);
		SH_TankA[i] = LoadMDL(str.c_str(), ModelFormat_Chunk);

		std::string strB = "sh-tankB" + std::to_string(i);
		SH_TankB[i] = LoadMDL(strB.c_str(), ModelFormat_Chunk);
	}

	for (size_t i = 0; i < LengthOfArray(SH_TankABroken); i++) {

		std::string str1 = "sh-tankC" + std::to_string(i);
		SH_TankC[i] = LoadMDL(str1.c_str(), ModelFormat_Chunk);

		std::string str2 = "sh-tankABroken" + std::to_string(i);
		SH_TankABroken[i] = LoadMDL(str2.c_str(), ModelFormat_Chunk);

		std::string str3 = "sh-tankBBroken" + std::to_string(i);
		SH_TankBBroken[i] = LoadMDL(str3.c_str(), ModelFormat_Chunk);

		std::string str4 = "sh-tankCBroken" + std::to_string(i);
		SH_TankCBroken[i] = LoadMDL(str4.c_str(), ModelFormat_Chunk);
	}

}