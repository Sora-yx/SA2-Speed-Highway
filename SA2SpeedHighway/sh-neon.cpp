#include "pch.h"

static ModelInfo* SH_Neon[4];


void SH_GenericNeonDisplay(ObjectMaster* a2)
{
	EntityData1* data; // esi
	__int16 timer; // cx
	NJS_MODEL_SADX* v4; // eax
	bool v5; // cc
	int v6; // ecx
	Angle v7; // eax

	data = a2->Data1.Entity;
	timer = data->field_6;

	if (data->field_6 > 0xF0u)
	{
		data->field_6 = 0;
	}

	//njSetTexture((NJS_TEXLIST*)data->LoopData.Pointer);
	njPushMatrix(0);
	njTranslateV(0, &data->Position);
	v7 = data->Rotation.y;
	if (v7)
	{
		njRotateY(0, (unsigned __int16)v7);
	}

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

		obj->DisplaySub = (ObjectFuncPtr)SH_GenericNeonDisplay;
		obj->MainSub = (ObjectFuncPtr)SH_GenericNeon;
		obj->field_4C = SH_Neon[0]->getmodel();

		v1->Index = 0;
	}
}

void __cdecl ONeon2(ObjectMaster* obj)
{
	EntityData1* v1; // edi

	v1 = obj->Data1.Entity;
	if (!ClipSetObject(obj))
	{

		obj->DisplaySub = (ObjectFuncPtr)SH_GenericNeonDisplay;
		obj->MainSub = (ObjectFuncPtr)SH_GenericNeon;

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

		obj->DisplaySub = (ObjectFuncPtr)SH_GenericNeonDisplay;
		obj->MainSub = (ObjectFuncPtr)SH_GenericNeon;
		obj->field_4C = SH_Neon[2]->getmodel();

		v1->Index = 2;
	}
}

void __cdecl ONeon4(ObjectMaster* obj)
{

	EntityData1* data = obj->Data1.Entity;
	if (!ClipSetObject(obj))
	{
		obj->DisplaySub = (ObjectFuncPtr)SH_GenericNeonDisplay;
		obj->MainSub = (ObjectFuncPtr)SH_GenericNeon;
		obj->field_4C = SH_Neon[3]->getmodel();

		data->Index = 3;
	}
}