/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	SwMap.cpp
* Create: 	10/14/06
* Desc:		地图类，存储地图逻辑数据
* Author:	HuangYue
*
* Modify:	增加地图数据结构和寻路算法, 10/28/2008
* Modify by: Qiu Li
*******************************************************************************/

#include "MeTerrain/stdafx.h"
#include "MeTerrain/SwType.h"
#include <vector>
#include "MeTerrain/SwMap.h"
//#include "atltypes.h"
#include "MeTerrain/BinaryAStarPF.h"
#include "Launcher/DataLauncher.h"
SwMap::SwMap()
{
	m_nWidth		= 0;
	m_nHeight		= 0;
	m_pkPathFinder	= NULL;
	m_pkMapData		= NULL;
}

SwMap::~SwMap()
{
	Destroy();
}

bool SwMap::Create(const char* pszMapName,bool isFreeData)
{
	// 先确定MAP的大小

	if( !ReadInReachableData(pszMapName) )
	{
		FreeMapData();
		return false;
	}

	
	// 创建BYTE地图数据，生成寻路地图
// 	BYTE *pbOrgMap = MeDefaultNew BYTE[m_nWidth * m_nHeight];
// 	int id = 0;
// 	for(int y = 0; y < m_nHeight; ++y)
// 	{
// 		for(int x = 0; x < m_nWidth; ++x)
// 		{
// 			pbOrgMap[id] = (BYTE)m_pkMapData[y*m_nWidth + x];
// 			++id;
// 		}
// 	}
	if( m_pkPathFinder )
	{
		delete m_pkPathFinder;
	}

	m_pkPathFinder = new BinaryAStarPF(m_pkMapData, m_nWidth, m_nHeight);
	if (isFreeData)
	{
		FreeMapData();
	}

//  	delete []pbOrgMap;
	return true;
}

float SwMap::GetMapRate()
{
	return m_fRate;
}

void SwMap::Destroy()
{
	if( m_pkPathFinder )
	{
		delete m_pkPathFinder;
		m_pkPathFinder = NULL;
	}
	
	FreeMapData();
}

bool SwMap::CanMove(const swVec2f& kOrgPosition, const swVec2f& kDestPosition, swVec2f* kCollisionPosition)
{
	if( !m_pkPathFinder )
		return true;

	// 如果destPosition和orgPosition在同个或相邻格子内，则直接取目标点是否可到达
	swVec2I orgPos;
	orgPos.x = GameCoordToMap(kOrgPosition.x);
	orgPos.y = GameCoordToMap(kOrgPosition.y);
	if(orgPos.x < 0 || orgPos.x > m_pkPathFinder->GetMapWidth() 
		||orgPos.y < 0 || orgPos.y > m_pkPathFinder->GetMapHeight())
	{
		return false;
	}
	swVec2I destPos;
	destPos.x = GameCoordToMap(kDestPosition.x);
	destPos.y = GameCoordToMap(kDestPosition.y);
	if(destPos.x < 0 || destPos.x > m_pkPathFinder->GetMapWidth() 
		||destPos.y < 0 || destPos.y > m_pkPathFinder->GetMapHeight())
	{
		return false;
	}
	swVec2I kDeltaMove;
 	kDeltaMove.x = abs(orgPos.x - destPos.x);
 	kDeltaMove.y = abs(orgPos.y - destPos.y);
	if( kDeltaMove.x == 0 && kDeltaMove.y == 0 )
	{
		// 相同格子内
		return true;
	}
	else if( kDeltaMove.x <= 1 && kDeltaMove.y <= 1 )
	{
		// 相邻格子，直接判断目标点是否可站立
		if(!m_pkPathFinder->IsReachable(destPos.x,destPos.y) )
		{
			// 可到达的点设为起始位置
			if (kCollisionPosition)
			{
				*kCollisionPosition = kOrgPosition;
			}
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		if (m_pkPathFinder->ValidLine(orgPos,destPos,kCollisionPosition))
		{
			return true;
		}
		else
		{
			if (kCollisionPosition)
			{
				kCollisionPosition->x = GameMapMiddleToCoord(kCollisionPosition->x);
				kCollisionPosition->y = GameMapMiddleToCoord(kCollisionPosition->y);
				char str[128];
				sprintf( str, "Map Return Position: %f %f\n", kCollisionPosition->x, kCollisionPosition->y);
				OutputDebugStringA( str);
			}
			return false;
		}
	}
}

bool SwMap::FindPath(const swVec2f& kStartPosition, const swVec2f& kEndPosition, std::vector<swVec2f>& vecBestPath)
{
	if (!m_pkPathFinder)
	{
		return false;
	}

	swVec2I kStart, kEnd;
	kStart.x	= GameCoordToMap(kStartPosition.x);
	kStart.y	= GameCoordToMap(kStartPosition.y);
	if(kStart.x < 0 || kStart.x > m_pkPathFinder->GetMapWidth() 
		||kStart.y < 0 || kStart.y > m_pkPathFinder->GetMapHeight())
	{
		return false;
	}
	kEnd.x		= GameCoordToMap(kEndPosition.x);
	kEnd.y		= GameCoordToMap(kEndPosition.y);
	if(kEnd.x < 0 || kEnd.x > m_pkPathFinder->GetMapWidth() 
		||kEnd.y < 0 || kEnd.y > m_pkPathFinder->GetMapHeight())
	{
		return false;
	}

	return FindPath(kStart, kEnd, vecBestPath);
}

// private
bool SwMap::FindPath(const swVec2I& kStartPosition, const swVec2I& kEndPosition, std::vector<swVec2f>& vecBestPath)
{
	vecBestPath.clear();	// 最优路线清空

	if( m_pkPathFinder && m_pkPathFinder->NewPath(kStartPosition.x, kStartPosition.y, kEndPosition.x, kEndPosition.y) )
	{
// 		swVec2f kNewPoint;
// 		kNewPoint.x = 0.f;
// 		kNewPoint.y = 0.f;
		// 先压入终点
		//kNewPoint.x = GameMapMiddleToCoord(kEndPosition.x);
		//kNewPoint.y = GameMapMiddleToCoord(kEndPosition.y);
// 		vecBestPath.insert(vecBestPath.begin(), swVec2f(0.f,0.f));
// 		vecBestPath.push_back(kNewPoint);

		//Trace("point %.3f, %.3f\n",newPoint.x, newPoint.y);
//		std::vector <swVec2I> vecAStarPath;		// 路线
		std::vector <swVec2I>& vecPath  = m_pkPathFinder->GetPath();		// 路线

		for (int i = 0; i < (int)vecPath.size();++i)
		{
			vecBestPath.push_back(swVec2f(
				GameMapMiddleToCoord(vecPath[i].x),
				GameMapMiddleToCoord(vecPath[i].y)
				));
		}
// 		while( !m_pkPathFinder->ReachedGoal() )
// 		{
// 			m_pkPathFinder->PathNextNode();   // point to next node = next tile on path
// 			kNewPoint.x = GameMapMiddleToCoord(m_pkPathFinder->NodeGetX());  // get the positions from current node
// 			kNewPoint.y = GameMapMiddleToCoord(m_pkPathFinder->NodeGetY());  // and set the MeNew destination
// 			//vecBestPath.insert(vecBestPath.begin(), kNewPoint);
// 			vecBestPath.push_back(kNewPoint);
// 			//Trace("point %.3f, %.3f\n",newPoint.x, newPoint.y);
// 		}
		return true;
	}
	else
		return false;
}

bool SwMap::CanReach( const swVec2f& kPosition )
{
	if( !m_pkPathFinder )
		return false;
	int x = GameCoordToMap(kPosition.x);
	int y = GameCoordToMap(kPosition.y);
	if ((x < 0.f )|| (x > m_nWidth - 1) || (y < 0.f) || (y > m_nHeight - 1))
	{
		return false;
	}
	return m_pkPathFinder->IsReachable(x,y);
}

bool SwMap::SameMapGrid( const swVec2f& kPosition1, const swVec2f& kPosition2 )
{

	return ( GameCoordToMap(kPosition1.x) == GameCoordToMap(kPosition2.x)
		  && GameCoordToMap(kPosition1.y) == GameCoordToMap(kPosition2.y) );
}


int SwMap::CalPFWeight( float startx,float starty,float endx,float endy ) 
{
	swVec2f kOrgPosition(startx,starty);
	swVec2f kDestPosition(endx,endy);
	if (CanMove(kOrgPosition,kDestPosition))
	{
		return (int)(sqrt((startx-endx)*(startx-endx) + (starty-endy)*(starty-endy)));
	}
	std::vector<swVec2f> vecBestPath;
	if (FindPath(kOrgPosition,kDestPosition,vecBestPath))
	{
		float ret = 0;
		for (int i = 1; i < vecBestPath.size(); ++i)
		{
			ret += sqrt((vecBestPath[i].x-vecBestPath[i - 1].x)*(vecBestPath[i].x-vecBestPath[i - 1].x) 
				+ (vecBestPath[i].y-vecBestPath[i - 1].y)*(vecBestPath[i].y-vecBestPath[i - 1].y));
		}
		return (int)(ret);
	}
	return -1;
}

void SwMap::AddBlockPoint( float x,float y )
{
	if( !m_pkPathFinder )
		return ;
	int posx = GameCoordToMap(x);
	int posy = GameCoordToMap(y);
	if(m_pkPathFinder->IsReachable(posx,posy))
	{
		m_pkPathFinder->ToggleTile(posx,posy);
	}

}

void SwMap::FreeMapData()
{
	if( m_pkMapData != NULL)
	{
		delete[]m_pkMapData;
		m_pkMapData = NULL;
	}
}

bool SwMap::ReadInReachableData( const char* pszFileName )
{
	DWORD dwWidthByteCount = 0;
// 	BOOL bReadMapSuccess = FALSE;

	FILE* stream = fopen( pszFileName, "rb");
	TileDataMapHeader mapHeader;
	if( stream != NULL)
	{
		fread(&mapHeader,sizeof( TileDataMapHeader ),1,stream);

		dwWidthByteCount = mapHeader.width;
		m_nWidth = mapHeader.width;
		m_nHeight = mapHeader.height;
		int nRateM = mapHeader.rate_M;
		int nRateR = mapHeader.rate_R;
		m_fRate = (float)nRateR / (float)nRateM;
		m_pkMapData = MeDefaultNew unsigned char[ mapHeader.width * mapHeader.height];
		if (mapHeader.version < 3)
		{
			DWORD  dwWidthByteCount = ( mapHeader.width + 7) >> 3;
			unsigned char* retTempData = MeDefaultNew unsigned char[ dwWidthByteCount * mapHeader.height];
			fread(retTempData,sizeof(unsigned char)*dwWidthByteCount * mapHeader.height,1,stream);

			for (int i = 0; i <  mapHeader.height; i++)
			{
				for (int j = 0; j < mapHeader.width; j++)
				{
					m_pkMapData[i * mapHeader.width + j] = (retTempData[i * dwWidthByteCount + j] & (1 << (j%8))) ? OTHERS: 0;
				}
			}
			delete [] retTempData;
		}
		else
		{
			DWORD  dwWidthByteCount = mapHeader.width;;
			fread(m_pkMapData,sizeof(unsigned char)*dwWidthByteCount * mapHeader.height,1,stream);
		}
		fclose( stream);
		return true;
	}
	return false;

}

bool SwMap::GetReachablePosToDest( const swVec2f& kOrgPosition, const swVec2f& kDestPosition, swVec2f* kReachablePosition )
{
	if( !m_pkPathFinder )
		return true;

	// 如果destPosition和orgPosition在同个或相邻格子内，则直接取目标点是否可到达
	swVec2I orgPos;
	orgPos.x = GameCoordToMap(kOrgPosition.x);
	orgPos.y = GameCoordToMap(kOrgPosition.y);
	if(orgPos.x < 0 || orgPos.x > m_pkPathFinder->GetMapWidth() 
		||orgPos.y < 0 || orgPos.y > m_pkPathFinder->GetMapHeight())
	{
		return false;
	}
	swVec2I destPos;
	destPos.x = GameCoordToMap(kDestPosition.x);
	destPos.y = GameCoordToMap(kDestPosition.y);
	if(destPos.x < 0 || destPos.x > m_pkPathFinder->GetMapWidth() 
		||destPos.y < 0 || destPos.y > m_pkPathFinder->GetMapHeight())
	{
		return false;
	}
	if(m_pkPathFinder->IsReachable(destPos.x,destPos.y) )
	{
		//目标点可走则直接返回
		if (kReachablePosition)
		{
			*kReachablePosition = kOrgPosition;
		}
		return true;
	}
	swVec2I kDeltaMove;
	kDeltaMove.x = abs(orgPos.x - destPos.x);
	kDeltaMove.y = abs(orgPos.y - destPos.y);
	if( kDeltaMove.x == 0 && kDeltaMove.y == 0 )
	{
		if(kReachablePosition)
		{
			*kReachablePosition = kDestPosition;
		}
		// 相同格子内
		return true;
	}

	else if( kDeltaMove.x <= 1 && kDeltaMove.y <= 1 )
	{
		// 相邻格子，直接判断目标点是否可站立
		if(kReachablePosition)
		{
			*kReachablePosition = kDestPosition;
		}
		// 相同格子内
		return true;
	}
	else
	{
		if (m_pkPathFinder->FindReachablePosOnLine(destPos,orgPos,kReachablePosition))
		{
			kReachablePosition->x = GameMapMiddleToCoord(kReachablePosition->x);
			kReachablePosition->y = GameMapMiddleToCoord(kReachablePosition->y);
			if (kReachablePosition)
			{
				char str[128];
				sprintf( str, "Map Reachable Position: %f %f\n", kReachablePosition->x, kReachablePosition->y);
				OutputDebugStringA( str);
			}
			return true;
		}
		else
		{
			return false;
		}
	}

}
