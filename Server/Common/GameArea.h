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
{ // 地图区块类
public:
    enum EConstDefine
    {
        constMaxCharacters = dr_areaMaxCharacters, // 区块内最大角色数
    };

public:

    DECLARE_POOL_FUNC( GameArea )

    GameArea();
    virtual ~GameArea();

    bool CharacterEnter( uint32 dwID, bool bPlayer ); // 角色进入
    bool CharacterLeave( uint32 dwID, bool bPlayer ); // 角色离开

    bool SendAllInfoToChar    ( uint32 dwID );        // 把所有人的基本信息发送给该角色
    bool AllLeaveFromCharSight( uint32 dwID );        // 所有人离开某人视野

    bool SendSpecialInfoToChar( uint32 dwID, uint8 eLimitType );          // 将指定的信息发送给该角色
    bool SpecialInfoLeaveFromCharSight( uint32 dwID, uint8 eLimitType );  // 指定信息离开角色

    GameObjectIdTPL(constMaxCharacters)* GetIDTable() { return &m_CharacterTable; } // 获得角色列表
    void AddAroundArea( int x, int y, int l, int h );                         // 加入周围区块

public:
    int m_nAroundAreaId[GAME_MAXAROUNDAREANUMBER]; // 周围区块的Id表
    int m_nAroundAreaCount;                        // 周围区块的数量

private:
    GameObjectIdTPL(constMaxCharacters) m_CharacterTable; // 角色ID表
};

#else

class GameArea : INHERIT_POOL( GameArea )
{
public:
    DECLARE_POOL_FUNC( GameArea )

    GameArea();
    virtual ~GameArea();

    // 角色进入
    bool CharacterEnter( GameObjectId dwID, bool bPlayer );

    // 角色离开
    bool CharacterLeave( GameObjectId dwID, bool bPlayer );

    // 把所有人的基本信息发送给该角色
    bool SendAllInfoToChar( GameObjectId dwID );

    // 所有人离开某人视野
    bool AllLeaveFromCharSight( GameObjectId dwID );

    // 将指定的信息发送给该角色
    bool SendSpecialInfoToChar( GameObjectId dwID, uint8 eLimitType );          

    // 指定信息离开角色
    bool SpecialInfoLeaveFromCharSight( GameObjectId dwID, uint8 eLimitType );

    // 遍历得到Id
    GameObjectId GetNextObjectBId( bool bFirst );

    // 得到Object的Size
    size_t GetObjectSize() { return _objectIds.size(); }

    // 得到Player的Size
    size_t GetPlayerObjectSize() { return _playerIds.size(); }

    // 添加边缘Area 加入周围区块
    void AddAroundArea( int x, int y, int l, int h );

public:
    int m_nAroundAreaId[GAME_MAXAROUNDAREANUMBER]; // 周围区块的Id表
    int m_nAroundAreaCount;                        // 周围区块的数量

private:
    GameObjectIDSet    _objectIds; // player Npc Monster Item 等
    GameObjectIDSet    _playerIds; // player 
    GameObjectIDSetItr _cur      ; // 光标
};

#endif

#endif // __GAMESERVER_GAMEAREA_H__
