/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	NDLCommon.cpp
* Date: 	01/09/2007
* Desc:
*
*******************************************************************************/
#include "MeTerrain/stdafx.h"

#pragma message("     Adding library: Winmm.lib" ) 
#pragma comment(lib, "Winmm.lib")
//#pragma comment(lib, "NiFloodgate.lib")
#pragma message("     Adding library: d3dx9.lib" ) 
#pragma comment(lib, "d3dx9.lib")
#pragma comment( lib , "png.lib" )
#pragma message("Adding library: png.lib" ) 
// #pragma comment( lib , "zlib.lib" )
// #pragma message("Adding library: zlib.lib" ) 

#if defined(_DX9)

#pragma message("     Adding library: dxguid.lib" ) 
#pragma comment(lib, "dxguid.lib")
#endif //#if defined(_DX9)

#pragma comment ( lib, "imm32.lib" )
