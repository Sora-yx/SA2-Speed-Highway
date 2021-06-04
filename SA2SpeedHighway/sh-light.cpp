#include "pch.h"
#include "objects.h"
#include "sh-light.h"

ModelInfo* SH_SLight = nullptr;

static CollisionData Col_SLight = { 0, (CollisionShapes)0x6, 0x77, 0, 0, {0.0f, 15.0f, 0.0f}, 7.0f, 7.0f, 0.0f, 0.0f, 0, 0, 0 };

void SHSlight_DisplayLight(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrixEx();
	njTranslateEx(&data->Position);
	njRotateY(CURRENT_MATRIX, data->Rotation.y);
	njTranslateEx((NJS_VECTOR*)&SH_SLight->getmodel()->child->pos);
	njRotateZ_(CURRENT_MATRIX, static_cast<Angle>(njSin((static_cast<float>(FrameCountIngame) * 65536.0f * 0.00278f)) * 23.0f * 65536.0f * 0.002777777777777778f));
	njRotateY(CURRENT_MATRIX, data->Rotation.y);
	njTranslateEx((NJS_VECTOR*)&SH_SLight->getmodel()->child->child->pos);
	DrawChunkModel(SH_SLight->getmodel()->child->child->chunkmodel);
	njPopMatrixEx();
}

void SHSlight_Display(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrixEx();
	njTranslateEx(&data->Position);
	njRotateY(CURRENT_MATRIX, data->Rotation.y);
	DrawChunkModel(SH_SLight->getmodel()->chunkmodel);
	njTranslateEx((NJS_VECTOR*)&SH_SLight->getmodel()->child->pos);
	njRotateZ_(CURRENT_MATRIX, static_cast<Angle>(njSin((static_cast<float>(FrameCountIngame) * 65536.0f * 0.00278f)) * 23.0f * 65536.0f * 0.002777777777777778f));
	njRotateY(CURRENT_MATRIX, data->Rotation.y);
	DrawChunkModel(SH_SLight->getmodel()->child->chunkmodel);
	njPopMatrixEx();
}

void SHSlight_Main(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	if (!ClipSetObject(obj))
	{
		AddToCollisionList(obj);
		ObjectSetupInput(data, nullptr);
	}
}

void __cdecl SHSLIGHT(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	InitCollision(obj, &Col_SLight, 1, 4u);
	data->Collision->Range = 25.0f;

	obj->DisplaySub = SHSlight_Display;
	obj->SomethingSub = SHSlight_DisplayLight;
	obj->MainSub = SHSlight_Main;
}