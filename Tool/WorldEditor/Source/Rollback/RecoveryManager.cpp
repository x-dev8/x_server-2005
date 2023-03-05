#include "RecoveryManager.h"
#include "rollback\BaseOperation.h"
#include <assert.h>

CRecoveryManager::CRecoveryManager(void)
{
}

CRecoveryManager::~CRecoveryManager(void)
{
	Clear();
}

void CRecoveryManager::Clear(void)
{
	ClearOpertaions(m_redoes);
	ClearOpertaions(m_undoes);
}

void CRecoveryManager::ClearOpertaions(TOperations &_ops_)
{
	while(!_ops_.empty())
	{
		delete _ops_.top();
		_ops_.pop();
	}
}

bool CRecoveryManager::CanRollback(void)
{
	return !m_undoes.empty();
}

bool CRecoveryManager::CanRoll(void)
{
	return !m_redoes.empty();
}

bool CRecoveryManager::Excute(COpertaionPair *operation_)
{
	assert(operation_ != NULL);
	if(NULL == operation_)
		return false;

	if(operation_->Excute())
	{
		ClearOpertaions(m_redoes);
		m_undoes.push(operation_);

		return true;
	}

	return false;
}

bool CRecoveryManager::Rollback(void)
{
	if(!CanRollback())
		return false;

	COpertaionPair *op = m_undoes.top();
	assert(op != NULL);
	if(op->Rollback())
	{
		m_undoes.pop();
		m_redoes.push(op);

		return true;
	}

	return false;
}

bool CRecoveryManager::Roll(void)
{
	if(!CanRoll())
		return false;

	COpertaionPair *op = m_redoes.top();
	assert(op != NULL);
	if(op->Excute())
	{
		m_redoes.pop();
		m_undoes.push(op);

		return true;
	}

	return false;
}
