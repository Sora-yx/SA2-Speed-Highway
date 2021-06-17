#include "pch.h"

static ModelInfo* SH_Neon[4];

static NJS_TEXNAME neonTexName[] = {
	{ (char*)"light2", 0, 0 },
};

static NJS_TEXNAME neonTexName2[] = {
	{ (char*)"aNeon03", 0, 0 },
	{ (char*)"aNeon10", 0, 0 },
	{ (char*)"aNeon04", 0, 0 },
	{ (char*)"aNeon06", 0, 0 },
	{ (char*)"aFentx05", 0, 0 }
};

static NJS_TEXNAME neonTexName3[] = {
	{ (char*)"aFentx07", 0, 0 },
	{ (char*)"aNeon02", 0, 0 },
	{ (char*)"aNeon08", 0, 0 },
	{ (char*)"aNeon01", 0, 0 },
	{ (char*)"aNeon07", 0, 0 },
	{ (char*)"aNeon02", 0, 0 },
};

static NJS_TEXNAME neonTexName4[] = {
	{ (char*)"aNeon05", 0, 0 },
	{ (char*)"aNeon07", 0, 0 },
	{ (char*)"aS_w18", 0, 0 },
	{ (char*)"aNeon04", 0, 0 },
	{ (char*)"aNeon09", 0, 0 },
};

static NJS_TEXLIST neonTexlist = { arrayptrandlength(neonTexName, Uint32) };
static NJS_TEXLIST neonTexlist2 = { arrayptrandlength(neonTexName2, Uint32) };
static NJS_TEXLIST neonTexlist3 = { arrayptrandlength(neonTexName3, Uint32) };
static NJS_TEXLIST neonTexlist4 = { arrayptrandlength(neonTexName4, Uint32) };

void Load_NeonAssets() {

	for (size_t i = 0; i < LengthOfArray(SH_Neon); i++) {
		std::string str = "sh-neon" + std::to_string(i);
		SH_Neon[i] = LoadMDL(str.c_str(), ModelFormat_Chunk);
	}

	neonTexlist.textures[0] = highwayObj2_TEXLIST.textures[7];

	neonTexlist2.textures[0] = highwayObj2_TEXLIST.textures[8];
	neonTexlist2.textures[1] = highwayObj2_TEXLIST.textures[9];
	neonTexlist2.textures[2] = highwayObj2_TEXLIST.textures[10];
	neonTexlist2.textures[3] = highwayObj2_TEXLIST.textures[11];
	neonTexlist2.textures[4] = highwayObj2_TEXLIST.textures[12];


	neonTexlist3.textures[0] = highwayObj2_TEXLIST.textures[13];
	neonTexlist3.textures[1] = highwayObj2_TEXLIST.textures[14];
	neonTexlist3.textures[2] = highwayObj2_TEXLIST.textures[15];
	neonTexlist3.textures[3] = highwayObj2_TEXLIST.textures[16];
	neonTexlist3.textures[4] = highwayObj2_TEXLIST.textures[17];
	neonTexlist3.textures[5] = highwayObj2_TEXLIST.textures[18];

	neonTexlist4.textures[0] = highwayObj2_TEXLIST.textures[19];
	neonTexlist4.textures[1] = highwayObj2_TEXLIST.textures[20];
	neonTexlist4.textures[2] = highwayObj2_TEXLIST.textures[21];
	neonTexlist4.textures[3] = highwayObj2_TEXLIST.textures[22];
	neonTexlist4.textures[4] = highwayObj2_TEXLIST.textures[23];

	return;
}

void Free_Neon() {

	for (size_t i = 0; i < LengthOfArray(SH_Neon); i++) {
		FreeMDL(SH_Neon[i]);
	}

	return;
}

void SH_GenericNeonDisplay(ObjectMaster* a2)
{
	EntityData1* data; // esi
	__int16 timer; // cx
	bool v5; // cc
	int v6; // ecx

	data = a2->Data1.Entity;
	timer = data->field_6;

	if (data->field_6 > 240)
	{
		data->field_6 = 0;
	}

	njSetTexture(&highwayObj2_TEXLIST);
	njPushMatrix(0);
	njTranslateV(0, &data->Position);
	njRotateY(0, data->Rotation.y);
	DrawObject((NJS_OBJECT*)a2->field_4C);
	njPopMatrix(1u);
}

void SH_GenericNeon(ObjectMaster* a1)
{
	if (!ClipSetObject(a1))
	{
		++a1->Data1.Entity->field_6;
	}
}


void __cdecl ONeon1(ObjectMaster* obj)
{
	EntityData1* v1; // edi

	v1 = obj->Data1.Entity;
	if (!ClipSetObject(obj))
	{
		obj->DisplaySub = SH_GenericNeonDisplay;
		obj->MainSub = SH_GenericNeon;
		obj->field_4C = SH_Neon[0]->getmodel();
		//obj->Data2.Undefined = &highwayObj2_TEXLIST;
		v1->Index = 0;
	}
}

void __cdecl ONeon2(ObjectMaster* obj)
{
	EntityData1* v1; // edi

	v1 = obj->Data1.Entity;
	if (!ClipSetObject(obj))
	{

		obj->DisplaySub = SH_GenericNeonDisplay;
		obj->MainSub = SH_GenericNeon;
		//obj->Data2.Undefined = &neonTexlist2;
		obj->field_4C = SH_Neon[1]->getmodel();
		v1->Index = 1;
	}
}

void __cdecl ONeon3(ObjectMaster* obj)
{
	EntityData1* v1; // edi

	v1 = obj->Data1.Entity;
	if (!ClipSetObject(obj))
	{

		obj->DisplaySub = SH_GenericNeonDisplay;
		obj->MainSub = SH_GenericNeon;
		//obj->Data2.Undefined = &neonTexlist3;
		obj->field_4C = SH_Neon[2]->getmodel();

		v1->Index = 2;
	}
}

void __cdecl ONeon4(ObjectMaster* obj)
{

	EntityData1* data = obj->Data1.Entity;
	if (!ClipSetObject(obj))
	{
		obj->DisplaySub = SH_GenericNeonDisplay;
		obj->MainSub = SH_GenericNeon;
		//obj->Data2.Undefined = &neonTexlist4;
		obj->field_4C = SH_Neon[3]->getmodel();

		data->Index = 3;
	}
}