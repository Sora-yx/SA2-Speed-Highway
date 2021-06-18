#include "pch.h"
#include "obj-common.h"
#include "objects.h"
#include "sh-light.h"
#include "sh-cage.h"
#include "sh-glass.h"
#include "sh-lamp.h"
#include "sh-cone.h"
#include "sh-bell.h"
#include "sh-jammer.h"
#include "SH-Fountain.h"

static NJS_TEXNAME highwayObj_Tex[118]{};
NJS_TEXLIST highwayObj_TEXLIST = { arrayptrandlength(highwayObj_Tex, Uint32) };

static NJS_TEXNAME highwayObj2_Tex[54]{};
NJS_TEXLIST highwayObj2_TEXLIST = { arrayptrandlength(highwayObj2_Tex, Uint32) };

static ModelInfo* SH_GFF;
static ModelInfo* SH_Ogg;
static ModelInfo* SH_OOStp4S;
static ModelInfo* SH_OOStp4T;
static ModelInfo* SH_OOStp4SCol;
static ModelInfo* SH_OOStp4TCol;
static ModelInfo* SH_Fence02;

static ModelInfo* SH_Bench;
static ModelInfo* SH_Plant1;
static ModelInfo* SH_Plant2;
static ModelInfo* SH_Lmpa;
static ModelInfo* SH_Kanban[2];
static ModelInfo* SH_Siba[2];
static ModelInfo* SH_HighRaft[2];
static ModelInfo* SH_HighRaftCol[2];



CollisionData Col_Fence = { 0, (CollisionShapes)0x3, 0x77, 0, 0, {0.0, 4.25, 0.0}, 13.0, 4.25, 2.75, 0.0, 0, 0, 0 };
CollisionData col_Fence02 = { 0, (CollisionShapes)0x3, 0x77, 0, 0, {0.0, 4.5, 0.0}, 10.0, 4.5, 1.0, 0.0, 0, 0, 0 };

CollisionData Col_Og[] = {
	{ 0, (CollisionShapes)0x1, 0x77, 0, 0, {34.0, 25.0, 0.0}, 2.5, 27.0, 0.0, 0.0, 0, 0, 0 },
	{ 0, (CollisionShapes)0x1, 0x77, 0, 0, {-34.0, 25.0, 0.0}, 2.5, 27.0, 0.0, 0.0, 0, 0, 0 },
	{ 0, (CollisionShapes)0x3, 0x77, 0, 0, {0.0, 50.0, 0.0}, 35.0, 10.0, 2.0, 0.0, 0, 0, 0 },
};

CollisionData BenchCol[] = {
	{ 0, (CollisionShapes)0x3, 0x77, 0, 0, {0}, 12.0, 5.0, 3.0, 0.0, 0, 0, 0 },
	{ 0, (CollisionShapes)0x3, 0x77, 0, 0, {0.0, 0.0, 3.0}, 12.0, 12.0, 1.0, 0.0, 0, 0, 0 },
};

CollisionData LmpaCol = { 0, (CollisionShapes)0x0, 0x77, 0, 0, {0.0, -1.0, 7.0}, 2.0, 0.0, 0.0, 0.0, 0, 0, 0 };

CollisionData KanbanaCol = { 0, (CollisionShapes)0x0, 0x77, 0, 0, {0.0, -5.0, 0.0}, 5.0, 0.0, 0.0, 0.0, 0, 0, 0 };

CollisionData Siba01col = { 0, (CollisionShapes)3, 0x77, 0, 0, {0}, 20.0, 2.0, 20.0, 0.0, 0, 0, 0 };
CollisionData Siba02col = { 0, (CollisionShapes)0, 1, 0x77, 0, 0, {0}, 40.0, 2.0, 0.0, 0.0, 0, 0, 0 };

CollisionData SHPlantCol = { 0, (CollisionShapes)0x6, 0x77, 0, 0, {0.0, 8.0, 0.0}, 1.0, 8.0, 0.0, 0.0, 0, 0, 0 };

void LoadModelsSH()
{
	LoadTextureList("OBJ_HIGHWAY", &highwayObj_TEXLIST);
	LoadTextureList("OBJ_HIGHWAY2", &highwayObj2_TEXLIST);

	LoadAssets_Jammer();
	LoadCraneModels();
	LoadSHGlass();
	LoadLampModel();
	LoadModel_TurnAsi();

	SH_SLight = LoadMDL("SH-Slight", ModelFormat_Chunk);
	SH_GFF = LoadMDL("SH-Fence", ModelFormat_Chunk);
	SH_Fence02 = LoadMDL("SH-Fence02", ModelFormat_Chunk);
	SH_Ogg = LoadMDL("SH-Ogg", ModelFormat_Chunk);

	//platform stuff
	SH_OOStp4S = LoadMDL("SH-OOstp4S", ModelFormat_Chunk);
	SH_OOStp4T = LoadMDL("SH-OOstp4T", ModelFormat_Chunk);

	SH_Bench = LoadMDL("SH-Bench", ModelFormat_Chunk);
	SH_Plant1 = LoadMDL("SH-Plant1", ModelFormat_Chunk);
	SH_Plant2 = LoadMDL("SH-Plant2", ModelFormat_Chunk);
	SH_Lmpa = LoadMDL("SH-Lmpa", ModelFormat_Chunk);
	SH_Kanban[0] = LoadMDL("SH-Kanbana", ModelFormat_Chunk);
	SH_Kanban[1] = LoadMDL("SH-Kanbanb", ModelFormat_Chunk);
	SH_Siba[0] = LoadMDL("SH-Siba01", ModelFormat_Chunk);
	SH_Siba[1] = LoadMDL("SH-Siba02", ModelFormat_Chunk);
	SH_HighRaft[0] = LoadMDL("sh-highraftA", ModelFormat_Chunk);
	SH_HighRaft[1] = LoadMDL("sh-highraftC", ModelFormat_Chunk);

	LoadHydModel();
	LoadBellModels();
	LoadConeModels();
	LoadFountainModel();
	LoadHelicoModel();
	LoadModel_Oev();
	Load_NeonAssets();

	LoadArcadesModels();
	LoadPosterModels();
	LoadTokeiModels();
	LoadGreenModels();
	LoadSH_EscalatorsModels();

	//Load Collisions model for DynCol
	SH_OOStp4SCol = LoadMDL("SH-OOstp4SCol", ModelFormat_Basic);
	SH_OOStp4TCol = LoadMDL("SH-OOstpTCol", ModelFormat_Basic);

	SH_HighRaftCol[0] = LoadMDL("sh-highraftA", ModelFormat_Basic);
	SH_HighRaftCol[1] = LoadMDL("sh-highraftC", ModelFormat_Basic);

	return;
}

void FreeModelsSH()
{
	FreeTexList(&highwayObj_TEXLIST);
	FreeTexList(&highwayObj2_TEXLIST);

	FreeAssets_Jammer();
	FreeCraneModels();
	FreeSHGlass();
	DeleteFountainModel();

	FreeMDL(SH_Lamp[0]);

	for (uint8_t i = 0; i < 2; i++) {
		FreeMDL(SH_Cone[i]);
		FreeMDL(SH_Bell[i]);

		FreeMDL(SH_Kanban[i]);
	}

	FreeMDL(SH_SLight);
	FreeMDL(SH_GFF);
	FreeMDL(SH_Ogg);

	FreeMDL(SH_Bench);
	FreeMDL(SH_Plant1);
	FreeMDL(SH_Plant2);
	FreeMDL(SH_Lmpa);

	FreeModel_TurnAsi();
	Free_Neon();

	FreePosterModels();
	FreeArcadesModels();

	FreeTokeiModels();
	FreeGreenModels();
	FreeHydModel();
	return;
}

void __cdecl GenericSHDisplay_RotY(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;


	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrixEx();
	njTranslateEx(&data->Position);
	njRotateY(0, data->Rotation.y);

	DrawObject((NJS_OBJECT*)obj->field_4C);
	njPopMatrixEx();
}

void __cdecl GenericSHDisplayZXY(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrixEx();
	njTranslateEx(&data->Position);
	njRotateZXY(&data->Rotation);

	DrawObject((NJS_OBJECT*)obj->field_4C);
	njPopMatrixEx();
}

void __cdecl OFence2(ObjectMaster* obj)
{
	EntityData1* v1 = obj->Data1.Entity;
	InitCollision(obj, &col_Fence02, 1, 4u);
	obj->field_4C = SH_Fence02->getmodel();
	obj->MainSub = MainSubGlobalCol;
	obj->DisplaySub_Delayed1 = GenericSHDisplayZXY;
}


void __cdecl OFence(ObjectMaster* obj)
{
	EntityData1* v1 = obj->Data1.Entity;
	InitCollision(obj, &Col_Fence, 1, 4u);
	obj->field_4C = SH_GFF->getmodel();
	obj->MainSub = MainSubGlobalCol;
	obj->DisplaySub_Delayed1 = GenericSHDisplayZXY;
}

void __cdecl SH_GlobalMainWithCalcRot(ObjectMaster* a1)
{
	EntityData1* data = a1->Data1.Entity;

	for (int i = 0; i < static_cast<int>(data->Scale.x) + 1; i++)
	{
		njPushUnitMatrix();
		njTranslateEx(&data->Position);
		njRotateZXY(&data->Rotation);

		if (i % 2)
		{
			njTranslate(CURRENT_MATRIX, 0.0f, 0.0f, ceil(static_cast<float>(i) * 0.5f) * data->Scale.y);
		}
		else
		{
			njTranslate(CURRENT_MATRIX, 0.0f, 0.0f, static_cast<float>(i) * data->Scale.y * -0.5f);
		}

		NJS_VECTOR pos;

		njGetTranslation(CURRENT_MATRIX, &pos);
		njPopMatrixEx();

		ObjectMaster* child = LoadChildObject((LoadObj)(LoadObj_UnknownB | 6 | LoadObj_UnknownA | LoadObj_Data1), (void(__cdecl*)(ObjectMaster*))a1->field_4C, a1);

		if (child)
		{
			child->Data1.Entity->Position = pos;
			child->Data1.Entity->Rotation.x = 0;
			child->Data1.Entity->Rotation.y = (data->Scale.z * 65536.0 * 0.002777777777777778);
			child->Data1.Entity->Rotation.z = 0;
		}
	}

	a1->MainSub = nullptr;
}

void Load_GFF(ObjectMaster* tp)
{
	EntityData1* v1 = tp->Data1.Entity;
	tp->field_4C = OFence;
	tp->MainSub = SH_GlobalMainWithCalcRot;
	tp->DeleteSub = j_DeleteChildObjects;
}

void Load_OGFence02(ObjectMaster* tp)
{
	EntityData1* v1 = tp->Data1.Entity;
	tp->field_4C = OFence2;
	tp->MainSub = SH_GlobalMainWithCalcRot;
	tp->DeleteSub = j_DeleteChildObjects;
}


void LoadOGG(ObjectMaster* obj) {
	InitCollision(obj, Col_Og, 3, 4u);
	obj->field_4C = SH_Ogg->getmodel();
	obj->MainSub = MainSubGlobalCol;
	obj->DisplaySub = GenericSHDisplayZXY;
	return;
}

void Load_OStp4s(ObjectMaster* obj) {
	obj->Data2.Undefined = SH_OOStp4SCol->getmodel();
	obj->field_4C = SH_OOStp4S->getmodel();
	obj->MainSub = MainSubGlobalDynCol;
	obj->DisplaySub = GenericSHDisplayZXY;
}


void Load_OStp4t(ObjectMaster* obj) {

	if (CurrentCharacter == Characters_Tails) {
		obj->Data2.Undefined = SH_OOStp4TCol->getmodel();
		obj->field_4C = SH_OOStp4T->getmodel();
	}
	else {
		obj->Data1.Entity->Position.y -= 2;
		obj->MainSub = Load_OStp4s;
		return;
	}
	obj->MainSub = MainSubGlobalDynCol;
	obj->DisplaySub = GenericSHDisplayZXY;
}

void __cdecl sub_49CE60(EntityData1* a1, EntityData2* a2)
{
	a1->Status &= 0xFFC7u;
	if (a2)
	{
		a2->Acceleration.z = 0.0;
		a2->Acceleration.y = 0.0;
		a2->Acceleration.x = 0.0;
	}
}


void OHighRaft_Main(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;
	if (!ClipSetObject(obj))
	{
		if (data->Action == 0) {

			obj->DeleteSub = DeleteFunc_DynCol;
			DynCol_AddFromObject(obj, SH_HighRaftCol[0]->getmodel(), &data->Position, data->Rotation.y, SurfaceFlag_Solid);
			data->Action = 1;
		}
	}
}

void __cdecl OHighRaftC(ObjectMaster* obj)
{
	obj->Data2.Undefined = SH_HighRaftCol[1]->getmodel();
	obj->field_4C = SH_HighRaft[1]->getmodel();
	obj->MainSub = MainSubGlobalDynCol;
	obj->DisplaySub = GenericSHDisplayZXY;
}


void __cdecl OHighRaftA(ObjectMaster* obj)
{
	obj->Data2.Undefined = SH_HighRaftCol[0]->getmodel();
	obj->field_4C = SH_HighRaft[0]->getmodel();
	obj->MainSub = MainSubGlobalDynCol;
	obj->DisplaySub = GenericSHDisplayZXY;
}

void Load_GraftC(ObjectMaster* tp)
{
	EntityData1* v1 = tp->Data1.Entity;
	tp->field_4C = OHighRaftC;
	tp->MainSub = SH_GlobalMainWithCalcRot;
	tp->DeleteSub = j_DeleteChildObjects;
}


void Load_GraftA(ObjectMaster* tp)
{
	EntityData1* v1 = tp->Data1.Entity;
	tp->field_4C = OHighRaftA;
	tp->MainSub = SH_GlobalMainWithCalcRot;
	tp->DeleteSub = j_DeleteChildObjects;
}


void OSiba02(ObjectMaster* obj) {

	InitCollision(obj, &Siba02col, 1, 4u);
	obj->field_4C = SH_Siba[1]->getmodel();
	obj->MainSub = MainSubGlobalCol;
	obj->DisplaySub = GenericSHDisplayZXY;
	return;
}


void OSiba01(ObjectMaster* obj) {

	InitCollision(obj, &Siba01col, 1, 4u);
	obj->Data1.Entity->Collision->Range = 29.0;
	obj->field_4C = SH_Siba[0]->getmodel();
	obj->MainSub = MainSubGlobalCol;
	obj->DisplaySub = GenericSHDisplayZXY;
	return;
}


void OKanbanb(ObjectMaster* obj) {

	InitCollision(obj, &KanbanaCol, 1, 4u);
	obj->Data1.Entity->Collision->Range = 10.0;
	obj->field_4C = SH_Kanban[1]->getmodel();
	obj->MainSub = MainSubGlobalCol;
	obj->DisplaySub = GenericSHDisplay_RotY;
	return;
}

void OKanbana(ObjectMaster* obj) {

	InitCollision(obj, &KanbanaCol, 1, 4u);
	obj->Data1.Entity->Collision->Range = 10.0;
	obj->field_4C = SH_Kanban[0]->getmodel();
	obj->MainSub = MainSubGlobalCol;
	obj->DisplaySub = GenericSHDisplay_RotY;
	return;
}

void LoadBench(ObjectMaster* obj) {
	InitCollision(obj, BenchCol, 2, 4u);
	obj->field_4C = SH_Bench->getmodel();
	obj->MainSub = MainSubGlobalCol;
	obj->DisplaySub = GenericSHDisplayZXY;
	return;
}


void LoadLmpa(ObjectMaster* obj) {
	InitCollision(obj, &LmpaCol, 1, 4u);
	obj->Data1.Entity->Collision->Range = 9.69;
	obj->field_4C = SH_Lmpa->getmodel();
	obj->MainSub = MainSubGlobalCol;
	obj->DisplaySub = GenericSHDisplayZXY;
	return;
}

void OStPlant02(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;

	if (data->Action == 0) {
		obj->field_4C = SH_Plant2->getmodel();
		obj->DisplaySub = GenericSHDisplay_RotY;
		data->Action = 1;
	}
}

void OStPlant01(ObjectMaster* obj) {
	InitCollision(obj, &SHPlantCol, 1, 4u);
	obj->Data1.Entity->Collision->Range = 32.0;
	obj->field_4C = SH_Plant1->getmodel();
	obj->MainSub = MainSubGlobalCol;
	obj->DisplaySub = GenericSHDisplay_RotY;
}


static ObjectListEntry SpeedHighwayObjList[] = {
	{ LoadObj_Data1, 2, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, 2, 0x20, 0.0, (ObjectFuncPtr)SpringA_Main },
	{ LoadObj_Data1, 2, 0x20, 0.0, SpringB_Main },
	{ (LoadObj)(LoadObj_Data2 | LoadObj_Data1), 2, 2, 0.0, DashPanel_Main },
	{ (LoadObj)(LoadObj_Data1), 2, 0, 0.0, (ObjectFuncPtr)IRONBALL2 },

	{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x7A3E50, "O FeBJG" } /* "O FeBJG",
	{ (LoadObj)2 }, //3, 0, 0, 0, (ObjectFuncPtr)0x7A30E0, "O TOGE" } /* "O TOGE" ,
	{ (LoadObj)3 }, //3, 4, 0, 0, (ObjectFuncPtr)0x4A3420, "O EME P" } /* "O EME P" ,
	{ (LoadObj)2, 2, 1, 640000, (ObjectFuncPtr)0x6C63C0, },
	{ (LoadObj)6 },// 3, 0, 0, 0, (ObjectFuncPtr)0x4CBA80, "O SWITCH" } /* "O SWITCH" */
	{ (LoadObj)10 },// 3, 0, 0, 0, (ObjectFuncPtr)0x7A2B60, "CMN KUSA" } /* "CMN KUSA" */,
	{ (LoadObj)14 }, //3, 1, 2250000, 0, (ObjectFuncPtr)0x7A26F0, "CMN_DRING" } /* "CMN_DRING" */,
	{ (LoadObj)2 }, //3, 0, 0, 0, (ObjectFuncPtr)0x7A21C0, "O BALOON" } /* "O BALOON" */,
	{ (LoadObj)(LoadObj_Data1), 2, 0x60, 0.0, ItemBox_Main }, //3, 0, 0, 0, (ObjectFuncPtr)0x4D6F10, "O ITEMBOX" } /* "O ITEMBOX" */,
	{ (LoadObj)6, 2, 0, 0, (ObjectFuncPtr)0x6D4EA0,  } /* "ROCKET   " */,
	{ (LoadObj)6, 2, 0, 0, (ObjectFuncPtr)0x6D4EA0,  } /* "ROCKET   " */,
	{ (LoadObj)6, 2, 0, 0, (ObjectFuncPtr)0x6CE4C0,  } /* "ROCKETMISSSILE" */,
	{ (LoadObj)6, 2, 0, 0, (ObjectFuncPtr)0x6CE4C0,  } /* "ROCKETMISSSILE" */,
	{ (LoadObj)2 },// 2, 1, 4000000, 0, (ObjectFuncPtr)0x4B8DC0, "O JPanel" } /* "O JPanel" */,
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA | LoadObj_UnknownB), 2, 0, 0, Checkpoint_Main },
	{ (LoadObj)(LoadObj_Data1) },// 2, DistObj_UseDist, 640000.0, (ObjectFuncPtr)WALL },
	{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x7A9140, "O KN HINT" } /* "O KN HINT" */,
	{ (LoadObj)(LoadObj_Data1), 2, 0, 0, (ObjectFuncPtr)LongSpring_Main },
	{ (LoadObj)6, 3, 1, 1000000, OEv },
	{ (LoadObj)10, 3, 1, 1000000, LoadFountain,} /* "O FOUNT" */,
	{ (LoadObj)6, 3, 1, 1000000, OCrane },
	{ (LoadObj)LoadObj_Data1, 3, 1, 1000000, OGlass}, /* "O GLASS " */
	{ (LoadObj)LoadObj_Data1, 3, 1, 2250000, OGlass2}, /* "O GLASS " */
	{ (LoadObj)6, 3, 0, 0, OHighRaftA }/* "HIGH RAFT A" */,
	{ (LoadObj)6, 3, 0, 0, OHighRaftC }/* "HIGH RAFT C" */,
	{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x61A330, "O TANKA" } /* "O TANKA" */,
	{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x619960, "O SIGNB" } /* "O SIGNB" */,
	{ (LoadObj)6, 3, 1, 1000000, LoadTurnAsi } /* "O TurnAsi" */,
	{ (LoadObj)2, 3, 1, 25000000, SHSLIGHT, }, /* "O SLIGHT" */
	{ (LoadObj)2, 3, 0, 0, OArcade01,} /* "O ARCADE01" */,
	{ (LoadObj)2, 3, 0, 0, OArcade02,} /* "O ARCADE02" */,
	{ (LoadObj)2, 3, 0, 0, OArcade03,} /* "O ARCADE03" */,
	{ (LoadObj)6, 3, 1, 1000000, ObjectJammer } /* "O JAMER" */,
	{ (LoadObj)LoadObj_Data1, 3, 1, 2250000, Load_OStp4s }, /* "O STP4S" */
	{ (LoadObj)6, 3, 1, 2250000, Load_OStp4t,} /* "O STP4T" */,
	{ (LoadObj)14 },// 3, 1, 2250000, 0, (ObjectFuncPtr)0x618030, "O FLYST" } /* "O FLYST" */,
	{ (LoadObj)2, 3, 1, 160000, OPost1 } /* "O Post1" */,
	{ (LoadObj)2, 3, 1, 160000, OPost4 },
	{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x6178F0, "O Nbox1" } /* "O Nbox1" */,
	{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x617940, "O Nbox2" } /* "O Nbox2" */,
	{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x617990, "O Nbox3" } /* "O Nbox3" */,
	{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x6179E0, "O Nbox4" } /* "O Nbox4" */,
	{ (LoadObj)2, 3, 0, 0, LoadBench,} /* "O Bench" */,
	{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x617780, "O FENCE" } /* "O FENCE" */,
	{ (LoadObj)6, 3, 1, 6250000, ONeon1} /* "O NEON1" */,
	{ (LoadObj)6, 3, 1, 6250000, ONeon2} /* "O NEON1" */,
	{ (LoadObj)6, 3, 1, 6250000, ONeon3} /* "O NEON1" */,
	{ (LoadObj)6, 3, 1, 6250000, ONeon4} /* "O NEON1" */,
	{ (LoadObj)2, 3, 1, 160000, OPoster0} /* "O POSTER0" */,
	{ (LoadObj)2, 3, 1, 160000, OPoster1} /* "O POSTER1" */,
	{ (LoadObj)2, 3, 1, 160000, OPoster2} /* "O POSTER2" */,
	{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x6173D0, "O SIGN1" } /* "O SIGN1" */,
	{ (LoadObj)2, 3, 0, 0, OKanbana } /* "O KANBANA" */,
	{ (LoadObj)2, 3, 0, 0, OKanbanb } /* "O KANBANB" */,
	{ (LoadObj)2 },// 3, 1, 40000, 0, (ObjectFuncPtr)0x617160, "O BAKETU" } /* "O BAKETU" */,
	{ (LoadObj)2, 3, 0, 0, nullptr} /* "O HYDBASS" */,
	{ (LoadObj)6, 3, 0, 0, OGreen} /* "O GREEN" */,
	{ (LoadObj)2, 3, 0, 0, OGreena} /* "O GREENA" */,
	{ (LoadObj)2, 3, 0, 0, OGreenb}, /* "O GREENB" */
	{ (LoadObj)2, 3, 0, 0, OGreend}, /* "O GREEND" */
	{ (LoadObj)2, 3, 0, 0, SHLAMP, },// 3, 0, 0, 0, (ObjectFuncPtr)0x6163D0, "O LAMP" } /* "O LAMP" */,
	{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x616770, "O CLIGHT" } /* "O CLIGHT" */,
	{ (LoadObj)2, 3, 0, 0, SHLAMP01, } /* "O LAMP01" */,
	{ (LoadObj)2, 3, 0, 0, SHLAMP02, },
	{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x616210, "O PinPin" } /* "O PinPin" */,
	{ (LoadObj)6, 3, 1, 4000000, OEscalator1, } /* "O Escalator1" */,
	{ (LoadObj)6, 3, 1, 4000000, OEscalator2,} /* "O Escalator2" */,
	{ (LoadObj)2 },//3, 1, 4000000, 0, (ObjectFuncPtr)0x615EB0, "O Antena" } /* "O Antena" */,
	{ (LoadObj)3, 0, 0, 0, OCone1, }, /* "O Cone1" */
	{ (LoadObj)3, 0, 0, 0, OCone2, }, /* "O Cone1" */
	{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x615990, "O Curb" } /* "O Curb" */,
	{ (LoadObj)2, 3, 0, 0, nullptr } /* "O Fence02" */,
	{ (LoadObj)2, 3, 0, 0, OGreene}, /* "O GREENE" */
	{ (LoadObj)2, 3, 0, 0, OSiba01, } /* "O SIBA01" */,
	{ (LoadObj)2, 3, 0, 0, OSiba02, },
	{ (LoadObj)6, 3, 1, 250000, OTokei } /* "O Tokei" */,
	{ (LoadObj)2, 3, 0, 0, LoadLmpa, } /* "O Lmpa" */,
	{ (LoadObj)2, 3, 0, 0, LoadOGG,  } /* "O GG" */,
	{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x615450, "O FF" } /* "O FF" */,
	{ (LoadObj)2, 3, 0, 0, OStPlant01, } /* "O StPlant01" */,
	{ (LoadObj)2, 5, 0, 0, OStPlant02, } /* "O StPlant01" */,
	{ (LoadObj)2, 3, 1, 1000000, OHelia} /* "O HeliA" */,
	{ (LoadObj)2, 3, 1, 1000000, OHelib} /* "O HeliA" */,
	{ (LoadObj)2, 3, 1, 1000000, OHwBell, }, /* "O HW BELL" */
	{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x614ED0, "O HELIP L" } /* "O HELIP L" */,
	{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x614E80, "O TUNAGI" } /* "O TUNAGI" */,
	{ LoadObj_Data1, 3, 1, 2250000, RingMain },
	{ LoadObj_Data1, 2, 4, 0, Beetle_Attack },
	{ LoadObj_Data1, 2, 4, 0, Beetle_Stationary },
	{ LoadObj_Data1, 2, 4, 0, Beetle_Electric },
	{ LoadObj_Data1, 2, 4, 0.0, (ObjectFuncPtr)Robots },
	{ (LoadObj)2 },//3, 5, 360000, 0, (ObjectFuncPtr)0x4AF190, "E UNI A" } /* "E UNI A" */,
	{ (LoadObj)2 },//3, 5, 360000, 0, (ObjectFuncPtr)0x4AF500, "E UNI B" } /* "E UNI B" */,
	{ (LoadObj)2, 2, 0, 0, (ObjectFuncPtr)SPHERE, }, /* "C SPHERE" */
	{ (LoadObj)2, 2, 0, 0, (ObjectFuncPtr)CCYL, }, /* "C CYLINDER" */
	{ (LoadObj)2, 2, 0, 0, (ObjectFuncPtr)CCUBE, }, /* CUBE */
	{ (LoadObj)2, 2, 0, 0, nullptr },
	{ (LoadObj)2 },//2, 0, 0, 0, (ObjectFuncPtr)0x7A1AA0, "O TIKAL" } /* "O TIKAL" */,
	{ (LoadObj)2 },//2, 0, 0, 0, (ObjectFuncPtr)0x7A9C60, "O HINT" } /* "O HINT" */,
	{ LoadObj_Data1, 2, 0x50, 0.0, RingGroup},
	{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x614B00, "O GFENCE" } /* "O GFENCE" */,
	{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x614B30, "O GCURB" } /* "O GCURB" */,
	{ (LoadObj)2, 3, 0, 0, Load_OGFence02, },//3, 0, 0, 0, (ObjectFuncPtr)0x614B60, "O GFENCE02" } /* "O GFENCE02" */,
	{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x614B90, "O GPINPIN" } /* "O GPINPIN" */,
	{ (LoadObj)2, 3, 0, 0, Load_GFF, } /* "O GFF" */,
	{ (LoadObj)2, 3, 0, 0, Load_GraftA } /* "O GRAFTA" */,
	{ (LoadObj)2, 3, 0, 0, Load_GraftC } /* "O GRAFTA" */,
	{ (LoadObj)2, 3, 0, 0, OGgrena, } /* "O GGRENA" */,
	{ (LoadObj)2, 3, 0, 0, OGgrenb, } /* "O GGRENA" */,
	{ (LoadObj)2, 3, 0, 0, OGgrend, } /* "O GGRENA" */,
	{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x614CE0, "O GCLIGHT" } /* "O GCLIGHT" */,
	{ (LoadObj)(LoadObj_Data2 | LoadObj_Data1 | LoadObj_UnknownA | LoadObj_UnknownB), 2, 0x30, 0.0, ItemBoxAir_Main },
	{ (LoadObj)2 }// 3, 1, 3240000, 0, (ObjectFuncPtr)0x614380, "MISSILE" } /* "MISSILE" */,
};

ObjectListHead SpeedHighwayObjListH = { arraylengthandptr(SpeedHighwayObjList) };

