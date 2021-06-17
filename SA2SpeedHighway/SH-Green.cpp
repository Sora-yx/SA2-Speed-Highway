#include "pch.h"

static ModelInfo* SH_Green[5];

CollisionData GreenACol = { 0, CollisionShape_Sphere, 0x77, 0, 0, {0.0, 4.0, 0.0} , 4.0, 0.0, 0.0, 0.0, 0, 0, 0 };
CollisionData GreenBCol = { 0, CollisionShape_Sphere, 0x77, 0, 0, {0.0, 4.0, 0.0}, 4.0, 0.0, 0.0, 0.0, 0, 0, 0 };
CollisionData GreenDCol = { 0, CollisionShape_Sphere, 0x77, 0, 0, {0.0, 4.0, 0.0}, 4.0, 0.0, 0.0, 0.0, 0, 0, 0 };

void __cdecl OGreene(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	if (data->Action == 0) {
		obj->field_4C = SH_Green[4]->getmodel();
		obj->DisplaySub = GenericSHDisplayZXY;
		data->Action = 1;
	}
}

void __cdecl OGreend(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	if (data->Action == 0) {
		obj->field_4C = SH_Green[3]->getmodel();
		obj->DisplaySub = GenericSHDisplayZXY;
		InitCollision(obj, &GreenDCol, 1, 4u);
		data->Collision->Range = 8.0f;
		data->Action = 1;
		obj->MainSub = MainSubGlobalCol;
	}
}

void __cdecl OGreenb(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	if (data->Action == 0) {
		obj->field_4C = SH_Green[2]->getmodel();
		obj->DisplaySub = GenericSHDisplayZXY;
		InitCollision(obj, &GreenBCol, 1, 4u);
		data->Collision->Range = 8.0f;
		data->Action = 1;
		obj->MainSub = MainSubGlobalCol;
	}
}

void __cdecl OGreena(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	if (data->Action == 0) {
		obj->field_4C = SH_Green[1]->getmodel();
		obj->DisplaySub = GenericSHDisplayZXY;
		InitCollision(obj, &GreenACol, 1, 4u);
		data->Collision->Range = 8.0f;
		data->Action = 1;
		obj->MainSub = MainSubGlobalCol;
	}
}

void __cdecl OGreen(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	if (data->Action == 0) {
		obj->field_4C = SH_Green[0]->getmodel();
		obj->DisplaySub = GenericSHDisplayZXY;
		data->Action = 1;
	}
}


//same function but call the global calc rot thing
void __cdecl OGgrend(ObjectMaster* obj)
{
	EntityData1* data; // ecx

	data = obj->Data1.Entity;
	obj->field_4C = OGreend;
	//data->LoopData.SInteger = 2;
	obj->DeleteSub = j_DeleteChildObjects;
	obj->MainSub = SH_GlobalMainWithCalcRot;
}

void __cdecl OGgrenb(ObjectMaster* obj)
{
	EntityData1* data; // ecx

	data = obj->Data1.Entity;
	obj->field_4C = OGreenb;
	//data->LoopData.SInteger = 2;
	obj->DeleteSub = j_DeleteChildObjects;
	obj->MainSub = SH_GlobalMainWithCalcRot;
}


void __cdecl OGgrena(ObjectMaster* obj)
{
	EntityData1* data; // ecx

	data = obj->Data1.Entity;
	obj->field_4C = OGreena;
	//data->LoopData.SInteger = 2;
	obj->DeleteSub = j_DeleteChildObjects;
	obj->MainSub = SH_GlobalMainWithCalcRot;
}

void FreeGreenModels() {
	for (size_t i = 0; i < LengthOfArray(SH_Green); i++) {
		FreeMDL(SH_Green[i]);
	}
}

void LoadGreenModels() {
	for (size_t i = 0; i < LengthOfArray(SH_Green); i++) {
		std::string str = "sh-Green" + std::to_string(i);
		SH_Green[i] = LoadMDL(str.c_str(), ModelFormat_Chunk);
	}
}