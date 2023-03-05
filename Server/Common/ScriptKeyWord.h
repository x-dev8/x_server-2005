#ifndef __COMMON_SCRIPTKEYWORD_H__
#define __COMMON_SCRIPTKEYWORD_H__

#pragma once

#include "MeRTLibsServer.h"

enum EScriptKeyWord
{
    SKW_UNKNOWN        = -1,
    SKW_NUMBER         = -2,
    
    // logic operator
    SKW_GREATER        = -100, 
    SKW_GREATER_EQUAL,
    SKW_LESS,
    SKW_LESS_EQUAL,
    SKW_EQUAL,
    SKW_NOT_EQUAL,

    // math operator
    SKW_ADD            = -200,
    SKW_SUB,
    SKW_MUL,
    SKW_DIV,
    SKW_SET,
    SKW_RES,
    SKW_SETADD,
    SKW_SETSUB,
    SKW_SETMUL,
    SKW_SETDIV,
    SKW_SETRES,
    SKW_MONEY          = -300,
    SKW_SILVER,
    SKW_LEVEL,
    SKW_POS,
    SKW_NAME,
    SKW_MAP,
    SKW_MODEL,
    SKW_PROFESSION,    // 职业
    SKW_SEX,           // 性别
    SKW_EXP,           // 经验
    SKW_SKILLEXP,      // 技能经验
    SKW_STRENGTH,      // 力量
    SKW_TENACITY,      // 坚韧
    SKW_STAMINA,       // 体质
    SKW_INTELLIGENCE,  // 智力
    SKW_SPIRIT,		   // 精力
	SKW_AGILITY,       // 敏捷
	SKW_LUCKY,		   // 运气
	SKW_SKILL,		   // 技能
	SKW_ITEMCOUNT,	   // 物品数目
	SKW_HP,			   // 生命
	SKW_MP,			   // 魔法力
	SKW_REPUTATION,	   // 声望
    SKW_EXPLOIT,       // 功勋
	SKW_HEADERNAME,	   // 队长名字
	SKW_DSTPLAYERNAME, // 目标玩家名字
	SKW_ENERGY,	       // 活力
    SKW_GUILDNAME,	   // 公会名
    SKW_POSX,
    SKW_POSY,
    SKW_ENERGYMAX,         // 活力上限
    SKW_VIGOR,             // 精力
    SKW_VIGORMAX,          // 精力最大
    SKW_MINESKILLPOINT,    // 采矿熟练度
    SKW_HERBSKILLPOINT,    // 采药熟练度
    SKW_MOUNTSKILLPOINT,   // 驯马熟练度
    SKW_FISHSKILLPOINT,    // 钓鱼熟练度
    SKW_DAZAOSKILLPOINT,   // 打造熟练度
    SKW_PENGRENSKILLPOINT, // 烹饪熟练度
    SKW_CHAYISKILLPOINT,   // 茶艺熟练度
    SKW_LIANYAOSKILLPOINT, // 炼药熟练度
    SKW_JIAGONGSKILLPOINT, // 加工熟练度
    SKW_MARRIAGENAME,
    SKW_JIAOZI,            //交子
    SKW_JIAOZI_MONEY,      //交子或者money
	SKW_GetGuildName,      //获得公会名字
};

class CScriptKeyWordMgr
{
public:
    int         GetKeyWord( const char* pszWord );
    const char* GetKeyWordString( int id );
    BOOL        IsLogicOperator( int id );
    //BOOL      IsFunction( int id );
    //BOOL      IsReserved( int id );
};

extern CScriptKeyWordMgr g_skwMgr;

#endif // __COMMON_SCRIPTKEYWORD_H__
