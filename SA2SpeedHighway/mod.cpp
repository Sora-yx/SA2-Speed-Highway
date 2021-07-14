#include "pch.h"
#include "level.h"
#include "Sonic.h"

HelperFunctions HelperFunctionsGlobal;


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

		//WriteData<1>((void*)0x5239A0, 0xC3);
	}

	__declspec(dllexport) void __cdecl OnFrame() {


		if (GameState != GameStates_Ingame)
			return;

		if (Controllers[0].press & Buttons_B && CurrentLevel == LevelIDs_RadicalHighway) {
		}

		FreeCam();
	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}