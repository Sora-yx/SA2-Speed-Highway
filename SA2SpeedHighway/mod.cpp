#include "pch.h"
#include "level.h"
#include "Sonic.h"

HelperFunctions HelperFunctionsGlobal;


static void FixCam()
{
	if (isSADXLevel())
	{
		if (CurrentSADXLevel == LevelIDs_SpeedHighway && CurrentAct == 1)
			return;

		if (MainCharObj2[0] && !MainCharObj2[1]) {
			if (MainCharObj2[0]->Speed.x >= 1 && MainCharObj2[0]->Speed.x <= 8)
				CameraData.Position.y += 0.7;

			if (MainCharObj2[0]->Speed.x > 8 && MainCharObj2[0]->Speed.x <= 13)
				CameraData.Position.y += 1.9;

			if (MainCharObj2[0]->Speed.x > 13)
				CameraData.Position.y += 2.7;
		}
	}
}

extern "C"
{
	__declspec(dllexport) void Init(const char* path, const HelperFunctions& helperFunctions)
	{
		if (helperFunctions.Version < 7) {
			MessageBoxA(MainWindowHandle,
				"Your copy of the Mod Loader is outdated, please update it to the latest version.",
				"SA2 Speed Highway",
				MB_ICONWARNING);
		}

		HelperFunctionsGlobal = helperFunctions;
		
		SpeedHighway_Hook();
		Init_Sonic();

		CommonObjects_Init();
	}

	__declspec(dllexport) void __cdecl OnFrame() {


		if (GameState != GameStates_Ingame)
			return;

		if (Controllers[0].press & Buttons_Y && CurrentLevel == LevelIDs_RadicalHighway) {
			//MainCharObj1[0]->Position = { 3630.514893, -1326, 1424.386963 };
			MainCharObj1[0]->Position = { 5512.210938, -1778, 1215 };
			//MainCharObj1[0]->Position = { 4095.762207, -1500, 4599.47998 };
			//MainCharObj1[0]->Position = { 3846, -1486, 1318 };
		}

		FixCam();
	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}