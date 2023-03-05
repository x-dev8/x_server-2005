#pragma once
#include "AttackBot.h"

class CScriptBot : public CAttackBot
{
public:    
	CScriptBot();
	virtual ~CScriptBot();

    virtual void InitPlayGame(UINT mapid = 0);

	virtual void PlayGame();

	virtual void PlayScript();

    bool GetFlyOut(){return m_bFlyOut;}

    void SetFlyOut(bool Value){ m_bFlyOut = Value;}

    bool GetFlyIn(){return m_bFlyIn;}

    void SetFlyIn(bool Value){ m_bFlyIn = Value;}

    bool FlyMap(DWORD dwNowTime, int nMapId);

private:
	int m_nScriptInMapId;
	int m_nScriptOutMapId;

	DWORD m_dwStayInScriptMapTime;		//在副本里和副本外呆的时间
	DWORD m_dwStayOutScriptMapTime;	//

	bool m_bFlyIn;
	bool m_bFlyOut;
	
	DWORD m_dwSpaceTime;
	DWORD m_dwNextFlyMapTime;
};

static const int s_nMapId[] = { 1, 2, 3, 4, };
static const int s_nMapCount = sizeof(s_nMapId) / sizeof(int);
static const int s_nScriptMapId[] = { 5, 6,};
static const int s_nScriptMapCount = sizeof(s_nScriptMapId) / sizeof(int);

/**********************************************************************
1. 判断在不在副本地图 , 不在则飞进去
2. 寻找怪物,杀几分钟; 然后飞出来



3. 副本地图id = (5,6)  淮南王陵 1 2 层
**********************************************************************/