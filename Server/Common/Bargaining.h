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
            char szItemData[400];       // ��Ʒ��data �ṹ��С(SMountItem = 267  SChatItem = 123)

            bool SetItemData( void* pItemData, int nSize )        // ����itemdata���ṹ��
            {
                memset( szItemData, 0, sizeof( szItemData ) );

                if ( pItemData == NULL || nSize > sizeof( szItemData ) )
                { return false; }

                memcpy_s( szItemData, sizeof( szItemData ), pItemData, nSize );
                return true;
            }

            bool GetItemData( void* pItemData, int nSize )        // �ӽṹ�л��itemdata
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
        DWORD             dwStartTime;  // ��ʼ���׵�ʱ��
    };

public:
    BargainingManager();
    ~BargainingManager();
    bool IsThePlayerBargainingNow( unsigned int nPlayerId );                           // ����Ƿ��ڽ���
    bool IsThePlayerBargainingNow( unsigned int nPlayer1Id, unsigned int nPlayer2Id ); // ����Ƿ��ڽ���

    bool ThePlayerInSameRoom( const unsigned int nPlayer1Id,const unsigned int nPlayer2Id );
    int  GetBargainingerId( const unsigned int nPlayerId );                            // �õ����׶����ID,��ʧ�ܷ���-1
    void UpDateBargaining();                                                           // ���½���

    bool AddRoom( unsigned int nPlayer1Id, unsigned int nPlayer2Id );                  // ����һ������
    bool DelRoom( unsigned int nPlayerId );                                            // ɾ��һ������

    unsigned char BargainingNow( BaseCharacter* pSend, BaseCharacter* pRec, MsgBargainingNow* pBargainingNow );

    bool IsComplete_First( const unsigned int nPlayerId );
    bool SetComplete_First( const int nPlayerId, bool bComplete );// ����ֵΪ,�Է��Ƿ�Ҳ�����.

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
