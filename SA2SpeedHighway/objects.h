#pragma once

void Objects_Init();
void LoadObjSHTex();
void LoadModelsSH();
ObjectFunc(ObjectFunc_DynColDelete, 0x5F12B0);
FunctionPointer(NJS_OBJECT*, GetFreeDynObject, (), 0x47D7F0);
void LoadCraneModels();
void __cdecl OCrane(ObjectMaster* obj);
void __cdecl RingGroup(ObjectMaster* obj);
void __cdecl sub_46C150(ObjectMaster* a1);
void LoadSHGlass();
void __cdecl OGlass(ObjectMaster* obj);