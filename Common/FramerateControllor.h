#pragma once

#include <windows.h>

//¿ØÖÆÖ´ÐÐÆµÂÊ
class CFramerateControllor
{
	int			m_iFrameCost;
	DWORD		m_dwLastCheck;
public:
	CFramerateControllor(void);
	~CFramerateControllor(void);

	void Control(void);
	void SetFramerate( int iFramerate ){ m_iFrameCost = 1000/iFramerate; };

};
