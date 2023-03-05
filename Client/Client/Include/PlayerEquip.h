#pragma once
#include "GlobalDef.h"

struct CPlayer_SEquipment
{

	CPlayer_SEquipment()
	{
		Reset();
		/*stEquipItemType = ErrorUnsignedShortID;*/
	}

	void Reset()
	{
		iModelID = InvalidLogicNumber;
		iModelID2 = InvalidLogicNumber;
		iModelID3 = InvalidLogicNumber;
	}
	//装备物品
	SCharItem item;
	//装备的模型ID
	int						iModelID;
	int						iModelID2; //双手武器，和头上饰物
	int						iModelID3; //收刀后的模型
	//short  stEquipItemType;//装备类型
	//效果??
};