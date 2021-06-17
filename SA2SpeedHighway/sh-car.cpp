#include "pch.h"
#include "sh-car.h"

NJS_SPRITE CarLight;

NJS_TEXLIST* carLightTex;



void Init_SH_Car(ObjectMaster* obj) {
    EntityData1* data = obj->Data1.Entity;

    CarLight.sx = 0.2;
    CarLight.tlist = carLightTex;
    CarLight.sy = 0.2;
    CarLight.tanim = &carTanim;
    CarLight.p.x = 0.0;
    CarLight.p.y = 0.0;
    CarLight.p.z = 0.0;
    data->NextAction = 0;
    data->field_6 = 0;
    obj->Data2.Undefined = obj->Child;
    obj->DeleteSub = j_DeleteChildObjects;
    //obj->MainSub = CarManager_Main;
}

void Load_SH_Car(ObjectMaster* a1) {
    LoadObject(3, "Init_Helico", Init_SH_Car, LoadObj_Data1 | LoadObj_Data2);
    a1->MainSub = DeleteObject_;
}