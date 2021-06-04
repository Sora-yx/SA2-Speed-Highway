#include "pch.h"
#include "objects.h"
#include "sh-bell.h"

static CollisionData Col_Bell01[] = {
	{ 0, (CollisionShapes)0x6, 0x77, 0, 0, {0.0, -30.0, 0.0}, 17.0, 4.0, 0.0, 0.0, 0, 0, 0 },
	{ 0, CollisionShape_Cyl1, 0x77, 0, 0, {0.0, -48.0, 0}, 19.0, 5.0, 0.0, 0.0, 0, 0, 0 },
};

static CollisionData Col_Bell02 = { 0, (CollisionShapes)0x6, 0x10, 0xEC, 0, {0.0, -60.0, 0.0}, 8.0, 5.0, 0.0, 0.0, 0, 0, 0 };

ModelInfo* SH_Bell[2];

void __cdecl Bell_Child(ObjectMaster* obj)
{
	ObjectMaster* v1; // ebx
	EntityData1* v2; // ebp
	EntityData1* v3; // esi
	EntityData1* v4; // edi
	Angle v5; // eax
	Angle v6; // eax
	Angle v7; // eax
	Angle v8; // ebx
	unsigned __int64 v9; // rax
	int v10; // eax
	int v11; // eax
	Angle v12; // ecx

	v1 = obj;
	v2 = MainCharObj1[0];
	v3 = obj->Data1.Entity;
	v4 = obj->Parent->Data1.Entity;
	v5 = v3->Rotation.z;
	if (v5)
	{
		njRotateZ(0, (unsigned __int16)v5);
	}
	v6 = v3->Rotation.x;
	if (v6)
	{
		njRotateX(0, (unsigned __int16)v6);
	}
	v7 = v3->Rotation.y;
	if (v7)
	{
		njRotateY(0, (unsigned __int16)v7);
	}

	if ((v3->Collision->Flag & 1) == 0 || (v4->Status & 0x100) != 0)
	{
		if ((v4->Status & 0x200) != 0)
		{
			v10 = v4->Index & 0x3FF00;
			if (v10)
			{
				v11 = v10 & 0xFF00;
				if (v11 == 49152 || v11 == 0x4000)
				{
					PrintDebug("BELL CHILDD");
					//PlaySound4(93, 0, 0, 64, v4->Position.x, v4->Position.y, v4->Position.z);
				}
				v12 = v4->Index - 1024;
				v4->Index = v12;
				v3->Rotation.x = (unsigned __int64)(njSin(v12) * *(float*)&v3->field_6 * 3094.0);
				v3->Rotation.z = (unsigned __int64)(njSin(v4->Index) * v3->Index * 3094.0);
			}
			else
			{
				v4->Status &= 0xFDFFu;
			}
		}

		AddToCollisionList(obj);
		ObjectSetupInput(v3, nullptr);
	}
	else
	{
		/*GetPlayerRunningSpeed(0, (float*)&obj);
		if (*(float*)&obj >= 1.0)
		{
			v8 = (unsigned __int16)v2->Rotation.y;
			*(float*)&v3->timer = njSin(v8);
			v3->LoopData.Single = -njCos(v8);
			if (*(float*)&obj > 3.0)
			{
				*(float*)&obj = 3.0;
			}
			v9 = (unsigned __int64)*(float*)&obj;
			v4->Status |= 3u;
			v4->Index = (DWORD)v9 << 16;
		}*/
	}
}

void Bell_Display(ObjectMaster* obj) {
	EntityData1* v3 = obj->Data1.Entity;
	Angle v4;

	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrixEx();
	njTranslateV(0, &v3->Position);
	njPushMatrixEx();
	v4 = v3->Rotation.y;
	if (v4)
	{
		njRotateY(0, (unsigned __int16)v4);
	}

	DrawObject(SH_Bell[0]->getmodel());
	njPopMatrixEx();
	DrawObject(SH_Bell[1]->getmodel());
	njPopMatrixEx();
}

void Bell_Main(ObjectMaster* obj) {

	EntityData1* v2; // ebx
	EntityData1* v3; // esi
	Angle v4; // eax
	CollisionInfo* v5; // eax
	char v6; // al
	double v7; // st7
	CollisionInfo* v8; // eax
	float y; // [esp+0h] [ebp-1Ch]

	v3 = obj->Data1.Entity;

	v2 = obj->Child->Data1.Entity;

	v5 = v3->Collision;

	if ((v5->Flag & 1) == 0 || (v3->Status & 0x100) != 0)
	{
		if ((v3->Status & 0x300) == 256)
		{
			if (v5)
			{
				if ((v5->Flag & 1) == 0)
				{
					if (v2)
					{
						v8 = v2->Collision;
						if (v8)
						{
							if ((v8->Flag & 1) == 0 && !v3->Index)
							{
								v3->Status &= 0xFEFFu;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		v6 = v3->Action;
		if (v3->Action)
		{
			v7 = v3->Position.y - 70.0;
			v3->Action = v6 - 1;
			y = v7;

		}
		//PlaySound(93, 0, 0, 0);
		PrintDebug("bellllllll");
		v3->Status |= 1u;
	}

	AddToCollisionList(obj);
	ObjectSetupInput(v3, nullptr);
}

void __cdecl OHwBell(ObjectMaster* obj)
{
	EntityData1* v1; // esi
	ObjectMaster* v2; // eax
	EntityData1* v3; // ecx

	v1 = obj->Data1.Entity;
	v1->Rotation.z = 0;
	v1->Rotation.x = 0;
	InitCollision(obj, Col_Bell01, 2, 4u);

	v2 = LoadChildObject((LoadObj)(LoadObj_UnknownA | LoadObj_Data1 | LoadObj_Data2), Bell_Child, obj);
	v3 = v2->Data1.Entity;
	v3->Position = v1->Position;
	v3->Rotation.z = 0;
	v3->Rotation.x = 0;
	v3->Rotation.y = v1->Rotation.y;
	InitCollision(v2, &Col_Bell02, 1, 4u);

	v1->Status &= 0xFCu;
	v1->Action = 5;
	obj->MainSub = Bell_Main;
	obj->DisplaySub = Bell_Display;
	obj->DeleteSub = j_DeleteChildObjects;
}