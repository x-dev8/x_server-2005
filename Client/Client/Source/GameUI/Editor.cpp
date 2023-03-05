/********************************************************************
Created by UIEditor.exe
FileName: F:\project\Turbo\Bin\Client\Data\Ui\Editor.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Editor.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "PlayerRole.h"
#include "Player.h"
#include "XmlStringLanguage.h"
#include "GlobalDef.h"
#include "RelationMessage.h"
#include "MessageBox.h"
#include "Common.h"
#include "ui/Create.h"

#include <string>

//签名的最大长度
uint32 GetMaxSignatureLen(void)
{
	return RelationDefine::MaxSignLength - 1;
}

CUI_ID_FRAME_Editor s_CUI_ID_FRAME_Editor;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Editor, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Editor, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Editor, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Editor, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Editor, ID_BUTTON_ShowOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Editor, ID_BUTTON_ConcealOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Editor, ID_CHECKBOX_ChoiceOnCheckBoxCheck )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Editor, ID_LIST_TitleListOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Editor, ID_BUTTON_SureOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Editor, ID_BUTTON_ShowTitleOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Editor, ID_BUTTON_ConcealTitleOnButtonClick )
CUI_ID_FRAME_Editor::CUI_ID_FRAME_Editor()
{
	// Member
	m_pID_FRAME_Editor = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_TitleTop = NULL;
	m_pID_TEXT_NonceName = NULL;
	m_pID_TEXT_HeartName = NULL;
	m_pID_BUTTON_Show = NULL;
	m_pID_BUTTON_Conceal = NULL;
	m_pID_TEXT_Title = NULL;
	m_pID_CHECKBOX_Choice = NULL;
	m_pID_LIST_TitleList = NULL;
	m_pID_TEXT_TitleContent = NULL;
	m_pID_BUTTON_Sure = NULL;
	m_pID_BUTTON_ShowTitle = NULL;
	m_pID_BUTTON_ConcealTitle = NULL;

}
// Frame
bool CUI_ID_FRAME_Editor::OnFrameRun()
{
	if(NULL == m_pID_FRAME_Editor)
		return false;

	return true;
}
bool CUI_ID_FRAME_Editor::OnFrameRender()
{
	if(NULL == m_pID_FRAME_Editor)
		return false;

	return true;
}
// Button
bool CUI_ID_FRAME_Editor::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_Editor::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_Editor::ID_BUTTON_ShowOnButtonClick( ControlObject* pSender )
{
	OnClickMoodButton(true);

	return true;
}
// Button
bool CUI_ID_FRAME_Editor::ID_BUTTON_ConcealOnButtonClick( ControlObject* pSender )
{
	OnClickMoodButton(false);

	return true;
}
// CheckBox
void CUI_ID_FRAME_Editor::ID_CHECKBOX_ChoiceOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	RefreshTitleList();
}
// List
void CUI_ID_FRAME_Editor::ID_LIST_TitleListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	RefreshTitleContent();
}
// Button
bool CUI_ID_FRAME_Editor::ID_BUTTON_SureOnButtonClick( ControlObject* pSender )
{
	const char *pSignature = m_pID_TEXT_HeartName->GetText();
	if(NULL == pSignature)
		return false;

	if(strlen(pSignature) > GetMaxSignatureLen())
	{
		std::string str(theXmlString.GetString(eText_Mood_Text_TooLong));
		//char buf[8] = {0};
		//sprintf(buf, "%d。", GetMaxSignatureLen());
		//str += buf;

		s_CUI_ID_FRAME_MessageBox.Show(str.c_str(), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, false);
		return false;
	}

	if(m_pID_TEXT_HeartName != NULL)
	{
		ChangeSignature(pSignature);
	}

	return true;
}
// Button
bool CUI_ID_FRAME_Editor::ID_BUTTON_ShowTitleOnButtonClick( ControlObject* pSender )
{
	OnClickTitleButton(true);

	return true;
}
// Button
bool CUI_ID_FRAME_Editor::ID_BUTTON_ConcealTitleOnButtonClick( ControlObject* pSender )
{
	OnClickTitleButton(false);

	return true;
}

// 装载UI
bool CUI_ID_FRAME_Editor::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Editor.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Editor.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Editor::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Editor, s_CUI_ID_FRAME_EditorOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Editor, s_CUI_ID_FRAME_EditorOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_Editor, ID_BUTTON_HELP, s_CUI_ID_FRAME_EditorID_BUTTON_HELPOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Editor, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_EditorID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Editor, ID_BUTTON_Show, s_CUI_ID_FRAME_EditorID_BUTTON_ShowOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Editor, ID_BUTTON_Conceal, s_CUI_ID_FRAME_EditorID_BUTTON_ConcealOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Editor, ID_CHECKBOX_Choice, s_CUI_ID_FRAME_EditorID_CHECKBOX_ChoiceOnCheckBoxCheck );
	theUiManager.OnListSelectChange( ID_FRAME_Editor, ID_LIST_TitleList, s_CUI_ID_FRAME_EditorID_LIST_TitleListOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_Editor, ID_BUTTON_Sure, s_CUI_ID_FRAME_EditorID_BUTTON_SureOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Editor, ID_BUTTON_ShowTitle, s_CUI_ID_FRAME_EditorID_BUTTON_ShowTitleOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Editor, ID_BUTTON_ConcealTitle, s_CUI_ID_FRAME_EditorID_BUTTON_ConcealTitleOnButtonClick );

	m_pID_FRAME_Editor = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Editor );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_Editor, ID_BUTTON_HELP );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_Editor, ID_BUTTON_CLOSE );
	m_pID_TEXT_TitleTop = (ControlText*)theUiManager.FindControl( ID_FRAME_Editor, ID_TEXT_TitleTop );
	m_pID_TEXT_NonceName = (ControlText*)theUiManager.FindControl( ID_FRAME_Editor, ID_TEXT_NonceName );
	m_pID_TEXT_HeartName = (ControlText*)theUiManager.FindControl( ID_FRAME_Editor, ID_TEXT_HeartName );
	m_pID_BUTTON_Show = (ControlButton*)theUiManager.FindControl( ID_FRAME_Editor, ID_BUTTON_Show );
	m_pID_BUTTON_Conceal = (ControlButton*)theUiManager.FindControl( ID_FRAME_Editor, ID_BUTTON_Conceal );
	m_pID_TEXT_Title = (ControlText*)theUiManager.FindControl( ID_FRAME_Editor, ID_TEXT_Title );
	m_pID_CHECKBOX_Choice = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Editor, ID_CHECKBOX_Choice );
	m_pID_LIST_TitleList = (ControlList*)theUiManager.FindControl( ID_FRAME_Editor, ID_LIST_TitleList );
	m_pID_TEXT_TitleContent = (ControlText*)theUiManager.FindControl( ID_FRAME_Editor, ID_TEXT_TitleContent );
	m_pID_BUTTON_Sure = (ControlButton*)theUiManager.FindControl( ID_FRAME_Editor, ID_BUTTON_Sure );
	m_pID_BUTTON_ShowTitle = (ControlButton*)theUiManager.FindControl( ID_FRAME_Editor, ID_BUTTON_ShowTitle );
	m_pID_BUTTON_ConcealTitle = (ControlButton*)theUiManager.FindControl( ID_FRAME_Editor, ID_BUTTON_ConcealTitle );
	assert( m_pID_FRAME_Editor );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_TEXT_TitleTop );
	assert( m_pID_TEXT_NonceName );
	assert( m_pID_TEXT_HeartName );
	assert( m_pID_BUTTON_Show );
	assert( m_pID_BUTTON_Conceal );
	assert( m_pID_TEXT_Title );
	assert( m_pID_CHECKBOX_Choice );
	assert( m_pID_LIST_TitleList );
	assert( m_pID_TEXT_TitleContent );
	assert( m_pID_BUTTON_Sure );
	assert( m_pID_BUTTON_ShowTitle );
	assert( m_pID_BUTTON_ConcealTitle );

	SetVisable(false);

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Editor::_UnLoadUI()
{
	m_pID_FRAME_Editor = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_TitleTop = NULL;
	m_pID_TEXT_NonceName = NULL;
	m_pID_TEXT_HeartName = NULL;
	m_pID_BUTTON_Show = NULL;
	m_pID_BUTTON_Conceal = NULL;
	m_pID_TEXT_Title = NULL;
	m_pID_CHECKBOX_Choice = NULL;
	m_pID_LIST_TitleList = NULL;
	m_pID_TEXT_TitleContent = NULL;
	m_pID_BUTTON_Sure = NULL;
	m_pID_BUTTON_ShowTitle = NULL;
	m_pID_BUTTON_ConcealTitle = NULL;

	return theUiManager.RemoveFrame( "Data\\UI\\Editor.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Editor::_IsVisable()
{
	if(NULL == m_pID_FRAME_Editor)
		return false;

	return m_pID_FRAME_Editor->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Editor::_SetVisable( const bool bVisable )
{
	if(NULL == m_pID_FRAME_Editor)
		return;

	m_pID_FRAME_Editor->SetVisable( bVisable );

	if(IsVisable())
	{
		Refresh();

		theUiManager.SetFocus(m_pID_TEXT_HeartName);
		//激活中文输入
		ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );
	}
	else
	{
		ImmAssociateContext( g_hWnd, NULL);
	}
}

void CUI_ID_FRAME_Editor::Refresh(void)
{
	//当前头顶信息
	RefreshHeadInfo();

	//心情
	RefreshMoodText();

	RefreshTitleList();

	RefreshButtonState();
}

void CUI_ID_FRAME_Editor::RefreshHeadInfo(void)
{
	if(NULL == m_pID_TEXT_NonceName)
		return;

	m_pID_TEXT_NonceName->Clear();

	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();

	if(pMe->IsShowSignature())
	{
		m_pID_TEXT_NonceName->SetText(pMe->GetSignature());
	}
	else if(pMe->GetTitleId() > 0)
	{
		m_pID_TEXT_NonceName->SetText(pMe->GetTitle());
	}

}

void CUI_ID_FRAME_Editor::RefreshMoodText(void)
{
	if(NULL == m_pID_TEXT_HeartName)
		return;

	m_pID_TEXT_HeartName->Clear();
	if(thePlayerRole.GetSignature())
		m_pID_TEXT_HeartName->SetText(thePlayerRole.GetSignature());
}

void CUI_ID_FRAME_Editor::RefreshTitleList(void)
{
	if(NULL == m_pID_LIST_TitleList)
		return;

	ShowAllTitle(IsShowAllTitle());
	RefreshTitleContent();
}

TitleConfig::Title *CUI_ID_FRAME_Editor::GetCurrentSelectedTitle()
{
	if(NULL == m_pID_LIST_TitleList)
		return NULL;

	ControlList::S_List* pSelectItem = m_pID_LIST_TitleList->GetCurSelItem();
	if( !pSelectItem )
		return NULL;

	TitleConfig::Title *pTitle = theTitleConfig.GetTitleByTitleID( pSelectItem->m_nID );

	return pTitle;
}

const char *CUI_ID_FRAME_Editor::GetTitleTypeName(unsigned char ucType)
{
	return theXmlString.GetString( ucType - 1 + eTitleTypeText_JuQing );
}

void CUI_ID_FRAME_Editor::RefreshTitleContent(void)
{
	TitleConfig::Title *pTitle = GetCurrentSelectedTitle();
	if(pTitle != NULL)
	{
		RefreshTitleContent(pTitle);
	}
}

void CUI_ID_FRAME_Editor::RefreshTitleContent(const TitleConfig::Title *pTitle_)
{
	if(NULL == m_pID_TEXT_TitleContent)
		return;

	m_pID_TEXT_TitleContent->Clear();

	if(NULL == pTitle_)
		return;

	char szBuff[MAX_PATH] = {0};
	if(pTitle_->GetType() == TitleConfig::Title_Marriage)
	{  
		// %s于%d年%d月%d日%d时与%s结为相伴一生的夫妻
		const TitleData* pTitleData = GetTitleData(pTitle_);
		if(!pTitleData)
			return;

		const char* pszMarryName = thePlayerRole.GetMarryerName();
		if(pszMarryName != NULL)
		{ 
			TimeEx timeFormat(pTitleData->GetAcquireTime());

			char szTitleDesc[256];
			MeSprintf_s(szTitleDesc,sizeof(szTitleDesc) / sizeof(char) - 1,pTitle_->GetDescription(),thePlayerRole.GetName(),
				timeFormat.GetYear(),timeFormat.GetMonth(),timeFormat.GetDay(),timeFormat.GetDay(),pszMarryName);

			m_pID_TEXT_TitleContent->SetText(szTitleDesc);
		}
	}
	else
	{
		m_pID_TEXT_TitleContent->SetText( pTitle_->GetDescription() );	
	}
}

bool CUI_ID_FRAME_Editor::IsShowAllTitle(void)
{
	if(m_pID_CHECKBOX_Choice != NULL && m_pID_CHECKBOX_Choice->IsChecked())
		return false;

	return true;
}

const TitleData *CUI_ID_FRAME_Editor::GetTitleData(const TitleConfig::Title *pTitle_)
{
	if(!pTitle_)
		return NULL;

	const std::vector< TitleData > &vCurrentTitleIds = thePlayerRole.GetTitleArray();
	for (std::vector<TitleData>::const_iterator it = vCurrentTitleIds.begin();it != vCurrentTitleIds.end();++it)
	{
		if((*it).GetTitleID() == pTitle_->GetID())
			return &(*it);
	}

	return NULL;
}

bool CUI_ID_FRAME_Editor::IsActiveTitle(const TitleConfig::Title *pTitle_)
{
	if(!pTitle_)
		return false;

	const std::vector< TitleData > &vCurrentTitleIds = thePlayerRole.GetTitleArray();
	for (std::vector<TitleData>::const_iterator it = vCurrentTitleIds.begin();it != vCurrentTitleIds.end();++it)
	{
		if((*it).GetTitleID() == pTitle_->GetID())
			return true;
	}

	return false;
}

void CUI_ID_FRAME_Editor::ShowAllTitle(bool bShowAll)
{
	if(NULL == m_pID_LIST_TitleList)
		return;

	m_pID_LIST_TitleList->Clear();		

	const std::vector<TitleConfig::Title> &vTitleList = theTitleConfig.GetTitleList();
	std::vector<TitleConfig::Title>::const_iterator iter = vTitleList.begin();
	unsigned char ucLastType = 255;
	if(bShowAll)
	{
		for( ; iter != vTitleList.end() ; ++ iter )
		{
			TitleConfig::Title* pTitle = theTitleConfig.GetTitleByTitleID( (*iter).GetID() );
			if( !pTitle )
				continue;	

			AddToTitleList( (void*)pTitle, ucLastType );
			ucLastType = pTitle->GetType();
		}
	}
	else
	{
		for( ; iter != vTitleList.end() ; ++ iter )
		{
			TitleConfig::Title* pTitle = theTitleConfig.GetTitleByTitleID( (*iter).GetID() );
			if( !pTitle || !IsActiveTitle(pTitle))
				continue;	

			AddToTitleList( (void*)pTitle, ucLastType );
			ucLastType = pTitle->GetType();
		}
	}

	m_pID_LIST_TitleList->SetCurSelIndex( 0 );
	m_pID_LIST_TitleList->SetScrollValue( 0 );
}

// void CUI_ID_FRAME_Editor::ShowActiveTitle(void)
// {
// 
// }

void CUI_ID_FRAME_Editor::AddToTitleList( void* pTitleInfo, unsigned char ucLastType )
{
	if(NULL == m_pID_LIST_TitleList)
		return;

	TitleConfig::Title* pTitle = ( TitleConfig::Title* )pTitleInfo;

	if( pTitle->GetType() != ucLastType ) //新的类型
	{
		ControlList::S_List sRootItem;
		sRootItem.SetData( GetTitleTypeName( pTitle->GetType() ), -1 );
		sRootItem.m_nHiberarchy = 0;
		m_pID_LIST_TitleList->AddItem( &sRootItem );
	}
	bool bExist = false;	
	if(IsActiveTitle(pTitle))
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
			if(IsActiveTitle(pTitle))
				return;
		}
		pTitle = pCurentTitle;
		while( pTitle->GetNextTitleId( true ) != 0 ) // 找高级的
		{
			pTitle = theTitleConfig.GetTitleByTitleID( pTitle->GetNextTitleId( true ) );
			if( !pTitle )
				break;
			// 拥有这个称号，所有搜索停止
			if(IsActiveTitle(pTitle))
				return;
		}
		pTitle = pCurentTitle;
		// 可顶此称号的称号是否有已经拥有的，有就不显示此称号
		TitleConfig::Title::TitleSet titleSets = pTitle->GetBeDisplaceds();
		for( TitleConfig::Title::TitleSetIter iter = titleSets.begin(); iter != titleSets.end(); ++ iter )
		{
			pTitle = &(*iter).second;
			// 拥有这个称号，所有搜索停止
			if(IsActiveTitle(pTitle))
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
				if(IsActiveTitle(pTitle))
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

bool CUI_ID_FRAME_Editor::EditInputIsVisable()
{
	if(m_pID_FRAME_Editor)
		return m_pID_TEXT_HeartName == theUiManager.GetFocus();
	return false;
}

void CUI_ID_FRAME_Editor::OnClickTitleButton(bool bShow)
{
	//必须先送这个消息，否则还是显示心情
	SendMoodMsg(false);
	theHeroGame.GetPlayerMgr()->GetMe()->ShowSignature(false);

	//这个消息发出去后自己会收到一个回复消息，后续处理在那里进行
	SendTitleMsg(bShow);	
}

void CUI_ID_FRAME_Editor::OnClickMoodButton(bool bShow)
{
	//theHeroGame.GetPlayerMgr()->GetMe()->SetSignature(thePlayerRole.GetSignature());
	theHeroGame.GetPlayerMgr()->GetMe()->ShowSignature(bShow);
	
	//这个消息自己是不会收到回复消息的，因此后续处理直接在这里进行
	SendMoodMsg(bShow);

	RefreshHeadInfo();
	RefreshButtonState();

/*
	if(bShow)
	{
		//发送隐藏title的消息
		SendTitleMsg(false);
	}
*/
}

void CUI_ID_FRAME_Editor::SendTitleMsg(bool bShow)
{
	MsgChangeTitleReq msg;
	if(!bShow)
	{
		msg.nTitleID = 0;
	}
	else
	{
		TitleConfig::Title* pTitle = GetCurrentSelectedTitle();
		if(NULL == pTitle || !IsActiveTitle(pTitle))
			return;

		msg.nTitleID = pTitle->GetID();
	}

	GettheNetworkInput().SendMsg(&msg,msg.GetLength() );
}

void CUI_ID_FRAME_Editor::SendMoodMsg(bool bShow)
{
	MsgShowSignature msg;
	msg.showSignature = bShow;
	if(bShow)
	{
		//隐藏title
		SendTitleMsg(false);

		MeSprintf_s(msg.szSignature, sizeof(msg.szSignature) / sizeof(char) - 1, "%s", thePlayerRole.GetSignature());
	}

	GettheNetworkInput().SendMsg(&msg);
}

void CUI_ID_FRAME_Editor::ChangeSignature(const char *pContent_)
{
	if(NULL == pContent_)
		return;

	MsgChangeSignatureReq Req;
	strcpy_s(Req.szSignature, /*GetMaxSignatureLen(), */pContent_);
	GettheNetworkInput().SendMsg( &Req );

	thePlayerRole.SetSignature(pContent_);
	RefreshMoodText();
}

void CUI_ID_FRAME_Editor::RefreshButtonState(void)
{
	//显示心情和显示title目前是互斥的

	if(theHeroGame.GetPlayerMgr()->GetMe()->IsShowSignature())
	{
		SetMoodButton(false);
		SetTitleButton(true);
	}
	else if(theHeroGame.GetPlayerMgr()->GetMe()->GetTitleId() != 0)
	{
		SetMoodButton(true);
		SetTitleButton(false);
	}
	else
	{
		SetMoodButton(true);
		SetTitleButton(true);
	}
}

void CUI_ID_FRAME_Editor::SetMoodButton(bool bShow)
{
	if(m_pID_BUTTON_Show != NULL)
		m_pID_BUTTON_Show->SetVisable(bShow);

	if(m_pID_BUTTON_Conceal != NULL)
		m_pID_BUTTON_Conceal->SetVisable(!bShow);
}

void CUI_ID_FRAME_Editor::SetTitleButton(bool bShow)
{
	if(m_pID_BUTTON_ShowTitle != NULL)
		m_pID_BUTTON_ShowTitle->SetVisable(bShow);

	if(m_pID_BUTTON_ConcealTitle != NULL)
		m_pID_BUTTON_ConcealTitle->SetVisable(!bShow);

}
