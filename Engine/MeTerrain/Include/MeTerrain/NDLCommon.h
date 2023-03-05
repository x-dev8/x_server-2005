#pragma once 
#ifndef __NDLCOMMON_H__
#define __NDLCOMMON_H__


#include <NiMain.h>

#if defined(WIN32)
#include <NiDirectXVersion.h>
#endif //#if defined(WIN32)

#include <NiPNGReader.h>
// Many NiApplication subclasses use NiOutputDebugString and other
// system-related calls
#include <NiSystem.h>


// graph visualization for common statistics
#include <NiVisualTracker.h>
#include <NiCommonGraphCallbackObjects.h>
#include <NiUniversalTypes.h>
#include <NiMainPCH.h>
//#include <NiInput.h>
#include <NiSystemCursor.h>
#include "NiFrameRate.h"
#include <NiAlphaProperty.h>
#include <NiPixelData.h>
#include <NiPixelFormat.h>
#include <NiSystem.h>
#include <NiTexturingProperty.h>
#include <NiVertexColorProperty.h>
#include <NiRenderTargetGroup.h>
#include <NiDX9Renderer.h>
//#include <NiD3D10Renderer.h>
#include <NiDX9Headers.h>
#include <NiDX9SystemDesc.h>
#include <NiRTLib.h>
#include <NiTList.h>
#include <NiColor.h>
#include <NiMaterialProperty.h>
#include <NiScreenElements.h>
#include <NiOS.h>
#include <NiRenderer.h>
#include <NiMemObject.h>
#include <NiUniversalTypes.h>
#include <NiMemManager.h>
#include <NiParticle.h>
#include <NiCollision.h>

#include <NiAnimation.h>
#include <NiD3DRendererHeaders.h>
#include <NiMeshLib.h>
//#include <NiD3DGeometryGroupManager.h>
#include <NiD3DShaderFactory.h>

#if defined(_DX9)
#include <NiDX9SystemDesc.h>
#endif //#if defined(_DX9)

//#include <NiDynamicGeometryGroup.h>
#include <NiTriShape.h>
#include <NiTriShapeDynamicData.h>

// Ensure that _LIB is defined if it's not using DLLs
#ifndef NIDX9RENDERER_IMPORT
#define _LIB
#endif //#ifndef NIDX9RENDERER_IMPORT

#ifndef SHADERFORMATCOMPATIBILITY_H
#define SHADERFORMATCOMPATIBILITY_H

#if defined(_DX9)
#define _NI_ASM_SHADER_PROGRAM_FORMAT
#define _NI_HLSL_SHADER_PROGRAM_FORMAT
#define _NI_FX_SHADER_FORMAT
#if defined(_SHADER_SAMPLE_USES_CG)
#define _NI_CG_SHADER_PROGRAM_FORMAT
#endif //#if defined(_SHADER_SAMPLE_USES_CG)
#elif defined(_XENON)
#define _NI_ASM_SHADER_PROGRAM_FORMAT
#define _NI_HLSL_SHADER_PROGRAM_FORMAT
#define _NI_FX_SHADER_FORMAT
#endif

#endif  //#ifndef SHADERFORMATCOMPATIBILITY_H


#if defined(_LIB_BUILD) || defined(_XENON)

#define _LIB
#include <NSBShaderLib.h>
#include <NSFParserLib.h>
#include <NiD3DXEffectShaderLib.h>
#include <NiCgShaderLib.h>
#undef _LIB

#endif  //#if defined(_LIB_BUILD)


#ifndef NDL_SAFE_DELETE
#define NDL_SAFE_DELETE( p )			{ if( p ){ NiDelete (p); (p) = NULL; } }
#endif

#ifndef NDL_SAFE_DELETE_ARRAY
#define NDL_SAFE_DELETE_ARRAY( p )		{ if( p ) { NiDelete[] (p);   (p)=NULL; } }
#endif

#ifndef NDL_SAFE_DESTROY_AND_DELETE
#define NDL_SAFE_DESTROY_AND_DELETE( p ){ if( p ){ (p)->Destroy(); NiDelete (p); (p) = NULL; } }
#endif





#endif	// __NDLCOMMON_H__