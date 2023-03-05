/*
 *	
 */

#pragma once
#include "GlobalDef.h"
#include <map>
#include <windows.h>
#include <functional>
#include <vector>

#include "Array.h"

//-------------------------------------------------------------------------
struct ItemMakeRule
{
	int ItemID1;	//Դ����1
	int	ItemNum1;
	//
	int ItemID2;	//Դ����2
	int	ItemNum2;
	//
	int ItemID3;	//Դ����3
	int	ItemNum3;
	//
	int	SuccRate;	//�ɹ��Ļ���
	//
	int MakeItemID;	//����ɵ�Ŀ�꣬��Ʒ���
};
class	ItemMake
{
	enum
	{
		MaxItemMakeRule = 1024,
	};
private:
	//ItemMakeRule	m_Rule[MaxItemMakeRule];
	Array<ItemMakeRule, MaxItemMakeRule>	m_Rule;
protected:
public:
	ItemMake(void);
	~ItemMake(void);
	bool	ReadSlkFile(char *filename);
	//
	bool	MakeItem(int item1, int item1num, int item2, int item2num,int item3, int item3num, int *pMakeItem);
};

//-------------------------------------------------------------------------
//	End.
//-------------------------------------------------------------------------
