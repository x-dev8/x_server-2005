#ifndef __PLAYERENMITYHANDLE_H__
#define __PLAYERENMITYHANDLE_H__

public:
    virtual void CalcEnmity( BaseCharacter* pTarget, const ItemDefine::SItemSkill* pSkillConfig, int nDamage );

protected:
    virtual void ProcessRefreshEnmity( uint32 nCurrentTime );

#endif