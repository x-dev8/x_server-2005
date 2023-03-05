/********************************************************************
    Filename:    Bargaining.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_BARGAINING_H__
#define __GAMESERVER_BARGAINING_H__

#pragma once

#include "MeRTLibsServer.h"
#include "GamePlayer.h"

class BargainingManager
{
public:
    struct stRoom
    {
        stRoom()
        {
            nPlayer1 = nPlayer2 = 0;
            bPlayer1Complete_First = bPlayer2Complete_First = false;
            bPlayer1Complete_Last = bPlayer2Complete_Last = false;
            dwPlayer1Money = dwPlayer2Money = 0;
            dwPlayer1RMB = dwPlayer2RMB = 0;
            m_lPlayer1Goods.clear();
            m_lPlayer2Goods.clear();
        }        
        struct stItem
        {
            stItem()
            {
                memset( szItemData, 0, sizeof( szItemData ) );
            }
            unsigned  char ucItemBagType;
            int       index;
            char szItemData[400];       // 物品的data 结构大小(SMountItem = 267  SChatItem = 123)

            bool SetItemData( void* pItemData, int nSize )        // 保存itemdata到结构中
            {
                memset( szItemData, 0, sizeof( szItemData ) );

                if ( pItemData == NULL || nSize > sizeof( szItemData ) )
                { return false; }

                memcpy_s( szItemData, sizeof( szItemData ), pItemData, nSize );
                return true;
            }

            bool GetItemData( void* pItemData, int nSize )        // 从结构中获得itemdata
            {
                memset( pItemData, 0, nSize );

                if ( pItemData == NULL || nSize > sizeof( szItemData ) )
                { return false; }

                memcpy_s( pItemData, nSize, szItemData, nSize );
                return true;
            }
        };

        unsigned int      nPlayer1;
        unsigned int      nPlayer2;
        bool              bPlayer1Complete_First;
        bool              bPlayer2Complete_First;
        bool              bPlayer1Complete_Last;
        bool              bPlayer2Complete_Last;
        std::list<stItem> m_lPlayer1Goods;
        std::list<stItem> m_lPlayer2Goods;
        DWORD             dwPlayer1Money;
        DWORD             dwPlayer2Money;
        DWORD             dwPlayer1RMB;
        DWORD             dwPlayer2RMB;
        DWORD             dwStartTime;  // 开始交易的时间
    };

public:
    BargainingManager();
    ~BargainingManager();
    bool IsThePlayerBargainingNow( unsigned int nPlayerId );                           // 玩家是否在交易
    bool IsThePlayerBargainingNow( unsigned int nPlayer1Id, unsigned int nPlayer2Id ); // 玩家是否在交易

    bool ThePlayerInSameRoom( const unsigned int nPlayer1Id,const unsigned int nPlayer2Id );
    int  GetBargainingerId( const unsigned int nPlayerId );                            // 得到交易对像的ID,如失败反回-1
    void UpDateBargaining();                                                           // 更新交易

    bool AddRoom( unsigned int nPlayer1Id, unsigned int nPlayer2Id );                  // 增加一个房间
    bool DelRoom( unsigned int nPlayerId );                                            // 删除一个房间

    unsigned char BargainingNow( BaseCharacter* pSend, BaseCharacter* pRec, MsgBargainingNow* pBargainingNow );

    bool IsComplete_First( const unsigned int nPlayerId );
    bool SetComplete_First( const int nPlayerId, bool bComplete );// 反回值为,对方是否也完成了.

    bool IsComplete_Last( const unsigned int nPlayerId );
    bool SetComplete_Last( const int nPlayerId, bool bComplete );

    bool IsCanExChange( stRoom* pRoom, GamePlayer* pPlayer1, GamePlayer* pPlayer2 );
    bool ExChange( GamePlayer* pPlayer1, GamePlayer* pPlayer2 );

private:
    stRoom* GetRoom( const unsigned int nPlayerId );

private:
    typedef std::list<stRoom>       RoomContainer;
    typedef RoomContainer::iterator ItRoomContainer;
    RoomContainer m_lRooms;

    typedef std::list<stRoom::stItem>   RoomItemContainer;
    typedef RoomItemContainer::iterator ItrRoomItemContainer;
};

BargainingManager&  GetBargainingManager();

#endif // __GAMESERVER_BARGAINING_H__
