#include "pch.h"

static ModelInfo* SH_Glass;
static ModelInfo* SH_GlassBroken[13];
extern NJS_TEXLIST highwayObj_TEXLIST;
CollisionData Col_Glass = { 0, CollisionShape_Cube1, 77, 0xE0, 0, {0.0, -3.0, 0.0}, 20.0, 6.0, 20.0, 0.0, 0, 0, 0 };



void __cdecl DrawGlass(ObjectMaster* a1)
{
    EntityData1* v1; // esi
    NJS_OBJECT* v2; // edi

    v1 = a1->Data1.Entity;
    v2 = (NJS_OBJECT*)a1->field_4C;
    njSetTexture(&highwayObj_TEXLIST);
    njPushMatrix(0);
    njTranslate(0, v1->Position.x, v1->Position.y, v1->Position.z);
    njRotateX(0, v1->Rotation.x);
    njRotateY(0, v1->Rotation.y);
    njRotateZ(0, v1->Rotation.z);
    //DrawVisibleModel_Queue((NJS_MODEL_SADX*)v2[1], QueuedModelFlagsB_SomeTextureThing);

    DrawObject(v2);
    njPopMatrixEx();
}


void __cdecl ByeByeGlass(ObjectMaster* obj)
{
    EntityData1* v2; // esi
    __int16 v3; // bx
    unsigned __int64 v4; // rax
    Angle v5; // edi
    double v6; // st7
    unsigned __int64 v7; // rax
    int v8; // ecx
    double v9; // st7
    Angle v10; // edi
    Angle v11; // edx
    ObjectMaster* thisa; // [esp+10h] [ebp+4h]

    v2 = obj->Data1.Entity;
    v3 = v2->field_6;
    if ((unsigned __int16)v3 <= 0xC8u)
    {
        v4 = (unsigned __int64)(v2->field_2 * 25.0 * 65536.0 * 0.002777777777777778);
        v5 = v4;
        if (v2->Index == 2)
        {
            v2->field_6 = v3 + 1;
            v2->Position.x = njCos(v4) * 0.5 + v2->Position.x;
            v6 = njSin(v5);
            thisa = (ObjectMaster*)(unsigned __int16)v2->field_6;
            v2->Position.z = v6 * 0.5 + v2->Position.z;
            v2->Position.y = ((v2->field_2 + 1.0) * 1.3 - (double)(int)thisa * 0.0625) * 0.5 + v2->Position.y;
            v7 = (unsigned __int64)(v2->Scale.x * 65536.0 * 0.002777777777777778);
            v8 = v7;
        }
        else
        {
            v9 = v2->Scale.x * 0.1;
            v2->field_6 = v3 + 1;
            v2->Position.y = v9 - (double)(unsigned __int16)(v3 + 1) * 0.0625 + v2->Position.y;
            v2->Position.x = njCos(v4) * 0.81 + v2->Position.x;
            v2->Position.z = njSin(v5) * 0.81 + v2->Position.z;
            v8 = (unsigned __int64)(v2->Scale.x * 65536.0 * 0.002777777777777778);
            (v7) = 2 * v8;
        }
        v10 = v7 + v2->Rotation.y;
        v11 = v7 + v2->Rotation.z;
        v2->Rotation.x += v8;
        v2->Rotation.y = v10;
        v2->Rotation.z = v11;
        DrawGlass(obj);
    }
    else
    {
        obj->MainSub = DeleteObject_;
    }
}



void __cdecl GlassBroken(ObjectMaster* a1)
{
    EntityData1* v2; // esi
    NJS_OBJECT* v3; // eax
    double v4; // st7
    bool v5; // c0
    bool v6; // c3
    ObjectMaster* v7; // [esp+Ch] [ebp+4h]

    v2 = a1->Data1.Entity;
    if (!v2->field_6)
    {
        v3 = (NJS_OBJECT*)a1->field_4C;
        v2->Position.x = v3[2].pos[0] + v2->Position.x;
        v2->Position.y = v3[3].pos[1] + v2->Position.y;
        v2->Position.z = v3[4].pos[2] + v2->Position.z;
        v2->Scale.x = pow(-1.0, (double)(int)(unsigned __int64)v2->field_2);
        a1->DisplaySub = DrawGlass;
    }
    if (v2->Index == 2
        || (v7 = (ObjectMaster*)(unsigned __int16)v2->field_6,
            v4 = (double)(int)v7,
            v5 = v4 < v2->Scale.z,
            v6 = v4 == v2->Scale.z,
            v2->field_6 = (WORD)v7 + 1,
            !v5 && !v6))
    {
        a1->MainSub = ByeByeGlass;
        v2->field_6 = 0;
    }
    //sub_61A910(a1);
}


void __cdecl BreakGlass(ObjectMaster* a1, signed int timer)
{
    ObjectMaster* v2; // esi
    EntityData1* v3; // edi
    bool v4; // zf
    int v5; // ebp
    ObjectMaster* v6; // eax
    EntityData1* v7; // esi
    NJS_OBJECT* v8; // eax
    float v9; // edx
    char v10; // al
    int v11; // [esp+8h] [ebp-38h]
    int v12; // [esp+8h] [ebp-38h]
    NJS_OBJECT* v13[13]; // [esp+Ch] [ebp-34h]

    v2 = a1;
    v3 = a1->Data1.Entity;
    v4 = v3->field_6 == 0;

    for (int i = 0; i < LengthOfArray(SH_GlassBroken); i++) {
        v13[i] = SH_GlassBroken[i]->getmodel();
    }

    if (v4)
    {
        v5 = 0;
        v11 = 0;
        do
        {
            v6 = LoadObject(3, "GlassBroken", GlassBroken, LoadObj_Data1);
            if (v6)
            {
                v7 = v6->Data1.Entity;
                v7->Position.x = v3->Position.x;
                v8 = v13[v5];
                v7->Position.y = v3->Position.y;
                v9 = v3->Position.z;
                v7->field_2 = v11;
                v7->Position.z = v9;
                a1->field_4C = (NJS_OBJECT*)v8;
               // v7->timer = (int*)v8;
                v7->Index = 2;
                v12 = rand();
                v7->Scale.x = (double)v12 * 0.000030517578 + (double)v12 * 0.000030517578;
                if (v3->Index == 1)
                {
                    v7->Index = 1;
                    v7->Scale.z = (float)timer;
                }
            }
            v11 = ++v5;
        }         while (v5 < 13);
        v2 = a1;
    }
    v10 = v3->Index;
    ++v3->field_6;
    if (v10 == 2 || (AddToCollisionList(a1), (unsigned __int16)v3->field_6 > timer))
    {
        //PlaySound(95, 0, 0, 0);
        sub_46C150(v2);
    }
}

void LoadBreakGlass(ObjectMaster* obj) {
    //BreakGlass(obj, 60);
}

void __cdecl SH_GlassDisplay(ObjectMaster* a2)
{
    EntityData1* v1 = a2->Data1.Entity;
    njSetTexture(&highwayObj_TEXLIST);
    njPushMatrix(0);
    njTranslate(0, v1->Position.x, v1->Position.y, v1->Position.z);
    njRotateX(0, v1->Rotation.x);
    njRotateY(0, v1->Rotation.y);
    njRotateZ(0, v1->Rotation.z);

    DrawObject(SH_Glass->getmodel());
    njPopMatrixEx();
}

void __cdecl SH_GlassMain(ObjectMaster* a1)
{
    EntityData1* v1; // esi
    __int16 v2; // ax
    Angle v3; // edi
    CollisionInfo* v4; // edx
    __int16 v5; // ax
    int v6; // [esp-10h] [ebp-1Ch]

    v1 = a1->Data1.Entity;
    if (!ClipSetObject(a1))
    {

        v2 = v1->Status;
        v3 = v1->Rotation.z;
        if ((v2 & 0x20) != 0 && !v3 || (v2 & 0x10) != 0 && v3)
        {
            v1->Status = v2 & 0xFFCF;
            a1->MainSub = LoadBreakGlass;
            v1->Index = 2;
            v6 = 95;
        LABEL_13:
            v1->field_6 = 0;
            //PlaySound(v6, 0, 0, 0);
            goto LABEL_14;
        }
        v4 = v1->Collision;
        v5 = v4->Flag;
        if ((v5 & 1) != 0 || (v1->Status & 0x10) != 0)
        {
            v4->Flag = v5 & 0xFFFE;
            (v1->Status) &= 0xCFu;
            if (++v1->field_6 > 5u)
            {
                a1->MainSub = LoadBreakGlass;
                v1->Index = 1;
                v6 = 94;
                goto LABEL_13;
            }
        }
        else
        {
            v1->field_6 = 0;
        }
    LABEL_14:
        AddToCollisionList(a1);
    }
}


void __cdecl OGlass(ObjectMaster* obj)
{
    if (!ClipSetObject(obj))
    {
        InitCollision(obj, &Col_Glass, 1, 4u);
        obj->MainSub = SH_GlassMain;
        obj->DisplaySub = SH_GlassDisplay;
    }
}

void LoadSHGlass() {
    SH_Glass = LoadMDL("SH-glass", ModelFormat_Chunk);

    for (Uint8 i = 0; i < LengthOfArray(SH_GlassBroken); i++) {
        std::string str = "sh-GlassBroken" + std::to_string(i);
        SH_GlassBroken[i] = LoadMDL(str.c_str(), ModelFormat_Chunk);
    }
}