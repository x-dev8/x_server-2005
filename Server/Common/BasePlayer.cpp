#include "BaseCharacter.h"
#include "BasePlayer.h"
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
#include "AiBaseCharacter.h"
#include "ResourcePath.h"
#include "MeRTLibsServer.h"
#include "MapConfig.h"
#include "TeamManager.h"
#include "EffectChar.h"
#include "GamePlayer.h"
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

extern CExpStage theExpStage;

#define SENDMOVINGMESSAGERATECONTAIN 250
#define MOVINGCOUNT 32767

int g_nSendMovingMessageRate = 250; //������ÿ���·��ƶ���Ϣ��Ƶ��

void PlayerLogFunc(BasePlayer* pPlayer, const char* szFormat, ...)
{
    if (pPlayer != NULL)
    {
        char szBuf[1024] = {0};
        va_list vl;
        va_start(vl, szFormat);
        int cnt = vsnprintf(szBuf, sizeof(szBuf)-1, szFormat, vl);
        pPlayer->Log(szBuf);
        va_end(vl);
    }
}

BasePlayer::BasePlayer()
{
    m_bPosDebugOpen = false;

    SetStatus(CS_LOGIN);
    SetHP(100);
    SetHPMax(100);
    SetMP(100);
    SetMPMax(100);
    SetLevel(1);
    //
    m_bDeathAndWaitForRelive = false;
    //
    //for (int i = 0; i < PLAYERCHAR_MAX_PET; i++)
    //{
    //	m_stPets[i] = -1;
    //}
    SetObjType( Object_Player );
    //
    m_shCheckMovingCount = 0;
    m_shCheckMovingIndex = theRand.rand32()%(CHECKMOVINGRATE-10)+10;

    strncpy_s( m_szLoginName, sizeof(m_szLoginName), "Invalid", sizeof(m_szLoginName) - 1);
    strncpy_s( m_szLoginIP,   sizeof(m_szLoginIP), "Invalid", sizeof(m_szLoginIP) - 1);

    m_dwStartReadytoSendVerifyPosMsgTime = 0;

    m_dwLastSendHitchMoveMsgTime = 0;

    m_nCredit = 20000;

    m_ucCharStatus = MsgPlayerEnterMySight::charstatus_normal_drawin;

    m_dwEnterWorldClientTime = 0;
    m_dwEnterWorldServerTime = 0;
    m_dwClientLastSendMovingMsgTime = 0;
    m_dwClientLastSendMovingMsgServerTime = 0;
    m_dwClientPassedTimePerCheck = 0;
    m_bAssaultMovingProcess = false;
    m_fLastMoveSpeedPerCheck = 0;
    m_nKickCount = 0;
    m_nTrafficID = -1;
    m_bHitchMoving = false;
    m_bHitchBack = false;
    m_dwRouteStep = 0;    
    memset( _szSessionKey, 0, sizeof(_szSessionKey));
}

bool BasePlayer::ProcessMsg( Msg* pMsg)
{
    DWORD dwType = pMsg->GetType();
    if(MSG_EXIT == dwType)
    {   
        ((GamePlayer*)this)->SetOffline();
        return false;
    }
    else if(MSG_PING == dwType)
    {
        OnPingMsg(pMsg);
        return true;
    }

    switch( GetStatus() )
    {
    case CS_LOADINGMAP:
        {
            DWORD dwType = pMsg->GetType();
            if (MSG_MAPLOADED == dwType)
            {
                //��ͼ�������,�л�״̬
                SetStatus( CS_IDLE );
                return true;
            }
            else if (MSG_QUERYDISPLAYNAME == dwType)
            {
                OnQueryDisplayName(pMsg);
                return true;
            }
        }
        break;
    case CS_DOACTION:
    case CS_IDLE:        
    case CS_HOLDSKILL:
    case CS_WALK:
    case CS_ATTACK:
    case CS_INTONATE:
    case CS_HURT:
    case CS_READYTOUSESPEICALSKILL:
        {
            DWORD dwType = pMsg->GetType();
            if (MSG_QUERYMOVE == dwType)
            {
                OnQueryMove();
                return true;
            }
            else if (MSG_QUERYDISPLAYNAME == dwType)
            {
                OnQueryDisplayName(pMsg);
                return true;
            }
            else if (MSG_GETLAG == dwType)
            {
                OnGetLag();
                return true;
            }
            else if (MSG_PLAYERMOVINGPOSTOSERVER == dwType)
            {
                OnMsgPlayerMovingPos( pMsg );
                return true;
            }
            else if (MSG_PLAYERMOVINGPOSANDDIRTOSERVER == dwType)
            {
                OnMsgPlayerMovingPosToDir( pMsg );
                return true;
            }
            else if (MSG_PLAYERPOSTOSERVER == dwType)
            {
                OnMsgPlayerPos( pMsg );
                return true;
            }
            else if (MSG_PLAYERDIRTOSERVER == dwType)
            {
                OnMsgPlayerDir( pMsg );
                return true;
            }
            else if (MSG_PLAYERPOSANDDIRTOSERVER == dwType)
            {
                OnMsgPlayerPosAndDir( pMsg );
                return true;
            }
            else if(MSG_INTONATEINTERRUPT == dwType)
            {
                OnMsgIntonateInterrupt( pMsg );
                return true;
            }
            else if( MSG_JUMP == dwType )
            {
                OnMsgJump( pMsg );
                return true;
            }
            else if( MSG_DRAWWEAPON == dwType )
            {
                OnMsgDrawWeapon( pMsg );
                return true;
            }
            else if( MSG_DRAWINWEAPON == dwType )
            {
                OnMsgDrawInWeapon( pMsg );
                return true;
            }
            else if (MSG_CHANGINGDIR == dwType)
            {
                OnReqChangeDir( pMsg );
                return true;
            }
            else if (MSG_READYTOUSESPECIALSKILL == dwType )
            {
                OnMsgReadytoUseSpecialSkill();
                return true;
            }
            //
            else if (MSG_QUERYCHARAROUND == dwType)
            {
                OnQueryCharAround( pMsg );
                return true;
            }
            else if (MSG_GETPLAYERINFO == dwType)//�ͻ��˷���������Ϣѯ��Ī��Player������
            {
                OnGetPlayerInfo(pMsg);
                return true;
            }
        }
        break;
    case CS_DIEING:
        return true;
        break;
    case CS_LOGINTODB:
    case CS_DBLOGINED:
        return true;
        break;
    case CS_ONSHIP:
        break;
    }

    //���һ���û��кܶࡣ������Ҫ�������Ϣ������ô˵�����û��Ŀͻ�����������ġ���
    //�������Ϣ�������û��Ĵ����������κ�
    //�ر�����
#if 0
    if ( IsPlayer() )
    {
        GamePlayer* pGamePlayer = (GamePlayer*)this;
        LOG_MESSAGE( CHECKCHEATOBJECT, LOG_PRIORITY_INFO, "account[%u:%s:%u:%s:%d message(%u) status(%d)]", 
            pGamePlayer->GetAccountID(), pGamePlayer->GetAccount(), pGamePlayer->GetDBCharacterID(), GetPlayerName(), GetID(), dwType, GetStatus() );
    }
#endif

    // �� CS_LOADMAP ��ʱ����Щ��Ϣ�������Ҫע�⣡
    return false;
}

void BasePlayer::Dieing()
{
    // ���������״̬���򲻴�������
    if( m_ExtendStatus.IsReliveTime() )
        return;
}


void BasePlayer::OnQueryMove()
{
    // �����ʧȥ����״̬����ֱ�ӷ��أ������κδ���
    //if( m_ExtendStatus.IsLoseControl() )
    //	return; 

    MsgAckMove msg;
    msg.x = GetX();
    msg.y = GetY();
    msg.header.stID = GetControl()->GetID();
    GettheServer().SendMsgToSingle( &msg, this );
#ifndef SINGLESTEPLOGIC
    SetStatus( CS_IDLE );
#endif
}

void BasePlayer::SendChangeMapMessageToClient( DWORD dwMapId, short nTileX, short nTileY, BYTE byDir, float fDir )
{
    MsgChangeMap msg;
    msg.header.stID = GetID();

    SetMapID( dwMapId );

    // ������
    bool bFix = IsNeedFixWorldCoordinate( nTileX, nTileY );

    SetX( nTileX, bFix );
    SetY( nTileY, bFix );
    SetZ( WORLD_HEIGHT );               // ����Z��, ��ֹ�쳣 z�᲻��
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

void BasePlayer::OnQueryDisplayName( Msg *pMsg )
{
    if (pMsg == NULL)
    {
        return;
    }
    MsgAckDisplayName msg;
    MsgQueryDisplayName *pMsgTmp = (MsgQueryDisplayName*)pMsg;

    if(pMsgTmp->nWhoId<0)
        return;

    msg.header.stID = pMsgTmp->nWhoId;

    BaseCharacter * pChar =(BaseCharacter*)theRunTimeData.GetCharacterByID( pMsgTmp->nWhoId );
    if(pChar==NULL)
        return;

    HelperFunc::SafeNCpy( msg.szDisplayName,pChar->GetPlayerName(),sizeof(msg.szDisplayName) );
    GettheServer().SendMsgToSingle( &msg, this );
}

//void BasePlayer::OnQueryAttack2( Msg* pMsg )
//{
//	//
//	short stSkills[More_iMaxLinkedSkills];		//
//	short stSkillLevel[More_iMaxLinkedSkills];	//
//	int	   iSkillCount = 0;
//	BOOL   bFailFlag = TRUE;
//	//
//	MsgQueryAttack2* msg = (MsgQueryAttack2*)pMsg;
//	//
//	BaseCharacter * pChar = (BaseCharacter*)theRunTimeData.GetCharacterByID( msg->stWho );
//	//
//	if (NULL != pChar)
//	{
//		// �����ʧȥ����״̬����ֱ�ӷ��أ������κδ���
//		if (!m_ExtendStatus.IsLoseControl() )
//		{
//			// �жϵ�ǰ����ҿɷ�ʹ�ü���
//			if (IsCanUseSkill())
//			{
//				bFailFlag = FALSE;
//				// �����ǰ����
//				if( GetActionId() != -1 )
//					SetActionId( -1 );
//
//				//ֻ����IDLE��ʱ�����ȡTask
//				CItemDetail::SItemSkill*pSkill = GettheItemDetail().GetSkillByID(msg->stSkills[0], msg->stSkillLevel[0]);
//				//
//				if (NULL != pSkill)
//				{
//					switch (pSkill->stGeneralType)
//					{
//					case CItemDetail::generaltype_sequence://����Action����
//						PlaySubSkill(msg->stSkills[0], stSkills, stSkillLevel, &iSkillCount);
//						break;
//					default:
//						stSkills[0] = msg->stSkills[0];			//
//						stSkillLevel[0] = msg->stSkillLevel[0];	//
//						iSkillCount = 1;
//						break;
//					}
//					if (iSkillCount > 0)
//						_SkillTaskManager.SetTasks(CSkillTaskMgr::TaskTypeSkill, msg->stWho, stSkills, stSkillLevel, iSkillCount);
//				}
//			}
//		}
//	}
//	//�ͻ��˻�pre_attack ..������Ҫ����Ϣ֪ͨһ�¡�
//	if (bFailFlag)
//	{
//		if (Object_Player == GetObjType())
//		{
//			MsgAckQueryAttack2 AckAttackMsg;
//			AckAttackMsg.Msgid = MsgAckQueryAttack2::AckQueryAttack2Fail;
//			//
//			GettheServer().SendMsg(this, &AckAttackMsg, sendrange_single);
//		}
//	}
//}
// Luo_157 added 2003.05.07
void BasePlayer::OnQueryAllGameProperty( Msg* pMsg )
{
    MsgQueryAllGameProperty* msg = (MsgQueryAllGameProperty*)pMsg;
    BaseCharacter * pChar = (BaseCharacter*)theRunTimeData.GetCharacterByID( msg->stTargetId );
    if(pChar==NULL)
        return;
    //	BaseCharacter::BaseInfo* pInfo = (BaseCharacter::BaseInfo*)pChar->GetInfoData();

    MsgAckAllGameProperty agpr;
    agpr.stTargetId = msg->stTargetId;
    agpr.gp.nHp = pChar->GetHP();
    agpr.gp.stLevel = pChar->GetLevel();
    agpr.gp.nMp = pChar->GetMP();
    GettheServer().SendMsgToSingle( &agpr, this );
}





void BasePlayer::OnGetLag()
{
    MsgGetLag msg;
    msg.header.stID = GetControl()->GetID();
    GettheServer().SendMsgToSingle( &msg, this );
}

void BasePlayer::OnDeath()
{
    // ���������꣬��ͼ���		
    // �����ά�ּ��ܻ�������״̬�����ܱ����
    switch( GetStatus() )
    {
    case CS_INTONATE:
    case CS_HOLDSKILL:
        CancelSkill();
        break;
    }
    // ��־�û�Ϊ����
    SetStatus( CS_DIEING );
    SetDead();

    //������г���б�
    ClearAllEnmity();       // ֻ������, ��ɾ���б�

    if ( IsPlayer() )
    {
        SetHP( 0 );
        SetMP( 0 );

        GamePlayer* pGamePlayer = (GamePlayer*)this;

        GetScriptMgr()->StartupVM( ST_CHAR_DEAD, 0, pGamePlayer );

        pGamePlayer->ClosePrivateShop();
        //�����ұ��������ɱ�����������½�10�㣬��ұ�����ɱ�����������½�20��
        if ( m_pKiller != NULL )
        { 
            SMountItem* pMount = pGamePlayer->_mountManager.GetActiveMount();
            if (pMount != NULL)
            {
                float hpDropPer = 1.0f;
                if (_buffManager.GetDeathMountHPDropPer() > 0)
                { hpDropPer = _buffManager.GetDeathMountHPDropPer() * DEF_PERCENT; }

                if (m_pKiller->IsPlayer())
                { pMount->baseInfo.hp -= MOUNT_HP_DROP_KILLED_BY_PALYER * hpDropPer ; }
                else
                { pMount->baseInfo.hp -= MOUNT_HP_DROP_KILLED_BY_MONSTER * hpDropPer; }

                if (pMount->baseInfo.hp  < 0)
                { pMount->baseInfo.hp = 0; }
            }
        }

        // ��������� ������
        if ( pGamePlayer->_mountManager.GetActiveBeRiding() )
        {
            pGamePlayer->DoRide( -1 );      
        }

        if ( pGamePlayer->GetProtectCharID() != -1 )
        {
            BaseCharacter* pTarget = theRunTimeData.GetCharacterByID(pGamePlayer->GetProtectCharID());
            if ( pTarget != NULL && pTarget->IsMonster())
            {
                AiBaseCharacter* pAiChar = (AiBaseCharacter*)pTarget;
                pTarget->SetDead();                
                pGamePlayer->KillProtectChar();                
                if ( pAiChar->GetBindProtectCharVarId() != -1)
                { pGamePlayer->SetVar( pAiChar->GetBindProtectCharVarId(), 0 ); }
            }

            pGamePlayer->LostProtectChar();
        }

        // �м��ܳ���
        if ( pGamePlayer->HavePet() )
        {
            for (int i=0;i<CharPetMonsterMaxCount; ++i)
            {
                SummonPetManager::SPetMonster* pPetMonster = pGamePlayer->GetPetMonster(i);
                if ( NULL == pPetMonster )
                { continue;  }

                BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( pPetMonster->petId );
                if ( pTarget != NULL )
                {
                    AiBaseCharacter* pAiChar = (AiBaseCharacter*)pTarget;
                    pTarget->SetDead();
                    pTarget->WasKilled( this );
                }

                pPetMonster->Clear();
            }
        }

        // �в������
        if ( pGamePlayer->HaveCapturePet() )
        {
            BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( pGamePlayer->GetCapturePetId() );
            if ( pTarget != NULL )
            {
                AiBaseCharacter* pAiChar = (AiBaseCharacter*)pTarget;
                pAiChar->SetDead();                
                //pAiChar->WasKilled( this );
                //pGamePlayer->LostCapturePet();
                pGamePlayer->KillCapturePet();
            }
        }
    }	

    //�ȹ㲥������Ϣ
    MsgSawSomeoneDead msg;
    msg.header.stID = GetID();
    GettheServer().SendMsgToView( &msg, GetID(), false );

    // ����������ϵ�״̬    
    bool bResult = _buffManager.UpdateOnDead();	
    if ( bResult )
    {
        _buffManager.ApplyBuffsToChar( GetProfession(), GetCharBaseAttr(), GetCharFightAttr() );
        SendBuffChanged( NULL );
    }

    m_bDeathAndWaitForRelive = true;
    m_ExtendStatus.EnterReliveTime( 1000 );
}

// script
bool BasePlayer::IsCanSwitchStage()
{
    if( m_bDeathAndWaitForRelive )
        return false;
    return BaseCharacter::IsCanSwitchStage();
}

void BasePlayer::SendRefreshChar()
{
    // ToLog( false );
}

Msg* BasePlayer::FirstSightOnMe(char* szMsgBuffer, unsigned int nBuffSize)
{
    return BaseCharacter::FirstSightOnMe(szMsgBuffer, nBuffSize);
}

//---
//�ͻ��˷��͹�������Ϣ������Ī��Player����
//---
void	BasePlayer::OnGetPlayerInfo(Msg*pMsg)
{
    MsgGetPlayerInfo*  pGetPlayerInfo = (MsgGetPlayerInfo *)pMsg;
    MsgAckGetPlayerInfo info;
    //
    BaseCharacter* pCPlayer = theRunTimeData.GetGamePlayerByName(pGetPlayerInfo->szPlayerName);
    //
    info.bOnline = false;
    info.stPlayerId = -1;
    strncpy_s(info.szPlayerName, sizeof(info.szPlayerName), pGetPlayerInfo->szPlayerName, sizeof(info.szPlayerName)-1);
    //
    if (NULL != pCPlayer)
    {
        //
        info.bOnline = true;
        info.stPlayerId = pCPlayer->GetID();
    }
    //����Ϣ��ȥ
    GettheServer().SendMsgToSingle( &info, this );
}

//
//void BasePlayer::OnBargainingComplete( const Msg* pMsg )
//{
//	//MsgBargainingComplete* pBargainingComplete = (MsgBargainingComplete*)pMsg;
//	//BasePlayer* pChar = (BasePlayer*)theRunTimeData.GetCharacterByID( pBargainingComplete->header.stID );
//	//if (pChar)
//	//{
//	//	if ( pBargainingComplete->bOK == true )
//	//	{
//	//		GetBargainingManager().SetComplete( GetControl()->GetID() );
//	//		if ( GetBargainingManager().IsComplete( pChar->GetControl()->GetID() ) == true )
//	//		{
//	//			GetBargainingManager().ExChange( this, pChar );
//	//			GetBargainingManager().DelRoom( GetControl()->GetID() );
//
//	//			pBargainingComplete->bOK = true;
//	//			GetControl()->SendMsg( pBargainingComplete );
//	//			pChar->GetControl()->SendMsg( pBargainingComplete );
//	//		}
//	//	}
//	//	else
//	//	{
//	//		GetBargainingManager().DelRoom( GetControl()->GetID() );
//
//	//		pBargainingComplete->bOK = false;
//	//		GetControl()->SendMsg( pBargainingComplete );
//	//		pChar->GetControl()->SendMsg( pBargainingComplete );
//	//	}// End if
//	//}
//}

void BasePlayer::OnMsgReadytoUseSpecialSkill()
{
    SetStatus( CS_READYTOUSESPEICALSKILL );
    m_ExtendStatus.EnterActionStatus(10000);

    MsgAgreeReadytoUseSpecialSkill agreereadytousespecialskill;
    agreereadytousespecialskill.shCurPermillage = 200;
    GettheServer().SendMsgToSingle( &agreereadytousespecialskill, this );
}

void BasePlayer::OnReqChangeDir( const Msg* pMsg )
{
    MsgChangingDir *pChangeDir = (MsgChangingDir*)pMsg;

    SetDirX( pChangeDir->DirX );
    SetDirY( pChangeDir->DirY );
    //SetDir( pChangeDir->byDir );
}

void BasePlayer::OnMsgJump( const Msg* pMsg )
{
    MsgJump *pJump = (MsgJump*)pMsg;
    MsgJump jump;
    jump.header.stID = GetControl()->GetID();
    jump.shJumpActionId = pJump->shJumpActionId;
    GettheServer().SendMsgToView( &jump, GetID(), true );
    IntonateInterrupt( EIT_Jump );
}

// �γ���������Ϣ
void BasePlayer::OnMsgDrawWeapon( const Msg* pMsg )
{
    m_ucCharStatus = MsgPlayerEnterMySight::charstatus_normal_draw;
    MsgDrawWeapon draw;
    draw.header.stID = GetControl()->GetID();
    GettheServer().SendMsgToView( &draw, GetID(), true );
}

// ������������Ϣ
void BasePlayer::OnMsgDrawInWeapon( const Msg* pMsg )
{
    m_ucCharStatus = MsgPlayerEnterMySight::charstatus_normal_drawin;
    MsgDrawInWeapon drawin;
    drawin.header.stID = GetControl()->GetID();
    GettheServer().SendMsgToView( &drawin, GetID(), true );
}

void BasePlayer::OnMsgIntonateInterrupt( const Msg* pMsg )
{
    IntonateInterrupt( EIT_Msg );
}

void BasePlayer::IntonateInterrupt( int8 nType )
{
    // �����ܲ����ƶ������
    if ( nType == EIT_Move || nType == EIT_Jump )
    {
        SSkillTask* pSkillTask = _SkillTaskManager.GetCurTask();
        if (pSkillTask != NULL )
        {
            if ( !IsCanCancelSkill( pSkillTask->id ) )
            { return; }
        }
    }
    
    if( GetStatus() == CS_INTONATE )
    {
        SetStatus( CS_IDLE );
        //���������жϵ���Ϣ
        Msg_IntonateInterrupt IntonateInterrupt_msg;
        IntonateInterrupt_msg.header.stID = GetID();
        IntonateInterrupt_msg.nSkillID    = _SkillTaskManager.DoneCurTask();
        GettheServer().SendMsgToSingle( &IntonateInterrupt_msg, this );
        Msg_SkillCanceld cancel;
        cancel.header.stID = GetID();
        GettheServer().SendMsgToView( &cancel, GetID(), false );
    }
    else if ( GetStatus() == CS_HOLDSKILL )
    {  
        SetStatus( CS_IDLE );
        if( m_ContinuousSkill.pEffectChar )
        {
            m_ContinuousSkill.pEffectChar->CriticalError(__FUNCTION__, __FILE__, __LINE__);
            m_ContinuousSkill.pEffectChar = 0;
        }
        m_ContinuousSkill.dwTimeSkillHoldingEnd = 0; 
        //��ʾ��ǰ���������
        int nSkillID = _SkillTaskManager.DoneCurTask();    
        if( IsPlayer() )
        {
            Msg_IntonateInterrupt IntonateInterrupt_msg;
            IntonateInterrupt_msg.header.stID = GetID();
            IntonateInterrupt_msg.nSkillID = nSkillID;
            GettheServer().SendMsgToSingle( &IntonateInterrupt_msg, this );
        }

        Msg_SkillCanceld cancel;
        cancel.header.stID = GetID();
        GettheServer().SendMsgToView( &cancel, GetID(), false );
    }
}

//void BasePlayer::OnMsgPlayerMoving( const Msg* pMsg )
//{
//	if(!m_cFightStatus.IsCanMove())
//		return;
//
//	MsgPlayerMoving *pmovepasspos = (MsgPlayerMoving*)pMsg;
//
//	float fx = pmovepasspos->vPos.x;
//	float fy = pmovepasspos->vPos.y;
//	float fz = pmovepasspos->vPos.z;
//	float fdirx = pmovepasspos->vDir.x;
//	float fdiry = pmovepasspos->vDir.y;
//
//	//m_vLastSavedVerifyPos = pmovepasspos->vPos;
//	//m_vLastSavedVerifyDir = pmovepasspos->vDir;
//
//	m_shLastSavedMovingType = pmovepasspos->shMovingType;
//
//	if( m_bSentVerifyPosMsg )
//	{
//		m_dwStartReadytoSendVerifyPosMsgTime = g_dwLastWorldProcessTime;
//		m_bSentVerifyPosMsg = FALSE;
//	}
//
//	if( fx != GetFloatX() || fy != GetFloatY() )
//	{
//		if( GetStatus() == CS_INTONATE )
//		{
//			//���������жϵ���Ϣ
//			Msg_IntonateInterrupt IntonateInterrupt_msg;
//			IntonateInterrupt_msg.header.stID = GetID();
//			GettheServer().SendMsgToSingle( &IntonateInterrupt_msg, this );
//			_SkillTaskManager.DoneCurTask();
//		}
//		SetStatus( CS_WALK );
//		_SkillTaskManager.DoneCurTask();
//		m_bMoving = TRUE;
//	}
//
//
//	SetX( fx );
//	SetY( fy );
//	SetZ( fz );
//	SetDirX( fdirx );
//	SetDirY( fdiry );
//	SetLastReceiveMoveMessageTime( g_dwLastWorldProcessTime );
//
//	if( !CheckMoving() && KICK_CREDIT)
//	{
//		SetX( m_vStartMovingPosPerCheck.x );
//		SetY( m_vStartMovingPosPerCheck.y );
//		SetZ( m_vStartMovingPosPerCheck.z );
//		Log("���[%s]�ƶ���Ϣ��ⲻ�Ϸ� ����ǿ��������", GetPlayerName(), m_nCredit );
//		CriticalError(__FUNCTION__, __FILE__, __LINE__);
//		return;
//	}
//
//	//GettheWorld().OnRefreshNewArea( GetID() );
//
//	//if( g_dwLastWorldProcessTime - m_dwLastSendPlayerMovingMsgTime > m_dwSendPlayerMovingMsgRate )
//	{
//		MsgPlayerVerifyPos msg;
//		msg.header.stID = GetID();
//		msg.vPos.x = GetFloatX();
//		msg.vPos.y = GetFloatY();
//		msg.vPos.z = GetFloatZ();
//		//msg.vDir.x = GetDirX();
//		//msg.vDir.y = GetDirY();
//		//msg.vDir.z = 0;
//		//msg.shMovingType = m_shLastSavedMovingType;
//
//		GettheServer().SendMsgToView( &msg, GetID(), true );
//		//m_dwLastSendPlayerMovingMsgTime = g_dwLastWorldProcessTime;
//	}
//}

void BasePlayer::OnMsgPlayerMovingPos( const Msg* pMsg )
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

    // �����ƶ���Ϣ���͵�Ƶ��
    CheckMovingMsgSendTime( pMsg1->dwSendTime );

    float fx = pMsg1->vPos.x;
    float fy = pMsg1->vPos.y;
    float fz = pMsg1->vPos.z;

    if( fx != GetFloatX() || fy != GetFloatY() )
    {
        SSkillTask* pSkillTask = _SkillTaskManager.GetCurTask();
        if (pSkillTask != NULL )
        {
            if ( IsCanCancelSkill( pSkillTask->id ) )
            { 
                OnHaveSkillDisplace();
                IntonateInterrupt( EIT_Move );
                SetStatus( CS_WALK );
            }
        }
        else
        {
            OnHaveSkillDisplace();
            IntonateInterrupt( EIT_Move );
            SetStatus( CS_WALK );
        }
    }

    m_vMovingBufPerCheck.x += abs( fx - GetFloatX() );
    m_vMovingBufPerCheck.y += abs( fy - GetFloatY() );

    SetX( fx );
    SetY( fy );
    SetZ( fz );
    SetLastReceiveMoveMessageTime( GettheWorld().g_dwLastWorldProcessTime );

    MsgPlayerMovingPos msg;
    msg.header.stID = GetID();
    msg.vPos.x = GetFloatX();
    msg.vPos.y = GetFloatY();
    msg.vPos.z = GetFloatZ();
    GettheServer().SendMsgToView( &msg, GetID(), true );

    m_bMoving = true;

    if (m_bPosDebugOpen)
    {
        char szBuffer[100];
        sprintf_s(szBuffer, sizeof(szBuffer)-1, "X: %f Y: %f Z: %f", this->GetFloatX(), this->GetFloatY(), this->GetFloatZ());
        TellClient(szBuffer);
    }

    if( pMsg1->bNeedChangeMap == 1 )
    {
        int nResult = TryRespondChangeStage();
        Log( "���󴥷���ת OnMsgPlayerMovingPos TryRespondChangeStage Result[%d]", nResult );
    }
}

void BasePlayer::OnMsgPlayerMovingPosToDir( const Msg* pMsg )
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
        SSkillTask* pSkillTask = _SkillTaskManager.GetCurTask();
        if (pSkillTask != NULL )
        {
            if ( IsCanCancelSkill( pSkillTask->id ) )
            { 
                OnHaveSkillDisplace();
                IntonateInterrupt( EIT_Move );
                SetStatus( CS_WALK );
            }
        }
        else
        {
            OnHaveSkillDisplace();
            IntonateInterrupt( EIT_Move );
            SetStatus( CS_WALK );
        }

        m_bMoving = true;
    }

    m_vMovingBufPerCheck.x += abs( fx - GetFloatX() );
    m_vMovingBufPerCheck.y += abs( fy - GetFloatY() );

    SetX( fx );
    SetY( fy );
    SetZ( fz );
    SetDirX( fdirx );
    SetDirY( fdiry );
    SetLastReceiveMoveMessageTime( GettheWorld().g_dwLastWorldProcessTime );

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

    //������˵�����Ϣ�򷵻�ȷ�ϵ�����
    if (m_bPosDebugOpen)
    {
        char szBuffer[100];
        sprintf_s(szBuffer, sizeof(szBuffer)-1, "X: %f Y: %f Z: %f", this->GetFloatX(), this->GetFloatY(), this->GetFloatZ());
        TellClient(szBuffer);
    }

    if( pMsg1->bNeedChangeMap == 1 )
    {
        int nResult = TryRespondChangeStage();
        Log( "���󴥷���ת OnMsgPlayerMovingPosToDir TryRespondChangeStage Result[%d]", nResult );
    }
}

void BasePlayer::OnMsgPlayerPos( const Msg* pMsg )
{
    if(!_buffManager.IsCanMove())
    {
        //ShowInfo( false, 1000, 0xffff0000, "��ǰ״̬�����ƶ�" );
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
        SSkillTask* pSkillTask = _SkillTaskManager.GetCurTask();
        if (pSkillTask != NULL )
        {
            if ( IsCanCancelSkill( pSkillTask->id ) )
            { 
                OnHaveSkillDisplace();
                IntonateInterrupt( EIT_Move );
                SetStatus( CS_WALK );
            }
        }
        else
        {
            OnHaveSkillDisplace();
            IntonateInterrupt( EIT_Move );
            SetStatus( CS_WALK );
        }
        
        m_bMoving = true;
    }

    m_vMovingBufPerCheck.x += abs( fx - GetFloatX() );
    m_vMovingBufPerCheck.y += abs( fy - GetFloatY() );

    SetX( fx );
    SetY( fy );
    SetZ( fz );
    SetLastReceiveMoveMessageTime( GettheWorld().g_dwLastWorldProcessTime );

    MsgPlayerPos msg;
    msg.header.stID = GetID();
    msg.vPos.x = GetFloatX();
    msg.vPos.y = GetFloatY();
    msg.vPos.z = GetFloatZ();

    GettheServer().SendMsgToView( &msg, GetID(), true );

    m_bMoving = false;

    //������˵�����Ϣ�򷵻�ȷ�ϵ�����
    if (m_bPosDebugOpen)
    {
        char szBuffer[100];
        sprintf_s(szBuffer, sizeof(szBuffer)-1, "X: %f Y: %f Z: %f", this->GetFloatX(), this->GetFloatY(), this->GetFloatZ());
        TellClient(szBuffer);
    }
    if( GetStatus() == CS_WALK )
    {
        SetStatus( CS_IDLE );
    }
}

void BasePlayer::OnMsgPlayerDir( const Msg* pMsg )
{
    if(!_buffManager.IsCanMove())
    {
        //ShowInfo( false, 1000, 0xffff0000, "��ǰ״̬�����ƶ�" );
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
    SetLastReceiveMoveMessageTime( GettheWorld().g_dwLastWorldProcessTime );

    MsgPlayerDir msg;
    msg.header.stID = GetID();
    msg.chDirX = pMsg1->chDirX;
    msg.chDirY = pMsg1->chDirY;
    msg.chDirZ = pMsg1->chDirZ;
    GettheServer().SendMsgToView( &msg, GetID(), true );

    m_bMoving = false;

    //������˵�����Ϣ�򷵻�ȷ�ϵ�����
    if (m_bPosDebugOpen)
    {
        char szBuffer[100];
        sprintf_s(szBuffer, sizeof(szBuffer)-1, "X: %f Y: %f Z: %f", this->GetFloatX(), this->GetFloatY(), this->GetFloatZ());
        TellClient(szBuffer);
    }

    if( GetStatus() == CS_WALK )
    {
        SetStatus( CS_IDLE );
    }
}

void BasePlayer::OnMsgPlayerPosAndDir( const Msg* pMsg )
{
    if(!_buffManager.IsCanMove())
    {
        //ShowInfo( false, 1000, 0xffff0000, "��ǰ״̬�����ƶ�" );
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
        SSkillTask* pSkillTask = _SkillTaskManager.GetCurTask();
        if (pSkillTask != NULL )
        {
            if ( IsCanCancelSkill( pSkillTask->id ) )
            { 
                OnHaveSkillDisplace();
                IntonateInterrupt( EIT_Move );
                SetStatus( CS_WALK );
            }
        }
        else
        {
            OnHaveSkillDisplace();
            IntonateInterrupt( EIT_Move );
            SetStatus( CS_WALK );
        }
        m_bMoving = true;
    }

    m_vMovingBufPerCheck.x += abs( fx - GetFloatX() );
    m_vMovingBufPerCheck.y += abs( fy - GetFloatY() );

    SetX( fx );
    SetY( fy );
    SetZ( fz );
    SetDirX( fdirx );
    SetDirY( fdiry );
    SetLastReceiveMoveMessageTime( GettheWorld().g_dwLastWorldProcessTime );

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

    //������˵�����Ϣ�򷵻�ȷ�ϵ�����
    if (m_bPosDebugOpen)
    {
        char szBuffer[100];
        sprintf_s(szBuffer, sizeof(szBuffer)-1, "X: %f Y: %f Z: %f", this->GetFloatX(), this->GetFloatY(), this->GetFloatZ());
        TellClient(szBuffer);
    }
    if( GetStatus() == CS_WALK )
    {
        SetStatus( CS_IDLE );
    }
}

void BasePlayer::LogOnlineInfo()
{

    //LOG_MESSAGE( PLAYERLOGIC, LOG_PRIORITY_INFO, "Player:%s IP:%s ����ʱ��:%d(s)", m_szLoginName,m_szLoginIP, (HQ_TimeGetTime()-m_dwLoginTime)/1000 );

}

void BasePlayer::OnQueryCharAround( const Msg* pMsg )
{
    short stRadius = ((MsgQueryCharAround*)pMsg)->stRadius;

    IDListTPL< GameWorld::constMaxCharacters > *pTable = GettheWorld().GetCharTable();
    int nTotal = pTable->Count();
    MsgAckCharAround ackMsg;
    ackMsg.stCharCount = 0;
    for(int i=0;i<nTotal;i++)
    {
        int nID = (*pTable)[i];
        BaseCharacter* c = (BaseCharacter*)theRunTimeData.GetCharacterByID( nID );
        if( c && c != this &&
            ( c->GetObjType() == Object_Player || 
            c->GetObjType() == Object_Monster_Normal ||
            c->GetObjType() == Object_Monster_Enmity) )
        {
            if( c->GetMapID() != GetMapID() )continue;
            if( abs( c->GetX()-GetX() )+abs( c->GetY()-GetY() ) > stRadius )continue;

            if (ackMsg.stCharCount >= 0 && ackMsg.stCharCount < MAX_ACKCHARAROUND)
            {
                ackMsg.charInfos[ackMsg.stCharCount].stId = nID;
                ackMsg.charInfos[ackMsg.stCharCount].stType = Object_Player;
                ackMsg.charInfos[ackMsg.stCharCount].x = c->GetX();
                ackMsg.charInfos[ackMsg.stCharCount].y = c->GetY();
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

void BasePlayer::SendVerifyPos()
{
    MsgVerifyPos verify;
    m_cMoveSerial++;

    verify.header.stID = GetID();
    verify.sNpcID      = GetID();
    verify.x           = GetX();
    verify.y           = GetY();
    verify.cMoveSerial = m_cMoveSerial;
    GettheServer().SendMsgToSingle( &verify, this );
}

void BasePlayer::SendVerifyPos( float fx, float fy )
{
    MsgVerifyPos verify;
    verify.header.stID = GetID();
    verify.sNpcID      = GetID();
    verify.x           = fx;
    verify.y           = fy;
    GettheServer().SendMsgToSingle( &verify, this );
}

bool BasePlayer::IsNeedFixWorldCoordinate( int nGridX, int nGridY)
{
    if( abs(GetFloatX() - TileToFloat(nGridX)) > MAPTILESIZE ||
        abs(GetFloatY() - TileToFloat(nGridY)) > MAPTILESIZE )
        return true;

    return false;
}

// ����Ҫ���Ե��ƶ���Ϣ(��ʼ��һ�ֵ��ƶ�����)
void BasePlayer::ResetCheckMoving()
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

void BasePlayer::PlaySubSkill(short stSkillID, short* pSubSkill, short* pSubSkillLevel, int *pSubcount)
{
    *pSubcount = 0;
}
//-----
//	�Կͻ��˷��͹�����PING��Ϣ�Ĵ���
//-----
void	BasePlayer::OnPingMsg(const Msg* pMsg) 
{
    //MsgPingMsg*  pPing = (MsgPingMsg *)pMsg;
    ////ֻ�ǰѷ��͹�������Ϣ�ͻ�ȥ
    //GettheServer().SendMsg( this, pPing, sendrange_single );
}

void BasePlayer::TellClient( const char* string, ... )
{
    if( !string )
        return;

    va_list	va;
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

void BasePlayer::TellClient( unsigned short ustStringID, UnionParam *pParam /* = NULL */, int nCount /* = 0 */ )
{
    if ( ustStringID == InvalidLogicNumber )
    { return; }

    MsgTellClient xTellClient;
    xTellClient.ustStringID = ustStringID;
    xTellClient.CopyParamData( pParam, nCount );

    GettheServer().SendMsgToSingle( &xTellClient, this );
}

void BasePlayer::ShowMsgBox( const char* string, ... )
{
    if( !string )
        return;

    va_list	va;
    char data[256];
    va_start( va, string );
    wvnsprintf(data, sizeof(data)-1, string, va );
    va_end( va );

    MsgClientShowMsg show;
    show.header.stID = GetID();
    _snprintf(show.szMsg, MsgClientShowMsg::MAXLENGTH-1, string);
    GettheServer().SendMsgToSingle( &show, this );
}

void BasePlayer::ShowInfo( bool bTile, int type, unsigned short ustStringID, UnionParam* pParam /* = NULL */, int nCount /* = 0 */ )
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

void BasePlayer::ShowInfo( bool bTile, int type, const char* string, ... )
{
    if( string == NULL || string[0] == 0 )
        return;

    va_list	va;
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

void BasePlayer::ShowInfo( const char* string, bool bTile, int type )
{
    ShowInfo(bTile, type, string);
}

void BasePlayer::ShowInfoToWorld( bool bTile, /*DWORD time,*/ int type, const char* string, ... )
{
    if( string == NULL || string[0] == 0 )
        return;

    va_list	va;
    char data[512] = {0};
    va_start( va, string );
    wvnsprintf(data, sizeof(data)-1, string, va );
    va_end( va );

    MsgShowText msg;
    msg.header.stID = 0;
    msg.byAlign = MsgShowText::eAlignMiddle;
    msg.bTile = bTile;
    //msg.dwTime = time;
    msg.nShowInfoType = type;
    strncpy_s( msg.szText, MsgShowText::STRING_LEGTH, data, MsgShowText::STRING_LEGTH-1 );
    GettheServer().SendMsgToWorld( &msg );
}

void BasePlayer::ShowFormatInfo( const char* szFormat, ... )
{
    if( !IsPlayer() || szFormat == NULL || szFormat[0] == 0 )
        return;
    char szBuf[1024] = {0};
    //ת������
    va_list vl;
    va_start(vl, szFormat);
    int cnt = vsnprintf(szBuf, sizeof(szBuf)-1, szFormat, vl);
    va_end(vl);
    ShowInfo(szBuf);
}

void BasePlayer::Log(const char* szFormat, ...)
{
    if( !IsPlayer() || szFormat == NULL || szFormat[0] == 0 )
        return;

    char szBuf[1024] = {0};	
    va_list vl;
    va_start(vl, szFormat);
    int cnt = vsnprintf(szBuf, sizeof(szBuf)-1, szFormat, vl);
    va_end(vl);

    if ( szBuf[0] == 0 )
    { return; }

    GamePlayer* pPlayer = (GamePlayer*)this;
    //if ( strcmp( GetPlayerName(), "" ) != 0 && pPlayer->GetDBCharacterID() != 0 )
    {
        LOG_MESSAGE( PLAYERLOGIC, LOG_PRIORITY_INFO, "[%d]\t[%s]\t[%s]\t[%d]\t[%d]\t[%s]\t[%d]\t%s",pPlayer->GetAccountID(), pPlayer->GetAccount(),GetPlayerName(), pPlayer->GetDBCharacterID(), EctypeId2MapId(pPlayer->GetMapID()), GetSessionKey(), GetID(), szBuf );
    }
}

void BasePlayer::DebugLog( const char* szFormat, ...)
{
    if( !IsPlayer() || szFormat == NULL || szFormat[0] == 0 )
        return;

    char szBuf[1024] = {0};	
    va_list vl;
    va_start(vl, szFormat);
    int cnt = vsnprintf(szBuf, sizeof(szBuf)-1, szFormat, vl);
    va_end(vl);

    if ( szBuf[0] == 0 )
    { return; }

    GamePlayer* pPlayer = (GamePlayer*)this;
    //if ( strcmp( GetPlayerName(), "" ) != 0 && pPlayer->GetDBCharacterID() != 0 )
    {
        LOG_MESSAGE( PLAYERLOGIC, LOG_PRIORITY_DEBUG, "[%d]\t[%s]\t[%s]\t[%d]\t[%d]\t[%s]\t[%d]\t%s",pPlayer->GetAccountID(), pPlayer->GetAccount(),GetPlayerName(), pPlayer->GetDBCharacterID(), EctypeId2MapId(pPlayer->GetMapID()), GetSessionKey(), GetID(), szBuf );
    }

}

void BasePlayer::ShoppingLog(const char* szFormat, ...)
{
    if( !IsPlayer() || szFormat == NULL || szFormat[0] == 0 )
        return;

    char szBuf[1024] = {0};
    // ת������
    va_list vl;
    va_start(vl, szFormat);
    int cnt = vsnprintf(szBuf, sizeof(szBuf)-1, szFormat, vl);
    va_end(vl);

    if ( szBuf[0] == 0 )
    { return; }

    GamePlayer* pPlayer = (GamePlayer*)this;
    //if ( strcmp( GetPlayerName(), "" ) != 0 && pPlayer->GetDBCharacterID() != 0 )
    {
        LOG_MESSAGE( SHOPPINGOBJECT, LOG_PRIORITY_INFO, "[%d]\t[%s]\t[%s]\t[%d]\t[%d]\t%s",pPlayer->GetAccountID(), pPlayer->GetAccount(), GetPlayerName(), pPlayer->GetDBCharacterID(), GetID(),szBuf );
    }
}

void BasePlayer::CheckCheatLog( const char* szFormat, ... )
{
    if( !IsPlayer() || szFormat == NULL || szFormat[0] == 0 )
        return;

    char szBuf[1024] = {0};
    // ת������
    va_list vl;
    va_start(vl, szFormat);
    int cnt = vsnprintf(szBuf, sizeof(szBuf)-1, szFormat, vl);
    va_end(vl);

    if ( szBuf[0] == 0 )
    { return; }

    GamePlayer* pPlayer = (GamePlayer*)this;
    //if ( strcmp( GetPlayerName(), "" ) != 0 && pPlayer->GetDBCharacterID() != 0 )
    {
        LOG_MESSAGE( CHECKCHEATOBJECT, LOG_PRIORITY_INFO, "[%d]\t[%s]\t[%d]\t[%s]\t%s",pPlayer->GetAccountID(), pPlayer->GetAccount(), pPlayer->GetDBCharacterID(), GetPlayerName(), szBuf );
    }
}

BOOL BasePlayer::CheckMoving()
{
    return TRUE;

    //if( m_shMovingCount < CHECKMOVINGRATE )
    //{
    //	if( !m_bCheckMovingPerCheck && m_shMovingCount == m_shCheckMovingIndex )
    //	{
    //		m_bCheckMovingPerCheck = TRUE;
    //		D3DXVECTOR3 vOffPos;
    //		vOffPos.x = GetFloatX() - m_vStartMovingPosPerCheck.x;
    //		vOffPos.y = GetFloatY() - m_vStartMovingPosPerCheck.y;
    //		vOffPos.z = 0;
    //		float fDistance = D3DXVec3Length( &vOffPos );
    //		float fMaxDistance = (float)g_nSendMovingMessageRate*0.001f*GetMoveSpeed()*(m_shMovingCount+4);

    //		int nReceiveMovingMsgCastTime = g_nSendMovingMessageRate*(m_shMovingCount+1) - g_nSendMovingMessageRate*3; //����Check������ô����ϢӦ����ʱ��
    //		int nThisCheckCastTime = HQ_TimeGetTime() - m_dwStartMovingTimePerCheck; //����Check���õ�ʱ��
    //		//int nErrorTime = nReceiveMovingMsgCastTime - nThisCheckCastTime; //�ƶ���Ϣ����Ƶ�ʵĳ���ʱ��
    //		float fErrorDistance = fDistance - fMaxDistance;

    //		//if( nErrorTime > 0 )
    //		//{
    //		//	//char szBuf[256];
    //		//	//_snprintf( szBuf, 256, "fErrorDistance = %f Count = %d Speed = %f",fErrorDistance, m_shMovingCount+1, GetMoveSpeed());
    //		//	//TellClient( szBuf );
    //		//	//_snprintf( szBuf, 256, "MaxDistance = %f time = %d", fMaxDistance, nReceiveMovingMsgCastTime - nThisCheckCastTime );
    //		//	//TellClient( szBuf );

    //		//	m_shMovingErrorCount++;

    //		//	if( nErrorTime > 1000 )
    //		//	{
    //		//		if( nErrorTime > 2000 )
    //		//		{
    //		//			m_nCredit -= 1000;
    //		//			Log("[%s]�ƶ���Ϣ����Ƶ�����س��� ����ʱ�� %d ��ǰ���� %d ��ǰ�ƶ��ٶ� %f", GetPlayerName(), nErrorTime, m_nCredit, GetMoveRate() );
    //		//		}
    //		//		else
    //		//		{
    //		//			Log("[%s]�ƶ���Ϣ����Ƶ�ʳ��� ����ʱ�� %d ��ǰ���� %d ��ǰ�ƶ��ٶ� %f", GetPlayerName(), nErrorTime, m_nCredit, GetMoveRate() );
    //		//		}
    //		//		m_nCredit -= 1000;
    //		//		m_shMovingErrorCount = 10;
    //		//	}

    //		//	if( m_shMovingErrorCount > 4 )
    //		//	{
    //		//		m_nCredit -= 1000;
    //		//		if( m_nCredit < 5000 )
    //		//		{
    //		//			Log("[%s]�ƶ���Ϣ����Ƶ�ʳ��� ����ʱ�� %d ��ǰ���� %d ��ǰ�ƶ��ٶ� %f", GetPlayerName(), nErrorTime, m_nCredit, GetMoveRate() );
    //		//		}
    //		//		m_shMovingErrorCount = 4;
    //		//	}
    //		//	ResetCheckMoving();
    //		//}

    //		if( fErrorDistance > 0 )
    //		{
    //			//char szBuf[256];
    //			//_snprintf( szBuf, 256, "fErrorDistance = %f Count = %d Speed = %f",fErrorDistance, m_shMovingCount+1, GetMoveSpeed());
    //			//TellClient( szBuf );
    //			//_snprintf( szBuf, 256, "MaxDistance = %f time = %d", fMaxDistance, nReceiveMovingMsgCastTime - nThisCheckCastTime );
    //			//TellClient( szBuf );

    //			//SendVerifyPos( m_vStartMovingPosPerCheck.x, m_vStartMovingPosPerCheck.y );
    //			//SetX(m_vStartMovingPosPerCheck.x);
    //			//SetY(m_vStartMovingPosPerCheck.y);

    //			//m_shMovingCount = 0;
    //			//m_shCheckMovingIndex = theRand.rand32()%(CHECKMOVINGRATE-10)+10;
    //			//m_dwStartMovingTimePerCheck = HQ_TimeGetTime();
    //			//m_bCheckMovingPerCheck = FALSE;
    //			//m_vStartMovingPosPerCheck.x = GetFloatX();
    //			//m_vStartMovingPosPerCheck.y = GetFloatY();
    //			//m_vStartMovingPosPerCheck.z = 0;

    //			m_shMovingErrorCount++;

    //			if( fErrorDistance > 10 )
    //			{
    //				if( fErrorDistance > 20 )
    //				{
    //					m_nCredit -= 2000;
    //					if( fErrorDistance > 256 )
    //					{
    //						m_nCredit -= 20000;
    //					}
    //					Log("[%s]�ƶ��������س��� ������� %f ��ǰ���� %d ��ǰ�ƶ��ٶ� %f", GetPlayerName(), fErrorDistance, m_nCredit, GetMoveRate() );
    //					return FALSE;
    //				}
    //				else
    //				{
    //					Log("[%s]�ƶ����볬�� ������� %f ��ǰ���� %d ��ǰ�ƶ��ٶ� %f", GetPlayerName(), fErrorDistance, m_nCredit, GetMoveRate() );
    //				}
    //				m_nCredit -= 1000;
    //				m_shMovingErrorCount = 10;
    //			}

    //			if( m_shMovingErrorCount > 4 )
    //			{
    //				m_nCredit -= 1000;
    //				if( m_nCredit < 5000 )
    //				{
    //					Log("[%s]�ƶ�����Ƿ����� %d ������� %f ��ǰ���� %d ��ǰ�ƶ��ٶ� %f", GetPlayerName(), fErrorDistance, m_nCredit, GetMoveRate() );
    //				}
    //				m_shMovingErrorCount = 4;
    //			}
    //			ResetCheckMoving();
    //		}
    //	}
    //	m_shMovingCount++;
    //}
    //else
    //{
    //	ResetCheckMoving();

    //	m_shCheckMovingCount++;
    //	if( m_shCheckMovingCount > 6 )
    //	{
    //		m_shCheckMovingCount = 0;
    //		if( m_shMovingErrorCount > 0 )
    //		{
    //			m_shMovingErrorCount--;
    //		}
    //	}
    //}
    //return TRUE;

    //if( m_shMovingCount < CHECKMOVINGRATE )
    //{
    //	if( !m_bCheckMovingPerCheck && m_shMovingCount == m_shCheckMovingIndex )
    //	{
    //		m_bCheckMovingPerCheck = TRUE;
    //		//D3DXVECTOR3 vOffPos;
    //		//vOffPos.x = GetFloatX() - m_vStartMovingPosPerCheck.x;
    //		//vOffPos.y = GetFloatY() - m_vStartMovingPosPerCheck.y;
    //		//vOffPos.z = 0;
    //		//float fDistance = D3DXVec3Length( &m_vMovingBufPerCheck );

    //		//char szBuf[256];
    //		//_snprintf( szBuf, 256, "MaxDistance = %f %d %d", fDistance, m_shMovingCount, HQ_TimeGetTime() - m_dwStartMovingTimePerCheck );
    //		//TellClient( szBuf );

    //		//float fMaxDistance = (float)g_nSendMovingMessageRate*0.001f*GetMoveSpeed()*(m_shMovingCount+4);

    //		//int nReceiveMovingMsgCastTime = g_nSendMovingMessageRate*(m_shMovingCount+1) - g_nSendMovingMessageRate*3; //����Check������ô����ϢӦ����ʱ��
    //		//int nThisCheckCastTime = HQ_TimeGetTime() - m_dwStartMovingTimePerCheck; //����Check���õ�ʱ��
    //		//float fErrorDistance = fDistance - fMaxDistance;

    //		//if( fErrorDistance > 0 )
    //		//{
    //		//	//char szBuf[256];
    //		//	//_snprintf( szBuf, 256, "fErrorDistance = %f Count = %d Speed = %f",fErrorDistance, m_shMovingCount+1, GetMoveSpeed());
    //		//	//TellClient( szBuf );
    //		//	//_snprintf( szBuf, 256, "MaxDistance = %f time = %d", fMaxDistance, nReceiveMovingMsgCastTime - nThisCheckCastTime );
    //		//	//TellClient( szBuf );

    //		//	//SendVerifyPos( m_vStartMovingPosPerCheck.x, m_vStartMovingPosPerCheck.y );
    //		//	//SetX(m_vStartMovingPosPerCheck.x);
    //		//	//SetY(m_vStartMovingPosPerCheck.y);

    //		//	//m_shMovingCount = 0;
    //		//	//m_shCheckMovingIndex = theRand.rand32()%(CHECKMOVINGRATE-10)+10;
    //		//	//m_dwStartMovingTimePerCheck = HQ_TimeGetTime();
    //		//	//m_bCheckMovingPerCheck = FALSE;
    //		//	//m_vStartMovingPosPerCheck.x = GetFloatX();
    //		//	//m_vStartMovingPosPerCheck.y = GetFloatY();
    //		//	//m_vStartMovingPosPerCheck.z = 0;

    //		//	m_shMovingErrorCount++;

    //		//	if( fErrorDistance > 10 )
    //		//	{
    //		//		if( fErrorDistance > 20 )
    //		//		{
    //		//			m_nCredit -= 2000;
    //		//			if( fErrorDistance > 256 )
    //		//			{
    //		//				m_nCredit -= 20000;
    //		//			}
    //		//			Log("[%s]�ƶ��������س��� ������� %f ��ǰ���� %d ��ǰ�ƶ��ٶ� %f", GetPlayerName(), fErrorDistance, m_nCredit, GetMoveRate() );
    //		//			return FALSE;
    //		//		}
    //		//		else
    //		//		{
    //		//			Log("[%s]�ƶ����볬�� ������� %f ��ǰ���� %d ��ǰ�ƶ��ٶ� %f", GetPlayerName(), fErrorDistance, m_nCredit, GetMoveRate() );
    //		//		}
    //		//		m_nCredit -= 1000;
    //		//		m_shMovingErrorCount = 10;
    //		//	}

    //		//	if( m_shMovingErrorCount > 4 )
    //		//	{
    //		//		m_nCredit -= 1000;
    //		//		if( m_nCredit < 5000 )
    //		//		{
    //		//			Log("[%s]�ƶ�����Ƿ����� %d ������� %f ��ǰ���� %d ��ǰ�ƶ��ٶ� %f", GetPlayerName(), fErrorDistance, m_nCredit, GetMoveRate() );
    //		//		}
    //		//		m_shMovingErrorCount = 4;
    //		//	}
    //			ResetCheckMoving();
    //		//}
    //	}
    //	m_shMovingCount++;
    //}
    //else
    //{
    //	ResetCheckMoving();

    //	m_shCheckMovingCount++;
    //	if( m_shCheckMovingCount > 6 )
    //	{
    //		m_shCheckMovingCount = 0;
    //		if( m_shMovingErrorCount > 0 )
    //		{
    //			m_shMovingErrorCount--;
    //		}
    //	}
    //}
    //return TRUE;
}

bool BasePlayer::CheckPosRightful()
{
    float fDistance     = D3DXVec3Length( &m_vMovingBufPerCheck );
    float fCurMoveSpeed = GetMoveSpeed();

    // ���ܻ���١����������漼�ܡ�
    if( m_fLastMoveSpeedPerCheck > fCurMoveSpeed )
        fCurMoveSpeed = m_fLastMoveSpeedPerCheck;

    if( fCurMoveSpeed < BaseMoveSpeed )
        fCurMoveSpeed = BaseMoveSpeed;

    float fClientMoveSpeed = 0;

    if( m_dwClientPassedTimePerCheck > 0 )
    {
        if( m_dwClientPassedTimePerCheck < 3000 )
            m_dwClientPassedTimePerCheck = 3000;

        fClientMoveSpeed = fDistance/m_dwClientPassedTimePerCheck*1000;

        // �Գ��ʱ�ķſ���
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

    //// �������ӳٵ��ж����������Ļ�Ҫ�����ߣ���Ϊ���ߵĻ����Ǹ���������õ�©����
    //if( m_dwClientPassedTimePerCheck > 4500 )
    //{
    //	m_nCredit -= 4000;
    //}

    if( m_bAssaultMovingProcess || fCurMoveSpeed )
        m_fLastMoveSpeedPerCheck = GetMoveSpeed() + 25.0f;
    else
        m_fLastMoveSpeedPerCheck = GetMoveSpeed();

    CheckCredit();
    ResetCheckMoving();
    return true;
}

void BasePlayer::CheckCredit()
{
    //��ʱ��������
    if( m_nCredit < 0 )
    {
        if( m_nKickCount >=1 )
        {
            if( g_Cfg.bKickPlayerByCredit )
            {
                SetX( m_vStartMovingPosPerCheck.x );
                SetY( m_vStartMovingPosPerCheck.y );
                SetZ( m_vStartMovingPosPerCheck.z );
                Log(theXmlString.GetString(eLog_info_2slk_44), m_nCredit );
                CheckCheatLog(theXmlString.GetString(eLog_info_2slk_44), m_nCredit );
                CriticalError(__FUNCTION__, __FILE__, __LINE__);
            }
            else
            {
                SendVerifyPos( m_vStartMovingPosPerCheck.x, m_vStartMovingPosPerCheck.y );
                SetX( m_vStartMovingPosPerCheck.x );
                SetY( m_vStartMovingPosPerCheck.y );
                SetZ( m_vStartMovingPosPerCheck.z );
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
            SetX( m_vStartMovingPosPerCheck.x );
            SetY( m_vStartMovingPosPerCheck.y );
            SetZ( m_vStartMovingPosPerCheck.z );
            Log(theXmlString.GetString(eLog_info_2slk_47), m_nCredit );
            CheckCheatLog(theXmlString.GetString(eLog_info_2slk_47), m_nCredit );
            m_nCredit = 4000;
            m_dwEnterWorldServerTime = m_dwClientLastSendMovingMsgServerTime;
            m_dwEnterWorldClientTime = m_dwClientLastSendMovingMsgTime;
            m_nKickCount++;
        }
    }
}

bool BasePlayer::CheckMovingMsgSendTime( DWORD dwSendTime )
{ // ÿ���ƶ���Ϣ������ô˺���
    if( m_dwEnterWorldClientTime > dwSendTime )
    {
        m_nCredit -= 10000000;
        // ToLog( false && "���ش��������������ݵ�����ǲ���������" );
        Log(theXmlString.GetString(eLog_info_2slk_48));
    }
    else
    {
        if( m_dwClientLastSendMovingMsgTime > dwSendTime )
        {
            m_nCredit -= 10000000;// ToLog( false && "���ش��������������ݵ�����ǲ���������" );//�����
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
            //	dwTimeOffset = dwServerPassedTime - dwClientPassedTime;
            //	dwTimeOffset = dwTimeOffset*0.25f;
            //}

            //�ϴ��ƶ�ʱ��ͱ����ƶ�ʱ��Ĳ�
            if( m_dwClientPassedTimePerCheck == 0 )
            {
                // �Ե�һ�βɼ����ݵ����⴦��
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
                    Log("[%s]�ƶ���Ϣ�����ӳٵ�̫������ %d", GetPlayerName(), dwClientPassedTime - dwServerPassedTime );
                else
                {
                    Log(theXmlString.GetString(eLog_info_2slk_50), dwTimeOffset );
                    ShowInfo(false, 257,  theXmlString.GetString(eClient_AddInfo_2slk_83), 0); 
                }
            }
        }
    }

    m_dwClientLastSendMovingMsgServerTime = HQ_TimeGetTime();
    m_dwClientLastSendMovingMsgTime       = dwSendTime;
    return true;
}

void BasePlayer::DoAssaultMoving()
{
    m_bAssaultMovingProcess = true;
}

bool BasePlayer::DoHitch( int nTrafficID, bool bBack, bool bGoOn )
{
    // idΪ-1ʱ��ʾ����
    if (nTrafficID == -1)
    {
        SetRideMountId( -1 );
        DoRide( -1 );
        return false;
    }
    
    CItemDetail::STraffic* pTrafficInfo = GettheItemDetail().GetTrafficByID( nTrafficID );
    if( pTrafficInfo == NULL )
    { return false;}

    SRoute route;
    GetRouteManager().GetRouteInfo( pTrafficInfo->nMapID, pTrafficInfo->nRouteID, route );

    int nDromeID = pTrafficInfo->nDromeID;

    // idΪ-1ʱ��ʾ����            
    CItemDetail::SDrome* pDromeInfo = GettheItemDetail().GetDromeByID( nDromeID );
    if( pDromeInfo == NULL )
    { 
        DoRide( -1 );
        return false;
   }

    if ( !bGoOn )
    {
        IntonateInterrupt( EIT_Force );

        //������ҵĿ���Ȩ
        MsgCanControlMoving msg;
        msg.header.stID       = GetID();
        msg.bCanControlMoving = false;
        if ( route.flyRoute )
        { msg.bIsFlyMoving = true ; }
        else
        { msg.bIsFlyMoving = false; }
        
        GamePlayer* pPlayer = static_cast< GamePlayer* >( this );
        pPlayer->SetFlyMoving( msg.bIsFlyMoving );
        GettheServer().SendMsgToView( &msg, GetID() );
    }

    MsgChangeDrome changedrome;
    changedrome.header.stID = GetID();
    changedrome.nDromeID    = nDromeID;	
    changedrome.ucOpType    = MsgChangeDrome::EOT_Ride;
    GettheServer().SendMsgToView( &changedrome, GetID(), false );

    SetRideMountId( nDromeID );

    m_bHitchMoving = true;
    m_bHitchBack   = bBack;
    m_nTrafficID   = nTrafficID;
    m_dwRouteStep  = 0;
    return true;
}

int BasePlayer::GetCurTrafficID()
{
    if( m_bHitchMoving )
        return m_nTrafficID;
    return -1;
}

void BasePlayer::DoHitchMoving( int nTrafficID )
{
    if ( IsDead() || GetRideId() < 0)
    { 
        CancelHitchMoving();
        return;
    }
    
    D3DXVECTOR3 vPos = GetPos();
    float fErrDistance = 0.0f, fSpeed = 0.0f;

    if( GetRouteManager().GetCurTrafficRoute( nTrafficID, m_bHitchBack, m_dwRouteStep, fSpeed, vPos, fErrDistance ) )
    {
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
    { // �ò�����
        CItemDetail::STraffic* pTrafficInfo = GettheItemDetail().GetTrafficByID( nTrafficID );
        if( pTrafficInfo == NULL || pTrafficInfo->nextTrafficId == -1)
        {
            CancelHitchMoving();
            return;
        }

        if ( DoHitch( pTrafficInfo->nextTrafficId, m_bHitchBack, true )  )
        { return; }
        else
        { CancelHitchMoving(); }
    }
    
    if( fErrDistance > 32 )
    {
        m_nCredit -= 4000;
        if( GettheItemDetail().GetTrafficByID( nTrafficID ) )
        {
            Log(theXmlString.GetStringWithName(eLog_info_2slk_51), GetPlayerName(), nTrafficID, "" );
        }
        else
        {
            Log(theXmlString.GetStringWithName(eLog_info_2slk_52), GetPlayerName(), nTrafficID);
        }
    }

    return;
}

void BasePlayer::CancelHitchMoving()
{
    m_bHitchMoving = false;
    m_bHitchBack   = false;
    m_nTrafficID     = -1;
    m_dwRouteStep  = 0;

    // ��������»�ÿ���Ȩ
    MsgCanControlMoving msg;
    msg.header.stID       = GetID();
    msg.bCanControlMoving = true;
    msg.bIsFlyMoving      = false;

    GamePlayer* pPlayer = static_cast< GamePlayer* >( this );
    pPlayer->SetFlyMoving( msg.bIsFlyMoving );
    GettheServer().SendMsgToView( &msg, GetID() );

    GetCharFightAttr()->moveSpeed.base = BaseMoveSpeed;
    GetCharFightAttr()->moveSpeed.UpdateFinal();
    ChangeAttr( CharAttr_MoveSpeed, GetMoveSpeed() );

    // �����������
    if( GetRideId() >= 0 )
    { DoRide( -1 ); }
}

long BasePlayer::TryRespondChangeStage()
{
    int iMapId = GetMapID();
    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( EctypeId2MapId( iMapId ) );
    if ( pMapData == NULL )
        return ER_MapCfgNotFound;

    MapConfig::TransportPosition* pTransportPosition = pMapData->GetTransportPositionByPositon( GetFloatX(), GetFloatY() );
    if ( pTransportPosition == NULL )
        return ER_NotInTransportRegion;

    MapConfig::MapData* pMapDataTarget = theMapConfig.GetMapDataById( pTransportPosition->TargetMapId );
    if ( pMapDataTarget == NULL )
        return ER_MapCfgNotFound;

    MapConfig::TransportDestination* pTransportDestination = pMapDataTarget->GetTransportDestinationById( pTransportPosition->TargetId );
    if ( pTransportDestination == NULL )
        return ER_NotTargetTransportRegion;

    GamePlayer* pPlayer = static_cast< GamePlayer* >( this );
    pPlayer->FlyToMapReq( pTransportPosition->TargetMapId, pTransportDestination->PositionX, pTransportDestination->PositionY, pTransportDestination->Direction );

    Log( "���󴥷���ת Ŀ���ͼ[%d]", pTransportPosition->TargetMapId );

    return ER_Success;
}