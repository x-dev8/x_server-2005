#include "CampGuildBattleManager.h"
#include "CampGuildBattleConfig.h"
#include "GuildManager.h"
#include "CampGuildBattle.h"
#include <algorithm>
#include <functional>
#include "GameWorld.h"
#include "GamePlayer.h"
#include "CampBattleMessage.h"
CampGuildBattleManager::CampGuildBattleManager()
{
    SetBattleType( CampDefine::BattleTypeGuild );
	m_BattleValue = GuildDefine::CampBattleGuild;
	m_BattleValueIsOpen = theGameGuildManager.GetCampBattleConfig()->m_GuildSetting.IsOpen;
}

class SignUpGuild
{
public:
    unsigned int GetID() const{ return nID; }
    unsigned char GetLevel() const { return uchLevel; }

    void SetID( unsigned int nValue ) { nID = nValue; }
    void SetLevel( unsigned char uchValue ) { uchLevel = uchValue; }

private:
    unsigned int nID;
    unsigned char uchLevel;
};

struct SortByGreaterGuildLevel : public std::unary_function< SignUpGuild, bool >
{
    bool operator() ( const SignUpGuild& xLeft, const SignUpGuild& xRight )
    {
        return xLeft.GetLevel() > xRight.GetLevel();
    }
};

// ����ת����׼��״̬�߼�
void CampGuildBattleManager::ProcessChangeToPrepareStatus()
{
    // ��������, ��������, 
    // �ж���ż֮�󣬰��հ��ȼ��Ӹ�������ԣ���Է�ʽΪ����һ�Եڶ��������Ե��ģ���������

	//m_vecSignUp.clear();

	//if(m_vecSignUp.size() == 1)
	//{
	//	//�ڱ��������� ����һ������û����� ��ʾ���� ���ʧ��
	//	GameGuild* pGuild = theGameGuildManager.GetGuild(m_vecSignUp[0] );
	//	if(pGuild != NULL)
	//	{
	//		MsgTellCampGuildBattleUnMatch xTell;
	//		pGuild->SendMessageToGuild( &xTell );
	//	}
	//}		
	//m_vecSignUp.clear();
    m_mapMatchUnit.clear();

    // ������б����İ�����Ϣ
    std::vector< SignUpGuild > vecSignUpGuild( 0 );
    for ( SignUpVectorIter iter = m_vecSignUp.begin(); iter != m_vecSignUp.end(); ++iter )
    {
        GameGuild* pGuild = theGameGuildManager.GetGuild( *iter );
        if ( pGuild == NULL )
        { continue; }

        SignUpGuild xSignUpGuild;
        xSignUpGuild.SetID( pGuild->GetID() );
        xSignUpGuild.SetLevel( pGuild->GetLevel() );
        vecSignUpGuild.push_back( xSignUpGuild );
    }

    m_vecSignUp.clear();

    // ����, ɾ�����������һ��
    if ( vecSignUpGuild.size() % 2 == 1 )
    { 
        const SignUpGuild& xGuild = vecSignUpGuild.back();
        GameGuild* pGuild = theGameGuildManager.GetGuild( xGuild.GetID() );
        if ( pGuild != NULL )
        {
            MsgTellCampGuildBattleUnMatch xTell;
            pGuild->SendMessageToGuild( &xTell );
        }

        vecSignUpGuild.pop_back();
    }

    // û�б�������
    if ( vecSignUpGuild.empty() )
    { return; }

    // ���հ��ɵȼ��ȼ���������
    std::sort( vecSignUpGuild.begin(), vecSignUpGuild.end(), SortByGreaterGuildLevel() );

    // ���������������
    std::vector< SignUpGuild >::iterator iter = vecSignUpGuild.begin();
    std::vector< SignUpGuild >::iterator end  = vecSignUpGuild.end();
    while( iter != vecSignUpGuild.end() )
    {
        unsigned int nRedGuildID = iter->GetID();
        ++iter;

        if ( iter == end )
        { break; }

        unsigned int nBlueGuildID = iter->GetID();
        m_mapMatchUnit[ nRedGuildID ] = nBlueGuildID;

        ++iter;
    }
}

// ����ת��������״̬�߼�
void CampGuildBattleManager::ProcessChangeToEnterStatus()
{
    // ������������, 
    for ( MatchUnitMapIter iter = m_mapMatchUnit.begin(); iter != m_mapMatchUnit.end(); ++iter )
    {
		GameGuild * pRedGuild = theGameGuildManager.GetGuild(iter->first);
		GameGuild * pBlueGuild = theGameGuildManager.GetGuild(iter->second);
		if(!pRedGuild || !pBlueGuild)
			continue;
		int RedSum = pRedGuild->GetSumByCampBattleValue(GuildDefine::CampBattleGuild);
		int BlueSum = pBlueGuild->GetSumByCampBattleValue(GuildDefine::CampBattleGuild);
		//��˫���������ٵ�ʱ�� ���ǲ�����ս�� �������ļ�
		const CampGuildBattleConfig* pBattleConfig = static_cast< const CampGuildBattleConfig* >( m_pBattleConfig );
		const CampGuildBattleConfig::SignUpSetting& xSetting = pBattleConfig->GetSignUpSetting();
		if(RedSum < xSetting.GetMinMemberCount() && BlueSum < xSetting.GetMinMemberCount())
		{
			//��ʾ���� ���Բ�ս��Ա���� �޷�����ս��
			MsgCampBattleCheckCampBattleValueSum msg;
			msg.redlose = false;
			msg.bulelose = false;
			msg.redguildid = iter->first;
			msg.blueguildid = iter->second;
			pRedGuild->SendMessageToGuild(&msg);
			pBlueGuild->SendMessageToGuild(&msg);
			continue;
		}
		else if(RedSum >= xSetting.GetMinMemberCount() && BlueSum < xSetting.GetMinMemberCount())
		{
			MsgCampBattleCheckCampBattleValueSum msg;
			msg.redlose = true;
			msg.bulelose = false;
			msg.redguildid = iter->first;
			msg.blueguildid = iter->second;
			pRedGuild->SendMessageToGuild(&msg);
			pBlueGuild->SendMessageToGuild(&msg);
			continue;
		}
		else if(RedSum < xSetting.GetMinMemberCount() && BlueSum >= xSetting.GetMinMemberCount())
		{
			MsgCampBattleCheckCampBattleValueSum msg;
			msg.redlose = false;
			msg.bulelose = true;
			msg.redguildid = iter->first;
			msg.blueguildid = iter->second;
			pRedGuild->SendMessageToGuild(&msg);
			pBlueGuild->SendMessageToGuild(&msg);
			continue;
		}
        // ��������
        unsigned int nBattleMapID = theGameWorld.GetEctypeMapID( GetMapID(), true );
        theGameWorld.MultiCreateStage( GetMapID(), nBattleMapID );

        // ����ս��
        CampBattle* pCampBattle = CampBattle::CreateBattle< CampGuildBattle >();
        pCampBattle->SetBattleManager( this );
        pCampBattle->SetBattleMapID( nBattleMapID );
        pCampBattle->SetRedID( iter->first );
        pCampBattle->SetBlueID( iter->second );
        pCampBattle->SetWinResource( m_pBattleConfig->GetResourceSetting().GetMaxResource() );
       
        // �����Ƿ����ս����Ϣ
        pCampBattle->SendEnterCampBattleMessage();

        // ��ӵ�ս���б���
        AddCampBattle( pCampBattle );
	    CampGuildBattle* pCampGuildBattle = static_cast<CampGuildBattle*>(pCampBattle);
		pCampGuildBattle->SetGuildCampBattleTimeMap();
    }

    m_mapMatchUnit.clear();
}

// ����ս������
bool CampGuildBattleManager::SignUpCampBattle( GamePlayer* pPlayer )
{
    GameGuild* pGuild = pPlayer->GetGuild();
    if ( pGuild == NULL || !pGuild->IsMaster( pPlayer->GetDBCharacterID() ) )
    {// �����Ĳ��ǰ���
        pPlayer->SendOperateAckToClient< MsgCampBattleSignUpAck >( CampDefine::SignUp_MustGuildMaster );
        return false;
    }

	if(!m_mapMatchUnit.empty())
	{
		MatchUnitMapIter Iter = m_mapMatchUnit.begin();
		for(;Iter != m_mapMatchUnit.end(); ++Iter)
		{
			if(pGuild->GetID() == Iter->first || pGuild->GetID() == Iter->second)
			{
				pPlayer->SendOperateAckToClient< MsgCampBattleSignUpAck >( CampDefine::SignUp_AlreadySignUp );
				return false;
			}
		}
	}
  
	if ( !CampBattleManager::SignUpCampBattle( pPlayer, pGuild->GetID()) )
    { return false; }

	// ���ɳ�Ա����
    const CampGuildBattleConfig* pBattleConfig = static_cast< const CampGuildBattleConfig* >( m_pBattleConfig );
    const CampGuildBattleConfig::SignUpSetting& xSetting = pBattleConfig->GetSignUpSetting();
    if ( pGuild->MemberCount() < xSetting.GetMinMemberCount() )
    {
        pPlayer->SendOperateAckToClient< MsgCampBattleSignUpAck >( CampDefine::SignUp_GuildMemberLess );
        return false;
    }

    AddSignUpUnit( pGuild->GetID() );

    // �����ɹ�
    pPlayer->SendOperateAckToClient< MsgCampBattleSignUpAck >( CampDefine::SignUp_Success );

	//if(m_vecSignUp.size() == 2)
	//{
	//	//��2�������ʱ�� ��������2�������Ѿ���Գɹ�
	//	m_mapMatchUnit[ m_vecSignUp[0] ] = m_vecSignUp[1];
	//	//����������ͻ��� ����2������ĳ�Ա ��Գɹ� ������ʾ��ԵĽ��
	//	MsgCampBattleSignUpSecc msg;
	//	msg.RedGuildID = m_vecSignUp[0];
	//	msg.BlueGuildID = m_vecSignUp[1];
	//	pGuild->SendMessageToGuild(&msg);
	//	GameGuild* pGuildRed = theGameGuildManager.GetGuild(m_vecSignUp[0]);
	//	if(pGuildRed)
	//		pGuildRed->SendMessageToGuild(&msg);
	//	m_vecSignUp.clear();
	//}
    return true;
}

bool CampGuildBattleManager::ShowCampBattleEnter( GamePlayer* pPlayer )
{
    GameGuild* pGuild = pPlayer->GetGuild();
    if ( pGuild == NULL )
    { return false; }

    return CampBattleManager::ShowCampBattleEnter( pPlayer, pGuild->GetID() );
}

bool CampGuildBattleManager::EnterCampBattle( GamePlayer* pPlayer )
{
    GameGuild* pGuild = pPlayer->GetGuild();
    if ( pGuild == NULL )
    { 
        pPlayer->SendOperateAckToClient< MsgEnterCampBattleAck >( CampDefine::Enter_MustSignUpGuild );
        return false;
    }

    return CampBattleManager::EnterCampBattle( pPlayer, pGuild->GetID() );   
}