#pragma once

#define MAXPLAYERS 2
#define CURRENT_MATRIX _nj_current_matrix_ptr_

extern HelperFunctions HelperFunctionsGlobal;
extern ObjectListHead SpeedHighwayObjListH;

#pragma pack(push, 1)
struct EntityData2_R
{
	NJS_POINT3 spd;
	NJS_POINT3 acc;
	Rotation ang_aim;
	Rotation ang_spd;
	float force;
	float accel;
	float frict;
};
#pragma pack(pop)

// Chaos Drive Function Pointers
DataPointer(void*, dword_1DE4680, 0x1DE4680);
DataPointer(void*, dword_1DE4684, 0x1DE4684);
DataPointer(void*, dword_1DE4688, 0x1DE4688);
DataPointer(void*, dword_1DE468C, 0x1DE468C);

DataPointer(int, PerfectRings_StartCount, 0x174B030);

FunctionPointer(void, DrawObject, (NJS_OBJECT* a1), 0x42E730);
VoidFunc(FreeSETObjects, 0x4889B0);
VoidFunc(DeleteMostObject, 0x470AE0);
ObjectFunc(LoopController, 0x497B50);
ObjectFunc(RailController, 0x4980C0);

extern LoopHead* PathList_SpeedHighway0[];
extern int CurrentAct;

void LoadSHAct(int act);
void SHControlActTrigger(ObjectMaster* obj);
void SetSonicRunningOnBulding(ObjectMaster* a1);

void PlayerGetSpeed(EntityData1* a1, CharObj2Base* co2, EntityData2* data2);
int PlayerSetPosition(EntityData1* a1, EntityData2* a2, CharObj2Base* a3);
void PlayerResetPosition(EntityData1* a1, EntityData2* a2, CharObj2Base* a3);
void PlayerResetAngle(EntityData1* a1, CharObj2Base* co2);
void PlayerGetAccelerationAir(EntityData1* a1, CharObj2Base* co2, EntityData2* data2);
void __fastcall PGetAccelerationForBuilding(EntityData1* twp, EntityData2_R* mwp, CharObj2Base* pwp);
void __cdecl PResetPositionForBuilding(EntityData1* a1, EntityData2_R* a2, CharObj2Base* a3);
void PConvertVector_P2G(EntityData1* a1, NJS_VECTOR* a2);
void __cdecl PResetAngleForBuilding(EntityData1* a1, EntityData2_R* _18, CharObj2Base* a3);
void Init_Sonic();
signed int Sonic_CheckJump(EntityData1* data, CharObj2Base* a2, SonicCharObj2* a3);
void LoadCrashStar(int player);
int __fastcall AdjustAngle(int ang0, int ang1, int dang);
bool CheckPlayerFall(CharObj2Base* status, EntityData1* _entity);