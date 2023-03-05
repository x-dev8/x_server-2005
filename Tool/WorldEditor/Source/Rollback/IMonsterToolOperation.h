#pragma once
#include "rollback\baseoperation.h"
#include "MeTerrain\SwType.h"

#include <vector>
#include <string>

class CToolMonsterQuad;
class CMonsterQuadRes;

namespace NMonsterTool
{

/*----------------------------------------------------------
desc	: �ı�monster�����Ľӿ��ࡣ
author	: zilong
version	: 1.0
date	: 2011-03-23

revision:
----------------------------------------------------------*/
class IMonsterToolOperation: public IBaseOperation
{
public:
	IMonsterToolOperation(CToolMonsterQuad *receiver_);
	virtual ~IMonsterToolOperation(void);

protected:
	CToolMonsterQuad *m_pReceiver;
};


//����ˢ������
//��������������պ��ͷŶ���ɾ������Ͳ��ù���
class CAddMonsterArea: public IMonsterToolOperation
{
public:
	CAddMonsterArea(CToolMonsterQuad *receiver_);
	virtual ~CAddMonsterArea();

	virtual bool Excute(void);

	void SetData(CMonsterQuadRes *pRes_);

private:
	CMonsterQuadRes *m_pRes;
};

//ɾ��ˢ������
class CDeleteMonsterArea: public IMonsterToolOperation
{
public:
	CDeleteMonsterArea(CToolMonsterQuad *receiver_);
	virtual ~CDeleteMonsterArea();

	virtual bool Excute(void);

	void SetData(CMonsterQuadRes *pRes_);

private:
	CMonsterQuadRes *m_pRes;
};

//�ƶ�ˢ������
class CMoveMonsterArea: public IMonsterToolOperation
{
public:
	CMoveMonsterArea(CToolMonsterQuad *receiver_);
	virtual ~CMoveMonsterArea();

	virtual bool Excute(void);

	void SetData(CMonsterQuadRes *pRes_, float x, float y, float w, float h);

private:
	CMonsterQuadRes *m_pRes;
	float m_fW, m_fH, m_fX, m_fY;
};

//ˢ��ˢ�ֵ�
class CRefreshMonsterPoint: public IMonsterToolOperation
{
public:
	CRefreshMonsterPoint(CToolMonsterQuad *receiver_);
	virtual ~CRefreshMonsterPoint();

	virtual bool Excute(void);

	void SetData(CMonsterQuadRes *pRes_);

private:
	CMonsterQuadRes *m_pRes;
};

//�ָ�ˢ�ֵ�
class CRevertMonsterPoint: public IMonsterToolOperation
{
public:
	CRevertMonsterPoint(CToolMonsterQuad *receiver_);
	virtual ~CRevertMonsterPoint();

	virtual bool Excute(void);

	void SetData(CMonsterQuadRes *pRes_);

private:
	CMonsterQuadRes *m_pRes;
	std::vector<Vector2> m_points;
};

//����ˢ������
class CSetMonsterType: public IMonsterToolOperation
{
public:
	CSetMonsterType(CToolMonsterQuad *receiver_);
	virtual ~CSetMonsterType();

	virtual bool Excute(void);

	void SetData(CMonsterQuadRes *pRes_, sInt32 type_, int index_);

private:
	CMonsterQuadRes *m_pRes;
	sInt32 m_type;
	int m_index;
};

//����ˢ�ֵ�����
class CSetMonsterCount: public IMonsterToolOperation
{
public:
	CSetMonsterCount(CToolMonsterQuad *receiver_);
	virtual ~CSetMonsterCount();

	virtual bool Excute(void);

	void SetData(CMonsterQuadRes *pRes_, UINT count_);

private:
	CMonsterQuadRes *m_pRes;
	UINT m_count;
};

//����ˢ�ָ���
class CSetMonsterRatio: public IMonsterToolOperation
{
public:
	CSetMonsterRatio(CToolMonsterQuad *receiver_);
	virtual ~CSetMonsterRatio();

	virtual bool Excute(void);

	void SetData(CMonsterQuadRes *pRes_, float ratio_);

private:
	CMonsterQuadRes *m_pRes;
	float m_ratio;
};

//����ˢ�ּ��
class CSetMonsterInterval: public IMonsterToolOperation
{
public:
	CSetMonsterInterval(CToolMonsterQuad *receiver_);
	virtual ~CSetMonsterInterval();

	virtual bool Excute(void);

	void SetData(CMonsterQuadRes *pRes_, sInt32 interval_);

private:
	CMonsterQuadRes *m_pRes;
	sInt32 m_interval;
};

//���ýű�
class CSetScript: public IMonsterToolOperation
{
public:
	CSetScript(CToolMonsterQuad *receiver_);
	virtual ~CSetScript();

	virtual bool Excute(void);

	void SetData(CMonsterQuadRes *pRes_, const char *script_, bool bEnter_);

private:
	CMonsterQuadRes *m_pRes;
	std::string m_script;
	bool m_bEnter;	//��־�ǽ��뻹���뿪
};

class CAddAutoTalk: public IMonsterToolOperation
{
public:
	CAddAutoTalk(CToolMonsterQuad *receiver_);
	virtual ~CAddAutoTalk();

	virtual bool Excute(void);

	void SetData(CMonsterQuadRes *pRes_, const CMonsterQuadRes::AutoTalk &talk_);

private:
	CMonsterQuadRes *m_pRes;
	CMonsterQuadRes::AutoTalk m_talk;
};

class CDeleteAutoTalk: public IMonsterToolOperation
{
public:
	CDeleteAutoTalk(CToolMonsterQuad *receiver_);
	virtual ~CDeleteAutoTalk();

	virtual bool Excute(void);

	void SetData(CMonsterQuadRes *pRes_, int index_);

private:
	CMonsterQuadRes *m_pRes;
	int m_index;
}; 

class CModifyAutoTalk: public IMonsterToolOperation
{
public:
	CModifyAutoTalk(CToolMonsterQuad *receiver_);
	virtual ~CModifyAutoTalk();

	virtual bool Excute(void);

	void SetData(CMonsterQuadRes *pRes_, int index_, int id_, int time_, int nextTimeId_);

private:
	CMonsterQuadRes *m_pRes;
	int m_index;
	int m_id;
	int m_time;
	int m_nextTimeId;
};

class CAddTalk: public IMonsterToolOperation
{
public:
	CAddTalk(CToolMonsterQuad *receiver_);
	virtual ~CAddTalk();

	virtual bool Excute(void);

	void SetData(CMonsterQuadRes *pRes_, int ownerIndex_, int stringId_, int probability_);

private:
	CMonsterQuadRes *m_pRes;
	int m_ownerIndex;
	int m_stringId;
	int m_probability;
};

class CDeleteTalk: public IMonsterToolOperation
{
public:
	CDeleteTalk(CToolMonsterQuad *receiver_);
	virtual ~CDeleteTalk();

	virtual bool Excute(void);

	void SetData(CMonsterQuadRes *pRes_, int ownerIndex_, int index_);

private:
	CMonsterQuadRes *m_pRes;
	int m_ownerIndex;
	int m_index;
};

class CModifyTalk: public IMonsterToolOperation
{
public:
	CModifyTalk(CToolMonsterQuad *receiver_);
	virtual ~CModifyTalk();

	virtual bool Excute(void);

	void SetData(CMonsterQuadRes *pRes_, int ownerIndex_, int index_, int stringId_, int probability_);

private:
	CMonsterQuadRes *m_pRes;
	int m_ownerIndex;
	int m_index;
	int m_stringId;
	int m_probability;
};

class CSetMonsterVisible: public IMonsterToolOperation
{
public:
	CSetMonsterVisible(CToolMonsterQuad *receiver_);
	virtual ~CSetMonsterVisible();

	virtual bool Excute(void);

	void SetData(CMonsterQuadRes *pRes_, bool bVisible);

private:
	CMonsterQuadRes *m_pRes;
	bool m_bVisible;
};


}


