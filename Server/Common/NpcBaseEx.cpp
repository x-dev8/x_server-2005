#include "NpcBaseEx.h"
#include "ScriptMgr.h"
#include "GamePlayer.h"
#include "GameStage.h"

NpcBaseEx::NpcBaseEx()
{
    m_pNpcInfo   = NULL;
    m_bNewConfig = false;
    m_bShow = true;
	nInitVMId = -1;
    m_vecQuestScript.clear();
    m_strLastAnimName.clear();

    SetObjType( Object_Npc );
    SetStatus( CS_IDLE );

    SetForce( ForceDefine::NormalNpcForce );
}

NpcBaseEx::~NpcBaseEx()
{
    GetScriptMgr()->ReleaseVMByDstId( ST_NPC, GetID() );

    if ( m_bNewConfig )
    { 
        delete m_pNpcInfo;
        m_pNpcInfo = NULL;
    }
}

void NpcBaseEx::Initialize( NpcInfo::Npc* pConfig, GameStage* pStage, bool bAsyn )
{
    m_pNpcInfo = pConfig;

    SetCharName( m_pNpcInfo->name.c_str() );
    SetLevel( m_pNpcInfo->level );
    SetModelId( m_pNpcInfo->modelId );
    SetMapID( pStage->GetStageID() );
    
    SetFloatXF( m_pNpcInfo->x );
    SetFloatYF( m_pNpcInfo->y );
    SetFloatZ( m_pNpcInfo->z );
    SetMask( m_pNpcInfo->isCollision  );
    SetShow( m_pNpcInfo->isWorldShow , bAsyn ); // 设置是否隐身状态
    SetCountry( m_pNpcInfo->uchCountryID );

    SetDirectiron( m_pNpcInfo->direction );
    
    GetCharFightAttr()->moveSpeed.base = 1.65f;
    GetCharFightAttr()->moveSpeed.UpdateFinal();
    GetCharFightAttr()->hpMax.base = 10000;
    GetCharFightAttr()->hpMax.UpdateFinal();
    SetHP( GetCharFightAttr()->hpMax.final );
    SetLastMovingSpeed( GetMoveSpeed() );

    if( !m_pNpcInfo->canChangeDirection )
    { AddShowFlag( eNotChangeDir ); }

    if( false )
    { AddShowFlag( eNotShadow ); }

    // 判断是否有路点
    InitRoute( GetMapID(), m_pNpcInfo->movePath );

    if ( !m_pNpcInfo->triggerScript.empty() )
    {
        std::string strScriptPath = "";
        strScriptPath = SCRIPT_ROOTDIRECTORY;
        strScriptPath += m_pNpcInfo->triggerScript;

        nInitVMId = GetScriptMgr()->CreateVM( ST_NPC, strScriptPath.c_str(), GetID() );
		if (!bAsyn)
		{
			CScriptVMThread thread;
			CScriptVM* pVM = GetScriptMgr()->GetScriptControl()->GetVM( nInitVMId );
			thread.SetVM( pVM );
			if( thread.SetEntrance( 0 ) )
			{
				thread.SetCharId( GetID() );
				if ( !thread.Restore() )
				{
					LogMessage::LogSystemError( "CScriptMgr::InitScripts() thread.Restore() error" );
				}
			}
		}
    }
}

void NpcBaseEx::Run( uint32 dwCostTime )
{
#ifdef _DEBUG
    static int id = 0;
    if ( GetID() == id )
    { int i = 0; }
#endif

    // 处理显示和隐藏
    ProcessShowAndHide();

    AiCharacter::Run( dwCostTime );
}

void NpcBaseEx::SetDisappear( uint32 nTime )
{
    if ( m_pNpcInfo->type != eNT_ScriptNpc || nTime == 0 )
    { return; }

    m_xTimer[ AiDefine::AiTimer_Disappear ].StartTimer( HQ_TimeGetTime(), nTime );
}

// 设置NPC状态
void NpcBaseEx::SetShow( bool bValue ,bool bInit)
{
    if ( m_bShow == bValue )
    { return; }

    m_bShow = bValue;

	// 防止多线程发消息
	if (!bInit)
	{
		MsgTellHideStatus xTell;
		xTell.header.stID = GetID();
		xTell.stID        = GetID();
		xTell.bShow       = m_bShow;
		GettheServer().SendMsgToView( &xTell, GetID(), true );
	}

}

void NpcBaseEx::StartHideTimer( unsigned int nStartTime, unsigned int nSpaceTime )
{
    m_xHideTimer.StartTimer( nStartTime, nSpaceTime );
}

void NpcBaseEx::StartShowTimer( unsigned int nStartTime, unsigned int nSpaceTime )
{
    m_xShowTimer.StartTimer( nStartTime, nSpaceTime );
}

void NpcBaseEx::ProcessShowAndHide()
{
    // 判断时间 如果要隐身, 就通知客户端隐身
    if ( m_xHideTimer.DoneTimer() )
    { SetShow( false ); }

    if ( m_xShowTimer.DoneTimer() )
    { SetShow( true ); }
}

Msg* NpcBaseEx::FirstSightOnMe( char* szMsgBuffer, unsigned int nBuffSize )
{
    BaseCharacter::FirstSightOnMe( szMsgBuffer, nBuffSize );

    MsgNPCEnterMySight* pMsg = (MsgNPCEnterMySight*)szMsgBuffer;
    strncpy_s( pMsg->szDisplayName, GetCharName(), sizeof( pMsg->szDisplayName ) - 1);
    pMsg->stId       = GetModelId();
    pMsg->bShow      = GetShow();
    pMsg->stCharType = Object_Npc;
    pMsg->fMoveStep  = GetMoveStep();
    pMsg->npcId      = GetNpcID();
	pMsg->BelongID			= GetKiller()?GetKiller()->GetID():0;
    return pMsg;
}

QuestScript* NpcBaseEx::GetQuestScriptByIndex( unsigned int nIndex )
{
    if ( nIndex >= GetQuestScriptCount() )
    { return NULL; }

    return &( m_vecQuestScript.at( nIndex ) );
}

QuestScript* NpcBaseEx::GetQuestScriptByQuestID( int nQuestID )
{
    for ( QuestScriptVectorIter iter = m_vecQuestScript.begin(); iter != m_vecQuestScript.end(); ++iter )
    {
        if ( iter->stQuestId == nQuestID )
        {
            return &( *iter );
        }
    }

    return NULL;
}

void NpcBaseEx::ProcessDeathExitWorld()
{
    // 改变AI状态
    SetAiStatus( AiDefine::ThinkingWaitRelive );

    // 开启死亡定时器
    m_xTimer[ AiDefine::AiTimer_Relive ].StartTimer( HQ_TimeGetTime(), m_pNpcInfo->fightData[0].reliveTime );

	//AiCharacter::ProcessDeathExitWorld();
	/*MsgExit xMsg;
	xMsg.header.stID = GetID();
	GettheServer().SendMsgToView( &xMsg, GetID(), false ); */
}

void NpcBaseEx::ProcessDeathCallScript()
{
    if ( !CheckDeathCallScript() )
    { return; }

    GamePlayer* pKillerPlayer = static_cast< GamePlayer* >( m_pBelongKiller );
    GetScriptMgr()->StartupVM( ST_NPC_DEAD, GetNpcID(), pKillerPlayer );
}

void NpcBaseEx::UpdateMoveRouteToPlayer( GamePlayer* pPlayer )
{
    if ( GetAiStatus() != AiDefine::ThinkingMoveToRoute )
    { return; }

    if ( !NeedMoveToNextRoute() )
    { return; }

    SendMoveToTargetPointMessage( pPlayer );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8 NpcBaseEx::GetShopItemCostType( ItemDefine::SItemCommon* pItem, SShopItem* pShopItem )
{
    uint8 nCostType  = pItem->costType;

    if (nCostType == ItemDefine::CT_Money || nCostType == ItemDefine::CT_JiaoZi)
    {
        if (pShopItem->bIsBound)
        { nCostType = ItemDefine::CT_JiaoZi; }
        else
        { nCostType = ItemDefine::CT_Money;  }
    }

    return nCostType;
}

int32 NpcBaseEx::GetPlayerSellNpcItemCost( uint16 itemId, uint16 count )
{
    ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID( itemId );
    if( pItem == NULL )
    { return -1; }

    if ( count == 0 )
    { return -1; }

    int nCost = 0;
    switch( pItem->ucItemType )
    {
    case ItemDefine::ITEMTYPE_WEAPON:
    case ItemDefine::ITEMTYPE_ARMOUR:
    case ItemDefine::ITEMTYPE_OTHER:
        { nCost = pItem->dwCost * fSellDiscountRate * count + 1; }
        break;
    case ItemDefine::ITEMTYPE_RESTORE:
    case ItemDefine::ITEMTYPE_MATERIAL:
    case ItemDefine::ITEMTYPE_REEL:
    case ItemDefine::ITEMTYPE_TREASUREBOX:
    case ItemDefine::ITEMTYPE_CHECKUP:
    case ItemDefine::ITEMTYPE_REALAWARD:
    case ItemDefine::ITEMTYPE_GEM:
        { nCost = 1 * count ; }
        break;
    default:
        { return -1; }
		break;
    }

    return nCost;
}

int32 NpcBaseEx::GetPlayerItemReclaimCost( SCharItem* pCharItem, uint16 count )
{
    if (pCharItem == NULL || count == 0)
    { return -1; }

    ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
    if( pItem == NULL )
    { return -1; }

    if (pItem->ucItemType != ItemDefine::ITEMTYPE_WEAPON && pItem->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
    { return -1; }

    int nCostReturn = 0;
    switch ( pItem->costType )
    {
    case ItemDefine::CT_Reputation:
    case ItemDefine::CT_Exploit:
    case ItemDefine::CT_Honour:
    case ItemDefine::CT_GuildOffer:
        {
            if (pCharItem->equipdata.quality == ItemDefine::EQL_Purple)
            { nCostReturn = pItem->dwCost * count ; }
            else
            { nCostReturn = pItem->dwCost * count * fReclaimDiscountRate + 1; }

        }
        break;
    case ItemDefine::CT_Item:
        {
            ItemDefine::SItemCommon* pBuyItem = GettheItemDetail().GetItemByID( pItem->costItemID );
            if( pBuyItem == NULL )
            { return -1; }

            if (pCharItem->equipdata.quality == ItemDefine::EQL_Purple)
            { nCostReturn = pBuyItem->dwCost * pItem->dwCost * count; }
            else
            { nCostReturn = pBuyItem->dwCost * pItem->dwCost * count  * fReclaimDiscountRate + 1; }
        }
        break;
    default:
        { return -1; }
        break;
    }

    return nCostReturn;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////