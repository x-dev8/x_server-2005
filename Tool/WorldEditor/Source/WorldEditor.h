#ifndef __WORLD_EDIT_H__
#define __WORLD_EDIT_H__
// WorldEdit.h : main header file for the WorldEdit application
// Desc: WorldEditorApp

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource/Resource.h"       // main symbols

////////////////////////////////////////////////////////////////////////////////

class CWorld;
class COptStack;
class CNdlWorldEditor;
class CMainFrame;
////////////////////////////////////////////////////////////////////////////////
// CWorldEditApp:
// See WorldEdit.cpp for the implementation of this class
//
class CWorldEditApp : public CWinApp
{
public:
						CWorldEditApp();

	void				OnActivateApp( bool isActive );
	bool				IsActiveApp();


	void				SetForceRenderNextFrame();
	bool				GetForceRenderNextFrame();

	LPCTSTR				GetAppDir()	const		{ return m_appDir; };
	CWorld*				GetWorld() const		{ Assert( NULL != m_world ); return m_world; };
	CNdlWorldEditor*	GetWorldEditor() const	{ Assert( NULL != m_worldEditor ); return m_worldEditor; };
	COptStack*			GetOptStack() const		{ Assert( NULL != m_editStack ); return m_editStack; };
	
	void				SetMainFrame( CMainFrame* mainFrame ){ m_mainFrame = mainFrame; };
	void				SetProcess( int percent );
	void				SetPromptText( LPCTSTR text );
	void				SetMousePosText( sInt32 posX, sInt32 posY, const Vector& rayPt, const Vector& rayDir );
	void				SetWorldPosText( flt32 posX, flt32 posY, flt32 posZ,flt32 angle );
	void				SetLoopCountText( sInt32 countA, sInt32 countB );

	void				SetLightDir( const Vector& dir );
	void				SetLightAmbientColor( const NiColor& ambient );
	void				SetLightDiffuseColor( const NiColor& diffuse );
	void				SetLightSpecularColor( const NiColor& specular );
	void				SetSunLessColor( const NiColor& specular );
	void				SetDefaultLight();

	void				SetFogColor( const NiColor& fogColor );
	void				SetFogDepth( flt32 fogNear, flt32 fogFar );
	FogProperty*		GetFogProperty();

	void				CalFPS();
// Overrides
public:
	virtual BOOL		InitInstance();
	virtual int			ExitInstance();

	virtual BOOL		OnIdle(LONG lCount);
	virtual int			Run(void);

protected:
	void				RunFrame(void);

protected:
// Implementation
	DECLARE_MESSAGE_MAP()
	afx_msg void		OnAppAbout();


protected:
	bool				m_isActiveApp;
	bool				m_isForceRenderNextFrame;

	TCHAR				m_appDir[MAX_PATH];

	CWorld*				m_world;
	CNdlWorldEditor*	m_worldEditor;
	COptStack*			m_editStack;

	CMainFrame*			m_mainFrame;
};

extern CWorldEditApp	theApp;


#endif //__WORLD_EDIT_H__