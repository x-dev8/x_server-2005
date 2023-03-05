#include <assert.h>
#include "MeUi/UiManager.h"
#include "Only.h"
#include "NetworkInput.h"
#include "MessageDefine.h"

CUI_ID_FRAME_Only s_CUI_ID_FRAME_Only;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Only, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Only, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Only, ID_BUTTON_OnlyOnButtonClick )
CUI_ID_FRAME_Only::CUI_ID_FRAME_Only()
{
	// Member
	m_pID_FRAME_Only = NULL;
	m_pID_BUTTON_Only = NULL;

}

// Frame
bool CUI_ID_FRAME_Only::OnFrameRun()
{
	return true;
}

bool CUI_ID_FRAME_Only::OnFrameRender()
{
	return true;
}

// Button
bool CUI_ID_FRAME_Only::ID_BUTTON_OnlyOnButtonClick( ControlObject* pSender )
{
	MsgReqOffNpcShip msg;
	GettheNetworkInput().SendMsg(&msg);
	return true;
}

// װ��UI
bool CUI_ID_FRAME_Only::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Only.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("��ȡ�ļ�[Data\\UI\\Only.MEUI]ʧ��")
			return false;
	}
	return DoControlConnect();
}

// �����ؼ�
bool CUI_ID_FRAME_Only::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Only, s_CUI_ID_FRAME_OnlyOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Only, s_CUI_ID_FRAME_OnlyOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_Only, ID_BUTTON_Only, s_CUI_ID_FRAME_OnlyID_BUTTON_OnlyOnButtonClick );

	m_pID_FRAME_Only = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Only );
	m_pID_BUTTON_Only = (ControlButton*)theUiManager.FindControl( ID_FRAME_Only, ID_BUTTON_Only );
	assert( m_pID_FRAME_Only );
	assert( m_pID_BUTTON_Only );
	return true;
}

// ж��UI
bool CUI_ID_FRAME_Only::_UnLoadUI()
{
	m_pID_FRAME_Only = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\Only.MEUI" );
}

// �Ƿ����
bool CUI_ID_FRAME_Only::_IsVisable()
{
	if(!m_pID_FRAME_Only)
		return false;

	return m_pID_FRAME_Only->IsVisable();
}

// �����Ƿ����
void CUI_ID_FRAME_Only::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_Only)
		return;

	m_pID_FRAME_Only->SetVisable( bVisable );
}
