/********************************************************************
    Filename:    SkillBag.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_SKILLBAG_H__
#define __COMMON_SKILLBAG_H__

#pragma once

#include "..\GlobalDef.h"

typedef std::pair<DWORD,DWORD> CDTIME;

class BuffStatusManager;

class SkillBag
{
public:    
    struct SColdTime
    { // ������ȴʱ��
        SColdTime()
        {
           Clear();
        }
        bool  bCooldowning;
        DWORD dwColdStartTime; // ��ʼʱ��
        DWORD dwColdTime;      // ��Ҫʱ��

        void Clear()
        {
            bCooldowning    = false;
            dwColdStartTime = 0;
            dwColdTime      = 0;
        }
    };

public:
    SkillBag();
    ~SkillBag();

    void        Init( SCharSkill *pSkill,int iSize, bool bFixedSize= false );
    bool        ClearAllSkills();
    bool        AddSkill( unsigned short ustSkillID, short stSkillLevel = 1 );         
	bool        PrepareSelfSkillEffect( unsigned short ustSkillID, short stSkillLevel );
	bool        RemoveSkill( unsigned short ustSkillID );
    int         GetSkillNum() {return m_iSkillNum;}    
    int         GetSkillIndexById( int nSkillID );
    SCharSkill* GetSkillByID( unsigned short ustSkillID );
    SCharSkill* GetSkillByIndex( unsigned short stIndex );
    bool        IsSkillCoolDownByIndex( short stIndex );
    bool        IsSkillCoolDownById( int nId );    
    void        Update();
    CDTIME      StartSkillCoolDown( unsigned short ustSkillID, short stSkillLevel, DWORD dwDelay = 0); //��ʼ����CoolDown ������ȴʱ��
    CDTIME      StartSkillCoolDown( BuffStatusManager& _buffManager, unsigned short ustSkillID, short stSkillLevel, DWORD dwDelay = 0); //��ʼ����CoolDown ������ȴʱ�� ����������
    bool        ClearSkillCollDown( unsigned short ustSkillID = InvalidLogicNumber );
    SColdTime*  GetColdTimeByIndex( unsigned int nIndex );
    SColdTime*  GetColdTimeById   ( unsigned int nID );
    void        SaveSkillColdTime(); // ����CDʱ��

private:    
    int          m_iSize;     // m_pSkills����Ĵ�С
    int          m_iSkillNum; // ��Ч�ļ��ܵĸ���
    SCharSkill*  m_pSkills;   // status����,���Ȱ�More_iMaxSkillKnown
    SColdTime    m_stSkillColdTime[More_iMaxSkillKnown];
    DWORD        m_dwLastUpdate;
};

#endif // __COMMON_SKILLBAG_H__
