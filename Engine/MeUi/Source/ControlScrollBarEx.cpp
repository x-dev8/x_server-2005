#include "MeUi/ControlScrollBarEx.h"
#include "MeUi/UiManager.h"
#include "MeFont/MeFontSystem.h"  //##

ControlScrollBarEx::ControlScrollBarEx(void) :
m_bDrawValueText( false ),
m_bDrawInCustom( false ),
m_nCustomValue( -1 )
{
}

ControlScrollBarEx::~ControlScrollBarEx(void)
{
}

void ControlScrollBarEx::Render()
{
	if ( IsNeedRender() )
	{
		RECT oldRC = m_pstData->m_rcRealSize;
		RECT newRC = oldRC;
		newRC.left = newRC.left + m_btnUp.GetData()->m_rcRealSize.right - m_btnUp.GetData()->m_rcRealSize.left;
		newRC.right = newRC.right - (m_btnDonw.GetData()->m_rcRealSize.right - m_btnDonw.GetData()->m_rcRealSize.left);
		ControlObject::SetRealRect(&newRC);
		ControlObject::Render();
		ControlObject::SetRealRect(&oldRC);

		m_btnUp.Render();
		m_btnDonw.Render();
		if (m_bEnable)
			m_btnBar.Render();

		if( m_btnBar.IsDrag() && m_bDrawValueText )
		{
			DrawValueText( m_nValue );
		}
	}
}

bool ControlScrollBarEx::OnMouseMove( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() && m_bEnable)
	{
		bool bUse = false;
		if ( m_btnUp.OnMouseMove( nFlags, nX, nY ) == true )
		{
			bUse = true;
		}
		if ( m_btnDonw.OnMouseMove( nFlags, nX, nY ) == true )
		{
			bUse = true;
		}
		if ( m_btnBar.OnMouseMove( nFlags, nX, nY ) == true )
		{
			bUse = true;
		}
		if ( m_btnBar.IsDrag() )
		{
			RECT rc;
			GetRealRect( &rc );
			int n = m_nWidth-(m_btnUp.m_nWidth + m_btnDonw.m_nWidth + m_btnBar.m_nWidth);
			if( n == 0 ) //除以0是危险的
			{				
				return true;
			}
			int x = m_ptBarPos.x + nX - m_ptMousePos.x;
			if (x < rc.left + m_btnUp.m_nWidth)
				x = rc.left + m_btnUp.m_nWidth;
			else if ( x > rc.right - (m_btnDonw.m_nWidth + m_btnBar.m_nWidth))
				x = rc.right - (m_btnDonw.m_nWidth + m_btnBar.m_nWidth);
			m_btnBar.SetXPos(x);

			int pos = x - rc.left - m_btnUp.m_nWidth;
			int nValue = pos*m_nMaxValue/n;

			// 计算当前值所在的位置是否靠右边
			int w = n / m_nMaxValue;
			int d = pos - nValue * w;
			if (d > w * 0.5f)
				++nValue;

			if (nValue == m_nValue)
				return true;

			m_nValue = nValue;

			if( m_nValue < 0 ) m_nValue = 0;
			else if( m_nValue > m_nMaxValue ) m_nValue = m_nMaxValue;

			if ( m_pFunUpdatePos )
			{
				m_pFunUpdatePos( this, m_nValue );
			}

			//m_nValue = (nX - rc.left - m_nHeight)*m_nMaxValue/n;
			//OnUpdatePos();
			bUse = true;
			//
			static DWORD dwLastTime = 0;
			DWORD dwCurTime = timeGetTime();
			if ( dwCurTime - dwLastTime >= 500 )
			{
				dwLastTime = dwCurTime;
				PlaySound();
			}
		}
		return bUse;
	}
	return false;
}

bool ControlScrollBarEx::OnLButtonDown( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() && m_bEnable )
	{
		if ( m_btnBar.OnLButtonDown( nFlags, nX, nY ) == true )
		{
			m_bLButtonDrag = true;
			RECT rc;
			m_btnBar.GetRealRect(&rc);
			m_ptBarPos.x = rc.left;
			m_ptBarPos.y = rc.top;
			m_ptMousePos.x = nX;
			m_ptMousePos.y = nY;
		}
		else if ( m_btnDonw.OnLButtonDown( nFlags, nX, nY ) == true )
		{
			m_nValue += m_nStepValue;
		}
		else 		if ( m_btnUp.OnLButtonDown( nFlags, nX, nY ) == true )
		{
			m_nValue -= m_nStepValue;
		}
		else if ( PtInObject( nX, nY ,true) == true )
		{
			RECT rc;
			GetRealRect( &rc );
			int n = m_nWidth-(m_btnUp.m_nWidth + m_btnDonw.m_nWidth + m_btnBar.m_nWidth);
			int nValue = (nX - rc.left - m_btnUp.m_nWidth)*m_nMaxValue/n;
			if ( nValue > m_nValue )	m_nValue += m_nStepValue * 3;
			else						m_nValue -= m_nStepValue * 3;
			SetActivate();
		}
		else
		{
			return false;
		}

		OnUpdatePos();
		return m_bMsgHoldup;
	}
	return false;
}

void ControlScrollBarEx::OnUpdatePos()
{
	if( m_nValue < 0 ) m_nValue = 0;
	if( m_nValue > m_nMaxValue ) m_nValue = m_nMaxValue;
    int nX = 0;
    if(m_nMaxValue != 0)
    {
		nX = (m_nWidth - (m_btnUp.m_nWidth + m_btnDonw.m_nWidth + m_btnBar.m_nWidth))*m_nValue/m_nMaxValue+m_btnUp.m_nWidth;
    }
	RECT rc;
	GetRealRect( &rc );
	m_btnBar.SetXPos( rc.left+nX );

	if ( m_pFunUpdatePos )
	{
		m_pFunUpdatePos( this, m_nValue );
	}
#ifdef _DEBUG
	else if ( m_debug_bHasWarning )
	{
		char szDebug[128];
		char szFatherID[128] = "";
		if ( m_pFather )
		{
			strcpy( szFatherID, m_pFather->GetControlID() );
		}
		sprintf(szDebug,"[%s]::[%s] OnUpdatePos(int n) not defend!!\r\n", szFatherID, GetControlID() );
		//OutputDebugString(szDebug);
	}
#endif
}

void ControlScrollBarEx::DrawValueText( int nValue )
{
	int nOffsetY = m_btnBar.GetFontSize() * ControlObjectGetREAL_SCALE(this);
	RECT rc;
	m_btnBar.GetRealRect( &rc );
	rc.left -= 100;
	rc.bottom = rc.top;
	rc.top -= nOffsetY;
	rc.right += 100;	
	char szValue[256];
	if( m_bDrawInCustom )
		sprintf_s( szValue, 256, "%d%s", m_nCustomValue, m_pstData->m_szCaption );
	else
		sprintf_s( szValue, 256, "%d%s", nValue, m_pstData->m_szCaption );
	FontSystem::DrawText( szValue, &rc, DT_CENTER | DT_NOCLIP,
		m_btnBar.GetFontColor(), m_btnBar.GetFontIndex() );
}