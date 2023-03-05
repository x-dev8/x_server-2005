/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	SwMap.h
* Create: 	10/14/06
* Desc:		��ͼ�࣬�洢��ͼ�߼�����
* Author:	HuangYue
*
* Modify:
* Modify by:
*******************************************************************************/

/*
�Զ�Ѱ·���裺
1. �ȳ���ֱ�����ߣ�������������Ѱ·
2. ���ų���ˮƽ��ֱ�������ߣ���¼��ÿһ��ת���
3. ÿ��ת���Ҫ����һ��ֱ���ߵ�����Ŀ��㣡��
4. �ÿ�ʼ���ÿһ��ת��������ӣ��жϿ����ԣ��ҳ����·��
5. ���½������ʼ�ý�ɫ����

��ɺ����β������¼������
1. ���κ��ϰ�
2. �����ϰ�
3. ����������ϰ�
4. �����ϰ�
5. ��������״�ϰ�
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
																				// �жϴ�orgPosition��destPosition�Ƿ�����
																				// ��������ߣ��򷵻������λ�������λ��collisionPosition
	bool					CanMove(const swVec2f& kOrgPosition, const swVec2f& kDestPosition, swVec2f* kCollisionPosition = NULL);	
																				//���ݳ������Ŀ���֮�������Ѱ����Ŀ�������Ŀɵ����
	bool					GetReachablePosToDest(const swVec2f& kOrgPosition, const swVec2f& kDestPosition, swVec2f* kReachablePosition);	
																				// Ѱ·�㷨�������Ѱ��·���򷵻�����·��vecBestPath��begin()����ʼ�㣬end()Ϊ�յ�
	bool					FindPath(const swVec2f& kStartPosition, const swVec2f& kEndPosition, std::vector<swVec2f>& vecBestPath);
																				// �ж�kPosition�Ƿ��ܵ���
	bool					CanReach(const swVec2f& kPosition);
																				// �ж�kPosition1��kPosition2��ͬ����ͼ������
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
	int						m_nWidth;		// ��ͼ�Ŀ��
	int						m_nHeight;		// ��ͼ�ĸ߶�
	float					m_fRate;		// ��ͼ�����ű���

	//AStarPathFinder*		m_pkPathFinder;	// Ѱ·�㷨
	BinaryAStarPF*		m_pkPathFinder;	// Ѱ·�㷨

	unsigned char*		m_pkMapData;			//Map�м�����
};



#endif