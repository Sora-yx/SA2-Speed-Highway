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

void TurnAsiaColCheck(ObjectMaster* obj_) {
	EntityData1* data; // esi
	ObjectMaster* player_obj; // eax
	CharObj2Base* player_co2; // ebp
	ObjectMaster* parent_obj; // eax
	EntityData1* parent_data; // edi
	Angle rot_y; // eax
	Angle rot_x; // eax
	double len; // st7
	CollisionInfo* colli; // ecx
	__int16 colli_flags; // ax
	long double offset_x; // st6
	long double offset_z; // st6
	EntityData1* player_data; // [esp+8h] [ebp-28h]
	NJS_POINT3 vs; // [esp+Ch] [ebp-24h]
	NJS_POINT3 vd; // [esp+18h] [ebp-18h]
	NJS_VECTOR v; // [esp+24h] [ebp-Ch]
	obj* child;
	obj* childchild;

	data = obj_->Data1.Entity;
	player_obj = MainCharacter[0];

	if (!player_obj)
		return;

	player_data = player_obj->Data1.Entity;

	player_co2 = MainCharObj2[0];

	if (!player_co2)
		return;

	parent_obj = obj_->Parent;

	if (!parent_obj)
		return;

	FloatInfo* parentRot = new FloatInfo;
	parentRot = (FloatInfo*)parent_obj->Data2.Undefined;

	FloatInfo* childRot = new FloatInfo;
	childRot = (FloatInfo*)obj_->Data2.Undefined;

	parent_data = parent_obj->Data1.Entity;

	parent_data->Index = 0;

	if (parent_data->Scale.y == 5.0)
	{
		data->Action = 2;
		data->Scale.y = 10.0;
		parent_data->Scale.y = 0.0;
	}
	else
	{
		vs.x = 0.0;
		vs.y = 0.0;
		vs.z = 0.0;
		njPushMatrix(_nj_unit_matrix_);
		njTranslateSADX(0, parent_data->Position.x, parent_data->Position.y, parent_data->Position.z);
		rot_y = parent_data->Rotation.y;
		if (rot_y)
		{
			njRotateY(0, (unsigned __int16)rot_y);
		}
		rot_x = parent_data->Rotation.x;
		if (rot_x + data->Rotation.x)
		{
			njRotateX(0, (unsigned __int16)(rot_x + (data->Rotation.x)));
		}
		child = TurnAsi->getmodel()->child;
		childchild = TurnAsi->getmodel()->child->child;
		njTranslateSADX(0, child->pos[0], child->pos[1], child->pos[2]);
		njTranslateSADX(0, childchild->pos[0], childchild->pos[1], childchild->pos[2]);
		njCalcPointSADX(0, &vs, &vd);
		njPopMatrixEx();
		data->Position = vd;
		data->Rotation.y = parent_data->Rotation.y;

		if (parent_data->Scale.z != 20.0)
		{
			if ((data->Scale.z != 10.0))
			{
				v.x = player_co2->Speed.x;
				v.y = player_co2->Speed.y;
				v.z = player_co2->Speed.z;
				len = njScalor(&v);
				parentRot->info01 = len;
				colli = data->Collision;
				colli_flags = colli->Flag;

				if ((colli_flags & 1) != 0) {

					colli->Flag = colli_flags & 0xFFFE;
					parent_data->Index = 10.0;
					data->Scale.z = 10.0;
					offset_x = (float)(player_data->Position.x - data->Position.x);
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
					offset_z = (float)(player_data->Position.z - data->Position.z);
					childRot->info01 = offset_z;

					if (fabs(offset_z) >= 7.0) {

						if (offset_z >= 0.0)
						{
							childRot->info03 = 7.0;
						}
						else
						{
							childRot->info03 = -7.0;
						}
					}

					parentRot->info01 = len;
				}

			}

			AddToCollisionList(obj_);
		}
	}
}



void TurnAsiaChild(ObjectMaster* tp)
{
	EntityData1* v1; // r31
	unsigned int v2; // r11
	double v3; // fp12
	CollisionInfo* v4; // r11

	v1 = tp->Data1.Entity;
	v2 = (unsigned __int8)v1->Action;
	if (v1->Action)
	{
		if (v2 == 1)
		{
			TurnAsiaColCheck(tp);
		}
		else if (v2 < 3)
		{
			v3 = v1->Scale.y;
			v1->Scale.y = v1->Scale.y - (float)1.0;
			if (v3 < 0.0)
			{
				v4 = v1->Collision;
				v1->Action = 1;
				v1->Scale.y = 10.0;
				v4->Flag &= 0xFFFEu;
				v1->Scale.z = 0.0;
			}
		}
	}
	else
	{
		FloatInfo* getrot = new FloatInfo();
		v1 = tp->Data1.Entity;
		getrot->info01 = 0.0;
		getrot->info03 = 0.0;
		tp->Data2.Undefined = getrot;
		InitCollision(tp, &AsiaChildCol, 1, 4u);
		v1->Action = 1;
	}
}

void sub_618F50(ObjectMaster* parentObj, EntityData1* dataParent)
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


	ChildObj = (ObjectMaster*)parentObj->field_4C;

	if (!ChildObj)
		return;

	FloatInfo* parentrot;
	parentrot = (FloatInfo*)parentObj->Data2.Undefined; //get rotation stored
	FloatInfo* childrot;
	childrot = (FloatInfo*)ChildObj->Data2.Undefined; //get rotation stored


	dataParent->Scale.z = 20.0;
	PlayerData->Position.x = ChildObj->Data1.Entity->Scale.x + ChildObj->Data1.Entity->Position.x;
	PlayerData->Position.y = ChildObj->Data1.Entity->Position.y - 7.5;
	PlayerData->Position.z = ChildObj->Data1.Entity->Position.z;

	if (parentrot->info01 < 4.0 && (dataParent->Scale.x) != 0x40A00000)
	{
		weight = parentrot->info01;
		timerParent = ++dataParent->field_6;
		if (weight <= 3.0)
		{
			resultParent = (double)timerParent / parentrot->info01 * 0.63;
		}
		else
		{
			resultParent = (double)timerParent / parentrot->info01 * 0.13;
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
			v15 = parentrot->info01 + 3.0;
			dataParent->Action = 3;
			a3.x = v15;
			a3.y = 0.0;
			a3.z = 0.0;
			a2.x = 0.0;
			a2.y = parentRotY;
			a2.z = 0.0;

			DoNextAction(0, 15, 0);
			dothedash(0, &a3, (Rotation*)&a2, 10);
		}
		else
		{
			parentRotY2 = *(float*)&dataParent->Rotation.y;
			v13 = parentrot->info01 + 1.0;
			dataParent->Action = 1;
			a2.x = v13;
			a2.y = 0.0;
			a2.z = 0.0;
			a3.x = 0.0;
			a3.y = parentRotY2;
			a3.z = 0.0;
			DoNextAction(0, 15, 0);
			dothedash(0, &a2, (Rotation*)&a3, 20);
		}
		//PlaySound(101, 0, 0, 0);
	LABEL_30:
		parentrot->info03 = 0;
		dataParent->field_6 = 0;
		dataParent->Scale.y = 5.0;
		dataParent->Scale.z = 0.0;
		return;
	}
	parentTimer2 = (unsigned __int16)++dataParent->field_6;
	dataParent->Scale.x = 5.0;
	v16 = (8.0 - (double)parentTimer2 / parentrot->info01 * 0.2) * 0.5;
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
		a3.x = parentrot->info01 + 1.0;
		dataParent->Action = 3;
		a3.y = 0.0;
		a3.z = 0.0;
		a2.x = 0.0;
		a2.y = parentRotY3;
		a2.z = 0.0;
		dothedash(0, &a3, (Rotation*)&a2, 10);
		//PlaySound(101, 0, 0, 0);
		DoNextAction(0, 15, 0);
		dataParent->Scale.x = 0.0;
		goto LABEL_30;
	}
	v19 = parentrot->info01 + 2.0;
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
	DoNextAction(0, 15, 0);
	dataParent->Scale.y = 5.0;
	dataParent->Scale.x = 0.0;
	parentrot->info03 = 0;
	dataParent->field_6 = 0;
	dataParent->Scale.z = 0.0;

}


void SetPlayerTurnAsiAction(ObjectMaster* a1) {

	EntityData1* data = a1->Data1.Entity;
	double v3;
	ObjectMaster* child; // esi

	AddToCollisionList(a1);

	FloatInfo* childrot;
	childrot = (FloatInfo*)a1->Data2.Undefined; //get rotation stored


	if (data->Index == 10) {

		if (childrot->info01 >= 1.5) {
			v3 = childrot->info01;
			data->Action = 2;
			if (v3 >= 4.0) {
				DoNextAction_r(0, 10, 0); //object control with speed
			}
			else {
				DoNextAction_r(0, 9, 0); //object control without speed
			}
		}
	}
	else {
		data->Index = 0;
		data->Scale.x = 0.0;
		data->Scale.y = 0.0;
		data->Scale.z = 0.0;
		data->Rotation.x = 0;
		child = (ObjectMaster*)a1->field_4C;
		if (child) {
			child->Data1.Entity->Scale.z = 0.0;
		}
	}


}

void __cdecl DisplayTurnAsi(ObjectMaster* a1)
{
	EntityData1* v1; // esi
	Angle v2; // eax
	Angle v3; // eax
	obj* child;
	obj* childchild;
	v1 = a1->Data1.Entity;
	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrixEx();
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
	DrawChunkModel(TurnAsi->getmodel()->chunkmodel);

	njPushMatrixEx();
	child = TurnAsi->getmodel()->child;

	njTranslate(0, child->pos[0], child->pos[1], child->pos[2]);
	DrawChunkModel(child->getchunkmodel());

	njPushMatrixEx();
	childchild = TurnAsi->getmodel()->child->child;
	njTranslate(0, childchild->pos[0], childchild->pos[1], childchild->pos[2]);
	if (v1->Rotation.x)
	{
		njRotateX(0, (unsigned __int16)-LOWORD(v1->Rotation.x));
	}
	DrawChunkModel(childchild->getchunkmodel());
	njPopMatrixEx();
	njPopMatrixEx();
	njPopMatrixEx();
}

void __cdecl OTurnasi(ObjectMaster* obj)
{
	EntityData1* v1; // esi
	ObjUnknownA* v2; // ecx
	EntityData1* v3; // eax
	int v4; // eax

	v1 = obj->Data1.Entity;
	if (!ClipSetObject(obj))
	{
		switch (v1->Action)
		{
		case 0: {
			obj->field_4C = LoadChildObject((LoadObj)(LoadObj_UnknownA | LoadObj_Data1 | LoadObj_Data2), TurnAsiaChild, obj);
			FloatInfo* getrot = new FloatInfo();
			v1 = obj->Data1.Entity;
			v1->Status |= 0x20u;
			getrot->info01 = 0.0;
			getrot->info03 = 0.0;
			obj->Data2.Undefined = getrot;
			v2 = obj->UnknownA_ptr;
			v3 = obj->Data1.Entity;
			v2->field_10 = 0;
			v2->field_14 = 0.0;
			v2->field_18 = 0;
			v2->field_4 = 0;
			v2->field_8 = 0;
			v2->field_C = 0;
			v3->Action = 1;
			v3->Index = 0;
			v3->Scale.x = 0.0;
			v3->Scale.y = 0.0;
			v3->Scale.z = 0.0;
			v3->Rotation.x = 0;
			obj->DeleteSub = j_DeleteChildObjects;
			obj->DisplaySub = DisplayTurnAsi;
			v1->Collision->Range = 100.0;
		}
			  break;
		case 1:
			SetPlayerTurnAsiAction(obj);
			break;
		case 2:
			sub_618F50(obj, v1);
			break;
		case 3:
			v4 = v1->Rotation.x - 182;
			v1->Rotation.x = v4;
			if (v4 <= 0)
			{
				(v1->Status) |= 0x100;
				v1->Action = 1;
				v1->Rotation.x = 0;
			}
			break;
		case 4:
			DeleteObjAndResetSet(obj);
			break;
		default:
			return;
		}
	}
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

void LoadModel_TurnAsi() {
	TurnAsi = LoadMDL("SH-TurnAsi", ModelFormat_Chunk);
}
