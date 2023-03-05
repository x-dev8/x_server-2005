/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\游戏设置UI\keyset.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ui/customShortcutKey.h"
#include "GameMain.h"
#include "../color_config.h"
#include "ChatInfoBox.h"
#include "XmlStringLanguage.h"
#include "core/Name.h"
#include "Main.h"
#include "exmain.h"
#include <Dxsdk/dinput.h>
#include "MainMenu.h"
#include "Common.h"
#include "SettingEffect.h"
#include "GameSettingBgFrame.h"
extern GAME_STATE	g_GameState;

extern short GetKeyboardInput(int iKey);

CUI_ID_FRAME_custom s_CUI_ID_FRAME_custom;
MAP_FRAME_RUN( s_CUI_ID_FRAME_custom, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_custom, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_custom, ID_BUTTON_defaultOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_custom, ID_BUTTON_sureOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_custom, ID_BUTTON_cancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_custom, ID_BUTTON_closeOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_custom, ID_BUTTON_helpOnButtonClick )
//MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_custom, ID_LIST_KeyListOnListSelectChange )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_custom, ID_CHECKBOX_KeyOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_custom, ID_CHECKBOX_GongNengCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_custom, ID_CHECKBOX_CaoZuoCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_custom, ID_CHECKBOX_KuaiJieJianCheck )
MAP_SCROLL_BAR_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_custom, ID_SCROLLBAR_KeyListOnScrollBarUpdatePos )
CUI_ID_FRAME_custom::CUI_ID_FRAME_custom()
{
	// Member
	m_pID_FRAME_custom = NULL;
	m_pID_PICTURE_grounding = NULL;
	m_pID_PICTURE_title_pattern = NULL;
	m_pID_PICTURE_title = NULL;
	m_pID_PICTURE_pattern = NULL;
	m_pID_PICTURE_pattern2 = NULL;
	m_pID_BUTTON_default = NULL;
	m_pID_BUTTON_sure = NULL;
	m_pID_BUTTON_cancel = NULL;
	m_pID_TEXT_function = NULL;
	m_pID_BUTTON_close = NULL;
	m_pID_BUTTON_help = NULL;
	//m_pID_LIST_KeyList = NULL;
	m_pID_SCROLLBAR_KeyList = NULL;

	m_nSelectedKey = -1;


}
// Frame
bool CUI_ID_FRAME_custom::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_custom::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_custom::ID_BUTTON_defaultOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if(!m_pID_FRAME_custom)
	{
		assert(false&&"ui error");
		return false;
	}

	_tempSaveKeyInfo.clear();
	std::map<int, AN_Configure_ShortcutKey::shortcutKeyValue> keyInfo = g_shortcutKey_configure.getDefaultCustomkeyMap();
	std::map<int, AN_Configure_ShortcutKey::shortcutKeyValue>::iterator iter =  keyInfo.begin();
	for( ; iter != keyInfo.end(); ++iter )
	{
		_tempSaveKeyInfo[iter->first]= iter->second;//s_CUI_ID_FRAME_custom.setTempSaveKeyInfoItem( iter->first, iter->second._szDefault.c_str() );
	}
	s_CUI_ID_FRAME_custom.updateSelectedKeyInfo();
	return true;
	unguard;
}
// Button
bool CUI_ID_FRAME_custom::ID_BUTTON_sureOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if(!m_pID_FRAME_custom)
	{
		assert(false&&"ui error");
		return false;
	}

	g_shortcutKey_configure.hasChangeCustomKey();
	SetVisable(false);
	s_CUI_ID_FRAME_GameSettingBgFrame._SetVisable(false);
	s_CUI_ID_FRAME_MAIN.RefeashHotKey();
	s_CUI_ID_FRAME_Exmain.RefeashHotNumber();

	s_CUI_ID_FRAME_MainMenu.refreshHotKey();

	return true;
	unguard;
}
// Button
bool CUI_ID_FRAME_custom::ID_BUTTON_cancelOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if(!m_pID_FRAME_custom)
	{
		assert(false&&"ui error");
		return false;
	}

	s_CUI_ID_FRAME_custom.initTempKeyInfo();
	s_CUI_ID_FRAME_custom.SetVisable( false );
	s_CUI_ID_FRAME_GameSettingBgFrame._SetVisable(false);
	return true;
	unguard
}
// Button
bool CUI_ID_FRAME_custom::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_custom::ID_BUTTON_closeOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if(!m_pID_FRAME_custom)
	{
		assert(false&&"ui error");
		return false;
	}

	s_CUI_ID_FRAME_custom.initTempKeyInfo();
	//s_CUI_ID_FRAME_custom.SetVisable( false );
	return true;
	unguard;
}
// List
// void CUI_ID_FRAME_custom::ID_LIST_KeyListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
// {
// 	guardfunc;
// 	if(!m_pID_FRAME_custom)
// 	{
// 		assert(false&&"ui error");
// 		return ;
// 	}
// 
// 	m_pID_SCROLLBAR_KeyList->SetValue(0);
// 	m_nSelectedKey = -1;
// 	m_pID_TEXT_function->SetText("");
// 	updateSelectedKeyInfo();
// 	unguard;
// }
void CUI_ID_FRAME_custom::ID_CHECKBOX_CaoZuoCheck(ControlObject* pSender, bool* pbChecked)
{
	if (!m_pID_FRAME_custom)
	{
		return;
	}
	if (*pbChecked)
	{
		m_pID_CHECKBOX_CaoZuo->SetCheck(true);
		m_pID_CHECKBOX_GongNeng->SetCheck(false);
		m_pID_CHECKBOX_KuaiJieJian->SetCheck(false);
	}
	m_pID_SCROLLBAR_KeyList->SetValue(0);
	m_nSelectedKey = -1;
	m_pID_TEXT_function->SetText("");
	updateSelectedKeyInfo();
}
void CUI_ID_FRAME_custom::ID_CHECKBOX_GongNengCheck(ControlObject* pSender, bool* pbChecked)
{
	if (!m_pID_FRAME_custom)
	{
		return;
	}
	if (*pbChecked)
	{
		m_pID_CHECKBOX_CaoZuo->SetCheck(false);
		m_pID_CHECKBOX_GongNeng->SetCheck(true);
		m_pID_CHECKBOX_KuaiJieJian->SetCheck(false);
	}
	m_pID_SCROLLBAR_KeyList->SetValue(0);
	m_nSelectedKey = -1;
	m_pID_TEXT_function->SetText("");
	updateSelectedKeyInfo();
}
void CUI_ID_FRAME_custom::ID_CHECKBOX_KuaiJieJianCheck(ControlObject* pSender, bool* pbChecked)
{
	if (!m_pID_FRAME_custom)
	{
		return;
	}
	if (*pbChecked)
	{
		m_pID_CHECKBOX_CaoZuo->SetCheck(false);
		m_pID_CHECKBOX_GongNeng->SetCheck(false);
		m_pID_CHECKBOX_KuaiJieJian->SetCheck(true);
	}
	m_pID_SCROLLBAR_KeyList->SetValue(0);
	m_nSelectedKey = -1;
	m_pID_TEXT_function->SetText("");
	updateSelectedKeyInfo();
}
// CheckBox
void CUI_ID_FRAME_custom::ID_CHECKBOX_KeyOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_custom)
	{
		assert(false&&"ui error");
		return ;
	}

// 	ControlList::S_List* pItem = s_CUI_ID_FRAME_custom.m_pID_LIST_KeyList->GetCurSelItem();
// 	if( !pItem )
// 		return;

	if (*pbChecked)
	{
		for (int j = 0; j < m_pID_CHECKBOX_KeyList.size(); ++j)
		{
			if (pSender == m_pID_CHECKBOX_KeyList[j])
			{
				m_pID_CHECKBOX_KeyList[j]->SetCheck(true);

				const std::map<std::string, std::vector<int> >& typeIdMap = g_shortcutKey_configure.getTypeIdMap();
				std::map<std::string, std::vector<int> >::const_iterator it = typeIdMap.find(GetCheckString()/*pItem->m_szText*/);

				if (it != typeIdMap.end())
				{
					const std::vector<int>& keys = it->second;
					int startIndex = m_pID_SCROLLBAR_KeyList->GetValue();

					if (startIndex + j < keys.size())
					{
						m_nSelectedKey = keys[startIndex + j];

						char buf[256];
						MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1, theXmlString.GetString(eClient_SetHotKey),
							_tempSaveKeyInfo[m_nSelectedKey]._szDiscription.c_str());
						m_pID_TEXT_function->SetText(buf);
					}
				}
			}
			else
				m_pID_CHECKBOX_KeyList[j]->SetCheck(false);
		}
	}
	else
	{
		m_nSelectedKey = -1;
		m_pID_TEXT_function->SetText("");
		for (int i = 0; i < m_pID_CHECKBOX_KeyList.size(); ++i)
		{
			m_pID_CHECKBOX_KeyList[i]->SetCheck(false);
		}
	}
}
// ScrollBar
void CUI_ID_FRAME_custom::ID_SCROLLBAR_KeyListOnScrollBarUpdatePos( ControlObject* pSender, int n )
{
	if(!m_pID_FRAME_custom)
	{
		assert(false&&"ui error");
		return ;
	}

	updateSelectedKeyInfo();
}

// 装载UI
bool CUI_ID_FRAME_custom::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SettingKey.MEUI");
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SettingKey.MEUI]失败")
			return false;
	}
// 	else if ( dwResult != 1/*文件版本号*/ )
// 	{
// 		MESSAGE_BOX("读取文件[Data\\UI\\customShortcutKey.MEUI]与源代码版本不一样")
// 	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_custom::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_custom, s_CUI_ID_FRAME_customOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_custom, s_CUI_ID_FRAME_customOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_custom, ID_BUTTON_default, s_CUI_ID_FRAME_customID_BUTTON_defaultOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_custom, ID_BUTTON_sure, s_CUI_ID_FRAME_customID_BUTTON_sureOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_custom, ID_BUTTON_cancel, s_CUI_ID_FRAME_customID_BUTTON_cancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_custom, ID_BUTTON_help, s_CUI_ID_FRAME_customID_BUTTON_helpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_custom, ID_BUTTON_close, s_CUI_ID_FRAME_customID_BUTTON_closeOnButtonClick );
	//theUiManager.OnListSelectChange( ID_FRAME_custom, ID_LIST_KeyList, s_CUI_ID_FRAME_customID_LIST_KeyListOnListSelectChange );
	theUiManager.OnScrollBarUpdatePos( ID_FRAME_custom, ID_SCROLLBAR_KeyList, s_CUI_ID_FRAME_customID_SCROLLBAR_KeyListOnScrollBarUpdatePos );
	theUiManager.OnCheckBoxCheck(ID_FRAME_custom,ID_CHECKBOX_GongNeng,s_CUI_ID_FRAME_customID_CHECKBOX_GongNengCheck);
	theUiManager.OnCheckBoxCheck(ID_FRAME_custom,ID_CHECKBOX_CaoZuo,s_CUI_ID_FRAME_customID_CHECKBOX_CaoZuoCheck);
	theUiManager.OnCheckBoxCheck(ID_FRAME_custom,ID_CHECKBOX_KuaiJieJian,s_CUI_ID_FRAME_customID_CHECKBOX_KuaiJieJianCheck);

	m_pID_FRAME_custom = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_custom );
	m_pID_PICTURE_grounding = (ControlPicture*)theUiManager.FindControl( ID_FRAME_custom, ID_PICTURE_grounding );
	m_pID_PICTURE_title_pattern = (ControlPicture*)theUiManager.FindControl( ID_FRAME_custom, ID_PICTURE_title_pattern );
	m_pID_PICTURE_title = (ControlPicture*)theUiManager.FindControl( ID_FRAME_custom, ID_PICTURE_title );
	m_pID_PICTURE_pattern = (ControlPicture*)theUiManager.FindControl( ID_FRAME_custom, ID_PICTURE_pattern );
	m_pID_PICTURE_pattern2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_custom, ID_PICTURE_pattern2 );
	m_pID_BUTTON_default = (ControlButton*)theUiManager.FindControl( ID_FRAME_custom, ID_BUTTON_default );
	m_pID_BUTTON_sure = (ControlButton*)theUiManager.FindControl( ID_FRAME_custom, ID_BUTTON_sure );
	m_pID_BUTTON_cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_custom, ID_BUTTON_cancel );
	m_pID_TEXT_function = (ControlText*)theUiManager.FindControl( ID_FRAME_custom, ID_TEXT_function );
	m_pID_BUTTON_close = (ControlButton*)theUiManager.FindControl( ID_FRAME_custom, ID_BUTTON_close );
	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_custom, ID_BUTTON_help );
	//m_pID_LIST_KeyList = (ControlList*)theUiManager.FindControl( ID_FRAME_custom, ID_LIST_KeyList );
	m_pID_SCROLLBAR_KeyList = (ControlScrollBar*)theUiManager.FindControl( ID_FRAME_custom, ID_SCROLLBAR_KeyList );
	m_pID_CHECKBOX_CaoZuo = (ControlCheckBox*)theUiManager.FindControl(ID_FRAME_custom,ID_CHECKBOX_CaoZuo);
	m_pID_CHECKBOX_GongNeng = (ControlCheckBox*)theUiManager.FindControl(ID_FRAME_custom,ID_CHECKBOX_GongNeng);
	m_pID_CHECKBOX_KuaiJieJian = (ControlCheckBox*)theUiManager.FindControl(ID_FRAME_custom,ID_CHECKBOX_KuaiJieJian);
	
	assert(m_pID_CHECKBOX_CaoZuo);
	assert(m_pID_CHECKBOX_GongNeng);
	assert(m_pID_CHECKBOX_KuaiJieJian);

	m_pID_TEXT_KeyList.clear();
	m_pID_CHECKBOX_KeyList.clear();

	char buf[64];
	int index = 1;
	sprintf(buf, "ID_TEXT_Key%d", index);
	ControlText* pText = (ControlText*)theUiManager.FindControl( ID_FRAME_custom, buf );
	while (pText)
	{
		m_pID_TEXT_KeyList.push_back(pText);

		sprintf(buf, "ID_CHECKBOX_Key%d", index);
		ControlCheckBox* pCheckBox = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_custom, buf );
		theUiManager.OnCheckBoxCheck( ID_FRAME_custom, buf, s_CUI_ID_FRAME_customID_CHECKBOX_KeyOnCheckBoxCheck );
		m_pID_CHECKBOX_KeyList.push_back(pCheckBox);

		++index;
		sprintf(buf, "ID_TEXT_Key%d", index);
		pText = (ControlText*)theUiManager.FindControl( ID_FRAME_custom, buf );
	}

	m_pID_FRAME_custom->SetMsgProcFun(msgCustom);
	m_pID_FRAME_custom->SetVisable(false);
	m_pID_FRAME_custom->SetFather(s_CUI_ID_FRAME_GameSettingBgFrame.GetFrame());
	m_pID_SCROLLBAR_KeyList->SetStepValue(1);
	m_pID_SCROLLBAR_KeyList->SetPageSize(14);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_custom::_UnLoadUI()
{
	m_pID_TEXT_KeyList.clear();
	m_pID_CHECKBOX_KeyList.clear();
	m_pID_FRAME_custom = 0;

	m_pID_FRAME_custom = NULL;
	m_pID_PICTURE_grounding = NULL;
	m_pID_PICTURE_title_pattern = NULL;
	m_pID_PICTURE_title = NULL;
	m_pID_PICTURE_pattern = NULL;
	m_pID_PICTURE_pattern2 = NULL;
	m_pID_BUTTON_default = NULL;
	m_pID_BUTTON_sure = NULL;
	m_pID_BUTTON_cancel = NULL;
	m_pID_TEXT_function = NULL;
	m_pID_BUTTON_close = NULL;
	m_pID_BUTTON_help = NULL;
	//m_pID_LIST_KeyList = NULL;
	m_pID_SCROLLBAR_KeyList = NULL;

	bool ret = theUiManager.RemoveFrame( "Data\\UI\\SettingKey.MEUI" );
	return ret;
}
// 是否可视
bool CUI_ID_FRAME_custom::_IsVisable()
{
	if (m_pID_FRAME_custom)
		return m_pID_FRAME_custom->IsVisable();
	return false;
}
// 设置是否可视
void CUI_ID_FRAME_custom::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_custom)
		return;

	m_pID_FRAME_custom->SetVisable( bVisable );
	m_pID_SCROLLBAR_KeyList->SetValue(0);
	m_nSelectedKey = -1;
	m_pID_TEXT_function->SetText("");
	
	initTempKeyInfo();
 	if( bVisable )
 	{
//  		if (m_pID_LIST_KeyList->GetListItemCnt() > 0)
//  		{
//  			if( m_pID_LIST_KeyList->GetCurSelIndex() == -1 )
//  				m_pID_LIST_KeyList->SetCurSelIndex( 0 );
//  			ID_LIST_KeyListOnListSelectChange( 0, m_pID_LIST_KeyList->GetListItem( 0 ) );
//  		}
		m_pID_CHECKBOX_CaoZuo->SetCheck(true);
		m_pID_CHECKBOX_KuaiJieJian->SetCheck(false);
		m_pID_CHECKBOX_GongNeng->SetCheck(false);
		updateSelectedKeyInfo();
 	}
	
}
void CUI_ID_FRAME_custom::load()
{
	guardfunc;
	if( NULL == m_pID_FRAME_custom )
		return;

	initTempKeyInfo();
	unguard;
}
void CUI_ID_FRAME_custom::initTempKeyInfo()
{
	guardfunc;
	std::map<int, AN_Configure_ShortcutKey::shortcutKeyValue>& keyInfo = g_shortcutKey_configure.getCustomkeyMap();
	std::map<int, AN_Configure_ShortcutKey::shortcutKeyValue>::iterator iter =  keyInfo.begin();
	for( ; iter != keyInfo.end(); ++iter )
	{
		_tempSaveKeyInfo[iter->first] = iter->second;
	}
	//listCustomUpdata();
	unguard;
}
void CUI_ID_FRAME_custom::listCustomUpdata()
{
	guardfunc;
// 	int oldPos = m_pID_LIST_KeyList->GetScrollBar()->GetValue();
// 
// 	m_pID_LIST_KeyList->Clear();
// 
// 	const std::vector<std::string>& types = g_shortcutKey_configure.getTypes(); 
// 	for (int i = 0; i < types.size(); ++i)
// 	{
// 		ControlList::S_List stItem;
// 		stItem.SetData( types[i].c_str() );
// 		m_pID_LIST_KeyList->AddItem( &stItem,NULL, false);
// 	}
// 
// 	m_pID_LIST_KeyList->SetScrollValue(oldPos);
// 
// 	int index = m_pID_LIST_KeyList->GetCurSelIndex();
// 	if( index == -1 )
// 		m_pID_LIST_KeyList->SetScrollValue(0);
// 
// 	updateSelectedKeyInfo();

	unguard;
}
void CUI_ID_FRAME_custom::setTempSaveKeyInfoItem( int id, const char* value )
{
	guardfunc;
	if( NULL == value )
		return;

	_tempSaveKeyInfo[id]._szValue = value;
	unguard;
}
void CUI_ID_FRAME_custom::updateSelectedKeyInfo()
{
	for (int i = 0; i < m_pID_TEXT_KeyList.size(); ++i)
	{
		m_pID_TEXT_KeyList[i]->SetVisable(false);
		m_pID_CHECKBOX_KeyList[i]->SetVisable(false);
		m_pID_CHECKBOX_KeyList[i]->SetCheck(false);
	}

// 	ControlList::S_List* pItem = s_CUI_ID_FRAME_custom.m_pID_LIST_KeyList->GetCurSelItem();
// 	if( !pItem )
// 		return;
	const std::map<std::string, std::vector<int> >& typeIdMap = g_shortcutKey_configure.getTypeIdMap();
	std::map<std::string, std::vector<int> >::const_iterator it = typeIdMap.find(GetCheckString()/*pItem->m_szText*/);
	if (it != typeIdMap.end())
	{
		const std::vector<int>& keys = it->second;

		size_t count = keys.size();
		if (count > m_pID_TEXT_KeyList.size())
		{
			m_pID_SCROLLBAR_KeyList->SetMaxValue(count - m_pID_TEXT_KeyList.size());
			m_pID_SCROLLBAR_KeyList->SetEnable(true);
		}
		else
		{
			m_pID_SCROLLBAR_KeyList->SetMaxValue(0);
			m_pID_SCROLLBAR_KeyList->SetEnable(false);
		}
		int startIndex = m_pID_SCROLLBAR_KeyList->GetValue();

		count = (count - startIndex) > m_pID_TEXT_KeyList.size() ? m_pID_TEXT_KeyList.size() : (count - startIndex);
		int index = 0;
		std::vector<int>::const_iterator itKey = keys.begin() + startIndex;
		for (size_t i = 0; i < count; ++i)
		{
			std::map<int, AN_Configure_ShortcutKey::shortcutKeyValue>::iterator itTemp = _tempSaveKeyInfo.find(*itKey);
			if (itTemp != _tempSaveKeyInfo.end())
			{
				std::string str;
				if (itTemp->second._ctrl)
					str = "Ctrl-";
				else if (itTemp->second._alt)
					str = "Alt-";
				else if (itTemp->second._shift)
					str = "Shift-";
				str += itTemp->second._szValue;

				m_pID_TEXT_KeyList[index]->SetText( itTemp->second._szDiscription );
				if (str.empty())
					strcpy(m_pID_CHECKBOX_KeyList[index]->GetData()->m_szCaption, theXmlString.GetString(eClient_NotHotKey));
				else
					strcpy(m_pID_CHECKBOX_KeyList[index]->GetData()->m_szCaption, str.c_str());

				m_pID_TEXT_KeyList[index]->SetVisable(true);
				m_pID_CHECKBOX_KeyList[index]->SetVisable(true);

				if (*itKey == m_nSelectedKey)
					m_pID_CHECKBOX_KeyList[index]->SetCheck(true);

				++index;
			}
			++itKey;
		}
	}
	else
		m_pID_SCROLLBAR_KeyList->SetMaxValue(0);
}
bool CUI_ID_FRAME_custom::msgCustom( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	guardfunc;
	if ( /*bMsgUsed == true || */g_GameState != G_MAIN || !s_CUI_ID_FRAME_custom.IsVisable()  )
		return false;

	switch( msg ) 
	{
	case WM_MOUSEWHEEL:
		{
			if (theUiManager.GetFrameFocus() != s_CUI_ID_FRAME_custom.m_pID_FRAME_custom ||
				s_CUI_ID_FRAME_custom.m_pID_SCROLLBAR_KeyList->GetMaxValue() <= 0)
				return false;

			int delta = 0;
			if (int(wParam) > 0)
				delta = s_CUI_ID_FRAME_custom.m_pID_SCROLLBAR_KeyList->GetValue() - s_CUI_ID_FRAME_custom.m_pID_SCROLLBAR_KeyList->GetStepValue() * 3;
			else
				delta = s_CUI_ID_FRAME_custom.m_pID_SCROLLBAR_KeyList->GetValue() + s_CUI_ID_FRAME_custom.m_pID_SCROLLBAR_KeyList->GetStepValue() * 3;
			s_CUI_ID_FRAME_custom.m_pID_SCROLLBAR_KeyList->SetValue(delta);
			s_CUI_ID_FRAME_custom.updateSelectedKeyInfo();
			break;
		}
	case WM_KEYUP:
		{
			if( s_CUI_ID_FRAME_custom.m_nSelectedKey == -1 )
				return false;

			bool ctrl = false;
			bool alt = false;
			bool shift = false;

			if (GetKeyboardInput(DIK_LCONTROL) || GetKeyboardInput(DIK_RCONTROL))
				ctrl = true;
			else if (GetKeyboardInput(DIK_LALT) || GetKeyboardInput(DIK_RALT))
				alt = true;
			else if (GetKeyboardInput(DIK_LSHIFT) || GetKeyboardInput(DIK_RSHIFT))
				shift = true;

			std::map<int, AN_Configure_ShortcutKey::win32String>& keyInfo = g_shortcutKey_configure.getShortcutKeyMap();
			std::map<int, AN_Configure_ShortcutKey::win32String>::iterator iter =  keyInfo.find(wParam);

			if (iter != keyInfo.end())
			{
				if( wParam == iter->first )
				{
					s_CUI_ID_FRAME_custom.m_pID_TEXT_function->SetText(theXmlString.GetString(eClient_SucceedSetHotKey));
					int key = s_CUI_ID_FRAME_custom.m_nSelectedKey;
					if (wParam == VK_ESCAPE)
					{
						char buf[256];
						MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1, theXmlString.GetString(eClient_customShortcutKeyRep),
							s_CUI_ID_FRAME_custom._tempSaveKeyInfo[key]._szDiscription.c_str());
						s_CUI_ID_FRAME_custom.m_pID_TEXT_function->SetText(buf, D3DCOLOR_XRGB(255, 0, 0));

						s_CUI_ID_FRAME_custom._tempSaveKeyInfo[key]._szValue = "";
						s_CUI_ID_FRAME_custom._tempSaveKeyInfo[key]._ctrl = false;
						s_CUI_ID_FRAME_custom._tempSaveKeyInfo[key]._alt = false;
						s_CUI_ID_FRAME_custom._tempSaveKeyInfo[key]._shift = false;

						s_CUI_ID_FRAME_custom.m_nSelectedKey = -1;
						s_CUI_ID_FRAME_custom.updateSelectedKeyInfo();
						return true;
					}

					std::map<int, AN_Configure_ShortcutKey::shortcutKeyValue>& keyInfo = s_CUI_ID_FRAME_custom.getTempSaveKeyInfo();
					std::map<int, AN_Configure_ShortcutKey::shortcutKeyValue>::iterator iterCustom =  keyInfo.begin();
					for( ; iterCustom != keyInfo.end(); ++iterCustom )
					{
						if( strcmp( iter->second._szValue.c_str(), iterCustom->second._szValue.c_str()) == 0 &&
							iterCustom->second._alt == alt && iterCustom->second._ctrl == ctrl && iterCustom->second._shift == shift)
						{
							if (s_CUI_ID_FRAME_custom.m_nSelectedKey == iterCustom->first)
								break;

							char buf[256];
							MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1, theXmlString.GetString(eClient_customShortcutKeyRep),
								iterCustom->second._szDiscription.c_str());
							s_CUI_ID_FRAME_custom.m_pID_TEXT_function->SetText(buf, D3DCOLOR_XRGB(255, 0, 0));

							iterCustom->second._szValue = "";
							iterCustom->second._ctrl = false;
							iterCustom->second._alt = false;
							iterCustom->second._shift = false;
							break;
						}
					}

					s_CUI_ID_FRAME_custom._tempSaveKeyInfo[key]._szValue = iter->second._szValue;
					s_CUI_ID_FRAME_custom._tempSaveKeyInfo[key]._ctrl = ctrl;
					s_CUI_ID_FRAME_custom._tempSaveKeyInfo[key]._alt = alt;
					s_CUI_ID_FRAME_custom._tempSaveKeyInfo[key]._shift = shift;

					s_CUI_ID_FRAME_custom.m_nSelectedKey = -1;
					s_CUI_ID_FRAME_custom.updateSelectedKeyInfo();
					return true;
				}
			}
		}
		break;
	}
	return false;
	unguard;
}

const char* CUI_ID_FRAME_custom::GetCheckString()
{
	if(m_pID_CHECKBOX_CaoZuo != NULL && m_pID_CHECKBOX_CaoZuo->IsChecked())
	{
		return theXmlString.GetString(eText_CaoZuo);
	}
	else if (m_pID_CHECKBOX_GongNeng != NULL && m_pID_CHECKBOX_GongNeng->IsChecked())
	{
		return theXmlString.GetString(eGameSettingList_Function);
	}
	else if (m_pID_CHECKBOX_KuaiJieJian != NULL && m_pID_CHECKBOX_KuaiJieJian->IsChecked())
	{
		return theXmlString.GetString(eText_KuaiJieJian);
	}
	else 
		return "";
}