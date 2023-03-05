/*
 *	道具打造相关的数据
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
		//编号
		reader.GetIntField(iCol, iIndex);
		iCol++;
		if (iIndex>=0 && iIndex<MaxItemMakeRule)
		{
			//物品1
			reader.GetIntField(iCol, iValue);
			m_Rule[iIndex].ItemID1 = iValue;
			iCol++;
			//物品1数目
			reader.GetIntField(iCol, iValue);
			m_Rule[iIndex].ItemNum1 = iValue;
			iCol++;
			//物品2
			reader.GetIntField(iCol, iValue);
			m_Rule[iIndex].ItemID2 = iValue;
			iCol++;
			//物品2数目
			reader.GetIntField(iCol, iValue);
			m_Rule[iIndex].ItemNum2 = iValue;
			iCol++;
			//物品3
			reader.GetIntField(iCol, iValue);
			m_Rule[iIndex].ItemID3 = iValue;
			iCol++;
			//物品3数目
			reader.GetIntField(iCol, iValue);
			m_Rule[iIndex].ItemNum2 = iValue;
			iCol++;
			//打造的目标物品
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
	//如果失败就是生成第一种道具
	*pMakeItem = item1;
	//在表中寻找对应的合成规则的
	for (int i=0; i<MaxItemMakeRule; i++)
	{
		if ((item1 == m_Rule[i].ItemID1) &&
		    (item2 == m_Rule[i].ItemID2) &&
		    (item3 == m_Rule[i].ItemID3))
		{
			//判断数目是否正确
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
