/********************************************************************
	Filename: 	BaseCharacter.h
	MaintenanceMan Mail: Luo_157@hotmail.com
	@brief:������

*********************************************************************/

#ifndef __GATESERVER_CHARACTER_H__
#define __GATESERVER_CHARACTER_H__

#pragma once

#include "MeRTLibsServer.h"
#include "MessageDefine.h"

#include "PosChangePackage.h"
#include "EnterMySightPackage.h"

const unsigned int MAX_CHARACTER_POS_SAVE = 200; // ��໺��200����ɫ�ƶ���Ϣ
const unsigned int NEAR_DISTANCE          = 15;  // ������ 20
const unsigned int MIDDLE_DISTANCE        = 30;  // �е�   40
const unsigned int FAR_DISTANCE           = 60;  // Զ     80

const unsigned int DISCARD_VERIFY = 30; // ����Χ�Ľ�ɫ�����ﵽ������ʱ������У�� 30
const unsigned int DISCARD_VEER   = 50; // ����Χ�Ľ�ɫ�����ﵽ������ʱ������ת�� 50

const unsigned int MAX_FIRSTID = 40;    // ���Ż��Ľ�ɫID����

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
    SPosChangeInfo          m_CharPosInfoList[MAX_CHARACTER_POS_SAVE]; // �ɽ��ܵ���������Ϸ��ɫ��λ����Ϣ
    GameObjectId            m_FirstList[MAX_FIRSTID];
    std::list<GameObjectId> m_WaitEnterMySightIDList; //�ȴ����ͽ�����Ұ��Ϣ���Ķ���
    CEnterMySightPackage    m_entermysightpack;

private:    
    uint32 m_dwStageID;     // ��ǰ�������
    short  m_stCurrentTile; // ��ǰTile
    float  m_floatX;
    float  m_floatY;
    float  m_floatZ;
    bool   m_bIsPlayer;     // �Ƿ���ҽ�ɫ ���������ҵĻ�������Ҫ������Ϣ
    uint32 m_dwLastReqAlloc;
};

#endif // __GATESERVER_CHARACTER_H__
