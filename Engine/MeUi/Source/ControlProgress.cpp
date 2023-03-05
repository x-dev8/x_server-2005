#include "MeUi/ControlProgress.h"
#include "MeUi/UiManager.h"
#include "Me3d/BaseGraphics.h"
#include "FuncPerformanceLog.h"
#include <assert.h>
#include "MeUi/UiRender.h"
#include "MeUi/Animation/XmlAnimation.h"
#include "Me3d/Global.h"

extern DWORD g_dwColorTip0;
extern DWORD g_dwColorTip1;

#define UI_FLASH_SPEED	0.618f
#define UI_MOVE_SPEED	0.2f

ControlProgress::ControlProgress(void)
{
    m_bVertical = false;
    m_bReverse = false;

	m_nMaxValue = 1000;
	m_nValue = 0;

	m_bMouseMoveOn = false;
	m_bShowTip = false;
	m_bFlicker = false;

    m_pAnimation = NULL;
    m_dwAniBeginTime = 0;
	m_bAniStart = false;
}

ControlProgress::~ControlProgress(void)
{
    if( m_pAnimation )
    {
        ControlFrame* pFrame = GetFrameFather();
        if( pFrame && m_pAnimation->IsInAnimation() )
        {
            pFrame->GetUiAniManageNotNULL()->StopAnimation( m_pAnimation );
        }
        delete m_pAnimation;
        m_pAnimation = NULL;
    }
	ReleaseBackGroundPic();
}

void ControlProgress::InitUIData( IN ControlObject* pFather, IN S_BaseData* pData )
{
	ControlObject::InitUIData( pFather, pData );

    S_ProgressData* pProgressData = ( S_ProgressData* )pData;
    if( pProgressData )
    {
        m_bVertical = pProgressData->m_bVertical;
        m_bReverse = pProgressData->m_bReverse;
        if( pProgressData->m_szAniPath )
        {
            CreateAnimation( pProgressData->m_szAniPath, pProgressData->m_bAniOnly, pProgressData->m_bAutoPlay );
        }
    }

	SetShowTips();
}

void ControlProgress::Run()
{
	ControlObject::Run();
	if ((IsVisable() ||m_bInFade) && GetFrameFather()->GetFrameRender()->isQueueingEnabled() )
	{
		// 淡入淡出
		if( m_bInFade )
		{
			if ( IsVisable() )
			{
				m_nFadeCurColorA = m_FadeSpeed*(HQ_TimeGetTime()-m_dwFadeLastTime);
				if ( m_nFadeCurColorA >= m_nMaxFade )
				{
					m_nFadeCurColorA = m_nMaxFade;
					m_bInFade = false;
				}
			}
			else
			{
				m_nFadeCurColorA = m_FadeSpeed*(HQ_TimeGetTime()-m_dwFadeLastTime);
				if ( m_nFadeCurColorA <= m_nMinFade )
				{
					m_nFadeCurColorA = m_nMinFade;
					m_bInFade = false;
				}
			}

			if ( !m_bInFade )
			{
				theUiManager.Compositor();
			}
		}

		float percent = 0.0f;
		if (m_nMaxValue > 0)
		{
			percent = (float)m_nValue/m_nMaxValue;
		}
		if( percent > 0.0f )
		{
			RECT rcReal;
			GetRealRect( &rcReal );
			if( ( IsNeedRender() ) && m_nFlashCurCount >= m_nFlashCount )
			{
				static bool bFlickerStatus = true;
				static DWORD dwLastTime = 0;
				static DWORD dwCurrentTime = 0;

				dwCurrentTime = HQ_TimeGetTime();

                int nAlpha = m_nFadeCurColorA;
                int nFade = 0xff;
				D3DCOLOR dwColor = D3DCOLOR_ARGB(m_nFadeCurColorA,0xff,0xff,0xff);
				if( m_bFlicker )
				{
					if( ( dwCurrentTime - dwLastTime ) >= 300 )//change color
					{
						bFlickerStatus = !bFlickerStatus;
						dwLastTime = dwCurrentTime;
					}

					if( bFlickerStatus )
                    {
						dwColor = D3DCOLOR_ARGB(m_nFadeCurColorA,0xcc,0xcc,0xcc);				
                        nFade = 0xcc;
                    }
				}			

                RECT rcDest;
                GetProgressWorkingArea( rcDest );

                if( !m_strBackPicName.empty() && m_pstPic && m_nQuadId != -1 )
                {
                    ControlPictureManager::S_Pic *pPic = theControlPictureManager.RetrievePic( m_nPicId, NULL );
                    if( pPic )
                    {
                        UiRender* pRender = GetFrameFather()->GetFrameRender();
                        if( pRender )
                        {
                            pRender->PushWorkingArea( rcDest );
                            pRender->adjustQuad( m_nQuadId, rcReal, pPic->m_pd3dTexture, m_pstPic->m_rcClient, dwColor );
                            pRender->PopWorkingArea();
                        }
                    }
                }

                // added by zhuomeng.hu		[12/9/2010]
                if( m_pAnimation )
                {
                    m_pAnimation->InitializeFunctor( CSmartAnimation::EFunctorType_Alpha,   nAlpha, NULL );
                    m_pAnimation->InitializeFunctor( CSmartAnimation::EFunctorType_Fade,    nFade, NULL );
                }
			}
		}
	}

    // 动画     added by zhuomeng.hu		[12/9/2010]
    if( m_pAnimation )
    {
        // 隐藏，失效则不播动画
        ControlFrame* pFrame = GetFrameFather();
        if( pFrame )
        {
            if( !pFrame->IsVisable() || !IsVisable() || !IsEnable() )
            {
                if( m_pAnimation->IsInAnimation() )
                    pFrame->GetUiAniManageNotNULL()->StopAnimation( m_pAnimation );
            }
        }
    }
}

void ControlProgress::SetWidth( const int nW )
{
    guardfunc;
    assert( nW >= 0 );
    m_pstData->m_rcRealSize.right = m_pstData->m_rcRealSize.left + nW *ReciprocalGetSCALE(this);
    m_nWidth = nW;
    unguard;
}

void ControlProgress::SetHeight( const int nH )
{
    guardfunc;
    assert( nH >= 0 );
    m_pstData->m_rcRealSize.bottom = m_pstData->m_rcRealSize.top + nH *ReciprocalGetSCALE(this);
    m_nHeight = nH;
    unguard;
}
void ControlProgress::SetValue( const DWORD dwValue )
{
	__int64 n64 = (__int64)dwValue;
	SetValue( n64 );
}
void ControlProgress::SetValue( const float fValue )
{
	__int64 n64 = (__int64)fValue;
	SetValue( n64 );
}
void ControlProgress::SetValue( const int n )
{
	__int64 n64 = (__int64)n;
	SetValue( n64 );
}
void ControlProgress::SetValue( const __int64 n )
{
	m_nValue = n;
	if ( m_nValue < 0 ) m_nValue = 0;
	if ( m_nValue > m_nMaxValue )	m_nValue = m_nMaxValue;

    UpdateByValueChange();
}

void ControlProgress::UpdateByValueChange()
{
    RECT rcDest;
    GetProgressWorkingArea( rcDest );

    if( m_pAnimation && m_pAnimation->IsInAnimation() )
    {
        m_pAnimation->SetWorkingArea( rcDest );
        DWORD dwTime = HQ_TimeGetTime();
        m_pAnimation->Update( dwTime );
    }
}

void ControlProgress::Render()
{
	if( !IsNeedRender() )
	    return;

    int left = m_pstData->m_rcRealSize.left;
    int right = m_pstData->m_rcRealSize.right;

    float percent = 0.0f;
    if (m_nMaxValue > 0)
    {
        percent = (float)m_nValue/m_nMaxValue;
    }

    RECT rcReal;
    GetRealRect( &rcReal );

    // 移动
    if( m_bMoving )
    {
        int na = m_nMoveToY - rcReal.top;
        int nb = m_nMoveToX - rcReal.left;
        int nc = sqrt( (FLOAT)(na*na) + (FLOAT)(nb*nb) );
        int nX = 0;
        int nY = 0;
        int nMoveDistance = UI_MOVE_SPEED*( HQ_TimeGetTime() - m_dwMoveStartTime );
        if ( nMoveDistance >= nc )
        {
            m_bMoving = false;
            nX = m_nMoveToX;
            nY = m_nMoveToY;
        }
        else
        {
            nX = nMoveDistance*nb/nc + rcReal.left;
            nY = nMoveDistance*na/nc + rcReal.top;
        }
        SetPos( nX, nY );
    }

    int nAlpha = 0xff;
    int nFade = 0xff;

    RECT rcDest;
    GetProgressWorkingArea( rcDest );

    UiRender* pRender = GetFrameFather()->GetFrameRender();
    if( pRender )
		pRender->PushWorkingArea( rcDest );

    {
        if ( !m_strBackPicName.empty() && m_pstPic  )
        {
            if (m_nPicId == -1)
            {
                theControlPictureManager.RegisterTexture(&m_nPicId,m_strBackPicName.c_str());
            }
            if( ( m_bVisable || m_bFadeInorFadeOut ) && m_nFlashCurCount >= m_nFlashCount )
            {
                static bool bFlickerStatus = true;
                static DWORD dwLastTime = 0;
                static DWORD dwCurrentTime = 0;

                dwCurrentTime = HQ_TimeGetTime();

                D3DCOLOR dwColor = D3DCOLOR_ARGB(m_nFadeCurColorA,0xff,0xff,0xff);
				nAlpha = m_nFadeCurColorA;
				if( m_bFlicker )
				{
					if( ( dwCurrentTime - dwLastTime ) >= 300 )//change color
					{
						bFlickerStatus = !bFlickerStatus;
						dwLastTime = dwCurrentTime;
					}

					if( bFlickerStatus )
					{
						dwColor = D3DCOLOR_ARGB(m_nFadeCurColorA,0xcc,0xcc,0xcc);				
						nFade = 0xcc;
					}
				}	
				m_nQuadId = theControlPictureManager.BitBlt( &m_nPicId, NULL, &rcReal,
					&m_pstPic->m_rcClient, dwColor, m_fBackPicZ, _renderFlag );
				////////////////////////////////////////////////////////////////////
				int w = m_nWidth;;
				int h = m_nHeight;;
				int nLeftW = (m_pstPic->m_rcClient.left - m_pstPic->m_rcFrame.left) * ControlObjectGetSCALE(this);
				int nLeftH = (m_pstPic->m_rcClient.bottom - m_pstPic->m_rcClient.top) * ControlObjectGetSCALE(this);
				int nTopW = (m_pstPic->m_rcClient.right - m_pstPic->m_rcClient.left) * ControlObjectGetSCALE(this);
				int nTopH = (m_pstPic->m_rcClient.top - m_pstPic->m_rcFrame.top) * ControlObjectGetSCALE(this);
				int nRightW = (m_pstPic->m_rcFrame.right - m_pstPic->m_rcClient.right) * ControlObjectGetSCALE(this);
				int nRightH = (m_pstPic->m_rcClient.bottom - m_pstPic->m_rcClient.top) * ControlObjectGetSCALE(this);
				int nBottomW = (m_pstPic->m_rcClient.right - m_pstPic->m_rcClient.left) * ControlObjectGetSCALE(this);
				int nBottomH = (m_pstPic->m_rcFrame.bottom - m_pstPic->m_rcClient.bottom) * ControlObjectGetSCALE(this);
				int nLeftTopW = (m_pstPic->m_rcClient.left - m_pstPic->m_rcFrame.left) * ControlObjectGetSCALE(this);
				int nLeftTopH = (m_pstPic->m_rcClient.top - m_pstPic->m_rcFrame.top) * ControlObjectGetSCALE(this);
				int nRightTopW = (m_pstPic->m_rcFrame.right - m_pstPic->m_rcClient.right) * ControlObjectGetSCALE(this);
				int nRightTopH = (m_pstPic->m_rcClient.top - m_pstPic->m_rcFrame.top) * ControlObjectGetSCALE(this);
				int nLeftBottomW = (m_pstPic->m_rcClient.left - m_pstPic->m_rcFrame.left) * ControlObjectGetSCALE(this);
				int nLeftBottomH = (m_pstPic->m_rcFrame.bottom - m_pstPic->m_rcClient.bottom) * ControlObjectGetSCALE(this);
				int nRightBottomW = (m_pstPic->m_rcFrame.right - m_pstPic->m_rcClient.right) * ControlObjectGetSCALE(this);
				int nRightBottomH = (m_pstPic->m_rcFrame.bottom - m_pstPic->m_rcClient.bottom) * ControlObjectGetSCALE(this);
				int nMiddleW = (m_pstPic->m_rcClient.right - m_pstPic->m_rcClient.left) * ControlObjectGetSCALE(this);
				int nMiddleH = (m_pstPic->m_rcClient.bottom - m_pstPic->m_rcClient.top) * ControlObjectGetSCALE(this);
				BitBlt( &m_nPicId, NULL,
					rcReal.left, rcReal.top,
					nLeftTopW, nLeftTopH,
					m_pstPic->m_rcFrame.left, m_pstPic->m_rcFrame.top,
					m_nLeftTopW, m_nLeftTopH,
					DrawModeNormal,
					dwColor );
				// RightTop
				BitBlt( &m_nPicId, NULL,
					rcReal.right-nRightTopW,rcReal.top,
					nRightTopW, nRightTopH,
					m_pstPic->m_rcClient.right, m_pstPic->m_rcFrame.top,
					m_nRightTopW, m_nRightTopH,
					DrawModeNormal,
					dwColor );
				// LeftBottom
				BitBlt( &m_nPicId, NULL,
					rcReal.left, rcReal.bottom-nLeftBottomH,
					nLeftBottomW, nLeftBottomH,
					m_pstPic->m_rcFrame.left, m_pstPic->m_rcClient.bottom,
					m_nLeftBottomW, m_nLeftBottomH,
					DrawModeNormal,
					dwColor );
				// RightBottom
				BitBlt( &m_nPicId, NULL,
					rcReal.right-nRightBottomW, rcReal.bottom-nRightBottomH,
					nRightBottomW, nRightBottomH,
					m_pstPic->m_rcClient.right, m_pstPic->m_rcClient.bottom,
					m_nRightBottomW, m_nRightBottomH,
					DrawModeNormal,
					dwColor );
				// Left
				BitBlt( &m_nPicId, NULL,
					rcReal.left, rcReal.top+nLeftTopH,
					nLeftW, h-nLeftTopH-nLeftBottomH,
					m_pstPic->m_rcFrame.left, m_pstPic->m_rcClient.top,
					m_nLeftW, m_nLeftH,
					m_pstData->m_nDrawMode[S_BaseData::Mode_Left],
					dwColor );
				// Top
				BitBlt( &m_nPicId, NULL,
					rcReal.left+nLeftTopW, rcReal.top,
					w-nLeftTopW-nRightTopW,nTopH,
					m_pstPic->m_rcClient.left, m_pstPic->m_rcFrame.top,
					m_nTopW,m_nTopH,
					m_pstData->m_nDrawMode[S_BaseData::Mode_Top],
					dwColor );
				// Right
				BitBlt( &m_nPicId, NULL,
					rcReal.right-nRightW, rcReal.top+nRightTopH,
					nRightW, h-nRightTopH-nRightBottomH,
					m_pstPic->m_rcClient.right, m_pstPic->m_rcClient.top,
					m_nRightW, m_nRightH,
					m_pstData->m_nDrawMode[S_BaseData::Mode_Right],
					dwColor );
				// Bottom
				BitBlt( &m_nPicId, NULL,
					rcReal.left+nLeftBottomW, rcReal.bottom-nLeftBottomH,
					w-nLeftBottomW-nRightBottomW, nBottomH,
					m_pstPic->m_rcClient.left, m_pstPic->m_rcClient.bottom,
					m_nBottomW,m_nBottomH,
					m_pstData->m_nDrawMode[S_BaseData::Mode_Bottom],
					dwColor );
				// Middle
				BitBlt( &m_nPicId, NULL,
					rcReal.left+nLeftTopW, rcReal.top+nLeftTopH,
					w-nLeftW-nRightW, h-nTopH-nBottomH,
					m_pstPic->m_rcClient.left, m_pstPic->m_rcClient.top,
					m_nMiddleW, m_nMiddleH,
					m_pstData->m_nDrawMode[S_BaseData::Mode_Middle],
					dwColor );
				////////////////////////////////////////////////////////////////////
                //nAlpha = m_nFadeCurColorA;
                //if( m_bFlicker )
                //{
                //    if( ( dwCurrentTime - dwLastTime ) >= 300 )//change color
                //    {
                //        bFlickerStatus = !bFlickerStatus;
                //        dwLastTime = dwCurrentTime;
                //    }

                //    if( bFlickerStatus )
                //    {
                //        dwColor = D3DCOLOR_ARGB(m_nFadeCurColorA,0xcc,0xcc,0xcc);				
                //        nFade = 0xcc;
                //    }
                //}			

                
            }
        }

        // 动画     added by zhuomeng.hu		[12/8/2010]
        if( m_pAnimation )
        {
            AnimationRedraw( nAlpha, nFade );
        }
    }
	if( pRender )
	    pRender->PopWorkingArea();

#ifdef _DEBUG
    if ( IsActivated() )
    {
        UiDrawer::DrawRect2D( rcDest, 0x7f0000ff );
    }
    else if ( GetAsyncKeyState(VK_LCONTROL) )
    {
        UiDrawer::DrawRect2D( rcDest, 0xff00ff00 );
    }
#endif
	
}

void ControlProgress::Create( IN const RECT* pRect, const D3DCOLOR colBack )
{
	assert( pRect );
	ReleaseUI();
	S_ProgressData *pProgress = MeNew S_ProgressData;
	m_bNeedRelease = true;
	pProgress->m_nType = Type_Progress;
	sprintf( pProgress->m_szID, "ID_PROGRESS_AUTO_%d", rand() );
	pProgress->m_rcRealSize = *pRect;
	InitUIData( NULL, pProgress );
	m_colBackColor = colBack;
}


void ControlProgress::Create( ControlFrame* pFather,S_ProgressData* pData ,const char* pProcessName)
{
	ReleaseUI();
	S_ProgressData *pProgress = MeNew S_ProgressData;
	m_bNeedRelease = true;
	memcpy_s(pProgress,sizeof(S_ProgressData),pData,sizeof(S_ProgressData));
	InitUIData( pFather, pProgress );
	strcpy_s(pProgress->m_szID,64,pProcessName);
}
void ControlProgress::SetVisable( const bool bVisable, const bool bFadeInorFadeOut )
{
	ControlObject::SetVisable( bVisable );
	SetFadeInorFadeOut(bFadeInorFadeOut);
	m_nFlashCount = m_nFlashCurCount = 0;
}
bool ControlProgress::OnMouseMove( UINT nFlags, const int nX, const int nY)
{
	if(IsVisable())
	{
		if( PtInObject(nX, nY,false) )
		{
			m_bMouseMoveOn = true;

			if( IsShowTip() && ( TipInfo.m_ucIconInfoLine > 0 ))
			{
				theIconInfoMouseTip.SetDisplayInfo( &TipInfo,
					nX, nY, false,
					m_nFontIndex, m_pstData->m_nFontSize * ControlObjectGetREAL_SCALE(this),
					m_pstData->m_colFont,
					false );
				return true;
			}
		}
		else
		{
			m_bMouseMoveOn = false;
		}
	}
	return false;
}
void ControlProgress::setTipName(const char* ch, DWORD dwAlign /* = DT_CENTER | DT_VCENTER */ )
{
	guardfunc;
	if( NULL == ch )
		return;

	TipInfo.SetInfo( ch, dwAlign );
	unguard;
}
void ControlProgress::ResetDevice()
{
	ControlObject::ResetDevice();
}

void ControlProgress::setTip(const char* data)
{
	guardfunc;
	if( NULL == data )
		return;

	TipInfo.SetInfo( data, DT_LEFT | DT_VCENTER  );	
	unguard;
}

void ControlProgress::SetShowTips()
{
	if (strlen(m_pstData->m_szTips) != 0)
	{
		m_bShowTip = true;
		setTip(m_pstData->m_szTips);
	}
}

void ControlProgress::SetRealPostion(const RECT& realRect)
{
	int nWidth = realRect.right - realRect.left;
	int nHeight = realRect.bottom - realRect.top;

	RECT rect = {0, 0, 0, 0};
	GetFatherRect(&rect);
	switch (m_pstData->m_nAlignMode)
	{
	case AlignMode_LeftTop:
		{
			m_pstData->m_rcRealSize.top = (realRect.top - rect.top) * ReciprocalGetSCALE(this);
			m_pstData->m_rcRealSize.bottom = m_pstData->m_rcRealSize.top + nHeight;
			m_pstData->m_rcRealSize.left = (realRect.left - rect.left) * ReciprocalGetSCALE(this);
			m_pstData->m_rcRealSize.right = m_pstData->m_rcRealSize.left + nWidth;
		}
		break;
	case AlignMode_RightTop:
		{
			m_pstData->m_rcRealSize.top = (realRect.top - rect.top) * ReciprocalGetSCALE(this);
			m_pstData->m_rcRealSize.bottom = m_pstData->m_rcRealSize.top + nHeight;
			m_pstData->m_rcRealSize.left = (realRect.left - rect.right) * ReciprocalGetSCALE(this);
			m_pstData->m_rcRealSize.right = m_pstData->m_rcRealSize.left + nWidth;
		}
		break;
	case AlignMode_LeftBottom:
		{
			m_pstData->m_rcRealSize.top = (realRect.top - rect.bottom) * ReciprocalGetSCALE(this);
			m_pstData->m_rcRealSize.bottom = m_pstData->m_rcRealSize.top + nHeight;
			m_pstData->m_rcRealSize.left = (realRect.left - rect.left) * ReciprocalGetSCALE(this);
			m_pstData->m_rcRealSize.right = m_pstData->m_rcRealSize.left + nWidth;
		}
		break;
	case AlignMode_RightBottom:
		{
			m_pstData->m_rcRealSize.top = (realRect.top - rect.bottom) * ReciprocalGetSCALE(this);
			m_pstData->m_rcRealSize.bottom = m_pstData->m_rcRealSize.top + nHeight;
			m_pstData->m_rcRealSize.left = (realRect.left - rect.right) * ReciprocalGetSCALE(this);
			m_pstData->m_rcRealSize.right = m_pstData->m_rcRealSize.left + nWidth;
		}
		break;
	case AlignMode_Middle:
		{
			m_pstData->m_rcRealSize.top = (realRect.top - (rect.bottom + rect.top) * 0.5) * ReciprocalGetSCALE(this);
			m_pstData->m_rcRealSize.bottom = m_pstData->m_rcRealSize.top + nHeight;
			m_pstData->m_rcRealSize.left = (realRect.left - (rect.right + rect.left) * 0.5) * ReciprocalGetSCALE(this);
			m_pstData->m_rcRealSize.right = m_pstData->m_rcRealSize.left + nWidth;
		}
		break;
	case AlignMode_LeftMiddle:
		{
			m_pstData->m_rcRealSize.top = (realRect.top - (rect.bottom + rect.top) * 0.5) * ReciprocalGetSCALE(this);
			m_pstData->m_rcRealSize.bottom = m_pstData->m_rcRealSize.top + nHeight;
			m_pstData->m_rcRealSize.left = (realRect.left - rect.left) * ReciprocalGetSCALE(this);
			m_pstData->m_rcRealSize.right = m_pstData->m_rcRealSize.left + nWidth;
		}
		break;
	case AlignMode_TopMiddle:
		{
			m_pstData->m_rcRealSize.top = (realRect.top - rect.top) * ReciprocalGetSCALE(this);
			m_pstData->m_rcRealSize.bottom = m_pstData->m_rcRealSize.top + nHeight;
			m_pstData->m_rcRealSize.left = (realRect.left - (rect.right + rect.left) * 0.5) * ReciprocalGetSCALE(this);
			m_pstData->m_rcRealSize.right = m_pstData->m_rcRealSize.left + nWidth;
		}
		break;
	case AlignMode_RightMiddle:
		{
			m_pstData->m_rcRealSize.top = (realRect.top - (rect.bottom + rect.top) * 0.5) * ReciprocalGetSCALE(this);
			m_pstData->m_rcRealSize.bottom = m_pstData->m_rcRealSize.top + nHeight;
			m_pstData->m_rcRealSize.left = (realRect.left - rect.right) * ReciprocalGetSCALE(this);
			m_pstData->m_rcRealSize.right = m_pstData->m_rcRealSize.left + nWidth;
		}
		break;
	case AlignMode_BottomMiddle:
		{
			m_pstData->m_rcRealSize.top = (realRect.top - rect.bottom) * ReciprocalGetSCALE(this);
			m_pstData->m_rcRealSize.bottom = m_pstData->m_rcRealSize.top + nHeight;
			m_pstData->m_rcRealSize.left = (realRect.left - (rect.right + rect.left) * 0.5) * ReciprocalGetSCALE(this);
			m_pstData->m_rcRealSize.right = m_pstData->m_rcRealSize.left + nWidth;
		}
		break;
	default:
		MESSAGE_BOX("类型超出范围!");
		break;
	}

	m_nWidth = (m_pstData->m_rcRealSize.right - m_pstData->m_rcRealSize.left) * ControlObjectGetSCALE(this);
	m_nHeight = (m_pstData->m_rcRealSize.bottom - m_pstData->m_rcRealSize.top) * ControlObjectGetSCALE(this);	
}

void ControlProgress::UpdateAimation(const RECT& rect)
{
	if (!m_pAnimation)
	{
		return;
	}

	int nWidth = rect.right - rect.left;
	int nHeight = rect.bottom - rect.top;
	m_pAnimation->InitializeFunctor(CSmartAnimation::EFunctorType_X, rect.left + nWidth/2, NULL);
	m_pAnimation->InitializeFunctor(CSmartAnimation::EFunctorType_Y, rect.top + nHeight/2, NULL);
	m_pAnimation->InitializeFunctor(CSmartAnimation::EFunctorType_Width, nWidth, NULL);
	m_pAnimation->InitializeFunctor(CSmartAnimation::EFunctorType_Height, nHeight, NULL);
	m_pAnimation->SetWorkingArea(const_cast<RECT&>(rect));
}

void ControlProgress::GetProgressWorkingArea( OUT RECT& rcDest )
{
    // 进度条分4种 (横竖正反)
    RECT rcReal;
    GetRealRect( &rcReal );
   
    float fPercent = 0.0f;
    if( m_nMaxValue > 0 )
    {
        fPercent = ( float )m_nValue / m_nMaxValue;
    }

    if( !m_bVertical && m_bReverse )
    {
        rcDest.right = rcReal.right;
        rcDest.left = rcReal.right - ( rcReal.right - rcReal.left ) * fPercent;
        rcDest.top = rcReal.top;
        rcDest.bottom = rcReal.bottom;
    }
    else if( m_bVertical && !m_bReverse )
    {
        rcDest.left = rcReal.left;
        rcDest.right = rcReal.right;
        rcDest.top = rcReal.bottom - ( rcReal.bottom - rcReal.top ) * fPercent;
        rcDest.bottom = rcReal.bottom;
    }
    else if( m_bVertical && m_bReverse )
    {
        rcDest.left = rcReal.left;
        rcDest.right = rcReal.right;
        rcDest.top = rcReal.top;
        rcDest.bottom = rcReal.top + ( rcReal.bottom - rcReal.top ) * fPercent;
    }
    else
    {
        rcDest.left = rcReal.left;
        rcDest.right = rcReal.left + ( rcReal.right - rcReal.left ) * fPercent;
        rcDest.top = rcReal.top;
        rcDest.bottom = rcReal.bottom;
    }
}

bool ControlProgress::CreateAnimation( std::string strPath, bool bEffectOnly, bool bAutoStart )
{
    if( strPath.empty() )
        return false;

    ControlFrame* pFrame = GetFrameFather();
    if( !pFrame )
        return false;

    UiRender* pRender = pFrame->GetFrameRender();
    if( !pRender )
        return false;

    if( strPath.find( ":\\" ) == std::string::npos )
    {
        strPath = std::string( GetRootPath() ) + "\\" + strPath;
    }

    m_pAnimation = new CXmlAnimation( pRender );
    MeXmlDocument doc;
    if( !doc.LoadFile( strPath.c_str() ) )
    {
        assert( false && "Load Progress Animation Failed!" );
        return false;
    }

    MeXmlElement* pElement = doc.FirstChildElement( "ProgressEffect" );
    if( pElement )
    {
        CXmlAnimation* pSmart = ( CXmlAnimation* )m_pAnimation;
        pSmart->Initialize( pElement );
    }

    RECT rcDest;
    GetRealRect( &rcDest );
    int nWidth = rcDest.right - rcDest.left;
    int nHeight = rcDest.bottom - rcDest.top;
    m_pAnimation->InitializeFunctor( CSmartAnimation::EFunctorType_X,       rcDest.left + nWidth / 2, NULL );
    m_pAnimation->InitializeFunctor( CSmartAnimation::EFunctorType_Y,       rcDest.top + nHeight / 2, NULL );
    m_pAnimation->InitializeFunctor( CSmartAnimation::EFunctorType_Width,   nWidth, NULL );
    m_pAnimation->InitializeFunctor( CSmartAnimation::EFunctorType_Height,  nHeight, NULL );

    m_bAniStart = bAutoStart;
    if( m_bAniStart )
    {
        StartAnimation();
    }

    if( bEffectOnly )
    {
        SetSkipAllMsg( true );
        SetMsgHoldup( false );
        SetValue( GetMaxValue() );
    }

    return true;
}

bool ControlProgress::IsAnimationCreated()
{
    if( !m_pAnimation )
        return false;

    return true;
}

void ControlProgress::AnimationRedraw( int nAlpha, int nFade )
{
    if( !m_pAnimation )
        return;

    ControlFrame* pFrame = GetFrameFather();
    if( !pFrame )
        return;
    if( !pFrame->IsVisable() || !IsVisable() || !IsEnable() )
        return;

	if( m_nMaxValue == 0 )
		return;

	if( !m_bAniStart )
		return;

    RECT rcReal;
    GetRealRect( &rcReal );
    int nWidth = rcReal.right - rcReal.left;
    int nHeight = rcReal.bottom - rcReal.top;
    m_pAnimation->InitializeFunctor( CSmartAnimation::EFunctorType_X,       rcReal.left + nWidth / 2, NULL );
    m_pAnimation->InitializeFunctor( CSmartAnimation::EFunctorType_Y,       rcReal.top + nHeight / 2, NULL );
    m_pAnimation->InitializeFunctor( CSmartAnimation::EFunctorType_Alpha,   nAlpha, NULL );
    m_pAnimation->InitializeFunctor( CSmartAnimation::EFunctorType_Fade,    nFade, NULL );
	
    RECT rcDest;
    GetProgressWorkingArea( rcDest );
    m_pAnimation->SetWorkingArea( rcDest );

    DWORD dwCurrentTime = HQ_TimeGetTime();
    if( m_pAnimation->IsInAnimation() )
    {
        m_pAnimation->Redraw( dwCurrentTime );
    }
    else if( m_pAnimation->GetD3DTexture() )
    {
        pFrame->GetUiAniManageNotNULL()->AddAnimation( m_pAnimation );
        m_pAnimation->StartAnimation( dwCurrentTime, dwCurrentTime - m_dwAniBeginTime );
    }
}

bool ControlProgress::StartAnimation()
{
    if( !m_pAnimation )
        return false;

    ControlFrame* pFrame = GetFrameFather();
    if( !pFrame )
        return false;

    m_bAniStart = true;

    if( m_pAnimation->IsInAnimation() || !m_pAnimation->GetD3DTexture() )
        return false;

    m_dwAniBeginTime = HQ_TimeGetTime();
    pFrame->SetRedraw();
    return true;
}

bool ControlProgress::StopAnimation()
{
    if( !m_pAnimation )
        return false;

    ControlFrame* pFrame = GetFrameFather();
    if( !pFrame )
        return false;

    m_bAniStart = false;

    if( !m_pAnimation->IsInAnimation() )
        return false;

    pFrame->GetUiAniManageNotNULL()->StopAnimation( m_pAnimation );
    pFrame->SetRedraw();
    return true;
}

bool ControlProgress::IsAnimationStarted()
{
    if( !m_pAnimation )
        return false;

    if( !m_bAniStart || !m_pAnimation->IsInAnimation() )
        return false;

    return true;
}

bool ControlProgress::RestartAnimation()
{
    if( !m_pAnimation )
        return false;

    ControlFrame* pFrame = GetFrameFather();
    if( !pFrame )
        return false;

    if( m_pAnimation->IsInAnimation() && m_bAniStart )
    {
        StopAnimation();
    }

    return StartAnimation();
}

bool ControlProgress::IsAnimationStop()
{
	if(!m_pAnimation)
		return false;

	return m_pAnimation->IsInAnimation();
}
