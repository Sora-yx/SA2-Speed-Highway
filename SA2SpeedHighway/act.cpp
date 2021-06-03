#include "pch.h"


void SetSonicRunningOnBulding(ObjectMaster* a1)
{
	EntityData1* v1; // esi
	EntityData1* v2; // edi
	__int16 v3; // ax
	__int16 v4; // ax


	v1 = a1->Data1.Entity;

	if (CurrentAct != 1 && MainCharObj1[0]->Position.x <= 2.0)
		return;

	if (a1->Data1.Entity->Action != 30) {
		for (int i = 0; i < MAXPLAYERS; i++) {
			v2 = MainCharObj1[i];
			if (v2)
			{
				v3 = v1->field_6;
				v1->field_6 = v3 + 1;

				if (v2->Position.y <= 25.0)
				{
					v4 = v1->Status;
					if ((v4 & 8) == 0)
					{
						v1->Status = v4 | 8;
						LoadLevelMusic((char*)"highway2.adx");
						//DoNextAction(i, 85, 0);
						a1->Data1.Entity->Action = 30;
					}
				}
	
			}
		}
	}
}


static void act3Trigger(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	
	for (int i = 0; i < MAXPLAYERS; i++)
	{
		EntityData1* player = MainCharObj1[i];

		if (player)
		{
			if (player->Position.x >= 280.0f && player->Position.y <= -19000.0f)
			{
				data->Action = 4;
				LoadSHAct(2);
			}
		}
	}
}

static void act2Trigger(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	for (int i = 0; i < MAXPLAYERS; i++)
	{
		EntityData1* player = MainCharObj1[i];

		if (player)
		{
			const float v3 = (4002.0f - player->Position.x) * (4002.0 - player->Position.x)
				+ (-1500.0 - player->Position.y) * (-1500.0 - player->Position.y)
				+ (4750.0 - player->Position.z) * (4750.0 - player->Position.z);

			if (sqrtf(v3) < 60.0f)
			{
				data->Action = 1;
				LoadSHAct(1);
			}
		}
	}
}

void __cdecl SHControlActTrigger(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	
	switch (CurrentAct)
	{
	case 0:
		act2Trigger(obj);
		break;
	case 1:
		SetSonicRunningOnBulding(obj);	
		act3Trigger(obj);
		break;
	default:
		return;
	}
}
