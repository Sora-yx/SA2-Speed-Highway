#include "pch.h"


static ModelInfo* SH_Hyd;

CollisionData HydCol = { 0, CollisionShape_Cyl1, 0x20, 0xE0, 0, {0}, 2.5, 10.0, 0.0, 0.0, 0, 0, 0 };




void HydBass_Main(ObjectMaster* obj)
{
	EntityData1* data; // r31
	EntityData1* P1; // r29
	CollisionInfo* col; // r11


	data = obj->Data1.Entity;

	if (ClipSetObject(obj))
		return;

	P1 = MainCharObj1[0];

	if (!P1)
		return;

	col = data->Collision;

	if (!col)
		return;

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
		obj->MainSub = HydBass_Main;
	}
}


void FreeHydModel() {
	FreeMDL(SH_Hyd);
	return;
}

void LoadHydModel() {
	SH_Hyd = LoadMDL("sh-hyd", ModelFormat_Chunk);
	return;
}