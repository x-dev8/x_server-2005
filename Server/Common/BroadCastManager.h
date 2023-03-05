#ifndef _BROADCASTMANAGER_
#define _BROADCASTMANAGER_

#include "MeRTLibs.h"
#include "Singleton.h"
#include "BroadCastConfig.h"
#include "GameTimer.h"
#include "CenterGameMessage.h"

class BroadCastManager : public ISingletion< BroadCastManager >
{
public:
	BroadCastManager();
	~BroadCastManager();

	// 自动更新
	void RunUpdate( unsigned int nCurrentTime );
	void runUpdateType0( unsigned int nCurrentTime );
	void runUpdateType1( unsigned int nCurrentTime );
	void runUpdateType2( unsigned int nCurrentTime );
	void runUpdateType3( unsigned int nCurrentTime );
	void runUpdateType4( unsigned int nCurrentTime );

	void UpdataData();
	void Updata0( BroadCastConfig::VecType0& data );
	void Updata1( BroadCastConfig::VecType1& data );
	void Updata2( BroadCastConfig::VecType2& data );
	void Updata3( BroadCastConfig::VecType3& data );
	void Updata4( BroadCastConfig::VecType4& data );

	void OnMsgAck( MsgGS2CSBroadCastAck* pMessage );

private:
	// 更新定时器
	GameTimerEx m_xUpdateTimer;

	//下边这些储存当天要发的公告
	BroadCastConfig::VecType0 m_vecType0; 
	BroadCastConfig::VecType1 m_vecType1; 
	BroadCastConfig::VecType2 m_vecType2; 
	BroadCastConfig::VecType3 m_vecType3; 
	BroadCastConfig::VecType4 m_vecType4; 
};

#define theBroadCastManager BroadCastManager::Instance()

#endif //_BROADCASTMANAGER_