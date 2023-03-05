#include "GamePlayer.h"
#include "ShareData.h"
#include "ItemDetailConfig.h"

void GamePlayer::OnEnterHide()
{
    //ClearAllEnmity( false );   // 清除所有角色仇恨
}

void GamePlayer::OnXinFaUpdate()
{
    for (int i=0; i<_buffManager.GetBufferStatusCount(); ++i)
    {   
        SCharBuff* pCharBuff = _buffManager.GetBuff( i );
        if ( pCharBuff == NULL )
        { continue; }

        if ( pCharBuff->eventType != SCharBuff::StatusEventType_Skill )
        { continue; }

        ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus( pCharBuff->StatusID, pCharBuff->iLevel);
        if ( pStatus == NULL )
        { continue; }

        ItemDefine::SItemSkill*  pSkill  = GettheItemDetail().GetSkillByID( pCharBuff->eventValue, 1 );
        if ( pSkill == NULL )
        { continue; }

        int nXinFaSkillAttr[SkillAttr_MaxSize] =  { 0 } ;
        BaseCharacter* pMasterChar =  theRunTimeData.GetCharacterByID( pCharBuff->masterId ) ; 
        if ( pMasterChar != NULL && pMasterChar->IsPlayer() )
        {
            GamePlayer* pMasterPlayer = static_cast< GamePlayer* >( pMasterChar );
            ItemDefine::SItemSkill* pSkillConfig = GettheItemDetail().GetSkillByID( pCharBuff->eventValue, 1 );
            if (pSkillConfig != NULL)
            { pMasterPlayer->GetXinFaSkillEffect( pSkillConfig, nXinFaSkillAttr ); }
        }

        if (pStatus->stSuckDamageMax != 0)
        {
            int stSuckMax = pStatus->stSuckDamageMax + nXinFaSkillAttr[StatusAttr_SuckDamage];
            _buffManager.SetSuckDamgeMax( stSuckMax );
        }
    }
}
