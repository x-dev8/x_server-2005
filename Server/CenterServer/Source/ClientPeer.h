/********************************************************************
	Filename: 	ClientPeer.h
	MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __CENTERSERVER_CLIENTPEER_H__
#define __CENTERSERVER_CLIENTPEER_H__

#pragma once

#include "GlobalDef.h"
#include "Memory_Pool.h"
#include "FuncPerformanceLog.h"
#include "NetClient.h"
//#include "MessageDefine.h"
#include "CenterGameMessage.h"

class GameServerPeer;

// Client 需要时效性的一个LifeId
class ClientPeer : INHERIT_POOL(ClientPeer)
{
public:
	DECLARE_POOL_FUNC(ClientPeer)

    ClientPeer();
    virtual ~ClientPeer(){}
    virtual long ProcessMessage( NetClient* pNetClient, Msg* pMessage );

    // 账号级别信息
    void             SetLoginInfo( const SLoginInfoBase& loginInfo ) { _loginInfo = loginInfo; }
    SLoginInfoBase&  GetLoginInfo() { return _loginInfo; }
    unsigned long    GetAccountId() { return _loginInfo.nAccountID; }
	std::string		 GetMacAdress() { return _loginInfo.szMac; }

    EClientStateType GetLoginState() { return _loginState; }
    void             SetLoginState( EClientStateType state ) { _loginState = state; }

    EClientStateType GetState() { return _playState; }
    void             SetState( EClientStateType state ) { _playState = state; }

    void             ChangeServerInfo( const SServerInfo& si);
    SServerInfo&     GetServerInfo()    { return _serverInfo;   } // 当前所在的服务器信息
    SStageReqInfo&   GetReqServerInfo() { return _stageReqInfo; } // 将要去的服务器信息

    void             GetToken()  { _IsHaveToken = true;  }
    void             MissToken() { _IsHaveToken = false; }
    bool             HaveToken() { return _IsHaveToken;  }
                  
    void             SetRequeryLoginTime(unsigned long dwTime) { _ReqLoginTime = dwTime; }
    unsigned long    GetRequeryLoginTime()            { return _ReqLoginTime; }

	void				ProcessPreDataLogin();	// 处理登陆前的准备数据
    void                ProcessLogin();			// 处理登录行为
	void                ProcessEnterWorld();	// 处理进入游戏
	void                ProcessExitWorld();		// 处理退出游戏

	void                UpdateCountryOnlineCount( int nCount );
    // 角色级别信息
    void                SetCharDynamicId( GameObjectId sCharId ) { _charDynamicId = sCharId; }
    GameObjectId        GetCharDynamicId() { return _charDynamicId; }
                     
    void                SetCharDbId( unsigned long nCharDbId ) { _currentCharDbId = nCharDbId; } 
    unsigned long       GetCharDbId() { return _currentCharDbId; }
    
    void                SetCountry( uint8 uchValue ) { _uchCountry = uchValue; }
    uint8               GetCountry()                 { return _uchCountry; }

    unsigned long       GetLastMapId() { return _nLastMapId;}
    void                SetLastMapId( unsigned long nLastMapId ) { _nLastMapId = nLastMapId; }

    SStageReqInfo&      GetStageReqInfo() { return _stageReqInfo;}
    void                ResetStageReqInfo(){ memset(&_stageReqInfo, 0xff, sizeof(_stageReqInfo)); _stageReqInfo.bHaveInvalidInfo = false;}

    void                OnSynInServerInfo( GS2CSPlayerSynInServerInfo* pMessage );
    long                OnExitServer( unsigned char ucExitType );

    void                SetCharacterName( const char* szName ) { strncpy_s( _szCharacterName, sizeof(_szCharacterName), szName, sizeof(_szCharacterName)-1); }
    const char*         GetCharacterName() { return _szCharacterName; }

    void                ResetAccountInfo();// 重置账号信息 构造
    void                ResetCharInfo();   // 重置角色信息 重新选人
	
	uint32				GetLoginServerId() { return _loginserverId;}
	void                SetLoginServerId( uint32 nId ) { _loginserverId = nId; }
	uint8				GetChannelStatus(uint32 client_count);

protected:
    void _OnS2SSwitchGate( S2SSwitchGate* pMessage );
    void _OnGS2CSSwitchStageReq( GS2CSSwitchStageReq* pMessage );
    void _OnMsgS2SSelectChannel( MsgS2SSelectChannel* pMessage );

    unsigned short _HandleEnterWorld( GameServerPeer* pLocusGameServerPeer, GS2CSSwitchStageReq* pMessage, bool bCorrect = false);
    unsigned short _HandleEnterMapGameServer( GameServerPeer* pLocusGameServerPeer, GS2CSSwitchStageReq* pMessage );
    unsigned short _HandleEnterCharacterLogin( GameServerPeer* pLocusGameServerPeer, GS2CSSwitchStageReq* pMessage );
    unsigned short _HandleFlyToMap( GameServerPeer* pLocusGameServerPeer, GS2CSSwitchStageReq* pMessage );
	unsigned short _HandleChangeChannel( GameServerPeer* pLocusGameServerPeer, GS2CSSwitchStageReq* pMessage );
	
private:
    // 账号级别
    SLoginInfoBase   _loginInfo;    // 登陆消息
    EClientStateType _loginState;   // 状态 登录状态
    SServerInfo      _serverInfo;   // 所在服务器信息
    bool             _IsHaveToken;  // 是否有票
    uint32           _ReqLoginTime; // 本客户端请求登录的时间

    // 角色级别
    uint8            _uchCountry;
    char             _szCharacterName[dr_MaxPlayerName];
    GameObjectId     _charDynamicId;              // 所在在服务器上动态Id
    uint32           _currentCharDbId;            // 当前所选择的角色
    short            _stWhichSlot;                // 当前所选择的角色的位置
    unsigned long    _nStageId;                   // 场景Id
    EClientStateType _playState;                  // 状态 游戏状态
    unsigned long    _nLastMapId;                 // 最近一次所在地图
    SStageReqInfo    _stageReqInfo;               // 要跳的地图的信息
    bool             _bIsHavePlayingInGameServer; // 是否已经选了角色在游戏世界里玩 在玩的话就可以告诉GameServer不要再发角色数据给Client    
    uint32           _organizeId;
  
	uint32           _loginserverId;				//登录服务器的id
};


typedef std::set<unsigned long>      AccountIdContainer;
typedef AccountIdContainer::iterator ItrAccountIdContainer;

typedef std::map<unsigned long, ClientPeer*> ClientPeerMapContainer;
typedef ClientPeerMapContainer::iterator     ItrClientPeerMapContainer;

typedef std::map<std::string, ClientPeer*>       ClientPeerMapContainerByString;
typedef ClientPeerMapContainerByString::iterator ItrClientPeerMapContainerByString;

typedef std::map<std::string, std::vector<ClientPeer*> >  ClientPeerMapContainerByMac;
typedef ClientPeerMapContainerByMac::iterator		  ItrClientPeerMapContainerByMac;

#endif // __CENTERSERVER_CLIENTPEER_H__
