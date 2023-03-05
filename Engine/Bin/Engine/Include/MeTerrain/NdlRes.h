/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	NdlRes.h
* Create: 	10/06/2006
* Desc:		地表元素和模型数据的数据结构定义
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef _NDL_NDLRES_H__
#define _NDL_NDLRES_H__

#include "WorldRes.h"
#include "Me3d/Engine/Frustum.h"
#include "Me3d/Model/MexAnimCtrl.h"
////////////////////////////////////////////////////////////////////////////////
struct	TBox2D;
class	CNdlLiquidRes;
class	CResMgr;
class	CNdlGlobalResMgr;
class	CNdlEditWorldPicker;
class	CNdlWorldEditor;
class	CWorldReadStream;
class	CWorldWriteStream;
class	CToolWorldFogDlg;
class	Box;
struct	SBBox;
////////////////////////////////////////////////////////////////////////////////
class CNdlShapeRes	: public CWorldRes
{
	friend	CResMgr;
public:
	CNdlShapeRes(bool isCulled);
	struct WaterVertex 
	{
		D3DXVECTOR3 p;
		DWORD		dwColor;
		D3DXVECTOR2 uv;
	};
	~CNdlShapeRes();

// 	void CreateTerrainLODD3DData();
// 	void CreateTerrainD3DData();
	void ReleaseTerrainLODData();
	void ReleaseTerrainData();
// 	FTerrainVertexSpecial*  GetTerrainVertex();
// 	TChunkLOD2Vertex* GetLOD2Vertex() ;
	WaterVertex* CreateLiquidVertex();
	WaterVertex* GetLiquidVertex();
	void DeleteLiquidVertex();

	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DVERTEXBUFFER9 m_pVBLOD2;



	Box			m_BBox;
	SBBox				m_MMBox;

	SBBox				m_LiquidMMBox;
	bool			m_culled;
// 	FTerrainVertexSpecial*	m_terrainVertex;
// 	TChunkLOD2Vertex*		m_LOD2Vertex;//;
	WaterVertex*			m_liquidVertex;
};


////////////////////////////////////////////////////////////////////////////////
class CNdlStaticModelRes	: public CWorldRes
{
	friend	CResMgr;
	friend	CNdlGlobalResMgr;
	friend	CNdlWorldEditor;
public:
						CNdlStaticModelRes();
	virtual				~CNdlStaticModelRes();
	
	bool				LoadModel(bool bKeepOldData = false);
	MexAnimCtrl*		GetModel() { return &m_animctrl; };
	
	bool				UnloadModel();
	void				IncRefCount(bool bKeepOldData = false);
	void				DecRefCount();
	bool				IsSubExist();
	sInt32				GetChildIndex(const char* pchildName);
	void				MarkClone(sInt32 nsubIndex,bool bFlag);
	bool				IsNeedClone(sInt32 nsubIndex);
protected:
	MexAnimCtrl		m_animctrl;				// 包含模型和动画数据

	sInt32				m_cloneMark;
};

////////////////////////////////////////////////////////////////////////////////
class TObjectInfo;
class CDoodadRes : public CWorldRes
{
	friend							CNdlWorldEditor;
	friend							CNdlGlobalResMgr;
	friend class					CToolDoodadDlg;
public:
	CDoodadRes();
	virtual ~CDoodadRes();

	bool					LoadModel();
	bool					UnloadModel();

	TObjectInfo*			GetModel() const{return m_Object;}
	int						GetPartCount();
	void							IncRefCount();
	void							DecRefCount();

protected:
	TObjectInfo*			m_Object;
};


////////////////////////////////////////////////////////////////////////////////
class CNdlTextureRes	: public CWorldRes
{
	friend  CNdlLiquidRes;
	friend	CResMgr;
public:
						CNdlTextureRes();
	virtual				~CNdlTextureRes();				
	
	uInt32 GetTexture() const { return m_texture; }
	virtual	void			IncRefCount();
	virtual	void			DecRefCount();
	
protected:
	uInt32				m_texture;
};

////////////////////////////////////////////////////////////////////////////////
class CNdlAlphaRes	: public CBaseRes
{
	friend				CResMgr;
	friend				CNdlWorldEditor;
	friend				CWorldReadStream;
	friend				CWorldWriteStream;

public:
						CNdlAlphaRes();
	virtual				~CNdlAlphaRes();				
//  	uInt32				GetMaskTetureId() const { return m_maskTetureId; }

	uAlphaBit*				GetMaskData() const { return m_maskData; }
	void				UpdateToTexture();

public://static members
	static uAlphaBit m_sShadowColor;

protected:
	uAlphaBit*				m_maskData;
//  	uInt32				m_maskTetureId;
};

enum emMaskChannel {
	emMSKC_Layer0 = 0,
	emMSKC_Layer1,
	emMSKC_Layer2,
	emMSKC_Shadow,
	emMSKC_Flight
};

////////////////////////////////////////////////////////////////////////////////
class CNdlMaskRes	: public CBaseRes
{
	friend				CResMgr;
	friend				CNdlWorldEditor;
	friend				CWorldReadStream;
	friend				CWorldWriteStream;
	friend	class		CResEditMgr;

public:
	CNdlMaskRes();
	virtual				~CNdlMaskRes();

	void				ReleaseMask();
	ITexture* GetTexture() const { return m_texture; }

protected:
	ITexture*				m_texture;
};

enum emLiquidType {
	emLT_Ocean = 0,
	emLT_Lake,
	emLT_Flight
};

////////////////////////////////////////////////////////////////////////////////
class CNdlLiquidRes : public CWorldRes
{
	friend							CResMgr;
	friend							CNdlGlobalResMgr;
	friend							CNdlWorldEditor;
	friend							CWorldReadStream;
	friend							CWorldWriteStream;
public:
									CNdlLiquidRes();
									~CNdlLiquidRes();
	
	bool							Create( const char* pathName, sInt32 texCount );
	sInt32							Count() const { return m_texList.size(); };
	void							NextTexture();
	CNdlTextureRes*					GetTexture();
	CNdlTextureRes*					GetNormalTexture();
protected:
	sInt32							m_texId;
	std::vector<CNdlTextureRes*>	m_texList;
	CNdlTextureRes*					m_normalRes;
};

////////////////////////////////////////////////////////////////////////////////
// 正方形贴花
struct swDecalShapeVertex : public MeCommonAllocObj<swDecalShapeVertex>
{
	enum
	{
		eFVF = D3DFVF_XYZ|D3DFVF_DIFFUSE| D3DFVF_TEX1
	};
	D3DXVECTOR3 p;
// 		D3DXVECTOR3 n;
	DWORD		color;
	float		u, v;
};
class CNdlDecalRes	: public CWorldRes
{
public:
									CNdlDecalRes();
									~CNdlDecalRes();
	
	bool							Create( const char* textureName, flt32 radius,bool bUseVexterBuffer = false );
	bool							Create( int textureId, flt32 radius ,bool bUseVexterBuffer = false);

	void							InitIndexBuffer( const uInt16 vertCount );
	void							SetPos( const flt32* pt2,float* pAngle = NULL );
	void							SetScale(flt32 val)		{ m_Scale = val; }
	
	bool							IsFill() const	{ return m_isFill; };
	void							Render();
    void                            CombineRenderData();
	void							FastRenderDecal(LPDIRECT3DDEVICE9 m_pDevice);
	void							SetAlpha(BYTE alpha);

	void							SetDecalTexID(short val) { m_sDecalTexID = val; }
	short							GetDecalTexID() const { return m_sDecalTexID; }
	
protected:
	bool							RefillHeight();
	void							RebuildGeometry();

	void							_rebuildGeometry();
	void							_setalpha( BYTE alpha );
protected:
	bool							m_isFill;
	flt32							m_Scale;
	flt32							m_radius;
	sInt32							m_unitNum;
	sInt32							m_unitPos[2];	// global position.
	flt32							m_position[3];	// 开始 unit.

	TChunkVertex*					m_vertexOut;
	TChunkVertex*					m_vertexIn;
	int								m_vetexColor;
	flt32							m_angle;
protected:
	struct swDecalShape : public MeCommonAllocObj<CNdlDecalRes::swDecalShape>
	{
		swDecalShapeVertex* pVertex;
		unsigned short* pIdx;
		//ctor
		LPDIRECT3DVERTEXBUFFER9 m_pVB;
		LPDIRECT3DINDEXBUFFER9 m_pIB;
		swDecalShape(){
			pVertex = 0;
			pIdx = 0;
			m_pVB = 0;
			m_pIB = 0;
		}
		//~ctor
		~swDecalShape()
		{
			SAFE_DELETE_ARRAY(pVertex);
			SAFE_DELETE_ARRAY(pIdx);
			SafeRelease(m_pVB);
			SafeRelease(m_pIB);
		}
	};

	swDecalShape* m_pDecalShape;
	short m_sDecalTexID;
	bool							m_bUseVertexBuffer;
	bool							m_bUnRegisterTexture;
public:
	void SetFloorDecalEnable(bool val) { m_floorDecalEnable = val; }
	bool IsExistDecalShape(){return m_floorDecalArr.size() != 0;}
protected:
	struct swFloorDecalShape
	{
		swFloorDecalShape()
			:m_bEnble(true)
		{

		}
		swDecalShapeVertex		floorVertex[4];
		unsigned short			floorIndex[6];
		bool					m_bEnble;
	};
	bool		m_floorDecalEnable;
	void CreateFloorShape();
	bool					CreateFloorShape(D3DXVECTOR3& vPos);
	void		GetZFromXYAndPlane(D3DXVECTOR3* pos,D3DXPLANE* plane);
	bool		IsPointInShape(D3DXVECTOR3* pos,swFloorDecalShape& plane);
	std::vector<swFloorDecalShape>			m_floorDecalArr;
	bool								m_AllShapeOnFloor;

};

////////////////////////////////////////////////////////////////////////////////
class CNdlLightRes : public CWorldRes
{
	friend class					CToolEnv;
	friend class					CToolEnvDlg;
	friend class					CToolWorldLightDlg;
	friend							CNdlGlobalResMgr;
	friend							CNdlWorldEditor;
	friend							CWorldReadStream;
	friend							CWorldWriteStream;
public:
									CNdlLightRes();
									~CNdlLightRes();

	bool							Create();
	
	bool							LinearLerp( const CNdlLightRes* lfA, const CNdlLightRes* lfB, flt32 lerp );
	
	uInt32							GetLightAmbient() const { return m_lightAmbient; }
	void							SetLightAmbient(uInt32 val) { m_lightAmbient = val; }
	uInt32							GetLightDiffuse() const { return m_lightDiffuse; }
	void							SetLightDiffuse(uInt32 val) { m_lightDiffuse = val; }
	uInt32							GetLightSpecular() const { return m_lightSpecular; }
	void							SetLightSpecular(uInt32 val) { m_lightSpecular = val; }
	Vector							GetLightDir() const { return m_lightDir; }
	void							SetLightDir(Vector& val) { m_lightDir = val; }
	uInt32							GetColorSunless() const { return m_colorSunless; }
	void							SetColorSunless(uInt32 val) { m_colorSunless = val; }

	bool							LightChanged() { return m_bLightChanged; }
	void							ClearLightChanged() { m_bLightChanged = false; }

protected:
									// Light
	uInt32							m_lightAmbient;
	uInt32							m_lightDiffuse;
	uInt32							m_lightSpecular;
	uInt32							m_colorSunless;
	Vector							m_lightDir;
	bool							m_bLightChanged;	// 灯光有改变，供Editor生成光照图用
};

class CNdlFogRes : public CWorldRes
{
	friend class					CToolEnv;
	friend class					CToolEnvDlg;
	friend							CNdlGlobalResMgr;
	friend							CNdlWorldEditor;
	friend							CWorldReadStream;
	friend							CWorldWriteStream;
	friend							CToolWorldFogDlg;
public:
									CNdlFogRes();
									~CNdlFogRes();

	bool							Create();
	bool							LinearLerp( const CNdlFogRes* lfA, const CNdlFogRes* lfB, flt32 lerp );

	uInt32							GetLightColor() const { return m_lightColor; }
	void							SetLightColor(uInt32 val) { m_lightColor = val; }
	flt32							GetLightNear() const { return m_lightNear; }
	void							SetLightNear(flt32 val) { m_lightNear = val; }
	flt32							GetLightFar() const { return m_lightFar; }
	void							SetLightFar(flt32 val) { m_lightFar = val; }

protected:
	// Fog	

	uInt32							m_lightColor;
	flt32							m_lightNear;
	flt32							m_lightFar;
};

////////////////////////////////////////////////////////////////////////////////
class CNdlEnvRes : public CWorldRes
{
	friend class					CToolEnv;
	friend							CNdlGlobalResMgr;
	friend							CNdlWorldEditor;
	friend							CWorldReadStream;
	friend							CWorldWriteStream;
	friend class					CToolEnvDlg;
public:
									CNdlEnvRes();
									~CNdlEnvRes();

	sInt32							GetLightId() const { return m_lightId; }
	void							SetLightId(sInt32 val) { m_lightId = val; }
	sInt32							GetFogId() const { return m_fogId; }
	void							SetFogId(sInt32 val) { m_fogId = val; }
protected:
	sInt32							m_lightId;
	sInt32							m_fogId;
};

class CNdlZoneRes : public CWorldRes
{
public:
	CNdlZoneRes();
	~CNdlZoneRes();
	char* GetMuiscPath()  { return m_muiscPath; }
	void SetMuiscPath(const char* val);
	const RECT* GetFontRect() const;
	void SetFontRect(const RECT* pRect);

protected:
	char			m_muiscPath[MAX_PATH];
	RECT		m_fontRect;
};

class CSoundPointRes : public CWorldRes
{
public:
	CSoundPointRes();
	virtual ~CSoundPointRes();


	flt32					GetPosX() const{return m_SoundPointPoint.x;}
	flt32					GetPosY() const{return m_SoundPointPoint.y;}
	flt32					GetPosZ() const{return m_SoundPointPoint.z;}
	void					SetPosX(flt32 val) {m_SoundPointPoint.x = val;}
	void					SetPosY(flt32 val) {m_SoundPointPoint.y = val;}
	void					SetPosZ(flt32 val) {m_SoundPointPoint.z = val;}
	char*					GetMuiscPath()  { return m_muiscPath; }
	void					SetMuiscPath(const char* val);
	Vector&					GetSoundPoint(){return m_SoundPointPoint;}
	flt32					GetMinDistance() const { return m_fMinDistance; }
	void					SetMinDistance(flt32 val) { m_fMinDistance = val; }
	flt32					GetMaxDistance() const { return m_fMaxDistance; }
	void					SetMaxDistance(flt32 val) { m_fMaxDistance = val; }
protected:
	Vector 				m_SoundPointPoint;
	char				m_muiscPath[MAX_PATH];
	flt32				m_fMinDistance;
	flt32				m_fMaxDistance;
};





class CTransportResBase : public CWorldRes
{
public:
	CTransportResBase(sInt32 id = -1);
	virtual ~CTransportResBase();


	sInt32					GetNtargetID() const { return m_ntargetID; }
	void					SetNtargetID(sInt32 val) { m_ntargetID = val; }

	virtual bool					IsTransport() = 0;
	virtual flt32					GetPosX() const= 0;
	virtual flt32					GetPosY() const= 0;
	virtual void					SetPosX(flt32 val) = 0;
	virtual void					SetPosY(flt32 val) = 0;

	virtual void					ApplyTransform() ;
	virtual TObjectInfo*			GetModel();
	virtual void					AttachModel() ;
	virtual void					DetachModel() ;

protected:
	sInt32							m_ntargetID;

};


class CTransportRes : public CTransportResBase
{
public:
	CTransportRes();
	virtual ~CTransportRes(){;}

	virtual float					GetPosX() const { return (m_fLeft+ m_fRight)/2; }
	virtual void					SetPosX(float val) { flt32 delta = GetPosX() - val; m_fLeft += delta; m_fRight += delta;}
	virtual float					GetPosY() const { return (m_fTop+ m_fBottom)/2; }
	virtual void					SetPosY(float val) { flt32 delta = GetPosY() - val; m_fTop += delta; m_fBottom += delta; }

	float					GetLeft() const { return m_fLeft; }
	void					SetLeft(float val) { m_fLeft = val; }
	float					GetTop() const { return m_fTop; }
	void					SetTop(float val) { m_fTop = val; }
	float					GetRight() const { return m_fRight; }
	void					SetRight(float val) { m_fRight = val; }
	float					GetBottom() const { return m_fBottom; }
	void					SetBottom(float val) { m_fBottom = val; }
	virtual bool					IsTransport(){ return true;}

	sInt32					GetDesMapID() const { return m_dwDesMapID; }
	void					SetDesMapID(sInt32 val) { m_dwDesMapID = val; }
	sInt32					GetEntranceId() const { return m_entranceId; }
	void					SetEntranceId(sInt32 val) { m_entranceId = val; }
protected:
	float							m_fLeft;			//跳转区域是一个矩形, TopLeft的坐标		
	float							m_fTop;
	float							m_fRight;			//BottomRight的坐标
	float							m_fBottom;
	sInt32							m_dwDesMapID;		//跳转到的目标MapID
	sInt32							m_entranceId;		//
};

class CTargetRes :	public CTransportResBase
{
public:
	enum ReliveType
	{
		Relive_Default	= 0x1,		//默认
		Relive_RedName	= 0x2,		//红名重生点
		Relive_Attack	= 0x4,		//攻城重生点
		Relive_Guard	= 0x8,		//守城重生点
	};
public:
	CTargetRes();
	CTargetRes(bool bRelive);	
	virtual ~CTargetRes(){;}
	virtual float					GetPosX() const { return m_fTargetPosX; }
	virtual void					SetPosX(float val) { m_fTargetPosX = val; }
	virtual float					GetPosY() const { return m_fTargetPosY; }
	virtual void					SetPosY(float val) { m_fTargetPosY = val; }
	float					GetTargetDir() const { return m_fTargetDir; }
	void					SetTargetDir(float val) { m_fTargetDir = val; }

	sInt32					GetReliveId() {return m_nReliveId; }
	void					SetReliveId(sInt32 val) { m_nReliveId = val; }

	bool					IsRelive() { return m_bRelive; }

	sInt32					GetReliveType() { return m_nReliveType; }
	void					SetReliveType(sInt32 val) { m_nReliveType = val; }

	sInt32					GetReliveMapId() { return m_nReliveMapId; }
	void					SetReliveMapId(sInt32 val) { m_nReliveMapId = val; }

	void					ClearPFWeight()
	{
		m_pfWeightArr.clear();
	}
	void					AddPFWeight(int val)
	{
		m_pfWeightArr.push_back(val);
	}
	std::vector<int>&				GetPFWeightArr()
	{
		return m_pfWeightArr;
	}
	virtual bool					IsTransport(){ return false;}
	void							SetRelive(bool val) { m_bRelive = val; }
protected:
	float							m_fTargetPosX;			//跳转到目标Map后 玩家所在的位置
	float							m_fTargetPosY;
	float							m_fTargetDir;		//跳转到目标Map后 玩家的朝向,绕z轴的旋转
	std::vector<int>				m_pfWeightArr;

	bool							m_bRelive;			//是否是重生点
	sInt32							m_nReliveId;	
	sInt32							m_nReliveMapId;		//复活的地图ID,-1是本城

	sInt32							m_nReliveType;

};



#endif	// _NDL_NDLRES_H__
