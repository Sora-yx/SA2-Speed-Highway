#include "pch.h"
#include "act.h"


int CurrentAct = 0;

static const void* const resetCPptr = (void*)0x43E380;
static inline void CP_ResetPosition(int a1)
{
	__asm
	{
		mov eax, [a1]
		call resetCPptr
	}
}


void CheckAndSetControl(ObjectMaster* obj) {

	EntityData1* v1 = obj->Data1.Entity;

	for (int i = 0; i < MAXPLAYERS; i++) {
		switch (v1->Action) {
		case 0:
			v1->field_6 = 0;

			ControllerEnabled[i] = false;
			if (MainCharObj2[i]) {
				if (MainCharObj2[i]->Speed.x >= 2.0) {
					MainCharObj2[i]->Speed.x = 1.5;
				}
				v1->Action = 1;
			}
			break;
		case 1:
			if (++v1->field_6 == 100) {
				ControllerEnabled[i] = true;
				v1->Action = 2;
			}
			break;
		}
	}

}


void SetSonicRunningOnBulding(ObjectMaster* a1)
{
	EntityData1* data; // esi
	EntityData1* player; // edi
	int v4;

	data = a1->Data1.Entity;

	for (int i = 0; i < MAXPLAYERS; i++) {

		player = MainCharObj1[i];

		if (!player || CurrentAct != 1)
			break;

		switch (data->Action) {

		case 0:
			StopMusic();
			if (++data->field_2 == 20) {
				SetCameraPos(-75.90f, 45.46f, -0.56f);
				data->Action = 1;
			}
			break;
		case 1:
			if (player->Position.y <= -50.0)
			{
				v4 = player->Status;
				if ((v4 & 8) != 0)
					break;

				ControllerEnabled[i] = 0;
				player->Status = v4 | 8;
				LoadLevelMusic((char*)"highway2.adx");

				if (MainCharObj2[i]->CharID <= Characters_Shadow) {
					player->Action = 92;
					MainCharObj2[i]->AnimInfo.Next = 68;
					player->Status &= 0xDAFFu;
				}
				data->field_2 = 0;
				data->Action = 2;

			}
			break;
		case 2:
			if (++data->field_6 == 60) {
				ControllerEnabled[i] = 1;
				data->Action = 3;
			}
			break;
		case 3:
			if (player->Position.y <= -18300.0)
			{
				if (player->Action > 60)
					player->Action = 10;

				EnemyBounceThing(0, 1.4, -2.0, MainCharData2[i]->Velocity.z);
				data->Action = 4;
			}
			break;
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
				CP_ResetPosition(i);
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
				CP_ResetPosition(i);
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
