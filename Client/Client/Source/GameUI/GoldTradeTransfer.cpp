/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\chixin.ni\桌面\金锭UI\GoldTradeTransfer.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GoldTradeTransfer.h"
#include "Player.h"
#include "NetworkInput.h"
#include "PlayerRole.h"
#include "ConsignmentDefine.h"
#include "ConsignmentMessage.h"

CUI_ID_FRAME_GoldTradeDeposit s_CUI_ID_FRAME_GoldTradeDeposit;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GoldTradeDeposit, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GoldTradeDeposit, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTradeDeposit, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTradeDeposit, ID_BUTTON_MaxGoldOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_GoldTradeDeposit, ID_EDIT_JinOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_GoldTradeDeposit, ID_EDIT_YinOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_GoldTradeDeposit, ID_EDIT_TongOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTradeDeposit, ID_BUTTON_MaxMoneyOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_GoldTradeDeposit, ID_EDIT_GoldOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTradeDeposit, ID_BUTTON_CancleOnButtonClick )
CUI_ID_FRAME_GoldTradeDeposit::CUI_ID_FRAME_GoldTradeDeposit()
{
	// Member
	m_pID_FRAME_GoldTradeDeposit = NULL;
	m_pID_TEXT_DepositMoney = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_MaxGold = NULL;
	m_pID_TEXT_DepositGold = NULL;
	m_pID_PICTURE_Jin = NULL;
	m_pID_PICTURE_Ying = NULL;
	m_pID_PICTURE_Tong = NULL;
	m_pID_EDIT_Jin = NULL;
	m_pID_EDIT_Yin = NULL;
	m_pID_EDIT_Tong = NULL;
	m_pID_BUTTON_MaxMoney = NULL;
	m_pID_EDIT_Gold = NULL;
	m_pID_PICTURE_Gold = NULL;
	m_pID_BUTTON_Cancle = NULL;
	m_pID_TEXT_ReceiveGold = NULL;
	m_pID_TEXT_ReceiveMoney = NULL;
	m_pID_PICTURE_DepositGold = NULL;
	m_pID_PICTURE_ReceiveGold = NULL;
	m_pID_PICTURE_DepositMoney = NULL;
	m_pID_PICTURE_ReceiveMoney = NULL;
	m_IsPop = true;
}
// Frame
bool CUI_ID_FRAME_GoldTradeDeposit::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_GoldTradeDeposit::OnFrameRender()
{
	if(m_bCloseUi)
	{
		ID_BUTTON_OKOnButtonClick( NULL );
		m_bCloseUi = false;
	}
	return true;
}
// Button
bool CUI_ID_FRAME_GoldTradeDeposit::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_GoldTradeDeposit)
		return false;
	int rmbmoney = atoi(m_pID_EDIT_Gold->GetText());
	int gold = atoi(m_pID_EDIT_Jin->GetText());
	int silver = atoi(m_pID_EDIT_Yin->GetText());
	int copper = atoi(m_pID_EDIT_Tong->GetText());
	DWORD money = thePlayerRole.GetMoneyFromGSC(gold, silver, copper);
	if(rmbmoney>0||money>0)
	{
		MsgOperateMoneyReq msg;
		msg.nRMBMoney = rmbmoney;
		msg.nGameMoney = money;

		if(m_IsPop)
		{
			msg.uchOperate = ConsignmentDefine::Operate_TakeOut;
		}
		else
		{
			msg.uchOperate = ConsignmentDefine::Operate_Save;
		}
		GettheNetworkInput().SendMsg( &msg );
	}

	SetVisable(false);

	return true;
}
// Button
bool CUI_ID_FRAME_GoldTradeDeposit::ID_BUTTON_MaxGoldOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_GoldTradeDeposit)
		return false;
	if(m_IsPop)
	{
		int gold = thePlayerRole.GetData(CPlayerRole::TYPE_TradeJinDing);

		if(m_pID_EDIT_Gold)
			m_pID_EDIT_Gold->SetText(gold);
	}
	else
	{
		int gold = thePlayerRole.GetData(/*CPlayerRole::TYPE_JinDing*/ CPlayerRole::TYPE_JinPiao );
		if (gold > ConsignmentDefine::MaxAccountRMB)
		{
			gold = ConsignmentDefine::MaxAccountRMB;
		}

		if(m_pID_EDIT_Gold)
			m_pID_EDIT_Gold->SetText(gold);
	}

	return true;
}
// Edit
void CUI_ID_FRAME_GoldTradeDeposit::ID_EDIT_JinOnEditEnter( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_GoldTradeDeposit)
		return;
	m_pID_EDIT_Jin->SetText(atoi(m_pID_EDIT_Jin->GetText()));
}
// Edit
void CUI_ID_FRAME_GoldTradeDeposit::ID_EDIT_YinOnEditEnter( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_GoldTradeDeposit)
		return;
	m_pID_EDIT_Yin->SetText(atoi(m_pID_EDIT_Yin->GetText()));
}
// Edit
void CUI_ID_FRAME_GoldTradeDeposit::ID_EDIT_TongOnEditEnter( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_GoldTradeDeposit)
		return;
	m_pID_EDIT_Tong->SetText(atoi(m_pID_EDIT_Tong->GetText()));
}
// Button
bool CUI_ID_FRAME_GoldTradeDeposit::ID_BUTTON_MaxMoneyOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_GoldTradeDeposit)
		return false;
	if(m_IsPop)
	{
		int money = thePlayerRole.GetData(CPlayerRole::TYPE_TradeMoney);

		int gold = 0, silver = 0, copper = 0;
		thePlayerRole.GetGSCFromMoney(money, gold, silver, copper);

		if(m_pID_EDIT_Jin)
			m_pID_EDIT_Jin->SetText(gold);
		if(m_pID_EDIT_Yin)
			m_pID_EDIT_Yin->SetText(silver);
		if(m_pID_EDIT_Tong)
			m_pID_EDIT_Tong->SetText(copper);
	}
	else
	{
		int money = thePlayerRole.GetData(CPlayerRole::TYPE_MONEY);
		if (money > ConsignmentDefine::MaxAccountGameMoney)
		{
			money = ConsignmentDefine::MaxAccountGameMoney;
		}

		int gold = 0, silver = 0, copper = 0;
		thePlayerRole.GetGSCFromMoney(money, gold, silver, copper);

		if(m_pID_EDIT_Jin)
			m_pID_EDIT_Jin->SetText(gold);
		if(m_pID_EDIT_Yin)
			m_pID_EDIT_Yin->SetText(silver);
		if(m_pID_EDIT_Tong)
			m_pID_EDIT_Tong->SetText(copper);
	}
	return true;
}
// Edit
void CUI_ID_FRAME_GoldTradeDeposit::ID_EDIT_GoldOnEditEnter( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_GoldTradeDeposit)
		return;
	m_pID_EDIT_Gold->SetText(atoi(m_pID_EDIT_Gold->GetText()));
}
// Button
bool CUI_ID_FRAME_GoldTradeDeposit::ID_BUTTON_CancleOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_GoldTradeDeposit)
		return false;
	SetVisable(false);

	return true;
}

// 装载UI
bool CUI_ID_FRAME_GoldTradeDeposit::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GoldTradeTransfer.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GoldTradeTransfer.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GoldTradeDeposit::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GoldTradeDeposit, s_CUI_ID_FRAME_GoldTradeDepositOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GoldTradeDeposit, s_CUI_ID_FRAME_GoldTradeDepositOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_GoldTradeDeposit, ID_BUTTON_OK, s_CUI_ID_FRAME_GoldTradeDepositID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GoldTradeDeposit, ID_BUTTON_MaxGold, s_CUI_ID_FRAME_GoldTradeDepositID_BUTTON_MaxGoldOnButtonClick );
	theUiManager.OnEditEnter( ID_FRAME_GoldTradeDeposit, ID_EDIT_Jin, s_CUI_ID_FRAME_GoldTradeDepositID_EDIT_JinOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_GoldTradeDeposit, ID_EDIT_Yin, s_CUI_ID_FRAME_GoldTradeDepositID_EDIT_YinOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_GoldTradeDeposit, ID_EDIT_Tong, s_CUI_ID_FRAME_GoldTradeDepositID_EDIT_TongOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_GoldTradeDeposit, ID_BUTTON_MaxMoney, s_CUI_ID_FRAME_GoldTradeDepositID_BUTTON_MaxMoneyOnButtonClick );
	theUiManager.OnEditEnter( ID_FRAME_GoldTradeDeposit, ID_EDIT_Gold, s_CUI_ID_FRAME_GoldTradeDepositID_EDIT_GoldOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_GoldTradeDeposit, ID_BUTTON_Cancle, s_CUI_ID_FRAME_GoldTradeDepositID_BUTTON_CancleOnButtonClick );

	m_pID_FRAME_GoldTradeDeposit = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GoldTradeDeposit );
	m_pID_TEXT_DepositMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTradeDeposit, ID_TEXT_DepositMoney );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTradeDeposit, ID_BUTTON_OK );
	m_pID_BUTTON_MaxGold = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTradeDeposit, ID_BUTTON_MaxGold );
	m_pID_TEXT_DepositGold = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTradeDeposit, ID_TEXT_DepositGold );
	m_pID_PICTURE_Jin = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTradeDeposit, ID_PICTURE_Jin );
	m_pID_PICTURE_Ying = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTradeDeposit, ID_PICTURE_Ying );
	m_pID_PICTURE_Tong = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTradeDeposit, ID_PICTURE_Tong );
	m_pID_EDIT_Jin = (ControlEdit*)theUiManager.FindControl( ID_FRAME_GoldTradeDeposit, ID_EDIT_Jin );
	m_pID_EDIT_Yin = (ControlEdit*)theUiManager.FindControl( ID_FRAME_GoldTradeDeposit, ID_EDIT_Yin );
	m_pID_EDIT_Tong = (ControlEdit*)theUiManager.FindControl( ID_FRAME_GoldTradeDeposit, ID_EDIT_Tong );
	m_pID_BUTTON_MaxMoney = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTradeDeposit, ID_BUTTON_MaxMoney );
	m_pID_EDIT_Gold = (ControlEdit*)theUiManager.FindControl( ID_FRAME_GoldTradeDeposit, ID_EDIT_Gold );
	m_pID_PICTURE_Gold = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTradeDeposit, ID_PICTURE_Gold );
	m_pID_BUTTON_Cancle = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTradeDeposit, ID_BUTTON_Cancle );
	m_pID_TEXT_ReceiveGold = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTradeDeposit, ID_TEXT_ReceiveGold );
	m_pID_TEXT_ReceiveMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTradeDeposit, ID_TEXT_ReceiveMoney );
	m_pID_PICTURE_DepositGold = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTradeDeposit, ID_PICTURE_DepositGold );
	m_pID_PICTURE_ReceiveGold = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTradeDeposit, ID_PICTURE_ReceiveGold );
	m_pID_PICTURE_DepositMoney = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTradeDeposit, ID_PICTURE_DepositMoney );
	m_pID_PICTURE_ReceiveMoney = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTradeDeposit, ID_PICTURE_ReceiveMoney );
	
	assert( m_pID_PICTURE_DepositGold );
	assert( m_pID_PICTURE_ReceiveGold );
	assert( m_pID_PICTURE_DepositMoney );
	assert( m_pID_PICTURE_ReceiveMoney );
	assert( m_pID_FRAME_GoldTradeDeposit );
	assert( m_pID_TEXT_DepositMoney );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_MaxGold );
	assert( m_pID_TEXT_DepositGold );
	assert( m_pID_PICTURE_Jin );
	assert( m_pID_PICTURE_Ying );
	assert( m_pID_PICTURE_Tong );
	assert( m_pID_EDIT_Jin );
	assert( m_pID_EDIT_Yin );
	assert( m_pID_EDIT_Tong );
	assert( m_pID_BUTTON_MaxMoney );
	assert( m_pID_EDIT_Gold );
	assert( m_pID_PICTURE_Gold );
	assert( m_pID_BUTTON_Cancle );
	assert( m_pID_TEXT_ReceiveGold );
	assert( m_pID_TEXT_ReceiveMoney );

	SetVisable(false);


	m_pID_EDIT_Gold->SetMaxLength(5);
	m_pID_EDIT_Jin->SetMaxLength(5);
	m_pID_EDIT_Yin->SetMaxLength(2);
	m_pID_EDIT_Tong->SetMaxLength(2);

	m_pID_FRAME_GoldTradeDeposit->SetMsgProcFun( frame_msg );

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GoldTradeDeposit::_UnLoadUI()
{
	m_pID_FRAME_GoldTradeDeposit = NULL;
	m_pID_TEXT_DepositMoney = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_MaxGold = NULL;
	m_pID_TEXT_DepositGold = NULL;
	m_pID_PICTURE_Jin = NULL;
	m_pID_PICTURE_Ying = NULL;
	m_pID_PICTURE_Tong = NULL;
	m_pID_EDIT_Jin = NULL;
	m_pID_EDIT_Yin = NULL;
	m_pID_EDIT_Tong = NULL;
	m_pID_BUTTON_MaxMoney = NULL;
	m_pID_EDIT_Gold = NULL;
	m_pID_PICTURE_Gold = NULL;
	m_pID_BUTTON_Cancle = NULL;
	m_pID_TEXT_ReceiveGold = NULL;
	m_pID_TEXT_ReceiveMoney = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GoldTradeTransfer.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GoldTradeDeposit::_IsVisable()
{
	if(m_pID_FRAME_GoldTradeDeposit)
		return m_pID_FRAME_GoldTradeDeposit->IsVisable();

	return false;
}
// 设置是否可视
void CUI_ID_FRAME_GoldTradeDeposit::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_GoldTradeDeposit)
		return;
	
	m_pID_FRAME_GoldTradeDeposit->SetVisable( bVisable );
	m_bCloseUi = false;
	if (m_IsPop)
	{
		if(m_pID_TEXT_DepositGold)
			m_pID_TEXT_DepositGold->SetVisable(false);
		if(m_pID_TEXT_DepositMoney)
			m_pID_TEXT_DepositMoney->SetVisable(false);
		if(m_pID_TEXT_ReceiveGold)
			m_pID_TEXT_ReceiveGold->SetVisable(true);
		if(m_pID_TEXT_ReceiveMoney)
			m_pID_TEXT_ReceiveMoney->SetVisable(true);
		m_pID_PICTURE_DepositGold->SetVisable(false);
		m_pID_PICTURE_DepositMoney->SetVisable(false);
		m_pID_PICTURE_ReceiveGold->SetVisable(true);
		m_pID_PICTURE_ReceiveMoney->SetVisable(true);
	}
	else
	{
		if(m_pID_TEXT_DepositGold)
			m_pID_TEXT_DepositGold->SetVisable(true);
		if(m_pID_TEXT_DepositMoney)
			m_pID_TEXT_DepositMoney->SetVisable(true);
		if(m_pID_TEXT_ReceiveGold)
			m_pID_TEXT_ReceiveGold->SetVisable(false);
		if(m_pID_TEXT_ReceiveMoney)
			m_pID_TEXT_ReceiveMoney->SetVisable(false);
		m_pID_PICTURE_DepositGold->SetVisable(true);
		m_pID_PICTURE_DepositMoney->SetVisable(true);
		m_pID_PICTURE_ReceiveGold->SetVisable(false);
		m_pID_PICTURE_ReceiveMoney->SetVisable(false);
	}
	Refresh();
}

void CUI_ID_FRAME_GoldTradeDeposit::SetPop()
{
	//if (!IsUILoad())
	//{
	//	_LoadUI();
	//}
	//if( !m_pID_FRAME_GoldTradeDeposit )
	//	return;

	m_IsPop = true;
}

void CUI_ID_FRAME_GoldTradeDeposit::SetPush()
{
	//if (!IsUILoad())
	//{
	//	_LoadUI();
	//}
	//if( !m_pID_FRAME_GoldTradeDeposit )
	//	return;

	m_IsPop = false;
}

void CUI_ID_FRAME_GoldTradeDeposit::Refresh()
{
	if(m_pID_EDIT_Gold)
	{
		m_pID_EDIT_Gold->SetText(0);
	}
	if(m_pID_EDIT_Jin)
	{
		m_pID_EDIT_Jin->SetText(0);
	}
	if(m_pID_EDIT_Yin)
	{
		m_pID_EDIT_Yin->SetText(0);
	}
	if(m_pID_EDIT_Tong)
	{
		m_pID_EDIT_Tong->SetText(0);
	}
}

bool CUI_ID_FRAME_GoldTradeDeposit::frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	if(!s_CUI_ID_FRAME_GoldTradeDeposit.IsVisable())
		return false;

	if(bMsgUsed == true)
		return false;

	if(msg == WM_KEYDOWN && wParam == VK_RETURN)
	{
		s_CUI_ID_FRAME_GoldTradeDeposit.SetCloseUi(true);
		return true;
	}

	if(theUiManager.GetFocus() == s_CUI_ID_FRAME_GoldTradeDeposit.m_pID_EDIT_Gold)
	{
		s_CUI_ID_FRAME_GoldTradeDeposit.ID_EDIT_GoldOnEditEnter(NULL, NULL);
	}
	if(theUiManager.GetFocus() == s_CUI_ID_FRAME_GoldTradeDeposit.m_pID_EDIT_Jin)
	{
		s_CUI_ID_FRAME_GoldTradeDeposit.ID_EDIT_JinOnEditEnter(NULL, NULL);
	}
	if(theUiManager.GetFocus() == s_CUI_ID_FRAME_GoldTradeDeposit.m_pID_EDIT_Yin)
	{
		s_CUI_ID_FRAME_GoldTradeDeposit.ID_EDIT_YinOnEditEnter(NULL, NULL);
	}
	if(theUiManager.GetFocus() == s_CUI_ID_FRAME_GoldTradeDeposit.m_pID_EDIT_Tong)
	{
		s_CUI_ID_FRAME_GoldTradeDeposit.ID_EDIT_TongOnEditEnter(NULL, NULL);
	}

	return false;

}

void CUI_ID_FRAME_GoldTradeDeposit::SetCloseUi(bool bValue)
{
	m_bCloseUi = bValue;
}
