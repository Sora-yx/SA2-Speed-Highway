#include "pch.h"
#include "objects.h"
#include "sh-bell.h"

static CollisionData Col_Bell01[] = {
	{ 0, (CollisionShapes)0x6, 0x77, 0, 0, {0.0, -30.0, 0.0}, 17.0, 4.0, 0.0, 0.0, 0, 0, 0 },
	{ 0, CollisionShape_Cyl1, 0x77, 0, 0, {0.0, -48.0, 0}, 19.0, 5.0, 0.0, 0.0, 0, 0, 0 },
};

static CollisionData Col_Bell02 = { 0, (CollisionShapes)0x6, 0x10, 0xEC, 0, {0.0, -60.0, 0.0}, 8.0, 5.0, 0.0, 0.0, 0, 0, 0 };

ModelInfo* SH_Bell[2];

void SH_DisplayBell(ObjectMaster* obj) {

	EntityData1* v1 = obj->Data1.Entity;


	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrix(0);
	njTranslateV(0, &v1->Position);
	njRotateZXY(&v1->Rotation);
	DrawObject(SH_Bell[0]->getmodel());

	njPushMatrix(0);

	njRotateZXY(&obj->Child->Data1.Entity->Rotation);
	DrawObject(SH_Bell[1]->getmodel());
	njPopMatrix(2u);
}

void __cdecl Bell_Child(ObjectMaster* obj)
{
	Angle v12; // ecx
	EntityData1* dataChild = obj->Data1.Entity;
	EntityData1* dataParent = obj->Parent->Data1.Entity;

	if (GetCollidingPlayer(obj))
	{
		if (dataParent->Action == 0)
		{
			PrintDebug("BELL CHILDD");
			dataChild->Rotation.x = (unsigned __int64)(njSin(1024) * *(float*)&dataChild->field_6 * 3094.0);
			dataChild->Rotation.z = (unsigned __int64)(njSin(1024) * dataChild->Index * 3094.0);
			//SpawnDroppedRings(dataParent->Position.x, dataParent->Position.y - 70.0, dataParent->Position.z, 6);
			dataParent->Action = 1;
			Play3DSound_Pos(sound_SHBell, &dataParent->Position, 0, 0, 50);
			//PlaySound4(93, 0, 0, 64, v4->Position.x, v4->Position.y, v4->Position.z);
		}
	}

	ObjectSetupInput(dataChild, nullptr);
	AddToCollisionList(obj);
}


void Bell_Main(ObjectMaster* obj) {

	EntityData1* v2; // ebx
	EntityData1* v3; // esi
	Angle v4; // eax
	CollisionInfo* v5; // eax
	char v6; // al
	double v7; // st7
	CollisionInfo* v8; // eax
	float y; // [esp+0h] [ebp-1Ch]

	v3 = obj->Data1.Entity;

	if (v3->Action == 0) {

	}
	else {
		if (++v3->field_6 > 100) {
			v3->field_6 = 0;
			v3->Action = 0;
		}
	}


	AddToCollisionList(obj);
	ObjectSetupInput(v3, nullptr);
}

void __cdecl OHwBell(ObjectMaster* obj)
{
	EntityData1* v1; // esi
	ObjectMaster* v2; // eax
	EntityData1* v3; // ecx

	v1 = obj->Data1.Entity;
	v1->Rotation.z = 0;
	v1->Rotation.x = 0;
	InitCollision(obj, Col_Bell01, 2, 4u);

	v2 = LoadChildObject((LoadObj)(LoadObj_UnknownA | LoadObj_Data1 | LoadObj_Data2), Bell_Child, obj);
	v3 = v2->Data1.Entity;
	v3->Position = v1->Position;
	v3->Rotation.z = 0;
	v3->Rotation.x = 0;
	v3->Index = 120;
	v3->field_6 = 120;
	v3->Rotation.y = v1->Rotation.y;
	InitCollision(v2, &Col_Bell02, 1, 4u);

	obj->MainSub = Bell_Main;
	obj->DisplaySub = SH_DisplayBell;
	obj->DeleteSub = j_DeleteChildObjects;
}

void LoadBellModels() {
	SH_Bell[0] = LoadMDL("SH-Bell0", ModelFormat_Chunk);
	SH_Bell[1] = LoadMDL("SH-Bell1", ModelFormat_Chunk);
}