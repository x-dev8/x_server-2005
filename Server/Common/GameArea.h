/********************************************************************
    Filename:     GameArea.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_GAMEAREA_H__
#define __GAMESERVER_GAMEAREA_H__

#define GAME_MAXAROUNDAREANUMBER 9

#include "GameDataType.h"
#include "MeRTLibsServer.h"
#include "Memory_Pool.h"

#if 0
class GameArea : INHERIT_POOL( GameArea )
{ // ��ͼ������
public:
    enum EConstDefine
    {
        constMaxCharacters = dr_areaMaxCharacters, // ����������ɫ��
    };

public:

    DECLARE_POOL_FUNC( GameArea )

    GameArea();
    virtual ~GameArea();

    bool CharacterEnter( uint32 dwID, bool bPlayer ); // ��ɫ����
    bool CharacterLeave( uint32 dwID, bool bPlayer ); // ��ɫ�뿪

    bool SendAllInfoToChar    ( uint32 dwID );        // �������˵Ļ�����Ϣ���͸��ý�ɫ
    bool AllLeaveFromCharSight( uint32 dwID );        // �������뿪ĳ����Ұ

    bool SendSpecialInfoToChar( uint32 dwID, uint8 eLimitType );          // ��ָ������Ϣ���͸��ý�ɫ
    bool SpecialInfoLeaveFromCharSight( uint32 dwID, uint8 eLimitType );  // ָ����Ϣ�뿪��ɫ

    GameObjectIdTPL(constMaxCharacters)* GetIDTable() { return &m_CharacterTable; } // ��ý�ɫ�б�
    void AddAroundArea( int x, int y, int l, int h );                         // ������Χ����

public:
    int m_nAroundAreaId[GAME_MAXAROUNDAREANUMBER]; // ��Χ�����Id��
    int m_nAroundAreaCount;                        // ��Χ���������

private:
    GameObjectIdTPL(constMaxCharacters) m_CharacterTable; // ��ɫID��
};

#else

class GameArea : INHERIT_POOL( GameArea )
{
public:
    DECLARE_POOL_FUNC( GameArea )

    GameArea();
    virtual ~GameArea();

    // ��ɫ����
    bool CharacterEnter( GameObjectId dwID, bool bPlayer );

    // ��ɫ�뿪
    bool CharacterLeave( GameObjectId dwID, bool bPlayer );

    // �������˵Ļ�����Ϣ���͸��ý�ɫ
    bool SendAllInfoToChar( GameObjectId dwID );

    // �������뿪ĳ����Ұ
    bool AllLeaveFromCharSight( GameObjectId dwID );

    // ��ָ������Ϣ���͸��ý�ɫ
    bool SendSpecialInfoToChar( GameObjectId dwID, uint8 eLimitType );          

    // ָ����Ϣ�뿪��ɫ
    bool SpecialInfoLeaveFromCharSight( GameObjectId dwID, uint8 eLimitType );

    // �����õ�Id
    GameObjectId GetNextObjectBId( bool bFirst );

    // �õ�Object��Size
    size_t GetObjectSize() { return _objectIds.size(); }

    // �õ�Player��Size
    size_t GetPlayerObjectSize() { return _playerIds.size(); }

    // ��ӱ�ԵArea ������Χ����
    void AddAroundArea( int x, int y, int l, int h );

public:
    int m_nAroundAreaId[GAME_MAXAROUNDAREANUMBER]; // ��Χ�����Id��
    int m_nAroundAreaCount;                        // ��Χ���������

private:
    GameObjectIDSet    _objectIds; // player Npc Monster Item ��
    GameObjectIDSet    _playerIds; // player 
    GameObjectIDSetItr _cur      ; // ���
};

#endif

#endif // __GAMESERVER_GAMEAREA_H__
