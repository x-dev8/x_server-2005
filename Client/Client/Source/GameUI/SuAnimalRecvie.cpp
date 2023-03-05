/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\SuAnimalRecvie.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SuAnimalRecvie.h"
#include "SuAnimal.h"
#include "PlayerRole.h"
CUI_ID_FRAME_SuAnimalRecvie s_CUI_ID_FRAME_SuAnimalRecvie;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SuAnimalRecvie, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SuAnimalRecvie, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalRecvie, ID_BUTTON_RecvieOnButtonClick )
CUI_ID_FRAME_SuAnimalRecvie::CUI_ID_FRAME_SuAnimalRecvie()
{
	// Member
	m_pID_FRAME_SuAnimalRecvie = NULL;
	m_pID_BUTTON_Recvie = NULL;
}
// Frame
bool CUI_ID_FRAME_SuAnimalRecvie::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_SuAnimalRecvie::OnFrameRender()
{
	/*if(thePlayerRole.GetActivedPet())
		m_pID_FRAME_SuAnimalRecvie->SetVisable(false);*/
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalRecvie::ID_BUTTON_RecvieOnButtonClick( ControlObject* pSender )
{
	s_CUI_ID_FRAME_SuAnimal.LoadUI();
	s_CUI_ID_FRAME_SuAnimal.ReviceSuAnimal();
	return true;
}
void CUI_ID_FRAME_SuAnimalRecvie::InitializeAtEnterWorld()
{
	LoadUI();
}
	// 装载UI
bool CUI_ID_FRAME_SuAnimalRecvie::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SuAnimalRecvie.MEUI",true);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SuAnimalRecvie.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SuAnimalRecvie::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SuAnimalRecvie, s_CUI_ID_FRAME_SuAnimalRecvieOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SuAnimalRecvie, s_CUI_ID_FRAME_SuAnimalRecvieOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimalRecvie, ID_BUTTON_Recvie, s_CUI_ID_FRAME_SuAnimalRecvieID_BUTTON_RecvieOnButtonClick );

	m_pID_FRAME_SuAnimalRecvie = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SuAnimalRecvie );
	m_pID_BUTTON_Recvie = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimalRecvie, ID_BUTTON_Recvie );
	assert( m_pID_FRAME_SuAnimalRecvie );
	assert( m_pID_BUTTON_Recvie );

	m_pID_FRAME_SuAnimalRecvie->SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_SuAnimalRecvie::_UnLoadUI()
{
	m_pID_FRAME_SuAnimalRecvie = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\SuAnimalRecvie.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_SuAnimalRecvie::_IsVisable()
{
	if(!m_pID_FRAME_SuAnimalRecvie)
		return false;
	return m_pID_FRAME_SuAnimalRecvie->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SuAnimalRecvie::_SetVisable( const bool bVisable )
{	
	m_pID_FRAME_SuAnimalRecvie->SetVisable( bVisable );
}
