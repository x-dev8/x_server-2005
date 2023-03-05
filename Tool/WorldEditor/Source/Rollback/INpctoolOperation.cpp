#include "stdafx.h"
#include "INpctoolOperation.h"
#include "Edit\ToolNpc.h"
#include "EditRes/NdlEditRes.h"

namespace NToolNpc
{

INpctoolOperation::INpctoolOperation(void):
m_pReceiver(NULL)
{
}

INpctoolOperation::INpctoolOperation(CToolNpc *receiver_):
m_pReceiver(receiver_)
{

}

INpctoolOperation::~INpctoolOperation(void)
{
}


//----------------------------------------------------------------------------
CChangeNpcModel::CChangeNpcModel(CToolNpc *receiver_):
INpctoolOperation(receiver_),
//m_pRes(NULL),
m_npcId(-1),
m_modelId(-1)
{

}

CChangeNpcModel::~CChangeNpcModel()
{

}

bool CChangeNpcModel::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	//return m_pReceiver->ChangeNpcModel(m_pRes, m_modelId);
	return m_pReceiver->ChangeNpcModel(m_npcId, m_modelId);
}

/*
void CChangeNpcModel::SetData(CNpcRes *_res_, int modelId_)
{
	m_pRes = _res_;
	m_modelId = modelId_;
}
*/

void CChangeNpcModel::SetData(int npcId_, int modelId_)
{
	m_npcId = npcId_;
	m_modelId = modelId_;
}

//--------------------------------------------------------------------------------
CChangeNpcPos::CChangeNpcPos(CToolNpc *receiver_):
INpctoolOperation(receiver_),
//m_pRes(NULL)
m_npcId(-1)
{

}
CChangeNpcPos::~CChangeNpcPos()
{

}

bool CChangeNpcPos::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	//return m_pReceiver->ChangeNpcPos(m_pRes, m_pos[0], m_pos[1], m_pos[2], m_dirction, m_scale);
	return m_pReceiver->ChangeNpcPos(m_npcId, m_pos[0], m_pos[1], m_pos[2], m_dirction, m_scale);
}

/*
void CChangeNpcPos::SetData(CNpcRes *_res_, float x_, float y_, float z_, int dir_, float scale_)
{
	m_pRes = _res_;
	m_pos[0] = x_;
	m_pos[1] = y_;
	m_pos[2] = z_;
	m_dirction = dir_;
	m_scale = scale_;
}
*/

void CChangeNpcPos::SetData(int npcId_, float x_, float y_, float z_, int dir_, float scale_)
{
	m_npcId = npcId_;
	m_pos[0] = x_;
	m_pos[1] = y_;
	m_pos[2] = z_;
	m_dirction = dir_;
	m_scale = scale_;
}

//-------------------------------------------------------------------------------------
CAddNpc::CAddNpc(CToolNpc *receiver_):
INpctoolOperation(receiver_),
m_pNpc(NULL),
m_pPos(NULL)
{

}

CAddNpc::~CAddNpc()
{
	if(m_pNpc)
	{
		delete m_pNpc;
	}

	if(m_pPos)
	{
		delete m_pPos;
	}
}

bool CAddNpc::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	return m_pReceiver->AddNpc(m_pNpc, m_pPos);
}

void CAddNpc::SetData(NpcInfo::Npc *pNpc_, PositionInfo::Position *pPos)
{
	m_pNpc = pNpc_;
	m_pPos = pPos;
}

//-------------------------------------------------------------------------------------
CDeleteNpc::CDeleteNpc(CToolNpc *receiver_):
INpctoolOperation(receiver_),
//m_resID(-1),
m_npcID(-1)
{

}

CDeleteNpc::~CDeleteNpc()
{

}

bool CDeleteNpc::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	return m_pReceiver->DeleteNpc(/*m_resID, */m_npcID);
}

void CDeleteNpc::SetData(/*int resId_, */int npcId_)
{
	//m_resID = resId_;
	m_npcID = npcId_;
}

//----------------------------------------------------------------------------------------
CAddNpcPosition::CAddNpcPosition(CToolNpc *receiver_):
INpctoolOperation(receiver_)
{

}

CAddNpcPosition::~CAddNpcPosition()
{

}

bool CAddNpcPosition::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	return m_pReceiver->AddNpcPostion(m_npcId, m_pos);
}

void CAddNpcPosition::SetData(int npcId_, const PositionInfo::Position &pos_)
{
	m_npcId = npcId_;
	m_pos = pos_;
}

//------------------------------------------------------------------------------------------
CDeleteNpcPosition::CDeleteNpcPosition(CToolNpc *receiver_):
INpctoolOperation(receiver_)
{

}
CDeleteNpcPosition::~CDeleteNpcPosition()
{

}

bool CDeleteNpcPosition::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	return m_pReceiver->DeleteNpcPosition(m_npcId);
}

void CDeleteNpcPosition::SetData(int npcId_)
{
	m_npcId = npcId_;
}

//---------------------------------------------------------------------------------------------
CChangeNpcPosition::CChangeNpcPosition(CToolNpc *receiver_):
INpctoolOperation(receiver_)
{

}

CChangeNpcPosition::~CChangeNpcPosition()
{

}

bool CChangeNpcPosition::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	return m_pReceiver->ChangeNpcPosition(m_npcId, m_pos);
}

void CChangeNpcPosition::SetData(int npcId_, const PositionInfo::Position &pos_)
{
	m_npcId = npcId_;
	m_pos	 = pos_;
}

//-----------------------------------------------------------------------------------
/*
CModifyNpcs::CModifyNpcs(CToolNpc *receiver_):
INpctoolOperation(receiver_)
{

}

CModifyNpcs::~CModifyNpcs()
{

}

bool CModifyNpcs::Excute(void)
{

}

void CModifyNpcs::SetData(int npcId_, const NpcInfo::Npc &npc_)
{
	m_npcId = npcId_;

	NpcInfo::FourNpc* FNpc = theNpcInfo.GetFourNpc(m_npcId);
	for (int i=0; i<4; ++i)
	{
		if (FNpc->FourCountryNpc[i] == NULL)
		{ continue;}

		FNpc->FourCountryNpc[i]->id = npc_.id;
		FNpc->FourCountryNpc[i]->type = npc_.type;   // Npc类型
		FNpc->FourCountryNpc[i]->dynamicId = 0;
		FNpc->FourCountryNpc[i]->name = npc_.name;	
		FNpc->FourCountryNpc[i]->pinyin = npc_.pinyin;
		FNpc->FourCountryNpc[i]->level =npc_.level;					
		FNpc->FourCountryNpc[i]->movePath = npc_.movePath;				
		FNpc->FourCountryNpc[i]->canChangeDirection = npc_.canChangeDirection;	
		FNpc->FourCountryNpc[i]->triggerScript = npc_.triggerScript;    // 触发脚本
		FNpc->FourCountryNpc[i]->actionScript = npc_.actionScript;  // 动作脚本
		FNpc->FourCountryNpc[i]->isMiniShow = npc_.isMiniShow;
		FNpc->FourCountryNpc[i]->isWorldShow = npc_.isWorldShow;
		FNpc->FourCountryNpc[i]->isCollision = npc_.isCollision;			
		FNpc->FourCountryNpc[i]->title = npc_.title;
		FNpc->FourCountryNpc[i]->tip = npc_.tip;
		FNpc->FourCountryNpc[i]->headPicture = npc_.headPicture;
		FNpc->FourCountryNpc[i]->isDynamicCollision=npc_.isDynamicCollision;
		FNpc->FourCountryNpc[i]->nTaskMenu = npc_.nTaskMenu;
		FNpc->FourCountryNpc[i]->uchCountryID = i; // 国家ID从0，1，2，3
	}
}
*/

}
