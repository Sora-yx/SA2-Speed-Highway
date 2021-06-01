#include "pch.h"

int CurrentAct = 0;

void act3Trigger(ObjectMaster* a1)
{
	EntityData1* v1; // esi
	EntityData1* v2; // edi
	float v3; // [esp+0h] [ebp-Ch]

	v2 = a1->Data1.Entity;

	for (int i = 0; i < 8; i++) {
		v1 = MainCharObj1[i];

		if (v1)
		{
			if (v1->Position.x >= 280.0 && v1->Position.y <= -19000) {
				v1->Action = 4;
				StopMusic();
				CurrentAct = 2;
				GameState = GameStates_RestartLevel_1;
			}
		}
	}
}


void act2Trigger(ObjectMaster* a1)
{
	EntityData1* v1; // esi
	EntityData1* v2; // edi
	float v3; // [esp+0h] [ebp-Ch]

	v2 = a1->Data1.Entity;

	for (int i = 0; i < 8; i++) {
		v1 = MainCharObj1[i];

		if (v1)
		{
			v3 = (4002.0 - v1->Position.x) * (4002.0 - v1->Position.x)
				+ (-1500.0 - v1->Position.y) * (-1500.0 - v1->Position.y)
				+ (4750.0 - v1->Position.z) * (4750.0 - v1->Position.z);
			if (sqrt(v3) < 60.0)
			{

				v2->Action = 1;
				StopMusic();
				CurrentAct = 1;
				GameState = GameStates_RestartLevel_1;
			}
		}
	}
}

void SHControlActTrigger(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;
	
	switch (CurrentAct) {
	case 0:
		act2Trigger(obj);
		break;
	case 1:
		act3Trigger(obj);
		break;
	default:
		return;
	}
}
