#include "Formula.h"
#include "GamePlayer.h"
#include "BaseCharacter.h"
#include "MonsterBaseEx.h"
#include "GamePlayer.h"
#include "FuncPerformanceLog.h"
#include "DataCenter.h"
#include "ArmourElementsConfig.h"
#include "DaoxingConfig.h"
#include "PhyleConfig.h"

void CFormula::SResult::Reset()
{
    m_stBalanceType             = 0;     // 结算类型
    m_dwSubComboStatus          = 0;     // 解除状态(复合状态种类)
    m_bMiss                     = false; // 攻击失败标志
    m_iHPRestore                = 0;     // HP的恢复值
    m_iMPRestore                = 0;     // MP的恢复
    m_iDamage                   = 0;     // 物理伤害值
    m_bRelive                   = false; // 是否复活一个已经死去的player
    m_bBackHit                  = false; // 是否背击
    m_bCriticalHit              = false; // 是否是致命一击
    m_nExtraHp                  = 0;
    m_nDamageMp                 = 0;

    m_ustMeAddStatusID[0]          = 0;     // 附加状态编号1(给我的)
    m_ustMeAddStatusLevel[0]       = 0;     // 附加状态等级1(给我的)
    m_ustMeAddStatusID[1]          = 0;     // 附加状态编号2(给我的)
    m_ustMeAddStatusLevel[1]       = 0;     // 附加状态等级2(给我的)

    for( int i = 0; i< EEquipPartType_MaxEquitPart; ++i )
    {
        m_ustMeAddStatusIDFromEquip[i]     = 0; // 附加状态编号(给我的) 
        m_ustMeAddStatusLevelFromEquip[i]  = 0; // 附加状态等级(给我的)
        m_ustDstAddStatusIDFromEquip[i]    = 0; // 附加状态编号(给对方的)
        m_ustDstAddStatusLevelFromEquip[i] = 0;   
    }

    memset( m_nDispelNegativeType, -1, sizeof(m_nDispelNegativeType));
}

// 构造初始化
CFormula::CFormula() : m_iAttackerStrength(0) ,m_iAttackerMagic(0) ,m_pSkill(0) ,m_iTotalTarget(0),
m_pAttacker( NULL ) ,m_stMinBonusDamageRange(0) , m_stMaxBonusDamageRange(0)
{  
    memset( m_pTarget,0,dr_MaxAttackTarget*sizeof(BaseCharacter*) );

    m_pStatusTarget = NULL;
    m_pStatusSrc = NULL;
}


// 重置结算器
void CFormula::Reset()
{
    ResetAttacker();
    ResetTarget();
}
// 重置攻击者
void CFormula::ResetAttacker() 
{
    m_pAttacker = NULL;
    m_iAttackerStrength = 0;
    m_iAttackerMagic = 0;
    m_stMinBonusDamageRange = 0;
    m_stMaxBonusDamageRange = 0;
}
// 重置受攻击者组
void CFormula::ResetTarget()
{
    for( int i = 0;i < dr_MaxAttackTarget; i++ )
    { 
        m_pTarget[i] = NULL; 
        m_TargetLastResult[i].Reset();
        m_SrcLastResult[i].Reset();
    }
    m_iTotalTarget = 0;
}

// 设置攻击者
void CFormula::SetAttacker( BaseCharacter *pAttacker )
{    
    if ( !pAttacker )
        return;

    m_pAttacker = pAttacker;
}

// 加入一个受攻击者
bool CFormula::AddTarget( BaseCharacter *pTarget )
{
    if ( pTarget == NULL )
    { return false; }

    if( m_iTotalTarget >= dr_MaxAttackTarget || m_iTotalTarget < 0 )
    { return false; }

    m_pTarget[m_iTotalTarget] = pTarget;
    m_iTotalTarget++;

    return true;
}

// 是否处于可攻击的设置状态
bool CFormula::IsAttackable()
{
    // 必须有攻击者
    if( !m_pAttacker )
        return false;
    // 必须有被攻击者
    if( m_iTotalTarget <=0 )
        return false;

    // 必须有技能
    if( !m_pSkill)
        return false;
    return true;
}

//计算复活后恢复HP的数值  HPMAX*5%
int CFormula::CalcReliveRestoreHP( int nWhich )
{
    //被施放者
    BaseCharacter *pDst = this->GetTarget( nWhich );

    int iReliveRestoreHP;

    if(m_pAttacker->IsPlayer())
    {
        iReliveRestoreHP = pDst->GetCharFightAttr()->hpMax.final * (1 / 100);
    }
    else
    {
        iReliveRestoreHP = 1;
    }

    return iReliveRestoreHP;
}

//设置状态的ID,Level
void CFormula::SetStatusInfo( unsigned short ustStatusID, unsigned short ustStatusLevel )
{
    m_ustTargetStatusID = ustStatusID;
    m_ustTargetStatusLevel = ustStatusLevel;
}

//状态结算类型balance_status_type_none
void CFormula::CalcStatusBalanceTypeNone()
{
    if (NULL == m_pStatusSrc || NULL == m_pStatus || NULL == m_pStatusTarget)
    { return; }

    if (m_pStatus->bAvail)
    { return; }

    if ( m_pStatusTarget->IsPlayer() )
    {
        GamePlayer *pTargeter = (GamePlayer*)m_pStatusTarget;
        for( int i= 0; i<EEquipPartType_MaxEquitPart; ++i )
        {

            if ( pTargeter->GetMeAddStatusTrigger(i) == ItemDefine::EEquipStatusTrigger_Damage )
            {
                int nMeRate  = (int) (pTargeter->GetMeStatusRate(i));
                if( theRand.rand32() % ADD_STATUS_RAND_NUM < nMeRate )
                {
                    m_TargetStatusResult.m_ustDstAddStatusIDFromEquip[i]     = pTargeter->GetMeAddStatus(i);
                    m_TargetStatusResult.m_ustDstAddStatusLevelFromEquip[i]  = pTargeter->GetMeAddStatusLvl(i);
                }
            }

            if ( pTargeter->GetDstAddStatusTrigger(i) == ItemDefine::EEquipStatusTrigger_Damage )
            {
                int nDstRate = (int) (pTargeter->GetDstStatusRate(i));
                if( theRand.rand32() % ADD_STATUS_RAND_NUM < nDstRate )
                {
                    m_TargetStatusResult.m_ustMeAddStatusIDFromEquip[i]     = pTargeter->GetDstAddStatus(i);
                    m_TargetStatusResult.m_ustMeAddStatusLevelFromEquip[i]  = pTargeter->GetDstAddStatusLvl(i);
                }
            }
        }
    }

    // 判断折光
    if ( m_pStatusTarget->_buffManager.GetHurtImmunity() > 0 )
    {
        MsgUseSkillHintMessage HintMsg;
        HintMsg.header.stID = m_pStatusSrc->GetID();
        HintMsg.TargetID = m_pStatusTarget->GetID();   
        HintMsg.shHintId = MsgUseSkillHintMessage::eHurtImmunity;
        GettheServer().SendMsgToView( &HintMsg, m_pStatusSrc->GetID() );

        int nHurtImmunity = m_pStatusTarget->_buffManager.GetHurtImmunity() - 1;
        m_pStatusTarget->_buffManager.SetHurtImmunity( nHurtImmunity );
        return;
    }

    int iChangedHP = m_pStatus->stChanged_HP  ; //stChanged_HP 负数表示掉血 正数表示回血
    int iDamageMP  = m_pStatus->stChanged_MP;
    int iAdditionalDamage = 0;
    
    if (iChangedHP <= 0 && NULL != m_pBuff && SCharBuff::StatusEventType_Skill == m_pBuff->eventType)
    {
        const ItemDefine::SItemSkill* pSkillConfig = GettheItemDetail().GetSkillByID( m_pBuff->eventValue, 1 );
        if (pSkillConfig != NULL)
        {
            //持续附加伤害 = 攻击*攻击系数 - 防御*防御系数
            int attackModulus = m_pStatusSrc->GetCharFightAttr()->attackPhysics.final * m_pStatus->attackModulus * DEF_PERCENT;

            switch ( pSkillConfig->ustDamageBalanceType )
            {
            case ItemDefine::balancetype_damagephysicaldefend:
                {
                    int defendPhysicsModulus = m_pStatusTarget->GetCharFightAttr()->defendPhysics.final * m_pStatus->defendModulus * DEF_PERCENT;
                    iAdditionalDamage += attackModulus - defendPhysicsModulus;
                    break;
                }
            case ItemDefine::balancetype_damagemagicdefend:
                {
                    int defendMagicModulus = m_pStatusTarget->GetCharFightAttr()->defendMagic.final * m_pStatus->defendModulus * DEF_PERCENT;
                    iAdditionalDamage += attackModulus - defendMagicModulus;
                    break;
                }
            }
        }

        if (iAdditionalDamage < 0)
        { iAdditionalDamage = 0; }
    }

    m_TargetStatusResult.m_iDamage  += (-iChangedHP) + iAdditionalDamage;
    m_TargetStatusResult.m_nDamageMp += (-iDamageMP);

	if ( NULL != m_pBuff && m_pBuff->lapoverNum > 1 ) //大于1次才叫叠加 lrt
	{
		int iLapoverDamage = m_TargetStatusResult.m_iDamage * (m_pBuff->lapoverNum - 1) * m_pStatus->lapoverMod * DEF_PERCENT ;
		m_TargetStatusResult.m_iDamage += iLapoverDamage;

		iLapoverDamage = m_TargetStatusResult.m_nDamageMp * (m_pBuff->lapoverNum - 1) * m_pStatus->lapoverMod * DEF_PERCENT ;
		m_TargetStatusResult.m_nDamageMp += iLapoverDamage;
	}

	// 技能附加伤害值
	if ( m_pStatusSrc->IsPlayer() )
	{
		MonsterBaseEx* pAIChar = (MonsterBaseEx*)m_pStatusTarget;
		GamePlayer* pTemPlayer = ( GamePlayer* )m_pStatusSrc;
		GameFamily* pFamily = pTemPlayer->GetFamily();
		if ( pTemPlayer != NULL && pFamily != NULL )
		{
			int nAttackerTotem = pFamily->GetFamilyTotem();
			int nBeAtrackerTotem = pAIChar->GetPhyle();

			m_TargetStatusResult.m_iDamage += m_TargetStatusResult.m_iDamage * thePhyleChastenConfig.GetDamageByTotem( nAttackerTotem, nBeAtrackerTotem ) * DEF_PERCENT;
		}
	}

	CalcBeDamagePerHP(m_pStatusTarget,&m_TargetStatusResult);
}

//状态结算类型balance_status_type_restore
void CFormula::CalcStatusBalanceTypeRestore()
{
    if (NULL == m_pStatusSrc || NULL == m_pStatus || NULL == m_pStatusTarget)
    { return; }

    if (!m_pStatus->bAvail)
    { return; }

    //持续附加回血 = 攻击*攻击系数
    int iAdditionalHPRestore = 0;
    if ( m_pStatus->attackModulus != 0 )
    { iAdditionalHPRestore = m_pStatusSrc->GetCharFightAttr()->attackPhysics.final * m_pStatus->attackModulus * DEF_PERCENT; }

    //改变生命
    int nChangeHP = m_pStatus->stChanged_HP;

    //恢复人物基础血量%
    int nHPBaseRestore = m_pStatusTarget->GetCharFightAttr()->hpMax.base * m_pStatus->recoverHPBasePer * DEF_PERCENT;

    //恢复人物基础最大值%
    int nHPMaxRestore  = m_pStatusTarget->GetCharFightAttr()->hpMax.final * m_pStatus->recoverHPMaxPer * DEF_PERCENT;

    //改变魔法
    int nChangeMP = m_pStatus->stChanged_MP;

    //恢复人物MP基础%
    int nMPBaseRestore = m_pStatusTarget->GetCharFightAttr()->mpMax.base * m_pStatus->recoverMPBasePer * DEF_PERCENT;

    //恢复人物MP上限%
    int nMPMaxRestore  = m_pStatusTarget->GetCharFightAttr()->mpMax.final * m_pStatus->recoverMPMaxPer * DEF_PERCENT;

    int nFinalHPRestore = nChangeHP + nHPBaseRestore + nHPMaxRestore + iAdditionalHPRestore;
    int nFinalMPRestore = nChangeMP + nMPBaseRestore + nMPMaxRestore;
    int nFinalXPRestore = m_pStatus->stChangedFightPoint;

    m_TargetStatusResult.m_iHPRestore += nFinalHPRestore;
    m_TargetStatusResult.m_iMPRestore += nFinalMPRestore;
    m_TargetStatusResult.m_iXPRestore += nFinalXPRestore;

}

void CFormula::InitPlayerAttackerAttr( int iStrength,int iMagic,short stMinBonusDamageRange,short stMaxBonusDamageRange )
{
    m_iAttackerStrength = iStrength;
    m_iAttackerMagic = iMagic;
    m_stMinBonusDamageRange = stMinBonusDamageRange;
    m_stMaxBonusDamageRange = stMaxBonusDamageRange;
}

// 被结算公式调用 复活结算
void CFormula::CallByBalanceTypeRelive( SResult* pResult, int nWhich )
{
    pResult->m_iHPRestore = CalcReliveRestoreHP( nWhich );
    pResult->m_bRelive = true;
}

// 初始化结算数据
bool CFormula::InitBalanceDamageData( SResult*& pResult, SResult*& pSrcResult, int nWhich )
{
    pResult    = GetTargetLastResult( nWhich );
    pSrcResult = GetSrcLastResult( nWhich );
    BaseCharacter* pDst = GetTarget( nWhich );

    if ( !pResult || !pSrcResult || !m_pAttacker || !pDst )
        return false;

    bool bMissStore = pResult->m_bMiss;
    
    pResult->Reset();
    pSrcResult->Reset();

    pResult->m_bMiss = bMissStore;

    // 技能是否有效
    if( !m_pSkill )
    {
        pResult->m_bMiss = true;
        return false;
    }    

    // 根据结算类型,计算伤害值(也有可能是其它的非伤害结算)
    pResult->m_stBalanceType    = m_pSkill->ustDamageBalanceType;
    pSrcResult->m_stBalanceType = m_pSkill->ustDamageBalanceType;

    return true;
}

//void CFormula::BalanceAddStatus( SResult* pResult, BaseCharacter* pTarget, BaseCharacter* pSrc )
//{
//    //技能产生的状态
//    int nRand = theRand.rand32() % RAND_NUM;
//    if( nRand > m_pSkill->ustStatusHitRate )
//    { return; }
//
//    //TODO: 计算道行
//
//    //TODO: 计算免疫
//
//    pResult->m_ustMeAddStatusID[0]     = m_pSkill->ustMeAddStatusID[0];
//    pResult->m_ustMeAddStatusLevel[0]  = m_pSkill->ustMeAddStatusLevel[0];
//
//    pResult->m_ustMeAddStatusID[1]     = m_pSkill->ustMeAddStatusID[1];
//    pResult->m_ustMeAddStatusLevel[1]  = m_pSkill->ustMeAddStatusLevel[1];
//
//    pResult->m_ustDstAddStatusID    = m_pSkill->ustDstAddStatusID;
//    pResult->m_ustDstAddStatusLevel = m_pSkill->ustDstAddStatusLevel;
//    
//    if( m_pAttacker->IsPlayer() )
//    {
//        GamePlayer *pAttacker = (GamePlayer*)m_pAttacker;
//        for( int i= 0; i<EEquipPartType_MaxEquitPart; ++i )
//        {
//            float fMeRate = (pAttacker->GetMeStatusRate(i))*DEF_PER;
//            int   nMeRate = (int)fMeRate;
//            float fDstRate = (pAttacker->GetDstStatusRate(i))*DEF_PER;
//            int   nDstRate = (int)fDstRate;
//
//            if( theRand.rand32()%ADD_STATUS_RAND_NUM < nMeRate )
//            {
//                pResult->m_ustMeAddStatusIDFrmArmour[i]    = pAttacker->GetMeAddStatus(i);
//                pResult->m_ustMeAddStatusLevelFrmArmour[i] = pAttacker->GetMeAddStatusLvl(i);
//                
//            }
//            if( theRand.rand32()%ADD_STATUS_RAND_NUM < nDstRate )
//            {
//                pResult->m_ustDstAddStatusIDFrmWeapon[i]    = pAttacker->GetDstAddStatus(i);
//                pResult->m_ustDstAddStatusLevelFrmWeapon[i] = pAttacker->GetDstAddStatusLvl(i);
//            }
//
//            //const SCharItem * pItem = pAttacker->GetAttriSuitEquipItem(i);
//            //if( !pItem )
//            //    continue;
//
//            //if( pItem->extdata.equipdata.usHP < DEF_PER )
//            //    continue;
//
//            //bool bEquipType = false;
//
//            //ItemDefine::SItemCommon *pItemSrc = GettheItemDetail().GetItemByID( pItem->ustItemID );
//            //if( !pItemSrc )
//            //    continue;
//            ////其他人
//            //if( pItemSrc->ucItemType == ItemDefine::ITEMTYPE_WEAPON )
//            //{
//            //    ItemDefine::SItemWeapon *pWeapon = (ItemDefine::SItemWeapon *)pItemSrc;
//            //    if(    theRand.rand32()%100 < pWeapon->fStatusRate )
//            //    {
//            //        pResult->m_ustDstAddStatusIDFrmWeapon[i]    = pWeapon->stAddStatus;
//            //        pResult->m_ustDstAddStatusLevelFrmWeapon[i] = pWeapon->stAddStatusLevel;
//            //    }
//            //}
//            ////自身
//            //if( pItemSrc->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
//            //{
//            //    ItemDefine::SItemArmour *pArmour = (ItemDefine::SItemArmour *)pItemSrc;
//            //    if(    theRand.rand32()%100 < pArmour->fStatusRate )
//            //    {
//            //        pResult->m_ustMeAddStatusIDFrmArmour[i]    = pArmour->stMyAddStatus;
//            //        pResult->m_ustMeAddStatusLevelFrmArmour[i] = pArmour->stMyAddStatusLevel;
//            //    }
//            //}
//        }
//
//
//    }
//}

bool CFormula::CheckingStatus( int nTargetIndex )
{
    SResult* pResult = GetTargetLastResult( nTargetIndex ); 
    BaseCharacter* pTarget = GetTarget( nTargetIndex );

    if ( NULL == pResult || NULL == m_pSkill || NULL == pTarget )
    {
        pResult->m_bMiss = true;
        return true; 
    }

    if ( m_pAttacker->GetID() == pTarget->GetID() )
    {
        pResult->m_bMiss = false;
        return true; 
    }

    ItemDefine::SItemStatus* pMeStatus1 = GettheItemDetail().GetMeStatusBySkill(m_pSkill,ItemDefine::SItemSkill::EItemSkillConst_MeStatusFirstIndex );
    ItemDefine::SItemStatus* pMeStatus2 = GettheItemDetail().GetMeStatusBySkill(m_pSkill,ItemDefine::SItemSkill::EItemSkillConst_MeStatusSecondIndex);
    ItemDefine::SItemStatus* pDstStatus = GettheItemDetail().GetDstStatusBySkill(m_pSkill);

    if ( NULL != pMeStatus1)
    {
        if ( pMeStatus1->bAvail )
        {
            pResult->m_bMiss = false;
            return true; 
        }
    }

    if ( NULL != pMeStatus2)
    {
        if ( pMeStatus2->bAvail )
        {
            pResult->m_bMiss = false;
            return true; 
        }
    }

    if ( NULL != pDstStatus)
    {
        if (pDstStatus->bAvail)
        {
            if ( m_pAttacker->CheckCanAttackTarget( pTarget ) )
            {
				//对敌人施放有利状态 闪避 修改下 xuda
				if(m_pSkill && m_pSkill->ustCastTarget == ItemDefine::casttarget_live)
					 pResult->m_bMiss = false;
				else
					pResult->m_bMiss = true;
                return true; 
            }
            else
            {
                pResult->m_bMiss = false;
                return true;  
            }
        }
        else
        {
            // 判断折光
            if ( pTarget->_buffManager.GetHurtImmunity() > 0 )
            {
                pResult->m_bMiss = true;
                pResult->m_bHurtImmunity = true;
                int nHurtImmunity = pTarget->_buffManager.GetHurtImmunity() - 1;
                pTarget->_buffManager.SetHurtImmunity( nHurtImmunity );
                pTarget->UpdateBuff();
                return true;
            }
        }
    }

    return false;
}

void CFormula::BalanceMissHero( int nTargetIndex )
{
    SResult* pResult = GetTargetLastResult( nTargetIndex ); 
    BaseCharacter* pTarget = GetTarget( nTargetIndex );

    if ( NULL == pResult || NULL == m_pSkill || NULL == pTarget )
    {
        pResult->m_bMiss = true;
        return; 
    }

    if ( m_pAttacker->GetID() == pTarget->GetID() )
    {
        pResult->m_bMiss = false;
        return; 
    }

    // 验证状态是否加对
    if ( CheckingStatus( nTargetIndex ) )
    { return;  }

    SArmsParamModulusCommon& gArmsParamModulusCommon = theDataCenter.GetArmsParamModulusCommon();
    
    int nTempExact = 0.0f;
    if ( m_pSkill->stSkillHitRate > 0 )
    { nTempExact = m_pSkill->stSkillHitRate; }
    else
    {// 命中几率 = MAX( 15 , A命中/ (A命中+B闪避) ) * 系数
        int nAttackerExact = m_pAttacker->GetCharFightAttr()->exact.final;
        int nTargetDodge   = pTarget->GetCharFightAttr()->dodge.final;
        int nDenominator   = nAttackerExact + nTargetDodge;

        if (nDenominator > 0)
        { nTempExact = nAttackerExact * DEF_PER_INT / nDenominator * ( gArmsParamModulusCommon.GetExactModulus() * DEF_PERCENT ) ; }
    }

    int16 nFinalExact = max( gArmsParamModulusCommon.GetExactMinValue() , nTempExact ); 

    if ( nFinalExact <= 0 )
    { 
        pResult->m_bMiss = true;
        return;
    }
    else if( nFinalExact >= 100)
    {
        pResult->m_bMiss = false;
        return;
    }
    else
    {
        short nRandNumber = theRand.rand32() % (RAND_NUM);
        if ( nRandNumber <= nFinalExact)
        { pResult->m_bMiss = false; }
        else
        { pResult->m_bMiss = true; }
    }
}

void CFormula::BalanceDamageHero( int nWhich,int iAttackHand )
{
    SResult* pResult    = NULL;
    SResult* pSrcResult = NULL;
    
    if( !InitBalanceDamageData( pResult, pSrcResult, nWhich ) )
        return;

    if ( !pResult || !pSrcResult || !m_pSkill)
        return;

    if( pResult->m_bMiss )
        return;

    // 解除状态
    pResult->m_dwSubComboStatus = m_pSkill->dwSubComboStatus;
    for( int i = 0; i<ItemDefine::CLEAR_MAX_STATUS; ++i )
    {
        pResult->m_dwClearStatus[i] = m_pSkill->dwClearStatus[i];
    }

    for ( int i=0; i< ItemDefine::SItemSkill::EItemSkillConst_DispelStatusMaxSize; ++i )
    {
        pResult->m_nDispelNegativeType[i] = m_pSkill->dispelNegativeType[i];
    }

    // 调用自定义公式
    CallCustomBanalanceHero( pResult, pSrcResult, nWhich,iAttackHand );
}

void CFormula::BalanceAddStatusHero( SResult* pResult, BaseCharacter* pTarget )
{
    if( NULL == m_pSkill || NULL == pTarget || NULL == m_pAttacker || NULL == pResult )
    { return ; }
  
    if( m_pAttacker->IsPlayer() && m_pAttacker->GetID() != pTarget->GetID() )
    {
        ItemDefine::SItemStatus* pDstStatus = GettheItemDetail().GetDstStatusBySkill(m_pSkill);
        if ( pDstStatus == NULL || !pDstStatus->bAvail )
        {
            GamePlayer *pAttacker = (GamePlayer*)m_pAttacker;
            for( int i= 0; i<EEquipPartType_MaxEquitPart; ++i )
            {
                
                if ( pAttacker->GetMeAddStatusTrigger(i) == ItemDefine::EEquipStatusTrigger_Attack )
                {
                    int nMeRate  = (int) (pAttacker->GetMeStatusRate(i));
                    if( theRand.rand32() % ADD_STATUS_RAND_NUM < nMeRate )
                    {
                        pResult->m_ustMeAddStatusIDFromEquip[i]     = pAttacker->GetMeAddStatus(i);
                        pResult->m_ustMeAddStatusLevelFromEquip[i]  = pAttacker->GetMeAddStatusLvl(i);

                    }
                }

                if ( pAttacker->GetDstAddStatusTrigger(i) == ItemDefine::EEquipStatusTrigger_Attack )
                {
                    int nDstRate = (int) (pAttacker->GetDstStatusRate(i));
                    if( theRand.rand32() % ADD_STATUS_RAND_NUM < nDstRate )
                    {
                        pResult->m_ustDstAddStatusIDFromEquip[i]    = pAttacker->GetDstAddStatus(i);
                        pResult->m_ustDstAddStatusLevelFromEquip[i] = pAttacker->GetDstAddStatusLvl(i);
                    }
                }
            }
        }
    }

    if ( pTarget->IsPlayer() && m_pAttacker->GetID() != pTarget->GetID() )
    {
        ItemDefine::SItemStatus* pDstStatus = GettheItemDetail().GetDstStatusBySkill(m_pSkill);
        if ( pDstStatus == NULL || !pDstStatus->bAvail )
        {
            GamePlayer *pTargeter = (GamePlayer*)pTarget;
            for( int i= 0; i<EEquipPartType_MaxEquitPart; ++i )
            {

                if ( pTargeter->GetMeAddStatusTrigger(i) == ItemDefine::EEquipStatusTrigger_BeAttack || 
                        pTargeter->GetMeAddStatusTrigger(i) == ItemDefine::EEquipStatusTrigger_Damage  )
                {
                    int nMeRate = (int) (pTargeter->GetMeStatusRate(i));
                    if( theRand.rand32() % ADD_STATUS_RAND_NUM < nMeRate )
                    {
                        pResult->m_ustDstAddStatusIDFromEquip[i]    = pTargeter->GetMeAddStatus(i);
                        pResult->m_ustDstAddStatusLevelFromEquip[i] = pTargeter->GetMeAddStatusLvl(i);
                    }
                }

                if ( pTargeter->GetDstAddStatusTrigger(i) == ItemDefine::EEquipStatusTrigger_BeAttack ||
                        pTargeter->GetDstAddStatusTrigger(i) == ItemDefine::EEquipStatusTrigger_Damage   )
                {
                    int nDstRate = (int) (pTargeter->GetDstStatusRate(i));
                    if( theRand.rand32() % ADD_STATUS_RAND_NUM < nDstRate )
                    {
                        pResult->m_ustMeAddStatusIDFromEquip[i]    = pTargeter->GetDstAddStatus(i);
                        pResult->m_ustMeAddStatusLevelFromEquip[i] = pTargeter->GetDstAddStatusLvl(i);
                    }
                }
            }
        }
    }

    //技能产生的状态
    int nRand = theRand.rand32() % RAND_NUM;
    if( nRand > m_pSkill->ustStatusHitRate )
    { return; }

    pResult->m_ustMeAddStatusID[0]     = m_pSkill->ustMeAddStatusID[0];
    pResult->m_ustMeAddStatusLevel[0]  = m_pSkill->ustMeAddStatusLevel[0];

    pResult->m_ustMeAddStatusID[1]     = m_pSkill->ustMeAddStatusID[1];
    pResult->m_ustMeAddStatusLevel[1]  = m_pSkill->ustMeAddStatusLevel[1];

    for (int i=0;i<ItemDefine::SItemSkill::EItemSkillConst_AddStatusMaxSize;++i)
    { BalanceAddDstStatusHero( pResult, pTarget, i ); }

	

    //if (m_pSkill->bNeedTestBackStrike && nRand < (m_pSkill->fBackStrikeStatusRate*100))
    //{
    //    //背击给我的状态
    //    pResult->m_stBackStrikeAddMeStatus      = m_pSkill->stBackStrikeMeStatus;
    //    pResult->m_stBackStrikeAddMeStatusLevel = m_pSkill->stBackStrikeMeStatusLevel;

    //    //背击给对方的状态
    //    pResult->m_stBackStrikeAddDstStatus     = m_pSkill->stBackStrikeDstStatus;
    //    pResult->m_stBackStrikeAddDstStatusLevel= m_pSkill->stBackStrikeDstStatusLevel;
    //}    
}

void CFormula::BalanceAddDstStatusHero( SResult* pResult, BaseCharacter* pTarget, uint8 index )
{
    if( NULL == m_pSkill || NULL == pTarget || NULL == m_pAttacker || NULL == pResult )
    { return ; }

    if (index >= ItemDefine::SItemSkill::EItemSkillConst_AddStatusMaxSize )
    { return ; }

    if (m_pSkill->ustDstAddStatusID[index] <= 0)
    { return ; }

    ItemDefine::SItemStatus* pItemStatus = GettheItemDetail().GetStatus(m_pSkill->ustDstAddStatusID[index],m_pSkill->ustDstAddStatusLevel[index]);

    if ( pItemStatus != NULL )
    {
        bool bAdd = false;

        switch ( pItemStatus->negativeType )
        {
        case SNT_GIDDY:      
        case SNT_STAND:
        case SNT_SLOWDOWN:    
        case SNT_TORPID:      
        case SNT_HURT:        
        case SNT_ATTR:        
        case SNT_AFRAID:      
        case SNT_SLEEP:       
        case SNT_DISTORTION:  
        case SNT_FROST:       
        case SNT_SNEERAT:     
        case SNT_FORGET:      
        case SNT_ILLIBERALITY:
        case SNT_ATONY:       
        case SNT_ALLURE:      
            {

                int negativeType = pItemStatus->negativeType;
                int nQuotient = 100;

                if ( pTarget->GetDaoxing() != 0 )
                { nQuotient = m_pAttacker->GetDaoxing() * DEF_PER_INT / pTarget->GetDaoxing(); }

                pTarget->ResetDaoxingEffect();
                DaoxingConfig::SDaoxingEffect* pDaoxing = theDaoxingConfig.GetDaoxingEffect(nQuotient);

                if ( pDaoxing == NULL )
                { return; }

                int resist = pDaoxing->resist[negativeType];
                if (resist != 0)
                {
                    int nRand = theRand.rand32() % RAND_NUM;
                    if( nRand < resist )
                    { 
                        pResult->m_nDaoxingEffect = e_Resist;
                        break; 
                    }
                }

                bAdd = true;
                if (pDaoxing->addTimePer[negativeType] > 0)
                { pResult->m_nDaoxingEffect = e_Stifle; }

                int nDurationTime = pItemStatus->iDurationTime + pItemStatus->iDurationTime * pDaoxing->addTimePer[negativeType] * DEF_PERCENT;
                pTarget->SetDaoxingEffect( pItemStatus->ustItemID, nDurationTime );

            }
            break;
        default:
            { bAdd = true; }
            break;
        }

        if ( bAdd )
        {
            pResult->m_ustDstAddStatusID[index]    = m_pSkill->ustDstAddStatusID[index];
            pResult->m_ustDstAddStatusLevel[index] = m_pSkill->ustDstAddStatusLevel[index];

            // 状态附加伤害
            if ( !IsFloatZero( m_pSkill->fDamageRate ) && pItemStatus->stChanged_HP < 0 )
            { pResult->m_iDamage -= pItemStatus->stChanged_HP; }
        }
    }
}

bool CFormula::TryBackStrikeDamage(int nWhich, SResult* pResult, SResult* pSrcResult )
{
    BaseCharacter* pDst = GetTarget( nWhich );
    if( NULL == m_pSkill || NULL == pDst || NULL == m_pAttacker || !pDst->IsCanBeAttackedObject() || !m_pAttacker->IsCanBeAttackedObject() )
    { return false; }

    if( !m_pSkill->bNeedTestBackStrike )
    { return false; }

    if( !m_pAttacker->IsInTargetBack( pDst, D3DX_PI*0.7f ) )
    { return false; }

    int backStrike = m_pAttacker->GetCharFightAttr()->backStrike.final;
    int backStrikeResist = pDst->GetCharFightAttr()->backStrikeResist.final;

    if ( ( backStrike - backStrikeResist ) < DEF_PER_INT )
    { return false; }

    int nCurTotalDamage = pResult->m_iDamage;
    pResult->m_iDamage  = nCurTotalDamage * ( backStrike - backStrikeResist ) * DEF_PERCENT;
    pResult->m_bBackHit = true;
    pResult->m_nBackAttackDamage = pResult->m_iDamage - nCurTotalDamage;

    // 人物
    pDst->OnBeBackAttack();

    int nRand = theRand.rand32() % RAND_NUM;
    if (m_pSkill->bNeedTestBackStrike && nRand < (m_pSkill->fBackStrikeStatusRate * 100))
    {
        //背击给我的状态
        pResult->m_stBackStrikeAddMeStatus      = m_pSkill->stBackStrikeMeStatus;
        pResult->m_stBackStrikeAddMeStatusLevel = m_pSkill->stBackStrikeMeStatusLevel;

        //背击给对方的状态
        pResult->m_stBackStrikeAddDstStatus     = m_pSkill->stBackStrikeDstStatus;
        pResult->m_stBackStrikeAddDstStatusLevel= m_pSkill->stBackStrikeDstStatusLevel;
    }

    return true;
}

bool CFormula::TryCriticalDamageHero(int nWhich, SResult* pResult, SResult* pSrcResult )
{
    BaseCharacter* pDst = GetTarget( nWhich );
    if( NULL == m_pSkill || NULL == pDst || NULL == m_pAttacker || !pDst->IsCanBeAttackedObject() || !m_pAttacker->IsCanBeAttackedObject() )
    { return false; }

    SArmsParamModulusCommon& gArmsParamModulusCommon = theDataCenter.GetArmsParamModulusCommon();

    // 暴击几率 = max( 0 ,( A暴击 - 目标B韧性 ) * 系数 ) / 100
    float critical = m_pAttacker->GetCharFightAttr()->critical.final;
    float tenacity = pDst->GetCharFightAttr()->tenacity.final;

    int nTempCritical  = 0 ;
    if (m_pSkill->addtionalCritical > 0)
    {
		nTempCritical = m_pSkill->addtionalCritical * RAND_THOUSAND;
	}
    else
    {
		/*
		 * Author:	2012-8-1 wangshuai
		 * Desc: 	根据策划要求, 修改暴击公式
		 */
		// 老的暴击公式
		//nTempCritical = (critical - tenacity) * RAND_THOUSAND * ( gArmsParamModulusCommon.GetCriticalModulus() * DEF_PERCENT );

		nTempCritical = (critical / (critical + tenacity)) * RAND_THOUSAND * ( gArmsParamModulusCommon.GetCriticalModulus() * DEF_PERCENT );
	}

    int nCriticalFinal = max( gArmsParamModulusCommon.GetCriticalMinValue() , nTempCritical );

    bool  bHaveCritical = false;
    if ( nCriticalFinal <=0 )
    { bHaveCritical = false; }
    else if ( nCriticalFinal >= RAND_NUM * RAND_THOUSAND)
    { bHaveCritical = true; }
    else
    {
        int nRandNum = theRand.rand32() % RAND_NUM * RAND_THOUSAND;
        if ( nRandNum < nCriticalFinal )
        { bHaveCritical = true; }
    }

    if (bHaveCritical)
    {
        pResult->m_bCriticalHit = true;

        int nCurTotalDamage     = pResult->m_iDamage;
        int criticalIntensity   = m_pAttacker->GetCharFightAttr()->criticalIntensity.final;

        pResult->m_iDamage      = nCurTotalDamage * criticalIntensity * DEF_PERCENT;
    }

    return bHaveCritical;
}

void CFormula::CallCustomBanalanceHero( SResult*& pResult, SResult*& pSrcResult, int nWhich ,int iAttackHand)
{
    switch (m_pSkill->ustDamageBalanceType)
    {
    case ItemDefine::balancetype_none:                     // 没有任何伤害
        CallByBalanceTypeNoneHero( pResult, pSrcResult, nWhich );
        break;
    case ItemDefine::balancetype_damagephysicaldefend:     // 物理伤害结算
        CallByBalanceTypePhyDamageHero( pResult, pSrcResult, nWhich ,iAttackHand);
        break;
    case ItemDefine::balancetype_damagemagicdefend:        // 魔法伤害结算
        CallByBalanceTypeMagDamageHero( pResult, pSrcResult, nWhich );
        break;
    case ItemDefine::balancetype_damagebothdefend:         // 物防魔防伤害结算
        CallByBalanceTypeBothDamageHero( pResult, pSrcResult, nWhich ,iAttackHand);
        break;
    case ItemDefine::balancetype_restorehpmp:              // 回HP MP结算
        CallByBalanceTypeRestoreHpMp( pResult, nWhich );
        break;
    case ItemDefine::balancetype_relive:                   // 复活恢复HP
        CallByBalanceTypeRelive( pResult, nWhich );
        break;
    default:
        { assert(!"CallCustomBanalanceHero() 技能结算公式填写错误 !"); }
        break;
    }
}

void CFormula::CallByBalanceTypeNoneHero( SResult* pResult, SResult* pSrcResult, int nWhich )
{   
    if ( !m_pSkill || !m_pAttacker || !pResult || !pSrcResult)
    { return; }

    // 附加状态结算
    BalanceAddStatusHero( pResult, GetTarget( nWhich ) );

    // 设置吟唱
    if ( m_pSkill->bNextNotIntonate )
    {
        m_pAttacker->_buffManager.SetNextNotIntonate( true );
        m_pAttacker->_buffManager.SetNextNotIntonateNum( m_pSkill->nNextNotIntonateNum );
    }
       
}

int CFormula::CalcSuckHp( int iDamage )
{
    float suckHpRate  = m_pAttacker->_buffManager.GetSuckHpRate();
    int   suckHpValue = m_pAttacker->_buffManager.GetSuckHpValue();

    if ( (suckHpRate > 0 || suckHpValue) && m_pSkill && m_pSkill->shCastType == ItemDefine::casttype_singletarget )
    {
        uint8 suckProbability = m_pAttacker->_buffManager.GetSuckHpProbability();
        uint8 randNum = theRand.rand32() % RAND_NUM;
        if ( randNum < suckProbability )
        { suckHpValue = iDamage * suckHpRate + suckHpValue;}
        else
        { suckHpValue = 0; }
    }

    return suckHpValue;
}

int CFormula::CalcDamageReflect( BaseCharacter* pTarget, int iDamage )
{ // 物理伤害反弹
    if ( pTarget == NULL )
    { return 0; }

    float fDamageReflectRate       = pTarget->_buffManager.GetDamageReflectedRatio();
    uint8 nDamageReflectProability = pTarget->_buffManager.GetDamageReflectProability();

    if ( IsFloatZero(fDamageReflectRate) || nDamageReflectProability == 0)
    { return 0; }

    if ( theRand.rand32() % RAND_NUM >= nDamageReflectProability )
    { return 0; }

    //float fTargetDefend = 0.0f;
    //float fAttackerDefend = 0.0f;
    //switch (m_pSkill->ustDamageBalanceType)
    //{
    //case ItemDefine::balancetype_damagephysicaldefend: // 物理伤害结算
    //    {
    //        fTargetDefend   = pTarget->GetCharFightAttr()->defendPhysics.final;
    //        fAttackerDefend = m_pAttacker->GetCharFightAttr()->defendPhysics.final;
    //    }
    //    break;
    //case ItemDefine::balancetype_damagemagicdefend: // 魔法伤害结算
    //    {
    //        fTargetDefend   = pTarget->GetCharFightAttr()->defendMagic.final;
    //        fAttackerDefend = m_pAttacker->GetCharFightAttr()->defendMagic.final;
    //    }
    //    break;
    //default:
    //    return 0;
    //}

    //if ( fAttackerDefend == 0)
    //{ fAttackerDefend = 1;}
 
    return iDamage * fDamageReflectRate;
}

bool CFormula::IsHaveDamageToHp( BaseCharacter* pTarget )
{
    return pTarget->_buffManager.GetDamageToHp() != 0;
}

int CFormula::CalcDamageToHp( BaseCharacter* pTarget, int iDamage )
{
    uint8 toRate = pTarget->_buffManager.GetDamageToHp();
    if ( toRate == 0 )
    { return 0;}
    
    int toHp = iDamage * toRate / DEF_PER;
        
    return toHp;
}

void CFormula::CallByBalanceTypePhyDamageHero( SResult* pResult, SResult* pSrcResult, int nWhich, int iAttackHand )
{
    BaseCharacter* pTarget = GetTarget(nWhich);
    if (NULL == pTarget || NULL == m_pSkill)
    { return ; }

    // 附加状态结算
    BalanceAddStatusHero( pResult, pTarget );

	//被动技能结算
	if(m_pAttacker)
	{
		m_pAttacker->TryPassivenessTriggerAttack();
	}

    // 伤害率为零则不进行伤害结算
    if ( IsFloatZero( m_pSkill->fDamageRate ) )
    { return ; }

    int iNormalDamage = CalcNormalDamage( ItemDefine::balancetype_damagephysicaldefend, nWhich, pResult, pSrcResult ); // 物理伤害
    int iAdditionalDamage = CalcAdditionalDamage( nWhich, pResult, pSrcResult );

    // 攻击伤害
    pResult->m_iDamage += iNormalDamage + iAdditionalDamage;

    // 背击伤害
    TryBackStrikeDamage   ( nWhich, pResult, pSrcResult );

    // 暴击伤害
    TryCriticalDamageHero ( nWhich, pResult, pSrcResult );

    int  nDamageReflect = 0;
    int  nSuckHp        = 0;

    bool bHaveDamageToHp = IsHaveDamageToHp( pTarget );    
    if ( bHaveDamageToHp )
    { // 有伤害转换成HP
        pResult->m_iHPRestore      += CalcDamageToHp( pTarget, pResult->m_iDamage );
        pResult->m_iDamage = 0;
    }
    else
    { // 无伤害装换成HP
        pSrcResult->m_iDamage      += CalcDamageReflect( pTarget, pResult->m_iDamage ); // 物理伤害反弹
        pSrcResult->m_nExtraHp     += CalcSuckHp( pResult->m_iDamage );                 // 吸血判定
    }

    CalcTargetSuckDamage( pTarget, pResult );

    SArmsParamModulusCommon& gArmsParamModulusCommon = theDataCenter.GetArmsParamModulusCommon();

    if ( pTarget->IsMonster() )
    { 
        MonsterBaseEx* pAIChar = (MonsterBaseEx*) pTarget;
        if ( !pAIChar->IsPet() && (pAIChar->GetMonsterType() != eMT_Pet) )
        {
            pResult->m_nBackAttackDamage = pResult->m_nBackAttackDamage * gArmsParamModulusCommon.GetAttackMonsterModulus();
            pResult->m_iDamage = pResult->m_iDamage * gArmsParamModulusCommon.GetAttackMonsterModulus(); 
        }

		// 如果攻击方是有家族的玩家，则伤害加成5%
		if ( m_pAttacker->IsPlayer() )
		{
			GamePlayer* pTemPlayer = ( GamePlayer* )m_pAttacker;
			GameFamily* pFamily    = pTemPlayer->GetFamily();

			if ( pTemPlayer != NULL && pFamily != NULL )
			{
				int nAttackerTotem = pFamily->GetFamilyTotem();
				int nBeAtrackerTotem = pAIChar->GetPhyle();

				pResult->m_iDamage += pResult->m_iDamage * thePhyleChastenConfig.GetDamageByTotem( nAttackerTotem, nBeAtrackerTotem ) * DEF_PERCENT;
			}
			
		}
    }

	CalcBeDamagePerHP(pTarget, pResult);
} 

// 被结算公式调用 魔法伤害结算
void CFormula::CallByBalanceTypeMagDamageHero( SResult* pResult, SResult* pSrcResult, int nWhich )
{
    BaseCharacter* pTarget = GetTarget(nWhich);
    if (NULL == pTarget || NULL == m_pSkill)
    { return ; }

    // 附加状态结算
    BalanceAddStatusHero( pResult, pTarget );

	//被动技能结算
	if(m_pAttacker)
	{
		m_pAttacker->TryPassivenessTriggerAttack();
	}


    // 伤害率为零则不进行伤害结算
    if ( IsFloatZero( m_pSkill->fDamageRate ) )
    { return ; }

    int iNormalDamage = CalcNormalDamage( ItemDefine::balancetype_damagemagicdefend, nWhich , pResult, pSrcResult); // 魔法伤害
    int iAdditionalDamage = CalcAdditionalDamage( nWhich, pResult, pSrcResult );

    // 攻击伤害
    pResult->m_iDamage += iNormalDamage + iAdditionalDamage;

    // 背击伤害
    TryBackStrikeDamage   ( nWhich, pResult, pSrcResult );

    // 暴击伤害
    TryCriticalDamageHero ( nWhich, pResult, pSrcResult ); 

    bool bHaveDamageToHp = IsHaveDamageToHp( pTarget );    
    if ( bHaveDamageToHp )
    { // 有伤害转换成HP
        pResult->m_iHPRestore      += CalcDamageToHp( pTarget, pResult->m_iDamage );
        pResult->m_iDamage = 0;
    }
    else
    { // 无伤害装换成HP
        pSrcResult->m_iDamage      += CalcDamageReflect( pTarget, pResult->m_iDamage ); // 物理伤害反弹
        pSrcResult->m_nExtraHp  += CalcSuckHp( pResult->m_iDamage );                 // 吸血判定
    }

    CalcTargetSuckDamage( pTarget, pResult );

    SArmsParamModulusCommon& gArmsParamModulusCommon = theDataCenter.GetArmsParamModulusCommon();

    if (pTarget->IsMonster())
    { 
        MonsterBaseEx* pAIChar = (MonsterBaseEx*) pTarget;
        if ( !pAIChar->IsPet() && (pAIChar->GetMonsterType() != eMT_Pet) )
        {
            pResult->m_nBackAttackDamage = pResult->m_nBackAttackDamage * gArmsParamModulusCommon.GetAttackMonsterModulus();
            pResult->m_iDamage = pResult->m_iDamage * gArmsParamModulusCommon.GetAttackMonsterModulus(); 
        }

		// 如果攻击方是有家族的玩家，则伤害加成5%
		if ( m_pAttacker->IsPlayer() )
		{
			GamePlayer* pTemPlayer = ( GamePlayer* )m_pAttacker;
			GameFamily* pFamily = pTemPlayer->GetFamily();
			if ( pTemPlayer != NULL && pFamily != NULL )
			{
				int nAttackerTotem = pFamily->GetFamilyTotem();
				int nBeAtrackerTotem = pAIChar->GetPhyle();

				pResult->m_iDamage += pResult->m_iDamage * thePhyleChastenConfig.GetDamageByTotem( nAttackerTotem, nBeAtrackerTotem ) / 100;
			}
		}
    }

	CalcBeDamagePerHP(pTarget, pResult);
}

void CFormula::CallByBalanceTypeBothDamageHero( SResult* pResult, SResult* pSrcResult, int nWhich, int iAttackHand )
{
    BaseCharacter* pTarget = GetTarget(nWhich);
    if (NULL == pTarget || NULL == m_pSkill)
    { return ; }

    // 附加状态结算
    BalanceAddStatusHero( pResult, pTarget );

	//被动技能结算
	if(m_pAttacker)
	{
		m_pAttacker->TryPassivenessTriggerAttack();
	}


    // 伤害率为零则不进行伤害结算
    if ( IsFloatZero( m_pSkill->fDamageRate ) )
    { return ; }

    int iNormalDamage = CalcNormalDamage( ItemDefine::balancetype_damagebothdefend, nWhich , pResult, pSrcResult);
    int iAdditionalDamage = CalcAdditionalDamage( nWhich, pResult, pSrcResult );

    // 攻击伤害
    pResult->m_iDamage += iNormalDamage + iAdditionalDamage;

    // 背击伤害
    TryBackStrikeDamage   ( nWhich, pResult, pSrcResult );

    // 暴击伤害
    TryCriticalDamageHero ( nWhich, pResult, pSrcResult ); 

    bool bHaveDamageToHp = IsHaveDamageToHp( pTarget );    
    if ( bHaveDamageToHp )
    { // 有伤害转换成HP
        pResult->m_iHPRestore   += CalcDamageToHp( pTarget, pResult->m_iDamage );
        pResult->m_iDamage = 0;
    }
    else
    { // 无伤害装换成HP
        pSrcResult->m_iDamage   += CalcDamageReflect( pTarget, pResult->m_iDamage ); // 物理伤害反弹
        pSrcResult->m_nExtraHp  += CalcSuckHp( pResult->m_iDamage );                 // 吸血判定
    }

    CalcTargetSuckDamage( pTarget, pResult );

    SArmsParamModulusCommon& gArmsParamModulusCommon = theDataCenter.GetArmsParamModulusCommon();

    if (pTarget->IsMonster())
    { 
        MonsterBaseEx* pAIChar = (MonsterBaseEx*) pTarget;
        if ( !pAIChar->IsPet() && (pAIChar->GetMonsterType() != eMT_Pet) )
        {
            pResult->m_nBackAttackDamage = pResult->m_nBackAttackDamage * gArmsParamModulusCommon.GetAttackMonsterModulus();
            pResult->m_iDamage = pResult->m_iDamage * gArmsParamModulusCommon.GetAttackMonsterModulus(); 
        }

		// 如果攻击方是有家族的玩家，则伤害加成5%
		if ( m_pAttacker->IsPlayer() )
		{
			GamePlayer* pTemPlayer = ( GamePlayer* )m_pAttacker;
			GameFamily* pFamily = pTemPlayer->GetFamily();

			if ( pTemPlayer != NULL && pFamily != NULL )
			{
				int nAttackerTotem = pFamily->GetFamilyTotem();
				int nBeAtrackerTotem = pAIChar->GetPhyle();

				pResult->m_iDamage += pResult->m_iDamage * thePhyleChastenConfig.GetDamageByTotem( nAttackerTotem, nBeAtrackerTotem ) / 100;
			}
		}
    }

	CalcBeDamagePerHP(pTarget, pResult);
}

void CFormula::CallByBalanceTypeRestoreHpMp( SResult* pResult, int nWhich  )
{
    BaseCharacter* pDst = GetTarget( nWhich );
    if( !m_pSkill || !pDst || !m_pAttacker || !pDst->IsCanBeAttackedObject() || !m_pAttacker->IsCanBeAttackedObject() )
    { return; }

    // 附加状态结算
    BalanceAddStatusHero( pResult, GetTarget( nWhich ) );

    //根据攻击力计算血量
    int nHPRestore = 0;
    int nChangeHP  = 0;
    int nChangeMP  = 0;
    int nHPBaseRestore = 0;
    int nHPMaxRestore  = 0;
    int nMPBaseRestore = 0;
    int nMPMaxRestore  = 0;
    int nXinFaHPRestore= 0;

    if ( !IsFloatZero( m_pSkill->fDamageRate ) )
    { 
        float fDamageRate = m_pSkill->fDamageRate;
        float attack = 0;
        if ( m_pSkill->additionalPhyAttack > 0 )
        { attack = m_pAttacker->GetCharFightAttr()->attackPhysics.final + m_pSkill->additionalPhyAttack; }
        else
        { attack = m_pAttacker->GetCharFightAttr()->attackMagic.final   + m_pSkill->additionalMagAttack; }
        
        int nRand = theRand.rand32() % ATTACK_FLOAT_COUNT;
        int nAttackFloating = 0;
        if ( m_pAttacker->IsPlayer())
        {        
            SArmsParamModulusExtend* pArmsParamModulusExtend = DataCenter::GetInstance().GetArmsParamModulus( m_pAttacker->GetProfession() );
            if ( NULL == pArmsParamModulusExtend )
            { return; }
            nAttackFloating = pArmsParamModulusExtend->sAttackFloating[nRand];
        }
        else if ( m_pAttacker->IsMonster() )
        {
            MonsterBaseEx* pMonster = (MonsterBaseEx*)pDst;
            nAttackFloating = pMonster->GetAttackFloat();
        }

        nHPRestore += attack * fDamageRate * ( nAttackFloating  * DEF_PER_REC );
    }

    ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatusBySkill( m_pSkill );
    if (pStatus != NULL)
    { 
        //改变生命
        nChangeHP = pStatus->stChanged_HP;

        //恢复人物基础血量%
        nHPBaseRestore = pDst->GetCharFightAttr()->hpMax.base * pStatus->recoverHPBasePer * DEF_PERCENT;

        //恢复人物基础最大值%
        nHPMaxRestore  = pDst->GetCharFightAttr()->hpMax.final * pStatus->recoverHPMaxPer * DEF_PERCENT;

        //改变魔法
        nChangeMP = pStatus->stChanged_MP;

        //恢复人物MP基础%
        nMPBaseRestore = pDst->GetCharFightAttr()->mpMax.base * pStatus->recoverMPBasePer * DEF_PERCENT;

        //恢复人物MP上限%
        nMPMaxRestore  = pDst->GetCharFightAttr()->mpMax.final * pStatus->recoverMPMaxPer * DEF_PERCENT;
    }

    if (m_pAttacker->IsPlayer())
    {
        GamePlayer* pPlayer = static_cast<GamePlayer*> ( m_pAttacker );
        nXinFaHPRestore = pPlayer->GetXinFaSkillEffectValue( m_pSkill, SkillAttr_HPRestore );
    }

    int nFinalHPRestore = nHPRestore + nChangeHP + nHPBaseRestore + nHPMaxRestore + nXinFaHPRestore;
    int nFinalMPRestore = nChangeMP  + nMPBaseRestore + nMPMaxRestore;

    pResult->m_iHPRestore = nFinalHPRestore;
    pResult->m_iMPRestore = nFinalMPRestore;
}

int CFormula::CalcNormalDamage( uint8 damageType, int nWhich, SResult* pResult, SResult* pSrcResult )
{
    BaseCharacter* pDst = GetTarget( nWhich );
    if( NULL == m_pSkill || NULL == pDst || NULL == m_pAttacker || !pDst->IsCanBeAttackedObject() || !m_pAttacker->IsCanBeAttackedObject() )
    { return 0; }

    SArmsParamModulusCommon& gArmsParamModulusCommon = theDataCenter.GetArmsParamModulusCommon();

    //uint8 HurtImmunity = EAttackType_Max;

    //BuffStatusManager* pFightStatus = pDst->GetBuffManager();
    //if( pDst->IsPlayer() && pFightStatus->IsHurtImmunity(HurtImmunity))
    //{ return 0; }

	float fDamageRate  = m_pSkill->fDamageRate; //伤害百分比
    //对有某个状态的目标造成额外的伤害
    if (m_pSkill->additionalDamagePer > 0)
    {
        switch ( m_pSkill->additionalDamageType )
        {
        case ItemDefine::SItemSkill::EItemSkillConst_AddDamageType_Status:
            if (pDst->_buffManager.IsHaveStatus(m_pSkill->additionalDamageStatus))
            { fDamageRate +=  m_pSkill->additionalDamagePer * DEF_PERCENT; }
            break;
        case ItemDefine::SItemSkill::EItemSkillConst_AddDamageType_Profession:
            if (pDst->GetProfession() == m_pSkill->additionalDamageProfession)
            { fDamageRate +=  m_pSkill->additionalDamagePer * DEF_PERCENT; }
            break;
        case ItemDefine::SItemSkill::EItemSkillConst_AddDamageType_All:
            { fDamageRate +=  m_pSkill->additionalDamagePer * DEF_PERCENT; }
            break;
        }
    }

    int   attackModulus= gArmsParamModulusCommon.GetAttackModulus(); //攻击系数
    int   defendModulus= gArmsParamModulusCommon.GetDefendModulus(); //防御系数
    if (attackModulus == 0 || defendModulus == 0)
    {
        assert(!"CFormula::CalcBaseDamage attackModulus or defendModulus is 0 !");
        return 0;
    }

    int nXinFaSkillAttr[SkillAttr_MaxSize] =  { 0 } ;

    if ( m_pAttacker->IsPlayer() )
    {  
        GamePlayer* pPlayer = static_cast<GamePlayer*>( m_pAttacker );
        pPlayer->GetXinFaSkillEffect( m_pSkill, nXinFaSkillAttr ); 
    }
    
    int nNormalDamage = 0;
    switch ( damageType )
    {
    case ItemDefine::balancetype_damagephysicaldefend:
        {
            int attack = m_pAttacker->GetCharFightAttr()->attackPhysics.final + m_pSkill->additionalPhyAttack + nXinFaSkillAttr[SkillAttr_PhysicsAttack];
            int defend = pDst->GetCharFightAttr()->defendPhysics.final;
            nNormalDamage = (attack / attackModulus - defend / defendModulus) * fDamageRate;
        }
        break;
    case ItemDefine::balancetype_damagemagicdefend:
        {
            int attack = m_pAttacker->GetCharFightAttr()->attackMagic.final + m_pSkill->additionalMagAttack   + nXinFaSkillAttr[SkillAttr_MagicAttack];
            int defend = pDst->GetCharFightAttr()->defendMagic.final;
            nNormalDamage = (attack / attackModulus - defend / defendModulus) * fDamageRate;
        }
        break;
    case ItemDefine::balancetype_damagebothdefend:
        {
            int attackPhysics = m_pAttacker->GetCharFightAttr()->attackPhysics.final + m_pSkill->additionalPhyAttack + nXinFaSkillAttr[SkillAttr_PhysicsAttack];
            int attackMagic   = m_pAttacker->GetCharFightAttr()->attackMagic.final   + m_pSkill->additionalMagAttack + nXinFaSkillAttr[SkillAttr_MagicAttack];
            int defendPhysics = pDst->GetCharFightAttr()->defendPhysics.final;
            int defendMagic   = pDst->GetCharFightAttr()->defendMagic.final;
            
            nNormalDamage = ((attackPhysics + attackMagic) / attackModulus - (defendPhysics + defendMagic) / defendModulus) * fDamageRate;
        }
        break;
    default:
        { return 0; }
    }

    if ( m_pAttacker->IsPlayer())
    {        
        SArmsParamModulusExtend* pArmsParamModulusExtend = theDataCenter.GetArmsParamModulus( m_pAttacker->GetProfession() );
        if ( pArmsParamModulusExtend != NULL )
        {
            int nRand = theRand.rand32() % ATTACK_FLOAT_COUNT;
            int nAttackFloating = pArmsParamModulusExtend->sAttackFloating[nRand];
            nNormalDamage = nNormalDamage * nAttackFloating * DEF_PERCENT;
        }
    }

    // 心法附加伤害
    nNormalDamage += nXinFaSkillAttr[SkillAttr_HPDamage];

    // 释放叠加状态伤害
    if (m_pSkill->releaseLapoverStatus > 0)
    {
        SCharBuff *pCharBuff = pDst->_buffManager.GetBuffByStatusID(m_pSkill->releaseLapoverStatus);
        if (pCharBuff != NULL)
        {
            ItemDefine::SItemStatus* pStatusConfig = GettheItemDetail().GetStatus( pCharBuff->StatusID, pCharBuff->iLevel );
            if ( pStatusConfig != NULL )
            {
                if (pStatusConfig->stBalanceType == ItemDefine::balance_status_type_none)
                {
                    int iLapoverDamage = pResult->m_iDamage * pCharBuff->lapoverNum * pStatusConfig->lapoverMod * DEF_PERCENT ;
                    pResult->m_iDamage += iLapoverDamage;
                }
            }

            //清理BUFF 
            pCharBuff->lapoverNum     = 0;
            pCharBuff->dwDurationTime = 0;
        }
    }
    
    return max( gArmsParamModulusCommon.GetDamageMinValue() , nNormalDamage );
}

int CFormula::CalcAdditionalDamage(int nWhich, SResult* pResult, SResult* pSrcResult )
{
    BaseCharacter* pDst = GetTarget( nWhich );
    if( NULL == m_pSkill || NULL == pDst || NULL == m_pAttacker || !pDst->IsCanBeAttackedObject() || !m_pAttacker->IsCanBeAttackedObject() )
    { return 0; }

    // 破甲伤害
    int nBreakDamage = 0;
    int breakStrike  = m_pAttacker->GetCharFightAttr()->breakStrike.final + m_pSkill->breakStrike ; 
    int breakResist  = pDst->GetCharFightAttr()->breakResist.final;
    if (breakResist < 100)
    { nBreakDamage = breakStrike * (100 - breakResist) * DEF_PERCENT; }

    // 贯穿伤害
    int nStabDamage = 0;
    int stabStrike  = m_pAttacker->GetCharFightAttr()->stabStrike.final + m_pSkill->stabStrike ; 
    int stabResist  = pDst->GetCharFightAttr()->stabResist.final;
    if (stabResist < 100)
    { nStabDamage = stabStrike * (100 - stabResist) * DEF_PERCENT; }

    // 元素抗性
    int nElementDamage = 0;
    int elementStrike  = m_pAttacker->GetCharFightAttr()->elementStrike.final + m_pSkill->elementStrike ; 
    int elementResist  = pDst->GetCharFightAttr()->elementResist.final;
    if (elementResist < 100)
    { nElementDamage = elementStrike * (100 - elementResist) * DEF_PERCENT; }

    // 毒素伤害
    int nToxinDamage   = 0;
    int toxinStrike    = m_pAttacker->GetCharFightAttr()->toxinStrike.final + m_pSkill->toxinStrike ; 
    int toxinResist    = pDst->GetCharFightAttr()->toxinResist.final;
    if (toxinResist < 100)
    { nToxinDamage = toxinStrike * (100 - toxinResist) * DEF_PERCENT; }

    // 精神伤害
    int nSpiritDamage  = 0;
    int spiritStrike   = m_pAttacker->GetCharFightAttr()->spiritStrike.final + m_pSkill->spiritStrike ; 
    int spiritResist   = pDst->GetCharFightAttr()->spiritResist.final;
    if (spiritResist < 100)
    { nSpiritDamage = spiritStrike * (100 - spiritResist) * DEF_PERCENT; }

    return nBreakDamage + nStabDamage + nElementDamage + nToxinDamage + nSpiritDamage ;
}

void CFormula::CalcTargetSuckDamage ( BaseCharacter* pDst, SResult* pResult )
{
    if ( NULL == pDst || NULL == pResult )
    { return; }

    //int nXinFaSkillAttr[SkillAttr_MaxSize] =  { 0 } ;

    //if ( m_pAttacker->IsPlayer() )
    //{  
    //    GamePlayer* pPlayer = static_cast<GamePlayer*>( m_pAttacker );
    //    pPlayer->GetXinFaSkillEffect( m_pSkill, nXinFaSkillAttr ); 
    //}

    BuffStatusManager* pDstBuffStatus  = pDst->GetBuffManager(); 
    if ( pDstBuffStatus )
    {
        int nSuckDamgeAmount = 0;

        //吸收伤害百分比
        if (pDstBuffStatus->GetSuckDamgePer() > 0)
        {
            nSuckDamgeAmount += pResult->m_iDamage * pDstBuffStatus->GetSuckDamgePer() * DEF_PERCENT;
        }

        //吸收伤害固定值
        if ( pResult->m_iDamage >  pDstBuffStatus->GetSuckDamgeMax() )
        {
            pResult->m_iDamage = pResult->m_iDamage - pDstBuffStatus->GetSuckDamgeMax();
            pResult->m_nShieldHp = pDstBuffStatus->GetSuckDamgeMax();
            pDstBuffStatus->SetSuckDamgeMax( 0 );
        }
        else
        {            
            pDstBuffStatus->SetSuckDamgeMax( pDstBuffStatus->GetSuckDamgeMax() - pResult->m_iDamage );
            pResult->m_nShieldHp = pResult->m_iDamage;
            pResult->m_iDamage = 0;
        }

        //计算总计吸收伤害值
        if (nSuckDamgeAmount > 0)
        {
            if ( pResult->m_iDamage >  nSuckDamgeAmount )
            { pResult->m_iDamage -= nSuckDamgeAmount; }
            else
            { pResult->m_iDamage = 0; }
        }
    }
}

void CFormula::CalcBeDamagePerHP(BaseCharacter* pDst, SResult* pResult )
{
	if ( NULL == pDst || NULL == pResult )
	{ return; }

	BuffStatusManager* pDstBuffStatus  = pDst->GetBuffManager(); 
	if ( pDstBuffStatus )
	{
		if (pDstBuffStatus->GetBeDamagePerHPMax() > 0&&pResult->m_iDamage > 0)
		{
			int HpMaxPer = pDst->GetHPMax()*pDstBuffStatus->GetBeDamagePerHPMax()*DEF_PERCENT;
			pResult->m_iDamage = HpMaxPer;
		}
	}
}

void CFormula::BalanceAttackHero( int iAttackHand )
{   
    // 如果缺少攻击者或被攻击者，则不可能进行攻击结算
    if( !IsAttackable() )
    { return; }

    for(int i=0;i<m_iTotalTarget; ++i)
    {
        SResult* pResult            = GetTargetLastResult(i);   // 目标结算结果
        SResult* pSrcResult         = GetSrcLastResult( i ) ;   // 攻击者结算结果
        BaseCharacter* pTargetChar  = GetTarget(i)          ;   // 被攻击目标

        if( !pResult || !pTargetChar || !m_pSkill || !pTargetChar->IsCanBeAttackedObject())
        { continue; }
 
        // 攻击命中
        BalanceMissHero     ( i )            ;
        
        // 伤害结算
        BalanceDamageHero   ( i,iAttackHand );

        // 回复结算
        //BalanceRestoreHero  ( i )            ;
    }
}
void CFormula::BalanceRestoreHero( int nWhich )
{  
    SResult* pResult            = GetTargetLastResult(nWhich);   // 目标结算结果
    SResult* pSrcResult         = GetSrcLastResult( nWhich ) ;   // 攻击者结算结果
    BaseCharacter* pTargetChar  = GetTarget(nWhich)          ;   // 被攻击目标

    if( !pResult || !pTargetChar || !m_pSkill || !pTargetChar->IsCanBeAttackedObject() )
    { return; }

    if ( pResult->m_bMiss )
    { return; }

    // XP回复
    //pSrcResult->m_iXPRestore += m_pSkill->usIncreaseFightPower;

    // 所有职业XP MP恢复
    //if (m_pAttacker->IsPlayer())
    //{ 
    //    //pSrcResult->m_iXPRestore += DEF_XP_FIGHT_RESTORE; 

    //    ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatusBySkill( m_pSkill );
    //    if (pStatus != NULL)
    //    { pSrcResult->m_iMPRestore += pStatus->stChanged_MP; }// 改变魔法
    //}

    //// 战神怒气回复 普通攻击怒气+5，被攻击怒气+2
    //if( m_pAttacker->GetID() != pTargetChar->GetID() )
    //{
    //    if ( !IsDamageSkill(m_pSkill->ustItemID) )
    //    { return; }

    //    if (pTargetChar->IsPlayer() && pTargetChar->GetProfession() == EArmType_Warrior )
    //    {
    //        pResult->m_iMPRestore += CHAR_WARRIOR_BEATTACK_RESTORE_MP;
    //    }

    //    if (m_pAttacker->IsPlayer() && m_pAttacker->GetProfession() == EArmType_Warrior )
    //    {
    //        pSrcResult->m_iMPRestore += CHAR_WARRIOR_ATTACK_RESTORE_MP;
    //    }
    //}
}

void CFormula::BalanceStatusHero()
{   
    ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus( m_ustTargetStatusID, m_ustTargetStatusLevel );
    if( !pStatus || !m_pStatusTarget )
    { return; }

    m_pStatus = pStatus;
    // 清空数据
    m_TargetStatusResult.Reset();
    m_SrcStatusResult.Reset();

    switch( pStatus->stBalanceType )
    {
        case ItemDefine::balance_status_type_none:
            CalcStatusBalanceTypeNone();
            break;
        case ItemDefine::balance_status_type_restore:
            CalcStatusBalanceTypeRestore();
            break;
        case ItemDefine::balance_status_type_timeexp:  // 在其他地方进行结算
        case ItemDefine::balance_status_type_mount:
            break;
        default:
            break;
    }
}
