#include "pch.h"

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
		act3Trigger(obj);
		break;
	default:
		return;
	}
}
