/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Code\RunTime\CLIENT\Data\UI\Bargaining.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Bargaining.h"
#include "Pack.h"
#include "ChatInfoBox.h"
#include "GameMain.h"
#include "PlayerRole.h"
#include "XmlStringLanguage.h"
#include "FuncPerformanceLog.h"
#include "MessageBox.h"
#include "../Player.h"
#include "PlayerMgr.h"
#include "Pack_Ex.h"
#include "core/Name.h"
#include "MeUi/ExpressionManager.h"
#include "ui/Pet.h"
#include "ui/SeekPet.h"
#include "ui/PrivateShop.h"
#include "color_config.h"
#include "ShowScreenText.h"
#include "XmlStringLanguage.h"
#include "Common.h"
#include "PreventWallow.h"
#include "Ui/InfoList.h"
#include "BargainingDefine.h"
#include "GameSetting.h"
#include "SoundConfig.h"
#include "TradeMoney.h"
#include "SelectPet.h"
#include "Helper/PetHelper.h"
#include "ui/SeeSuAnimal.h"
#include "PackItemEnableManager.h"
#include "WealthProtect.h"
#include "ui/Soul.h"

CUI_ID_FRAME_Bargaining s_CUI_ID_FRAME_Bargaining;

MAP_FRAME_RUN( s_CUI_ID_FRAME_Bargaining, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Bargaining, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Bargaining, ID_LISTIMG_MeOnIconDragOn )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Bargaining, ID_LISTIMG_MeOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Bargaining, ID_BUTTON_QuitOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Bargaining, ID_BUTTON_CompleteOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Bargaining, ID_BUTTON_LockOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Bargaining, ID_LISTIMG_MyPetOnIconDragOn )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Bargaining, ID_LISTIMG_MyPetOnIconRButtonUp )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Bargaining, ID_LISTIMG_MyPetOnIconButtonClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Bargaining, ID_LISTIMG_PlayerPetOnIconButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Bargaining, ID_BUTTON_SeekPlayerPetOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Bargaining, ID_BUTTON_SeekMyPetOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Bargaining, ID_BUTTON_MoneyInputOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Bargaining, ID_LIST_PlayerPetOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Bargaining, ID_LIST_SelfPetOnListSelectChange )

CUI_ID_FRAME_Bargaining::CUI_ID_FRAME_Bargaining()
{
	// Member
	m_pID_FRAME_Bargaining = NULL;
	m_pID_BUTTON_Lock = NULL;
	m_pID_BUTTON_Complete = NULL;
	m_pID_LISTIMG_Me = NULL;
	m_pID_LISTIMG_Player = NULL;
	m_pID_TEXT_PlayerGold = NULL;
    m_pID_TEXT_MeGold = NULL;
	m_pID_PICTURE_SelfLock = NULL;
	m_pID_PICTURE_PlayerLock = NULL;
	m_pID_TEXT_SelfName = NULL;
	m_pID_TEXT_PlayerName = NULL;
	m_pID_BUTTON_Quit = NULL;
	m_pID_LISTIMG_PlayerPet = NULL;
	m_pID_LISTIMG_MyPet = NULL;
	m_pID_BUTTON_SeekPlayerPet = NULL;
	m_pID_BUTTON_SeekMyPet = NULL;
    m_pID_BUTTON_MoneyInput = NULL;

	m_nPlayerId = -1;
	m_bQueryBargaining = false;
    m_nSelfStatus = BargainingDefine::StatusInit;
    m_nPlayerStatus = BargainingDefine::StatusInit;
    m_pSelectMount = NULL;
}

int CUI_ID_FRAME_Bargaining::PetList_GetNullItem()
{
    if( !IsUILoad() )
        return -1;

    return m_pID_LISTIMG_MyPet->GetNullItem();
}

ControlIconDrag::S_ListImg* CUI_ID_FRAME_Bargaining::GetLISTIMG_MyPetItem( const unsigned int nIndex )
{
	if ( !m_pID_FRAME_Bargaining )
		return NULL;
	if( !m_pID_LISTIMG_MyPet )
		return NULL;
	
	return m_pID_LISTIMG_MyPet->GetItemByIndex(nIndex);
}

bool CUI_ID_FRAME_Bargaining::OnIconDragOnFromPack( ControlObject* pSender, ControlIconDrag::S_ListImg* pItemDrag )
{
	if ( !m_pID_FRAME_Bargaining )
		return false;
	if( !m_pID_LISTIMG_Me )
		return false;
	int nNullIndex = m_pID_LISTIMG_Me->GetNullItem();
	if( nNullIndex == -1 )
		return false;

	return ID_LISTIMG_MeOnIconDragOn( pSender, NULL, pItemDrag, m_pID_LISTIMG_Me->GetItemByIndex( nNullIndex ) );
}

bool CUI_ID_FRAME_Bargaining::IsEqualToLISTIMG_Me( const ControlListImage* pItemDrag )
{
	if ( !m_pID_FRAME_Bargaining )
		return false;
	if( !m_pID_LISTIMG_Me )
		return false;
	return (m_pID_LISTIMG_Me == pItemDrag);
}

void CUI_ID_FRAME_Bargaining::BargainReset()
{
	if( !IsUILoad() )
		return;

    m_pID_LISTIMG_Me->Clear();
    m_pID_LISTIMG_MyPet->Clear();
    m_pID_LISTIMG_Player->Clear();
    m_pID_LISTIMG_PlayerPet->Clear();

	m_pID_BUTTON_Lock->SetEnable( true );
	m_pID_BUTTON_Complete->SetEnable( false );
    m_pID_PICTURE_SelfLock->SetVisable( false );
    m_pID_PICTURE_PlayerLock->SetVisable( false );

    SetSelectMount( NULL );
    m_MountItems.clear();
    int gold = 0;
    int silver = 0;
    int copper = 0;
    std::stringstream str;
    str << gold << "#81  ";
    str << silver << "#82  ";
    str << copper << "#83  ";
    std::string text = str.str();
    ExpressionManager::GetInstance().AddExpressionAni( text );
    *m_pID_TEXT_PlayerGold = text;
    *m_pID_TEXT_MeGold = text;

    m_nSelfStatus = BargainingDefine::StatusInit;
    m_nPlayerStatus = BargainingDefine::StatusInit;
}

// Frame
bool CUI_ID_FRAME_Bargaining::OnFrameRun()
{	
	guardfunc;

	// --- changed by huwen. -----
	if ( m_bQueryBargaining ) 
	{
		CPlayer* pPlayer, *pMe;
		pPlayer = theHeroGame.GetPlayerMgr()->FindByID( m_nPlayerId );
		pMe = theHeroGame.GetPlayerMgr()->GetMe();
		//
		if ( !pPlayer || !pMe )
		{
			if ( s_CUI_ID_FRAME_MessageBox.IsVisable() ) 
				s_CUI_ID_FRAME_MessageBox.ID_BUTTON_NOOnButtonClick( NULL );

			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_Client_Trade_Faild) );

			m_bQueryBargaining = false;
			return false;
		}

		float fMeX,fMeY,fMeZ;
		float fPlayerX, fPlayerY, fPlayerZ;
		pMe->GetPos( &fMeX, &fMeY, &fMeZ );
		pPlayer->GetPos( &fPlayerX, &fPlayerY, &fPlayerZ );
		float x = fPlayerX - fMeX;
		float y = fPlayerY - fMeY;
		float dist = sqrtf( x*x + y*y );
		if( dist > 10.0f )
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_Client_Trade_Faild_Distance) );

			if ( s_CUI_ID_FRAME_MessageBox.IsVisable() ) 
				s_CUI_ID_FRAME_MessageBox.ID_BUTTON_NOOnButtonClick( NULL );

			m_bQueryBargaining = false;
		}
	}
	//----------------------------

	if ( IsVisable() )
	{
		CPlayer* pPlayer, *pMe;
		pPlayer = theHeroGame.GetPlayerMgr()->FindByID( m_nPlayerId );
		pMe = theHeroGame.GetPlayerMgr()->GetMe();
		//
		if ( !pPlayer || !pMe )
		{
			ID_BUTTON_CancelOnButtonClick( NULL );
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_Client_Trade_Faild) );
			return false;
		}
		//
		if ( pPlayer->IsMounting() ||
			pMe->IsMounting() )
		{
			ID_BUTTON_CancelOnButtonClick( NULL );
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_Client_Trade_Faild_Ride) );
			return false;
		}
		//
		float fMeX,fMeY,fMeZ;
		float fPlayerX, fPlayerY, fPlayerZ;
		pMe->GetPos( &fMeX, &fMeY, &fMeZ );
		pPlayer->GetPos( &fPlayerX, &fPlayerY, &fPlayerZ );
		float x = fPlayerX - fMeX;
		float y = fPlayerY - fMeY;
		float dist = sqrtf( x*x + y*y );
		if( dist > 10.0f )
		{
			ID_BUTTON_CancelOnButtonClick(NULL);		
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_Client_Trade_Faild_Distance) );

			return false;	
		}
	}
	return true;
	unguard;
}

bool CUI_ID_FRAME_Bargaining::OnFrameRender()
{
	guardfunc;
	return true;
	unguard;
}

// Button
bool CUI_ID_FRAME_Bargaining::ID_BUTTON_LockOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !IsUILoad() )
		return false;

	MsgBargainingLockReq msgLock;
	GettheNetworkInput().SendMsg( &msgLock );
	return true;
	unguard;
}

// Button
bool CUI_ID_FRAME_Bargaining::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
    SetVisable( false );
    return true;
}

bool CUI_ID_FRAME_Bargaining::ID_BUTTON_CompleteOnButtonClick( ControlObject* pSender )
{
	if (!m_pID_FRAME_Bargaining)
		return false;

	if( CPreventWallow::Instance().IsFCMNotHealthy() )
	{
		SetVisable( false );
	}
    else
    {
		s_CUI_ID_FRAME_Soul.SetVisable(false);//铸魂UI关闭
        MsgBargainingFixReq msg;
        GettheNetworkInput().SendMsg( &msg );
    }

	return true;
}

bool CUI_ID_FRAME_Bargaining::ID_LISTIMG_MeOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !IsUILoad() )
		return false;

    if( m_nSelfStatus != BargainingDefine::StatusStart )
		return false;

	ControlListImage* pBagListImg = 0;
	CItemBag2* pBag = 0;
	int bagType = BT_NormalItemBag;

	if( s_CUI_ID_FRAME_PACK.IsListImageByBagType( BT_NormalItemBag, pSender ) )
	{
		pBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType( BT_NormalItemBag );
		pBag = &thePlayerRole.m_bag;
		bagType = BT_NormalItemBag;
	}
	else if( s_CUI_ID_FRAME_PACK.IsListImageByBagType( BT_MaterialBag, pSender ) )
	{
		pBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType( BT_MaterialBag );
		pBag = &thePlayerRole.m_bagMaterial;
		bagType = BT_MaterialBag;
	}
	else
    {
		return false;
    }

	if ( !pItemDrag || pItemDrag->IsNull() )
		return false;
	if ( !pItemSrc || !pItemSrc->IsNull() )
		return false;

	int nIndex = pBagListImg->GetItemIndex( pItemDrag );
	if ( nIndex == -1 )
		return false;

    int nBarginIndex = m_pID_LISTIMG_Me->GetItemIndex( pItemSrc );
    if ( nBarginIndex == -1 )
        return false;

	// 如果物品已经加锁 return			
	SCharItem stItem;
	if( pBag->GetItem( nIndex, &stItem ) == false )
	{
		return false;
	}
	if( stItem.storageinfo.bIsLocked )
	{
		CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Trade_Failed, theXmlString.GetString( eText_ItemHaveBeenLocked ) );
		return false;
	}
	if( stItem.IsBounded() )
	{
		CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Trade_Failed, theXmlString.GetString( eUI_SoulBoundedCanotDo ));
		return false;
	}
	if( stItem.itembaseinfo.ustItemID != pItemDrag->m_pkIconInfo->GetItemId() )
	{
		return false;
	}
	ItemDefine::SItemCommon *pItem = NULL;
	pItem = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->Id() );
	if( !pItem )
		return false;

	// 是否可买卖
	if ( !pItem->bIsCanTrade )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_Failed, theXmlString.GetString( eClient_AddInfo_2slk_31 ) );
		return false;
	}

    // 放入物品
    MsgBargainingDataReq msg;
    msg.uchBargainintType = BargainingDefine::BargainingItem;
    msg.uchBargainingIndex = nBarginIndex;
    msg.uchBagType = bagType;
    msg.uchIndex = nIndex;
    msg.n64Guid = stItem.itembaseinfo.nOnlyInt;
    GettheNetworkInput().SendMsg( &msg );

	return false;
	unguard;
}

bool CUI_ID_FRAME_Bargaining::ID_LISTIMG_MeOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    if( !IsUILoad() )
        return false;

    if( m_nSelfStatus != BargainingDefine::StatusStart )
        return false;

	if( !pItem )
		return false;
    int nIndex = m_pID_LISTIMG_Me->GetItemIndex( pItem );
    if( nIndex == -1 )
        return false;

    // 发送移除交易栏内物品消息
    MsgRemoveBargainingDataReq msg;
    msg.uchBargainingIndex = nIndex;
    GettheNetworkInput().SendMsg( &msg );

	return false;
}

bool CUI_ID_FRAME_Bargaining::ID_LISTIMG_MyPetOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
	ControlIconDrag::S_ListImg* pItemDrag,
	ControlIconDrag::S_ListImg* pItemSrc )
{
	return true; //先不让交易 lrt
    if( !IsUILoad() )
        return false;

    if( m_nSelfStatus != BargainingDefine::StatusStart )
        return false;

	if( !s_CUI_ID_FRAME_Pet.IsEqualToLISTIMG_PetIcon( pSender ) )
	{
		return false;
	}	

	if( !pItemDrag || pItemDrag->IsNull() )
		return false;
	if( !pItemSrc || !pItemSrc->IsNull() )
		return false;

	int nIndex = s_CUI_ID_FRAME_Pet.PenIcon_GetIndexByItem( pItemDrag );
	if ( nIndex == -1 )
		return false;
    int nBarginIndex = m_pID_LISTIMG_MyPet->GetItemIndex( pItemSrc );
    if( nBarginIndex == -1 )
        return false;

	SMountItem* pMountItem = &thePlayerRole.GetMountByIndex( nIndex );
	if( pMountItem->baseInfo.id == InvalidLogicNumber )
		return false;
	
	ItemDefine::SItemCommon *pItem = NULL;
	pItem = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->Id() );
	if( !pItem )
		return false;

	// 是否可买卖
	if( !pItem->bIsCanTrade )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_Failed, theXmlString.GetString( eClient_AddInfo_2slk_31 ) );
		return false;
	}

    // 出战中，不可交易
	if( thePlayerRole.GetActivedMount() )
	{
		if( thePlayerRole.GetActivedMount()->baseInfo.guid == pMountItem->baseInfo.guid )
		{
			CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Trade_Failed,
                theXmlString.GetString( eMountError_ActiveMountNotSupport ) );
			return false;
		}
	}

    // 放入坐骑
    MsgBargainingDataReq msg;
    msg.uchBargainintType = BargainingDefine::BargainingMount;
    msg.uchBargainingIndex = nBarginIndex + m_pID_LISTIMG_Player->GetItemCnt();
    msg.uchBagType = BT_MountBag;
    msg.uchIndex = nIndex;
    msg.n64Guid = pMountItem->baseInfo.guid;
    GettheNetworkInput().SendMsg( &msg );

	return false;
}

bool CUI_ID_FRAME_Bargaining::ID_LISTIMG_MyPetOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{		
    if( !IsUILoad() )
        return false;

    if( m_nSelfStatus != BargainingDefine::StatusStart )
        return false;

    if( !pItem )
		return false;
	
    // 发送移除交易栏内坐骑消息
	int nIndex = m_pID_LISTIMG_MyPet->GetItemIndex( pItem );	

    MsgRemoveBargainingDataReq msg;
    msg.uchBargainingIndex = nIndex + m_pID_LISTIMG_Player->GetItemCnt();;
    GettheNetworkInput().SendMsg( &msg );

	return false;
}

bool CUI_ID_FRAME_Bargaining::ID_LISTIMG_MyPetOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    if ( !IsUILoad() )
        return false;

    if( !pItem )
        return false;

    SetSelectMount( pItem );
    return false;
}

bool CUI_ID_FRAME_Bargaining::ID_LISTIMG_PlayerPetOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    if ( !IsUILoad() )
        return false;

    if( !pItem )
        return false;

    SetSelectMount( pItem );
    return false;
}

// Button 查看选中别人的宠物
bool CUI_ID_FRAME_Bargaining::ID_BUTTON_SeekPlayerPetOnButtonClick( ControlObject* pSender )
{
	if( !IsUILoad() )
		return false;

    //if( !m_pSelectMount || !m_pSelectMount->m_pkIconInfo )
    //    return true;

    //int nIndex = m_pID_LISTIMG_PlayerPet->GetItemIndex( m_pSelectMount );
    //if( nIndex < 0 || nIndex >= m_pID_LISTIMG_PlayerPet->GetItemCnt() )
    //    return true;

    //for( int i = 0 ; i < m_MountItems.size() ; ++ i )
    //{
    //    SMountItem* pMountItem = &m_MountItems[i];
    //    if( pMountItem->baseInfo.guid == m_pSelectMount->m_pkIconInfo->GetOnlyId() )
    //    {
    //        s_CUI_ID_FRAME_SeekPet.SetVisable( true );
    //        s_CUI_ID_FRAME_SeekPet.SetMount( *pMountItem );
    //        return true;
    //    }
    //}

	ControlList::S_List *pItem = NULL;
	if(m_pID_LIST_PlayerPet)
		pItem = m_pID_LIST_PlayerPet->GetCurSelItem();

	if(pItem != NULL)
	{
		int idx = m_pID_LIST_PlayerPet->GetCurSelIndex();
		if ( idx >= m_PetItems.size() )
		{
			return true;
		}
		
		SPetItem *pet = (SPetItem *) &m_PetItems[idx];
		if(pet != NULL)
		{
			s_CUI_ID_FRAME_SeeSuAnimal.SetVisable(true);
			s_CUI_ID_FRAME_SeeSuAnimal.SetPetItem(*pet);
		}
	}
	
	return true;
}

// Button  查看自己选中的宠物
bool CUI_ID_FRAME_Bargaining::ID_BUTTON_SeekMyPetOnButtonClick( ControlObject* pSender )
{
 //   if( !m_pSelectMount || !m_pSelectMount->m_pkIconInfo )
 //       return true;

 //   int nIndex = m_pID_LISTIMG_MyPet->GetItemIndex( m_pSelectMount );
 //   if( nIndex < 0 || nIndex >= m_pID_LISTIMG_MyPet->GetItemCnt() )
 //       return true;

	//SMountItem* pMount = thePlayerRole.GetMountByGUID( m_pSelectMount->m_pkIconInfo->GetOnlyId() );
 //   if( !pMount )
 //       return true;

	//s_CUI_ID_FRAME_SeekPet.SetVisable( true );
	//s_CUI_ID_FRAME_SeekPet.SetMount( *pMount );

	ControlList::S_List *pItem = NULL;
	if(m_pID_LIST_SelfPet)
		pItem = m_pID_LIST_SelfPet->GetCurSelItem();

	if(pItem != NULL)
	{
		SPetItem *pet = (SPetItem *)pItem->m_pData;
		if(pet != NULL)
		{
			s_CUI_ID_FRAME_SeeSuAnimal.SetVisable(true);
			s_CUI_ID_FRAME_SeeSuAnimal.SetPetItem(*pet);
		}
	}
	
	return true;
}

bool CUI_ID_FRAME_Bargaining::ID_BUTTON_MoneyInputOnButtonClick( ControlObject* pSender )
{
    if( !IsUILoad() )
        return false;

    s_CUI_ID_FRAME_TradeMoney.ShowMoneyInput( TellAddMoney, theXmlString.GetString( eText_MoneyInput_Trade ) );
    return true;
}

// List
void CUI_ID_FRAME_Bargaining::ID_LIST_PlayerPetOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_Bargaining )
		return;
	m_pID_BUTTON_SeekPlayerPet->SetEnable( true );
}

// List
void CUI_ID_FRAME_Bargaining::ID_LIST_SelfPetOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_Bargaining )
		return;
	m_pID_BUTTON_SeekMyPet->SetEnable( true );
}

// 装载UI
bool CUI_ID_FRAME_Bargaining::_LoadUI()
{
    guardfunc;
    DWORD dwResult = theUiManager.AddFrame( "data\\ui\\Bargaining.meui", false, UI_Render_LayerFirst );
    if ( dwResult == 0 )
    {
        MESSAGE_BOX("读取文件[UI\\Bargaining.UI]失败")
            return false;
    }
    return DoControlConnect();
    unguard;
}

// 关连控件
bool CUI_ID_FRAME_Bargaining::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_Bargaining, s_CUI_ID_FRAME_BargainingOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Bargaining, s_CUI_ID_FRAME_BargainingOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_Bargaining, ID_BUTTON_Lock, s_CUI_ID_FRAME_BargainingID_BUTTON_LockOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Bargaining, ID_BUTTON_Quit, s_CUI_ID_FRAME_BargainingID_BUTTON_QuitOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Bargaining, ID_BUTTON_Complete, s_CUI_ID_FRAME_BargainingID_BUTTON_CompleteOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_Bargaining, ID_LISTIMG_Me, s_CUI_ID_FRAME_BargainingID_LISTIMG_MeOnIconDragOn );
	theUiManager.OnIconRButtonUp( ID_FRAME_Bargaining, ID_LISTIMG_Me, s_CUI_ID_FRAME_BargainingID_LISTIMG_MeOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_Bargaining, ID_LISTIMG_MyPet, s_CUI_ID_FRAME_BargainingID_LISTIMG_MyPetOnIconDragOn );
	theUiManager.OnIconRButtonUp( ID_FRAME_Bargaining, ID_LISTIMG_MyPet, s_CUI_ID_FRAME_BargainingID_LISTIMG_MyPetOnIconRButtonUp );
    theUiManager.OnIconButtonClick( ID_FRAME_Bargaining, ID_LISTIMG_MyPet, s_CUI_ID_FRAME_BargainingID_LISTIMG_MyPetOnIconButtonClick );
    theUiManager.OnIconButtonClick( ID_FRAME_Bargaining, ID_LISTIMG_PlayerPet, s_CUI_ID_FRAME_BargainingID_LISTIMG_PlayerPetOnIconButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Bargaining, ID_BUTTON_SeekPlayerPet, s_CUI_ID_FRAME_BargainingID_BUTTON_SeekPlayerPetOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Bargaining, ID_BUTTON_SeekMyPet, s_CUI_ID_FRAME_BargainingID_BUTTON_SeekMyPetOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_Bargaining, ID_BUTTON_MoneyInput, s_CUI_ID_FRAME_BargainingID_BUTTON_MoneyInputOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_Bargaining, ID_LIST_PlayerPet, s_CUI_ID_FRAME_BargainingID_LIST_PlayerPetOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Bargaining, ID_LIST_SelfPet, s_CUI_ID_FRAME_BargainingID_LIST_SelfPetOnListSelectChange );

	m_pID_FRAME_Bargaining = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Bargaining );
	m_pID_BUTTON_Lock = (ControlButton*)theUiManager.FindControl( ID_FRAME_Bargaining, ID_BUTTON_Lock );
	m_pID_BUTTON_Quit = (ControlButton*)theUiManager.FindControl( ID_FRAME_Bargaining, ID_BUTTON_Quit );
	m_pID_BUTTON_Complete = (ControlButton*)theUiManager.FindControl( ID_FRAME_Bargaining, ID_BUTTON_Complete );
	m_pID_LISTIMG_Me = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Bargaining, ID_LISTIMG_Me );
	m_pID_LISTIMG_Player = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Bargaining, ID_LISTIMG_Player );
	m_pID_TEXT_PlayerGold = (ControlText*)theUiManager.FindControl( ID_FRAME_Bargaining, ID_TEXT_PlayerGold );
    m_pID_TEXT_MeGold = (ControlText*)theUiManager.FindControl( ID_FRAME_Bargaining, ID_TEXT_MeGold );
	m_pID_PICTURE_SelfLock = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Bargaining, ID_PICTURE_SelfLock );
	m_pID_PICTURE_PlayerLock = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Bargaining, ID_PICTURE_PlayerLock );
	m_pID_TEXT_SelfName = (ControlText*)theUiManager.FindControl( ID_FRAME_Bargaining, ID_TEXT_SelfName );
	m_pID_TEXT_PlayerName = (ControlText*)theUiManager.FindControl( ID_FRAME_Bargaining, ID_TEXT_PlayerName );
	m_pID_LISTIMG_PlayerPet = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Bargaining, ID_LISTIMG_PlayerPet );
	m_pID_LISTIMG_MyPet = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Bargaining, ID_LISTIMG_MyPet );		
	m_pID_BUTTON_SeekPlayerPet = (ControlButton*)theUiManager.FindControl( ID_FRAME_Bargaining, ID_BUTTON_SeekPlayerPet );
	m_pID_BUTTON_SeekMyPet = (ControlButton*)theUiManager.FindControl( ID_FRAME_Bargaining, ID_BUTTON_SeekMyPet );
    m_pID_BUTTON_MoneyInput = (ControlButton*)theUiManager.FindControl( ID_FRAME_Bargaining, ID_BUTTON_MoneyInput );
	m_pID_LIST_PlayerPet = (ControlList*)theUiManager.FindControl( ID_FRAME_Bargaining, ID_LIST_PlayerPet );
	m_pID_LIST_SelfPet = (ControlList*)theUiManager.FindControl( ID_FRAME_Bargaining, ID_LIST_SelfPet );

    assert( m_pID_FRAME_Bargaining );
	assert( m_pID_BUTTON_Lock );
	assert( m_pID_BUTTON_Quit );
	assert( m_pID_BUTTON_Complete );
	assert( m_pID_LISTIMG_Me );
	assert( m_pID_LISTIMG_Player );
	assert( m_pID_TEXT_PlayerGold );
    assert( m_pID_TEXT_MeGold );
	assert( m_pID_PICTURE_SelfLock );
	assert( m_pID_PICTURE_PlayerLock );
	assert( m_pID_TEXT_SelfName );
	assert( m_pID_TEXT_PlayerName );
    assert( m_pID_BUTTON_MoneyInput );
	assert( m_pID_LIST_PlayerPet );
	assert( m_pID_LIST_SelfPet );

    m_pID_FRAME_Bargaining->SetVisable(false);
    m_pID_FRAME_Bargaining->SetOnVisibleChangedFun( OnVisibleChanged );

    theUiManager.SetFrameLayout(UI_LAYOUT_1, m_pID_FRAME_Bargaining);

    m_pID_LISTIMG_Me->SetEnableDragOut( false );
    m_pID_LISTIMG_MyPet->SetEnableDragOut( false );

    m_pID_PICTURE_SelfLock->SetVisable( false );
    m_pID_PICTURE_PlayerLock->SetVisable( false );

	// 初始化成员变量
	m_nPlayerId = -1;
	m_bQueryBargaining = false;

	return true;
	unguard;
}

// 卸载UI
bool CUI_ID_FRAME_Bargaining::_UnLoadUI()
{
	guardfunc;
	theUiManager.RemoveFrameLayout(m_pID_FRAME_Bargaining);
	m_pID_FRAME_Bargaining = NULL;
	m_pID_BUTTON_Lock = NULL;
	m_pID_BUTTON_Complete = NULL;
	m_pID_LISTIMG_Me = NULL;
	m_pID_LISTIMG_Player = NULL;
	m_pID_TEXT_PlayerGold = NULL;
    m_pID_TEXT_MeGold = NULL;
	m_pID_PICTURE_SelfLock = NULL;
	m_pID_PICTURE_PlayerLock = NULL;
	m_pID_TEXT_SelfName = NULL;
	m_pID_TEXT_PlayerName = NULL;
	m_pID_BUTTON_Quit = NULL;
	m_pID_LISTIMG_PlayerPet = NULL;
	m_pID_LISTIMG_MyPet = NULL;
	m_pID_BUTTON_SeekPlayerPet = NULL;
	m_pID_BUTTON_SeekMyPet = NULL;
    m_pID_BUTTON_MoneyInput = NULL;
	m_pID_LIST_PlayerPet = NULL;
	m_pID_LIST_SelfPet = NULL;

	m_MountItems.clear();
    m_pSelectMount = NULL;
	return theUiManager.RemoveFrame( "data\\ui\\Bargaining.meui" );
	unguard;
}
// 是否可视
bool CUI_ID_FRAME_Bargaining::_IsVisable()
{
	guardfunc;
	if (!m_pID_FRAME_Bargaining)
		return false;
	return m_pID_FRAME_Bargaining->IsVisable();
	unguard;
}
// 设置是否可视
void CUI_ID_FRAME_Bargaining::_SetVisable( const bool bVisable )
{
	guardfunc;
	if (!m_pID_FRAME_Bargaining)
		return;

	if ( !bVisable )
	{
		if(s_CUI_ID_FRAME_SelectPet.IsVisable())
		{
			s_CUI_ID_FRAME_SelectPet.SetVisable(false);
		}
	}
	else
	{
		m_petIDList.clear();
		m_PetItems.clear();
		m_pID_LIST_PlayerPet->Clear();
		m_pID_LIST_SelfPet->Clear();
		s_CUI_ID_FRAME_SelectPet.SetVisable(true);
		s_CUI_ID_FRAME_SelectPet.Refresh();
	}

	m_pID_FRAME_Bargaining->SetVisable( bVisable );
	unguard;
}

void CUI_ID_FRAME_Bargaining::SetPlayer( const char* szPlayerName, int nId )
{
	guardfunc;
	if (!m_pID_FRAME_Bargaining)
		return;
	assert( szPlayerName );
	if( !szPlayerName )
		return;
	m_nPlayerId = nId;
	*m_pID_TEXT_PlayerName = szPlayerName;
	*m_pID_TEXT_SelfName = thePlayerRole.GetName();
	unguard;
}

void CUI_ID_FRAME_Bargaining::SetQueryBargaining( bool enabled )
{
    // 处于收到交易申请状态时，离申请者过远会自动拒绝 ( huwen 的逻辑 )
	m_bQueryBargaining = enabled;
}

bool CUI_ID_FRAME_Bargaining::ID_BUTTON_QuitOnButtonClick( ControlObject* pSender )
{
	return ID_BUTTON_CancelOnButtonClick( NULL );
}

//-------------------------------- 新的交易流程 -------------------------------------

void CUI_ID_FRAME_Bargaining::OnVisibleChanged( ControlObject* pSender )
{
    // 界面关闭
    if( !pSender )
        return;
    if( !pSender->IsVisable() )
    {
        s_CUI_ID_FRAME_Bargaining.SelfCancelBargain();
    }
}

void CUI_ID_FRAME_Bargaining::SelfCancelBargain()
{
    // 交易中界面关闭则发送取消交易消息
    if( m_nSelfStatus == BargainingDefine::StatusInit )
        return;

    MsgBargainingCancelReq msg;
    GettheNetworkInput().SendMsg( &msg );
}

void CUI_ID_FRAME_Bargaining::TellRequestBargainResult( int nResult )
{
    // 交易申请结果
    switch( nResult )
    {
    case BargainingDefine::FailedBargaining:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_Failed,
                theXmlString.GetString( eText_BargainFailed_SelfInTrade ) );
        }
        break;
    case BargainingDefine::FailedTargetBargaining:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_Failed,
                theXmlString.GetString( eText_BargainFailed_OppoInTrade ) );
        }
        break;
    case BargainingDefine::FailedStall:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_Failed,
                theXmlString.GetString( eText_BargainFailed_SelfInStallage ) );
        }
        break;
    case BargainingDefine::FailedTargetStall:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_Failed,
                theXmlString.GetString( eText_BargainFailed_OppoInStallage ) );
        }
        break;
    case BargainingDefine::FailedNotInArea:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_Failed,
                theXmlString.GetString( eText_BargainFailed_OppoOutOfRange ) );
        }
        break;
    case BargainingDefine::FailedRefuse:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_Failed,
                theXmlString.GetString( eText_BargainFailed_OppoRefuse ) );
        }
        break;
    case BargainingDefine::FailedRequest:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_Success,
                theXmlString.GetString( eText_BargainSuccess_Request ) );
        }
        break;
	case BargainingDefine::FailedTargetFighting:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_Failed,
				theXmlString.GetString(eText_Bargain_TargetInFightState));
		}
		break;
    default:
        break;
    }
}

void CUI_ID_FRAME_Bargaining::TellPlayerRequestBargain( int nPayerId )
{



    // 收到交易申请，弹出对话框
    CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
    if( !pPlayerMgr )
        return;

    CPlayer* pPlayer = pPlayerMgr->FindByID( nPayerId );
    if ( !pPlayer )
        return;
    
    CPlayer* pMe = pPlayerMgr->GetMe();
    if( !pMe )
        return;

    // 以前的逻辑:设置了战斗状态自动拒绝
    bool bInFight = pMe->HasFightFlag( eFighting );
    bool bRefuseInFight = ( bool )GameSetting::Instance()->GetLevel( GameSetting::eGSC_RefuseBargainInFight );
    bool bRefuse = ( bool )GameSetting::Instance()->GetLevel( GameSetting::eGSC_RefuseBargain );
    if( ( bInFight && bRefuseInFight ) || ( !bInFight && bRefuse ) )
    {
        QueryBargaining( false );
        return;
    }

    char szMsg[MAX_PATH] = {0};
    MeSprintf_s( szMsg, sizeof( szMsg ) - 1, theXmlString.GetString( eExchange_Ask ), pPlayer->GetName() );
    s_CUI_ID_FRAME_MessageBox.Show( szMsg, "", CUI_ID_FRAME_MessageBox::eTypeYesNo, false, CUI_ID_FRAME_Bargaining::QueryBargaining );

    SetPlayer( pPlayer->GetName(), nPayerId );
    SetQueryBargaining( true );

    PlaySoundConfig( SoundConfig::EST_RequestTrade );
}

bool CUI_ID_FRAME_Bargaining::QueryBargaining( const char bPressYesButton, void* pData )
{
    // 收到交易申请，点完对话框的回调
    MsgBargainingRequestAck msg;
    if( bPressYesButton != 0 )
    {
		//lyh++ 财产保护时间内，不允许接受别人的交易
		DWORD dwEndTime = CWealthProtect::Instance().GetProtectEndingTime();
		if( dwEndTime > HQ_TimeGetTime() )
		{
			// 安全保护时间内无法修改安全保护时间
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_OperateFailInProtectTime) );
			msg.bBargainintAgree = false;
			GettheNetworkInput().SendMsg( &msg );
			return false;
		}

        msg.bBargainintAgree = true;
    }
    else
    {
        msg.bBargainintAgree = false;
    }
    GettheNetworkInput().SendMsg( &msg );
    return true;
}

void CUI_ID_FRAME_Bargaining::TellBargainStart( int nPlayerId )
{
    // 交易开始
    m_selfItems.clear();
    CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
    if( !pPlayerMgr )
        return;

    CPlayer* pPlayer = pPlayerMgr->FindByID( nPlayerId );
    if ( !pPlayer )	
        return;

    // 重置界面，同时打开背包
    SetVisable( true );
    BargainReset();
    SetPlayer( pPlayer->GetName(), nPlayerId );
    if( !s_CUI_ID_FRAME_PACK.IsVisable() )
    {
        s_CUI_ID_FRAME_PACK.SetVisable( true );
    }
    ResetWindowPosition( s_CUI_ID_FRAME_Bargaining.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame() );
    SetQueryBargaining( false );
    m_nSelfStatus = BargainingDefine::StatusStart;
    m_nPlayerStatus = BargainingDefine::StatusStart;
}

void CUI_ID_FRAME_Bargaining::TellBargainFinish( int nType )
{
    // 交易完成
    m_selfItems.clear();
    switch( nType )
    {
    case BargainingDefine::FinishSuccess:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_Success,
                theXmlString.GetString( eText_BargainSuccess_Finish ) );
        }
        break;
    case BargainingDefine::FinishTimeOut:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_Failed,
                theXmlString.GetString( eText_BargainFailed_OutOfTime ) );
        }
        break;
    case BargainingDefine::FinishCancel:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_Failed,
                theXmlString.GetString( eText_BargainFailed_Cancel ) );
        }
        break;
    case BargainingDefine::FinishOutLine:
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_Failed,
                theXmlString.GetString( eText_BargainFailed_Offline ) );
        }
        break;
    default:
        {
            return;
        }
        break;
    }

    SetVisable( false );

    // 交易失败需要将原先失效物品恢复
    if( nType != BargainingDefine::FinishSuccess )
    {
        RenewItems();
    }

    BargainReset();
}

void CUI_ID_FRAME_Bargaining::TellBargainStatus( int nPlayerId, int nStatusType )
{
    // 交易过程中双方的各种状态变化
    if( !IsUILoad() )
        return;

    CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
    if( !pPlayerMgr )
        return;

    CPlayer* pMe = pPlayerMgr->GetMe();
    if( !pMe )
        return;

    if( pMe->GetID() == nPlayerId )
    {
        // 自己
        switch( nStatusType )
        {
            // 某方出错导致重新进入放物品状态
        case BargainingDefine::StatusStart:
            {
                m_nSelfStatus = BargainingDefine::StatusStart;
                m_pID_BUTTON_Lock->SetEnable( true );
                m_pID_BUTTON_Complete->SetEnable( false );
                m_pID_PICTURE_SelfLock->SetVisable( false );
            }
            break;
            // 自己进入锁定状态
        case BargainingDefine::StatusLock:
            {
                m_nSelfStatus = BargainingDefine::StatusLock;
                m_pID_BUTTON_Lock->SetEnable( false );
                m_pID_PICTURE_SelfLock->SetVisable( true );
                if( m_nPlayerStatus == BargainingDefine::StatusLock )
                {
                    m_pID_BUTTON_Complete->SetEnable( true );
                }
            }
            break;
            // 自己进入点完成交等待服务器确认状态
        case BargainingDefine::StatusFix:
            {
                m_nSelfStatus = BargainingDefine::StatusFix;
                m_pID_BUTTON_Complete->SetEnable( false );
            }
            break;
        default:
            break;
        }

		s_CUI_ID_FRAME_SelectPet.EnableSelect( BargainingDefine::StatusLock != nStatusType );
    }
    else
    {
        // 对方
        CPlayer* pPlayer = pPlayerMgr->FindByID( nPlayerId );
        if ( !pPlayer )	
            return;

        switch( nStatusType )
        {
            // 某方出错导致重新进入放物品状态
        case BargainingDefine::StatusStart:
            {
                m_nPlayerStatus = BargainingDefine::StatusStart;
                m_pID_PICTURE_PlayerLock->SetVisable( false );
            }
            break;
            // 对方进入锁定状态
        case BargainingDefine::StatusLock:
            {
                m_nPlayerStatus = BargainingDefine::StatusLock;
                m_pID_PICTURE_PlayerLock->SetVisable( true );
                if( m_nSelfStatus == BargainingDefine::StatusLock )
                {
                    m_pID_BUTTON_Complete->SetEnable( true );
                }
            }
            break;
            // 对方进入点完成交等待服务器确认状态
        case BargainingDefine::StatusFix:
            {
                m_nPlayerStatus = BargainingDefine::StatusFix;
            }
            break;
        default:
            break;
        }
    }
}

void CUI_ID_FRAME_Bargaining::TellBargainErrors( int nPlayerId, int nErrorType )
{
    // 交易过程中自己或对方的出错信息
    CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
    if( !pPlayerMgr )
        return;

    CPlayer* pMe = pPlayerMgr->GetMe();
    if( !pMe )
        return;

    std::string strError;
    switch( nErrorType )
    {
    case BargainingDefine::LessMoney:
        {
            strError = theXmlString.GetString( eText_BargainFailed_NoMoney );
        }
        break;
    case BargainingDefine::LessRMB:
        {
            strError = theXmlString.GetString( eText_BargainFailed_NoGold );
        }
        break;
    case BargainingDefine::MaxMoney:
        {
            strError = theXmlString.GetString( eText_BargainFailed_MoneyMax );
        }
        break;
    case BargainingDefine::DataError:
        {
            strError = theXmlString.GetString( eText_BargainFailed_ItemError );
        }
        break;
    case BargainingDefine::DataLocked:
        {
            strError = theXmlString.GetString( eText_BargainFailed_ItemBind );
        }
        break;
    case BargainingDefine::DataOverdue:
        {
            strError = theXmlString.GetString( eText_BargainFailed_ItemOverdue );
        }
        break;
    case BargainingDefine::DataAlready:
        {
            strError = theXmlString.GetString( eText_BargainFailed_ItemExist );
        }
        break;
    case BargainingDefine::IndexAlready:
        {
            strError = theXmlString.GetString( eText_BargainFailed_SlotFilled );
        }
        break;
    case BargainingDefine::CanNotTrade:
        {
            strError = theXmlString.GetString( eText_BargainFailed_ItemNoTrade );
        }
        break;
    case BargainingDefine::IndexError:
        {
            strError = theXmlString.GetString( eText_BargainFailed_PosError );
        }
        break;
    case BargainingDefine::NormalFull:
        {
            strError = theXmlString.GetString( eText_BargainFailed_PackFull );
        }
        break;
    case BargainingDefine::MaterialFull:
        {
            strError = theXmlString.GetString( eText_BargainFailed_MaterialFull );
        }
        break;
    case BargainingDefine::MountFull:
        {
            strError = theXmlString.GetString( eText_BargainFailed_HouseFull );
        }
        break;
    case BargainingDefine::DataChange:
        {
            strError = theXmlString.GetString( eText_BargainFailed_ItemChange );
        }
        break;
    case BargainingDefine::MountActive:
        {
            strError = theXmlString.GetString( eText_BargainFailed_HouseBattle );
        }
        break;
    case BargainingDefine::MoneyLevelLimit:
        {
            strError = theXmlString.GetString( eText_BargainFailed_LevelLess );
        }
        break;
    case BargainingDefine::MountLevelLimit:
        {
            strError = theXmlString.GetString( eText_BargainFailed_HouseLevelHigh );
        }
        break;
	case BargainingDefine::PlayerPetLimit:
		{
			strError = theXmlString.GetString( eText_BargainFailed_PlayerPetLimit );
		}
		break;
	case BargainingDefine::PetFull:
		{
			strError = theXmlString.GetString( eText_BargainFailed_PlayerPetLimit );
		}
		break;
    default:
        break;
    }

    // 是对方出错的话，在出错信息前增加对方名字
    char szError[MAX_PATH] = {0};
    if( pMe->GetID() == nPlayerId )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_Failed, strError );
    }
    else
    {
        CPlayer* pPlayer = pPlayerMgr->FindByID( nPlayerId );
        if ( !pPlayer )	
            return;

        MeSprintf_s( szError, sizeof( szError ) / sizeof( char ) - 1, "~%s_ %s", pPlayer->GetName(), strError.c_str() );
        strError = szError;
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_Failed, strError );
    }
}

bool CUI_ID_FRAME_Bargaining::TellAddMoney( DWORD dwMoney, void* m_pData )
{
    // 自己放上金钱
    if( dwMoney > 0 )
    {
        MsgBargainingDataReq msg;
        msg.uchBargainintType = BargainingDefine::BargainingMoney;
        msg.nBargainingValue = dwMoney;
        GettheNetworkInput().SendMsg( &msg );
    }
    return true;
}

void CUI_ID_FRAME_Bargaining::TellBargainSelfAddData( MsgBargainingDataAck* pMsg )
{
    // 服务器回馈，自己将交易品拖至交易栏内
    if( !IsUILoad() )
    {
        BargainSelfError();
        return;
    }

    switch( pMsg->uchBargainintType )
    {
    // 放上了金钱
    case BargainingDefine::BargainingMoney:
        {
            DWORD dwMoney = pMsg->nBargainingValue;
            int gold( 0 ), silver( 0 ), copper( 0 );
            thePlayerRole.GetGSCFromMoney( dwMoney, gold, silver, copper );
            std::stringstream str;
            str << gold << "#81  ";
            str << silver << "#82  ";
            str << copper << "#83  ";
            std::string text = str.str();
            ExpressionManager::GetInstance().AddExpressionAni( text );
            *m_pID_TEXT_MeGold = text;
        }
        break;
    // 放上了马
    case BargainingDefine::BargainingMount:
        {
            // 各种错误，主动取消交易
            if( pMsg->uchBagType != BT_MountBag )
            {
                BargainSelfError();
                return;
            }

            int nIndex = pMsg->uchBargainingIndex - m_pID_LISTIMG_Me->GetItemCnt();
            if( nIndex < 0 || nIndex >= m_pID_LISTIMG_MyPet->GetItemCnt() )
            {
                BargainSelfError();
                return;
            }

            SMountItem* pMountItem = &thePlayerRole.GetMountByIndex( pMsg->uchIndex );
            if( !pMountItem || pMountItem->baseInfo.id == InvalidLogicNumber )
            {
                BargainSelfError();
                return;
            }

            if( pMountItem->baseInfo.guid != pMsg->n64Guid )
            {
                BargainSelfError();
                return;
            }
            
            // 拖动成功
            AddSelfItem( pMsg->n64Guid );
            SCharItem charItem;
            charItem.itembaseinfo.ustItemID = pMountItem->baseInfo.id;
            charItem.itembaseinfo.nOnlyInt = pMountItem->baseInfo.guid;
            ControlIconDrag::S_ListImg stListImg;
            stListImg.SetData( &charItem );
            m_pID_LISTIMG_MyPet->SetItem( &stListImg, nIndex );

            // 拖到交易栏后，原处失效
            s_CUI_ID_FRAME_Pet.RefreshIconInfo();
        }
        break;
    // 放置宠物
	case BargainingDefine::BargainingPet:
		{
			// 各种错误，主动取消交易
			if( pMsg->uchBagType != BT_PetBag )
			{
				BargainSelfError();
				return;
			}
			s_CUI_ID_FRAME_Bargaining.AddPetToBargainAck( thePlayerRole.GetPetIndex( pMsg->n64Guid ) );		
		}
		break;
	// 放上了道具
    case BargainingDefine::BargainingItem:
        {
            // 各种错误，主动取消交易
            ControlListImage* pBagListImg = NULL;
            CItemBag2* pBag = NULL;
            switch( pMsg->uchBagType )
            {
            case BT_NormalItemBag:
                {
                    pBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType( BT_NormalItemBag );
                    pBag = &thePlayerRole.m_bag;
                }
                break;
            case BT_MaterialBag:
                {
                    pBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType( BT_MaterialBag );
                    pBag = &thePlayerRole.m_bagMaterial;
                }
                break;
            default:
                {
                    BargainSelfError();
                    return;
                }
                break;
            }
            
            if( !pBagListImg || !pBag )
            {
                BargainSelfError();
                return;
            }
            
            int nBargainIndex = pMsg->uchBargainingIndex;
            if( nBargainIndex < 0 || nBargainIndex >= m_pID_LISTIMG_Me->GetItemCnt() )
            {
                BargainSelfError();
                return;
            }

            if( pMsg->uchIndex < 0 || pMsg->uchIndex >= pBagListImg->GetItemCnt() )
            {
                BargainSelfError();
                return;
            }

            SCharItem charItem;
            if( pBag->GetItem( pMsg->uchIndex, &charItem ) == false )
            {
                BargainSelfError();
                return;
            }

            if( charItem.itembaseinfo.nOnlyInt != pMsg->n64Guid )
            {
                BargainSelfError();
                return;
            }

            // 拖动成功
            AddSelfItem( pMsg->n64Guid );
            ControlIconDrag::S_ListImg stListImg;
            stListImg.SetData( &charItem );
            m_pID_LISTIMG_Me->SetItem( &stListImg, nBargainIndex );

            // 拖到交易栏后，原处失效
            CPackItemEnableManager::Instance()->RefreshBagItemEnable( pBag, pMsg->uchIndex, true );
        }
        break;
    default:
        break;
    }
}

void CUI_ID_FRAME_Bargaining::BargainSelfError()
{
    // 出错则主动取消交易
    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_Failed, 
        theXmlString.GetString( eText_BargainFailed_ItemError ) );
    SelfCancelBargain();
}

void CUI_ID_FRAME_Bargaining::TellBargainPlayerAddData( MsgShowBargainingData* pMsg )
{
    if( !IsUILoad() )
        return;

    switch( pMsg->uchBargainintType )
    {
        // 对方改变了交易金钱
    case BargainingDefine::BargainingMoney:
        {
            DWORD dwMoney = pMsg->nBargainingValue;
            int gold( 0 ), silver( 0 ), copper( 0 );
            thePlayerRole.GetGSCFromMoney( dwMoney, gold, silver, copper );
            std::stringstream str;
            str << gold << "#81  ";
            str << silver << "#82  ";
            str << copper << "#83  ";
            std::string text = str.str();
            ExpressionManager::GetInstance().AddExpressionAni( text );
            *m_pID_TEXT_PlayerGold = text;
        }
        break;
        // 对方在交易栏里增加了马
    case BargainingDefine::BargainingMount:
        {
            int nBargainIndex = pMsg->uchBargainingIndex - m_pID_LISTIMG_Player->GetItemCnt();
            if( sizeof( SMountItem ) > sizeof( pMsg->szBargainingData ) )
                break;

            if( nBargainIndex < 0 || nBargainIndex >= m_pID_LISTIMG_PlayerPet->GetItemCnt() )
                break;

            SMountItem mountItem;
            memset( &mountItem, 0, sizeof( SMountItem ) );
            memcpy_s( &mountItem, sizeof( SMountItem ), pMsg->szBargainingData, sizeof( SMountItem ) );

            SCharItem charItem;
            charItem.itembaseinfo.ustItemID = mountItem.baseInfo.id;
            charItem.itembaseinfo.nOnlyInt = mountItem.baseInfo.guid;
            m_MountItems.push_back( mountItem );

            ControlIconDrag::S_ListImg stListImg;
            stListImg.SetData( &charItem );
            m_pID_LISTIMG_PlayerPet->SetItem( &stListImg, nBargainIndex );
        }
        break;
		//对方交易栏里面增加宠物
	case BargainingDefine::BargainingPet:
		{
			int nBargainIndex = pMsg->uchBargainingIndex - m_pID_LISTIMG_Player->GetItemCnt();
			if( sizeof( SPetItem ) > sizeof( pMsg->szBargainingData ) )
				break;

			if( nBargainIndex < 0 || nBargainIndex >= m_pID_LISTIMG_PlayerPet->GetItemCnt() )
				break;

			SPetItem petItem;
			memset( &petItem, 0, sizeof( SPetItem ) );
			memcpy_s( &petItem, sizeof( SPetItem ), pMsg->szBargainingData, sizeof( SPetItem ) );

			SCharItem charItem;
			charItem.itembaseinfo.ustItemID = petItem.GetPetID();
			charItem.itembaseinfo.nOnlyInt = petItem.GetPetGuid();
			m_PetItems.push_back( petItem );

			ControlList::S_List	stItem;
			if(!IsValidPet(petItem))
				return;

			stItem.SetData(/*petItem.GetPetName()*/GetPetName(petItem).c_str(), 0, &petItem, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
			m_pID_LIST_PlayerPet->AddItem(&stItem, NULL, false);

		}
		break;
        // 对方在交易栏里增加了道具 
    case BargainingDefine::BargainingItem:
        {
            if( sizeof( SCharItem ) > sizeof( pMsg->szBargainingData ) )
                break;

            SCharItem charItem;
            memset( &charItem, 0, sizeof( SCharItem ) );
            memcpy_s( &charItem, sizeof( SCharItem ), pMsg->szBargainingData, sizeof( SCharItem ) );

            ControlIconDrag::S_ListImg stListImg;
            stListImg.SetData( &charItem );
            m_pID_LISTIMG_Player->SetItem( &stListImg, pMsg->uchBargainingIndex );
        }
        break;
    default:
        break;
    }
}

void CUI_ID_FRAME_Bargaining::TellBargainRemoveData( MsgRemoveBargainingDataAck* pMsg )
{
    if( !IsUILoad() )
        return;

    CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
    if( !pPlayerMgr )
        return;

    CPlayer* pMe = pPlayerMgr->GetMe();
    if( !pMe )
        return;

    if( pMe->GetID() == pMsg->ustPlayerID )
    {
		//宠物在自己移走的情况下就不处理自己的客户端了，因为已经处理过了


        // 自己从交易栏里移走物品
        int nBargainIndex = pMsg->uchBargainingIndex;
        if( nBargainIndex >= m_pID_LISTIMG_Me->GetItemCnt() )
        {
            // 马
            nBargainIndex -= m_pID_LISTIMG_Me->GetItemCnt();
            if( nBargainIndex < 0 || nBargainIndex >= m_pID_LISTIMG_MyPet->GetItemCnt() )
                return;

            ControlIconDrag::S_ListImg* pItem = m_pID_LISTIMG_MyPet->GetItemByIndex( nBargainIndex );
            if( !pItem )
                return;
            
            if( pItem->m_pkIconInfo )
            {
                RemoveSelfItem( pItem->m_pkIconInfo->GetOnlyId() );
            }

            // 移除的为选中坐骑，则取消选中
            if( pItem == m_pSelectMount )
            {
                SetSelectMount( NULL );
            }

            // 移除交易栏内的物品
            m_pID_LISTIMG_MyPet->RemoveItemByIndex( nBargainIndex );

            // 恢复坐骑栏内失效的物品
            s_CUI_ID_FRAME_Pet.RefreshIconInfo();
        }
        else
        {
            // 背包道具
            if( nBargainIndex < 0 || nBargainIndex >= m_pID_LISTIMG_Me->GetItemCnt() )
                return;

            ControlIconDrag::S_ListImg* pItem = m_pID_LISTIMG_Me->GetItemByIndex( nBargainIndex );
            if( !pItem )
                return;

            if( pItem->m_pkIconInfo )
            {
                RemoveSelfItem( pItem->m_pkIconInfo->GetOnlyId() );
            }

            EBagType eBagType;
            int nBagIndex = 0;
            if( !thePlayerRole.GetBagTypeByItemGUID( pItem->m_pkIconInfo->GetOnlyId(), eBagType, &nBagIndex ) )
                return;

            // 背包类型
            CItemBag2* pBag = NULL;
            if( eBagType == BT_NormalItemBag )
            {
                pBag = &thePlayerRole.m_bag;
            }
            else if( eBagType == BT_MaterialBag )
            {
                pBag = &thePlayerRole.m_bagMaterial;
            }
            else
            {
                return;
            }

            // 移除交易栏内的物品
            m_pID_LISTIMG_Me->RemoveItemByIndex( nBargainIndex );

            // 恢复背包内失效的物品
            CPackItemEnableManager::Instance()->RefreshBagItemEnable( pBag, nBagIndex, true );
        }
    }
    else
    {
        // 对方从交易栏里移走物品
        CPlayer* pPlayer = pPlayerMgr->FindByID( pMsg->ustPlayerID );
        if( !pPlayer )
            return;

        int nRemoveIndex = pMsg->uchBargainingIndex;
        if( nRemoveIndex >= m_pID_LISTIMG_Player->GetItemCnt() )
        {
            //  宠物
            nRemoveIndex -= m_pID_LISTIMG_Player->GetItemCnt();
            if( nRemoveIndex < 0 || nRemoveIndex >= m_pID_LISTIMG_PlayerPet->GetItemCnt() )
                return;

			if ( nRemoveIndex >= m_PetItems.size() )
			{
				return;
			}

			m_pID_LIST_PlayerPet->RemoveListItem( nRemoveIndex );
			m_PetItems.erase( m_PetItems.begin() + nRemoveIndex );

            //ControlIconDrag::S_ListImg* pItem = m_pID_LISTIMG_PlayerPet->GetItemByIndex( nRemoveIndex );
            //if( !pItem )
            //    return;

            //// 移除的为选中坐骑，则取消选中
            //if( pItem == m_pSelectMount )
            //{
            //    SetSelectMount( NULL );
            //}

            //m_pID_LISTIMG_PlayerPet->RemoveItemByIndex( nRemoveIndex );
        }
        else
        {
            // 道具
            if( nRemoveIndex >= m_pID_LISTIMG_Player->GetItemCnt() )
                return;
            m_pID_LISTIMG_Player->RemoveItemByIndex( nRemoveIndex );
        }
    }
}

void CUI_ID_FRAME_Bargaining::RenewItems()
{
    // 恢复失效物品
    if( !IsUILoad() )
        return;

    CPackItemEnableManager::Instance()->RefreshAllPackEnables();
    s_CUI_ID_FRAME_Pet.RefreshIconInfo();
}

void CUI_ID_FRAME_Bargaining::SetSelectMount( ControlIconDrag::S_ListImg* pItem )
{
    if( !IsUILoad() )
        return;

    // 清空
    if( !pItem )
    {
        if( m_pSelectMount && m_pSelectMount->m_pkIconInfo )
        {
            m_pSelectMount->m_pkIconInfo->SetColorFrameType( eColorFrame_None );
        }
        m_pSelectMount = NULL;
        m_pID_BUTTON_SeekMyPet->SetEnable( false );
        m_pID_BUTTON_SeekPlayerPet->SetEnable( false );
        return;
    }

    // 是自己的坐骑
    int nIndex = m_pID_LISTIMG_MyPet->GetItemIndex( pItem );
    if( nIndex >= 0 && nIndex < m_pID_LISTIMG_MyPet->GetItemCnt() )
    {
        m_pID_BUTTON_SeekMyPet->SetEnable( true );
        m_pID_BUTTON_SeekPlayerPet->SetEnable( false );
    }
    else
    {
        // 是对方的坐骑
        nIndex = m_pID_LISTIMG_PlayerPet->GetItemIndex( pItem );
        if( nIndex >= 0 && nIndex < m_pID_LISTIMG_PlayerPet->GetItemCnt() )
        {
            m_pID_BUTTON_SeekMyPet->SetEnable( false );
            m_pID_BUTTON_SeekPlayerPet->SetEnable( true );
        }
        else
        {
            return;
        }
    }

    // 设置选中框
    if( m_pSelectMount && m_pSelectMount->m_pkIconInfo )
    {
        m_pSelectMount->m_pkIconInfo->SetColorFrameType( eColorFrame_None );
    }
    m_pSelectMount = pItem;
    if( m_pSelectMount->m_pkIconInfo )
    {
        m_pSelectMount->m_pkIconInfo->SetColorFrameType( eColorFrame_Select );
    }
}

// 增加本地保存自己的交易物品
void CUI_ID_FRAME_Bargaining::AddSelfItem( __int64 nGuid )
{
    std::vector<__int64>::iterator it = m_selfItems.begin();
    for( ; it!= m_selfItems.end(); ++it )
    {
        if( *it == nGuid )
            return;
    }
    m_selfItems.push_back( nGuid );
}

// 移除本地保存自己的交易物品
void CUI_ID_FRAME_Bargaining::RemoveSelfItem( __int64 nGuid )
{
    if( m_selfItems.empty() )
        return;

    std::vector<__int64>::iterator it = m_selfItems.begin();
    for( ; it!= m_selfItems.end(); ++it )
    {
        if( *it == nGuid )
        {
            m_selfItems.erase( it );
            return;
        }
    }
}

std::string CUI_ID_FRAME_Bargaining::GetPetName( const SPetItem &pet )
{
	ItemDefine::SPetMonster *pPetMonster = GettheItemDetail().GetPetById(pet.baseInfo.petId);
	char temp[64]={0};
	if(pPetMonster != NULL)
	{
		if (strcmp(pPetMonster->GetName(),pet.GetPetName())!= 0)
		{
			MeSprintf_s(temp,sizeof(temp),"%s(%s)",pet.GetPetName(),pPetMonster->GetName());
		}
		else
		{
			MeSprintf_s(temp,sizeof(temp),"%s",pet.GetPetName());
		}
	}
	else
	{
		MeSprintf_s(temp,sizeof(temp),"%s",pet.GetPetName());
	}
	return temp;
}

// 是否为自己的交易物品
bool CUI_ID_FRAME_Bargaining::IsSelfItemInBargaining( __int64 nGuid )
{
    if( !IsVisable() || nGuid <= 0 )
        return false;

    std::vector<__int64>::iterator it = m_selfItems.begin();
    for( ; it!= m_selfItems.end(); ++it )
    {
        if( *it == nGuid )
        {
            return true;
        }
    }
    return false;
}

void CUI_ID_FRAME_Bargaining::AddPetToBargain( int petIdx )
{
	if ( m_petIDList.size() >= BargainingDefine::MaxPetCount )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, 
			theXmlString.GetString(eText_Bargain_AddFailed) );
		return;		//超过4个限制不允许再加入了
	}

	SPetItem &pet = thePlayerRole.GetPetByIndex(petIdx);
	// 放入物品
	MsgBargainingDataReq msg;
	msg.uchBargainintType = BargainingDefine::BargainingPet;
	msg.uchBargainingIndex = m_pID_LISTIMG_Me->GetItemCnt() + m_petIDList.size();
	msg.uchBagType = BT_PetBag;
	msg.uchIndex = petIdx;
	msg.n64Guid = pet.GetPetGuid();
	GettheNetworkInput().SendMsg( &msg );

}

void CUI_ID_FRAME_Bargaining::AddPetToBargainAck( int petIdx )
{
	//当加入成功的时候刷新列表
	m_petIDList.push_back(petIdx);
	RefreshPetListUI();

	s_CUI_ID_FRAME_SelectPet.Refresh(true);
}

void CUI_ID_FRAME_Bargaining::CallBackPetFromBargain( int petIdx )
{
	int count = (int)m_petIDList.size();
	for ( int i = 0; i < count; i ++ )
	{
		if ( m_petIDList[i] == petIdx )
		{
			m_petIDList.erase( m_petIDList.begin() + i );
			RefreshPetListUI();
			MsgRemoveBargainingDataReq msg;
			msg.uchBargainingIndex = i + m_pID_LISTIMG_Player->GetItemCnt();;
			GettheNetworkInput().SendMsg( &msg );
			break;
		}
	}
	RefreshPetListUI();

}

bool CUI_ID_FRAME_Bargaining::IsPetInBargain( int petIdx )
{
	int count = (int)m_petIDList.size();
	for ( int i = 0; i < count; i ++ )
	{
		if ( m_petIDList[i] == petIdx )
		{
			return true;
		}
	}
	return false;
}

void CUI_ID_FRAME_Bargaining::RefreshPetListUI()
{
	int count = (int)m_petIDList.size();
	m_pID_LIST_SelfPet->Clear();
	ControlList::S_List	stItem;
	for ( int i = 0; i < count; i ++ )
	{
		//m_pID_LIST_SelfPet
		SPetItem &pet = thePlayerRole.GetPetByIndex(m_petIDList[i]);

		if(!IsValidPet(pet))
			continue;

		stItem.clear();
		if(pet.baseInfo.isActive)	//出战的是不可以交易的
			continue;
		stItem.SetData(/*pet.GetPetName()*/GetPetName(pet).c_str(), 0, &pet, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

		m_pID_LIST_SelfPet->AddItem(&stItem, NULL, false);
	}

	//重置后没有选中项，查看不可用
	m_pID_BUTTON_SeekMyPet->SetEnable(false);
}

// 仅为重载
bool CUI_ID_FRAME_Bargaining::IsPackItemBeUsing( __int64 nGuid )
{
    return IsSelfItemInBargaining( nGuid );
}
