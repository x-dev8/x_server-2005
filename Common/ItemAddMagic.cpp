/*
 *	道具合成(为道具增加MF属性)
 */
#include "ItemAddmagic.h"
#include "slkReader.h"
#include "Helper.h"
#include "FuncPerformanceLog.h"



//static CFlyNormalAllocer g_normalAllocer;

ItemMagicAdd::ItemMagicAdd(): m_MagicAddData("[ItemAddMagic.h]ItemMagicAdd.m_MagicAddData")
{
	guardfunc;
	//m_pMemAllocer = &g_normalAllocer;
	unguard;
}
ItemMagicAdd::~ItemMagicAdd()
{
	guardfunc;
	unguard;
}
//
bool	ItemMagicAdd::ReadSlkFile(char *szFilename)
{
	guardfunc;
	static char* (s_szItemType[]) = 
	{
		"weapon",	//武器
		"cloth",	//衣服
		"shoes",	//鞋子
		"glove",	//手套
		"armet",	//头盔
		"special"	//饰品
	};
	static char* (s_szDataType[]) = 
	{
		"special1",
		"special2",
		"special3",
		"special4",
		"special5",
		"special6"
	};
	//
	int iCol;
	int iValue;
	int iIndex;
	int iRet;
	int i;
	int	ItemType, SpecialType;
	//
	//memset(m_MagicAddData, 0 , sizeof(MagicItemData) * MaxMagicItemAddRule);
	m_MagicAddData.Clear();	//zizi add
	//
	CSlkReader reader;
	if (!reader.ReadFromFile(szFilename))
		return false;
	//
	i = 0;
	while ( CSlkReader::ret_readover != ( iRet = reader.GotoNextLine( i++ ) ) ) 
	{
		if( CSlkReader::ret_nothisline == iRet )
			continue;
		//
		iCol = 1;
		//道具编号
		reader.GetIntField(iCol, iValue);
		iCol++;
		iIndex = iValue - MagicItemBeginIndex;
		//
		if (iIndex <0 || iIndex>=MaxMagicItemAddRule)
		{
			assert(false && "itemaddmagic.cpp index error!!");
			continue;
		}
		//道具类型
		std::string	 szItemType;
		reader.GetStringField(iCol, szItemType);
		ItemType = HelperFunc::GetIDByConstString((char*)szItemType.c_str(), s_szItemType, sizeof(s_szItemType)/sizeof(char*) );
		iCol++;
		if (ItemType<0 || ItemType>= MagicItemData::MaxMagicItemType)
		{
			assert(false && "itemaddmagic.cpp magic type error!!");
			continue;
		}
		//
		//改变的项目
		std::string	 szSpecialType = NULL;
		reader.GetStringField(iCol, szSpecialType);
		SpecialType = HelperFunc::GetIDByConstString((char*)szSpecialType.c_str(), s_szDataType, sizeof(s_szDataType)/sizeof(char*) );
		iCol++;
		if (SpecialType<0 || SpecialType >= MagicItemData::MaxMagicSpeiclNum)
		{
			assert(false && "itemaddmagic.cpp special  type error!!");
			continue;
		}
		//
		m_MagicAddData[iIndex].ItemID = iValue;
		
		//几率数值范围最小
		reader.GetIntField(iCol, iIndex);
		m_MagicAddData[iIndex].RangeData[ItemType][SpecialType].AddMagicRangeMin = iIndex;
		iCol++;
		//几率数值范围最大
		reader.GetIntField(iCol, iIndex);
		m_MagicAddData[iIndex].RangeData[ItemType][SpecialType].AddMagicRangeMax = iIndex;
		iCol++;
		//改变范围最小
		reader.GetIntField(iCol, iIndex);
		m_MagicAddData[iIndex].RangeData[ItemType][SpecialType].AddDataRangeMin = iIndex;
		iCol++;
		//改变范围最大
		reader.GetIntField(iCol, iIndex);
		m_MagicAddData[iIndex].RangeData[ItemType][SpecialType].AddDataRangeMax = iIndex;
		iCol++;
	}
	return false;
	unguard;
}
//合成法术属性到道具上面
bool	ItemMagicAdd::ItemAddMagic(ItemDefine::SItemCommon *pMagicItem, ItemDefine::SItemCommon *pWeaponItem)
{
	guardfunc;
	return false;
	unguard;
}
//

//-------------------------------------------------------------------------
//	End.
//-------------------------------------------------------------------------
