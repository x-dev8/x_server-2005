/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\GuildBaseInfo.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GuildBaseInfo.h"
#include "GuildInfo.h"
#include "GuildMember.h"
#include "PlayerRole.h"
#include "GuildSQ.h"
#include "NetworkInput.h"
#include "GuildApply.h"
#include "CountryDefine.h"
#include "MessageBox.h"
#include "XmlStringLanguage.h"
#include "ScreenInfoManager.h"
#include "chatcheck.h"
#include "AddGuildGeneralBattle.h"
#include "GuildGeneralBattleList.h"
extern int g_nCharacterDBID;
CUI_ID_FRAME_GuildBaseInfo s_CUI_ID_FRAME_GuildBaseInfo;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GuildBaseInfo, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GuildBaseInfo, OnFrameRender )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GuildBaseInfo, ID_CHECKBOX_GuildMemberOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GuildBaseInfo, ID_CHECKBOX_GuildInfoOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GuildBaseInfo, ID_CHECKBOX_GuildRequestOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GuildBaseInfo, ID_CHECKBOX_AddGuildGeneralOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GuildBaseInfo, ID_CHECKBOX_GuildGeneralListOnCheckBoxCheck )
CUI_ID_FRAME_GuildBaseInfo::CUI_ID_FRAME_GuildBaseInfo()
{
	// Member
	m_pID_FRAME_GuildBaseInfo = NULL;
	m_pID_CHECKBOX_GuildMember = NULL;
	m_pID_CHECKBOX_GuildInfo = NULL;
	m_pID_CHECKBOX_GuildRequest = NULL;

	m_pID_CHECKBOX_AddGuildGeneral=NULL;
	m_pID_CHECKBOX_GuildGeneralList=NULL;

	
	m_Master = NULL;
	m_GuileMe = NULL;
	m_GuildNum = 0;
	m_GuildOnLineNum = 0;
	m_GuildMemberOnLine.clear();
	m_GuildMenberNonOnLine.clear();
}
// Frame
bool CUI_ID_FRAME_GuildBaseInfo::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_GuildBaseInfo::OnFrameRender()
{
	return true;
}
// CheckBox
void CUI_ID_FRAME_GuildBaseInfo::ID_CHECKBOX_GuildMemberOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_CHECKBOX_GuildMember->IsChecked())
	{
		m_pID_CHECKBOX_GuildMember->SetCheck(true);
		return;
	}
	m_pID_CHECKBOX_GuildInfo->SetCheck(false);
	m_pID_CHECKBOX_GuildRequest->SetCheck(false);
	m_pID_CHECKBOX_AddGuildGeneral->SetCheck(false);
	m_pID_CHECKBOX_GuildGeneralList->SetCheck(false);
	ShowUI(GuildUIType::GUT_Mamber);
}
void CUI_ID_FRAME_GuildBaseInfo::ID_CHECKBOX_AddGuildGeneralOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  )
{
	if(!m_pID_CHECKBOX_AddGuildGeneral->IsChecked())
	{
		m_pID_CHECKBOX_AddGuildGeneral->SetCheck(true);
		return;
	}
	m_pID_CHECKBOX_GuildMember->SetCheck(false);
	m_pID_CHECKBOX_GuildInfo->SetCheck(false);
	m_pID_CHECKBOX_GuildRequest->SetCheck(false);
	m_pID_CHECKBOX_GuildGeneralList->SetCheck(false);
	ShowUI(GuildUIType::GUT_Add);
}
void CUI_ID_FRAME_GuildBaseInfo::ID_CHECKBOX_GuildGeneralListOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  )
{
	if(!m_pID_CHECKBOX_GuildGeneralList->IsChecked())
	{
		m_pID_CHECKBOX_GuildGeneralList->SetCheck(true);
		return;
	}
	m_pID_CHECKBOX_GuildMember->SetCheck(false);
	m_pID_CHECKBOX_GuildInfo->SetCheck(false);
	m_pID_CHECKBOX_GuildRequest->SetCheck(false);
	m_pID_CHECKBOX_AddGuildGeneral->SetCheck(false);
	ShowUI(GuildUIType::GUT_List);
}
// CheckBox
void CUI_ID_FRAME_GuildBaseInfo::ID_CHECKBOX_GuildInfoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_CHECKBOX_GuildInfo->IsChecked())
	{
		m_pID_CHECKBOX_GuildInfo->SetCheck(true);
		return;
	}
	m_pID_CHECKBOX_GuildMember->SetCheck(false);
	m_pID_CHECKBOX_GuildRequest->SetCheck(false);
	m_pID_CHECKBOX_AddGuildGeneral->SetCheck(false);
	m_pID_CHECKBOX_GuildGeneralList->SetCheck(false);
	ShowUI(GuildUIType::GUT_Info);
}
// CheckBox
void CUI_ID_FRAME_GuildBaseInfo::ID_CHECKBOX_GuildRequestOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_CHECKBOX_GuildRequest->IsChecked())
	{
		m_pID_CHECKBOX_GuildRequest->SetCheck(true);
		return;
	}
	m_pID_CHECKBOX_GuildInfo->SetCheck(false);
	m_pID_CHECKBOX_GuildMember->SetCheck(false);
	m_pID_CHECKBOX_AddGuildGeneral->SetCheck(false);
	m_pID_CHECKBOX_GuildGeneralList->SetCheck(false);
	ShowUI(GuildUIType::GUT_SQ);
}
// װ��UI
bool CUI_ID_FRAME_GuildBaseInfo::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GuildBaseInfo.MEUI",false,UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("��ȡ�ļ�[Data\\UI\\GuildBaseInfo.MEUI]ʧ��")
		return false;
	}
	return DoControlConnect();
}
void CUI_ID_FRAME_GuildBaseInfo::InitializeAtEnterWorld()
{
	LoadUI();
	m_GuildCampBattleConfig.OnLoadFilePath(GUILDCAMPBATTLE_FILEPATH);//���������ļ�
}
// �����ؼ�
bool CUI_ID_FRAME_GuildBaseInfo::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GuildBaseInfo, s_CUI_ID_FRAME_GuildBaseInfoOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GuildBaseInfo, s_CUI_ID_FRAME_GuildBaseInfoOnFrameRender );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GuildBaseInfo, ID_CHECKBOX_GuildMember, s_CUI_ID_FRAME_GuildBaseInfoID_CHECKBOX_GuildMemberOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GuildBaseInfo, ID_CHECKBOX_GuildInfo, s_CUI_ID_FRAME_GuildBaseInfoID_CHECKBOX_GuildInfoOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GuildBaseInfo, ID_CHECKBOX_GuildRequest, s_CUI_ID_FRAME_GuildBaseInfoID_CHECKBOX_GuildRequestOnCheckBoxCheck );

	theUiManager.OnCheckBoxCheck( ID_FRAME_GuildBaseInfo, ID_CHECKBOX_AddGuildGeneral, s_CUI_ID_FRAME_GuildBaseInfoID_CHECKBOX_AddGuildGeneralOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GuildBaseInfo, ID_CHECKBOX_GuildGeneralList, s_CUI_ID_FRAME_GuildBaseInfoID_CHECKBOX_GuildGeneralListOnCheckBoxCheck );

	m_pID_FRAME_GuildBaseInfo = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GuildBaseInfo );
	m_pID_CHECKBOX_GuildMember = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GuildBaseInfo, ID_CHECKBOX_GuildMember );
	m_pID_CHECKBOX_GuildInfo = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GuildBaseInfo, ID_CHECKBOX_GuildInfo );
	m_pID_CHECKBOX_GuildRequest = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GuildBaseInfo, ID_CHECKBOX_GuildRequest );

	m_pID_CHECKBOX_AddGuildGeneral = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GuildBaseInfo, ID_CHECKBOX_AddGuildGeneral );
	m_pID_CHECKBOX_GuildGeneralList = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GuildBaseInfo, ID_CHECKBOX_GuildGeneralList );

	assert( m_pID_FRAME_GuildBaseInfo );
	assert( m_pID_CHECKBOX_GuildMember );
	assert( m_pID_CHECKBOX_GuildInfo );
	assert( m_pID_CHECKBOX_GuildRequest );
	assert( m_pID_CHECKBOX_AddGuildGeneral );
	assert( m_pID_CHECKBOX_GuildGeneralList );

	SetVisable(false);
	return true;
}
	// ж��UI
bool CUI_ID_FRAME_GuildBaseInfo::_UnLoadUI()
{
	m_pID_FRAME_GuildBaseInfo = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GuildBaseInfo.MEUI" );
}
// �Ƿ����
bool CUI_ID_FRAME_GuildBaseInfo::_IsVisable()
{
	return m_pID_FRAME_GuildBaseInfo->IsVisable();
}
// �����Ƿ����
void CUI_ID_FRAME_GuildBaseInfo::_SetVisable( const bool bVisable )
{
	if(bVisable)
	{
		if(thePlayerRole.GetCountry() == CountryDefine::Country_Init)
		{
			//û�й��� �޷�����Ui ����MessageBox��ʾ
			m_pID_FRAME_GuildBaseInfo->SetVisable( false );
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_NonCountryByGuild));
			return;
		}
		if(!InitGuildInfo())
		{
			//��ʾ�޹��� ���߿���ȫ�������б�
			m_pID_FRAME_GuildBaseInfo->SetVisable( false );
			s_CUI_ID_FRAME_GuildApply.SetVisable( !s_CUI_ID_FRAME_GuildApply.IsVisable() );
			return;
		}
		ShowUI();
	}
	m_pID_FRAME_GuildBaseInfo->SetVisable( bVisable );
}
void CUI_ID_FRAME_GuildBaseInfo::ShowUI(GuildUIType Type)
{
	//����ָ�����ӿؼ���ʾ
 	switch(Type)
	{
	case GuildUIType::GUT_Info:
		{
			s_CUI_ID_FRAME_GuildMember.SetVisable(false);//������ʾ
			s_CUI_ID_FRAME_GuildInfo.SetVisable(true);
			s_CUI_ID_FRAME_GuildSQ.SetVisable(false);
			s_CUI_ID_FRAME_AddGuildGeneralBattle.SetVisable(false);
			s_CUI_ID_FRAME_GuildGeneralBattleList.SetVisable(false);

			//��ʾ����Ļ�����Ϣҳ��
			m_pID_CHECKBOX_GuildInfo->SetCheck(true);
			m_pID_CHECKBOX_GuildMember->SetCheck(false);
			m_pID_CHECKBOX_GuildRequest->SetCheck(false);
			m_pID_CHECKBOX_AddGuildGeneral->SetCheck(false);
			m_pID_CHECKBOX_GuildGeneralList->SetCheck(false);
		}
		break;
	case GuildUIType::GUT_Mamber:
		{
			s_CUI_ID_FRAME_GuildMember.SetVisable(true);//������ʾ
			s_CUI_ID_FRAME_GuildInfo.SetVisable(false);
			s_CUI_ID_FRAME_GuildSQ.SetVisable(false);
			s_CUI_ID_FRAME_AddGuildGeneralBattle.SetVisable(false);
			s_CUI_ID_FRAME_GuildGeneralBattleList.SetVisable(false);

			//��ʾ�������ҵ��б�
			m_pID_CHECKBOX_GuildInfo->SetCheck(false);
			m_pID_CHECKBOX_GuildMember->SetCheck(true);
			m_pID_CHECKBOX_GuildRequest->SetCheck(false);
			m_pID_CHECKBOX_AddGuildGeneral->SetCheck(false);
			m_pID_CHECKBOX_GuildGeneralList->SetCheck(false);
		}
		break;
	case GuildUIType::GUT_SQ:
		{
			s_CUI_ID_FRAME_GuildMember.SetVisable(false);//������ʾ
			s_CUI_ID_FRAME_GuildInfo.SetVisable(false);
			s_CUI_ID_FRAME_GuildSQ.SetVisable(true);
			s_CUI_ID_FRAME_AddGuildGeneralBattle.SetVisable(false);
			s_CUI_ID_FRAME_GuildGeneralBattleList.SetVisable(false);

			//��ʾ���������б�
			m_pID_CHECKBOX_GuildInfo->SetCheck(false);
			m_pID_CHECKBOX_GuildMember->SetCheck(false);
			m_pID_CHECKBOX_GuildRequest->SetCheck(true);
			m_pID_CHECKBOX_AddGuildGeneral->SetCheck(false);
			m_pID_CHECKBOX_GuildGeneralList->SetCheck(false);
		}
		break;
	case GuildUIType::GUT_Add:
		{
			s_CUI_ID_FRAME_GuildMember.SetVisable(false);//������ʾ
			s_CUI_ID_FRAME_GuildInfo.SetVisable(false);
			s_CUI_ID_FRAME_GuildSQ.SetVisable(false);
			s_CUI_ID_FRAME_AddGuildGeneralBattle.SetVisable(true);
			s_CUI_ID_FRAME_GuildGeneralBattleList.SetVisable(false);

			m_pID_CHECKBOX_GuildInfo->SetCheck(false);
			m_pID_CHECKBOX_GuildMember->SetCheck(false);
			m_pID_CHECKBOX_GuildRequest->SetCheck(false);
			m_pID_CHECKBOX_AddGuildGeneral->SetCheck(true);
			m_pID_CHECKBOX_GuildGeneralList->SetCheck(false);
		}
		break;
	case GuildUIType::GUT_List:
		{
			s_CUI_ID_FRAME_GuildMember.SetVisable(false);//������ʾ
			s_CUI_ID_FRAME_GuildInfo.SetVisable(false);
			s_CUI_ID_FRAME_GuildSQ.SetVisable(false);
			s_CUI_ID_FRAME_AddGuildGeneralBattle.SetVisable(false);
			s_CUI_ID_FRAME_GuildGeneralBattleList.SetVisable(true);

			m_pID_CHECKBOX_GuildInfo->SetCheck(false);
			m_pID_CHECKBOX_GuildMember->SetCheck(false);
			m_pID_CHECKBOX_GuildRequest->SetCheck(false);
			m_pID_CHECKBOX_AddGuildGeneral->SetCheck(false);
			m_pID_CHECKBOX_GuildGeneralList->SetCheck(true);
		}
		break;
	}
}
bool CUI_ID_FRAME_GuildBaseInfo::InitGuildInfo()
{
	//����Ui�ϵ�һЩ�������� ����᳤ �����Ա�ķ���ʲô��
	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	if(pGuild == NULL || pGuild->GetGuildID() == GuildDefine::InitID) return false;//�ް���
	if(m_GuildNum >0) return true;
	//����һЩ��������Ϣ ���Ҳ����UI ��ҪUpdate��ʱ����� ��֤UI������ʱ���µ�
	m_GuildNum = pGuild->GetMemberCount();
	m_GuildMemberOnLine.clear();
	m_GuildMenberNonOnLine.clear();
	for(int i =0;i<m_GuildNum;++i)
	{
		GuildMember * pMember = pGuild->GetMember(i);
		if(!pMember) continue;
		if(pMember->GetID() == thePlayerRole.GetDBID())
		{
			m_GuileMe = pMember;
		}
		if(pMember->GetPosition() == GuildDefine::Position_Master)
		{
			m_Master = pMember;
		}

		if(pMember->GetOnLine())
		{
			m_GuildMemberOnLine.push_back(pMember);
		}
		else
		{
			m_GuildMenberNonOnLine.push_back(pMember);
		}
	}
	m_GuildOnLineNum = m_GuildMemberOnLine.size();
	m_GuildName  = pGuild->GetGuildName();
	m_GuildCommon = pGuild->GetGuildNotice();//���ṫ��
	m_GuildMoney = pGuild->GetGuildMoney();
	m_GuildLevel = pGuild->GetGuildLevel();
	m_GuildExp = pGuild->GetGuildExp();
	m_Mission =	pGuild->GetGuildMission();
	m_GuildStrongth = pGuild->GetGuildStrength();
	//���㹫���ʵ��
	return true;
}

void CUI_ID_FRAME_GuildBaseInfo::OnUpdateUiInfo()
{
	//���������ݷ��ͱ仯��ʱ��
	m_GuildNum = 0;
	InitGuildInfo();
	s_CUI_ID_FRAME_GuildMember.OnUpdateUiInfo();
	s_CUI_ID_FRAME_GuildInfo.OnUpdateUiInfo();
	s_CUI_ID_FRAME_GuildSQ.OnUpdateUiInfo();
	s_CUI_ID_FRAME_AddGuildGeneralBattle.OnUpdateUiInfo();
	s_CUI_ID_FRAME_GuildGeneralBattleList.OnUpdateUiInfo();
}
string CUI_ID_FRAME_GuildBaseInfo::GetGuildMastrName() const
{
	if(!m_Master)
		return NULL;
	return m_Master->GetName();
}
bool CUI_ID_FRAME_GuildBaseInfo::IsCanCommonByMe()
{
	if(!m_GuileMe)
		return false;
	return ( GuildDefine::GetRightByPositon(m_GuileMe->GetPosition()) & GuildDefine::Right_Notice ) != 0;
}
bool CUI_ID_FRAME_GuildBaseInfo::IsCanDoByRight(uint32 Right)
{
	if(!m_GuileMe)
		return false;
	return ( GuildDefine::GetRightByPositon(m_GuileMe->GetPosition()) & Right ) != 0;
}
//����
void CUI_ID_FRAME_GuildBaseInfo::ChangeFamilyName( const char* pName )
{
	if (pName && pName[0] != '\0')
	{
		CGangMgr* theGuild = thePlayerRole.GetGangMgr();
		if(theGuild == NULL)
		{
			return ;
		}

		GuildMember* member = theGuild->FindByDBId(g_nCharacterDBID);
		if (member)
		{
			MsgGuildFamilyChangeReq msgModifyTong;
			strcpy(msgModifyTong.szName, pName);
			msgModifyTong.uchFamilyID = member->GetFamilyID();
			GettheNetworkInput().SendMsg(&msgModifyTong);
		}
	}
}
void CUI_ID_FRAME_GuildBaseInfo::ShowSQUI()
{
	ShowUI(GuildUIType::GUT_SQ);
	m_pID_FRAME_GuildBaseInfo->SetVisable( true );
}
void CUI_ID_FRAME_GuildBaseInfo::ShowGuildGeneralList()
{
	ShowUI(GuildUIType::GUT_List);
	m_pID_FRAME_GuildBaseInfo->SetVisable( true );
}
void CUI_ID_FRAME_GuildBaseInfo::SetMemberCampBattleValue(unsigned int Value,GuildMember* pMember)
{
	//����ָ�������Աָ����ս��
	if(!pMember)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildCampBattle_Non));
		return;
	}
	//1.�Ƿ�Ϊ����
	if(!m_Master || (m_Master->GetID() != thePlayerRole.GetDBID()))
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildCampBattle_Master));
		return;
	}
	else if(pMember->GetCampBattleValue() & Value)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildCampBattle_Dou));
		return;
	}
	//2.�ж�����Ŀ��ĵȼ� ְҵ  ���� 
	//3.�ж�ָ��Ȩ���ڹ�������� 
	GuildCampBattleSetting * pSetting = NULL;
	switch(Value)
	{
	case GuildDefine::CampBattleCountry:
		pSetting  = &m_GuildCampBattleConfig.m_CountrySetting;
		break;
	case GuildDefine::CampBattleGuild:
		pSetting  = &m_GuildCampBattleConfig.m_GuildSetting;
		break;
	case GuildDefine::CampBattleGuildUnion:
		pSetting  = &m_GuildCampBattleConfig.m_GuildUnionSetting;
		break;
	case GuildDefine::GameBattleGuildGeneral:
		pSetting  = &m_GuildCampBattleConfig.m_GuildGeneralSetting;
		break;
	}
	if(!pSetting)
		return;
	else if(pSetting->MinLevel > pMember->GetLevel())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildCampBattle_Level));
		return;
	}
	else if(pSetting->Profession != pMember->GetProfession() && pSetting->Profession != 0)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildCampBattle_Position));
		return;
	}
	else if(pSetting->Offer > pMember->GetOffer())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildCampBattle_Offer));
		return;
	}
	else
	{
		//�жϹ��������
		int Sum = 0;
		vector<GuildMember*>::iterator Iter = m_GuildMemberOnLine.begin();
		for(;Iter != m_GuildMemberOnLine.end();++Iter)
		{
			if((*Iter)->GetCampBattleValue() & Value)
				++Sum;
		}
		Iter = m_GuildMenberNonOnLine.begin();
		for(;Iter != m_GuildMenberNonOnLine.end();++Iter)
		{
			if((*Iter)->GetCampBattleValue() & Value)
				++Sum;
		}
		if(Sum >= pSetting->MaxSum)
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildCampBattle_MaxSum));
			return;
		}
	}
	//4.�������GameServerȥ ���ù����ԱΪָ����Ȩ�� 
	//������ �ͻ��� �ж��ǿ��Ը��������Ȩ�޵ķ��͵�GameServerȥ
	MsgSetGuildCampBattleValue msg;
	msg.TargetID = pMember->GetID();
	msg.CampBattleValue = Value;
	msg.IsAdd = true;//���Ȩ��
	GettheNetworkInput().SendMsg(&msg);
}
void CUI_ID_FRAME_GuildBaseInfo::DelMemberCampBattleValue(unsigned int Value,GuildMember* pMember)
{
	if(!pMember)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildCampBattle_Non));
		return;
	}
	else if(!m_Master || (m_Master->GetID() != thePlayerRole.GetDBID()))
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildCampBattle_Master));
		return;
	}
	else if(pMember->GetCampBattleValue() & Value)
	{
		MsgSetGuildCampBattleValue msg;
		msg.TargetID = pMember->GetID();
		msg.CampBattleValue = Value;
		msg.IsAdd = false;//���Ȩ��
		GettheNetworkInput().SendMsg(&msg);
	}
}
void CUI_ID_FRAME_GuildBaseInfo::ChangeGuildName(const char * NewName)
{
	//�޸Ĺ�������
	if(!thePlayerRole.GetGangMgr() || thePlayerRole.GetGangMgr()->GetGuildMasterID() != thePlayerRole.GetDBID())
	{
		//��ʾ��� �ǹ���᳤�������޸�����
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString( eText_GuildChangeName_NotMaster ) );
		return;
	}
	
	if(strcoll(thePlayerRole.GetGangMgr()->GetGuildMasterName(),NewName) == 0)
	{
		//����û�仯 �޷��޸�
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString( eText_GuildChangeName_NonChange ) );
		return;
	}
	//���µ����ƽ��м��
	//�����������ַ����
	bool bIsInLow	= CChatCheck::getInstance()->CheckStringInLow(NewName);
	if (!bIsInLow )//������
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString( eText_GuildChangeName_Error ) );
		return;
	}
	if( strlen(NewName) <= 0)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString( eText_GuildChangeName_Error2 ) );
		return;
	}
	else if( strlen(NewName) > GuildDefine::MaxNameLength  )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString( eText_GuildChangeName_Error3 ) );
		return;
	}
    if(strchr(NewName, ' ') != NULL)
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString( eText_GuildChangeName_Error4 ) );
        return;
    }
	//���������GameServerȥ 
	MsgChangeGuldNameReq msg;
	msg.GuildID = thePlayerRole.GetGangMgr()->GetGuildID();
	strcpy_s(msg.Name,GuildDefine::MaxNameLength-1,NewName);
	GettheNetworkInput().SendMsg(&msg);
}