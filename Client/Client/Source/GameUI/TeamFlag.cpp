/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\����\�½��ļ��� (22)\TeamFlag.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "TeamFlag.h"

CUI_ID_FRAME_TeamFlag s_CUI_ID_FRAME_TeamFlag;
MAP_FRAME_RUN( s_CUI_ID_FRAME_TeamFlag, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_TeamFlag, OnFrameRender )
CUI_ID_FRAME_TeamFlag::CUI_ID_FRAME_TeamFlag()
{
	// Member
	m_pID_FRAME_TeamFlag = NULL;
	m_pID_PICTURE_flag = NULL;

}
// Frame
bool CUI_ID_FRAME_TeamFlag::OnFrameRun()
{
	//ÿ֡�����߼����£���Ҫ���жϽ����Ƿ�ɼ�������������
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_TeamFlag::OnFrameRender()
{
	return true;
}

// װ��UI
bool CUI_ID_FRAME_TeamFlag::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\TeamFlag.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("��ȡ�ļ�[Data\\UI\\TeamFlag.MEUI]ʧ��")
		return false;
	}
	return DoControlConnect();
}
// �����ؼ�
bool CUI_ID_FRAME_TeamFlag::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_TeamFlag, s_CUI_ID_FRAME_TeamFlagOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_TeamFlag, s_CUI_ID_FRAME_TeamFlagOnFrameRender );

	m_pID_FRAME_TeamFlag = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_TeamFlag );
	m_pID_PICTURE_flag = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TeamFlag, ID_PICTURE_flag );

	assert( m_pID_FRAME_TeamFlag );
	assert( m_pID_PICTURE_flag );

	SetVisable(false);
	return true;
}
// ж��UI
bool CUI_ID_FRAME_TeamFlag::_UnLoadUI()
{
	m_pID_FRAME_TeamFlag = NULL;
	m_pID_PICTURE_flag = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\TeamFlag.MEUI" );
}
// �Ƿ����
bool CUI_ID_FRAME_TeamFlag::_IsVisable()
{
	if ( !m_pID_FRAME_TeamFlag )
		return false;
	return m_pID_FRAME_TeamFlag->IsVisable();
}
// �����Ƿ����
void CUI_ID_FRAME_TeamFlag::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_TeamFlag )
		return;
	m_pID_FRAME_TeamFlag->SetVisable( bVisable );
}
