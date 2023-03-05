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

// 处理转换到准备状态逻辑
void CampGuildBattleManager::ProcessChangeToPrepareStatus()
{
    // 报名结束, 分配对阵表, 
    // 判断奇偶之后，按照帮会等级从高往低配对，配对方式为：第一对第二，第三对第四，依次类推

	//m_vecSignUp.clear();

	//if(m_vecSignUp.size() == 1)
	//{
	//	//在报名结束后 还有一个公会没有配对 提示公会 配对失败
	//	GameGuild* pGuild = theGameGuildManager.GetGuild(m_vecSignUp[0] );
	//	if(pGuild != NULL)
	//	{
	//		MsgTellCampGuildBattleUnMatch xTell;
	//		pGuild->SendMessageToGuild( &xTell );
	//	}
	//}		
	//m_vecSignUp.clear();
    m_mapMatchUnit.clear();

    // 获得所有报名的帮派信息
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

    // 奇数, 删除最后报名的那一个
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

    // 没有报名帮派
    if ( vecSignUpGuild.empty() )
    { return; }

    // 按照帮派等级等级进行排序
    std::sort( vecSignUpGuild.begin(), vecSignUpGuild.end(), SortByGreaterGuildLevel() );

    // 相邻两个帮派配对
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

// 处理转换到进入状态逻辑
void CampGuildBattleManager::ProcessChangeToEnterStatus()
{
    // 创建副本场景, 
    for ( MatchUnitMapIter iter = m_mapMatchUnit.begin(); iter != m_mapMatchUnit.end(); ++iter )
    {
		GameGuild * pRedGuild = theGameGuildManager.GetGuild(iter->first);
		GameGuild * pBlueGuild = theGameGuildManager.GetGuild(iter->second);
		if(!pRedGuild || !pBlueGuild)
			continue;
		int RedSum = pRedGuild->GetSumByCampBattleValue(GuildDefine::CampBattleGuild);
		int BlueSum = pBlueGuild->GetSumByCampBattleValue(GuildDefine::CampBattleGuild);
		//当双方人数过少的时候 我们不开启战场 加配置文件
		const CampGuildBattleConfig* pBattleConfig = static_cast< const CampGuildBattleConfig* >( m_pBattleConfig );
		const CampGuildBattleConfig::SignUpSetting& xSetting = pBattleConfig->GetSignUpSetting();
		if(RedSum < xSetting.GetMinMemberCount() && BlueSum < xSetting.GetMinMemberCount())
		{
			//提示公会 可以参战成员不足 无法开启战场
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
        // 创建副本
        unsigned int nBattleMapID = theGameWorld.GetEctypeMapID( GetMapID(), true );
        theGameWorld.MultiCreateStage( GetMapID(), nBattleMapID );

        // 创建战场
        CampBattle* pCampBattle = CampBattle::CreateBattle< CampGuildBattle >();
        pCampBattle->SetBattleManager( this );
        pCampBattle->SetBattleMapID( nBattleMapID );
        pCampBattle->SetRedID( iter->first );
        pCampBattle->SetBlueID( iter->second );
        pCampBattle->SetWinResource( m_pBattleConfig->GetResourceSetting().GetMaxResource() );
       
        // 发送是否进入战场消息
        pCampBattle->SendEnterCampBattleMessage();

        // 添加到战场列表中
        AddCampBattle( pCampBattle );
	    CampGuildBattle* pCampGuildBattle = static_cast<CampGuildBattle*>(pCampBattle);
		pCampGuildBattle->SetGuildCampBattleTimeMap();
    }

    m_mapMatchUnit.clear();
}

// 处理战场报名
bool CampGuildBattleManager::SignUpCampBattle( GamePlayer* pPlayer )
{
    GameGuild* pGuild = pPlayer->GetGuild();
    if ( pGuild == NULL || !pGuild->IsMaster( pPlayer->GetDBCharacterID() ) )
    {// 报名的不是帮主
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

	// 帮派成员限制
    const CampGuildBattleConfig* pBattleConfig = static_cast< const CampGuildBattleConfig* >( m_pBattleConfig );
    const CampGuildBattleConfig::SignUpSetting& xSetting = pBattleConfig->GetSignUpSetting();
    if ( pGuild->MemberCount() < xSetting.GetMinMemberCount() )
    {
        pPlayer->SendOperateAckToClient< MsgCampBattleSignUpAck >( CampDefine::SignUp_GuildMemberLess );
        return false;
    }

    AddSignUpUnit( pGuild->GetID() );

    // 报名成功
    pPlayer->SendOperateAckToClient< MsgCampBattleSignUpAck >( CampDefine::SignUp_Success );

	//if(m_vecSignUp.size() == 2)
	//{
	//	//有2个公会的时候 我们设置2个公会已经配对成功
	//	m_mapMatchUnit[ m_vecSignUp[0] ] = m_vecSignUp[1];
	//	//发送命令道客户端 告诉2个公会的成员 配对成功 并且显示配对的结果
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