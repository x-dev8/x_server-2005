/********************************************************************
Created by UIEditor.exe
FileName: F:\project\Turbo\Bin\Client\Data\Ui\SearchPrivateShop.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SearchPrivateShop.h"
#include "StallQuerySystem.h"
#include "PlayerRole.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "XmlStringLanguage.h"

CUI_ID_FRAME_QueryStall s_CUI_ID_FRAME_QueryStall;
MAP_FRAME_RUN(s_CUI_ID_FRAME_QueryStall, OnFrameRun )
MAP_FRAME_RENDER(s_CUI_ID_FRAME_QueryStall, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK(s_CUI_ID_FRAME_QueryStall, ID_BUTTON_RefurbishOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK(s_CUI_ID_FRAME_QueryStall, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK(s_CUI_ID_FRAME_QueryStall, ID_BUTTON_PursueOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK(s_CUI_ID_FRAME_QueryStall, ID_LIST_FunctionLevelOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK(s_CUI_ID_FRAME_QueryStall, ID_LIST_GunDongOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK(s_CUI_ID_FRAME_QueryStall, ID_LIST_NewFunctionOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK(s_CUI_ID_FRAME_QueryStall, ID_LIST_PlayerOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK(s_CUI_ID_FRAME_QueryStall, ID_LIST_ShopOnListSelectChange )
MAP_EDIT_ENTER_CALLBACK(s_CUI_ID_FRAME_QueryStall, ID_EDIT_SearchOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK(s_CUI_ID_FRAME_QueryStall, ID_BUTTON_SearchOnButtonClick )
MAP_COMBO_BOX_CHANGE_CALLBACK(s_CUI_ID_FRAME_QueryStall, ID_COMBOBOX_SearchContentOnComboBoxChange )
CUI_ID_FRAME_QueryStall::CUI_ID_FRAME_QueryStall()
{
	// Member
	m_pID_FRAME_QueryStall = NULL;
	m_pID_BUTTON_Refurbish = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Pursue = NULL;
	m_pID_LIST_FunctionLevel = NULL;
	m_pID_LIST_GunDong = NULL;
	m_pID_LIST_NewFunction = NULL;
	m_pID_TEXT_ShopName = NULL;
	m_pID_TEXT_PlayerName = NULL;
	m_pID_LIST_Player = NULL;
	m_pID_LIST_Shop = NULL;
	m_pID_EDIT_Search = NULL;
	m_pID_BUTTON_Search = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_COMBOBOX_SearchContent = NULL;

}
// Frame
bool CUI_ID_FRAME_QueryStall::OnFrameRun()
{
	if(!IsVisable())
		return false;

	//增加超时功能
	if(IsTimeOut())
	{
		OnTimeOut();
	}

	return true;
}
bool CUI_ID_FRAME_QueryStall::OnFrameRender()
{
	if( IsVisable() )
	{
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
		if ( pMe )
		{
			float fMeX,fMeY,fMeZ;			
			pMe->GetPos( &fMeX, &fMeY, &fMeZ );
			float dist = pMe->GetDistToTarget( m_vVisiblePos.x, m_vVisiblePos.y );			
			if( dist > 12.0f )
			{
				SetVisable( false );
			}
		}
	}

	return true;
}
// Button
bool CUI_ID_FRAME_QueryStall::ID_BUTTON_RefurbishOnButtonClick( ControlObject* pSender )
{
	CStallQueryManager::Instance()->Reset();
	Refresh();

	return true;
}
// Button
bool CUI_ID_FRAME_QueryStall::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	CStallQueryManager::Instance()->Reset();

	return true;
}
// Button
bool CUI_ID_FRAME_QueryStall::ID_BUTTON_PursueOnButtonClick( ControlObject* pSender )
{
	if(NULL == m_pID_LIST_Shop)
		return false;

	int index = m_pID_LIST_Shop->GetCurSelIndex();
	if(index >= 0)
		CStallQueryManager::Instance()->MoveToStall(index);

	return true;
}
// List
void CUI_ID_FRAME_QueryStall::ID_LIST_FunctionLevelOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_QueryStall::ID_LIST_GunDongOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_QueryStall::ID_LIST_NewFunctionOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_QueryStall::ID_LIST_PlayerOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_QueryStall::ID_LIST_ShopOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// Edit
void CUI_ID_FRAME_QueryStall::ID_EDIT_SearchOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// Button
bool CUI_ID_FRAME_QueryStall::ID_BUTTON_SearchOnButtonClick( ControlObject* pSender )
{
	CStallQueryManager::Instance()->Reset();
	Refresh();

	return true;
}
// ComboBox
void CUI_ID_FRAME_QueryStall::ID_COMBOBOX_SearchContentOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	m_pID_COMBOBOX_SearchContent->GetEditInput().SetText(szData);
}

void CUI_ID_FRAME_QueryStall::ID_LIST_Shop_OnLDBClick( ControlObject* pSender, ControlList::S_List* pItem )
{
	s_CUI_ID_FRAME_QueryStall.ID_BUTTON_PursueOnButtonClick(s_CUI_ID_FRAME_QueryStall.m_pID_BUTTON_Pursue);
}

// 装载UI
bool CUI_ID_FRAME_QueryStall::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SearchPrivateShop.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SearchPrivateShop.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_QueryStall::DoControlConnect()
{
	theUiManager.OnFrameRun(ID_FRAME_QueryStall,s_CUI_ID_FRAME_QueryStallOnFrameRun );
	theUiManager.OnFrameRender(ID_FRAME_QueryStall,s_CUI_ID_FRAME_QueryStallOnFrameRender );
	theUiManager.OnButtonClick(ID_FRAME_QueryStall, ID_BUTTON_Refurbish,s_CUI_ID_FRAME_QueryStallID_BUTTON_RefurbishOnButtonClick );
	theUiManager.OnButtonClick(ID_FRAME_QueryStall, ID_BUTTON_CLOSE,s_CUI_ID_FRAME_QueryStallID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick(ID_FRAME_QueryStall, ID_BUTTON_Pursue,s_CUI_ID_FRAME_QueryStallID_BUTTON_PursueOnButtonClick );
	theUiManager.OnListSelectChange(ID_FRAME_QueryStall, ID_LIST_FunctionLevel,s_CUI_ID_FRAME_QueryStallID_LIST_FunctionLevelOnListSelectChange );
	theUiManager.OnListSelectChange(ID_FRAME_QueryStall, ID_LIST_GunDong,s_CUI_ID_FRAME_QueryStallID_LIST_GunDongOnListSelectChange );
	theUiManager.OnListSelectChange(ID_FRAME_QueryStall, ID_LIST_NewFunction,s_CUI_ID_FRAME_QueryStallID_LIST_NewFunctionOnListSelectChange );
	theUiManager.OnListSelectChange(ID_FRAME_QueryStall, ID_LIST_Player,s_CUI_ID_FRAME_QueryStallID_LIST_PlayerOnListSelectChange );
	theUiManager.OnListSelectChange(ID_FRAME_QueryStall, ID_LIST_Shop,s_CUI_ID_FRAME_QueryStallID_LIST_ShopOnListSelectChange );
	theUiManager.OnEditEnter(ID_FRAME_QueryStall, ID_EDIT_Search,s_CUI_ID_FRAME_QueryStallID_EDIT_SearchOnEditEnter );
	theUiManager.OnButtonClick(ID_FRAME_QueryStall, ID_BUTTON_Search,s_CUI_ID_FRAME_QueryStallID_BUTTON_SearchOnButtonClick );
	theUiManager.OnComboBoxChange(ID_FRAME_QueryStall, ID_COMBOBOX_SearchContent,s_CUI_ID_FRAME_QueryStallID_COMBOBOX_SearchContentOnComboBoxChange );

	m_pID_FRAME_QueryStall = (ControlFrame*)theUiManager.FindFrame(ID_FRAME_QueryStall );
	m_pID_BUTTON_Refurbish = (ControlButton*)theUiManager.FindControl(ID_FRAME_QueryStall, ID_BUTTON_Refurbish );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl(ID_FRAME_QueryStall, ID_BUTTON_CLOSE );
	m_pID_BUTTON_Pursue = (ControlButton*)theUiManager.FindControl(ID_FRAME_QueryStall, ID_BUTTON_Pursue );
	m_pID_LIST_FunctionLevel = (ControlList*)theUiManager.FindControl(ID_FRAME_QueryStall, ID_LIST_FunctionLevel );
	m_pID_LIST_GunDong = (ControlList*)theUiManager.FindControl(ID_FRAME_QueryStall, ID_LIST_GunDong );
	m_pID_LIST_NewFunction = (ControlList*)theUiManager.FindControl(ID_FRAME_QueryStall, ID_LIST_NewFunction );
	m_pID_TEXT_ShopName = (ControlText*)theUiManager.FindControl(ID_FRAME_QueryStall, ID_TEXT_ShopName );
	m_pID_TEXT_PlayerName = (ControlText*)theUiManager.FindControl(ID_FRAME_QueryStall, ID_TEXT_PlayerName );
	m_pID_LIST_Player = (ControlList*)theUiManager.FindControl(ID_FRAME_QueryStall, ID_LIST_Player );
	m_pID_LIST_Shop = (ControlList*)theUiManager.FindControl(ID_FRAME_QueryStall, ID_LIST_Shop );
	m_pID_EDIT_Search = (ControlEdit*)theUiManager.FindControl(ID_FRAME_QueryStall, ID_EDIT_Search );
	m_pID_BUTTON_Search = (ControlButton*)theUiManager.FindControl(ID_FRAME_QueryStall, ID_BUTTON_Search );
	m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl(ID_FRAME_QueryStall, ID_TEXT_Money );
	m_pID_COMBOBOX_SearchContent = (ControlComboBox*)theUiManager.FindControl(ID_FRAME_QueryStall, ID_COMBOBOX_SearchContent );
	assert( m_pID_FRAME_QueryStall );
	assert( m_pID_BUTTON_Refurbish );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_Pursue );
	assert( m_pID_LIST_FunctionLevel );
	assert( m_pID_LIST_GunDong );
	assert( m_pID_LIST_NewFunction );
	assert( m_pID_TEXT_ShopName );
	assert( m_pID_TEXT_PlayerName );
	assert( m_pID_LIST_Player );
	assert( m_pID_LIST_Shop );
	assert( m_pID_EDIT_Search );
	assert( m_pID_BUTTON_Search );
	assert( m_pID_TEXT_Money );
	assert( m_pID_COMBOBOX_SearchContent );

	if(m_pID_LIST_Shop != NULL)
	{
		m_pID_LIST_Shop->SetLDBClickFun(ID_LIST_Shop_OnLDBClick);
	}

	if(m_pID_COMBOBOX_SearchContent != NULL)
	{
		m_pID_COMBOBOX_SearchContent->GetEditInput().SetReadOnly(true);

		//设置内容
		ControlList& list = m_pID_COMBOBOX_SearchContent->GetListBox();
		list.Clear();
		ControlList::S_List stItem;
		stItem.clear();
		stItem.SetData(theXmlString.GetString(eText_StallQuery_StallName), 0);
		stItem.SetMargin( 5 );
		list.AddItem(&stItem);

		m_pID_COMBOBOX_SearchContent->GetEditInput().SetText(stItem.m_szText);

		stItem.clear();
		stItem.SetData(theXmlString.GetString(eText_StallQuery_BossName), 1);
		stItem.SetMargin( 5 );
		list.AddItem(&stItem);

		list.SetCurSelIndex(0);
	}

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_QueryStall::_UnLoadUI()
{
	m_pID_FRAME_QueryStall = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\SearchPrivateShop.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_QueryStall::_IsVisable()
{
	return m_pID_FRAME_QueryStall->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_QueryStall::_SetVisable( const bool bVisable )
{
	if(NULL == m_pID_FRAME_QueryStall)
		return;

	m_pID_FRAME_QueryStall->SetVisable( bVisable );

	if(bVisable)
	{
		m_pID_EDIT_Search->SetText("");
		CStallQueryManager::Instance()->Reset();
		Refresh();
	}
}

bool CUI_ID_FRAME_QueryStall::IsTimeOut()
{
	const DWORD TimesOut = 30 * 1000;
	DWORD now = HQ_TimeGetTime();
	return (now - m_lastTime >= TimesOut);
}

void CUI_ID_FRAME_QueryStall::OnTimeOut()
{
	//这里最好能增加一条提示信息，告诉玩家接收信息超时

	CStallQueryManager::Instance()->SetDataStatus(CStallQueryManager::E_Data_TimeOut);

	m_pID_BUTTON_Refurbish->SetEnable(true);
	m_pID_BUTTON_Search->SetEnable(true);
	//m_pID_BUTTON_Pursue->SetEnable(true);
}

void CUI_ID_FRAME_QueryStall::Refresh()
{
	if(!IsVisable())
		return;

	switch(CStallQueryManager::Instance()->GetDataStatus())
	{
	case CStallQueryManager::E_Data_Invalid:
		{
			m_pID_BUTTON_Refurbish->SetEnable(false);
			m_pID_BUTTON_Search->SetEnable(false);
			//m_pID_BUTTON_Pursue->SetEnable(false);
			m_pID_LIST_Shop->Clear();
			m_pID_LIST_Player->Clear();

			uint8 keyFieldID = MsgStallQuery::ESF_NONE;

			char keyContent[StallDefine::MaxStallTitle];
			m_pID_EDIT_Search->GetText(keyContent, StallDefine::MaxStallTitle);
			bool bKeyInvalid = false;
			for(int i=0; i<strlen(keyContent); ++i)
			{
				if(keyContent[i] != ' ')
				{
					bKeyInvalid = true;
					break;
				}
			}

			if(bKeyInvalid)
			{
				ControlList& list = m_pID_COMBOBOX_SearchContent->GetListBox();
				if(0 == list.GetCurSelIndex())
					keyFieldID = MsgStallQuery::ESF_StallName;
				else if(1 == list.GetCurSelIndex())
					keyFieldID = MsgStallQuery::ESF_ChaName;
			}

			m_lastTime = HQ_TimeGetTime();
			//获取摊位信息
			CStallQueryManager::EQueryStatus ret = CStallQueryManager::Instance()->QueryStall(keyFieldID, keyContent, StallDefine::MaxStallTitle);
			if(ret != CStallQueryManager::E_Query_Status_Succeed)
			{
				//显示错误信息
				switch(ret)
				{
				case CStallQueryManager::E_Query_Status_KeyTooLong:
					break;
				case CStallQueryManager::E_Query_Status_KeyFieldInvalid:
					break;
				case CStallQueryManager::E_Query_Status_KeyInvalid:
					break;
				}

				m_pID_BUTTON_Refurbish->SetEnable(true);
				m_pID_BUTTON_Search->SetEnable(true);
			}	
		}
		break;
	case CStallQueryManager::E_Data_Uncompleted:
		{

		}
		break;
	case CStallQueryManager::E_Data_Completed:
		{
			CStallQueryManager::Instance()->SetDataStatus(CStallQueryManager::E_Data_Invalid);

			m_pID_BUTTON_Refurbish->SetEnable(true);
			m_pID_BUTTON_Search->SetEnable(true);
			//m_pID_BUTTON_Pursue->SetEnable(true);
		}
		break;
	case CStallQueryManager::E_Data_TimeOut:
		break;
	default:
		assert(false);
	}

	//其他控件
	if(m_pID_TEXT_Money != NULL)
	{
		m_pID_TEXT_Money->SetText(thePlayerRole.GetData(CPlayerRole::TYPE_MONEY));
	}
}

void CUI_ID_FRAME_QueryStall::AddStallInfo(StallDefine::SStallInfo *pInfos_, int count_)
{
	assert(pInfos_ != NULL);
	if(m_pID_LIST_Shop != NULL && m_pID_LIST_Player != NULL)
	{
		int index = m_pID_LIST_Player->GetListItemCnt();
		for(int i=0; i<count_; ++i)
		{
			ControlList::S_List stItem;
			stItem.SetData(pInfos_[i].szStallTitle, index);
			m_pID_LIST_Shop->AddItem(&stItem);

			stItem.SetData(pInfos_[i].szCharacterName, index++);
			m_pID_LIST_Player->AddItem(&stItem);
		}
	}

	Refresh();
}
