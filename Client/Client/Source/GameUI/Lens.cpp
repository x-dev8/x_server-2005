/********************************************************************
	Created by UIEditor.exe
	FileName: E:\ShenWang\Turbo\Program\trunk\Bin\Client\Data\Ui\Lens.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Lens.h"
#include "GameMain.h"

CUI_ID_FRAME_Lens s_CUI_ID_FRAME_Lens;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Lens, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Lens, OnFrameRender )
CUI_ID_FRAME_Lens::CUI_ID_FRAME_Lens()
{
	// Member
	m_pID_FRAME_Lens = NULL;
	m_pID_PROGRESS_Up1 = NULL;
	m_pID_PROGRESS_Down1 = NULL;
	m_pID_PROGRESS_Up2 = NULL;
	m_pID_PROGRESS_Down2 = NULL;
	m_pID_PICTURE_Up = NULL;
	m_pID_PICTURE_Down = NULL;

	m_dwScreenTimeBegin = 0;
	m_dwScreenTime = 0;
}

// Frame
bool CUI_ID_FRAME_Lens::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}

	ProcessUIShowOrHide();
	return true;
}

bool CUI_ID_FRAME_Lens::OnFrameRender()
{
    ShowMoviceUpAndDown();
    ProcessScreenPlay();
	return true;
}

// 装载UI
bool CUI_ID_FRAME_Lens::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Lens.MEUI", false,  UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Lens.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}

// 关连控件
bool CUI_ID_FRAME_Lens::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Lens, s_CUI_ID_FRAME_LensOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Lens, s_CUI_ID_FRAME_LensOnFrameRender );

	m_pID_FRAME_Lens = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Lens );
	m_pID_PROGRESS_Up1 = (ControlProgress*)theUiManager.FindControl( ID_FRAME_Lens, ID_PROGRESS_Up1 );
	m_pID_PROGRESS_Down1 = (ControlProgress*)theUiManager.FindControl( ID_FRAME_Lens, ID_PROGRESS_Down1 );
	m_pID_PROGRESS_Up2 = (ControlProgress*)theUiManager.FindControl( ID_FRAME_Lens, ID_PROGRESS_Up2 );
	m_pID_PROGRESS_Down2 = (ControlProgress*)theUiManager.FindControl( ID_FRAME_Lens, ID_PROGRESS_Down2 );
	m_pID_PICTURE_Up = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Lens, ID_PICTURE_Up );
	m_pID_PICTURE_Down = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Lens, ID_PICTURE_Down );

	assert( m_pID_FRAME_Lens );
	assert( m_pID_PROGRESS_Up1 );
	assert( m_pID_PROGRESS_Down1 );
	assert( m_pID_PROGRESS_Up2 );
	assert( m_pID_PROGRESS_Down2 );
	assert( m_pID_PICTURE_Up );
	assert( m_pID_PICTURE_Down );

	ModifyWAndH();

	m_pID_FRAME_Lens->enableEscKey( false );
	m_pID_FRAME_Lens->SetOnEscResponseType( ControlFrame::EscResponse_SkipMe );

	m_pID_FRAME_Lens->SetMsgHoldup(false);
	_SetVisable(false);
	return true;
}

// 卸载UI
bool CUI_ID_FRAME_Lens::_UnLoadUI()
{
	m_pID_FRAME_Lens = NULL;
	m_pID_PROGRESS_Up1 = NULL;
	m_pID_PROGRESS_Down1 = NULL;
	m_pID_PROGRESS_Up2 = NULL;
	m_pID_PROGRESS_Down2 = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\Lens.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_Lens::_IsVisable()
{
	if ( !m_pID_FRAME_Lens )
		return false;
	return m_pID_FRAME_Lens->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_Lens::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_Lens )
		return;

	m_pID_FRAME_Lens->SetVisable( bVisable );

	theUiManager.ToTop(m_pID_FRAME_Lens);
	m_bAning = false;
	m_dwScreenTimeBegin = 0;
	m_dwScreenTime = 0;
}

void CUI_ID_FRAME_Lens::BeginAnim()
{
	if(!m_pID_FRAME_Lens)
		return;

	m_pID_PROGRESS_Up2->SetVisable(false);
	m_pID_PROGRESS_Down2->SetVisable(false);

	m_pID_PROGRESS_Up1->SetVisable(true);
	m_pID_PROGRESS_Down1->SetVisable(true);

	m_pID_PROGRESS_Up1->RestartAnimation();
	m_pID_PROGRESS_Down1->RestartAnimation();


	m_pID_PICTURE_Up->SetVisable(false);
	m_pID_PICTURE_Down->SetVisable(false);

	m_bAning = true;

	GetUIScriptMgr()->ProcessUiShowOrHide(false,this);
}

void CUI_ID_FRAME_Lens::EndAnim()
{
	if(!m_pID_FRAME_Lens)
		return;

	m_pID_PROGRESS_Up1->SetVisable(false);
	m_pID_PROGRESS_Down1->SetVisable(false);
	 	
	m_pID_PROGRESS_Up2->SetVisable(true);
	m_pID_PROGRESS_Down2->SetVisable(true);

	m_pID_PICTURE_Up->SetVisable(false);
	m_pID_PICTURE_Down->SetVisable(false);

	m_pID_PROGRESS_Up2->RestartAnimation();
	m_pID_PROGRESS_Down2->RestartAnimation();

	BeginTime();
}

void CUI_ID_FRAME_Lens::ResetDevice()
{
	if(!m_pID_FRAME_Lens)
		return;

	ModifyWAndH();
}

void CUI_ID_FRAME_Lens::ModifyWAndH()
{
	if(!m_pID_FRAME_Lens)
		return;

	m_pID_FRAME_Lens->SetWidth(SCREEN_WIDTH);
	m_pID_FRAME_Lens->SetHeight(SCREEN_HEIGHT);

	m_pID_PICTURE_Up->SetWidth(SCREEN_WIDTH);
	m_pID_PICTURE_Down->SetWidth(SCREEN_WIDTH);

	m_pID_PROGRESS_Up1->SetWidth(SCREEN_WIDTH);
	m_pID_PROGRESS_Down1->SetWidth(SCREEN_WIDTH);

	m_pID_PROGRESS_Up2->SetWidth(SCREEN_WIDTH);
	m_pID_PROGRESS_Down2->SetWidth(SCREEN_WIDTH);
}

bool CUI_ID_FRAME_Lens::IsTimeOver()
{
	if(!m_pID_FRAME_Lens)
		return false;

	static DWORD dwElapse = 1500;

	return HQ_TimeGetTime() - m_dwBeginTime > dwElapse;
}

void CUI_ID_FRAME_Lens::BeginTime()
{
	m_dwBeginTime = HQ_TimeGetTime();
	m_bTiming = true;
}

void CUI_ID_FRAME_Lens::ProcessUIShowOrHide()
{
	if(!m_pID_FRAME_Lens)
		return;

	if(!m_bTiming)
		return;

	if(!IsTimeOver())
		return;

	m_bTiming = false;
	SetVisable(false);
	GetUIScriptMgr()->ProcessUiShowOrHide(true,this);
	return;
}

void CUI_ID_FRAME_Lens::ShowMoviceUpAndDown()
{
	if(!m_pID_FRAME_Lens)
		return;

	if(!m_bAning)
		return;

	if(!m_pID_PROGRESS_Up1->IsAnimationStop())
		return;

	m_pID_PICTURE_Up->SetVisable(true);
	m_pID_PICTURE_Down->SetVisable(true);

	m_bAning = false;
}

void CUI_ID_FRAME_Lens::SetScreenPlay(DWORD dwTime)
{
	SetVisable(true);
	m_dwScreenTimeBegin = HQ_TimeGetTime();
	m_dwScreenTime      = dwTime;
	BeginAnim();
}

void CUI_ID_FRAME_Lens::ProcessScreenPlay()
{
	if(m_dwScreenTime == 0)
		return;

	if(HQ_TimeGetTime() - m_dwScreenTimeBegin < m_dwScreenTime)
		return;

	EndAnim();
	m_dwScreenTime = 0;
	return;
}
