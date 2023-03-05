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

	//加载装备强化配置文件
	bool LoadIntensifyEffectConfig(const char *szFile);

	/*查找武器强化特效模型id , 
	  des_EffectID : 返回的武器特效id
	  weaponId :当前强化的武器 id 
	  weapon_IntensifyLev :当前武器强化的等级
	*/ 
	bool FindWeaponEffectID(int &des_EffectID ,int weaponId , int weapon_IntensifyLev);

    //根据全身装备的最低强化等级 返回全身强化特效路径
	std::string GetEquipIntensifyModelPath(int LowIntensify);
	

private:
	//武器强化特效容器
	WEAPON_INTENSIFY_EFFECT_MGR m_WeaponEffectMgr;
	 EQUIP_INTENSIFY_EFFECT_MGR  m_EquipEffectMgr;

};

#define theIntensifyEffect IntensifyEquip::Instance()   //实例接口

#endif

