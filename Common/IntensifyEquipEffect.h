#ifndef __INTENSIFYEFFECT_H__
#define __INTENSIFYEFFECT_H__

#pragma once

#include <string>
#include <vector>
#include <map>

struct WEAPONINTENSIFY_INFO
{

  WEAPONINTENSIFY_INFO()
  {
	   MaxIntensifyLev = 0;
	   MinIntensifyLev = 0;
	   MaxWeapoinID    = 0; 
	   MinWeapoinID    = 0;
	   EffectID = -1;
  }

  int MaxIntensifyLev; 
  int MinIntensifyLev; 
  int MaxWeapoinID;    
  int MinWeapoinID;
  int EffectID;
};

struct EQUIPINTENSIFY_INFO
{
	EQUIPINTENSIFY_INFO()
	{
		EffectPath = "NULL";
		MinIntensifyLev = 0;
	}

	std::string EffectPath;
	int  MinIntensifyLev;

};

typedef std::vector<WEAPONINTENSIFY_INFO> WEAPON_INTENSIFY_EFFECT_MGR;
typedef std::vector<EQUIPINTENSIFY_INFO> EQUIP_INTENSIFY_EFFECT_MGR;

class IntensifyEquip
{

public:
	static IntensifyEquip& Instance()
	{
		static IntensifyEquip s_xConfig;
		return s_xConfig;
	}

	//����װ��ǿ�������ļ�
	bool LoadIntensifyEffectConfig(const char *szFile);

	/*��������ǿ����Чģ��id , 
	  des_EffectID : ���ص�������Чid
	  weaponId :��ǰǿ�������� id 
	  weapon_IntensifyLev :��ǰ����ǿ���ĵȼ�
	*/ 
	bool FindWeaponEffectID(int &des_EffectID ,int weaponId , int weapon_IntensifyLev);

    //����ȫ��װ�������ǿ���ȼ� ����ȫ��ǿ����Ч·��
	std::string GetEquipIntensifyModelPath(int LowIntensify);
	

private:
	//����ǿ����Ч����
	WEAPON_INTENSIFY_EFFECT_MGR m_WeaponEffectMgr;
	 EQUIP_INTENSIFY_EFFECT_MGR  m_EquipEffectMgr;

};

#define theIntensifyEffect IntensifyEquip::Instance()   //ʵ���ӿ�

#endif

