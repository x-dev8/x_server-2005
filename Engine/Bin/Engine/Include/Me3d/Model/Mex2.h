#ifndef _mex2_h
#define _mex2_h

#include "Me3d/Me3d.h"
#include "Me3d/Model/MexSkinMesh.h"
#include "Me3d/Engine/Engine.h"
#include "Me3d/Engine/Renderable.h"
#include "Mutex.h"
#include "Me3d/Model/MexConfig.h"
#include "FuncPerformanceLog.h"
#include "Me3d/Model/MexGeoChunk.h"
#include "Me3d/Model/Mex2EffectRenderable.h"
#include "Me3d/Model/MexSimpleSpline.h"
#include "Me3d/Model/MexRotationalSpline.h"
#define MEX2_SET_FLAG( a, b ) ( a |= b )
#define MEX2_HAS_FLAG( a, b ) ( ( a & b ) != 0 )
//struct SK_VERTEX
//{
//	Vector	p;			// 12byte
//	Vector n;			// 12byte
//	DWORD		color;		// 4 byte
//	float		u, v;		// 8 byte
//	float		u1,v1;		// 8 byte
//	//BYTE		pad[20];
//};

enum ECKFMex2RenderFlag
{
	MEX2_SPECULARENABLE	=	1<<12,
	MEX2_SORTBYFARZ		=	1<<13,
	MEX2_ALPHABLEND		=	1<<14,
	MEX2_ALPHATEST			=	1<<15,
	MEX2_TWOSIDED			=	1<<16,
	MEX2_BLEND				=	1<<17,
	MEX2_ADD				=	1<<18,
	MEX2_MODULATE			=	1<<19,
	MEX2_MODULATE2X		=	1<<20,
	MEX2_MODULATE4X		=	1<<21,
	MEX2_ALPHAKEY			=	1<<22,
	MEX2_UNSHADED			=	1<<23,
	MEX2_UNFOGGED			=	1<<24,
	MEX2_ZWRITEENABLE		=	1<<25,
};

enum EMex2DefaultTexture
{
	eLightTrack,
	eRigidGlow,
	eMaxMex2DefaultTexture
};

enum 
{
	eNormalTexture		=	1<<0,
	eReplaceableTexture =	1<<1,
};


class Vector;
class Quaternion;
union Mex2Pointer;
class Mex2;
class Mex2GeoChunk;
class Mex2Geometry;
class Mex2Material;
struct Mex2ActionKeyframe
{
	Vector vTrans;
	Quaternion qRot;
};

struct Mex2Action : public MeCommonAllocObj<Mex2Action>
{
	int		nStartFrame;
	int		nEndFrame;
	int		nNumFrame;
	
	BYTE*	pbyMatrixBuffer;
	BYTE*	pbyKeyFrameBuffer;
	BOOL*	pbVisiBuffer;
	
	DWORD	dwLastUseTime;	// 上次使用时间
	int		nRef;
private:
	BOOL	bLoaded;
public:
	Mex2Action();
	BOOL	IsLoaded(){ return bLoaded; }
	void	Loaded( BOOL b ){ bLoaded = b; }
	void	Unload();
	void	Use();
};

struct Mex2ActionList
{
	Mex2ActionList();
	BOOL	AddAction( int nStartFrame, int nEndFrame );
	float*	GetMatrices( int nBoneId, int nFrameId );
	BOOL	IsVisible( int nBoneId, int nFrameId );
	Mex2ActionKeyframe* GetKeyframe( int nBoneId, int nFrameId );
	Mex2Action* GetAction( int nFrameId );
	int		FindRecentlyMostUnusedActionInLoaded();
	void	Destroy();

	std::vector<Mex2Action*> actions;
	std::vector<int> LoadedActions;
	int		nActionCache;
	//int		nNumBone;
	//int		nNumMexFrame;
	Mex2*	pMex;
};

// mex2版本
struct Mex2Version : public MeCommonAllocObj<Mex2Version>
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
	Mex2Version():dwVersion(111){}
	BOOL	Read( Mex2Pointer inP, int nSize );
	DWORD	dwVersion;
	
};
// mex2 face

// mex2 uv坐标
//   added 2003.12.09
struct Mex2ColorKey : public MeCommonAllocObj<Mex2ColorKey>
{
	float	dr, dg, db;	// diffuse color
	float	ar, ag, ab;	// ambiant color
	float	sr, sg, sb;	// specular color
	float	alpha;		// alpha
	float	shinstr;		// shiness
	float	selfillum;	// self illumination
	float	uoffset, voffset;
	DWORD	dwBlendMode;
	float	reserved[1];	// total 16 floats
};

struct Mex2MtlAnim : public MeCommonAllocObj<Mex2MtlAnim>
{
	int bTiling;		// 是否有tile;
	int nUTile, nVTile;	// u,v块数
	int nStartFrame;	// 开始帧编号
	float fPlaybackRate;	// 每多少帧次更新一次

	int nKeyCount;
	Mex2ColorKey* pKeys;
	DWORD nLastTime;	// 最近一次刷新时间
	int nLastFrameId;	// 上次刷新帧数id

	bool bHasAlphaChange;	// 是否有Alpha变化

	Mex2MtlAnim()
	{
		bTiling = true;
		nUTile = 1;
		nVTile = 1;
		nStartFrame = 0;
		fPlaybackRate = 1.0f;
		nKeyCount = 0;
		pKeys = NULL;
		nLastTime = 0;
		nLastFrameId = 0;

		bHasAlphaChange = false;
	};
	~Mex2MtlAnim();
	BOOL	Read( Mex2Pointer inP, int nSize );
};

struct Mex2MtlAnims : public MeCommonAllocObj<Mex2MtlAnims>
{
	~Mex2MtlAnims();
	// if has color track,
	// color track count must equal layer count
	std::vector<Mex2MtlAnim*> vectorColorTrack;
	BOOL	Read( Mex2Pointer inP, int nSize );
};

// mex2 贴图
class Mex2Texture:public IMexTexture
{
public:
	Mex2Texture(){
		szName[0] = 0;
	}
	void SetName( const char* pszName );
	const char* GetName(){ return szName; }
protected:
	char	szName[MAX_PATH];
};

// mex2 层
class Mex2Layer:public IMexLayer
{
	friend Mex2;
	friend Mex2GeoChunk;
	friend Mex2Material;
public:
	Mex2Layer():
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
	BOOL IsSameLayer( IMexLayer* pLayer );
	
protected:
	int		m_nBlendMode;
	DWORD	m_dwFlag;
	int		m_nTextureID;
	float	m_fAlpha;
};

// mex2骨骼组
class Mex2BoneGroup:public IMexBoneGroup,public MeCommonAllocObj<Mex2BoneGroup>
{
	friend Mex2GeoChunk;
public:
	Mex2BoneGroup():nBoneCount(0),pnBoneIds(NULL),pfBondWeight(NULL){}
	~Mex2BoneGroup();
	BOOL	Read( Mex2Pointer inP, int nSize, DWORD version );

	// 虚函数
	int		GetBoneCount(){ return nBoneCount; }
	int		GetBoneID( int i ){ return pnBoneIds[i]; }
	BOOL	SetBoneID( int i, int nBoneID );
	int*	GetBoneIDs(){ return pnBoneIds; }
	float	GetBoneWeight( int i ){if( pfBondWeight ) return pfBondWeight[i]; else return 1.0f;}

protected:
	int		nBoneCount;
	int*	pnBoneIds;
	// 增加骨骼权重
	float*	pfBondWeight;
};

// mex2骨骼组集合
class Mex2BoneGroups:public IMexBoneGroups, public MeCommonAllocObj<Mex2BoneGroups>
{
	friend Mex2;
public:
	BOOL	Read( Mex2Pointer inP, int nSize, DWORD version );
	
	// 虚函数
	int GetBoneGroupCount(){ return vectorBoneGroup.size(); }
	IMexBoneGroup* GetBoneGroup( int i );
protected:
	std::vector<Mex2BoneGroup*> vectorBoneGroup;
	Mex2BoneGroups(){}
	~Mex2BoneGroups();
};

// // mex2 关键帧
// struct Mex2Keyframe
// {
// 	int		nTime;
// 	int		nType;		// trans, rot, scale, color
// 	int		bVisible;
// 	float*	pfParam;
// };
// 
// // mex2 帧轨迹
// struct Mex2Track
// {
// 	int		nKeyframeCount;
// 	Mex2Keyframe* pKeyframes;
// };
// //   added 2003.11.17
// struct Mex2BoneInfl
// {
// 	int nBoneCount;
// 	int* pnBoneIds;
// 	float* pfWeights;
// };
// // 骨骼影响
// struct Mex2BoneInfls
// {
// 	std::vector<Mex2BoneInfl> vectorInfl;
// };
//   addded 2003.12.12
//#include "IOXml/IOXMLObject.h"
// mex2 几何体片
// mex2 几何体
struct StaticMeshInstanceInfo
{
	StaticMeshInstanceInfo(int vcount, bool castShadow) :
		nVertexCount(vcount)
		,bCastShadow(castShadow)
		{}

	int nVertexCount;
	bool bCastShadow;
};

class Mex2Geometry:public IMexGeometry, public MeCommonAllocObj<Mex2Geometry>
{
	friend Mex2;
public:
	Mex2Geometry():	pSrcMex(NULL){}
	~Mex2Geometry();
	BOOL	Read( Mex2Pointer inP, int nSize );
	//void	Render( Mex2* pMex );
	//Mex2GeoChunk* FindChunkByName( const char* pszName );
	// 虚接口
	int	GetChunkCount();
	IRenderable* GetChunk( int nChunkId );
	IRenderable* FindChunkByName( const char* pszName );
	void createBuffers(bool dynamic);

	// 谨慎使用，目前MexViewer里替换辅助模型用到，[QL 2011/04/06]
	std::vector<Mex2GeoChunk*>& GetChunks() { return vectorChunk; }	
	std::vector<CMexChunkData*>& GetChunkDatas() { return vectorChunkData; }

	void restoreBuffers(){
		for (int i = 0; i < vectorChunk.size(); ++i)
		{
			vectorChunk[i]->restoreBuffers();
		}
	}
	void DestoryBuffers()
	{
		for (int i = 0; i < vectorChunk.size(); ++i)
		{
			vectorChunk[i]->destroyBuffers();
		}
	}
	void OnDeviceLost()
	{
		for (int i = 0; i < vectorChunk.size(); ++i)
		{
			vectorChunk[i]->OnDeviceLost();
		}
	}
protected:
	std::vector<Mex2GeoChunk*> vectorChunk;
	std::vector<CMexChunkData*> vectorChunkData;
	Mex2*	pSrcMex;
};

// mex2 动画序列信息
class Mex2Sequence:public IMexSequence, public MeCommonAllocObj<Mex2Sequence>
{
	friend Mex2;
public:
	Mex2Sequence(){
		szName[0] = 0;
	}
	const char* GetName(){ return szName; }
	int GetStartFrameID(){ return nStartFrameId; }
	int GetEndFrameID(){ return nEndFrameId; }
	BOOL IsLoopping(){ return bLoopping; }
	
protected:
	char	szName[MEX2_MAX_NAME];
	int		nFps;
	int		nStartFrameId;
	int		nEndFrameId;
	int		bLoopping;
};

// mex2 动画序列集合
// class Mex2Sequences:public IMexSequences
// {
// 	friend Mex2;
// public:
// 	int GetSequenceCount(){ return vectorSequence.size(); }
// 	IMexSequence* GetSequence( int i ){ return &vectorSequence[i]; }
// protected:
// 	std::vector<Mex2Sequence> vectorSequence;
// };

// mex2 贴图集合
class Mex2Textures:public IMexTextures , public MeCommonAllocObj<Mex2Textures>
{
public:
	Mex2Textures(){};//:nTextureCount(0),pTextures(NULL){}
	BOOL	Read( Mex2Pointer inP, int nSize );
	//////////////////////////////////////////////////////////////////////////
	// 虚函数
	int GetTextureCount(){ return vectorTexture.size(); }
	IMexTexture* GetTexture( int i );
	int GetRenderTextureCount(){ return vectorRenderTextureId.size(); }
	int GetRenderTextureID( int i );
	void AddRenderTextureID( int nID ){ vectorRenderTextureId.push_back(nID); }
	void ClearRenderTextureIDs(){ vectorRenderTextureId.clear(); }
	IMexTexture* AddTexture();
protected:
	//int		nTextureCount;
	//Mex2Texture* pTextures;
	std::vector<Mex2Texture> vectorTexture;
	std::vector<int> vectorRenderTextureId;

};

// mex2 材质
class Mex2Material:public IMexMaterial , public MeCommonAllocObj<Mex2Material>
{
	friend Mex2;
	friend Mex2GeoChunk;
public:
	Mex2Material()
		/*:		
		nLayerCount(0),
		pLayers(NULL)*/{}

	int GetLayerCount(){ return vectorLayer.size(); }//{ return nLayerCount; }
	//IMexLayer* GetLayer( int nLayer ){ return &pLayers[nLayer]; }
	IMexLayer* GetLayer( int nLayer ){ return &vectorLayer[nLayer]; }
	IMexLayer* AddLayer();
	BOOL IsSameMtl( IMexMaterial* pMtl , DWORD dwFlag );
	BOOL Prepare( IRenderer* pRenderer, IReplaceableTextureProj* pTextureProj, DWORD* pdwFlag, int* pnTextureID );

	BOOL	Read( Mex2Pointer inP, int nSize );

	//   added 2004.07.07
	BOOL	HasColorTrack(){ return colorTracks.vectorColorTrack.size() > 0; }
	BOOL	HasColorKey()
	{ 
		if( HasColorTrack() &&
			colorTracks.vectorColorTrack[0]->nKeyCount )
			return TRUE;
		return FALSE;
	}
	Mex2MtlAnims& GetColorTracks() { return colorTracks; }

protected:
	//int		nLayerCount;
	//Mex2Layer* pLayers;
	std::vector<Mex2Layer> vectorLayer;
	//   added 2003.12.09
	Mex2MtlAnims colorTracks;
};

// mex2 材质集合
class Mex2Materials:public IMexMaterials, public MeCommonAllocObj<Mex2Materials>
{
	friend Mex2;
	friend Mex2GeoChunk;
public:
	Mex2Materials(){}
	~Mex2Materials();
	BOOL	Read( Mex2Pointer inP, int nSize );

	int GetMtlCount(){ return vectorMtl.size(); }
	IMexMaterial* GetMtl( int nMtl );/*{ return &vectorMtl[nMtl]; }*/
	IMexLayer* AddLayer();
protected:
	std::vector<Mex2Material*> vectorMtl;
};

// mex2 骨骼
struct Mex2Skeleton;
class IMexSkeleton;
class KeyFrame
{
public:
	KeyFrame(): nFrameId(0), ucPosSpace(eKS_Parent), ucRotSpace(eKS_Parent) {}
	KeyFrame (int frame, const Vector& pos, const Quaternion& rot)
	{
		nFrameId = frame;
		kTrans = pos;
		kQuat = rot;
	}
	virtual ~KeyFrame() {}

	void operator=(const KeyFrame& kf)
	{
		nFrameId = kf.nFrameId;
		ucPosSpace = kf.ucPosSpace;
		ucRotSpace = kf.ucRotSpace;
		kTrans = kf.kTrans;
		kQuat = kf.kQuat;
	}

	enum EKeySpace				// 从eKS_World到eKS_LeftHand和Max biped key prop定义一致
	{
		eKS_World = 0,
		eKS_Body,
		eKS_RightHand,
		eKS_LeftHand,
		eKS_Parent
	};

	virtual void Interpolate(float t, const KeyFrame* pKey1, KeyFrame* pResult);

	unsigned short nFrameId;	// 最多65535个关键帧
	unsigned char ucPosSpace;	// EKeySpace
	unsigned char ucRotSpace;	// EKeySpace
	Vector kTrans;
	Quaternion kQuat;
};

class TcbKeyFrame: public KeyFrame
{
public:
	TcbKeyFrame(): m_iTcbIndex(0) {}
	TcbKeyFrame (int frame, const Vector& pos, const Quaternion& rot, int index):
		KeyFrame( frame, pos, rot )
	{
		m_iTcbIndex = index;
	}
	~TcbKeyFrame() {}

	void operator=(const TcbKeyFrame& kf)
	{
		nFrameId = kf.nFrameId;
		ucPosSpace = kf.ucPosSpace;
		ucRotSpace = kf.ucRotSpace;
		kTrans = kf.kTrans;
		kQuat = kf.kQuat;
		m_iTcbIndex = kf.m_iTcbIndex;
	}

	virtual void Interpolate(float t, const KeyFrame* pKey1, KeyFrame* pResult);

	void CalculatePosDVals(const Vector& ptSub1, const Vector& ptPlus1, float fPreLen, float fNextLen, IMexSkeleton* pSkeleton, std::vector<Vector>& PosDSs, int index);
	void CalculateRotDVals(const KeyFrame* pPrev, const KeyFrame* pNext, IMexSkeleton* pSkeleton);

	// TCB相关参数
	int				m_iTcbIndex;	// 从TCB表对应index读取TCB参数，省内存

	//float			m_fTension;
	//float			m_fContinuity;
	//float			m_fBias;

	// Position临时数据
	// DS and DD hold the first derivative information defined by
	// the tension, continuity, and bias parameters.
	//Vector			m_PosDS;
	Vector			m_PosDD;

	// A & B are calculated and stored for use with this interpolant
	// and the interpolant to the "right", i.e. the next interpolant 
	// specified at a non-decreasing time value.  In doing this, A & B
	// can be calculated once, rather than each time interpolation
	// is done using the two keys in question.
	Vector			m_PosA;
	Vector			m_PosB;

	//Rotation临时数据
	// Intermediate quaternion values and angles used for interpolation.
	Quaternion		m_RotA;
	Quaternion		m_RotB;
};

// Struct for store splines, allocate on demand for better memory footprint
//struct Splines
//{
//	SimpleSpline positionSpline;
//	RotationalSpline rotationSpline;
//};

struct FrameIndex
{
	FrameIndex()
		: fTime(0.f)
		, nKeyIndex(0)
	{}
	FrameIndex(float time, unsigned int keyIndex)
		: fTime(time)
		, nKeyIndex(keyIndex)
	{}
	void operator=(const FrameIndex& fi)
	{
		fTime = fi.fTime;
		nKeyIndex = fi.nKeyIndex;
	}


	/** The time position (in relation to the whole animation sequence)
	*/
	float fTime;
	/** The global keyframe index (in relation to the whole animation sequence)
	that used to convert to local keyframe index, or INVALID_KEY_INDEX which
	means global keyframe index unavailable, and then slight slow method will
	used to search local keyframe index.
	*/
	unsigned int nKeyIndex;
};

class AnimationTrack
{
public:
	AnimationTrack(): m_eKeyType(eKT_Linear) { m_vecKeyFrames.clear(); m_KeyFrameIndexMap.clear(); }
	virtual ~AnimationTrack();

	enum KeyType
	{
		eKT_Linear,
		eKT_Tcb
	};
	typedef vector<KeyFrame*> KeyFrameList;

	KeyFrameList& GetKeyFrames() { return m_vecKeyFrames; }
	void BuildInterpolationSplines(IMexSkeleton* pSkeleton);
	/** Internal method to collect keyframe times, in unique, ordered format. */
	void CollectKeyFrameTimes(std::vector<int>& keyFrameTimes);

	/** Internal method to build keyframe time index map to translate global lower
	bound index to local lower bound index. */
	void BuildKeyFrameIndexMap(const std::vector<int>& keyFrameTimes);

	// 获取FrameIndex::nKeyIndex相应的关键帧数据；对于武器绑定骨骼rh.和lh.如果前后两帧链接关系不同，则返回kf和extrakf
	float GetInterpolatedKeyFrame(const FrameIndex& frameIndex, KeyFrame& kf, KeyFrame& extrakf);

	// 获取FrameIndex::nKeyIndex相应的前后两个关键帧，返回插值数据
	float GetKeyFramesAtTime(const FrameIndex& frameIndex, KeyFrame** keyFrame1, KeyFrame** keyFrame2, KeyFrame** keyFrame3, KeyFrame** keyFrame0, int* firstKeyIndex = 0) const;

	void FillDerivedVals(IMexSkeleton* pSkeleton);

	int GetKeyType() { return m_eKeyType; }
	void SetKeyType( KeyType type ) { m_eKeyType = type; }

	// 第0帧本地空间位置和旋转
	Vector			m_kInitTrans;
	Quaternion		m_kInitQuat;

	/// Map used to translate global keyframe time lower bound index to local lower bound index
	typedef std::vector<unsigned short> KeyFrameIndexMap;
	KeyFrameIndexMap m_KeyFrameIndexMap;

protected:
	void RemoveAllKeyFrames();

	KeyFrameList	m_vecKeyFrames;	// 关键帧
	KeyType			m_eKeyType;		// 关键帧插值类型
	//mutable Splines	m_Splines;

};
class Mex2Bone:public IMexBone, public MeCommonAllocObj<Mex2Bone>
{
public:
	//IOXMLObject Interface
	//bool loadXMLSettings(XMLElement *element);
	//bool exportXMLSettings(ofstream &xmlFile  );
public:
	//char* pszName;
	char	szName[MEX2_MAX_NAME];
	int nParentId;
	int nChildCount;
	int* pnChildIds;
	int nFrameCount;			// 逐帧动画帧数
	MeMatrix* pMatrices;
	//bool* pVisible;
	BOOL* pVisible;
	float* pVisibleFloat;
	Vector* pTrans;
	Quaternion* pQuats;
	MeMatrix* pmatTransform;	// 当前的transform
	MeMatrix matFrame0Inv;
	//MeMatrix matInv;			// 当前的transform*到第0帧的逆
	int	nFrameId;
	//Mex2* pMex;
	//Mex2Skeleton* pSkeleton;
	IMexSkeleton* pSkeleton;
	int	nBoneId;
	BOOL	bHasKeyframe;
	Mex2ActionList* pActionList;
	float	fScaleAdjust;		// 骨骼缩放校正，用来实现体格变形
	AnimationTrack* m_pTrack;	// 新关键帧动画格式
	BOOL	m_bFullFrame;		// 腿部和脚部骨骼用逐帧动画

	Mex2Bone(): nParentId(-1),
					nChildCount(0),
					pnChildIds(NULL),
					nFrameCount(0),
					pMatrices(NULL),
					pVisible(NULL),
					pVisibleFloat( NULL ),
					pTrans(NULL),
					pQuats(NULL),
					nFrameId(0),
					pActionList(NULL),
					//pMex(NULL),
					pSkeleton(NULL),
					nBoneId(-1),
					bHasKeyframe(FALSE),
					fScaleAdjust(1.0f),
					m_pTrack(NULL),
					m_bFullFrame(FALSE)
	{}
	~Mex2Bone();
	BOOL	Read( Mex2Pointer inP, int nSize, DWORD dwVersion  );
	BOOL	SnapShotFromFile( FILE* fp, int nSize, DWORD dwFlag );

	inline BOOL	GetTranslationAndRotation( float fKeyTime, int nFps, Vector& v, Quaternion& q );
	BOOL	HasKeyFrame();
	//   added 2003.09.23
	void Update();
	//   added 2003.10.23
	void Update( int nFrameId );
	//   added 2005.08.26
	const char* GetName(){ return szName; }
	int	GetParentId(){ return nParentId; }
	int GetChildCount(){ return nChildCount; }
	int GetChildId( int i ){ return pnChildIds[i]; }
	int GetFrameId(){ return nFrameId; }
	int GetFrameCount(){ return nFrameCount; }
	float GetRotation(float fKeyTime, int nFps );
	float* GetMatrices( int nFrameId );//{ return (float*)&pMatrices[nFrameId]; }
	float* GetMatricesFromKeyTime( float fKeyTime, int nFps, float* parentMat = NULL );
    float* GetBlendedMatrices( float t, float fKeyTime0, float fKeyTime1, int nFps, BOOL bIsLastBlend = FALSE, Vector* pLastBlendTrans = NULL, Quaternion* pLastBlendQuats = NULL );
	float* GetTransform(){ return (float*)pmatTransform; }
	float* GetFrame0Inv(){ return (float*)&matFrame0Inv; }
	float* GetInv(){ return NULL;/*(float*)&matInv;*/ }
	BOOL HasVisibleTrack(){ return pVisible != NULL; }
	//BOOL IsVisible( int nFrameId ){ return pVisible[nFrameId]; }
	BOOL IsVisible( int nFrameId );//{ return TRUE; }
	float GetVisibleFloat( int nFrameId );
	AnimationTrack* GetTrack() { return m_pTrack; }
	/** Internal method to collect keyframe times, in unique, ordered format. */
	void CollectKeyFrameTimes(std::vector<int>& keyFrameTimes);

	/** Internal method to build keyframe time index map to translate global lower
	bound index to local lower bound index. */
	void BuildKeyFrameIndexMap(const std::vector<int>& keyFrameTimes);

	// 获取关键帧，返回0成功，>0需要转成模型坐标再插值
	float GetInterpolatedKeyFrame(const FrameIndex& frameIndex, KeyFrame& kf, KeyFrame& extrakf);
	void GetParentModelMatAtKeyFrame(float fKeyTime, const FrameIndex& frameIndex, MeMatrix& mat);

protected:
	void BuildInterpolationSplines(IMexSkeleton* pSkeleton) const;
	void CalModelSpaceKeyFrame(KeyFrame& kKeyFrame, KeyFrame& kOutKeyFrame, float fKeyTime, const FrameIndex& frameIndex, float* parentMat);
};

// mex2 骨架
struct Mex2Skeleton:public IMexSkeleton, public MeCommonAllocObj<Mex2Skeleton>
{
	std::vector<Mex2Bone*> vectorBone;
	//std::vector<IMexBone*> vectorBone;
	int nRootBoneCount;
	int* pnRootBoneIds;
	//   added 2003.10.09
	IMex* pMex;
	BOOL m_bSpecialModel;	// 逐帧动画的模型
	//IMex* pMex;
	Mex2Skeleton():
		nRootBoneCount(0),
		pnRootBoneIds(NULL),
		pMex(NULL),
		m_bSpecialModel(TRUE)
		{ m_KeyFrameTimes.clear(); m_KeyFrameSegments.clear(); m_vTcbList.clear(); }
	~Mex2Skeleton();
	int GetBoneCount(){ return vectorBone.size(); }
	IMexBone* GetBone( int i )
	{ 
		if( i < 0 || i >= vectorBone.size() )
			return NULL;
		return vectorBone[i]; 
	}
	int GetRootBoneCount(){ return nRootBoneCount; }
	int GetRootBoneId( int i ){ return pnRootBoneIds[i]; }
	void SetMex( IMex* p ){ pMex = p; }
	IMex* GetMex(){ return pMex; }
	BOOL	Read( void* p, int nSize, DWORD dwVersion );
	BOOL	SnapShotFromFile( FILE* fp, int nSize, DWORD dwFlag );

	BOOL	IsSameFormat( IMexSkeleton* pSkeleton );
	int		FindBone( const char* pszBoneName );
	//   added 2003.09.23
	int		GetBoneId( const char* pszBoneName );

	// bFindAll == TRUE，从头到尾查；FALSE，先从KeyFrameSegmentList查在哪个区段里，在从区段内查找
	// 如果bFindAll为TRUE，可以制定iBeginIndex从哪个位置开始查找
	FrameIndex	GetTimeIndex(float fTime, BOOL bFindAll = FALSE, int iBeginIndex = 0) const;
	/// Internal method to build global keyframe time list
	void	BuildKeyFrameTimeList(void) const;

	typedef std::vector<int> KeyFrameSegmentList;	// 每500帧为一子段，加快搜索速度
	typedef std::vector<int> KeyFrameTimeList;

	//void	AddKeyFrameSegment(const KeyFrameSegment& kSegment);
	KeyFrameSegmentList& GetKeyFrameSegments() const { return m_KeyFrameSegments; }
	KeyFrameTimeList& GetKeyFrameTimeList() const { return m_KeyFrameTimes; }

	// TCB表，TCB类型关键帧用，节省内存用
	struct TcbData
	{
		TcbData(): fTension(0.f), fContinuity(0.f), fBias(0.f) {}
		bool operator== (const TcbData& tcb) const
		{
			return (fabs(fTension - tcb.fTension) < 0.001f &&
				fabs(fContinuity - tcb.fContinuity) < 0.001f &&
				fabs(fBias - tcb.fBias) < 0.001f );
		}

		float	fTension;
		float	fContinuity;
		float	fBias;
	};
	typedef std::vector<TcbData> TcbList;
	TcbList m_vTcbList;

protected:

	/// Global keyframe time list used to search global keyframe index.
	mutable KeyFrameTimeList m_KeyFrameTimes;

	mutable KeyFrameSegmentList m_KeyFrameSegments;
};

//   added 2003.09.29
struct Mex2Attachment:public IMexAttachment
{
	Mex2Attachment():
		nAttachBoneID(-1)
		{pszName[0] = '\0';}
public:
	int GetAttachBoneID(){ return nAttachBoneID; }
	const char* GetName(){ return pszName; }
	float* GetInitMatrix(){ return (float*)&matInit; }
public:
	BOOL	Read( Mex2Pointer inP, int nSize );
	int		nAttachBoneID;
	char	pszName[MEX2_MAX_NAME];
	MeMatrix matInit;
	
};
struct Mex2Attachments:public IMexAttachments, public MeCommonAllocObj<Mex2Attachments>
{
public:
	int GetNumAttachment();
	IMexAttachment* GetAttachment( int nAttachment );
	IMexAttachment* FindAttachment( const char* pszName );
	// add, jiayi, [2009.4.17], attachment偏移用
	IMexAttachment*	FindAttachment( const char* pszName, int nOffset );
	void	PushBack( const Mex2Attachment& attachment ){ m_Attachments.push_back( attachment ); }

	BOOL	Read( Mex2Pointer inP, int nSize );
public:
	std::vector<Mex2Attachment> m_Attachments;
};




struct Mex2Lights;

struct Mex2Light: IMexLight, public MeCommonAllocObj<Mex2Light>
{
	friend Mex2Lights;
protected:
	struct Param
	{
		DWORD		m_dwFlag;
		char		m_szName[MEX2_MAX_NAME];	
		//char*		m_pszName;		// 80 byte
		int			m_nParentBoneID;	// 跟随骨骼运动
		Vector	m_vPivot;	// 原始位置	1 vector
		float		m_fRange;			// 照射范围
		float		m_fIntense;
		float		m_fDiffuse[3];
		float		m_fAttenuration[3];	// 衰减参数, 3 float
		int			m_nFrameCount;	// 
		float*		m_pColorTrack;	// 颜色动画 nFrameCount*3 float
		Mex2*	m_pSrcMex;
		Param():
			m_dwFlag(0),
			m_nParentBoneID(-1),
			//m_pvPivot(NULL),
			m_fRange(0.0f),
			m_fIntense(0.0f),
			m_nFrameCount(0),
			m_pColorTrack(NULL),
			m_pSrcMex(NULL){}
	};
public:

	Mex2Light():	
		m_nLightID(-1){};
	~Mex2Light();;
	// 虚函数
	void SetFlag( DWORD dwFlag ){ m_param.m_dwFlag = dwFlag; }
	DWORD GetFlag(){ return m_param.m_dwFlag; }
	void SetName( const char* pszName );
	const char* GetName(){ return m_param.m_szName; }
	void SetParentBoneID( int nParentBoneID ){ m_param.m_nParentBoneID = nParentBoneID; }
	int GetParentBoneID(){ return m_param.m_nParentBoneID; }
	void SetColor( float* pfColor );
	float* GetColor(){ return m_param.m_fDiffuse; }
	void SetRange( float fRange ){ m_param.m_fRange = fRange; }
	float GetRange(){ return m_param.m_fRange; }
	void SetIntense( float fIntense ){ m_param.m_fIntense = fIntense; }
	float GetIntense(){ return m_param.m_fIntense; }
	void SetAttenuration( float* pfAtten );
	float* GetAttenuration(){ return m_param.m_fAttenuration; }
	void SetFrameCount( int nFrameCount ){ m_param.m_nFrameCount = nFrameCount; }
	int GetFrameCount(){ return m_param.m_nFrameCount; }
	void SetColorTrack( float* pfColorTrack ){ m_param.m_pColorTrack = pfColorTrack; }
	float* GetColorTrack(){ return m_param.m_pColorTrack; }
	
	void SetLightID( int nLightID ){ m_nLightID = nLightID; }
	int GetLightID(){ return m_nLightID; }
	
	void SetPivot( float* pfPivot ){ m_param.m_vPivot = *(Vector*)pfPivot; }
	float* GetPivot(){ return (float*)&m_param.m_vPivot; }

	void SetPos( float* pfPos ){ m_vPos = *(Vector*)pfPos; }
	float* GetPos(){ return (float*)&m_vPos; }


	IMexLight* Clone();
	void Release(){ delete this; }
protected:
	Param		m_param;

	// runtime
	int			m_nLightID;		// 注册灯光id
	
	Vector m_vPos;


	BOOL	Read( Mex2Pointer inP, int nSize );
	void	Update( int nTime, float* pfMatrices, float* pfMatModel );
	//void	Update( int nTime, MeMatrix* pMatrices, MeMatrix* pmatModel = NULL );
};
struct Mex2Lights:public IMexLights
{
	friend Mex2;
public:
	int GetLightCount(){ return vectorLight.size(); }
	IMexLight* GetLight( int nLight ){ return &vectorLight[nLight]; }
protected:
	std::vector<Mex2Light> vectorLight;
	BOOL	Read( Mex2Pointer inP, int nSize );
	void	Bind( Mex2* pMex );

};
///////////////////////////////////////////////////////



//   added 2003.10.24
#define MAX_MEX2_HITPOINT 8
struct Mex2HitPoint
{
	int		nFrameId;
	char	szWavFilename[MEX2_MAX_NAME];
	BOOL	bLastHitPoint;
};

struct Mex2HitPoints
{
	Mex2HitPoints(): nHitPointCount(0){}
	int nHitPointCount;
	Mex2HitPoint hitPoints[MAX_MEX2_HITPOINT];
	BOOL	Read( Mex2Pointer inP, int nSize );
	Mex2HitPoint*	GetHitPoint( int nMin, int nMax );
	int	GetHitPoints( int nMin, int nMax, Mex2HitPoint* ppHitPoints[] );
};

struct Mex2HitPointsSet
{
	std::vector<Mex2HitPoints> vectorHitPoints;
	Mex2HitPoint*	GetHitPoint( int nMin, int nMax );
	int	GetHitPoints( int nMin, int nMax, Mex2HitPoint* ppHitPoints[] );
};

union Mex2Pointer
{
	BYTE*			byte;
	bool*			boolean;
	int*			i;
	DWORD*			dw;
	char*			c;
	void*			p;
	float*			f;
	Vector*		v3;
	Quaternion*	quat;
	Vector2*		uv;
	Mex2Face*	face;
	Mex2Texture*  tex;
	Mex2Layer*	layer;
	MeMatrix*		matrix;
	Mex2ColorKey* colorKey;

	Mex2Pointer(void* in) :p(in)
	{
	}
};



#define MAX_MEX2_ATTACHMENT	16
#define MEX2_SAFE_DELETE(a)	{ if(a){ delete a; a = NULL; } }
#define MEX2_ASSERT(a)			{ assert( a == NULL && #a "not delete" ); }
#ifndef MEX2_SAFE_DELETE_ARRAY
#define MEX2_SAFE_DELETE_ARRAY( p )	{ if(p){ delete[] (p); (p)=NULL; } }
#endif
#define MEX_TAG(x) (DWORD)(  (((DWORD)x&0x0000ff00)<<8)+(((DWORD)x&0x000000ff)<<24)+(((DWORD)x&0x00ff0000)>>8)+(((DWORD)x&0xff000000)>>24) )

class Mex2:public IMex, public MeCommonAllocObj<Mex2>//, public CSemiAutoIntLock
{

public:
	enum
	{
		eHaloTextureId,
		eMaxBone	= 64
	};
	struct MemoryBlock
	{
		BYTE*	m_pbyBuffer;
		int		m_nBufferSize;
		MemoryBlock();
		~MemoryBlock();
		BOOL	Create( BYTE* pbyBuffer, int nBufferSize );
		BOOL	Create( FILE* fp, int nBufferSize );
		Mex2Pointer GetPointer();
		int		GetBufferSize(){ return m_nBufferSize; }
		void	Destory();
	};
public:
	Mex2();
	~Mex2();

	void	Destroy();

	virtual void SetKeepOldData( bool bKeepOldData ){ m_bKeepOldData = bKeepOldData; }

	virtual void						OnDeviceLost();
	virtual void						OnDeviceReset();

	//   added 2004.06.29
	BOOL	Intersect( float* pvStart, float* pvDir, float* pvHit, DWORD dwFlag = eMex_HitAll );
// 	// jiayi added [09.03.24]
	bool	IntersectQuick( Vector* pvStart, Vector* pvDir, MexReplaceableTextureProj* replaceableTexture, D3DXMATRIX* pModelInverseMatrix );

	//   added 2004.07.16
	BOOL	IsBoneVisible( int nFrameId, int nBoneId );

	// added, jiayi, [2010/7/29]
	float	GetBoneVisibleFloat( int nFrameId, int nBoneId );

	//   added 2005.08.23
	int		GetVertexCount();

	int		GetFaceCount();

	BOOL	HasMtl();
// 	void	SetFrameId( int nFrameId ){ m_nFrameId = nFrameId; }
// 	int		GetFrameId(){ return m_nFrameId; }

	//int		GetGeomChunkCount();
	//IRenderable* GetGeomChunk( int nId );
	void	Release();

	//////////////////////////////////////////////////////////////////////////
	DWORD	GetVersion();
	BOOL	SaveToFile( const char* pszFilename, DWORD dwFlag );
	BOOL	LoadFromFile( const char* pszFilename, DWORD dwFlag, bool bKeepCloneMemory = true );
	BOOL	LoadFromMemory( BYTE* pbyBuffer, int nBufferSize );
	void	DeleteMemory() {MEX2_SAFE_DELETE_ARRAY(m_pbyMemory); m_nMemorySize = 0;}

	virtual BOOL CreateParticleEmitters();
	virtual void DestroyParticleEmitters();

	IMexSequence* GetSequence(){ return m_pSequence; }
	IMexSkeleton* GetSkeleton(){ return m_skeleton; }
	//IMexSkeleton* GetHelpers(){ return m_pHelpers; }
	IMexMaterials* GetMtls(){ return m_mtls; }
	IMexGeometry* GetGeometry(){ return m_geometry; }
// 	IMexSequences* GetSequences(){ return m_sequences; }
	IMexBoneGroups* GetBoneGroups(){ return m_boneGroups; }
	IMexTextures* GetTextures(){ return m_textures; }
	//IMexLights* GetLights(){ return m_lights; }
	IMexRibbonEmitters* GetRibbonEmitters(){ return m_ribbonEmitters; }
	IMexParticleEmitters* GetParticleEmitters(){ return m_particleEmitters; }
	IMexAttachments* GetAttachments(){ return m_attachments; }
	const char* GetFilename(){ return m_szFilename; }
	IMex*	Clone( DWORD dwFlag );

// 	void	SetMexCfg( void* pMexCfg );

	//////////////////////////////////////////////////////////////////////////
// 	BOOL SetSkeleton( IMexSkeleton* pSkeleton );
// 	BOOL BindSkeleton( IMexSkeleton* pSkeleton );

// 	//////////////////////////////////////////////////////////////////////////
// 	void UseAbstractPath( BOOL bUse );
// 	//////////////////////////////////////////////////////////////////////////

	
	//Mex2Attachment* GetAttachments(){ return m_attachment; }
	//Mex2Lights* GetLights(){ return m_lights; }
	//const char* GetFileName(){ return m_szFilename; }

	//   added 2005.09.27
// 	MexSkinMesh*	GetSkinMesh(){ return m_pSkinMesh; }
	//CMemoryFactory* GetMemoryFactory(){ return &m_MemoryFactory; }
// 	void	Mirror( DWORD dwFlag );
	BOOL	LoadAction( Mex2Action* action );
	Mex2ActionList*	GetActionList(){ return &m_ActionList; }
	//BOOL	IsSmartLoading(){ return m_bSmartLoading; }
// 	DWORD	GetLoadFlag(){ return m_dwLoadFlag; }
// 
	// 把另一个模型的骨骼动画数据合并到这个模型里，用于合并武器相关动画，
	BOOL	CombineAnimationFromModel(IMex* pMex, int& nFrameOffset);	
	BOOL	ReallocAnimationFrameCount(int nNewFrameCount);
	void	BuildKeyFrameTimeList(void);

public:


	Mex2Sequence*			m_pSequence;
	MemoryBlock				m_SequencenMB;
	void					InitializeDefaultSequece();
	
	//static BOOL			m_bUseAbstractPath;
	Box* GetLocalBBox(){ return &m_LocalBBox; }
	Vector* GetMin(){ return &m_vMin; }
	Vector* GetMax(){ return &m_vMax; }
protected:

	bool m_bKeepOldData;// added, [8/11/2010 zhangjiayi]

	
// 	int		m_nFrameId;

	Mex2Version*		m_version;
	MemoryBlock				m_VersionMB;
	Mex2Textures*		m_textures;
	MemoryBlock				m_TexturesMB;
	Mex2Materials*		m_mtls;
	MemoryBlock				m_MtlsMB;
	Mex2Geometry*		m_geometry;
	MemoryBlock				m_GeometryMB;
	
	IMexSkeleton*			m_skeleton;
	MemoryBlock				m_SkeletonMB;
	//Mex2Skeleton*		m_pHelpers;
	
// 	Mex2Sequences*		m_sequences;
// 	MemoryBlock				m_SequencesMB;
	Mex2BoneGroups*	m_boneGroups;
	MemoryBlock				m_BoneGroupsMB;
	//   added 2003.09.23
	//Mex2Attachment*	m_attachment;
	Mex2RibbonEmitters* m_ribbonEmitters;
	MemoryBlock				m_RibbonEmitterMB;//这个内存不要Destory,为了在clone的时候共用数据
	//Mex2Billboards*	m_billboards;
	//   added 2003.10.24
	//Mex2HitPointsSet*	m_hitPointsSet;
	//   added 2003.12.16
	Mex2ParticleEmitters* m_particleEmitters;
	MemoryBlock				m_ParticleEmittersMB;
	//   added 2004.08.06
	//Mex2Lights*		m_lights;
	//
	Mex2Attachments*	m_attachments;
	MemoryBlock				m_AttachmentsMB;

	//   added 2003.12.22
	char				m_szFilename[MAX_PATH];

	// 保存从文件读入的内存数据，在Clone里使用
	BYTE*				m_pbyMemory;
	int					m_nMemorySize;
	//   added 2005.09.27
	// 加入了vertex shader 对骨骼动画的支持
	// 同时使用了vertex buffer和index buffer
// 	MexSkinMesh*		m_pSkinMesh;
	//CMemoryFactory		m_MemoryFactory;
	DWORD				m_dwSkeletonOffsetInFile;
	DWORD				m_dwSkeletonChunkSize;
	Mex2ActionList m_ActionList;
	//BOOL				m_bSmartLoading;
	DWORD				m_dwLoadFlag;

	/* 武器动画合并前先统计所有武器动画帧数，然后预分配所有动画
	（包括通用动画+武器动画）需要的数据空间，保存在m_nReallocBoneFrameCount里*/
	int					m_nReallocBoneFrameCount;
	Box		m_LocalBBox;
	void	BuildLocalBBox();
	Vector m_vMin ;
	Vector m_vMax ;
};

inline BOOL Mex2Bone::GetTranslationAndRotation( float fKeyTime, 
                                                     int nFps, 
                                                     Vector& v, 
                                                     Quaternion& q )
{
    guardfunc;

    //Mex2* pMex = (Mex2*)pSkeleton->GetMex();
    //if( !pTrans )
    if( !HasKeyFrame() )
    {
        //assert( FALSE );
        return FALSE;
    }
    if( nFps <= 0 )
        nFps = 1;
    //if( nFps < 0 )
    //	return ;

    guard( FrameOutRange );
    float fInterval = 1000.0f/nFps;
    int nStartFrame = (int)(fKeyTime/fInterval);
    if( nStartFrame < 0 /*||
                        nStartFrame >= nFrameCount*/ )
    {
        assert( false );
        return FALSE;
    }
    if( nStartFrame == nFrameCount )
        nStartFrame = nFrameCount-1;


    //D3DXQuaternionToAxisAngle()

    int nEndFrame = nStartFrame+1;
    if( nEndFrame >= nFrameCount )
        nEndFrame = 0;

    float t = (fKeyTime-nStartFrame*fInterval)/fInterval;
    if( t < 0 /*||
              t > 1.0f*/ )
    {
        return FALSE;
    }
    if( t > 1.0f )
        t = 1.0f;

    Vector vStart(0,0,0);
    Vector vEnd(0,0,0);
    Quaternion qStart(0,0,0,0);
    Quaternion qEnd(0,0,0,0);
    //if( pMex->IsSmartLoading() )
    if( pActionList )
    {
        //Mex2ActionList* pActionList = ((Mex2*)pSkeleton->GetMex())->GetActionList();
        Mex2ActionKeyframe* pKeyStart = pActionList->GetKeyframe( nBoneId, nStartFrame );
        Mex2ActionKeyframe* pKeyEnd = pActionList->GetKeyframe( nBoneId, nEndFrame );

        if( pKeyStart && pKeyEnd )
        {
            vStart = pKeyStart->vTrans;
            vEnd = pKeyEnd->vTrans;

            qStart = pKeyStart->qRot;
            qEnd = pKeyEnd->qRot;
        }
    }
    else
    {
        if( nStartFrame >= nFrameCount )
            nStartFrame = 0;
        if( nEndFrame >= nFrameCount )
            nEndFrame = 0;

		vStart = pTrans[nStartFrame];
		qStart = pQuats[nStartFrame];
		vEnd = pTrans[nEndFrame];
		qEnd = pQuats[nEndFrame];
    }
    v = vStart+t*(vEnd-vStart);
// 	q = Quaternion::SlerpSimpleRenormal(t,qStart,qEnd);
 	q = qStart;
     q.blend( t, qEnd );
    unguard;
    return TRUE;
    unguard;
}

#endif