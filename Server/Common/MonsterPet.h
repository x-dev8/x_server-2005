/********************************************************************
    Filename:    MonsterPet.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_MONSTERPET_H__
#define __GAMESERVER_MONSTERPET_H__

#pragma once

#include "MonsterBaseEx.h"

class MonsterPet : public MonsterBaseEx, public TEnmity<EnmitySize>, 
                   INHERIT_POOL_PARAM( MonsterPet, 50 )
{
public:
    DECLARE_POOL_FUNC( MonsterPet )

    MonsterPet() {}
    virtual ~MonsterPet() {}

    virtual void OnBeAttacked( BaseCharacter* pAttacker,const CItemDetail::SItemSkill* pSkillConfig );
    virtual bool OnThink();
    virtual bool OnMove( uint32 lapseTime );

    // 有仇恨的怪物不能关闭AI，否则有些怪物之间的战斗就因为旁边没有人而无法发生
    virtual bool MustOpenAI()    { return true;      }
    virtual void OnExitMySightNoPlayer(){}
    //////////////////////////////////////////////////////////////////////////
    // 仇恨相关
    virtual int     GetEnmitySize() { return EnmityNum; }
    virtual SEnmity& EnmityList( int nNum );

    //获取某个ID的仇恨值
    virtual unsigned int GetEnmity( unsigned int nID );
    virtual bool         SetEnmity( unsigned int nID, unsigned int nEnmity );

    //添加/移除仇恨列表中对象
    //如果ID在列表中已经存在，则不会添加。返回false
    virtual bool         AddEnmityList(unsigned int nID, unsigned int nEnmity = 0);
    virtual bool         RemoveEnmityList(unsigned int nID);
    virtual void         RemoveAllEnmityList(unsigned int nId);
    virtual bool         UpdateDecEnmityRate(unsigned int nID);

    //添加/减少仇恨
    virtual bool         AddEnmity(unsigned int nID, unsigned int nEnmity);
    virtual bool         DecEnmity(unsigned int nID, unsigned int nEnmity);
    
    //一个计算DPS的参考仇恨 此仇恨并不影响怪物的攻击目标
    virtual unsigned int GetDamageEnmity(unsigned int nID);
    virtual bool         SetDamageEnmity(unsigned int nID, unsigned int nEnmity);
    virtual bool         AddDamageEnmity(unsigned int nID, unsigned int nEnmity);
    virtual bool         DecDamageEnmity(unsigned int nID, unsigned int nEnmity);

    virtual bool         AddTargetEnmityToMe(unsigned int nID,unsigned int nEnmity);
    virtual void         ClearAllEnmity();
    virtual void         AddAllEnmity(unsigned int nEnmity);
    virtual void         DecAllEnmity(unsigned int nEnmity);

    
    virtual bool         IsHaveEnmity(); //当前是有怪对玩家存在仇恨    
    virtual short        GetNearestEnmityChar( D3DXVECTOR3 vSelfPos, int nSelfCountry ); //当前仇恨表中离角色最近的Char

    //当前仇恨表中对角色仇恨最大的Char
    virtual short GetMaxEnmityChar();
    virtual void  RefreshEnmity();    
    virtual void  OnEnmityNumChange(); // 有敌人的人数变动
    virtual void  OnEnmityValueChanged( unsigned short id, unsigned int value); // 有某个敌人的仇恨值变动
    //////////////////////////////////////////////////////////////////////////
protected:
    void MoveAttackMoving( uint32 lapseTime ); // 有攻击目标的移动
    void MovePosMoving   ( uint32 lapseTime ); // 一般的点目标的移动
};

#endif // __GAMESERVER_MONSTERPET_H__
