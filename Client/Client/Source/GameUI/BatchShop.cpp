/********************************************************************
Created by UIEditor.exe
FileName: D:\My Documents\桌面\BatchShop.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "BatchShop.h"
#include "InputBox.h"
#include "Shop.h"
#include "MeUi/ExpressionManager.h"
#include "PlayerPrivateShop.h"
#include "XmlStringLanguage.h"
#include "ItemDetail.h"
#include "PlayerRole.h"
#include "PlayerRole.h"
#include "Common.h"
#include "Shop.h"
#include "SystemStallage.h"

CUI_ID_FRAME_BatchShop s_CUI_ID_FRAME_BatchShop;
MAP_FRAME_RUN( s_CUI_ID_FRAME_BatchShop, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_BatchShop, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BatchShop, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BatchShop, ID_BUTTON_CancleOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_BatchShop, ID_EDIT_NumberOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BatchShop, ID_BUTTON_UpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BatchShop, ID_BUTTON_DownOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BatchShop, ID_BUTTON_MaxOnButtonClick )

funBatchCallbackFun	m_pCurCallbackFun = NULL;
void*			m_pData = NULL;
std::vector<CUI_InputBox::S_InputBox> m_vtInputBox;

bool CUI_ID_FRAME_BatchShop::ms_bPrivateShop =false;

CUI_ID_FRAME_BatchShop::CUI_ID_FRAME_BatchShop()
{
	// Member
	m_pID_FRAME_BatchShop = NULL;
	m_pID_TEXT_Msg = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancle = NULL;
	m_pID_PICTURE_TotalPriceWall = NULL;
	m_pID_TEXT_TotalPriceZ = NULL;
	m_pID_TEXT_TotalPrice = NULL;
	m_pID_PICTURE_Number = NULL;
	m_pID_EDIT_Number = NULL;
	m_pID_BUTTON_Up = NULL;
	m_pID_BUTTON_Down = NULL;
	m_pID_BUTTON_Max = NULL;

	ms_bPrivateShop = false;
}
// Frame
bool CUI_ID_FRAME_BatchShop::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_BatchShop::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_BatchShop::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_BatchShop)
	{
		assert(false&&"ui error");
		return false;
	}

	if ( m_pCurCallbackFun )
	{
		m_pCurCallbackFun( m_pID_EDIT_Number->GetText(), m_pData );
	}
	if ( m_pData )
	{
		delete[] m_pData;
		m_pData = NULL;
	}
	//m_vtInputBox.pop_back();
	if ( m_vtInputBox.size() > 0 )
	{
		m_vtInputBox.erase( m_vtInputBox.begin() );
	}
	Refresh();
	return true;
}
// Button
bool CUI_ID_FRAME_BatchShop::ID_BUTTON_CancleOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_BatchShop)
	{
		assert(false&&"ui error");
		return false;
	}

	if ( m_pData )
	{
		delete[] m_pData;
		m_pData = NULL;
	}
	//m_vtInputBox.pop_back();
	if ( m_vtInputBox.size() > 0 )
	{
		m_vtInputBox.erase( m_vtInputBox.begin() );
	}
	Refresh();
	return true;
}
// Edit
void CUI_ID_FRAME_BatchShop::ID_EDIT_NumberOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// Button
bool CUI_ID_FRAME_BatchShop::ID_BUTTON_UpOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_BatchShop)
	{
		assert(false&&"ui error");
		return false;
	}

	int number = 0;
	if (strlen(m_pID_EDIT_Number->GetText()) > 0)
		number = atoi(m_pID_EDIT_Number->GetText());
	if (number < m_nMaxNumber)
	{
		++number;
		m_pID_EDIT_Number->SetText(number);
	}
	return true;
}
// Button
bool CUI_ID_FRAME_BatchShop::ID_BUTTON_DownOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_BatchShop)
	{
		assert(false&&"ui error");
		return false;
	}

	int number = 2;
	if (strlen(m_pID_EDIT_Number->GetText()) > 0)
		number = atoi(m_pID_EDIT_Number->GetText());
	if (number > 1)
	{
		--number;
		m_pID_EDIT_Number->SetText(number);
	}
	return true;
}
// Button
bool CUI_ID_FRAME_BatchShop::ID_BUTTON_MaxOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_BatchShop)
	{
		assert(false&&"ui error");
		return false;
	}

	m_pID_EDIT_Number->SetText(m_nMaxNumber);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_BatchShop::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\BatchShop.MEUI", true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\BatchShop.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_BatchShop::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_BatchShop, s_CUI_ID_FRAME_BatchShopOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_BatchShop, s_CUI_ID_FRAME_BatchShopOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_BatchShop, ID_BUTTON_OK, s_CUI_ID_FRAME_BatchShopID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_BatchShop, ID_BUTTON_Cancle, s_CUI_ID_FRAME_BatchShopID_BUTTON_CancleOnButtonClick );
	theUiManager.OnEditEnter( ID_FRAME_BatchShop, ID_EDIT_Number, s_CUI_ID_FRAME_BatchShopID_EDIT_NumberOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_BatchShop, ID_BUTTON_Up, s_CUI_ID_FRAME_BatchShopID_BUTTON_UpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_BatchShop, ID_BUTTON_Down, s_CUI_ID_FRAME_BatchShopID_BUTTON_DownOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_BatchShop, ID_BUTTON_Max, s_CUI_ID_FRAME_BatchShopID_BUTTON_MaxOnButtonClick );

	m_pID_FRAME_BatchShop = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_BatchShop );
	m_pID_TEXT_Msg = (ControlText*)theUiManager.FindControl( ID_FRAME_BatchShop, ID_TEXT_Msg );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_BatchShop, ID_BUTTON_OK );
	m_pID_BUTTON_Cancle = (ControlButton*)theUiManager.FindControl( ID_FRAME_BatchShop, ID_BUTTON_Cancle );
	m_pID_PICTURE_TotalPriceWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BatchShop, ID_PICTURE_TotalPriceWall );
	m_pID_TEXT_TotalPriceZ = (ControlText*)theUiManager.FindControl( ID_FRAME_BatchShop, ID_TEXT_TotalPriceZ );
	m_pID_TEXT_TotalPrice = (ControlText*)theUiManager.FindControl( ID_FRAME_BatchShop, ID_TEXT_TotalPrice );
	m_pID_PICTURE_Number = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BatchShop, ID_PICTURE_Number );
	m_pID_EDIT_Number = (ControlEdit*)theUiManager.FindControl( ID_FRAME_BatchShop, ID_EDIT_Number );
	m_pID_BUTTON_Up = (ControlButton*)theUiManager.FindControl( ID_FRAME_BatchShop, ID_BUTTON_Up );
	m_pID_BUTTON_Down = (ControlButton*)theUiManager.FindControl( ID_FRAME_BatchShop, ID_BUTTON_Down );
	m_pID_BUTTON_Max = (ControlButton*)theUiManager.FindControl( ID_FRAME_BatchShop, ID_BUTTON_Max );
	SetVisable( false );
	assert( m_pID_FRAME_BatchShop );
	assert( m_pID_TEXT_Msg );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_Cancle );
	assert( m_pID_PICTURE_TotalPriceWall );
	assert( m_pID_TEXT_TotalPriceZ );
	assert( m_pID_TEXT_TotalPrice );
	assert( m_pID_PICTURE_Number );
	assert( m_pID_EDIT_Number );

	m_pID_EDIT_Number->SetIsNumber( true );
	m_pID_EDIT_Number->SetMaxLength( 2 );
	m_pID_EDIT_Number->SetTextChangedFun( CUI_ID_FRAME_BatchShop::EditDataChange );
	SetMaxValue(99);
	//m_pID_EDIT_Number->SetNumberLimit(true, 0, 99);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_BatchShop::_UnLoadUI()
{
	m_pID_FRAME_BatchShop = NULL;
	m_pID_TEXT_Msg = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancle = NULL;
	m_pID_PICTURE_TotalPriceWall = NULL;
	m_pID_TEXT_TotalPriceZ = NULL;
	m_pID_TEXT_TotalPrice = NULL;
	m_pID_PICTURE_Number = NULL;
	m_pID_EDIT_Number = NULL;
	m_pID_BUTTON_Up = NULL;
	m_pID_BUTTON_Down = NULL;
	m_pID_BUTTON_Max = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\BatchShop.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_BatchShop::_IsVisable()
{
	if(!m_pID_FRAME_BatchShop)
		return false;

	return m_pID_FRAME_BatchShop->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_BatchShop::_SetVisable( const bool bVisable )
{
	m_pID_FRAME_BatchShop->SetVisable( bVisable );
	theUiManager.ToTop( m_pID_FRAME_BatchShop );		
}

bool CUI_ID_FRAME_BatchShop::EditInputIsVisable()
{	
	if (m_pID_EDIT_Number == NULL)
	{
		return false;
	}
	return m_pID_EDIT_Number == theUiManager.GetFocus();		
}

void CUI_ID_FRAME_BatchShop::Show(const char* szCaption, const bool bIsNumber /* = true */, const bool bModal /* = true */, 
								  const funBatchCallbackFun pFun /* = NULL */, void *pData /* = NULL */, const int nDataLength /* = 0  */, 
								  const bool bIfPwd /* = false */,int nMaxLength /* = 2 */,bool bPrivateShop /*false*/)
{
	guardfunc;
	// deleted, jiayi, [2009/11/25]
	//s_CUI_ID_FRAME_BatchShop.m_nMaxNumber = 99;

	ms_bPrivateShop = bPrivateShop;

	CUI_InputBox::S_InputBox stInputBox;
	stInputBox.m_strCaption = szCaption;
	stInputBox.m_pCallbackFun = pFun;
	stInputBox.m_bModal = bModal;
	stInputBox.m_bIsNumber = bIsNumber;
	stInputBox.m_bIsPassWord = bIfPwd;
	s_CUI_ID_FRAME_BatchShop.SetVisable(true);
	s_CUI_ID_FRAME_BatchShop.m_pID_EDIT_Number->SetMaxLength(nMaxLength);
	s_CUI_ID_FRAME_BatchShop.m_pID_EDIT_Number->SetText("");
	if ( pData && nDataLength > 0 )
	{
		stInputBox.m_pData = MeDefaultNew BYTE[nDataLength];
		memcpy( stInputBox.m_pData, pData, nDataLength );
	}
	m_vtInputBox.push_back( stInputBox );
	s_CUI_ID_FRAME_BatchShop.Refresh();
	s_CUI_ID_FRAME_BatchShop.SetEditDataChangedCallback(CUI_ID_FRAME_BatchShop::EditDataChange);
	unguard;
}

void CUI_ID_FRAME_BatchShop::Refresh()
{
	if ( m_vtInputBox.size() > 0 )
	{
		CUI_InputBox::S_InputBox *pInputBox;
		pInputBox = &m_vtInputBox[0];
		//*m_pID_TEXT_CAPTION = pInputBox->m_strCaption;
		*m_pID_EDIT_Number = "";
		m_pCurCallbackFun = pInputBox->m_pCallbackFun;
		m_pData = pInputBox->m_pData;
		if ( pInputBox->m_bModal == true )
		{
			m_pID_FRAME_BatchShop->SetArrayMode( ArrayMode_Top );
		}
		else
		{
			m_pID_FRAME_BatchShop->SetArrayMode( ArrayMode_Normal );
		}			
		m_pID_EDIT_Number->SetIsNumber( pInputBox->m_bIsNumber );
		m_pID_EDIT_Number->SetIsPassword( pInputBox->m_bIsPassWord );

		SetVisable( true );
		theUiManager.Compositor();
		m_pID_EDIT_Number->SetActivate();
	}
	else
	{
		SetVisable( false );
	}
}

bool CUI_ID_FRAME_BatchShop::InputBox_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	guardfunc;
	if( !s_CUI_ID_FRAME_BatchShop.IsVisable() )
		return false;

	switch( msg ) 
	{
	case WM_KEYUP:
		{
			if( wParam == VK_ESCAPE/*g_shortcutKey_configure.getValueCharWin32(AN_Configure_ShortcutKey::AN_SCKC_uiMessageCancel)*/ )	//cancle
			{
				s_CUI_ID_FRAME_BatchShop.ID_BUTTON_CancleOnButtonClick( NULL );
				return true;
			}
			else if( wParam == VK_RETURN/*g_shortcutKey_configure.getValueCharWin32(AN_Configure_ShortcutKey::AN_SCKC_uiMessageOk)*/ )
			{
				s_CUI_ID_FRAME_BatchShop.ID_BUTTON_OKOnButtonClick( NULL );
				return true;
			}
		}
		break;
	}
	return false;
	unguard;
}

void CUI_ID_FRAME_BatchShop::EditDataChange( OUT ControlObject* pSender, OUT const char *szData )
{
	DWORD dwCost = -1;
	if( !m_pData )
		return;

	if ( s_CUI_ID_FRAME_BatchShop.m_pID_EDIT_Number != pSender )
	{
		return ;
	}

	unsigned short ustItemID = InvalidLogicNumber;
    bool bJiaoziTypeNeedMoney = false; 

    // modified by ZhuoMeng.Hu		[12/23/2010]
	bool IsGuildShop = false;
	DWORD price = 0;
	if( s_CUI_ID_FRAME_PlayerPrivateShop.IsVisable() )
	{
        CSystemStallage::StallageItem* pStallInfo = ( CSystemStallage::StallageItem* )m_pData;
		dwCost = pStallInfo->m_nMoneyPrice;
        ustItemID = pStallInfo->m_nItemId;
	}
	else if( s_CUI_ID_FRAME_SHOP.IsVisable() )
	{
		TempTransferStruct* pData = (TempTransferStruct*)m_pData;			
		dwCost = s_CUI_ID_FRAME_SHOP.GetItemSellPrice( pData->m_nId );
		ustItemID = pData->m_nId;
        bJiaoziTypeNeedMoney = !pData->m_bNeedJiaozi;
		if(s_CUI_ID_FRAME_SHOP.GetIsGuildShop())
		{
			IsGuildShop = true;
			if(s_CUI_ID_FRAME_SHOP.GetItemCost(ustItemID))
				price = s_CUI_ID_FRAME_SHOP.GetItemCost(ustItemID)->nCost;		
		}
	}

	

	if ( dwCost == -1 )
		return;

	ItemDefine::SItemCommon *pItemDetail = NULL;
	pItemDetail = GettheItemDetail().GetItemByID( ustItemID  );
	if (!pItemDetail)
		return;

	DWORD dwCount = atoi( s_CUI_ID_FRAME_BatchShop.m_pID_EDIT_Number->GetText() );
	DWORD dwTotalPrice = dwCost * dwCount;

	price = price * dwCount;

	std::stringstream str;
	std::string text = "";
	if(!ms_bPrivateShop)
	{
		if(IsGuildShop)
		{
			str << price << "#80 ";
			text = str.str();
			ExpressionManager::GetInstance().AddExpressionAni(text);
		}
		else if (pItemDetail->costType == ItemDefine::CT_Money)
		{
			// 金钱gif
			thePlayerRole.GetGSCStringFromMoney(dwTotalPrice, text);
		}
		else if (pItemDetail->costType == ItemDefine::CT_Reputation)
		{
			// 名望gif,98
			str << dwTotalPrice << "#98 ";
		}
		else if (pItemDetail->costType == ItemDefine::CT_Exploit)
		{
			// 功勋gif,99
			str << dwTotalPrice << "#99 ";
		}
		else if (pItemDetail->costType == ItemDefine::CT_Item)
		{
			// 令牌
			char szBuff[256];
			MeSprintf_s( szBuff, sizeof(szBuff)/sizeof(char) - 1, "%d%s%d", pItemDetail->dwCost * dwCount, "#lp", pItemDetail->costItemID );
			str << szBuff << " ";
		}
		else if (pItemDetail->costType == ItemDefine::CT_GuildOffer)
		{
			// 帮贡gif,80
			str << dwTotalPrice << "#80 ";
		}
		else if (pItemDetail->costType == ItemDefine::CT_GuildMoney)
		{
			// 帮会资金
			int gold = 0;
			int silver = 0;
			int copper = 0;
			thePlayerRole.GetGSCFromMoney(dwTotalPrice,gold,silver,copper);

			str << theXmlString.GetString( eText_GuildMoney );

			if (gold > 0)
			{
				str << gold << "#68  ";
			}
			if (silver > 0)
			{
				str << silver << "#66  ";
			}
			if (copper > 0)
			{
				str << copper << "#67  ";
			}
		}
		else if (pItemDetail->costType == ItemDefine::CT_GuildBuild)
		{
			// 帮贡gif,80
			str << dwTotalPrice << "#69 ";
		}
		else if( pItemDetail->costType == ItemDefine::CT_MasterValue )
		{
			// 师傅威望
			int dwMoney = pItemDetail->dwCost;
			if( dwMoney > 0 )
			{
				str << dwTotalPrice << "#64 ";
			}
		}
		else if(pItemDetail->costType = ItemDefine::CT_JiaoZi)
		{
			if( bJiaoziTypeNeedMoney )
			{
				thePlayerRole.GetGSCStringFromMoney( dwTotalPrice,text );
			}
			else
			{
				thePlayerRole.GetGSCStringFromJiaoZi( dwTotalPrice,text );
			}
		}

		if (pItemDetail->costType != ItemDefine::CT_Money&&pItemDetail->costType != ItemDefine::CT_JiaoZi)
		{
			text = str.str();
			ExpressionManager::GetInstance().AddExpressionAni(text);
		}
	}
	else
	{
		// 金钱gif
		thePlayerRole.GetGSCStringFromMoney(dwTotalPrice, text);
	}

	*s_CUI_ID_FRAME_BatchShop.m_pID_TEXT_TotalPrice= text;	
}

void CUI_ID_FRAME_BatchShop::SetEditNumber( int i )
{
	if(m_pID_EDIT_Number)
		m_pID_EDIT_Number->SetText(i);
	else
		assert(false&&"ui error");
}

void CUI_ID_FRAME_BatchShop::SetTextTotalPrice( string str )
{
	if(m_pID_TEXT_TotalPrice)
		m_pID_TEXT_TotalPrice->SetText(str);
	else
		assert(false&&"ui error");
}

const char* CUI_ID_FRAME_BatchShop::GetEditNumberText()
{
	if(m_pID_EDIT_Number)
		return m_pID_EDIT_Number->GetText();
	else
		assert(false&&"ui error");

	return NULL;
}