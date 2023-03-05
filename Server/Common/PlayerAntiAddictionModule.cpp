#include "GamePlayer.h"
#include "Configure.h"

void GamePlayer::UpdateAntiAddiction()
{
    // 是否要进行防沉迷逻辑
    if ( !IsRunAntiAddiction())
    { return; }

    // 状态变化逻辑 每一分钟进来一次
    if ( !_xUpdateAntiAddictionTimer.DoneTimer( HQ_TimeGetTime() ))
    { return; }

    // 累积在线时长单位分钟
    uint32 nTotalOnlineTime = GetAntiAddictionOnlineTime();
    AntiAddictionState curState = CalcAntiAddictionStatus( nTotalOnlineTime );

    if ( curState != gTransferRuntimeInfo.nAntiAddicationStatus )
    { // 有状态改变

        Log("Antiaddiction change status from [%d->%d] %d ", gTransferRuntimeInfo.nAntiAddicationStatus, curState, GetAntiAddictionOnlineTime() );

        // 设置新的时间
        gTransferRuntimeInfo.nAntiAddicationStatus = curState;

        // 充值状态变化后的计数
        ResetAntiAddictionNotifyIndex();

        // 发消息通知客户端变化
        SendMsgWallowAbout( MsgWallowAbout::ENotifyType_StatusChange);
    }

    // 通知提示客户端
    UpdateAntiAddictionNotify();

    // 保存入平台
    UpdateSaveAntiAddiction();
}


void GamePlayer::UpdateAntiAddictionNotify()
{
    // 累积在线时长单位分钟
    TimeEx xCurrentTime = TimeEx::GetCurrentTime();

    if ( 0 == _nAntiAddtionStatusChangeStamp )
    { _nAntiAddtionStatusChangeStamp = xCurrentTime.GetTime(); }

    TimeEx xStartTime( _nAntiAddtionStatusChangeStamp );    
    if ( xStartTime > xCurrentTime )
    { _nAntiAddtionStatusChangeStamp = xCurrentTime.GetTime(); }

    // 得到经过的分钟数
    TimeSpan xTimeSpan = TimeEx::GetCurrentTime() - xStartTime; 
    int nDurantionTime = xTimeSpan.GetTotalSeconds() / OneMinuteSecond;

    uint32 nNotifyInterval = 60;
	uint32 nPlayTime = 0;//上一个状态的持续时间
    switch ( gTransferRuntimeInfo.nAntiAddicationStatus )
    {
    case enumAntiAddictionStateNormal:
        { 
			nNotifyInterval = g_Cfg.xAntiAddictionInfo._normal._notifyTime; 
			nPlayTime		= 0; 
		}
        break;
    case enumAntiAddictionStateTired:
        { 
			nNotifyInterval = g_Cfg.xAntiAddictionInfo._tired._notifyTime; 
			nPlayTime		= g_Cfg.xAntiAddictionInfo._normal._playTime; 
		}
        break;
    case enumAntiAddictionStateRest:
        { 
			nNotifyInterval = g_Cfg.xAntiAddictionInfo._rest._notifyTime; 
			nPlayTime		= g_Cfg.xAntiAddictionInfo._tired._playTime; 
		}
        break;
    }

    // 得到经过第一个间隔
    uint16 nIntervalCount = (GetAntiAddictionOnlineTime() - nPlayTime) / nNotifyInterval;
    if ( nIntervalCount > _nAntiAddtionNotifyIndex )
    {
        // 发消息通知客户端变化
        SendMsgWallowAbout( MsgWallowAbout::ENotifyType_TimerNotify );

        //++_nAntiAddtionNotifyIndex; // 往下走一个
		_nAntiAddtionNotifyIndex = nIntervalCount;
    }
}

void GamePlayer::UpdateSaveAntiAddiction()
{
    // 总时间 当把间隔时间提交给平台后 gTransferRuntimeInfo.nOnlineTimeAntiAddiction 变为最终时间 _nAntiAddictionDurationTime 为累计提交的时间
    uint32 nOnlineTime = GetOnlineRealTime() / OneMinuteSecond;

    // 提交间隔分钟
    uint16 nIntervalTime = g_Cfg.nAntiAddictionSaveTime;
    if ( nIntervalTime == 0)
    { nIntervalTime = 10; }

    // 算出第几个间隔时间
    uint32 nCurrentAntiAddtionTimeCount = nOnlineTime / nIntervalTime;

    // 判断是否需要新的提交
    if ( nCurrentAntiAddtionTimeCount > _nAntiAddtionTimeCount )
    { // 需要新的提交
        // 得到差几个
        uint32 nCount = nCurrentAntiAddtionTimeCount - _nAntiAddtionTimeCount;

        // 需要提交给平台保存的时间
        uint32 nNeedSaveTime = nCount * nIntervalTime;

        // 加上提交的
        _nAntiAddtionTimeCount += nCount;

        // 发消息给CenterServer
        GS2CSUpdateAntiaddictionInfoReq xUpdateAntiaddiction;
        xUpdateAntiaddiction.nType      = GS2CSUpdateAntiaddictionInfoReq::EUpdateReqType_Update;
        xUpdateAntiaddiction.nAccountId = GetAccountID();
        strncpy_s( xUpdateAntiaddiction.passport, sizeof(xUpdateAntiaddiction.passport), GetAccount(), sizeof(xUpdateAntiaddiction.passport)-1);
        xUpdateAntiaddiction.nDuration = nNeedSaveTime;
        GettheServer().SendMsgToCenterServer( &xUpdateAntiaddiction );

        Log("GS2CSUpdateAntiaddictionInfoReq(%d:%u)", xUpdateAntiaddiction.nType, nNeedSaveTime );
    }
}

void GamePlayer::ExitSaveAntiAddiction()
{
    // 是否要进行防沉迷逻辑
    if ( !IsRunAntiAddiction())
    { return; }

    uint16 nIntervalTime = g_Cfg.nAntiAddictionSaveTime;
    if ( nIntervalTime == 0)
    { nIntervalTime = 10; }

    int nLeftMinute = GetOnlineRealTime() / OneMinuteSecond - _nAntiAddtionTimeCount * nIntervalTime;
    if ( nLeftMinute < 0 )
    { return; }

    // 发消息给CenterServer
    GS2CSUpdateAntiaddictionInfoReq xUpdateAntiaddiction;
    xUpdateAntiaddiction.nType      = GS2CSUpdateAntiaddictionInfoReq::EUpdateReqType_Exit;
    xUpdateAntiaddiction.nAccountId = GetAccountID();
    strncpy_s( xUpdateAntiaddiction.passport, sizeof(xUpdateAntiaddiction.passport), GetAccount(), sizeof(xUpdateAntiaddiction.passport)-1);
    xUpdateAntiaddiction.nDuration = nLeftMinute;
    GettheServer().SendMsgToCenterServer( &xUpdateAntiaddiction );

    Log("GS2CSUpdateAntiaddictionInfoReq(%d:%u)", xUpdateAntiaddiction.nType, nLeftMinute );
}

AntiAddictionState GamePlayer::CalcAntiAddictionStatus( uint32 totalTime )
{
    AntiAddictionState state = enumAntiAddictionStateNormal;

    if ( g_Cfg.bIsOpenAntiAddiction &&  _bNeedAntiAddiction )
    {
        if ( totalTime >= g_Cfg.xAntiAddictionInfo._normal._playTime && totalTime < g_Cfg.xAntiAddictionInfo._tired._playTime )
        { state = enumAntiAddictionStateTired; }
        else if ( totalTime >=  g_Cfg.xAntiAddictionInfo._tired._playTime )
        { state = enumAntiAddictionStateRest; }
    }

    return state;
}

uint32 GamePlayer::GetAntiAddictionLimitTime( uint8 nAntiAddictionStatus )
{
    switch ( nAntiAddictionStatus )
    {
    case enumAntiAddictionStateTired:
        return g_Cfg.xAntiAddictionInfo._normal._playTime;
        break;
    case enumAntiAddictionStateRest:
        return g_Cfg.xAntiAddictionInfo._tired._playTime;
        break;
    }
    return 0;
}

uint32 GamePlayer::GetAntiAddictionOnlineTime()
{
    // 累积在线时长单位分钟
    int nDurantionTime = GetOnlineRealTime() / OneMinuteSecond - _nHaveSaveAntiAddtionDuration;
    if ( nDurantionTime < 0)
    { nDurantionTime = 0; }

    return gTransferRuntimeInfo.nAntiAddictionDbOnlineTime + nDurantionTime;
}

void GamePlayer::ResetAntiAddictionNotifyIndex()
{
    _nAntiAddtionStatusChangeStamp = TimeEx::GetCurrentTime().GetTime();
    _nAntiAddtionNotifyIndex = 0;

	if (CHARACTERSERVERID != g_Cfg.dwServerID&&g_Cfg.bIsOpenAntiAddiction)
	{
		uint32 nNotifyInterval = 60;
		uint32 nPlayTime = 0;//上一个状态的持续时间
		switch ( gTransferRuntimeInfo.nAntiAddicationStatus )
		{
		case enumAntiAddictionStateNormal:
			{ 
				nNotifyInterval = g_Cfg.xAntiAddictionInfo._normal._notifyTime; 
				nPlayTime		= 0; 
			}
			break;
		case enumAntiAddictionStateTired:
			{ 
				nNotifyInterval = g_Cfg.xAntiAddictionInfo._tired._notifyTime; 
				nPlayTime		= g_Cfg.xAntiAddictionInfo._normal._playTime;
			}
			break;
		case enumAntiAddictionStateRest:
			{ 
				nNotifyInterval = g_Cfg.xAntiAddictionInfo._rest._notifyTime; 
				nPlayTime		= g_Cfg.xAntiAddictionInfo._tired._playTime;
			}
			break;
		}

		// 得到经过第一个间隔
		uint16 nIntervalCount = (GetAntiAddictionOnlineTime() - nPlayTime) / nNotifyInterval;
		_nAntiAddtionNotifyIndex = nIntervalCount;
	}
}

void GamePlayer::SendMsgWallowAbout( uint8 nType )
{
    MsgWallowAbout msg;
    msg.header.stID = GetID();
    msg.nType       = nType;
    msg.nStatus     = gTransferRuntimeInfo.nAntiAddicationStatus;
    msg.nOnlineTime = GetAntiAddictionOnlineTime();
    msg.nLimitTime  = GetAntiAddictionLimitTime( msg.nStatus );
    SendMessageToClient( &msg );
} 

bool GamePlayer::IsRunAntiAddiction()
{
    // 在选人服务器不需要Update
    if ( CHARACTERSERVERID == g_Cfg.dwServerID )
    { return false; }

    // 如果还没有拿到防沉迷的配置就不Update
    if ( !g_Cfg.bHaveGetAntiAddictionInfoConfig)
    { return false; }

    // 如果不需要防沉迷没有开启就不Update
    if ( !g_Cfg.bIsOpenAntiAddiction )
    { return false; }

    // 如果玩家自身还没有拿到Account沉迷信息不Update
    if ( !gTransferRuntimeInfo.bGetAntiAddictionInfo)
    { return false; }

    // 如果玩家是成年人 也不需要Update
    if ( !_bNeedAntiAddiction )
    { return false; }

    return true;
}
