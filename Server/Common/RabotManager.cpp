#include "RabotManager.h"
#include "ShareData.h"
#include "GamePlayer.h"

unsigned short CheckData::Update( unsigned int dwCurrentTime )
{
    unsigned short ustResult = RabotDefine::EGP_DoNothing;

    switch ( GetCheckStatus() )
    {
    case RabotDefine::EGP_CheckFirstTime: // 第一次验证,
        {
            SetCheckStatus( RabotDefine::EGP_WaitSendCode );
            StartOperateTimer( dwCurrentTime, 5000 );
        }
        break;
    case RabotDefine::EGP_CheckStatusInit:    // 初始阶段
        {
            SetCheckStatus( RabotDefine::EGP_WaitSendCode );
            StartOperateTimer( dwCurrentTime, RabotDefine::EGP_CheckSpaceTime );
        }
        break;
    case RabotDefine::EGP_WaitSendCode:       // 等待发送
        {
            if ( !m_xOperateTimer.DoneTimer() )
            { return ustResult; }

            SetRightResult( RabotDefine::EGP_InitResult );
            ustResult = RabotDefine::EGP_SendCheckCode;
        }
        break;
    case RabotDefine::EGP_WaitCheckResult:    // 等待验证
        {
            if ( !m_xOperateTimer.DoneTimer() )
            { return ustResult; }

            ++m_uchTimeOutCount;
            if ( m_uchTimeOutCount >= RabotDefine::EGP_ResultTimeOutCount )
            {
                m_uchTimeOutCount = 0;
                SetCheckStatus( RabotDefine::EGP_CheckStatusInit );
                ustResult = RabotDefine::EGP_KickPlayer;
            }
            else
            {
                SetCheckStatus( RabotDefine::EGP_CheckFirstTime );    // 没有回 马上再验证一次
            }
        }
        break;
    default:
        Initialize();
        break;
    }

    return ustResult;
}

template<>
GamePlayer* RabotManager< GamePlayer >::GetPlayerByID( unsigned int nPlayerID )
{
    return theRunTimeData.GetGamePlayerByDBID( nPlayerID );
}