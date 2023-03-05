/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Hero\trunk\Bin\Client\Data\Ui\MailReceive.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "MailReceive.h"
#include "MailReceive2.h"
#include "TimeEx.h"
#include "XmlStringLanguage.h"
#include "PlayerRole.h"
#include "NetworkInput.h"
#include "MailMain.h"
#include "color_config.h"
#include "MessageBox.h"
#include "ScreenInfoManager.h"
#include "XmlStringLanguage.h"
#include "Common.h"

const time_t elapseTime = 1 * 60 * 60 * 24 * 7;

CUI_ID_FRAME_MailReceive s_CUI_ID_FRAME_MailReceive;
MAP_FRAME_RUN( s_CUI_ID_FRAME_MailReceive, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_MailReceive, OnFrameRender )
//MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_MailReceive, ID_CHECKBOX_AutoDeleteOnCheckBoxCheck )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_MailReceive, ID_LISTIMG_MailIconOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_MailReceive, ID_LISTIMG_MailIconOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MailReceive, ID_LISTIMG_MailIconOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_MailReceive, ID_LISTIMG_MailIconOnIconRButtonUp )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_MailReceive, ID_COMBOBOX_FilterOnComboBoxChange )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_MailReceive, ID_CHECKBOX_Select1OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_MailReceive, ID_CHECKBOX_Select2OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_MailReceive, ID_CHECKBOX_Select3OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_MailReceive, ID_CHECKBOX_Select4OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_MailReceive, ID_CHECKBOX_Select5OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_MailReceive, ID_CHECKBOX_Select6OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_MailReceive, ID_CHECKBOX_SelectAllOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MailReceive, ID_BUTTON_PageupOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MailReceive, ID_BUTTON_PagedownOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MailReceive, ID_BUTTON_DeleteOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_MailReceive, ID_LIST_MailListOnListSelectChange )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_MailReceive, ID_LISTIMG_ItemIconOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_MailReceive, ID_LISTIMG_ItemIconOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MailReceive, ID_LISTIMG_ItemIconOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_MailReceive, ID_LISTIMG_ItemIconOnIconRButtonUp )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_MailReceive, ID_CHECKBOX_AcceptMailOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_MailReceive, ID_CHECKBOX_WriteMailOnCheckBoxCheck )
CUI_ID_FRAME_MailReceive::CUI_ID_FRAME_MailReceive()
{
	// Member
	ResetMembers();
}

void CUI_ID_FRAME_MailReceive::ResetMembers()
{
	m_pID_FRAME_MailReceive = NULL;
	m_pID_TEXT_Filter = NULL;
// 	m_pID_PICTURE_MailList = NULL;
// 	m_pID_TEXT_AutoDelete = NULL;
// 	m_pID_CHECKBOX_AutoDelete = NULL;
	m_pID_LISTIMG_MailIcon = NULL;
	m_pID_COMBOBOX_Filter = NULL;
	m_pID_CHECKBOX_Select1 = NULL;
	m_pID_CHECKBOX_Select2 = NULL;
	m_pID_CHECKBOX_Select3 = NULL;
	m_pID_CHECKBOX_Select4 = NULL;
	m_pID_CHECKBOX_Select5 = NULL;
	m_pID_CHECKBOX_Select6 = NULL;
	m_pID_CHECKBOX_SelectAll = NULL;
	m_pID_TEXT_SelectAll = NULL;
	m_pID_TEXT_Page = NULL;
	m_pID_TEXT_MailInfo1 = NULL;
	m_pID_TEXT_MailInfo2 = NULL;
	m_pID_TEXT_MailInfo3 = NULL;
	m_pID_TEXT_MailInfo4 = NULL;
	m_pID_TEXT_MailInfo5 = NULL;
	m_pID_TEXT_MailInfo6 = NULL;
	m_pID_TEXT_MailTitle1 = NULL;
	m_pID_TEXT_MailTitle2 = NULL;
	m_pID_TEXT_MailTitle3 = NULL;
	m_pID_TEXT_MailTitle4 = NULL;
	m_pID_TEXT_MailTitle5 = NULL;
	m_pID_TEXT_MailTitle6 = NULL;
	m_pID_TEXT_LeaveTime1 = NULL;
	m_pID_TEXT_LeaveTime2 = NULL;
	m_pID_TEXT_LeaveTime3 = NULL;
	m_pID_TEXT_LeaveTime4 = NULL;
	m_pID_TEXT_LeaveTime5 = NULL;
	m_pID_TEXT_LeaveTime6 = NULL;
	m_pID_BUTTON_Pageup = NULL;
	m_pID_BUTTON_Pagedown = NULL;
	m_pID_BUTTON_Delete = NULL;
	m_pID_LIST_MailList = NULL;
	m_pID_LISTIMG_ItemIcon = NULL;
	m_pID_CheckBox_AcceptMail = NULL;
	m_pID_CheckBox_WriteMail = NULL;
	m_pID_TEXT_State6 = NULL;
	m_pID_TEXT_State5 = NULL;
	m_pID_TEXT_State4 = NULL;
	m_pID_TEXT_State3 = NULL;
	m_pID_TEXT_State2 = NULL;
	m_pID_TEXT_State1 = NULL;

}
// Frame
bool CUI_ID_FRAME_MailReceive::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_MailReceive::OnFrameRender()
{
	return true;
}
// CheckBox
// void CUI_ID_FRAME_MailReceive::ID_CHECKBOX_AutoDeleteOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
// 	if(!m_pID_FRAME_MailReceive)
// 		return;
//     const __int64 dwTime = 3600;
//     thePlayerRole.DeleteMailByTime(dwTime);
//     Refresh();
// }
// ListImg / ListEx
bool CUI_ID_FRAME_MailReceive::ID_LISTIMG_MailIconOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	if(!m_pID_FRAME_MailReceive)
		return false;
	return false;
}
bool CUI_ID_FRAME_MailReceive::ID_LISTIMG_MailIconOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_MailReceive)
		return false;
	return false;
}
bool CUI_ID_FRAME_MailReceive::ID_LISTIMG_MailIconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_MailReceive)
		return false;
	return false;
}
bool CUI_ID_FRAME_MailReceive::ID_LISTIMG_MailIconOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_MailReceive)
		return false;
	return false;
}
// ComboBox
void CUI_ID_FRAME_MailReceive::ID_COMBOBOX_FilterOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_MailReceive)
		return;
    int nIndex = m_pID_COMBOBOX_Filter->GetListBox().GetCurSelIndex();
    m_FilterType = (MailFilter)nIndex;
    m_nCurPage = 0;
    ClearContorData();
    Refresh();
}
// CheckBox
void CUI_ID_FRAME_MailReceive::ID_CHECKBOX_Select1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_MailReceive)
		return;
    if(!(*pbChecked))
        m_pID_CHECKBOX_SelectAll->SetCheck(*pbChecked);
	if (*pbChecked)
	{
		m_pID_BUTTON_Delete->SetEnable(true);
	}
	else
	{
		m_pID_BUTTON_Delete->SetEnable(false);
		for (int i = 0;i < MAXSHOWNUM;++i)
		{
			if(m_CheckBox[i]&&m_CheckBox[i]->IsChecked())
			{
				m_pID_BUTTON_Delete->SetEnable(true);
				break;
			}
		}
	}
}
// CheckBox
void CUI_ID_FRAME_MailReceive::ID_CHECKBOX_Select2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_MailReceive)
		return;
    if(!(*pbChecked))
        m_pID_CHECKBOX_SelectAll->SetCheck(*pbChecked);
	if (*pbChecked)
	{
		m_pID_BUTTON_Delete->SetEnable(true);
	}
	else
	{
		m_pID_BUTTON_Delete->SetEnable(false);
		for (int i = 0;i < MAXSHOWNUM;++i)
		{
			if(m_CheckBox[i]&&m_CheckBox[i]->IsChecked())
			{
				m_pID_BUTTON_Delete->SetEnable(true);
				break;
			}
		}
	}
}
// CheckBox
void CUI_ID_FRAME_MailReceive::ID_CHECKBOX_Select3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_MailReceive)
		return;
    if(!(*pbChecked))
        m_pID_CHECKBOX_SelectAll->SetCheck(*pbChecked);
	if (*pbChecked)
	{
		m_pID_BUTTON_Delete->SetEnable(true);
	}
	else
	{
		m_pID_BUTTON_Delete->SetEnable(false);
		for (int i = 0;i < MAXSHOWNUM;++i)
		{
			if(m_CheckBox[i]&&m_CheckBox[i]->IsChecked())
			{
				m_pID_BUTTON_Delete->SetEnable(true);
				break;
			}
		}
	}
}
// CheckBox
void CUI_ID_FRAME_MailReceive::ID_CHECKBOX_Select4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_MailReceive)
		return;
    if(!(*pbChecked))
        m_pID_CHECKBOX_SelectAll->SetCheck(*pbChecked);
	if (*pbChecked)
	{
		m_pID_BUTTON_Delete->SetEnable(true);
	}
	else
	{
		m_pID_BUTTON_Delete->SetEnable(false);
		for (int i = 0;i < MAXSHOWNUM;++i)
		{
			if(m_CheckBox[i]&&m_CheckBox[i]->IsChecked())
			{
				m_pID_BUTTON_Delete->SetEnable(true);
				break;
			}
		}
	}
}
// CheckBox
void CUI_ID_FRAME_MailReceive::ID_CHECKBOX_Select5OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_MailReceive)
		return;
    if(!(*pbChecked))
        m_pID_CHECKBOX_SelectAll->SetCheck(*pbChecked);
	if (*pbChecked)
	{
		m_pID_BUTTON_Delete->SetEnable(true);
	}
	else
	{
		m_pID_BUTTON_Delete->SetEnable(false);
		for (int i = 0;i < MAXSHOWNUM;++i)
		{
			if(m_CheckBox[i]&&m_CheckBox[i]->IsChecked())
			{
				m_pID_BUTTON_Delete->SetEnable(true);
				break;
			}
		}
	}
}
// CheckBox
void CUI_ID_FRAME_MailReceive::ID_CHECKBOX_Select6OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_MailReceive)
		return;
    if(!(*pbChecked))
        m_pID_CHECKBOX_SelectAll->SetCheck(*pbChecked);
	if (*pbChecked)
	{
		m_pID_BUTTON_Delete->SetEnable(true);
	}
	else
	{
		m_pID_BUTTON_Delete->SetEnable(false);
		for (int i = 0;i < MAXSHOWNUM;++i)
		{
			if(m_CheckBox[i]&&m_CheckBox[i]->IsChecked())
			{
				m_pID_BUTTON_Delete->SetEnable(true);
				break;
			}
		}
	}
	
}
// CheckBox
void CUI_ID_FRAME_MailReceive::ID_CHECKBOX_SelectAllOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_MailReceive)
		return;
    int nSize = m_pID_LISTIMG_MailIcon->GetItemCnt();
    for (int i = 0;i < nSize;++i)
    {
        if(m_CheckBox[i]&&m_CheckBox[i]->IsVisable())
            m_CheckBox[i]->SetCheck(*pbChecked);
    }
	m_pID_BUTTON_Delete->SetEnable(false);
	if (*pbChecked)
	{
		for (int i = 0;i < MAXSHOWNUM;++i)
		{
			if(m_CheckBox[i]&&m_CheckBox[i]->IsChecked())
			{
				m_pID_BUTTON_Delete->SetEnable(true);
				break;
			}
		}
	}
	
}

// Button
bool CUI_ID_FRAME_MailReceive::ID_BUTTON_PageupOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_MailReceive)
		return false;
    if(m_nCurPage > 0)
    {
        ClearContorData();
        --m_nCurPage;
        UpdateMail();
        RefreshPage();
    }
	
	return true;
}

// Button
bool CUI_ID_FRAME_MailReceive::ID_BUTTON_PagedownOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_MailReceive)
		return false;
    int nNum = m_pID_LISTIMG_MailIcon->GetItemCnt();
    int nCount = thePlayerRole.GetCurrentMailSize();
    if(nCount - (m_nCurPage + 1) * nNum > 0)
    {
        ClearContorData();
        ++m_nCurPage;
        UpdateMail();
        RefreshPage();
    }
	
	return true;
}

// Button
bool CUI_ID_FRAME_MailReceive::ID_BUTTON_DeleteOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_MailReceive)
		return false;
    if(IsExistItemInMailList())
        s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_MailItemNotify)," ",CUI_ID_FRAME_MessageBox::eTypeYesNo,true,ProcessDeleteMail);
    else
       DeleteMailInList();
	return true;
}

bool CUI_ID_FRAME_MailReceive::IsExistItemInMailList()
{
    int nSize = thePlayerRole.GetCurrentMailSize();
    int nNum = m_pID_LISTIMG_MailIcon->GetItemCnt();
    for (int i = 0;i < MAXSHOWNUM;++i)
    {
        if(m_CheckBox[i]&&m_CheckBox[i]->IsVisable()&&m_CheckBox[i]->IsChecked())
        {
            int nIndex = nSize - m_nCurPage * nNum - 1 - i;//m_nCurPage * nNum + i;

            SMail *pMail = thePlayerRole.ReadMail(nIndex);
            if(!pMail)
                continue;

            if(pMail->money > 0)
                return true;

            if(pMail->state != SMail::EMS_HaveGetItem&&pMail->accessory.type != SMail::EAT_None)
                return true;
        }
    }
    return false;
}

void CUI_ID_FRAME_MailReceive::DeleteMailInList()
{
    int nSize = thePlayerRole.GetCurrentMailSize();
    std::vector<int> delSet;
    delSet.clear();
    int nNum = m_pID_LISTIMG_MailIcon->GetItemCnt();
    for (int i = 0;i < MAXSHOWNUM;++i)
    {
        if(m_CheckBox[i]&&m_CheckBox[i]->IsVisable()&&m_CheckBox[i]->IsChecked())
        {
            int nIndex = nSize - m_nCurPage * nNum - 1 - i;

            SMail *pMail = thePlayerRole.ReadMail(nIndex);
            if(!pMail)
                continue;

            delSet.push_back(pMail->id);
        }
    }

    if(delSet.size() <= 0)
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_MailNoSelect) );
        return;
    }
    for (int n = delSet.size() - 1;n >= 0;--n)
    {
        MsgOpMailReq msg;
        msg.op    = EMO_Delete;
        msg.mailId = delSet[n];

        GettheNetworkInput().SendMsg(&msg);
    }

    ClearContorData();
    Refresh();
    m_pID_CHECKBOX_SelectAll->SetCheck(false);
}

void CUI_ID_FRAME_MailReceive::ID_LIST_MailListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(!m_pID_FRAME_MailReceive)
		return;
    ReadMail(m_pID_LIST_MailList->GetCurSelIndex());
}

// ListImg / ListEx
bool CUI_ID_FRAME_MailReceive::ID_LISTIMG_ItemIconOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
    ControlIconDrag::S_ListImg* pItemDrag,
    ControlIconDrag::S_ListImg* pItemSrc )
{
	if(!m_pID_FRAME_MailReceive)
		return false;
    return false;
}

bool CUI_ID_FRAME_MailReceive::ID_LISTIMG_ItemIconOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_MailReceive)
		return false;
    return false;
}

bool CUI_ID_FRAME_MailReceive::ID_LISTIMG_ItemIconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_MailReceive)
		return false;
    return false;
}

bool CUI_ID_FRAME_MailReceive::ID_LISTIMG_ItemIconOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_MailReceive)
		return false;
    return false;
}

void CUI_ID_FRAME_MailReceive::ID_CHECKBOX_AcceptMailOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_MailReceive )
		return;
}
// Button
void CUI_ID_FRAME_MailReceive::ID_CHECKBOX_WriteMailOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_MailReceive )
		return;

	if (*pbChecked)
	{
		s_CUI_ID_FRAME_MailMain.SetVisable(true);
	}
	
	//s_CUI_ID_FRAME_MailMain.ToggleUI(MailType_Send);

}


// 装载UI
bool CUI_ID_FRAME_MailReceive::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\MailReceive.MEUI",false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\MailReceive.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_MailReceive::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_MailReceive, s_CUI_ID_FRAME_MailReceiveOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_MailReceive, s_CUI_ID_FRAME_MailReceiveOnFrameRender );
   // theUiManager.OnCheckBoxCheck( ID_FRAME_MailReceive, ID_CHECKBOX_AutoDelete, s_CUI_ID_FRAME_MailReceiveID_CHECKBOX_AutoDeleteOnCheckBoxCheck );
    theUiManager.OnIconDragOn( ID_FRAME_MailReceive, ID_LISTIMG_MailIcon, s_CUI_ID_FRAME_MailReceiveID_LISTIMG_MailIconOnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_MailReceive, ID_LISTIMG_MailIcon, s_CUI_ID_FRAME_MailReceiveID_LISTIMG_MailIconOnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_MailReceive, ID_LISTIMG_MailIcon, s_CUI_ID_FRAME_MailReceiveID_LISTIMG_MailIconOnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_MailReceive, ID_LISTIMG_MailIcon, s_CUI_ID_FRAME_MailReceiveID_LISTIMG_MailIconOnIconRButtonUp );
    theUiManager.OnComboBoxChange( ID_FRAME_MailReceive, ID_COMBOBOX_Filter, s_CUI_ID_FRAME_MailReceiveID_COMBOBOX_FilterOnComboBoxChange );
    theUiManager.OnCheckBoxCheck( ID_FRAME_MailReceive, ID_CHECKBOX_Select1, s_CUI_ID_FRAME_MailReceiveID_CHECKBOX_Select1OnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_MailReceive, ID_CHECKBOX_Select2, s_CUI_ID_FRAME_MailReceiveID_CHECKBOX_Select2OnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_MailReceive, ID_CHECKBOX_Select3, s_CUI_ID_FRAME_MailReceiveID_CHECKBOX_Select3OnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_MailReceive, ID_CHECKBOX_Select4, s_CUI_ID_FRAME_MailReceiveID_CHECKBOX_Select4OnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_MailReceive, ID_CHECKBOX_Select5, s_CUI_ID_FRAME_MailReceiveID_CHECKBOX_Select5OnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_MailReceive, ID_CHECKBOX_Select6, s_CUI_ID_FRAME_MailReceiveID_CHECKBOX_Select6OnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_MailReceive, ID_CHECKBOX_SelectAll, s_CUI_ID_FRAME_MailReceiveID_CHECKBOX_SelectAllOnCheckBoxCheck );
    theUiManager.OnButtonClick( ID_FRAME_MailReceive, ID_BUTTON_Pageup, s_CUI_ID_FRAME_MailReceiveID_BUTTON_PageupOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_MailReceive, ID_BUTTON_Pagedown, s_CUI_ID_FRAME_MailReceiveID_BUTTON_PagedownOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_MailReceive, ID_BUTTON_Delete, s_CUI_ID_FRAME_MailReceiveID_BUTTON_DeleteOnButtonClick );
    theUiManager.OnListSelectChange( ID_FRAME_MailReceive, ID_LIST_MailList, s_CUI_ID_FRAME_MailReceiveID_LIST_MailListOnListSelectChange );
    theUiManager.OnIconDragOn( ID_FRAME_MailReceive, ID_LISTIMG_ItemIcon, s_CUI_ID_FRAME_MailReceiveID_LISTIMG_ItemIconOnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_MailReceive, ID_LISTIMG_ItemIcon, s_CUI_ID_FRAME_MailReceiveID_LISTIMG_ItemIconOnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_MailReceive, ID_LISTIMG_ItemIcon, s_CUI_ID_FRAME_MailReceiveID_LISTIMG_ItemIconOnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_MailReceive, ID_LISTIMG_ItemIcon, s_CUI_ID_FRAME_MailReceiveID_LISTIMG_ItemIconOnIconRButtonUp );
	theUiManager.OnCheckBoxCheck( ID_FRAME_MailReceive, ID_CHECKBOX_AcceptMail, s_CUI_ID_FRAME_MailReceiveID_CHECKBOX_AcceptMailOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_MailReceive, ID_CHECKBOX_WriteMail, s_CUI_ID_FRAME_MailReceiveID_CHECKBOX_WriteMailOnCheckBoxCheck );
	
    m_pID_FRAME_MailReceive = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_MailReceive );
	m_pID_TEXT_Filter = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_Filter );
// 	m_pID_PICTURE_MailList = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_PICTURE_MailList );
// 	m_pID_TEXT_AutoDelete = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_AutoDelete );
// 	m_pID_CHECKBOX_AutoDelete = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_CHECKBOX_AutoDelete );
	m_pID_LISTIMG_MailIcon = (ControlListImage*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_LISTIMG_MailIcon );
	m_pID_COMBOBOX_Filter = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_COMBOBOX_Filter );
	m_pID_CHECKBOX_Select1 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_CHECKBOX_Select1 );
	m_pID_CHECKBOX_Select2 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_CHECKBOX_Select2 );
	m_pID_CHECKBOX_Select3 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_CHECKBOX_Select3 );
	m_pID_CHECKBOX_Select4 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_CHECKBOX_Select4 );
	m_pID_CHECKBOX_Select5 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_CHECKBOX_Select5 );
	m_pID_CHECKBOX_Select6 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_CHECKBOX_Select6 );
	m_pID_CHECKBOX_SelectAll = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_CHECKBOX_SelectAll );
	m_pID_TEXT_SelectAll = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_SelectAll );
	m_pID_TEXT_Page = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_Page );
	m_pID_TEXT_MailInfo1 = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_MailInfo1 );
	m_pID_TEXT_MailInfo2 = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_MailInfo2 );
	m_pID_TEXT_MailInfo3 = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_MailInfo3 );
	m_pID_TEXT_MailInfo4 = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_MailInfo4 );
	m_pID_TEXT_MailInfo5 = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_MailInfo5 );
	m_pID_TEXT_MailInfo6 = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_MailInfo6 );
	m_pID_TEXT_MailTitle1 = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_MailTitle1 );
	m_pID_TEXT_MailTitle2 = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_MailTitle2 );
	m_pID_TEXT_MailTitle3 = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_MailTitle3 );
	m_pID_TEXT_MailTitle4 = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_MailTitle4 );
	m_pID_TEXT_MailTitle5 = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_MailTitle5 );
	m_pID_TEXT_MailTitle6 = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_MailTitle6 );
	m_pID_TEXT_LeaveTime1 = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_LeaveTime1 );
	m_pID_TEXT_LeaveTime2 = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_LeaveTime2 );
	m_pID_TEXT_LeaveTime3 = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_LeaveTime3 );
	m_pID_TEXT_LeaveTime4 = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_LeaveTime4 );
	m_pID_TEXT_LeaveTime5 = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_LeaveTime5 );
	m_pID_TEXT_LeaveTime6 = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_LeaveTime6 );
	m_pID_BUTTON_Pageup = (ControlButton*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_BUTTON_Pageup );
	m_pID_BUTTON_Pagedown = (ControlButton*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_BUTTON_Pagedown );
	m_pID_BUTTON_Delete = (ControlButton*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_BUTTON_Delete );
	m_pID_LIST_MailList = (ControlList*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_LIST_MailList );
	m_pID_LISTIMG_ItemIcon = (ControlListImage*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_LISTIMG_ItemIcon );
	m_pID_CheckBox_AcceptMail = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_CHECKBOX_AcceptMail );
	m_pID_CheckBox_WriteMail = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_CHECKBOX_WriteMail );
	m_pID_TEXT_State6 = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_State6 );
	m_pID_TEXT_State5 = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_State5 );
	m_pID_TEXT_State4 = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_State4 );
	m_pID_TEXT_State3 = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_State3 );
	m_pID_TEXT_State2 = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_State2 );
	m_pID_TEXT_State1 = (ControlText*)theUiManager.FindControl( ID_FRAME_MailReceive, ID_TEXT_State1 );

	assert( m_pID_CheckBox_AcceptMail );
	assert( m_pID_CheckBox_WriteMail );
    assert( m_pID_FRAME_MailReceive );
	assert( m_pID_TEXT_Filter );
// 	assert( m_pID_PICTURE_MailList );
// 	assert( m_pID_TEXT_AutoDelete );
// 	assert( m_pID_CHECKBOX_AutoDelete );
	assert( m_pID_LISTIMG_MailIcon );
	assert( m_pID_COMBOBOX_Filter );
	assert( m_pID_CHECKBOX_Select1 );
	assert( m_pID_CHECKBOX_Select2 );
	assert( m_pID_CHECKBOX_Select3 );
	assert( m_pID_CHECKBOX_Select4 );
	assert( m_pID_CHECKBOX_Select5 );
	assert( m_pID_CHECKBOX_Select6 );
	assert( m_pID_CHECKBOX_SelectAll );
	assert( m_pID_TEXT_SelectAll );
	assert( m_pID_TEXT_Page );
	assert( m_pID_TEXT_MailInfo1 );
	assert( m_pID_TEXT_MailInfo2 );
	assert( m_pID_TEXT_MailInfo3 );
	assert( m_pID_TEXT_MailInfo4 );
	assert( m_pID_TEXT_MailInfo5 );
	assert( m_pID_TEXT_MailInfo6 );
	assert( m_pID_TEXT_MailTitle1 );
	assert( m_pID_TEXT_MailTitle2 );
	assert( m_pID_TEXT_MailTitle3 );
	assert( m_pID_TEXT_MailTitle4 );
	assert( m_pID_TEXT_MailTitle5 );
	assert( m_pID_TEXT_MailTitle6 );
	assert( m_pID_TEXT_LeaveTime1 );
	assert( m_pID_TEXT_LeaveTime2 );
	assert( m_pID_TEXT_LeaveTime3 );
	assert( m_pID_TEXT_LeaveTime4 );
	assert( m_pID_TEXT_LeaveTime5 );
	assert( m_pID_TEXT_LeaveTime6 );
	assert( m_pID_BUTTON_Pageup );
	assert( m_pID_BUTTON_Pagedown );
	assert( m_pID_BUTTON_Delete );
	assert( m_pID_LIST_MailList );
	assert( m_pID_LISTIMG_ItemIcon );
	assert( m_pID_TEXT_State6 );
	assert( m_pID_TEXT_State5 );
	assert( m_pID_TEXT_State4 );
	assert( m_pID_TEXT_State3 );
	assert( m_pID_TEXT_State2 );
	assert( m_pID_TEXT_State1 );
    SetVisable(false);

   //m_pID_FRAME_MailReceive->SetMsgHoldup(false);

    m_pID_LISTIMG_ItemIcon->SetMsgHoldup(false);
    m_pID_LISTIMG_ItemIcon->SetCanbePick(false);
    m_pID_LISTIMG_ItemIcon->ShowPressEffect(false);
	m_pID_BUTTON_Delete->SetEnable(false);
    m_pID_LISTIMG_MailIcon->SetMsgHoldup(false);
    m_pID_LISTIMG_MailIcon->SetCanbePick(false);
    m_pID_LISTIMG_MailIcon->ShowPressEffect(false);

    m_CheckBox[0] = m_pID_CHECKBOX_Select1;
    m_CheckBox[1] = m_pID_CHECKBOX_Select2;
    m_CheckBox[2] = m_pID_CHECKBOX_Select3;
    m_CheckBox[3] = m_pID_CHECKBOX_Select4;
    m_CheckBox[4] = m_pID_CHECKBOX_Select5;
    m_CheckBox[5] = m_pID_CHECKBOX_Select6;

    m_TextMailInfo[0] = m_pID_TEXT_MailInfo1;       
    m_TextMailInfo[1] = m_pID_TEXT_MailInfo2;       
    m_TextMailInfo[2] = m_pID_TEXT_MailInfo3;       
    m_TextMailInfo[3] = m_pID_TEXT_MailInfo4;       
    m_TextMailInfo[4] = m_pID_TEXT_MailInfo5;       
    m_TextMailInfo[5] = m_pID_TEXT_MailInfo6;       


    m_TextMailTitle[0] = m_pID_TEXT_MailTitle1;
    m_TextMailTitle[1] = m_pID_TEXT_MailTitle2;
    m_TextMailTitle[2] = m_pID_TEXT_MailTitle3;
    m_TextMailTitle[3] = m_pID_TEXT_MailTitle4;
    m_TextMailTitle[4] = m_pID_TEXT_MailTitle5;
    m_TextMailTitle[5] = m_pID_TEXT_MailTitle6;


    m_TextMailLevelTime[0] = m_pID_TEXT_LeaveTime1;
    m_TextMailLevelTime[1] = m_pID_TEXT_LeaveTime2;
    m_TextMailLevelTime[2] = m_pID_TEXT_LeaveTime3;
    m_TextMailLevelTime[3] = m_pID_TEXT_LeaveTime4;
    m_TextMailLevelTime[4] = m_pID_TEXT_LeaveTime5;
    m_TextMailLevelTime[5] = m_pID_TEXT_LeaveTime6;

	m_TextMailStates[0] = m_pID_TEXT_State1;
	m_TextMailStates[1] = m_pID_TEXT_State2;
	m_TextMailStates[2] = m_pID_TEXT_State3;
	m_TextMailStates[3] = m_pID_TEXT_State4;
	m_TextMailStates[4] = m_pID_TEXT_State5;
	m_TextMailStates[5] = m_pID_TEXT_State6;

	//GetFrame()->SetFather(s_CUI_ID_FRAME_MailMain.GetFrame());

    Init();
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_MailReceive::_UnLoadUI()
{
    m_pID_FRAME_MailReceive = NULL;
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\MailReceive.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_MailReceive::_IsVisable()
{
    if(!m_pID_FRAME_MailReceive)
        return false;
	return m_pID_FRAME_MailReceive->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_MailReceive::_SetVisable( const bool bVisable )
{
    if(m_pID_FRAME_MailReceive)
    {
	    m_pID_FRAME_MailReceive->SetVisable( bVisable );
        if(bVisable)
        {
		   ClearContorData();
		   SendMailListReq();
		   m_pID_CheckBox_WriteMail->SetCheck(false);
		   m_pID_CheckBox_AcceptMail->SetCheck(true);
           //Refresh();
		   s_CUI_ID_FRAME_MailMain.SetVisable(false);
        }
        //s_CUI_ID_FRAME_MailMain.RefreshEnable(s_CUI_ID_FRAME_MailMain.m_bagType,s_CUI_ID_FRAME_MailMain.m_nIndex,0,-1);
    }
}

void CUI_ID_FRAME_MailReceive::Init()
{
    thePlayerRole.ClearMailList();
    m_pID_LIST_MailList->Clear();

    m_nCurPage = 0;
    m_FilterType = MailFilter_ALL;

    InitCombox();
    ClearContorData();
    Refresh();

}

void CUI_ID_FRAME_MailReceive::InitCombox()
{
	//zhuxincong 8.29 试试，加上空格
    const char *pszFilter[MailFilter_Max] = {"全部信件","玩家信件","系统信件","已读信件","未读信件","包含附件的信件"};

    for (int i = 0;i < MailFilter_Max;++i)
    {
        ControlList::S_List stList;
        stList.SetData( pszFilter[i] );
        m_pID_COMBOBOX_Filter->GetListBox().AddItem(&stList);
    }

    m_pID_COMBOBOX_Filter->GetEditInput().SetText(pszFilter[0]);
}

void CUI_ID_FRAME_MailReceive::UpdateMail()
{
    int nPerPage = m_pID_LISTIMG_MailIcon->GetItemCnt();  //获得当前可以显示的邮件数量
    int nCurMailSize = thePlayerRole.GetCurrentMailSize();
    int nStartCount = nCurMailSize - m_nCurPage * nPerPage;
    int nEnd = 0;
    if(nStartCount > nPerPage)
        nEnd = nStartCount - nPerPage;

    if(nStartCount <= nPerPage)
        nEnd = 0;

    for(int n = nStartCount - 1; n >= nEnd;--n)
    {
        SMail *pMail = thePlayerRole.ReadMail(n);
        if(!pMail)
            continue;

        RefreshMailInfo(nStartCount - 1 - n,*pMail);
    }
}

void CUI_ID_FRAME_MailReceive::RefreshMailInfo(int nIndex,SMail& mail)
{
    if(!m_pID_FRAME_MailReceive)
        return;

    int nPerPage = m_pID_LISTIMG_MailIcon->GetItemCnt();  //获得当前可以显示的邮件数量
    if(nIndex <0 || nIndex >= nPerPage)
        return;

    DWORD dwColor = 0;

    char szText[256];
    MeSprintf_s(szText,sizeof(szText)/sizeof(char) - 1,"%s%s",theXmlString.GetString(eText_MailReceivedTip)
        ,mail.owners[EM_FromIndex].addressName);

    //设置发送人地址
    if(mail.state == SMail::EMS_NotOpen)
        dwColor = Color_Config.getColor(CC_MAILTIP);

    m_TextMailInfo[nIndex]->SetText(szText,dwColor);
    
    MeSprintf_s(szText,sizeof(szText)/sizeof(char) - 1,"%s%s",theXmlString.GetString(eText_MailTitleTip)
        ,mail.title);

    dwColor = 0;
    if(mail.state == SMail::EMS_NotOpen)
        dwColor = Color_Config.getColor(CC_MAILTIP);

    //设置邮件Title
    m_TextMailTitle[nIndex]->SetText(szText,dwColor); 


    ControlListImage::S_ListImg img;
    if((mail.accessory.type != SMail::EAT_None&&mail.state != SMail::EMS_HaveGetItem)
        ||(mail.money > 0))
    {
        img.SetData(59,1);
    }
    m_pID_LISTIMG_ItemIcon->SetItem(&img,nIndex);
    
    ControlListImage::S_ListImg ImgAccory;
    if(mail.state == SMail::EMS_NotOpen)
    {
        ImgAccory.SetData(56,1,eIcon_Enable,false,eTipFlag_Event);
    }
    else
    {
        ImgAccory.SetData(57,1,eIcon_Enable,false,eTipFlag_Event);
    }
    m_pID_LISTIMG_MailIcon->SetItem(&ImgAccory,nIndex);


    //显示时间
    time_t nowTime;

    _time64(&nowTime);
    __time64_t leftTime = elapseTime - ( nowTime - mail.sendTime );

    char szTime[256]={0};

    TimeSpan span = TimeSpan(/*elapseTime*/leftTime);
    if( span.GetDays() > 0 )
        MeSprintf_s(szTime, sizeof(szTime)/sizeof(char)-1, "%s%I64u%s", theXmlString.GetString(eText_MailLifeTip),span.GetDays(),theXmlString.GetString(eText_Day));
    else if( span.GetHours() > 0 )
        MeSprintf_s(szTime, sizeof(szTime)/sizeof(char)-1, "%s%ld%s",   theXmlString.GetString(eText_MailLifeTip),span.GetHours(), theXmlString.GetString(eText_Hour));
    else if( span.GetMinutes() > 0 )
        MeSprintf_s(szTime, sizeof(szTime)/sizeof(char)-1, "%s%ld%s",   theXmlString.GetString(eText_MailLifeTip),span.GetSeconds(), theXmlString.GetString(eTimeUnit_Minute));

    dwColor = 0;
    if(mail.state == SMail::EMS_NotOpen)
        dwColor = Color_Config.getColor(CC_MAILTIP);

    m_TextMailLevelTime[nIndex]->SetText(szTime,dwColor);

	if(mail.state == SMail::EMS_NotOpen)
		m_TextMailStates[nIndex]->SetText(theXmlString.GetString(eText_MailState_UnRead), dwColor);
	else
		m_TextMailStates[nIndex]->SetText(theXmlString.GetString(eText_MailState_Read), dwColor);

    ControlList::S_List item;  
    item.SetData(" ");
    m_pID_LIST_MailList->AddItem(&item);

    m_CheckBox[nIndex]->SetVisable(true);
}

void CUI_ID_FRAME_MailReceive::RefreshPage()
{
    int nPage = thePlayerRole.GetCurrentMailSize();
    int nPerPage = m_pID_LISTIMG_MailIcon->GetItemCnt();
    if(nPerPage == 0)
        nPerPage = 1;

    int nTotalPage = 0;

    nTotalPage = nPage/nPerPage;
    if(nPage%nPerPage != 0)
        ++nTotalPage;

    if(nTotalPage == 0)
        nTotalPage = 1;

    char szWord[64];
    MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,"%d/%d",m_nCurPage + 1,nTotalPage);
    m_pID_TEXT_Page->SetText(szWord);
}

void CUI_ID_FRAME_MailReceive::SendMailListReq()
{
	 MsgMailListReq msg;
	 GettheNetworkInput().SendMsg(&msg);
}

void CUI_ID_FRAME_MailReceive::Refresh()
{   
    if(!m_pID_FRAME_MailReceive)
        return;

    if(!IsVisable())
        return;

	ClearContorData();

    thePlayerRole.FilterMail(m_FilterType);
    UpdateMail(); 
    RefreshPage();
}

void CUI_ID_FRAME_MailReceive::ReadMail(int nIndex)
{
    int nNum = m_pID_LISTIMG_MailIcon->GetItemCnt();
    if(nIndex >= nNum ||nIndex <0)
    {
        assert(0&&"索引越界");
        return;
    }

    nIndex = thePlayerRole.GetCurrentMailSize() - nNum * m_nCurPage -  nIndex - 1;

    SMail *pMail = thePlayerRole.ReadMail(nIndex);
    if(!pMail)
        return;

	SetVisable(false);
    s_CUI_ID_FRAME_MailReceive2.SetVisable(true);
    
    s_CUI_ID_FRAME_MailReceive2.UpdateMail(*pMail);
}

void CUI_ID_FRAME_MailReceive::ClearContorData()
{
    if(!m_pID_FRAME_MailReceive)
        return;

    m_pID_LISTIMG_ItemIcon->Clear();
    m_pID_LISTIMG_MailIcon->Clear();
    m_pID_LIST_MailList->Clear();
    for (int i =0;i < MAXSHOWNUM ;++i)
    {
        m_CheckBox[i]->SetCheck(false);
        m_CheckBox[i]->SetVisable(false);

        m_TextMailInfo[i]->Clear();       //邮件信息
        m_TextMailTitle[i]->Clear();      //邮件标题
        m_TextMailLevelTime[i]->Clear();  //剩余时间
		m_TextMailStates[i]->Clear();	  //是否阅读
    }
	m_pID_BUTTON_Delete->SetEnable(false);
    m_pID_CHECKBOX_SelectAll->SetCheck(false);
}

bool CUI_ID_FRAME_MailReceive::ProcessDeleteMail(const char  bYesPress,void *pData)
{
    if(bYesPress)
    {
        s_CUI_ID_FRAME_MailReceive.DeleteMailInList();
        return true;
    }

    return true;
}
