#ifndef _mdx2_ctrlpanel_h
#define _mdx2_ctrlpanel_h

#include <d3dx9.h>
//#include "hr3d_include.h"

class CMdx2CtrlPanel
{
public:
	CMdx2CtrlPanel():	m_hD3DWnd(NULL),
				m_pD3D(NULL),
				m_pd3dDevice(NULL),
				m_bQuit(FALSE),
				m_bRunning(FALSE),
				m_nSelId(-1),
				m_bPause(FALSE){}
	~CMdx2CtrlPanel();
	BOOL		Create( HINSTANCE hInstance );
	void		Render();
	void		ShutDown( BOOL bCreateSucc = TRUE );
	void		Run();
	LRESULT		MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT		CtrlPanelMsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT		AnimSequenceSettingDlgMsgProc( HWND hDlg,UINT uMsg, WPARAM wParam, LPARAM lParam );
	LRESULT		LogDlgMsgProc( HWND hDlg,UINT uMsg, WPARAM wParam, LPARAM lParam );
	LRESULT		AutoNamePanelMsgProc( HWND hDlg,UINT uMsg, WPARAM wParam, LPARAM lParam );
	void		UpdateNode( int nNodeId );
	// realrender added 2003.09.03
	void		AddObjectsToTree( HWND hWnd );
	void		AddAnimsToList( HWND hWnd );
	void		AddTexturesToList( HWND hWnd );
	void		AddMaterialsToTree( HWND hWnd );
	void		AddChunksToTree( HWND hWnd );

	BOOL		CreateD3DViewWnd();
	BOOL		m_bRunning;
	HWND		m_hD3DWnd;
	HWND		m_hCtrlPanel;
	// realrender added 2003.07.04
	BOOL		ExpSWF( const char* pszFilename );
	// realrender added 2003.07.16
	BOOL		ExpPrim( const char* pszFilename );
protected:
				
	
	WNDCLASSEX				m_winClass; 
	LPDIRECT3D9 			m_pD3D;
	LPDIRECT3DDEVICE9		m_pd3dDevice;
	BOOL					m_bQuit;

	//HR3D_Camera*				m_pCamera;
	//HR3D_MouseCtrl			m_msCtrl;

	// 当前选中的节点(在tree中)
	int						m_nSelId;

	BOOL					m_bPause;
	
};

extern CMdx2CtrlPanel g_mdx2CtrlPanel;

#endif