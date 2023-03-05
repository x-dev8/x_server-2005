/********************************************************************
    Filename:    Enmity.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_ENMITY_H__
#define __GAMESERVER_ENMITY_H__

#include "GlobalDef.h"
#include "FuncPerformanceLog.h"
#include "Dxsdk/d3dx9math.h"

#define ENMITY_NOTINLIST 0xFFFFFFFF
#define NULLID           0xFFFF
#define EnmitySize       150

struct SEnmity
{
    GameObjectId nID;
    unsigned int nEnmity;
    unsigned int nDecEnmityRate;

    SEnmity()
    { Reset(); }

    void ClearEnmity();
    void Reset();
};

//////////////////////////////////////////////////////////////////////////
//inline
inline void SEnmity::ClearEnmity()
{
    nEnmity        = 0;
    nDecEnmityRate = 0;
}

inline void SEnmity::Reset()
{
    nID            = NULLID;
    nEnmity        = 0;
    nDecEnmityRate = 0;
}

template<int Num> 
class TEnmity
{ // 遍历太耗 需要改为map
public:
    static const int EnmityNum = Num;

    TEnmity()
    { m_dwLastDecEnmityTime = 0; }

    virtual ~TEnmity()
    {}

public:
	uint32  m_dwLastDecEnmityTime;
    SEnmity m_enmityList[Num];
};

template <int Num>
class TPlayerEnmity : public TEnmity<Num>
{
public:
    TPlayerEnmity()
    {}

public:
    SEnmity m_damageenmityList[Num]; // 后面加的伤害值造成的仇恨列表，此列表不影响怪物攻击目标，仅对DPS进行一个评估
};

class IEnmityChar
{
public:
    IEnmityChar() {}
    virtual ~IEnmityChar() {}
    
    virtual int          GetEnmitySize()             { return 0; }
    virtual SEnmity&     EnmityList(int nNum)        { static SEnmity e; return e;}
    virtual unsigned int GetEnmity(GameObjectId nID) { return 0;}
    virtual bool         SetEnmity(GameObjectId nID, unsigned int nEnmity) { return false;}
    virtual bool         AddEnmityList(GameObjectId nID, unsigned int nEnmity = 0) { return false;} // 以下添加/移除仇恨列表中对象 如果ID在列表中已经存在，则不会添加。返回false
    virtual bool         RemoveEnmityList(GameObjectId nID) { return false; }
    virtual void         RemoveAllEnmityList(GameObjectId nId) { }
    virtual bool         UpdateDecEnmityRate(GameObjectId nID) { return false; }
    virtual bool         AddEnmity(GameObjectId nID, unsigned int nEnmity) { return false; } // 以下添加/减少仇恨
    virtual bool         DecEnmity(GameObjectId nID, unsigned int nEnmity) { return false; }
    virtual unsigned int GetDamageEnmity(GameObjectId nID) { return -1; }                    // 以下一个计算DPS的参考仇恨 此仇恨并不影响怪物的攻击目标
    virtual bool         SetDamageEnmity(GameObjectId nID, unsigned int nEnmity) { return false; }
    virtual bool         AddDamageEnmity(GameObjectId nID, unsigned int nEnmity) { return false; }
    virtual bool         DecDamageEnmity(GameObjectId nID, unsigned int nEnmity) { return false; }
    virtual bool         AddTargetEnmityToMe(GameObjectId nID,unsigned int nEnmity) { return false; }
    virtual void         ClearAllEnmity() {}
    virtual void         AddAllEnmity(unsigned int nEnmity) {}
    virtual void         DecAllEnmity(unsigned int nEnmity) {}
    virtual bool         IsHaveEnmity() { return false; }                                              // 当前是有怪对玩家存在仇恨
    virtual GameObjectId        GetNearestEnmityChar( D3DXVECTOR3 vSelfPos, int nSelfCountry ) { return -1; } // 当前仇恨表中离角色最近的Char
    virtual GameObjectId        GetMaxEnmityChar()  { return -1; }                                            // 当前仇恨表中对角色仇恨最大的Char

protected:
    virtual void         OnEnmityNumChange() {} // 有敌人的人数变动
    virtual void         OnEnmityValueChanged( GameObjectId id, unsigned int value ) {}// 有某个敌人的仇恨值变动
};

#endif
