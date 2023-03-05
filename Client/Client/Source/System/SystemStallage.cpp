/********************************************************************
            �°�̯ϵͳ        by ZhuoMeng.Hu		[12/23/2010]
*********************************************************************/

#include "SystemStallage.h"
#include "ScreenInfoManager.h"
#include "Cfg.h"
#include "PrivateShop.h"
#include "PlayerRole.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "GameMain.h"
#include "SeekPet.h"
#include "PlayerPrivateShop.h"
#include "EditPrice.h"
#include "ReclaimPriceInput.h"
#include "ChatCheck.h"
#include "SoundConfig.h"
#include "BatchShop.h"
#include "ChatMessageMgr.h"
#include "TradeRecord.h"
#include "Pack.h"
#include "Pet.h"
#include "WealthProtect.h"
#include "PreventWallow.h"
#include "Bargaining.h"
#include "PackItemEnableManager.h"
#include "Rename.h"
#include "MessageBox.h"
#include "ui/SelectPet.h"
#include "Helper/PetHelper.h"
#include "ui/ChooseShopType.h"
#include "StallConfig.h"
const int CSystemStallage::m_goodsIndex[] = {0, 12, 18, StallDefine::MaxSellCount, StallDefine::MaxSellCount + 1, StallDefine::MaxStallCount};
extern const char* GetRootPath();
CSystemStallage::CSystemStallage()
: m_nItemSellIndexBegin( 0 ),
m_nMountSellIndexBegin( 18 ),
m_nItemBuyIndexBegin( StallDefine::MaxSellCount + 1 ),
m_nItemBuyStackCnt( 99 ),
m_bOnlineStall(true)
{
    assert( m_nItemBuyIndexBegin < StallDefine::MaxStallCount );
    m_tradeRecordVec.clear();
    m_nVenderPlayerId = -1;
    m_bStallageFirstShow = true;
}

CSystemStallage::~CSystemStallage()
{
}

bool CSystemStallage::IsPackItemBeUsing( __int64 nGuid )
{
    if( nGuid <= 0 )
        return false;

    if( s_CUI_ID_FRAME_PrivateShop.IsVisable() || IsSelfInStalling() )
    {
        for( int i = 0; i < StallDefine::MaxStallCount; ++i )
        {
            if( m_selfStallData[i].GetGuid() == nGuid )
            {
                return true;
            }
        }
    }
    return false;
}

//-----------------------------------�ڲ��߼�---------------------------------------
// ��ɫ��½�����ڳ�ʼ��
void CSystemStallage::TellSelfEnterWorld()
{
    m_bStallageFirstShow = true;
    ClearTradeRecord();
}

// �����������
void CSystemStallage::ClearSelfStallage()
{
    for( int i = 0; i < StallDefine::MaxStallCount; ++i )
    {
        m_selfStallData[i].ClearStall();
    }
}

// �����������
void CSystemStallage::ClearPlayerStallage()
{
    memset( m_playerSellData, 0, sizeof( m_playerSellData ) );
    memset( m_playerBuyData, 0, sizeof( m_playerBuyData ) );
}

// �չ���Ʒ�ѵ������������
int CSystemStallage::GetBuyStackNumLimit()
{
    return m_nItemBuyStackCnt;
}

// ��ȡ����̯����������
SellDataToClient* CSystemStallage::GetPlayerSellData()
{
    return m_playerSellData;
}

// ��ȡ����̯���չ�����
BuyDataToClient* CSystemStallage::GetPlayerBuyData()
{
    return m_playerBuyData;
}

// ���ݷ���˵�������ȡ�ͻ��˵�
int CSystemStallage::GetSubIndexByTotalIndex( int nIndex, int nUsage, int nBagType )
{
    int nSubIndex( -1 );
    switch( nUsage )
    {
    case StallDefine::StallSell:
        {
            switch( nBagType )
            {
            case BT_NormalItemBag:
            case BT_MaterialBag:
                {
                    if( nIndex < m_nItemSellIndexBegin || nIndex >= m_nMountSellIndexBegin )
                        return -1;
                    nSubIndex = nIndex - m_nItemSellIndexBegin;
                }
                break;
            case BT_MountBag:
                {
                    if( nIndex < m_nMountSellIndexBegin || nIndex >= m_nItemBuyIndexBegin )
                        return -1;
                    nSubIndex = nIndex - m_nMountSellIndexBegin;
                }
                break;
            default:
                {
                    return -1;
                }
                break;
            }
        }
        break;
    case StallDefine::StallBuy:
        {
            if( nIndex < m_nItemBuyIndexBegin || nIndex >= StallDefine::MaxStallCount )
                return -1;
            nSubIndex = nIndex - m_nItemBuyIndexBegin;
        }
        break;
    default:
        {
            return -1;
        }
        break;
    }
    return nSubIndex;
}

int CSystemStallage::GetTotalIndexBySubIndex(int subIndex_, EGoodsType goodType_)
{
	if(subIndex_ < 0 || goodType_ >= E_Goods_end)
		return -1;

	int totalIndex = m_goodsIndex[goodType_] + subIndex_;
	if(!CheckGoodIndex(totalIndex, goodType_))
		return -1;

	return totalIndex;
}

// ���ݿͻ��˵�������ȡ����˵�
int CSystemStallage::GetTotalIndexBySubIndex( int nIndex, int nUsage, int nBagType )
{
    if( nIndex < 0 )
        return -1;

    int nTotalIndex( -1 );
    switch( nUsage )
    {
    case StallDefine::StallSell:
        {
            switch( nBagType )
            {
            case BT_NormalItemBag:
            case BT_MaterialBag:
                {
                    if( nIndex >= m_nMountSellIndexBegin - m_nItemSellIndexBegin )
                        return -1;
                    nTotalIndex = nIndex + m_nItemSellIndexBegin;
                }
                break;
            case BT_MountBag:
                {
                    if( nIndex >= m_nItemBuyIndexBegin - m_nMountSellIndexBegin )
                        return -1;
                    nTotalIndex = nIndex + m_nMountSellIndexBegin;
                }
                break;
            default:
                {
                    return -1;
                }
                break;
            }
        }
        break;
    case StallDefine::StallBuy:
        {
            if( nIndex >= StallDefine::MaxStallCount - m_nItemBuyIndexBegin )
                return -1;
            nTotalIndex = nIndex + m_nItemBuyIndexBegin;
        }
        break;
    default:
        {
            return -1;
        }
        break;
    }
    if( nTotalIndex < 0 || nTotalIndex >= StallDefine::MaxStallCount )
        return -1;

    return nTotalIndex;
}

bool CSystemStallage::ClassifyByTotalIndex( IN int nTotalIndex, OUT int& nSubIndex, OUT int& nUsage, OUT bool& bIsMount )
{
    if( nTotalIndex < m_nItemSellIndexBegin || nTotalIndex >= StallDefine::MaxStallCount )
        return false;

    if( nTotalIndex < m_nMountSellIndexBegin )
    {
        nSubIndex = nTotalIndex - m_nItemSellIndexBegin;
        nUsage = StallDefine::StallSell;
        bIsMount = false;
    }
    else if( nTotalIndex >= m_nMountSellIndexBegin && nTotalIndex < m_nItemBuyIndexBegin )
    {
        nSubIndex = nTotalIndex - m_nMountSellIndexBegin;
        nUsage = StallDefine::StallSell;
        bIsMount = true;
    }
    else
    {
        nSubIndex = nTotalIndex - m_nItemBuyIndexBegin;
        nUsage = StallDefine::StallBuy;
        bIsMount = false;
    }
    return true;
}

//-----------------------------------�ӿ�---------------------------------------
// �Լ��Ƿ��ڰ�̯
bool CSystemStallage::IsSelfInStalling()
{
    if( !CheckMeExist() )
        return false;
    return theHeroGame.GetPlayerMgr()->GetMe()->IsPrivateShopOpen();
}

// ����Ƿ��ڰ�̯
bool CSystemStallage::IsPlayerInStalling( int nPlayerId )
{
    if( !CheckPlayerExist( nPlayerId ) )
        return false;
    return theHeroGame.GetPlayerMgr()->FindByID( nPlayerId )->IsPrivateShopOpen();
}

// �����Ƿ���̯λ��
bool CSystemStallage::IsMountInStallage( __int64 nGuid )
{
    for( int i = m_nMountSellIndexBegin; i < m_nItemBuyIndexBegin; ++i )
    {
        if( m_selfStallData[i].GetGuid() == nGuid && m_selfStallData[i].GetCount() > 0 )
            return true;
    }
    return false;
}

bool CSystemStallage::IsPetInStallage(__int64 nGuid )
{
	for( int i = m_goodsIndex[E_Goods_pet]; i < m_goodsIndex[E_Goods_pet + 1]; ++i )
	{
		if( m_selfStallData[i].GetGuid() == nGuid && m_selfStallData[i].GetCount() > 0 )
			return true;
	}
	return false;
}

// ��ȡ̯��ID
int CSystemStallage::GetVenderId()
{
    return m_nVenderPlayerId;
}

// �ж� GetPlayerMgr()->GetMe()
bool CSystemStallage::CheckMeExist()
{
    CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
    if( !pPlayerMgr )
        return false;

    CPlayer* pMe = pPlayerMgr->GetMe();
    if( !pMe )
        return false;

    return true;
}

// �ж� GetPlayerMgr()->FindById()
bool CSystemStallage::CheckPlayerExist( int nPlayerId )
{
    if( nPlayerId < 0 )
        return false;

    CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
    if( !pPlayerMgr )
        return false;

    CPlayer* pPlayer = pPlayerMgr->FindByID( nPlayerId );
    if( !pPlayer )
        return false;

    return true;
}

// �鿴�Լ�������
void CSystemStallage::SeekSelfMountByIndex( int nIndex, __int64 nGuid )
{
    int nTotalIndex = GetTotalIndexBySubIndex( nIndex, StallDefine::StallSell, BT_MountBag );
    if( nTotalIndex < m_nMountSellIndexBegin || nTotalIndex >= StallDefine::MaxStallCount )
        return;

    if( m_selfStallData[nTotalIndex].GetBagType() != BT_MountBag )
        return;

    __int64 nMountGuid = m_selfStallData[nTotalIndex].GetGuid();
    if( nMountGuid != nGuid )
        return;

    SMountItem* pMount = thePlayerRole.GetMountByGUID( nGuid );
    if( !pMount )
        return;

    s_CUI_ID_FRAME_SeekPet.SetVisable( true );
    s_CUI_ID_FRAME_SeekPet.SetMount( *pMount );
}

// �鿴̯��������
void CSystemStallage::SeekPlayerMountByIndex( int nIndex, __int64 nGuid )
{
    int nTotalIndex = GetTotalIndexBySubIndex( nIndex, StallDefine::StallSell, BT_MountBag );
    if( nTotalIndex < m_nMountSellIndexBegin || nTotalIndex >= StallDefine::MaxStallCount )
        return;

    if( m_playerSellData[nTotalIndex].GetBagType() != BT_MountBag )
        return;
    
    SMountItem mountItem;
    if( !m_playerSellData[nTotalIndex].GetData( &mountItem, sizeof( SMountItem ) ) )
        return;

    if( mountItem.GetMountGuid() != nGuid )
		return;

    s_CUI_ID_FRAME_SeekPet.SetVisable( true );
    s_CUI_ID_FRAME_SeekPet.SetMount( mountItem );
}

// ��ȡ���׼�¼
const std::vector<std::string>& CSystemStallage::GetTradeRecord()
{
    return m_tradeRecordVec;
}

std::string CSystemStallage::GetPriceTipString( DWORD dwPrice )
{
    char szPriceInfo[MAX_PATH] = {0};
    int nGold( 0 ), nSilver( 0 ), nCopper( 0 );
    thePlayerRole.GetGSCFromMoney( dwPrice, nGold, nSilver, nCopper );

    std::stringstream str;
    if( nGold > 0 )
        str << nGold << theXmlString.GetString( eText_Money_Gold );
    if( nSilver > 0 )
        str << nSilver << theXmlString.GetString( eText_Money_Silver );
    if( nCopper > 0 || ( nGold == 0 && nSilver == 0 ) )
        str << nCopper << theXmlString.GetString( eText_Money_Copper );
    std::string strPrice = str.str();

    MeSprintf_s( szPriceInfo, sizeof( szPriceInfo ) / sizeof( char ) - 1, theXmlString.GetString( eText_Stall_TipPrice ), strPrice.c_str() );
    return std::string( szPriceInfo );
}

int CSystemStallage::GetMountIndexByGuid( __int64 nGuid )
{
    for( int i = 0 ; i < thePlayerRole.GetCharInfo2().baseinfo.liveinfo.ucMountCount; ++i )
    {
        if( thePlayerRole.GetCharInfo2().ItemBagData.miItems[i].baseInfo.guid == nGuid )
            return i;
    }
    return -1;
}

// ˢ�±�������Ʒ�� Enablehe �� Disable
void CSystemStallage::RefreshCharItemsInStallage()
{
    bool bEnable = !( s_CUI_ID_FRAME_PrivateShop.IsVisable() || IsSelfInStalling() );
    for( int i = 0; i < StallDefine::MaxStallCount; ++i )
    {
        if( m_selfStallData[i].GetStallType() == StallDefine::StallSell && m_selfStallData[i].GetCount() > 0 )
        {
            SetCharItemEnable( m_selfStallData[i].GetGuid(), bEnable );
        }
    }

    // ��ǰ�İ�̯ϵͳ�����������ˢ�£���֪����ʲô�ã���ʱ�ȸ����������
    //ItemDefine::SItemCommon *pitemCommon = GettheItemDetail().GetItemByID(stSrcItem.itembaseinfo.ustItemID);
    //if ( pitemCommon && pitemCommon->ucItemType == ItemDefine::ITEMTYPE_RESTORE )
    //{
    //	ItemDefine::SItemRestore* pItemRestore = (ItemDefine::SItemRestore*)pitemCommon;
    //	if ( pItemRestore->bHPAuto || pItemRestore->bMPAuto || pItemRestore->bAutoRelive )
    //	{
    //		thePlayerRole.refreshHotKey();
    //	}
    //}
}

// ������ұ������������� Enablehe �� Disable
void CSystemStallage::SetCharItemEnable( __int64 nGuid, bool bEnable )
{
    int nIndex( -1 );

    // ��ͨ����
    nIndex = thePlayerRole.m_bag.GetItemIndexByGUID( nGuid );
    if( nIndex >= 0 )
    {
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, nIndex, true );
        return;
    }

    // ���ϰ���
    nIndex = thePlayerRole.m_bagMaterial.GetItemIndexByGUID( nGuid );
    if( nIndex >= 0 )
    {
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, nIndex, true );
        return;
    }

    // ����
    nIndex = GetMountIndexByGuid( nGuid );
    if( nIndex >= 0 && nIndex < ITEM_MOUNT_MAXCOUNT )
    {
        ControlIconDrag::S_ListImg* pListImg = s_CUI_ID_FRAME_Pet.PenIcon_GetItemByIndex( nIndex );
        if( pListImg )
        {
            s_CUI_ID_FRAME_Pet.RefreshIconInfo();
        }
        return;
    }
}

bool CSystemStallage::GetSelfItemPrice(int subIndex_, EGoodsType goodType_, int &_moneyPrice, int &_goldPrice, int &_count)
{
	if(goodType_ >= E_Goods_end || subIndex_ < 0)
		return false;

	int totalIndex = GetTotalIndexBySubIndex(subIndex_, goodType_);
	if(totalIndex < 0)
		return false;

	_count = m_selfStallData[totalIndex].GetCount();
	if(_count <= 0)
		return false;

	_moneyPrice = m_selfStallData[totalIndex].GetGameMoneyPrice();
	_goldPrice = m_selfStallData[totalIndex].GetRMBMoneyPrice();
	if( _moneyPrice < 0 || _goldPrice < 0 )
		return false;

	return true;
}

bool CSystemStallage::GetPlayerItemPrice(int subIndex_, EGoodsType goodType_, int &_moneyPrice, int &_goldPrice, int &_count)
{
	if(goodType_ >= E_Goods_end || subIndex_ < 0)
		return false;

	int totalIndex = GetTotalIndexBySubIndex(subIndex_, goodType_);
	if(totalIndex < 0)
		return false;

	_moneyPrice = m_playerSellData[totalIndex].GetGameMoneyPrice();
	_goldPrice = m_playerSellData[totalIndex].GetRMBMoneyPrice();
	if(_moneyPrice < 0 || _goldPrice < 0 )
		return false;

	switch(goodType_)
	{
	case E_Goods_common:
		{
			SCharItem charItem;
			if( !m_playerSellData[totalIndex].GetData( &charItem, sizeof( SCharItem ) ) )
				return false;

			_count = charItem.GetItemCount();
			if(_count <= 0 )
				return false;

			return true;
		}
		break;
	case E_Goods_pet:
		{
			_count = 1;
			return true;
		}
		break;
	case E_Goods_replace:
		{

		}
		break;
	case E_Goods_mount:
		{
			_count = 1;
			return true;
		}
		break;
	case E_Goods_buy:
		{
			_count = m_playerBuyData[totalIndex].GetCount();
			if( _count <= 0 )
				return false;

			return true;
		}
		break;
	default:
		{
			assert(false);
			return false;
		}
	}

	return false;
}

// ��ȡ�Լ���Ʒ�۸���Ϣ
bool CSystemStallage::GetSelfItemPrice( IN int nIndex, IN bool bIsSell, IN bool bIsMount, OUT int& nMoneyPrice, OUT int& nGoldPrice, OUT int& nCount )
{
    int nTotalIndex( -1 );
    SCharItem charItem;
    if( bIsSell && !bIsMount )
    {
        // ���۵���
        nTotalIndex = GetTotalIndexBySubIndex( nIndex, StallDefine::StallSell );
        if( nTotalIndex < 0 )
            return false;

        nCount = m_selfStallData[nTotalIndex].GetCount();
        if( nCount <= 0 )
            return false;

        nMoneyPrice = m_selfStallData[nTotalIndex].GetGameMoneyPrice();
        nGoldPrice = m_selfStallData[nTotalIndex].GetRMBMoneyPrice();
        if( nMoneyPrice < 0 || nGoldPrice < 0 )
            return false;

        return true;
    }
    else if( bIsSell && bIsMount )
    {
        // ��������
        nTotalIndex = GetTotalIndexBySubIndex( nIndex, StallDefine::StallSell, BT_MountBag );
        if( nTotalIndex < 0 )
            return false;

        nCount = m_selfStallData[nTotalIndex].GetCount();
        if( nCount != 1 )
            return false;

        if( m_selfStallData[nTotalIndex].GetBagType() != BT_MountBag )
            return false;

        nMoneyPrice = m_selfStallData[nTotalIndex].GetGameMoneyPrice();
        nGoldPrice = m_selfStallData[nTotalIndex].GetRMBMoneyPrice();
        if( nMoneyPrice < 0 || nGoldPrice < 0 )
            return false;

        return true;
    }
    else if( !bIsSell && !bIsMount )
    {
        // �չ�����
        nTotalIndex = GetTotalIndexBySubIndex( nIndex, StallDefine::StallBuy );
        if( nTotalIndex < 0 )
            return false;

        nCount = m_selfStallData[nTotalIndex].GetCount();
        if( nCount <= 0 )
            return false;

        nMoneyPrice = m_selfStallData[nTotalIndex].GetGameMoneyPrice();
        nGoldPrice = m_selfStallData[nTotalIndex].GetRMBMoneyPrice();
        if( nMoneyPrice < 0 || nGoldPrice < 0 )
            return false;

        return true;
    }

    return false;
}

// ��ȡ̯����Ʒ�۸���Ϣ
bool CSystemStallage::GetPlayerItemPrice( IN int nIndex, IN bool bIsSell, IN bool bIsMount, OUT int& nMoneyPrice, OUT int& nGoldPrice, OUT int& nCount )
{
    int nTotalIndex( -1 );
    SCharItem charItem;
    if( bIsSell && !bIsMount )
    {
        // ���۵���
        nTotalIndex = GetTotalIndexBySubIndex( nIndex, StallDefine::StallSell );
        if( nTotalIndex < 0 )
            return false;

        if( !m_playerSellData[nTotalIndex].GetData( &charItem, sizeof( SCharItem ) ) )
            return false;

        nCount = charItem.GetItemCount();
        if( nCount <= 0 )
            return false;

        nMoneyPrice = m_playerSellData[nTotalIndex].GetGameMoneyPrice();
        nGoldPrice = m_playerSellData[nTotalIndex].GetRMBMoneyPrice();
        if( nMoneyPrice < 0 || nGoldPrice < 0 )
            return false;

        return true;
    }
    else if( bIsSell && bIsMount )
    {
        // ��������
        nTotalIndex = GetTotalIndexBySubIndex( nIndex, StallDefine::StallSell, BT_MountBag );
        if( nTotalIndex < 0 )
            return false;

        SMountItem mountItem;
        if( !m_playerSellData[nTotalIndex].GetData( &mountItem, sizeof( SMountItem ) ) )
            return false;

        if( m_playerSellData[nTotalIndex].GetBagType() != BT_MountBag )
            return false;

        nMoneyPrice = m_playerSellData[nTotalIndex].GetGameMoneyPrice();
        nGoldPrice = m_playerSellData[nTotalIndex].GetRMBMoneyPrice();
        if( nMoneyPrice < 0 || nGoldPrice < 0 )
            return false;

        nCount = 1;
        return true;
    }
    else if( !bIsSell && !bIsMount )
    {
        // �չ�����
        nTotalIndex = GetTotalIndexBySubIndex( nIndex, StallDefine::StallBuy );
        if( nTotalIndex < 0 )
            return false;

        nCount = m_playerBuyData[nTotalIndex].GetCount();
        if( nCount <= 0 )
            return false;

        nMoneyPrice = m_playerBuyData[nTotalIndex].GetGameMoneyPrice();
        nGoldPrice = m_playerBuyData[nTotalIndex].GetRMBMoneyPrice();
        if( nMoneyPrice < 0 || nGoldPrice < 0 )
            return false;

        return true;
    }

    return false;
}

//-----------------------------------����˷�������Ϣ����---------------------------------------
void CSystemStallage::ShowSelfStallageData( const MsgTellTotalStallData* pMsg )
{
    if( !pMsg )
        return;

    // ����ɫ��½���һ�δ򿪣�����������һ��Ĭ��̯λ��
    if( m_bStallageFirstShow )
    {
        m_bStallageFirstShow = false;

        MsgChangeStallTitleReq msg;
        MeSprintf_s( msg.szTitle, sizeof( msg.szTitle ) / sizeof( char ) - 1, theXmlString.GetString( eText_Stallage_Default_Name ), thePlayerRole.GetName() );
        GettheNetworkInput().SendMsg( &msg );
    }

    ClearSelfStallage();

    // ����̯λ���ơ�̯������
    s_CUI_ID_FRAME_PrivateShop.SetVisable( true );
    s_CUI_ID_FRAME_PrivateShop.ClearAll();
    s_CUI_ID_FRAME_PrivateShop.SetTitleName( pMsg->szStallTitle );
    s_CUI_ID_FRAME_PrivateShop.SetPlayerName( thePlayerRole.GetName() );
	
	if(strlen(pMsg->szStallTitle) == 0)
	{
		MsgChangeStallTitleReq msg;
        MeSprintf_s( msg.szTitle, sizeof( msg.szTitle ) / sizeof( char ) - 1, theXmlString.GetString( eText_Stallage_Default_Name ), thePlayerRole.GetName() );
        GettheNetworkInput().SendMsg( &msg );
	}

	    StallConfig::CostSetmeal* nConstSetmealOff = GetStallConfig().GetOfflineCostSetmeal(0);
		StallConfig::CostSetmeal* nConstSetmealOn = GetStallConfig().GetOnlineCostSetmeal(0);
		
		int nTradeCostOff =10; //����˰��
		if (nConstSetmealOff != NULL)	
			nTradeCostOff = nConstSetmealOff->nTradeRevenue;

		int nTradeCostOn = 5;
		if (nConstSetmealOn != NULL)	
			nTradeCostOn = nConstSetmealOn->nTradeRevenue;

	s_CUI_ID_FRAME_PrivateShop.SetTaxPercent( m_bOnlineStall? nTradeCostOn : nTradeCostOff);
    
    // ˢ��̯λ��Ʒ
    int nGoodsCnt = min( pMsg->uchCount, StallDefine::MaxStallCount );
    if( nGoodsCnt <= 0 )
        return;

    for( int i = 0; i < nGoodsCnt; ++i )
    {
        int nTotalIndex = pMsg->xStallData[i].uchStallIndex;
        if( nTotalIndex < 0 || nTotalIndex > StallDefine::MaxStallCount )
            continue;

        // ���±�������
        m_selfStallData[nTotalIndex] = pMsg->xStallData[i].xData;

		/*
        int nGoodsUsage = pMsg->xStallData[i].xData.GetStallType();
        int nGoodsBagType = pMsg->xStallData[i].xData.GetBagType();
        int nGoodsIndex = GetSubIndexByTotalIndex( nTotalIndex, nGoodsUsage, nGoodsBagType );
        if( nGoodsIndex < 0 )
            continue;
		*/

		int subIndex = -1;
		EGoodsType goodType = GetGoodInfo(nTotalIndex, subIndex);
		if(E_Goods_end == goodType || subIndex < 0)
			continue;

        int nItemCnt = pMsg->xStallData[i].xData.GetCount();
        if( nItemCnt <= 0 )
            continue;

        int nMoneyPrice = pMsg->xStallData[i].xData.GetGameMoneyPrice();
        int nGoldPrice = pMsg->xStallData[i].xData.GetRMBMoneyPrice();
        if( nMoneyPrice < 0 || nGoldPrice < 0 )
            continue;

		/*
        // ���ۻ����չ�
        switch( nGoodsUsage )
        {
        case StallDefine::StallSell:
            {
                // ����
                __int64 nItemGuid = pMsg->xStallData[i].xData.GetGuid();
                if( nGoodsBagType == BT_MountBag )
                {
                    // ����
                    if( nItemCnt != 1 )
                        continue;

                    SMountItem* pMount = thePlayerRole.GetMountByGUID( nItemGuid );
                    if( !pMount )
                        continue;

                    SCharItem charItem;
                    charItem.itembaseinfo.ustItemID = pMount->baseInfo.id;
                    charItem.itembaseinfo.nOnlyInt = pMount->baseInfo.guid;

                    s_CUI_ID_FRAME_PrivateShop.SetSellMount( nGoodsIndex, &charItem, nMoneyPrice, nGoldPrice );
                }
                else
                {
                    // ����
                    SCharItem charItem;
                    if( !thePlayerRole.GetBagItemByGUID( nItemGuid, &charItem ) )
                        continue;

                    s_CUI_ID_FRAME_PrivateShop.SetSellGoods( nGoodsIndex, &charItem, nMoneyPrice, nGoldPrice );
                }
            }
            break;
        case StallDefine::StallBuy:
            {
                // �չ�
                int nItemId = pMsg->xStallData[i].xData.GetItemID();
                if( nItemId < 0 )
                    continue;

                s_CUI_ID_FRAME_PrivateShop.SetBuyGoods( nGoodsIndex, nItemId, nItemCnt, nMoneyPrice, nGoldPrice );
            }
            break;
        default:
            {
                continue;
            }
            break;
        }
		*/
		switch(goodType)
		{
		case E_Goods_common:
			{
				__int64 nItemGuid = pMsg->xStallData[i].xData.GetGuid();
				SCharItem charItem;
				if(thePlayerRole.GetBagItemByGUID( nItemGuid, &charItem ) )
					s_CUI_ID_FRAME_PrivateShop.SetSellGoods(subIndex, &charItem, nMoneyPrice, nGoldPrice );
			}
			break;
		case E_Goods_pet:
			{
				__int64 nItemGuid = pMsg->xStallData[i].xData.GetGuid();		
				SPetItem *pItem = thePlayerRole.GetPetByGUID(nItemGuid);
				if(pItem)
					s_CUI_ID_FRAME_PrivateShop.SetSellPet(subIndex, pItem, nMoneyPrice, nGoldPrice );
			}
			break;
		case E_Goods_replace:
			{
				assert(false);
			}
			break;
		case E_Goods_mount:
			{
				__int64 nItemGuid = pMsg->xStallData[i].xData.GetGuid();

				if( nItemCnt != 1 )
					continue;

				SMountItem* pMount = thePlayerRole.GetMountByGUID( nItemGuid );
				if( !pMount )
					continue;

				SCharItem charItem;
				charItem.itembaseinfo.ustItemID = pMount->baseInfo.id;
				charItem.itembaseinfo.nOnlyInt = pMount->baseInfo.guid;

				s_CUI_ID_FRAME_PrivateShop.SetSellMount(subIndex, &charItem, nMoneyPrice, nGoldPrice );
			}
			break;
		case E_Goods_buy:
			{
				int nItemId = pMsg->xStallData[i].xData.GetItemID();
				if( nItemId < 0 )
					continue;

				s_CUI_ID_FRAME_PrivateShop.SetBuyGoods(subIndex, nItemId, nItemCnt, nMoneyPrice, nGoldPrice );
			}
			break;
		default:
			assert(false);
		}
    }

    RefreshCharItemsInStallage();
}

void CSystemStallage::TellSelfStallageUpdate( const MsgUpdateStallData* pMsg )
{
    if( !pMsg )
        return;

    if( pMsg->uchIndex < 0 || pMsg->uchIndex >= StallDefine::MaxStallCount )
        return;

    int nSubIndex( -1 );
/*	
	int nUsage( -1 );
    bool bIsMount( false );
    if( !ClassifyByTotalIndex( pMsg->uchIndex, nSubIndex, nUsage, bIsMount ) )
        return;
*/

	EGoodsType goodType = GetGoodInfo(pMsg->uchIndex, nSubIndex);
	if(E_Goods_end == goodType || nSubIndex < 0)
		return;

    int nItemCnt = pMsg->xData.GetCount();
    __int64 nRenewGuid( 0 );
    //if( nItemCnt == 0 && nUsage == StallDefine::StallSell )
	if(nItemCnt == 0 && goodType < E_Goods_buy)
    {
        nRenewGuid = m_selfStallData[pMsg->uchIndex].GetGuid();
    }

    // ���±�������
    m_selfStallData[pMsg->uchIndex] = pMsg->xData;

    if( nRenewGuid > 0 )
    {
        SetCharItemEnable( nRenewGuid, true );
    }

    if( nItemCnt == 0 )
    {
		/*
        // �Ƴ���Ʒ
        if( nUsage == StallDefine::StallSell && bIsMount )
        {
            s_CUI_ID_FRAME_PrivateShop.RemoveMountSellByIndex( nSubIndex );
        }
        else if( nUsage == StallDefine::StallSell && !bIsMount )
        {
            s_CUI_ID_FRAME_PrivateShop.RemoveGoodsSellByIndex( nSubIndex );
        }
        else if( nUsage == StallDefine::StallBuy && !bIsMount )
        {
            s_CUI_ID_FRAME_PrivateShop.RemoveGoodsBuyByIndex( nSubIndex );
        }
		*/

		switch(goodType)
		{
		case E_Goods_common:
			{
				s_CUI_ID_FRAME_PrivateShop.RemoveGoodsSellByIndex( nSubIndex );
			}
			break;
		case E_Goods_pet:
			{
				s_CUI_ID_FRAME_PrivateShop.RemovePetSellByIndex( nSubIndex );
				if(s_CUI_ID_FRAME_SelectPet.IsVisable())
				{
					s_CUI_ID_FRAME_SelectPet.Refresh();
				}
			}
			break;
		case E_Goods_replace:
			{
				assert(false);
			}
			break;
		case E_Goods_mount:
			{
				s_CUI_ID_FRAME_PrivateShop.RemoveMountSellByIndex( nSubIndex );
			}
			break;
		case E_Goods_buy:
			{
				 s_CUI_ID_FRAME_PrivateShop.RemoveGoodsBuyByIndex( nSubIndex );
			}
			break;
		default:
			assert(false);
		}
    }
    else
    {
        int nMoneyPrice = pMsg->xData.GetGameMoneyPrice();
        int nGoldPrice = pMsg->xData.GetRMBMoneyPrice();
        if( nMoneyPrice < 0 || nGoldPrice < 0 )
            return;

        // ������Ʒ
        __int64 nGuid = pMsg->xData.GetGuid();

		/*
        if( nUsage == StallDefine::StallSell && bIsMount )
        {
            // ����
            SMountItem* pMount = thePlayerRole.GetMountByGUID( nGuid );
            if( !pMount )
                return;

            SCharItem charItem;
            charItem.itembaseinfo.ustItemID = pMount->baseInfo.id;
            charItem.itembaseinfo.nOnlyInt = pMount->baseInfo.guid;

            s_CUI_ID_FRAME_PrivateShop.SetSellMount( nSubIndex, &charItem, nMoneyPrice, nGoldPrice );
        }
        else if( nUsage == StallDefine::StallSell && !bIsMount )
        {
            // ���۵���
            SCharItem charItem;
            if( !thePlayerRole.GetBagItemByGUID( nGuid, &charItem ) )
                return;

            s_CUI_ID_FRAME_PrivateShop.SetSellGoods( nSubIndex, &charItem, nMoneyPrice, nGoldPrice );
        }
        else if( nUsage == StallDefine::StallBuy && !bIsMount )
        {
            // �չ�����
            int nItemId = pMsg->xData.GetItemID();

            if( nItemId < 0 )
                return;

            s_CUI_ID_FRAME_PrivateShop.SetBuyGoods( nSubIndex, nItemId, nItemCnt, nMoneyPrice, nGoldPrice );
        }
		*/

		switch(goodType)
		{
		case E_Goods_common:
			{
				SCharItem charItem;
				if( !thePlayerRole.GetBagItemByGUID( nGuid, &charItem ) )
					return;

				s_CUI_ID_FRAME_PrivateShop.SetSellGoods( nSubIndex, &charItem, nMoneyPrice, nGoldPrice );
			}
			break;
		case E_Goods_pet:
			{
				SPetItem *pItem = thePlayerRole.GetPetByGUID(nGuid);

				if(pItem && IsValidPet(*pItem))
				{
					s_CUI_ID_FRAME_PrivateShop.SetSellPet( nSubIndex, pItem, nMoneyPrice, nGoldPrice );

					if(s_CUI_ID_FRAME_SelectPet.IsVisable())
					{
						s_CUI_ID_FRAME_SelectPet.Refresh();
					}
				}
			}
			break;
		case E_Goods_replace:
			{
				assert(false);
			}
			break;
		case E_Goods_mount:
			{
				SMountItem* pMount = thePlayerRole.GetMountByGUID( nGuid );
				if( !pMount )
					return;

				SCharItem charItem;
				charItem.itembaseinfo.ustItemID = pMount->baseInfo.id;
				charItem.itembaseinfo.nOnlyInt = pMount->baseInfo.guid;

				s_CUI_ID_FRAME_PrivateShop.SetSellMount( nSubIndex, &charItem, nMoneyPrice, nGoldPrice );
			}
			break;
		case E_Goods_buy:
			{
				int nItemId = pMsg->xData.GetItemID();

				if( nItemId < 0 )
					return;

				s_CUI_ID_FRAME_PrivateShop.SetBuyGoods( nSubIndex, nItemId, nItemCnt, nMoneyPrice, nGoldPrice );
			}
			break;
		default:
			assert(false);
		}
    }

    RefreshCharItemsInStallage();
}

void CSystemStallage::TellSelfGoodsPriceChange( int nIndex, int nMoneyPrice, int nGoldPrice )
{
    if( nIndex < 0 || nIndex >= StallDefine::MaxStallCount || nMoneyPrice < 0 || nGoldPrice < 0 )
        return;

    // ���±�������
    m_selfStallData[nIndex].SetGameMoneyPrice( nMoneyPrice );
    m_selfStallData[nIndex].SetRMBMoneyPrice( nGoldPrice );

    if( nMoneyPrice < 0 || nGoldPrice < 0 )
        return;

    int nSubIndex( -1 );

	/*
	int nUsage( -1 );
    bool bIsMount( false );
    if( !ClassifyByTotalIndex( nIndex, nSubIndex, nUsage, bIsMount ) )
        return;

    if( nUsage == StallDefine::StallSell && bIsMount )
    {
        // ����
        s_CUI_ID_FRAME_PrivateShop.SetSellMountPrice( nSubIndex, nMoneyPrice, nGoldPrice );
    }
    else if( nUsage == StallDefine::StallSell && !bIsMount )
    {
        // ���۵���
        s_CUI_ID_FRAME_PrivateShop.SetSellGoodsPrice( nSubIndex, nMoneyPrice, nGoldPrice );
    }
    else if( nUsage == StallDefine::StallBuy && !bIsMount )
    {
        // �չ�����
        s_CUI_ID_FRAME_PrivateShop.SetBuyGoodsPrice( nSubIndex, nMoneyPrice, nGoldPrice );
    }
	*/

	EGoodsType goodType = GetGoodInfo(nIndex, nSubIndex);
	if(goodType >= E_Goods_buy || nSubIndex < 0)
		return;

	switch(goodType)
	{
	case E_Goods_common:
		{
			s_CUI_ID_FRAME_PrivateShop.SetSellGoodsPrice( nSubIndex, nMoneyPrice, nGoldPrice );
		}
		break;
	case E_Goods_pet:
		{
			s_CUI_ID_FRAME_PrivateShop.SetSellPetPrice( nSubIndex, nMoneyPrice, nGoldPrice );
		}
		break;
	case E_Goods_replace:
		{

		}
		break;
	case E_Goods_mount:
		{
			 s_CUI_ID_FRAME_PrivateShop.SetSellMountPrice( nSubIndex, nMoneyPrice, nGoldPrice );
		}
		break;
	case E_Goods_buy:
		{
			s_CUI_ID_FRAME_PrivateShop.SetBuyGoodsPrice( nSubIndex, nMoneyPrice, nGoldPrice );
		}
		break;
	default:
		assert(false);

	}

}

// ̯����̯λ����
void CSystemStallage::TellPlayerStallageData( MsgShowStallData* pMsg )
{
    if( !pMsg )
        return;

    if( !CheckPlayerExist( m_nVenderPlayerId ) )
        return;

    CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID( m_nVenderPlayerId );
    
    ClearPlayerStallage();
	s_CUI_ID_FRAME_PlayerPrivateShop.m_IsOnlineStall = !pMsg->IsOffLineStall;
    s_CUI_ID_FRAME_PlayerPrivateShop.SetVisable( true );
    s_CUI_ID_FRAME_PlayerPrivateShop.ClearAll();
    s_CUI_ID_FRAME_PlayerPrivateShop.SetTitleName( pPlayer->GetShopName().c_str() );
    s_CUI_ID_FRAME_PlayerPrivateShop.SetPlayerName( pPlayer->GetName() );

	StallConfig::CostSetmeal* nConstSetmealOff = GetStallConfig().GetOfflineCostSetmeal(0);
	StallConfig::CostSetmeal* nConstSetmealOn = GetStallConfig().GetOnlineCostSetmeal(0);

	int nTradeCostOff =10; //����˰��
	if (nConstSetmealOff != NULL)	
		nTradeCostOff = nConstSetmealOff->nTradeRevenue;

	int nTradeCostOn = 5;
	if (nConstSetmealOn != NULL)	
		nTradeCostOn = nConstSetmealOn->nTradeRevenue;

    //lyh�޸� ��̯˰��
    s_CUI_ID_FRAME_PlayerPrivateShop.SetTaxPercent( pMsg->IsOffLineStall? nTradeCostOff : nTradeCostOn );

    // ˢ��̯λ��Ʒ
    int nSubIndex( -1 ), nUsage( -1 );
    bool bIsMount( false );
    int nBuyCount = min( pMsg->uchBuyDataCount, StallDefine::MaxBuyCount );
    int nSellCount = min( pMsg->uchSellDataCount, StallDefine::MaxSellCount );

    // �չ�
    for( int i = 0; i < nBuyCount; ++i )
    {
        int nTotalIndex = pMsg->xBuyData[i].GetIndex();
        if( nTotalIndex < m_nItemBuyIndexBegin || nTotalIndex >= StallDefine::MaxStallCount )
            continue;

        // ���±�������
        memcpy_s( &m_playerBuyData[nTotalIndex], sizeof( BuyDataToClient ), &pMsg->xBuyData[i], sizeof( BuyDataToClient ) );

		/*
        if( !ClassifyByTotalIndex( nTotalIndex, nSubIndex, nUsage, bIsMount ) )
            continue;
        if( nUsage != StallDefine::StallBuy || bIsMount || nSubIndex < 0 )
            continue;
		*/

		if(GetGoodInfo(nTotalIndex, nSubIndex) != E_Goods_buy)
			continue;

        int nItemCnt = pMsg->xBuyData[i].GetCount();
        if( nItemCnt <= 0 )
            continue;
        int nItemId = pMsg->xBuyData[i].GetItemID();
        if( nItemId < 0 )
            continue;

        int nMoneyPrice = pMsg->xBuyData[i].GetGameMoneyPrice();
        int nGoldPrice = pMsg->xBuyData[i].GetRMBMoneyPrice();
        if( nMoneyPrice < 0 || nGoldPrice < 0 )
            continue;

        s_CUI_ID_FRAME_PlayerPrivateShop.SetBuyGoods( nSubIndex, nItemId, nItemCnt, nMoneyPrice, nGoldPrice );
    }

    // ����
    for( int i = 0; i < nSellCount; ++i )
    {
        int nTotalIndex = pMsg->xSellData[i].GetIndex();
        if( nTotalIndex < m_nItemSellIndexBegin || nTotalIndex >= m_nItemBuyIndexBegin )
            continue;

        // ���±�������
        memcpy_s( &m_playerSellData[nTotalIndex], sizeof( SellDataToClient ), &pMsg->xSellData[i], sizeof( SellDataToClient ) );

		/*
        if( !ClassifyByTotalIndex( nTotalIndex, nSubIndex, nUsage, bIsMount ) )
            continue;
        if( nSubIndex < 0 )
            continue;
		*/
		
		EGoodsType goodType = GetGoodInfo(nTotalIndex, nSubIndex);
		if(goodType >= E_Goods_buy)
			continue;
		if(nSubIndex < 0)
			continue;
        
        int nMoneyPrice = pMsg->xSellData[i].GetGameMoneyPrice();
        int nGoldPrice = pMsg->xSellData[i].GetRMBMoneyPrice();
        if( nMoneyPrice < 0 || nGoldPrice < 0 )
            continue;

		/*
        if( nUsage == StallDefine::StallSell && !bIsMount )
        {
            // ����
            SCharItem charItem;
            memset( &charItem, 0, sizeof( SCharItem ) );
            if( !pMsg->xSellData[i].GetData( &charItem, sizeof( SCharItem ) ) )
                continue;

            s_CUI_ID_FRAME_PlayerPrivateShop.SetSellGoods( nSubIndex, &charItem, nMoneyPrice, nGoldPrice );
        }
        else if( nUsage == StallDefine::StallSell && bIsMount )
        {
            // ����
            SMountItem mountItem;
            memset( &mountItem, 0, sizeof( SMountItem ) );
            if( !pMsg->xSellData[i].GetData( &mountItem, sizeof( SMountItem ) ) )
                continue;

            SCharItem charItem;
            charItem.itembaseinfo.ustItemID = mountItem.baseInfo.id;
            charItem.itembaseinfo.nOnlyInt = mountItem.baseInfo.guid;

            s_CUI_ID_FRAME_PlayerPrivateShop.SetSellMount( nSubIndex, &charItem, nMoneyPrice, nGoldPrice  );
        }
		*/

		switch(goodType)
		{
		case E_Goods_common:
			{
				// ����
				SCharItem charItem;
				memset( &charItem, 0, sizeof( SCharItem ) );
				if( !pMsg->xSellData[i].GetData( &charItem, sizeof( SCharItem ) ) )
					continue;

				s_CUI_ID_FRAME_PlayerPrivateShop.SetSellGoods( nSubIndex, &charItem, nMoneyPrice, nGoldPrice );
			}
			break;
		case E_Goods_pet:
			{
				//����ി��ֻ��Ϊ�˵���m_szData.
				class MySellDataToClient: public SellDataToClient
				{
				public:
					char *GetData(void)
					{
						return m_szData;
					}
				};

				MySellDataToClient *pData = (MySellDataToClient *)(pMsg->xSellData + i);
				SPetItem *pItem = (SPetItem *)pData->GetData();
				assert(pItem != NULL);
				
				if(pItem != NULL)
					s_CUI_ID_FRAME_PlayerPrivateShop.SetSellPet(nSubIndex, pItem, nMoneyPrice, nGoldPrice );
			}
			break;
		case E_Goods_replace:
			{

			}
			break;
		case E_Goods_mount:
			{
				// ����
				SMountItem mountItem;
				memset( &mountItem, 0, sizeof( SMountItem ) );
				if( !pMsg->xSellData[i].GetData( &mountItem, sizeof( SMountItem ) ) )
					continue;

				SCharItem charItem;
				charItem.itembaseinfo.ustItemID = mountItem.baseInfo.id;
				charItem.itembaseinfo.nOnlyInt = mountItem.baseInfo.guid;

				s_CUI_ID_FRAME_PlayerPrivateShop.SetSellMount( nSubIndex, &charItem, nMoneyPrice, nGoldPrice  );
			}
			break;
		default:
			assert(false);

		}
    }
}

// ̯����̯λ����Ʒ�����ı�
void CSystemStallage::TellPlayerStallageCountChange( int nTotalIndex, int nItemCnt )
{
/*
    int nSubIndex( -1 ), nUsage( -1 );
    bool bIsMount( false );
    if( !ClassifyByTotalIndex( nTotalIndex, nSubIndex, nUsage, bIsMount ) )
        return;

    if( nSubIndex < 0 )
        return;

    if( nUsage == StallDefine::StallSell && !bIsMount && nItemCnt > 0 )
    {
        SCharItem charItem;
        if( !m_playerSellData[nTotalIndex].GetData( &charItem, sizeof( SCharItem ) ) )
            return;
        charItem.SetItemCount( nItemCnt );
        if( !m_playerSellData[nTotalIndex].SetData( &charItem, sizeof( SCharItem ) ) )
            return;

        int nMoneyPrice = m_playerSellData[nTotalIndex].GetGameMoneyPrice();
        int nGoldPrice = m_playerSellData[nTotalIndex].GetRMBMoneyPrice();
        if( nMoneyPrice < 0 || nGoldPrice < 0 )
            return;

        s_CUI_ID_FRAME_PlayerPrivateShop.SetGoodsSellCnt( nSubIndex, nItemCnt, nMoneyPrice, nGoldPrice );
    }
    else if( nUsage == StallDefine::StallSell && !bIsMount && nItemCnt == 0 )
    {
        memset( &m_playerSellData[nTotalIndex], 0, sizeof( SellDataToClient ) );
        s_CUI_ID_FRAME_PlayerPrivateShop.RemoveGoodsSellByIndex( nSubIndex );
    }
    else if( nUsage == StallDefine::StallSell && bIsMount && nItemCnt == 0 )
    {
        memset( &m_playerSellData[nTotalIndex], 0, sizeof( SellDataToClient ) );
        s_CUI_ID_FRAME_PlayerPrivateShop.RemoveMountSellByIndex( nSubIndex );
    }
    else if( nUsage == StallDefine::StallBuy && !bIsMount && nItemCnt > 0 )
    {
        m_playerBuyData[nTotalIndex].SetCount( nItemCnt );

        int nMoneyPrice = m_playerBuyData[nTotalIndex].GetGameMoneyPrice();
        int nGoldPrice = m_playerBuyData[nTotalIndex].GetRMBMoneyPrice();
        if( nMoneyPrice < 0 || nGoldPrice < 0 )
            return;

        s_CUI_ID_FRAME_PlayerPrivateShop.SetGoodsBuyCnt( nSubIndex, nItemCnt, nMoneyPrice, nGoldPrice );
    }
    else if( nUsage == StallDefine::StallBuy && !bIsMount && nItemCnt == 0 )
    {
        memset( &m_playerBuyData[nTotalIndex], 0, sizeof( BuyDataToClient ) );
        s_CUI_ID_FRAME_PlayerPrivateShop.RemoveGoodsBuyByIndex( nSubIndex );
    }
*/

	int nSubIndex = -1;
	EGoodsType goodType = GetGoodInfo(nTotalIndex, nSubIndex);
	if(E_Goods_end == goodType || nSubIndex < 0)
		return;

	switch(goodType)
	{
	case E_Goods_common:
		{
			if(nItemCnt > 0)
			{
				SCharItem charItem;
				if( !m_playerSellData[nTotalIndex].GetData( &charItem, sizeof( SCharItem ) ) )
					return;
				charItem.SetItemCount( nItemCnt );
				if( !m_playerSellData[nTotalIndex].SetData( &charItem, sizeof( SCharItem ) ) )
					return;

				int nMoneyPrice = m_playerSellData[nTotalIndex].GetGameMoneyPrice();
				int nGoldPrice = m_playerSellData[nTotalIndex].GetRMBMoneyPrice();
				if( nMoneyPrice < 0 || nGoldPrice < 0 )
					return;

				s_CUI_ID_FRAME_PlayerPrivateShop.SetGoodsSellCnt( nSubIndex, nItemCnt, nMoneyPrice, nGoldPrice );
			}
			else
			{
				memset( &m_playerSellData[nTotalIndex], 0, sizeof( SellDataToClient ) );
				s_CUI_ID_FRAME_PlayerPrivateShop.RemoveGoodsSellByIndex( nSubIndex );
			}
		}
		break;
	case E_Goods_pet:
		{
			if(0 == nItemCnt)
			{
				memset( &m_playerSellData[nTotalIndex], 0, sizeof( SellDataToClient ) );
				s_CUI_ID_FRAME_PlayerPrivateShop.RemovePetSellByIndex( nSubIndex );
			}
		}
		break;
	case E_Goods_replace:
		{
			assert(false);
		}
		break;
	case E_Goods_mount:
		{
			if(0 == nItemCnt)
			{
				memset( &m_playerSellData[nTotalIndex], 0, sizeof( SellDataToClient ) );
				s_CUI_ID_FRAME_PlayerPrivateShop.RemoveMountSellByIndex( nSubIndex );
			}
		}
		break;
	case E_Goods_buy:
		{
			if(nItemCnt > 0)
			{
				m_playerBuyData[nTotalIndex].SetCount( nItemCnt );

				int nMoneyPrice = m_playerBuyData[nTotalIndex].GetGameMoneyPrice();
				int nGoldPrice = m_playerBuyData[nTotalIndex].GetRMBMoneyPrice();
				if( nMoneyPrice < 0 || nGoldPrice < 0 )
					return;

				s_CUI_ID_FRAME_PlayerPrivateShop.SetGoodsBuyCnt( nSubIndex, nItemCnt, nMoneyPrice, nGoldPrice );
			}
			else
			{
				memset( &m_playerBuyData[nTotalIndex], 0, sizeof( BuyDataToClient ) );
				s_CUI_ID_FRAME_PlayerPrivateShop.RemoveGoodsBuyByIndex( nSubIndex );
			}
		}
		break;
	default:
		assert(false);

	}
	

	
}

void CSystemStallage::TellPlayerStartStall( int nPlayerId, int nModelId, const char* pTitle, bool bIsOffline_)
{
// 	if(!bIsOffline_)
// 	{
		// ĳ��ҿ�ʼ��̯
		if( !CheckPlayerExist( nPlayerId ) || !CheckMeExist() )
			return;

		CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID( nPlayerId );
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	    
		// ������Լ�����ս��׼�¼,���½���
		if( pPlayer->GetID() == pMe->GetID() )
		{
			pMe->m_isOfflineStall = bIsOffline_;
			m_tradeRecordVec.clear();
			s_CUI_ID_FRAME_PrivateShop.SetStallStart( true );
			PlaySoundConfig( SoundConfig::EST_StartStall );
		}

		pPlayer->SetPrivateInfo( true, pTitle );
		pPlayer->MorphMonster( nModelId, true );
// 	}
// 	else
// 	{
// 
// 	}
}

void CSystemStallage::TellPlayerCloseStallage( int nPlayerId )
{
    // ĳ��ҹر�̯λ
    if( !CheckPlayerExist( nPlayerId ) || !CheckMeExist() )
        return;

    CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID( nPlayerId );
    CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();

    // ������Լ�����½���
    if( pPlayer->GetID() == pMe->GetID() )
    {
        s_CUI_ID_FRAME_PrivateShop.SetStallStart( false );
    }

    // ����Լ����鿴�����̯λ����ر�
    if( GetVenderId() == nPlayerId && s_CUI_ID_FRAME_PlayerPrivateShop.IsVisable() )
    {
        s_CUI_ID_FRAME_PlayerPrivateShop.SetVisable( false );
        char szTmp[MAX_PATH] = {0};
        MeSprintf_s( szTmp, sizeof( szTmp ) / sizeof( char ) - 1, theXmlString.GetString( eTextPlayer_CloseShop ), pPlayer->GetName() );
        s_CUI_ID_FRAME_MessageBox.Show( szTmp, "", CUI_ID_FRAME_MessageBox::eTypeConfirm, false );
    }

    pPlayer->SetPrivateInfo( false, "" );
    pPlayer->MorphMonster( -1 );

	 if( pPlayer->GetID() == pMe->GetID() )
	 {
CSystemStallage::Instance()->RefreshCharItemsInStallage();

	 }
}

void CSystemStallage::TellPlayerTitleChange( int nPlayerId, const char* pTitle )
{
    // �ͻ��˲������̯�����и�����ֻ�����Լ���
    if( !CheckPlayerExist( nPlayerId ) || !CheckMeExist() )
        return;

    CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID( nPlayerId );
    CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();

    if( pPlayer->GetID() == pMe->GetID() )
    {
        s_CUI_ID_FRAME_PrivateShop.SetTitleName( pTitle );
    }
}

void CSystemStallage::AddSelfTradeRecord( MsgTellBuyOrSellStallData* pMsg )
{
    if( !pMsg )
        return;

    // ���׼�¼     Ŀǰ��̯û�н�    nRmbMoney �ݲ�����
    char szRecord[MAX_PATH] = {0};
    std::string strTmp;
    thePlayerRole.GetGSCStringFromMoney( pMsg->nGameMoney, strTmp );
    
    if( pMsg->uchStallType == StallDefine::StallSell )
    {
        MeSprintf_s( szRecord, sizeof( szRecord ) / sizeof( char ) - 1, theXmlString.GetString( eText_Stall_TradeRecord_Sell ),
            pMsg->szPlayer, ( int )pMsg->uchCount, pMsg->szItemName, strTmp.c_str() );
    }
    else if( pMsg->uchStallType == StallDefine::StallBuy )
    {
        MeSprintf_s( szRecord, sizeof( szRecord ) / sizeof( char ) - 1, theXmlString.GetString( eText_Stall_TradeRecord_Buy ),
            pMsg->szPlayer, ( int )pMsg->uchCount, pMsg->szItemName, strTmp.c_str() );
    }
    else
    {
        return;
    }
    

	time_t now;	
	struct tm *fmt;	
	time(&now);	
	fmt = localtime(&now);	
    
	char szTime[MAX_PATH] = {0};
	sprintf(szTime,"%d:%d:%d",fmt->tm_hour,fmt->tm_min,fmt->tm_sec);
     m_tradeRecordVec.push_back( szTime );

    strTmp = szRecord;
    m_tradeRecordVec.push_back( strTmp );
    s_CUI_ID_FRAME_TradeRecord.Refresh();
}

// ���һ��������Ʒ����
void CSystemStallage::TellAddSellResult( int nResult )
{
    switch( nResult )
    {
        // �����̯λ����
    case MsgAddSellDataAck::ECD_ErrorStallIndex:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_AddItemError ) );
        }
        break;
        // ����ı�������
    case MsgAddSellDataAck::ECD_ErrorBagType:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_AddItemError ) );
        }
        break;
        // ����ĵ���
    case MsgAddSellDataAck::ECD_ErrorItem:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_AddItemError ) );
        }
        break;
        // ���������
    case MsgAddSellDataAck::ECD_ErrorCount:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_ItemNumError ) );
        }
        break;
        // ����, ��, ��������Ʒ���ܰ�̯����
    case MsgAddSellDataAck::ECD_BoundItem:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_ItemError ) );
        }
        break;
        // ̯λ��λ���е��߳���, �������
    case MsgAddSellDataAck::ECD_AlreadyHaveData:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_SlotAlready ) );
        }
        break;
        // �˵����Ѿ�����ӵ�̯λ��
    case MsgAddSellDataAck::ECD_AlreadySellItem:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_DataAlready ) );
        }
        break;
    default:
        break;
    }
}

// ���һ���ع���Ʒ����
void CSystemStallage::TellAddBuyResult( int nResult )
{
    switch( nResult )
    {
        // �����̯λ����
    case MsgAddBuyDataAck::ECD_ErrorStallIndex:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_AddItemError ) );
        }
        break;
        // ����ı�������
    case MsgAddBuyDataAck::ECD_ErrorBagType:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_AddItemError ) );
        }
        break;
        // ����ĵ���ID
    case MsgAddBuyDataAck::ECD_ErrorItem:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_AddItemError ) );
        }
        break;
        // ̯λ��λ���е��߳���, �������
    case MsgAddBuyDataAck::ECD_AlreadyHaveData:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_SlotAlready ) );
        }
        break;
    default:
        break;
    }
}

// ��̯�������
void CSystemStallage::TellQuestStallResult( int nResult )
{
    switch( nResult )
    {
    case MsgStartStallAck::ECD_Success:
        {
            
        }
        break;
        // ��ģʽ���ܰ�̯
    case MsgStartStallAck::ECD_PKModeCritical:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_PKMode_FuryNoShop ) );
        }
        break;
        // ӵ�б���״̬���ܰ�̯
    case MsgStartStallAck::ECD_ChangeMosterBuffer:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eExChange_NoPermitInMorp ) );
        }
        break;
        // �Ʋ�����ʱ���ڲ��ܰ�̯
    case MsgStartStallAck::ECD_InProtectLockTime:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_WealthProtect ) );
        }
        break;
        // ���ڽ��ײ��ܰ�̯
    case MsgStartStallAck::ECD_IsBargainingNow:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_InBargaining ) );
        }
        break;
        // С�ڰ�̯�ȼ�
    case MsgStartStallAck::ECD_LessPrivateShopLevel:
        {
            char szBuff[MAX_PATH];
            MeSprintf_s( szBuff, sizeof( szBuff ) / sizeof( char ) - 1, theXmlString.GetString( eText_PrivateShop_LevelLimit ),
                gCfg.m_ucPrivateShopLevelLimit ) ;
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, szBuff );
        }
        break;
        // Я����Ǯ��������
    case MsgStartStallAck::ECD_SelfMaxMoneyLimit:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_TooMouchMoney ) );
        }
        break;
        // ���ܿ���һ����̯λ
    case MsgStartStallAck::ECD_EmptyStall:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_EmptyStallage ) );
        }
        break;
        // ����״̬�²��ܰ�̯
    case MsgStartStallAck::ECD_OnRide:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_NoRide ) );
        }
        break;
        // ������̵����
    case MsgStartStallAck::ECD_ErrorStallTitle:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_NameError ) );
        }
        break;
        // ս��״̬���ܰ�̯
    case MsgStartStallAck::ECD_InFighting:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_InBattle ) );
        }
        break;
        // û���㹻�Ľ�Ǯ�չ�̯λ�ϵ���Ʒ
    case MsgStartStallAck::ECD_NotEnoughMoneyBuy:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_VenderMoneyLess ) );
        }
        break;
        // û���㹻�İ����ռ��չ����е���Ʒ
    case MsgStartStallAck::ECD_NotEnoughEmptyBagCount:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_VenderPackNoPlace ) );
        }
        break;
		//û���ڰ�̯����
	case MsgStartStallAck::ECD_NotInStallZone:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString(eText_NotInStallArea) );
		}
		break;
	case MsgStartStallAck::ECD_LackOfStallFee:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString(eText_Stall_No_Item) );
		}
		break;
	case MsgStartStallAck::ECD_StallDistance:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString(eText_Stall_Too_Near) );
		}
		break;
    default:
        break;
    }
}

void CSystemStallage::TellErrorsInStall( int nErrorType )
{
    switch( nErrorType )
    {
        // ̯���Ѿ���������
    case MsgBuyOrSellStallAck::ECD_PlayerOutLine:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_Offline ) );
        }
        break;
        // �Ѿ����ڰ�̯��
    case MsgBuyOrSellStallAck::ECD_StallNotStart:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_StallageClose ) );
        }
        break;
        // ̯λ���ݲ���ȷ, ��ˢ��̯λ
    case MsgBuyOrSellStallAck::ECD_StallDataError:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_StallageError ) );
        }
        break;
        // ����Ʒ����,�����Ѿ�������, ���ܹ���
    case MsgBuyOrSellStallAck::ECD_StallItemError:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_ItemError ) );
        }
        break;
        // û���㹻����Ϸ��
    case MsgBuyOrSellStallAck::ECD_NotEnoughMoney:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_BargainFailed_NoMoney ) );
        }
        break;
        // û���㹻�Ľ�
    case MsgBuyOrSellStallAck::ECD_NotEnoughRMB:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_BargainFailed_NoGold ) );
        }
        break;
        // ̯λ��Ǯ�Ѿ�������
    case MsgBuyOrSellStallAck::ECD_StallPriceError:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_PriceChange ) );
        }
        break;
        // ��������, ���ܹ���
    case MsgBuyOrSellStallAck::ECD_ItemPackFull:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eWarning_BagFull ) );
        }
        break;
        // ���ﱳ������, ���ܹ���
    case MsgBuyOrSellStallAck::ECD_MountPackFull:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_BargainFailed_HouseFull ) );
        }
        break;
        // ̯λ��������ȷ
    case MsgBuyOrSellStallAck::ECD_StallCountError:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_ItemNumError ) );
        }
        break;
        // ̯��û���㹻����Ϸ�ҽ�Ǯ�չ���
    case MsgBuyOrSellStallAck::ECD_StallerNotMoney:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_VenderNoMoney ) );
        }
        break;
        // ̯��û���㹻�Ľ��չ���
    case MsgBuyOrSellStallAck::ECD_StallerNotRMB:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_VenderNoGold ) );
        }
        break;
        // ���۸�̯λ����Ʒ���ݲ���ȷ
    case MsgBuyOrSellStallAck::ECD_SellErrorItem:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_ItemNumError ) );
        }
        break;
        // ̯����������
    case MsgBuyOrSellStallAck::ECD_StallerPackFull:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_VenderPackFull ) );
        }
        break;
        // ���� or �� or ��������Ʒ���ܳ���
    case MsgBuyOrSellStallAck::ECD_SellItemBound:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_ItemError ) );
        }
        break;
        // ��ս�����ܳ���
    case MsgBuyOrSellStallAck::ECD_SellMountActive:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_BargainFailed_HouseBattle ) );
        }
        break;
        // ̯��������������, �����չ�
    case MsgBuyOrSellStallAck::ECD_StallerMountFull:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_VenderHouseFull ) );
        }
        break;
        // ������æ, ���Ժ�.( ��Ҫ����Ϊ��ֹ˫�����ڵȴ����ݿ����ʱ, ���ˢ������bug )
    case MsgBuyOrSellStallAck::ECD_SystemBusy:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eError_ServerBusy ) );
        }
        break;
    default:
        break;
    }
}

//-----------------------------------�û�UI�����������---------------------------------------
// �򿪰�̯���棬����ͬ��̯λ����
void CSystemStallage::OpenStallageWindow()
{
    // ��ȫ������������Բ������׶�
    if( CWealthProtect::Instance().IsInProtectTime() || CPreventWallow::Instance().IsFCMNotHealthy() )
    {
        return;
    }

    // �ȼ��ж�
    if( thePlayerRole.GetLevel() < gCfg.m_ucPrivateShopLevelLimit )
    {
        char szBuff[MAX_PATH] = {0};
        MeSprintf_s( szBuff, sizeof( szBuff ) / sizeof( char ) - 1, theXmlString.GetString( eText_PrivateShop_LevelLimit ), gCfg.m_ucPrivateShopLevelLimit ) ;
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, szBuff );
        return;
    }

    // ����ʱ�޷���̯
    if( s_CUI_ID_FRAME_Bargaining.IsVisable() )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_InBargaining ) );
        return;
    }
    
    // ���ʹ򿪰�̯������Ϣ��ͬ������������
    MsgStartStallReq msg;
    msg.uchOpenType = MsgStartStallReq::TypeOpenWindow;
    GettheNetworkInput().SendMsg( &msg );
}

bool WillOpenOffLineStall(const char bPressYesButton, void *pData)
{
	if(bPressYesButton)
	{
		CSystemStallage::Instance()->SendOpenStallMsg(false);
	}

	return true;
}
bool WillOpenOnLineStall(const char nYes,void *pdata)
{
	if (nYes)
	{
		CSystemStallage::Instance()->SendOpenStallMsg(nYes);
	}
	return true;
}
/*-----------------------------------------------------------
In	: bOnline_, true, ������̯�� false, ���߰�̯��
-----------------------------------------------------------*/
void OpenMyStallageWindow(bool bOnline_)
{
	if(!bOnline_)//���߰�̯
	{	//Ŀǰֻ��һ�����ͣ�����ֱ��ȡ����ĵ�һ��Ԫ�ء��������������Ҫ��Ϊ���� GetOfflineCostSetmealByID()����ȡֵ
		StallConfig::CostSetmeal* nConstSetmeal = GetStallConfig().GetOfflineCostSetmeal(0);
		int nStallCost = 0;
		int nTradeCost =0;
		if (nConstSetmeal != NULL)
		{
			nStallCost= nConstSetmeal->nStallRevenue;
			nTradeCost = nConstSetmeal->nTradeRevenue;
		}
		char temp[128] = {0};
		std::string str;
		std::string str_money;
		thePlayerRole.GetGSCStringFromJiaoZi(nStallCost,str_money);
		if (!thePlayerRole.HaveEnoughMoney(nStallCost))
		{
			CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Shop_Private,theXmlString.GetString(eText_NotEnoughMoneyForOffline));
			return;
		}
		//str += theXmlString.GetString(eText_NormalTextStall);
		//str +="\n";
		MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eText_Stall_Rent),str_money.c_str());
		str += temp;

		memset(temp,0,sizeof(temp));
		MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eText_Stall_Tax),nTradeCost);
		str += temp;

		const char *pOther = theXmlString.GetString(eText_Stall_YesNo);
		if(pOther != NULL)\
		{
			str += pOther;
		}
		//str +="\n";
		//str += theXmlString.GetString(eText_NoticeForStall);
		s_CUI_ID_FRAME_MessageBox.Show(str.c_str(), theXmlString.GetString(eText_Stall_YesNo), 
			CUI_ID_FRAME_MessageBox::eTypeYesNo, false, WillOpenOffLineStall);

		return;
	}
	else //���߰�̯
	{
		//Ŀǰֻ��һ�����ͣ�����ֱ��ȡ����ĵ�һ��Ԫ�ء��������������Ҫ��Ϊ���� GetOnlineCostSetmealByID()����ȡֵ
		StallConfig::CostSetmeal* nConstSetmeal = GetStallConfig().GetOnlineCostSetmeal(0);
		int nStallCost = 0;
		int nTradeCost =0;
		if (nConstSetmeal != NULL)
		{
			nStallCost= nConstSetmeal->nStallRevenue;
			nTradeCost = nConstSetmeal->nTradeRevenue;
		}
		char temp[128] = {0};
		std::string str;
		std::string str_money;
		thePlayerRole.GetGSCStringFromJiaoZi(nStallCost,str_money);
		if (!thePlayerRole.HaveEnoughMoney(nStallCost))
		{
			CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Shop_Private,theXmlString.GetString(eText_NotEnoughMoneyFonOnline));
			return;
		}
		//str += theXmlString.GetString(eText_NormalTextStall);
		//str +="\n";
		MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eText_Stall_Rent),str_money.c_str());
		str += temp;

		memset(temp,0,sizeof(temp));
		MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eText_Stall_Tax),nTradeCost);
		str += temp;

		const char *pOther = theXmlString.GetString(eText_Stall_YesNo);
		if(pOther != NULL)
		{
			str += pOther;
		}
		//str +="\n";
		//	str += theXmlString.GetString(eText_NoticeForStall);
		s_CUI_ID_FRAME_MessageBox.Show(str.c_str(), theXmlString.GetString(eText_Stall_YesNo), 
			CUI_ID_FRAME_MessageBox::eTypeYesNo, false, WillOpenOnLineStall);
	}
	
}
void CSystemStallage::OpenStallageWindow2(void)
{
	if(IsSelfInStalling())
	{
		//s_CUI_ID_FRAME_PrivateShop.SetVisable(true);
		OpenStallageWindow();
		return;
	}

	// 	if( CWealthProtect::Instance().IsInProtectTime())
	// 	{
	// 		return;
	// 	}

	// ��ȫ������������Բ������׶�
	if( CWealthProtect::Instance().IsInProtectTime() || CPreventWallow::Instance().IsFCMNotHealthy() )
	{
		return;
	}

	// ����ʱ���ܰ�̯
	if (theHeroGame.GetPlayerMgr()->GetMe()->IsDueling())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_InDueling ) );
		return;
	}

	// �ȼ��ж�
	if( thePlayerRole.GetLevel() < gCfg.m_ucPrivateShopLevelLimit )
	{
		char szBuff[MAX_PATH] = {0};
		MeSprintf_s( szBuff, sizeof( szBuff ) / sizeof( char ) - 1, theXmlString.GetString( eText_PrivateShop_LevelLimit ), gCfg.m_ucPrivateShopLevelLimit ) ;
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, szBuff );
		return;
	}

	// ����ʱ�޷���̯
	if( s_CUI_ID_FRAME_Bargaining.IsVisable() )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_InBargaining ) );
		return;
	}
	//���ذ�̯���ʱ�
	/*char strName[256] = {0};
	MeSprintf_s( strName, sizeof(strName)/sizeof(char) -1, "%s\\Data\\Config\\Stall.config", GetRootPath());
	GetStallConfig().LoadStallConfig(strName);*/
	s_CUI_ID_FRAME_ChooseShopType.Show(OpenMyStallageWindow);

}

void CSystemStallage::SendOpenStallMsg(bool bOnline_)
{
	MsgStartStallReq msg;
	msg.uchOpenType = MsgStartStallReq::TypeOpenWindow;
	GettheNetworkInput().SendMsg( &msg );

	m_bOnlineStall = bOnline_;
	s_CUI_ID_FRAME_PrivateShop.m_BisOnlineShop = bOnline_;
}

// �ӱ�����̯λ��Ʒ���ƶ�
void CSystemStallage::MoveFromPackToGoodsSell( int nDestIndex, int nSrcIndex, int nBagType )
{
    // ��̯��
    if( IsSelfInStalling() )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private,
            theXmlString.GetString( eText_StallFailed_NoItemMoveWhenOpen ) );
        return;
    }

    nDestIndex += m_nItemSellIndexBegin;
    if( nDestIndex < m_nItemSellIndexBegin || nDestIndex >= m_nMountSellIndexBegin )
        return;
    if( nBagType != BT_NormalItemBag && nBagType != BT_MaterialBag )
        return;

    // �ӱ��������л�ȡ��Ʒ��Ϣ
    CItemBag2* pBag = NULL;
    if( nBagType == BT_NormalItemBag )
    {
        pBag = &thePlayerRole.m_bag;		
    }
    else
    {
        pBag = &thePlayerRole.m_bagMaterial;
    }

    SCharItem charItem;
    if( !pBag->GetItem( nSrcIndex, &charItem ) )
        return;

    // ��Ʒ�Ѿ�����
    if( charItem.storageinfo.bIsLocked )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_ItemHaveBeenLocked ) );
        return;
    }
    if( charItem.IsLock() )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_ItemLockShop ) );
        return;
    }

    // ��Ʒ�Ѱ�
    if( charItem.IsBounded() )
    {
        CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eUI_SoulBoundedCanotDo ));
        return;
    }
    if( nSrcIndex >= pBag->GetNowBagSize() )
        return;
    ItemDefine::SItemCommon *pItem = GettheItemDetail().GetItemByID( charItem.GetItemID() );
    if ( !pItem )
        return;

    // �ܷ���
    if( !pItem->bIsCanTrade )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eClient_AddInfo_2slk_31 ) );
        return;
    }

    StallageItem stallItem;
    stallItem.m_nBagType = nBagType;
    stallItem.m_nSrcIndex = nSrcIndex;
    stallItem.m_nDestIndex = nDestIndex;
    stallItem.m_nCount = charItem.GetItemCount();
    stallItem.m_nGuid = charItem.GetItemGuid();

    s_CUI_ID_FRAME_EditPrice.Show( AddItemToStallageSell, &stallItem, sizeof( stallItem ), stallItem.m_nCount );
}

void CSystemStallage::AddPetToSell(SPetItem &pet, int srcIndex_, int destIndex_)
{
	// ��̯��
	if( IsSelfInStalling() )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private,
			theXmlString.GetString( eText_StallFailed_NoItemMoveWhenOpen ) );
		return;
	}

	destIndex_ += m_goodsIndex[E_Goods_pet];
	if(!CheckGoodIndex(destIndex_, E_Goods_pet))
		return;

	// ������
	if(pet.IsLock())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString(eText_PetLockShop) );
		return;
	}

	// ��ս�У����ɽ���
	if(pet.baseInfo.isActive)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString(eText_PetInBattle) );
		return;
	}

// 	ItemDefine::SItemCommon *pItem = GettheItemDetail().GetItemByID( pMountItem->GetMountID() );
// 	if( !pItem )
// 		return;
// 
// 	// �ܷ���
// 	if( !pItem->bIsCanTrade )
// 	{
// 		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eClient_AddInfo_2slk_31 ) );
// 		return;
// 	}

	StallageItem stallItem;
	stallItem.m_nBagType = BT_PetBag;
	stallItem.m_nSrcIndex = srcIndex_;
	stallItem.m_nDestIndex = destIndex_;
	stallItem.m_nCount = 1;
	stallItem.m_nGuid = pet.GetPetGuid();

	s_CUI_ID_FRAME_EditPrice.Show( AddItemToStallageSell, &stallItem, sizeof( stallItem ), 1 );
}

void CSystemStallage::RemovePetSell(int index_)
{
	// ��̯��
	if( IsSelfInStalling() )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private,
			theXmlString.GetString( eText_StallFailed_NoItemMoveWhenOpen ) );
		return;
	}

	index_ += m_goodsIndex[E_Goods_pet];
	if(!CheckGoodIndex(index_, E_Goods_pet))
		return;

	MsgRemoveStallDataReq msg;
	msg.uchIndex = index_;
	GettheNetworkInput().SendMsg( &msg );
}

void CSystemStallage::RemovePetSell(SPetItem &pet_)
{
	int index = s_CUI_ID_FRAME_PrivateShop.GetPetIndex(pet_);
	if(index >= 0)
		RemovePetSell(index);
}

// ��������̯λ�������ƶ�
void CSystemStallage::MoveMountToSell( int nDestIndex, int nSrcIndex )
{
    // ��̯��
    if( IsSelfInStalling() )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private,
            theXmlString.GetString( eText_StallFailed_NoItemMoveWhenOpen ) );
        return;
    }

    nDestIndex += m_nMountSellIndexBegin;
    if( nDestIndex < m_nMountSellIndexBegin || nDestIndex >= m_nItemBuyIndexBegin )
        return;

    SMountItem* pMountItem = &thePlayerRole.GetMountByIndex( nSrcIndex );
    if( pMountItem->baseInfo.id == 0 )
        return;

    // ������
    if( pMountItem->IsLock() )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_MountLockShop ) );
        return;
    }

    // ��ս�У����ɽ���
    if( thePlayerRole.GetActivedMount() )
    {
        if( thePlayerRole.GetActivedMount()->baseInfo.guid == pMountItem->baseInfo.guid )
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eMountError_ActiveMountNotSupport ) );
            return;
        }
    }

    ItemDefine::SItemCommon *pItem = GettheItemDetail().GetItemByID( pMountItem->GetMountID() );
    if( !pItem )
        return;

    // �ܷ���
    if( !pItem->bIsCanTrade )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eClient_AddInfo_2slk_31 ) );
        return;
    }

    StallageItem stallItem;
    stallItem.m_nBagType = BT_MountBag;
    stallItem.m_nSrcIndex = nSrcIndex;
    stallItem.m_nDestIndex = nDestIndex;
    stallItem.m_nCount = 1;
    stallItem.m_nGuid = pMountItem->GetMountGuid();

    s_CUI_ID_FRAME_EditPrice.Show( AddItemToStallageSell, &stallItem, sizeof( stallItem ), 1 );
}

// �ӱ�����̯λ�չ����ƶ�
void CSystemStallage::MoveFromPackToGoodsBuy( int nDestIndex, int nSrcIndex, int nBagType )
{
    // ��̯��
    if( IsSelfInStalling() )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private,
            theXmlString.GetString( eText_StallFailed_NoItemMoveWhenOpen ) );
        return;
    }

    nDestIndex += m_nItemBuyIndexBegin;
    if( nDestIndex < m_nItemBuyIndexBegin || nDestIndex >= StallDefine::MaxStallCount )
        return;
    if( nBagType != BT_NormalItemBag && nBagType != BT_MaterialBag )
        return;

    // �ӱ��������л�ȡ��Ʒ��Ϣ
    CItemBag2* pBag = NULL;
    if( nBagType == BT_NormalItemBag )
    {
        pBag = &thePlayerRole.m_bag;		
    }
    else
    {
        pBag = &thePlayerRole.m_bagMaterial;
    }

    SCharItem charItem;
    if( !pBag->GetItem( nSrcIndex, &charItem ) )
        return;

    // ��Ʒ�Ѱ�
    if( charItem.IsBounded() )
    {
        CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eUI_SoulBoundedCanotDo ));
        return;
    }
    if( nSrcIndex >= pBag->GetNowBagSize() )
        return;
    ItemDefine::SItemCommon *pItem = GettheItemDetail().GetItemByID( charItem.GetItemID() );
    if ( !pItem )
        return;

    // �ܷ���
    if( !pItem->bIsCanTrade )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eClient_AddInfo_2slk_31 ) );
        return;
    }

    // ֻ���չ��ɶѵ���Ʒ
    if( pItem->nStackNum <= 1 )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_AddBuyAllowStack ) );
        return;
    }

    StallageItem stallItem;
    stallItem.m_nBagType = nBagType;
    stallItem.m_nSrcIndex = nSrcIndex;
    stallItem.m_nDestIndex = nDestIndex;
    stallItem.m_nCount = 0;
    stallItem.m_nGuid = charItem.GetItemGuid();

    s_CUI_ID_FRAME_Reclaim.Show( AddItemToStallageBuy, &stallItem, sizeof( stallItem ) );
}

// ���۽�Ǯ�����ص�
bool CSystemStallage::AddItemToStallageSell( DWORD dwPrice, void *pData )
{
    if( !pData )
        return false;

    StallageItem* pStallItem = ( StallageItem* )pData;
    if( pStallItem->m_nDestIndex < 0 || pStallItem->m_nDestIndex >= StallDefine::MaxStallCount )
        return false;

    // ������ӳ�����Ʒ��Ϣ
    MsgAddSellDataReq msg;
    msg.uchBagType = pStallItem->m_nBagType;
    msg.uchBagIndex = pStallItem->m_nSrcIndex;
    msg.nGameMoneyPrice = dwPrice;
    msg.nRMBMoneyPrice = 0;
    msg.uchCount = pStallItem->m_nCount;
    msg.n64Guid = pStallItem->m_nGuid;
    msg.uchStallIndex = pStallItem->m_nDestIndex;
    GettheNetworkInput().SendMsg( &msg );

    return true;
}

// �չ������ص�
bool CSystemStallage::AddItemToStallageBuy( DWORD dwPrice, int nCount, void *pData )
{
    if( !pData )
        return false;

    StallageItem* pStallItem = ( StallageItem* )pData;
    if( pStallItem->m_nDestIndex < 0 || pStallItem->m_nDestIndex >= StallDefine::MaxStallCount )
        return false;

    if( nCount <= 0 || nCount > CSystemStallage::Instance()->GetBuyStackNumLimit() )
        return false;

    SCharItem charItem;
    thePlayerRole.GetBagItemByGUID( pStallItem->m_nGuid, &charItem );
    int nItemId = charItem.GetItemID();
    if( nItemId < 0 )
        return false;

    // ��������չ���Ʒ��Ϣ
    MsgAddBuyDataReq msg;
    msg.uchBagType = pStallItem->m_nBagType;
    msg.ustItemID = nItemId;
    msg.nGameMoneyPrice = dwPrice;
    msg.nRMBMoneyPrice = 0;
    msg.uchCount = nCount;
    msg.uchStallIndex = pStallItem->m_nDestIndex;
    GettheNetworkInput().SendMsg( &msg );

    return true;
}

// ��Ʒ���������ƶ�
void CSystemStallage::MoveGoodsInSellSlots( int nSrcIndex, int nDestIndex )
{
    // ��̯��
    if( IsSelfInStalling() )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private,
            theXmlString.GetString( eText_StallFailed_NoItemMoveWhenOpen ) );
        return;
    }

    nSrcIndex += m_nItemSellIndexBegin;
    nDestIndex += m_nItemSellIndexBegin;

    if( nSrcIndex < m_nItemSellIndexBegin || nSrcIndex >= m_nMountSellIndexBegin )
        return;

    if( nDestIndex < m_nItemSellIndexBegin || nDestIndex >= m_nMountSellIndexBegin )
        return;

    MsgMoveStallDataReq msg;
    msg.uchSrcIndex = nSrcIndex;
    msg.uchDestIndex = nDestIndex;
    GettheNetworkInput().SendMsg( &msg );
}

// ����������Ʒ�ƶ�
void CSystemStallage::MoveMountInSellSlots( int nSrcIndex, int nDestIndex )
{
    // ��̯��
    if( IsSelfInStalling() )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private,
            theXmlString.GetString( eText_StallFailed_NoItemMoveWhenOpen ) );
        return;
    }

    nSrcIndex += m_nMountSellIndexBegin;
    nDestIndex += m_nMountSellIndexBegin;

    if( nSrcIndex < m_nMountSellIndexBegin || nSrcIndex >= m_nItemBuyIndexBegin )
        return;

    if( nDestIndex < m_nMountSellIndexBegin || nDestIndex >= m_nItemBuyIndexBegin )
        return;

    MsgMoveStallDataReq msg;
    msg.uchSrcIndex = nSrcIndex;
    msg.uchDestIndex = nDestIndex;
    GettheNetworkInput().SendMsg( &msg );
}

// �չ�������Ʒ�ƶ�
void CSystemStallage::MoveGoodsInBuySlots( int nSrcIndex, int nDestIndex )
{
    // ��̯��
    if( IsSelfInStalling() )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private,
            theXmlString.GetString( eText_StallFailed_NoItemMoveWhenOpen ) );
        return;
    }

    nSrcIndex += m_nItemBuyIndexBegin;
    nDestIndex += m_nItemBuyIndexBegin;

    if( nSrcIndex < m_nItemBuyIndexBegin || nSrcIndex >= StallDefine::MaxStallCount )
        return;

    if( nDestIndex < m_nItemBuyIndexBegin || nDestIndex >= StallDefine::MaxStallCount )
        return;

    MsgMoveStallDataReq msg;
    msg.uchSrcIndex = nSrcIndex;
    msg.uchDestIndex = nDestIndex;
    GettheNetworkInput().SendMsg( &msg );
}

// ���������Ƴ���Ʒ
void CSystemStallage::RemoveGoodsSell( int nIndex )
{
    // ��̯��
    if( IsSelfInStalling() )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private,
            theXmlString.GetString( eText_StallFailed_NoItemMoveWhenOpen ) );
        return;
    }

    nIndex += m_nItemSellIndexBegin;
    if( nIndex < m_nItemSellIndexBegin || nIndex >= m_nMountSellIndexBegin )
        return;

    MsgRemoveStallDataReq msg;
    msg.uchIndex = nIndex;
    GettheNetworkInput().SendMsg( &msg );
}

// ���������Ƴ���Ʒ
void CSystemStallage::RemoveMountSell( int nIndex )
{
    // ��̯��
    if( IsSelfInStalling() )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private,
            theXmlString.GetString( eText_StallFailed_NoItemMoveWhenOpen ) );
        return;
    }

    nIndex += m_nMountSellIndexBegin;
    if( nIndex < m_nMountSellIndexBegin || nIndex >= m_nItemBuyIndexBegin )
        return;

    MsgRemoveStallDataReq msg;
    msg.uchIndex = nIndex;
    GettheNetworkInput().SendMsg( &msg );
}

// �չ������Ƴ���Ʒ
void CSystemStallage::RemoveGoodsBuy( int nIndex )
{
    // ��̯��
    if( IsSelfInStalling() )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private,
            theXmlString.GetString( eText_StallFailed_NoItemMoveWhenOpen ) );
        return;
    }
    nIndex += m_nItemBuyIndexBegin;
    if( nIndex < m_nItemBuyIndexBegin || nIndex >= StallDefine::MaxStallCount )
        return;

    MsgRemoveStallDataReq msg;
    msg.uchIndex = nIndex;
    GettheNetworkInput().SendMsg( &msg );
}

// ��̯
void CSystemStallage::StartStallRequest()
{
    // ��̯��
    if( IsSelfInStalling() )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private,
            theXmlString.GetString( eText_StallFailed_NoItemMoveWhenOpen ) );
        return;
    }
    
    if( !CheckMeExist() )
        return;
    CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();

    // ��ģʽ���ܰ�̯
    if( pMe->GetPKType() == PKMode_Critical )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_PKMode_FuryNoShop ) );
        return;
    }

    // ���ֲ��ܰ�̯��״̬
    if( pMe->HasFightFlag( eFighting ) )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_InBattle ) );
        return;
    }
    if( pMe->IsInWater() )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_PrivateShopError_InSwin ) );
        return;
    }
    if( pMe->IsJumping() )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_SitFailed_CurrStatus ) );
        return;
    }
    if( pMe->IsMounting() )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_SitFailed_CurrStatus ) );
        return;
    }
    if( pMe->IsDead() )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_PrivateShopError_InDead ) );
        return;
    }

    // ���ƷǷ�
    std::string strTitle = s_CUI_ID_FRAME_PrivateShop.GetStallageTitleName();
    if( strTitle.empty() || !CChatCheck::getInstance()->CheckStringInLow( strTitle.c_str() ) )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_NameError ) );
        return;
    }

    MsgStartStallReq msg;
	if(m_bOnlineStall)
		msg.uchOpenType = MsgStartStallReq::TypeStartStall;
	else
		msg.uchOpenType = MsgStartStallReq::TypeStartOfflineStall;
    MeSprintf_s( msg.szTitle, sizeof( msg.szTitle ) / sizeof( char ) - 1, "%s", strTitle.c_str() );
    GettheNetworkInput().SendMsg( &msg );
}

// ��̯
void CSystemStallage::CloseStallRequest()
{
    // δ��̯
    if( !IsSelfInStalling() )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString( eText_StallFailed_StallageClose ) );
        return;
    }

    MsgCloseStallReq msg;
    GettheNetworkInput().SendMsg( &msg );
}

// �������̯λ����
void CSystemStallage::ChangeStallName()
{
    s_CUI_ID_FRAME_Rename.SetType( CUI_ID_FRAME_Rename::eChangeStallName );
    s_CUI_ID_FRAME_Rename.SetVisable( true );
}

// ���ĵ�̯λ����
void CSystemStallage::TellStallageName( const char* pName )
{
    MsgChangeStallTitleReq msg;
    std::string strTmp = std::string( pName ).substr( 0, StallDefine::MaxStallTitle - 1 );
    MeSprintf_s( msg.szTitle, sizeof( msg.szTitle ) / sizeof( char ) - 1, strTmp.c_str() );
    GettheNetworkInput().SendMsg( &msg );
}

void CSystemStallage::SetItemPrice(int totalIndex_)
{
	// ��̯��
	if( IsSelfInStalling() )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private,
			theXmlString.GetString( eText_StallFailed_NoItemMoveWhenOpen ) );
		return;
	}

	if(totalIndex_ < 0)
		return;

	int subIndex = -1;
	EGoodsType goodType = GetGoodInfo(totalIndex_, subIndex);
	if(goodType >= E_Goods_end || subIndex < 0)
		return;

	int count = m_selfStallData[totalIndex_].GetCount();

	switch(goodType)
	{
	case E_Goods_common:
		{
			if( count <= 0 )
				return;
		}
		break;
	case E_Goods_pet:
		{
			if(count != 1)
				return;
		}
		break;
	case E_Goods_replace:
		{

		}
		break;
	case E_Goods_mount:
		{
			if(count != 1)
				return;
		}
		break;
	case E_Goods_buy:
		{
			if(count <= 0)
				return;
		}
		break;
	default:
		{
			assert(false);
			return;
		}
	}

	StallageItem stallItem;
	stallItem.m_nDestIndex = totalIndex_;
	s_CUI_ID_FRAME_EditPrice.Show( SelfStallageSetPrice, &stallItem, sizeof( StallageItem ), count );
}

// ������ü۸�
void CSystemStallage::SetItemPrice( int nIndex, bool bIsSell, bool bIsMount, __int64 nGuid )
{
    // ��̯��
    if( IsSelfInStalling() )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private,
            theXmlString.GetString( eText_StallFailed_NoItemMoveWhenOpen ) );
        return;
    }

    int nTotalIndex( -1 ), nCount( 0 );
    SCharItem charItem;
    if( bIsSell && !bIsMount )
    {
        // ���۵���
        nTotalIndex = GetTotalIndexBySubIndex( nIndex, StallDefine::StallSell );
        if( nTotalIndex < 0 )
            return;

        nCount = m_selfStallData[nTotalIndex].GetCount();
        if( nCount <= 0 )
            return;
    }
    else if( bIsSell && bIsMount )
    {
        // ��������
        nTotalIndex = GetTotalIndexBySubIndex( nIndex, StallDefine::StallSell, BT_MountBag );
        if( nTotalIndex < 0 )
            return;

        nCount = m_selfStallData[nTotalIndex].GetCount();
        if( nCount != 1 )
            return;

        if( m_selfStallData[nTotalIndex].GetBagType() != BT_MountBag )
            return;
    }
    else if( !bIsSell && !bIsMount )
    {
        // �չ�����
        nTotalIndex = GetTotalIndexBySubIndex( nIndex, StallDefine::StallBuy );
        if( nTotalIndex < 0 )
            return;

        nCount = m_selfStallData[nTotalIndex].GetCount();
        if( nCount <= 0 )
            return;
    }
    else
    {
        return;
    }

    StallageItem stallItem;
    stallItem.m_nDestIndex = nTotalIndex;
    s_CUI_ID_FRAME_EditPrice.Show( SelfStallageSetPrice, &stallItem, sizeof( StallageItem ), nCount );
}

// ���ü۸������ص�
bool CSystemStallage::SelfStallageSetPrice( DWORD dwPrice, void *pData )
{
    if( !pData )
        return false;

    StallageItem* pStallItem = ( StallageItem* )pData;
    if( pStallItem->m_nDestIndex < 0 || pStallItem->m_nDestIndex >= StallDefine::MaxStallCount )
        return false;

    // �����޸���Ʒ�۸���Ϣ
    MsgChangeStallPriceReq msg;
    msg.uchStallIndex = pStallItem->m_nDestIndex;
    msg.nGameMoneyPrice = dwPrice;
    msg.nRMBMoneyPrice = 0;
    GettheNetworkInput().SendMsg( &msg );

    return true;
}

// ��ս��׼�¼
void CSystemStallage::ClearTradeRecord()
{
    m_tradeRecordVec.clear();
    s_CUI_ID_FRAME_TradeRecord.Refresh();
}

// ����鿴���˵�̯λ
void CSystemStallage::QuerryPlayerStallageRequest( int nPlayerId )
{
    if( !CheckPlayerExist( nPlayerId ) )
        return;

    // ��ȫ������������Բ������׶�
//     if( CWealthProtect::Instance().IsInProtectTime() || CPreventWallow::Instance().IsFCMNotHealthy() )
//     {
//         return;
//     }

    CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID( nPlayerId );

    m_nVenderPlayerId = nPlayerId;

    MsgOpenStallReq msg;
    msg.nPlayerID = nPlayerId;
    GettheNetworkInput().SendMsg( &msg );
}

// ��̯������
void CSystemStallage::LeaveMessageToVender()
{
    int nVenderId = GetVenderId();
    if( !CheckPlayerExist( nVenderId ) )
        return;

    CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID( nVenderId );

    chatMessageManage.ShowChatMessageFrame( pPlayer->GetName() );
}

// ����Ʒ����̯���չ�����
void CSystemStallage::MoveItemToVenderBuy( int nBagType, int nSrcIndex, int nDestIndex, __int64 nGuid )
{
    // �Ƿ�Ϊ�չ�����
    if( nBagType != BT_NormalItemBag && nBagType != BT_MaterialBag )
        return;

    int nTotalIndex = GetTotalIndexBySubIndex( nDestIndex, StallDefine::StallBuy );
    if( nTotalIndex < 0 )
        return;
    if( m_playerBuyData[nTotalIndex].GetCount() == 0 )
        return;

    // �Ƿ�Ϊͬ����Ʒ
    SCharItem charItem;
    if( !thePlayerRole.GetBagItemByGUID( nGuid, &charItem ) )
        return;
    if( m_playerBuyData[nTotalIndex].GetItemID() != charItem.GetItemID() )
        return;

    // ���ϱ�׼��������������
    int nMaxCount = min( m_playerBuyData[nTotalIndex].GetCount(), charItem.GetItemCount() );

    StallageItem stallItem;
    stallItem.m_nBagType = nBagType;
    stallItem.m_nSrcIndex = nSrcIndex;
    stallItem.m_nDestIndex = nTotalIndex;
    stallItem.m_nMoneyPrice = m_playerBuyData[nTotalIndex].GetGameMoneyPrice();
    stallItem.m_nItemId = charItem.GetItemID();
    stallItem.m_nGuid = nGuid;

    CUI_ID_FRAME_BatchShop::Show( "", true, true, SellItemToVender, &stallItem, sizeof( StallageItem ) );
    s_CUI_ID_FRAME_BatchShop.SetMaxValue( nMaxCount );
    s_CUI_ID_FRAME_BatchShop.SetEditNumber( 1 );
}

// ����̯��������Ŀ�����ص�
bool CSystemStallage::SellItemToVender( const char* szInputData, void *pData )
{
    if( !pData )
        return false;

    int nGoodsCount = atoi( szInputData );
    if( nGoodsCount <= 0 )
        return false;

    StallageItem* pStallData = ( StallageItem* )pData;

    if( pStallData->m_nDestIndex < 0 || pStallData->m_nDestIndex >= StallDefine::MaxStallCount )
        return false;

    int nPlayerId = CSystemStallage::Instance()->GetVenderId();
    if( nPlayerId < 0 )
        return false;

    BuyDataToClient* pBuyData = CSystemStallage::Instance()->GetPlayerBuyData(); 
    if( !pBuyData )
        return false;

    MsgSellStallReq msg;
    msg.nPlayerID = nPlayerId;
    msg.uchStallIndex = pStallData->m_nDestIndex;
    msg.nGameMoneyPrice = pBuyData[pStallData->m_nDestIndex].GetGameMoneyPrice();
    msg.nRMBMoneyPrice = pBuyData[pStallData->m_nDestIndex].GetRMBMoneyPrice();
    msg.uchBagType = pStallData->m_nBagType;
    msg.uchBagIndex = pStallData->m_nSrcIndex;
    msg.uchCount = nGoodsCount;
    msg.n64Guid = pStallData->m_nGuid;
    GettheNetworkInput().SendMsg( &msg );

    return true;
}

void CSystemStallage::GetItemFromVenderSell( int totalIndex_)
{
	if(totalIndex_ < 0)
		return;

	int subIndex = -1;
	EGoodsType goodType = GetGoodInfo(totalIndex_, subIndex);
	if(goodType >= E_Goods_end || subIndex < 0)
		return;

	int nMaxCount( 0 ),nItemId( -1 );
	__int64 nGuid = -1;
	switch(goodType)
	{
	case E_Goods_common:
		{
			SCharItem charItem;
			m_playerSellData[totalIndex_].GetData( &charItem, sizeof( SCharItem ) );
			nGuid = charItem.GetItemGuid();
			nItemId = charItem.GetItemID();
			nMaxCount = charItem.GetItemCount();
		}
		break;
	case E_Goods_pet:
		{

			SPetItem item;
			m_playerSellData[totalIndex_].GetData( &item, sizeof(item) );
			nGuid = item.GetPetGuid();
			//nItemId = item.GetPetID();
			nItemId = item.baseInfo.itemId;
			nMaxCount = 1;
		}
		break;
	case E_Goods_replace:
		{

		}
		break;
	case E_Goods_mount:
		{

			SMountItem mountItem;
			m_playerSellData[totalIndex_].GetData( &mountItem, sizeof( SMountItem ) );
			nGuid = mountItem.GetMountGuid();
			nItemId = mountItem.GetMountID();
			nMaxCount = 1;
		}
		break;
	case E_Goods_buy:
		{
		}
		break;
	default:
		{
			assert(false);
		}
	}

	if( nItemId < 0 )
		return;
	if( nMaxCount <= 0 )
		return;
	if(nGuid < 0)
		return;


	// ���ϱ�׼�����빺������
	StallageItem stallItem;
	stallItem.m_nDestIndex = totalIndex_;
	stallItem.m_nGuid = nGuid;
	stallItem.m_nMoneyPrice = m_playerSellData[totalIndex_].GetGameMoneyPrice();
	stallItem.m_nItemId = nItemId;

	CUI_ID_FRAME_BatchShop::Show( "", true, true, BuyItemFromVender, &stallItem, sizeof( StallageItem ), false, 2, true );
	s_CUI_ID_FRAME_BatchShop.SetMaxValue( nMaxCount );
	s_CUI_ID_FRAME_BatchShop.SetEditNumber( 1 );
}

// ��̯�������򶫶�
void CSystemStallage::GetItemFromVenderSell( int nIndex, bool bIsMount, __int64 nGuid )
{
    // �Ƿ�Ϊ̯�����۶��󣬻�ȡ̯λ����
    int nTotalIndex( -1 ), nMaxCount( 0 ),nItemId( -1 );
    if( bIsMount )
    {
        nTotalIndex = GetTotalIndexBySubIndex( nIndex, StallDefine::StallSell, BT_MountBag );
        if( nTotalIndex < m_nMountSellIndexBegin || nTotalIndex >= m_nItemBuyIndexBegin )
            return;

        SMountItem mountItem;
        m_playerSellData[nTotalIndex].GetData( &mountItem, sizeof( SMountItem ) );
        if( mountItem.GetMountGuid() != nGuid )
            return;

        nItemId = mountItem.GetMountID();
        nMaxCount = 1;
    }
    else
    {
        nTotalIndex = GetTotalIndexBySubIndex( nIndex, StallDefine::StallSell );
        if( nTotalIndex < m_nItemSellIndexBegin || nTotalIndex >= m_nMountSellIndexBegin )
            return;

        SCharItem charItem;
        m_playerSellData[nTotalIndex].GetData( &charItem, sizeof( SCharItem ) );
        if( charItem.GetItemGuid() != nGuid )
            return;

        nItemId = charItem.GetItemID();
        nMaxCount = charItem.GetItemCount();
    }

    if( nItemId < 0 )
        return;
    if( nMaxCount <= 0 )
        return;

    // ���ϱ�׼�����빺������
    StallageItem stallItem;
    stallItem.m_nDestIndex = nTotalIndex;
    stallItem.m_nGuid = nGuid;
    stallItem.m_nMoneyPrice = m_playerSellData[nTotalIndex].GetGameMoneyPrice();
    stallItem.m_nItemId = nItemId;

    CUI_ID_FRAME_BatchShop::Show( "", true, true, BuyItemFromVender, &stallItem, sizeof( StallageItem ), false, 2, true );
    s_CUI_ID_FRAME_BatchShop.SetMaxValue( nMaxCount );
    s_CUI_ID_FRAME_BatchShop.SetEditNumber( 1 );
}

// ��̯�������򶫶���Ŀ�����ص�
bool CSystemStallage::BuyItemFromVender( const char* szInputData, void *pData )
{
    if( !pData )
        return false;

    int nGoodsCount = atoi( szInputData );
    if( nGoodsCount <= 0 )
        return false;

    StallageItem* pStallData = ( StallageItem* )pData;

    if( pStallData->m_nDestIndex < 0 || pStallData->m_nDestIndex >= StallDefine::MaxStallCount )
        return false;

    int nPlayerId = CSystemStallage::Instance()->GetVenderId();
    if( nPlayerId < 0 )
        return false;

    SellDataToClient* pSellData = CSystemStallage::Instance()->GetPlayerSellData();
    if( !pSellData )
        return false;

    MsgBuyStallReq msg;
    msg.nPlayerID = nPlayerId;
    msg.uchIndex = pStallData->m_nDestIndex;
    msg.nGameMoneyPrice = pSellData[pStallData->m_nDestIndex].GetGameMoneyPrice();
    msg.nRMBMoneyPrice = pSellData[pStallData->m_nDestIndex].GetRMBMoneyPrice();
    msg.uchCount = nGoodsCount;
    msg.n64Guid = pStallData->m_nGuid;
    GettheNetworkInput().SendMsg( &msg );

    return true;
}

CSystemStallage::EGoodsType CSystemStallage::GetGoodInfo(int index_, int &_subIndex)
{
	EGoodsType type = E_Goods_end;
	if(index_ < m_goodsIndex[0] || index_ >= m_goodsIndex[E_Goods_end] )
		return type;

	for(int i = 0; i < (int)E_Goods_end; ++i)
	{
		if(index_ >= m_goodsIndex[i] && index_ < m_goodsIndex[i + 1])
		{
			type = (EGoodsType)i;
			_subIndex = index_ - m_goodsIndex[i];
		}
	}

	return type;
}

bool CSystemStallage::CheckGoodIndex(int index_, EGoodsType goodType_)
{
	if(goodType_ >= E_Goods_end)
		return false;

	return index_ >= m_goodsIndex[goodType_] && index_ < m_goodsIndex[goodType_ + 1];
}
