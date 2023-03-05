/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\桌面\新建文件夹 (13)\FamilyUI\Family.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Family.h"
#include "FamilyMoney.h"
#include "FamilyMessageBox.h"
#include "CountryFunction.h"
#include "FamilyMessage.h"
#include "NetworkInput.h"
#include "PlayerRole.h"
#include "MessageBox.h"
#include "Common.h"
#include "XmlStringLanguage.h"
#include "FamilyConfig.h"
#include "FamilyTenet.h"
#include "AddMember.h"
#include "SystemFamily.h"

CUI_ID_FRAME_Family s_CUI_ID_FRAME_Family;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Family, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Family, OnFrameRender )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Family, ID_LIST_FamilyNameOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Family, ID_LIST_ProfessionOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Family, ID_LIST_ContributeOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Family, ID_LIST_LevelOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Family, ID_BUTTON_ExpelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Family, ID_BUTTON_AttornOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Family, ID_BUTTON_ExitOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Family, ID_BUTTON_AfficheOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Family, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Family, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Family, ID_BUTTON_UpgradeOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Family, ID_BUTTON_ContributeOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Family, ID_LIST_NameOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Family, ID_LIST_ZhiWuOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Family, ID_LIST_LineOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Family, ID_BUTTON_AddZYOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Family, ID_BUTTON_ChangeZZOnButtonClick )
CUI_ID_FRAME_Family::CUI_ID_FRAME_Family()
{
	// Member
	m_pID_FRAME_Family = NULL;
	m_pID_LIST_FamilyName = NULL;
	m_pID_PICTURE_Logo = NULL;
	m_pID_LIST_Profession = NULL;
	m_pID_LIST_Contribute = NULL;
	m_pID_LIST_Level = NULL;
	m_pID_TEXT_FamilyName = NULL;
	m_pID_TEXT_ZuZhang = NULL;
	m_pID_TEXT_FamilyLevel = NULL;
	m_pID_TEXT_Amount = NULL;
	m_pID_TEXT_FanRongDu = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_TEXT_Affiche = NULL;
	m_pID_TEXT_FamilyInfo = NULL;
	m_pID_BUTTON_Expel = NULL;
	m_pID_BUTTON_Attorn = NULL;
	m_pID_BUTTON_Exit = NULL;
	m_pID_BUTTON_Affiche = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Upgrade = NULL;
	m_pID_BUTTON_Contribute = NULL;
	m_pID_LIST_Name = NULL;
	m_pID_LIST_ZhiWu = NULL;
	m_pID_LIST_Line = NULL;
	m_pID_BUTTON_AddZY = NULL;
	m_pID_BUTTON_ChangeZZ = NULL;

}
// Frame
bool CUI_ID_FRAME_Family::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_Family::OnFrameRender()
{
	return true;
}
// List 选中不同的家族成员
void CUI_ID_FRAME_Family::ID_LIST_FamilyNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_Family )
		return;

	if ( CSystemFamily::Instance()->IsMeFamilyLeader( thePlayerRole.GetDBID() ) )
	{
		int idx = m_pID_LIST_FamilyName->GetCurSelIndex();
		if ( idx >= 0 && idx < m_vecFamilyMembers.size() )
		{
			if( m_vecFamilyMembers[idx].GetID() == thePlayerRole.GetDBID() )
			{
				//选中自己
				m_pID_BUTTON_Expel->SetEnable(false);
				m_pID_BUTTON_Attorn->SetEnable(false);
			}
			else
			{
				m_pID_BUTTON_Expel->SetEnable(true);
				m_pID_BUTTON_Attorn->SetEnable(true);
			}
		}
	}
	


}
// List
void CUI_ID_FRAME_Family::ID_LIST_ProfessionOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_Family )
		return;
}
// List
void CUI_ID_FRAME_Family::ID_LIST_ContributeOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_Family )
		return;
}
// List
void CUI_ID_FRAME_Family::ID_LIST_LevelOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_Family )
		return;
}
// List
void CUI_ID_FRAME_Family::ID_LIST_NameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_Family )
		return;
}
bool FamilyExpelCheck(char bIsTell,void *pData )
{
	if ( bIsTell == 1 )
	{
		int idx = s_CUI_ID_FRAME_Family.m_pID_LIST_FamilyName->GetCurSelIndex();
		if ( idx >= 0 && idx < s_CUI_ID_FRAME_Family.m_vecFamilyMembers.size() )
		{
			MsgFamilyTransferReq msg;
			msg.nTargetPlayerID = s_CUI_ID_FRAME_Family.m_vecFamilyMembers[idx].GetID();
			GettheNetworkInput().SendMsg(&msg);
		}
	}

	return true;
}
// Button  转让族长
bool CUI_ID_FRAME_Family::ID_BUTTON_ExpelOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Family )
		return false;

	s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_FamilySureExpel), "",   
		CUI_ID_FRAME_MessageBox::eTypeYesNo, true, FamilyExpelCheck);


	return true;
}


bool FamilyAttornCheck(char bIsTell,void *pData )
{
	if ( bIsTell == 1 )
	{
		s_CUI_ID_FRAME_Family.DoAttornMemeber();
	}

	return true;
}

void CUI_ID_FRAME_Family::DoAttornMemeber()
{
	int idx = m_pID_LIST_FamilyName->GetCurSelIndex();
	if ( idx >= 0 && idx < m_vecFamilyMembers.size() )
	{
		MsgKickOutFamilyReq msg;
		msg.nTargetPlayerID = m_vecFamilyMembers[idx].GetID();
		GettheNetworkInput().SendMsg(&msg);

		RefreshValues();
	}
}

// Button 踢出成员
bool CUI_ID_FRAME_Family::ID_BUTTON_AttornOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Family )
		return false;

	int idx = m_pID_LIST_FamilyName->GetCurSelIndex();
	if ( idx >= 0 && idx < m_vecFamilyMembers.size() )
	{
		char tmpStr[256] = {0};
		MeSprintf_s( tmpStr, sizeof(tmpStr), theXmlString.GetString(eText_FamilyKickoutTip), m_vecFamilyMembers[idx].GetName() );
		s_CUI_ID_FRAME_MessageBox.Show( tmpStr, theXmlString.GetString(eText_FamilyKickout),   
			CUI_ID_FRAME_MessageBox::eTypeYesNo, true, FamilyAttornCheck);
	}
	
	//int idx = m_pID_LIST_FamilyName->GetCurSelIndex();
	//if ( idx >= 0 && idx < m_vecFamilyMembers.size() )
	//{
	//	MsgKickOutFamilyReq msg;
	//	msg.nTargetPlayerID = m_vecFamilyMembers[idx].GetID();
	//	GettheNetworkInput().SendMsg(&msg);
	//}
	
	//RefreshValues();
	return true;
}

bool FamilyExitCheck(char bIsTell,void *pData )
{
	if ( bIsTell == 1 )
	{
		MsgQuitFamilyReq msg;
		GettheNetworkInput().SendMsg(&msg);
	}

	return true;
}

// Button 退出家族
bool CUI_ID_FRAME_Family::ID_BUTTON_ExitOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Family )
		return false;

	//MsgQuitFamilyReq msg;
	//GettheNetworkInput().SendMsg(&msg);

	std::string tmpStr = theXmlString.GetString(eText_FamilyQuitYesNo);
	tmpStr += CSystemFamily::Instance()->GetFamilyInfo()->GetFamilyName();
	s_CUI_ID_FRAME_MessageBox.Show( tmpStr.c_str(), theXmlString.GetString(eText_FamilyQuit),   
		CUI_ID_FRAME_MessageBox::eTypeYesNo, true, FamilyExitCheck);
	
	return true;
}
// Button	//修改公告
bool CUI_ID_FRAME_Family::ID_BUTTON_AfficheOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Family )
		return false;

	if ( s_CUI_ID_FRAME_GUILD_FamilyMessageBox.IsVisable() == true )
	{
		s_CUI_ID_FRAME_GUILD_FamilyMessageBox.SetVisable(false);
	}
	else
	{
		s_CUI_ID_FRAME_GUILD_FamilyMessageBox.ShowAsModifyNote();
		s_CUI_ID_FRAME_GUILD_FamilyMessageBox.m_pID_TEXT_Message->SetText(m_pID_TEXT_Affiche->GetText());
	}
	
	
	return true;
}
// Button
bool CUI_ID_FRAME_Family::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Family )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_Family::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Family )
		return false;
	return true;
}
bool FamilyUpgradCheck(char bIsTell,void *pData )
{
	if ( bIsTell == 1 )
	{
		MsgFamilyUpgradeReq msg;
		GettheNetworkInput().SendMsg(&msg);
	}

	return true;
}
// Button 升级
bool CUI_ID_FRAME_Family::ID_BUTTON_UpgradeOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Family )
		return false;

	
	int level = (int)CSystemFamily::Instance()->GetFamilyInfo()->GetFamilyLevel();
	const FamilyConfig::AttrSetting* attr = FamilyConfig::Instance().GetAttrSettingByLevel( level + 1 );
	if ( attr == NULL )
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_FamilyMaxLevel), "",
			CUI_ID_FRAME_MessageBox::eTypeConfirm);
		return true;
	}
	char tmpStr[512] = {0};
	std::string text = "";
	thePlayerRole.GetGSCStringFromMoney(attr->GetCostMoney(), text);
	MeSprintf( tmpStr, sizeof(tmpStr) - 1, theXmlString.GetString(eText_FamilySureUpgrad), level + 1, attr->GetProsperityNeed(), text.c_str() );
	s_CUI_ID_FRAME_MessageBox.Show( tmpStr, "",   
		CUI_ID_FRAME_MessageBox::eTypeYesNo, true, FamilyUpgradCheck);
	return true;
}
// Button 贡献资金
bool CUI_ID_FRAME_Family::ID_BUTTON_ContributeOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Family )
		return false;

	s_CUI_ID_FRAME_GUILD_FamilyMoney.SetVisable(true);

	return true;
}

// List
void CUI_ID_FRAME_Family::ID_LIST_ZhiWuOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_Family )
		return;
}
// List
void CUI_ID_FRAME_Family::ID_LIST_LineOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_Family )
		return;
}

// Button  添加组员
bool CUI_ID_FRAME_Family::ID_BUTTON_AddZYOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Family )
		return false;
	s_CUI_ID_FRAME_ADD_MEMBER.SetFrameType( CUI_ID_FRAME_ADD_MEMBER::eFrameType_AddFamilyMember );
	s_CUI_ID_FRAME_ADD_MEMBER.SetVisable( !s_CUI_ID_FRAME_ADD_MEMBER.IsVisable() );

	return true;
}
// Button 修改宗旨
bool CUI_ID_FRAME_Family::ID_BUTTON_ChangeZZOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Family )
		return false;
	s_CUI_ID_FRAME_GUILD_FamilyTenet.SetVisable( !s_CUI_ID_FRAME_GUILD_FamilyTenet.IsVisable() );

	return true;
}

void CUI_ID_FRAME_Family::SetButtonsEnable( bool bval )
{
	if ( !m_pID_FRAME_Family )
		return;
	m_pID_BUTTON_Upgrade->SetEnable(bval);		//升级家族
	m_pID_BUTTON_Contribute->SetEnable(bval);	//贡献资金
	m_pID_BUTTON_Expel->SetEnable(bval);		//转让族长
	m_pID_BUTTON_Attorn->SetEnable(bval);		//开除成员
	m_pID_BUTTON_Exit->SetEnable(bval);			//退出家族
	m_pID_BUTTON_Affiche->SetEnable(bval);		//修改公告

	m_pID_BUTTON_AddZY->SetEnable(bval);
	m_pID_BUTTON_ChangeZZ->SetEnable(bval);
}

void CUI_ID_FRAME_Family::ClearAllValues()
{
	if ( !m_pID_FRAME_Family )
		return;
	//list  列表清除
	m_pID_LIST_FamilyName->Clear();
	m_pID_LIST_Name->Clear();
	m_pID_LIST_Level->Clear();		//等级
	m_pID_LIST_Profession->Clear();
	m_pID_LIST_Contribute->Clear();
	m_pID_LIST_ZhiWu->Clear();
	m_pID_LIST_Line->Clear();

	m_pID_TEXT_FamilyName->SetText("");    //家族名称
	m_pID_TEXT_ZuZhang->SetText("");       //族长
	m_pID_TEXT_FamilyLevel->SetText("");  //等级
	m_pID_TEXT_FanRongDu->SetText("");   //繁荣度
	m_pID_TEXT_Money->SetText("");		//资金
	m_pID_TEXT_Amount->SetText("");		//成员数
	m_pID_TEXT_Affiche->SetText("");     //留言
	

	m_vecFamilyMembers.clear();
}

void CUI_ID_FRAME_Family::InitialValues()
{
	if ( !m_pID_FRAME_Family )
		return;
	char tmpStr[256] = {0};
	SetButtonsEnable(false);
	ClearAllValues();

	FamilyDefine::FamilyInfo* familyInfo = CSystemFamily::Instance()->GetFamilyInfo();

	if ( familyInfo->GetFamilyID() < FamilyDefine::FirstFamilyID )
	{
		ClearAllValues();
		return;
	}
	

	m_pID_TEXT_FamilyName->SetText(familyInfo->GetFamilyName());
	m_pID_TEXT_ZuZhang->SetText(CSystemFamily::Instance()->GetLeaderName());
	MeSprintf( tmpStr, sizeof(tmpStr) - 1, "%u", familyInfo->GetFamilyLevel() );
	m_pID_TEXT_FamilyLevel->SetText(tmpStr);
	MeSprintf( tmpStr, sizeof(tmpStr) - 1, "%u", familyInfo->GetProsperity() );
	m_pID_TEXT_FanRongDu->SetText(tmpStr);

	//MeSprintf( tmpStr, sizeof(tmpStr) - 1, "%u", familyInfo->GetMoney() );
	std::string text = "";
	thePlayerRole.GetGSCStringFromMoney(familyInfo->GetMoney(), text);
	m_pID_TEXT_Money->SetText(text.c_str());

	MeSprintf( tmpStr, sizeof(tmpStr) - 1, "%u", CSystemFamily::Instance()->GetMemeberCount() );
	m_pID_TEXT_Amount->SetText(tmpStr);

	m_pID_TEXT_Affiche->SetText( CSystemFamily::Instance()->GetFamilyInfo()->GetFamilyNotice() );

	CSystemFamily::Instance()->GetAllMemberInfo( m_vecFamilyMembers );

	int count = (int)m_vecFamilyMembers.size();
	for ( int i = 0; i < count; i ++ )
	{
		char strLevel[64] = {0};
		MeSprintf( strLevel, sizeof(strLevel) -1, "%u", m_vecFamilyMembers[i].GetLevel() );
		//char strMoney[64] = {0};
		//MeSprintf( strMoney, sizeof(strMoney) -1, "%u", m_vecFamilyMembers[i].GetDonateMoney() );

		std::string text = "";
		thePlayerRole.GetGSCStringFromMoney(m_vecFamilyMembers[i].GetDonateMoney(), text);
		//m_pID_TEXT_Money->SetText(text.c_str());
		
		DWORD clr = 0xFFFFFFFF;
		if ( m_vecFamilyMembers[i].GetOnLine() == false )
		{
			//不在线状态
			clr = 0xFF888888;
		}

		std::string strLeader = "";
		if ( m_vecFamilyMembers[i].GetPosition() == FamilyDefine::Position_Leader )
		{
			strLeader = theXmlString.GetString(eText_FamilyLeader); 
		}
		
		
		this->AddToList( m_vecFamilyMembers[i].GetName(), strLevel, CountryFunction::GetProfessionByID( m_vecFamilyMembers[i].GetProfession() ).c_str(), /*strMoney*/text.c_str(), strLeader.c_str(), "1", clr );
	}
}

void CUI_ID_FRAME_Family::RefreshValues()
{
	if ( !m_pID_FRAME_Family )
		return;
	InitialValues();
	SetButtonsEnable(false);
	if( CSystemFamily::Instance()->IsMeHaveFamily() )
	{
		if ( CSystemFamily::Instance()->IsMeFamilyLeader( thePlayerRole.GetDBID() ) )
		{
			SetButtonsEnable(true);
			m_pID_BUTTON_Exit->SetEnable(false);

			if ( CSystemFamily::Instance()->GetMemeberCount() <= 1 )
			{
				//当家族只有族长一个人的时候，转让和踢出成员是不可用的
				m_pID_BUTTON_Expel->SetEnable(false);
				m_pID_BUTTON_Attorn->SetEnable(false);
			}
			
		}
		else
		{
			//队员只有贡献资金和退出操作功能
			m_pID_BUTTON_Contribute->SetEnable(true);
			m_pID_BUTTON_Exit->SetEnable(true);
		}

		m_pID_LIST_FamilyName->SetCurSelIndex(0);
		ID_LIST_FamilyNameOnListSelectChange( m_pID_LIST_FamilyName, m_pID_LIST_FamilyName->GetCurSelItem() );
	}
}

void CUI_ID_FRAME_Family::AddToList( const char* name, const char* level, const char* profession, const char* money, const char* position, const char* line, DWORD clr )
{
	if ( !m_pID_FRAME_Family )
		return;
	ControlList::S_List	stItem;

	//特效处理列表
	stItem.SetData("", 0, NULL, clr);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_FamilyName->AddItem(&stItem, NULL, false);
	stItem.clear();

	//角色名称
	stItem.SetData(name, 0, NULL, clr);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_Name->AddItem(&stItem, NULL, false);
	stItem.clear();

	//等级
	stItem.SetData(level, 0, NULL, clr);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_Level->AddItem(&stItem, NULL, false);
	stItem.clear();

	//职业
	stItem.SetData(profession, 0, NULL, clr);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_Profession->AddItem(&stItem, NULL, false);
	stItem.clear();

	//资金贡献
	stItem.SetData(money, 0, NULL, clr);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_Contribute->AddItem(&stItem, NULL, false);
	stItem.clear();

	//家族职务
	stItem.SetData(position, 0, NULL, clr);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_ZhiWu->AddItem(&stItem, NULL, false);
	stItem.clear();

	//所在的线
	stItem.SetData(line, 0, NULL, clr);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_Line->AddItem(&stItem, NULL, false);
	stItem.clear();

}

// 装载UI
bool CUI_ID_FRAME_Family::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Family.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Family.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Family::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Family, s_CUI_ID_FRAME_FamilyOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Family, s_CUI_ID_FRAME_FamilyOnFrameRender );
	theUiManager.OnListSelectChange( ID_FRAME_Family, ID_LIST_FamilyName, s_CUI_ID_FRAME_FamilyID_LIST_FamilyNameOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Family, ID_LIST_Profession, s_CUI_ID_FRAME_FamilyID_LIST_ProfessionOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Family, ID_LIST_Contribute, s_CUI_ID_FRAME_FamilyID_LIST_ContributeOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Family, ID_LIST_Level, s_CUI_ID_FRAME_FamilyID_LIST_LevelOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_Family, ID_BUTTON_Expel, s_CUI_ID_FRAME_FamilyID_BUTTON_ExpelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Family, ID_BUTTON_Attorn, s_CUI_ID_FRAME_FamilyID_BUTTON_AttornOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Family, ID_BUTTON_Exit, s_CUI_ID_FRAME_FamilyID_BUTTON_ExitOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Family, ID_BUTTON_Affiche, s_CUI_ID_FRAME_FamilyID_BUTTON_AfficheOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Family, ID_BUTTON_HELP, s_CUI_ID_FRAME_FamilyID_BUTTON_HELPOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Family, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_FamilyID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Family, ID_BUTTON_Upgrade, s_CUI_ID_FRAME_FamilyID_BUTTON_UpgradeOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Family, ID_BUTTON_Contribute, s_CUI_ID_FRAME_FamilyID_BUTTON_ContributeOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_Family, ID_LIST_Name, s_CUI_ID_FRAME_FamilyID_LIST_NameOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Family, ID_LIST_ZhiWu, s_CUI_ID_FRAME_FamilyID_LIST_ZhiWuOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Family, ID_LIST_Line, s_CUI_ID_FRAME_FamilyID_LIST_LineOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_Family, ID_BUTTON_AddZY, s_CUI_ID_FRAME_FamilyID_BUTTON_AddZYOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Family, ID_BUTTON_ChangeZZ, s_CUI_ID_FRAME_FamilyID_BUTTON_ChangeZZOnButtonClick );

	m_pID_FRAME_Family = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Family );
	m_pID_LIST_FamilyName = (ControlList*)theUiManager.FindControl( ID_FRAME_Family, ID_LIST_FamilyName );
	m_pID_PICTURE_Logo = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Family, ID_PICTURE_Logo );
	m_pID_LIST_Profession = (ControlList*)theUiManager.FindControl( ID_FRAME_Family, ID_LIST_Profession );
	m_pID_LIST_Contribute = (ControlList*)theUiManager.FindControl( ID_FRAME_Family, ID_LIST_Contribute );
	m_pID_LIST_Level = (ControlList*)theUiManager.FindControl( ID_FRAME_Family, ID_LIST_Level );
	m_pID_TEXT_FamilyName = (ControlText*)theUiManager.FindControl( ID_FRAME_Family, ID_TEXT_FamilyName );
	m_pID_TEXT_ZuZhang = (ControlText*)theUiManager.FindControl( ID_FRAME_Family, ID_TEXT_ZuZhang );
	m_pID_TEXT_FamilyLevel = (ControlText*)theUiManager.FindControl( ID_FRAME_Family, ID_TEXT_FamilyLevel );
	m_pID_TEXT_Amount = (ControlText*)theUiManager.FindControl( ID_FRAME_Family, ID_TEXT_Amount );
	m_pID_TEXT_FanRongDu = (ControlText*)theUiManager.FindControl( ID_FRAME_Family, ID_TEXT_FanRongDu );
	m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_Family, ID_TEXT_Money );
	m_pID_TEXT_Affiche = (ControlText*)theUiManager.FindControl( ID_FRAME_Family, ID_TEXT_Affiche );
	m_pID_TEXT_FamilyInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_Family, ID_TEXT_FamilyInfo );
	m_pID_BUTTON_Expel = (ControlButton*)theUiManager.FindControl( ID_FRAME_Family, ID_BUTTON_Expel );
	m_pID_BUTTON_Attorn = (ControlButton*)theUiManager.FindControl( ID_FRAME_Family, ID_BUTTON_Attorn );
	m_pID_BUTTON_Exit = (ControlButton*)theUiManager.FindControl( ID_FRAME_Family, ID_BUTTON_Exit );
	m_pID_BUTTON_Affiche = (ControlButton*)theUiManager.FindControl( ID_FRAME_Family, ID_BUTTON_Affiche );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_Family, ID_BUTTON_HELP );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_Family, ID_BUTTON_CLOSE );
	m_pID_BUTTON_Upgrade = (ControlButton*)theUiManager.FindControl( ID_FRAME_Family, ID_BUTTON_Upgrade );
	m_pID_BUTTON_Contribute = (ControlButton*)theUiManager.FindControl( ID_FRAME_Family, ID_BUTTON_Contribute );
	m_pID_LIST_Name = (ControlList*)theUiManager.FindControl( ID_FRAME_Family, ID_LIST_Name );
	m_pID_LIST_ZhiWu = (ControlList*)theUiManager.FindControl( ID_FRAME_Family, ID_LIST_ZhiWu );
	m_pID_LIST_Line = (ControlList*)theUiManager.FindControl( ID_FRAME_Family, ID_LIST_Line );
	m_pID_BUTTON_AddZY = (ControlButton*)theUiManager.FindControl( ID_FRAME_Family, ID_BUTTON_AddZY );
	m_pID_BUTTON_ChangeZZ = (ControlButton*)theUiManager.FindControl( ID_FRAME_Family, ID_BUTTON_ChangeZZ );

	assert( m_pID_FRAME_Family );
	assert( m_pID_LIST_FamilyName );
	assert( m_pID_PICTURE_Logo );
	assert( m_pID_LIST_Profession );
	assert( m_pID_LIST_Contribute );
	assert( m_pID_LIST_Level );
	assert( m_pID_TEXT_FamilyName );
	assert( m_pID_TEXT_ZuZhang );
	assert( m_pID_TEXT_FamilyLevel );
	assert( m_pID_TEXT_Amount );
	assert( m_pID_TEXT_FanRongDu );
	assert( m_pID_TEXT_Money );
	assert( m_pID_TEXT_Affiche );
	assert( m_pID_TEXT_FamilyInfo );
	assert( m_pID_BUTTON_Expel );
	assert( m_pID_BUTTON_Attorn );
	assert( m_pID_BUTTON_Exit );
	assert( m_pID_BUTTON_Affiche );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_Upgrade );
	assert( m_pID_BUTTON_Contribute );
	assert( m_pID_LIST_Name );
	assert( m_pID_LIST_ZhiWu );
	assert( m_pID_LIST_Line );
	assert( m_pID_BUTTON_AddZY );
	assert( m_pID_BUTTON_ChangeZZ );
	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Family::_UnLoadUI()
{
	m_pID_FRAME_Family = NULL;
	m_pID_LIST_FamilyName = NULL;
	m_pID_PICTURE_Logo = NULL;
	m_pID_LIST_Profession = NULL;
	m_pID_LIST_Contribute = NULL;
	m_pID_LIST_Level = NULL;
	m_pID_TEXT_FamilyName = NULL;
	m_pID_TEXT_ZuZhang = NULL;
	m_pID_TEXT_FamilyLevel = NULL;
	m_pID_TEXT_Amount = NULL;
	m_pID_TEXT_FanRongDu = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_TEXT_Affiche = NULL;
	m_pID_TEXT_FamilyInfo = NULL;
	m_pID_BUTTON_Expel = NULL;
	m_pID_BUTTON_Attorn = NULL;
	m_pID_BUTTON_Exit = NULL;
	m_pID_BUTTON_Affiche = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Upgrade = NULL;
	m_pID_BUTTON_Contribute = NULL;
	m_pID_LIST_Name = NULL;
	m_pID_LIST_ZhiWu = NULL;
	m_pID_LIST_Line = NULL;
	m_pID_BUTTON_AddZY = NULL;
	m_pID_BUTTON_ChangeZZ = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\Family.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Family::_IsVisable()
{
	if ( !m_pID_FRAME_Family )
		return false;
	return m_pID_FRAME_Family->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Family::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_Family )
		return ;
	m_pID_FRAME_Family->SetVisable( bVisable );
	if ( bVisable )
	{
		if ( CSystemFamily::Instance()->IsMeHaveFamily() == false )
		{
			m_pID_FRAME_Family->SetVisable( false );
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_FamilyHaveNoFamily) );
			return;
		}
		
		RefreshValues();
	}
	
}
