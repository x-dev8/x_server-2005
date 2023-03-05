/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Code\RunTime\CLIENT\Data\UI\Progress.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Progress.h"
#include "FuncPerformanceLog.h"
#include "SystemConfig.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "../Player.h"

CUI_Progress s_CUI_Progress;
MAP_FRAME_RUN( s_CUI_Progress, ProgressOnFrameRun )
MAP_FRAME_RENDER( s_CUI_Progress, ProgressOnFrameRender )

CUI_Progress::CUI_Progress()
{
	// SGuildMember
	m_pProgress = NULL;
	m_pID_PROGRESS = NULL;
	m_pID_CASTINGBAR_BORDER = NULL;
	m_pID_CASTINGBAR_Full = NULL;
	m_pID_CASTINGBAR_Intermit = NULL;
	m_pID_Text_Name = NULL;

	m_enShowType = Type_Normal;
	m_nFlashCount = 0;
	m_bAutoClose = FALSE;
	m_bFadeIn = FALSE;
	m_dwStartTime = 0;
	m_dwPeriod = 0;
	m_bUp = TRUE;
	m_bProgressComplete = FALSE;			//进度完成
	m_bIsInterrupt = FALSE;					//是中断吗？
	m_bClientCompletedDisappear = FALSE;	//客户端进度完成后就消失
}

bool CUI_Progress::IsInterrupt()
{
	guardfunc;
	return m_bIsInterrupt;
	unguard;
}

void CUI_Progress::BackupPeriodTime( int nBackupPercent )
{
	guardfunc;
	if( !m_pProgress )
		return;
	m_dwStartTime += m_dwPeriod*nBackupPercent/100;

	if( m_dwStartTime > HQ_TimeGetTime() )
		m_dwStartTime = HQ_TimeGetTime();
	unguard;
}

void CUI_Progress::SetProgressComplete()
{
	guardfunc;
	m_bProgressComplete = TRUE;
	if( m_pID_CASTINGBAR_Full )
		m_pID_CASTINGBAR_Full->SetVisable( true );
	if( m_pID_CASTINGBAR_Intermit )
		m_pID_CASTINGBAR_Intermit->SetVisable( false );

	if( m_pID_CASTINGBAR_BORDER )
		m_pID_CASTINGBAR_BORDER->SetVisable( false );
	unguard;
}

// Frame
bool CUI_Progress::ProgressOnFrameRun()
{
	guardfunc;
	if ( m_bAutoClose == TRUE && m_enShowType != Type_Normal)
	{
		if ( m_bUp == TRUE )
		{
			int nValue = (HQ_TimeGetTime() - m_dwStartTime)*1000/m_dwPeriod;

			if( nValue >= 1000 && HQ_TimeGetTime() - m_dwStartTime > m_dwPeriod + 6000 )
			{
				m_pProgress->SetVisable( false);
// 				m_pID_CASTINGBAR_BORDER->SetVisable( false);
// 				m_pID_Text_Name->SetVisable( false, true );
// 				m_pID_PROGRESS->SetVisable( false, true );

				m_enShowType = Type_Normal;
			}

			if( ( m_bProgressComplete || ( m_bClientCompletedDisappear && nValue >= 1000 ) ) )
			{
				m_pProgress->SetVisable( false);
// 				m_pID_CASTINGBAR_BORDER->SetVisable( false, true );
// 				m_pID_Text_Name->SetVisable( false, true );
// 				m_pID_PROGRESS->SetVisable( false, true );
				if (m_bClientCompletedDisappear)
				{
					if (m_pID_CASTINGBAR_Full)
					{
						m_pID_CASTINGBAR_Full -> SetVisable(true);
					}
					if (m_pID_CASTINGBAR_BORDER)
					{
						m_pID_CASTINGBAR_BORDER -> SetVisable(false);
					}
				}
				
				
				m_enShowType = Type_Normal;
				return true;
			}
		}
		else
		{
			if( m_pID_PROGRESS->GetValue() <= 0 )
			{
#ifdef _DEBUG
				OutputDebugString("m_pID_PROGRESS->GetValue() <= 0\n");
#endif

				m_pProgress->SetVisable( false);
// 				m_pID_CASTINGBAR_BORDER->SetVisable( false, true );
// 				m_pID_Text_Name->SetVisable( false, true );
// 				m_pID_PROGRESS->SetVisable( false, true );

				m_enShowType = Type_Normal;
				return true;
			}
		}
	}

	switch( m_enShowType ) 
	{
	case Type_Time:
		{
			if( m_dwPeriod == 0 )
			{
				m_dwPeriod = 1;
			}

			if ( m_bUp == TRUE )
			{
				if( m_bIsInterrupt )
					m_pID_PROGRESS->SetValue( 0 );
				else
				{
					m_pID_PROGRESS->SetValue( (HQ_TimeGetTime() - m_dwStartTime)*1000/m_dwPeriod );
				}
			}
			else
			{
				int nValue = 1000 - (HQ_TimeGetTime()-m_dwStartTime)*1000/m_dwPeriod;					
				m_pID_PROGRESS->SetValue( nValue );
				//lyh解决进度条倒读条的时候进度不正确的问题
				m_pID_PROGRESS->GetFrameFather()->SetRedraw();
			}
		}
		break;
	default:
	    break;
	}

	// test
#ifdef _DEBUG
	if ( GetAsyncKeyState(VK_RCONTROL) )
	{
		if( GetAsyncKeyState('U') )
		{
			s_CUI_Progress.ShowByTime( HQ_TimeGetTime(), 3000, true,
									1, true, true );
		}
		else if( GetAsyncKeyState('D') )
		{
			s_CUI_Progress.ShowByTime( HQ_TimeGetTime(), 3000, false,
									1, true, true );
		}
		else if( GetAsyncKeyState('S') )
		{
			SetVisable( false );
		}
	}
#endif

	return true;
	unguard;
}

bool CUI_Progress::ProgressOnFrameRender()
{
	return true;
}

// 装载UI
bool CUI_Progress::_LoadUI()
{
	guardfunc;
	DWORD dwResult = theUiManager.AddFrame(  "data\\ui\\Progress.meui", true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[UI\\Progress.UI]失败")
			return false;
	}
	return DoControlConnect();
	unguard;
}
// 关连控件
bool CUI_Progress::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( Progress, s_CUI_ProgressProgressOnFrameRun );
	theUiManager.OnFrameRender( Progress, s_CUI_ProgressProgressOnFrameRender );

	m_pProgress = (ControlFrame*)theUiManager.FindFrame( Progress );
	m_pID_PROGRESS = (ControlProgress*)theUiManager.FindControl( Progress, ID_PROGRESS );
	m_pID_CASTINGBAR_BORDER = (ControlPicture*)theUiManager.FindControl( Progress, ID_CASTINGBAR_BORDER );
	m_pID_CASTINGBAR_Intermit = (ControlPicture*)theUiManager.FindControl( Progress, ID_CASTINGBAR_Intermit );
	m_pID_CASTINGBAR_Full = (ControlPicture*)theUiManager.FindControl( Progress, ID_CASTINGBAR_Full );
	m_pID_Text_Name = (ControlText*)theUiManager.FindControl( Progress, ID_TEXT_NAME );

	assert( m_pID_Text_Name );
	assert( m_pProgress );
	assert( m_pID_CASTINGBAR_BORDER );
	assert( m_pID_CASTINGBAR_Full );
	assert( m_pID_CASTINGBAR_Intermit );

	assert( m_pID_PROGRESS );

	SetVisable(FALSE);
	m_pProgress->SetFadeInorFadeOut(true);
	return true;
	unguard;
}
// 卸载UI
bool CUI_Progress::_UnLoadUI()
{
	guardfunc;
	m_pProgress = NULL;
	m_pID_PROGRESS = NULL;
	m_pID_CASTINGBAR_BORDER = NULL;
	m_pID_CASTINGBAR_Full = NULL;
	m_pID_CASTINGBAR_Intermit = NULL;
	m_pID_Text_Name = NULL;

	return theUiManager.RemoveFrame( "data\\ui\\Progress.meui" );
	unguard;
}
// 是否可视
bool CUI_Progress::_IsVisable()
{
	guardfunc;
	if( !m_pProgress )
		return false;
	return m_pProgress->IsVisable();
	unguard;
}
// 设置是否可视
void CUI_Progress::_SetVisable( const bool bVisable )
{
	guardfunc;
	if( !m_pProgress )
		return;
	if( !m_pID_PROGRESS )
		return;

	if( m_pProgress )
	{
		m_pProgress->SetVisable( bVisable );
		if ( bVisable )
		{
			theUiManager.ToTop( m_pProgress );
		}
	}

	if( m_pID_Text_Name )
		m_pID_Text_Name->SetVisable( bVisable );

	if ( bVisable == false )
	{
		m_enShowType = Type_Normal;
	}
	else
	{
		m_pID_PROGRESS->SetVisable( bVisable );
	}
	
	if (bVisable)
	{
		if( m_pID_CASTINGBAR_BORDER )
			m_pID_CASTINGBAR_BORDER->SetVisable( bVisable );
		if( m_pID_CASTINGBAR_Intermit )
			m_pID_CASTINGBAR_Intermit->SetVisable( false );
	}
	else
	{
		if( m_pID_CASTINGBAR_BORDER )
			m_pID_CASTINGBAR_BORDER->SetVisable( false );
		if( m_pID_CASTINGBAR_Intermit )
			m_pID_CASTINGBAR_Intermit->SetVisable( true );

	}

	if( m_pID_CASTINGBAR_Full )
		m_pID_CASTINGBAR_Full->SetVisable( false );
	

	
	unguard;
}

void CUI_Progress::ShowByValue( int nCurValue, int nLowValue, int nHighValue,
			int nFlashCount, bool bAutoClose, bool bFadeIn )
{
	guardfunc;
	if( !m_pID_PROGRESS )
		return;

	m_enShowType = Type_Value;
	m_pID_PROGRESS->SetValue( (nCurValue-nLowValue)*(nHighValue-nLowValue)/1000 );
	m_nFlashCount = nFlashCount;
	m_bAutoClose = bAutoClose;
	m_bFadeIn = bFadeIn;
	SetVisable( true );
	unguard;
}

void CUI_Progress::ShowByTime( DWORD dwStartTime, DWORD dwPeriod, bool bUp,
	int nFlashCount, bool bAutoClose, bool bFadeIn,
	const char* pName, bool bIsInterrupt, bool bConnectLastProgress,
	DWORD dwCorrectValue, BOOL bClientCompletedDisappear )
{
	guardfunc;

    if( !m_pProgress )
        SetVisable( true );

	if( !m_pProgress || !m_pID_PROGRESS )
		return;

	if( bIsInterrupt )
		m_bProgressComplete = TRUE;
	else
		m_bProgressComplete = FALSE;

	if( bConnectLastProgress && !m_bIsInterrupt )
	{
		float fLastPercent = 1; // 上一次吟唱播放到的百分比
		DWORD dwTotalPeriodTime = 1; // 计算后得的总的吟唱时间

		if( m_dwPeriod > 0 )
			fLastPercent = (float)(HQ_TimeGetTime() - m_dwStartTime )/m_dwPeriod;

		if( fLastPercent > 0 && fLastPercent < 1 )
		{
			if( dwCorrectValue > dwPeriod )
			{
				dwTotalPeriodTime = 0;
			}
			else
			{
				dwTotalPeriodTime = (dwPeriod - dwCorrectValue)/( 1 - fLastPercent );
				dwStartTime = dwStartTime - fLastPercent*dwTotalPeriodTime;
			}
		}
		dwPeriod = dwTotalPeriodTime;
	}

	m_enShowType = Type_Time;
	m_dwStartTime = dwStartTime;
	m_dwPeriod = dwPeriod;
	m_nFlashCount = nFlashCount;
	m_bAutoClose = bAutoClose;
	m_bFadeIn = bFadeIn;
	m_bUp = bUp;
	m_bClientCompletedDisappear = bClientCompletedDisappear;

	if ( pName )
		*m_pID_Text_Name = pName;
	else
		*m_pID_Text_Name = "";

	m_bIsInterrupt = bIsInterrupt;

	m_pProgress->StartFlash( 0, false, false );

	if( m_bUp == TRUE )
	{
		m_pID_PROGRESS->SetValue( 0 );
	}
	else
	{
		m_pID_PROGRESS->SetValue( 1000 );
	}
	
	SetVisable( true );
	if( bIsInterrupt )
	{
		
		//m_pID_PROGRESS->SetValue( 0 );
		m_pID_PROGRESS->SetVisable( true );
		if( m_pID_CASTINGBAR_Full )
			m_pID_CASTINGBAR_Full->SetVisable( false );
		if( m_pID_CASTINGBAR_Intermit )
			m_pID_CASTINGBAR_Intermit->SetVisable( true );
		if( m_pID_CASTINGBAR_BORDER )
			m_pID_CASTINGBAR_BORDER->SetVisable( false );
	}
	else
	{
		
		if( m_pID_CASTINGBAR_Full )
			m_pID_CASTINGBAR_Full->SetVisable( false );
		if( m_pID_CASTINGBAR_Intermit )
			m_pID_CASTINGBAR_Intermit->SetVisable( false );

		if( m_pID_CASTINGBAR_BORDER )
			m_pID_CASTINGBAR_BORDER->SetVisable( true );
	}
	unguard;
}