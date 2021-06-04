#include "pch.h"
#include "sh-cone.h"

ModelInfo* SH_Cone[2];

static CollisionData Col_Cone = { 0x300, (CollisionShapes)0x6, 0x20, 0xE0, 0, { 0.0f, 2.0f, 0.0f }, 3.0f, 1.5f, 0.0f, 0.0f, 0, 0, 0 };

void __cdecl Cone_Display(ObjectMaster* a2)
{
	EntityData1* data = a2->Data1.Entity;
	
	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrix(0);
	njTranslateEx(&data->Position);
	njRotateZXY(&data->Rotation);

	if (data->Action)
	{
		DrawObject(SH_Cone[1]->getmodel());
	}
	else
	{
		DrawObject(SH_Cone[0]->getmodel());
	}

	njPopMatrixEx();
}

void __cdecl Cone_Main(ObjectMaster* a1)
{
	ObjectMaster* v1; // ebx
	EntityData1* v2; // esi
	NJS_POINT3* v3; // edi
	Angle v4; // edi
	double v5; // st7
	ObjectMaster* v6; // ecx
	Rotation a4; // [esp+Ch] [ebp-Ch] BYREF
	Float v13 = 0;

	v1 = a1;
	v2 = a1->Data1.Entity;
	v3 = &MainCharObj1[0]->Position;
	if (ClipSetObject(a1))
	{
		if (v2->Scale.y != 0.0 || v2->Scale.x != 0.0)
		{
			UpdateSetDateAndDelete(v1);
		}
	}
	else
	{
		if (v2->Scale.y == 0.0 && v2->Scale.x == 0.0)
		{
			if ((v2->Collision->Flag & 1) != 0)
			{
				GetPlayerRunningSpeed(0, v13);
				if (v13) {
					v2->Scale.x = v13 * 1.5;
					v2->Scale.y = v13 * 0.66666669;
				}
				v2->field_6 = (unsigned __int16)(-16384
					- (unsigned __int64)(atan2(
						v2->Position.z - v3->z,
						v2->Position.x - v3->x)
						* 65536.0
						* -0.1591549762031479));
				//PlaySound(118, 0, 0, 0);
			}
		}
		else
		{
			v4 = v2->field_6;
			v2->Position.x = v2->Position.x - njSin(v4) * v2->Scale.x;
			v2->Position.y = v2->Scale.y + v2->Position.y;
			v2->Position.z = njCos(v4) * v2->Scale.x + v2->Position.z;

			v5 = v2->Scale.x - 0.5;
			v2->Scale.x = v5;
			if (v5 < 0.0)
			{
				v2->Scale.x = 0.0;
			}
			v6 = a1;
			if (v2->Scale.y >= -1.0)
			{
				v2->Scale.y = 0.0;
			}
			else
			{
				v2->Scale.y = v2->Scale.y * -0.5;
			}

		}

		AddToCollisionList(a1);
		ObjectSetupInput(v2, 0);
	}
}

void __cdecl OCone2(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	data->Action = 1;
	data->Scale.x = 0.0;
	data->Scale.y = 0.0;
	InitCollision(obj, &Col_Cone, 1, 4u);
	obj->MainSub = (ObjectFuncPtr)Cone_Main;
	obj->DisplaySub = (ObjectFuncPtr)Cone_Display;
}

void __cdecl OCone1(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	data->Action = 0;
	data->Scale.x = 0.0;
	data->Scale.y = 0.0;
	InitCollision(obj, &Col_Cone, 1, 4u);
	obj->MainSub = (ObjectFuncPtr)Cone_Main;
	obj->DisplaySub = (ObjectFuncPtr)Cone_Display;
}