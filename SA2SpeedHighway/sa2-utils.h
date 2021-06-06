#pragma once

// Stuff from the game's code, missing from the Mod Loader includes

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


FunctionPointer(void, DrawObject, (NJS_OBJECT* a1), 0x42E730);


struct pathinfo
{
	int slangx;
	int slangz;
	int slangax;
	int slangaz;
	float onpathpos;
	NJS_POINT3 pos;
	float xpos;
	float ypos;
	float zpos;
	NJS_POINT3 normal;
	NJS_POINT3 normala;
	NJS_POINT3 front;
};

FunctionPointer(int, GetStatusOnPath, (LoopHead* a1, pathinfo* a2), 0x4905A0);