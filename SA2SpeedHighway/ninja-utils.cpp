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
	njRotateZ(CURRENT_MATRIX, rot->z);
	njRotateX(CURRENT_MATRIX, rot->x);
	njRotateY(CURRENT_MATRIX, rot->y);
}

void njRotateXYZ(Rotation* rot)
{
	njRotateX(CURRENT_MATRIX, rot->x);
	njRotateY(CURRENT_MATRIX, rot->y);
	njRotateZ(CURRENT_MATRIX, rot->z);
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

int BAMS_Subtract(int a1, int a2)
{
	int result; // eax

	(result) = a2 - a1;
	if ((__int16)(a2 - a1) < 0)
	{
		(result) = a1 - a2;
	}
	return (unsigned __int16)result;
}

void njAddVectorSADX(NJS_VECTOR* vd, const NJS_VECTOR* vs)
{
	vd->x = vd->x + vs->x;
	vd->y = vs->y + vd->y;
	vd->z = vs->z + vd->z;
}

float njInnerProduct(const NJS_VECTOR* v1, const NJS_VECTOR* v2)
{
	return v1->z * v2->z + v1->y * v2->y + v1->x * v2->x;
}

float VectorMaxAbs(NJS_VECTOR* y)
{
	double result; // st7
	float x; // [esp+0h] [ebp-4h]
	float v4; // [esp+8h] [ebp+4h]

	x = fabs(y->x);
	v4 = fabs(y->y);
	result = fabs(y->z);
	if (x <= (double)v4)
	{
		if (v4 > result)
		{
			result = v4;
		}
	}
	else if (x > result)
	{
		result = x;
	}
	return result;
}

void njGetTranslation(NJS_MATRIX_PTR matrix, NJS_VECTOR* out)
{
	if (!matrix)
	{
		matrix = CURRENT_MATRIX;
	}

	out->x = matrix[3];
	out->y = matrix[7];
	out->z = matrix[11];
}