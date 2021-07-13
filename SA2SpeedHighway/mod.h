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

#pragma pack(push, 8)
struct __declspec(align(2)) ObjectThing
{
	void(__cdecl* func)(ObjectMaster*);
	__int16 flags;
	__int16 status;
	Rotation rotation;
	NJS_VECTOR pos_probably;
	NJS_OBJECT* object;
};
#pragma pack(pop)