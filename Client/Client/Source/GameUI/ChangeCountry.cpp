/********************************************************************
Created by UIEditor.exe
FileName: E:\Zxc\3Guo Client 8.30\3Guo Client\Data\Ui\ChangeCountry.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ChangeCountry.h"
#include "NetworkInput.h"
#include "CountryMessage.h"
#include "CountryDefine.h"
#include "PlayerRole.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Main.h"
#include "MainMenu.h"
#include "CountryBaseInfo.h"
#include "ChangeCountryConfig.h"

extern bool g_RenderTips;

CUI_ID_FRAME_ChangeCountry s_CUI_ID_FRAME_ChangeCountry;
MAP_FRAME_RUN( s_CUI_ID_FRAME_ChangeCountry, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ChangeCountry, OnFrameRender )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ChangeCountry, ID_CHECKBOX_ShuGuoOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ChangeCountry, ID_CHECKBOX_WeiGuoOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ChangeCountry, ID_CHECKBOX_WuGuoOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ChangeCountry, ID_BUTTON_JoinOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ChangeCountry, ID_BUTTON_ExitOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ChangeCountry, ID_BUTTON_RandOnButtonClick )
CUI_ID_FRAME_ChangeCountry::CUI_ID_FRAME_ChangeCountry()
{
	// Member
	m_pID_FRAME_ChangeCountry = NULL;
	m_pID_CHECKBOX_ShuGuo = NULL;
	m_pID_CHECKBOX_WeiGuo = NULL;
	m_pID_CHECKBOX_WuGuo = NULL;
	m_pID_BUTTON_Join = NULL;
	m_pID_BUTTON_Exit = NULL;
	m_pID_BUTTON_Rand = NULL;

	check_ShuGuo = false;
	check_WeiGuo = false;
	check_WuGuo = false;

}
// Frame
bool CUI_ID_FRAME_ChangeCountry::OnFrameRun()
{
	if(m_pID_FRAME_ChangeCountry && s_CUI_ID_FRAME_ChangeCountry.IsVisable()) 
		theUiManager.ToTop(m_pID_FRAME_ChangeCountry);
	
	return true;
}
bool CUI_ID_FRAME_ChangeCountry::OnFrameRender()
{
	return true;
}
// CheckBox
void CUI_ID_FRAME_ChangeCountry::ID_CHECKBOX_ShuGuoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_ChangeCountry)
		return ;
	m_pID_CHECKBOX_ShuGuo->SetCheck(true);
	m_pID_CHECKBOX_WeiGuo->SetCheck(false);
	m_pID_CHECKBOX_WuGuo->SetCheck(false);

	check_ShuGuo = true;
	check_WeiGuo = false;
	check_WuGuo = false;

}
// CheckBox
void CUI_ID_FRAME_ChangeCountry::ID_CHECKBOX_WeiGuoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_ChangeCountry)
		return ;
	m_pID_CHECKBOX_ShuGuo->SetCheck(false);
	m_pID_CHECKBOX_WeiGuo->SetCheck(true);
	m_pID_CHECKBOX_WuGuo->SetCheck(false);

	check_ShuGuo = false;
	check_WeiGuo = true;
	check_WuGuo = false;

}
// CheckBox
void CUI_ID_FRAME_ChangeCountry::ID_CHECKBOX_WuGuoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_ChangeCountry)
		return ;
	m_pID_CHECKBOX_ShuGuo->SetCheck(false);
	m_pID_CHECKBOX_WeiGuo->SetCheck(false);
	m_pID_CHECKBOX_WuGuo->SetCheck(true);

	check_ShuGuo = false;
	check_WeiGuo = false;
	check_WuGuo = true;
}
// Button
bool CUI_ID_FRAME_ChangeCountry::ID_BUTTON_JoinOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ChangeCountry)
		return false;
	s_CUI_ID_FRAME_MainMenu.SetVisable(true);
	s_CUI_ID_FRAME_MAIN.SetVisable(true);

	int c_id = GetCountryId();
	if (c_id == CountryDefine::Country_Init)
	{
		return false;
	}
	
	//�ж����¼�����һ����ѹ�
	if (CountryDefine::Country_Init == thePlayerRole.GetCountry())
	{
		MsgCountryChangeReq msg;	
		msg.uchCountryID = c_id;
		if (msg.uchCountryID == 0)
		{
			LOG_MESSAGE(INFO_LOG,LOG_PRIORITY_INFO,"zhuxincong1�ͻ����������IDΪ%d",msg.uchCountryID);
		}
		GettheNetworkInput().SendMsg(&msg);
	}
	//else
	//{
	//	//��ҽ����ѹ� ������Ҫ�ж���ҵ������Ƿ����� �����ļ���ȡ
	//	if(thePlayerRole.GetGroupId() != -1)
	//	{
	//		//��ʾ����ж��� �޷��ѹ�
	//		s_CUI_ID_FRAME_BaseInfo.TellBetrayCountryResult(MsgCountryChangeAck::ECD_HaveTeam);
	//		return true;
	//	}
	//	if(thePlayerRole.GetCountry() == c_id || c_id == CountryDefine::Country_Init)
	//	{
	//		//������ѡ��ͬһ����
	//		s_CUI_ID_FRAME_BaseInfo.TellBetrayCountryResult(MsgCountryChangeAck::ECD_SameCountry);
	//		return true;
	//	}
	//	bool isCreTeacher = false;
	//	int studentSum = 0;
	//	thePlayerRole.CalculateTeacherStudent(isCreTeacher,studentSum);
	//	if(isCreTeacher)
	//	{
	//		//��ʦ�� �������ѹ�
	//		s_CUI_ID_FRAME_BaseInfo.TellBetrayCountryResult(MsgCountryChangeAck::ECD_HaveTeacher);
	//		return true;
	//	}
	//	if(studentSum >0)
	//	{
	//		//��ͽ�� �������ѹ�
	//		s_CUI_ID_FRAME_BaseInfo.TellBetrayCountryResult(MsgCountryChangeAck::ECD_HaveStudent);
	//		return true;
	//	}
	//	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	//	if(pGuild && pGuild->GetGuildID() != GuildDefine::InitID) 
	//	{
	//		//�а��� 
	//		s_CUI_ID_FRAME_BaseInfo.TellBetrayCountryResult(MsgCountryChangeAck::ECD_HaveGuild);
	//		return true;
	//	}
	//	if(thePlayerRole.GetCharInfo2().baseinfo.liveinfo.uchPosition)
	//	{
	//		//�й�ְ���� �޷��ѹ�
	//		s_CUI_ID_FRAME_BaseInfo.TellBetrayCountryResult(MsgCountryChangeAck::ECD_HaveOff);
	//		return true;
	//	}
	//	//�жϵȼ�
	//	if((theChangeCountryConfig.GetMinLevel() != -1 && theChangeCountryConfig.GetMinLevel() > thePlayerRole.GetLevel()) || 
	//		(theChangeCountryConfig.GetMaxLevel() != -1 && theChangeCountryConfig.GetMaxLevel()<thePlayerRole.GetLevel()))
	//	{
	//		s_CUI_ID_FRAME_BaseInfo.TellBetrayCountryResult(MsgCountryChangeAck::ECD_Config);
	//		return true;
	//	}
	//	int ItemID = theChangeCountryConfig.GetItemID(thePlayerRole.GetCountry(),c_id,thePlayerRole.GetWeakCountryID(),thePlayerRole.GetStrongthCountryID());
	//	int ItemNum = theChangeCountryConfig.GetItemSum(thePlayerRole.GetCountry(),c_id,thePlayerRole.GetWeakCountryID(),thePlayerRole.GetStrongthCountryID());
	//	if(ItemID != 0 && ItemNum != 0)
	//	{
	//		//��ȡ��Ʒ���� �õ���������
	//		ItemDefine::SItemCommon *pItem = GettheItemDetail().GetItemByID(ItemID);
	//		if(!pItem)
	//			return true;
	//		CItemBag2 * pBag=NULL;
	//		switch(thePlayerRole.GetBagTypeByItemType(pItem->costType))
	//		{
	//		case BT_TaskBag:
	//			pBag = &thePlayerRole.m_bagTask;
	//			break;
	//		case BT_MaterialBag:
	//			pBag = &thePlayerRole.m_bagMaterial;
	//			break;
	//		case BT_NormalItemBag:
	//			pBag = &thePlayerRole.m_bag;
	//			break;
	//		}
	//		if(!pBag)
	//			return true;
	//		int sum =pBag->GetItemCount(ItemID);
	//		if(sum < ItemNum)
	//		{
	//			s_CUI_ID_FRAME_BaseInfo.TellBetrayCountryResult(MsgCountryChangeAck::ECD_Config);
	//			return true;
	//		}
	//	}
	//	if(theChangeCountryConfig.GetQuestIndex() !=-1)
	//	{
	//		CPlayerRole::QuestInfo* pQuestInfo = thePlayerRole.FindVariableInfoById(theChangeCountryConfig.GetQuestIndex());
	//		if(!pQuestInfo) return true;
	//		if(pQuestInfo->chState != theChangeCountryConfig.GetQuestValue() )
	//		{
	//			s_CUI_ID_FRAME_BaseInfo.TellBetrayCountryResult(MsgCountryChangeAck::ECD_Config);
	//			return true;
	//		}
	//	}
	//	MsgCountryChangeReq msg;	
	//	msg.uchCountryID = c_id;
	//	GettheNetworkInput().SendMsg(&msg);
	//}
	Refresh();
	return true;
}
// Button
bool CUI_ID_FRAME_ChangeCountry::ID_BUTTON_ExitOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ChangeCountry)
		return false;
	SetVisable(false);
	s_CUI_ID_FRAME_MainMenu.SetVisable(true);
	s_CUI_ID_FRAME_MAIN.SetVisable(true);
	return true;
}
// Button
bool CUI_ID_FRAME_ChangeCountry::ID_BUTTON_RandOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ChangeCountry)
		return false;

	s_CUI_ID_FRAME_MainMenu.SetVisable(true);
	s_CUI_ID_FRAME_MAIN.SetVisable(true);

	//TODO:�ı�MsgCountryChangeReq�еı���ΪCHAR�����ѡ��11��ֵ���������������ѡ��һ������
	MsgCountryChangeReq msg;	
	msg.uchCountryID = RandCountry; 
	if (msg.uchCountryID == 0)
	{
		LOG_MESSAGE(INFO_LOG,LOG_PRIORITY_INFO,"zhuxincong2�ͻ����������IDΪ%d",msg.uchCountryID);
	}
	GettheNetworkInput().SendMsg(&msg);
	Refresh();
	return true;
}

// װ��UI
bool CUI_ID_FRAME_ChangeCountry::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ChangeCountry.MEUI" , true, UI_Render_LayerThree); //���������� UI_Render_LayerThree ��˼�ǰѵ�����UI ������ǰ��
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("��ȡ�ļ�[Data\\UI\\ChangeCountry.MEUI]ʧ��")
			return false;
	}
	return DoControlConnect();
}
// �����ؼ�
bool CUI_ID_FRAME_ChangeCountry::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_ChangeCountry, s_CUI_ID_FRAME_ChangeCountryOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ChangeCountry, s_CUI_ID_FRAME_ChangeCountryOnFrameRender );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ChangeCountry, ID_CHECKBOX_ShuGuo, s_CUI_ID_FRAME_ChangeCountryID_CHECKBOX_ShuGuoOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ChangeCountry, ID_CHECKBOX_WeiGuo, s_CUI_ID_FRAME_ChangeCountryID_CHECKBOX_WeiGuoOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ChangeCountry, ID_CHECKBOX_WuGuo, s_CUI_ID_FRAME_ChangeCountryID_CHECKBOX_WuGuoOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_ChangeCountry, ID_BUTTON_Join, s_CUI_ID_FRAME_ChangeCountryID_BUTTON_JoinOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ChangeCountry, ID_BUTTON_Exit, s_CUI_ID_FRAME_ChangeCountryID_BUTTON_ExitOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ChangeCountry, ID_BUTTON_Rand, s_CUI_ID_FRAME_ChangeCountryID_BUTTON_RandOnButtonClick );

	m_pID_FRAME_ChangeCountry = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ChangeCountry );
	m_pID_CHECKBOX_ShuGuo = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ChangeCountry, ID_CHECKBOX_ShuGuo );
	m_pID_CHECKBOX_WeiGuo = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ChangeCountry, ID_CHECKBOX_WeiGuo );
	m_pID_CHECKBOX_WuGuo = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ChangeCountry, ID_CHECKBOX_WuGuo );
	m_pID_BUTTON_Join = (ControlButton*)theUiManager.FindControl( ID_FRAME_ChangeCountry, ID_BUTTON_Join );
	m_pID_BUTTON_Exit = (ControlButton*)theUiManager.FindControl( ID_FRAME_ChangeCountry, ID_BUTTON_Exit );
	m_pID_BUTTON_Rand = (ControlButton*)theUiManager.FindControl( ID_FRAME_ChangeCountry, ID_BUTTON_Rand );
	assert( m_pID_FRAME_ChangeCountry );
	assert( m_pID_CHECKBOX_ShuGuo );
	assert( m_pID_CHECKBOX_WeiGuo );
	assert( m_pID_CHECKBOX_WuGuo );
	assert( m_pID_BUTTON_Join );
	assert( m_pID_BUTTON_Exit );
	assert( m_pID_BUTTON_Rand );

	s_CUI_ID_FRAME_ChangeCountry.SetVisable(false);

	return true;
}
// ж��UI
bool CUI_ID_FRAME_ChangeCountry::_UnLoadUI()
{
	m_pID_FRAME_ChangeCountry = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\ChangeCountry.MEUI" );
}
// �Ƿ����
bool CUI_ID_FRAME_ChangeCountry::_IsVisable()
{
	if(!m_pID_FRAME_ChangeCountry)
		return false;
	return m_pID_FRAME_ChangeCountry->IsVisable();
}
// �����Ƿ����
void CUI_ID_FRAME_ChangeCountry::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_ChangeCountry)
		return;
	m_pID_FRAME_ChangeCountry->SetVisable( bVisable );
    g_RenderTips = !bVisable;
	if (bVisable)
	{
		m_pID_CHECKBOX_ShuGuo->SetCheck(false);
		m_pID_CHECKBOX_WeiGuo->SetCheck(false);
		m_pID_CHECKBOX_WuGuo->SetCheck(false);

		//todo:������Ҳ���0������Ĺ��Ҳ���ʾ��ѡ
		//������Ҳ���0����û�����ѡ��
		
		if (CountryDefine::Country_Init != thePlayerRole.GetCountry())
		{
			m_pID_BUTTON_Rand->SetVisable(false);

			switch (thePlayerRole.GetCountry())
			{
			case CountryDefine::Country_LouLan:
				m_pID_CHECKBOX_ShuGuo->SetEnable(true);
				break;

			case CountryDefine::Country_KunLun:
				m_pID_CHECKBOX_WeiGuo->SetEnable(true);
				break;

			case CountryDefine::Country_DunHuang:
				m_pID_CHECKBOX_WuGuo->SetEnable(true);
				break;
			}
					
		}
	}
}

int CUI_ID_FRAME_ChangeCountry::GetCountryId()
{
	if (check_WeiGuo)
	{
		return CountryDefine::Country_LouLan;
	}
	if (check_ShuGuo)
	{
		return CountryDefine::Country_KunLun;
	}
	if (check_WuGuo)
	{
		return CountryDefine::Country_DunHuang;
	}
	return CountryDefine::Country_Init;
}


void CUI_ID_FRAME_ChangeCountry::Refresh()
{
	if( !m_pID_FRAME_ChangeCountry)
	{
		return ;
	}

	m_pID_CHECKBOX_ShuGuo->SetCheck(false);
	m_pID_CHECKBOX_WeiGuo->SetCheck(false);
	m_pID_CHECKBOX_WuGuo->SetCheck(false);

	if ( 0 != thePlayerRole.GetCountry())
	{
		m_pID_BUTTON_Rand->SetVisable(false);

		switch (thePlayerRole.GetCountry())
		{
		case CountryDefine::Country_LouLan:
			m_pID_CHECKBOX_ShuGuo->SetEnable(true);
			break;

		case CountryDefine::Country_KunLun:
			m_pID_CHECKBOX_WeiGuo->SetEnable(true);
			break;

		case CountryDefine::Country_DunHuang:
			m_pID_CHECKBOX_WuGuo->SetEnable(true);
			break;
		}

	}
	
	m_pID_FRAME_ChangeCountry->SetVisable(false);
	g_RenderTips = true;
}

void CUI_ID_FRAME_ChangeCountry::InitializeAtEnterWorld()
{
	/*if( !m_pID_FRAME_ChangeCountry )
		return;*/
	//theChangeCountryConfig.LoadConfigFile();
	//s_CUI_ID_FRAME_ChangeCountry.SetVisable( false );	
}