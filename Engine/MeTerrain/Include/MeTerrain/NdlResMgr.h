/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	NdlResMgr.h
* Create: 	10/06/2006
* Desc:		全局资源管理
* Author:	Yuan Ding
*
* Modify:	TObjectInfo增加光照图数据
* Modify by:Qiu Li, 01/19/2010
*******************************************************************************/
#ifndef _NDL_NDLRESMGR_H__
#define _NDL_NDLRESMGR_H__
#include <vector>
#include <Me3d/Model/MexAnimCtrl.h>
#include <MeTerrain/Lighting/StaticMeshInstance.h>

////////////////////////////////////////////////////////////////////////////////
class MexAnimCtrl;
class CResMgr;
class StaticMeshInstance;
class TObjectInfo : public MeCommonAllocObj<TObjectInfo>
{
public:
	enum emModelFade
	{
		ModelFirstRender,	// 第一次渲染
		ModelNormal,
		ModelFadeIn,
		ModelFadeOut
	};
	enum ELightMapScale
	{
		//LMS_1024                =0,
		LMS_512                 =0,
		LMS_256                 =1,
		LMS_128                 =2,
		LMS_64                  =3,
		LMS_32                  =4,
		LMS_16                  =5,
		LMS_8                   =6,
		LMS_4                   =7,
		LMS_No_Lightmap         =8,
		LMS_MAX                 =9,
	};

					TObjectInfo();
	virtual			~TObjectInfo();

	void UnLoadModel();
	void			IncreaseRef(CResMgr* pResMgr);
	void			DecreaseRef(CResMgr* pResMgr);

	void			CleanDspTree();
	virtual				bool			LoadFromFile(const char* pszFile);
	void			Update( float fTime ){ if (model->IsAni())	{model->UpdateByParam(fTime); 	}	}
	void			Render( float fAlpha, bool bUseLightmap = true, int* pVertexCount=NULL, int* pFaceCount=NULL, int* pSubmodelCount=NULL );//{ model->Render(fAlpha); }

	/*
	 * 2012.6.26 wangshuai
	 * 渲染包围盒和Radius
	 */
	void RenderAABBAndRadius();

	virtual			TObjectInfo*	Clone();
	bool			UpdateRenderCounter(uInt32 curRenderCounter);	// 更新renderCounter，并返回是否需要渲染
	float			GetModelScale();

	sInt32			id;
	MexAnimCtrl*	model;
	uInt32			renderCounter;		// 判断当前帧是否已渲染，避免重复渲染
	bool			m_isLoad;
	bool			m_bIsWujian;		// 非房屋的小物件模型

	bool			m_bIsOpaque;		// false: 模型与相机碰撞后会半透明, 值为true的时候不透明
	bool			m_bIs2_5dColi;		// 是否需要在2.5d模式下参与阻挡碰撞

	BspTree*		GetModelFloor() {return m_pModelFloor;};
	BspTree*		GetCollision() {return m_pCollision;};
	BspTree*		GetCamereCollision() {return m_pCameraCollision;};
	BspTree::SIntersect* GetNearestIntersect( Vector& vPos, Vector& vDir, BOOL bNormal=0, BOOL bIsCamera=FALSE );
	BspTree*		GetAlphaBox() const { return m_pAlphaBox; }

	BspTree*		m_pModelFloor;
	BspTree*		m_pCollision;
	BspTree*		m_pCameraCollision;
	BspTree*		m_pSupperFloor;
	BspTree*		m_pAlphaBox;
	virtual void		CreateFloorAndCollision();

	void		CreateCameraBsp( float fMinLeafSize );
	void		CreateCollisionBsp( float fMinLeafSize );
	void		CreateFloorBsp( float fMinLeafSize );
	void		CreateAlphaBoxBsp( float fMinLeafSize );
	flt32		pos[3];
	flt32		offset[3];
	flt32		rotate[3];
	flt32		scale[3];

	int32		m_nCountRef;
	float			m_fAlpha;
	float			m_fDestAlpha;	// 目标alpha值，淡入淡出用。与fademode等无关。
	bool			m_bToDestBlend; // 是否渐变

	emModelFade		m_FadeMode;		// 淡入还是淡出
	float			m_FadeParam;	// 每毫秒淡入或淡出因子
	DWORD			m_LastFadeTime;	// 上一帧时间
	bool			m_bWasInCullFar;	// 是否在模型渲染距离内
	bool			m_bIsCulled;	// 是否被可视剪裁

	void			SetInCullFar(bool bNeedRender)	{ m_bWasInCullFar = bNeedRender; }
	bool			WasInCullFar()	{ return m_bWasInCullFar;	}
	int				GetFadeMode() { return m_FadeMode; }
	void			SetAlpha(float f, bool bBlend = false, float df = 1.f ) { m_fAlpha = f; m_bToDestBlend = bBlend; m_fDestAlpha = df; }
	float			GetAlpha()	{ return m_fAlpha; }
	void			SetDestAlpha( float f ){ m_fDestAlpha = f; }
	float			GetDestAlpha(){ return m_fDestAlpha; }
	void			SetIsCulled(bool bIsCull) { m_bIsCulled = bIsCull; }
	bool			IsCulled() { return m_bIsCulled; }
	bool			IsWuJian() { return m_bIsWujian; }

	void			SetFadeMode(int fadeMode, DWORD currTime, int alphaDuration)
	{
		m_FadeMode = (emModelFade)fadeMode;
		m_FadeParam = 1.f / alphaDuration;
		m_LastFadeTime = currTime;
	}

	void			UpdateAlpha(DWORD currTime)
	{
		if( m_FadeMode == ModelFadeIn )
		{
			m_fAlpha += (currTime - m_LastFadeTime) * m_FadeParam;
			if( m_fAlpha >= 1.f )
			{
				m_FadeMode = ModelNormal;
				m_fAlpha = 1.f;
			}
		}
		else if( m_FadeMode == ModelFadeOut )
		{
			m_fAlpha -= (currTime - m_LastFadeTime) * m_FadeParam;
			if( m_fAlpha <= 0.f )
			{
				m_FadeMode = ModelNormal;
				m_fAlpha = 0.f;
				m_bWasInCullFar = false;
			}
		}
	}

	// Lightmap相关
	StaticMeshInstance* GetStaticMeshInstance(int index)
	{
		if( index < 0 || index >= m_vecStaticMeshInstances.size() )
			return NULL;
		return m_vecStaticMeshInstances[index]; 
	}
	StaticMeshInstance* GetStaticMeshInstanceByChunkId(int chunk);
	int				GetStaticMeshIntanceCount() { return m_vecStaticMeshInstances.size(); }

	void			CreateStaticMeshInstance(Mex2GeoChunk* pChunk, int chunk);
	void			CreateStaticMeshInstance(unsigned short ChunkIndex, INT vertexCount, BYTE lightmapIndex, float* UVOffset, float* UVScale);
	
	void			DestroyStaticMeshInstances();
	void			DestroyStaticMeshInstance(int index);

	bool			CastShadow() { return m_bCastShadow; }
	void			SetCastShadow( bool bCast ) { m_bCastShadow = bCast; }

	bool			LightChanged() { return m_bLightChanged; }
	void			SetLightChanged(bool bChanged) { m_bLightChanged = bChanged; }

	unsigned char	GetLightMapScale() { return m_ucLightMapScale; }
	void			SetLightMapScale(ELightMapScale scale) { m_ucLightMapScale = scale; }

	StaticMeshInstanceContainer& GetStaticMeshInstanceContainer(){ return m_vecStaticMeshInstances; }
	LayerDataContainer& GetLayerDataContainer(){ return m_LayerDatas; }

	void			ClearColorData() { m_mapLightColorData.clear(); }
	void			PushColorData( sInt16 nGeoChunkId, sInt32 colorindex )
					{ m_mapLightColorData.insert(std::map<sInt16, sInt32>::value_type(nGeoChunkId, colorindex)); }
	const std::map<sInt16, sInt32>& GetColorData() { return m_mapLightColorData; }

protected:
	StaticMeshInstanceContainer m_vecStaticMeshInstances;	// 静态模型实例，保存灯光图信息
	LayerDataContainer m_LayerDatas;		// 辅助存储layerdata
	bool			m_bCastShadow;			// 是否投影到其他模型上，默认为true
	bool			m_bLightChanged;		// 模型变换则需要重新计算灯光图，【Editor用】
	BYTE			m_ucLightMapScale;		// 灯光图分辨率枚举，ELightMapScale，默认LMS_128
	std::map<sInt16, sInt32> m_mapLightColorData;// 已生成灯光图颜色数据，保存指向全局ColorData的索引
};

////////////////////////////////////////////////////////////////////////////////
class CWorldRes;
class CNdlLineRes;
class CNdlAlphaRes;
class CNdlMaskRes;
class CNdlShapeRes;
class CNdlTextureRes;
class CNdlLightFogRes;
class CWorldChunk;
class CDoodadRes;
class CNdlEditWorldPicker;
class CWorldReadStream;
class CWorldWriteStream;
class CWorldTile;
class CWorldBuffer;
struct TWTDObjLightmapInfo;
struct TWTDObjInstance;
////////////////////////////////////////////////////////////////////////////////
class CResMgr
{
	friend						CWorldReadStream;
	friend						CWorldWriteStream;
	friend						CNdlWorldEditor;
	friend						CWorldBuffer;
public:	
								CResMgr();
	virtual						~CResMgr();
		
	bool						Create( CWorldBuffer* worldBuffer, CWorldTile* worldTile );
	virtual void						Unload();

	void						SafeDeleteObjInfo( TObjectInfo*  objInfo );
	static void							CreateStaticStream();

	static void						FillStaticIndexBuffer();
	void						ReleaseStaticIndexBuffer();
	static WORD*							GetStaticIndexStream(int index)
	{
		return m_IndexStream[index];
	}

	static LPDIRECT3DINDEXBUFFER9 GetIndexBuffer(int index)
	{
		return m_pIB[index];
	}

	virtual CSoundPointRes*				CreateSoundPointRes();
	virtual CTransportRes*				CreateTransportRes();
	virtual CTargetRes*					CreateTargetRes();

	virtual bool						IsNeedClone(CNdlStaticModelRes* pRes,sInt32 nsubIndex);

	WORD* GetLiquidIndexStream() const { return m_liquidIndexStream; }

	void						Update( flt32 totalTime, flt32 deltaTime );

	bool						ReCreate();

	void						OnDeviceLost();
	void						OnDeviceReset( bool bBeforeReset);


	virtual sInt32				PushStaticModel( sInt32 refModelId, const flt32* pos, const flt32* offset, const flt32* rotate, const flt32* scale,
												 TWTDObjLightmapInfo* plmInfo = NULL, TWTDObjInstance* pInss = NULL, TWTDObjLightmapColorData* pColorData = NULL);

	void						GenerateObjInfo( TObjectInfo* objInfo, bool bKeepOldData = false );
	sInt32						PushRefStaticModel( const char* modelName, bool onlyPhysics = false);
	TObjectInfo*				GetStaticModel( sInt32 id );


	void						IncDoodadRef( sInt32 id );
	void						DecDoodadRef( sInt32 id );
	sInt32						PushRefDoodad( const char* fileName );
	CWorldRes*					GetDoodad( sInt32 id );
	CDoodadRes*					GetDoodadRes( sInt32 id );
	int							GetDoodadCount();

	sInt32						PushMask( CWorldChunk* worldChunk );
	sInt32						PushAlpha( const uInt8* alpha );
	sInt32						PushShadow( const uInt8* shadowMap );
	virtual sInt32						PushChunkShape( CWorldChunk* worldChunk );
	virtual	void						FillShapeData( CNdlShapeRes* res , CWorldChunk* worldChunk);
	void						FillShapeData( FTerrainVertexSpecial* terrainVertex , CWorldChunk* worldChunk);
	void						FillLOD2Vertex(CNdlShapeRes* res,CWorldChunk* worldChunk);
	void						FillLOD2Vertex(TChunkLOD2Vertex* res,CWorldChunk* worldChunk);

	void						FillAllVertexBuffer();
	void						DestoryAllVertexBuffer();
	void						CalChunkSpecialUV( CWorldChunk* worldChunk, FTerrainVertexSpecial terrainVertex[] ,int special = -1);
	void						CalSpecialTEXCOORD( CWorldChunk* worldChunk,int index, FTerrainVertexSpecial terrainVertex[]);

	CTransportResBase*		PushTransport(float top,float left,float right,float bottom,sInt32 nIndex);		// 压入传送点
	CTransportResBase*		PushTarget(float posX,float posY,float dir, bool bRelive);									// 压入目标点

	bool						RefreshLiquidHeight(CWorldChunk* worldChunk, flt32 height , COLORREF niColor,float alphaCoaf);
	bool						PushChunkLiquid(CWorldChunk* worldChunk, sInt32 shapeId, sInt32 liquidId, flt32 height , COLORREF niColor,float alphaCoaf);
	bool						IsChunkLiquidExist(CWorldChunk* worldChunk);
	bool						RemoveChunkLiquid(CWorldChunk* worldChunk);
	
	sInt32						FindRefStaticModel( const char* modelName );
	CWorldRes*						FindTexture( const char* fileName );
	sInt32						FindRefDoodad( const char* fileName );
	
	sInt32						Texture( sInt32 id );
	CNdlTextureRes*				GetTexture( sInt32 id );
	ITexture*					Mask( sInt32 id );
	CNdlShapeRes*				Shape( sInt32 id );

	CTransportResBase*		Transport( sInt32 id );
	CTargetRes*				GetTarget( sInt32 TargetId );
	CTargetRes*				GetRelive(sInt32 TargetId);
	void						CleanTransport();

	void						FreeAlphaAndShadow();
	sInt32						GetTextureCount() const;
	sInt32						GetAlphaCount() const;
	sInt32						GetShadowCount() const;
	sInt32						GetShapeCount() const;
	sInt32						GetTransportCount() const;
	
	bool						TextureName( char* name, sInt32 id );
	
	CNdlAlphaRes*				GetAlpha( sInt32 id );
	CNdlAlphaRes*				GetShadow( sInt32 id );
	virtual bool				RefreshChunkMask( CWorldChunk* worldChunk );
	bool						ReleaseChunkMask( CWorldChunk* worldChunk );
	TTextureInfo*				GetAlignChunk(CWorldChunk* worldChunk,sInt32& chunkX,sInt32& chunkY,int index);
	virtual bool						UpdateChunkMask( CWorldChunk* worldChunk );
	bool						ReloadTexture( sInt32 nTexture );
	sInt32						PushTexture( const char* fileName );

	void						AddSpecialUV( sInt32 shapeId, CWorldChunk* worldChunk,int index );
	void						SetLOD0Material( CWorldChunk* worldChunk, sInt32 shapeId );
	//void						ApplyTransform(NiAVObject* pObj, const flt32* pos, const flt32* offset, const flt32* rotate, const flt32* scale);
	void						ApplyTransform(MexAnimCtrl* pObj, const flt32* pos, const flt32* offset, const flt32* rotate, const flt32* scale);

	std::vector< CSoundPointRes* >& GetSoundPointList(){return m_SoundPointList;}
	CSoundPointRes*			SoundPoint( sInt32 id );
	void						CleanSoundPoint();
	CSoundPointRes*				PushSoundPoint(const char* pName);		
	sInt32						GetSoundPointCount() const;
	void						DeleteSoundPoint(sInt32 id );

public:	
	std::vector< CWorldRes* >&	GetStaticModelRefList()  { return m_staticModelRefList; }
	std::vector< TObjectInfo*>& GetStaticModelList() { return m_staticModelList; }
	//NiFogProperty*				GetFogProperty(){ return m_fogProp; };

	CNdlEnvRes*						GetEnvRes( sInt32 zoneId );
	CNdlZoneRes*						GetZoneRes( sInt32 zoneId );
	CNdlLightRes*					GetLightRes( sInt32 lightId );
	CNdlFogRes*						GetFogRes( sInt32 fogId );
	sInt32							CreateEnv( const char* name, sInt32 lightId, sInt32 fogId );
	sInt32							FindEnv( const char* name, sInt32 lightId, sInt32 fogId );
	sInt32							CreateZone( const char* name, const char* musicPath, const RECT* pRect );
	sInt32							FindZone( const char* name, const char* musicPath );
	std::vector< CWorldRes* >&		GetFogList() { return m_fogList; }
	std::vector< CWorldRes* >&		GetLightList() { return m_lightList; }
	std::vector< CWorldRes* >&		GetEnvResList() { return m_envResList; }
	std::vector< CWorldRes* >&		GetZoneResList() { return m_zoneResList; }
	enum {
		LOD0 = 0,
		LOD1,
		LOD2,
		LOD0to1,
		LOD1to2,
		LODLEVEL
	};
	static	int							m_LODFaceCount[LODLEVEL];
// 	static int							m_baseShadowId;
	bool						SetLODLevel(CWorldChunk* worldChunk,sInt32 nlevel);
	//internal use only for edit 
	bool						SetLODLevelPrivate(CWorldChunk* worldChunk,sInt32 nlevel);
	bool						RefreshNeighborLODLevel(CWorldChunk* worldChunk,int oldLevel,int newLevel );

	struct SInOutPos
	{
		float x;
		float y;
		short inOutIndex;
		bool bIn;
	};

	SInOutPos&						GetIndexToInOut(int index) const 
	{return m_IndexToInOut[index];}

protected:
	bool						IsHigherLODNeighbor(CWorldChunk* worldChunk,sInt32 nlevel);
	bool						FindTextureReference(sInt32 textureId);
	void						UpdateLiquidTexture();
	bool						ReFillShape( CWorldChunk* chunk );
	bool						CreateWireframeShape();
	bool						CreateBoundBoxShape();

	bool						_RefillMaskTexture( ITexture* texture, uAlphaBit* data0, uAlphaBit* data1, uAlphaBit* data2, uAlphaBit* shadowData );
	void						_FillShapData( CNdlShapeRes* res , CWorldChunk* worldChunk );

protected:
	CWorldBuffer*				m_worldBuffer;
	CWorldTile*					m_bindTile;

	std::vector< CWorldRes* >	m_staticModelRefList;
	std::vector< TObjectInfo* >	m_staticModelList;
	std::vector<CWorldRes*>		m_doodadRefList;
	std::vector< CWorldRes* >	m_textureList;
	std::vector< CBaseRes* >	m_alphaList;
	std::vector< CBaseRes* >	m_shadowList;
	std::vector< CBaseRes* >	m_maskList;
	std::vector<CWorldRes* >	m_shapeList;
	std::vector< CWorldRes* >	m_envResList;
	std::vector< CWorldRes* >	m_zoneResList;
	std::vector< CWorldRes* >	m_lightList;
	std::vector< CWorldRes* >	m_fogList;
	static void							DestoryStaticStream();

	static WORD*						m_IndexStream[LODLEVEL];	
	static WORD						m_LOD2IndexConvert[CHUNK_LOD1T02_VERTEX_NUMBER];	
	static WORD*						m_liquidIndexStream;
	static SInOutPos				m_IndexToInOut[CHUNK_VERTEX_NUMBER];
	std::vector< CTransportResBase* >	m_transportList;

	std::vector< CSoundPointRes* >	m_SoundPointList;

	// public property
	flt32						m_deltaTime;


	void					CalcBBox(CNdlShapeRes* res, CWorldChunk* worldChunk);

	static LPDIRECT3DINDEXBUFFER9 m_pIB[LODLEVEL];
};

#endif	// _NDL_NDLRESMGR_H__
