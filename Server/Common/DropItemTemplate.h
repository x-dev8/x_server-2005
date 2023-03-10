/********************************************************************
	Filename: 	DropItemTemplate.h
	AuthorMail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_DROPITEMTEMPLATE_H__
#define __GAMESERVER_DROPITEMTEMPLATE_H__

#pragma once

#include "MeRTLibsServer.h"
#include "TSingleton.h"

class CItemDropTemplate
{
public:
    class ItemDropRate
    {
    public:
        std::string strName;
        float fRate;
    };

    CItemDropTemplate();
    virtual ~CItemDropTemplate();

    bool LoadFromFile( const char *szFileName );

    ItemDropRate *GetItemInfo( int i )
    {
        if( i<0 || i>=Size() )
            return NULL;

        return &m_vecItemDropRate[i];
    }

    int Size() {
        return (int)m_vecItemDropRate.size();
    }

protected:

    std::vector<ItemDropRate> m_vecItemDropRate;

};

CItemDropTemplate *GetItemDropTemplate( const char *szTempName );

#endif // __GAMESERVER_DROPITEMTEMPLATE_H__

