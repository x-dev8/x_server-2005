/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	NdlResMgr.h
* Create: 	10/06/2006
* Desc:		全局资源管理
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef _NDL_NDLEDITRESMGR_H__
#define _NDL_NDLEDITRESMGR_H__
#include "MeTerrain/NdlResMgr.h"

////////////////////////////////////////////////////////////////////////////////
class MexAnimCtrl;
class CResEditMgr;
class TObjectEditInfo : public TObjectInfo
{
public:
	TObjectEditInfo();
	~TObjectEditInfo();
	virtual				bool			LoadFromFile(const char* pszFile);
	virtual void		CreateFloorAndCollision();

	virtual			TObjectInfo*	Clone();

	//added by zilong.
	TObjectInfo *CloneAll(void);

	BspTree*		GetSupperFloor() {return m_pSupperFloor;};
	void		CreateSupperFloorBsp( float fMinLeafSize );
	bool		m_bLockHeight;
	void		SyncOffset2WorldPos( );
	void			ApplyTransform();
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
////////////////////////////////////////////////////////////////////////////////
class CResEditMgr/*	: public NiRefObject*/ : public CResMgr
{
	friend						CWorldReadStream;
	friend						CWorldWriteStream;
	friend						CNdlWorldEditor;
	friend						CWorldBuffer;
public:	
								CResEditMgr();
	virtual						~CResEditMgr();
		
	virtual void						Unload();

	virtual CSoundPointRes*				CreateSoundPointRes();
	virtual CTransportRes*				CreateTransportRes();
	virtual CTargetRes*					CreateTargetRes();

	virtual	sInt32						PushStaticModel( sInt32 refModelId, const flt32* pos, const flt32* offset, const flt32* rotate, const flt32* scale,
														 TWTDObjLightmapInfo* plmInfo = NULL, TWTDObjInstance* pInss = NULL, TWTDObjLightmapColorData* pColorData = NULL);
	virtual sInt32						PushChunkShape( CWorldChunk* worldChunk );
	virtual bool						UpdateChunkMask( CWorldChunk* worldChunk );
	virtual bool						RefreshChunkMask( CWorldChunk* worldChunk );
	
	virtual bool						IsNeedClone(CNdlStaticModelRes* pRes,sInt32 nsubIndex);

	std::vector< CMonsterQuadRes* >& GetMonsterQuadList(){return m_monsterQuadList;}
	CMonsterQuadRes*			MonsterQuad( sInt32 id );
	void						CleanMonsterQuad();
	CMonsterQuadRes*			PushMonsterQuad(float top,float left,float right,float bottom);		
	sInt32						GetMonsterQuadCount() const;
	void						DeleteMonsterQuad(sInt32 id );
	void						AttachAllMonsterQuad();
	void						DetachAllMonsterQuad();
	virtual	void						FillShapeData( CNdlShapeRes* res , CWorldChunk* worldChunk);

	CMonsterQuadRes *CreateMonsterQuadRes(float top,float left,float right,float bottom);
	//只是简单的将对象插入或弹出，并不会真的生成或删除对象
	bool PushMonsterQuad(CMonsterQuadRes *pRes);
	bool PopMonsterQuad(CMonsterQuadRes *pRes);

	bool	CreateMeshRes(CWorldTile* pTile, int lineRes, float fHeightPercent);
	void 	SetMeshRes(sInt32 nTileId, sInt32 nLength, float fHeightPercent);

	CNPCRouteRes*				PushFlyRoute(const char* pName);		
	void						AttachAllFlyRoute();
	void						DetachAllFlyRoute();

	CNPCRouteRes* CreateRoute(const char *pName_, bool bFlyRoute_);
	//只是简单的将对象插入或弹出，并不会真的生成或删除对象
	bool PushRoute(CNPCRouteRes *_pRoute_);
	bool PopRoute(CNPCRouteRes *pRoute_);

	std::vector< CNPCRouteRes* >& GetNPCRouteList(){return m_NPCRouteList;}
	CNPCRouteRes*				NPCRoute( sInt32 id );
	void						CleanNPCRoute();
	CNPCRouteRes*				PushNPCRoute(const char* pName);		
	sInt32						GetNPCRouteCount() const;
	void						DeleteNPCRoute(sInt32 id );
	void						AttachAllNPCRoute();
	void						DetachAllNPCRoute();

	void						RefreshSpecialChunkLayer(CWorldChunk* worldChunk,sInt32 nLevel);
	bool						ReplaceChunkTexture( CWorldChunk* worldChunk, sInt32 layerId, sInt32 textureId );
	bool						ReplaceChunkTexture( CWorldChunk* worldChunk, sInt32 layerId, const char* textureName);
	bool						ReplaceTexture( sInt32 texId, const char* textureName ,CWorldChunk** ppchunk );
	void						ReplaceChunkTextrueId( CWorldChunk* worldChunk, sInt32 layerId , sInt32 newId);
	bool						SetSpecialLayerAlign(CWorldChunk* worldChunk,bool flag,sInt32 nLevel);
	bool						RefreshAllChunkTexture(  );

	bool						CreateLineRes( CWorldChunk* worldChunk, CNdlLineRes* lineRes );
	bool						RefreshLineRes( CWorldChunk* worldChunk, sInt32 lineId );
	CNdlLineRes*				Line( sInt32 id );

	bool						RefreshObjHeight( CWorldChunk* worldChunk );
	bool						RefreshChunkShapeHeight( sInt32 shapeId, const TChunkVertex* outHeight, const TChunkVertex* inHeight, CWorldChunk* worldChunk, uInt32 hole=0x0 );
	bool						RefreshChunkShapeVertexColor( sInt32 shapeId, sInt32 VertId,COLORREF niColor, bool isOutVertex );
	bool						RefreshChunkShapeNormal( sInt32 shapeId, const TChunkVertex* outHeight, const TChunkVertex* inHeight, uInt32 hole=0x0 );
	bool						RefreshNormal();

	bool						PopStaticModel( sInt32 staticId );
	bool						CleanUnusedResource(bool isGameWtd = false);
	void						CleanUnusedDoodad();
	void						CleanUnusedModel(bool isGameWtd = false);
	void						CleanUnusedAlphaAndShadow();
	void						CleanUnusedTexture();
	void						PreClean();
	void						DeleteStaticModel( sInt32 delId );
	void						DeleteEnvRes( sInt32 delId );
	void						DeleteZoneRes( sInt32 delId );
	void						DeleteLightRes( sInt32 delId );
	void						DeleteFogRes( sInt32 delId );
	bool						FindStaticModelInUsed( sInt32 resId);

	bool						ModifyStaticModel( sInt32 modelId, const flt32* offset, const flt32* rotate, const flt32* scale );
	bool						CleanTileModelId( sInt32 delId );

	void						CloneModelInfo(CResMgr* pSrcMgr,sInt32* chunk);

	sInt32						PushDoodad( const char* modelName );
	bool						PopDoodad( sInt32 DoodadId );
	bool						CleanTileDoodadId( sInt32 delId );

	bool						UpdateChunkDoodad( CWorldChunk* worldChunk );
	void						DeleteTransport(sInt32 id );
	bool						ReplaceModelId(CWorldRes* nnewRes,CWorldRes* noldRes);
	bool						ReplaceDoodadId(CWorldRes* nnewRes,CWorldRes* noldRes);
	bool						ReplaceTextureId(sInt32 newId,sInt32 oldId);

	void						AttachAllSoundPoint();
	void						DetachAllSoundPoint();

public:
	enum	{
		eShadow = 0,
		eRoad,
		ePathFindMap
	};
	CNdlAlphaRes*				GetRoad( sInt32 id );
	sInt32						GetRoadCount() const;
	sInt32						PushRoad( const uInt8* shadowMap );
	bool						IsRoadShow() const { return m_ShadowShowType == eRoad; }
	int							GetShadowShowType() { return m_ShadowShowType; }
	void						SetShadowShowType(int val);
	void						FillShadowByPathFindMap(uInt8 * alphaData,CWorldChunk* pChunk);
protected:
	std::vector< CBaseRes* >	m_roadList;
	int							m_ShadowShowType;
public:
    std::vector< CNpcRes* >&    GetNpcList(){return m_vecSet;}	
    sInt32						GetNpcCount() const;
    void						AttachAllNpc();
    void						DetachAllNpc();
    CNpcRes*                    GetNpcRes(int nValue);
	CNpcRes* GetNpcResByNpcId(int id_);
    CNpcRes*                    AddNpc(float x,float y,float z);
    CNpcRes*                    AddNpc(NpcInfo::Npc *pNpc);
    void                        DelNpc(int nValue,int mapId);

	bool InitNpc(float x,float y,float z, NpcInfo::Npc &_npc);

    int                         GetNpcListCount(){return m_vecSet.size();}
	CMeshLineRes* GetMesh();
    void  CreateNpcLine();
    std::vector<CNdlNpcLineRes*>& GetNpcLineList(){return m_vecLineSet;}
    void                        ClearNpcLine(); //清楚NpcLine
protected:
    std::vector<CNpcRes*>        m_vecSet;
    std::vector<CNdlNpcLineRes*> m_vecLineSet;
	std::vector< CMonsterQuadRes* >	m_monsterQuadList;
// 	std::vector< CFlyRouteRes* >	m_FlyRouteList;
	std::vector< CNPCRouteRes* >	m_NPCRouteList;
	std::vector< CWorldRes*	>	m_shapeLineList;	// 编辑器使用
	CMeshLineRes	m_Mesh;	// 距离框 
	void							_DeleteIdFromList(std::vector< CWorldRes* >& list, sInt32 delId );

};

#endif	// _NDL_NDLEDITRESMGR_H__
