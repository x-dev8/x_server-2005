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
	С��ͼ����ͼ��һ��tga��
	��С�����ƣ�
	
	С��ͼ��ʾ�����ǿɱ仯��С��
	������״̬��
	һ����ƽʱ������Ϸ�������Ͻǵ�
	һ����������ʾ��

	������ÿһ����ɫ������һ�Ķ���icon
	���Թ�����ʾ��
	���統�����ʾ���عرպ�
	С��ͼ����Ϳ���������ˣ�


	//
	����ı䣬
	ÿ�ŵ�ͼ����һ�Ŵ�ߴ�ı���ͼ��
	��С��ͼ���ڣ�
	���ֻ�ܿ������ֵ�ͼ��

	//
	���ȵõ���ͼ����ʵ��С��
	Ȼ���ȡ��ͼ����ͼ
	����ͼ����Լ����
	Ӧ���ǵ�ͼʵ�ʴ�С��n����



*/



#define	BUTTON_SIZE_32		32
#define	BUTTON_SIZE_64		64
#define BUTTON_SIZE_128		128


#define MAPTEX_WIDTH 256
#define MAPTEX_HEIGHT 256


#define	NEWMAPSIZE_WIDTH		22			//�������ͼ����
#define	NEWMAPSIZE_HEIGHT	11

#define	MAP_CULL_TOP			0.125		//��ͼ�Ͻ����
#define	MAP_CULL_BOTTEM	0.875		//��ͼ�½����

#define	MAP_CULL_SIZE		0.75				//��Ч�������

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
						//������ʱ����ʾ��ͼ
	};
	enum
	{
		eImage_Target = 0,			//������Ŀ��
		eImage_TargetInRegionMap,			//������Ŀ��

		eImage_Monster,
		eImage_DeadMonster,
		eImage_NormalNpc,			// ��ͨnpc
		eImage_NpcDirectLoocked,	// ����npcָ�� ����Ұ��Χ�� ���Կ�����
		eImage_Restore,				// 
		eImage_Weapon,				// ������
		eImage_Jewelry,				//
		eImage_Dress,				// ��װ��
		eImage_Material,			// ������
		eImage_Transport,			// ���͵�
		eImage_Cavalry,				// 
		eImage_Storage,				// �ֿ�
		eImage_Star,			// 
		eImage_MakeItem,			// �ϳ�,����,ǿ��NPC
		eImage_Activity,			// �NPC
		eImage_Feudal,			// �ٸ�����NPC
		eImage_Sale,			// ��������NPC
		eImage_SpecialSale,			// ����һ���
		eImage_GongXun,			// ����NPC
		eImage_MingWang,			// ����NPC
		eImage_ShiZhuang,			// ʱװNPC
		eImage_WenDa,			// �ʴ�NPC
		eImage_JiNeng,			// ����NPC
		eImage_PeiJian,			// �������
		eImage_ShiWu,			// ʳ��
		eImage_YiZhan,			// ��վ
		eImage_ZaHuo,			// �ӻ�
		eImage_FenJie,			// �ֽ�
		eImage_QianZhuang,			// Ǯׯ
		eImage_MoveStar,			// ����
		eImage_SpecialRepair,			// ����
		eImage_Patrol,			// ������0
		eImage_KeepWord1,			// ������1
		eImage_KeepWord2,			// ������2
		eImage_KeepWord3,			// ������3
		eImage_KeepWord4,			// ������4
		eImage_KeepWord5,			// ������5
		eImage_KeepWord6,			// ������6
		eImage_KeepWord7,			// ������7
		eImage_KeepWord8,			// ������8
		eImage_KeepWord9,			// ������9

		eImage_NpcDirect,			// Npc ָ��
		eImage_MouseDirect,			// ����ָ��
		eImage_MiniMapPath,			// ·����ʾ

		eImage_YellowGanTanHao,
		eImage_WhiteGanTanHao,
		eImage_YellowWenHao,
		eImage_WhiteWenHao,


		eImage_RoleArrow,
		eImage_NpcPosMark,

		eImage_Player,
		eImage_Guild,			//��ͬ����
		eImage_Friend,			//����
		eImage_Teammate,			//����
		eImage_Enemy,			//����

		eImage_Camera,			// �ӽ���ʾ
		eImage_Me,
		eImage_PetAnimal,
		eImage_ProtectMonster,
        eImage_CampBattleS,     //��Ӫս�����ͼ��
        eImage_CampBattleT,     //��Ӫս���ƾ�ͼ��
        eImage_CampBattleZL,    //��Ӫս������ռ��
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