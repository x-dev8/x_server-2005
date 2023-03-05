// WorldEditDoc.h : interface of the CWorldEditDoc class
//
#pragma once

#include <vector>

////////////////////////////////////////////////////////////////////////////////
class CWorldTile;
class CWorld;
class CWorldEditView;
class CToolsTabView;
////////////////////////////////////////////////////////////////////////////////
class CWorldEditDoc : public CDocument
{
protected: // create from serialization only
	CWorldEditDoc();
	DECLARE_DYNCREATE(CWorldEditDoc)

// Attributes
public:
	static CWorldEditDoc*	GetActiveMapDoc();	
	
	CWorldEditView*			GetWorldView()	{ return m_mainView; };
	CToolsTabView*			GetToolsView()	{ return  m_toolsView; };
	void					SetMainView( CWorldEditView* pView );
	void					SetToolView( CToolsTabView* pView );

	void					UpdateCurrentTime();
	void					UpdateAnimation();	// run any animation
	void					Update3DViews();	// redraw the 3d views

	void					SetWorldModify();
	void					AddTileModify( CWorldTile* worldTile );
	void					AddTileModify( uInt32 tileId);
	void					ClearTileModify( uInt32 tileId );
	void					ClearTileModify();
	
	void					UpdateMinimap();

	void					Reset();

public:
// Overrides
	public:
	virtual BOOL			OnNewDocument();
	virtual BOOL			OnOpenDocument(LPCTSTR lpszPathName);

	virtual void			Serialize(CArchive& ar);
	virtual void			UpdateAllViews( CView* pSender, LPARAM lHint = 0L, CObject* pHint = NULL );

	bool					WriteWorld( const char* worldPath );
	bool					WriteTile( CWorldTile* cacheTile, bool isPrompt = true );
	bool					WriteDirtyTile( bool isPrompt = true );
	
	bool					WriteServerMap( const char* mapPath, const char* mapName );

// Implementation
public:
	virtual ~CWorldEditDoc();
#ifdef _DEBUG
	virtual void			AssertValid() const;
	virtual void			Dump(CDumpContext& dc) const;
#endif


// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void			OnFileNew();
	afx_msg void			OnFileOpen();
	afx_msg void			OnFileSave();
	afx_msg void			OnFileSaveAs();
	afx_msg void			OnMergeTiles();
	afx_msg void			OnSplitTiles();
	afx_msg void			OnSaveServerMap();

protected:
	static CWorldEditDoc*	m_activeMapDoc;

	CWorldEditView*			m_mainView;
	CToolsTabView*			m_toolsView;

	float					m_currentTime;
	flt32					m_totalTime;
	
	std::vector<uInt32>		m_dirtyTileList;
public:
};


