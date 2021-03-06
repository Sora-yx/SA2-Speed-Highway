#include "pch.h"

static ModelInfo* SH_Fountain[3];

extern NJS_TEXLIST highwayObj2_TEXLIST;
CollisionData ftnCol = { 0, (CollisionShapes)0, 0x77, 0, 0, {0.0, 30.0, 0.0}, 5.0, 0.0, 0.0, 0.0, 0, 0, 0 };


//They actually made 4 texlist with one tex lol.
static NJS_TEXNAME ftntexid0 = { (char*)"fountain01", 0, 0 };
static NJS_TEXNAME ftntexid1 = { (char*)"fountain02", 0, 0 };
static NJS_TEXNAME ftntexid2 = { (char*)"fountain03", 0, 0 };
static NJS_TEXNAME ftntexid3 = { (char*)"fountain04", 0, 0 };

static NJS_TEXLIST ftnTexList[4] = {
	&ftntexid0, 0,
	&ftntexid1, 0,
	&ftntexid2, 0,
	&ftntexid3, 0,
};


void Ftn_ExpandAndConstrict(EntityData1* a1)
{
	double v1; // st7

	a1->Scale.x = (double)rand() * 0.000030517578 * 0.02 - 0.0099999998 + a1->Scale.x;
	v1 = (double)rand() * 0.000030517578 * 0.02 - 0.0099999998 + a1->Scale.z;
	a1->Scale.z = v1;
	if (a1->Scale.x <= 1.01)
	{
		if (a1->Scale.x < 0.99000001)
		{
			a1->Scale.x = 0.99000001;
		}
	}
	else
	{
		a1->Scale.x = 1.01;
	}
	if (v1 <= 1.01)
	{
		if (v1 < 0.99000001)
		{
			a1->Scale.z = 0.99000001;
		}
	}
	else
	{
		a1->Scale.z = 1.01;
	}
}

void ExecFountain(EntityData1* data)
{
	__int16 getTimer; // ax
	double v2; // st7
	__int16 timer2; // ax
	double rng; // st7

	if ((unsigned int)data->NextAction > 3)
	{
		data->Scale.y = 1.0;
	}
	else
	{
		switch (data->NextAction)
		{
		case 0:
			getTimer = data->field_6;
			data->field_6 = getTimer + 1;
			if ((unsigned __int16)getTimer < 100u)
			{
				v2 = (double)rand() * 0.000030517578 * 0.0099999998 - 0.0049999999 + data->Scale.y;
				data->Scale.y = v2;
				if (v2 < 0.4)
				{
					data->Scale.y = 0.40000001;
				}
				else if (v2 > 0.5)
				{
					data->Scale.y = 0.5;
				}
			}
			else
			{
				data->field_6 = 0;
				data->NextAction = 1;
			}
			return;
		case 1:
			if (data->Scale.y <= 1.0)
			{
				data->Scale.y = data->Scale.y + 0.050000001;
			}
			else
			{
				data->NextAction = 2;
			}
			return;
		case 2:
			timer2 = data->field_6;
			data->field_6 = timer2 + 1;

			if ((unsigned __int16)timer2 >= 0x64u)
			{
				data->field_6 = 0;
				data->NextAction = 3;
				return;
			}

			rng = (double)rand() * 0.000030517578 * 0.0099999998 - 0.0049999999 + data->Scale.y;

			data->Scale.y = rng;

			if (data->Scale.y > 1.0)
			{
				data->Scale.y = 1.0;
			}
			if (rng < 0.89999998)
			{
				data->Scale.y = 0.89999998;
			}
			break;
		case 3:
			if (data->Scale.y >= 0.40000001)
			{
				data->Scale.y = data->Scale.y - 0.0099999998;
			}
			else
			{
				data->NextAction = 0;
			}
			return;
		default:
			data->Scale.y = 1.0;
			break;
		}
	}
}

void PushPlayer(ObjectMaster* a1)
{
	NJS_VECTOR* PosStock; // ebx
	EntityData1* Data; // esi
	EntityData1* Player; // edi
	double P1PosY; // st7

	PosStock = &a1->Data2.Entity->Velocity;
	Data = a1->Data1.Entity;
	Player = MainCharObj1[0];
	//QueueSound_DualEntity(106, a1, 1, 0, 30);
	EnemyBounceThing_Wrapper(0, PosStock->x, PosStock->y, PosStock->z);
	DoRotationStuff(0, 0, Data->Rotation.y + 0x8000, 0);
	P1PosY = Player->Position.y;
	Player->Position.x = Data->Position.x;
	Player->Position.z = Data->Position.z;
	if (P1PosY - Data->Position.y < 20.0)
	{
		Player->Position.y = Data->Position.y + 20.0;
	}
}

void Fount_CalcPushUP(ObjectMaster* a1)
{
	EntityData1* data = a1->Data1.Entity;

	njPushUnitMatrix();
	njRotateZXY(&data->Rotation);

	if (data->Scale.x != 0.0 || data->Scale.y != 0.0 || data->Scale.z != 0.0)
	{
		njTranslateEx(&data->Scale);
	}
	else
	{
		njTranslate(CURRENT_MATRIX, 0.0f, 6.0f, -6.0f);
	}
	
	njGetTranslation(CURRENT_MATRIX, &a1->Data2.Entity->Velocity);
	njPopMatrix(1u);
}

void Fountain_Delete(ObjectMaster* obj) {
	DeleteFunc_DynCol(obj);
	j_DeleteChildObjects(obj);
}

void Fountain_Display(ObjectMaster* obj) {

	Angle v3; // eax
	NJS_OBJECT* ftnOBJ = (NJS_OBJECT*)obj->field_4C;
	NJS_OBJECT* child; // esi
	float v5; // edi
	NJS_OBJECT* sibling; // esi
	float a3; // [esp+0h] [ebp-18h]
	NJS_TEXLIST* v8; // [esp+8h] [ebp-10h]
	float sy; // [esp+14h] [ebp-4h]
	float XScale; // [esp+1Ch] [ebp+4h]
	float XScalea; // [esp+1Ch] [ebp+4h]
	EntityData1* data = obj->Data1.Entity;

	njSetTexture(&ftnTexList[data->Index]);

	njPushMatrix(0);
	sy = 1.0 / data->Scale.y;
	XScale = data->Scale.y * 0.60000002 + 0.40000001;
	njTranslateV(0, &data->Position);
	v3 = data->Rotation.y;
	if (v3)
	{
		njRotateY(0, (unsigned __int16)v3);
	}
	njScaleV_(&data->Scale);
	a3 = VectorMaxAbs(&data->Scale);
	DrawChunkModel(ftnOBJ->getchunkmodel());

	njPushMatrix(0);

	njTranslate(0, ftnOBJ->pos[0], ftnOBJ->pos[1], ftnOBJ->pos[2]);
	v5 = XScale;
	njScale(0, XScale, sy, XScale);
	//XScalea = sub_49CC70(v5, sy, v5);
	DrawChunkModel(ftnOBJ->child->getchunkmodel());
	njPopMatrix(1u);
	njPushMatrix(0);
	sibling = ftnOBJ->child->sibling;
	njTranslate(0, sibling->pos[0], sibling->pos[1], sibling->pos[2]);
	njScale(0, v5, sy, v5);
	DrawChunkModel(sibling->getchunkmodel());
	njPopMatrix(1u);
	njPopMatrix(1u);

}

void Fountain_Main(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;
	Angle rotY; // eax
	double posX2; // st7
	double posZ2; // st6
	double posX; // st7
	double posZ; // st6
	char index = 0; // al
	float result2; // [esp+0h] [ebp-1Ch]
	float resultPos; // [esp+0h] [ebp-1Ch]
	float posY2; // [esp+14h] [ebp-8h]
	float posY; // [esp+14h] [ebp-8h]

	if (ClipObject(obj, 1020100.0))
	{
		return;
	}

	switch (data->Action) {

	case 1:
		posX = MainCharObj1[0]->Position.x - data->Position.x;
		posY = MainCharObj1[0]->Position.y - data->Position.y;
		posZ = MainCharObj1[0]->Position.z - data->Position.z;
		resultPos = posZ * posZ + posX * posX;
		if (sqrt(resultPos) <= 15.0 && posY > 0.0 && data->Scale.y * 100.0 >= posY)
		{
			PushPlayer(obj);
			data->Action = 2;
			data->field_6 = 0;
		}
		ExecFountain(data);
		Ftn_ExpandAndConstrict(data);

		AddToCollisionList(obj);
		break;
	case 2:
		posX2 = MainCharObj1[0]->Position.x - data->Position.x;
		posY2 = MainCharObj1[0]->Position.y - data->Position.y;
		posZ2 = MainCharObj1[0]->Position.z - data->Position.z;
		result2 = posZ2 * posZ2 + posX2 * posX2;

		if (sqrt(result2) > 15.0 || posY2 <= 0.0 || data->Scale.y * 100.0 < posY2)
		{
			data->Action = 1;
			data->field_6 = 0;
		}
		else
		{
			PushPlayer(obj);
			data->NextAction = 1;
		}
		ExecFountain(data);
		Ftn_ExpandAndConstrict(data);
		break;
	}

	if (TimeTotal % 4 == 0) { //4 frames by second
		index = data->Index + 1; //Index is used to change texlist so the fountain can be animated.
		data->Index = index;
	}

	if ((unsigned __int8)index > 3u)
	{
		data->Index = 0;
	}
}

void __cdecl DisplFtnChild2(ObjectMaster* a2)
{
	EntityData1* data; // esi
	Angle rotY; // eax
	float scale; // [esp+0h] [ebp-Ch]

	int index = a2->Parent->Data1.Entity->Index;

	data = a2->Data1.Entity;
		
	//njSetTexture((NJS_TEXLIST*)(8 * (unsigned __int8)a2->Parent->Data1.Entity->Index + 40579296));
	njSetTexture(&ftnTexList[index]);
	njPushMatrix(0);
	njTranslateV(0, &data->Position);
	rotY = data->Rotation.y;
	if (rotY)
	{
		njRotateY(0, (unsigned __int16)rotY);
	}
	DrawObject((NJS_OBJECT*)a2->field_4C);
	njPopMatrix(1u);
}

void Ftn_ApplyRotScale(EntityData1* data, double scaleY, Angle rotY, bool isPositive) {

	rotY = data->Rotation.y;

	if (isPositive)
		data->Scale.y = scaleY + 0.0020000001;
	else
		data->Scale.y = scaleY - 0.0020000001;

	data->Rotation.y = rotY += 32;
	Ftn_ExpandAndConstrict(data);
}

void __cdecl FountainChild2(ObjectMaster* a1)
{
	EntityData1* data; // esi
	double scaleY = 0.0; // st7
	Angle rotY = 0; // eax

	data = a1->Data1.Entity;

	switch (data->Action) {

	case 0:
		a1->field_4C = SH_Fountain[1]->getmodel();
		a1->DisplaySub = DisplFtnChild2;;
		a1->DeleteSub = j_DeleteChildObjects;
		data->Scale.z = 1.0;
		data->Scale.x = 1.0;
		data->Scale.y = 0.75;
		data->Action = 1;
		break;
	case 1:
		if (data->Scale.y < 0.85000002)
		{
			Ftn_ApplyRotScale(data, scaleY, rotY, true);
			return;
		}

		data->Action = 2;
		break;
	case 2:
		if (data->Scale.y > 0.64999998)
		{
			Ftn_ApplyRotScale(data, scaleY, rotY, false);
			return;
		}
		data->Action = 1;
		break;
	default:
		Fountain_Delete(a1);
		return;
	}
}

void __cdecl FountainChild_Display(ObjectMaster* a2)
{
	EntityData1* data = a2->Data1.Entity;
	unsigned int index = a2->Parent->Data1.Entity->Index;

	njSetTexture(&ftnTexList[index]);
	njPushMatrix(0);
	njTranslateV(0, &data->Position);
	njScaleV_(&data->Scale);
	DrawObject((NJS_OBJECT*)a2->field_4C);
	njPopMatrix(1u);
}

void FountainChild(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;

	if (data->Action == 0) {
		obj->field_4C = SH_Fountain[0]->getmodel();
		obj->DeleteSub = Fountain_Delete;
		obj->DisplaySub = FountainChild_Display;
		data->Scale.z = 1.0;
		data->Scale.y = 1.0;
		data->Scale.x = 1.0;
		data->Action = 1;
	}
	else if (data->Action == 1) {
		Ftn_ExpandAndConstrict(data);
	}
}


ObjectThing ftnStruct[2] = {
	{ FountainChild2, LoadObj_Data1, 1, {0}, {0}, nullptr },
	{ FountainChild2, LoadObj_Data1, 2, {0, 0x8000, 0}, {0}, nullptr}
};


void LoadFountain(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;

	if (!ClipObject(obj, 1020100.0))
	{
		obj->field_4C = SH_Fountain[2]->getmodel();
		Fount_CalcPushUP(obj);
		data->Scale.z = 1.0;
		data->Scale.y = 1.0;
		data->Scale.x = 0.40000001;
		InitCollision(obj, &ftnCol, 1, 4u);
		data->Collision->Range = 5.0;
		data->Collision->Flag |= 0x40u;
		obj->DeleteSub = Fountain_Delete;
		obj->DisplaySub = Fountain_Display;
		Load_MultipleChildObjects(ftnStruct, obj, LengthOfArray(ftnStruct));
		//LoadChildObject(LoadObj_Data1, (void(__cdecl*)(ObjectMaster*))FountainChild2, obj);
		LoadChildObject(LoadObj_Data1, (void(__cdecl*)(ObjectMaster*))FountainChild, obj);
		data->Action = 1;
		obj->MainSub = Fountain_Main;
	}
}

void DeleteFountainModel() {

	for (int i = 0; i < LengthOfArray(SH_Fountain); i++) {
		FreeMDL(SH_Fountain[i]);
	}

	return;
}

void LoadFountainModel() {
	for (size_t i = 0; i < LengthOfArray(SH_Fountain); i++) {
		std::string str = "sh-Fount" + std::to_string(i);
		SH_Fountain[i] = LoadMDL(str.c_str(), ModelFormat_Chunk);
	}

	ftnTexList[0].textures[0] = highwayObj2_TEXLIST.textures[25];
	ftnTexList[1].textures[0] = highwayObj2_TEXLIST.textures[26];
	ftnTexList[2].textures[0] = highwayObj2_TEXLIST.textures[27];
	ftnTexList[3].textures[0] = highwayObj2_TEXLIST.textures[28];

	return;
}