#include "pch.h"


static ModelInfo* SH_Tokei[2];


CollisionData TokeiCol[] = {
	{ 0, CollisionShape_Cube1, 0x77, 0, 0, {0.0, 2.0, 0.0}, 11.0, 2.0, 11.0, 0.0, 0, 0, 0 },
	{ 0, CollisionShape_Cyl1, 0x77, 0, 0, {0.0, 14.0, 0.0}, 8.0, 12.0, 0.0, 0.0, 0, 0, 0 },
	{ 0, CollisionShape_Cyl1, 0x77, 0, 0, {0.0, 38.5, 0.0}, 7.0, 17.5, 0.0, 0.0, 0, 0, 0 }
};

void OTokei_Display(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;

	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrix(0);
	njTranslateV(CURRENT_MATRIX, &data->Position);
	njRotateZXY(&data->Rotation);
	DrawObject(SH_Tokei[0]->getmodel());

	njTranslate(CURRENT_MATRIX, 0.0, 0.0, 0.0);
	njRotateX(CURRENT_MATRIX, obj->Data2.Entity->SpeedAngle.x);
	DrawObject(SH_Tokei[1]->getmodel());

	njPopMatrix(1u);
}

void __cdecl OTokei_Main(ObjectMaster* a1)
{
	EntityData1* data; // esi
	Angle v2; // eax
	Angle v3; // eax
	Angle v4; // eax
	int* v5; // eax
	__int16 v6; // ax
	__int16 v7; // cx
	__int16 v8; // ax

	data = a1->Data1.Entity;
	if (!ClipSetObject(a1))
	{
		switch (data->Action) {
		case 0:
			a1->Data2.Entity = AllocateEntityData2();
			a1->Data2.Entity->SpeedAngle.x = 0.0;
			a1->Data2.Entity->SpeedAngle.y = 0.0;
			a1->Data2.Entity->SpeedAngle.z = 0.0;
			a1->DisplaySub = OTokei_Display;
			data->Action = 1;
			break;
		case 1:
			data->field_6 += 1024;
			a1->Data2.Entity->SpeedAngle.x = unsigned __int64(njSin((unsigned __int16)data->field_6) * 896.0);
			v6 = data->Status;
			if ((v6 & 0x100) != 0)
			{
				v7 = data->field_6;
				if ((unsigned __int16)v7 <= 0xC000u)
				{
					if ((v7 & 0x7FFF) == 0)
					{
						//playsound
						return;
					}
				}
				v8 = v6 & 0xFEFF;
			}
			else
			{
				v7 = data->field_6;
				if ((unsigned __int16)v7 <= 0x4000u)
				{
					//playsound
					return;
				}
				v8 = v6 | 0x100;
			}
			data->Status = v8;
			break;
		}
	}

	AddToCollisionList(a1);
	sub_49CE60(data, 0);
}


void __cdecl OTokei(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	InitCollision(obj, TokeiCol, 3, 4u);
	data->Status &= 0xFEu;
	data->field_6 = 0;
	obj->MainSub = OTokei_Main;
}

void FreeTokeiModels() {
	FreeMDL(SH_Tokei[0]);
	FreeMDL(SH_Tokei[1]);
	return;
}

void LoadTokeiModels() {
	SH_Tokei[0] = LoadMDL("SH-Tokei0", ModelFormat_Chunk);
	SH_Tokei[1] = LoadMDL("SH-Tokei1", ModelFormat_Chunk);
	return;
}