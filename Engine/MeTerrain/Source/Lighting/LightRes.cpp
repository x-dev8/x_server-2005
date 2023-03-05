//-----------------------------------------------------------------------------
// File:	LightRes.cpp
// Desc:	静态光照资源定义
// Create: 	02/21/2011
// Author:	Qiu Li
//
// Copyright ShenWang 2011 - All Rights Reserved.
//-----------------------------------------------------------------------------
#include "MeTerrain/Lighting/LightRes.h"
#include "MeTerrain/stdafx.h"

////////////////////////////////////////////////////////////////////////////////////////////
// 灯光资源
bool LightRes::Read( FILE* stream )
{
	assert(stream);
	if( !stream )
		return false;

	fread(&m_Color, sizeof(NiColorB), 1, stream);

	return true;
}

bool LightRes::SaveToFile( FILE* stream )
{
	assert(stream);
	if( !stream )
		return false;

	fwrite(&m_Color, sizeof(NiColorB), 1, stream);
	
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////
// 点光源
bool PointLight::Read( FILE* stream )
{
	assert(stream);
	if( !stream )
		return false;

	LightRes::Read( stream );

	fread(&m_fNearDist, sizeof(float), 1, stream);
	fread(&m_fDist, sizeof(float), 1, stream);
	fread(&m_vPos, sizeof(Vector), 1, stream);

	return true;
}

bool PointLight::SaveToFile( FILE* stream )
{
	assert(stream);
	if( !stream )
		return false;

	LightRes::SaveToFile(stream);

	fwrite(&m_fNearDist, sizeof(float), 1, stream);
	fwrite(&m_fDist, sizeof(float), 1, stream);
	fwrite(&m_vPos, sizeof(Vector), 1, stream);

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////
// 方向光
bool DirectionLight::Read( FILE* stream )
{
	assert(stream);
	if( !stream )
		return false;

	LightRes::Read( stream );

	fread(&m_vDir, sizeof(Vector), 1, stream);
	return true;
}

bool DirectionLight::SaveToFile( FILE* stream )
{
	assert(stream);
	if( !stream )
		return false;

	// 是地表光源，则不保存
	if( IsChunkLight() )
		return true;

	LightRes::SaveToFile(stream);
	
	fwrite(&m_vDir, sizeof(Vector), 1, stream);
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////
// 全局静态灯光容器
void StaticLightsContainer::Clear()
{
	m_mapObjectAffectLight.clear();

	if( 0 == m_mapStaticLights.size() )
		return;

	std::map<unsigned short, LightRes*>::const_iterator iter = m_mapStaticLights.begin();
	for(; iter != m_mapStaticLights.end(); ++iter )
	{
		if( iter->second )
		{
			delete iter->second;
		}
	}
	m_mapStaticLights.clear();
}

bool StaticLightsContainer::InsertLight( unsigned short id, LightRes* pLight )
{
	if( !pLight )
		return false;

	std::map<unsigned short, LightRes*>::const_iterator iter = m_mapStaticLights.find(id);
	if( iter == m_mapStaticLights.end() )
	{
		m_mapStaticLights.insert(std::map<unsigned short, LightRes*>::value_type(id, pLight));
		m_usMaxKey = max(id, m_usMaxKey);
	}
	else
	{
		// 提示，不做任何处理
		char msg[256] = {0};
		sprintf_s(msg, sizeof(msg)-1, "WARNING: 静态光源ID重复 ID: %d .\n", id);
		OutputDebugString(msg);
		return false;
	}

	return true;
}

bool StaticLightsContainer::InsertLight( LightRes* pLight, unsigned short& usOutId )
{
	if( !pLight )
		return false;

	if( m_usMaxKey == 65535 )	// 满了
	{
		// 逐个查找比较慢
		bool bFind = false;
		if( m_mapStaticLights.size() < 65535 )	// 查找没用到id
		{
			int nAvailableId = 0;
			while( nAvailableId <= 65535 )
			{
				std::map<unsigned short, LightRes*>::const_iterator iter = m_mapStaticLights.find(nAvailableId);
				if( iter == m_mapStaticLights.end() )
				{
					bFind = true;
					break;
				}
				++nAvailableId;
			}
			if( bFind )
			{
				m_mapStaticLights.insert(std::map<unsigned short, LightRes*>::value_type(nAvailableId, pLight));
				usOutId = nAvailableId;
			}
		}
		if( !bFind )
		{
			char msg[256] = {0};
			sprintf_s(msg, sizeof(msg)-1, "WARNING: 静态光源个数满65535，创建失败\n");
			OutputDebugString(msg);
			return false;
		}
	}
	else
	{
		if( m_mapStaticLights.size() == 0 )
			m_usMaxKey = 0;
		else
			++m_usMaxKey;
		m_mapStaticLights.insert(std::map<unsigned short, LightRes*>::value_type(m_usMaxKey, pLight));
		usOutId = m_usMaxKey;
	}

	return true;
}

bool StaticLightsContainer::RemoveLight( unsigned short key )
{
	std::map<unsigned short, LightRes*>::iterator iter = m_mapStaticLights.find(key);
	if( iter == m_mapStaticLights.end() )
		return false;

	m_mapStaticLights.erase(iter);
	return true;
}

bool StaticLightsContainer::GetAffectLights( TObjectInfo* pObject, CWorldTile* pTile, std::vector<LightRes*>& outLights, BOOL bReCalculate /*= TRUE*/ )
{
	if( !pObject || !pTile )
		return false;

	// 重新统计
	if( bReCalculate || 0 == m_mapObjectAffectLight.size() )
		RetrieveAllObjectsAffectLights(pTile);

	if( 0 == m_mapObjectAffectLight.size() )
		return false;

	std::map<TObjectInfo*, std::vector<unsigned short>>::iterator iter = m_mapObjectAffectLight.find(pObject);
	if( iter == m_mapObjectAffectLight.end() )
		return false;

	outLights.clear();
	std::vector<unsigned short>& vecLights = iter->second;
	for( int i=0; i<vecLights.size(); ++i )
	{
		std::map<unsigned short, LightRes*>::const_iterator itLight = m_mapStaticLights.find(vecLights[i]);
		if( itLight != m_mapStaticLights.end() && itLight->second )
		{
			outLights.push_back(itLight->second);
		}
	}

	return true;
}

void StaticLightsContainer::RetrieveAllObjectsAffectLights(CWorldTile* pTile)
{
	m_mapObjectAffectLight.clear();

	if( 0 == m_mapStaticLights.size() )
		return;

	std::map<unsigned short, LightRes*>::iterator iter = m_mapStaticLights.begin();
	for( ; iter != m_mapStaticLights.end(); ++iter )
	{
		std::vector<TObjectInfo*> vecObjects;
		vecObjects.clear();

		if( RetrieveAffectObjects( iter->first, pTile, vecObjects) )
		{
			unsigned short key = iter->first;
			for( int i=0; i<vecObjects.size(); ++i )
			{
				if( !vecObjects[i] )
					continue;

				std::map<TObjectInfo*, std::vector<unsigned short>>::iterator itObj = m_mapObjectAffectLight.find(vecObjects[i]);
				if( itObj == m_mapObjectAffectLight.end() )
				{
					std::vector<unsigned short> vecLights;
					vecLights.push_back(key);
					m_mapObjectAffectLight.insert(std::map<TObjectInfo*, std::vector<unsigned short>>::value_type(vecObjects[i], vecLights));
				}
				else
				{
					std::vector<unsigned short>& vecLights = itObj->second;
					bool bFind = false;
					for( int j=0; j<vecLights.size(); ++j )
					{
						if( vecLights[j] == key )
						{
							bFind = true;
							break;
						}
					}
					if( !bFind )
						vecLights.push_back(key);
				}
			}
		}
	}
}

bool StaticLightsContainer::RetrieveAffectObjects( unsigned short key, CWorldTile* pTile, std::vector<TObjectInfo*>& outObjects )
{
	std::map<unsigned short, LightRes*>::iterator iter = m_mapStaticLights.find(key);
	if( iter == m_mapStaticLights.end() )
		return false;

	return RetrieveAffectObjects(iter->second, pTile, outObjects);
}

bool StaticLightsContainer::RetrieveAffectObjects( LightRes* pLightRes, CWorldTile* pTile, std::vector<TObjectInfo*>& outObjects )
{
	assert(pLightRes && pTile);
	if( !pLightRes || !pTile )
		return false;

	CResMgr* resMgr = pTile->GetCResMgr();
	if( !resMgr )
		return false;

	float fMinX = 0.f, fMaxX = 0.f, fMinY = 0.f, fMaxY = 0.f;
	Vector vLightPos;
	float fLightRadius = 0.f;

	switch( pLightRes->GetType() )
	{
	case LightRes::LT_POINTLIGHT:
		{
			PointLight* pLight = (PointLight*)pLightRes;
			fMinX = pLight->GetPos().x - pLight->GetDist();
			fMaxX = pLight->GetPos().x + pLight->GetDist();
			fMinY = pLight->GetPos().y - pLight->GetDist();
			fMaxY = pLight->GetPos().y + pLight->GetDist();
			vLightPos = pLight->GetPos();
			fLightRadius = pLight->GetDist();
		}
		break;
	default:
		{
			assert(0&&"光源类型不支持");
			return false;
		}
		break;
	}

	CWorldChunk *pWorldChunk = pTile->GetChunkFromPos(fMinX, fMinY);
	int nMinChunkX = pWorldChunk->GetChunkX();
	int nMinChunkY = pWorldChunk->GetChunkY();
	pWorldChunk = pTile->GetChunkFromPos(fMaxX, fMaxY);
	int nMaxChunkX = pWorldChunk->GetChunkX();
	int nMaxChunkY = pWorldChunk->GetChunkY();

	for( int Y = nMinChunkY; Y <= nMaxChunkY; ++Y )
	{
		for( int X = nMinChunkX; X <= nMaxChunkX; ++X )
		{
			pWorldChunk = pTile->GetChunk(X, Y);
			if( !pWorldChunk || pWorldChunk->GetStaticModelList().size() == 0 )
				continue;

			int nModelNum = pWorldChunk->GetStaticModelList().size();
			// 查找chunk里模型
			for( INT ModelIndex = 0; ModelIndex < nModelNum; ++ModelIndex )
			{
				sInt32 nModelId = pWorldChunk->GetStaticModelList()[ModelIndex];

				if( nModelId >= resMgr->GetStaticModelList().size() )
					continue;

				TObjectInfo* pObjInfo = resMgr->GetStaticModelList()[nModelId];
				if( !pObjInfo ||
					!pObjInfo->model ||
					!pObjInfo->model->GetMex() ||
					!((Mex2*)(pObjInfo->model->GetMex()))->GetGeometry() ||
					!pObjInfo->CastShadow() )
					continue;

				// 去掉草模型
				char name[MAX_PATH] = {0};
				strncpy(name, pObjInfo->model->GetMex()->GetFilename(), sizeof(name)-1 );
				strlwr(name);
				if( strstr(name, "grass") )
					continue;

				//MeMatrix mat;
				//pObjInfo->model->CalcTransformMatrix( &mat );

				// 静态模型
				BOOL bIsStatic = FALSE;
				Mex2Geometry* pGeometry = (Mex2Geometry*)((Mex2*)(pObjInfo->model->GetMex()))->GetGeometry();
				for( int nGeoChunk = 0; nGeoChunk < pGeometry->GetChunkCount(); ++nGeoChunk )
				{
					if( !pGeometry->GetChunk(nGeoChunk) )
						continue;

					Mex2GeoChunk* pGeoChunk = (Mex2GeoChunk*)pGeometry->GetChunk(nGeoChunk);

					if( pGeometry->GetChunk(nGeoChunk)->GetType() == Mex2GeoChunkProperty::eStatic )
					{
						bIsStatic = TRUE;
						break;
					}
				}

				// 判断相交
				if( bIsStatic )
				{
					Vector vModelCenter = pObjInfo->model->GetCenter();
					float fModelRadius = pObjInfo->model->GetRadius();

					float dist = (vModelCenter - vLightPos).length();
					if( dist <= fModelRadius + fLightRadius )
					{
						// 受光影响
						bool bFind = false;
						for( int k=0; k<outObjects.size(); ++k )
						{
							if( pObjInfo == outObjects[k] )
							{
								bFind = true;
								break;
							}
						}
						if( !bFind )
							outObjects.push_back(pObjInfo);
					}
				}
			}
		}//end for X
	}//end for Y

	return true;
}
