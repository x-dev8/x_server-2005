/********************************************************************
    Filename:    MonsterRoute.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_MONSTERROUTE_H__
#define __GAMESERVER_MONSTERROUTE_H__

#pragma once

#include "MonsterBase.h"

const uint32 gMonsterRoutePoolBatchSize = 10;

// dota����·������
class MonsterRoute : public MonsterBase, public TEnmity<EnmitySize>, 
                     INHERIT_POOL_PARAM( MonsterRoute, gMonsterRoutePoolBatchSize )
{
public:
    DECLARE_POOL_FUNC( MonsterRoute )

    MonsterRoute();
    virtual ~MonsterRoute();
    
    virtual void OnBeAttacked( BaseCharacter* pAttacker,const CItemDetail::SItemSkill* pSkillConfig ); // ���˴���
    virtual bool OnThink();
    virtual bool OnMove( uint32 lapseTime );
    virtual bool OnSuccessLockTarget();        // �ڳɹ�����Ŀ��ʱ��
    virtual bool MustOpenAI() { return true; } // Ĭ��AI���Ǳ���򿪵�
    virtual void OnExitMySightNoPlayer(){}

    //////////////////////////////////////////////////////////////////////////
    // ������
    virtual int          GetEnmitySize() { return EnmityNum; }
    virtual SEnmity&     EnmityList( int nNum );

    //��ȡĳ��ID�ĳ��ֵ
    virtual unsigned int GetEnmity( GameObjectId nID );
    virtual bool         SetEnmity( GameObjectId nID, unsigned int nEnmity );

    //���/�Ƴ�����б��ж���
    //���ID���б����Ѿ����ڣ��򲻻���ӡ�����false
    virtual bool         AddEnmityList      ( GameObjectId nID, unsigned int nEnmity = 0);
    virtual bool         RemoveEnmityList   ( GameObjectId nID );
    virtual void         RemoveAllEnmityList( GameObjectId nId );
    virtual bool         UpdateDecEnmityRate( GameObjectId nID );

    //���/���ٳ��
    virtual bool         AddEnmity( GameObjectId nID, unsigned int nEnmity);
    virtual bool         DecEnmity( GameObjectId nID, unsigned int nEnmity);

    //һ������DPS�Ĳο���� �˳�޲���Ӱ�����Ĺ���Ŀ��
    virtual unsigned int GetDamageEnmity( GameObjectId nID);
    virtual bool         SetDamageEnmity( GameObjectId nID, unsigned int nEnmity);
    virtual bool         AddDamageEnmity( GameObjectId nID, unsigned int nEnmity);
    virtual bool         DecDamageEnmity( GameObjectId nID, unsigned int nEnmity);

    virtual bool         AddTargetEnmityToMe( GameObjectId nID,unsigned int nEnmity);
    virtual void         ClearAllEnmity();
    virtual void         AddAllEnmity( unsigned int nEnmity);
    virtual void         DecAllEnmity( unsigned int nEnmity);

    virtual bool         IsHaveEnmity(); // ��ǰ���йֶ���Ҵ��ڳ��
    virtual GameObjectId        GetNearestEnmityChar( D3DXVECTOR3 vSelfPos, int nSelfCountry ); //��ǰ��ޱ������ɫ�����Char

    //��ǰ��ޱ��жԽ�ɫ�������Char
    virtual GameObjectId        GetMaxEnmityChar();
    virtual void         RefreshEnmity();    
    virtual void         OnEnmityNumChange(); // �е��˵������䶯
    virtual void         OnEnmityValueChanged( GameObjectId id, unsigned int value); // ��ĳ�����˵ĳ��ֵ�䶯

    //////////////////////////////////////////////////////////////////////////
    // Route
    void                 SetPosOff( float xoff, float yoff ){ _posXOff = xoff; _posYOff = yoff; }
    bool                 IsBeginPosMove();
    bool                 HaveRoute(){ return _routeId != ErrorUnsignedShortID; }
    uint32               InitRoute( uint32 mapId, uint16 routeId );
    SMovePos*            GetMovePos( uint8 step = 1);
    SMovePos*            GetBeginPos();

    //////////////////////////////////////////////////////////////////////////
    // For Debug
    uint16               GetRouteStep()         { return _routeStep;        }
    bool                 GetIsArriveTargetPos() { return _bArriveTargetPos; }
    bool                 GetIsOutOfRoute()      { return _bOutOfRoute;      }
    bool                 GetIsFinalArrive()     { return _bFinalArrive;     }
    bool                 GetIsNeedMove()        { return _isNeedMove;       }

protected:
    void UpdateViewEnmity( uint8 index, MonsterBase* pTargetMonster ); // ���ָ���Ŀ��ĳ��ֵ

protected:
    void ThinkAttack()   ; // ���Բ���������Ϊ
    void ThinkIdle()     ; // ���Բ���Idle��̬��Ϊ    

    void ThinkRouteMove(); // ·���ƶ�
    void ClearOutOfRouteRecord();

    void MoveAttackMoving( uint32 lapseTime ); // �й���Ŀ����ƶ�
    void MovePosMoving   ( uint32 lapseTime ); // һ��ĵ�Ŀ����ƶ�

    //void MAlarmWhenBeAttack()        ; // �ڱ�������ʱ������Χ�������� next��Ŀ�����ȹر�

private:
    uint16 _routeId         ; // routeId
    uint16 _routeStep       ; // ��ǰ����һ��
    SRoute _route           ; // ·����Ϣ
    bool   _bArriveTargetPos; // �Ƿ�ﵽĿ���
    bool   _bOutOfRoute     ; // �Ƿ��뿪��ָ����ǰ��·����������ȥ��
    bool   _bFinalArrive    ; // ���յ���Ŀ�ĵ�
    float  _posXOff         ; // Ŀ��������
    float  _posYOff         ; // Ŀ��������
};

//////////////////////////////////////////////////////////////////////////
// inline
inline void MonsterRoute::ClearOutOfRouteRecord()
{
    GetAiData()->lastIdleX = 0;
    GetAiData()->lastIdleY = 0;
}
#endif // __GAMESERVER_MONSTERROUTE_H__
