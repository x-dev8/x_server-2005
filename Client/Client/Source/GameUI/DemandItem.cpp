/********************************************************************
Created by UIEditor.exe
FileName: E:\Document\package\DemandItem.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "DemandItem.h"
//#include "UIMgr.h"
#include "MessageDefine.h"
#include "NetworkInput.h"
#include "ItemDetail.h"
#include "IconManagerClient.h"
#include "Common.h"
#include "AutoAttackSet.h"

#define DemandItemDisplayMax   5       // 最多显示5个

DemandItemFrameMgr DemandItemFrameManage;
MAP_FRAME_RUN_INDEX( DemandItemFrameManage, OnFrameRunIndexedFrame )
MAP_FRAME_RENDER_INDEX( DemandItemFrameManage, OnFrameRenderIndexedFrame )
MAP_BUTTON_CLICK_CALLBACK( DemandItemFrameManage, ID_BUTTON_CloseOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( DemandItemFrameManage, ID_BUTTON_DemandOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( DemandItemFrameManage, ID_LISTIMG_ItemOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( DemandItemFrameManage, ID_LISTIMG_ItemOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( DemandItemFrameManage, ID_LISTIMG_ItemOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( DemandItemFrameManage, ID_LISTIMG_ItemOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( DemandItemFrameManage, ID_BUTTON_GiveUpOnButtonClick )
CUI_ID_FRAME_DemandItem::CUI_ID_FRAME_DemandItem(int frameIndex)
{
	// Member
	m_pID_FRAME_DemandItem = NULL;
	m_pID_BUTTON_Close = NULL;
	m_pID_BUTTON_Demand = NULL;
	m_pID_TEXT_Name = NULL;
	m_pID_LISTIMG_Item = NULL;
	m_pID_PICTURE_9017 = NULL;
	m_pID_PROGRESS = NULL;
	m_pID_BUTTON_GiveUp = NULL;

	m_FrameIndex			= frameIndex;
	MeSprintf_s(szFrameID,sizeof(szFrameID)-1,"%s%d",ID_FRAME_DemandItem,frameIndex);

	m_dwStartCountDownTime  = 0;
	m_dwEndCountDownTime    = 0;
	m_nItemPackageID        = -1;
}
// Frame
bool CUI_ID_FRAME_DemandItem::OnFrameRun()
{
	if( !IsVisable() )
		return true;

	//zhuxincong 8.25 更新倒计时
	DWORD dwCurrentTime = HQ_TimeGetTime();
	//zhuxincong 判断是否在挂机，是否 点击需求所以物品，当出现界面后，一秒后点击自动需求 lyh++ 自动挂机为全部需求
	if (dwCurrentTime - m_dwStartCountDownTime > 1000 && s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight()
		/*&& s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsTeamFlag(Team_NeedItem)*/) //并且点击了全部需求则需求 ，没有点的话 不执自动拾取操作，并全部放弃
	{
		// 一秒后自动点需求 (自动挂机中的操作) 勾选自动拾取 则全部拾取，否则全部放弃。
		// 判断背包是否已经满了  满了的话 全部放弃
		ControlIconDrag::S_ListImg* pItem = m_pID_LISTIMG_Item->GetItemByIndex(0);
		if(pItem)
		{
			//m_vctDemandItemData
			CItemBag2* pBag=NULL;
			ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID(pItem->m_pkIconInfo->GetItemId());
			SCharItem* pCharItem = (SCharItem*)pItem->m_pkIconInfo->GetData();
			if(!pItemDetail || !pCharItem)
			{
				ID_BUTTON_CloseOnButtonClick(NULL);
			}
			switch(thePlayerRole.GetBagTypeByItemType(pItemDetail->ucItemType))
			{
			case BT_NormalItemBag:
				pBag=&thePlayerRole.m_bag;
				break;
			case BT_MaterialBag:
				pBag=&thePlayerRole.m_bagMaterial;
				break;
			case BT_TaskBag:
				pBag=&thePlayerRole.m_bagTask;
				break;
			}
			bool IsNeedPos = false;
			if(pBag && pBag->CanPushItem(*pCharItem,IsNeedPos) && s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsPickFlag(Pick_All))
			{
				ID_BUTTON_DemandOnButtonClick(NULL); 
			}
			else
			{
				ID_BUTTON_CloseOnButtonClick(NULL);
			}
		}
		/*if (s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsPickFlag(Pick_All))
		{
			ID_BUTTON_DemandOnButtonClick(NULL); 
		}
		else
		{
			ID_BUTTON_CloseOnButtonClick(NULL);
		}*/
		
	}
	else if( dwCurrentTime >= m_dwEndCountDownTime )
	{
		// 已超时则关闭UI
		ID_BUTTON_CloseOnButtonClick(NULL);
	}
	else
		m_pID_PROGRESS->SetValue((int)((m_dwEndCountDownTime-dwCurrentTime)*1.f/(m_dwEndCountDownTime-m_dwStartCountDownTime) * 1000));
	return true;
}
bool CUI_ID_FRAME_DemandItem::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_DemandItem::ID_BUTTON_CloseOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_DemandItem)
	{
		assert(false&&"ui error");
		return false;
	}
	// 放弃
	ControlIconDrag::S_ListImg* pItem = m_pID_LISTIMG_Item->GetItemByIndex(0);
	if( pItem )
	{
		MsgPackageItemBoultAck kRollMsg;
		kRollMsg.nItemPackageID = m_nItemPackageID;
		kRollMsg.nItemID = pItem->m_pkIconInfo->GetOnlyId();
		kRollMsg.nResult = MsgPackageItemBoultAck::Boult_Abandon;
		GettheNetworkInput().SendMsg( &kRollMsg );
	}

	// 关闭UI
	SetVisable(false);

	return true;
}
// Button
bool CUI_ID_FRAME_DemandItem::ID_BUTTON_DemandOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_DemandItem)
	{
		assert(false&&"ui error");
		return false;
	}
	// 掷骰子
	ControlIconDrag::S_ListImg* pItem = m_pID_LISTIMG_Item->GetItemByIndex(0);
	if( pItem )
	{
		MsgPackageItemBoultAck kRollMsg;
		kRollMsg.nItemPackageID = m_nItemPackageID;
		kRollMsg.nItemID = pItem->m_pkIconInfo->GetOnlyId();
		kRollMsg.nResult = MsgPackageItemBoultAck::Boult_Choose;
		GettheNetworkInput().SendMsg( &kRollMsg );
	}
	// 关闭UI
	SetVisable(false);

	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_DemandItem::ID_LISTIMG_ItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														  ControlIconDrag::S_ListImg* pItemDrag,
														  ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_DemandItem::ID_LISTIMG_ItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_DemandItem::ID_LISTIMG_ItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_DemandItem::ID_LISTIMG_ItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// Button
bool CUI_ID_FRAME_DemandItem::ID_BUTTON_GiveUpOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_DemandItem)
	{
		assert(false&&"ui error");
		return false;
	}

	ID_BUTTON_CloseOnButtonClick(pSender);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_DemandItem::_LoadUI()
{
	m_pObject = theUiManager.AddFrameByIndex( "Data\\UI\\DemandItem.MEUI" ,m_FrameIndex,true);
	if ( m_pObject == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\DemandItem.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_DemandItem::DoControlConnect()
{
	theUiManager.OnFrameRunIndexedFrame( szFrameID, DemandItemFrameManageOnFrameRunIndexedFrame );
	theUiManager.OnFrameRenderIndexedFrame( szFrameID, DemandItemFrameManageOnFrameRenderIndexedFrame );
	theUiManager.OnButtonClick( szFrameID, ID_BUTTON_Close, DemandItemFrameManageID_BUTTON_CloseOnButtonClick );
	theUiManager.OnButtonClick( szFrameID, ID_BUTTON_Demand, DemandItemFrameManageID_BUTTON_DemandOnButtonClick );
	theUiManager.OnIconDragOn( szFrameID, ID_LISTIMG_Item, DemandItemFrameManageID_LISTIMG_ItemOnIconDragOn );
	theUiManager.OnIconLDBClick( szFrameID, ID_LISTIMG_Item, DemandItemFrameManageID_LISTIMG_ItemOnIconLDBClick );
	theUiManager.OnIconButtonClick( szFrameID, ID_LISTIMG_Item, DemandItemFrameManageID_LISTIMG_ItemOnIconButtonClick );
	theUiManager.OnIconRButtonUp( szFrameID, ID_LISTIMG_Item, DemandItemFrameManageID_LISTIMG_ItemOnIconRButtonUp );
	theUiManager.OnButtonClick( szFrameID, ID_BUTTON_GiveUp, DemandItemFrameManageID_BUTTON_GiveUpOnButtonClick );

	m_pID_FRAME_DemandItem = (ControlFrame*)theUiManager.FindFrame( szFrameID );
	m_pID_BUTTON_Close = (ControlButton*)theUiManager.FindControl( szFrameID, ID_BUTTON_Close );
	m_pID_BUTTON_Demand = (ControlButton*)theUiManager.FindControl( szFrameID, ID_BUTTON_Demand );
	m_pID_TEXT_Name = (ControlText*)theUiManager.FindControl( szFrameID, ID_TEXT_Name );
	m_pID_LISTIMG_Item = (ControlListImage*)theUiManager.FindControl( szFrameID, ID_LISTIMG_Item );
	m_pID_PICTURE_9017 = (ControlPicture*)theUiManager.FindControl( szFrameID, ID_PICTURE_9017 );
	m_pID_PROGRESS = (ControlProgress*)theUiManager.FindControl( szFrameID, ID_PROGRESS_27816 );
	m_pID_BUTTON_GiveUp = (ControlButton*)theUiManager.FindControl( szFrameID, ID_BUTTON_GiveUp );
	assert( m_pID_FRAME_DemandItem );
	assert( m_pID_BUTTON_Close );
	assert( m_pID_BUTTON_Demand );
	assert( m_pID_TEXT_Name );
	assert( m_pID_LISTIMG_Item );
	assert( m_pID_PICTURE_9017 );
	assert( m_pID_PROGRESS );
	assert( m_pID_BUTTON_GiveUp );
	int YPos = 550;
	m_pID_FRAME_DemandItem->SetYPos(YPos-m_FrameIndex*100);

	//USE_SCRIPT( eUI_OBJECT_DemandItem, this );

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_DemandItem::_UnLoadUI()
{
	if (NULL == m_pID_FRAME_DemandItem)
	{
		return true;
	}
	//CLOSE_SCRIPT( eUI_OBJECT_DemandItem );
	m_pID_LISTIMG_Item->Clear();
	m_pID_FRAME_DemandItem = NULL;
	m_pID_BUTTON_Close = NULL;
	m_pID_BUTTON_Demand = NULL;
	m_pID_TEXT_Name = NULL;
	m_pID_LISTIMG_Item = NULL;
	m_pID_PICTURE_9017 = NULL;
	m_pID_PROGRESS = NULL;
	m_pID_BUTTON_GiveUp = NULL;
	return theUiManager.RemoveFrame( m_pObject );
}
// 是否可视
bool CUI_ID_FRAME_DemandItem::_IsVisable()
{
	if( !m_pID_FRAME_DemandItem )
		return false;
	return m_pID_FRAME_DemandItem->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_DemandItem::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_DemandItem )
		return;
	m_pID_FRAME_DemandItem->SetVisable( bVisable );
	if( !bVisable )
	{
		DemandItemFrameManage.RemoveDemandItem(this);
	}
}

// 添加物品并显示
void CUI_ID_FRAME_DemandItem::AddItem( int nItemPackageID, SCharItem& kCharItem, DWORD dwStart, DWORD dwEnd )
{
	// 已超时
	if( dwStart >= dwEnd )
		return;

	if( !m_pID_FRAME_DemandItem )
		return;

	m_pID_LISTIMG_Item->Clear();
	ControlIconDrag::S_ListImg stItem;
	stItem.SetData( &kCharItem );
	m_pID_LISTIMG_Item->SetItem( &stItem, 0 );
	ItemDefine::SItemCommon *pItemCommon =GettheItemDetail().GetItemByID(kCharItem.itembaseinfo.ustItemID);
	if( pItemCommon )
	{
		DWORD color = S_IconInfoHero::GetQualityColor( pItemCommon->ustLevel );
		m_pID_TEXT_Name->SetText(pItemCommon->GetItemName(), color);
	}
	else
		m_pID_TEXT_Name->SetText("");

	// 设置倒计时进度条
	m_dwStartCountDownTime = dwStart;
	m_dwEndCountDownTime = dwEnd;
	m_nItemPackageID = nItemPackageID;

	DWORD dwCurrentTime = HQ_TimeGetTime();
	m_pID_PROGRESS->SetValue((m_dwEndCountDownTime-dwCurrentTime)*1000/(m_dwEndCountDownTime-m_dwStartCountDownTime));

	SetVisable(true);
}

ControlIconDrag::S_ListImg* CUI_ID_FRAME_DemandItem::GetItemByIndex( int i )
{
	if(m_pID_LISTIMG_Item)
		return m_pID_LISTIMG_Item->GetItemByIndex(i);
	else
		assert(false&&"ui error");

	return NULL;
}
///////////////////////////////////////////////////////////////////////////
DemandItemFrameMgr::DemandItemFrameMgr()
{
	Reset();
}

DemandItemFrameMgr::~DemandItemFrameMgr()
{
}

bool DemandItemFrameMgr::OnFrameRunIndexedFrame( int index )
{
	assert(mDemandItemArr.size() > index);
    if( index < 0 || mDemandItemArr.size() <= index )
    {
        return false;
    }
	return mDemandItemArr[index]->OnFrameRun();
}

bool DemandItemFrameMgr::OnFrameRenderIndexedFrame( int index )
{
	assert(mDemandItemArr.size() > index);
    if( index < 0 || mDemandItemArr.size() <= index )
    {
        return false;
    }
	return mDemandItemArr[index]->OnFrameRender();
}

bool DemandItemFrameMgr::ID_BUTTON_CloseOnButtonClick( ControlObject* pSender )
{
	m_ActiveIndex = GetFrameIndexByChildWidget(pSender);
    if( m_ActiveIndex < 0 || mDemandItemArr.size() <= m_ActiveIndex )
    {
        return false;
    }
	return mDemandItemArr[m_ActiveIndex]->ID_BUTTON_CloseOnButtonClick(pSender);
}

bool DemandItemFrameMgr::ID_BUTTON_DemandOnButtonClick( ControlObject* pSender )
{
	m_ActiveIndex = GetFrameIndexByChildWidget(pSender);
    if( m_ActiveIndex < 0 || mDemandItemArr.size() <= m_ActiveIndex )
    {
        return false;
    }
	return mDemandItemArr[m_ActiveIndex]->ID_BUTTON_DemandOnButtonClick(pSender);
}

bool DemandItemFrameMgr::ID_LISTIMG_ItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc )
{
	m_ActiveIndex = GetFrameIndexByChildWidget(pSender);
    if( m_ActiveIndex < 0 || mDemandItemArr.size() <= m_ActiveIndex )
    {
        return false;
    }
	return mDemandItemArr[m_ActiveIndex]->ID_LISTIMG_ItemOnIconDragOn(pSender,pMe,pItemDrag,pItemSrc);
}

bool DemandItemFrameMgr::ID_LISTIMG_ItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	m_ActiveIndex = GetFrameIndexByChildWidget(pSender);
    if( m_ActiveIndex < 0 || mDemandItemArr.size() <= m_ActiveIndex )
    {
        return false;
    }
	return mDemandItemArr[m_ActiveIndex]->ID_LISTIMG_ItemOnIconLDBClick(pSender,pItem);
}

bool DemandItemFrameMgr::ID_LISTIMG_ItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    m_ActiveIndex = GetFrameIndexByChildWidget(pSender);
    if( m_ActiveIndex < 0 || mDemandItemArr.size() <= m_ActiveIndex )
    {
        return false;
    }
	return mDemandItemArr[m_ActiveIndex]->ID_LISTIMG_ItemOnIconButtonClick(pSender,pItem);
}

bool DemandItemFrameMgr::ID_LISTIMG_ItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    m_ActiveIndex = GetFrameIndexByChildWidget(pSender);
    if( m_ActiveIndex < 0 || mDemandItemArr.size() <= m_ActiveIndex )
    {
        return false;
    }
	return mDemandItemArr[m_ActiveIndex]->ID_LISTIMG_ItemOnIconRButtonUp(pSender,pItem);
}

int DemandItemFrameMgr::GetFrameIndexByChildWidget( ControlObject* pSender )
{
	ControlObject* pFrame = pSender;
	while(pFrame->GetControlType() != Type_Frame)
	{
		pFrame = pFrame->GetFather();
	}
	assert(pFrame);
	ControlFrame* pConFrame = (ControlFrame*) pFrame;
	return pConFrame->GetIndex();
}

void DemandItemFrameMgr::Reset()
{
	for (int i = 0; i < mDemandItemArr.size();++i)
	{
		mDemandItemArr[i]->UnLoadUI();
		delete mDemandItemArr[i];
	}
	m_ActiveIndex = -1;
	mDemandItemArr.clear();
	m_vctDemandItemData.clear();
	m_vctItemWaitResult.clear();
}

void DemandItemFrameMgr::SetVisable( const bool bVisable )
{
	for (int i = 0; i < mDemandItemArr.size(); ++i)
	{
		mDemandItemArr[i]->SetVisable(bVisable);
	}
}

CUI_ID_FRAME_DemandItem* DemandItemFrameMgr::GetDemandItemByIndex( int index )
{
	if (index < 0 || index >= mDemandItemArr.size())
	{
		return NULL;
	}
	return mDemandItemArr[index];
}

CUI_ID_FRAME_DemandItem* DemandItemFrameMgr::GetDemandItemByChildWidget( ControlObject* pSender )
{
	ControlObject* pFrame = pSender;
	while(pFrame->GetControlType() != Type_Frame)
	{
		pFrame = pFrame->GetFather();
	}
	assert(pFrame);
	ControlFrame* pTemp = (ControlFrame*)pSender;
	m_ActiveIndex = pTemp->GetIndex();
	assert(m_ActiveIndex != -1);
	return GetDemandItemByIndex(m_ActiveIndex);
}

CUI_ID_FRAME_DemandItem* DemandItemFrameMgr::GetActiveTeamFrame()
{
	if (m_ActiveIndex < 0 || m_ActiveIndex >= mDemandItemArr.size())
	{
		return NULL;
	}
	return mDemandItemArr[m_ActiveIndex];
}

CUI_ID_FRAME_DemandItem* DemandItemFrameMgr::CreateFrame( int index )
{
	assert(index == mDemandItemArr.size());
	CUI_ID_FRAME_DemandItem* pNew = MeNew CUI_ID_FRAME_DemandItem(index);
	pNew->LoadUI();
	mDemandItemArr.push_back(pNew);
	m_ActiveIndex = index;
	return pNew;
}

bool DemandItemFrameMgr::AddDemandItem( int nPackageID, const SCharItem& kCharItem, int iCountDown )
{
	// 添加到m_vctDemandItemData
	DemandItemData kDemandItem;
	memcpy(&kDemandItem.kItem, &kCharItem, sizeof(SCharItem));
	kDemandItem.dwStartCountDownTime = HQ_TimeGetTime();
	kDemandItem.dwEndCountDownTime = kDemandItem.dwStartCountDownTime + iCountDown;
	kDemandItem.nItemPackageID = nPackageID;
	kDemandItem.bDisplay = false;

	// UI显示
	int iDemandItemNum = min( mDemandItemArr.size(), DemandItemDisplayMax );
	// 获取可用的CUI_ID_FRAME_DemandItem
	CUI_ID_FRAME_DemandItem* pDemandItemFrameAvailable = NULL;
	for( int iDemand=0; iDemand<iDemandItemNum; ++iDemand )
	{
		CUI_ID_FRAME_DemandItem* pDemandItemFrame = GetDemandItemByIndex(iDemand);
		if( !pDemandItemFrame->IsVisable() )
		{
			pDemandItemFrameAvailable = pDemandItemFrame;
			break;
		}
	}
	if( !pDemandItemFrameAvailable && iDemandItemNum < DemandItemDisplayMax)
	{
		// 创建新的CUI_ID_FRAME_DemandItem
		CUI_ID_FRAME_DemandItem* pDemandItemFrame = CreateFrame(iDemandItemNum);
		if( pDemandItemFrame )
			pDemandItemFrameAvailable = pDemandItemFrame;
	}
	// 有可用CUI_ID_FRAME_DemandItem
	if( pDemandItemFrameAvailable )
	{
		pDemandItemFrameAvailable->AddItem(nPackageID, kDemandItem.kItem, kDemandItem.dwStartCountDownTime, kDemandItem.dwEndCountDownTime);
		kDemandItem.bDisplay = true;
	}

	m_vctDemandItemData.push_back(kDemandItem);

	return true;
}

bool DemandItemFrameMgr::RemoveDemandItem( CUI_ID_FRAME_DemandItem* pRemoveDemandItem )
{
	if( mDemandItemArr.size() )
	{
		// 查找删除的Frame的物品ID
		__int64 nItemOnlyInt = 0;
		std::vector<CUI_ID_FRAME_DemandItem*>::iterator iter;
		for( iter = mDemandItemArr.begin(); iter != mDemandItemArr.end(); ++iter )
		{
			CUI_ID_FRAME_DemandItem* pDemandItem = *iter;
			if( pDemandItem == pRemoveDemandItem )
			{
				ControlIconDrag::S_ListImg* pItem = pRemoveDemandItem->GetItemByIndex(0);
				nItemOnlyInt = pItem->m_pkIconInfo->GetOnlyId();
				break;
			}
		}
		// 从m_vctDemandItemData表移除，加入m_vctItemWaitResult，用于收到Roll结果时显示物品名称用
		if( m_vctDemandItemData.size() && nItemOnlyInt > 0 )
		{
			std::vector<DemandItemData>::iterator iter;
			for(iter = m_vctDemandItemData.begin(); iter != m_vctDemandItemData.end(); ++iter)
			{
				DemandItemData* pItemData = (DemandItemData*)(&(*iter));
				if( pItemData->kItem.itembaseinfo.nOnlyInt == nItemOnlyInt )
				{
					SCharItem kItemBackup;
					memcpy(&kItemBackup, &pItemData->kItem, sizeof(SCharItem));
					m_vctItemWaitResult.push_back(kItemBackup);
					m_vctDemandItemData.erase(iter);
					break;
				}
			}
		}
		// 判断队列中是否还有没显示的
		for( int iItemData=0; iItemData<m_vctDemandItemData.size(); ++iItemData)
		{
			if( !m_vctDemandItemData[iItemData].bDisplay )
			{
				if( HQ_TimeGetTime() < m_vctDemandItemData[iItemData].dwEndCountDownTime )
				{
					pRemoveDemandItem->AddItem(m_vctDemandItemData[iItemData].nItemPackageID, m_vctDemandItemData[iItemData].kItem, m_vctDemandItemData[iItemData].dwStartCountDownTime, m_vctDemandItemData[iItemData].dwEndCountDownTime);
					m_vctDemandItemData[iItemData].bDisplay = true;
					break;
				}
			}
		}
	}

	return true;
}

bool DemandItemFrameMgr::IsVisable()
{
	if( mDemandItemArr.size() )
	{
		for(size_t iItem=0; iItem < mDemandItemArr.size(); ++iItem)
		{
			if( mDemandItemArr[iItem]->IsVisable() )
				return true;
		}
	}
	return false;
}

SCharItem* DemandItemFrameMgr::GetItemInResultList( __int64 nItemID )
{
	if( m_vctItemWaitResult.size() )
	{
		for(size_t iItem=0; iItem < m_vctItemWaitResult.size(); ++iItem)
		{
			if( m_vctItemWaitResult[iItem].itembaseinfo.nOnlyInt == nItemID )
				return &m_vctItemWaitResult[iItem];
		}
	}
	return NULL;
}

void DemandItemFrameMgr::RemoveItemInResultList( __int64 nItemID )
{
	if( !m_vctItemWaitResult.empty() )
	{
		for(std::vector<SCharItem>::iterator iter=m_vctItemWaitResult.begin(); iter != m_vctItemWaitResult.end(); ++iter)
		{
			SCharItem* pItem = (SCharItem*)(&*iter);
			if( pItem->itembaseinfo.nOnlyInt == nItemID )
			{
				m_vctItemWaitResult.erase(iter);
				return;
			}
		}
	}
}

void DemandItemFrameMgr::Update()
{
	// 未显示的数据更新倒计时
	DWORD dwCurrentTime = HQ_TimeGetTime();
	std::vector<DemandItemData>::iterator iter;
	for(iter = m_vctDemandItemData.begin(); iter != m_vctDemandItemData.end();)
	{
		DemandItemData* pItemData = (DemandItemData*)(&(*iter));
		if( !pItemData->bDisplay && dwCurrentTime >= pItemData->dwEndCountDownTime )
		{
			// 已超时
			MsgPackageItemBoultAck kRollMsg;
			kRollMsg.nItemPackageID = pItemData->nItemPackageID;
			kRollMsg.nItemID = pItemData->kItem.itembaseinfo.nOnlyInt;
			kRollMsg.nResult = MsgPackageItemBoultAck::Boult_Abandon;
			GettheNetworkInput().SendMsg( &kRollMsg );

			// 从表里删除
			iter = m_vctDemandItemData.erase(iter);
			continue;
		}
		++iter;
	}
}

bool DemandItemFrameMgr::ID_BUTTON_GiveUpOnButtonClick( ControlObject* pSender )
{
	m_ActiveIndex = GetFrameIndexByChildWidget(pSender);
    if( m_ActiveIndex < 0 || m_ActiveIndex >= mDemandItemArr.size() )
    {
        return false;
    }
	return mDemandItemArr[m_ActiveIndex]->ID_BUTTON_GiveUpOnButtonClick(pSender);
}

