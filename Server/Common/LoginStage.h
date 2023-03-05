/********************************************************************
    Filename:     LoginStage.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_LOGINSTAGE_H__
#define __GAMESERVER_LOGINSTAGE_H__

#pragma once

#include "StaticArray.h"
#include "WorkThread.h"
#include "MsgBase.h"

#define theLoginStage GetTheLoginStage()

// 登录处理 还没有进入场景的时候
// 特殊状态时，可将玩家角色加入 如：死亡，等待重生
class LoginStage
{
public:
	LoginStage();
	~LoginStage();

    void UnInit();

	bool KickCharByAccount( unsigned int dwAccount );
    void Run    ();

    bool IsExist( GameObjectId stID );
	bool Enter  ( GameObjectId stID );
    
	int  EnterQueue      ( GameObjectId stID ); // 进入排队
    int  LeaveQueue      ( GameObjectId stID ); // 离开排队
    int  GetLoginQueuePos( GameObjectId stID ); // 得到队伍中的位置

	bool IsOpenQueue()  {return m_bOpenService;}
	void SetService(bool b) {m_bOpenService = b;}
protected:
    DWORD               m_dwLastProcessTime; // 上一次处理的时间
    DWORD               m_dwCostTime;        // run的间隔消费时间

    typedef std::list<GameObjectId>               CharacterIdContainer;
    typedef CharacterIdContainer::iterator		   ItrCharacterIdContainer;

    CharacterIdContainer _charIDs;			 // 登录在这个服务器上的人

    CharacterIdContainer _charIDQueues;		 // 排队的人

	bool                 m_bOpenService;    //开启排队
};

LoginStage& GetTheLoginStage();

#endif // __GAMESERVER_LOGINSTAGE_H__
