#pragma once

NJS_TEXANIM carTanim = { 0x40, 0x40, 0x20, 0x20, 0, 0, 0xFF, 0xFF, 0, 0 };

extern LoopHead PathList_SpeedHighway2_0;
extern LoopHead PathList_SpeedHighway2_1;

struct player_location_info
{
    int zone;
    float dist;
    float pos_1d;
    NJS_POINT3 pos_3d;
};

struct kuruma_model
{
    NJS_MODEL* colli_model;
    NJS_TEXLIST* tex;
    NJS_ACTION* act;
    float acc;
    float max_spd;
    float length;
};


struct kuruma_info
{
    char model_num;
    char col_num;
    float pos;
    float dist;
    float offset;
};
