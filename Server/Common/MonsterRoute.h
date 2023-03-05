/********************************************************************
    Filename:    MonsterRoute.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_MONSTERROUTE_H__
#define __GAMESERVER_MONSTERROUTE_H__

#pragma once

#include "MonsterBase.h"

const uint32 gMonsterRoutePoolBatchSize = 10;

// dota类型路径怪物
class MonsterRoute : public MonsterBase, public TEnmity<EnmitySize>, 
                     INHERIT_POOL_PARAM( MonsterRoute, gMonsterRoutePoolBatchSize )
{
public:
    DECLARE_POOL_FUNC( MonsterRoute )

    MonsterRoute();
    virtual ~MonsterRoute();
    
    virtual void OnBeAttacked( BaseCharacter* pAttacker,const CItemDetail::SItemSkill* pSkillConfig ); // 被人打了
    virtual bool OnThink();
    virtual bool OnMove( uint32 lapseTime );
    virtual bool OnSuccessLockTarget();        // 在成功锁定目标时候
    virtual bool MustOpenAI() { return true; } // 默认AI不是必须打开的
    virtual void OnExitMySightNoPlayer(){}

    //////////////////////////////////////////////////////////////////////////
    // 仇恨相关
    virtual int          GetEnmitySize() { return EnmityNum; }
    virtual SEnmity&     EnmityList( int nNum );

    //获取某个ID的仇恨值
    virtual unsigned int GetEnmity( GameObjectId nID );
    virtual bool         SetEnmity( GameObjectId nID, unsigned int nEnmity );

    //添加/移除仇恨列表中对象
    //如果ID在列表中已经存在，则不会添加。返回false
    virtual bool         AddEnmityList      ( GameObjectId nID, unsigned int nEnmity = 0);
    virtual bool         RemoveEnmityList   ( GameObjectId nID );
    virtual void         RemoveAllEnmityList( GameObjectId nId );
    virtual bool         UpdateDecEnmityRate( GameObjectId nID );

    //添加/减少仇恨
    virtual bool         AddEnmity( GameObjectId nID, unsigned int nEnmity);
    virtual bool         DecEnmity( GameObjectId nID, unsigned int nEnmity);

    //一个计算DPS的参考仇恨 此仇恨并不影响怪物的攻击目标
    virtual unsigned int GetDamageEnmity( GameObjectId nID);
    virtual bool         SetDamageEnmity( GameObjectId nID, unsigned int nEnmity);
    virtual bool         AddDamageEnmity( GameObjectId nID, unsigned int nEnmity);
    virtual bool         DecDamageEnmity( GameObjectId nID, unsigned int nEnmity);

    virtual bool         AddTargetEnmityToMe( GameObjectId nID,unsigned int nEnmity);
    virtual void         ClearAllEnmity();
    virtual void         AddAllEnmity( unsigned int nEnmity);
    virtual void         DecAllEnmity( unsigned int nEnmity);

    virtual bool         IsHaveEnmity(); // 当前是有怪对玩家存在仇恨
    virtual GameObjectId        GetNearestEnmityChar( D3DXVECTOR3 vSelfPos, int nSelfCountry ); //当前仇恨表中离角色最近的Char

    //当前仇恨表中对角色仇恨最大的Char
    virtual GameObjectId        GetMaxEnmityChar();
    virtual void         RefreshEnmity();    
    virtual void         OnEnmityNumChange(); // 有敌人的人数变动
    virtual void         OnEnmityValueChanged( GameObjectId id, unsigned int value); // 有某个敌人的仇恨值变动

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
    void UpdateViewEnmity( uint8 index, MonsterBase* pTargetMonster ); // 保持更新目标的仇恨值

protected:
    void ThinkAttack()   ; // 可以产生攻击行为
    void ThinkIdle()     ; // 可以产生Idle常态行为    

    void ThinkRouteMove(); // 路径移动
    void ClearOutOfRouteRecord();

    void MoveAttackMoving( uint32 lapseTime ); // 有攻击目标的移动
    void MovePosMoving   ( uint32 lapseTime ); // 一般的点目标的移动

    //void MAlarmWhenBeAttack()        ; // 在被攻击的时候向周围发出警告 next项目不用先关闭

private:
    uint16 _routeId         ; // routeId
    uint16 _routeStep       ; // 当前到哪一步
    SRoute _route           ; // 路点信息
    bool   _bArriveTargetPos; // 是否达到目标点
    bool   _bOutOfRoute     ; // 是否离开了指定的前进路线做其他事去了
    bool   _bFinalArrive    ; // 最终到达目的地
    float  _posXOff         ; // 目标的随机差
    float  _posYOff         ; // 目标的随机差
};

//////////////////////////////////////////////////////////////////////////
// inline
inline void MonsterRoute::ClearOutOfRouteRecord()
{
    GetAiData()->lastIdleX = 0;
    GetAiData()->lastIdleY = 0;
}
#endif // __GAMESERVER_MONSTERROUTE_H__
