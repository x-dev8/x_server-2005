#ifndef __EQUIP_EVOLVE_CONFIG_H__
#define __EQUIP_EVOLVE_CONFIG_H__

#pragma once

#include <string>
#include <vector>
#include <map>

#include "GlobalDef.h"


//װ���ӹ������ļ���
class EquipEvolveConfig
{
public:
	//�������
	struct SEquipStiletto
	{
		uint8	nHoleIndex;		//��λ��,��1��ʼ
		uint16	nSuccessRate;	//�ɹ���
		uint8	nCostType;		//��������
		uint32	nCostValue;		//����

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

	//��Ƕ����
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

	//δ֪����
	struct SEquipUnknowIdentify
	{
		enum EConstDefine
		{
			ECD_GetItemMaxCount = 7,	//�����������������
		};

		struct SGetItem
		{
			uint16	nGetItemID;		//�������װ��ID����
			uint16	nGetItemRate;	//������Ӧ����ĸ���
		};
		typedef std::vector<SGetItem>	GetItemList;
		typedef GetItemList::iterator	IterGetItemList;

		uint16	nItemID;			//������װ��ID
		GetItemList	getItemList;	//�����ɵõ���װ���б�
		uint8	nCostType;			//��������
		int		nCostValue;			//����ֵ
		bool	blIsStarRandom;		//���������Ǽ��Ƿ����
		uint8	nStarLevel;			//ָ��������Ǽ���ֵ
		bool	blIsBound;			//��������װ���Ƿ�Ϊ�󶨵�

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

#define theEquipEvolveConfig EquipEvolveConfig::Instance()   //ʵ���ӿ�

#endif

