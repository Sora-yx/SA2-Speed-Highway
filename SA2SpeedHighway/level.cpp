#include "pch.h"
#include "level.h"
#include "act.h"
#include "objects.h"

int CurrentSADXLevel = 0;

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
static const LevelEndPosition sh_endpos23 = { LevelIDs_RadicalHighway, 0, 0x8000, 0, { 0, 10, 10}, { 10487.26, -1999.75, 10216.84 } };

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
			njPopMatrixEx();

		}
		break;
	case 2:
		njSetTexture(&bg_highway03_TEXLIST);
		njPushMatrixEx();
		njTranslateV(0, position);
		njScaleV_(&SkyboxScale_SH[CurrentAct]);
		DrawObject(SH_BG[3]->getmodel());
		njPopMatrixEx();
		break;
	}

	njControl3D_Restore();
}

void __cdecl BgExec_SH(ObjectMaster* a1)
{

	EntityData1* v1; // eax
	EntityData1* data = a1->Data1.Entity;
	float v2; // ecx
	Float v3; // edx
	Float v4; // eax
	NJS_VECTOR a2; // [esp+4h] [ebp-Ch] BYREF

	if (!MainCharObj1[0] || !data)
		return;

	switch (CurrentAct) {
	case 0:
	case 1:
	default:
		if ((double)rand() * 0.000030517578125 < 0.05000000074505806)
		{
			if (MainCharObj1[1])
			{
				v1 = MainCharObj1[FrameCountIngame & 1];
				v2 = v1->Position.x;
				v3 = v1->Position.y;
				v4 = v1->Position.z;
			}
			else
			{
				v2 = MainCharObj1[0]->Position.x;
				v3 = MainCharObj1[0]->Position.y;
				v4 = MainCharObj1[0]->Position.z;
			}
			a2.z = v4;
			a2.y = v3;
			a2.x = ((double)rand() * 0.000030517578125 - 0.5) * 530.0 + v2;
			a2.y = ((double)rand() * 0.000030517578125 - 0.5) * 530.0 + a2.y;
			a2.z = ((double)rand() * 0.000030517578125 - 0.5) * 530.0 + a2.z;


			Play3DSound_Pos(sound_SHWind, &a2, 0, 0, 80);

		}
		break;
	case 2:
		if (++data->field_6 == 360) {
			PlaySoundProbably(sound_SHPeople, 0, 0, 80);
			data->field_6 = 0;
		}
		break;
	}
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
		data->Action = 1;
		break;
	case 1:

		if (CurrentAct == 1) {

			LoadChildObject(LoadObj_Data1, CheckAndSetControl, obj);
			LoadChildObject(LoadObj_Data1, SetSonicRunningOnBulding, obj);

			data->Action = 2;
		}
		break;
	case 2:
		if (CurrentAct == 2) {
			LoadChildObject(LoadObj_Data1, CheckAndSetControl, obj);
			data->Action = 3;
		}
		break;
	case 3:
		if (++data->field_2 == 20) {
			SetCameraPos(72.13f, 40.46f, 222.96f);
		}
		data->Action = 4;
		break;
	}

	CheckAndKillPlayer(obj);
}


void LoadSHAct(int act)
{
	PrintDebug("[SH] Loading act %i", act);

	PerfectRings_StartCount = PerfectRings;

	StopMusic();
	DeleteSetHandler();
	DeleteSETObjects();
	DeleteDeathZones();

	CurrentAct = act;

	switch (act)
	{
	case 0:
		LoadLandManager_(Act1LandInfo->getlandtable());
		LoadLevelLayout(&SpeedHighwayObjListH, "speed-highway0-set-s.bin", "SET0048_2P_U.bin");
		LoadLevelMusic((char*)"highway1.adx");
		LoadStagePaths(PathList_SpeedHighway0);
		break;
	case 1:
		LoadLandManager_(Act2LandInfo->getlandtable());
		LoadLevelLayout(&SpeedHighwayObjListH, "speed-highway1-set-s.bin", "SET0048_2P_U.bin");
		break;
	case 2:
		LoadLandManager_(Act3LandInfo->getlandtable());
		LoadLevelLayout(&SpeedHighwayObjListH, "speed-highway2-set-s.bin", "SET0048_2P_U.bin");
		LoadLevelMusic((char*)"highway3.adx");
		break;
	}

	if (CurrentAct < 1)
		LoadSH_DeathZones(act);

	for (uint8_t i = 0; i < MAXPLAYERS; i++) {

		if (MainCharacter[i])
			SetLevelPosAndRot(i);
	}

	return;
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
	FreeDZModels();
	DropRingsFunc_ptr = nullptr;
	DisplayItemBoxItemFunc_ptr = nullptr;

	if (ParticleCoreTask)
	{
		DeleteObject_(ParticleCoreTask);
		ParticleCoreTask = 0;
	}

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

	DropRingsFunc_ptr = DropRings;
	DisplayItemBoxItemFunc_ptr = DisplayItemBoxItem;

	SetDrawingPlanes(-3.0f, -65535.0f);

	// Chaos Drive Function Pointers
	dword_1DE4680 = (void*)0x6B6C20;
	dword_1DE4684 = (void*)0x6BBAE0;
	dword_1DE4688 = (void*)0x6BC450;
	dword_1DE468C = (void*)0x6BC4A0;

	// Get starting act
	CurrentAct = 0;

	CurrentSADXLevel = LevelIDs_SpeedHighway;
	LoadGreenForestCharAnims(); //used for helico grab animation
	if (!ParticleCoreTask)
	{
		ParticleCoreTask = AllocateObjectMaster(ParticleCoreTask_Load, 1, "ParticleCoreTask");
	}

	LoadSH_DeathZonesModel();
	LoadModelBG_SH();
	LoadModelsSH();
	LoadTexPacks((TexPackInfo*)0x109E810, (NJS_TEXLIST***)0x109E748);

	ObjectMaster* bg = AllocateObjectMaster(BgExec_SH, 1, "BgExec");
	if (bg)
	{
		EntityData1* data = AllocateEntityData1();
		if (data)
		{
			bg->Data1.Entity = data;
			bg->DisplaySub = (void(__cdecl*)(ObjectMaster*))SpeedHighway_Display;
		}
		else
		{
			DeleteObject_(bg);
		}
	}
}

static const LevelHeader speedHighwayModule = { "SPDHIGH", 0, SpeedHighway_Init, SpeedHighway_Free, SpeedHighway_Main };

void SpeedHighway_Hook()
{
	RadicalHighwayHeader = speedHighwayModule;
	SetStartEndPoints(&sh_startpos, &sh_2pintro, &sh_endpos, &sh_endpos23);
}