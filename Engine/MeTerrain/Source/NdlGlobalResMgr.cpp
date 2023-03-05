/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	NdlGlobalResMgr.cpp
* Create: 	10/06/2006
* Desc:		全局地图资源
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#include "MeTerrain/stdafx.h"
#include "MeTerrain/WorldPrecompiled.hpp"
#include "MeTerrain/NdlRes.h"
#include "MeTerrain/NdlGlobalResMgr.h"
#include "MeTerrain/MapConfigXml.h"
// #include "FlyRouteXml.h"
// #include "NPCRouteXml.h"
#include "MeTerrain/SoundPointXml.h"
////////////////////////////////////////////////////////////////////////////////
namespace {
	const flt32 l_liquidStepTime = 0.08f;
}

////////////////////////////////////////////////////////////////////////////////
CNdlGlobalResMgr::CNdlGlobalResMgr()
:m_modelPtrHash(5096,NULL),m_doodadPtrHash(2048,NULL)
{
	m_totalTime		= 0.0f;
	m_liquidResList.clear();
}

CNdlGlobalResMgr::~CNdlGlobalResMgr()
{
	Destroy();
	CMapConfigXml::Release();
	CSoundPointXml::Release();
// 	CFlyRouteXml::Release();
// 	CNPCRouteXml::Release();
}

bool CNdlGlobalResMgr::Create()
{
	if( !LoadLiquidRes() ) {
		Trace( "<<<ERROR>>> failed to load liquid res! \n" );
	}
	if( !LoadLightRes() ) {
		Trace( "<<<ERROR>>> failed to load light res! \n" );
	}

	return true;
}

bool CNdlGlobalResMgr::ReCreate()
{

	return true;
}

void CNdlGlobalResMgr::Reset()
{
	m_totalTime		= 0.0f;

}

void CNdlGlobalResMgr::Destroy()
{
	Reset();
	size_t i;
	for( i = 0; i< m_liquidResList.size(); i++ ) {
		SAFE_DELETE( m_liquidResList[i] );
	}
	m_liquidResList.clear();


	DestoryModelDoodad();
}

bool CNdlGlobalResMgr::LoadLiquidRes()
{
	char liquidName[MAX_PATH];
#if _MSC_VER >= 1400
	sprintf_s( liquidName, MAX_PATH, "\\Data\\Texture\\Liquid\\ocean\\ocean_h" );
#else
	sprintf( liquidName, "\\Data\\Texture\\Liquid\\ocean\\ocean_h" );
#endif
	
	if( !LoadLiquidTexture( liquidName, 30 ) ) 
	{
		Trace( "<<<ERROR>>> can`t load liquid texture [%s] \n", liquidName );
		return false;
	}
	
	return true;
}
 
bool CNdlGlobalResMgr::LoadLiquidTexture( const char* fileName, sInt32 texCount )
{
	CNdlLiquidRes* res = MeNew CNdlLiquidRes();
	res->SetId( m_liquidResList.size() );
	char path[MAX_PATH];
#if _MSC_VER >= 1400
	strcpy_s( path, fileName );
	_strlwr_s( path );
#else
	strcpy( path, fileName );
	_strlwr( path );
#endif
	res->SetName( "Liquid" );
	res->Create( fileName, texCount );
	
	m_liquidResList.push_back( res );
	
	return true;
}

bool CNdlGlobalResMgr::LoadLightRes()
{
	return true;
}


void CNdlGlobalResMgr::Update( flt32 totalTime, flt32 deltaTime )
{
	flt32 delta = totalTime - m_totalTime;
	if( delta > l_liquidStepTime ) {
		UpdateLiquidTexture();
		m_totalTime	= totalTime;
	}
}

void CNdlGlobalResMgr::UpdateLiquidTexture()
{
	for( size_t i=0; i<m_liquidResList.size(); i++ ) {
		CNdlLiquidRes* res = (CNdlLiquidRes*)m_liquidResList[i];
		res->NextTexture();
	}
}


CNdlStaticModelRes* CNdlGlobalResMgr::FindRefStaticModel( const char* modelName )
{
	//CStringA temp(modelName);
	return m_modelPtrHash.Get(modelName);
}

void CNdlGlobalResMgr::UnloadRefModel( const char* modelName )
{
	char path[MAX_PATH*2];
#if _MSC_VER >= 1400
	strcpy_s( path, modelName );
	_strlwr_s( path );
#else
	strcpy( path, modelName );
	_strlwr( path );
#endif
	CNdlStaticModelRes* pModelRes = FindRefStaticModel( path );
 	if (NULL != pModelRes) //only is referenced by this->m_modelPtrHash;
 	{
		pModelRes->DecRefCount();
// 		if (pModelRes->RefCount() == 0)
// 		{
// 			int pos = m_modelPtrHash.Find(path);
// 			MeDelete pModelRes;
// 			m_modelPtrHash.Remove(pos);
// 		}
	}
	//do nothing when Unload
}



CNdlStaticModelRes* CNdlGlobalResMgr::LoadRefModel( const char* modelName )
{
	char path[MAX_PATH*2];
#if _MSC_VER >= 1400
	strcpy_s( path, modelName );
	_strlwr_s( path );
#else
	strcpy( path, modelName );
	_strlwr( path );
#endif
	CNdlStaticModelRes* res = FindRefStaticModel( path );
	if( NULL == res) 
	{
		res = MeNew CNdlStaticModelRes();
		Assert( NULL != res );
		Assert( strlen( path ) < RES_NAME_LEN );
		res->SetName( path );
		m_modelPtrHash.Put(path, res );
	}

	return res;
}

CDoodadRes* CNdlGlobalResMgr::RetriveRefDoodad( const char* doodadName )
{
	char path[MAX_PATH*2];
#if _MSC_VER >= 1400
	strcpy_s( path, doodadName );
	_strlwr_s( path );
#else
	strcpy( path, doodadName );
	_strlwr( path );
#endif
	CDoodadRes* res = m_doodadPtrHash.Get( path );
	if( NULL == res) 
	{
		res = MeNew CDoodadRes();
		Assert( NULL != res );
		Assert( strlen( path ) < RES_NAME_LEN );
		res->SetName( path );
		m_doodadPtrHash.Put(path, res );
	}

// 	res->IncRefCount();

	return res;

}

// void CNdlGlobalResMgr::UnloadRefDoodad( const char* doodadName )
// {
// 	char path[MAX_PATH*2];
// #if _MSC_VER >= 1400
// 	strcpy_s( path, doodadName );
// 	_strlwr_s( path );
// #else
// 	strcpy( path, doodadName );
// 	_strlwr( path );
// #endif
// 	CDoodadRes* pDoodadRes = FindRefDoodad( path );
// 	if (NULL != pDoodadRes) //only is referenced by this->m_doodadPtrHash;
// 	{
// 		pDoodadRes->DecRefCount();
// 		if (pDoodadRes->RefCount() == 0)
// 		{
// 			int pos = m_doodadPtrHash.Find(path);
// 			MeDelete pDoodadRes;
// 			m_doodadPtrHash.Remove(pos);
// 		}
// 	}
// 
// }

// CDoodadRes* CNdlGlobalResMgr::FindRefDoodad( const char* doodadName )
// {
// 	return m_doodadPtrHash.Get(doodadName);
// }

CNdlTextureRes* CNdlGlobalResMgr::GetCurrFrameLiquidRes( sInt32 liquidId )
{
	if( (liquidId < 0) || (liquidId >= m_liquidResList.size()) ) {
		return NULL;
	}
	return ((CNdlLiquidRes*)m_liquidResList[liquidId])->GetTexture();

}

CNdlTextureRes* CNdlGlobalResMgr::GetCurrFrameLiquidNormalRes( sInt32 liquidId )
{
	if( (liquidId < 0) || (liquidId >= m_liquidResList.size()) ) {
		return NULL;
	}
	return ((CNdlLiquidRes*)m_liquidResList[liquidId])->GetNormalTexture();

}

void CNdlGlobalResMgr::UnloadModelDoodad()
{
	for (size_t i = 0; i < m_modelPtrHash.Size(); ++i)
	{
		CNdlStaticModelRes* pModel = m_modelPtrHash[i];
		if (NULL != pModel)
		{
			if (pModel->IsLoad())
			{
				pModel->UnloadModel();
			}
		}
	}
	for (size_t i = 0; i < m_doodadPtrHash.Size(); ++i)
	{
		CDoodadRes* pModel = m_doodadPtrHash[i];
		if (NULL != pModel)
		{
			if (pModel->IsLoad())
			{
				pModel->UnloadModel();
			}
		}
	}

}

void CNdlGlobalResMgr::DestoryModelDoodad()
{
	for (size_t i = 0; i < m_modelPtrHash.Size(); ++i)
	{
		CNdlStaticModelRes* pModel = m_modelPtrHash[i];
		if (NULL != pModel)
		{
			SAFE_DELETE(pModel);
		}
	}
	m_modelPtrHash.Clear();
	for (size_t i = 0; i < m_doodadPtrHash.Size(); ++i)
	{
		CDoodadRes* pModel = m_doodadPtrHash[i];
		if (NULL != pModel)
		{
			assert(pModel->RefCount() == 0);
			SAFE_DELETE(pModel);
		}
	}
	m_doodadPtrHash.Clear();
}