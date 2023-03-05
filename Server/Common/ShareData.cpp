#include "ShareData.h"
#include "application_config.h"
#include "StaticArray.h"
#include "GameWorld.h"
#include "LoginStage.h"
#include "ItemCharacter.h"
#include "GamePlayer.h"
#include "EffectChar.h"
#include "MissionList.h"
#include "TimeClock.h"
#include "FuncPerformanceLog.h"
#include "CCharacterID.h"
#include "WaitReleaseChar.h"
#include "Configure.h"
#include "TimeEx.h"
#include "AntiAddictionSystem.h"
#include "XmlStringLanguage.h"
#include "TeamManager.h"
#include "StageMonitor.h"
#include "NpcNormalEx.h"
#include "NpcShipEx.h"
#include "NpcFightEx.h"
#include "MonsterNormalEx.h"
#include "MonsterBuildEx.h"
#include "MonsterProtectedEx.h"
#include "MonsterSpecial.h"
#include "MonsterPetCapture.h"
#include "MonsterPetTrap.h"
#include "MonsterSummonPet.h"
#include "MonsterPetIllusion.h"
#include "MonsterResource.h"
#include "MonsterPickup.h"
#include "ObjectCounter.h"
#include "TalismanConfig.h"
#include "StarLevelUpConfig.h"
#include "EquipScoreRatioConfig.h"

RunTimeData* RunTimeData::pRunTimeDataInstance = NULL;
RunTimeData& RunTimeData::GetInstance()
{
	if ( !pRunTimeDataInstance )
	{ pRunTimeDataInstance = new RunTimeData; }

	return *pRunTimeDataInstance;
}
RunTimeData::RunTimeData() : theCharacters( dr_worldMaxCharacters ), _nLiftCodeIndex(0), serverStartTime( 0 ),
                                g_bNowSave(false), g_nExpPer( 100 ), g_nSkillExpPer( 100 ), g_bIsChangeSkillExp( false ), m_uchWeakCountryID( 0 )
{
    memset( &_onlineCharactorInfo, 0, sizeof(_onlineCharactorInfo));
    m_mapNameCharacters.clear();
    m_mapDBCharacters.clear();

    memset( m_nCountryOnLineCount, 0, sizeof( m_nCountryOnLineCount ) );

	m_uchWeakCountryID = CountryDefine::Country_Init;
	m_uchStrongCountryID = CountryDefine::Country_Init;
}

RunTimeData::RunTimeData( const RunTimeData& ) : theCharacters( dr_worldMaxCharacters ), _nLiftCodeIndex(0), g_nExpPer( 100 ),
g_nSkillExpPer( 100 ), g_bIsChangeSkillExp( false )
{

}

DWORD RunTimeData::IncreaseOnlinePlayer( int nPlayerCount )
{
    _onlineCharactorInfo.dwOnlinePlayer += nPlayerCount;

    if ( _onlineCharactorInfo.dwOnlinePlayer > _onlineCharactorInfo.dwMaximalOnlinePlayer)
    {
        _onlineCharactorInfo.dwMaximalOnlinePlayer = _onlineCharactorInfo.dwOnlinePlayer;
    }

    OnUpdateBurthen();

    return _onlineCharactorInfo.dwOnlinePlayer;
}

DWORD RunTimeData::IncreaseEnterWorldOnlinePlayer( int nPlayerCount)
{
    int nCount = _onlineCharactorInfo.dwEnterGameWorldOnlinePlayer + nPlayerCount;
    if ( nCount < 0 )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "IncreaseEnterWorldOnlinePlayer calculate result[%d]", nCount);
        nCount = 0;
    }
    _onlineCharactorInfo.dwEnterGameWorldOnlinePlayer = nCount;
    return _onlineCharactorInfo.dwEnterGameWorldOnlinePlayer;
}

DWORD RunTimeData::IncreaseCharacter( int nPlayerCount )
{
    int nCount = _onlineCharactorInfo.dwCharacterCount + nPlayerCount;
    if ( nCount < 0 )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "IncreaseCharacter calculate result[%d]", nCount);
        nCount = 0;
    }
    _onlineCharactorInfo.dwCharacterCount += nPlayerCount;
    return _onlineCharactorInfo.dwCharacterCount;
}

DWORD RunTimeData::IncreaseMonster( int nMonsterCount )
{
	int nCount = _onlineCharactorInfo.dwToalMonster + nMonsterCount;
	if ( nCount < 0 )
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "IncreaseMonster calculate result[%d]", nCount);
		nCount = 0;
	}
	_onlineCharactorInfo.dwToalMonster += nMonsterCount;
	return _onlineCharactorInfo.dwToalMonster;	  
}

DWORD RunTimeData::IncreaseNPC( int nNPCCount )
{
	int nCount = _onlineCharactorInfo.dwTotalNPC + nNPCCount;
	if ( nCount < 0 )
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "IncreaseNPC calculate result[%d]", nCount);
		nCount = 0;
	}
	_onlineCharactorInfo.dwTotalNPC += nNPCCount;
	return _onlineCharactorInfo.dwTotalNPC;	  
}

DWORD RunTimeData::IncreaseItemchar( int nItemcharCount )
{
	int nCount = _onlineCharactorInfo.dwTotalItemchar + nItemcharCount;
	if ( nCount < 0 )
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "IncreaseItemchar calculate result[%d]", nCount);
		nCount = 0;
	}
	_onlineCharactorInfo.dwTotalItemchar += nItemcharCount;
	return _onlineCharactorInfo.dwTotalItemchar;	  
}

void RunTimeData::OnUpdateBurthen()
{   
    MsgGWBurthen msg;
    msg.nCurrOnline = _onlineCharactorInfo.dwOnlinePlayer;
    msg.nMaxOnline  = g_Cfg.iOnlineMax;
    msg.nGateCount  = g_GateServerNum;
    GettheServer().GetCenterServerConnector().Send(&msg);
}

uint8 RunTimeData::GetObjecTypeByNpcType( uint8 npcType )
{
    switch ( npcType )
    {
    case eNT_Normal       :
    case eNT_Restore      :
    case eNT_Weapon       :
    case eNT_Jewelry      :
    case eNT_Dress        :
    case eNT_Material     :
    case eNT_Transport    :
    case eNT_Cavalry      :
    case eNT_Storage      :
    case eNT_Star         :
    case eNT_MakeItemNpc  :
    case eNT_Activity     :
    case eNT_Feudal       :
    case eNT_Sale         :
    case eNT_SpecialSale  :
    case eNT_ScriptNpc    :
    case eNT_GongXun      :
    case eNT_MingWang     :
    case eNT_ShiZhuang    :
    case eNT_WenDa        :
    case eNT_JiNeng       :
    case eNT_PeiJian      :
    case eNT_ShiWu        :
    case eNT_YiZhan       :
    case eNT_ZaHuo        :
    case eNT_FenJie       :
    case eNT_QianZhuang   :
    case eNT_Pub          :
    case eNT_MoveStar     :
    case eNT_SpecialRepair:
    case eNT_KeepWord2    :
    case eNT_KeepWord3    :
    case eNT_KeepWord4    :
    case eNT_KeepWord5    :
    case eNT_KeepWord6    :
    case eNT_KeepWord7    :
    case eNT_KeepWord8    :
    case eNT_KeepWord9    :
    case eNT_Item         :
    case eNT_Battle       :
    case eNT_Elevator     :
    case eNT_SpecialNpc   :
        return Object_NpcNormal;
        break;
    case eNT_Patrol:
        return Object_NpcFight;
        break;
    case eNT_Ship:
        return Object_NpcShip;
        break;
    }

    return Object_NpcNormal;
}

GameObjectId RunTimeData::CreateObject( int ObjectType )
{
    int iIDCharacter = theCharacters.MallocLoopID(ObjectType);

    if (-1 == iIDCharacter)
    { goto FailProcess; }
    
    IBaseControl* pCtrl = NULL;
    IBaseCharControl* pChar = NULL;

    switch(ObjectType)
    {
    case Object_Player:
        pCtrl = NetControlEx::CreateInstance();
        pChar = GamePlayer::CreateInstance();
        break;
    case Object_NpcNormal:
        pCtrl = CNpcCtrl::CreateInstance();
        pChar = NpcNormalEx::CreateInstance();
        break;
    case Object_NpcFight:
        pCtrl = CNpcCtrl::CreateInstance();
        pChar = NEW_POOL( NpcFightEx );
        break;
    case Object_NpcShip:
        pCtrl = CNpcCtrl::CreateInstance();
        pChar = NpcShipEx::CreateInstance();
        break;
    case Object_Item:
        pCtrl = CItemControl::CreateInstance();
        pChar = ItemCharacter::CreateInstance();
        break;
    case Object_Effect:
        pCtrl = CEffectControl::CreateInstance();
        pChar = CEffectChar::CreateInstance();
        break;
    case Object_MonsterNormal:
        pCtrl = CAICharacterControl::CreateInstance();
        pChar = NEW_POOL( MonsterNormalEx );
        break;
    case Object_MonsterPet:
        pCtrl = CAICharacterControl::CreateInstance();
        pChar = NEW_POOL( MonsterSummonPet );
        break;
    case Object_MonsterResource:
        pCtrl = CAICharacterControl::CreateInstance();
        pChar = NEW_POOL( MonsterResource );
        break;
    case Object_MonsterProtected:
        pCtrl = CAICharacterControl::CreateInstance();
        pChar = NEW_POOL( MonsterProtectedEx );
        break;
    case Object_MonsterTrap:
        pCtrl = CAICharacterControl::CreateInstance();
        pChar = NEW_POOL( MonsterPetTrap );
        break;
    case Object_MonsterBuilding:
        pCtrl = CAICharacterControl::CreateInstance();
        pChar = NEW_POOL( MonsterBuildEx );
        break;
    case Object_MonsterNurturePet:
        pCtrl = CAICharacterControl::CreateInstance();
        pChar = NEW_POOL( MonsterNurturePet );
        break;
    case Object_MonsterPickup:
        pCtrl = CAICharacterControl::CreateInstance();
        pChar = NEW_POOL( MonsterPickup );
        break;
	case Object_MonsterSpecial:
		pCtrl = CAICharacterControl::CreateInstance();
        pChar = NEW_POOL( MonsterSpecial );
        break;
    default:
        break;
    }

    if( !pCtrl || !pChar)
        goto FailProcess;

	switch ( ObjectType )
	{
	case Object_Player:
		{ IncreaseOnlinePlayer(); }
		break;
	case Object_NpcNormal:
	case Object_NpcShip:
		{ IncreaseNPC(); }
		break;
	case Object_Item:
		{ IncreaseItemchar(); }
		break;
	default:	// 其余全是怪
		{ IncreaseMonster(); }
		break;
	}

    {
        SControlWithLifeCode CWLC = {0};
        CWLC.ustLifeCode = _nLiftCodeIndex;
        ++_nLiftCodeIndex;

        pCtrl->SetID(iIDCharacter);
        pChar->SetLifeCode(CWLC.ustLifeCode);
        pChar->SetControl(pCtrl);

        CWLC.pCtrl = pCtrl;

        theCharacters[iIDCharacter]->m_Char = pChar;
        theCharacters[iIDCharacter]->m_lifecode = CWLC;

        IncreaseCharacter();
    }

    return iIDCharacter;

FailProcess:
    if( -1 != iIDCharacter )
        theRunTimeData.theCharacters.Free(iIDCharacter);
    if( pCtrl )
        pCtrl->Release();

    if( pChar )
        pChar->Release();

    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"CreateObject 类型[%d] 失败！ iIDCharacter = %d,pCtrl = %d,pChar = %d", ObjectType,iIDCharacter,pCtrl,pChar);
    return -1;
}

void RunTimeData::ReleaseObject( GameObjectId iID,const char* szFile, uint32 line )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID(iID);
    if ( NULL == pChar)
    { return; }

    if (pChar->IsPlayer())              //只有玩家才有用到关联 
    {

        GamePlayer* pGamePlayer = (GamePlayer*)pChar;
        RemoveMapDBID(pGamePlayer->GetDBCharacterID());  // 删除DB ID      map关联
        RemoveMapNameToID(pGamePlayer->GetCharName()); // 删除名字关联
        RemoveMapAccountID(pGamePlayer->GetAccountID()); // 删除Account ID map关联

		LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u:%s:%u:-:%s] RunTimeData::ReleaseObject(%d):%s,%d", pGamePlayer->GetAccountID(), pGamePlayer->GetAccount(),
            pGamePlayer->GetDBCharacterID(), pGamePlayer->GetCharName(), /*pGamePlayer->GetSessionKey(),*/ iID,szFile,line );
    }

    theCharacters.Free(iID);

    pChar->SendNPCExit();

    if ( pChar->IsPlayer() && GetOnlinePlayer()> 0)
    {
        IncreaseOnlinePlayer( -1);
    }

    GettheWaitReleaseChar().AddReleaseChar(pChar);  //添加到等待删除队列中，默认十秒后删除

    if ( GetCharacterCount() > 0 )
    {
        IncreaseCharacter( -1 );
		if ( pChar->IsMonster() )
		{ IncreaseMonster( -1 ); }
		else if ( pChar->IsNpc() )
		{ IncreaseNPC( -1 ); }
		else if ( pChar->IsItem() )
		{ IncreaseItemchar( -1 ); }
    }
}

void RunTimeData::ReleaseAllObject()
{
    int iSizeLoop = 0,iUsedLoop = 0;
    int iSize = theCharacters.GetSize();
    int iUsed = theCharacters.GetUsed();
    for( iSizeLoop = 0 , iUsedLoop = 0 ; ( iSizeLoop < iSize && iUsedLoop < iUsed ) ; ++ iSizeLoop )
    {
        if( theCharacters[iSizeLoop] )
        {
            ++iUsedLoop;
            ReleaseObject( iSizeLoop, __FILE__, __LINE__ );
        }
    }
}

BaseCharacter* RunTimeData::GetCharacterByID( GameObjectId iID )
{
    if ( iID < 0 || iID > dr_worldMaxCharacters)
        return NULL;

    GameObject* pObject = theCharacters[iID];
    if ( !pObject )
        return NULL;

    if ( !pObject->m_Char)
        return NULL;

    return (BaseCharacter*)(pObject->m_Char);
}

bool RunTimeData::AddMapNameToID(std::string strName, GameObjectId iID, bool bReplace /* = true */)
{
    if (strName.empty() || iID < 0) { return false; }

    ItrCharacterByNameContainer iter = m_mapNameCharacters.find(strName);
    if (iter != m_mapNameCharacters.end())
    {   
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "AddMapDBID:已经存在名字关联 %s->%d", strName.c_str(), iter->second);

        if (bReplace)
        { iter->second = iID; }

        return bReplace;
    }
    return m_mapNameCharacters.insert( CharacterByNameContainer::value_type(strName, iID) ).second;
}

bool RunTimeData::RemoveMapNameToID(std::string strName)
{
    ItrCharacterByNameContainer iter = m_mapNameCharacters.find(strName);
    if (iter != m_mapNameCharacters.end())
    {
        m_mapNameCharacters.erase(iter);
        return true;
    }

    return false;
}

bool RunTimeData::AddMapAccountID( uint32 accountId, GameObjectId iId, bool bReplace /*= true*/ )
{
    if ( accountId == 0) 
    { return false; }

    ItrCharacterByAccountIdContainer iter = accountCharacters.find( accountId );
    if (iter != accountCharacters.end())
    {   
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "AddMapAccountID:已经存在名字关联 %d->%d", accountId, iter->second);

        if (bReplace)
        { iter->second = iId; }

        return bReplace;
    }
    return accountCharacters.insert( CharacterByAccountIdContainer::value_type( accountId, iId) ).second;
}

bool RunTimeData::RemoveMapAccountID( uint32 accountId )
{   
    accountCharacters.erase(accountId);
    return true;
}

GamePlayer* RunTimeData::GetGamePlayerByName( const std::string& strName )
{
    if (strName.empty()) 
    { return NULL; }
    
    std::map<std::string, GameObjectId>::iterator iter = m_mapNameCharacters.find(strName);
    if (iter == m_mapNameCharacters.end())
    { return NULL; }
    
    BaseCharacter* pChar = GetCharacterByID(iter->second);
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return NULL; }

    return static_cast< GamePlayer* >( pChar );
}

void RunTimeData::GetGamePlayersByName(const std::string& strName, StringContainer& szCharList)
{
    szCharList.clear();
    
    int nUseSize  = theCharacters.GetPlayerUsed();

    int nUseSizeIndex = 0;
    int nSize        = dr_worldMaxPlayers;

    for(int i=0;  i<nSize && nUseSizeIndex<nUseSize ; ++i)
    {
        BaseCharacter* pChar = GetCharacterByID(i);
        if( !pChar)
            continue;

        ++nUseSizeIndex;
        
        if ( !pChar->IsPlayer())
            continue;

        string strFind = pChar->GetCharName();

        if(strFind.find(strName) != string::npos)
        {
            szCharList.push_back( strFind );
        }
    }
}

bool RunTimeData::AddMapDBID(DWORD dwDBID, GameObjectId iID, bool bReplace /* = false */)
{
    if (dwDBID < 0 || iID < 0) { return false; }

    ItrDbIdCharacterContainer iter = m_mapDBCharacters.find(dwDBID);
    if (iter != m_mapDBCharacters.end())
    {   
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "AddMapDBID:已经存在db关联 %d->%d", dwDBID, iter->second);
        if (bReplace)
        { iter->second = iID; }
        return bReplace;
    }

    return m_mapDBCharacters.insert( CharacterByDbIdContainer::value_type(dwDBID, iID) ).second;
}

bool RunTimeData::RemoveMapDBID(DWORD dwDBID)
{
    m_mapDBCharacters.erase( dwDBID );
    return false;
}

GamePlayer* RunTimeData::GetGamePlayerByDBID( DWORD nDBID )
{   
    if (nDBID <= 0)
    { return NULL; }

    std::map<DWORD, GameObjectId>::iterator iter = m_mapDBCharacters.find(nDBID);
    if ( iter == m_mapDBCharacters.end() )
    { return NULL; }

    BaseCharacter* pChar = GetCharacterByID(iter->second);
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return NULL; }

    return static_cast< GamePlayer* >( pChar );
}

BaseCharacter* RunTimeData::GetCharacterByNpcID(int nNpcId, unsigned int nMapId)
{
    int nUseSize  = theCharacters.GetUsed() - theCharacters.GetPlayerUsed();
    if ( nUseSize<0)
    { nUseSize = 0; }

    int nUseSizeIndex = 0;
    int nSize = theCharacters.GetSize();

    for( int i=BeginOtherCharacterID; nUseSizeIndex<nUseSize && i<nSize; ++i )
    {
        BaseCharacter* pChar = (BaseCharacter*)GetCharacterByID( i );
        if( !pChar )
            continue;

        ++nUseSizeIndex;

        if ( !pChar->IsNpc() )
            continue;

        NpcBaseEx *pNpc = (NpcBaseEx*)pChar;
        if ( !pNpc )
            continue;

        if ( pNpc->GetNpcID() == nNpcId && pNpc->GetMapID() == nMapId ) // 由于NpcId是相同的，需要再加上MapId判断
            return pChar;
    }
    return NULL;
}

BaseCharacter* RunTimeData::GetCharacterByMonsterID( int nMonsterId, unsigned int nMapId )
{
	int nUseSize  = theCharacters.GetUsed() - theCharacters.GetPlayerUsed();
	if ( nUseSize<0)
	{ nUseSize = 0; }

	int nUseSizeIndex = 0;
	int nSize = theCharacters.GetSize();

	for( int i=BeginOtherCharacterID; nUseSizeIndex<nUseSize && i<nSize; ++i )
	{
		BaseCharacter* pChar = (BaseCharacter*)GetCharacterByID( i );
		if( !pChar )
			continue;

		++nUseSizeIndex;

		if ( !pChar->IsMonster() )
			continue;

		MonsterBaseEx *pMonster = (MonsterBaseEx*)pChar;
		if ( !pMonster )
			continue;

		if ( pMonster->GetMonsterID() == nMonsterId && pMonster->GetMapID() == nMapId ) // 由于MonsterId是相同的，需要再加上MapId判断
			return pChar;
	}
	return NULL;
}

IBaseCharControl* RunTimeData::GetCharacterByIDAndLifecode(GameObjectId iID, unsigned short ustLifeCode)
{       
    IBaseCharControl* pChar = GetCharacterByID(iID);
    if ( !pChar )
        return NULL;

    if ( pChar->IsSameCharacter(iID, ustLifeCode))
        return pChar;
    
    return NULL;
}

GamePlayer* RunTimeData::GetCharacterByAccountID( uint32 dwAccount)
{   
    if (dwAccount == 0 ) 
    { return NULL; }

    ItrCharacterByAccountIdContainer iter = accountCharacters.find( dwAccount );
    if (iter == accountCharacters.end())
    { return NULL; }

    BaseCharacter* pChar = GetCharacterByID(iter->second);
    if ( pChar == NULL )
    { return NULL; }

    if ( !pChar->IsPlayer() )
    { return NULL; }

    return (GamePlayer*)pChar;
    //int nUseSize  = theCharacters.GetPlayerUsed();

    //int nUseSizeIndex = 0;
    //int nSize         = dr_worldMaxPlayers;

    //for (int i=0; nUseSizeIndex<nUseSize && i<nSize ;  ++i)
    //{
    //    BaseCharacter* pChar = GetCharacterByID( i );
    //    if( !pChar )
    //        continue;
    //    ++nUseSizeIndex;

    //    if (!pChar->IsPlayer())
    //        continue;

    //    GamePlayer* pPlayer = (GamePlayer*)pChar;
    //    if ( !pPlayer )
    //        continue;
    //       
    //    if( pPlayer->GetAccountID() == dwAccount)
    //        return pPlayer;
    //}

    return NULL;
}

bool RunTimeData::CreateItem( BaseCharacter* pChar, unsigned short ustItemID, short stCount, __int64 nGUID, OUT SCharItem& rItem ,bool isChangeUnBindSum ,unsigned short UnBindeSum)
{
    if ( !CreateItem( ustItemID, stCount, nGUID, rItem ,isChangeUnBindSum,UnBindeSum) )
    { return false; }

    if ( pChar == NULL || !pChar->IsPlayer() )
    { return true; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( ustItemID );
    if( pItemDetail == NULL )
    { return true; }

    switch ( pItemDetail->ucItemType )
    {
    case ItemDefine::ITEMTYPE_SPECIAL:
        {
            ItemDefine::SItemSpecial* pItemSpecial = static_cast< ItemDefine::SItemSpecial* >( pItemDetail );
            switch ( pItemSpecial->uchSpecialType )
            {
            case ItemDefine::SItemSpecial::ECD_MarriageCard:
                {
                    rItem.itembaseinfo.value1 = pPlayer->GetDBCharacterID();        // 专用物品, 将该角色的DBID 赋值给value1
                    strncpy_s( rItem.itembaseinfo.szCreaterName, sizeof( rItem.itembaseinfo.szCreaterName ), pPlayer->GetCharName(), sizeof( rItem.itembaseinfo.szCreaterName ) - 1 );
                }
                break;
            }
        }
        break;
    }

    return true;
}

bool RunTimeData::CreateItem( unsigned short ustItemID, short stCount, __int64 nGUID, OUT SCharItem& rItem ,bool isChangeUnBindSum ,unsigned short UnBindeSum )
{
    ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( ustItemID );
    if( pItemDetail == NULL )
    { return false; }

    if ( InvalidLogicNumber == ustItemID || stCount <= 0 || stCount > pItemDetail->nStackNum )
    { return false; }

    rItem.itembaseinfo.ustItemID = ustItemID;
    rItem.bCanUse = true;

    rItem.itembaseinfo.n64UseTime = TimeEx::UNDEF_TIME;
    rItem.itembaseinfo.nLeftTime  = TimeEx::UNDEF_TIME;
    rItem.itembaseinfo.ustItemCount = stCount;

    if ( pItemDetail->IsExclusive() )
    {
        rItem.itembaseinfo.ustItemCount = 1;
        
        //ItemDatail里面取出来的是小时. 这里转换为秒 
        if( pItemDetail->nUseTime != TimeEx::UNDEF_TIME )
        {
            uint32 dwTime = pItemDetail->nUseTime * 60 * 60;
            TimeSpan timespan( dwTime );
            TimeEx DestTime = TimeEx::GetCurrentTime() + timespan;

            rItem.itembaseinfo.n64UseTime = DestTime.GetTime();
            rItem.itembaseinfo.nLeftTime  = timespan.GetTimeSpan();
        }
    }

	if(pItemDetail->IsCanEquip())
	{
		if(isChangeUnBindSum)
			rItem.equipdata.unBindCount = UnBindeSum;//设置实际物品的绑定次数
		else
		{
			ItemDefine::SItemCanEquip * pEquipCommon = (ItemDefine::SItemCanEquip *)pItemDetail;
			rItem.equipdata.unBindCount = pEquipCommon->unBindCount;//创建物品的时候 设置好物品的 属性
		}
	}

    // 初始化物品的数值
    rItem.equipdata.quality = pItemDetail->ustLevel;    // 物品品质
    switch ( pItemDetail->ucItemType )
    {
    case ItemDefine::ITEMTYPE_RESTORE:
        {
            ItemDefine::SItemRestore* pRestore = (ItemDefine::SItemRestore*)pItemDetail;
            if ( pRestore->bHPAuto )
            {
                rItem.itembaseinfo.value2 = pRestore->dwAddHP;
            }
            else if ( pRestore->bMPAuto )
            {
                rItem.itembaseinfo.value2 = pRestore->dwAddMP;
            }
        }
        break;
    case ItemDefine::ITEMTYPE_MATERIAL:
        { }
        break;
    case ItemDefine::ITEMTYPE_GEM:
        { }
        break;
    case ItemDefine::ITEMTYPE_WEAPON:
    case ItemDefine::ITEMTYPE_ARMOUR:
        {
            ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip *)pItemDetail;
            // 耐久度
            rItem.equipdata.usHP    = pItemCanEquip->stHPMax;
            rItem.equipdata.usHpMax = pItemCanEquip->stHPMax;
            rItem.equipdata.ucLevel = SCharItem::EL_Min;
            rItem.equipdata.gemHoleCount = 0;
            rItem.equipdata.element = GetRand( ItemElements_Metal, ItemElements_Earth );
			rItem.equipdata.ustEquipType = pItemCanEquip->ustEquipType;
            
			if ( pItemCanEquip->RandWhenCreate())
            { EquipBaseRand(rItem); }

			EquipScore(rItem, pItemDetail); // 计算装备评分

        }
        break;
    case ItemDefine::ITEMTYPE_TALISMAN:
        {
            ItemDefine::SItemTalisman* pItemTalisman = (ItemDefine::SItemTalisman *)pItemDetail;

            InitTalismanEquip( rItem, pItemTalisman );
        }
        break;
	case ItemDefine::ITEMTYPE_PETEQUIP:
		{
			ItemDefine::SItemPetEquip* pItemTalisman = (ItemDefine::SItemPetEquip *)pItemDetail;
			InitPetEquip(rItem,pItemTalisman);
		}
		break;
    }    

    rItem.itembaseinfo.nOnlyInt     = nGUID;
    rItem.SetLock       ( false );
    rItem.SetBounded    ( !pItemDetail->bIsCanTrade  );
    rItem.SetSoulStamp  ( false );
    return true;
}
bool RunTimeData::InitPetEquip( OUT SCharItem& rItem, ItemDefine::SItemPetEquip* pItemCanEquip )
{
	//初始化 副将装备
	if ( pItemCanEquip == NULL )
    { return false; }
	rItem.petequipdata.Strength = pItemCanEquip->Strength ;
	rItem.petequipdata.Agility = pItemCanEquip->Agility ;
	rItem.petequipdata.Stamina= pItemCanEquip->Stamina;
	rItem.petequipdata.Intelligence= pItemCanEquip->Intelligence;
	rItem.petequipdata.iEquipLevelReq= pItemCanEquip->iEquipLevelReq;
	rItem.petequipdata.isTimeEnd = false;
	return true;
}
bool RunTimeData::InitTalismanEquip( OUT SCharItem& rItem, ItemDefine::SItemTalisman* pItemTalisman )
{
    if ( pItemTalisman == NULL )
    { return false; }

    uint8* pTalismanQuality = theTalismanConfig.GetTalismanQuality();

    rItem.equipdata.element     = GetRand( ItemElements_Metal, ItemElements_Earth );
    rItem.talismandata.quality  = GetRandIndex( pTalismanQuality, ETalismanQuality_Count, theRand.rand16() % RAND_NUM );
    rItem.talismandata.level    = 1;
    rItem.talismandata.daoxing  = pItemTalisman->daoxing;
    rItem.talismandata.nimbus           = pItemTalisman->nimbusMax;
    rItem.talismandata.nimbusMax        = pItemTalisman->nimbusMax;
    rItem.talismandata.nimbusRestore    = pItemTalisman->nimbusRestore;
    rItem.talismandata.exp              = 0;
    rItem.talismandata.randAttrNumber   = theTalismanConfig.GetRandAttrNumber( rItem.talismandata.quality );
    
    theTalismanConfig.InitTalismanEquipAttr( pItemTalisman->ustItemID, rItem.talismandata.quality, rItem.equipdata.element, rItem.equipdata.baseRands );
    theTalismanConfig.InitTalismanRandAttr ( pItemTalisman->poolId, rItem.talismandata.talismanRands );

    return true;
}

bool RunTimeData::EquipBaseRand( OUT SCharItem& rItem, bool bJustFixedRand /*= true*/  )
{
    ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( rItem.itembaseinfo.ustItemID);
    if ( pItemDetail == NULL || !pItemDetail->IsCanEquip() )
    { return false; }

    ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*)pItemDetail;
    if (!pItemCanEquip)
    { return false; }
/*
//modified by junyi.chen begin
//    short sRandNum = pItemCanEquip->additiveRandCount;
	short sRandNum = 0;
	for ( int i = 0; i < ItemDefine::SItemCanEquip::ECD_AdditiveRandAttrCount; ++i )
	{
		int16 nRoll = theRand.rand16() % 10000;
		if ( nRoll < pItemCanEquip->additiveRandCountRates[i] )
		{
			sRandNum = ItemDefine::SItemCanEquip::ECD_AdditiveRandAttrCount - i;
			break;
		}
	}
//end
    
    if (sRandNum <= 0)
    { return true; }

    if (sRandNum > SCharItem::EConstDefine_BaseRandMaxCount)
    { sRandNum = SCharItem::EConstDefine_BaseRandMaxCount; }
    
//modified by junyi.chen begin
//     // 根据Flag位判断是否sRandNum也要随机 不是固定的 个数也要随机
//     if ( !pItemCanEquip->additiveRandFlags[0] )
//     { sRandNum = theRand.rand16() % (sRandNum + 1); }
// 
//     if (sRandNum == 0)
//     {  ++sRandNum; }
//end

    //清空随机属性
    memset( rItem.equipdata.baseRands, 0, sizeof(rItem.equipdata.baseRands) );

//added by junyi.chen begin
	ItemDefine::RandAttrContainer randResult;
//end
    for (int i = 0; i<sRandNum; ++i)
    {
        if ( pItemCanEquip->additiveRandFlags[i] )
        { // 数值

//modified by junyi.chen begin
//            ItemDefine::SRandAttribute* pRand = GettheItemDetail().GetRandByID(pItemCanEquip->additiveRandValues[i]);
			ItemDefine::SRandAttribute* pRand = GettheItemDetail().GetRandByID(pItemCanEquip->additiveRandFlags[i]);
//end
            if ( pRand != NULL )
            {
                rItem.equipdata.baseRands[i] = pRand->id;
//added by junyi.chen begin
				ItemDefine::RandAttr	randAttr;
				randAttr.usID = pRand->id;
				randAttr.usType = pRand->type[0];
				randResult.push_back(randAttr);
//end
            }
        }
        else
        { // 等级
//modified by junyi.chen begin
//            CItemDetail::RandContainer rands;
			ItemDefine::RandAttrContainer rands;

//            GettheItemDetail().GetRandByLevel(pItemCanEquip->additiveRandValues[i],rands);
			int nRollLvl = 0;
			nRollLvl = theRand.rand16() % ( pItemCanEquip->additiveRandLvUpperLimit - pItemCanEquip->additiveRandLvLowerLimit + 1 ) + pItemCanEquip->additiveRandLvLowerLimit;


//			GettheItemDetail().GetRandByLevel(pItemCanEquip->additiveRandValues[i],rands);
			GettheItemDetail().GetRandByLevel(nRollLvl,rands);

			//类型筛选
			CItemDetail::ItrRandAttrContainer it;
			for ( it = rands.begin(); it != rands.end(); ++it )
			{
				int i = 0;
				for ( ; i < pItemCanEquip->typeFilter.GetSize(); ++i )
				{
					if ( pItemCanEquip->typeFilter[i] > 0  && pItemCanEquip->typeFilter[i] == it->usType )
					{
						break;
					}
				}
				if ( i < pItemCanEquip->typeFilter.GetSize() )
				{
					rands.erase(it);
				}
			}
//end
            if ( !rands.empty() )
            {
                int nSize = rands.size();
                int nIndex = theRand.rand16() % nSize;
//modified by junyi.chen begin
//                rItem.equipdata.baseRands[i] = rands[nIndex];
				rItem.equipdata.baseRands[i] = rands[nIndex].usID;
				randResult.push_back(rands[nIndex]);
//end
            }
        }
    }
*/
	// by liaojie
	//bool bRandAttr = true;
	//if (pItemCanEquip->nHeroID!=0)
	//{
	//	bRandAttr = EquipBaseRand_Hero(rItem.equipdata.suitRands, pItemCanEquip);
	//}
    return EquipBaseRand(rItem.equipdata.baseRands, pItemCanEquip);
}

bool RunTimeData::EquipBaseRand( OUT IN uint16 *rands, ItemDefine::SItemCanEquip* pConfig, bool bJustFixedRand /*= false */ )
{
	if ( NULL == rands || NULL == pConfig )
	{
		return false;
	}

	short sRandNum = 0;
	for ( int i = 0; i < ItemDefine::SItemCanEquip::ECD_AdditiveRandAttrCount; ++i )
	{
		int16 nRoll = theRand.rand16() % 10000;
		if ( nRoll < pConfig->additiveRandCountRates[i] )
		{
			sRandNum = ItemDefine::SItemCanEquip::ECD_AdditiveRandAttrCount - i;
			break;
		}
	}

	if (sRandNum <= 0)
	{
		//对鉴定结果为无附加随机属性的装备做的处理来标记为已鉴定过
		rands[0] = SCharItem::EConstDefine_HasBaseRanded;
		return true;
	}

	if (sRandNum > SCharItem::EConstDefine_BaseRandMaxCount)
	{ sRandNum = SCharItem::EConstDefine_BaseRandMaxCount; }

	//清空随机属性
	memset( rands, 0, sizeof(uint16) * SCharItem::EConstDefine_BaseRandMaxCount );

	CItemDetail::RandAttrContainer randResult;
	for (int i = 0; i<sRandNum; ++i)
	{
		if ( pConfig->additiveRandFlags[i] )
		{ // 数值
			ItemDefine::SRandAttribute* pRand = GettheItemDetail().GetRandByID(pConfig->additiveRandFlags[i]);

			if ( pRand != NULL )
			{
				rands[i] = pRand->id;

				ItemDefine::RandAttr	randAttr;
				randAttr.usID = pRand->id;
				randAttr.usType = pRand->type[0];
				randResult.push_back(randAttr);
			}
		}
		else
		{ // 等级
			CItemDetail::RandAttrContainer randsByLvl;

			int nRollLvl = 0;
			if ( pConfig->additiveRandLvUpperLimit - pConfig->additiveRandLvLowerLimit >= 0 )
			{
				nRollLvl = theRand.rand16() % ( pConfig->additiveRandLvUpperLimit - pConfig->additiveRandLvLowerLimit + 1 ) + pConfig->additiveRandLvLowerLimit;
			}
			GettheItemDetail().GetRandByLevel(nRollLvl,randsByLvl);

			//类型筛选
			CItemDetail::RandAttrContainer randsAfterFilter;
			CItemDetail::ItrRandAttrContainer it = randsByLvl.begin();
			for ( ; it != randsByLvl.end(); ++it )
			{
				int i = 0;
				for ( ; i < pConfig->typeFilter.GetSize(); ++i )
				{
					if ( pConfig->typeFilter[i] > 0  && pConfig->typeFilter[i] == it->usType )
					{
						randsAfterFilter.push_back( *it );
						break;
					}
				}
			}

			//去除已有属性,为了不重复
			CItemDetail::RandAttrContainer randsNoRepeat;
			for ( it = randsAfterFilter.begin(); it != randsAfterFilter.end(); ++it )
			{
				CItemDetail::ItrRandAttrContainer itRlt = randResult.begin();
				for ( ; itRlt < randResult.end(); ++itRlt )
				{
					if ( itRlt->usType == it->usType )
					{ break; }
				}

				if ( itRlt == randResult.end() )
				{ randsNoRepeat.push_back( *it ); }
			}

			if ( !randsNoRepeat.empty() )
			{
				int nSize = randsNoRepeat.size();
				int nIndex = theRand.rand16() % nSize;
				rands[i] = randsNoRepeat[nIndex].usID;
				randResult.push_back( randsNoRepeat[nIndex] );
			}
		}
	}
	return true;
}

bool RunTimeData::EquipRandAttrByIds(SCharItem& rItem, int nRandId1, int nRandId2, int nRandId3, int nRandId4, int nRandId5, int nRandId6, int nRandId7)
{
	ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( rItem.itembaseinfo.ustItemID);
	if ( pItemDetail == NULL || !pItemDetail->IsCanEquip() )
	{ return false; }

	ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*)pItemDetail;
	if (!pItemCanEquip)
	{ return false; }

	//清空随机属性
	memset( rItem.equipdata.baseRands, 0, sizeof(uint16) * SCharItem::EConstDefine_BaseRandMaxCount );

	if (nRandId1 > 0)
	{
		ItemDefine::SRandAttribute* pRand = GettheItemDetail().GetRandByID(nRandId1);

		if ( pRand != NULL && 0 < SCharItem::EConstDefine_BaseRandMaxCount )
			rItem.equipdata.baseRands[0] = pRand->id;
	}

	if (nRandId2 > 0)
	{
		ItemDefine::SRandAttribute* pRand = GettheItemDetail().GetRandByID(nRandId2);

		if ( pRand != NULL && 1 < SCharItem::EConstDefine_BaseRandMaxCount )
			rItem.equipdata.baseRands[1] = pRand->id;
	}

	if (nRandId3 > 0)
	{
		ItemDefine::SRandAttribute* pRand = GettheItemDetail().GetRandByID(nRandId3);

		if ( pRand != NULL && 2 < SCharItem::EConstDefine_BaseRandMaxCount )
			rItem.equipdata.baseRands[2] = pRand->id;
	}

	if (nRandId4 > 0)
	{
		ItemDefine::SRandAttribute* pRand = GettheItemDetail().GetRandByID(nRandId4);

		if ( pRand != NULL && 3 < SCharItem::EConstDefine_BaseRandMaxCount )
			rItem.equipdata.baseRands[3] = pRand->id;
	}

	if (nRandId5 > 0)
	{
		ItemDefine::SRandAttribute* pRand = GettheItemDetail().GetRandByID(nRandId5);

		if ( pRand != NULL && 4 < SCharItem::EConstDefine_BaseRandMaxCount )
			rItem.equipdata.baseRands[4] = pRand->id;
	}

	if (nRandId6 > 0)
	{
		ItemDefine::SRandAttribute* pRand = GettheItemDetail().GetRandByID(nRandId6);

		if ( pRand != NULL && 5 < SCharItem::EConstDefine_BaseRandMaxCount )
			rItem.equipdata.baseRands[5] = pRand->id;
	}

	if (nRandId7 > 0)
	{
		ItemDefine::SRandAttribute* pRand = GettheItemDetail().GetRandByID(nRandId7);

		if ( pRand != NULL && 6 < SCharItem::EConstDefine_BaseRandMaxCount )
			rItem.equipdata.baseRands[6] = pRand->id;
	}

	return true;
}

//bool RunTimeData::EquipBaseRand_Hero( OUT IN uint16 *rands, ItemDefine::SItemCanEquip* pConfig, bool bJustFixedRand /*= false */ )
//{
//	if ( NULL == rands || NULL == pConfig )
//	{
//		return false;
//	}
//
//	short sRandNum = 0;
//	for ( int i = 0; i < ItemDefine::SItemCanEquip::ECD_AdditiveRandAttrCount; ++i )
//	{
//		int16 nRoll = theRand.rand16() % 10000;
//		if ( nRoll < pConfig->additiveRandCountRates[i] )
//		{
//			sRandNum = ItemDefine::SItemCanEquip::ECD_AdditiveRandAttrCount - i;
//			break;
//		}
//	}
//
//	if (sRandNum <= 0)
//	{
//		//对鉴定结果为无附加随机属性的装备做的处理来标记为已鉴定过
//		rands[0] = SCharItem::EConstDefine_HasBaseRanded;
//		return true;
//	}
//
//	if (sRandNum > SCharItem::EConstDefine_BaseRandMaxCount)
//	{ sRandNum = SCharItem::EConstDefine_BaseRandMaxCount; }
//
//	//清空随机属性
//	memset( rands, 0, sizeof(uint16) * SCharItem::EConstDefine_BaseRandMaxCount );
//
//	ItemDefine::RandAttrContainer randResult;
//	for (int i = 0; i<sRandNum; ++i)
//	{
//		if ( pConfig->additiveRandFlags[i] )
//		{ // 数值
//			ItemDefine::SRandAttribute* pRand = GettheItemDetail().GetRandByID(pConfig->additiveRandFlags[i]);
//
//			if ( pRand != NULL )
//			{
//				rands[i] = pRand->id;
//
//				ItemDefine::RandAttr	randAttr;
//				randAttr.usID = pRand->id;
//				randAttr.usType = pRand->type[0];
//				randResult.push_back(randAttr);
//			}
//		}
//		else
//		{ // 等级
//			ItemDefine::RandAttrContainer randsByLvl;
//
//			int nRollLvl = 0;
//			if ( pConfig->additiveRandLvUpperLimit - pConfig->additiveRandLvLowerLimit >= 0 )
//			{
//				nRollLvl = theRand.rand16() % ( pConfig->additiveRandLvUpperLimit - pConfig->additiveRandLvLowerLimit + 1 ) + pConfig->additiveRandLvLowerLimit;
//			}
//			GettheItemDetail().GetRandByLevel(nRollLvl,randsByLvl);
//
//			//类型筛选
//			ItemDefine::RandAttrContainer randsAfterFilter;
//			CItemDetail::ItrRandAttrContainer it = randsByLvl.begin();
//			for ( ; it != randsByLvl.end(); ++it )
//			{
//				int i = 0;
//				for ( ; i < pConfig->typeFilter_hero.GetSize(); ++i )
//				{
//					if ( pConfig->typeFilter_hero[i] > 0  && pConfig->typeFilter_hero[i] == it->usType )
//					{
//						randsAfterFilter.push_back( *it );
//						break;
//					}
//				}
//			}
//
//			//去除已有属性,为了不重复
//			ItemDefine::RandAttrContainer randsNoRepeat;
//			for ( it = randsAfterFilter.begin(); it != randsAfterFilter.end(); ++it )
//			{
//				CItemDetail::ItrRandAttrContainer itRlt = randResult.begin();
//				for ( ; itRlt < randResult.end(); ++itRlt )
//				{
//					if ( itRlt->usType == it->usType )
//					{ break; }
//				}
//
//				if ( itRlt == randResult.end() )
//				{ randsNoRepeat.push_back( *it ); }
//			}
//
//			if ( !randsNoRepeat.empty() )
//			{
//				int nSize = randsNoRepeat.size();
//				int nIndex = theRand.rand16() % nSize;
//				rands[i] = randsNoRepeat[nIndex].usID;
//				randResult.push_back( randsNoRepeat[nIndex] );
//			}
//		}
//	}
//	return true;
//}

bool RunTimeData::EquipPurpleRand( OUT IN SCharItem& rItem)
{
    ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( rItem.itembaseinfo.ustItemID);
    if ( pItemDetail == NULL || !pItemDetail->IsCanEquip() )
    { return false; }

    ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*)pItemDetail;
    if (!pItemCanEquip)
    { return false; }

    short sRandNum = pItemCanEquip->purpleRandCount;

    if (sRandNum <= 0)
    { return true; }

    if (sRandNum > SCharItem::EConstDefine_PurpleRandMaxCount)
    { sRandNum = SCharItem::EConstDefine_PurpleRandMaxCount; }

    // 根据Flag位判断是否sRandNum也要随机 不是固定的 个数也要随机
    if ( !pItemCanEquip->purpleRandFlags[0] )
    { sRandNum = theRand.rand16() % (sRandNum + 1); }

    if (sRandNum == 0)
    {  ++sRandNum; }

    //清空紫色随机属性
    memset( rItem.equipdata.purpleRands, 0, sizeof(rItem.equipdata.purpleRands) );
    
	CItemDetail::RandAttrContainer randResult;
    for (int i = 0; i<sRandNum; ++i)
    {
        if ( pItemCanEquip->purpleRandFlags[i])
        { // 数值
            ItemDefine::SRandAttribute* pRand = GettheItemDetail().GetRandByID(pItemCanEquip->purpleRandValues[i]);
            if ( pRand != NULL )
            {
                rItem.equipdata.purpleRands[i] = pRand->id;
            }
        }
        else
        { // 等级
            CItemDetail::RandAttrContainer randsByLvl;
            GettheItemDetail().GetRandByLevel(pItemCanEquip->purpleRandValues[i],randsByLvl);

			//类型筛选
			CItemDetail::RandAttrContainer randsAfterFilter;
			CItemDetail::ItrRandAttrContainer it = randsByLvl.begin();
			for ( ; it != randsByLvl.end(); ++it )
			{
				int i = 0;
				for ( ; i < pItemCanEquip->typeFilter.GetSize(); ++i )
				{
					if ( pItemCanEquip->typeFilter[i] > 0  && pItemCanEquip->typeFilter[i] == it->usType )
					{
						randsAfterFilter.push_back( *it );
						break;
					}
				}
			}

			//去除已有属性,为了不重复
			CItemDetail::RandAttrContainer randsNoRepeat;
			for ( it = randsAfterFilter.begin(); it != randsAfterFilter.end(); ++it )
			{
				CItemDetail::ItrRandAttrContainer itRlt = randResult.begin();
				for ( ; itRlt < randResult.end(); ++itRlt )
				{
					if ( itRlt->usType == it->usType )
					{ break; }
				}

				if ( itRlt == randResult.end() )
				{ randsNoRepeat.push_back( *it ); }
			}

            if ( !randsNoRepeat.empty() )
            {
                int nSize = randsNoRepeat.size();
                int nIndex = theRand.rand16() % nSize;
                rItem.equipdata.purpleRands[i] = randsNoRepeat[nIndex].usID;
				randResult.push_back( randsNoRepeat[nIndex] );
            }
        }
    }

    return true;
}

short RunTimeData::EquipRandByLevel(short stLevel )
{
    CItemDetail::RandContainer rands;
    GettheItemDetail().GetRandByLevel( stLevel, rands );

    if( rands.empty() )
    { return InvalidLogicNumber; }

    int nIndex = theRand.rand16() % rands.size();
    return rands[nIndex];
}

void RunTimeData::RunUpdate( uint32 dwCurrentTime )
{
    static const uint32 s_dwNoneUpdateSpaceTime = 60000 * 3;        // 3分钟 , 该玩家没有Update, 删除内存( 防止无效的外加还残留在列表中 )

    //static uint32 s_dwLastUpdateTime = 0;
    //if ( !GameTime::IsPassCurrentTime( dwCurrentTime, s_dwLastUpdateTime, 5000 ) )
    //{ return; }
    //s_dwLastUpdateTime = dwCurrentTime;

    //int nUseSize  = theCharacters.GetPlayerUsed();
    //int nUseSizeIndex = 0;
    //for( int i = 0;  i < dr_worldMaxPlayers && nUseSizeIndex < nUseSize ; ++i )
    //{
    //    BaseCharacter* pChar = GetCharacterByID(i);
    //    if( pChar == NULL )
    //    { continue; }

    //    ++nUseSizeIndex;

    //    if ( !pChar->IsPlayer() )
    //    { continue; }

    //    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    //    if ( GameTime::IsPassCurrentTime( dwCurrentTime, pPlayer->GetLastUpdateTime(), s_dwNoneUpdateSpaceTime ) )
    //    {
    //        pPlayer->Log( "Exit By 玩家已经有3分钟没有RunUpdate了!", pPlayer->GetCharName() );
    //        pPlayer->OnExit( NULL );
    //    }
    //}
}

void RunTimeData::UpdateCountryOnLineCount( uint8 uchCountryID, int nCount )
{
    if ( uchCountryID == CountryDefine::Country_Init || uchCountryID >= CountryDefine::Country_Max )
    { return; }

    m_nCountryOnLineCount[ uchCountryID ] += nCount;
    if ( m_nCountryOnLineCount[ uchCountryID ] < 0 )
    { m_nCountryOnLineCount[ uchCountryID ] = 0; }
}

uint8 RunTimeData::CalcRandCreateCountryID()
{
	/*
	 * Author:	2012-8-7 wangshuai
	 * Desc: 	创建角色时暂时将国家设置为0
	 */	

    if ( theRunTimeData.GetWeakCountry() != CountryDefine::Country_Init )
    { return theRunTimeData.GetWeakCountry(); }

    int nMinOnLineCount = 0xFFFFFFF;
    uint8 uchCountryID = 0;

    // 找出最小人数的国家
    for ( int i = 1; i < CountryDefine::Country_Max; ++i )
    {
        if ( m_nCountryOnLineCount[ i ] < nMinOnLineCount )
        {
            nMinOnLineCount = m_nCountryOnLineCount[ i ];
            uchCountryID    = i;
        }
    }

    // 先判断3个国家人数是否相同
    int nSameCount = 1;
    for ( int i = 1; i < CountryDefine::Country_Max; ++i )
    {
        if ( m_nCountryOnLineCount[ i ] == nMinOnLineCount )
        { ++nSameCount; }
    }

    // 3个国家人数一样
    if ( nSameCount == CountryDefine::Country_Max )
    { uchCountryID = ( rand() % CountryDefine::Country_DunHuang ) + 1; }
    
    return uchCountryID;
}

void RunTimeData::EquipScore( SCharItem& rItem, ItemDefine::SItemCommon *pItemDetail )
{
	if (!pItemDetail)
		return;

	if (!pItemDetail->IsCanEquip())
		return;

	ItemDefine::SItemCanEquip* pEquip = ( ItemDefine::SItemCanEquip* )pItemDetail;
	if (pEquip->bFashion)
		return;

	bool bSouled = rItem.IsSoulStamp();
	uint8 nSoulPer = rItem.equipdata.ucSoulPer;

	unsigned char ucLevel = rItem.equipdata.ucLevel;
	float fAttributeMod   = theStarLevelUpConfig.GetItemStarLevelModulus( pEquip->ustEquipType, ucLevel );
	float score = 0.0f;
	rItem.equipdata.fScore = 0.0f;

	if (pEquip->attackPhysics > 0.0f)
	{
		score =  pEquip->attackPhysics * fAttributeMod * theEquipScoreRatioConfig.GetAttrRatio( RT_AddPhysicsAttack - 1 );
		if ( bSouled )
			score += pEquip->attackPhysics * nSoulPer * theEquipScoreRatioConfig.GetAttrRatio( RT_AddPhysicsAttack - 1 ) / 100.0f;
		rItem.equipdata.fScore += score;
	}

	if (pEquip->attackMagic > 0.0f)
	{
		score =  pEquip->attackMagic * fAttributeMod * theEquipScoreRatioConfig.GetAttrRatio( RT_AddMagicAttack - 1 );
		if ( bSouled )
			score += pEquip->attackMagic * nSoulPer * theEquipScoreRatioConfig.GetAttrRatio( RT_AddMagicAttack - 1 ) / 100.0f;
		rItem.equipdata.fScore += score;
	}

	if (pEquip->exact > 0.0f)
	{
		score =  pEquip->exact * fAttributeMod * theEquipScoreRatioConfig.GetAttrRatio( RT_AddExact - 1 );
		if ( bSouled )
			score += pEquip->exact * nSoulPer * theEquipScoreRatioConfig.GetAttrRatio( RT_AddExact - 1 ) / 100.0f;
		rItem.equipdata.fScore += score;
	}

	if (pEquip->dodge > 0.0f)
	{
		score =  pEquip->dodge * fAttributeMod * theEquipScoreRatioConfig.GetAttrRatio( RT_AddDodge - 1 );
		if ( bSouled )
			score += pEquip->dodge * nSoulPer * theEquipScoreRatioConfig.GetAttrRatio( RT_AddDodge - 1 ) / 100.0f;
		rItem.equipdata.fScore += score;
	}

	if (pEquip->critical > 0.0f)
	{
		score =  pEquip->critical * fAttributeMod * theEquipScoreRatioConfig.GetAttrRatio( RT_AddCritical - 1 );
		if ( bSouled )
			score += pEquip->critical * nSoulPer * theEquipScoreRatioConfig.GetAttrRatio( RT_AddCritical - 1 ) / 100.0f;
		rItem.equipdata.fScore += score;
	}

	if (pEquip->tenacity > 0.0f)
	{
		score =  pEquip->tenacity * fAttributeMod * theEquipScoreRatioConfig.GetAttrRatio( RT_AddTenacity - 1 );
		if ( bSouled )
			score += pEquip->tenacity * nSoulPer * theEquipScoreRatioConfig.GetAttrRatio( RT_AddTenacity - 1 ) / 100.0f;
		rItem.equipdata.fScore += score;
	}

	if (pEquip->breakStrike > 0.0f)
	{
		score =  pEquip->breakStrike * fAttributeMod * theEquipScoreRatioConfig.GetAttrRatio( RT_AddBreakStrike - 1 );
		if ( bSouled )
			score += pEquip->breakStrike * nSoulPer * theEquipScoreRatioConfig.GetAttrRatio( RT_AddBreakStrike - 1 ) / 100.0f;
		rItem.equipdata.fScore += score;
	}

	if (pEquip->breakResist > 0.0f)
	{
		score =  pEquip->breakResist * fAttributeMod * theEquipScoreRatioConfig.GetAttrRatio( RT_AddBreakResist - 1 );
		if ( bSouled )
			score += pEquip->breakResist * nSoulPer * theEquipScoreRatioConfig.GetAttrRatio( RT_AddBreakResist - 1 ) / 100.0f;
		rItem.equipdata.fScore += score;
	}

	if (pEquip->stabStrike > 0.0f)
	{
		score =  pEquip->stabStrike * fAttributeMod * theEquipScoreRatioConfig.GetAttrRatio( RT_AddStabStrike - 1 );
		if ( bSouled )
			score += pEquip->stabStrike * nSoulPer * theEquipScoreRatioConfig.GetAttrRatio( RT_AddStabStrike - 1 ) / 100.0f;
		rItem.equipdata.fScore += score;
	}

	if (pEquip->stabResist > 0.0f)
	{
		score =  pEquip->stabResist * fAttributeMod * theEquipScoreRatioConfig.GetAttrRatio( RT_AddStabResist - 1 );
		if ( bSouled )
			score += pEquip->stabResist * nSoulPer * theEquipScoreRatioConfig.GetAttrRatio( RT_AddStabResist - 1 ) / 100.0f;
		rItem.equipdata.fScore += score;
	}

	if (pEquip->elementStrike > 0.0f)
	{
		score =  pEquip->elementStrike * fAttributeMod * theEquipScoreRatioConfig.GetAttrRatio( RT_AddElementStrike - 1 );
		if ( bSouled )
			score += pEquip->elementStrike * nSoulPer * theEquipScoreRatioConfig.GetAttrRatio( RT_AddElementStrike - 1 ) / 100.0f;
		rItem.equipdata.fScore += score;
	}

	if (pEquip->elementResist > 0.0f)
	{
		score =  pEquip->elementResist * fAttributeMod * theEquipScoreRatioConfig.GetAttrRatio( RT_AddElementResist - 1 );
		if ( bSouled )
			score += pEquip->elementResist * nSoulPer * theEquipScoreRatioConfig.GetAttrRatio( RT_AddElementResist - 1 ) / 100.0f;
		rItem.equipdata.fScore += score;
	}

	if (pEquip->toxinStrike > 0.0f)
	{
		score =  pEquip->toxinStrike * fAttributeMod * theEquipScoreRatioConfig.GetAttrRatio( RT_AddToxinStrike - 1 );
		if ( bSouled )
			score += pEquip->toxinStrike * nSoulPer * theEquipScoreRatioConfig.GetAttrRatio( RT_AddToxinStrike - 1 ) / 100.0f;
		rItem.equipdata.fScore += score;
	}

	if (pEquip->toxinResist > 0.0f)
	{
		score =  pEquip->toxinResist * fAttributeMod * theEquipScoreRatioConfig.GetAttrRatio( RT_AddToxinResist - 1 );
		if ( bSouled )
			score += pEquip->toxinResist * nSoulPer * theEquipScoreRatioConfig.GetAttrRatio( RT_AddToxinResist - 1 ) / 100.0f;
		rItem.equipdata.fScore += score;
	}

	if (pEquip->spiritStrike > 0.0f)
	{
		score =  pEquip->spiritStrike * fAttributeMod * theEquipScoreRatioConfig.GetAttrRatio( RT_AddSpiritStrike - 1 );
		if ( bSouled )
			score += pEquip->spiritStrike * nSoulPer * theEquipScoreRatioConfig.GetAttrRatio( RT_AddSpiritStrike - 1 ) / 100.0f;
		rItem.equipdata.fScore += score;
	}

	if (pEquip->spiritResist > 0.0f)
	{
		score =  pEquip->spiritResist * fAttributeMod * theEquipScoreRatioConfig.GetAttrRatio( RT_AddSpiritResist - 1 );
		if ( bSouled )
			score += pEquip->spiritResist * nSoulPer * theEquipScoreRatioConfig.GetAttrRatio( RT_AddSpiritResist - 1 ) / 100.0f;
		rItem.equipdata.fScore += score;
	}

	if( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
	{
		ItemDefine::SItemArmour* pArmour = ( ItemDefine::SItemArmour* )pItemDetail;

		if (pArmour->defendPhysics > 0.0f)
		{
			score =  pArmour->defendPhysics * fAttributeMod * theEquipScoreRatioConfig.GetAttrRatio( RT_AddPhysicsDefend - 1 );
			if ( bSouled )
				score += pArmour->defendPhysics * nSoulPer * theEquipScoreRatioConfig.GetAttrRatio( RT_AddPhysicsDefend - 1 ) / 100.0f;
			rItem.equipdata.fScore += score;
		}

		if (pArmour->defendMagic > 0.0f)
		{
			score =  pArmour->defendMagic * fAttributeMod * theEquipScoreRatioConfig.GetAttrRatio( RT_AddMagicDefend - 1 );
			if ( bSouled )
				score += pArmour->defendMagic * nSoulPer * theEquipScoreRatioConfig.GetAttrRatio( RT_AddMagicDefend - 1 ) / 100.0f;
			rItem.equipdata.fScore += score;
		}

		if (pArmour->Hp > 0)
		{
			score =  pArmour->Hp * fAttributeMod * theEquipScoreRatioConfig.GetAttrRatio( RT_AddHPMax - 1 );
			if ( bSouled )
				score += pArmour->Hp * nSoulPer * theEquipScoreRatioConfig.GetAttrRatio( RT_AddHPMax - 1 ) / 100.0f;
			rItem.equipdata.fScore += score;
		}

		if (pArmour->Mp > 0)
		{
			score =  pArmour->Mp * fAttributeMod * theEquipScoreRatioConfig.GetAttrRatio( RT_AddMPMax - 1 );
			if ( bSouled )
				score += pArmour->Mp * nSoulPer * theEquipScoreRatioConfig.GetAttrRatio( RT_AddMPMax - 1 ) / 100.0f;
			rItem.equipdata.fScore += score;
		}
	}

	// 随机属性
	for( int nloop = 0; nloop < SCharItem::EConstDefine_BaseRandMaxCount; nloop++ )
	{
		ItemDefine::SRandAttribute* pEquipRand = NULL;
		unsigned short usRand = rItem.equipdata.baseRands[nloop];

		if( usRand == InvalidLogicNumber )
			continue;

		pEquipRand = GettheItemDetail().GetRandByID(rItem.equipdata.baseRands[nloop]);

		if (!pEquipRand)
			continue;

		for( int i = 0 ; i < ItemDefine::SRandAttribute::CD_TypeCount ; i++ )
		{
			if( pEquipRand->type[i] == RT_None )
				continue;
			float intensity = GettheItemDetail().GetEquipQualityIntensity(rItem.equipdata.quality);
			float fvalue = pEquipRand->value[i].fValue * intensity;

			score = fvalue * theEquipScoreRatioConfig.GetAttrRatio( pEquipRand->type[i] - 1 );
			rItem.equipdata.fScore += score;
		}
	}

	//紫色随即属性
	for (int nloop = 0; nloop <  SCharItem::EConstDefine_PurpleRandMaxCount; ++nloop)
	{
		ItemDefine::SRandAttribute* pEquipRand = NULL;
		unsigned short usRand = rItem.equipdata.purpleRands[nloop];     
		if ( usRand == InvalidLogicNumber )
			continue;

		pEquipRand = GettheItemDetail().GetRandByID( rItem.equipdata.purpleRands[nloop] );
		if ( !pEquipRand )
			continue;

		for( int i = 0 ; i < ItemDefine::SRandAttribute::CD_TypeCount ; ++ i )
		{
			if( pEquipRand->type[i] == RT_None )
				continue;
			
			float fvalue = pEquipRand->value[i].fValue;

			score = fvalue * theEquipScoreRatioConfig.GetAttrRatio( pEquipRand->type[i] - 1 );
			rItem.equipdata.fScore += score;
		}
	}

	// 宝石属性

	int nHoleCount = rItem.equipdata.gemHoleCount;
	if( nHoleCount <= 0 || nHoleCount > SCharItem::EConstDefine_GemHoleMaxCount )
		return;

	for( int i = 0; i < nHoleCount; ++i )
	{
		int nGemId = rItem.equipdata.gemIds[i];
		ItemDefine::SItemGem* pGem = NULL;
		if( nGemId > 0 )
		{
			pGem = ( ItemDefine::SItemGem* )GettheItemDetail().GetItemByID( nGemId );
		}

		if( pGem )
		{
			for( int j = 0; j < ItemDefine::SItemGem::CD_TypeCount; ++j )
			{
				if( pGem->type[j] == RT_None )
					continue;

				score = pGem->value[j].fValue * theEquipScoreRatioConfig.GetAttrRatio( pGem->type[i] - 1 );
				rItem.equipdata.fScore += score;
			}
		}
	}
}