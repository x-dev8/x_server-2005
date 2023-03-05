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

//Luo ���� ���� m_iMasterGroupID != -1 && m_iMasterGroupID != -1 ʱ�����
#define ITEM_PEOPLE_OF_TEAM		(40*1000)	//�������ʱ ǰ40�����ڶ����е�ĳ���� 40���Ժ����Ϊ�������
ItemCharacter::ItemCharacter()
{
    m_dwDeathTime = ITEM_DEFINE_LIFE_TIEM;  //���ߵ�����ʱ��
    //
    m_dwDropBeginTime = HQ_TimeGetTime();
    //
    m_borndelay.stBornDelay = 0;
    //
    m_iMasterGroupID = -1;
    m_iMasterNpcID = -1;
    //�жϸõ����Ƿ��Ѿ�������������
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
    m_vecItemPackageToPlayer.clear();               // ���������Ӧ��ҵ�Ȩ��

    m_mapVewTime.clear();
    m_chHoldType        = eIHT_Nothing;
    m_chItemAssignType  = AssignMode_FreeMode;
    m_nDropItemType     = PackDropType_Package;
	m_bFirstEnterSight  = true;
}

void ItemCharacter::SetTaskItem()
{
    m_dwDropBeginTime = HQ_TimeGetTime();
    m_dwDropBeginTime += ITEM_DEFINE_LIFE_TIEM;//���ߵģ�����ʱ��
    m_bTaskItem = true;
}
void ItemCharacter::setPeopleOfTeamTime()
{//�����и��˵ı���ʱ�� Ϊ��Ʒ����ʱ+40�� 40���Ժ���Ʒ�������������
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

    //�����鿴��ʱ��, �ı���Ʒ����Ȩ��
    //if (m_dwFristPackageViewTimeOut != 0 && HQ_TimeGetTime() > m_dwFristPackageViewTimeOut)
    //{
    //    ChangePackageAccessAllCanView();
    //}

    //�ж϶�ɸ�ӳ�ʱ
    CheckPackageItemBoultTimeOut();

    //if( TimePeopleOfTeam )
    //{//�������ʱ ��Ʒ�����ڴ˶����е�ĳ���� ���40�뻹����Ļ� ��Ʒ�ı�����ڴζ���
    //	if( GameTime::IsLessOrEqualCurrentTime(TimePeopleOfTeam) )
    //	{
    //		setItemAscriptionToGroup(); //ȡ��������ĳ���˵Ĺ��� ������Ʒ�����ڴ˶���
    //	}
    //}
    //
    //if( GameTime::IsLessOrEqualCurrentTime(m_dwDropBeginTime))
    //{
    //	//ȡ�����߱������κ��˶�����pick����
    //	m_iMasterGroupID = -1;
    //	m_iMasterNpcID = -1;
    //	HoldGroupId = -1;
    //}
    //
    if( GameTime::IsPassCurrentTime( m_dwDropBeginTime, m_dwDeathTime ) )
    {
        ExitWorld(); // �Զ���ʧ ���ܵ���ExitWorldByPushMsg
        ENDFUNCPERLOG( "ItemCharacter->Run" );
        return;         // ���ʹ�� ExitWorldByPushMsg һ������return ������ִ��������Ϣ����
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

//�ҵĵ�һ��ӡ��
Msg* ItemCharacter::FirstSightOnMe(char* szMsgBuffer, unsigned int nBuffSize)
{
    if (nBuffSize < sizeof(MsgItemEnterMySight))
    { return NULL; }

    MsgItemEnterMySight* pMsg = new (szMsgBuffer) MsgItemEnterMySight;
    pMsg->header.stID = GetID();
    pMsg->ustItemId = m_item.itembaseinfo.ustItemID;
    pMsg->ustItemCount = m_item.itembaseinfo.ustItemCount;
    pMsg->byClientDisplayDelaySecond = ( m_borndelay.stBornDelay + 999 ) / 1000; // �ӳ���ʾʱ��
    pMsg->nMapID = GetMapID();
    pMsg->fX = GetFloatX();
    pMsg->fY = GetFloatY();
	pMsg->m_bFirstEnterSight = this->m_bFirstEnterSight;
	this->m_bFirstEnterSight = false;

    //�����Ĳ鿴Ȩ�����
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

    theGameWorld.OnDelCharacter( stID );           // �ӳ�����ɾ��
    theRunTimeData.ReleaseObject( stID, __FILE__, __LINE__ );
}

bool ItemCharacter::ProcessMsg( Msg* pMsg )
{  
    if( MSG_EXIT == pMsg->GetType() )
    {
        OnExit( pMsg );
        //�������������Ϣ
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

//nGroupId ��ʲôid
SCharItem* ItemCharacter::PickItem( uint32 nGroupId, int nPlayerId, EPickResult &result )
{
    return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//add by lxb ���ڼ�����Ĺ���
void ItemCharacter::SetPackagePolistDeathTime()
{
    m_dwDropBeginTime = HQ_TimeGetTime();
    m_dwDeathTime = ITEM_DEFINE_LIFE_TIEM * 2;      // �м�Ʒ��Ʒ,��������4����
}

void ItemCharacter::SetPackageNormalDeathTime()
{
    m_dwDropBeginTime = HQ_TimeGetTime();
    m_dwDeathTime = ITEM_DEFINE_LIFE_TIEM;           // �޼�Ʒ��Ʒ,��������2����
}

// ���һ�����ߵ�������
bool ItemCharacter::AddCharItem( SCharItem& xItem )                                       
{
    if ( m_listItem.size() >= MaxPackageItemCount )       // ������������
    { return false; }

    for ( std::list<SCharItem>::iterator iter = m_listItem.begin(); iter != m_listItem.end(); ++iter )
    {
        if ( iter->itembaseinfo.nOnlyInt == xItem.itembaseinfo.nOnlyInt )
        { return false; }
    }

    m_listItem.push_back(xItem);
    return true;
}

// �Ӱ�����ɾ��һ������
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

    if( m_listItem.empty() )      //������û��Ʒ��
    {
        ExitWorld(); // �Զ���ʧ ���ܵ���ExitWorldByPushMsg
    }
}

// �Ӱ����л��һ������
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

// �Ӱ����л��һ������
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
        SetPackageNormalDeathTime();            //�Ѱ����Ĵ���ʱ���Ϊ��ͨ����ʱ��
    }
}

//�Ƿ�����Ҫ�������Ʒ, �����Ժ�Ҫ���б���ɾ����
bool ItemCharacter::IsPolistItem(__int64 nItemID)
{
    std::list<__int64>::iterator iter = find(m_listPolishItem.begin(), m_listPolishItem.end(), nItemID);

    return iter != m_listPolishItem.end();
}

// ���ð�����ʰȡȨ��
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

// ��ð�����ʰȡȨ��
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

// �Ƿ��ܲ鿴����
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

//���ð�������Ʒ��ʰȡȨ��
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

// �Ƿ���ʰȡ�����Ʒ
bool ItemCharacter::IsCanPickUpItem(__int64 nItemID, uint32 dwPlayerDBID)                    
{
    uint8 chPickLevel = GetItemPickLevel(nItemID, dwPlayerDBID);

    return ( chPickLevel & ( eIPL_Pick | eIPL_Hold ) ) != 0;
}

// �Ƿ��ܷ��������Ʒ(һ��ֻ�жӳ�ģʽ�²Ż�����)
bool ItemCharacter::IsCanAssignItem(__int64 nItemID, uint32 dwPlayerDBID)                     
{
    uint8 chPickLevel = GetItemPickLevel(nItemID, dwPlayerDBID);

    return ( chPickLevel & eIPL_Assign ) != 0;
}

//����ҵ㿪���ر��Ժ�, �����е���Ʒ���Ա��������ʰȡ
void ItemCharacter::SetCanPickUpAllItem()
{
    PickLevelMap::iterator mend = m_mapItemToPlayer.end();
    for (PickLevelMap::iterator miter = m_mapItemToPlayer.begin(); miter != mend; ++miter)
    {
        PickAccessVector::iterator vend = miter->second.end();
        for (PickAccessVector::iterator viter = miter->second.begin(); viter != vend; ++viter)
        {
            if (!IsPolistItem(miter->first))            // ���ڵȴ��������Ʒ,���ܸ�ʰȡȨ��
            {
                viter->chPickAccess |= eIPL_View | eIPL_Pick;
            }
        }
    }
}

//��ɸ�Ӿ��������Ժ�,������Ҳ���ʰȡ����Ʒ, ����ɾ��������Ʒ���������������Ϣ
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

// �����Ʒ�Ƿ����ж�Ա����ɸ����
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
    if (!IsAllPackageItemBoult(nItemID))            // ������û�ж�ɸ��
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
        if (viter->nBoultNumber != 0)           //ɸ��������, ˵������Ҷ���ɸ��
        {
            return false;
        }
    }

    return true;
}   

// �������Ƿ񶪹�ɸ����
bool ItemCharacter::IsPlayerPackageItemBoult(__int64 nItemID, uint32 dwPlayerDBID)            
{
    BoultNumberMap::iterator iter = m_mapBoultNumber.find(nItemID);
    if (iter == m_mapBoultNumber.end())
    {
        return false;            //û����Ʒ����,����false
    }

    BoultNumberVector::iterator viter = find(iter->second.begin(), iter->second.end(), dwPlayerDBID);

    return (viter != iter->second.end());
}

// ��������Ʒ��ҵ�ɸ�ӵ���
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

// ��������Ʒ��ɸ�ӹ���
void ItemCharacter::ClearPackageItemBoult(__int64 nItemID)                                   
{
    BoultNumberMap::iterator iter = m_mapBoultNumber.find(nItemID);
    if (iter != m_mapBoultNumber.end())
    {
        m_mapBoultNumber.erase(iter);
    }
}

// ������������
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

// ��ɸ�ӽ����Ժ�,�жϵ����ж���Ʒ����
void ItemCharacter::PackageItemBoultEnd(__int64 nItemID)
{
    SCharItem* pItem = GetCharItem(nItemID);
    if (pItem == NULL)          //ҪͶɸ�ӵ���Ʒһ��Ҫ����Ŷ
    { return; }

    MsgPackageItemBoultNumber xBoultNumber;
    xBoultNumber.nItemPackageID = GetID();
    xBoultNumber.nItemID        = nItemID;

    ItemCharacter::BoultNumberVector vecBoult;
    GetPackageItemBoult(nItemID, vecBoult);

    //ɸ�ӵ������
    ItemCharacter::BoultNumberVector::iterator end = vecBoult.end();
    for (ItemCharacter::BoultNumberVector::iterator iter = vecBoult.begin(); iter != end; ++iter)
    {         
        xBoultNumber.AddPackageItemBoultNumber(iter->dwPlayerID, iter->nBoultNumber);
    }

    uint32 dwHoldPlayerID = -1;
    if (IsPackageItemAbandon(nItemID))        //�����˷�����
    {
        //pItemChar->SetAllCanViewItemPackage();
        SetAllCanPickItem(nItemID);       //���������˶���ʰȡ�����Ʒ
    }
    else
    {
        dwHoldPlayerID = GetMaxPackageItemBoult(nItemID);
        SetItemHoldByPlayer(nItemID, dwHoldPlayerID);
    }
    xBoultNumber.dwHoldPlayerID = dwHoldPlayerID;

    RemovePolistItem(nItemID);                    // ��������Ʒ�б���ɾ��
    RemovePackageItemBoultTimeOut(nItemID);       // ɾ�������Ʒ��ɸ�ӳ�ʱʱ��

    if (dwHoldPlayerID != -1)                     // ����ɹ��Ժ�ֱ�ӷŰ�����, ���ǰ�������
    {
        GamePlayer* pHoldPlayer = theRunTimeData.GetGamePlayerByDBID(dwHoldPlayerID);
        if (pHoldPlayer != NULL)
        {
            short nResult = pHoldPlayer->AddItemToBag(*pItem, pItem->itembaseinfo.ustItemCount, EIGS_DropItem, 3, GetDropMonsterID() );
            if (nResult == ierr_Success)        //��ӳɹ��Ժ�,ɾ�������е������Ʒ
            {
                RemoveCharItem(nItemID, pItem->itembaseinfo.ustItemCount);
                xBoultNumber.bRemove = true;
            }
        }
    }

    SendMsgToAllPackageEffectPlayer(&xBoultNumber);
}

// ��Ӹ���Ʒ��ɸ�ӵĳ�ʱʱ��
void ItemCharacter::AddPackageItemBoultTimeOut(__int64 nItemID, uint32 dwTimeOut)                 
{
    BoultTimeMap::iterator iter = m_mapBoultTime.find(nItemID);
    if (iter == m_mapBoultTime.end())
    {
        m_mapBoultTime.insert(make_pair(nItemID, dwTimeOut));
    }
}

// ɾ����Ʒ��ɸ�ӵĳ�ʱʱ��
void ItemCharacter::RemovePackageItemBoultTimeOut(__int64 nItemID)                               
{
    BoultTimeMap::iterator iter = m_mapBoultTime.find(nItemID);
    if (iter != m_mapBoultTime.end())
    {
        m_mapBoultTime.erase(iter);
    }
}

// �ж���Ʒ��ɸ��ʱ���Ƿ�ʱ
void ItemCharacter::CheckPackageItemBoultTimeOut()
{
    DWORD dwCurrentTime = HQ_TimeGetTime();
    for (BoultTimeMap::iterator iter = m_mapBoultTime.begin(); iter != m_mapBoultTime.end(); ++iter)
    {
        if ( GameTime::IsPassCurrentTime( dwCurrentTime, iter->second, ItemCharacter::ServerBoultTimeOut ) )
        {
            SetPackageItemBoultWhenTimeOut(iter->first);
            PackageItemBoultEnd(iter->first);
            break;              //ÿ��ֻ�ж�һ�� PackageItemBoultEnd �������иı�map��С,�п��ܻ������ʱЧ�����ڴ����
        }
    }
}

// ��Ӳ鿴����������ʱ��,һ��Ϊ2��
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

// �Ѿ������ٴβ鿴����ʱ��
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
    SetAllCanViewItemPackage();          // �����������ܿ�����
    SetCanPickUpAllItem();               // ������������ʰȡ��Ʒ

    SetPackageFristViewTimeOut(0);       // ���ò���Ҫ��֤��ʱ��

    //�·���Ϣ
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

//����Ϣ���ӳ�����, ���Ͳ��ɹ��Ļ�,����false, ��η���ģʽ��ɶ�ɸ��ģʽ
bool ItemCharacter::SendMsgToPackageTeamHeaderPlayer(Msg* pMsg)
{
    GamePlayer* pTeamHeader = theRunTimeData.GetGamePlayerByDBID(m_dwTeamHeaderID);
    if (pTeamHeader == NULL)
    {
        return false;
    }

    //�ӳ����̫Զ��
    if ( !pTeamHeader->IsInMapArea(GetMapID(), GetFloatX(), GetFloatY(), TEAM_EXP_DIS) )
    {
        return false;
    }

    GettheServer().SendMsgToSingle(pMsg, pTeamHeader);

    return true;
}

//������Ϣ����Ч�ĳ�Ա,
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
            //������Ч�ķ�Χ�ڵ����,���������ɸ����Ϣֱ������������
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