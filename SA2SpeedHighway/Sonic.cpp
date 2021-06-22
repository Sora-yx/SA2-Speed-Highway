#include "pch.h"
#include "PhysicsFunction.h"

Trampoline* Sonic_Main_t;
Trampoline* Sonic_runsActions_t;

enum class Saction {
	RunBuilding = 90,
	RollBuilding,
	FallBuilding,
	JumpBuilding,
	HurtBuilding
};

static const void* const SonicNactPtr = (void*)0x7220E0;
int Sonic_CheckNextActions(SonicCharObj2* a1, EntityData1* a2, EntityData2* a3, CharObj2Base* a4) {

	int result;

	__asm
	{
		push[a4]
		push[a3]
		push[a2]
		mov eax, [a1]
		// Call your __cdecl function here:
		call SonicNactPtr
		add esp, 12
		mov result, eax
	}

	return result;
}



void __cdecl Sonic_runsActions_r(EntityData1* data1, EntityData2* data2, CharObj2Base* co2, SonicCharObj2* SonicCO2) {

	FunctionPointer(void, original, (EntityData1 * data1, EntityData2 * data2, CharObj2Base * co2, SonicCharObj2 * SonicCO2), Sonic_runsActions_t->Target());
	original(data1, data2, co2, SonicCO2);


	EntityData2_R* data2R = (EntityData2_R*)data2;

	switch ((Saction)data1->Action) {

	case Saction::RunBuilding:
		if (Sonic_CheckNextActions(SonicCO2, data1, data2, co2)) {
			return;
		}

		if (CheckPlayerFall(co2, data1))
		{
			data1->Action = (char)Saction::FallBuilding;
			return;
		}
		else {

			if (co2->Speed.x < 1.0 && !GetAnalog(data1, co2, 0, 0))
				co2->Speed.x = 1.0;

			if (Sonic_CheckJump(data1, co2, SonicCO2)) {
				co2->Speed.y = co2->PhysData.JumpSpeed * 1.05;
				data1->Action = (char)Saction::JumpBuilding;
			}
			else if (Action_Pressed[co2->PlayerNum]) {
				data1->Action = (char)Saction::RollBuilding;
				co2->AnimInfo.Next = 12;
				data1->Status |= Status_Ball;
			}
		}

		return;
	case Saction::RollBuilding:

		if (Sonic_CheckNextActions(SonicCO2, data1, data2, co2)) {
			return;
		}

		if (CheckPlayerFall(co2, data1))
		{
			data1->Action = (char)Saction::FallBuilding;
		}
		else {
			if (Sonic_CheckJump(data1, co2, SonicCO2)) {
				co2->Speed.y = co2->PhysData.JumpSpeed * 1.05;
				data1->Action = (char)Saction::JumpBuilding;
			}
			else if (Action_Pressed[co2->PlayerNum]) {
				data1->Action = (char)Saction::RunBuilding;
				PhysicsAndAnimCheck(co2, data1);
				data1->Status &= 0xDAFFu;
			}

		}

		return;
	case Saction::FallBuilding:
		if (Sonic_CheckNextActions(SonicCO2, data1, data2, co2) || (data1->Status & (Status_OnObjectColli | Status_Ground)) == 0) {

			if (co2->Speed.x >= 0)
				co2->Speed.x = -1;

			return;
		}

		data1->Rotation.x = data2R->ang_aim.x;
		data1->Rotation.z = data2R->ang_aim.z;
		data1->Action = (char)Saction::RunBuilding;
		PhysicsAndAnimCheck(co2, data1);

		return;
	case Saction::JumpBuilding:
		if (Sonic_CheckNextActions(SonicCO2, data1, data2, co2) || (data1->Status & (Status_OnObjectColli | Status_Ground)) == 0) {
			return;
		}

		data1->Rotation.x = data2R->ang_aim.x;
		data1->Rotation.z = data2R->ang_aim.z;
		data1->Action = (char)Saction::RunBuilding;
		PhysicsAndAnimCheck(co2, data1);

		return;
	case Saction::HurtBuilding:
		if (Sonic_CheckNextActions(SonicCO2, data1, data2, co2)) {
			return;
		}

		data1->Action = (char)Saction::RunBuilding;
		co2->AnimInfo.Next = 6;
		return;
	}

}


void HurtPlayerBuilding(EntityData1* data1, CharObj2Base* co2) {
	data1->Action = (char)Saction::HurtBuilding;
	Float v26 = co2->Speed.x;
	co2->Speed.y = co2->PhysData.JumpSpeed;
	co2->Speed.x = v26 * 0.2;
	data1->Rotation.x = 0;
	data1->Rotation.z = 49152;
}


void Sonic_Main_r(ObjectMaster* obj)
{

	ObjectFunc(origin, Sonic_Main_t->Target());
	origin(obj);

	CharObj2Base* co2 = MainCharObj2[obj->Data2.Character->PlayerNum];
	EntityData1* data1 = MainCharObj1[obj->Data2.Character->PlayerNum];
	EntityData2* data2 = MainCharData2[obj->Data2.Character->PlayerNum];
	EntityData2_R* data2R = (EntityData2_R*)data2;

	switch ((Saction)data1->Action) {

	case (Saction)Action_Pain:
		if (CurrentSADXLevel == LevelIDs_SpeedHighway && CurrentAct == 1)
			HurtPlayerBuilding(data1, co2);
		break;
	case Saction::RunBuilding:
		PGetAccelerationForBuilding(data1, data2R, co2);
		PlayerGetSpeed(data1, co2, data2);

		if (PSetPositionForBuilding(data1, data2R, co2) == 2) {
			HurtPlayerBuilding(data1, co2);
		}
		else {
			PResetPositionForBuilding(data1, data2R, co2);
			PhysicsAndAnimCheck(co2, data1);
		}


		break;
	case Saction::RollBuilding:
		PGetAccelerationForBuilding(data1, data2R, co2);
		PlayerGetSpeed(data1, co2, data2);

		if (PSetPositionForBuilding(data1, data2R, co2) == 2) {

			HurtPlayerBuilding(data1, co2);
		}
		else {
			PResetPositionForBuilding(data1, data2R, co2);
		}

		break;
	case Saction::FallBuilding:
		PResetAngleForBuilding(data1, data2R, co2);
		PGetAccelerationForBuilding(data1, data2R, co2);
		PlayerGetSpeed(data1, co2, data2);

		if (PSetPositionForBuilding(data1, data2R, co2) != 2) {
			PResetPositionForBuilding(data1, data2R, co2);
			PResetPositionForBuilding(data1, data2R, co2);
		}
		else {
			HurtPlayerBuilding(data1, co2);
			PResetPositionForBuilding(data1, data2R, co2);
		}

		//LoadCrashStar(co2->PlayerNum);
		break;
	case Saction::JumpBuilding:
		PResetAngleForBuilding(data1, data2R, co2);
		PGetAccelerationForBuilding(data1, data2R, co2);
		PlayerGetSpeed(data1, co2, data2);

		if (PSetPositionForBuilding(data1, data2R, co2) == 2) {

			HurtPlayerBuilding(data1, co2);
		}
		else {
			PResetPositionForBuilding(data1, data2R, co2);
			PResetPositionForBuilding(data1, data2R, co2);
		}

		break;
	case Saction::HurtBuilding:
		PGetAccelerationForBuilding(data1, data2R, co2);
		PlayerGetSpeed(data1, co2, data2);
		data1->Position.y = data2R->spd.y + data1->Position.y;
		PResetPositionForBuilding(data1, data2R, co2);
		break;
	}
}

void Init_Sonic() {
	Sonic_Main_t = new Trampoline((int)Sonic_Main, (int)Sonic_Main + 0x6, Sonic_Main_r);
	Sonic_runsActions_t = new Trampoline((int)Sonic_ChecksForDamage, (int)Sonic_ChecksForDamage + 0x8, Sonic_runsActions_r);
}
