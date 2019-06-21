#pragma once

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <list>
#include <unordered_map>
#include <vector>
#include <queue>
#include <functional>
#include <Windows.h> 

#include <crtdbg.h>
#include <assert.h>
#include <math.h>
#include <string>
#include <typeinfo>
#include "Vector2.h"
#include "resource.h"

#include <thread>
#include <mutex>

#include "Sound\fmod.hpp"

#pragma comment(lib, "fmod_vc")
#pragma comment(lib, "msimg32")


using namespace FMOD;
using namespace std;

#define LONG_MAX_PATH 512
#define MAX_NAME 128
#define TILESIZE CVector2(32,32)
#define TILEWIDTH 32
#define TILEHEIGHT 32

#define GET_SINGLE(type) type::GetInstance()
#define GETKEYDOWN(key) GET_SINGLE(CInput)->GetKeyDown(key)
#define GETKEY(key) GET_SINGLE(CInput)->GetKey(key)
#define GETKEYUP(key) GET_SINGLE(CInput)->GetKeyUp(key)

#define ROOT_PATH "RootPath"
#define TEXTURE_PATH "TexturePath"
#define UI_TEXTURE_PATH "UITexturePath"
#define UNIT_TEXTURE_PATH "UnitTexturePath"
#define BUILDING_TEXTURE_PATH "BuildingTexturePath"
#define TILESET_TEXTURE_PATH "TileSetTexturePath"
#define VOICE_PATH "VoicePath"
#define SFX_PATH "SFXPath"
#define BGM_PATH "BGMPath"
#define VFX_PATH "VFXPath"
#define UNIT_PATH "UnitPath"
#define CACHE_PATH "CachePath"
#define ANIMATION_CLIP_PATH "AnimationClipPath"
#define MAP_PATH "MapPath"

enum FOW_STATE
{
	FS_INVISIBLE,
	FS_VISIBLE
};

typedef struct _tagFOW
{
	FOW_STATE m_eState;
	bool m_bVisit;

	bool operator ==(const _tagFOW& target)
	{
		return target.m_bVisit == m_bVisit && target.m_eState == m_eState;
	}
	bool operator != (const _tagFOW& target)
	{
		return target.m_bVisit != m_bVisit || target.m_eState != m_eState;
	}

	_tagFOW() :
		m_eState(FS_INVISIBLE),
		m_bVisit(false)
	{};
}FOW, *PFOW;


enum SOUND_TYPE
{
	ST_BGM,
	ST_SFX,
	ST_END
};

typedef struct _tagSoundInfo
{
	Sound*	pSound;
	bool	bLoop;
}SOUNDINFO, *PSOUNDINFO;


typedef struct _tagPIXEL
{
	unsigned char b;
	unsigned char g;
	unsigned char r;

}PIXEL, *PPIXEL;

enum UNIT_INFO_STATE
{
	IS_NONE,
	IS_BUILD,
	IS_UPGRADE
};
enum ATTACK_MODE
{
	AM_NONE,
	AM_ATTACK_MOVE,
	AM_ATTACK_TARGET,
};
enum UPGRADE_TYPE
{
	UT_NONE,
	UT_TERRAN_BIONIC_WEAPON,
	UT_TERRAN_BIONIC_DEFFENCE,
	UT_TERRAN_MECHANIC_GROUND_WAEPON,
	UT_TERRAN_MECHANIC_GROUND_DEFFENCE,
	UT_TERRAN_MECHANIC_AIR_WAEPON,
	UT_TERRAN_MECHANIC_AIR_DEFFENCE,

	//Academy
	UT_TERRAN_RESTORATION, // 메딕
	UT_TERRAN_OPTICAL_FLARE,
	UT_TERRAN_CADUCEUS_REACTOR, // 메딕 마나 + 50
	UT_TERRAN_U238,//마린 사정거리
	UT_TERRAN_STIMPACK,//스팀팩

	//MachineShop
	UT_TERRAN_ION_THRUSTERS, // 벌쳐 속업
	UT_TERRAN_SPIDER_MINE,
	UT_TERRAN_SEIGE_TECH, // 시즈모드
	UT_TERRAN_CHARON_BOOSTER, // 골리앗 공중 사정거리

	//Science Facility
	UT_TERRAN_EMP,
	UT_TERRAN_IRRADIATE,
	UT_TERRAN_TITAN_REACTOR, // 사이언스 베슬 마나 +50

	//Covert Ops
	UT_TERRAN_LOCK_DOWN,
	UT_TERRAN_CLOAKING,
	UT_TERRAN_OCULAR_IMPLANT, //고스트 시야업
	UT_TERRAN_MOEBIUS_REACTOR, //고스트 마나 +50

	//Physics Lab
	UT_TERRAN_YAMATO_GUN,
	UT_TERRAN_COLOSSUS_REACTOR, //배틀 쿠르저 마나 +50

	//Control Tower
	UT_TERRAN_CLOAKING_FIELD,
	UT_TERRAN_APOLLO_REACTOR, //레이스 마나 + 50

	UT_PROTOSS_SHIELD,

	UT_END
};

enum GATHER_STATE
{
	GS_MOVETORESOURCE,
	GS_RETURNTOBASEMENT,
	GS_GATHERING
};

enum BUILD_STATE
{
	BS_NONE,
	BS_MOVETOBUILD,
	BS_BUILD
};

enum OBJECT_TYPE
{
	OT_RESOURCE,
	OT_BUILDING,
	OT_UNIT
};

enum TERRAIN_TYPE
{
	TT_NORMAL,
	TT_GAS,
	TT_CREEP
};


enum TEAM_COLOR
{
	TC_RED,
	TC_BLUE,
	TC_TEAL,
	TC_PURPLE,
	TC_ORANGE,
	TC_BROWN,
	TC_WHITE,
	TC_YELLOW
};

enum CURSOR_STATE
{
	CS_NORMAL,
	CS_OVER_UNIT,
	CS_SELECT_RECT,
	CS_TARGETING
};


enum BUTTON_STATE
{
	BS_DISABLE,
	BS_ENABLE
};
enum RACE_TYPE
{
	RT_TERRAN,
	RT_PROTOSS,
	RT_ZERG,
	RT_RANDOM
};

enum RESOURCE_TYPE
{
	RT_NONE,
	RT_MINERAL,
	RT_VESPENE_GAS
};

enum COMPONENT_PARENT_TYPE
{
	PT_NONE,
	PT_RENDERER,
	PT_COLLIDER
};
enum COMPONENT_TYPE
{
	CT_NONE,
	CT_TRANSFORM,
	CT_CAMERA,
	CT_CAMERA_MOVE,
	CT_COLLISION_TILE,
	CT_DEFAULT_UNIT_ANIMATOR,
	CT_SYSTEM_MANAGER,
	CT_TEST_MOVE,
	CT_ELLIPSE_RENDERER,
	CT_GRID_RENDERER,
	CT_RECTANGLE_RENDERER,
	CT_SPRITE_RENDERER,
	CT_TERRAIN_RENDERER,
	CT_TEXTURE_RENDERER,
	CT_UI_RENDERER,
	CT_CIRCLE_COLLIDER,
	CT_PIXEL_COLLIDER,
	CT_POINT_COLLIDER,
	CT_RECT_COLLIDER,
	CT_TEXT_RENDERER,
	CT_BUTTON_COLLIDER,
	CT_STRUCTURE,
	CT_RESOURCE,
	CT_CURSOR_MOVE,
	CT_CURSOR,
	CT_PLAYER,
	CT_UNIT_STATUS,
	CT_MOVE,
	CT_ATTACK,
	CT_BUILD,
	CT_ADVANCED_BUILD,
	CT_GATHER,
	CT_HOLD,
	CT_STOP,
	CT_REPAIR,
	CT_DEFFENCE,
	CT_SHIELD,
	CT_UNITINFO,
	CT_ENERGY,
	CT_PATROL,
	CT_SCV_ANIMATOR,
	CT_MINERALORB_ANIMATOR,
	CT_GASTANK_ANIMATOR,
	CT_GASBOX_ANIMATOR,
	CT_GASSAC_ANIMATOR,
	CT_MARINE_ANIMATOR,
	CT_MEDIC_ANIMATOR,
	CT_GHOST_ANIMATOR,
	CT_FIREBAT_ANIMATOR,
	CT_VULTURE_ANIMATOR,
	CT_SEIGETANK_ANIMATOR,
	CT_GOLIAHT_ANIMATOR,
	CT_WRAITH_ANIMATOR,
	CT_BATTLECRUISER_ANIMATOR,
	CT_DROPSHIP_ANIMATOR,
	CT_VALKYRIE_ANIMATOR,
	CT_SPIDERMINE_ANIMATOR,
	CT_SCIENCEVESSEL_ANIMATOR,

	CT_STIMPACK,

	CT_COMMANDCENTER,
	CT_SUPPLYDEPOT,
	CT_ACADEMY,
	CT_BARRACKS,
	CT_ENGINEERINGBAY,
	CT_BUNKER,
	CT_MISSILETURRET,

	CT_FACTORY,
	CT_STARPORT,
	CT_SCIENCEFACILITY,
	CT_ARMORY,



};