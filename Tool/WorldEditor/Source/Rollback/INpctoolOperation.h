#pragma once

#include "rollback\BaseOperation.h"

class CToolNpc;
class CNpcRes;

namespace NToolNpc
{

/*----------------------------------------------------------
desc	: 改变Npc操作的接口类。由于一个操作不管要涉及数据库的操作，还涉及同步Ui的操作，
		  故此处将IBaseOperation的client和receiver都假设是CToolNpc。
		  这些操作中，生成一个对象或者删除一个对象的回复是最为复杂的，因为对象之间存在许多关联，
		  所以要小心处理，并且以后若改变对象的结构，如何让定义的操作符合开放闭合原则，这也是要认真考虑的。
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

//增加一个npc
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
	PositionInfo::Position *m_pPos;	//寻路点
};

//删除一个npc
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

//更改npc的model
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

//更改Npc的position、orientation & scale
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

//增加npc寻路点
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

//删除npc寻路点
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

//改变npc寻路点的属性
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
//更改npc属性
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

