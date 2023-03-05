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
{ // 得到升级需要的经验值
    struct SExp
    {
        int64 dwTotalExp; // 总经验
        uint32 dwPerExp;   // 每级经验
    };

    struct SSkillExp
    {
        DWORD dwSkillExp;   // 当前级别的总经验值
        DWORD dwLevelUpExp;	// 两级经验之差
    };
   
public:	
    CExpStage();
    ~CExpStage();

    bool LoadFromConfig( const char* pszFile );
    
    int64   GetLevelupExp( int iLevel );  // 升到下一级需要的总经验值
    int     GetLevel( int64 iCurExp );  // 得到当前经验值对应的等级    
    uint32	GetExpDistance( int iLevel ); // 得到指定等级与前一等级的所需经验值的差
    DWORD   GetPLevelupExp( int iLevel ); // 得到属性升级所需的经验值
    
    int     GetMountLevel( __int64 iCurExp );	// 得到当前经验值对应的等级
	int64   GetMountLevelupExp(int iLevel);	    // 升到下一级需要的总经验值
	DWORD   GetMountExpDistance( int nLevel );

    int     GetPetLevel( __int64 iCurExp );	    // 得到当前经验值对应的等级
    int64   GetPetLevelupExp(int iLevel);	    // 升到下一级需要的总经验值
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
