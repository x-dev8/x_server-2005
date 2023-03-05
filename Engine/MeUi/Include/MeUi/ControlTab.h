
#pragma once
#include "MeUi/ControlObject.h"
#include "MeUi/ControlFrame.h"
#include "MeUi/ControlButton.h"
#include "MeUi/ControlCheckBox.h"

class ControlTab : public ControlObject
{
public:	/*Virtual Function*/
	void Render();
	bool IsChild( IN const ControlObject* pChild );
	ControlObject*	FindControl( IN const char* szControlID,
					IN const char* szFrameID = NULL );
	ControlObject* FindFrame( IN const char *szFrameID );
	void InitUIData( IN ControlObject* pFather, IN S_BaseData* pData );
	bool OnChar( UINT nChar );
	bool OnMouseMove( UINT nFlags, const int nX, const int nY );
	bool OnMouseWheel( bool bUp, const int nX, const int nY );
	bool OnLButtonUp( UINT nFlags, const int nX, const int nY );
	bool OnLButtonDown( UINT nFlags, const int nX, const int nY );
	bool OnLButtonDBClick( UINT nFlags, const int nX, const int nY );
	bool OnRButtonUp( UINT nFlags, const int nX, const int nY );
	bool OnRButtonDown( UINT nFlags, const int nX, const int nY );
	bool OnRButtonDBClick( UINT nFlags, const int nX, const int nY );
	bool OnKeyDown( UINT nChar );
	bool OnKeyUp( UINT nChar );

public:
	void	OnFrameChange();

private:
	ControlButton	m_btnTab[TAB_CONTROL_MAX];
	ControlFrame	m_frame;
	ControlFrame	m_frameTab[TAB_CONTROL_MAX];
	int				m_nCurSelFrame;

public:
	ControlTab(void);
	~ControlTab(void);
};

class ControlTabGroup : public ControlGroup
{
public:
	ControlTabGroup();
	virtual ~ControlTabGroup();

	virtual void Clear();
	virtual void SetVisible(bool v);

	virtual ControlObject* GetControl(int index);

	void AddPage(ControlCheckBox* pTab, ControlGroup* pPage);
	void TogglePage(ControlCheckBox* pTab);

private:
	std::map<ControlCheckBox*, ControlGroup*> m_pages;
	ControlRadioGroup m_tabs;
};