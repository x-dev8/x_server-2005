/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\yang.xu\桌面\角色资料和其他信息界面\角色资料和其他信息界面\SelfInfo.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SelfInfo.h"
#include "core/Name.h"
#include "Common.h"
#include "XmlStringLanguage.h"
#include "baseProperty.h"
#include "BasePropertyBGFrame.h"

const int Info_MaxLength = 30;
CUI_ID_FRAME_SelfInfo s_CUI_ID_FRAME_SelfInfo;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SelfInfo, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SelfInfo, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelfInfo, ID_BUTTON_SaveOnButtonClick )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_SelfInfo, ID_COMBOBOX_SexOnComboBoxChange )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_SelfInfo, ID_EDIT_AgeOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_SelfInfo, ID_EDIT_CityOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_SelfInfo, ID_EDIT_JobOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_SelfInfo, ID_EDIT_QQOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_SelfInfo, ID_EDIT_MSNOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_SelfInfo, ID_EDIT_DescOnEditEnter )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SelfInfo, ID_CHECKBOX_PublicOnCheckBoxCheck )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_SelfInfo, ID_EDIT_LikeOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_SelfInfo, ID_EDIT_MailOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_SelfInfo, ID_EDIT_HttpOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_SelfInfo, ID_EDIT_NickNameOnEditEnter )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SelfInfo, ID_CHECKBOX_FriendOnlyOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SelfInfo, ID_CHECKBOX_PrivateOnCheckBoxCheck )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_SelfInfo, ID_COMBOBOX_BirthMonthOnComboBoxChange )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_SelfInfo, ID_COMBOBOX_BirthDayOnComboBoxChange )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_SelfInfo, ID_COMBOBOX_ProvinceOnComboBoxChange )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_SelfInfo, ID_COMBOBOX_ConstellationOnComboBoxChange )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_SelfInfo, ID_COMBOBOX_AnimalOnComboBoxChange )
CUI_ID_FRAME_SelfInfo::CUI_ID_FRAME_SelfInfo()
{
	// Member
	m_pID_FRAME_SelfInfo = NULL;
	m_pID_BUTTON_Save = NULL;
	m_pID_COMBOBOX_Sex = NULL;
	m_pID_EDIT_Age = NULL;
	m_pID_EDIT_City = NULL;
	m_pID_EDIT_Job = NULL;
	m_pID_EDIT_QQ = NULL;
	m_pID_EDIT_MSN = NULL;
	m_pID_EDIT_Desc = NULL;
	m_pID_CHECKBOX_Public = NULL;
	m_pID_EDIT_Like = NULL;
	m_pID_EDIT_Mail = NULL;
	m_pID_EDIT_Http = NULL;
	m_pID_EDIT_NickName = NULL;
	m_pID_CHECKBOX_FriendOnly = NULL;
	m_pID_CHECKBOX_Private = NULL;
	m_pID_COMBOBOX_BirthMonth = NULL;
	m_pID_COMBOBOX_BirthDay = NULL;
	m_pID_COMBOBOX_Province = NULL;
	m_pID_COMBOBOX_Constellation = NULL;
	m_pID_COMBOBOX_Animal = NULL;
	m_pID_PICTURE_Image01 = NULL;
	m_pID_PICTURE_Image02 = NULL;

}
// Frame
bool CUI_ID_FRAME_SelfInfo::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_SelfInfo::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_SelfInfo::ID_BUTTON_SaveOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_SelfInfo )
		return false;
	return true;
}
// ComboBox
void CUI_ID_FRAME_SelfInfo::ID_COMBOBOX_SexOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_SelfInfo )
		return;
}
// Edit
void CUI_ID_FRAME_SelfInfo::ID_EDIT_AgeOnEditEnter( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_SelfInfo )
		return;
}
// Edit
void CUI_ID_FRAME_SelfInfo::ID_EDIT_CityOnEditEnter( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_SelfInfo )
		return;
}
// Edit
void CUI_ID_FRAME_SelfInfo::ID_EDIT_JobOnEditEnter( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_SelfInfo )
		return;
}
// Edit
void CUI_ID_FRAME_SelfInfo::ID_EDIT_QQOnEditEnter( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_SelfInfo )
		return;
}
// Edit
void CUI_ID_FRAME_SelfInfo::ID_EDIT_MSNOnEditEnter( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_SelfInfo )
		return;
}
// Edit
void CUI_ID_FRAME_SelfInfo::ID_EDIT_DescOnEditEnter( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_SelfInfo )
		return;
}
// CheckBox
void CUI_ID_FRAME_SelfInfo::ID_CHECKBOX_PublicOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_SelfInfo )
		return;
}
// Edit
void CUI_ID_FRAME_SelfInfo::ID_EDIT_LikeOnEditEnter( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_SelfInfo )
		return;
}
// Edit
void CUI_ID_FRAME_SelfInfo::ID_EDIT_MailOnEditEnter( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_SelfInfo )
		return;
}
// Edit
void CUI_ID_FRAME_SelfInfo::ID_EDIT_HttpOnEditEnter( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_SelfInfo )
		return;
}
// Edit
void CUI_ID_FRAME_SelfInfo::ID_EDIT_NickNameOnEditEnter( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_SelfInfo )
		return;
}
// CheckBox
void CUI_ID_FRAME_SelfInfo::ID_CHECKBOX_FriendOnlyOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_SelfInfo )
		return;
}
// CheckBox
void CUI_ID_FRAME_SelfInfo::ID_CHECKBOX_PrivateOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_SelfInfo )
		return;
}
// ComboBox
void CUI_ID_FRAME_SelfInfo::ID_COMBOBOX_BirthMonthOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_SelfInfo )
		return;
	int nIndex = m_pID_COMBOBOX_BirthMonth->GetListBox().GetCurSelIndex();
	InitDayComboBox(m_pID_COMBOBOX_BirthDay,nIndex+1);
}
// ComboBox
void CUI_ID_FRAME_SelfInfo::ID_COMBOBOX_BirthDayOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_SelfInfo )
		return;
}
// ComboBox
void CUI_ID_FRAME_SelfInfo::ID_COMBOBOX_ProvinceOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_SelfInfo )
		return;
}
// ComboBox
void CUI_ID_FRAME_SelfInfo::ID_COMBOBOX_ConstellationOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_SelfInfo )
		return;
}
// ComboBox
void CUI_ID_FRAME_SelfInfo::ID_COMBOBOX_AnimalOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_SelfInfo )
		return;
}

// 装载UI
bool CUI_ID_FRAME_SelfInfo::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SelfInfo.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SelfInfo.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SelfInfo::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SelfInfo, s_CUI_ID_FRAME_SelfInfoOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SelfInfo, s_CUI_ID_FRAME_SelfInfoOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_SelfInfo, ID_BUTTON_Save, s_CUI_ID_FRAME_SelfInfoID_BUTTON_SaveOnButtonClick );
	theUiManager.OnComboBoxChange( ID_FRAME_SelfInfo, ID_COMBOBOX_Sex, s_CUI_ID_FRAME_SelfInfoID_COMBOBOX_SexOnComboBoxChange );
	theUiManager.OnEditEnter( ID_FRAME_SelfInfo, ID_EDIT_Age, s_CUI_ID_FRAME_SelfInfoID_EDIT_AgeOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_SelfInfo, ID_EDIT_City, s_CUI_ID_FRAME_SelfInfoID_EDIT_CityOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_SelfInfo, ID_EDIT_Job, s_CUI_ID_FRAME_SelfInfoID_EDIT_JobOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_SelfInfo, ID_EDIT_QQ, s_CUI_ID_FRAME_SelfInfoID_EDIT_QQOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_SelfInfo, ID_EDIT_MSN, s_CUI_ID_FRAME_SelfInfoID_EDIT_MSNOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_SelfInfo, ID_EDIT_Desc, s_CUI_ID_FRAME_SelfInfoID_EDIT_DescOnEditEnter );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SelfInfo, ID_CHECKBOX_Public, s_CUI_ID_FRAME_SelfInfoID_CHECKBOX_PublicOnCheckBoxCheck );
	theUiManager.OnEditEnter( ID_FRAME_SelfInfo, ID_EDIT_Like, s_CUI_ID_FRAME_SelfInfoID_EDIT_LikeOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_SelfInfo, ID_EDIT_Mail, s_CUI_ID_FRAME_SelfInfoID_EDIT_MailOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_SelfInfo, ID_EDIT_Http, s_CUI_ID_FRAME_SelfInfoID_EDIT_HttpOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_SelfInfo, ID_EDIT_NickName, s_CUI_ID_FRAME_SelfInfoID_EDIT_NickNameOnEditEnter );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SelfInfo, ID_CHECKBOX_FriendOnly, s_CUI_ID_FRAME_SelfInfoID_CHECKBOX_FriendOnlyOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SelfInfo, ID_CHECKBOX_Private, s_CUI_ID_FRAME_SelfInfoID_CHECKBOX_PrivateOnCheckBoxCheck );
	theUiManager.OnComboBoxChange( ID_FRAME_SelfInfo, ID_COMBOBOX_BirthMonth, s_CUI_ID_FRAME_SelfInfoID_COMBOBOX_BirthMonthOnComboBoxChange );
	theUiManager.OnComboBoxChange( ID_FRAME_SelfInfo, ID_COMBOBOX_BirthDay, s_CUI_ID_FRAME_SelfInfoID_COMBOBOX_BirthDayOnComboBoxChange );
	theUiManager.OnComboBoxChange( ID_FRAME_SelfInfo, ID_COMBOBOX_Province, s_CUI_ID_FRAME_SelfInfoID_COMBOBOX_ProvinceOnComboBoxChange );
	theUiManager.OnComboBoxChange( ID_FRAME_SelfInfo, ID_COMBOBOX_Constellation, s_CUI_ID_FRAME_SelfInfoID_COMBOBOX_ConstellationOnComboBoxChange );
	theUiManager.OnComboBoxChange( ID_FRAME_SelfInfo, ID_COMBOBOX_Animal, s_CUI_ID_FRAME_SelfInfoID_COMBOBOX_AnimalOnComboBoxChange );

	m_pID_FRAME_SelfInfo = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SelfInfo );
	m_pID_BUTTON_Save = (ControlButton*)theUiManager.FindControl( ID_FRAME_SelfInfo, ID_BUTTON_Save );
	m_pID_COMBOBOX_Sex = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_SelfInfo, ID_COMBOBOX_Sex );
	m_pID_EDIT_Age = (ControlEdit*)theUiManager.FindControl( ID_FRAME_SelfInfo, ID_EDIT_Age );
	m_pID_EDIT_City = (ControlEdit*)theUiManager.FindControl( ID_FRAME_SelfInfo, ID_EDIT_City );
	m_pID_EDIT_Job = (ControlEdit*)theUiManager.FindControl( ID_FRAME_SelfInfo, ID_EDIT_Job );
	m_pID_EDIT_QQ = (ControlEdit*)theUiManager.FindControl( ID_FRAME_SelfInfo, ID_EDIT_QQ );
	m_pID_EDIT_MSN = (ControlEdit*)theUiManager.FindControl( ID_FRAME_SelfInfo, ID_EDIT_MSN );
	m_pID_EDIT_Desc = (ControlEdit*)theUiManager.FindControl( ID_FRAME_SelfInfo, ID_EDIT_Desc );
	m_pID_CHECKBOX_Public = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SelfInfo, ID_CHECKBOX_Public );
	m_pID_EDIT_Like = (ControlEdit*)theUiManager.FindControl( ID_FRAME_SelfInfo, ID_EDIT_Like );
	m_pID_EDIT_Mail = (ControlEdit*)theUiManager.FindControl( ID_FRAME_SelfInfo, ID_EDIT_Mail );
	m_pID_EDIT_Http = (ControlEdit*)theUiManager.FindControl( ID_FRAME_SelfInfo, ID_EDIT_Http );
	m_pID_EDIT_NickName = (ControlEdit*)theUiManager.FindControl( ID_FRAME_SelfInfo, ID_EDIT_NickName );
	m_pID_CHECKBOX_FriendOnly = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SelfInfo, ID_CHECKBOX_FriendOnly );
	m_pID_CHECKBOX_Private = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SelfInfo, ID_CHECKBOX_Private );
	m_pID_COMBOBOX_BirthMonth = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_SelfInfo, ID_COMBOBOX_BirthMonth );
	m_pID_COMBOBOX_BirthDay = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_SelfInfo, ID_COMBOBOX_BirthDay );
	m_pID_COMBOBOX_Province = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_SelfInfo, ID_COMBOBOX_Province );
	m_pID_COMBOBOX_Constellation = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_SelfInfo, ID_COMBOBOX_Constellation );
	m_pID_COMBOBOX_Animal = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_SelfInfo, ID_COMBOBOX_Animal );
	m_pID_PICTURE_Image01 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SelfInfo, ID_PICTURE_Image01 );
	m_pID_PICTURE_Image02 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SelfInfo, ID_PICTURE_Image02 );

	assert( m_pID_FRAME_SelfInfo );
	assert( m_pID_BUTTON_Save );
	assert( m_pID_COMBOBOX_Sex );
	assert( m_pID_EDIT_Age );
	assert( m_pID_EDIT_City );
	assert( m_pID_EDIT_Job );
	assert( m_pID_EDIT_QQ );
	assert( m_pID_EDIT_MSN );
	assert( m_pID_EDIT_Desc );
	assert( m_pID_CHECKBOX_Public );
	assert( m_pID_EDIT_Like );
	assert( m_pID_EDIT_Mail );
	assert( m_pID_EDIT_Http );
	assert( m_pID_EDIT_NickName );
	assert( m_pID_CHECKBOX_FriendOnly );
	assert( m_pID_CHECKBOX_Private );
	assert( m_pID_COMBOBOX_BirthMonth );
	assert( m_pID_COMBOBOX_BirthDay );
	assert( m_pID_COMBOBOX_Province );
	assert( m_pID_COMBOBOX_Constellation );
	assert( m_pID_COMBOBOX_Animal );
	assert( m_pID_PICTURE_Image01 );
	assert( m_pID_PICTURE_Image02 );
	
	InitMonthComboBox(m_pID_COMBOBOX_BirthMonth);
	//InitDayComboBox(m_pID_COMBOBOX_BirthDay);
	InitSexComboBox(m_pID_COMBOBOX_Sex);
	InitAnimalComboBox(m_pID_COMBOBOX_Animal);
	InitCityComboBox(m_pID_COMBOBOX_Province);
	InitConstellationComboBox(m_pID_COMBOBOX_Constellation);
	
	m_pID_EDIT_Age->SetMaxLength(Info_MaxLength);
	m_pID_EDIT_City->SetMaxLength(Info_MaxLength);
	m_pID_EDIT_Job->SetMaxLength(Info_MaxLength);
	m_pID_EDIT_QQ->SetMaxLength(Info_MaxLength);
	m_pID_EDIT_Desc->SetMaxLength(Info_MaxLength);
	m_pID_EDIT_Like->SetMaxLength(Info_MaxLength);
	m_pID_EDIT_Mail->SetMaxLength(Info_MaxLength);
	m_pID_EDIT_Http->SetMaxLength(Info_MaxLength);
	m_pID_EDIT_NickName->SetMaxLength(Info_MaxLength);
	m_pID_FRAME_SelfInfo->SetFather(s_CUI_ID_FRAME_BasePropertyBGFrame.GetFrame());
	_SetVisable(false);
	
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_SelfInfo::_UnLoadUI()
{
	m_pID_FRAME_SelfInfo = NULL;
	m_pID_BUTTON_Save = NULL;
	m_pID_COMBOBOX_Sex = NULL;
	m_pID_EDIT_Age = NULL;
	m_pID_EDIT_City = NULL;
	m_pID_EDIT_Job = NULL;
	m_pID_EDIT_QQ = NULL;
	m_pID_EDIT_MSN = NULL;
	m_pID_EDIT_Desc = NULL;
	m_pID_CHECKBOX_Public = NULL;
	m_pID_EDIT_Like = NULL;
	m_pID_EDIT_Mail = NULL;
	m_pID_EDIT_Http = NULL;
	m_pID_EDIT_NickName = NULL;
	m_pID_CHECKBOX_FriendOnly = NULL;
	m_pID_CHECKBOX_Private = NULL;
	m_pID_COMBOBOX_BirthMonth = NULL;
	m_pID_COMBOBOX_BirthDay = NULL;
	m_pID_COMBOBOX_Province = NULL;
	m_pID_COMBOBOX_Constellation = NULL;
	m_pID_COMBOBOX_Animal = NULL;
	m_pID_PICTURE_Image01 = NULL;
	m_pID_PICTURE_Image02 = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\SelfInfo.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_SelfInfo::_IsVisable()
{
	if ( !m_pID_FRAME_SelfInfo )
		return false;
	return m_pID_FRAME_SelfInfo->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SelfInfo::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_SelfInfo )
		return ;
	m_pID_FRAME_SelfInfo->SetVisable( bVisable );
	if (bVisable)
	{
		InitSelfInfo(); //初始化信息
	}
}

void CUI_ID_FRAME_SelfInfo::InitSelfInfo()
{
	if (m_pID_FRAME_SelfInfo != NULL)
	{
		m_pID_EDIT_Age->SetText(m_selfinfo.m_age);
		m_pID_EDIT_City->SetText(m_selfinfo.m_city);
		m_pID_EDIT_NickName->SetText(m_selfinfo.m_name);
		m_pID_EDIT_Desc->SetText(m_selfinfo.m_desc);
		m_pID_EDIT_Http->SetText(m_selfinfo.m_http);
		m_pID_EDIT_Like->SetText(m_selfinfo.m_like);
		m_pID_EDIT_Mail->SetText(m_selfinfo.m_mail);
		m_pID_COMBOBOX_Animal->GetListBox().SetCurSelIndex(m_selfinfo.m_Animal);
		m_pID_COMBOBOX_BirthMonth->GetListBox().SetCurSelIndex(m_selfinfo.m_month);
		InitDayComboBox(m_pID_COMBOBOX_BirthDay,m_selfinfo.m_month);
		m_pID_COMBOBOX_BirthDay->GetListBox().SetCurSelIndex(m_selfinfo.m_day);
		m_pID_COMBOBOX_Constellation->GetListBox().SetCurSelIndex(m_selfinfo.m_constellation);
// 		MexResMgr::Record* record = NULL;
// 		record = GetMexResMgr()->GetRecord(theHeroGame.GetPlayerMgr()->GetMe()->GetModelId());
// 		if (record != NULL)
// 		{
// 			m_pID_PICTURE_Image01->SetPicName(record);
// 		}
	}
}

void CUI_ID_FRAME_SelfInfo::RefreshInfo()
{

}

uint8 CUI_ID_FRAME_SelfInfo::GetDayCount(uint8 m_month)
{
	if(0 == m_month || m_month > 12)
		return 0;

	const uint8 days[] = {31, 29, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31};

	return days[m_month - 1];
}
void CUI_ID_FRAME_SelfInfo::InitMonthComboBox(ControlComboBox *pBox)
{
	assert(pBox != NULL);
	if(NULL == pBox)
		return;

	//设置内容
	ControlList& list = pBox->GetListBox();
	list.Clear();

	ControlList::S_List stItem;
	stItem.clear();
	stItem.SetMargin( 5 );

	char buf[3];
	for(int i = 1; i <= 12; ++i)
	{
		MeSprintf_s(buf, sizeof(buf),"%d", i);
		stItem.SetData(buf, i);
		stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
		list.AddItem(&stItem);
	}
}

void CUI_ID_FRAME_SelfInfo::InitDayComboBox(ControlComboBox *pBox,uint8 m_month)
{
	//assert(pBox != NULL && m_month >= 1 && m_month <= 12);
	if(pBox != NULL && m_month >= 1 && m_month <= 12)
	{
		//设置内容
		ControlList& list = pBox->GetListBox();
		list.Clear();

		ControlList::S_List stItem;
		stItem.clear();
		stItem.SetMargin( 5 );

		uint8 days = GetDayCount(m_month);
		assert(days >= 1 && days <= 31);
		if(days >= 1 && days <= 31)
		{
			char buf[3];
			for(int i=1; i<=days; ++i)
			{
				MeSprintf_s(buf, sizeof(buf),"%d", i);
				stItem.SetData(buf, i - 1);
				stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
				list.AddItem(&stItem);
			}
		}
	}
}

void CUI_ID_FRAME_SelfInfo::InitSexComboBox(ControlComboBox *pBox)
{
	if (pBox != NULL)
	{
		ControlList &list = pBox->GetListBox();
		list.Clear();
		ControlList::S_List stItem;
		stItem.clear();
		stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
		stItem.SetMargin(2);
		char buf[3];
		MeSprintf_s(buf,sizeof(buf),theXmlString.GetString(eClient_AddInfo_2slk_132));
		stItem.SetData(buf,0);
		list.AddItem(&stItem);

		MeSprintf_s(buf,sizeof(buf),theXmlString.GetString(eClient_AddInfo_2slk_133));
		stItem.SetData(buf,1);
		list.AddItem(&stItem);
	}
}

void CUI_ID_FRAME_SelfInfo::InitAnimalComboBox(ControlComboBox *pBox)
{
	if (pBox != NULL)
	{
		ControlList &list = pBox->GetListBox();
		list.Clear();
		ControlList::S_List stItem;
		stItem.clear();
		stItem.SetMargin(5);
		char buf[3];
		for (int i = eText_AnimShu; i< eText_AnimZhu +1; i++)
		{
			MeSprintf_s(buf,sizeof(buf),theXmlString.GetString(i));
			stItem.SetData(buf,i);
			stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
			list.AddItem(&stItem);
		}
	}
}

void CUI_ID_FRAME_SelfInfo::InitCityComboBox(ControlComboBox *pBox)
{
	if (pBox != NULL)
	{
		ControlList &list = pBox->GetListBox();
		list.Clear();
		ControlList::S_List stItem;
		stItem.clear();
		stItem.SetMargin(5);
		char buf[8];
		for (int i=eText_BeiJing; i< eText_YunNan +1 ; i++ )
		{
			MeSprintf_s(buf,sizeof(buf),theXmlString.GetString(i));
			stItem.SetData(buf,i);
			stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
			list.AddItem(&stItem);
		}
	}
}

void CUI_ID_FRAME_SelfInfo::InitConstellationComboBox(ControlComboBox *pBox)
{
	if (pBox != NULL)
	{
		ControlList &list = pBox->GetListBox();
		list.Clear();
		ControlList::S_List stItem;
		stItem.clear();
		stItem.SetMargin(5);
		char buf[8];
		for (int i=eText_ConShuiPing; i< eText_ConMoJie +1 ; i++ )
		{
			MeSprintf_s(buf,sizeof(buf),theXmlString.GetString(i));
			stItem.SetData(buf,i);
			stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
			list.AddItem(&stItem);
		}
	}
}

bool CUI_ID_FRAME_SelfInfo::EditInputIsVisable()
{
	if (m_pID_EDIT_Age != NULL && m_pID_EDIT_City != NULL
		&& m_pID_EDIT_Job != NULL &&m_pID_EDIT_QQ != NULL
		&& m_pID_EDIT_Desc != NULL && m_pID_EDIT_Like != NULL
		&&m_pID_EDIT_Mail != NULL && m_pID_EDIT_Http != NULL
		&&m_pID_EDIT_NickName != NULL)
	{
		return (theUiManager.GetFocus() == m_pID_EDIT_Age || theUiManager.GetFocus() == m_pID_EDIT_City
					||theUiManager.GetFocus() == m_pID_EDIT_Job ||theUiManager.GetFocus() == m_pID_EDIT_QQ
					||theUiManager.GetFocus() == m_pID_EDIT_Desc ||theUiManager.GetFocus() == m_pID_EDIT_Like
					||theUiManager.GetFocus() == m_pID_EDIT_Mail ||theUiManager.GetFocus() == m_pID_EDIT_Http
					||theUiManager.GetFocus() == m_pID_EDIT_NickName);
	}
	return false;	

}