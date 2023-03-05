/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	CrossMapPF.h
* Create: 	10/14/06
* Desc:		跨地图寻路类
* Author:	yuanding
*
* Modify:
* Modify by:
*******************************************************************************/

/*
自动寻路步骤:

完成后依次测试以下几种情况
*/

#ifndef __CROSS_MAP_PF_H__
#define __CROSS_MAP_PF_H__
#include "Singleton.h"

class CTransportResBase;
class CrossMapPF : public Singleton<CrossMapPF>
{
public:
							CrossMapPF();
							~CrossMapPF();
	void					Reset();
	bool					CrossMapFindPath(int startMapId,float startx,float starty,int endMapId,float endx,float endy/*,int nType = NULL*/);
	bool					CrossMapPathEvaluation(int startMapId,int endMapId,int& nPathLength);
	bool					UpdateAfterTileLoad();
	int						GetMapLevel(int MapId);
	//void                    SetActive(bool bActive){m_bActive = bActive;}
private:
	bool					GetValidPathWeight(float  weight,std::vector<CTransportResBase*>&	TransportArr,std::vector<int>&	CrossMapIdArr);
	int						m_nMapCross;
	std::vector<CTransportResBase*>			mTransportArr;
	bool					m_bActive;		//是否处于激活状态，如果是，需要在地图加载的时候进行寻路
	float					mfMinWeight;
	int						m_nMinMapCross;
	int						m_nEndMapId;
	int						m_nPlayerLevel;
	float					m_endx;
	float					m_endy;
};



#endif