/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolManager.cpp
* Date: 	02/08/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "ToolCamera.h"
#include "ToolVertex.h"
#include "ToolLayer.h"
#include "ToolDoodad.h"
#include "ToolObject.h"
#include "ToolLiquid.h"
#include "ToolEnv.h"
#include "ToolLight.h"
#include "ToolManager.h"
#include "ToolGameCamera.h"
#include "ToolTransport.h"
#include "ToolFlyRoute.h"
#include "ToolMonsterQuad.h"
#include "ToolZone.h"
#include "ToolClickToAdd.h"
#include "ToolNpc.h"
#include "ToolFreeBlock.h"
#include "ToolStaticLight.h"

CToolManager::CToolManager()
{
	m_parentWnd		= NULL;
	m_activeTool	= TOOL_CAMERA;
}

CToolManager::~CToolManager()
{
	m_parentWnd		= NULL;
	m_activeTool	= TOOL_CAMERA;
	for( size_t i = 0; i < m_toolList.size(); i++ )	{
		SAFE_DELETE( m_toolList[i] );
	}
	m_toolList.clear();

}

bool CToolManager::Create( CWnd* parentWnd )
{
	Assert( NULL != parentWnd );
// 	HWND hWnd = GetDesktopWindow();
	m_parentWnd = parentWnd;

	// NOTE: 顺序有关
	// Camera
	CToolCamera* toolCamera = new CToolCamera();
	toolCamera->Create( this );
	m_toolList.push_back( toolCamera );
	Assert( (m_toolList.size()-1) == TOOL_CAMERA );
	
	CToolGameCamera* toolGameCamera = new CToolGameCamera();
	toolGameCamera->Create( this );
	m_toolList.push_back( toolGameCamera );
	Assert( (m_toolList.size()-1) == TOOL_GAMECAMERA );
	// vertextSelect.
	CToolVertex* toolVertex = new CToolVertex();
	toolVertex->Create( this );
	m_toolList.push_back( toolVertex );
	Assert( (m_toolList.size()-1) == TOOL_VERTEX );
	
	CToolLayer* toolLayer	= new CToolLayer();
	toolLayer->Create( this );
	m_toolList.push_back( toolLayer );
	Assert( (m_toolList.size()-1) == TOOL_LAYER );

	CToolDoodad* toolDoodad = new CToolDoodad();
	toolDoodad->Create( this );
	m_toolList.push_back( toolDoodad );
	Assert( (m_toolList.size()-1) == TOOL_DOODAD );

	CToolObject* toolObject = new CToolObject();
	toolObject->Create( this );
	m_toolList.push_back( toolObject );
	Assert( (m_toolList.size()-1) == TOOL_OBJECT );

	CToolLiquid* toolLiquid = new CToolLiquid();
	toolLiquid->Create( this );
	m_toolList.push_back( toolLiquid );
	Assert( (m_toolList.size()-1) == TOOL_LIQUID );
	
	CToolTransport* toolTransport = new CToolTransport();
	toolTransport->Create( this );
	m_toolList.push_back( toolTransport );
	Assert( (m_toolList.size()-1) == TOOL_TRANSPORT );

	CToolRoute* toolFlyRoute = new CToolRoute();
	toolFlyRoute->Create( this );
	m_toolList.push_back( toolFlyRoute );
	Assert( (m_toolList.size()-1) == TOOL_FLYROUTE );

	CToolMonsterQuad* toolMonster = new CToolMonsterQuad();
	toolMonster->Create( this );
	m_toolList.push_back( toolMonster );
	Assert( (m_toolList.size()-1) == TOOL_MONSTERQUAD );

	CToolEnv* toolEnv = new CToolEnv();
	toolEnv->Create( this );
	m_toolList.push_back( toolEnv );
	Assert( (m_toolList.size()-1) == TOOL_ENV );

	CToolZone* toolZone = new CToolZone();
	toolZone->Create( this );
	m_toolList.push_back( toolZone );
	Assert( (m_toolList.size()-1) == TOOL_ZONE );

	CToolLight* toolLight = new CToolLight();
	toolLight->Create( this );
	m_toolList.push_back( toolLight );
	Assert( (m_toolList.size()-1) == TOOL_LIGHT );

	CToolClick2Add* toolClick2Add = new CToolClick2Add();
	toolClick2Add->Create( this );
	m_toolList.push_back( toolClick2Add );
	Assert( (m_toolList.size()-1) == TOOL_CLICK2ADD );

	CToolNpc* toolNpc = new CToolNpc;
	toolNpc->Create(this);
	m_toolList.push_back(toolNpc);
	Assert((m_toolList.size() -1) == TOOL_NPC);

	// 阻挡编辑工具
	ToolFreeBlock* toolFreeBlock = new ToolFreeBlock;
	toolFreeBlock->Create(this);
	m_toolList.push_back(toolFreeBlock);
	Assert((m_toolList.size() -1) == TOOL_FREEBLOCK);

	CToolStaticLight* toolStaticLight = new CToolStaticLight;
	toolStaticLight->Create(this);
	m_toolList.push_back(toolStaticLight);
	Assert((m_toolList.size() -1) == TOOL_STATICLIGHT);

	return true;
}

CBaseTool* CToolManager::GetActiveTool()
{
	if( TOOL_NONE == m_activeTool )
		return NULL;

	return m_toolList[m_activeTool];
}

void CToolManager::SetActiveTool( ToolID id )
{
	if( (id<=TOOL_NONE) || (id>=TOOL_FLIGHT) )
		return;

	if (m_activeTool != id)
	{
		m_toolList[m_activeTool]->SetActive( false );
		m_activeTool = id;
		m_toolList[m_activeTool]->SetActive( true );
	}
}

void CToolManager::SetActiveToolParam( uInt32 lParam, uInt32 wParam )
{
	if( (m_activeTool<=TOOL_NONE) || (m_activeTool>=TOOL_FLIGHT) )
		return;

	m_toolList[m_activeTool]->SetParam( lParam, wParam );
}

CBaseTool* CToolManager::GetTool( ToolID id )
{
	Assert( (m_activeTool>TOOL_NONE) && (m_activeTool<TOOL_FLIGHT) );

	return m_toolList[id];
}

UINT CToolManager::BeginTimer( UINT timerID, UINT uElapse )
{
	return m_parentWnd->SetTimer( timerID, uElapse, 0 );
}

void CToolManager::EndTimer( UINT timerID )
{
	m_parentWnd->KillTimer( timerID );
}

void CToolManager::Render()
{
	m_toolList[m_activeTool]->Render();
}

void CToolManager::Reset()
{
	SetActiveTool(TOOL_CAMERA);
}

