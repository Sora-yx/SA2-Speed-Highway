#include "pch.h"

static NJS_TEXNAME highwayObj_Tex[118]{};
NJS_TEXLIST highwayObj_TEXLIST = { arrayptrandlength(highwayObj_Tex, Uint32) };

static NJS_TEXNAME highwayObj2_Tex[54]{};
NJS_TEXLIST highwayObj2_TEXLIST = { arrayptrandlength(highwayObj2_Tex, Uint32) };

/*NJS_TEXNAME light2 = { "light2", 0, 0 };
NJS_TEXNAME aNen01 = { "nen_01", 0, 0 };
NJS_TEXNAME aRefCrome_5 = { "ref_crome", 0, 0 };
NJS_TEXNAME aStSLight06_2 = { "st_slight06", 0, 0 };*/



NJS_TEXNAME cone04[5] = { (char*)"cone04", 0, 0, (char*)"light2", 0, 0, (char*)"nen_01", 0, 0, (char*)"ref_crome", 0, 0, (char*)"st_slight06", 0, 0 };

NJS_TEXLIST JammerTexlist = { arrayptrandlength(cone04, Uint32) };
NJS_TEXLIST JammerTexlist2 = { arrayptrandlength(cone04, Uint32) };

/*NJS_TEXLIST JammerTexlist[5] = {
	{ &cone04, 0 },
	{ &light2, 0 },
	{ &aNen01, 0},
	{ &aRefCrome_5, 0},
	{ &aStSLight06_2, 0},
};

NJS_TEXLIST JammerTexlist2[5] = {
	{ &cone04, 0 },
	{ &light2, 0 },
	{ &aNen01, 0},
	{ &aRefCrome_5, 0},
	{ &aStSLight06_2, 0},
};*/

static ModelInfo* SH_Cone[2];
static ModelInfo* SH_Lamp[2];

static ModelInfo* SH_Bell[2];

static ModelInfo* SH_Jammer;

static ModelInfo* SH_SLight;
static ModelInfo* SH_GFF;

CollisionData Col_Cone = { 0x300, (CollisionShapes)0x6, 0x20, 0xE0, 0, { 0, 2.0, 0 }, 3.0, 1.5, 0.0, 0, 0, 0, 0 };
CollisionData Col_Lamp01 = { 0, CollisionShape_Cyl1, 0x77, 0, 0, {0.0, 22.0, 0.0}, 3.0, 22.0, 0.0, 0.0, 0, 0, 0 };
CollisionData Col_Bell01[] = {
	{ 0, (CollisionShapes)0x6, 0x77, 0, 0, {0.0, -30.0, 0.0}, 17.0, 4.0, 0.0, 0.0, 0, 0, 0 },
	{ 0, CollisionShape_Cyl1, 0x77, 0, 0, {0.0, -48.0, 0}, 19.0, 5.0, 0.0, 0.0, 0, 0, 0 },
};

CollisionData Col_Bell02 = { 0, (CollisionShapes)0x6, 0x10, 0xEC, 0, {0.0, -60.0, 0.0}, 8.0, 5.0, 0.0, 0.0, 0, 0, 0 };

CollisionData Col_SLight = { 0, (CollisionShapes)0x6, 0x77, 0, 0, {0.0, 15.0, 0.0}, 7.0, 7.0, 0.0, 0.0, 0, 0, 0 };

CollisionData Col_Fence = { 0, (CollisionShapes)0x3, 0x77, 0, 0, {0.0, 4.25, 0.0}, 13.0, 4.25, 2.75, 0.0, 0, 0, 0 };


void LoadModelsSH() {

	LoadCraneModels();
	SH_Cone[0] = LoadMDL("cone_cone1", ModelFormat_Chunk);
	SH_Cone[1] = LoadMDL("cone_cone2", ModelFormat_Chunk);

	LoadSHGlass();

	SH_Lamp[0] = LoadMDL("SH-Lamp01", ModelFormat_Chunk);

	SH_Bell[0] = LoadMDL("SH-Bell0", ModelFormat_Chunk);
	SH_Bell[1] = LoadMDL("SH-Bell1", ModelFormat_Chunk);
	SH_Jammer = LoadMDL("SH-Jammer", ModelFormat_Chunk);
	SH_SLight = LoadMDL("SH-Slight", ModelFormat_Chunk);
	SH_GFF = LoadMDL("SH-Fence", ModelFormat_Chunk);
}

void LoadObjSHTex() {
	LoadTextureList("OBJ_HIGHWAY", &highwayObj_TEXLIST);
	LoadTextureList("OBJ_HIGHWAY2", &highwayObj2_TEXLIST);
	LoadTextureList("OBJ_HIGHWAY2", &JammerTexlist);
	LoadTextureList("OBJ_HIGHWAY2", &JammerTexlist2);
}

void __cdecl GenericSHDisplay(ObjectMaster* a1)
{
	EntityData1* v1; // esi
	Angle rotZ; // eax
	Angle rotX; // eax
	Angle rotY; // eax

	v1 = a1->Data1.Entity;
	if (!ClipSetObject(a1))
	{

		njSetTexture(&highwayObj_TEXLIST);
		njPushMatrixEx();
		njTranslateV(0, &v1->Position);
		rotZ = v1->Rotation.z;
		if (rotZ)
		{
			njRotateZ(0, (unsigned __int16)rotZ);
		}
		rotX = v1->Rotation.x;
		if (rotX)
		{
			njRotateX(0, (unsigned __int16)rotX);
		}
		rotY = v1->Rotation.y;
		if (rotY)
		{
			njRotateY(0, (unsigned __int16)rotY);
		}
		DrawObject((NJS_OBJECT*)a1->field_4C);
		njPopMatrixEx();
	}
}

void SHSlight_Display(ObjectMaster* obj) {

	EntityData1* v1 = obj->Data1.Entity;
	unsigned __int64 v3; // rax
	int v11; // r4
	double v12; // fp1
	Angle v4; // eax
	NJS_OBJECT* v5;
	__int64 v9;
	__int64 v10;

	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrixEx();
	njTranslateV(0, &v1->Position);
	if (v1->Rotation.y) {
		njRotateY(0, v1->Position.y);
	}

	DrawChunkModel(SH_SLight->getmodel()->chunkmodel);
	njTranslate(0, SH_SLight->getmodel()->child->pos[0], SH_SLight->getmodel()->child->pos[1], SH_SLight->getmodel()->child->pos[2]);

	v9 = v1->field_6;
	v11 = (int)((float)((float)njSin((int)((double)v9 * 65536.0 * 0.002777777777777778)) * (float)23.0)
		* 65536.0
		* 0.002777777777777778);
	if (v11)
	{
		(v10) = v1->field_6;
		v12 = njSin((int)((double)v10 * 65536.0 * 0.002777777777777778));
		njRotateX(0, (unsigned __int16)(int)((float)((float)v12 * (float)23.0) * 65536.0 * 0.002777777777777778));
	}
	v4 = v1->Rotation.y;
	if (v4)
	{
		njRotateY(0, (unsigned __int16)v4);
	}
	DrawChunkModel(SH_SLight->getmodel()->child->chunkmodel);
	v5 = SH_SLight->getmodel()->child->child;
	njTranslate(0, SH_SLight->getmodel()->child->pos[0], SH_SLight->getmodel()->child->pos[1], SH_SLight->getmodel()->child->pos[2]);
	DrawChunkModel(v5->chunkmodel);
	njPopMatrixEx();
}

void SHSlight_Main(ObjectMaster* obj) {

	EntityData1* v1 = obj->Data1.Entity;

	if (!ClipObject(obj, 25000000.0))
	{
		AddToCollisionList(obj);
		sub_49CE60(v1, 0);
		++v1->field_6;
	}
}

void LoadSHSlight(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;

	if (!ClipObject(obj, 25000000.0)) {
		InitCollision(obj, &Col_SLight, 1, 4u);
		data->Collision->Range = 25.0;
		obj->DisplaySub = SHSlight_Display;
		obj->MainSub = SHSlight_Main;
	}
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

void __cdecl MainSubGlobalCol(ObjectMaster* obj)
{
	EntityData1* v1; // edi

	v1 = obj->Data1.Entity;
	if (!ClipSetObject(obj))
	{
		AddToCollisionList(obj);
		v1->Status &= 0xFFC7u;
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

void JammerChangeTex(ObjectMaster* obj)
{
	char v1; // cl
	EntityData1* result = obj->Data1.Entity;

	if (++result->field_6 > 0x19u)
	{
		v1 = result->NextAction;
		result->field_6 = 0;
		if (v1)
		{
			result->NextAction = v1 - 1;
			obj->field_4C = &JammerTexlist;
		}
		else
		{
			result->NextAction = 1;
			obj->field_4C = &JammerTexlist2;
		}
	}
}

void __cdecl OJamerDisplay(ObjectMaster* a2)
{
	EntityData1* v1; // esi
	Angle v2; // eax
	Angle v3; // eax
	Angle v4; // eax

	v1 = a2->Data1.Entity;
	njSetTexture((NJS_TEXLIST*)&highwayObj2_TEXLIST);
	njPushMatrixEx();
	njTranslateV(0, &v1->Position);
	v2 = v1->Rotation.z;
	if (v2)
	{
		njRotateZ(0, (unsigned __int16)v2);
	}
	v3 = v1->Rotation.x;
	if (v3)
	{
		njRotateX(0, (unsigned __int16)v3);
	}
	v4 = v1->Rotation.y;
	if (v4)
	{
		njRotateY(0, (unsigned __int16)v4);
	}
	DrawObject(SH_Jammer->getmodel());
	njPopMatrixEx();
}

void ObjectJammer(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;

	if (!ClipSetObject(obj))
	{
		if (data->Action == 1)
		{
			if (IsPlayerInsideSphere(&data->Position, 33.0))
			{
				data->Status | 0x100;
			}
			else {
				data->Status & 0xFEFF;
			}

			JammerChangeTex(obj);
		}
		else {
			data->Action = 1;
			obj->field_4C = &JammerTexlist;
			obj->DisplaySub = OJamerDisplay;
		}


	}
}

void __cdecl Bell_Child(ObjectMaster* obj)
{
	ObjectMaster* v1; // ebx
	EntityData1* v2; // ebp
	EntityData1* v3; // esi
	EntityData1* v4; // edi
	Angle v5; // eax
	Angle v6; // eax
	Angle v7; // eax
	Angle v8; // ebx
	unsigned __int64 v9; // rax
	int v10; // eax
	int v11; // eax
	Angle v12; // ecx

	v1 = obj;
	v2 = MainCharObj1[0];
	v3 = obj->Data1.Entity;
	v4 = obj->Parent->Data1.Entity;
	v5 = v3->Rotation.z;
	if (v5)
	{
		njRotateZ(0, (unsigned __int16)v5);
	}
	v6 = v3->Rotation.x;
	if (v6)
	{
		njRotateX(0, (unsigned __int16)v6);
	}
	v7 = v3->Rotation.y;
	if (v7)
	{
		njRotateY(0, (unsigned __int16)v7);
	}

	if ((v3->Collision->Flag & 1) == 0 || (v4->Status & 0x100) != 0)
	{
		if ((v4->Status & 0x200) != 0)
		{
			v10 = v4->Index & 0x3FF00;
			if (v10)
			{
				v11 = v10 & 0xFF00;
				if (v11 == 49152 || v11 == 0x4000)
				{
					PrintDebug("BELL CHILDD");
					//PlaySound4(93, 0, 0, 64, v4->Position.x, v4->Position.y, v4->Position.z);
				}
				v12 = v4->Index - 1024;
				v4->Index = v12;
				v3->Rotation.x = (unsigned __int64)(njSin(v12) * *(float*)&v3->field_6 * 3094.0);
				v3->Rotation.z = (unsigned __int64)(njSin(v4->Index) * v3->Index * 3094.0);
			}
			else
			{
				v4->Status &= 0xFDFFu;
			}
		}

		AddToCollisionList(obj);
		sub_49CE60(v3, 0);
	}
	else
	{
		/*GetPlayerRunningSpeed(0, (float*)&obj);
		if (*(float*)&obj >= 1.0)
		{
			v8 = (unsigned __int16)v2->Rotation.y;
			*(float*)&v3->timer = njSin(v8);
			v3->LoopData.Single = -njCos(v8);
			if (*(float*)&obj > 3.0)
			{
				*(float*)&obj = 3.0;
			}
			v9 = (unsigned __int64)*(float*)&obj;
			v4->Status |= 3u;
			v4->Index = (DWORD)v9 << 16;
		}*/
	}
}


void Bell_Display(ObjectMaster* obj) {
	EntityData1* v3 = obj->Data1.Entity;
	Angle v4;

	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrixEx();
	njTranslateV(0, &v3->Position);
	njPushMatrixEx();
	v4 = v3->Rotation.y;
	if (v4)
	{
		njRotateY(0, (unsigned __int16)v4);
	}

	DrawObject(SH_Bell[0]->getmodel());
	njPopMatrixEx();
	DrawObject(SH_Bell[1]->getmodel());
	njPopMatrixEx();
}

void Bell_Main(ObjectMaster* obj) {

	EntityData1* v2; // ebx
	EntityData1* v3; // esi
	Angle v4; // eax
	CollisionInfo* v5; // eax
	char v6; // al
	double v7; // st7
	CollisionInfo* v8; // eax
	float y; // [esp+0h] [ebp-1Ch]

	v3 = obj->Data1.Entity;

	v2 = obj->Child->Data1.Entity;

	v5 = v3->Collision;

	if ((v5->Flag & 1) == 0 || (v3->Status & 0x100) != 0)
	{
		if ((v3->Status & 0x300) == 256)
		{
			if (v5)
			{
				if ((v5->Flag & 1) == 0)
				{
					if (v2)
					{
						v8 = v2->Collision;
						if (v8)
						{
							if ((v8->Flag & 1) == 0 && !v3->Index)
							{
								v3->Status &= 0xFEFFu;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		v6 = v3->Action;
		if (v3->Action)
		{
			v7 = v3->Position.y - 70.0;
			v3->Action = v6 - 1;
			y = v7;

		}
		//PlaySound(93, 0, 0, 0);
		PrintDebug("bellllllll");
		v3->Status |= 1u;
	}

	AddToCollisionList(obj);
	sub_49CE60(v3, 0);

}

void __cdecl OHwBell(ObjectMaster* obj)
{
	EntityData1* v1; // esi
	ObjectMaster* v2; // eax
	EntityData1* v3; // ecx

	v1 = obj->Data1.Entity;
	v1->Rotation.z = 0;
	v1->Rotation.x = 0;
	InitCollision(obj, Col_Bell01, 2, 4u);

	v2 = LoadChildObject((LoadObj)(LoadObj_UnknownA | LoadObj_Data1 | LoadObj_Data2), Bell_Child, obj);
	v3 = v2->Data1.Entity;
	v3->Position = v1->Position;
	v3->Rotation.z = 0;
	v3->Rotation.x = 0;
	v3->Rotation.y = v1->Rotation.y;
	InitCollision(v2, &Col_Bell02, 1, 4u);

	v1->Status &= 0xFCu;
	v1->Action = 5;
	obj->MainSub = Bell_Main;
	obj->DisplaySub = Bell_Display;
	obj->DeleteSub = j_DeleteChildObjects;
}


void Lamp_Main(ObjectMaster* a1) {

	EntityData1* v1 = a1->Data1.Entity;
	AddToCollisionList(a1);
	v1->Status &= 0xC7u;

}
void __cdecl LoadLamp01(ObjectMaster* a1)
{
	a1->MainSub = Lamp_Main;
	a1->DisplaySub = GenericSHDisplay;
}

void InitLamp01(ObjectMaster* obj) {
	obj->field_4C = SH_Lamp[0]->getmodel();
	InitCollision(obj, &Col_Lamp01, 1, 4u);
	obj->Data1.Entity->Status |= 0x8000u;
	LoadLamp01(obj);
}

//Ennemies
static void __cdecl Beetle_Stationary(ObjectMaster* a1)
{
	EntityData1* entity = a1->Data1.Entity;
	entity->Rotation.x = 0;
	entity->Rotation.z = 0xC1;
	entity->Scale = { 0.10, 3.50, 51 };
	a1->MainSub = (ObjectFuncPtr)Beetle_Main;
}

static void __cdecl Beetle_Attack(ObjectMaster* a1)
{
	EntityData1* entity = a1->Data1.Entity;
	entity->Rotation.x = 0x1;
	entity->Rotation.z = 0x1C0;
	entity->Scale = { 4, 1, 150 };
	a1->MainSub = (ObjectFuncPtr)Beetle_Main;
}

static void __cdecl Beetle_Electric(ObjectMaster* a1)
{
	EntityData1* entity = a1->Data1.Entity;
	entity->Rotation.x = 0;
	entity->Rotation.z = 0x101;
	entity->Scale = { 0.10, 3.50, 51 };
	a1->MainSub = (ObjectFuncPtr)Beetle_Main;
}

static void __cdecl Robots(ObjectMaster* a1)
{
	EntityData1* entity = a1->Data1.Entity;
	entity->Rotation.x = 0x1;
	entity->Rotation.z = 0x100;
	entity->Scale = { 0, 1, 126 };
	entity->Position.y -= 6.5;
	a1->MainSub = (ObjectFuncPtr)E_AI;
}

void __fastcall ObjectSetupInput(EntityData1* twp, EntityData2* mwp)
{
	twp->Status &= 0xFFC7u;
	if (mwp)
	{
		mwp->Acceleration.z = 0.0;
		mwp->Acceleration.y = 0.0;
		mwp->Acceleration.x = 0.0;
	}
}

void __cdecl sub_46C150(ObjectMaster* a1)
{
	if (a1->SETData) {
		a1->SETData->Flags &= 0x7FFFu;
		a1->SETData->Flags &= 0xFFFEu;
	}
	a1->MainSub = DeleteObject_;
}



void __cdecl Cone_Display(ObjectMaster* a2)
{
	EntityData1* v1; // esi
	Angle v2; // eax
	Angle v3; // eax
	Angle v4; // eax

	v1 = a2->Data1.Entity;

	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrix(0);
	njTranslateV(0, &v1->Position);
	v2 = v1->Rotation.z;
	if (v2)
	{
		njRotateZ(0, (unsigned __int16)v2);
	}
	v3 = v1->Rotation.x;
	if (v3)
	{
		njRotateX(0, (unsigned __int16)v3);
	}
	v4 = v1->Rotation.y;
	if (v4)
	{
		njRotateY(0, (unsigned __int16)v4);
	}
	if (v1->Action)
	{
		DrawObject(SH_Cone[1]->getmodel());
	}
	else
	{
		DrawObject(SH_Cone[0]->getmodel());
	}
	njPopMatrixEx();

}

void __cdecl Cone_Main(ObjectMaster* a1)
{
	ObjectMaster* v1; // ebx
	EntityData1* v2; // esi
	NJS_POINT3* v3; // edi
	Angle v4; // edi
	double v5; // st7
	ObjectMaster* v6; // ecx
	Rotation a4; // [esp+Ch] [ebp-Ch] BYREF
	Float v13 = 0;

	v1 = a1;
	v2 = a1->Data1.Entity;
	v3 = &MainCharObj1[0]->Position;
	if (ClipSetObject(a1))
	{
		if (v2->Scale.y != 0.0 || v2->Scale.x != 0.0)
		{
			sub_46C150(v1);
		}
	}
	else
	{
		if (v2->Scale.y == 0.0 && v2->Scale.x == 0.0)
		{
			if ((v2->Collision->Flag & 1) != 0)
			{
				GetPlayerRunningSpeed(0, v13);
				if (v13) {
					v2->Scale.x = v13 * 1.5;
					v2->Scale.y = v13 * 0.66666669;
				}
				v2->field_6 = (unsigned __int16)(-16384
					- (unsigned __int64)(atan2(
						v2->Position.z - v3->z,
						v2->Position.x - v3->x)
						* 65536.0
						* -0.1591549762031479));
				//PlaySound(118, 0, 0, 0);
			}
		}
		else
		{
			v4 = v2->field_6;
			v2->Position.x = v2->Position.x - njSin(v4) * v2->Scale.x;
			v2->Position.y = v2->Scale.y + v2->Position.y;
			v2->Position.z = njCos(v4) * v2->Scale.x + v2->Position.z;

			v5 = v2->Scale.x - 0.5;
			v2->Scale.x = v5;
			if (v5 < 0.0)
			{
				v2->Scale.x = 0.0;
			}
			v6 = a1;
			if (v2->Scale.y >= -1.0)
			{
				v2->Scale.y = 0.0;
			}
			else
			{
				v2->Scale.y = v2->Scale.y * -0.5;
			}

		}

		AddToCollisionList(a1);
		ObjectSetupInput(v2, 0);
	}
}


void __cdecl OCone2(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	data->Action = 1;
	data->Scale.x = 0.0;
	data->Scale.y = 0.0;
	InitCollision(obj, &Col_Cone, 1, 4u);
	obj->MainSub = (ObjectFuncPtr)Cone_Main;
	obj->DisplaySub = (ObjectFuncPtr)Cone_Display;
}

void __cdecl OCone1(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	data->Action = 0;
	data->Scale.x = 0.0;
	data->Scale.y = 0.0;
	InitCollision(obj, &Col_Cone, 1, 4u);
	obj->MainSub = (ObjectFuncPtr)Cone_Main;
	obj->DisplaySub = (ObjectFuncPtr)Cone_Display;
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
	{ (LoadObj)2, 3, 1, 25000000, LoadSHSlight, }, /* "O SLIGHT" */
	{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x6188E0, "O ARCADE01" } /* "O ARCADE01" */,
	{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x6188F0, "O ARCADE02" } /* "O ARCADE02" */,
	{ (LoadObj)2 },// 3, 0, 0, 0, (ObjectFuncPtr)0x618900, "O ARCADE03" } /* "O ARCADE03" */,
	{ (LoadObj)6, 3, 1, 1000000, ObjectJammer } /* "O JAMER" */,
	{ (LoadObj)LoadObj_Data1, 3, 1, 2250000, nullptr }, /* "O STP4S" */
	{ (LoadObj)6 },//3, 1, 2250000, 0, (ObjectFuncPtr)0x617F00, "O STP4T" } /* "O STP4T" */,
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
	{ (LoadObj)2, 3, 0, 0, InitLamp01, } /* "O LAMP01" */,
	{ (LoadObj)2, 3, 0, 0, nullptr, },
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
	{ (LoadObj)2 },//3, 0, 0, 0, (ObjectFuncPtr)0x615410, "O GG" } /* "O GG" */,
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
	{ (LoadObj)2, 2, 0, 0, (ObjectFuncPtr)CCUBE, },
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

