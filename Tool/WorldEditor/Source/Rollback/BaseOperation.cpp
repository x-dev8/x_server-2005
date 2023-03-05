#include "BaseOperation.h"
#include <stdlib.h>
#include <assert.h>

IBaseOperation::IBaseOperation(void):
m_bExcuted(false)
{
}

IBaseOperation::~IBaseOperation(void)
{
}

void IBaseOperation::SetStatus(bool bExcuted_)
{
	m_bExcuted = bExcuted_;
}

COpertaionPair::COpertaionPair(IBaseOperation *do_, IBaseOperation *undo_):
m_do(do_),
m_undo(undo_),
m_bExcuted(false)
{

}

COpertaionPair::~COpertaionPair()
{

}

bool COpertaionPair::Rollback(void)
{
	assert(m_undo != NULL);
	if(!m_bExcuted)
		return false;

	m_bExcuted = false;

/*
	return m_undo->Excute();
*/
	bool ret = m_undo->Excute();
	if(ret)
	{
		m_undo->SetStatus(true);
		m_do->SetStatus(false);
	}

	return ret;
}

bool COpertaionPair::Excute(void)
{
	assert(m_do != NULL);
	if(m_bExcuted)
		return false;

	m_bExcuted  = true;
/*
	return m_do->Excute();
*/

	bool ret = m_do->Excute();
	if(ret)
	{
		m_do->SetStatus(true);
		m_undo->SetStatus(false);
	}

	return ret;
}
