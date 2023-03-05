#pragma once

#include "rollback\BaseOperation.h"

class CToolNpc;
class CNpcRes;

namespace NToolNpc
{

/*----------------------------------------------------------
desc	: �ı�Npc�����Ľӿ��ࡣ����һ����������Ҫ�漰���ݿ�Ĳ��������漰ͬ��Ui�Ĳ�����
		  �ʴ˴���IBaseOperation��client��receiver��������CToolNpc��
		  ��Щ�����У�����һ���������ɾ��һ������Ļظ�����Ϊ���ӵģ���Ϊ����֮�������������
		  ����ҪС�Ĵ��������Ժ����ı����Ľṹ������ö���Ĳ������Ͽ��űպ�ԭ����Ҳ��Ҫ���濼�ǵġ�
author	: zilong
version	: 1.0
date	: 2011-03-23

revision:

----------------------------------------------------------*/
class INpctoolOperation: public IBaseOperation
{
public:
	INpctoolOperation();
	INpctoolOperation(CToolNpc *receiver_);
	virtual ~INpctoolOperation(void);

	void SetReceiver(CToolNpc *receiver_);

protected:
	CToolNpc *m_pReceiver;
};

//����һ��npc
class CAddNpc: public INpctoolOperation
{
public:
	//CAddNpc();
	CAddNpc(CToolNpc *receiver_);
	~CAddNpc();

	virtual bool Excute(void);

	void SetData(NpcInfo::Npc *pNpc_, PositionInfo::Position *pPos);

private:
	NpcInfo::Npc *m_pNpc;
	PositionInfo::Position *m_pPos;	//Ѱ·��
};

//ɾ��һ��npc
class CDeleteNpc: public INpctoolOperation
{
public:
	CDeleteNpc();
	CDeleteNpc(CToolNpc *receiver_);
	virtual ~CDeleteNpc();

	virtual bool Excute(void);

	void SetData(/*int resId_, */int npcId_);

private:
	//int m_resID;
	int m_npcID;
};

//����npc��model
class CChangeNpcModel: public INpctoolOperation
{
public:
	//CChangeNpcModel();
	CChangeNpcModel(CToolNpc *receiver_);
	virtual ~CChangeNpcModel();

	virtual bool Excute(void);

	//void SetData(CNpcRes *_res_, int modelId_);
	void SetData(int npcId_, int modelId_);
private:
	//CNpcRes *m_pRes;
	int m_npcId;
	int m_modelId;
};

//����Npc��position��orientation & scale
class CChangeNpcPos: public INpctoolOperation
{
public:
	CChangeNpcPos(CToolNpc *receiver_);
	virtual ~CChangeNpcPos();

	virtual bool Excute(void);

	//void SetData(CNpcRes *_res_, float x_, float y_, float z_, int dir_, float scale_);
	void SetData(int npcId_, float x_, float y_, float z_, int dir_, float scale_);
private:
	//CNpcRes *m_pRes;
	int m_npcId;
	float m_pos[3];
	int m_dirction;
	float m_scale;
};

//����npcѰ·��
class CAddNpcPosition: public INpctoolOperation
{
public:
	CAddNpcPosition(CToolNpc *receiver_);
	virtual ~CAddNpcPosition();

	virtual bool Excute(void);

	void SetData(int npcId_, const PositionInfo::Position &pos_);
private:
	int m_npcId;
	PositionInfo::Position m_pos;
};

//ɾ��npcѰ·��
class CDeleteNpcPosition: public INpctoolOperation
{
public:
	CDeleteNpcPosition(CToolNpc *receiver_);
	virtual ~CDeleteNpcPosition();

	virtual bool Excute(void);

	void SetData(int npcId_);
private:
	int m_npcId;
};

//�ı�npcѰ·�������
class CChangeNpcPosition: public INpctoolOperation
{
public:
	CChangeNpcPosition(CToolNpc *receiver_);
	virtual ~CChangeNpcPosition();

	virtual bool Excute(void);

	void SetData(int npcId_, const PositionInfo::Position &pos_);
private:
	int m_npcId;
	PositionInfo::Position m_pos;
};

/*
//����npc����
class CModifyNpcs: public INpctoolOperation
{
public:
	CModifyNpcs(CToolNpc *receiver_);
	virtual ~CModifyNpcs();

	virtual bool Excute(void);

	void SetData(int npcId_, const NpcInfo::Npc &npc_);
private:
	int m_npcId;
	std::vector<NpcInfo::Npc> m_npcs;
};
*/

}

