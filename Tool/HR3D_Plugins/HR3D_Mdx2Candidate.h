#ifndef _hr3d_mdx2candidate_h
#define _hr3d_mdx2candidate_h

#include "particleemittersettingdlg.h"
#include "ribbonemittersettingdlg.h"

#include "max.h"
#include "hr3d_maxinterface.h"

#include "defines.h"

#define STRING_ADD		"Add"
#define STRING_BLEND	"Blend"
#define STRING_MODULATE	"Modulate"
#define STRING_MOD2X	"Mod2X"
#define	STRING_ALPHAKEY	"AlphaKey"

#define STRING_HEAD		"Head"
#define STRING_TAIL		"Tail"
#define STRING_BOTH		"Both"

#define STRING_BINDNONE ""
#define STRING_BINDLEFTHAND "LeftHand"
#define STRING_BINDRIGHTHAND "RightHand"
#define STRING_BINDLEFTBACK "LeftBack"
#define STRING_BINDRIGHTBACK "RightBack"

#define STR_TEXTURENAME "TextureName"
#define STR_EDGEPERSEC	"EdgePerSec"
#define STR_EDGELIFE	"EdgeLife"
#define STR_VERTEXALPHA	"VertexAlpha" 
#define STR_BINDPARTNAME "BindPartName"
#define STR_BLEND_MODE "BlendMode"

class CMdxAnimCtrl;
/*
	首先，从选择的节点构成一棵树，
	列举材质，贴图
	剖分网格体，
	得到每个网格体的动画轨迹，
	载入默认配置文件，读取参数，
	在窗口中预览，
	在面板中调整参数
*/
class CCreateMdxParam;
class HR3D_Mdx2Candidate
{
public:
	struct Texture
	{
		Texture()
		{
			memset( szName, 0x00, sizeof( szName ) );
		}
		char	szName[MAX_PATH];
	};
	struct Textures
	{
	public:
		int AddTexture( Texture& t );
		int GetTextureCount(){ return vectorTexture.size(); }
		Texture* GetTexture( int i ){ return &vectorTexture[i]; }
	protected:
		std::vector<Texture> vectorTexture;
		std::vector<int> vectorTextureId;
	};
	struct Material
	{
		std::vector<HR3D_Mdx2Layer> vectorLayer;
		std::vector<HR3D_MaxInterface::ColorTrack> vectorColorTrack;
		
		Material(){}
	};
	struct Materials
	{
		std::vector<Material> vectorMtl;
	};
	typedef struct 
	{
		int nVertexId;
		int nParentVertID;
		Point3 pos;
		Point3 normal;
		DWORD color;
		float u, v;
		// realrender added 2003.11.17
		// 为了适应所有的骨骼系统，每个定点保存自己的一份骨骼影响数据
		HR3D_MaxInterface::BoneGroup bg;
	} SplitVertex;
	typedef struct
	{
		short nMaxVertexId[3];
	} MtlFace;
	struct GeomChunk
	{
		enum { eMaxUVLayer = 4 };

		std::vector<Point3> vectorVertex;
		std::vector<Point3> vectorNormal;

		HR3D_Vector2 *m_pUVs[eMaxUVLayer];
		short	m_shUVLayerCount;
		short	m_shLightmapLayer;	// 光照图所在UV层

		std::vector<BYTE> vectorBGId;		// bone group ids
		std::vector<MtlFace> vectorFace;
		
		std::vector<SplitVertex> vectorSplitVertex;
		// realrender added 2005.08.17
		std::vector<DWORD> vectorColor;
		// realrender added 2004.11.10
		//std::vector<MtlFace> vectorShiningFace;
		int nMtlId;
		int nModifierType;
		//int nPartId;
		int nType;
		DWORD dwFlag;
		char szNodename[MAX_PATH];
		char szParentName[ MAX_PATH ];

		int  nParentID;
		int  nChildID;
		// realrender added 2004.02.10
		BOOL bHasUnEnveloppedVertices;		// 含有未封套顶点
		BOOL bHasNoneMtlFaces;				// 含有没有材质的面
		// realrender added 2004.07.14
		BOOL bHasReplacableTexture;			//
		StdMat* pStdMtl;
		Point3	ptCenter;
		GeomChunk()
		{
			nParentID		= -1;
			nChildID		= -1;
			nMtlId = -1;
			nModifierType = -1;
			//nPartId = -1;
			nType = -1;
			szNodename[0] = 0;
			szParentName[ 0 ] = 0;
			bHasUnEnveloppedVertices = FALSE;
			bHasUnEnveloppedVertices = FALSE;
			bHasReplacableTexture = FALSE;
			pStdMtl = NULL;
			dwFlag = 0;
		};
	};
	struct Geometry
	{
		std::vector<GeomChunk> vectorChunk;
	};
	struct BoneGroups
	{
		std::vector<HR3D_MaxInterface::BoneGroup> vectorBoneGroup;
	};
	struct Keyframe
	{
		int nTime;
		float fParam[4];
	};
	struct Track
	{
		std::vector<Keyframe> vectorKeyframe;
	};
	struct Attachment
	{
		INode* pNode;
		int nAttachBoneID;
		char szName[MEX2_MAX_NAME];
		HR3D_Matrix matInit;
		Attachment()
		{
			pNode = NULL;
			nAttachBoneID = -1;
			szName[0] = 0;

		}
	};
	struct Attachments
	{
		std::vector<Attachment> vectorAttachment;
	};
	struct Bone
	{
		Bone()
		{
			memset( szName, 0x00, sizeof( szName ) );
			memset( szParentName, 0x00, sizeof( szParentName ) );
		}
		INode* pNode;
		char szName[MEX2_MAX_NAME];
		char szParentName[MEX2_MAX_NAME];
		int nParentId;
		std::vector<int> vectorChildId;
		
		HR3D_MaxInterface::Track track;
		
		// 一下是为关键帧方案做准备的，但是现在不用了，
		BOOL bAbsoluteTrack;		// 是否使用绝对的变换
		Track trackTrans;
		Track trackRot;
		Track trackScale;
		HR3D_Vector vPivot;
		HR3D_Quaternion qPivotRot;


		HR3D_Vector vTrans;
		HR3D_Quaternion qRot;
		HR3D_Vector vScale;

		HR3D_Vector vTransAbs;
		HR3D_Quaternion qRotAbs;
		HR3D_Vector vScaleAbs;

		HR3D_Matrix matInv;
	};
	struct Skeleton
	{
		std::vector<Bone> vectorBone;
		std::vector<int> vectorRootBoneId;
		int FindBone( const char* pszBoneName )
		{
			for( int i = 0; i < vectorBone.size(); i++ )
			{
				if( stricmp( pszBoneName, vectorBone[i].szName ) == 0 )
					return i;
			}
			return -1;
		}
	};
	struct Light
	{
		DWORD		dwFlag;
		char		szName[MEX2_MAX_NAME];
		char		szParentBoneName[MEX2_MAX_NAME];
		int			nParentBoneId;
		Point3		vPivot;		// 原始位置
		float		fRange;		// 照射范围
		float		fIntense;
		float		fAttenuration[3];	// 衰减参数
		HR3D_MaxInterface::ColorTrack colorTrack;

	};
	struct Lights
	{
		std::vector<Light> vectorLight;
	};


	//struct Attachment
	//{
	//	Attachment():nParentBoneId(-1)
	//	{
	//		memset( szParentBoneName, 0x00, sizeof( szParentBoneName ) );
	//	}
	//	char szParentBoneName[MEX2_MAX_NAME];
	//	int nParentBoneId;
	//};
	struct RibbonEmitter
	{
		RibbonEmitter():nParentBoneId(-1)
		{
			memset( szParentBoneName, 0x00, sizeof( szParentBoneName ) );
			memset( szBindPartName, 0x00, sizeof( szBindPartName ) );
		}
		char szParentBoneName[MEX2_MAX_NAME];
		char szBindPartName[MEX2_MAX_NAME];
		int nParentBoneId;
		int nTextureId;
		Point3 vLine[2];
		RibbonEmitterSettingDlg setting;
	};
	struct RibbonEmitters
	{
		std::vector<RibbonEmitter> vectorRibbonEmitter;
	};

	struct Billboard
	{
		Billboard():nParentBoneId(-1)
		{
			memset( szParentBoneName, 0x00, sizeof( szParentBoneName ) );
		}
		char szParentBoneName[MEX2_MAX_NAME];
		int nParentBoneId;
		std::vector<Point3> vectorCenter;
		std::vector<float>	vectorSize;
		int		nRow, nCol;
	};
	struct Billboards
	{
		std::vector<Billboard> vectorBillboard;
	};
	struct ParticleEmitter
	{
		char	szParentBoneName[MEX2_MAX_NAME];
		char	szBindPartName[MEX2_MAX_NAME];
		char	szNodeName[MEX2_MAX_NAME];

		int		nParentBoneId;
		Point3	vPivot;
		int		nTextureId;
		Point3	vPlaneNormal;
		Point3	vPlaneXAxis;
		Point3	vPlaneYAxis;
		
		BOOL	bUseTimeBasedCell;
		int		nSeqLoopTimes;

		BOOL	m_bRotateParticle;
		int		m_nRotate360DegreeCostTime;

		BOOL	m_bRandomDir;				// 产生的粒子贴图是否随即方向                added by ZhuoMeng.Hu [8/5/2010]	[>104]
		BOOL    m_bNoSelfRotate;			// 粒子是否跟随发射器的变换而旋转增加开关    added by zhuomeng.hu [1/30/2011]	[>108]

		BOOL    m_bXYInWorldSpace;			// 粒子的XYQuad模式下，在世界坐标系中放平    added by zhuomeng.hu [3/17/2011]	[>110]
		BOOL    m_bUVRandomFirstCell;		// 粒子的UV动画是否随机产生第一帧            added by zhuomeng.hu [3/10/2011]	[>100]

		ParticleEmitterSettingDlg settingDlg;

		ParticleEmitter()
		{
			szParentBoneName[0] = 0;
			szBindPartName[0] = 0;
			nParentBoneId = -1;
			bUseTimeBasedCell = FALSE;
			nSeqLoopTimes = 0;

			m_bRotateParticle = TRUE;
			m_nRotate360DegreeCostTime = 0;

			m_bRandomDir = false;
			m_bNoSelfRotate = true;
			m_bUVRandomFirstCell = false;
			m_bXYInWorldSpace = true;
		};
	};
	struct ParticleEmitters
	{
		std::vector<ParticleEmitter> vectorEmitter;
	};
public:
	HR3D_Mdx2Candidate():
		m_dwTime(0),
		m_nFrameId(0),
		m_pCreateParam(NULL),
		m_pAnimCtrl(NULL){}
	~HR3D_Mdx2Candidate();
	BOOL CreateFromNode( INode* pRootNode, CCreateMdxParam* pParam );
	// realrender added 2003.09.27
	BOOL Create( CCreateMdxParam* pParam );
	BOOL CreateSkeleton( INode* pRootNode );
	BOOL CreateSkeleton2( INode* pRootNode );

	BOOL CreateMtl( Mtl* pMtl, Materials& mtls );
	BOOL GetTrack( Track& track, INode* pNode, int nType, float fScale = 1.0f );
	BOOL GetTrack2( Track& track, INode* pNode, int nType );

	// related parent
	BOOL GetTrack3( Track& track, INode* pNode, int nType );
	BOOL GetFrameParam( Track& track, int nType, int nTime, Keyframe& frame );
	void CalcMatrix( Keyframe& trans, Keyframe& rot, Keyframe& scale, HR3D_Matrix& mat );
	int FindTextureId( const char* pszFilename );
	void CreateGeometry( INode* pNode );
	// realrender added 2004.08.06
	void CreateLight( INode* pNode );
	// realrender added 2003.10.07
	void CreateRibbonEmitter( INode* pNode );
	// realrender added 2003.10.08
	void CreateBillboard( INode* pNode );
	// realrender added 2003.12.16
	void CreateParticleEmitter( INode* pNode );

	
	HR3D_Matrix* GetBoneMatrix( const char* pszBoneName );

	// realrender added 2003.10.08
	INode* GetFirstBoneAncestor( INode* pNode );

	int FindBoneGroup( HR3D_MaxInterface::BoneGroup* infls );
	int FindTexture( Texture* pTexture );
	int FindMtl( Material* pMtl );
	int FindBone( const char* pszBoneName );
	void ProjBoneGroups();

	// realrender added 2003.10.13
	BOOL Combine2Chunk( GeomChunk* pChunk0, GeomChunk* pChunk1 );

	void Log( const char* pszFilename );

	void Update( DWORD dwTime ){ m_dwTime = dwTime; }
	void Render();
	void RenderChunk( GeomChunk* pChunk );
	void RenderChunk2( GeomChunk* pChunk );
	BOOL SaveToFile( const char* pszFilename );
	BOOL SaveMdx( const char* pszFilename, BOOL bConvTexturePath = TRUE );
	// realrender added 2003.12.22
	BOOL ConvertTextures( const char* pszMdxFilename );
	// realrender added 2004.01.04
	BOOL CreateMdx( CCreateMdxParam* pParam );

	BOOL AddBillboard( GeomChunk* pChunk );
	BOOL GetSpecularFaces( GeomChunk* pChunk, std::vector<int>* pvectorFace );
	BOOL GenSpecularChunk( GeomChunk* pChunk, GeomChunk* pNormalChunk, GeomChunk* pSpecularChunk, std::vector<int>* pvectorFace );
	BOOL RemapChunk( GeomChunk* pParent, GeomChunk* pChild );
public:
	Mex2Version m_version;
	Textures	m_textures;
	Materials	m_mtls;
	Geometry	m_geometry;
	BoneGroups	m_boneGroups;
	Skeleton	m_skeleton;
	//Anims		m_anims;
	Attachments	m_attachments;
	RibbonEmitters	m_ribbonEmitters;
	//Billboards	m_billboards;
	ParticleEmitters m_particleEmitters;
	// realrender added 2004.08.06
	Lights		m_lights;
	Geometry	m_billboards;

	int			m_nFrameId;
	CMdxAnimCtrl*	m_pAnimCtrl;

	CCreateMdxParam* m_pCreateParam;

protected:
	DWORD		m_dwTime;
	
};

// 在mdx2输出之前，需要设置当前mdx2的的一些参数
// 是否转换到父空间
// 是否获取动画
class CCreateMdxParam
{
public:
	CCreateMdxParam():	m_bConvertToParentSpace(FALSE),
						m_bGetTrack(TRUE),
						m_pRootNode(NULL),
						m_bCreateDefaultCharSkeleton(FALSE){}
	void	ConvertToParentSpace( BOOL b ){ m_bConvertToParentSpace = b; }
	BOOL	IsConvertToParentSpace(){ return m_bConvertToParentSpace; }
	void	GetTrack( BOOL b ){ m_bGetTrack = b; }
	BOOL	IsGetTrack(){ return m_bGetTrack; }
	void	SetRootNode( INode* pNode ){ m_pRootNode = pNode; }
	INode*	GetRootNode(){ return m_pRootNode; }
	// realrender added 2003.10.10
	void	CreateDefaultCharSkeleton( BOOL b ){ m_bCreateDefaultCharSkeleton = b; }
	BOOL	IsCreateDefaultCharSkeleton(){ return m_bCreateDefaultCharSkeleton; }
	
protected:
	BOOL	m_bConvertToParentSpace;
	BOOL	m_bGetTrack;
	INode*	m_pRootNode;
	BOOL	m_bCreateDefaultCharSkeleton;

};

#endif