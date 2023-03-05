#include "DropItemManager.h"
#include "DropItem.h"
#include "DropQuestItem.h"
#include "DropCommonItem.h"
#include "DropMonsterItem.h"
#include "MonsterBaseEx.h"
#include "XmlStringLanguage.h"
#include "ItemDetail.h"
#include "CenterGameMessage.h"
#include "DropMonsterItemConfig.h"
#include "DropCommonItemConfig.h"
#include "ShareData.h"
#include "GamePlayer.h"
//#include "LogFileObjectName.h"

DropItemManager& GetDropItemManager()
{
    static DropItemManager s;
    return s;
}

DropItemManager::DropItemManager()
{
    srand( HQ_TimeGetTime() );
}

DropItemManager::~DropItemManager()
{
}

bool DropItemManager::Init()
{
	bool bResult = theDropCommonItemConfig.LoadConfig(COMMONDROPITEM_FILEPATH);
	if ( !bResult )
    { return false; }

	bResult = theDropMonsterItemConfig.LoadConfig(MONSTERDROPITEM_FILEPATH);
	if ( !bResult )
    { return false; }

    bResult = _DropQuestItem.Init();
    if ( !bResult )
    { return false; }

	return true;
}

bool DropItemManager::MonsterDeath( MonsterBaseEx* pMonster, BaseCharacter* pKiller)
{
    if ( !pMonster || !pKiller )
        return false;
    if ( !pMonster->IsMonster() || !pKiller->IsPlayer()/* || pKiller->IsDead()*/ )
    {
        //pKiller->IsDead()֮ǰΪtrue��returnԭ����ȷ,Ϊ�����û��͹ֵ����˱��ɵ��˵��������а�����ж�ȡ�� by ^^
        return false;
    }
    
    _DropQuestItem.MonsterDeath( pMonster, pKiller );
    _DropMonsterItem.MonsterDeath( pMonster, pKiller );
    return true;
}


void DropItemManager::AddItemDropControl( uint16 nItemID, uint32 dwControlCount, uint32 dwDorpCount )
{
    if ( nItemID == ErrorUnsignedShortID )
    { return; }

    MapItemDropControlIter iter = m_mapItemDropControl.find( nItemID );
    if ( iter == m_mapItemDropControl.end() )
    {
        ItemDropControl xControl;
        xControl.dwControlCount = dwControlCount;
        xControl.dwDropCount = dwDorpCount;

        m_mapItemDropControl.insert( make_pair( nItemID, xControl ) );
    }
    else
    {
        iter->second.dwControlCount = dwControlCount;
        iter->second.dwDropCount    = dwDorpCount;
    }
}

ItemDropControl* DropItemManager::GetItemDropControl( uint16 nItemID )
{
    MapItemDropControlIter iter = m_mapItemDropControl.find( nItemID );
    if ( iter  == m_mapItemDropControl.end() )
    { return NULL; }

    return &( iter->second );
}

bool DropItemManager::CheckItemCanDrop( uint16 nItemID, uint16 nCount )
{
    // �ж���Ʒ������ֵ
    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( nItemID );
    if ( pItemCommon == NULL )
    { return false; }

    if ( pItemCommon->nDropControlCount == 0 && pItemCommon->nDropMaxCount == -1 )
    { return true; }        // ������һ���� Ҳ��Ҫ����Manager��

    if ( pItemCommon->nDropMaxCount == 0 )
    { return false; }       // ���ò�����

    MapItemDropControlIter iter = m_mapItemDropControl.find( nItemID );
    if ( iter == m_mapItemDropControl.end() )
    { 
        ItemDropControl xControl;
        xControl.dwControlCount = nCount;
        xControl.dwDropCount = 0;

        iter = m_mapItemDropControl.insert( make_pair( nItemID, xControl ) ).first;
    }   
    else
    {
        iter->second.dwControlCount += nCount;
    }

    if ( iter == m_mapItemDropControl.end() )
    { return false; }

    int nMinCount = 0;
    bool bCanDrop = ( ( pItemCommon->nDropMaxCount == -1 || iter->second.dwDropCount < pItemCommon->nDropMaxCount ) 
						&& iter->second.dwControlCount >= pItemCommon->nDropControlCount );
    if ( bCanDrop )
    {
        // ������˵����Ʒ�ܵ���, ��������
        if ( pItemCommon->bIsClearControlCount )
        {
            iter->second.dwControlCount = 0;        // �����¼����ֵ
        }

        if ( pItemCommon->nDropMaxCount == -1 )
        {
            nMinCount = nCount;
        }
        else
        {
            int nLeftDropCount = pItemCommon->nDropMaxCount - iter->second.dwDropCount;
            nMinCount = ( nCount < nLeftDropCount ? nCount : nLeftDropCount );
        }

        iter->second.dwDropCount += nMinCount;
    }

    // ͬ����CenterServer
    S2SMsgUpdateItemDropControl xControl;
    xControl.nItemID        = nItemID;
    xControl.dwControlCount = iter->second.dwControlCount; // ���͸�CenterServer, ��ǰ����ֵ
    xControl.dwDropCount    = nMinCount ;       // ���͸�CenterServer ,ȷ��Ҫ����ĸ���
    GettheServer().SendMsgToCenterServer( &xControl );

    return bCanDrop;
}

void DropItemManager::DropItemBroadcast( int StringID, uint32 dwPlayerID,  short nMonsterID, int nItemID, ItemCharacter* pItemChar )
{
    if ( StringID <= 0 || nItemID <= 0 || pItemChar == NULL)
    { return; }

    GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( dwPlayerID );
    if ( pPlayer == NULL )
    { return; }

    BaseCharacter* pMonster = theRunTimeData.GetCharacterByID( nMonsterID );
    if ( pMonster == NULL || !pMonster->IsMonster() )
    { return; }

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( nItemID );
    if ( pItemCommon == NULL )
    { return; }

    SCharItem* pCharItem = pItemChar->GetCharItemById( nItemID );
    if ( pCharItem == NULL )
    { return; }

    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( EctypeId2MapId( pPlayer->GetMapID() ) );
    if ( pMapData == NULL )
    { return; }

    char szItemHyberMem[dr_MaxChatString] = { 0 };    
    memcpy( szItemHyberMem, pCharItem, sizeof(SCharItem) );

    char bufStr[BUFSIZ] = {0};
    sprintf_s( bufStr,sizeof(bufStr),theXmlString.GetString(StringID), pPlayer->GetCharName(), pMapData->MapName.c_str(), pMonster->GetCharName(), pItemCommon->GetItemName() );

    pPlayer->ProcessSystem( GamePlayer::SystemWorld, bufStr, szItemHyberMem );
}
