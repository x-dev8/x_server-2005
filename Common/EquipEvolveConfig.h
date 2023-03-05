#ifndef __EQUIP_EVOLVE_CONFIG_H__
#define __EQUIP_EVOLVE_CONFIG_H__

#pragma once

#include <string>
#include <vector>
#include <map>

#include "GlobalDef.h"


//装备加工配置文件集
class EquipEvolveConfig
{
public:
	//打孔配置
	struct SEquipStiletto
	{
		uint8	nHoleIndex;		//孔位号,从1开始
		uint16	nSuccessRate;	//成功率
		uint8	nCostType;		//花费类型
		uint32	nCostValue;		//花费

		SEquipStiletto()
		{
			Clear();
		}

		void Clear()
		{
			nHoleIndex = 0;
			nSuccessRate = 0;
			nCostType = 0;
			nCostValue = 0;
		}
	};
	typedef std::vector<SEquipStiletto>			EquipStilettoContainer;
	typedef EquipStilettoContainer::iterator	IterEquipStilettoContainer;

	//镶嵌配置
	struct SEquipInlayRate
	{
		uint8	nMaterialType;
		uint16	nSuccessRate;
		
		SEquipInlayRate()
		{
			Clear();
		}

		void	Clear()
		{
			nMaterialType = 0;
			nSuccessRate = 0;
		}
	};
	typedef std::vector<SEquipInlayRate>		EquipInlayRateContainer;
	typedef EquipInlayRateContainer::iterator	IterEquipInlayRateContainer;

	//未知鉴定
	struct SEquipUnknowIdentify
	{
		enum EConstDefine
		{
			ECD_GetItemMaxCount = 7,	//鉴定结果集数量上限
		};

		struct SGetItem
		{
			uint16	nGetItemID;		//鉴定结果装备ID集合
			uint16	nGetItemRate;	//鉴定相应结果的概率
		};
		typedef std::vector<SGetItem>	GetItemList;
		typedef GetItemList::iterator	IterGetItemList;

		uint16	nItemID;			//待鉴定装备ID
		GetItemList	getItemList;	//鉴定可得到的装备列表
		uint8	nCostType;			//花费类型
		int		nCostValue;			//花费值
		bool	blIsStarRandom;		//鉴定出的星级是否随机
		uint8	nStarLevel;			//指定或随机星级的值
		bool	blIsBound;			//鉴定出的装备是否为绑定的

		SEquipUnknowIdentify()
		{
			Clear();
		}

		void Clear()
		{
			memset( this, 0, sizeof(SEquipUnknowIdentify) );
		}
	};
	typedef std::vector<SEquipUnknowIdentify>		EquipUnknowIdentifyContainer;
	typedef EquipUnknowIdentifyContainer::iterator	IterEquipUnknowIdentifyContainer;

public:
	static EquipEvolveConfig& Instance()
	{
		static EquipEvolveConfig s_xConfig;
		return s_xConfig;
	}

	bool LoadStilettoConfig(const char *szFile);
	bool LoadInlayRateConfig(const char *szFile);
	bool LoadUnknowIdentifyConfig(const char *szFile);

	SEquipStiletto*			GetStiletto(uint8 holeIndex);
	SEquipInlayRate*		GetInlayRate(uint8 materialType);
	SEquipUnknowIdentify*	GetUnknowIdentify(uint16 nItemID);

protected:
	EquipEvolveConfig()
	{
		m_vecStiletto.clear();
		m_vecInlayRate.clear();
		m_vecUnknowIdentify.clear();
	}

private:
	EquipStilettoContainer			m_vecStiletto;
	EquipInlayRateContainer			m_vecInlayRate;
	EquipUnknowIdentifyContainer	m_vecUnknowIdentify;
};

#define theEquipEvolveConfig EquipEvolveConfig::Instance()   //实例接口

#endif

