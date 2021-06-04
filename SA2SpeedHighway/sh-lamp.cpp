#include "pch.h"
#include "objects.h"
#include "sh-lamp.h"

ModelInfo* SH_Lamp[2];


static CollisionData Col_Lamp01 = { 0, CollisionShape_Cyl1, 0x77, 0, 0, {0.0, 22.0, 0.0}, 3.0, 22.0, 0.0, 0.0, 0, 0, 0 };

void __cdecl Lamp_DisplayLight(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* object = (NJS_OBJECT*)obj->field_4C;

	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrixEx();
	njTranslateEx(&data->Position);
	njRotateZXY(&data->Rotation);
	njTranslateEx((NJS_VECTOR*)&object->child->pos);
	njRotateZ_(CURRENT_MATRIX, object->child->ang[2]);
	DrawChunkModel(object->child->chunkmodel);
	njPopMatrixEx();
}

void __cdecl Lamp_Display(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* object = (NJS_OBJECT*)obj->field_4C;
	
	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrixEx();
	njTranslateEx(&data->Position);
	njRotateZXY(&data->Rotation);
	DrawChunkModel(object->chunkmodel);
	njPopMatrixEx();
}

void  __cdecl Lamp_Main(ObjectMaster* obj)
{
	if (!ClipSetObject(obj))
	{
		AddToCollisionList(obj);
		obj->Data1.Entity->Status &= 0xC7u;
	}
}

void  __cdecl SHLAMP01(ObjectMaster* obj)
{
	obj->MainSub = Lamp_Main;
	obj->DisplaySub = Lamp_Display;
	obj->field_1C = Lamp_DisplayLight;
	obj->field_4C = SH_Lamp[0]->getmodel();
	obj->Data1.Entity->Status |= 0x8000u;

	InitCollision(obj, &Col_Lamp01, 1, 4u);
}

void  __cdecl SHLAMP02(ObjectMaster* obj)
{
	obj->MainSub = Lamp_Main;
	obj->DisplaySub = Lamp_Display;
	obj->field_1C = Lamp_DisplayLight;
	obj->field_4C = SH_Lamp[1]->getmodel();
	obj->Data1.Entity->Status |= 0x8000u;

	InitCollision(obj, &Col_Lamp01, 1, 4u);
}

void LoadLampModel() {
	SH_Lamp[0] = LoadMDL("SH-Lamp01", ModelFormat_Chunk);
	SH_Lamp[1] = LoadMDL("SH-Lamp02", ModelFormat_Chunk);
}