#pragma once

bool isSADXLevel();
float GetDistance(NJS_VECTOR* orig, NJS_VECTOR* dest);
bool IsPointInsideSphere(NJS_VECTOR* center, NJS_VECTOR* pos, float radius);
ModelInfo* LoadMDL(const char* name, ModelFormat format);
AnimationFile* LoadAnim(const char* name);
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
void MovePlayersToStartPos(float x, float y, float z);
int IsPlayerInsideSphere(NJS_VECTOR* position, float a2);
signed int __cdecl GetPlayerRunningSpeed(unsigned __int8 a1, Float a2);
void ObjectSetupInput(EntityData1* twp, EntityData2* mwp);
void DynCol_AddFromObject(ObjectMaster* obj, NJS_OBJECT* object, NJS_VECTOR* position, Angle rotY, int flags);