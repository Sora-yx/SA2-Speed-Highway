#pragma once

#define CURRENT_MATRIX _nj_current_matrix_ptr_

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
void njAddVectorSADX(NJS_VECTOR* vd, const NJS_VECTOR* vs);
int BAMS_Subtract(int a1, int a2);
float njInnerProduct(const NJS_VECTOR* v1, const NJS_VECTOR* v2);
void njGetTranslation(NJS_MATRIX_PTR matrix, NJS_VECTOR* out);
float VectorMaxAbs(NJS_VECTOR* y);