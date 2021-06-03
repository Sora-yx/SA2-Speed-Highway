#include "pch.h"

static const void* const PGetAccelAirPtr = (void*)0x45D770;
static inline void PlayerGetAccelerationAirASM(EntityData1* a1, CharObj2Base* co2, EntityData2* data2)
{
	__asm
	{
		push[data2]
		mov eax, [co2]
		mov ecx, a1 // a1

		// Call your __cdecl function here:
		call PGetAccelAirPtr

		add esp, 4 // a3
	}
}

void PlayerGetAccelerationAir(EntityData1* a1, CharObj2Base* co2, EntityData2* data2) {
	return PlayerGetAccelerationAirASM(a1, co2, data2);
}

static const void* const PResetAnglePtr = (void*)0x460260;
static inline void PlayerResetAngleASM(EntityData1* a1, CharObj2Base* co2)
{
	__asm
	{
		mov ebx, [co2]
		mov eax, [a1] // a1
		call PResetAnglePtr
	}
}

void PlayerResetAngle(EntityData1* a1, CharObj2Base* co2)
{
	return PlayerResetAngleASM(a1, co2);
}


static const void* const PGetSpeedPtr = (void*)0x460860;
static inline void PlayerGetSpeedASM(EntityData1* a1, CharObj2Base* co2, EntityData2* data2)
{
	__asm
	{
		push[data2] // a3
		mov ebx, co2 // a2
		mov eax, a1 // a1

		// Call your __cdecl function here:
		call PGetSpeedPtr

		add esp, 4 // a3
	}
}

void PlayerGetSpeed(EntityData1* a1, CharObj2Base* co2, EntityData2* data2)
{
	PlayerGetSpeedASM(a1, co2, data2);
}

static const void* const PSetPositionptr = (void*)0x4616E0;
static inline int PSetPositionASM(EntityData1* a1, EntityData2* a2, CharObj2Base* a3)
{
	int result;
	__asm
	{
		push[a3]
		push[a2]
		mov eax, [a1]
		call PSetPositionptr
		add esp, 8
		mov result, eax
	}
	return result;
}

int PlayerSetPosition(EntityData1* a1, EntityData2* a2, CharObj2Base* a3)
{
	return PSetPositionASM(a1, a2, a3);
}

static const void* const sub_469050Ptr = (void*)0x469050;
static inline void PResetPositionASM(EntityData1* a1, EntityData2* a2, CharObj2Base* a3)
{
	__asm
	{
		push[a3] // a3
		mov ebx, a2 // a2
		mov eax, a1 // a1
		call sub_469050Ptr
		add esp, 4 // a2
	}
}

void PlayerResetPosition(EntityData1* a1, EntityData2* a2, CharObj2Base* a3) {
	PResetPositionASM(a1, a2, a3);
}