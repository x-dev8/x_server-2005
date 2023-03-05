/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	NdlWorldPicker.cpp
* Date: 	03/01/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "NdlEditWorldPicker.h"
#include "MeTerrain/World.h"
#include "MeTerrain/WorldBuffer.h"
#include "MeTerrain/WorldTile.h"
#include "MeTerrain/WorldChunk.h"
#include "MeTerrain/NdlResMgr.h"

////////////////////////////////////////////////////////////////////////////////
#define PICK_CHUNK_NUM			( 16 )
	
////////////////////////////////////////////////////////////////////////////////


CNdlEditWorldPicker::CNdlEditWorldPicker( CWorld* world ) :CNdlWorldPickerBase(world)
{

}

CNdlEditWorldPicker::~CNdlEditWorldPicker()
{

}

void CNdlEditWorldPicker::CollideObjForEditer( sInt32 pickType, bool bPickResult, Vector& rayPt, Vector& rayDir, TPickResult& pickResult )
{
	if (emPT_Transport & pickType)
	{
		bPickResult |= CollideTransport(m_worldBuffer->GetResMgr(), rayPt, rayDir, pickResult);
	}
	if ((emPT_FlyRoute & pickType) )
	{
		bPickResult |= CollideFlyRoute(m_worldBuffer->GetResMgr(), rayPt, rayDir, pickResult);
	}
	if ((emPT_NpcRoute & pickType))
	{
		bPickResult |= CollideNPCRoute(m_worldBuffer->GetResMgr(), rayPt, rayDir, pickResult);
	}
	if (emPT_MonsterQuad & pickType)
	{
		bPickResult |= CollideMonsterQuad(m_worldBuffer->GetResMgr(), rayPt, rayDir, pickResult);
	}
	if (emPT_Click2Add & pickType)
	{
		bPickResult |= CollideClick2Add(m_worldBuffer->GetResMgr(), rayPt, rayDir, pickResult);
	}
	if(emPT_NPC & pickType)
	{
		bPickResult |= CoolideNpc(m_worldBuffer->GetResMgr(),rayPt,rayDir,pickResult);
	}
}

void CNdlEditWorldPicker::CollideSupperFloor( TObjectInfo* obj, Vector& rayPt, Vector& rayDir, TPickResult &castResult, int id, bool& bPick )
{
	if (obj->m_pSupperFloor)
	{
		BspTree::SIntersect* pIntersect = obj->m_pSupperFloor->GetNearestIntersect(rayPt,rayDir);
		if (pIntersect)
		{
			castResult.pickResultInfo[castResult.pickResultCount].resultType	= emPT_FloorObj;
			castResult.pickResultInfo[castResult.pickResultCount].resultId		= id;
			castResult.pickResultInfo[castResult.pickResultCount].resultObjInfo	= obj;
			castResult.pickResultInfo[castResult.pickResultCount].point	= pIntersect->pos;
			castResult.pickResultInfo[castResult.pickResultCount].dist			= pIntersect->t;
			castResult.pickResultInfo[castResult.pickResultCount].vFacePos[0]	= pIntersect->vFacePos[0];
			castResult.pickResultInfo[castResult.pickResultCount].vFacePos[1]	= pIntersect->vFacePos[1];
			castResult.pickResultInfo[castResult.pickResultCount].vFacePos[2]	= pIntersect->vFacePos[2];
			castResult.pickResultInfo[castResult.pickResultCount].normal			= pIntersect->vNormal;
			castResult.pickResultCount++;
			bPick = true;
		}
	}
}
bool CNdlEditWorldPicker::CollideTransport( CResMgr* resMgr, const Vector& rayPt, const Vector& rayDir, TPickResult& castResult )
{
	bool bCollide = false;
	if( castResult.pickResultCount >= MAX_PICK_OBJ_COUNT )
		return false;

	CResEditMgr* resEditMgr = (CResEditMgr*)resMgr;
	for( size_t i=0; i<resEditMgr->GetTransportCount(); i++ ) {
		if( castResult.pickResultCount >= MAX_PICK_OBJ_COUNT )
			break;
		CTransportResBase* pTran = (CTransportResBase*)resEditMgr->Transport(i);
		if( pTran->GetModel()->model->GetWorldBBox()->Intersect( rayPt, rayDir ) )
		{
			castResult.pickResultInfo[castResult.pickResultCount].resultType = emPT_Transport;
			castResult.pickResultInfo[castResult.pickResultCount].resultId	 = i;
			castResult.pickResultInfo[castResult.pickResultCount].resultObjInfo = pTran->GetModel();
			castResult.pickResultCount++;
			bCollide = true;
		}
	}
	return bCollide;

}

bool CNdlEditWorldPicker::CollideMonsterQuad( CResMgr* resMgr, const Vector& rayPt, const Vector& rayDir, TPickResult& castResult )
{
	bool bCollide = false;
	if( castResult.pickResultCount >= MAX_PICK_OBJ_COUNT )
		return false;
	CResEditMgr* resEditMgr = (CResEditMgr*)resMgr;
	for( size_t i=0; i<resEditMgr->GetMonsterQuadCount(); i++ ) {
		if( castResult.pickResultCount >= MAX_PICK_OBJ_COUNT )
			break;
		CMonsterQuadRes* pQuad = resEditMgr->MonsterQuad(i);
		if( pQuad->GetModel()->model->GetWorldBBox()->Intersect( rayPt, rayDir ) )
		{
			castResult.pickResultInfo[castResult.pickResultCount].resultType = emPT_MonsterQuad;
			castResult.pickResultInfo[castResult.pickResultCount].resultId	 = i;
			castResult.pickResultInfo[castResult.pickResultCount].resultObjInfo = pQuad->GetModel();
			castResult.pickResultCount++;
			bCollide = true;
		}
	}
	return bCollide;

}

bool CNdlEditWorldPicker::CollideFlyRoute( CResMgr* resMgr, const Vector& rayPt, const Vector& rayDir, TPickResult& castResult )
{
	bool bCollide = false;
	if( castResult.pickResultCount >= MAX_PICK_OBJ_COUNT )
		return false;
	CResEditMgr* resEditMgr = (CResEditMgr*)resMgr;

	for( size_t i=0; i<resEditMgr->GetNPCRouteCount(); i++ ) {
		if( castResult.pickResultCount >= MAX_PICK_OBJ_COUNT )
			break;
		CNPCRouteRes* pQuad = resEditMgr->NPCRoute(i);
		if (!pQuad->IsFlyRoute())
		{
			continue;
		}
		std::vector<TObjectEditInfo*>& objList = pQuad->GetRoutePointModelList();
		for (size_t j = 0; j < objList.size(); ++j)
		{
			TObjectInfo* pInfo = objList[j];
			if (pInfo->model->GetWorldBBox()->Intersect( rayPt, rayDir ) )
			{
				castResult.pickResultInfo[castResult.pickResultCount].resultType = emPT_FlyRoute;
				castResult.pickResultInfo[castResult.pickResultCount].resultId	 = j;
				castResult.pickResultInfo[castResult.pickResultCount].resultObjInfo =(TObjectInfo*)pQuad;//
				castResult.pickResultCount++;
				bCollide = true;
			}
		}
	}
	return bCollide;
}

bool CNdlEditWorldPicker::CollideNPCRoute( CResMgr* resMgr, const Vector& rayPt, const Vector& rayDir, TPickResult& castResult )
{
	bool bCollide = false;
	if( castResult.pickResultCount >= MAX_PICK_OBJ_COUNT )
		return false;
	CResEditMgr* resEditMgr = (CResEditMgr*)resMgr;

	for( size_t i=0; i<resEditMgr->GetNPCRouteCount(); i++ ) {
		if( castResult.pickResultCount >= MAX_PICK_OBJ_COUNT )
			break;
		CNPCRouteRes* pQuad = resEditMgr->NPCRoute(i);
		if (pQuad->IsFlyRoute())
		{
			continue;
		}
		std::vector<TObjectEditInfo*>& objList = pQuad->GetRoutePointModelList();
		for (size_t j = 0; j < objList.size(); ++j)
		{
			TObjectInfo* pInfo = objList[j];
			if (pInfo->model->GetWorldBBox()->Intersect( rayPt, rayDir ) )
			{
				castResult.pickResultInfo[castResult.pickResultCount].resultType = emPT_NpcRoute;
				castResult.pickResultInfo[castResult.pickResultCount].resultId	 = j;
				castResult.pickResultInfo[castResult.pickResultCount].resultObjInfo =(TObjectInfo*)pQuad;//
				castResult.pickResultCount++;
				bCollide = true;
			}
		}
	}
	return bCollide;


}

bool CNdlEditWorldPicker::CollideClick2Add( CResMgr* resMgr, const Vector& rayPt, const Vector& rayDir, TPickResult& castResult )
{
	bool bCollide = false;
	if( castResult.pickResultCount >= MAX_PICK_OBJ_COUNT )
		return false;
	CResEditMgr* resEditMgr = (CResEditMgr*)resMgr;

	for( size_t i=0; i<resEditMgr->GetSoundPointCount(); i++ ) {
		if( castResult.pickResultCount >= MAX_PICK_OBJ_COUNT )
			break;
		CSoundPointEditRes* pQuad = (CSoundPointEditRes*)resEditMgr->SoundPoint(i);
		TObjectInfo* pInfo = pQuad->GetSoundPointPointModel();
		if (pInfo->model->GetWorldBBox()->Intersect( rayPt, rayDir ) )
		{
			castResult.pickResultInfo[castResult.pickResultCount].resultType = emPT_Click2Add;
			castResult.pickResultInfo[castResult.pickResultCount].resultId	 = pQuad->GetId();
			castResult.pickResultInfo[castResult.pickResultCount].resultObjInfo =(TObjectInfo*)pQuad;//
			castResult.pickResultCount++;
			bCollide = true;
			break;
		}
	}
	return bCollide;



}

bool  CNdlEditWorldPicker::CoolideNpc(CResMgr* resMgr,const Vector& rayPt,const Vector& rayDir,TPickResult& castResult)
{
	bool bCollide = false;
	if(castResult.pickResultCount >= MAX_PICK_OBJ_COUNT)
		return false;

	CResEditMgr* resEditMgr = (CResEditMgr*)resMgr;
	for (size_t i = 0; i < resEditMgr->GetNpcListCount();++i)
	{
		if(castResult.pickResultCount >= MAX_PICK_OBJ_COUNT)
			break;

		CNpcRes* pNpcRes = resEditMgr->GetNpcRes(i);
		if(pNpcRes!= NULL&&pNpcRes->GetObjectInfo()->model->GetWorldBBox()->Intersect(rayPt,rayDir))
		{
			castResult.pickResultInfo[castResult.pickResultCount].resultType = emPT_NPC;
			castResult.pickResultInfo[castResult.pickResultCount].resultId   = i;
			castResult.pickResultInfo[castResult.pickResultCount].resultObjInfo = pNpcRes->GetObjectInfo();
			++castResult.pickResultCount;
			bCollide = true;
		}
	}
	return bCollide;
}
