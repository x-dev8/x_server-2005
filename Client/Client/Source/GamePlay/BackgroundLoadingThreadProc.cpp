#include "BackgroundLoadingThreadProc.h"

//////////////////////////////////////////////////////////////////////////
BackgoundLoadingThreadProc::BackgoundLoadingThreadProc()
{
	m_pfThreadProc = 0;
}
//////////////////////////////////////////////////////////////////////////
BackgoundLoadingThreadProc::BackgoundLoadingThreadProc( funcThreadProc pf )
{
	m_pfThreadProc = pf;
}
//////////////////////////////////////////////////////////////////////////
BackgoundLoadingThreadProc::~BackgoundLoadingThreadProc()
{
}
//////////////////////////////////////////////////////////////////////////
void BackgoundLoadingThreadProc::ThreadProcedure()
{
	if( m_pfThreadProc )
		m_pfThreadProc();
}
//////////////////////////////////////////////////////////////////////////
void BackgoundLoadingThreadProc::WaitForComplete()
{

}
//////////////////////////////////////////////////////////////////////////
void BackgoundLoadingThreadProc::Destroy()
{
	m_pfThreadProc = 0;
}
//////////////////////////////////////////////////////////////////////////