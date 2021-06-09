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

int __cdecl BAMS_Subtract(int a1, int a2)
{
	int result; // eax

	(result) = a2 - a1;
	if ((__int16)(a2 - a1) < 0)
	{
		(result) = a1 - a2;
	}
	return (unsigned __int16)result;
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

void __fastcall njTranslateVSADX(NJS_MATRIX_PTR m, const NJS_VECTOR* v)
{
	double x; // st7
	NJS_MATRIX_PTR _m; // eax
	double y; // st6
	double z; // st5

	x = v->x;
	_m = m;
	y = v->y;
	z = v->z;
	if (!m)
	{
		_m = _nj_current_matrix_ptr_;
	}
	_m[M30] = z * _m[M20] + y * _m[M10] + x * *_m + _m[M30];
	_m[M31] = z * _m[M21] + y * _m[M11] + x * _m[M01] + _m[M31];
	_m[M32] = z * _m[M22] + y * _m[M12] + x * _m[M02] + _m[M32];
	_m[M33] = z * _m[M23] + y * _m[M13] + x * _m[M03] + _m[M33];
}

void __fastcall njCalcVectorSADX(NJS_MATRIX_PTR m, const NJS_VECTOR* vs, NJS_VECTOR* vd)
{
	double vsx; // st7
	NJS_MATRIX_PTR _m; // eax
	double vsy; // st6
	double vsz; // st5
	double length; // st7
	float magnitude; // [esp+0h] [ebp-10h]
	float vdy; // [esp+8h] [ebp-8h]
	float vdz; // [esp+Ch] [ebp-4h]
	float vdx; // [esp+14h] [ebp+4h]

	vsx = vs->x;
	_m = m;
	vsy = vs->y;
	vsz = vs->z;
	if (!m)
	{
		_m = _nj_current_matrix_ptr_;
	}
	vd->x = vsz * _m[M20] + vsy * _m[M10] + vsx * *_m;
	vd->y = vsz * _m[M21] + vsy * _m[M11] + vsx * _m[M01];
	vd->z = vsz * _m[M22] + vsy * _m[M12] + vsx * _m[M02];

}


void __fastcall njAddVectorSADX(NJS_VECTOR* vd, const NJS_VECTOR* vs)
{
	vd->x = vd->x + vs->x;
	vd->y = vs->y + vd->y;
	vd->z = vs->z + vd->z;
}

float __fastcall njInnerProduct(const NJS_VECTOR* v1, const NJS_VECTOR* v2)
{
	return v1->z * v2->z + v1->y * v2->y + v1->x * v2->x;
}

float __cdecl VectorMaxAbs(NJS_VECTOR* y)
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