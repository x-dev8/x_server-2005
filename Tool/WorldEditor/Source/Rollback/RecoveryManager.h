/*----------------------------------------------------------
desc	: �ָ����ܣ�undo redo��ģ�顣
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

	//��տ�
	void Clear(void);

	//�Ƿ���Իع�
	bool CanRollback(void);
	//�Ƿ������ǰ����
	bool CanRoll(void);

	//ִ��һ���������ɹ�֮�󽫸ò�����⡣
	bool Excute(COpertaionPair *operation_);
	//�ع�һ��������
	bool Rollback(void);
	//��ǰ����һ��������
	bool Roll(void);
	bool Rollback(int count_);
	bool Roll(int count_);

private:
	void ClearOpertaions(TOperations &_ops_);

private:
	TOperations m_undoes;	//
	TOperations m_redoes;
};
