/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\Pack.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Pack.h"
#include "Shop.h"
#include "MessageBox.h"
#include "InputBox.h"
#include "PrivateShop.h"
#include "PlayerPrivateShop.h"
#include "Bargaining.h"
#include "Compound.h"
#include "ItemDetail.h"
#include "RestoreColdDown.h"
#include "Me3d/MoreAction.h"
#include "GameMain.h"
#include "XmlStringLanguage.h"
#include "PlayerRole.h"
#include "MeUi/ControlIconDragManager.h"
#include "../Player.h"
#include "PlayerMgr.h"
#include "Main.h"
#include "ChatInfoBox.h"
#include "GlobalDef.h"
#include "ui/FiveXing.h"
#include "SystemConfig.h"
#include "FuncPerformanceLog.h"
#include "ItemDetail.h"
#include "GameMain.h"
#include "UIStorage.h"
#include "../NpcCoord.h"
#include "../ShowScreenText.h"
#include "Task.h"
#include "MeUi/MouseManager.h"
#include "SeekEquip.h"
#include "Group_Me.h" 
#include "EquipmentDoll.h"
#include "Main.h"
#include "exmain.h"
#include "Progress.h"
#include "Pack_Ex.h"
#include "../Cfg.h"
#include "ActionUI.h"
#include "ui/Pet.h" 
#include "chat_particular.h"
#include "baseProperty.h"
#include "TimeEx.h"
#include "../color_config.h"
#include "Me3d/Engine/RendererDx.h"
#include "Me3d/MoreAction.h"
#include "Dxsdk/dinput.h"
#include "Meui/ExpressionManager.h"
#include "ChatMessageMgr.h"
#include "Message_Chat.h"
#include "Skill.h"
#include "ui/Star.h"
#include "ui/BatchShop.h"
#include "Bargaining.h"
// #include "ChatSystem.h"
#include "GoldPlating.h"
#include "GameSetting.h"
#include "Speaker.h"
#include "DataCenter.h"
#include "ui/Decompound.h"
#include "ui/MoveStar.h"
//#include "ui/WebAward.h"
//#include "ui/Guild.h"
#include "ui/SpecialRepair.h"
#include "EquipUpgradeConfig.h"
#include "ui/EquipUpgrade.h"
#include "SkillEquipUpdate.h"
#include "SkillEquipChange.h"
#include "FiveXingChange.h"
#include "FiveXingUpdate.h"
#include "FiveXingDisplace.h"
#include "MoveStarUpgrade.h"
#include "StarMaterialUpgrade.h"
#include "MailMain.h"
#include "GivePresent.h"
#include "IntensifyStar.h"
#include "WealthProtect.h"
#include "PreventWallow.h"
#include "InfoList.h"
#include "Pet.h"
#include "ui/Soul.h"
#include "ui/Hole.h"
#include "Ui/Gem.h"
#include "Ui/GemRemove.h"
#include "Ui/GemReplace.h"
#include "Ui/Purple.h"
#include "Ui/Repurple.h"
#include "Ui/EquipCopy.h"
#include "Ui/EquipReturn.h"
#include "Ui/Symbol.h"
#include "Ui/Amulet.h"
#include "Ui/GemUp.h"
#include "Ui/GemMaterialUp.h"
#include "MainMenu.h"
#include "SoundConfig.h"
#include "BargainingMessage.h"
#include "SystemStallage.h"
#include "EspecialTask.h"
#include "ItemDetailConfig.h"
#include "IdentifyQuality.h"
#include "zhujiangtujian.h"
#include "zhujiangbianshen.h"
#include "PocketShop.h"
#include "SuAnimal.h"
#include "zhujiangUp.h"
#include "Ui/TransferStar.h"
#include "Ui/MountStrengthen.h"
#include "Ui/jiebang.h"
#include "Ui/GemRemove.h"
#include "RandAttribute.h"
#include "SelectChannel.h"
#include "Ui/AddQuestEntrust.h"
#include "ui/mountmovestar.h"
#include "SuperPassword.h"
extern char* GetFullFileName(const char* filename);
#define StorageRulePara_A  10204
#define StorageRulePara_B  9.8

extern CHeroGame* theApp;
extern GAME_STATE	g_GameState;
extern bool g_bMessageChat;

extern int PlayEffect ( const char* pEffectName, 
					   CPlayer* pSrcPlayer = NULL, 
					   float fScale = 0 ,
					   DWORD dwFlyTime = 0,
					   CPlayer* pDestPlayer = NULL,
					   int nSlot = 0
					   ,bool bCalDist = true);
extern short GetKeyboardInput(int iKey);
extern ControlIconDragManager theIconDragManager;

//静态全局变量负责跟踪当前使用的物品
static ItemDefine::SItemCommon *sItemCommon = NULL;

static POINT s_ptSplitItemPos;
static POINT s_ptSplitMousePos;
static int s_nPackItemHeightMaxShowCount = 0;

struct S_DstSrcIndex
{
	unsigned int nDstIndex;
	unsigned int nSrcIndex;
	ControlListImage* pBagListImg;
	CItemBag2* pBag;
	int bagType;
};

struct BagInfo
{
	ControlListImage* pBagListImg;
	CItemBag2* pBag;
	int bagType;
};
static bool sendMendMsg( const char bPressYesButton, void *pData )
{
	if( bPressYesButton )
	{
		MsgRepairItem msg;	
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
		if(pMe)
			msg.header.stID =  pMe->GetID();
		msg.eType = MsgRepairItem::RT_All;
		msg.bIsCostRmb = false;
		GettheNetworkInput().SendMsg(&msg);

		return true;
	}
	return false;
}
void CUI_ID_FRAME_PACK::EnableSplitItem()
{
	ClearMotion();
	s_CUI_ID_FRAME_SHOP.SetRepair(false);

	m_bSplitItem = true;
	theMouseManager.SetCanSetCursor( true );
	theMouseManager.SetUICursor(MouseManager::Type_Split);
	theMouseManager.SetCanSetCursor( false );

	if (s_CUI_ID_FRAME_PACK.m_pID_CHECKBOX_Material->IsChecked())
		s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Material->SetEnableDrag(false);
	else if (s_CUI_ID_FRAME_PACK.m_pID_CHECKBOX_Task->IsChecked())
		s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Task->SetEnableDrag(false);
	else
		s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_PACK->SetEnableDrag(false);
}

void CUI_ID_FRAME_PACK::DisableSplitItem()
{
	if( !m_pID_FRAME_PACK )
		return;
	ClearMotion();
	theMouseManager.SetCanSetCursor( true );
	theMouseManager.SetUICursor(MouseManager::Type_Arrow);
	theMouseManager.SetCanSetCursor( false );

	if (s_CUI_ID_FRAME_PACK.m_pID_CHECKBOX_Material->IsChecked())
		s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Material->SetEnableDrag(true);
	else if (s_CUI_ID_FRAME_PACK.m_pID_CHECKBOX_Task->IsChecked())
		s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Task->SetEnableDrag(true);
	else
		s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_PACK->SetEnableDrag(true);
}

void CUI_ID_FRAME_PACK::EnableLockItem()
{
	ClearMotion();
	s_CUI_ID_FRAME_SHOP.SetRepair(false);
	theMouseManager.SetCanSetCursor( true );
	theMouseManager.SetUICursor(MouseManager::Type_LockItem);
	theMouseManager.SetCanSetCursor( false );

	m_bLockItem = true;

	if (s_CUI_ID_FRAME_PACK.m_pID_CHECKBOX_Material->IsChecked())
		s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Material->SetEnableDrag(false);
	else if (s_CUI_ID_FRAME_PACK.m_pID_CHECKBOX_Task->IsChecked())
		s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Task->SetEnableDrag(false);
	else
		s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_PACK->SetEnableDrag(false);
}

void CUI_ID_FRAME_PACK::DisableLockItem()
{
	ClearMotion();
	theMouseManager.SetCanSetCursor( true );
	theMouseManager.SetUICursor(MouseManager::Type_Arrow);
	theMouseManager.SetCanSetCursor( false );

	if (s_CUI_ID_FRAME_PACK.m_pID_CHECKBOX_Material->IsChecked())
		s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Material->SetEnableDrag(true);
	else if (s_CUI_ID_FRAME_PACK.m_pID_CHECKBOX_Task->IsChecked())
		s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Task->SetEnableDrag(true);
	else
		s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_PACK->SetEnableDrag(true);
}

void CUI_ID_FRAME_PACK::EnableUnLockItem()
{
	ClearMotion();
	s_CUI_ID_FRAME_SHOP.SetRepair(false);
	theMouseManager.SetCanSetCursor( true );
	theMouseManager.SetUICursor(MouseManager::Type_UnLockItem);
	theMouseManager.SetCanSetCursor( false );

	m_bUnLockItem = true;

	if (s_CUI_ID_FRAME_PACK.m_pID_CHECKBOX_Material->IsChecked())
		s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Material->SetEnableDrag(false);
	else if (s_CUI_ID_FRAME_PACK.m_pID_CHECKBOX_Task->IsChecked())
		s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Task->SetEnableDrag(false);
	else
		s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_PACK->SetEnableDrag(false);
}

void CUI_ID_FRAME_PACK::DisableUnLockItem()
{
	ClearMotion();
	theMouseManager.SetCanSetCursor( true );
	theMouseManager.SetUICursor(MouseManager::Type_Arrow);
	theMouseManager.SetCanSetCursor( false );

	if (s_CUI_ID_FRAME_PACK.m_pID_CHECKBOX_Material->IsChecked())
		s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Material->SetEnableDrag(true);
	else if (s_CUI_ID_FRAME_PACK.m_pID_CHECKBOX_Task->IsChecked())
		s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Task->SetEnableDrag(true);
	else
		s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_PACK->SetEnableDrag(true);
}

void CUI_ID_FRAME_PACK::ClearMotion()
{
	m_bLockItem = false;
	m_bUnLockItem = false;
	m_bSplitItem = false;
	m_bDestroyItem = false;
	m_bShiftRBSplitItem = false;
	m_pID_CHECKBOX_Decompose->SetCheck(false);
}

void CUI_ID_FRAME_PACK::UpdateIconInfo()
{
	POINT pos;
	RECT rect;
	GetCursorPos(&pos);
	GetWindowRect(g_hWnd, &rect);

	if(!theApp->IsFullScreen())
	{
		pos.x-=(rect.left + GetSystemMetrics(SM_CXBORDER));
		pos.y-=(rect.top + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CXBORDER));
	}

	POINT ptMouseOnSel;

	ControlListImage* m_pNow = NULL;
	if(m_PackGroup.IsVisible())
		m_pNow = m_pID_LISTIMG_PACK;
	else if(m_MaterialGroup.IsVisible())
		m_pNow = m_pID_LISTIMG_Material;
	else if(m_TaskGroup.IsVisible())
		m_pNow = m_pID_LISTIMG_Task;

	if (m_pNow && m_pNow->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true )
	{
		RECT rcItem;
		m_pNow->GetItemRect( pos.x, pos.y, rcItem );	
		// 偏移到中间
		rcItem.left += m_pNow->GetItemWidth() / 2;
		rcItem.top += m_pNow->GetItemHeight() / 2;
		
		bool bHaveCompare = false;
		ControlIconDrag::S_ListImg *pItem = m_pNow->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );

		int nSrcIndex = m_pNow->GetItemIndex( pItem );

		SCharItem scharItem;
		//背包有3个 应该先确定当前使用的背包的指针
		CItemBag2* pBag=NULL;
		if(m_PackGroup.IsVisible())
			pBag = &thePlayerRole.m_bag;
		else if(m_MaterialGroup.IsVisible())
			pBag = &thePlayerRole.m_bagMaterial;
		else if(m_TaskGroup.IsVisible())
			pBag = &thePlayerRole.m_bagTask;
		if(!pBag)
			return;

		if (pBag->IsHaveItem(nSrcIndex))
		{
			pBag->GetItem( nSrcIndex, &scharItem );

			ItemDefine :: SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( scharItem.itembaseinfo.ustItemID );

			if( pItemDetail 
				&& 
				( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_WEAPON 
				|| pItemDetail->ucItemType == ItemDefine::ITEMTYPE_ARMOUR
				)
				)
			{
                bool bEnable = CPackItemEnableManager::Instance()->IsPackItemEnable( pBag, nSrcIndex );
				pItem->SetData( &scharItem, ( bEnable ? eIcon_Enable : eIcon_Disable ), 
					eTipFlag_Normal, false, theApp->GetPlayerMgr()->GetMyID() ); 				
			}
			else
			{
                bool bEnable = CPackItemEnableManager::Instance()->IsPackItemEnable( pBag, nSrcIndex );
				pItem->SetData( &scharItem, bEnable ? eIcon_Enable : eIcon_Disable );
			}
		}
	}
}

int CUI_ID_FRAME_PACK::GetBagType( ControlListImage* pImageSender )
{
	if( !pImageSender )
		return -1;
	if( !m_pID_FRAME_PACK )
		return -1;

	if( pImageSender == m_pID_LISTIMG_PACK )
		return BT_NormalItemBag;
	else if( pImageSender == m_pID_LISTIMG_Material )
		return BT_MaterialBag;
	else if( pImageSender == m_pID_LISTIMG_Task )
		return BT_TaskBag;
	return -1;
}

ControlListImage* CUI_ID_FRAME_PACK::GetListImageByBagType( int iBagType )
{
	if( !m_pID_FRAME_PACK )
		return NULL;

	switch(iBagType)
	{
	case BT_NormalItemBag:
		return m_pID_LISTIMG_PACK;
		break;
	case BT_MaterialBag:
		return m_pID_LISTIMG_Material;
		break;
	case BT_TaskBag:
		return m_pID_LISTIMG_Task;
		break;
	default:
		break;
	}
	return NULL;
}

bool CUI_ID_FRAME_PACK::ChangeItemIdbyGuid( int iBagType, __int64 nOldGuid, uint16 ustNewItemID, __int64 nNewGuid )
{
	if( !m_pID_FRAME_PACK )
		return false;

	switch( iBagType )
	{
	case BT_NormalItemBag:
		{
			int index = thePlayerRole.m_bag.GetItemIndexByGUID(nOldGuid);
			if( index < 0 || index >= thePlayerRole.m_bag.GetNowBagSize() )
				return false;

			// 根据GUID查对应index
			//thePlayerRole.m_bag.m_bEnables[index] = true;
			SCharItem* pItem = thePlayerRole.m_bag.GetCharItemFromIdx( index );
			if( !pItem )
				return false;

			pItem->itembaseinfo.ustItemID = ustNewItemID;
			pItem->itembaseinfo.nOnlyInt = nNewGuid;
			RefreshNormalPackByIndex( index );
		}
		break;
	case BT_MaterialBag:
		{
			int index = thePlayerRole.m_bagMaterial.GetItemIndexByGUID(nOldGuid);
			if( index < 0 || index >= thePlayerRole.m_bagMaterial.GetNowBagSize() )
				return false;

			//thePlayerRole.m_bagMaterial.m_bEnables[index] = true;
			SCharItem* pItem = thePlayerRole.m_bagMaterial.GetCharItemFromIdx( index );
			if( !pItem )
				return false;
			pItem->itembaseinfo.ustItemID = ustNewItemID;
			pItem->itembaseinfo.nOnlyInt = nNewGuid;
			RefreshMaterialPackByIndex( index );
		}
		break;
	case BT_TaskBag:
		{
			int index = thePlayerRole.m_bagTask.GetItemIndexByGUID(nOldGuid);
			if( index < 0 || index >= thePlayerRole.m_bagTask.GetNowBagSize() )
				return false;

			//thePlayerRole.m_bagTask.m_bEnables[index] = true;
			SCharItem* pItem = thePlayerRole.m_bagTask.GetCharItemFromIdx( index );
			if( !pItem )
				return false;
			pItem->itembaseinfo.ustItemID = ustNewItemID;
			pItem->itembaseinfo.nOnlyInt = nNewGuid;
			RefreshTaskPackByIndex( index );
		}
		break;
	default:
		break;
	}
	return true;
}

ControlIconDrag::S_ListImg* CUI_ID_FRAME_PACK::GetItemByIndex( int iBagType, int index )
{
	if( index == -1 )
		return NULL;
	if( !m_pID_FRAME_PACK )
		return NULL;

	switch(iBagType)
	{
	case BT_NormalItemBag:
		return m_pID_LISTIMG_PACK->GetItemByIndex(index);
		break;
	case BT_MaterialBag:
		return m_pID_LISTIMG_Material->GetItemByIndex(index);
		break;
	case BT_TaskBag:
		return m_pID_LISTIMG_Task->GetItemByIndex(index);
		break;
	default:
		break;
	}
	return NULL;
}

ControlIconDrag::S_ListImg* CUI_ID_FRAME_PACK::GetItemById( int iBagType, int id )
{
	if( !m_pID_FRAME_PACK )
		return NULL;

	switch(iBagType)
	{
	case BT_NormalItemBag:
		return m_pID_LISTIMG_PACK->GetItemById(id);
		break;
	case BT_MaterialBag:
		return m_pID_LISTIMG_Material->GetItemById(id);
		break;
	case BT_TaskBag:
		return m_pID_LISTIMG_Task->GetItemById(id);
		break;
	default:
		break;
	}
	return NULL;
}

bool CUI_ID_FRAME_PACK::IsListImageByBagType(int iBagType, ControlObject* pObject )
{
	if( !m_pID_FRAME_PACK || !pObject )
		return false;

	switch(iBagType)
	{
	case BT_NormalItemBag:
		return (m_pID_LISTIMG_PACK == pObject);
		break;
	case BT_MaterialBag:
		return (m_pID_LISTIMG_Material == pObject);
		break;
	case BT_TaskBag:
		return (m_pID_LISTIMG_Task == pObject);
		break;
	default:
		break;
	}
	return false;
}

int CUI_ID_FRAME_PACK::GetIndexByItem( int iBagType, ControlIconDrag::S_ListImg* pListImg )
{
	if( !pListImg )
		return -1;
	if( !m_pID_FRAME_PACK )
		return -1;

	switch(iBagType)
	{
	case BT_NormalItemBag:
		return m_pID_LISTIMG_PACK->GetItemIndex(pListImg);
		break;
	case BT_MaterialBag:
		return m_pID_LISTIMG_Material->GetItemIndex(pListImg);
		break;
	case BT_TaskBag:
		return m_pID_LISTIMG_Task->GetItemIndex(pListImg);
		break;
	default:
		break;
	}
	return -1;
}

ControlIconDrag::S_ListImg* CUI_ID_FRAME_PACK::GetItemByXY( int iBagType, unsigned int nX, unsigned int nY )
{
	if( !m_pID_FRAME_PACK )
		return NULL;

	switch(iBagType)
	{
	case BT_NormalItemBag:
		return m_pID_LISTIMG_PACK->GetItem(nX, nY);
		break;
	case BT_MaterialBag:
		return m_pID_LISTIMG_Material->GetItem(nX, nY);
		break;
	case BT_TaskBag:
		return m_pID_LISTIMG_Task->GetItem(nX, nY);
		break;
	default:
		break;
	}
	return NULL;
}


bool CUI_ID_FRAME_PACK::IsSameFrame( ControlFrame* pFrame )
{
	if( !pFrame || !m_pID_FRAME_PACK )
		return false;
	return (pFrame == m_pID_FRAME_PACK);
}

void CUI_ID_FRAME_PACK::SetFrameArrayMode( const int nMode )
{
	if( !m_pID_FRAME_PACK )
		return;
	m_pID_FRAME_PACK->SetArrayMode(nMode);
}

bool CUI_ID_FRAME_PACK::IsOpenPackByBagType( int iBagType )
{
	if( !m_pID_FRAME_PACK )
		return false;

	switch(iBagType)
	{
	case BT_NormalItemBag:
		return m_pID_CHECKBOX_Zhuangbei->IsChecked();
		break;
	case BT_MaterialBag:
		return m_pID_CHECKBOX_Material->IsChecked();
		break;
	case BT_TaskBag:
		return m_pID_CHECKBOX_Task->IsChecked();
		break;
	default:
		break;
	}
	return false;
}

void CUI_ID_FRAME_PACK::SwitchToBag( int iBagType )
{
	if( !m_pID_FRAME_PACK )
		return;

	switch( iBagType )
	{
	case BT_NormalItemBag:
		m_BagTabGroup.TogglePage(m_pID_CHECKBOX_Zhuangbei);
		break;
	case BT_MaterialBag:
		m_BagTabGroup.TogglePage(m_pID_CHECKBOX_Material);
		break;
	case BT_TaskBag:
		m_BagTabGroup.TogglePage(m_pID_CHECKBOX_Task);
		break;
	default:
		break;
	}
}
bool PackAddValues( const bool bPressYesButton, void *pData )
{
	guardfunc;
	if( bPressYesButton )
	{
		MsgReqResetTime *pMsg = (MsgReqResetTime*)pData;
		GettheNetworkInput().SendMsg( pMsg );
	}
	return false;
	unguard;
}

BOOL PackMoveItem(INT nCount, MsgMoveGoodsReq* pMsg )
{
	guardfunc;
	if( nCount == -1 )
	{
		nCount = thePlayerRole.m_bag.m_pPackItem[pMsg->ustSrcIndex].itembaseinfo.ustItemCount;
	}
	if( nCount < 0 || !pMsg)
		return FALSE;

    CItemBag2* pBag = NULL;
    switch( pMsg->ucItemBagType )
    {
    case BT_NormalItemBag:
        pBag = &thePlayerRole.m_bag;
        break;
    case BT_MaterialBag:
        pBag = &thePlayerRole.m_bagMaterial;
        break;
    case BT_TaskBag:
        pBag = &thePlayerRole.m_bagTask;
        break;
    default:
        break;
    }

	if(!pBag)
		return FALSE;

    // 检查绑定不绑定合并
    if( CUI_ID_FRAME_PACK::IsSameItemDifInBound( pBag->m_pPackItem[pMsg->ustSrcIndex].itembaseinfo.nOnlyInt, pMsg->ustSrcIndex,
        pBag->m_pPackItem[pMsg->ustDstIndex].itembaseinfo.nOnlyInt, pMsg->ustDstIndex ) )
    {
        CUI_ID_FRAME_PACK::MoveSameItemDifInBoundData data;
        data.indexScr = pMsg->ustSrcIndex;
        data.indexDst = pMsg->ustDstIndex;
        data.pBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType( pMsg->ucItemBagType );
        data.pBag = pBag;
        data.bagType = pMsg->ucItemBagType;
        data.msg = *pMsg;
        data.nCount = nCount;
        CUI_ID_FRAME_PACK::ShowConfirmBoundMessageBox( data );
    }
    else
    {
        if( CItemBag2::MoveItem( &pBag->m_pPackItem[pMsg->ustDstIndex],
            &pBag->m_pPackItem[pMsg->ustSrcIndex],NULL,NULL,"", nCount ) != -1 )
        {
            pMsg->ustCount =  nCount;
            GettheNetworkInput().SendMsg( pMsg );

            s_CUI_ID_FRAME_PACK.RefreshPackByIndex(pMsg->ustSrcIndex);
            s_CUI_ID_FRAME_PACK.RefreshPackByIndex(pMsg->ustDstIndex);
        }
    }
	return TRUE;
	unguard;
}

BOOL PackMoveItem(INT nCount, MsgMoveGoodsReq* pMsg, ControlListImage* pBagListImg, CItemBag2* pBag, int bagType, BOOL bIsSplit = FALSE);
BOOL PackMoveItem(INT nCount, MsgMoveGoodsReq* pMsg, ControlListImage* pBagListImg, CItemBag2* pBag, int bagType, BOOL bIsSplit)
{
	guardfunc;
    // 检查包大小
    if( pMsg->ustSrcIndex >= pBag->GetNowBagSize() || pMsg->ustDstIndex >= pBag->GetNowBagSize() )
        return FALSE;

	if( nCount == -1 )
	{
		nCount = pBag->m_pPackItem[pMsg->ustSrcIndex].itembaseinfo.ustItemCount;
	}
	if( nCount <= 0 || !pMsg)
		return FALSE;

    // 如果原先目标位置有物品，则不需要锁定物品
    if( bIsSplit && 
        (pBag->m_pPackItem[pMsg->ustDstIndex].itembaseinfo.ustItemCount > 0 || pBag->m_pPackItem[pMsg->ustSrcIndex].itembaseinfo.ustItemCount == nCount) )
        bIsSplit = FALSE;

    // 检查绑定不绑定合并
    if( CUI_ID_FRAME_PACK::IsSameItemDifInBound( pBag->m_pPackItem[pMsg->ustSrcIndex].itembaseinfo.nOnlyInt, pMsg->ustSrcIndex,
        pBag->m_pPackItem[pMsg->ustDstIndex].itembaseinfo.nOnlyInt, pMsg->ustDstIndex ) )
    {
        CUI_ID_FRAME_PACK::MoveSameItemDifInBoundData data;
        data.indexScr = pMsg->ustSrcIndex;
        data.indexDst = pMsg->ustDstIndex;
        data.pBagListImg = pBagListImg;
        data.pBag = pBag;
        data.bagType = bagType;
        data.msg = *pMsg;
        data.nCount = nCount;
        data.bIsSplit = bIsSplit;
        CUI_ID_FRAME_PACK::ShowConfirmBoundMessageBox( data );
    }
    else
    {
		//移动物品的位置 需要处理物品本身的位置的属性
        if( CItemBag2::MoveItem( &pBag->m_pPackItem[pMsg->ustDstIndex],
            &pBag->m_pPackItem[pMsg->ustSrcIndex],NULL,NULL,"", nCount ) != -1 )
        {
            pMsg->ustCount =  nCount;

			pBag->m_pPackItem[pMsg->ustSrcIndex].itembaseinfo.stPacketIdx = pMsg->ustSrcIndex;
			pBag->m_pPackItem[pMsg->ustDstIndex].itembaseinfo.stPacketIdx = pMsg->ustDstIndex;

            if( pBag->GetCharItemFromIdx( pMsg->ustSrcIndex ) )
                pMsg->nGuID = pBag->GetCharItemFromIdx( pMsg->ustSrcIndex )->itembaseinfo.nOnlyInt;
            GettheNetworkInput().SendMsg( pMsg );

            if( bIsSplit )
            {
                // 锁定物品无法使用，等收到服务端反馈
                pBag->m_pPackItem[pMsg->ustSrcIndex].storageinfo.bIsLocked = true;
                //pBag->m_bEnables[pMsg->ustSrcIndex] = false;
                pBag->m_pPackItem[pMsg->ustDstIndex].storageinfo.bIsLocked = true;
                //pBag->m_bEnables[pMsg->ustDstIndex] = false;
                theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
            }

            s_CUI_ID_FRAME_PACK.RefreshPackByIndex(pMsg->ustSrcIndex, pBagListImg, pBag, bagType);
            s_CUI_ID_FRAME_PACK.RefreshPackByIndex(pMsg->ustDstIndex, pBagListImg, pBag, bagType);
        }
    }
	return TRUE;
	unguard;
}

bool UIPACK_MovePackItem( const char* szInputData, void *pData )
{
	guardfunc;

	int nCount = atoi( szInputData );
	if ( nCount <= 0 )
		return false;

	if( !s_CUI_ID_FRAME_PACK.GetFrame() )
		return false;

	ControlListImage* pListPack = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag);
	if( !pListPack )
		return false;

	if (s_CUI_ID_FRAME_PACK.GetSplitItem())
	{
		ControlIconDrag::S_ListImg* pListImg =
			s_CUI_ID_FRAME_PACK.GetItemByXY( BT_NormalItemBag, s_ptSplitItemPos.x, s_ptSplitItemPos.y);
		if ( pListImg && !pListImg->IsNull() &&
			!theIconDragManager.IsIconDraging() )
		{
			if ( pListImg->m_eEnable == eIcon_Enable ||
				pListPack->IsDisableCanbePick() )
			{
				RECT realRC;
				pListPack->GetItemRect(
					s_ptSplitItemPos.x, s_ptSplitItemPos.y, realRC);

				POINT realPos;
				realPos.x = realRC.left;
				realPos.y = realRC.top;

				pListPack->SetEnableDrag(true);
				theIconDragManager.SetDrag( pListPack,
					pListImg, s_ptSplitItemPos, realPos, s_ptSplitMousePos );
				theIconDragManager.SetDraging();

				s_CUI_ID_FRAME_PACK.DisableSplitItem();
				s_CUI_ID_FRAME_PACK.SetSplitCount(nCount);

				return true;
			}
		}
		return true;
	}

	MsgMoveGoodsReq* pMsg = (MsgMoveGoodsReq*)pData;
	PackMoveItem( nCount, pMsg );
	return true;
	unguard;
}

static bool UIPACK_SplitPackItem( const char* szInputData, void *pData )
{
	guardfunc;

	int nCount = atoi( szInputData );
	if ( nCount <= 0 )
		return false;

	BagInfo* pBagInfo = (BagInfo*)pData;

	ControlIconDrag::S_ListImg* pListImg =
		pBagInfo->pBagListImg->GetItem(s_ptSplitItemPos.x, s_ptSplitItemPos.y);
	if ( pListImg && !pListImg->IsNull() &&
		!theIconDragManager.IsIconDraging() )
	{
		if ( pListImg->m_eEnable == eIcon_Enable ||
			pBagInfo->pBagListImg->IsDisableCanbePick() )
		{
			RECT realRC;
			pBagInfo->pBagListImg->GetItemRect(
				s_ptSplitItemPos.x, s_ptSplitItemPos.y, realRC);

			POINT realPos;
			realPos.x = realRC.left;
			realPos.y = realRC.top;

			pBagInfo->pBagListImg->SetEnableDrag(true);
			theIconDragManager.SetDrag( pBagInfo->pBagListImg,
				pListImg, s_ptSplitItemPos, realPos, s_ptSplitMousePos );
			theIconDragManager.SetDraging();

			s_CUI_ID_FRAME_PACK.DisableSplitItem();
			s_CUI_ID_FRAME_PACK.SetSplitCount(nCount);
			return true;
		}
	}
	return true;
	unguard;
}

bool UIPACK_BuyGoodsDefCallBackFun( const bool bPressYesButton, void *pData )
{
	guardfunc;
	MsgBuyOrSellGoods* pMsg = (MsgBuyOrSellGoods*)pData;
	if( !pMsg )
		return FALSE;
	if ( bPressYesButton == true )
	{
		pMsg->ustCount = 1;
		GettheNetworkInput().SendMsg( pMsg );
	}
	return true;
	unguard;
}

bool UIPACK_TryDropItem(  const bool bPressYesButton, void *pData  )
{
	guardfunc;
	if( bPressYesButton == TRUE )
	{
		INT *pIdx = (INT*)pData;
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
		if ( !pMe )
			return false;
		pMe->TryDropItem( *pIdx );
	}
	return true;
	unguard;
}


bool RemoveSomething( const char bPressYesButton, void *pData )
{
	if (bPressYesButton && pData)
	{
		MsgMoveGoodsReq msg;
		::CopyMemory(&msg,pData,sizeof(MsgMoveGoodsReq));
		GettheNetworkInput().SendMsg( &msg );
	}
	return true;
}

bool LockItem( const char bPressYesButton, void *pData )
{
	if(bPressYesButton && pData)
	{
		MsgLockItemReq msg;
		::CopyMemory(&msg,pData,sizeof(MsgLockItemReq));
		GettheNetworkInput().SendMsg( &msg );
	}
	return true;
}

bool UnLockItem( const char bPressYesButton, void *pData )
{
	if(bPressYesButton && pData)
	{
		MsgUnLockItemReq msg;
		::CopyMemory(&msg,pData,sizeof(MsgUnLockItemReq));
		GettheNetworkInput().SendMsg( &msg );
	}
	return true;
}

//从别的城市的仓库取物品
bool GetItemFromTheOtherStorage( const bool bPressYes, void *pData)
{
	guardfunc;
	if( bPressYes == true )
	{
		if (theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->IsDead())
		{
			return false;
		}
		S_DstSrcIndex *pDstSrcIndex = (S_DstSrcIndex*)pData;
		//玩家身上的钱
		DWORD dwMoneyOnSelf = thePlayerRole.GetData(CPlayerRole::TYPE_MONEY); 
		if (s_CUI_ID_FRAME_PACK.GetItemCost()  <= dwMoneyOnSelf )
		{
			if(pDstSrcIndex->nSrcIndex >= /*PAGESIZE*/STORAGE_ITEMGRID_MAX)
				return false;
			//向包裹里加物品
			SCharItem* pItem = NULL;
			pItem = &thePlayerRole.m_stStorage.stStorageItems[pDstSrcIndex->nSrcIndex];
			int nRes = thePlayerRole.m_bag.PushItem( *pItem, (unsigned short&)s_CUI_ID_FRAME_PACK.GetGoodsCount(),NULL,NULL,"", pDstSrcIndex->nDstIndex );
			if (nRes != ierr_Success)
			{
				return false;
			}
			//清除仓库里相关物品
			thePlayerRole.m_stStorage.stStorageItems[pDstSrcIndex->nSrcIndex].itembaseinfo.ustItemCount -= s_CUI_ID_FRAME_PACK.GetGoodsCount();
			if(thePlayerRole.m_stStorage.stStorageItems[pDstSrcIndex->nSrcIndex].itembaseinfo.ustItemCount == 0)
			{
				thePlayerRole.m_stStorage.stStorageItems[pDstSrcIndex->nSrcIndex].itembaseinfo.ustItemID = InvalidLogicNumber;
			}

			//发送消息给服务端 to playerchar2
			MsgMoveStorageItem msg;
			if( pItem )
				msg.nGuid = pItem->itembaseinfo.nOnlyInt;
			msg.enMoveType = MsgMoveStorageItem::Type_StorageToPack;
			msg.ustDstIndex = pDstSrcIndex->nDstIndex;
			msg.ustSrcIndex = pDstSrcIndex->nSrcIndex;
			msg.ustCount = s_CUI_ID_FRAME_PACK.GetGoodsCount();
			msg.nNpcID = thePlayerRole.GetNpcID();
			msg.dwMoney = s_CUI_ID_FRAME_PACK.GetItemCost();
			GettheNetworkInput().SendMsg( &msg );
			//将客户端费用清空
			if(s_CUI_ID_FRAME_PACK.GetMoveCount() - s_CUI_ID_FRAME_PACK.GetGoodsCount() == 0)
			{
				thePlayerRole.fCostOfFetchItem[pDstSrcIndex->nSrcIndex] = 0;
			}
			DWORD dwTemp = (DWORD)s_CUI_ID_FRAME_PACK.GetItemCost();
			//客户端玩家的钱扣除
			if(dwMoneyOnSelf > dwTemp)
			{
				dwMoneyOnSelf = dwMoneyOnSelf - dwTemp;
				thePlayerRole.SetMoneyOnPlayer(dwMoneyOnSelf);	
			}
			else
			{
				return false;
			}
			//刷新
			s_CUI_ID_FRAME_Storage.Refeash();
			s_CUI_ID_FRAME_PACK.Refeash();
			return true;
		}
		else
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eText_MoneyNotEnoungh ) );
			return false;
		}
	}

	return false;
	unguard;
}

bool StorageItemToPack(const char* szInputData, void *pData )
{
	guardfunc;
	if (theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->IsDead())
	{
		return false;
	}

	float dwNull =0.0f;

	S_DstSrcIndex *pDstSrcIndex = (S_DstSrcIndex*)pData;

	ControlListImage* pBagListImg = pDstSrcIndex->pBagListImg;
	CItemBag2* pBag = pDstSrcIndex->pBag;
	int bagType = pDstSrcIndex->bagType;

	//--------------判别输入的物品数量是否规范---------------------
	s_CUI_ID_FRAME_PACK.SetGoodsCount(atoi( szInputData ));
	if ( s_CUI_ID_FRAME_PACK.GetGoodsCount() <= 0 )
		return false;

	if(s_CUI_ID_FRAME_PACK.GetGoodsCount() > s_CUI_ID_FRAME_PACK.GetMoveCount())
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_OverCount) );
		return false;
	}
	//--------------------邮政仓库取物品--------------------------
	s_CUI_ID_FRAME_PACK.SetTempNpcId(thePlayerRole.m_stStorage.stStorageItems[pDstSrcIndex->nSrcIndex].storageinfo.nStorageNpcId);
	//同城取物品
	if(s_CUI_ID_FRAME_PACK.GetTempNpcId() == thePlayerRole.GetNpcID())
	{
		//向包裹里加物品
		SCharItem* pItem = NULL;
		pItem = &thePlayerRole.m_stStorage.stStorageItems[pDstSrcIndex->nSrcIndex];

		if (thePlayerRole.m_stStorage.stStorageItems[pDstSrcIndex->nSrcIndex].itembaseinfo.ustItemCount != s_CUI_ID_FRAME_PACK.GetGoodsCount()&&
			thePlayerRole.m_stStorage.stStorageItems[pDstSrcIndex->nSrcIndex].storageinfo.bIsLocked)
		{
			return false;
		}

		// 独占物品，但又是有堆叠数，取一个出来
		ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID(pItem->itembaseinfo.ustItemID);
		SCharItem newItem;
		bool bNeedLock = false;
		if ( pItemDetail && pItemDetail->IsExclusive() && pItem->itembaseinfo.ustItemCount > 1 )
		{
			memcpy(&newItem, pItem, sizeof(SCharItem));
			newItem.itembaseinfo.ustItemCount = 1;
			pItem = &newItem;
			bNeedLock = true;
		}

		int nRes = pBag->PushItem( *pItem, (unsigned short&)s_CUI_ID_FRAME_PACK.GetGoodsCount(), NULL,NULL,"",pDstSrcIndex->nDstIndex );
		if (nRes != ierr_Success)
		{
			return false;
		}

		if( bNeedLock )
		{
			// 锁定物品无法使用，等收到服务端反馈
			pBag->m_pPackItem[pDstSrcIndex->nDstIndex].storageinfo.bIsLocked = true;
			//pBag->m_bEnables[pDstSrcIndex->nDstIndex] = false;
			theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
		}

		//清除仓库里相关物品
		thePlayerRole.m_stStorage.stStorageItems[pDstSrcIndex->nSrcIndex].itembaseinfo.ustItemCount -= s_CUI_ID_FRAME_PACK.GetGoodsCount();
		if(thePlayerRole.m_stStorage.stStorageItems[pDstSrcIndex->nSrcIndex].itembaseinfo.ustItemCount == 0)
		{
			thePlayerRole.m_stStorage.stStorageItems[pDstSrcIndex->nSrcIndex].itembaseinfo.ustItemID = InvalidLogicNumber;
		}
		//发送消息给服务端 to playerchar2
		MsgMoveStorageItem msg;
		msg.nGuid = pItem->itembaseinfo.nOnlyInt;
		msg.enMoveType = MsgMoveStorageItem::Type_StorageToPack;
		msg.ustDstIndex = pDstSrcIndex->nDstIndex;
		msg.ustSrcIndex = pDstSrcIndex->nSrcIndex;
		msg.ustCount = s_CUI_ID_FRAME_PACK.GetGoodsCount();
		msg.nNpcID = thePlayerRole.GetNpcID();
		msg.dwMoney = 0; 
		msg.ucItemBagType = bagType;
		GettheNetworkInput().SendMsg( &msg );

		if ( pItemDetail && pItemDetail->ucItemType == ItemDefine::ITEMTYPE_RESTORE )
		{
			ItemDefine::SItemRestore* pItemRestore = (ItemDefine::SItemRestore*)pItemDetail;
			if ( pItemRestore->bHPAuto || pItemRestore->bMPAuto || pItemRestore->bAutoRelive )
			{
				thePlayerRole.refreshHotKey();
			}
		}
	}
	else//不同城市取物品
	{
		ItemDefine::SItemCommon *pItem = GettheItemDetail().GetItemByID(thePlayerRole.m_stStorage.stStorageItems[pDstSrcIndex->nSrcIndex].itembaseinfo.ustItemID);
		if ( !pItem )
			return false;

		if (thePlayerRole.m_stStorage.stStorageItems[pDstSrcIndex->nSrcIndex].itembaseinfo.ustItemCount != s_CUI_ID_FRAME_PACK.GetGoodsCount()&&
			thePlayerRole.m_stStorage.stStorageItems[pDstSrcIndex->nSrcIndex].storageinfo.bIsLocked)
		{
			return false;
		}

		//物品重量
		float fValue = pItem->dwCost;
		//不同城市取物品所花费用
		float fCostOfDistance = thePlayerRole.fCostOfFetchItem[pDstSrcIndex->nSrcIndex];
		//计算取物品所花费用 取消了异地仓库收取的价格
		float fUnitPrice = (fValue*fValue)*dwNull/(StorageRulePara_A+StorageRulePara_B*fValue) + fCostOfDistance*dwNull;
		s_CUI_ID_FRAME_PACK.SetItemCost(fUnitPrice*(float)s_CUI_ID_FRAME_PACK.GetGoodsCount());

		s_CUI_ID_FRAME_PACK.SetItemCost(0.0f);

		{
			if(pDstSrcIndex->nSrcIndex >= /*PAGESIZE*/STORAGE_ITEMGRID_MAX)
				return false;
			//向包裹里加物品
			SCharItem* pItem = NULL;
			pItem = &thePlayerRole.m_stStorage.stStorageItems[pDstSrcIndex->nSrcIndex];

			// 独占物品，但又是有堆叠数，取一个出来
			ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID(pItem->itembaseinfo.ustItemID);
			SCharItem newItem;
			bool bNeedLock = false;
			if ( pItemDetail && pItemDetail->IsExclusive() && pItem->itembaseinfo.ustItemCount > 1 )
			{
				memcpy(&newItem, pItem, sizeof(SCharItem));
				newItem.itembaseinfo.ustItemCount = 1;
				pItem = &newItem;
				bNeedLock = true;
			}


			int nRes = pBag->PushItem( *pItem, (unsigned short&)s_CUI_ID_FRAME_PACK.GetGoodsCount(), NULL,NULL,"",pDstSrcIndex->nDstIndex );
			if (nRes != ierr_Success)
			{
				return false;
			}

			if( bNeedLock )
			{
				// 锁定物品无法使用，等收到服务端反馈
				pBag->m_pPackItem[pDstSrcIndex->nDstIndex].storageinfo.bIsLocked = true;
				//pBag->m_bEnables[pDstSrcIndex->nDstIndex] = false;
				s_CUI_ID_FRAME_PACK.RefreshNormalPackByIndex(pDstSrcIndex->nDstIndex);	
			}

			//清除仓库里相关物品
			thePlayerRole.m_stStorage.stStorageItems[pDstSrcIndex->nSrcIndex].itembaseinfo.ustItemCount -= s_CUI_ID_FRAME_PACK.GetGoodsCount();
			if(thePlayerRole.m_stStorage.stStorageItems[pDstSrcIndex->nSrcIndex].itembaseinfo.ustItemCount == 0)
			{
				thePlayerRole.m_stStorage.stStorageItems[pDstSrcIndex->nSrcIndex].itembaseinfo.ustItemID = InvalidLogicNumber;
			}
			//发送消息给服务端 to playerchar2
			MsgMoveStorageItem msg;
			msg.nGuid = pItem->itembaseinfo.nOnlyInt;
			msg.enMoveType = MsgMoveStorageItem::Type_StorageToPack;
			msg.ustDstIndex = pDstSrcIndex->nDstIndex;
			msg.ustSrcIndex = pDstSrcIndex->nSrcIndex;
			msg.ustCount = s_CUI_ID_FRAME_PACK.GetGoodsCount();
			msg.nNpcID = thePlayerRole.GetNpcID();
			msg.dwMoney = 0;
			msg.ucItemBagType = bagType;
			GettheNetworkInput().SendMsg( &msg );
			//刷新
			s_CUI_ID_FRAME_Storage.Refeash();
			s_CUI_ID_FRAME_PACK.RefreshPackByIndex(pDstSrcIndex->nDstIndex, pDstSrcIndex->pBagListImg, pDstSrcIndex->pBag, pDstSrcIndex->bagType);
			return true;
		}
	}

	s_CUI_ID_FRAME_Storage.Refeash();
	s_CUI_ID_FRAME_PACK.RefreshPackByIndex(pDstSrcIndex->nDstIndex, pDstSrcIndex->pBagListImg, pDstSrcIndex->pBag, pDstSrcIndex->bagType);	
	return true;
	unguard;

}

bool StorageItemToPack_DefCallBackFun( const bool bPressYesButton, void *pData )
{
	guardfunc;
	if ( bPressYesButton == true )
	{
		StorageItemToPack( "1", pData );
	}
	return true;
	unguard;
}

void CUI_ID_FRAME_PACK::EnableDestroyItem()
{
	ClearMotion();
	s_CUI_ID_FRAME_SHOP.SetRepair(false);

	s_CUI_ID_FRAME_PACK.m_bDestroyItem = true;
	theMouseManager.SetUICursor(MouseManager::Type_Destroy);
}

void CUI_ID_FRAME_PACK::DisableDestroyItem()
{
	if( !m_pID_FRAME_PACK )
		return;
	ClearMotion();
	theMouseManager.SetUICursor(MouseManager::Type_Arrow);
}

bool UIPack_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	guardfunc;
	if ( bMsgUsed == true || g_GameState != G_MAIN )
		return false;
	if ( !s_CUI_ID_FRAME_PACK.IsVisable() )
		return false;
	switch( msg ) 
	{
	case WM_LBUTTONDOWN:
		{
			if ( !theIconDragManager.m_pLastSelItem || !theIconDragManager.GetRemoveIcon() )
				return false;

			ControlListImage* pBagListImg = 0;
			CItemBag2* pBag = 0;
			int bagType = 0;

			int nIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_NormalItemBag, theIconDragManager.m_pLastSelItem );
			if (nIndex != -1)
			{
				pBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag);
				pBag = &thePlayerRole.m_bag;
				bagType = BT_NormalItemBag;
			}
			else if ( (nIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem(BT_MaterialBag, theIconDragManager.m_pLastSelItem)) != -1 )
			{
				pBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_MaterialBag);
				pBag = &thePlayerRole.m_bagMaterial;
				bagType = BT_MaterialBag;
			}
			else if ( (nIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem(BT_TaskBag, theIconDragManager.m_pLastSelItem)) != -1)
			{
				pBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_TaskBag);
				pBag = &thePlayerRole.m_bagTask;
				bagType = BT_TaskBag;
			}
			else
			{
				return false;
			}

			SCharItem sItem;
			if( !pBag->GetItem( nIndex, &sItem ) )
                return false;
			if( sItem.itembaseinfo.ustItemID == InvalidLogicNumber )
				return false;

			theIconDragManager.ClearDrag();
			theIconDragManager.m_pLastSelItem = NULL;
			theIconDragManager.SetRemoveIcon(false);

			if( ( s_CUI_ID_FRAME_PACK.GetFrame() && 
					s_CUI_ID_FRAME_PACK.GetFrame()->PtInOnlyFrame( theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y )
				) || 
				( s_CUI_ID_FRAME_Exmain.PtInOnlyFrame( theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y )
				) ||
				( s_CUI_ID_FRAME_MAIN.GetFrame() && 
					s_CUI_ID_FRAME_MAIN.GetFrame()->PtInOnlyFrame( theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y)
				) ||
				( s_CUI_ID_FRAME_SHOP.GetFrame() && 
					s_CUI_ID_FRAME_SHOP.GetFrame()->PtInOnlyFrame(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y)
				) ||
				( s_CUI_ID_FRAME_Bargaining.GetFrame() && 
					s_CUI_ID_FRAME_Bargaining.GetFrame()->PtInOnlyFrame(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y)
				) ||
				( s_CUI_ID_FRAME_Compound.GetFrame() &&
					s_CUI_ID_FRAME_Compound.GetFrame()->PtInOnlyFrame(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y)
				) )
			{
				return false;
			}

			//加密后不准丢弃
			if(sItem.storageinfo.bIsLocked)
			{
				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eText_ItemHaveBeenLocked ) );
				return true;
			}
			if(sItem.IsLock())
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString(eText_ItemLockDestory) );
				return true;
			}

            // 判断是否安全保护状态
            if( !CWealthProtect::Instance().IsInProtectTime() )
            {
			    MsgMoveGoodsReq msg;
			    msg.ustSrcIndex = nIndex;
				msg.nGuID = sItem.itembaseinfo.nOnlyInt;
			    msg.ustDstIndex = ITEM_DISTORY;
			    msg.ustCount = sItem.itembaseinfo.ustItemCount;
			    msg.ucItemBagType = bagType;

                ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( sItem.itembaseinfo.ustItemID );
                if( pItemCommon )
                {
                    DWORD dwColor = S_IconInfoHero::GetQualityColor( pItemCommon->ustLevel );
                    char strItemColor[MAX_PATH] = {0};
                    char strMessage[MAX_PATH] = {0};
                    sprintf(strItemColor, "{#%x=%s#}", dwColor, pItemCommon->GetItemName());
                    sprintf(strMessage, theXmlString.GetString(eClient_AddInfo_2slk_27), sItem.itembaseinfo.ustItemCount, 
                        strItemColor);
                    s_CUI_ID_FRAME_MessageBox.Show( strMessage, theXmlString.GetString(eClient_AddInfo_2slk_28),
                        CUI_ID_FRAME_MessageBox::eTypeYesNo, false,
                        RemoveSomething, &msg, sizeof(MsgMoveGoodsReq));
                }
            }

			return true;
		}
		break;
	}
	return false;
	unguard;
}

void CleanUpBag()
{
	if (s_CUI_ID_FRAME_PACK.IsOpenPackByBagType(BT_MaterialBag))
	{
		MsgCleanUpBag msg;
		msg.ucItemBagType = BT_MaterialBag;
		msg.stBagIndexBegin = 0;
		msg.stBagIndexEnd = thePlayerRole.m_bagMaterial.GetNowBagSize();
		GettheNetworkInput().SendMsg( &msg );
	}
	else if (s_CUI_ID_FRAME_PACK.IsOpenPackByBagType(BT_TaskBag))
	{
		MsgCleanUpBag msg;
		msg.ucItemBagType = BT_TaskBag;
		msg.stBagIndexBegin = 0;
		msg.stBagIndexEnd = thePlayerRole.m_bagTask.GetNowBagSize();
		GettheNetworkInput().SendMsg( &msg );
	}
	else
	{
        // 记录普通包裹，是否有物品拖到快捷栏里，记录快捷栏位置
        s_CUI_ID_FRAME_PACK.ClearHotkeyPackBackup();
        for( int i = 0; i < More_iHotkey; ++i )
        {
            SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[i];
            if( pHotkey->ShortCut.BagType == BagTypePack && thePlayerRole.m_bag.IsHaveItem(pHotkey->ShortCut.BagIndex) )
            {
                HotKeyPackData kHotKeyData;
                kHotKeyData.iHotKeyIndex = i;
                kHotKeyData.ustItemID = thePlayerRole.m_bag.m_pPackItem[pHotkey->ShortCut.BagIndex].itembaseinfo.ustItemID;
                s_CUI_ID_FRAME_PACK.PushHotkeyPackBackup(kHotKeyData);
            }
        }

		s_CUI_ID_FRAME_PACK.ClearSlotSpark();

		MsgCleanUpBag msg;
		msg.ucItemBagType = BT_NormalItemBag;
		msg.stBagIndexBegin = 0;
		msg.stBagIndexEnd = thePlayerRole.m_bag.GetNowBagSize();
		GettheNetworkInput().SendMsg( &msg );
	}
	PlaySoundConfig( SoundConfig::EST_CleanupItem );
}

CUI_ID_FRAME_PACK s_CUI_ID_FRAME_PACK;
MAP_FRAME_RUN( s_CUI_ID_FRAME_PACK, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_PACK, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_PACK, ID_LISTIMG_PACKOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_LISTIMG_PACKOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_LISTIMG_PACKOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_PACK, ID_LISTIMG_PACKOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_PACK, ID_LISTIMG_MaterialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_LISTIMG_MaterialOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_LISTIMG_MaterialOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_PACK, ID_LISTIMG_MaterialOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_PACK, ID_LISTIMG_TaskOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_LISTIMG_TaskOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_LISTIMG_TaskOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_PACK, ID_LISTIMG_TaskOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_BUTTON_CLOSEOnButtonClick )
// MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_PACK, ID_LISTIMG_rubbishOnIconDragOn )
// MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_LISTIMG_rubbishOnIconLDBClick )
// MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_LISTIMG_rubbishOnIconButtonClick )
// MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_PACK, ID_LISTIMG_rubbishOnIconRButtonUp )
// MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_PACK, ID_LISTIMG_SplitOnIconDragOn )
// MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_LISTIMG_SplitOnIconLDBClick )
// MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_LISTIMG_SplitOnIconButtonClick )
// MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_PACK, ID_LISTIMG_SplitOnIconRButtonUp )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_BUTTON_rubbishOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_BUTTON_SplitOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_BUTTON_BaitanOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_BUTTON_CleanOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_CHECKBOX_DecomposeOnCheckBoxCheck )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_BUTTON_helpOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_CHECKBOX_ZhuangbeiOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_CHECKBOX_MaterialOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_CHECKBOX_TaskOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_BUTTON_LockOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_BUTTON_UnlockOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_BUTTON_PocketShopOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_BUTTON_ChangkuOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_BUTTON_StarOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_BUTTON_GemUpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_BUTTON_GemOnButtonClick )

MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_BUTTON_mendOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PACK, ID_BUTTON_mend2OnButtonClick )

CUI_ID_FRAME_PACK::CUI_ID_FRAME_PACK()
{
	// Member
	ResetMembers();

    m_nTaskEffBagType = -1;
    m_nTaskEffIndex = -1;
    m_nTaskEffGuid = 0;
    m_bTaskEffNeedCheck = false;
}

void CUI_ID_FRAME_PACK::ResetMembers()
{
	 
	m_pID_FRAME_PACK = NULL;
// 	m_pID_PICTURE_Di = NULL;
// 	m_pID_PICTURE_Di2 = NULL;
// 	m_pID_PICTURE_Icon_Di = NULL;
	m_pID_LISTIMG_PACK = NULL;
	m_pID_LISTIMG_Material = NULL;
	m_pID_LISTIMG_Task = NULL;
//	m_pID_PICTURE_FenGe = NULL;
//	m_pID_PICTURE_Money_Di = NULL;
	m_pID_TEXT_MONEY = NULL;
	m_pID_TEXT_JIFEN = NULL;
// 	m_pID_PICTURE_title2 = NULL;
// 	m_pID_PICTURE_title = NULL;
//	m_pID_PICTURE_yuanbao = NULL;
	m_pID_PICTURE_money = NULL;
	m_pID_BUTTON_CLOSE = NULL;
// 	m_pID_LISTIMG_rubbish = NULL;
// 	m_pID_LISTIMG_Split = NULL;
// 	m_pID_BUTTON_rubbish = NULL;
	m_pID_BUTTON_Split = NULL;
	m_pID_BUTTON_Baitan = NULL;
	m_pID_BUTTON_Clean = NULL;
	m_pID_CHECKBOX_Decompose = NULL;

//	m_pID_BUTTON_help = NULL;
	m_pID_CHECKBOX_Zhuangbei = NULL;
	m_pID_CHECKBOX_Material = NULL;
	m_pID_CHECKBOX_Task = NULL;
	m_pID_TEXT_JinDing = NULL;
	m_pID_TEXT_JinPiao = NULL;

	m_pID_BUTTON_Lock = NULL;
	m_pID_BUTTON_Unlock = NULL;
//	m_pID_PICTURE_Tip = NULL;
    m_pID_PROGRESS_TaskItemEff = NULL;

	bInUIFrameLock = false;
	bInUIFrameUnLock = false;
	m_dwMoveCount = 0;
	m_nItemInBagIndex = -1;
	m_nEquipToWhereIndex = -1;
	m_nForTargetItemIndex = -1;
	m_nGoodsCount = 0;
	m_bStartIntensify = false;
	m_dwLastTime = 0;

	m_bDestroyItem = false;
	m_bSplitItem = false;
	m_nSplitCount = 0;

	m_bLockItem = false;
	m_bUnLockItem = false;

	m_stQuestUseItem.m_bQuestUseItem = false;
	m_stQuestUseItem.m_dwQuestUseItemStartTime = 0;
	m_stQuestUseItem.m_dwQuestTime = 0;
	m_stQuestUseItem.nId = -1;
	m_stQuestUseItem.nIndex = -1;

	m_bCancelOperator = false;
	m_bShiftRBSplitItem = false;

	m_bRepair = false;

    m_vctHotkeyPackBackup.clear();
//     m_pID_TEXT_EspecialMoneyZ = NULL;
    m_pID_TEXT_EspecialMoney = NULL;
//	m_pID_PICTURE_Tip2 = NULL;
	m_pID_BUTTON_PocketShop = NULL;
	m_pID_BUTTON_Changku = NULL;
	m_pID_BUTTON_Star = NULL;
	m_pID_BUTTON_GemUp = NULL;
	m_pID_BUTTON_Gem = NULL;
	m_pID_BUTTON_mend2 = NULL;
	m_pID_BUTTON_mend = NULL;
    m_nEquipPos = -1;
}
// Frame
bool CUI_ID_FRAME_PACK::OnFrameRun()
{
	// 死亡后要关闭背包界面
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if ( pMe == NULL )
	{
		return false;
	}
	if ( pMe->IsDead() )
	{
		m_stQuestUseItem.m_bQuestUseItem = false;
		return true;
	}
	if ( m_stQuestUseItem.m_bQuestUseItem == true )
	{
		if ( pMe->IsMoving() )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString(eClient_AddInfo_2slk_11) );
			m_stQuestUseItem.m_bQuestUseItem = false;
			s_CUI_Progress.ShowByTime( HQ_TimeGetTime(), 1, true, 1, true, true, theXmlString.GetString(eTextPlayer_Break), true, false, 0, FALSE );
		}
		else
		{
			if ( HQ_TimeGetTime() - m_stQuestUseItem.m_dwQuestUseItemStartTime >= 
				m_stQuestUseItem.m_dwQuestTime )
			{

				m_stQuestUseItem.m_bQuestUseItem = false;
				//吟唱结束，重置静态变量为False
				sItemCommon->bIsSinging = m_stQuestUseItem.m_bQuestUseItem;
				UseItem( m_stQuestUseItem.nId,
					m_stQuestUseItem.nIndex, false );
			}
		}
	}
	if (m_bStartIntensify)
	{
		if (pMe->IsMoving())
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString(eClient_AddInfo_2slk_11) );
			m_bStartIntensify = false;
			s_CUI_Progress.ShowByTime( HQ_TimeGetTime(), 1, true, 1, true, true, theXmlString.GetString(eTextPlayer_Break), true, false, 0, FALSE );
		}
	}

	if(s_CUI_ID_FRAME_PACK.IsVisable())
	{
		UpdateIconInfo();
	}

	IntonationUtility_Tick();

    // 检查任务道具特效是否继续播放
    CheckTaskItemEff();

	OnUpdateUIShopAndCK();
	return true;
}

bool CUI_ID_FRAME_PACK::OnFrameRender()
{
	return true;
}

// ListImg / ListEx
bool CUI_ID_FRAME_PACK::ID_LISTIMG_PACKOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													ControlIconDrag::S_ListImg* pItemDrag,
													ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_PACK )
		return false;

	return PackOnIconDragOn(dynamic_cast<ControlListImage*>(pSender), dynamic_cast<ControlListImage*>(pMe),
		pItemDrag, pItemSrc, &thePlayerRole.m_bag, BT_NormalItemBag);
}

bool CUI_ID_FRAME_PACK::ID_LISTIMG_PACKOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PACK )
		return false;

	return false;
}

bool CUI_ID_FRAME_PACK::ID_LISTIMG_PACKOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PACK )
		return false;

	return PackOnIconButtonClick(m_pID_LISTIMG_PACK, pItem, &thePlayerRole.m_bag, BT_NormalItemBag);
}

bool CUI_ID_FRAME_PACK::ID_LISTIMG_PACKOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PACK )
		return false;

	return PackOnIconRButtonUp(m_pID_LISTIMG_PACK, pItem, &thePlayerRole.m_bag, BT_NormalItemBag);
}

// ListImg / ListEx
bool CUI_ID_FRAME_PACK::ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														ControlIconDrag::S_ListImg* pItemDrag,
														ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_PACK )
		return false;

	return PackOnIconDragOn(dynamic_cast<ControlListImage*>(pSender), dynamic_cast<ControlListImage*>(pMe),
		pItemDrag, pItemSrc, &thePlayerRole.m_bagMaterial, BT_MaterialBag);
}

bool CUI_ID_FRAME_PACK::ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PACK )
		return false;

	return false;
}

bool CUI_ID_FRAME_PACK::ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PACK )
		return false;

	// 已点下分解物品功能, 包里的材料与任务标签均不接受物品单击事件
	if (m_pID_CHECKBOX_Decompose->IsChecked())
		return false;

	return PackOnIconButtonClick(m_pID_LISTIMG_Material, pItem, &thePlayerRole.m_bagMaterial, BT_MaterialBag);
}

bool CUI_ID_FRAME_PACK::ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PACK )
		return false;

	return PackOnIconRButtonUp(m_pID_LISTIMG_Material, pItem, &thePlayerRole.m_bagMaterial, BT_MaterialBag);
}

// ListImg / ListEx
bool CUI_ID_FRAME_PACK::ID_LISTIMG_TaskOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													ControlIconDrag::S_ListImg* pItemDrag,
													ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_PACK )
		return false;

	return PackOnIconDragOn(dynamic_cast<ControlListImage*>(pSender), dynamic_cast<ControlListImage*>(pMe),
		pItemDrag, pItemSrc, &thePlayerRole.m_bagTask, BT_TaskBag);
}
bool CUI_ID_FRAME_PACK::ID_LISTIMG_TaskOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PACK )
		return false;

	return false;
}

bool CUI_ID_FRAME_PACK::ID_LISTIMG_TaskOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PACK )
		return false;

	// 已点下分解物品功能, 包里的材料与任务标签均不接受物品单击事件
	if (m_pID_CHECKBOX_Decompose->IsChecked())
		return false;

	return PackOnIconButtonClick(m_pID_LISTIMG_Task, pItem, &thePlayerRole.m_bagTask, BT_TaskBag);
}

bool CUI_ID_FRAME_PACK::ID_LISTIMG_TaskOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PACK )
		return false;

	return PackOnIconRButtonUp(m_pID_LISTIMG_Task, pItem, &thePlayerRole.m_bagTask, BT_TaskBag);
}
// Button
bool CUI_ID_FRAME_PACK::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PACK )
		return false;

	SetVisable( false );
	if(s_CUI_ID_FRAME_Storage.IsVisable())
	{
		s_CUI_ID_FRAME_Storage.SetVisable(false);
	}
	//光标置回原来的状态

	return true;
}

// Button
bool CUI_ID_FRAME_PACK::ID_BUTTON_mendOnButtonClick( ControlObject* pSender )
{
	if (!m_pID_FRAME_PACK)
		return false;
	DWORD dwMoney = thePlayerRole.GetData(CPlayerRole::TYPE_MONEY);
	int nItemHp = 0, nItemMaxHp = 0, nHpPoint = 0, mendPri = 0;
	bool bIsNeed = false;
	int nAllSprice = 0;
	for( int i = 0; i < EEquipPartType_MaxEquitPart; ++i)
	{
		if(thePlayerRole.m_charinfo.visual.GetVisualArray()[i].itembaseinfo.ustItemID != InvalidLogicNumber)
		{
			ItemDefine::SItemCanEquip *pItem = (ItemDefine::SItemCanEquip *)GettheItemDetail().GetItemByID(
				thePlayerRole.m_charinfo.visual.GetVisualArray()[i].itembaseinfo.ustItemID ); 
			if (!pItem || pItem->uchRepairType != ItemDefine::SItemCanEquip::ECD_Repair_Normal)
				continue;

			nItemHp = thePlayerRole.m_charinfo.visual.GetVisualArray()[i].equipdata.usHP;
			nItemMaxHp = pItem->stHPMax;
			if( nItemHp >= 0 && nItemHp < nItemMaxHp )
			{//这里说明耐久已经下降了　应该计算修理
				bIsNeed = true;
				if( pItem )
				{
					nAllSprice += pItem->stRepairPrice * (pItem->stHPMax - nItemHp);
				}
			}
		}
	}
	if (nAllSprice == 0&&bIsNeed)
	{
		nAllSprice = 1;
	}
	if(!thePlayerRole.HaveEnoughMoney(nAllSprice))
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eText_MoneyNotEnoungh ) );
		return false;
	}
	if( nAllSprice == 0)
	{
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Fix_Failed, theXmlString.GetString(eClient_AddInfo_2slk_10) );
		return false;
	}

	char szTemp[128] = {0};

	int gold = 0,silver = 0,copper = 0;
    thePlayerRole.GetGSCFromMoney(nAllSprice,gold,silver,copper);

	std::stringstream sstr;
	sstr << theXmlString.GetString(eText_Client_Doyou_Mend_CostGold);
	if (gold > 0)
		sstr << gold << theXmlString.GetString(eText_Money_Gold);
	if (silver > 0)
		sstr << silver << theXmlString.GetString(eText_Money_Silver);
	if (copper > 0)
		sstr << copper << theXmlString.GetString(eText_Money_Copper);

	s_CUI_ID_FRAME_MessageBox.Show( sstr.str().c_str(), "", CUI_ID_FRAME_MessageBox::eTypeYesNo,
		false, sendMendMsg );
	return true;
}
// Button
bool CUI_ID_FRAME_PACK::ID_BUTTON_mend2OnButtonClick( ControlObject* pSender )
{
	if (!m_pID_FRAME_PACK)
		return false;
	theMouseManager.SetCanSetCursor(true);
	m_bRepair = !m_bRepair;
	if (m_bRepair)
	{
		ClearMotion();
		theMouseManager.SetCursor(MouseManager::Type_Repair);
		theMouseManager.SetUICursor(MouseManager::Type_Repair);
	}
	else
	{
		theMouseManager.SetCursor(MouseManager::Type_Arrow);
		theMouseManager.SetUICursor(MouseManager::Type_Arrow);
	}
	theMouseManager.SetCanSetCursor(false);
	return true;
}
// ListImg / ListEx
// bool CUI_ID_FRAME_PACK::ID_LISTIMG_rubbishOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
// 													   ControlIconDrag::S_ListImg* pItemDrag,
// 													   ControlIconDrag::S_ListImg* pItemSrc )
// {
// 	if( !m_pID_FRAME_PACK )
// 		return false;
// 
// 	unsigned int nSrcIndex = -1;
// 	if( pSender == m_pID_LISTIMG_PACK )
// 	{
// 		nSrcIndex = m_pID_LISTIMG_PACK->GetItemIndex( pItemDrag );
// 	}
// 
// 	//如果物品加密则不能删除
// 	SCharItem stBagItemSrc;
// 	if(thePlayerRole.m_bag.IsHaveItem(nSrcIndex))
// 	{
// 		thePlayerRole.m_bag.GetItem( nSrcIndex, &stBagItemSrc );
// 		if(stBagItemSrc.storageinfo.bIsLocked)
// 		{
// 			s_CUI_ID_FRAME_MessageBox.Show(  theXmlString.GetString(eText_ItemHaveBeenLocked) );
// 			return false;
// 		}		
// 	}
// 	else
// 	{
// 		return false;
// 	}
// 
// 	//--------------------------
//     // 判断是否安全保护状态
//     if( !CWealthProtect::Instance().IsInProtectTime() )
//     {
//         MsgMoveGoodsReq msg;
// 	    msg.ustSrcIndex = nSrcIndex;
// 		msg.nGuID = thePlayerRole.m_bag.m_pPackItem[nSrcIndex].itembaseinfo.nOnlyInt;
// 	    msg.ustDstIndex = ITEM_DISTORY;
// 	    msg.ustCount = thePlayerRole.m_bag.m_pPackItem[nSrcIndex].itembaseinfo.ustItemCount;
//         ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( thePlayerRole.m_bag.m_pPackItem[nSrcIndex].itembaseinfo.ustItemID );
//         if( pItemCommon )
//         {
//             DWORD dwColor = S_IconInfoHero::GetQualityColor( pItemCommon->ustLevel );
//             char strItemColor[MAX_PATH] = {0};
//             char strMessage[MAX_PATH] = {0};
//             sprintf(strItemColor, "{#%x=%s#}", dwColor, pItemCommon->GetItemName());
//             sprintf(strMessage, theXmlString.GetString(eClient_AddInfo_2slk_27), thePlayerRole.m_bag.m_pPackItem[nSrcIndex].itembaseinfo.ustItemCount, 
//                 strItemColor);
//             s_CUI_ID_FRAME_MessageBox.Show( strMessage, theXmlString.GetString(eClient_AddInfo_2slk_28),
//                 CUI_ID_FRAME_MessageBox::eTypeYesNo, false,
//                 RemoveSomething,&msg,sizeof(MsgMoveGoodsReq));
//         }
//     }
// 	return false;
// }
// bool CUI_ID_FRAME_PACK::ID_LISTIMG_rubbishOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
// {
// 	if( !m_pID_FRAME_PACK )
// 		return false;
// 
// 	return false;
// }
// bool CUI_ID_FRAME_PACK::ID_LISTIMG_rubbishOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
// {
// 	if( !m_pID_FRAME_PACK )
// 		return false;
// 
// 	return false;
// }
// bool CUI_ID_FRAME_PACK::ID_LISTIMG_rubbishOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
// {
// 	if( !m_pID_FRAME_PACK )
// 		return false;
// 
// 	return false;
// }
// // ListImg / ListEx
// bool CUI_ID_FRAME_PACK::ID_LISTIMG_SplitOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
// 													 ControlIconDrag::S_ListImg* pItemDrag,
// 													 ControlIconDrag::S_ListImg* pItemSrc )
// {
// 	if( !m_pID_FRAME_PACK )
// 		return false;
// 
// 	return false;
// }
// bool CUI_ID_FRAME_PACK::ID_LISTIMG_SplitOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
// {
// 	if( !m_pID_FRAME_PACK )
// 		return false;
// 
// 	return false;
// }
// bool CUI_ID_FRAME_PACK::ID_LISTIMG_SplitOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
// {
// 	if( !m_pID_FRAME_PACK )
// 		return false;
// 
// 	return false;
// }
// bool CUI_ID_FRAME_PACK::ID_LISTIMG_SplitOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
// {
// 	return false;
// }
// Button
// bool CUI_ID_FRAME_PACK::ID_BUTTON_rubbishOnButtonClick( ControlObject* pSender )
// {
// 	if( !m_pID_FRAME_PACK )
// 		return false;
// 
// 	if (!m_bDestroyItem)
// 		EnableDestroyItem();
// 	else
// 		DisableDestroyItem();
// 	return true;
// }
// Button
bool CUI_ID_FRAME_PACK::ID_BUTTON_SplitOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PACK )
		return false;

	if (!m_bSplitItem)
		EnableSplitItem();
	else
		DisableSplitItem();
	return true;
}
// Button
bool CUI_ID_FRAME_PACK::ID_BUTTON_BaitanOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PACK )
		return false;

    CSystemStallage::Instance()->OpenStallageWindow2();
	return true;
}
// Button
bool CUI_ID_FRAME_PACK::ID_BUTTON_CleanOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PACK )
		return false;

    char strDestroyItem[MAX_PATH] = {0};
    strncpy(strDestroyItem, theXmlString.GetString(eClient_AddInfo_2slk_27), MAX_PATH-1);
    char *p = strchr(strDestroyItem,'%');
    if( p )
        *p = '\0';
	if (s_CUI_ID_FRAME_Bargaining.IsVisable()
        || s_CUI_ID_FRAME_Decompound.IsVisable() 
        || s_CUI_ID_FRAME_Star.IsVisable() 
        || s_CUI_ID_FRAME_GoldPlating.IsVisable()
		|| s_CUI_ID_FRAME_FiveXing.IsVisable()
		|| s_CUI_ID_FRAME_MoveStar.IsVisable()
		|| s_CUI_ID_FRAME_SkillEquipUpdate.IsVisable()
		|| s_CUI_ID_FRAME_SkillEquipChange.IsVisable()
        || s_CUI_ID_FRAME_FiveXingChange.IsVisable()
        || s_CUI_ID_FRAME_FiveXingUpdate.IsVisable()
        || s_CUI_ID_FRAME_FiveXingDisplace.IsVisable()
		|| s_CUI_ID_FRAME_MoveStarUpgrade.IsVisable()
		|| s_CUI_ID_FRAME_StarMaterialUpgrade.IsVisable()
        || s_CUI_ID_FRAME_MessageBox.HasMessageBoxMatchString(strDestroyItem)
        || s_CUI_ID_FRAME_MailMain.IsVisable()
		|| s_CUI_ID_FRAME_GivePresent.IsVisable()
		|| s_CUI_ID_FRAME_IntensifyStar.IsVisable()
		|| s_CUI_ID_FRAME_ZhuJianUp.IsVisable()
		|| s_CUI_ID_FRAME_zhujiangbianshen.IsVisable()
		|| s_CUI_ID_FRAME_TransferStar.IsVisable()
		|| s_CUI_ID_FRAME_GemUp.IsVisable()
		|| s_CUI_ID_FRAME_MountStrengthen.IsVisable()
		|| s_CUI_ID_FRAME_GemRemove.IsVisable()
		|| s_CUI_ID_FRAME_IdentifyQuality.IsVisable()
		|| s_CUI_ID_FRAME_RandAttribute.IsVisable()
		|| s_CUI_ID_FRAME_EquipUpgrade.IsVisable()
		|| s_CUI_ID_FRAME_MountMoveStar.IsVisable()
		|| !IsCanFixBag()
		)   // 是否显示销毁物品确认框
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString( eText_SitFailed_CurrStatus ) );
		return false;
	}

	CleanUpBag();
	return true;
}

void CUI_ID_FRAME_PACK::ID_CHECKBOX_DecomposeOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_PACK )
		return;

	DecomposeItem(!m_pID_CHECKBOX_Decompose->IsChecked());

}

// Button
// bool CUI_ID_FRAME_PACK::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
// {
// 	if( !m_pID_FRAME_PACK )
// 		return false;
// 
// 	return true;
// }
// CheckBox
void CUI_ID_FRAME_PACK::ID_CHECKBOX_ZhuangbeiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_PACK )
		return;

	m_BagTabGroup.TogglePage(m_pID_CHECKBOX_Zhuangbei);
}
// CheckBox
void CUI_ID_FRAME_PACK::ID_CHECKBOX_MaterialOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_PACK )
		return;

	m_BagTabGroup.TogglePage(m_pID_CHECKBOX_Material);
}
// CheckBox
void CUI_ID_FRAME_PACK::ID_CHECKBOX_TaskOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_PACK )
		return;

	m_BagTabGroup.TogglePage(m_pID_CHECKBOX_Task);
}

// Button
bool CUI_ID_FRAME_PACK::ID_BUTTON_LockOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PACK )
		return false;

	if (!m_bLockItem)
		EnableLockItem();
	else
		DisableLockItem();

	return true;
}
// Button
bool CUI_ID_FRAME_PACK::ID_BUTTON_UnlockOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PACK )
		return false;

	if (!m_bUnLockItem)
		EnableUnLockItem();
	else
		DisableUnLockItem();

	return true;
}
//仓库
bool CUI_ID_FRAME_PACK::ID_BUTTON_ChangkuOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PACK )
		return false;
	//判断是否有出战的副将
	if(!thePlayerRole.GetActivedPet())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_ActionPetNon ) );
		return false;
	}
	OpenChangKu();
	return true;
}
// 商店Button
bool CUI_ID_FRAME_PACK::ID_BUTTON_PocketShopOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PACK )
		return false;
	//判断是否有出战的副将
	if(!thePlayerRole.GetActivedPet())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_ActionPetNon ) );
		return false;
	}

	s_CUI_ID_FRAME_SHOP.SetRemoteClose(false);
	s_CUI_ID_FRAME_SHOP.SetNpcID(theHeroGame.GetPlayerMgr()->GetMe()->GetID());
	{
		if (s_CUI_ID_FRAME_Gem.IsVisable())
		{
			s_CUI_ID_FRAME_Gem.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_Hole.IsVisable())
		{
			s_CUI_ID_FRAME_Hole.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_Star.IsVisable())
		{
			s_CUI_ID_FRAME_Star.SetVisable(false);
		}
	}
	s_CUI_ID_FRAME_SHOP.SetVisable(true);
	return true;
}

// 升星Button
bool CUI_ID_FRAME_PACK::ID_BUTTON_StarOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PACK )
		return false;
	s_CUI_ID_FRAME_Star.SetIsPocket(true);
	{
		if (s_CUI_ID_FRAME_Gem.IsVisable())
		{
			s_CUI_ID_FRAME_Gem.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_Hole.IsVisable())
		{
			s_CUI_ID_FRAME_Hole.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_SHOP.IsVisable())
		{
			s_CUI_ID_FRAME_SHOP.SetVisable(false);
		}
	}
	s_CUI_ID_FRAME_Star.SetVisable(true);
	ResetWindowPosition(s_CUI_ID_FRAME_Star.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
	return true;
}
// 装备打孔Button
bool CUI_ID_FRAME_PACK::ID_BUTTON_GemUpOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PACK )
		return false;
	s_CUI_ID_FRAME_Hole.SetIsPocket(true);
	{
		if (s_CUI_ID_FRAME_Gem.IsVisable())
		{
			s_CUI_ID_FRAME_Gem.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_Star.IsVisable())
		{
			s_CUI_ID_FRAME_Star.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_SHOP.IsVisable())
		{
			s_CUI_ID_FRAME_SHOP.SetVisable(false);
		}
	}
	s_CUI_ID_FRAME_Hole.SetVisable(true);
	ResetWindowPosition(s_CUI_ID_FRAME_Hole.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
	return true;
}

// 镶嵌Button
bool CUI_ID_FRAME_PACK::ID_BUTTON_GemOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PACK )
		return false;
	s_CUI_ID_FRAME_Gem.SetIsPocket(true);

	{
		if (s_CUI_ID_FRAME_Hole.IsVisable())
		{
			s_CUI_ID_FRAME_Hole.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_Star.IsVisable())
		{
			s_CUI_ID_FRAME_Star.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_SHOP.IsVisable())
		{
			s_CUI_ID_FRAME_SHOP.SetVisable(false);
		}
	}

	s_CUI_ID_FRAME_Gem.SetVisable(true);
	ResetWindowPosition(s_CUI_ID_FRAME_Gem.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
	return true;
}

void CUI_ID_FRAME_PACK::InitializeAtEnterWorld()
{
    if( !m_pID_FRAME_PACK )
        return;

    ClearSlotSpark();
    _SetVisable( false );
}

// 装载UI
bool CUI_ID_FRAME_PACK::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Pack.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Pack.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}

static void UIPack_VisableChanged(ControlObject* pObject)
{
	if (!s_CUI_ID_FRAME_PACK.IsVisable())
	{
		s_CUI_ID_FRAME_PACK.SetSplitCount(0);
		s_CUI_ID_FRAME_PACK.SetDestroyItem(false);
		s_CUI_ID_FRAME_PACK.SetSplitItem(false);
		s_CUI_ID_FRAME_SHOP.SetRepair(false);
		s_CUI_ID_FRAME_PACK.DisableDestroyItem();
		s_CUI_ID_FRAME_PACK.DisableSplitItem();

		theIconDragManager.ClearDrag();
		theMouseManager.SetCanSetCursor(true);
		theMouseManager.SetUICursor(MouseManager::Type_Arrow);
		theMouseManager.SetCanSetCursor(false);
	}
}

// 关连控件
bool CUI_ID_FRAME_PACK::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_PACK, s_CUI_ID_FRAME_PACKOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_PACK, s_CUI_ID_FRAME_PACKOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_PACK, ID_LISTIMG_PACK, s_CUI_ID_FRAME_PACKID_LISTIMG_PACKOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_PACK, ID_LISTIMG_PACK, s_CUI_ID_FRAME_PACKID_LISTIMG_PACKOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_PACK, ID_LISTIMG_PACK, s_CUI_ID_FRAME_PACKID_LISTIMG_PACKOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_PACK, ID_LISTIMG_PACK, s_CUI_ID_FRAME_PACKID_LISTIMG_PACKOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_PACK, ID_LISTIMG_Material, s_CUI_ID_FRAME_PACKID_LISTIMG_MaterialOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_PACK, ID_LISTIMG_Material, s_CUI_ID_FRAME_PACKID_LISTIMG_MaterialOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_PACK, ID_LISTIMG_Material, s_CUI_ID_FRAME_PACKID_LISTIMG_MaterialOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_PACK, ID_LISTIMG_Material, s_CUI_ID_FRAME_PACKID_LISTIMG_MaterialOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_PACK, ID_LISTIMG_Task, s_CUI_ID_FRAME_PACKID_LISTIMG_TaskOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_PACK, ID_LISTIMG_Task, s_CUI_ID_FRAME_PACKID_LISTIMG_TaskOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_PACK, ID_LISTIMG_Task, s_CUI_ID_FRAME_PACKID_LISTIMG_TaskOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_PACK, ID_LISTIMG_Task, s_CUI_ID_FRAME_PACKID_LISTIMG_TaskOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_PACK, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_PACKID_BUTTON_CLOSEOnButtonClick );
// 	theUiManager.OnIconDragOn( ID_FRAME_PACK, ID_LISTIMG_rubbish, s_CUI_ID_FRAME_PACKID_LISTIMG_rubbishOnIconDragOn );
// 	theUiManager.OnIconLDBClick( ID_FRAME_PACK, ID_LISTIMG_rubbish, s_CUI_ID_FRAME_PACKID_LISTIMG_rubbishOnIconLDBClick );
// 	theUiManager.OnIconButtonClick( ID_FRAME_PACK, ID_LISTIMG_rubbish, s_CUI_ID_FRAME_PACKID_LISTIMG_rubbishOnIconButtonClick );
// 	theUiManager.OnIconRButtonUp( ID_FRAME_PACK, ID_LISTIMG_rubbish, s_CUI_ID_FRAME_PACKID_LISTIMG_rubbishOnIconRButtonUp );
// 	theUiManager.OnIconDragOn( ID_FRAME_PACK, ID_LISTIMG_Split, s_CUI_ID_FRAME_PACKID_LISTIMG_SplitOnIconDragOn );
// 	theUiManager.OnIconLDBClick( ID_FRAME_PACK, ID_LISTIMG_Split, s_CUI_ID_FRAME_PACKID_LISTIMG_SplitOnIconLDBClick );
// 	theUiManager.OnIconButtonClick( ID_FRAME_PACK, ID_LISTIMG_Split, s_CUI_ID_FRAME_PACKID_LISTIMG_SplitOnIconButtonClick );
// 	theUiManager.OnIconRButtonUp( ID_FRAME_PACK, ID_LISTIMG_Split, s_CUI_ID_FRAME_PACKID_LISTIMG_SplitOnIconRButtonUp );
// 	theUiManager.OnButtonClick( ID_FRAME_PACK, ID_BUTTON_rubbish, s_CUI_ID_FRAME_PACKID_BUTTON_rubbishOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PACK, ID_BUTTON_Split, s_CUI_ID_FRAME_PACKID_BUTTON_SplitOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PACK, ID_BUTTON_Baitan, s_CUI_ID_FRAME_PACKID_BUTTON_BaitanOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PACK, ID_BUTTON_Clean, s_CUI_ID_FRAME_PACKID_BUTTON_CleanOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PACK, ID_CHECKBOX_Decompose, s_CUI_ID_FRAME_PACKID_CHECKBOX_DecomposeOnCheckBoxCheck );
//	theUiManager.OnButtonClick( ID_FRAME_PACK, ID_BUTTON_help, s_CUI_ID_FRAME_PACKID_BUTTON_helpOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PACK, ID_CHECKBOX_Zhuangbei, s_CUI_ID_FRAME_PACKID_CHECKBOX_ZhuangbeiOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PACK, ID_CHECKBOX_Material, s_CUI_ID_FRAME_PACKID_CHECKBOX_MaterialOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PACK, ID_CHECKBOX_Task, s_CUI_ID_FRAME_PACKID_CHECKBOX_TaskOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_PACK, ID_BUTTON_Lock, s_CUI_ID_FRAME_PACKID_BUTTON_LockOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PACK, ID_BUTTON_Unlock, s_CUI_ID_FRAME_PACKID_BUTTON_UnlockOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PACK, ID_BUTTON_PocketShop, s_CUI_ID_FRAME_PACKID_BUTTON_PocketShopOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PACK, ID_BUTTON_Changku, s_CUI_ID_FRAME_PACKID_BUTTON_ChangkuOnButtonClick );

	theUiManager.OnButtonClick( ID_FRAME_PACK, ID_BUTTON_mend,s_CUI_ID_FRAME_PACKID_BUTTON_mendOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PACK, ID_BUTTON_mend2, s_CUI_ID_FRAME_PACKID_BUTTON_mend2OnButtonClick );
	
	theUiManager.OnButtonClick( ID_FRAME_PACK, ID_BUTTON_Star, s_CUI_ID_FRAME_PACKID_BUTTON_StarOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PACK, ID_BUTTON_GemUp, s_CUI_ID_FRAME_PACKID_BUTTON_GemUpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PACK, ID_BUTTON_Gem, s_CUI_ID_FRAME_PACKID_BUTTON_GemOnButtonClick );

	m_pID_FRAME_PACK = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_PACK );
// 	m_pID_PICTURE_Di = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PACK, ID_PICTURE_Di );
// 	m_pID_PICTURE_Di2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PACK, ID_PICTURE_Di2 );
// 	m_pID_PICTURE_Icon_Di = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PACK, ID_PICTURE_Icon_Di );
	m_pID_LISTIMG_PACK = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PACK, ID_LISTIMG_PACK );
	m_pID_LISTIMG_Material = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PACK, ID_LISTIMG_Material );
	m_pID_LISTIMG_Task = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PACK, ID_LISTIMG_Task );
//	m_pID_PICTURE_FenGe = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PACK, ID_PICTURE_FenGe );
//	m_pID_PICTURE_Money_Di = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PACK, ID_PICTURE_Money_Di );
	m_pID_TEXT_MONEY = (ControlText*)theUiManager.FindControl( ID_FRAME_PACK, ID_TEXT_MONEY );
	m_pID_TEXT_JIFEN = (ControlText*)theUiManager.FindControl( ID_FRAME_PACK, ID_TEXT_JIFEN );
	
// 	m_pID_PICTURE_title2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PACK, ID_PICTURE_title2 );
// 	m_pID_PICTURE_title = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PACK, ID_PICTURE_title );
//	m_pID_PICTURE_yuanbao = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PACK, ID_PICTURE_yuanbao );
	m_pID_PICTURE_money = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PACK, ID_PICTURE_money );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_PACK, ID_BUTTON_CLOSE );
// 	m_pID_LISTIMG_rubbish = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PACK, ID_LISTIMG_rubbish );
// 	m_pID_LISTIMG_Split = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PACK, ID_LISTIMG_Split );
// 	m_pID_BUTTON_rubbish = (ControlButton*)theUiManager.FindControl( ID_FRAME_PACK, ID_BUTTON_rubbish );
	m_pID_BUTTON_Split = (ControlButton*)theUiManager.FindControl( ID_FRAME_PACK, ID_BUTTON_Split );
	m_pID_BUTTON_Baitan = (ControlButton*)theUiManager.FindControl( ID_FRAME_PACK, ID_BUTTON_Baitan );
	m_pID_BUTTON_Clean = (ControlButton*)theUiManager.FindControl( ID_FRAME_PACK, ID_BUTTON_Clean );
	m_pID_CHECKBOX_Decompose = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PACK, ID_CHECKBOX_Decompose );

//	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_PACK, ID_BUTTON_help );
	m_pID_CHECKBOX_Zhuangbei = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PACK, ID_CHECKBOX_Zhuangbei );
	m_pID_CHECKBOX_Material = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PACK, ID_CHECKBOX_Material );
	m_pID_CHECKBOX_Task = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PACK, ID_CHECKBOX_Task );
	m_pID_TEXT_JinDing = (ControlText*)theUiManager.FindControl( ID_FRAME_PACK, ID_TEXT_JinDing );
	m_pID_TEXT_JinPiao = (ControlText*)theUiManager.FindControl( ID_FRAME_PACK, ID_TEXT_JinPiao );
	m_pID_BUTTON_Lock = (ControlButton*)theUiManager.FindControl( ID_FRAME_PACK, ID_BUTTON_Lock );
	m_pID_BUTTON_Unlock = (ControlButton*)theUiManager.FindControl( ID_FRAME_PACK, ID_BUTTON_Unlock );
//	m_pID_PICTURE_Tip = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PACK, ID_PICTURE_Tip );
//     m_pID_TEXT_EspecialMoneyZ = (ControlText*)theUiManager.FindControl( ID_FRAME_PACK, ID_TEXT_EspecialMoneyZ );
    m_pID_TEXT_EspecialMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_PACK, ID_TEXT_EspecialMoney );
//	m_pID_PICTURE_Tip2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PACK, ID_PICTURE_Tip2 );
    m_pID_PROGRESS_TaskItemEff = (ControlProgress*)theUiManager.FindControl( ID_FRAME_PACK, ID_PROGRESS_TaskItemEff );
	m_pID_BUTTON_PocketShop = (ControlButton*)theUiManager.FindControl( ID_FRAME_PACK, ID_BUTTON_PocketShop );
	m_pID_BUTTON_Changku  = (ControlButton*)theUiManager.FindControl( ID_FRAME_PACK, ID_BUTTON_Changku );
	m_pID_BUTTON_Star = (ControlButton*)theUiManager.FindControl( ID_FRAME_PACK, ID_BUTTON_Star );
	m_pID_BUTTON_GemUp = (ControlButton*)theUiManager.FindControl( ID_FRAME_PACK, ID_BUTTON_GemUp );
	m_pID_BUTTON_Gem = (ControlButton*)theUiManager.FindControl( ID_FRAME_PACK, ID_BUTTON_Gem );

	m_pID_BUTTON_mend = (ControlButton*)theUiManager.FindControl( ID_FRAME_PACK, ID_BUTTON_mend );
	m_pID_BUTTON_mend2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_PACK, ID_BUTTON_mend2 );

	assert(m_pID_TEXT_JIFEN);
	assert( m_pID_BUTTON_Gem );
	assert( m_pID_BUTTON_GemUp );
	assert( m_pID_BUTTON_Star );
	assert( m_pID_BUTTON_PocketShop );
	assert( m_pID_BUTTON_Changku);
	assert( m_pID_FRAME_PACK );
//	assert( m_pID_PICTURE_Di );
//	assert( m_pID_PICTURE_Di2 );
	//assert( m_pID_PICTURE_Icon_Di );
	assert( m_pID_LISTIMG_PACK );
	assert( m_pID_LISTIMG_Material );
	//assert( m_pID_PICTURE_Money_Di );
	assert( m_pID_TEXT_MONEY );
// 	assert( m_pID_PICTURE_title2 );
// 	assert( m_pID_PICTURE_title );
	//assert( m_pID_PICTURE_yuanbao );
	assert( m_pID_PICTURE_money );
	assert( m_pID_BUTTON_CLOSE );
// 	assert( m_pID_LISTIMG_rubbish );
// 	assert( m_pID_LISTIMG_Split );
// 	assert( m_pID_BUTTON_rubbish );
	assert( m_pID_BUTTON_Baitan );
	assert( m_pID_BUTTON_Clean );
	assert( m_pID_CHECKBOX_Decompose );
//	assert( m_pID_BUTTON_help );

	assert( m_pID_BUTTON_Lock );
	assert( m_pID_BUTTON_Unlock );
//	assert( m_pID_PICTURE_Tip );
//     assert( m_pID_TEXT_EspecialMoneyZ );
    assert( m_pID_TEXT_EspecialMoney );	
//	assert( m_pID_PICTURE_Tip2 );
    assert( m_pID_PROGRESS_TaskItemEff );

	assert( m_pID_BUTTON_mend );
	assert( m_pID_BUTTON_mend2 );

	m_pID_FRAME_PACK->SetMsgProcFun( UIPack_MsgProc );
	m_pID_LISTIMG_PACK->SetShiftLBClickFun( IconOnShiftLBClick );
    m_pID_LISTIMG_PACK->SetSparkOnMouseMoveFun( SparkMouseMoveOn );
	m_pID_LISTIMG_PACK->ShowPressEffect(true);
	s_nPackItemHeightMaxShowCount = m_pID_LISTIMG_PACK->GetHeightShowMaxCnt();

	m_pID_LISTIMG_Material->SetShiftLBClickFun( IconOnShiftLBClick );
	m_pID_LISTIMG_Material->ShowPressEffect(true);
	m_pID_LISTIMG_Material->SetVisable(false);

	m_pID_LISTIMG_Task->SetShiftLBClickFun( IconOnShiftLBClick );
	m_pID_LISTIMG_Task->ShowPressEffect(true);
	m_pID_LISTIMG_Task->SetVisable(false);

	m_PackGroup.AddControl(m_pID_LISTIMG_PACK);
	m_MaterialGroup.AddControl(m_pID_LISTIMG_Material);
	m_TaskGroup.AddControl(m_pID_LISTIMG_Task);
	m_BagTabGroup.AddPage(m_pID_CHECKBOX_Zhuangbei, &m_PackGroup);
	m_BagTabGroup.AddPage(m_pID_CHECKBOX_Material, &m_MaterialGroup);
	m_BagTabGroup.AddPage(m_pID_CHECKBOX_Task, &m_TaskGroup);
	m_BagTabGroup.TogglePage(m_pID_CHECKBOX_Zhuangbei);

// 	m_pID_PICTURE_Tip->setShowTip(true);
// 	m_pID_PICTURE_Tip->setTip(theXmlString.GetString(eText_MaxMoneyTip), DT_LEFT);

	m_pID_FRAME_PACK->SetOnVisibleChangedFun(UIPack_VisableChanged);

//     m_pID_PICTURE_Tip2->setShowTip(true);
//     m_pID_PICTURE_Tip2->setTip(theXmlString.GetString(eText_JiaoZiTip),DT_LEFT);
	SetVisable(false);

	LoadGrassItemID();
	USE_SCRIPT( eUI_OBJECT_Pack, this );

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_PACK::_UnLoadUI()
{
	m_PackGroup.Clear();
	m_MaterialGroup.Clear();
	m_TaskGroup.Clear();
	m_BagTabGroup.Clear();

	CLOSE_SCRIPT( eUI_OBJECT_Pack );
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\Pack.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_PACK::_IsVisable()
{
	if( !m_pID_FRAME_PACK )
		return false;
	return m_pID_FRAME_PACK->IsVisable();
}


// 设置是否可视
void CUI_ID_FRAME_PACK::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_PACK )
		return;
	m_pID_FRAME_PACK->SetVisable( bVisable );

	if (bVisable)
	{
		m_BagTabGroup.TogglePage(m_pID_CHECKBOX_Zhuangbei);
		m_pID_LISTIMG_PACK->SetScrollValue( 0 );
	}

	if (bVisable)
	{
		s_CUI_ID_FRAME_MainMenu.SetNeedSpark(false, CUI_ID_FRAME_MainMenu::ekey_bag);		
		PlaySoundConfig( SoundConfig::EST_OpenPackUI );
	}	

	DisableDestroyItem();
	DisableSplitItem();
	DecomposeItem(true);
}

void CUI_ID_FRAME_PACK::RefreshMoney()
{
	if( !m_pID_FRAME_PACK )
		return;
	if( m_pID_TEXT_MONEY )
	{
		std::string text = "";
        thePlayerRole.GetGSCStringFromCurrentMoney(text);
		*m_pID_TEXT_MONEY = text;
	}

	if (m_pID_TEXT_JinDing)
	{
		m_pID_TEXT_JinDing->SetText(thePlayerRole.GetData(CPlayerRole::TYPE_JinDing));
	}

	if (m_pID_TEXT_JinPiao)
	{
		m_pID_TEXT_JinPiao->SetText(thePlayerRole.GetData(CPlayerRole::TYPE_JinPiao));
	}

	if (m_pID_TEXT_JIFEN)
	{
		m_pID_TEXT_JIFEN->SetText(thePlayerRole.GetData(CPlayerRole::TYPE_ShopCenterScore));
	}

	
}

void CUI_ID_FRAME_PACK::RefreshJiaoZi()
{
    if(!m_pID_FRAME_PACK)
        return;

    if(!m_pID_TEXT_EspecialMoney)
        return;

	std::string text = "";
    thePlayerRole.GetGSCStringFromCurrentJiaoZi(text);

    *m_pID_TEXT_EspecialMoney = text;    
}

void CUI_ID_FRAME_PACK::RefreshArmour()
{
	if( !m_pID_FRAME_PACK )
		return;
	eTipFlag eFlag = s_CUI_ID_FRAME_SHOP.IsVisable() ? eTipFlag_ShowMoney : eTipFlag_Normal;
	for( int n=0; n<thePlayerRole.m_bag.GetNowBagSize(); n++)
	{
		if ( thePlayerRole.m_bag.IsHaveItem(n) == false )
			continue;

		SCharItem stItem;
		thePlayerRole.m_bag.GetItem( n, &stItem );

		ControlIconDrag::S_ListImg stListItem;			
		ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );

		if( pItemDetail 
			&&  pItemDetail->ucItemType == ItemDefine::ITEMTYPE_ARMOUR	)
		{
			ItemDefine::SItemCanEquip *pEquip = (ItemDefine::SItemCanEquip *)pItemDetail;
			{	
				BOOL bContinue = FALSE;
				int nCanEquipPart = 0;
				for( int i=0; i< EEquipPartType_MaxEquitPart; i++ )
				{
					if( bContinue )
					{
						continue;
					}
					if ( pEquip->arrayCanEquip[i] == 1 )
					{
						nCanEquipPart = i;
						bContinue = TRUE;
					}
				}
                bool bEnable = CPackItemEnableManager::Instance()->IsPackItemEnable( &thePlayerRole.m_bag, n );
				stListItem.SetData( &stItem, ( bEnable ? eIcon_Enable : eIcon_Disable ),
					eFlag, false, theApp->GetPlayerMgr()->GetMyID() ); 				

				bContinue = FALSE;

                if( m_newEquipMap.count( n ) > 0 && m_newEquipMap.find( n )->second )
                    stListItem.SetSparkEnable( true );
                else
                    stListItem.SetSparkEnable( false );

				m_pID_LISTIMG_PACK->SetItem( &stListItem, n );
			}
		}
	}
}

void CUI_ID_FRAME_PACK::Refeash()
{
	if( !m_pID_FRAME_PACK )
		return;
	{
		eTipFlag eFlag = s_CUI_ID_FRAME_SHOP.IsVisable() ? eTipFlag_ShowMoney : eTipFlag_Normal;

		if( m_pID_TEXT_MONEY )
		{
			std::string text = "";
			thePlayerRole.GetGSCStringFromCurrentMoney(text);
			*m_pID_TEXT_MONEY = text;
		}

		int nScrollPos = m_pID_LISTIMG_PACK->GetScrollValue();

		m_pID_LISTIMG_PACK->Clear();

		int nHeightCount = (thePlayerRole.m_bag.GetNowBagSize() + m_pID_LISTIMG_PACK->GetRowItemCnt() - 1) /
			m_pID_LISTIMG_PACK->GetRowItemCnt();
		//m_pID_LISTIMG_PACK->SetHeightMaxCnt(nHeightCount);
		m_pID_LISTIMG_PACK->SetHeightShowMaxCnt(nHeightCount > s_nPackItemHeightMaxShowCount ? s_nPackItemHeightMaxShowCount : nHeightCount);

		for( int n=0; n<thePlayerRole.m_bag.GetNowBagSize(); n++)
		{
			if ( thePlayerRole.m_bag.IsHaveItem(n) == false )
				continue;

			SCharItem stItem;
			thePlayerRole.m_bag.GetItem( n, &stItem );


			ControlIconDrag::S_ListImg stListItem;			
			ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );

			if( pItemDetail 
				&& 
				( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_WEAPON 
				|| pItemDetail->ucItemType == ItemDefine::ITEMTYPE_ARMOUR
				)
				)
			{
				ItemDefine::SItemCanEquip *pEquip = (ItemDefine::SItemCanEquip *)pItemDetail;
				{	
					BOOL bContinue = FALSE;
					int nCanEquipPart = 0;
					for( int i=0; i< EEquipPartType_MaxEquitPart; i++ )
					{
						if( bContinue )
						{
							continue;
						}
						if ( pEquip->arrayCanEquip[i] == 1 )
						{
							nCanEquipPart = i;
							bContinue = TRUE;
						}
					}
                    bool bEnable = CPackItemEnableManager::Instance()->IsPackItemEnable( &thePlayerRole.m_bag, n );
					stListItem.SetData( &stItem, ( bEnable ? eIcon_Enable:eIcon_Disable), 
						eFlag, false, theApp->GetPlayerMgr()->GetMyID() ); 				

					bContinue = FALSE;
				}
			}
			else
			{
                bool bEnable = CPackItemEnableManager::Instance()->IsPackItemEnable( &thePlayerRole.m_bag, n );
				stListItem.SetData( &stItem, bEnable ? eIcon_Enable : eIcon_Disable, eFlag );
			}

			CUI_ID_FRAME_SHOP::ItemCost *pItemCost = s_CUI_ID_FRAME_SHOP.GetItemCost(
				stItem.itembaseinfo.ustItemID);
			if ( pItemCost )
				stListItem.m_pkIconInfo->SetCost( pItemCost->nCost );

			RestoreColdDown* pRestoreCoolDown = NULL;
			pRestoreCoolDown = thePlayerRole.GetRestoreCoolDown();
			DWORD dwStartTiem,dwPeriod;
			if( pRestoreCoolDown->GetTime( stItem.itembaseinfo.ustItemID,
				&dwStartTiem, &dwPeriod ) == true )
			{
				stListItem.SetTime( dwStartTiem,dwPeriod );
			}

            if( m_newEquipMap.count( n ) > 0 && m_newEquipMap.find( n )->second )
                stListItem.SetSparkEnable( true );
            else
                stListItem.SetSparkEnable( false );

			m_pID_LISTIMG_PACK->SetItem( &stListItem, n );

		}
		m_pID_LISTIMG_PACK->SetScrollValue(nScrollPos);
	}

	s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
	s_CUI_ID_FRAME_MAIN.RefeashHotKey();
}

ControlIconDrag::S_ListImg* CUI_ID_FRAME_PACK::GetIntensifyProtectByGUID( __int64 guid )
{
	if( !m_pID_FRAME_PACK )
		return NULL;

	for( int n=0; n< thePlayerRole.m_bagMaterial.GetNowBagSize(); n++)
	{
		if ( thePlayerRole.m_bagMaterial.IsHaveItem(n) == false )
			continue;

		SCharItem stItem;
		thePlayerRole.m_bagMaterial.GetItem( n, &stItem );
		if( stItem.itembaseinfo.nOnlyInt == guid )
		{
			return m_pID_LISTIMG_Material->GetItemByIndex( n );
		}		
	}
	return NULL;
}

ControlIconDrag::S_ListImg* CUI_ID_FRAME_PACK::GetIntensifyProtect()
{
	if( !m_pID_FRAME_PACK )
		return NULL;

	for( int n=0; n< thePlayerRole.m_bagMaterial.GetNowBagSize(); n++)
	{
		if ( thePlayerRole.m_bagMaterial.IsHaveItem(n) == false )
			continue;

		SCharItem stItem;
		thePlayerRole.m_bagMaterial.GetItem( n, &stItem );
		ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );
		if( !pCommon || pCommon->ucItemType != ItemDefine::ITEMTYPE_MATERIAL )
			continue;
		ItemDefine::SCreateMaterial* pMaterial = ( ItemDefine::SCreateMaterial* )pCommon;

		if( pMaterial->stMaterialType == ItemDefine::ematerial_compound )//附加材料			
		{
			return m_pID_LISTIMG_Material->GetItemByIndex( n );
		}		
	}
	return NULL;
}


ControlIconDrag::S_ListImg* CUI_ID_FRAME_PACK::GetIntensifyAddRateByGUID( __int64 guid )
{
	if( !m_pID_FRAME_PACK )
		return NULL;

	for( int n=0; n< thePlayerRole.m_bagMaterial.GetNowBagSize(); n++)
	{
		if ( thePlayerRole.m_bagMaterial.IsHaveItem(n) == false )
			continue;

		SCharItem stItem;
		thePlayerRole.m_bagMaterial.GetItem( n, &stItem );
		if( stItem.itembaseinfo.nOnlyInt == guid )
		{
			return m_pID_LISTIMG_Material->GetItemByIndex( n );
		}		
	}
	return NULL;
}

ControlIconDrag::S_ListImg* CUI_ID_FRAME_PACK::GetIntensifyAddRate()
{
	if( !m_pID_FRAME_PACK )
		return NULL;

	for( int n=0; n< thePlayerRole.m_bagMaterial.GetNowBagSize(); n++)
	{
		if ( thePlayerRole.m_bagMaterial.IsHaveItem(n) == false )
			continue;

		SCharItem stItem;
		thePlayerRole.m_bagMaterial.GetItem( n, &stItem );
		ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );
		if( !pCommon || pCommon->ucItemType != ItemDefine::ITEMTYPE_MATERIAL )
			continue;
		ItemDefine::SCreateMaterial* pMaterial = ( ItemDefine::SCreateMaterial* )pCommon;
		
// 		if( pMaterial->stMaterialType == CItemDetail::ematerial_addrate )//附加材料			
// 		{
// 			return m_pID_LISTIMG_Material->GetItemByIndex( n );
// 		}		
	}
	return NULL;
}

void CUI_ID_FRAME_PACK::UseMountRestoreItem()
{
	if( !m_pID_FRAME_PACK )
		return;

	int nIndex = -1;
	int nId = 0;
	for( int n=0; n< thePlayerRole.m_bag.GetNowBagSize(); n++)
	{
		if ( thePlayerRole.m_bag.IsHaveItem(n) == false )
			continue;	

		SCharItem stItem;
		thePlayerRole.m_bag.GetItem( n, &stItem );//遍历背包，获得物品的名字
		if(IsGrassID(stItem.itembaseinfo.ustItemID))//判断是否是草料的itemID
// 		if( stItem.itembaseinfo.ustItemID == 6573 ||
// 			stItem.itembaseinfo.ustItemID == 6572)// 草料，从高级到低级
		{
			if ( nId < stItem.itembaseinfo.ustItemID  )
			{
				nId = stItem.itembaseinfo.ustItemID ;
				nIndex = n;
			}
		}		
	}
	ControlIconDrag::S_ListImg* pItemImg = m_pID_LISTIMG_PACK->GetItemByIndex( nIndex );
	if( !pItemImg )
		return;
		
	UseItem( m_pID_LISTIMG_PACK, &thePlayerRole.m_bag, BT_NormalItemBag,nId, nIndex );
		
}

ItemDefine::SCreateMaterial* CUI_ID_FRAME_PACK::CanUseIntensifyGemById( unsigned short ustItemId, unsigned short ustArmourLevel )
{
	if( !m_pID_FRAME_PACK )
		return NULL;


	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( ustItemId );
	if( !pItemCommon )
		return 0;
	if( pItemCommon->ucItemType != ItemDefine::ITEMTYPE_MATERIAL )
		return 0;
	ItemDefine::SCreateMaterial* pItemMaterial = ( ItemDefine::SCreateMaterial* )pItemCommon;
	
	//是升星类型并且级别符合
	if( pItemMaterial->stMaterialType == ItemDefine::ematerial_starlevel && pItemMaterial->levelLowLimit <= ustArmourLevel && pItemMaterial->levelUpLimit >= ustArmourLevel)
		return pItemMaterial;
	return 0;
}
ControlIconDrag::S_ListImg* CUI_ID_FRAME_PACK::GetIntensifyGemById( unsigned short ustItemId, unsigned short ustLevel )
{
	if( !m_pID_FRAME_PACK )
		return NULL;

	for( int n=0; n< thePlayerRole.m_bagMaterial.GetNowBagSize(); n++)
	{
		if ( thePlayerRole.m_bagMaterial.IsHaveItem(n) == false )
			continue;	

		SCharItem stItem;
		thePlayerRole.m_bagMaterial.GetItem( n, &stItem );
		if( ustItemId == stItem.itembaseinfo.ustItemID )
		{
			if( CanUseIntensifyGemById( ustItemId, ustLevel ) )
				return m_pID_LISTIMG_Material->GetItemByIndex( n );
		}
	}
	return 0;
}

ControlIconDrag::S_ListImg* CUI_ID_FRAME_PACK::GetIntensifyGem( unsigned short ustLevel )
{
	if( !m_pID_FRAME_PACK )
		return NULL;

	/////////////////////////
	///三个当前宝石的相关值
	int nBagIndex = -1; //包裹里的index
	ItemDefine::SCreateMaterial* pMaterial = 0; 
	bool bBound = false;//是否已经绑定

	for( int n=0; n< thePlayerRole.m_bagMaterial.GetNowBagSize(); n++)
	{
		if ( thePlayerRole.m_bagMaterial.IsHaveItem(n) == false )
			continue;	

		SCharItem stItem;
		thePlayerRole.m_bagMaterial.GetItem( n, &stItem );
		
		ItemDefine::SCreateMaterial* pItemMaterial = CanUseIntensifyGemById( stItem.itembaseinfo.ustItemID, ustLevel );		
		if( !pItemMaterial )
			continue;
					
		if( !pMaterial )//第一个
		{
			pMaterial = pItemMaterial;
			nBagIndex = n;
 			bBound = stItem.IsBounded();
			continue;
		}
		// 比较宝石等级
		if( pMaterial->levelUpLimit < pItemMaterial->levelUpLimit )
		{
			pMaterial = pItemMaterial;
			nBagIndex = n;
			bBound = stItem.IsBounded();
		}
		else if( pMaterial->levelUpLimit == pItemMaterial->levelUpLimit )//等级相同，比较绑定
		{
 			if( bBound && !stItem.IsBounded() )//当前的已经绑定，新的未绑定，用新的
			{
				pMaterial = pItemMaterial;
				nBagIndex = n;
 				bBound = stItem.IsBounded();
			}
		}
					
	}
	// 返回找到的宝石
	if( pMaterial )
	{
		return m_pID_LISTIMG_Material->GetItemByIndex( nBagIndex );
	}

	return NULL;
}

void CUI_ID_FRAME_PACK::Refresh(ControlListImage* pBagListImg, CItemBag2* pBag, int bagType)
{
	if( !pBagListImg )
		return;
	{
		RefreshMoney();
        RefreshJiaoZi();
		eTipFlag eFlag = s_CUI_ID_FRAME_SHOP.IsVisable() ? eTipFlag_ShowMoney : eTipFlag_Normal;

		int nScrollPos = pBagListImg->GetScrollValue();

		pBagListImg->Clear();

		int nHeightCount = (pBag->GetNowBagSize() + pBagListImg->GetRowItemCnt() - 1) /
			pBagListImg->GetRowItemCnt();

#if 0 // 0显示锁
		pBagListImg->SetHeightMaxCnt(nHeightCount);
		pBagListImg->SetHeightShowMaxCnt(nHeightCount > s_nPackItemHeightMaxShowCount ? s_nPackItemHeightMaxShowCount : nHeightCount);
#else
		//pBagListImg->SetHeightMaxCnt(nHeightCount > s_nPackItemHeightMaxShowCount ? nHeightCount : s_nPackItemHeightMaxShowCount );
		pBagListImg->SetHeightShowMaxCnt(s_nPackItemHeightMaxShowCount);
#endif
		pBagListImg->SetEnableCnt(pBag->GetNowBagSize());

		for( int n=0; n<pBag->GetNowBagSize(); n++)
		{
			if ( pBag->IsHaveItem(n) == false )
				continue;

			SCharItem stItem;
			pBag->GetItem( n, &stItem );


			ControlIconDrag::S_ListImg stListItem;			
			ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );

			if( pItemDetail 
				&& 
				( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_WEAPON 
				|| pItemDetail->ucItemType == ItemDefine::ITEMTYPE_ARMOUR
				)
				)
			{
				ItemDefine::SItemCanEquip *pEquip = (ItemDefine::SItemCanEquip *)pItemDetail;
				{	
					BOOL bContinue = FALSE;
					int nCanEquipPart = 0;
					for( int i=0; i< EEquipPartType_MaxEquitPart; i++ )
					{
						if( bContinue )
						{
							continue;
						}
						if ( pEquip->arrayCanEquip[i] == 1 )
						{
							nCanEquipPart = i;
							bContinue = TRUE;
						}
					}
                    bool bEnable = CPackItemEnableManager::Instance()->IsPackItemEnable( pBag, n );
					stListItem.SetData( &stItem, ( bEnable ? eIcon_Enable : eIcon_Disable ), eFlag ); 

                    // 新获得的装备增加闪光特效     added by ZhuoMeng.Hu		[11/12/2010]
                    if( pBagListImg && m_pID_LISTIMG_PACK && pBagListImg == m_pID_LISTIMG_PACK )
                    {
                        if( m_newEquipMap.count( n ) == 0 )
                        {
                            m_newEquipMap.insert( make_pair( n, false ) );
                        }
                        else
                        {
                            if( m_newEquipMap.find( n )->second )
                                stListItem.SetSparkEnable( true );
                            else
                                stListItem.SetSparkEnable( false );
                        }
                    }

					bContinue = FALSE;
				}
			}
			else
			{
                bool bEnable = CPackItemEnableManager::Instance()->IsPackItemEnable( pBag, n );
				stListItem.SetData( &stItem, bEnable ? eIcon_Enable : eIcon_Disable, eFlag );
			}

			CUI_ID_FRAME_SHOP::ItemCost *pItemCost = s_CUI_ID_FRAME_SHOP.GetItemCost(
				stItem.itembaseinfo.ustItemID);
			if ( pItemCost )
				stListItem.m_pkIconInfo->SetCost( pItemCost->nCost );

			RestoreColdDown* pRestoreCoolDown = NULL;
			pRestoreCoolDown = thePlayerRole.GetRestoreCoolDown();
			DWORD dwStartTiem,dwPeriod;
			if( pRestoreCoolDown->GetTime( stItem.itembaseinfo.ustItemID,
				&dwStartTiem, &dwPeriod ) == true )
			{
				stListItem.SetTime( dwStartTiem,dwPeriod );
			}

			pBagListImg->SetItem( &stListItem, n );

		}
		pBagListImg->SetScrollValue(nScrollPos);
	}

	thePlayerRole.RefreshQuestDone();
	s_CUI_ID_FRAME_Task.RefreshCurrSelect();
	s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
	s_CUI_ID_FRAME_MAIN.RefeashHotKey();
}

void CUI_ID_FRAME_PACK::RefreshPackByIndex(int index)
{
	if( !m_pID_FRAME_PACK )
		return;

	if ( !thePlayerRole.m_bag.IsHaveItem(index) )
	{
		m_pID_LISTIMG_PACK->RemoveItemByIndex( index );
		return;
	}
	eTipFlag eFlag = s_CUI_ID_FRAME_SHOP.IsVisable() ? eTipFlag_ShowMoney : eTipFlag_Normal;

	SCharItem stItem;	
	thePlayerRole.m_bag.GetItem( index, &stItem );

	ControlIconDrag::S_ListImg stListItem;			
	ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );

	if( pItemDetail 
		&& 
		( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_WEAPON 
		|| pItemDetail->ucItemType == ItemDefine::ITEMTYPE_ARMOUR
		)
		)
	{
 		ItemDefine::SItemCanEquip *pEquip = (ItemDefine::SItemCanEquip *)pItemDetail;

		BOOL bContinue = FALSE;
		int nCanEquipPart = 0;
		std::vector< ItemDefine::SItemArmour* > vSuitEquip;
		for( int i=0; i< EEquipPartType_MaxEquitPart; i++ )
		{
			if( bContinue )
			{
				continue;
			}
			if ( pEquip->arrayCanEquip[i] == 1 )
			{
				nCanEquipPart = i;
				bContinue = TRUE;
			}
		}
        bool bEnable = CPackItemEnableManager::Instance()->IsPackItemEnable( &thePlayerRole.m_bag, index );
		stListItem.SetData( &stItem, ( bEnable ? eIcon_Enable : eIcon_Disable ),
			eFlag, false, theApp->GetPlayerMgr()->GetMyID() ); 			
		const SCharItem* pCompareEquipItem = thePlayerRole.GetEquipItem( nCanEquipPart );
		if( pCompareEquipItem )
		{
			if( theIconInfoMouseTip.GetCompareIconInfo() )
			{
				theIconInfoMouseTip.GetCompareIconInfo()->SetData( (void*)pCompareEquipItem, eIcon_Enable, 0, true, theApp->GetPlayerMgr()->GetMyID() );
			}				
		}			
		
	}
	else
	{
        bool bEnable = CPackItemEnableManager::Instance()->IsPackItemEnable( &thePlayerRole.m_bag, index );
		stListItem.SetData( &stItem, bEnable ? eIcon_Enable : eIcon_Disable, eFlag );
	}

	CUI_ID_FRAME_SHOP::ItemCost *pItemCost = s_CUI_ID_FRAME_SHOP.GetItemCost(
		stItem.itembaseinfo.ustItemID);
	if ( pItemCost )
		stListItem.m_pkIconInfo->SetCost( pItemCost->nCost );

	RestoreColdDown* pRestoreCoolDown = NULL;
	pRestoreCoolDown = thePlayerRole.GetRestoreCoolDown();
	DWORD dwStartTiem,dwPeriod;
	if( pRestoreCoolDown->GetTime( stItem.itembaseinfo.ustItemID,
		&dwStartTiem, &dwPeriod ) == true )
	{
		stListItem.SetTime( dwStartTiem,dwPeriod );
	}

    if( m_newEquipMap.count( index ) > 0 && m_newEquipMap.find( index )->second )
        stListItem.SetSparkEnable( true );
    else
        stListItem.SetSparkEnable( false );

	m_pID_LISTIMG_PACK->SetItem( &stListItem, index );
}

void CUI_ID_FRAME_PACK::IconOnShiftLBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
	if( !s_CUI_ID_FRAME_PACK.GetFrame() )
		return;

	if( !pItem || pItem->IsNull() )
		return;

	ItemDefine::SItemCommon *pDetail = GettheItemDetail().GetItemByID( pItem->m_pkIconInfo->Id() );
	if( pDetail == NULL )
		return;

	ControlListImage* pBagListImg = 0;
	CItemBag2* pBag = 0;
	int bagType = BT_NormalItemBag;
	switch (pDetail->ucItemType)
	{
	case ItemDefine::ITEMTYPE_MATERIAL:
	case ItemDefine::ITEMTYPE_GEM:
		pBagListImg = s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Material;
		pBag = &thePlayerRole.m_bagMaterial;
		bagType = BT_MaterialBag;
		break;
	case ItemDefine::ITEMTYPE_TASK:
		pBagListImg = s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Task;
		pBag = &thePlayerRole.m_bagTask;
		bagType = BT_TaskBag;
		break;
	default:
		pBagListImg = s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_PACK;
		pBag = &thePlayerRole.m_bag;
		bagType = BT_NormalItemBag;
		break;
	}


	int index = pBagListImg->GetItemIndex( pItem );
	SCharItem stItem;
	if( !pBag->GetItem( index, &stItem ) )
        return;

	{
		Common::_tstring tstrName( pDetail->GetItemName() );
		S_IconInfoHero::ReplaceSpecifiedName( pDetail->ustLevel, tstrName );
		CommonChatFrame::GetActiveChatFrame()->addHyberText( tstrName.c_str(), 
			stItem.itembaseinfo.nOnlyInt, stItem.itembaseinfo.ustItemID, bagType );

	}


	unguard;
}
bool CUI_ID_FRAME_PACK::ActiveItem( ControlIconDrag* pListImgCtrl, CItemBag2* pBag, unsigned short usItemID, unsigned char ucActive )
{
	if( !m_pID_FRAME_PACK )
		return false;

	if( !pListImgCtrl )
		return false;

	for( int i = 0 ; i < pListImgCtrl->GetItemCnt() ; ++ i )
	{
		ControlIconDrag::S_ListImg* pImg = pListImgCtrl->GetItemByIndex( i );
		if( !pImg )
			continue;

		if( pImg->m_pkIconInfo->GetItemId() == usItemID )
		{
			((SCharItem*)pImg->m_pkIconInfo->GetData())->itembaseinfo.useType = ucActive;
			pImg->m_pkIconInfo->RefreshColorFrameType();
		}
	}
	// 这里遍历背包中的物品
	if( pBag )
	{
		for( int i = 0 ; i < pBag->GetNowBagSize(); ++i )
		{
			SCharItem* pSrcItem = pBag->GetCharItemFromIdx( i );
			if( pSrcItem )
				pSrcItem->itembaseinfo.useType = ucActive;
		}
	}

	// 这里遍历快捷栏的相同物品, act/deact
	for( int i = 0 ; i < s_CUI_ID_FRAME_MAIN.GetHotKeyItemSize() ; ++ i )
	{
		ControlIconDrag::S_ListImg* pImg = s_CUI_ID_FRAME_MAIN.GetHotKeyItemByIndex(i);
		if( !pImg )
			continue;
		if( pImg->m_pkIconInfo->GetItemId() == usItemID )
		{
			((SCharItem*)pImg->m_pkIconInfo->GetData())->itembaseinfo.useType = ucActive;
			pImg->m_pkIconInfo->RefreshColorFrameType();
		}
	}
	return true;
}
bool CUI_ID_FRAME_PACK::ActiveAutoUseItem( ControlIconDrag* pListImgCtrl, ItemDefine::SItemRestore *pItemRestore, SCharItem& stItem, CItemBag2* pBag, int nIndex )
{
	if( !pItemRestore )
		return false;

	// 物用等级
	if ( pItemRestore->stUseLevel >thePlayerRole.GetLevel() )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString(eText_ItemUseLevel) );
		return false;
	}
	//如果物品已经加锁 return
	if(stItem.storageinfo.bIsLocked)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString(eText_ItemHaveBeenLocked) );
		return false;
	}

	if( pItemRestore->bHPAuto || //自动回血
		pItemRestore->bMPAuto || //自动回蓝
		pItemRestore->bAutoRelive // 自动复活
		)
	{
		SCharItem* pSrcItem = pBag->GetCharItemFromIdx( nIndex );
		if( !pSrcItem )
			return false;

		if( stItem.itembaseinfo.useType == SCharItem::EUT_AutoUse )
		{
			pSrcItem->itembaseinfo.useType = SCharItem::EUT_None;			
		}
		else
		{
			pSrcItem->itembaseinfo.useType = SCharItem::EUT_AutoUse;			
		}

		ActiveItem( pListImgCtrl, pBag, stItem.itembaseinfo.ustItemID, pSrcItem->itembaseinfo.useType );

		// send to server
		// todo 		
	}
	else
	{
		return false;
	}
	return true;
}
bool CUI_ID_FRAME_PACK::coolDownRestoreItem(ItemDefine::SItemRestore *pItemRestore, const SCharItem& stItem )
{
	if( !m_pID_FRAME_PACK )
		return false;
	int itemId = stItem.itembaseinfo.ustItemID;

	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();

    // 职业限制     added by ZhuoMeng.Hu		[12/17/2010]
    int nProfession = thePlayerRole.GetProfession();
    if( !pItemRestore->arrayProfessionReq[nProfession] )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString( eText_ItemUse_ProfessionLimit ) );
        return false;
    }

	// 物用等级
	if ( pItemRestore->stUseLevel >thePlayerRole.GetLevel() )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString(eText_ItemUseLevel) );
		return false;
	}
	//如果物品已经加锁 return
	if(stItem.storageinfo.bIsLocked)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString(eText_ItemHaveBeenLocked) );
		return false;
	}

	if( pItemRestore->nUseFightStatus != ItemDefine::EUseStatusType_None )
	{
		if ( pItemRestore->nUseFightStatus == ItemDefine::EUseStatusType_NoFight &&  thePlayerRole.IsFighting() )
		{ 
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString(eText_QuestInFight) );
			return false;
		}

		if ( pItemRestore->nUseFightStatus == ItemDefine::EUseStatusType_InFight && !thePlayerRole.IsFighting() )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString(eText_QuestNoFight) );
			return false;
		}
	}

	if ( pMe )
	{
		if (!pMe->m_cFightStatus.IsCanUseItem())
		{		
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString(eClient_CantUseGood_ByDiffState) );
			return false;
		}
	}
	RestoreColdDown* pRestoreCoolDown = NULL;
	pRestoreCoolDown = thePlayerRole.GetRestoreCoolDown();
	{
		if( !pRestoreCoolDown->UseRestore( itemId, false ) )
		{
			return false;
		}
	}
	return true;
}

void CUI_ID_FRAME_PACK::Equip( unsigned int nWhere, unsigned int nPackIndex )
{
	guardfunc;
	if( !m_pID_FRAME_PACK )
		return;
	if ( nWhere >= EEquipPartType_MaxEquitPart || nPackIndex >= thePlayerRole.m_bag.GetNowBagSize() )
		return;

	SCharItem* pVisual = NULL;
	SCharItem	stPack;
	SCharItem stOldItem;


	if ( thePlayerRole.m_bag.IsHaveItem( nPackIndex ) == false )
		return;
	thePlayerRole.m_bag.GetItem( nPackIndex, &stPack );

	//stPack.SetBounded(true);

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( stPack.itembaseinfo.ustItemID );
	ItemDefine::SItemCanEquip* pItemCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
	/*if( pItemCanEquip->bFashion )
		pVisual = &thePlayerRole.m_pVisual->GetVisualArray()[nWhere];;
	else
		pVisual = &thePlayerRole.m_pVisual->GetVisualArray()[nWhere];*/
	pVisual = &thePlayerRole.m_pVisual->GetVisualArray()[nWhere];
	stOldItem = *pVisual;

	*pVisual = stPack;

	//检测是否能装备


	/*if( nWhere == EPT_LeftHandShieldPart )
	{

		if( stOldItem.itembaseinfo.ustItemID == InvalidLogicNumber)
		{
			stOldItem = thePlayerRole.m_pVisual->GetViewSuitArray()[EPT_LHandItem];
			thePlayerRole.m_pVisual->GetViewSuitArray()[EPT_LHandItem].itembaseinfo.ustItemID = 
				InvalidLogicNumber;
		}
	}*/
	/*if( nWhere == EPT_LHandItem )
	{
		if( stOldItem.itembaseinfo.ustItemID== InvalidLogicNumber )
		{
			stOldItem = thePlayerRole.m_pVisual->GetViewSuitArray()[EPT_LeftHandShieldPart];
			thePlayerRole.m_pVisual->GetViewSuitArray()[EPT_LeftHandShieldPart].itembaseinfo.ustItemID =
				InvalidLogicNumber;
		}
	}*/

	unsigned short stCount = 0;
	if ( stOldItem.itembaseinfo.ustItemID!= InvalidLogicNumber )
	{
		thePlayerRole.m_bag.ClearItem(nPackIndex);
		thePlayerRole.m_bag.PushItem( stOldItem, stCount,NULL,NULL,"", nPackIndex );
	}
	else
	{
		thePlayerRole.m_bag.PopItem( nPackIndex, stCount,NULL,NULL,"" );
	}
	RefreshPackByIndex(nPackIndex);

	bool bAecorative = (nWhere == EEquipPartType_AecorativeGoods || nWhere == EEquipPartType_AecorativeClothing );
	if (!thePlayerRole.m_charinfo.visual.IsShowAecorative()&&bAecorative)
	{
		s_CUI_ID_FRAME_BaseProperty.ID_CHECKBOX_ShowFasionOnCheckBoxCheck(NULL,NULL);
	}

	unguard;
}

bool SendEquipMsg(char bFlag,void *pData)
{
	guardfunc;
	if (bFlag)
	{
		if (s_CUI_ID_FRAME_PACK.GetItemInBagIndex() > -1)
		{
			MsgEquip msg;
            if( s_CUI_ID_FRAME_PACK.GetEquipPos() >= 0 )
            {
                msg.nEquipWhere = s_CUI_ID_FRAME_PACK.GetEquipPos();
            }
			msg.ustPackIndex = s_CUI_ID_FRAME_PACK.GetItemInBagIndex();

			if ( CPackItemEnableManager::Instance()->IsPackItemEnable( &thePlayerRole.m_bag, msg.ustPackIndex ) )
				GettheNetworkInput().SendMsg( &msg );
            s_CUI_ID_FRAME_PACK.SetEquipPos( -1 );
			return true;
		}
		else
        {
            s_CUI_ID_FRAME_PACK.SetEquipPos( -1 );
			return false;
        }
	}
	else
    {
        s_CUI_ID_FRAME_PACK.SetEquipPos( -1 );
		return false;
    }
	unguard;
}

bool SendEquipMsgToWhere(bool btell,void *pData)
{
	guardfunc;
	if (btell)
	{
		if (s_CUI_ID_FRAME_PACK.GetEquipToWhereIndex() > -1
			&&s_CUI_ID_FRAME_PACK.GetItemInBagIndex() > -1)
		{
			MsgEquipToWhere msg;
			msg.ustPackIndex = s_CUI_ID_FRAME_PACK.GetItemInBagIndex();
			msg.ustWhere = s_CUI_ID_FRAME_PACK.GetEquipToWhereIndex();
			GettheNetworkInput().SendMsg( &msg );
			return true;
		}
		else
			return false;
	}
	else
		return false;
	unguard;
}

void CUI_ID_FRAME_PACK::Equip( ControlObject* pSender, ControlObject* pMe,
							  ControlIconDrag::S_ListImg* pItemDrag,
							  ControlIconDrag::S_ListImg* pItemSrc )
{
	guardfunc;
	if( !m_pID_FRAME_PACK )
		return;

    if( !pItemSrc )
        return;

    m_nEquipPos = s_CUI_ID_FRAME_BaseProperty.GetWhere( pItemSrc );

	if (thePlayerRole.GetMyHP() <= 0||(theApp->GetPlayerMgr()->GetMe() && theApp->GetPlayerMgr()->GetMe()->IsDead()) )
	{
		return;
	}
	//战斗中能换装备，  by liaojie  11.20
	/*if (thePlayerRole.IsFighting())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString(eText_SitFailed_CurrStatus) );
		return ;
	}*/
	if ( pSender == s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_PACK )
	{
		int nPackIndex = -1;
		if( pSender == s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_PACK )
		{
			nPackIndex = m_pID_LISTIMG_PACK->GetItemIndex( pItemDrag );
		}

		if( pItemDrag->IsNull() )
			return;
		ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->Id() );

		if ( pItem )
		{
			bool bEquiped = false;
			if( pItem->ucItemType == ItemDefine::ITEMTYPE_WEAPON || pItem->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
			{
				//装备需求
				ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItem;

				if( !CanEquip( pCanEquip ) )
					return;

                m_nItemInBagIndex = nPackIndex;
                if( thePlayerRole.m_bag.m_pPackItem[nPackIndex].IsBounded() )
                {
                    MsgEquip msg;
                    msg.ustPackIndex = nPackIndex;
                    if( GetEquipPos() >= 0 )
                    {
                        msg.nEquipWhere = GetEquipPos();
                    }
                    SetEquipPos( -1 );
                    GettheNetworkInput().SendMsg( &msg );
                    bEquiped = true;
                }
                if( !bEquiped )
                {
                    if( pCanEquip->bIsCanBound )
                    {
                        s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eUI_SoulBound ), theXmlString.GetString( eClient_AddInfo_2slk_16 ),
                            CUI_ID_FRAME_MessageBox::eTypeYesNo, true, SendEquipMsg );
                    }
                    else
                    {
                        MsgEquip msg;
                        msg.ustPackIndex = nPackIndex;
                        if( GetEquipPos() >= 0 )
                        {
                            msg.nEquipWhere = GetEquipPos();
                        }
                        SetEquipPos( -1 );
                        GettheNetworkInput().SendMsg( &msg );
                        bEquiped = true;
                    }
                }
			}
		}
	}		
	unguard;
}

void CUI_ID_FRAME_PACK::showInUILayout( bool show )
{
	if( !m_pID_FRAME_PACK )
		return;
	m_pID_FRAME_PACK->SetVisable( show );

	if( show == true )
	{

		if( thePlayerRole.m_bag.GetNowBagSize() > ITEM_PACK_OLD )
		{
			RECT rc;
			m_pID_FRAME_PACK->GetRealRect( &rc );
		}
	}
}

void CUI_ID_FRAME_PACK::PopGoods( const unsigned int nIndex, ControlListImage* pBagListImg, CItemBag2* pBag, int bagType )
{
	guardfunc;
	if ( nIndex >= pBag->GetNowBagSize() )
		return;

	SCharItem item;
	bool ret = pBag->GetItem( nIndex, &item );

	pBag->ClearItem( nIndex );

	if ( ret )
	{
		ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( item.itembaseinfo.ustItemID );
		if ( pItemDetail && pItemDetail->ucItemType == ItemDefine::ITEMTYPE_RESTORE )
		{
			ItemDefine::SItemRestore* restore = (ItemDefine::SItemRestore*)pItemDetail;
			if ( restore->bHPAuto || restore->bMPAuto || restore->bAutoRelive )
			{
				thePlayerRole.refreshHotKey();
			}
		}
	}
	//
	Refresh(pBagListImg, pBag, bagType);
	unguard;
}

void CUI_ID_FRAME_PACK::PushGoods( SCharItem* pItem )
{
	if( !m_pID_FRAME_PACK )
		return;
	guardfunc;
	char szInfo[256] = {0};
	bool bHaveItem = false;
	if ( pItem->itembaseinfo.ustItemID == const_ustItemMoney )
	{
		thePlayerRole.Update( CPlayerRole::TYPE_MONEY,
			thePlayerRole.GetData(CPlayerRole::TYPE_MONEY)+pItem->itembaseinfo.value1 );
		//你的到了 金币

		int nMoney = pItem->itembaseinfo.value1;
		if (nMoney > 0)
		{
			int gold = 0,silver = 0,copper = 0;
            thePlayerRole.GetGSCFromMoney(nMoney,gold,silver,copper);

			std::stringstream sstr;
			sstr << theXmlString.GetString(eText_YouGet_Money);
			if (gold > 0)
				sstr << gold << theXmlString.GetString(eText_Money_Gold);
			if (silver > 0)
				sstr << silver << theXmlString.GetString(eText_Money_Silver);
			if (copper > 0)
				sstr << copper << theXmlString.GetString(eText_Money_Copper);

			strcpy(szInfo, sstr.str().c_str());

			RefreshMoney();

            s_CUI_ID_FRAME_GoldPlating.RefreshOkButton();
            s_CUI_ID_FRAME_Star.RefreshOkButton();
            s_CUI_ID_FRAME_FiveXing.RefreshOkButton();
            s_CUI_ID_FRAME_FiveXingChange.RefreshOkButton();
            s_CUI_ID_FRAME_FiveXingUpdate.RefreshOkButton();
            s_CUI_ID_FRAME_FiveXingDisplace.RefreshOkButton();
			s_CUI_ID_FRAME_IntensifyStar.RefreshOkButton();
		}
	}
	else
	{
		ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
		if( !pItemDetail )
			return;

		bool bAlmostFull = false;
		int nStringDef = -1;
		ControlListImage* pBagListImg = 0;
		CItemBag2* pBag = 0;
		int bagType = BT_NormalItemBag;
		switch (pItemDetail->ucItemType)
		{
		case ItemDefine::ITEMTYPE_MATERIAL:
		case ItemDefine::ITEMTYPE_GEM:
			pBagListImg = s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Material;
			pBag = &thePlayerRole.m_bagMaterial;
			bagType = BT_MaterialBag;
			if( thePlayerRole.m_bagMaterial.GetNullItemCount() <= 6 )
			{
				bAlmostFull = true;
				nStringDef = eText_AlmostFull_BagMaterial;
			}
			break;
		case ItemDefine::ITEMTYPE_TASK:
			pBagListImg = s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Task;
			pBag = &thePlayerRole.m_bagTask;
			bagType = BT_TaskBag;
			if( thePlayerRole.m_bagTask.GetNullItemCount() <= 6 )
			{
				bAlmostFull = true;
				nStringDef = eText_AlmostFull_BagTask;
			}
			break;
		default:
			pBagListImg = s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_PACK;
			pBag = &thePlayerRole.m_bag;
			bagType = BT_NormalItemBag;
			if( thePlayerRole.m_bag.GetNullItemCount() <= 6 )
			{
				bAlmostFull = true;
				nStringDef = eText_AlmostFull_BagNormal;
			}
            // 如果新物品是装备，则标记闪烁开始     added by ZhuoMeng.Hu		[11/12/2010]
            if( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_WEAPON || pItemDetail->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
                EnableSlotSpark( pBag->FindNullItemOffset(), true );

			break;
		}
		if( bAlmostFull ) // 显示背包快满的信息
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString( nStringDef) );
		}
		//
		unsigned short stCount = pItem->itembaseinfo.ustItemCount;
		switch( pBag->PushItem( *pItem, stCount ,NULL,NULL,"") ) 
		{
		case ierr_Success:
			{
				// 物品显示品质颜色
				Common::_tstring tstrName( pItemDetail->GetItemName() );
				S_IconInfoHero::ReplaceSpecifiedName( pItemDetail->ustLevel, tstrName );
				sprintf( szInfo, theXmlString.GetString(eText_YouGet_N_S), stCount, tstrName.c_str() );
				bHaveItem = true;
			}			
			break;
		case ierr_notallitempushed:
		case ierr_PackIsFull:
			break;
		default:
			return;
		}
		//
		thePlayerRole.UpdateActiveQuestStateByItem(pItemDetail->ustItemID);
		//s_CUI_Guild.SetNeedRefreshAlignment(true);
		ShowTaskItemInfo( pItemDetail );
		s_CUI_ID_FRAME_EspecialTask.RefeshBrushButton();

		//
		if ( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_RESTORE )
		{
			ItemDefine::SItemRestore* pItemRestore = (ItemDefine::SItemRestore*)pItemDetail;
			if ( pItemRestore->bHPAuto || pItemRestore->bMPAuto || pItemRestore->bAutoRelive )
			{
				thePlayerRole.refreshHotKey();
			}
		}

		Refresh(pBagListImg, pBag, bagType);
		CUIMgr::Instance()->RefreshByItemChange();
	}
	if( strcmp(szInfo, "") != 0 )
	{
		if( bHaveItem )
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Things_Get, szInfo, 0, (char*)pItem, 1 );
		else
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, szInfo );

	}
	unguard;
}

bool CUI_ID_FRAME_PACK::RemoveItem( EBagType eType, int nIndex, unsigned short usCount )
{
	if( !m_pID_FRAME_PACK )
		return false;
	ControlListImage* pBagListImg = 0;
	CItemBag2* pBag = 0;
	int bagType = BT_NormalItemBag;
	switch ( eType )
	{
	case BT_MaterialBag:
		pBagListImg = s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Material;
		pBag = &thePlayerRole.m_bagMaterial;
		bagType = BT_MaterialBag;
		break;
	case BT_TaskBag:
		pBagListImg = s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Task;
		pBag = &thePlayerRole.m_bagTask;
		bagType = BT_TaskBag;
		break;
	default:
		pBagListImg = s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_PACK;
		pBag = &thePlayerRole.m_bag;
		bagType = BT_NormalItemBag;
		break;
	}

	pBag->PopItem( nIndex, usCount, NULL, NULL, "" );
	RefreshPackByIndex( nIndex, pBagListImg, pBag, bagType);

	s_CUI_ID_FRAME_MAIN.RefeashHotKey();
	s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
	return true;
}
bool CUI_ID_FRAME_PACK::RemoveItemByGuID(Msg* pMsg)
{
	//根据唯一ID移除物品
	guardfunc;
	if( !m_pID_FRAME_PACK )
		return false;
	MsgRemoveItemByGuID *pRemoveItem = (MsgRemoveItemByGuID*)pMsg;
	ControlListImage* pBagListImg = 0;
	CItemBag2* pBag = 0;
	int bagType = BT_NormalItemBag;
	switch (pRemoveItem->ucItemBagType)
	{
	case BT_MaterialBag:
		pBagListImg = s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Material;
		pBag = &thePlayerRole.m_bagMaterial;
		bagType = BT_MaterialBag;
		break;
	case BT_TaskBag:
		pBagListImg = s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Task;
		pBag = &thePlayerRole.m_bagTask;
		bagType = BT_TaskBag;
		break;
	default:
		pBagListImg = s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_PACK;
		pBag = &thePlayerRole.m_bag;
		bagType = BT_NormalItemBag;
		break;
	}
	SCharItem stItem;
	bool bExist = pBag->GetItemByOnlyeID( pRemoveItem->GuID, &stItem );
	pBag->PopItemByGuID( pRemoveItem->GuID,pRemoveItem->ustCount,NULL,NULL,"" );	
	switch (pRemoveItem->ucItemBagType)
	{
	case BT_MaterialBag:
		RefreshMaterialPack();
		break;
	case BT_TaskBag:
		RefreshTaskPack();
		break;
	default:
		RefreshNormalPack();
		break;
	}

	char szInfo[256] = {0};
	ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID(stItem.GetItemID());
	if( pItemDetail && bExist)
	{
		Common::_tstring tstrName( pItemDetail->GetItemName() );
		S_IconInfoHero::ReplaceSpecifiedName( pItemDetail->ustLevel, tstrName );
		sprintf( szInfo, theXmlString.GetString(eText_YouLost_N_S), pRemoveItem->ustCount, tstrName.c_str() );
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Things_Get, szInfo, 0, (char*)&stItem, 1, pRemoveItem->ucItemBagType );
	}

	s_CUI_ID_FRAME_MAIN.RefeashHotKey();
	s_CUI_ID_FRAME_Exmain.RefeashHotNumber();

	return true;
	unguard;
}
bool CUI_ID_FRAME_PACK::RemoveItem( Msg* pMsg )
{
	guardfunc;
	if( !m_pID_FRAME_PACK )
		return false;

	MsgRemoveItem *pRemoveItem = (MsgRemoveItem*)pMsg;

	ControlListImage* pBagListImg = 0;
	CItemBag2* pBag = 0;
	int bagType = BT_NormalItemBag;
	switch (pRemoveItem->ucItemBagType)
	{
	case BT_MaterialBag:
		pBagListImg = s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Material;
		pBag = &thePlayerRole.m_bagMaterial;
		bagType = BT_MaterialBag;
		break;
	case BT_TaskBag:
		pBagListImg = s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Task;
		pBag = &thePlayerRole.m_bagTask;
		bagType = BT_TaskBag;
		break;
	default:
		pBagListImg = s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_PACK;
		pBag = &thePlayerRole.m_bag;
		bagType = BT_NormalItemBag;
		break;
	}

	SCharItem stItem;
	bool bExist = pBag->GetItemByItemID( pRemoveItem->ustItemID, &stItem );

	pBag->PopItemByID( pRemoveItem->ustItemID,pRemoveItem->ustCount,NULL,NULL,"" );	

	switch (pRemoveItem->ucItemBagType)
	{
	case BT_MaterialBag:
		RefreshMaterialPack();
		break;
	case BT_TaskBag:
		RefreshTaskPack();
		break;
	default:
		RefreshNormalPack();
		break;
	}

	char szInfo[256] = {0};
	ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( pRemoveItem->ustItemID );
	if( pItemDetail && bExist)
	{
		Common::_tstring tstrName( pItemDetail->GetItemName() );
		S_IconInfoHero::ReplaceSpecifiedName( pItemDetail->ustLevel, tstrName );
		sprintf( szInfo, theXmlString.GetString(eText_YouLost_N_S), pRemoveItem->ustCount, tstrName.c_str() );
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Things_Get, szInfo, 0, (char*)&stItem, 1, pRemoveItem->ucItemBagType );
	}

	s_CUI_ID_FRAME_MAIN.RefeashHotKey();
	s_CUI_ID_FRAME_Exmain.RefeashHotNumber();

	return true;
	unguard;
}

void CUI_ID_FRAME_PACK::ShowTaskItemInfo( ItemDefine::SItemCommon *pItem )
{
	guardfunc;
	assert( pItem );
	if ( !pItem )
	{
		return;
	}

	std::vector<CPlayerRole::QuestInfo*>& stQuestInfos = thePlayerRole.GetActiveQuestInfo();
	for ( int n=0; n<stQuestInfos.size(); n++ )
	{
		CPlayerRole::QuestInfo* pInfo = stQuestInfos[n];
		if (!pInfo || pInfo->chState!=QuestManager::eQuestGaining)
		{
			continue;
		}
		SQuest *pQuest = NULL;
		pQuest = theQuestManager.GetQuest( pInfo->nQuestId );		
		if ( !pQuest )
			continue;
		
		SQuestRequirement *pRequirement = NULL;
		for( int i = 0; i < pQuest->stCommitRequirement.size(); i++ )
		{
			pRequirement = &pQuest->stCommitRequirement[i];
			if( pRequirement->byType == SQuest::eRequirement_Item)
			{
				if ( ( pItem->ustItemID ==  pRequirement->Value ) )
				{
					int nItemCount = thePlayerRole.m_bag.GetItemCount( pItem->ustItemID );
					if (nItemCount < 1)
					{
						nItemCount = thePlayerRole.m_bagMaterial.GetItemCount( pItem->ustItemID );
						if (nItemCount < 1)
							nItemCount = thePlayerRole.m_bagTask.GetItemCount( pItem->ustItemID );
					}

					if ( nItemCount <= pRequirement->MaxNum )
					{
						char szInfo[128];
						MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eClient_AddInfo_2slk_125), pQuest->GetQuestName() );
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Item_TaskNeed, szInfo );
						
						MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, "%s(%d/%d)", pItem->GetItemName(), nItemCount, pRequirement->MaxNum );
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Item_TaskNeed, szInfo );
					}
				}
			}
		}

	}
	unguard;
}

bool CUI_ID_FRAME_PACK::BuyOrSellGoods( MsgAckBuyOrSellGoods* pMsg )
{
	guardfunc;
	if( !m_pID_FRAME_PACK )
		return false;
	unsigned short stCount = pMsg->ustCount;

	ControlListImage* pBagListImg = 0;
	CItemBag2* pBag = 0;
	int bagType = BT_NormalItemBag;
	switch (pMsg->ucItemBagType)
	{
	case BT_MaterialBag:
		pBagListImg = s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Material;
		pBag = &thePlayerRole.m_bagMaterial;
		bagType = BT_MaterialBag;

		m_BagTabGroup.TogglePage(m_pID_CHECKBOX_Material);
		break;
	case BT_TaskBag:
		pBagListImg = s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Task;
		pBag = &thePlayerRole.m_bagTask;
		bagType = BT_TaskBag;

		m_BagTabGroup.TogglePage(m_pID_CHECKBOX_Task);
		break;
	default:
		pBagListImg = s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_PACK;
		pBag = &thePlayerRole.m_bag;
		bagType = BT_NormalItemBag;

		m_BagTabGroup.TogglePage(m_pID_CHECKBOX_Zhuangbei);
		break;
	}

	// 买
	if ( pMsg->bIsBuy == true ) 
	{
		if ( pBag->IsHaveItem( pMsg->ustPackIndex ) == true )
			return false;
		//
		SCharItem stItem;
		memset( &stItem, 0 , sizeof(stItem) );
		stItem.itembaseinfo.ustItemID = pMsg->ustItemId;
		stItem.equipdata.usHP = -1;
		stItem.itembaseinfo.ustItemCount = pMsg->ustCount;
		stItem.itembaseinfo.n64UseTime = pMsg->n64UseTime;
		stItem.bCanUse = pMsg->bCanUse;
		stItem.itembaseinfo.nOnlyInt = pMsg->nOnlyInt;
		stItem.itembaseinfo.flag = pMsg->flag;
		for( int i = 0 ; i < SCharItem::EConstDefine_BaseRandMaxCount ; ++ i )
			stItem.equipdata.baseRands[i] = InvalidLogicNumber;
        for( int i = 0 ; i < SCharItem::EConstDefine_PurpleRandMaxCount; ++i )
            stItem.equipdata.purpleRands[i] = InvalidLogicNumber;

		unsigned short stCount = pMsg->ustCount;

		// AutoRestore
		ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );
		if ( !pItemDetail )
			return false;

		if( pItemDetail->nUseTime > 0 )
		{
			// 计算时限
			uint32 dwTime = pItemDetail->nUseTime * 60 * 60;
			TimeSpan timespan( dwTime );
			stItem.itembaseinfo.nLeftTime  = timespan.GetTimeSpan();
		}

		ItemDefine::SItemRestore* restore = NULL;
		if ( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_RESTORE )
		{
			restore = (ItemDefine::SItemRestore*)pItemDetail;
			if ( restore->bHPAuto )
				stItem.itembaseinfo.value2 = restore->dwAddHP;
			else if ( restore->bMPAuto )
				stItem.itembaseinfo.value2 = restore->dwAddMP;
		}

		pBag->PushItem( stItem, stCount, NULL,NULL,"",pMsg->ustPackIndex );

		if ( restore && ( restore->bHPAuto || restore->bMPAuto || restore->bAutoRelive ) )
		{
			thePlayerRole.refreshHotKey();
		}

		DWORD dwMoney = thePlayerRole.GetData( CPlayerRole::TYPE_MONEY );
		if (dwMoney > pMsg->dwCurMoney)
		{
			dwMoney = dwMoney - pMsg->dwCurMoney;

			int gold = 0,silver = 0, copper = 0;
            thePlayerRole.GetGSCFromMoney(dwMoney,gold,silver,copper);

			std::stringstream sstr;
			sstr << theXmlString.GetString(eText_YouLost);
			if (gold > 0)
				sstr << gold << theXmlString.GetString(eText_Money_Gold);
			if (silver > 0)
				sstr << silver << theXmlString.GetString(eText_Money_Silver);
			if (copper > 0)
				sstr << copper << theXmlString.GetString(eText_Money_Copper);

			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, sstr.str().c_str() );
		}

		Common::_tstring tstrName( pItemDetail->GetItemName() );
		S_IconInfoHero::ReplaceSpecifiedName( pItemDetail->ustLevel, tstrName );

		char szInfo[256];
		sprintf( szInfo, theXmlString.GetString(eText_YouGet_N_S), stCount, tstrName.c_str() );
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Things_Get, szInfo, 0, (char*)&stItem, 1 );
	}
	// 卖
	else 
	{
		if ( !pBag->IsHaveItem( pMsg->ustPackIndex ) )
			return false;

		SCharItem item;
		if ( !pBag->GetItem( pMsg->ustPackIndex, &item ) )
			return false;

		s_CUI_ID_FRAME_SHOP.GetBuyBackPack().AddItem(item);

		// 修改item内容，与服务器匹配，方便找错
		item.itembaseinfo.nOnlyInt = pMsg->nOnlyInt;
		item.itembaseinfo.ustItemID = pMsg->ustItemId;

		pBag->PopItem( pMsg->ustPackIndex, stCount,NULL,NULL,"" );

		ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( pMsg->ustItemId );
		if (pItemDetail)
		{

			char szInfo[256] = {0};
			char szOut[256] = {0};
			sprintf( szInfo, "%s%s%s", "[", pItemDetail->GetItemName(), "]" );
			sprintf(szOut,theXmlString.GetString(eText_LostThings),stCount,szInfo);
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Things_Get, szOut, 0, (char*)&item, 1 );
		}
		
		if ( pItemDetail && pItemDetail->ucItemType == ItemDefine::ITEMTYPE_RESTORE )
		{
			ItemDefine::SItemRestore* restore = (ItemDefine::SItemRestore*)pItemDetail;
			if ( restore->bHPAuto || restore->bMPAuto || restore->bAutoRelive )
			{
				thePlayerRole.refreshHotKey();
			}
		}

		DWORD dwMoney = thePlayerRole.GetData( CPlayerRole::TYPE_MONEY );

		if (pMsg->dwCurMoney > dwMoney)
		{
			dwMoney = pMsg->dwCurMoney - dwMoney;

			int gold = 0,silver = 0,copper = 0;
            thePlayerRole.GetGSCFromMoney(dwMoney,gold,silver,copper);

			std::stringstream sstr;
			if (gold > 0)
				sstr << gold << theXmlString.GetString(eText_Money_Gold);
			if (silver > 0)
				sstr << silver << theXmlString.GetString(eText_Money_Silver);
			if (copper >= 0)
				sstr << copper << theXmlString.GetString(eText_Money_Copper);

			Common::_tstring tstrName( pItemDetail->GetItemName() );
			S_IconInfoHero::ReplaceSpecifiedName( pItemDetail->ustLevel, tstrName );

			char szInfo[256] = {0};
			char szOut[256] = {0};
			sprintf( szInfo, "%s%s%sx%d", "[", tstrName.c_str(), "]", stCount );
			MeSprintf_s( szOut, sizeof(szOut)/sizeof(char) - 1, theXmlString.GetString(eText_YouSell), szInfo, sstr.str().c_str() );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Things_Get, szOut, 0, (char*)&item, 1 );
		}
	}
	thePlayerRole.Update( CPlayerRole::TYPE_MONEY, pMsg->dwCurMoney );

	RefreshMoney();
	RefreshPackByIndex(pBag->GetBagIndex(), pBagListImg, pBag, bagType);
	

	s_CUI_ID_FRAME_MAIN.RefeashHotKey();
	s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
	return true;
	unguard;
}

bool CUI_ID_FRAME_PACK::BuyBackOrSellBackGoods( MsgAckBuyOrSellGoods* pMsg ,MsgBuyBackItemAck* ack )
{
	guardfunc;
	if( !m_pID_FRAME_PACK )
		return false;
	unsigned short stCount = pMsg->ustCount;

	ControlListImage* pBagListImg = 0;
	CItemBag2* pBag = 0;
	int bagType = BT_NormalItemBag;
	switch (pMsg->ucItemBagType)
	{
	case BT_MaterialBag:
		pBagListImg = s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Material;
		pBag = &thePlayerRole.m_bagMaterial;
		bagType = BT_MaterialBag;

		m_BagTabGroup.TogglePage(m_pID_CHECKBOX_Material);
		break;
	case BT_TaskBag:
		pBagListImg = s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Task;
		pBag = &thePlayerRole.m_bagTask;
		bagType = BT_TaskBag;

		m_BagTabGroup.TogglePage(m_pID_CHECKBOX_Task);
		break;
	default:
		pBagListImg = s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_PACK;
		pBag = &thePlayerRole.m_bag;
		bagType = BT_NormalItemBag;

		m_BagTabGroup.TogglePage(m_pID_CHECKBOX_Zhuangbei);
		break;
	}

	// 买
	if ( pMsg->bIsBuy == true ) 
	{
		if ( pBag->IsHaveItem( pMsg->ustPackIndex ) == true )
			return false;
		//
		SCharItem stItem;
		SCharItem *pstItem;
		memset( &stItem, 0 , sizeof(stItem) );

		pstItem = s_CUI_ID_FRAME_SHOP.GetBuyBackPack().GetItemByIndex(ack->uchBuyBackPackIndex);

		memcpy(&stItem, pstItem, sizeof(SCharItem) );

		unsigned short stCount = pMsg->ustCount;

		// AutoRestore
		ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );
		if ( !pItemDetail )
			return false;

		ItemDefine::SItemRestore* restore = NULL;
		if ( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_RESTORE )
		{
			restore = (ItemDefine::SItemRestore*)pItemDetail;
		}

		pBag->PushItem( stItem, stCount, NULL,NULL,"",pMsg->ustPackIndex );

		if ( restore && ( restore->bHPAuto || restore->bMPAuto || restore->bAutoRelive ) )
		{
			thePlayerRole.refreshHotKey();
		}

		DWORD dwMoney = thePlayerRole.GetData( CPlayerRole::TYPE_MONEY );
		if (dwMoney > pMsg->dwCurMoney)
		{
			dwMoney = dwMoney - pMsg->dwCurMoney;

			int gold = 0,silver = 0, copper = 0;
            thePlayerRole.GetGSCFromMoney(dwMoney,gold,silver,copper);

			std::stringstream sstr;
			sstr << theXmlString.GetString(eText_YouLost);
			if (gold > 0)
				sstr << gold << theXmlString.GetString(eText_Money_Gold);
			if (silver > 0)
				sstr << silver << theXmlString.GetString(eText_Money_Silver);
			if (copper > 0)
				sstr << copper << theXmlString.GetString(eText_Money_Copper);

			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, sstr.str().c_str() );
		}

		Common::_tstring tstrName( pItemDetail->GetItemName() );
		S_IconInfoHero::ReplaceSpecifiedName( pItemDetail->ustLevel, tstrName );

		char szInfo[256];
		sprintf( szInfo, theXmlString.GetString(eText_YouGet_N_S), stCount, tstrName.c_str() );
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Things_Get, szInfo, 0, (char*)&stItem, 1 );
	}
	// 卖
	else 
	{
		if ( !pBag->IsHaveItem( pMsg->ustPackIndex ) )
			return false;

		SCharItem item;
		if ( !pBag->GetItem( pMsg->ustPackIndex, &item ) )
			return false;

		s_CUI_ID_FRAME_SHOP.GetBuyBackPack().AddItem(item);

		// 修改item内容，与服务器匹配，方便找错
		item.itembaseinfo.nOnlyInt = pMsg->nOnlyInt;
		item.itembaseinfo.ustItemID = pMsg->ustItemId;

		pBag->PopItem( pMsg->ustPackIndex, stCount,NULL,NULL,"" );

		ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( pMsg->ustItemId );
		if ( pItemDetail && pItemDetail->ucItemType == ItemDefine::ITEMTYPE_RESTORE )
		{
			ItemDefine::SItemRestore* restore = (ItemDefine::SItemRestore*)pItemDetail;
			if ( restore->bHPAuto || restore->bMPAuto || restore->bAutoRelive )
			{
				thePlayerRole.refreshHotKey();
			}
		}

		DWORD dwMoney = thePlayerRole.GetData( CPlayerRole::TYPE_MONEY );

		if (pMsg->dwCurMoney > dwMoney)
		{
			dwMoney = pMsg->dwCurMoney - dwMoney;

			int gold = 0,silver = 0,copper = 0;
            thePlayerRole.GetGSCFromMoney(dwMoney,gold,silver,copper);

			std::stringstream sstr;
			if (gold > 0)
				sstr << gold << theXmlString.GetString(eText_Money_Gold);
			if (silver > 0)
				sstr << silver << theXmlString.GetString(eText_Money_Silver);
			if (copper >= 0)
				sstr << copper << theXmlString.GetString(eText_Money_Copper);

			Common::_tstring tstrName( pItemDetail->GetItemName() );
			S_IconInfoHero::ReplaceSpecifiedName( pItemDetail->ustLevel, tstrName );

			char szInfo[256] = {0};
			char szOut[256] = {0};
			sprintf( szInfo, "%s%s%sx%d", "[", tstrName.c_str(), "]", stCount );
			MeSprintf_s( szOut, sizeof(szOut)/sizeof(char) - 1, theXmlString.GetString(eText_YouSell), szInfo, sstr.str().c_str() );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Things_Get, szOut, 0, (char*)&item, 1 );
		}
	}
	thePlayerRole.Update( CPlayerRole::TYPE_MONEY, pMsg->dwCurMoney );

	RefreshMoney();
	RefreshPackByIndex(pBag->GetBagIndex(), pBagListImg, pBag, bagType);

	s_CUI_ID_FRAME_MAIN.RefeashHotKey();
	s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
	return true;
	unguard;
}

static bool IfSellItemCallback(char bPressYesButton, void *pData)
{
	if (bPressYesButton && pData)
	{
		MsgBuyOrSellGoods* pMsg = (MsgBuyOrSellGoods*)pData;
		GettheNetworkInput().SendMsg( pMsg );
		return true;
	}
	return false;
}

static bool SellItemCallback(const char* szInputData, void *pData)
{
	int nGoodsCount = atoi( szInputData );
	if ( nGoodsCount <= 0 )
		return false;

	MsgBuyOrSellGoods* pMsg = (MsgBuyOrSellGoods*)pData;
	if (!s_CUI_ID_FRAME_SHOP.IsRemoteClose())
	{
		pMsg->bIsPocketShop = true;
	}
	else
	{
		pMsg->bIsPocketShop = false;
	}
	ItemDefine::SItemCommon *pItem = GettheItemDetail().GetItemByID(pMsg->ustItemId);
	if ( !pItem )
		return false;

	if ( nGoodsCount > pMsg->ustCount )
		return false;

	pMsg->ustCount = nGoodsCount;

	GameSetting::eGameSettingCategory eSellPrompt = pItem->ustLevel < 6
		? (GameSetting::eGameSettingCategory)(GameSetting::eGSC_SellPrompt1 + pItem->ustLevel)
		: GameSetting::eGSC_SellPrompt6;
	if ( GameSetting::Instance()->GetLevel( eSellPrompt ) )
	{
		Common::_tstring tstrName( pItem->GetItemName() );
		S_IconInfoHero::ReplaceSpecifiedName( pItem->ustLevel, tstrName );
		char buf[256];
		switch (pItem->ustLevel)
		{
		case 1:
			sprintf(buf, theXmlString.GetString(eClient_IfSellItem2), nGoodsCount, tstrName.c_str());
			break;
		case 2:
			sprintf(buf, theXmlString.GetString(eClient_IfSellItem3), nGoodsCount, tstrName.c_str());
			break;
		case 3:
			sprintf(buf, theXmlString.GetString(eClient_IfSellItem4), nGoodsCount, tstrName.c_str());
			break;
		case 4:
			sprintf(buf, theXmlString.GetString(eClient_IfSellItem5), nGoodsCount, tstrName.c_str());
			break;
		case 5:
			sprintf(buf, theXmlString.GetString(eClient_IfSellItem6), nGoodsCount, tstrName.c_str());
			break;
		default:
			sprintf(buf, theXmlString.GetString(eClient_IfSellItem1), nGoodsCount, tstrName.c_str());
			break;
		}
        // 消息框用模态，禁止拖动包裹物品
		s_CUI_ID_FRAME_MessageBox.Show( buf, "", CUI_ID_FRAME_MessageBox::eTypeYesNo,
			true, IfSellItemCallback, pMsg, sizeof(MsgBuyOrSellGoods) );
	}
	else
	{
		MsgBuyOrSellGoods* pMsg = (MsgBuyOrSellGoods*)pData;
		GettheNetworkInput().SendMsg( pMsg );
	}

	return true;
}

void CUI_ID_FRAME_PACK::SellItem(ControlIconDrag::S_ListImg* pListImg, ControlListImage* pBagListImg, CItemBag2* pBag, int bagType)
{
	if ( pListImg->IsNull() )
		return;

	int nPackIndex = pBagListImg->GetItemIndex( pListImg );

	//如果物品已经加锁 return			
	SCharItem stItem;
	if( !pBag->GetItem( nPackIndex, &stItem ) )
        return;
	if(stItem.storageinfo.bIsLocked)
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eText_ItemHaveBeenLocked ) );
		return;
	}
	if(stItem.IsLock())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString(eText_ItemLockSale) );
		return;
	}

	ItemDefine::SItemCommon *pItem = GettheItemDetail().GetItemByID(pListImg->m_pkIconInfo->Id());
	if ( !pItem )
		return;
	// 是否可买卖
	if ( !pItem->bIsCanSellShop )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString( eClient_AddInfo_2slk_35 ) );
		return;
	}

    // 安全保护
    if( CWealthProtect::Instance().IsInProtectTime() || CPreventWallow::Instance().IsFCMNotHealthy() )
        return;

	MsgBuyOrSellGoods msg;
	msg.nGuid = pListImg->m_pkIconInfo->GetOnlyId();
	msg.ustItemId = pItem->ustItemID;
	msg.bIsBuy = false;
	msg.ustPackIndex = nPackIndex;
	msg.ustCount = pListImg->m_pkIconInfo->Count();
	msg.ucItemBagType = bagType;

	if (pListImg->m_pkIconInfo->Count() > 1 && (GetKeyboardInput(DIK_LSHIFT) || GetKeyboardInput(DIK_RSHIFT) ) )
	{
		s_CUI_InputBox.Show( "",
			true, true, SellItemCallback,
			&msg, sizeof(msg) );
		s_CUI_InputBox.SetMaxValue(msg.ustCount);
		s_CUI_InputBox.EditInput_SetText(msg.ustCount);
	}
	else
	{
		char buf[64] = {0};
		sprintf(buf, "%d", msg.ustCount);
		SellItemCallback(buf, &msg);
	}
}

void CUI_ID_FRAME_PACK::SetDestroyItem(bool v)
{
	if( !m_pID_FRAME_PACK )
		return;

	if (v)
		EnableDestroyItem();
	else
		DisableDestroyItem();
}

bool CUI_ID_FRAME_PACK::ShowSplitInputBox(ControlListImage* pBagListImg, ControlIconDrag::S_ListImg* pItem, CItemBag2* pBag, int bagType)
{
	unsigned int nSrcIndex = pBagListImg->GetItemIndex( pItem );

	//如果物品加密则不能删除
	SCharItem stBagItemSrc;
	if (pBag->IsHaveItem(nSrcIndex))
	{
		pBag->GetItem( nSrcIndex, &stBagItemSrc );
		if(stBagItemSrc.storageinfo.bIsLocked)
		{
			s_CUI_ID_FRAME_MessageBox.Show(  theXmlString.GetString(eText_ItemHaveBeenLocked) );
			return false;
		}
		else if (stBagItemSrc.itembaseinfo.ustItemCount < 2)
			return false;
	}
	else
	{
		return false;
	}

	s_ptSplitMousePos = theUiManager.m_ptMoust;
	pBagListImg->GetTilePt( s_ptSplitMousePos.x, s_ptSplitMousePos.y, &s_ptSplitItemPos );
	m_bShiftRBSplitItem = true;

	BagInfo bagInfo;
	bagInfo.pBagListImg = pBagListImg;
	bagInfo.pBag = pBag;
	bagInfo.bagType = bagType;

	s_CUI_InputBox.SetVisable(true);
	if( s_CUI_InputBox.GetFrame() )
	{
		s_CUI_InputBox.GetFrame()->GetData()->m_nAlignMode = AlignMode_LeftTop;
		s_CUI_InputBox.GetFrame()->SetScreenPos(s_ptSplitMousePos.x, s_ptSplitMousePos.y);

		s_CUI_InputBox.Show( "", true, true, UIPACK_SplitPackItem, &bagInfo, sizeof(bagInfo) );
		s_CUI_InputBox.SetMaxValue(stBagItemSrc.itembaseinfo.ustItemCount);
		s_CUI_InputBox.EditInput_SetText( 1 );
	}
	return true;
}

void CUI_ID_FRAME_PACK::SetSplitItem(bool v)
{
	if( !m_pID_FRAME_PACK )
		return;

	if (v)
		EnableSplitItem();
	else
	{
		m_nSplitCount = 0;
		DisableSplitItem();
	}
}

bool CUI_ID_FRAME_PACK::GetSplitItem()
{
	if( !m_pID_FRAME_PACK )
		return false;
	return m_bSplitItem;
}

bool CUI_ID_FRAME_PACK::IsDecomposeItem()
{
	if ( m_pID_FRAME_PACK == NULL || m_pID_CHECKBOX_Decompose == NULL)
		return false;
	return m_pID_CHECKBOX_Decompose->IsChecked();
}

void CUI_ID_FRAME_PACK::DecomposeItem(bool cancel)
{
	static MouseManager::E_CursorType oldUICursorType = MouseManager::Type_Arrow;
	if (cancel)
	{
		m_pID_CHECKBOX_Decompose->SetCheck(false);

		theMouseManager.SetCanSetCursor(true);
		theMouseManager.SetUICursor(oldUICursorType);
		theMouseManager.SetCanSetCursor(false);
	}
	else
	{
		m_pID_CHECKBOX_Decompose->SetCheck(true);
		oldUICursorType = theMouseManager.GetCursor();

		theMouseManager.SetCanSetCursor(true);
		theMouseManager.SetUICursor(MouseManager::Type_Decompose);
		theMouseManager.SetCanSetCursor(false);
	}
}

bool CUI_ID_FRAME_PACK::GetLockItem()
{
	if( !m_pID_FRAME_PACK )
		return false;
	return m_bLockItem;
}

bool CUI_ID_FRAME_PACK::GetUnLockItem()
{
	if( !m_pID_FRAME_PACK )
		return false;
	return m_bUnLockItem;
}

void CUI_ID_FRAME_PACK::SetLockItem(bool b)
{
	if( !m_pID_FRAME_PACK )
		return;
	if (b)
		EnableLockItem();
	else
		DisableLockItem();
}

void CUI_ID_FRAME_PACK::SetUnLockItem(bool b)
{
	if( !m_pID_FRAME_PACK )
		return;
	if (b)
		EnableUnLockItem();
	else
		DisableUnLockItem();
}

void CUI_ID_FRAME_PACK::RefreshCooldown()
{
	if( !m_pID_FRAME_PACK )
		return;
	SCharItem stItem;		
	for( int n=0; n<thePlayerRole.m_bag.GetNowBagSize(); n++)
	{
		if ( thePlayerRole.m_bag.IsHaveItem(n) == false )
			continue;
		thePlayerRole.m_bag.GetItem( n, &stItem );

		RestoreColdDown* pRestoreCoolDown = thePlayerRole.GetRestoreCoolDown();
		DWORD dwStartTiem,dwPeriod;
		if ( pRestoreCoolDown->GetTime( stItem.itembaseinfo.ustItemID, &dwStartTiem, &dwPeriod ) )
			m_pID_LISTIMG_PACK->GetItemByIndex(n)->SetTime( dwStartTiem,dwPeriod );
	}
}

bool CUI_ID_FRAME_PACK::CanEquip(ItemDefine::SItemCanEquip *pCanEquip)
{
	//战斗时能换装备 
	/*if( theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->HasFightFlag(eFighting) )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString( eText_SitFailed_CurrStatus ) );
		return false;
	}*/
	if( pCanEquip->cEquipSexReq != -1 && pCanEquip->cEquipSexReq != thePlayerRole.GetSex() )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString( eText_Equip_Error_Sex ) );
		return false;
	}
	if (pCanEquip->stEquipLevelReq > thePlayerRole.GetLevel())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString( eText_Equip_Error_Level ) );
		return false;
	}
	if( !pCanEquip->arrayEquipArmsReq[thePlayerRole.GetProfession()])
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString( eText_Equip_Error_Profession ) );
		return false;
	}
	return true;
}

// 分解物品
void SendItemDecomposeRequest(void *data)
{
	if (data == NULL)
		return;

	MsgAckReduceItem *msg = reinterpret_cast<MsgAckReduceItem *> (data);
	GettheNetworkInput().SendMsg(msg);
}

void CUI_ID_FRAME_PACK::CallIntonationUtility_Start( void* pData )
{
	if ( !pData )
		return;
	IntonationUtility_Start(500, theXmlString.GetString(eText_Decompound_Progress), SendItemDecomposeRequest, pData, sizeof(MsgAckReduceItem));
}

bool DecomposeRequest(const char bPressYesButton, void *pData)
{
	if ( bPressYesButton )
	{
		// 开始分解读条
		CPlayer *me = theHeroGame.GetPlayerMgr()->GetMe();
		if (me != NULL && !me->IsMoving() && !me->IsJumping())
		{
			s_CUI_ID_FRAME_PACK.CallIntonationUtility_Start( pData );
		}
	}

	return true;
}

bool CUI_ID_FRAME_PACK::PackOnIconButtonClick(ControlListImage* pBagListImg, ControlIconDrag::S_ListImg* pItem, CItemBag2* pBag, int bagType)
{
	if (pItem && pItem->m_eEnable == eIcon_Disable) //lyh++ 左键点击包裹物品，如果该物品现在正被影像，则不可进行一下相关操作
	{
        return false;
	}
	if (m_bDestroyItem)
	{
		unsigned int nSrcIndex = nSrcIndex = pBagListImg->GetItemIndex( pItem );

		//如果物品加密则不能删除
		SCharItem stBagItemSrc;
		if(thePlayerRole.m_bag.IsHaveItem(nSrcIndex))
		{
			thePlayerRole.m_bag.GetItem( nSrcIndex, &stBagItemSrc );
			if(stBagItemSrc.storageinfo.bIsLocked)
			{
				s_CUI_ID_FRAME_MessageBox.Show(  theXmlString.GetString(eText_ItemHaveBeenLocked) );
				return false;
			}		

			if(stBagItemSrc.IsLock())
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString(eText_ItemLockDestory) );
				return true;
			}
		}
		else
		{
			return false;
		}

		//--------------------------
        // 判断是否安全保护状态
        if( !CWealthProtect::Instance().IsInProtectTime() )
        {
		    MsgMoveGoodsReq msg;
		    msg.ustSrcIndex = nSrcIndex;
			msg.nGuID = thePlayerRole.m_bag.m_pPackItem[nSrcIndex].itembaseinfo.nOnlyInt;
		    msg.ustDstIndex = ITEM_DISTORY;
		    msg.ustCount = thePlayerRole.m_bag.m_pPackItem[nSrcIndex].itembaseinfo.ustItemCount;
		    msg.ucItemBagType = bagType;
            ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( thePlayerRole.m_bag.m_pPackItem[nSrcIndex].itembaseinfo.ustItemID );
            if( pItemCommon )
            {
                DWORD dwColor = S_IconInfoHero::GetQualityColor( pItemCommon->ustLevel );
                char strItemColor[MAX_PATH] = {0};
                char strMessage[MAX_PATH] = {0};
                MeSprintf_s(strItemColor, sizeof(strItemColor)/sizeof(char) - 1,"{#%x=%s#}", dwColor, pItemCommon->GetItemName());
                MeSprintf_s(strMessage,sizeof(strMessage)/sizeof(char) - 1, theXmlString.GetString(eClient_AddInfo_2slk_27), thePlayerRole.m_bag.m_pPackItem[nSrcIndex].itembaseinfo.ustItemCount, 
                    strItemColor);
                s_CUI_ID_FRAME_MessageBox.Show( strMessage, theXmlString.GetString(eClient_AddInfo_2slk_28),
                    CUI_ID_FRAME_MessageBox::eTypeYesNo, false,
                    RemoveSomething,&msg,sizeof(MsgMoveGoodsReq));
            }
        }
		return true;
	}
	else if (s_CUI_ID_FRAME_PACK.GetSplitItem())
	{
		return ShowSplitInputBox(pBagListImg, pItem, pBag, bagType);
	}
	else if (s_CUI_ID_FRAME_SHOP.GetRepair() || m_bRepair)
	{
		unsigned int nSrcIndex = pBagListImg->GetItemIndex( pItem );

		SCharItem stBagItemSrc;
		if (pBag->IsHaveItem(nSrcIndex))
		{
			pBag->GetItem( nSrcIndex, &stBagItemSrc );

			ItemDefine::SItemCanEquip *pItemCanEquip = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID(
				stBagItemSrc.itembaseinfo.ustItemID );
			if (pItemCanEquip &&
				(pItemCanEquip->ucItemType == ItemDefine::ITEMTYPE_WEAPON ||
				 pItemCanEquip->ucItemType ==  ItemDefine::ITEMTYPE_ARMOUR ) )
			{
				int nItemHp = stBagItemSrc.equipdata.usHP;
				int nItemMaxHp = pItemCanEquip->stHPMax;
				if( nItemHp < nItemMaxHp )
				{
					MsgRepairItem msg;	
					CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
					if(pMe)
						msg.header.stID =  pMe->GetID();
					msg.eType = MsgRepairItem::RT_Pack;
					msg.stIndex = nSrcIndex;
					msg.nGuid = stBagItemSrc.itembaseinfo.nOnlyInt;
					msg.bIsCostRmb = false;
					GettheNetworkInput().SendMsg(&msg);
				}
			}
		}
		return false;
	}
	else if (s_CUI_ID_FRAME_PACK.GetLockItem())
	{
		unsigned int nSrcIndex = pBagListImg->GetItemIndex( pItem );

		//如果已加锁返回
		SCharItem stBagItemSrc;
		if (pBag->IsHaveItem(nSrcIndex))
		{
			pBag->GetItem( nSrcIndex, &stBagItemSrc );

			ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( stBagItemSrc.itembaseinfo.ustItemID );

			if(!pItemDetail)
				assert(false);



			if(pItemDetail->ucItemType != ItemDefine::ITEMTYPE_ARMOUR
				&& pItemDetail->ucItemType != ItemDefine::ITEMTYPE_WEAPON)
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString(eText_ItemCannotLock) );
				s_CUI_ID_FRAME_PACK.SetLockItem(false);
				return false;
			}
			else if(stBagItemSrc.IsLock()&&!stBagItemSrc.GetUnLockTime())
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString(eText_ItemHasLocked) );
				s_CUI_ID_FRAME_PACK.SetLockItem(false);
				return false;
			}
		}
		else
		{
			s_CUI_ID_FRAME_PACK.SetLockItem(false);
			return false;
		}

	    MsgLockItemReq msg;
	    msg.ustItemIndex = nSrcIndex;
		msg.nGuID = stBagItemSrc.itembaseinfo.nOnlyInt;
	    msg.uchBagType = bagType;

        ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( stBagItemSrc.itembaseinfo.ustItemID );
        if( pItemCommon )
        {
            DWORD dwColor = S_IconInfoHero::GetQualityColor( pItemCommon->ustLevel );
            char strItemColor[MAX_PATH] = {0};
            char strMessage[MAX_PATH] = {0};
            MeSprintf_s(strItemColor,sizeof(strItemColor)/sizeof(char) - 1, "{#%x=%s#}", dwColor, pItemCommon->GetItemName());
            MeSprintf_s(strMessage, sizeof(strMessage)/sizeof(char) - 1,theXmlString.GetString(eClient_AddInfo_2slk_27), stBagItemSrc.itembaseinfo.ustItemCount, 
                strItemColor);
            
			//lyh++ 对于已经解锁的正在解锁中的物品 进行枷锁，提示物品物品处在解锁状态
			if (stBagItemSrc.GetUnLockTime())
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString(eText_ItemCannotUnlock) );
				s_CUI_ID_FRAME_PACK.SetUnLockItem(false);
				return true;
			}

            s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_ItemLockedContext), theXmlString.GetString(eText_ItemLockedContext),//是否确定加锁
                CUI_ID_FRAME_MessageBox::eTypeYesNo, false ,
                LockItem, &msg, sizeof(MsgLockItemReq));

			s_CUI_ID_FRAME_PACK.SetLockItem(false);
        }                
		return true;
	}
	else if(s_CUI_ID_FRAME_PACK.GetUnLockItem())
	{
		unsigned int nSrcIndex = pBagListImg->GetItemIndex( pItem );

		//如果已加锁返回
		SCharItem stBagItemSrc;
		if (pBag->IsHaveItem(nSrcIndex))
		{
			pBag->GetItem( nSrcIndex, &stBagItemSrc );
			if(!stBagItemSrc.IsLock())
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString(eText_ItemHasNotLocked) );
				s_CUI_ID_FRAME_PACK.SetUnLockItem(false);
				return false;
			}
			else if(stBagItemSrc.GetUnLockTime())
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString(eText_ItemCannotUnlock) );
				s_CUI_ID_FRAME_PACK.SetUnLockItem(false);
				return false;
			}
		}
		else
		{
			s_CUI_ID_FRAME_PACK.SetUnLockItem(false);
			return false;
		}

		MsgUnLockItemReq msg;
	    msg.ustItemIndex = nSrcIndex;
		msg.nGuID = stBagItemSrc.itembaseinfo.nOnlyInt;
	    msg.uchBagType = bagType;

        ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( stBagItemSrc.itembaseinfo.ustItemID );
        if( pItemCommon )
        {
            DWORD dwColor = S_IconInfoHero::GetQualityColor( pItemCommon->ustLevel );
            char strItemColor[MAX_PATH] = {0};
            char strMessage[MAX_PATH] = {0};
            sprintf(strItemColor, "{#%x=%s#}", dwColor, pItemCommon->GetItemName());
            sprintf(strMessage, theXmlString.GetString(eClient_AddInfo_2slk_27), stBagItemSrc.itembaseinfo.ustItemCount, 
                strItemColor);
            s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_ItemUnLockedContext), theXmlString.GetString(eText_ItemUnLockedContext),//是否确定解锁
                CUI_ID_FRAME_MessageBox::eTypeYesNo, false ,
                UnLockItem, &msg, sizeof(MsgUnLockItemReq));

			s_CUI_ID_FRAME_PACK.SetUnLockItem(false);
        }
	}
	else if (m_pID_CHECKBOX_Decompose->IsChecked()) // 分解物品
	{
		unsigned int srcIndex = pBagListImg->GetItemIndex(pItem);
		if (!thePlayerRole.m_bag.IsHaveItem(srcIndex))
		{
			return false;
		}
		
		SCharItem bagItemSrc;
		thePlayerRole.m_bag.GetItem(srcIndex, &bagItemSrc);

		// 物品已被锁定, 无法分解
		if (bagItemSrc.storageinfo.bIsLocked)
		{
			s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_ItemHaveBeenLocked));
			return false;
		}
		if (bagItemSrc.IsLock())
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString(eText_ItemLockDestory) );
			return true;
		}

		// 判断是否安全保护状态
		if (CWealthProtect::Instance().IsInProtectTime())
		{
			return false;
		}

		// 装备能否分解
		uint32 isItemCanDecompose = GettheItemDetail().IsCanSplitItem(bagItemSrc.GetItemID());
		if (isItemCanDecompose != ER_Success)
		{
			CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Info_ChatSys, theXmlString.GetString(eText_ItemDecompose_Cant));
			return false;
		}

		ItemDefine::SItemCommon *itemCommon = GettheItemDetail().GetItemByID(bagItemSrc.GetItemID());
		if (itemCommon == NULL)
		{
			return false;
		}

		//如果装备镶嵌了宝石或者装备强化过，给messagebox提示
		int nHole = bagItemSrc.equipdata.gemHoleCount;
		bool HasGem = false;
		for (int i = 0; i < nHole; ++i)
		{
			if (bagItemSrc.equipdata.gemIds[i] != 0)
			{
				HasGem = true;
				break;
			}		
		}
		if ( bagItemSrc.equipdata.ucLevel > 0 || HasGem )
		{
			MsgAckReduceItem msg;
			msg.index = srcIndex;
			msg.guid = bagItemSrc.itembaseinfo.nOnlyInt;

			int strIndex = eText_Decompose_HasStarLevel;
			if ( HasGem )
				strIndex = eText_Decompose_HasGem;

			s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(strIndex), "", CUI_ID_FRAME_MessageBox::eTypeYesNo, true, DecomposeRequest, &msg, sizeof(MsgAckReduceItem));

			theIconDragManager.ClearDrag();
			theIconDragManager.m_pLastSelItem = NULL;
			theIconDragManager.SetRemoveIcon(false);

			return true;
		}


		// 开始分解读条
		CPlayer *me = theHeroGame.GetPlayerMgr()->GetMe();
		if (me != NULL && !me->IsMoving() && !me->IsJumping())
		{
			MsgAckReduceItem msg;
			msg.index = srcIndex;
			msg.guid = bagItemSrc.itembaseinfo.nOnlyInt;
			// 应策划要求, 分解物品读条改为0.5秒
			IntonationUtility_Start(500, theXmlString.GetString(eText_Decompound_Progress), SendItemDecomposeRequest, &msg, sizeof(MsgAckReduceItem));
		}
	}
	return true;
}

bool CUI_ID_FRAME_PACK::PackOnIconRButtonUp(ControlListImage* pBagListImg, ControlIconDrag::S_ListImg* pItem, CItemBag2* pBag, int bagType)
{
	//光标置回原来的状态
	if (m_bCancelOperator)
	{
		m_bCancelOperator = false;
		return true;
	}

	s_CUI_ID_FRAME_PACK.SetInUIFrameLock(false);
	s_CUI_ID_FRAME_PACK.SetInUIFrameUnLock(false);
	s_CUI_ID_FRAME_Storage.SetInUIFrameLock(false);
	s_CUI_ID_FRAME_Storage.SetInUIFrameUnLock(false);
	if (!pItem || pItem->IsNull() || pItem->m_eEnable == eIcon_Disable )
		return false;

	int nPackIndex = pBagListImg->GetItemIndex( pItem );

	SCharItem stItem;
	if( !pBag->GetItem( nPackIndex, &stItem ) )
		return false;

	if( !stItem.bCanUse )
	{
		MsgReqResetTime msg;
		msg.ustBagType = BT_NormalItemBag;
		msg.ustIdx = nPackIndex;

		char szBuffer[1024] ={0};

		ItemDefine :: SItemCommon* pCommon = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );
		if( pCommon )
		{
			assert("name.h error" && 0 );
			return false;
		}
		else
			return false;

	}

	if(s_CUI_ID_FRAME_SHOP.IsVisable())
	{
		if (s_CUI_ID_FRAME_SHOP.CHECKBOX_Goumai_IsChecked())
		{
			if(s_CUI_ID_FRAME_SHOP.GetIsGuildShop())
			{
				//公会商店不允许出售物品
				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_Guild_SellItem));
				return true;
			}
			SellItem(pItem, pBagListImg, pBag, bagType);
		}
		return true;	//如果商店界面打开的话 右键就只能买卖。。
	}
// 	if( s_CUI_ID_FRAME_Compound.IsVisable() )  // 生产界面
// 	{
// 		s_CUI_ID_FRAME_Compound.ID_LISTIMG_EspecialOnIconDragOn( pBagListImg, NULL, pItem, 0 );
// 	}
	if( s_CUI_ID_FRAME_Star.IsVisable() ) // 升星界面
	{
		if( bagType == BT_NormalItemBag )
			s_CUI_ID_FRAME_Star.ID_LISTIMG_ArmourOnIconDragOn( pBagListImg, NULL, pItem, 0 );
 		else if( bagType == BT_MaterialBag  )
 		{
			s_CUI_ID_FRAME_Star.ID_LISTIMG_MaterialOnIconDragOn(pBagListImg, NULL, pItem, 0);	
// 			switch( s_CUI_ID_FRAME_Star.GetItemMaterialType( pItem->m_pkIconInfo->GetItemId() ) )
// 			{
// 			case ItemDefine::ematerial_starlevel:
// 				s_CUI_ID_FRAME_Star.ID_LISTIMG_MaterialOnIconDragOn( pBagListImg, NULL, pItem, 0 );
// 				break;
// 			}			
 		}
		else if (bagType == BT_TaskBag)
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseStar_Failed, theXmlString.GetString(eClient_SkillSuitCannotUpStar) );
			return false;
		}
		return true;
	}
	if( s_CUI_ID_FRAME_Soul.IsVisable() ) // 灵魂铭刻界面
	{
		if( bagType == BT_NormalItemBag )
			s_CUI_ID_FRAME_Soul.ID_LISTIMG_ArmourOnIconDragOn( pBagListImg, NULL, pItem, 0 );
		else if( bagType == BT_MaterialBag  )
			s_CUI_ID_FRAME_Soul.OnMaterialItemDrag( pBagListImg, pItem );
		return true;
	}
	if( s_CUI_ID_FRAME_Purple.IsVisable() ) // 鎏金界面
	{
		if( bagType == BT_NormalItemBag )
			s_CUI_ID_FRAME_Purple.ID_LISTIMG_EquipOnIconDragOn( pBagListImg, NULL, pItem, 0 );
		return true;
	}
	if( s_CUI_ID_FRAME_Repurple.IsVisable() ) // 鎏金界面
	{
		if( bagType == BT_NormalItemBag )
			s_CUI_ID_FRAME_Repurple.ID_LISTIMG_EquipOnIconDragOn( pBagListImg, NULL, pItem, 0 );
		return true;
	}
	if( s_CUI_ID_FRAME_Hole.IsVisable() ) // 打孔界面
	{
		if( bagType == BT_NormalItemBag )
			s_CUI_ID_FRAME_Hole.ID_LISTIMG_ArmourOnIconDragOn( pBagListImg, NULL, pItem, 0 );
		return true;
	}
	if( s_CUI_ID_FRAME_Gem.IsVisable() ) // 镶嵌界面
	{
		if( bagType == BT_NormalItemBag )
			s_CUI_ID_FRAME_Gem.ID_LISTIMG_ArmourOnIconDragOn( pBagListImg, NULL, pItem, 0 );
		else if( bagType = BT_MaterialBag )
		{
			ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );
			if(pCommon)
			{
				if (pCommon->ucItemType == ItemDefine::ITEMTYPE_GEM)
				{
					s_CUI_ID_FRAME_Gem.RClickGemIn(pBagListImg,  pItem);
				}
				else if(pCommon->ucItemType == ItemDefine::ITEMTYPE_MATERIAL)
				{
					/*ItemDefine::SCreateMaterial* pMaterial = (ItemDefine::SCreateMaterial*)pCommon;

					if(pMaterial->stMaterialType == ItemDefine::ematerial_inlay)
					{
						s_CUI_ID_FRAME_Gem.ID_LISTIMG_Material1OnIconDragOn( pBagListImg, NULL, pItem, 0 );
					}
					else if(pMaterial->stMaterialType == ItemDefine::ematerial_rateboll)
					{
						s_CUI_ID_FRAME_Gem.ID_LISTIMG_Material2OnIconDragOn( pBagListImg, NULL, pItem, 0 );
					}*/
				}
			}
		}
		return true;
	}
	if( s_CUI_ID_FRAME_GemRemove.IsVisable() ) // 宝石移除界面
	{
		if( bagType == BT_NormalItemBag )
			s_CUI_ID_FRAME_GemRemove.ID_LISTIMG_ArmourOnIconDragOn( pBagListImg, NULL, pItem, 0 );
		return true;
	}
	if( s_CUI_ID_FRAME_GemReplace.IsVisable() ) // 宝石替换界面
	{
		if( bagType == BT_NormalItemBag )
			s_CUI_ID_FRAME_GemReplace.ID_LISTIMG_ArmourOnIconDragOn( pBagListImg, NULL, pItem, 0 );
		return true;
	}
	if( s_CUI_ID_FRAME_EquipCopy.IsVisable() ) // 保值界面
	{
		if( bagType == BT_NormalItemBag )
			s_CUI_ID_FRAME_EquipCopy.ArmourOnIconDragOn( pBagListImg, pItem);
		return true;
	}
	if( s_CUI_ID_FRAME_EquipReturn.IsVisable() ) // 装备回收界面
	{
		if( bagType == BT_NormalItemBag )
			s_CUI_ID_FRAME_EquipReturn.ID_LISTIMG_EquipOnIconDragOn( pBagListImg, NULL, pItem, 0 );
		return true;
	}
	if( s_CUI_ID_FRAME_Symbol.IsVisable() ) // 符文吸蓝界面
	{
		if( bagType == BT_NormalItemBag )
			s_CUI_ID_FRAME_Symbol.ID_LISTIMG_EquipOnIconDragOn( pBagListImg, NULL, pItem, 0 );
		return true;
	}
	if( s_CUI_ID_FRAME_Amulet.IsVisable() ) // 护身符上色界面
	{
		if( bagType == BT_NormalItemBag )
			s_CUI_ID_FRAME_Amulet.ID_LISTIMG_AmuletOnIconDragOn( pBagListImg, NULL, pItem, 0 );
		else if( bagType = BT_MaterialBag )
		{
			s_CUI_ID_FRAME_Amulet.ID_LISTIMG_SymbolOnIconDragOn( pBagListImg, NULL, pItem, 0 );
		}
		return true;
	}
	if( s_CUI_ID_FRAME_GemUp.IsVisable() ) // 宝石升阶界面
	{
		if( bagType == BT_MaterialBag || bagType == BT_NormalItemBag)
			s_CUI_ID_FRAME_GemUp.OnDragOn( pBagListImg, NULL, pItem, 0 );
		return true;
	}
	if ( s_CUI_ID_FRAME_ZhuJianUp.IsVisable() )//主将升阶界面
	{
		if (bagType == BT_NormalItemBag || bagType == BT_MaterialBag )
			s_CUI_ID_FRAME_ZhuJianUp.OnDragOn( pBagListImg, NULL, pItem, 0 );
		return true;
	}
	if ( s_CUI_ID_FRAME_TransferStar.IsVisable() )//转星界面
	{
		if (bagType == BT_NormalItemBag || bagType == BT_MaterialBag )
			s_CUI_ID_FRAME_TransferStar.OnDragOn( pBagListImg, NULL, pItem, 0 );
		return true;
	}
	if( s_CUI_ID_FRAME_GemMaterialUp.IsVisable() ) // 洗石剂升阶界面
	{
		if( bagType == BT_MaterialBag )
			s_CUI_ID_FRAME_GemMaterialUp.ID_LISTIMG_Material1OnIconDragOn( pBagListImg, NULL, pItem, 0 );
		return true;
	}
	if( s_CUI_ID_FRAME_IntensifyStar.IsVisable() ) // 流光升星界面
	{
		if( bagType == BT_NormalItemBag )
			s_CUI_ID_FRAME_IntensifyStar.ID_LISTIMG_ArmourOnIconDragOn( pBagListImg, NULL, pItem, 0 );
		else if( bagType = BT_MaterialBag )
		{
			switch( s_CUI_ID_FRAME_IntensifyStar.GetItemMaterialType( pItem->m_pkIconInfo->GetItemId() ) )
			{
			case ItemDefine::ematerial_starlevel:
				s_CUI_ID_FRAME_IntensifyStar.ID_LISTIMG_MaterialOnIconDragOn( pBagListImg, NULL, pItem, 0 );
				break;
// 			case CItemDetail::ematerial_addrate:
// 				s_CUI_ID_FRAME_IntensifyStar.ID_LISTIMG_EspecialOnIconDragOn( pBagListImg, NULL, pItem, 0 );
// 				break;
			default:
				break;
			}			
		}
		return true;
	}
	if( s_CUI_ID_FRAME_FiveXing.IsVisable() ) // 五行界面
	{
		ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pItem->m_pkIconInfo->GetItemId() );
		if( pItemDetail)
		{
			bool bElements = false;
			if (pItemDetail->ucItemType == ItemDefine::ITEMTYPE_CHECKUP)
			{
				ItemDefine::SItemCheckUp* pItemCheckUp = (ItemDefine::SItemCheckUp*)pItemDetail;
				if( pItemCheckUp->stCheckUpType == ItemDefine::SItemCheckUp::ECD_Elements )
					bElements = true;
			}
			if( bElements )
				s_CUI_ID_FRAME_FiveXing.ID_LISTIMG_MaterialOnIconDragOn( pBagListImg, NULL, pItem, 0 );
			else
			{
				s_CUI_ID_FRAME_FiveXing.ID_LISTIMG_ArmourOnIconDragOn( pBagListImg, NULL, pItem, 0 );
			}
		}
		return true;
	}
	if( s_CUI_ID_FRAME_MoveStar.IsVisable() ) // 移星界面
	{
		ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pItem->m_pkIconInfo->GetItemId() );
		if( bagType == BT_NormalItemBag && pItemDetail)
		{
			bool bMoveStar = false;
			if (pItemDetail->ucItemType == ItemDefine::ITEMTYPE_CHECKUP)
			{
				ItemDefine::SItemCheckUp* pItemCheckUp = (ItemDefine::SItemCheckUp*)pItemDetail;
				if( pItemCheckUp->stCheckUpType == ItemDefine::SItemCheckUp::ECD_MoveStar )
					bMoveStar = true;
			}
			if( bMoveStar )
			{
				s_CUI_ID_FRAME_MoveStar.ID_LISTIMG_MaterialOnIconDragOn( pBagListImg, NULL, pItem, 0 );
			}
			else
			{
				s_CUI_ID_FRAME_MoveStar.ID_LISTIMG_ArmourOnIconDragOn( pBagListImg, NULL, pItem, 0 );
			}
		}
		return true;
	}
	if( s_CUI_ID_FRAME_SpecialRepair.IsVisable() ) // 修理界面
	{
		ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pItem->m_pkIconInfo->GetItemId() );
		if( pItemDetail)
		{
			if (pItemDetail->ucItemType == ItemDefine::ITEMTYPE_ARMOUR ||
				pItemDetail->ucItemType == ItemDefine::ITEMTYPE_WEAPON)
			{
				s_CUI_ID_FRAME_SpecialRepair.ID_LISTIMG_ArmourOnIconDragOn( pBagListImg, NULL, pItem, 0 );
			}
			else
			{
				s_CUI_ID_FRAME_SpecialRepair.ID_LISTIMG_AimOnIconDragOn( pBagListImg, NULL, pItem, 0 );
			}
		}
		return true;
	}
	//if( s_CUI_ID_FRAME_WebAward.IsVisable() && s_CUI_ID_FRAME_WebAward.GetAddressCtrlGroup().IsVisible() ) // 实物界面
	//{
	//	ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pItem->m_pkIconInfo->GetItemId() );
	//	if( pItemDetail)
	//	{
	//		if (pItemDetail->ucItemType == ItemDefine::ITEMTYPE_REALAWARD)
	//		{
	//			s_CUI_ID_FRAME_WebAward.ID_LISTIMG_ItemOnIconDragOn( pBagListImg, NULL, pItem, 0 );
	//		}
	//	}
	//	return true;
	//}
	if( s_CUI_ID_FRAME_EquipUpgrade.IsVisable()) //
	{
		if( bagType == BT_NormalItemBag)
		{
			// 装备或武器升阶判断挪到s_CUI_ID_FRAME_EquipUpgrade.CanItemUpgrade里
			if( s_CUI_ID_FRAME_EquipUpgrade.CanItemUpgrade( pItem->m_pkIconInfo->GetItemId() ) )
			{
				s_CUI_ID_FRAME_EquipUpgrade.ID_LISTIMG_ArmourOnIconDragOn( pBagListImg, NULL, pItem, 0 );
			}
			else
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString(eText_EquipUpgrade_Cannot) );
			}
		}
		if ((bagType == BT_MaterialBag ) && s_CUI_ID_FRAME_EquipUpgrade.IsOptionalMaterial(pItem->m_pkIconInfo->GetItemId()))
		{
			s_CUI_ID_FRAME_EquipUpgrade.ID_LISTIMG_M3OnIconDragOn(pBagListImg, NULL, pItem, 0 );
		}
		return true;
	}
	if( s_CUI_ID_FRAME_GoldPlating.IsVisable() ) // 鉴定/开光界面是否打开
	{
		if( bagType == BT_NormalItemBag )
			s_CUI_ID_FRAME_GoldPlating.ID_LISTIMG_ArmourOnIconDragOn( pBagListImg, NULL, pItem, 0 );
		else if( bagType == BT_MaterialBag )
        {
            if(s_CUI_ID_FRAME_GoldPlating.IsReturnMaterial(pItem))
                s_CUI_ID_FRAME_GoldPlating.ID_LISTIMG_EspecialOnIconDragOn(pBagListImg, NULL, pItem, 0);
            else
			  s_CUI_ID_FRAME_GoldPlating.ID_LISTIMG_MaterialOnIconDragOn( pBagListImg, NULL, pItem, 0 );
        }

		return true;
	}
    if( s_CUI_ID_FRAME_Decompound.IsVisable() ) // 分解界面是否打开
    {
        if( bagType == BT_NormalItemBag )
            s_CUI_ID_FRAME_Decompound.ID_LISTIMG_ArmourOnIconDragOn( pBagListImg, NULL, pItem, 0 );
        return true;
	}
	if( s_CUI_ID_FRAME_SkillEquipUpdate.IsVisable() ) // 分解界面是否打开
	{
		ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pItem->m_pkIconInfo->GetItemId() );
		if( pItemDetail && pItemDetail->ucItemType == ItemDefine::ITEMTYPE_ARMOUR) {
			s_CUI_ID_FRAME_SkillEquipUpdate.SetEquip(pBagListImg, pItem);
		}
		else {
			s_CUI_ID_FRAME_SkillEquipUpdate.SetMaterial0(pBagListImg, pItem);
		}
		return true;
	}
	if( s_CUI_ID_FRAME_SkillEquipChange.IsVisable() ) // 分解界面是否打开
	{
		ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pItem->m_pkIconInfo->GetItemId() );
		if( pItemDetail && pItemDetail->ucItemType == ItemDefine::ITEMTYPE_ARMOUR) {
			s_CUI_ID_FRAME_SkillEquipChange.SetEquip(pBagListImg, pItem);
		}
		else if (pItemDetail->ucItemType == ItemDefine::ITEMTYPE_CHECKUP) {
			s_CUI_ID_FRAME_SkillEquipChange.SetMaterial0(pBagListImg, pItem);
		}
		else {
			s_CUI_ID_FRAME_SkillEquipChange.SetMaterial1(pBagListImg, pItem);
		}
		return true;
	}
	if( s_CUI_ID_FRAME_Storage.IsVisable() )//仓库是否打开中
	{
		s_CUI_ID_FRAME_Storage.ID_LISTIMG_MainOnIconDragOn( pBagListImg, NULL, pItem, 0 );
		return true;
	}
	if( s_CUI_ID_FRAME_Bargaining.IsVisable() )//交易界面
	{
		return s_CUI_ID_FRAME_Bargaining.OnIconDragOnFromPack(pBagListImg, pItem);
	}
	if( s_CUI_ID_FRAME_PrivateShop.IsVisable() )//摆摊界面
	{
		int nNullIndex = s_CUI_ID_FRAME_PrivateShop.CommonList_GetNullItem();
		if( nNullIndex == -1 )
			return false;

		s_CUI_ID_FRAME_PrivateShop.ID_LISTIMG_CommonListOnIconDragOn( pBagListImg, NULL, pItem , s_CUI_ID_FRAME_PrivateShop.CommonList_GetItemByIndex( nNullIndex ) );
		return true;
	}

	/*
	 * Author: 2012-10-17 15:13:48 liaojie
	 * Desc:   
	 */
	//if (s_CUI_ID_FRAME_ItemTrade.IsVisable())	//物品寄售
	//{
	//	int nNullIndex =s_CUI_ID_FRAME_ItemTrade.m_pID_LISTIMG_Item->GetNullItem();
	//	if( nNullIndex == -1 )
	//		return false;

	//	s_CUI_ID_FRAME_ItemTrade.ID_LISTIMG_ItemOnIconDragOn( pBagListImg, NULL, pItem , s_CUI_ID_FRAME_ItemTrade.m_pID_LISTIMG_Item->GetItemByIndex( nNullIndex ) );
	//	return true;
	//}

    //五行转换界面
    if(s_CUI_ID_FRAME_FiveXingChange.IsVisable())
    {
        //五行道具
        if(s_CUI_ID_FRAME_FiveXingChange.IsFiveXingItem(pItem->m_pkIconInfo->GetItemId(),ItemDefine::ITEMTYPE_ARMOUR,0,0,NULL))
        {
            s_CUI_ID_FRAME_FiveXingChange.ID_LISTIMG_ArmourOnIconDragOn(pBagListImg, NULL, pItem, 0);
        }
        else if(s_CUI_ID_FRAME_FiveXingChange.IsFiveXingItem(pItem->m_pkIconInfo->GetItemId(),ItemDefine::ITEMTYPE_CHECKUP,  \
            ItemDefine::SItemCheckUp::ECD_Elements,ItemDefine::SItemCheckUp::ECD_ElementsCheckUp,NULL))
        {//五行灵珠
            s_CUI_ID_FRAME_FiveXingChange.ID_LISTIMG_MaterialOnIconDragOn(pBagListImg, NULL, pItem, 0);
        }
        else if(s_CUI_ID_FRAME_FiveXingChange.IsFiveXingItem(pItem->m_pkIconInfo->GetItemId(),ItemDefine::ITEMTYPE_CHECKUP,  \
            ItemDefine::SItemCheckUp::ECD_Suit,ItemDefine::SItemCheckUp::ECD_ElementsSuitChange,NULL))
        {//五行转换材料
            s_CUI_ID_FRAME_FiveXingChange.ID_LISTIMG_Material2OnIconDragOn(pBagListImg, NULL, pItem, 0);
        }
        return false;
    }
    //五行提纯
    if(s_CUI_ID_FRAME_FiveXingUpdate.IsVisable())
    {
        //是否为五行道具
        if(s_CUI_ID_FRAME_FiveXingUpdate.IsFiveXingItem(pItem->m_pkIconInfo->GetItemId(),ItemDefine::ITEMTYPE_ARMOUR,0,0,NULL))
        {
            s_CUI_ID_FRAME_FiveXingUpdate.ID_LISTIMG_ArmourOnIconDragOn(pBagListImg, NULL, pItem, 0);
        }
        else if(s_CUI_ID_FRAME_FiveXingUpdate.IsFiveXingItem(pItem->m_pkIconInfo->GetItemId(),ItemDefine::ITEMTYPE_CHECKUP,  \
            ItemDefine::SItemCheckUp::ECD_Elements,ItemDefine::SItemCheckUp::ECD_ElementsCheckUp,NULL))
        {
            //是否为五行灵珠
            s_CUI_ID_FRAME_FiveXingUpdate.ID_LISTIMG_MaterialOnIconDragOn(pBagListImg, NULL, pItem, 0);
        }
        else if(s_CUI_ID_FRAME_FiveXingUpdate.IsFiveXingItem(pItem->m_pkIconInfo->GetItemId(),ItemDefine::ITEMTYPE_CHECKUP,  \
            ItemDefine::SItemCheckUp::ECD_Suit,ItemDefine::SItemCheckUp::ECD_ElementsSuitLevel,NULL))
        {
                    //是否五行提纯材料
            s_CUI_ID_FRAME_FiveXingUpdate.ID_LISTIMG_Material2OnIconDragOn(pBagListImg, NULL, pItem, 0);
        }
        else if(s_CUI_ID_FRAME_FiveXingUpdate.IsFiveXingReputationItem(pItem))
        {
                    //是否为功勋名望道具
           s_CUI_ID_FRAME_FiveXingUpdate.ID_LISTIMG_Material3OnIconDragOn(pBagListImg, NULL, pItem, 0);
        }
        return false;
    }
    if(s_CUI_ID_FRAME_FiveXingDisplace.IsVisable())
    {
        //是否为五行道具
        if(s_CUI_ID_FRAME_FiveXingDisplace.IsFiveXingItem(pItem->m_pkIconInfo->GetItemId(),ItemDefine::ITEMTYPE_ARMOUR,0,0,NULL))
        {
            int nIndex = m_pID_LISTIMG_PACK->GetItemIndex(pItem);
            SCharItem sItem;
            if(!thePlayerRole.m_bag.GetItem(nIndex,&sItem))
                return false;

            //是否有五行属性
            if(sItem.GetElements() == ItemElements_Init)
                s_CUI_ID_FRAME_FiveXingDisplace.ID_LISTIMG_AimOnIconDragOn(pBagListImg, NULL, pItem, 0);
            else
                s_CUI_ID_FRAME_FiveXingDisplace.ID_LISTIMG_ArmourOnIconDragOn(pBagListImg,NULL,pItem,0);
        }
        else if(s_CUI_ID_FRAME_FiveXingDisplace.IsFiveXingStone(pItem))
        {
            //是否为五行石
            s_CUI_ID_FRAME_FiveXingDisplace.ID_LISTIMG_MaterialOnIconDragOn(pBagListImg, NULL,pItem,0);
        }
        else if(s_CUI_ID_FRAME_FiveXingDisplace.IsFiveXingLuckStone(pItem))
        {
            //是否为五行祝福石
            s_CUI_ID_FRAME_FiveXingDisplace.ID_LISTIMG_Material2OnIconDragOn(pBagListImg, NULL,pItem,0);
        }
        return false;
    }
	//移星石升级
	if( s_CUI_ID_FRAME_MoveStarUpgrade.IsVisable() )
	{
		int index = pBagListImg->GetItemIndex( pItem );
		if( index != -1 )
		{
			s_CUI_ID_FRAME_MoveStarUpgrade.PutItemFromPack(pBagListImg, pItem, bagType, index);
		}
		return true;
	}
	// 保星材料升级
	if( s_CUI_ID_FRAME_StarMaterialUpgrade.IsVisable() )
	{
		int index = pBagListImg->GetItemIndex( pItem );
		if( index != -1 )
		{
			s_CUI_ID_FRAME_StarMaterialUpgrade.PutItemFromPack(pBagListImg, pItem, bagType, index);
		}
		return true;
	}
	// 邮件界面
    if(s_CUI_ID_FRAME_MailMain.IsVisable())
    {
        int nIndex = pBagListImg->GetItemIndex( pItem );
        if(nIndex != -1)
            s_CUI_ID_FRAME_MailMain.ID_LISTIMG_MailItemOnIconDragOn(pBagListImg,NULL,pItem,NULL);
        return true;
    }
	// 赠送礼物
	if( s_CUI_ID_FRAME_GivePresent.IsVisable() )
	{
		if( bagType == BT_NormalItemBag )
		{
			int nIndex = pBagListImg->GetItemIndex( pItem );
			if(nIndex != -1)
				s_CUI_ID_FRAME_GivePresent.PutItemFromPack(pBagListImg, pItem, bagType, nIndex);
		}
		else
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString(eText_GivePresentFailed_ItemCannotGive) );
		}
		return true;
	}

	if(s_CUI_ID_FRAME_IdentifyQuality.IsVisable())
	{
		if(bagType == BT_NormalItemBag)
		{
			int nIndex = pBagListImg->GetItemIndex( pItem );
			if(nIndex != -1)
				s_CUI_ID_FRAME_IdentifyQuality.ID_LISTIMG_ArmourOnIconDragOn(pBagListImg, NULL,pItem,NULL);
		}
		return true;
	}
	//if (s_CUI_ID_FRAME_MountStrengthen.IsVisable() && bagType == BT_MaterialBag) //坐骑强化界面
	//{
	//	s_CUI_ID_FRAME_MountStrengthen.ID_LISTIMG_MaterialOnIconDragOn(pBagListImg, 0, pItem, 0);
	//	return true;
	//}
	if( s_CUI_ID_FRAME_JieBang.IsVisable() ) // 解绑
	{
		if( bagType == BT_NormalItemBag )
			s_CUI_ID_FRAME_JieBang.ID_LISTIMG_ZJ1OnIconDragOn(pBagListImg, NULL,pItem,NULL);
		return true;
	}
	if (s_CUI_ID_FRAME_zhujiangbianshen.IsVisable())
	{
		if( bagType == BT_NormalItemBag )
			s_CUI_ID_FRAME_zhujiangbianshen.ID_LISTIMG_bianshenitemOnIconDragOn(pBagListImg, NULL,pItem,NULL);
		return true;
	}
	if (s_CUI_ID_FRAME_RandAttribute.IsVisable())
	{
		if ( bagType == BT_NormalItemBag )
			s_CUI_ID_FRAME_RandAttribute.ID_LISTIMG_ArmourOnIconDragOn(pBagListImg, NULL,pItem,NULL);
		return true;
	}
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( ((SCharItem*)pItem->m_pkIconInfo->GetData())->itembaseinfo.ustItemID);
	if(s_CUI_ID_FRAME_SuAnimal.IsVisable() && pItemCommon && pItemCommon->ucItemType == ItemDefine::ITEMTYPE_PETEQUIP)
	{
		if ( bagType == BT_NormalItemBag )
		{
			//穿上装备
			s_CUI_ID_FRAME_SuAnimal.SetPetEquip((SCharItem*)pItem->m_pkIconInfo->GetData());
		}
			//s_CUI_ID_FRAME_SuAnimal.ID_LISTIMG_PetEquipOnIconDragOn(pBagListImg, NULL,pItem,NULL);
		return true;
	}
	if (s_CUI_ID_FRAME_AddQuestEntrust.IsVisable())
	{
		s_CUI_ID_FRAME_AddQuestEntrust.ID_LISTIMG_ItemOnIconDragOn(pBagListImg, NULL,pItem,NULL);
		return true;
	}
	if (GetKeyboardInput(DIK_LSHIFT) || GetKeyboardInput(DIK_RSHIFT))
	{
		return ShowSplitInputBox(pBagListImg, pItem, pBag, bagType);
	}

	////主将变身
	//if (s_CUI_ID_FRAME_zhujiangbianshen._IsVisable())
	//{
	//	if (bagType == BT_NormalItemBag)
	//	{
	//		int nIndex = pBagListImg->GetItemIndex( pItem );
	//		if(nIndex != -1)
	//			s_CUI_ID_FRAME_zhujiangbianshen.ID_LISTIMG_bianshenitemOnIconDragOn(pBagListImg, NULL,pItem,NULL);
	//	}
	//}
	return UseItem( pBagListImg, pBag, bagType, pItem->m_pkIconInfo->Id(), nPackIndex );
}

bool CUI_ID_FRAME_PACK::UseItem(int nID, int nIndex, bool bUseSing)
{
	if( !m_pID_FRAME_PACK )
		return false;
	return UseItem(m_pID_LISTIMG_PACK, &thePlayerRole.m_bag, BT_NormalItemBag, nID, nIndex, bUseSing);
}

static bool PACK_UseMountItem(char bPressYesButton, void *pData)
{
	if (bPressYesButton && pData)
	{
		MsgUseGoodsToMount* pMsg = (MsgUseGoodsToMount*)pData;
		GettheNetworkInput().SendMsg( pMsg );
	}
	return true;
}

bool CUI_ID_FRAME_PACK::UseItem(ControlListImage* pBagListImg, CItemBag2* pBag, int bagType, int nID, int nIndex, bool bUseSing)
{
	//s_CUI_ID_FRAME_zhujiangtujian._SetVisable(true);
	/*s_CUI_ID_FRAME_zhujiangbianshen._SetVisable(true);
	return false;*/
	if( thePlayerRole.IsDie() )
		return false;

	if ( s_CUI_ID_FRAME_SelectChannel.IsVisable() )
		return false;

	if (theHeroGame.GetPlayerMgr()->GetMe()->IsYabiaoState())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_YabiaoState_UseItem ));
		return false;
	}

	if ( !pBag->IsHaveItem( nIndex ) )
		return false;

	SCharItem stItem;
	if( !pBag->GetItem( nIndex, &stItem ) )
		return false;

	if( !stItem.bCanUse )
	{
		char szBuffer[256] = {0};
		TimeEx kTime(stItem.itembaseinfo.n64UseTime);
		ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );
		if(pItemDetail)
		{
			assert("name.h"&&0);
		}

		return false;
	}

    //这里添加对ID的判断--刘传鹏
    if(stItem.itembaseinfo.ustItemID != nID)
        return false;

	ItemDefine::SItemCommon *pItemCommon = NULL;
	pItemCommon = GettheItemDetail().GetItemByID( nID );
	if( !pItemCommon )
		return false;

	//拷贝零时物品变量到全局静态变量以便查询
	sItemCommon = pItemCommon;
	// 如还在吟唱则直接返回
	if ( m_stQuestUseItem.m_bQuestUseItem == true )
		return false;

	if ( bUseSing )
	{
		if ( pItemCommon->dwUseSingTime != 0 )
		{
			if ( s_CUI_Progress.IsVisable() )
				return false;

			//开始吟唱，设置状态为True
			pItemCommon->bIsSinging = true;
			DWORD dwCurTime = HQ_TimeGetTime();
			m_stQuestUseItem.m_bQuestUseItem = pItemCommon->bIsSinging;
			m_stQuestUseItem.m_dwQuestUseItemStartTime = dwCurTime;
			m_stQuestUseItem.m_dwQuestTime = pItemCommon->dwUseSingTime;
			m_stQuestUseItem.nId = nID;
			m_stQuestUseItem.nIndex = nIndex;
			s_CUI_Progress.ShowByTime( dwCurTime,
				pItemCommon->dwUseSingTime,
				true, 1, true, true );
			return true;
		}
	}

	bool bCanUseItem = true;
	switch( pItemCommon->ucItemType )
	{

	case ItemDefine::ITEMTYPE_RESTORE:
		{
			ControlIconDrag::S_ListImg* pListImg = pBagListImg->GetItemByIndex(nIndex);
			if (pListImg && pListImg->m_eEnable == eIcon_Disable)
				return false;

			ItemDefine::SItemRestore *pItemRestore;
			pItemRestore = (ItemDefine::SItemRestore*)pItemCommon;

			// 大喇叭
			if (pItemRestore->ustItemID == 6108)
			{
				if (s_CUI_ID_FRAME_Speaker.GetItemImgIndex() != -1)
					return true;

				s_CUI_ID_FRAME_Speaker.SetItemImgIndex(nIndex);
				s_CUI_ID_FRAME_Speaker.SetListImage(pBagListImg);
			}

			if( pItemCommon->byUserTarget == ItemDefine::eTargetMount ) // 宠物
			{
				if (pItemRestore->specialFunction == 1)
				{
					/*if (!thePlayerRole.GetActivedMount())
					{
						GetShowScreenText() ->AddInfo( theXmlString.GetString( eText_Mount_NotActived ),	Color_Config.getColor( CC_Center_WarningErrorInfo ), 0, FIGHTHINTMESSAGEROW );
						return false;
					}
					else
					{*/
						
					//ItemDefine::SItemCommon* pMountCommon = GettheItemDetail().GetItemByID( thePlayerRole.GetActivedMount()->baseInfo.id );
					//if( !thePlayerRole.GetActivedMount() )
					//	return false;

                    if( !s_CUI_ID_FRAME_Pet.IsVisable() )
                    {
                        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString( eText_UseItem_MountNotSelect ) );
                        return false;
                    }

                    ItemDefine::SItemCommon* pMountCommon = GettheItemDetail().GetItemByID(s_CUI_ID_FRAME_Pet.GetCurrentMount().baseInfo.id);
                    if( !pMountCommon )
                    {
                        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString( eText_UseItem_MountNotSelect ) );
                        return false;
                    }

                    MsgUseGoodsToMount  msg;						
                    //msg.nMountIndex = thePlayerRole.GetActivedMountIndex();
					//原来这儿当坐骑生命值为0的时候会有问题，现修改下
					msg.nMountIndex = s_CUI_ID_FRAME_Pet.GetCurrentMountIndex();
                    msg.nGuid = stItem.itembaseinfo.nOnlyInt;
                    msg.ustItemIndex = nIndex;
                    if( theHeroGame.GetPlayerMgr()->GetMe() )
                        msg.stDstChar = theHeroGame.GetPlayerMgr()->GetMe()->GetID();
                    msg.ucItemBagType = bagType;
                    DWORD dwColorItem = S_IconInfoHero::GetQualityColor( pItemCommon->ustLevel );
                    DWORD dwColorMount = S_IconInfoHero::GetQualityColor( pMountCommon->ustLevel );

                    char text[256] = {0};
                    sprintf_s(text, sizeof(text)-1,theXmlString.GetString( eClient_IfUseItemForMount ),
                        dwColorMount, thePlayerRole.GetMountByIndex(msg.nMountIndex).baseInfo.szName,
                        dwColorItem, pItemCommon->GetItemName());

                    s_CUI_ID_FRAME_MessageBox.Show( text, "", CUI_ID_FRAME_MessageBox::eTypeYesNo,
                        false, PACK_UseMountItem, &msg, sizeof(MsgUseGoodsToMount) );
                    return true;
					/*}*/
				}
				else
				{
					// 如果骑宠界面没有显示，不能喂养
					if( !s_CUI_ID_FRAME_Pet.IsVisable() )
                    {
                        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString( eText_UseItem_MountNotSelect ) );
						return true;
                    }

					MsgUseGoodsToMount  msg;
					msg.nMountIndex = s_CUI_ID_FRAME_Pet.GetCurrentMountIndex();
					if( msg.nMountIndex != -1 )
					{
						msg.nGuid = stItem.itembaseinfo.nOnlyInt;
						msg.ustItemIndex = nIndex;
						if( theHeroGame.GetPlayerMgr()->GetMe() )
							msg.stDstChar = theHeroGame.GetPlayerMgr()->GetMe()->GetID();
						msg.ucItemBagType = bagType;
						GettheNetworkInput().SendMsg( &msg );
					}
                    else
                    {
                        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString( eText_UseItem_MountNotSelect ) );
                    }
				}
			}
			/*else if (pItemCommon->byUserTarget == ItemDefine::eTargetPet)
			{
				if( !s_CUI_ID_FRAME_SuAnimal.IsVisable() )
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString( eText_PetFailSelect ) );
					return true;
				}
				MsgUseGoodsToPet  msg;
				msg.nPetIndex = s_CUI_ID_FRAME_SuAnimal.GetCurrentMountIndex();
				if( msg.nPetIndex != -1 )
				{
					msg.nGuid = stItem.itembaseinfo.nOnlyInt;
					msg.ustItemIndex = nIndex;
					if( theHeroGame.GetPlayerMgr()->GetMe() )
						msg.stDstChar = theHeroGame.GetPlayerMgr()->GetMe()->GetID();
					msg.ucItemBagType = bagType;
					GettheNetworkInput().SendMsg( &msg );
				}
				else
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString( eText_PetFailSelect ) );
				}
			}*/

			bCanUseItem = coolDownRestoreItem( pItemRestore, stItem );
		}
		break;
	case ItemDefine::ITEMTYPE_WEAPON:
	case ItemDefine::ITEMTYPE_ARMOUR:
		{
			bool bFlg = false;
			m_nItemInBagIndex = nIndex;

			ItemDefine::SItemCanEquip *pCanEquip = (ItemDefine::SItemCanEquip *)pItemCommon;
			if (!CanEquip(pCanEquip))
				return false;

			if (pBag->m_pPackItem[nIndex].IsBounded())
			{
				MsgEquip msg;
				msg.ustPackIndex = nIndex;
				GettheNetworkInput().SendMsg( &msg );
				bFlg  = true;

				return true;
			}
			if (!bFlg)
			{
				if (pItemCommon->bIsCanBound && pItemCommon->bIsCanTrade)
				{
					s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eUI_SoulBound), theXmlString.GetString(eClient_AddInfo_2slk_16),
						CUI_ID_FRAME_MessageBox::eTypeYesNo, true, SendEquipMsg);
					return true;
				}
				else
				{
					MsgEquip msg;
					msg.ustPackIndex = nIndex;
					GettheNetworkInput().SendMsg( &msg );
					bFlg  = true;
					return true;
				}
			}
		}
		break;
	case ItemDefine::ITEMTYPE_REEL:
		{
			ItemDefine::SItemReel* pReel = (ItemDefine::SItemReel*)pItemCommon;
			if (pReel->byUserTarget == ItemDefine::eTargetMount)
			{
				if (!thePlayerRole.GetActivedMount())
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString( eText_Mount_NotActived ) );
					return false;
				}
				else
				{
					const SCharSkill* pSkill = thePlayerRole.GetActivedMount()->skillInfo.GetSkill(pReel->skillId);
					if (pSkill && pSkill->stSkillLevel >= pReel->skillLevel)
					{
						s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eText_MountAlreadyLearnSkill ) );
						return false;
					}

					MsgUseGoodsToMount  msg;
					msg.nMountIndex = thePlayerRole.GetActivedMountIndex();
					msg.nGuid = stItem.itembaseinfo.nOnlyInt;
					msg.ustItemIndex = nIndex;
					if( theHeroGame.GetPlayerMgr()->GetMe() )
						msg.stDstChar = theHeroGame.GetPlayerMgr()->GetMe()->GetID();
					msg.ucItemBagType = bagType;
					GettheNetworkInput().SendMsg( &msg );
					return true;
				}
			}
		}break;
	case ItemDefine::ITEMTYPE_TALISMAN:
		{
			ItemDefine::SItemTalisman* pTalisman = (ItemDefine::SItemTalisman*)pItemCommon;

			MsgEquipTalisman msg;
			msg.ustPackIndex = nIndex;
			GettheNetworkInput().SendMsg(&msg);
		}
		break;
	case ItemDefine::ITEMTYPE_OTHER:
		{
			ItemDefine::SItemOther* pOhter = (ItemDefine::SItemOther*)pItemCommon;
			if (pOhter&&pOhter->otherType == ItemDefine::OtherType_ZhujiangIdentify)
			{
				if (s_CUI_ID_FRAME_zhujiangtujian.IsVisable())
				{
					s_CUI_ID_FRAME_zhujiangtujian._SetVisable(false);
				}
				s_CUI_ID_FRAME_zhujiangtujian.SetItemId(stItem.itembaseinfo.ustItemID);
				s_CUI_ID_FRAME_zhujiangtujian._SetVisable(true);
				return true;
			}
		}
		break;
	default:
		{
			//如果物品已经加锁 return
			if(stItem.storageinfo.bIsLocked)
			{
				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eText_ItemHaveBeenLocked ) );
				return false;
			}
		}
		break;
	}
	// 物品需要目标
	if ( pItemCommon->byUserTarget == ItemDefine::eTargetMe )
	{
		if( bCanUseItem )
		{
			MsgUseGoods msg;
			msg.nGuid = stItem.itembaseinfo.nOnlyInt;
			msg.ustItemIndex = nIndex;
			if( theHeroGame.GetPlayerMgr()->GetMe() )
				msg.stDstChar = theHeroGame.GetPlayerMgr()->GetMe()->GetID();
			msg.ucItemBagType = bagType;
			GettheNetworkInput().SendMsg( &msg );
            return false;
		}
	}
	else if (pItemCommon->byUserTarget == ItemDefine::eTargetPet)
	{//有出战的宠物则可以直接使用丹药
		SPetItem * m_pet = thePlayerRole.GetActivedPet();
		short currIndex = s_CUI_ID_FRAME_SuAnimal.GetCurrentMountIndex();
		if (m_pet != NULL || currIndex!=-1)
		{
			if (pItemCommon->ucItemType == ItemDefine::ITEMTYPE_RESTORE)
			{
				ItemDefine::SItemRestore *pRestore = (ItemDefine::SItemRestore*)pItemCommon;
				if (pRestore != NULL)
				{
					//lyh增加最后一个条件，解决给副将吃经验
					if(pRestore->specialFunction == ItemDefine::EPetFunc_AddLife || pRestore->specialFunction ==ItemDefine::EPetFunc_RestoreHP ||  pRestore->specialFunction ==ItemDefine::EPetFunc_AddLoyalty || pRestore->specialFunction ==ItemDefine::EPetFunc_AddExp)
					{
						MsgUseGoodsToPet msg;
						msg.nPetIndex = thePlayerRole.GetActivedPetIndex();
						if(msg.nPetIndex != -1)
						{
							msg.nGuid = stItem.itembaseinfo.nOnlyInt;
							msg.ustItemIndex = nIndex;
							msg.stItemCount = 1;
							msg.stSrcChar = 0;
							msg.stDstChar = 0;
							msg.ucItemBagType = BT_NormalItemBag;
							GettheNetworkInput().SendMsg( &msg );
						}
					}
					else if (pRestore->specialFunction == ItemDefine::EPetFunc_ResetPoint)
					{
						MsgUseGoodsToPet msg;
						msg.nPetIndex = currIndex;
						if(msg.nPetIndex != -1)
						{
							msg.nGuid = stItem.itembaseinfo.nOnlyInt;
							msg.ustItemIndex = nIndex;
							msg.stItemCount = 1;
							msg.stSrcChar = 0;
							msg.stDstChar = 0;
							msg.ucItemBagType = BT_NormalItemBag;
							GettheNetworkInput().SendMsg( &msg );
						}
					}
				}
			}
		}else
		{
		CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Amulet_Failed, theXmlString.GetString(eText_NoPetActived));
		}
	}
	else
	{
		m_nForTargetItemIndex = nIndex;
 		s_CUI_ID_FRAME_ActionUI.SetCurFunction( CUI_ID_FRAME_BaseProperty::TYPE_USEITEM );
	}
	return true;
}

bool CUI_ID_FRAME_PACK::PackOnIconDragOn(ControlListImage* pDlgDrag, ControlListImage* pDlgSrc, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc, CItemBag2* pBag, int bagType )
{
	if( NULL == pDlgDrag || NULL == pDlgSrc || NULL == pItemDrag )
		return false;
	if ( pItemDrag->IsNull() )
		return false;

	unsigned int nDstIndex = pDlgSrc->GetItemIndex( pItemSrc );
	unsigned int nSrcIndex = 0;

	//对本身操作(移动位置)
	if (pDlgDrag == pDlgSrc)
	{//包裹内部自身移动
		nDstIndex = pDlgSrc->GetItemIndex( pItemSrc );
		nSrcIndex = pDlgSrc->GetItemIndex( pItemDrag );
		s_CUI_ID_FRAME_PACK.dropIconFromPack( nSrcIndex, nDstIndex, pItemDrag, pItemSrc, pDlgSrc, pBag, bagType);
		return true;
	}
	// 商店(买)
	else if ( s_CUI_ID_FRAME_SHOP.IsList(pDlgDrag) )
	{
		s_CUI_ID_FRAME_PACK.dropIconFromShop( pDlgSrc, pItemDrag, pItemSrc, pDlgSrc, pBag, bagType );
	}
	else if (s_CUI_ID_FRAME_BaseProperty.IsList(pDlgDrag))
	{
		s_CUI_ID_FRAME_PACK.dropIconFromEquip( nDstIndex, pItemDrag );
		return true;
	}
    // 摆摊 移除物品        modified by ZhuoMeng.Hu		[12/23/2010]
	else if( s_CUI_ID_FRAME_PrivateShop.IsEqualToCommonList( pDlgDrag ) )
	{
        s_CUI_ID_FRAME_PrivateShop.ID_LISTIMG_CommonListOnIconRButtonUp( NULL, pItemDrag );
	}
	// storage
	else if ( s_CUI_ID_FRAME_Storage.IsEqualTo_LISTIMG_Main(pDlgDrag) )
	{
		nSrcIndex = s_CUI_ID_FRAME_Storage.LISTIMG_Main_GetIndexByItem( pItemDrag )+ PAGESIZE*s_CUI_ID_FRAME_Storage.GetPageCurr();
		s_CUI_ID_FRAME_PACK.dropIconFromStorage( nSrcIndex, nDstIndex, pDlgSrc, pItemDrag, pItemSrc, pDlgSrc, pBag, bagType );
	}
	// 摆摊购买             modified by ZhuoMeng.Hu		[12/23/2010]
	else if ( s_CUI_ID_FRAME_PlayerPrivateShop.IsEqualToCommonList( pDlgDrag ) )
	{
		s_CUI_ID_FRAME_PlayerPrivateShop.ID_LISTIMG_CommonListOnIconRButtonUp( NULL, pItemDrag );
	}
	// 交易                 modified by ZhuoMeng.Hu		[12/23/2010]
	else if ( s_CUI_ID_FRAME_Bargaining.IsEqualToLISTIMG_Me( pDlgDrag ) )
	{
        s_CUI_ID_FRAME_Bargaining.ID_LISTIMG_MeOnIconRButtonUp( NULL, pItemDrag );
	}
	else  if ((
			( s_CUI_ID_FRAME_Compound.GetMaterial() && pDlgDrag == s_CUI_ID_FRAME_Compound.GetMaterial())
			|| s_CUI_ID_FRAME_Compound.IsGrid( pDlgDrag )
		   )
		&& pDlgSrc == m_pID_LISTIMG_Material )
	{
		nSrcIndex = s_CUI_ID_FRAME_Compound.GetItemIndexFromGrid( pItemDrag );
		assert( nSrcIndex != ErrorUnsignedLongID );
	}
	else if(s_CUI_ID_FRAME_SuAnimal.IsNowPetEquip(pDlgDrag))
	{
		if(pItemSrc->IsNull())
		{
			//拖装备
			s_CUI_ID_FRAME_SuAnimal.RemovePetEquip((SCharItem *)pItemDrag->m_pkIconInfo->GetData(),nDstIndex);
		}
		else
		{
			//穿装备
			s_CUI_ID_FRAME_SuAnimal.SetPetEquip((SCharItem *)pItemSrc->m_pkIconInfo->GetData(),pDlgDrag->GetItemIndex(pItemDrag));
		}
	}
	s_CUI_ID_FRAME_PACK.RefreshPackByIndex(nDstIndex, pDlgSrc, pBag, bagType);
	return true;
}

bool CUI_ID_FRAME_PACK::dropIconFromPack(int indexScr, int indexDst, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc, ControlListImage* pBagListImg, CItemBag2* pBag, int bagType)
{
	guardfunc;
	if( !s_CUI_ID_FRAME_PACK.m_pID_FRAME_PACK )
		return false;

	if ( pItemSrc->m_eEnable == eIcon_Disable )
		return false;

	if( s_CUI_ID_FRAME_Storage.GetInUIFrameLock()  ||
		s_CUI_ID_FRAME_PACK.GetInUIFrameLock() ||
		s_CUI_ID_FRAME_PACK.GetInUIFrameUnLock() ||
		s_CUI_ID_FRAME_Storage.GetInUIFrameUnLock())
	{
		s_CUI_ID_FRAME_Storage.SetInUIFrameLock(false);
		s_CUI_ID_FRAME_Storage.SetInUIFrameUnLock(false);
		s_CUI_ID_FRAME_PACK.SetInUIFrameLock(false);
		s_CUI_ID_FRAME_PACK.SetInUIFrameUnLock(false);
		theMouseManager.SetUICursor(MouseManager::Type_Arrow);
	}
	ItemDefine::SItemCommon *pSrcItemDetail = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->Id() );

	if( pSrcItemDetail == NULL )
		return FALSE;

	if (s_CUI_ID_FRAME_PACK.m_bShiftRBSplitItem)
	{
		s_CUI_ID_FRAME_PACK.m_bShiftRBSplitItem = false;

		if( pItemSrc->m_pkIconInfo->Id() != pItemDrag->m_pkIconInfo->Id() && pBag->IsHaveItem(indexDst) )
        {
            SCharItem *pSrcItem = pBag->GetCharItemFromIdx(indexScr);
            // 判断拆分个数是否等于物品总数
            if( pSrcItem && pSrcItem->itembaseinfo.ustItemCount != s_CUI_ID_FRAME_PACK.GetSplitCount() )
            {
                s_CUI_ID_FRAME_PACK.SetSplitCount(0);
                return true;
            }
        }

		MsgMoveGoodsReq msg;
		msg.ustSrcIndex = indexScr;
		msg.ustDstIndex = indexDst;
		msg.ucItemBagType = bagType;
		PackMoveItem(s_CUI_ID_FRAME_PACK.GetSplitCount(), &msg, pBagListImg, pBag, bagType, TRUE);
		s_CUI_ID_FRAME_PACK.SetSplitCount(0);
		return true;
	}
	else if (s_CUI_ID_FRAME_PACK.GetSplitCount() > 0)
	{
		if( pItemSrc->m_pkIconInfo->Id() != pItemDrag->m_pkIconInfo->Id() && pBag->IsHaveItem(indexDst) )
        {
            SCharItem *pSrcItem = pBag->GetCharItemFromIdx(indexScr);
            // 判断拆分个数是否等于物品总数
            if( pSrcItem && pSrcItem->itembaseinfo.ustItemCount != s_CUI_ID_FRAME_PACK.GetSplitCount() )
            {
                s_CUI_ID_FRAME_PACK.SetSplitCount(0);
                return true;
            }
        }

		MsgMoveGoodsReq msg;
		msg.ustSrcIndex = indexScr;
		msg.ustDstIndex = indexDst;
		msg.ucItemBagType = bagType;
		PackMoveItem(s_CUI_ID_FRAME_PACK.GetSplitCount(), &msg, pBagListImg, pBag, bagType, TRUE);
		s_CUI_ID_FRAME_PACK.SetSplitCount(0);

		return true;
	}

	if( pBag->IsHaveItem(indexDst) && 
		pBag->IsHaveItem(indexScr) )
	{
		SCharItem *pDst;
		SCharItem *pSrc;
		pDst = &pBag->m_pPackItem[indexDst];
		pSrc = &pBag->m_pPackItem[indexScr];
		if ( pDst->itembaseinfo.ustItemID != 
			pSrc->itembaseinfo.ustItemID 
			||pDst->storageinfo.bIsLocked != pSrc->storageinfo.bIsLocked)
		{
			if( CItemBag2::ExchangeItem( pDst, pSrc ,NULL,NULL,"") == true )
			{
				//发送消息给服务端
				MsgChangeItemPos msg;
				msg.ustDstIndex = indexDst;
				msg.ustSrcIndex= indexScr;
				msg.nWhichIs = 0;
				msg.ucItemBagType = bagType;
				GettheNetworkInput().SendMsg( &msg );

				s_CUI_ID_FRAME_PACK.RefreshPackByIndex(indexScr, pBagListImg, pBag, bagType);
				s_CUI_ID_FRAME_PACK.RefreshPackByIndex(indexDst, pBagListImg, pBag, bagType);

                // 移动物品在快捷栏上有快捷键，则更新快捷键的物品位置
                int iNewHotKeyBagIndex[2];
                iNewHotKeyBagIndex[0] = iNewHotKeyBagIndex[1] = -1;
                int iNewHotKeyPackIndex[2];
                iNewHotKeyPackIndex[0] = iNewHotKeyPackIndex[1] = -1;
                int iChangeCount = 0;
                for( int i = 0; i < More_iHotkey; ++i )
                {
                    SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[i];
                    if( pHotkey->ShortCut.BagType == BagTypePack )
                    {
                        if( pHotkey->ShortCut.BagIndex == indexScr )
                        {
                            iNewHotKeyBagIndex[iChangeCount] = i;
                            iNewHotKeyPackIndex[iChangeCount] = indexDst;
                            ++iChangeCount;
                            if( iChangeCount >= 2 )
                                break;
                        }
                        else if( pHotkey->ShortCut.BagIndex == indexDst )
                        {
                            iNewHotKeyBagIndex[iChangeCount] = i;
                            iNewHotKeyPackIndex[iChangeCount] = indexScr;
                            ++iChangeCount;
                            if( iChangeCount >= 2 )
                                break;
                        }
                    }
                }
                if( iChangeCount > 0 )
                {
                    for(int i=0; i<iChangeCount; ++i)
                    {
                        if( iNewHotKeyBagIndex[i] >= 0 && iNewHotKeyBagIndex[i] < More_iHotkey && iNewHotKeyPackIndex[i] >= 0 )
                        {
                            thePlayerRole.m_pHotKeyBag[iNewHotKeyBagIndex[i]].ShortCut.BagIndex = iNewHotKeyPackIndex[i];
                        }
                    }
                    // 更新快捷键给服务器
                    thePlayerRole.SendHotKeyToServer();
                }
			}
			return true;
		}
	}

	if ( pItemDrag->m_pkIconInfo->GetItemId() == InvalidLogicNumber)
		return false;

	bool bLive = false;
	if (pSrcItemDetail)
	{
		bLive = pSrcItemDetail->IsExclusive();
	}

	if ( bLive)
	{			
		if (pSrcItemDetail->ucItemType == ItemDefine::ITEMTYPE_MATERIAL )
		{
			ItemDefine::SCreateMaterial* pMaterial = NULL;
			pMaterial = (ItemDefine::SCreateMaterial*)pSrcItemDetail;
			switch(pMaterial->stMaterialType)
			{
			case ItemDefine::ematerial_metal:
			case ItemDefine::ematerial_pelage:
			case ItemDefine::ematerial_wood:
				{
					if( pItemSrc->m_pkIconInfo->Id() == ErrorUnsignedShortID )// 去掉了id相等的判断
					{
						MsgMoveGoodsReq msg;
						msg.ustSrcIndex = indexScr;
						msg.ustDstIndex = indexDst;
						msg.ucItemBagType = bagType;
						if (pItemDrag->m_pkIconInfo->Count() == 1)
						{
							if( CItemBag2::MoveItem( &pBag->m_pPackItem[indexDst],
								&pBag->m_pPackItem[indexScr], NULL,NULL,"",1) != -1 )
							{
								msg.ustCount = 1;
								if( pBag->GetCharItemFromIdx( indexScr ) )
									msg.nGuID = pBag->GetCharItemFromIdx( indexScr )->itembaseinfo.nOnlyInt;								
								GettheNetworkInput().SendMsg( &msg );

								s_CUI_ID_FRAME_PACK.RefreshPackByIndex(indexScr, pBagListImg, pBag, bagType);
								s_CUI_ID_FRAME_PACK.RefreshPackByIndex(indexDst, pBagListImg, pBag, bagType);
							}						
						}
						else
						{
							if( GetKeyboardInput(DIK_LCONTROL) )
							{
								//请输入移动的数量
								if (pBag->m_pPackItem[indexDst].storageinfo.bIsLocked)
								{
									return false;
								}

								if( pBag->GetCharItemFromIdx( msg.ustSrcIndex ) )
									msg.nGuID = pBag->GetCharItemFromIdx( msg.ustSrcIndex )->itembaseinfo.nOnlyInt;

								s_CUI_InputBox.Show( "", 
									true, true, UIPACK_MovePackItem, &msg, msg.GetLength() );
								s_CUI_InputBox.SetMaxValue(pItemDrag->m_pkIconInfo->Count());
								s_CUI_InputBox.EditInput_SetText( 1 );
							}
							else
							{
								PackMoveItem( -1, &msg, pBagListImg, pBag, bagType );
							}
						}
						return true;
					}
					else if( pItemSrc->m_pkIconInfo->Id() == pItemDrag->m_pkIconInfo->Id() )
					{
						// 既然是不可叠加物品，那么id相同的物品互相移动不用触发任何操作。
						return true;
					}
				}
				break;
			default:
				break;
			}
		}
		else
		{
			if( CItemBag2::MoveItem( &pBag->m_pPackItem[indexDst],
				&pBag->m_pPackItem[indexScr],NULL,NULL,"",1) != -1 )
			{
				MsgMoveGoodsReq msg;
				msg.ustSrcIndex = indexScr;
				msg.ustDstIndex = indexDst;
				msg.ustCount = 1;
				msg.ucItemBagType = bagType;
				if( pBag->GetCharItemFromIdx( indexScr ) )
					msg.nGuID = pBag->GetCharItemFromIdx( indexScr )->itembaseinfo.nOnlyInt;
				
				GettheNetworkInput().SendMsg( &msg );

				s_CUI_ID_FRAME_PACK.RefreshPackByIndex(indexScr, pBagListImg, pBag, bagType);
				s_CUI_ID_FRAME_PACK.RefreshPackByIndex(indexDst, pBagListImg, pBag, bagType);

                // 移动物品在快捷栏上有快捷键，则更新快捷键的物品位置
                bool bHotKeyChanged = false;
                for( int i = 0; i < More_iHotkey; ++i )
                {
                    SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[i];
                    if( pHotkey->ShortCut.BagType == BagTypePack )
                    {
                        if( pHotkey->ShortCut.BagIndex == indexScr )
                        {
                            pHotkey->ShortCut.BagIndex = indexDst;
                            bHotKeyChanged = true;
                        }
                    }
                }
                if( bHotKeyChanged )
                {
                    // 更新快捷键给服务器
                    thePlayerRole.SendHotKeyToServer();
                }

				return true;
			}
		}
	}
	else
	{
		if ( pItemSrc->m_pkIconInfo->Id() == InvalidLogicNumber ||
			pItemSrc->m_pkIconInfo->Id() == pItemDrag->m_pkIconInfo->Id() )
		{
			MsgMoveGoodsReq msg;
			msg.ustSrcIndex = indexScr;
			msg.ustDstIndex = indexDst;
			msg.ucItemBagType = bagType;
			if ( pItemDrag->m_pkIconInfo->Count() == 1 )
			{
                // 检查绑定不绑定合并
                if( CUI_ID_FRAME_PACK::IsSameItemDifInBound( pBag->m_pPackItem[indexScr].itembaseinfo.nOnlyInt, indexScr,
                    pBag->m_pPackItem[indexDst].itembaseinfo.nOnlyInt, indexDst ) )
                {
                    MoveSameItemDifInBoundData data;
                    data.indexScr = indexScr;
                    data.indexDst = indexDst;
                    data.pBagListImg = pBagListImg;
                    data.pBag = pBag;
                    data.bagType = bagType;
                    data.msg = msg;
                    data.nCount = 1;
                    CUI_ID_FRAME_PACK::ShowConfirmBoundMessageBox( data );
                }
                else
                {
                    if( CItemBag2::MoveItem( &pBag->m_pPackItem[indexDst],
                        &pBag->m_pPackItem[indexScr],NULL,NULL,"", 1)!= -1 )
                    {
                        msg.ustCount = 1;
                        if( pBag->GetCharItemFromIdx( indexScr ) )
                            msg.nGuID = pBag->GetCharItemFromIdx( indexScr )->itembaseinfo.nOnlyInt;
                        GettheNetworkInput().SendMsg( &msg);

                        s_CUI_ID_FRAME_PACK.RefreshPackByIndex(indexScr, pBagListImg, pBag, bagType);
                        s_CUI_ID_FRAME_PACK.RefreshPackByIndex(indexDst, pBagListImg, pBag, bagType);
                    }
				}
			}
			else
			{
				if( GetKeyboardInput(DIK_LCONTROL) )
				{
					//请输入移动的数量
					if (pBag->m_pPackItem[indexDst].storageinfo.bIsLocked)
					{
						return false;
					}
					if( pBag->GetCharItemFromIdx( msg.ustSrcIndex ) )
						msg.nGuID = pBag->GetCharItemFromIdx( msg.ustSrcIndex )->itembaseinfo.nOnlyInt;

					s_CUI_InputBox.Show( "", true, true, UIPACK_MovePackItem, &msg, msg.GetLength() );
					s_CUI_InputBox.SetMaxValue(pItemDrag->m_pkIconInfo->Count());
					s_CUI_InputBox.EditInput_SetText( 1 );
				}
				else
				{
					PackMoveItem( -1, &msg, pBagListImg, pBag, bagType );
				}
			}
			return true;
		}
	}
	return false;
	unguard;
}

bool CUI_ID_FRAME_PACK::dropIconFromShop( ControlListImage* pObjListSrc, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc, ControlListImage* pBagListImg, CItemBag2* pBag, int bagType)
{
	guardfunc;
	if( !s_CUI_ID_FRAME_PACK.m_pID_FRAME_PACK )
		return false;

	int nPackEmptyIndex = -1;
	if(pItemSrc == NULL)
	{
		bool bBugInPackEx =  false;
		nPackEmptyIndex = pBagListImg->GetNullItem();
		if(nPackEmptyIndex == -1)
		{
			//说明没有 空位了
			switch (bagType)
			{
			case BT_MaterialBag:
				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_MaterialPackFull) );
				break;
			case BT_TaskBag:
				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_TaskPackFull) );
				break;
			default:
				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_NormalPackFull) );
				break;
			}
			return false;
		}
		if( bBugInPackEx )
		{
			nPackEmptyIndex += ITEM_PACK_OLD;
		}
		//
		if ( nPackEmptyIndex >= pBag->GetNowBagSize() )
		{
			//说明没有 空位了
			switch (bagType)
			{
			case BT_MaterialBag:
				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_MaterialPackFull) );
				break;
			case BT_TaskBag:
				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_TaskPackFull) );
				break;
			default:
				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_NormalPackFull) );
				break;
			}
			return false;
		}
	}
	else
	{
		if ( !pItemSrc->IsNull() )
			return false;

		if( pObjListSrc == pBagListImg )
		{
			nPackEmptyIndex = pBagListImg->GetItemIndex( pItemSrc );
		}
	}

	ItemDefine::SItemCommon *pItem = GettheItemDetail().GetItemByID(pItemDrag->m_pkIconInfo->Id());
	if ( !pItem )
		return false;

	switch (pItem->ucItemType)
	{
	case ItemDefine::ITEMTYPE_MATERIAL:
	case ItemDefine::ITEMTYPE_GEM:
		if (pBagListImg != s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Material)
			return false;
		break;
	case ItemDefine::ITEMTYPE_TASK:
		if (pBagListImg != s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Task)
			return false;
		break;
	default:
		if (pBagListImg != s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_PACK)
			return false;
		break;
	}

    // 安全保护
    if( CWealthProtect::Instance().IsInProtectTime() || CPreventWallow::Instance().IsFCMNotHealthy() )
        return false;

	// 购回
	if (s_CUI_ID_FRAME_SHOP.CHECKBOX_Gouhui_IsChecked())
	{
		return s_CUI_ID_FRAME_SHOP.BuyBack(pItemDrag);
	}

	// 没有足够的钱 (由于2哥的更改，此处只能拿绑定来做逻辑)
	bool bBound = ( ( S_IconInfoHero* )( pItemDrag->m_pkIconInfo ) )->m_stItem.IsBounded();
	if( bBound )
	{
		if ( pItemDrag->m_pkIconInfo->Cost() > thePlayerRole.GetData( CPlayerRole::TYPE_MONEY ) + thePlayerRole.GetData( CPlayerRole::TYPE_JiaoZi ) )
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eExchange_NoJiaoziNoMoney ) );
			return false;
		}
	}
	else
	{
		if ( pItemDrag->m_pkIconInfo->Cost() > thePlayerRole.GetData( CPlayerRole::TYPE_MONEY ) + thePlayerRole.GetData( CPlayerRole::TYPE_JiaoZi ) )
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eExchange_NotMoney ) );
			return false;
		}
	}

// 	MsgBuyOrSellGoods msg;
// 	msg.bIsBuy = true;
// 	msg.ustItemId = pItemDrag->m_pkIconInfo->Id();
// 	msg.ustPackIndex = nPackEmptyIndex;
// 	msg.ucItemBagType = bagType;

	TempTransferStruct tempData;
	tempData.m_nId = pItemDrag->m_pkIconInfo->Id();
	tempData.m_nType = bagType;
    tempData.m_bNeedJiaozi = bBound;

	if( pItem->IsExclusive() )
	{
		CUI_ID_FRAME_SHOP::UIShop_BuyGoods(1, &tempData);
	}
	else
	{
		//请输入要购买的物品数量
		CUI_ID_FRAME_BatchShop::Show( "",
			true, true, CUI_ID_FRAME_SHOP::UIShop_BuyGoodsByCount,
			&tempData, sizeof(TempTransferStruct) );
		s_CUI_ID_FRAME_BatchShop.SetMaxValue(CItemBag2::GetItemStackCount(pItemDrag->m_pkIconInfo->Id()));
		s_CUI_ID_FRAME_BatchShop.SetEditNumber( 1 );
	}
	return false;
	unguard;
}

bool CUI_ID_FRAME_PACK::dropIconFromStorage(int inexSrc, int indexDst, ControlIconDrag* pDlgSrc, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc, ControlListImage* pBagListImg, CItemBag2* pBag, int bagType)
{
	guardfunc;

	if( !s_CUI_ID_FRAME_PACK.m_pID_FRAME_PACK )
		return false;
	if ( !pItemDrag || pItemDrag->IsNull() )
		return false;
    // 安全保护
    if( CWealthProtect::Instance().IsInProtectTime() )
        return false;

	//二级密码保护
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if (thePlayerRole.GetIsSecondPassword() && !s_CUI_ID_FRAME_SuperPassword.GetChecked() && pMe)
	{
		s_CUI_ID_FRAME_SuperPassword.SetVisiblePosition(*(Vector*)&pMe->GetPos());
		s_CUI_ID_FRAME_SuperPassword.SetVisable(true);

		if( s_CUI_ID_FRAME_SuperPassword.GetEditAddName() )
			theUiManager.SetFocus(s_CUI_ID_FRAME_SuperPassword.GetEditAddName());

		return false;
	}
	if (s_CUI_ID_FRAME_PACK.GetCancelOperator())
	{
		s_CUI_ID_FRAME_PACK.SetCancelOperator(false);
		return true;
	}

	S_DstSrcIndex stDstSrcIndex;
	stDstSrcIndex.nDstIndex = indexDst;
	stDstSrcIndex.nSrcIndex = inexSrc;
	stDstSrcIndex.pBagListImg = pBagListImg;
	stDstSrcIndex.pBag = pBag;
	stDstSrcIndex.bagType = bagType;

	//索引超出仓库和背包的最大限制
	if (indexDst>=pBag->GetNowBagSize() || indexDst <= -1
		|| inexSrc >= thePlayerRole.GetData(CPlayerRole::TYPE_Storage)/*PAGESIZE*/
		|| inexSrc <= -1)
		return false;
	ItemDefine::SItemCommon *pSrcItem = (ItemDefine::SItemCommon *)GettheItemDetail().GetItemByID( thePlayerRole.m_stStorage.stStorageItems[inexSrc].itembaseinfo.ustItemID );
	if (!pSrcItem)
		return false;

	switch (pSrcItem->ucItemType)
	{
	case ItemDefine::ITEMTYPE_MATERIAL:
	case ItemDefine::ITEMTYPE_GEM:
		if (pBagListImg != s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Material)
			return false;
		break;
	case ItemDefine::ITEMTYPE_TASK:
		if (pBagListImg != s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_Task)
			return false;
		break;
	default:
		if (pBagListImg != s_CUI_ID_FRAME_PACK.m_pID_LISTIMG_PACK)
			return false;
		break;
	}

	//物品独占并且背包里有物品
	if(pBag->IsHaveItem(indexDst))
	{
		return false;
	}
	//背包没有 空位了
	int nPackEmptyIndex = -1;

	if(pItemSrc == NULL)
	{
		nPackEmptyIndex = pDlgSrc->GetNullItem();
		if(nPackEmptyIndex == -1)
		{
			switch (bagType)
			{
			case BT_MaterialBag:
				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_MaterialPackFull) );
				break;
			case BT_TaskBag:
				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_TaskPackFull) );
				break;
			default:
				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_NormalPackFull) );
				break;
			}
			return false;
		}
	}
	s_CUI_ID_FRAME_PACK.m_dwMoveCount  = pItemDrag->m_pkIconInfo->Count();
//不询问，直接放
	//zhuxincong，这里也是需要修改的，如果有2级密码就要先输入2级密码
	char strCount[256];
	itoa(s_CUI_ID_FRAME_PACK.m_dwMoveCount,strCount,10);
	StorageItemToPack( strCount, &stDstSrcIndex );

	return true;
	unguard;
}

void CUI_ID_FRAME_PACK::RefreshPackByIndex(int index, ControlListImage* pBagListImg, CItemBag2* pBag, int bagType)
{
	if( !m_pID_FRAME_PACK )
		return;

	s_CUI_ID_FRAME_MAIN.RefeashHotKey();
	s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
	if ( !pBag->IsHaveItem(index) )
	{
		pBagListImg->RemoveItemByIndex( index );
		return;
	}
	eTipFlag eFlag = s_CUI_ID_FRAME_SHOP.IsVisable() ? eTipFlag_ShowMoney : eTipFlag_Normal;

	SCharItem stItem;	
	if( !pBag->GetItem( index, &stItem ) )
        return;

	ControlIconDrag::S_ListImg stListItem;			
	ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );

	if( pItemDetail 
		&& 
		( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_WEAPON 
		|| pItemDetail->ucItemType == ItemDefine::ITEMTYPE_ARMOUR
		)
		)
	{
		ItemDefine::SItemCanEquip *pEquip = (ItemDefine::SItemCanEquip *)pItemDetail;
		{	
			BOOL bContinue = FALSE;
			int nCanEquipPart = 0;
			for( int i=0; i< EEquipPartType_MaxEquitPart; i++ )
			{
				if( bContinue )
				{
					continue;
				}
				if ( pEquip->arrayCanEquip[i] == 1 )
				{
					nCanEquipPart = i;
					bContinue = TRUE;
				}
			}
            bool bEnable = CPackItemEnableManager::Instance()->IsPackItemEnable( pBag, index );
			stListItem.SetData( &stItem, ( bEnable ? eIcon_Enable:eIcon_Disable), eFlag ); 			
			const SCharItem* pCompareEquipItem = thePlayerRole.GetEquipItem( nCanEquipPart );
			if( pCompareEquipItem )
			{
				if( theIconInfoMouseTip.GetCompareIconInfo() )
				{
					theIconInfoMouseTip.GetCompareIconInfo()->SetData( (void*)pCompareEquipItem, eIcon_Enable, 0, true );
				}				
			}			
		}
	}
	else
	{
        bool bEnable = CPackItemEnableManager::Instance()->IsPackItemEnable( pBag, index );
		stListItem.SetData( &stItem, bEnable ? eIcon_Enable : eIcon_Disable, eFlag );
	}
 
	CUI_ID_FRAME_SHOP::ItemCost *pItemCost = s_CUI_ID_FRAME_SHOP.GetItemCost(
		stItem.itembaseinfo.ustItemID);
	if ( pItemCost )
		stListItem.m_pkIconInfo->SetCost( pItemCost->nCost );

	RestoreColdDown* pRestoreCoolDown = NULL;
	pRestoreCoolDown = thePlayerRole.GetRestoreCoolDown();
	DWORD dwStartTiem,dwPeriod;
	if( pRestoreCoolDown->GetTime( stItem.itembaseinfo.ustItemID,
		&dwStartTiem, &dwPeriod ) == true )
	{
		stListItem.SetTime( dwStartTiem,dwPeriod );
	}

    if( m_newEquipMap.count( index ) > 0 && m_newEquipMap.find( index )->second && pBagListImg == m_pID_LISTIMG_PACK )
        stListItem.SetSparkEnable( true );
    else
        stListItem.SetSparkEnable( false );

	pBagListImg->SetItem( &stListItem, index );
	thePlayerRole.RefreshQuestDone();
	s_CUI_ID_FRAME_Task.RefreshCurrSelect();
}

bool CUI_ID_FRAME_PACK::dropIconFromEquip(int indexScr, ControlIconDrag::S_ListImg* pItemDrag)
{
	guardfunc;
	if( !s_CUI_ID_FRAME_PACK.m_pID_FRAME_PACK )
		return false;

	if (thePlayerRole.GetMyHP() <= 0|| (theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->IsDead()) )
	{
		return false;
	}

	//战斗时能换装备
	/*if (thePlayerRole.IsFighting())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString(eText_SitFailed_CurrStatus) );
		return false;
	}*/

	int nEquipWhere = s_CUI_ID_FRAME_BaseProperty.GetWhere( pItemDrag );
	if ( nEquipWhere == -1 )
	{
		return false;
	}

	ItemDefine::SItemCommon *pItem = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if( !pItem )
		return false;
	ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*)pItem;
	int nSuitID = (int)pItemCanEquip->bFashion;
	/*if( pItemCanEquip->bFashion )
		nEquipWhere = s_CUI_ID_FRAME_BaseProperty.GetSuitIndex( nEquipWhere );*/

	if ( nEquipWhere == -1 )
	{
		return false;
	}
	if( nEquipWhere == EEquipPartType_Weapon )
	{
		SCharItem* pVisual = NULL;
		pVisual = &thePlayerRole.m_pVisual->GetVisualArray()[EEquipPartType_Weapon];
		if( pVisual )
		{
			ItemDefine::SItemCommon *pItem = GettheItemDetail().GetItemByID( pVisual->itembaseinfo.ustItemID );
			/*if( pItem )
			{
				if( pItem->ucItemType == ItemDefine::ITEMTYPE_WEAPON )
				{
					nEquipWhere = EPT_LHandItem;
				}
			}*/
		}			
	}
	SCharItem* pVisual = NULL;
	pVisual = thePlayerRole.m_pVisual->GetVisual( nEquipWhere );
	unsigned short stCount = 0;	
	int nRes = thePlayerRole.m_bag.PushItem( *pVisual, stCount, NULL,NULL,"",indexScr );
	if (nRes != ierr_Success)
	{
		return false;
	}

	MsgUnEquip msg;
	/*msg.nIndex = nSuitID;*/
	msg.stPackIndex = indexScr;
	msg.ustWhere = nEquipWhere;
	GettheNetworkInput().SendMsg( &msg );

	s_CUI_ID_FRAME_PACK.RefreshPackByIndex(indexScr);

	if ( pVisual->itembaseinfo.ustItemID == InvalidLogicNumber
		/*&&pVisual->guid == GUID_NULL*/)
	{
		assert(false);
		return false;
	}

	pVisual->itembaseinfo.ustItemID = InvalidLogicNumber;

	return true;
	unguard;
}

void CUI_ID_FRAME_PACK::RefreshNormalPack()
{
	if( !m_pID_FRAME_PACK )
		return;
	Refresh(m_pID_LISTIMG_PACK, &thePlayerRole.m_bag, BT_NormalItemBag);
}

void CUI_ID_FRAME_PACK::RefreshMaterialPack()
{
	if( !m_pID_FRAME_PACK )
		return;
	Refresh(m_pID_LISTIMG_Material, &thePlayerRole.m_bagMaterial, BT_MaterialBag);
}

void CUI_ID_FRAME_PACK::RefreshTaskPack()
{
	if( !m_pID_FRAME_PACK )
		return;
	Refresh(m_pID_LISTIMG_Task, &thePlayerRole.m_bagTask, BT_TaskBag);
}

void CUI_ID_FRAME_PACK::RefreshAllPack()
{
	if( !m_pID_FRAME_PACK )
		return;
	RefreshNormalPack();
	RefreshMaterialPack();
	RefreshTaskPack();
}


void CUI_ID_FRAME_PACK::RefreshNormalPackByIndex(int index)
{
	if( !m_pID_FRAME_PACK )
		return;
	RefreshPackByIndex(index, m_pID_LISTIMG_PACK, &thePlayerRole.m_bag, BT_NormalItemBag);
}
void CUI_ID_FRAME_PACK::RefreshMaterialPackByIndex(int index)
{
	if( !m_pID_FRAME_PACK )
		return;
	RefreshPackByIndex(index, m_pID_LISTIMG_Material, &thePlayerRole.m_bagMaterial, BT_MaterialBag);
}
void CUI_ID_FRAME_PACK::RefreshTaskPackByIndex(int index)
{
	if( !m_pID_FRAME_PACK )
		return;
	RefreshPackByIndex(index, m_pID_LISTIMG_Task, &thePlayerRole.m_bagTask, BT_TaskBag);
}

void CUI_ID_FRAME_PACK::UpdateHotkeyAfterClearupBag()
{
	if( !m_pID_FRAME_PACK )
		return;

    if( m_vctHotkeyPackBackup.size() > 0 )
    {
        bool bChange = false;
        for( int i=0; i<m_vctHotkeyPackBackup.size(); ++i )
        {
            for( int j=0; j<thePlayerRole.m_bag.GetNowBagSize(); ++j )
            {
                if( m_vctHotkeyPackBackup[i].iHotKeyIndex >= 0 
                    && m_vctHotkeyPackBackup[i].iHotKeyIndex < More_iHotkey 
                    && thePlayerRole.m_bag.m_pPackItem[j].itembaseinfo.ustItemID == m_vctHotkeyPackBackup[i].ustItemID )
                {
                    thePlayerRole.m_pHotKeyBag[m_vctHotkeyPackBackup[i].iHotKeyIndex].ShortCut.BagIndex = j;
                    bChange = true;
                    break;
                }
            }
        }
        // 更新快捷键给服务器
        if( bChange )
            thePlayerRole.SendHotKeyToServer();

        m_vctHotkeyPackBackup.clear();
    }
}

void CUI_ID_FRAME_PACK::ChangeMoney(int nCurrMoney)
{
	if( !m_pID_FRAME_PACK )
		return;
	// 刷新钱
	int nMoney = abs((int)thePlayerRole.GetData( CPlayerRole::TYPE_MONEY ) - nCurrMoney);

	int gold = 0,silver = 0,copper = 0;
    thePlayerRole.GetGSCFromMoney(nMoney,gold,silver,copper);

	std::stringstream sstr;
	if (thePlayerRole.GetData( CPlayerRole::TYPE_MONEY ) < nCurrMoney)
		sstr << theXmlString.GetString(eText_YouGet_Money);
	else
		sstr << theXmlString.GetString(eText_YouLost);
	if (gold > 0)
		sstr << gold << theXmlString.GetString(eText_Money_Gold);
	if (silver > 0)
		sstr << silver << theXmlString.GetString(eText_Money_Silver);
	if (copper > 0)
		sstr << copper << theXmlString.GetString(eText_Money_Copper);
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, sstr.str().c_str() );

	thePlayerRole.Update( CPlayerRole::TYPE_MONEY, nCurrMoney );
	s_CUI_ID_FRAME_PACK.RefreshMoney();
}

int CUI_ID_FRAME_PACK::GetPackImageIndex(ControlIconDrag::S_ListImg *pImg)
{
    if(!pImg || !m_pID_FRAME_PACK)
        return -1;

    return m_pID_LISTIMG_PACK->GetItemIndex(pImg);
}

int CUI_ID_FRAME_PACK::GetMaterialImageIndex(ControlIconDrag::S_ListImg *pImg)
{
    if(!pImg || !m_pID_FRAME_PACK)
        return -1;

    return m_pID_LISTIMG_Material->GetItemIndex(pImg);
}

bool CUI_ID_FRAME_PACK::SparkMouseMoveOn( ControlIconDrag::S_ListImg* pImg, ControlIconDrag* pThis )
{
    if( !s_CUI_ID_FRAME_PACK.IsUILoad() || !pThis )
        return false;

    ControlListImage* pListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType( BT_NormalItemBag );
    if( pThis == pListImg )
    {
        int n = pListImg->GetItemIndex( pImg );
        s_CUI_ID_FRAME_PACK.EnableSlotSpark( n, false );
        pImg->SetSparkEnable( false );
    }
    return true;
}

void CUI_ID_FRAME_PACK::EnableSlotSpark( int nId, bool bEnable )
{
    if( nId >= 0 )
        m_newEquipMap[nId] = bEnable;
}

void CUI_ID_FRAME_PACK::ClearSlotSpark()
{
    if( IsUILoad() )
    {
        std::map<int, bool>::iterator it = m_newEquipMap.begin();
        for( ; it != m_newEquipMap.end(); ++it )
        {
            ControlIconDrag::S_ListImg* pItem = m_pID_LISTIMG_PACK->GetItemByIndex( it->first );
            if( pItem )
            {
                pItem->SetSparkEnable( false );
            }
        }
    }
    m_newEquipMap.clear();
}

bool CUI_ID_FRAME_PACK::LoadGrassItemID()
{
	MeXmlDocument doc;
	char szWord[256] = {0};
	MeSprintf_s(szWord,sizeof(szWord),"%s\\Data\\ClientConfig\\GameSetting.config",GetRootPath());
	if( !doc.LoadFile(szWord) )
		return false;
	int nValue = 0;
	m_GrassIDSet.clear();

	MeXmlElement* pRoot = doc.FirstChildElement("Project")->FirstChildElement("GrassSet");
	if(pRoot)
	{
		MeXmlElement* pSubElem = pRoot->FirstChildElement("Grass");
		for (;pSubElem != NULL;pSubElem = pSubElem->NextSiblingElement())
		{

			pSubElem->QueryIntAttribute("Id",&nValue);

			m_GrassIDSet.push_back(nValue);
		}
	}
	return true;

}

bool CUI_ID_FRAME_PACK::IsGrassID(int nItemID)
{
	std::vector<int>::iterator it = std::find(m_GrassIDSet.begin(),m_GrassIDSet.end(),nItemID);
	if(it != m_GrassIDSet.end())
		return true;

	return false;
}

void CUI_ID_FRAME_PACK::DisplayTaskItemEff( int nBagType, int nItemId )
{
    SCharItem charItem;
    ControlListImage* pListImg = NULL;
    switch( nBagType )
    {
    case BT_NormalItemBag:
        {
            if( !thePlayerRole.m_bag.GetItemByItemID( nItemId, &charItem ) )
                return;

            m_nTaskEffIndex = thePlayerRole.m_bag.GetItemIndex( &charItem );
            if( m_nTaskEffIndex < 0 )
                return;
        }
        break;
    case BT_MaterialBag:
        {
            if( !thePlayerRole.m_bagMaterial.GetItemByItemID( nItemId, &charItem ) )
                return;

            m_nTaskEffIndex = thePlayerRole.m_bagMaterial.GetItemIndex( &charItem );
            if( m_nTaskEffIndex < 0 )
                return;
        }
        break;
    case BT_TaskBag:
        {
            if( !thePlayerRole.m_bagTask.GetItemByItemID( nItemId, &charItem ) )
                return;

            m_nTaskEffIndex = thePlayerRole.m_bagTask.GetItemIndex( &charItem );
            if( m_nTaskEffIndex < 0 )
                return;
        }
        break;
    default:
        {
            return;
        }
        break;
    }
    m_nTaskEffGuid = charItem.GetItemGuid();
    m_nTaskEffBagType = nBagType;
    m_bTaskEffNeedCheck = true;

    if( !IsUILoad() )
        return;

    if( !m_pID_PROGRESS_TaskItemEff->IsAnimationCreated() )
        return;

    pListImg = GetListImageByBagType( nBagType );
    if( !pListImg )
        return;

    RECT rc, rcFrame;
    pListImg->GetItemRect( m_nTaskEffIndex, rc );
    int nCenterX = ( rc.left + rc.right ) / 2;
    int nCenterY = ( rc.top + rc.bottom ) / 2;
    m_pID_PROGRESS_TaskItemEff->GetFatherRect( &rcFrame );
    nCenterX -= rcFrame.left;
    nCenterY -= rcFrame.top;
    m_pID_PROGRESS_TaskItemEff->GetRealRect( &rc );
    RECT rcEff;
    rcEff.left = nCenterX - ( rc.right - rc.left ) / 2;
    rcEff.right = nCenterX + ( rc.right - rc.left ) / 2;
    rcEff.top = nCenterY - ( rc.bottom - rc.top ) / 2;
    rcEff.bottom = nCenterY + ( rc.bottom - rc.top ) / 2;
    m_pID_PROGRESS_TaskItemEff->SetRealRect( &rcEff );
    m_pID_PROGRESS_TaskItemEff->StartAnimation();
}

void CUI_ID_FRAME_PACK::CheckTaskItemEff()
{
    if( !m_bTaskEffNeedCheck )
        return;

    if( !IsUILoad() )
    {
        m_bTaskEffNeedCheck = false;
        return;
    }

    if( !IsVisable() )
    {
        StopTaskEff();
        m_bTaskEffNeedCheck = false;
        return;
    }

    switch( m_nTaskEffBagType )
    {
    case BT_NormalItemBag:
        {
            if( !m_pID_LISTIMG_PACK->IsVisable() || thePlayerRole.m_bag.GetItemIndexByGUID( m_nTaskEffGuid ) != m_nTaskEffIndex )
            {
                StopTaskEff();
                m_bTaskEffNeedCheck = false;
                return;
            }
        }
        break;
    case BT_MaterialBag:
        {
            if( !m_pID_LISTIMG_Material->IsVisable() || thePlayerRole.m_bagMaterial.GetItemIndexByGUID( m_nTaskEffGuid ) != m_nTaskEffIndex )
            {
                StopTaskEff();
                m_bTaskEffNeedCheck = false;
                return;
            }
        }
        break;
    case BT_TaskBag:
        {
            if( !m_pID_LISTIMG_Task->IsVisable() || thePlayerRole.m_bagTask.GetItemIndexByGUID( m_nTaskEffGuid ) != m_nTaskEffIndex )
            {
                StopTaskEff();
                m_bTaskEffNeedCheck = false;
                return;
            }
        }
        break;
    default:
        break;
    }
}

void CUI_ID_FRAME_PACK::StopTaskEff()
{
    if( !IsUILoad() )
        return;

    if( !m_pID_PROGRESS_TaskItemEff->IsAnimationCreated() )
        return;

    m_pID_PROGRESS_TaskItemEff->StopAnimation();
}

int CUI_ID_FRAME_PACK::GetEquipPos()
{
    return m_nEquipPos;
}

void CUI_ID_FRAME_PACK::SetEquipPos( int nPos )
{
    m_nEquipPos = nPos;
}

bool CUI_ID_FRAME_PACK::IsList(const ControlObject* pObject)
{
	if ( m_pID_LISTIMG_PACK == pObject ||
		m_pID_LISTIMG_Material == pObject ||
		m_pID_LISTIMG_Task == pObject
		)
	{
		return true;
	}
	return false;
}

bool CUI_ID_FRAME_PACK::IsSameItemDifInBound( __int64 nGuid1, int nIndex1, __int64 nGuid2, int nIndex2 )
{
    // 没找到对应物品
    SCharItem charItem1, charItem2;
    if( !thePlayerRole.GetStorageItemByGUID( nGuid1, &charItem1 ) && !thePlayerRole.GetBagItemByGUID( nGuid1, &charItem1 ) )
        return false;

	CItemBag2* bag = 0;
	if (thePlayerRole.GetBagByItemGUID(nGuid1, bag))
	{
		if (!bag->IsHaveItem(nIndex1))
			return false;
	}

    if( !thePlayerRole.GetStorageItemByGUID( nGuid2, &charItem2 ) && !thePlayerRole.GetBagItemByGUID( nGuid2, &charItem2 ) )
        return false;

	if (thePlayerRole.GetBagByItemGUID(nGuid2, bag))
	{
		if (!bag->IsHaveItem(nIndex2))
			return false;
	}

    // 不是同一物品
    if( charItem1.itembaseinfo.ustItemID != charItem2.itembaseinfo.ustItemID )
        return false;

    // 是可堆叠
    ItemDefine::SItemCommon* pItem = GetItemDetailConfig().GetItemByID( charItem1.itembaseinfo.ustItemID );
    if( !pItem )
        return false;

    if( pItem->IsExclusive()||!pItem->bIsCanTrade)
        return false;

    // 绑定类型不同
    if( charItem1.IsBounded() == charItem2.IsBounded() )
        return false;

    return true;
}

void CUI_ID_FRAME_PACK::ShowConfirmBoundMessageBox( const MoveSameItemDifInBoundData& data )
{
    s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eText_ItemBind_ConfirmByDifInBound ), "", CUI_ID_FRAME_MessageBox::eTypeYesNo,
        false, CUI_ID_FRAME_PACK::ConfirmBoundCallback, ( void* )( &data ), sizeof( MoveSameItemDifInBoundData ) );
}

bool CUI_ID_FRAME_PACK::ConfirmBoundCallback( char bPressYesButton, void *pData )
{
    if( bPressYesButton )
    {
        if( !pData )
            return true;
		//优先判断2个物品是否在背包为不可以使用状态 就是灰色的图标
        MoveSameItemDifInBoundData* pNewData = ( MoveSameItemDifInBoundData* )pData;
		if(!pNewData->pBag->GetBagEnablesByIndex(pNewData->indexScr) || !pNewData->pBag->GetBagEnablesByIndex(pNewData->indexDst))
			return true;
        if( CItemBag2::MoveItem( &pNewData->pBag->m_pPackItem[pNewData->indexDst],
            &pNewData->pBag->m_pPackItem[pNewData->indexScr], NULL, NULL, "", pNewData->nCount ) != -1 )
        {
            pNewData->msg.ustCount = pNewData->nCount;
            if( pNewData->pBag->GetCharItemFromIdx( pNewData->indexScr ) )
                pNewData->msg.nGuID = pNewData->pBag->GetCharItemFromIdx( pNewData->indexScr )->itembaseinfo.nOnlyInt;
            GettheNetworkInput().SendMsg( &pNewData->msg );

            if( pNewData->bIsSplit )
            {
                pNewData->pBag->m_pPackItem[pNewData->msg.ustSrcIndex].storageinfo.bIsLocked = true;
                pNewData->pBag->m_pPackItem[pNewData->msg.ustDstIndex].storageinfo.bIsLocked = true;
                theIconDragManager.SetIconStateAfterDrag( eIcon_Disable );
            }

            s_CUI_ID_FRAME_PACK.RefreshPackByIndex( pNewData->indexScr, pNewData->pBagListImg, pNewData->pBag, pNewData->bagType );
            s_CUI_ID_FRAME_PACK.RefreshPackByIndex( pNewData->indexDst, pNewData->pBagListImg, pNewData->pBag, pNewData->bagType );
        }
    }
    return true;
}

bool CUI_ID_FRAME_PACK::IsCanFixBag()
{
	CItemBag2* pBag = NULL;
	if (m_pID_CHECKBOX_Material->IsChecked())
		pBag = &thePlayerRole.m_bagMaterial;
	else if (m_pID_CHECKBOX_Task->IsChecked())
		pBag = &thePlayerRole.m_bagTask;
	else
		pBag = &thePlayerRole.m_bag;

	if(!pBag)
		return false;

	for (int nIndex = 0;nIndex < pBag->GetNowBagSize();++nIndex)
	{
		if(pBag->IsHaveItem(nIndex))
		{
			if(!pBag->m_bEnables[nIndex])
				return false;
		}
	}

	return true;
}
void CUI_ID_FRAME_PACK::OpenChangKu()
{
	//打开仓库 随身仓库
	if(!thePlayerRole.GetActivedPet())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_ActionPetNon ) );
		return;
	}
	//发送命令道服务器端 打开仓库
	MsgOpenBagStorage msg;
	GettheNetworkInput().SendMsg(&msg);
	//s_CUI_ID_FRAME_Storage.SetVisable(true);//打开仓库
}
void CUI_ID_FRAME_PACK::OnUpdateUIShopAndCK()
{
	if(!IsVisable()) return;
	if(!thePlayerRole.GetActivedPet())
	{
		m_pID_BUTTON_PocketShop->SetEnable(false);
		m_pID_BUTTON_Changku->SetEnable(false);
		m_pID_BUTTON_mend2->SetEnable(false);
		m_pID_BUTTON_mend->SetEnable(false);
		if(m_bRepair)
		{
			m_bRepair = false;
			theMouseManager.SetCursor(MouseManager::Type_Arrow);
			theMouseManager.SetUICursor(MouseManager::Type_Arrow);
		}
	}
	else
	{
		if(!m_pID_BUTTON_PocketShop->IsEnable())
			m_pID_BUTTON_PocketShop->SetEnable(true);
		if(!m_pID_BUTTON_Changku->IsEnable())
			m_pID_BUTTON_Changku->SetEnable(true);
		if(!m_pID_BUTTON_mend2->IsEnable())
			m_pID_BUTTON_mend2->SetEnable(true);
		if(!m_pID_BUTTON_mend->IsEnable())
			m_pID_BUTTON_mend->SetEnable(true);
	}
}