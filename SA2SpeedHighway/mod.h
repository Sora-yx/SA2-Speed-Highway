#pragma once

#define MAXPLAYERS 2

extern HelperFunctions HelperFunctionsGlobal;
extern ObjectListHead SpeedHighwayObjListH;

// Chaos Drive Function Pointers
DataPointer(void*, dword_1DE4680, 0x1DE4680);
DataPointer(void*, dword_1DE4684, 0x1DE4684);
DataPointer(void*, dword_1DE4688, 0x1DE4688);
DataPointer(void*, dword_1DE468C, 0x1DE468C);

FunctionPointer(void, DrawObject, (NJS_OBJECT* a1), 0x42E730);
VoidFunc(FreeSETObjects, 0x4889B0);
VoidFunc(DeleteMostObject, 0x470AE0);
ObjectFunc(LoopController, 0x497B50);
ObjectFunc(RailController, 0x4980C0);

extern LoopHead* PathList_SpeedHighway0[];
extern int CurrentAct;

void LoadSHAct(int act);
void SHControlActTrigger(ObjectMaster* obj);
void Objects_Init();