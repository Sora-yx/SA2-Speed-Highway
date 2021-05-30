#include "pch.h"

HelperFunctions HelperFunctionsGlobal;

static int CurrentAct;

static LandTableInfo* Act1LandInfo = nullptr;
static LandTableInfo* Act2LandInfo = nullptr;
static LandTableInfo* Act3LandInfo = nullptr;

static NJS_TEXNAME HIGHWAY01_TEXNAME[89]{};
static NJS_TEXLIST HIGHWAY01_TEXLIST = { arrayptrandlength(HIGHWAY01_TEXNAME, Uint32) };
static const TexPackInfo HIGHWAY01_TEXINFO = { "HIGHWAY01", &HIGHWAY01_TEXLIST };

static NJS_TEXNAME HIGHWAY02_TEXNAME[32]{};
static NJS_TEXLIST HIGHWAY02_TEXLIST = { arrayptrandlength(HIGHWAY02_TEXNAME, Uint32) };
static const TexPackInfo HIGHWAY02_TEXINFO = { "HIGHWAY02", &HIGHWAY02_TEXLIST };

static NJS_TEXNAME HIGHWAY03_TEXNAME[107]{};
static NJS_TEXLIST HIGHWAY03_TEXLIST = { arrayptrandlength(HIGHWAY03_TEXNAME, Uint32) };
static const TexPackInfo HIGHWAY03_TEXINFO = { "HIGHWAY03", &HIGHWAY03_TEXLIST };

static const StartPosition sh_startpos = { LevelIDs_RadicalHighway, 0, 0, 0, { -673.0f, -10.0f, 5.0f }, { -673.0f, -10.0f, 0.0f }, { -673.0f, -10.0f, 10.0f } };
static const StartPosition sh_endpos = { LevelIDs_RadicalHighway, 0, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
static const LevelEndPosition sh_2pintro = { LevelIDs_RadicalHighway, 0, 0, 0, { 0.0f, 0.0f, 0.0 }, { 0.0f, 0.0f, 0.0 } };
static const LevelEndPosition sh_endpos23 = { LevelIDs_RadicalHighway, 0, 0, 0, { 0.0f, 0.0f, 0.0 }, { 0.0f, 0.0f, 0.0 } };



static void LoadSHAct(int act)
{
	FreeLandTableObj();
	DeleteSetHandler();
	FreeSETObjects();

	CurrentAct = act;

	switch (act)
	{
	case 0:
		LoadLandTable("resource\\gd_pc\\speed-highway0.sa2lvl", &Act1LandInfo, &HIGHWAY01_TEXINFO);
		LoadLevelLayout(&SpeedHighwayObjListH, "speed-highway0-set-s.bin", "speed-highway0-set-u.bin");
		LoadLevelMusic((char*)"highway1.adx");
		LoadStagePaths(PathList_SpeedHighway0);
		//LoadDeathZones(SpeedHighway0DeathZones);
		MovePlayers(-673.0f, -10.0f, 5.0f);
		break;
	case 1:
		LoadLandTable("resource\\gd_pc\\speed-highway1.sa2lvl", &Act2LandInfo, &HIGHWAY02_TEXINFO);
		LoadLevelLayout(&SpeedHighwayObjListH, "speed-highway1-set-s.bin", "speed-highway1-set-u.bin");
		//LoadLevelMusic((char*)"highway2.adx");
		//LoadStagePaths(SpeedHighway1PathList);
		//LoadDeathZones(SpeedHighway1DeathZones);
		MovePlayers(-50.0f, 42.0f, 0.0f);
		break;
	case 2:
		LoadLandTable("resource\\gd_pc\\speed-highway2.sa2lvl", &Act3LandInfo, &HIGHWAY03_TEXINFO);
		LoadLevelLayout(&SpeedHighwayObjListH, "speed-highway2-set-s.bin", "speed-highway2-set-u.bin");
		//LoadLevelMusic((char*)"highway3.adx");
		//LoadStagePaths(SpeedHighway2PathList);
		//LoadDeathZones(SpeedHighway2DeathZones);
		MovePlayers(72.0f, 26.0f, 192.0f);
		break;
	}
}

static void __cdecl SpeedHighway_Main(ObjectMaster* obj)
{
	if (++obj->Data1.Entity->field_6 == 300)
	{
		//LoadSHAct(1);
	}
}

static void __cdecl SpeedHighway_Free()
{
	FreeTexPacks((NJS_TEXLIST***)0x109E748, (TexPackInfo*)0x109E810);
	FreeLandTableObj();
	DeleteSetHandler();

	FreeLandTableInfo(&Act1LandInfo);
	FreeLandTableInfo(&Act2LandInfo);
	FreeLandTableInfo(&Act3LandInfo);

	DropRingsFunc_ptr = nullptr;
	DisplayItemBoxItemFunc_ptr = nullptr;

	*(void**)0x1DE4680 = nullptr;
	*(void**)0x1DE4684 = nullptr;
	*(void**)0x1DE4688 = nullptr;
	*(void**)0x1DE468C = nullptr;
}

static void __cdecl SpeedHighway_Init()
{
	LoadSHAct(0);

	LoadStageLight("stg14_light.bin");
	LoadFogData_Fogtask("stg14_fog.bin", (FogData*)0x19EEF28);
	LoadStageSounds("se_ac_rh.mlt", (void*)0x8ABFB0);

	DropRingsFunc_ptr = DropRings;
	DisplayItemBoxItemFunc_ptr = DisplayItemBoxItem;

	SetDrawingPlanes(-3.0f, -65535.0f);

	//Chaos Drive Function Pointers
	dword_1DE4680 = (void*)0x6B6C20;
	dword_1DE4684 = (void*)0x6BBAE0;
	dword_1DE4688 = (void*)0x6BC450;
	dword_1DE468C = (void*)0x6BC4A0;

	LoadTexPacks((TexPackInfo*)0x109E810, (NJS_TEXLIST***)0x109E748);
}

static const LevelHeader speedHighwayModule = { "SPDHIGH", 0, SpeedHighway_Init, SpeedHighway_Free, SpeedHighway_Main };

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

		RadicalHighway_ObjectList.Count = 118;
		RadicalHighway_ObjectList.List = SpeedHighwayObjListH.List;

		HelperFunctionsGlobal = helperFunctions;
		RadicalHighwayHeader = speedHighwayModule;

		SetStartEndPoints(&sh_startpos, &sh_2pintro, &sh_endpos, &sh_endpos23);
	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}