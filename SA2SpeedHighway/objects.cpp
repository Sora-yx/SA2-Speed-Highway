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


CollisionData Col_Fence = { 0, (CollisionShapes)0x3, 0x77, 0, 0, {0.0, 4.25, 0.0}, 13.0, 4.25, 2.75, 0.0, 0, 0, 0 };

CollisionData Col_Og[] = { 
	{ 0, (CollisionShapes)0x1, 0x77, 0, 0, {34.0, 25.0, 0.0}, 2.5, 27.0, 0.0, 0.0, 0, 0, 0 },
	{ 0, (CollisionShapes)0x1, 0x77, 0, 0, {-34.0, 25.0, 0.0}, 2.5, 27.0, 0.0, 0.0, 0, 0, 0 },
	{ 0, (CollisionShapes)0x3, 0x77, 0, 0, {0.0, 50.0, 0.0}, 35.0, 10.0, 2.0, 0.0, 0, 0, 0 },
};

void LoadModelsSH()
{
	LoadTextureList("OBJ_HIGHWAY", &highwayObj_TEXLIST);
	LoadTextureList("OBJ_HIGHWAY2", &highwayObj2_TEXLIST);

	LoadAssets_Jammer();
	LoadCraneModels();
	LoadSHGlass();
	LoadLampModel();

	SH_Cone[0] = LoadMDL("cone_cone1", ModelFormat_Chunk);
	SH_Cone[1] = LoadMDL("cone_cone2", ModelFormat_Chunk);
	SH_Bell[0] = LoadMDL("SH-Bell0", ModelFormat_Chunk);
	SH_Bell[1] = LoadMDL("SH-Bell1", ModelFormat_Chunk);
	SH_SLight = LoadMDL("SH-Slight", ModelFormat_Chunk);
	SH_GFF = LoadMDL("SH-Fence", ModelFormat_Chunk);
	SH_Ogg = LoadMDL("SH-Ogg", ModelFormat_Chunk);

	//platform stuff
	SH_OOStp4S = LoadMDL("SH-OOstp4S", ModelFormat_Chunk);
	SH_OOStp4T = LoadMDL("SH-OOstp4T", ModelFormat_Chunk);
	SH_OOStp4SCol = LoadMDL("SH-OOstp4SCol", ModelFormat_Basic);
	SH_OOStp4TCol = LoadMDL("SH-OOstpTCol", ModelFormat_Basic);

}

void FreeModelsSH()
{
	FreeTexList(&highwayObj_TEXLIST);
	FreeTexList(&highwayObj2_TEXLIST);

	FreeAssets_Jammer();
	FreeCraneModels();
	FreeSHGlass();

	FreeMDL(SH_Lamp[0]);

	for (uint8_t i = 0; i < 2; i++) {
		FreeMDL(SH_Cone[i]);
		FreeMDL(SH_Bell[i]);
		}

		FreeMDL(SH_SLight);
		FreeMDL(SH_GFF);
		FreeMDL(SH_Ogg);
	
}

void __cdecl GenericSHDisplay(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrixEx();
	njTranslateEx(&data->Position);
	njRotateZXY(&data->Rotation);
	DrawObject((NJS_OBJECT*)obj->field_4C);
	njPopMatrixEx();
}

void __cdecl SHGFF_Main(ObjectMaster* a1)
{
	ObjectMaster* v1; // edi
	EntityData1* v2; // ebx
	double v3; // st7
	double v4; // st7
	Angle v5; // eax
	Angle v6; // eax
	Angle v7; // eax
	ObjectMaster* v8; // eax
	Angle v9; // esi
	ObjectMaster* v10; // eax
	double v11; // st7
	double v12; // st7
	Angle v13; // eax
	Angle v14; // eax
	Angle v15; // eax
	int i; // [esp+18h] [ebp-40h]
	int j; // [esp+18h] [ebp-40h]
	Vector3 vs; // [esp+1Ch] [ebp-3Ch] BYREF
	Vector3 a2; // [esp+28h] [ebp-30h] BYREF
	Rotation a3; // [esp+34h] [ebp-24h] BYREF
	Rotation v21; // [esp+40h] [ebp-18h] BYREF
	Vector3 a; // [esp+4Ch] [ebp-Ch] BYREF

	v1 = a1;
	v2 = a1->Data1.Entity;
	a3.x = 0;
	a3.y = 0;
	a3.z = 0;
	vs.x = 0.0;
	vs.y = 0.0;
	vs.z = 0.0;

	if (!ClipObject(a1, 2890000.0))
	{
		switch ((char)v2->Action)
		{
		case 0:
			for (i = 0; i < (int)((unsigned __int64)v2->Scale.x + 1); i++)
			{
				v3 = (double)i;
				if (i % 2)
				{
					v4 = ceil(v3 * 0.5) * v2->Scale.y;
				}
				else
				{
					v4 = v3 * v2->Scale.y * -0.5;
				}
				vs.z = v4;
				njPushMatrix(_nj_unit_matrix_);
				njTranslateV(0, &v2->Position);
				v5 = v2->Rotation.z;
				if (v5)
				{
					njRotateZ(0, (unsigned __int16)v5);
				}
				v6 = v2->Rotation.x;
				if (v6)
				{
					njRotateX(0, (unsigned __int16)v6);
				}
				v7 = v2->Rotation.y;
				if (v7)
				{
					njRotateY(0, (unsigned __int16)v7);
				}
				njCalcVector(0, &vs, &a2, true);
				njAddVector(&a2, &v2->Position);
				njPopMatrixEx();
				a3.y = (unsigned __int64)(v2->Scale.z * 65536.0 * 0.002777777777777778);


				v8 = LoadChildObject(
					(LoadObj)2,
					(void(__cdecl*)(ObjectMaster*))a1->field_4C,
					v1);
				if (v8)
				{
					v8->Data1.Entity->Position = a2;
					v9 = a3.y;
					v8->Data1.Entity->Rotation.x = 0;
					v8->Data1.Entity->Rotation.y = v9;
					v8->Data1.Entity->Rotation.z = 0;
				}

			}

			v2->Action = 1;


			break;
		case 1:

			v10 = a1->Child;
			if (v10)
			{
				while (v10->MainSub != DeleteObject_)
				{
					v10 = v10->NextObject;

				}
				v2->Action = 3;
			}

			break;
		case 3:
			a1->MainSub = DeleteObject_;
			break;

		default:
			return;
		}
	}
}



void __cdecl OFence(ObjectMaster* obj)
{
	EntityData1* v1 = obj->Data1.Entity;
	InitCollision(obj, &Col_Fence, 1, 4u);
	obj->field_4C = SH_GFF->getmodel();
	obj->MainSub = MainSubGlobalCol;
	obj->DisplaySub = GenericSHDisplay;
}

void Load_GFF(ObjectMaster* tp)
{
	EntityData1* v1 = tp->Data1.Entity;
	if (v1->Action == 0) {
		tp->MainSub = SHGFF_Main;
		tp->field_1C = OFence;
	}
}

void LoadOGG(ObjectMaster* obj) {
	InitCollision(obj, Col_Og, 3, 4u);
	obj->field_4C = SH_Ogg->getmodel();
	obj->MainSub = MainSubGlobalCol;
	obj->DisplaySub = GenericSHDisplay;
	return;
}

void Load_OStp4s(ObjectMaster* obj) {


	obj->Data2.Undefined = SH_OOStp4SCol->getmodel();
	obj->field_4C = SH_OOStp4S->getmodel();
	obj->MainSub = MainSubGlobalDynCol;
	obj->DisplaySub = GenericSHDisplay;
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
	obj->DisplaySub = GenericSHDisplay;
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
	{ (LoadObj)6 }, //3, 1, 1000000, 0, (ObjectFuncPtr)0x61C740, "O EV   " } /* "O EV   " */,
	{ (LoadObj)10 }, //3, 1, 1000000, 0, (ObjectFuncPtr)0x61BDC0, "O FOUNT" } /* "O FOUNT" */,
	{ (LoadObj)6, 3, 1, 1000000, OCrane },
	{ (LoadObj)LoadObj_Data1, 3, 1, 1000000, OGlass}, /* "O GLASS " */
	{ (LoadObj)LoadObj_Data1, 3, 1, 2250000, OGlass2}, /* "O GLASS " */
	{ (LoadObj)6 },//3, 0, 0, 0, (ObjectFuncPtr)0x614E40, "HIGH RAFT A" } /* "HIGH RAFT A" */,
	{ (LoadObj)6 },//3, 0, 0, 0, (ObjectFuncPtr)0x614E60, "HIGH RAFT C" } /* "HIGH RAFT C" */,
	{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x61A330, "O TANKA" } /* "O TANKA" */,
	{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x619960, "O SIGNB" } /* "O SIGNB" */,
	{ (LoadObj)6 }, //3, 1, 1000000, 0, (ObjectFuncPtr)0x619340, "O TurnAsi" } /* "O TurnAsi" */,
	{ (LoadObj)2, 3, 1, 25000000, SHSLIGHT, }, /* "O SLIGHT" */
	{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x6188E0, "O ARCADE01" } /* "O ARCADE01" */,
	{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x6188F0, "O ARCADE02" } /* "O ARCADE02" */,
	{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x618900, "O ARCADE03" } /* "O ARCADE03" */,
	{ (LoadObj)6, 3, 1, 1000000, ObjectJammer } /* "O JAMER" */,
	{ (LoadObj)LoadObj_Data1, 3, 1, 2250000, Load_OStp4s }, /* "O STP4S" */
	{ (LoadObj)6, 3, 1, 2250000, Load_OStp4t,} /* "O STP4T" */,
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
	{ (LoadObj)2, 3, 0, 0, SHLAMP01, } /* "O LAMP01" */,
	{ (LoadObj)2, 3, 0, 0, SHLAMP02, },
	{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x616210, "O PinPin" } /* "O PinPin" */,
	{ (LoadObj)6 },// 3, 1, 4000000, 0, (ObjectFuncPtr)0x616150, "O Escalator1" } /* "O Escalator1" */,
	{ (LoadObj)6 },// 3, 1, 4000000, 0, (ObjectFuncPtr)0x6161B0, "O Escalator2" } /* "O Escalator2" */,
	{ (LoadObj)2 },//3, 1, 4000000, 0, (ObjectFuncPtr)0x615EB0, "O Antena" } /* "O Antena" */,
	{ (LoadObj)3, 0, 0, 0, OCone1, }, /* "O Cone1" */
	{ (LoadObj)3, 0, 0, 0, OCone2, }, /* "O Cone1" */
	{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x615990, "O Curb" } /* "O Curb" */,
	{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x615940, "O Fence02" } /* "O Fence02" */,
	{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x615920, "O GREENE" } /* "O GREENE" */,
	{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x615780, "O SIBA01" } /* "O SIBA01" */,
	{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x6157D0, "O SIBA02" } /* "O SIBA02" */,
	{ (LoadObj)6 },// 3, 1, 250000, 0, (ObjectFuncPtr)0x615740, "O Tokei" } /* "O Tokei" */,
	{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x6155A0, "O Lmpa" } /* "O Lmpa" */,
	{ (LoadObj)2, 3, 0, 0, LoadOGG,  } /* "O GG" */,
	{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x615450, "O FF" } /* "O FF" */,
	{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x6153C0, "O StPlant01" } /* "O StPlant01" */,
	{ (LoadObj)2 },//5, 0, 0, 0, (ObjectFuncPtr)0x615310, "O StPlant02" } /* "O StPlant02" */,
	{ (LoadObj)2 },//3, 1, 1000000, 0, (ObjectFuncPtr)0x613E30, "O HeliA" } /* "O HeliA" */,
	{ (LoadObj)2 },//3, 1, 1000000, 0, (ObjectFuncPtr)0x613E80, "O HeliB" } /* "O HeliB" */,
	{ (LoadObj)2, 3, 1, 1000000, OHwBell, }, /* "O HW BELL" */
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
	{ (LoadObj)2, 2, 0, 0, nullptr },
	{ (LoadObj)2 },//2, 0, 0, 0, (ObjectFuncPtr)0x7A1AA0, "O TIKAL" } /* "O TIKAL" */,
	{ (LoadObj)2 },//2, 0, 0, 0, (ObjectFuncPtr)0x7A9C60, "O HINT" } /* "O HINT" */,
	{ LoadObj_Data1, 2, 0x50, 0.0, RingGroup},
	{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x614B00, "O GFENCE" } /* "O GFENCE" */,
	{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x614B30, "O GCURB" } /* "O GCURB" */,
	{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x614B60, "O GFENCE02" } /* "O GFENCE02" */,
	{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x614B90, "O GPINPIN" } /* "O GPINPIN" */,
	{ (LoadObj)2, 3, 0, 0, Load_GFF, } /* "O GFF" */,
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

