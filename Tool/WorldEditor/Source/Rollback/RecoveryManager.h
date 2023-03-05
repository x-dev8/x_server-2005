/*----------------------------------------------------------
desc	: 恢复功能（undo redo）模块。
author	: zilong
version	: 1.0
date	: 2011-03-23

revision:

----------------------------------------------------------*/

#pragma once

#include <stack>

class COpertaionPair;

class CRecoveryManager
{
private:
	typedef std::stack<COpertaionPair *> TOperations;

public:
	CRecoveryManager(void);
	~CRecoveryManager(void);

	//清空库
	void Clear(void);

	//是否可以回滚
	bool CanRollback(void);
	//是否可以向前滚动
	bool CanRoll(void);

	//执行一个操作，成功之后将该操作入库。
	bool Excute(COpertaionPair *operation_);
	//回滚一个操作。
	bool Rollback(void);
	//向前滚动一个操作。
	bool Roll(void);
	bool Rollback(int count_);
	bool Roll(int count_);

private:
	void ClearOpertaions(TOperations &_ops_);

private:
	TOperations m_undoes;	//
	TOperations m_redoes;
};
