/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Code\RunTime\CLIENT\Data\UI\InputBox.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "InputBox.h"
#include "FuncPerformanceLog.h"
#include "..\shortcutkey_configure.h"


CUI_InputBox s_CUI_InputBox;
MAP_FRAME_RUN( s_CUI_InputBox, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_InputBox, OnFrameRender )
MAP_EDIT_ENTER_CALLBACK( s_CUI_InputBox, ID_EDIT_INPUTOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_InputBox, ID_BUTTON_OKOnButtonClick );
MAP_BUTTON_CLICK_CALLBACK( s_CUI_InputBox, ID_BUTTON_CANCELOnButtonClick );
MAP_BUTTON_CLICK_CALLBACK( s_CUI_InputBox, ID_BUTTON_UPOnButtonClick );
MAP_BUTTON_CLICK_CALLBACK( s_CUI_InputBox, ID_BUTTON_DOWNOnButtonClick );

CUI_InputBox::CUI_InputBox()
{
	// SGuildMember
	m_pID_InputBox = NULL;
	m_pID_EDIT_INPUT = NULL;
	m_pID_TEXT_CAPTION = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_CANCEL = NULL;
	m_pID_BUTTON_UP = NULL;
	m_pID_BUTTON_DOWN = NULL;

	m_nMaxValue		= 99;
	m_nMinValue		= 1;
	m_pCurCallbackFun = NULL;
	m_pData = NULL;
}

// Frame
bool CUI_InputBox::OnFrameRun()
{
	guardfunc;
	return true;
	unguard;
}
bool CUI_InputBox::OnFrameRender()
{
	guardfunc;
	return true;
	unguard;
}
// Edit
void CUI_InputBox::ID_EDIT_INPUTOnEditEnter( ControlObject* pSender, const char* szData )
{
	guardfunc;
	if( !m_pID_InputBox )
		return;
	ID_BUTTON_OKOnButtonClick(NULL);
	unguard;
}
// Button
bool CUI_InputBox::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_InputBox )
		return false;

	if ( m_pCurCallbackFun )
	{
		m_pCurCallbackFun( m_pID_EDIT_INPUT->GetText(), m_pData );
	}
	if ( m_pData )
	{
		delete[] m_pData;
		m_pData = NULL;
	}
	if ( m_vtInputBox.size() > 0 )
	{
		m_vtInputBox.erase( m_vtInputBox.begin() );
	}
	Refeash();
	return true;
	unguard;
}
// Button
bool CUI_InputBox::ID_BUTTON_CANCELOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_InputBox )
		return false;

	if ( m_pData )
	{
		delete[] m_pData;
		m_pData = NULL;
	}
	if ( m_vtInputBox.size() > 0 )
	{
		m_vtInputBox.erase( m_vtInputBox.begin() );
	}
	Refeash();
	return true;
	unguard;
}
// Button
bool CUI_InputBox::ID_BUTTON_UPOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_InputBox )
		return false;
	INT nCnt = atoi( m_pID_EDIT_INPUT->GetText() );
	if(nCnt >= m_nMaxValue)
		return true;
	nCnt ++;
	m_pID_EDIT_INPUT->SetText( nCnt );
	return true;
	unguard;
}
// Button
bool CUI_InputBox::ID_BUTTON_DOWNOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_InputBox )
		return false;
	int number = 2;
	if (strlen(m_pID_EDIT_INPUT->GetText()) > 0)
		number = atoi(m_pID_EDIT_INPUT->GetText());
	if (number > m_nMinValue)
	{
		--number;
		m_pID_EDIT_INPUT->SetText(number);
	}
	return true;
}

static RECT InputBoxSrcRC;
static short InputBoxAlignMode;

void CUI_InputBox::InputBox_OnVisibleChanged(ControlObject* pSender)
{
	if (!s_CUI_InputBox.IsVisable())
	{
		s_CUI_InputBox.GetFrame()->GetData()->m_rcRealSize = InputBoxSrcRC;
		s_CUI_InputBox.GetFrame()->GetData()->m_nAlignMode = InputBoxAlignMode;
	}
}

// 装载UI
bool CUI_InputBox::_LoadUI()
{
     DWORD dwResult = 0;

    dwResult = theUiManager.AddFrame( "data\\ui\\InputBox.meui", true, UI_Render_LayerThree );

	
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[UI\\InputBox.UI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_InputBox::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_InputBox, s_CUI_InputBoxOnFrameRun );
	theUiManager.OnFrameRender( ID_InputBox, s_CUI_InputBoxOnFrameRender );
	theUiManager.OnEditEnter( ID_InputBox, ID_EDIT_INPUT, s_CUI_InputBoxID_EDIT_INPUTOnEditEnter );
	theUiManager.OnButtonClick( ID_InputBox, ID_BUTTON_OK, s_CUI_InputBoxID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_InputBox, ID_BUTTON_CANCEL, s_CUI_InputBoxID_BUTTON_CANCELOnButtonClick );
	theUiManager.OnButtonClick( ID_InputBox, ID_BUTTON_UP, s_CUI_InputBoxID_BUTTON_UPOnButtonClick );
	theUiManager.OnButtonClick( ID_InputBox, ID_BUTTON_DOWN, s_CUI_InputBoxID_BUTTON_DOWNOnButtonClick );

	m_pID_InputBox = (ControlFrame*)theUiManager.FindFrame( ID_InputBox );
	m_pID_EDIT_INPUT = (ControlEdit*)theUiManager.FindControl( ID_InputBox, ID_EDIT_INPUT );
	m_pID_TEXT_CAPTION = (ControlText*)theUiManager.FindControl( ID_InputBox, ID_TEXT_CAPTION );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_InputBox, ID_BUTTON_OK );
	m_pID_BUTTON_CANCEL = (ControlButton*)theUiManager.FindControl( ID_InputBox, ID_BUTTON_CANCEL );
	m_pID_BUTTON_UP = (ControlButton*)theUiManager.FindControl( ID_InputBox, ID_BUTTON_UP );
	m_pID_BUTTON_DOWN = (ControlButton*)theUiManager.FindControl( ID_InputBox, ID_BUTTON_DOWN );

	assert( m_pID_InputBox );
	m_pID_InputBox->SetMsgProcFun( InputBox_MsgProc );
	m_pID_InputBox->SetOnVisibleChangedFun(InputBox_OnVisibleChanged);
	InputBoxSrcRC = m_pID_InputBox->GetData()->m_rcRealSize;
	InputBoxAlignMode = m_pID_InputBox->GetData()->m_nAlignMode;
	assert( m_pID_EDIT_INPUT );
	assert( m_pID_TEXT_CAPTION );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_CANCEL );
	assert( m_pID_BUTTON_UP );
	assert( m_pID_BUTTON_DOWN );

	m_pID_EDIT_INPUT->SetIsNumber( true );
	m_pID_EDIT_INPUT->SetMaxLength( 2 );
	m_pID_EDIT_INPUT->SetNumberLimit(true, m_nMinValue, m_nMaxValue);
	m_pID_TEXT_CAPTION->SetVisable(false);

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_InputBox::_UnLoadUI()
{
	m_pID_InputBox = NULL;
	m_pID_EDIT_INPUT = NULL;
	m_pID_TEXT_CAPTION = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_CANCEL = NULL;
	m_pID_BUTTON_UP = NULL;
	m_pID_BUTTON_DOWN = NULL;
	return theUiManager.RemoveFrame( "data\\ui\\InputBox.meui" );
}
// 是否可视
bool CUI_InputBox::_IsVisable()
{
	guardfunc;
    if(!m_pID_InputBox)
        return false;
	return m_pID_InputBox->IsVisable();
	unguard;
}
// 设置是否可视
void CUI_InputBox::_SetVisable( const bool bVisable )
{
	guardfunc;
	if( !m_pID_InputBox )
		return;
	m_pID_InputBox->SetVisable( bVisable );

	theUiManager.ToTop( m_pID_InputBox );
	unguard;
}

void CUI_InputBox::Show( const char* szCaption, const bool bIsNumber,const bool bModal, 
			const funCallbackFun pFun, void *pData, const int nDataLength,const bool bIfPwd ,int nMaxLength )
{
	guardfunc;
	SetVisable( true );
	if( !m_pID_InputBox )
		return;
	S_InputBox stInputBox;
	stInputBox.m_strCaption = szCaption;
	stInputBox.m_pCallbackFun = pFun;
	stInputBox.m_bModal = bModal;
	stInputBox.m_bIsNumber = bIsNumber;
	stInputBox.m_bIsPassWord = bIfPwd;
	m_pID_EDIT_INPUT->SetMaxLength(nMaxLength);
	if ( pData && nDataLength > 0 )
	{
		stInputBox.m_pData = MeDefaultNew BYTE[nDataLength];
		memcpy( stInputBox.m_pData, pData, nDataLength );
	}
	m_vtInputBox.push_back( stInputBox );
	Refeash();
	if (!bIfPwd)
		s_CUI_InputBox.m_pID_EDIT_INPUT->SetText( 1 );
	unguard;
}

BOOL CUI_InputBox::EditInputIsVisable()
{
	guardfunc;
	if( !m_pID_InputBox )
		return FALSE;
	return m_pID_EDIT_INPUT->IsVisable();
	unguard;
}

void CUI_InputBox::Refeash()
{
	guardfunc;
	if ( m_vtInputBox.size() > 0 )
	{
		S_InputBox *pInputBox;
		pInputBox = &m_vtInputBox[0];
		*m_pID_TEXT_CAPTION = pInputBox->m_strCaption;
		*m_pID_EDIT_INPUT = "";
		m_pCurCallbackFun = pInputBox->m_pCallbackFun;
		m_pData = pInputBox->m_pData;
		if ( pInputBox->m_bModal == true )
		{
			m_pID_InputBox->SetArrayMode( ArrayMode_SingleModal );
		}
		else
		{
			m_pID_InputBox->SetArrayMode( ArrayMode_Normal );
		}
		if(!pInputBox->m_bIsNumber)
		{
			m_pID_BUTTON_UP->SetVisable(false);
			m_pID_BUTTON_DOWN->SetVisable(false);
		}
		m_pID_EDIT_INPUT->SetIsNumber( pInputBox->m_bIsNumber );
		m_pID_EDIT_INPUT->SetIsPassword( pInputBox->m_bIsPassWord );

		SetVisable( true );
		theUiManager.Compositor();
		m_pID_EDIT_INPUT->SetActivate();
	}
	else
	{
		SetVisable( false );
	}
	unguard;
}

bool CUI_InputBox::InputBox_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	guardfunc;
	if( !s_CUI_InputBox.IsVisable() )
		return false;

	switch( msg ) 
	{
	case WM_KEYUP:
		{
			if( wParam == VK_ESCAPE )	//cancle
			{
				s_CUI_InputBox.ID_BUTTON_CANCELOnButtonClick( NULL );
				return true;
			}
			else if( wParam == VK_RETURN )
			{
				s_CUI_InputBox.ID_BUTTON_OKOnButtonClick( NULL );
				return true;
			}
		}
		break;
	}
	return false;
	unguard;
}

void CUI_InputBox::SetMaxValue(int v)
{
	if( !m_pID_InputBox )
		return;
	m_nMaxValue = v;
	m_pID_EDIT_INPUT->SetNumberLimit(true, m_nMinValue, m_nMaxValue);
}

void CUI_InputBox::EditInput_SetText( int num )
{
	if( !m_pID_InputBox )
		return;
	m_pID_EDIT_INPUT->SetText(num);
}
