/**********************************************************************
 *<
	FILE: HR3D_Plugins.h

	DESCRIPTION:	Includes for Plugins

	CREATED BY:

	HISTORY:

 *>	Copyright (c) 2000, All Rights Reserved.
 **********************************************************************/

#ifndef __HR3D_PLUGINS__H
#define __HR3D_PLUGINS__H

#include "max.h"
#include "stdmat.h"
#include "cs/bipexp.h"
#include "cs/Phyexp.h"
#include "iskin.h"

#include "resource.h"
#include "istdplug.h"
#include "iparamb2.h"
#include "iparamm2.h"
#include "stdmat.h"
#include "utilapi.h"

extern TCHAR *GetString(int id);

extern HINSTANCE hInstance;

class HR3D_Plugins : public UtilityObj 
{
public:
	HWND			hPanel;
	IUtil			*iu;
	Interface		*ip;

	void BeginEditParams(Interface *ip,IUtil *iu);
	void EndEditParams(Interface *ip,IUtil *iu);

	void Init(HWND hWnd);
	void Destroy(HWND hWnd);


	void DeleteThis() { }		
	//Constructor/Destructor

	HR3D_Plugins();
	~HR3D_Plugins();
	// realrender added 2003.03.04
public:
	void DestroyCKF();
	Interface* GetInterface(){ return ip; }
	// realrender added 2003.05.31
	void NodeProperty();
	// realrender added 2003.06.01
	void Preview();
	// realrender added 2003.07.16
	BOOL ExpPrim( const char* pszFilename );
	// realrender added 2003.08.25
	BOOL ExpMdx2( const char* pszFilename );
	// realrender added 2003.08.31
	void TestKey();
	void SampleController(INode *n, Control *c);
	// realrender added 2003.10.07
	char* GetPluginAppPath(){ return m_szPluginAppPath; }

	Animatable *PickAnim();
	void GetAppData();
	void PutAppData();
	// realrender added 2003.12.16
	BOOL ParticleEmitterSetting();
	// realrender added 2004.01.06
	void ConvertBoneName();
	// realrender added 2004.03.15
	BOOL RibbonEmitterSetting();

protected:
	char m_szPluginAppPath[MAX_PATH];
};

extern HR3D_Plugins theHR3D_Plugins;
#endif // __HR3D_PLUGINS2__H
