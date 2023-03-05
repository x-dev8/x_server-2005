#include "StdAfx.h"
#include "progresscontrol.h"

CProgressControl::CProgressControl(void)
{
	m_nType = Type_Progress;

	m_nWidth = 200;
	m_nHeight = 15;
	m_strID.Format( "ID_PROGRESS_%d", rand() );
}

CProgressControl::~CProgressControl(void)
{
}
