#include "GamePlayer.h"
#include "FuncPerformanceLog.h"
//#include "MeNetwork.h"
#include "PosChangePackage.h"
#include "EnterMySightPackage.h"
#include "AckEnterWorldPackage.h"
#include "GateServer.h"
#include "Config.h"
#include "CountryMessage.h"

const DWORD dwSendPackDelay = 200;  // ���ٰ�������Ż��İ���Ϣ;

GamePlayer::GamePlayer()
{
    m_dwLastSendPackTime     = 0;
	m_iFreeCount             = 0;
	_iGameServerPlayerId     = InvalidGameObjectId;
	_iGateServerPlayerId     = InvalidGameObjectId;
	m_bHasSendClientExit     = false;
    m_nAccountID             = 0xFFFFFFFF;
    //memset (m_SessionKey,0,sizeof(m_SessionKey));
	m_SessionKey             = 0;
    m_dwDisConnectTime       = 0;
    m_dwAcceptTime           = 0;
    m_bIsSendConnectInfo     = false;
    m_pConnector             = NULL;
    
	SetPlayer( true );
	SetPingTime(HQ_TimeGetTime());

	_clientStatus = EStatusType_None;
    _dwSendSwitchGateingTime = 0;
    _level = 0;
    _country = 0;
}

GamePlayer::~GamePlayer()
{
	m_iFreeCount = -1;
    ReleaseConnector();
    SetPlayer( false );
}

void GamePlayer::SetConnector( /*IMeConnector*/Socketer* pMeConnector, bool bReleaseOld /*= true */) 
{ 
    if ( bReleaseOld )
    { ReleaseConnector(); }// ��ɾ��ԭ������Դ 
    
    m_pConnector = pMeConnector;  
}

void GamePlayer::ReleaseConnector()
{
    if( m_pConnector != NULL )
    {
        //m_pConnector->Close();
        /*GetMeNetwork().ReleaseMeConnector( m_pConnector->GetKey());*/
		Socketer_release(m_pConnector);
        m_pConnector = NULL;
    }
}

void GamePlayer::SendMsg( Msg* pMsg )
{
    if ( NULL == pMsg)
    { return; }

    //�������ֱ�ӷ����ͻ��˵��ƶ���Ϣ��һЩ�Ż�����
    switch (pMsg->GetType())
    {
    case MSG_PLAYERMOVINGPOS:                       //�ƶ������λ�øı����Ϣ
        OnPlayerMoveingPos(static_cast<MsgPlayerMovingPos*>(pMsg));
        break;
    case MSG_PLAYERMOVINGPOSANDDIR:                 //�ƶ������λ�úͳ���ı����Ϣ
        OnPlayerMovingPosAndDir(static_cast<MsgPlayerMovingPosAndDir*>(pMsg));
        break;
    case MSG_PLAYERPOS:                             //ԭ�ز�����ҵ�λ����Ϣ
        OnPlayerPos(static_cast<MsgPlayerPos*>(pMsg));
        break;
    case MSG_PLAYERDIR:                             //ԭ�ز�����ҵĳ�����Ϣ
        OnPlayerDir(static_cast<MsgPlayerDir*>(pMsg));
        break;
    case MSG_PLAYERPOSANDDIR:                       //ԭ�ز�����ҵ�λ�úͳ�����Ϣ
        OnPlayerPosAndDir(static_cast<MsgPlayerPosAndDir*>(pMsg));
        break;
    case MSG_PLAYERVERIFYPOS:						//�����У������Ϣ
        OnPlayerVerifyPos(static_cast<MsgPlayerVerifyPos*>(pMsg));
        break;
    case MSG_UNPLAYERMOVINGTOPOS:					//�����λ���ƶ���Ϣ
        OnUnPlayerMovingToPos(static_cast<MsgUnPlayerMovingToPos*>(pMsg));
        break;
    case MSG_UNPLAYERVERIFYPOS:						//�������У������Ϣ
        OnUnPlayerVerifyPos(static_cast<MsgUnPlayerVerifyPos*>(pMsg));
        break;
    case MSG_UNPLAYERCLOSINGTOLOCKTARGET:			
        OnUnPlayerCloseingToLockTarget(static_cast<MsgUnPlayerClosingToLockTarget*>(pMsg));
        break;
    case MSG_ACKENTERWORLD:
        OnAckEnterWorld(static_cast<MsgAckEnterWorld*>(pMsg));
		TESTECHORECV( GetAccountID(), MsgAckEnterWorld )
        break;
    case MSG_ADD_FIRSTLIST:
        AddFirstIDToList(static_cast<MsgAddFirstList*>(pMsg)->shCharID);
        break;
    case MSG_REMOVE_FIRSTLIST:
        RemoveFirstIDFromList(static_cast<MsgRemoveFirstList*>(pMsg)->shCharID);
        break;
    case MSG_COUNTRYTELLCOUNTRYID:
        OnTellCountryID( static_cast< MsgCountryTellCountryID* >( pMsg ) );
        break; 
    case MSG_SWITCHGATE:
        SetClientStatus( GamePlayer::EStatusType_WaitSwitchGateCallBack );
        SendToClient( pMsg );
        break;
    case MSG_SEECHARLEVELUP:
        OnChangeLevel( static_cast< MsgSeeCharacterLevelup* >( pMsg ) );
        break;
    default:
        SendToClient( pMsg );
        break;
    }
}

void GamePlayer::SendToClient( Msg* pMessage )
{
    if ( m_pConnector == NULL || pMessage == NULL )
    { return; }
    m_pConnector->SendMsg( pMessage/*, IMeConnector::ECT_Normal, theCfg.gEncryptMode*/ );
}

void GamePlayer::SendPackage()
{
    if (!m_entermysightpack.IsEmpty())
    {
        static MsgEnterMySightPack package;
        if (m_entermysightpack.MakePackMsg(package))
        {
            SendMsg(&package);
        }
        m_entermysightpack.Clear();
    }

    if (HQ_TimeGetTime() - m_dwLastSendPackTime < dwSendPackDelay)
        return;

    //�жϵ�ǰ���Ͷ������Ƿ��д���Ϣ 
    //��ΪnetworkĿǰֻ�ܼ���һ����Ϣ�����Դ�����Ϣ��������ͣ�������͵���ϢҲ������ȥ��
    //�Ϳ����϶�������Ϣ�������ͳ�ȥ
    /*IMeConnector*/Socketer* pConnecter = GetConnector();
    if ( pConnecter == NULL )
    { return; }

    /*if (pConnecter->GetOutMsgWatchType() != MSG_POSCHANGE)
    { 
        pConnecter->SetOutMsgWatchType(MSG_POSCHANGE);
    }
    else
    { 
        if (pConnecter->GetOutMsgWatchNum() == 0)*/
        { // ���û�оͷ��͡�
            static MsgPosChange      msgpos;
            static CPosChangePackage package;
            package.Clear();

            // ����ͨ�����η���ʱ��Ĳ�ֵ��̬�������Ͱ��Ĵ�С
            const unsigned int DEFAULT_SENDSIZE = 100; // Ĭ��һ�θ���100����ɫ��λ���ƶ���Ϣ
            package.SetMaxSize(DEFAULT_SENDSIZE);     
            if (MakePosChangePackage(package))
            {
                ClearCharPosInfo();
                if (package.MakePackMsg(msgpos))
                {
                    SendMsg(&msgpos);
                }
            }
            m_dwLastSendPackTime = HQ_TimeGetTime();
        }
    //}
}

void GamePlayer::OnPlayerMoveingPos( MsgPlayerMovingPos* pMsg )
{
    if ( pMsg->vPos.z > WORLD_HEIGHT || pMsg->vPos.z < -WORLD_HEIGHT )
    { pMsg->vPos.z = 0; }

    // ����ڽ�ֹ�Ż��б��д������Ż�
    if ( IDIsInFirstList(pMsg->header.stID))
    {
        pMsg->header.uMsgLevel = level_high;
        GetConnector()->SendMsg( pMsg/*, IMeConnector::ECT_Normal, theCfg.gEncryptMode */);
        return;
    }

    uint32 nPos = FindEmptyPos( pMsg->header.stID );

    if (nPos == ErrorUnsignedLongID)
    { return; }

	m_CharPosInfoList[nPos].vPos = pMsg->vPos;

	//����������Ѿ���δ��������Ϣ������ô��������������ݰ��������
	if( m_CharPosInfoList[nPos].nID == pMsg->header.stID )
	{
		if( m_CharPosInfoList[nPos].nType == CPosChangePackage::PACK_MSG_PLAYERDIR 
			|| m_CharPosInfoList[nPos].nType == CPosChangePackage::PACK_MSG_PLAYERPOSANDDIR
			|| m_CharPosInfoList[nPos].nType == CPosChangePackage::PACK_MSG_PLAYERMOVINGPOSANDDIR )
		{
			m_CharPosInfoList[nPos].nID = pMsg->header.stID;
            m_CharPosInfoList[nPos].nType = CPosChangePackage::PACK_MSG_PLAYERMOVINGPOSANDDIR;
            m_CharPosInfoList[nPos].chOptimize = SPosChangeInfo::Optimize_MovingPosAndDir;
		}
		else
		{
			m_CharPosInfoList[nPos].nID = pMsg->header.stID;
			m_CharPosInfoList[nPos].nType = CPosChangePackage::PACK_MSG_PLAYERMOVINGPOS;
            m_CharPosInfoList[nPos].chOptimize = SPosChangeInfo::Optimize_MovingPos;
		}
	}
	else
	{
		m_CharPosInfoList[nPos].nID = pMsg->header.stID;
		m_CharPosInfoList[nPos].nType = CPosChangePackage::PACK_MSG_PLAYERMOVINGPOS;
        m_CharPosInfoList[nPos].chOptimize = SPosChangeInfo::Optimize_None;
	}
}

void GamePlayer::OnPlayerMovingPosAndDir( MsgPlayerMovingPosAndDir* pMsg )
{
    if ( pMsg->vPos.z > WORLD_HEIGHT || pMsg->vPos.z < -WORLD_HEIGHT )
    { pMsg->vPos.z = 0; }

    //����ڽ�ֹ�Ż��б��д������Ż�
    if ( IDIsInFirstList(pMsg->header.stID) )
    {
        pMsg->header.uMsgLevel = level_high;
        GetConnector()->SendMsg( pMsg/*, IMeConnector::ECT_Normal, theCfg.gEncryptMode */);
        return;
    }

    uint32 nPos = FindEmptyPos(pMsg->header.stID);
    if ( nPos == ErrorUnsignedLongID )
    { return; }

    m_CharPosInfoList[nPos].nType  = CPosChangePackage::PACK_MSG_PLAYERMOVINGPOSANDDIR;
    m_CharPosInfoList[nPos].vPos   = pMsg->vPos;
    m_CharPosInfoList[nPos].chDirX = pMsg->chDirX;
    m_CharPosInfoList[nPos].chDirY = pMsg->chDirY;
    m_CharPosInfoList[nPos].chDirZ = pMsg->chDirZ;

    //����������Ѿ���δ��������Ϣ������ô��������������ݰ��������
    if( m_CharPosInfoList[nPos].nID == pMsg->header.stID )
    {
        m_CharPosInfoList[nPos].chOptimize = SPosChangeInfo::Optimize_MovingPos;
    }
    else
    {
        m_CharPosInfoList[nPos].nID = pMsg->header.stID;
        m_CharPosInfoList[nPos].chOptimize = SPosChangeInfo::Optimize_None;
    }
}

void GamePlayer::OnPlayerPos(MsgPlayerPos* pMsg)
{
    if ( pMsg->vPos.z > WORLD_HEIGHT || pMsg->vPos.z < -WORLD_HEIGHT )
    { pMsg->vPos.z = 0; }

    //����ڽ�ֹ�Ż��б��д������Ż�
    if ( IDIsInFirstList(pMsg->header.stID) )
    {
        pMsg->header.uMsgLevel = level_high;
        GetConnector()->SendMsg( pMsg/*, IMeConnector::ECT_Normal, theCfg.gEncryptMode */);
        return;
    }

    uint32 nPos = FindEmptyPos(pMsg->header.stID);
    if (nPos == ErrorUnsignedLongID)
    { return; }

    m_CharPosInfoList[nPos].vPos = pMsg->vPos;

    //����������Ѿ���δ��������Ϣ������ô��������������ݰ��������
    if( m_CharPosInfoList[nPos].nID == pMsg->header.stID )
    {
        if( m_CharPosInfoList[nPos].nType == CPosChangePackage::PACK_MSG_PLAYERDIR 
            || m_CharPosInfoList[nPos].nType == CPosChangePackage::PACK_MSG_PLAYERPOSANDDIR
            || m_CharPosInfoList[nPos].nType == CPosChangePackage::PACK_MSG_PLAYERMOVINGPOSANDDIR )
        {
            m_CharPosInfoList[nPos].nID = pMsg->header.stID;
            m_CharPosInfoList[nPos].nType = CPosChangePackage::PACK_MSG_PLAYERPOSANDDIR;
            m_CharPosInfoList[nPos].chOptimize = SPosChangeInfo::Optimize_PosAndDir;
        }
        else
        {
            m_CharPosInfoList[nPos].nID = pMsg->header.stID;
            m_CharPosInfoList[nPos].nType = CPosChangePackage::PACK_MSG_PLAYERPOS;
            m_CharPosInfoList[nPos].chOptimize = SPosChangeInfo::Optimize_Pos;
        }
    }
    else
    {
        m_CharPosInfoList[nPos].nID = pMsg->header.stID;
        m_CharPosInfoList[nPos].nType = CPosChangePackage::PACK_MSG_PLAYERPOS;
        m_CharPosInfoList[nPos].chOptimize = SPosChangeInfo::Optimize_None;
    }
}

void GamePlayer::OnPlayerDir(MsgPlayerDir* pMsg)
{
    if ( pMsg->vPos.z > WORLD_HEIGHT || pMsg->vPos.z < -WORLD_HEIGHT )
    { pMsg->vPos.z = 0; }

    //����ڽ�ֹ�Ż��б��д������Ż�
    if (this->IDIsInFirstList(pMsg->header.stID))
    {
        pMsg->header.uMsgLevel = level_high;
        GetConnector()->SendMsg( pMsg/*, IMeConnector::ECT_Normal, theCfg.gEncryptMode */);
        return;
    }

    uint32 nPos = FindEmptyPos(pMsg->header.stID);
    if ( nPos == ErrorUnsignedLongID )
    { return; }
    
    m_CharPosInfoList[nPos].chDirX = pMsg->chDirX;
    m_CharPosInfoList[nPos].chDirY = pMsg->chDirY;
    m_CharPosInfoList[nPos].chDirZ = pMsg->chDirZ;
	//m_CharPosInfoList[nPos].vPos = pMsg->vPos;

	//����������Ѿ���δ��������Ϣ������ô��������������ݰ��������
	if( m_CharPosInfoList[nPos].nID == pMsg->header.stID )
	{
		if( m_CharPosInfoList[nPos].nType == CPosChangePackage::PACK_MSG_PLAYERPOS 
			|| m_CharPosInfoList[nPos].nType == CPosChangePackage::PACK_MSG_PLAYERPOSANDDIR
			|| m_CharPosInfoList[nPos].nType == CPosChangePackage::PACK_MSG_PLAYERMOVINGPOSANDDIR
			|| m_CharPosInfoList[nPos].nType == CPosChangePackage::PACK_MSG_PLAYERVERIFYPOS
			|| m_CharPosInfoList[nPos].nType == CPosChangePackage::PACK_MSG_PLAYERMOVINGPOS )
		{
			m_CharPosInfoList[nPos].nID        = pMsg->header.stID;
			m_CharPosInfoList[nPos].nType      = CPosChangePackage::PACK_MSG_PLAYERPOSANDDIR;
            m_CharPosInfoList[nPos].chOptimize = SPosChangeInfo::Optimize_PosAndDir;
		}
		else
		{
			m_CharPosInfoList[nPos].nID = pMsg->header.stID;
			m_CharPosInfoList[nPos].nType = CPosChangePackage::PACK_MSG_PLAYERDIR;
            m_CharPosInfoList[nPos].chOptimize = SPosChangeInfo::Optimize_Dir;
		}
	}
	else
	{
		m_CharPosInfoList[nPos].nID = pMsg->header.stID;
		m_CharPosInfoList[nPos].nType = CPosChangePackage::PACK_MSG_PLAYERDIR;
        m_CharPosInfoList[nPos].chOptimize = SPosChangeInfo::Optimize_None;
	}
}

void GamePlayer::OnPlayerPosAndDir(MsgPlayerPosAndDir* pMsg)
{
    if ( pMsg->vPos.z > WORLD_HEIGHT || pMsg->vPos.z < -WORLD_HEIGHT )
    { pMsg->vPos.z = 0; }

    uint32 nPos = FindEmptyPos(pMsg->header.stID);
    if (nPos == ErrorUnsignedLongID)
    { return; }

    m_CharPosInfoList[nPos].nType = CPosChangePackage::PACK_MSG_PLAYERPOSANDDIR;
    m_CharPosInfoList[nPos].chDirX = pMsg->chDirX;
    m_CharPosInfoList[nPos].chDirY = pMsg->chDirY;
    m_CharPosInfoList[nPos].chDirZ = pMsg->chDirZ;
    m_CharPosInfoList[nPos].vPos = pMsg->vPos;


    //����������Ѿ���δ��������Ϣ������ô��������������ݰ��������
    if( m_CharPosInfoList[nPos].nID == pMsg->header.stID )
    {
        m_CharPosInfoList[nPos].chOptimize = SPosChangeInfo::Optimize_PosAndDir;
    }
    else
    {
        m_CharPosInfoList[nPos].nID = pMsg->header.stID;
        m_CharPosInfoList[nPos].chOptimize = SPosChangeInfo::Optimize_None;
    }
}

void GamePlayer::OnPlayerVerifyPos(MsgPlayerVerifyPos* pMsg)
{
    if ( pMsg->vPos.z > WORLD_HEIGHT || pMsg->vPos.z < -WORLD_HEIGHT )
    { pMsg->vPos.z = 0; }

    uint32 nPos = FindEmptyPos(pMsg->header.stID);
    if ( nPos == ErrorUnsignedLongID )
    { return; }

    m_CharPosInfoList[nPos].vPos = pMsg->vPos;

	//����������Ѿ���δ��������Ϣ������ô��������������ݰ��������
	if( m_CharPosInfoList[nPos].nID == pMsg->header.stID )
	{
		if( m_CharPosInfoList[nPos].nType == CPosChangePackage::PACK_MSG_PLAYERDIR 
			|| m_CharPosInfoList[nPos].nType == CPosChangePackage::PACK_MSG_PLAYERPOSANDDIR )
		{
			m_CharPosInfoList[nPos].nID = pMsg->header.stID;
			m_CharPosInfoList[nPos].nType = CPosChangePackage::PACK_MSG_PLAYERPOSANDDIR;
            m_CharPosInfoList[nPos].chOptimize = SPosChangeInfo::Optimize_PosAndDir;
		}
		else if( m_CharPosInfoList[nPos].nType == CPosChangePackage::PACK_MSG_PLAYERMOVINGPOS )
		{
			m_CharPosInfoList[nPos].nID = pMsg->header.stID;
			m_CharPosInfoList[nPos].nType = CPosChangePackage::PACK_MSG_PLAYERMOVINGPOS;
            m_CharPosInfoList[nPos].chOptimize = SPosChangeInfo::Optimize_MovingPos;
		}
		else if( m_CharPosInfoList[nPos].nType == CPosChangePackage::PACK_MSG_PLAYERMOVINGPOSANDDIR )
		{
			m_CharPosInfoList[nPos].nID = pMsg->header.stID;
			m_CharPosInfoList[nPos].nType = CPosChangePackage::PACK_MSG_PLAYERMOVINGPOSANDDIR;
            m_CharPosInfoList[nPos].chOptimize = SPosChangeInfo::Optimize_MovingPosAndDir;
		}
		else if( m_CharPosInfoList[nPos].nType == CPosChangePackage::PACK_MSG_PLAYERPOS )
		{
			m_CharPosInfoList[nPos].nID = pMsg->header.stID;
			m_CharPosInfoList[nPos].nType = CPosChangePackage::PACK_MSG_PLAYERPOS;
            m_CharPosInfoList[nPos].chOptimize = SPosChangeInfo::Optimize_Pos;
		}
		else
		{
			m_CharPosInfoList[nPos].nID = pMsg->header.stID;
			m_CharPosInfoList[nPos].nType = CPosChangePackage::PACK_MSG_PLAYERVERIFYPOS;
            m_CharPosInfoList[nPos].chOptimize = SPosChangeInfo::Optimize_Pos;
		}
	}
	else
	{
		m_CharPosInfoList[nPos].nID = pMsg->header.stID;
		m_CharPosInfoList[nPos].nType = CPosChangePackage::PACK_MSG_PLAYERVERIFYPOS;
        m_CharPosInfoList[nPos].chOptimize = SPosChangeInfo::Optimize_None;
	}
}

void GamePlayer::OnUnPlayerMovingToPos(MsgUnPlayerMovingToPos* pMsg)
{
    uint32 nPos = FindEmptyPos(pMsg->header.stID);

    if ( nPos == ErrorUnsignedLongID)
    { return; }

	m_CharPosInfoList[nPos].nID        = pMsg->header.stID;
    m_CharPosInfoList[nPos].vPos       = pMsg->vStartPos;
    m_CharPosInfoList[nPos].vEndPos    = pMsg->vEndPos;
	m_CharPosInfoList[nPos].nType      = CPosChangePackage::PACK_MSG_UNPLAYERMOVINGTOPOS;
    m_CharPosInfoList[nPos].chOptimize = SPosChangeInfo::Optimize_None;
}

void GamePlayer::OnUnPlayerVerifyPos(MsgUnPlayerVerifyPos* pMsg)
{
    if ( pMsg->vPos.z > WORLD_HEIGHT || pMsg->vPos.z < -WORLD_HEIGHT )
    { pMsg->vPos.z = 0; }

    uint32 nPos = FindEmptyPos(pMsg->header.stID);
    if (nPos == ErrorUnsignedLongID)
    { return; }

    //m_CharPosInfoList[nPos].nID = pMsg->header.stID;
    m_CharPosInfoList[nPos].chDirX = pMsg->chDirX;
    m_CharPosInfoList[nPos].chDirY = pMsg->chDirY;
    m_CharPosInfoList[nPos].chDirZ = pMsg->chDirZ;
    m_CharPosInfoList[nPos].vPos = pMsg->vPos;

    // ���λ��û�� 0.01����ı仯����ʾ����û�ж�
    /*if ( abs(m_CharPosInfoList[nPos].vPos.x - pMsg->vPos.x)< POSITION_FLOAT_DIFFERENCE && 
         abs(m_CharPosInfoList[nPos].vPos.y - pMsg->vPos.y)< POSITION_FLOAT_DIFFERENCE &&
         abs(m_CharPosInfoList[nPos].chDirX - pMsg->chDirX) == 0 &&
         abs(m_CharPosInfoList[nPos].chDirY - pMsg->chDirY) == 0)
    {
        return;
    }*/

	//����������Ѿ���δ��������Ϣ������ô��������������ݰ��������
	if( m_CharPosInfoList[nPos].nID == pMsg->header.stID )
	{
		if( m_CharPosInfoList[nPos].nType == CPosChangePackage::PACK_MSG_UNPLAYERCLOSINGTOLOCKTARGET ) 
		{
			m_CharPosInfoList[nPos].nID = pMsg->header.stID;
			m_CharPosInfoList[nPos].nType = CPosChangePackage::PACK_MSG_UNPLAYERCLOSINGTOLOCKTARGET;
            m_CharPosInfoList[nPos].chOptimize = SPosChangeInfo::Optimize_ClosingToLockTarget;
		}
		else
		{
			m_CharPosInfoList[nPos].nID = pMsg->header.stID;
			m_CharPosInfoList[nPos].nType = CPosChangePackage::PACK_MSG_UNPLAYERVERIFYPOS;
            m_CharPosInfoList[nPos].chOptimize = SPosChangeInfo::Optimize_Pos;
		}
	}
	else
	{
		m_CharPosInfoList[nPos].nID = pMsg->header.stID;
		m_CharPosInfoList[nPos].nType = CPosChangePackage::PACK_MSG_UNPLAYERVERIFYPOS;
        m_CharPosInfoList[nPos].chOptimize = SPosChangeInfo::Optimize_None;
	}
}

void GamePlayer::OnUnPlayerCloseingToLockTarget(MsgUnPlayerClosingToLockTarget* pMsg)
{
    uint32 nPos = FindEmptyPos(pMsg->header.stID);
    if (nPos == ErrorUnsignedLongID )
    { return; }

    m_CharPosInfoList[nPos].nID = pMsg->header.stID;
    m_CharPosInfoList[nPos].nTargetID = pMsg->LockTargetID;
    m_CharPosInfoList[nPos].vPos = pMsg->vPos;
    m_CharPosInfoList[nPos].nType = CPosChangePackage::PACK_MSG_UNPLAYERCLOSINGTOLOCKTARGET;
    m_CharPosInfoList[nPos].chOptimize = SPosChangeInfo::Optimize_None;
}

/************************************************************************/
/* @brief ������ҽ�����Ұ                                              */
/************************************************************************/
void GamePlayer::OnPlayerEnterMySight(MsgPlayerEnterMySight* pMsg)
{
    //�������ʧ�ܣ����ʾ�������������������з��ͣ��ٲ���
    if (!m_entermysightpack.PushEnterMySight(*pMsg))
    {
        static MsgEnterMySightPack pack;
        if (m_entermysightpack.MakePackMsg(pack))
        { SendMsg(&pack); }

        m_entermysightpack.Clear();
        m_entermysightpack.PushEnterMySight(*pMsg);
    }
}

void GamePlayer::OnAckEnterWorld( MsgAckEnterWorld* pMsg )
{
    // ���Ȼ�ȡ��������XYZ����
    SetFloatX( pMsg->charinfo.otherdataclient.pos.vPos.x );
    SetFloatY( pMsg->charinfo.otherdataclient.pos.vPos.y );
    // SetFloatZ( pMsg->charinfo.otherdataclient.pos.vPos.z );
    SetCountryId( pMsg->charinfo.baseinfo.aptotic.ucCountry );
    SetLevel( pMsg->charinfo.baseinfo.liveinfo.ustLevel );

    static CAckEnterWorldPackage packagemaker;
    MsgAckEnterWorldPack* pPackmsg = packagemaker.MakePackageMsg(*pMsg);
    packagemaker.UnPackageMsg(*pPackmsg);

    if (pPackmsg != NULL)
    { SendMsg(pPackmsg); }
    else
    { 
		SendMsg(pMsg); 
		TESTECHOSEND( GetAccountID(), MsgAckEnterWorld )
	}
}

void GamePlayer::OnTellCountryID( MsgCountryTellCountryID* pMsg )
{
    if ( pMsg->header.stID == GetGameServerPlayerId() )
    {
        SetCountryId( pMsg->uchCountry );
    }

    SendToClient( pMsg );
}

void GamePlayer::OnChangeLevel( MsgSeeCharacterLevelup* pMsg )
{
    if ( pMsg->header.stID == GetGameServerPlayerId() )
    {
        SetLevel( pMsg->nNewLevel );
    }

    SendToClient( pMsg );
}
