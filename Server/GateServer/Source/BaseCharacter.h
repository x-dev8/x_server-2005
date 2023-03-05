/********************************************************************
	Filename: 	BaseCharacter.h
	MaintenanceMan Mail: Luo_157@hotmail.com
	@brief:人物类

*********************************************************************/

#ifndef __GATESERVER_CHARACTER_H__
#define __GATESERVER_CHARACTER_H__

#pragma once

#include "MeRTLibsServer.h"
#include "MessageDefine.h"

#include "PosChangePackage.h"
#include "EnterMySightPackage.h"

const unsigned int MAX_CHARACTER_POS_SAVE = 200; // 最多缓存200个角色移动信息
const unsigned int NEAR_DISTANCE          = 15;  // 近距离 20
const unsigned int MIDDLE_DISTANCE        = 30;  // 中等   40
const unsigned int FAR_DISTANCE           = 60;  // 远     80

const unsigned int DISCARD_VERIFY = 30; // 当周围的角色数量达到此数量时，抛弃校验 30
const unsigned int DISCARD_VEER   = 50; // 当周围的角色数量达到此数量时，抛弃转向 50

const unsigned int MAX_FIRSTID = 40;    // 不优化的角色ID数量

class BaseCharacter
{
public:
    BaseCharacter();
    virtual ~BaseCharacter();

    float GetFloatX() { return m_floatX; }
    float GetFloatY() { return m_floatY; }
    float GetFloatZ() { return m_floatZ; }

    void  SetFloatX( float fX ) { m_floatX = fX;}
    void  SetFloatY( float fY ) { m_floatY = fY;}
    void  SetFloatZ( float fZ ) { m_floatZ = fZ;}

    uint32 GetStageID() { return m_dwStageID; }
    void   SetStageID( uint32 dwStageID ){ m_dwStageID = dwStageID; }

    short GetCurrentTileId(){ return m_stCurrentTile; }
    void  SetCurrentTileId( short stCurrentTileId ){ m_stCurrentTile = stCurrentTileId; }

    bool IsPlayer(){ return m_bIsPlayer; }
    void SetPlayer( bool bIsPlayer ){ m_bIsPlayer = bIsPlayer; }

    uint32 GetReqAllocTime()                  { return m_dwLastReqAlloc; }
    void   SetReqAllocTime(uint32 dwReqAlloc) { m_dwLastReqAlloc = dwReqAlloc; }

    void ClearCharPosInfo();
    bool MakePosChangePackage(CPosChangePackage& package);

    bool   AddFirstIDToList     ( GameObjectId nID );
    void   RemoveFirstIDFromList( GameObjectId nID );
    bool   IDIsInFirstList      ( GameObjectId nID );
    void   ClearFirstID();
    uint32 FindEmptyPos( GameObjectId nID);

public:
    SPosChangeInfo          m_CharPosInfoList[MAX_CHARACTER_POS_SAVE]; // 可接受到的所有游戏角色的位置信息
    GameObjectId            m_FirstList[MAX_FIRSTID];
    std::list<GameObjectId> m_WaitEnterMySightIDList; //等待发送进入视野消息包的队列
    CEnterMySightPackage    m_entermysightpack;

private:    
    uint32 m_dwStageID;     // 当前场景编号
    short  m_stCurrentTile; // 当前Tile
    float  m_floatX;
    float  m_floatY;
    float  m_floatZ;
    bool   m_bIsPlayer;     // 是否玩家角色 如果不是玩家的话，不需要接收消息
    uint32 m_dwLastReqAlloc;
};

#endif // __GATESERVER_CHARACTER_H__
