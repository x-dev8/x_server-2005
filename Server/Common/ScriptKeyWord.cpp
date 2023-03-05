#include "ScriptKeyWord.h"

CScriptKeyWordMgr g_skwMgr;

struct SKeyWordPair
{
    char* pszWord;
    int   nId;
};

SKeyWordPair g_ScriptKeyWordPairs[] = 
{
	// logic operator
	">",			SKW_GREATER,
	">=",			SKW_GREATER_EQUAL,
	"<",			SKW_LESS,
	"<=",			SKW_LESS_EQUAL,
	"==",			SKW_EQUAL,
	"!=",			SKW_NOT_EQUAL,
	// math operator
	"+",			SKW_ADD,
	"-",			SKW_SUB,
	"*",			SKW_MUL,
	"/",			SKW_DIV,
    "%",            SKW_RES,
	"=",			SKW_SET,
	"+=",			SKW_SETADD,
	"-=",			SKW_SETSUB,
	"*=",			SKW_SETMUL,
	"/=",			SKW_SETDIV,
    "%=",           SKW_SETRES,
	// property
	"money",		SKW_MONEY,
	"silver",		SKW_SILVER,
	"level",		SKW_LEVEL,
	"pos",			SKW_POS,
	"name",			SKW_NAME,
	"map",			SKW_MAP,
	"model",		SKW_MODEL,
	"profession",	SKW_PROFESSION,
	"sex",			SKW_SEX,
	"exp",			SKW_EXP,
	"skillexp",		SKW_SKILLEXP,
	"con",			SKW_STAMINA,
	"str",			SKW_STRENGTH,
	"dex",			SKW_AGILITY,
	"int",			SKW_INTELLIGENCE,
	"mgc",			SKW_SPIRIT,
	"lky",			SKW_LUCKY,
	"hp",			SKW_HP,
	"mp",			SKW_MP,
	"status",		SKW_SKILL,
	"item_count",	SKW_ITEMCOUNT,
	"reputation",	SKW_REPUTATION,
    "exploit",      SKW_EXPLOIT,
	"headername",	SKW_HEADERNAME,
	"dstplayername",SKW_DSTPLAYERNAME,
	"energy",		SKW_ENERGY,
    "guildname",    SKW_GUILDNAME,
    "posx",			SKW_POSX,
    "posy",			SKW_POSY,
	"energymax",    SKW_ENERGYMAX,
    "vigor",             SKW_VIGOR,
    "vigormax",          SKW_VIGORMAX,
    "mineskillpoint",    SKW_MINESKILLPOINT,
    "herbskillpoint",    SKW_HERBSKILLPOINT,
    "mountskillpoint",   SKW_MOUNTSKILLPOINT,
    "fishskillpoint",    SKW_FISHSKILLPOINT,
    "dazaoskillpoint",   SKW_DAZAOSKILLPOINT,
    "pengrenskillpoint", SKW_PENGRENSKILLPOINT,
    "chayiskillpoint",   SKW_CHAYISKILLPOINT,
    "lianyaoskillpoint", SKW_LIANYAOSKILLPOINT,
    "jiagongskillpoint", SKW_JIAGONGSKILLPOINT,
    "marriagename",      SKW_MARRIAGENAME,
    "jiaozi",            SKW_JIAOZI,
    "jiaoziormoney",     SKW_JIAOZI_MONEY,
	"GetGuildName",      SKW_GetGuildName,
	NULL,
};

int CScriptKeyWordMgr::GetKeyWord( const char* pszWord )
{
    if( NULL == pszWord )
    { return SKW_UNKNOWN; }

    for( int i=0; g_ScriptKeyWordPairs[i].pszWord != NULL; ++i )
    {
        if( stricmp( g_ScriptKeyWordPairs[i].pszWord, pszWord ) == 0 )
        { return g_ScriptKeyWordPairs[i].nId; }
    }
    return SKW_UNKNOWN;
}

const char* CScriptKeyWordMgr::GetKeyWordString( int id )
{
    for( int i = 0; g_ScriptKeyWordPairs[i].pszWord != NULL; i++ )
    {
        if( id == g_ScriptKeyWordPairs[i].nId )
            return g_ScriptKeyWordPairs[i].pszWord;
    }
    return NULL;
}

BOOL CScriptKeyWordMgr::IsLogicOperator( int id )
{
    if( id == SKW_GREATER ||
        id == SKW_GREATER_EQUAL ||
        id == SKW_LESS ||
        id == SKW_LESS_EQUAL ||
        id == SKW_EQUAL ||
        id == SKW_NOT_EQUAL )
    { return TRUE; }

    return FALSE;
}

//BOOL CScriptKeyWordMgr::IsReserved( int id )
//{
//    if( id == SKW_PROC_START    ||
//        id == SKW_PROC_END        ||
//        id == SKW_IF            ||
//        id == SKW_ELSE            ||
//        id == SKW_ENDIF            ||
//        id == SKW_SET            ||
//        id == SKW_CALL            ||
//        id == SKW_JUMP            ||
//        id == SKW_RETURN        ||
//        id == SKW_JUMPTOENDIF )
//        return TRUE;
//    return FALSE;
//}

//BOOL CScriptKeyWordMgr::IsFunction( int id )
//{
//    /*if( id == SKW_DLG ||
//        id == SKW_TELL ||
//        id == SKW_TALK ||
//        id == SKW_BROADCAST )*/
//    if( id > SKW_FUNCTION_START && id < SKW_FUNCTION_END )
//        return TRUE;
//    return FALSE;
//}
