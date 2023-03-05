#include "AchieveServerManager.h"
#include "GamePlayer.h"
#include "ScriptMgr.h"
#include "GlobalDef.h"

void AchieveServerManager::CreateFromData(GamePlayer* pPlayer,SAchieveData* pData)
{
    m_pPlayer = pPlayer;
    m_pAchieveData = pData;
}

uint8 AchieveServerManager::GetAchieveState( uint16 nId )
{
    AchieveConfig::Achieve* pAchieve = theAchieveConfig.GetAchieve(nId);
    if (pAchieve == NULL)
    { return ECS_Unfinished; }

    SCharAchieve* pCharAchieve = &m_pAchieveData->xAchievements[nId];

    return pCharAchieve->finishState;
}

bool AchieveServerManager::TriggerFinishAchieve(  uint16 nId  )
{
    AchieveConfig::Achieve* pAchieve = theAchieveConfig.GetAchieve(nId);
    if (pAchieve == NULL)
    { return false; }

    SCharAchieve* pCharAchieve = &m_pAchieveData->xAchievements[nId];

    if (pCharAchieve->finishState != ECS_Unfinished)
    { return true; }

    pCharAchieve->finishState = ECS_Finished;
    pCharAchieve->finishTime  = TimeEx::GetNowTime();

    MsgUpdateAchieve msg;
    msg.nIndex = nId;
    msg.nAchievePoint = m_pPlayer->GetAchievePoint();
    msg.xCharAchieve = *pCharAchieve;
    m_pPlayer->SendMessageToClient( &msg);

	GetScriptMgr()->StartupVM( ST_ACHIEVE, nId, m_pPlayer );

    return true;
}

bool AchieveServerManager::UpdateTriggerById( uint16 nId, uint32 nValue  )
{
    if ( !g_Cfg.bOpenAchievement )
    { return false; }

    AchieveConfig::Achieve* pAchieve = theAchieveConfig.GetAchieve(nId);
    if (pAchieve == NULL)
    { return false; }

    SCharAchieve* pCharAchieve = &m_pAchieveData->xAchievements[nId];

    if (pCharAchieve->finishState != ECS_Unfinished)
    { return true; }

    bool bIsFinish = false;

    switch( pAchieve->GetCompare() )
    {
    case EAC_Greater:
        {
            if ( nValue >= pAchieve->GetFinishValue() )
            { bIsFinish = true; }
        }
        break;
    case EAC_Equal:
        {
            if ( nValue == pAchieve->GetFinishValue() )
            { bIsFinish = true; }
        }
        break;
    case EAC_Less:
        {
            if ( nValue < pAchieve->GetFinishValue() )
            { bIsFinish = true; }
        }
        break;
    }

    if ( bIsFinish )
    {
        pCharAchieve->finishState = ECS_Finished;
        pCharAchieve->finishTime  = TimeEx::GetNowTime();

        MsgUpdateAchieve msg;
        msg.nIndex = nId;
        msg.nAchievePoint = m_pPlayer->GetAchievePoint();
        msg.xCharAchieve = *pCharAchieve;
        m_pPlayer->SendMessageToClient( &msg );

		GetScriptMgr()->StartupVM( ST_ACHIEVE, nId, m_pPlayer );
    }

    return true;
}

bool AchieveServerManager::UpdateTriggerByValueType( uint16 nValueType, uint32 nValue, bool bAddValue )
{
    if ( !g_Cfg.bOpenAchievement )
    { return false; }

    if (m_pPlayer == NULL || m_pAchieveData == NULL)
    { return false; }

    if ( nValueType >= More_iMaxAchieveVars )
    { return false; }

    AchieveConfig::Observer* pObserver = theAchieveConfig.GetObserver(nValueType);
    if (pObserver == NULL)
    { return false; }

    if (bAddValue)
    {// 需要累计变量
         m_pAchieveData->achieveVars[nValueType] += nValue;
         nValue = m_pAchieveData->achieveVars[nValueType] ;

         MsgUpdateAchieveVar  msg;
         msg.nValueType = nValueType;
         msg.nValue     = nValue    ;
         m_pPlayer->SendMessageToClient( &msg );

         std::vector<uint16>::iterator iter = pObserver->vecAchieveIds.begin();
         for ( ; iter != pObserver->vecAchieveIds.end(); ++iter )
         {
             UpdateTriggerById( *iter, nValue );
         }
    }
    else
    {
        uint32 nOldValue = m_pAchieveData->achieveVars[nValueType];

        if ( ( nValue == 0 ) || (nValue != nOldValue) )
        {
            m_pAchieveData->achieveVars[nValueType] = nValue;

            MsgUpdateAchieveVar  msg;
            msg.nValueType = nValueType;
            msg.nValue     = nValue    ;
            m_pPlayer->SendMessageToClient( &msg );

            std::vector<uint16>::iterator iter = pObserver->vecAchieveIds.begin();
            for ( ; iter != pObserver->vecAchieveIds.end(); ++iter )
            {
                UpdateTriggerById( *iter, nValue );
            }
        }
    }
    
    return true;
}
