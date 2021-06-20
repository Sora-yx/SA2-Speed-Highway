#include "pch.h"

static ModelInfo* SH_Gclight;
NJS_SPRITE OGclight_Sprite;
NJS_TEXANIM OGclight_anim = { 0x20, 0x20, 0x10, 0x10, 0, 0, 0xFF, 0xFF, 0, 0 };
CollisionData GclightCol = { 0, (CollisionShapes)6, 0x77, 0, 0, {0.0, 5.0, 0.0}, 5.0, 3.0, 0.0, 0.0, 0, 0, 0 };

static NJS_TEXNAME gcLightTex = { (char*)"st_cornerlight", 0, 0 };
static NJS_TEXLIST gcLightTexlist = { (gcLightTex, 0) };

void __cdecl Draw_OClight(ObjectMaster* a1)
{
	EntityData1* data; // esi
	NJS_VECTOR* pos; // edi
	double ColorIDK; // st7
	CameraInfo* camData; // eax
	Angle camRotY; // ecx
	Angle v12; // ecx
	float XDist; // [esp+0h] [ebp-30h]
	float YDist; // [esp+4h] [ebp-2Ch]
	float ZDist; // [esp+8h] [ebp-28h]
	Vector3 a2; // [esp+14h] [ebp-1Ch] BYREF
	NJS_ARGB a1a; // [esp+20h] [ebp-10h] BYREF

	data = a1->Data1.Entity;
	pos = &data->Position;
	a2.x = 0.0;
	a2.y = 10.0;
	a2.z = 0.0;

	if (ClipSetObject(a1))
		return;

	njSetTexture(&highwayObj_TEXLIST);
	njPushMatrix(0);
	njTranslate(0, pos->x, data->Position.y, data->Position.z);
	njRotateZXY(&data->Rotation);
	DrawObject(SH_Gclight->getmodel());
	njPopMatrix(1u);
	a1a.a = 1.0;
	ColorIDK = njSin((unsigned __int64)((double)(unsigned __int16)data->field_6 * 65536.0 * 0.002777777777777778)) * 0.80000001;
	if (ColorIDK < 0.0)
	{
		ColorIDK = -ColorIDK;
	}
	a1a.b = ColorIDK;
	a1a.g = ColorIDK;
	a1a.r = ColorIDK;
	SetMaterialColor(a1a.a, a1a.r, a1a.g, a1a.b);

	njPushMatrix(_nj_unit_matrix_);
	njRotateZXY(&data->Rotation);

	njGetTranslation(CURRENT_MATRIX, &a2);
	njPopMatrix(1u);

	njSetTexture(&gcLightTexlist);
	njPushMatrix(0);
	ZDist = a2.z + data->Position.z;
	YDist = a2.y + data->Position.y;
	XDist = a2.x + pos->x;
	njTranslate(0, XDist, YDist, ZDist);
	camData = &CameraData;
	camRotY = CameraData.Rotation.y;
	if (camRotY)
	{
		njRotateY(0, (unsigned __int16)camRotY);
	}
	v12 = camData->Rotation.x;
	if (v12)
	{
		njRotateX(0, (unsigned __int16)v12);
	}

	/*njDrawSprite3D_Queue(
		&OGclight_Sprite,
		0,
		NJD_SPRITE_ALPHA | NJD_SPRITE_VFLIP | NJD_SPRITE_COLOR,
		QueuedModelFlagsB_SomeTextureThing);*/
	//njDrawSprite2D(&OGclight_Sprite, 0, 0, NJD_SPRITE_ALPHA | NJD_SPRITE_VFLIP | NJD_SPRITE_COLOR);

	njPopMatrix(1u);
	ResetMaterialColorOffset();
}

void gclight_spriteInit()
{
	OGclight_Sprite.tlist = &gcLightTexlist;
	OGclight_Sprite.tanim = &OGclight_anim;
	OGclight_Sprite.sx = 0.40000001;
	OGclight_Sprite.sy = 0.40000001;
	OGclight_Sprite.p.x = 0.0;
	OGclight_Sprite.p.y = 0.0;
	OGclight_Sprite.p.z = 0.0;
}

void __cdecl GClight_main(ObjectMaster* obj)
{
	EntityData1* data; // edi
	CollisionInfo* getCol; // eax
	unsigned __int16 getFlag; // cx

	data = obj->Data1.Entity;
	if (!ClipSetObject(obj))
	{
		if (data->Action)
		{
			if (data->Action == 1)
			{
				data->field_6 += 4;
				getCol = data->Collision;
				getFlag = getCol->Flag;
				if ((getFlag & 1) != 0)
				{
					getCol->Flag = getFlag & 0xFFFE;
				}
				AddToCollisionList(obj);
				sub_49CE60(data, 0);

			}
		}
		else
		{
			obj->field_4C = SH_Gclight->getmodel();

			InitCollision(obj, &GclightCol, 1, 4u);
			data->Collision->Range = 11.0F;
			gclight_spriteInit();
			obj->DisplaySub = Draw_OClight;
			data->Action = 1;
		}
	}
}


void __cdecl OGclight(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	obj->field_4C = GClight_main;
	obj->DeleteSub = j_DeleteChildObjects;
	obj->MainSub = SH_GlobalMainWithCalcRot;
}

void LoadClightModel() {
	SH_Gclight = LoadMDL("SH-Gclight", ModelFormat_Chunk);
	gcLightTexlist.textures = &highwayObj2_TEXLIST.textures[24];
	return;
}

void FreeClightModel() {
	FreeMDL(SH_Gclight);
}