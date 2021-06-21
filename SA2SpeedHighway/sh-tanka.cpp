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

void Tank_ResetRotationAndScale(EntityData1* data) {
	data->Scale.z = 1.0;
	data->Scale.y = 1.0;
	data->Scale.x = 1.0;
	data->Rotation.z = 0;
	data->Rotation.x = 0;
	return;
}

void Tank_ApplyCalcPos(EntityData1* data, EntityData1* parentData) {
	data->Position.x += parentData->Scale.x;
	data->Position.z += parentData->Scale.z;
	data->Position.x -= parentData->Scale.x;
	data->Position.z -= parentData->Scale.z;
	return;
}

void __cdecl tank_display(ObjectMaster* obj)
{
	EntityData1*  data = obj->Data1.Entity;

	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrix(0);
	njTranslateV(0, &data->Position);
	njRotateZXY(&data->Rotation);
	njScaleV_(&data->Scale);
	DrawObject((NJS_OBJECT*)obj->field_4C);
	njPopMatrix(1u);
}

void Tanka_Brokenpart(ObjectMaster* obj)
{
	EntityData1* data; // esi
	char nextAction; // al
	double calcScaleY; // st7

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
			calcScaleY = data->Scale.y - 0.059999999;
			data->Rotation.x += 1280;
			data->Scale.y = calcScaleY;
			data->Rotation.z += 1280;
			data->Position.x += data->Scale.x;
			data->Rotation.y += 1280;
			data->Position.y += calcScaleY;
			data->Position.z += data->Scale.z;
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
	char index; // al

	EntityData1* data = obj->Data1.Entity;
	EntityData1* parentData = obj->Parent->Data1.Entity;
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
					Tank_ApplyCalcPos(data, parentData);
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
			obj->DeleteSub = j_DeleteChildObjects;
		}
	}
}

void __cdecl execTankBody(ObjectMaster* obj)
{

	EntityData1* data = obj->Data1.Entity;
	EntityData1* parentData = obj->Parent->Data1.Entity;
	char indexParent;

	if (data->Action)
	{
		if (data->Action == 1)
		{
			indexParent = parentData->Index;
			if ((indexParent & 0x10) != 0)
			{
				DeleteObject_(obj);
			}
			else if ((indexParent & 8) != 0)
			{
				Tank_ApplyCalcPos(data, parentData);
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
		Tank_ResetRotationAndScale(data);
		obj->DeleteSub = j_DeleteChildObjects;
		obj->DisplaySub = tank_display;
	}
}

void __cdecl execTankBase(ObjectMaster* obj)
{

	char index; // cl
	EntityData1* data = obj->Data1.Entity;
	EntityData1* parentData = obj->Parent->Data1.Entity;

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

		Tank_ResetRotationAndScale(data);
		obj->DeleteSub = j_DeleteChildObjects;
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
		index = parentData->Index;
		if ((index & 0x40) != 0)
		{
			data->Action = 4;
		}
		else
		{
			if ((index & 8) == 0)
			{
				data->Action = 1;
			}
		}

		Tank_ApplyCalcPos(data, parentData);
		break;
	default:
		DeleteChildObjects(obj);
		DeleteFunc_DynCol(obj);
		break;
	}
}

void __cdecl tankladder_Main(ObjectMaster* obj)
{
	int v5; // eax

	EntityData1* data = obj->Data1.Entity;
	EntityData1* parentData = obj->Parent->Data1.Entity;
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
					Tank_ApplyCalcPos(data, parentData);
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
			if (data->Scale.x >= 10.0)
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

			Tank_ResetRotationAndScale(data);
			obj->DisplaySub = tank_display;
			obj->DeleteSub = j_DeleteChildObjects;
		}
	}
}

void setTankLadder(ObjectMaster* obj)
{
	EntityData1* data; // esi
	ObjectMaster* child; // eax
	EntityData1* childData; // edi

	Vector3 a2; // [esp+8h] [ebp-18h] BYREF

	data = obj->Data1.Entity;
	child = LoadChildObject(LoadObj_Data1, tankladder_Main, obj);
	if (child)
	{
		obj->Child = child;
		childData = child->Data1.Entity;
		if (data->Scale.x >= 10.0)
		{
			a2.x = 9.0;
			if (data->Scale.x >= 20.0)
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

		njGetTranslation(CURRENT_MATRIX, &a2);
		njPopMatrix(1u);
		childData->Position.x = a2.x + data->Position.x;
		childData->Position.y = a2.y + data->Position.y;

		childData->Rotation.z = 0;
		childData->Rotation.x = 0;
		childData->Position.z += a2.z;
		childData->Rotation.y = data->Rotation.y;
		childData->Scale.x = data->Scale.x;
	}
}

void TankDoIndexCollisionStuff(char nextAction, char v9, double v11, char index, char v15, ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;

	if (nextAction == 0 || nextAction == 7)
	{
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
		index = v9 & 0xF7;
		data->Index = index;
		if ((index & 0x20) != 0)
		{
			data->Index = index | 0x40;
			data->Action = 4;
			/*sub_4CAF80(v21, a2, v23, 1.0);
			sub_477D90(data->Rotation.z, &data->Position);*/

			if ((data->Index & 1) != 0)
			{
				InitCollision(obj, &tankaCol[2], 1, 4u);
			}
			else if ((data->Index & 2) != 0)
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
			if ((index & 0x10) != 0)
			{
				data->Action = 1;
				v15 = index | 0x20;
			}
			else
			{
				v15 = index | 0x10;
				data->Action = 3;
			}
			data->Index = v15;
		}
	}
	else {
		v11 = 0.0f;
	}

	return;
}

void __cdecl OTanka(ObjectMaster* obj)
{
	EntityData1* data; // esi
	Angle v2; // eax
	CollisionInfo* v5; // eax
	CollisionInfo* v6; // eax
	char v7; // cl
	float* v8; // ebp
	char v9; // al
	char v10; // cl
	double v11 = 0.0f; // st7
	char v12 = 0; // al
	double v13; // st7
	char v14; // al
	char v15 = 0; // al
	float v16; // ecx
	float v17; // eax
	int v18; // eax
	int v19; // ebx
	unsigned __int8 rotZ; // [esp-8h] [ebp-30h]
	float a2; // [esp+0h] [ebp-28h]
	float v23; // [esp+4h] [ebp-24h]
	NJS_VECTOR a1; // [esp+1Ch] [ebp-Ch] BYREF

	data = obj->Data1.Entity;
	if (!ClipSetObject(obj))
	{
		switch (data->Action)
		{
		case 0:
			data->Action = 1;
			data->Index = 0;
			if (data->Scale.x >= 10.0)
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
			obj->DeleteSub = j_DeleteChildObjects;
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

			data->NextAction = 0;
			if ((data->Status & 4) != 0)
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
				TankDoIndexCollisionStuff(v10, v9, v11, v12, v15, obj);
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
			v18 = (unsigned __int16)(0x4000 - (unsigned __int64)(atan2( MainCharObj1[0]->Position.z - data->Position.z,
					MainCharObj1[0]->Position.x - data->Position.x) * 65536.0 * 0.1591549762031479) - data->Rotation.y);
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

	return;
}