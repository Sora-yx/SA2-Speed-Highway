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


static const void* const PConvertVP2GPtr = (void*)0x468E70;
static inline void PConvertVector_P2GASM(EntityData1* a1, NJS_VECTOR* a2)
{
	__asm
	{
		mov esi, [a2]
		mov edi, [a1] // a1
		call PConvertVP2GPtr
	}
}

void PConvertVector_P2G(EntityData1* a1, NJS_VECTOR* a2) {
	return PConvertVector_P2GASM(a1, a2);
}

static const void* const PConvertVPtr = (void*)0x468DF0;
static inline void PConvertVector_G2PASM(EntityData1* a1, NJS_VECTOR* a2)
{
	__asm
	{
		mov esi, [a2]
		mov edi, [a1]
		call PConvertVPtr
	}
}

void PConvertVector_G2P(EntityData1* a1, NJS_VECTOR* a2) {
	return PConvertVector_G2PASM(a1, a2);
}

void __fastcall njCalcPointSADX(NJS_MATRIX_PTR m, const NJS_VECTOR* vs, NJS_VECTOR* vd)
{
	const float* _m; // eax
	double z; // st5
	double y; // st6
	double x; // st7

	x = vs->x;
	_m = m;
	y = vs->y;
	z = vs->z;
	if (!m)
	{
		_m = _nj_current_matrix_ptr_;
	}
	vd->x = z * _m[M20] + y * _m[M10] + x * *_m + _m[M30];
	vd->y = z * _m[M21] + y * _m[M11] + x * _m[M01] + _m[M31];
	vd->z = z * _m[M22] + y * _m[M12] + x * _m[M02] + _m[M32];
}

void njTranslateSADX(NJS_MATRIX_PTR m, Float x, Float y, Float z)
{
	NJS_MATRIX_PTR v4; // eax

	v4 = m;
	if (!m)
	{
		v4 = _nj_current_matrix_ptr_;
	}
	v4[12] = y * v4[4] + z * v4[8] + x * *v4 + v4[12];
	v4[13] = x * v4[1] + y * v4[5] + z * v4[9] + v4[13];
	v4[14] = x * v4[2] + y * v4[6] + z * v4[10] + v4[14];
	v4[15] = x * v4[3] + y * v4[7] + z * v4[11] + v4[15];
}
