#include "pch.h"

HelperFunctions HelperFunctionsGlobal;

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

ModelInfo* SH_BG[4];

static NJS_TEXNAME bg_highway_Tex[2]{};
static NJS_TEXLIST bg_highway_TEXLIST = { arrayptrandlength(bg_highway_Tex, Uint32) };

static NJS_TEXNAME bg_highway01_Tex[5]{};
static NJS_TEXLIST bg_highway01_TEXLIST = { arrayptrandlength(bg_highway01_Tex, Uint32) };

static NJS_TEXNAME bg_highway02_Tex[10]{};
static NJS_TEXLIST bg_highway02_TEXLIST = { arrayptrandlength(bg_highway02_Tex, Uint32) };

static NJS_TEXNAME bg_highway03_Tex[2]{};
static NJS_TEXLIST bg_highway03_TEXLIST = { arrayptrandlength(bg_highway03_Tex, Uint32) };

NJS_VECTOR SkyboxScale_SH[3] = { {8.5102701, 8.5102701, 8.5102701},  {1.0, 1.0, 1.0}, {1.22, 1.22, 1.22} };

void SpeedHighway_Display(ObjectMaster* obj) {
	EntityData1* v1; // esi
	CameraInfo v2; // edi
	float YDist; // [esp+0h] [ebp-14h]

	v1 = obj->Data1.Entity;
	v2 = CameraData;

	njControl3D_Backup();
	njControl3D_Add(NJD_CONTROL_3D_NO_CLIP_CHECK);
	njControl3D_Remove(NJD_CONTROL_3D_DEPTH_QUEUE);

	switch (v1->Action)
	{
	case 1:
		njPushMatrixEx();
		njTranslateV(0, &v2.Position);
		njScaleV_(&SkyboxScale_SH[CurrentAct]);
		njSetTexture(&bg_highway_TEXLIST);
		DrawObject(SH_BG[0]->getmodel());
		njSetTexture(&bg_highway01_TEXLIST);
		DrawObject(SH_BG[1]->getmodel());
		njScale(0, 1.0, 1.0, 1.0);
		njPopMatrixEx();
		break;
	case 2:
	case 5:
	case 8:
		v1->Action = 1;
		break;
	case 3:
		v1->Action = 4;
		break;
	case 4:
		if (MainCharObj1[0]->Position.y > -10400.0)
		{
			njPushMatrixEx();
			njTranslateV(0, &v2.Position);
			njScaleV_(&SkyboxScale_SH[CurrentAct]);
			njSetTexture(&bg_highway_TEXLIST);
			DrawObject(SH_BG[1]->getmodel());
			YDist = -10000.0 - v2.Position.y * 0.2;
	
			njTranslate(0, 0.0, YDist, 0.0);
			njSetTexture(&bg_highway02_TEXLIST);
			DrawObject(SH_BG[2]->getmodel());
			njScale(0, 1.0, 1.0, 1.0);
			njPopMatrixEx();

		}
		break;
	case 6:
		v1->Action = 7;
		break;
	case 7:
		njSetTexture(&bg_highway03_TEXLIST);
		njPushMatrixEx();
		njTranslateV(0, &v2.Position);
		njScaleV_(&SkyboxScale_SH[CurrentAct]);
		DrawObject(SH_BG[3]->getmodel());
		njScale(0, 1.0, 1.0, 1.0);
		njPopMatrixEx();
		break;
	}

	njControl3D_Restore();
}

void LoadModelBG_SH() {
	for (Uint8 i = 0; i < LengthOfArray(SH_BG); i++) {
		std::string str = "BG_SH0" + std::to_string(i);
		SH_BG[i] = LoadMDL(str.c_str(), ModelFormat_Chunk);
	}
}

void LoadTextureBG_SH() {
	LoadTextureList("BG_HIGHWAY", &bg_highway_TEXLIST);
	LoadTextureList("BG_HIGHWAY01", &bg_highway01_TEXLIST);
	LoadTextureList("BG_HIGHWAY02", &bg_highway02_TEXLIST);
	LoadTextureList("BG_HIGHWAY03", &bg_highway03_TEXLIST);
	return;
}

static void __cdecl SpeedHighway_Main(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	__int16 v1 = 0;
	__int16 curAct;
	unsigned __int16 v4;
	int curAction;
	int v6;

	switch (data->Action)
	{
	case 0:
		LoadTextureBG_SH();
		LoadObject(0, "act", SHControlActTrigger, LoadObj_Data1);
		obj->DisplaySub = SpeedHighway_Display;
		data->Action = 1;
		break;
	}

	v1 = 4;
	curAct = CurrentAct | v1;
	v4 = (unsigned __int8)curAct;

	v4 = (unsigned __int8)CurrentAct;

	curAction = data->Action;
	v6 = curAction % 3;
	if (curAction / 3 != v4)
	{
		if (v6 == 1)
		{
			++data->Action;
			return;
		}
		if (!v6)
		{
			data->Action = 3 * v4;
		}
	}

}

void LoadSHAct(int act)
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
		LoadLevelMusic((char*)"highway2.adx");
		//LoadStagePaths(SpeedHighway1PathList);
		//LoadDeathZones(SpeedHighway1DeathZones);
		MovePlayers(-50.0f, 42.0f, 0.0f);
		break;
	case 2:
		LoadLandTable("resource\\gd_pc\\speed-highway2.sa2lvl", &Act3LandInfo, &HIGHWAY03_TEXINFO);
		LoadLevelLayout(&SpeedHighwayObjListH, "speed-highway2-set-s.bin", "speed-highway2-set-u.bin");
		LoadLevelMusic((char*)"highway3.adx");
		//LoadStagePaths(SpeedHighway2PathList);
		//LoadDeathZones(SpeedHighway2DeathZones);
		MovePlayers(72.0f, 26.0f, 192.0f);
		break;
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

	LoadModelBG_SH();

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