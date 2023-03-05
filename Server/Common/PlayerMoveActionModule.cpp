#include "GamePlayer.h"
#include "ShareData.h"
#include "GameTime.h"
#include "GameWorld.h"
#include "LoginStage.h"
#include "mathlib.h"
#include "DBMessageDefine.h"
#include "ServerVarInterface.h"
#include "ScriptKeyword.h"
#include "ScriptCompiler.h"
#include "ItemCharacter.h"
#include "ItemDetail.h"
#include "Helper.h"
#include "ExpStage.h"
#include "NewWithDebug.h"
#include "Configure.h"
#include "FuncPerformanceLog.h"
#include "RouteManager.h"
#include "UserLoger.h"
#include "XmlStringLanguage.h"
#include "MonsterBaseEx.h"
#include "ResourcePath.h"
#include "MeRTLibsServer.h"
#include "MapConfig.h"
#include "TeamManager.h"
#include "EffectChar.h"
#include "GameBlockMap.h"
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

extern CExpStage theExpStage;

#define SENDMOVINGMESSAGERATECONTAIN 250
#define MOVINGCOUNT 32767

int g_nSendMovingMessageRate = 250; //服务器每次下发移动消息的频率

void GamePlayer::OnQueryMove( Msg* pMsg )
{
    // 如果是失去控制状态，则直接返回，不做任何处理。
    //if( m_ExtendStatus.IsLoseControl() )
    //    return; 
    MsgAckMove msg;
    msg.x = GetTileX();
    msg.y = GetTileY();
    msg.header.stID = GetControl()->GetID();
    GettheServer().SendMsgToSingle( &msg, this );
#ifndef SINGLESTEPLOGIC
    SetStatus( CS_IDLE );
#endif
}

void GamePlayer::SendChangeMapMessageToClient( DWORD dwMapId, short nTileX, short nTileY, BYTE byDir, float fDir )
{
    MsgChangeMap msg;
    msg.header.stID = GetID();

    SetMapID( dwMapId );

    // 做纠正
    bool bFix = IsNeedFixWorldCoordinate( nTileX, nTileY );

    SetTileX( nTileX, bFix );
    SetTileY( nTileY, bFix );
    SetFloatZ( WORLD_HEIGHT );               // 设置Z轴, 防止异常 z轴不对
    SetDir( byDir );

    D3DXVECTOR3 vDir = D3DXVECTOR3( cos(fDir), sin(fDir), 0.0f );
    D3DXVec3Normalize( &vDir, &vDir );
    SetDirX( vDir.x );
    SetDirY( vDir.y );

    msg.dwMapId     = EctypeId2MapId(dwMapId);
    msg.new_map_x   = nTileX;
    msg.new_map_y   = nTileY;
    msg.byDir       = byDir;
    msg.nGameMapId  = GetMapID();
    msg.fX          = GetFloatX();
    msg.fY          = GetFloatY();
    msg.fDirX       = GetDirX();
    msg.fDirY       = GetDirY();

    GettheServer().SendMsgToSingle( &msg, this );

    ResetCheckMoving();
    SetStatus( CS_LOADINGMAP );
}

void GamePlayer::OnQueryDisplayName( Msg *pMsg )
{
    if (pMsg == NULL)
    { return; }

    MsgAckDisplayName msg;
    MsgQueryDisplayName *pMsgTmp = (MsgQueryDisplayName*)pMsg;

    if(pMsgTmp->nWhoId<0)
    { return; }

    msg.header.stID = pMsgTmp->nWhoId;

    BaseCharacter * pChar =(BaseCharacter*)theRunTimeData.GetCharacterByID( pMsgTmp->nWhoId );
    if(pChar==NULL)
        return;

    HelperFunc::SafeNCpy( msg.szDisplayName,pChar->GetCharName(),sizeof(msg.szDisplayName) );
    GettheServer().SendMsgToSingle( &msg, this );
}

void GamePlayer::OnGetLag( Msg* pMsg )
{
    MsgGetLag msg;
    msg.header.stID = GetID();
    GettheServer().SendMsgToSingle( &msg, this );
}

bool GamePlayer::IsCanSwitchStage()
{
    if( m_bDeathAndWaitForRelive )
        return false;
    return BaseCharacter::IsCanSwitchStage();
}

void GamePlayer::OnGetPlayerInfo( Msg*pMsg )
{
    MsgGetPlayerInfo*  pGetPlayerInfo = (MsgGetPlayerInfo *)pMsg;
    MsgAckGetPlayerInfo info;
    BaseCharacter* pCPlayer = theRunTimeData.GetGamePlayerByName(pGetPlayerInfo->szPlayerName);
    info.bOnline = false;
    info.stPlayerId = -1;
    strncpy_s(info.szPlayerName, sizeof(info.szPlayerName), pGetPlayerInfo->szPlayerName, sizeof(info.szPlayerName)-1);
    if (NULL != pCPlayer)
    {
        info.bOnline = true;
        info.stPlayerId = pCPlayer->GetID();
    }
    //发消息回去
    GettheServer().SendMsgToSingle( &info, this );
}

void GamePlayer::OnMsgReadytoUseSpecialSkill( Msg*pMsg )
{
    SetStatus( CS_READYTOUSESPEICALSKILL );
    m_ExtendStatus.EnterActionStatus(10000);

    MsgAgreeReadytoUseSpecialSkill agreereadytousespecialskill;
    agreereadytousespecialskill.shCurPermillage = 200;
    GettheServer().SendMsgToSingle( &agreereadytousespecialskill, this );
}

void GamePlayer::OnReqChangeDir( const Msg* pMsg )
{
    MsgChangingDir* pChangeDir = (MsgChangingDir*)pMsg;
    SetDirX( pChangeDir->DirX );
    SetDirY( pChangeDir->DirY );
    //SetDir( pChangeDir->byDir );
}

void GamePlayer::OnMsgJump( const Msg* pMsg )
{
    MsgJump *pJump = (MsgJump*)pMsg;
    MsgJump jump;
    jump.header.stID = GetControl()->GetID();
    jump.shJumpActionId = pJump->shJumpActionId;
    GettheServer().SendMsgToView( &jump, GetID(), true );
    IntonateInterrupt( ItemDefine::EIT_Jump, __FUNCTION__ );
}

// 拔出武器的消息
void GamePlayer::OnMsgDrawWeapon( const Msg* pMsg )
{
    m_ucCharStatus = MsgPlayerEnterMySight::charstatus_normal_draw;
    MsgDrawWeapon draw;
    draw.header.stID = GetControl()->GetID();
    GettheServer().SendMsgToView( &draw, GetID(), true );
}

// 收起武器的消息
void GamePlayer::OnMsgDrawInWeapon( const Msg* pMsg )
{
    m_ucCharStatus = MsgPlayerEnterMySight::charstatus_normal_drawin;
    MsgDrawInWeapon drawin;
    drawin.header.stID = GetControl()->GetID();
    GettheServer().SendMsgToView( &drawin, GetID(), true );
}

void GamePlayer::OnMsgIntonateInterrupt( const Msg* pMsg )
{
    IntonateInterrupt( ItemDefine::EIT_Msg, __FUNCTION__ );
}

void GamePlayer::IntonateInterrupt( int8 nType, char* szCallFun )
{
    if ( _SkillTaskManager.IsTaskEmpty() )
    { return; }

    switch( GetStatus() )
    {
    case CS_INTONATE:
        {
            SetStatus( CS_IDLE );
            //发送吟唱中断的信息
            Msg_IntonateInterrupt IntonateInterrupt_msg;
            IntonateInterrupt_msg.header.stID = GetID();
            IntonateInterrupt_msg.nSkillID    = _SkillTaskManager.DoneCurTask();
            GettheServer().SendMsgToSingle( &IntonateInterrupt_msg, this );
            Msg_SkillCanceld cancel;
            cancel.header.stID = GetID();
            GettheServer().SendMsgToView( &cancel, GetID(), false );
        }
        break;
    case CS_HOLDSKILL:
        {  
            if ( !m_ContinuousSkill.bMoveInterrupt )
            { return; }

            SetStatus( CS_IDLE );
            if( m_ContinuousSkill.pEffectChar )
            {
                m_ContinuousSkill.pEffectChar->CriticalError(__FUNCTION__, __FILE__, __LINE__);
                m_ContinuousSkill.pEffectChar = 0;
            }
            m_ContinuousSkill.dwTimeSkillHoldingEnd = 0; 
            //表示当前任务完成了
            int nSkillID = _SkillTaskManager.DoneCurTask();    

            Msg_IntonateInterrupt IntonateInterrupt_msg;
            IntonateInterrupt_msg.header.stID = GetID();
            IntonateInterrupt_msg.nSkillID = nSkillID;
            GettheServer().SendMsgToSingle( &IntonateInterrupt_msg, this );

            Msg_SkillCanceld cancel;
            cancel.header.stID = GetID();
            GettheServer().SendMsgToView( &cancel, GetID(), false );
        }
        break;
    case CS_LOADINGMAP:
        {
            Msg_IntonateInterrupt IntonateInterrupt_msg;
            IntonateInterrupt_msg.header.stID = GetID();
            IntonateInterrupt_msg.nSkillID    = _SkillTaskManager.DoneCurTask();
            GettheServer().SendMsgToSingle( &IntonateInterrupt_msg, this );

            Msg_SkillCanceld cancel;
            cancel.header.stID = GetID();
            GettheServer().SendMsgToSingle( &cancel, this );
        }
        break;
    default:
        break;
    }
}

//void GamePlayer::OnMsgPlayerMoving( const Msg* pMsg )
//{
//    if(!m_cFightStatus.IsCanMove())
//        return;
//
//    MsgPlayerMoving *pmovepasspos = (MsgPlayerMoving*)pMsg;
//
//    float fx = pmovepasspos->vPos.x;
//    float fy = pmovepasspos->vPos.y;
//    float fz = pmovepasspos->vPos.z;
//    float fdirx = pmovepasspos->vDir.x;
//    float fdiry = pmovepasspos->vDir.y;

//    m_shLastSavedMovingType = pmovepasspos->shMovingType;
//
//    if( m_bSentVerifyPosMsg )
//    {
//        m_dwStartReadytoSendVerifyPosMsgTime = g_dwLastWorldProcessTime;
//        m_bSentVerifyPosMsg = FALSE;
//    }
//
//    if( fx != GetFloatX() || fy != GetFloatY() )
//    {
//        if( GetStatus() == CS_INTONATE )
//        {
//            //发送吟唱中断的信息
//            Msg_IntonateInterrupt IntonateInterrupt_msg;
//            IntonateInterrupt_msg.header.stID = GetID();
//            GettheServer().SendMsgToSingle( &IntonateInterrupt_msg, this );
//            _SkillTaskManager.DoneCurTask();
//        }
//        SetStatus( CS_WALK );
//        _SkillTaskManager.DoneCurTask();
//        m_bMoving = TRUE;
//    }
//
//
//    SetX( fx );
//    SetY( fy );
//    SetZ( fz );
//    SetDirX( fdirx );
//    SetDirY( fdiry );
//    SetLastReceiveMoveMessageTime( g_dwLastWorldProcessTime );
//
//    if( !CheckMoving() && KICK_CREDIT)
//    {
//        SetX( m_vStartMovingPosPerCheck.x );
//        SetY( m_vStartMovingPosPerCheck.y );
//        SetZ( m_vStartMovingPosPerCheck.z );
//        Log("玩家[%s]移动信息监测不合法 将其强行踢下线", GetCharName(), m_nCredit );
//        CriticalError(__FUNCTION__, __FILE__, __LINE__);
//        return;
//    }
//
//    //theGameWorld.OnRefreshNewArea( GetID() );
//
//    //if( g_dwLastWorldProcessTime - m_dwLastSendPlayerMovingMsgTime > m_dwSendPlayerMovingMsgRate )
//    {
//        MsgPlayerVerifyPos msg;
//        msg.header.stID = GetID();
//        msg.vPos.x = GetFloatX();
//        msg.vPos.y = GetFloatY();
//        msg.vPos.z = GetFloatZ();
//        //msg.vDir.x = GetDirX();
//        //msg.vDir.y = GetDirY();
//        //msg.vDir.z = 0;
//        //msg.shMovingType = m_shLastSavedMovingType;
//
//        GettheServer().SendMsgToView( &msg, GetID(), true );
//        //m_dwLastSendPlayerMovingMsgTime = g_dwLastWorldProcessTime;
//    }
//}

// 提交一个移动合法性分析请求消息
void GamePlayer::ReqPlayerMoveAnalysis( D3DXVECTOR3& posMoveTo )
{
	PlayerMoveAnalysis::ReqAnalysisMsg req;
	req.nAccountID = GetAccountID();
	strncpy_s( req.szLoginName, sizeof(req.szLoginName), GetAccount(), sizeof(req.szLoginName)-1);
	req.nChaDBID = GetDBCharacterID();
	req.nID = GetID();
	req.nMapID = EctypeId2MapId( GetMapID() );
	strncpy_s( req.szCharName, sizeof(req.szCharName), GetCharName(), sizeof(req.szCharName)-1);
	/*strncpy_s( req.szSessionKey, sizeof(req.szSessionKey), GetSessionKey(), sizeof(req.szSessionKey)-1);*/
	req.SessionKey = GetSessionKey();
	req.vOldPos = GetPos();
	req.vNewPos = posMoveTo;
	GetPlayerMoveAnalysis().AddReqAnalysisMsg( req );
}

void GamePlayer::OnMsgPlayerMovingPos( const Msg* pMsg )
{
    if(!_buffManager.IsCanMove())
        return;

    //if (g_Cfg.bAntiPluginOpen && !m_graphiccodecheck.IsCanMove())
    //{
    //    this->SendVerifyPos(GetFloatX(), GetFloatY());
    //    ShowInfo(false, 1000, 0xffff0000, theXmlString.GetString(eClient_AddInfo_2slk_49));
    //    return;
    //}

    MsgPlayerMovingPosToServer* pMsg1 = (MsgPlayerMovingPosToServer*)pMsg;

    // 测试移动消息发送的频率
    CheckMovingMsgSendTime( pMsg1->dwSendTime );

    float fx = pMsg1->vPos.x;
    float fy = pMsg1->vPos.y;
    float fz = pMsg1->vPos.z;

	// 提交一个移动合法性分析请求消息
	ReqPlayerMoveAnalysis( D3DXVECTOR3( fx, fy, fz ) );

    if( fx != GetFloatX() || fy != GetFloatY() )
    {
        OnHaveStatusDisplacement();
        if ( IsCurrentTaskCanBeInterrupt( ItemDefine::EIT_Move ) )
        { IntonateInterrupt( ItemDefine::EIT_Move, __FUNCTION__ ); }

        SetMoveStatus( CS_WALK );
    }

    m_vMovingBufPerCheck.x += abs( fx - GetFloatX() );
    m_vMovingBufPerCheck.y += abs( fy - GetFloatY() );

    SetFloatXF( fx );
    SetFloatYF( fy );
    SetFloatZ( fz );
    SetLastReceiveMoveMessageTime( theGameWorld.g_dwLastWorldProcessTime );

    MsgPlayerMovingPos msg;
    msg.header.stID = GetID();
    msg.vPos.x = GetFloatX();
    msg.vPos.y = GetFloatY();
    msg.vPos.z = GetFloatZ();
    GettheServer().SendMsgToView( &msg, GetID(), true );

    m_bMoving = true;
	if (m_bAttackLockChar)
	{
		SetAttackLockCharState(false);
	}

    if (m_bPosDebugOpen)
    {
        char szBuffer[100];
        sprintf_s(szBuffer, sizeof(szBuffer)-1, "X: %f Y: %f Z: %f", this->GetFloatX(), this->GetFloatY(), this->GetFloatZ());
        TellClient(szBuffer);
    }

    if( pMsg1->bNeedChangeMap == 1 )
    {
        int nResult = TryRespondChangeStage();
        //Log( "请求触发跳转 OnMsgPlayerMovingPos TryRespondChangeStage Result[%d]", nResult );
		Log( theXmlString.GetString(eServerLog_QingQiuTiaoZhuan), nResult );
    }

    // 多人坐骑移动
    _mountManager.OnMultiMountMoving();
}

void GamePlayer::OnMsgPlayerMovingPosToDir( const Msg* pMsg )
{
    if(!_buffManager.IsCanMove())
    {
        TellClient( theXmlString.GetString(eClient_AddInfo_2slk_78) );
        return;
    }

    //if (g_Cfg.bAntiPluginOpen && !m_graphiccodecheck.IsCanMove())
    //{
    //    this->SendVerifyPos(GetFloatX(), GetFloatY());
    //    ShowInfo(false, 1000, 0xffff0000, theXmlString.GetString(eClient_AddInfo_2slk_49));
    //    return;
    //}

    MsgPlayerMovingPosAndDirToServer* pMsg1 = (MsgPlayerMovingPosAndDirToServer*)pMsg;

    CheckMovingMsgSendTime( pMsg1->dwSendTime );

    float fx = pMsg1->vPos.x;
    float fy = pMsg1->vPos.y;
    float fz = pMsg1->vPos.z;

    D3DXVECTOR3 vDir = D3DXVECTOR3( pMsg1->chDirX, pMsg1->chDirY, pMsg1->chDirZ );
    D3DXVec3Normalize( &vDir, &vDir );

    float fdirx = vDir.x;
    float fdiry = vDir.y;

    if( fx != GetFloatX() || fy != GetFloatY() )
    {
        OnHaveStatusDisplacement();
        if ( IsCurrentTaskCanBeInterrupt( ItemDefine::EIT_Move ) )
        { IntonateInterrupt( ItemDefine::EIT_Move, __FUNCTION__ ); }
        SetMoveStatus( CS_WALK );
        m_bMoving = true;
		if (m_bAttackLockChar)
		{
			SetAttackLockCharState(false);
		}
    }

    m_vMovingBufPerCheck.x += abs( fx - GetFloatX() );
    m_vMovingBufPerCheck.y += abs( fy - GetFloatY() );

    SetFloatXF( fx );
    SetFloatYF( fy );
    SetFloatZ( fz );
    SetDirX( fdirx );
    SetDirY( fdiry );
    SetLastReceiveMoveMessageTime( theGameWorld.g_dwLastWorldProcessTime );

    MsgPlayerMovingPosAndDir msg;
    msg.header.stID = GetID();
    msg.vPos.x = GetFloatX();
    msg.vPos.y = GetFloatY();
    msg.vPos.z = GetFloatZ();
    msg.chDirX = pMsg1->chDirX;
    msg.chDirY = pMsg1->chDirY;
    msg.chDirZ = pMsg1->chDirZ;
    GettheServer().SendMsgToView( &msg, GetID(), true );

    m_bMoving = true;
	if (m_bAttackLockChar)
	{
		SetAttackLockCharState(false);
	}

    //如果打开了调试信息则返回确认的坐标
    if (m_bPosDebugOpen)
    {
        char szBuffer[100];
        sprintf_s(szBuffer, sizeof(szBuffer)-1, "X: %f Y: %f Z: %f", this->GetFloatX(), this->GetFloatY(), this->GetFloatZ());
        TellClient(szBuffer);
    }

    if( pMsg1->bNeedChangeMap == 1 )
    {
        int nResult = TryRespondChangeStage();
       // Log( "请求触发跳转 OnMsgPlayerMovingPosToDir TryRespondChangeStage Result[%d]", nResult );
		Log( theXmlString.GetString(eServerLog_QingQiuTiaoZhuan1), nResult );
    }

    // 多人坐骑移动
    _mountManager.OnMultiMountMoving();
}

void GamePlayer::OnMsgPlayerPos( const Msg* pMsg )
{
    if(!_buffManager.IsCanMove())
    {
        //ShowInfo( false, 1000, 0xffff0000, "当前状态不能移动" );
        TellClient( theXmlString.GetString(eClient_AddInfo_2slk_78) );
        return;
    }

    //if (g_Cfg.bAntiPluginOpen && !m_graphiccodecheck.IsCanMove())
    //{
    //    this->SendVerifyPos(GetFloatX(), GetFloatY());
    //    ShowInfo(false, 1000, 0xffff0000, theXmlString.GetString(eClient_AddInfo_2slk_49));
    //    return;
    //}

    MsgPlayerPosToServer* pMsg1 = (MsgPlayerPosToServer*)pMsg;

    CheckMovingMsgSendTime( pMsg1->dwSendTime );

    float fx = pMsg1->vPos.x;
    float fy = pMsg1->vPos.y;
    float fz = pMsg1->vPos.z;

    if( fx != GetFloatX() || fy != GetFloatY() )
    {
        OnHaveStatusDisplacement();
        if ( IsCurrentTaskCanBeInterrupt( ItemDefine::EIT_Move ) )
        { IntonateInterrupt( ItemDefine::EIT_Move, __FUNCTION__ ); }
        SetMoveStatus( CS_WALK );
        m_bMoving = true;
		if (m_bAttackLockChar)
		{
			SetAttackLockCharState(false);
		}
    }

    m_vMovingBufPerCheck.x += abs( fx - GetFloatX() );
    m_vMovingBufPerCheck.y += abs( fy - GetFloatY() );

    SetFloatXF( fx );
    SetFloatYF( fy );
    SetFloatZ( fz );
    SetLastReceiveMoveMessageTime( theGameWorld.g_dwLastWorldProcessTime );

    MsgPlayerPos msg;
    msg.header.stID = GetID();
    msg.vPos.x = GetFloatX();
    msg.vPos.y = GetFloatY();
    msg.vPos.z = GetFloatZ();

    GettheServer().SendMsgToView( &msg, GetID(), true );

    m_bMoving = false;

    //如果打开了调试信息则返回确认的坐标
    if (m_bPosDebugOpen)
    {
        char szBuffer[100];
        sprintf_s(szBuffer, sizeof(szBuffer)-1, "X: %f Y: %f Z: %f", this->GetFloatX(), this->GetFloatY(), this->GetFloatZ());
        TellClient(szBuffer);
    }
    if( GetMoveStatus() == CS_WALK )
    { SetMoveStatus( CS_IDLE ); }

    // 多人坐骑移动
    _mountManager.OnMultiMountMoving();
}

void GamePlayer::OnMsgPlayerDir( const Msg* pMsg )
{
    if(!_buffManager.IsCanMove())
    {
        //ShowInfo( false, 1000, 0xffff0000, "当前状态不能移动" );
        TellClient( theXmlString.GetString(eClient_AddInfo_2slk_78) );
        return;
    }

    //if (g_Cfg.bAntiPluginOpen && !m_graphiccodecheck.IsCanMove())
    //{
    //    this->SendVerifyPos(GetFloatX(), GetFloatY());
    //    ShowInfo(false, 1000, 0xffff0000, theXmlString.GetString(eClient_AddInfo_2slk_49));
    //    return;
    //}

    MsgPlayerDirToServer* pMsg1 = (MsgPlayerDirToServer*)pMsg;

    CheckMovingMsgSendTime( pMsg1->dwSendTime );

    D3DXVECTOR3 vDir = D3DXVECTOR3( pMsg1->chDirX, pMsg1->chDirY, pMsg1->chDirZ );
    D3DXVec3Normalize( &vDir, &vDir );

    float fdirx = vDir.x;
    float fdiry = vDir.y;

    SetDirX( fdirx );
    SetDirY( fdiry );
    SetLastReceiveMoveMessageTime( theGameWorld.g_dwLastWorldProcessTime );

    MsgPlayerDir msg;
    msg.header.stID = GetID();
    msg.chDirX = pMsg1->chDirX;
    msg.chDirY = pMsg1->chDirY;
    msg.chDirZ = pMsg1->chDirZ;
    GettheServer().SendMsgToView( &msg, GetID(), true );

    m_bMoving = false;

    //如果打开了调试信息则返回确认的坐标
    if (m_bPosDebugOpen)
    {
        char szBuffer[100];
        sprintf_s(szBuffer, sizeof(szBuffer)-1, "X: %f Y: %f Z: %f", this->GetFloatX(), this->GetFloatY(), this->GetFloatZ());
        TellClient(szBuffer);
    }

    if( GetMoveStatus() == CS_WALK )
    { SetMoveStatus( CS_IDLE ); }

    // 多人坐骑移动
    _mountManager.OnMultiMountMoving();
}

void GamePlayer::OnMsgPlayerPosAndDir( const Msg* pMsg )
{
    if(!_buffManager.IsCanMove())
    {
        //ShowInfo( false, 1000, 0xffff0000, "当前状态不能移动" );
        TellClient( theXmlString.GetString(eClient_AddInfo_2slk_78) );
        return;
    }

    //if (g_Cfg.bAntiPluginOpen && !m_graphiccodecheck.IsCanMove())
    //{
    //    this->SendVerifyPos(GetFloatX(), GetFloatY());
    //    ShowInfo(false, 1000, 0xffff0000, theXmlString.GetString(eClient_AddInfo_2slk_49));
    //    return;
    //}

    MsgPlayerPosAndDirToServer* pMsg1 = (MsgPlayerPosAndDirToServer*)pMsg;

    CheckMovingMsgSendTime( pMsg1->dwSendTime );

    float fx = pMsg1->vPos.x;
    float fy = pMsg1->vPos.y;
    float fz = pMsg1->vPos.z;

    D3DXVECTOR3 vDir = D3DXVECTOR3( pMsg1->chDirX, pMsg1->chDirY, pMsg1->chDirZ );
    D3DXVec3Normalize( &vDir, &vDir );
    float fdirx = vDir.x;
    float fdiry = vDir.y;

    if( fx != GetFloatX() || fy != GetFloatY() )
    {
        OnHaveStatusDisplacement();
        if ( IsCurrentTaskCanBeInterrupt( ItemDefine::EIT_Move ) )
        { IntonateInterrupt( ItemDefine::EIT_Move, __FUNCTION__ ); }
        SetMoveStatus( CS_WALK );
        m_bMoving = true;
		if (m_bAttackLockChar)
		{
			SetAttackLockCharState(false);
		}
    }

    m_vMovingBufPerCheck.x += abs( fx - GetFloatX() );
    m_vMovingBufPerCheck.y += abs( fy - GetFloatY() );

    SetFloatXF( fx );
    SetFloatYF( fy );
    SetFloatZ( fz );
    SetDirX( fdirx );
    SetDirY( fdiry );
    SetLastReceiveMoveMessageTime( theGameWorld.g_dwLastWorldProcessTime );

    MsgPlayerPosAndDir msg;
    msg.header.stID = GetID();
    msg.vPos.x = GetFloatX();
    msg.vPos.y = GetFloatY();
    msg.vPos.z = GetFloatZ();
    msg.chDirX = pMsg1->chDirX;
    msg.chDirY = pMsg1->chDirY;
    msg.chDirZ = pMsg1->chDirZ;
    GettheServer().SendMsgToView( &msg, GetID(), true );

    m_bMoving = false;

    //如果打开了调试信息则返回确认的坐标
    if (m_bPosDebugOpen)
    {
        char szBuffer[100];
        sprintf_s(szBuffer, sizeof(szBuffer)-1, "X: %f Y: %f Z: %f", GetFloatX(), GetFloatY(), GetFloatZ());
        TellClient(szBuffer);
    }

    if( GetMoveStatus() == CS_WALK )
    { SetMoveStatus( CS_IDLE ); }

    // 多人坐骑移动
    _mountManager.OnMultiMountMoving();
}

void GamePlayer::OnQueryCharAround( const Msg* pMsg )
{
    short stRadius = ((MsgQueryCharAround*)pMsg)->stRadius;

    MsgAckCharAround ackMsg;
    ackMsg.stCharCount = 0;
    GameObjectId objectId = InvalidGameObjectId;
    for ( uint32 currentIndex = 0; (objectId = theGameWorld.GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
    {
        BaseCharacter* c = theRunTimeData.GetCharacterByID( objectId );
        if( c && c != this && IsCanBeAttackedObject() )
        {
            if( c->GetMapID() != GetMapID() )continue;
            if( abs( c->GetTileX()-GetTileX() )+abs( c->GetTileY()-GetTileY() ) > stRadius )continue;

            if (ackMsg.stCharCount >= 0 && ackMsg.stCharCount < MAX_ACKCHARAROUND)
            {
                ackMsg.charInfos[ackMsg.stCharCount].stId = objectId;
                ackMsg.charInfos[ackMsg.stCharCount].stType = Object_Player;
                ackMsg.charInfos[ackMsg.stCharCount].x = c->GetTileX();
                ackMsg.charInfos[ackMsg.stCharCount].y = c->GetTileY();
                ackMsg.charInfos[ackMsg.stCharCount].nHp = c->GetHP();
            }
            ackMsg.stCharCount++;

            if( ackMsg.stCharCount >= MAX_ACKCHARAROUND )
                break;

        }
    }
    if( ackMsg.stCharCount > 0 )
    {
        GettheServer().SendMsgToSingle( &ackMsg, this );
    }
}

void GamePlayer::SendVerifyPos()
{
    MsgVerifyPos verify;
    m_cMoveSerial++;

    verify.header.stID = GetID();
    verify.sNpcID      = GetID();
    verify.x           = GetTileX();
    verify.y           = GetTileY();
    verify.cMoveSerial = m_cMoveSerial;
    GettheServer().SendMsgToSingle( &verify, this );
}

void GamePlayer::SendVerifyPos( float fx, float fy )
{
    MsgVerifyPos verify;
    verify.header.stID = GetID();
    verify.sNpcID      = GetID();
    verify.x           = fx;
    verify.y           = fy;
    GettheServer().SendMsgToSingle( &verify, this );
}

bool GamePlayer::IsNeedFixWorldCoordinate( int tileX, int tileY )
{
    if( abs(GetFloatX() - TileToFloat(tileX)) > MAPTILESIZE ||
        abs(GetFloatY() - TileToFloat(tileY)) > MAPTILESIZE )
        return true;

    return false;
}

// 重置要测试的移动信息(开始新一轮的移动测试)
void GamePlayer::ResetCheckMoving()
{
    //m_shMovingCount = 0;
    //m_shCheckMovingIndex = theRand.rand32()%(CHECKMOVINGRATE-10)+10;
    //m_bCheckMovingPerCheck = FALSE;

    m_vStartMovingPosPerCheck.x = GetFloatX();
    m_vStartMovingPosPerCheck.y = GetFloatY();
    m_vStartMovingPosPerCheck.z = 0;
    m_vMovingBufPerCheck.x = 0;
    m_vMovingBufPerCheck.y = 0;
    m_vMovingBufPerCheck.z = 0;
    m_dwClientPassedTimePerCheck = 0;
    m_bAssaultMovingProcess = false;
}

void GamePlayer::OnPingMsg( Msg* pMsg ) 
{   
}

void GamePlayer::TellClient( const char* string, ... )
{
    if( !string )
        return;

    va_list    va;
    char data[1024];
    va_start( va, string );
    wvnsprintf(data, sizeof(data)-1, string, va );
    va_end( va );

#ifdef _DEBUG
    OutputDebugString( data );
#endif // _DEBUG

    MsgChat chat(MsgChat::CHAT_TYPE_GAMEPROMPT);
    chat.header.stID = GetID();
    chat.SetString( data );
    GettheServer().SendMsgToSingle( &chat, this );
}

void GamePlayer::TellClient( unsigned short ustStringID, UnionParam *pParam /* = NULL */, int nCount /* = 0 */ )
{
    if ( ustStringID == InvalidLogicNumber )
    { return; }

    MsgTellClient xTellClient;
    xTellClient.ustStringID = ustStringID;
    xTellClient.CopyParamData( pParam, nCount );

    GettheServer().SendMsgToSingle( &xTellClient, this );
}

void GamePlayer::ShowMsgBox( const char* string, ... )
{
    if( !string )
    { return; }

    va_list va;
    char data[256];
    va_start( va, string );
    wvnsprintf(data, sizeof(data)-1, string, va );
    va_end( va );

    MsgClientShowMsg show;
    show.header.stID = GetID();
    _snprintf(show.szMsg, MsgClientShowMsg::MAXLENGTH-1, string);
    GettheServer().SendMsgToSingle( &show, this );
}

void GamePlayer::ShowInfo( bool bTile, int type, unsigned short ustStringID, UnionParam* pParam /* = NULL */, int nCount /* = 0 */ )
{
    if ( ustStringID == InvalidLogicNumber )
    { return; }

    MsgTellClient xTellClient;
    xTellClient.chType = MsgTellClient::ECD_ShowInfo;
    xTellClient.ustStringID = ustStringID;
    xTellClient.bTile   = bTile;
    //xTellClient.ustTime = time;
    xTellClient.dwShowInfoType = type;
    xTellClient.CopyParamData( pParam, nCount );

    GettheServer().SendMsgToSingle( &xTellClient, this );
}

void GamePlayer::ShowInfo( bool bTile, int type, const char* string, ... )
{
    if( string == NULL || string[0] == 0 )
        return;

    va_list    va;
    char data[512] = {0};
    va_start( va, string );
    wvnsprintf(data, sizeof(data)-1, string, va );
    va_end( va );

    MsgShowText msg;
    msg.header.stID = GetID();
    msg.byAlign = MsgShowText::eAlignMiddle;
    msg.bTile = bTile;
    //msg.dwTime = time;
    msg.nShowInfoType = type;
    strncpy_s( msg.szText, MsgShowText::STRING_LEGTH, data, MsgShowText::STRING_LEGTH-1 );
    GettheServer().SendMsgToSingle( &msg, this );
}

void GamePlayer::ShowInfo( const char* string, bool bTile, int type )
{
    ShowInfo(bTile, type, string);
}

void GamePlayer::ShowFormatInfo( const char* szFormat, ... )
{
    if( szFormat == NULL || szFormat[0] == 0 )
    { return; }

    char szBuf[1024] = {0};
    //转换参数
    va_list vl;
    va_start(vl, szFormat);
    int cnt = vsnprintf(szBuf, sizeof(szBuf)-1, szFormat, vl);
    va_end(vl);
    ShowInfo(szBuf);
}

BOOL GamePlayer::CheckMoving()
{
    return TRUE;

    //if( m_shMovingCount < CHECKMOVINGRATE )
    //{
    //    if( !m_bCheckMovingPerCheck && m_shMovingCount == m_shCheckMovingIndex )
    //    {
    //        m_bCheckMovingPerCheck = TRUE;
    //        D3DXVECTOR3 vOffPos;
    //        vOffPos.x = GetFloatX() - m_vStartMovingPosPerCheck.x;
    //        vOffPos.y = GetFloatY() - m_vStartMovingPosPerCheck.y;
    //        vOffPos.z = 0;
    //        float fDistance = D3DXVec3Length( &vOffPos );
    //        float fMaxDistance = (float)g_nSendMovingMessageRate*0.001f*GetMoveSpeed()*(m_shMovingCount+4);

    //        int nReceiveMovingMsgCastTime = g_nSendMovingMessageRate*(m_shMovingCount+1) - g_nSendMovingMessageRate*3; //本次Check中收这么多信息应花的时间
    //        int nThisCheckCastTime = HQ_TimeGetTime() - m_dwStartMovingTimePerCheck; //本次Check所用的时间
    //        //int nErrorTime = nReceiveMovingMsgCastTime - nThisCheckCastTime; //移动消息发送频率的超标时间
    //        float fErrorDistance = fDistance - fMaxDistance;

    //        //if( nErrorTime > 0 )
    //        //{
    //        //    //char szBuf[256];
    //        //    //_snprintf( szBuf, 256, "fErrorDistance = %f Count = %d Speed = %f",fErrorDistance, m_shMovingCount+1, GetMoveSpeed());
    //        //    //TellClient( szBuf );
    //        //    //_snprintf( szBuf, 256, "MaxDistance = %f time = %d", fMaxDistance, nReceiveMovingMsgCastTime - nThisCheckCastTime );
    //        //    //TellClient( szBuf );

    //        //    m_shMovingErrorCount++;

    //        //    if( nErrorTime > 1000 )
    //        //    {
    //        //        if( nErrorTime > 2000 )
    //        //        {
    //        //            m_nCredit -= 1000;
    //        //            Log("[%s]移动消息发送频率严重超标 超标时间 %d 当前荣誉 %d 当前移动速度 %f", GetCharName(), nErrorTime, m_nCredit, GetMoveRate() );
    //        //        }
    //        //        else
    //        //        {
    //        //            Log("[%s]移动消息发送频率超标 超标时间 %d 当前荣誉 %d 当前移动速度 %f", GetCharName(), nErrorTime, m_nCredit, GetMoveRate() );
    //        //        }
    //        //        m_nCredit -= 1000;
    //        //        m_shMovingErrorCount = 10;
    //        //    }

    //        //    if( m_shMovingErrorCount > 4 )
    //        //    {
    //        //        m_nCredit -= 1000;
    //        //        if( m_nCredit < 5000 )
    //        //        {
    //        //            Log("[%s]移动消息发送频率出错 超标时间 %d 当前荣誉 %d 当前移动速度 %f", GetCharName(), nErrorTime, m_nCredit, GetMoveRate() );
    //        //        }
    //        //        m_shMovingErrorCount = 4;
    //        //    }
    //        //    ResetCheckMoving();
    //        //}

    //        if( fErrorDistance > 0 )
    //        {
    //            //char szBuf[256];
    //            //_snprintf( szBuf, 256, "fErrorDistance = %f Count = %d Speed = %f",fErrorDistance, m_shMovingCount+1, GetMoveSpeed());
    //            //TellClient( szBuf );
    //            //_snprintf( szBuf, 256, "MaxDistance = %f time = %d", fMaxDistance, nReceiveMovingMsgCastTime - nThisCheckCastTime );
    //            //TellClient( szBuf );

    //            //SendVerifyPos( m_vStartMovingPosPerCheck.x, m_vStartMovingPosPerCheck.y );
    //            //SetX(m_vStartMovingPosPerCheck.x);
    //            //SetY(m_vStartMovingPosPerCheck.y);

    //            //m_shMovingCount = 0;
    //            //m_shCheckMovingIndex = theRand.rand32()%(CHECKMOVINGRATE-10)+10;
    //            //m_dwStartMovingTimePerCheck = HQ_TimeGetTime();
    //            //m_bCheckMovingPerCheck = FALSE;
    //            //m_vStartMovingPosPerCheck.x = GetFloatX();
    //            //m_vStartMovingPosPerCheck.y = GetFloatY();
    //            //m_vStartMovingPosPerCheck.z = 0;

    //            m_shMovingErrorCount++;

    //            if( fErrorDistance > 10 )
    //            {
    //                if( fErrorDistance > 20 )
    //                {
    //                    m_nCredit -= 2000;
    //                    if( fErrorDistance > 256 )
    //                    {
    //                        m_nCredit -= 20000;
    //                    }
    //                    Log("[%s]移动距离严重超标 超标距离 %f 当前荣誉 %d 当前移动速度 %f", GetCharName(), fErrorDistance, m_nCredit, GetMoveRate() );
    //                    return FALSE;
    //                }
    //                else
    //                {
    //                    Log("[%s]移动距离超标 超标距离 %f 当前荣誉 %d 当前移动速度 %f", GetCharName(), fErrorDistance, m_nCredit, GetMoveRate() );
    //                }
    //                m_nCredit -= 1000;
    //                m_shMovingErrorCount = 10;
    //            }

    //            if( m_shMovingErrorCount > 4 )
    //            {
    //                m_nCredit -= 1000;
    //                if( m_nCredit < 5000 )
    //                {
    //                    Log("[%s]移动距离非法出错 %d 超标距离 %f 当前荣誉 %d 当前移动速度 %f", GetCharName(), fErrorDistance, m_nCredit, GetMoveRate() );
    //                }
    //                m_shMovingErrorCount = 4;
    //            }
    //            ResetCheckMoving();
    //        }
    //    }
    //    m_shMovingCount++;
    //}
    //else
    //{
    //    ResetCheckMoving();

    //    m_shCheckMovingCount++;
    //    if( m_shCheckMovingCount > 6 )
    //    {
    //        m_shCheckMovingCount = 0;
    //        if( m_shMovingErrorCount > 0 )
    //        {
    //            m_shMovingErrorCount--;
    //        }
    //    }
    //}
    //return TRUE;

    //if( m_shMovingCount < CHECKMOVINGRATE )
    //{
    //    if( !m_bCheckMovingPerCheck && m_shMovingCount == m_shCheckMovingIndex )
    //    {
    //        m_bCheckMovingPerCheck = TRUE;
    //        //D3DXVECTOR3 vOffPos;
    //        //vOffPos.x = GetFloatX() - m_vStartMovingPosPerCheck.x;
    //        //vOffPos.y = GetFloatY() - m_vStartMovingPosPerCheck.y;
    //        //vOffPos.z = 0;
    //        //float fDistance = D3DXVec3Length( &m_vMovingBufPerCheck );

    //        //char szBuf[256];
    //        //_snprintf( szBuf, 256, "MaxDistance = %f %d %d", fDistance, m_shMovingCount, HQ_TimeGetTime() - m_dwStartMovingTimePerCheck );
    //        //TellClient( szBuf );

    //        //float fMaxDistance = (float)g_nSendMovingMessageRate*0.001f*GetMoveSpeed()*(m_shMovingCount+4);

    //        //int nReceiveMovingMsgCastTime = g_nSendMovingMessageRate*(m_shMovingCount+1) - g_nSendMovingMessageRate*3; //本次Check中收这么多信息应花的时间
    //        //int nThisCheckCastTime = HQ_TimeGetTime() - m_dwStartMovingTimePerCheck; //本次Check所用的时间
    //        //float fErrorDistance = fDistance - fMaxDistance;

    //        //if( fErrorDistance > 0 )
    //        //{
    //        //    //char szBuf[256];
    //        //    //_snprintf( szBuf, 256, "fErrorDistance = %f Count = %d Speed = %f",fErrorDistance, m_shMovingCount+1, GetMoveSpeed());
    //        //    //TellClient( szBuf );
    //        //    //_snprintf( szBuf, 256, "MaxDistance = %f time = %d", fMaxDistance, nReceiveMovingMsgCastTime - nThisCheckCastTime );
    //        //    //TellClient( szBuf );

    //        //    //SendVerifyPos( m_vStartMovingPosPerCheck.x, m_vStartMovingPosPerCheck.y );
    //        //    //SetX(m_vStartMovingPosPerCheck.x);
    //        //    //SetY(m_vStartMovingPosPerCheck.y);

    //        //    //m_shMovingCount = 0;
    //        //    //m_shCheckMovingIndex = theRand.rand32()%(CHECKMOVINGRATE-10)+10;
    //        //    //m_dwStartMovingTimePerCheck = HQ_TimeGetTime();
    //        //    //m_bCheckMovingPerCheck = FALSE;
    //        //    //m_vStartMovingPosPerCheck.x = GetFloatX();
    //        //    //m_vStartMovingPosPerCheck.y = GetFloatY();
    //        //    //m_vStartMovingPosPerCheck.z = 0;

    //        //    m_shMovingErrorCount++;

    //        //    if( fErrorDistance > 10 )
    //        //    {
    //        //        if( fErrorDistance > 20 )
    //        //        {
    //        //            m_nCredit -= 2000;
    //        //            if( fErrorDistance > 256 )
    //        //            {
    //        //                m_nCredit -= 20000;
    //        //            }
    //        //            Log("[%s]移动距离严重超标 超标距离 %f 当前荣誉 %d 当前移动速度 %f", GetCharName(), fErrorDistance, m_nCredit, GetMoveRate() );
    //        //            return FALSE;
    //        //        }
    //        //        else
    //        //        {
    //        //            Log("[%s]移动距离超标 超标距离 %f 当前荣誉 %d 当前移动速度 %f", GetCharName(), fErrorDistance, m_nCredit, GetMoveRate() );
    //        //        }
    //        //        m_nCredit -= 1000;
    //        //        m_shMovingErrorCount = 10;
    //        //    }

    //        //    if( m_shMovingErrorCount > 4 )
    //        //    {
    //        //        m_nCredit -= 1000;
    //        //        if( m_nCredit < 5000 )
    //        //        {
    //        //            Log("[%s]移动距离非法出错 %d 超标距离 %f 当前荣誉 %d 当前移动速度 %f", GetCharName(), fErrorDistance, m_nCredit, GetMoveRate() );
    //        //        }
    //        //        m_shMovingErrorCount = 4;
    //        //    }
    //            ResetCheckMoving();
    //        //}
    //    }
    //    m_shMovingCount++;
    //}
    //else
    //{
    //    ResetCheckMoving();

    //    m_shCheckMovingCount++;
    //    if( m_shCheckMovingCount > 6 )
    //    {
    //        m_shCheckMovingCount = 0;
    //        if( m_shMovingErrorCount > 0 )
    //        {
    //            m_shMovingErrorCount--;
    //        }
    //    }
    //}
    //return TRUE;
}

bool GamePlayer::CheckPosRightful()
{
    if ( GetStatus() == CS_ONSHIP ||  m_bHitchMoving )
    {
		ResetCheckMoving();
		return true; 
	}

    float fDistance     = D3DXVec3Length( &m_vMovingBufPerCheck );
    float fCurMoveSpeed = GetMoveSpeed();

    // 可能会加速【正常，如冲锋技能】
    if( m_fLastMoveSpeedPerCheck > fCurMoveSpeed )
        fCurMoveSpeed = m_fLastMoveSpeedPerCheck;

    //if( fCurMoveSpeed < BaseMoveSpeed )
    //    fCurMoveSpeed = BaseMoveSpeed;

    float fClientMoveSpeed = 0;

    if( m_dwClientPassedTimePerCheck > 0 )
    {
        if( m_dwClientPassedTimePerCheck < 3000 )
            m_dwClientPassedTimePerCheck = 3000;

        fClientMoveSpeed = fDistance/m_dwClientPassedTimePerCheck*1000;

        // 对冲锋时的放宽检测
        if( m_bAssaultMovingProcess )
        { fCurMoveSpeed += 25.0f; }
    }

    if( fClientMoveSpeed > fCurMoveSpeed )
    {
        float fMoveSpeedOffset = fClientMoveSpeed - fCurMoveSpeed;

        if( fMoveSpeedOffset > 2 )
        {
            if( fMoveSpeedOffset < 6 )
            {
                m_nCredit -= 3000;
                Log(theXmlString.GetString(eLog_info_2slk_41), fMoveSpeedOffset, fDistance, m_dwClientPassedTimePerCheck, m_nCredit, GetMoveSpeed() );
                //CheckCredit();
            }
            else if( fMoveSpeedOffset < 40 )
            {
                m_nCredit -= 7000;
                Log(theXmlString.GetString(eLog_info_2slk_42), fMoveSpeedOffset, fDistance, m_dwClientPassedTimePerCheck, m_nCredit, GetMoveSpeed() );
                //CheckCredit();
            }
            else
            {
                m_nCredit -= 100000;
                Log(theXmlString.GetString(eLog_info_2slk_43), fMoveSpeedOffset, fDistance, m_dwClientPassedTimePerCheck, m_nCredit, GetMoveSpeed() );
                //CheckCredit();
            }
        }
    }

    //// 对网络延迟的判定，（厉害的话要踢下线，因为不踢的话这是个给外挂利用的漏洞）
    //if( m_dwClientPassedTimePerCheck > 4500 )
    //{
    //    m_nCredit -= 4000;
    //}

    if( m_bAssaultMovingProcess || fCurMoveSpeed )
        m_fLastMoveSpeedPerCheck = GetMoveSpeed() + 25.0f;
    else
        m_fLastMoveSpeedPerCheck = GetMoveSpeed();

    //CheckCredit(); 暂时防止被拉...屏蔽先 by cloud
    ResetCheckMoving();
    return true;
}

void GamePlayer::CheckCredit()
{
	//暂时屏蔽踢人
	if( m_nCredit < 0 )
	{
		if( m_nKickCount >=1 )
		{
			if( g_Cfg.bKickPlayerByCredit )
			{
				SetFloatXF( m_vStartMovingPosPerCheck.x );
				SetFloatYF( m_vStartMovingPosPerCheck.y );
				SetFloatZ( m_vStartMovingPosPerCheck.z );
				Log(theXmlString.GetString(eLog_info_2slk_44), m_nCredit );
				CheckCheatLog(theXmlString.GetString(eLog_info_2slk_44), m_nCredit );
				CriticalError(__FUNCTION__, __FILE__, __LINE__);
			}
			else
			{
				SendVerifyPos( m_vStartMovingPosPerCheck.x, m_vStartMovingPosPerCheck.y );
				SetFloatXF( m_vStartMovingPosPerCheck.x );
				SetFloatYF( m_vStartMovingPosPerCheck.y );
				SetFloatZ( m_vStartMovingPosPerCheck.z );
				Log(theXmlString.GetString(eLog_info_2slk_46), m_nCredit );
				CheckCheatLog(theXmlString.GetString(eLog_info_2slk_46), m_nCredit );
				m_nCredit = 20000;
				m_dwEnterWorldServerTime = m_dwClientLastSendMovingMsgServerTime;
				m_dwEnterWorldClientTime = m_dwClientLastSendMovingMsgTime;
				m_nKickCount++;
			}
		}
		else
		{
			SendVerifyPos( m_vStartMovingPosPerCheck.x, m_vStartMovingPosPerCheck.y );
			SetFloatXF( m_vStartMovingPosPerCheck.x );
			SetFloatYF( m_vStartMovingPosPerCheck.y );
			SetFloatZ( m_vStartMovingPosPerCheck.z );
			Log(theXmlString.GetString(eLog_info_2slk_47), m_nCredit );
			CheckCheatLog(theXmlString.GetString(eLog_info_2slk_47), m_nCredit );
			m_nCredit = 4000;
			m_dwEnterWorldServerTime = m_dwClientLastSendMovingMsgServerTime;
			m_dwEnterWorldClientTime = m_dwClientLastSendMovingMsgTime;
			m_nKickCount++;
		}
	}
}

bool GamePlayer::CheckMovingMsgSendTime( DWORD dwSendTime )
{ // 每个移动消息都会调用此函数
    if( m_dwEnterWorldClientTime > dwSendTime )
    {
        m_nCredit -= 10000000;
        // ToLog( false && "严重错误，正常发送数据的玩家是不会进这里的" );
        Log(theXmlString.GetString(eLog_info_2slk_48));
    }
    else
    {
        if( m_dwClientLastSendMovingMsgTime > dwSendTime )
        {
            m_nCredit -= 10000000;// ToLog( false && "严重错误，正常发送数据的玩家是不会进这里的" );//故意的
            Log(theXmlString.GetString(eLog_info_2slk_49) );
            TellClient( theXmlString.GetString(eClient_AddInfo_2slk_82) );
        }
        else
        {
            DWORD dwClientPassedTime = dwSendTime       - m_dwEnterWorldClientTime;
            DWORD dwServerPassedTime = HQ_TimeGetTime() - m_dwEnterWorldServerTime;
            DWORD dwTimeOffset = 0;
            if( dwClientPassedTime > dwServerPassedTime )
            {
                dwTimeOffset = dwClientPassedTime - dwServerPassedTime;
            }
            //else
            //{
            //    dwTimeOffset = dwServerPassedTime - dwClientPassedTime;
            //    dwTimeOffset = dwTimeOffset*0.25f;
            //}

            //上次移动时间和本次移动时间的差
            if( m_dwClientPassedTimePerCheck == 0 )
            {
                // 对第一次采集数据的特殊处理
                m_dwClientPassedTimePerCheck = 125;
            }
            else
            {
                m_dwClientPassedTimePerCheck += dwSendTime - m_dwClientLastSendMovingMsgTime;
            } 

            if( dwTimeOffset > 6000 )
            {
                m_nCredit -= 1000000;
                if( dwClientPassedTime - dwServerPassedTime < 0 )
                  //  Log("[%s]移动消息错误，延迟的太厉害了 %d", GetCharName(), dwClientPassedTime - dwServerPassedTime );//消息发送太快 认为是变速齿轮
					Log(theXmlString.GetString(eServerLog_YanChiLiHai), GetCharName(), dwClientPassedTime - dwServerPassedTime );
                else
                {
                    Log(theXmlString.GetString(eLog_info_2slk_50), dwTimeOffset ); 
                    //ShowInfo(false, 257,  theXmlString.GetString(eClient_AddInfo_2slk_83), 0); //lyh-- ，//客户端发消息太慢 ，极度延迟。
                }
            }
        }
    }

    m_dwClientLastSendMovingMsgServerTime = HQ_TimeGetTime();
    m_dwClientLastSendMovingMsgTime       = dwSendTime;
    return true;
}

void GamePlayer::DoAssaultMoving( float fDistance, int nInstantMovingType )
{
    m_bAssaultMovingProcess = true;
}

bool GamePlayer::DoHitch( int nTrafficID, bool bBack )
{
    // id为-1时表示下马
    if ( nTrafficID == -1 )
    {
        DebugLog("nTrafficID:-1  SetRideMountId( -1 ) DoRide( -1 )");
        DoRide( -1 );
        return false;
    }

    ItemDefine::STraffic* pTrafficInfo = GettheItemDetail().GetTrafficByID( nTrafficID );
    if( pTrafficInfo == NULL )
    { return false;}

    SRoute route;
    GetRouteManager().GetRouteInfo( pTrafficInfo->nMapID, pTrafficInfo->nRouteID, route );

    // 是否骑坐骑
    int nDromeID = pTrafficInfo->nDromeID;    
    ItemDefine::SDrome* pDromeInfo = GettheItemDetail().GetDromeByID( nDromeID );
    if( pDromeInfo != NULL )
    { 
        //DoRide( nDromeID );
        SetRideId( nDromeID );
		SetRideLevel(0/*_mountManager.GetActiveMount()->baseInfo.level*/);
		SetRideDriverId(GetID());

        MsgChangeDrome changedrome;
        changedrome.header.stID = GetID();
        changedrome.nDromeID    = nDromeID;
		changedrome.nMountLevel = 0/*_mountManager.GetActiveMount()->baseInfo.level*/;
        changedrome.ucOpType    = MsgChangeDrome::EOT_Ride;
        GettheServer().SendMsgToView( &changedrome, GetID(), false );
    }

    IntonateInterrupt( ItemDefine::EIT_Force, __FUNCTION__ );

    //夺走玩家的控制权
    MsgCanControlMoving msg;
    msg.header.stID       = GetID();
    msg.bCanControlMoving = false;
    if ( route.flyRoute )
    { msg.bIsFlyMoving = true ; }
    else
    { msg.bIsFlyMoving = false; }
    SetFlyMoving( msg.bIsFlyMoving );
    GettheServer().SendMsgToView( &msg, GetID(), false );

    m_bHitchMoving = true;
    m_bHitchBack   = bBack;
    m_nTrafficID   = nTrafficID;
    m_dwRouteStep  = 0;
    return true;
}

int GamePlayer::GetCurTrafficID()
{
    if( m_bHitchMoving )
        return m_nTrafficID;
    return -1;
}

void GamePlayer::DoHitchMoving( int nTrafficID )
{
    if ( IsDead() )
    { 
        CancelHitchMoving();
        return;
    }

    if ( m_xHitchMoveTimer.IsStart() && !m_xHitchMoveTimer.DoneTimer() )
    { return; }

    D3DXVECTOR3 vPos = GetPos();
    float fErrDistance = 0.0f, fSpeed = 0.0f;
    SMovePos xRouteMovePos;

	uint16 dwRouteStep = m_dwRouteStep;

    if( GetRouteManager().GetCurTrafficRoute( nTrafficID, m_bHitchBack, m_dwRouteStep, fSpeed, vPos, fErrDistance, xRouteMovePos ) )
    {
        // 路点动作
        if ( strlen( xRouteMovePos.szActionName ) >= 1 )
        {
            MsgNpcPlayAnim msg;
            msg.header.stID = GetID();
            msg.nNpcId      = GetID();
            HelperFunc::SafeNCpy( msg.szActionName,  xRouteMovePos.szActionName , MsgNpcPlayAnim::eActionNameLength );
            HelperFunc::SafeNCpy( msg.szEndActionName, "idle", MsgNpcPlayAnim::eActionNameLength );
            msg.nLoopTimes = 1;
            GettheServer().SendMsgToSingle( &msg, this );
        }

        // 场景
        if ( xRouteMovePos.stSceneId > 0  )
        {
            MsgScenePlay  msgScene;
            msgScene.header.stID = GetID();
            msgScene.stSceneId   = xRouteMovePos.stSceneId;
            GettheServer().SendMsgToSingle( &msgScene, this );
        }

        // 停止移动
        if ( xRouteMovePos.dwTime > 0 )
        { 
            m_xHitchMoveTimer.StartTimer( HQ_TimeGetTime(), xRouteMovePos.dwTime ); 
            return;
        }
        
        MsgHitchMoveTargetPos msg;
        msg.header.stID = GetID();
        msg.vTargetPos.x = vPos.x;
        msg.vTargetPos.y = vPos.y;
        msg.vTargetPos.z = vPos.z;
        GettheServer().SendMsgToSingle( &msg, this );

        if ( fSpeed != GetMoveSpeed() )
        {
            GetCharFightAttr()->moveSpeed.Reset();
            GetCharFightAttr()->moveSpeed.base = fSpeed;
            GetCharFightAttr()->moveSpeed.UpdateFinal();
            ChangeAttr( CharAttr_MoveSpeed, GetMoveSpeed() );
        }
    }
    else
    { // 拿不到了
        ItemDefine::STraffic* pTrafficInfo = GettheItemDetail().GetTrafficByID( nTrafficID );
        if( pTrafficInfo == NULL || pTrafficInfo->nextTrafficId == -1)
        {
            CancelHitchMoving();

			if (pTrafficInfo)
			{
				SRoute sRoute;
				bool bResult = GetRouteManager().GetRouteInfo( pTrafficInfo->nMapID, pTrafficInfo->nRouteID, sRoute );
				if ( bResult)
				{
					int nSize = sRoute.allMovePos.size();
					if ( dwRouteStep < nSize)
					{
						m_vStartMovingPosPerCheck.x = sRoute.allMovePos[dwRouteStep].fX;
						m_vStartMovingPosPerCheck.y = sRoute.allMovePos[dwRouteStep].fY;
						m_vStartMovingPosPerCheck.z = 0;
						m_vMovingBufPerCheck.x = 0;
						m_vMovingBufPerCheck.y = 0;
						m_vMovingBufPerCheck.z = 0;
						m_dwClientPassedTimePerCheck = 0;
						m_bAssaultMovingProcess = false;
					}
				}
			}
            return;
        }

        if ( DoHitch( pTrafficInfo->nextTrafficId, m_bHitchBack )  )
        { return; }
        else
        {			
			CancelHitchMoving(); 
			if (pTrafficInfo)
			{
				SRoute sRoute;
				bool bResult = GetRouteManager().GetRouteInfo( pTrafficInfo->nMapID, pTrafficInfo->nRouteID, sRoute );
				if ( bResult)
				{
					int nSize = sRoute.allMovePos.size();
					if ( dwRouteStep < nSize)
					{
						m_vStartMovingPosPerCheck.x = sRoute.allMovePos[dwRouteStep].fX;
						m_vStartMovingPosPerCheck.y = sRoute.allMovePos[dwRouteStep].fY;
						m_vStartMovingPosPerCheck.z = 0;
						m_vMovingBufPerCheck.x = 0;
						m_vMovingBufPerCheck.y = 0;
						m_vMovingBufPerCheck.z = 0;
						m_dwClientPassedTimePerCheck = 0;
						m_bAssaultMovingProcess = false;
					}
				}
			}
		}
    }

    if( fErrDistance > 32 )
    {
        m_nCredit -= 4000;
        if( GettheItemDetail().GetTrafficByID( nTrafficID ) )
        {
            Log(theXmlString.GetStringWithName(eLog_info_2slk_51), GetCharName(), nTrafficID, "" );
        }
        else
        {
            Log(theXmlString.GetStringWithName(eLog_info_2slk_52), GetCharName(), nTrafficID);
        }
    }

    return;
}

void GamePlayer::CancelHitchMoving()
{
    m_bHitchMoving = false;
    m_bHitchBack   = false;
    m_nTrafficID   = -1;
    m_dwRouteStep  = 0;
    m_xHitchMoveTimer.StopTimer();

    // 让玩家重新获得控制权
    MsgCanControlMoving msg;
    msg.header.stID       = GetID();
    msg.bCanControlMoving = true;
    msg.bIsFlyMoving      = false;
    SetFlyMoving( msg.bIsFlyMoving );
    GettheServer().SendMsgToView( &msg, GetID(), false );

    GetCharFightAttr()->moveSpeed.base = BaseMoveSpeed;
    GetCharFightAttr()->moveSpeed.UpdateFinal();
    ChangeAttr( CharAttr_MoveSpeed, GetMoveSpeed() );

    // 让玩家下坐骑
    if( GetRideId() > InvalidLogicNumber )
    { DoRide( -1 ); }
	ResetCheckMoving();
}

long GamePlayer::TryRespondChangeStage()
{
    MapConfig::MapData* pMapData = GetMapData();
    if ( pMapData == NULL )
    { return ER_MapCfgNotFound; }

    MapConfig::TransportPosition* pTransportPosition = pMapData->GetTransportPositionByPositon( GetFloatX(), GetFloatY() );
    if ( pTransportPosition == NULL )
    { return ER_NotInTransportRegion; }

    MapConfig::MapData* pMapDataTarget = theMapConfig.GetMapDataById( pTransportPosition->TargetMapId );
    if ( pMapDataTarget == NULL )
    { return ER_MapCfgNotFound; } 

    MapConfig::TransportDestination* pTransportDestination = pMapDataTarget->GetTransportDestinationById( pTransportPosition->TargetId );
    if ( pTransportDestination == NULL )
    { return ER_NotTargetTransportRegion; }

    FlyToMapReq( pTransportPosition->TargetMapId, pTransportDestination->PositionX, pTransportDestination->PositionY, pTransportDestination->Direction );

	// 队长跳转时,将队伍跟随的队友也跳转
	GameTeam *pTeam = theGameTeamManager.GetTeam( GetTeamID() );
	if ( pTeam && pTeam->IsTeamHeader( GetDBCharacterID() ) )
	{
		for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
		{
			GameTeamMember* pMember = pTeam->GetTeamMemberByIndex(i);
			if ( pMember && pMember->GetTeamFollowMemberID() > 0 )
			{
				GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( pMember->GetID() );
				if ( pPlayer )
				{
					pPlayer->FlyToMapReq( pTransportPosition->TargetMapId, pTransportDestination->PositionX, pTransportDestination->PositionY, pTransportDestination->Direction );
				}
			}
		}
	}

    //Log( "请求触发跳转 目标地图[%d]", pTransportPosition->TargetMapId );
	Log( theXmlString.GetString(eServerLog_QingQiuToMap), pTransportPosition->TargetMapId );

    return ER_Success;
}