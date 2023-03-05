#ifndef MINIMAP_20031112_INC

#define MINIMAP_20031112_INC

#include "tga.h"
#include "globaldef.h"
#include "GlobalDef.h"
#include "NpcCoord.h"
#include <vector>
// #include "Tinyxml/tinyxml.h"
#include "MeUI/IconManager.h"

#define	DEALAYTIME	50
#define	MAX_MAP_COUNTS	19
//using namespace std;
/*
	小地图背景图是一个tga，
	大小不限制，
	
	小地图显示窗口是可变化大小的
	有两种状态，
	一种是平时放在游戏画面右上角的
	一种是整张显示的

	画面上每一个角色都会有一的动画icon
	可以过滤显示，
	比如当玩家显示开关关闭后，
	小地图上面就看不到玩家了，


	//
	需求改变，
	每张地图回有一张大尺寸的背景图，
	在小地图窗口，
	玩家只能看见部分地图，

	//
	首先得到地图的真实大小，
	然后读取地图背景图
	背景图按照约定，
	应该是地图实际大小的n倍，



*/



#define	BUTTON_SIZE_32		32
#define	BUTTON_SIZE_64		64
#define BUTTON_SIZE_128		128


#define MAPTEX_WIDTH 256
#define MAPTEX_HEIGHT 256


#define	NEWMAPSIZE_WIDTH		22			//修正后地图比例
#define	NEWMAPSIZE_HEIGHT	11

#define	MAP_CULL_TOP			0.125		//地图上界比例
#define	MAP_CULL_BOTTEM	0.875		//地图下界比例

#define	MAP_CULL_SIZE		0.75				//有效区域比例

#define	SCREEN_SIZE_1024	1024
#define	SCREEN_SIZE_768		768
#define	SCREEN_SIZE_800		800
#define	SCREEN_SIZE_600		600



class CPlayer;
struct NpcCoordInfo;
class CAdvancedMiniMap
{
public:
	enum
	{
		eMinMode,
		eMaxMode,
						//副本的时候显示地图
	};
	enum
	{
		eImage_Target = 0,			//锁定的目标
		eImage_TargetInRegionMap,			//锁定的目标

		eImage_Monster,
		eImage_DeadMonster,
		eImage_NormalNpc,			// 普通npc
		eImage_NpcDirectLoocked,	// 用于npc指引 在视野范围内 可以看到的
		eImage_Restore,				// 
		eImage_Weapon,				// 武器店
		eImage_Jewelry,				//
		eImage_Dress,				// 服装店
		eImage_Material,			// 材料商
		eImage_Transport,			// 传送点
		eImage_Cavalry,				// 
		eImage_Storage,				// 仓库
		eImage_Star,			// 
		eImage_MakeItem,			// 合成,精炼,强化NPC
		eImage_Activity,			// 活动NPC
		eImage_Feudal,			// 官府任务NPC
		eImage_Sale,			// 寄售商人NPC
		eImage_SpecialSale,			// 特殊兑换商
		eImage_GongXun,			// 贡献NPC
		eImage_MingWang,			// 名望NPC
		eImage_ShiZhuang,			// 时装NPC
		eImage_WenDa,			// 问答NPC
		eImage_JiNeng,			// 技能NPC
		eImage_PeiJian,			// 武器配件
		eImage_ShiWu,			// 食物
		eImage_YiZhan,			// 驿站
		eImage_ZaHuo,			// 杂货
		eImage_FenJie,			// 分解
		eImage_QianZhuang,			// 钱庄
		eImage_MoveStar,			// 移星
		eImage_SpecialRepair,			// 特修
		eImage_Patrol,			// 保留字0
		eImage_KeepWord1,			// 保留字1
		eImage_KeepWord2,			// 保留字2
		eImage_KeepWord3,			// 保留字3
		eImage_KeepWord4,			// 保留字4
		eImage_KeepWord5,			// 保留字5
		eImage_KeepWord6,			// 保留字6
		eImage_KeepWord7,			// 保留字7
		eImage_KeepWord8,			// 保留字8
		eImage_KeepWord9,			// 保留字9

		eImage_NpcDirect,			// Npc 指引
		eImage_MouseDirect,			// 怪物指引
		eImage_MiniMapPath,			// 路径显示

		eImage_YellowGanTanHao,
		eImage_WhiteGanTanHao,
		eImage_YellowWenHao,
		eImage_WhiteWenHao,


		eImage_RoleArrow,
		eImage_NpcPosMark,

		eImage_Player,
		eImage_Guild,			//相同工会
		eImage_Friend,			//朋友
		eImage_Teammate,			//队友
		eImage_Enemy,			//仇人

		eImage_Camera,			// 视角显示
		eImage_Me,
		eImage_PetAnimal,
		eImage_ProtectMonster,
        eImage_CampBattleS,     //阵营战场随军图标
        eImage_CampBattleT,     //阵营战场唐军图标
        eImage_CampBattleZL,    //阵营战场无人占领
		eImage_Max,
	};
	enum
	{
		eMaxMark = 32,
		eMaxMarkText = 32
	};
	struct SImageType
	{
		int		m_NpcType;
		string	strTypeString;
		int		m_Order;
	};
	struct Image
	{
		int	nTextureID;
		int nWidth;
		int nHeight;
		char shortcut[5];
		Image()
		{
			nTextureID = -1;
			nWidth = 0;
			nHeight = 0;
			memset(shortcut,0,5*sizeof(char));
			m_NpcType = 0;
		}
		string strEffectPath;
		int		m_NpcType;
	};

	struct MapImage 
	{
		int nImageType;
		int nPlayerId;
	};
	std::list<MapImage>			m_currMapImageList;
	void						AddMapImage(int nImage,int nPlayerId);

	struct SortNpcType
	{
		std::string strType;
		std::vector<int> vecSet;

		SortNpcType()
		{
			strType.clear();
			vecSet.clear();
		}
	};

	std::list<SortNpcType>   m_NpcSort;
public:
	CAdvancedMiniMap();
	~CAdvancedMiniMap();

	void		Destroy();
	void		Render( int nRoleX, int nRoleY );
	void		RenderNeedRedraw( int nMode, int nRoleX, int nRoleY );
	void		Run(int nRoleX, int nRoleY);
	int			GetImageMap( BYTE byNpcType );
	void		RenderTip( RECT &rcWindow ,const char * s);
	void		RefreshCurrMapTexture();
	BOOL		Create( int nMapRealWidth, 
						int nMapRealHeight,  
						char* pszFilename );
	BOOL		LoadImage( int nImage, const char* pszFilename,const char* shortcut = NULL,const char* effect = NULL/*,const char* pTypeString = NULL*/,int type = -1);
	void		LoadImages();
	BOOL		DrawTextUnderImage( RECT rcImage, const char* pszText, DWORD dwColor );
	BOOL		DrawImage(  RECT rcWindow, int nImageType, RECT& rcDst, bool target = false );

	void		GetRcSrcForMe( RECT& rcSrc );
	BOOL		DrawCameraImage( RECT rcWindow );
	void		GetImageWindowRect( RECT rcWindow,  int nImageType, int nImageX, int nImageY, RECT& rcDst , int nRoleX, int nRoleY, float fScale);
	void		CancelNPCPF();
	void		SetNpcInfo(const char* szName, double mapX, double mapY, bool bNpc);
	void		SetNpcInfo(const NpcCoordInfo* pInfo);
    // add [6/18/2008 whu]
    const NpcCoordInfo* getNpcInfo( int index );

	bool		MoveRoleToNPC( );

	BOOL		GetCurSelectNpc( D3DXVECTOR3& vPos );

	void		ProcessMinimapMouseDownL(int x, int y);

	Image*		GetImage(int index){return &m_images[index];}
	void		SetTargetNpc(const char* val);

	std::list<SImageType>& GetImageTypeList()  { return m_ImageTypeList; }
	std::list<SortNpcType>& GetNpcSortList(){return m_NpcSort;}
protected:
	static Image		m_images[eImage_Max];
	static int			m_nFontSizeOnRegionMap;
	static char			m_nFontNameOnRegionMap[256];
	std::vector<NpcCoordInfo>	m_vecNpcInfo;
	
	int			GetImageType(const char* pString);
protected:
	int m_minimapScreenRadius;
	int m_minimapScreenCenterX;
	int m_minimapScreenCenterY;
	int m_minimapScreenWidth;
	int m_minimapScreenHeight;

	int m_maxDimension;
	CWorldTile*  oldTile;
	int oldTexid;
	int m_texEdge;
	int m_xPixelOffset;
	int m_yPixelOffset;
	CPlayer* m_pPlayerCursorOn;
	CPlayer* m_pTargetPlayer;
	std::string m_strTargetNpc;
	bool m_ShowTeamTip;
	bool m_lastRefreshTime;
	S_TextTipInfo m_TipInfo;
	bool m_bInitialize;

protected:
	void						InsertImageTypeByOrder(SImageType& type);
	std::list<SImageType>		m_ImageTypeList;
};


extern CAdvancedMiniMap* GetAdvancedMiniMap();
#endif