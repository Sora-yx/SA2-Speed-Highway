#include "pch.h"

static const int SADXLevel[2] = { LevelIDs_RadicalHighway, NULL };

bool isSADXLevel()
{
	for (int i = 0; i < LengthOfArray(SADXLevel); i++)
	{
		if (CurrentLevel == SADXLevel[i])
		{
			return true;
		}
	}

	return false;
}


void __cdecl EnemyBounceThing(unsigned __int8 playerID, float speedX, float speedY, float speedZ)
{
	int index; // eax
	EntityData2_R* v5; // ecx
	EntityData1* data1; // edx
	CharObj2Base* data2; // esi
	NJS_VECTOR newSpeed; // [esp+4h] [ebp-Ch] BYREF

	index = playerID;
	v5 = (EntityData2_R*)MainCharData2[index];
	data1 = MainCharObj1[index];
	data2 = MainCharObj2[index];
	if (v5)
	{
		if (data2)
		{
			if (data1)
			{
				v5->spd.x = speedX;
				v5->spd.y = speedY;
				v5->spd.z = speedZ;

				newSpeed.y = speedY;
				newSpeed.x = speedX;
				newSpeed.z = speedZ;

				PConvertVector_G2P(data1, &newSpeed);

				if (newSpeed.x <= 0.001 && newSpeed.x >= -0.001)
				{
					newSpeed.x = 0.0;
				}
				if (newSpeed.z <= 0.001 && newSpeed.z >= -0.001)
				{
					newSpeed.z = 0.0;
				}
				data2->Speed = newSpeed;
			}
		}
	}
}

void __cdecl EnemyBounceThing_Wrapper(unsigned __int8 playerID, float a2, float a3, float a4)
{
	EntityData1* data1; // eax

	data1 = MainCharObj1[playerID];
	data1->Status |= 0x10u;
	data1->NextAction = 3;
	EnemyBounceThing(playerID, a2, a3, a4);
}

signed int __cdecl GetPlayerRunningSpeed(unsigned __int8 a1, Float a2)
{
	EntityData1* v2; // ecx

	v2 = MainCharObj1[a1];
	if (!v2 || (v2->Status & (Status_OnObjectColli | Status_Ground)) == 0)
	{
		return 0;
	}
	a2 = MainCharObj2[a1]->Speed.x;
	return 1;
}

void ObjectSetupInput(EntityData1* twp, EntityData2* mwp)
{
	twp->Status &= Status_Unknown5 | Status_Unknown4 | Status_Hurt | Status_OnObjectColli | Status_Ground;
	if (mwp)
	{
		mwp->Acceleration.z = 0.0;
		mwp->Acceleration.y = 0.0;
		mwp->Acceleration.x = 0.0;
	}
}

int IsPlayerInsideSphere(NJS_VECTOR* position, float a2)
{
	int player; // esi
	EntityData1* v3; // eax
	CollisionInfo* v4; // eax
	float* v5; // eax
	double v6; // st7
	float posX; // [esp+4h] [ebp-1Ch]
	float posY; // [esp+8h] [ebp-18h]
	float posZ; // [esp+Ch] [ebp-14h]
	float v11; // [esp+10h] [ebp-10h]
	NJS_VECTOR a1; // [esp+14h] [ebp-Ch] BYREF

	posX = position->x;
	player = 0;
	posY = position->y;
	posZ = position->z;
	while (1)
	{
		v3 = MainCharObj1[player];
		if (v3)
		{
			v4 = v3->Collision;
			if (v4)
			{
				v5 = (float*)&v4->CollisionArray->kind;
				v6 = v5[2];
				v5 += 3;
				a1.x = v6 - posX;
				a1.y = *v5 - posY;
				a1.z = v5[1] - posZ;
				v11 = njScalor(&a1) - a2;
				if (v11 < 0.0)
				{
					break;
				}
			}
		}
		if (++player >= 2)
		{
			return 0;
		}
	}
	return player + 1;
}

float GetDistance(NJS_VECTOR* orig, NJS_VECTOR* dest)
{
	return sqrtf(powf(dest->x - orig->x, 2) + powf(dest->y - orig->y, 2) + powf(dest->z - orig->z, 2));
}

bool IsPointInsideSphere(NJS_VECTOR* center, NJS_VECTOR* pos, float radius)
{
	return GetDistance(center, pos) <= radius;
}

const char* ModelFormatStrings[]
{
	"collision",
	"chunk",
	"battle"
};

//Load Object File
ModelInfo* LoadMDL(const char* name, ModelFormat format) {
	std::string fullPath;

	if (format == ModelFormat_Chunk)
	{
		fullPath = "resource\\gd_PC\\Models\\";
	}


	if (format == ModelFormat_Basic)
	{
		fullPath = "resource\\gd_PC\\Collisions\\";
	}

	fullPath += name;

	switch (format)
	{
	case ModelFormat_Basic:
		fullPath += ".sa1mdl";
		break;
	case ModelFormat_Chunk:
		fullPath += ".sa2mdl";
		break;
	case ModelFormat_SA2B:
		fullPath += ".sa2bmdl";
		break;
	}

	const char* foo = fullPath.c_str();

	ModelInfo* temp = new ModelInfo(HelperFunctionsGlobal.GetReplaceablePath(foo));

	if (temp->getformat() == format)
	{
		PrintDebug("[SA2 Speed Highway] Loaded %s model: %s.", ModelFormatStrings[(int)format - 1], name);
	}
	else {
		PrintDebug("[SA2 Speed Highway] Failed loading %s model: %s.", ModelFormatStrings[(int)format - 1], name);
	}

	return temp;
}

void LoadAnimation(AnimationFile** info, const char* name, const HelperFunctions& helperFunctions)
{
	std::string fullPath = "system\\anims\\";
	fullPath = fullPath + name + ".saanim";

	AnimationFile* anm = new AnimationFile(helperFunctions.GetReplaceablePath(fullPath.c_str()));

	if (anm->getmodelcount() == 0)
	{
		delete anm;
		*info = nullptr;
	}
	else {
		*info = anm;
	}
};

AnimationFile* LoadAnim(const char* name)
{
	std::string fullPath = "resource\\gd_PC\\Anim\\";

	fullPath = fullPath + name + ".saanim";

	AnimationFile* file = new AnimationFile(HelperFunctionsGlobal.GetReplaceablePath(fullPath.c_str()));

	if (file->getmotion() != nullptr) {
		PrintDebug("[SA2 Speed Highway] Loaded animation: %s.", name);
	}
	else {
		PrintDebug("[SA2 Speed Highway] Failed loading animation: %s.", name);
	}

	return file;
}

void FreeMDL(ModelInfo* pointer)
{
	if (pointer) delete(pointer);
}

void FreeAnim(AnimationFile* pointer)
{
	if (pointer) delete pointer;
}

void FreeLandTableObj()
{
	if (LandManagerPtr)
	{
		DeleteObject_(LandManagerPtr);
		LandManagerPtr = nullptr;
	}
}

void FreeLandTableInfo(LandTableInfo** info)
{
	if (*info)
	{
		delete* info;
	}
}

static void FixLand(LandTable* land)
{
	for (int i = 0; i < land->COLCount; ++i) {
		COL* col = &land->COLList[i];

		col->field_14 = 0;
		col->Chunks = 0;


		if (col->Flags == 0x2)
		{
			col->Flags = 0x40000002;
		}
		else if (col->Flags & SurfaceFlag_Visible)
		{
			col->Flags = SurfaceFlag_Visible;
		}
		else if (col->Flags & SurfaceFlag_Water)
		{
			col->Flags = SurfaceFlag_Water;
		}
		else
		{
			col->Flags = 0x1;
		}
	}
}

void LoadLandTable(const char* path, LandTableInfo** land, const TexPackInfo* tex)
{
	LandTableInfo* land_ = new LandTableInfo(HelperFunctionsGlobal.GetReplaceablePath(path));

	if (land_ != nullptr)
	{
		LandTable* geo = land_->getlandtable();

		FixLand(geo);

		geo->TextureList = tex->TexList;
		geo->TextureName = (char*)tex->TexName;
	}

	*land = land_;
}

void LoadLandManager_(LandTable* land)
{
	LandTableSA2BModels = 0;
	LoadLandManager(land);
}

void DeleteSetHandler()
{
	if (SetObject_ptr)
	{
		DeleteObject_(SetObject_ptr);
		SetObject_ptr = nullptr;
	}
}

void DeleteSETObjects()
{
	for (int i = 0; i < ObjectLists_Length; ++i)
	{
		ObjectMaster* obj = ObjectLists[i];
		ObjectMaster* obj_orig = obj;

		if (obj)
		{
			while (1)
			{
				ObjectMaster* previous = obj->PrevObject;

				if (obj->SETData)
				{
					obj->MainSub = DeleteObject_;
				}

				if (obj->Child)
				{
					DeleteChildObjects(obj);
				}

				if (previous == obj_orig)
				{
					break;
				}

				obj_orig = ObjectLists[i];

				if (!obj_orig)
				{
					break;
				}

				obj = previous;
			}
		}
	}
}



void DeleteDeathZones() {

	if (DeathZoneObject_ptr) {
		DeleteObject_(DeathZoneObject_ptr);
	}
}


void LoadLevelLayout(ObjectListHead* objlist, const char* s, const char* u)
{
	void* setfile = LoadSETFile(2048, (char*)s, (char*)u);
	LoadSetObject(objlist, setfile);
}

void LoadLevelMusic(const char* name)
{
	char character;
	int c = 0;

	do
	{
		character = name[c];
		CurrentSongName[c++] = character;
	} while (character);


	PlayMusic(name);
	ResetMusic();
}

void SetStartEndPoints(const StartPosition* start, const LevelEndPosition* start2pIntro, const StartPosition* end, const LevelEndPosition* missionend)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		HelperFunctionsGlobal.RegisterStartPosition(i, *start);

		if (start2pIntro)
		{
			HelperFunctionsGlobal.Register2PIntroPosition(i, *start2pIntro);
		}

		if (HelperFunctionsGlobal.Version >= 5)
		{
			HelperFunctionsGlobal.RegisterEndPosition(i, *end);
			HelperFunctionsGlobal.RegisterMission23EndPosition(i, *missionend);
		}
	}
}

void __cdecl StartPosManager(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	EntityData1* player = MainCharObj1[data->Index];

	if (player)
	{
		if (IsPointInsideSphere(&data->Position, &player->Position, 5.0f))
		{
			DeleteObject_(obj);
		}
		else
		{
			player->Position = data->Position;
			player->Rotation = data->Rotation;
		}
	}
	else
	{
		DeleteObject_(obj);
	}
}

static const void* const SavePosptr = (void*)0x43E520;
static inline void CP_SavePosition(NJS_VECTOR* pos, Rotation* rot, int pID, int a4)
{
	__asm
	{
		push[a4]
		push[pID]
		mov edi, [rot]
		mov ebx, [pos]
		call SavePosptr
		add esp, 8
	}
}


void MovePlayersToStartPos(NJS_VECTOR Pos, int yrot)
{
	for (int i = 0; i < MAXPLAYERS; ++i)
	{
		if (MainCharObj1[i])
		{
			EntityData1* data = LoadObject(1, "PLAYERTP", StartPosManager, LoadObj_Data1)->Data1.Entity;
			data->Index = i;
			data->Position = Pos;
			data->Rotation.y = yrot;
		}
	}

	return;
}

NJS_OBJECT* DynCol_AddFromObject(ObjectMaster* obj, NJS_OBJECT* object, NJS_VECTOR* position, Angle rotY, int flags)
{
	NJS_OBJECT* dynobj = GetFreeDyncolObjectEntry();

	if (dynobj)
	{
		memcpy(dynobj, object, sizeof(NJS_OBJECT));

		dynobj->evalflags &= 0xFFFFFFFC;

		dynobj->ang[1] = rotY;
		dynobj->pos[0] = position->x;
		dynobj->pos[1] = position->y;
		dynobj->pos[2] = position->z;

		DynCol_Add((SurfaceFlags)flags, obj, dynobj);
		obj->EntityData2 = (UnknownData2*)dynobj;
	}

	return dynobj;
}

void __cdecl MainSubGlobalDynCol(ObjectMaster* obj)
{

	EntityData1* data = obj->Data1.Entity;
	if (!ClipSetObject(obj))
	{
		if (data->Action == 0) {

			if (obj->Data2.Undefined == nullptr)
				return;

			obj->DeleteSub = DeleteFunc_DynCol;
			DynCol_AddFromObject(obj, (NJS_OBJECT*)obj->Data2.Undefined, &data->Position, data->Rotation.y, SurfaceFlag_Solid);
			data->Action = 1;
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

void DoNextAction_r(int playerNum, char action, int unknown)
{
	EntityData1* v3; // eax

	v3 = MainCharObj1[playerNum];
	if (v3)
	{
		v3->Status |= Status_DoNextAction;
		v3->NextAction = action;
		MainCharObj2[playerNum]->field_28 = unknown;
	}
}


// signed int __usercall CL_ColPolCheckTouchRe@<eax>(csts* a1@<eax>, NJS_OBJECT* object, SurfaceFlags attribute)
static const void* const CL_ColPolCheckTouchRePtr = (void*)0x48CE40;
static inline int CL_ColPolCheckTouchReASM(NJS_OBJECT* object, csts* a1, bool attribute)
{
	int result;
	__asm
	{
		push[attribute]
		push[a1]
		mov eax, [object]
		call CL_ColPolCheckTouchRePtr
		add esp, 8
		mov result, eax
	}
	return result;
}

int CL_ColPolCheckTouchRe(NJS_OBJECT* object, csts* a2, bool attribute) {
	return CL_ColPolCheckTouchReASM(object, a2, attribute);
}

double __fastcall sub_7889F0(NJS_VECTOR* a1, NJS_VECTOR* a2, NJS_VECTOR* a3)
{
	double v3; // st7
	double v4; // st6
	double v5; // st5
	float v7; // [esp+0h] [ebp-4h]

	v3 = a2->z * a1->y - a2->y * a1->z;
	v4 = a2->x * a1->z - a2->z * a1->x;
	v5 = a2->y * a1->x - a2->x * a1->y;
	a3->x = v3;
	a3->y = v4;
	a3->z = v5;
	v7 = v5 * v5 + v4 * v4 + v3 * v3;
	return sqrt(v7);
}

int VectorAngle(NJS_VECTOR* a1, NJS_VECTOR* a2, NJS_VECTOR* a3)
{
	double v3; // st7
	int v5; // esi
	float v6; // [esp+8h] [ebp-10h]
	NJS_VECTOR a3a; // [esp+Ch] [ebp-Ch] BYREF

	v3 = njInnerProduct(a1, a2);
	v6 = v3;
	if (v3 <= -1.0)
	{
		return 0x8000;
	}
	if (v6 >= 1.0)
	{
		return 0;
	}
	v5 = (unsigned __int64)(acos(v6) * 65536.0 * 0.1591549762031479);
	sub_7889F0(a1, a2, &a3a);
	if (a3)
	{
		if (njInnerProduct(a3, &a3a) < 0.0)
		{
			v5 = 0x10000 - v5;
		}
	}
	return v5;
}

static const void* const PhysicsAnimCheckPtr = (void*)0x474F80;
static inline void PhysicsAndAnimCheckASM(CharObj2Base* a1, EntityData1* a2)
{

	__asm
	{
		push[a2]
		mov ebx, [a1]
		call PhysicsAnimCheckPtr
		add esp, 4
	}
}


void PhysicsAndAnimCheck(CharObj2Base* a1, EntityData1* a2) {
	return PhysicsAndAnimCheckASM(a1, a2);
}

int __cdecl DoRotationStuff(unsigned __int8 a1, int a2, int a3, int a4)
{
	int v4; // eax
	EntityData1* v5; // edx
	EntityData2_R* v6; // eax
	int result; // eax

	v4 = a1;
	v5 = MainCharObj1[v4];
	v6 = (EntityData2_R*)MainCharData2[v4];
	v5->Rotation.x = a2;
	v5->Rotation.y = 0x4000 - a3;
	v6->ang_aim.y = 0x4000 - a3;
	result = a4;
	v5->Rotation.z = a4;
	return result;
}

void ResetMaterialColorOffset()
{
	GlobalMatColorR = 0.0f;
	GlobalMatColorG = 0.0f;
	GlobalMatColorB = 0.0f;
	GlobalMatColorA = 0.0f;
	return;
}

ObjectMaster* __cdecl GetCharacterObject(unsigned __int8 character)
{
	return MainCharacter[character];
}

void __cdecl dothedash(unsigned __int8 playerID, NJS_VECTOR* _speed, Rotation* angle, __int16 disableTime)
{
	int index; // eax
	EntityData1* data1; // ecx
	EntityData2_R* data2; // esi
	CharObj2Base* co2; // eax
	Angle wtf_y; // ebx
	float wtf_z; // edx
	NJS_VECTOR result; // [esp+Ch] [ebp-Ch] BYREF

	index = playerID;
	data1 = MainCharObj1[index];
	data2 = (EntityData2_R*)MainCharData2[index];
	co2 = MainCharObj2[index];
	co2->field_12 = disableTime;
	co2->Speed = *_speed;
	data1->Rotation.x = angle->x;
	wtf_y = angle->y;
	data1->Rotation.y = 0x4000 - wtf_y;
	data2->ang_aim.y = 0x4000 - wtf_y;
	data1->Rotation.z = angle->z;
	result.x = _speed->x;
	wtf_z = _speed->z;
	result.y = _speed->y;
	result.z = wtf_z;
	PConvertVector_P2G(data1, &result);
	data2->spd = result;
}

void __cdecl DoThatThingWhereYouGetCloseAndItLightsUp(EntityData1* a1, unsigned __int16 a2)
{
	NJS_ARGB a1a; // [esp+0h] [ebp-10h] BYREF

	if ((a2 & (unsigned __int16)(1 << GetCharacterID(0))) != 0)
	{
		a1a.a = 0.0;
		if (IsPlayerInsideSphere(&a1->Position, 20.0))
		{
			a1a.r = 0.5;
			a1a.g = 0.5;
			a1a.b = 0.5;
		}
		else
		{
			a1a.r = 0.0;
			a1a.g = 0.0;
			a1a.b = 0.0;
		}
		SetMaterialColor(a1a.a, a1a.r, a1a.g, a1a.b);
	}
}

void __cdecl Load_MultipleChildObjects(ObjectThing* things, ObjectMaster* parent, uint32_t size)
{
	EntityData1* entity;
	NJS_VECTOR a3;
	entity = parent->Data1.Entity;

	njPushMatrix(_nj_unit_matrix_);
	if (entity)
	{
		njTranslateV(0, &entity->Position);
		njRotateZXY(&entity->Rotation);
	}

	for (int i = 0; i < size; i++) {

		ObjectMaster* obj = LoadChildObject((LoadObj)things[i].flags, things[i].func, parent);

		if (obj)
		{
			EntityData1* childData = obj->Data1.Entity;

			if (childData)
			{
				childData->Status = things[i].status;
				njCalcPoint(&things[i].pos_probably, &a3, CURRENT_MATRIX);
				njAddVector(&childData->Position, &a3);

				childData->Rotation.x = things[i].rotation.x + entity->Rotation.x;
				childData->Rotation.y = things[i].rotation.y + entity->Rotation.y;
				childData->Rotation.z = things[i].rotation.z + entity->Rotation.z;
			}
		}
	}

	njPopMatrix(1u);
	return;
}


// void __usercall(NJS_VECTOR *a1@<ebx>, float a2, float a3)
static const void* const SplashWaterPtr = (void*)0x6ED630;
static inline void LoadSplashWaterASM(int a1)
{
	__asm
	{
		mov ebx, [a1]
		call SplashWaterPtr
	}
}

void LoadSplashWater(int a1) {
	return LoadSplashWaterASM(a1);
}


void SetCameraPos(float x, float y, float z) {
	CameraData.Position.x = x;
	CameraData.Position.y = y;
	CameraData.Position.z = z;
	return;
}