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
    SKW_PROFESSION,    // ְҵ
    SKW_SEX,           // �Ա�
    SKW_EXP,           // ����
    SKW_SKILLEXP,      // ���ܾ���
    SKW_STRENGTH,      // ����
    SKW_TENACITY,      // ����
    SKW_STAMINA,       // ����
    SKW_INTELLIGENCE,  // ����
    SKW_SPIRIT,		   // ����
	SKW_AGILITY,       // ����
	SKW_LUCKY,		   // ����
	SKW_SKILL,		   // ����
	SKW_ITEMCOUNT,	   // ��Ʒ��Ŀ
	SKW_HP,			   // ����
	SKW_MP,			   // ħ����
	SKW_REPUTATION,	   // ����
    SKW_EXPLOIT,       // ��ѫ
	SKW_HEADERNAME,	   // �ӳ�����
	SKW_DSTPLAYERNAME, // Ŀ���������
	SKW_ENERGY,	       // ����
    SKW_GUILDNAME,	   // ������
    SKW_POSX,
    SKW_POSY,
    SKW_ENERGYMAX,         // ��������
    SKW_VIGOR,             // ����
    SKW_VIGORMAX,          // �������
    SKW_MINESKILLPOINT,    // �ɿ�������
    SKW_HERBSKILLPOINT,    // ��ҩ������
    SKW_MOUNTSKILLPOINT,   // ѱ��������
    SKW_FISHSKILLPOINT,    // ����������
    SKW_DAZAOSKILLPOINT,   // ����������
    SKW_PENGRENSKILLPOINT, // ���������
    SKW_CHAYISKILLPOINT,   // ����������
    SKW_LIANYAOSKILLPOINT, // ��ҩ������
    SKW_JIAGONGSKILLPOINT, // �ӹ�������
    SKW_MARRIAGENAME,
    SKW_JIAOZI,            //����
    SKW_JIAOZI_MONEY,      //���ӻ���money
	SKW_GetGuildName,      //��ù�������
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
