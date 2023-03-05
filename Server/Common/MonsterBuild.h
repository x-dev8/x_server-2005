/********************************************************************
    Filename:    MonsterBuild.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_MONSTERBUILD_H__
#define __COMMON_MONSTERBUILD_H__

#include "MonsterBase.h"

const uint32 gMonsterBuildPoolBatchSize = 10;

class MonsterBuild : public MonsterBase, public TEnmity<EnmitySize>, 
                     INHERIT_POOL_PARAM( MonsterBuild, gMonsterBuildPoolBatchSize )
{
public:
    DECLARE_POOL_FUNC( MonsterBuild )

    MonsterBuild();
    virtual ~MonsterBuild();

    virtual void Run( DWORD dwCostTime ); // 主动执行,主运行
    virtual void ProcessLogicBeforeProcessMsg( DWORD dwCostTime, bool& bContinue );
    virtual void OnBeAttacked( BaseCharacter* pAttacker,const CItemDetail::SItemSkill* pSkillConfig );
    virtual void OnDeath();    
    virtual bool OnThink(){ return true; }                  // 在思考时候
    virtual bool OnMove( uint32 lapseTime ){ return true; } // 在移动时候

    //////////////////////////////////////////////////////////////////////////
    // 仇恨相关
    virtual int     GetEnmitySize() { return EnmityNum; }
    virtual SEnmity& EnmityList( int nNum );

    //获取某个ID的仇恨值
    virtual unsigned int GetEnmity( GameObjectId nID );
    virtual bool         SetEnmity( GameObjectId nID, unsigned int nEnmity );

    //添加/移除仇恨列表中对象
    //如果ID在列表中已经存在，则不会添加。返回false
    virtual bool         AddEnmityList(GameObjectId nID, unsigned int nEnmity = 0);
    virtual bool         RemoveEnmityList(GameObjectId nID);
    virtual void         RemoveAllEnmityList(GameObjectId nId);
    virtual bool         UpdateDecEnmityRate(GameObjectId nID);

    //添加/减少仇恨
    virtual bool         AddEnmity(GameObjectId nID, unsigned int nEnmity);
    virtual bool         DecEnmity(GameObjectId nID, unsigned int nEnmity);

    //一个计算DPS的参考仇恨 此仇恨并不影响怪物的攻击目标
    virtual unsigned int GetDamageEnmity(GameObjectId nID);
    virtual bool         SetDamageEnmity(GameObjectId nID, unsigned int nEnmity);
    virtual bool         AddDamageEnmity(GameObjectId nID, unsigned int nEnmity);
    virtual bool         DecDamageEnmity(GameObjectId nID, unsigned int nEnmity);

    virtual bool         AddTargetEnmityToMe(GameObjectId nID,unsigned int nEnmity);
    virtual void         ClearAllEnmity();
    virtual void         AddAllEnmity(unsigned int nEnmity);
    virtual void         DecAllEnmity(unsigned int nEnmity);


    virtual bool         IsHaveEnmity(); //当前是有怪对玩家存在仇恨    
    virtual GameObjectId        GetNearestEnmityChar( D3DXVECTOR3 vSelfPos, int nSelfCountry ); //当前仇恨表中离角色最近的Char

    //当前仇恨表中对角色仇恨最大的Char
    virtual GameObjectId		 GetMaxEnmityChar();
    virtual void  RefreshEnmity();    
    virtual void  OnEnmityNumChange(); // 有敌人的人数变动
    virtual void  OnEnmityValueChanged( GameObjectId id, unsigned int value); // 有某个敌人的仇恨值变动
    //////////////////////////////////////////////////////////////////////////
protected:
    void UpdateViewEnmity( uint8 index, MonsterBase* pTargetMonster ); // 保持更新目标的仇恨值
};

#endif // __COMMON_MONSTERBUILD_H__
