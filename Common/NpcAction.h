#pragma once
#include <math.h>
#include <vector>
#include "RapidXml/MeRapidXml.h"

//��������
enum ReqType
{
	Req_None,   //��
	Req_Dislen, //����
	Req_Sex,    //�Ա�
	Req_Task,	//����
	Req_Level,  //�ȼ�
	Req_Max,
};

//��������
enum EventType
{
	Event_None,   //��
	Event_Talk,   //˵��
	Event_Anim,   //����
	Event_AutoFace,//�Զ��������
	Event_Max,
};

//��������
struct Require
{
	ReqType   eType;  //��������
	int       nSex;   //�Ա�
	float     fMin;   //���䷶Χ
	float     fMax;
	int		  nTaskID;	//����ɵ�����

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

//˵���¼�
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

//�����¼�
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

//ת���¼�
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

//��Ϊ
struct Action
{
	std::vector<Require> vecMustTerm;      //��������
	std::vector<Require> vecProbilityTerm; //��������,����һ���Ϳ�����
	EventAnim anim;
	EventTalk talk;
	EventAutoFace autoFace;						//�¼�����ʱ�Ƿ��Զ��������
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
	std::vector<Action> m_ActSet;  //��Ϊ����
};
