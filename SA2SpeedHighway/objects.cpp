#include "pch.h"


Trampoline* goalringt;
Trampoline* itembox_t;
Trampoline* airbox_t;
Trampoline* RingLinear_t;

//Ennemies
void Beetle_Stationary(ObjectMaster* a1) {
	EntityData1* entity = a1->Data1.Entity;
	entity->Rotation.x = 0;
	entity->Rotation.z = 0xC1;
	entity->Scale = { 0.10, 3.50, 51 };
	a1->MainSub = (ObjectFuncPtr)Beetle_Main;
}

void Beetle_Attack(ObjectMaster* a1) {
	EntityData1* entity = a1->Data1.Entity;
	entity->Rotation.x = 0x1;
	entity->Rotation.z = 0x1C0;
	entity->Scale = { 4, 1, 150 };
	a1->MainSub = (ObjectFuncPtr)Beetle_Main;
}

void Beetle_Electric(ObjectMaster* a1) {
	EntityData1* entity = a1->Data1.Entity;
	entity->Rotation.x = 0;
	entity->Rotation.z = 0x101;
	entity->Scale = { 0.10, 3.50, 51 };
	a1->MainSub = (ObjectFuncPtr)Beetle_Main;
}

void Robots(ObjectMaster* a1) {
	EntityData1* entity = a1->Data1.Entity;
	entity->Rotation.x = 0x1;
	entity->Rotation.z = 0x100;
	entity->Scale = { 0, 1, 126 };
	a1->MainSub = (ObjectFuncPtr)E_AI;
}

enum objects {
	ObjIndex_Common = 2,

};

void GoalRing_r(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;
	if (data->Action == 0) {
		if (isSADXLevel()) {
			data->Position.y += 32;
		}
	}

	ObjectFunc(origin, goalringt->Target());
	origin(obj);
}

//SADX uses different itembox ID than SA2
unsigned int FixItemBoxID(unsigned int id) {

	switch (id)
	{
	case 1:
		return 10;
	case 2:
		return 1;
	case 6:
		return 2;
	case 7:
		return 6;
	}

	return id;
}

void ItemBox_r(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;
	if (data->Action == 0) {
		if (isSADXLevel()) {
			if ((unsigned __int64)data->Scale.x >= 9)
			{
				data->Scale.x = 0.0;
			}

			data->Scale.x = FixItemBoxID((unsigned int)data->Scale.x);
		}
	}

	ObjectFunc(origin, itembox_t->Target());
	origin(obj);
}

void AirBox_r(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;
	if (data->Action == 0) {
		if (isSADXLevel()) {
			if ((unsigned __int64)data->Scale.x >= 9)
			{
				data->Scale.x = 0.0;
			}

			data->Scale.x = FixItemBoxID((unsigned int)data->Scale.x);
		}
	}

	ObjectFunc(origin, airbox_t->Target());
	origin(obj);
}

signed int RingsLinear_r(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;

	if (data->Action == 0) {
		if (isSADXLevel()) {
			if (data->Scale.z >= 1.0) {
				return RingCircleMain(obj);
			}

			//in sadx scale X is number of rings and scale Y is distance between rings.
			data->Scale.z = data->Scale.x + 1;
			data->Scale.x = data->Scale.y / 2.0;
			data->Scale.y = 0;
		}

	}

	ObjectFunc(origin, RingLinear_t->Target());
	origin(obj);
}


static ObjectListEntry SpeedHighwayObjList[] = {
	{ LoadObj_Data1, 2, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x20, 0.0, (ObjectFuncPtr)SpringA_Main },
	{ LoadObj_Data1, ObjIndex_Common, 0x20, 0.0, SpringB_Main },
	{ (LoadObj)(LoadObj_Data2 | LoadObj_Data1), 2, 2, 0.0, DashPanel_Main },
	{ (LoadObj)(LoadObj_Data1), ObjIndex_Common, 0, 0.0, (ObjectFuncPtr)IRONBALL2 },

{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x7A3E50, "O FeBJG" } /* "O FeBJG",
{ (LoadObj)2 }, //3, 0, 0, 0, (ObjectFuncPtr)0x7A30E0, "O TOGE" } /* "O TOGE" ,
{ (LoadObj)3 }, //3, 4, 0, 0, (ObjectFuncPtr)0x4A3420, "O EME P" } /* "O EME P" ,
{ (LoadObj)2, 2, 1, 640000, (ObjectFuncPtr)0x6C63C0, },
{ (LoadObj)6 },// 3, 0, 0, 0, (ObjectFuncPtr)0x4CBA80, "O SWITCH" } /* "O SWITCH" */
{ (LoadObj)10 },// 3, 0, 0, 0, (ObjectFuncPtr)0x7A2B60, "CMN KUSA" } /* "CMN KUSA" */,
{ (LoadObj)14 }, //3, 1, 2250000, 0, (ObjectFuncPtr)0x7A26F0, "CMN_DRING" } /* "CMN_DRING" */,
{ (LoadObj)2 }, //3, 0, 0, 0, (ObjectFuncPtr)0x7A21C0, "O BALOON" } /* "O BALOON" */,
{ (LoadObj)(LoadObj_Data1), ObjIndex_Common, 30, 0.0, ItemBox_Main }, //3, 0, 0, 0, (ObjectFuncPtr)0x4D6F10, "O ITEMBOX" } /* "O ITEMBOX" */,
{ (LoadObj)6, 2, 0, 0, (ObjectFuncPtr)0x6D4EA0,  } /* "ROCKET   " */,
{ (LoadObj)6, 2, 0, 0, (ObjectFuncPtr)0x6D4EA0,  } /* "ROCKET   " */,
{ (LoadObj)6, 2, 0, 0, (ObjectFuncPtr)0x6CE4C0,  } /* "ROCKETMISSSILE" */,
{ (LoadObj)6, 2, 0, 0, (ObjectFuncPtr)0x6CE4C0,  } /* "ROCKETMISSSILE" */,
{ (LoadObj)2 },// 2, 1, 4000000, 0, (ObjectFuncPtr)0x4B8DC0, "O JPanel" } /* "O JPanel" */,
{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA | LoadObj_UnknownB), ObjIndex_Common, 0, 0, Checkpoint_Main },
{ (LoadObj)(LoadObj_Data1) },// ObjIndex_Common, DistObj_UseDist, 640000.0, (ObjectFuncPtr)WALL },
{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x7A9140, "O KN HINT" } /* "O KN HINT" */,
{ (LoadObj)(LoadObj_Data1), ObjIndex_Common, 0, 0, (ObjectFuncPtr)LongSpring_Main },
{ (LoadObj)6 }, //3, 1, 1000000, 0, (ObjectFuncPtr)0x61C740, "O EV   " } /* "O EV   " */,
{ (LoadObj)10 }, //3, 1, 1000000, 0, (ObjectFuncPtr)0x61BDC0, "O FOUNT" } /* "O FOUNT" */,
{ (LoadObj)3, 1, 1000000, 0, nullptr }, /* "O CRANE" */
{ (LoadObj)2 },//3, 1, 1000000, 0, (ObjectFuncPtr)0x61AE80, "O GLASS " } /* "O GLASS " */,
{ (LoadObj)2 },//3, 1, 2250000, 0, (ObjectFuncPtr)0x61ACA0, "O GLASS2" } /* "O GLASS2" */,
{ (LoadObj)6 },//3, 0, 0, 0, (ObjectFuncPtr)0x614E40, "HIGH RAFT A" } /* "HIGH RAFT A" */,
{ (LoadObj)6 },//3, 0, 0, 0, (ObjectFuncPtr)0x614E60, "HIGH RAFT C" } /* "HIGH RAFT C" */,
{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x61A330, "O TANKA" } /* "O TANKA" */,
{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x619960, "O SIGNB" } /* "O SIGNB" */,
{ (LoadObj)6 }, //3, 1, 1000000, 0, (ObjectFuncPtr)0x619340, "O TurnAsi" } /* "O TurnAsi" */,
{ (LoadObj)3, 1, 25000000, 0, nullptr, }, /* "O SLIGHT" */
{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x6188E0, "O ARCADE01" } /* "O ARCADE01" */,
{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x6188F0, "O ARCADE02" } /* "O ARCADE02" */,
{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x618900, "O ARCADE03" } /* "O ARCADE03" */,
{ (LoadObj)6 },//3, 1, 1000000, 0, (ObjectFuncPtr)0x6186D0, "O JAMER" } /* "O JAMER" */,
{ (LoadObj)3, 1, 2250000, 0, nullptr }, /* "O STP4S" */
{ (LoadObj)6 },//3, 1, 2250000, 0, (ObjectFuncPtr)0x617F00, "O STP4T" } /* "O STP4T" */,
{ (LoadObj)14 },// 3, 1, 2250000, 0, (ObjectFuncPtr)0x618030, "O FLYST" } /* "O FLYST" */,
{ (LoadObj)2 },// 3, 1, 160000, 0, (ObjectFuncPtr)0x617AE0, "O Post1" } /* "O Post1" */,
{ (LoadObj)2 },// 3, 1, 160000, 0, (ObjectFuncPtr)0x617B10, "O Post4" } /* "O Post4" */,
{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x6178F0, "O Nbox1" } /* "O Nbox1" */,
{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x617940, "O Nbox2" } /* "O Nbox2" */,
{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x617990, "O Nbox3" } /* "O Nbox3" */,
{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x6179E0, "O Nbox4" } /* "O Nbox4" */,
{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x6177C0, "O Bench" } /* "O Bench" */,
{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x617780, "O FENCE" } /* "O FENCE" */,
{ (LoadObj)6 },// 3, 1, 6250000, 0, (ObjectFuncPtr)0x617680, "O NEON1" } /* "O NEON1" */,
{ (LoadObj)6 },// 3, 1, 6250000, 0, (ObjectFuncPtr)0x6176C0, "O NEON2" } /* "O NEON2" */,
{ (LoadObj)6 },// 3, 1, 6250000, 0, (ObjectFuncPtr)0x617700, "O NEON3" } /* "O NEON3" */,
{ (LoadObj)6 },// 3, 1, 6250000, 0, (ObjectFuncPtr)0x617740, "O NEON4" } /* "O NEON4" */,
{ (LoadObj)2 },// 3, 1, 160000, 0, (ObjectFuncPtr)0x617420, "O POSTER0" } /* "O POSTER0" */,
{ (LoadObj)2 },// 3, 1, 160000, 0, (ObjectFuncPtr)0x617440, "O POSTER1" } /* "O POSTER1" */,
{ (LoadObj)2 },// 3, 1, 160000, 0, (ObjectFuncPtr)0x617460, "O POSTER2" } /* "O POSTER2" */,
{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x6173D0, "O SIGN1" } /* "O SIGN1" */,
{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x617290, "O KANBANA" } /* "O KANBANA" */,
{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x617330, "O KANBANB" } /* "O KANBANB" */,
{ (LoadObj)2 },// 3, 1, 40000, 0, (ObjectFuncPtr)0x617160, "O BAKETU" } /* "O BAKETU" */,
{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x616C90, "O HYDBASS" } /* "O HYDBASS" */,
{ (LoadObj)6 },// 3, 0, 0, 0, (ObjectFuncPtr)0x615810, "O GREEN" } /* "O GREEN" */,
{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x615830, "O GREENA" } /* "O GREENA" */,
{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x615880, "O GREENB" } /* "O GREENB" */,
{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x6158D0, "O GREEND" } /* "O GREEND" */,
{ (LoadObj)2, 3, 0, 0, nullptr, },// 3, 0, 0, 0, (ObjectFuncPtr)0x6163D0, "O LAMP" } /* "O LAMP" */,
{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x616770, "O CLIGHT" } /* "O CLIGHT" */,
{ (LoadObj)2, 3, 0, 0, nullptr, },// "o lamp01" },// 3, 0, 0, 0, (ObjectFuncPtr)0x6163D0, "O LAMP01" } /* "O LAMP01" */,
{ (LoadObj)2, 3, 0, 0, nullptr, },
{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x616210, "O PinPin" } /* "O PinPin" */,
{ (LoadObj)6 },// 3, 1, 4000000, 0, (ObjectFuncPtr)0x616150, "O Escalator1" } /* "O Escalator1" */,
{ (LoadObj)6 },// 3, 1, 4000000, 0, (ObjectFuncPtr)0x6161B0, "O Escalator2" } /* "O Escalator2" */,
{ (LoadObj)2 },//3, 1, 4000000, 0, (ObjectFuncPtr)0x615EB0, "O Antena" } /* "O Antena" */,
{ (LoadObj)3, 0, 0, 0, nullptr, }, /* "O Cone1" */
{ (LoadObj)3, 0, 0, 0, nullptr, }, /* "O Cone1" */
{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x615990, "O Curb" } /* "O Curb" */,
{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x615940, "O Fence02" } /* "O Fence02" */,
{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x615920, "O GREENE" } /* "O GREENE" */,
{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x615780, "O SIBA01" } /* "O SIBA01" */,
{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x6157D0, "O SIBA02" } /* "O SIBA02" */,
{ (LoadObj)6 },// 3, 1, 250000, 0, (ObjectFuncPtr)0x615740, "O Tokei" } /* "O Tokei" */,
{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x6155A0, "O Lmpa" } /* "O Lmpa" */,
{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x615410, "O GG" } /* "O GG" */,
{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x615450, "O FF" } /* "O FF" */,
{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x6153C0, "O StPlant01" } /* "O StPlant01" */,
{ (LoadObj)2 },//5, 0, 0, 0, (ObjectFuncPtr)0x615310, "O StPlant02" } /* "O StPlant02" */,
{ (LoadObj)2 },//3, 1, 1000000, 0, (ObjectFuncPtr)0x613E30, "O HeliA" } /* "O HeliA" */,
{ (LoadObj)2 },//3, 1, 1000000, 0, (ObjectFuncPtr)0x613E80, "O HeliB" } /* "O HeliB" */,
{ (LoadObj)3, 1, 1000000, 0, nullptr, }, /* "O HW BELL" */
{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x614ED0, "O HELIP L" } /* "O HELIP L" */,
{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x614E80, "O TUNAGI" } /* "O TUNAGI" */,
{ (LoadObj)2 },//3, 1, 2250000, 0, (ObjectFuncPtr)0x614D80, "O RING2" } /* "O RING2" */,
{ LoadObj_Data1, 2, 4, 0, Beetle_Attack },
{ LoadObj_Data1, 2, 4, 0, Beetle_Stationary },
{ LoadObj_Data1, 2, 4, 0, Beetle_Electric },
{ LoadObj_Data1, 2, 4, 0.0, (ObjectFuncPtr)Robots },
{ (LoadObj)2 },//3, 5, 360000, 0, (ObjectFuncPtr)0x4AF190, "E UNI A" } /* "E UNI A" */,
{ (LoadObj)2 },//3, 5, 360000, 0, (ObjectFuncPtr)0x4AF500, "E UNI B" } /* "E UNI B" */,
{ (LoadObj)2, 2, 0, 0, (ObjectFuncPtr)SPHERE, }, /* "C SPHERE" */
{ (LoadObj)2, 2, 0, 0, (ObjectFuncPtr)CCYL, }, /* "C CYLINDER" */
{ (LoadObj)2, 2, 0, 0, (ObjectFuncPtr)CCUBE, }, /* CUBE */
{ (LoadObj)2 }, /*2, 0, 0, (ObjectFuncPtr)CWALL, }, "OTTOTTO" */
{ (LoadObj)2 },//2, 0, 0, 0, (ObjectFuncPtr)0x7A1AA0, "O TIKAL" } /* "O TIKAL" */,
{ (LoadObj)2 },//2, 0, 0, 0, (ObjectFuncPtr)0x7A9C60, "O HINT" } /* "O HINT" */,
{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, (ObjectFuncPtr)RingLinearMain },
{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x614B00, "O GFENCE" } /* "O GFENCE" */,
{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x614B30, "O GCURB" } /* "O GCURB" */,
{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x614B60, "O GFENCE02" } /* "O GFENCE02" */,
{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x614B90, "O GPINPIN" } /* "O GPINPIN" */,
{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x614BC0, "O GFF" } /* "O GFF" */,
{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x614BF0, "O GRAFTA" } /* "O GRAFTA" */,
{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x614C20, "O GRAFTC" } /* "O GRAFTC" */,
{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x614C50, "O GGRENA" } /* "O GGRENA" */,
{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x614C80, "O GGRENB" } /* "O GGRENB" */,
{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x614CB0, "O GGREND" } /* "O GGREND" */,
{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x614CE0, "O GCLIGHT" } /* "O GCLIGHT" */,
{ (LoadObj)(LoadObj_Data2 | LoadObj_Data1 | LoadObj_UnknownA | LoadObj_UnknownB), 2, 0x30, 0.0, ItemBoxAir_Main },
{ (LoadObj)2 }// 3, 1, 3240000, 0, (ObjectFuncPtr)0x614380, "MISSILE" } /* "MISSILE" */,
};

ObjectListHead SpeedHighwayObjListH = { arraylengthandptr(SpeedHighwayObjList) };


void Objects_Init() {
	goalringt = new Trampoline((int)GoalRing_Main, (int)GoalRing_Main + 0x6, GoalRing_r);
	itembox_t = new Trampoline((int)ItemBox_Main, (int)ItemBox_Main + 0x5, ItemBox_r);
	airbox_t = new Trampoline((int)ItemBoxAir_Main, (int)ItemBoxAir_Main + 0x5, AirBox_r);
	RingLinear_t = new Trampoline((int)RingLinearMain, (int)RingLinearMain + 0x6, RingsLinear_r);
}