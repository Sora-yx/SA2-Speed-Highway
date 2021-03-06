#pragma once

// Stuff from the game's code, missing from the Mod Loader includes

static const void* const DrawChunkModelPtr = (void*)0x42E6C0;
static inline void DrawChunkModel(NJS_CNK_MODEL* a1)
{
	__asm
	{
		mov eax, [a1]
		call DrawChunkModelPtr
	}
}

static const void* const PConvertVP2GPtr = (void*)0x468E70;
static inline void PConvertVector_P2G(EntityData1* a1, NJS_VECTOR* a2)
{
	__asm
	{
		mov esi, [a2]
		mov edi, [a1] // a1
		call PConvertVP2GPtr
	}
}

static const void* const PConvertVPtr = (void*)0x468DF0;
static inline void PConvertVector_G2P(EntityData1* a1, NJS_VECTOR* a2)
{
	__asm
	{
		mov esi, [a2]
		mov edi, [a1]
		call PConvertVPtr
	}
}


static const void* const njdrawsprite3Dptr = (void*)0x77D690;
static inline void NJDrawSprite3D(int a1, NJS_SPRITE* a2, char a3)
{
	__asm
	{
		push[a3]
		push[a2]
		mov eax, [a1]
		call njdrawsprite3Dptr
		add esp, 8
	}
}

#pragma pack(push, 1)
struct EntityData2_R
{
	NJS_POINT3 spd;
	NJS_POINT3 acc;
	Rotation ang_aim;
	Rotation ang_spd;
	float force;
	float accel;
	float frict;
};
#pragma pack(pop)

static const void* const camptr = (void*)0x4EBD30;
static int sub_4EBD30(int a1, int a2)
{

	int result;
	__asm
	{
		mov ecx, a2
		mov eax, a1
		call camptr
		mov result, eax
	}
	return result;
}

static const void* const KillPlayerFallPtr = (void*)0x46B330;
static inline void  BGCheckAndKillPlayer(int a1)
{
	__asm
	{
		mov ebx, a1 // a2
		call KillPlayerFallPtr
	}
}


// Chaos Drive Function Pointers
DataPointer(void*, dword_1DE4680, 0x1DE4680);
DataPointer(void*, dword_1DE4684, 0x1DE4684);
DataPointer(void*, dword_1DE4688, 0x1DE4688);
DataPointer(void*, dword_1DE468C, 0x1DE468C);


DataPointer(__int16, ActiveLandTableColCount, 0x1DE9484);
FunctionPointer(void, DrawObject, (NJS_OBJECT* a1), 0x42E730);


struct minicsts
{
	int angx;
	int angz;
	NJS_POINT3 normal;
	NJS_POINT3 normal2;
	NJS_POINT3 onpoly;
	NJS_POINT3 pshbk;
	NJS_POINT3 anaspdh;
	NJS_POINT3 anaspdv;
};

struct coliparapool
{
	minicsts paras;
	float distchk;
	float distnxt;
};


struct csts
{
	float radius;
	NJS_POINT3 pos;
	NJS_POINT3 spd;
	NJS_POINT3 tnorm;
	unsigned __int16 find_count;
	unsigned __int16 selected_nmb;
	float yt;
	float yb;
	int angx;
	int angz;
	NJS_POINT3 normal;
	NJS_POINT3 normal2;
	NJS_POINT3 onpoly;
	NJS_POINT3 pshbk;
	NJS_POINT3 anaspdh;
	NJS_POINT3 anaspdv;
};


struct pathinfo
{
	int slangx;
	int slangz;
	int slangax;
	int slangaz;
	float onpathpos;
	NJS_POINT3 pos;
	float xpos;
	float ypos;
	float zpos;
	NJS_POINT3 normal;
	NJS_POINT3 normala;
	NJS_POINT3 front;
};


FunctionPointer(int, GetStatusOnPath, (LoopHead* a1, pathinfo* a2), 0x4905A0);


struct DynColInfo
{
	SurfaceFlags  Attribute;
	NJS_OBJECT* Object;
	ObjectMaster* Task;
};

DataPointer(DynColInfo*, LandColList, 0x1A5A2DC);

DataPointer(unsigned __int16, LandColList_Count, 0x1DE9484);

FunctionPointer(int, CL_ColPolListUpNear, (csts* a1), 0x48BAF0);

int VectorAngle(NJS_VECTOR* a1, NJS_VECTOR* a2, NJS_VECTOR* a3);


#pragma pack(push, 8)
struct struct_0x58
{
	int RotationX_;
	int RotationZ_;
	NJS_VECTOR field_8;
	NJS_VECTOR field_14;
	NJS_VECTOR field_20;
	BYTE gap2C[40];
	float field_54;
};
#pragma pack(pop)


#pragma pack(push, 8)
struct __declspec(align(4)) SomeFloatThing
{
	BYTE gap0[68];
	struct_0x58 _struct_0x58;
};
#pragma pack(pop)


struct CL_PolyInfo
{
	CL_PolyInfo* next;
	CL_PolyInfo* before;
	float cx;
	float cy;
	float cz;
	float ndlenmax2;
	NJS_POINT3 vrt[3];
	unsigned int polatflg;
};

struct CL_ObjInfo
{
	CL_ObjInfo* next;
	CL_ObjInfo* before;
	obj* objptr;
	int objatt;
	CL_PolyInfo* pri_start;
	CL_PolyInfo* pri_end;
	int pri_nmb;
	CL_PolyInfo** pni_start;
	CL_PolyInfo** pni_end;
	int pni_nmb;
	float zelen;
	float xelen;
	float cx;
	float cy;
	float cz;
	float dummy;
};


static const void* const PhysicsAnimCheckPtr = (void*)0x474F80;
static inline void PhysicsAndAnimCheck(CharObj2Base* a1, EntityData1* a2)
{

	__asm
	{
		push[a2]
		mov ebx, [a1]
		call PhysicsAnimCheckPtr
		add esp, 4
	}
}


// signed int __usercall CL_ColPolCheckTouchRe@<eax>(csts* a1@<eax>, NJS_OBJECT* object, SurfaceFlags attribute)
static const void* const CL_ColPolCheckTouchRePtr = (void*)0x48CE40;
static inline int CL_ColPolCheckTouchRe(NJS_OBJECT* object, csts* a1, bool attribute)
{
	int result;
	__asm
	{
		push[attribute]
		push[a1]
		mov eax, [object]
		call CL_ColPolCheckTouchRePtr
		add esp, 8
		mov result, eax
	}
	return result;
}


void PhysicsAndAnimCheck(CharObj2Base* a1, EntityData1* a2);
FunctionPointer(void, SetMaterialColor, (float Alpha, float R, float G, float B), 0x44B2E0);
DataPointer(float, GlobalMatColorR, 0x25EFFD4);
DataPointer(float, GlobalMatColorG, 0x25EFFD8);
DataPointer(float, GlobalMatColorB, 0x25EFFDC);
DataPointer(float, GlobalMatColorA, 0x25EFFD0);
void ResetMaterialColorOffset();

void SetCameraPos(float x, float y, float z);
bool isSonicBouncing();