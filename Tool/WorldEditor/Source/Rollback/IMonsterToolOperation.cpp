#include "stdafx.h"
#include "IMonsterToolOperation.h"
#include "Edit/ToolMonsterQuad.h"

namespace NMonsterTool
{

IMonsterToolOperation::IMonsterToolOperation(CToolMonsterQuad *receiver_):
m_pReceiver(receiver_)
{
}

IMonsterToolOperation::~IMonsterToolOperation(void)
{
}


//-----------------------------------------------------------------------------
CAddMonsterArea::CAddMonsterArea(CToolMonsterQuad *receiver_):
IMonsterToolOperation(receiver_),
m_pRes(NULL)
{

}

CAddMonsterArea::~CAddMonsterArea()
{
	if(m_pRes != NULL && !m_bExcuted)
	{
		SAFE_DELETE(m_pRes);
	}
}

bool CAddMonsterArea::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	return m_pReceiver->AddMonsterQuad(m_pRes);
}

void CAddMonsterArea::SetData(CMonsterQuadRes *pRes_)
{
	m_pRes = pRes_;
}

//---------------------------------------------------------------------------------
CDeleteMonsterArea::CDeleteMonsterArea(CToolMonsterQuad *receiver_):
IMonsterToolOperation(receiver_),
m_pRes(NULL)
{

}

CDeleteMonsterArea::~CDeleteMonsterArea()
{

}

bool CDeleteMonsterArea::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	return m_pReceiver->DeleteMonsterQuad(m_pRes);
}

void CDeleteMonsterArea::SetData(CMonsterQuadRes *pRes_)
{
	m_pRes = pRes_;
}

//-----------------------------------------------------------------------------------
CMoveMonsterArea::CMoveMonsterArea(CToolMonsterQuad *receiver_):
IMonsterToolOperation(receiver_)
{

}

CMoveMonsterArea::~CMoveMonsterArea()
{

}

bool CMoveMonsterArea::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	return m_pReceiver->UpdateMonsQuad(m_pRes, m_fX, m_fY, m_fW, m_fH);
}

void CMoveMonsterArea::SetData(CMonsterQuadRes *pRes_, float x, float y, float w, float h)
{
	m_pRes = pRes_;
	
	m_fW = w;
	m_fH = h;

	m_fX = x;
	m_fY = y;
}

//------------------------------------------------------------------------------------
CRefreshMonsterPoint::CRefreshMonsterPoint(CToolMonsterQuad *receiver_):
IMonsterToolOperation(receiver_)
{

}

CRefreshMonsterPoint::~CRefreshMonsterPoint()
{

}

bool CRefreshMonsterPoint::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	//return m_pReceiver->RefreshMonsterPoint(m_pRes);
	return false;
}

void CRefreshMonsterPoint::SetData(CMonsterQuadRes *pRes_)
{
	m_pRes = pRes_;
}

//--------------------------------------------------------------------------------------
CRevertMonsterPoint::CRevertMonsterPoint(CToolMonsterQuad *receiver_):
IMonsterToolOperation(receiver_)
{

}

CRevertMonsterPoint::~CRevertMonsterPoint()
{

}

bool CRevertMonsterPoint::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	Vector2 *points = NULL;
	if(!m_points.empty())
		points = &m_points[0];

	return m_pReceiver->RevertMonsterPoint(m_pRes, points, m_points.size());
}

void CRevertMonsterPoint::SetData(CMonsterQuadRes *pRes_)
{
	if(NULL == pRes_)
		return;

	std::vector<Vector2* > points;// = pRes_->GetMonsterPointList();
	for(int i=0; i<points.size(); ++i)
	{
		if(NULL == points[i])
			continue;

		m_points.push_back(*points[i]);
	}

	m_pRes = pRes_;
}

//------------------------------------------------------------------------------
CSetMonsterType::CSetMonsterType(CToolMonsterQuad *receiver_):
IMonsterToolOperation(receiver_)
{

}
CSetMonsterType::~CSetMonsterType()
{

}

bool CSetMonsterType::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	return m_pReceiver->SetMonsterType(m_pRes, m_type, m_index);
}

void CSetMonsterType::SetData(CMonsterQuadRes *pRes_, sInt32 type_, int index_)
{
	m_pRes = pRes_;
	m_type = type_;
	m_index = index_;
}

//--------------------------------------------------------------------------------
CSetMonsterCount::CSetMonsterCount(CToolMonsterQuad *receiver_):
IMonsterToolOperation(receiver_)
{

}
CSetMonsterCount::~CSetMonsterCount()
{

}

bool CSetMonsterCount::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	return m_pReceiver->SetMonsterCount(m_pRes, m_count);
}

void CSetMonsterCount::SetData(CMonsterQuadRes *pRes_, UINT count_)
{
	m_pRes = pRes_;
	m_count = count_;
}

//-----------------------------------------------------------------------------------
CSetMonsterRatio::CSetMonsterRatio(CToolMonsterQuad *receiver_):
IMonsterToolOperation(receiver_)
{

}

CSetMonsterRatio::~CSetMonsterRatio()
{

}

bool CSetMonsterRatio::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	return m_pReceiver->SetMonterRatio(m_pRes, m_ratio);
}

void CSetMonsterRatio::SetData(CMonsterQuadRes *pRes_, float ratio_)
{
	m_pRes = pRes_;
	m_ratio = ratio_;
}

//------------------------------------------------------------------------------------
CSetMonsterInterval::CSetMonsterInterval(CToolMonsterQuad *receiver_):
IMonsterToolOperation(receiver_)
{

}
CSetMonsterInterval::~CSetMonsterInterval()
{

}

bool CSetMonsterInterval::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	return m_pReceiver->SetMonsterInterval(m_pRes, m_interval);
}

void CSetMonsterInterval::SetData(CMonsterQuadRes *pRes_, sInt32 interval_)
{
	m_pRes = pRes_;
	m_interval = interval_;
}

//------------------------------------------------------------------------------------------
CSetScript::CSetScript(CToolMonsterQuad *receiver_):
IMonsterToolOperation(receiver_)
{

}
CSetScript::~CSetScript()
{

}

bool CSetScript::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	return m_pReceiver->SetScript(m_pRes, m_script.c_str(), m_bEnter);
}

void CSetScript::SetData(CMonsterQuadRes *pRes_, const char *script_, bool bEnter_)
{
	m_pRes = pRes_;
	m_script = script_;
	m_bEnter = bEnter_;
}

//---------------------------------------------------------------------------------------------
CAddAutoTalk::CAddAutoTalk(CToolMonsterQuad *receiver_):
IMonsterToolOperation(receiver_)
{

}
CAddAutoTalk::~CAddAutoTalk()
{

}

bool CAddAutoTalk::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	return m_pReceiver->AddAutoTalk(m_pRes, m_talk);
}

void CAddAutoTalk::SetData(CMonsterQuadRes *pRes_, const CMonsterQuadRes::AutoTalk &talk_)
{
	m_pRes = pRes_;
	m_talk = talk_;
}

//---------------------------------------------------------------------------------------------
CDeleteAutoTalk::CDeleteAutoTalk(CToolMonsterQuad *receiver_):
IMonsterToolOperation(receiver_)
{

}
CDeleteAutoTalk::~CDeleteAutoTalk()
{

}

bool CDeleteAutoTalk::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	return m_pReceiver->DeleteAutoTalk(m_pRes, m_index);
}

void CDeleteAutoTalk::SetData(CMonsterQuadRes *pRes_, int index_)
{
	m_pRes = pRes_;
	m_index = index_;
}

//------------------------------------------------------------------------------------------
CModifyAutoTalk::CModifyAutoTalk(CToolMonsterQuad *receiver_):
IMonsterToolOperation(receiver_)
{

}

CModifyAutoTalk::~CModifyAutoTalk()
{

}

bool CModifyAutoTalk::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	return m_pReceiver->ModifyAutoTalk(m_pRes, m_index, m_id, m_time, m_nextTimeId);
}

void CModifyAutoTalk::SetData(CMonsterQuadRes *pRes_, int index_, int id_, int time_, int nextTimeId_)
{
	m_pRes = pRes_;
	m_index = index_;
	m_id = id_;
	m_time = time_;
	m_nextTimeId = nextTimeId_;
}

//------------------------------------------------------------------------------------------------
CAddTalk::CAddTalk(CToolMonsterQuad *receiver_):
IMonsterToolOperation(receiver_)
{

}

CAddTalk::~CAddTalk()
{

}

bool CAddTalk::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	return m_pReceiver->AddTalk(m_pRes, m_ownerIndex, m_stringId, m_probability);
}

void CAddTalk::SetData(CMonsterQuadRes *pRes_, int ownerIndex_, int stringId_, int probability_)
{
	m_pRes = pRes_;
	m_ownerIndex = ownerIndex_;
	m_stringId = stringId_;
	m_probability = probability_;
}

//------------------------------------------------------------------------------------------------------
CDeleteTalk::CDeleteTalk(CToolMonsterQuad *receiver_):
IMonsterToolOperation(receiver_)
{

}
CDeleteTalk::~CDeleteTalk()
{

}

bool CDeleteTalk::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	return m_pReceiver->DeleteTalk(m_pRes, m_ownerIndex, m_index);
}

void CDeleteTalk::SetData(CMonsterQuadRes *pRes_, int ownerIndex_, int index_)
{
	m_pRes = pRes_;
	m_ownerIndex = ownerIndex_;
	m_index = index_;
}

//------------------------------------------------------------------------------------------------
CModifyTalk::CModifyTalk(CToolMonsterQuad *receiver_):
IMonsterToolOperation(receiver_)
{

}

CModifyTalk::~CModifyTalk()
{

}

bool CModifyTalk::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;
	
	return m_pReceiver->ModifyTalk(m_pRes, m_ownerIndex, m_index, m_stringId, m_probability);
}

void CModifyTalk::SetData(CMonsterQuadRes *pRes_, int ownerIndex_, int index_, int stringId_, int probability_)
{
	m_pRes = pRes_;
	m_ownerIndex = ownerIndex_;
	m_index = index_;
	m_stringId = stringId_;
	m_probability = probability_;
}

CSetMonsterVisible::CSetMonsterVisible(CToolMonsterQuad *receiver_):
IMonsterToolOperation(receiver_)
{

}
CSetMonsterVisible::~CSetMonsterVisible()
{

}

bool CSetMonsterVisible::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	return m_pReceiver->SetMonsterVisible(m_pRes, m_bVisible);
}

void CSetMonsterVisible::SetData(CMonsterQuadRes *pRes_, bool bVisible)
{
	m_pRes = pRes_;
	m_bVisible = bVisible;
}

}
