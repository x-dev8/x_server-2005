
#include "Me3d/Config.h"
#include "Me3d/Camera.h"
#include "FuncPerformanceLog.h"
#include <STDARG.H>
#include <windows.h>

int Config::m_nRigidHaloTextureId = -1;
int Config::m_nLightTrackTextureId = -1;
bool Config::m_bFrameUpdated = false;
MeMatrix Config::m_matBillboard;
MeMatrix Config::m_matStandboard;
int Config::m_nScreenWidth = 800;
int Config::m_nScreenHeight = 600;
bool Config::m_bPaused = false;
//   added 2003.05.16
HWND Config::m_hDebugWnd = NULL;
//   added 2003.05.20
char Config::m_szWC3MpqPath[256];
//   added 2003.06.08
MeCamera Config::m_camera;
MeCamera* Config::m_pCamera = NULL;
//   added 2003.06.09
int	Config::m_nRunFrameCount = 0;
//   added 2003.07.25
int	Config::m_nShadowTextureId = -1;
//   added 2003.07.25
int	Config::m_nZBias = 0;
//   added 2003.07.30
int Config::m_nDefaultTextureIds[eMax_Default_Texture];
//   added 2003.08.04
int Config::m_nPlayerColorTextureIds[MAX_PLAYER_COLOR];
int Config::m_nPlayerGlowColorTextureIds[MAX_PLAYER_COLOR];
int Config::m_nCurrentPlayerColor;
float Config::m_fMdlSpaceScale = 0.02f;
//   added 2003.11.26
int Config::m_bUsePushSurface = false;
//   added 2003.05.16
BOOL Config::m_bAlwaysRenderEffect = FALSE;
float	Config::m_fObjectMtlMod = 1.0f;

BOOL	Config::m_nPlayerShowInfo = eClose_NameLvl;

BOOL	Config::m_bShowGrid = FALSE;
BOOL	Config::m_bShowChunk = FALSE;
BOOL	Config::m_bRenderScShadows = TRUE;
BOOL	Config::m_bRenderTerrain = TRUE;

BOOL	Config::m_bShowWalk = FALSE;
BOOL	Config::m_bRenderObjs = TRUE;
BOOL	Config::m_bAllRender = FALSE;
BOOL	Config::m_bMiniMap	=	TRUE; 
BOOL	Config::m_bShowWorld = TRUE;
BOOL	Config::m_bRenderWater = TRUE;
BOOL	Config::m_ShowAllAlphaInfo = FALSE;

BOOL	Config::m_ShowFog = TRUE;
//BOOL	Config::m_bFastLoadMex = FALSE;

//BOOL	Config::m_bRenderBBox = FALSE; 

// 场景运动饰物的播放速度( 0 为默认 )
DWORD g_dwSceneObjLoopTime = 0;

static Config gs_Me3dConfig;
Config* GetMe3dConfig()
{
	guardfunc;
	return &gs_Me3dConfig;
	unguard;
}
void Config::Debug( DWORD dwDbgType, const char* string, ... )
{
	guardfunc;
	va_list	va;
	static char data[1024];

	va_start( va, string );
	wvsprintf( (char*)data, string, va );
	va_end( va );
	//HWND hWnd = m_hDebugWnd;
	SendMessage( m_hDebugWnd, LB_INSERTSTRING, 0, (LPARAM)(LPCTSTR)data );
	unguard;
}

Config::Config()
{
	guardfunc;
	m_bIsATICard = FALSE;

	m_dwSkinMeshVertexShaderID = 0xffffffff;
	m_bUseSkinMesh = FALSE;
	m_fObjectMtlMod = 1.0f;

	m_bAlwayseWireFrameRendering = FALSE;
	m_bIsUseVBIB = TRUE;//	默认使用VB
	
	m_bShowTerrain = TRUE;
	for( int i=0; i<4; i++ )
	{
		m_bLayerRender[i] = TRUE;
	}

	m_bRenderMapBox = FALSE;

	m_bIsRenderTree = TRUE;

	m_bIsRenderGrass = TRUE;


	m_fBspRenderDis = 0.0f;
	for( int i = 0; i < eCommonEffectTextureMax; i++ )
	{
		m_nCommonEffectTextureIDs[i] = -1;
	}
	m_bToolMode = FALSE;
	m_RenderHelper = None_Helper;

	m_fMipLodBais = -1.0f;

	m_dwLoadSleepTime = 0;

	m_bEnjoinTwoSide = FALSE;

	m_dwServerStartTime = 0;
	m_dwClientStartTime = 0;

// 	m_bFastLoadMex = FALSE;
	m_nScreenWidth = 0;
	m_nScreenHeight = 0;

    m_bFullSceneAntialiasing = TRUE;

    m_cullDistance = 250.0f;

	m_bIsRenderModelSelected = FALSE;

	m_terrainLayer = 4;

	m_bIsPlayMapEffect = FALSE;
	m_bLockFPS = FALSE;
	m_nKeepFPS = 30;

	/*
	 * Author:	2012-8-25 wangshuai
	 * Desc: 	默认开启垂直同步
	 */
	m_bVSync = TRUE;

	unguard;
}