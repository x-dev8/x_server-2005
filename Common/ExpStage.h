/********************************************************************
    Filename:    ExpStage.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __COMMON_EXPSTAGE_H__
#define __COMMON_EXPSTAGE_H__

#pragma once

#include "MeRTLibs.h"
#include "Array.h"
#include "GlobalDef.h"

class CExpStage
{ // �õ�������Ҫ�ľ���ֵ
    struct SExp
    {
        int64 dwTotalExp; // �ܾ���
        uint32 dwPerExp;   // ÿ������
    };

    struct SSkillExp
    {
        DWORD dwSkillExp;   // ��ǰ������ܾ���ֵ
        DWORD dwLevelUpExp;	// ��������֮��
    };
   
public:	
    CExpStage();
    ~CExpStage();

    bool LoadFromConfig( const char* pszFile );
    
    int64   GetLevelupExp( int iLevel );  // ������һ����Ҫ���ܾ���ֵ
    int     GetLevel( int64 iCurExp );  // �õ���ǰ����ֵ��Ӧ�ĵȼ�    
    uint32	GetExpDistance( int iLevel ); // �õ�ָ���ȼ���ǰһ�ȼ������辭��ֵ�Ĳ�
    DWORD   GetPLevelupExp( int iLevel ); // �õ�������������ľ���ֵ
    
    int     GetMountLevel( __int64 iCurExp );	// �õ���ǰ����ֵ��Ӧ�ĵȼ�
	int64   GetMountLevelupExp(int iLevel);	    // ������һ����Ҫ���ܾ���ֵ
	DWORD   GetMountExpDistance( int nLevel );

    int     GetPetLevel( __int64 iCurExp );	    // �õ���ǰ����ֵ��Ӧ�ĵȼ�
    int64   GetPetLevelupExp(int iLevel);	    // ������һ����Ҫ���ܾ���ֵ
    DWORD   GetPetExpDistance( int nLevel );

    //bool  LoadSkillExp(char *pszFile); 
    //DWORD GetSkillLevelExp(int nLevel);
    //DWORD GetSkillLevelUpExp(int nLevel);
    //int   GetSkillLevel(int nCuiExp);
    //int   GetSkillExpDistance(int nLevel);

private:
    int _maxCharLevel   ;
    int _maxMountLevel  ;
    int _maxPetLevel    ;
    //int m_iMaxSkillLevel;

    Array<SExp, const_iCharMaxLevel>	       _charExp ;    
    Array<SExp, const_iCharMaxLevel>	       _mountExp;
    Array<SExp, const_iCharMaxLevel>	       _petExp  ;
};

extern CExpStage theExpStage;

#endif // __COMMON_EXPSTAGE_H__
