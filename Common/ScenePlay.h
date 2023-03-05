#pragma once
#include <vector>

struct Segment
{
	std::string strAnimBegin;  //说话时候的开始动作
	std::string strAnimEnd;    //说话时候的结束动作
	int         nTalkId;   //角色说话的 字符串id ，从string.config 中读取
	std::string strTrack; // 摄像机的 需要播放动作的名字
	std::string strMountAnimBegin; //说话时候在坐骑上的开始动作
	std::string strMountAnimEnd;   //说话时候在坐骑上的结束动作

	Segment()
	{
		strAnimBegin.clear();
		strAnimEnd.clear();
		nTalkId = -1;
		strTrack.clear();
		strMountAnimBegin.clear();
		strMountAnimEnd.clear();
	}
};

struct ElapseTime
{
	int nId;    //当期阶段的id
	int nTime;  //当前阶段需要播放的时间
	int nNextId; //需要播放下一个阶段的id
	std::vector<Segment> set;
	ElapseTime()
	{
		nId = 0;
		nTime = 0;
		nNextId = 0;
		set.clear();
	}
};

struct SceneAction
{
	int nId;      //当前场景动画的id
	int nModelID; //摄像机 动作模型 （决定摄像机的运动轨迹）
	float fx;    //坐标 摄像机动作模型在场景中的位置 和旋转角度
	float fy;
	float fz;
	float fRot;  //旋转角度
	std::vector<ElapseTime> vecSet;
	SceneAction()
	{
		nId = -1;
		nModelID = -1;
		fx = 0.0f;
		fy = 0.0f;
		fz = 0.0f;
		fRot = 0.0f;
	}
};

class CScenePlay
{
public:
	CScenePlay(void);
	~CScenePlay(void);

public:
	bool LoadSceneConfig(const char* pszPath);
	inline static  CScenePlay& Instance()
	{
		static CScenePlay s_xScenePlay;
		return s_xScenePlay;
	}

	SceneAction* GetActionInfoById(int nId);

private:
	std::vector<SceneAction> m_vecSet;
};

#define theScenePlay CScenePlay::Instance()