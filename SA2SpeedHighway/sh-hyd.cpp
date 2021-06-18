#include "pch.h"


static ModelInfo* SH_Hyd;


CollisionData HydCol = { 0, CollisionShape_Cyl1, 0x20, 0xE0, 0, {0}, 2.5, 10.0, 0.0, 0.0, 0, 0, 0 };

particle_info ParticleSprite = { 1.0, 0.037999999, 0.19, 0.115, 0.025, {0}, {0}, { 1.0, 1.0, 1.0, 1.0} };


/*void __cdecl HydChild(ObjectMaster* a1)
{
	EntityData1* data; // esi

	data = a1->Data1.Entity;
	if (!ClipSetObject(a1))
	{
		if (data->Action)
		{
			if (data->Action == 1)
			{
				//ByeByeHyd(data);
			}
			else
			{
				if (data->Action == 3)
				{
					a1->MainSub = DeleteObject_;
				}
				else
				{
					data->Action = 0;
				}
			}
		}
		else
		{
			data->Action = 1;
			//ByeByeHyd(data);
			data->field_6 = 0;
		}
	}
}

void __cdecl CreateWater(NJS_VECTOR* position, NJS_VECTOR* scale_v, float scale)
{
	sp_task* spriteWater; // eax
	sp_task* spriteWaterCopy; // esi
	float v5; // eax

	//spriteWater = AllocateParticle(stru_97E26C.data, EffectWater);
//	spriteWaterCopy = spriteWater;
	if (spriteWater)
	{
		spriteWater->pos = *position;
		spriteWater->spd.x = scale_v->x;
		spriteWater->spd.y = scale_v->y;
		v5 = scale_v->z;
		spriteWaterCopy->scl = scale * 0.17;
		spriteWaterCopy->spd.z = v5;
		spriteWaterCopy->frame = (double)rand() * 0.000030517578 * 5.0;
		spriteWaterCopy->ang = (unsigned __int64)(((double)rand() * 0.000030517578 * 160.0 + 100.0)
			* 65536.0
			* 0.002777777777777778);
		spriteWaterCopy->argb = ParticleSprite.argb;
		spriteWaterCopy->work[0] = (sp_task*)&ParticleSprite;
	}
}

void __cdecl Hyd_HitMain(ObjectMaster* a1)
{
	EntityData1* data; // esi
	NJS_VECTOR a2; // [esp+Ch] [ebp-Ch] BYREF

	data = a1->Data1.Entity;

	a2.x = 0.0;
	a2.y = 1.0;
	a2.z = 0.0;
	CreateWater(&data->Position, &a2, 0.2);
	//Hyd_Display(a1);
	//QueueSound_XYZ(121, v1, 1, 0, 2, v1->Position.x, v1->Position.y, v1->Position.z);
}

/*void __fastcall HydBass_Main(ObjectMaster* obj)
{
	EntityData1* data; // r31
	EntityData1* P1; // r29
	CollisionInfo* col; // r11
	unsigned __int16 v5; // r10
	double resultPosY; // fp31
	ObjectMaster* child; // r3
	EntityData1* childData; // r30
	double getSpeed; // fp13
	NJS_POINT3 speed; // [sp+50h] [-40h] BYREF

	data = obj->Data1.Entity;

	if (ClipSetObject(obj))
		return;

	P1 = MainCharObj1[0];

	if (!P1)
		return;

	col = data->Collision;

	if (!col)
		return;

	v5 = col->Flag;
	if ((v5 & 1) != 0)
	{
		col->Flag = v5 & 0xFFFE;
		resultPosY = (float)(data->Position.y - P1->Position.y);
		GetPlayerRunningSpeed(0, speed.x);
		if (speed.x > 0.64999998 && resultPosY < 5.0)
		{
			child = LoadChildObject(LoadObj_Data1, HydChild, obj);
			if (child)
			{
				childData = child->Data1.Entity;
				childData->Rotation.y = (int)(atan2(
					(float)(data->Position.x - P1->Position.x),
					(float)(data->Position.z - P1->Position.z))
					* 65536.0
					* 0.1591549762031479);
				getSpeed = speed.x;
				if (speed.x > 2.0)
				{
					speed.x = 2.0;
					getSpeed = 2.0;
				}
				childData->Scale.x = getSpeed;
				childData->Position.x = data->Position.x;
				childData->Position.y = data->Position.y;
				childData->Position.z = data->Position.z;
				//obj->MainSub = (void(__cdecl*)(task*))Hit;
				data->Action = 2;
				//dsPlay_oneshot(120, 0, 0, 0);
			}
		}
	}
	AddToCollisionList(obj);
}



void __cdecl Hyd_Display(ObjectMaster* a2)
{
	EntityData1* data; // esi
	Angle v2; // eax

	data = a2->Data1.Entity;

	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrix(0);
	njTranslate(0, data->Position.x, data->Position.y, data->Position.z);
	v2 = data->Rotation.y;
	if (v2)
	{
		njRotateY(0, (unsigned __int16)v2);
	}
	if (data->Action == 2)
	{
		DrawChunkModel(SH_Hyd->getmodel()->child->getchunkmodel());
	}
	else
	{
		DrawObject((NJS_OBJECT*)a2->field_4C);
	}
	njPopMatrix(1u);
}

void __cdecl OHydbass(ObjectMaster* obj)
{
	EntityData1* data; // edi

	data = obj->Data1.Entity;
	if (!ClipSetObject(obj))
	{
		obj->field_4C = SH_Hyd->getmodel();
		InitCollision(obj, &HydCol, 1, 4u);
		data->Collision->Range = 11.0f;

		obj->DisplaySub = Hyd_Display;
		obj->MainSub = (ObjectFuncPtr)HydBass_Main;
	}
}*/


void FreeHydModel() {
	FreeMDL(SH_Hyd);
	return;
}

void LoadHydModel() {
	SH_Hyd = LoadMDL("sh-hyd", ModelFormat_Chunk);
	return;
}