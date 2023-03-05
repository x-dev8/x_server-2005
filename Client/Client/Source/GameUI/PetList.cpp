/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\PetList.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "PetList.h"
#include "PetStorage.h"
#include "IconManagerClient.h"
#include "PlayerRole.h"
#include "SeekPet.h"
#include "MessageDefine.h"
#include "NetworkInput.h"
#include "ScreenInfoManager.h"

CUI_ID_FRAME_PetList s_CUI_ID_FRAME_PetList;

MAP_FRAME_RUN( s_CUI_ID_FRAME_PetList, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_PetList, OnFrameRender )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_PetList, ID_LIST_PetListOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PetList, ID_BUTTON_InfoOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PetList, ID_BUTTON_OKOnButtonClick )

CUI_ID_FRAME_PetList::CUI_ID_FRAME_PetList()
{
    m_nCurSelectId = -1;
    ResetMembers();
}
	
void CUI_ID_FRAME_PetList::ResetMembers()
{
    m_pID_FRAME_PetList = NULL;
    m_pID_LIST_PetList = NULL;
    m_pID_BUTTON_Info = NULL;
    m_pID_BUTTON_OK = NULL;
}

bool CUI_ID_FRAME_PetList::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_PetList::OnFrameRender()
{
	return true;
}
// List
void CUI_ID_FRAME_PetList::ID_LIST_PetListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_PetList )
		return;
    
    SetCurrentSelectIndex( m_pID_LIST_PetList->GetCurSelIndex() );
}
// Button
bool CUI_ID_FRAME_PetList::ID_BUTTON_InfoOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetList )
		return false;

    SeekPetByIndex( m_nCurSelectId );
	return true;
}
// Button
bool CUI_ID_FRAME_PetList::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_PetList )
		return false;
    
    StoreMount();
	return true;
}

// 装载UI
bool CUI_ID_FRAME_PetList::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\PetList.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\PetList.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}

// 关连控件
bool CUI_ID_FRAME_PetList::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_PetList, s_CUI_ID_FRAME_PetListOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_PetList, s_CUI_ID_FRAME_PetListOnFrameRender );
	theUiManager.OnListSelectChange( ID_FRAME_PetList, ID_LIST_PetList, s_CUI_ID_FRAME_PetListID_LIST_PetListOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_PetList, ID_BUTTON_Info, s_CUI_ID_FRAME_PetListID_BUTTON_InfoOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PetList, ID_BUTTON_OK, s_CUI_ID_FRAME_PetListID_BUTTON_OKOnButtonClick );

	m_pID_FRAME_PetList = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_PetList );
	m_pID_LIST_PetList = (ControlList*)theUiManager.FindControl( ID_FRAME_PetList, ID_LIST_PetList );
	m_pID_BUTTON_Info = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetList, ID_BUTTON_Info );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_PetList, ID_BUTTON_OK );

	assert( m_pID_FRAME_PetList );
	assert( m_pID_LIST_PetList );
	assert( m_pID_BUTTON_Info );
	assert( m_pID_BUTTON_OK );

    m_pID_FRAME_PetList->SetOnVisibleChangedFun( OnVisibleChange );

	return true;
}

// 卸载UI
bool CUI_ID_FRAME_PetList::_UnLoadUI()
{
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\PetList.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_PetList::_IsVisable()
{
	if ( !m_pID_FRAME_PetList )
		return false;
	return m_pID_FRAME_PetList->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_PetList::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_PetList )
		return;
	m_pID_FRAME_PetList->SetVisable( bVisable );
}

//---------------------逻辑----------------------
void CUI_ID_FRAME_PetList::ShowPetList( bool bShow )
{
    SetVisable( bShow );
    if( bShow )
    {
        Refresh();
    }
}

void CUI_ID_FRAME_PetList::OnVisibleChange( ControlObject* pUIObject )
{
    if( !s_CUI_ID_FRAME_PetList.IsVisable() )
    {
        s_CUI_ID_FRAME_PetStorage.ShowPetStorage( false );
    }
}

void CUI_ID_FRAME_PetList::SeekPetByIndex( int nIndex )
{
    // 查看详情
    if( nIndex < 0 || nIndex >= ITEM_MOUNT_MAXCOUNT )
        return;

    SMountItem* pMount = &thePlayerRole.m_charinfo.ItemBagData.miItems[nIndex];
    s_CUI_ID_FRAME_SeekPet.SetVisable( true );
    s_CUI_ID_FRAME_SeekPet.SetMount( *pMount );
}

void CUI_ID_FRAME_PetList::StoreMount()
{
    // 存马报错信息
    if( m_nCurSelectId < 0 || m_nCurSelectId > ITEM_MOUNT_MAXCOUNT )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_Mount_InfoError ) );
        return;
    }

    SMountItem* pMount = &thePlayerRole.m_charinfo.ItemBagData.miItems[m_nCurSelectId];
    if( pMount->GetMountID() <= 0 )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_Mount_InfoError ) );
        return;
    }

    if( pMount->baseInfo.isActive )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_Mount_ActivedNotAdmit ) );
        return;
    }

    int nDestIndex = s_CUI_ID_FRAME_PetStorage.GetStorageEmptySlot();
    if( nDestIndex < 0 )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_Mount_StorageFull ) );
        return;
    }

    // 发送信息
    MsgMoveStorageMount msg;
    msg.nMoveType = MsgMoveStorageMount::Type_CharToStorage;
    msg.nSrcIndex = m_nCurSelectId;
    msg.nDstIndex = nDestIndex;
    msg.nGuid = pMount->baseInfo.guid;
    GettheNetworkInput().SendMsg( &msg );
}

int CUI_ID_FRAME_PetList::GetCharEmptySlot()
{
    // 寻找人物携带坐骑空位
    int nCharMountCnt( 0 );
    int nEmptyIndex( -1 );
    for( int i = 0; i < ITEM_MOUNT_MAXCOUNT; ++i )
    {
        SMountItem* pMount = &thePlayerRole.m_charinfo.ItemBagData.miItems[i];
        if( pMount->GetMountID() <= 0 && nEmptyIndex < 0 )
        {
            nEmptyIndex = i;
        }
        else if( pMount->GetMountID() > 0 )
        {
            ++nCharMountCnt;
        }
    }
    // 当前可携带最大数量
    if( nCharMountCnt >= thePlayerRole.m_charinfo.baseinfo.liveinfo.ucMountCount )
    {
        return -1;
    }
    else
    {
        return nEmptyIndex;
    }
}

//--------------------UI-------------------------
void CUI_ID_FRAME_PetList::Refresh()
{
    if( !IsUILoad() )
        return;

    // 将角色携带的马放入List
    m_pID_LIST_PetList->Clear();
    for( int i = 0; i < ITEM_MOUNT_MAXCOUNT; ++i )
    {
        SMountItem* pMount = &thePlayerRole.m_charinfo.ItemBagData.miItems[i];
        if( pMount->GetMountID() <= 0 )
        {
            continue;
        }
        ControlList::S_List sList;
        DWORD dwColor = S_IconInfoHero::GetQualityColor( pMount->baseInfo.quality );
        sList.SetData( pMount->GetMountName(), 0, NULL, dwColor );
        sList.SetAlignMode( ControlList::S_List::LIST_ALIGNMODE_MIDDLE );
        m_pID_LIST_PetList->AddItem( &sList, false );
    }

    // 默认选中第一匹
    m_nCurSelectId = -1;
    SetCurrentSelectIndex( 0 );

    // 没马时“寄存”和“详细信息”灰态
    if( m_pID_LIST_PetList->GetListItemCnt() <= 0 )
    {
        m_pID_BUTTON_OK->SetEnable( false );
        m_pID_BUTTON_Info->SetEnable( false );
    }
    else
    {
        m_pID_BUTTON_OK->SetEnable( true );
        m_pID_BUTTON_Info->SetEnable( true );
    }
}

void CUI_ID_FRAME_PetList::SetCurrentSelectIndex( int nIndex )
{
    // 选中马
    if( !IsUILoad() )
        return;

    if( nIndex < 0 || nIndex >= ITEM_MOUNT_MAXCOUNT )
        return;

    int nMountId = thePlayerRole.m_charinfo.ItemBagData.miItems[nIndex].baseInfo.id;
    if( nMountId <= 0 )
        return;

    if( nIndex >= m_pID_LIST_PetList->GetListItemCnt() )
        return;

    m_nCurSelectId = nIndex;
    if( m_pID_LIST_PetList->GetCurSelIndex() != nIndex )
    {
        m_pID_LIST_PetList->SetCurSelIndex( nIndex );
    }
}
