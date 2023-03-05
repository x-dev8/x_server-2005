#include "StdAfx.h"
#include "picmgr.h"
#include <assert.h>

CPicMgr thePicMgr;

CPicMgr::CPicMgr(void)
{
}

CPicMgr::~CPicMgr(void)
{
	Clear();
}

void CPicMgr::Clear()
{
	for( UINT n=0; n<m_vtPic.size(); n++ )
	{
		delete m_vtPic[n];
		m_vtPic[n] = NULL;
	}
	m_vtPic.clear();
}

CDC* CPicMgr::GetDC( const char* pszPicName, CDC* pDC )
{
	for( UINT n=0; n<m_vtPic.size(); n++ )
	{
		if ( m_vtPic[n]->m_Graphics.GetFileName() == pszPicName )
		{
			return &m_vtPic[n]->m_DC;
		}
	}
	S_Pic *pPic = new S_Pic;
	pPic->m_Graphics.LoadTGAFile( pszPicName );
	pPic->m_DC.CreateCompatibleDC(pDC);
	SelectObject( pPic->m_DC, pPic->m_Graphics.GetBitmap() );
	m_vtPic.push_back( pPic );
	int nIndex = (int)m_vtPic.size() - 1;
	assert( nIndex >= 0 );
	return &m_vtPic[nIndex]->m_DC;
}

