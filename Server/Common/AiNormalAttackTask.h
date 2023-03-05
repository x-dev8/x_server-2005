#ifndef __GAMESERVER_AINORMALATTACKTASK_H__
#define __GAMESERVER_AINORMALATTACKTASK_H__

#pragma once

#include "AiBaseTask.h"
#include "Memory_Pool.h"
#include "MsgBase.h"

class AiNormalAttackTask : public AiBaseTask, INHERIT_POOL_PARAM( AiNormalAttackTask, 50 )
{ // Ò»°ã¹¥»÷
public:
    DECLARE_POOL_FUNC( AiNormalAttackTask )

    AiNormalAttackTask();
    virtual ~AiNormalAttackTask();
    
    virtual void ExecuteTask( BaseCharacter* pOwner );

    void SetAttackTarget( GameObjectId iWho ) { _targetObjectId = iWho; }
    void SetSkill( uint16 iSkillId, uint8 iLevel );

protected:
    GameObjectId	_targetObjectId;
    uint16          m_iSkillId;
    uint8           m_iLevel;
};

//////////////////////////////////////////////////////////////////////////
// inline
inline void AiNormalAttackTask::SetSkill( uint16 iSkillId, uint8 iLevel )
{
    m_iSkillId = iSkillId;
    m_iLevel   = iLevel;
}

#endif // __GAMESERVER_AINORMALATTACKTASK_H__
