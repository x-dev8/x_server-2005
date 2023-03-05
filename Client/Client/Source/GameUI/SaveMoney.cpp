/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Document\仓库存钱\SaveMoney.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SaveMoney.h"
#include "NetworkInput.h"
#include "PlayerRole.h"
#include "UIMgr.h"
#include "GameMain.h"
#include "XmlStringLanguage.h"
#include "ChatInfoBox.h"
#include "ShowScreenText.h"
#include "color_config.h"
#include "Ui/InfoList.h"

static bool s_bPressEnter = false;

CUI_ID_FRAME_SaveMoney s_CUI_ID_FRAME_SaveMoney;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SaveMoney, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SaveMoney, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SaveMoney, ID_BUTTON_OKOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SaveMoney, ID_BUTTON_CancleOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_SaveMoney, ID_EDIT_JinOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_SaveMoney, ID_EDIT_YinOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_SaveMoney, ID_EDIT_TongOnEditEnter )
CUI_ID_FRAME_SaveMoney::CUI_ID_FRAME_SaveMoney()
{
	// Member
	m_pID_FRAME_SaveMoney = NULL;
	m_pID_TEXT_Msg = NULL;
	m_pID_BUTTON_OK = NULL;
// 	m_pID_BUTTON_Cancle = NULL;
	m_pID_PICTURE_Jin = NULL;
	m_pID_PICTURE_Ying = NULL;
	m_pID_PICTURE_Tong = NULL;
	m_pID_EDIT_Jin = NULL;
	m_pID_EDIT_Yin = NULL;
	m_pID_EDIT_Tong = NULL;
	m_pID_TEXT_MsgGet = NULL;
	m_fCheckMoneyCD = 0.f;
}
// Frame
bool CUI_ID_FRAME_SaveMoney::OnFrameRun()
{
	if( s_bPressEnter )
	{
		ID_BUTTON_OKOnButtonClick(NULL);
		s_bPressEnter = false;
	}
	else if( IsVisable() )
	{
		// 每0.5秒检查一次钱
		if( m_fCheckMoneyCD > 0.f )
		{
			m_fCheckMoneyCD -= theHeroGame.GetFrameElapsedTime();
			if( m_fCheckMoneyCD > 0.f )
				return true;
		}

		m_fCheckMoneyCD = 0.5f;
		CheckMoney();
	}
	return true;
}
bool CUI_ID_FRAME_SaveMoney::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_SaveMoney::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SaveMoney )
		return false;
    CheckMoney();

	m_iGold = _atoi64( m_pID_EDIT_Jin->GetText() );
	m_iSilver = _atoi64( m_pID_EDIT_Yin->GetText() );
	m_iCopper = _atoi64( m_pID_EDIT_Tong->GetText() );

	// 判断是否超过仓库存放上限
	if( m_ucStorageType == MsgStorageMoneyReq::Save )
	{
		DWORD dwStorageMoney = thePlayerRole.m_stStorage.dwStorageMoney;
		DWORD dwMoney = thePlayerRole.GetMoneyFromGSC(m_iGold, m_iSilver, m_iCopper);
		DWORD dwMoneyTotal = (dwStorageMoney + dwMoney);
		int iGoldLimit = 0;
		if( thePlayerRole.GetLevel() >= 40 )
		{
			iGoldLimit = 100000;
		}
		else
		{
			iGoldLimit = 200;
		}
		if( dwMoneyTotal > iGoldLimit * 10000 )
		{
			// 提醒
			char szMsg[256] = {0};
			sprintf_s(szMsg, 255, theXmlString.GetString(eText_BeyondPackMoneyLimit), iGoldLimit);
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, szMsg );

			SetVisable(false);
			return true;
		}
	}

	DWORD dwMoney = thePlayerRole.GetMoneyFromGSC(m_iGold, m_iSilver, m_iCopper);
	MsgStorageMoneyReq kStorageMoneyReq;
	kStorageMoneyReq.chOperation = m_ucStorageType;
	kStorageMoneyReq.dwMoney = dwMoney;
	GettheNetworkInput().SendMsg( &kStorageMoneyReq );

	SetVisable(false);
	return true;
}
// Button
// bool CUI_ID_FRAME_SaveMoney::ID_BUTTON_CancleOnButtonClick( ControlObject* pSender )
// {
// 	if( !m_pID_FRAME_SaveMoney )
// 		return false;
//     SetVisable(false);
// 	return true;
// }
// Edit
void CUI_ID_FRAME_SaveMoney::ID_EDIT_JinOnEditEnter( ControlObject* pSender, const char* szData )
{
	if( !m_pID_FRAME_SaveMoney )
		return;
}
// Edit
void CUI_ID_FRAME_SaveMoney::ID_EDIT_YinOnEditEnter( ControlObject* pSender, const char* szData )
{
	if( !m_pID_FRAME_SaveMoney )
		return;
}
// Edit
void CUI_ID_FRAME_SaveMoney::ID_EDIT_TongOnEditEnter( ControlObject* pSender, const char* szData )
{
	if( !m_pID_FRAME_SaveMoney )
		return;
}

// 装载UI
bool CUI_ID_FRAME_SaveMoney::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SaveMoney.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SaveMoney.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SaveMoney::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SaveMoney, s_CUI_ID_FRAME_SaveMoneyOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SaveMoney, s_CUI_ID_FRAME_SaveMoneyOnFrameRender );
    theUiManager.OnButtonClick( ID_FRAME_SaveMoney, ID_BUTTON_OK, s_CUI_ID_FRAME_SaveMoneyID_BUTTON_OKOnButtonClick );
//     theUiManager.OnButtonClick( ID_FRAME_SaveMoney, ID_BUTTON_Cancle, s_CUI_ID_FRAME_SaveMoneyID_BUTTON_CancleOnButtonClick );
    theUiManager.OnEditEnter( ID_FRAME_SaveMoney, ID_EDIT_Jin, s_CUI_ID_FRAME_SaveMoneyID_EDIT_JinOnEditEnter );
    theUiManager.OnEditEnter( ID_FRAME_SaveMoney, ID_EDIT_Yin, s_CUI_ID_FRAME_SaveMoneyID_EDIT_YinOnEditEnter );
    theUiManager.OnEditEnter( ID_FRAME_SaveMoney, ID_EDIT_Tong, s_CUI_ID_FRAME_SaveMoneyID_EDIT_TongOnEditEnter );

	m_pID_FRAME_SaveMoney = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SaveMoney );
	m_pID_TEXT_Msg = (ControlText*)theUiManager.FindControl( ID_FRAME_SaveMoney, ID_TEXT_Msg );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_SaveMoney, ID_BUTTON_OK );
// 	m_pID_BUTTON_Cancle = (ControlButton*)theUiManager.FindControl( ID_FRAME_SaveMoney, ID_BUTTON_Cancle );
	m_pID_PICTURE_Jin = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SaveMoney, ID_PICTURE_Jin );
	m_pID_PICTURE_Ying = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SaveMoney, ID_PICTURE_Ying );
	m_pID_PICTURE_Tong = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SaveMoney, ID_PICTURE_Tong );
	m_pID_EDIT_Jin = (ControlEdit*)theUiManager.FindControl( ID_FRAME_SaveMoney, ID_EDIT_Jin );
	m_pID_EDIT_Yin = (ControlEdit*)theUiManager.FindControl( ID_FRAME_SaveMoney, ID_EDIT_Yin );
	m_pID_EDIT_Tong = (ControlEdit*)theUiManager.FindControl( ID_FRAME_SaveMoney, ID_EDIT_Tong );
	m_pID_TEXT_MsgGet = (ControlText*)theUiManager.FindControl( ID_FRAME_SaveMoney, ID_TEXT_MsgGet );
	assert( m_pID_FRAME_SaveMoney );
	assert( m_pID_TEXT_Msg );
	assert( m_pID_BUTTON_OK );
// 	assert( m_pID_BUTTON_Cancle );
	assert( m_pID_PICTURE_Jin );
	assert( m_pID_PICTURE_Ying );
	assert( m_pID_PICTURE_Tong );
	assert( m_pID_EDIT_Jin );
	assert( m_pID_EDIT_Yin );
	assert( m_pID_EDIT_Tong );
	assert( m_pID_TEXT_MsgGet );

	m_pID_FRAME_SaveMoney->SetMsgProcFun( frame_msg );

    SetVisable(false);
    m_iGold = 0;
    m_iSilver = 0;
    m_iCopper = 0;

	s_bPressEnter = false;

    USE_SCRIPT( eUI_OBJECT_SaveMoney, this );

    return true;
}
// 卸载UI
bool CUI_ID_FRAME_SaveMoney::_UnLoadUI()
{
    CLOSE_SCRIPT( eUI_OBJECT_SaveMoney );

	m_pID_FRAME_SaveMoney = NULL;
	m_pID_TEXT_Msg = NULL;
	m_pID_BUTTON_OK = NULL;
// 	m_pID_BUTTON_Cancle = NULL;
	m_pID_PICTURE_Jin = NULL;
	m_pID_PICTURE_Ying = NULL;
	m_pID_PICTURE_Tong = NULL;
	m_pID_EDIT_Jin = NULL;
	m_pID_EDIT_Yin = NULL;
	m_pID_EDIT_Tong = NULL;
	m_pID_TEXT_MsgGet = NULL;
	m_fCheckMoneyCD = 0.f;
	return theUiManager.RemoveFrame( "Data\\UI\\SaveMoney.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_SaveMoney::_IsVisable()
{
	if( !m_pID_FRAME_SaveMoney )
		return false;
	return m_pID_FRAME_SaveMoney->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SaveMoney::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_SaveMoney )
		return;
	m_pID_FRAME_SaveMoney->SetVisable( bVisable );
    if( bVisable )
    {
        m_iGold = 0;
        m_iSilver = 0;
        m_iCopper = 0;
		m_pID_EDIT_Jin->SetMaxLength(4);
        m_pID_EDIT_Jin->SetIsNumber(true);
        m_pID_EDIT_Jin->SetText("");
        m_pID_EDIT_Yin->SetMaxLength(2);
        m_pID_EDIT_Yin->SetText("");
        m_pID_EDIT_Yin->SetIsNumber(true);
        m_pID_EDIT_Tong->SetMaxLength(2);
        m_pID_EDIT_Tong->SetText("");
        m_pID_EDIT_Tong->SetIsNumber(true);
        theUiManager.SetFocus( m_pID_EDIT_Tong );

        if( m_ucStorageType == MsgStorageMoneyReq::Save )
        {
            m_pID_TEXT_Msg->SetVisable(true);
            m_pID_TEXT_MsgGet->SetVisable(false);
        }
        else
        {
            m_pID_TEXT_Msg->SetVisable(false);
            m_pID_TEXT_MsgGet->SetVisable(true);
        }
    }
}

void CUI_ID_FRAME_SaveMoney::CheckMoney()
{
    int iGold = _atoi64( s_CUI_ID_FRAME_SaveMoney.m_pID_EDIT_Jin->GetText() );
    int iSilver = _atoi64( s_CUI_ID_FRAME_SaveMoney.m_pID_EDIT_Yin->GetText() );
    int iCopper = _atoi64( s_CUI_ID_FRAME_SaveMoney.m_pID_EDIT_Tong->GetText() );

    if( iGold > 0 || iSilver > 0 || iCopper > 0 )
    {
        // 发送存/取消息
        DWORD dwMoney = thePlayerRole.GetMoneyFromGSC(iGold, iSilver, iCopper);
        bool bHasEnoughMoney = false;
        if( s_CUI_ID_FRAME_SaveMoney.m_ucStorageType == MsgStorageMoneyReq::Save )
        {
            // 判断背包里钱够不够
            bHasEnoughMoney = thePlayerRole.PackHasEnoughMoney(dwMoney);
            if( !bHasEnoughMoney )
            {
                DWORD dwMaxMoney = thePlayerRole.GetData(CPlayerRole::TYPE_MONEY);
                thePlayerRole.GetGSCFromMoney(dwMaxMoney, iGold, iSilver, iCopper);
                s_CUI_ID_FRAME_SaveMoney.m_pID_EDIT_Jin->SetText(iGold);
                s_CUI_ID_FRAME_SaveMoney.m_pID_EDIT_Yin->SetText(iSilver);
                s_CUI_ID_FRAME_SaveMoney.m_pID_EDIT_Tong->SetText(iCopper);
           }
        }
        else
        {
            // 判断仓库里钱够不够
            bHasEnoughMoney = thePlayerRole.StorageHasEnoughMoney(dwMoney);
            if( !bHasEnoughMoney )
            {
                DWORD dwMaxMoney = thePlayerRole.m_stStorage.dwStorageMoney;
                thePlayerRole.GetGSCFromMoney(dwMaxMoney, iGold, iSilver, iCopper);
                if( iGold > 0 )
                    s_CUI_ID_FRAME_SaveMoney.m_pID_EDIT_Jin->SetText(iGold);
                else
                    s_CUI_ID_FRAME_SaveMoney.m_pID_EDIT_Jin->SetText("");
                if( iSilver > 0 )
                    s_CUI_ID_FRAME_SaveMoney.m_pID_EDIT_Yin->SetText(iSilver);
                else
                    s_CUI_ID_FRAME_SaveMoney.m_pID_EDIT_Yin->SetText("");
                if( iCopper > 0 )
                    s_CUI_ID_FRAME_SaveMoney.m_pID_EDIT_Tong->SetText(iCopper);
                else
                    s_CUI_ID_FRAME_SaveMoney.m_pID_EDIT_Tong->SetText("");
            }
        }
    }
}

bool CUI_ID_FRAME_SaveMoney::frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	guardfunc;
	if( !s_CUI_ID_FRAME_SaveMoney.IsVisable() )
		return false;

	if ( bMsgUsed == true )
		return false;

	if( msg == WM_KEYDOWN )
	{
		if( wParam == VK_RETURN )
		{
			s_bPressEnter = true;
			return true;
		}
	}

	return false;

	unguard;
}