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

int CL_ColPolCheckTouchRe(NJS_OBJECT* object, csts* a1, bool attribute);
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


struct particle_info
{
	float scl;
	float sclspd;
	float animspd;
	float friction;
	float yacc;
	NJS_POINT3 pos;
	NJS_POINT3 velo;
	NJS_ARGB argb;
};

struct sp_link;

struct sp_info
{
	NJS_TEXLIST* texlist;
	NJS_TEXANIM* texanim;
	int animnum;
	int srcblend;
	int dstblend;
};


struct __declspec(align(4)) sp_task
{
	sp_task* next;
	void(__cdecl* exec)(sp_task*, sp_link*);
	unsigned __int8 mode;
	unsigned __int8 flag;
	__int16 no;
	int ang;
	float frame;
	float scl;
	NJS_POINT3 pos;
	NJS_POINT3 spd;
	NJS_ARGB argb;
	float offset;
	sp_task* work[2];
	unsigned __int8 wrtZflg;
};


struct sp_link
{
	sp_link* next;
	sp_task* head;
	void(__cdecl* exec)(sp_link*);
	unsigned int numtask;
	sp_info* info;
	unsigned int sysflag;
	void* work;
};


DataPointer(CL_ObjInfo*, NJS_OBJ_LIST_PTR_PREV, 0x1A5A400);
void PhysicsAndAnimCheck(CharObj2Base* a1, EntityData1* a2);
FunctionPointer(void, SetMaterialColor, (float Alpha, float R, float G, float B), 0x44B2E0);
DataPointer(float, GlobalMatColorR, 0x25EFFD4);
DataPointer(float, GlobalMatColorG, 0x25EFFD8);
DataPointer(float, GlobalMatColorB, 0x25EFFDC);
DataPointer(float, GlobalMatColorA, 0x25EFFD0);
void ResetMaterialColorOffset();