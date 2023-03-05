#include "MeUi/ControlTab.h"
#include <assert.h>

ControlTab::ControlTab(void)
{
	m_nCurSelFrame = 0;
}

ControlTab::~ControlTab(void)
{
}


void ControlTab::Render()
{
	if ( IsNeedRender() )
	{
		ControlObject::Render();
		for ( int n=0; n<((S_TabData*)m_pstData)->m_nTabCount; n++ )
		{
			m_btnTab[n].Render();
		}
		m_frameTab[m_nCurSelFrame].Render();
	}
}

void ControlTab::InitUIData( IN ControlObject* pFather, IN S_BaseData* pData )
{
	ControlObject::InitUIData( pFather, pData );

	S_TabData* pTabData = (S_TabData*)pData;

	m_frame.InitUIData( this, &pTabData->m_frame );
	for ( int n=0; n<pTabData->m_nTabCount; n++ )
	{
		m_btnTab[n].InitUIData( this, &pTabData->m_btnTab[n] );
//		if ( m_frameTab[n].LoadUIFormFile( pTabData->m_szFrameFileName[n], &m_frame ) == 0 )
//		{
//#ifdef _DEBUG
//			char szError[128];
//			sprintf( szError, "找不到文件:%s", pTabData->m_szFrameFileName[n] );
//			MESSAGE_BOX(szError)
//#endif
//		}
	}
	m_btnTab[0].SetPressPic();
}

bool ControlTab::OnLButtonDown( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() )
	{
		for ( int n=0; n<((S_TabData*)m_pstData)->m_nTabCount; n++ )
		{
			if ( m_btnTab[n].OnLButtonDown( nFlags, nX, nY ) == true )
			{
				m_nCurSelFrame = n;
				OnFrameChange();
				return m_bMsgHoldup;
			}
		}
		if ( m_frameTab[m_nCurSelFrame].OnLButtonDown( nFlags, nX, nY ) == true )
		{
			return m_bMsgHoldup;
		}
	}
	return false;
}

bool ControlTab::OnRButtonDown( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() )
	{
		if ( m_frameTab[m_nCurSelFrame].OnRButtonDown( nFlags, nX, nY ) == true )
		{
			return m_bMsgHoldup;
		}
	}
	return false;
}

bool ControlTab::OnChar( UINT nChar )
{
	if ( IsVisable() )
	{
		return m_frameTab[m_nCurSelFrame].OnChar( nChar );
	}
	return false;
}

void ControlTab::OnFrameChange()
{
	for ( int n=0; n<((S_TabData*)m_pstData)->m_nTabCount; n++ )
	{
		m_btnTab[n].SetNormalPic();
	}
	m_btnTab[m_nCurSelFrame].SetPressPic();
}

bool ControlTab::OnMouseMove( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() )
	{
		return m_frameTab[m_nCurSelFrame].OnMouseMove( nFlags, nX, nY );
	}
	return false;
}

bool ControlTab::OnMouseWheel( bool bUp, const int nX, const int nY )
{
	if ( IsVisable() )
	{
		return m_frameTab[m_nCurSelFrame].OnMouseWheel( bUp, nX, nY );
	}
	return false;
}

bool ControlTab::OnLButtonUp( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() )
	{
		return m_frameTab[m_nCurSelFrame].OnLButtonUp( nFlags, nX, nY );
	}
	return false;
}

bool ControlTab::OnRButtonUp( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() )
	{
		return m_frameTab[m_nCurSelFrame].OnRButtonUp( nFlags, nX, nY );
	}
	return false;
}

bool ControlTab::OnLButtonDBClick( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() )
	{
		return m_frameTab[m_nCurSelFrame].OnLButtonDBClick( nFlags, nX, nY );
	}
	return false;
}

bool ControlTab::OnRButtonDBClick( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() )
	{
		return m_frameTab[m_nCurSelFrame].OnRButtonDBClick( nFlags, nX, nY );
	}
	return false;
}

bool ControlTab::OnKeyDown( UINT nChar )
{
	if ( IsVisable() )
	{
		return m_frameTab[m_nCurSelFrame].OnKeyDown( nChar );
	}
	return false;
}

bool ControlTab::OnKeyUp( UINT nChar )
{
	if ( IsVisable() )
	{
		return m_frameTab[m_nCurSelFrame].OnKeyUp( nChar );
	}
	return false;
}

bool ControlTab::IsChild( IN const ControlObject* pChild )
{
	assert( pChild );
	for ( int n=0; n<((S_TabData*)m_pstData)->m_nTabCount; n++ )
	{
		if ( m_frameTab[n].IsChild( pChild ) == true )
		{
			return true;
		}
		if ( &m_btnTab[n] == pChild )
		{
			return true;
		}
	}
	return false;
}

ControlObject* ControlTab::FindControl( IN const char* szControlID,
									   IN const char* szFrameID )
{
	if ( szFrameID )
	{
		for ( int n=0; n<((S_TabData*)m_pstData)->m_nTabCount; n++ )
		{
			if ( strcmp( m_frameTab[n].GetControlID(), szFrameID ) == 0 )
			{
				return m_frameTab[n].FindControl( szControlID );
			}
		}
	}
	return NULL;
}

ControlObject* ControlTab::FindFrame( IN const char *szFrameID )
{
	for ( int n=0; n<((S_TabData*)m_pstData)->m_nTabCount; n++ )
	{
		if ( strcmp( m_frameTab[n].GetControlID(), szFrameID ) == 0 )
		{
			return &m_frameTab[n];
		}
	}
	return NULL;
}

ControlTabGroup::ControlTabGroup()
{

}

ControlTabGroup::~ControlTabGroup()
{

}

void ControlTabGroup::SetVisible(bool v)
{
	m_isVisible = v;
	m_tabs.SetVisible(v);

	std::map<ControlCheckBox*, ControlGroup*>::iterator it, end = m_pages.end();
	for (it = m_pages.begin(); it != end; ++it)
		it->second->SetVisible(v);
}

ControlObject* ControlTabGroup::GetControl(int index)
{
	std::map<ControlCheckBox*, ControlGroup*>::iterator it = m_pages.find(m_tabs.GetSelectRadio());
	if (it != m_pages.end())
		return it->second->GetControl(index);
	return 0;
}

void ControlTabGroup::AddPage(ControlCheckBox* pTab, ControlGroup* pPage)
{
	m_pages.insert(std::make_pair(pTab, pPage));
	m_tabs.AddRadio(pTab);
}

void ControlTabGroup::TogglePage(ControlCheckBox* pTab)
{
	m_tabs.ToggleRadio(pTab);

	std::map<ControlCheckBox*, ControlGroup*>::iterator it, end = m_pages.end();
	ControlGroup* pGroup = 0;
	for (it = m_pages.begin(); it != end; ++it)
	{
		if (it->first == pTab)
			pGroup = it->second;
		else
			it->second->SetVisible(false);
	}
	if( pGroup )
	{
		pGroup->SetVisible( true );
	}
}

void ControlTabGroup::Clear()
{
	ControlGroup::Clear();
	std::map<ControlCheckBox*, ControlGroup*>::iterator it, end = m_pages.end();
	ControlGroup* pGroup = 0;
	for (it = m_pages.begin(); it != end; ++it)
	{
		it->second->Clear();
	}
	m_pages.clear();	
	m_tabs.Clear();
	
}