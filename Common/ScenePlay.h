#pragma once
#include <vector>

struct Segment
{
	std::string strAnimBegin;  //˵��ʱ��Ŀ�ʼ����
	std::string strAnimEnd;    //˵��ʱ��Ľ�������
	int         nTalkId;   //��ɫ˵���� �ַ���id ����string.config �ж�ȡ
	std::string strTrack; // ������� ��Ҫ���Ŷ���������
	std::string strMountAnimBegin; //˵��ʱ���������ϵĿ�ʼ����
	std::string strMountAnimEnd;   //˵��ʱ���������ϵĽ�������

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
	int nId;    //���ڽ׶ε�id
	int nTime;  //��ǰ�׶���Ҫ���ŵ�ʱ��
	int nNextId; //��Ҫ������һ���׶ε�id
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
	int nId;      //��ǰ����������id
	int nModelID; //����� ����ģ�� ��������������˶��켣��
	float fx;    //���� ���������ģ���ڳ����е�λ�� ����ת�Ƕ�
	float fy;
	float fz;
	float fRot;  //��ת�Ƕ�
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