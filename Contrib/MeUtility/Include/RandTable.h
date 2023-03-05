/********************************************************************
    Filename:    randtable.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#pragma once

#define		MAX_RAND_TABLE_NUM	10000
class	CRandTable
{
private:
	int	m_RandTable[MAX_RAND_TABLE_NUM];	//保留随机数
	int	m_TableNum;		//随机数的最大数目
	int	m_CurPos;		//但前的位置
protected:
public:
	CRandTable(void);
	~CRandTable(void);
	int	rand(void);
};
