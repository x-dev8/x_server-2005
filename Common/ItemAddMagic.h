/*
 *	
 */
#pragma once
#include "GlobalDef.h"
#include <map>
#include <windows.h>
#include <functional>
#include <vector>
#include "ItemDetail.h"

struct MagicItemRangeData
{
	int AddMagicRangeMin;	//增加该属性的随机数，数值范围
	int AddMagicRangeMax;
	//
	int	AddDataRangeMin;	//该项属性,改变的数值范围
	int	AddDataRangeMax;
};
struct  MagicItemData
{
	MagicItemData() : RangeData("[ItemAddMagic.h]ItemMagicAdd.MagicItemData.RangeData")
	{
	}
	enum 
	{
		ItemTypeWeapon = 0,		  //武器
		ItemTypeCloth = 0,		  //衣服
		ItemTypeShoes= 0,		  //鞋子
		ItemTypeGlove = 0,		  //手套
		ItemTypeArmet = 0,		  //头盔	
		ItemTypeAccouterment = 0, //饰品
		MaxMagicItemType = 6,//武器, 衣服, 鞋子, 手套, 头盔, 饰品
		MaxMagicSpeiclNum = 7,
	};
	//
	int		ItemID;		//对应的道具编号
	//
	//MagicItemRangeData  RangeData[MaxMagicItemType][MaxMagicSpeiclNum];
	Array< Array<MagicItemRangeData, MaxMagicSpeiclNum>, MaxMagicItemType>	RangeData;//zizi add
	//
};
//道具的合成
class	ItemMagicAdd
{
private:
	enum 
	{
		MagicItemBeginIndex = 1000, //法术道具在道具表中的开始位置
		MaxMagicItemAddRule = 1024,	//最多合成道具的种类
	};
	//内存分配器
//	CFlyMemAllocer *m_pMemAllocer;
	//
	//MagicItemData m_MagicAddData[MaxMagicItemAddRule];   //道具合成的规则数据
	Array< MagicItemData, MaxMagicItemAddRule>	m_MagicAddData;//zizi add
protected:
public:
	ItemMagicAdd();
	~ItemMagicAdd();
	//
	bool	ReadSlkFile(char *szFilename);
	//合成法术属性到道具上面
	bool	ItemAddMagic(ItemDefine::SItemCommon *pMagicItem, ItemDefine::SItemCommon *pWeaponItem);
};





//-------------------------------------------------------------------------
//	End.
//-------------------------------------------------------------------------
