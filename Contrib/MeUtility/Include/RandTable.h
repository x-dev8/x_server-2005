/********************************************************************
    Filename:    randtable.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#pragma once

#define		MAX_RAND_TABLE_NUM	10000
class	CRandTable
{
private:
	int	m_RandTable[MAX_RAND_TABLE_NUM];	//���������
	int	m_TableNum;		//������������Ŀ
	int	m_CurPos;		//��ǰ��λ��
protected:
public:
	CRandTable(void);
	~CRandTable(void);
	int	rand(void);
};
