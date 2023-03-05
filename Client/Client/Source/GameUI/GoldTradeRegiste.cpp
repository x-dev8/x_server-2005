/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\chixin.ni\桌面\金锭UI\GoldTradeRegiste.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GoldTradeRegiste.h"
#include "MessageDefine.h"
#include "NetworkInput.h"
#include "MessageBox.h"
#include "XmlStringLanguage.h"
#include "ScreenInfoManager.h"
#include "color_config.h"
#include "GoldTrade.h"
#include "PlayerRole.h"
#include "Common.h"

bool CancelTrade( const char bPressYesButton, void *pData )
{
	if(bPressYesButton && pData)
	{
		MsgConsignmentOperateReq msg;
		::CopyMemory(&msg,pData,sizeof(MsgConsignmentOperateReq));
		GettheNetworkInput().SendMsg( &msg );
	}
	return true;
}

CUI_ID_FRAME_GoldTradeRegiste s_CUI_ID_FRAME_GoldTradeRegiste;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GoldTradeRegiste, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GoldTradeRegiste, OnFrameRender )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GoldTradeRegiste, ID_LIST_SellOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTradeRegiste, ID_BUTTON_helpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTradeRegiste, ID_BUTTON_CLOSEOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GoldTradeRegiste, ID_LIST_TypeOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GoldTradeRegiste, ID_LIST_GoldOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GoldTradeRegiste, ID_LIST_UnitPriceOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTradeRegiste, ID_BUTTON_CloseOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTradeRegiste, ID_BUTTON_CancleOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GoldTradeRegiste, ID_LIST_FinishTimeOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GoldTradeRegiste, ID_LIST_PriceOnListSelectChange )
CUI_ID_FRAME_GoldTradeRegiste::CUI_ID_FRAME_GoldTradeRegiste()
{
	// Member
	ResetMembers();
}

void CUI_ID_FRAME_GoldTradeRegiste::ResetMembers()
{
	m_pID_FRAME_GoldTradeRegiste = NULL;
	m_pID_PICTURE_Entrust = NULL;
	m_pID_PICTURE_Wall = NULL;
	m_pID_LIST_Sell = NULL;
	m_pID_PICTURE_TitleMiddle = NULL;
	m_pID_PICTURE_Title = NULL;
	m_pID_TEXT_Price = NULL;
	m_pID_TEXT_Gold = NULL;
	m_pID_PICTURE_TitleLeft = NULL;
	m_pID_PICTURE_TitleRight = NULL;
	m_pID_PICTURE_TitleL = NULL;
	m_pID_PICTURE_TltleR = NULL;
	m_pID_BUTTON_help = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_LIST_Type = NULL;
	m_pID_TEXT_Type = NULL;
	m_pID_LIST_Gold = NULL;
	m_pID_TEXT_UnitPrice = NULL;
	m_pID_LIST_UnitPrice = NULL;
	m_pID_BUTTON_Close = NULL;
	m_pID_BUTTON_Cancle = NULL;
	m_pID_TEXT_FinishTime = NULL;
	m_pID_LIST_FinishTime = NULL;
	m_pID_LIST_Price = NULL;

}
// Frame
bool CUI_ID_FRAME_GoldTradeRegiste::OnFrameRun()
{
	if( IsVisable() )
	{
		int nStartIndex = m_pID_LIST_Sell->GetShowStartHeight();

		m_pID_LIST_Price->SetShowStartHeight(nStartIndex);
		m_pID_LIST_Type->SetShowStartHeight(nStartIndex);
		m_pID_LIST_Gold->SetShowStartHeight(nStartIndex);
		m_pID_LIST_UnitPrice->SetShowStartHeight(nStartIndex);
		m_pID_LIST_FinishTime->SetShowStartHeight(nStartIndex);

		int sel = m_pID_LIST_Sell->GetCurSelIndex();
		if(sel!=-1&&sel<m_vecHistory.size())
		{
			if(m_vecHistory[sel].GetStatus() != ConsignmentDefine::Status_Running)
			{
				m_pID_BUTTON_Cancle->SetEnable(false);
			}
			else
			{
				m_pID_BUTTON_Cancle->SetEnable(true);
			}
		}
		else
		{
			m_pID_BUTTON_Cancle->SetEnable(false);
		}
	}

	return true;
}
bool CUI_ID_FRAME_GoldTradeRegiste::OnFrameRender()
{
	return true;
}
// List
void CUI_ID_FRAME_GoldTradeRegiste::ID_LIST_SellOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(!m_pID_FRAME_GoldTradeRegiste)
		return;
}
// Button
bool CUI_ID_FRAME_GoldTradeRegiste::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_GoldTradeRegiste)
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_GoldTradeRegiste::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_GoldTradeRegiste)
		return false;
	return true;
}
// List
void CUI_ID_FRAME_GoldTradeRegiste::ID_LIST_TypeOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(!m_pID_FRAME_GoldTradeRegiste)
		return;
}
// List
void CUI_ID_FRAME_GoldTradeRegiste::ID_LIST_GoldOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(!m_pID_FRAME_GoldTradeRegiste)
		return;
}
// List
void CUI_ID_FRAME_GoldTradeRegiste::ID_LIST_UnitPriceOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(!m_pID_FRAME_GoldTradeRegiste)
		return;
}
// Button
bool CUI_ID_FRAME_GoldTradeRegiste::ID_BUTTON_CloseOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_GoldTradeRegiste)
		return false;
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_GoldTradeRegiste::ID_BUTTON_CancleOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_GoldTradeRegiste)
		return false;
	int sel = m_pID_LIST_Sell->GetCurSelIndex();
	if(sel!=-1&&sel<m_vecHistory.size())
	{
		if(m_vecHistory[sel].GetStatus() == ConsignmentDefine::Status_Running)
		{
			MsgConsignmentOperateReq msg;
			msg.uchOperate = ConsignmentDefine::Operate_Cancel;
			msg.n64ConsignmentID = m_vecHistory[sel].GetID();
			msg.uchConsignmentType = m_vecHistory[sel].GetType();
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_GoldTrade_Cancel), theXmlString.GetString(eClient_AddInfo_2slk_16),
				CUI_ID_FRAME_MessageBox::eTypeYesNo,false,CancelTrade,&msg,sizeof(MsgConsignmentOperateReq));
		}
		else
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_FailedReason, theXmlString.GetString(eText_SystemAuctionError_CannotBuySelfItem) );
		}
	}

	return true;
}
// List
void CUI_ID_FRAME_GoldTradeRegiste::ID_LIST_PriceOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(!m_pID_FRAME_GoldTradeRegiste)
		return;
}
// List
void CUI_ID_FRAME_GoldTradeRegiste::ID_LIST_FinishTimeOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(!m_pID_FRAME_GoldTradeRegiste)
		return;
}

// 装载UI
bool CUI_ID_FRAME_GoldTradeRegiste::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GoldTradeRegiste.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GoldTradeRegiste.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GoldTradeRegiste::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GoldTradeRegiste, s_CUI_ID_FRAME_GoldTradeRegisteOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GoldTradeRegiste, s_CUI_ID_FRAME_GoldTradeRegisteOnFrameRender );
	theUiManager.OnListSelectChange( ID_FRAME_GoldTradeRegiste, ID_LIST_Sell, s_CUI_ID_FRAME_GoldTradeRegisteID_LIST_SellOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_GoldTradeRegiste, ID_BUTTON_help, s_CUI_ID_FRAME_GoldTradeRegisteID_BUTTON_helpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GoldTradeRegiste, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_GoldTradeRegisteID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_GoldTradeRegiste, ID_LIST_Type, s_CUI_ID_FRAME_GoldTradeRegisteID_LIST_TypeOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GoldTradeRegiste, ID_LIST_Gold, s_CUI_ID_FRAME_GoldTradeRegisteID_LIST_GoldOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GoldTradeRegiste, ID_LIST_UnitPrice, s_CUI_ID_FRAME_GoldTradeRegisteID_LIST_UnitPriceOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_GoldTradeRegiste, ID_BUTTON_Close, s_CUI_ID_FRAME_GoldTradeRegisteID_BUTTON_CloseOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GoldTradeRegiste, ID_BUTTON_Cancle, s_CUI_ID_FRAME_GoldTradeRegisteID_BUTTON_CancleOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_GoldTradeRegiste, ID_LIST_FinishTime, s_CUI_ID_FRAME_GoldTradeRegisteID_LIST_FinishTimeOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GoldTradeRegiste, ID_LIST_Price, s_CUI_ID_FRAME_GoldTradeRegisteID_LIST_PriceOnListSelectChange );

	m_pID_FRAME_GoldTradeRegiste = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GoldTradeRegiste );
	m_pID_PICTURE_Entrust = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTradeRegiste, ID_PICTURE_Entrust );
	m_pID_PICTURE_Wall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTradeRegiste, ID_PICTURE_Wall );
	m_pID_LIST_Sell = (ControlList*)theUiManager.FindControl( ID_FRAME_GoldTradeRegiste, ID_LIST_Sell );
	m_pID_PICTURE_TitleMiddle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTradeRegiste, ID_PICTURE_TitleMiddle );
	m_pID_PICTURE_Title = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTradeRegiste, ID_PICTURE_Title );
	m_pID_TEXT_Price = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTradeRegiste, ID_TEXT_Price );
	m_pID_TEXT_Gold = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTradeRegiste, ID_TEXT_Gold );
	m_pID_PICTURE_TitleLeft = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTradeRegiste, ID_PICTURE_TitleLeft );
	m_pID_PICTURE_TitleRight = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTradeRegiste, ID_PICTURE_TitleRight );
	m_pID_PICTURE_TitleL = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTradeRegiste, ID_PICTURE_TitleL );
	m_pID_PICTURE_TltleR = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTradeRegiste, ID_PICTURE_TltleR );
	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTradeRegiste, ID_BUTTON_help );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTradeRegiste, ID_BUTTON_CLOSE );
	m_pID_LIST_Type = (ControlList*)theUiManager.FindControl( ID_FRAME_GoldTradeRegiste, ID_LIST_Type );
	m_pID_TEXT_Type = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTradeRegiste, ID_TEXT_Type );
	m_pID_LIST_Gold = (ControlList*)theUiManager.FindControl( ID_FRAME_GoldTradeRegiste, ID_LIST_Gold );
	m_pID_TEXT_UnitPrice = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTradeRegiste, ID_TEXT_UnitPrice );
	m_pID_LIST_UnitPrice = (ControlList*)theUiManager.FindControl( ID_FRAME_GoldTradeRegiste, ID_LIST_UnitPrice );
	m_pID_BUTTON_Close = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTradeRegiste, ID_BUTTON_Close );
	m_pID_BUTTON_Cancle = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTradeRegiste, ID_BUTTON_Cancle );
	m_pID_TEXT_FinishTime = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTradeRegiste, ID_TEXT_FinishTime );
	m_pID_LIST_FinishTime = (ControlList*)theUiManager.FindControl( ID_FRAME_GoldTradeRegiste, ID_LIST_FinishTime );
	m_pID_LIST_Price = (ControlList*)theUiManager.FindControl( ID_FRAME_GoldTradeRegiste, ID_LIST_Price );
	assert( m_pID_FRAME_GoldTradeRegiste );
	assert( m_pID_PICTURE_Entrust );
	assert( m_pID_PICTURE_Wall );
	assert( m_pID_LIST_Sell );
	assert( m_pID_PICTURE_TitleMiddle );
	assert( m_pID_PICTURE_Title );
	assert( m_pID_TEXT_Price );
	assert( m_pID_TEXT_Gold );
	assert( m_pID_PICTURE_TitleLeft );
	assert( m_pID_PICTURE_TitleRight );
	assert( m_pID_PICTURE_TitleL );
	assert( m_pID_PICTURE_TltleR );
	assert( m_pID_BUTTON_help );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_LIST_Type );
	assert( m_pID_TEXT_Type );
	assert( m_pID_LIST_Gold );
	assert( m_pID_TEXT_UnitPrice );
	assert( m_pID_LIST_UnitPrice );
	assert( m_pID_BUTTON_Close );
	assert( m_pID_BUTTON_Cancle );
	assert( m_pID_TEXT_FinishTime );
	assert( m_pID_LIST_FinishTime );
	assert( m_pID_LIST_Price );
		
	SetVisable(false);

	m_pID_LIST_Sell->SetCurSelIndex(-1);

	m_pID_LIST_Price->HaveSelBar(false);
	m_pID_LIST_Type->HaveSelBar(false);
	m_pID_LIST_Gold->HaveSelBar(false);
	m_pID_LIST_UnitPrice->HaveSelBar(false);
	m_pID_LIST_FinishTime->HaveSelBar(false);

	m_pID_LIST_Price->SetDrawFlags(DT_CENTER|DT_NOCLIP);
	m_pID_LIST_Type->SetDrawFlags(DT_CENTER|DT_NOCLIP);
	m_pID_LIST_Gold->SetDrawFlags(DT_CENTER|DT_NOCLIP);
	m_pID_LIST_UnitPrice->SetDrawFlags(DT_CENTER|DT_NOCLIP);
	m_pID_LIST_FinishTime->SetDrawFlags(DT_CENTER|DT_NOCLIP);

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GoldTradeRegiste::_UnLoadUI()
{
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\GoldTradeRegiste.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GoldTradeRegiste::_IsVisable()
{
	if(m_pID_FRAME_GoldTradeRegiste)
		return m_pID_FRAME_GoldTradeRegiste->IsVisable();

	return false;
}
// 设置是否可视
void CUI_ID_FRAME_GoldTradeRegiste::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_GoldTradeRegiste)
		return;
	m_pID_FRAME_GoldTradeRegiste->SetVisable( bVisable );
}

void CUI_ID_FRAME_GoldTradeRegiste::Refresh()
{
	if(!m_pID_FRAME_GoldTradeRegiste)
		return;
	m_pID_LIST_Sell->SetCurSelIndex(-1);

	m_pID_LIST_Price->Clear();
	m_pID_LIST_Sell->Clear();
	m_pID_LIST_Type->Clear();
	m_pID_LIST_Gold->Clear();
	m_pID_LIST_UnitPrice->Clear();
	m_pID_LIST_FinishTime->Clear();
	
	char buf[128] = {0};
	ControlList::S_List	stItem;

	for(int i=0;i<m_vecHistory.size();++i)
	{
		DWORD allprice = m_vecHistory[i].GetPrice() * m_vecHistory[i].GetCount();
		int gold = 0, silver = 0, copper = 0;
		thePlayerRole.GetGSCFromMoney(allprice, gold, silver, copper);

		stItem.SetData( "" );
		m_pID_LIST_Sell->AddItem(&stItem,NULL,false);

		if (gold > 0)
		{
			if (silver > 0)
			{
				if (copper > 0)
				{
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#81}%d{#82}%d{#83}",gold,silver,copper);
				}
				else
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#81}%d{#82}",gold,silver);
			}
			else
			{
				if (copper > 0)
				{
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#81}%d{#83}",gold,copper);
				}
				else
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#81}",gold);
			}
		}
		else
		{
			if (silver > 0)
			{
				if (copper > 0)
				{
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#82}%d{#83}",silver,copper);
				}
				else
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#82}",silver);
			}
			else
			{
				MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#83}",copper);
			}
		}

		stItem.SetData( buf );
		m_pID_LIST_Price->AddItem(&stItem,NULL,false);

		if(m_vecHistory[i].GetType() == ConsignmentDefine::Consignment_SellRMB)
		{
			MeSprintf_s(buf, sizeof(buf)/sizeof(char)-1,"%s",theXmlString.GetString(eText_GoldTrade_Sell));
		}
		else if(m_vecHistory[i].GetType() == ConsignmentDefine::Consignment_BuyRMB)
		{
			MeSprintf_s(buf, sizeof(buf)/sizeof(char)-1,"%s",theXmlString.GetString(eText_GoldTrade_Buy));
		}

		stItem.SetData( buf );
		m_pID_LIST_Type->AddItem(&stItem,NULL,false);

		MeSprintf_s(buf, sizeof(buf)/sizeof(char)-1, /*"%d{#1103}"*/"%d{#1104}",m_vecHistory[i].GetCount() );
		stItem.SetData( buf );
		m_pID_LIST_Gold->AddItem(&stItem,NULL,false);

		thePlayerRole.GetGSCFromMoney(m_vecHistory[i].GetPrice(), gold, silver, copper);

		if (gold > 0)
		{
			if (silver > 0)
			{
				if (copper > 0)
				{
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#81}%d{#82}%d{#83}",gold,silver,copper);
				}
				else
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#81}%d{#82}",gold,silver);
			}
			else
			{
				if (copper > 0)
				{
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#81}%d{#83}",gold,copper);
				}
				else
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#81}",gold);
			}
		}
		else
		{
			if (silver > 0)
			{
				if (copper > 0)
				{
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#82}%d{#83}",silver,copper);
				}
				else
					MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#82}",silver);
			}
			else
			{
				MeSprintf_s(buf,sizeof(buf)/sizeof(char)-1,"%d{#83}",copper);
			}
		}

		stItem.SetData( buf );
		m_pID_LIST_UnitPrice->AddItem(&stItem,NULL,false);

		stItem.SetData( "" );

		switch(m_vecHistory[i].GetStatus())
		{
		case ConsignmentDefine::Status_Init:        // 初始状态
			stItem.SetData(theXmlString.GetString(eText_AuctionItemState_Status_Init));
			break;
		case ConsignmentDefine::Status_Running:          // 挂单中
			stItem.SetData(theXmlString.GetString(eText_SystemAuction_Status_Running));
			break;
		case ConsignmentDefine::Status_BuySuccess:       // 购买成功
			stItem.SetData(theXmlString.GetString(eText_SystemAuctionError_Status_BuySuccess));
			break;
		case ConsignmentDefine::Status_SellSuccess:      // 出售成功
			stItem.SetData(theXmlString.GetString(eText_SystemAuctionError_Status_SellSuccess));
			break;
		case ConsignmentDefine::Status_Buyed:            // 已购买
			stItem.SetData(theXmlString.GetString(eText_SystemAuctionError_Status_Buyed));
			break;
		case ConsignmentDefine::Status_Selled:           // 已售出
			stItem.SetData(theXmlString.GetString(eText_SystemAuctionError_Status_Selled));
			break;
		case ConsignmentDefine::Status_Cancel:           // 玩家取消订单
			stItem.SetData( theXmlString.GetString(eText_AuctionItemState_Terminate) );
			break;
		case ConsignmentDefine::Status_TimeOut:          // 订单到期
			stItem.SetData( theXmlString.GetString(eText_AuctionItemState_TimeOut) );
			break;
		}
		m_pID_LIST_FinishTime->AddItem(&stItem,NULL,false);
	}
	
}

void CUI_ID_FRAME_GoldTradeRegiste::Clear()
{
	if(!m_pID_FRAME_GoldTradeRegiste)
		return;
	m_vecHistory.clear();
}

void CUI_ID_FRAME_GoldTradeRegiste::AddMoneyAuctionHistroy(ConsignmentHistroy &data)
{
	if(!m_pID_FRAME_GoldTradeRegiste)
		return;

	m_vecHistory.push_back(data);
}

bool CUI_ID_FRAME_GoldTradeRegiste::UpdateConsignState(__int64 n64ConsignmentID,unsigned char ucStatus)
{
	vector<ConsignmentHistroy>::iterator it = m_vecHistory.begin();
	for (;it != m_vecHistory.end();++it)
	{
		if(it->GetID() == n64ConsignmentID)
		{
			it->SetStatus(ucStatus);
			return true;
		}
	}

	return false;
}
