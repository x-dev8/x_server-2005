/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	CPathDirection.h
* Create: 	10/14/06
* Desc:		地图寻路路标显示类
* Author:	yuanding
*
* Modify:
* Modify by:
*******************************************************************************/


#ifndef __PATH_DIRECTION_H__
#define __PATH_DIRECTION_H__
#include "Singleton.h"
class CWSModelEffect;
class CCharEffectContainer;
class CPathDirection : public Singleton<CPathDirection>
{
public:
							CPathDirection();
							~CPathDirection();
	void					Reset();
	void					CreateEffectArr(const std::vector<swVec2f>& path);
	int						GetDecalSize() const { return mDecalArr.size(); }
	bool					IsActive(){return m_bActive;}
	bool					UpdatePathDirection();
	bool					SetEffectInstance(D3DXVECTOR3& pos,swVec2f& dir);
	int						GetPathDirBegin(){return m_movingStep;}
	int						GetPathDirEnd(){return m_effectNum;}
	void					GetDirectionPos(int index,float& posx,float& posy);
	bool					IsVisible() const { return m_visible; }
	void					SetVisible(bool val);
	const	static	int			MinPathLenghtForDirection = 30.f;
private:
	struct SPathEffect{
		SPathEffect()
			:m_effect(NULL)
			,nEffectContainerID(-1)
		{}
		CWSModelEffect*			m_effect;
		int nEffectContainerID;
	};
	SPathEffect			CreateEffect();
	std::vector<SPathEffect>				mDecalArr;
	std::vector<swVec2f>				mVecArr;
	int									m_effectNum;
	bool								m_bActive;
	float								m_fMaxStep;
	float								m_fMinStep;
	int									m_movingStep;
	bool								m_visible;
};



#endif