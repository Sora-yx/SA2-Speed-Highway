#pragma once

void FreeLandTable(LandTableInfo** land);
void LoadLandTable(const char* path, LandTableInfo** land, const TexPackInfo* tex);
void DeleteSetHandler();
void LoadLevelLayout(const ObjectListHead* objlist, const char* s, const char* u);
void LoadLevelMusic(const char* name);
void SetStartEndPoints(const StartPosition* start, const LevelEndPosition* start2pIntro, const StartPosition* end, const LevelEndPosition* missionend);
void MovePlayers(float x, float y, float z);