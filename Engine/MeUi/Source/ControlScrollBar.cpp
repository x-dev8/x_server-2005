#include "MeUi/ControlScrollBar.h"
#include "MeUi/UiManager.h"

ControlScrollBar::ControlScrollBar(void)
{
	m_nValue = 0;
	m_pFunUpdatePos = NULL;
	m_bLButtonDrag = false;
	m_bEnable	= true;
	m_nMaxValue = 1000;
	m_nStepValue = 100;
    m_nPageSize = 1000;
	//
	m_strSound = UiManager::m_strScrollBarSound;
}

ControlScrollBar::~ControlScrollBar(void)
{
}

void ControlScrollBar::Render()
{
	if ( IsNeedRender() )
	{
		ControlObject::Render();
		m_btnUp.Render();
		m_btnDonw.Render();
		if (m_bEnable)
			m_btnBar.Render();
	}
}

void ControlScrollBar::InitUIData( IN ControlObject* pFather, IN S_BaseData* pData )
{
	ControlObject::InitUIData( pFather, pData );
	m_btnUp.InitUIData( this, &((S_ScrollBarData*)pData)->m_stUp);
	m_btnDonw.InitUIData( this, &((S_ScrollBarData*)pData)->m_stDown);
	m_btnBar.InitUIData( this, &((S_ScrollBarData*)pData)->m_stBar );
	OnUpdatePos();

#ifdef _DEBUG
	m_btnUp.m_debug_bHasWarning = false;
	m_btnDonw.m_debug_bHasWarning = false;
	m_btnBar.m_debug_bHasWarning = false;
#endif
}

bool ControlScrollBar::OnMouseMove( UINT nFlags, const int nX, const int nY )
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
			int n = m_nHeight-(m_btnUp.m_nHeight + m_btnDonw.m_nHeight + m_btnBar.m_nHeight);
			if( n == 0 ) //除以0是危险的
			{
				return true;
			}			

			int y = m_ptBarPos.y + nY - m_ptMousePos.y;
			if (y < rc.top + m_btnUp.m_nHeight)
				y = rc.top + m_nWidth;
			else if ( y > rc.bottom - (m_btnDonw.m_nHeight + m_btnBar.m_nHeight))
				y = rc.bottom - (m_btnDonw.m_nHeight + m_btnBar.m_nHeight);
			m_btnBar.SetYPos(y);
			
			int pos = y - rc.top - m_btnUp.m_nHeight;
			int nValue = pos*m_nMaxValue/n;

			// 计算当前值所在的位置是否靠下边
			int w = n / m_nMaxValue;
			int d = pos - nValue * w;
			if (d > w * 0.5f)
				++nValue;

			//修改一下移动的value值，每次的数值都可以整除m_nStepValue by vvx 2012.11.15
			int nTemp = nValue%m_nStepValue;
			if (nTemp != 0)
			{
				if (nValue < m_nStepValue)
				{
					nValue = m_nStepValue;
				}
				else
				{
					int nTemp_value = nValue/m_nStepValue;
					nValue = (nTemp_value+1)*m_nStepValue;
				}
			}
			//////////////////////////////////////////////////////////////
			if (nValue == m_nValue)
				return true;

			m_nValue = nValue;

			if( m_nValue < 0 ) m_nValue = 0;
			else if( m_nValue > m_nMaxValue ) m_nValue = m_nMaxValue;

			if ( m_pFunUpdatePos )
			{
				m_pFunUpdatePos( this, m_nValue );
			}

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

bool ControlScrollBar::OnLButtonDown( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() && m_bEnable )
	{
		if ( m_btnUp.OnLButtonDown( nFlags, nX, nY ) == true )
		{
			m_nValue -= m_nStepValue;
			if (m_nValue < 0)
			{
				m_nValue = 0;
			}
		}
		else if ( m_btnDonw.OnLButtonDown( nFlags, nX, nY ) == true )
		{
			m_nValue += m_nStepValue;
			if (m_nValue > m_nMaxValue )
			{
				m_nValue = m_nMaxValue;
			}
		}
		else if ( m_btnBar.OnLButtonDown( nFlags, nX, nY ) == true )
		{
			m_bLButtonDrag = true;
			RECT rc;
			m_btnBar.GetRealRect(&rc);
			m_ptBarPos.x = rc.left;
			m_ptBarPos.y = rc.top;
			m_ptMousePos.x = nX;
			m_ptMousePos.y = nY;

		}
		else if ( PtInObject( nX, nY ,true) == true )
		{
			RECT rc;
			GetRealRect( &rc );
			int n = m_nHeight-(m_btnUp.m_nHeight + m_btnDonw.m_nHeight + m_btnBar.m_nHeight);
			int nValue = (nY - rc.top - m_btnUp.m_nHeight)*m_nMaxValue/n;
			if ( nValue > m_nValue )
			{
				m_nValue += m_nPageSize - 1;//m_nValue += 3*m_nStepValue;
				if (m_nValue > m_nMaxValue )
				{
					m_nValue = m_nMaxValue ;
				}
			}
			else						
			{
				m_nValue -= m_nPageSize - 1;//m_nValue -= 3*m_nStepValue;
				if (m_nValue < 0)
				{
					m_nValue = 0;
				}
			}
			SetActivate();
		}
		else
		{
			return false;
		}

		//OnUpdatePos();
		return m_bMsgHoldup;
	}
	return false;
}

bool ControlScrollBar::OnLButtonUp( UINT nFlags, const int nX, const int nY )
{
    m_bLButtonDrag = false;
	if ( IsVisable() && m_bEnable)
	{
		m_btnUp.OnLButtonUp( nFlags, nX, nY );
        m_btnDonw.OnLButtonUp( nFlags, nX, nY );
        m_btnBar.OnLButtonUp( nFlags, nX, nY );
		OnUpdatePos();
		return PtInObject( nX, nY ,true);
	}
	return false;
}

void ControlScrollBar::OnUpdatePos()
{
	if (m_nMaxValue < 1)
		return;
	if( m_nValue < 0 ) m_nValue = 0;
	if( m_nValue > m_nMaxValue ) m_nValue = m_nMaxValue;
	int nY = (m_nHeight-(m_btnUp.m_nHeight + m_btnDonw.m_nHeight + m_btnBar.m_nHeight))*m_nValue/m_nMaxValue+m_btnUp.m_nHeight;
	RECT rc;
	GetRealRect( &rc );
	m_btnBar.SetYPos( rc.top+nY );

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
void ControlScrollBar::ResetDevice()
{
	ControlObject::ResetDevice();
	m_btnUp.ResetDevice();
	m_btnDonw.ResetDevice();
	m_btnBar.ResetDevice();
}

void ControlScrollBar::SetRealRect( const RECT* prc )
{
	ControlObject::SetRealRect(prc);

	RECT rc = m_btnUp.GetData()->m_rcRealSize;
	int h = m_btnUp.GetData()->m_rcRealSize.bottom - m_btnUp.GetData()->m_rcRealSize.top;
	rc.top = m_pstData->m_rcRealSize.top;
	rc.bottom = rc.top + h;
	m_btnUp.SetRealRect(&rc);

	rc = m_btnDonw.GetData()->m_rcRealSize;
	h = m_btnDonw.GetData()->m_rcRealSize.bottom - m_btnDonw.GetData()->m_rcRealSize.top;
	rc.top = m_pstData->m_rcRealSize.bottom - h;
	rc.bottom = m_pstData->m_rcRealSize.bottom;
	m_btnDonw.SetRealRect(&rc);

	rc = m_btnBar.GetData()->m_rcRealSize;
	h = m_btnBar.GetData()->m_rcRealSize.bottom - m_btnBar.GetData()->m_rcRealSize.top;
	rc.top = m_pstData->m_rcRealSize.bottom - h;
	rc.bottom = m_pstData->m_rcRealSize.bottom;
	m_btnBar.SetRealRect(&rc);

	OnUpdatePos();

	//rc = m_btnBar.GetData()->m_rcRealSize;
	//rc.top = m_btnUp.GetData()->m_rcRealSize.bottom;
	//rc.bottom = m_btnDonw.GetData()->m_rcRealSize.top;
	//m_btnBar.SetRealRect(&rc);
}

void ControlScrollBar::FocusOut()
{
	m_btnBar.SetDrag(false);
}

void ControlScrollBar::SetValue( const int n )
{
	if (m_nValue == n)
	{
		return;
	}
	m_nValue = n; 
	if (m_nValue < 0)
	{
		m_nValue = 0;
	}
	if (m_nValue > m_nMaxValue)
	{
		m_nMaxValue = m_nValue;
	}
	OnUpdatePos();
}

void ControlScrollBar::Clear()
{
	m_nValue = 0;
	m_nMaxValue = 1000;
	m_nStepValue = 100;
	m_nPageSize = 1000;
}