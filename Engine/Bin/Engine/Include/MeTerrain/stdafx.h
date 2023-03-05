// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

// #ifndef VC_EXTRALEAN
// #define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
// #endif
// 
// // Modify the following defines if you have to target a platform prior to the ones specified below.
// // Refer to MSDN for the latest info on corresponding values for different platforms.
// #ifndef WINVER				// Allow use of features specific to Windows 95 and Windows NT 4 or later.
// #define WINVER 0x0400		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
// #endif
// 
// #ifndef _WIN32_WINNT		// Allow use of features specific to Windows NT 4 or later.
// #define _WIN32_WINNT 0x0400	// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
// #endif						
// 
// #ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
// #define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
// #endif
// 
// #ifndef _WIN32_IE			// Allow use of features specific to IE 4.0 or later.
// #define _WIN32_IE 0x0400	// Change this to the appropriate value to target IE 5.0 or later.
// #endif

// #define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit
// 
// // turns off MFC's hiding of some common and often safely ignored warning messages
// #define _AFX_ALL_WARNINGS
// 
//#include <afxwin.h>         // MFC core and standard components
// #include <afxext.h>         // MFC extensions
// #include <afxdisp.h>        // MFC Automation classes
// // 
//  #include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
//  #ifndef _AFX_NO_AFXCMN_SUPPORT
//  #include <afxcmn.h>			// MFC support for Windows Common Controls
//  #endif // _AFX_NO_AFXCMN_SUPPORT

// #ifdef _DEBUG
// #	define _CRTDBG_MAP_ALLOC
// #	include<stdlib.h>
// #	include<crtdbg.h>
// #endif
//#include <XTToolkitPro.h>	// Xtreme Toolkit Pro components

#include <MeFoundation/MeFoundationPCH.h>
#include "Me3d/engine/TextureDx8.h"
#include "MeTerrain/NiColor.h"
#include "MeTerrain/SwType.h"
#include "MeTerrain/SwDebug.h"
#include "MeTerrain/STCommon.h"
// #include "SwTimer.h"
#include "Singleton.h"
#include "MeTerrain/SwGlobal.h"
#include "MeTerrain/SwPublicFunc.h"
#include "MeTerrain/HashTable.h"
#include "MapFile.h"
#include "MeTerrain/MapUtil.h"
#include "MeTerrain/World.h"
#include "MeTerrain/WorldBuffer.h"
#include "MeTerrain/WorldTile.h"
#include "MeTerrain/WorldChunk.h"
#include "MeTerrain/NdlRes.h"
#include "MeTerrain/NdlResMgr.h"
// #include "FuncPerformanceLog.h"

//#include "EditRender/EditAccumulator.h"
// #include "Ndl/NdlEditWorldPicker.h"
// #include "EditRender/EditRender.h"
// #include "EditRender/EditCamera.h"
// 
// #include "WorldEdit.h"
// #include "MainFrm.h"
// #include "WorldEditDoc.h"
// #include "WorldEditView.h"
// 
// #include <atlimage.h>
#include "RapidXml/MeRapidXml.h"
// 
// #include "External/CxImage/ximacfg.h"
// #include "External/CxImage/ximage.h"

//#include "Lua_5_1_2/lua.hpp"
// #include "luaplus/luaplus.h"
// 
// #include "External/PtInput/PtInput.h"

#include "Me3d/Engine/EngineInstance.h"
#include "Me3d/Engine/Engine.h"
#include "3dsmax/gfloat.h"