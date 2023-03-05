#include "ItemDetail.h"
#include "SlkReader.h"
#include "Helper.h"
#include "Official.h"
#include "SystemConfig.h"
#include "ErrorLog.h"
#include "FuncPerformanceLog.h"
#include "ProcessCharInfo.h"
#include "NewWithDebug.h"
#include "XmlStringLanguage.h"
#include "ResourcePath.h"
#include "core/Name.h"
#include "application_config.h"
#include "TitleConfig.h"
#include "packet_interface.h"
//#include "Cipher/cipher_factory.h"
//#include "Launcher/DataLauncher.h"
#include "SplitItemConfig.h"
#include "ErrorCode.h"
#include "tstring.h"
#include "RapidXml/MeRapidXml.h"

#pragma warning( push, 0 )

const char* GetWeaponTypeNamed(int nIdx)
{
	if (nIdx < 0|| nIdx >=eWeaponType_Max)
    { return ""; }

	return ItemDefine::g_szWeaponType[nIdx];
}

uint32 GetEquipTypeByName( const char* pName )
{   
	int iValue = HelperFunc::GetIDByConstString( const_cast<char*>(pName), ItemDefine::g_szEquipType,sizeof(ItemDefine::g_szEquipType)/sizeof(char*) );
    if( -1 == iValue )
    { iValue = 1; }

    uint32 result = 1;
    result <<= iValue;
    return result;
}

const char * FindActionStringByID( const int nID)
{
    for (int i=0; i<sizeof(ItemDefine::str_action) / ( sizeof(char)*32 ); i++)
    {
        if (nID == i)
        {
            return ItemDefine::str_action[i];
        }
    }
    return NULL;
}

int FindActionIdByName( const char* pszName )
{
    for (int i=0; i<sizeof(ItemDefine::str_action) / ( sizeof(char)*32 ); i++)
    {
        if (0 == strcmp(ItemDefine::str_action[i], pszName))
            return i;
    }
    //
    return -1;
}

int GetIDByConstString( const char* szString,char**pszString,int iHowManyString )
{
    strlwr( const_cast<char*>(szString) );
    int iLoop;
    int iBlack = ' ';

    //去掉前面和后面的空格
    char *szFind = NULL;
    while( szFind = (char*)strchr( szString,iBlack ) )
    {
        if( szString == szFind )
            szString ++;
        else
            break;
    }

    szFind = 0;
    //int iLen;
    while( szFind = (char*)strrchr( szString,iBlack  ) )
    {    
        if( 1 == strlen( szFind ) )
        {
            szFind[0] = 0;
        }
        else
            break;
    }

    //
    for( iLoop = 0 ; iLoop < iHowManyString ; iLoop ++)
    {
        if( 0 == stricmp( szString,pszString[iLoop] ) )
            return iLoop;
    }
    return -1;
}

BYTE* CItemDetail::GetAddrPointer( DWORD dwAddr )
{
    if( m_pbyGlobalBuffer == NULL )
    {
        // ToLog( false );
        return NULL;
    }
    if( dwAddr >= m_dwGlobalBufferSize ||
        dwAddr >= m_dwGlobalBufferUsed )
    {
        // ToLog( false );
        return NULL;
    }
    return &m_pbyGlobalBuffer[dwAddr];
}
const char* CItemDetail::GetString( DWORD dwAddr )
{
    BYTE* pbyPointer = GetAddrPointer(dwAddr);
    if( pbyPointer )
        return (const char*)pbyPointer;
    //return (const char*)GetAddrPointer(dwAddr);
    return "";
}
BOOL CItemDetail::AllocStringCopy( const char* pszString )
{
    if( !pszString )
    {
        // ToLog( false );
        return FALSE;
    }

    int nLength = strlen( pszString )+1;
    DWORD dwAddr = AllocGlobalBuffer( nLength );
    HelperFunc::SafeNCpy( (char*)GetAddrPointer(dwAddr), pszString, nLength );
    return dwAddr;
}


const char* CItemDetail::GetStringByDword(DWORD dwName)
{
    return GettheItemDetail().GetString(dwName);
}


CItemDetail::CItemDetail():
m_pbyGlobalBuffer(NULL),
m_dwGlobalBufferSize(0),
m_dwGlobalBufferUsed(0),
m_vectorLevelItem("[ItemDetail.h]CItemDetail.m_vectorLevelItem"),
m_SkillArray("[ItemDetail.h]CItemDetail.m_SkillArray"),
m_StatusArray("[ItemDetail.h]CItemDetail.m_StatusArray")
//m_WeaponArray("[ItemDetail.h]CItemDetail.m_WeaponArray")
{
    //m_bClientMode = true;
    //m_pMemAllocer = &g_normalAllocer;
    //m_vectorItem.resize(10000);
    //m_vectorGems[ gem_ruby ].resize( 5 );
    //m_vectorGems[ gem_beryl ].resize( 5 );
    //m_vectorGems[ gem_sapphire ].resize( 5 );
    //m_vectorGems[ gem_diamond ].resize( 5 );

    //AllocGlobalBuffer( 1024 );
    m_dwGlobalBufferSize = 1024*1024*36;
    m_pbyGlobalBuffer = CNewWithDebug<BYTE>::Alloc(m_dwGlobalBufferSize, "CItemDetail构造申请内存");
    memset( m_pbyGlobalBuffer, 0x00, m_dwGlobalBufferSize );

    m_ItemFinder.SupportSameNameElement( TRUE );
}

CItemDetail::~CItemDetail()
{
    int iLoop;

    //for(int i=0;i<(int)m_BakupItem.size();i++)
    //{
    //    delete m_BakupItem[i];
    //}
    if( m_pbyGlobalBuffer )
    {
        CNewWithDebug<BYTE>::Free(m_pbyGlobalBuffer);
        //         delete[] m_pbyGlobalBuffer;
        m_pbyGlobalBuffer = NULL;
    }

    ////vectoritem
    //for( iLoop=0; iLoop< (int)m_vectorItem.size( ); iLoop++ )
    //{
    //    if( m_vectorItem[iLoop] != NULL )
    //    {
    //        Safe_DeleteArray(m_vectorItem[iLoop]->pszIconInItembag);
    //        Safe_DeleteArray(m_vectorItem[iLoop]->pszItemDesc);
    //        Safe_DeleteArray(m_vectorItem[iLoop]->pszItemName);
    //        delete m_vectorItem[iLoop];
    //        m_vectorItem[iLoop] = NULL;
    //    }
    //}

    //charmodulus
    //for( iLoop=0; iLoop<(int)m_vecCharModulus.size( ); iLoop++ )
    //{
    //    if( m_vecCharModulus[iLoop] != NULL )
    //    {
    //        //delete m_vecCharModulus[iLoop];
    //        m_vecCharModulus[iLoop] = NULL;
    //    }
    //}

    //StoneSkill
    //iterStoneSkill stoneskill;
    //stoneskill = m_mapStoneSkill.begin( );
    //for( ;stoneskill!=m_mapStoneSkill.end( ); stoneskill++ )
    //{
    //    if( stoneskill->second != NULL )
    //    {
    //        delete stoneskill->second;
    //        stoneskill->second = NULL;
    //    }
    //}

    //SkillToSkill
    //iterSkillToSkill skilltoskill;
    //skilltoskill = m_mapSkillToSkill.begin( );
    //for( ;skilltoskill!=m_mapSkillToSkill.end( ); skilltoskill++ )
    //{
    //    if( skilltoskill->second != NULL )
    //    {
    //        delete skilltoskill->second;
    //        skilltoskill->second = NULL;
    //    }
    //}

    //Produce Item
    //for( iLoop=0; iLoop<(int)m_vecProduceItem.size( ); iLoop++ )
    //{
    //    if( m_vecProduceItem[iLoop] != NULL )
    //    {
    //        delete m_vecProduceItem[iLoop];
    //        m_vecProduceItem[iLoop] = NULL;
    //    }
    //}
}

DWORD CItemDetail::AllocGlobalBuffer( DWORD dwBufferSize )
{
    if( m_dwGlobalBufferUsed+dwBufferSize > m_dwGlobalBufferSize )
    {
        // ToLog( false );
        return 0;
    }

    BYTE* pbyAllocBuffer = &m_pbyGlobalBuffer[m_dwGlobalBufferUsed];
    DWORD dwAddr = m_dwGlobalBufferUsed;
    m_dwGlobalBufferUsed += dwBufferSize;
    return dwAddr;
}
BYTE* CItemDetail::AllocItem( DWORD dwItemType, DWORD dwSize )
{
    if( dwSize == 0 )
    {
        // ToLog( false );
    }

    DWORD dwAddr = AllocGlobalBuffer( dwSize );
    return GetAddrPointer( dwAddr );
    //return AllocGlobalBuffer( dwSize );
    //return NULL;
}

bool CItemDetail::GetIntField( CSlkReader *pReader,const char * szColName,int &iValue )
{
    return pReader->GetIntFieldByName( szColName,iValue );
}

bool CItemDetail::GetFloatField( CSlkReader *pReader,const char * szColName, float &fValue )
{
    return pReader->GetFloatFieldByName( szColName, fValue );
}

bool CItemDetail::GetStringField( CSlkReader *pReader,const char * szColName,std::string& strRetValue )
{    
    return pReader->GetStringFieldByName( szColName,strRetValue);
}

int GetItemTypeByString( const char *szStrItemType )
{
    int i;
    for( i = 0 ; i < ItemDefine::ITEMTYPE_MAX ; i ++ )
    {
		if( 0 != strstr( szStrItemType, ItemDefine::g_szItemType[i] ) )
            return i;
    }
    return -1;
}

int GetBagTypeByItemType( int nItemType )
{
    switch( nItemType )
    {
    case ItemDefine::ITEMTYPE_SKILL:
    case ItemDefine::ITEMTYPE_STATUS:    
    case ItemDefine::ITEMTYPE_ACTION:
        {
            return -1;
        }
        break;
    case ItemDefine::ITEMTYPE_TASK:
        {
            return BT_TaskBag;
        }
        break;
    case ItemDefine::ITEMTYPE_MATERIAL:
    case ItemDefine::ITEMTYPE_GEM:
        {
            return BT_MaterialBag;
        }
    case ItemDefine::ITEMTYPE_RESTORE:
    case ItemDefine::ITEMTYPE_WEAPON:
    case ItemDefine::ITEMTYPE_ARMOUR:
    case ItemDefine::ITEMTYPE_CREATEITEMRULE:
    case ItemDefine::ITEMTYPE_OTHER:
    case ItemDefine::ITEMTYPE_REEL:
    case ItemDefine::ITEMTYPE_TREASUREBOX:
    case ItemDefine::ITEMTYPE_CHECKUP:
    case ItemDefine::ITEMTYPE_REALAWARD:
    case ItemDefine::ITEMTYPE_GUILD:
    case ItemDefine::ITEMTYPE_SPECIAL:
    case ItemDefine::ITEMTYPE_TALISMAN:
	case ItemDefine::ITEMTYPE_PETEQUIP:
        {
            return BT_NormalItemBag;
        }
        break;
    default:
        return -1;
    }
}

bool CItemDetail::AddItemConfig(const char *szFileName)
{
    CSlkReader slkItem;
    OutputSlkLoadingMessage( "正在分析%s\r\n",szFileName );
    if( !slkItem.ReadFromFile( szFileName ) )
    {        
        OutputSlkLoadingMessage( "找不到%s文件\r\n",szFileName);
        return false;
    }

    int offset = 3;
    int iRet;

    int iValue = 0;
    float fValue = 0.0f;
    char* pszItemType = 0;
    std::string strTemp;

    DWORD dwTime = HQ_TimeGetTime();

    while ( CSlkReader::ret_readover != ( iRet = slkItem.GotoNextLine( offset++ ) ) ) 
    {   
        if( CSlkReader::ret_nothisline == iRet )
        {
            continue;
        }

        // 查找道具类型
        int nItemType = -1;
        strTemp = "";
        if( !slkItem.GetStringFieldByName( "ItemType", strTemp ) )
        { // 物品类型
            OutputSlkLoadingMessage("[%s] 行号:%d 未填写 ItemType列", szFileName,offset);
            GetErrorLog()->logString("[%s] 行号:%d 未填写 ItemType列", szFileName,offset );
            continue;
            //return false;
        }

        nItemType = GetItemTypeByString( strTemp.c_str());
        if( nItemType < 0 || nItemType >=ItemDefine::ITEMTYPE_MAX )
        {
            OutputSlkLoadingMessage( "[%s] 行号:%d ItemType列 数据错误 ！", szFileName,offset );
            GetErrorLog()->logString( "[%s] 行号:%d ItemType列 数据错误 ！", szFileName,offset );
            return false;
        }

        ItemDefine::SItemCommon* pItemCommon = NULL;

        //根据类型分配对象内存
        switch( nItemType) 
        {
        case ItemDefine::ITEMTYPE_RESTORE:
            pItemCommon = (ItemDefine::SItemRestore*)AllocItem( 0, sizeof( ItemDefine::SItemRestore ) );
            break;
        case ItemDefine::ITEMTYPE_WEAPON:
            pItemCommon = (ItemDefine::SItemWeapon*)AllocItem( 0, sizeof( ItemDefine::SItemWeapon ) );
            break;
        case ItemDefine::ITEMTYPE_ARMOUR:
            pItemCommon = (ItemDefine::SItemArmour*)AllocItem( 0, sizeof( ItemDefine::SItemArmour ) );
            break;
        case ItemDefine::ITEMTYPE_SKILL:
            pItemCommon = (ItemDefine::SItemSkill*)AllocItem( 0, sizeof( ItemDefine::SItemSkill ) );
            break;
        case ItemDefine::ITEMTYPE_STATUS:
            pItemCommon = (ItemDefine::SItemStatus*)AllocItem( 0, sizeof( ItemDefine::SItemStatus ) );
            break;
        case ItemDefine::ITEMTYPE_ACTION:
            pItemCommon = (ItemDefine::SItemAction*)AllocItem( 0, sizeof( ItemDefine::SItemAction ) );
            break;
        case ItemDefine::ITEMTYPE_MATERIAL:
            pItemCommon = (ItemDefine::SCreateMaterial*)AllocItem( 0, sizeof( ItemDefine::SCreateMaterial ) );
            break;
        case ItemDefine::ITEMTYPE_GEM:
            pItemCommon = (ItemDefine::SItemGem*)AllocItem( 0, sizeof( ItemDefine::SItemGem ) );
            break;
        case ItemDefine::ITEMTYPE_CREATEITEMRULE:
            pItemCommon = (ItemDefine::SItemCreateItemRule*)AllocItem( 0, sizeof( ItemDefine::SItemCreateItemRule ) );
            break;
        case ItemDefine::ITEMTYPE_TASK:
            pItemCommon = (ItemDefine::SItemTask*)AllocItem( 0, sizeof( ItemDefine::SItemTask ) );
            break;
        case ItemDefine::ITEMTYPE_OTHER:
            pItemCommon = (ItemDefine::SItemOther*)AllocItem( 0, sizeof( ItemDefine::SItemOther ) );
            break;
        case ItemDefine::ITEMTYPE_REEL:
            pItemCommon = (ItemDefine::SItemReel*)AllocItem( 0, sizeof( ItemDefine::SItemReel ) );
            break;
        case ItemDefine::ITEMTYPE_TREASUREBOX:
            pItemCommon = (ItemDefine::SItemTreasureBox*)AllocItem( 0, sizeof( ItemDefine::SItemTreasureBox ) );
            break;
        case ItemDefine::ITEMTYPE_CHECKUP:
            pItemCommon = (ItemDefine::SItemCheckUp*)AllocItem( 0, sizeof( ItemDefine::SItemCheckUp ) );
            break;
        case ItemDefine::ITEMTYPE_REALAWARD:
            pItemCommon = (ItemDefine::SItemRealAward*)AllocItem( 0, sizeof( ItemDefine::SItemRealAward ) );
            break;
        case ItemDefine::ITEMTYPE_GUILD:
            pItemCommon = (ItemDefine::SItemGuild*)AllocItem( 0, sizeof( ItemDefine::SItemGuild ) );
            break;
        case ItemDefine::ITEMTYPE_SPECIAL:
            pItemCommon = (ItemDefine::SItemSpecial*)AllocItem( 0, sizeof( ItemDefine::SItemSpecial ) );
            break;
        case ItemDefine::ITEMTYPE_TALISMAN:
            pItemCommon = (ItemDefine::SItemTalisman*)AllocItem( 0, sizeof( ItemDefine::SItemTalisman ) );
            break;
		case ItemDefine::ITEMTYPE_PETEQUIP:
			pItemCommon = (ItemDefine::SItemPetEquip*)AllocItem( 0, sizeof( ItemDefine::SItemPetEquip ) );
			break;
            //case ITEMTYPE_CARD:
            //    AddCardItem(&slkChildItem[common.ucItemType],common);
            //    break;
            //case ITEMTYPE_CRYSTAL:
            //    AddCrystalItem(&slkChildItem[common.ucItemType],common);
            //    break;

        default:
            pItemCommon = (ItemDefine::SItemCommon*)AllocItem( 0, sizeof( ItemDefine::SItemCommon ) );
            break;
        }

        if( !pItemCommon )
        {
            OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
            GetErrorLog()->logString( "Item.slk中内存分配出错" );
            return false;    
        }


        pItemCommon->ucItemType = nItemType;
        pItemCommon->cItemClass = ItemDefine::ItemClass_Normal;

        //道具ID        
        if( !slkItem.GetIntFieldByName( "ID", iValue ) )
            continue;
        pItemCommon->ustItemID = iValue;

        std::string strItemName;
        if( !slkItem.GetStringFieldByName( "ItemName", strItemName ) )
        {
            OutputSlkLoadingMessage("未填写 [%s] ItemId[%d] ItemName列", szFileName, pItemCommon->ustItemID);
            continue;
        }

        OutputSlkLoadingMessage( "Load Item(%s)", strItemName.c_str() );
        pItemCommon->dwItemNameAddr = AllocStringCopy( strItemName.c_str() );

        std::string strItemDesc;
        if( !slkItem.GetStringFieldByName( "Description", strItemDesc ) )
        {
        }
        pItemCommon->dwItemDescAddr = AllocStringCopy( strItemDesc.c_str() );

        if( slkItem.GetIntFieldByName( "UseTime", iValue ) )
        {// 以小时为单位
            pItemCommon->nUseTime = iValue;
        }
        else
        {            
            pItemCommon->nUseTime = -1;
            OutputSlkLoadingMessage("未填写 [%s] ItemId[%d] UseTime列 请填写默认[-1]", szFileName, pItemCommon->ustItemID);
        }

        if( slkItem.GetIntFieldByName( "Bill", iValue ) )
        {// 以小时为单位
            pItemCommon->nBill = iValue;
        }
        else
        {
            pItemCommon->nBill = 0;
            OutputSlkLoadingMessage("未填写 [%s] ItemId[%d] Bill列 请填写默认[0]", szFileName, pItemCommon->ustItemID);
        }

        if( !slkItem.GetIntFieldByName( "Cost", iValue  ) ) 
        { // 价值
            OutputSlkLoadingMessage("未填写 [%s] ItemId[%d] Cost列", szFileName, pItemCommon->ustItemID);
        }
        pItemCommon->dwCost = iValue;

        if( !slkItem.GetIntFieldByName( "CostType", iValue  ) ) 
        { // 价值类型
            OutputSlkLoadingMessage("未填写 [%s] ItemId[%d] CostType列", szFileName, pItemCommon->ustItemID);
        }
        pItemCommon->costType = iValue;

        if( !slkItem.GetIntFieldByName( "CostItemID", iValue  ) ) 
        { // 价值类型
            OutputSlkLoadingMessage("未填写 [%s] ItemId[%d] CostItemID列", szFileName, pItemCommon->ustItemID);
        }
        pItemCommon->costItemID = iValue;

        if( !slkItem.GetIntFieldByName( "SpecialCost", iValue  ) ) 
        { // 价值
            OutputSlkLoadingMessage("未填写 [%s] ItemId[%d] SpecialCost列", szFileName, pItemCommon->ustItemID);
        }
        pItemCommon->dwSpecialCost = iValue;

        if( !slkItem.GetIntFieldByName( "Quality", iValue  ) )
        { // 品质等级
            OutputSlkLoadingMessage("未填写 [%s] ItemId[%d] Quality列", szFileName, pItemCommon->ustItemID);
        }
        pItemCommon->ustLevel = iValue;

        std::string strIconInItemBag;        
        if( !slkItem.GetStringFieldByName( "IconFile", strIconInItemBag ) )
        {
            OutputSlkLoadingMessage( "未填写 [%s] ItemId[%d] IconFile列", szFileName, pItemCommon->ustItemID );
        }
        pItemCommon->dwIconInItemBagAddr = AllocStringCopy( strIconInItemBag.c_str() );

        if( !slkItem.GetIntFieldByName( "DropItemModel", iValue ) )
        { // 掉落物品的模型
            OutputSlkLoadingMessage( "未填写 [%s] ItemId[%d] DropItemModel列", szFileName, pItemCommon->ustItemID );
        }
        pItemCommon->ustModelIDOverGround = iValue;

        if( slkItem.GetIntFieldByName( "Rare", iValue ) )
        { // 稀有度
            pItemCommon->cItemClass = iValue;
        }
        else
        {
            pItemCommon->cItemClass = ItemDefine::ItemClass_Normal;
        }

        if( slkItem.GetIntFieldByName( "IfShowEqipEffect", iValue ) )
        { // 是否显示装备特效
            iValue = 1;
        }
        pItemCommon->bShowEquipEffect = iValue>0?true:false;


        if (slkItem.GetIntFieldByName("CanMoved",iValue)) 
        { // 可否被移动
            pItemCommon->bIsCanMove = iValue>0?true:false;
        }
        else
        {
            pItemCommon->bIsCanMove = false;
            OutputSlkLoadingMessage( "未填写 [%s] ItemId[%d] CanMoved列", szFileName, pItemCommon->ustItemID );
        }        

        if (slkItem.GetIntFieldByName("CanDroped",iValue))
        { // 可否丢弃
            pItemCommon->bIsCanDrop = iValue>0?true:false;
        }

        if(slkItem.GetIntFieldByName("CanDeleted", iValue))
        { // 可否销毁
            pItemCommon->bIsCanDestory = iValue > 0 ? true : false;
        }
        else
        {
            pItemCommon->bIsCanDestory = false;
            OutputSlkLoadingMessage( "未填写 [%s] ItemId[%d] CanDeleted列", szFileName, pItemCommon->ustItemID );
        }

        if(slkItem.GetIntFieldByName("CanTrade", iValue))    //可否交易
        { // 可否交易
            pItemCommon->bIsCanTrade = iValue > 0 ? true : false;
        }
        else
        {
            pItemCommon->bIsCanTrade = true;
            OutputSlkLoadingMessage( "未填写 [%s] ItemId[%d] CanTrade列", szFileName, pItemCommon->ustItemID );
        }

        if (slkItem.GetIntFieldByName("CanSold",iValue))    //可否买卖
        { // 可否买卖
            pItemCommon->bIsCanSellShop = iValue>0?true:false;
        }
        else
        {
            pItemCommon->bIsCanSellShop = false;
            OutputSlkLoadingMessage( "未填写 [%s] ItemId[%d] CanSold列", szFileName, pItemCommon->ustItemID );
        }

        if (slkItem.GetIntFieldByName("CanStored",iValue))    //可否放入仓库
        { // 可否放入仓库
            pItemCommon->bIsCanPushInStorage = iValue>0?true:false;
        }
        else
        {
            pItemCommon->bIsCanPushInStorage = false;
            OutputSlkLoadingMessage( "未填写 [%s] ItemId[%d] CanStored列", szFileName, pItemCommon->ustItemID );
        }

        if (slkItem.GetIntFieldByName("CanLocked",iValue))
        { // 可否加锁
            pItemCommon->bIsCanLocked = iValue>0?true:false;
        }
        else
        {
            pItemCommon->bIsCanLocked = false;
            OutputSlkLoadingMessage( "item.slk中[可否加锁]字段未填写,默认不可以加锁!" );
        }

        //if ( !GetIntField(&slkItem, iCol++, iValue) )
        //{ // 占格宽
        //    iValue = 1;
        //}

        //if ( !GetIntField(&slkItem, iCol++, iValue) )
        //{ // 占杭高
        //    iValue = 1;
        //}

        if( !slkItem.GetIntFieldByName( "HoldGridWidth", iValue ) )
        {
            iValue = 1;
        }
        pItemCommon->ustItemW = iValue;

        if( !slkItem.GetIntFieldByName( "HoldGridHeight", iValue ) )
        {
            iValue = 1;
        }
        pItemCommon->ustItemH = iValue;


        //吟唱特效目录
        strTemp.clear();
        if (!slkItem.GetStringFieldByName("CastEffectPath",strTemp))
        {
        }
        pItemCommon->dwSingEffect = AllocStringCopy(strTemp.c_str());

        //释放特效目录
        strTemp.clear();
        if (!slkItem.GetStringFieldByName("FireEffectPath",strTemp))
        {
        }
        pItemCommon->dwAssoilEffect = AllocStringCopy(strTemp.c_str());

        //命中特效目录
        strTemp.clear();
        if (!slkItem.GetStringFieldByName("HitEffectPath",strTemp))
        {
        }
        pItemCommon->dwHurtEffect = AllocStringCopy(strTemp.c_str());

        // IConId
        if (!slkItem.GetIntFieldByName("iconID",iValue))
        {
        }
        pItemCommon->ustIconId = iValue;

        if (!slkItem.GetFloatFieldByName("Weight",fValue))
        { // 重量
            //// ToLog(false);
        }
        pItemCommon->fWeight = fValue;


        std::string strSound;
        if( !slkItem.GetStringFieldByName( "UsingItemSound", strSound ) )
        { // 声音
        }
        pItemCommon->dwIconSoundAddr = AllocStringCopy( strSound.c_str() );

        // 使用物品吟唱时间
        if( slkItem.GetIntFieldByName( "UseSingTime", iValue ) )
        {
            pItemCommon->dwUseSingTime = iValue;
        }

        if( slkItem.GetIntFieldByName( "CanSingingInterrupt", iValue ) )
        {
            pItemCommon->bCanSingingInterrupt = iValue;
        }

        // 物品使用目标
        if( slkItem.GetIntFieldByName( "UserTarget", iValue ) )
        {
            pItemCommon->byUserTarget = iValue;
        }

        if (!slkItem.GetIntFieldByName("CanBound",iValue))
        { // 绑定
        }
        pItemCommon->bIsCanBound = iValue;

        if (!slkItem.GetIntFieldByName("CanSplit",iValue))
        { // 拆分
            //// ToLog(false);
        }
        pItemCommon->bIsCanSplit = iValue;

        if (slkItem.GetIntFieldByName("DropControlCount",iValue) )
        { // 掉落阈值
            pItemCommon->nDropControlCount = iValue;
        }

        if ( slkItem.GetIntFieldByName("ClearControlCount",iValue) )
        { // 是否清楚掉落阈值
            pItemCommon->bIsClearControlCount = iValue;
        }

        if ( slkItem.GetIntFieldByName("DropMaxCount",iValue) )
        { // 掉落阈值
            pItemCommon->nDropMaxCount = iValue;
        }

        if ( slkItem.GetIntFieldByName("StackNum",iValue) )
        { // 可叠加数量
            pItemCommon->nStackNum = iValue;
        }

        AddItemToContainer(pItemCommon);
    }

    return true;
}

bool CItemDetail::LoadSlkItemDetail( const char *szPath, FILE* fpOutput )
{
    char *(szItemFile[])=
    {
        "Item.slk"          ,
        "Restore.slk"       ,
        "Weapon.slk"        ,
        "Armour.slk"        ,
        "Skill.slk"         ,
        "Status.slk"        ,
        "GameAction.slk"    ,
        "Material.slk"      ,
        "Gem.slk"           ,
        //"CreateItemRule.slk",  ?
        //"Task.slk"          ,  ?
        "Reel.slk"          ,
        "TreasureBox.slk"   ,
        "CheckUp.slk"       ,
        //"RealAward.slk"     ,  ?
        "GuildItem.slk"     ,
        "SpecialItem.slk"   ,
        "Talisman.slk"      ,
        "Other.slk"         ,
		"PetEquip.slk"		,
    };


    static bool bInstance = false;

    // ToLog( !bOnlyOne );
    // 函数目前设计为只能被调用一次
    if( bInstance )
    {
        return false;
    }

    bInstance = true;

    bool bRight = false;

    char szFile[ MAX_PATH ] = {0};

    _snprintf( szFile, sizeof(szFile)-1, "%s\\%s", szPath, szItemFile[0] );
    bRight = AddItemConfig(szFile);

    if (!bRight)
    {
        return false;
    }

    _snprintf( szFile, sizeof(szFile)-1, "%s\\%s", szPath, szItemFile[1] );
    bRight = AddRestoreItem    ( szFile ); // 恢复药品

    if (!bRight)
    {
        return false;
    }

    _snprintf( szFile, sizeof(szFile)-1, "%s\\%s", szPath, szItemFile[2] );
    bRight = AddWeaponItem     ( szFile ); // 武器

    if (!bRight)
    {
        return false;
    }

    _snprintf( szFile, sizeof(szFile)-1, "%s\\%s", szPath, szItemFile[3] );
    bRight = AddArmourItem     ( szFile ); // 防具

    if (!bRight)
    {
        return false;
    }

    _snprintf( szFile, sizeof(szFile)-1, "%s\\%s", szPath, szItemFile[4] );
    bRight = AddSkillItem      ( szFile ); // 技能.

    if (!bRight)
    {
        return false;
    }

    _snprintf( szFile, sizeof(szFile)-1, "%s\\%s", szPath, szItemFile[5] );
    bRight = AddStatusItem     ( szFile ); // 状态

    if (!bRight)
    {
        return false;
    }

    _snprintf( szFile, sizeof(szFile)-1, "%s\\%s", szPath, szItemFile[6] );
    bRight = AddActionItem     ( szFile ); // 基本动作

    if (!bRight)
    {
        return false;
    }

    _snprintf( szFile, sizeof(szFile)-1, "%s\\%s", szPath, szItemFile[7] );
    bRight = AddMaterialItem   ( szFile ); // 原料

    if (!bRight)
    {
        return false;
    }

    _snprintf( szFile, sizeof(szFile)-1, "%s\\%s", szPath, szItemFile[8] );
    bRight = AddGemItem        ( szFile ); // 宝石

    if (!bRight)
    {
        return false;
    }

    _snprintf( szFile, sizeof(szFile)-1, "%s\\%s", szPath, szItemFile[9] );
    bRight = AddReelItem       ( szFile ); // 卷轴

    if (!bRight)
    {
        return false;
    }

    _snprintf( szFile, sizeof(szFile)-1, "%s\\%s", szPath, szItemFile[10] );
    bRight = AddTreasureBoxItem( szFile ); // 宝箱

    if (!bRight)
    {
        return false;
    }

    _snprintf( szFile, sizeof(szFile)-1, "%s\\%s", szPath, szItemFile[11] );
    bRight = AddCheckUpItem    ( szFile ); // 鉴定或者其他的一些物品

    if (!bRight)
    {
        return false;
    }

    _snprintf( szFile, sizeof(szFile)-1, "%s\\%s", szPath, szItemFile[12] );
    bRight = AddGuildBoxItem   ( szFile );

    if (!bRight)
    {
        return false;
    }

    _snprintf( szFile, sizeof(szFile)-1, "%s\\%s", szPath, szItemFile[13] );
    bRight = AddSpecialItem    ( szFile );

    if (!bRight)
    {
        return false;
    }

    _snprintf( szFile, sizeof(szFile)-1, "%s\\%s", szPath, szItemFile[14] );
    bRight = AddTalismanItem     ( szFile );

    if (!bRight)
    {
        return false;
    }

    _snprintf( szFile, sizeof(szFile)-1, "%s\\%s", szPath, szItemFile[15] );
    bRight = AddOtherItem    ( szFile );

	if (!bRight)
    {
        return false;
    }

	_snprintf( szFile, sizeof(szFile)-1, "%s\\%s", szPath, szItemFile[16] );
    bRight = AddPetEquipItem    ( szFile ); // 副将装备

    

    if (!bRight)
    {
        return false;
    }

    if (!bRight)
    {
        return false;
    }


    return true;
}

BOOL CItemDetail::LoadBinFile( const char* pszFilename ) // 二进制加载
{
    f_Handle* fp = NULL;

// #ifdef DATA_LAUNCHER
//     if (g_DirectReadInPackage)
//     {
//         // 		fp = Cipher::CipherFactory::OpenCipherFile(pszFilename);
//         fp = fopen( pszFilename, "rb" );
//         if( !fp )
//         {
//             return FALSE;
//         }
//     }
//     else
// #endif
    {
        fp = packet_namespace::w_fopen( pszFilename, "rb" );
        if( !fp )
        {
            // 			fp = Cipher::CipherFactory::OpenCipherFile(pszFilename);
            // 			if( !fp )
            // 			{
            return FALSE;
            // 			}
        }
    }
    // 版本号
    unsigned long majoy = 0,mirror = 0,buid = 0 ,Revision = 0;
    packet_namespace::w_fread( &majoy, sizeof(unsigned long), 1, fp );
    packet_namespace::w_fread( &mirror, sizeof(unsigned long), 1, fp );
    packet_namespace::w_fread( &buid, sizeof(unsigned long), 1, fp );
    packet_namespace::w_fread( &Revision, sizeof(unsigned long), 1, fp );

    if (majoy != ApplicationConfig::Instance().GetMajorVersion()
        ||mirror != ApplicationConfig::Instance().GetMinorVersion()
        ||buid != ApplicationConfig::Instance().GetBuildVersion())
    {
        packet_namespace::w_fclose( fp );
        return FALSE;
    }

    // 道具
    int nItemCount = 0;
    packet_namespace::w_fread( &nItemCount, sizeof(int), 1, fp );
    std::vector<int> vectorItemAddr;
    if( nItemCount > 0 )
    {
        vectorItemAddr.reserve( nItemCount );
        vectorItemAddr.resize( nItemCount );
        packet_namespace::w_fread( &vectorItemAddr[0], sizeof(int)*nItemCount, 1, fp );
    }

    // 怪物
    int nMonsterCount = 0;
    packet_namespace::w_fread( &nMonsterCount, sizeof(int), 1, fp );
    std::vector<DWORD> MonsterAddr;
    if ( nMonsterCount > 0 )
    {
        MonsterAddr.resize( nMonsterCount );
        packet_namespace::w_fread( &MonsterAddr[0], sizeof(DWORD)*nMonsterCount, 1, fp );
    }

    // 宠物
    int nPetMonsterCount = 0;
    packet_namespace::w_fread( &nPetMonsterCount, sizeof(int), 1, fp );
    std::vector<DWORD> PetMonsterAddr;
    if ( nPetMonsterCount > 0 )
    {
        PetMonsterAddr.resize( nPetMonsterCount );
        packet_namespace::w_fread( &PetMonsterAddr[0], sizeof(DWORD)*nPetMonsterCount, 1, fp );
    }

    // 怪物声音
    int nMonsterSoundCount = 0;
    packet_namespace::w_fread( &nMonsterSoundCount, sizeof(int), 1, fp );
    std::vector<DWORD> MonsterSoundAddr;
    if ( nMonsterSoundCount > 0 )
    {
        MonsterSoundAddr.resize( nMonsterSoundCount );
        packet_namespace::w_fread( &MonsterSoundAddr[0], sizeof(DWORD)*nMonsterSoundCount, 1, fp );
    }

    // 坐骑
    int nMountCount = 0;
    packet_namespace::w_fread( &nMountCount, sizeof(int), 1, fp );
    std::vector<DWORD> MountAddr;
    if ( nMountCount > 0 )
    {
        MountAddr.resize( nMountCount );
        packet_namespace::w_fread( &MountAddr[0], sizeof(DWORD)*nMountCount, 1, fp );
    }

    // 随机
    int nRandCount = 0;
    packet_namespace::w_fread( &nRandCount, sizeof(int), 1, fp );
    std::vector<DWORD> RandAddr;
    if ( nRandCount > 0 )
    {
        RandAddr.resize( nRandCount );
        packet_namespace::w_fread( &RandAddr[0], sizeof(DWORD)*nRandCount, 1, fp );
    }

    // 全局buffer的大小
    packet_namespace::w_fread( &m_dwGlobalBufferUsed, sizeof(DWORD), 1, fp );
    if( m_dwGlobalBufferUsed > 0 )
    {
        packet_namespace::w_fread( m_pbyGlobalBuffer, m_dwGlobalBufferUsed*sizeof(BYTE), 1, fp );
    }
    packet_namespace::w_fclose( fp );

    // 分析 道具
    for( int nItem = 0; nItem < nItemCount; ++nItem )
    {
        ItemDefine::SItemCommon* pItem = (ItemDefine::SItemCommon*)&m_pbyGlobalBuffer[vectorItemAddr[nItem]];

        //配方读取要特殊处理
        if (pItem->ucItemType == ItemDefine::ITEMTYPE_CREATEITEMRULE)
        {
            ItemDefine::SItemCreateItemRule* pItemRule = (ItemDefine::SItemCreateItemRule *)pItem;
            short stTargetID        = pItemRule->ustTargetItemID;
            short stTargetID1       = pItemRule->ustTargetItemID1;
            short stTargetID2       = pItemRule->ustTargetItemID2;
            pItemRule->pItemTarget  = GetItemByID(stTargetID);
            pItemRule->pItemTarget1 = GetItemByID(stTargetID1);
            pItemRule->pItemTarget2 = GetItemByID(stTargetID2);

            if (pItemRule->iMaterialNum > pItemRule->material.GetSize())
            {   
                continue;
            }

            for (int iloop = 0; iloop < pItemRule->iMaterialNum; iloop++)
            {
                short stMaterialID;
                stMaterialID = pItemRule->material[iloop].ustItemID;
            }
            AddItemToContainer(pItem);
        }
        else
        { 
            AddItemToContainer( pItem ); 
        }

        int nType = pItem->ucItemType;
        switch(nType)
        {
        case ItemDefine::ITEMTYPE_RESTORE:
            {
                ItemDefine::SItemRestore* pRestore = (ItemDefine::SItemRestore*)pItem;
                m_vecRestoreItem.push_back( pRestore );
            }
            break;
        case ItemDefine::ITEMTYPE_WEAPON:
            {
                ItemDefine::SItemWeapon* pWeapon = (ItemDefine::SItemWeapon*)pItem;
                //添加到套装map
                if( pWeapon->sSuitID != 0 && pWeapon->sSuitID != -1 )
                {			
                    m_mapSuit[pWeapon->sSuitID].push_back( pWeapon );
                }
            }
            break;
        case ItemDefine::ITEMTYPE_ARMOUR:
            {
                ItemDefine::SItemArmour* pArmour = (ItemDefine::SItemArmour*)pItem;
                //添加到套装map
                if( pArmour->sSuitID != 0 && pArmour->sSuitID != -1 )
                {			
                    m_mapSuit[pArmour->sSuitID].push_back( pArmour );
                }
            }
            break;
        case ItemDefine::ITEMTYPE_SKILL:
            { // 建立一个技能物品ID到技能序号的 转换
                ItemDefine::SItemSkill* pSkill = (ItemDefine::SItemSkill *)pItem;
                m_mapSkillNO.insert( mapSkillNO::value_type( pSkill->ustItemID,(unsigned short)m_mapSkillNO.size()) );
                m_vecSkill.push_back( pSkill->ustItemID );

                //建立一个技能数组(只限法术)
                if(pSkill->ustItemID>=ItemDefine::StartID_Skill)
                {
                    int index;
                    index = pSkill->ustItemID-ItemDefine::StartID_Skill;
                    if(index >= 0 && index < m_SkillArray.GetSize() &&
                        pSkill->ustLevel > 0 /*&& pSkill->ustLevel < MaxLevel_Skill*/)
                    {
                        m_SkillArray[index][pSkill->ustLevel] = *pSkill;

                        if(pSkill->ustLevel==1)
                        {
                            m_SkillArray[index][ 0 ] = *pSkill;
                        }
                    }
                }
            }
            break;
        case ItemDefine::ITEMTYPE_STATUS:
            {
                ItemDefine::SItemStatus *pStatus = (ItemDefine::SItemStatus *)pItem;
                //m_mapStatusNO.insert(mapStatusNO::value_type(pStatus->ustItemID,(unsigned short)m_mapStatusNO.size()));
                //m_vecStatus.push_back(pStatus->ustItemID);
                //建立一个状态数组

                if(pStatus->ustItemID>=ItemDefine::StartID_Status)
                {
                    int index;
                    index = pStatus->ustItemID-ItemDefine::StartID_Status;
                    if (index >= 0 )
                    {
                        m_StatusArray[index][pStatus->ustLevel] = *pStatus;

                        if(pStatus->ustLevel==1)
                        {
                            m_StatusArray[index][ 0 ] = *pStatus;
                        }
                    }                    
                }

                m_vecStatusItem.push_back(pStatus);
            }
            break;
        case  ItemDefine::ITEMTYPE_MATERIAL:
            {
                m_vecMaterialItem.push_back(pItem);
            }
            break;
        case  ItemDefine::ITEMTYPE_GEM:
            {
                m_vecGemItem.push_back(pItem);
            }
            break;
		case ItemDefine::ITEMTYPE_PETEQUIP:
			{
				m_vecPetEquipItem.push_back(pItem);
			}
			break;
        default:
            break;
        }
    }

    // 分析怪物
    _MonsterInfos.clear();
    for ( int nIndex = 0; nIndex < MonsterAddr.size(); ++nIndex )
    {
        ItemDefine::SMonster* pMonster = (ItemDefine::SMonster*)&m_pbyGlobalBuffer[MonsterAddr[nIndex]]; 

        pMonster->iMonsterContainerIndex = _MonsterInfos.size();

        _MonsterInfos.push_back( pMonster );
        _Name2IndexMonsters.insert( Name2IndexMonsterContainer::value_type( pMonster->GetName(), pMonster->iMonsterContainerIndex ) );
        _Id2IndexMonsters.insert( Id2IndexMonsterContainer::value_type( pMonster->stMonsterId, pMonster->iMonsterContainerIndex) );
    }

    // 分析宠物
    m_vecPetMonster.clear();
    for ( int nIndex = 0; nIndex < PetMonsterAddr.size(); ++nIndex )
    {
        ItemDefine::SPetMonster* pPetMonster = (ItemDefine::SPetMonster*)&m_pbyGlobalBuffer[PetMonsterAddr[nIndex]]; 

        pPetMonster->iPetContainerIndex = m_vecPetMonster.size();

        m_vecPetMonster.push_back( pPetMonster );
        m_mapId2IndexPetMonster.insert( Id2IndexPetMonsterContainer::value_type( pPetMonster->stMonsterId, pPetMonster->iPetContainerIndex) );
        m_mapName2IndexPetMonster.insert( Name2IndexPetMonsterContainer::value_type( pPetMonster->GetName(), pPetMonster->iPetContainerIndex) );
        m_mapPetTypeList[pPetMonster->petType].push_back( pPetMonster );
    }

    // 分析怪物声音
    _creatureSounds.clear();
    for ( int nIndex = 0; nIndex < MonsterSoundAddr.size(); ++nIndex )
    {
        ItemDefine::SCreatureSound* pCreatureSound = (ItemDefine::SCreatureSound*)&m_pbyGlobalBuffer[MonsterSoundAddr[nIndex]]; 
        _creatureSounds.insert( CreatureSoundContainer::value_type( pCreatureSound->GetName(), pCreatureSound ) );
    }

    // 分析坐骑
    m_vecDrome.clear();
    for ( int nIndex = 0; nIndex < MountAddr.size(); ++nIndex )
    {
        ItemDefine::SDrome* pMount = (ItemDefine::SDrome*)&m_pbyGlobalBuffer[MountAddr[nIndex]]; 
        pMount->stIndex = m_vecDrome.size();

        m_mapDrome.insert( mapDrome::value_type( pMount->GetName(), pMount->stIndex ) );
        m_vecDrome.push_back( pMount);
    }

    // 分析随机
    _RandsById.clear();
    _RandsByLevel.clear();
    _RandMaxValueByLevelType.clear();
    for ( int nIndex = 0; nIndex < RandAddr.size(); ++nIndex )
    {
        ItemDefine::SRandAttribute* pRandAttribute = (ItemDefine::SRandAttribute*)&m_pbyGlobalBuffer[RandAddr[nIndex]]; 

        _RandsById.insert( RandContainerById::value_type( pRandAttribute->id, pRandAttribute ) ); 
        _RandsByLevel.insert(RandContainerByLevel::value_type( pRandAttribute->level, pRandAttribute));

        // 设置数值，等级，和类型
        SetRandValueLevelType(pRandAttribute->value[0].fValue, pRandAttribute->level, pRandAttribute->type[0]);
    }

    return TRUE;
}

BOOL CItemDetail::SaveBinFile( const char* pszFilename )
{
    FILE* fp = fopen( pszFilename, "wb" );
    if( !fp )
        return FALSE;

    // 版本
    unsigned long Major = ApplicationConfig::Instance().GetMajorVersion();
    unsigned long Minor = ApplicationConfig::Instance().GetMinorVersion();
    unsigned long Build = ApplicationConfig::Instance().GetBuildVersion();
    unsigned long Revision = ApplicationConfig::Instance().GetRevisionVersion();

    fwrite( &Major,   sizeof(unsigned long), 1, fp);
    fwrite( &Minor,   sizeof(unsigned long), 1, fp);
    fwrite( &Build,   sizeof(unsigned long), 1, fp);
    fwrite( &Revision,sizeof(unsigned long), 1, fp);

    // 道具
    int nItemCount = m_BakupItem.size();
    fwrite( &nItemCount, sizeof(int), 1, fp );
    for( int nItem = 0; nItem < nItemCount; ++nItem )
    {
        ItemDefine::SItemCommon* pItem = m_BakupItem[nItem];
        DWORD dwOffset = (BYTE*)pItem-m_pbyGlobalBuffer;
        fwrite( &dwOffset, sizeof(DWORD), 1, fp );    
    }

    // 怪物
    int nMonsterCount = _MonsterInfos.size();
    fwrite( &nMonsterCount, sizeof(int), 1, fp );
    for ( int nIndex = 0; nIndex < nMonsterCount; ++nIndex )
    {
        ItemDefine::SMonster* pMonster = _MonsterInfos[nIndex];
        DWORD dwOffset = (BYTE*)pMonster - m_pbyGlobalBuffer;
        fwrite( &dwOffset, sizeof(DWORD), 1, fp );
    }

    // 宠物
    int nPetMonsterCount = m_vecPetMonster.size();
    fwrite( &nPetMonsterCount, sizeof(int), 1, fp );
    for ( int nIndex = 0; nIndex < nPetMonsterCount; ++nIndex )
    {
        ItemDefine::SPetMonster* pPetMonster = m_vecPetMonster[nIndex];
        DWORD dwOffset = (BYTE*)pPetMonster - m_pbyGlobalBuffer;
        fwrite( &dwOffset, sizeof(DWORD), 1, fp );
    }

    // 怪物声音
    int nMonsterSoundCount = _creatureSounds.size();
    fwrite( &nMonsterSoundCount, sizeof(int), 1, fp );
    ItrCreatureSoundContainer itSound    = _creatureSounds.begin();
    ItrCreatureSoundContainer itSoundEnd = _creatureSounds.end();
    for ( ; itSound!=itSoundEnd; ++itSound)
    {
        ItemDefine::SCreatureSound* pCreatureSound = itSound->second;
        DWORD dwOffset = (BYTE*)pCreatureSound - m_pbyGlobalBuffer;
        fwrite( &dwOffset, sizeof(DWORD), 1, fp );
    }

    // 坐骑
    int nMountCount = m_vecDrome.size();
    fwrite( &nMountCount, sizeof(int), 1, fp );
    for ( int nIndex = 0; nIndex < nMountCount; ++nIndex )
    {
        ItemDefine::SDrome* pMount = m_vecDrome[ nIndex ];
        DWORD dwOffset = (BYTE*)pMount - m_pbyGlobalBuffer;
        fwrite( &dwOffset, sizeof(DWORD), 1, fp );
    }

    // 随机属性表
    int nRandCount = _RandsById.size();
    fwrite( &nRandCount, sizeof(int), 1, fp );
    RandContainerById::iterator it    = _RandsById.begin();
    RandContainerById::iterator itEnd = _RandsById.end();
    for ( ; it!=itEnd; ++it)
    {
        ItemDefine::SRandAttribute* pRand = it->second;
        DWORD dwOffset = (BYTE*)pRand - m_pbyGlobalBuffer;
        fwrite( &dwOffset, sizeof(DWORD), 1, fp );
    }

    // 大buffer
    fwrite( &m_dwGlobalBufferUsed, sizeof(int), 1, fp );
    if( m_dwGlobalBufferUsed > 0 )    
        fwrite( m_pbyGlobalBuffer, m_dwGlobalBufferUsed, 1, fp );

    if( fp )
        fclose( fp );
    return TRUE;
}


bool CItemDetail::AddItemToContainer( ItemDefine::SItemCommon *pItem )
{
    // 根据Item的等级放入相应的Vector中
    if( pItem->ustLevel>=1 && pItem->ustLevel<100 )
    {
        m_vectorLevelItem[pItem->ustLevel].push_back(pItem);
    }

    m_BakupItem.push_back(pItem);

    //记录ItemID
    m_vectorItemID.push_back( pItem->ustItemID );

    if( m_ItemFinder.Register( (char*)GetAddrPointer(pItem->dwItemNameAddr), pItem ) == 0 )
    {
        OutputSlkLoadingMessage( "道具重名 %s", (char*)GetAddrPointer(pItem->dwItemNameAddr) );
        return false;
    }

    if( pItem->ustItemID >= m_vectorItem.size() )
    {
        m_vectorItem.resize( pItem->ustItemID + pItem->ustItemID );        
    }
    m_vectorItem[pItem->ustItemID] = pItem;

    m_ItemFinder.Register( (char*)GetAddrPointer(pItem->dwItemNameAddr), pItem );

    return true;
}

void CItemDetail::SetCanEquipByString( char* szDst, const char* pszEquip )
{
    strlwr( const_cast<char*>(pszEquip) );
    for( int i=0; i<EEquipPartType_MaxEquitPart; ++i )
    {
		szDst[i] = (0 == _stricmp(pszEquip,ItemDefine::g_szCanEquip[i] ) ) ? 1 : 0;
    }

    szDst[EEquipPartType_Ring2]   = szDst[EEquipPartType_Ring1];
    szDst[EEquipPartType_Bangle2] = szDst[EEquipPartType_Bangle1];
}

//取得技能领悟条件
static char* (g_strKey[]) =
{
    "profession"
    ,"skillused"
};
static char* g_strSpn = " ,\r\n";

bool CItemDetail::GetProfessionCondition( ItemDefine::SSkillProfessionCondition *pCondition
                                         ,char *szProfession,char *szLevel )
{
    if( !pCondition || !szProfession || !szLevel )
        return false;
    pCondition->stProfessionID = GetProfessionID( szProfession );
    if( -1 == pCondition->stProfessionID )
    {
        OutputSlkLoadingMessage( "\t查找职业的领悟条件或使用条件:找不到职业:%s\r\n",szProfession );
        return false;
    }
    pCondition->stNeedLevel = atoi( szLevel );
    return true;
}

//bool CItemDetail::GetSkillUsedCondition( SSkillUsedCondition *pCondition
//                           ,char *szSkill,char *szMinUsed,char *szMaxUsed )
//{
//    if( !pCondition || !szSkill || !szMinUsed || !szMaxUsed )
//        return false;
//  ItemDefine::SItemCommon *pItem = GetItemByName( szSkill );
//    if( !pItem )
//    {
//        OutputSlkLoadingMessage( "\t查找职业的领悟条件:找不到技能:%s\r\n",szSkill );
//        return false;
//    }
//    pCondition->ustSkillID = pItem->ustItemID;
//    pCondition->ustMinUsed = atoi( szMinUsed );
//    pCondition->ustMaxUsed = atoi( szMaxUsed );
//    return true;
//}

//void CItemDetail::GetSkillUnderstandConditionFromString( SItemSkill *pSkill
//                                                        ,char *szStr )
//{    
//    char *szToken;
//    int iNum;
//    char *szProfession;
//    char *szLevel;
//    char *szSkill;
//    char *szMinUsed;
//    char *szMaxUsed;
//    
//    szToken = strtok( szStr,g_strSpn );
//    while( szToken )
//    {
//        //职业需求
//        if( 0 == strcmp( g_strKey[0],szToken ) )
//        {
//            iNum = pSkill->skillunderstand.iProfessionNum;
//            if( iNum < const_iSkillUnderstandPCondition )
//            {
//                szProfession = strtok(NULL,g_strSpn);
//                szLevel = strtok( NULL,g_strSpn);
//                szToken = szLevel;
//                if( GetProfessionCondition( 
//                    &pSkill->skillunderstand.profession[ iNum ],
//                    szProfession,szLevel  ) )
//                {
//                    pSkill->skillunderstand.iProfessionNum ++;
//                }
//                else
//                {
//                    OutputSlkLoadingMessage( "\t技能%d\r\n",pSkill->ustItemID );
//                }
//            }
//        }
//        else
//        //技能使用需求
//        if( 0 == strcmp( g_strKey[1],szToken ) )
//        {
//            iNum = pSkill->skillunderstand.iSkillUsedNum;
//            if( iNum < const_iSkillUnderstandSCondition )
//            {
//                szSkill = strtok(NULL,g_strSpn);
//                szMinUsed = strtok(NULL,g_strSpn);
//                szMaxUsed = strtok(NULL,g_strSpn);
//                szToken = szMaxUsed;
//
//                if( GetSkillUsedCondition(
//                    &pSkill->skillunderstand.skillused[ iNum ],
//                    szSkill,szMinUsed,szMaxUsed ) )
//                {
//                    pSkill->skillunderstand.iSkillUsedNum ++;
//                }
//                else
//                {
//                    OutputSlkLoadingMessage( "\t技能%d\r\n",pSkill->ustItemID );
//                }
//            }
//        }
//
//        szToken = strtok( NULL,g_strSpn );
//    }
//}
//
//void CItemDetail::GetSkillUsingConditionFromString( SItemSkill *pSkill,char *szStr )
//{
//    char *szToken;
//    int iNum;
//    char *szProfession;
//    char *szLevel;
//
//    szToken = strtok( szStr,g_strSpn );
//    while( szToken )
//    {
//        //职业需求
//        if( 0 == strcmp( g_strKey[0],szToken ) )
//        {
//            iNum = pSkill->skillusing.iProfessionNum;
//            if( iNum < const_iSkillUnderstandPCondition )
//            {
//                szProfession = strtok(NULL,g_strSpn);
//                szLevel = strtok( NULL,g_strSpn);
//                szToken = szLevel;
//                if( GetProfessionCondition( 
//                    &pSkill->skillusing.profession[ iNum ],
//                    szProfession,szLevel  ) )
//                {
//                    pSkill->skillusing.iProfessionNum ++;
//                }
//                else
//                {
//                    OutputSlkLoadingMessage( "\t技能%d\r\n",pSkill->ustItemID );
//                }
//            }
//        }
//
//        szToken = strtok( NULL,g_strSpn );
//    }
//}


//void CItemDetail::AddCardItem( CSlkReader *pReader,SItemCommon &common )
//{
//    SItemCard *pItemCard;
//    pItemCard = (SItemCard*)AllocItem( 0, sizeof( SItemCard ) );
//    if( !pItemCard )
//        return;    
//
//    CopyCommon( pItemCard,common );
//    AddToMap( pItemCard );
//}
//


ItemDefine::SItemCommon* CItemDetail::GetItemByID( unsigned short ustItemID )
{
    if ( ustItemID >= m_vectorItem.size() )
    { return NULL; }
    return m_vectorItem[ ustItemID ];
}

// 取得对应套装map
std::vector<ItemDefine::SItemCanEquip*>* CItemDetail::GetSuitsByID( short stSuitID )
{
    if( m_mapSuit.find( stSuitID ) != m_mapSuit.end() )
        return &m_mapSuit[stSuitID];

    return NULL;
}

//取得对应道具的类型
uint8 CItemDetail::GetItemType( unsigned short ustItemID)
{
    ItemDefine::SItemCommon *pItem = GetItemByID( ustItemID );
    if( pItem )
    {
        return pItem->ucItemType;
    }
    return ItemDefine::ITEMTYPE_MAX;
}

bool CItemDetail::IsEquipItem( unsigned short ustItemID)
{
    if (GetItemType(ustItemID) == ItemDefine::ITEMTYPE_WEAPON || GetItemType(ustItemID) == ItemDefine::ITEMTYPE_ARMOUR)
    { return true; }

    return false;
}

ItemDefine::SItemCommon *CItemDetail::GetItem( unsigned short ustItemID,int iItemType )
{
    ItemDefine::SItemCommon *pItem = GetItemByID( ustItemID );
    if( pItem )
    {
        if( iItemType != pItem->ucItemType )
            return 0;
    }
    return pItem;
}

ItemDefine::SItemCommon *CItemDetail::GetItemByNameAndLevel( char*szItemName, int nLevel )
{
    CMapStrToIDMgr::RecordSet* pSet = m_ItemFinder.GetRecordSetByName( szItemName );
    if( !pSet )
        return NULL;
    for( int nRecord = 0; nRecord < pSet->vectorRecord.size(); nRecord++ )
    {
        CMapStrToIDMgr::Record* pRecord = &pSet->vectorRecord[nRecord];

        if( stricmp( pRecord->pszName, szItemName ) == 0 )
        {
            ItemDefine::SItemCommon* pItem = (ItemDefine::SItemCommon*)pRecord->pDst;
            if( pItem &&
                pItem->ustLevel == nLevel )
            {
                return pItem;
            }
        }
    }
    return NULL;
}

ItemDefine::SItemCommon *CItemDetail::GetItemByName(const char*szItemName )
{
    return (ItemDefine::SItemCommon *)m_ItemFinder.GetDstByName( szItemName );
    //mapNameItem::iterator itName;
    //std::string strFind = szItemName;

    //itName = m_mapNameItem.find( strFind );
    //if( itName == m_mapNameItem.end() )
    //    return 0;

    //return (*itName).second;
    return NULL;
}

bool CItemDetail::LoadSlkProfession( char *szFile )
{
    CSlkReader reader;
    if( !reader.ReadFromFile( szFile ) )
    {
        GetErrorLog()->logString( "profession.slk not find");
        return false;
    }

    int iCol;
    //int iValue;
    int iRet;
    ItemDefine::SProfession profession;

    int iRow = 2;
    while ( CSlkReader::ret_readover != ( iRet = reader.GotoNextLine( iRow++ ) ) ) 
    {
        if( CSlkReader::ret_nothisline == iRet )
            continue;

        iCol = 1;

        //职业名字    
        std::string strProfessionName;
        //if( !reader.GetStringField( iCol,profession.szName) )
        if( !reader.GetStringField( iCol,strProfessionName) )
        {
            GetErrorLog()->logString("职业名字缺失");

            continue;
        }
        profession.dwNameAddr = AllocStringCopy( strProfessionName.c_str() );
        iCol ++;

        std::string strProfessionDesc;
        //if( !reader.GetStringField( iCol,profession.szDesc))
        if( !reader.GetStringField( iCol,strProfessionDesc))
        {
            GetErrorLog()->logString( "profession desc not find" );
            continue;
        }
        profession.dwDescAddr = AllocStringCopy( strProfessionDesc.c_str() );
        iCol ++;

        profession.stType = ItemDefine::ProfessionType_Normal;

        if( !m_mapProfession.insert( 
            //mapProfession::value_type(profession.szName.c_str(),(short)m_vecProfession.size() ) ).second )
            mapProfession::value_type(profession.GetName(),(short)m_vecProfession.size() ) ).second )
        {
            OutputSlkLoadingMessage( "\t职业重名:%s\r\n", profession.GetName() );// profession.szName );
            GetErrorLog()->logString( "prefession name redefine!" );
            continue;
        }
        m_vecProfession.push_back( profession );
    }
    return true;
}

ItemDefine::SProfession *CItemDetail::GetProfession( int iIndex )
{
    if( iIndex < 0 || iIndex >= (int )m_vecProfession.size() )
        return 0;
    return &m_vecProfession[ iIndex ];
}

int    CItemDetail::GetProfessionNum( void )
{
    return (int)m_vecProfession.size();
}

int CItemDetail::GetProfessionID( char *szName )
{
    mapProfession::iterator it;
    it = m_mapProfession.find( szName ); 
    if( m_mapProfession.end() == it )
    {
        return -1;
    }
    return (*it).second;
}

ItemDefine::SProfession    *CItemDetail::GetProfession( char *szName )
{
    return GetProfession( GetProfessionID( szName) );
}

ItemDefine::SCreatureSound* CItemDetail::GetCreatureSound( const std::string& strName )
{
    ItrCreatureSoundContainer it = _creatureSounds.find( strName );
    if ( it != _creatureSounds.end())
        return it->second;

    return NULL;
}

CItemDetail::ItrCreatureSoundContainer CItemDetail::GetCreatureSoundItr( const std::string& strName )
{ 
    return _creatureSounds.find( strName );
}

int CItemDetail::FindDromeIndxByName( char *szName )
{
    mapDrome::iterator it;
    it = m_mapDrome.find( szName );
    if( m_mapDrome.end() == it )
        return -1;
    return it->second;
}

int CItemDetail::FindTrafficIndexByName( char *szName )
{
    mapTraffic::iterator it;
    it = m_mapTraffic.find( szName );
    if( m_mapTraffic.end() == it )
        return -1;
    return it->second;
}

ItemDefine::SDrome* CItemDetail::GetDrome( int nIndex )
{
    if( m_vecDrome.empty() )
        return NULL;
    if( nIndex < 0 || nIndex >= (int)m_vecDrome.size() )
        return NULL;
    // ToLog( nIndex == m_vecDrome[ nIndex ]->stIndex );
    return m_vecDrome[ nIndex ];
}

ItemDefine::STraffic *CItemDetail::GetTraffic( int nIndex )
{
    if( m_vecTraffic.empty() )
        return NULL;
    if( nIndex < 0 || nIndex >= m_vecTraffic.size() )
        return 0;
    // ToLog( nIndex == m_vecTraffic[ nIndex ].nIndex );
    return &m_vecTraffic[ nIndex ];
}

ItemDefine::SDrome* CItemDetail::GetDromeByID( int nID )
{
    for( int i = 0; i < m_vecDrome.size(); ++i)
    {
        ItemDefine::SDrome* pMount = m_vecDrome[i];
        if ( !pMount)
            continue;

        if( pMount->stId == nID )
            return pMount;
    }
    return NULL;
}

ItemDefine::SDrome* CItemDetail::GetDromeByName( char *szName )
{ 
    return GetDrome( FindDromeIndxByName( szName ) ); 
}

ItemDefine::STraffic *CItemDetail::GetTrafficByID( int nID )
{
    for( int i = 0; i < m_vecTraffic.size(); i++ )
    {
        if( m_vecTraffic[i].nID == nID )
        {
            return &m_vecTraffic[i];
        }
    }
    return NULL;
}

ItemDefine::STraffic *CItemDetail::GetTrafficByName( char *szName ) 
{ 
    return GetTraffic( FindTrafficIndexByName( szName ) ); 
}


bool CItemDetail::LoadSlkTraffic( const char* szFileName )
{   
    MeXmlDocument doc;
    if( !doc.LoadFile( szFileName ) )
        return false;

    MeXmlElement* lpRoot = doc.FirstChildElement("Project");
    if(!lpRoot)
        return false;


    MeXmlElement* pElement = lpRoot->FirstChildElement("Traffic");

    while ( pElement )
    {
        ItemDefine::STraffic traffic;

        int nValue= 0;
        if ( MEXML_SUCCESS == pElement->QueryIntAttribute("ID",&nValue ) )
        { traffic.nID = nValue; }

        const char* szName = pElement->Attribute("Name");
        if ( !szName )
        { return false; }
        traffic.dwNameAddr = AllocStringCopy( szName );

        if ( MEXML_SUCCESS == pElement->QueryIntAttribute("DromeID",&nValue) )
        { traffic.nDromeID = nValue; }
        
        if ( MEXML_SUCCESS == pElement->QueryIntAttribute("MapID",&nValue) )
        { traffic.nMapID = nValue; }

        if ( MEXML_SUCCESS == pElement->QueryIntAttribute("RouteID",&nValue) )
        { traffic.nRouteID = nValue; }

        if ( MEXML_SUCCESS == pElement->QueryIntAttribute("NextTrafficId",&nValue) )
        { traffic.nextTrafficId = nValue; }

        m_mapTraffic.insert( mapTraffic::value_type( traffic.GetName(), m_vecTraffic.size() ) );        
        m_vecTraffic.push_back( traffic );

        pElement = pElement->NextSiblingElement("Traffic");
    }
    return true;
}

bool IsNormalAttack( unsigned short ustSkillID )
{
    switch( ustSkillID )
    {
    case ConstSkillId_NormalAttack_Combat      :
    case ConstSkillId_NormalAttack_Warrior :
    case ConstSkillId_NormalAttack_Mage :
    case ConstSkillId_NormalAttack_Taoist   :
    case ConstSkillId_NormalAttack_Assassin :
    case ConstSkillId_NormalAttack_Hunter   :
    case ConstSkillId_NormalAttack_Sniper:
        return true;
    }
    return false;
}

bool IsCollectSkill( unsigned short ustSkillID )
{
    switch ( ustSkillID )
    {
    case ItemDefine::eCSI_CaiYao:
    case ItemDefine::eCSI_CaiKuang:
    case ItemDefine::eCSI_Treasure:
    case ItemDefine::eCSI_BuZhuo:
    case ItemDefine::eCSI_BuChong:
        return true;
    default:
        break;
    }

    return false;
}

bool IsRecipeSkill( unsigned short ustSkillID )
{
    switch ( ustSkillID )
    {
    case ItemDefine::eCSI_DuanZao:
    case ItemDefine::eCSI_ZhuJia:
    case ItemDefine::eCSI_GongYi:
    case ItemDefine::eCSI_LianYao:
    case ItemDefine::eCSI_XunMa:
    case ItemDefine::eCSI_ZhuBao:
    case ItemDefine::eCSI_CatchPet:
        return true;
    default:
        break;
    }

    return false;
}

bool IsSkillCanBeInterrupt( unsigned char interrupeType, unsigned short ustSkillID )
{
    switch ( interrupeType )
    {
    case ItemDefine::EIT_Move:
        {
            if( ustSkillID == ItemDefine::eSSI_MountMonster || ustSkillID == ItemDefine::eSSI_Relive )
            { return false; }
        }
        break;
    }
    return true;
}

bool IsDamageSkill( unsigned short ustSkillID )
{
    ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( ustSkillID, 1 );
    if (pSkill == NULL)
    { return false; }

    if ( pSkill->ustDamageBalanceType == ItemDefine::balancetype_damagephysicaldefend ||
         pSkill->ustDamageBalanceType == ItemDefine::balancetype_damagebothdefend  ||
         pSkill->ustDamageBalanceType == ItemDefine::balancetype_damagemagicdefend 
         )
    { return true; }

    return false;
}

bool IsMountSkill( unsigned short ustSkillID )
{
    ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( ustSkillID, 1 );
    if (pSkill == NULL)
    { return false; }

    if ( pSkill->sSkillCategory == ItemDefine::SCT_MountPassive ||
        pSkill->sSkillCategory == ItemDefine::SCT_MountMasterInitiativeUnControl  ||
        pSkill->sSkillCategory == ItemDefine::SCT_MountMasterInitiativeControl
        )
    { return true; }

    return false;
}

bool IsHoldSkill( unsigned short ustSkillID )
{
    ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( ustSkillID, 1 );
    if (pSkill == NULL)
    { return false; }

    if ( pSkill->iDurationTime > 0 && pSkill->iDamageBalanceDelay > 0 )
    { return true; }

    return false;
}

bool IsLootMountSkill( unsigned short ustSkillID )
{
    if( ustSkillID == ItemDefine::eCSI_BuZhuo )
        return true;
    return false;
}

bool IsGoBackSkill( unsigned short ustSkillID )
{
    if( ustSkillID == ItemDefine::eCSI_GoBack || ustSkillID == ItemDefine::eCSI_GoBack2 )
        return true;
    return false;
}

bool IsMountMonsterSkill( unsigned short ustSkillID )
{
    if( ustSkillID == ItemDefine::eSSI_MountMonster )
        return true;
    return false;
}


ItemDefine::SItemCommon* CItemDetail::GetWeaponItem( int iIndex )
{
    if( m_vecWeaponItem.empty() )
    {
        return NULL;
    }
    if( iIndex < 0 && iIndex >= m_vecWeaponItem.size() )
        return NULL;
    return m_vecWeaponItem[iIndex];
}

ItemDefine::SItemCommon* CItemDetail::GetArmourItem( int iIndex )
{
    if( m_vecArmourItem.empty() )
    {
        return NULL;
    }
    if( iIndex < 0 && iIndex >= m_vecArmourItem.size() )
        return NULL;
    return m_vecArmourItem[iIndex];
}

ItemDefine::SItemCommon* CItemDetail::GetGloveItem( int iIndex )
{
    if( m_vecGloveItem.empty() )
    {
        return NULL;
    }
    if( iIndex < 0 && iIndex >= m_vecGloveItem.size() )
        return NULL;
    return m_vecGloveItem[iIndex];
}

ItemDefine::SItemCommon* CItemDetail::GetShoeItem( int iIndex )
{
    if( m_vecShoeItem.empty() )
    {
        return NULL;
    }
    if( iIndex < 0 && iIndex >= m_vecShoeItem.size() )
        return NULL;
    return m_vecShoeItem[iIndex];
}

ItemDefine::SItemCommon* CItemDetail::GetCapItem( int iIndex )
{
    if( m_vecCapItem.empty() )
    {
        return NULL;
    }
    if( iIndex < 0 && iIndex >= m_vecCapItem.size() )
        return NULL;
    return m_vecCapItem[iIndex];
}

int CItemDetail::GetWeaponNumber( )
{
    return (int)m_vecWeaponItem.size( );
}

int CItemDetail::GetArmourNumber( )
{
    return (int)m_vecArmourItem.size( );
}

int CItemDetail::GetGloveNumber( )
{
    return (int)m_vecGloveItem.size( );
}

int    CItemDetail::GetShoeNumber( )
{
    return (int)m_vecShoeItem.size( );
}

int CItemDetail::GetCapNumber( )
{
    return (int)m_vecCapItem.size( );
}

bool CItemDetail::LoadSlkNewCreatItem(char *szFile)
{
    CSlkReader reader;
    if (!reader.ReadFromFile(szFile))
    {
        // ToLog(false&&"NewCreatItem.slk not find");
        return false;
    }

    int iRow =2;
    int iRet;
    int iCol;
    int iValue;
    float fValue;
    int nAFlag = 0;
    int nWFlag = 0;
    while( CSlkReader::ret_readover!=(iRet=reader.GotoNextLine(iRow++)))    
    {
        if(CSlkReader::ret_nothisline==iRet)
            continue;

		ItemDefine::SCreatItemMod *pCreatItemMod;
        ItemDefine::SItemNew *pNewItem ;
        pCreatItemMod = (ItemDefine::SCreatItemMod*)AllocItem( 0, sizeof( ItemDefine::SCreatItemMod ) ) ;
        pNewItem = (ItemDefine::SItemNew*)AllocItem( 0, sizeof( ItemDefine::SItemNew ) ) ;
        if(!pCreatItemMod)
        {
            OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
            GetErrorLog()->logString( "NewCreatItem.slk内存分配出错" );
            return false;
        }
        if(!pNewItem)
        {
            OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
            GetErrorLog()->logString( "NewCreatItem.slk内存分配出错" );
            return false;
        }

        iCol = 1;
        std::string strTemp;

        /*if (!reader.GetStringFieldByName("名称",strTemp))
        {
        // ToLog(false);
        }
        pCreatItemMod->dwName = AllocStringCopy(strTemp.c_str());
        iCol++;*/

        if (!reader.GetIntFieldByName("Lv",iValue))
        {
            // ToLog(false);
            //continue;
        }
        pCreatItemMod->ustLevel = iValue;
        iCol++;

        if (!reader.GetIntFieldByName("IfWeapon",iValue))
        {
            // ToLog(false);
        }
        pCreatItemMod->bIsWeapon = iValue>0?true:false;
        nWFlag = iValue;
        iCol++;

        if (!reader.GetIntFieldByName("IfArmour",iValue))
        {
            // ToLog(false);
        }
        pCreatItemMod->bIsArmour = iValue>0?true:false;
        nAFlag = iValue;
        iCol++;

        if (!reader.GetStringFieldByName("Equiptype",strTemp))
        {
            pCreatItemMod->stItemType = eWeaponType_Invalid;
        }
        else if (nWFlag == 1)
        {
            pCreatItemMod->stItemType = eWeaponType_Combat;

			int nType = GetIDByConstString( strTemp.c_str(),ItemDefine::g_szWeaponType,sizeof(ItemDefine::g_szWeaponType)/sizeof(char*) );

            if ( nType == -1)
            {
                OutputSlkLoadingMessage( "\tError:[武器类型不存在]失败\r\n" );
                // ToLog(false);
                continue;
            }

            pCreatItemMod->stItemType = nType;

        }
        else if (nAFlag == 1)
        {
            pCreatItemMod->stItemType = HelperFunc::GetIDByConstString( (char*)strTemp.c_str(),
                ItemDefine::g_szEquipType,sizeof(ItemDefine::g_szEquipType)/sizeof(char*) );
        }
        iCol++;

        if (!reader.GetIntFieldByName("ModelId",iValue))
        {
            // ToLog(false);
        }
        pNewItem->stModelID = iValue;
        iCol++;

        //if (!reader.GetStringFieldByName("物品在物品栏中得icon文件",strTemp))
        //{
        //    // ToLog(false);
        //}
        //pNewItem->dwIconFileName = AllocStringCopy(strTemp.c_str());
        //iCol++;

        if (!reader.GetStringFieldByName("Vol",strTemp))
        {
            // ToLog(false);
        }
        else
        {
            if (strTemp == "small")
                pCreatItemMod->stItemSize = ItemDefine::eBulk_Small;
            if (strTemp == "normal")
                pCreatItemMod->stItemSize = ItemDefine::eBulk_Normal;
            if (strTemp == "big")
                pCreatItemMod->stItemSize = ItemDefine::eBulk_Big;

        }        
        iCol++;

        if (!reader.GetIntFieldByName("speed",iValue))
        {
            // ToLog(false);
        }
        pNewItem->stAttSpeed = iValue;
        iCol++;        

        if (!reader.GetFloatFieldByName("HitCoef",fValue))
        {
            // ToLog(false);
        }
        pNewItem->fHitMod = fValue;
        iCol++;    

        if (!reader.GetIntFieldByName("Price",iValue))
        {
            // ToLog(false);
        }
        pNewItem->nCost = iValue;
        iCol++;        

        if (!reader.GetFloatFieldByName("AtkRange",fValue))
        {
            // ToLog(false);
        }
        pNewItem->fAttRange = fValue;
        iCol++;

        if (!reader.GetIntFieldByName("iconid",iValue))
        {
            // ToLog(false);
        }
        pNewItem->stIconId = iValue;
        iCol++;

		ItemDefine::SCreatItemMod *pCreatMod = GetCreatMod(pCreatItemMod->ustLevel,
            pCreatItemMod->stItemSize,
            pCreatItemMod->bIsWeapon,
            pCreatItemMod->bIsArmour,
            pCreatItemMod->stItemType);
        if (pCreatMod)
        {
            if (pCreatItemMod->bIsArmour == pCreatMod->bIsArmour&&
                pCreatItemMod->bIsWeapon == pCreatMod->bIsWeapon&&
                pCreatItemMod->ustLevel == pCreatMod->ustLevel&&
                pCreatItemMod->stItemSize == pCreatMod->stItemSize&&
                pCreatItemMod->stItemType == pCreatMod->stItemType)
            {
                pCreatMod->vtItemNew.push_back(pNewItem);
            }
            else
            {
                pCreatItemMod->vtItemNew.push_back(pNewItem);
                m_vecCreatItemMod.push_back(pCreatItemMod);
            }
        }
        else
        {
            pCreatItemMod->vtItemNew.push_back(pNewItem);
            m_vecCreatItemMod.push_back(pCreatItemMod);
        }        
    }
    return true;
}

void CItemDetail::GetCreatItemModByLevel( unsigned short ustLevel,std::vector<ItemDefine::SCreatItemMod*> &pvtCreatItemMod )
{
    //mapCreatItemMod::iterator itRand;
    //short RandID = ustLevel;
    //
    //for( itRand = m_mapCreatItemMod.begin(); itRand != m_mapCreatItemMod.end(); itRand ++ )
    //{
    //    if( (*itRand).first == ustLevel)    
    //        pvtCreatItemMod.push_back( (*itRand).second );
    //    /*    if( (*itRand).first == ustLevel )
    //        return (*itRand).second;    */    
    //}
    //return;
}

ItemDefine::SCreatItemMod *CItemDetail::GetCreatMod(unsigned short ustLevel,short stSize,bool bWeapon,bool bArmour,short stType)
{
	ItemDefine::SCreatItemMod* pCreatItemMod ;
    for(int nloop = 0;nloop< m_vecCreatItemMod.size();nloop++)
    {
        pCreatItemMod = m_vecCreatItemMod[nloop];

        if (ustLevel == pCreatItemMod->ustLevel&&
            stSize == pCreatItemMod->stItemSize&&
            bWeapon == pCreatItemMod->bIsWeapon&&
            bArmour == pCreatItemMod->bIsArmour&&
            stType == pCreatItemMod->stItemType)
        {
            return pCreatItemMod;    
        }
    }
    return NULL;
}

// int CItemDetail::CreateSkillDesc( unsigned short ustSkillID, unsigned short ustSkillLevel, 
//                                  char (*pDesc)[256], DWORD *pDescColor, int iDescLength )
// {
//     //获取技能的信息
//     ItemDefine::SItemSkill *pSkill;
//     pSkill = GettheItemDetail().GetSkillByID( ustSkillID, ustSkillLevel );
//     if(!pSkill)
//         return 0;
// 
//     //记录行数
//     int iLineCount = 0;
// 
//     //暂时的颜色
//     for( int i=0;i<iDescLength;i++ )
//     {
//         pDescColor[ i ] = 0xff000000;
//     }
// 
//     //技能名称
//     _snprintf( pDesc[iLineCount++], 255,
//         g_CfgItemDesc.m_strSkillName, 
//         //pSkill->szItemName.c_str() );
//         GetString( pSkill->dwItemNameAddr ) );
//     if( iLineCount == iDescLength )
//         return iLineCount;
// 
//     return iLineCount;    
// }

//获取状态的描述信息
// int CItemDetail::CreateStatusDesc( unsigned short ustStatusID, unsigned short ustStatusLevel,
//                                   char (*pDesc)[256], DWORD *pDescColor, int iDescLength )
// {
//     //获取状态的信息
//     ItemDefine::SItemStatus *pStatus;
//     pStatus = GettheItemDetail().GetStatus( ustStatusID, ustStatusLevel );
//     if(!pStatus)
//         return 0;
// 
//     //记录行数
//     int iLineCount = 0;
// 
//     //暂时的颜色
//     for( int i=0;i<iDescLength;i++ )
//     {
//         pDescColor[ i ] = 0xff000000;
//     }
// 
//     //状态的描述
//     _snprintf( pDesc[iLineCount++], 255,
//         g_CfgItemDesc.m_strStatusDesc, 
//         //pStatus->szItemDesc.c_str() );
//         GetString( pStatus->dwItemDescAddr ) );
//     if( iLineCount == iDescLength )
//         return iLineCount;
// 
//     return iLineCount;    
// }

//随机取得一个等级范围的道具
unsigned short CItemDetail::GetRandomLevelRangeItem(int iMinLevel, int iMaxLevel)
{
    int level = 0;
    if (iMinLevel > 100)
        iMinLevel = 99;
    if (iMaxLevel <=  iMinLevel)
        level = iMinLevel;
    else
        level = rand() % (iMaxLevel - iMinLevel) + iMinLevel;
    //
    if (level < 0)
        return InvalidLogicNumber;
    if (level >= 100)
        return InvalidLogicNumber;
    //
    while (1)
    {
        if (m_vectorLevelItem[level].size() > 0)
            break;
        level ++;
        if (level >= iMaxLevel)
            break;
    }
    //
    if (level >= iMaxLevel)
        return InvalidLogicNumber;
    //
    int rand_num = (int) (rand() % m_vectorLevelItem[level].size());
    //
    return m_vectorLevelItem[level][rand_num]->ustItemID;
}

bool CItemDetail::LoadSlkBaseAttr(char *szFile )
{
    CSlkReader reader;
    if(!reader.ReadFromFile( szFile ))
    {
        //取新的slk资源
        GetErrorLog()->logString( "UpBaseAttr.slk not find" );
        return false;
    }
    bool bReadSucc = true;
    int iRow = 3;
    int iCol;
    int iRet;
    int  iValue;

    while(CSlkReader::ret_readover!=(iRet=reader.GotoNextLine(iRow++)))
    {

        if(CSlkReader::ret_nothisline==iRet)
            continue;

        ItemDefine::SUpBaseAttr *pUpBaseAttr;
        pUpBaseAttr = (ItemDefine::SUpBaseAttr*)AllocItem( 0, sizeof( ItemDefine::SUpBaseAttr ) );
        if(!pUpBaseAttr)
        {
            OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
            GetErrorLog()->logString( "UpBaseAttr.slk内存分配出错" );
            return false;
        }

        iCol = 1;
        ////////////////////////////////////////////////////////////
#define UpBaseAttrGetFieldInt( t, str ) \
    if( !reader.GetIntFieldByName( str.c_str(), iValue ) ) \
        { \
        char szMem[256] = {0};    \
        strncpy_s(szMem, sizeof( szMem ), ("Error:读取UpBaseAttr.slk字段"+str+"出错\r\n").c_str(), sizeof(szMem)-1);    \
        OutputSlkLoadingMessage( szMem ); \
        GetErrorLog()->logString( ("Error:读取UpBaseAttr.slk字段"+str+"出错").c_str() ); \
        continue; \
        } \
        t = iValue; \
        iCol++;
        /////////////////////////////////////////////////////////////
        std::string szProInfo;
        szProInfo = "Lvl";
        UpBaseAttrGetFieldInt( pUpBaseAttr->sLevel, szProInfo );

        for( int i=0; i<=EArmType_MaxSize; i++)
        {
			CProfessionInfo *pProInfo = GetSystemConfig()->GetProessionInfoFromID( i );
            if( !pProInfo )
                continue;
            szProInfo = pProInfo->m_strProShow;
            string szTemp = szProInfo+"Str";
            UpBaseAttrGetFieldInt( pUpBaseAttr->Str[i], szTemp);// szTemp.c_str() );
            szTemp = (szProInfo+"Agi");
            UpBaseAttrGetFieldInt( pUpBaseAttr->Agi[i], szTemp );
            szTemp = (szProInfo+"Con");
            UpBaseAttrGetFieldInt( pUpBaseAttr->Con[i], szTemp );
            szTemp = (szProInfo+"Int");
            UpBaseAttrGetFieldInt( pUpBaseAttr->Int[i], szTemp );
            szTemp = (szProInfo+"Mag");
            UpBaseAttrGetFieldInt( pUpBaseAttr->Mag[i], szTemp );
            szTemp = (szProInfo+"Charm");
            UpBaseAttrGetFieldInt( pUpBaseAttr->Charm[i], szTemp );
            szTemp = "stSkillPoint";
            UpBaseAttrGetFieldInt(pUpBaseAttr->stSkillPoint,szTemp);
        }
        //加入查找
        m_mapUpBaseAttr.insert( mapUpBaseAttr::value_type( pUpBaseAttr->sLevel, pUpBaseAttr ) );
        //加入vector
        m_vectorUpBaseAttr.push_back( pUpBaseAttr );

    }
    return true;
}

ItemDefine::SUpBaseAttr *CItemDetail::GetBaseAttrByLevel(short sLevel)
{
    //mapUpBaseAttr::iterator itRand;
    //short RandID = sLevel;

    mapUpBaseAttr::iterator itr = m_mapUpBaseAttr.find(sLevel);
    if (itr != m_mapUpBaseAttr.end())
    {
        return itr->second;
    }

    //for( itRand = m_mapUpBaseAttr.begin(); itRand != m_mapUpBaseAttr.end(); itRand ++ )
    //{
    //    if( (*itRand).first == sLevel )
    //        return (*itRand).second;
    //}

    return NULL;
}

//void CItemDetail::AddCrystalItem(CSlkReader *pReader, SItemCommon &common)
//{
//    SItemCrystal *pCrystal = 0;
//    int iValue = 0;
//    int iCon = 0;
//
//    int iLineNo = pReader->FindLineByIntField( 1,common.ustItemID );
//    if( -1 == iLineNo )
//    {
//        OutputSlkLoadingMessage( "\tError:Crystal.slk中找不到ID为:%d的物品!\r\n",common.ustItemID );
//        GetErrorLog()->logString( "Crystal.slk中找不到物品ID" );
//        return;
//    }
//    if(  CSlkReader::ret_succ != pReader->GotoNextLine( iLineNo ))
//    {
//        OutputSlkLoadingMessage( "\tError:Crystal.slk中找不到ID为:%d的物品!\r\n",common.ustItemID );
//        GetErrorLog()->logString( "Crystal.slk中找不到物品ID" );
//        return;
//    }
//
//    pCrystal = (SItemCrystal*)AllocItem( 0, sizeof( SItemCrystal ) );
//
//    if( !pCrystal )
//    {
//        OutputSlkLoadingMessage( "\tError:Crystal.slk中ID为:%d的物品,分配内存失败!\r\n",common.ustItemID );
//        // ToLog(false);
//        return;
//    }
//
//    CopyCommon( pCrystal,common );
//
//
//    bool bReadSucc = true;
//
//    while( bReadSucc )
//    {
//        bReadSucc = false;
//        iCon = 3;
//        if (!pReader->GetIntFieldByName("Lv",iValue))
//        {
//            // ToLog( false );
//            continue;
//        }
//        pCrystal->usCrystalLevel = iValue;
//
//        bReadSucc = true;
//        break;
//    }
//    if( bReadSucc )
//    {
//        //添加到物品队列中
//        AddToMap( pCrystal );
//
//        m_vectorCrystalItem.push_back( pCrystal );
//    }
//}

bool CItemDetail::LoadSlkIcon(char* szFile)
{
    CSlkReader reader;
    if (!reader.ReadFromFile(szFile))
    {
        // ToLog(false&&"icon.slk not find");
        return false;
    }    
    int iRow =2;
    int iRet;
    int iCol;
    int iValue;    

    while( CSlkReader::ret_readover!=(iRet=reader.GotoNextLine(iRow++)))    
    {
        if(CSlkReader::ret_nothisline==iRet)
            continue;

        ItemDefine::sIcon *pIcon;
        pIcon = (ItemDefine::sIcon*)AllocItem( 0, sizeof( ItemDefine::sIcon ) ) ;        
        if(!pIcon)
        {
            OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
            GetErrorLog()->logString( "icon.slk内存分配出错" );
            return false;
        }

        iCol = 1;
        std::string strTemp;

        if (!reader.GetIntFieldByName("IconId",iValue))
        {
            // ToLog(false);
        }
        pIcon->stIconId = iValue;
        iCol++;

        if(!reader.GetStringFieldByName("iconFile",strTemp))
        {
            // ToLog(false);
        }        
        strncpy_s(pIcon->sIconFile, sizeof(pIcon->sIconFile), strTemp.c_str(), sizeof(pIcon->sIconFile)-1);
        iCol++;

        m_vectorIcon.push_back(pIcon);

    }
    return true;
}


ItemDefine::sIcon *CItemDetail::GetIconFileByID(unsigned short ustId)
{
    if (ustId < 1000)
    {
        //    // ToLog(false&&"iconId错误");
        return NULL;
    }
    else
    {
        int nInx = ustId - 1000;
        if( nInx > m_vectorIcon.size() )
            return NULL;
        ItemDefine::sIcon* pIconMod = m_vectorIcon[nInx];

        return pIconMod;    
    }
    return NULL;
}

uint32 CItemDetail::IsCanSplitItem( uint16 itemId )
{
    ItemDefine::SItemCommon* pItemCommonConfig = GettheItemDetail().GetItemByID( itemId );
    if ( pItemCommonConfig == NULL )
    { return ER_ItemConfigNotExist; }

    // 是否可以被拆分
    if ( !pItemCommonConfig->bIsCanSplit )
    { return ER_SplitItemCantBeSplit; }

	/*
    // 是否是武器
    if ( pItemCommonConfig->ucItemType != ItemDefine::ITEMTYPE_WEAPON )
    { return ER_SplitItemTypeError; }

    ItemDefine::SItemWeapon* pItemWeaponConfig = (ItemDefine::SItemWeapon*)pItemCommonConfig;

    // 是否武器等级符合 大于40级 
    if ( pItemWeaponConfig->stEquipLevelReq < theItemSplitConfig.GetLevel() )
    { return ER_SplitItemLevelError; }

    // 是否10的倍数 50 60 70 80 ...
    if ( pItemWeaponConfig->stEquipLevelReq % theItemSplitConfig.GetMultiLevel()!= 0)
    { return ER_SplitItemLevelMulError; }

    // 是否武器品质符合
    if ( pItemWeaponConfig->ustLevel < theItemSplitConfig.GetQualityLevel() )
    { return ER_SplitItemQualityLevelError; }
	*/

    // 是否有拆分物品信息
    if ( !theItemSplitConfig.IsHaveSplitItemInfo(itemId) )
    { return ER_SplitItemConfigNotExist;}

    return ER_Success;
}
#pragma warning( pop )
