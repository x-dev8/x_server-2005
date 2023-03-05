/********************************************************************
Created by UIEditor.exe
FileName: E:\Document\package\PickUp.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "PickUp.h"
#include "ItemDetail.h"
#include "MessageDefine.h"
#include "UIMgr.h"
#include "NetworkInput.h"
#include "XmlStringLanguage.h"
#include "color_config.h"
#include "PlayerRole.h"
#include "GameMain.h"
#include "shortcutkey_configure.h"
#include "PlayerMgr.h"
#include "IconManagerClient.h"
#include "ScreenInfoManager.h"


#define ITEM_NUM_PER_PAGE   4
extern CPlayerRole	thePlayerRole;
extern GAME_STATE	g_GameState;

CUI_ID_FRAME_PickUp s_CUI_ID_FRAME_PickUp;
MAP_FRAME_RUN( s_CUI_ID_FRAME_PickUp, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_PickUp, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PickUp, ID_BUTTON_Item1OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PickUp, ID_BUTTON_Item2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PickUp, ID_BUTTON_Item3OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PickUp, ID_BUTTON_Item4OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PickUp, ID_BUTTON_CloseOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PickUp, ID_BUTTON_PickAllOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PickUp, ID_BUTTON_PageupOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PickUp, ID_BUTTON_PagedownOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_PickUp, ID_LISTIMG_ItemOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_PickUp, ID_LISTIMG_ItemOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PickUp, ID_LISTIMG_ItemOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_PickUp, ID_LISTIMG_ItemOnIconRButtonUp )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_PickUp, ID_LIST_MemberListOnListSelectChange )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_PickUp, ID_LISTIMG_Item2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_PickUp, ID_LISTIMG_Item2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PickUp, ID_LISTIMG_Item2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_PickUp, ID_LISTIMG_Item2OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_PickUp, ID_LISTIMG_Item3OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_PickUp, ID_LISTIMG_Item3OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PickUp, ID_LISTIMG_Item3OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_PickUp, ID_LISTIMG_Item3OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_PickUp, ID_LISTIMG_Item4OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_PickUp, ID_LISTIMG_Item4OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PickUp, ID_LISTIMG_Item4OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_PickUp, ID_LISTIMG_Item4OnIconRButtonUp )
CUI_ID_FRAME_PickUp::CUI_ID_FRAME_PickUp()
{
	// Member
	ResetMembers();
}
void CUI_ID_FRAME_PickUp::ResetMembers()
{
	m_pID_FRAME_PickUp = NULL;
	//m_pID_PICTURE_Wall = NULL;
	m_pID_BUTTON_Item1 = NULL;
	m_pID_BUTTON_Item2 = NULL;
	m_pID_BUTTON_Item3 = NULL;
	m_pID_BUTTON_Item4 = NULL;
	m_pID_BUTTON_Close = NULL;
	m_pID_BUTTON_PickAll = NULL;
	m_pID_TEXT_Name1 = NULL;
	m_pID_TEXT_Name2 = NULL;
	m_pID_TEXT_Name3 = NULL;
	m_pID_TEXT_Name4 = NULL;
	m_pID_TEXT_Page = NULL;
	m_pID_BUTTON_Pageup = NULL;
	m_pID_BUTTON_Pagedown = NULL;
	m_pID_LISTIMG_Item = NULL;
	m_pID_PICTURE_MemberList = NULL;
	m_pID_LIST_MemberList = NULL;
	m_pID_LISTIMG_Item2 = NULL;
	m_pID_LISTIMG_Item3 = NULL;
	m_pID_LISTIMG_Item4 = NULL;

}
// Frame
bool CUI_ID_FRAME_PickUp::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_PickUp::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_PickUp::ID_BUTTON_Item1OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PickUp )
		return false;
    int iItem = sCurrentPage*sItemNumPerPage;
    if( kLootItemList[iItem].bHasItem )
    {
		if (SinglePlayerTeamPickUpItem(iItem))
		{
			return true;
		}
        if( kLootItemList[iItem].bNeedLeadAssign && thePlayerRole.IsTeamHeader() )
        {
            ShowAssignMemberList();
            nCurrentSelectItem = 0;
        }
        else if( kLootItemList[iItem].bCanLoot )
        {
            PickOneItem( kLootItemList[iItem].kItem );
        }
        else
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PickUp, theXmlString.GetString( eText_PackagePickUp_CannotPick ) );
        }
    }
	return true;
}
// Button
bool CUI_ID_FRAME_PickUp::ID_BUTTON_Item2OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PickUp )
		return false;
    int iItem = sCurrentPage*sItemNumPerPage + 1;
    if( kLootItemList[iItem].bHasItem )
    {
		if (SinglePlayerTeamPickUpItem(iItem))
		{
			return true;
		}

        if( kLootItemList[iItem].bNeedLeadAssign && thePlayerRole.IsTeamHeader() )
        {
            ShowAssignMemberList();
            nCurrentSelectItem = 1;
        }
        else if( kLootItemList[iItem].bCanLoot )
        {
            PickOneItem( kLootItemList[iItem].kItem );
        }
        else
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PickUp, theXmlString.GetString( eText_PackagePickUp_CannotPick ) );
        }
    }
	return true;
}
// Button
bool CUI_ID_FRAME_PickUp::ID_BUTTON_Item3OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PickUp )
		return false;
    int iItem = sCurrentPage*sItemNumPerPage + 2;
    if( kLootItemList[iItem].bHasItem )
    {
		if (SinglePlayerTeamPickUpItem(iItem))
		{
			return true;
		}

        if( kLootItemList[iItem].bNeedLeadAssign && thePlayerRole.IsTeamHeader() )
        {
            ShowAssignMemberList();
            nCurrentSelectItem = 2;
        }
        else if( kLootItemList[iItem].bCanLoot )
        {
            PickOneItem( kLootItemList[iItem].kItem );
        }
        else
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PickUp, theXmlString.GetString( eText_PackagePickUp_CannotPick ) );
        }
    }
    return true;
}

bool CUI_ID_FRAME_PickUp::SinglePlayerTeamPickUpItem(int iItem)
{
	//lyh++  解决在队伍分配的时候，单击掉落包中的需要分配的时候，提示该物品不属与你
	if(thePlayerRole.m_TeamData.size() == 1 )
	{
		TeamInfo* pInfo = &(thePlayerRole.m_TeamData[0]);
		extern CHeroGame theHeroGame;
		if ( strcmp(pInfo->szName.c_str() , thePlayerRole.GetName()) == 0 )
		{
			PickOneItem( kLootItemList[iItem].kItem );
			return true;
		}


	}

	return false;
}
// Button
bool CUI_ID_FRAME_PickUp::ID_BUTTON_Item4OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PickUp )
		return false;
    int iItem = sCurrentPage*sItemNumPerPage + 3;
    if( kLootItemList[iItem].bHasItem )
    {
        if (SinglePlayerTeamPickUpItem(iItem))
        {
			return true;
        }
		


        // 判断物品是否需要分配
        if( kLootItemList[iItem].bNeedLeadAssign && thePlayerRole.IsTeamHeader() )
        {
            ShowAssignMemberList();
            nCurrentSelectItem = 3;
        }
        else if( kLootItemList[iItem].bCanLoot )
        {
            PickOneItem( kLootItemList[iItem].kItem );
        }
        else
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PickUp, theXmlString.GetString( eText_PackagePickUp_CannotPick ) );
        }
    }
	return true;
}
// Button
bool CUI_ID_FRAME_PickUp::ID_BUTTON_CloseOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PickUp )
		return false;
    if( bNeedSendCloseMsg )
    {
        MsgPackageViewEnd kCloseMsg;
        kCloseMsg.nItemPackageID = nItemPackageID;
        GettheNetworkInput().SendMsg( &kCloseMsg );
    }
	if( theHeroGame.GetPlayerMgr() && theHeroGame.GetPlayerMgr()->GetLockPlayerID() > -1 )
	{
		if( theHeroGame.GetPlayerMgr()->GetLockPlayerID() == nItemPackageID )
			theHeroGame.GetPlayerMgr()->SetLockPlayerID(-1);
	}
    SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_PickUp::ID_BUTTON_PickAllOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PickUp )
		return false;
    MsgPickPackageItemReq kPickMsg;
    kPickMsg.nItemPackageID = nItemPackageID;
    kPickMsg.bAllPick = true;
    GettheNetworkInput().SendMsg( &kPickMsg );
	return true;
}
// Button
bool CUI_ID_FRAME_PickUp::ID_BUTTON_PageupOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PickUp )
		return false;
    if( sItemNumPerPage > 0 && sCurrentPage > 0 )
    {
        // 下一页物品起始下标
        int iItemNumBegin = (sCurrentPage-1)*sItemNumPerPage;
        // 下一页显示的物品个数
        int iItemNumCurrentPage = sItemNumPerPage;
        ClearItemList();

        for(int iItem = 0; iItem < iItemNumCurrentPage; ++iItem)
        {
            if( !kLootItemList[iItem+iItemNumBegin].bHasItem )
                continue;
            // 有物品
            SetItem( kLootItemList[iItem+iItemNumBegin].kItem, iItem );
        }
        sCurrentPage--;

        // Pageup按钮是否可见
        if( sCurrentPage > 0 )
            m_pID_BUTTON_Pageup->SetVisable(true);
        else
            m_pID_BUTTON_Pageup->SetVisable(false);

        // 重新计算页数
        sTotalPage = CalculateTotalPage(sCurrentPage, sItemNumPerPage);
        // Pagedown按钮是否可见
        if( sCurrentPage + 1 >= sTotalPage )
            m_pID_BUTTON_Pagedown->SetVisable(false);
        else
            m_pID_BUTTON_Pagedown->SetVisable(true);
        if( sTotalPage > 1 )
        {
            // 显示页数
            char szPage[MAX_PATH] = {0};
            sprintf(szPage, "%d/%d", sCurrentPage+1, sTotalPage);
            m_pID_TEXT_Page->SetText(szPage);
        }
        else
            m_pID_TEXT_Page->Clear();
    }
	return true;
}
// Button
bool CUI_ID_FRAME_PickUp::ID_BUTTON_PagedownOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PickUp )
		return false;
    if( sItemNumPerPage > 0 && sCurrentPage + 1 < sTotalPage)
    {
        // 下一页物品起始下标
        int iItemNumBegin = (sCurrentPage+1)*sItemNumPerPage;
        // 下一页显示的物品个数
        int iItemNumCurrentPage = min(sItemCount-iItemNumBegin, sItemNumPerPage);
        ClearItemList();

        for(int iItem = 0; iItem < iItemNumCurrentPage; ++iItem)
        {
            if( !kLootItemList[iItem+iItemNumBegin].bHasItem )
                continue;
            // 有物品
            SetItem( kLootItemList[iItem+iItemNumBegin].kItem, iItem );
        }
        sCurrentPage++;
        if( sTotalPage > 1 )
        {
            // 显示页数
            char szPage[MAX_PATH] = {0};
            sprintf(szPage, "%d/%d", sCurrentPage+1, sTotalPage);
            m_pID_TEXT_Page->SetText(szPage);
        }
        else
            m_pID_TEXT_Page->Clear();

        m_pID_BUTTON_Pageup->SetVisable(true);

        // Pagedown按钮是否可见
        if( sCurrentPage + 1 >= sTotalPage )
        {
            m_pID_BUTTON_Pagedown->SetVisable(false);
        }
        else
        {
            m_pID_BUTTON_Pagedown->SetVisable(true);
        }
    }
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_PickUp::ID_LISTIMG_ItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_PickUp )
		return false;
	return false;
}
bool CUI_ID_FRAME_PickUp::ID_LISTIMG_ItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PickUp )
		return false;
	return false;
}
bool CUI_ID_FRAME_PickUp::ID_LISTIMG_ItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PickUp )
		return false;
    if( !pItem )
        return false;

    ID_BUTTON_Item1OnButtonClick( pSender );
	return false;
}
bool CUI_ID_FRAME_PickUp::ID_LISTIMG_ItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PickUp )
		return false;
	return false;
}
// List
void CUI_ID_FRAME_PickUp::ID_LIST_MemberListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_PickUp )
		return;
    // 点玩家分配
    int iItemBegin = sCurrentPage*sItemNumPerPage;
    for(int iPlayer=0; iPlayer < vctTeamMemberAssignList.size(); ++iPlayer)
    {
        if( !stricmp( vctTeamMemberAssignList[iPlayer].szPlayerName, pItem->m_szText) )
        {
            MsgPackageItemAssignReq kAssignReq;
            kAssignReq.nItemPackageID = nItemPackageID;
            kAssignReq.dwPlayerID = vctTeamMemberAssignList[iPlayer].nPlayerDBID;
            kAssignReq.nItemID = kLootItemList[nCurrentSelectItem+iItemBegin].kItem.itembaseinfo.nOnlyInt;
            GettheNetworkInput().SendMsg( &kAssignReq );
            m_pID_LIST_MemberList->SetVisable(false);
            m_pID_PICTURE_MemberList->SetVisable(false);
        }
    }
}
// ListImg / ListEx
bool CUI_ID_FRAME_PickUp::ID_LISTIMG_Item2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_PickUp )
		return false;
	return false;
}
bool CUI_ID_FRAME_PickUp::ID_LISTIMG_Item2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PickUp )
		return false;
	return false;
}
bool CUI_ID_FRAME_PickUp::ID_LISTIMG_Item2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PickUp )
		return false;
    if( !pItem )
        return false;
    ID_BUTTON_Item2OnButtonClick( pSender );

    return false;
}
bool CUI_ID_FRAME_PickUp::ID_LISTIMG_Item2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PickUp )
		return false;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_PickUp::ID_LISTIMG_Item3OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_PickUp )
		return false;
	return false;
}
bool CUI_ID_FRAME_PickUp::ID_LISTIMG_Item3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PickUp )
		return false;
	return false;
}
bool CUI_ID_FRAME_PickUp::ID_LISTIMG_Item3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PickUp )
		return false;
    if( !pItem )
        return false;
    ID_BUTTON_Item3OnButtonClick( pSender );

    return false;
}
bool CUI_ID_FRAME_PickUp::ID_LISTIMG_Item3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PickUp )
		return false;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_PickUp::ID_LISTIMG_Item4OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_PickUp )
		return false;
	return false;
}
bool CUI_ID_FRAME_PickUp::ID_LISTIMG_Item4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PickUp )
		return false;
	return false;
}
bool CUI_ID_FRAME_PickUp::ID_LISTIMG_Item4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PickUp )
		return false;
    if( !pItem )
        return false;
    ID_BUTTON_Item4OnButtonClick( pSender );

	return false;
}
bool CUI_ID_FRAME_PickUp::ID_LISTIMG_Item4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PickUp )
		return false;
	return false;
}

// 装载UI
bool CUI_ID_FRAME_PickUp::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\PickUp.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\PickUp.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_PickUp::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_PickUp, s_CUI_ID_FRAME_PickUpOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_PickUp, s_CUI_ID_FRAME_PickUpOnFrameRender );
    theUiManager.OnButtonClick( ID_FRAME_PickUp, ID_BUTTON_Item1, s_CUI_ID_FRAME_PickUpID_BUTTON_Item1OnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_PickUp, ID_BUTTON_Item2, s_CUI_ID_FRAME_PickUpID_BUTTON_Item2OnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_PickUp, ID_BUTTON_Item3, s_CUI_ID_FRAME_PickUpID_BUTTON_Item3OnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_PickUp, ID_BUTTON_Item4, s_CUI_ID_FRAME_PickUpID_BUTTON_Item4OnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_PickUp, ID_BUTTON_Close, s_CUI_ID_FRAME_PickUpID_BUTTON_CloseOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_PickUp, ID_BUTTON_PickAll, s_CUI_ID_FRAME_PickUpID_BUTTON_PickAllOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_PickUp, ID_BUTTON_Pageup, s_CUI_ID_FRAME_PickUpID_BUTTON_PageupOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_PickUp, ID_BUTTON_Pagedown, s_CUI_ID_FRAME_PickUpID_BUTTON_PagedownOnButtonClick );
    theUiManager.OnIconDragOn( ID_FRAME_PickUp, ID_LISTIMG_Item, s_CUI_ID_FRAME_PickUpID_LISTIMG_ItemOnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_PickUp, ID_LISTIMG_Item, s_CUI_ID_FRAME_PickUpID_LISTIMG_ItemOnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_PickUp, ID_LISTIMG_Item, s_CUI_ID_FRAME_PickUpID_LISTIMG_ItemOnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_PickUp, ID_LISTIMG_Item, s_CUI_ID_FRAME_PickUpID_LISTIMG_ItemOnIconRButtonUp );
    theUiManager.OnListSelectChange( ID_FRAME_PickUp, ID_LIST_MemberList, s_CUI_ID_FRAME_PickUpID_LIST_MemberListOnListSelectChange );
    theUiManager.OnIconDragOn( ID_FRAME_PickUp, ID_LISTIMG_Item2, s_CUI_ID_FRAME_PickUpID_LISTIMG_Item2OnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_PickUp, ID_LISTIMG_Item2, s_CUI_ID_FRAME_PickUpID_LISTIMG_Item2OnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_PickUp, ID_LISTIMG_Item2, s_CUI_ID_FRAME_PickUpID_LISTIMG_Item2OnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_PickUp, ID_LISTIMG_Item2, s_CUI_ID_FRAME_PickUpID_LISTIMG_Item2OnIconRButtonUp );
    theUiManager.OnIconDragOn( ID_FRAME_PickUp, ID_LISTIMG_Item3, s_CUI_ID_FRAME_PickUpID_LISTIMG_Item3OnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_PickUp, ID_LISTIMG_Item3, s_CUI_ID_FRAME_PickUpID_LISTIMG_Item3OnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_PickUp, ID_LISTIMG_Item3, s_CUI_ID_FRAME_PickUpID_LISTIMG_Item3OnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_PickUp, ID_LISTIMG_Item3, s_CUI_ID_FRAME_PickUpID_LISTIMG_Item3OnIconRButtonUp );
    theUiManager.OnIconDragOn( ID_FRAME_PickUp, ID_LISTIMG_Item4, s_CUI_ID_FRAME_PickUpID_LISTIMG_Item4OnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_PickUp, ID_LISTIMG_Item4, s_CUI_ID_FRAME_PickUpID_LISTIMG_Item4OnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_PickUp, ID_LISTIMG_Item4, s_CUI_ID_FRAME_PickUpID_LISTIMG_Item4OnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_PickUp, ID_LISTIMG_Item4, s_CUI_ID_FRAME_PickUpID_LISTIMG_Item4OnIconRButtonUp );

	m_pID_FRAME_PickUp = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_PickUp );
	//m_pID_PICTURE_Wall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PickUp, ID_PICTURE_Wall );
	m_pID_BUTTON_Item1 = (ControlButton*)theUiManager.FindControl( ID_FRAME_PickUp, ID_BUTTON_Item1 );
	m_pID_BUTTON_Item2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_PickUp, ID_BUTTON_Item2 );
	m_pID_BUTTON_Item3 = (ControlButton*)theUiManager.FindControl( ID_FRAME_PickUp, ID_BUTTON_Item3 );
	m_pID_BUTTON_Item4 = (ControlButton*)theUiManager.FindControl( ID_FRAME_PickUp, ID_BUTTON_Item4 );
	m_pID_BUTTON_Close = (ControlButton*)theUiManager.FindControl( ID_FRAME_PickUp, ID_BUTTON_Close );
	m_pID_BUTTON_PickAll = (ControlButton*)theUiManager.FindControl( ID_FRAME_PickUp, ID_BUTTON_PickAll );
	m_pID_TEXT_Name1 = (ControlText*)theUiManager.FindControl( ID_FRAME_PickUp, ID_TEXT_Name1 );
	m_pID_TEXT_Name2 = (ControlText*)theUiManager.FindControl( ID_FRAME_PickUp, ID_TEXT_Name2 );
	m_pID_TEXT_Name3 = (ControlText*)theUiManager.FindControl( ID_FRAME_PickUp, ID_TEXT_Name3 );
	m_pID_TEXT_Name4 = (ControlText*)theUiManager.FindControl( ID_FRAME_PickUp, ID_TEXT_Name4 );
	m_pID_TEXT_Page = (ControlText*)theUiManager.FindControl( ID_FRAME_PickUp, ID_TEXT_Page );
	m_pID_BUTTON_Pageup = (ControlButton*)theUiManager.FindControl( ID_FRAME_PickUp, ID_BUTTON_Pageup );
	m_pID_BUTTON_Pagedown = (ControlButton*)theUiManager.FindControl( ID_FRAME_PickUp, ID_BUTTON_Pagedown );
	m_pID_LISTIMG_Item = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PickUp, ID_LISTIMG_Item );
	m_pID_PICTURE_MemberList = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PickUp, ID_PICTURE_MemberList );
	m_pID_LIST_MemberList = (ControlList*)theUiManager.FindControl( ID_FRAME_PickUp, ID_LIST_MemberList );
	m_pID_LISTIMG_Item2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PickUp, ID_LISTIMG_Item2 );
	m_pID_LISTIMG_Item3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PickUp, ID_LISTIMG_Item3 );
	m_pID_LISTIMG_Item4 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PickUp, ID_LISTIMG_Item4 );
	assert( m_pID_FRAME_PickUp );
	//assert( m_pID_PICTURE_Wall );
	assert( m_pID_BUTTON_Item1 );
	assert( m_pID_BUTTON_Item2 );
	assert( m_pID_BUTTON_Item3 );
	assert( m_pID_BUTTON_Item4 );
	assert( m_pID_BUTTON_Close );
	assert( m_pID_BUTTON_PickAll );
	assert( m_pID_TEXT_Name1 );
	assert( m_pID_TEXT_Name2 );
	assert( m_pID_TEXT_Name3 );
	assert( m_pID_TEXT_Name4 );
	assert( m_pID_TEXT_Page );
	assert( m_pID_BUTTON_Pageup );
	assert( m_pID_BUTTON_Pagedown );
	assert( m_pID_LISTIMG_Item );
	assert( m_pID_PICTURE_MemberList );
	assert( m_pID_LIST_MemberList );
	assert( m_pID_LISTIMG_Item2 );
	assert( m_pID_LISTIMG_Item3 );
	assert( m_pID_LISTIMG_Item4 );
    m_pID_FRAME_PickUp->SetMsgProcFun( frame_msg );

    m_pID_LISTIMG_Item->SetOnMouseMoveFun( ID_LISTIMG_ItemOnMouseOn );
    m_pID_LISTIMG_Item2->SetOnMouseMoveFun( ID_LISTIMG_Item2OnMouseOn );
    m_pID_LISTIMG_Item3->SetOnMouseMoveFun( ID_LISTIMG_Item3OnMouseOn );
    m_pID_LISTIMG_Item4->SetOnMouseMoveFun( ID_LISTIMG_Item4OnMouseOn );

    USE_SCRIPT( eUI_OBJECT_PickUp, this );

    //Reset();
    SetVisable(false);

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_PickUp::_UnLoadUI()
{
    CLOSE_SCRIPT( eUI_OBJECT_PickUp );
	if (NULL == m_pID_FRAME_PickUp)
	{
		return true;
	}
	
	ResetMembers();
    Reset();
	return theUiManager.RemoveFrame( "Data\\UI\\PickUp.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_PickUp::_IsVisable()
{
	if( !m_pID_FRAME_PickUp )
		return false;
	return m_pID_FRAME_PickUp->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_PickUp::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_PickUp )
		return;
	m_pID_FRAME_PickUp->SetVisable( bVisable );
    if( bVisable )
    {
        if( sCurrentPage < 0 )
        {
            ClearItemList();
            // 初始化ImageList
            sItemNumPerPage = ITEM_NUM_PER_PAGE;
            if( sItemNumPerPage > 0 )
            {
                int iItemNumCurrentPage = min(sItemCount, sItemNumPerPage);
                for(int iItem = 0; iItem < iItemNumCurrentPage; ++iItem)
                {
                    if( !kLootItemList[iItem].bHasItem )
                        continue;
                    // 有物品
                    SetItem( kLootItemList[iItem].kItem, iItem );
                }
                sCurrentPage = 0;
                sTotalPage = CalculateTotalPage(sCurrentPage, sItemNumPerPage);
                m_pID_BUTTON_Pageup->SetVisable(false);

                if( sTotalPage > 1 )
                {
                    // 显示页数
                    char szPage[MAX_PATH] = {0};
                    sprintf(szPage, "%d/%d", sCurrentPage+1, sTotalPage);
                    m_pID_TEXT_Page->SetText(szPage);
                }
                else
                    m_pID_TEXT_Page->Clear();

                // Pagedown按钮是否可见
                if( sCurrentPage + 1 >= sTotalPage )
                {
                    m_pID_BUTTON_Pagedown->SetVisable(false);
                }
                else
                {
                    // 检查后面是否真有物品
                    bool bHasItem = false;
                    for(int iItem = iItemNumCurrentPage; iItem < sItemCount; ++iItem)
                    {
                        if( kLootItemList[iItem].bHasItem )
                        {
                            bHasItem = true;
                            break;
                        }
                    }
                    if( !bHasItem )
                        m_pID_BUTTON_Pagedown->SetVisable(false);
                    else
                        m_pID_BUTTON_Pagedown->SetVisable(true);
                }
            }
        }
    }
}

void CUI_ID_FRAME_PickUp::InitData()
{
	memset(kLootItemList, 0, sizeof(LootItemData)*MaxPackageItemCount);
	sCurrentPage    = -1;
	sTotalPage      = 0;
	sItemCount      = 0;
	sItemNumPerPage = 0;
	bNeedSendCloseMsg = false;
}

void CUI_ID_FRAME_PickUp::Reset()
{
	InitData();

	if( !m_pID_FRAME_PickUp )
		return;
	ClearItemList();
	m_pID_TEXT_Page->Clear();
}

// 添加一个物品
bool CUI_ID_FRAME_PickUp::AddItem( const SCharItem& kItem, bool bCanPick )
{
// 	if( !m_pID_FRAME_PickUp )
// 		return false;

    if( sItemCount >= MaxPackageItemCount )
        return false;

    kLootItemList[sItemCount].bHasItem = true;
    memcpy(&kLootItemList[sItemCount].kItem, &kItem, sizeof(SCharItem));
    kLootItemList[sItemCount].bCanLoot = bCanPick;
	int qualityMap[4] = { 0, ItemDefine::IQ_Green, ItemDefine::IQ_Blue, ItemDefine::IQ_Purple };
	if ( thePlayerRole.GetAssignMode() == AssignMode_Assign && kItem.equipdata.quality >= qualityMap[thePlayerRole.GetItemRollLevel()%4] )
	{
		kLootItemList[sItemCount].bNeedLeadAssign = true;
	}
	else
	{
		kLootItemList[sItemCount].bNeedLeadAssign = false;
	}
    sItemCount++;
    return true;
}

void CUI_ID_FRAME_PickUp::SetItem( SCharItem& kItem, int index )
{
    ControlIconDrag::S_ListImg stItem;
    stItem.SetData( &kItem );

    ItemDefine::SItemCommon *pItemCommon =GettheItemDetail().GetItemByID(kItem.itembaseinfo.ustItemID);
    if (!pItemCommon)
    {
        char msg[MAX_PATH] = {0};
        sprintf(msg, "掉落未知物品 ItemID:%d\n", kItem.itembaseinfo.ustItemID);
        OutputDebugString(msg);
        return;
    }

	DWORD color = S_IconInfoHero::GetQualityColor( pItemCommon->ustLevel );
    switch(index)
    {
    case 0:
        m_pID_LISTIMG_Item->SetItem( &stItem, 0 );
        m_pID_LISTIMG_Item->SetVisable(true);
        m_pID_BUTTON_Item1->SetVisable(true);
        m_pID_TEXT_Name1->SetText( pItemCommon->GetItemName(), color );
        break;
    case 1:
        m_pID_LISTIMG_Item2->SetItem( &stItem, 0 );
        m_pID_LISTIMG_Item2->SetVisable(true);
        m_pID_BUTTON_Item2->SetVisable(true);
        m_pID_TEXT_Name2->SetText( pItemCommon->GetItemName(), color );
        break;
    case 2:
        m_pID_LISTIMG_Item3->SetItem( &stItem, 0 );
        m_pID_LISTIMG_Item3->SetVisable(true);
        m_pID_BUTTON_Item3->SetVisable(true);
        m_pID_TEXT_Name3->SetText( pItemCommon->GetItemName(), color );
        break;
    case 3:
        m_pID_LISTIMG_Item4->SetItem( &stItem, 0 );
        m_pID_LISTIMG_Item4->SetVisable(true);
        m_pID_BUTTON_Item4->SetVisable(true);
        m_pID_TEXT_Name4->SetText( pItemCommon->GetItemName(), color );
        break;
    default:
        break;
    }
}

void CUI_ID_FRAME_PickUp::PickOneItem( const SCharItem& kItem )
{
    MsgPickPackageItemReq kPickItemReq;
    kPickItemReq.nItemPackageID = nItemPackageID;
    kPickItemReq.nItemID = kItem.itembaseinfo.nOnlyInt;
    GettheNetworkInput().SendMsg( &kPickItemReq );
}

void CUI_ID_FRAME_PickUp::DeleteItem( __int64 nItemID )
{
	if( !m_pID_FRAME_PickUp )
		return;

    for(int iItem=0; iItem < sItemCount; ++iItem)
    {
        // 从表里删除物品
        if( kLootItemList[iItem].bHasItem && kLootItemList[iItem].kItem.itembaseinfo.nOnlyInt == nItemID )
        {
            kLootItemList[iItem].bHasItem = false;
            // 从UI界面删除物品
            bool bRemoved = false;
            if( m_pID_LISTIMG_Item->IsVisable() )
            {
                ControlIconDrag::S_ListImg* pItem = m_pID_LISTIMG_Item->GetItemByIndex(0);
                if( pItem && pItem->m_pkIconInfo->GetOnlyId() == nItemID)
                {
                    m_pID_LISTIMG_Item->Clear();
                    m_pID_LISTIMG_Item->SetVisable(false);
                    m_pID_BUTTON_Item1->SetVisable(false);
                    m_pID_TEXT_Name1->Clear();
                    bRemoved = true;
                }
            }
            if( !bRemoved && m_pID_LISTIMG_Item2->IsVisable() )
            {
                ControlIconDrag::S_ListImg* pItem = m_pID_LISTIMG_Item2->GetItemByIndex(0);
                if( pItem && pItem->m_pkIconInfo->GetOnlyId() == nItemID)
                {
                    m_pID_LISTIMG_Item2->Clear();
                    m_pID_LISTIMG_Item2->SetVisable(false);
                    m_pID_BUTTON_Item2->SetVisable(false);
                    m_pID_TEXT_Name2->Clear();
                    bRemoved = true;
                }
            }
            if( !bRemoved && m_pID_LISTIMG_Item3->IsVisable() )
            {
                ControlIconDrag::S_ListImg* pItem = m_pID_LISTIMG_Item3->GetItemByIndex(0);
                if( pItem && pItem->m_pkIconInfo->GetOnlyId() == nItemID)
                {
                    m_pID_LISTIMG_Item3->Clear();
                    m_pID_LISTIMG_Item3->SetVisable(false);
                    m_pID_BUTTON_Item3->SetVisable(false);
                    m_pID_TEXT_Name3->Clear();
                    bRemoved = true;
                }
            }
            if( !bRemoved && m_pID_LISTIMG_Item4->IsVisable() )
            {
                ControlIconDrag::S_ListImg* pItem = m_pID_LISTIMG_Item4->GetItemByIndex(0);
                if( pItem && pItem->m_pkIconInfo->GetOnlyId() == nItemID)
                {
                    m_pID_LISTIMG_Item4->Clear();
                    m_pID_LISTIMG_Item4->SetVisable(false);
                    m_pID_BUTTON_Item4->SetVisable(false);
                    m_pID_TEXT_Name4->Clear();
                    bRemoved = true;
                }
            }
            break;
        }
    }
    // 检查包裹里还有物品吗，没有则关闭
    bool bContainItem = false;
    for(int iItem=0; iItem < sItemCount; ++iItem)
    {
        if( kLootItemList[iItem].bHasItem )
        {
            bContainItem = true;
            break;
        }
    }
    if( !bContainItem )
    {
        SetVisable(false);
    }
    else    // 重新计算页数
    {
        sTotalPage = CalculateTotalPage(sCurrentPage, sItemNumPerPage);
        if( sTotalPage > 1 )
        {
            // 显示页数
            char szPage[MAX_PATH] = {0};
            sprintf(szPage, "%d/%d", sCurrentPage+1, sTotalPage);
            m_pID_TEXT_Page->SetText(szPage);
        }
        else
            m_pID_TEXT_Page->Clear();
        if( sCurrentPage + 1 >= sTotalPage )
            m_pID_BUTTON_Pagedown->SetVisable(false);
        else
            m_pID_BUTTON_Pagedown->SetVisable(true);
    }
}

short CUI_ID_FRAME_PickUp::CalculateTotalPage(int nCurPage, int nDisplayNumPerPage)
{
    short totalPage = 0;
    // 获取最后一个有物品的数组下标
    int iItemCount = 0;
    int iItem = sItemCount-1;
    for(; iItem >= 0; --iItem)
    {
        if( kLootItemList[iItem].bHasItem )
            break;
    }
    iItemCount = iItem+1;
    totalPage = (short)(iItemCount * 1.f / nDisplayNumPerPage);
    if( iItemCount > totalPage * nDisplayNumPerPage )
        totalPage++;

    if( totalPage <= nCurPage )
        totalPage = nCurPage + 1;
    return totalPage;        
}

void CUI_ID_FRAME_PickUp::ClearItemList()
{
    m_pID_LISTIMG_Item->Clear();
    m_pID_LISTIMG_Item2->Clear();
    m_pID_LISTIMG_Item3->Clear();
    m_pID_LISTIMG_Item4->Clear();
    m_pID_LISTIMG_Item->SetVisable(false);
    m_pID_LISTIMG_Item2->SetVisable(false);
    m_pID_LISTIMG_Item3->SetVisable(false);
    m_pID_LISTIMG_Item4->SetVisable(false);
    m_pID_BUTTON_Item1->SetVisable(false);
    m_pID_BUTTON_Item2->SetVisable(false);
    m_pID_BUTTON_Item3->SetVisable(false);
    m_pID_BUTTON_Item4->SetVisable(false);
    m_pID_TEXT_Name1->Clear();
    m_pID_TEXT_Name2->Clear();
    m_pID_TEXT_Name3->Clear();
    m_pID_TEXT_Name4->Clear();
    m_pID_LIST_MemberList->Clear();
    m_pID_LIST_MemberList->SetVisable(false);
    m_pID_PICTURE_MemberList->SetVisable(false);
    nCurrentSelectItem = 0;
}

void CUI_ID_FRAME_PickUp::UpdateItemCanLoot( __int64 nItemID, bool bCanLoot )
{
	if( !m_pID_FRAME_PickUp )
		return;
    for(int iItem=0; iItem<sItemCount; ++iItem)
    {
        if( kLootItemList[iItem].bHasItem && kLootItemList[iItem].kItem.itembaseinfo.nOnlyInt == nItemID )
        {
            kLootItemList[iItem].bCanLoot = bCanLoot;
            if( kLootItemList[iItem].bNeedLeadAssign )
                kLootItemList[iItem].bNeedLeadAssign = false;
            break;
        }
    }
}

void CUI_ID_FRAME_PickUp::SetAssignItemListMemberList( int nItemCount, __int64* pItemList, int nPlayerCount, uint32* pPlayerIDList )
{
	if( !m_pID_FRAME_PickUp )
		return;
	for(int iItem=0; iItem<nItemCount; ++iItem)
    {
        for(int iItemIndex=0; iItemIndex<sItemCount; ++iItemIndex)
        {
            if( kLootItemList[iItemIndex].bHasItem && kLootItemList[iItemIndex].kItem.itembaseinfo.nOnlyInt == pItemList[iItem] )
            {
                kLootItemList[iItemIndex].bNeedLeadAssign = true;
                break;
            }
        }
    }

    vctTeamMemberAssignList.clear();
    for(int iPlayer=0; iPlayer<nPlayerCount; ++iPlayer)
    {
        TeamInfo* pTeamInfo = thePlayerRole.GetTeamInfo(pPlayerIDList[iPlayer]);
        if( pTeamInfo )
        {
            TeamMemberAssignData kTeamMember;
            kTeamMember.nPlayerDBID = pPlayerIDList[iPlayer];
            strncpy( kTeamMember.szPlayerName, pTeamInfo->szName.c_str(), 63 );
            vctTeamMemberAssignList.push_back(kTeamMember);
        }
        else
        {
            // 玩家已离队
        }
    }
}

void CUI_ID_FRAME_PickUp::ShowAssignMemberList()
{
    m_pID_LIST_MemberList->Clear();
    for(int iPlayer=0; iPlayer<vctTeamMemberAssignList.size(); ++iPlayer)
    {
        ControlList::S_List stPlayer;
        stPlayer.SetData( vctTeamMemberAssignList[iPlayer].szPlayerName );
        m_pID_LIST_MemberList->AddItem(&stPlayer);
    }
    m_pID_LIST_MemberList->SetVisable(true);
    m_pID_PICTURE_MemberList->SetVisable(true);
}

void CUI_ID_FRAME_PickUp::RemovePlayerFromAssignList(uint32 iPlayerDBID)
{
    if( !vctTeamMemberAssignList.size() )
        return;

    std::vector<TeamMemberAssignData>::iterator iter;
    for( iter = vctTeamMemberAssignList.begin(); iter != vctTeamMemberAssignList.end(); ++iter)
    {
        TeamMemberAssignData* pMemberData = (TeamMemberAssignData*)(&(*iter));
        if( pMemberData && pMemberData->nPlayerDBID == iPlayerDBID)
        {
            vctTeamMemberAssignList.erase(iter);
            break;
        }
    }
    if( m_pID_LIST_MemberList->IsVisable() )
    {
        ShowAssignMemberList();
    }
}

void CUI_ID_FRAME_PickUp::PickAll()
{
	if( !m_pID_FRAME_PickUp )
		return;
    for(int iItem=0; iItem<sItemCount; ++iItem)
    {
        if( kLootItemList[iItem].bHasItem && kLootItemList[iItem].bCanLoot )
        {
            PickOneItem( kLootItemList[iItem].kItem );
        }
    }
}

void CUI_ID_FRAME_PickUp::ID_LISTIMG_ItemOnMouseOn( UINT nFLag, int nX, int nY )
{
   s_CUI_ID_FRAME_PickUp.m_pID_BUTTON_Item1->OnMouseMove( nFLag, nX, nY );
}

void CUI_ID_FRAME_PickUp::ID_LISTIMG_Item2OnMouseOn( UINT nFLag, int nX, int nY )
{
    s_CUI_ID_FRAME_PickUp.m_pID_BUTTON_Item2->OnMouseMove( nFLag, nX, nY );
}

void CUI_ID_FRAME_PickUp::ID_LISTIMG_Item3OnMouseOn( UINT nFLag, int nX, int nY )
{
    s_CUI_ID_FRAME_PickUp.m_pID_BUTTON_Item3->OnMouseMove( nFLag, nX, nY );
}

void CUI_ID_FRAME_PickUp::ID_LISTIMG_Item4OnMouseOn( UINT nFLag, int nX, int nY )
{
    s_CUI_ID_FRAME_PickUp.m_pID_BUTTON_Item4->OnMouseMove( nFLag, nX, nY );
}

bool CUI_ID_FRAME_PickUp::frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
    if ( bMsgUsed == true || g_GameState != G_MAIN )
        return false;

    if( !s_CUI_ID_FRAME_PickUp.IsVisable() )
        return false;

    switch( msg ) 
    {
    case WM_KEYDOWN:
        {
			if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_PickAll) )
            {
                s_CUI_ID_FRAME_PickUp.PickAll();
                return true;
            }
        }
    }
    return false;
}

ControlButton* CUI_ID_FRAME_PickUp::GetButtonPickAll()
{
	if( !m_pID_FRAME_PickUp )
		return NULL;
	return m_pID_BUTTON_PickAll;
}

void CUI_ID_FRAME_PickUp::AllItemAssignMySelf()
{
	for (int i = 0;i < sItemCount;++i)
	{
		MsgPackageItemAssignReq kAssignReq;
		kAssignReq.nItemPackageID = nItemPackageID;
		kAssignReq.dwPlayerID = thePlayerRole.GetDBID();
		kAssignReq.nItemID = kLootItemList[i].kItem.itembaseinfo.nOnlyInt;
		GettheNetworkInput().SendMsg( &kAssignReq );
	}
}