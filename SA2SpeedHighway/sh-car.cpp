#include "pch.h"

NJS_SPRITE CarLight;

NJS_TEXLIST* carLightTex;



void Load_SH_Car(ObjectMaster* obj) {
    EntityData1* data = obj->Data1.Entity;

    CarLight.sx = 0.2;
    CarLight.tlist = carLightTex;
    CarLight.sy = 0.2;
    //CarLight.tanim = anim_car_light;
    CarLight.p.x = 0.0;
    CarLight.p.y = 0.0;
    CarLight.p.z = 0.0;
    data->NextAction = 0;
    data->field_6 = 0;
    obj->field_2C = obj->Child;
    obj->DeleteSub = j_DeleteChildObjects;
    //obj->MainSub = CarManager_Main;
}