#pragma once

#include <windows.h>

//����ִ��Ƶ��
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
