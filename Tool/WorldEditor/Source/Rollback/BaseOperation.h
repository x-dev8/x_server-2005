/*----------------------------------------------------------
desc	: �༭���и��ֲ����Ľӿ��ࡣ
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

	//ÿ��operationӦ�ñ�֤��û�гɹ���������Լ��ع��������ı����ݿ⣩��
	virtual bool Excute(void) = 0;

	void SetStatus(bool bExcuted_);

protected:
	bool m_bExcuted;
};

//һ���෴�Ĳ���
class COpertaionPair
{
public:
	COpertaionPair(IBaseOperation *do_, IBaseOperation *undo_);
	~COpertaionPair();

	//�ع�����������������ִ��ǰ��״̬��
	bool Rollback(void);
	//ִ�б�����
	bool Excute(void);

	//�������Ƿ���ִ��
	bool IsExcuted(void){return m_bExcuted;};

private:
	IBaseOperation *m_do;
	IBaseOperation *m_undo;

	bool m_bExcuted;	//true, ��ִ�У�false, ���ڻع����״̬��
};
