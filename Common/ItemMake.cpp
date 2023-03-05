/*
 *	���ߴ�����ص�����
 */
#include "ItemMake.h"
#include "slkReader.h"
#include "FuncPerformanceLog.h"



ItemMake::ItemMake(void) : m_Rule("[ItemMake.h]ItemMake.m_Rule")
{
	guardfunc;
	unguard;
}
ItemMake::~ItemMake(void)
{

	guardfunc;
	unguard;
}
bool	ItemMake::ReadSlkFile(char *szFile)
{
	guardfunc;
	int iCol;
	int iValue;
	int iIndex;
	int iRet;
	int i;
	//
	//memset(m_Rule, 0, sizeof(ItemMakeRule)*MaxItemMakeRule);
	m_Rule.Clear();	//zizi add
	//
	CSlkReader reader;
	if (!reader.ReadFromFile(szFile))
		return false;
	//
	i = 0;
	while ( CSlkReader::ret_readover != ( iRet = reader.GotoNextLine( i++ ) ) ) 
	{
		if( CSlkReader::ret_nothisline == iRet )
			continue;
		//
		iCol = 1;
		//���
		reader.GetIntField(iCol, iIndex);
		iCol++;
		if (iIndex>=0 && iIndex<MaxItemMakeRule)
		{
			//��Ʒ1
			reader.GetIntField(iCol, iValue);
			m_Rule[iIndex].ItemID1 = iValue;
			iCol++;
			//��Ʒ1��Ŀ
			reader.GetIntField(iCol, iValue);
			m_Rule[iIndex].ItemNum1 = iValue;
			iCol++;
			//��Ʒ2
			reader.GetIntField(iCol, iValue);
			m_Rule[iIndex].ItemID2 = iValue;
			iCol++;
			//��Ʒ2��Ŀ
			reader.GetIntField(iCol, iValue);
			m_Rule[iIndex].ItemNum2 = iValue;
			iCol++;
			//��Ʒ3
			reader.GetIntField(iCol, iValue);
			m_Rule[iIndex].ItemID3 = iValue;
			iCol++;
			//��Ʒ3��Ŀ
			reader.GetIntField(iCol, iValue);
			m_Rule[iIndex].ItemNum2 = iValue;
			iCol++;
			//�����Ŀ����Ʒ
			reader.GetIntField(iCol, iValue);
			m_Rule[iIndex].SuccRate = iValue;
			iCol++;
		}
	}
	//
	return false;
	unguard;
}
bool	ItemMake::MakeItem(int item1, int item1num, int item2, int item2num,int item3, int item3num, int *pMakeItem)
{
	guardfunc;
	if (NULL == pMakeItem)
		return false;
	//
	//���ʧ�ܾ������ɵ�һ�ֵ���
	*pMakeItem = item1;
	//�ڱ���Ѱ�Ҷ�Ӧ�ĺϳɹ����
	for (int i=0; i<MaxItemMakeRule; i++)
	{
		if ((item1 == m_Rule[i].ItemID1) &&
		    (item2 == m_Rule[i].ItemID2) &&
		    (item3 == m_Rule[i].ItemID3))
		{
			//�ж���Ŀ�Ƿ���ȷ
			if ((item1num >= m_Rule[i].ItemNum1) &&
			    (item1num >= m_Rule[i].ItemNum1) &&
			    (item1num >= m_Rule[i].ItemNum1))
			{
				*pMakeItem = m_Rule[i].MakeItemID;
				return true;
			}
			//
			break;
		}
	}
	//
	return false;
	unguard;
}





//-------------------------------------------------------------------------
//	End.
//-------------------------------------------------------------------------
