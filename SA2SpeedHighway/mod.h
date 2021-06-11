#pragma once

#define MAXPLAYERS 2

extern HelperFunctions HelperFunctionsGlobal;

extern int CurrentAct;

void CheckAndSetControl(ObjectMaster* obj);
void CheckAndKillPlayer(ObjectMaster* obj);

struct RotInfo
{
	int info01;
	int info02;
	int info03;
};

struct FloatInfo
{
	float info01;
	float info03;
};