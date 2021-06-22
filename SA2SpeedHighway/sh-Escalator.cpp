#include "pch.h"
#include "objects.h"

static ModelInfo* SH_Escalator[2];
static ModelInfo* SH_Escalator2[2];
static ModelInfo* SH_EscalatorCol[2];


void Escalator_Display(ObjectMaster* obj) {

	Angle v6; // eax
	Angle v7; // eax
	Angle v8; // eax
	float a2; // [esp+0h] [ebp-10h]

	EntityData1* v1 = obj->Data1.Entity;

	if (!ClipObject(obj, 4161600.0))
	{
		if (IsPlayerInsideSphere(&v1->Position, 100))
		{
			(v1->Status) |= 100u;
		}
		else
		{
			(v1->Status) &= 0xFEFF;
		}

		njSetTexture(&highwayObj_TEXLIST);
		njPushMatrix(0);
		njTranslateV(0, &v1->Position);
		njRotateZXY(&v1->Rotation);
		DrawObject((NJS_OBJECT*)obj->field_4C);

		if (obj->field_4C == SH_Escalator[0]->getmodel()) {
			DrawChunkModel(SH_Escalator[1]->getmodel()->getchunkmodel());
		}
		else {
			DrawChunkModel(SH_Escalator2[1]->getmodel()->getchunkmodel());
		}
		njPopMatrix(1u);
	}
}


void __cdecl OEscalator2(ObjectMaster* obj)
{
	obj->Data2.Undefined = SH_EscalatorCol[1]->getmodel();
	obj->field_4C = SH_Escalator2[0]->getmodel();
	obj->MainSub = MainSubGlobalDynCol;
	obj->DisplaySub = Escalator_Display;
}

void __cdecl OEscalator1(ObjectMaster* obj)
{
	obj->Data2.Undefined = SH_EscalatorCol[0]->getmodel();
	obj->field_4C = SH_Escalator[0]->getmodel();
	obj->MainSub = MainSubGlobalDynCol;
	obj->DisplaySub = Escalator_Display;
}


void FreeEscalators() {
	for (int i = 0; i < LengthOfArray(SH_Escalator); i++) {
		FreeMDL(SH_Escalator[i]);
		FreeMDL(SH_Escalator2[i]);
		FreeMDL(SH_EscalatorCol[i]);
	}
}

void LoadSH_EscalatorsModels() {
	SH_Escalator[0] = LoadMDL("SH-Escalator1", ModelFormat_Chunk);
	SH_Escalator[1] = LoadMDL("SH-Escalator2", ModelFormat_Chunk);
	SH_Escalator2[0] = LoadMDL("SH-Escalator3", ModelFormat_Chunk);
	SH_Escalator2[1] = LoadMDL("SH-Escalator4", ModelFormat_Chunk);


	SH_EscalatorCol[0] = LoadMDL("SH-EscalatorCol1", ModelFormat_Basic);
	SH_EscalatorCol[1] = LoadMDL("SH-EscalatorCol2", ModelFormat_Basic);
}