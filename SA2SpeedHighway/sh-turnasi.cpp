#include "pch.h"

static ModelInfo* TurnAsi;

static CollisionData TurnAsiCol[] = {
	{ 0, (CollisionShapes)0x6, 0x77, 0, 0, {0.0, 15.0, 0.0}, 7.0, 7.0, 0.0, 0.0, 0, 0, 0 },
	{ 0, (CollisionShapes)0x3, 0x77, 0xE0, 0x2000, {0.0, -61.0, 0.0}, 34.5, 2.5, 17.0, 0.0, 0, 0, 0},
	{ 0, (CollisionShapes)0x3, 0x77, 0xE0, 0x2000, {0.0, -53.0, 0.0}, 34.5, 4.0, 4.0, 0.0, 0, 0, 0},
	{ 0, (CollisionShapes)0x3, 0x77, 0xE0, 0x2000, {33.0, -74.0, 0.0}, 2.5, 14.0, 14.0, 0.0, 0, 0, 0 },
	{ 0, (CollisionShapes)0x3, 0x77, 0xE0, 0x2000, {-33.0, -74.0, 0.0}, 2.5, 14.0, 14.0, 0.0, 0, 0, 0 },
	{ 0, (CollisionShapes)0x3, 0x77, 0xE0, 0x2000, {0.0, -93.0, 0.0}, 34.5, 6.0, 14.0, 0.0, 0, 0, 0},
	{ 0, (CollisionShapes)0x3, 0x77, 0xE0, 0x2000, {0.0, -74.0, -15.0}, 34.5, 18.0, 6.0, 0.0, 0, 0, 0},
};

static CollisionData TurnAsiTriggerCol = { 0, (CollisionShapes)0x3, 0, 0xE0, 0, {0.0, 0.0, 5.0}, 40.5, 14.0, 5.0, 0.0, 0, 0, 0 };

struct turnasiwk
{
	float Speed;
};

enum TurnasiActions
{
	Turnasi_Check,
	Turnasi_Send,
	Turnasi_Reset,
	Turnasi_Delete
};

enum TurnasiTActions
{
	TurnasiT_Init,
	TurnasiT_Run,
	TurnasiT_Reset
};

//broken
void TurnasiT_CalcPos(EntityData1* data, ObjectMaster* parent)
{
	EntityData1* parent_data = parent->Data1.Entity;
	turnasiwk* wk = (turnasiwk*)parent->UnknownA_ptr;

	parent_data->Index = 0;

	if (parent_data->Scale.y == 5.0f)
	{
		data->Action = TurnasiT_Reset;
		data->Scale.y = 10.0f;
		parent_data->Scale.y = 0.0;
	}
	else
	{
		NJS_VECTOR vs{};
		NJS_VECTOR vd;
		NJS_OBJECT* child = TurnAsi->getmodel()->child;
		NJS_OBJECT* childChild = TurnAsi->getmodel()->child->child;

		njPushUnitMatrix();
		njTranslateEx(&parent_data->Position);
		njRotateY_(CURRENT_MATRIX, parent_data->Rotation.y);
		njRotateX(CURRENT_MATRIX, parent_data->Rotation.x + data->Rotation.x);
		njTranslateEx((NJS_VECTOR*)&child->pos);
		njTranslateEx((NJS_VECTOR*)&childChild->pos);
		njCalcVector(CURRENT_MATRIX, &vd, &vs, false);
		njPopMatrixEx();

		data->Position = vd;
		data->Rotation.y = parent_data->Rotation.y;

		int player = 0;

		if (MainCharObj1[1])
		{
			if (GetDistance(&data->Position, &MainCharObj1[0]->Position) >
				GetDistance(&data->Position, &MainCharObj1[1]->Position))
			{
				player = 1;
			}
		}

		if (parent_data->Scale.z = 20.0f)
		{
			if (data->Scale.z != 10.0f && data->Collision->Flag & 1)
			{
				EntityData1* player_data = MainCharObj1[player];

				wk->Speed = njScalor(&MainCharObj2[player]->Speed);

				parent_data->field_2 = player;
				parent_data->Index = 10;
				data->Scale.z = 10.0;
				data->Scale.x = player_data->Position.x - data->Position.x;

				if (fabs(data->Scale.x) >= 15.0f)
				{
					if (data->Scale.x >= 0.0f)
					{
						data->Scale.x = 15.0f;
					}
					else
					{
						data->Scale.x = -15.0f;
					}
				}
			}
		}
	}
}

void __cdecl TurnAsi_Trigger(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	switch (data->Action)
	{
	case TurnasiT_Init:
		InitCollision(obj, &TurnAsiTriggerCol, 1, 4);
		data->Action = TurnasiT_Run;
		break;
	case TurnasiT_Run:
		TurnasiT_CalcPos(data, obj->Parent);
		AddToCollisionList(obj);
		break;
	case TurnasiT_Reset:

		if (--data->Scale.y < 0.0f)
		{
			data->Action = TurnasiT_Run;
			data->Scale.y = 10.0f;
			data->Scale.z = 0.0f;
		}

		break;
	}
}

void Turnasi_ResetSub(EntityData1* data)
{
	data->Rotation.x -= 182;

	if (data->Rotation.x <= 0)
	{
		data->Action = Turnasi_Check;
		data->Rotation.x = 0;
		data->Status |= 0x100;
	}
}

void Turnasi_SendSub(EntityData1* data, turnasiwk* info, ObjectMaster* child)
{
	EntityData1* player = MainCharObj1[data->field_2];

	data->Scale.z = 20.0f;

	player->Position.x = child->Data1.Entity->Scale.x + child->Data1.Entity->Position.x;
	player->Position.y = child->Data1.Entity->Position.y - 7.5;
	player->Position.z = child->Data1.Entity->Position.z;

	int timer = ++data->field_6;

	if (info->Speed < 4.0f && data->Scale.x != 5.0f)
	{
		float speed;

		if (info->Speed <= 3.0f)
		{
			speed = timer / info->Speed * 0.63f;
		}
		else
		{
			speed = timer / info->Speed * 0.13f;
		}

		speed -= 8.0f;

		if (speed >= 0.0f)
		{
			if (speed > 4.3f)
			{
				speed = 4.3f;
			}

			Angle angle = speed * 65536.0 * 0.002777777777777778;
			data->Rotation.x += angle;
			child->Data1.Entity->Rotation.x = angle;
		}
		else
		{
			speed = fabs(speed);

			if (speed > 4.3f)
			{
				speed = 4.3f;
			}

			Angle angle = -0.002777777777777778 * (speed * 65536.0);
			data->Rotation.x += angle;
			child->Data1.Entity->Rotation.x = angle;
		}

		if (data->Rotation.x >= 0)
		{
			if (data->Rotation.x <= 0x8000)
			{
				return;
			}
			
			data->Action = Turnasi_Reset;

			NJS_VECTOR speed = { info->Speed + 3.0f, 0, 0 };
			Rotation rot = { 0, data->Rotation.y, 0 };
			
			DoNextAction(data->field_2, 10, 0);
			dothedash(0, &speed, &rot, 10);
		}
		else
		{
			NJS_VECTOR speed = { info->Speed + 1.0f, 0, 0 };
			Rotation rot = { 0, data->Rotation.y, 0 };

			DoNextAction(data->field_2, 9, 0);
			dothedash(0, &speed, &rot, 20);
		}

		// PlaySound(101, 0, 0, 0);

		info->Speed = 0;
		data->field_6 = 0;
		data->Scale.y = 5.0;
		data->Scale.z = 0.0;
	}
	else
	{
		data->Scale.x = 5.0f;

		float speed = (8.0f - timer / info->Speed * 0.2f) * 0.5f;

		if (speed >= 0.0f)
		{
			Angle angle = speed * 65536.0 * 0.002777777777777778;
			data->Rotation.x += angle;
			child->Data1.Entity->Rotation.x = angle;
		}
		else
		{
			Angle angle = -0.002777777777777778 * (fabs(speed) * 65536.0);
			data->Rotation.x += angle;
			child->Data1.Entity->Rotation.x = angle;
		}

		if (data->Rotation.x >= 0)
		{
			if (static_cast<float>(data->Rotation.x) * 0.0054931640625f < 180.0f)
			{
				return;
			}

			NJS_VECTOR speed = { info->Speed + 1.0f, 0, 0 };
			Rotation rot = { 0, data->Rotation.y, 0 };

			DoNextAction(data->field_2, 9, 0);
			dothedash(0, &speed, &rot, 10);

			data->Action = Turnasi_Reset;
			
			//PlaySound(101, 0, 0, 0);
			
			data->Scale.y = 5.0f;
		}
		else
		{
			NJS_VECTOR offset = { 0, 0, info->Speed + 2.0f };
			NJS_VECTOR output;

			data->Action = Turnasi_Check;

			njPushUnitMatrix();
			njRotateY_(CURRENT_MATRIX, data->Rotation.y);
			njCalcPoint(&offset, &output, CURRENT_MATRIX);
			njPopMatrixEx();

			EnemyBounceThing(0, output.x, output.y, output.z);
			
			data->Scale.y = 5.0f;
		}

		data->Scale.x = 0.0f;
		info->Speed = 0;
		data->field_6 = 0;
		data->Scale.z = 0.0f;
	}
}

void Turnasi_CheckSub(EntityData1* data, turnasiwk* info)
{
	if (data->Index == 10)
	{
		if (info->Speed >= 1.5f)
		{
			// PlaySound
			
			data->Action = Turnasi_Send;

			if (info->Speed >= 4.0f)
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
		}
	}
}

void __cdecl Turnasi_Display(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity; // esi
	NJS_OBJECT* child = TurnAsi->getmodel()->child;
	NJS_OBJECT* childChild = TurnAsi->getmodel()->child->child;

	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrixEx();
	njTranslateEx(&data->Position);
	njRotateY_(CURRENT_MATRIX, data->Rotation.y);
	njRotateX_(CURRENT_MATRIX, data->Rotation.x);
	DrawChunkModel(TurnAsi->getmodel()->getchunkmodel());
	
	njTranslateEx((NJS_VECTOR*)&child->pos);
	DrawChunkModel(child->getchunkmodel());

	njTranslateEx((NJS_VECTOR*)&childChild->pos);
	njRotateX_(CURRENT_MATRIX, -data->Rotation.x);
	DrawChunkModel(childChild->getchunkmodel());
	njPopMatrixEx();
}

void __cdecl Turnasi_Main(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	turnasiwk* info = (turnasiwk*)obj->UnknownA_ptr;
	
	switch (data->Action)
	{
	case Turnasi_Check:
		Turnasi_CheckSub(data, info);
		break;
	case Turnasi_Send:
		Turnasi_SendSub(data, info, obj->Child);
		break;
	case Turnasi_Reset:
		Turnasi_ResetSub(data);
		break;
	case Turnasi_Delete:
		UpdateSetDataAndDelete(obj);
		return;
	}

	AddToCollisionList(obj);
}

void __cdecl LoadTurnAsi(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	LoadChildObject((LoadObj)(LoadObj_UnknownA | LoadObj_Data1 | LoadObj_Data2), TurnAsi_Trigger, obj);

	InitCollision(obj, TurnAsiCol, 7, 4);

	data->Collision->Range = 100.0f;

	obj->MainSub = Turnasi_Main;
	obj->DisplaySub = Turnasi_Display;
	obj->DeleteSub = j_DeleteChildObjects;
}

void FreeModel_TurnAsi()
{
	FreeMDL(TurnAsi);
}

void LoadModel_TurnAsi()
{
	TurnAsi = LoadMDL("SH-TurnAsi", ModelFormat_Chunk);
}
