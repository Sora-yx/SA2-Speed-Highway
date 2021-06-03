#include "pch.h"

Trampoline* Sonic_Main_t;


void SonicNextAction() {

}

void Sonic_Main_r(ObjectMaster* obj)
{

	ObjectFunc(origin, Sonic_Main_t->Target());
	origin(obj);

	CharObj2Base* co2 = MainCharObj2[obj->Data2.Character->PlayerNum];
	EntityData1* data1 = MainCharObj1[obj->Data2.Character->PlayerNum];
	EntityData2* data2 = MainCharData2[obj->Data2.Character->PlayerNum];

	switch (data1->Action) {
	case 86:
		PlayerGetSpeed(data1, co2, data2);

		PlayerSetPosition(data1, data2, co2);
		PlayerResetPosition(data1, data2, co2);
		break;

	}
}

void Init_Sonic() {
	Sonic_Main_t = new Trampoline((int)Sonic_Main, (int)Sonic_Main + 0x6, Sonic_Main_r);
}
