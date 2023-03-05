#include "StdAfx.h"
#include "ScrollBarExControl.h"

CScrollBarExControl::CScrollBarExControl(void)
{
	m_nType = Type_ScrollBarEx;

	m_nWidth = 70;
	m_nHeight = 12;

	m_btnUp.m_nWidth = m_nHeight;
	m_btnUp.m_nHeight = m_nHeight;

	m_btnDown.m_nWidth = m_nHeight;
	m_btnDown.m_nHeight = m_nHeight;

	m_btnBar.m_nWidth = m_nHeight;
	m_btnBar.m_nHeight = m_nHeight;

	m_strID.Format( "ID_SCROLLBAREX_%d", rand() );
}

CScrollBarExControl::~CScrollBarExControl(void)
{
}

void CScrollBarExControl::OnSize()
{
	if ( m_nWidth < 3*m_nHeight )
	{
		m_nWidth = 3*m_nHeight;
	}
	//m_btnUp.m_nWidth = m_nHeight;
	//m_btnUp.m_nHeight = m_nHeight;

	m_btnDown.m_nOffsetX = m_nWidth-m_nHeight;
	//m_btnDown.m_nWidth = m_nHeight;
	//m_btnDown.m_nHeight = m_nHeight;

	m_btnBar.m_nOffsetX = m_nWidth/2-m_nHeight/2;
	//m_btnBar.m_nWidth = m_nHeight;
	//m_btnBar.m_nHeight = m_nHeight;
}

