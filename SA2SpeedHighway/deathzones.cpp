#include "pch.h"

static ModelInfo* SH_DZ[5];
static ModelInfo* SH_DZ2;
static ModelInfo* SH_DZ3;

DeathZone SHDeathZones[5];
DeathZone SHDeathZonesAct2;
DeathZone SHDeathZonesAct3;


uint32_t charaFlag = CharacterFlags_Sonic | CharacterFlags_Shadow | CharacterFlags_Tails | CharacterFlags_Eggman | CharacterFlags_Knuckles | CharacterFlags_Rouge | CharacterFlags_MechTails | CharacterFlags_MechEggman;

void CheckAndKillPlayer(ObjectMaster* obj) {


	EntityData1* data = obj->Data1.Entity;

	if (data->Action == 50)
		return;

	switch (CurrentLevel) {
	case LevelIDs_RadicalHighway:

		if (CurrentAct == 0) {
			if (MainCharObj1[0]->Position.y < -3176)
			{
				KillPlayerFall(0);
				data->Action = 50;
			}
		}
		else if (CurrentAct == 2) {
			if (MainCharObj1[0]->Position.y < -100)
			{
				KillPlayerFall(0);
				data->Action = 50;
			}
		}
		break;
	}
}

void LoadSH_DeathZonesModel() {

	for (size_t i = 0; i < LengthOfArray(SH_DZ); i++) {
		std::string str = "dz" + std::to_string(i);
		SH_DZ[i] = LoadMDL(str.c_str(), ModelFormat_Basic);
	}

	SH_DZ2 = LoadMDL("dz5", ModelFormat_Basic);
	SH_DZ3 = LoadMDL("dz6", ModelFormat_Basic);
}

void LoadSH_DeathZones(int act) {


	switch (act) {
	case 0:
		for (size_t i = 0; i < LengthOfArray(SH_DZ); i++) {
			SHDeathZones[i].Flags = charaFlag;
			SHDeathZones[i].Model = SH_DZ[i]->getmodel();
		}

		LoadDeathZones(SHDeathZones);
		break;
	case 1:
		SHDeathZonesAct2.Flags = charaFlag;
		SHDeathZonesAct2.Model = SH_DZ2->getmodel();

		LoadDeathZones(&SHDeathZonesAct2);
		break;
	case 2:
		SHDeathZonesAct3.Flags = charaFlag;
		SHDeathZonesAct3.Model = SH_DZ3->getmodel();

		LoadDeathZones(&SHDeathZonesAct3);
		break;
	}

}


void FreeDZModels() {
	for (size_t i = 0; i < LengthOfArray(SH_DZ); i++) {
		std::string str = "dz" + std::to_string(i);
		FreeMDL(SH_DZ[i]);
	}
	FreeMDL(SH_DZ2);
	FreeMDL(SH_DZ3);
}



