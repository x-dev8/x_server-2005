#pragma once

#include "external/HR3D_Vector.h"
#include "external/HR3D_Quaternion.h"

#include "external/DataChunkWriter.h"

#define MEX2_MAX_NAME 80

enum ECKFMdx2RenderFlag
{
	HR3D_MDX2_SPECULARENABLE	=	1<<12,
	HR3D_MDX2_SORTBYFARZ		=	1<<13,
	HR3D_MDX2_ALPHABLEND		=	1<<14,
	HR3D_MDX2_ALPHATEST			=	1<<15,
	HR3D_MDX2_TWOSIDED			=	1<<16,
	HR3D_MDX2_BLEND				=	1<<17,
	HR3D_MDX2_ADD				=	1<<18,
	HR3D_MDX2_MODULATE			=	1<<19,
	HR3D_MDX2_MODULATE2X		=	1<<20,
	HR3D_MDX2_MODULATE4X		=	1<<21,
	HR3D_MDX2_ALPHAKEY			=	1<<22,
	HR3D_MDX2_UNSHADED			=	1<<23,
	HR3D_MDX2_UNFOGGED			=	1<<24,
	HR3D_MDX2_ZWRITEENABLE		=	1<<25,
};

enum ECKFMex2ParticleEmitterFlag
{
	MEX2_PARTICLE_EMITTER_SQUIRT		=	1<<13,
	MEX2_PARTICLE_EMITTER_LINEEMITTER	=	1<<14,
	MEX2_PARTICLE_EMITTER_HEAD			=	1<<15,
	MEX2_PARTICLE_EMITTER_TAIL			=	1<<16,
	MEX2_PARTICLE_EMITTER_BOTH			=	1<<17,
	MEX2_PARTICLE_EMITTER_PARTICLEINMODELSPACE	=	1<<18,
	MEX2_PARTICLE_EMITTER_XYQUAD		=	1<<19,
	MEX2_PARTICLE_EMITTER_LOCKEMITTER	=	1<<20,
	MEX2_PARTICLE_EMITTER_TANGENT		=	1<<21,
};


enum
{
	Mex2BbrdFlag_AlwayseLookAtCamera	= 1<<0,
	Mex2BbrdFlag_AlwayseStand			= 1<<1,
	Mex2BbrdFlag_VerticalGround			= 1<<2,
	Mex2BbrdFlag_AlwayseStand_ForEffect = 1<<3,
	Mex2BbrdFlag_OriginalPointCircling	= 1<<4,
	Mex2BbrdFlag_SmoothRotating         = 1<<5,
	Mex2BbrdFlag_FrontOffset            = 1<<6
};
enum 
{
	eNormalTexture		=	1<<0,
	eReplaceableTexture =	1<<1,
};

enum eRenderFlag
{
	eWireFrame		= 1<<0,
	eAlphaBlend		= 1<<1,
	eLinearFilter	= 1<<2,
	eSortByFarZ		= 1<<3,

	eDstBlendOne	= 1<<4,
	eUseTextureColor= 1<<5,
	eZFunLess		= 1<<6,
	eNotUseSkinMesh	= 1<<7,

	eOpModulate1X	= 1<<8,
	eOpModulate2X	= 1<<9,
	eOpModulate4X	= 1<<10,
	eOpAdd			= 1<<11,

	eGlobalTransparent = 1<<12,
	eNeetNotDraw	= 1<<13,

	eRenderTreeLeaf = 1<<14,
	eRenderSkyBox	= 1<<15,

	//eNeedNotSetIB	= 1<<14,
	//eNeedNotSetVB	= 1<<15,
	eUseVB			= 1<<16,
	eUseIB			= 1<<17,
	eShimmer		= 1<<18,// modified, jiayi, [2010/6/18],eIsTerrain
	eNeedNotSetTexture = 1<<19,
	eSpecularEnable = 1<<20,

	// 	eOpBlendTexutrueAlpha = 1<<21,
	// 
	// 	eMipmapShiftForBlur = 1<<22,
	eUClamp			= 1<<21,
	eVClamp		    = 1<<22,
	eZDisable		= 1<<23,
	eZWriteDisable	= 1<<24,
	ePointFilter	= 1<<25,
	eAlphaTest		= 1<<26,
	eCullCCW		= 1<<27,
	eTwoSided		= 1<<28,
	//eLightingEnable	= 1<<29,
	eLightingDisable = 1<<29,
	eMipmapLinear	= 1<<30,
	eNoMipmap		= 1<<31,

};

class IHRMdxLayer
{
public:
	virtual void SetBlendMode( int nBlendMode ) = 0;
	virtual int GetBlendMode() = 0;
	virtual void SetFlag( DWORD dwFlag ) = 0;
	virtual DWORD GetFlag() = 0;
	virtual void SetTextureID( int nTextureID ) = 0;
	virtual int GetTextureID() = 0;
	virtual void SetAlpha( float fAlpha ) = 0;
	virtual float GetAlpha() = 0;
	virtual BOOL IsSameLayer( IHRMdxLayer* pLayer ) = 0;
};

/*
* 2012.7.2 wangshuai
* 使用dwBlendMode
*/
struct HR3D_Mdx2RibbonEmitterSetting
{
	HR3D_Vector vLines[2];
	char szParentBonename[MEX2_MAX_NAME];
	int nParentBoneId;
	int nTextureId;
	DWORD dwEdgePerSec;
	DWORD dwEdgeLifeSec;
	DWORD dwVertexAlpha;
	DWORD dwBlendMode;
};

// mdx2 层
class HR3D_Mdx2Layer:public IHRMdxLayer
{
public:
	HR3D_Mdx2Layer():
	  m_nBlendMode(0),
		  m_dwFlag(0),
		  m_nTextureID(-1),
		  m_fAlpha(1.0f){}
	  void SetBlendMode( int nBlendMode ){ m_nBlendMode = nBlendMode; }
	  int GetBlendMode(){ return m_nBlendMode; }
	  void SetFlag( DWORD dwFlag ){ m_dwFlag = dwFlag; }
	  DWORD GetFlag(){ return m_dwFlag; }
	  void SetTextureID( int nTextureID ){ m_nTextureID = nTextureID; }
	  int GetTextureID(){ return m_nTextureID; }
	  void SetAlpha( float fAlpha ){ m_fAlpha = fAlpha; }
	  float GetAlpha(){ return m_fAlpha; }
	  BOOL IsSameLayer( IHRMdxLayer* pLayer )
	  {
		  if( !pLayer )
		  {
			  assert( false );
			  return FALSE;
		  }
		  if( GetAlpha() != pLayer->GetAlpha() )
			  return FALSE;
		  if( GetBlendMode() != pLayer->GetBlendMode() )
			  return FALSE;
		  if( GetFlag() != pLayer->GetFlag() )
			  return FALSE;
		  if( GetTextureID() != pLayer->GetTextureID() )
			  return FALSE;
		  return TRUE;
	  }

protected:
	int		m_nBlendMode;
	DWORD	m_dwFlag;
	int		m_nTextureID;
	float	m_fAlpha;
};

// mdx2 face
struct HR3D_Mdx2Face
{
	short nId[3];
};

class IHRMdxTexture
{
public:
	virtual void SetName( const char* pszName ) = 0;
	virtual const char* GetName() = 0;
};

// mdx2 贴图
class HR3D_Mdx2Texture:public IHRMdxTexture
{
public:
	void SetName( const char* pszName );
	const char* GetName(){ return szName; }
protected:
	char	szName[MAX_PATH];
};

enum
{
	MODIFIER_NONE,
	MODIFIER_SKIN,
	MODIFIER_PHYSIQUE
};

class HR3D_Matrix
{
public:
	float m[4][4];
};

struct HR3D_Mdx2ColorKey
{
	float dr;
	float dg;
	float db;

	float ar;
	float ag;
	float ab;

	float sr;
	float sg;
	float sb;

	float alpha;
	float shinstr;
	float selfillum;

	float uoffset;
	float voffset;

	DWORD dwBlendMode;

	float	reserved[1];
};

// mex2版本
struct Mex2Version
{
	// 2005.10.10 升级为101版本(1.01)
	// 2009.3.3 升级为102版本，增加骨骼权重数据
	// 2009.04.07 升级为103版本，改变mex格式
	// added, jiayi, [2010/7/29], 变更104,添加visibility支持
	// added by zhuomeng.hu	 [8/6/2010], 变更105， 添加产生随机方向粒子的功能
	// added, [8/10/2010 zhangjiayi], 106.变更visibility的存储方式，节省资源
	// added by zhuomeng.hu		[8/17/2010], 变更107， 修正粒子本地 X 坐标反向问题
	// added, [11/16/2010 qiuli], 变更108，动画格式更改，逐帧动画改为关键帧动画
	// added by zhuomeng.hu		[1/30/2011]，变更109， 粒子是否跟随发射器坐标旋转增加开关
	// added by zhuomeng.hu		[3/10/2011]，变更110， 粒子的UV动画增加随机第一帧的开关
	// added by zhuomeng.hu		[3/17/2011]，变更111， 粒子的XYQuad模式下，可以勾选在世界坐标系中放平
	Mex2Version() : dwVersion(105) {}
	DWORD	dwVersion;

};

struct HR3D_Mdx2GeoChunkProperty
{
	enum
	{
		eStatic = 0,
		eBillboard,
		eLaser,
		//eRibbonEmitter, 
		eDecal,
		eFloor,
		eSupperFloor,
		eCollision,
		eDynamic,
		eRFloor,
		eRCollision,
		eSkeleton,
		eShimmer,
		eAlphaBox,
		eNoShadow,
		eMax
	};
	int		nType;
	float	fBillboardSize;
	DWORD	dwFlag;
	HR3D_Mdx2GeoChunkProperty():	nType(eStatic),
		fBillboardSize(0),
		dwFlag(0){}
};

struct Mex2ParticleEmitterSetting
{
	DWORD		dwFlag;
	char		szName[MEX2_MAX_NAME];	// 80 byte
	int			nParentBoneId;	// 跟随骨骼运动
	HR3D_Vector	vPivot;		// 原始位置

	// 发射器选项
	int			nCount;			// 粒子数目
	float		fSpeed;			// 粒子创建时的初始速度
	float		fVariation;		// speed变化振幅
	float		fConeAngle;		// 喷射cone的夹角
	float		fGravity;		// 重力
	// 时间选项
	float		fLifeSpan;		// 生命
	float		fEmissionRate;	// 每秒钟创建粒子数目
	float		fWidth;			
	float		fHeight;		// 发射器面板的大小
	// 贴图选项
	DWORD		dwBlendMode;	// 混合模式
	int			nRow;
	int			nCol;			// 贴图材质的网格数

	// 粒子选项
	// head, tail说明
	// head是一个正方形的billboard
	// tile是一个长方形billboard，沿着粒子的运动方向，长度=fTailLength
	DWORD		dwPart;
	float		fTailLength;	// 拖尾长度
	float		fMiddleTime;	// 生命的middle key，相对时间

	int			nSegmentColor[3][3];	// start/middle/end, multiply粒子颜色
	int			nAlpha[3];				// start/middle/end
	float		fParticleScaling[3];	// start/middle/end
	DWORD		dwUVAnimFps;			// uv动画的播放速率
	DWORD		dwLifeSpanHeadUVAnim[3];	// start/middle/end
	DWORD		dwDecayHeadUVAnim[3];		// start/middle/end
	DWORD		dwLifeSpanTailUVAnim[3];		// start/middle/end
	DWORD		dwDecayTailUVAnim[3];	// start/middle/end
	int			nTextureId;				// 贴图id
	int			nPriorityPlane;			// 优先级平面
};

struct Mex2ParticleEmitterSetting2:public Mex2ParticleEmitterSetting
{
	HR3D_Vector vPlaneNormal;
	HR3D_Vector vPlaneXAxis;
	HR3D_Vector vPlaneYAxis;
	Mex2ParticleEmitterSetting2() {}
};

// added by zhuomeng.hu		[2/12/2011]
struct Mex2ParticleEmitterSetting3 : public Mex2ParticleEmitterSetting2
{
	Mex2ParticleEmitterSetting3()
	{
		fLifeSpanMax = 0.0f;
		fScaleRateMin = 1.0f;
		fScaleRateMax = 1.0f;
		bContraryColor = false;
	}
	const Mex2ParticleEmitterSetting3& operator =( const Mex2ParticleEmitterSetting2& emtSetting )
	{
		dwFlag = emtSetting.dwFlag;
		sprintf_s( szName, sizeof( szName ) / sizeof( char ) - 1, "%s", emtSetting.szName );
		nParentBoneId = emtSetting.nParentBoneId;
		vPivot = emtSetting.vPivot;
		nCount = emtSetting.nCount;
		fSpeed = emtSetting.fSpeed;
		fVariation = emtSetting.fVariation;
		fConeAngle = emtSetting.fConeAngle;
		fGravity = emtSetting.fGravity;
		fLifeSpan = emtSetting.fLifeSpan;
		fEmissionRate = emtSetting.fEmissionRate;
		fWidth = emtSetting.fWidth;
		fHeight = emtSetting.fHeight;
		dwBlendMode = emtSetting.dwBlendMode;
		nRow = emtSetting.nRow;
		nCol = emtSetting.nCol;
		dwPart = emtSetting.dwPart;
		fTailLength = emtSetting.fTailLength;
		fMiddleTime = emtSetting.fMiddleTime;
		dwUVAnimFps = emtSetting.dwUVAnimFps;
		nTextureId = emtSetting.nTextureId;
		nPriorityPlane = emtSetting.nPriorityPlane;
		for( int i = 0; i < 3; ++i )
		{
			for( int j = 0; j < 3; ++j )
			{
				nSegmentColor[i][j] = emtSetting.nSegmentColor[i][j];
			}
			nAlpha[i] = emtSetting.nAlpha[i];
			fParticleScaling[i] = emtSetting.fParticleScaling[i];
			dwLifeSpanHeadUVAnim[i] = emtSetting.dwLifeSpanHeadUVAnim[i];
			dwDecayHeadUVAnim[i] = emtSetting.dwDecayHeadUVAnim[i];
			dwLifeSpanTailUVAnim[i] = emtSetting.dwLifeSpanTailUVAnim[i];
			dwDecayTailUVAnim[i] = emtSetting.dwDecayTailUVAnim[i];
		}

		vPlaneNormal = emtSetting.vPlaneNormal;
		vPlaneXAxis = emtSetting.vPlaneXAxis;
		vPlaneYAxis = emtSetting.vPlaneYAxis;

		fLifeSpanMax = 0.0f;
		fScaleRateMin = 1.0f;
		fScaleRateMax = 1.0f;
		bContraryColor = false;
		return *this;
	}

	float fLifeSpanMax;     // 生命随机最大值，仅当此值大于 fLifeSpan 有效
	float fScaleRateMin;    // 大小缩放比例最小随机值，仅当此值小于 fScaleRateMin 有效
	float fScaleRateMax;    // 大小缩放比例最大随机值，仅当此值大于 fScaleRateMax 有效
	bool  bContraryColor;   // 粒子顶点是否反色
};

// added by zhuomeng.hu		[2/18/2011]
struct Mex2ParticleEmitterSetting4 : public Mex2ParticleEmitterSetting3
{
	Mex2ParticleEmitterSetting4()
	{
		bAngleChangeByCone = false;
		bTailLengthChange = false;

		for( int i = 0; i < 3; ++i )
		{
			fTailLengthChange[i] = 0.0f;
		}
	}

	const Mex2ParticleEmitterSetting4& operator =( const Mex2ParticleEmitterSetting3& emtSetting)
	{
		dwFlag = emtSetting.dwFlag;
		sprintf_s( szName, sizeof( szName ) / sizeof( char ) - 1, "%s", emtSetting.szName );
		nParentBoneId = emtSetting.nParentBoneId;
		vPivot = emtSetting.vPivot;
		nCount = emtSetting.nCount;
		fSpeed = emtSetting.fSpeed;
		fVariation = emtSetting.fVariation;
		fConeAngle = emtSetting.fConeAngle;
		fGravity = emtSetting.fGravity;
		fLifeSpan = emtSetting.fLifeSpan;
		fEmissionRate = emtSetting.fEmissionRate;
		fWidth = emtSetting.fWidth;
		fHeight = emtSetting.fHeight;
		dwBlendMode = emtSetting.dwBlendMode;
		nRow = emtSetting.nRow;
		nCol = emtSetting.nCol;
		dwPart = emtSetting.dwPart;
		fTailLength = emtSetting.fTailLength;
		fMiddleTime = emtSetting.fMiddleTime;
		dwUVAnimFps = emtSetting.dwUVAnimFps;
		nTextureId = emtSetting.nTextureId;
		nPriorityPlane = emtSetting.nPriorityPlane;
		for( int i = 0; i < 3; ++i )
		{
			for( int j = 0; j < 3; ++j )
			{
				nSegmentColor[i][j] = emtSetting.nSegmentColor[i][j];
			}
			nAlpha[i] = emtSetting.nAlpha[i];
			fParticleScaling[i] = emtSetting.fParticleScaling[i];
			dwLifeSpanHeadUVAnim[i] = emtSetting.dwLifeSpanHeadUVAnim[i];
			dwDecayHeadUVAnim[i] = emtSetting.dwDecayHeadUVAnim[i];
			dwLifeSpanTailUVAnim[i] = emtSetting.dwLifeSpanTailUVAnim[i];
			dwDecayTailUVAnim[i] = emtSetting.dwDecayTailUVAnim[i];
		}

		vPlaneNormal = emtSetting.vPlaneNormal;
		vPlaneXAxis = emtSetting.vPlaneXAxis;
		vPlaneYAxis = emtSetting.vPlaneYAxis;

		fLifeSpanMax = emtSetting.fLifeSpanMax;
		fScaleRateMin = emtSetting.fScaleRateMin;
		fScaleRateMax = emtSetting.fScaleRateMax;
		bContraryColor = emtSetting.bContraryColor;

		bAngleChangeByCone = false;
		bTailLengthChange = false;
		for( int i = 0; i < 3; ++i )
		{
			fTailLengthChange[i] = 0.0f;
		}
		return *this;
	}

	bool  bAngleChangeByCone;       // 粒子是否会随发射方向的不同而旋转
	bool  bTailLengthChange;        // 粒子尾的长度是否会变化
	float fTailLengthChange[3];     // 粒子尾的长度变化值
};

std::string GetOpenOrSaveFileNameEx(bool openFile, const char *szFilter);
int FloatCmp( float a, float b);