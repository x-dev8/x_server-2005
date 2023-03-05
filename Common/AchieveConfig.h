#ifndef __ACHIEVE_CONFIG_H__
#define __ACHIEVE_CONFIG_H__

#pragma once

#include <string>
#include <vector>
#include <map>

#include "GlobalDef.h"

class AchieveConfig
{
public:
    struct Achieve
    {
        uint16  nId         ;		// �ɾ�ID
        uint8   nType       ;		// �ɾʹ���
        uint16  nSubType    ;		// �ɾ�С��
        std::string  strSubName;	// �ɾ�С����
        std::string  strName;		// �ɾ���
        std::string  strDesc;		// �ɾ�Ŀ��
        uint16 nValueType   ;		// ��������� ����
        uint32 nFinishValue ;		// ��������� ֵ
        uint16 nRewardPoint ;		// �ɾ͵���
        uint16 nRewardItem  ;		// ������ƷID 
        uint16 nIconID      ;		// ICON ID
        uint8  nCompare     ;		// 0 �Ǵ��ڵ��� 1 �ǵ��� 2 ��С�� �жϸ�����������
        uint32 nShowProcess ;		// �Ƿ���ʾ����
		std::string strScriptAddr;  // �ɾ͵��ýű�·��

        Achieve() : nId(0),  nType(0), nSubType(0),strSubName("") ,strName(""),strDesc(""),nValueType(0), nFinishValue(0), 
            nRewardPoint(0),nRewardItem(0),nIconID(0),nCompare(0), strScriptAddr("")
        { 
        }

        Achieve(const Achieve& xAchieve)
        {
            *this = xAchieve;
        }

        Achieve& operator = (const Achieve& xAchieve)
        {
            if (this != &xAchieve)
            {
                nId         = xAchieve.nId;
                nType       = xAchieve.nType;
                nSubType    = xAchieve.nSubType;
                strSubName  = xAchieve.strSubName;
                strName     = xAchieve.strName;
                strDesc     = xAchieve.strDesc;
                nValueType  = xAchieve.nValueType;
                nFinishValue = xAchieve.nFinishValue;
                nRewardPoint = xAchieve.nRewardPoint;
                nRewardItem  = xAchieve.nRewardItem;
                nIconID      = xAchieve.nIconID;
                nCompare     = xAchieve.nCompare;
                nShowProcess = xAchieve.nShowProcess;
				strScriptAddr = xAchieve.strScriptAddr;
            }

            return *this;
        }

        bool operator == (const int Id) { return (this->nId == Id); }

        const uint16 GetID() const { return nId; }
        const uint8  GetType()  const { return nType; }
        const uint16 GetSubType() const { return nSubType;  }
        const std::string GetSubName() const { return strSubName; }
        const std::string GetName() const { return strName; }
        const std::string GetDesc() const { return strDesc; }
        const uint16 GetValueType() const { return nValueType; }
        const uint32 GetFinishValue() const { return nFinishValue; }
        const uint16 GetRewardPoint() const { return nRewardPoint; }
        const uint16 GetRewardItem () const { return nRewardItem ; }
        const uint16 GetIconID() const { return nIconID;  }
        const uint8  GetCompare() const{ return nCompare; }
        const uint32 GetShowProcess() const { return nShowProcess; }
		const std::string GetScriptAddr() const { return strScriptAddr; }
    };

    struct Observer
    {
        Observer() : nValueType(0)
        {
            vecAchieveIds.clear();
        }

        uint16 nValueType;
        std::vector<uint16> vecAchieveIds;
    };

protected:
    AchieveConfig();

public:
    ~AchieveConfig();

    inline static AchieveConfig& Instance()
    {
        static AchieveConfig s_xConfig;
        return s_xConfig;
    }

    bool LoadAchieveConfig(const char* szFile);

    Achieve*  GetAchieve  ( uint16 nId ) 
    {
        if ( nId >= MAX_ACHIVEVMENT_COUNT)
        { return NULL; }

        Achieve xAchieve = m_vecAchieve[nId];

        if ( xAchieve.GetID() == InvalidLogicNumber )
        { return NULL; }
        
        return &m_vecAchieve[nId];
    }

    Observer* GetObserver( uint16 nValueType )
    {
        return &m_vecObserver[nValueType];
    }

    const std::vector<Achieve>& GetAchieveList() const{ return m_vecAchieve; }

private:
    std::vector<Achieve>    m_vecAchieve    ;
    std::vector<Observer>   m_vecObserver   ;

public:
    typedef std::vector<Achieve>::iterator  AchieveIter ;
    typedef std::vector<Observer>::iterator ObserverIter;
};

#define theAchieveConfig AchieveConfig::Instance()   //ʵ���ӿ�

#endif

