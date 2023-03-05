#include "frameratecontrollor.h"
//#include "wkCore.h"
//#define new WKNEW


CFramerateControllor::CFramerateControllor(void)
{
	m_dwLastCheck = 0;
	m_iFrameCost = 30;
}

CFramerateControllor::~CFramerateControllor(void)
{
}

void CFramerateControllor::Control(void)
{
    while (GetTickCount() - m_dwLastCheck < (DWORD)m_iFrameCost)
    {
        Sleep(1);
    }
    m_dwLastCheck = GetTickCount();
	//DWORD dwTick = GetTickCount();
	//dwTick -= m_dwLastCheck;
	//if( (int)dwTick < m_iFrameCost )
	//{
	//	Sleep( m_iFrameCost - dwTick );		
	//}
	//m_dwLastCheck = GetTickCount();
}