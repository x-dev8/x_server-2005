#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "RandTable.h"

CRandTable::CRandTable(void)
{
	m_TableNum = MAX_RAND_TABLE_NUM;	//随机数的最大数目
	m_CurPos = 0;
	//
	for (int i=0; i<m_TableNum; i++)
		m_RandTable[i] = i;
	//
	srand( (unsigned)time( NULL ) );
	//
	int swap_pos;
	int val=0;
	for (int i=0; i<m_TableNum; i++)
	{
		swap_pos = rand()%m_TableNum;
		val = m_RandTable[i];
		m_RandTable[i] = m_RandTable[swap_pos];
		m_RandTable[swap_pos] = val;
	}
}
CRandTable::~CRandTable(void)
{
}
int	CRandTable::rand(void)
{
	m_CurPos ++;
	if (m_CurPos >= m_TableNum)
		m_CurPos =0;
	return m_RandTable[m_CurPos];
}
//------------------------------------------------------------------------------------------------
//	End.
//------------------------------------------------------------------------------------------------
