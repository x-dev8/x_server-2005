/********************************************************************
    Filename:     DropMonsterItem.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_DROPMONSTERITEM_CONFIG_H__
#define __GAMESERVER_DROPMONSTERITEM_CONFIG_H__

#pragma once

#include <vector>
#include "DropItem.h"

class DropMonsterItemConfig 
{
public:
   
	inline static DropMonsterItemConfig& Instance()
	{
		static DropMonsterItemConfig s_xDropMonsterItemConfig;
		return s_xDropMonsterItemConfig;
	}

    virtual bool LoadData(const char* szFileName);
	virtual bool LoadConfig(const char* szFileName);
	virtual bool SaveConfig(const char* szFileName);


	SMonsterDrop* GetSMonsterDropByIndex(int nIndex);
	SMonsterDrop* GetSMonsterDropByMonsterId(int nMonsterId);

	std::vector<SMonsterDrop>& GetDropMonsterItemConfig() { return m_vtDropItem; }

private:
	DropMonsterItemConfig() {}
    std::vector<SMonsterDrop> m_vtDropItem;
};

#define theDropMonsterItemConfig DropMonsterItemConfig::Instance()   //ÊµÀý½Ó¿Ú

#endif // __GAMESERVER_DROPMONSTERITEM_H__
