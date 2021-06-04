#include "pch.h"
#include "objects.h"
#include "sh-jammer.h"

static NJS_TEXNAME JammerTexName[] = {
	{ (char*)"cone04", 0, 0 },
	{ (char*)"light2", 0, 0 },
	{ (char*)"nen_01", 0, 0 },
	{ (char*)"ref_crome", 0, 0 },
	{ (char*)"st_slight06", 0, 0 }
};

static NJS_TEXNAME JammerTexName2[] = {
	{ (char*)"cone04", 0, 0 },
	{ (char*)"light2", 0, 0 },
	{ (char*)"nen_02", 0, 0 },
	{ (char*)"ref_crome", 0, 0 },
	{ (char*)"st_slight06", 0, 0 }
};

static NJS_TEXLIST JammerTexlist = { arrayptrandlength(JammerTexName, Uint32) };
static NJS_TEXLIST JammerTexlist2 = { arrayptrandlength(JammerTexName2, Uint32) };

static ModelInfo* SH_Jammer;

void JammerChangeTex(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	if (++data->field_6 > 0x19u)
	{
		data->field_6 = 0;

		if (data->NextAction)
		{
			data->NextAction -= 1;
			obj->field_4C = &JammerTexlist;
		}
		else
		{
			data->NextAction = 1;
			obj->field_4C = &JammerTexlist2;
		}
	}
}

void __cdecl OJamerDisplay(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	njSetTexture((NJS_TEXLIST*)obj->field_4C);
	njPushMatrixEx();
	njTranslateEx(&data->Position);
	njRotateZXY(&data->Rotation);
	DrawObject(SH_Jammer->getmodel());
	njPopMatrixEx();
}

void ObjectJammer(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	if (!ClipSetObject(obj))
	{
		if (data->Action == 1)
		{
			if (IsPlayerInsideSphere(&data->Position, 33.0f))
			{
				data->Status | 0x100;
			}
			else {
				data->Status & 0xFEFF;
			}

			JammerChangeTex(obj);
		}
		else
		{
			data->Action = 1;
			obj->field_4C = &JammerTexlist;
			obj->DisplaySub = OJamerDisplay;
		}
	}
}

void LoadAssets_Jammer()
{
	SH_Jammer = LoadMDL("SH-Jammer", ModelFormat_Chunk);

	JammerTexlist.textures[0] = highwayObj2_TEXLIST.textures[34];
	JammerTexlist.textures[1] = highwayObj2_TEXLIST.textures[35];
	JammerTexlist.textures[2] = highwayObj2_TEXLIST.textures[31];
	JammerTexlist.textures[3] = highwayObj2_TEXLIST.textures[32];
	JammerTexlist.textures[4] = highwayObj2_TEXLIST.textures[33];

	JammerTexlist2.textures[0] = highwayObj2_TEXLIST.textures[34];
	JammerTexlist2.textures[1] = highwayObj2_TEXLIST.textures[35];
	JammerTexlist2.textures[2] = highwayObj2_TEXLIST.textures[36];
	JammerTexlist2.textures[3] = highwayObj2_TEXLIST.textures[32];
	JammerTexlist2.textures[4] = highwayObj2_TEXLIST.textures[33];
}

void FreeAssets_Jammer()
{
	FreeMDL(SH_Jammer);
}