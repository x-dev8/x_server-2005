/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	SwGlobal.cpp
* Create: 	10/06/06
* Desc:		SwGlobal类，用于获取全局数据
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#include "MeTerrain/stdafx.h"
#include "MeTerrain/SwGlobal.h"
#include "MeTerrain/NdlWorldPickerBase.h"
#include "Me3d/Model/MexGeoChunk.h"

// #include "UiManager.h"

////////////////////////////////////////////////////////////////////////////////
//静态变量初始化
////////////////////////////////////////////////////////////////////////////////

// SwTimer		SwGlobal::s_timer;
SwRender*	SwGlobal::s_pRender			= NULL;
// SwCamera*	SwGlobal::s_pCamera			= NULL;
int			SwGlobal::s_nMousePosX		= 0;
int			SwGlobal::s_nMousePosY		= 0;
int			SwGlobal::s_nMouseLastPosX	= 0;
int			SwGlobal::s_nMouseLastPosY	= 0;
int			SwGlobal::s_nMouseZ			= 0;
CWorld*		SwGlobal::s_pWorld			= NULL;

 const NiColor NiColor::WHITE = NiColor(1,1,1);
// const NiColor NiColor::BLACK = NiColor(0,0,0);
// const NiColorA NiColorA::WHITE = NiColorA(1,1,1,1);
// const NiColorA NiColorA::BLACK = NiColorA(0,0,0,1);
CNdlWorldPickerBase*	SwGlobal::s_pWorldPicker	= NULL;
// UITextureManager*		SwGlobal::s_pTexManager		= NULL;
//PtCtrlManager*			SwGlobal::s_pCtrlManager	= NULL;
const D3DXCOLOR			SwGlobal::s_globalDefaultFogColor = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);//( 0.4921875f, 0.46875f, 0.609375f, 1.0f);
// swLuaScript*			SwGlobal::s_Lua				= NULL;
LONG					SwGlobal::s_lLoadProgress = 0;
bool					SwGlobal::s_SimpleMapLoadMode = 0;
int						SwGlobal::s_SimpleMapLoadDistance = 60;
////////////////////////////////////////////////////////////////////////////////
//成员函数定义
////////////////////////////////////////////////////////////////////////////////
SwGlobal::SwGlobal()
{
}

SwGlobal::~SwGlobal()
{
}

void SwGlobal::Initialize()
{
	CDecalGeoChunk::SetGetZByXYFunc( GetZByXY );
}
void SwGlobal::SetMousePosition( int posX, int posY )
{
	s_nMouseLastPosX = s_nMousePosX;
	s_nMouseLastPosY = s_nMousePosY;
	s_nMousePosX		= posX;
	s_nMousePosY		= posY;
}

void SwGlobal::SetLoadProgress(float progress)
{
	 InterlockedExchange(&s_lLoadProgress, (LONG)progress * 10);	 
}

float SwGlobal::GetZByXY( float fCurrentZ,float x, float y,DWORD dwFlag, BOOL* bInFloor /*= NULL*/, DWORD* pdwRet /*= NULL*/, BOOL bIsRole /*= false*/, D3DXVECTOR3 *pNormal /*= NULL*/ )
{
	float fRet = 0.f;
	if (GetWorldPicker())
	{
		fRet = GetWorldPicker()->GetZByXY(fCurrentZ,x,y,dwFlag,bInFloor,pdwRet,bIsRole,pNormal);
	}
	return fRet;
}

////////////////////////////////////////////////////////////////////////////////
// end of file
////////////////////////////////////////////////////////////////////////////////