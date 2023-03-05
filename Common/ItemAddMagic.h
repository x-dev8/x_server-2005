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
	int AddMagicRangeMin;	//���Ӹ����Ե����������ֵ��Χ
	int AddMagicRangeMax;
	//
	int	AddDataRangeMin;	//��������,�ı����ֵ��Χ
	int	AddDataRangeMax;
};
struct  MagicItemData
{
	MagicItemData() : RangeData("[ItemAddMagic.h]ItemMagicAdd.MagicItemData.RangeData")
	{
	}
	enum 
	{
		ItemTypeWeapon = 0,		  //����
		ItemTypeCloth = 0,		  //�·�
		ItemTypeShoes= 0,		  //Ь��
		ItemTypeGlove = 0,		  //����
		ItemTypeArmet = 0,		  //ͷ��	
		ItemTypeAccouterment = 0, //��Ʒ
		MaxMagicItemType = 6,//����, �·�, Ь��, ����, ͷ��, ��Ʒ
		MaxMagicSpeiclNum = 7,
	};
	//
	int		ItemID;		//��Ӧ�ĵ��߱��
	//
	//MagicItemRangeData  RangeData[MaxMagicItemType][MaxMagicSpeiclNum];
	Array< Array<MagicItemRangeData, MaxMagicSpeiclNum>, MaxMagicItemType>	RangeData;//zizi add
	//
};
//���ߵĺϳ�
class	ItemMagicAdd
{
private:
	enum 
	{
		MagicItemBeginIndex = 1000, //���������ڵ��߱��еĿ�ʼλ��
		MaxMagicItemAddRule = 1024,	//���ϳɵ��ߵ�����
	};
	//�ڴ������
//	CFlyMemAllocer *m_pMemAllocer;
	//
	//MagicItemData m_MagicAddData[MaxMagicItemAddRule];   //���ߺϳɵĹ�������
	Array< MagicItemData, MaxMagicItemAddRule>	m_MagicAddData;//zizi add
protected:
public:
	ItemMagicAdd();
	~ItemMagicAdd();
	//
	bool	ReadSlkFile(char *szFilename);
	//�ϳɷ������Ե���������
	bool	ItemAddMagic(ItemDefine::SItemCommon *pMagicItem, ItemDefine::SItemCommon *pWeaponItem);
};





//-------------------------------------------------------------------------
//	End.
//-------------------------------------------------------------------------
