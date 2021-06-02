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

void njCnkAction(NJS_ACTION* action, float frame)
{
	*(int*)0x25EFE54 = 0x25EFE60;
	njSetMotion(action->motion, frame);
	MotionDrawCallback = (ObjectFuncPtr)0x42E660;
	DrawObjMotion(action->object);
}

void njCnkMotion(NJS_OBJECT* obj, NJS_MOTION* mot, float frame)
{
	*(int*)0x25EFE54 = 0x25EFE60;
	njSetMotion(mot, frame);
	MotionDrawCallback = (ObjectFuncPtr)0x42E660;
	DrawObjMotion(obj);
}

void njAddVector(NJS_VECTOR* vd, NJS_VECTOR* vs)
{
	vd->x += vs->x;
	vd->y += vs->y;
	vd->z += vs->z;
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

int __cdecl BAMS_SubWrap(__int16 bams_a, unsigned __int16 bams_b, int limit)
{
	int result; // eax
	__int16 v4; // cx

	result = bams_b;
	v4 = bams_b - bams_a;
	if ((__int16)(bams_b - bams_a) > limit || v4 < -limit)
	{
		if (v4 >= 0)
		{
			result = (unsigned __int16)(limit + bams_a);
		}
		else
		{
			result = (unsigned __int16)(bams_a - limit);
		}
	}
	return result;
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
		col->field_18 = 0;

		if (col->Flags == 0x2)
		{
			col->Flags = 0x40000002;
		}
		else if (col->Flags & SurfaceFlag_Visible)
		{
			col->Flags = SurfaceFlag_Visible;
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
		}
	}
	else
	{
		DeleteObject_(obj);
	}
}

void MovePlayersToStartPos(float x, float y, float z)
{
	for (int i = 0; i < MAXPLAYERS; ++i)
	{
		if (MainCharObj1[i])
		{
			EntityData1* data = LoadObject(1, "PLAYERTP", StartPosManager, LoadObj_Data1)->Data1.Entity;
			data->Index = i;
			data->Position = { x, y, z };
		}
	}
}