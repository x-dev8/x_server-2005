#ifndef _config_h
#define _config_h
#include "Me3d.h"
#define MAX_PLAYER_COLOR 12
class MeCamera;
enum DefaultTextureType
{
	eShadow_TextureId,
	eLightTrack_TextureId,

	eWC3_ReplaceableTextureId1,
	eWC3_ReplaceableTextureId2,
	eWC3_ReplaceableTextureId3,

	eMax_Default_Texture
};
enum
{
	eCommonEffectTexture_Flash,
	eCommonEffectTexture_Flame,
	eCommonEffectTexture_Ice,
	eCommonEffectTexture_LightTrack,
	eCommonEffectTextureMax,
};
enum
{
	eAllPlayer_NameLvl,
	eAllNpcMonster_NameLvl,	
	eALL_NameLvl,
	eClose_NameLvl,
	eMax_NameLvl
};

enum
{ 
	eATI_Card,
	enVidia_Card
};

class Config
{
public:
	static int m_nRigidHaloTextureId;
	static int m_nLightTrackTextureId;
	static bool m_bFrameUpdated;
	static MeMatrix m_matBillboard;
	static MeMatrix m_matStandboard;
	static int m_nScreenWidth;
	static int m_nScreenHeight;
	static bool m_bPaused;
	//   added 2003.05.16
	static HWND m_hDebugWnd;
	//   added 2003.05.20
	static char m_szWC3MpqPath[256];
	//   added 2003.06.08
	static MeCamera m_camera;
	static MeCamera* m_pCamera;
	//   added 2003.06.09
	static int	m_nRunFrameCount;
	//   added 2003.07.25
	static int	m_nShadowTextureId;

	// human
	static float	m_fObjectMtlMod;
	

	//   added 2004.09.15
	static int	m_nZBias;
	//human
	static BOOL	m_bAllRender;
	

	//int					m_nScreenWidth;
	//int					m_nScreenHeight;
public:
	Config();
	//   added 2003.07.30
	static int m_nDefaultTextureIds[eMax_Default_Texture];
	static int m_nPlayerColorTextureIds[MAX_PLAYER_COLOR];
	static int m_nPlayerGlowColorTextureIds[MAX_PLAYER_COLOR];
	int m_nCommonEffectTextureIDs[eCommonEffectTextureMax];
	BOOL m_bToolMode;
	enum ERenderHelper {
		None_Helper,
		Floor_Helper,
		Supper_Floor_Helper,
		Collision_Helper,
		Alpha_Box_Helper,
		Floor_Collision_Helper,
	};
	int m_RenderHelper;
	static int m_nCurrentPlayerColor;
	//   added 2003.11.26
	static int m_bUsePushSurface;
	//   added 2003.09.06
	static float m_fMdlSpaceScale;	//坐标转化 编辑器->游戏世界中的转化 ( 0.02 )
	static BOOL m_bAlwaysRenderEffect;
	static BOOL	m_nPlayerShowInfo;

	static BOOL	m_bShowGrid;		//是否显示线筐图

	static BOOL	m_bShowChunk;
	static BOOL	m_bRenderScShadows;
	static BOOL m_bRenderTerrain;
	static BOOL m_bShowWalk;

	static BOOL m_bRenderObjs;
	static BOOL	m_bMiniMap;
	static BOOL m_bShowWorld;
	static BOOL m_bRenderWater;

	static BOOL m_ShowAllAlphaInfo; //Terrain的Aphla层信息
	
	static BOOL m_ShowFog;


	DWORD			m_dwServerStartTime;
	DWORD			m_dwClientStartTime;
	FLOAT		m_fMipLodBais;
	DWORD		m_dwLoadSleepTime;

	DWORD		GetLoadSleepTime()					{ return m_dwLoadSleepTime;		}
	VOID		SetLoadSleepTime(DWORD dwTime)		{ m_dwLoadSleepTime = dwTime;	}

	//static BOOL m_bRenderBBox;
	
	BOOL	IsRenderBBox()							{ return m_bRenderBBox; }
	VOID	SetRenderBBox( BOOL bRender )			{ m_bRenderBBox = bRender; }

	static VOID	SetShowFog( BOOL bRender )				{ m_ShowFog = bRender; }
	static BOOL	IsShowFog()								{ return m_ShowFog; }

	static VOID	ShowAllAlphaInfo( BOOL bRender )		{ m_ShowAllAlphaInfo = bRender; }
	static BOOL	IsShowAllAlphaInfo( )					{ return m_ShowAllAlphaInfo; }

	static BOOL	IsRenderWater()							{ return m_bRenderWater; }
	static VOID	SetRenderWater( BOOL bRender )			{ m_bRenderWater = bRender; }

	static BOOL	IsRenderWorld()							{ return m_bShowWorld; }
	static VOID	SetRenderWorld( BOOL bRender )			{ m_bShowWorld = bRender; }
	
	BOOL	IsRenderTerain()							{ return m_bShowTerrain; }
	VOID	SetRenderTerrain( BOOL bRender )			{ m_bShowTerrain = bRender; }


	static BOOL	IsRenderObjs()						{ return m_bRenderObjs; }
	static VOID	SetRenderObjs( BOOL bRenderobjs )		{ m_bRenderObjs = bRenderobjs; }

// 	static BOOL	IsMiniMap()								{ return m_bMiniMap; }
// 	static VOID	SetShowMiniMap( BOOL bShow )		{ m_bMiniMap = bShow; }

	static BOOL	IsShowWalk()						{ return m_bShowWalk; }
	static VOID	SetShowWalk( BOOL bShowWalk )		{ m_bShowWalk = bShowWalk; }

	static BOOL	IsShowGrid()		{ return m_bShowGrid; }
	static VOID	SetShowGrid( BOOL bShowGrid )		{ m_bShowGrid = bShowGrid; }

	static BOOL	IsRenderChunkGrid()		{ return m_bShowChunk; }
	static VOID	SetRenderChunkGrid( BOOL bShowGrid )		{ m_bShowChunk = bShowGrid; }

	static VOID	SetRenderShadows( BOOL bRenderShadows )	{ m_bRenderScShadows = bRenderShadows; }
	static BOOL	IsRenderShadows( )	{ return m_bRenderScShadows; }

	static VOID SetRenderAllObjs( BOOL bRender ) { m_bAllRender = bRender; }
	static BOOL IsRenderAllObjs() { return m_bAllRender; }

//	static BOOL	SetRenderTerrain( BOOL bRenderTerrain )	{ m_bRenderTerrain = bRenderTerrain; }
//	static BOOL	IsRenderTerrain( )	{ return m_bRenderTerrain; }



	static void SetObjectMtlMod( float fObjectMtlMod ) { m_fObjectMtlMod = fObjectMtlMod; }
	static float GetObjectMtlMod() {  return m_fObjectMtlMod; }

	static void SetShowPlayerInfo( INT nShowInfo ) { m_nPlayerShowInfo = nShowInfo; }
	static INT	GetShowInfoLvl( ) { return m_nPlayerShowInfo; }

	static void SetDefaultTextureId( DefaultTextureType type, int nTextureId )
	{
		m_nDefaultTextureIds[type] = nTextureId;
	}
	static int GetDefaultTextureId( DefaultTextureType type )
	{
		return m_nDefaultTextureIds[type];
	}
	
	
	
	static void SetRigidHaloTextureId( int nTextureId )
	{
		m_nRigidHaloTextureId = nTextureId;
	}
	static int GetRigidHaloTextureId()
	{
		return m_nRigidHaloTextureId;
	}
	static void SetLightTrackTextureId( int nTextureId )
	{
		m_nLightTrackTextureId = nTextureId;
	}
	static int GetLightTrackTextureId()
	{
		return m_nLightTrackTextureId;
	}
	static void FrameUpdated( bool flag )
	{
		m_bFrameUpdated = flag;
		if( m_bFrameUpdated )
			m_nRunFrameCount++;
	}
	static bool IsFrameUpdated()
	{
		return m_bFrameUpdated;
	}
	static void SetBillboard( const MeMatrix& matBillboard )
	{
		m_matBillboard = matBillboard;
	}
	static const MeMatrix& GetBillboard()
	{
		return m_matBillboard;
	}
	static void SetStandboard( const MeMatrix& matStandboard )
	{
		m_matStandboard = matStandboard;
	}
	static const MeMatrix& GetStandboard()
	{
		return m_matStandboard;
	}
	static int GetScreenWidth()
	{
		return m_nScreenWidth;
	}
	static int GetScreenHeight()
	{
		return m_nScreenHeight;
	}
	static bool IsPaused()
	{
		return m_bPaused;
	}
	static void Pause( bool bPaused )
	{
		m_bPaused = bPaused;
	}
	//   added 2003.05.16
	static void SetDbgWnd( HWND hDbgWnd ){ m_hDebugWnd = hDbgWnd; }
	static void Debug( DWORD dwDbgType, const char* string, ... );
	//   added 2003.05.20
	static void SetWC3MpqPath( const char* pszPath )
	{
		strcpy( m_szWC3MpqPath, pszPath );
	}
	char* GetWC3MpqPath(){ return m_szWC3MpqPath; }
	//   added 2003.06.08
	static MeCamera* GetCamera()
	{
		if (!m_pCamera)
			m_pCamera = &m_camera;
		return m_pCamera;
	}
	static void SetCamera(MeCamera* pCamera ) { m_pCamera = pCamera; }
	//   added 2003.06.09
	static int GetRunFrameCount(){ return m_nRunFrameCount; }
	//   added 2003.07.25
	static void SetShadowTextureId( int id ){ m_nShadowTextureId = id; }
	static int GetShadowTextureId(){ return m_nShadowTextureId; }

	VOID	SetLayerIsRender(INT nLayer, BOOL bRender ) { m_bLayerRender[nLayer] = bRender; }
	BOOL	GetLayerIsRender(INT nLayer )				{ return m_bLayerRender[nLayer]; }

	VOID	SetUseVB( BOOL bUseVB )						{ m_bIsUseVBIB = bUseVB;}
	BOOL	IsUseVBIB()									{ return m_bIsUseVBIB; }	
	
	VOID	SetRenderMapBox( BOOL bRender )				{ m_bRenderMapBox = bRender; }
	BOOL	IsRenderMapBox( )							{ return m_bRenderMapBox; }
	
	VOID	SetRenderTree( BOOL bRender )				{ m_bIsRenderTree = bRender; }
	BOOL	IsRenderTree()								{ return m_bIsRenderTree; }
	
	VOID	SetRenderGrass( BOOL bRender )				{ m_bIsRenderGrass = bRender; }
	BOOL	IsRenderGrass()								{ return m_bIsRenderGrass; }

	VOID	SetToolMode( BOOL bToolMode )				{ m_bToolMode = bToolMode; }
	BOOL	IsToolMode()								{ return m_bToolMode; }

	FLOAT	GetBspRenderDistance()							{ return m_fBspRenderDis; }
	VOID	SetBspRenderDistance( FLOAT fBspRenderDis )		{ m_fBspRenderDis = fBspRenderDis; }

	BOOL	GetCardType()									{ return m_bIsATICard; }
	VOID	SetCardType( BOOL bIsATI )						{ m_bIsATICard = bIsATI; }

	VOID	SetMipLodBais(	FLOAT fLodBais )				{ m_fMipLodBais = fLodBais; }
    FLOAT	GetMipLodBais( )								{ return m_fMipLodBais; }

    VOID	SetFullSceneAntialiasing( BOOL enabled )		{ m_bFullSceneAntialiasing = enabled; }
    BOOL	GetFullSceneAntialiasing( )						{ return m_bFullSceneAntialiasing; }

    void    SetCullDistance(float dist)
    {
        m_cullDistance = dist;
    }

    float   GetCullDistance() const
    {
        return m_cullDistance;
    }

	int		GetRenderHelper() { return m_RenderHelper; }
	void	ChangeRenderHelper() { m_RenderHelper++;if(m_RenderHelper > Floor_Collision_Helper) m_RenderHelper = None_Helper; }
	void	SetRenderHelper(ERenderHelper flag) { m_RenderHelper = flag; }

public:
	DWORD	m_dwSkinMeshVertexShaderID;
	DWORD	m_bUseSkinMesh;
	BOOL	m_bAlwayseWireFrameRendering;
	BOOL	m_bRenderBBox;
	BOOL	m_bLayerRender[4];
// 	BOOL	m_bFastLoadMex;

	BOOL	m_bIsUseVBIB;	//True使用,false不使用

	BOOL	m_bShowTerrain;	//True使用

	BOOL	m_bIsATICard;

	BOOL	m_bRenderMapBox;	//是否渲染地图 包围盒

	BOOL	m_bIsRenderTree;
	BOOL	m_bIsRenderGrass;

	//显卡 Render状态
	FLOAT	m_fBspRenderDis;
	BOOL	m_bEnjoinTwoSide;

    BOOL    m_bFullSceneAntialiasing;
    float   m_cullDistance;

	// 是否选中模型当前渲染模型，m_bRenderHelper为true时，选中模型隐藏非碰撞模型以外数据。（偷懒了，不想改渲染接口，仅供编辑器使用）
	BOOL	m_bIsRenderModelSelected;
	BOOL	IsRenderModelSelected() { return m_bIsRenderModelSelected; }
	void	SetRenderModelSelected(BOOL bRender) { m_bIsRenderModelSelected = bRender; }

	short	m_terrainLayer;	// 地表渲染层数
	short	GetTerrainRenderLayer() { return m_terrainLayer; }
	void	SetTerrainRenderLayer( short level ) { m_terrainLayer = min( 4,level ); 
												   m_terrainLayer = max( level, 2 );}

	BOOL	m_bIsPlayMapEffect;
	BOOL	IsPlayMapEffect() { return m_bIsPlayMapEffect; }
	void	SetPlayMapEffect(BOOL bPlay) { m_bIsPlayMapEffect = bPlay; }

	BOOL	m_bLockFPS;	// 是否锁帧
	short	m_nKeepFPS;	// 锁的帧数
	BOOL	IsLockFPS() { return m_bLockFPS; }
	void	SetLockFPS(BOOL bLock) { m_bLockFPS = bLock; }
	short	GetKeepFPS() { return m_nKeepFPS; }
	void	SetKeepFPS(short nFPS) { if( nFPS > 0 ) m_nKeepFPS = nFPS; }

	BOOL	m_bVSync;	// 是否垂直同步
	BOOL	IsVSync() { return m_bVSync; }
	void	SetVSync( BOOL bVSync ) { m_bVSync = bVSync; }
};
extern Config* GetMe3dConfig();
#endif 
