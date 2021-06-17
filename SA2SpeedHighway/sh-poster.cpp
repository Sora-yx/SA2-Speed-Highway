#include "pch.h"

static ModelInfo* SH_Poster[3];
static ModelInfo* SH_Post[2];

void __cdecl OPoster2(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	if (data->Action == 0) {
		obj->field_4C = SH_Poster[2]->getmodel();
		obj->DisplaySub = GenericSHDisplayZXY;
		data->Action = 1;
	}
}

void __cdecl OPoster1(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	if (data->Action == 0) {
		obj->field_4C = SH_Poster[1]->getmodel();
		obj->DisplaySub = GenericSHDisplayZXY;
		data->Action = 1;
	}
}

void __cdecl OPoster0(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	if (data->Action == 0) {
		obj->field_4C = SH_Poster[0]->getmodel();
		obj->DisplaySub = GenericSHDisplayZXY;
		data->Action = 1;
	}
}

void __cdecl OPost4(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	if (data->Action == 0) {
		obj->field_4C = SH_Post[1]->getmodel();
		obj->DisplaySub = GenericSHDisplayZXY;
		data->Action = 1;
	}
}

void __cdecl OPost1(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	if (data->Action == 0) {
		obj->field_4C = SH_Post[0]->getmodel();
		obj->DisplaySub = GenericSHDisplayZXY;
		data->Action = 1;
	}
}

void FreePosterModels() {
	for (size_t i = 0; i < LengthOfArray(SH_Poster); i++) {
		FreeMDL(SH_Poster[i]);
	}

	FreeMDL(SH_Post[0]);
	FreeMDL(SH_Post[1]);
	return;
}

void LoadPosterModels() {
	for (size_t i = 0; i < LengthOfArray(SH_Poster); i++) {
		std::string str = "sh-Poster" + std::to_string(i);
		SH_Poster[i] = LoadMDL(str.c_str(), ModelFormat_Chunk);
	}

	SH_Post[0] = LoadMDL("SH-Post", ModelFormat_Chunk);
	SH_Post[1] = LoadMDL("SH-Post2", ModelFormat_Chunk);
	return;
}