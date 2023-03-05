/********************************************************************
Created by UIEditor.exe
FileName: D:\My Documents\桌面\Title\Title.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "UiTitle.h"
#include "PlayerRole.h"
#include "XmlStringLanguage.h"
#include "NetworkInput.h"
#include "MeUI/IconManager.h"
#include "UIMgr.h"
#include "Common.h"
#include "baseProperty.h"
#include "TitleConfig.h"
#include "MessageBox.h"
#include "RelationMessage.h"
#include "Create.h"
#include "ScreenInfoManager.h"
#include "chatcheck.h"
#include "RankTitle.h"

extern CPlayerRole thePlayerRole;

CUI_ID_FRAME_Title s_CUI_ID_FRAME_Title;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Title, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Title, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Title, ID_BUTTON_HideTitleOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Title, ID_LIST_TitleListOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Title, ID_BUTTON_ShowTitleOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Title, ID_LIST_PropertyOnListSelectChange )
//MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Title, ID_LIST_NextPropertyOnListSelectChange )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_Title, ID_EDIT_MOODOnEditEnter )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_Title, ID_COMBOBOX_MOOD_TITLEOnComboBoxChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Title, ID_BUTTON_MODIFY_MOODOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Title, ID_LISTIMG_BuffOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Title, ID_LISTIMG_BuffOnIconLDBClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Title, ID_LISTIMG_BuffOnIconRButtonUp )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Title, ID_LISTIMG_BuffOnIconButtonClick )

CUI_ID_FRAME_Title::CUI_ID_FRAME_Title()
{
	// Member
	ResetMembers();
}

void CUI_ID_FRAME_Title::ResetMembers()
{
	m_pID_FRAME_Title = NULL;
	m_pID_TEXT_Explain = NULL;
	m_pID_BUTTON_HideTitle = NULL;
	m_pID_LIST_TitleList = NULL;
	m_pID_BUTTON_ShowTitle = NULL;
	m_pID_LIST_Property = NULL;
// 	m_pID_LIST_NextProperty = NULL;	
// 	m_pID_TEXT_NextExplain = NULL;
// 	m_pID_TEXT_NextTitle = NULL;
	m_pID_EDIT_MOOD = NULL;
	m_pID_COMBOBOX_MOOD_TITLE = NULL;
	m_pID_BUTTON_MODIFY_MOOD = NULL;
	m_pID_LISTIMG_Buff = NULL;
}

// Frame
bool CUI_ID_FRAME_Title::OnFrameRun()
{
	if( 0 )
		Refresh();
	return true;
}
bool CUI_ID_FRAME_Title::OnFrameRender()
{
	if( !IsVisable() )
		return false;
    if(m_bNeedRefresh)
    {
        Refresh();
        m_bNeedRefresh = false;
    }
	return true;
}
// List
void CUI_ID_FRAME_Title::ID_LIST_PropertyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_Title )
		return;
}

// Edit
void CUI_ID_FRAME_Title::ID_EDIT_MOODOnEditEnter( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_Title )
		return;
}

// ComboBox
void CUI_ID_FRAME_Title::ID_COMBOBOX_MOOD_TITLEOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	static int lastSelIdx = -1;
	int curIdx = m_pID_COMBOBOX_MOOD_TITLE->GetCurSelIndex();
	if (curIdx == lastSelIdx)
		return;

	lastSelIdx = curIdx;

	if(curIdx == 1)
	{
		TitleConfig::Title* pTitle = GetCurrentSelectTitle();
		if( !pTitle )
		{	
			return ;
		}

		MsgShowSignature msg1;
		msg1.showSignature = false;
		memcpy(msg1.szSignature,thePlayerRole.GetSignature(),RelationDefine::MaxSignLength - 1);
		GettheNetworkInput().SendMsg(&msg1);
		theHeroGame.GetPlayerMgr()->GetMe()->ShowSignature(false);

	MsgChangeTitleReq msg;
	msg.nTitleID = pTitle->GetID();
	GettheNetworkInput().SendMsg( &msg,msg.GetLength() );



	return ;
	}


	if(curIdx == 0)
	{
		MsgChangeTitleReq msg1;
		msg1.nTitleID = 0;
		GettheNetworkInput().SendMsg( &msg1,msg1.GetLength() );

		MsgShowSignature msg;
		msg.showSignature = (curIdx == 0 ? 1 : 0);
		//strcpy_s(msg.szSignature, RelationDefine::MaxSignLength - 1, thePlayerRole.GetSignature());
		memcpy(msg.szSignature,thePlayerRole.GetSignature(),RelationDefine::MaxSignLength - 1);
		GettheNetworkInput().SendMsg(&msg);
		theHeroGame.GetPlayerMgr()->GetMe()->ShowSignature(msg.showSignature);
	}
	

	

	
}

// Button
bool CUI_ID_FRAME_Title::ID_BUTTON_MODIFY_MOODOnButtonClick( ControlObject* pSender )
{
	// 修改心情
	const char *szMood = m_pID_EDIT_MOOD->GetText();
	//if (szMood == NULL) 它能与NULL判断么？
	//	return false;

	// 空的心情也要发送修改请求
	//if(!strlen(szMood))
	//	return false;
	if (strlen(szMood) > 0)
	{
		bool bValue =  CChatCheck::getInstance()->CheckStringInLow(szMood);
		if(!bValue)
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eCreate_NameError ));
			return false;
		}
	}
	
	if (strlen(szMood) > RelationDefine::MaxSignLength - 1)
	{
		std::string str(theXmlString.GetString(eText_Mood_Text_TooLong));
		//char buf[8] = {0};
		//sprintf(buf, "%d。", RelationDefine::MaxSignLength - 1);
		//str += buf;
		s_CUI_ID_FRAME_MessageBox.Show(str.c_str(), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, false);
		return false;
	}

	if (m_pID_EDIT_MOOD != NULL)
	{
		MsgChangeSignatureReq Req;
		int sizeStr = sizeof(szMood);
		int len = strlen(szMood);
		int sizeD = sizeof(Req.szSignature);


		
		//strcpy_s(Req.szSignature,min(RelationDefine::MaxSignLength - 1,len) , szMood); //lyh会崩溃，在临界点的时候 所以修改为memcpy

		memcpy(Req.szSignature,szMood,RelationDefine::MaxSignLength - 1);
		Req.szSignature[RelationDefine::MaxSignLength - 1] = '\0';
		
		GettheNetworkInput().SendMsg( &Req );

		thePlayerRole.SetSignature(szMood);
		RefreshMood();

		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Title_Belongs, theXmlString.GetString(eText_Title_ChangeSuccess) );
	}
	return true;
}

// Button
bool CUI_ID_FRAME_Title::ID_BUTTON_HideTitleOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Title )
		return false;
//隐藏同时隐藏心情和称号
/*	int curIdx = m_pID_COMBOBOX_MOOD_TITLE->GetCurSelIndex();*/
	MsgShowSignature msg0; //lyh++ 如果选择的是心情 则隐藏心情
	msg0.showSignature = false;
		memcpy(msg0.szSignature,thePlayerRole.GetSignature(),RelationDefine::MaxSignLength - 1);
		GettheNetworkInput().SendMsg(&msg0);
		theHeroGame.GetPlayerMgr()->GetMe()->ShowSignature(0);


	MsgChangeTitleReq msg;
	msg.nTitleID = 0;
	GettheNetworkInput().SendMsg(&msg,msg.GetLength() );


	return true;
}
// List
void CUI_ID_FRAME_Title::ID_LIST_TitleListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_Title )
		return;
	*m_pID_TEXT_Explain = "";
// 	*m_pID_TEXT_NextExplain = "";
// 	*m_pID_TEXT_NextTitle = "";
	m_pID_LIST_Property->Clear();
//	m_pID_LIST_NextProperty->Clear();
	m_pID_LISTIMG_Buff->Clear();

	TitleConfig::Title* pTitle = GetCurrentSelectTitle();
	if( !pTitle )
		return;

	RefreshTitleDesc( m_pID_TEXT_Explain, pTitle );
	RefreshTitleProp( m_pID_LIST_Property, pTitle );
	RefreshTitleBuff( m_pID_LISTIMG_Buff, pTitle );

    if(!IsHaveExistTitle(pTitle))
        return;

	TitleConfig::Title* pNextTitle = theTitleConfig.GetTitleByTitleID( pTitle->GetNextTitleId( true ) );
	if( !pNextTitle )
	{
		// 已经不能升级了		
// 		char szBuff[255];
//         if(pTitle->GetID() == 10000)
//             MeSprintf_s(szBuff,sizeof(szBuff) / sizeof(char) - 1,"%s",theXmlString.GetString(eText_TitleNoUpdate));
//         else
// 		    MeSprintf_s( szBuff, sizeof(szBuff)/sizeof(char) - 1, theXmlString.GetString( eTitle_CannotUplevel ), pTitle->GetName() );
// 		m_pID_TEXT_NextExplain->SetText( szBuff );					
		return;
	}

// 	RefreshTitleDesc( m_pID_TEXT_NextExplain, pNextTitle, true );
// 	RefreshTitleProp( m_pID_LIST_NextProperty, pNextTitle );

}
// Button
bool CUI_ID_FRAME_Title::ID_BUTTON_ShowTitleOnButtonClick( ControlObject* pSender )
{		
	if( !m_pID_FRAME_Title )
		return false;

	int curIdx = m_pID_COMBOBOX_MOOD_TITLE->GetCurSelIndex();
	MsgShowSignature msg0; //lyh++ 如果选择的是心情 则显示心情
	msg0.showSignature = (curIdx == 0 ? 1 : 0);
	if(msg0.showSignature)
	{ 
		memcpy(msg0.szSignature,thePlayerRole.GetSignature(),RelationDefine::MaxSignLength - 1);
		GettheNetworkInput().SendMsg(&msg0);
		theHeroGame.GetPlayerMgr()->GetMe()->ShowSignature(msg0.showSignature);
		//s_CUI_ID_FRAME_RankTitle.ID_BUTTON_HideTitleOnButtonClick(NULL);
		return true;
	}

	
	TitleConfig::Title* pTitle = GetCurrentSelectTitle();
	if( !pTitle )
	{	
		return true;
	}

	if (theHeroGame.GetPlayerMgr() && 
		theHeroGame.GetPlayerMgr()->GetMe() && 
		theHeroGame.GetPlayerMgr()->GetMe()->IsShowSignature())
	{
        //显示心情则关闭它
		MsgShowSignature msg1;
		msg1.showSignature = false;
		memcpy(msg1.szSignature,thePlayerRole.GetSignature(),RelationDefine::MaxSignLength - 1);
		GettheNetworkInput().SendMsg(&msg1);
		theHeroGame.GetPlayerMgr()->GetMe()->ShowSignature(false);
	}

	MsgChangeTitleReq msg;
	msg.nTitleID = pTitle->GetID();
	GettheNetworkInput().SendMsg( &msg,msg.GetLength() );

	//s_CUI_ID_FRAME_RankTitle.ID_BUTTON_HideTitleOnButtonClick(NULL);

	return true;
}
// void CUI_ID_FRAME_Title::ID_LIST_NextPropertyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
// {	
// 	if( !m_pID_FRAME_Title )

// 		return;

// }

// ListImg / ListEx
bool CUI_ID_FRAME_Title::ID_LISTIMG_BuffOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													 ControlIconDrag::S_ListImg* pItemDrag,
													 ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_Title::ID_LISTIMG_BuffOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Title::ID_LISTIMG_BuffOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Title::ID_LISTIMG_BuffOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

// 装载UI
bool CUI_ID_FRAME_Title::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Title.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Title.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
static void Title_VisableChanged(ControlObject* pObject)
{
	if ( s_CUI_ID_FRAME_Title.GetFrame() && s_CUI_ID_FRAME_Title.GetFrame()->IsVisable() )
	{
		if( s_CUI_ID_FRAME_Title.GetLIST_TitleList() && 
			s_CUI_ID_FRAME_Title.GetLIST_TitleList()->GetCurSelIndex() == -1 )
		{
			s_CUI_ID_FRAME_Title.GetLIST_TitleList()->SetCurSelIndex( 1 );
			s_CUI_ID_FRAME_Title.GetLIST_TitleList()->SetScrollValue( 0 );
		}
	}
}
// 关连控件
bool CUI_ID_FRAME_Title::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Title, s_CUI_ID_FRAME_TitleOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Title, s_CUI_ID_FRAME_TitleOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_Title, ID_BUTTON_HideTitle, s_CUI_ID_FRAME_TitleID_BUTTON_HideTitleOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_Title, ID_LIST_TitleList, s_CUI_ID_FRAME_TitleID_LIST_TitleListOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_Title, ID_BUTTON_ShowTitle, s_CUI_ID_FRAME_TitleID_BUTTON_ShowTitleOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_Title, ID_LIST_Property, s_CUI_ID_FRAME_TitleID_LIST_PropertyOnListSelectChange );
	//theUiManager.OnListSelectChange( ID_FRAME_Title, ID_LIST_NextProperty, s_CUI_ID_FRAME_TitleID_LIST_NextPropertyOnListSelectChange );
	theUiManager.OnEditEnter( ID_FRAME_Title, ID_EDIT_MOOD, s_CUI_ID_FRAME_TitleID_EDIT_MOODOnEditEnter );
	theUiManager.OnComboBoxChange( ID_FRAME_Title, ID_COMBOBOX_MOOD_TITLE, s_CUI_ID_FRAME_TitleID_COMBOBOX_MOOD_TITLEOnComboBoxChange );
	theUiManager.OnButtonClick( ID_FRAME_Title, ID_BUTTON_MODIFY_MOOD, s_CUI_ID_FRAME_TitleID_BUTTON_MODIFY_MOODOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_Title, ID_LISTIMG_Buff, s_CUI_ID_FRAME_TitleID_LISTIMG_BuffOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Title, ID_LISTIMG_Buff, s_CUI_ID_FRAME_TitleID_LISTIMG_BuffOnIconLDBClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Title, ID_LISTIMG_Buff, s_CUI_ID_FRAME_TitleID_LISTIMG_BuffOnIconRButtonUp );
	theUiManager.OnIconButtonClick( ID_FRAME_Title, ID_LISTIMG_Buff, s_CUI_ID_FRAME_TitleID_LISTIMG_BuffOnIconButtonClick );

	m_pID_FRAME_Title = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Title );
	m_pID_TEXT_Explain = (ControlText*)theUiManager.FindControl( ID_FRAME_Title, ID_TEXT_Explain );
	m_pID_BUTTON_HideTitle = (ControlButton*)theUiManager.FindControl( ID_FRAME_Title, ID_BUTTON_HideTitle );
	m_pID_LIST_TitleList = (ControlList*)theUiManager.FindControl( ID_FRAME_Title, ID_LIST_TitleList );
	m_pID_BUTTON_ShowTitle = (ControlButton*)theUiManager.FindControl( ID_FRAME_Title, ID_BUTTON_ShowTitle );
	m_pID_LIST_Property = (ControlList*)theUiManager.FindControl( ID_FRAME_Title, ID_LIST_Property );
// 	m_pID_LIST_NextProperty = (ControlList*)theUiManager.FindControl( ID_FRAME_Title, ID_LIST_NextProperty );	
// 	m_pID_TEXT_NextExplain = (ControlText*)theUiManager.FindControl( ID_FRAME_Title, ID_TEXT_NextExplain );
// 	m_pID_TEXT_NextTitle = (ControlText*)theUiManager.FindControl( ID_FRAME_Title, ID_TEXT_NextTitle );
	m_pID_EDIT_MOOD = (ControlEdit*)theUiManager.FindControl( ID_FRAME_Title, ID_EDIT_MOOD );
	m_pID_COMBOBOX_MOOD_TITLE = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_Title, ID_COMBOBOX_MOOD_TITLE );
	m_pID_BUTTON_MODIFY_MOOD = (ControlButton*)theUiManager.FindControl( ID_FRAME_Title, ID_BUTTON_MODIFY_MOOD );
	m_pID_LISTIMG_Buff = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Title, ID_LISTIMG_Buff );

	assert( m_pID_FRAME_Title );
	assert( m_pID_TEXT_Explain );
	assert( m_pID_BUTTON_HideTitle );
	assert( m_pID_LIST_TitleList );
	assert( m_pID_BUTTON_ShowTitle );
// 	assert( m_pID_LIST_Property );
// 	assert( m_pID_LIST_NextProperty );	
	assert( m_pID_EDIT_MOOD );
	assert( m_pID_COMBOBOX_MOOD_TITLE );
	assert( m_pID_BUTTON_MODIFY_MOOD );
	assert( m_pID_LISTIMG_Buff );

	//assert( m_pID_TEXT_NextExplain );
	m_pID_FRAME_Title->SetVisable( false );
	
	m_pID_LIST_Property->HaveSelBar( 0, 0 );
	m_pID_FRAME_Title->SetOnVisibleChangedFun( Title_VisableChanged );
	//m_pID_LIST_NextProperty->HaveSelBar( 0, 0 );
	//GetFrame()->SetFather(s_CUI_ID_FRAME_BaseProperty.GetFrame());
	USE_SCRIPT( eUI_OBJECT_Title, this );

	m_pID_COMBOBOX_MOOD_TITLE->GetEditInput().SetReadOnly(true);
	ControlList &lb = m_pID_COMBOBOX_MOOD_TITLE->GetListBox();
	std::string lbitems[2] = {
		theXmlString.GetString(eText_Mood),
		theXmlString.GetString(eText_Title)
	};

	ControlList::S_List stItem;
	for (int i = 0; i < 2; ++i)
	{	
		stItem.clear();
		stItem.SetData(lbitems[i].c_str(), 0);
		stItem.SetMargin(5);
		lb.AddItem(&stItem);
	}
	m_pID_COMBOBOX_MOOD_TITLE->SetCurSelIndex(0);
	m_pID_EDIT_MOOD->SetMaxLength(20);

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Title::_UnLoadUI()
{
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\Title.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Title::_IsVisable()
{
	if( !m_pID_FRAME_Title )
		return false;
	return m_pID_FRAME_Title->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Title::_SetVisable( const bool bVisable )
{
    if(!m_pID_FRAME_Title)
        return;

	m_pID_FRAME_Title->SetVisable( bVisable );
	if( bVisable )
	{
        RefreshTitleList();
		RefreshMood();
		ID_LIST_TitleListOnListSelectChange( 0, 0 );

		if (m_pID_EDIT_MOOD->IsVisable())
		{
			theUiManager.SetFocus(m_pID_EDIT_MOOD);
			ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );
		}
	}
	else
	{
		if (m_pID_EDIT_MOOD->IsVisable())
		{
			ImmAssociateContext( g_hWnd, NULL );
		}
	}
}

void CUI_ID_FRAME_Title::Refresh()
{
	if( !m_pID_FRAME_Title )
		return;

	RefreshMood();

	// 刷新下拉框, 显示心情和称号是互斥的
	bool isShowMood = theHeroGame.GetPlayerMgr()->GetMe()->IsShowSignature();
	if (isShowMood)
		m_pID_COMBOBOX_MOOD_TITLE->SetCurSelIndex(0);
	else
		m_pID_COMBOBOX_MOOD_TITLE->SetCurSelIndex(1);

	RefreshTitleList();
}

TitleConfig::Title* CUI_ID_FRAME_Title::GetCurrentSelectTitle()
{
	if( !m_pID_FRAME_Title )
		return NULL;
	ControlList::S_List* pSelectItem = m_pID_LIST_TitleList->GetCurSelItem();
	if( !pSelectItem )
		return 0;
	TitleConfig::Title* pTitle = theTitleConfig.GetTitleByTitleID( pSelectItem->m_nID );
	if( !pTitle )
		return 0;

	return pTitle;
}

bool SortTitleType( TitleConfig::Title& title1, TitleConfig::Title& title2 )
{
	if( title1.GetType() < title2.GetType() )
		return true;
	return false;
}

void CUI_ID_FRAME_Title::RefreshMood()
{
	if (m_pID_EDIT_MOOD == NULL)
		return;

	// 刷新心情
	if (strlen(thePlayerRole.GetSignature()) > 0)
		m_pID_EDIT_MOOD->SetText(thePlayerRole.GetSignature());
}

void CUI_ID_FRAME_Title::RefreshTitleList()
{
    if (m_pID_FRAME_Title == NULL)
        return;

	m_pID_LIST_TitleList->Clear();		
	m_pID_LIST_Property->Clear();
//	m_pID_LIST_NextProperty->Clear();

	const std::vector<TitleConfig::Title> vTitleList = theTitleConfig.GetTitleList();
	std::vector<TitleConfig::Title>::const_iterator iter = vTitleList.begin();
	unsigned char ucLastType = 255;
	for( ; iter != vTitleList.end() ; ++ iter )
	{
		TitleConfig::Title* pTitle = theTitleConfig.GetTitleByTitleID( (*iter).GetID() );
		if (pTitle == NULL)
			continue;

		// 添加到ui
		AddToTitleList( (void*)pTitle, ucLastType );
		ucLastType = pTitle->GetType();
	}
	
	int curTitleID = theHeroGame.GetPlayerMgr()->GetMe()->GetTitleId();
	if (curTitleID > 0)
		m_pID_LIST_TitleList->SetCurSelIndex( curTitleID );
	else
		m_pID_LIST_TitleList->SetCurSelIndex( 0 );
	m_pID_LIST_TitleList->SetScrollValue( 0 );
}

void CUI_ID_FRAME_Title::RefreshTitleDesc( ControlObject* pDescUi, TitleConfig::Title* pTitle, bool bShowName /* = false */ )
{		
	if( !pDescUi )
		return;

	ControlText* pDescTextUi = ( ControlText* )pDescUi;
	if( !pTitle )
		return;		

	char szBuff[MAX_PATH] = {0};
// 	if( bShowName )
// 	{	
// 		MeSprintf_s( szBuff, sizeof(szBuff)/sizeof(char) - 1, "%s {#%x=%s#}",theXmlString.GetString( eTitle_NextTitleName ), pTitle->dwColor, pTitle->GetName() );
// 		m_pID_TEXT_NextTitle->SetText( szBuff );
// 	}

	if(pTitle->GetType() == TitleConfig::Title_Marriage)
    {  
        // %s于%d年%d月%d日%d时与%s结为相伴一生的夫妻
        TitleData* pTitleData = IsHaveExistTitle(pTitle);
        if(!pTitleData)
            return;

        const char* pszMarryName = thePlayerRole.GetMarryerName();
        if(pszMarryName != NULL)
        { 
            TimeEx timeFormat(pTitleData->GetAcquireTime());

            char szTitleDesc[256];
            MeSprintf_s(szTitleDesc,sizeof(szTitleDesc) / sizeof(char) - 1,pTitle->GetDescription(),thePlayerRole.GetName(),
                timeFormat.GetYear(),timeFormat.GetMonth(),timeFormat.GetDay(),timeFormat.GetDay(),pszMarryName);

            pDescTextUi->SetText(szTitleDesc);
        }
    }
    else
    {
        pDescTextUi->SetText( pTitle->GetDescription() );	
    }
}

void CUI_ID_FRAME_Title::RefreshTitleProp( ControlObject* pPropertyUi, TitleConfig::Title* pTitle )
{
	if( !pPropertyUi )
		return;

	ControlList* pPropList = ( ControlList* )pPropertyUi;
	if( !pTitle )
		return;	
	ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus( pTitle->GetStatusID(), pTitle->GetStatusLevel() );
	if( !pStatus )
		return;

 	DWORD dwTextColor = 0xffffffff;

    if(IsHaveExistTitle(pTitle))
        dwTextColor = 0xffffffff;

	char szBuffer[256] = {0};
    for (int i=0; i<EBaseAttr_MaxSize; i++ )
	{
		if( pStatus->stAddBaseAttr[i] == 0 )
			continue;

		if( pStatus->stAddBaseAttr[i] > 0 )
		{
			MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1, "%s: %s%d \n",				
				theXmlString.GetString( eTip_sAddStrength + i ),
				"+", pStatus->stAddBaseAttr[i]  );
			ControlList::S_List sItem;
			sItem.SetData( szBuffer );
			sItem.setColor( dwTextColor );
			pPropList->AddItem( &sItem );
		}
	}
	if( pStatus->stChanged_HPMax != 0 )
	{
		if( pStatus->stChanged_HPMax > 0 )
		{

			MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1, "%s: %s%d\n",
				theXmlString.GetString(eUI_stChanged_HPMax),
				"+", (INT)pStatus->stChanged_HPMax );

		}
		else
		{

			MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1, "%s: %d \n",
				theXmlString.GetString(eUI_stChanged_HPMax),
				(INT)pStatus->stChanged_HPMax );

		}
		ControlList::S_List sItem;
		sItem.SetData( szBuffer );
		sItem.setColor( dwTextColor );
		pPropList->AddItem( &sItem );
	}
	if( pStatus->fAddExpMul != 0 )
	{
		if( pStatus->fAddExpMul > 0 )
		{

			MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1 ,"%s: %s%d%%\n",
				theXmlString.GetString( eTip_sAddExpPer ),
				"+", (int)( pStatus->fAddExpMul * 100 ) );


		}
		else
		{

			MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1, "%s: %d%%\n",
				theXmlString.GetString( eTip_sAddExpPer ),
				"-",
				(int)( pStatus->fAddExpMul * 100 ));


		}
		ControlList::S_List sItem;
		sItem.SetData( szBuffer );
		sItem.setColor( dwTextColor );
		pPropList->AddItem( &sItem );
	}
	if( pStatus->stChanged_MPMax != 0 )
	{
		if( pStatus->stChanged_MPMax > 0 )
		{

			MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1 ,"%s: %s%d\n",
				theXmlString.GetString( eUI_stChanged_MPMax ),
				"+", (INT)pStatus->stChanged_MPMax );


		}
		else
		{

			MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1, "%s: %d\n",
				theXmlString.GetString( eUI_stChanged_MPMax ),
				(INT)pStatus->stChanged_MPMax );


		}
		ControlList::S_List sItem;
		sItem.SetData( szBuffer );
		sItem.setColor( dwTextColor );
		pPropList->AddItem( &sItem );
	}
	if( pStatus->fMoveSpeedChanged != 0 )
	{
		if( pStatus->fMoveSpeedChanged > 0 )
		{

			MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1, "%s: %s%d %%\n",
				theXmlString.GetString(eTip_sAddMoveSpeed),
				"+", (INT)(pStatus->fMoveSpeedChanged*100) );


		}
		else
		{

			MeSprintf_s( szBuffer, sizeof(szBuffer)/sizeof(char) - 1,"%s: %d %%\n",
				theXmlString.GetString(eTip_sAddMoveSpeed),
				(INT)(pStatus->fMoveSpeedChanged*100) );


		}
		ControlList::S_List sItem;
		sItem.SetData( szBuffer );
		sItem.setColor( dwTextColor );
		pPropList->AddItem( &sItem );
	}
	if( pStatus->changePhyAttack != 0 )
	{
		if( pStatus->changePhyAttack > 0 )
		{

			MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1, "%s: %s%.1f \n",
				theXmlString.GetString( eUI_ePlayAtt_Physics ),
				"+", pStatus->changePhyAttack );


		}
		else
		{

			MeSprintf_s( szBuffer, sizeof(szBuffer)/sizeof(char) - 1,"%s: %.1f \n",
				theXmlString.GetString( eUI_ePlayAtt_Physics ),
				pStatus->changePhyAttack );



		}
		ControlList::S_List sItem;
		sItem.SetData( szBuffer );
		sItem.setColor( dwTextColor );
		pPropList->AddItem( &sItem );
	}
	if( pStatus->changeMagAttack != 0 )
	{
		if( pStatus->changeMagAttack > 0 )
		{

			MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1, "%s: %s%.1f \n",
				theXmlString.GetString( eUI_ePlayAtt_Magic ),
				"+", pStatus->changeMagAttack );


		}
		else
		{

			MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1, "%s: %.1f \n",
				theXmlString.GetString( eUI_ePlayAtt_Magic ),
				pStatus->changeMagAttack );



		}
		ControlList::S_List sItem;
		sItem.SetData( szBuffer );
		sItem.setColor( dwTextColor );
		pPropList->AddItem( &sItem );
	}
	if( pStatus->changeDefend[EDefendType_Physical] != 0 )
	{
		if( pStatus->changeDefend[EDefendType_Physical] > 0 )
		{

			MeSprintf_s( szBuffer, sizeof(szBuffer)/sizeof(char) - 1,"%s: %s%.1f \n",
				theXmlString.GetString( eTip_sAddShortDefend ),
				"+", pStatus->changeDefend[EDefendType_Physical] );


		}
		else
		{

			MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1, "%s: %.1f \n",
				theXmlString.GetString( eTip_sAddShortDefend ),
				pStatus->changeDefend[EDefendType_Physical] );


		}
		ControlList::S_List sItem;
		sItem.SetData( szBuffer );
		sItem.setColor( dwTextColor );
		pPropList->AddItem( &sItem );
	}
// 	if( pStatus->changeDefend[EDefendType_Long] != 0 )
// 	{
// 		if( pStatus->changeDefend[EDefendType_Long] > 0 )
// 		{
// 
// 			MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1, "%s: %s%.1f \n",
// 				theXmlString.GetString( eTip_sAddLongDefend ),
// 				"+", pStatus->changeDefend[EDefendType_Long] );
// 
// 
// 		}
// 		else
// 		{
// 
// 			MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1, "%s: %.1f \n",
// 				theXmlString.GetString( eTip_sAddLongDefend ),
// 				pStatus->changeDefend[EDefendType_Long] );
// 
// 
// 		}
// 		ControlList::S_List sItem;
// 		sItem.SetData( szBuffer );
// 		sItem.setColor( dwTextColor );
// 		pPropList->AddItem( &sItem );
// 	}

	if( pStatus->changeDefend[EDefendType_Magic] != 0 )
	{
		if( pStatus->changeDefend[EDefendType_Magic] > 0 )
		{

			MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1, "%s: %s%.1f \n",
				theXmlString.GetString( eTip_sAddMagicDefend ),
				"+", pStatus->changeDefend[EDefendType_Magic] );


		}
		else
		{

			MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1, "%s: %.1f \n",
				theXmlString.GetString( eTip_sAddMagicDefend ),
				pStatus->changeDefend[EDefendType_Magic] );


		}
		ControlList::S_List sItem;
		sItem.SetData( szBuffer );
		sItem.setColor( dwTextColor );
		pPropList->AddItem( &sItem );
	}
	if( pStatus->stChanged_Hit != 0 )
	{
		if( pStatus->stChanged_Hit > 0 )
		{

			MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1, "%s: %s%d \n",
				theXmlString.GetString( eUI_sExact ),
				"+", (INT)pStatus->stChanged_Hit );


		}
		else
		{

			MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1, "%s: %d \n",
				theXmlString.GetString( eUI_sExact ),
				(INT)pStatus->stChanged_Hit );


		}
		ControlList::S_List sItem;
		sItem.SetData( szBuffer );
		sItem.setColor( dwTextColor );
		pPropList->AddItem( &sItem );
	}
	if( pStatus->stChanged_Hedge != 0 )
	{
		if( pStatus->stChanged_Hedge > 0 )
		{

			MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1, "%s: %s%d \n",
				theXmlString.GetString( eUI_sDodge ),
				"+", (INT)pStatus->stChanged_Hedge );


		}
		else
		{

			MeSprintf_s( szBuffer, sizeof(szBuffer)/sizeof(char) - 1,"%s: %d \n",
				theXmlString.GetString( eUI_sDodge ),
				(INT)pStatus->stChanged_Hedge );


		}
		ControlList::S_List sItem;
		sItem.SetData( szBuffer );
		sItem.setColor( dwTextColor );
		pPropList->AddItem( &sItem );
	}
	if( pStatus->resumeHP != 0 )
	{
		if( pStatus->resumeHP > 0 )
		{

			MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1, "%s: %s%d \n",
				theXmlString.GetString( eTip_sAddHPRestoreRate ),
				"+", (INT)pStatus->resumeHP );


		}
		else
		{

			MeSprintf_s( szBuffer, sizeof(szBuffer)/sizeof(char) - 1,"%s: %d \n",
				theXmlString.GetString( eTip_sAddHPRestoreRate ),
				(INT)pStatus->resumeHP );


		}
		ControlList::S_List sItem;
		sItem.SetData( szBuffer );
		sItem.setColor( dwTextColor );
		pPropList->AddItem( &sItem );
	}
	if( pStatus->resumeMP != 0 )
	{
		if( pStatus->resumeMP > 0 )
		{

			MeSprintf_s( szBuffer, sizeof(szBuffer)/sizeof(char) - 1,"%s: %s%d \n",
				theXmlString.GetString( eTip_sAddMPRestoreRate ),
				"+", (INT)pStatus->resumeMP );


		}
		else
		{

			MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1, "%s: %d \n",
				theXmlString.GetString( eTip_sAddMPRestoreRate ),
				(INT)pStatus->resumeMP );


		}
		ControlList::S_List sItem;
		sItem.SetData( szBuffer );
		sItem.setColor( dwTextColor );
		pPropList->AddItem( &sItem );
	}
// 	if( pStatus->sFightHpRestore > 0 )
// 	{
// 
// 		MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1 ,theXmlString.GetString(eText_Skill_AddRestorHP),
// 			(pStatus->sFightHpRestore)
// 			);
// 
// 
// 		ControlList::S_List sItem;
// 		sItem.SetData( szBuffer );
// 		sItem.setColor( dwTextColor );
// 		pPropList->AddItem( &sItem );
// 	}
// 	if( pStatus->sFightMpRestore > 0 )
// 	{
// 		MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1,theXmlString.GetString( eText_Skill_AddRestorMP ),
// 			(pStatus->sFightMpRestore)
// 			);
// 
// 		ControlList::S_List sItem;
// 		sItem.SetData( szBuffer );
// 		sItem.setColor( dwTextColor );
// 		pPropList->AddItem( &sItem );
// 	}
// 	if( pStatus->stPrepSpeedChanged != 0 )
// 	{
// 		if( pStatus->stPrepSpeedChanged > 0 )
// 		{
// 
// 			MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1, "%s:%d %%\n",
// 				theXmlString.GetString(eUI_stAttSpeedChanged),
// 				(INT)(-pStatus->stPrepSpeedChanged) );
// 
// 		}
// 		else
// 		{
// 
// 			MeSprintf_s( szBuffer, sizeof(szBuffer)/sizeof(char) - 1,"%s:%s%d %%\n",theXmlString.GetString(eUI_stAttSpeedChanged),
// 				"+",(int)(-pStatus->stPrepSpeedChanged) );
// 
// 		} 
// 		ControlList::S_List sItem;
// 		sItem.SetData( szBuffer );
// 		sItem.setColor( dwTextColor );
// 		pPropList->AddItem( &sItem );
// 	}
// 	if( pStatus->fAddtionTorpidResistRatio != 0 )
// 	{
// 		if( pStatus->fAddtionTorpidResistRatio > 0 )
// 		{
// 
// 			/*MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1, "%s: %s%d\n",
// 				theXmlString.GetString(eTip_sAddTorpidResist),
// 				"+", (INT)(pStatus->fAddtionTorpidResistRatio) );*/
// 
// 
// 		}
// 		else
// 		{
// 
// 			/*MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1, "%s: %d\n",
// 				theXmlString.GetString(eTip_sAddTorpidResist),
// 				(INT)(pStatus->fAddtionTorpidResistRatio) );*/
// 
// 
// 		}
// 		ControlList::S_List sItem;
// 		sItem.SetData( szBuffer );
// 		sItem.setColor( dwTextColor );
// 		pPropList->AddItem( &sItem );
// 	}
// 	if( pStatus->fAddtionSlowdownResistRatio != 0 )
// 	{
// 		if( pStatus->fAddtionSlowdownResistRatio > 0 )
// 		{
// 
// 			/*MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1 ,"%s: %s%d\n",
// 				theXmlString.GetString(eTip_sAddSlowdownResist),
// 				"+", (INT)(pStatus->fAddtionSlowdownResistRatio) );*/
// 
// 
// 		}
// 		else
// 		{
// 
// 			/*MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1, "%s: %d\n",
// 				theXmlString.GetString(eTip_sAddSlowdownResist),
// 				(INT)(pStatus->fAddtionSlowdownResistRatio) );*/
// 
// 
// 		}
// 		ControlList::S_List sItem;
// 		sItem.SetData( szBuffer );
// 		sItem.setColor( dwTextColor );
// 		pPropList->AddItem( &sItem );
// 	}
// 	if( pStatus->fAddtionStandResistRatio != 0 )
// 	{
// 		if( pStatus->fAddtionStandResistRatio > 0 )
// 		{
// 
// 			/*MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1, "%s: %s%d\n",
// 				theXmlString.GetString(eTip_sAddStandResist),
// 				"+", (INT)(pStatus->fAddtionStandResistRatio) );*/
// 
// 
// 		}
// 		else
// 		{
// 
// 			/*MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1, "%s: %d\n",
// 				theXmlString.GetString(eTip_sAddStandResist),
// 				(INT)(pStatus->fAddtionStandResistRatio) );*/
// 
// 
// 		}
// 		ControlList::S_List sItem;
// 		sItem.SetData( szBuffer );
// 		sItem.setColor( dwTextColor );
// 		pPropList->AddItem( &sItem );
// 	}
// 	if( pStatus->fAddtionGiddyResistRatio != 0 )
// 	{
// 		if( pStatus->fAddtionGiddyResistRatio > 0 )
// 		{
// 
// 			/*MeSprintf_s( szBuffer, sizeof(szBuffer)/sizeof(char) - 1,"%s: %s%d\n",
// 				theXmlString.GetString(eTip_sAddGiddyResist),
// 				"+", (INT)(pStatus->fAddtionGiddyResistRatio) );*/
// 
// 
// 		}
// 		else
// 		{
// 
// 			/*MeSprintf_s( szBuffer,sizeof(szBuffer)/sizeof(char) - 1, "%s: %d\n",
// 				theXmlString.GetString(eTip_sAddGiddyResist),
// 				(INT)(pStatus->fAddtionGiddyResistRatio) );*/
// 
// 
// 		}
// 		ControlList::S_List sItem;
// 		sItem.SetData( szBuffer );
// 		sItem.setColor( dwTextColor );
// 		pPropList->AddItem( &sItem );
// 	}
}

void CUI_ID_FRAME_Title::AddToTitleList( void* pTitleInfo, unsigned char ucLastType )
{
	TitleConfig::Title* pTitle = ( TitleConfig::Title* )pTitleInfo;
	
	if( pTitle->GetType() != ucLastType ) //新的类型
	{
		ControlList::S_List sRootItem;
		sRootItem.SetData( GetTitleTypeName( pTitle->GetType() ), -1 );
		sRootItem.m_nHiberarchy = 0;
		m_pID_LIST_TitleList->AddItem( &sRootItem );
	}
	bool bExist = false;	
    if(IsHaveExistTitle(pTitle))
		bExist = true;	
	if( !bExist )
	{
		if( pTitle->GetInvisible() )
			return;//不可见，并且玩家没有此称号，返回

		TitleConfig::Title* pCurentTitle = pTitle;
		while( pTitle->GetPrevTitleId( true ) != 0 ) // 找低级的
		{
			pTitle = theTitleConfig.GetTitleByTitleID( pTitle->GetPrevTitleId( true ) );
			if( !pTitle )
				break;
			// 拥有这个称号，所有搜索停止
            if(IsHaveExistTitle(pTitle))
				return;
		}
		pTitle = pCurentTitle;
		while( pTitle->GetNextTitleId( true ) != 0 ) // 找高级的
		{
			pTitle = theTitleConfig.GetTitleByTitleID( pTitle->GetNextTitleId( true ) );
			if( !pTitle )
				break;
			// 拥有这个称号，所有搜索停止
            if(IsHaveExistTitle(pTitle))
				return;
		}
		pTitle = pCurentTitle;
		// 可顶此称号的称号是否有已经拥有的，有就不显示此称号
		TitleConfig::Title::TitleSet titleSets = pTitle->GetBeDisplaceds();
		for( TitleConfig::Title::TitleSetIter iter = titleSets.begin(); iter != titleSets.end(); ++ iter )
		{
			pTitle = &(*iter).second;
			// 拥有这个称号，所有搜索停止
            if(IsHaveExistTitle(pTitle))
				return;
		}
		pTitle = pCurentTitle;
		// 此称号可顶的称号如果有已经拥有的，就不显示此称号
		const unsigned short* const pusDisplace = pTitle->GetDisplaceIds();
		for( int i = 0 ; i < TitleConfig::Title_Max_Displace; ++ i )
		{
			if( pusDisplace != 0 )
			{
				// 拥有这个称号，所有搜索停止
                if(IsHaveExistTitle(pTitle))
					return;
			}
		}

		// 如果都没有返回，说明没有获得此称号链中的任意称号，则判断当前称号是否为第一个称号，如果是
		// 则显示，如果不是则返回。
		if( pTitle->GetPrevTitleId() != 0 ) // 说明不是链头
			return;
	}

	DWORD dwColor = 0xffffff;
	// 如果没有得到，显示灰色	
	if( !bExist )
		dwColor = 0xff808080;
	else 
		dwColor = pTitle->dwColor;

	ControlList::S_List sItem;	
    //if(pTitle->GetID() == 10000)  //结婚称号ID
	if( pTitle->GetType() == TitleConfig::Title_Marriage )
    {
        const char* pszMarryName = thePlayerRole.GetMarryerName();

        if(pszMarryName != NULL)
        {
            char szText[256] = {0};
            if(thePlayerRole.GetSex() == 0)
                 MeSprintf_s(szText,sizeof(szText)/sizeof(char) - 1,pTitle->GetName(),pszMarryName,theXmlString.GetString(eText_MarryHusband));
            else
                 MeSprintf_s(szText,sizeof(szText)/sizeof(char) - 1,pTitle->GetName(),pszMarryName,theXmlString.GetString(eText_MarryWife));
            sItem.SetData(szText,pTitle->GetID(),0,dwColor);
        }
    }
	else if( pTitle->GetType() == TitleConfig::Title_Student)
	{
		const char* pcTeacherName = thePlayerRole.GetNameByDBID( thePlayerRole.GetTeacherDBID() );
		if( pcTeacherName )
		{
			char szText[256] = {0};
			MeSprintf_s( szText, sizeof( szText ) / sizeof( char ) - 1, pTitle->GetName(), pcTeacherName );
			sItem.SetData( szText, pTitle->GetID(), 0, dwColor );
		}
	}
    else
	     sItem.SetData( pTitle->GetName(), pTitle->GetID(), 0, dwColor );	
	sItem.m_nHiberarchy = 1;
	if( sItem.m_nID != -1 )
		m_pID_LIST_TitleList->AddItem( &sItem );
}

const char* CUI_ID_FRAME_Title::GetTitleTypeName(unsigned char ucType)
{
	return theXmlString.GetString( ucType - 1 + eTitleTypeText_JuQing );
}


TitleData* CUI_ID_FRAME_Title::IsHaveExistTitle(TitleConfig::Title* pTitle)
{
    if(!pTitle)
        return false;

    std::vector< TitleData > vCurrentTitleIds = thePlayerRole.GetTitleArray();
    std::vector<TitleData>::iterator it = vCurrentTitleIds.begin();

    for (;it != vCurrentTitleIds.end();++it)
    {
        if((*it).GetTitleID() == pTitle->GetID())
            return &(*it);
    }

    return NULL;
}

void CUI_ID_FRAME_Title::NeedRefresh()
{
    m_bNeedRefresh = true;
}

ControlList* CUI_ID_FRAME_Title::GetLIST_TitleList()
{
	if( !m_pID_FRAME_Title )
		return NULL;
	return m_pID_LIST_TitleList;
}

bool CUI_ID_FRAME_Title::EditInputIsVisable()
{
	if(m_pID_EDIT_MOOD && m_pID_FRAME_Title)
	{
		return (theUiManager.GetFocus() == m_pID_EDIT_MOOD);
	}
	return false;
}

void CUI_ID_FRAME_Title::RefreshTitleBuff( ControlObject* pBuffUi, TitleConfig::Title* pTitle )
{
	if ( !pBuffUi || !pTitle )
		return;

	ControlListImage* pImg = (ControlListImage*)pBuffUi;
	if ( !pImg )
		return;

	ItemDefine::SItemStatus* pItemStatus = NULL;
	pItemStatus = GettheItemDetail().GetStatus( pTitle->GetBuffId(), pTitle->GetBuffLevel() );

	if ( pItemStatus )
	{
		ControlIconDrag::S_ListImg stItem;
		stItem.SetData( pTitle->GetBuffId(), pTitle->GetBuffLevel(), eIcon_Enable, true, eTipFlag_Status );
		pImg->SetItem( &stItem );
	}
}