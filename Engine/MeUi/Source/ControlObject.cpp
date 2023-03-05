#include "MeUi/ControlObject.h"
#include <assert.h>
#include <vector>
#include "MeUi/UiManager.h"
#include "FuncPerformanceLog.h"
#include "Me3d/Config.h"
#include "MeFont/MeFontSystem.h"    //##

#define UI_FLASH_SPEED	0.618f
#define UI_MOVE_SPEED	0.2f

//int SCREEN_WIDTH = 1024;
//int SCREEN_HEIGHT = 768;

void print_error( const char* err )
{
	//char szData[256] = {0};

	//SYSTEMTIME systime;
	//GetLocalTime( &systime );
	//_snprintf(szData, sizeof(szData)-1, "%04d-%02d-%02d\t%02d:%02d:%02d\t\t", 
	//	systime.wYear, systime.wMonth, systime.wDay, systime.wHour, systime.wMinute, systime.wSecond);

	//std::string strError = szData;
	//strError += err;
	//std::ofstream fErr(".\\Log\\err.log", std::ios::app);
	//if(fErr.is_open() && strError.c_str() )
	//{
	//	fErr << strError.c_str() <<std::endl;
	//	fErr.close();
	//}//---------------------------------------
}

float ControlObject::UI_SCALE = 1.0f;
float ControlObject::UI_REAL_SCALE = 1.f;
float ControlObject::UI_Adjust_SCALE = 1.f;

ControlObject::ControlObject(void)
{
	guardfunc;
	m_pstData = NULL;
	m_pFather = NULL;
	m_pFrameFather = NULL;
	m_nWidth = m_nHeight = 0;
	m_nLeftW = m_nLeftH = 0;
	m_nTopW = m_nTopH = 0;
	m_nRightW = m_nRightH = 0;
	m_nBottomW = m_nBottomH = 0;
	m_nLeftTopW = m_nLeftTopH = 0;
	m_nRightTopW = m_nRightTopH = 0;
	m_nLeftBottomW = m_nLeftBottomH = 0;
	m_nRightBottomW = m_nRightBottomH = 0;
	m_nMiddleW = m_nMiddleH = 0;
	m_nFontIndex = 0;
	m_bVisable = true;
	m_bCovered = false;
	m_bNeedRelease = false;
	m_colBackColor = 0;
	m_pstPic = NULL;
	m_pOnMsgProc = NULL;
	m_pOnMsgProc2 = NULL;
	m_bMsgHoldup = true;
	m_fBackPicZ = 0.0f;

	m_nFlashCurCount = 0;
	m_nFlashCount = 0;
	m_nFlashCurColorA = 0;
	m_bFlashedAutoClose = false;
	m_dwFlashStartTime = 0;

    m_fAlpha = 1.0f;
	m_bFadeInorFadeOut = false;
	m_bInFade			= false;
	m_nFadeCurColorA = 0xff;
	m_nMaxFade		 = 0xff;
	m_nMinFade		 = 0x00;
	m_dwFadeLastTime = 0;

	m_bMoving = false;
	m_nMoveToX = 0;
	m_nMoveToY = 0;
	m_dwMoveStartTime = 0;
	m_bFadeInval	  = false;
	m_bDrawFrame	  = false;
	m_bAllVisable	  = false;
	m_nPicId = -1;
	m_bSkipMsg = false;
	m_hDC = NULL;


	m_unLeftTopVBOffset = -1;
	m_unRightTopVBOffset = -1;
	m_unLeftBottomVBOffset = -1;
	m_unRightBottomVBOffset = -1;
	m_unLeftVBOffset = -1;
	m_unTopVBOffset = -1;
	m_unRightVBOffset = -1;
	m_unBottomVBOffset = -1;
	m_unMiddleVBOffset = -1;

	m_fFlashSpeed = 0.618f;

    m_pOnVisibleChanged = NULL;

    _renderFlag = 0;

	m_bRenderTextWithZ = false;
	m_nQuadId = -1;
#ifdef _DEBUG
	m_debug_bHasWarning = true;
#endif

	m_bEnable = true;

	m_FadeSpeed = UI_FADE_SPEED;

// 	m_bLostFocusPassive = true;
	unguard;
}
void ControlObject::CheckTipAndClear()
{
	if( GetTipPointer() != theIconInfoMouseTip.GetIconInfo() )
		return;

	theIconInfoMouseTip.Clear();
}
ControlObject::~ControlObject(void)
{
	guardfunc;
//	SetVisable( false );
	CheckTipAndClear();
	ReleaseUI();
	unguard;
}

//------- 释放    (   at 2004-6-2)
void ControlObject::ReleaseUI()
{
	guardfunc;
	m_pFather = NULL;
	m_pFrameFather = NULL;
	if ( m_bNeedRelease == true )
	{
		if ( m_pstData )
		{
			delete m_pstData;
			m_pstData = NULL;
		}
	}
	ReleaseBackGroundPic();
	unguard;
}

bool ControlObject::UseFocus()
{
	guardfunc;
	if ( IsVisable() )
	{
		return true;
	}
	return false;
	unguard;
}

void ControlObject::GetFatherRect( OUT RECT* prc )
{
	guardfunc;
	assert( prc );
	assert( m_pstData );
	if ( !m_pFather )
	{
		prc->left = 0;
		prc->right = SCREEN_WIDTH;
		prc->top = 0;
		prc->bottom = SCREEN_HEIGHT;
	}
	else
	{
		m_pFather->GetRealRect( prc );
	}
	unguard;
}

void ControlObject::GetRectSize(OUT RECT* prc)
{
	prc->left   = m_pstData->m_rcRealSize.left * ControlObjectGetSCALE(this);
	prc->right  = prc->left + m_nWidth;
	prc->top    = m_pstData->m_rcRealSize.top * ControlObjectGetSCALE(this);
	prc->bottom = prc->top + m_nHeight;
}

void ControlObject::GetRealRect( OUT RECT* prc )
{
	guardfunc;
	GetFatherRect( prc );
	switch( m_pstData->m_nAlignMode )
	{
	case AlignMode_LeftTop:
		prc->left += m_pstData->m_rcRealSize.left * ControlObjectGetSCALE(this);
		prc->right = prc->left + m_nWidth;
		prc->top += m_pstData->m_rcRealSize.top * ControlObjectGetSCALE(this);
		prc->bottom = prc->top + m_nHeight;
		break;
	case AlignMode_RightTop:
		prc->left = prc->right + m_pstData->m_rcRealSize.left * ControlObjectGetSCALE(this);
		prc->right = prc->left + m_nWidth;
		prc->top += m_pstData->m_rcRealSize.top * ControlObjectGetSCALE(this);
		prc->bottom = prc->top + m_nHeight;
		break;
	case AlignMode_LeftBottom:
		prc->left += m_pstData->m_rcRealSize.left * ControlObjectGetSCALE(this);
		prc->right = prc->left + m_nWidth;
		prc->top = prc->bottom + m_pstData->m_rcRealSize.top * ControlObjectGetSCALE(this);
		prc->bottom = prc->top + m_nHeight;
		break;
	case AlignMode_RightBottom:
		prc->left = prc->right + m_pstData->m_rcRealSize.left * ControlObjectGetSCALE(this);
		prc->right = prc->left + m_nWidth;
		prc->top = prc->bottom + m_pstData->m_rcRealSize.top * ControlObjectGetSCALE(this);
		prc->bottom = prc->top + m_nHeight;
		break;
	case AlignMode_Middle:
		prc->left += (prc->right-prc->left)/2 + m_pstData->m_rcRealSize.left * ControlObjectGetSCALE(this);
		prc->right = prc->left + m_nWidth;
		prc->top += (prc->bottom-prc->top)/2 + m_pstData->m_rcRealSize.top * ControlObjectGetSCALE(this);
		prc->bottom = prc->top + m_nHeight;
		break;
	case AlignMode_LeftMiddle:
		prc->left += m_pstData->m_rcRealSize.left * ControlObjectGetSCALE(this);
		prc->right = prc->left + m_nWidth;
		prc->top += (prc->bottom-prc->top)/2 + m_pstData->m_rcRealSize.top * ControlObjectGetSCALE(this);
		prc->bottom = prc->top + m_nHeight;
		break;
	case AlignMode_TopMiddle:
		prc->left += (prc->right-prc->left)/2 + m_pstData->m_rcRealSize.left * ControlObjectGetSCALE(this);
		prc->right = prc->left + m_nWidth;
		prc->top += m_pstData->m_rcRealSize.top * ControlObjectGetSCALE(this);
		prc->bottom = prc->top + m_nHeight;
		break;
	case AlignMode_RightMiddle:
		prc->left = prc->right + m_pstData->m_rcRealSize.left * ControlObjectGetSCALE(this);
		prc->right = prc->left + m_nWidth;
		prc->top += (prc->bottom-prc->top)/2 + m_pstData->m_rcRealSize.top * ControlObjectGetSCALE(this);
		prc->bottom = prc->top + m_nHeight;
		break;
	case AlignMode_BottomMiddle:
		prc->left += (prc->right-prc->left)/2 + m_pstData->m_rcRealSize.left * ControlObjectGetSCALE(this);
		prc->right = prc->left + m_nWidth;
		prc->top = prc->bottom + m_pstData->m_rcRealSize.top * ControlObjectGetSCALE(this);
		prc->bottom = prc->top + m_nHeight;
		break;
	default:
		MESSAGE_BOX("类型超出范围!")
		break;
	}
	unguard;
}

void ControlObject::SetWidth( const int nW )
{
	guardfunc;
	assert( nW >= 0 );
	m_pstData->m_rcRealSize.right = m_pstData->m_rcRealSize.left + nW *ReciprocalGetSCALE(this);
    m_nWidth = nW;
	unguard;
}

void ControlObject::SetHeight( const int nH )
{
	guardfunc;
	assert( nH >= 0 );
	m_pstData->m_rcRealSize.bottom = m_pstData->m_rcRealSize.top + nH *ReciprocalGetSCALE(this);
    m_nHeight = nH;
	unguard;
}

void ControlObject::SetPos( const int nX, const int nY, bool bReal )
{
	guardfunc;
	RECT rc;
	if ( bReal )
	{
		GetRealRect( &rc );
        int w = m_pstData->m_rcRealSize.right - m_pstData->m_rcRealSize.left;
        int h = m_pstData->m_rcRealSize.bottom - m_pstData->m_rcRealSize.top;
		m_pstData->m_rcRealSize.left += nX - rc.left;
		m_pstData->m_rcRealSize.right = m_pstData->m_rcRealSize.left + w;
		m_pstData->m_rcRealSize.top +=  nY - rc.top;
		m_pstData->m_rcRealSize.bottom = m_pstData->m_rcRealSize.top + h;
	}
	else
	{
		//		GetFatherRect( &rc );
		GetRealRect( &rc );
		int w = m_pstData->m_rcRealSize.right - m_pstData->m_rcRealSize.left;
		int h = m_pstData->m_rcRealSize.bottom - m_pstData->m_rcRealSize.top;
		m_pstData->m_rcRealSize.left = /*rc.left + */nX;
		m_pstData->m_rcRealSize.right = m_pstData->m_rcRealSize.left + w;
		m_pstData->m_rcRealSize.top = /*rc.top + */nY;
		m_pstData->m_rcRealSize.bottom = m_pstData->m_rcRealSize.top + h;
	}
	if (GetFrameFather())
	{
		GetFrameFather()->SetRedraw();
	}
	
	unguard;
}

 void ControlObject::SetFather(ControlObject* pFather) 
{
	
	m_pFather = pFather; 

}
void ControlObject::SetScreenPos(int x, int y)
{
	RECT rc;
	GetRealRect( &rc );
	int w = m_pstData->m_rcRealSize.right - m_pstData->m_rcRealSize.left;
	int h = m_pstData->m_rcRealSize.bottom - m_pstData->m_rcRealSize.top;
	m_pstData->m_rcRealSize.left = x *ReciprocalGetSCALE(this);
	m_pstData->m_rcRealSize.right = m_pstData->m_rcRealSize.left + w;
	m_pstData->m_rcRealSize.top = y *ReciprocalGetSCALE(this);
	m_pstData->m_rcRealSize.bottom = m_pstData->m_rcRealSize.top + h;
	if (GetFrameFather())
	{
		GetFrameFather()->SetRedraw();
	}
// 	if (m_pstData->m_rcRealSize.right > 1280)
// 	{
// 		int v = m_pstData->m_rcRealSize.right - 1280;
// 		m_pstData->m_rcRealSize.left -= v;
// 		m_pstData->m_rcRealSize.right -= v;
// 	}
// 	if (m_pstData->m_rcRealSize.bottom > 960)
// 	{
// 		int v = m_pstData->m_rcRealSize.bottom - 960;
// 		m_pstData->m_rcRealSize.top -= v;
// 		m_pstData->m_rcRealSize.bottom -= v;
// 	}
}

void ControlObject::SetScreenPos(float x, float y)
{
	RECT rc;
	GetRealRect( &rc );
	int w = m_pstData->m_rcRealSize.right - m_pstData->m_rcRealSize.left;
	int h = m_pstData->m_rcRealSize.bottom - m_pstData->m_rcRealSize.top;
	m_pstData->m_rcRealSize.left = x *ReciprocalGetSCALE(this);
	m_pstData->m_rcRealSize.right = m_pstData->m_rcRealSize.left + w;
	m_pstData->m_rcRealSize.top = y *ReciprocalGetSCALE(this);
	m_pstData->m_rcRealSize.bottom = m_pstData->m_rcRealSize.top + h;
	if (GetFrameFather())
	{
		GetFrameFather()->SetRedraw();
	}
// 	if (m_pstData->m_rcRealSize.right > 1280)
// 	{
// 		int v = m_pstData->m_rcRealSize.right - 1280;
// 		m_pstData->m_rcRealSize.left -= v;
// 		m_pstData->m_rcRealSize.right -= v;
// 	}
// 	if (m_pstData->m_rcRealSize.bottom > 960)
// 	{
// 		int v = m_pstData->m_rcRealSize.bottom - 960;
// 		m_pstData->m_rcRealSize.top -= v;
// 		m_pstData->m_rcRealSize.bottom -= v;
// 	}
}

void ControlObject::SetXPos( const int nX )
{
	guardfunc;
	RECT rc;
	GetRealRect( &rc );
	int w = m_pstData->m_rcRealSize.right - m_pstData->m_rcRealSize.left;
	m_pstData->m_rcRealSize.left += (nX - rc.left)*ReciprocalGetSCALE(this);
	m_pstData->m_rcRealSize.right = m_pstData->m_rcRealSize.left + w;
	if (GetFrameFather())
	{
		GetFrameFather()->SetRedraw();
	}
	unguard;
}

void ControlObject::SetYPos( const int nY )
{
	guardfunc;
	RECT rc;
	GetRealRect( &rc );
	int h = m_pstData->m_rcRealSize.bottom - m_pstData->m_rcRealSize.top;
	m_pstData->m_rcRealSize.top +=  (nY - rc.top)*ReciprocalGetSCALE(this);
	m_pstData->m_rcRealSize.bottom = m_pstData->m_rcRealSize.top + h;
	if (GetFrameFather())
	{
		GetFrameFather()->SetRedraw();
	}
	unguard;
}

// added by zhuomeng.hu		[11/5/2010]
void ControlObject::SetAlpha( float fAlpha )
{
    guardfunc
    if( fAlpha > 1.0f )
        m_fAlpha = 1.0f;
    else if( fAlpha < 0.0f )
        m_fAlpha = 0.0f;
    else
        m_fAlpha = fAlpha;

    if( GetFrameFather() )
    {
        GetFrameFather()->SetRedraw();
    }
    unguard
}

float ControlObject::GetAlpha()
{
    guardfunc
    return m_fAlpha;
    unguard
}

void ControlObject::Run()
{
	guardfunc;
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
				if (m_pOnVisibleChanged)
				{
					m_pOnVisibleChanged( this );
				}
				m_nFadeCurColorA = m_nMinFade;
				m_bInFade = false;
			}
		}

		if ( !m_bInFade )
		{
			theUiManager.Compositor();
		}
		if(GetFrameFather())
		{
			GetFrameFather()->SetRedraw();
		}
	}
	unguard;
}


void ControlObject::SetMaxMinFade( const int nMaxFade, const int nMinFade )
{
	guardfunc;
	m_nMaxFade 	= nMaxFade;
	m_nMinFade  = nMinFade;
	unguard;
}

void ControlObject::Render()
{
	guardfunc;

    float oldMipmapLodBias = GetMe3dConfig()->GetMipLodBais();
    GetMe3dConfig()->SetMipLodBais( -1.0f );

	if( IsNeedRender() )
	{
		assert( m_pstData );

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



		if ( !m_strBackPicName.empty() && m_pstPic )
		{
			if (m_nPicId == -1)
			{
				theControlPictureManager.RegisterTexture(&m_nPicId,m_strBackPicName.c_str());
			}
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
			if( ( m_bVisable || m_bInFade ) && m_nFlashCurCount >= m_nFlashCount )
			//if( m_bVisable && m_nFlashCurCount >= m_nFlashCount )
			{

				// LeftTop
				D3DCOLOR dwColor = D3DCOLOR_ARGB( static_cast< int >( m_fAlpha * m_nFadeCurColorA ), 0xff, 0xff, 0xff );
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
			}

			//if( m_bFadeInorFadeOut )
			//{
			//	BitBlt( &m_nPicId, m_strBackPicName.c_str(),
			//		rcReal.left + m_nLeftTopW,
			//		rcReal.top + m_nLeftTopH,
			//		m_nWidth - m_nLeftW - m_nRightW,
			//		m_nHeight - m_nTopH - m_nBottomH,
			//		m_pstPic->m_rcClient.left, m_pstPic->m_rcClient.top,
			//		m_nMiddleW, m_nMiddleH,
			//		DrawModeStrectch,
			//		D3DCOLOR_ARGB( m_nFadeCurColorA, 0xff, 0xff, 0xff ) );
			//}

			// 闪动
			static int nLastFlashFactor = 1;
			
			if ( m_nFlashCurCount < m_nFlashCount )
			{
				int nCurrentFlashColorFactor = sin( ( HQ_TimeGetTime() - m_dwFlashStartTime ) * m_fFlashSpeed * 0.01f) * 0xff;
				if( nLastFlashFactor * nCurrentFlashColorFactor <= 0 )
					++m_nFlashCurCount;
				nLastFlashFactor = nCurrentFlashColorFactor;
					
				//m_nFlashCurColorA = UI_FLASH_SPEED*(HQ_TimeGetTime()-m_dwFlashStartTime)*0.1f;
				m_nFlashCurColorA =  abs( nCurrentFlashColorFactor );//-m_dwFlashStartTime);				

				////int nOffset = 0*m_nFlashCurColorA/0xff;
				//int nOffset = 0;
				//int nPicX = rcReal.left + m_nLeftTopW - nOffset;
				//int nPicY = rcReal.top + m_nLeftTopH - nOffset;
				//int nPicWidth = m_nWidth - m_nLeftW - m_nRightW + nOffset*2;
				//int nPicHeight = m_nHeight - m_nTopH - m_nBottomH + nOffset*2;

				BitBlt( &m_nPicId, NULL,
					rcReal.left+nLeftTopW, rcReal.top+nLeftTopH,
					w-nLeftW-nRightW, h-nTopH-nBottomH,
					m_pstPic->m_rcClient.left, m_pstPic->m_rcClient.top,
					m_nMiddleW, m_nMiddleH,
					m_pstData->m_nDrawMode[S_BaseData::Mode_Middle],
					D3DCOLOR_ARGB( m_nFlashCurColorA, 0xff, 0xff, 0xff ) );
				if (GetFrameFather())
				{
					GetFrameFather()->SetRedraw();
				}
			}
			//else if ( m_nFlashCount != 0 && m_nFlashCurCount == m_nFlashCount )
			//{
			//	if ( m_bFlashedAutoClose == true )
			//	{
			//		m_nFlashCurCount = 0;
			//		m_nFlashCount = 0;
			//		//SetVisable( false, false );
			//		SetVisable( false, m_bFlashFade );
			//	}
			//}

			if ( m_nFlashCount != 0 && m_nFlashCurCount == m_nFlashCount )
			{
				if ( m_bFlashedAutoClose == true )
				{
					m_nFlashCurCount = 0;
					m_nFlashCount = 0;
					SetVisable( false );
					SetFadeInorFadeOut(m_bFlashFade);
				}
			}
		}
		else
		{
		//	UiDrawer::FillRect2D( rcReal, m_colBackColor );
			if( m_bDrawFrame )
			{	
				RECT rtIn	=	{0},
					 rtOut	=	{0};
				SetRect( &rtOut, rcReal.left-2, rcReal.top, rcReal.right+4, rcReal.bottom );
				//Draw frame
				SetRect( &rtIn, rtOut.left+2, rtOut.top, rtOut.right-2, rtOut.bottom-2);	

				UiDrawer::DrawRect2D( rtOut, 0xff110000 );
				UiDrawer::DrawRect2D( rtIn, 0xFF888888 );	
			}
		}

#ifdef _DEBUG
		if ( IsActivated() )
		{
			UiDrawer::DrawRect2D( rcReal, 0x7f0000ff );
		}
		else if ( GetAsyncKeyState(VK_LCONTROL) )
		{
			UiDrawer::DrawRect2D( rcReal, 0xff00ff00 );
			if( GetFrameFather() )
				GetFrameFather()->SetRedraw();
		}
#endif
	}

    GetMe3dConfig()->SetMipLodBais( oldMipmapLodBias );

	unguard;
}

void ControlObject::BitBlt( IN OUT int* pPicId, IN const char* szPicName,
						   float nDstX, float nDstY,
						   float nDstWidth, float nDstHeight,
						   int nSrcX, int nSrcY,
						   int nSrcWidth, int nSrcHeight,
						   int nDrawMode, D3DCOLOR col )
{
//     assert( szPicName );
	guardfunc;
	if ( nDstWidth == 0 || nDstHeight == 0 ||
		nSrcWidth == 0 || nSrcHeight == 0 )
	{
		return;
	}

	RECT rcDst,rcSrc;
	switch( nDrawMode )
	{
	case DrawModeNormal:
		{
			rcDst.left = nDstX;
			rcDst.top = nDstY;
			rcDst.right = rcDst.left + nSrcWidth*ControlObjectGetSCALE(this)/*-1*/;
			rcDst.bottom = rcDst.top + nSrcHeight*ControlObjectGetSCALE(this)/*-1*/;
			rcSrc.left = nSrcX;
			rcSrc.top = nSrcY;
			rcSrc.right = rcSrc.left + nSrcWidth;
			rcSrc.bottom = rcSrc.top + nSrcHeight;
			theControlPictureManager.BitBlt( &m_nPicId, szPicName, &rcDst, &rcSrc, col, m_fBackPicZ, _renderFlag );
		}
		break;
	case DrawModeTile:
		{
            int dw = nDstWidth*ReciprocalGetSCALE(this);
            int dh = nDstHeight*ReciprocalGetSCALE(this);
			int nWCount = dw/nSrcWidth;
			int nHCount = dh/nSrcHeight;
			for( int h=0; h<nHCount; h++ )
			{
				for( int w=0; w<nWCount; w++ )
				{
					rcDst.left = nDstX+w*nSrcWidth*ControlObjectGetSCALE(this);
					rcDst.top = nDstY+h*nSrcHeight*ControlObjectGetSCALE(this);
					rcDst.right = rcDst.left + nSrcWidth*ControlObjectGetSCALE(this)/*-1*/;
					rcDst.bottom = rcDst.top + nSrcHeight*ControlObjectGetSCALE(this)/*-1*/;
					rcSrc.left = nSrcX;
					rcSrc.top = nSrcY;
					rcSrc.right = rcSrc.left + nSrcWidth;
					rcSrc.bottom = rcSrc.top + nSrcHeight;
					theControlPictureManager.BitBlt( &m_nPicId, szPicName, &rcDst, &rcSrc, col, m_fBackPicZ, _renderFlag );
				}
			}
			int nWSurplus = dw%nSrcWidth;
			int nHSurplus = dh%nSrcHeight;
			if ( nWSurplus != 0 )
			{
				for( int h=0; h<nHCount; h++ )
				{
					rcDst.left = nDstX+nWCount*nSrcWidth*ControlObjectGetSCALE(this);
					rcDst.top = nDstY+h*nSrcHeight*ControlObjectGetSCALE(this);
					rcDst.right = rcDst.left + nWSurplus*ControlObjectGetSCALE(this)/*-1*/;
					rcDst.bottom = rcDst.top + nSrcHeight*ControlObjectGetSCALE(this)/*-1*/;
					rcSrc.left = nSrcX;
					rcSrc.top = nSrcY;
					rcSrc.right = rcSrc.left + nWSurplus;
					rcSrc.bottom = rcSrc.top + nSrcHeight;
					theControlPictureManager.BitBlt( &m_nPicId, szPicName, &rcDst, &rcSrc, col, m_fBackPicZ, _renderFlag );
				}
			}
			if ( nHSurplus != 0 )
			{
				for( int w=0; w<nWCount; w++ )
				{
					rcDst.left = nDstX+w*nSrcWidth*ControlObjectGetSCALE(this);
					rcDst.top = nDstY+nHCount*nSrcHeight*ControlObjectGetSCALE(this);
					rcDst.right = rcDst.left + nSrcWidth*ControlObjectGetSCALE(this)/*-1*/;
					rcDst.bottom = rcDst.top + nHSurplus*ControlObjectGetSCALE(this)/*-1*/;
					rcSrc.left = nSrcX;
					rcSrc.top = nSrcY;
					rcSrc.right = rcSrc.left + nSrcWidth;
					rcSrc.bottom = rcSrc.top + nHSurplus;
					theControlPictureManager.BitBlt( &m_nPicId, szPicName, &rcDst, &rcSrc, col, m_fBackPicZ, _renderFlag );
				}
			}
			if ( nWSurplus != 0 && nHSurplus != 0 )
			{
				rcDst.left = nDstX+nWCount*nSrcWidth*ControlObjectGetSCALE(this);
				rcDst.top = nDstY+nHCount*nSrcHeight*ControlObjectGetSCALE(this);
				rcDst.right = rcDst.left + nWSurplus*ControlObjectGetSCALE(this)/*-1*/;
				rcDst.bottom = rcDst.top + nHSurplus*ControlObjectGetSCALE(this)/*-1*/;
				rcSrc.left = nSrcX;
				rcSrc.top = nSrcY;
				rcSrc.right = rcSrc.left + nWSurplus;
				rcSrc.bottom = rcSrc.top + nHSurplus;
				theControlPictureManager.BitBlt( &m_nPicId, szPicName, &rcDst, &rcSrc, col, m_fBackPicZ, _renderFlag );
			}
		}
		break;
	case DrawModeStrectch:
		{
			rcDst.left = nDstX;
			rcDst.top = nDstY;
			rcDst.right = rcDst.left + nDstWidth/*-1*/;
			rcDst.bottom = rcDst.top + nDstHeight/*-1*/;
			rcSrc.left = nSrcX;
			rcSrc.top = nSrcY;
			rcSrc.right = rcSrc.left + nSrcWidth;
			rcSrc.bottom = rcSrc.top + nSrcHeight;
			theControlPictureManager.BitBlt( &m_nPicId, szPicName, &rcDst, &rcSrc, col, m_fBackPicZ, _renderFlag );
		}
		break;
	default:
		assert( false );
		break;
	}
	unguard;
}

void ControlObject::InitUIData( IN ControlObject* pFather, IN S_BaseData* pData )
{
	guardfunc;
	if ( m_bNeedRelease == true )
	{
		assert( !m_pstData );
	}
	assert( pData );
	m_pFather = pFather;
	m_pstData = pData;
	if (m_pFather == NULL)
	{
		if (GetControlType() == Type_Frame)
		{
			m_pFrameFather = (ControlFrame *)this;
		}
	}
	else
	{
		m_pFrameFather = m_pFather->GetFrameFather();
	}

	m_pstData->m_colFont |= 0xff000000;
	if ( m_pstData->m_colFont == 0xffffffff )
	{
		m_pstData->m_colFont = 0xfffefefe;
	}

//	m_nFontIndex = theFontManager.CreateFont( pData->m_szFont, pData->m_nFontSize );
	if ( strlen(pData->m_szFont) > 0 && pData->m_nFontSize > 0 )
	{
//		m_nFontIndex = FontSystem::CreateFont( pData->m_szFont, pData->m_nFontSize );
		m_nDefaultFontSize = pData->m_nFontSize;
        //pData->m_nFontSize *= ControlObjectGetSCALE(this);
		int nFontSize = pData->m_nFontSize * ControlObjectGetREAL_SCALE(this);
		//## 
		m_nFontIndex = FontSystem::CreateFont( pData->m_szFont,
											nFontSize,
											0,
											/*pData->m_isFontBold ? FW_BOLD :*/ FW_NORMAL,
											1,
											FALSE,
											DEFAULT_CHARSET,
											CLIP_DEFAULT_PRECIS,
											ANTIALIASED_QUALITY,
											DEFAULT_PITCH|FF_DONTCARE,
											&m_hDC );
 	
	}

	m_nWidth = (m_pstData->m_rcRealSize.right - m_pstData->m_rcRealSize.left) * ControlObjectGetSCALE(this);
	m_nHeight = (m_pstData->m_rcRealSize.bottom - m_pstData->m_rcRealSize.top) * ControlObjectGetSCALE(this);
	SetPic( &m_pstData->m_stBackPic );
	unguard;
}

extern const char* GetRootPath();
void	ControlObject::SetPicName( const char* szPath )
{ 
	guardfunc;
	if(!szPath)
		return;

	if(m_pstPic) 
	{
		char fullname[MAX_PATH];
		char lwrpath[MAX_PATH];
		strcpy(lwrpath, szPath);
		strlwr(lwrpath);
		if( lwrpath[1] == ':' )
		{
			strcpy( fullname, szPath  );
		}
		else
		{
// 			if( (strstr(lwrpath, "ui\\") && !strstr(lwrpath, "data\\ui" ))
// 				|| (strstr(lwrpath, "ui/") && !strstr(lwrpath, "ui//") && !strstr(lwrpath, "data/ui" ))
// 				|| (strstr(lwrpath, "ui//") && !strstr(lwrpath, "data//ui" )))
// 				sprintf( fullname, "%s\\data\\%s", GetRootPath(), szPath );
// 			else
				sprintf( fullname, "%s\\%s", GetRootPath(), szPath );
		}
		if(stricmp(fullname,m_pstPic->m_szPicName) == 0)
			return;

		strncpy( m_pstPic->m_szPicName, fullname, MAX_PATH );
		ReleaseBackGroundPic();
		if (GetFrameFather())
		{
			GetFrameFather()->SetRedraw();
		}
		m_strBackPicName = m_pstPic->m_szPicName;
		
		theControlPictureManager.RegisterTexture( &m_nPicId, m_strBackPicName.c_str() );
	}
	unguard;
}

S_BaseData::S_Pic* ControlObject::GetPic( )
{
	return m_pstPic;
}

bool ControlObject::SetPic( IN S_BaseData::S_Pic *pPic, bool bCoverData )
{
	guardfunc;
	assert( pPic );
	if ( bCoverData == true )
	{
		if (GetFrameFather())
		{
			GetFrameFather()->SetRedraw();
		}
		*m_pstPic = *pPic;
	}
	else if ( m_pstPic != pPic )
	{
		if (GetFrameFather())
		{
			GetFrameFather()->SetRedraw();
		}
		m_pstPic = pPic;
	}
	else
	{
		return true;
	}

	if ( pPic->m_szPicName[0] != 0 )
	{
		m_strBackPicName = GetRootPath();
		m_strBackPicName += "\\data\\UI\\";
		m_strBackPicName += pPic->m_szPicName;
		//FILE	*fp = fopen( m_strBackPicName.c_str(), "r" );
		//if ( !fp )
		//{
		//	m_strBackPicName = "UI\\Common\\";
		//	m_strBackPicName += pPic->m_szPicName;
		//	fp = fopen( m_strBackPicName.c_str(), "r" );
		//	if ( !fp )
		//	{
		//		char szError[128];
		//		sprintf( szError, "载入文件失败:%s", pPic->m_szPicName );
		//		MESSAGE_BOX(szError)
		//	}
		//}
		//if (fp)	fclose(fp);
	}
	else
	{
		m_strBackPicName = "";
	}
	ReleaseBackGroundPic();
	
	m_nLeftW = pPic->m_rcClient.left - pPic->m_rcFrame.left;
	m_nLeftH = pPic->m_rcClient.bottom - pPic->m_rcClient.top;
	m_nTopW = pPic->m_rcClient.right - pPic->m_rcClient.left;
	m_nTopH = pPic->m_rcClient.top - pPic->m_rcFrame.top;
	m_nRightW = pPic->m_rcFrame.right - pPic->m_rcClient.right;
	m_nRightH = pPic->m_rcClient.bottom - pPic->m_rcClient.top;
	m_nBottomW = pPic->m_rcClient.right - pPic->m_rcClient.left;
	m_nBottomH = pPic->m_rcFrame.bottom - pPic->m_rcClient.bottom;
	m_nLeftTopW = pPic->m_rcClient.left - pPic->m_rcFrame.left;
	m_nLeftTopH = pPic->m_rcClient.top - pPic->m_rcFrame.top;
	m_nRightTopW = pPic->m_rcFrame.right - pPic->m_rcClient.right;
	m_nRightTopH = pPic->m_rcClient.top - pPic->m_rcFrame.top;
	m_nLeftBottomW = pPic->m_rcClient.left - pPic->m_rcFrame.left;
	m_nLeftBottomH = pPic->m_rcFrame.bottom - pPic->m_rcClient.bottom;
	m_nRightBottomW = pPic->m_rcFrame.right - pPic->m_rcClient.right;
	m_nRightBottomH = pPic->m_rcFrame.bottom - pPic->m_rcClient.bottom;
	m_nMiddleW = pPic->m_rcClient.right - pPic->m_rcClient.left;
	m_nMiddleH = pPic->m_rcClient.bottom - pPic->m_rcClient.top;

	theControlPictureManager.RegisterTexture( &m_nPicId, m_strBackPicName.c_str() );
	return true;

	unguard;
}

bool ControlObject::PtInObject( const int nX, const int nY ,bool bCheckMsgHold)
{
	guardfunc;
 	if (bCheckMsgHold && (m_bMsgHoldup == false ))
		return false;
	if ( IsVisable() )
	{
		RECT rc;
		GetRealRect( &rc );
		if ( nX >= rc.left && nX <= rc.right &&
			nY >= rc.top && nY <= rc.bottom )
		{
			return true;
		}
	}
	return false;
	unguard;
}
bool ControlObject::PtInObject( const RECT& rc, const int nX, const int nY)
{
	guardfunc;
	if(IsVisable())
	{
		if( m_bMsgHoldup == true )
		{
			if( nX >= rc.left && nX <= rc.right && nY >= rc.top && nY <= rc.bottom)
				return true;
		}
	}
	return false;
	unguard;
}
bool ControlObject::IsBeCovered( IN ControlObject* pCover )
{
	guardfunc;
	assert( pCover );
	if ( IsVisable() && pCover->IsVisable() )
	{
		RECT rcMe,rcCover;
		GetRealRect( &rcMe );
		pCover->GetRealRect( &rcCover );
		if ( rcCover.left <= rcMe.left &&
			rcCover.right >= rcMe.right &&
			rcCover.top <= rcMe.top &&
			rcCover.bottom >= rcMe.bottom )
		{
			return true;
		}
	}
	return false;
	unguard;
}

bool ControlObject::IsFadeInval()
{
	guardfunc;
	return m_bFadeInval;
	unguard;
}
// 设置是否可见/可用
void ControlObject::SetVisable( const bool bVisable)
{
    guardfunc;

    bool bChanged = m_bVisable != bVisable;
    if (!bChanged)
        return;

	if (GetFrameFather())
	{
		GetFrameFather()->SetRedraw();
	}
    m_bVisable = bVisable;
    if ( m_pOnVisibleChanged && bChanged )
    {
        m_pOnVisibleChanged( this );
    }
	
	if ( m_bFadeInorFadeOut)
	{
		if (bVisable)
		{
			m_nFadeCurColorA = 0;
		}
		else
		{
			m_nFadeCurColorA = 0xFF;
		}
		m_bInFade = true;
		m_dwFadeLastTime = HQ_TimeGetTime();
	}
	//
	//if ( m_bVisable == false )
	//{
	//	theUiManager.Compositor();
	//}
	if( m_bVisable )
	{
		theUiManager.ToTop( this );
	}
	theUiManager.Compositor();

	unguard;
}

void ControlObject::SetActivate( const bool bActivate )
{
	guardfunc;
	if ( bActivate == true )
	{
		theUiManager.SetFocus(this);
	}
	else if ( IsActivated() )
	{
		theUiManager.SetFocus(NULL);
	}
	unguard;
}

bool ControlObject::IsActivated()
{
	guardfunc;
	return theUiManager.GetFocus() == this;
	unguard;
}

void ControlObject::StartFlash( const int nFlashCount, const bool bAutoClose, const bool bFadeIn )
{
	guardfunc;
	// added, jiayi, [2009/6/26]
	if( !m_nFlashCurCount )//not flashing	
		m_dwFlashStartTime = HQ_TimeGetTime();		
	
	m_nFlashCount = nFlashCount;
	m_nFlashCurCount = 0;
	m_bFlashedAutoClose = bAutoClose;
	m_bFlashFade = bFadeIn;
	if (GetFrameFather())
	{
		GetFrameFather()->SetRedraw();
	}
	unguard;
}

bool ControlObject::IsNeedRender()
{
	guardfunc;
	return IsVisable() || m_bInFade == true;
	unguard;
}

void ControlObject::MoveTo( const int nX, const int nY )
{
	guardfunc;
	m_dwMoveStartTime = HQ_TimeGetTime();
	m_bMoving = true;
	m_nMoveToX = nX;
	m_nMoveToY = nY;
	unguard;
}

//设置淡入淡出效果对次对象是否有效
void ControlObject::SetFadeInval( bool bInval )
{
	guardfunc;
	m_bFadeInval	=	bInval;
	unguard;
}

bool ControlObject::MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	guardfunc;
	if ( m_pOnMsgProc )
	{
		return m_pOnMsgProc( msg, wParam, lParam, bMsgUsed );
	}
	else if (m_pOnMsgProc2)
	{
		return m_pOnMsgProc2( msg, wParam, lParam, bMsgUsed ,this);
	}
	return false;
	unguard;
}

void ControlObject::SetRealRect( IN const RECT* prc )
{
	guardfunc;
	m_pstData->m_rcRealSize = *prc;
	m_nWidth = (m_pstData->m_rcRealSize.right - m_pstData->m_rcRealSize.left) * ControlObjectGetSCALE(this);
	m_nHeight = (m_pstData->m_rcRealSize.bottom - m_pstData->m_rcRealSize.top) * ControlObjectGetSCALE(this);
	unguard;
}

bool ControlObject::PlaySound()
{
	guardfunc;
	return theUiManager.PlaySound( m_strSound );
	unguard;

}

void ControlObject::SetFont( const ControlObject* pSrc )
{
	if ( !pSrc )
	{
		return;
	}
	m_nFontIndex = pSrc->m_nFontIndex;
	m_hDC = pSrc->m_hDC;
	m_pstData->m_nFontSize = pSrc->m_pstData->m_nFontSize;
}

void ControlObject::ResetDevice()
{
	if ( strlen(m_pstData->m_szFont) > 0 && m_pstData->m_nFontSize > 0 )
	{
		int nFontSize = m_nDefaultFontSize * ControlObjectGetREAL_SCALE(this);
		//##
		m_nFontIndex = FontSystem::CreateFont( m_pstData->m_szFont,
			nFontSize,
			0,
			/*m_pstData->m_isFontBold ? FW_BOLD :*/ FW_NORMAL,
			1,
			FALSE,
			DEFAULT_CHARSET,
			CLIP_DEFAULT_PRECIS,
			ANTIALIASED_QUALITY,
			DEFAULT_PITCH|FF_DONTCARE,
			&m_hDC );


	}

	m_nWidth = (m_pstData->m_rcRealSize.right - m_pstData->m_rcRealSize.left) * ControlObjectGetSCALE(this);
	m_nHeight = (m_pstData->m_rcRealSize.bottom - m_pstData->m_rcRealSize.top) * ControlObjectGetSCALE(this);
}

void ControlObject::LostDevice()
{

}

void ControlObject::SetEnable( bool b )
{
	if (m_bEnable == b)
		return;

	m_bEnable = b;
	if ( m_bEnable )
		SetPic( &m_pstData->m_stBackPic );
	else
		SetPic( &m_pstData->m_stDisablePic );
}

ControlHelper::ControlHelper()
{
	m_Analysis = 0;
}

ControlHelper::~ControlHelper()
{
	if( m_Analysis )
		ScriptStringFree( &m_Analysis );
}

bool ControlHelper::Analyse(const std::wstring &text, HDC fontHDC)
{
	if (text == m_AnalysisText)
		return true;

	m_AnalysisText = text.c_str();

	if( m_Analysis )
		ScriptStringFree( &m_Analysis );

	SCRIPT_CONTROL ScriptControl; // For uniscribe
	SCRIPT_STATE   ScriptState;   // For uniscribe
	ZeroMemory( &ScriptControl, sizeof(ScriptControl) );
	ZeroMemory( &ScriptState, sizeof(ScriptState) );
	ScriptApplyDigitSubstitution ( NULL, &ScriptControl, &ScriptState );

	HRESULT hr = ScriptStringAnalyse( fontHDC,
		m_AnalysisText.c_str(),
		m_AnalysisText.length() + 1,  // NULL is also analyzed.
		m_AnalysisText.length() * 3 / 2 + 16,
		-1,
		SSA_BREAK | SSA_GLYPHS | SSA_FALLBACK | SSA_LINK,
		0,
		&ScriptControl,
		&ScriptState,
		NULL,
		NULL,
		NULL,
		&m_Analysis );
	return hr == S_OK;
}

//## add by pyj
int ControlHelper::GetTextWidth(const std::wstring& text, HDC fontHDC, int startCharIndex, int endCharIndex,ControlObject* pObject, int nFontIndex)
{
	if( text.length() == 0 )
		return 0;

	if (FontSystem::IsUseNewFont())
	{
		int width=FontSystem::GetTextWidth(nFontIndex, text, startCharIndex, endCharIndex, false);
		return width;
	}
	else
	{
		if (Analyse(text, fontHDC))
		{
			int s = 0;
			int e = 0;
			HRESULT hr;
			hr = ScriptStringCPtoX( m_Analysis, startCharIndex, FALSE, &s );
			hr = ScriptStringCPtoX( m_Analysis, endCharIndex, FALSE, &e );
			return (e - s) * ControlObjectGetREAL_SCALE(pObject);
		}
	}

	return 0;
}

int ControlHelper::GetTextWidth(const std::wstring &text, HDC fontHDC, int startCharIndex, int endCharIndex,ControlObject* pObject)
{
	assert(false&&"please use new GetTextWidth()");

    if( text.length() == 0 )
        return 0;

	if (Analyse(text, fontHDC))
	{
		int s = 0;
		int e = 0;
		HRESULT hr;
		hr = ScriptStringCPtoX( m_Analysis, startCharIndex, FALSE, &s );
		hr = ScriptStringCPtoX( m_Analysis, endCharIndex, FALSE, &e );
		return (e - s) * ControlObjectGetREAL_SCALE(pObject);
	}

	return 0;
}

ControlGroup::ControlGroup()
{
	m_isVisible = false;
}

ControlGroup::~ControlGroup()
{
}

void ControlGroup::AddControl(ControlObject* pControl)
{
    if( pControl )
	    m_vecControl.push_back(pControl);
}

void ControlGroup::SetVisible(bool v)
{
	m_isVisible = v;
	for (int i = 0; i < m_vecControl.size(); ++i)
	{
		m_vecControl[i]->SetVisable(v);
	}
}

void ControlGroup::Clear()
{
	m_vecControl.clear();
}


float ControlObject::GetSCALE( ControlObject* pObject )
{
	if ( !pObject )
	{
		return UI_SCALE*UI_Adjust_SCALE;
	}
	if (/*!pObject ||*/ !pObject->GetFrameFather())
	{
		return UI_SCALE;
	}
	if (pObject->GetFrameFather()->IsSolidScale())
	{
		return UI_SCALE;
	}
	else
	{
		return UI_SCALE*UI_Adjust_SCALE;
	}
}

float ControlObject::GetREAL_SCALE( ControlObject* pObject )
{
	if ( !pObject )
	{
		return UI_REAL_SCALE*UI_Adjust_SCALE;
	}
	if (/*!pObject ||*/ !pObject->GetFrameFather())
	{
		return UI_REAL_SCALE;
	}
	if (pObject->GetFrameFather()->IsSolidScale())
	{
		return UI_REAL_SCALE;
	}
	else
	{
		return UI_REAL_SCALE*UI_Adjust_SCALE;
	}

}

void ControlObject::ReleaseBackGroundPic()
{
	if ( m_nPicId != -1 )
	{
		theControlPictureManager.UnregisterTexture( m_nPicId );
		m_nPicId = -1;
	}
}


bool ControlObject::IsMouseInUI( const int nX, const int nY )
{
	return ControlObject::PtInObject(nX,nY,true);
}

