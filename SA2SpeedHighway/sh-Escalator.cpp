#include "pch.h"
#include "objects.h"

static ModelInfo* SH_Escalator[2];
static ModelInfo* SH_Escalator2[2];
static ModelInfo* SH_EscalatorCol[2];


void Escalator_Display(ObjectMaster* obj) {

	EntityData1* v1 = obj->Data1.Entity;

	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrix(0);
	njTranslateV(0, &v1->Position);
	njRotateZXY(&v1->Rotation);
	DrawObject((NJS_OBJECT*)obj->field_4C);
	njPopMatrix(1u);
}

void Escalator_Main(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;

	if (data->Action == 0) {

		if (obj->Data2.Undefined == nullptr)
			return;

		obj->DeleteSub = DeleteFunc_DynCol;
		DynCol_AddFromObject(obj, (NJS_OBJECT*)obj->Data2.Undefined, &data->Position, data->Rotation.y, SurfaceFlag_Solid);
		data->Action = 1;
	}
	else {
		if (IsPlayerInsideSphere(&data->Position, 100))
		{
			(data->Status) |= 100u;
		}
		else
		{
			(data->Status) &= 0xFEFF;
		}
	}
}

void EscalatorChild(ObjectMaster* obj) {
	EntityData1* data1 = obj->Data1.Entity;

	if (data1->Action == 0) {
		obj->DisplaySub = Escalator_Display;
		data1->Action = 1;
	}
}
void __cdecl OEscalator2(ObjectMaster* obj)
{
	obj->Data2.Undefined = SH_EscalatorCol[1]->getmodel();
	obj->field_4C = SH_Escalator2[0]->getmodel();
	obj->MainSub = Escalator_Main;
	obj->DisplaySub = Escalator_Display;

	ObjectMaster* child = LoadChildObject((LoadObj)6, EscalatorChild, obj);
	child->field_4C = SH_Escalator2[1]->getmodel();
}

void __cdecl OEscalator1(ObjectMaster* obj)
{
	obj->Data2.Undefined = SH_EscalatorCol[0]->getmodel();
	obj->field_4C = SH_Escalator[0]->getmodel();
	obj->MainSub = Escalator_Main;
	obj->DisplaySub = Escalator_Display;

	ObjectMaster* child = LoadChildObject((LoadObj)6, EscalatorChild, obj);
	child->field_4C = SH_Escalator[1]->getmodel();
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