////////////////////////////////////////////////////////////////////////
#include "IconManagerClient.h"
#include "Me3d/Include.h"
#include "MessageDefine.h"
#include "MeUi/ExpressionManager.h"
#include "RandPropertyEvaluate.h"
#include "StarLevelUpConfig.h"
#include "ItemDetail.h"
#include "PlayerRole.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "GameMain.h"
#include "color_config.h"
#include "XmlStringLanguage.h"
#include "ArmourElementsConfig.h"
#include "TimeEx.h"
#include "SuitOperateConfig.h"
#include "FilePath.h"
#include "MeUi/UiManager.h"
#include "TitleConfig.h"
#include "Common.h"
#include "CountryFunction.h"
#include "XinFaConfig.h"
#include <sstream>
#include "SuitConfig.h"
#define OFFSET_WIDTH	3
#define OFFSET_HEIGHT	4
#define	FRAME_SIZE		7
#define TILE_SIZE		32
#define PLAYERPROFESSION 5

#define TIP_ICON_SIZE	64
#define TIP_ICON_SOUL_SIZE  28
#define TIP_ICON_GEM_SIZE   18
#define TIP_LINE_WIDTH      119
#define TIP_LINE_HEIGHT     1
#define TIP_LINE_SRC_X      4
#define TIP_LINE_SRC_Y      23
#define TIP_SOUL_SRC_X      12
#define TIP_SOUL_SRC_Y      34
#define TIP_HOLE_SRC_X      14
#define TIP_HOLE_SRC_Y      93

#define MAX_SPARETIME	36000000	/*10小时*/
#define MAX_SUIT_PART_COUNT 8

// 五行资源相关定义
#define WUXING_ELEMENT_WIDTH 138
#define WUXING_ELEMENT_HEIGHT 35

// 灵魂铭刻描述前的基本属性字串长度统一为12
#define SOULSTAMP_CHAR_LEN_AHEAD    12

#define SHOW_LOCK_PATH "Data\\Ui\\Icon\\ShowIconLock.dds"
#define SHOW_UNLOCK_PATH "Data\\Ui\\Icon\\ShowIconUnLock.dds"
#define SHOW_CANTUSE_PATH "Data\\Ui\\Icon\\ItemCantUse.dds"
#define MOUSETIP_PICPATH "Data\\Ui\\Icon\\ItemMouseTip.dds"
#define SOUL_PICPATH "Data\\Ui\\Icon\\Hun.dds"

const int g_nMouseOffsetWidth = 15;
const int g_nMouseOffsetHeight = 15;

extern char* ItemDefine::g_szSexType[];
extern int g_nTheRoleProfession;
extern CHeroGame theHeroGame;

static const int s_nProduceSkillsCount = 9;
static const int s_ProduceSkillIds[s_nProduceSkillsCount] =
{
    ItemDefine::eCSI_CaiYao,
    ItemDefine::eCSI_CaiKuang,
    ItemDefine::eCSI_BuChong,
    ItemDefine::eCSI_DuanZao,
    ItemDefine::eCSI_ZhuJia,
    ItemDefine::eCSI_GongYi,
    ItemDefine::eCSI_LianYao,
    ItemDefine::eCSI_XunMa,
    ItemDefine::eCSI_ZhuBao,
};

int CaculateSkillPointMax( int nCurrent )
{
	int nResult = 0;
	for( int i = 0 ; i < nCurrent ; ++ i )
	{
		nResult += 50 + 25 * i ;
	}
	return nResult * 2;
}

//added by ZhuoMeng.Hu		[9/28/2010]
const char* GetMPTypeString( int nProfession )
{
	//统一成消耗魔法
/*
    switch( nProfession )
    {
    case EArmType_Warrior:
        return theXmlString.GetString( eTip_sAddFPMax );
        break;
    case EArmType_Mage:
    case EArmType_Taoist:
        return theXmlString.GetString( eTip_sAddMPMax );
        break;
    case EArmType_Assassin:
        return theXmlString.GetString( eTip_sAddEPMax );
        break;
    case EArmType_Hunter:
        return theXmlString.GetString( eTip_sAddAPMax );
        break;
    case EArmType_Sniper:
        return theXmlString.GetString( eTip_sAddBPMax );
        break;
    }
*/
    return theXmlString.GetString( eTip_sAddMPMax );
}

S_IconInfoHero::S_IconInfoHero()
{
	Clear();
	m_nCount = 1;
	m_bItemLocked = 0;
    m_bItemCanTrade = true;
    m_bItemCanBeUsed = true;
    m_bEnableUsableEff = true;

	m_strIconBigImageFilename = "";
	m_ucIconSize = TILE_SIZE;
	m_usIconImageRow = 0;
	m_usIconImageColumn = 0;
}

bool S_IconInfoHero::IsNull()
{
	if ( m_stItem.itembaseinfo.ustItemID == InvalidLogicNumber
		/*m_stItem.guid == GUID_NULL*/)
	{
		return true;
	}
	return false;
}

void S_IconInfoHero::Clear()
{
	S_IconInfoBase::Clear();
	memset( &m_stItem, 0, sizeof(m_stItem) );
	m_stItem.itembaseinfo.ustItemID = InvalidLogicNumber;
	m_nCount = 1;
	m_nCost = 0;
	m_nMaxCount = -1;
	m_bLocked = false;
	m_dwSpareTime = 0;
	m_dwSpareStartTime = 0;
	m_bNextLvl = false;

	memset( &m_stCompareItem, 0, sizeof(m_stCompareItem) );
	m_stCompareItem.itembaseinfo.ustItemID = InvalidLogicNumber;
}

int& S_IconInfoHero::MaxCount()
{
	return m_nMaxCount;
}

bool& S_IconInfoHero::IsNextLvl()
{
	return m_bNextLvl;
}

DWORD& S_IconInfoHero::SpareTime()
{
	return m_dwSpareTime;
}

DWORD S_IconInfoHero::GetSpareTime()
{
	DWORD nPass = HQ_TimeGetTime() - m_dwSpareStartTime;
	DWORD nTime = 0;
	if (SpareTime() > nPass)
	{
		nTime = SpareTime() - nPass;
	}
	else
		nTime = 0;

	return nTime;
}

void S_IconInfoHero::SetSpareTime(DWORD dwSpareTime, int nStartTime )
{
	SpareTime() = dwSpareTime;
	m_dwSpareStartTime = nStartTime;
}

unsigned short& S_IconInfoHero::Id()
{
	return m_stItem.itembaseinfo.ustItemID;
}

int& S_IconInfoHero::Count()
{
	return m_nCount;
}
bool& S_IconInfoHero::IsLocked()
{
	return m_bLocked;
}
int S_IconInfoHero::Cost()
{
	return m_nCost;
}

bool S_IconInfoHero::SetData( const int nId,
							 const int nCount, 
							 const bool bShowCount /* = false */, 
							 const bool bNext /* = false */, 
							 IN INT nCompareId /* = ErrorUnsignedShortID */,
							 int nPlayerID /*= -1*/,
							 const bool bIsBound /*= false*/ )
{
	SCharItem stItem;
	memset( &stItem, 0, sizeof(stItem) );
	stItem.itembaseinfo.ustItemID = nId;
	stItem.equipdata.usHP = -1;
	for( int i = 0 ; i < SCharItem::EConstDefine_BaseRandMaxCount; ++ i )
		stItem.equipdata.baseRands[i] = InvalidLogicNumber;
    for( int i = 0 ; i < SCharItem::EConstDefine_PurpleRandMaxCount; ++i )
        stItem.equipdata.purpleRands[i] = InvalidLogicNumber;

	ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );
	if ( !pItemDetail )
	{
		return false;
	}

    // 装备有随机属性和鎏金属性
    if( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_WEAPON || pItemDetail->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
    {
        ItemDefine::SItemCanEquip* pEquip = ( ItemDefine::SItemCanEquip* )pItemDetail;
        for( int loop = 0; loop < ItemDefine::SItemCanEquip::ECD_AdditiveRandAttrCount; ++loop )
        {
//             if( loop < pEquip->additiveRandCount && pEquip->additiveRandFlags[loop] && pEquip->additiveRandValues[loop] > 0 )
//                 stItem.equipdata.baseRands[loop] = pEquip->additiveRandValues[loop];
//             else
                stItem.equipdata.baseRands[loop] = 0;
        }
        for( int loop = 0; loop < ItemDefine::SItemCanEquip::ECD_PurpleRandAttrCount; ++loop )
        {
//             if( loop < pEquip->purpleRandCount && pEquip->purpleRandFlags[loop] && pEquip->purpleRandValues[loop] > 0 )
//                 stItem.equipdata.purpleRands[loop] = pEquip->purpleRandValues[loop];
//             else
                stItem.equipdata.purpleRands[loop] = 0;
        }
    }

	if (pItemDetail->ucItemType == ItemDefine::ITEMTYPE_STATUS)
	{
		ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus( nId, nCount );
		if(pStatus)
		{
			if (pStatus->iDurationTime < 0 && !pStatus->IsForeverStatus() )
			{
				return false;
			}
		}
	}
	// AutoRestore
	else if ( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_RESTORE )
	{
		ItemDefine::SItemRestore* restore = (ItemDefine::SItemRestore*)pItemDetail;
		if ( restore->bHPAuto )
			stItem.itembaseinfo.value2 = restore->dwAddHP;
		else if ( restore->bMPAuto )
			stItem.itembaseinfo.value2 = restore->dwAddMP;
	}
	else if (pItemDetail->ucItemType == ItemDefine::ITEMTYPE_SKILL)
	{
		stItem.itembaseinfo.ustItemCount = nCount; // 技能不用显示个数，ustItemCount < 0表示为学习
	}

	if ( !pItemDetail->IsExclusive() || bShowCount == true )
	{
		stItem.itembaseinfo.ustItemCount = nCount;
	}

	if ( bIsBound ) //特殊需要绑定时才在这里设置绑定，比如商城的积分商城和绑金商城，否则按配置文件里的来
	{
		stItem.SetBounded( true );
	}

	return SetData( &stItem, bShowCount, bNext, NULL, nPlayerID );
}

#define SET_COLOR(n)									\
	if ( n < 30 )										\
	m_stInfo[m_ucIconInfoLine].m_col = 0xFFFFAA00;	\
	else if ( n < 60 )									\
	m_stInfo[m_ucIconInfoLine].m_col = 0xFFFF7f00;	\
	else												\
	m_stInfo[m_ucIconInfoLine].m_col = 0xFFFF5500;


float S_IconInfoHero::GetAttributeWithLevel( int nEquipType, float fAttribute, short stLevel )
{	
	return theStarLevelUpConfig.GetItemStarLevelModulus( nEquipType, stLevel ) * fAttribute;
}

int S_IconInfoHero::GetAttributeWithLevel( int nEquipType, int nAttribute, short stLevel )
{
	return theStarLevelUpConfig.GetItemStarLevelModulus( nEquipType, stLevel ) * nAttribute;
}

extern char* (g_szProfessionType[]);

//Define
#define ITEM_SHOW_INT_ONLYCPY( x, str ) if( x > 0 ) \
{ \
	sprintf_s( szTemp, 256, "%s %s+%d", szTemp, str, x );\
}

#define ITEM_SHOW_FLOAT_ONLYCPY( x, str )		if(x > 0.0f) \
{	\
	sprintf( szTemp, "%s %s%0.1f",szTemp, str, x );	\
}

#define ITEM_SHOW_INT(x, str, col)		if(x > 0) \
{									\
	sprintf( szTemp, "%s+%d",str, x );	\
	m_stInfo[m_ucIconInfoLine].m_col = col;	\
	m_stInfo[m_ucIconInfoLine++].m_strInfo = szTemp;	\
}
#define ITEM_SHOW_INT_PRETEXT(x, str, col)		if(x > 0) \
{									\
	sprintf( szTemp, "%s%s+%d",theXmlString.GetString( eTip_PreText_Normal ), str, x );	\
	m_stInfo[m_ucIconInfoLine].m_col = col;	\
	m_stInfo[m_ucIconInfoLine++].m_strInfo = szTemp;	\
}
#define ITEM_SHOW_INT_PER(x, str, col)		if(x > 0) \
{									\
	sprintf( szTemp, "%s: +%d%%",str, x );	\
	m_stInfo[m_ucIconInfoLine].m_col = col;	\
	m_stInfo[m_ucIconInfoLine++].m_strInfo = szTemp;	\
}

#define ITEM_SHOW_FLOAT_PRETEXT(x, str, col)		if(x > 0.0f) \
{	\
	sprintf( szTemp, "%s%s%0.1f",theXmlString.GetString( eTip_PreText_Normal ), str, x );	\
	m_stInfo[m_ucIconInfoLine].m_col = col;	\
	m_stInfo[m_ucIconInfoLine++].m_strInfo = szTemp;	\
}

#define ITEM_SHOW_FLOAT(x, str, col)		if(x > 0.0f) \
{	\
	sprintf( szTemp, "%s%0.1f",str, x );	\
	m_stInfo[m_ucIconInfoLine].m_col = col;	\
	m_stInfo[m_ucIconInfoLine++].m_strInfo = szTemp;	\
}
#define ITEM_SHOW_BOOL(x, str)	if(x) \
{	\
	sprintf( szTemp, "%s %s",str, x? theXmlString.GetString(eUI_Yes): theXmlString.GetString(eUI_NO) );	\
	m_stInfo[m_ucIconInfoLine++].m_strInfo = szTemp;	\
}
#define ITEM_SHOW_STRING(x, str, str1)	if(x!=0) \
{	\
	sprintf( szTemp, "%s %s",str,str1 );	\
	m_stInfo[m_ucIconInfoLine++].m_strInfo = szTemp;	\
}

#define SHOW_STRING(str, col )				\
{												\
	m_stInfo[m_ucIconInfoLine].m_strInfo = str;	\
	m_stInfo[m_ucIconInfoLine].m_col = col;		\
	m_ucIconInfoLine++;							\
}

#define SET_EQUIP(str, n, col)		\
	sprintf( szTemp, str, n);	\
	m_stInfo[m_ucIconInfoLine].m_strInfo = szTemp;	\
	m_stInfo[m_ucIconInfoLine].m_col = col;		\
	m_ucIconInfoLine++;
//Define
#define SET_EQUIPNotParam(str, col)	\
	m_stInfo[m_ucIconInfoLine].m_strInfo = str;\
	m_stInfo[m_ucIconInfoLine].m_col = col;\
	m_ucIconInfoLine++;

#define SET_EQUIPEX(cx, cy, str, n, col, elsecol)											\
	if( cx < cy )												\
{															\
	sprintf( szTemp, str, n);								\
	m_stInfo[m_ucIconInfoLine].m_strInfo = szTemp;			\
	m_stInfo[m_ucIconInfoLine].m_col = col;					\
	m_ucIconInfoLine++;										\
}															\
								else														\
{															\
	if( cy !=0 )											\
{														\
	sprintf( szTemp, str, n);						\
	m_stInfo[m_ucIconInfoLine].m_strInfo = szTemp;	\
	m_stInfo[m_ucIconInfoLine].m_col = elsecol;		\
	m_ucIconInfoLine++;								\
}												\
}

#define SET_EQUIPEX_STRING(cx, cy, str, _str, _n,  col, elsecol)										\
	if( cx < cy )												\
{															\
	sprintf( szTemp, str, _str, _n );								\
	m_stInfo[m_ucIconInfoLine].m_strInfo = szTemp;			\
	m_stInfo[m_ucIconInfoLine].m_col = col;					\
	m_ucIconInfoLine++;										\
}															\
							else														\
{															\
	if( cy !=0 )											\
{														\
	sprintf( szTemp, str, _str, _n );							\
	m_stInfo[m_ucIconInfoLine].m_strInfo = szTemp;		\
	m_stInfo[m_ucIconInfoLine].m_col = elsecol;			\
	m_ucIconInfoLine++;									\
}														\
}

#define SHOW_LINE()				\
{												\
	m_stInfo[m_ucIconInfoLine].m_bImage = true;	\
	m_stInfo[m_ucIconInfoLine].m_bIcon = false;	\
	m_stInfo[m_ucIconInfoLine].m_bNewLine = false;	\
	m_stInfo[m_ucIconInfoLine].m_eImageAlignMode = stIconInfoEx::eIIIA_Middle;	\
	m_stInfo[m_ucIconInfoLine].m_nImageID = -1;	\
	m_stInfo[m_ucIconInfoLine].m_strImage = "data/Ui/Common/line.tga";	\
	m_stInfo[m_ucIconInfoLine].m_usImageWidth = 256;	\
	m_stInfo[m_ucIconInfoLine].m_usImageHeight = 8;	\
	m_stInfo[m_ucIconInfoLine].m_usSrcX = 0; \
	m_stInfo[m_ucIconInfoLine].m_usSrcY = 0; \
	m_stInfo[m_ucIconInfoLine].m_col = 0xffffffff;	\
	m_ucIconInfoLine++;	\
}

void S_IconInfoHero::SetInfoRightText()
{
	ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( m_stItem.itembaseinfo.ustItemID );
	int nType = pItemDetail->ucItemType;
	if( nType == ItemDefine::ITEMTYPE_STATUS )
		return;

	m_stInfo[m_ucIconInfoLine].m_bIconRightText = true;
	m_stInfo[m_ucIconLine].m_ucRightRowCount++;
}

void S_IconInfoHero::ShowBaseInfo( void* pItemDetail, INT nType )
{
	ItemDefine::SItemCommon *pItem = NULL;

	if( pItemDetail )
	{
		pItem = ( ItemDefine::SItemCommon* )pItemDetail;
	}
    else
    {
        return;
    }

    char szTemp [MAX_PATH] = {0};
    DWORD dwDefColor = 0xffffffff;

	//////////////////////////////////
	// 物品名称 (按品质)
	if( pItemDetail )
	{
		if( m_stItem.itembaseinfo.ustItemID != CompoundItemID && pItem != NULL )
		{				
			Common::_tstring tstrName( pItem->GetItemName() );
			ReplaceSpecifiedName( pItem->ustLevel, tstrName );
			strncpy( szTemp, tstrName.c_str(), MAX_PATH - 1 );
		}
	}

    // 品质可能是提升后的，也可能是读表的
    int nQuality = m_stItem.equipdata.quality;
    nQuality = nQuality == 0 ? pItem->ustLevel : nQuality;
    DWORD dwNameColor = GetQualityColor( nQuality );

    if( pItemDetail )
    {
        switch( nType )
        {
        case ItemDefine::ITEMTYPE_WEAPON:
        case ItemDefine::ITEMTYPE_ARMOUR:
            {
                if( m_stItem.itembaseinfo.ustItemID != CompoundItemID )
				{
					if(!m_stItem.HasBaseRanded())
					{
						char szText[256] = {0};
						//MeSprintf_s(szText,sizeof(szText),"%s%s",szTemp,"(未鉴定)");
						MeSprintf_s(szText,sizeof(szText),"%s",szTemp);
                        m_stInfo[m_ucIconInfoLine].m_strInfo = szText;	
					}
					else
					{
						m_stInfo[m_ucIconInfoLine].m_strInfo = szTemp;
						if (m_stItem.equipdata.ucLevel>0)
						{
							char tempLv[128] = {0};
							sprintf_s(tempLv,sizeof(tempLv)/sizeof(char),"+%d",m_stItem.equipdata.ucLevel);
							m_stInfo[m_ucIconInfoLine].m_strInfo += tempLv;
						}
                        
					}
				}
            }
            break;
        case ItemDefine::ITEMTYPE_SKILL:
			{
				std::ostringstream ss;
				ss << pItem->GetItemName();

				ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( m_stItem.itembaseinfo.ustItemID, 
					m_stItem.itembaseinfo.ustItemCount < 1 ? 1 : m_stItem.itembaseinfo.ustItemCount );
				if(pSkill)
					ss << "(" << theXmlString.GetString(eText_Level) << pSkill->ustLevel << ")";

				m_stInfo[m_ucIconInfoLine].m_strInfo = ss.str();
				dwNameColor = Color_Config.getColor( CC_ItemTip_SkillName );
			}
			break;
        case ItemDefine::ITEMTYPE_STATUS:
        case ItemDefine::ITEMTYPE_ACTION:
            {
                m_stInfo[m_ucIconInfoLine].m_strInfo = pItem->GetItemName();
                dwNameColor = Color_Config.getColor( CC_ItemTip_SkillName );
            }
            break;
        default:
            {
                m_stInfo[m_ucIconInfoLine].m_strInfo = pItem->GetItemName();
            }
            break;
        }
    }
    m_stInfo[m_ucIconInfoLine].m_col = dwNameColor;
	if (nType != ItemDefine::ITEMTYPE_ARMOUR && nType != ItemDefine::ITEMTYPE_WEAPON && nType != ItemDefine::ITEMTYPE_RESTORE)
	{
		m_stInfo[m_ucIconInfoLine].m_dwTextAlign = DT_CENTER;
		m_ucIconInfoLine++;
	}


    // 非状态则显示图标
	if( nType != ItemDefine::ITEMTYPE_STATUS )
	{
		m_stInfo[m_ucIconInfoLine].m_bImage = true;
		m_stInfo[m_ucIconInfoLine].m_bIcon = true;
		m_stInfo[m_ucIconInfoLine].m_bNewLine = false;
		m_stInfo[m_ucIconInfoLine].m_eImageAlignMode = stIconInfoEx::eIIIA_Left;
		m_stInfo[m_ucIconInfoLine].m_nImageID = m_nIconPicId;
		m_stInfo[m_ucIconInfoLine].m_strImage = IconFileName().c_str();
		m_stInfo[m_ucIconInfoLine].m_usImageWidth = TIP_ICON_SIZE;
		m_stInfo[m_ucIconInfoLine].m_usImageHeight = TIP_ICON_SIZE;
		m_stInfo[m_ucIconInfoLine].m_usImageRow = m_usIconImageRow;
		m_stInfo[m_ucIconInfoLine].m_usImageColumn = m_usIconImageColumn;	
		m_stInfo[m_ucIconInfoLine].m_col = dwDefColor;
		m_stInfo[m_ucIconInfoLine].m_ucRightRowCount = 0;
		m_ucIconLine = m_ucIconInfoLine;
		
		m_ucIconInfoLine++;
	}

	if (nType == ItemDefine::ITEMTYPE_ARMOUR || nType == ItemDefine::ITEMTYPE_WEAPON || nType == ItemDefine::ITEMTYPE_RESTORE)
	{
		SetInfoRightText();
		SET_EQUIP( "%s", m_stInfo[m_ucIconInfoLine-1].m_strInfo.c_str(), dwNameColor );
	}

	bool bMoveStar = false;
	bool bCheckUp = false;
	if( nType == ItemDefine::ITEMTYPE_CHECKUP && pItemDetail )
	{
		ItemDefine::SItemCheckUp *pItemCheckUp = (ItemDefine::SItemCheckUp*)pItemDetail;
		if( pItemCheckUp->stCheckUpType == ItemDefine::SItemCheckUp::ECD_MoveStar )
			bMoveStar = true;
		else
			bCheckUp = true;
	}
	// 绑定
	//char szText[64] = {0};
	//MeSprintf_s(szText,sizeof(szText),"当前位置为:%d flag_1为:%d,运算结果为:%d \n",m_stItem.itembaseinfo.stPacketIdx,m_stItem.itembaseinfo.flag,_HAS_FLAG( m_stItem.itembaseinfo.flag, SCharItem::EEquipDataFlagType_Bounded  ));
	//::OutputDebugStr(szText);
	if (nType == ItemDefine::ITEMTYPE_ARMOUR || nType == ItemDefine::ITEMTYPE_WEAPON || nType == ItemDefine::ITEMTYPE_RESTORE)
	{
		
	}
	else
	{
		if (m_stItem.IsBounded())//已绑定
		{
			//char szText[64] = {0};
			//MeSprintf_s(szText,sizeof(szText),"当前位置为:%d flag_2为:%d,运算结果为:%d \n",m_stItem.itembaseinfo.stPacketIdx,m_stItem.itembaseinfo.flag,_HAS_FLAG( m_stItem.itembaseinfo.flag, SCharItem::EEquipDataFlagType_Bounded  ));
			//::OutputDebugStr(szText);
			SHOW_STRING(theXmlString.GetString(eTip_BelongerDone), Color_Config.getColor( CC_ItemTip_ItemBind ) );
		}
		else if( pItem )
		{
			if ( ( nType == ItemDefine::ITEMTYPE_ARMOUR || nType == ItemDefine::ITEMTYPE_WEAPON  || nType == ItemDefine::ITEMTYPE_TREASUREBOX 
				|| bMoveStar ) && pItem->bIsCanBound )
			{			
				if( !pItem->bIsCanTrade )
				{
					if (m_stItem.itembaseinfo.stPacketIdx != -1 ) //背包index不为-1说明在包里
					{
						SHOW_STRING(theXmlString.GetString(eTip_BelongerDone), Color_Config.getColor( CC_ItemTip_ItemBind ) );
					}
					else
					{					
						SHOW_STRING(theXmlString.GetString(eTip_PickBound), Color_Config.getColor( CC_ItemTip_ItemBind ) );
					}
				}
				else
				{
					if (!bMoveStar)
					{
						SHOW_STRING(theXmlString.GetString(eText_Title_Bound), Color_Config.getColor( CC_ItemTip_ItemBind ) );
					}
					else
					{
						SHOW_STRING(theXmlString.GetString( eText_Bind_ByStarMove ), Color_Config.getColor( CC_ItemTip_ItemBind ) ); // 移星后绑定
					}
				}
			}	
			else if( nType == ItemDefine::ITEMTYPE_MATERIAL ||
				nType == ItemDefine::ITEMTYPE_RESTORE ||
				nType == ItemDefine::ITEMTYPE_GEM ||
				nType == ItemDefine::ITEMTYPE_TASK ||
				nType == ItemDefine::ITEMTYPE_REEL ||
				bCheckUp ||
				nType == ItemDefine::ITEMTYPE_GUILD ||
				nType == ItemDefine::ITEMTYPE_OTHER )
			{
				if( !pItem->bIsCanTrade )
				{
					if (m_stItem.itembaseinfo.stPacketIdx != -1 ) //背包index不为-1说明在包里
					{
						//SetInfoRightText();
						SHOW_STRING(theXmlString.GetString(eTip_BelongerDone), Color_Config.getColor( CC_ItemTip_ItemBind ) );
					}
					else
					{
						//SetInfoRightText();
						SHOW_STRING(theXmlString.GetString(eTip_PickBound), Color_Config.getColor( CC_ItemTip_ItemBind ) );
					}
				}			
			}
		}
		if(pItem->IsCanEquip())
		{
			//判断当前物品的解绑状态处理
			ItemDefine::SItemCanEquip * pEquip = (ItemDefine::SItemCanEquip*)pItem;
			if(pEquip && m_stItem.itembaseinfo.nOnlyInt != 0)
			{
				/*if((m_stItem.equipdata.unBindCount == 0xFFFF && pEquip->unBindCount !=0xFFFF) || (m_stItem.equipdata.unBindCount != 0xFFFF && pEquip->unBindCount ==0xFFFF))
				{
					m_stItem.equipdata.unBindCount = pEquip->unBindCount;
				}*/
				if(m_stItem.equipdata.unBindCount == 0xFFFF && pEquip->unBindCount !=0xFFFF)
				{
					m_stItem.equipdata.unBindCount = pEquip->unBindCount;
				}
				if(m_stItem.equipdata.unBindCount == 0xFFFF)
				{
					SHOW_STRING(theXmlString.GetString(eText_UnBind), Color_Config.getColor( CC_PetColor_Red ) );
				}
				else if(m_stItem.equipdata.unBindCount == 0)
				{
					SHOW_STRING(theXmlString.GetString(eText_UnBind_Non), Color_Config.getColor( CC_PetColor_Red ) );
				}
				else
				{
					char szText[256] = {0};
					sprintf_s(szText, sizeof(szText)-1,theXmlString.GetString(eText_UnBind_Num),m_stItem.equipdata.unBindCount);
					SHOW_STRING(szText,Color_Config.getColor( CC_PetColor_Red ) );
				}
			}
		}
	}

	// 灵魂铭刻
    if( m_stItem.IsSoulStamp() )
    {
        m_stInfo[m_ucIconInfoLine].m_bImage = true;
        m_stInfo[m_ucIconInfoLine].m_bIcon = false;
        m_stInfo[m_ucIconInfoLine].m_bNewLine = true;
        m_stInfo[m_ucIconInfoLine].m_eImageAlignMode = stIconInfoEx::eIIIA_Right;
        m_stInfo[m_ucIconInfoLine].m_nImageID = -1;
        m_stInfo[m_ucIconInfoLine].m_strImage = SOUL_PICPATH;
        m_stInfo[m_ucIconInfoLine].m_usImageWidth = gCfg.m_nSoulPicWidth;
        m_stInfo[m_ucIconInfoLine].m_usImageHeight = gCfg.m_nSoulPicHeight;
        m_stInfo[m_ucIconInfoLine].m_usSrcX = 0/*TIP_SOUL_SRC_X*/;
        m_stInfo[m_ucIconInfoLine].m_usSrcY = 0/*TIP_SOUL_SRC_Y*/;
        m_stInfo[m_ucIconInfoLine].m_col = dwDefColor;
        m_ucIconInfoLine++;
    }
	
	// 称号限制
	if( pItem && ( nType == ItemDefine::ITEMTYPE_ARMOUR || nType == ItemDefine::ITEMTYPE_WEAPON ) )
	{
		ItemDefine::SItemCanEquip* pCanEquip = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID(pItem->ustItemID);
		if( pCanEquip && pCanEquip->nTitleNeed != 0 )
		{
			TitleConfig::Title* pTitle = theTitleConfig.GetTitleByTitleID(pCanEquip->nTitleNeed);

			// 判断是否有该称号
			bool bHasTitle = false;
			DWORD dwColor = Color_Config.getColor( CC_ItemTip_Require_NotReach );
			std::vector< TitleData > vCurrentTitleIds = thePlayerRole.GetTitleArray();
			std::vector<TitleData>::iterator it = vCurrentTitleIds.begin();

			for (;it != vCurrentTitleIds.end();++it)
			{
				if((*it).GetTitleID() == pTitle->GetID())
				{
					bHasTitle = true;
					dwColor = Color_Config.getColor( CC_ItemTip_Require_Reach );
					break;
				}
			}
			
			if( pTitle && pTitle->GetName() )
			{
				char szText[256] = {0};
				sprintf_s(szText, sizeof(szText)-1, "%s%s", theXmlString.GetString(eText_EquipLimit), pTitle->GetName());
				
				SHOW_STRING( szText, dwColor );
			}
		}
	}

	// 显示道具类型
    const DWORD dwItemTypeColor = Color_Config.getColor( CC_ItemTip_ItemType );
	switch(nType) 
	{
	case ItemDefine::ITEMTYPE_GUILD:
		{
            SetInfoRightText();
            SHOW_STRING( theXmlString.GetString( eText_Tip_GuildItem ), dwItemTypeColor );
			break;
		}
	case ItemDefine::ITEMTYPE_MATERIAL:
		{
            SetInfoRightText();
            SHOW_STRING( theXmlString.GetString( eText_IT_MATERIAL ), dwItemTypeColor );
			break;
		}
	case ItemDefine::ITEMTYPE_RESTORE:
		{
            SetInfoRightText();
            SHOW_STRING( theXmlString.GetString( eText_IT_RESTORE ), dwItemTypeColor );
			break;
		}
	case ItemDefine::ITEMTYPE_GEM:
		{
            SetInfoRightText();
            SHOW_STRING( theXmlString.GetString( eText_IT_GEM ), dwItemTypeColor );
			break;
		}		
	case ItemDefine::ITEMTYPE_TASK:
		{
            SetInfoRightText();
            SHOW_STRING( theXmlString.GetString( eText_IT_TASK ), dwItemTypeColor );
			break;
		}
	case ItemDefine::ITEMTYPE_REEL:
		{
            SetInfoRightText();
            SHOW_STRING( theXmlString.GetString( eText_IT_Reel ), dwItemTypeColor );
			//m_stInfo[m_ucIconInfoLine].m_strInfo = theXmlString.GetString(eText_IT_Reel);
			//m_stInfo[m_ucIconInfoLine].m_col = dwItemTypeColor;
			//m_ucIconInfoLine++;
			break;
		}
	case ItemDefine::ITEMTYPE_CHECKUP:
		{
			if( bMoveStar )
			{
				// 星级
				if( m_stItem.equipdata.ucLevel <= 9 )
					sprintf_s( szTemp, sizeof(szTemp)/sizeof(char) -1, "#100%d", (int)m_stItem.equipdata.ucLevel );
				else
					sprintf_s( szTemp, sizeof(szTemp)/sizeof(char) -1, "#130%d", (int)m_stItem.equipdata.ucLevel-10 );

				m_stInfo[m_ucIconInfoLine].m_bImage = false;
				m_stInfo[m_ucIconInfoLine].m_bGif = false;//true;
				m_stInfo[m_ucIconInfoLine].m_usImageHeight = 16;
				m_stInfo[m_ucIconInfoLine].m_usImageWidth = 144;
				m_stInfo[m_ucIconInfoLine].m_strImage = szTemp;
				m_stInfo[m_ucIconInfoLine].m_usImageColumn = 0;
				m_stInfo[m_ucIconInfoLine].m_usImageRow = (int)m_stItem.equipdata.ucLevel;
				m_stInfo[m_ucIconInfoLine].m_nImageID = -1;
				m_stInfo[m_ucIconInfoLine].m_col = dwDefColor;
				m_ucIconInfoLine++;
			}
			break;
		}
	default:
		break;
	}

	/*
	 * Author: 2013-1-22 9:55:47 wangshuai
	 * Desc:   DEBUG下显示物品ID
	 */
#ifdef _DEBUG	
	sprintf( szTemp, "item id: %d\n", pItem->ustItemID);
	SHOW_STRING( szTemp, 0xffff0000 );
#endif
	return;
	unguard;
}

void S_IconInfoHero::ShowEquipCommon( void* pItemDetail, INT nType )
{
	char szTemp [256] = {0};
	if( nType != ItemDefine::ITEMTYPE_WEAPON && nType != ItemDefine::ITEMTYPE_ARMOUR )
        return;

    ItemDefine::SItemCanEquip* pEquip = NULL;
    if( pItemDetail )
    {
        pEquip = (ItemDefine::SItemCanEquip*)pItemDetail;
    }
    else
    {	
        return;
    }

    INT	nHPMax = pEquip->stHPMax;
    int nCurrHP = ceil( m_stItem.equipdata.usHP );		
    if ( nCurrHP < 0 )
    {
        nCurrHP = nHPMax;
    }

    //////////////////////////////////////////////////////////////////////////
    // 图表右侧文字: 职业,性别,等级
    const DWORD dwReqReachColor = Color_Config.getColor( CC_ItemTip_Require_Reach );
    const DWORD dwReqUnReachColor = Color_Config.getColor( CC_ItemTip_Require_NotReach );
    const DWORD dwDefColor = 0xffffffff;

    //职业需求
    for( int i = 0; i < PLAYERPROFESSION; ++i )
        m_nProfession[i] = 0;
    BOOL bIsAllProfession = FALSE;
    INT nProCnt = 0;

    for( int i=0; i< PLAYERPROFESSION; i++ )
    {
        if( pEquip->arrayEquipArmsReq[i] )
        {
            nProCnt++;
            m_nProfession[i] = 1;
        }
        else
            m_nProfession[i] = 0;
    }
    if( nProCnt == PLAYERPROFESSION )
    {
        bIsAllProfession = true;
    }
    
    if( !bIsAllProfession )
    {
        //SetInfoRightText();
        char szProfession[128] = {0};
        char szProfessionTemp[10] = {0};

        BOOL bIsFirst = true;
        for(int n = 0; n < PLAYERPROFESSION; n++ )
        {
            if( m_nProfession[n] == 1 )
            {
                switch( n )
                {
                case EArmType_Mage:
                    if ( bIsFirst )
                    {
                        strcpy( szProfession, theXmlString.GetString( eProfession_Mage ) );
                        bIsFirst = false;
                    }
                    else
                    {
                        strcpy( szProfessionTemp," " );
                        HelperFunc::AddNCpy( szProfessionTemp, theXmlString.GetString( eProfession_Mage ),sizeof( szProfessionTemp ) );									
                        HelperFunc::AddNCpy( szProfession, szProfessionTemp, sizeof( szProfession ) );
                    }
                    break;
                case EArmType_Taoist:
                    if ( bIsFirst )
                    {								
                        strcpy( szProfession, theXmlString.GetString( eProfession_Taoist ) );
                        bIsFirst = false;
                    }
                    else
                    {
                        strcpy( szProfessionTemp," " );
                        HelperFunc::AddNCpy( szProfessionTemp, theXmlString.GetString( eProfession_Taoist ),sizeof( szProfessionTemp ) );									
                        HelperFunc::AddNCpy( szProfession, szProfessionTemp, sizeof( szProfession ));
                    }							
                    break;
                case EArmType_Assassin:
                    if ( bIsFirst )
                    {
                        strcpy( szProfession, theXmlString.GetString( eProfession_Assassin ) );
                        bIsFirst = false;
                    }
                    else
                    {
                        strcpy( szProfessionTemp," " );
                        HelperFunc::AddNCpy( szProfessionTemp, theXmlString.GetString( eProfession_Assassin ),sizeof( szProfessionTemp ) );									
                        HelperFunc::AddNCpy( szProfession, szProfessionTemp, sizeof( szProfession ) );
                    }							
                    break;
                case EArmType_Warrior:
                    if ( bIsFirst )
                    {
                        strcpy( szProfession, theXmlString.GetString( eProfession_Warrior ) );
                        bIsFirst = false;
                    }
                    else
                    {
                        strcpy( szProfessionTemp," " );
                        HelperFunc::AddNCpy( szProfessionTemp, theXmlString.GetString( eProfession_Warrior ),sizeof( szProfessionTemp ) );									
                        HelperFunc::AddNCpy( szProfession, szProfessionTemp, sizeof( szProfession ) );
                    }						
                    break;
                case EArmType_Hunter:
                    if ( bIsFirst )
                    {
                        strcpy( szProfession, theXmlString.GetString( eProfession_Hunter ) );
                        bIsFirst = false;
                    }
                    else
                    {
                        strcpy( szProfessionTemp," " );
                        HelperFunc::AddNCpy( szProfessionTemp, theXmlString.GetString( eProfession_Hunter ),sizeof( szProfessionTemp ) );									
                        HelperFunc::AddNCpy( szProfession, szProfessionTemp, sizeof( szProfession ) );
                    }							
                    break;
                case EArmType_Sniper:
                    {
                    }
                    break;
                default:
                    break;
                }
            }						
        }
        if( m_nProfession[g_nTheRoleProfession] == 1 )
        {
            char szTemp2[256] = {0};
            sprintf_s( szTemp2,sizeof(szTemp2)/sizeof(char) - 1 ,"%s %s", theXmlString.GetString( eNeed_Profession ), szProfession );
            SET_EQUIP( "%s", szTemp2, dwReqReachColor );
        }
        else
        {
            char szTemp2[256] = {0};
            sprintf_s( szTemp2,sizeof(szTemp2)/sizeof(char) - 1, "%s %s", theXmlString.GetString( eNeed_Profession ), szProfession );
            SET_EQUIP( "%s", szTemp2, dwReqUnReachColor );
        }

    }/*
     else
     {
     ItemDefine::SItemCommon *pItemCommon = NULL;
     if( pItemDetail )
     pItemCommon = (ItemDefine::SItemCommon *)pItemDetail;
     else
     pItemCommon = (ItemDefine::SItemCommon *)pComItemDetail;

     bool bSet = false;
     if ( pItemCommon && pItemCommon->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
     {
     ItemDefine::SItemArmour* pItemArmour = (ItemDefine::SItemArmour*)pItemCommon;

     if( pItemArmour->IsSuitEquip() )
     {
     // 判断技能套 或者 五行套
     if ( pItemArmour->IsSkillSuitEquip() )
     {
     SET_EQUIP( "%s", theXmlString.GetString(eText_SkillSuitArmour), WHITE_COLOR );
     bSet = true;
     }
     else if ( pItemArmour->IsElementSuitEquip() )
     {
     SET_EQUIP( "%s", theXmlString.GetString(eText_ElementSuitArmour), WHITE_COLOR );
     bSet = true;
     }
     }
     }
     if( !bSet )
     SET_EQUIP( "%s", theXmlString.GetString(eText_AllPro), WHITE_COLOR );
     }*/
    // 性别需求
    char szSex[128] = {0};
    BOOL bNeedShowSex = true;
    switch( pEquip->cEquipSexReq )
    {
    case -1:
        bNeedShowSex = false;
        break;
    case Sex_Male:
        sprintf_s( szSex,sizeof(szSex)/sizeof(char) - 1, "%s", theXmlString.GetString( eSex_Man ) );
        break;
    case Sex_Female:
        sprintf_s( szSex,sizeof(szSex)/sizeof(char) - 1, "%s", theXmlString.GetString( eSex_FeMan ) );
        break;
    default:
        bNeedShowSex = false;
        break;
    }
    if( bNeedShowSex )
    {
        SetInfoRightText();
        if( pEquip->cEquipSexReq  == thePlayerRole.GetSex() )
        {
            char szTempSex[256] = {0};
            char szTemp[256] = {0};
            sprintf_s( szTempSex,sizeof(szTempSex)/sizeof(char) - 1, "%s %s", theXmlString.GetString(eUI_NeedSex), szSex );
            SET_EQUIP( "%s", szTempSex, dwReqReachColor );
        }
        else
        {
            char szTempSex[256] = {0};						
            char szTemp[256] = {0};
            sprintf_s( szTempSex,sizeof(szTempSex)/sizeof(char) - 1, "%s %s", theXmlString.GetString(eUI_NeedSex), szSex );
            SET_EQUIP( "%s", szTempSex, dwReqUnReachColor );
        }
    }
    //级别需求
    SetInfoRightText();
    SET_EQUIPEX_STRING(
        thePlayerRole.GetLevel(),
        pEquip->stEquipLevelReq,
        "%s %d",
        theXmlString.GetString( eUI_NeedLevel ),
        ( INT )pEquip->stEquipLevelReq, 
        dwReqUnReachColor, 
        dwReqReachColor );
    //////////////////////////////////////////////////////////////////////////
    // 图表下方文字: 耐久
    sprintf( szTemp, "%s %d/%d", theXmlString.GetString(eEquip_Durable), nCurrHP, nHPMax );		
	if (!pEquip->bFashion)
	{
		SetInfoRightText();
		//时装不显示耐久度   liaojie
		m_stInfo[m_ucIconInfoLine].m_strInfo = szTemp;
		if( nCurrHP > 0 )
			m_stInfo[m_ucIconInfoLine].m_col = Color_Config.getColor( CC_ItemTip_Endure_Nonzero );
		else
			m_stInfo[m_ucIconInfoLine].m_col = Color_Config.getColor( CC_ItemTip_Endure_Zero );
		m_ucIconInfoLine++;	
	}

	//
	ItemDefine::SItemCommon* pItem = ( ItemDefine::SItemCommon* )pItemDetail;
	m_stInfo[m_ucIconInfoLine].m_strInfo.clear();

	if (m_stItem.IsBounded())
	{
		m_stInfo[m_ucIconInfoLine].m_strInfo = theXmlString.GetString(eTip_BelongerDone);
	}
	else if( pItem )
	{
		if ( ( nType == ItemDefine::ITEMTYPE_ARMOUR || nType == ItemDefine::ITEMTYPE_WEAPON ) && pItem->bIsCanBound )
		{
			if( !pItem->bIsCanTrade )
			{
				if (m_stItem.itembaseinfo.stPacketIdx != -1 ) //背包index不为-1说明在包里
				{
					m_stInfo[m_ucIconInfoLine].m_strInfo = theXmlString.GetString(eTip_BelongerDone);
				}
				else
				{
					m_stInfo[m_ucIconInfoLine].m_strInfo = theXmlString.GetString(eTip_PickBound);
				}
			}
			else
			{
				m_stInfo[m_ucIconInfoLine].m_strInfo = theXmlString.GetString(eText_Title_Bound);
			}
		}
	}

	if(pItem->IsCanEquip())
	{
		ItemDefine::SItemCanEquip * pEquip = (ItemDefine::SItemCanEquip*)pItem;
		if(pEquip)
		{
			//if(m_stItem.itembaseinfo.nOnlyInt == 0)
			//{
			//	//装备实际上不存在
			//	if(pEquip->unBindCount ==0xFFFF)//可解绑
			//	{
			//		m_stInfo[m_ucIconInfoLine].m_strInfo += theXmlString.GetString(eText_UnBind);	
			//	}
			//	else if(pEquip->unBindCount ==0)
			//	{
			//		m_stInfo[m_ucIconInfoLine].m_strInfo += theXmlString.GetString(eText_UnBind_Non);
			//	}
			//	else
			//	{
			//		char szText[256] = {0};
			//		sprintf_s(szText, sizeof(szText)-1,theXmlString.GetString(eText_UnBind_Num),pEquip->unBindCount);
			//		m_stInfo[m_ucIconInfoLine].m_strInfo += szText;
			//	}
			//}
			//else
			if(m_stItem.itembaseinfo.nOnlyInt != 0)
			{
				/*if((m_stItem.equipdata.unBindCount == 0xFFFF && pEquip->unBindCount !=0xFFFF) || (m_stItem.equipdata.unBindCount != 0xFFFF && pEquip->unBindCount ==0xFFFF))
				{
					m_stItem.equipdata.unBindCount = pEquip->unBindCount;
				}*/
				if(m_stItem.equipdata.unBindCount == 0xFFFF && pEquip->unBindCount !=0xFFFF)
				{
					m_stItem.equipdata.unBindCount = pEquip->unBindCount;
				}
				if(m_stItem.equipdata.unBindCount == 0xFFFF)
				{
					m_stInfo[m_ucIconInfoLine].m_strInfo += theXmlString.GetString(eText_UnBind);
				}
				else if(m_stItem.equipdata.unBindCount == 0)
				{
					m_stInfo[m_ucIconInfoLine].m_strInfo += theXmlString.GetString(eText_UnBind_Non);
				}
				else
				{
					char szText[256] = {0};
					sprintf_s(szText, sizeof(szText)-1,theXmlString.GetString(eText_UnBind_Num),m_stItem.equipdata.unBindCount);
					m_stInfo[m_ucIconInfoLine].m_strInfo += szText;
				}
			}
		}
	}

	if (strlen(m_stInfo[m_ucIconInfoLine].m_strInfo.c_str()) > 0)
	{
		SetInfoRightText();
		SET_EQUIP( "%s", m_stInfo[m_ucIconInfoLine].m_strInfo.c_str(), Color_Config.getColor( CC_ItemTip_ItemBind ) );
	}
    //////////////////////////////////////////////////////////////////////////
    // 图表下方文字:加解锁
    if(m_stItem.IsLock())
    {
        if( m_stItem.GetUnLockTime() == 0 )
        {
            m_stInfo[m_ucIconInfoLine].m_dwTextAlign = DT_LEFT;
            m_stInfo[m_ucIconInfoLine].m_col = Color_Config.getColor( CC_ItemTip_Lock );
            m_stInfo[m_ucIconInfoLine].m_strInfo = theXmlString.GetString(eText_ItemLocked);
            m_ucIconInfoLine++;
        }
        else
        {
            TimeSpan time = TimeSpan( m_stItem.GetUnLockLeftTime() );

            sprintf( szTemp,"%d",time.GetDays() );
            strcat_s(szTemp, 256, theXmlString.GetString(eText_Day));

            char szTemp2[256] = {0};
            sprintf( szTemp2,"%s%d%s",szTemp, time.GetHours(),theXmlString.GetString(eText_Hour) );

            char szTemp3[256] = {0};
            sprintf( szTemp3,"%s%d%s",szTemp2, time.GetMinutes(),theXmlString.GetString(eTimeUnit_Minute) );

            char szTemp4[256] = {0};
            sprintf( szTemp4,"%s%d%s",szTemp3, time.GetSeconds(),theXmlString.GetString(eTimeUnit_Second));

            char szTemp5[256] = {0};
            sprintf( szTemp5,theXmlString.GetString(eText_ItemUnLocked), szTemp4 );

            m_stInfo[m_ucIconInfoLine].m_dwTextAlign = DT_LEFT;
            m_stInfo[m_ucIconInfoLine].m_col = Color_Config.getColor( CC_ItemTip_Unlock );
            m_stInfo[m_ucIconInfoLine].m_strInfo = szTemp5;
            m_ucIconInfoLine++;
        }
    }

    //////////////////////////////////////////////////////////////////////////
    // 星级，时装没有星级
    if( !pEquip->bFashion && m_stItem.equipdata.ucLevel > 0 )
    {
        MouseTipDrawLine();
        if( m_stItem.equipdata.ucLevel <= 9 )
            sprintf_s( szTemp, sizeof(szTemp)/sizeof(char) -1, "#100%d", (int)m_stItem.equipdata.ucLevel );
        else
            sprintf_s( szTemp, sizeof(szTemp)/sizeof(char) -1, "#130%d", (int)m_stItem.equipdata.ucLevel - 10 );
        m_stInfo[m_ucIconInfoLine].m_bImage = false;
        m_stInfo[m_ucIconInfoLine].m_bGif = true;
        m_stInfo[m_ucIconInfoLine].m_usImageHeight = 16;
        m_stInfo[m_ucIconInfoLine].m_usImageWidth = 159;
		m_stInfo[m_ucIconInfoLine].m_usDestWidth = 0;
		m_stInfo[m_ucIconInfoLine].m_usDestHeight = 0;
        m_stInfo[m_ucIconInfoLine].m_strImage = szTemp;
        m_stInfo[m_ucIconInfoLine].m_usImageColumn = 0;
        m_stInfo[m_ucIconInfoLine].m_usImageRow = (int)m_stItem.equipdata.ucLevel;
        m_stInfo[m_ucIconInfoLine].m_nImageID = -1;
        m_stInfo[m_ucIconInfoLine].m_col = dwDefColor;
        m_ucIconInfoLine++;
    }
}

void S_IconInfoHero::ShowWeapon( void* pItemDetail, INT nType )
{
	if( nType != ItemDefine::ITEMTYPE_WEAPON )
		return;

	// 武器类型
	ItemDefine::SItemWeapon* pWeapon = NULL;
	if( pItemDetail )
	{
		pWeapon = ( ItemDefine::SItemWeapon* )pItemDetail;
	}
    else
    {
        return;
    }

    MouseTipDrawLine();
    char szTemp [MAX_PATH] = {0};
    int nCount( 0 );
    for( int i = 0; i < PLAYERPROFESSION; ++i )
        if( m_nProfession[i] )
            nCount++;
	SHOW_STRING( theXmlString.GetString( eText_BaseAttrInEquip ), Color_Config.getColor( CC_ItemTip_BaseAttr ) );
    // 是否全职通用
	// 攻击  
	// 近
	if(pWeapon->attackPhysics != 0)
	{
		int nAttStarVal = GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->attackPhysics, m_stItem.equipdata.ucLevel );
		std::string strDescribe;
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eText_PlayAtt_Short ), nAttStarVal );
		strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pWeapon->attackPhysics );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );
	}

	// 魔
	if(pWeapon->attackMagic != 0)
	{
		int nAttStarVal = GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->attackMagic, m_stItem.equipdata.ucLevel );
		std::string strDescribe;		
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eText_PlayAtt_Magic ), nAttStarVal );
		strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pWeapon->attackMagic );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );
	}

	//命中率
	if(pWeapon->exact != 0)
	{
		int nAttStarVal = GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->exact, m_stItem.equipdata.ucLevel );
		std::string strDescribe;
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddExact ), nAttStarVal );
		strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pWeapon->exact );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );
		
	}

	//闪避率
	if(pWeapon->dodge != 0)
	{
		int nAttStarVal = GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->dodge, m_stItem.equipdata.ucLevel );
		std::string strDescribe;
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddDodge ), nAttStarVal );
		strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pWeapon->dodge );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );

	
	}

	//暴击率
	if(pWeapon->critical != 0)
	{
		int nAttStarVal = GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->critical, m_stItem.equipdata.ucLevel );
		std::string strDescribe;
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddCritical ), nAttStarVal );
		strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pWeapon->critical );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );
		
	}

	//韧性
	if(pWeapon->tenacity != 0)
	{
		int nAttStarVal = GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->tenacity, m_stItem.equipdata.ucLevel );
		std::string strDescribe;
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddTenacity ), nAttStarVal );
		strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pWeapon->tenacity );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );
		
	}

#pragma message("这儿添加装备的元素属性")
	//破甲伤害
	if(pWeapon->breakStrike != 0)
	{
		int nAttStarVal = GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->breakStrike, m_stItem.equipdata.ucLevel );
		std::string strDescribe;
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddBreakStrike ), nAttStarVal );
		strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pWeapon->breakStrike );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );

	}
	//破甲抗性
	if(pWeapon->breakResist != 0)
	{
		int nAttStarVal = GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->breakResist, m_stItem.equipdata.ucLevel );
		std::string strDescribe;
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddBreakResist ), nAttStarVal );
		strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pWeapon->breakResist );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );

	}
	//贯穿伤害
	if(pWeapon->stabStrike != 0)
	{
		int nAttStarVal = GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->stabStrike, m_stItem.equipdata.ucLevel );
		std::string strDescribe;
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddStabStrike ), nAttStarVal );
		strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pWeapon->stabStrike );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );

	}
	//贯穿抗性
	if(pWeapon->stabResist != 0)
	{
		int nAttStarVal = GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->stabResist, m_stItem.equipdata.ucLevel );
		std::string strDescribe;
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddStabResist ), nAttStarVal );
		strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pWeapon->stabResist );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );

	}
	//元素伤害
	if(pWeapon->elementStrike != 0)
	{
		int nAttStarVal = GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->elementStrike, m_stItem.equipdata.ucLevel );
		std::string strDescribe;
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddElementStrike ), nAttStarVal );
		strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pWeapon->elementStrike );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );

	}
	//元素抗性
	if(pWeapon->elementResist != 0)
	{
		int nAttStarVal = GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->elementResist, m_stItem.equipdata.ucLevel );
		std::string strDescribe;
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddElementResist ), nAttStarVal );
		strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pWeapon->elementResist );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );

	}
	//毒素伤害
	if(pWeapon->toxinStrike != 0)
	{
		int nAttStarVal = GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->toxinStrike, m_stItem.equipdata.ucLevel );
		std::string strDescribe;
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddToxinStrike ), nAttStarVal );
		strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pWeapon->toxinStrike );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );

	}
	//毒素抗性
	if(pWeapon->toxinResist != 0)
	{
		int nAttStarVal = GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->toxinResist, m_stItem.equipdata.ucLevel );
		std::string strDescribe;
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddToxinResist ), nAttStarVal );
		strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pWeapon->toxinResist );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );

	}
	//精神伤害
	if(pWeapon->spiritStrike != 0)
	{
		int nAttStarVal = GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->spiritStrike, m_stItem.equipdata.ucLevel );
		std::string strDescribe;
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddSpiritStrike ), nAttStarVal );
		strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pWeapon->spiritStrike );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );

	}
	//精神抗性
	if(pWeapon->spiritResist != 0)
	{
		int nAttStarVal = GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->spiritResist, m_stItem.equipdata.ucLevel );
		std::string strDescribe;
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddSpiritResist ), nAttStarVal );
		strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pWeapon->spiritResist );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );
	}
}

void S_IconInfoHero::ShowArmour( void* pItemDetail, INT nType )
{
	if( nType != ItemDefine::ITEMTYPE_ARMOUR )
		return;

	char szTemp [256] = {0};
	ItemDefine::SItemArmour* pArmour = NULL;

    if( pItemDetail )
    {
        pArmour = ( ItemDefine::SItemArmour* )pItemDetail;
    }
    else
    {
        return;
    }

    MouseTipDrawLine();
    int nCount( 0 );
    for( int i = 0; i < PLAYERPROFESSION; ++i )
        if( m_nProfession[i] )
            nCount++;
	SHOW_STRING( theXmlString.GetString( eText_BaseAttrInEquip ), Color_Config.getColor( CC_ItemTip_BaseAttr ) );
	std::string strDescribe;
	// 近
	if(pArmour->attackPhysics != 0)
	{
		int nAttStarVal = GetAttributeWithLevel( pArmour->ustEquipType, pArmour->attackPhysics, m_stItem.equipdata.ucLevel );
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eText_PlayAtt_Short ), nAttStarVal );
		strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pArmour->attackPhysics );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );
	}

	// 魔
	if(pArmour->attackMagic != 0)
	{
		int nAttStarVal = GetAttributeWithLevel( pArmour->ustEquipType, pArmour->attackMagic, m_stItem.equipdata.ucLevel );
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eText_PlayAtt_Magic ), nAttStarVal );
		strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pArmour->attackMagic );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );
	}

    // 防御
    if( pArmour->defendPhysics != 0 )  
    {
        // 近
        MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eText_PlayDef_Short ),
            (int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->defendPhysics, m_stItem.equipdata.ucLevel ) );  
        std::string strDescribe = szTemp;
        if( m_stItem.IsSoulStamp() )
        {
            ChangeToSoulStampTip( strDescribe, pArmour->defendPhysics );
        }
        SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );
    }

    if( pArmour->defendMagic != 0 )  
    {
        // 魔
        MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eText_PlayDef_Magic ),
            (int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->defendMagic, m_stItem.equipdata.ucLevel ) );  
        std::string strDescribe = szTemp;
        if( m_stItem.IsSoulStamp() )
        {
            ChangeToSoulStampTip( strDescribe, pArmour->defendMagic );
        }
        SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );
    }

	/*
	 * Author: 2012-10-11 20:42:05 liaojie
	 * Desc:   
	 */
	if( pArmour->Hp != 0 )  
	{
		// 血
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddHPMax ),
			(int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->Hp, m_stItem.equipdata.ucLevel ) );  
		std::string strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pArmour->Hp );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );
	}
	if( pArmour->Mp != 0 )  
	{
		// Mp
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddMPMax ),
			(int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->Mp, m_stItem.equipdata.ucLevel ) );  
		std::string strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pArmour->Mp );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );
	}

	//命中率
	if(pArmour->exact != 0)
	{
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddExact ),
			(int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->exact, m_stItem.equipdata.ucLevel ) );  
		std::string strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pArmour->exact );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );		
	}

	//闪避率
	if(pArmour->dodge != 0)
	{
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddDodge ),
			(int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->dodge, m_stItem.equipdata.ucLevel ) );  
		std::string strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pArmour->dodge );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );

		
	}

	//暴击率
	if(pArmour->critical != 0)
	{
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddCritical ),
			(int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->critical, m_stItem.equipdata.ucLevel ) );  
		std::string strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pArmour->critical );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );
		
	}

	//韧性
	if(pArmour->tenacity != 0)
	{
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddTenacity ),
			(int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->tenacity, m_stItem.equipdata.ucLevel ) );  
		std::string strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pArmour->tenacity );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );
	}
#pragma message("这儿添加防具的元素属性")
	//破甲伤害
	if(pArmour->breakStrike != 0)
	{
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddBreakStrike ),
			(int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->breakStrike, m_stItem.equipdata.ucLevel ) );  
		std::string strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pArmour->breakStrike );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );
	}
	//破甲抗性
	if(pArmour->breakResist != 0)
	{
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddBreakResist ),
			(int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->breakResist, m_stItem.equipdata.ucLevel ) );  
		std::string strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pArmour->breakResist );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );
	}
	//贯穿伤害
	if(pArmour->stabStrike != 0)
	{
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddStabStrike ),
			(int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->stabStrike, m_stItem.equipdata.ucLevel ) );  
		std::string strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pArmour->stabStrike );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );
	}
	//贯穿抗性
	if(pArmour->stabResist != 0)
	{
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddStabResist ),
			(int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->stabResist, m_stItem.equipdata.ucLevel ) );  
		std::string strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pArmour->stabResist );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );
	}
	//元素伤害
	if(pArmour->elementStrike != 0)
	{
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddElementStrike ),
			(int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->elementStrike, m_stItem.equipdata.ucLevel ) );  
		std::string strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pArmour->elementStrike );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );
	}
	//元素抗性
	if(pArmour->elementResist != 0)
	{
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddElementResist ),
			(int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->elementResist, m_stItem.equipdata.ucLevel ) );  
		std::string strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pArmour->elementResist );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );
	}
	//毒素伤害
	if(pArmour->toxinStrike != 0)
	{
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddToxinStrike ),
			(int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->toxinStrike, m_stItem.equipdata.ucLevel ) );  
		std::string strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pArmour->toxinStrike );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );
	}
	//毒素抗性
	if(pArmour->toxinResist != 0)
	{
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddToxinResist ),
			(int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->toxinResist, m_stItem.equipdata.ucLevel ) );  
		std::string strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pArmour->toxinResist );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );
	}
	//精神伤害
	if(pArmour->spiritStrike != 0)
	{
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddSpiritStrike ),
			(int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->spiritStrike, m_stItem.equipdata.ucLevel ) );  
		std::string strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pArmour->spiritStrike );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );
	}
	//精神抗性
	if(pArmour->spiritResist != 0)
	{
		MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eTip_sAddSpiritResist ),
			(int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->spiritResist, m_stItem.equipdata.ucLevel ) );  
		std::string strDescribe = szTemp;
		if( m_stItem.IsSoulStamp() )
		{
			ChangeToSoulStampTip( strDescribe, pArmour->spiritResist );
		}
		SHOW_STRING( strDescribe.c_str(), Color_Config.getColor( CC_ItemTip_BaseAttr ) );
	}
}

void S_IconInfoHero::ShowEquipRand( void* pItemDetail, INT nType )
{
    if( nType != ItemDefine::ITEMTYPE_ARMOUR  && nType != ItemDefine::ITEMTYPE_WEAPON )
        return;	

    int nRandValue = 0;
    char szTemp[256];
    int nTipPreTextIndex = 0;

    // 显示鉴定等级ui
    //unsigned short usRandEvalValue = GetEquipRandomEvaluate( pItemDetail, nType, CRandPropertyEvaluate::PropertyEvaluate_Identify, m_stItem );
    //ShowRandomEvaluateUI( usRandEvalValue, CRandPropertyEvaluate::PropertyEvaluate_Identify );

    ItemDefine::SItemCanEquip* pEquip = NULL;
    if( pItemDetail )
    {
        pEquip = ( ItemDefine::SItemCanEquip* )pItemDetail;
    }
    else
    {
        return;
    }

	//MouseTipDrawLine();
	bool bShowOnce = false;
	//SHOW_STRING( theXmlString.GetString( eText_RandAttrInEquip ), Color_Config.getColor( CC_ItemTip_RandAttr ) );
    // 附加随机属性
    for( int nloop = 0; nloop < SCharItem::EConstDefine_BaseRandMaxCount; ++nloop )
    {			
        ItemDefine::SRandAttribute* pEquipRand = NULL;
        unsigned short usRand =m_stItem.equipdata.baseRands[nloop];
        //if( nloop >= pEquip->additiveRandCount && pEquip->ustEquipType != ItemDefine::equip_Amulet)//&& ( nloop != ( SCharItem::e_AddRandIndex ) ) )//随机个数以内
        //     continue;

        if( usRand == InvalidLogicNumber )//&& ( nloop != ( SCharItem::e_AddRandIndex ) ) )// 显示问号
        {
            // 现在无未鉴定     //品质介于2-5，现在套装也显示
            //if( pEquip->ustLevel >= 2 && pEquip->ustLevel <= 5 )
            //{
            //	sprintf_s( szTemp, 256, "%s %s", theXmlString.GetString( eTip_PreText_Addition1 + nTipPreTextIndex ), 
            //      theXmlString.GetString( eTip_PreText_NoIdentify ) );
            //	nTipPreTextIndex ++ ;
            //	SHOW_STRING( szTemp, BLUE_COLOR );
            //}
            continue;
        }

        pEquipRand = GettheItemDetail().GetRandByID(m_stItem.equipdata.baseRands[nloop]);

        if (!pEquipRand)
            continue;

        for( int i = 0 ; i < ItemDefine::SRandAttribute::CD_TypeCount ; ++ i )
        {
            nRandValue = GetRandValueByType( pEquipRand, i );
            if( pEquipRand->type[i] == RT_None )
                continue;

			float intensity = GettheItemDetail().GetEquipQualityIntensity(m_stItem.equipdata.quality);

            if( pEquipRand->type[i] == RT_AddMoveSpeed )
            {
                sprintf( szTemp, "%s+%.2f", S_IconInfoHero::GetRandStringByType( pEquipRand->type[i] ).c_str(), 
					( float )nRandValue / 100.0f * intensity);
            }
            else
            {
				int value  = (float)nRandValue * intensity/* + 0.5f*/;
				sprintf( szTemp, "%s+%d", GetRandStringByType( pEquipRand->type[i] ).c_str(), value > 0 ? value : 1);  
                if( pEquipRand->type[i] == RT_AddExpPer )
                    sprintf( szTemp, "%s%s", szTemp, "%" );
            }

			if (!bShowOnce)
			{
				MouseTipDrawLine();
				SHOW_STRING( theXmlString.GetString( eText_RandAttrInEquip ), Color_Config.getColor( CC_ItemTip_RandAttr ) );
				bShowOnce = true;
			}
            SHOW_STRING( szTemp, Color_Config.getColor( CC_ItemTip_RandAttr ) );
            nTipPreTextIndex ++ ;
        }
    }

    // 鎏金(开光)
    nTipPreTextIndex = 0;
    for( int nloop = 0; nloop < SCharItem::EConstDefine_PurpleRandMaxCount; ++nloop )
    {
        ItemDefine::SRandAttribute* pEquipRand = NULL;
        unsigned short usRand = m_stItem.equipdata.purpleRands[nloop];
        if( nloop >= pEquip->purpleRandCount || usRand == InvalidLogicNumber ) //随机个数以内
            continue;

        pEquipRand = GettheItemDetail().GetRandByID( m_stItem.equipdata.purpleRands[nloop] );
        if ( !pEquipRand )
            continue;

        for( int i = 0 ; i < ItemDefine::SRandAttribute::CD_TypeCount ; ++ i )
        {
            nRandValue = GetRandValueByType( pEquipRand, i );
            if( pEquipRand->type[i] == RT_None )
                continue;

            if( pEquipRand->type[i] == RT_AddMoveSpeed )
            {
                sprintf( szTemp, "%s+%.2f", S_IconInfoHero::GetRandStringByType( pEquipRand->type[i] ).c_str(), ( float )nRandValue / 100.0f );
            }
            else
            {
                sprintf( szTemp, "%s+%d", GetRandStringByType( pEquipRand->type[i] ).c_str(), nRandValue );
                if( pEquipRand->type[i] == RT_AddExpPer )
                    sprintf( szTemp, "%s%s", szTemp, "%" );
            }
            SHOW_STRING( szTemp, Color_Config.getColor( CC_ItemTip_PurpleAttr ) );
            nTipPreTextIndex ++ ;
        }

        // 显示开光等级ui
       /* unsigned short usRandEvalValue = GetEquipRandomEvaluate( pItemDetail, nType, CRandPropertyEvaluate::PropertyEvaluate_OpenLight,
            m_stItem );*/
        //ShowRandomEvaluateUI( usRandEvalValue, CRandPropertyEvaluate::PropertyEvaluate_OpenLight );
    } 
	if (pEquip->ustEquipType == ItemDefine::equip_Amulet)
	{
		int nNowExisting = 0;
		for (int nloop=0;nloop<SCharItem::EConstDefine_BaseRandMaxCount;++nloop)
		{
			if (m_stItem.equipdata.baseRands[nloop] != InvalidLogicNumber)
			{
				++nNowExisting;
			}
		}
		int nTotal = m_stItem.equipdata.quality;
		sprintf_s(szTemp,256,theXmlString.GetString(eText_Amulet_Left),nTotal - nNowExisting);
		SHOW_STRING( szTemp, Color_Config.getColor( CC_ItemTip_RandAttr ) );
	}
}

void S_IconInfoHero::ShowEquipGemInlay( void* pItemDetail, INT nType )
{
    if( nType != ItemDefine::ITEMTYPE_WEAPON && nType != ItemDefine::ITEMTYPE_ARMOUR )
        return;

    ItemDefine::SItemCanEquip* pEquip = ( ItemDefine::SItemCanEquip* )pItemDetail;

    int nHoleCount = m_stItem.equipdata.gemHoleCount;
    if( nHoleCount <= 0 || nHoleCount > SCharItem::EConstDefine_GemHoleMaxCount )
        return;

    char szTemp[MAX_PATH] = {0};
    DWORD dwDefColor = 0xffffffff;
    MouseTipDrawLine();
    for( int i = 0; i < nHoleCount; ++i )
    {
        int nGemId = m_stItem.equipdata.gemIds[i];
        ItemDefine::SItemGem* pGem = NULL;
        if( nGemId > 0 )
        {
            pGem = ( ItemDefine::SItemGem* )GettheItemDetail().GetItemByID( nGemId );
        }

        if( pGem )
        {
            // 宝石图标
            int nIconRow = 0;
            int nIconCol = 0;
            int nIconSize = TIP_ICON_GEM_SIZE;
            std::string strImg = MOUSETIP_PICPATH;
            const IconManager::IconInfo* pIcon = IconManager::Get().GetIconInfo( nGemId );
            if( pIcon )
            {
                strImg = pIcon->image;
                nIconSize = pIcon->iconSize;
                nIconRow = pIcon->row;
                nIconCol = pIcon->column;
            }
            m_stInfo[m_ucIconInfoLine].m_bImage = true;
            m_stInfo[m_ucIconInfoLine].m_bIcon = false;
            m_stInfo[m_ucIconInfoLine].m_bNewLine = false;
            m_stInfo[m_ucIconInfoLine].m_eImageAlignMode = stIconInfoEx::eIIIA_Left;
            m_stInfo[m_ucIconInfoLine].m_nImageID = -1;
            m_stInfo[m_ucIconInfoLine].m_strImage = strImg;
            m_stInfo[m_ucIconInfoLine].m_usImageWidth = nIconSize;
            m_stInfo[m_ucIconInfoLine].m_usImageHeight = nIconSize;
            m_stInfo[m_ucIconInfoLine].m_usDestWidth = TIP_ICON_GEM_SIZE;
            m_stInfo[m_ucIconInfoLine].m_usDestHeight = TIP_ICON_GEM_SIZE;
            m_stInfo[m_ucIconInfoLine].m_usImageRow = nIconRow;
            m_stInfo[m_ucIconInfoLine].m_usImageColumn = nIconCol;
            m_stInfo[m_ucIconInfoLine].m_ucRightRowCount = 1;
            m_stInfo[m_ucIconInfoLine].m_usSrcX = nIconCol * nIconSize;
            m_stInfo[m_ucIconInfoLine].m_usSrcY = nIconRow * nIconSize;
            m_stInfo[m_ucIconInfoLine].m_col = dwDefColor;
            m_ucIconInfoLine++;

            // 一颗宝石2属性
            std::string strGemAttr;
            for( int j = 0; j < ItemDefine::SItemGem::CD_TypeCount; ++j )
            {
                std::string strGemAttrType = GetRandStringByType( pGem->type[j] );
                if( strGemAttrType.empty() )
                    continue;

                if( !strGemAttr.empty() )
                    strGemAttr += "， ";

                if( pGem->type[j] == RT_AddMoveSpeed )
                {
                    MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%.2f", strGemAttrType.c_str(), pGem->value[j].fValue );
                    strGemAttr += szTemp;
                }
                else
                {
                    MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", strGemAttrType.c_str(), ( int )pGem->value[j].fValue );
                    strGemAttr += szTemp;
                    if( pGem->type[j] == RT_AddExpPer )
                        strGemAttr += "%";
                }
            }
            m_stInfo[m_ucIconInfoLine].m_bRightText = true;
            m_stInfo[m_ucIconInfoLine].m_strInfo = strGemAttr;
            m_stInfo[m_ucIconInfoLine].m_col = Color_Config.getColor( CC_ItemTip_GemAttr );
            m_ucIconInfoLine++;	
        }
        else
        {
            // 有孔未镶嵌
            m_stInfo[m_ucIconInfoLine].m_bImage = true;
            m_stInfo[m_ucIconInfoLine].m_bIcon = false;
            m_stInfo[m_ucIconInfoLine].m_bNewLine = false;
            m_stInfo[m_ucIconInfoLine].m_eImageAlignMode = stIconInfoEx::eIIIA_Left;
            m_stInfo[m_ucIconInfoLine].m_nImageID = -1;
            m_stInfo[m_ucIconInfoLine].m_strImage = MOUSETIP_PICPATH;
            m_stInfo[m_ucIconInfoLine].m_usImageWidth = TIP_ICON_GEM_SIZE;
            m_stInfo[m_ucIconInfoLine].m_usImageHeight = TIP_ICON_GEM_SIZE;
            m_stInfo[m_ucIconInfoLine].m_usImageRow = 0;
            m_stInfo[m_ucIconInfoLine].m_usImageColumn = 0;
            m_stInfo[m_ucIconInfoLine].m_ucRightRowCount = 0;
            m_stInfo[m_ucIconInfoLine].m_usSrcX = TIP_HOLE_SRC_X;
            m_stInfo[m_ucIconInfoLine].m_usSrcY = TIP_HOLE_SRC_Y;
            m_stInfo[m_ucIconInfoLine].m_col = dwDefColor;
            m_ucIconInfoLine++;
        }
    }
}

void S_IconInfoHero::ShowArmourSkill( void* pItemDetail, INT nType, int nPlayerID )
{
    guardfunc;
    if( nType != ItemDefine::ITEMTYPE_ARMOUR )
        return;

    char szTemp [256] = {0};
    ItemDefine::SItemArmour* pArmour = NULL;

    if( pItemDetail )
    {
            pArmour = ( ItemDefine::SItemArmour* )pItemDetail;
    }
    else
    {
        return;
    }

    int nCount( 0 );
    for( int i = 0; i < PLAYERPROFESSION; ++i )
        if( m_nProfession[i] )
            nCount++;

    // 乱七八糟的五行残留数据 和 套装技能
    bool bEquiped = false;      // 是否已经装备了
    if( pArmour->sSuitID == 0 || pArmour->sSuitID == -1 )
        return;

    std::vector< ItemDefine::SItemArmour* > vSuitEquip;
    std::vector< SCharItem* > vSuitCharItem;

    CPlayer *pPlayer = theHeroGame.GetPlayerMgr()->FindByID( nPlayerID );
    if( pPlayer )
    {
        SCharItem* pEquipItems = 0;
        if( theHeroGame.GetPlayerMgr()->GetMe() == pPlayer )
            pEquipItems = thePlayerRole.m_pVisual->GetVisual( 0 );
        else
            pEquipItems = pPlayer->GetSeekEquipInfo();
        if( pEquipItems != 0 )
        {
            for( int i = 0 ; i < EEquipPartType_MaxEquitPart ; ++ i )
            {
                SCharItem* pPlayerEquip = &pEquipItems[i];
                if( pPlayerEquip )
                {
                    ItemDefine::SItemCommon* pPlayerItem = GettheItemDetail().GetItemByID( pPlayerEquip->itembaseinfo.ustItemID );
                    if( pPlayerItem && 
                        pPlayerItem->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
                    {
                        ItemDefine::SItemArmour* pPlayerArmour = (ItemDefine::SItemArmour*)pPlayerItem;
                        if( pPlayerArmour->sSuitID == pArmour->sSuitID )//是套装部件
                        {
                            vSuitEquip.push_back( pPlayerArmour );
                            vSuitCharItem.push_back( pPlayerEquip );
                        }
                        if( pPlayerEquip->itembaseinfo.nOnlyInt == m_stItem.itembaseinfo.nOnlyInt )
                            bEquiped = true;
                    }
                }	
            }
        }
    }

    DWORD dwSuitColor = Color_Config.getColor( CC_ItemTip_suitNoneAll );
    const DWORD dwDefColor = 0xffffffff; 
    // 是否判定五行,是依据是否满套
    bool bEnableFiveElement = false;
    const int ncEnableFiveElementCount = 6;//6件套装才会开启
    // 套装技能
    bool bEanbleSuitSkill = false; 
    // 满套
    if( pArmour->sPartCount == vSuitEquip.size() )
    {				
        // 开启五行判定				
        if( pArmour->sPartCount == ncEnableFiveElementCount )
            bEnableFiveElement = true;
        dwSuitColor = GetQualityColor( pArmour->ustLevel );
        if( bEquiped )
            m_eColorFrameType = eColorFrame_Level;

        if (pArmour->IsSkillSuitEquip())
            bEanbleSuitSkill = true;
    }

    // 单件套装技能装备属性
    unsigned short usSkillSuitID = thePlayerRole.suitManager.GetSkillSuitIdByPartSuitId( pArmour->sSuitID );
    const SkillSuitAttribute& attri = theSuitOperateConfig.GetSkillSuitAttribute(usSkillSuitID);

    if (pArmour->IsSkillSuitEquip() && attri.attributeName != "")
        SHOW_LINE();

    if (pArmour->IsSkillSuitEquip() && m_stItem.GetSuitLevel() > 0 && attri.attributeName != "")
    {
        //// 套装技能装备等级，图片
        char szBuf[256];
        if (!attri.attributePicture.empty())
        {
            sprintf_s( szBuf, 256, attri.attributePicture.c_str(), (int)m_stItem.GetSuitLevel() );
            m_stInfo[m_ucIconInfoLine].m_bImage = false;
            m_stInfo[m_ucIconInfoLine].m_bGif = true;
            m_stInfo[m_ucIconInfoLine].m_usImageHeight = attri.attributePictureHeight;
            m_stInfo[m_ucIconInfoLine].m_usImageWidth = attri.attributePictureWidth;
            m_stInfo[m_ucIconInfoLine].m_strImage = szBuf;
            m_stInfo[m_ucIconInfoLine].m_usImageColumn = 0;
            m_stInfo[m_ucIconInfoLine].m_usImageRow = (int)m_stItem.GetSuitLevel();
            m_stInfo[m_ucIconInfoLine].m_nImageID = -1;
            m_stInfo[m_ucIconInfoLine].m_col = dwDefColor;
            m_ucIconInfoLine++;
        }

        ItemDefine::SRandAttribute* pArmourRand = NULL;
        for( int loop = 0; loop < SCharItem::EConstDefine_SuitRandMaxCount; ++loop )
        {
            pArmourRand = NULL;
            pArmourRand = GettheItemDetail().GetRandByID( m_stItem.equipdata.suitRands[loop] );

            if( pArmourRand )
            {
                int nRandValue = InvalidLogicNumber;
                int nTipPreTextIndex = 0;
                for( int i = 0; i < ItemDefine::SRandAttribute::CD_TypeCount; ++i )
                {
                    if( pArmourRand->type[i] == RT_None )
                        continue;

                    nRandValue = GetRandValueByType( pArmourRand, i );
                    if( nRandValue != InvalidLogicNumber )  
                    { 
                        if( pArmourRand->type[i] == RT_AddMoveSpeed )
                        {
							sprintf( szBuf, "%s+%d:%s+%.2f", attri.attributeName.c_str(), m_stItem.GetSuitLevel(),
                                GetRandStringByType( pArmourRand->type[i] ).c_str(), ( float )nRandValue / 100.0f ); 
                        }
                        else
                        {
							sprintf( szBuf, "%s+%d:%s+%d", attri.attributeName.c_str(), m_stItem.GetSuitLevel(),
                                GetRandStringByType( pArmourRand->type[i] ).c_str(), nRandValue ); 
                            if( pArmourRand->type[i] == RT_AddExpPer )
                                sprintf( szTemp, "%s%s", szTemp, "%" );
                        }
                        SHOW_STRING( szBuf, Color_Config.getColor( CC_ItemTip_Other ) );
                    }
                }
            }
        }
    }

    // 全套套装技能装备属性
    ItemDefine::SItemArmour* pSuitArmour = (ItemDefine::SItemArmour*)GettheItemDetail().GetItemByID( usSkillSuitID );
    if (pSuitArmour && attri.attributeName != "")
    {
        // 技能等级
        SCharSkill* pSuitSkill = thePlayerRole.m_SkillBag.GetSkillByID(pSuitArmour->skillId);
        int skillLevel = 0;
        if (pSuitSkill)
        {
            for (int l = ItemDefine::MaxLevel_Skill - 1; l > 0; --l)
            {
                if (thePlayerRole.suitManager.IsSuitHaveSkill(pSuitArmour->skillId, l))
                {
                    skillLevel = l;
                    pSuitSkill->stSkillLevel = skillLevel;
                    break;
                }
            }
        }

        // 套装等级
        unsigned short suitLevel = InvalidLogicNumber;
        for (int s = 0; s < vSuitCharItem.size(); ++s)
        {
            if (suitLevel > vSuitCharItem[s]->GetSuitLevel())
                suitLevel = vSuitCharItem[s]->GetSuitLevel();
        }

        if (bEanbleSuitSkill && bEquiped && pSuitSkill && m_stItem.GetSuitLevel() > 0 && skillLevel > 1)
        {

            ItemDefine::SItemSkill *pItemSkill = GettheItemDetail().GetSkillByID( pSuitSkill->ustSkillID, skillLevel );
            if (pItemSkill)
            {
                //套装技能链(+%d):%s技能提升%d级
                char szBuf[256];
                const SkillSuitAttribute& attri = theSuitOperateConfig.GetSkillSuitAttribute(usSkillSuitID);
                sprintf( szBuf, theXmlString.GetString(4822),
                    suitLevel,
                    pItemSkill->GetItemName(),
                    skillLevel ); 

                SHOW_STRING( szBuf, Color_Config.getColor( CC_ItemTip_Other ) );
            }
        }
        else
        {
            //全套%d+3、+4、+5即可提升技能等级
            char szBuf[256];
            sprintf( szBuf, theXmlString.GetString(4821), attri.attributeName.c_str() ); 
            SHOW_STRING( szBuf, 0xFFa0a0a0 );
        }

        if (pArmour->IsSkillSuitEquip())
            SHOW_LINE();
    }
    unguard;
}

void S_IconInfoHero::ShowEquipSuit( void* pItemDetail, INT nType, int nPlayerID )
{
    guardfunc;
    if( nType != ItemDefine::ITEMTYPE_ARMOUR && nType != ItemDefine::ITEMTYPE_WEAPON )
        return;

    char szTemp [256] = {0};
    ItemDefine::SItemCanEquip* pEquip = NULL;

    if ( pItemDetail )
    {
        pEquip = ( ItemDefine::SItemCanEquip* )pItemDetail;
    }
    else
    {
        return;
    }

    int nCount( 0 );
    for( int i = 0; i < PLAYERPROFESSION; ++i )
        if( m_nProfession[i] )
            nCount++;

    // 乱七八糟的五行残留数据
    bool bEquiped = false;      // 是否已经装备了
    if( pEquip->sSuitID == 0 || pEquip->sSuitID == -1 )
        return;

    std::vector< ItemDefine::SItemCanEquip* > vSuitEquip;
    std::vector< SCharItem* > vSuitCharItem;

    CPlayer *pPlayer = theHeroGame.GetPlayerMgr()->FindByID( nPlayerID );
    if( pPlayer )
    {
        SCharItem* pEquipItems = 0;
        if( theHeroGame.GetPlayerMgr()->GetMe() == pPlayer )
            pEquipItems = thePlayerRole.m_pVisual->GetVisual( 0 );
        else
            pEquipItems = pPlayer->GetSeekEquipInfo();
        if( pEquipItems != 0 )
        {
            for( int i = 0 ; i < EEquipPartType_MaxEquitPart ; ++ i )
            {
                SCharItem* pPlayerEquip = &pEquipItems[i];
                if( pPlayerEquip )
                {
                    ItemDefine::SItemCommon* pPlayerItem = GettheItemDetail().GetItemByID( pPlayerEquip->itembaseinfo.ustItemID );
                    if( pPlayerItem && ( pPlayerItem->ucItemType == ItemDefine::ITEMTYPE_ARMOUR || 
                        pPlayerItem->ucItemType == ItemDefine::ITEMTYPE_WEAPON ) )
                    {
                        ItemDefine::SItemCanEquip* _pPlayerEuip = ( ItemDefine::SItemCanEquip* )pPlayerItem;
                        if( _pPlayerEuip->sSuitID == pEquip->sSuitID )//是套装部件
                        {
                            vSuitEquip.push_back( _pPlayerEuip );
                            vSuitCharItem.push_back( pPlayerEquip );
                        }
                        if( pPlayerEquip->itembaseinfo.nOnlyInt == m_stItem.itembaseinfo.nOnlyInt )
                            bEquiped = true;
                    }
                }	
            }
        }
    }

    // 真正套装部分开始
    // 显示套装名(?/?)
    MouseTipDrawLine();
    int nCurrentLine = m_ucIconInfoLine;
    ItemDefine::SItemCommon* pCommon = 0;
    for( int i = 1; i <= MAX_SUIT_PART_COUNT; ++ i )
    {
        pCommon = GettheItemDetail().GetItemByID( pEquip->sSuitID * 10 + i );
        if( pCommon )
            break;
    }
    if( pCommon )
        m_stInfo[nCurrentLine].m_strInfo = pCommon->GetItemName();
    else
        m_stInfo[nCurrentLine].m_strInfo = theXmlString.GetString( eUI_TipsSuit );

    m_stInfo[m_ucIconInfoLine].m_col = Color_Config.getColor( CC_ItemTip_SuitPart_Have );
    m_ucIconInfoLine++;

    // 套装部件 ( 套装放在防具表里 )
    std::vector<ItemDefine::SItemCanEquip*>* pEquipVector = GettheItemDetail().GetSuitsByID( pEquip->sSuitID );
    if( pEquipVector )
    {
        int nPartNum( 0 );
        for( int i = 0 ; i < pEquipVector->size(); ++ i )
        {
            ItemDefine::SItemCanEquip* pPartEquip = (*pEquipVector)[i];
            sprintf_s( szTemp, 256, "  %s", pPartEquip->GetItemName() );
            if( std::find( vSuitEquip.begin(), vSuitEquip.end(), pPartEquip ) != vSuitEquip.end() )//find
            {
                ++nPartNum;
                SHOW_STRING( szTemp, Color_Config.getColor( CC_ItemTip_SuitPart_Have ) );
            }
            else
            {
                SHOW_STRING( szTemp, Color_Config.getColor( CC_ItemTip_SuitPart_NotHave ) );
            }
        }
        char szPartNum[MAX_PATH] = { 0 };
        MeSprintf_s( szPartNum, sizeof( szPartNum ) / sizeof( char ) - 1, " ( %d/%d )", nPartNum, pEquipVector->size() );
        m_stInfo[nCurrentLine].m_strInfo = m_stInfo[nCurrentLine].m_strInfo + szPartNum;
    }

    // 显示套装属性加成
    // 在套装id后加上不同数字代表不同装备数的套装
    DWORD dwAttrColor = 0;
    for( int i = 1 ; i <= MAX_SUIT_PART_COUNT ; ++ i )//从1开始遍历，约定套装编号为满套属性
    {
        pCommon = GettheItemDetail().GetItemByID( pEquip->sSuitID * 10 + i );

        if( i <= vSuitEquip.size() )//满足数量
            dwAttrColor = Color_Config.getColor( CC_ItemTip_SuitAttr_Have );
        else
            dwAttrColor = Color_Config.getColor( CC_ItemTip_SuitAttr_NotHave );
        if( pCommon )
            ShowSuitAttribute( i, pCommon->ucItemType, pCommon, dwAttrColor );
    }			
    // 添加满套属性 //暂时不要
    //pCommon = GettheItemDetail().GetItemByID( pEquip->sSuitID );
    //ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID( pEquip->sSuitID );
    
    unguard;
}

void S_IconInfoHero::ShowRandomEvaluateUI( unsigned short usValue, unsigned short usEvalType )
{	
    if( usValue == InvalidLogicNumber ||
        usValue == ErrorUnsignedShortID -1 )
        return;

    const DWORD dwDefColor = 0xffffffff;
    // 显示评估值
    if( usEvalType == CRandPropertyEvaluate::PropertyEvaluate_Identify )
    {
        // 鉴定还需要另外显示‘鉴定:’
        char acTemp[255] = {0};
		sprintf_s( acTemp, 255, "%s:", theXmlString.GetString( eText_Identify ) );
        SHOW_STRING( acTemp, Color_Config.getColor( CC_ItemTip_Identify ) );
    }
    m_stInfo[m_ucIconInfoLine].m_bImage = true;
    m_stInfo[m_ucIconInfoLine].m_bIcon = false;
    m_stInfo[m_ucIconInfoLine].m_bNewLine = false;
    m_stInfo[m_ucIconInfoLine].m_eImageAlignMode = stIconInfoEx::eIIIA_Right;
    m_stInfo[m_ucIconInfoLine].m_nImageID = -1;
    char acQuality[255] = {0};
    sprintf_s( acQuality, 255, "./data/Ui/Common/MiniEquipQuility%d.tga", usValue + 1 );
    m_stInfo[m_ucIconInfoLine].m_strImage = acQuality;
    m_stInfo[m_ucIconInfoLine].m_usImageWidth = 24;
    m_stInfo[m_ucIconInfoLine].m_usImageHeight = 24;		
    m_stInfo[m_ucIconInfoLine].m_usSrcX = 0;
    m_stInfo[m_ucIconInfoLine].m_usSrcY = 0;
    m_stInfo[m_ucIconInfoLine].m_col = dwDefColor;
    m_ucIconLine = m_ucIconInfoLine;
    m_ucIconInfoLine++;
}

void S_IconInfoHero::ShowSuitAttribute( int nCount, INT nType, void* pItemDetail, DWORD dwColor )
{
    if( nType != ItemDefine::ITEMTYPE_ARMOUR )
        return;

    ItemDefine::SItemArmour* pArmour = (ItemDefine::SItemArmour*)pItemDetail;
    if( !pArmour )
        return;

//     for( int i = 0; i < pArmour->additiveRandCount; ++i )
//     {
//         if( !pArmour->additiveRandFlags[i] )
//             return;
//     }

    char szTemp[256] = {0};
    if( pArmour->skillId == 0 )// 不是套装技能
    {
		sprintf_s( szTemp, 256, "%s (%d):", theXmlString.GetString( eText_Suit ), nCount );

        for( int i = 0; i < (int)SCharItem::EConstDefine_BaseRandMaxCount; ++i )
        {
            ItemDefine::SRandAttribute* pArmourRand = NULL;
            pArmourRand = GettheItemDetail().GetRandByID( pArmour->additiveRandFlags[i] );
            if( pArmourRand )
            {
                int nRandValue = InvalidLogicNumber;
                int nTipPreTextIndex = 0;
                for( int i = 0 ; i < ItemDefine::SRandAttribute::CD_TypeCount ; ++i )
                {
                    if( pArmourRand->type[i] == RT_None )
                        continue;

                    nRandValue = GetRandValueByType( pArmourRand, i );
                    if( nRandValue != InvalidLogicNumber )  
                    { 
                        ITEM_SHOW_INT_ONLYCPY( nRandValue, GetRandStringByType( pArmourRand->type[i] ).c_str() );
                    }
                }
            }
        }
        m_stInfo[m_ucIconInfoLine].m_strInfo = szTemp;
        m_stInfo[m_ucIconInfoLine].m_col = dwColor;
        m_ucIconInfoLine ++;
    }
    else//套装技能
    {
        ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( pArmour->skillId, pArmour->skillLevel );		
        if( !pSkill )
            return;
        // (x) 套装技能:技能名字
        sprintf_s( szTemp, 256, "(%d) %s%s", nCount, theXmlString.GetString( eText_SuitSkill ), pSkill->GetSkillName() );
        m_stInfo[m_ucIconInfoLine].m_strInfo = szTemp;
        m_stInfo[m_ucIconInfoLine++].m_col = dwColor;
        // 技能描述
        memset( szTemp, 0, sizeof(szTemp) );
        int nLength = 0;
        std::string szItemDesc = pArmour->GetItemDesc();
        for ( UINT n=0; n<szItemDesc.size(); n++ )
        {
            if ( szItemDesc[n] != 0 &&
                szItemDesc[n] == '\\' && szItemDesc[n+1] == 'n' )
            {
                m_stInfo[m_ucIconInfoLine].m_strInfo = szTemp;
                m_stInfo[m_ucIconInfoLine].m_col = dwColor;
                memset( szTemp, 0, sizeof(szTemp) );
                nLength = 0;
                m_ucIconInfoLine++;
                n++;
            }
            else
            {
                szTemp[nLength++] = szItemDesc[n];
                if ( n == szItemDesc.size() - 1 && strlen(szTemp) > 0 )
                {
                    m_stInfo[m_ucIconInfoLine].m_strInfo = szTemp;
                    m_stInfo[m_ucIconInfoLine].m_col = dwColor;
                    m_ucIconInfoLine++;
                }
            }
            assert( m_ucIconInfoLine < MAX_ICON_INFO_EX_LINE_COUNT );
        }	
    }
}	

void S_IconInfoHero::ShowEquipDescribe( void* pItemDetail, INT nType )
{
    guardfunc;
    if( nType != ItemDefine::ITEMTYPE_ARMOUR && nType != ItemDefine::ITEMTYPE_WEAPON )
        return;

    char szTemp [256] = {0};
    ItemDefine::SItemCanEquip* pEquip = NULL;

    if( pItemDetail )
    {
        pEquip = ( ItemDefine::SItemCanEquip* )pItemDetail;
    }
    else
    {
        return;
    }

    // 添加装备描述
    memset( szTemp, 0, sizeof(szTemp) );
    int nLength = 0;
    std::string szItemDesc = pEquip->GetItemDesc();
    DWORD dwDescColor = Color_Config.getColor( CC_ItemTip_EquipDes_Default );
    for( UINT n = 0; n < szItemDesc.size(); ++n )
    {
        if ( szItemDesc[n] != 0 && szItemDesc[n] == '\\' && szItemDesc[n+1] == 'n' )
        {
            m_stInfo[m_ucIconInfoLine].m_strInfo = szTemp;
            m_stInfo[m_ucIconInfoLine].m_col = dwDescColor;
            memset( szTemp, 0, sizeof(szTemp) );
            nLength = 0;
            m_ucIconInfoLine++;
            n++;
        }
        else if ( n < szItemDesc.size() - 10 &&  szItemDesc[n] == '<' && szItemDesc[n+1] == '#' )
        {
            char szColor[10];
            memset( szColor, 0, sizeof( szColor ) );
            memcpy( szColor, &szItemDesc[n + 2], 8 );
            sscanf( szColor, "%x", &dwDescColor );
            n += 10;
        }
        else
        {
            szTemp[nLength++] = szItemDesc[n];
            if ( n == szItemDesc.size() - 1 && strlen(szTemp) > 0 )
            {
                m_stInfo[m_ucIconInfoLine].m_strInfo = szTemp;
                m_stInfo[m_ucIconInfoLine].m_col = dwDescColor;
                m_ucIconInfoLine++;
            }
        }
        assert( m_ucIconInfoLine < MAX_ICON_INFO_EX_LINE_COUNT );
    }

    // 添加价格		
    //出售价格
    if( GetFlag() == eTipFlag_ShowMoney && pEquip->bIsCanSellShop )
    {
		MouseTipDrawLine();
        int nGold = 0, nSilver = 0, nCopper = 0;
        thePlayerRole.GetGSCFromMoney(Cost(),nGold,nSilver,nCopper);

        std::stringstream str;
        if (nGold > 0)
            str << nGold << theXmlString.GetString( eText_Money_Gold );
        if (nSilver > 0)
            str << nSilver << theXmlString.GetString( eText_Money_Silver );
        if (nCopper > 0)
            str << nCopper << theXmlString.GetString( eText_Money_Copper );
		else 
		{
			if (nGold == 0 && nSilver == 0)
				str << nCopper << theXmlString.GetString( eText_Money_Copper );
		}
        std::string strPrice = str.str();
        sprintf( szTemp, "%s %s%s", theXmlString.GetString(eText_Title_SellPrice), strPrice.c_str(),theXmlString.GetString(eText_Bind_Money) );
        SHOW_STRING( szTemp, Color_Config.getColor( CC_ItemTip_SellPrice ) );

        // 修理价格
       /* int nCurrHP = m_stItem.equipdata.usHP;		
        if ( nCurrHP < 0 )
        {
            nCurrHP = pEquip->stHPMax;
        }
        int nCost = pEquip->stRepairPrice * ( pEquip->stHPMax - nCurrHP );
        thePlayerRole.GetGSCFromMoney(nCost,nGold,nSilver,nCopper);	
        std::stringstream strStreamPrice;
        if (nGold > 0)
            strStreamPrice << nGold << theXmlString.GetString( eText_Money_Gold );
        if (nSilver > 0)
            strStreamPrice << nSilver << theXmlString.GetString( eText_Money_Silver );
        if (nCopper >= 0)
            strStreamPrice << nCopper << theXmlString.GetString( eText_Money_Copper );
        strPrice = strStreamPrice.str();
        sprintf_s( szTemp, 256, "%s%s", theXmlString.GetString( eText_PrepareCost ), strPrice.c_str() );
        SHOW_STRING( szTemp, Color_Config.getColor( CC_ItemTip_FixPrice ) );*/
    }
	else
	{
		MouseTipDrawLine();
		SHOW_STRING( theXmlString.GetString(eText_Equip_Cannot_Sell), Color_Config.getColor( CC_ItemTip_SellPrice ) );
	}
    unguard;
}
void S_IconInfoHero::ShowPetEquip(SCharItem& pItem,void* pItemDetail, INT nType )
{
	if( nType != ItemDefine::ITEMTYPE_PETEQUIP )
        return;

	char szTemp [256] = {0};
    if (!pItemDetail)
    {
        return;
    }
	ItemDefine::SItemPetEquip* pPetEquip = (ItemDefine::SItemPetEquip*)pItemDetail;
	if( !pPetEquip )
        return;
	//等级限制
	SetInfoRightText();
    SET_EQUIPEX_STRING
        (
        (INT)pPetEquip->iEquipLevelReq,
        pPetEquip->iEquipLevelReq,
        "%s %d", 
        theXmlString.GetString(eUI_NeedLevel),
        (INT)pPetEquip->iEquipLevelReq,
        Color_Config.getColor( CC_ItemTip_Require_NotReach ), 
        Color_Config.getColor( CC_ItemTip_Require_Reach ) 
        );

	//显示属性
	char szBuffer[256];
	sprintf( szBuffer, "%s:%s%d\n",theXmlString.GetString( eTip_sAddStrength  ),"+", pItem.petequipdata.Strength );
	SHOW_STRING(szBuffer,0);
	sprintf( szBuffer, "%s:%s%d\n",theXmlString.GetString( eTip_sAddAgility  ),"+", pItem.petequipdata.Agility );
	SHOW_STRING(szBuffer,0);
	sprintf( szBuffer, "%s:%s%d\n",theXmlString.GetString( eTip_sAddConstitution  ),"+", pItem.petequipdata.Stamina);
	SHOW_STRING(szBuffer,0);
	sprintf( szBuffer, "%s:%s%d\n",theXmlString.GetString( eTip_sAddIntelligence ),"+", pItem.petequipdata.Intelligence );
	SHOW_STRING(szBuffer,0);
	//显示描述
	memset( szTemp, 0, sizeof(szTemp) );
    int nLength = 0;
    std::string szItemDesc = pPetEquip->GetItemDesc();
    DWORD dwDescColor = Color_Config.getColor( CC_ItemTip_EventItem_Des );
    for( UINT n = 0; n < szItemDesc.size(); ++n )
    {
        if ( szItemDesc[n] != 0 && szItemDesc[n] == '\\' && szItemDesc[n+1] == 'n' )
        {
            m_stInfo[m_ucIconInfoLine].m_strInfo = szTemp;
            m_stInfo[m_ucIconInfoLine].m_col = dwDescColor;
            memset( szTemp, 0, sizeof(szTemp) );
            nLength = 0;
            m_ucIconInfoLine++;
            n++;
        }
        else if ( n < szItemDesc.size() - 10 &&  szItemDesc[n] == '<' && szItemDesc[n+1] == '#' )
        {
            char szColor[10];
            memset( szColor, 0, sizeof( szColor ) );
            memcpy( szColor, &szItemDesc[n + 2], 8 );
            sscanf( szColor, "%x", &dwDescColor );
            n += 10;
        }
        else
        {
            szTemp[nLength++] = szItemDesc[n];
            if ( n == szItemDesc.size() - 1 && strlen(szTemp) > 0 )
            {
                m_stInfo[m_ucIconInfoLine].m_strInfo = szTemp;
                m_stInfo[m_ucIconInfoLine].m_col = dwDescColor;
                m_ucIconInfoLine++;
            }
        }
        assert( m_ucIconInfoLine < MAX_ICON_INFO_EX_LINE_COUNT );
    }
}
void S_IconInfoHero::ShowRestore( void* pItemDetail, INT nType )
{

    if( nType != ItemDefine::ITEMTYPE_RESTORE )
        return;

    char szTemp [256] = {0};
    if (!pItemDetail)
    {
        return;
    }
    ItemDefine::SItemRestore* pRestore = (ItemDefine::SItemRestore*)pItemDetail;
    if( !pRestore )
        return;

    // 添加使用次数
    if( pRestore->bHPAuto || pRestore->bMPAuto)
    {
        std::string strPreText;
        int nMaxHpMp = 0;
        if( pRestore->bHPAuto )
        {
            strPreText = theXmlString.GetString( eLeftType_Hp );
            nMaxHpMp = pRestore->dwAddHP;
        }
        else if( pRestore->bMPAuto )
        {
            strPreText = theXmlString.GetString( eLeftType_Mp );
            nMaxHpMp = pRestore->dwAddMP;
        }
		sprintf_s( szTemp, 256, "%s:%d/%d", strPreText.c_str(), m_stItem.itembaseinfo.value2, 
            nMaxHpMp );	
        SHOW_STRING( szTemp, Color_Config.getColor( CC_ItemTip_RestoreTime ) );
    }	

    // 添加职业限制         added by ZhuoMeng.Hu		[12/17/2010]
    int nProCnt( 0 );
    for( int i = 0; i < PLAYERPROFESSION; ++i )
    {
        if( pRestore->arrayProfessionReq[i] )
        {
            ++nProCnt;
            m_nProfession[i] = 1;
        }
        else
        {
            m_nProfession[i] = 0;
        }
    }

    if( nProCnt != PLAYERPROFESSION )
    {
        SetInfoRightText();
        std::string strProfession;
        for( int n = 0; n < PLAYERPROFESSION; ++n )
        {
            if( m_nProfession[n] == 1 )
            {
                switch( n )
                {
                case EArmType_Mage:
                    {
                        strProfession += theXmlString.GetString( eProfession_Mage );
                    }
                    break;
                case EArmType_Taoist:
                    {								
                        strProfession += theXmlString.GetString( eProfession_Taoist );
                    }
                    break;
                case EArmType_Assassin:
                    {
                        strProfession += theXmlString.GetString( eProfession_Assassin );
                    }
                    break;
                case EArmType_Warrior:
                    {
                        strProfession += theXmlString.GetString( eProfession_Warrior );
                    }
                    break;
                case EArmType_Hunter:
                    {
                        strProfession += theXmlString.GetString( eProfession_Hunter );
                    }
                    break;
                case EArmType_Sniper:
                    {

                    }
                    break;
                default:
                    break;
                }
                strProfession += " ";
            }
        }
        int nProfession = thePlayerRole.GetProfession();
        char szTemp[MAX_PATH] = {0};
        MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1 , "%s %s", theXmlString.GetString( eNeed_Profession ), strProfession.c_str() );
        if( m_nProfession[nProfession] == 1 )
        {
            SET_EQUIP( "%s", szTemp, Color_Config.getColor( CC_ItemTip_Require_Reach ) );
        }
        else
        {
            SET_EQUIP( "%s", szTemp, Color_Config.getColor( CC_ItemTip_Require_NotReach ) );
        }
    }


    //添加使用等级
    SetInfoRightText();
    SET_EQUIPEX_STRING
        (
        thePlayerRole.GetLevel(),
        pRestore->stUseLevel,
        "%s %d", 
        theXmlString.GetString(eUI_NeedLevel),
        (INT)pRestore->stUseLevel,
        Color_Config.getColor( CC_ItemTip_Require_NotReach ), 
        Color_Config.getColor( CC_ItemTip_Require_Reach ) 
        );

	//
	ItemDefine::SItemCommon* pItem = ( ItemDefine::SItemCommon* )pItemDetail;
	m_stInfo[m_ucIconInfoLine].m_strInfo.clear();

	if (m_stItem.IsBounded())
	{
		m_stInfo[m_ucIconInfoLine].m_strInfo = theXmlString.GetString(eTip_BelongerDone);
	}
	else if( pItem )
	{
	    if (nType == ItemDefine::ITEMTYPE_RESTORE)
		{
			if( !pItem->bIsCanTrade )
			{
				if (m_stItem.itembaseinfo.stPacketIdx != -1 ) //背包index不为-1说明在包里
				{
					m_stInfo[m_ucIconInfoLine].m_strInfo = theXmlString.GetString(eTip_BelongerDone);
				}
				else
				{
					m_stInfo[m_ucIconInfoLine].m_strInfo = theXmlString.GetString(eTip_PickBound);
				}
			}		
		}
	}

	if(pItem->IsCanEquip())
	{
		ItemDefine::SItemCanEquip * pEquip = (ItemDefine::SItemCanEquip*)pItem;
		if(pEquip && m_stItem.itembaseinfo.nOnlyInt != 0)
		{
			/*if((m_stItem.equipdata.unBindCount == 0xFFFF && pEquip->unBindCount !=0xFFFF) || (m_stItem.equipdata.unBindCount != 0xFFFF && pEquip->unBindCount ==0xFFFF))
			{
				m_stItem.equipdata.unBindCount = pEquip->unBindCount;
			}*/
			if(m_stItem.equipdata.unBindCount == 0xFFFF && pEquip->unBindCount !=0xFFFF)
			{
				m_stItem.equipdata.unBindCount = pEquip->unBindCount;
			}
			if(m_stItem.equipdata.unBindCount == 0xFFFF)
			{
				m_stInfo[m_ucIconInfoLine].m_strInfo += theXmlString.GetString(eText_UnBind);
			}
			else if(m_stItem.equipdata.unBindCount == 0)
			{
				m_stInfo[m_ucIconInfoLine].m_strInfo += theXmlString.GetString(eText_UnBind_Non);
			}
			else
			{
				char szText[256] = {0};
				sprintf_s(szText, sizeof(szText)-1,theXmlString.GetString(eText_UnBind_Num),m_stItem.equipdata.unBindCount);
				m_stInfo[m_ucIconInfoLine].m_strInfo += szText;
			}
		}
	}

	if (strlen(m_stInfo[m_ucIconInfoLine].m_strInfo.c_str()) > 0)
	{
		SetInfoRightText();
		SET_EQUIP( "%s", m_stInfo[m_ucIconInfoLine].m_strInfo.c_str(), Color_Config.getColor( CC_ItemTip_ItemBind ) );
	}
}

void S_IconInfoHero::ShowSkill( void* pItemDetail, INT nType )
{
    guardfunc;
    if( nType != ItemDefine::ITEMTYPE_SKILL )
    {
        if( nType != ItemDefine::ITEMTYPE_STATUS)
            return;
    }

    char szBuffer [eMAX_TEMP_BUFF] = {0};
    m_nCount = m_stItem.itembaseinfo.ustItemCount;
    ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( m_stItem.itembaseinfo.ustItemID, m_nCount < 1 ? 1 : m_nCount );
    ItemDefine::SItemSkill* pNextLvlSkill = NULL;

    BOOL bMaxLel = FALSE;
    ItemDefine::SMonster	*pMonster = NULL,
        *pNextMonster = NULL;
    ItemDefine::SItemStatus *pStatus = NULL,
        *pNextStatus = NULL;

    if( nType == ItemDefine::ITEMTYPE_SKILL )
    {
        if ( !pSkill )
        {
            assert( false );
            return;
        }

        m_nCount = m_stItem.itembaseinfo.ustItemCount;
        if( m_nCount < pSkill->ustSkillMaxLvl )
        {
            pNextLvlSkill = GettheItemDetail().GetSkillByID( m_stItem.itembaseinfo.ustItemID,	( m_nCount < 1 ? 1 : m_nCount ) + 1 );
        }
        else
        {
            pNextLvlSkill = pSkill;
            bMaxLel = true;
        }

        if( pSkill->bSummonSkill )
        {
            pMonster = GettheItemDetail().GetMonsterById( pSkill->nSummonMonsterId );
            if( pNextLvlSkill && pNextLvlSkill->bSummonSkill )
            {
                pNextMonster = GettheItemDetail().GetMonsterById( pNextLvlSkill->nSummonMonsterId );
            }
        }
        //pNextStatus = GettheItemDetail().GetStatusBySkill( pNextLvlSkill );
        if( /*!pNextStatus ||*/ bMaxLel )
        {
            m_bNextLvl = false;
            pNextLvlSkill = NULL;
        }
    }
    else
    {
        pStatus = GettheItemDetail().GetStatus( m_stItem.itembaseinfo.ustItemID, m_nCount );
        if( !pStatus )
        {
            return;
        }
        pNextStatus = NULL;
    }

    for( int i = 0 ; i < s_nProduceSkillsCount ; ++i )
    {
        if( m_stItem.itembaseinfo.ustItemID == s_ProduceSkillIds[i] )
        {
            WriteProduceSkillData( pSkill );
            return;
        }		
    }

    switch( m_eFlag )
    {
    case eTipFlag_SkillNoNextLevel:
        {
            // 添加skill信息
            WriteSkillData( pSkill );
        }
        break;
    case eTipFlag_SkillWithNextLevel:
        {
            // 添加skill信息
            WriteSkillData( pSkill );
            if( pNextLvlSkill && m_nCount )
            {
                sprintf( szBuffer, "%s", theXmlString.GetString( eUI_NextLevel ) );
                SHOW_STRING( "", Color_Config.getColor( CC_ItemTip_Other ) );
                SHOW_STRING( szBuffer, Color_Config.getColor( CC_ItemTip_Skill_NextLevel ) );
                WriteSkillData( pNextLvlSkill, true );
            }
            else if( !pNextLvlSkill && m_nCount )
            {
                sprintf( szBuffer, "%s", theXmlString.GetString( eTip_AlreadyMaxLevel ) );
                SHOW_STRING( szBuffer, Color_Config.getColor( CC_ItemTip_Skill_MaxLevel ) );				
            }
        }
        break;
    case eTipFlag_SkillTree:
        {			
            WriteSkillTreeData( pSkill );
            if( pNextLvlSkill && m_nCount )
            {
                // "下一级"
                sprintf( szBuffer, "%s", theXmlString.GetString( eUI_NextLevel ) );
                SHOW_STRING( szBuffer, Color_Config.getColor( CC_ItemTip_Skill_NextLevel ) );
                WriteSkillTreeData( pNextLvlSkill );				
                // 写限制信息
                WriteSkillRestricData( pNextLvlSkill );
            }
            else
            {
                //todo: 已经升级到最高级
            }

        }
        break;
    case eTipFlag_Status:
        {
            // 添加status信息
            WriteStatusData( pStatus );
        }
        break;
    default:
        break;
    }

    unguard;
}

void S_IconInfoHero::ShowMaterial( void* pItemDetail, INT nType )
{
	if( nType != ItemDefine::ITEMTYPE_MATERIAL )
		return;
	char szTemp [256] = {0};

	for (int nloop=0;nloop<SCharItem::EConstDefine_BaseRandMaxCount;++nloop)
	{
		if (m_stItem.equipdata.baseRands[nloop] != InvalidLogicNumber)
		{
			ItemDefine::SRandAttribute* pArmourRand = GettheItemDetail().GetRandByID(m_stItem.equipdata.baseRands[nloop]);
			if (!pArmourRand)
				continue;

			for( int i = 0 ; i < ItemDefine::SRandAttribute::CD_TypeCount ; ++ i )
			{
				std::string strGemAttr;
				int nRandValue = S_IconInfoHero::GetRandValueByType( pArmourRand, i );
				if( pArmourRand->type[i] == RT_None )
					continue;

				if( pArmourRand->type[i] == RT_AddMoveSpeed )
				{
					sprintf( szTemp, "%s+%.2f", S_IconInfoHero::GetRandStringByType( pArmourRand->type[i] ).c_str(), ( float )nRandValue / 100.0f );
					strGemAttr = szTemp;
				}
				else
				{
					sprintf( szTemp, "%s+%d", S_IconInfoHero::GetRandStringByType( pArmourRand->type[i] ).c_str(), nRandValue );  
					strGemAttr = szTemp;
					if( pArmourRand->type[i] == RT_AddExpPer )
						strGemAttr += "%";
				}
				SHOW_STRING( strGemAttr, S_IconInfoHero::GetQualityColor( ItemDefine::EQL_Blue ) );
			}
		}
	}
}

void S_IconInfoHero::ShowGem( void* pItemDetail, INT nType )
{
    if( nType != ItemDefine::ITEMTYPE_GEM )
        return;

    ItemDefine::SItemGem* pGem = NULL;
    if( pItemDetail )
    {
        pGem = ( ItemDefine::SItemGem* )pItemDetail;
    }
    else
    {
        return;
    }

    // 一颗宝石2属性
    char szTemp[MAX_PATH] = {0};
    for( int j = 0; j < ItemDefine::SItemGem::CD_TypeCount; ++j )
    {
        std::string strGemAttr = GetRandStringByType( pGem->type[j] );
        if( strGemAttr.empty() )
            continue;

        if( pGem->type[j] == RT_AddMoveSpeed )
        {
            MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%.2f", strGemAttr.c_str(), pGem->value[j].fValue );
            strGemAttr = szTemp;
        }
        else
        {
            MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", strGemAttr.c_str(), ( int )pGem->value[j].fValue );
            strGemAttr = szTemp;
            if( pGem->type[j] == RT_AddExpPer )
                strGemAttr += "%";
        }
        SHOW_STRING( strGemAttr, Color_Config.getColor( CC_ItemTip_Gem ) );
    }
}

void S_IconInfoHero::ShowOthers( void* pItemDetail, INT nType )
{
    if( (nType != ItemDefine::ITEMTYPE_MATERIAL)
        && (nType != ItemDefine::ITEMTYPE_TASK) 
        && (nType != ItemDefine::ITEMTYPE_RESTORE) 
        && (nType != ItemDefine::ITEMTYPE_ACTION)
        && (nType != ItemDefine::ITEMTYPE_OTHER )
        && (nType != ItemDefine::ITEMTYPE_REEL )
        && (nType != ItemDefine::ITEMTYPE_TREASUREBOX )
        && (nType != ItemDefine::ITEMTYPE_CHECKUP )
        && (nType != ItemDefine::ITEMTYPE_GUILD )
        && (nType != ItemDefine::ITEMTYPE_REALAWARD )
        && (nType != ItemDefine::ITEMTYPE_STATUS
        && (nType != ItemDefine::ITEMTYPE_SPECIAL)
        && (nType != ItemDefine::ITEMTYPE_GEM))
        )
        return;	

    if( !pItemDetail )
        return;

    ItemDefine::SItemCommon* pItem = (ItemDefine::SItemCommon*)pItemDetail;

    char szTemp[256];
    // 道具说明	
    const DWORD dwItemIntroColor = Color_Config.getColor( CC_ItemTip_Item_Introduction );
    memset( szTemp, 0, sizeof(szTemp) );
    int nLength = 0;
    std::string szItemDesc = pItem->GetItemDesc();
    if(nType == ItemDefine::ITEMTYPE_SPECIAL)
    {
        ItemDefine::SItemSpecial* pItemSpecial = (ItemDefine::SItemSpecial*)pItemDetail;
        if(pItemSpecial)
        {
            if(pItemSpecial->uchSpecialType == ItemDefine::SItemSpecial::ECD_MarriageCard)  //喜帖
            {
                if ( m_stItem.itembaseinfo.szCreaterName[0] != 0 )
                {
                    char szDesc[512] = {0};
                    sprintf_s(szDesc,sizeof(szDesc)/sizeof(char) - 1,szItemDesc.c_str(),m_stItem.itembaseinfo.szCreaterName);
                    szItemDesc.clear();
                    szItemDesc = szDesc;
                }
            }
        }
    }
    for ( UINT n=0; n<szItemDesc.size(); n++ )
    {
        if ( szItemDesc[n] != 0 &&
            szItemDesc[n] == '\\' && szItemDesc[n+1] == 'n' )
        {
            m_stInfo[m_ucIconInfoLine].m_strInfo = szTemp;
            m_stInfo[m_ucIconInfoLine].m_col = dwItemIntroColor;
            memset( szTemp, 0, sizeof(szTemp) );
            nLength = 0;
            m_ucIconInfoLine++;
            n++;
        }
        else if ( n < szItemDesc.size()-10 &&
            szItemDesc[n] == '<' && szItemDesc[n+1] == '#' )
        {
            char szColor[10];
            memset( szColor, 0, sizeof(szColor) );
            memcpy( szColor, &szItemDesc[n+2], 8 );
            sscanf( szColor, "%x", &dwItemIntroColor );
            n += 10;
        }
        else
        {
            szTemp[nLength++] = szItemDesc[n];
            if ( n == szItemDesc.size() - 1 && strlen(szTemp) > 0 )
            {
                m_stInfo[m_ucIconInfoLine].m_strInfo = szTemp;
                m_stInfo[m_ucIconInfoLine].m_col = dwItemIntroColor;
                m_ucIconInfoLine++;
            }
        }
        assert( m_ucIconInfoLine < MAX_ICON_INFO_EX_LINE_COUNT );
    }
    if( nType == ItemDefine::ITEMTYPE_ACTION || 
        nType == ItemDefine::ITEMTYPE_OTHER  ||
        nType == ItemDefine::ITEMTYPE_REEL	  ||
        nType == ItemDefine::ITEMTYPE_REALAWARD
        )
        return;

    // 卖出价格
    if( GetFlag() == eTipFlag_ShowMoney && nType != ItemDefine::ITEMTYPE_TASK && pItem->bIsCanSellShop )
    {
		MouseTipDrawLine();
        int gold = 0, silver = 0, copper = 0;
        thePlayerRole.GetGSCFromMoney(Cost(),gold,silver,copper);

        std::stringstream sstr;
        if (gold > 0)
            sstr << gold << theXmlString.GetString(eText_Money_Gold);
        if (silver > 0)
            sstr << silver << theXmlString.GetString(eText_Money_Silver);
        if (copper > 0)
            sstr << copper << theXmlString.GetString(eText_Money_Copper);
		else 
		{
			if (gold == 0 && silver == 0)
				sstr << copper << theXmlString.GetString( eText_Money_Copper );
		}

        sprintf( szTemp, "%s %s%s", theXmlString.GetString(eText_Title_SellPrice), sstr.str().c_str(), theXmlString.GetString(eText_Bind_Money) );
        m_stInfo[m_ucIconInfoLine].m_col = Color_Config.getColor( CC_ItemTip_SellPrice );
        m_stInfo[m_ucIconInfoLine++].m_strInfo = szTemp;
    }	
}

void S_IconInfoHero::WriteSkillTreeData( void* pSkillData )
{
	if( !pSkillData )
		return;

	ItemDefine::SItemSkill* pSkill = (ItemDefine::SItemSkill*)pSkillData;
	if( !pSkill )
		return;

	char szBuffer[256];
    const DWORD dwItemIntroColor = Color_Config.getColor( CC_ItemTip_Item_Introduction );
	//技能说明
	memset( szBuffer, 0, sizeof(szBuffer) );
	int nLength = 0;
	std::string szSkillDesc = pSkill->GetSkillDescription();
	for ( UINT n = 0 ; n < szSkillDesc.size() ; ++ n )
	{
		if ( szSkillDesc[n] != 0 &&
			szSkillDesc[n] == '\\' && szSkillDesc[n+1] == 'n' )
		{
			m_stInfo[m_ucIconInfoLine].m_strInfo = szBuffer;
			m_stInfo[m_ucIconInfoLine].m_col = dwItemIntroColor;
			memset( szBuffer, 0, sizeof(szBuffer) );
			nLength = 0;
			m_ucIconInfoLine++;
			n++;
		}
		else if ( n < szSkillDesc.size()-10 &&
			szSkillDesc[n] == '<' && szSkillDesc[n+1] == '#' )
		{
			char szColor[10];
			memset( szColor, 0, sizeof(szColor) );
			memcpy( szColor, &szSkillDesc[n+2], 8 );
			sscanf( szColor, "%x", &dwItemIntroColor );
			n += 10;
		}		
		else
		{
			szBuffer[nLength++] = szSkillDesc[n];
			if ( n == szSkillDesc.size() - 1 && strlen(szBuffer) > 0 )
			{
				m_stInfo[m_ucIconInfoLine].m_strInfo = szBuffer;
				m_stInfo[m_ucIconInfoLine].m_col = dwItemIntroColor;
				m_ucIconInfoLine++;
			}
		}
		assert( m_ucIconInfoLine < MAX_ICON_INFO_EX_LINE_COUNT );
	}
	// 技能等级/未学习
	if( m_nCount == 0 ) 
	{
		sprintf( szBuffer, "%s\n", theXmlString.GetString( eText_Skill_NotStudy ) );
		SHOW_STRING( szBuffer, Color_Config.getColor( CC_ItemTip_Skill_NotLearn ) );
	}
	else
	{
		sprintf( szBuffer, "%s%d\n", theXmlString.GetString( eText_Title_Skill_Level ), pSkill->ustLevel );
		SHOW_STRING( szBuffer, Color_Config.getColor( CC_ItemTip_Skill_Level ) );
	}
}

void S_IconInfoHero::WriteProduceSkillData( void* pSkillData )
{
	ItemDefine::SItemSkill* pSkill = (ItemDefine::SItemSkill*)pSkillData;
	if( !pSkill )
		return;

	char szBuffer [eMAX_TEMP_BUFF] = {0};	
    const DWORD dwItemIntroColor = Color_Config.getColor( CC_ItemTip_Item_Introduction );
	//技能说明
	int nLength = 0;
	sprintf_s( szBuffer, eMAX_TEMP_BUFF, " " );
	SHOW_STRING( szBuffer, dwItemIntroColor );
	memset( szBuffer, 0, sizeof(szBuffer) );
	nLength = 0;
	std::string szSkillDesc = pSkill->GetSkillDescription();
	for ( UINT n = 0 ; n < szSkillDesc.size() ; ++ n )
	{
		if ( szSkillDesc[n] != 0 &&
			szSkillDesc[n] == '\\' && szSkillDesc[n+1] == 'n' )
		{
			m_stInfo[m_ucIconInfoLine].m_strInfo = szBuffer;
			m_stInfo[m_ucIconInfoLine].m_col = dwItemIntroColor;
			memset( szBuffer, 0, sizeof(szBuffer) );
			nLength = 0;
			m_ucIconInfoLine++;
			n++;
		}
		else if ( n < szSkillDesc.size()-10 &&
			szSkillDesc[n] == '<' && szSkillDesc[n+1] == '#' )
		{
			char szColor[10];
			memset( szColor, 0, sizeof(szColor) );
			memcpy( szColor, &szSkillDesc[n+2], 8 );
			sscanf( szColor, "%x", &dwItemIntroColor );
			n += 10;
		}
		else
		{
			szBuffer[nLength++] = szSkillDesc[n];
			if ( n == szSkillDesc.size() - 1 && strlen(szBuffer) > 0 )
			{
				m_stInfo[m_ucIconInfoLine].m_strInfo = szBuffer;
				m_stInfo[m_ucIconInfoLine].m_col = dwItemIntroColor;
				m_ucIconInfoLine++;
			}
		}
		assert( m_ucIconInfoLine < MAX_ICON_INFO_EX_LINE_COUNT );
	}
}
void S_IconInfoHero::WriteSkillData( void* pSkillData, bool bIsNextLevel /* = false */ )
{	
	ItemDefine::SItemSkill* pSkill = (ItemDefine::SItemSkill*)pSkillData;
	if( !pSkill )
		return;

	char szBuffer [eMAX_TEMP_BUFF] = {0};
	const DWORD dwItemIntroColor = Color_Config.getColor( CC_ItemTip_Item_Introduction );

	//消耗mp
	if( pSkill->ustCostMP != 0 )
	{
		if( !bIsNextLevel )
			SetInfoRightText();
		if( pSkill->ustCostMP > 0 )
		{
			MeSprintf_s( szBuffer, sizeof(szBuffer)-1, theXmlString.GetString( eText_Skill_CostMP ),
				GetMPTypeString( thePlayerRole.GetProfession() ), (INT)pSkill->ustCostMP );
		}
		SHOW_STRING( szBuffer, dwItemIntroColor );
	}	
	//冷却时间
	if( pSkill->dwSkillCoolDownTime != 0 )
	{		
		if( !bIsNextLevel )
			SetInfoRightText();
		if( pSkill->dwSkillCoolDownTime > 0 )
		{
			float fVal = pSkill->dwSkillCoolDownTime/1000.0f ;
			sprintf_s( szBuffer, sizeof(szBuffer)-1, theXmlString.GetString(eText_Skill_SkillCoolDownTime), fVal );
		}
		SHOW_STRING( szBuffer, dwItemIntroColor );
	}
	if( !bIsNextLevel ) // 下一级里面不显示这些信息
	{
		// 技能类型
		int nSkillCategory = -1;
		// 小队技能优先显示
		if( pSkill->specialSkillType >= ItemDefine::ESST_Team && pSkill->specialSkillType < ItemDefine::ESST_TeamMax )
		{
			nSkillCategory = eUI_SkillCategory_Team;
		}
		else
		{
			switch( pSkill->sSkillCategory )
			{
			case ItemDefine::SCT_Attack://主动
			case ItemDefine::SCT_MountMasterInitiativeUnControl:
			case ItemDefine::SCT_MountMasterInitiativeControl:
			case ItemDefine::SCT_PetMasterAutoUnControl:
			case ItemDefine::SCT_PetMasterManualControl:
			case ItemDefine::SCT_HeroAttack:
				{
					nSkillCategory = eUI_SkillCategory_Attack;
				}		
				break;
			case ItemDefine::SCT_Passive://被动
			case ItemDefine::SCT_MountPassive:
			case ItemDefine::SCT_PetPassive:
			case ItemDefine::SCT_HeroPassive:
				{
					nSkillCategory = eUI_SkillCategory_Passive;
				}
				break;
			case ItemDefine::SCT_Assistant://辅助
				{
					nSkillCategory = eUI_SkillCategory_Assistant;
				}
				break;
			default:
				break;
			}
		}
		sprintf_s( szBuffer, sizeof(szBuffer)-1, "%s", theXmlString.GetString( nSkillCategory ) );
		SHOW_STRING( szBuffer, dwItemIntroColor );

		//作用对象
		int nSkillTargetOffset = eUI_SillTyps_Target_no;
		sprintf_s( szBuffer, sizeof(szBuffer)-1, "%s %s", theXmlString.GetString( eUI_SillTyps_TargetType ), theXmlString.GetString( pSkill->stTargetType + nSkillTargetOffset ) );
        if( pSkill->sSkillCategory != ItemDefine::SCT_Passive && !pSkill->bSummonSkill )
		    SHOW_STRING( szBuffer, dwItemIntroColor );

		// 作用范围
		int nType = 0;
		switch( pSkill->shCastType )
		{
		case ItemDefine::casttype_singletarget:
			nType = eSkillCastType_SingleTarget;
			break;
		case ItemDefine::casttype_AOEPointCircleArea:
			nType = eSkillCastType_PointCircle;
			break;
		case ItemDefine::casttype_AOEcircleself:
			nType = eSkillCastType_SelfCircle;
			break;
		case ItemDefine::casttype_AOEquartercirlcefrontage:
			nType = eSkillCastType_QuarterCirleFront;
			break;
		case ItemDefine::casttype_AOETargetcirclearea:
			nType = eSkillCastType_PointAOE;
			break;			
		}
		if( nType != 0 )
		{
			char szString[eMAX_TEMP_BUFF] = {0};
			sprintf_s( szBuffer, sizeof(szBuffer)-1, "%s %s", theXmlString.GetString( eSkillCastType_Title ), theXmlString.GetString( nType ) );
			if( nType != eSkillCastType_SingleTarget )
			{
				sprintf_s( szString, sizeof(szString)-1, szBuffer, (int)pSkill->fAOEradius );
				strncpy( szBuffer, szString, sizeof(szBuffer)-1 );
			}
            if( pSkill->sSkillCategory != ItemDefine::SCT_Passive && !pSkill->bSummonSkill
                && pSkill->stTargetType + nSkillTargetOffset != eUI_SillTyps_Target_myself )
			    SHOW_STRING( szBuffer, dwItemIntroColor );
		}	

		//吟唱时间	
		if( pSkill->ustPrepTime > 0 && pSkill->bShowIntonateBar )
		{
			sprintf( szBuffer, theXmlString.GetString( eText_Skill_PrepTime ), (FLOAT)pSkill->ustPrepTime/1000.0f );
		}
		else if( pSkill->ustPrepTime <= 0 || !pSkill->bShowIntonateBar )//瞬间释放
		{
			sprintf( szBuffer, "%s",  theXmlString.GetString( eText_Title_UseImmediate ) );
		}
        if( pSkill->sSkillCategory != ItemDefine::SCT_Passive )
            SHOW_STRING( szBuffer, dwItemIntroColor );	

		//施法距离
		if( pSkill->fRangeCanCast != 0 )
		{
			if( pSkill->fRangeCanCast > 0)
			{
				sprintf( szBuffer,"%s %d - %d", theXmlString.GetString(eText_Title_UseDistance),
					(INT)pSkill->fRangeCanCastMin, (INT)pSkill->fRangeCanCast );
			}
            if( pSkill->sSkillCategory != ItemDefine::SCT_Passive && !pSkill->bSummonSkill
                && pSkill->stTargetType + nSkillTargetOffset != eUI_SillTyps_Target_myself )
			    SHOW_STRING( szBuffer, dwItemIntroColor );
		}

		////////消耗内容

		//消耗hp
		if( pSkill->ustCostHP != 0 )
		{
			if( !bIsNextLevel )
				SetInfoRightText();
			if( pSkill->ustCostHP > 0 )
			{
				sprintf( szBuffer,  theXmlString.GetString(eText_Skill_CostHP), (INT)pSkill->ustCostHP );
			}
			SHOW_STRING( szBuffer, dwItemIntroColor );
		}
		if( pSkill->ustCostHPPer != 0 )
		{
			if( !bIsNextLevel )
				SetInfoRightText();
			if( pSkill->ustCostHPPer > 0 )
			{
				sprintf( szBuffer, theXmlString.GetString(eText_Skill_CostHPPer),
					(INT)pSkill->ustCostHPPer );

			}
			SHOW_STRING( szBuffer, dwItemIntroColor );
		}

		if( pSkill->ustCostMPPer != 0 )
		{
			if( !bIsNextLevel )
				SetInfoRightText();
			if( pSkill->ustCostMPPer > 0 )
			{
				MeSprintf_s( szBuffer, sizeof( szBuffer ) - 1, theXmlString.GetString( eText_Skill_CostMPPer ),
					GetMPTypeString( thePlayerRole.GetProfession() ), (INT)pSkill->ustCostMPPer );

			}
			SHOW_STRING( szBuffer, dwItemIntroColor );
		}

		//消耗斗气
		if( pSkill->usConsumeFightPower > 0 )
		{
			if( !bIsNextLevel )
				SetInfoRightText();

			if( pSkill->usConsumeFightPower > 0 )
			{
				MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s%d", theXmlString.GetString( eText_Skill_CostExPower ),
                    ( int )pSkill->usConsumeFightPower );
			}
			SHOW_STRING( szBuffer, dwItemIntroColor );
		}

        // 增加捕虫     added by zhuomeng.hu		[11/9/2010]
        if( pSkill->ustItemID == ItemDefine::eCSI_BuChong  )//捕虫
        {
            int nPoint = thePlayerRole.m_pBaseInfo->liveinfo.nSkillPoint[ERT_BuChong];
            int nMaxPoint = CaculateSkillPointMax( m_nCount );
			sprintf_s( szBuffer, eMAX_TEMP_BUFF, "%s: %d / %d", theXmlString.GetString( eText_SkillPoint ), nPoint, nMaxPoint );
            SHOW_STRING( szBuffer, dwItemIntroColor );
        }
		else if( pSkill->ustItemID == ItemDefine::eCSI_CaiYao  )//采药
		{
			int nPoint = thePlayerRole.m_pBaseInfo->liveinfo.nSkillPoint[ERT_CaiYao];
			int nMaxPoint = CaculateSkillPointMax( m_nCount );
			sprintf_s( szBuffer, eMAX_TEMP_BUFF, "%s: %d / %d", theXmlString.GetString( eText_SkillPoint ), nPoint, nMaxPoint );
			SHOW_STRING( szBuffer, dwItemIntroColor );
		}
		else if( pSkill->ustItemID == ItemDefine::eCSI_CaiKuang )// 采矿
		{
			int nPoint = thePlayerRole.m_pBaseInfo->liveinfo.nSkillPoint[ERT_CaiKuang];
			int nMaxPoint = CaculateSkillPointMax( m_nCount );
			sprintf_s( szBuffer, eMAX_TEMP_BUFF, "%s: %d / %d", theXmlString.GetString( eText_SkillPoint ), nPoint, nMaxPoint );
			SHOW_STRING( szBuffer, dwItemIntroColor );
		}
		//技能item描述
		memset( szBuffer, 0, sizeof(szBuffer) );
		int nLength = 0;
		std::string szItemDesc = pSkill->GetItemDesc();
		for ( UINT n = 0 ; n < szItemDesc.size() ; ++ n )
		{
			if ( szItemDesc[n] != 0 &&
				szItemDesc[n] == '\\' && szItemDesc[n+1] == 'n' )
			{
				m_stInfo[m_ucIconInfoLine].m_strInfo = szBuffer;
				m_stInfo[m_ucIconInfoLine].m_col = dwItemIntroColor;
				memset( szBuffer, 0, sizeof(szBuffer) );
				nLength = 0;
				m_ucIconInfoLine++;
				n++;
			}
			else if ( n < szItemDesc.size()-10 &&
				szItemDesc[n] == '<' && szItemDesc[n+1] == '#' )
			{
				char szColor[10];
				memset( szColor, 0, sizeof(szColor) );
				memcpy( szColor, &szItemDesc[ n + 2 ], 8 );
				sscanf( szColor, "%x", &dwItemIntroColor );
				n += 10;
			}
			else
			{
				szBuffer[nLength++] = szItemDesc[n];
				if ( n == szItemDesc.size() - 1 && strlen(szBuffer) > 0 )
				{
					m_stInfo[m_ucIconInfoLine].m_strInfo = szBuffer;
					m_stInfo[m_ucIconInfoLine].m_col = dwItemIntroColor;
					m_ucIconInfoLine++;
				}
			}
			assert( m_ucIconInfoLine < MAX_ICON_INFO_EX_LINE_COUNT );
		}	
	}	

	//技能说明
	int nLength = 0;
	sprintf_s( szBuffer, eMAX_TEMP_BUFF, " " );
	SHOW_STRING( szBuffer, Color_Config.getColor( CC_ItemTip_Other ) );
	memset( szBuffer, 0, sizeof(szBuffer) );
	nLength = 0;
	std::string szSkillDesc = pSkill->GetSkillDescription();
	for ( UINT n = 0 ; n < szSkillDesc.size() ; ++ n )
	{
		if ( szSkillDesc[n] != 0 &&
			szSkillDesc[n] == '\\' && szSkillDesc[n+1] == 'n' )
		{
			m_stInfo[m_ucIconInfoLine].m_strInfo = szBuffer;
			m_stInfo[m_ucIconInfoLine].m_col = dwItemIntroColor;
			memset( szBuffer, 0, sizeof(szBuffer) );
			nLength = 0;
			m_ucIconInfoLine++;
			n++;
		}
		else if ( n < szSkillDesc.size()-10 &&
			szSkillDesc[n] == '<' && szSkillDesc[n+1] == '#' )
		{
			char szColor[10];
			memset( szColor, 0, sizeof(szColor) );
			memcpy( szColor, &szSkillDesc[n+2], 8 );
			sscanf( szColor, "%x", &dwItemIntroColor );
			n += 10;
		}
		else if ( n < szSkillDesc.size()-2 &&
			szSkillDesc[n] == '<' && szSkillDesc[n+1] == '@' && (szSkillDesc[n+2] == '1' || szSkillDesc[n+2] == '2'))
		{
			int nNeedID = 0; 
			if (szSkillDesc[n + 2] == '1')
			{
				nNeedID = 1; 				
			}
			else if (szSkillDesc[n + 2] == '2') 
			{
				nNeedID = 2; 				
			}	
			XinFaConfig::STalentXinFa* pXinFa = NULL;
			if (bIsNextLevel)
			{
				//根据填的心法ID与需要等级去心法表里取得值
				pXinFa = theXinFaConfig.GetXinFaByID(pSkill->nXinFaID, pSkill->nLearnNeedXinFaLevel);				
			}
			else
			{
				//根据填的心法ID去人物心法包里面取得值
				SCharXinFa* pCharXinFa = thePlayerRole.m_xinFaBag.GetXinFaByID(pSkill->nXinFaID);
				if (pCharXinFa)
				{
					if (pCharXinFa->nXinFaLevel < pSkill->nLearnNeedXinFaLevel)
					{
						pXinFa = theXinFaConfig.GetXinFaByID(pSkill->nXinFaID, pSkill->nLearnNeedXinFaLevel);
					}
					else
					{
						pXinFa = theXinFaConfig.GetXinFaByID(pCharXinFa->nXinFaID, pCharXinFa->nXinFaLevel);
					}						
				}
				else
				{
					//根据填的心法ID与需要等级去心法表里取得值
					pXinFa = theXinFaConfig.GetXinFaByID(pSkill->nXinFaID, pSkill->nLearnNeedXinFaLevel);
				}
							
			}
			if (pXinFa)
			{

				XinFaConfig::SXinFaSkill* pXinFaSkill = pXinFa->GetXinFaSkill(pSkill->ustItemID, pSkill->ustLevel);
				if (pXinFaSkill)
				{
					int nResult = 0;
					if (nNeedID == 1)
					{
						nResult = pXinFaSkill->attrValue[nNeedID - 1] + pSkill->nAddonDesc1;
					}
					else
					{
						nResult = pXinFaSkill->attrValue[nNeedID - 1] + pSkill->nAddonDesc2;
					}
					char szbuf[16];
					sprintf( szbuf, "%d", nResult );
					for (int i = 0; i < strlen(szbuf); ++i)
					{
						szBuffer[nLength++] = szbuf[i];
					}
				}				
			}
			n += 2;
		}
		else
		{
			szBuffer[nLength++] = szSkillDesc[n];
			if ( n == szSkillDesc.size() - 1 && strlen(szBuffer) > 0 )
			{
				m_stInfo[m_ucIconInfoLine].m_strInfo = szBuffer;
				m_stInfo[m_ucIconInfoLine].m_col = dwItemIntroColor;
				m_ucIconInfoLine++;
			}
		}
		assert( m_ucIconInfoLine < MAX_ICON_INFO_EX_LINE_COUNT );
	}


	// 技能等级/未学习
	if( m_nCount == 0 ) 
	{
		sprintf( szBuffer, "%s\n", theXmlString.GetString( eText_Skill_NotStudy ) );
		SHOW_STRING( szBuffer, Color_Config.getColor( CC_ItemTip_Skill_NotLearn ) );
	}
	else
	{
		sprintf( szBuffer, "%s%d\n", theXmlString.GetString( eText_Title_Skill_Level ), pSkill->ustLevel );
		SHOW_STRING( szBuffer, Color_Config.getColor( CC_ItemTip_Skill_Level ) );

		/*
		 * Author: 2013-1-22 9:53:35 wangshuai
		 * Desc:   在DEBUG下显示SkillID
		 */
#ifdef _DEBUG
		sprintf( szBuffer, "skill id: %d\n", pSkill->ustItemID );
		SHOW_STRING( szBuffer, 0xffff0000 );
		m_ucIconInfoLine++;
#endif
		
	}
}

void S_IconInfoHero::WriteSkillRestricData( void* pSkillData )
{
	//////////////////////////////////////////////////////////////////////////
	/// 不满足条件显示，否则不显示

	ItemDefine::SItemSkill* pSkill = (ItemDefine::SItemSkill*)pSkillData;
	if( !pSkill )
		return;

	char szBuffer[256];
	DWORD dwColor = Color_Config.getColor( CC_ItemTip_Skill_LearnNotReach );

	// 需要人物等级限制
	if ( pSkill->stLearnLevelReq != 0 )
	{
		if( thePlayerRole.GetLevel() < pSkill->stLearnLevelReq )
		{
			sprintf_s( szBuffer, 256, theXmlString.GetString(eTip_LearnSkillLevelReq), pSkill->stLearnLevelReq );
			SHOW_STRING( szBuffer, dwColor );
		}
	}
	//    学习时的 技能牵制条件
	for(int idx = 0; idx<3; idx++)
	{
		if ( pSkill->stSkillNeed[idx] != -1 && pSkill->stSkillLevelNeed[idx] != -1 )
		{
			ItemDefine::SItemSkill *pPreSkill = 
				GettheItemDetail().GetSkillByID( pSkill->stSkillNeed[idx], pSkill->stSkillLevelNeed[idx] );
			if ( pPreSkill )
			{
				int nSkillLevel = -1;
				for ( int n = 0; n<More_iMaxSkillKnown; n++ )
				{
					if ( thePlayerRole.m_charinfo.otherdataclient.skills.skill[n].ustSkillID == pSkill->stSkillNeed[idx] )
					{
						nSkillLevel = thePlayerRole.m_charinfo.otherdataclient.skills.skill[n].stSkillLevel;
						break;
					}
				}
				//不满足条件
				if ( nSkillLevel < pSkill->stSkillLevelNeed[idx] )
				{
					sprintf_s( szBuffer, 256, theXmlString.GetString(eTip_LearnSkillLevelNeed),
						pSkill->stSkillLevelNeed[idx], 
						pPreSkill->GetItemName() );
					SHOW_STRING( szBuffer, dwColor );
				}				
			}
		}
	}
}

void S_IconInfoHero::WriteStatusData( void* pStatusData, bool bIsNextLevel /* = false */ )
{
	if( !pStatusData )
		return;

	ItemDefine::SItemStatus *pStatus = ( ItemDefine::SItemStatus* )pStatusData;

    const DWORD dwItemIntroColor = Color_Config.getColor( CC_ItemTip_Item_Introduction );
	if( !pStatus )
		return;

	char szBuffer[1024] ={0};

	const char* szSign[2] = { "+", "-" };
	if (pStatus->stActualTime > 0)
	{
		sprintf( szBuffer,
			theXmlString.GetString( eText_Skill_DurationActualTime ),
			(pStatus->stActualTime)
			);

		SHOW_STRING( szBuffer, dwItemIntroColor );
	}
	else
	{
		if( pStatus->iDurationTime > 0 )
		{
			char szTitle[256] = {0};
			char szBufferT[256] = {0};		
			char szBufferS[256] = {0};
			char szBufferF[256] = {0};
			char szBuffer[256] = {0};		
			int nSecond = pStatus->iDurationTime / 1000;		
			int nDay = nSecond / ( 24 * 60 * 60 ) ;	
			int nLeft = nSecond % ( 24 * 60 * 60 );
			int nHour = nLeft / ( 60 * 60 );
			nLeft = nLeft % ( 60 * 60 );
			int nMinute = nLeft / 60;
			nLeft = nLeft % 60;

			std::string strTime;
			strTime.clear();     

			sprintf_s( szTitle, 256, "%s", theXmlString.GetString( eText_Skill_DurationTime ) );
			strTime += szTitle;

			if(nDay > 0)
			{
				sprintf_s(szBuffer,sizeof(szBuffer),"%d%s",nDay,theXmlString.GetString(eText_Day));
				strTime += szBuffer;
			}

			if(nHour > 0)
			{
				sprintf_s(szBuffer,sizeof(szBuffer),"%d%s",nHour,theXmlString.GetString(eTimeUnit_Hour));
				strTime += szBuffer;
			}

			if(nMinute > 0)
			{
				sprintf_s(szBuffer,sizeof(szBuffer),"%d%s",nMinute,theXmlString.GetString(eTimeUnit_Minute));
				strTime += szBuffer;
			}

			if(nLeft > 0)
			{
				sprintf_s(szBuffer,sizeof(szBuffer),"%d%s",nLeft,theXmlString.GetString(eTimeUnit_Second));
				strTime += szBuffer;
			}

			SHOW_STRING( strTime, dwItemIntroColor );
		}
	}	
// 	if( pStatus->stChangedPhy_Hurt > 0 )
// 	{
// 
// 		sprintf( szBuffer, "%s: %d \n", 
// 			theXmlString.GetString(eUI_Hurt_AddPhisycsDam),
// 			pStatus->stChangedPhy_Hurt );
// 
// 		SHOW_STRING( szBuffer, dwItemIntroColor );
// 	}

// 	if( pStatus->fChangedPhy_HurtPer > 0 )
// 	{
// 
// 		sprintf( szBuffer, "%s: %d%%\n", 
// 			theXmlString.GetString(eUI_Hurt_AddPhisycsDam),
// 			(INT)(pStatus->fChangedPhy_HurtPer*100) );
// 
// 		SHOW_STRING( szBuffer, dwItemIntroColor );
// 	}


	if( pStatus->iBalanceDelayTime > 0 
		&& pStatus->stChanged_HP < 0 )
	{

		sprintf( szBuffer, theXmlString.GetString( eText_Skill_DelayTimeChangeHP ),
			(FLOAT)(pStatus->iBalanceDelayTime/1000.0f),
			abs( pStatus->stChanged_HP )		
			);

		SHOW_STRING( szBuffer, dwItemIntroColor );
	}

	if( pStatus->iBalanceDelayTime > 0 
		&& pStatus->stChanged_HP > 0 )
	{

		sprintf( szBuffer, theXmlString.GetString( eText_Skill_DelayTimeRestorHP ),
			(FLOAT)(pStatus->iBalanceDelayTime/1000.0f),
			pStatus->stChanged_HP		
			);


		SHOW_STRING( szBuffer, dwItemIntroColor );
	}

// 	if( pStatus->sFightHpRestore > 0 )
// 	{
// 
// 		sprintf( szBuffer, theXmlString.GetString(eText_Skill_AddRestorHP),
// 			(pStatus->sFightHpRestore)
// 			);
// 
// 
// 		SHOW_STRING( szBuffer, dwItemIntroColor );
// 	}

//	for( int i=0; i< EAttackType_Max; i++ )
//	{
//		if( i == pStatus->stMagicShield )
//		{

// 			sprintf( szBuffer, "%s: %d%s %s \n",
// 				theXmlString.GetString( eText_Skill_MaxAbsorb ),
// 				(INT)( pStatus->stSuckDamageMax ),
// 				theXmlString.GetString( eText_Point ),
// 				theXmlString.GetString( eUI_Hurt_AddPhisycsDam + i )
// 				);
// 
// 			SHOW_STRING( szBuffer, dwItemIntroColor );

// 			if( pStatus->stBurnMpPerDamage != 0 )
// 			{
// 
// 				sprintf( szBuffer, 
// 					theXmlString.GetString( eText_Skill_BurnMpPerDamage ),
// 					pStatus->stBurnMpPerDamage );
// 
// 
// 				SHOW_STRING( szBuffer, dwItemIntroColor );
// 			}

//		}
//	}
//	if( pStatus->stMagicShield == EAttackType_Max )
//	{

// 		sprintf( szBuffer, "%s: %d%s %s \n",
// 			theXmlString.GetString( eText_Skill_MaxAbsorb ),
// 			(INT)( pStatus->stSuckDamageMax ),
// 			theXmlString.GetString( eText_Point ),
// 			theXmlString.GetString( eText_Skill_AllDamage )
// 			);


		//SHOW_STRING( szBuffer, dwItemIntroColor );

// 		if( pStatus->stBurnMpPerDamage != 0 )
// 		{
// 
// 			sprintf( szBuffer, theXmlString.GetString( eText_Skill_BurnMpPerDamage ), pStatus->stBurnMpPerDamage );
// 
// 
// 			SHOW_STRING( szBuffer, dwItemIntroColor );
// 		}
//	}

// 	if( pStatus->fFightHpRestorePer > 0 )
// 	{
// 
// 		sprintf( szBuffer,theXmlString.GetString( eText_Skill_AddRestorHPPer ),
// 			(INT)( pStatus->fFightHpRestorePer*100 )
// 			);
// 
// 
// 		SHOW_STRING( szBuffer, dwItemIntroColor );
// 	}

// 	if( pStatus->sFightMpRestore > 0 )
// 	{
// 		sprintf( szBuffer,theXmlString.GetString( eText_Skill_AddRestorMP ),
// 			(pStatus->sFightMpRestore)
// 			);
// 
// 		SHOW_STRING( szBuffer, dwItemIntroColor );
// 	}

// 	if( pStatus->fFightMpRestorePer > 0 )
// 	{
// 
// 		sprintf( szBuffer, theXmlString.GetString( eText_Skill_AddRestorMPPer ),
// 			(INT)(pStatus->fFightMpRestorePer*100)
// 			);
// 
// 
// 		SHOW_STRING( szBuffer, dwItemIntroColor );
// 	}

	if( pStatus->stAbsorbExtraHPVal != 0 )
	{
		if (pStatus->stAbsorbExtraHPVal > 0 )
		{

			sprintf( szBuffer, theXmlString.GetString( eText_Skill_RestorHP ),
				(pStatus->stAbsorbExtraHPVal)
				);


			SHOW_STRING( szBuffer, dwItemIntroColor );
		}
		else if (pStatus->stAbsorbExtraHPVal < 0 )
		{

			sprintf( szBuffer, theXmlString.GetString( eText_Skill_ExtraHP ),
				(pStatus->stAbsorbExtraHPVal)
				);


			SHOW_STRING( szBuffer, dwItemIntroColor );
		}
	}
	if (pStatus->fChanged_ReboundVal > 0 )
	{

		sprintf( szBuffer,theXmlString.GetString( eText_Skill_ReboundHP ),
			(INT)(pStatus->fChanged_ReboundVal*100.0f)
			);


		SHOW_STRING( szBuffer, dwItemIntroColor );
	}
//===============================================================
	//魔法免疫 
	if (pStatus->bIsBeMagAttack  )
	{
		sprintf( szBuffer,theXmlString.GetString( eText_Buf_ContBeMagAttack ));
		SHOW_STRING( szBuffer, dwItemIntroColor );
	}

	//物理免疫
	if (pStatus->bIsBePhyAttack )
	{
		sprintf( szBuffer,theXmlString.GetString( eText_Buf_ContBePhyAttack ));
		SHOW_STRING( szBuffer, dwItemIntroColor );
	}
//===============================================================
	//状态闪避
	if(pStatus->hurtImmunity > 0)
	{
		 if (pStatus->iDurationTime > 0)
		 {
			 sprintf( szBuffer,theXmlString.GetString( eText_Buf_DamageMianYiCnt ),pStatus->hurtImmunity);
			 SHOW_STRING( szBuffer, dwItemIntroColor );
		 }     
	}
	//========================================================
	for (int i=0; i<EBaseAttr_MaxSize; i++ )
	{
		if( pStatus->stAddBaseAttr[i] == 0 )
			continue;

		if( pStatus->stAddBaseAttr[i] > 0 )
		{

			sprintf( szBuffer, "%s:%s%d\n",
				theXmlString.GetString( eTip_sAddStrength + i ),
				"+", pStatus->stAddBaseAttr[i]  );

		}
		else
		{

			sprintf( szBuffer, "%s:%d\n",
				theXmlString.GetString( eTip_sAddStrength + i ),
				(INT)pStatus->stAddBaseAttr[i] );


			SHOW_STRING( szBuffer, dwItemIntroColor );
		}

	}

	if( pStatus->stChanged_HPMax != 0 )
	{
		if( pStatus->stChanged_HPMax > 0 )
		{

			sprintf( szBuffer, "%s:%s%d\n",
				theXmlString.GetString(eUI_stChanged_HPMax),
				"+", (INT)pStatus->stChanged_HPMax );

		}
		else
		{

			sprintf( szBuffer, "%s:%d\n",
				theXmlString.GetString(eUI_stChanged_HPMax),
				(INT)pStatus->stChanged_HPMax );

		}
		SHOW_STRING( szBuffer, dwItemIntroColor );
	}
	
	if( pStatus->stChanged_MPMax != 0 )
	{
		if( pStatus->stChanged_MPMax > 0 )
		{

			sprintf( szBuffer, "%s:%s%d\n",
				theXmlString.GetString( eUI_stChanged_MPMax ),
				"+", (INT)pStatus->stChanged_MPMax );


		}
		else
		{

			sprintf( szBuffer, "%s:%d\n",
				theXmlString.GetString( eUI_stChanged_MPMax ),
				(INT)pStatus->stChanged_MPMax );


		}
		SHOW_STRING( szBuffer, dwItemIntroColor );
	}
	if( pStatus->changeMPMaxPer != 0 )
	{
		if( pStatus->changeMPMaxPer > 0 )
		{

			sprintf( szBuffer, "%s:%s%d%%\n",
				theXmlString.GetString( eUI_stChanged_MPMax ),
				"+", (INT)(pStatus->changeMPMaxPer) );


		}
		else
		{

			sprintf( szBuffer, "%s:%d%%\n",
				theXmlString.GetString( eUI_stChanged_MPMax ),
				(INT)(pStatus->changeMPMaxPer) );


		}
		SHOW_STRING( szBuffer, dwItemIntroColor );
	}
	if( pStatus->stChanged_Hit != 0 )
	{
		if( pStatus->stChanged_Hit > 0 )
		{

			sprintf( szBuffer, "%s:%s%d\n",
				theXmlString.GetString( eUI_sExact ),
				"+", (INT)pStatus->stChanged_Hit );


		}
		else
		{

			sprintf( szBuffer, "%s:%d\n",
				theXmlString.GetString( eUI_sExact ),
				(INT)pStatus->stChanged_Hit );


		}
		SHOW_STRING( szBuffer, dwItemIntroColor );
	}

	if( pStatus->stChanged_Hedge != 0 )
	{
		if( pStatus->stChanged_Hedge > 0 )
		{

			sprintf( szBuffer, "%s:%s%d\n",
				theXmlString.GetString( eUI_sDodge ),
				"+", (INT)pStatus->stChanged_Hedge );


		}
		else
		{

			sprintf( szBuffer, "%s:%d\n",
				theXmlString.GetString( eUI_sDodge ),
				(INT)pStatus->stChanged_Hedge );


		}
		SHOW_STRING( szBuffer, dwItemIntroColor );
	}

	if( pStatus->fMoveSpeedChanged != 0 )
	{
		if( pStatus->fMoveSpeedChanged > 0 )
		{

			sprintf( szBuffer, "%s:%s%d%%\n",
				theXmlString.GetString(eTip_sAddMoveSpeed),
				"+", (INT)(pStatus->fMoveSpeedChanged*100) );


		}
		else
		{

			sprintf( szBuffer, "%s:%d%%\n",
				theXmlString.GetString(eTip_sAddMoveSpeed),
				(INT)(pStatus->fMoveSpeedChanged*100) );


		}
		SHOW_STRING( szBuffer, dwItemIntroColor );
	}

	//还是攻击速度
// 	if( pStatus->stPrepSpeedChanged != 0 )
// 	{
// 		if( pStatus->stPrepSpeedChanged > 0 )
// 		{
// 
// 			sprintf( szBuffer, "%s:%d %%\n",
// 				theXmlString.GetString(eUI_stAttSpeedChanged),
// 				(INT)(-pStatus->stPrepSpeedChanged) );
// 
// 		}
// 		else
// 		{
// 
// 			sprintf( szBuffer, "%s:%s%d %%\n",theXmlString.GetString(eUI_stAttSpeedChanged),
// 				"+",(int)(-pStatus->stPrepSpeedChanged) );
// 
// 		} 
// 		SHOW_STRING( szBuffer, dwItemIntroColor );
// 	}
	if (pStatus->fAddExpMul != 0.0f)
	{
		if (pStatus->fAddExpMul > 0.0f)
		{
			float fTemp = pStatus->fAddExpMul+1;
			sprintf(szBuffer,theXmlString.GetString(eTip_Status_AddExp), fTemp );
			SHOW_STRING(szBuffer,dwItemIntroColor);
		}			
	}
	if (pStatus->fAddSkillExpMul != 0.0f)
	{
		if (pStatus->fAddSkillExpMul > 0.0f)
		{
			float fTemp = pStatus->fAddSkillExpMul+1;
			sprintf(szBuffer,theXmlString.GetString(eTip_Status_AddSkillExp), fTemp );
			SHOW_STRING(szBuffer,dwItemIntroColor);
		}
	}

// 	if( pStatus->fBackStrikePer != 0 )
// 	{
// 		float f = pStatus->fBackStrikePer*100.0f;
// 		if( pStatus->fBackStrikePer > 0 )
// 		{
// 
// 			sprintf( szBuffer, theXmlString.GetString(eText_Skill_BackStrikePer), (INT)f );
// 
// 
// 		}
// 		SHOW_STRING( szBuffer, dwItemIntroColor );
// 	}

// 	if ( pStatus->nAddWardValue != 0 )
// 	{
// 		if ( pStatus->nAddWardValue > 0 )
// 		{
// 
// 			sprintf(szBuffer,theXmlString.GetString(eText_Skill_AddWardValue), pStatus->nAddWardValue );
// 
// 
// 		}
// 		SHOW_STRING(szBuffer,dwItemIntroColor);
// 	}

// 	if ( pStatus->fAddWardRate != 0 )
// 	{
// 		if ( pStatus->fAddWardRate > 0 )
// 		{
// 
// 			INT nAddWardRate = pStatus->fAddWardRate*100;
// 			sprintf(szBuffer,theXmlString.GetString(eText_Skill_AddWardRate), nAddWardRate );
// 
// 
// 		}
// 		SHOW_STRING(szBuffer,dwItemIntroColor);
// 	}		
// 	if (pStatus->fAddIntonateRatePer > 0.0f)
// 	{
// 
// 		INT nAddIntonateRate = pStatus->fAddIntonateRatePer*100;			
// 		sprintf(szBuffer, theXmlString.GetString(eTipForSkill_AddIntonateRate),
// 			nAddIntonateRate);
// 
// 		SHOW_STRING(szBuffer,dwItemIntroColor);
// 	}
// 	if (pStatus->bIsNightDo)
// 	{
// 		sprintf(szBuffer, theXmlString.GetString(eTipForSkill_DoNight));
// 		SHOW_STRING(szBuffer,dwItemIntroColor);
// 	}

// 	if (pStatus->stComposeOdds > 0)
// 	{
// 		sprintf(szBuffer, theXmlString.GetString(eStatusAddCompoundRate),pStatus->stComposeOdds);
// 		SHOW_STRING(szBuffer,dwItemIntroColor);
// 	}
// 
// 	if (pStatus->stIntensifyOdds > 0)
// 	{
// 		sprintf(szBuffer, theXmlString.GetString(eStatusAddIntensifyRate),pStatus->stIntensifyOdds);
// 		SHOW_STRING(szBuffer,dwItemIntroColor);
// 	}

    // added by zhuomeng.hu		[12/4/2010]
    // 一级属性 (值)
    for( int i = 0; i < EBaseAttr_MaxSize; ++i )
    {
        if( pStatus->bAvail && pStatus->stAddBaseAttr[i] > 0 )
        {
			MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s:+%d", GetBaseAttrStringByType( i ).c_str(),
                ( int )pStatus->stAddBaseAttr[i] );
            SHOW_STRING( szBuffer, dwItemIntroColor );
        }
        else if( !pStatus->bAvail && pStatus->stAddBaseAttr[i] < 0 )
        {
            MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s%d", GetBaseAttrStringByType( i ).c_str(),
                ( int )pStatus->stAddBaseAttr[i] );
            SHOW_STRING( szBuffer, dwItemIntroColor );
        }
    }
    
    // 一级属性 (百分比)
    for( int i = 0; i < EBaseAttr_MaxSize; ++i )
    {
        if( pStatus->bAvail && pStatus->stAddBaseAttrPer[i] > 0 )
        {
			MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s:+%d%%", GetBaseAttrStringByType( i ).c_str(),
                ( int )pStatus->stAddBaseAttrPer[i] );
            SHOW_STRING( szBuffer, dwItemIntroColor );
        }
        else if( !pStatus->bAvail && pStatus->stAddBaseAttrPer[i] < 0 )
        {
            MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s%d%%", GetBaseAttrStringByType( i ).c_str(),
                ( int )pStatus->stAddBaseAttrPer[i] );
            SHOW_STRING( szBuffer, dwItemIntroColor );
        }
    }

    // 眩晕、恐惧、定身、沉默、减速
    if( !pStatus->bAvail )
    {
        switch( pStatus->negativeType )
        {
        case SNT_GIDDY:
            SHOW_STRING( theXmlString.GetString( eText_Debuf_Giddy ), dwItemIntroColor );
            break;
        case SNT_STAND:
            SHOW_STRING( theXmlString.GetString( eText_Debuf_Stand ), dwItemIntroColor );
            break;
        case SNT_SLOWDOWN:
            if( pStatus->fMoveSpeedChanged < 0 )
            {
                MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s%.2f", theXmlString.GetString( eText_Debuf_Slowdown ),
                    pStatus->fMoveSpeedChanged );
                SHOW_STRING( szBuffer, dwItemIntroColor );
            }
            else if( pStatus->nMoveSpeedPer < 0 )
            {
                MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s%d%%", theXmlString.GetString( eText_Debuf_Slowdown ),
                    pStatus->nMoveSpeedPer );
                SHOW_STRING( szBuffer, dwItemIntroColor );
            }
            break;
        case SNT_TORPID:
            SHOW_STRING( theXmlString.GetString( eText_Debuf_Torpid ), dwItemIntroColor );
            break;
        case SNT_AFRAID:
            SHOW_STRING( theXmlString.GetString( eText_Debuf_Afraid ), dwItemIntroColor );
            break;
        default:
            break;
        }
    }

    // 伤害减免 (百分比)
    if( pStatus->bAvail && pStatus->fSuckDamagePer > 0 )
    {
        int nDamagePer = pStatus->fSuckDamagePer;
        MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s%d%%", theXmlString.GetString( eText_Buf_DamageDerate ), nDamagePer );
        SHOW_STRING( szBuffer, dwItemIntroColor );
    }

    // 韧性
    if( pStatus->bAvail && pStatus->changeTenacity > 0 )
    {
		MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s:+%d", theXmlString.GetString( eTip_sAddTenacity ),
            pStatus->changeTenacity );
        SHOW_STRING( szBuffer, dwItemIntroColor );
    }
    else if( !pStatus->bAvail && pStatus->changeTenacity < 0 )
    {
        MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s%d", theXmlString.GetString( eTip_sAddTenacity ),
            pStatus->changeTenacity );
        SHOW_STRING( szBuffer, dwItemIntroColor );
    }

    // 生命最大值 (百分比)
    if( pStatus->bAvail && pStatus->changeHPMaxPer > 0 )
    {
		MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s:+%d%%", theXmlString.GetString( eUI_stChanged_HPMax ),
            pStatus->changeHPMaxPer );
        SHOW_STRING( szBuffer, dwItemIntroColor );
    }
    else if( pStatus->bAvail && pStatus->changeHPMaxPer < 0 )
    {
        MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s%d%%", theXmlString.GetString( eUI_stChanged_HPMax ),
            pStatus->changeHPMaxPer );
        SHOW_STRING( szBuffer, dwItemIntroColor );
    }

    // 3攻 (百分比)
	//物理攻击力百分比
    if( pStatus->bAvail && pStatus->changePhyAttackPer > 0 )
    {
        std::string strAtt = theXmlString.GetString(eText_PlayAtt_Short);
		MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s:+%d%%", strAtt.c_str(), pStatus->changePhyAttackPer );
        SHOW_STRING( szBuffer, dwItemIntroColor );
    }
    else if( !pStatus->bAvail && pStatus->changePhyAttackPer < 0 )
    {
        std::string strAtt = theXmlString.GetString(eText_PlayAtt_Short);
        MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s%d%%", strAtt.c_str(), pStatus->changePhyAttackPer );
        SHOW_STRING( szBuffer, dwItemIntroColor );
    }

	//魔法攻击力百分比
	if(pStatus->bAvail && pStatus->changeMagAttackPer > 0)
	{
		std::string strAtt = theXmlString.GetString(eText_PlayAtt_Magic);
		MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s:+%d%%", strAtt.c_str(), pStatus->changeMagAttackPer );
		SHOW_STRING( szBuffer, dwItemIntroColor );

	}
	else if(!pStatus->bAvail && pStatus->changeMagAttackPer < 0)
	{
		std::string strAtt = theXmlString.GetString(eText_PlayAtt_Magic);
		MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s%d%%", strAtt.c_str(), pStatus->changeMagAttackPer );
		SHOW_STRING( szBuffer, dwItemIntroColor );
	}

    // 3攻 (值)
	//物理攻击力
    if( pStatus->bAvail && pStatus->changePhyAttack  > 0 )
    {
        std::string strAtt = theXmlString.GetString(eText_PlayAtt_Short);
		MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s:+%d", strAtt.c_str(), ( int )pStatus->changePhyAttack);
        SHOW_STRING( szBuffer, dwItemIntroColor );
    }
    else if( !pStatus->bAvail && pStatus->changePhyAttack    < 0 )
    {
        std::string strAtt = theXmlString.GetString(eText_PlayAtt_Short);
        MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s%d", strAtt.c_str(), ( int )pStatus->changePhyAttack);
        SHOW_STRING( szBuffer, dwItemIntroColor );
    }

	//魔法攻击力
	if(pStatus->bAvail && pStatus->changeMagAttack > 0)
	{
		std::string strAtt = theXmlString.GetString(eText_PlayAtt_Magic);
		MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s:+%d", strAtt.c_str(), ( int )pStatus->changeMagAttack);
		SHOW_STRING( szBuffer, dwItemIntroColor );
	}
	else if( !pStatus->bAvail && pStatus->changeMagAttack < 0)
	{
		std::string strAtt = theXmlString.GetString(eText_PlayAtt_Magic);
		MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s%d", strAtt.c_str(), ( int )pStatus->changeMagAttack);
		SHOW_STRING( szBuffer, dwItemIntroColor );
	}

    // 3防 (百分比)
//     if( pStatus->bAvail && pStatus->changeDefendPer[EDefendType_Short] > 0 )
//     {
//         MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s+%d%%", theXmlString.GetString( eText_PlayDef_Short ),
//             pStatus->changeDefendPer[EDefendType_Short] );
//         SHOW_STRING( szBuffer, dwItemIntroColor );
//     }
//     else if( !pStatus->bAvail && pStatus->changeDefendPer[EDefendType_Short] < 0 )
//     {
//         MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s%d%%", theXmlString.GetString( eText_PlayDef_Short ),
//             pStatus->changeDefendPer[EDefendType_Short] );
//         SHOW_STRING( szBuffer, dwItemIntroColor );
//     }

//     if( pStatus->bAvail && pStatus->changeDefendPer[EDefendType_Long] > 0 )
//     {
//         MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s+%d%%", theXmlString.GetString( eText_PlayDef_Long ),
//             pStatus->changeDefendPer[EDefendType_Long] );
//         SHOW_STRING( szBuffer, dwItemIntroColor );
//     }
//     else if( !pStatus->bAvail && pStatus->changeDefendPer[EDefendType_Long] < 0 )
//     {
//         MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s%d%%", theXmlString.GetString( eText_PlayDef_Long ),
//             pStatus->changeDefendPer[EDefendType_Long] );
//         SHOW_STRING( szBuffer, dwItemIntroColor );
//     }

	if( pStatus->bAvail && pStatus->changeDefendPer[EDefendType_Physical] > 0 )
	{
		MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s:+%d%%", theXmlString.GetString( eText_PlayDef_Short ),
			pStatus->changeDefendPer[EDefendType_Physical] );
		SHOW_STRING( szBuffer, dwItemIntroColor );
	}
	else if( !pStatus->bAvail && pStatus->changeDefendPer[EDefendType_Physical] < 0 )
	{
		MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s%d%%", theXmlString.GetString( eText_PlayDef_Short ),
			pStatus->changeDefendPer[EDefendType_Physical] );
		SHOW_STRING( szBuffer, dwItemIntroColor );
	}

    if( pStatus->bAvail && pStatus->changeDefendPer[EDefendType_Magic] > 0 )
    {
		MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s:+%d%%", theXmlString.GetString( eText_PlayDef_Magic ),
            pStatus->changeDefendPer[EDefendType_Magic] );
        SHOW_STRING( szBuffer, dwItemIntroColor );
    }
    else if( !pStatus->bAvail && pStatus->changeDefendPer[EDefendType_Magic] < 0 )
    {
        MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s%d%%", theXmlString.GetString( eText_PlayDef_Magic ),
            pStatus->changeDefendPer[EDefendType_Magic] );
        SHOW_STRING( szBuffer, dwItemIntroColor );
    }

//     // 3防 (值)
//     if( pStatus->bAvail && pStatus->changeDefend[EDefendType_Short] > 0 )
//     {
//         MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eText_PlayDef_Short ),
//             ( int )pStatus->changeDefend[EDefendType_Short] );
//         SHOW_STRING( szBuffer, dwItemIntroColor );
//     }
//     else if( !pStatus->bAvail && pStatus->changeDefend[EDefendType_Short] < 0 )
//     {
//         MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s%d", theXmlString.GetString( eText_PlayDef_Short ),
//             ( int )pStatus->changeDefend[EDefendType_Short] );
//         SHOW_STRING( szBuffer, dwItemIntroColor );
//     }
// 
//     if( pStatus->bAvail && pStatus->changeDefend[EDefendType_Long] > 0 )
//     {
//         MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s+%d", theXmlString.GetString( eText_PlayDef_Long ),
//             ( int )pStatus->changeDefend[EDefendType_Long] );
//         SHOW_STRING( szBuffer, dwItemIntroColor );
//     }
//     else if( !pStatus->bAvail && pStatus->changeDefend[EDefendType_Long] < 0 )
//     {
//         MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s%d", theXmlString.GetString( eText_PlayDef_Long ),
//             ( int )pStatus->changeDefend[EDefendType_Long] );
//         SHOW_STRING( szBuffer, dwItemIntroColor );
//     }

    if( pStatus->bAvail && pStatus->changeDefend[EDefendType_Magic] > 0 )
    {
		MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s:+%d", theXmlString.GetString( eText_PlayDef_Magic ),
            ( int )pStatus->changeDefend[EDefendType_Magic] );
        SHOW_STRING( szBuffer, dwItemIntroColor );
    }
    else if( !pStatus->bAvail && pStatus->changeDefend[EDefendType_Magic] < 0 )
    {
        MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s%d", theXmlString.GetString( eText_PlayDef_Magic ),
            ( int )pStatus->changeDefend[EDefendType_Magic] );
        SHOW_STRING( szBuffer, dwItemIntroColor );
    }

	if( pStatus->bAvail && pStatus->changeDefend[EDefendType_Physical] > 0 )
	{
		MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s:+%d", theXmlString.GetString( eText_PlayDef_Short ),
			( int )pStatus->changeDefend[EDefendType_Physical] );
		SHOW_STRING( szBuffer, dwItemIntroColor );
	}
	else if( !pStatus->bAvail && pStatus->changeDefend[EDefendType_Physical] < 0 )
	{
		MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s%d", theXmlString.GetString( eText_PlayDef_Short ),
			( int )pStatus->changeDefend[EDefendType_Physical] );
		SHOW_STRING( szBuffer, dwItemIntroColor );
	}

    // 恢复 / 损失 基础魔法上限 (百分比)
    if( pStatus->bAvail && pStatus->iBalanceDelayTime > 0 && pStatus->recoverMPBasePer > 0 )
    {
        std::string strDelayTime;
        if( pStatus->iBalanceDelayTime != 1000 )
        {
            if( pStatus->iBalanceDelayTime % 1000 == 0 )
            {
                MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%d", pStatus->iBalanceDelayTime / 1000 );
            }
            else
            {
                MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%.1f", ( float )pStatus->iBalanceDelayTime / 1000.0f );
            }
            strDelayTime = szBuffer;
        }
        MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, theXmlString.GetString( eText_StatusTip_BaseMPPer ),
            strDelayTime.c_str(), GetMPTypeString( thePlayerRole.GetProfession() ), pStatus->recoverMPBasePer );
        SHOW_STRING( szBuffer, dwItemIntroColor );
    }
    else if( !pStatus->bAvail && pStatus->iBalanceDelayTime > 0 && pStatus->recoverMPBasePer < 0 )
    {
        int nMpRecover = abs( pStatus->recoverMPBasePer );
        std::string strDelayTime;
        if( pStatus->iBalanceDelayTime != 1000 )
        {
            if( pStatus->iBalanceDelayTime % 1000 == 0 )
            {
                MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%d", pStatus->iBalanceDelayTime / 1000 );
            }
            else
            {
                MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%.1f", ( float )pStatus->iBalanceDelayTime / 1000.0f );
            }
            strDelayTime = szBuffer;
        }
        MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, theXmlString.GetString( eText_Buf_BaseMPPerDecrease ),
            strDelayTime.c_str(), GetMPTypeString( thePlayerRole.GetProfession() ), nMpRecover );
        SHOW_STRING( szBuffer, dwItemIntroColor );
    }

    // 恢复 / 损失 魔法值 (值)
    if( pStatus->bAvail && pStatus->iBalanceDelayTime > 0 && pStatus->stChanged_MP > 0 )
    {
        std::string strDelayTime;
        if( pStatus->iBalanceDelayTime != 1000 )
        {
            if( pStatus->iBalanceDelayTime % 1000 == 0 )
            {
                MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%d", pStatus->iBalanceDelayTime / 1000 );
            }
            else
            {
                MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%.1f", ( float )pStatus->iBalanceDelayTime / 1000.0f );
            }
            strDelayTime = szBuffer;
        }
        MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, theXmlString.GetString( eText_Buf_RestorMP ),
            strDelayTime.c_str(), GetMPTypeString( thePlayerRole.GetProfession() ), pStatus->stChanged_MP );
        SHOW_STRING( szBuffer, dwItemIntroColor );
    }
    else if( !pStatus->bAvail && pStatus->iBalanceDelayTime > 0 && pStatus->stChanged_MP < 0 )
    {
        int nMpRecover = abs( pStatus->stChanged_MP );
        std::string strDelayTime;
        if( pStatus->iBalanceDelayTime != 1000 )
        {
            if( pStatus->iBalanceDelayTime % 1000 == 0 )
            {
                MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%d", pStatus->iBalanceDelayTime / 1000 );
            }
            else
            {
                MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%.1f", ( float )pStatus->iBalanceDelayTime / 1000.0f );
            }
            strDelayTime = szBuffer;
        }
        MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, theXmlString.GetString( eText_Buf_DecreaseMP ),
            strDelayTime.c_str(), GetMPTypeString( thePlayerRole.GetProfession() ), nMpRecover );
        SHOW_STRING( szBuffer, dwItemIntroColor );
    }

    // 隐身
    if( pStatus->bAvail && pStatus->bIsHide )
    {
        SHOW_STRING( theXmlString.GetString( eText_Buf_Invisible ), dwItemIntroColor );
    }

    // 加速 (百分比)
    if( pStatus->bAvail && pStatus->nMoveSpeedPer > 0 )
    {
		MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s:+%d%%", theXmlString.GetString( eTip_sAddMoveSpeed ), pStatus->nMoveSpeedPer );
        SHOW_STRING( szBuffer, dwItemIntroColor );
    }

    // 暴击率 (值)
    if( pStatus->bAvail && pStatus->changed_Critical > 0 )
    {
		MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s:+%d", theXmlString.GetString( eTip_sAddCritical ), pStatus->changed_Critical );
        SHOW_STRING( szBuffer, dwItemIntroColor );
    }
    else if( !pStatus->bAvail && pStatus->changed_Critical < 0 )
    {
        MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s%d", theXmlString.GetString( eTip_sAddCritical ), pStatus->changed_Critical );
        SHOW_STRING( szBuffer, dwItemIntroColor );
    }
        
    // 暴击伤害 (值)
    if( pStatus->bAvail && pStatus->changed_CriticalIntensity > 0 )
    {
		MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s:+%d", theXmlString.GetString( eTip_sAddCriticalIntensity ),
            pStatus->changed_CriticalIntensity );
        SHOW_STRING( szBuffer, dwItemIntroColor );
    }
    else if( !pStatus->bAvail && pStatus->changed_Critical < 0 )
    {
        MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1, "%s%d", theXmlString.GetString( eTip_sAddCriticalIntensity ),
            pStatus->changed_CriticalIntensity );
        SHOW_STRING( szBuffer, dwItemIntroColor );
    }

	if (pStatus->BeDamagePerHpMax > 0)
	{
		MeSprintf_s( szBuffer, sizeof( szBuffer ) / sizeof( char ) - 1,theXmlString.GetString( eText_BeDamagePerHPMax ),pStatus->BeDamagePerHpMax );
		SHOW_STRING( szBuffer, dwItemIntroColor );
	}
}

void S_IconInfoHero::RefreshColorFrameType()
{
	ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( m_stItem.itembaseinfo.ustItemID );
	if( !pItemDetail )
		return;

	m_eColorFrameType = eColorFrame_None;

	if( m_stItem.itembaseinfo.useType == SCharItem::EUT_AutoUse )
		m_eColorFrameType = eColorFrame_Active;
}

extern const char* GetRootPath();
bool S_IconInfoHero::SetData( IN void* pData,
							 const bool bShowCount /* = false */,
							 const bool bNext /* = false */, 
							 IN bool bCompareData /* = false */,
							 int nPlayerID /*= -1*/ )
{
	assert( pData );

	char szTemp[256] = {0};
	int nCurrHP = 0,
		nHPMax = 0; 
	//
	Clear();
	m_bNextLvl = bNext;
	//
	m_stItem = *(SCharItem*)pData;

	if ( m_stItem.itembaseinfo.ustItemID == InvalidLogicNumber )
	{
		return false;
	}

	if(m_stItem.IsLock())
	{
		if( m_stItem.xLockInfo.n64UnLockTime == 0 )
		{
			m_bItemLocked = 1;
		}
		else
		{
			m_bItemLocked = 2;
		}
	}

	float fPhysicAtt = 0.0f ;
	float fMagicAtt  = 0.0f;
	float fDef  = 0.0f;
	ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( m_stItem.itembaseinfo.ustItemID );
	ItemDefine::SItemCommon* pCompareItemDetail = 
		GettheItemDetail().GetItemByID( m_stCompareItem.itembaseinfo.ustItemID );

	if( !pItemDetail )
		return false;

    // 不可交易的物品左下角显示小锁         added by zhuomeng.hu		[11/9/2010]
    m_bItemCanTrade = pItemDetail->bIsCanTrade;
    if( m_bItemCanTrade )
        m_bItemCanTrade = m_bItemCanTrade && !m_stItem.IsBounded();

    // 不可使用或装备的物品蒙一层红色       added by zhuomeng.hu		[11/25/2010]
    if( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_RESTORE )
    {
        // 消耗品
        ItemDefine::SItemRestore* pItemRestore = ( ItemDefine::SItemRestore* )pItemDetail;
        if( pItemRestore->stUseLevel > thePlayerRole.GetLevel() )
            m_bItemCanBeUsed = false;
    }
    else if( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_OTHER )
    {
        // 马
        ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( pItemDetail->ustItemID );
        if( pDrome )
        {
            if( pDrome->takeLevel > thePlayerRole.GetLevel() )
                m_bItemCanBeUsed = false;
        }
    }
    else if( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_WEAPON || pItemDetail->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
    {
        // 装备
        ItemDefine::SItemCanEquip* pEquip = ( ItemDefine::SItemCanEquip* )pItemDetail;
            
        if( pEquip->stEquipLevelReq > thePlayerRole.GetLevel() )
        {
            // 等级不符
            m_bItemCanBeUsed = false;
        }
        else if( pEquip->cEquipSexReq != -1 && pEquip->cEquipSexReq != thePlayerRole.GetSex() )
        {
            // 性别不符
            m_bItemCanBeUsed = false;
        }
        else if( !pEquip->arrayEquipArmsReq[ thePlayerRole.GetProfession() ] )
        {
            // 职业不符
            m_bItemCanBeUsed = false;
        }
    }

	// set item level
	m_nItemLevel = pItemDetail->ustLevel;

	bool bShowCountTemp = bShowCount;
	if (pItemDetail->ucItemType == ItemDefine::ITEMTYPE_SKILL)
		bShowCountTemp = false;
	else
	{
		bShowCountTemp = true;
	}	
	if( m_stItem.itembaseinfo.useType == SCharItem::EUT_AutoUse )
		m_eColorFrameType = eColorFrame_Active;

	m_bShowCount = bShowCountTemp;

	char filename[MAX_PATH] = {0};
	char fullpath[MAX_PATH] = {0};

	const IconManager::IconInfo* iconInfo = IconManager::Get().GetIconInfo(m_stItem.itembaseinfo.ustItemID);
	if (iconInfo)
		SetIconImageInfo(iconInfo->image, iconInfo->iconSize, iconInfo->row, iconInfo->column);

	if (m_strIconBigImageFilename.empty())
		strcpy(filename, pItemDetail->GetIconInItemBag());
	else
		strcpy(filename, m_strIconBigImageFilename.c_str());
	if( filename[0] != '0' )
	{
		if( filename[1] == ':' )
		{
			strcpy(fullpath, filename);
		}
		else
		{

			char lwrpath[MAX_PATH] = {0};
			strcpy(lwrpath, filename);
			strlwr(lwrpath);
			if( (strstr(lwrpath, "ui\\") && !strstr(lwrpath, "data\\ui" ))
				|| (strstr(lwrpath, "ui/") && !strstr(lwrpath, "ui//") && !strstr(lwrpath, "data/ui" ))
				|| (strstr(lwrpath, "ui//") && !strstr(lwrpath, "data//ui" )))
				sprintf_s( fullpath,sizeof(fullpath)/sizeof(char) - 1, "%s\\data\\%s", GetRootPath(), filename );
			else
				sprintf_s( fullpath,sizeof(fullpath)/sizeof(char) - 1, "%s\\%s", GetRootPath(), filename );
		}
		m_strIconFileName = fullpath;
	}
	else
		m_strIconFileName = filename;

	CFilePath path;
	path.Split( m_strIconFileName.c_str() );
	char szDisableFile[MAX_PATH] = {0};
	sprintf_s( szDisableFile,sizeof(szDisableFile)/sizeof(char) - 1 ,"%s%s%s_disable%s", 
		path.GetDrive(), path.GetDirectory(), path.GetFileName(), path.GetExt() );

	m_strDisableIconFileName = szDisableFile;

	char szShopFile[MAX_PATH] = {0};
	sprintf_s( szShopFile,sizeof(szShopFile)/sizeof(char) - 1, "%s%s%s_shop%s", 
		path.GetDrive(), path.GetDirectory(), path.GetFileName(), path.GetExt() );
	m_strShopIconFileName = szShopFile;


	strcpy(filename, pItemDetail->GetIconSoundFile());
	if( filename[0] != '0' )
	{
		if( filename[1] == ':' )
		{
			strcpy(fullpath, filename);
		}
		else
		{

			char lwrpath[MAX_PATH] = {0};
			strcpy(lwrpath, filename);
			strlwr(lwrpath);
			if( (strstr(lwrpath, "ui\\") && !strstr(lwrpath, "data\\ui" ))
				|| (strstr(lwrpath, "ui/") && !strstr(lwrpath, "ui//") && !strstr(lwrpath, "data/ui" ))
				|| (strstr(lwrpath, "ui//") && !strstr(lwrpath, "data//ui" )))
				sprintf_s( fullpath,sizeof(fullpath)/sizeof(char) - 1, "%s\\data\\%s", GetRootPath(), filename );
			else
				sprintf_s( fullpath,sizeof(fullpath)/sizeof(char) - 1, "%s\\%s", GetRootPath(), filename );
		}
		m_strSoundName = fullpath;
	}
	else
		m_strSoundName = filename;

	if( pItemDetail->costType == ItemDefine::CT_Money || pItemDetail->costType == ItemDefine::CT_JiaoZi )
		m_nCost = pItemDetail->dwCost*fSellDiscountRate + 1;
	/*else
		m_nCost = pItemDetail->dwSpecialCost*fSellDiscountRate + 1;*/
	
	m_bLocked = m_stItem.storageinfo.bIsLocked;
	m_bNextLvl = bNext;
	if ( !pItemDetail->IsExclusive() || bShowCount == true )
	{
		m_nCount = m_stItem.itembaseinfo.ustItemCount;
	}

	//
	if (pItemDetail)
	{
		if ( pItemDetail->IsExclusive() )
		{
			if (pItemDetail->ucItemType == ItemDefine::ITEMTYPE_WEAPON||
				pItemDetail->ucItemType == ItemDefine::ITEMTYPE_ARMOUR)
			{

			}
			else
			{
				if (pItemDetail->ucItemType == ItemDefine::ITEMTYPE_MATERIAL)
				{
					ItemDefine::SCreateMaterial* pMaterial = NULL;
					pMaterial = (ItemDefine::SCreateMaterial*)pItemDetail;
					switch(pMaterial->stMaterialType)
					{
					case ItemDefine::ematerial_metal:
					case ItemDefine::ematerial_pelage:
					case ItemDefine::ematerial_wood:
						{
							m_nCount = m_stItem.itembaseinfo.ustItemCount;
						}
						break;
					default:
						break;
					}

				}
			}
		}
	}

	// Name
	//根据装备的特殊属性 加入名字后缀
	int nType = InvalidLogicNumber ;
	if (pItemDetail)
	{
		nType = pItemDetail->ucItemType;
	}
	if( m_stItem.itembaseinfo.ustItemID != CompoundItemID && bCompareData )
	{
		m_stInfo[m_ucIconInfoLine].m_dwTextAlign = DT_CENTER;
		SHOW_STRING( theXmlString.GetString(eText_PartitionLine), Color_Config.getColor( CC_ItemTip_NowEquip ) );
	}

	if (nType == ItemDefine::ITEMTYPE_ARMOUR || nType == ItemDefine::ITEMTYPE_WEAPON || nType == ItemDefine::ITEMTYPE_RESTORE)
	{
		if( pItemDetail->costType == ItemDefine::CT_Money || pItemDetail->costType == ItemDefine::CT_JiaoZi )
			SetFlag(eTipFlag_ShowMoney);
	}

	if( m_eFlag == eTipFlag_Event )
	{
		int nLength = 0;
		std::string szItemDesc = pItemDetail->GetItemDesc();
		const DWORD dwDescColor = Color_Config.getColor( CC_ItemTip_EventItem_Des );
		char szTemp[256];
		memset(szTemp, 0, sizeof(szTemp));
		for ( UINT n=0; n<szItemDesc.size(); n++ )
		{
			if ( szItemDesc[n] != 0 &&
				szItemDesc[n] == '\\' && szItemDesc[n+1] == 'n' )
			{
				m_stInfo[m_ucIconInfoLine].m_strInfo = szTemp;
				m_stInfo[m_ucIconInfoLine].m_col = dwDescColor;
				memset( szTemp, 0, sizeof(szTemp) );
				nLength = 0;
				m_ucIconInfoLine++;
				n++;
			}
			else if ( n < szItemDesc.size()-10 &&
				szItemDesc[n] == '<' && szItemDesc[n+1] == '#' )
			{
				char szColor[10];
				memset( szColor, 0, sizeof(szColor) );
				memcpy( szColor, &szItemDesc[n+2], 8 );
				sscanf( szColor, "%x", &dwDescColor );
				n += 10;
			}
			else
			{
				szTemp[nLength++] = szItemDesc[n];
				if ( n == szItemDesc.size() - 1 && strlen(szTemp) > 0 )
				{
					m_stInfo[m_ucIconInfoLine].m_strInfo = szTemp;
					m_stInfo[m_ucIconInfoLine].m_col = dwDescColor;
					m_ucIconInfoLine++;
				}
			}
			assert( m_ucIconInfoLine < MAX_ICON_INFO_EX_LINE_COUNT );
		}
	}
	else
	{
		ShowBaseInfo( pItemDetail, nType );
		ShowEquipCommon( pItemDetail, nType );                      // 装备
		ShowWeapon( pItemDetail,nType );                            // 武器特有
		ShowArmour( pItemDetail,nType );                            // 防具特有
        ShowEquipRand( pItemDetail, nType );                        // 随机属性
        //ShowArmourSkill( pItemDetail,nType, NULL, nPlayerID );    // 套装技能，暂时无用
        ShowEquipGemInlay( pItemDetail, nType );                    // 打孔和镶嵌
        ShowEquipSuit( pItemDetail,nType, nPlayerID );              // 套装属性
		ShowEquipScore( pItemDetail, nType );						// 装备平分
		ShowEquipDescribe( pItemDetail,nType );                     // 描述和售价
        
        ShowGem( pItemDetail,nType );
		ShowMaterial(pItemDetail,nType);
		ShowSkill( pItemDetail,nType );	
		ShowRestore( pItemDetail, nType );
		ShowOthers( pItemDetail, nType );
		ShowPetEquip(m_stItem, pItemDetail, nType );
		ShowSuit(pItemDetail,nType, nPlayerID);//套装属性

		// 显示剩余时间，放在最后显示
		if( m_stItem.itembaseinfo.n64UseTime > 0 )
		{
			// get item last time
			if(!m_stItem.IsOverdue(true))
			{
				TimeSpan timeDelta( m_stItem.itembaseinfo.nLeftTime );
				const DWORD dwLeftTimeColor = Color_Config.getColor( CC_ItemTip_Item_LeftTime );
				char acTimeDay[256] = {0};
				if( timeDelta.GetDays() != 0 )	//剩余时间:几天
				{
					sprintf_s( acTimeDay, 256, "%s%d", theXmlString.GetString( eText_Title_LeftTime ), timeDelta.GetDays());
					strcat_s(acTimeDay, 256, theXmlString.GetString(eText_Day));
					SHOW_STRING( acTimeDay, dwLeftTimeColor );
				}
				else if( timeDelta.GetHours() != 0 )	// 剩余时间:几小时几分钟
				{
					if( timeDelta.GetMinutes() )
						sprintf_s( acTimeDay, 256, "%s%d%s%d%s", theXmlString.GetString( eText_Title_LeftTime ), timeDelta.GetHours(), theXmlString.GetString(eText_Hour),
						timeDelta.GetMinutes(), theXmlString.GetString(eText_Title_Minute) );
					else
						sprintf_s( acTimeDay, 256, "%s%d%s", theXmlString.GetString( eText_Title_LeftTime ), timeDelta.GetHours(), theXmlString.GetString(eText_Hour) );
					SHOW_STRING( acTimeDay, dwLeftTimeColor );
				}
				else if( timeDelta.GetMinutes() != 0 )
				{
					sprintf_s( acTimeDay, 256, "%s%d%s", theXmlString.GetString( eText_Title_LeftTime ), timeDelta.GetMinutes(), theXmlString.GetString(eText_Title_Minute) );
					SHOW_STRING( acTimeDay, dwLeftTimeColor );
				}
				else if(timeDelta.GetSeconds() != 0)
				{
					printf_s( acTimeDay, 256, "%s%d%s", theXmlString.GetString( eText_Title_LeftTime ), timeDelta.GetSeconds(), theXmlString.GetString(eText_Title_Sec) );
					SHOW_STRING( acTimeDay, dwLeftTimeColor );
				}
				else
				{
					SHOW_STRING( theXmlString.GetString( eText_TimeOut ), dwLeftTimeColor );
				}
			}
			else
			{
				const DWORD dwLeftTimeColor = Color_Config.getColor( CC_ItemTip_Item_LeftTime );
				SHOW_STRING( theXmlString.GetString( eText_TimeOut ), dwLeftTimeColor );
			}
		}
	}


	switch( nType ) 
	{
	case ItemDefine::ITEMTYPE_CREATEITEMRULE:
		{
		}
		break;
	case ItemDefine::ITEMTYPE_MATERIAL:
		{
			ItemDefine::SCreateMaterial *pMaterial = (ItemDefine::SCreateMaterial *)GettheItemDetail().GetItemByID(m_stItem.itembaseinfo.ustItemID);
			if (pMaterial->stMaterialType == ItemDefine::ematerial_metal||
				pMaterial->stMaterialType == ItemDefine::ematerial_pelage||
				pMaterial->stMaterialType == ItemDefine::ematerial_wood)
			{
			}
		}
	}

	m_usByteMaxWidthCount = 0;
	for ( int n=0; n<m_ucIconInfoLine; n++ )
	{
		int nSize = m_stInfo[n].m_strInfo.size();
		if( m_stInfo[n].m_bIconRightText )
        {
			nSize += TIP_ICON_SIZE / m_nFontSize * 2;
            // 灵魂铭刻另外加长度
            if( m_stItem.IsSoulStamp() )
            {
                nSize += ( TIP_ICON_SOUL_SIZE + OFFSET_WIDTH * 2 ) * 2 / m_nFontSize;
            }
        }
		m_usByteMaxWidthCount = max( nSize, m_usByteMaxWidthCount );		
	}

	m_usWidth = m_nFontSize/2*max(m_usByteMaxWidthCount,m_usByteOtherInfoMaxWidthCount) + OFFSET_HEIGHT*2 + FRAME_SIZE*2;
	m_usHeight = (m_nFontSize+OFFSET_HEIGHT)*(m_ucIconInfoLine+m_ucIconOtherInfoLine) + OFFSET_HEIGHT + FRAME_SIZE*2;

	return true;
}

std::string& S_IconInfoHero::IconFileName()
{
	return m_strIconFileName;
}

std::string& S_IconInfoHero::DisableIconFileName()
{
	return m_strDisableIconFileName;
}

std::string& S_IconInfoHero::ShopIconFileName()
{
	return m_strShopIconFileName;
}


bool S_IconInfoHero::PlaySound()
{
	if ( m_strSoundName.size() > 0 )
	{
		return theUiManager.PlaySound( m_strSoundName );
	}
	return false;
}



bool S_IconInfoHero::operator==( IN S_IconInfoBase& stIconInfoBase )
{
	S_IconInfoHero* pIconInfoHero = (S_IconInfoHero*)&stIconInfoBase;
	return m_stItem == pIconInfoHero->m_stItem;
}

unsigned short S_IconInfoHero::GetEquipRandomEvaluate(unsigned short usItemID, unsigned short usEvalType, const std::vector<unsigned short>& vectorRandID)
{
	unsigned short usEvalRet = InvalidLogicNumber;    // 默认返回值为普通

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( usItemID );
	if( !pItemCommon )
		return usEvalRet;

	// 装备类型，防具/武器
	unsigned short usEquipType = 0;
	if ( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
		usEquipType = CRandPropertyEvaluate::PropEvalEquipment_Aumour;
	else if( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_WEAPON )
		usEquipType = CRandPropertyEvaluate::PropEvalEquipment_Weapon;
	else
		return usEvalRet;

	// 随机等级
	ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*)pItemCommon;
	const CRandPropertyEvaluate::SEquipmentEval* pEquipmentEval = theRandPropEvaluate.GetEquipmentEval(usEvalType, usEquipType, pItemCanEquip->stEquipLevelReq);
	if( !pEquipmentEval || (pEquipmentEval && pEquipmentEval->usRandLevel < 0) )
		return usEvalRet;

	int nRandCount = vectorRandID.size();
	if( nRandCount <= 0 )
		return usEvalRet;

	float fEvalValueSum = 0.f;
	for( int i=0; i<nRandCount; ++i )
	{
		ItemDefine::SRandAttribute* pRandAttr = GettheItemDetail().GetRandByID(vectorRandID[i]);
		if( !pRandAttr )
			return usEvalRet;

		float fMaxEvalValue = GettheItemDetail().GetMaxValueByRandLevelType(pEquipmentEval->usRandLevel, pRandAttr->type[0]);
		if( fMaxEvalValue <= 0 )
			return usEvalRet;

		float fRandValue = 0.f;
		fRandValue = GetRandValueByType( pRandAttr, 0 );
		float fEvalValue = fRandValue / fMaxEvalValue;
		fEvalValueSum += fEvalValue; 
	}
	// 鉴定，并且随机属性个数不满3个，则用最低评估值进行补足
	if( usEvalType == CRandPropertyEvaluate::PropertyEvaluate_Identify && nRandCount < 3 )
	{
		fEvalValueSum += ( 3 - nRandCount ) * pEquipmentEval->fEvalNormal;
		nRandCount = 3;
	}

	fEvalValueSum /= nRandCount;
	if( fEvalValueSum <= pEquipmentEval->fEvalNormal )
		usEvalRet = eIL_Normal;
	else if( fEvalValueSum <= pEquipmentEval->fEvalLiangPin )
		usEvalRet = eIL_Choiceness;
	else if( fEvalValueSum <= pEquipmentEval->fEvalJingPin )
		usEvalRet = eIL_Polish;
	else if( fEvalValueSum <= pEquipmentEval->fEvalJiPin )
		usEvalRet = eIL_Nonsuch;
	else if( fEvalValueSum <= pEquipmentEval->fEvalShenPin )
		usEvalRet = eIL_Holiness;

	return usEvalRet;
}
unsigned short S_IconInfoHero::GetEquipRandomEvaluate( void* pItemDetail, INT nType, unsigned short usEvalType, const SCharItem& stItem )
{
	if( nType != ItemDefine::ITEMTYPE_ARMOUR  && nType != ItemDefine::ITEMTYPE_WEAPON )
		return InvalidLogicNumber;	
	ItemDefine::SItemCanEquip* pArmour = NULL;
	if ( !pItemDetail )
		return InvalidLogicNumber;

	std::vector<unsigned short> vRandArr;
	pArmour = (ItemDefine::SItemCanEquip*)pItemDetail;

    // 附加随机属性
	for( int nloop = 0; nloop < SCharItem::EConstDefine_BaseRandMaxCount; ++nloop )
	{		
		unsigned short usRand = stItem.equipdata.baseRands[nloop];
// 		if( nloop >= pArmour->additiveRandCount )//&& ( nloop != ( SCharItem::e_AddRandIndex ) ) )//随机个数以内
// 			continue;

		//if( usEvalType == CRandPropertyEvaluate::PropertyEvaluate_OpenLight && nloop != SCharItem::e_AddRandIndex )//开光
		//	continue;
		//if( usEvalType == CRandPropertyEvaluate::PropertyEvaluate_Identify && nloop == SCharItem::e_AddRandIndex )
		//	continue;

		//if( usRand == InvalidLogicNumber )      // 没有的话直接返回，开光不做特殊判断，因为没有鉴定就没有开光
		//{			
		//	// 品质介于2-5，现在套装也显示
		//	if( pArmour->ustLevel >= 2 && pArmour->ustLevel <= 5 )
		//	{
		//		return InvalidLogicNumber;
		//	}
		//}
		//vRandArr.push_back( usRand );
        if( usRand != InvalidLogicNumber )
            vRandArr.push_back( usRand );
	}

    // 鎏金
    for( int nloop = 0; nloop < SCharItem::EConstDefine_PurpleRandMaxCount; ++nloop )
    {		
        unsigned short usRand = stItem.equipdata.purpleRands[nloop];
//         if( nloop >= pArmour->additiveRandCount )                   //随机个数以内
//             continue;

        if( usRand != InvalidLogicNumber )
            vRandArr.push_back( usRand );
    }

	if( vRandArr.size() == 0 )
		return InvalidLogicNumber;

	// 获得评估值
	unsigned short eval = GetEquipRandomEvaluate( pArmour->ustItemID, usEvalType, vRandArr );
	if( eval != InvalidLogicNumber )
		--eval;
	return eval;	

}

void S_IconInfoHero::Clone( S_IconInfoBase* pkInfo )
{
	S_IconInfoHero* pkHeroInfo = dynamic_cast<S_IconInfoHero*>( pkInfo );
	if( !pkHeroInfo )
		return;

	S_IconInfoBase::Clone( pkInfo );

	for( int i = 0 ; i < MAX_ICON_INFO_EX_LINE_COUNT ; ++ i )
	{
		m_stInfo[i] = pkHeroInfo->m_stInfo[i];
	}
	for( int i = 0 ; i < MAX_ICON_OTHER_INFO_EX_LINE_COUNT ; ++ i )
	{
		m_stOtherInfo[i] = pkHeroInfo->m_stOtherInfo[i];
	}
	m_stItem = pkHeroInfo->m_stItem;
	m_stCompareItem = pkHeroInfo->m_stCompareItem;	
	m_nCount = pkHeroInfo->m_nCount;
	m_bLocked = pkHeroInfo->m_bLocked;
	m_bItemLocked = pkHeroInfo->m_bItemLocked;
    m_bItemCanTrade = pkHeroInfo->m_bItemCanTrade;
    m_bEnableUsableEff = pkHeroInfo->m_bEnableUsableEff;
    m_bItemCanBeUsed = pkHeroInfo->m_bItemCanBeUsed;
	m_nMaxCount = pkHeroInfo->m_nMaxCount;
	m_strIconFileName = pkHeroInfo->m_strIconFileName;
	m_strDisableIconFileName = pkHeroInfo->m_strDisableIconFileName;
	m_strShopIconFileName = pkHeroInfo->m_strShopIconFileName;
	m_strSoundName = pkHeroInfo->m_strSoundName;
	m_nCost = pkHeroInfo->m_nCost;	
	m_dwSpareStartTime = pkHeroInfo->m_dwSpareStartTime;
	m_dwSpareTime = pkHeroInfo->m_dwSpareTime;
	m_bNextLvl = pkHeroInfo->m_bNextLvl;
	m_eFlag = pkHeroInfo->m_eFlag;
}

void S_IconInfoHero::DisplayIcon( IN RECT* prcDst, COLORREF col,
							 int nFontIndex, int nFontSize,
							 COLORREF colFont, eIconDrawState eEnable,ControlFrame* pFatherFrame
							 )
{
	S_IconInfoBase::DisplayIcon( prcDst, col,
							 nFontIndex, nFontSize,
							 colFont, eEnable,pFatherFrame);

    //防盗加锁 显示锁图标
 	if( IsItemLocked() != 0 || !m_bItemCanTrade )
 	{
 		RECT rcDest = *prcDst;
		RECT rcSrc;
 		int width,height;
 
 		width = rcDest.right - rcDest.left;
 		height = rcDest.bottom - rcDest.top;
 
		if( width != 42 && height != 42 )
		{
 			width /= 3;
 			height /= 3;
		}
		else
		{
 			width = 16;
 			height = 16;
		}

 		rcDest.right = rcDest.left+width;
 		rcDest.bottom = rcDest.top+height;
 
 		rcSrc.left = 0;
 		rcSrc.top = 0;
 		rcSrc.right = 16;
 		rcSrc.bottom = 16;
 
 		char filename[MAX_PATH] = {0};
 		char fullpath[MAX_PATH] = {0};
		if( IsItemLocked() == 1 )
		{
 			sprintf_s( filename,sizeof(filename)/sizeof(char) - 1, "%s", SHOW_LOCK_PATH );

 			sprintf_s( fullpath,sizeof(fullpath)/sizeof(char) - 1 ,"%s\\%s", GetRootPath(), filename );
	 
 			theControlPictureManager.BitBlt( &m_nIconLockId,
 				fullpath,
 				&rcDest, &rcSrc, D3DCOLOR_XRGB(255,255,255) );
		}
		else if( IsItemLocked() == 2 )
		{
			sprintf_s( filename,sizeof(filename)/sizeof(char) - 1, "%s", SHOW_UNLOCK_PATH );

 			sprintf_s( fullpath,sizeof(fullpath)/sizeof(char) - 1, "%s\\%s", GetRootPath(), filename );
	 
 			theControlPictureManager.BitBlt( &m_nIconUnLockId,
 				fullpath,
 				&rcDest, &rcSrc, D3DCOLOR_XRGB(255,255,255) );
		}
        //else if( IsItemLocked() == 0 && !m_bItemCanTrade )
		if( !m_bItemCanTrade )
        {
            // 非加锁状态的不可交易物品左下角显示小锁 (郑亮需求)       added by zhuomeng.hu		[11/9/2010]
            rcDest = *prcDst;
            rcDest.right = rcDest.left + width / 2;
            rcDest.top = rcDest.bottom - height / 2;

            MeSprintf_s( filename, sizeof( filename ) / sizeof( char ) - 1, "%s", SHOW_LOCK_PATH );
            MeSprintf_s( fullpath, sizeof( fullpath ) / sizeof( char ) - 1 ,"%s\\%s", GetRootPath(), filename );
            theControlPictureManager.BitBlt( &m_nIconLockId, fullpath, &rcDest, &rcSrc, D3DCOLOR_XRGB( 255, 255, 255 ) );
        }
 	}

    // 不可用物品显示红色           added by zhuomeng.hu		[11/25/2010]
    if( m_bEnableUsableEff && !m_bItemCanBeUsed )
    {
        RECT rcDest = *prcDst;
        RECT rcSrc;
        rcSrc.left = 0;
        rcSrc.top = 0;
        rcSrc.right = 64;
        rcSrc.bottom = 64;
        char filename[MAX_PATH] = {0};
        char fullpath[MAX_PATH] = {0};
        MeSprintf_s( filename, sizeof( filename ) / sizeof( char ) - 1, "%s", SHOW_CANTUSE_PATH );
        MeSprintf_s( fullpath, sizeof( fullpath ) / sizeof( char ) - 1 ,"%s\\%s", GetRootPath(), filename );
        int nId( -1 );
        theControlPictureManager.BitBlt( &nId, fullpath, &rcDest, &rcSrc, D3DCOLOR_XRGB( 255, 255, 255 ) );
    }
}

void  S_IconInfoHero::ReplaceSpecifiedName( unsigned short ustLevel, Common::_tstring& tstrName )
{
	switch( ustLevel )
	{
	case 2: // green
		if( tstrName.Find( theXmlString.GetString( ePreItemText_LiangPin ) ) < 2 )
			tstrName.Replace( theXmlString.GetString( ePreItemText_LiangPin ), "" );
		break;
	case 3: // blue
		if( tstrName.Find( theXmlString.GetString( ePreItemText_JingPin ) ) < 2 )
			tstrName.Replace( theXmlString.GetString( ePreItemText_JingPin ), "" );
		break;
	case 4: // purple
		if( tstrName.Find( theXmlString.GetString( ePreItemText_JiPin ) ) < 2 )
			tstrName.Replace( theXmlString.GetString( ePreItemText_JiPin ), "" );
		break;
	case 5: // yellow
		if( tstrName.Find( theXmlString.GetString( ePreItemText_ShenPin ) ) < 2 )
			tstrName.Replace( theXmlString.GetString( ePreItemText_ShenPin ), "" );
		break;
	}
}

DWORD S_IconInfoHero::GetQualityColor( int nItemLevel )
{
	DWORD dwNameColor = 0;
	//品质
	switch( nItemLevel ) 
	{
    case ItemDefine::EQL_White:
		dwNameColor = Color_Config.getColor( CC_ItemTip_Name_Quality0 );
		break;
	case ItemDefine::EQL_Green:
		dwNameColor = Color_Config.getColor( CC_ItemTip_Name_Quality1 );
		break;
	case ItemDefine::EQL_DeepGreen:
		dwNameColor = Color_Config.getColor( CC_ItemTip_Name_Quality2 );
		break;
	case ItemDefine::EQL_Blue:
		dwNameColor = Color_Config.getColor( CC_ItemTip_Name_Quality3 );
		break;
	case ItemDefine::EQL_Purple:
		dwNameColor = Color_Config.getColor( CC_ItemTip_Name_Quality4 );
		break;
	case ItemDefine::EQL_Orange:
		dwNameColor = Color_Config.getColor( CC_ItemTip_Name_Quality5 );
		break;
	case ItemDefine::EQL_Golden:
		dwNameColor = Color_Config.getColor( CC_ItemTip_Name_Quality6 );
		break;
	case ItemDefine::EQL_Red:
		dwNameColor = Color_Config.getColor( CC_ItemTip_Name_Quality7 );
		break;
	default:
		dwNameColor = Color_Config.getColor( CC_ItemTip_Name_Quality0 );
		break;
	}
	return dwNameColor;
}
DWORD S_IconInfoHero::GetPetShowColor(SPetItem *m_petItem)
{
	//默认可选择的暗灰色
	DWORD dwNameColor = Color_Config.getColor(CC_PetColor_Green);
	if (m_petItem != NULL)
	{
		if (m_petItem->baseInfo.isActive)
		{
			dwNameColor = Color_Config.getColor(CC_PetColor_Red);
		}
		else
		{
			ItemDefine::SPetMonster* m_petMonster = GettheItemDetail().GetPetById(m_petItem->baseInfo.petId);
			if ((m_petMonster != NULL && ! m_petMonster->bIsBaby ) || m_petItem->baseInfo.savvy>= MaxSavvy) 
			{
				dwNameColor = Color_Config.getColor(CC_PetColor_Taupe);
			}
			else 
			{
				dwNameColor = Color_Config.getColor(CC_PetColor_White);
			}
		}
	}
	return dwNameColor;
}
const char* S_IconInfoHero::GetItemName( unsigned char* data )
{
	static const char* name = "";
	if( data == NULL  )
		return name;
	SCharItem stItem;
	memcpy_s( &stItem, sizeof( stItem ), data, sizeof( stItem ) );
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );
	if( pItemCommon == NULL )
		return name;
	return pItemCommon->GetItemName();
}
int S_IconInfoHero::GetItemLevel( unsigned char* data )
{
	if( data == NULL )
		return -1;
	SCharItem stItem;
	memcpy_s( &stItem, sizeof( stItem ), data, sizeof( stItem ) );
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );
	if( pItemCommon == NULL )
		return -1;
	return pItemCommon->ustLevel;
}
void S_IconInfoHero::GlobalParseText( ControlList::S_List::STextData& kTextData, 
									 const std::wstring& wstrOutText, 
									 EKeyType eType, 
									 int& nLineHeight,
									 ControlList::S_List* pkThis )
{
	switch( eType ) 
	{
	case eKeyNormal:
		break;
	case eKeyItem:
		{
			if( pkThis->_hyberItemInfoRaw )
			{
				SCharItem stItem;
				memcpy_s( &stItem, sizeof( stItem ), pkThis->_hyberItemInfoRaw, sizeof( stItem ) );
				ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );
				if( pItemCommon )
				{
					// 这里做文字替换,极品，良品，......
					Common::_tstring tstrName( pItemCommon->GetItemName() );					
					ReplaceSpecifiedName( pItemCommon->ustLevel, tstrName );
					kTextData.str = wstrOutText;
					Common::_tstring itemName = _tstring::toNarrowString(wstrOutText.substr(1, wstrOutText.length() - 2).c_str());
					// 同样替换名字
					ReplaceSpecifiedName( pItemCommon->ustLevel, itemName );
					if( tstrName == itemName )
						kTextData.col = GetQualityColor( pItemCommon->ustLevel );			

				}
			}			
		}
		break;
	case eKeyImg:
		{
			const int nLen = 64;
			char szChar[nLen];
			WideCharToMultiByte( CP_ACP, 0, wstrOutText.c_str(), -1,
				szChar, nLen-1, NULL, NULL );
			szChar[nLen-1] = 0;
			ExpressionManager::ExpressionData* pInfo = ExpressionManager::GetInstance().GetExpressionInfo(szChar);
			if (pInfo)
			{
				kTextData.pInfo = (void*)pInfo;
				kTextData.nTextureID = pInfo->GetTextureId();
				{
					kTextData.rc.right = pInfo->m_nWidth *  ControlObject::GetSCALE(0);
					kTextData.rc.left = 0;
					kTextData.rc.bottom = pInfo->m_nHeight *  ControlObject::GetSCALE(0);
					if (kTextData.rc.bottom > nLineHeight)
					{
						nLineHeight = kTextData.rc.bottom;
					}
					kTextData.rc.top = 0;
				}
			}
		}
		break;
	case eKeyAddress:
		kTextData.col = ControlList::s_PathFindLinker_COLOR;
		break;
	case eKeyNpc:
		if (pkThis->m_bUseHyberColor)
		{
			kTextData.col = pkThis->m_colHyberOther;
		}
		break;
	case eKeyPlayer:
		kTextData.col = ControlList::s_CHAT_PLAYERNAME_COLOR;
		break;
	default:
		break;
	}
}

void S_IconInfoHero::GlobalParseText_HighShout( ControlList::S_List::STextData& kTextData,
											   const std::wstring& wstrOutText,
											   EKeyType eType, 
											   int& nLineHeight,
											   ControlList::S_List* pkThis )
{
	if( eType != eKeyPlayer )
		GlobalParseText( kTextData, wstrOutText, eType, nLineHeight, pkThis );
	else
	{
		// 判断是否至尊卡VIP用户
		kTextData.col = ControlList::s_CHAT_PLAYERNAME_COLOR;
		if( wstrOutText.length() > 0 )
		{
			Common::_tstring strPlayerName = Common::_tstring::toNarrowString(wstrOutText.c_str());
			if( theHeroGame.GetPlayerMgr() && theHeroGame.GetPlayerMgr()->IsVipPlayer(strPlayerName.c_str()) )
			{
				char szVIPName[256];
				sprintf_s(szVIPName, 256, "%s(VIP)", strPlayerName.c_str());
				kTextData.str = Common::_tstring::toWideString(szVIPName);
				kTextData.col = Color_Config.getColor(CC_CHAT_VIP_PLAYERNAME);
			}
		}
	}
}

int S_IconInfoHero::GetRandValueByType( ItemDefine::SRandAttribute* pArmourRand, int i )
{
    switch ( pArmourRand->type[i] )
    {
    case RT_None:
        return 0;
        break;
    case RT_AddStrength:
    case RT_AddAgility:
    case RT_AddConstitution:
    case RT_AddIntelligence:
	case RT_AddPhysicsAttack:
    case RT_AddMagicAttack:
	case RT_AddPhysicsDefend:
    case RT_AddMagicDefend:
    case RT_AddHPMax:
    case RT_AddAPMax_UnUse:
    case RT_AddBPMax_UnUse:
    case RT_AddFPMax_UnUse:
    case RT_AddEPMax_UnUse:
    case RT_AddMPMax:
    case RT_AddExact:
    case RT_AddDodge:
    case RT_AddCritical:
    case RT_AddTenacity:
    case RT_AddCriticalIntensity:
    case RT_AddBaseAttr:
    case RT_AddExpPer:
    case RT_AddEnergyMax:
    case RT_AddHPRestore:
    case RT_AddAPRestore_UnUse:
    case RT_AddBPRestore_UnUse:
    case RT_AddFPRestore_UnUse:
    case RT_AddEPRestore_UnUse:
	case RT_AddMPRestore:
	case RT_AddDaoxing:   //道行
	case RT_AddBreakStrike:   //破甲伤害
	case RT_AddStabStrike:   //贯穿伤害
	case RT_AddElementStrike:   //元素伤害
	case RT_AddToxinStrike:   //毒素伤害
	case RT_AddSpiritStrike:   //精神伤害
	case RT_AddBreakResist:   //破甲抗性
	case RT_AddStabResist:   //贯穿抗性
	case RT_AddElementResist:   //元素抗性
	case RT_AddToxinResist:   //毒素抗性
	case RT_AddSpiritResist:   //精神抗性
		return pArmourRand->value[i].fValue;
		break;
    case RT_AddMoveSpeed:
        return pArmourRand->value[i].fValue * 100.0f;
        break;
    default:
        return 0;
        break;
    }
}

std::string S_IconInfoHero::GetBaseAttrStringByType( int iType )
{
    std::string strBase;
    switch( iType )
    {
    case EBaseAttr_Strength:
        strBase = theXmlString.GetString( eTip_sAddStrength );
        break;
    case EBaseAttr_Agility:
        strBase = theXmlString.GetString( eTip_sAddAgility );
        break;
    case EBaseAttr_Stamina:
        strBase = theXmlString.GetString( eTip_sAddConstitution );
        break;
    case EBaseAttr_Intelligence:
        strBase = theXmlString.GetString( eTip_sAddIntelligence );
        break;
    default:
        break;
    }
    return strBase;
}

std::string S_IconInfoHero::GetRandStringByType( int iType )
{
    std::string strRand;
    switch( iType )
    {
    case RT_AddStrength:
        strRand = theXmlString.GetString( eTip_sAddStrength );
        break;
    case RT_AddAgility:
        strRand = theXmlString.GetString( eTip_sAddAgility );
        break;
    case RT_AddConstitution:
        strRand = theXmlString.GetString( eTip_sAddConstitution );
        break;
    case RT_AddIntelligence:
        strRand = theXmlString.GetString( eTip_sAddIntelligence );
        break;
	case RT_AddPhysicsAttack:
        strRand = theXmlString.GetString( eTip_sAddShortAttack );
        break;
    case RT_AddMagicAttack:
        strRand = theXmlString.GetString( eTip_sAddMagicAttack );
        break;
	case RT_AddPhysicsDefend:
        strRand = theXmlString.GetString( eTip_sAddShortDefend );
        break;
    case RT_AddMagicDefend:
        strRand = theXmlString.GetString( eTip_sAddMagicDefend );
        break;
    case RT_AddExact:
        strRand = theXmlString.GetString( eTip_sAddExact );
        break;
    case RT_AddDodge:
        strRand = theXmlString.GetString( eTip_sAddDodge );
        break;
    case RT_AddCritical:
        strRand = theXmlString.GetString( eTip_sAddCritical );
        break;
    case RT_AddTenacity:
        strRand = theXmlString.GetString( eTip_sAddTenacity );
        break;
    case RT_AddCriticalIntensity:
        strRand = theXmlString.GetString( eTip_sAddCriticalIntensity );
        break;
    case RT_AddHPMax:
        strRand = theXmlString.GetString( eTip_sAddHPMax );
        break;
    case RT_AddAPMax_UnUse:
        strRand = theXmlString.GetString( eTip_sAddAPMax );
        break;
    case RT_AddBPMax_UnUse:
        strRand = theXmlString.GetString( eTip_sAddBPMax );
        break;
    case RT_AddFPMax_UnUse:
        strRand = theXmlString.GetString( eTip_sAddFPMax );
        break;
    case RT_AddEPMax_UnUse:
        strRand = theXmlString.GetString( eTip_sAddEPMax );
        break;
    case RT_AddMPMax:
        strRand = theXmlString.GetString( eTip_sAddMPMax );
        break;
    case RT_AddBaseAttr:
        strRand = theXmlString.GetString( eTip_sAddBaseAttr );
        break;
    case RT_AddExpPer:
        strRand = theXmlString.GetString( eTip_sAddExpPer );
        break;
    case RT_AddEnergyMax:
        strRand = theXmlString.GetString( eTip_sAddEnergyMax );
        break;
    case RT_AddMoveSpeed:
        strRand = theXmlString.GetString( eTip_sAddMoveSpeed );
        break;
    case RT_AddHPRestore:
        strRand = theXmlString.GetString( eTip_sAddHPRestoreRate );
        break;
    case RT_AddMPRestore:
        strRand = theXmlString.GetString( eTip_sAddMPRestoreRate );
        break;
    case RT_AddFPRestore_UnUse:
        strRand = theXmlString.GetString( eTip_sAddFPRestoreRate );
        break;
    case RT_AddEPRestore_UnUse:
        strRand = theXmlString.GetString( eTip_sAddEPRestoreRate );
        break;
    case RT_AddAPRestore_UnUse:
        strRand = theXmlString.GetString( eTip_sAddAPRestoreRate );
        break;
    case RT_AddBPRestore_UnUse:
        strRand = theXmlString.GetString( eTip_sAddBPRestoreRate );
        break;
	case RT_AddDaoxing:   //道行
		strRand = theXmlString.GetString( eTip_sAddDaoxing );
		break;
	case RT_AddBreakStrike:   //破甲伤害
		strRand = theXmlString.GetString( eTip_sAddBreakStrike );
		break;
	case RT_AddStabStrike:   //贯穿伤害
		strRand = theXmlString.GetString( eTip_sAddStabStrike );
		break;
	case RT_AddElementStrike:   //元素伤害
		strRand = theXmlString.GetString( eTip_sAddElementStrike);
		break;
	case RT_AddToxinStrike:   //毒素伤害
		strRand = theXmlString.GetString( eTip_sAddToxinStrike);
		break;
	case RT_AddSpiritStrike:   //精神伤害
		strRand = theXmlString.GetString( eTip_sAddSpiritStrike);
		break;
	case RT_AddBreakResist:   //破甲抗性
		strRand = theXmlString.GetString( eTip_sAddBreakResist);
		break;
	case RT_AddStabResist:   //贯穿抗性
		strRand = theXmlString.GetString( eTip_sAddStabResist );
		break;
	case RT_AddElementResist:   //元素抗性
		strRand = theXmlString.GetString( eTip_sAddElementResist);
		break;
	case RT_AddToxinResist:   //毒素抗性
		strRand = theXmlString.GetString( eTip_sAddToxinResist);
		break;
	case RT_AddSpiritResist:   //精神抗性
		strRand = theXmlString.GetString( eTip_sAddSpiritResist);
		break;
    default:
        break;
    }
    return strRand;
}

void S_IconInfoHero::ChangeToSoulStampTip( std::string& strDes, float fValue )
{
	uint8 sp =  m_stItem.equipdata.ucSoulPer;
    int nAddValue = fValue * sp / 100.0f;
    int nSize = strDes.size();
    for( int i = nSize; i < SOULSTAMP_CHAR_LEN_AHEAD; ++i )
    {
        strDes += " ";
    }
    strDes += " ";
    char szTemp[MAX_PATH] = {0};
    MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_Tip_SoulStamp ), nAddValue );
    strDes += szTemp;
}

void S_IconInfoHero::MouseTipDrawLine()
{
    DWORD dwDefColor = 0xffffffff;
    m_stInfo[m_ucIconInfoLine].m_bLine = true;
    m_stInfo[m_ucIconInfoLine].m_bImage = true;
    m_stInfo[m_ucIconInfoLine].m_bIcon = false;
    m_stInfo[m_ucIconInfoLine].m_bNewLine = true;
    m_stInfo[m_ucIconInfoLine].m_eImageAlignMode = stIconInfoEx::eIIIA_Left;
    m_stInfo[m_ucIconInfoLine].m_nImageID = -1;
    m_stInfo[m_ucIconInfoLine].m_strImage = MOUSETIP_PICPATH;
    m_stInfo[m_ucIconInfoLine].m_usImageWidth = TIP_LINE_WIDTH;
    m_stInfo[m_ucIconInfoLine].m_usImageHeight = TIP_LINE_HEIGHT;
    m_stInfo[m_ucIconInfoLine].m_usDestWidth = 0;                       // 宽度由底层实现
    m_stInfo[m_ucIconInfoLine].m_usDestHeight = TIP_LINE_HEIGHT;
    m_stInfo[m_ucIconInfoLine].m_usSrcX = TIP_LINE_SRC_X;
    m_stInfo[m_ucIconInfoLine].m_usSrcY = TIP_LINE_SRC_Y;
    m_stInfo[m_ucIconInfoLine].m_col = dwDefColor;
    m_ucIconInfoLine++;
}

void S_IconInfoHero::ShowEquipScore( void* pItemDetail, INT nType )
{
	if( nType != ItemDefine::ITEMTYPE_ARMOUR  && nType != ItemDefine::ITEMTYPE_WEAPON )
		return;	

	ItemDefine::SItemCanEquip* pEquip = NULL;
	if( pItemDetail )
	{
		pEquip = ( ItemDefine::SItemCanEquip* )pItemDetail;
	}
	else
	{
		return;
	}

	if ( pEquip->bFashion )
		return;

	if ( strlen( m_stItem.itembaseinfo.szCreaterName) > 0 )
	{
		char szTemp[256] = {0};
		MouseTipDrawLine();
		sprintf( szTemp, "%s %s", theXmlString.GetString(eText_EquipOwner), m_stItem.itembaseinfo.szCreaterName );
		SHOW_STRING( szTemp, Color_Config.getColor( CC_PetColor_Green ) );
	}

	if (m_stItem.equipdata.fScore > 0.0f)
	{
		char szTemp[256] = {0};
		MouseTipDrawLine();
		sprintf( szTemp, "%s %d", theXmlString.GetString(eText_EquipScore), (int)m_stItem.equipdata.fScore );
		SHOW_STRING( szTemp, Color_Config.getColor( CC_PetColor_Green ) );
	}
}
void S_IconInfoHero::ShowSuit(void* pItemDetail, INT nType,int nPlayerID)
{
	//在装备或者防具后面 显示装备的套装属性 判断这件装备是否属于自己的 并且穿在身上
	if( nType != ItemDefine::ITEMTYPE_WEAPON && nType != ItemDefine::ITEMTYPE_ARMOUR )
        return;

    ItemDefine::SItemCanEquip* pEquip = NULL;
    if( pItemDetail )
    {
        pEquip = (ItemDefine::SItemCanEquip*)pItemDetail;
    }
    else
    {
		return;
	}

	//判断装备是否属于自己的
	unsigned int SuitID = theSuitConfig.GetSuitIDByItemID(pEquip->ustItemID);
	if(SuitID == 0)
		return;
	SuitAtt* pSuitAtt = theSuitConfig.GetSuitInfoBySuitID(SuitID);
	if(!pSuitAtt)
		return;
	//处理玩家身上的装备处理
	std::set<unsigned int> SuitList;
	int Sum = 0;
    CPlayer *pPlayer = theHeroGame.GetPlayerMgr()->FindByID( nPlayerID );
    if( pPlayer )
    {
        SCharItem* pEquipItems = 0;
        if( theHeroGame.GetPlayerMgr()->GetMe() == pPlayer )
            pEquipItems = thePlayerRole.m_pVisual->GetVisual( 0 );
        else
            pEquipItems = pPlayer->GetSeekEquipInfo();
        if( pEquipItems != 0 )
        {
            for( int i = 0 ; i < EEquipPartType_MaxEquitPart ; ++ i )
            {
                SCharItem* pPlayerEquip = &pEquipItems[i];
                if( pPlayerEquip )
                {
                    ItemDefine::SItemCommon* pPlayerItem = GettheItemDetail().GetItemByID( pPlayerEquip->itembaseinfo.ustItemID );
                    if( pPlayerItem && 
                        (pPlayerItem->ucItemType == ItemDefine::ITEMTYPE_ARMOUR  
						|| pPlayerItem->ucItemType == ItemDefine::ITEMTYPE_WEAPON))
                    {
						//获取到装备 我们开始分析装备的处理
						if(theSuitConfig.GetSuitIDByItemID(pPlayerEquip->itembaseinfo.ustItemID) == SuitID)
						{
							//当前装备为套装的时候 
							//1.记录到集合里去
							if(SuitList.count(pPlayerEquip->itembaseinfo.ustItemID) == 0)
								SuitList.insert(std::set<unsigned int>::value_type(pPlayerEquip->itembaseinfo.ustItemID));
							++Sum;
						}
                    }	
                }	
            }
        }
    }
	Sum = 	pSuitAtt->IsRepeatItem?Sum:SuitList.size();
	if(Sum == 0)
	{
		Sum=1;//最少一件
		if(SuitList.empty())
		{
			SuitList.insert(std::set<unsigned int>::value_type(pEquip->ustItemID));
		}
	}
	//套装以及处理完毕后 我们开始处理数据
	//1.套装名称xxx(1/xx)
	MouseTipDrawLine();
	int nCurrentLine = m_ucIconInfoLine;
	m_stInfo[nCurrentLine].m_strInfo = pSuitAtt->Name;//套装的名称
	m_stInfo[m_ucIconInfoLine].m_col = Color_Config.getColor( CC_ItemTip_SuitPart_Have );
	m_ucIconInfoLine++;
	std::vector<unsigned int>::iterator Iter = pSuitAtt->ItemList.begin();
	for(;Iter !=pSuitAtt->ItemList.end();++Iter)
	{
		ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID(*Iter);
		char szTemp[MAX_PATH] = { 0 };
		sprintf_s( szTemp, 256, "  %s", pCommon->GetItemName());
        if( std::find( SuitList.begin(), SuitList.end(), *Iter ) != SuitList.end())
		{
            SHOW_STRING( szTemp, Color_Config.getColor( CC_ItemTip_SuitPart_Have ) );
		}
        else
		{
            SHOW_STRING( szTemp, Color_Config.getColor( CC_ItemTip_SuitPart_NotHave ));
		}
	}
	char szPartNum[MAX_PATH] = { 0 };
	MeSprintf_s( szPartNum, sizeof( szPartNum ) / sizeof( char ) - 1, " ( %d/%d )", Sum, pSuitAtt->ItemList.size() );
    m_stInfo[nCurrentLine].m_strInfo = m_stInfo[nCurrentLine].m_strInfo + szPartNum;
	//显示套装的属性
	//套装属性 应该包含一件装备的全部的固定属性 和 技能 什么的 
	std::map<unsigned char,unsigned int>::iterator MapIter = pSuitAtt->SuitList.begin();
	DWORD dwAttrColor = 0;
	for(;MapIter != pSuitAtt->SuitList.end();++MapIter)
	{
		int MinSum = MapIter->first;//几件套属性
		ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( MapIter->second );
		if( MinSum <= Sum )//满足数量
            dwAttrColor = Color_Config.getColor( CC_ItemTip_SuitAttr_Have );
        else
            dwAttrColor = Color_Config.getColor( CC_ItemTip_SuitAttr_NotHave );
		char szTemp[256] = {0};
		sprintf_s( szTemp, 256, "%s (%d):", theXmlString.GetString( eText_Suit ), MinSum );
		SHOW_STRING(szTemp,dwAttrColor);
		//设置完毕后 我们显示需要的属性
		ShowSuitAtter(MapIter->second ,dwAttrColor,MinSum);
	}
}
void S_IconInfoHero::ShowSuitAtter(unsigned int ItemID,DWORD Color,int Count)//一件所有属性全部是固定的装备 我们将其设置为套装属性
{
	ItemDefine::SItemCommon* pPlayerItem = GettheItemDetail().GetItemByID(ItemID);
    if( pPlayerItem && (pPlayerItem->ucItemType == ItemDefine::ITEMTYPE_ARMOUR    || pPlayerItem->ucItemType == ItemDefine::ITEMTYPE_WEAPON))
	{
		//显示具体的属性
		ItemDefine::SItemCanEquip * pEquipCommon = (ItemDefine::SItemCanEquip * )pPlayerItem;
		char szTemp[256] = {0};
		if(pPlayerItem->ucItemType == ItemDefine::ITEMTYPE_ARMOUR)
		{
			//为防具的话
			ItemDefine::SItemArmour* pArmour = (ItemDefine::SItemArmour*)pEquipCommon;
			if(pArmour)
			{
				if( pArmour->defendPhysics != 0 )    
				{
					// 近
					MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "    %s+%d", theXmlString.GetString( eText_PlayDef_Short ),
						(int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->defendPhysics, 0) );    
					std::string strDescribe = szTemp;
					SHOW_STRING( strDescribe.c_str(),Color);
				}

				if( pArmour->defendMagic != 0 )    
				{
					// 魔
					MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "    %s+%d", theXmlString.GetString( eText_PlayDef_Magic ),
						(int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->defendMagic, 0) );    
					std::string strDescribe = szTemp;
					SHOW_STRING( strDescribe.c_str(),Color);
				}

				if( pArmour->Hp != 0 )    
				{
					// 血
					MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "    %s+%d", theXmlString.GetString( eTip_sAddHPMax ),
						(int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->Hp, 0) );    
					std::string strDescribe = szTemp;
					SHOW_STRING( strDescribe.c_str(),Color);
				}
				if( pArmour->Mp != 0 )    
				{
					// Mp
					MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "    %s+%d", theXmlString.GetString( eTip_sAddMPMax ),
						(int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->Mp, 0 ) );    
					std::string strDescribe = szTemp;
					SHOW_STRING( strDescribe.c_str(), Color);
				}
			}
		}
		if(pEquipCommon->attackPhysics != 0)
		{
			int nAttStarVal = GetAttributeWithLevel( pEquipCommon->ustEquipType, pEquipCommon->attackPhysics,0);
			std::string strDescribe;
			MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "    %s+%d", theXmlString.GetString( eText_PlayAtt_Short ), nAttStarVal );
			strDescribe = szTemp;
			SHOW_STRING( strDescribe.c_str(),Color);
		}
		// 魔
		if(pEquipCommon->attackMagic != 0)
		{
			int nAttStarVal = GetAttributeWithLevel( pEquipCommon->ustEquipType, pEquipCommon->attackMagic,0);
			std::string strDescribe;		
			MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "    %s+%d", theXmlString.GetString( eText_PlayAtt_Magic ), nAttStarVal );
			strDescribe = szTemp;
			SHOW_STRING( strDescribe.c_str(),Color);
		}
		if(pEquipCommon->attackSpeed != 0)
		{
			int nAttStarVal = GetAttributeWithLevel( pEquipCommon->ustEquipType, pEquipCommon->attackSpeed,0);
			std::string strDescribe;		
			MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "    %s+%d", theXmlString.GetString( eUI_stAttSpeedChanged ), nAttStarVal );
			strDescribe = szTemp;
			SHOW_STRING( strDescribe.c_str(),Color);
		}
		//命中率
		if(pEquipCommon->exact != 0)
		{
			int nAttStarVal = GetAttributeWithLevel( pEquipCommon->ustEquipType, pEquipCommon->exact,0);
			std::string strDescribe;
			MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "    %s+%d", theXmlString.GetString( eTip_sAddExact ), nAttStarVal );
			strDescribe = szTemp;
			SHOW_STRING( strDescribe.c_str(), Color );
			
		}

		//闪避率
		if(pEquipCommon->dodge != 0)
		{
			int nAttStarVal = GetAttributeWithLevel( pEquipCommon->ustEquipType, pEquipCommon->dodge,0);
			std::string strDescribe;
			MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "    %s+%d", theXmlString.GetString( eTip_sAddDodge ), nAttStarVal );
			strDescribe = szTemp;
			SHOW_STRING( strDescribe.c_str(), Color );
		}
		//暴击率
		if(pEquipCommon->critical != 0)
		{
			int nAttStarVal = GetAttributeWithLevel( pEquipCommon->ustEquipType, pEquipCommon->critical,0 );
			std::string strDescribe;
			MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "    %s+%d", theXmlString.GetString( eTip_sAddCritical ), nAttStarVal );
			strDescribe = szTemp;
			SHOW_STRING( strDescribe.c_str(), Color );
			
		}

		//韧性
		if(pEquipCommon->tenacity != 0)
		{
			int nAttStarVal = GetAttributeWithLevel( pEquipCommon->ustEquipType, pEquipCommon->tenacity,0);
			std::string strDescribe;
			MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "    %s+%d", theXmlString.GetString( eTip_sAddTenacity ), nAttStarVal );
			strDescribe = szTemp;
			SHOW_STRING( strDescribe.c_str(), Color );
			
		}
		//破甲伤害
		if(pEquipCommon->breakStrike != 0)
		{
			int nAttStarVal = GetAttributeWithLevel( pEquipCommon->ustEquipType, pEquipCommon->breakStrike,0);
			std::string strDescribe;
			MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "    %s+%d", theXmlString.GetString( eTip_sAddBreakStrike ), nAttStarVal );
			strDescribe = szTemp;
			SHOW_STRING( strDescribe.c_str(), Color );

		}
		//破甲抗性
		if(pEquipCommon->breakResist != 0)
		{
			int nAttStarVal = GetAttributeWithLevel( pEquipCommon->ustEquipType, pEquipCommon->breakResist,0);
			std::string strDescribe;
			MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "    %s+%d", theXmlString.GetString( eTip_sAddBreakResist ), nAttStarVal );
			strDescribe = szTemp;
			SHOW_STRING( strDescribe.c_str(), Color );

		}
		//贯穿伤害
		if(pEquipCommon->stabStrike != 0)
		{
			int nAttStarVal = GetAttributeWithLevel( pEquipCommon->ustEquipType, pEquipCommon->stabStrike,0);
			std::string strDescribe;
			MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "    %s+%d", theXmlString.GetString( eTip_sAddStabStrike ), nAttStarVal );
			strDescribe = szTemp;
			SHOW_STRING( strDescribe.c_str(), Color );

		}
		//贯穿抗性
		if(pEquipCommon->stabResist != 0)
		{
			int nAttStarVal = GetAttributeWithLevel( pEquipCommon->ustEquipType, pEquipCommon->stabResist,0);
			std::string strDescribe;
			MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "    %s+%d", theXmlString.GetString( eTip_sAddStabResist ), nAttStarVal );
			strDescribe = szTemp;
			SHOW_STRING( strDescribe.c_str(), Color );

		}
		//元素伤害
		if(pEquipCommon->elementStrike != 0)
		{
			int nAttStarVal = GetAttributeWithLevel( pEquipCommon->ustEquipType, pEquipCommon->elementStrike,0);
			std::string strDescribe;
			MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "    %s+%d", theXmlString.GetString( eTip_sAddElementStrike ), nAttStarVal );
			strDescribe = szTemp;
			SHOW_STRING( strDescribe.c_str(), Color );

		}
		//元素抗性
		if(pEquipCommon->elementResist != 0)
		{
			int nAttStarVal = GetAttributeWithLevel( pEquipCommon->ustEquipType, pEquipCommon->elementResist,0);
			std::string strDescribe;
			MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "    %s+%d", theXmlString.GetString( eTip_sAddElementResist ), nAttStarVal );
			strDescribe = szTemp;
			SHOW_STRING( strDescribe.c_str(), Color );

		}
		//毒素伤害
		if(pEquipCommon->toxinStrike != 0)
		{
			int nAttStarVal = GetAttributeWithLevel( pEquipCommon->ustEquipType, pEquipCommon->toxinStrike,0);
			std::string strDescribe;
			MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "    %s+%d", theXmlString.GetString( eTip_sAddToxinStrike ), nAttStarVal );
			strDescribe = szTemp;
			SHOW_STRING( strDescribe.c_str(), Color );

		}
		//毒素抗性
		if(pEquipCommon->toxinResist != 0)
		{
			int nAttStarVal = GetAttributeWithLevel( pEquipCommon->ustEquipType, pEquipCommon->toxinResist,0);
			std::string strDescribe;
			MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "    %s+%d", theXmlString.GetString( eTip_sAddToxinResist ), nAttStarVal );
			strDescribe = szTemp;
			SHOW_STRING( strDescribe.c_str(), Color );

		}
		//精神伤害
		if(pEquipCommon->spiritStrike != 0)
		{
			int nAttStarVal = GetAttributeWithLevel( pEquipCommon->ustEquipType, pEquipCommon->spiritStrike,0);
			std::string strDescribe;
			MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "    %s+%d", theXmlString.GetString( eTip_sAddSpiritStrike ), nAttStarVal );
			strDescribe = szTemp;
			SHOW_STRING( strDescribe.c_str(), Color );

		}
		//精神抗性
		if(pEquipCommon->spiritResist != 0)
		{
			int nAttStarVal = GetAttributeWithLevel( pEquipCommon->ustEquipType, pEquipCommon->spiritResist,0);
			std::string strDescribe;
			MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "    %s+%d", theXmlString.GetString( eTip_sAddSpiritResist ), nAttStarVal );
			strDescribe = szTemp;
			SHOW_STRING( strDescribe.c_str(), Color );
		}
		//随机属性 应该是固定的
		EquipBaseRand(pPlayerItem,pPlayerItem->ucItemType,Color);
		//我们现行 套装属性对应的技能信息
		if(pEquipCommon->skillId != 0)
		{
			//有技能 我们展示出来
			ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( pEquipCommon->skillId, pEquipCommon->skillLevel );		
			if( !pSkill )
				return;
			// (x) 套装技能:技能名字
			sprintf_s( szTemp, 256, "    %s%s(%s%d)",theXmlString.GetString( eText_SuitSkill ), pSkill->GetSkillName(),theXmlString.GetString( eText_Level ),pEquipCommon->skillLevel);
			SHOW_STRING(szTemp,Color);
			//// 技能描述
			//memset( szTemp, 0, sizeof(szTemp) );
			//int nLength = 0;
			//std::string szItemDesc = pEquipCommon->GetItemDesc();
			//for ( UINT n=0; n<szItemDesc.size(); n++ )
			//{
			//	if ( szItemDesc[n] != 0 &&
			//		szItemDesc[n] == '\\' && szItemDesc[n+1] == 'n' )
			//	{
			//		SHOW_STRING(szTemp,Color);
			//		memset( szTemp, 0, sizeof(szTemp) );
			//		nLength = 0;
			//		n++;
			//	}
			//	else
			//	{
			//		szTemp[nLength++] = szItemDesc[n];
			//		if ( n == szItemDesc.size() - 1 && strlen(szTemp) > 0 )
			//		{
			//			SHOW_STRING(szTemp,Color);
			//		}
			//	}
			//	assert( m_ucIconInfoLine < MAX_ICON_INFO_EX_LINE_COUNT );
			//}	
		}
	}
}
void S_IconInfoHero::EquipBaseRand( void* pItemDetail, INT nType ,DWORD Color)
{
	if( nType != ItemDefine::ITEMTYPE_ARMOUR  && nType != ItemDefine::ITEMTYPE_WEAPON )
        return;	
	ItemDefine::SItemCanEquip* pEquip = NULL;
    if( pItemDetail )
    {
        pEquip = ( ItemDefine::SItemCanEquip* )pItemDetail;
    }
    else
    {
        return;
    }
	uint16 rands[ SCharItem::EConstDefine_BaseRandMaxCount ] = { 0 };
	//生成随机属性词条 
	short sRandNum = 0;
	for ( int i = 0; i < ItemDefine::SItemCanEquip::ECD_AdditiveRandAttrCount; ++i )
	{
		int16 nRoll = theRand.rand16() % 10000;
		if ( nRoll < pEquip->additiveRandCountRates[i] )
		{
			sRandNum = ItemDefine::SItemCanEquip::ECD_AdditiveRandAttrCount - i;
			break;
		}
	}
	if (sRandNum <= 0)
	{
		//对鉴定结果为无附加随机属性的装备做的处理来标记为已鉴定过
		rands[0] = SCharItem::EConstDefine_HasBaseRanded;
		return;
	}
	if (sRandNum > SCharItem::EConstDefine_BaseRandMaxCount)
	{ sRandNum = SCharItem::EConstDefine_BaseRandMaxCount; }

	//清空随机属性
	memset( rands, 0, sizeof(uint16) * SCharItem::EConstDefine_BaseRandMaxCount );

	CItemDetail::RandAttrContainer randResult;
	for (int i = 0; i<sRandNum; ++i)
	{
		if ( pEquip->additiveRandFlags[i] )
		{ // 数值
			ItemDefine::SRandAttribute* pRand = GettheItemDetail().GetRandByID(pEquip->additiveRandFlags[i]);

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
			if ( pEquip->additiveRandLvUpperLimit - pEquip->additiveRandLvLowerLimit >= 0 )
			{
				nRollLvl = theRand.rand16() % ( pEquip->additiveRandLvUpperLimit - pEquip->additiveRandLvLowerLimit + 1 ) + pEquip->additiveRandLvLowerLimit;
			}
			GettheItemDetail().GetRandByLevel(nRollLvl,randsByLvl);

			//类型筛选
			CItemDetail::RandAttrContainer randsAfterFilter;
			CItemDetail::ItrRandAttrContainer it = randsByLvl.begin();
			for ( ; it != randsByLvl.end(); ++it )
			{
				int i = 0;
				for ( ; i < pEquip->typeFilter.GetSize(); ++i )
				{
					if ( pEquip->typeFilter[i] > 0  && pEquip->typeFilter[i] == it->usType )
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
	uint16 Temp = 0;
	for(int i =0;i<SCharItem::EConstDefine_BaseRandMaxCount-1;++i)
	{	
		for(int j =i+1;j<SCharItem::EConstDefine_BaseRandMaxCount-1;++j)
		{
			if(rands[i] > rands[j])
			{			
				Temp = rands[i];
				rands[i] = rands[j];
				rands[j] = Temp;
			}
		}
	}
	int nRandValue = 0;
	char szTemp[256];
    int nTipPreTextIndex = 0;
	//随机词缀生成完毕后 我们浮现出来
	for (int nloop = 0; nloop < SCharItem::EConstDefine_BaseRandMaxCount; ++nloop)
    {    
		if ( rands[nloop] == InvalidLogicNumber )
		{ continue; }

        ItemDefine::SRandAttribute* pEquipRand = NULL;
        unsigned short usRand =rands[nloop];

        pEquipRand = GettheItemDetail().GetRandByID(usRand);

        if (!pEquipRand)
            continue;

        for( int i = 0 ; i < ItemDefine::SRandAttribute::CD_TypeCount ; ++ i )
        {
            nRandValue = GetRandValueByType( pEquipRand, i );
            if( pEquipRand->type[i] == RT_None )
                continue;

			//float intensity = GettheItemDetail().GetEquipQualityIntensity(pEquip->ustLevel);

            if( pEquipRand->type[i] == RT_AddMoveSpeed )
            {
                sprintf( szTemp, "    %s+%.2f", S_IconInfoHero::GetRandStringByType( pEquipRand->type[i] ).c_str(), 
					nRandValue);
            }
            else
            {
				sprintf( szTemp, "    %s+%d", GetRandStringByType( pEquipRand->type[i] ).c_str(), nRandValue > 0 ? nRandValue : 1);  
                if( pEquipRand->type[i] == RT_AddExpPer )
                    sprintf( szTemp, "%s%s",szTemp,"%");
            }
            SHOW_STRING( szTemp,Color);
            nTipPreTextIndex ++ ;
        }
    }
}