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
void __cdecl GenericSHDisplayZXY(ObjectMaster* obj);
void LoadModel_Oev();
void __cdecl OEv(ObjectMaster* obj);
void __cdecl SH_EVChild(ObjectMaster* a2);
void Load_NeonAssets();
void Free_Neon();

void __cdecl ONeon1(ObjectMaster* obj);
void __cdecl ONeon2(ObjectMaster* obj);
void __cdecl ONeon3(ObjectMaster* obj);
void __cdecl ONeon4(ObjectMaster* obj);

void Load_SH_Car(ObjectMaster* a1);
void __cdecl OEscalator2(ObjectMaster* obj);

void __cdecl OEscalator1(ObjectMaster* obj);
void LoadBellModels();

void LoadConeModels();

void LoadArcadesModels();
void __cdecl OArcade03(ObjectMaster* obj);
void __cdecl OArcade02(ObjectMaster* obj);
void __cdecl OArcade01(ObjectMaster* obj);
void FreeArcadesModels();
void __cdecl OPoster2(ObjectMaster* obj);
void __cdecl OPoster1(ObjectMaster* obj);

void __cdecl OPoster0(ObjectMaster* obj);

void FreePosterModels();

void LoadPosterModels();
void FreeTokeiModels();
void LoadTokeiModels();
void __cdecl OTokei(ObjectMaster* obj);

void __cdecl OGreene(ObjectMaster* obj);
void __cdecl OGreend(ObjectMaster* obj);
void __cdecl OGreenb(ObjectMaster* obj);
void __cdecl OGreena(ObjectMaster* obj);
void __cdecl OGreen(ObjectMaster* obj);
void FreeGreenModels();
void LoadGreenModels();
void __cdecl OPost4(ObjectMaster* obj);
void __cdecl OPost1(ObjectMaster* obj);
void LoadSH_EscalatorsModels();
void __cdecl SH_GlobalMainWithCalcRot(ObjectMaster* a1);
void __cdecl OGgrend(ObjectMaster* obj);
void __cdecl OGgrenb(ObjectMaster* obj);
void __cdecl OGgrena(ObjectMaster* obj);

void __cdecl OHydbass(ObjectMaster* obj);
void FreeHydModel();
void LoadHydModel();

void __cdecl OGclight(ObjectMaster* obj);
void LoadClightModel();

void FreeClightModel();
void LoadTrashModels();
void __cdecl OTanka(ObjectMaster* obj);

void LoadSignBModels();
void __cdecl OSignb(ObjectMaster* obj);

void __cdecl Beetle_Attack2(ObjectMaster* a1);