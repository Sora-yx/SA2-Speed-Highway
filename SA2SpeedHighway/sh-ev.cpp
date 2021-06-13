#include "pch.h"

static ModelInfo* sh_ev;
static ModelInfo* sh_evCol;

static ModelInfo* sh_evPlat;

extern NJS_TEXLIST highwayObj_TEXLIST;

void OEv_SetFlag(ObjectMaster* obj) {

    EntityData1* data = obj->Data1.Entity;
    NJS_OBJECT* item = (NJS_OBJECT*)obj->field_4C;

    item->pos[0] = data->Position.x;
    item->pos[1] = data->Position.y;
    item->pos[2] = data->Position.z;

    if (IsPlayerInsideSphere(&data->Position, 170.0f))
    {
        data->Status |= 0x100u;
    }
    else
    {
        data->Status &= 0xFEFFu;
    }
}

void __cdecl OEv(ObjectMaster* obj)
{
    EntityData1* data; // esi
    Angle v2; // eax
    int* v4; // ecx
    Vector3 a2; // [esp+8h] [ebp-30h] BYREF


    data = obj->Data1.Entity;
    if (!ClipObject(obj, 1020100.0))
    {
        
       if (data->Action)
        {
            if (data->Action == 1)
            {
               // QueueSound_XYZ(102, data, 1, 0, 30, data->Position.x, data->Position.y, data->Position.z);
                OEv_SetFlag(obj);
            }
        }
        else
        {
            data->Action = 1;
            obj->field_4C = sh_ev->getmodel();
           // data->timer = (int*)&object_0267315C;
            obj->DeleteSub = DeleteFunc_DynCol;
            obj->DisplaySub = GenericSHDisplay_RotY;
            DynCol_AddFromObject(obj, sh_evCol->getmodel(), &data->Position, data->Rotation.y, SurfaceFlag_Solid | SurfaceFlag_Dynamic);
            //DoObjectThing(stru_26B31A0, obj);
        }
    }
}

void LoadModel_Oev() {
	LoadMDL("sh-ev", ModelFormat_Chunk);
}

void Init_OEv() {

}