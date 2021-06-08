#pragma once

void PlayerGetSpeed(EntityData1* a1, CharObj2Base* co2, EntityData2* data2);
int PlayerSetPosition(EntityData1* a1, EntityData2* a2, CharObj2Base* a3);
void PlayerResetPosition(EntityData1* a1, EntityData2* a2, CharObj2Base* a3);
void PlayerResetAngle(EntityData1* a1, CharObj2Base* co2);
void PlayerGetAccelerationAir(EntityData1* a1, CharObj2Base* co2, EntityData2* data2);
void __fastcall PGetAccelerationForBuilding(EntityData1* twp, EntityData2_R* mwp, CharObj2Base* pwp);
void __cdecl PResetPositionForBuilding(EntityData1* a1, EntityData2_R* a2, CharObj2Base* a3);
void PConvertVector_P2G(EntityData1* a1, NJS_VECTOR* a2);
void __cdecl PResetAngleForBuilding(EntityData1* a1, EntityData2_R* _18, CharObj2Base* a3);
signed int Sonic_CheckJump(EntityData1* data, CharObj2Base* a2, SonicCharObj2* a3);
bool CheckPlayerFall(CharObj2Base* status, EntityData1* _entity);
int PSetPositionForBuilding(EntityData1* a1, EntityData2_R* a2, CharObj2Base* a3);