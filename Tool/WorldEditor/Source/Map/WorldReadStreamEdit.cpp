/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	WorldReadStream.cpp
* Create: 	10/06/2006
* Desc:		地图读取类
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#include "stdafx.h"
#include "RapidXml/MeRapidXml.h"
#include "MeTerrain/WorldPrecompiled.hpp"
// #include "atlpath.h"
#include "Map/WorldReadStreamEdit.h"
#include "MeTerrain/MapConfigXml.h"
// #include "MeTerrain/FlyRouteXml.h"
#include "MeTerrain/NPCRouteXml.h"
#include "MeTerrain/SoundPointXml.h"
#include "tstring.h"
//#include "Launcher/DataLauncher.h"
#include <Me3d/PostProcess/PostProcessManager.h>
#include "MeTerrain/Lighting/MeshLightmapColorData.h"
#include "MeTerrain/Lighting/LightRes.h"

////////////////////////////////////////////////////////////////////////////////
namespace
{
	bool IsSame4Segment( const sInt8* a, const char* b )	
	{
		return ( (a[0]==b[0]) && (a[1]==b[1]) && (a[2]==b[2]) && (a[3]==b[3]) );
	}
};

#define CheckThrow( x )		if( !(x) ){ throw #x; }

extern bool g_IsShuiHu ;

void CWorldReadStreamEdit::ColorChange( COLORREF& niColor )
{
	if (!g_IsShuiHu)
	{
		return;
	}
	if (niColor == 0xFFFFFFFF || 0xff7f7f7f == niColor)
	{
		niColor = 0x227F7F7F;
	}
}

////////////////////////////////////////////////////////////////////////////////
CWorldReadStreamEdit::CWorldReadStreamEdit( CWorldBuffer* worldBuffer )
:CWorldReadStream(worldBuffer)
{
	m_ColorChange = (ColorChangeFun)ColorChange;
}

CWorldReadStreamEdit::~CWorldReadStreamEdit()
{
}

bool CWorldReadStreamEdit::LoadWorld( const char* worldPath)
{
	if(false == CMapConfigXml::Instance()->LoadMapConfig())
	{
		if (false == CMapConfigXml::Instance()->LoadMapConfig_Old()) 
		{
			CMapConfigXml::Instance()->InitializeMapConfig();
		}	

	}
	if( !EnumFile( /*strPath*/worldPath,(swFileOperation)LoadTileHash,this,true ) )
		return false;
	CSoundPointXml::Instance()->LoadSoundPoint(true);
// 	CFlyRouteXml::Instance()->LoadFlyRoute();
	CNPCRouteXml::Instance()->LoadNPCRoute();
	return true;
}

bool CWorldReadStreamEdit::LoadTile( CWorldTile* tile )
{
	Assert( !tile->IsLoad() );

	char fileName[MAX_PATH*2];
	sprintf_s( fileName, MAX_PATH*2, "%s\\%s", m_worldBuffer->GetWorld()->GetWorldPath(), tile->GetPathName() );
	if( !LoadWtd( tile, fileName ) )
	{
		return false;
	}

	// 加载寻路图
	tile->LoadReachableMap(false);
	if (!tile->IsLoadReachableMap())
	{
		((CMainFrame *) AfxGetMainWnd())->SetPromptText("加载寻路地图失败, 请查看Map.Config中是否填写了ClientReachableMap字段", 10000, "Ready");
	}

	if (tile->GetMonsterPath()[0] == '\0')
	{
		char cTemp[MAX_PATH];
		strcpy_s(cTemp,MAX_PATH,tile->GetPathName());
		char* pFind = strstr(cTemp,".mew");
		strcpy(&pFind[1],"monster");
		tile->SetMonsterPath(cTemp);
// 		std::string strxmlPath;
// 		strxmlPath = (fileName);
// 		//std::string::size_type fileNameBegin = strxmlPath.rfind('\\');
// 		std::string::size_type fileNameBegin = strxmlPath.rfind(".mew");
// 
// 		strxmlPath.erase(strxmlPath.begin() + fileNameBegin + 1,strxmlPath.end());
// 		strxmlPath += "monster";
	}
	{
		char monsterFileName[MAX_PATH*2];
		sprintf_s( monsterFileName, MAX_PATH*2, "%s\\%s", m_worldBuffer->GetWorld()->GetWorldPath(), tile->GetMonsterPath() );
		if (!LoadMonsterData( tile, monsterFileName ))
		{
			// 		strxmlPath.erase(strxmlPath.size() - 4);
			// 		LoadMonsterData( tile, strxmlPath.c_str() );
		}
	}
	

	_strlwr(fileName);
	char* pFind = strstr(fileName,".mew");
	strcpy(&pFind[1],"road");
	LoadRoadRes(tile,fileName);
    LoadNpc(tile);         //载入NPc
	strcpy(&pFind[1],"grass");
	if (!LoadDoodadRes(tile,fileName))
	{
		strcpy(&pFind[1],"cao");
		LoadDoodadRes(tile,fileName);
	}
	strcpy(&pFind[1],"Zone");
	if (!LoadZoneRes(tile,fileName))
	{
		strcpy(&pFind[1],"Zone.xml");
		LoadZoneRes(tile,fileName);
	}

	MeshLightmapColorData::GetInstance()->Clear();
	if( m_wifhead.version >= WORLD_FILE_LASTEST_108 )
	{
		// 模型灯光图数据Light Map Color Data
		strcpy(&pFind[1],"lmcd");
		LoadLightmapColorData(fileName);
	}

	StaticLightsContainer::GetInstance()->Clear();
	if( m_wifhead.version >= WORLD_FILE_LASTEST_109 )
	{
		// 静态光源数据
		strcpy(&pFind[1],"lights");
		LoadStaticLights(fileName);
	}

	for( sInt32 i = 0; i < ( tile->GetChunkTotal() ); ++i ) 
	{
		CWorldChunk* worldChunk = tile->GetChunk(i);
		InitializeLoadLevel(worldChunk);
	}

	D3DXVECTOR3 vC( tile->GetContrastOffsetR(), tile->GetContrastOffsetG(), tile->GetContrastOffsetB() );
	PostProcessManager::instance().SetBrightNContrast( tile->GetBrightnessOffset(), vC );
	PostProcessManager::instance().setParameter( "BloomScale", D3DXVECTOR4( tile->GetBloomScale(), 0, 0, 0 ) );
	PostProcessManager::instance().setParameter( "Luminance", D3DXVECTOR4( tile->GetLuminance(), 0, 0, 0 ) );

	return true;
}



static LONG AllObjectCount = 0;
static LONG CurrentLoadCount = 0;



#include "MeTerrain/MonsterFile.h"

bool CWorldReadStreamEdit::LoadMonsterData( CWorldTile* tile, const char* pathName )
{
	//<Stage>
	//	<Zone>
	//		<ZoneInfo Name = "0" Left = "40" Top = "64" Right = "44" Bottom = "74" AIStep = "0" CanPK = "false" CanPrivateShop = "false" EnterScript = "NULL" LeaveScript = "NULL">
	//		</ZoneInfo>
	//		...
	//	</Zone>
	//	<Monster>
	//		<MonsterGroup>
	//			<MonsterGroupInfo ZoneId = "0" X = "40.8809" Y = "72.8907" RandRange = "false" Dir = "2" TemplateName = "机关地刺#" 
	//							  Index = "17011" Number = "1" Relife = "36000000" County = "0" Enable = "true" Hide = "true" 
	//							  DeadScript = "Script\quest\GUAIWU\0000.s" LuaScript = "NULL" AIValue = "1000" MoveAIType = "1" 
	//							  AttackAIType = "1" IdleMoveAIType = "1" SpecialAIType = "1">
	//			</MonsterGroupInfo>
	//		</MonsterGroup>
	//		...
	//	</Monster>
	//</Stage>
	Assert( NULL != tile );
	Assert( NULL != pathName );

	MeXmlDocument monsterDocument;
	char xmlName[MAX_PATH*2];
	sprintf_s(xmlName, MAX_PATH*2, "%s", pathName);
	if (!monsterDocument.LoadFile(xmlName))
	{
		Trace("no monster data");
		return true;
	}

	CResEditMgr *resMgr = (CResEditMgr *) tile->GetCResMgr();
	resMgr->CleanMonsterQuad();

	MeXmlElement *pRoot = monsterDocument.FirstChildElement("Stage")->ToElement();

	// 读取Zones
	MeXmlElement *pZone = pRoot->FirstChildElement("Zone");
	MeXmlElement *pZoneInfo = pZone->FirstChildElement("ZoneInfo");
	while (pZoneInfo != NULL)
	{
		float fLeft, fRight, fTop, fBottom;
		int nQueryValue = 0;
		std::wstring strQueryValue;

		// top和bottom相反取值，配合服务器
		pZoneInfo->QueryFloatAttribute("Left", &fLeft);
		fLeft = MAP_GRID_SIZE * ( fLeft + 0.5f);
		pZoneInfo->QueryFloatAttribute("Right", &fRight);
		fRight = MAP_GRID_SIZE * ( fRight - 1.5f);
		pZoneInfo->QueryFloatAttribute("Top", &fBottom);
		fBottom = MAP_GRID_SIZE * ( fBottom + 0.5f);
		pZoneInfo->QueryFloatAttribute("Bottom", &fTop);
		fTop = MAP_GRID_SIZE * ( fTop - 1.5f);
		CMonsterQuadRes *pRes = resMgr->PushMonsterQuad(fTop, fLeft, fRight, fBottom);

		strQueryValue = Common::_tstring::UTF8towcs(pZoneInfo->Attribute("Name"));
		pRes->SetZoneName(Common::_tstring::toNarrowString(strQueryValue.c_str()).c_str());

		pZoneInfo->QueryIntAttribute("MonsterCount", &nQueryValue);
		pRes->m_nNumber = nQueryValue;

		pZoneInfo->QueryIntAttribute("AIStep", &nQueryValue);
		pRes->m_nAIStep = nQueryValue;

		pZoneInfo->QueryIntAttribute("CanPK", &nQueryValue);
		pRes->m_nPKMode = nQueryValue;

		//lyhqiecuo
		pRes->m_bCanDuel = 1;
		if(pZoneInfo->QueryIntAttribute("CanDuel", &nQueryValue) == 0)
		pRes->m_bCanDuel = nQueryValue > 0;

		strQueryValue = Common::_tstring::UTF8towcs(pZoneInfo->Attribute("CanPrivateShop"));
		pRes->m_bCanStall = ((strQueryValue == L"true") ? true : false);

		strQueryValue = Common::_tstring::UTF8towcs(pZoneInfo->Attribute("EnterScript"));
		pRes->SetEnterScript(Common::_tstring::toNarrowString(strQueryValue.c_str()).c_str());

		strQueryValue = Common::_tstring::UTF8towcs(pZoneInfo->Attribute("LeaveScript"));
		pRes->SetLeaveScript(Common::_tstring::toNarrowString(strQueryValue.c_str()).c_str());

		pZoneInfo = pZoneInfo->NextSiblingElement("ZoneInfo");
	}

	// 读取Monsters
	MeXmlElement *pMonster = pRoot->FirstChildElement("Monster");
	if (pMonster != NULL)
	{
		MeXmlElement* pMonsterGroup = pMonster->FirstChildElement("MonsterGroup");
		while (pMonsterGroup)
		{
			MeXmlElement* pMonsterGroupInfo = pMonsterGroup->FirstChildElement("MonsterGroupInfo");
			if (pMonsterGroupInfo)
			{				
				float fX, fY;
				int nValue = 0;

				int nZoneId;
				pMonsterGroupInfo->QueryIntAttribute("ZoneId", &nZoneId);
				CMonsterQuadRes *quadRes = resMgr->GetMonsterQuadList()[nZoneId];

				pMonsterGroupInfo->QueryFloatAttribute("X", &fX);
				fX = MAP_GRID_SIZE * ( fX - 0.5f);

				pMonsterGroupInfo->QueryFloatAttribute("Y", &fY);
				fY = MAP_GRID_SIZE * ( fY - 0.5f);

				pMonsterGroupInfo->QueryIntAttribute("Index", &quadRes->m_nMonsterId);
				pMonsterGroupInfo->QueryIntAttribute("Camp", &quadRes->m_nCamp);
				pMonsterGroupInfo->QueryIntAttribute("Country", &quadRes->m_nCountry);
				pMonsterGroupInfo->QueryIntAttribute("Force", &quadRes->m_nForce);
				pMonsterGroupInfo->QueryIntAttribute("Path", &quadRes->m_nPath);
				pMonsterGroupInfo->QueryIntAttribute("County", &quadRes->m_nCountry); //lyh++

				quadRes->m_bEnable = true;
				quadRes->m_bHide = false;
				quadRes->m_bRandRange = false;
				quadRes->m_bIsOnePoint = true;
				
				{
					pMonsterGroupInfo->QueryIntAttribute("Relife", &quadRes->m_nRelife);
					pMonsterGroupInfo->QueryIntAttribute("Number", &quadRes->m_nNumber);
					pMonsterGroupInfo->QueryIntAttribute("Dir", &quadRes->m_nDir);
					pMonsterGroupInfo->QueryIntAttribute("AIValue", &quadRes->m_nAIValue);

					std::wstring str = Common::_tstring::UTF8towcs(pMonsterGroupInfo->Attribute("DeadScript"));
					strcpy(quadRes->m_szDeadScript, Common::_tstring::toNarrowString(str.c_str()).c_str());

					str = Common::_tstring::UTF8towcs(pMonsterGroupInfo->Attribute("LuaScript"));
					strcpy(quadRes->m_szAIScript, Common::_tstring::toNarrowString(str.c_str()).c_str()); //读取的地方
				}
				
				// 更新怪物模型
				quadRes->UpdateMonsterModel();

				pMonsterGroupInfo = pMonsterGroupInfo->NextSiblingElement("MonsterGroupInfo");
			}

			pMonsterGroup = pMonsterGroup->NextSiblingElement("MonsterGroup");
		}
	}

	return true;
}

bool CWorldReadStreamEdit::ReadRoadTable( FILE* stream, CResEditMgr* resMgr )
{
	TWTDShadowTable kRoadTable;
	sInt32 numRead = fread( &kRoadTable, 1, sizeof(TWTDShadowTable), stream );
	CheckThrow( IsSame4Segment(kRoadTable.head.segment,"WRMD") );

	for( uInt32 i = 0; i < kRoadTable.head.size; ++i )
	{
// 		uInt8 ucRoadData[64*64];
		{
			TWTDAlphaMap shadowMap;
			numRead = fread( &shadowMap, 1, sizeof(TWTDAlphaMap), stream );
			CheckThrow( numRead == sizeof(TWTDAlphaMap) );
// 			GetAlphaData(ucRoadData, shadowMap.alpha);
			resMgr->PushRoad( shadowMap.alpha );
		}
	}
	return true;

}

bool CWorldReadStreamEdit::LoadRoadRes( CWorldTile* tile, const char* pathName )
{
	Assert( NULL != tile );
	Assert( NULL != pathName );

	size_t uiReadSize = 0;
	FILE* stream = NULL;
	try
	{
		sInt32 offset = 0;
		CheckThrow( fopen_s( &stream, pathName, "rb" ) == 0 );


		TRoadResHead head;
		uiReadSize = fread( &head, sizeof( TRoadResHead ), 1, stream );
		CheckThrow( uiReadSize != sizeof(TRoadResHead) );
		CheckThrow( IsSame4Segment( head.head.segment, "WRDH" )  );	
		if (head.version < WORLD_FILE_LASTEST_105)
		{
// 			if (head.version >= WORLD_FILE_OLD_VERSION)
// 			{
// 				Trace( "Old world file (%s)version [%d]!\n",pathName, head.version);
// 			}
// 			else
			{
				throw( "unsupported Road file version \n" );
			}
		}
		else if (head.version >= WORLD_FILE_LASTEST_106)
		{
			for( sInt32 chunkId=0; chunkId<(tile->GetChunkTotal()); chunkId++ ) 
			{
				TWTDRoadInfo info;
				uiReadSize = fread( &info, sizeof( TWTDRoadInfo ), 1, stream );
				CheckThrow( uiReadSize != sizeof(TWTDRoadInfo) );
				tile->GetChunk(chunkId)->m_road = info.roadResId;
			}
		}

		{
//  			CheckThrow( 0 == fseek( stream, sizeof(TRoadResHead), SEEK_SET ) );
			if( !ReadRoadTable( stream, (CResEditMgr*)tile->GetCResMgr() ) )
			{
				Trace( "Error read road table! \n" );
			}
		}

		Trace( "Load road table OK \n" );
		fclose( stream );
	}
	catch( const char* s )
	{
		Trace( "failed read road resource:[ %s ] \n", s );
		for (int i = 0; i < tile->GetRowColumn()[0];++i)
		{
			for(int j = 0; j < tile->GetRowColumn()[1];++j)
			{
				CWorldChunk* pChunk = tile->GetChunk(i,j);
				pChunk->m_road = RES_INVALID_ID;
			}
		}
		if( NULL != stream )
		{
			fclose( stream );
			stream	= NULL;
		}
		return false;
	}

	return true;

}

bool   CWorldReadStreamEdit::LoadNpc(CWorldTile* pTile)
{
    sInt32 mapID = pTile->GetMapId();

    NpcInfo::Npcs::iterator it  = theNpcInfo.npcs_.begin();
    NpcInfo::Npcs::iterator end = theNpcInfo.npcs_.end();

    for (;it != end;++it)
    {
        if(it->second.mapId == mapID)
            ((CResEditMgr*)pTile->GetCResMgr())->AddNpc(&it->second);
    }
    return true;
}

void CWorldReadStreamEdit::ReadInDoodadData( TDoodadLevelInfo* pLevelInfo, TWTDDoodesRef &doodes, FILE* stream, CWorldTile* tile, CWorldChunk* worldChunk )
{
	fread(pLevelInfo->GetDoodadMap(),sizeof(TDoodadInfoForEdit)*doodes.mulevelUnit*doodes.mulevelUnit,1,stream);
// 	tile->GetCResMgr()->IncDoodadRef(pLevelInfo->mdoodadId);
// 	pLevelInfo->RefreshDoodad(tile->GetCResMgr(),worldChunk,tile);
}

void CWorldReadStreamEdit::InitializeLoadLevel( CWorldChunk* worldChunk )
{
	worldChunk->SetLoadLevel(CWorldChunk::eDoodadLoaded);
}

void CWorldReadStreamEdit::AddDoodadLevel( CWorldChunk* worldChunk, TWTDDoodesRef &doodes )
{
	worldChunk->AddDoodadLevel(doodes.mulevelUnit,true);

}

void CWorldReadStreamEdit::LoadTileHash( LPCTSTR strPath, void* point)
{
	const char* pos  =  strstr( strPath, _T(".mew")); 
	if(!pos ||  (strlen(strPath) - 4 != pos - strPath )) 
	{
		return;
	}
	char workPathName[MAX_PATH*2];
	GetRelativePathToWorldPath(strPath,workPathName);
	CWorldReadStreamEdit* pStream = (CWorldReadStreamEdit*)point;
	pStream->GetWorldBuffer()->PushTileRes(-1,workPathName);
}

bool CWorldReadStreamEdit::LoadLightmapColorData( const char* pathName )
{
	Assert( NULL != pathName );
	if( !pathName )
		return false;

	size_t uiReadSize = 0;
	FILE* stream = NULL;
	try
	{
		if( fopen_s( &stream, pathName, "rb" ) != 0 )
		{
			// 没文件
			return false;
		}

		TMeshLightMapHead head;
		uiReadSize = fread( &head, sizeof( TMeshLightMapHead ), 1, stream );
		CheckThrow( uiReadSize == 1 );
		CheckThrow( IsSame4Segment( head.head.segment, "WMLM" )  );	

		MeshLightmapColorData::GetInstance()->Clear();

		sInt32 count = 0;
		fread( &count, sizeof(sInt32), 1, stream );
		for( int i=0; i<count; ++i )
		{
			sInt32 key = 0;
			sInt32 resolution = 0;
			fread( &key, sizeof(sInt32), 1, stream );
			if( key == INVALID_LIGHTMAP_DATA )
			{
				// 数据有问题
				continue;
			}
			fread( &resolution, sizeof(sInt32), 1, stream );
			CheckThrow( key >= 0 );
			CheckThrow( resolution >= 0 );

			MeshLightmapColorData::LMColorData* pColorData = new MeshLightmapColorData::LMColorData;
			CheckThrow( NULL != pColorData );
			pColorData->m_nColorDataResolution = resolution;
			pColorData->m_pColorData = new NiColorB[resolution*resolution];
			CheckThrow( NULL != pColorData->m_pColorData );

			sInt32 size = resolution * resolution;
			uiReadSize = fread( pColorData->m_pColorData, sizeof(NiColorB), resolution*resolution, stream );
			CheckThrow( uiReadSize == size );

			MeshLightmapColorData::GetInstance()->PushColorData(key, pColorData);
		}

		Trace( "Load mesh light map color data OK \n" );
		fclose( stream );
	}

	catch( const char* s )
	{
		Trace( "failed read mesh light map color data:[ %s ] \n", s );
		if( NULL != stream )
		{
			fclose( stream );
			stream	= NULL;
		}
		return false;
	}

	return true;
}

bool CWorldReadStreamEdit::LoadStaticLights( const char* pathName )
{
	Assert( NULL != pathName );
	if( !pathName )
		return false;

	size_t uiReadSize = 0;
	FILE* stream = NULL;
	try
	{
		if( fopen_s( &stream, pathName, "rb" ) != 0 )
		{
			// 没文件
			return false;
		}

		TStaticLightHead head;
		uiReadSize = fread( &head, sizeof( TStaticLightHead ), 1, stream );
		CheckThrow( uiReadSize == 1 );
		CheckThrow( IsSame4Segment( head.head.segment, "WSLR" )  );	

		sInt32 count = 0;
		fread( &count, sizeof(sInt32), 1, stream );
		
		StaticLightsContainer::GetInstance()->Clear();

		for( int i=0; i<count; ++i )
		{
			unsigned char type = 0;
			fread(&type, sizeof(unsigned char), 1, stream);
			CheckThrow( type < LightRes::LT_MAX );

			sInt32 nID = 0;
			fread(&nID, sizeof(sInt32), 1, stream);
			if( nID == INVALID_STATIC_LIGHT_DATA )
				continue;

			switch( type )
			{
			case LightRes::LT_POINTLIGHT:
				{
					PointLight* pPointLight = MeNew PointLight;
					if( !pPointLight )
					{
						CheckThrow(0&&"点光源内存分配出错");
					}
					else
					{
						if( pPointLight->Read(stream) )
						{
							StaticLightsContainer::GetInstance()->InsertLight(nID, pPointLight);
						}
						else
						{
							CheckThrow(0&&"点光源数据读取出错");
						}
					}
				}
				break;
			default:
				{
					CheckThrow(0&&"光源类型出错");
					break;
				}
			}
		}

		Trace( "Load static lights data OK \n" );
		fclose( stream );
	}

	catch( const char* s )
	{
		Trace( "failed read static lights data:[ %s ] \n", s );
		if( NULL != stream )
		{
			fclose( stream );
			stream	= NULL;
		}
		return false;
	}

	return true;
}