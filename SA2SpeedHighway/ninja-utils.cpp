#include "pch.h"

void njCnkAction(NJS_ACTION* action, float frame)
{
	*(int*)0x25EFE54 = 0x25EFE60;
	njSetMotion(action->motion, frame);
	MotionDrawCallback = (ObjectFuncPtr)0x42E660;
	DrawObjMotion(action->object);
}

void njCnkMotion(NJS_OBJECT* obj, NJS_MOTION* mot, float frame)
{
	*(int*)0x25EFE54 = 0x25EFE60;
	njSetMotion(mot, frame);
	MotionDrawCallback = (ObjectFuncPtr)0x42E660;
	DrawObjMotion(obj);
}

void njAddVector(NJS_VECTOR* vd, NJS_VECTOR* vs)
{
	vd->x += vs->x;
	vd->y += vs->y;
	vd->z += vs->z;
}

void njRotateZXY(Rotation* rot)
{
	njRotateZ_(CURRENT_MATRIX, rot->z);
	njRotateX(CURRENT_MATRIX, rot->x);
	njRotateY(CURRENT_MATRIX, rot->y);
}

void njRotateXYZ(Rotation* rot)
{
	njRotateX(CURRENT_MATRIX, rot->x);
	njRotateY(CURRENT_MATRIX, rot->y);
	njRotateZ_(CURRENT_MATRIX, rot->z);
}

void njTranslateX(float x)
{
	njTranslate(CURRENT_MATRIX, x, 0.0f, 0.0f);
}

void njTranslateY(float y)
{
	njTranslate(CURRENT_MATRIX, 0.0f, y, 0.0f);
}

void njTranslateZ(float z)
{
	njTranslate(CURRENT_MATRIX, 0.0f, 0.0f, z);
}