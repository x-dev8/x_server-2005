/********************************************************************
Created by UIEditor.exe
FileName: E:\work\Client\UI\BillBoard.cpp
*********************************************************************/
#include <assert.h>
#include "ui/BillBoard.h"
#include "MotionBillBoard.h"
#include "MeUi/UiManager.h"

#include "FuncPerformanceLog.h"

#include "Guild_Pic.h"

CUI_ID_FRAME_BillBoard s_CUI_ID_FRAME_BillBoard;
MAP_FRAME_RUN( s_CUI_ID_FRAME_BillBoard, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_BillBoard, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BillBoard, ID_BUTTON_NextOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BillBoard, ID_BUTTON_BackOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BillBoard, ID_BUTTON_CloseOnButtonClick )
CUI_ID_FRAME_BillBoard::CUI_ID_FRAME_BillBoard()
{
	// SGuildMember
	m_pID_FRAME_BillBoard = NULL;
	m_pID_BUTTON_Next = NULL;
	m_pID_BUTTON_Back = NULL;
	m_pID_BUTTON_Close = NULL;
	m_pID_TEXT_Text = NULL;
}
// Frame
bool CUI_ID_FRAME_BillBoard::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_BillBoard::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_BillBoard::ID_BUTTON_NextOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_BillBoard::ID_BUTTON_BackOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_BillBoard::ID_BUTTON_CloseOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if(!m_pID_FRAME_BillBoard)
	{
		assert(false&&"ui error");
		return false;
	}

    if ( !StringBuffer.empty() )
    {
        StringBuffer.erase( StringBuffer.begin() );
    }
	if (StringBuffer.empty())
	{
        SetVisable(false);
		GetBillBoard()->SetSpritePlay(false);
	}
    else
    {
        SetVisable(true);
		GetBillBoard()->SetSpritePlay(true);
		m_pID_TEXT_Text->SetText(StringBuffer.at(0));
	}

	return true;
	unguard;
}
void CUI_ID_FRAME_BillBoard::OnVisibleChanged( ControlObject* pSender )
{
    if ( !pSender->IsVisable() )
    {
        if ( !StringBuffer.empty() )
        {
            StringBuffer.erase( StringBuffer.begin() );
        }
        GetBillBoard()->SetSpritePlay(false);
    }
}

void BillBoard_OnVisibleChanged( ControlObject* pSender )
{
    s_CUI_ID_FRAME_BillBoard.OnVisibleChanged( pSender );
}

void CUI_ID_FRAME_BillBoard::PushStringBuffer(std::string szbuff)
{
	guardfunc;
	StringBuffer.push_back(szbuff);
	unguard;
}
// 装载UI
bool CUI_ID_FRAME_BillBoard::_LoadUI()
{
	guardfunc;
	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\BillBoard.meui" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\BillBoard.UI]失败")
			return false;
	}
// 	else if ( dwResult != 0/*文件版本号*/ )
// 	{
// 		MESSAGE_BOX("读取文件[Data\\UI\\BillBoard.UI]与源代码版本不一样")
// 	}
	return DoControlConnect();
	unguard;
}
// 关连控件
bool CUI_ID_FRAME_BillBoard::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_BillBoard, s_CUI_ID_FRAME_BillBoardOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_BillBoard, s_CUI_ID_FRAME_BillBoardOnFrameRender );
	//theUiManager.OnButtonClick( ID_FRAME_BillBoard, ID_BUTTON_Next, s_CUI_ID_FRAME_BillBoardID_BUTTON_NextOnButtonClick );
	//theUiManager.OnButtonClick( ID_FRAME_BillBoard, ID_BUTTON_Back, s_CUI_ID_FRAME_BillBoardID_BUTTON_BackOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_BillBoard, ID_BUTTON_Close, s_CUI_ID_FRAME_BillBoardID_BUTTON_CloseOnButtonClick );

	m_pID_FRAME_BillBoard = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_BillBoard );
	m_pID_BUTTON_Next = (ControlButton*)theUiManager.FindControl( ID_FRAME_BillBoard, ID_BUTTON_Next );
	m_pID_BUTTON_Back = (ControlButton*)theUiManager.FindControl( ID_FRAME_BillBoard, ID_BUTTON_Back );
	m_pID_BUTTON_Close = (ControlButton*)theUiManager.FindControl( ID_FRAME_BillBoard, ID_BUTTON_Close );
	m_pID_TEXT_Text = (ControlText*)theUiManager.FindControl( ID_FRAME_BillBoard, ID_TEXT_Text );

    m_pID_FRAME_BillBoard->SetOnVisibleChangedFun( BillBoard_OnVisibleChanged );

	assert( m_pID_FRAME_BillBoard );
	m_pID_FRAME_BillBoard->SetMsgHoldup(false);
	m_pID_FRAME_BillBoard->SetVisable( false );
	assert( m_pID_BUTTON_Close );
	assert( m_pID_TEXT_Text );
	return true;
	unguard;
}
// 卸载UI
bool CUI_ID_FRAME_BillBoard::_UnLoadUI()
{
	guardfunc;
	m_pID_FRAME_BillBoard = NULL;
	m_pID_BUTTON_Next = NULL;
	m_pID_BUTTON_Back = NULL;
	m_pID_BUTTON_Close = NULL;
	m_pID_TEXT_Text = NULL;
	return theUiManager.RemoveFrame( "data\\ui\\BillBoard.meui" );
	unguard
}
// 是否可视
bool CUI_ID_FRAME_BillBoard::_IsVisable()
{
	guardfunc;
	if(!m_pID_FRAME_BillBoard)
		return false;

	return m_pID_FRAME_BillBoard->IsVisable();
	unguard;
}
// 设置是否可视
void CUI_ID_FRAME_BillBoard::_SetVisable( const bool bVisable )
{
	guardfunc;
	if(m_pID_FRAME_BillBoard)
		m_pID_FRAME_BillBoard->SetVisable( bVisable );
	unguard;
}