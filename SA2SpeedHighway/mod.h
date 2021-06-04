#pragma once

#define MAXPLAYERS 2

extern HelperFunctions HelperFunctionsGlobal;
extern LoopHead* PathList_SpeedHighway0[];
extern int CurrentAct;

void LoadSHAct(int act);
void SHControlActTrigger(ObjectMaster* obj);
void SetSonicRunningOnBulding(ObjectMaster* a1);