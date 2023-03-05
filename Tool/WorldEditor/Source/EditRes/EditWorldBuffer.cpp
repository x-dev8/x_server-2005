/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	WorldBuffer.cpp
* Create: 	10/06/2006
* Desc:		地图数据缓冲
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#include "stdafx.h"
#include "MeTerrain/WorldPrecompiled.hpp"
#include "MeTerrain/SwRender.h"
#include <deque>
#include "Me3d/engine/RendererDx.h"
#include "Map/WorldReadStreamEdit.h"
#include "ui/Custom/ReachableMapGenerate.h"
#include "MeTerrain/Lighting/LightMapTexture.h"
using namespace std;



////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
CEditWorldBuffer::CEditWorldBuffer( CWorld* world )
:CWorldBuffer(world)
{
}

CEditWorldBuffer::~CEditWorldBuffer()
{
}

bool CEditWorldBuffer::Create()
{
	Assert( NULL == m_readStream );
	m_readStream	= new CWorldReadStreamEdit( this );

	m_globalResMgr = new CNdlGlobalResMgr();

	return true;
}

void CEditWorldBuffer::UpdateLight( CNdlLightRes* lightRes )
{
	m_isLightChange = true;
	m_lightRes		= lightRes;
	Assert( NULL != lightRes );
}

void CEditWorldBuffer::UpdateFog( CNdlFogRes* fogRes )
{
	m_isFogChange	= true;
	m_fogRes		= fogRes;
}






bool CEditWorldBuffer::SetActiveTile( CWorldTile* val ,int nRoleX ,int nRoleY )
{
	if(m_activeTile != NULL)
	{
		((CResEditMgr*)m_activeTile->GetCResMgr())->DetachAllNpc();
	}

	SwGlobal::GetRender()->UnlockModelRes();
	// 注销光照图
	if( GetActiveTile() )
	{
		CWorldTile* pOldTile = GetActiveTile();
		for( int i=0; i<pOldTile->GetLightMaps().size(); ++i )
		{
			GetEngine()->GetTextureManager()->UnRegisterTexture( pOldTile->GetLightMaps()[i]->GetTextureId() );
		}
	}

	m_activeTile = NULL;
	CWorldTile* pTile = LoadTileRes(val,nRoleX,nRoleY);
	_SetActiveTile(pTile);
	CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();

	view->SetActivePos(pTile->GetOrigin()[0],pTile->GetOrigin()[1]);
	((CResEditMgr*)pTile->GetCResMgr())->CreateNpcLine();
	CReachableMapGenerate::Instance()->ClearSlopeCheck();
	return pTile != NULL;
}

void CEditWorldBuffer::_SetActiveTile( CWorldTile* val )
{
	if (m_activeTile != val)
	{
		// 		CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
		if (NULL != m_activeTile)
		{
			m_activeTile->DetachHelperModel();
			// 			toolManager->GetActiveTool()->SetActive(false);
		}
		CWorldEditDoc::GetActiveMapDoc()->Reset();
		m_activeTile = val;
		if (NULL != m_activeTile)
		{
			m_activeTile->AttachHelperModel();
			// 			toolManager->GetActiveTool()->SetActive(true);
		}
	}
}



void CEditWorldBuffer::ClearTileModify( CWorldTile * tile, uInt32 tileId )
{
	if( tile->IsModify() ) 
	{
		CWorldEditDoc::GetActiveMapDoc()->WriteTile( tile, false );
		tile->SetModify(false);
	}
	CWorldEditDoc::GetActiveMapDoc()->ClearTileModify( tileId );
}

CWorldTile* CEditWorldBuffer::PushTileRes(sInt32 nMapId,  const char* pPathName )
{
	if (pPathName == NULL)
	{
		return NULL;
	}
	CWorldTile* pNewTile = NULL;
	if (-1 == nMapId)
	{
		if (!(pNewTile = GetTileFromPath(pPathName)))
		{
			for (int i = 0 ; i < 10000; ++i)
			{
				if (!GetTile(i))
				{
					nMapId = i;
					break;
				}
			}
		}
	}
	else
	{
		pNewTile = GetTile(nMapId);
	}
	if (!pNewTile)
	{
		pNewTile = new CWorldTile(pPathName);
		m_tileMapHash.insert(std::map<sInt32,CWorldTile*>::value_type(nMapId,pNewTile));
		pNewTile->Create(this,new CResEditMgr);
		pNewTile->SetMapId(nMapId);
	}
	return pNewTile;
}