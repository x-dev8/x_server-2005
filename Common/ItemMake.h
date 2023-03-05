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
	int ItemID1;	//源材料1
	int	ItemNum1;
	//
	int ItemID2;	//源材料2
	int	ItemNum2;
	//
	int ItemID3;	//源材料3
	int	ItemNum3;
	//
	int	SuccRate;	//成功的机率
	//
	int MakeItemID;	//打造成的目标，物品编号
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
