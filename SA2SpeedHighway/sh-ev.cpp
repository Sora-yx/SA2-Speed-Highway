#include "pch.h"

static ModelInfo* sh_ev;
static ModelInfo* sh_evCol;

static ModelInfo* sh_evPlat;
static ModelInfo* sh_evPlatCol;

extern NJS_TEXLIST highwayObj_TEXLIST;

NJS_OBJECT* shevChild;

ObjectThing stru_EVPlatform[6] = {
	{ SH_EVChild, LoadObj_Data1 | LoadObj_UnknownA, 3, {0}, {60.0, -110.0, 0.0}, nullptr},
	{ SH_EVChild, LoadObj_Data1 | LoadObj_UnknownA, 0, {0}, {70.0, 0.0, 0.0}, nullptr},
	{ SH_EVChild, LoadObj_Data1 | LoadObj_UnknownA, 1, {0}, {60.0, 110.0, 0.0}, nullptr},
	{ SH_EVChild, LoadObj_Data1 | LoadObj_UnknownA, 1, {0}, {-60.0, 110.0, 0.0}, nullptr},
	{ SH_EVChild, LoadObj_Data1 | LoadObj_UnknownA, 2, {0}, {-70.0, 0.0, 0.0}, nullptr},
	{ SH_EVChild, LoadObj_Data1 | LoadObj_UnknownA, 3, {0}, {-60.0, -110.0, 0.0}, nullptr},
};

bool SHEv_isPlayerOnPlatform(ObjectMaster* a1)
{
	EntityData1* v3; // r30

	NJS_VECTOR a2;
	NJS_VECTOR a3; // [sp+60h] [-30h] BYREF

	v3 = a1->Data1.Entity;
	a2.x = MainCharObj1[0]->Position.x - v3->Position.x;
	a2.y = MainCharObj1[0]->Position.y - v3->Position.y;
	a2.z = MainCharObj1[0]->Position.z - v3->Position.z;

	njPushUnitMatrix();

	if (v3->Rotation.y != 0x10000)
		njRotateY(0, (unsigned __int16)-HIWORD(v3->Rotation.y));

	njTranslate(CURRENT_MATRIX, a2.x, a2.y, a2.z);
	njGetTranslation(CURRENT_MATRIX, &a2);
	//njCalcPoint(&a2, &a3, CURRENT_MATRIX);
	njPopMatrix(1u);

	return (MainCharObj1[0]->Status & 1) != 0 && fabs(a2.x) < 43.0 && fabs(a2.y) < 10.0 && fabs(a2.z) < 43.0;
}


void EV_UpdatePlayerPos(ObjectMaster* obj, float x, float y, float z) {
	if (SHEv_isPlayerOnPlatform(obj))
	{
		MainCharObj1[0]->Position.x += x;
		MainCharObj1[0]->Position.y += y;
		MainCharObj1[0]->Position.z += z;
	}
}


void OEv_SetFlag(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* item = (NJS_OBJECT*)obj->field_4C;

	if (!item)
		return;

	item->pos[0] = data->Position.x;
	item->pos[1] = data->Position.y;
	item->pos[2] = data->Position.z;

	if (IsPlayerInsideSphere(&data->Position, 170.0f))
	{
		data->Status |= 0x100u;
	}
	else
	{
		data->Status &= 0xFEFFu;
	}
}

void __cdecl OEv_ChildDisplay(ObjectMaster* a1)
{
	EntityData1* data; // esi
	NJS_OBJECT* getChildObj; // edi
	NJS_OBJECT* child; // ebx
	Angle rotY; // eax
	unsigned __int16 timer; // ax
	unsigned __int16 timer2; // si
	NJS_OBJECT* sibling; // ebx

	data = a1->Data1.Entity;
	getChildObj = (NJS_OBJECT*)a1->field_4C;
	child = getChildObj->child;
	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrix(0);
	njTranslateV(0, &data->Position);
	rotY = data->Rotation.y;
	if (rotY)
	{
		njRotateY(0, (unsigned __int16)rotY);
	}
	DrawChunkModel(getChildObj->getchunkmodel());
	njPushMatrix(0);
	timer = data->field_6;
	if (timer)
	{
		njRotateZ(0, timer);
	}
	DrawChunkModel(child->getchunkmodel());
	njPopMatrix(1u);
	njPushMatrix(0);
	timer2 = data->field_6;
	sibling = child->sibling;
	if (timer2)
	{
		njRotateZ(0, timer2);
	}
	DrawChunkModel(sibling->getchunkmodel());
	njPopMatrix(2u);
}

void __cdecl SH_EVChild(ObjectMaster* a2)
{
	EntityData1* data; // ebp
	ObjUnknownA* unkA; // esi
	EntityData1* dataParent; // edi
	double v4; // st7
	double v5; // st7
	double v6; // st7
	double v7; // st7
	double v8; // st7
	double v9; // st7
	double v10; // st7
	double v11; // st7
	double v12; // st7
	double v13; // st7
	double v14; // st7
	double v15; // st7
	NJS_OBJECT* v16; // eax
	int* v17; // ecx
	Angle v18; // ecx
	char v19; // al
	char v20; // cl
	float v21; // [esp+0h] [ebp-24h]
	float v22; // [esp+0h] [ebp-24h]
	float v23; // [esp+0h] [ebp-24h]
	float v24; // [esp+0h] [ebp-24h]
	float v25; // [esp+18h] [ebp-Ch]
	float v26; // [esp+18h] [ebp-Ch]
	float v27; // [esp+18h] [ebp-Ch]
	float v28; // [esp+18h] [ebp-Ch]

	data = a2->Data1.Entity;
	unkA = a2->UnknownA_ptr;
	dataParent = a2->Parent->Data1.Entity;
	if (data->Action)
	{
		NJS_OBJECT* dyncol = (NJS_OBJECT*)a2->EntityData2;
		*(NJS_VECTOR*)dyncol->pos = data->Position;
		EV_UpdatePlayerPos(a2, unkA->field_24, unkA->field_28, unkA->field_2C);

		if (data->Action == 1)
		{
			switch (data->NextAction)
			{
			case 0:
				unkA->field_24 = 0;
				unkA->field_28 = 0.69999999;
				unkA->field_2C = 0;
				v10 = data->Position.y + 0.69999999;
				data->Position.y = v10;
				if (v10 - dataParent->Position.y >= 110.0)
				{
					data->NextAction = 1;
				}
				break;
			case 1:
				v11 = njCos(-data->Rotation.y);
				unkA->field_28 = 0.0;
				*(float*)&unkA->field_24 = -(v11 * 0.69999999);
				*(float*)&unkA->field_2C = -(njSin(-data->Rotation.y) * 0.69999999);
				data->Position.x = data->Position.x + *(float*)&unkA->field_24;
				v12 = data->Position.z + *(float*)&unkA->field_2C;
				data->Position.z = v12;
				v27 = data->Position.x - dataParent->Position.x;
				v23 = pow(v12 - dataParent->Position.z, 2.0) + pow(v27, 2.0);
				if (sqrt(v23) >= 70.0)
				{
					data->NextAction = 2;
				}
				break;
			case 2:
				unkA->field_24 = 0;
				unkA->field_28 = -0.69999999;
				unkA->field_2C = 0;
				v13 = data->Position.y - 0.69999999;
				data->Position.y = v13;
				//EV_UpdatePlayerPos(a2, 0, unkA->field_28, 0);
				if (v13 - dataParent->Position.y <= -110.0)
				{
					data->NextAction = 3;
				}
				break;
			case 3:
				v14 = njCos(-data->Rotation.y);
				unkA->field_28 = 0.0;
				*(float*)&unkA->field_24 = v14 * 0.69999999;
				*(float*)&unkA->field_2C = njSin(-data->Rotation.y) * 0.69999999;
				data->Position.x = data->Position.x + *(float*)&unkA->field_24;
				v15 = data->Position.z + *(float*)&unkA->field_2C;
				data->Position.z = v15;
				//	EV_UpdatePlayerPos(a2, 0, 0, *(float*)&unkA->field_2C);
				v28 = data->Position.x - dataParent->Position.x;
				v24 = pow(v15 - dataParent->Position.z, 2.0) + pow(v28, 2.0);
				if (sqrt(v24) >= 70.0)
				{
					data->NextAction = 0;
				}
				break;
			default:
				data->Action = 3;
				break;
			}
			data->field_6 += 256;
			OEv_SetFlag(a2);

		}
		else if (data->Action == 2)
		{
			switch (data->NextAction)
			{
			case 0:
				unkA->field_24 = 0;
				unkA->field_28 = -0.69999999;
				unkA->field_2C = 0;
				v4 = data->Position.y - 0.69999999;
				data->Position.y = v4;
				//EV_UpdatePlayerPos(a2, 0, unkA->field_28, 0);
				if (v4 - dataParent->Position.y <= -110.0)
				{
					data->NextAction = 3;
				}
				break;
			case 1:
				v8 = njCos(-data->Rotation.y);
				unkA->field_28 = 0.0;
				*(float*)&unkA->field_24 = v8 * 0.69999999;
				*(float*)&unkA->field_2C = njSin(-data->Rotation.y) * 0.69999999;
				data->Position.x = data->Position.x + *(float*)&unkA->field_24;
				v9 = data->Position.z + *(float*)&unkA->field_2C;
				data->Position.z = v9;
				//EV_UpdatePlayerPos(a2, 0, 0, *(float*)&unkA->field_2C);
				v26 = data->Position.x - dataParent->Position.x;
				v22 = pow(v9 - dataParent->Position.z, 2.0) + pow(v26, 2.0);
				if (sqrt(v22) >= 70.0)
				{
					data->NextAction = 0;
				}
				break;
			case 2:
				unkA->field_24 = 0;
				unkA->field_28 = 0.69999999;
				unkA->field_2C = 0;
				v7 = data->Position.y + 0.69999999;
				data->Position.y = v7;
				//EV_UpdatePlayerPos(a2, 0, unkA->field_28, 0);
				if (v7 - dataParent->Position.y >= 110.0)
				{
					data->NextAction = 1;
				}
				break;
			case 3:
				v5 = njCos(-data->Rotation.y);
				unkA->field_28 = 0.0;
				*(float*)&unkA->field_24 = -(v5 * 0.69999999);
				*(float*)&unkA->field_2C = -(njSin(-data->Rotation.y) * 0.69999999);
				data->Position.x = data->Position.x + *(float*)&unkA->field_24;
				v6 = data->Position.z + *(float*)&unkA->field_2C;
				data->Position.z = v6;
				//EV_UpdatePlayerPos(a2, 0, 0, unkA->field_2C);
				v25 = data->Position.x - dataParent->Position.x;
				v21 = pow(v6 - dataParent->Position.z, 2.0) + pow(v25, 2.0);
				if (sqrt(v21) >= 70.0)
				{
					data->NextAction = 2;
				}
				break;
			default:
				data->Action = 3;
				break;
			}
			data->field_6 -= 256;
			OEv_SetFlag(a2);

		}
	}
	else
	{
		a2->field_4C = sh_evPlat->getmodel();

		a2->DeleteSub = DeleteFunc_DynCol;
		a2->DisplaySub = OEv_ChildDisplay;
		DynCol_AddFromObject(a2, sh_evPlatCol->getmodel(), &data->Position, data->Rotation.y, SurfaceFlag_Solid | SurfaceFlag_Dynamic);
		if (dataParent->Scale.x < 0.0)
		{
			v20 = data->Status;
			data->Action = 2;
			data->NextAction = v20;
		}
		else
		{
			v19 = data->Status;
			data->Action = 1;
			data->NextAction = v19;
		}
		unkA->field_24 = 0;
		unkA->field_28 = 0.0;
		unkA->field_2C = 0;
		unkA->field_4 = 0;
		unkA->field_8 = 0;
		unkA->field_C = 0;
	}
}



void __cdecl OEv(ObjectMaster* obj)
{
	EntityData1* data; // esi
	Angle v2; // eax
	int* v4; // ecx
	Vector3 a2; // [esp+8h] [ebp-30h] BYREF
	NJS_VECTOR a3;


	data = obj->Data1.Entity;
	if (!ClipObject(obj, 1020100.0))
	{

		if (data->Action)
		{
			if (data->Action == 1)
			{
				// QueueSound_XYZ(102, data, 1, 0, 30, data->Position.x, data->Position.y, data->Position.z);
				OEv_SetFlag(obj);
			}
		}
		else {

			obj->field_4C = sh_ev->getmodel();
			// data->timer = (int*)&object_0267315C;
			obj->DeleteSub = DeleteFunc_DynCol;
			obj->DisplaySub = GenericSHDisplay_RotY;
			DynCol_AddFromObject(obj, sh_evCol->getmodel(), &data->Position, data->Rotation.y, SurfaceFlag_Solid | SurfaceFlag_Dynamic);
			data->Action = 1;
			shevChild = sh_evPlat->getmodel();

			Load_MultipleChildObjects(stru_EVPlatform, obj, LengthOfArray(stru_EVPlatform));
		}
	}

}

void LoadModel_Oev() {
	sh_ev = LoadMDL("sh-ev", ModelFormat_Chunk);
	sh_evPlat = LoadMDL("sh-evplat", ModelFormat_Chunk);

	sh_evCol = LoadMDL("sh-evCol", ModelFormat_Basic);
	sh_evPlatCol = LoadMDL("sh-evplatCol", ModelFormat_Basic);
}

void Init_OEv() {

}