/********************************************************************
Created by UIEditor.exe
FileName: D:\res\client\UI\Storage.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "UIStorage.h"
#include "FuncPerformanceLog.h"

#include "XmlStringLanguage.h"
#include "GameMain.h"
#include "PlayerRole.h"
#include "PlayerMgr.h"
#include "../Player.h"
#include "pack.h"
#include "InputBox.h"
#include "MessageBox.h"
#include "ChatInfoBox.h"
#include "MeUi/ControlList.h"
#include "MeUi/MouseManager.h"
#include "../NpcCoord.h"
#include "Pack_Ex.h"
#include "MessageDefine.h"
#include "core/Name.h"
#include "SaveMoney.h"
#include "meui/ExpressionManager.h"
#include "SuperPasswordReset.h"
#include "SuperPasswordRegister.h"
#include "me3d/Vector.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "GameMain.h"
#include "WealthProtect.h"
#include "PackItemEnableManager.h"
#include "SuperPassword.h"
#include "XmlStringLanguage.h"
#include "ScreenInfoManager.h"


//-----------仓库收费参数设置------------------------------------
#define StorageRulePara_A  10204
#define StorageRulePara_B  9.8
#define Count_Char 128
//-----------------------------------------------------------
extern CHeroGame* theApp;


static int s_nHeightMaxShowCount = 0;

CUI_ID_FRAME_Storage s_CUI_ID_FRAME_Storage;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Storage, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Storage, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Storage, ID_BUTTON_CloseOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Storage, ID_BUTTON_helpOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Storage, ID_LIST_cityOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Storage, ID_LIST_priceOnListSelectChange )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Storage, ID_LISTIMG_MainOnIconButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Storage, ID_LISTIMG_MainOnIconDragOn )
MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_Storage, ID_LISTIMG_MainOnIconDragOff )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Storage, ID_LISTIMG_MainOnIconLDBClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Storage, ID_LISTIMG_MainOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Storage, ID_BUTTON_LOCKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Storage, ID_BUTTON_UNLOCKOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Storage, ID_BUTTON_ClearPwdOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Storage, ID_BUTTON_CHANGE_PWDOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Storage, ID_BUTTON_UpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Storage, ID_BUTTON_DownOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Storage, ID_BUTTON_CleanOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Storage, ID_BUTTON_SplitOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Storage, ID_BUTTON_SaveOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Storage, ID_BUTTON_GetOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Storage, ID_BUTTON_PasswordOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Storage, ID_CHECKBOX_Storage1OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Storage, ID_CHECKBOX_Storage2OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Storage, ID_CHECKBOX_Storage3OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Storage, ID_CHECKBOX_Storage4OnCheckBoxCheck )
CUI_ID_FRAME_Storage::CUI_ID_FRAME_Storage()
{
	guardfunc;
	// SGuildMember
	ResetMembers();
}

void CUI_ID_FRAME_Storage::ResetMembers()
{
	m_pID_FRAME_Storage = NULL;
//	m_pID_BUTTON_Close = NULL;
	//m_pID_BUTTON_help = NULL;
	m_pID_LIST_city = NULL;
	m_pID_LIST_price = NULL;								 
	m_pID_LISTIMG_Main = NULL;
	m_pID_BUTTON_LOCK = NULL;
	m_pID_BUTTON_UNLOCK = NULL;
	m_pID_BUTTON_CHANGE_PWD = NULL;
	//m_pID_BUTTON_ClearPwd = NULL;
	m_pID_BUTTON_Up = NULL;
	m_pID_BUTTON_Down = NULL;
	m_pID_PICTURE_PageShow = NULL;
	m_pID_TEXT_Page = NULL;
	m_pID_BUTTON_Clean = NULL;
	m_pID_BUTTON_Split = NULL;
	m_pID_BUTTON_Save = NULL;
	m_pID_BUTTON_Get = NULL;
	m_pID_TEXT_MONEY = NULL;
	m_pID_TEXT_AllNum = NULL;
	m_pID_BUTTON_Password = NULL;
	m_pID_PICTURE_Limit = NULL;
	m_pID_CHECKBOX_Storage1 = NULL;
	m_pID_CHECKBOX_Storage2 = NULL;
	m_pID_CHECKBOX_Storage3 = NULL;
	m_pID_CHECKBOX_Storage4 = NULL;

	bInUIFrameLock = false;
	bInUIFrameUnLock = false;
	strcpy(szItem_PrePWD,"");
	strcpy(szItem_LastPWD,"");
	strcpy(szItem_PWD,"");
	m_ustDstIndex = 0;
	m_nNpcSysId = -1;
	m_bQuestNpc = false;
	nPageCount = int(STORAGE_ITEMGRID_MAX/PAGESIZE);
	nPageCurr = 0;
	IsNpcStorage = true;
	unguard;
}
struct S_DstSrcIndex
{
	unsigned int nDstIndex;
	unsigned int nSrcIndex;
	ControlListImage* pBagListImg;
	CItemBag2* pBag;
	int bagType;
};
// Frame
bool CUI_ID_FRAME_Storage::OnFrameRun()
{
	guardfunc;
	if ( m_nNpcSysId < 0 )
		return false;
	//获得玩家自己的坐标
	CPlayer* pMe = NULL;
	pMe = theApp->GetPlayerMgr()->GetMe();
	if ( !pMe )
		return false;
	if(IsNpcStorage)
	{
		float fMeX,fMeY,fMeZ;
		pMe->GetPos( &fMeX, &fMeY, &fMeZ );
		//获得NPC的坐标
		CPlayer* pNpc = theHeroGame.GetPlayerMgr()->FindByID( m_nNpcSysId );
		if ( !pNpc )
		{
			if(s_CUI_ID_FRAME_Storage.IsVisable())
			{
				s_CUI_ID_FRAME_Storage.SetVisable(false);
				theMouseManager.SetUICursor(MouseManager::Type_Arrow);
				m_bQuestNpc = false;
			}
			return false;
		}
		float fNpcX, fNpcY, fNpcZ;
		pNpc->GetPos( &fNpcX, &fNpcY, &fNpcZ );
		float x = fNpcX - fMeX;
		float y = fNpcY - fMeY;
		//计算玩家与NPC之间的距离
		float dist = sqrtf( x*x + y*y );
		//如果玩家和NPC的距离大于8.0f就关闭仓库和包裹交易窗口,并把光标设置为原先的状态
		if( dist > 8.0f && m_bQuestNpc )
		{
			if(s_CUI_ID_FRAME_Storage.IsVisable())
			{
				s_CUI_ID_FRAME_Storage.SetVisable(false);
				theMouseManager.SetUICursor(MouseManager::Type_Arrow);
				m_bQuestNpc = false;
			}
		}
	}
	if( s_CUI_ID_FRAME_Storage.IsVisable() )
	{
		UpdateIconInfo();
	}

	return true;
	unguard;
}
bool CUI_ID_FRAME_Storage::OnFrameRender()
{
	guardfunc;
	return true;
	unguard;
}

void CUI_ID_FRAME_Storage::UpdateIconInfo()
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
	if ( m_pID_LISTIMG_Main->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true )
	{
		// 这里tip的位置取当前item的左边界
		// 这样就可以固定tip位置
		RECT rcItem;
		m_pID_LISTIMG_Main->GetItemRect( pos.x, pos.y, rcItem );	
		// 偏移到中间
		rcItem.left += m_pID_LISTIMG_Main->GetItemWidth() / 2;
		rcItem.top += m_pID_LISTIMG_Main->GetItemHeight() / 2;
		
		bool bHaveCompare = false;
		ControlIconDrag::S_ListImg *pItem = m_pID_LISTIMG_Main->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );
		if(!pItem)
			return;

		if(pItem->IsNull())
			return;

		int nSrcIndex = m_pID_LISTIMG_Main->GetItemIndex( pItem );

		SCharItem* pscharItem;

		pscharItem = thePlayerRole.m_stStorage.GetItemByIndex( nPageCurr * PAGESIZE + nSrcIndex );

		if(pscharItem)
		{
			pItem->SetData(pscharItem);
		}
	}
}

// Button
bool CUI_ID_FRAME_Storage::ID_BUTTON_CloseOnButtonClick( ControlObject* pSender )
{
	guardfunc;			
	if( !m_pID_FRAME_Storage )
		return false;
	//光标置回原来的状态
	theMouseManager.SetUICursor(MouseManager::Type_Arrow);
	SetVisable(false);
	s_CUI_ID_FRAME_PACK.SetVisable(false);
	s_CUI_ID_FRAME_PACK.SetInUIFrameLock(false);
	s_CUI_ID_FRAME_PACK.SetInUIFrameUnLock(false);
	s_CUI_ID_FRAME_Storage.bInUIFrameLock = false;
	s_CUI_ID_FRAME_Storage.bInUIFrameUnLock = false;
	return true;
	unguard;
}
// Button
// bool CUI_ID_FRAME_Storage::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
// {
// 	guardfunc;
// 	if( !m_pID_FRAME_Storage )
// 		return false;
// 	return true;
// 	unguard;
// }
// List
void CUI_ID_FRAME_Storage::ID_LIST_cityOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_Storage )
		return;
}
// List
void CUI_ID_FRAME_Storage::ID_LIST_priceOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_Storage )
		return;
}
bool PackItemToStorage_DefCallBackFun( const char* szInputData, void *pData )
{
	guardfunc;

	if (theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->IsDead())
	{
		return false;
	}

	S_DstSrcIndex *pDstSrcIndex = (S_DstSrcIndex*)pData;
	int nGoodsCount = atoi( szInputData );
	if ( nGoodsCount <= 0 )
		return false;
	if(nGoodsCount > s_CUI_ID_FRAME_Storage.GetChangeCount())
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_OverCount) );
		return false;
	}

	SCharItem stPackItem;
	SCharStorageData* pStorageItem = NULL; 
	if( !pDstSrcIndex->pBag->GetItem( pDstSrcIndex->nSrcIndex, &stPackItem ) )
		return false;

	//最大存储限制为物品堆叠数
	if(nGoodsCount>CItemBag2::GetItemStackCount(stPackItem.itembaseinfo.ustItemID))
	{
		nGoodsCount = CItemBag2::GetItemStackCount(stPackItem.itembaseinfo.ustItemID);
		char szInfo[128] = {0};
		//物品最大存储数目为物品堆叠数
		sprintf(szInfo, "%s %d", theXmlString.GetString( eText_ItemMaxStoreNum ) , 
			nGoodsCount);
		s_CUI_ID_FRAME_MessageBox.Show( szInfo );
	}

	pStorageItem = &thePlayerRole.m_stStorage;

	if (stPackItem.storageinfo.bIsLocked&&
		nGoodsCount != stPackItem.itembaseinfo.ustItemCount)
	{
		return false;
	}

	MsgMoveStorageItem msg;
	msg.nGuid = stPackItem.itembaseinfo.nOnlyInt;
	msg.enMoveType = MsgMoveStorageItem::Type_PackToStorage;
	msg.ustDstIndex = pDstSrcIndex->nDstIndex;
	msg.ustSrcIndex = pDstSrcIndex->nSrcIndex;
	msg.ustCount = nGoodsCount;
	msg.nNpcID = thePlayerRole.GetNpcID();
	msg.ucItemBagType = pDstSrcIndex->bagType;
	GettheNetworkInput().SendMsg( &msg );


	stPackItem.itembaseinfo.ustItemCount = nGoodsCount;
	stPackItem.storageinfo.nStorageNpcId = thePlayerRole.GetNpcID(); 
	//将物品标志设为 仓库1
// 	stPackItem.storageinfo.nWhoIs = 1;

	pStorageItem->stStorageItems[pDstSrcIndex->nDstIndex] = stPackItem;
	pDstSrcIndex->pBag->ClearItem(pDstSrcIndex->nSrcIndex,nGoodsCount);

	//通过npc的id 得到 npc 名字 
	const char* szName = NpcCoord::getInstance()->GetNpcName(thePlayerRole.GetNpcID());
	if(szName)
	{
		strcpy(thePlayerRole.CityName[pDstSrcIndex->nDstIndex], szName);
	}

	s_CUI_ID_FRAME_Storage.Refeash();
	s_CUI_ID_FRAME_PACK.RefreshPackByIndex(pDstSrcIndex->nSrcIndex, pDstSrcIndex->pBagListImg, pDstSrcIndex->pBag, pDstSrcIndex->bagType);
	

	ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID(stPackItem.itembaseinfo.ustItemID);
    if ( pItemDetail && pItemDetail->ucItemType == ItemDefine::ITEMTYPE_RESTORE )
    {
        ItemDefine::SItemRestore* pItemRestore = (ItemDefine::SItemRestore*)pItemDetail;
        if ( pItemRestore->bHPAuto || pItemRestore->bMPAuto || pItemRestore->bAutoRelive )
        {
            thePlayerRole.refreshHotKey();
        }
    }
	return true;
	unguard;
}
//
bool PackToStorage_DefCallBackFun( const bool bPressYesButton, void *pData )
{
	guardfunc;
	if ( bPressYesButton == true )
	{
		PackItemToStorage_DefCallBackFun( "1", pData );
	}
	return true;
	unguard;
}
bool CUI_ID_FRAME_Storage::AddPackItem( int nPackItemIndex,
									   ControlIconDrag::S_ListImg* pItemPack, 
									   ControlIconDrag::S_ListImg* pItemStorage,
									   ControlListImage* pBagListImg,
									   CItemBag2* pBag,
									   int bagType)
{

	if ( pItemPack->IsNull() )
	{
		return false;
	}
	unsigned int nDstIndex = 0;	
	if(pItemStorage == NULL)
	{
		nDstIndex = m_pID_LISTIMG_Main->GetNullItem() + PAGESIZE * nPageCurr;
	}
	else
	{
		nDstIndex = m_pID_LISTIMG_Main->GetItemIndex( pItemStorage ) + PAGESIZE*s_CUI_ID_FRAME_Storage.nPageCurr;
	}

	if ( nDstIndex >= thePlayerRole.GetData(CPlayerRole::TYPE_Storage) )
	{		
		return false;
	}

	S_DstSrcIndex stDstSrcIndex;
	stDstSrcIndex.nDstIndex = nDstIndex;
	stDstSrcIndex.nSrcIndex = nPackItemIndex;
	stDstSrcIndex.pBagListImg = pBagListImg;
	stDstSrcIndex.pBag = pBag;
	stDstSrcIndex.bagType = bagType;

	//-------
	if (nDstIndex>= thePlayerRole.GetData(CPlayerRole::TYPE_Storage) ||
		nPackItemIndex>= pBag->GetNowBagSize() )
		return false;

	int nStorageEmptyIndex = -1;
	if(pItemStorage == NULL)
	{
		nStorageEmptyIndex = m_pID_LISTIMG_Main->GetNullItem();
		if(nStorageEmptyIndex == -1)
		{//说明没有 空位了
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
		}
	}
	else
	{
		if ( !pItemStorage->IsNull() )
			return false;
		nStorageEmptyIndex = m_pID_LISTIMG_Main->GetItemIndex( pItemStorage );
	}

	ItemDefine::SItemCommon *pItem = GettheItemDetail().GetItemByID(pItemPack->m_pkIconInfo->Id());
	if ( !pItem )
		return false;
	//利用ItemDetail类里的全局静态变量来判断该物品是否在吟唱状态
	//如果True,则不允许放入仓库
	if(pItem->bIsSinging)
		return false;
	// 物品是否可以放入仓库
	if ( !pItem->bIsCanPushInStorage )
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_CanNotPushItemIntoStorage) );
		return false;
	}

	if (s_CUI_ID_FRAME_PACK.GetSplitCount() > 0)
	{
		char buf[64] = {0};
		sprintf(buf, "%d", s_CUI_ID_FRAME_PACK.GetSplitCount());
		m_dwChangeCount	= s_CUI_ID_FRAME_PACK.GetSplitCount();
		PackItemToStorage_DefCallBackFun( buf, &stDstSrcIndex );

		s_CUI_ID_FRAME_PACK.SetSplitItem(false);
		return true;
	}

	m_dwChangeCount	= pItemPack->m_pkIconInfo->Count();

	//不询问，直接放
	char strCount[256];
	itoa(m_dwChangeCount,strCount,10);
	PackItemToStorage_DefCallBackFun( strCount, &stDstSrcIndex );

	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Storage::ID_LISTIMG_MainOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													   ControlIconDrag::S_ListImg* pItemDrag,
													   ControlIconDrag::S_ListImg* pItemSrc )
{
	guardfunc;
	if( !m_pID_FRAME_Storage )
		return false;

	if ( pItemDrag->IsNull() )
	{
		return false;
	}
    
    // 安全保护
    if( CWealthProtect::Instance().IsInProtectTime() )
        return false;

	int nDstIndex = 0;
	if(pItemSrc == NULL)
	{
		nDstIndex = m_pID_LISTIMG_Main->GetNullItem() + nPageCurr * PAGESIZE;
	}
	else
	{
		nDstIndex = m_pID_LISTIMG_Main->GetItemIndex( pItemSrc ) + PAGESIZE*s_CUI_ID_FRAME_Storage.nPageCurr;
	}
	
	if( m_pID_LISTIMG_Main->GetNullItem() == -1)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PKMode_Change, theXmlString.GetString(eText_Item_CurPageStorageFull) );
		return false;
	}

	if ( nDstIndex >= thePlayerRole.GetData(CPlayerRole::TYPE_Storage) )
	{	
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PKMode_Change, theXmlString.GetString(eText_Item_CurPageStorageFull) );
		return false;
	}
	unsigned int nSrcIndex = 0;
	// Me
	if ( pSender == pMe )
	{
		if( s_CUI_ID_FRAME_Storage.bInUIFrameLock == true ||
			s_CUI_ID_FRAME_PACK.GetInUIFrameLock() == true)
		{
			s_CUI_ID_FRAME_Storage.bInUIFrameLock = false;
			s_CUI_ID_FRAME_PACK.SetInUIFrameLock(false);
			theMouseManager.SetUICursor(MouseManager::Type_Arrow);
		}
		nSrcIndex = m_pID_LISTIMG_Main->GetItemIndex( pItemDrag )+ PAGESIZE*s_CUI_ID_FRAME_Storage.nPageCurr;
		if ( nSrcIndex >= thePlayerRole.GetData(CPlayerRole::TYPE_Storage) )
		{
			return false;
		}
		//
		SCharStorageData* pStorageItem = NULL;
		pStorageItem = &thePlayerRole.m_stStorage;

		//同一物品
		if((pStorageItem->stStorageItems[nSrcIndex].itembaseinfo.ustItemID == pStorageItem->stStorageItems[nDstIndex].itembaseinfo.ustItemID)&&
			(pStorageItem->stStorageItems[nDstIndex].itembaseinfo.ustItemID!=InvalidLogicNumber)
			&& (pStorageItem->stStorageItems[nSrcIndex].storageinfo.bIsLocked 
			== pStorageItem->stStorageItems[nDstIndex].storageinfo.bIsLocked)
			)
		{
			ItemDefine::SItemWeapon *pItemWeapon = NULL;
			pItemWeapon	= (ItemDefine::SItemWeapon *)GettheItemDetail().GetItemByID(pStorageItem->stStorageItems[nDstIndex].itembaseinfo.ustItemID);
			if(!pItemWeapon)
				return false;
			if(pItemWeapon->IsExclusive())
			{
				return false;
			}
			else
			{
				//同一城市
				if(pStorageItem->stStorageItems[nDstIndex].storageinfo.nStorageNpcId 
					== pStorageItem->stStorageItems[nSrcIndex].storageinfo.nStorageNpcId)
				{
					int nTempCount = pStorageItem->stStorageItems[nDstIndex].itembaseinfo.ustItemCount + pStorageItem->stStorageItems[nSrcIndex].itembaseinfo.ustItemCount;
					if(nTempCount <= CItemBag2::GetItemStackCount(pStorageItem->stStorageItems[nSrcIndex].itembaseinfo.ustItemID))
					{
						MsgMoveStorageItem msg;
						msg.nGuid = pStorageItem->stStorageItems[nSrcIndex].itembaseinfo.nOnlyInt;
						msg.enMoveType = MsgMoveStorageItem::Type_StorageToStorage; 	
						msg.ustDstIndex = nDstIndex;
						msg.ustSrcIndex = nSrcIndex;
						msg.ustCount = pStorageItem->stStorageItems[nSrcIndex].itembaseinfo.ustItemCount;

                        // 检查绑定不绑定合并
                        if( CUI_ID_FRAME_PACK::IsSameItemDifInBound( pStorageItem->stStorageItems[nSrcIndex].itembaseinfo.nOnlyInt, nSrcIndex,
                            pStorageItem->stStorageItems[nDstIndex].itembaseinfo.nOnlyInt, nDstIndex ) )
                        {
                            s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eText_ItemBind_ConfirmByDifInBound ), "",
                                CUI_ID_FRAME_MessageBox::eTypeYesNo, false, CUI_ID_FRAME_Storage::ConfirmBoundCallback,
                                ( void* )( &msg ), sizeof( MsgMoveStorageItem ) );
                        }
                        else
                        {
                            GettheNetworkInput().SendMsg( &msg );

                            pStorageItem->stStorageItems[nDstIndex].itembaseinfo.ustItemCount += pStorageItem->stStorageItems[nSrcIndex].itembaseinfo.ustItemCount;
                            pStorageItem->stStorageItems[nSrcIndex].itembaseinfo.ustItemID = InvalidLogicNumber;	
                            //价格清空
                            thePlayerRole.fCostOfFetchItem[nSrcIndex] = 0;
                            //城市名字清空
                            strcpy_s( thePlayerRole.CityName[nSrcIndex], MAX_NAME_STRING, 
                                "" );
                            s_CUI_ID_FRAME_Storage.Refeash();
                        }
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}

			}

		}
		//不同物品
		else if(pStorageItem->stStorageItems[nDstIndex].itembaseinfo.ustItemID == InvalidLogicNumber)
		{
			MsgMoveStorageItem msg;
			msg.nGuid = pStorageItem->stStorageItems[nSrcIndex].itembaseinfo.nOnlyInt;
			msg.enMoveType = MsgMoveStorageItem::Type_StorageToStorage; 	
			msg.ustDstIndex = nDstIndex;
			msg.ustSrcIndex = nSrcIndex;
			msg.ustCount = pStorageItem->stStorageItems[nSrcIndex].itembaseinfo.ustItemCount;
			GettheNetworkInput().SendMsg( &msg );

			//物品付给
			pStorageItem->stStorageItems[nDstIndex] = pStorageItem->stStorageItems[nSrcIndex];
			//价格付给
			thePlayerRole.fCostOfFetchItem[nDstIndex] = thePlayerRole.fCostOfFetchItem[nSrcIndex];
			//城市付给
			strcpy(thePlayerRole.CityName[nDstIndex],thePlayerRole.CityName[nSrcIndex]);
			thePlayerRole.fCostOfFetchItem[nSrcIndex] = 0;
			strcpy(thePlayerRole.CityName[nSrcIndex],"");
			pStorageItem->stStorageItems[nSrcIndex].itembaseinfo.ustItemID = InvalidLogicNumber;	
			s_CUI_ID_FRAME_Storage.Refeash();
		}
		else if( pItemSrc->m_pkIconInfo->Id() != pItemDrag->m_pkIconInfo->Id() )//物品交换
		{
			SCharItem *pDst;
			SCharItem *pSrc;
			pDst = &pStorageItem->stStorageItems[nDstIndex];
			pSrc = &pStorageItem->stStorageItems[nSrcIndex];
			if ( CItemBag2::ExchangeItem( pDst, pSrc,NULL,NULL,"" ) )
			{
				//发送消息给服务端
				MsgChangeItemPos msg;
				msg.ustDstIndex = nDstIndex;
				msg.ustSrcIndex = nSrcIndex;
				msg.nWhichIs = 1;
				GettheNetworkInput().SendMsg( &msg );
				//城市信息替换
				char szCityInfoDst[128];
				char szCityInfoSrc[128];
				strcpy(szCityInfoDst,thePlayerRole.CityName[nDstIndex]);
				strcpy(szCityInfoSrc,thePlayerRole.CityName[nSrcIndex]);
				strcpy(thePlayerRole.CityName[nDstIndex],szCityInfoSrc);
				strcpy(thePlayerRole.CityName[nSrcIndex],szCityInfoDst);
                //取物品费用交换
                float fCostDst;
				float fCostSrc;
				fCostDst = thePlayerRole.fCostOfFetchItem[nDstIndex];
                fCostSrc = thePlayerRole.fCostOfFetchItem[nSrcIndex];

				thePlayerRole.fCostOfFetchItem[nDstIndex] = fCostSrc;
				thePlayerRole.fCostOfFetchItem[nSrcIndex] = fCostDst;

				s_CUI_ID_FRAME_Storage.Refeash();
			}
			return true;
		}
	}
	// Pack @PS: this is only way to push item into storage
	else if ( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pSender) )
	{
		// 包裹拆分物品不能直接扔仓库
		if( s_CUI_ID_FRAME_PACK.GetSplitCount() == 0 )
		{
			nSrcIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_NormalItemBag, pItemDrag );
			if( nSrcIndex != -1 && s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag) )
				AddPackItem( nSrcIndex, pItemDrag, pItemSrc, s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag),
					&thePlayerRole.m_bag, BT_NormalItemBag );
		}
		else
			return false;
	}
	else if ( s_CUI_ID_FRAME_PACK.IsListImageByBagType( BT_MaterialBag, pSender ) )
	{
		// 包裹拆分物品不能直接扔仓库
		if( s_CUI_ID_FRAME_PACK.GetSplitCount() == 0 )
		{
			nSrcIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_MaterialBag, pItemDrag );
			if( nSrcIndex != -1 && s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_MaterialBag) )
				AddPackItem( nSrcIndex, pItemDrag, pItemSrc, s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_MaterialBag),
					&thePlayerRole.m_bagMaterial, BT_MaterialBag );
		}
		else
			return false;
	}

	return true;
	unguard;
}
bool CUI_ID_FRAME_Storage::ID_LISTIMG_MainOnIconDragOff( ControlObject* pSender, ControlObject* pMe,
														ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Storage )
		return false;
	return false;
}
bool CUI_ID_FRAME_Storage::ID_LISTIMG_MainOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Storage )
		return false;
	return false;
}
bool CUI_ID_FRAME_Storage::ID_LISTIMG_MainOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Storage )
		return false;
	return false;
}
bool CUI_ID_FRAME_Storage::ID_LISTIMG_MainOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Storage )
		return false;
	//当有二级密码的时候		liaojie
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

	if( s_CUI_ID_FRAME_PACK.IsVisable() )
	{
        // 安全保护
        if( CWealthProtect::Instance().IsInProtectTime() )
            return false;

		int nSrcIndex = s_CUI_ID_FRAME_Storage.m_pID_LISTIMG_Main->GetItemIndex( pItem )+ PAGESIZE*s_CUI_ID_FRAME_Storage.nPageCurr;

		ItemDefine::SItemCommon *pSrcItem = (ItemDefine::SItemCommon *)GettheItemDetail().GetItemByID(
			thePlayerRole.m_stStorage.stStorageItems[nSrcIndex].itembaseinfo.ustItemID );
		if (!pSrcItem)
			return false;

		ControlListImage* pBagListImg = 0;
		CItemBag2* pBag = 0;
		int bagType = BT_NormalItemBag;
		switch (pSrcItem->ucItemType)
		{
		case ItemDefine::ITEMTYPE_MATERIAL:
		case ItemDefine::ITEMTYPE_GEM:
			pBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_MaterialBag);
			pBag = &thePlayerRole.m_bagMaterial;
			bagType = BT_MaterialBag;
			break;
		case ItemDefine::ITEMTYPE_TASK:
			pBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_TaskBag);
			pBag = &thePlayerRole.m_bagTask;
			bagType = BT_TaskBag;
			break;
		default:
			pBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag);
			pBag = &thePlayerRole.m_bag;
			bagType = BT_NormalItemBag;
			break;
		}

		unsigned int nDstIndex = pBagListImg->GetNullItem();		
		if ( nDstIndex == -1 || nDstIndex >= pBag->GetNowBagSize())//没位置了
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

		s_CUI_ID_FRAME_PACK.dropIconFromStorage( nSrcIndex, nDstIndex, pBagListImg, pItem, NULL, pBagListImg, pBag, bagType);
		return true;
	}
	return false;
}
// Button
bool CUI_ID_FRAME_Storage::ID_BUTTON_LOCKOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_Storage )
		return false;
	//物品加锁 鼠标标志切换，相应开关打开
	if(bInUIFrameLock)
	{
		theMouseManager.SetUICursor(MouseManager::Type_Arrow);
		bInUIFrameLock = false;
		if(s_CUI_ID_FRAME_Storage.bInUIFrameUnLock)
		{
			s_CUI_ID_FRAME_Storage.bInUIFrameUnLock = false;
		}
	}
	else
	{
		theMouseManager.SetUICursor( MouseManager::Type_LockItem );
		bInUIFrameLock = true;
		if(s_CUI_ID_FRAME_Storage.bInUIFrameUnLock)
		{
			s_CUI_ID_FRAME_Storage.bInUIFrameUnLock = false;
		}	
	}
	return true;
	unguard;
}
// Button
bool CUI_ID_FRAME_Storage::ID_BUTTON_UNLOCKOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_Storage )
		return false;
	//物品解锁 鼠标标志切换，相应开关打开
	if(bInUIFrameUnLock)
	{
		theMouseManager.SetUICursor(MouseManager::Type_Arrow);
		bInUIFrameUnLock = false;
		if(s_CUI_ID_FRAME_Storage.bInUIFrameLock)
		{
			s_CUI_ID_FRAME_Storage.bInUIFrameLock = false;
		}
	}
	else
	{
		theMouseManager.SetUICursor( MouseManager::Type_UnLockItem );
		s_CUI_ID_FRAME_Storage.bInUIFrameUnLock = true;
		if(s_CUI_ID_FRAME_Storage.bInUIFrameLock)
		{
			s_CUI_ID_FRAME_Storage.bInUIFrameLock = false;
		}
	}
	return true;
	unguard;
}
//上一页
bool CUI_ID_FRAME_Storage::ID_BUTTON_UpOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Storage )
		return false;
// 	if(nPageCurr<nPageCount&&nPageCurr>0)
// 	{
// 		nPageCurr--;
// 	}
	
	Refeash();
	return true;
}
// 下一页
bool CUI_ID_FRAME_Storage::ID_BUTTON_DownOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Storage )
		return false;
	return true;
}
bool CUI_ID_FRAME_Storage::ID_BUTTON_CHANGE_PWDOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_Storage )
		return false;
	return false;
	unguard;
}
bool AskClearPwdOfItem_DefCallBackFun( const bool bPressYesButton, void *pData )
{
	guardfunc;
	return true;
	unguard;
}
// bool CUI_ID_FRAME_Storage::ID_BUTTON_ClearPwdOnButtonClick( ControlObject* pSender )
// {
// 	guardfunc;
// 	if( !m_pID_FRAME_Storage )
// 		return false;
//     return false;
// 	unguard;
// }
// Button
bool CUI_ID_FRAME_Storage::ID_BUTTON_CleanOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Storage )
		return false;
	MsgCleanUpBag msg;
	msg.ucItemBagType = BT_StorageBag;
	//以下两个值服务器没用
	msg.stBagIndexBegin = 0;
	msg.stBagIndexEnd = thePlayerRole.GetData(CPlayerRole::TYPE_Storage);
	GettheNetworkInput().SendMsg( &msg );
	return true;
}
// Button
bool CUI_ID_FRAME_Storage::ID_BUTTON_SplitOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Storage )
		return false;
	s_CUI_ID_FRAME_PACK.SetSplitItem(!s_CUI_ID_FRAME_PACK.IsVisable());
	return true;
}
// Button
bool CUI_ID_FRAME_Storage::ID_BUTTON_SaveOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Storage )
		return false;
    // 安全保护
    if( CWealthProtect::Instance().IsInProtectTime() )
        return true;

    // 存钱
    s_CUI_ID_FRAME_SaveMoney.SetStorageType(MsgStorageMoneyReq::Save);
    s_CUI_ID_FRAME_SaveMoney.SetVisable(true);
	return true;
}
// Button
bool CUI_ID_FRAME_Storage::ID_BUTTON_GetOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Storage )
		return false;
   // 安全保护
    if( CWealthProtect::Instance().IsInProtectTime() )
        return true;
	//zhuxincong 取钱之前要先验证2级密码
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if (thePlayerRole.GetIsSecondPassword() && !s_CUI_ID_FRAME_SuperPassword.GetChecked() && pMe)
	{
		s_CUI_ID_FRAME_SuperPassword.SetVisiblePosition(*(Vector*)&pMe->GetPos());
		s_CUI_ID_FRAME_SuperPassword.SetVisable(true);
		return false;
	}
    // 取钱
    s_CUI_ID_FRAME_SaveMoney.SetStorageType(MsgStorageMoneyReq::TakeOut);
    s_CUI_ID_FRAME_SaveMoney.SetVisable(true);
	return true;
}

bool CUI_ID_FRAME_Storage::ID_BUTTON_PasswordOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Storage )
		return false;
	if(thePlayerRole.GetIsSecondPassword())
	{
		s_CUI_ID_FRAME_SuperPasswordReset.SetVisable(true);
		s_CUI_ID_FRAME_SuperPasswordReset.Reset();
		if( theHeroGame.GetPlayerMgr()->GetMe() )
			s_CUI_ID_FRAME_SuperPasswordReset.SetVisiblePosition(*(Vector*)&(theHeroGame.GetPlayerMgr()->GetMe())->GetPos());

		if( s_CUI_ID_FRAME_SuperPasswordReset.AddNameArray[0] )
			theUiManager.SetFocus(s_CUI_ID_FRAME_SuperPasswordReset.AddNameArray[0]);
	}
	else
	{
		s_CUI_ID_FRAME_SuperPasswordRegister.SetVisable(true);
		s_CUI_ID_FRAME_SuperPasswordRegister.Reset();
		if( theHeroGame.GetPlayerMgr()->GetMe() )
			s_CUI_ID_FRAME_SuperPasswordRegister.SetVisiblePosition(*(Vector*)&(theHeroGame.GetPlayerMgr()->GetMe())->GetPos());
		if( s_CUI_ID_FRAME_SuperPasswordRegister.GetEDIT_AddName() )
			theUiManager.SetFocus(s_CUI_ID_FRAME_SuperPasswordRegister.GetEDIT_AddName());
	}

	return true;
}

// CheckBox
void CUI_ID_FRAME_Storage::ID_CHECKBOX_Storage1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(nPageCurr == 0)
	{
		m_pID_CHECKBOX_Storage1->SetCheck(true);
		return;
	}

     ChangeItemByIndex(0);
}

// CheckBox
void CUI_ID_FRAME_Storage::ID_CHECKBOX_Storage2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(nPageCurr == 1)
	{
		m_pID_CHECKBOX_Storage2->SetCheck(true);
		return;
	}

     ChangeItemByIndex(1);
}

// CheckBox
void CUI_ID_FRAME_Storage::ID_CHECKBOX_Storage3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(nPageCurr == 2)
	{
		m_pID_CHECKBOX_Storage3->SetCheck(true);
		return;
	}

     ChangeItemByIndex(2);
}

// CheckBox
void CUI_ID_FRAME_Storage::ID_CHECKBOX_Storage4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(nPageCurr == 3)
	{
		m_pID_CHECKBOX_Storage4->SetCheck(true);
		return;
	}

     ChangeItemByIndex(3);
}

// 装载UI
bool CUI_ID_FRAME_Storage::_LoadUI()
{
	guardfunc;
	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\Storage.meui", false, UI_Render_LayerSecond );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[UI\\Storage.UI]失败")
			return false;
	}
	return DoControlConnect();
	unguard;
}
bool CheckPwd(const char* szInputData, void *pData)
{
	guardfunc;
	s_CUI_ID_FRAME_Storage.SetItem_LastPWD( szInputData );
	if(strcmp(s_CUI_ID_FRAME_Storage.GetItem_LastPWD(),"") == 0)
	{
		s_CUI_ID_FRAME_Storage.SetInUIFrameLock(false);
		s_CUI_ID_FRAME_PACK.SetInUIFrameLock(false);
		return false;
	}
	//光标置回原来的状态
	theMouseManager.SetUICursor(MouseManager::Type_Arrow);
	//判别两个字符串是否相等
	int nCompare = strcmp(s_CUI_ID_FRAME_Storage.GetItem_PrePWD(),s_CUI_ID_FRAME_Storage.GetItem_LastPWD());
	if(nCompare == 0)
	{
		if (thePlayerRole.IsLockNumLimit())
		{
			return false;
		}

		thePlayerRole.m_stStorage.stStorageItems[s_CUI_ID_FRAME_Storage.GetDstIndex()].storageinfo.bIsLocked = true;
		strcpy(thePlayerRole.szItem_PWD,s_CUI_ID_FRAME_Storage.GetItem_PrePWD()); 
		s_CUI_ID_FRAME_Storage.SetInUIFrameLock(false);
		s_CUI_ID_FRAME_PACK.SetInUIFrameLock(false);
		s_CUI_ID_FRAME_Storage.Refeash();
	}
	else
	{
		//两次输入的密码不一样！
		s_CUI_ID_FRAME_Storage.SetInUIFrameLock(false);
		s_CUI_ID_FRAME_PACK.SetInUIFrameLock(false);
		return false;
	}
	return true;
	unguard;
}
bool ItemLock(const char* szInputData, void *pData)
{
	guardfunc;	
	s_CUI_ID_FRAME_Storage.SetItem_PrePWD( szInputData );
	return true;
	unguard;
}
bool ItemUnLock(const char* szInputData, void *pData)
{
	guardfunc;
	SCharStorageData* pStorageItem = NULL;
	pStorageItem = &thePlayerRole.m_stStorage;
	s_CUI_ID_FRAME_Storage.SetItem_PWD( szInputData );
	int nCmpPwd = strcmp(s_CUI_ID_FRAME_Storage.GetItem_PWD(),thePlayerRole.szItem_PWD);
	//如果密码正确
	if(nCmpPwd == 0 )
	{
		pStorageItem->stStorageItems[s_CUI_ID_FRAME_Storage.GetDstIndex()].storageinfo.bIsLocked = false;
		s_CUI_ID_FRAME_Storage.SetInUIFrameUnLock(false);
		s_CUI_ID_FRAME_PACK.SetInUIFrameUnLock(false);
		s_CUI_ID_FRAME_Storage.Refeash();
	}
	else
	//如果密码错误
	{
		s_CUI_ID_FRAME_Storage.SetInUIFrameUnLock(false);
		s_CUI_ID_FRAME_PACK.SetInUIFrameUnLock(false);
		return false;		
	}
	return false;
	unguard;
}
bool ItemLock_DefCallBackFun(const bool bPressYesButton, void *pData )
{
	guardfunc;
	return false;
	unguard;
}
//物品加锁解锁
bool IconOnClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{	
	guardfunc;
	int index = s_CUI_ID_FRAME_Storage.LISTIMG_Main_GetIndexByItem(pItem);
	if( index == -1 )
		return false;
	unsigned int nWhichItemIndex = index + PAGESIZE*s_CUI_ID_FRAME_Storage.GetPageCurr();
	SCharStorageData* pStorageItem = NULL;
	pStorageItem = &thePlayerRole.m_stStorage;

    if (nWhichItemIndex >= PAGESIZE)
    {
        return false;
    }

	//物品加锁
	if(s_CUI_ID_FRAME_Storage.GetInUIFrameLock()||s_CUI_ID_FRAME_PACK.GetInUIFrameLock())
	{
		guard(test_1);
		if ( pStorageItem->stStorageItems[nWhichItemIndex].itembaseinfo.ustItemID == InvalidLogicNumber )
			return false;
	
		ItemDefine::SItemCommon *pCheckItem = GettheItemDetail().GetItemByID(pItem->m_pkIconInfo->Id());
		if( NULL == pCheckItem )
			return false;

		if(!pCheckItem->bIsCanLocked)
		{ 
			return false;	
		}

        // 统一接口         added by zhuomeng.hu		[12/30/2010]
        if( !CPackItemEnableManager::Instance()->IsPackItemEnable( &thePlayerRole.m_bag, nWhichItemIndex ) )
		{
			return false;	
		}

		if (thePlayerRole.IsLockNumLimit())
		{
			return false;
		}
		unguard;

		//如果物品已经加锁 return
		if(!pStorageItem->stStorageItems[nWhichItemIndex].storageinfo.bIsLocked)
		{
			guard(test_2);
			s_CUI_ID_FRAME_Storage.SetDstIndex(nWhichItemIndex);
			return true;
			unguard;
		}
		else
		{	
			s_CUI_ID_FRAME_Storage.SetInUIFrameLock(false);
			s_CUI_ID_FRAME_PACK.SetInUIFrameLock(false);
			theMouseManager.SetUICursor(MouseManager::Type_Arrow);
			return false;
		}
	}
	else if(s_CUI_ID_FRAME_Storage.GetInUIFrameUnLock()||s_CUI_ID_FRAME_PACK.GetInUIFrameUnLock())//物品解锁
	{
		guard(test_3);
		//如果物品已经未处于lock状态则 return
		if(pStorageItem->stStorageItems[nWhichItemIndex].storageinfo.bIsLocked)
		{
			s_CUI_ID_FRAME_Storage.SetDstIndex(nWhichItemIndex);
			//光标置回原来的状态
			theMouseManager.SetUICursor(MouseManager::Type_Arrow);
			return true;	
		}
		else
		{
			s_CUI_ID_FRAME_Storage.SetInUIFrameUnLock(false);
			s_CUI_ID_FRAME_PACK.SetInUIFrameUnLock(false);
			theMouseManager.SetUICursor(MouseManager::Type_Arrow);
			return false;
		}
		unguard;
	}
	else
	{
		return false;

	}
	return false;
	unguard;
}

// 关连控件
bool CUI_ID_FRAME_Storage::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_Storage, s_CUI_ID_FRAME_StorageOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Storage, s_CUI_ID_FRAME_StorageOnFrameRender );
// 	theUiManager.OnButtonClick( ID_FRAME_Storage, ID_BUTTON_Close, s_CUI_ID_FRAME_StorageID_BUTTON_CloseOnButtonClick );
	//theUiManager.OnButtonClick( ID_FRAME_Storage, ID_BUTTON_help, s_CUI_ID_FRAME_StorageID_BUTTON_helpOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_Storage, ID_LIST_city, s_CUI_ID_FRAME_StorageID_LIST_cityOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Storage, ID_LIST_price, s_CUI_ID_FRAME_StorageID_LIST_priceOnListSelectChange );
	theUiManager.OnIconButtonClick( ID_FRAME_Storage, ID_LISTIMG_Main, s_CUI_ID_FRAME_StorageID_LISTIMG_MainOnIconButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_Storage, ID_LISTIMG_Main, s_CUI_ID_FRAME_StorageID_LISTIMG_MainOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Storage, ID_LISTIMG_Main, s_CUI_ID_FRAME_StorageID_LISTIMG_MainOnIconLDBClick );
	theUiManager.OnButtonClick( ID_FRAME_Storage, ID_BUTTON_LOCK, s_CUI_ID_FRAME_StorageID_BUTTON_LOCKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Storage, ID_BUTTON_UNLOCK, s_CUI_ID_FRAME_StorageID_BUTTON_UNLOCKOnButtonClick );
	//theUiManager.OnButtonClick( ID_FRAME_Storage, ID_BUTTON_ClearPwd, s_CUI_ID_FRAME_StorageID_BUTTON_ClearPwdOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Storage, ID_BUTTON_CHANGE_PWD, s_CUI_ID_FRAME_StorageID_BUTTON_CHANGE_PWDOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Storage, ID_BUTTON_Up, s_CUI_ID_FRAME_StorageID_BUTTON_UpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Storage, ID_BUTTON_Down, s_CUI_ID_FRAME_StorageID_BUTTON_DownOnButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Storage, ID_LISTIMG_Main, s_CUI_ID_FRAME_StorageID_LISTIMG_MainOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_Storage, ID_BUTTON_Clean, s_CUI_ID_FRAME_StorageID_BUTTON_CleanOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Storage, ID_BUTTON_Split, s_CUI_ID_FRAME_StorageID_BUTTON_SplitOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Storage, ID_BUTTON_Save, s_CUI_ID_FRAME_StorageID_BUTTON_SaveOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Storage, ID_BUTTON_Get, s_CUI_ID_FRAME_StorageID_BUTTON_GetOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Storage, ID_BUTTON_Password, s_CUI_ID_FRAME_StorageID_BUTTON_PasswordOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Storage, ID_CHECKBOX_Storage1, s_CUI_ID_FRAME_StorageID_CHECKBOX_Storage1OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Storage, ID_CHECKBOX_Storage2, s_CUI_ID_FRAME_StorageID_CHECKBOX_Storage2OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Storage, ID_CHECKBOX_Storage3, s_CUI_ID_FRAME_StorageID_CHECKBOX_Storage3OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Storage, ID_CHECKBOX_Storage4, s_CUI_ID_FRAME_StorageID_CHECKBOX_Storage4OnCheckBoxCheck );
	
	m_pID_FRAME_Storage = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Storage );
// 	m_pID_BUTTON_Close = (ControlButton*)theUiManager.FindControl( ID_FRAME_Storage, ID_BUTTON_Close );
//	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_Storage, ID_BUTTON_help );
	m_pID_LIST_city = (ControlList*)theUiManager.FindControl( ID_FRAME_Storage, ID_LIST_city );
	m_pID_LIST_price = (ControlList*)theUiManager.FindControl( ID_FRAME_Storage, ID_LIST_price );
	m_pID_LISTIMG_Main = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Storage, ID_LISTIMG_Main );
	m_pID_BUTTON_LOCK = (ControlButton*)theUiManager.FindControl( ID_FRAME_Storage, ID_BUTTON_LOCK );
	m_pID_BUTTON_UNLOCK = (ControlButton*)theUiManager.FindControl( ID_FRAME_Storage, ID_BUTTON_UNLOCK );
	m_pID_BUTTON_CHANGE_PWD = (ControlButton*)theUiManager.FindControl( ID_FRAME_Storage, ID_BUTTON_CHANGE_PWD );
	//m_pID_BUTTON_ClearPwd = (ControlButton*)theUiManager.FindControl( ID_FRAME_Storage, ID_BUTTON_ClearPwd );
	m_pID_BUTTON_Up = (ControlButton*)theUiManager.FindControl( ID_FRAME_Storage, ID_BUTTON_Up );
	m_pID_BUTTON_Down = (ControlButton*)theUiManager.FindControl( ID_FRAME_Storage, ID_BUTTON_Down );
	m_pID_PICTURE_PageShow = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Storage, ID_PICTURE_PageShow );
	m_pID_TEXT_Page = (ControlText*)theUiManager.FindControl( ID_FRAME_Storage, ID_TEXT_Page );
	m_pID_BUTTON_Clean = (ControlButton*)theUiManager.FindControl( ID_FRAME_Storage, ID_BUTTON_Clean );
	m_pID_BUTTON_Split = (ControlButton*)theUiManager.FindControl( ID_FRAME_Storage, ID_BUTTON_Split );
	m_pID_BUTTON_Save = (ControlButton*)theUiManager.FindControl( ID_FRAME_Storage, ID_BUTTON_Save );
	m_pID_BUTTON_Get = (ControlButton*)theUiManager.FindControl( ID_FRAME_Storage, ID_BUTTON_Get );
	m_pID_TEXT_MONEY = (ControlText*)theUiManager.FindControl( ID_FRAME_Storage, ID_TEXT_MONEY );
	m_pID_TEXT_AllNum = (ControlText*)theUiManager.FindControl( ID_FRAME_Storage, ID_TEXT_AllNum );
	m_pID_BUTTON_Password = (ControlButton*)theUiManager.FindControl( ID_FRAME_Storage, ID_BUTTON_Password );
	m_pID_PICTURE_Limit = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Storage, ID_PICTURE_Limit );
	m_pID_CHECKBOX_Storage1 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Storage, ID_CHECKBOX_Storage1 );
	m_pID_CHECKBOX_Storage2 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Storage, ID_CHECKBOX_Storage2 );
	m_pID_CHECKBOX_Storage3 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Storage, ID_CHECKBOX_Storage3 );
	m_pID_CHECKBOX_Storage4 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Storage, ID_CHECKBOX_Storage4 );

	assert( m_pID_FRAME_Storage );
	m_pID_FRAME_Storage->SetVisable(false);
//	assert( m_pID_BUTTON_Close );
	//assert( m_pID_BUTTON_help );
	assert( m_pID_LIST_city );
	assert( m_pID_LIST_price );
	assert( m_pID_LISTIMG_Main );
	assert( m_pID_BUTTON_LOCK );
	assert( m_pID_BUTTON_UNLOCK );
	//assert( m_pID_BUTTON_ClearPwd );
	assert( m_pID_BUTTON_CHANGE_PWD);
	assert( m_pID_BUTTON_Up );
	assert( m_pID_BUTTON_Down );
	assert( m_pID_PICTURE_PageShow );
	assert( m_pID_TEXT_Page );
	assert( m_pID_BUTTON_Password );
	assert( m_pID_PICTURE_Limit );
	assert( m_pID_CHECKBOX_Storage1 );
	assert( m_pID_CHECKBOX_Storage2 );
	assert( m_pID_CHECKBOX_Storage3 );
	assert( m_pID_CHECKBOX_Storage4 );

	m_pID_LISTIMG_Main->SetButtonClickFun( IconOnClick );
	m_pID_LISTIMG_Main->ShowPressEffect(true);
	m_pID_LIST_city->HaveSelBar(false);
	m_pID_LIST_price->HaveSelBar(false);

	m_pID_PICTURE_Limit->setShowTip(true);
	m_pID_PICTURE_Limit->setTip(theXmlString.GetString(eText_MaxMoneyTip), DT_LEFT);

	s_nHeightMaxShowCount = m_pID_LISTIMG_Main->GetHeightShowMaxCnt();

	theUiManager.SetFrameLayout(UI_LAYOUT_1, m_pID_FRAME_Storage);

	m_pID_FRAME_Storage->SetMsgProcFun(StorageFrame_MsgProc);
	
	ChangeItemByIndex(0);

	USE_SCRIPT( eUI_OBJECT_Storage, this );

	return true;
	unguard;
}


bool CUI_ID_FRAME_Storage::StorageFrame_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	guardfunc;
	if( !s_CUI_ID_FRAME_Storage.IsVisable() )
		return false;

	if (!(s_CUI_ID_FRAME_SuperPasswordRegister.IsVisable() || s_CUI_ID_FRAME_SuperPasswordReset.IsVisable()))
	{
		return false;
	}

	switch( msg ) 
	{
	case WM_KEYUP:
		{
			if( wParam == VK_TAB )	//cancle
			{
				if( s_CUI_ID_FRAME_SuperPasswordRegister.IsVisable() && s_CUI_ID_FRAME_SuperPasswordRegister.GetEDIT_AddName() && s_CUI_ID_FRAME_SuperPasswordRegister.GetEDIT_AddName2())
				{
                            if (theUiManager.GetFocus() == s_CUI_ID_FRAME_SuperPasswordRegister.GetEDIT_AddName())
                            {
								theUiManager.SetFocus(s_CUI_ID_FRAME_SuperPasswordRegister.GetEDIT_AddName2());
                            }else
							{
								if (theUiManager.GetFocus() == s_CUI_ID_FRAME_SuperPasswordRegister.GetEDIT_AddName2())
								{
									theUiManager.SetFocus(s_CUI_ID_FRAME_SuperPasswordRegister.GetEDIT_AddName());
								}
							}

							

				}else if (s_CUI_ID_FRAME_SuperPasswordReset.IsVisable() && s_CUI_ID_FRAME_SuperPasswordReset.AddNameArray[0] && s_CUI_ID_FRAME_SuperPasswordReset.AddNameArray[1]&&s_CUI_ID_FRAME_SuperPasswordReset.AddNameArray[2]) 
				{
					 int NameId = 0;


					if (theUiManager.GetFocus() == s_CUI_ID_FRAME_SuperPasswordReset.AddNameArray[0])
						NameId = 1;

					if (theUiManager.GetFocus() == s_CUI_ID_FRAME_SuperPasswordReset.AddNameArray[1])
						NameId = 2;

					if (theUiManager.GetFocus() == s_CUI_ID_FRAME_SuperPasswordReset.AddNameArray[2])
						NameId = 0;

					theUiManager.SetFocus(s_CUI_ID_FRAME_SuperPasswordReset.AddNameArray[NameId]);
					
					
				}
				
				return true;
			}
			
			
		}
		break;
	}
	return false;
	unguard;
}



// 卸载UI
bool CUI_ID_FRAME_Storage::_UnLoadUI()
{
	guardfunc;
	theUiManager.RemoveFrameLayout(m_pID_FRAME_Storage);
	CLOSE_SCRIPT( eUI_OBJECT_Storage );
	ResetMembers();
	return theUiManager.RemoveFrame( "data\\ui\\Storage.meui" );
	unguard;
}
// 是否可视
bool CUI_ID_FRAME_Storage::_IsVisable()
{
	guardfunc;
	if (!m_pID_FRAME_Storage)
		return false;
	return m_pID_FRAME_Storage->IsVisable();
	unguard;
}
// 设置是否可视
void CUI_ID_FRAME_Storage::_SetVisable( const bool bVisable )
{
	guardfunc;
    if(!m_pID_FRAME_Storage)
        return;

	if ( m_pID_FRAME_Storage )
	{
		m_pID_FRAME_Storage->SetVisable( bVisable );
	}
	if ( bVisable == true )
	{
		INT nStorageX = SCREEN_WIDTH*2 / 3;
		if(!s_CUI_ID_FRAME_PACK.IsVisable())
		{
			s_CUI_ID_FRAME_PACK.SetVisable( bVisable );
		}
		m_bQuestNpc = true;
		ResetWindowPosition(m_pID_FRAME_Storage, s_CUI_ID_FRAME_PACK.GetFrame());

		RefeshStorageState();
        InitStorageState();

		UpdateMoney();
	}
	else
	{
		m_pID_FRAME_Storage->SetArrayMode( ArrayMode_Normal );
		s_CUI_ID_FRAME_PACK.SetFrameArrayMode( ArrayMode_Normal );
		IsNpcStorage = true;//关闭的时候
	}
	unguard;
}
void CUI_ID_FRAME_Storage::GetNpcSysID( unsigned int nId )
{
	guardfunc;
	m_nNpcSysId = nId;
	unguard;
}
void CUI_ID_FRAME_Storage::Refeash()
{
	guardfunc;
	if( !m_pID_FRAME_Storage )
		return;

	if(!IsVisable())
		return;

	m_pID_LISTIMG_Main->Clear();
	m_pID_LIST_city->Clear();
	m_pID_LIST_price->Clear();
	SCharStorageData* pStorageItem = NULL;
	pStorageItem = &thePlayerRole.m_stStorage;
	ControlList::S_List	stList;
	char szCount[Count_Char] = {0};
	char szPage[Count_Char] = {0};
    nPageCount=btStorageMaxPage;
    sprintf(szPage,"%d/%d",nPageCurr+1,nPageCount);
	m_pID_TEXT_Page->SetText(szPage);
	if(nPageCurr == 0)
	{
	   m_pID_BUTTON_Up->SetVisable(false);
	   m_pID_BUTTON_Up->SetEnable(false);
	   m_pID_BUTTON_Down->SetVisable(true);
	   m_pID_BUTTON_Down->SetEnable(true);	   
	}
	else if(nPageCurr == 2)
	{
	   m_pID_BUTTON_Down->SetVisable(false);
	   m_pID_BUTTON_Down->SetEnable(false);
	}
	else if(nPageCurr<2&&nPageCurr>0)
	{
	   m_pID_BUTTON_Up->SetVisable(true);
	   m_pID_BUTTON_Up->SetEnable(true);
	   m_pID_BUTTON_Down->SetVisable(true);
	   m_pID_BUTTON_Down->SetEnable(true);	   
	}

	short shValue = thePlayerRole.GetData(CPlayerRole::TYPE_Storage);
	if(shValue < PAGESIZE)
		shValue = PAGESIZE;

	//int nHeightCount = (shValue + m_pID_LISTIMG_Main->GetRowItemCnt() - 1) /
	//	m_pID_LISTIMG_Main->GetRowItemCnt();
	//m_pID_LISTIMG_Main->SetHeightMaxCnt(nHeightCount);
	//m_pID_LISTIMG_Main->SetHeightShowMaxCnt(nHeightCount > s_nHeightMaxShowCount ? s_nHeightMaxShowCount : nHeightCount);
	//m_pID_LISTIMG_Main->SetEnableCnt(thePlayerRole.GetData(CPlayerRole::TYPE_Storage));
	int nPos = m_pID_LISTIMG_Main->GetScrollValue();
	int nItemCount = 0;

	for( int n=0; n<shValue; n++)
	{
		if ( pStorageItem->stStorageItems[n + PAGESIZE*nPageCurr].itembaseinfo.ustItemID == InvalidLogicNumber )
		{//这里 增加list控件空项
			memset(szCount, 0, sizeof(char)*Count_Char);
			stList.SetData( szCount );
			m_pID_LIST_city->AddItem(&stList);
			m_pID_LIST_price->AddItem(&stList);
			continue;
		}
		//物品设置
		ControlIconDrag::S_ListImg stStorageItem;

		stStorageItem.SetData( &pStorageItem->stStorageItems[n + PAGESIZE*nPageCurr]);

		m_pID_LISTIMG_Main->SetItem( &stStorageItem, n );

		++nItemCount;

		//------取物品所花费用---------------
		//物品价值
		ItemDefine::SItemCommon *pItem = GettheItemDetail().GetItemByID(pStorageItem->stStorageItems[n + PAGESIZE*nPageCurr].itembaseinfo.ustItemID);
		if ( !pItem )
			return;

		float fValue = pItem->dwCost;
		//不同城市取物品所花费用
		float fCostOfDistance = thePlayerRole.fCostOfFetchItem[n + PAGESIZE*nPageCurr];
		float fGetItemCost;
		if(fCostOfDistance == 0)
		{
		    fGetItemCost = 0;
		}
		else
		{
			//计算取物品所花费用
			fGetItemCost =(fValue*fValue)/(StorageRulePara_A+StorageRulePara_B*fValue) + fCostOfDistance;
		}
		//物品单价
		int nUnitPrice;
		//取物品价格
		float fUnitPrice = fGetItemCost;
		nUnitPrice = (int)fUnitPrice;
		//物品城市名字
		sprintf(szCount, "%s", thePlayerRole.CityName[n + PAGESIZE*nPageCurr]);
		stList.SetData( szCount);
		m_pID_LIST_city->AddItem(&stList);

		sprintf(szCount, "%d", nUnitPrice);
		stList.SetData( szCount);
		m_pID_LIST_price->AddItem(&stList);
	}
	m_pID_LISTIMG_Main->SetScrollValue(nPos);

	//设置仓库数量
	char buf[64];
	sprintf(buf, "%d/%d", nItemCount, thePlayerRole.GetData(CPlayerRole::TYPE_Storage)); //实际物品/仓库格子数
	m_pID_TEXT_AllNum->SetText(buf);

    UpdateMoney();

	unguard;
}
void CUI_ID_FRAME_Storage::GetPageCout()
{
}

void CUI_ID_FRAME_Storage::UpdateMoney()
{
	if( !m_pID_FRAME_Storage )
		return;
    if( m_pID_TEXT_MONEY )
    {
        std::string strMoney;
        SCharStorageData* pStorageItem = &thePlayerRole.m_stStorage;

        thePlayerRole.GetGSCStringFromMoney(pStorageItem->dwStorageMoney, strMoney);
        ExpressionManager::GetInstance().AddExpressionAni(strMoney);

        *m_pID_TEXT_MONEY = strMoney;
    }
}

bool CUI_ID_FRAME_Storage::IsEqualTo_LISTIMG_Main(ControlObject* pObject)
{
	if( !m_pID_FRAME_Storage || !pObject )
		return false;

	return (m_pID_LISTIMG_Main == pObject);
}

int CUI_ID_FRAME_Storage::LISTIMG_Main_GetIndexByItem( ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Storage || !pItem )
		return -1;
	return m_pID_LISTIMG_Main->GetItemIndex(pItem);
}

bool CUI_ID_FRAME_Storage::ConfirmBoundCallback( char bPressYesButton, void* pData )
{
    if( bPressYesButton )
    {
        if( !pData )
            return true;

        MsgMoveStorageItem* pMsg = ( MsgMoveStorageItem* )pData;
        GettheNetworkInput().SendMsg( pMsg );

        bool bBound = ( thePlayerRole.m_stStorage.stStorageItems[pMsg->ustDstIndex].IsBounded()
            || thePlayerRole.m_stStorage.stStorageItems[pMsg->ustSrcIndex].IsBounded() );

        thePlayerRole.m_stStorage.stStorageItems[pMsg->ustDstIndex].SetBounded( bBound );
        thePlayerRole.m_stStorage.stStorageItems[pMsg->ustDstIndex].itembaseinfo.ustItemCount
            += thePlayerRole.m_stStorage.stStorageItems[pMsg->ustSrcIndex].itembaseinfo.ustItemCount;
        thePlayerRole.m_stStorage.stStorageItems[pMsg->ustSrcIndex].itembaseinfo.ustItemID = InvalidLogicNumber;

        thePlayerRole.fCostOfFetchItem[pMsg->ustSrcIndex] = 0;
        strcpy_s( thePlayerRole.CityName[pMsg->ustSrcIndex], MAX_NAME_STRING, "" );
        s_CUI_ID_FRAME_Storage.Refeash();
    }
    return true;
}

void  CUI_ID_FRAME_Storage::ChangeItemByIndex(int nIndex)
{

	int nTotal = thePlayerRole.GetData(CPlayerRole::TYPE_Storage) - nIndex * PAGESIZE;
	if(nTotal < 0)
		return;

	if(nPageCurr == nIndex)
		return;

	m_pID_CHECKBOX_Storage1->SetCheck(false);
	m_pID_CHECKBOX_Storage2->SetCheck(false);
	m_pID_CHECKBOX_Storage3->SetCheck(false);
	m_pID_CHECKBOX_Storage4->SetCheck(false);

	if(nIndex == 0)
		m_pID_CHECKBOX_Storage1->SetCheck(true);

	if(nIndex == 1)
		m_pID_CHECKBOX_Storage2->SetCheck(true);

	if(nIndex == 2)
		m_pID_CHECKBOX_Storage3->SetCheck(true);

	if(nIndex == 3)
		m_pID_CHECKBOX_Storage4->SetCheck(true);

	nPageCurr = nIndex;
	Refeash();
}

void  CUI_ID_FRAME_Storage::RefeshStorageState()
{
	short shNum = thePlayerRole.GetData(CPlayerRole::TYPE_Storage);
	int nCount = shNum/PAGESIZE;

	m_pID_CHECKBOX_Storage1->SetEnable(false);
	m_pID_CHECKBOX_Storage1->SetMsgHoldup(false);
	m_pID_CHECKBOX_Storage2->SetEnable(false);
	m_pID_CHECKBOX_Storage2->SetMsgHoldup(false);
	m_pID_CHECKBOX_Storage3->SetEnable(false);
	m_pID_CHECKBOX_Storage3->SetMsgHoldup(false);
	m_pID_CHECKBOX_Storage4->SetEnable(false);
	m_pID_CHECKBOX_Storage4->SetMsgHoldup(false);

	if(nCount > 0)
	{
		m_pID_CHECKBOX_Storage1->SetEnable(true);
	    m_pID_CHECKBOX_Storage1->SetMsgHoldup(true);
	}

	if(nCount > 1)
	{
		m_pID_CHECKBOX_Storage2->SetEnable(true);
	    m_pID_CHECKBOX_Storage2->SetMsgHoldup(true);
	}

	if(nCount > 2)
	{
		m_pID_CHECKBOX_Storage3->SetEnable(true);
	    m_pID_CHECKBOX_Storage3->SetMsgHoldup(true);
	}

	if(nCount > 3)
	{
		m_pID_CHECKBOX_Storage4->SetEnable(true);
	    m_pID_CHECKBOX_Storage4->SetMsgHoldup(true);
	}
}

void CUI_ID_FRAME_Storage::InitStorageState()
{
	nPageCurr = 0;
	if(!m_pID_FRAME_Storage)
		return;

	m_pID_CHECKBOX_Storage1->SetCheck(true);
	m_pID_CHECKBOX_Storage2->SetCheck(false);
	m_pID_CHECKBOX_Storage3->SetCheck(false);
	m_pID_CHECKBOX_Storage4->SetCheck(false);
}