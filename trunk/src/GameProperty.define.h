#pragma once
 
#define BASE_GAME_VALUE 0x1

enum eGameType
{
	GT_OL,
	GT_Web,
	GT_Flash,
	GT_Local
};

enum eGameCategory
{
	GC_ACT = 0,
	GC_AVG,
	GC_RPG,
	GC_TAB,
	GC_SPG,
	GC_RTS,
	GC_RAC,
	GC_STG,
	GC_SIM,
	GC_FTG,
	GC_MUG,
	GC_PUZ,
	GC_SLG,
	GC_TCG,
	GC_ETC
};

enum eGamePlatform
{
	PTF_PC = 0,
	PTF_Web,
	PTF_XBOX360,
	PTF_XBOXONE,
	PTF_PS3,
	PTF_PS4
};


