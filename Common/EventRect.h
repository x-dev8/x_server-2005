#ifndef _eventrect_h
#define _eventrect_h

#include <windows.h>

class I_EventRect:public RECT
{
public:
	//virtual void		SetTrigger( BYTE* pBuffer ){}
	virtual DWORD		Process( DWORD dwTime, BYTE* pBuffer ){ return 0; }
	virtual BOOL		IsEnd(){ return TRUE; }
};


class CEventRectManager
{

};

#endif