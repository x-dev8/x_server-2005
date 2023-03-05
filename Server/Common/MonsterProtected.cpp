#include "MonsterProtected.h"
#include "ShareData.h"
#include "GameWorld.h"
#include "GamePlayer.h"

void MonsterProtected::OnBeAttacked( BaseCharacter* pAttacker,const CItemDetail::SItemSkill* pSkillConfig )
{
    if( !pAttacker)
    { return; }

    BaseCharacter::OnBeAttacked( pAttacker, pSkillConfig);

    StartUpAI();
    if ( !HaveCanAttackCharId() )
    { _disableControlThinkTime = true; }

    //记录下上一次未被攻击前的空闲位置
    if (GetAiData()->lastIdleX == 0)
    {
        GetAiData()->lastIdleX = GetFloatX();
        GetAiData()->lastIdleY = GetFloatY();
    }
}

bool MonsterProtected::OnThink()
{
    BaseCharacter* pSummoner = theRunTimeData.GetCharacterByID( GetSummonMasterID() );
    if ( pSummoner == NULL || !pSummoner->IsPlayer() || pSummoner->IsDead())
    {
        Murder();
        return false;
    }

    // 跟着召唤他的人
    FollowTheSummonMaster( pSummoner ); 
    return true;
}

bool MonsterProtected::OnMove( uint32 lapseTime )
{
    MovePosMoving( lapseTime );
    return true;
}

void MonsterProtected::MovePosMoving( uint32 lapseTime )
{
    // 没有攻击目标
    if( _isNeedMove )
    { // 如果需要移动

        D3DXVECTOR3 vecDistance( _moveTargetPos.x - GetFloatX(), _moveTargetPos.y - GetFloatY(), 0 );
        float fDist = D3DXVec3Length( &vecDistance );
        D3DXVECTOR3 vDir(0,0,0);
        D3DXVec3Normalize( &vDir, &vecDistance );

        float fActualMoveDist = GetMoveSpeed()*((float)lapseTime * 0.001);
        if( fActualMoveDist >= fDist )
        {
            fActualMoveDist = fDist;
            m_bMoving   = false;
            _isNeedMove = false;
        }
        else
        {
            m_bMoving = true;
        }

        SetDirX( vDir.x );
        SetDirY( vDir.y );
        SetFloatXF( GetFloatX() + fActualMoveDist * vDir.x );
        SetFloatYF( GetFloatY() + fActualMoveDist * vDir.y );
    }
    else
    {
        m_bMoving = false;
    }

    if( GameTime::IsPassCurrentTime( m_dwSendMoveMessageTime, 2000 ) )
    { // 移动消息频率 更新用 比如GateServer热起

        theGameWorld.OnRefreshNewArea( GetID() );

        if ( AreaHavePlayer() )
        {
            if ( m_bMoving )
            {
                // 在移动中
                MsgUnPlayerMovingToPos msg;                    
                msg.header.stID = GetID();
                msg.vStartPos.x = GetFloatX();
                msg.vStartPos.y = GetFloatY();
                msg.vStartPos.z = WORLD_HEIGHT;
                msg.vEndPos     = _moveTargetPos;
                GettheServer().SendMsgToView( &msg, GetID(), true );
            }
            else
            { // 两秒再两秒
                if ( GameTime::IsPassCurrentTime( m_noMoveSendVerifyPosTime, 4000 ) )
                { 
                    SendVerifyPos( GetFloatX(), GetFloatY() ); 
                    m_noMoveSendVerifyPosTime = HQ_TimeGetTime();
                }
            }
        }

        m_dwSendMoveMessageTime = HQ_TimeGetTime();
    }
}