/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\li.yan\桌面\刘小兵\社交\Search.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Search.h"
#include "GlobalDef.h"
#include "RelationMessage.h"
#include "CountryFunction.h"
#include "NetworkInput.h"
#include "Common.h"
#include "SystemConfig.h"
#include "InfoList.h"
#include "PlayerRole.h"
#include "AddFriend.h"
#include "ui/Create.h"
#include "GameMain.h"
#include "FamilyDefine.h"
#include "SystemFamily.h"

const int ConstListNumber = 5; 

CUI_ID_FRAME_Search s_CUI_ID_FRAME_Search;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Search, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Search, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Search, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Search, ID_BUTTON_AddFriendOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Search, ID_BUTTON_AdvanceOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Search, ID_BUTTON_NameSearchOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Search, ID_LIST_NameOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Search, ID_LIST_GuildOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Search, ID_LIST_CountryOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Search, ID_LIST_JobOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Search, ID_LIST_SelectOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Search, ID_LIST_LvOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Search, ID_BUTTON_AdvanceSearchOnButtonClick )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_Search, ID_COMBOBOX_ProvinceOnComboBoxChange )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_Search, ID_COMBOBOX_CityOnComboBoxChange )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_Search, ID_COMBOBOX_AgeOnComboBoxChange )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_Search, ID_COMBOBOX_SexOnComboBoxChange )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_Search, ID_EDIT_SelectTargetOnEditEnter )

MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Search, ID_BUTTON_PageUpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Search, ID_BUTTON_PageDownOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Search, ID_LIST_FaminlyOnListSelectChange )
CUI_ID_FRAME_Search::CUI_ID_FRAME_Search()
{
	// Member
	m_pID_FRAME_Search = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_AddFriend = NULL;
	m_pID_BUTTON_Advance = NULL;
	m_pID_BUTTON_NameSearch = NULL;
	m_pID_LIST_Name = NULL;
	m_pID_LIST_Guild = NULL;
	m_pID_LIST_Country = NULL;
	m_pID_LIST_Lv = NULL;
	m_pID_LIST_Job = NULL;
	m_pID_LIST_Select = NULL;
	m_pID_PICTURE_AdvanceBg = NULL;
	m_pID_BUTTON_AdvanceSearch = NULL;
	m_pID_COMBOBOX_Province = NULL;
	m_pID_COMBOBOX_City = NULL;
	m_pID_COMBOBOX_Age = NULL;
	m_pID_COMBOBOX_Sex = NULL;
	m_pID_EDIT_SelectTarget = NULL;
	m_pID_TEXT_Tell = NULL;

	m_pID_TEXT_Page = NULL;
	m_pID_BUTTON_PageUp = NULL;
	m_pID_BUTTON_PageDown = NULL;
	//member
	m_nPlayerNumber = 0;
	m_nCurrentPageIndex = 1;
	m_pID_LIST_Faminly = NULL;
}
// Frame
bool CUI_ID_FRAME_Search::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_Search::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_Search::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_Search::ID_BUTTON_AddFriendOnButtonClick( ControlObject* pSender )
{
	int nSelectIndex = m_pID_LIST_Select->GetCurSelIndex();//CurSel从0开始
	int nPlayerIndex = (m_nCurrentPageIndex - 1) * ConstListNumber + nSelectIndex;
	if (nSelectIndex == -1 || nPlayerIndex >= m_nPlayerNumber)
	{
		return true;
	}
	s_CUI_ID_FRAME_AddFriend.SetFrameType( CUI_ID_FRAME_AddFriend::eFrameType_AddFriendFromRMenu );
	s_CUI_ID_FRAME_AddFriend.SetPrivateName(m_vctRelationAttribute[nPlayerIndex].GetName());
	s_CUI_ID_FRAME_AddFriend.SetVisable(true);	
	return true;
}
// Button
bool CUI_ID_FRAME_Search::ID_BUTTON_AdvanceOnButtonClick( ControlObject* pSender )
{
	if (!m_pID_FRAME_Search)
	{
		return true;
	}
	if (AdvanceCtrlGroup.IsVisible())
	{
		AdvanceCtrlGroup.SetVisible(false);
	}
	else
	{
		AdvanceCtrlGroup.SetVisible(true);
	}
	
	return true;
}
// Button
bool CUI_ID_FRAME_Search::ID_BUTTON_NameSearchOnButtonClick( ControlObject* pSender )
{
	if(thePlayerRole.GetLevel() <= gCfg.m_nFriendLevel)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs,theXmlString.GetString(eText_Friend_FindPlayerMax) );
		return true;
	}

	if (strlen(m_pID_EDIT_SelectTarget->GetText()) == 0)
	{
		return true;
	}
	ResetRelationAttribute();
	MsgQueryAttributeReq msg;
	strncpy(msg.szName, m_pID_EDIT_SelectTarget->GetText(), sizeof(msg.szName) - 1);
	GettheNetworkInput().SendMsg(&msg);
	
	return true;
}
// List
void CUI_ID_FRAME_Search::ID_LIST_NameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
void CUI_ID_FRAME_Search::ID_LIST_LvOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_Search::ID_LIST_GuildOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_Search::ID_LIST_CountryOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_Search::ID_LIST_JobOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_Search::ID_LIST_SelectOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// Button
bool CUI_ID_FRAME_Search::ID_BUTTON_AdvanceSearchOnButtonClick( ControlObject* pSender )
{
	return true;
}
// ComboBox
void CUI_ID_FRAME_Search::ID_COMBOBOX_ProvinceOnComboBoxChange( ControlObject* pSender, const char* szData )
{
}
// ComboBox
void CUI_ID_FRAME_Search::ID_COMBOBOX_CityOnComboBoxChange( ControlObject* pSender, const char* szData )
{
}
// ComboBox
void CUI_ID_FRAME_Search::ID_COMBOBOX_AgeOnComboBoxChange( ControlObject* pSender, const char* szData )
{
}
// ComboBox
void CUI_ID_FRAME_Search::ID_COMBOBOX_SexOnComboBoxChange( ControlObject* pSender, const char* szData )
{
}
// Edit
void CUI_ID_FRAME_Search::ID_EDIT_SelectTargetOnEditEnter( ControlObject* pSender, const char* szData )
{
}

// List
void CUI_ID_FRAME_Search::ID_LIST_FaminlyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_Search )
		return;
}


	// 装载UI
bool CUI_ID_FRAME_Search::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame("Data\\UI\\Search.MEUI", false, UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Search.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Search::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Search, s_CUI_ID_FRAME_SearchOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Search, s_CUI_ID_FRAME_SearchOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_Search, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_SearchID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Search, ID_BUTTON_AddFriend, s_CUI_ID_FRAME_SearchID_BUTTON_AddFriendOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Search, ID_BUTTON_Advance, s_CUI_ID_FRAME_SearchID_BUTTON_AdvanceOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Search, ID_BUTTON_NameSearch, s_CUI_ID_FRAME_SearchID_BUTTON_NameSearchOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_Search, ID_LIST_Name, s_CUI_ID_FRAME_SearchID_LIST_NameOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Search, ID_LIST_Guild, s_CUI_ID_FRAME_SearchID_LIST_GuildOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Search, ID_LIST_Country, s_CUI_ID_FRAME_SearchID_LIST_CountryOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Search, ID_LIST_Job, s_CUI_ID_FRAME_SearchID_LIST_JobOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Search, ID_LIST_Select, s_CUI_ID_FRAME_SearchID_LIST_SelectOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Search, ID_LIST_Lv, s_CUI_ID_FRAME_SearchID_LIST_LvOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_Search, ID_BUTTON_AdvanceSearch, s_CUI_ID_FRAME_SearchID_BUTTON_AdvanceSearchOnButtonClick );
	theUiManager.OnComboBoxChange( ID_FRAME_Search, ID_COMBOBOX_Province, s_CUI_ID_FRAME_SearchID_COMBOBOX_ProvinceOnComboBoxChange );
	theUiManager.OnComboBoxChange( ID_FRAME_Search, ID_COMBOBOX_City, s_CUI_ID_FRAME_SearchID_COMBOBOX_CityOnComboBoxChange );
	theUiManager.OnComboBoxChange( ID_FRAME_Search, ID_COMBOBOX_Age, s_CUI_ID_FRAME_SearchID_COMBOBOX_AgeOnComboBoxChange );
	theUiManager.OnComboBoxChange( ID_FRAME_Search, ID_COMBOBOX_Sex, s_CUI_ID_FRAME_SearchID_COMBOBOX_SexOnComboBoxChange );
	theUiManager.OnEditEnter( ID_FRAME_Search, ID_EDIT_SelectTarget, s_CUI_ID_FRAME_SearchID_EDIT_SelectTargetOnEditEnter );

	theUiManager.OnButtonClick( ID_FRAME_Search, ID_BUTTON_PageUp, s_CUI_ID_FRAME_SearchID_BUTTON_PageUpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Search, ID_BUTTON_PageDown, s_CUI_ID_FRAME_SearchID_BUTTON_PageDownOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_Search, ID_LIST_Faminly, s_CUI_ID_FRAME_SearchID_LIST_FaminlyOnListSelectChange );

	m_pID_FRAME_Search = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Search );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_Search, ID_BUTTON_CLOSE );
	m_pID_BUTTON_AddFriend = (ControlButton*)theUiManager.FindControl( ID_FRAME_Search, ID_BUTTON_AddFriend );
	m_pID_BUTTON_Advance = (ControlButton*)theUiManager.FindControl( ID_FRAME_Search, ID_BUTTON_Advance );
	m_pID_BUTTON_NameSearch = (ControlButton*)theUiManager.FindControl( ID_FRAME_Search, ID_BUTTON_NameSearch );
	m_pID_LIST_Name = (ControlList*)theUiManager.FindControl( ID_FRAME_Search, ID_LIST_Name );
	m_pID_LIST_Guild = (ControlList*)theUiManager.FindControl( ID_FRAME_Search, ID_LIST_Guild );
	//m_pID_LIST_Country = (ControlList*)theUiManager.FindControl( ID_FRAME_Search, ID_LIST_Country );
	m_pID_LIST_Job = (ControlList*)theUiManager.FindControl( ID_FRAME_Search, ID_LIST_Job );
	m_pID_LIST_Select = (ControlList*)theUiManager.FindControl( ID_FRAME_Search, ID_LIST_Select );
	m_pID_PICTURE_AdvanceBg = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Search, ID_PICTURE_AdvanceBg );
	m_pID_BUTTON_AdvanceSearch = (ControlButton*)theUiManager.FindControl( ID_FRAME_Search, ID_BUTTON_AdvanceSearch );
	m_pID_COMBOBOX_Province = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_Search, ID_COMBOBOX_Province );
	m_pID_COMBOBOX_City = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_Search, ID_COMBOBOX_City );
	m_pID_COMBOBOX_Age = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_Search, ID_COMBOBOX_Age );
	m_pID_COMBOBOX_Sex = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_Search, ID_COMBOBOX_Sex );
	m_pID_EDIT_SelectTarget = (ControlEdit*)theUiManager.FindControl( ID_FRAME_Search, ID_EDIT_SelectTarget );

	m_pID_BUTTON_PageUp = (ControlButton*)theUiManager.FindControl( ID_FRAME_Search, ID_BUTTON_PageUp );
	m_pID_BUTTON_PageDown = (ControlButton*)theUiManager.FindControl( ID_FRAME_Search, ID_BUTTON_PageDown );
	m_pID_TEXT_Page = (ControlText*)theUiManager.FindControl( ID_FRAME_Search, ID_TEXT_Page );
	m_pID_TEXT_Tell = (ControlText*)theUiManager.FindControl( ID_FRAME_Search, ID_TEXT_Tell);
	m_pID_LIST_Lv = (ControlList*)theUiManager.FindControl( ID_FRAME_Search, ID_LIST_Lv );
	m_pID_LIST_Faminly = (ControlList*)theUiManager.FindControl( ID_FRAME_Search, ID_LIST_Faminly );

	AdvanceCtrlGroup.AddControl(m_pID_COMBOBOX_Province);
	AdvanceCtrlGroup.AddControl(m_pID_COMBOBOX_City);
	AdvanceCtrlGroup.AddControl(m_pID_COMBOBOX_Age);
	AdvanceCtrlGroup.AddControl(m_pID_COMBOBOX_Sex);
	AdvanceCtrlGroup.AddControl(m_pID_PICTURE_AdvanceBg);
	AdvanceCtrlGroup.AddControl(m_pID_BUTTON_AdvanceSearch);

	assert( m_pID_FRAME_Search );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_AddFriend );
	assert( m_pID_BUTTON_Advance );
	assert( m_pID_BUTTON_NameSearch );
	assert( m_pID_LIST_Name );
	assert( m_pID_LIST_Guild );
	//assert( m_pID_LIST_Country );
	assert( m_pID_LIST_Job );
	assert( m_pID_LIST_Select );
	assert( m_pID_PICTURE_AdvanceBg );
	assert( m_pID_BUTTON_AdvanceSearch );
	assert( m_pID_COMBOBOX_Province );
	assert( m_pID_COMBOBOX_City );
	assert( m_pID_COMBOBOX_Age );
	assert( m_pID_COMBOBOX_Sex );
	assert( m_pID_EDIT_SelectTarget );
	assert( m_pID_BUTTON_PageUp );
	assert( m_pID_BUTTON_PageDown );
	assert( m_pID_TEXT_Tell );
	assert(m_pID_LIST_Lv);
	assert( m_pID_LIST_Faminly );

	m_pID_BUTTON_Advance->SetVisable(false);

	return true;
}
	// 卸载UI
bool CUI_ID_FRAME_Search::_UnLoadUI()
{
	m_pID_FRAME_Search = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_AddFriend = NULL;
	m_pID_BUTTON_Advance = NULL;
	m_pID_BUTTON_NameSearch = NULL;
	m_pID_LIST_Name = NULL;
	m_pID_LIST_Guild = NULL;
	m_pID_LIST_Country = NULL;
	m_pID_LIST_Lv = NULL;
	m_pID_LIST_Job = NULL;
	m_pID_LIST_Select = NULL;
	m_pID_PICTURE_AdvanceBg = NULL;
	m_pID_BUTTON_AdvanceSearch = NULL;
	m_pID_COMBOBOX_Province = NULL;
	m_pID_COMBOBOX_City = NULL;
	m_pID_COMBOBOX_Age = NULL;
	m_pID_COMBOBOX_Sex = NULL;
	m_pID_EDIT_SelectTarget = NULL;
	m_pID_TEXT_Tell = NULL;

	m_pID_TEXT_Page = NULL;
	m_pID_BUTTON_PageUp = NULL;
	m_pID_BUTTON_PageDown = NULL;
	//member
	m_nPlayerNumber = 0;
	m_nCurrentPageIndex = 1;

	AdvanceCtrlGroup.Clear();
	return theUiManager.RemoveFrame( "Data\\UI\\Search.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Search::_IsVisable()
{
	return m_pID_FRAME_Search->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Search::_SetVisable( const bool bVisable )
{
	RefreshButtonState();
	ResetRelationAttribute();
	ResetListData();
	SetAdvanceVisable(false);
	m_pID_FRAME_Search->SetVisable( bVisable );
	if (bVisable)
	{
		theUiManager.ToTop(m_pID_FRAME_Search);

		theUiManager.SetFocus(m_pID_EDIT_SelectTarget);
		//激活中文输入
		ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );
	}
	else
	{
		ImmAssociateContext( g_hWnd, NULL);
	}
	
}

//--------------------------------------------------------------------------------------------------------------
void CUI_ID_FRAME_Search::SetAdvanceVisable(bool bShow)
{
	AdvanceCtrlGroup.SetVisible(bShow);	
}

void CUI_ID_FRAME_Search::OnSearchResult(Msg * pMsg_)
{
	if (!pMsg_)
	{
		return;
	}

	MsgQueryAttributeResult* pMsg = (MsgQueryAttributeResult*)pMsg_;
	if (pMsg->ustCount == 0)
	{
		/*s_CUI_ID_FRAME_Search.SetVisable(false);*/
		ShowUnFoundMessage();
		return;
	}
	else
	{
		m_pID_TEXT_Tell->Clear();
	}
	
	m_nPlayerNumber = pMsg->ustCount;
	m_nCurrentPageIndex = 1;
	m_vctRelationAttribute.clear();
	for (int i = 0; i < pMsg->ustCount; ++i)
	{
		m_vctRelationAttribute.push_back(pMsg->xAttribute[i]);
	}

	RefreshButtonState();
	ResetListData();
	ShowFoundPlayerAttribute(1, ConstListNumber);
}

void CUI_ID_FRAME_Search::ShowUnFoundMessage()
{
	ResetListData();
	char szText[256] = {0};
	MeSprintf_s(szText, sizeof(szText)-1, theXmlString.GetString(eText_Search_OfflineOrNotExist));
	m_pID_TEXT_Tell->SetText(szText);
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, theXmlString.GetString( eText_Search_OfflineOrNotExist ) );		
}

void CUI_ID_FRAME_Search::ShowFoundPlayerAttribute(int nStart_, int nEnd_)
{
	ControlList::S_List	stItem;
	nStart_ -= 1;
	for (int i = nStart_; i < nEnd_ && i < m_nPlayerNumber; ++i)
	{
		stItem.SetData( "" );
		m_pID_LIST_Select->AddItem(&stItem);
		stItem.clear();

		if(m_pID_LIST_Name)
		{
			//------------------------------name
			char szName[RelationDefine::MaxNameLength] = {0};
			MeSprintf_s(szName, sizeof(szName)/sizeof(char) - 1, "%s", m_vctRelationAttribute[i].GetName());
			stItem.SetData(szName, 0, NULL, 0);
			m_pID_LIST_Name->AddItem(&stItem);
			stItem.clear();
		}

		if(m_pID_LIST_Guild)
		{
			//------------------------------guild
			char szGuildName[128] = {0};
			std::string str = "无";
			if (m_vctRelationAttribute[i].GetGuildID() == GuildDefine::InitID)
			{	
				MeSprintf_s(szGuildName, sizeof(szGuildName)/sizeof(char) - 1, "%s", str.c_str());
			}
			else
			{
				MeSprintf_s(szGuildName, sizeof(szGuildName)/sizeof(char) - 1, "%s", thePlayerRole.GetGuildNameById(m_vctRelationAttribute[i].GetGuildID()));
			}

			stItem.SetData(szGuildName, 0, NULL, 0);
			m_pID_LIST_Guild->AddItem(&stItem);
			stItem.clear();
		}

		//------------------------------country
		if(m_pID_LIST_Country)
		{
			std::string countryName = CountryFunction::GetCountryNameById(m_vctRelationAttribute[i].GetCountry());
			stItem.SetData(countryName.c_str(), 0, NULL, 0);
			m_pID_LIST_Country->AddItem(&stItem);
			stItem.clear();
		}

		if(m_pID_LIST_Faminly)
		{
			FamilyDefine::FamilySimpleInfo* simpleInfo = CSystemFamily::Instance()->GetFamilySimpleInfo( m_vctRelationAttribute[i].GetFamilyID() );
			if(simpleInfo)
			{
				std::string familyName = simpleInfo->GetFamilyName();
				stItem.SetData(familyName.c_str(), 0, NULL, 0);
				m_pID_LIST_Faminly->AddItem(&stItem);
				stItem.clear();
			}
			else
			{
				stItem.SetData("无", 0, NULL, 0);
				m_pID_LIST_Faminly->AddItem(&stItem);
				stItem.clear();
			}
		}

		if(m_pID_LIST_Job)
		{
			//------------------------------job
			CProfessionInfo *pProInfo = GetSystemConfig()->GetProessionInfoFromID(m_vctRelationAttribute[i].GetProfession());
			stItem.SetData(pProInfo->m_strProShow.c_str(), 0, NULL, 0);
			m_pID_LIST_Job->AddItem(&stItem);
			stItem.clear();
		}

		if(m_pID_LIST_Lv)
		{
			char szLv[8] = {0};
			MeSprintf_s(szLv, sizeof(szLv)/sizeof(char) - 1, "%d级", m_vctRelationAttribute[i].GetLevel());
			stItem.SetData(szLv, 0, NULL, 0);
			m_pID_LIST_Lv->AddItem(&stItem);
			stItem.clear();
		}
	}
	
}

void CUI_ID_FRAME_Search::RefreshButtonState()
{
	if (m_nCurrentPageIndex * ConstListNumber < m_nPlayerNumber)
	{
		m_pID_BUTTON_PageDown->SetEnable(true);
	}
	else
	{
		m_pID_BUTTON_PageDown->SetEnable(false);
	}

	if (m_nCurrentPageIndex > 1)
	{
		m_pID_BUTTON_PageUp->SetEnable(true);
	}
	else
	{
		m_pID_BUTTON_PageUp->SetEnable(false);
	}

	char szPageNum[256];
// 	std::string strStart = "第 ";
// 	std::string strEnd = " 页";
// 	MeSprintf_s(szPageNum, sizeof(szPageNum)/sizeof(char) - 1, "%s%d%s", strStart.c_str(), m_nCurrentPageIndex, strEnd.c_str());
	MeSprintf_s(szPageNum, sizeof(szPageNum)/sizeof(char) - 1, "%d/%d", m_nCurrentPageIndex, (max(0,m_nPlayerNumber - 1))/ConstListNumber + 1);
	m_pID_TEXT_Page->SetText(szPageNum);
}

bool CUI_ID_FRAME_Search::ID_BUTTON_PageUpOnButtonClick( ControlObject* pSender )
{
	if (m_nCurrentPageIndex <= 1)
	{
		return true;
	}
	ResetListData();
	ShowFoundPlayerAttribute((m_nCurrentPageIndex - 2) * ConstListNumber + 1, (m_nCurrentPageIndex - 1) * ConstListNumber);
	--m_nCurrentPageIndex;
	RefreshButtonState();
	return true;
}

bool CUI_ID_FRAME_Search::ID_BUTTON_PageDownOnButtonClick( ControlObject* pSender )
{
	if ((m_nCurrentPageIndex) * ConstListNumber >= m_nPlayerNumber)
	{
		return true;
	}
	ResetListData();
	if ((m_nCurrentPageIndex + 1) * ConstListNumber < m_nPlayerNumber)
	{
		ShowFoundPlayerAttribute(m_nCurrentPageIndex * ConstListNumber + 1, (m_nCurrentPageIndex + 1) * ConstListNumber);
		++m_nCurrentPageIndex;
	}
	else
	{
		ShowFoundPlayerAttribute(m_nCurrentPageIndex * ConstListNumber + 1, m_nPlayerNumber);
	}
	RefreshButtonState();
	return true;
}

void CUI_ID_FRAME_Search::ResetRelationAttribute()
{
	m_nPlayerNumber = 0;
	m_nCurrentPageIndex = 1;
	m_vctRelationAttribute.clear();
}

void CUI_ID_FRAME_Search::ResetListData()
{
	if(m_pID_LIST_Name)
		m_pID_LIST_Name->Clear();

	if(m_pID_LIST_Guild)
		m_pID_LIST_Guild->Clear();

	if(m_pID_LIST_Country)
		m_pID_LIST_Country->Clear();

	if(m_pID_LIST_Job)
		m_pID_LIST_Job->Clear();

	if(m_pID_LIST_Select)
		m_pID_LIST_Select->Clear();

	if(m_pID_TEXT_Tell)
		m_pID_TEXT_Tell->Clear();

	if( m_pID_LIST_Faminly )
		m_pID_LIST_Faminly->Clear();

	if( m_pID_LIST_Lv )
		m_pID_LIST_Lv->Clear();
}

bool CUI_ID_FRAME_Search::EditInputIsVisable()
{
	if( m_pID_EDIT_SelectTarget )
	{
		return (theUiManager.GetFocus() == m_pID_EDIT_SelectTarget);
	}
	return false;
}