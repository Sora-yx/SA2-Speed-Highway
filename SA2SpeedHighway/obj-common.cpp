#include "pch.h"

static Trampoline* goalringt;
static Trampoline* itembox_t;
static Trampoline* airbox_t;
static Trampoline* RingLinear_t;


static void __cdecl RingsLinear_r(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	if (data->Action == 0)
	{
		if (isSADXLevel())
		{
			if (data->Scale.z >= 1.0f)
			{
				RingCircleMain(obj);
				return;
			}

			//in sadx scale X is number of rings and scale Y is distance between rings.
			data->Scale.z = data->Scale.x + 1;
			data->Scale.x = data->Scale.y / 2.0f;
			data->Scale.y = 0;
		}
	}

	ObjectFunc(origin, RingLinear_t->Target());
	origin(obj);
}

static void __cdecl GoalRing_r(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	if (data->Action == 0)
	{
		if (isSADXLevel())
		{
			data->Position.y += 31.0f;
		}
	}

	ObjectFunc(origin, goalringt->Target());
	origin(obj);
}

// SADX uses different itembox ID than SA2
static unsigned int FixItemBoxID(unsigned int id)
{
	switch (id)
	{
	case 1:
		return 10;
	case 2:
		return 1;
	case 6:
		return 2;
	case 7:
		return 6;
	}

	return id;
}

static void __cdecl ItemBox_r(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	if (data->Action == 0)
	{
		if (isSADXLevel())
		{
			if ((unsigned __int64)data->Scale.x >= 9)
			{
				data->Scale.x = 0.0;
			}

			data->Scale.x = FixItemBoxID((unsigned int)data->Scale.x);
		}
	}

	ObjectFunc(origin, itembox_t->Target());
	origin(obj);
}

static void __cdecl AirBox_r(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	if (data->Action == 0)
	{
		if (isSADXLevel())
		{
			if ((unsigned __int64)data->Scale.x >= 9)
			{
				data->Scale.x = 0.0;
			}

			data->Scale.x = FixItemBoxID((unsigned int)data->Scale.x);
		}
	}

	ObjectFunc(origin, airbox_t->Target());
	origin(obj);
}


void Objects_Init() {
	//SADX Fixes
	goalringt = new Trampoline((int)GoalRing_Main, (int)GoalRing_Main + 0x6, GoalRing_r);
	itembox_t = new Trampoline((int)ItemBox_Main, (int)ItemBox_Main + 0x5, ItemBox_r);
	airbox_t = new Trampoline((int)ItemBoxAir_Main, (int)ItemBoxAir_Main + 0x5, AirBox_r);
	RingLinear_t = new Trampoline((int)RingLinearMain, (int)RingLinearMain + 0x6, RingsLinear_r);
}