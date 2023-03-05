/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\ChangeName.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ChangeName.h"
#include "MessageDefine.h"
#include "NetworkInput.h"
#include "Select.h"
#include "chatcheck.h"
#include "XmlStringLanguage.h"
#include "Create.h"
#include "GameMain.h"

CUI_ID_FRAME_ChangeName s_CUI_ID_FRAME_ChangeName;

MAP_FRAME_RUN( s_CUI_ID_FRAME_ChangeName, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ChangeName, OnFrameRender )

MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ChangeName, ID_BUTTON_OKOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_ChangeName, ID_EDIT_NameOnEditEnter )

CUI_ID_FRAME_ChangeName::CUI_ID_FRAME_ChangeName()
{
	// Member
	m_pID_FRAME_ChangeName = NULL;
	m_pID_EDIT_Name = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_TEXT_Info = NULL;
}
CUI_ID_FRAME_ChangeName::~CUI_ID_FRAME_ChangeName()
{
}
// Frame
bool CUI_ID_FRAME_ChangeName::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_ChangeName::OnFrameRender()
{
	return true;
}
void CUI_ID_FRAME_ChangeName::ID_EDIT_NameOnEditEnter( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_ChangeName )
		return;
}
// Button
bool CUI_ID_FRAME_ChangeName::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ChangeName)
		return false;
	string Name = m_pID_EDIT_Name->GetText();
	if(Name.empty())
	{
		//��ʾ������Ʋ�����Ϊ��
		return true;
	}
	//1.�����ƽ��л����Ĺ���
	if(!CChatCheck::getInstance()->CheckStringInLow(Name.c_str()))
	{
		//�����ιؼ���

		return true;
	}
	//�����ƽ��й��� ����������������˽����ж�
	MsgNewChangeNameReq msg;
	memcpy(msg.szName, Name.c_str(), Name.length());
	msg.szName[Name.length()] = 0;
	msg.PlayerID = s_CUI_ID_FRAME_Select.GetCurSelectPlayerID();//���ID
	GettheNetworkInput().SendMsg( &msg );

	m_pID_EDIT_Name->SetEnable(false);
	m_pID_BUTTON_OK->SetEnable(false);
	//�ȴ�������������Ϣ
	return true;
}

// װ��UI
void CUI_ID_FRAME_ChangeName::Clear()
{
	if(m_pID_EDIT_Name)
		m_pID_EDIT_Name->SetText("");
}
bool CUI_ID_FRAME_ChangeName::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ChangeName.meui",false,UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("��ȡ�ļ�[Data\\UI\\ChangeName.meui]ʧ��")
		return false;
	}
	return DoControlConnect();
}
// �����ؼ�
bool CUI_ID_FRAME_ChangeName::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_ChangeName, s_CUI_ID_FRAME_ChangeNameOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ChangeName, s_CUI_ID_FRAME_ChangeNameOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_ChangeName, ID_BUTTON_OK, s_CUI_ID_FRAME_ChangeNameID_BUTTON_OKOnButtonClick );
	theUiManager.OnEditEnter( ID_FRAME_ChangeName, ID_EDIT_Name, s_CUI_ID_FRAME_ChangeNameID_EDIT_NameOnEditEnter );


	m_pID_FRAME_ChangeName = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ChangeName );
	m_pID_EDIT_Name = (ControlEdit*)theUiManager.FindControl( ID_FRAME_ChangeName, ID_EDIT_Name );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_ChangeName, ID_BUTTON_OK );
	m_pID_TEXT_Info = (ControlText*)theUiManager.FindControl( ID_FRAME_ChangeName, ID_TEXT_Info );
	assert( m_pID_FRAME_ChangeName );
	assert( m_pID_EDIT_Name );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_TEXT_Info );

	if( !s_CUI_ID_FRAME_CREATE.GetImeInstance() )
		s_CUI_ID_FRAME_CREATE.SetImeInstance( ImmGetContext( g_hWnd ) );
	ImmReleaseContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );

	return true;
}
// ж��UI
bool CUI_ID_FRAME_ChangeName::_UnLoadUI()
{
	return theUiManager.RemoveFrame( "Data\\UI\\ChangeName.meui" );
}
// �Ƿ����
bool CUI_ID_FRAME_ChangeName::_IsVisable()
{
	return m_pID_FRAME_ChangeName->IsVisable();
}
// �����Ƿ����
void CUI_ID_FRAME_ChangeName::_SetVisable( const bool bVisable )
{
	if(bVisable)
		ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );
	else
		ImmAssociateContext( g_hWnd, NULL );
	m_pID_FRAME_ChangeName->SetVisable( bVisable );
}
void CUI_ID_FRAME_ChangeName::OnChangeNameAck(bool Result)
{
	if(Result)
	{
		s_CUI_ID_FRAME_Select.ChangeName();
		SetVisable(false);//����UI
		m_pID_TEXT_Info->SetText("");
	}
	else
	{
		//��ʾ������Ʋ�����ʹ��
		//����Ҽ�������
		m_pID_EDIT_Name->SetText("");
		m_pID_TEXT_Info->SetText(theXmlString.GetString( eText_RoleChangeName_Error ));
	}
	m_pID_EDIT_Name->SetEnable(true);
	m_pID_BUTTON_OK->SetEnable(true);
}
string CUI_ID_FRAME_ChangeName::GetTextName()
{
	return m_pID_EDIT_Name->GetText();
}