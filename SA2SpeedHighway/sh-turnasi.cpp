#include "pch.h"

static ModelInfo* TurnAsi;
extern NJS_TEXLIST highwayObj_TEXLIST;

CollisionData TurnAsiCol[] = {
	{ 0, (CollisionShapes)0x6, 0x77, 0, 0, {0.0, 15.0, 0.0}, 7.0, 7.0, 0.0, 0.0, 0, 0, 0 },
	{ 0, (CollisionShapes)0x3, 0x77, 0xE0, 0x2000, {0.0, -61.0, 0.0}, 34.5, 2.5, 17.0, 0.0, 0, 0, 0},
	{ 0, (CollisionShapes)0x3, 0x77, 0xE0, 0x2000, {0.0, -53.0, 0.0}, 34.5, 4.0, 4.0, 0.0, 0, 0, 0},
	{ 0, (CollisionShapes)0x3, 0x77, 0xE0, 0x2000, {33.0, -74.0, 0.0}, 2.5, 14.0, 14.0, 0.0, 0, 0, 0 },
	{ 0, (CollisionShapes)0x3, 0x77, 0xE0, 0x2000, {-33.0, -74.0, 0.0}, 2.5, 14.0, 14.0, 0.0, 0, 0, 0 },
	{ 0, (CollisionShapes)0x3, 0x77, 0xE0, 0x2000, {0.0, -93.0, 0.0}, 34.5, 6.0, 14.0, 0.0, 0, 0, 0},
	{ 0, (CollisionShapes)0x3, 0x77, 0xE0, 0x2000, {0.0, -74.0, -15.0}, 34.5, 18.0, 6.0, 0.0, 0, 0, 0},
};


CollisionData AsiaChildCol = { 0, (CollisionShapes)0x3, 0, 0xE0, 0, {0.0, 0.0, 5.0}, 40.5, 14.0, 5.0, 0.0, 0, 0, 0 };

//broken
void AsiChild_CalcColPos(ObjectMaster* a1)
{
	EntityData1* data; // esi
	ObjectMaster* PlayerPtr; // eax
	CharObj2Base* co2; // ebp
	ObjectMaster* parent; // eax
	EntityData1* dataParent; // edi
	bool scaleValue; // zf
	Angle rotY; // eax
	Angle rotX; // eax
	double v10; // st7
	CollisionInfo* col; // ecx
	unsigned __int16 colFlag; // ax
	long double offset_x; // st6
	long double offset_z; // st6
	EntityData1* dataPlayer; // [esp+8h] [ebp-28h]
	Vector3 vs; // [esp+Ch] [ebp-24h] BYREF
	Vector3 vd; // [esp+18h] [ebp-18h] BYREF
	Vector3 result; // [esp+24h] [ebp-Ch] BYREF

	data = a1->Data1.Entity;
	PlayerPtr = MainCharacter[0];

	if (!PlayerPtr)
		return;

	dataPlayer = PlayerPtr->Data1.Entity;
	co2 = MainCharObj2[0];

	if (!co2)
		return;

	parent = a1->Parent;

	if (!parent)
		return;

	FloatInfo* parRot = new FloatInfo();
	parRot = (FloatInfo*)parent->Data2.Undefined;

	FloatInfo* childRot = new FloatInfo();
	childRot = (FloatInfo*)a1->Data2.Undefined;

	NJS_OBJECT* child = TurnAsi->getmodel()->child;
	NJS_OBJECT* childChild = TurnAsi->getmodel()->child->child;

	dataParent = parent->Data1.Entity;
	scaleValue = (dataParent->Scale.y) == 5.0F;
	dataParent->Index = 0;

	if (scaleValue)
	{
		data->Action = 2;
		data->Scale.y = 10.0;
		dataParent->Scale.y = 0.0;
	}
	else
	{
		vs.x = 0.0;
		vs.y = 0.0;
		vs.z = 0.0;
		njPushMatrix(_nj_unit_matrix_);
		njTranslateSADX(0, dataParent->Position.x, dataParent->Position.y, dataParent->Position.z);
		rotY = dataParent->Rotation.y;
		if (rotY)
		{
			njRotateY(0, (unsigned __int16)rotY);
		}
		rotX = dataParent->Rotation.x;
		if (rotX + data->Rotation.x)
		{
			njRotateX(0, (unsigned __int16)(rotX + LOWORD(data->Rotation.x)));
		}
		njTranslateSADX(0, child->pos[0], child->pos[1], child->pos[2]);
		njTranslateSADX(0, childChild->pos[0], childChild->pos[1], childChild->pos[2]);
		njCalcPointSADX(0, &vs, &vd);
		njPopMatrix(1u);
		data->Position = vd;
		data->Rotation.y = dataParent->Rotation.y;
		if ((dataParent->Scale.z) != 20.0f)
		{
			if ((data->Scale.z) == 10.0f
				|| (result = co2->Speed,
					v10 = njScalor(&result),
					parRot->info01 = v10,
					col = data->Collision,
					colFlag = col->Flag,
					(colFlag & 1) == 0))
			{
				AddToCollisionList(a1);
			}
			else
			{
				col->Flag = colFlag & 0xFFFE;
				dataParent->Index = 10;
				data->Scale.z = 10.0;
				offset_x = dataPlayer->Position.x - data->Position.x;
				data->Scale.x = offset_x;
				if (fabs(offset_x) >= 15.0)
				{
					if (offset_x >= 0.0)
					{
						data->Scale.x = 15.0;
					}
					else
					{
						data->Scale.x = -15.0;
					}
				}
				offset_z = dataPlayer->Position.z - data->Position.z;
				childRot->info01 = offset_z;
				if (fabs(offset_z) >= 7.0)
				{
					if (offset_z >= 0.0)
					{
						childRot->info03 = 7.0f;
					}
					else
					{
						childRot->info03 = -7.0f;
					}
				}
				parRot->info01 = v10;
				AddToCollisionList(a1);
			}
		}
	}
}

void TurnAsi_Child(ObjectMaster* tp)
{
	EntityData1* data; // r31
	unsigned int curAction; // r11
	double v3; // fp12
	CollisionInfo* col; // r11
	FloatInfo* rot = new FloatInfo();

	data = tp->Data1.Entity;
	curAction = data->Action;
	if (data->Action)
	{
		if (curAction == 1)
		{
			AsiChild_CalcColPos(tp);
		}
		else if (curAction < 3)
		{
			v3 = data->Scale.y;
			data->Scale.y = data->Scale.y - (float)1.0;
			if (v3 < 0.0)
			{
				col = data->Collision;
				data->Action = 1;
				data->Scale.y = 10.0;
				col->Flag &= 0xFFFEu;
				data->Scale.z = 0.0;
			}
		}
	}
	else
	{
		tp->Data2.Undefined = rot;
		InitCollision(tp, &AsiaChildCol, 1, 4u);
		data->Action = 1;
	}
}

void Asi_ApplyScaleStuff(EntityData1* dataParent, FloatInfo* parRot) {
	parRot->info03 = 0;
	dataParent->field_6 = 0;
	dataParent->Scale.y = 5.0;
	dataParent->Scale.z = 0.0;
	return;
}


void Asi_DoRotationThing(ObjectMaster* objParent, EntityData1* dataParent)
{
	ObjectMaster* PlayerPTR; // eax
	EntityData1* PlayerData; // ebp
	ObjectMaster* ChildObj; // edi
	double weight; // st7
	unsigned __int16 timerParent; // cx
	double resultParent; // st7
	long double v7; // st7
	long double v8; // st7
	long double v9; // st7
	long double v10; // st7
	Angle parentRotX; // eax
	float parentRotY2; // edx
	double v13; // st7
	float parentRotY; // edx
	double v15; // st7
	long double v16; // st7
	long double v17; // st7
	long double v18; // st7
	double v19; // st7
	Angle v20; // eax
	float parentRotY3; // ecx
	int parentTimer2; // [esp+4h] [ebp-1Ch]
	Vector3 a3; // [esp+8h] [ebp-18h] BYREF
	Vector3 a2; // [esp+14h] [ebp-Ch] BYREF

	PlayerPTR = MainCharacter[0];

	if (!PlayerPTR)
		return;

	PlayerData = PlayerPTR->Data1.Entity;

	if (!MainCharObj2[0])
		return;

	ChildObj = (ObjectMaster*)objParent->field_4C;

	if (!ChildObj)
		return;

	FloatInfo* parRot = new FloatInfo();
	parRot = (FloatInfo*)objParent->Data2.Undefined;

	FloatInfo* childRot = new FloatInfo();
	childRot = (FloatInfo*)ChildObj->Data2.Undefined;

	dataParent->Scale.z = 20.0;
	PlayerData->Position.x = ChildObj->Data1.Entity->Scale.x + ChildObj->Data1.Entity->Position.x;
	PlayerData->Position.y = ChildObj->Data1.Entity->Position.y - 7.5;
	PlayerData->Position.z = ChildObj->Data1.Entity->Position.z;

	if (parRot->info01 < 4.0 && (dataParent->Scale.x) != 5.0)
	{
		weight = parRot->info01;
		timerParent = ++dataParent->field_6;
		if (weight <= 3.0)
		{
			resultParent = (double)timerParent / parRot->info01 * 0.63;
		}
		else
		{
			resultParent = (double)timerParent / parRot->info01 * 0.13;
		}
		v7 = 8.0 - resultParent;
		if (v7 >= 0.0)
		{
			if (v7 > 4.3000002)
			{
				v7 = 4.3000002;
			}
			v10 = v7 * 65536.0;
			dataParent->Rotation.x += (unsigned __int64)(0.002777777777777778 * v10);
			ChildObj->Data1.Entity->Rotation.x = (unsigned __int64)(v10 * 0.002777777777777778);
		}
		else
		{
			v8 = fabs(v7);
			if (v8 > 4.3000002)
			{
				v8 = 4.3000002;
			}
			v9 = v8 * 65536.0;
			dataParent->Rotation.x += (unsigned __int64)(-0.002777777777777778 * v9);
			ChildObj->Data1.Entity->Rotation.x = (unsigned __int64)(v9 * -0.002777777777777778);
		}
		parentRotX = dataParent->Rotation.x;
		if (parentRotX >= 0)
		{
			if (parentRotX <= 0x8000)
			{
				return;
			}
			parentRotY = *(float*)&dataParent->Rotation.y;
			v15 = parRot->info01 + 3.0;
			dataParent->Action = 3;
			a3.x = v15;
			a3.y = 0.0;
			a3.z = 0.0;
			a2.x = 0.0;
			a2.y = parentRotY;
			a2.z = 0.0;
			DoNextAction_r(0, 15, 0);
			dothedash(0, &a3, (Rotation*)&a2, 10);
		}
		else
		{
			parentRotY2 = *(float*)&dataParent->Rotation.y;
			v13 = parRot->info01 + 1.0;
			dataParent->Action = 1;
			a2.x = v13;
			a2.y = 0.0;
			a2.z = 0.0;
			a3.x = 0.0;
			a3.y = parentRotY2;
			a3.z = 0.0;
			DoNextAction_r(0, 15, 0);
			dothedash(0, &a2, (Rotation*)&a3, 20);
		}
		//PlaySound(101, 0, 0, 0);
	LABEL_30:
		Asi_ApplyScaleStuff(dataParent, parRot);
		return;
	}
	parentTimer2 = (unsigned __int16)++dataParent->field_6;
	dataParent->Scale.x = 5.0;
	v16 = (8.0 - (double)parentTimer2 / parRot->info01 * 0.2) * 0.5;
	if (v16 >= 0.0)
	{
		v18 = v16 * 65536.0;
		dataParent->Rotation.x += (unsigned __int64)(0.002777777777777778 * v18);
		ChildObj->Data1.Entity->Rotation.x = (unsigned __int64)(v18 * 0.002777777777777778);
	}
	else
	{
		v17 = fabs(v16) * 65536.0;
		dataParent->Rotation.x += (unsigned __int64)(-0.002777777777777778 * v17);
		ChildObj->Data1.Entity->Rotation.x = (unsigned __int64)(v17 * -0.002777777777777778);
	}

	if (dataParent->Rotation.x >= 0)
	{
		if ((double)dataParent->Rotation.x * 0.0054931640625 < 180.0)
		{
			return;
		}
		parentRotY3 = *(float*)&dataParent->Rotation.y;
		a3.x = parRot->info01 + 1.0;
		dataParent->Action = 3;
		a3.y = 0.0;
		a3.z = 0.0;
		a2.x = 0.0;
		a2.y = parentRotY3;
		a2.z = 0.0;
		dothedash(0, &a3, (Rotation*)&a2, 10);
		//PlaySound(101, 0, 0, 0);
		DoNextAction_r(0, 15, 0);
		dataParent->Scale.x = 0.0;
		Asi_ApplyScaleStuff(dataParent, parRot);
		return;
	}

	v19 = parRot->info01 + 2.0;
	dataParent->Action = 1;
	a2.x = 0.0;
	a2.y = 0.0;
	a2.z = v19;
	njPushMatrix(_nj_unit_matrix_);
	v20 = dataParent->Rotation.y;
	if (v20)
	{
		njRotateY(0, (unsigned __int16)v20);
	}
	njCalcPointSADX(CURRENT_MATRIX, &a2, &a3);
	njPopMatrix(1u);
	EnemyBounceThing(0, a3.x, a3.y, a3.z);
	DoNextAction_r(0, 15, 0);
	dataParent->Scale.y = 5.0;
	dataParent->Scale.x = 0.0;
	parRot->info03 = 0;
	dataParent->field_6 = 0;
	dataParent->Scale.z = 0.0;
	return;
}


void TurnAsi_CheckAndSendPlayer(ObjectMaster* obj)
{
	EntityData1* data; // esi
	ObjectMaster* child; // esi
	double getSpeed; // st7
	FloatInfo* getrot = new FloatInfo();
	getrot = (FloatInfo*)obj->Data2.Undefined;

	data = obj->Data1.Entity;
	AddToCollisionList(obj);
	if (data->Index == 10)
	{
		if (getrot->info01 >= 1.5)
		{
			// PlaySound(100, 0, 0, 0);
			getSpeed = getrot->info01;
			data->Action = 2;
			if (getSpeed >= 4.0)
			{
				DoNextAction_r(0, 10, 0); //object control with speed
			}
			else
			{
				DoNextAction_r(0, 9, 0); //object control without speed
			}
		}
		else
		{
			data->Index = 0;
			data->Scale.x = 0.0;
			data->Scale.y = 0.0;
			data->Scale.z = 0.0;
			data->Rotation.x = 0;
			child = (ObjectMaster*)obj->field_4C;
			if (child)
			{
				child->Data1.Entity->Scale.z = 0.0;
			}
		}
	}
}

void OTurnasi(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;
	FloatInfo* rot = new FloatInfo();
	ObjUnknownA* objUnk; // ecx
	int getRotX = 0;
	__int16 status;


	switch (data->Action)
	{
	case 0:
		obj->field_4C = LoadChildObject((LoadObj)(LoadObj_UnknownA | LoadObj_Data1 | LoadObj_Data2), TurnAsi_Child, obj);
		rot->info01 = 0.0;
		rot->info03 = 0.0;
		obj->Data2.Undefined = rot;
		objUnk = obj->UnknownA_ptr;
		objUnk->field_10 = 0;
		objUnk->field_14 = 0.0;
		objUnk->field_18 = 0;
		objUnk->field_4 = 0;
		objUnk->field_8 = 0;
		objUnk->field_C = 0;
		data->Action = 1;
		data->Scale.y = 0.0;
		data->Index = 0;
		data->Scale.z = 0.0;
		data->Rotation.x = 0;
		data->Collision->Range = 100.0;
		break;
	case 1:
		TurnAsi_CheckAndSendPlayer(obj);
		break;
	case 2:
		Asi_DoRotationThing(obj, data);
		break;
	case 3:
		getRotX = data->Rotation.x - 182;
		data->Rotation.x = getRotX;
		if (getRotX <= 0)
		{
			status = data->Status;
			data->Action = 1;
			data->Rotation.x = 0;
			data->Status = status | 0x100;
		}
		break;
	case 4:
		DeleteObjAndResetSet(obj);
		break;
	default:
		return;
	}
}

void __cdecl DisplayTurnAsi(ObjectMaster* a1)
{
	EntityData1* v1; // esi
	Angle v2; // eax
	Angle v3; // eax
	NJS_OBJECT* child = TurnAsi->getmodel()->child;
	NJS_OBJECT* childChild = TurnAsi->getmodel()->child->child;


	v1 = a1->Data1.Entity;
	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrix(0);
	njTranslate(0, v1->Position.x, v1->Position.y, v1->Position.z);
	v2 = v1->Rotation.y;
	if (v2)
	{
		njRotateY(0, (unsigned __int16)v2);
	}
	v3 = v1->Rotation.x;
	if (v3)
	{
		njRotateX(0, (unsigned __int16)v3);
	}
	DrawChunkModel(TurnAsi->getmodel()->getchunkmodel());
	njPushMatrix(0);
	njTranslate(0, child->pos[0], child->pos[1], child->pos[2]);
	DrawChunkModel(child->getchunkmodel());
	njPushMatrix(0);
	njTranslate(0, childChild->pos[0], childChild->pos[1], childChild->pos[2]);
	if (v1->Rotation.x)
	{
		njRotateX(0, (unsigned __int16)-LOWORD(v1->Rotation.x));
	}
	DrawChunkModel(childChild->getchunkmodel());
	njPopMatrix(1u);
	njPopMatrix(1u);
	njPopMatrix(1u);
}

void __cdecl LoadTurnAsi(ObjectMaster* obj)
{
	EntityData1* v1; // esi

	v1 = obj->Data1.Entity;
	InitCollision(obj, TurnAsiCol, 7, 4u);

	obj->MainSub = OTurnasi;
	obj->DisplaySub = DisplayTurnAsi;
	obj->DeleteSub = j_DeleteChildObjects;
}

void FreeModel_TurnAsi() {
	FreeMDL(TurnAsi);
}

void LoadModel_TurnAsi() {
	TurnAsi = LoadMDL("SH-TurnAsi", ModelFormat_Chunk);
	return;
}
