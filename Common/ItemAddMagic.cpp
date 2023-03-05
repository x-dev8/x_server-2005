/*
 *	���ߺϳ�(Ϊ��������MF����)
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
		"weapon",	//����
		"cloth",	//�·�
		"shoes",	//Ь��
		"glove",	//����
		"armet",	//ͷ��
		"special"	//��Ʒ
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
		//���߱��
		reader.GetIntField(iCol, iValue);
		iCol++;
		iIndex = iValue - MagicItemBeginIndex;
		//
		if (iIndex <0 || iIndex>=MaxMagicItemAddRule)
		{
			assert(false && "itemaddmagic.cpp index error!!");
			continue;
		}
		//��������
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
		//�ı����Ŀ
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
		
		//������ֵ��Χ��С
		reader.GetIntField(iCol, iIndex);
		m_MagicAddData[iIndex].RangeData[ItemType][SpecialType].AddMagicRangeMin = iIndex;
		iCol++;
		//������ֵ��Χ���
		reader.GetIntField(iCol, iIndex);
		m_MagicAddData[iIndex].RangeData[ItemType][SpecialType].AddMagicRangeMax = iIndex;
		iCol++;
		//�ı䷶Χ��С
		reader.GetIntField(iCol, iIndex);
		m_MagicAddData[iIndex].RangeData[ItemType][SpecialType].AddDataRangeMin = iIndex;
		iCol++;
		//�ı䷶Χ���
		reader.GetIntField(iCol, iIndex);
		m_MagicAddData[iIndex].RangeData[ItemType][SpecialType].AddDataRangeMax = iIndex;
		iCol++;
	}
	return false;
	unguard;
}
//�ϳɷ������Ե���������
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
