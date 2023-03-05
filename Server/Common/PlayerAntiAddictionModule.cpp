#include "GamePlayer.h"
#include "Configure.h"

void GamePlayer::UpdateAntiAddiction()
{
    // �Ƿ�Ҫ���з������߼�
    if ( !IsRunAntiAddiction())
    { return; }

    // ״̬�仯�߼� ÿһ���ӽ���һ��
    if ( !_xUpdateAntiAddictionTimer.DoneTimer( HQ_TimeGetTime() ))
    { return; }

    // �ۻ�����ʱ����λ����
    uint32 nTotalOnlineTime = GetAntiAddictionOnlineTime();
    AntiAddictionState curState = CalcAntiAddictionStatus( nTotalOnlineTime );

    if ( curState != gTransferRuntimeInfo.nAntiAddicationStatus )
    { // ��״̬�ı�

        Log("Antiaddiction change status from [%d->%d] %d ", gTransferRuntimeInfo.nAntiAddicationStatus, curState, GetAntiAddictionOnlineTime() );

        // �����µ�ʱ��
        gTransferRuntimeInfo.nAntiAddicationStatus = curState;

        // ��ֵ״̬�仯��ļ���
        ResetAntiAddictionNotifyIndex();

        // ����Ϣ֪ͨ�ͻ��˱仯
        SendMsgWallowAbout( MsgWallowAbout::ENotifyType_StatusChange);
    }

    // ֪ͨ��ʾ�ͻ���
    UpdateAntiAddictionNotify();

    // ������ƽ̨
    UpdateSaveAntiAddiction();
}


void GamePlayer::UpdateAntiAddictionNotify()
{
    // �ۻ�����ʱ����λ����
    TimeEx xCurrentTime = TimeEx::GetCurrentTime();

    if ( 0 == _nAntiAddtionStatusChangeStamp )
    { _nAntiAddtionStatusChangeStamp = xCurrentTime.GetTime(); }

    TimeEx xStartTime( _nAntiAddtionStatusChangeStamp );    
    if ( xStartTime > xCurrentTime )
    { _nAntiAddtionStatusChangeStamp = xCurrentTime.GetTime(); }

    // �õ������ķ�����
    TimeSpan xTimeSpan = TimeEx::GetCurrentTime() - xStartTime; 
    int nDurantionTime = xTimeSpan.GetTotalSeconds() / OneMinuteSecond;

    uint32 nNotifyInterval = 60;
	uint32 nPlayTime = 0;//��һ��״̬�ĳ���ʱ��
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

    // �õ�������һ�����
    uint16 nIntervalCount = (GetAntiAddictionOnlineTime() - nPlayTime) / nNotifyInterval;
    if ( nIntervalCount > _nAntiAddtionNotifyIndex )
    {
        // ����Ϣ֪ͨ�ͻ��˱仯
        SendMsgWallowAbout( MsgWallowAbout::ENotifyType_TimerNotify );

        //++_nAntiAddtionNotifyIndex; // ������һ��
		_nAntiAddtionNotifyIndex = nIntervalCount;
    }
}

void GamePlayer::UpdateSaveAntiAddiction()
{
    // ��ʱ�� ���Ѽ��ʱ���ύ��ƽ̨�� gTransferRuntimeInfo.nOnlineTimeAntiAddiction ��Ϊ����ʱ�� _nAntiAddictionDurationTime Ϊ�ۼ��ύ��ʱ��
    uint32 nOnlineTime = GetOnlineRealTime() / OneMinuteSecond;

    // �ύ�������
    uint16 nIntervalTime = g_Cfg.nAntiAddictionSaveTime;
    if ( nIntervalTime == 0)
    { nIntervalTime = 10; }

    // ����ڼ������ʱ��
    uint32 nCurrentAntiAddtionTimeCount = nOnlineTime / nIntervalTime;

    // �ж��Ƿ���Ҫ�µ��ύ
    if ( nCurrentAntiAddtionTimeCount > _nAntiAddtionTimeCount )
    { // ��Ҫ�µ��ύ
        // �õ����
        uint32 nCount = nCurrentAntiAddtionTimeCount - _nAntiAddtionTimeCount;

        // ��Ҫ�ύ��ƽ̨�����ʱ��
        uint32 nNeedSaveTime = nCount * nIntervalTime;

        // �����ύ��
        _nAntiAddtionTimeCount += nCount;

        // ����Ϣ��CenterServer
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
    // �Ƿ�Ҫ���з������߼�
    if ( !IsRunAntiAddiction())
    { return; }

    uint16 nIntervalTime = g_Cfg.nAntiAddictionSaveTime;
    if ( nIntervalTime == 0)
    { nIntervalTime = 10; }

    int nLeftMinute = GetOnlineRealTime() / OneMinuteSecond - _nAntiAddtionTimeCount * nIntervalTime;
    if ( nLeftMinute < 0 )
    { return; }

    // ����Ϣ��CenterServer
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
    // �ۻ�����ʱ����λ����
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
		uint32 nPlayTime = 0;//��һ��״̬�ĳ���ʱ��
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

		// �õ�������һ�����
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
    // ��ѡ�˷���������ҪUpdate
    if ( CHARACTERSERVERID == g_Cfg.dwServerID )
    { return false; }

    // �����û���õ������Ե����þͲ�Update
    if ( !g_Cfg.bHaveGetAntiAddictionInfoConfig)
    { return false; }

    // �������Ҫ������û�п����Ͳ�Update
    if ( !g_Cfg.bIsOpenAntiAddiction )
    { return false; }

    // ����������û���õ�Account������Ϣ��Update
    if ( !gTransferRuntimeInfo.bGetAntiAddictionInfo)
    { return false; }

    // �������ǳ����� Ҳ����ҪUpdate
    if ( !_bNeedAntiAddiction )
    { return false; }

    return true;
}
