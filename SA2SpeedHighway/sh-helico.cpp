#include "pch.h"

static ModelInfo* SH_Helico[3];

CollisionData HeliCol = { 0, (CollisionShapes)0x1, 1, 0x2F, 0x400, {0.0, 20.0, 0.0}, 75.0, 1.0, 0.0, 0.0, 0, 0, 0 };
CollisionData HeliGrabCol = { 0, (CollisionShapes)0x0, 0x70, 0xEC, 0, {0}, 12.0, 0.0, 0.0, 0.0, 0, 0, 0 };

extern NJS_TEXLIST highwayObj_TEXLIST;
extern LoopHead PathList_SpeedHighway0_3;

float Floatidk1 = 0.0;
float Floatidk2 = 0.0;
float Floatidk3 = 0.0;
int HeliStackA = 0;
int HeliAngY_Spd = 0;
int HeliAngleY = 0;

float floatWriteIDK = 0.0;
float floatWriteIDK2 = 0.0;
float floatWriteIDK3 = 0.0;

void Heli_ApplyPositionStuff(RotInfo* dataNewRot, EntityData1* v2) {
	int v25;
	v25 = (unsigned __int16)v2->field_6 + dataNewRot->info01;
	v2->Position.y = v2->Scale.z + v2->Position.y;
	dataNewRot->info01 = v25;
}

void HeliWriteSub(EntityData1* a1, ObjectMaster* a2)
{
	EntityData1* v2; // esi
	double delta_z; // st7
	double delta_y; // st6
	double delta_x; // st5
	double v7; // st7
	double v8; // st7
	unsigned __int64 v9; // rax
	int v10; // ecx
	int v11; // ecx
	RotInfo* dataNewRot;
	int v12; // edi
	int v13; // eax
	int v14;
	int v15; // eax
	int v16;
	int v17; // eax
	int v18; // edx
	bool v19; // sf
	__int16 v20; // cx
	double v21; // st7
	double v22; // st7
	__int16 v23; // cx
	double v24; // st7
	float square_mag; // [esp+0h] [ebp-Ch]
	float v27; // [esp+0h] [ebp-Ch]
	dataNewRot = (RotInfo*)a2->field_4C;

	v2 = a2->Data1.Entity;
	delta_z = CameraData.Position.z - v2->Position.z;
	delta_y = CameraData.Position.y - v2->Position.y;
	delta_x = CameraData.Position.x - v2->Position.x;
	square_mag = delta_y * delta_y + delta_z * delta_z + delta_x * delta_x;

	if (sqrt(square_mag) < 1000.0)
	{
		switch (v2->NextAction)
		{
		case 1:
			v17 = dataNewRot->info03 + 96;
			v18 = dataNewRot->info02 + 256;
			v19 = (int)(dataNewRot->info03 - 1440) < 0;
			dataNewRot->info03 = v17;
			dataNewRot->info02 = v18;
			
			if (v17 < 6444)
			{
				v2->NextAction = 2;
			}
			break;
		case 2:
			v15 = dataNewRot->info03 - 96;
			v16 = dataNewRot->info02 - 256;
			dataNewRot->info03 = v15;
			dataNewRot->info02 = v16;
			if ((int)v15 <= -6144)
			{
				v2->NextAction = 1;
			}
			break;
		case 3:
			floatWriteIDK = v2->Position.x - a1->Position.x - -28.884884;
			v7 = v2->Position.z - a1->Position.z;
			floatWriteIDK2 = v7;
			v27 = v7 * floatWriteIDK2 + floatWriteIDK * floatWriteIDK;
			v8 = sqrt(v27);
			floatWriteIDK3 = v8;
			if (v8 > 50.0)
			{
				floatWriteIDK3 = 50.0;
			}
			v9 = (unsigned __int64)(floatWriteIDK3 * 65536.0 * 0.002777777777777778);
			v10 = dataNewRot->info03;
			if ((int)v10 > (int)v9 + 64 || (int)v10 < (int)v9 - 64)
			{
				if ((int)v10 <= (int)v9)
				{
					v11 = v10 + 16;
				}
				else
				{
					v11 = v10 - 16;
				}
				dataNewRot->info03 = v11;
			}
			v12 = dataNewRot->info02;
			v13 = (unsigned __int16)(v12
				+ v2->Rotation.y
				- (unsigned __int64)(atan2(floatWriteIDK, floatWriteIDK2)
					* 65536.0
					* 0.1591549762031479));
			if (v13 > 384)
			{
				if (v13 >= 0x8000)
				{
					v14 = v12 + 384;
				}
				else
				{
					v14 = v12 - 384;
				}
				dataNewRot->info02 = v14;
			}
			break;
		}

		v20 = v2->Status;
		if ((v20 & 0x2000) == 0)
		{
			Heli_ApplyPositionStuff(dataNewRot, v2);
			return;
		}
		v21 = v2->Scale.z;
		if ((v20 & 0x4000) != 0)
		{
			v22 = v21 + 0.2;
			v2->Scale.z = v22;
			if (v22 >= 2.0)
			{
				v2->Scale.z = 2.0;
				v23 = v20 + 0x4000;
				v2->Status = v23;
				Heli_ApplyPositionStuff(dataNewRot, v2);
				return;
			}
		}
		else
		{
			v24 = v21 - 0.2;
			v2->Scale.z = v24;
			if (v24 <= -2.0)
			{
				v2->Scale.z = -2.0;
				v23 = v20 - 0x4000;
				Heli_ApplyPositionStuff(dataNewRot, v2);
				return;
			}
		}

		Heli_ApplyPositionStuff(dataNewRot, v2);
	}
}

void HeliPosCopyPlayer(EntityData1* data, EntityData1* P1)
{
	Angle v2; // edi
	__int16 v3; // ax
	double v4; // st7
	double v5; // st7
	Angle v6; // ecx
	double v7; // st7

	v2 = data->Rotation.y;
	P1->Position.y = data->Position.y - 27.0 + data->Scale.z;
	v3 = data->Status;
	if ((v3 & 0x100) != 0)
	{
		P1->Position.x = njSin(v2 - 0x8000) * 11.2 + data->Position.x;
		v4 = njCos(v2 - 0x8000) * 11.2 + data->Position.z;
		P1->Rotation.y = 0x8000 - v2;
		P1->Position.z = v4;
	}
	else if ((v3 & 0x200) != 0)
	{
		P1->Position.x = njSin(v2 - 0x8000) * 13.8 + data->Position.x;
		v5 = njCos(v2 - 0x8000) * 13.8 + data->Position.z;
		P1->Rotation.y = -v2;
		P1->Position.z = v5;
	}
	else
	{
		v6 = v2 + 0x8000;
		if ((v3 & 0x400) != 0)
		{
			P1->Position.x = data->Position.x - njSin(v6) * 14.2;
			v7 = data->Position.z - njCos(v2 + 0x8000) * 14.2;
			P1->Rotation.y = 0x8000 - v2;
		}
		else
		{
			P1->Position.x = data->Position.x - njSin(v6) * 12.0;
			v7 = data->Position.z - njCos(v2 + 0x8000) * 12.0;
			P1->Rotation.y = -v2;
		}
		P1->Position.z = v7;
	}
}


void HelicoFollowPath(LoopHead* a1, EntityData1* a2, pathinfo* a3) {

	__int16 getRotY; // [esp-14h] [ebp-14h]

	a3->onpathpos = a2->Scale.x;
	GetStatusOnPath(a1, a3);
	HeliAngY_Spd = a2->Rotation.y;
	Floatidk1 = a3->pos.x;
	Floatidk2 = a3->pos.y;
	Floatidk3 = a3->pos.z;
	getRotY = a2->Rotation.y;
	HeliAngleY = (unsigned __int16)(0x4000 - (unsigned __int64)(atan2(a3->normala.x, a3->normala.z) * 65536.0 * -0.1591549762031479));
	HeliStackA = BAMS_SubWrap(getRotY, HeliAngleY, 240);
	HeliAngY_Spd = SubAngle(HeliStackA, HeliAngY_Spd);
}

void __cdecl SH_Helico_Main(ObjectMaster* a1)
{
	EntityData1* v1; // ebx
	EntityData1* Data; // ebp
	int v3; // ecx
	int CurAction; // eax
	__int16 v5; // ax
	char v6; // al
	double v7; // st7
	float v8; // ecx
	float playerPosX; // edx
	bool v10; // c0
	bool v11; // c3
	Angle v12; // esi
	char v13; // al
	double v14; // st7
	char v15; // al
	double v17; // st7
	unsigned __int8 v18; // c0
	unsigned __int8 v19; // c3
	int v20; // eax
	int v21; // eax
	EntityData1* v22; // esi
	double v23; // st7
	int v24; // edx
	bool v25; // zf
	pathinfo heliPath = {}; // [esp-4Ch] [ebp-CCh] BYREF

	int v29; // [esp-40h] [ebp-C0h]
	int v30; // [esp-3Ch] [ebp-BCh]
	int v31; // [esp-38h] [ebp-B8h]
	EntityData1* P1Data; // [esp+14h] [ebp-6Ch]
	float HelicoPosX; // [esp+18h] [ebp-68h]

	v1 = MainCharObj1[0];
	Data = a1->Data1.Entity;

	v3 = (unsigned __int8)Data->Action;
	CurAction = Data->Action;
	P1Data = MainCharObj1[0];

	switch (CurAction)
	{
	case 0:

		if (MainCharObj1[0]->Position.x > 3120.0
			&& MainCharObj1[0]->Position.x < 3500.0
			&& MainCharObj1[0]->Position.z > 1220.0
			&& MainCharObj1[0]->Position.z < 1600.0) {
			v5 = Data->field_6;
			if ((unsigned __int16)v5 >= 0xF00u)
			{
				if (Data->Scale.x >= 30.0)
				{
					Data->Status |= 0x30u;

					v6 = Data->Action;
					Data->Status &= 0xEFu;
					Data->Action = v6 + 1;
				}
				else
				{
					Data->Scale.x = Data->Scale.x + 0.5;
				}
			}
			else
			{
				Data->field_6 = v5 + 64;
			}
		}
		break;
	case 1:
		if (Data->Scale.x >= 30.0)
		{
			v7 = Data->Position.y - 10.0;
			v8 = Data->Position.z;
			playerPosX = MainCharObj1[0]->Position.x;
			HelicoPosX = Data->Position.x;
			v10 = v7 < MainCharObj1[0]->Position.y;
			v11 = v7 == MainCharObj1[0]->Position.y;
			v31 = MainCharObj1[0]->Position.z;
			v29 = v8;
			v30 = playerPosX;

			v12 = Data->Rotation.y;
			if ((v12 - (atan2(Data->Position.z - v1->Position.z, Data->Position.x - v1->Position.x) * 65536.0 * -0.1591549762031479)) >= 0x8000u)
			{
				if ((v12 + v1->Rotation.y) <= 0x4000u || (v12 + v1->Rotation.y) >= 0xC000u)
				{
					Data->Status += 2048;
				}
				else
				{
					Data->Status += 1024;
				}
			}
			else if ((v12 + v1->Rotation.y) <= 0x4000u || (v12 + v1->Rotation.y) >= 0xC000u)
			{
				Data->Status += 512;
			}
			else
			{
				Data->Status += 256;
			}

		}
		break;

	case 2:
		if (Data->Scale.x > 1100.0)
		{
			v14 = Data->Position.y;
			(Data->Status) &= 0xF0FFu;

			v1->Position.y = v14 - 30.0;
			DoNextAction_r(0, 15, 0);
			v15 = Data->Action + 1;
			Data->Scale.y = 1.0;
			Data->Action = v15;
		}
		v17 = Data->Scale.y;
		if (Data->Scale.x <= 940.0)
		{
			if (MainCharObj2[0]->CharID <= Characters_Shadow) {
				MainCharObj2[0]->AnimInfo.Next = 186;
			}

			if (v17 >= 6.0)
			{

				v1 = P1Data;
			}
			v21 = Data->Rotation.z + 32;
			Data->Scale.y = Data->Scale.y + 0.059999999;
		}
		else
		{
			v20 = Data->Rotation.z;
			Data->Scale.y = v17 - 0.1;
			if (v20 <= 0)
			{
				v22 = P1Data;
				Data->Rotation.z = 0;
				v1 = v22;
			}
			v21 = v20 - 96;
		}
		Data->Rotation.z = v21;

		HeliPosCopyPlayer(Data, P1Data);

		break;
	case 3:
		if (Data->Scale.x < 2200.0)
		{
			if (Data->Scale.y < 4.0)
			{
				v23 = Data->Scale.y + 0.12;
				Data->Rotation.z += 64;
				Data->Scale.y = v23;
			}
		}
		else
		{
			Data->Scale.y = 0.0;
			Data->Scale.x = 30.0;
			Data->Rotation.z = 0;
			Data->Action = 0;
		}
		break;
	}

	Data->Scale.x = Data->Scale.y + Data->Scale.x;
	if (v1->Status >= 0)
	{
		AddToCollisionList(a1);
		sub_49CE60(Data, 0);
	}

	HelicoFollowPath(&PathList_SpeedHighway0_3, Data, &heliPath);

	HeliWriteSub(v1, a1);
	Data->Position.x = Floatidk1;
	Data->Position.y = Floatidk2;
	v24 = Floatidk3;
	Data->Rotation.y = HeliStackA;
	v25 = Data->Action == 0;
	Data->Position.z = v24;
	if (!v25)
	{
		if (++Data->field_2 == 100) {
			Play3DSound_Pos(sound_SHHelico, &Data->Position, 0, 0, 40);
			Data->field_2 = 0;
		}
	}
	return;
}

void SH_DisplayHelico(ObjectMaster* a1) {

	Angle v2; // eax
	Angle v3; // eax
	int v4;
	int v5;
	int v6; // eax
	RotInfo* getrot;	
	getrot = (RotInfo*)a1->field_4C; //get rotation stored in the object for propeller
	EntityData1* v1 = a1->Data1.Entity;

	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrix(0);
	njTranslateV(0, &v1->Position);
	v2 = v1->Rotation.y;
	if (v2)
	{
		njRotateY(0, (unsigned __int16)v2);
	}
	v3 = v1->Rotation.z;
	if (v3)
	{
		njRotateZ(0, (unsigned __int16)v3);
	}
	DrawObject(SH_Helico[0]->getmodel());

	njPushMatrix(0);
	v4 = getrot->info01;
	if (v4)
	{
		njRotateY(0, v4);
	}
	DrawObject(SH_Helico[1]->getmodel());
	njPopMatrix(1u);
	njTranslate(0, -28.884884, -11.80179, 0.0);
	v5 = getrot->info02;
	if (v5)
	{
		njRotateY(0, v5);
	}

	v6 = getrot->info03;

	if (v6)
	{
		njRotateX(0, (unsigned __int16)v6);
	}
	DrawObject(SH_Helico[2]->getmodel());
	njPopMatrix(1u);
}

void __cdecl HelicoChildHelper(ObjectMaster* a1)
{
	EntityData1* v1; // esi
	EntityData1* v2; // eax
	double v3; // st7
	double v4; // st7

	v1 = a1->Data1.Entity;
	v2 = a1->Parent->Data1.Entity;
	v1->Position.x = v2->Position.x;
	v1->Position.y = v2->Position.y - 25.0;
	v3 = v2->Position.z;
	if (v1->Action)
	{
		v4 = v3 + 12.0;
	}
	else
	{
		v4 = v3 - 12.0;
	}
	v1->Position.z = v4;
	v1->Rotation.y = v2->Rotation.y;
	if ((v2->Status & 0x1000) != 0)
	{
		v1->Collision->Flag |= 0x40u;
	}
	if (GetCollidingPlayer(a1) && v2->Action == 1) {

		DoNextAction_r(0, 9, 0);
		v2->Status &= 0xDFu;
		v2->Action = 2;
		return;
	}
	AddToCollisionList(a1);
	sub_49CE60(v1, 0);
}

void Init_Helico(ObjectMaster* a1) {

	EntityData1* v1; // esi
	ObjectMaster* v2; // eax
	ObjectMaster* v3; // eax
	RotInfo* getrot = new RotInfo(); //custom struct used to save propellers rotation/animation in the display

	v1 = a1->Data1.Entity;
	v1->Status &= 0x80FF;
	v1->Action = 0;
	v1->Scale.z = 0.0;
	v1->Scale.x = 0.0;
	v1->Scale.y = 0.0;
	v1->field_6 = 0;
	// v1->timer = (int*)2048;
	getrot->info01 = 0.0; //CharIndex
	getrot->info02 = 0.0; //LoopData
	getrot->info03 = 2048; //Timer/Object

	a1->field_4C = getrot;
	v1->field_2 = 0;
	v1->NextAction = 3;
	InitCollision(a1, &HeliCol, 1, 4u);
	v2 = LoadChildObject(LoadObj_Data1, HelicoChildHelper, a1);
	v2->Data1.Entity->Action = 0;
	InitCollision(v2, &HeliGrabCol, 1, 4u);
	v3 = LoadChildObject(LoadObj_Data1, HelicoChildHelper, a1);
	v3->Data1.Entity->Action = 1;
	InitCollision(v3, &HeliGrabCol, 1, 4u);
	a1->DeleteSub = j_DeleteChildObjects;
	a1->DisplaySub = SH_DisplayHelico;
	a1->MainSub = SH_Helico_Main;
}

void Load_Helico(ObjectMaster* a1) {
	LoadObject(3, "Init_Helico", Init_Helico, LoadObj_Data1);
	a1->MainSub = DeleteObject_;
}

void __cdecl OHelia_Main(ObjectMaster* a2)
{
	EntityData1* v1; // esi
	EntityData1* v2; // edi

	v1 = a2->Data1.Entity;
	v2 = MainCharObj1[0];

	if (v2->Status >= 0)
	{
		AddToCollisionList(a2);
		sub_49CE60(v1, 0);
	}
	HeliWriteSub(v2, a2);
	//sub_424920(96, v1, 1, 0, 2, v1);
}

void __cdecl OHelib(ObjectMaster* obj)
{
	EntityData1* v1; // esi
	RotInfo* getrot = new RotInfo();
	v1 = obj->Data1.Entity;
	v1->Status |= 0x20u;
	getrot->info01 = 0.0;
	getrot->info02 = 0.0;
	getrot->info03 = 2048;
	obj->field_4C = getrot;
	v1->field_6 = 4096;
	InitCollision(obj, &HeliCol, 1, 4u);
	obj->DeleteSub = j_DeleteChildObjects;
	obj->MainSub = OHelia_Main;
	obj->DisplaySub = SH_DisplayHelico;
	v1->NextAction = 3;
}

void __cdecl OHelia(ObjectMaster* obj)
{
	EntityData1* v1; // esi
	RotInfo* getrot = new RotInfo();
	v1 = obj->Data1.Entity;
	v1->Status |= 0x20u;
	getrot->info01 = 0.0;
	getrot->info02 = 0.0;
	getrot->info03 = 2048;
	obj->field_4C = getrot;
	v1->field_6 = 4096;
	InitCollision(obj, &HeliCol, 1, 4u);
	obj->DeleteSub = j_DeleteChildObjects;
	obj->MainSub = OHelia_Main;
	obj->DisplaySub = SH_DisplayHelico;
	v1->NextAction = 1;
}


void LoadHelicoModel() {
	SH_Helico[0] = LoadMDL("sh-heliBody", ModelFormat_Chunk);
	SH_Helico[1] = LoadMDL("sh-heliHane", ModelFormat_Chunk);
	SH_Helico[2] = LoadMDL("sh-heliLight", ModelFormat_Chunk);
	return;
}