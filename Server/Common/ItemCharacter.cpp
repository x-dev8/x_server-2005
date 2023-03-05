#define STRICT

#include "ItemCharacter.h"
#include "ShareData.h"
#include "GameWorld.h"
#include "GameTime.h"
#include "DropQuestItem.h"
#include "FuncPerformanceLog.h"
#include "DropItemManager.h"
#include "TeamManager.h"
#include "GamePlayer.h"

#define ITEM_DEFINE_LIFE_TIEM	(2*60000)
#define ITEM_PROTECT_TIEM		(1*60000)

//Luo 仅仅 用于 m_iMasterGroupID != -1 && m_iMasterGroupID != -1 时的情况
#define ITEM_PEOPLE_OF_TEAM		(40*1000)	//队伍分配时 前40归属于队伍中的某个人 40秒以后归属为这个队伍
ItemCharacter::ItemCharacter()
{
    m_dwDeathTime = ITEM_DEFINE_LIFE_TIEM;  //道具的生存时间
    //
    m_dwDropBeginTime = HQ_TimeGetTime();
    //
    m_borndelay.stBornDelay = 0;
    //
    m_iMasterGroupID = -1;
    m_iMasterNpcID = -1;
    //判断该道具是否已经被，拿起来了
    m_BePickFlag = false;
    m_bTaskItem = false;

    TimePeopleOfTeam = 0;
    HoldGroupId = -1;

    m_bAdscription_teamHeader = false;

    m_listItem.clear();
    m_listPolishItem.clear();
    m_bPackageAlreadyBoult = false;
    m_bPackageViewEnd = false;
    m_dwFristPackageViewTimeOut = 0;
    m_mapItemToPlayer.clear();       
    m_vecItemPackageToPlayer.clear();               // 包裹本身对应玩家的权限

    m_mapVewTime.clear();
    m_chHoldType        = eIHT_Nothing;
    m_chItemAssignType  = AssignMode_FreeMode;
    m_nDropItemType     = PackDropType_Package;
	m_bFirstEnterSight  = true;
}

void ItemCharacter::SetTaskItem()
{
    m_dwDropBeginTime = HQ_TimeGetTime();
    m_dwDropBeginTime += ITEM_DEFINE_LIFE_TIEM;//道具的，保护时间
    m_bTaskItem = true;
}
void ItemCharacter::setPeopleOfTeamTime()
{//队伍中个人的保护时间 为物品掉落时+40秒 40秒以后物品将属于这个队伍
    TimePeopleOfTeam = HQ_TimeGetTime();
    TimePeopleOfTeam += ITEM_PEOPLE_OF_TEAM;//
}

void ItemCharacter::setPeopleOfTeamTime( DWORD tm)
{
    TimePeopleOfTeam = tm;
}
int ItemCharacter::getRemainTimeIsGroupNotPlayer()
{
    int nTime = TimePeopleOfTeam - HQ_TimeGetTime();
    nTime /= 1000;
    if( nTime < 0 )
        nTime = 0;
    return nTime;
}
int ItemCharacter::GetCanPickRemainTime()
{
    int nTime = m_dwDropBeginTime - HQ_TimeGetTime();
    nTime /= 1000;
    if ( nTime < 0 )
        nTime = 0;
    return nTime;
}

void ItemCharacter::Run( DWORD dwCostTime )
{
    BEGINFUNCPERLOG( "ItemCharacter->Run" );

    IBaseControl *pCtrl = GetControl();
    if (pCtrl != NULL)
    {
        pCtrl->Process();
    }
    if( m_borndelay.stBornDelay > 0 )
    {
        m_borndelay.stBornDelay -= dwCostTime;
        if ( m_borndelay.stBornDelay < 0 )
        {
            m_borndelay.stBornDelay = 0;
        }
    }

    //包裹查看超时了, 改变物品包裹权限
    //if (m_dwFristPackageViewTimeOut != 0 && HQ_TimeGetTime() > m_dwFristPackageViewTimeOut)
    //{
    //    ChangePackageAccessAllCanView();
    //}

    //判断丢筛子超时
    CheckPackageItemBoultTimeOut();

    //if( TimePeopleOfTeam )
    //{//队伍分配时 物品归属于此队伍中的某个人 如果40秒还不检的话 物品改变归属于次队伍
    //	if( GameTime::IsLessOrEqualCurrentTime(TimePeopleOfTeam) )
    //	{
    //		setItemAscriptionToGroup(); //取消队伍中某个人的归属 现在物品归属于此队伍
    //	}
    //}
    //
    //if( GameTime::IsLessOrEqualCurrentTime(m_dwDropBeginTime))
    //{
    //	//取消道具保护，任何人都可以pick道具
    //	m_iMasterGroupID = -1;
    //	m_iMasterNpcID = -1;
    //	HoldGroupId = -1;
    //}
    //
    if( GameTime::IsPassCurrentTime( m_dwDropBeginTime, m_dwDeathTime ) )
    {
        ExitWorld(); // 自动消失 不能调用ExitWorldByPushMsg
        ENDFUNCPERLOG( "ItemCharacter->Run" );
        return;         // 如果使用 ExitWorldByPushMsg 一定不能return 否则不能执行下面消息处理
    }

    Msg *pMsg;
    while( pMsg = pCtrl->GetMsg() )
    {
        if( !ProcessMsg( pMsg ) )
        {
            ENDFUNCPERLOG( "ItemCharacter->Run" );
            return; 
        }
    }

    ENDFUNCPERLOG( "ItemCharacter->Run" );
}

//我的第一眼印象
Msg* ItemCharacter::FirstSightOnMe(char* szMsgBuffer, unsigned int nBuffSize)
{
    if (nBuffSize < sizeof(MsgItemEnterMySight))
    { return NULL; }

    MsgItemEnterMySight* pMsg = new (szMsgBuffer) MsgItemEnterMySight;
    pMsg->header.stID = GetID();
    pMsg->ustItemId = m_item.itembaseinfo.ustItemID;
    pMsg->ustItemCount = m_item.itembaseinfo.ustItemCount;
    pMsg->byClientDisplayDelaySecond = ( m_borndelay.stBornDelay + 999 ) / 1000; // 延迟显示时间
    pMsg->nMapID = GetMapID();
    pMsg->fX = GetFloatX();
    pMsg->fY = GetFloatY();
	pMsg->m_bFirstEnterSight = this->m_bFirstEnterSight;
	this->m_bFirstEnterSight = false;

    //包裹的查看权限情况
    if ( !IsPackageHoldByAll() )
    {
        PickAccessVector::iterator iter = m_vecItemPackageToPlayer.begin();
        PickAccessVector::iterator end = m_vecItemPackageToPlayer.end();
        for (; iter != end; ++iter)
        {
            if(iter->chPickAccess & eIPL_View )
            {
                pMsg->AddPackageAccessInfo(iter->dwPlayerDBID);
            }
        }
    }
    return pMsg;
}

void ItemCharacter::OnExit( Msg* pMsg, unsigned char exitType /*= ET_ExitGame*/)
{
    GameObjectId stID = GetControl()->GetID();
    GettheServer().SendMsgToView( pMsg, stID, true );

    theGameWorld.OnDelCharacter( stID );           // 从场景中删掉
    theRunTimeData.ReleaseObject( stID, __FILE__, __LINE__ );
}

bool ItemCharacter::ProcessMsg( Msg* pMsg )
{  
    if( MSG_EXIT == pMsg->GetType() )
    {
        OnExit( pMsg );
        //不处理后续的消息
        return false;
    }
    return true;
}

void ItemCharacter::SetBornDelay( unsigned char ucBornDelay )
{
    m_borndelay.stBornDelay = ucBornDelay * 1000;
    m_borndelay.dwLastCheckTime = HQ_TimeGetTime();
}

void ItemCharacter::SetMasterGroupID(int id)
{

    m_iMasterGroupID = id;

    Msg2CItemAdscription msg;
    msg.npcid = this->GetID();
    msg.adscriptionPlayerId = -1;
    msg.adscriptionGroupId = id;
    msg.bAdscription_TeamHeader = false;
    msg.bHold_Groupid = false;
    GettheServer().SendMsgToView(&msg, this->GetID(), true);

}

void ItemCharacter::SetMasterID(int id)
{
    m_iMasterNpcID = id;

    Msg2CItemAdscription msg;
    msg.npcid = this->GetID();
    msg.adscriptionPlayerId = id;
    msg.adscriptionGroupId = -1;
    msg.bAdscription_TeamHeader = false;
    msg.bHold_Groupid = false;
    GettheServer().SendMsgToView(&msg, this->GetID(), true);

}

void ItemCharacter::setHoldGroupId(int id)
{ 
    HoldGroupId = id;		

    Msg2CItemAdscription msg;
    msg.npcid = this->GetID();
    msg.adscriptionPlayerId = -1;
    msg.adscriptionGroupId = -1;
    msg.bAdscription_TeamHeader = false;
    msg.bHold_Groupid = true;
    GettheServer().SendMsgToView(&msg, this->GetID(), true);

}
void ItemCharacter::setAdscription_teamHeader(bool bHeader)
{
    m_bAdscription_teamHeader = bHeader; 

    Msg2CItemAdscription msg;
    msg.npcid = this->GetID();
    msg.adscriptionPlayerId = -1;
    msg.adscriptionGroupId = -1;
    msg.bAdscription_TeamHeader = true;
    msg.bHold_Groupid = false;
    GettheServer().SendMsgToView(&msg, this->GetID(), true);
}

//nGroupId 是什么id
SCharItem* ItemCharacter::PickItem( uint32 nGroupId, int nPlayerId, EPickResult &result )
{
    return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//add by lxb 关于检包裹的功能
void ItemCharacter::SetPackagePolistDeathTime()
{
    m_dwDropBeginTime = HQ_TimeGetTime();
    m_dwDeathTime = ITEM_DEFINE_LIFE_TIEM * 2;      // 有极品物品,包裹保存4分钟
}

void ItemCharacter::SetPackageNormalDeathTime()
{
    m_dwDropBeginTime = HQ_TimeGetTime();
    m_dwDeathTime = ITEM_DEFINE_LIFE_TIEM;           // 无极品物品,包裹保存2分钟
}

// 添加一个道具到包裹中
bool ItemCharacter::AddCharItem( SCharItem& xItem )                                       
{
    if ( m_listItem.size() >= MaxPackageItemCount )       // 超过最大个数了
    { return false; }

    for ( std::list<SCharItem>::iterator iter = m_listItem.begin(); iter != m_listItem.end(); ++iter )
    {
        if ( iter->itembaseinfo.nOnlyInt == xItem.itembaseinfo.nOnlyInt )
        { return false; }
    }

    m_listItem.push_back(xItem);
    return true;
}

// 从包裹中删除一个道具
void ItemCharacter::RemoveCharItem( __int64 nItemID, uint16 nItemCount )                                       
{
    for (std::list<SCharItem>::iterator iter = m_listItem.begin(); iter != m_listItem.end(); ++iter)
    {
        if ( iter->itembaseinfo.nOnlyInt == nItemID )
        {
            //if ( iter->itembaseinfo.ustItemCount == nItemCount )
            //{
            RemoveItemPickLevel( nItemID );
            ClearPackageItemBoult( nItemID );
            RemovePackageItemBoultTimeOut( nItemID );
            m_listItem.erase( iter );
            // }
            //else
            //{
            //    iter->itembaseinfo.ustItemCount -= nItemCount; 
            //}

            break;
        }
    }

    if( m_listItem.empty() )      //包裹中没物品了
    {
        ExitWorld(); // 自动消失 不能调用ExitWorldByPushMsg
    }
}

// 从包裹中获得一个道具
SCharItem* ItemCharacter::GetCharItem(__int64 nItemID)                                    
{
    for (std::list<SCharItem>::iterator iter = m_listItem.begin(); iter != m_listItem.end(); ++iter)
    {
        if (iter->itembaseinfo.nOnlyInt == nItemID)
        {
            return &(*iter);
        }
    }

    return NULL;
}

// 从包裹中获得一个道具
SCharItem* ItemCharacter::GetCharItemById(uint16 nItemID)                                    
{
    for (std::list<SCharItem>::iterator iter = m_listItem.begin(); iter != m_listItem.end(); ++iter)
    {
        if (iter->itembaseinfo.ustItemID == nItemID)
        {
            return &(*iter);
        }
    }

    return NULL;
}


SCharItem* ItemCharacter::GetCharItemByIndex(short nIndex)
{
    if (nIndex < 0 || nIndex >= m_listItem.size())
    {
        return NULL;
    }

    std::list<SCharItem>::iterator iter = m_listItem.begin();
    advance(iter, nIndex);

    return &(*iter);
}

void ItemCharacter::GetCharItemList( std::vector<__int64>& vecItem )
{
    vecItem.clear();

    for ( std::list<SCharItem>::iterator iter = m_listItem.begin(); iter != m_listItem.end(); ++iter )
    {
        vecItem.push_back( iter->itembaseinfo.nOnlyInt );
    }
}

bool ItemCharacter::AddPolishItem(__int64 nItemID)
{
    std::list<__int64>::iterator iter = find( m_listPolishItem.begin(), m_listPolishItem.end(), nItemID );
    if ( iter == m_listPolishItem.end() )
    {
        m_listPolishItem.push_back(nItemID);
        return true;
    }

    return false;
}

SCharItem* ItemCharacter::GetPolistItemByIndex(short nIndex)
{
    if (nIndex < 0 || nIndex >= m_listPolishItem.size())
    {
        return NULL;
    }

    std::list<__int64>::iterator iter = m_listPolishItem.begin();
    advance(iter, nIndex);

    return GetCharItem(*iter);
}

void ItemCharacter::RemovePolistItem(__int64 nItemID)
{
    std::list<__int64>::iterator iter = find(m_listPolishItem.begin(), m_listPolishItem.end(), nItemID);
    if (iter != m_listPolishItem.end())
    {
        m_listPolishItem.erase(iter);
    }

    if (m_listPolishItem.empty())
    {
        SetPackageNormalDeathTime();            //把包裹的存在时间改为普通包裹时间
    }
}

//是否是需要分配的物品, 分配以后要重列表中删除的
bool ItemCharacter::IsPolistItem(__int64 nItemID)
{
    std::list<__int64>::iterator iter = find(m_listPolishItem.begin(), m_listPolishItem.end(), nItemID);

    return iter != m_listPolishItem.end();
}

// 设置包裹的拾取权限
void ItemCharacter::SetItemPackageAccess(uint32 dwPlayerDBID, uint8 chPickLevel)          
{
    PickAccessVector::iterator iter = find(m_vecItemPackageToPlayer.begin(), m_vecItemPackageToPlayer.end(), dwPlayerDBID);
    if (iter != m_vecItemPackageToPlayer.end())
    {
        iter->chPickAccess = chPickLevel;
        return;
    }

    SPickAccessInfo xPickInfo;
    xPickInfo.dwPlayerDBID = dwPlayerDBID;
    xPickInfo.chPickAccess  = chPickLevel;
    m_vecItemPackageToPlayer.push_back(xPickInfo);
}

// 获得包裹的拾取权限
uint8 ItemCharacter::GetItemPackageAccess(uint32 dwPlayerDBID)                            
{
    if ( IsPackageHoldByAll() )
    {
        return eIPL_View | eIPL_Pick;
    }

    PickAccessVector::iterator iter = find(m_vecItemPackageToPlayer.begin(), m_vecItemPackageToPlayer.end(), dwPlayerDBID);
    if (iter != m_vecItemPackageToPlayer.end())
    {
        return iter->chPickAccess;
    }

    return eIPL_Nothing;
}

// 是否能查看包裹
bool ItemCharacter::IsCanViewItemPackage(uint32 dwPlayerDBID)                                
{
    if ( IsPackageHoldByAll() )
    {
        return true;
    }

    uint8 chPickLevel = GetItemPackageAccess(dwPlayerDBID);

    return ( chPickLevel & eIPL_View ) != 0;
}

bool ItemCharacter::IsInPackageAccessList(uint32 dwPlayerDBID)
{
    PickAccessVector::iterator iter = find(m_vecItemPackageToPlayer.begin(), m_vecItemPackageToPlayer.end(), dwPlayerDBID);
    return (iter != m_vecItemPackageToPlayer.end());
}

void ItemCharacter::SetAllCanViewItemPackage()
{
    PickAccessVector::iterator end = m_vecItemPackageToPlayer.end();
    for (PickAccessVector::iterator iter = m_vecItemPackageToPlayer.begin(); iter != end; ++iter)
    {
        iter->chPickAccess |= eIPL_View;
    }
}

//设置包裹中物品的拾取权限
void ItemCharacter::SetItemPickLevel(__int64 nItemID, uint32 dwPlayerDBID, uint8 chPickLevel)  
{
    PickLevelMap::iterator miter = m_mapItemToPlayer.find(nItemID);
    if (miter == m_mapItemToPlayer.end())
    {
        SPickAccessInfo xPickLevel;
        xPickLevel.dwPlayerDBID = dwPlayerDBID;
        xPickLevel.chPickAccess  = chPickLevel;

        PickAccessVector vecPickInfo;
        vecPickInfo.push_back(xPickLevel);

        m_mapItemToPlayer.insert(make_pair(nItemID, vecPickInfo));
    }
    else
    {
        PickAccessVector::iterator viter = find(miter->second.begin(), miter->second.end(), dwPlayerDBID);
        if (viter != miter->second.end())
        {
            viter->chPickAccess = chPickLevel;
        }
        else
        {
            SPickAccessInfo xPickLevel;
            xPickLevel.dwPlayerDBID = dwPlayerDBID;
            xPickLevel.chPickAccess  = chPickLevel;

            miter->second.push_back(xPickLevel);
        }
    }

}
void ItemCharacter::RemoveItemPickLevel(__int64 nItemID)
{
    PickLevelMap::iterator miter = m_mapItemToPlayer.find(nItemID);
    if (miter != m_mapItemToPlayer.end())
    {
        m_mapItemToPlayer.erase(miter);
    }
}

uint8 ItemCharacter::GetItemPickLevel(__int64 nItemID, uint32 dwPlayerDBID)
{
    if ( IsPackageHoldByAll() )
    { return eIPL_View | eIPL_Pick; }

    PickLevelMap::iterator miter = m_mapItemToPlayer.find(nItemID);
    if (miter == m_mapItemToPlayer.end())
    { return eIPL_Nothing; }

    PickAccessVector::iterator viter = find(miter->second.begin(), miter->second.end(), dwPlayerDBID);
    if (viter == miter->second.end())
    { return eIPL_Nothing; }

    return viter->chPickAccess;
}

void ItemCharacter::SetAllCanPickItem(__int64 nItemID)
{
    PickLevelMap::iterator miter = m_mapItemToPlayer.find(nItemID);
    if (miter == m_mapItemToPlayer.end())
    { return; }

    PickAccessVector::iterator end = miter->second.end();
    for (PickAccessVector::iterator iter = miter->second.begin(); iter != end; ++iter)
    {
        iter->chPickAccess |= eIPL_View | eIPL_Pick ; 
    }
}

// 是否能拾取这个物品
bool ItemCharacter::IsCanPickUpItem(__int64 nItemID, uint32 dwPlayerDBID)                    
{
    uint8 chPickLevel = GetItemPickLevel(nItemID, dwPlayerDBID);

    return ( chPickLevel & ( eIPL_Pick | eIPL_Hold ) ) != 0;
}

// 是否能分配这个物品(一般只有队长模式下才会有用)
bool ItemCharacter::IsCanAssignItem(__int64 nItemID, uint32 dwPlayerDBID)                     
{
    uint8 chPickLevel = GetItemPickLevel(nItemID, dwPlayerDBID);

    return ( chPickLevel & eIPL_Assign ) != 0;
}

//当玩家点开包关闭以后, 包裹中的物品可以被其他玩家拾取
void ItemCharacter::SetCanPickUpAllItem()
{
    PickLevelMap::iterator mend = m_mapItemToPlayer.end();
    for (PickLevelMap::iterator miter = m_mapItemToPlayer.begin(); miter != mend; ++miter)
    {
        PickAccessVector::iterator vend = miter->second.end();
        for (PickAccessVector::iterator viter = miter->second.begin(); viter != vend; ++viter)
        {
            if (!IsPolistItem(miter->first))            // 还在等待分配的物品,不能给拾取权限
            {
                viter->chPickAccess |= eIPL_View | eIPL_Pick;
            }
        }
    }
}

//当筛子决定归属以后,其他玩家不能拾取该物品, 这里删除掉该物品关联的其他玩家信息
void ItemCharacter::SetItemHoldByPlayer(__int64 nItemID, uint32 dwPlayerDBID)
{
    PickLevelMap::iterator miter = m_mapItemToPlayer.find(nItemID);
    if (miter == m_mapItemToPlayer.end())
    {
        return;
    }

    PickAccessVector::iterator viter = find(miter->second.begin(), miter->second.end(), dwPlayerDBID);
    if (viter == miter->second.end())
    {
        return;
    }

    SPickAccessInfo xPickLevel;
    xPickLevel.dwPlayerDBID = dwPlayerDBID;
    xPickLevel.chPickAccess = eIPL_View | eIPL_Pick | eIPL_Hold;

    miter->second.clear();
    miter->second.push_back(xPickLevel);
}

// 这个物品是否所有队员都丢筛子了
bool ItemCharacter::IsAllPackageItemBoult(__int64 nItemID)                                    
{
    PickLevelMap::iterator miter = m_mapItemToPlayer.find(nItemID);
    if (miter == m_mapItemToPlayer.end())
    {
        return false;
    }

    PickAccessVector::iterator vend = miter->second.end();
    for (PickAccessVector::iterator viter = miter->second.begin(); viter != vend; ++viter)
    {
        if (!IsPlayerPackageItemBoult(nItemID, viter->dwPlayerDBID))
        {
            return false;
        }
    }

    return true;
}

bool ItemCharacter::IsPackageItemAbandon(__int64 nItemID)
{
    if (!IsAllPackageItemBoult(nItemID))            // 还有人没有丢筛子
    {
        return false;
    }

    BoultNumberMap::iterator miter = m_mapBoultNumber.find(nItemID);
    if (miter == m_mapBoultNumber.end())
    {
        return true;
    }

    BoultNumberVector::iterator vend = miter->second.end();
    for (BoultNumberVector::iterator viter = miter->second.begin(); viter != vend; ++viter)
    {
        if (viter->nBoultNumber != 0)           //筛子有数量, 说明该玩家丢过筛子
        {
            return false;
        }
    }

    return true;
}   

// 这个玩家是否丢过筛子了
bool ItemCharacter::IsPlayerPackageItemBoult(__int64 nItemID, uint32 dwPlayerDBID)            
{
    BoultNumberMap::iterator iter = m_mapBoultNumber.find(nItemID);
    if (iter == m_mapBoultNumber.end())
    {
        return false;            //没有物品关联,返回false
    }

    BoultNumberVector::iterator viter = find(iter->second.begin(), iter->second.end(), dwPlayerDBID);

    return (viter != iter->second.end());
}

// 添加这个物品玩家的筛子点数
void ItemCharacter::AddPackageItemBoult(__int64 nItemID, uint32 dwPlayerDBID, uint16 nNumber) 
{
    BoultNumberMap::iterator miter = m_mapBoultNumber.find(nItemID);
    if (miter == m_mapBoultNumber.end())
    {
        SPlayerBoultNumber xBoultNumber;
        xBoultNumber.dwPlayerID   = dwPlayerDBID;
        xBoultNumber.nBoultNumber = nNumber;

        BoultNumberVector vecBoultNumber;
        vecBoultNumber.push_back(xBoultNumber);

        m_mapBoultNumber.insert(make_pair(nItemID, vecBoultNumber));
    }
    else
    {
        BoultNumberVector::iterator viter = find(miter->second.begin(), miter->second.end(), dwPlayerDBID);
        if (viter == miter->second.end())
        {
            SPlayerBoultNumber xBoultNumber;
            xBoultNumber.dwPlayerID   = dwPlayerDBID;
            xBoultNumber.nBoultNumber = nNumber;

            miter->second.push_back(xBoultNumber);
        }
    }
}

// 清除这个物品的筛子关联
void ItemCharacter::ClearPackageItemBoult(__int64 nItemID)                                   
{
    BoultNumberMap::iterator iter = m_mapBoultNumber.find(nItemID);
    if (iter != m_mapBoultNumber.end())
    {
        m_mapBoultNumber.erase(iter);
    }
}

// 获得最大点数玩家
uint32 ItemCharacter::GetMaxPackageItemBoult(__int64 nItemID)
{
    BoultNumberMap::iterator miter = m_mapBoultNumber.find(nItemID);
    if (miter == m_mapBoultNumber.end())
    {
        return -1;
    }

    if (miter->second.empty())
    {
        return -1;
    }

    sort(miter->second.begin(), miter->second.end(), greater<SPlayerBoultNumber>());
    SPlayerBoultNumber& xNumber = miter->second.front();

    return xNumber.dwPlayerID;
}

void ItemCharacter::GetPackageItemBoult(__int64 nItemID, BoultNumberVector& vecBoult)
{
    vecBoult.clear();
    BoultNumberMap::iterator miter = m_mapBoultNumber.find(nItemID);
    if (miter == m_mapBoultNumber.end())
    {
        return;
    }

    vecBoult = miter->second;
}

void ItemCharacter::SetPackageItemBoultWhenTimeOut(__int64 nItemID)
{
    PickLevelMap::iterator miter = m_mapItemToPlayer.find(nItemID);
    if (miter == m_mapItemToPlayer.end())
    {
        return;            
    }

    PickAccessVector::iterator vend = miter->second.end();
    for (PickAccessVector::iterator viter = miter->second.begin(); viter != vend; ++viter)
    {
        if (!IsPlayerPackageItemBoult(nItemID, viter->dwPlayerDBID))
        {
            AddPackageItemBoult(nItemID, viter->dwPlayerDBID, 0);
        }
    }
}

// 丢筛子结束以后,判断点数判断物品归属
void ItemCharacter::PackageItemBoultEnd(__int64 nItemID)
{
    SCharItem* pItem = GetCharItem(nItemID);
    if (pItem == NULL)          //要投筛子的物品一定要存在哦
    { return; }

    MsgPackageItemBoultNumber xBoultNumber;
    xBoultNumber.nItemPackageID = GetID();
    xBoultNumber.nItemID        = nItemID;

    ItemCharacter::BoultNumberVector vecBoult;
    GetPackageItemBoult(nItemID, vecBoult);

    //筛子点数情况
    ItemCharacter::BoultNumberVector::iterator end = vecBoult.end();
    for (ItemCharacter::BoultNumberVector::iterator iter = vecBoult.begin(); iter != end; ++iter)
    {         
        xBoultNumber.AddPackageItemBoultNumber(iter->dwPlayerID, iter->nBoultNumber);
    }

    uint32 dwHoldPlayerID = -1;
    if (IsPackageItemAbandon(nItemID))        //所有人放弃了
    {
        //pItemChar->SetAllCanViewItemPackage();
        SetAllCanPickItem(nItemID);       //设置所有人都能拾取这个物品
    }
    else
    {
        dwHoldPlayerID = GetMaxPackageItemBoult(nItemID);
        SetItemHoldByPlayer(nItemID, dwHoldPlayerID);
    }
    xBoultNumber.dwHoldPlayerID = dwHoldPlayerID;

    RemovePolistItem(nItemID);                    // 在优质物品列表中删除
    RemovePackageItemBoultTimeOut(nItemID);       // 删除这个物品的筛子超时时间

    if (dwHoldPlayerID != -1)                     // 分配成功以后直接放包裹里, 除非包裹满了
    {
        GamePlayer* pHoldPlayer = theRunTimeData.GetGamePlayerByDBID(dwHoldPlayerID);
        if (pHoldPlayer != NULL)
        {
            short nResult = pHoldPlayer->AddItemToBag(*pItem, pItem->itembaseinfo.ustItemCount, EIGS_DropItem, 3, GetDropMonsterID() );
            if (nResult == ierr_Success)        //添加成功以后,删除包裹中的这个物品
            {
                RemoveCharItem(nItemID, pItem->itembaseinfo.ustItemCount);
                xBoultNumber.bRemove = true;
            }
        }
    }

    SendMsgToAllPackageEffectPlayer(&xBoultNumber);
}

// 添加该物品丢筛子的超时时间
void ItemCharacter::AddPackageItemBoultTimeOut(__int64 nItemID, uint32 dwTimeOut)                 
{
    BoultTimeMap::iterator iter = m_mapBoultTime.find(nItemID);
    if (iter == m_mapBoultTime.end())
    {
        m_mapBoultTime.insert(make_pair(nItemID, dwTimeOut));
    }
}

// 删除物品丢筛子的超时时间
void ItemCharacter::RemovePackageItemBoultTimeOut(__int64 nItemID)                               
{
    BoultTimeMap::iterator iter = m_mapBoultTime.find(nItemID);
    if (iter != m_mapBoultTime.end())
    {
        m_mapBoultTime.erase(iter);
    }
}

// 判断物品丢筛子时间是否超时
void ItemCharacter::CheckPackageItemBoultTimeOut()
{
    DWORD dwCurrentTime = HQ_TimeGetTime();
    for (BoultTimeMap::iterator iter = m_mapBoultTime.begin(); iter != m_mapBoultTime.end(); ++iter)
    {
        if ( GameTime::IsPassCurrentTime( dwCurrentTime, iter->second, ItemCharacter::ServerBoultTimeOut ) )
        {
            SetPackageItemBoultWhenTimeOut(iter->first);
            PackageItemBoultEnd(iter->first);
            break;              //每次只判断一次 PackageItemBoultEnd 函数里有改变map大小,有可能会迭代器时效导致内存出错
        }
    }
}

// 添加查看包裹的限制时间,一般为2秒
void ItemCharacter::AddPackageViewTime(uint32 dwPlayerID)                                    
{
    uint32 dwTime = HQ_TimeGetTime() + PackageViewSpaceTime;;
    ViewTimeMap::iterator iter = m_mapVewTime.find(dwPlayerID);
    if (iter != m_mapVewTime.end())
    {
        iter->second = dwTime;
    }
    else
    {
        m_mapVewTime.insert(make_pair(dwPlayerID, dwTime));
    }
}

// 已经过了再次查看包裹时间
bool ItemCharacter::IsOverPackageViewLastTime(uint32 dwPlayerID)                              
{
    ViewTimeMap::iterator iter = m_mapVewTime.find(dwPlayerID);
    if (iter == m_mapVewTime.end())
    {
        return true;
    }

    return (HQ_TimeGetTime() > iter->second);
}

void ItemCharacter::ChangePackageAccessAllCanView()
{
    SetAllCanViewItemPackage();          // 设置所有人能看包裹
    SetCanPickUpAllItem();               // 设置所有人能拾取物品

    SetPackageFristViewTimeOut(0);       // 设置不需要验证超时了

    //下发消息
    MsgTellPackageAccess xAccess;
    xAccess.nItemPackageID = GetID();

    if ( !IsPackageHoldByAll() )
    {
        ItemCharacter::PickAccessVector::iterator end = m_vecItemPackageToPlayer.end();
        for (ItemCharacter::PickAccessVector::iterator iter = m_vecItemPackageToPlayer.begin(); iter != end; ++iter)
        {
            if ((iter->chPickAccess & eIPL_View) != 0) 
            {
                xAccess.AddPackageAccessInfo(iter->dwPlayerDBID);
            }
        }
    }

    GettheServer().SendMsgToView(&xAccess, GetID(), true);
}

void ItemCharacter::PackageItemAccessReq(GamePlayer* pPlayer)
{
    if (pPlayer == NULL)
    { return; } 

    MsgPackageitemAccessAck xAccessAck;
    xAccessAck.nItemPackageID = GetID();

    std::list<SCharItem>::iterator end = m_listItem.end();
    for (std::list<SCharItem>::iterator iter = m_listItem.begin(); iter != end; ++iter)
    {
        uint8 chPickItem = GetItemPickLevel(iter->itembaseinfo.nOnlyInt, pPlayer->GetDBCharacterID());
        xAccessAck.AddPackageItem(iter->itembaseinfo.nOnlyInt, chPickItem | eIPL_View);
    }

    if (xAccessAck.nCount > 0)
    {
        GettheServer().SendMsgToSingle(&xAccessAck, pPlayer);
    }
}

//发消息给队长分配, 发送不成功的话,返回false, 这次分配模式变成丢筛子模式
bool ItemCharacter::SendMsgToPackageTeamHeaderPlayer(Msg* pMsg)
{
    GamePlayer* pTeamHeader = theRunTimeData.GetGamePlayerByDBID(m_dwTeamHeaderID);
    if (pTeamHeader == NULL)
    {
        return false;
    }

    //队长离的太远了
    if ( !pTeamHeader->IsInMapArea(GetMapID(), GetFloatX(), GetFloatY(), TEAM_EXP_DIS) )
    {
        return false;
    }

    GettheServer().SendMsgToSingle(pMsg, pTeamHeader);

    return true;
}

//发送消息给有效的成员,
void ItemCharacter::SendMsgToAllPackageEffectPlayer(Msg* pMsg, uint32 dwExceptPlayerID /* = -1 */)
{
    if ( pMsg == NULL ) 
    { return; }

    PickAccessVector::iterator end = m_vecItemPackageToPlayer.end();
    for (PickAccessVector::iterator iter = m_vecItemPackageToPlayer.begin(); iter != end; ++iter)
    {
        if (iter->dwPlayerDBID == dwExceptPlayerID)
        { continue; }     
        GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID(iter->dwPlayerDBID);
        if ( pPlayer == NULL || !pPlayer->IsInMapArea(GetMapID(), GetFloatX(), GetFloatY(), TEAM_EXP_DIS) )
        {
            //不在有效的范围内的玩家,如果是请求丢筛子消息直接算他放弃了
            if ( pMsg->GetType() == MSG_PICKPACKAGEITEMBOULTREQ )
            {
                MsgPackageItemBoultReq* pBoultReq = (MsgPackageItemBoultReq*) pMsg;
                for( int i = 0; i < pBoultReq->nCount; ++i)
                {
                    AddPackageItemBoult(pBoultReq->xItem[i].itembaseinfo.nOnlyInt, iter->dwPlayerDBID, 0);
                }
            }
            continue;
        }

        GettheServer().SendMsgToSingle(pMsg, pPlayer);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////