#include "pch.h"
#include "PhysicsFunction.h"

//SA2 Functions

static const void* const SCheckJumpPtr = (void*)0x721C00;
static inline signed int Sonic_CheckJumpASM(EntityData1* data, CharObj2Base* a2, SonicCharObj2* a3)
{
    signed int result;
    __asm
    {
        push[a3]
        push[a2]
        mov eax, data // a1

        // Call your __cdecl function here:
        call SCheckJumpPtr

        add esp, 8 // a3
        mov result, eax
    }
}

signed int Sonic_CheckJump(EntityData1* data, CharObj2Base* a2, SonicCharObj2* a3) {
    return Sonic_CheckJumpASM(data, a2, a3);
}

static const void* const PGetAccelAirPtr = (void*)0x45D770;
static inline void PlayerGetAccelerationAirASM(EntityData1* a1, CharObj2Base* co2, EntityData2* data2)
{
    __asm
    {
        push[data2]
        mov eax, [co2]
        mov ecx, a1 // a1

        // Call your __cdecl function here:
        call PGetAccelAirPtr

        add esp, 4 // a3
    }
}

void PlayerGetAccelerationAir(EntityData1* a1, CharObj2Base* co2, EntityData2* data2) {
    return PlayerGetAccelerationAirASM(a1, co2, data2);
}

static const void* const PResetAnglePtr = (void*)0x460260;
static inline void PlayerResetAngleASM(EntityData1* a1, CharObj2Base* co2)
{
    __asm
    {
        mov ebx, [co2]
        mov eax, [a1] // a1
        call PResetAnglePtr
    }
}

void PlayerResetAngle(EntityData1* a1, CharObj2Base* co2)
{
    return PlayerResetAngleASM(a1, co2);
}


static const void* const PGetSpeedPtr = (void*)0x460860;
static inline void PlayerGetSpeedASM(EntityData1* a1, CharObj2Base* co2, EntityData2* data2)
{
    __asm
    {
        push[data2] // a3
        mov ebx, co2 // a2
        mov eax, a1 // a1

        // Call your __cdecl function here:
        call PGetSpeedPtr

        add esp, 4 // a3
    }
}

void PlayerGetSpeed(EntityData1* a1, CharObj2Base* co2, EntityData2* data2)
{
    PlayerGetSpeedASM(a1, co2, data2);
}

static const void* const PSetPositionptr = (void*)0x4616E0;
static inline int PSetPositionASM(EntityData1* a1, EntityData2* a2, CharObj2Base* a3)
{
    int result;
    __asm
    {
        push[a3]
        push[a2]
        mov eax, [a1]
        call PSetPositionptr
        add esp, 8
        mov result, eax
    }
    return result;
}

int PlayerSetPosition(EntityData1* a1, EntityData2* a2, CharObj2Base* a3)
{
    return PSetPositionASM(a1, a2, a3);
}

static const void* const sub_469050Ptr = (void*)0x469050;
static inline void PResetPositionASM(EntityData1* a1, EntityData2* a2, CharObj2Base* a3)
{
    __asm
    {
        push[a3] // a3
        mov ebx, a2 // a2
        mov eax, a1 // a1
        call sub_469050Ptr
        add esp, 4 // a2
    }
}

void PlayerResetPosition(EntityData1* a1, EntityData2* a2, CharObj2Base* a3) {
    PResetPositionASM(a1, a2, a3);
}


static const void* const PadAdjustYS = (void*)0x460610;
static inline void PAdjustAngleYS(__int16 ax0, EntityData1* a1, CharObj2Base* a3)
{
    __asm
    {
        push[a3]
        push[a1]
        mov ax, [ax0]
        call PadAdjustYS
        add esp, 8
    }
}

void __cdecl PAdjustAngleYQ(EntityData1* twp, CharObj2Base* pwp, int angy)
{
    float spd_y; // r10
    float spd_z; // r9
    float v8; // r7
    float v9; // r6
    NJS_POINT3 v10; // [sp+50h] [-30h] BYREF

    spd_y = pwp->Speed.y;
    spd_z = pwp->Speed.z;
    v10.x = pwp->Speed.x;
    v10.y = spd_y;
    v10.z = spd_z;
    PConvertVector_P2G(twp, &v10);
    twp->Rotation.y = AdjustAngle(twp->Rotation.y, angy, 0x2000);
    PConvertVector_G2P(twp, &v10);
    v8 = v10.y;
    v9 = v10.z;
    pwp->Speed.x = v10.x;
    pwp->Speed.y = v8;
    pwp->Speed.z = v9;
}

bool CheckPlayerFall(CharObj2Base* status, EntityData1* _entity)
{
    __int16 v2; // ax

    v2 = _entity->Status;
    if ((v2 & (Status_OnObjectColli | Status_Ground)) != 0)
    {
        return 0;
    }
    if ((v2 & Status_Ball) != 0)
    {
        _entity->Action = 8;
        return 1;
    }

    _entity->Action = Action_Fall;
    status->AnimInfo.Next = 68;
    return 1;
}


#pragma optimize("", off)
//SADX Functions
void __fastcall PGetAccelerationForBuilding(EntityData1* twp, EntityData2_R* mwp, CharObj2Base* pwp)
{
    float v3; // r9
    float v5; // r8
    int v8; // r6
    double v9; // fp29
    double v10; // fp10
    int v11; // r3
    __int16 v12; // r11
    double v13; // fp11
    double v14; // fp0
    double v15; // fp7
    double v16; // fp31
    int v17; // r9
    int v18; // r10
    __int64 v19; // r9
    double v20; // fp2
    double v21; // fp1
    int v22; // r10
    int v23; // r31
    int v24; // r3
    double v25; // fp11
    double v26; // fp12
    double v27; // fp0
    double v28; // fp13
    double v29; // fp0
    double v30; // fp0
    double v31; // fp13
    double v32; // fp0
    double v33; // fp13
    float v34; // r10
    float v35; // r9
    NJS_POINT3 v36; // [sp+58h] [-58h] BYREF

    v3 = mwp->acc.y;
    v5 = mwp->acc.z;
    v8 = twp->Status & 0x4000;
    v36.x = mwp->acc.x;
    v9 = 0.0;
    v36.y = v3;
    v36.z = v5;
    if (!v8)
    {
        v10 = (float)(v36.x - pwp->PhysData.Weight);
        v36.y = v36.y - pwp->PhysData.Weight;
        v36.x = v10;
        PConvertVector_G2P(twp, &v36);
        v11 = GetAnalog(twp, pwp, 0, 0);
        v12 = twp->Status;
        if ((v12 & 1) != 0 || pwp->Speed.x <= (double)pwp->PhysData.SpeedMaxH)
        {
            if ((twp->Status & 0x100) == 0
                || pwp->Speed.x <= (double)(float)(pwp->PhysData.SpeedMaxH * (float)1.2))
            {
                if ((twp->Status & 0x100) != 0 || pwp->Speed.x <= (double)pwp->PhysData.SpeedMaxH)
                    goto LABEL_14;

                v14 = (float)(pwp->Speed.x - pwp->PhysData.SpeedMaxH);
            }
            else
            {
                v14 = (float)(pwp->Speed.x - (float)(pwp->PhysData.SpeedMaxH * (float)1.2));
            }
            v13 = (float)((float)((float)v14 * pwp->PhysData.AirResist) + v36.x);
        }
        else
        {
            v13 = (float)((float)(pwp->PhysData.AirDecel * pwp->Speed.x) + v36.x);
        }
        v36.x = v13;
    LABEL_14:
        v15 = (float)((float)(pwp->PhysData.AirResistH * pwp->Speed.z) + v36.z);
        v36.y = (float)(pwp->PhysData.AirResistV * pwp->Speed.y) + v36.y;
        v36.z = v15;
        if ((v12 & 1) != 0 && pwp->Speed.x < (double)pwp->PhysData.SpeedMaxH)
            v16 = pwp->PhysData.RunAccel;
        else
            v16 = (float)(pwp->PhysData.RunAccel * (float)0.30000001);
        mwp->force = v16;
        if (v11)
        {
            v17 = pwp->PlayerNum;
            v18 = Controllers[v17].x1 << 8;
            (v19) = Controllers[v17].y1 << 8;
            (v19) = v18;
            if ((float)((PDS_PERIPHERAL*)&Controllers[0].x1, v18) < 0.0)
                v20 = (float)((float)((PDS_PERIPHERAL*)&Controllers[0].x1, v18) + (float)3072.0);
            else
                v20 = (float)((float)((PDS_PERIPHERAL*)&Controllers[0].x1, v18) - (float)3072.0);
            if ((float)v19 < 0.0)
                v21 = (float)((float)v19 + (float)3072.0);
            else
                v21 = (float)((float)v19 - (float)3072.0);
            v22 = (int)(atan2(v21, v20) * 65536.0 * 0.1591549762031479);
            if (CameraData.Rotation.z < 0x4000)
                v23 = 0x8000 - CameraData.Rotation.y - v22;
            else
                v23 = v22 - CameraData.Rotation.y;
            v24 = SubAngle(v23, 0);
            if (v24 <= 2048)
            {
                if (v24 < -2048)
                    (v23) = (4 * twp->Status) & 0x400 | 0xF800;
            }
            else
            {
                (v23) = (twp->Status & 0x100) == 0 ? 2048 : 1024;
            }
            mwp->ang_aim.y = (unsigned __int16)v23;

            PAdjustAngleYS((unsigned __int16)v23, twp, pwp);
        }
        else
        {
            mwp->ang_aim.y = 0;
            PAdjustAngleYQ(twp, pwp, 0);
        }
        v25 = mwp->frict;
        v26 = v36.y;
        v27 = (float)((float)(mwp->frict * pwp->PhysData.FrictionCap) * v36.y);
        if ((twp->Status & 1) != 0 && v27 > 0.0 && v27 < v16)
        {
            v28 = (float)((float)v16 + v36.x);
            if (v28 > v27)
            {
                mwp->accel = (float)((float)v16 + v36.x) - (float)((float)(mwp->frict * pwp->PhysData.FrictionCap) * v36.y);
                v28 = v27;
            }
        }
        else
        {
            v28 = (float)((float)v16 + v36.x);
        }
        v29 = pwp->Speed.z;
        v36.x = v28;
        if (v29 == 0.0)
        {
            v30 = (float)((float)((float)v25 * pwp->PhysData.FrictionCap) * (float)v26);
            if (v36.z < v30 && v36.z > -v30)
                v36.z = 0.0;
        }
        else
        {
            if (v26 >= 0.0)
                v31 = 0.0;
            else
                v31 = (float)((float)(pwp->PhysData.GroundFrictionH * (float)v25) * (float)v26);
            v32 = v36.z;
            if (v36.z <= 0.0)
            {
                if (v32 < 0.0)
                    v9 = v31;
            }
            else
            {
                v9 = -v31;
            }
            v33 = (float)(v36.z + (float)v9);
            if (v32 != 0.0 && v9 != 0.0 && (float)((float)(v36.z + (float)v9) * v36.z) < 0.0)
                v33 = 0.0;
            v36.z = v33;
        }
        v34 = v36.y;
        v35 = v36.z;
        pwp->Acceleration.x = v36.x;
        pwp->Acceleration.y = v34;
        pwp->Acceleration.z = v35;
    }
}

void __cdecl PResetAngleForBuilding(EntityData1* a1, EntityData2_R* _18, CharObj2Base* a3)
{
    double v3; // st7
    float v4; // edx
    int v5; // eax
    float v6; // ecx
    float v7; // edx
    __int16 v8; // [esp-24h] [ebp-34h]
    Vector3 a2; // [esp+4h] [ebp-Ch] BYREF

    v3 = a3->PhysData.DashSpeed;
    a2.x = a3->Speed.x;
    v4 = a3->Speed.y;
    a2.z = a3->Speed.z;
    a2.y = v4;

    double result = a2.z * a2.z + v4 * v4 + a2.x * a2.x;

    if (v3 * v3 >= result)
    {
        PConvertVector_P2G(a1, &a2);
        v5 = BAMS_SubWrap(a1->Rotation.x, 0, 2048);
        v8 = a1->Rotation.z;
        a1->Rotation.x = v5;
        a1->Rotation.z = BAMS_SubWrap(v8, 0xC000u, 2048);
        PConvertVector_G2P(a1, &a2);
        v6 = a2.y;
        v7 = a2.z;
        a3->Speed.x = a2.x;
        a3->Speed.y = v6;
        a3->Speed.z = v7;
    }
}

void __cdecl PResetPositionForBuilding(EntityData1* a1, EntityData2_R* a2, CharObj2Base* a3)
{
    float v3; // edx
    float v4; // eax
    double v5; // st7
    double v6; // st6
    double v7; // st7
    Vector3 a2a; // [esp+4h] [ebp-Ch] BYREF

    v3 = a2->spd.y;
    v4 = a2->spd.z;
    a2a.x = a2->spd.x;
    a2a.y = v3;
    a2a.z = v4;
    PConvertVector_G2P(a1, &a2a);
    if (a2a.x <= 0.001 && a2a.x >= -0.001)
    {
        a2a.x = 0.0;
    }
    if (a2a.y <= 0.001 && a2a.y >= -0.001)
    {
        a2a.y = 0.0;
    }
    if (a2a.z <= 0.001 && a2a.z >= -0.001)
    {
        a2a.z = 0.0;
    }
    a3->Speed = a2a;
    if ((a1->Status & 1) != 0)
    {
        a3->Speed.y = 0.0;
    }
    if (a1->Position.y <= -18400.0)
    {
        if (a1->Position.y <= -18845.0)
        {
            if (a1->Position.y <= -19000.0)
            {
                return;
            }
            if (a1->Position.z < -110.0)
            {
                a1->Position.z = -110.0;
            }
            if (a1->Position.z > 110.0)
            {
                a1->Position.z = 110.0;
            }
            if (a1->Position.x < 115.0)
            {
                a1->Position.x = 115.0;
            }
        }
        else
        {
            v5 = -18400.0 - a1->Position.y;
            v6 = 0.11235955 * v5 + 160.0;
            if (-v6 > a1->Position.z)
            {
                a1->Position.z = -v6;
            }
            if (v6 < a1->Position.z)
            {
                a1->Position.z = v6;
            }
            v7 = v5 * 0.31460676 - 20.0;
            if (v7 > a1->Position.x)
            {
                a1->Position.x = v7;
            }
        }
    }
    else
    {
        if (a1->Position.z < -160.0)
        {
            a1->Position.z = -160.0;
        }
        if (a1->Position.z > 160.0)
        {
            a1->Position.z = 160.0;
        }
        if (a1->Position.x < -20.0)
        {
            a1->Position.x = -20.0;
        }
    }
    if (a1->Position.x > 300.0)
    {
        a1->Position.x = 300.0;
    }
}


int PSetPositionForBuilding(EntityData1* a1, EntityData2_R* a2, CharObj2Base* a3)
{
    CollisionInfo* v4; // eax
    unsigned __int16 v5; // cx
    EntityData2_R* v6; // ebx
    float v7; // eax
    float v8; // edx
    CharObj2Base* v9; // ebp
    __int16 v10; // ax
    csts* v11; // edi
    Angle v12; // eax
    Angle v13; // eax
    int v14; // eax
    double v15; // st7
    int v16; // eax
    CharObj2Base* v17; // edx
    unsigned __int64 v18; // rax
    __int16 v19; // bx
    unsigned __int64 v20; // rax
    int v21; // ebp
    int v22; // ebx
    int v23; // eax
    Angle v24; // edx
    int v25; // eax
    ObjectMaster* v26; // eax
    unsigned __int8 v28; // c0
    unsigned __int8 v29; // c3
    float v30; // eax
    float v31; // edx
    double v32; // st7
    float v33; // edx
    float v34; // ecx
    int v36; // [esp+10h] [ebp-4Ch]
    int v37; // [esp+14h] [ebp-48h]
    char v38; // [esp+18h] [ebp-44h]
    int v39; // [esp+1Ch] [ebp-40h]
    int v40; // [esp+20h] [ebp-3Ch]
    int v41; // [esp+24h] [ebp-38h]
    int v42; // [esp+28h] [ebp-34h]
    Vector3 a2a; // [esp+2Ch] [ebp-30h] BYREF
    Vector3 a3a; // [esp+38h] [ebp-24h] BYREF
    Vector3 a1a; // [esp+44h] [ebp-18h] BYREF
    Vector3 v1; // [esp+50h] [ebp-Ch] BYREF
    char v47; // [esp+60h] [ebp+4h]

    v4 = a1->Collision;
    v5 = v4->Flag;
    v36 = 0;
    if ((v5 & 0x10) != 0
        && (a1->Status & 4) == 0
        && (v5 & 4) != 0
        && (v4->CollidingObject->CollisionArray[v4->hit_num].push & 7) != 0)
    {
        //CCL_GetHitFaceNormal(a1, &v1);
        v6 = a2;
        v7 = a2->spd.x;
        v8 = a2->spd.z;
        a1a.y = a2->spd.y;
        a1a.x = v7;
        a1a.z = v8;
        if (njScalor(&a1a) != 0.0)
        {
            njUnitVector(&a1a);
        }
        if (njInnerProduct(&v1, &a1a) < 0.0)
        {
            a2->spd.x = 0.0;
            a2->spd.z = 0.0;
        }
        v9 = a3;
        if (a3->Speed.x < (double)a3->PhysData.RunSpeed)
        {
            v36 = 1;
        }
        else
        {
            v36 = 2;
        }
    }
    else
    {
        v6 = a2;
        v9 = a3;
    }
    v10 = a1->Status;
    v38 = v10;
    if ((v10 & 2) != 0)
    {
        a1->Status = v10 & 0xFFFC;
        a1->Position.x = v6->spd.x + a1->Position.x;
        a1->Position.z = v6->spd.z + a1->Position.z;
        return v36;
    }
    a1->Status = v10 & 0xFFFC;
    v11 = (csts*)v9->csts;
    v47 = 0;
    njPushMatrixEx();
    njUnitMatrix_();
    //njUnitMatrix(0);
    v12 = a1->Rotation.z;
    if (v12)
    {
        njRotateZ(0, (unsigned __int16)v12);
    }
    v13 = a1->Rotation.x;
    if (v13)
    {
        njRotateX(0, (unsigned __int16)v13);
    }
    if (a1->Rotation.y)
    {
        njRotateY(0, (unsigned __int16)-LOWORD(a1->Rotation.y));
    }
    v14 = a1->Rotation.x;
    a2a.z = 0.0;
    a2a.x = 0.0;
    a2a.y = 1.0;
    v11->angx = v14;
    v11->angz = a1->Rotation.z;
   // njCalcVector(0, &a2a, &v11->tnorm);
    njCalcPoint(&a2a, &v11->tnorm, CURRENT_MATRIX);
    a2a.y = v9->PhysData.Height * 0.5;
    a2a.z = 0.0;
    a2a.x = 0.0;
    //njCalcVector(0, &a2a, &a3a);
    njCalcPoint(&a2a, &a3a, CURRENT_MATRIX);
    v15 = v9->PhysData.Height * 0.5 - v9->PhysData.FloorGrip * 0.5;
    a2a.z = 0.0;
    a2a.x = 0.0;
    a2a.y = v15;
    //njCalcVector(0, &a2a, &v1);
    njCalcPoint(&a2a, &v1, CURRENT_MATRIX);
    njPopMatrix(1u);
    v11->radius = v9->PhysData.Height * 0.5;
    v11->pos.x = v1.x + a1->Position.x;
    v11->pos.y = v1.y + a1->Position.y;
    v11->pos.z = v1.z + a1->Position.z;
    v11->spd = v6->spd;
    CL_ColPolListUpNear(v11);
    v16 = 0;
    v37 = 0;
    if ((__int16)ActiveLandTableColCount <= 0)
    {
        a1->Position.x = a1->Position.x + v6->spd.x;
        a1->Position.y = v6->spd.y + a1->Position.y;
        a1->Position.z = v6->spd.z + a1->Position.z;
        return v36;
    }
    do
    {
        v42 = v16;
        if (CL_ColPolCheckTouchRe(LandColList[v16].Object, v11, false))
        {
            a2a.x = 1.0;
            a2a.z = 0.0;
            a2a.y = 0.0;
            if (VectorAngle(&a2a, &v11->normal2, 0) > 11264)
            {
                a1a.x = -v6->spd.x;
                a1a.y = -v6->spd.y;
                a1a.z = -v6->spd.z;
                if (njScalor(&a1a) != 0.0)
                {
                    njUnitVector(&a1a);
                    if (VectorAngle(&a1a, &v11->normal2, 0) <= 11264)
                    {
                        v36 = 2;
                        if (a3->Speed.x < (double)a3->PhysData.KnockbackSpeed)
                        {
                            v36 = 1;
                        }
                    }
                }
                v32 = v11->pshbk.x;
                v11->pos.x = v11->pshbk.x;
                v33 = v11->pshbk.z;
                v11->pos.y = v11->pshbk.y;
                v11->pos.z = v33;
                a1->Position.x = v32 - a3a.x;
                a1->Position.y = v11->pshbk.y - a3a.y;
                a1->Position.z = v11->pshbk.z - a3a.z;
                v11->spd.x = v11->anaspdh.x;
                v34 = v11->anaspdh.z;
                v11->spd.y = v11->anaspdh.y;
                v11->spd.z = v34;
            }
            else
            {
                v17 = a3;
                if (a3->Speed.y <= 0.0 || (v38 & 3) == 0)
                {
                    v47 = 1;
                    if (v6->spd.x != 0.0 || v6->spd.z != 0.0)
                    {
                        v18 = (unsigned __int64)(asin(v11->normal2.z) * 65536.0 * 0.1591549762031479);
                        v19 = v18;
                        v41 = v18;
                        v20 = (unsigned __int64)(asin(v11->normal2.x) * 65536.0 * -0.1591549762031479);
                        v40 = v20;
                        if (v11->normal2.y < 0.0)
                        {
                            v21 = (unsigned __int16)(0x8000 - v19);
                            v22 = (unsigned __int16)(0x8000 - v20);
                            v39 = BAMS_Subtract(a1->Rotation.x, v21);
                            if (v39 >= BAMS_Subtract(a1->Rotation.z, v22))
                            {
                                v11->angx = v41;
                                v11->angz = v22;
                            }
                            else
                            {
                                v11->angx = v21;
                                v11->angz = v40;
                            }
                        }
                        v23 = BAMS_SubWrap(a1->Rotation.x, v11->angx, 4096);
                        v24 = a1->Rotation.z;
                        a1->Rotation.x = v23;
                        v25 = BAMS_SubWrap(v24, v11->angz, 4096);
                        v6 = a2;
                        v17 = a3;
                        a1->Rotation.z = v25;
                    }
                    v6->ang_aim.x = v11->angx;
                    v6->ang_aim.z = v11->angz;
                    v11->pos.x = v11->anaspdh.x + v11->pshbk.x;
                    v11->pos.y = v11->anaspdh.y + v11->pshbk.y;
                    v11->pos.z = v11->anaspdh.z + v11->pshbk.z;
                    v26 = LandColList[v42].Task;
                    if (v26)
                    {
                        v17->HoldTarget = v26;
                        //PSSGCollisionForceWorkEffect(v17, &a3a, a1, v11);
                    }
                    a2a.x = v11->pos.x - a3a.x;
                    a2a.y = v11->pos.y - a3a.y;
                    a2a.z = v11->pos.z - a3a.z;

                    v28 = a1->Position.y;
                    v29 = a1->Position.z;

                    double posX = (float)(a1->Position.x - a2a.x);

                    float result = (float)(posX * posX) + (float)(v29 - a2a.z) * (float)(v29 - a2a.z) + (float)(v28 - a2a.y) * (float)(a2a.y - a2a.y);

                    if ( result > 0.000099999997)
                    {
                        v30 = a2a.y;
                        a1->Position.x = a2a.x;
                        v31 = a2a.z;
                        a1->Position.y = v30;
                        a1->Position.z = v31;
                    }
                    v11->spd.z = 0.0;
                    v11->spd.y = 0.0;
                    v11->spd.x = 0.0;
                    a1->Status |= 1u;
                }
            }
        }
        v16 = (unsigned __int16)++v37;
    }     while ((unsigned __int16)v37 < (__int16)ActiveLandTableColCount);
    if (v47 != 1)
    {
        a1->Position.x = a1->Position.x + v6->spd.x;
        a1->Position.y = v6->spd.y + a1->Position.y;
        a1->Position.z = v6->spd.z + a1->Position.z;
    }
    return v36;
}
#pragma optimize("", on)