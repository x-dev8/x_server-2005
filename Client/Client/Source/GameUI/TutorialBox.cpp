/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\桌面\新建文件夹 (18)\新建文件夹 (6)\TutorialBox.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "PlayerRole.h"
#include "IntroductionManager.h"
#include "ScreenInfoManager.h"
#include "TutorialBox.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

CUI_ID_FRAME_TutorialBox s_CUI_ID_FRAME_TutorialBox;
MAP_FRAME_RUN( s_CUI_ID_FRAME_TutorialBox, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_TutorialBox, OnFrameRender )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_TutorialBox, ID_CHECKBOX_UpOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_TutorialBox, ID_CHECKBOX_DownOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_TutorialBox, ID_CHECKBOX_LeftOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_TutorialBox, ID_CHECKBOX_RightOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_TutorialBox, ID_CHECKBOX_MouseLeftOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_TutorialBox, ID_CHECKBOX_MouseRightOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_TutorialBox, ID_CHECKBOX_SpaceOnCheckBoxCheck )
CUI_ID_FRAME_TutorialBox::CUI_ID_FRAME_TutorialBox()
{
	// Member
	m_pID_FRAME_TutorialBox = NULL;
	m_pID_TEXT_CAPTION = NULL;
	m_pID_CHECKBOX_Up = NULL;
	m_pID_CHECKBOX_Down = NULL;
	m_pID_CHECKBOX_Left = NULL;
	m_pID_CHECKBOX_Right = NULL;
	m_pID_PICTURE_FangXiang = NULL;
	m_pID_CHECKBOX_MouseLeft = NULL;
	m_pID_CHECKBOX_MouseRight = NULL;
	m_pID_PICTURE_Mouse = NULL;
	m_pID_CHECKBOX_Space = NULL;
	m_pID_PICTURE_Space = NULL;
	m_pID_TEXT_Info = NULL;
	m_pID_TEXT_Mouse = NULL;
	m_pID_PICTURE_And = NULL;

	m_bUpPressed = false;
	m_bDowPressed = false;
	m_bLeftPressed = false;
	m_bRightPressed = false;

}

void CUI_ID_FRAME_TutorialBox::MovePair::Update( DWORD tic )
{
	if ( m_bFinished == false )
	{
		if( s_CUI_ID_FRAME_TutorialBox.m_pID_FRAME_TutorialBox != NULL )
		{
			if ( m_dwLastTic == 0 )
			{
				m_dwLastTic = tic;
			}
			
			float dt = ( tic - m_dwLastTic ) / 1000.0f;
			m_dwLastTic = tic;

			m_fElapse += dt;

			if ( m_fElapse >= m_fMoveTime )
			{
				m_bFinished = true;
				s_CUI_ID_FRAME_TutorialBox.m_pID_FRAME_TutorialBox->SetPos( m_fEndX, m_fEndY );
				if ( m_func )
				{
					(s_CUI_ID_FRAME_TutorialBox.*m_func)();
				}
				
			}
			else
			{
				s_CUI_ID_FRAME_TutorialBox.m_pID_FRAME_TutorialBox->SetPos( m_fStartX + m_fElapse / m_fMoveTime * ( m_fEndX - m_fStartX ) , m_fStartY + m_fElapse / m_fMoveTime * ( m_fEndY - m_fStartY ) );
			}
		}
	}

}
// Frame
bool CUI_ID_FRAME_TutorialBox::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	if( IsVisable() )
	{
		m_movePair.Update( HQ_TimeGetTime() );

		static DWORD lastT = HQ_TimeGetTime();
		DWORD curT = HQ_TimeGetTime();
		while ( curT > lastT && curT - lastT > 200 )
		{
			lastT += 200;
			if ( m_eTutorialType == T_MOVEPLAYER_UP )
			{
				m_pID_CHECKBOX_Up->SetCheck( !m_pID_CHECKBOX_Up->IsChecked() );
				//if ( m_bUpPressed == false )
				//{
				//	m_pID_CHECKBOX_Up->SetCheck( !m_pID_CHECKBOX_Up->IsChecked() );
				//}
				//else 
				//{
				//	m_pID_CHECKBOX_Up->SetCheck( false );
				//}
				//
				//if ( m_bDowPressed == false )
				//{
				//	m_pID_CHECKBOX_Down->SetCheck( !m_pID_CHECKBOX_Down->IsChecked() );
				//}
				//else
				//{
				//	m_pID_CHECKBOX_Down->SetCheck( false );
				//}
				//
				//if ( m_bLeftPressed == false )
				//{
				//	m_pID_CHECKBOX_Left->SetCheck( !m_pID_CHECKBOX_Left->IsChecked() );
				//}
				//else
				//{
				//	m_pID_CHECKBOX_Left->SetCheck( false );
				//}
				//
				//if ( m_bRightPressed == false )
				//{
				//	m_pID_CHECKBOX_Right->SetCheck( !m_pID_CHECKBOX_Right->IsChecked() );
				//}
				//else
				//{
				//	m_pID_CHECKBOX_Right->SetCheck(false);
				//}
				
				
				//if ( m_bDowPressed && m_bUpPressed && m_bLeftPressed && m_bRightPressed )
				//{
				//	thePlayerRole.SetFinishedIntroduce(INTRO_MOVEPLAYER);
				//	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PlayerGuide, theXmlString.GetString(eText_GuideFinishMovePlayer) );
				//	//接着测试左键
				//	//SetTutorialLMouseOpt();
				//	m_eTutorialType = T_MOUSELBUTTON_OPT;
				//	MoveInEffect();
				//	m_movePair.m_func = &CUI_ID_FRAME_TutorialBox::SetTutorialLMouseOpt;
				//}
				
			}
			else if ( m_eTutorialType == T_MOVEPLAYER_DOWN )
			{
				m_pID_CHECKBOX_Down->SetCheck( !m_pID_CHECKBOX_Down->IsChecked() );
			}
			else if ( m_eTutorialType == T_MOVEPLAYER_LEFT )
			{
				m_pID_CHECKBOX_MouseRight->SetCheck( !m_pID_CHECKBOX_MouseRight->IsChecked() );
				m_pID_CHECKBOX_Left->SetCheck( !m_pID_CHECKBOX_Left->IsChecked() );
			}
			else if ( m_eTutorialType == T_MOVEPLAYER_RIGHT )
			{
				m_pID_CHECKBOX_MouseRight->SetCheck( !m_pID_CHECKBOX_MouseRight->IsChecked() );
				m_pID_CHECKBOX_Right->SetCheck( !m_pID_CHECKBOX_Right->IsChecked() );
			}
			else if ( m_eTutorialType == T_MOUSELBUTTON_OPT )
			{
				m_pID_CHECKBOX_MouseLeft->SetCheck( !m_pID_CHECKBOX_MouseLeft->IsChecked() );
			}
			else if ( m_eTutorialType == T_MOUSERBUTTON_OPT )
			{
				m_pID_CHECKBOX_MouseRight->SetCheck( !m_pID_CHECKBOX_MouseRight->IsChecked() );
			}
			else if ( m_eTutorialType == T_SPACE_OPT )
			{
				m_pID_CHECKBOX_Space->SetCheck( !m_pID_CHECKBOX_Space->IsChecked() );
			}
		}
	}
	return true;
}
bool CUI_ID_FRAME_TutorialBox::OnFrameRender()
{

	return true;
}
// CheckBox
void CUI_ID_FRAME_TutorialBox::ID_CHECKBOX_UpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_TutorialBox )
		return;
}
// CheckBox
void CUI_ID_FRAME_TutorialBox::ID_CHECKBOX_DownOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_TutorialBox )
		return;
}
// CheckBox
void CUI_ID_FRAME_TutorialBox::ID_CHECKBOX_LeftOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_TutorialBox )
		return;
}
// CheckBox
void CUI_ID_FRAME_TutorialBox::ID_CHECKBOX_RightOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_TutorialBox )
		return;
}
// CheckBox
void CUI_ID_FRAME_TutorialBox::ID_CHECKBOX_MouseLeftOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_TutorialBox )
		return;
}
// CheckBox
void CUI_ID_FRAME_TutorialBox::ID_CHECKBOX_MouseRightOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_TutorialBox )
		return;
}
// CheckBox
void CUI_ID_FRAME_TutorialBox::ID_CHECKBOX_SpaceOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_TutorialBox )
		return;
}

// 装载UI
bool CUI_ID_FRAME_TutorialBox::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\TutorialBox.MEUI", true, UI_Render_LayerThree  );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\TutorialBox.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_TutorialBox::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_TutorialBox, s_CUI_ID_FRAME_TutorialBoxOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_TutorialBox, s_CUI_ID_FRAME_TutorialBoxOnFrameRender );
	theUiManager.OnCheckBoxCheck( ID_FRAME_TutorialBox, ID_CHECKBOX_Up, s_CUI_ID_FRAME_TutorialBoxID_CHECKBOX_UpOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_TutorialBox, ID_CHECKBOX_Down, s_CUI_ID_FRAME_TutorialBoxID_CHECKBOX_DownOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_TutorialBox, ID_CHECKBOX_Left, s_CUI_ID_FRAME_TutorialBoxID_CHECKBOX_LeftOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_TutorialBox, ID_CHECKBOX_Right, s_CUI_ID_FRAME_TutorialBoxID_CHECKBOX_RightOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_TutorialBox, ID_CHECKBOX_MouseLeft, s_CUI_ID_FRAME_TutorialBoxID_CHECKBOX_MouseLeftOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_TutorialBox, ID_CHECKBOX_MouseRight, s_CUI_ID_FRAME_TutorialBoxID_CHECKBOX_MouseRightOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_TutorialBox, ID_CHECKBOX_Space, s_CUI_ID_FRAME_TutorialBoxID_CHECKBOX_SpaceOnCheckBoxCheck );

	m_pID_FRAME_TutorialBox = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_TutorialBox );
	m_pID_TEXT_CAPTION = (ControlText*)theUiManager.FindControl( ID_FRAME_TutorialBox, ID_TEXT_CAPTION );
	m_pID_CHECKBOX_Up = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_TutorialBox, ID_CHECKBOX_Up );
	m_pID_CHECKBOX_Down = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_TutorialBox, ID_CHECKBOX_Down );
	m_pID_CHECKBOX_Left = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_TutorialBox, ID_CHECKBOX_Left );
	m_pID_CHECKBOX_Right = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_TutorialBox, ID_CHECKBOX_Right );
	m_pID_PICTURE_FangXiang = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TutorialBox, ID_PICTURE_FangXiang );
	m_pID_CHECKBOX_MouseLeft = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_TutorialBox, ID_CHECKBOX_MouseLeft );
	m_pID_CHECKBOX_MouseRight = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_TutorialBox, ID_CHECKBOX_MouseRight );
	m_pID_PICTURE_Mouse = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TutorialBox, ID_PICTURE_Mouse );
	m_pID_CHECKBOX_Space = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_TutorialBox, ID_CHECKBOX_Space );
	m_pID_PICTURE_Space = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TutorialBox, ID_PICTURE_Space );
	m_pID_TEXT_Info = (ControlText*)theUiManager.FindControl( ID_FRAME_TutorialBox, ID_TEXT_Info );
	m_pID_TEXT_Mouse = (ControlText*)theUiManager.FindControl( ID_FRAME_TutorialBox, ID_TEXT_Mouse );
	m_pID_PICTURE_And = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TutorialBox, ID_PICTURE_And );

	assert( m_pID_FRAME_TutorialBox );
	assert( m_pID_TEXT_CAPTION );
	assert( m_pID_CHECKBOX_Up );
	assert( m_pID_CHECKBOX_Down );
	assert( m_pID_CHECKBOX_Left );
	assert( m_pID_CHECKBOX_Right );
	assert( m_pID_PICTURE_FangXiang );
	assert( m_pID_CHECKBOX_MouseLeft );
	assert( m_pID_CHECKBOX_MouseRight );
	assert( m_pID_PICTURE_Mouse );
	assert( m_pID_CHECKBOX_Space );
	assert( m_pID_PICTURE_Space );
	assert( m_pID_TEXT_Info );
	assert( m_pID_TEXT_Mouse );
	assert( m_pID_PICTURE_And );
	m_pID_TEXT_Mouse->SetText("{#1043}");

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_TutorialBox::_UnLoadUI()
{
	m_pID_FRAME_TutorialBox = NULL;
	m_pID_TEXT_CAPTION = NULL;
	m_pID_CHECKBOX_Up = NULL;
	m_pID_CHECKBOX_Down = NULL;
	m_pID_CHECKBOX_Left = NULL;
	m_pID_CHECKBOX_Right = NULL;
	m_pID_PICTURE_FangXiang = NULL;
	m_pID_CHECKBOX_MouseLeft = NULL;
	m_pID_CHECKBOX_MouseRight = NULL;
	m_pID_PICTURE_Mouse = NULL;
	m_pID_CHECKBOX_Space = NULL;
	m_pID_PICTURE_Space = NULL;
	m_pID_TEXT_Info = NULL;
	m_pID_TEXT_Mouse = NULL;
	m_pID_PICTURE_And = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\TutorialBox.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_TutorialBox::_IsVisable()
{
	if ( !m_pID_FRAME_TutorialBox )
		return false;
	return m_pID_FRAME_TutorialBox->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_TutorialBox::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_TutorialBox )
		return;
	m_pID_FRAME_TutorialBox->SetVisable( bVisable );
}

bool VerifyNewPlayer(char bIsTell,void *pData )
{
	if ( bIsTell == 1 )
	{
		s_CUI_ID_FRAME_TutorialBox.SetVisable(true);
		s_CUI_ID_FRAME_TutorialBox.SetTutorialMovePlayer();
	}
	else
	{
		thePlayerRole.SetFinishedIntroduce(INTRO_MOVEPLAYER);
		thePlayerRole.SetFinishedIntroduce(INTRO_LMOUSEOPT);
		thePlayerRole.SetFinishedIntroduce(INTRO_RMOUSEOPT);
		thePlayerRole.SetFinishedIntroduce(INTRO_SPACEOPT);
	}
	return true;
}

void CUI_ID_FRAME_TutorialBox::StartTutorial()
{
	//s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_GuideIsNewPlayer), "", CUI_ID_FRAME_MessageBox::eTypeYesNo, true, VerifyNewPlayer );
	//this->SetVisable(false);

	//延时2s
	m_pID_FRAME_TutorialBox->SetPos( SCREEN_WIDTH + m_pID_FRAME_TutorialBox->GetWidth(), GetPosY() );

	int height = m_pID_FRAME_TutorialBox->GetHeight();
	int width = m_pID_FRAME_TutorialBox->GetWidth();

	m_movePair.m_fStartX = SCREEN_WIDTH + width;
	m_movePair.m_fStartY = GetPosY();
	m_movePair.m_fEndX = SCREEN_WIDTH + width;
	m_movePair.m_fEndY = GetPosY();
	m_movePair.m_bFinished = false;
	m_movePair.m_dwLastTic = 0;
	m_movePair.m_fMoveTime = 2.0f;
	m_movePair.m_fElapse = 0.0f;
	m_movePair.m_func = &CUI_ID_FRAME_TutorialBox::SetTutorialMovePlayerUp;//&CUI_ID_FRAME_TutorialBox::SetTutorialMovePlayer;

	SetVisable(true);
	//SetTutorialMovePlayer();
}

void CUI_ID_FRAME_TutorialBox::SetTutorialMovePlayer()
{
	//m_eTutorialType = T_MOVEPLAYER;
	HideAllButton();

	m_bUpPressed = false;
	m_bDowPressed = false;
	m_bLeftPressed = false;
	m_bRightPressed = false;

	m_pID_CHECKBOX_Up->SetVisable(true);
	m_pID_CHECKBOX_Down->SetVisable(true);
	m_pID_CHECKBOX_Left->SetVisable(true);
	m_pID_CHECKBOX_Right->SetVisable(true);
	m_pID_TEXT_Info->SetText(theXmlString.GetString(eText_GuideASDWMovePlayer));
	MoveOutEffect();
	m_movePair.m_func = NULL;
}

void CUI_ID_FRAME_TutorialBox::SetTutorialMovePlayerUp()
{
	m_eTutorialType = T_MOVEPLAYER_UP;
	HideAllButton();
	m_pID_CHECKBOX_Up->SetVisable(true);
	m_pID_TEXT_Info->SetText(theXmlString.GetString(eText_GuideMovePlayerUp));
	MoveOutEffect();
	m_movePair.m_func = NULL;
}

void CUI_ID_FRAME_TutorialBox::SetTutorialMovePlayerDown()
{
	m_eTutorialType = T_MOVEPLAYER_DOWN;
	HideAllButton();
	m_pID_CHECKBOX_Down->SetVisable(true);
	m_pID_TEXT_Info->SetText(theXmlString.GetString(eText_GuideMovePlayerDown));
	MoveOutEffect();
	m_movePair.m_func = NULL;
}

void CUI_ID_FRAME_TutorialBox::SetTutorialMovePlayerLeft()
{
	m_eTutorialType = T_MOVEPLAYER_LEFT;
	HideAllButton();
	m_pID_CHECKBOX_Left->SetVisable(true);
	m_pID_PICTURE_And->SetVisable(true);
	m_pID_CHECKBOX_MouseRight->SetVisable(true);
	//m_pID_TEXT_Mouse->SetVisable(true);
	//m_pID_TEXT_Mouse->SetText(theXmlString.GetString(eText_GIF_MouseRight));
	m_pID_TEXT_Info->SetText(theXmlString.GetString(eText_GuideMovePlayerLeft));
	MoveOutEffect();
	m_movePair.m_func = NULL;
}

void CUI_ID_FRAME_TutorialBox::SetTutorialMovePlayerRight()
{
	m_eTutorialType = T_MOVEPLAYER_RIGHT;
	HideAllButton();
	m_pID_CHECKBOX_Right->SetVisable(true);
	m_pID_PICTURE_And->SetVisable(true);
	m_pID_CHECKBOX_MouseRight->SetVisable(true);
	//m_pID_TEXT_Mouse->SetVisable(true);
	//m_pID_TEXT_Mouse->SetText(theXmlString.GetString(eText_GIF_MouseRight));
	m_pID_TEXT_Info->SetText(theXmlString.GetString(eText_GuideMovePlayerRight));
	MoveOutEffect();
	m_movePair.m_func = NULL;
}

void CUI_ID_FRAME_TutorialBox::SetTutorialLMouseOpt()
{
	m_eTutorialType = T_MOUSELBUTTON_OPT;
	HideAllButton();
	m_pID_CHECKBOX_MouseLeft->SetVisable(true);
	//m_pID_TEXT_Mouse->SetVisable(true);
	//m_pID_TEXT_Mouse->SetText(theXmlString.GetString(eText_GIF_MouseLeft));
	m_pID_TEXT_Info->SetText(theXmlString.GetString(eText_GuideClickMovePlayer));
	MoveOutEffect();
	m_movePair.m_func = NULL;
}

void CUI_ID_FRAME_TutorialBox::SetTutorialRMouseOpt()
{
	m_eTutorialType = T_MOUSERBUTTON_OPT;
	HideAllButton();
	m_pID_CHECKBOX_MouseRight->SetVisable(true);
	//m_pID_TEXT_Mouse->SetVisable(true);
	//m_pID_TEXT_Mouse->SetText(theXmlString.GetString(eText_GIF_MouseRight));
	m_pID_TEXT_Info->SetText(theXmlString.GetString(eText_GuideRMouseRote));
	MoveOutEffect();
	m_movePair.m_func = NULL;
}

void CUI_ID_FRAME_TutorialBox::SetTutorialSapceOpt()
{
	m_eTutorialType = T_SPACE_OPT;
	HideAllButton();
	m_pID_CHECKBOX_Space->SetVisable(true);
	m_pID_TEXT_Info->SetText(theXmlString.GetString(eText_GuideSpaceJump));

	MoveOutEffect();
	m_movePair.m_func = NULL;
}

void CUI_ID_FRAME_TutorialBox::OnMovePlayerUp()
{
	if ( !IsVisable() || m_eTutorialType != T_MOVEPLAYER_UP )
	{
		return;
	}
	m_bUpPressed = true;
	thePlayerRole.SetFinishedIntroduce(INTRO_MOVEPLAYER_UP);
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PlayerGuide, theXmlString.GetString(eText_GuideFinishMovePlayerUp) );
	m_eTutorialType = T_MOVEPLAYER_DOWN;
	MoveInEffect();
	m_movePair.m_func = &CUI_ID_FRAME_TutorialBox::SetTutorialMovePlayerDown;
}

void CUI_ID_FRAME_TutorialBox::OnMovePlayerDown()
{
	if ( !IsVisable() || m_eTutorialType != T_MOVEPLAYER_DOWN )
	{
		return;
	}
	m_bDowPressed = true;
	thePlayerRole.SetFinishedIntroduce(INTRO_MOVEPLAYER_DOWN);
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PlayerGuide, theXmlString.GetString(eText_GuideFinishMovePlayerDown) );
	m_eTutorialType = T_MOVEPLAYER_LEFT;
	MoveInEffect();
	m_movePair.m_func = &CUI_ID_FRAME_TutorialBox::SetTutorialMovePlayerLeft;
}

void CUI_ID_FRAME_TutorialBox::OnMovePlayerLeft()
{
	if ( !IsVisable() || m_eTutorialType != T_MOVEPLAYER_LEFT )
	{
		return;
	}
	m_bLeftPressed = true;
	thePlayerRole.SetFinishedIntroduce(INTRO_MOVEPLAYER_LEFT);
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PlayerGuide, theXmlString.GetString(eText_GuideFinishMovePlayerLeft) );
	m_eTutorialType = T_MOVEPLAYER_RIGHT;
	MoveInEffect();
	m_movePair.m_func = &CUI_ID_FRAME_TutorialBox::SetTutorialMovePlayerRight;
}

void CUI_ID_FRAME_TutorialBox::OnMovePlayerRight()
{
	if ( !IsVisable() || m_eTutorialType != T_MOVEPLAYER_RIGHT )
	{
		return;
	}
	m_bRightPressed = true;
	thePlayerRole.SetFinishedIntroduce(INTRO_MOVEPLAYER_RIGHT);
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PlayerGuide, theXmlString.GetString(eText_GuideFinishMovePlayerRight) );
	m_eTutorialType = T_MOUSELBUTTON_OPT;
	MoveInEffect();
	m_movePair.m_func = &CUI_ID_FRAME_TutorialBox::SetTutorialLMouseOpt;
}

void CUI_ID_FRAME_TutorialBox::OnLMouseButton()
{
	if ( !IsVisable() || m_eTutorialType != T_MOUSELBUTTON_OPT )
	{
		return;
	}
	thePlayerRole.SetFinishedIntroduce(INTRO_LMOUSEOPT);
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PlayerGuide, theXmlString.GetString(eText_GuideFinishLMouseOpt) );
	//接着测试右键
	//SetTutorialRMouseOpt();
	m_eTutorialType = T_MOUSERBUTTON_OPT;
	MoveInEffect();
	m_movePair.m_func = &CUI_ID_FRAME_TutorialBox::SetTutorialRMouseOpt;
}

void CUI_ID_FRAME_TutorialBox::OnRMouseButton()
{
	if ( !IsVisable() || m_eTutorialType != T_MOUSERBUTTON_OPT )
	{
		return;
	}
	thePlayerRole.SetFinishedIntroduce(INTRO_RMOUSEOPT);
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PlayerGuide, theXmlString.GetString(eText_GuideFinishRMouseOpt) );
	//接着测试空格键跳跃
	//SetTutorialSapceOpt();
	m_eTutorialType = T_SPACE_OPT;
	MoveInEffect();
	m_movePair.m_func = &CUI_ID_FRAME_TutorialBox::SetTutorialSapceOpt;
}

void CUI_ID_FRAME_TutorialBox::OnSapcePress()
{
	if ( !IsVisable() || m_eTutorialType != T_SPACE_OPT )
	{
		return;
	}
	thePlayerRole.SetFinishedIntroduce(INTRO_SPACEOPT);
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PlayerGuide, theXmlString.GetString(eText_GuideFinishSpaceOpt) );
	//教程结束
	//this->SetVisable(false);
	m_eTutorialType = T_MAX;
	MoveInEffect();
	m_movePair.m_func = NULL;
}

void CUI_ID_FRAME_TutorialBox::HideAllButton()
{
	m_pID_CHECKBOX_Up->SetVisable(false);
	m_pID_CHECKBOX_Down->SetVisable(false);
	m_pID_CHECKBOX_Left->SetVisable(false);
	m_pID_CHECKBOX_Right->SetVisable(false);

	m_pID_CHECKBOX_MouseLeft->SetVisable(false);
	m_pID_CHECKBOX_MouseRight->SetVisable(false);
	m_pID_CHECKBOX_Space->SetVisable(false);
	m_pID_TEXT_Mouse->SetVisable(false);
	m_pID_PICTURE_And->SetVisable(false);
}

void CUI_ID_FRAME_TutorialBox::MoveOutEffect()
{
	int height = m_pID_FRAME_TutorialBox->GetHeight();
	int width = m_pID_FRAME_TutorialBox->GetWidth();

	m_movePair.m_fStartX = SCREEN_WIDTH + width;
	m_movePair.m_fStartY = GetPosY();
	m_movePair.m_fEndX = ( SCREEN_WIDTH - width ) / 2;
	m_movePair.m_fEndY = GetPosY();
	m_movePair.m_bFinished = false;
	m_movePair.m_dwLastTic = 0;
	m_movePair.m_fMoveTime = 0.5f;
	m_movePair.m_fElapse = 0.0f;
}

void CUI_ID_FRAME_TutorialBox::MoveInEffect()
{
	int height = m_pID_FRAME_TutorialBox->GetHeight();
	int width = m_pID_FRAME_TutorialBox->GetWidth();

	m_movePair.m_fStartX = ( SCREEN_WIDTH - width ) / 2;
	m_movePair.m_fStartY = GetPosY();
	m_movePair.m_fEndX = SCREEN_WIDTH + width;
	m_movePair.m_fEndY = GetPosY();
	m_movePair.m_bFinished = false;
	m_movePair.m_dwLastTic = 0;
	m_movePair.m_fMoveTime = 0.5f;
	m_movePair.m_fElapse = 0.0f;
}

int CUI_ID_FRAME_TutorialBox::GetPosY()
{
	if ( m_pID_FRAME_TutorialBox )
	{
		RECT rc;
		m_pID_FRAME_TutorialBox->GetRealRect( &rc );
		return rc.top;
	}
	
	return 0;
}