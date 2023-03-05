/*----------------------------------------------------------
desc	: 编辑器中各种操作的接口类。
author	: zilong
version	: 1.0
date	: 2011-03-23

revision:

----------------------------------------------------------*/

#pragma once

class IBaseOperation
{
public:
	IBaseOperation(void);
	virtual ~IBaseOperation(void);

	//每个operation应该保证在没有成功的情况下自己回滚（即不改变数据库）。
	virtual bool Excute(void) = 0;

	void SetStatus(bool bExcuted_);

protected:
	bool m_bExcuted;
};

//一对相反的操作
class COpertaionPair
{
public:
	COpertaionPair(IBaseOperation *do_, IBaseOperation *undo_);
	~COpertaionPair();

	//回滚本操作，即本操作执行前的状态。
	bool Rollback(void);
	//执行本操作
	bool Excute(void);

	//本操作是否已执行
	bool IsExcuted(void){return m_bExcuted;};

private:
	IBaseOperation *m_do;
	IBaseOperation *m_undo;

	bool m_bExcuted;	//true, 已执行；false, 处于回滚后的状态。
};
