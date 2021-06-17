#include "pch.h"

static ModelInfo* SH_Arcade[3];

CollisionData SHArcadeCol[] = {
	{ 0, (CollisionShapes)0x3, 0x20, 0xE0, 0, {10.0, -4.0, 0.0}, 10.0, 2.0, 28.0, 0.0, 0, 0, 0},
	{ 0, (CollisionShapes)0x3, 0x27, 0xE0, 0, {10.0, -6.0, 0.0}, 10.0, 2.0, 28.0, 0.0, 0, 0, 0 }
};


void __cdecl Arcade_Display(ObjectMaster* a1)
{
	EntityData1* data; // esi
	Angle v2; // eax

	data = a1->Data1.Entity;
	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrix(0);
	njTranslateV(0, &data->Position);

	njRotateY(0, data->Rotation.y);
	DrawObject((NJS_OBJECT*)a1->field_4C);
	njPopMatrix(1u);
}

void Oaracade_Main(ObjectMaster* a1)
{
	EntityData1* data;
	__int16 status; 
	data = a1->Data1.Entity;

	if (!ClipSetObject(a1))
	{
		status = data->Status;
		if ((status & 0x10) != 0)
		{
			data->Status = status & 0xFFEF;
			for (int i = 0; i < 2; ++i)
			{
				if (data->Collision->CollidingObject->Object == GetCharacterObject(i))
				{
					EnemyBounceThing_Wrapper(i, 0.0, 3.0, 0.0);
				}
			}
		}
		AddToCollisionList(a1);
	}
}

void __cdecl OArcade03(ObjectMaster* obj)
{
	InitCollision(obj, SHArcadeCol, 2, 4u);
	obj->field_4C = SH_Arcade[2]->getmodel();
	obj->MainSub = Oaracade_Main;
	obj->DisplaySub = Arcade_Display;
}

void __cdecl OArcade02(ObjectMaster* obj)
{
	InitCollision(obj, SHArcadeCol, 2, 4u);
	obj->field_4C = SH_Arcade[1]->getmodel();
	obj->MainSub = Oaracade_Main;
	obj->DisplaySub = Arcade_Display;
}

void __cdecl OArcade01(ObjectMaster* obj)
{
	InitCollision(obj, SHArcadeCol, 2, 4u);
	obj->field_4C = SH_Arcade[0]->getmodel();
	obj->MainSub = Oaracade_Main;
	obj->DisplaySub = Arcade_Display;
}

void FreeArcadesModels() {
	for (size_t i = 0; i < LengthOfArray(SH_Arcade); i++) {
		FreeMDL(SH_Arcade[i]);
	}
}

void LoadArcadesModels() {
	for (size_t i = 0; i < LengthOfArray(SH_Arcade); i++) {
		std::string str = "sh-arcade" + std::to_string(i);
		SH_Arcade[i] = LoadMDL(str.c_str(), ModelFormat_Chunk);
	}
}