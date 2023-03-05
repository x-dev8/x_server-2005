/********************************************************************
    Filename:    DropCommonItem.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_DROPCOMMONITEM_CONFIG_H__
#define __GAMESERVER_DROPCOMMONITEM_CONFIG_H__

#pragma once

#include <vector>
#include "DropItem.h"

class DropCommonItemConfig 
{
public:

	inline static DropCommonItemConfig& Instance()
	{
		static DropCommonItemConfig s_xDropCommonItemConfig;
		return s_xDropCommonItemConfig;
	}

    virtual bool LoadData(const char* szFileName);
	virtual bool LoadConfig(const char* szFileName);
	virtual bool SaveConfig(const char* szFileName);

    int  GetIndexByPackId( int nPackId );
	SCommonDrop* GetSCommonDropByIndex(int nIndex);
	SCommonDrop* GetSCommonDropByPackId(int nPackId);

	const std::vector<SCommonDrop>& GetDropCommonItemConfig() const{ return m_vtDropItem; }

private:
	DropCommonItemConfig() {}
    std::vector<SCommonDrop> m_vtDropItem;
};

#define theDropCommonItemConfig DropCommonItemConfig::Instance()   //ÊµÀý½Ó¿Ú

#endif // __GAMESERVER_DROPCOMMONITEM_H__
