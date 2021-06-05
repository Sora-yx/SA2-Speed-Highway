#pragma once

void LoadModelsSH();
void FreeModelsSH();

extern ObjectListHead SpeedHighwayObjListH;
extern NJS_TEXLIST highwayObj_TEXLIST;
extern NJS_TEXLIST highwayObj2_TEXLIST;
void LoadModel_TurnAsi();
void OTurnasi(ObjectMaster* obj);
void __cdecl LoadTurnAsi(ObjectMaster* obj);