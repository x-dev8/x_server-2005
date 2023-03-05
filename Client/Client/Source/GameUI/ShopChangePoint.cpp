/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\ShopChangePoint.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ShopChangePoint.h"
#include "MeTerrain/stdafx.h"
#include "Me3d/ShaderManager.h"
#include "Me3d/Engine/RendererDX.h"
#include "MeTerrain/SwGlobal.h"
#include "wsRender.h"
#include "GameMain.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "TradeCenterConfig.h"
#include "TradeCenterInfo.h"
#include "BatchShop.h"
#include "Pack.h"
#include "MessageBox.h"
#include "XmlStringLanguage.h"
#include "MeFont/MeFont.h"

CUI_ID_FRAME_ShopChangePoint s_CUI_ID_FRAME_ShopChangePoint;
MAP_FRAME_RUN( s_CUI_ID_FRAME_ShopChangePoint, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ShopChangePoint, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShopChangePoint, ID_BUTTON_OkOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShopChangePoint, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShopChangePoint, ID_BUTTON_CloseOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShopChangePoint, ID_BUTTON_HelpOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_ShopChangePoint, ID_EDIT_YuanBaoOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShopChangePoint, ID_BUTTON_UpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShopChangePoint, ID_BUTTON_DownOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShopChangePoint, ID_BUTTON_MaxOnButtonClick )
CUI_ID_FRAME_ShopChangePoint::CUI_ID_FRAME_ShopChangePoint()
{
	// Member
	ResetMembers();
}
void CUI_ID_FRAME_ShopChangePoint::ResetMembers()
{
	m_pID_FRAME_ShopChangePoint = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_PICTURE_22476 = NULL;
	m_pID_PICTURE_28008 = NULL;
	m_pID_PICTURE_27628 = NULL;
	m_pID_PICTURE_20101 = NULL;
	m_pID_PICTURE_TitleWall = NULL;
	m_pID_TEXT_Point = NULL;
	m_pID_TEXT_Title = NULL;
	m_pID_BUTTON_Close = NULL;
	m_pID_BUTTON_Help = NULL;
	m_pID_PICTURE_Wall3 = NULL;
	m_pID_EDIT_YuanBao = NULL;
	m_pID_TEXT_Word = NULL;
	m_pID_TEXT_ChangeWord = NULL;
	m_pID_BUTTON_Up = NULL;
	m_pID_BUTTON_Down = NULL;
	m_pID_BUTTON_Max = NULL;
	m_dwLastTime = 0;
	m_nPoint = 0;

    m_pID_TEXT_ChangeRate = NULL;
    m_pID_TEXT_Hold = NULL;
}
// Frame
bool CUI_ID_FRAME_ShopChangePoint::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_ShopChangePoint::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_ShopChangePoint::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ShopChangePoint)
		return false;
	int count = 0;
	if (strlen(m_pID_EDIT_YuanBao->GetText()) > 0)
		count = atoi( m_pID_EDIT_YuanBao->GetText() );

	if (count > 0)
	{
		MsgReqRmbOp msg;
		msg.op = MsgReqRmbOp::ET_ExchangeJinDing;
		msg.value = count;
		GettheNetworkInput().SendMsg( &msg );

		m_nMaxValue = 0;
		m_pID_EDIT_YuanBao->SetNumberLimit(true, 0, m_nMaxValue);
		m_pID_EDIT_YuanBao->SetText(0);

		m_pID_TEXT_Point->SetText(theXmlString.GetString(eText_ExchangeRmbPoint));

		m_pID_BUTTON_Ok->SetEnable(false);
	}

	return true;
}
// Button
bool CUI_ID_FRAME_ShopChangePoint::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ShopChangePoint)
		return false;
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_ShopChangePoint::ID_BUTTON_CloseOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ShopChangePoint)
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_ShopChangePoint::ID_BUTTON_HelpOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ShopChangePoint)
		return false;
	return true;
}
// Edit
void CUI_ID_FRAME_ShopChangePoint::ID_EDIT_YuanBaoOnEditEnter( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_ShopChangePoint)
		return;
}
// Button
bool CUI_ID_FRAME_ShopChangePoint::ID_BUTTON_UpOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ShopChangePoint)
		return false;
	INT nCnt = atoi( m_pID_EDIT_YuanBao->GetText() );
	if(nCnt >= m_nMaxValue)
		return true;
	nCnt ++;
	m_pID_EDIT_YuanBao->SetText( nCnt );
	return true;
}
// Button
bool CUI_ID_FRAME_ShopChangePoint::ID_BUTTON_DownOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ShopChangePoint)
		return false;
	int number = 1;
	if (strlen(m_pID_EDIT_YuanBao->GetText()) > 0)
		number = atoi(m_pID_EDIT_YuanBao->GetText());
	if (number > 0)
	{
		--number;
		m_pID_EDIT_YuanBao->SetText(number);
	}
	return true;
}
// Button
bool CUI_ID_FRAME_ShopChangePoint::ID_BUTTON_MaxOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ShopChangePoint)
		return false;
	m_pID_EDIT_YuanBao->SetText(m_nMaxValue);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_ShopChangePoint::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ShopChangePoint.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\ShopChangePoint.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_ShopChangePoint::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_ShopChangePoint, s_CUI_ID_FRAME_ShopChangePointOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ShopChangePoint, s_CUI_ID_FRAME_ShopChangePointOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_ShopChangePoint, ID_BUTTON_Ok, s_CUI_ID_FRAME_ShopChangePointID_BUTTON_OkOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ShopChangePoint, ID_BUTTON_Cancel, s_CUI_ID_FRAME_ShopChangePointID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ShopChangePoint, ID_BUTTON_Close, s_CUI_ID_FRAME_ShopChangePointID_BUTTON_CloseOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ShopChangePoint, ID_BUTTON_Help, s_CUI_ID_FRAME_ShopChangePointID_BUTTON_HelpOnButtonClick );
	theUiManager.OnEditEnter( ID_FRAME_ShopChangePoint, ID_EDIT_YuanBao, s_CUI_ID_FRAME_ShopChangePointID_EDIT_YuanBaoOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_ShopChangePoint, ID_BUTTON_Up, s_CUI_ID_FRAME_ShopChangePointID_BUTTON_UpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ShopChangePoint, ID_BUTTON_Down, s_CUI_ID_FRAME_ShopChangePointID_BUTTON_DownOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ShopChangePoint, ID_BUTTON_Max, s_CUI_ID_FRAME_ShopChangePointID_BUTTON_MaxOnButtonClick );

	m_pID_FRAME_ShopChangePoint = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ShopChangePoint );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_ShopChangePoint, ID_BUTTON_Ok );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_ShopChangePoint, ID_BUTTON_Cancel );
	m_pID_PICTURE_22476 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopChangePoint, ID_PICTURE_22476 );
	m_pID_PICTURE_28008 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopChangePoint, ID_PICTURE_28008 );
	m_pID_PICTURE_27628 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopChangePoint, ID_PICTURE_27628 );
	m_pID_PICTURE_20101 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopChangePoint, ID_PICTURE_20101 );
	m_pID_PICTURE_TitleWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopChangePoint, ID_PICTURE_TitleWall );
	m_pID_TEXT_Point = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopChangePoint, ID_TEXT_Point );
	m_pID_TEXT_Title = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopChangePoint, ID_TEXT_Title );
	m_pID_BUTTON_Close = (ControlButton*)theUiManager.FindControl( ID_FRAME_ShopChangePoint, ID_BUTTON_Close );
	m_pID_BUTTON_Help = (ControlButton*)theUiManager.FindControl( ID_FRAME_ShopChangePoint, ID_BUTTON_Help );
	m_pID_PICTURE_Wall3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopChangePoint, ID_PICTURE_Wall3 );
	m_pID_EDIT_YuanBao = (ControlEdit*)theUiManager.FindControl( ID_FRAME_ShopChangePoint, ID_EDIT_YuanBao );
	m_pID_TEXT_Word = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopChangePoint, ID_TEXT_Word );
	m_pID_TEXT_ChangeWord = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopChangePoint, ID_TEXT_ChangeWord );
	m_pID_BUTTON_Up = (ControlButton*)theUiManager.FindControl( ID_FRAME_ShopChangePoint, ID_BUTTON_Up );
	m_pID_BUTTON_Down = (ControlButton*)theUiManager.FindControl( ID_FRAME_ShopChangePoint, ID_BUTTON_Down );
	m_pID_BUTTON_Max = (ControlButton*)theUiManager.FindControl( ID_FRAME_ShopChangePoint, ID_BUTTON_Max );

    m_pID_TEXT_ChangeRate = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopChangePoint, ID_TEXT_ChangeRate );
    m_pID_TEXT_Hold = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopChangePoint, ID_TEXT_Hold );
	assert( m_pID_TEXT_ChangeRate );
	assert( m_pID_TEXT_Hold );

	m_pID_EDIT_YuanBao->SetTextChangedFun(EditDataChange);
	m_pID_EDIT_YuanBao->SetIsNumber(true);

	m_dwLastTime = 0;
	m_nPoint = -1;

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_ShopChangePoint::_UnLoadUI()
{
    ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\ShopChangePoint.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_ShopChangePoint::_IsVisable()
{
    if(!m_pID_FRAME_ShopChangePoint)
        return false;
	return m_pID_FRAME_ShopChangePoint->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_ShopChangePoint::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_ShopChangePoint )
		return;
	m_pID_FRAME_ShopChangePoint->SetVisable( bVisable );
	if (bVisable)
	{

		int count = 0;
		char buf[256];
		sprintf(buf, theXmlString.GetString(eText_ExchangeNeedPoint), count);
		m_pID_TEXT_ChangeWord->SetText(buf);

        //设置对换比例
        sprintf(buf,theXmlString.GetString(eText_ChangePoint),theTradeCenter.GetTradeRadio());
        m_pID_TEXT_ChangeRate->SetText(buf);

        //拥有金锭数
        sprintf(buf,theXmlString.GetString(eText_OwnGold),thePlayerRole.GetData(CPlayerRole::TYPE_JinDing));
        m_pID_TEXT_Hold->SetText(buf);

		DWORD dwTime = HQ_TimeGetTime();
		if (dwTime - m_dwLastTime > 1000 * 60 * 5 || m_nPoint == -1)
		{
			m_dwLastTime = dwTime;

			MsgReqRmbOp msg;
			msg.op = MsgReqRmbOp::ET_QueryPoint;
			GettheNetworkInput().SendMsg( &msg );

			m_pID_TEXT_Point->SetText(theXmlString.GetString(eText_ReqRmbPoint));

			m_nMaxValue = 0;
			m_pID_EDIT_YuanBao->SetNumberLimit(true, 0, m_nMaxValue);
			m_pID_EDIT_YuanBao->SetText(0);
		}
		else
		{
			char buf[256];
			sprintf(buf, theXmlString.GetString(eText_RemainRmbPoint), m_nPoint);
			m_pID_TEXT_Point->SetText(buf);

			m_nMaxValue = m_nPoint;
			m_pID_EDIT_YuanBao->SetNumberLimit(true, 0, m_nMaxValue);
			m_pID_EDIT_YuanBao->SetText(0);
		}

		m_pID_BUTTON_Ok->SetEnable(false);

		m_pID_EDIT_YuanBao->SetActivate();
	}
}

void CUI_ID_FRAME_ShopChangePoint::EditDataChange( OUT ControlObject* pSender, OUT const char *szData )
{
	if (!szData)
		return;
	if( !s_CUI_ID_FRAME_ShopChangePoint.GetFrame() )
		return;

	int count = 0;
	if (strlen(szData) > 0)
		count = atoi( szData );

	if (count > 0)
		s_CUI_ID_FRAME_ShopChangePoint.m_pID_BUTTON_Ok->SetEnable(true);

	int jinDing = count * theTradeCenter.GetTradeRadio();

	char buf[256];
	sprintf(buf, theXmlString.GetString(eText_ExchangeNeedPoint), jinDing);
	s_CUI_ID_FRAME_ShopChangePoint.m_pID_TEXT_ChangeWord->SetText(buf);
}

void CUI_ID_FRAME_ShopChangePoint::YuanBao_SetNumberLimit( bool limit, int min, int max )
{
	if( !m_pID_FRAME_ShopChangePoint )
		return;
	m_pID_EDIT_YuanBao->SetNumberLimit(limit, min, max);
}

void CUI_ID_FRAME_ShopChangePoint::Point_SetText( const char* text )
{
	if( !m_pID_FRAME_ShopChangePoint || !text )
		return;
	m_pID_TEXT_Point->SetText(text);
}

void CUI_ID_FRAME_ShopChangePoint::Hold_SetText( const char* text )
{
	if( !m_pID_FRAME_ShopChangePoint || !text )
		return;
	m_pID_TEXT_Hold->SetText(text);
}