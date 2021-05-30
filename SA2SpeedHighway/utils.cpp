#include "pch.h"

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
		delete *info;
	}
}

static void FixLand(LandTable* land) {
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

void LoadLandTable(const char* path, LandTableInfo** land, const TexPackInfo* tex) {
	LandTableInfo* land_ = new LandTableInfo(HelperFunctionsGlobal.GetReplaceablePath(path));

	if (land_ != nullptr)
	{
		LandTable* geo = land_->getlandtable();

		FixLand(geo);
		
		geo->TextureList = tex->TexList;
		geo->TextureName = (char*)tex->TexName;
		LoadTextureList(tex->TexName, tex->TexList);
		LandTableSA2BModels = 0;
		LoadLandManager(geo);
	}
	
	*land = land_;
}

void DeleteSetHandler()
{
	if (SetObject_ptr)
	{
		DeleteObject_(SetObject_ptr);
		SetObject_ptr = nullptr;
	}
}

void LoadLevelLayout(const ObjectListHead* objlist, const char* s, const char* u) {
	for (uint8_t i = 0; i < objlist->Count; ++i) {
		RadicalHighway_ObjectList.List[i] = objlist->List[i];
	}

	void* setfile = LoadSETFile(2048, (char*)s, (char*)u);
	LoadSetObject(&RadicalHighway_ObjectList, setfile);
}

void LoadLevelMusic(const char* name) {
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

void SetStartEndPoints(const StartPosition* start, const LevelEndPosition* start2pIntro, const StartPosition* end, const LevelEndPosition* missionend) {
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

void MovePlayers(float x, float y, float z)
{
	for (int i = 0; i < 2; ++i)
	{
		if (MainCharObj1[i])
		{
			MainCharObj1[i]->Position = { x, y, z };
		}
	}
}