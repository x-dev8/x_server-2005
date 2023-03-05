/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Hero\Program\trunk\Bin\Client\Data\Ui\Action.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Action.h"
#include "UIMgr.h"
#include "ExpressionAction.h"
#include "Common.h"
#include "PlayerRole.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"

CUI_ID_FRAME_Action s_CUI_ID_FRAME_Action;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Action, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Action, OnFrameRender )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Action, ID_BUTTON_helpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Action, ID_BUTTON_CLOSEOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Action, ID_LISTIMG_ActionIconOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Action, ID_LISTIMG_ActionIconOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Action, ID_LISTIMG_ActionIconOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Action, ID_LISTIMG_ActionIconOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Action, ID_BUTTON_PageupOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Action, ID_BUTTON_PagedownOnButtonClick )
CUI_ID_FRAME_Action::CUI_ID_FRAME_Action()
{
	// Member
	m_pID_FRAME_Action = NULL;
// 	m_pID_PICTURE_TitleDi = NULL;
// 	m_pID_BUTTON_help = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_LISTIMG_ActionIcon = NULL;
	m_pID_TEXT_Name = NULL;
	m_pID_TEXT_Name1 = NULL;
	m_pID_TEXT_Name2 = NULL;
	m_pID_TEXT_Name3 = NULL;
	m_pID_TEXT_Name4 = NULL;
	m_pID_TEXT_Name5 = NULL;
	m_pID_TEXT_Name6 = NULL;
	m_pID_TEXT_Name7 = NULL;
	m_pID_TEXT_Name8 = NULL;
	m_pID_TEXT_Name9 = NULL;
	m_pID_TEXT_Page = NULL;
	m_pID_BUTTON_Pageup = NULL;
	m_pID_BUTTON_Pagedown = NULL;
	m_pID_TEXT_Name10 = NULL;
	m_pID_TEXT_Name11 = NULL;

	m_bInited = false;
	m_ustCurPage = 0;
	m_ustIconNumPerPage = 0;
	m_ustPageNum = 0;
	m_vecDescriptions.clear();
	m_vecDescriptions.reserve(10);
}
// Frame
bool CUI_ID_FRAME_Action::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_Action::OnFrameRender()
{
	return true;
}
// Button
// bool CUI_ID_FRAME_Action::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
// {
// 	if( !m_pID_FRAME_Action )
// 		return false;
// 
// 	return true;
// }
// Button
bool CUI_ID_FRAME_Action::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Action )
		return false;

	SetVisable(false);
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Action::ID_LISTIMG_ActionIconOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_Action )
		return false;

	return false;
}
bool CUI_ID_FRAME_Action::ID_LISTIMG_ActionIconOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Action )
		return false;

	return false;
}
bool CUI_ID_FRAME_Action::ID_LISTIMG_ActionIconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Action )
		return false;

	return false;
}
bool CUI_ID_FRAME_Action::ID_LISTIMG_ActionIconOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Action )
		return false;

	CPlayer *me = theHeroGame.GetPlayerMgr()->GetMe();
	if( pItem && me != NULL && !me->IsMoving())
	{
		unsigned short ustItemId = pItem->m_pkIconInfo->GetItemId();
		ExpAction::ESex sex = (thePlayerRole.GetSex() == Sex_Male) ? ExpAction::Male : ExpAction::Female;
		CExpressionAction::Instance().CheckAndDoExpressionActionByItemId(ustItemId, sex);
	}

	return false;
}
// Button
bool CUI_ID_FRAME_Action::ID_BUTTON_PageupOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Action )
		return false;

	if( m_ustCurPage > 0 )
	{
		ShowPage(m_ustCurPage-1);
	}

	return true;
}
// Button
bool CUI_ID_FRAME_Action::ID_BUTTON_PagedownOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Action )
		return false;

	if( m_ustCurPage < m_ustPageNum -1 )
	{
		ShowPage(m_ustCurPage+1);
	}
	return true;
}

// 装载UI
bool CUI_ID_FRAME_Action::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Action.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Action.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Action::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Action, s_CUI_ID_FRAME_ActionOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Action, s_CUI_ID_FRAME_ActionOnFrameRender );
	//theUiManager.OnButtonClick( ID_FRAME_Action, ID_BUTTON_help, s_CUI_ID_FRAME_ActionID_BUTTON_helpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Action, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_ActionID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_Action, ID_LISTIMG_ActionIcon, s_CUI_ID_FRAME_ActionID_LISTIMG_ActionIconOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Action, ID_LISTIMG_ActionIcon, s_CUI_ID_FRAME_ActionID_LISTIMG_ActionIconOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Action, ID_LISTIMG_ActionIcon, s_CUI_ID_FRAME_ActionID_LISTIMG_ActionIconOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Action, ID_LISTIMG_ActionIcon, s_CUI_ID_FRAME_ActionID_LISTIMG_ActionIconOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_Action, ID_BUTTON_Pageup, s_CUI_ID_FRAME_ActionID_BUTTON_PageupOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Action, ID_BUTTON_Pagedown, s_CUI_ID_FRAME_ActionID_BUTTON_PagedownOnButtonClick );

	m_pID_FRAME_Action = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Action );
// 	m_pID_PICTURE_TitleDi = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Action, ID_PICTURE_TitleDi );
// 	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_Action, ID_BUTTON_help );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_Action, ID_BUTTON_CLOSE );
	m_pID_LISTIMG_ActionIcon = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Action, ID_LISTIMG_ActionIcon );
	m_pID_TEXT_Name = (ControlText*)theUiManager.FindControl( ID_FRAME_Action, ID_TEXT_Name );
	m_pID_TEXT_Name1 = (ControlText*)theUiManager.FindControl( ID_FRAME_Action, ID_TEXT_Name1 );
	m_pID_TEXT_Name2 = (ControlText*)theUiManager.FindControl( ID_FRAME_Action, ID_TEXT_Name2 );
	m_pID_TEXT_Name3 = (ControlText*)theUiManager.FindControl( ID_FRAME_Action, ID_TEXT_Name3 );
	m_pID_TEXT_Name4 = (ControlText*)theUiManager.FindControl( ID_FRAME_Action, ID_TEXT_Name4 );
	m_pID_TEXT_Name5 = (ControlText*)theUiManager.FindControl( ID_FRAME_Action, ID_TEXT_Name5 );
	m_pID_TEXT_Name6 = (ControlText*)theUiManager.FindControl( ID_FRAME_Action, ID_TEXT_Name6 );
	m_pID_TEXT_Name7 = (ControlText*)theUiManager.FindControl( ID_FRAME_Action, ID_TEXT_Name7 );
	m_pID_TEXT_Name8 = (ControlText*)theUiManager.FindControl( ID_FRAME_Action, ID_TEXT_Name8 );
	m_pID_TEXT_Name9 = (ControlText*)theUiManager.FindControl( ID_FRAME_Action, ID_TEXT_Name9 );
	m_pID_TEXT_Page = (ControlText*)theUiManager.FindControl( ID_FRAME_Action, ID_TEXT_Page );
	m_pID_BUTTON_Pageup = (ControlButton*)theUiManager.FindControl( ID_FRAME_Action, ID_BUTTON_Pageup );
	m_pID_BUTTON_Pagedown = (ControlButton*)theUiManager.FindControl( ID_FRAME_Action, ID_BUTTON_Pagedown );
	m_pID_TEXT_Name10 = (ControlText*)theUiManager.FindControl( ID_FRAME_Action, ID_TEXT_Name10 );
	m_pID_TEXT_Name11 = (ControlText*)theUiManager.FindControl( ID_FRAME_Action, ID_TEXT_Name11 );

	assert( m_pID_FRAME_Action );
// 	assert( m_pID_PICTURE_TitleDi );
// 	assert( m_pID_BUTTON_help );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_LISTIMG_ActionIcon );
	assert( m_pID_TEXT_Name );
	assert( m_pID_TEXT_Name1 );
	assert( m_pID_TEXT_Name2 );
	assert( m_pID_TEXT_Name3 );
	assert( m_pID_TEXT_Name4 );
	assert( m_pID_TEXT_Name5 );
	assert( m_pID_TEXT_Name6 );
	assert( m_pID_TEXT_Name7 );
	assert( m_pID_TEXT_Name8 );
	assert( m_pID_TEXT_Name9 );
	assert( m_pID_TEXT_Page );
	assert( m_pID_BUTTON_Pageup );
	assert( m_pID_BUTTON_Pagedown );
	assert( m_pID_TEXT_Name10 );
	assert( m_pID_TEXT_Name11 );

	m_bInited = false;
	m_ustCurPage = 0;
	m_ustIconNumPerPage = 0;
	m_ustPageNum = 0;
	m_vecDescriptions.clear();

	m_vecDescriptions.push_back(m_pID_TEXT_Name);
	m_vecDescriptions.push_back(m_pID_TEXT_Name1);
	m_vecDescriptions.push_back(m_pID_TEXT_Name2);
	m_vecDescriptions.push_back(m_pID_TEXT_Name3);
	m_vecDescriptions.push_back(m_pID_TEXT_Name4);
	m_vecDescriptions.push_back(m_pID_TEXT_Name5);
	m_vecDescriptions.push_back(m_pID_TEXT_Name6);
	m_vecDescriptions.push_back(m_pID_TEXT_Name7);
	m_vecDescriptions.push_back(m_pID_TEXT_Name8);
	m_vecDescriptions.push_back(m_pID_TEXT_Name9);
	m_vecDescriptions.push_back(m_pID_TEXT_Name10);
	m_vecDescriptions.push_back(m_pID_TEXT_Name11);

	SetVisable(false);
	USE_SCRIPT( eUI_OBJECT_Action, this );
	
	return true;
}
	// 卸载UI
bool CUI_ID_FRAME_Action::_UnLoadUI()
{
	CLOSE_SCRIPT( eUI_OBJECT_Action );

	m_vecDescriptions.clear();

	m_pID_FRAME_Action = NULL;
// 	m_pID_PICTURE_TitleDi = NULL;
//	m_pID_BUTTON_help = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_LISTIMG_ActionIcon = NULL;
	m_pID_TEXT_Name = NULL;
	m_pID_TEXT_Name1 = NULL;
	m_pID_TEXT_Name2 = NULL;
	m_pID_TEXT_Name3 = NULL;
	m_pID_TEXT_Name4 = NULL;
	m_pID_TEXT_Name5 = NULL;
	m_pID_TEXT_Name6 = NULL;
	m_pID_TEXT_Name7 = NULL;
	m_pID_TEXT_Name8 = NULL;
	m_pID_TEXT_Name9 = NULL;
	m_pID_TEXT_Page = NULL;
	m_pID_BUTTON_Pageup = NULL;
	m_pID_BUTTON_Pagedown = NULL;
	m_pID_TEXT_Name10 = NULL;
	m_pID_TEXT_Name11 = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\Action.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Action::_IsVisable()
{
	if( !m_pID_FRAME_Action )
		return false;
	return m_pID_FRAME_Action->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Action::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_Action ) 
		return;
	m_pID_FRAME_Action->SetVisable( bVisable );
	if( bVisable )
	{
		if( !m_bInited )
		{
			Init();
		}
	}
}

void CUI_ID_FRAME_Action::Init()
{
	m_bInited = true;

	ExpAction::ESex sex;
	if( thePlayerRole.GetSex() == Sex_Male )
		sex = ExpAction::Male;
	else
		sex = ExpAction::Female;

	m_ustIconNumPerPage = min(m_pID_LISTIMG_ActionIcon->GetItemCnt(), m_vecDescriptions.size());
	m_ustPageNum = (unsigned short)ceil(CExpressionAction::Instance().GetExpActionNum(sex)* 1.f / m_ustIconNumPerPage);

	ShowPage(0);
}

bool CUI_ID_FRAME_Action::ShowPage( unsigned short ustPageNo )
{
	m_pID_LISTIMG_ActionIcon->Clear();
	for(int i=0; i<m_vecDescriptions.size(); ++i)
	{
		m_vecDescriptions[i]->SetText("");
	}

	if( m_ustIconNumPerPage == 0 || ustPageNo >= m_ustPageNum )
		return false;

	m_ustCurPage = ustPageNo;
	char page[32] = {0};
	MeSprintf_s(page, sizeof(page)/sizeof(char) - 1, "%d/%d", m_ustCurPage+1, m_ustPageNum);
	m_pID_TEXT_Page->SetText(page);

	ExpAction::ESex sex;
	if( thePlayerRole.GetSex() == Sex_Male )
		sex = ExpAction::Male;
	else
		sex = ExpAction::Female;

	int nBeginIndex = ustPageNo * m_ustIconNumPerPage;
	if( nBeginIndex >= CExpressionAction::Instance().GetExpActionNum(sex) )
		return false;

	int nEndIndex = min(nBeginIndex + m_ustIconNumPerPage -1, CExpressionAction::Instance().GetExpActionNum(sex) -1);
	for( int i = nBeginIndex; i <= nEndIndex; ++i )
	{
		const ExpAction* pAction = CExpressionAction::Instance().GetExpActionByIndex(i, sex);
		if( !pAction )
			continue;
		
		SetIcon(i-nBeginIndex, pAction);
	}

	if( m_ustCurPage > 0 )
		m_pID_BUTTON_Pageup->SetEnable(true);
	else
		m_pID_BUTTON_Pageup->SetEnable(false);
	if( m_ustCurPage < m_ustPageNum -1 )
		m_pID_BUTTON_Pagedown->SetEnable(true);
	else
		m_pID_BUTTON_Pagedown->SetEnable(false);

	return true;
}

void CUI_ID_FRAME_Action::SetIcon( int index, const ExpAction* pAction )
{
	ControlIconDrag::S_ListImg stItem;
	stItem.SetData(pAction->GetItemId(), 0 );
	m_pID_LISTIMG_ActionIcon->SetItem(&stItem, index);
	if( index < m_vecDescriptions.size() )
		m_vecDescriptions[index]->SetText(pAction->GetCommand());
}

bool CUI_ID_FRAME_Action::IsActionList( ControlObject* pListImg )
{
	if( !m_pID_FRAME_Action ) 
		return false;

	if( pListImg && m_pID_LISTIMG_ActionIcon == pListImg )
		return true;

	return false;
}