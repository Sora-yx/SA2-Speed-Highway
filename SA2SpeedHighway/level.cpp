#include "pch.h"
#include "level.h"
#include "act.h"
#include "objects.h"

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
//static const StartPosition sh_endpos = { LevelIDs_RadicalHighway, 0, 0, 0, { -230.08, 150, -1840.42 }, { -230.08, 150, -1840.42}, { -230.08, 150, -1840.42} };
static const StartPosition sh_endpos = { LevelIDs_RadicalHighway, 16404, 16404, 16404, { -229.0391998, 140, -1591.42 }, { -229.0391998, 140, -1591.42}, { -240.0391998, 140, -1591.42} };
static const LevelEndPosition sh_2pintro = { LevelIDs_RadicalHighway, 0, 0, 0, { 0.0f, 0.0f, 0.0 }, { 0.0f, 0.0f, 0.0 } };
static const LevelEndPosition sh_endpos23 = { LevelIDs_RadicalHighway, 0, 0, 0, { -230.08, 150, -1840.42}, { -230.08, 150, -1840.42 } };

static ModelInfo* SH_BG[4];

static NJS_TEXNAME bg_highway_Tex[2]{};
static NJS_TEXLIST bg_highway_TEXLIST = { arrayptrandlength(bg_highway_Tex, Uint32) };

static NJS_TEXNAME bg_highway01_Tex[5]{};
static NJS_TEXLIST bg_highway01_TEXLIST = { arrayptrandlength(bg_highway01_Tex, Uint32) };

static NJS_TEXNAME bg_highway02_Tex[10]{};
static NJS_TEXLIST bg_highway02_TEXLIST = { arrayptrandlength(bg_highway02_Tex, Uint32) };

static NJS_TEXNAME bg_highway03_Tex[2]{};
static NJS_TEXLIST bg_highway03_TEXLIST = { arrayptrandlength(bg_highway03_Tex, Uint32) };

static NJS_VECTOR SkyboxScale_SH[3] = { {8.5f, 8.5f, 8.5f},  {1.0f, 1.0f, 1.0f}, {1.22f, 1.22f, 1.22f} };

extern LoopHead* PathList_SpeedHighway0[];

void LoadModelBG_SH()
{
	LoadTextureList("BG_HIGHWAY", &bg_highway_TEXLIST);
	LoadTextureList("BG_HIGHWAY01", &bg_highway01_TEXLIST);
	LoadTextureList("BG_HIGHWAY02", &bg_highway02_TEXLIST);
	LoadTextureList("BG_HIGHWAY03", &bg_highway03_TEXLIST);

	for (size_t i = 0; i < LengthOfArray(SH_BG); i++) {
		std::string str = "BG_SH0" + std::to_string(i);
		SH_BG[i] = LoadMDL(str.c_str(), ModelFormat_Chunk);
	}
}

void FreeModelBG_SH()
{
	FreeTexList(&bg_highway_TEXLIST);
	FreeTexList(&bg_highway01_TEXLIST);
	FreeTexList(&bg_highway02_TEXLIST);
	FreeTexList(&bg_highway03_TEXLIST);

	for (size_t i = 0; i < LengthOfArray(SH_BG); i++) {
		FreeMDL(SH_BG[i]);
	}
}

void SpeedHighway_Display(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	NJS_VECTOR* position = &CameraScreensInfoArray[CurrentScreen]->pos;

	njControl3D_Backup();
	njControl3D_Add(NJD_CONTROL_3D_NO_CLIP_CHECK);
	njControl3D_Remove(NJD_CONTROL_3D_DEPTH_QUEUE);

	switch (CurrentAct)
	{
	case 0:
		njPushMatrixEx();
		njTranslateV(0, position);
		njScaleV_(&SkyboxScale_SH[CurrentAct]);
		njSetTexture(&bg_highway_TEXLIST);
		DrawObject(SH_BG[0]->getmodel());
		njSetTexture(&bg_highway01_TEXLIST);
		DrawObject(SH_BG[1]->getmodel());
		njScale(0, 1.0f, 1.0f, 1.0f);
		njPopMatrixEx();
		break;
	case 1:
		if (MainCharObj1[CurrentScreen]->Position.y > -10400.0f)
		{
			njPushMatrixEx();
			njTranslateV(0, position);
			njScaleV_(&SkyboxScale_SH[CurrentAct]);
			njSetTexture(&bg_highway_TEXLIST);
			DrawObject(SH_BG[0]->getmodel());
			njTranslate(0, 0.0f, -10000.0f - position->y * 0.2f, 0.0f);
			njSetTexture(&bg_highway02_TEXLIST);
			DrawObject(SH_BG[2]->getmodel());
			njScale(0, 1.0f, 1.0f, 1.0f);
			njPopMatrixEx();

		}
		break;
	case 2:
		njSetTexture(&bg_highway03_TEXLIST);
		njPushMatrixEx();
		njTranslateV(0, position);
		njScaleV_(&SkyboxScale_SH[CurrentAct]);
		DrawObject(SH_BG[3]->getmodel());
		njScale(0, 1.0f, 1.0f, 1.0f);
		njPopMatrixEx();
		break;
	}

	njControl3D_Restore();
}

static void __cdecl SpeedHighway_Main(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	switch (data->Action)
	{
	case 0:
		PerfectRings_StartCount = 0;
		LoadSHAct(CurrentAct);
		LoadObject(0, "SHActManager", SHControlActTrigger, LoadObj_Data1);
		obj->DisplaySub = SpeedHighway_Display;
		data->Action = 1;
		break;
	case 1:
		if (CurrentAct == 0) {
			if (MainCharObj1[0]->Position.y < -3176)
			{
				KillPlayerFall(0);
				data->Action = 2;
			}
		}
		else if (CurrentAct == 2) {
			if (MainCharObj1[0]->Position.y < -100)
			{
				KillPlayerFall(0);
				data->Action = 2;
			}
		}
		break;
	}

}


void LoadSHAct(int act)
{
	PrintDebug("[SH] Loading act %i", act);

	PerfectRings_StartCount = PerfectRings;

	StopMusic();
	DeleteSetHandler();
	DeleteSETObjects();
	CurrentAct = act;

	switch (act)
	{
	case 0:
		LoadLandManager_(Act1LandInfo->getlandtable());
		LoadLevelLayout(&SpeedHighwayObjListH, "speed-highway0-set-s.bin", "SET0048_2P_U.bin");
		LoadLevelMusic((char*)"highway1.adx");
		LoadStagePaths(PathList_SpeedHighway0);
		MovePlayersToStartPos(-673.0f, -10.0f, 5.0f);
		break;
	case 1:
		LoadLandManager_(Act2LandInfo->getlandtable());
		LoadLevelLayout(&SpeedHighwayObjListH, "speed-highway1-set-s.bin", "SET0048_2P_U.bin");
		MovePlayersToStartPos(-50.0f, 42.0f, 0.0f);
		break;
	case 2:
		LoadLandManager_(Act3LandInfo->getlandtable());
		LoadLevelLayout(&SpeedHighwayObjListH, "speed-highway2-set-s.bin", "SET0048_2P_U.bin");
		LoadLevelMusic((char*)"highway3.adx");
		MovePlayersToStartPos(72.0f, 26.0f, 192.0f);
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

	FreeModelBG_SH();
	FreeModelsSH();
	DeleteDeathZones();
	DropRingsFunc_ptr = nullptr;
	DisplayItemBoxItemFunc_ptr = nullptr;

	*(void**)0x1DE4680 = nullptr;
	*(void**)0x1DE4684 = nullptr;
	*(void**)0x1DE4688 = nullptr;
	*(void**)0x1DE468C = nullptr;
}

static void __cdecl SpeedHighway_Init()
{
	LoadStageLight("stg14_light.bin");
	LoadFogData_Fogtask("stg14_fog.bin", (FogData*)0x19EEF28);
	LoadStageSounds("se_ac_rh.mlt", (void*)0x8ABFB0);

	LoadLandTable("resource\\gd_pc\\speed-highway0.sa2lvl", &Act1LandInfo, &HIGHWAY01_TEXINFO);
	LoadLandTable("resource\\gd_pc\\speed-highway1.sa2lvl", &Act2LandInfo, &HIGHWAY02_TEXINFO);
	LoadLandTable("resource\\gd_pc\\speed-highway2.sa2lvl", &Act3LandInfo, &HIGHWAY03_TEXINFO);

	LoadMLT("se_ac_cg.mlt");

	DropRingsFunc_ptr = DropRings;
	DisplayItemBoxItemFunc_ptr = DisplayItemBoxItem;

	SetDrawingPlanes(-3.0f, -65535.0f);

	// Chaos Drive Function Pointers
	dword_1DE4680 = (void*)0x6B6C20;
	dword_1DE4684 = (void*)0x6BBAE0;
	dword_1DE4688 = (void*)0x6BC450;
	dword_1DE468C = (void*)0x6BC4A0;

	// Get starting act
	if (CurrentCharacter == Characters_Knuckles || CurrentCharacter == Characters_Rouge)
	{
		CurrentAct = 2;
	}
	else
	{
		CurrentAct = 0;
	}

	LoadGreenForestCharAnims(); //used for helico grab animation
	LoadSH_DeathZonesModel();
	LoadModelBG_SH();
	LoadModelsSH();
	LoadTexPacks((TexPackInfo*)0x109E810, (NJS_TEXLIST***)0x109E748);
}

static const LevelHeader speedHighwayModule = { "SPDHIGH", 0, SpeedHighway_Init, SpeedHighway_Free, SpeedHighway_Main };

void SpeedHighway_Hook()
{
	RadicalHighwayHeader = speedHighwayModule;
	SetStartEndPoints(&sh_startpos, &sh_2pintro, &sh_endpos, &sh_endpos23);
}