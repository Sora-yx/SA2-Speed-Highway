#pragma once

void njCnkAction(NJS_ACTION* action, float frame);
void njCnkMotion(NJS_OBJECT* obj, NJS_MOTION* mot, float frame);
void njAddVector(NJS_VECTOR* vd, NJS_VECTOR* vs);
void njRotateZXY(Rotation* rot);
void njRotateXYZ(Rotation* rot);
void njTranslateX(float x);
void njTranslateY(float Y);
void njTranslateZ(float Z);