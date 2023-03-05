/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	ReachableMapGenerate.cpp
* Create: 	10/29/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#include "stdafx.h"
#include "Resource/Resource.h"
#include "ReachableMapGenerate.h"
#include "SwMap.h"
#include "Map/WorldWriteStream.h"
////////////////////////////////////////////////////////////////////////////////
static sInt32 Real2SeverMapScale = 1000;
sInt32 g_reachableMapScale = 32;
////////////////////////////////////////////////////////////////////////////////
CReachableMapGenerate::CReachableMapGenerate()
{
	m_interval	= 0.5f;
	Reset();
}

CReachableMapGenerate::~CReachableMapGenerate()
{
}


void CReachableMapGenerate::Reset()
{

	
}



char CReachableMapGenerate::IsRealPosReachable( flt32 posX, flt32 posY, flt32 angle,THeightResult* pheightResult,bool* bSlopeCheck)
{
	if (NULL == pheightResult)
	{
		static THeightResult heightResult;

		if(SwGlobal::GetWorldPicker()->GetHeight(posX,posY,heightResult))
			pheightResult = &heightResult;
		else
		{
			return 0;
		}

	}
// 	NiCamera* pCamera = g_render->GetSnapCamera();
// 	pCamera->SetTranslate(posX,posY,pheightResult->height + 10.f);
// 	pCamera->Update( 0.0f );
// 	Vector rayPt(posX,posY,pheightResult->height), rayDir(0.f,0.f,-1.f);

	static TPickResult pickResult;
	if (IsPickObj(posX, posY, pheightResult, pickResult))
	{
		if( emPT_FloorObj == pickResult.pickResultInfo[0].resultType ) 
		{
			goto REACHABLE;
		}
		else
			return 0;
	}

	if (pheightResult->isInLiquid)
	{
		goto REACHABLE;
	}

// 	static TPickResult pickNormalResult;
// 
// 
// 	if (!SwGlobal::GetWorldPicker()->Pick(Vector(posX,posY,pheightResult->height + 50.f),Vector(0.f,0.f,-1.f),pickNormalResult))
// 	{
// 		return 0;
// 	}

	float normal = pheightResult->normal.z;
// 	if( pickNormalResult.pickResultCount > 0 ) 
// 	{
// 		for( sInt32 i =0; i< MAX_PICK_OBJ_COUNT; i++ ) 
// 		{
// 			if( emPT_Terrain == pickNormalResult.pickResultInfo[i].resultType ) 
// 			{
// 				normal = pickNormalResult.pickResultInfo[i].normal.z;
// 			}
// 		}
// 	}
	Assert(normal > -0.00001);
	if(PI/2 -asin(normal) > angle)
	{
		if(bSlopeCheck)
		{
			*bSlopeCheck = true;
		}
		return 0;
	}
REACHABLE:
	{
		CWorldTile* ptile = CURRENTTILE;
		CWorldChunk* pChunk = ptile->GetChunk(ChunkFromPos(posX),ChunkFromPos(posY));
		sInt32 roadId = pChunk->GetRoad();
		if (RES_INVALID_ID != roadId)
		{
			CNdlAlphaRes* roadRes = ((CResEditMgr*)ptile->GetCResMgr())->GetRoad(roadId);
			uAlphaBit shadow[WORLD_TILE_CHUNK_ATOM_NUM*WORLD_TILE_CHUNK_ATOM_NUM];
			SwPublicFunc::GetAlphaData(shadow,roadRes->GetMaskData());
			int atomX = AtomFromPos(posX - WORLD_CHUNK_ORIGIN) % WORLD_TILE_CHUNK_ATOM_NUM;
			int atomY = AtomFromPos(posY - WORLD_CHUNK_ORIGIN) % WORLD_TILE_CHUNK_ATOM_NUM;
			switch (shadow[atomY*WORLD_TILE_CHUNK_ATOM_NUM + atomX])
			{
			case 0x00:
				return SwMap::MAIN_ROAD; 
			case 0x88:
				return SwMap::SUB_ROAD;
			default:
				return SwMap::OTHERS;
			}
		}
	}
	return SwMap::OTHERS;
}

bool CReachableMapGenerate::IsRealPosReachableInData( flt32 posX,flt32 posY, sInt32 width, flt32 interval,const unsigned char* pData )
{
	sInt32 targetPosX = ZnFloor2Int(posX/interval);
	sInt32 targetPosY = ZnFloor2Int(posY/interval);
	return IsReachable(targetPosX,targetPosY,width,pData);
}

//yanli[2010-8-6]----------------------------------------------------------------------------------------
bool CReachableMapGenerate::GenerateHeightMap( sInt32 tileId, sInt32 mapScale, const char* fileName )
{
	CWorld* pWorld = SwGlobal::GetWorld();
	CWorldTile* tile = pWorld->GetWorldBuffer()->GetTile( tileId);
	if( NULL == tile )
		return false;

	if( !tile->IsLoad() )
		return false;

	m_interval = WORLD_CHUNKSIZE/(float)mapScale;

	CWorldWriteStream writeStream(SwGlobal::GetWorld());
	if (!writeStream.RemoveReadOnly(fileName))
	{
		return false;
	}
	FILE* stream = NULL;
	try	{
		if( fopen_s( &stream, fileName, "wb" ) != 0 ) 
		{
			throw( "error open file !" );
		}
		TileHeightMapHeader header;
		memset( &header, 0, sizeof(TileHeightMapHeader) );
		header.version = SwMap::MAPVRSION;
		header.rate_R = WORLD_CHUNKSIZE;
		header.rate_M = mapScale;
		header.width = tile->GetRowColumn()[0]*WORLD_CHUNKSIZE*(header.rate_M/header.rate_R);
		header.height = tile->GetRowColumn()[1]*WORLD_CHUNKSIZE*(header.rate_M/header.rate_R);
		header.size = header.width*header.height;

		

		DWORD  dwWidthByteCount = header.width;
		float* pcDataTemp = new float[dwWidthByteCount * header.height];
		memset(pcDataTemp, 0, sizeof(float)*dwWidthByteCount * header.height);

		//计算高度图，临时保存为float型数据
		float maxHeight = -10000.0;
		float minHeight = 10000.0;
		flt32 posx = 0.f,posy= 0.f;
		for (DWORD j = 0; j < header.height; ++j)
		{
			posy = (j +0.5f)* m_interval ;
			for (DWORD i = 0; i < header.width; ++i)
			{
				posx = (i+0.5f) * m_interval;
				pcDataTemp[dwWidthByteCount*j + i] = GetZbyXY(posx,posy);
				if (pcDataTemp[dwWidthByteCount*j + i] < minHeight)
				{
					minHeight = pcDataTemp[dwWidthByteCount*j + i];
				}
				if (pcDataTemp[dwWidthByteCount*j + i] > maxHeight)
				{
					maxHeight = pcDataTemp[dwWidthByteCount*j + i];
				}
			}
		}

		header.minHeight = minHeight;
		header.maxHeight = maxHeight;
		fwrite( &header, sizeof( TileHeightMapHeader ), 1, stream );
		sInt32 offHead	= ftell( stream );

		//将高度图数据转化为0-255
		float delta = maxHeight - minHeight;
		if (delta < 0)
		{
			if( NULL != stream )
			{
				fclose( stream );
				stream	= NULL;
			}
			return false;
		}

		unsigned char* pcData = new unsigned char[dwWidthByteCount * header.height];
		for (DWORD j = 0; j < header.height; ++j)
		{
			for (DWORD i = 0; i < header.width; ++i)
			{
				pcData[dwWidthByteCount * j + i] = (unsigned char)(((pcDataTemp[dwWidthByteCount * j + i] - header.minHeight) * 255.0) / delta);
			}
		}
		delete [] pcDataTemp;
		
		fwrite( pcData, sizeof(unsigned char)*dwWidthByteCount * header.height, 1, stream );
		sInt32 offData				= ftell( stream );
		fclose( stream );
		stream = NULL;
		delete [] pcData;
		::AfxMessageBox( _T("高度图生成成功！") );
	}
	catch( const char* s )
	{
		Trace( "failed write HeightMap:[ %s ] \n", s );
		if( NULL != stream )
		{
			fclose( stream );
			stream	= NULL;
		}
		return false;
	}
	return true;
}

//------------------------------------------------------------------------------------------------------
bool CReachableMapGenerate::GenerateFile( sInt32 tileId,sInt32 mapScale,const char* fileName )
{
	CWorld* pWorld = SwGlobal::GetWorld();
	CWorldTile* tile = pWorld->GetWorldBuffer()->GetTile( tileId);
	if( NULL == tile )
		return false;

	if( !tile->IsLoad() )
		return false;

	m_interval = WORLD_CHUNKSIZE/(float)mapScale;

	CWorldWriteStream writeStream(SwGlobal::GetWorld());
	if (!writeStream.RemoveReadOnly(fileName))
	{
		return false;
	}
	FILE* stream = NULL;
	
	if (fopen_s(&stream, fileName, "wb") != 0) 
	{
		char temp[MAX_PATH] = {0};
		sprintf(temp, "无法创建寻路文件: %s", fileName);
		AfxMessageBox(temp);
		return false;
	}

	TileDataMapHeader header;
	memset( &header, 0, sizeof(TileDataMapHeader) );
	header.version = SwMap::MAPVRSION;
	header.rate_R = WORLD_CHUNKSIZE;
	header.rate_M = mapScale;
	header.width = tile->GetRowColumn()[0]*WORLD_CHUNKSIZE*(header.rate_M/header.rate_R);
	header.height = tile->GetRowColumn()[1]*WORLD_CHUNKSIZE*(header.rate_M/header.rate_R);
	header.size = header.width*header.height;
	fwrite( &header, sizeof( TileDataMapHeader ), 1, stream );
	sInt32 offHead = ftell( stream );

	DWORD  dwWidthByteCount = header.width;//( header.width + 7) >> 3;
	unsigned char* pcData = new unsigned char[ dwWidthByteCount * header.height];
	memset(pcData,0,sizeof(unsigned char)*dwWidthByteCount * header.height);
	flt32 posx = 0.f,posy= 0.f;
	size_t charIndex = 0;
	for (DWORD j = 0; j < header.height; ++j)
	{
		posy = (j +0.5f)* m_interval ;
		for (DWORD i = 0; i < header.width; ++i)
		{
			posx = (i+0.5f) * m_interval;
			pcData[dwWidthByteCount*j + i] = IsRealPosReachable(posx,posy,tile->GetReachableAngle()*PIOVER180);
// 				if (bReach)
// 				{
// 					charIndex = dwWidthByteCount*j + i;//(i >> 3);
// 					pcData[charIndex] = SwMap::OTHERS;//(bReach << (i%8));
// 				}
		}
		charIndex = dwWidthByteCount*j;
	}

	MarkBorder(dwWidthByteCount,header.height,pcData);
	
	if (!VerifyReachableMap(dwWidthByteCount,header.height,pcData,tile))
	{
		delete [] pcData;
		// 注意关闭文件
		fclose(stream);
		return false;
	}

	fwrite( pcData, sizeof(unsigned char)*dwWidthByteCount * header.height, 1, stream );
	sInt32 offData				= ftell( stream );
	fclose( stream );
	stream = NULL;
	delete [] pcData;
	
	AfxMessageBox("生成寻路地图完成");
	return true;
}

bool CReachableMapGenerate::VerifyReachableMap( sInt32 width,sInt32 height,unsigned char* pData,CWorldTile* tile )
{
	Assert (NULL != tile && tile->GetCResMgr());
	CResEditMgr* presMgr = (CResEditMgr*)tile->GetCResMgr();
	sInt32 nCount = 0;
	std::vector< CTransportResBase* > validTranList;
	for (sInt32 t =0; t < presMgr->GetTransportCount(); ++t)
	{
		CTransportResBase* pres = presMgr->Transport(t);
		sInt32 targetPosX = ZnFloor2Int(pres->GetPosX()/m_interval);
		sInt32 targetPosY = ZnFloor2Int(pres->GetPosY()/m_interval);
		if (!pres->IsTransport())
		{
			CTargetEditRes* pTarget = (CTargetEditRes*)pres;
			if (pTarget->IsRelive())
			{
				continue;
			}
		}
		if( targetPosX >= width || targetPosY >= height )
		{
			CString prompt;
			prompt.Format( _T("传送点超出地图范围，无法参与寻路图计算[X %.1f Y %.1f]"), pres->GetPosX(), pres->GetPosY() );
			::AfxMessageBox( prompt );
			continue;
		}
		if (!IsReachable(targetPosX,targetPosY, width, pData))
		{
			Trace("unreachable transport:%d [%6.2f,%6.2f]!!!!",t,pres->GetPosX(),pres->GetPosY());
			continue;
		}
		validTranList.push_back(pres);
		++nCount;
	}
	if (0 == nCount)
	{
		::AfxMessageBox( _T("该地图不存在合法的出生点或者跳转点!") );
		Trace("no valid transport or target in tile %s!!!!\n",tile->GetPathName());
		return false;
	}
	bool**	transportMap = new bool*[nCount];

	for (sInt32 i = 0; i < nCount; ++i)
	{
		transportMap[i] = new bool[width*height];
	}

	struct NODE {     // node structure
		int x, y;
	};
	NODE *nodelist = new NODE[width*height];    // the node list pointers


	for (sInt32 i = 0; i < nCount; ++i)
	{
		bool* currMap = transportMap[i];
		memset(currMap,0,sizeof(bool)*width*height);
		memset(nodelist,0,sizeof(NODE)*width*height);
		NODE* currNode = &nodelist[0];
		currNode->x = ZnFloor2Int(validTranList[i]->GetPosX()/m_interval);
		currNode->y = ZnFloor2Int(validTranList[i]->GetPosY()/m_interval);
		currMap[currNode->y*width + currNode->x] = true;
		sInt32 nChecked = 0;sInt32 nValid = 1;
		sInt32 x = 0,y = 0;
		do 
		{
			currNode = &nodelist[nChecked];
			//上
			x = currNode->x,y = currNode->y + 1;
			if (y < height)
			{
				if (false == currMap[y*width + x])
				{//check it
					if (IsReachable(x,y,width,pData))
					{
						currMap[y*width + x] = true;
						nodelist[nValid].x = x;
						nodelist[nValid].y = y;
						++nValid;
					}
				}
			}
			//下
			x = currNode->x,y = currNode->y - 1;
			if (y >= 0)
			{
				if (false == currMap[y*width + x])
				{//check it
					if (IsReachable(x,y,width,pData))
					{
						currMap[y*width + x] = true;
						nodelist[nValid].x = x;
						nodelist[nValid].y = y;
						++nValid;
					}
				}
			}
			//左
			x = currNode->x - 1,y = currNode->y ;
			if (x >= 0)
			{
				if (false == currMap[y*width + x])
				{//check it
					if (IsReachable(x,y,width,pData))
					{
						currMap[y*width + x] = true;
						nodelist[nValid].x = x;
						nodelist[nValid].y = y;
						++nValid;
					}
				}
			}
			//右
			x = currNode->x + 1,y = currNode->y ;
			if (x < width)
			{
				if (false == currMap[y*width + x])
				{//check it
					if (IsReachable(x,y,width,pData))
					{
						currMap[y*width + x] = true;
						nodelist[nValid].x = x;
						nodelist[nValid].y = y;
						++nValid;
					}
				}
			}
			++nChecked;
		} while (nChecked != nValid);
	}


	for (DWORD j = 0; j < height; ++j)
	{
		for (DWORD i = 0; i < width; ++i)
		{
			if (!IsReachable(i,j,width,pData))
			{
				continue;
			}
			bool bValid = false;
			for (sInt32 x = 0; x < nCount; ++x)
			{
				bool* currMap = transportMap[x];
				if (currMap[width*j + i])
				{
					bValid = true;
					break;
				}
			}

			if (!bValid)
			{
// 				sInt32 charIndex = (width*j + i) >> 3;
//				char	xx = (~(1 << (i%8)));
// 				pData[charIndex] &= (~(1 << (i%8)));
				sInt32 charIndex = (width*j + i) ;
				pData[charIndex] = 0;
			}

		}
	}

	for (sInt32 x = 0; x < nCount; ++x)
	{
		delete [] transportMap[x];
	}
	delete [] transportMap;
	delete [] nodelist;
	
	return true;
}

bool CReachableMapGenerate::IsReachable( sInt32 posX,sInt32 posY, sInt32 width,const unsigned char* pData )
{
// 	size_t charIndex = (posX + posY*width )>>3;
// 	return	(pData[charIndex] & (1 << (posX%8))) != 0;
	return	(pData[posX + posY*width] ) != 0;

}

//yanli[2010-8-6]-------------------------------------------------------------------------------------
float CReachableMapGenerate::GetZbyXY(flt32 posX, flt32 posY)
{
	sInt32 pickCollisionCount = 0;
	flt32 posDeltaX = posX - 0.25*m_interval;
	flt32 posDeltaY = posY - 0.25*m_interval;
	float maxHeight = 10000;
	std::vector<float> vctHeight;
	vctHeight.push_back(SwGlobal::GetWorldPicker()->GetZByXY(maxHeight, posDeltaX, posDeltaY, 0));

	posDeltaX = posX + 0.25*m_interval;
	posDeltaY = posY - 0.25*m_interval;
	vctHeight.push_back(SwGlobal::GetWorldPicker()->GetZByXY(maxHeight, posDeltaX, posDeltaY, 0));
	
	posDeltaX = posX - 0.25*m_interval;
	posDeltaY = posY + 0.25*m_interval;
	vctHeight.push_back(SwGlobal::GetWorldPicker()->GetZByXY(maxHeight, posDeltaX, posDeltaY, 0));
	
	posDeltaX = posX + 0.25*m_interval;
	posDeltaY = posY + 0.25*m_interval;
	vctHeight.push_back(SwGlobal::GetWorldPicker()->GetZByXY(maxHeight, posDeltaX, posDeltaY, 0));

	std::vector<float>::iterator itBegin = vctHeight.begin();
	std::vector<float>::iterator itEnd = vctHeight.end();
	std::sort(itBegin, itEnd);
	
	//排序完成后通过容差计算高度
	const float zMax = 1.2;
	if (vctHeight[1] - vctHeight[0] > zMax)
	{
		return vctHeight[0];
	}
	else
		if (vctHeight[2] - vctHeight[0] > zMax)
		{
			return (vctHeight[0] + vctHeight[1]) / 2;
		}
		else
			if (vctHeight[3] - vctHeight[0] > zMax)
			{
				return (vctHeight[0] + vctHeight[1] + vctHeight[2]) / 3;
			}
			else
				return (vctHeight[0] + vctHeight[1] + vctHeight[2] + vctHeight[3]) / 4;
}

//-----------------------------------------------------------------
bool CReachableMapGenerate::IsPickObj( flt32 posX, flt32 posY, THeightResult* pheightResult, TPickResult &pickResult )
{
	sInt32 pickCollisionCount = 0;
	flt32 posDeltaX = posX - 0.25*m_interval;
	flt32 posDeltaY = posY - 0.25*m_interval;
	SwGlobal::GetWorldPicker()->SimplePickCollision(posDeltaX,posDeltaY,pheightResult->height+50.f,pickResult);
	if( pickResult.pickResultCount > 0 ) 
	{
// 		for( sInt32 i =0; i< MAX_PICK_OBJ_COUNT; i++ ) 
		{
			if( emPT_FloorObj == pickResult.pickResultInfo[0].resultType ) 
			{
 				++pickCollisionCount;
				return true;
			}
			else if (emPT_CollisionObj == pickResult.pickResultInfo[0].resultType)
			{
				return true;
			}

		}
	}
	 posDeltaX = posX + 0.25*m_interval;
	posDeltaY = posY - 0.25*m_interval;
	SwGlobal::GetWorldPicker()->SimplePickCollision(posDeltaX,posDeltaY,pheightResult->height+50.f,pickResult);
	if( pickResult.pickResultCount > 0 ) 
	{
// 		for( sInt32 i =0; i< MAX_PICK_OBJ_COUNT; i++ ) 
		{
			if( emPT_FloorObj == pickResult.pickResultInfo[0].resultType ) 
			{
				++pickCollisionCount;
			}
			else if (emPT_CollisionObj == pickResult.pickResultInfo[0].resultType)
			{
				return true;
			}

		}
	}
	posDeltaX = posX - 0.25*m_interval;
	posDeltaY = posY + 0.25*m_interval;
	SwGlobal::GetWorldPicker()->SimplePickCollision(posDeltaX,posDeltaY,pheightResult->height+50.f,pickResult);
	if( pickResult.pickResultCount > 0 ) 
	{
// 		for( sInt32 i =0; i< MAX_PICK_OBJ_COUNT; i++ ) 
		{
			if( emPT_FloorObj == pickResult.pickResultInfo[0].resultType ) 
			{
				++pickCollisionCount;
			}
			else if (emPT_CollisionObj == pickResult.pickResultInfo[0].resultType)
			{
				return true;
			}

		}
	}
	posDeltaX = posX + 0.25*m_interval;
	posDeltaY = posY + 0.25*m_interval;
	SwGlobal::GetWorldPicker()->SimplePickCollision(posDeltaX,posDeltaY,pheightResult->height+50.f,pickResult);
	if( pickResult.pickResultCount > 0 ) 
	{
// 		for( sInt32 i =0; i< MAX_PICK_OBJ_COUNT; i++ ) 
		{
			if( emPT_FloorObj == pickResult.pickResultInfo[0].resultType ) 
			{
				++pickCollisionCount;
			}
			else if (emPT_CollisionObj == pickResult.pickResultInfo[0].resultType)
			{
				return true;
			}

		}
	}
	if (pickCollisionCount == 4)
	{
		return true;
	}
	return false;
}

bool CReachableMapGenerate::ReadInReachableData( CWorldTile* pTile )
{
	if (NULL == pTile)
	{
		return NULL;
	}
	char gameMapPath[MAX_PATH];
	GetGameWtdFileName(pTile->GetPathName(),gameMapPath);
	char* pFind = strstr(gameMapPath,".mew");
	pFind[1] = 'm';
	pFind[2] = 'a';
	pFind[3] = 'p';

	if (pTile->ReachableMap().Create(gameMapPath,false))
	{
		return true;
	}
	else
	{
		::AfxMessageBox( _T("不能加载该地图的寻路地图，请使用world页面tile浏览的右键弹出菜单里的‘导出可到达地图’生成该地图!") );
		Trace( "failed open ReachableMap:[ %s ] \n", pTile->GetPathName() );
	}
	return false;
// 	FILE* stream = NULL;
// 	try	{
// 		stream = fopen( gameMapPath, "rb" );
// 		CheckThrow( stream != NULL );

// 		return pTile->ReachableMap().Create(gameMapPath);
// 		if( fopen_s( &stream, gameMapPath, "rb" ) != 0 ) 
// 		{
// 			throw( "error open file !" );
// 		}
// 		MapHeader header;
// 		fread(&header,sizeof( MapHeader ),1,stream);
// 
// 		unsigned char* retData = new unsigned char[ header.width * header.height];
// 		if (header.version < 3)
// 		{
// 			DWORD  dwWidthByteCount = ( header.width + 7) >> 3;
// 			unsigned char* retTempData = new unsigned char[ dwWidthByteCount * header.height];
// 			fread(retData,sizeof(unsigned char)*dwWidthByteCount * header.height,1,stream);
// 
// 			for (int i = 0; i <  header.height; i++)
// 			{
// 				for (int j = 0; j < header.width; j++)
// 				{
// 					retTempData[i * header.width + j] = (retTempData[i * dwWidthByteCount + j] & (1 << (j%8))) ? SwMap::OTHERS: 0;
// 				}
// 			}
// 		}
// 		else
// 		{
// 			DWORD  dwWidthByteCount = header.width;;
// 			fread(retData,sizeof(unsigned char)*dwWidthByteCount * header.height,1,stream);
// 		}
// 		fclose( stream );
// 		stream = NULL;
// 		return retData;
// 	}
// 	catch( const char* s )
// 	{
// 		::AfxMessageBox( _T("不能加载该地图的可到达地图，请使用world页面tile浏览的右键弹出菜单里的‘导出可到达地图’生成该地图!") );
// 		Trace( "failed open ReachableMap:[ %s ] \n", pTile->GetPathName() );
// 	}
// 	return false;
}

void CReachableMapGenerate::MarkBorder( sInt32 width,sInt32 height,unsigned char* pData )
{
	for (int i = 0; i < height; ++i)
	{
		for(int j = 0; j < width; ++j)
		{
			if (pData[j + i* width] != SwMap::UNREACHABLE)
			{
				bool bLeft = false;
				bool bLeftUp = false;
				bool bLeftDown = false;
				bool bUp = false;
				//判断周边八方向
				if (j > 0 )
				{
					if (pData[j - 1 + i* width] == SwMap::UNREACHABLE)
					{
						bLeft = true;
					}
					if (i > 0)
					{
						if (pData[j - 1 + (i- 1)* width] == SwMap::UNREACHABLE)
						{
							bLeftDown = true;
						}
					}
					if (i < height - 1)
					{
						if (pData[j - 1 + (i + 1)* width] == SwMap::UNREACHABLE)
						{
							bLeftUp = true;
						}
					}
				}
				if (i > 0)
				{
					if (pData[j + (i- 1)* width] == SwMap::UNREACHABLE)
					{
						bUp = true;
					}
				}
				if (i < height - 1)
				{
					if (pData[j + (i + 1)* width] == SwMap::UNREACHABLE)
					{
						if (bUp)
						{
							pData[j + i* width] = SwMap::UNREACHABLE;
							continue;
						}
						else
						{
							bUp = true;
						}
					}
				}
				if (j < width - 1 )
				{
					if (pData[j + 1 + i* width] == SwMap::UNREACHABLE)
					{
						if (bLeft)
						{
							pData[j + i* width] = SwMap::UNREACHABLE;
							continue;
						}
						else
						{
							bLeft = true;
						}
					}
					if (i > 0)
					{
						if (pData[j + 1 + (i- 1)* width] == SwMap::UNREACHABLE)
						{
							if (bLeftUp)
							{
								pData[j + i* width] = SwMap::UNREACHABLE;
								continue;
							}
							else
							{
								bLeftUp = true;
							}
						}
					}
					if (i < height - 1)
					{
						if (pData[j + 1 + (i + 1)* width] == SwMap::UNREACHABLE)
						{
							if (bLeftDown)
							{
								pData[j + i* width] = SwMap::UNREACHABLE;
								continue;
							}
							else
							{
								bLeftDown = true;
							}
						}
					}
				}
				if (bLeft || bLeftDown || bLeftUp || bUp)
				{
					pData[j + i* width] = SwMap::CORNER_AREA;
				}
			}
		}
	}
}

bool CReachableMapGenerate::GenerateWaterMap( sInt32 tileId,sInt32 mapScale,const char* fileName )
{
	CWorld* pWorld = SwGlobal::GetWorld();
	CWorldTile* tile = pWorld->GetWorldBuffer()->GetTile( tileId);
	if( NULL == tile )
		return false;

	if( !tile->IsLoad() )
		return false;

	m_interval = WORLD_CHUNKSIZE/(float)mapScale;

	CWorldWriteStream writeStream(SwGlobal::GetWorld());
	if (!writeStream.RemoveReadOnly(fileName))
	{
		return false;
	}
	FILE* stream = NULL;
	try	{
		if( fopen_s( &stream, fileName, "wb" ) != 0 ) 
		{
			throw( "error open file !" );
		}
		TileDataMapHeader header;
		memset( &header, 0, sizeof(TileDataMapHeader) );
		header.version = SwMap::MAPVRSION;
		header.rate_R = WORLD_CHUNKSIZE;
		header.rate_M = mapScale;
		header.width = tile->GetRowColumn()[0]*WORLD_CHUNKSIZE*(header.rate_M/header.rate_R);
		header.height = tile->GetRowColumn()[1]*WORLD_CHUNKSIZE*(header.rate_M/header.rate_R);
		header.size = header.width*header.height;


		fwrite( &header, sizeof( TileDataMapHeader ), 1, stream );
		sInt32 offHead				= ftell( stream );

		DWORD  dwWidthByteCount = ( header.width + 7) >> 3;
		unsigned char* pcData = new unsigned char[ dwWidthByteCount * header.height];
		memset(pcData,0,sizeof(unsigned char)*dwWidthByteCount * header.height);
		flt32 posx = 0.f,posy= 0.f;
		size_t charIndex = 0;
		for (DWORD j = 0; j < header.height; ++j)
		{
			posy = (j +0.5f)* m_interval ;
			for (DWORD i = 0; i < header.width; ++i)
			{
				posx = (i+0.5f) * m_interval;
				if (IsRealPosWater(posx,posy))
				{
					charIndex = dwWidthByteCount*j + (i >> 3);
					pcData[charIndex] |= (1 << (7 - i%8));
				}
			}
			charIndex = dwWidthByteCount*j;
		}

		fwrite( pcData, sizeof(unsigned char)*dwWidthByteCount * header.height, 1, stream );
		fclose( stream );
		stream = NULL;
		delete [] pcData;

	}
	catch( const char* s )
	{
		Trace( "failed write WaterMap:[ %s ] \n", s );
		if( NULL != stream )
		{
			fclose( stream );
			stream	= NULL;
		}
		return false;
	}
	return true;

}

char CReachableMapGenerate::IsRealPosWater( flt32 posX, flt32 posY )
{
		static THeightResult heightResult;

		if(!SwGlobal::GetWorldPicker()->GetHeight(posX,posY,heightResult))
		{
			return false;
		}


	static TPickResult pickResult;
	if (IsPickObj(posX, posY, &heightResult, pickResult))
	{
		if( emPT_FloorObj == pickResult.pickResultInfo[0].resultType ) 
		{
			return false;
		}
	}


	return heightResult.isInLiquid;

}

bool CReachableMapGenerate::IsErrorSlope( CWorldChunk* chunk )
{
	for(std::vector<CWorldChunk*>::iterator iter = m_SlopeCheckChunkArr.begin(); iter != m_SlopeCheckChunkArr.end(); ++iter)
	{
		if (*iter == chunk)
		{
			return true;
		}
	}
	return false;
}

void CReachableMapGenerate::SlopeCheck()
{
	m_SlopeCheckChunkArr.clear();

	CWorld* pWorld = SwGlobal::GetWorld();
	CWorldTile* tile = pWorld->GetWorldBuffer()->GetActiveTile( );
	if( NULL == tile )
		return ;

	if( !tile->IsLoad() )
		return ;

	m_interval = WORLD_CHUNKSIZE/(float)g_reachableMapScale;

	int width = tile->GetRowColumn()[0]*WORLD_CHUNKSIZE*2;
	int height = tile->GetRowColumn()[1]*WORLD_CHUNKSIZE*2;

	flt32 posx = 0.f,posy= 0.f;
	for (DWORD j = 0; j < height; ++j)
	{
		posy = (j +0.5f)* m_interval ;
		for (DWORD i = 0; i < width; ++i)
		{
			posx = (i+0.5f) * m_interval;
			CWorldChunk* chunk = tile->GetChunkFromPos(posx,posy);
			if (chunk && !IsErrorSlope(chunk))
			{
				bool bSlopeCheck = false;
				if((0 == IsRealPosReachable(posx,posy,tile->GetReachableAngle()*PIOVER180,NULL,&bSlopeCheck)) && bSlopeCheck)
				{
					m_SlopeCheckChunkArr.push_back(chunk);
				}
			}
		}
	}

}

void CReachableMapGenerate::ClearSlopeCheck()
{
	m_SlopeCheckChunkArr.clear();
}