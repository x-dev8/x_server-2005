/********************************************************************
	Filename: 	influence.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_INFLUENCE_H__
#define __GAMESERVER_INFLUENCE_H__

#pragma once

#include "MeRTLibsServer.h"

const unsigned int MaxInfluence = 32; //最大阵营数

class CInfluence
{ // 阵营
public:
	enum EFriendValue
	{
		HOSTILE  = 0, // 敌对
		FRIENDLY = 1, // 友好
	};

public:
	CInfluence();
	virtual ~CInfluence();
	// 初始化
    void Init(int nID, std::string strName, int nRight, int nKill, int nHuiren, int nMojia, int nNoGuild, int nGuard, int nAttack, int nNormal, std::string strFriend);

	// 阵营友好度
    int GetRightValue() { return m_nRight; }
    int GetKillValue() { return m_nKill; }
    int GetGuildValue( int nInfluence )
    { 
        if(nInfluence == 0)
        {
            return m_nMojia;
        }
        
        if(nInfluence == 1)
        {
            return m_nHuiren;
        }

        return m_nNoGuild;
    }

    int GetCityValue( int nGroup )
    { 
        if(nGroup == 1)
        {
            return m_nCityGuard;
        }

        if(nGroup == 2)
        {
            return m_nCityAttack;
        }

        return m_nCityNormal;
    }

	void SetFriendValue(int nID, int nFriendValue) { m_vFriendList[nID] = nFriendValue; }
	int GetFriendValue(int nID) { return m_vFriendList[nID]; }

	// 获取阵营信息
	int GetID() { return m_nID; }
    std::string GetName() { return m_strName; }

private:
	int m_nID;
    std::string m_strName;

    int m_nRight;
    int m_nKill;
    int m_nHuiren;
    int m_nMojia;
    int m_nNoGuild;
    int m_nCityGuard;
    int m_nCityAttack;
    int m_nCityNormal;
	
    std::vector<int> m_vFriendList;
};

// 阵营管理器
class CInfluenceManager
{
public:
    CInfluenceManager();
    virtual ~CInfluenceManager();

public:
    // 从slk配置文件载入各阵营
    bool InitFromSlkFile(const char* szFile);

	// 获取阵营指针
	CInfluence* GetInfluenceByID(int nID);
    CInfluence* GetInfluenceByName(const std::string& strName);

private:
    std::vector<CInfluence*> m_vInfluenceList;
};

#endif // __GAMESERVER_INFLUENCE_H__
