#pragma once

void LoadModelsSH();
void FreeModelsSH();

extern ObjectListHead SpeedHighwayObjListH;
extern NJS_TEXLIST highwayObj_TEXLIST;
extern NJS_TEXLIST highwayObj2_TEXLIST;
void LoadModel_TurnAsi();
void OTurnasi(ObjectMaster* obj);
void __cdecl LoadTurnAsi(ObjectMaster* obj);
void LoadHelicoModel();
void Load_Helico(ObjectMaster* a1);
void __cdecl OHelia(ObjectMaster* obj);
void __cdecl OHelib(ObjectMaster* obj);
void FreeModel_TurnAsi();

void __cdecl GenericSHDisplay_RotY(ObjectMaster* obj);
void LoadModel_Oev();
void __cdecl OEv(ObjectMaster* obj);
void __cdecl SH_EVChild(ObjectMaster* a2);