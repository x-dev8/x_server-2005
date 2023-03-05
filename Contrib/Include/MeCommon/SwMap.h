/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	SwMap.h
* Create: 	10/14/06
* Desc:		地图类，存储地图逻辑数据
* Author:	HuangYue
*
* Modify:
* Modify by:
*******************************************************************************/

/*
自动寻路步骤：
1. 先尝试直线行走，如果可行则完成寻路
2. 接着尝试水平或垂直方向行走，记录下每一个转向点
3. 每次转向后都要尝试一下直接走到最终目标点！！
4. 用开始点和每一个转向点做连接，判断可行性，找出最短路径
5. 记下结果，开始让角色行走

完成后依次测试以下几种情况
1. 无任何障碍
2. 矩形障碍
3. 多矩形连接障碍
4. 球形障碍
5. 不规则形状障碍
*/

#ifndef __SW_MAP_H__
#define __SW_MAP_H__
#include "BinaryAStarPF.h"
//class AStarPathFinder;
class BinaryAStarPF;
class SwMap
{
public:
							SwMap();
							~SwMap();

	enum TerrainPowerType
	{
		UNREACHABLE = 0,
		MAIN_ROAD	= 10,
		MAIN_ROAD_DIAGONAL	= 14,
		SUB_ROAD	= 12,
		SUB_ROAD_DIAGONAL	= 17,
		OTHERS		= 20,
		OTHERS_DIAGONAL		= 28,
		CORNER_AREA		= 30,
		CORNER_AREA_DIAGONAL		= 40
	};
	static const int MAPVRSION = 3;

	bool					ReadInReachableData(const char* pszMapName);
	bool					Create(const char* pszMapName,bool isFreeData = true);
	bool					Create( const SwMap& templateMap );

	void					FreeMapData();
	float					GetMapRate();
	void					Destroy();
																				// 判断从orgPosition到destPosition是否能走
																				// 如果不能走，则返回离出发位置最近的位置collisionPosition
	bool					CanMove(const swVec2f& kOrgPosition, const swVec2f& kDestPosition, swVec2f* kCollisionPosition = NULL);	
																				//根据出发点和目标点之间的连线寻找离目标点最近的可到达点
	bool					GetReachablePosToDest(const swVec2f& kOrgPosition, const swVec2f& kDestPosition, swVec2f* kReachablePosition);	
																				// 寻路算法，如果能寻到路，则返回最优路径vecBestPath，begin()是起始点，end()为终点
	bool					FindPath(const swVec2f& kStartPosition, const swVec2f& kEndPosition, std::vector<swVec2f>& vecBestPath);
																				// 判断kPosition是否能到达
	bool					CanReach(const swVec2f& kPosition);
																				// 判断kPosition1和kPosition2在同个地图格子里
	bool					SameMapGrid(const swVec2f& kPosition1, const swVec2f& kPosition2);

	int						CalPFWeight(float startx,float starty,float endx,float endy);

	void					AddBlockPoint(float x,float y);
	void					DelBlockPoint(float x,float y);
	int						GameCoordToMap( float x) { return (int)( x/m_fRate);}
	float					GameMapMiddleToCoord( int x) { return (float)( x*m_fRate + 0.5f*m_fRate);}
	unsigned char*			GetMapData() const { return m_pkMapData; }
	bool					GetUseWeight() const { return m_pkPathFinder->GetUseWeight(); }
	void					SetUseWeight(bool val) { m_pkPathFinder->SetUseWeight( val ); }
private:
	bool					FindPath(const swVec2I& kStartPosition, const swVec2I& kEndPosition, std::vector<swVec2f>& vecBestPath);

private:
	int						m_nWidth;		// 地图的宽度
	int						m_nHeight;		// 地图的高度
	float					m_fRate;		// 地图的缩放比率

	//AStarPathFinder*		m_pkPathFinder;	// 寻路算法
	BinaryAStarPF*		m_pkPathFinder;	// 寻路算法

	unsigned char*		m_pkMapData;			//Map中间数据
};



#endif