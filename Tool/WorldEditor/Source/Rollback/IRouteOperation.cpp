#include "stdafx.h"
#include "IRouteOperation.h"
#include "Edit\ToolFlyRoute.h"

namespace NRouteTool
{

IRouteOperation::IRouteOperation(CToolRoute *receiver_):
m_pReceiver(receiver_)
{
}

IRouteOperation::~IRouteOperation(void)
{
}

//-------------------------------------------------------------------
CAddRoute::CAddRoute(CToolRoute *receiver_):
IRouteOperation(receiver_),
m_pRes(NULL)
{

}

CAddRoute::~CAddRoute()
{
	if(m_pRes != NULL && !m_bExcuted)
	{
		SAFE_DELETE(m_pRes);
	}
}

bool CAddRoute::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	return m_pReceiver->AddRoute((CNPCRouteRes *)m_pRes);
}

void CAddRoute::SetData(CRouteRes *pRes_)
{
	m_pRes = pRes_;
}

//----------------------------------------------------------------------
CDeleteRoute::CDeleteRoute(CToolRoute *receiver_):
IRouteOperation(receiver_),
m_pRes(NULL)
{

}

CDeleteRoute::~CDeleteRoute()
{

}

bool CDeleteRoute::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	return m_pReceiver->DeleteRoute((CNPCRouteRes *)m_pRes);
}

void CDeleteRoute::SetData(CRouteRes *pRes_)
{
	m_pRes = pRes_;
}

//-----------------------------------------------------------------------
CGenerateCloseRoute::CGenerateCloseRoute(CToolRoute *receiver_):
IRouteOperation(receiver_),
m_pRes(NULL)
{

}
CGenerateCloseRoute::~CGenerateCloseRoute()
{

}

bool CGenerateCloseRoute::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	return m_pReceiver->GenerateCloseRoute((CNPCRouteRes *)m_pRes, m_bShow, m_bGenerate);
}

void CGenerateCloseRoute::SetData(CRouteRes *pRes_, bool bShow_, bool bGenerate_)
{
	m_pRes = pRes_;
	m_bShow = bShow_;
	m_bGenerate = bGenerate_;
}

//-------------------------------------------------------------------------------------------------------------
CChangeRouteProperty::CChangeRouteProperty(CToolRoute *receiver_):
IRouteOperation(receiver_),
m_pRes(NULL)
{

}

CChangeRouteProperty::~CChangeRouteProperty()
{

}

bool CChangeRouteProperty::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	return m_pReceiver->ChangeRouteProperty((CNPCRouteRes *)m_pRes, m_name.c_str(), m_nextMapId, m_nextRouteId);
}

void CChangeRouteProperty::SetData(CNPCRouteRes *_pRes_, const char *name_, sInt32 nextMapId_, sInt32 nextRouteId_)
{
	m_pRes = _pRes_;
	m_name = name_;
	m_nextMapId = nextMapId_;
	m_nextRouteId = nextRouteId_;
}

//-------------------------------------------------------------------------------------------------------------
CAddRoutePoint::CAddRoutePoint(CToolRoute *receiver_):
IRouteOperation(receiver_),
m_pRes(NULL),
m_pNpcPoint(NULL),
m_pPoint(NULL)
{

}

CAddRoutePoint::~CAddRoutePoint()
{
	if(m_bExcuted)
		return;

	if(m_pNpcPoint != NULL)
	{
		delete m_pNpcPoint;
	}

	if(m_pPoint != NULL)
	{
		delete m_pPoint;
	}
}

bool CAddRoutePoint::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	return m_pReceiver->AddRoutePoint((CNPCRouteRes*)m_pRes, m_index, m_pNpcPoint, m_pPoint, m_bShow);
}

void CAddRoutePoint::SetData(CRouteRes *pRes_, int index_, CNPCRouteRes::SNpcRoutePoint *pNpcPoint_, Vector *pPoint_, bool bShow_)
{
	m_pRes = pRes_;
	m_index = index_;
	m_pNpcPoint = pNpcPoint_;
	m_pPoint = pPoint_;
	m_bShow = bShow_;
}

//----------------------------------------------------------------------------------------------------------
CDeleteRoutePoint::CDeleteRoutePoint(CToolRoute *receiver_):
IRouteOperation(receiver_),
m_pRes(NULL)
{

}

CDeleteRoutePoint::~CDeleteRoutePoint()
{

}

bool CDeleteRoutePoint::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	return m_pReceiver->DeleteRoutePoint((CNPCRouteRes*)m_pRes, m_index);
}

void CDeleteRoutePoint::SetData(CRouteRes *pRes_, int index_)
{
	m_pRes = pRes_;
	m_index = index_;
}

//-----------------------------------------------------------------------------------------------------------
CChangeRoutePointPosition::CChangeRoutePointPosition(CToolRoute *receiver_):
IRouteOperation(receiver_),
m_pRes(NULL)
{

}

CChangeRoutePointPosition::~CChangeRoutePointPosition()
{

}

bool CChangeRoutePointPosition::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	return m_pReceiver->ChangeRoutePointPosition((CNPCRouteRes*)m_pRes, m_index, m_x, m_y, m_z);
}

void CChangeRoutePointPosition::SetData(CRouteRes *pRes_, int index_, flt32 x_, flt32 y_, flt32 z_)
{
	m_pRes = pRes_;
	m_index = index_;
	m_x = x_;
	m_y	= y_;
	m_z	= z_;
}

//-------------------------------------------------------------------------------------------------------------
CChangeRoutePointProperty::CChangeRoutePointProperty(CToolRoute *receiver_):
IRouteOperation(receiver_),
m_pRes(NULL)
{

}

CChangeRoutePointProperty::~CChangeRoutePointProperty()
{

}

bool CChangeRoutePointProperty::Excute(void)
{
	if(NULL == m_pReceiver)
		return false;

	return m_pReceiver->ChangeRoutePointProperty((CNPCRouteRes *)m_pRes, m_index, m_npcPoint);
}

void CChangeRoutePointProperty::SetData(CRouteRes *pRes_, int index_, const CNPCRouteRes::SNpcRoutePoint &npcPoint_)
{
	m_pRes = pRes_;
	m_index = index_;
	m_npcPoint = npcPoint_;
}

}