#pragma once 
#ifndef __STCOMMON_H__
#define __STCOMMON_H__

#include "Dxsdk/d3dx9.h"

#include "Me3d/vector.h"
#include "Me3d/quaternion.h"
// #include "NiSmartPointer.h"
// #include "NiRect.h"

// Ensure that _LIB is defined if it's not using DLLs
//#ifndef NIDX9RENDERER_IMPORT
// #define _LIB
//#endif //#ifndef NIDX9RENDERER_IMPORT

#ifndef SHADERFORMATCOMPATIBILITY_H
#define SHADERFORMATCOMPATIBILITY_H

#define _NI_ASM_SHADER_PROGRAM_FORMAT
#define _NI_HLSL_SHADER_PROGRAM_FORMAT
#define _NI_FX_SHADER_FORMAT

#endif  //#ifndef SHADERFORMATCOMPATIBILITY_H

#define COLOR_BLACK (0.0f,0.0f,0.0f)
#define COLOR_WHITE (1.0f,1.0f,1.0f)

#ifndef NDL_SAFE_DELETE
#define NDL_SAFE_DELETE( p )			{ if( p ){ delete (p); (p) = NULL; } }
#endif

#ifndef NDL_SAFE_DELETE_ARRAY
#define NDL_SAFE_DELETE_ARRAY( p )		{ if( p ) { delete[] (p);   (p)=NULL; } }
#endif

#ifndef NDL_SAFE_DESTROY_AND_DELETE
#define NDL_SAFE_DESTROY_AND_DELETE( p ){ if( p ){ (p)->Destroy(); delete (p); (p) = NULL; } }
#endif





#endif	// __STCOMMON_H__