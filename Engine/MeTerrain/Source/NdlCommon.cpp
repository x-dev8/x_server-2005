/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	NDLCommon.cpp
* Date: 	01/09/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"

#pragma message("     Adding library: Winmm.lib" ) 
#pragma comment(lib, "Winmm.lib")
#pragma message("     Adding library: NiSystem.lib" ) 
#pragma comment(lib, "NiSystem.lib" )
#pragma message("     Adding library: NiMain.lib" ) 
#pragma comment(lib, "NiMain.lib")
#pragma message("     Adding library: NiAnimation.lib" ) 
#pragma comment(lib, "NiAnimation.lib")
#pragma message("     Adding library: NiInput.lib" ) 
#pragma comment(lib, "NiInput.lib")
#pragma message("     Adding library: NiCollision.lib" ) 
#pragma comment(lib, "NiCollision.lib") 
#pragma message("     Adding library: NiParticle.lib" ) 
#pragma comment(lib, "NiParticle.lib")
#pragma message("     Adding library: NiPNGReader.lib" ) 
#pragma comment( lib,"NiPNGReader.lib" )
#pragma message("     Adding library: NiMesh.lib" ) 
#pragma comment(lib, "NiMesh.lib")
#pragma message("     Adding library: NiFloodgate.lib" ) 
#pragma comment(lib, "NiFloodgate.lib")
#pragma message("     Adding library: d3dx9.lib" ) 
#pragma comment(lib, "d3dx9.lib")
#pragma comment( lib , "png.lib" )
#pragma message("Adding library: png.lib" ) 
#pragma comment( lib , "zlib.lib" )
#pragma message("Adding library: zlib.lib" ) 

#if defined(_DX9)
#include <NiDX9Renderer.h>
#pragma message("     Adding library: NiDX9Renderer.lib" ) 
#pragma comment(lib, "NiDX9Renderer.lib")
#pragma message("     Adding library: NiD3D10Renderer.lib" ) 
#pragma comment(lib, "NiD3D10Renderer.lib")

#pragma message("     Adding library: dxguid.lib" ) 
#pragma comment(lib, "dxguid.lib")
#endif //#if defined(_DX9)


#ifdef NIDX9RENDERER_IMPORT
#ifdef _DEBUG
#if (_MSC_VER == 1400) //VC8.0
#pragma message("     Adding library: NiDX9Renderer22VC80D.lib" ) 
#pragma comment(lib, "NiDX9Renderer22VC80D.lib")
#elif (_MSC_VER == 1310) //VC7.1
#pragma message("     Adding library: NiDX9Renderer21VC71D.lib" ) 
#pragma comment(lib, "NiDX9Renderer22VC71D.lib")
#else
#error Unsupported version of Visual Studio
#endif
#else   // #ifdef _DEBUG
#if (_MSC_VER == 1400) //VC8.0
#pragma message("     Adding library: NiDX9Renderer21VC80.lib" ) 
#pragma comment(lib, "NiDX9Renderer22VC80.lib")
#elif (_MSC_VER == 1310) //VC7.1
#pragma message("     Adding library: NiDX9Renderer21VC71.lib" ) 
#pragma comment(lib, "NiDX9Renderer22VC71.lib")
#else
#error Unsupported version of Visual Studio
#endif
#endif  // #ifdef _DEBUG
#else   // #ifdef NIDX9RENDERER_IMPORT
// #pragma message("     Adding library: NiDX9Renderer.lib" ) 
// #pragma comment(lib, "NiDX9Renderer.lib")
#endif  // #ifdef NIDX9RENDERER_IMPORT


#ifdef NIVISUALTRACKER_IMPORT
#ifdef _DEBUG
#if (_MSC_VER == 1400) //VC8.0
#pragma message("     Adding library: NiVisualTracker21VC80D.lib" ) 
#pragma comment(lib, "NiVisualTracker22VC80D.lib")
#elif (_MSC_VER == 1310) //VC7.1
#pragma message("     Adding library: NiVisualTracker21VC71D.lib" ) 
#pragma comment(lib, "NiVisualTracker22VC71D.lib")
#else
#error Unsupported version of Visual Studio
#endif
#else   // #ifdef _DEBUG
#if (_MSC_VER == 1400) //VC8.0
#pragma message("     Adding library: NiVisualTracker21VC80.lib" ) 
#pragma comment(lib, "NiVisualTracker22VC80.lib")
#elif (_MSC_VER == 1310) //VC7.1
#pragma message("     Adding library: NiVisualTracker21VC71.lib" ) 
#pragma comment(lib, "NiVisualTracker22VC71.lib")
#else
#error Unsupported version of Visual Studio
#endif
#endif  // #ifdef _DEBUG
#else   // #ifdef NIVisualTracker_IMPORT
//#pragma message("     Adding library: NiVisualTracker.lib" ) 
//#pragma comment(lib, "NiVisualTracker.lib")
#endif  // #ifdef NIVisualTracker_IMPORT

