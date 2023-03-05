#pragma once
#include <math.h>
#include <vector>
#include "RapidXml/MeRapidXml.h"

//需求类型
enum ReqType
{
	Req_None,   //无
	Req_Dislen, //距离
	Req_Sex,    //性别
	Req_Task,	//任务
	Req_Level,  //等级
	Req_Max,
};

//触发类型
enum EventType
{
	Event_None,   //无
	Event_Talk,   //说话
	Event_Anim,   //动画
	Event_AutoFace,//自动朝向玩家
	Event_Max,
};

//需求类型
struct Require
{
	ReqType   eType;  //需求类型
	int       nSex;   //性别
	float     fMin;   //区间范围
	float     fMax;
	int		  nTaskID;	//已完成的任务

	Require()
	{
		eType = Req_None;
		nSex = 0;
		fMin = 0.0f;
		fMax = 0.0f;
		nTaskID = -1;
	}

	bool IsInZoneArea(float fx1,float fy1,float fx2,float fy2)
	{
		float fX = abs(fx1 - fx2);
		float fY = abs(fy1 - fy2);
		float fDis = sqrt(fX * fX + fY * fY);
		if(fDis < fMin || fDis > fMax)
			return false;

		return true;
	}

	bool IsSameSex(int nPlayerSex)
	{
		return (nPlayerSex == nSex);
	}

	bool IsInLevelArea(int nLevel)
	{
		if(nLevel < fMin || nLevel > fMax)
			return false;

		return true;
	}

	int FinishedTaskID()
	{
		return nTaskID;
	}
	
};

//说话事件
struct EventTalk
{
	int nStringId;
	int nProbability;
	int nDelayTime;
	EventTalk()
	{
		nStringId = 0;
		nProbability = 0;
		nDelayTime = 0;
	}
};

//动作事件
struct EventAnim
{
	std::string strType;
	int nProbability;
	int nDelayTime;
	EventAnim()
	{
		strType.clear();
		nProbability = 0;
		nDelayTime = 0;
	}
};

//转向事件
struct EventAutoFace
{
	bool bIsAutoFace;
	int nProbability;
	int nDelayTime;
	EventAutoFace()
	{
		bIsAutoFace = false;
		nProbability = 0;
		nDelayTime = 0;
	}
};

//行为
struct Action
{
	std::vector<Require> vecMustTerm;      //必须条件
	std::vector<Require> vecProbilityTerm; //概率条件,满足一条就可以了
	EventAnim anim;
	EventTalk talk;
	EventAutoFace autoFace;						//事件发生时是否自动朝向玩家
	Action()
	{
		vecMustTerm.clear();
		vecProbilityTerm.clear();
	}
};

class CNpcAction
{
public:
	CNpcAction(void);
	~CNpcAction(void);
public:
	void Clear(){m_ActSet.clear();}
	bool ParseAction(MeXmlElement *pRoot);	
	Action* GetOneActionByIndex(int nIndex);
	void AddAction(Action &act){m_ActSet.push_back(act);}
	int   GetSize(){return (int)m_ActSet.size();}
private:
	std::vector<Action> m_ActSet;  //行为集合
};
