#pragma once
#include <Windows.h>
#include <deque>
#include "Dxsdk/D3DX9Math.h"
#include "GlobalDef.h"

class CCameraStuntManager
{
public:
	CCameraStuntManager(void);
	~CCameraStuntManager(void);

public:
	enum LookatPosOffsetType
	{
		LPOT_NORMAL = 0,
		LPOT_HORIZONTAL,
		LPOT_VERTICAL,
		LPOT_VIEWDIR //延方向运行
	};

private:
	D3DXVECTOR3		m_vTheRolePos;					//游戏里主角的坐标
	D3DXVECTOR3     m_vViewDir;                     //游戏中的观察方向
	float           m_fDistance;                    //相机离角色的距离
	float           m_fLastDistance;                //上次相机离角色的距离
	DWORD           m_dwStartMovingCameraTime;      //开始移动相机的时间
	DWORD           m_dwMovingElapse;               //移动间隔

public:
	void			UpdateRolePos( D3DXVECTOR3 vRolePos,D3DXVECTOR3 vDir);
	void            RecordLastDistance(float fLen){m_fLastDistance = fLen;}
	void            ProcessSmothMove(float &fLen);
	int             GetDistance(){return m_fDistance;}
	int             GetLookType(){return m_nLookatPosOffsetType;}
	bool            IsCameraMoving();

private:
	int				m_nLookatPosOffsetType;			//观看点偏移类型
	float			m_fLookatPosMaxOffset;			//观看点的最大偏移
	float			m_fLookatPosMinOffset;			//观看点的最小偏移
	float			m_fLookatPosShakeCorrect;		//观看点的振动修正
	DWORD			m_dwLookatPosStartShakeTime;	//观看点开始振动的时间
	DWORD			m_dwLookatPosShakeKeepTime;		//观看点振动的维持时间

public:
	//得到观看点的偏移
	D3DXVECTOR3		GetLookatPosOffset();

	//开始随机震动
	void			StartRandShake( D3DXVECTOR3 vShakePos,		//震动点
		float fMaxShakeWaveRange,	//振波影响最弱的范围
		float fMinShakeWaveRange,	//振波影响最强的范围
		float fMaxShakeRange,		//最大振幅
		float fMinShakeRange,		//最小振幅
		DWORD dwShakeKeepTime,		//振动维持时间
		int	  nShakeType = LPOT_NORMAL,int nCurZoom = 0 );//振动类型

	void			StartRandShake(	float fMaxShakeRange,		//最大振幅
		float fMinShakeRange,		//最小振幅
		DWORD dwShakeKeepTime,		//振动维持时间
		int	  nShakeType = LPOT_NORMAL,int nCurZoom = 0 );//振动类型
};