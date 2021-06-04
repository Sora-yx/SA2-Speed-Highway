#pragma once

bool isSADXLevel();
float GetDistance(NJS_VECTOR* orig, NJS_VECTOR* dest);
bool IsPointInsideSphere(NJS_VECTOR* center, NJS_VECTOR* pos, float radius);
void njCnkAction(NJS_ACTION* action, float frame);
void njCnkMotion(NJS_OBJECT* obj, NJS_MOTION* mot, float frame);
void njAddVector(NJS_VECTOR* vd, NJS_VECTOR* vs);
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
void MovePlayersToStartPos(float x, float y, float z);
int IsPlayerInsideSphere(NJS_VECTOR* position, float a2);
signed int __cdecl GetPlayerRunningSpeed(unsigned __int8 a1, Float a2);
void __cdecl sub_49CE60(EntityData1* a1, EntityData2* a2);
int __fastcall SubAngle(int ang0, int ang1);
void DrawChunkModel(NJS_CNK_MODEL* a1);

