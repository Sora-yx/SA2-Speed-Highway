#pragma once

#define CURRENT_MATRIX _nj_current_matrix_ptr_

static const void* const DrawChunkModelPtr = (void*)0x42E6C0;
static inline void DrawChunkModel(NJS_CNK_MODEL* a1)
{
	__asm
	{
		mov eax, [a1]
		call DrawChunkModelPtr
	}
}

void njCnkAction(NJS_ACTION* action, float frame);
void njCnkMotion(NJS_OBJECT* obj, NJS_MOTION* mot, float frame);
void njAddVector(NJS_VECTOR* vd, NJS_VECTOR* vs);
void njRotateZXY(Rotation* rot);
void njRotateXYZ(Rotation* rot);
void njTranslateX(float x);
void njTranslateY(float Y);
void njTranslateZ(float Z);
int AdjustAngle(int ang0, int ang1, int dang);
int SubAngle(int ang0, int ang1);
int BAMS_SubWrap(__int16 bams_a, unsigned __int16 bams_b, int limit);
void PConvertVector_G2P(EntityData1* a1, NJS_VECTOR* a2);
void PConvertVector_P2G(EntityData1* a1, NJS_VECTOR* a2);
void __fastcall njCalcPointSADX(NJS_MATRIX_PTR m, const NJS_VECTOR* vs, NJS_VECTOR* vd);
void njTranslateSADX(NJS_MATRIX_PTR m, Float x, Float y, Float z);