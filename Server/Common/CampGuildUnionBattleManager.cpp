#include "CampGuildUnionBattleManager.h"
#include "GlobalDBManager.h"
#include "Guild.h"
#include "GuildManager.h"
#include "GamePlayer.h"
#include "CampBattleMessage.h"
#include "CampGuildUnionBattleConfig.h"
#include "GameWorld.h"
#include "CampBattle.h"
#include "CampGuildUnionBattle.h"
CampGuildUnionBattleManager::CampGuildUnionBattleManager()
{
	SetBattleType( CampDefine::BattleTypeGuildUnion );//���ù���ս������
	m_BattleValue = GuildDefine::CampBattleGuildUnion;
	m_BattleValueIsOpen = theGameGuildManager.GetCampBattleConfig()->m_GuildUnionSetting.IsOpen;
}
bool CampGuildUnionBattleManager::SignUpCampBattle( GamePlayer* pPlayer )//����ָ����ұ���
{
	if(theGameGlobalDBManager.GetBattleSum() == 0)
	{
		GameGuild* pGuild = pPlayer->GetGuild();
		if ( pGuild == NULL || !pGuild->IsMaster( pPlayer->GetDBCharacterID() ) )
		{
			// �����Ĳ��ǰ���
			pPlayer->SendOperateAckToClient< MsgCampBattleSignUpAck >( CampDefine::SignUp_MustGuildMaster );
			return false;
		}
		if ( !CampBattleManager::SignUpCampBattle( pPlayer, pGuild->GetID()) )
		{ return false; }
		
		//�жϱ����Ƿ�����
		int MaxSum = 2<<theCampGuildUnionBattleConfig.GetBattleSum();
		if(m_vecSignUp.size() >= MaxSum)
		{
			pPlayer->SendOperateAckToClient< MsgCampBattleSignUpAck >( CampDefine::SignUp_GuildBattleFull );//�����Ѿ����˲������ٱ�����
			return false;
		}

		AddSignUpUnit( pGuild->GetID() );
		// �����ɹ�
		pPlayer->SendOperateAckToClient< MsgCampBattleSignUpAck >( CampDefine::SignUp_Success );
		return true;
	}
	else
	{	
		GameGuild * pGuild = theGameGuildManager.GetGuild(pPlayer->GetGuildID());
		if(pGuild && pGuild->GetBattleSum() == theGameGlobalDBManager.GetBattleSum())
			pPlayer->SendOperateAckToClient< MsgCampBattleSignUpAck >( CampDefine::SignUp_GuildUnionBattleNone );
		else
			pPlayer->SendOperateAckToClient< MsgCampBattleSignUpAck >( CampDefine::SignUp_GuildUnionBattleSumError );
        return false;
	}
}
void CampGuildUnionBattleManager::ProcessChangeToPrepareStatus()// ���Ѿ������Ĺ��������Դ���
{
	if(theGameGlobalDBManager.GetBattleSum() != 0)
	{
		//�Ѿ����Ժ��������
		//��ȡȫ���Ĺ��� ���ǿ�ʼ���� �жϹ���BattleSumΪ��ǰֵ�Ĺ����ȫ��ID ��Щ����ᱻ���Ĵ���
		map< unsigned int, GameGuild* >& pMap = theGameGuildManager.GetAllGuild();
		if(pMap.empty())
		{
			//����Ϊ�� 
			m_vecSignUp.clear();
			return;
		}
		map< unsigned int, GameGuild* >::iterator Iter = pMap.begin();
		for(;Iter != pMap.end();++Iter)
		{
			if(Iter->second->GetBattleSum() == theGameGlobalDBManager.GetBattleSum())
			{
				m_vecSignUp.push_back(Iter->second->GetID());//���뵽�����б�
			}
			else if(Iter->second->GetBattleSum() != 0)
			{
				Iter->second->SetBattleSum(0);

				CS2GSGuildBattleSum msg;
				msg.nGuildID = Iter->second->GetID();
				msg.battleSum = 0;
				GettheServer().SendMsgToCenterServer( &msg );
			}
		}
	}
	m_mapMatchUnit.clear();
	if ( m_vecSignUp.empty())
		return; 
		
	//�Լ��ϵĹ��������� �����ֱ�ӽ��� ���轱��
	if(m_vecSignUp.size()% 2 == 1)
	{
		//���ѡ��һ������ ����ֱ�ӽ���
		int RandSum = theRand.rand32() % m_vecSignUp.size();
		//����ָ������ֱ�ӽ���
		uint32 GuildID = m_vecSignUp[RandSum];
		m_vecSignUp[RandSum] = 0;//���ñ��Ϊ0
		GameGuild * pGameGuild = theGameGuildManager.GetGuild(GuildID);
		if(pGameGuild)
		{	
			//1.����ָ���Ľ��� ���ù��������
			uint32 Num = pGameGuild->GetBattleSum();
			uint32 Sum = theCampGuildUnionBattleConfig.GetBattleSum();
			++Num;
			if(Num>=Sum)
				Num = 0;
			pGameGuild->SetBattleSum(Num);

			CS2GSGuildBattleSum msg;
			msg.nGuildID = GuildID;
			msg.battleSum = Num;
			GettheServer().SendMsgToCenterServer( &msg );
		}
	}
	int Sum = m_vecSignUp.size() /2;
	for(int i =0;i<Sum;++i)
	{
		//������Դ���
		int RandOne=0;
		do
		{
			RandOne = theRand.rand32() % m_vecSignUp.size();
		}while(m_vecSignUp[RandOne] == 0);

		int RandTwo=0;
		do
		{
			RandTwo = theRand.rand32() % m_vecSignUp.size();
		}while(RandTwo == RandOne || m_vecSignUp[RandTwo] == 0);

		m_mapMatchUnit[ m_vecSignUp[RandOne] ] = m_vecSignUp[RandTwo];
		
		m_vecSignUp[RandOne]  = 0;
		m_vecSignUp[RandTwo]  = 0;
	}
	m_vecSignUp.clear();
}
void CampGuildUnionBattleManager::ProcessChangeToEnterStatus()
{
    // ������������, 
    for ( MatchUnitMapIter iter = m_mapMatchUnit.begin(); iter != m_mapMatchUnit.end(); ++iter )
    {
        // ��������
        unsigned int nBattleMapID = theGameWorld.GetEctypeMapID( GetMapID(), true );
        theGameWorld.MultiCreateStage( GetMapID(), nBattleMapID );

        // ����ս��
        CampBattle* pCampBattle = CampBattle::CreateBattle< CampGuildUnionBattle >();
        pCampBattle->SetBattleManager( this );
        pCampBattle->SetBattleMapID( nBattleMapID );
        pCampBattle->SetRedID( iter->first );
        pCampBattle->SetBlueID( iter->second );
        pCampBattle->SetWinResource( m_pBattleConfig->GetResourceSetting().GetMaxResource() );
       
        // �����Ƿ����ս����Ϣ
        pCampBattle->SendEnterCampBattleMessage();

        // ��ӵ�ս���б���
        AddCampBattle( pCampBattle );
    }
    m_mapMatchUnit.clear();
}
void CampGuildUnionBattleManager::ProcessChangeToSignUpStatus()
{
	//��ս����������״̬��Initת��������״̬��ʱ�� ������Ҫ����һ��ս���Ļ�������
	//1.���ݵ�ǰ���е����� ���ú������ļ�����
	SetBattleConfig(&theCampGuildUnionBattleConfig.GetGuildBattleSumConfig(theGameGlobalDBManager.GetBattleSum()));
	m_vecSignUp.clear();
    // ����ս������, ��ս��MapConfig ID
    for ( int i = 0; i < m_pBattleConfig->GetMapSettingCount(); ++i )
    {
        const CampBattleConfig::MapSetting* pSetting = m_pBattleConfig->GetMapSetting( i );
        if ( pSetting == NULL )
        { continue; }

        if ( !g_Cfg.IsMapRun( pSetting->GetMapID() ) )
        { continue; }       // û�п���ͼ

        SetMapID( pSetting->GetMapID() );
        SetCountryID( pSetting->GetCountryID() );

		const CampBattleConfig::CKingdomMap &xKingdomMap = m_pBattleConfig->GetKingdomMap();

		SetkingdomMapInfo(xKingdomMap.GetMapID(),
						  xKingdomMap.GetMapX(),
						  xKingdomMap.GetMapY());
    }
}
void CampGuildUnionBattleManager::ProcessChangeToEndStatus()
{
	//��ս�����ý�����ʱ�� ������Ҫ����һ�¹�������״̬
	uint32 Num = theGameGlobalDBManager.GetBattleSum();
	uint32 Sum = theCampGuildUnionBattleConfig.GetBattleSum();
	++Num;
	if(Num>=Sum)
		Num = 0;
	theGameGlobalDBManager.SetBattleSum(Num);//��¼�´�ս�������� ���ұ��浽���ݿ�ȥ
}
bool CampGuildUnionBattleManager::ShowCampBattleEnter( GamePlayer* pPlayer )
{
    GameGuild* pGuild = pPlayer->GetGuild();
	if ( pGuild == NULL || pGuild->GetBattleSum() != theGameGlobalDBManager.GetBattleSum())
    { return false; }

    return CampBattleManager::ShowCampBattleEnter( pPlayer, pGuild->GetID() );
}

bool CampGuildUnionBattleManager::EnterCampBattle( GamePlayer* pPlayer )
{
    GameGuild* pGuild = pPlayer->GetGuild();
    if ( pGuild == NULL )
    { 
        pPlayer->SendOperateAckToClient< MsgEnterCampBattleAck >( CampDefine::Enter_MustSignUpGuild );
        return false;
    }
	else if(pGuild->GetBattleSum() != theGameGlobalDBManager.GetBattleSum())
	{
		pPlayer->SendOperateAckToClient< MsgEnterCampBattleAck >( CampDefine::Enter_BattleSumError );
        return false;
	}

    return CampBattleManager::EnterCampBattle( pPlayer, pGuild->GetID() );   
}
void CampGuildUnionBattleManager::ProcessBattleInitStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute )
{
	if(!m_pBattleConfig)//��Ϊcenter��ȫ�����ݻ�û���� ������ʱ�ȱ��ж� �ȴ����ݴ���
		return;
	// �ж��Ƿ���ս��׼��ʱ��
    if ( !CheckBattleSignUpTime( nCurrentTime, nDayOfWeek, nHour, nMinute ) )
    { return; }

    // ����ս���ı䵽׼��״̬
    ProcessChangeStatus( CampDefine::StatusSignUp );
}