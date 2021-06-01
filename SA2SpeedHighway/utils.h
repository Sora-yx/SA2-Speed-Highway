#pragma once

void njCnkAction(NJS_ACTION* action, float frame);
void njCnkMotion(NJS_OBJECT* obj, NJS_MOTION* mot, float frame);
ModelInfo* LoadMDL(const char* name, ModelFormat format);
AnimationFile* LoadAnim(const char* name);
int __cdecl BAMS_SubWrap(__int16 bams_a, unsigned __int16 bams_b, int limit);
void FreeMDL(ModelInfo* pointer);
void LoadAnimation(AnimationFile** info, const char* name, const HelperFunctions& helperFunctions);
void FreeAnim(AnimationFile* pointer);
void FreeLandTableObj();
void FreeLandTableInfo(LandTableInfo** info);
void LoadLandTable(const char* path, LandTableInfo** land, const TexPackInfo* tex);
void LoadLandManager_(LandTable* land);
void DeleteSetHandler();
void DeleteSETObjects();
void LoadLevelLayout(ObjectListHead* objlist, const char* s, const char* u);
void LoadLevelMusic(const char* name);
void SetStartEndPoints(const StartPosition* start, const LevelEndPosition* start2pIntro, const StartPosition* end, const LevelEndPosition* missionend);
void MovePlayers(float x, float y, float z);
bool isSADXLevel();