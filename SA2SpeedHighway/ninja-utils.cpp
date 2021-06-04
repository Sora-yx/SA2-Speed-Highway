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

int SubAngle(int ang0, int ang1)
{
	return (__int16)(ang1 - ang0);
}

int AdjustAngle(int ang0, int ang1, int dang)
{
	__int16 v3; // r11
	int result; // r3
	int v5; // r9
	unsigned __int16 v6; // r11

	v3 = ang0;
	result = (unsigned __int16)ang1;
	v5 = (__int16)(ang1 - v3);
	if (v5 > dang || v5 < -dang)
	{
		if ((v5 & 0x8000) != 0)
			v6 = v3 - dang;
		else
			v6 = v3 + dang;
		result = v6;
	}
	return result;
}

int BAMS_SubWrap(__int16 bams_a, unsigned __int16 bams_b, int limit)
{
	int result; // eax
	__int16 v4; // cx

	result = bams_b;
	v4 = bams_b - bams_a;
	if ((__int16)(bams_b - bams_a) > limit || v4 < -limit)
	{
		if (v4 >= 0)
		{
			result = (unsigned __int16)(limit + bams_a);
		}
		else
		{
			result = (unsigned __int16)(bams_a - limit);
		}
	}
	return result;
}