#include "GamePlayer.h"
#include "PasswordMessage.h"
#include "PasswordDefine.h"
#include "GlobalFunction.h"

bool GamePlayer::ProcessPasswordMsg(Msg* pMsg)
{
    DWORD dwType = pMsg->GetType();

    GAMESERVER_MESSAGE_MAPPING_BEGIN
        GAMESERVER_MESSAGE_HANDLE( MSG_SETSECONDPASSWORDREQ,              OnMsgSetSecondPasswordReq          )
        GAMESERVER_MESSAGE_HANDLE( MSG_RESETSECONDPASSWORDREQ,            OnMsgReSetSecondPasswordReq        )
        GAMESERVER_MESSAGE_HANDLE( MSG_CLEARSECONDEPASSWORDREQ,           OnMsgClearSecondPasswordReq        )
        GAMESERVER_MESSAGE_HANDLE( MSG_CHECKSECONDPASSWORDACK,            OnMsgCheckSecondPasswordAck        )
        GAMESERVER_MESSAGE_HANDLE( MSG_SETPROTECTREQ,                     OnMsgPasswordSetProtectReq         )
        GAMESERVER_MESSAGE_HANDLE( MSG_CHANGEPROTECTREQ,                  OnMsgChangeProtectReq              )
    GAMESERVER_MESSAGE_MAPPING_END
    return false;
}

void GamePlayer::OnMsgSetSecondPasswordReq( Msg* pMsg )
{
    MsgSetSecondPasswordReq* pReq = static_cast< MsgSetSecondPasswordReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    MsgSetSecondPasswordAck xAck;
    if ( gCharInfoServer.otherdata.xSecondPassword.HavePassword() )
    {
        xAck.uchResult = MsgSetSecondPasswordAck::AlreadyHavePassword;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    if ( !gCharInfoServer.otherdata.xSecondPassword.SetPassword( pReq->szPassword ) )
    {
        xAck.uchResult = MsgSetSecondPasswordAck::PasswordFormatError;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }
    // 设置第一位为1，也就是保护仓库物品，以后应该是从财产保护中选择
    gCharInfoServer.otherdata.xSecondPassword.SetProtectFlag(1<<PasswordDefine::EProtect_OpenStorage);

    xAck.uchResult = MsgSetSecondPasswordAck::SetPasswordSuccess;
    GettheServer().SendMsgToSingle( &xAck, this );
}

void GamePlayer::OnMsgReSetSecondPasswordReq( Msg* pMsg )
{
    MsgReSetSecondPasswordReq* pReq = static_cast< MsgReSetSecondPasswordReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    HelperFunc::CheckStringValid( pReq->szOldPassword, sizeof( pReq->szOldPassword ) );        // 校验字符串

    MsgSetSecondPasswordAck xAck;
    if ( !gCharInfoServer.otherdata.xSecondPassword.CheckPassword( pReq->szOldPassword ) )
    {
        xAck.uchResult = MsgSetSecondPasswordAck::OldPasswordError;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    if ( !gCharInfoServer.otherdata.xSecondPassword.SetPassword( pReq->szNewPassword ) )
    {
        xAck.uchResult = MsgSetSecondPasswordAck::PasswordFormatError;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }

    gCharInfoServer.otherdata.xSecondPassword.SetHaveCheck( false );    // 需要重新验证
    xAck.uchResult = MsgSetSecondPasswordAck::ReSetPasswordSuccess;
    GettheServer().SendMsgToSingle( &xAck, this );
}

// 清除密码
void GamePlayer::OnMsgClearSecondPasswordReq( Msg* pMsg )
{
    if ( !gCharInfoServer.otherdata.xSecondPassword.HavePassword() )
    { 	
	return; 
	} // 没有密码 或者已经强制解除了

	if ( gCharInfoServer.otherdata.xSecondPassword.GetRemoveTime() != 0 )
	{
		MsgClearSecondPasswordAck xAck;
		xAck.uchResult = MsgClearSecondPasswordAck::BUnchaining;
		TimeEx xCurrent = TimeEx::GetCurrentTime();
		TimeEx xDest( gCharInfoServer.otherdata.xSecondPassword.GetRemoveTime() );
		TimeSpan xSpan = xDest - xCurrent;
		xAck.spareTime = xSpan.GetTimeSpan();
		GettheServer().SendMsgToSingle( &xAck, this );
		return;
	}

    TimeEx xCurrentTime = TimeEx::GetCurrentTime();

    DWORD dwTime = PasswordDefine::ClearSecondPasswordTime * 24 * 3600;
    TimeSpan xSpan( dwTime );

    TimeEx xDestTime = xCurrentTime + xSpan;
    gCharInfoServer.otherdata.xSecondPassword.SetRemoveTime( xDestTime.GetTime() );

    MsgClearSecondPasswordAck xAck;
    GettheServer().SendMsgToSingle( &xAck, this );
}

void GamePlayer::OnMsgCheckSecondPasswordAck( Msg* pMsg )
{
    MsgCheckSecondPasswordAck* pAck = static_cast< MsgCheckSecondPasswordAck* >( pMsg );
    if ( pAck == NULL )
    { return; }

    HelperFunc::CheckStringValid( pAck->szPassword, sizeof( pAck->szPassword ) );

    MsgCheckSecondPasswordResult xResult;
    if ( !gCharInfoServer.otherdata.xSecondPassword.CheckPassword( pAck->szPassword ) )
    {
        xResult.uchResult = MsgCheckSecondPasswordResult::SecondPasswordError;
        GettheServer().SendMsgToSingle( &xResult, this );
        return;
    }

    gCharInfoServer.otherdata.xSecondPassword.SetHaveCheck( true );

    if ( gCharInfoServer.otherdata.xSecondPassword.GetRemoveTime() != 0 )
    {
        gCharInfoServer.otherdata.xSecondPassword.SetRemoveTime( 0 );   // 进入以后 把强制解除取消掉
        xResult.uchResult = MsgCheckSecondPasswordResult::SuccessAndClear;
    }

    GettheServer().SendMsgToSingle( &xResult, this );

    // 验证2级密码后的操作
    ProcessSecondPwdOperator( m_uchOperator );
}

void GamePlayer::OnMsgPasswordSetProtectReq( Msg* pMsg )
{
    MsgSetProtectAck xAck;
    if ( !gCharInfoServer.otherdata.xSecondPassword.HavePassword() )    // 没有密码
    {
        xAck.nResult = PasswordDefine::ESetProtect_NonePassword;
        GettheServer().SendMsgToSingle( &xAck, this );
        return;
    }
    // 请求打开设置保护窗口，如果已经验证过了，则打开，否则请求密码
    if ( !ProcessSecondPasswordOperate( PasswordDefine::EProtectFlagInit, PasswordDefine::OP_SetProtect ) )
    { return; }
        
    xAck.nResult = PasswordDefine::ESetProtect_PasswordSucc;
    xAck.nProtectFlag = gCharInfoServer.otherdata.xSecondPassword.GetProtectFlag();
    GettheServer().SendMsgToSingle( &xAck, this );
}

void GamePlayer::OnMsgChangeProtectReq(Msg* pMsg)
{
    MsgChangeProtectReq* pReq = static_cast<MsgChangeProtectReq *>(pMsg);
    if (pReq == NULL)
    { return;}

    gCharInfoServer.otherdata.xSecondPassword.SetProtectFlag(pReq->nProtectFlag);
}

bool GamePlayer::CheckCanOperator( unsigned int nFlag, unsigned char uchOperate )
{// 检查物品是否可操作
    if ( !gCharInfoServer.otherdata.xSecondPassword.HavePassword() || gCharInfoServer.otherdata.xSecondPassword.GetHaveCheck() )
    { return true; }

    if ( nFlag != PasswordDefine::EProtectFlagInit )
    {
        if ( BitValue< unsigned int >::GetBitValue( nFlag, gCharInfoServer.otherdata.xSecondPassword.GetProtectFlag() ) != BitValue< unsigned int >::HaveValue )
        { return true; }
    }

    CheckRemoveSecondPassword();

    // 发送验证2级密码请求
    MsgCheckSecondPasswordReq xReq;
    if ( gCharInfoServer.otherdata.xSecondPassword.GetRemoveTime() != 0 )
    {
        TimeEx xCurrent = TimeEx::GetCurrentTime();
        TimeEx xDest( gCharInfoServer.otherdata.xSecondPassword.GetRemoveTime() );
        TimeSpan xSpan = xDest - xCurrent;

        xReq.nClearPasswordLeftTime = xSpan.GetTimeSpan();
    }
    SendMessageToClient( &xReq );

    //  保存操作类型
    m_uchOperator = uchOperate;    
    return false;
}

bool GamePlayer::ProcessSecondPasswordOperate( unsigned int nFlag, unsigned char uchOperate )
{
    if ( !CheckCanOperator( nFlag, uchOperate ) )
    { return false; }
    
    ProcessSecondPwdOperator( uchOperate );
    
    return true;
}

void GamePlayer::ProcessSecondPwdOperator( unsigned char uchOperate )
{
    switch ( uchOperate )
    {
    case PasswordDefine::OP_OpenStorage:
        {
            MsgUpdateStorage xUpdate;
            xUpdate.SetCompress();
            xUpdate.header.stID = GetID();
            xUpdate.stStorage   = _StorageBag;
            xUpdate.nNpcId      = GetScirptNpc();;
            SendMessageToClient( &xUpdate );
        }
        break;
    case PasswordDefine::OP_OpenMountStorage:
        {
            MsgUpdateMountStorage xUpdate;
            xUpdate.header.stID = GetID();
            memcpy(xUpdate.xStorageMounts,_StorageBag.xStorageMounts, sizeof(_StorageBag.xStorageMounts));
            SendMessageToClient( &xUpdate );
        }
        break;
    case PasswordDefine::OP_HandleAuction:
        {
            OpenConsignmentMoneyWindow();   // 打开金锭寄售窗口
        }
        break;
    default:
        break;
    }
}

