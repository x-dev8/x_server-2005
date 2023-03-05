#include "AntiAddictionSystem.h"
#include"GamePlayer.h"
#include "BaseCharacter.h"
#include "Configure.h"
#include "XmlStringLanguage.h"
#include "ShareData.h"

AntiAddictionSystem::AntiAddictionSystem()
{
}

AntiAddictionSystem::~AntiAddictionSystem()
{
}

AntiAddictionSystem::sPlayerOnlineTime* AntiAddictionSystem::GetPlayerOnlineTimeById(DWORD dwDBID)
{
    if (m_vecPlayerOnlineTime.empty())
    { return NULL; }

    for (int n = 0; n < m_vecPlayerOnlineTime.size();n++)
    {
        if (m_vecPlayerOnlineTime[n].dwCharDbID == dwDBID)
        {
            return &m_vecPlayerOnlineTime[n];
        }
    }
    return NULL;
}

AntiAddictionSystem::sPlayerTimeInGame* AntiAddictionSystem::GetPlayerTimenGameById(DWORD dwDBID)
{
    if (m_vecPlayerTimeInGame.empty())
    {
        return NULL;
    }
    for (int n = 0; n < m_vecPlayerTimeInGame.size();n++)
    {
        if (m_vecPlayerTimeInGame[n].dwCharDbID == dwDBID)
        {
            return &m_vecPlayerTimeInGame[n];
        }
    }

    return NULL;
}

void AntiAddictionSystem::ApplyPlayerInGameServerTime(BaseCharacter* pChar)
{
    //if ( !pChar)
    //    return;

    //if ( !pChar->IsPlayer() )
    //    return;

    //GamePlayer* pGameplayer = (GamePlayer*)pChar;
    //if ( !pGameplayer)
    //    return;

    //if ( !g_Cfg.m_bIsOpenDefWallow)
    //    return;

    //DWORD deTimeTemp = 0;
    //bool bNeedTell = false;
    //int nTimeTemp = 0;
    //CDefWallow::sPlayerTimeInGame* pPlayerTimeInGame = GetPlayerTimenGameById(pGameplayer->GetDBCharacterID());
    //if (pPlayerTimeInGame)
    //{
    //    pPlayerTimeInGame->dwTimeInGame += pChar->GetInGameServerTime();
    //    pChar->ClearInGameServerTime();
    //    deTimeTemp = pPlayerTimeInGame->dwTimeInGame/CheckPlayerPerTime;
    //    nTimeTemp = pPlayerTimeInGame->nTellTime;
    //    if (g_Cfg.m_TellPlayerPerTime > 0 && pPlayerTimeInGame->dwTimeInGame > g_Cfg.m_nFirstPhase*1000)
    //    {
    //        DWORD dwTime = g_Cfg.m_TellPlayerPerTime*1000;
    //        if (dwTime > 0)
    //        {
    //            playertimeingame.nTellTime = playertimeingame.dwTimeInGame/dwTime;
    //        }
    //        else
    //        {
    //            playertimeingame.nTellTime = 0;
    //        }
    //        if (pPlayerTimeInGame->nTellTime > nTimeTemp)
    //        {
    //            if (deTimeTemp > 60)
    //            {
    //                int nHours = deTimeTemp/60;
    //                int nMin = deTimeTemp%60;
    //                pChar->TellClient( theXmlString.GetString(eTellClient_OnlineTimeAndHour), nHours,nMin );
    //            }
    //            else
    //            {
    //                pChar->TellClient( theXmlString.GetString(eTellClient_OnlineTime), deTimeTemp );
    //            }

    //            bNeedTell = true;
    //        }
    //    }			
    //}
    //else
    //{
    //    sPlayerTimeInGame  playertimeingame;
    //    playertimeingame.dwCharDbID = pGameplayer->GetDBCharacterID();
    //    playertimeingame.dwTimeInGame = pChar->GetInGameServerTime();
    //    playertimeingame.nTellTime = 0;
    //    pChar->ClearInGameServerTime();
    //    m_vecPlayerTimeInGame.push_back(playertimeingame);

    //    deTimeTemp = playertimeingame.dwTimeInGame/CheckPlayerPerTime;
    //    nTimeTemp = playertimeingame.nTellTime;
    //    if (g_Cfg.m_TellPlayerPerTime > 0&&playertimeingame.dwTimeInGame > g_Cfg.m_nFirstPhase*1000)
    //    {
    //        DWORD dwTime = g_Cfg.m_TellPlayerPerTime*1000;
    //        if (dwTime > 0)
    //        {
    //            playertimeingame.nTellTime = playertimeingame.dwTimeInGame/dwTime;
    //        }
    //        else
    //        {
    //            playertimeingame.nTellTime = 0;
    //        }
    //        if (nTimeTemp < playertimeingame.nTellTime)
    //        {
    //            if (deTimeTemp > 60)
    //            {
    //                int nHours = deTimeTemp/60;
    //                int nMin = deTimeTemp%60;
    //                char szTemp1 [128];
    //                _snprintf( szTemp1, sizeof(szTemp1)-1, theXmlString.GetString(eTellClient_OnlineTimeAndHour), nHours,nMin);
    //                pChar->TellClient(szTemp1);
    //            }
    //            else
    //            {
    //                char szTemp1 [128];
    //                _snprintf( szTemp1, sizeof(szTemp1)-1, theXmlString.GetString(eTellClient_OnlineTime), deTimeTemp);
    //                pChar->TellClient(szTemp1);
    //            }
    //            bNeedTell = true;
    //        }
    //    }
    //}

    //bool bFlag = false;
    //SYSTEMTIME systime;
    //GetLocalTime( &systime );
    //if (systime.wHour == g_Cfg.m_nRefreshHour &&systime.wMinute == g_Cfg.m_nRefreshMin)
    //{
    //    m_vecPlayerTimeInGame.clear();
    //    bFlag = true;
    //    pChar->TellClient(theXmlString.GetString(eTellClient_ClearOnlineTime));
    //}
    //if (bFlag == false)
    //{
    //    pPlayerTimeInGame =	GetPlayerTimenGameById(pGameplayer->GetDBCharacterID());
    //    if (pPlayerTimeInGame)
    //    {
    //        int nExp = 0;
    //        int nSkillExp = 0;
    //        DWORD dwTemp = pPlayerTimeInGame->dwTimeInGame/1000;
    //        if ( dwTemp >= g_Cfg.m_nFirstPhase)
    //        {
    //            nExp = 100 - g_Cfg.m_nFirstPhaseExpSub;
    //            nSkillExp = 100 - g_Cfg.m_nFirstPhaseSkillExpSub;
    //            if (dwTemp >= g_Cfg.m_nSecondPhase)
    //            {
    //                nExp = 100 - g_Cfg.m_nSecondPhaseExpSub;
    //                nSkillExp = 100 - g_Cfg.m_nSecondPhaseSkillExpSub;
    //                if (dwTemp >= g_Cfg.m_nThirdPhase)
    //                {
    //                    nExp = 100 - g_Cfg.m_nThirdPhaseExpSub;
    //                    nSkillExp = 100 - g_Cfg.m_nThirdPhaseSkillExpSub;
    //                }
    //            }
    //            pChar->SetExpChangePer((float)nExp/100);
    //            pChar->SetSkillExpChangePer((float)nSkillExp/100);
    //            if (bNeedTell == true)
    //            {
    //                char szTemp [128];
    //                _snprintf( szTemp, sizeof(szTemp)-1, theXmlString.GetString(eTellClient_GetExp), nExp,nSkillExp);
    //                pChar->TellClient(szTemp);
    //            }					
    //        }
    //    }
    //}
    //else
    //{
    //    int nExp = 100;
    //    int nSkillExp = 100;
    //    pChar->SetExpChangePer(1);
    //    pChar->SetSkillExpChangePer(1);
    //    char szTemp [128];
    //    _snprintf( szTemp, sizeof(szTemp)-1, theXmlString.GetString(eTellClient_GetExp), nExp,nSkillExp);
    //    pChar->TellClient(szTemp);
    //}
}

/* comment by zhangqi 2010-7-7
AntiAddictionSystem& GetAntiAddictionSystem()
{
static AntiAddictionSystem s_handle;
return s_handle;
}
*/
void AntiAddictionSystem::ClearPlayerInWorldTime(BaseCharacter* pChar)
{
    if ( pChar != NULL && pChar->IsPlayer() )
    {
        GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
        AntiAddictionSystem::sPlayerTimeInGame *pPlayerTimeInGame =NULL;
        pPlayerTimeInGame =	GetPlayerTimenGameById( pPlayer->GetDBCharacterID() );
        if (pPlayerTimeInGame)
        {
            pPlayerTimeInGame->dwTimeInGame = 0;
            int nExp = 100;
            int nSkillExp = 100;
            pPlayer->SetExpChangePer(1);
            pPlayer->SetSkillExpChangePer(1);
            char szTemp [128];
            _snprintf( szTemp, sizeof(szTemp)-1, theXmlString.GetString(eTellClient_GetExp), nExp,nSkillExp);
            pChar->TellClient(szTemp);			
        }
    }	
}

bool AntiAddictionSystem::ClearAllPlayerInWorldTime(void)
{
    if (m_vecPlayerTimeInGame.empty()||m_vecPlayerOnlineTime.empty())
    {
        return false;
    }

    int nSize = m_vecPlayerTimeInGame.size();

    for (int n = 0; n < nSize ; n++)
    {
        BaseCharacter* pChar = theRunTimeData.GetGamePlayerByDBID(m_vecPlayerTimeInGame[n].dwCharDbID);
        if ( pChar != NULL && pChar->IsPlayer() )
        {
            GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

            int nExp = 100;
            int nSkillExp = 100;
            pPlayer->SetExpChangePer(1);
            pPlayer->SetSkillExpChangePer(1);
            char szTemp [128];
            _snprintf( szTemp, sizeof(szTemp)-1, theXmlString.GetString(eTellClient_GetExp), nExp,nSkillExp);
            pChar->TellClient(szTemp);	
        }
    }
    m_vecPlayerTimeInGame.clear();
    m_vecPlayerOnlineTime.clear();
    return true;
}

void AntiAddictionSystem::SetPlayerChangePerByDbID(DWORD dwCharDbID)
{
    BaseCharacter* pChar = theRunTimeData.GetGamePlayerByDBID(dwCharDbID);
    if ( pChar != NULL && pChar->IsPlayer() )
    {
        GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

        if (m_vecPlayerTimeInGame.empty())
        {
            pPlayer->SetExpChangePer(1);
            pPlayer->SetSkillExpChangePer(1);
        }
        else
        {
            AntiAddictionSystem::sPlayerTimeInGame *pPlayerTimeInGame =NULL;
            pPlayerTimeInGame =	GetPlayerTimenGameById(dwCharDbID);
            if (!pPlayerTimeInGame)
            {
                pPlayer->SetExpChangePer(1);
                pPlayer->SetSkillExpChangePer(1);
            }
            else
            {
                int nExp = 0;
                int nSkillExp = 0;
                DWORD dwTemp = pPlayerTimeInGame->dwTimeInGame/1000;
                /*
                if ( dwTemp >= g_Cfg.m_nFirstPhase)
                {
                nExp = 100 - g_Cfg.m_nFirstPhaseExpSub;
                nSkillExp = 100 - g_Cfg.m_nFirstPhaseSkillExpSub;
                if (dwTemp >= g_Cfg.m_nSecondPhase)
                {
                nExp = 100 - g_Cfg.m_nSecondPhaseExpSub;
                nSkillExp = 100 - g_Cfg.m_nSecondPhaseSkillExpSub;
                if (dwTemp >= g_Cfg.m_nThirdPhase)
                {
                nExp = 100 - g_Cfg.m_nThirdPhaseExpSub;
                nSkillExp = 100 - g_Cfg.m_nThirdPhaseSkillExpSub;
                }
                }

                pChar->SetExpChangePer((float)nExp/100);
                pChar->SetSkillExpChangePer((float)nSkillExp/100);			
                }*/	
            }
        }
    }
}

void AntiAddictionSystem::ApplyPlayerOnlineTime(BaseCharacter* pChar)
{
    if ( NULL == pChar && !pChar->IsPlayer())
    { return; }

    GamePlayer* pGamePlayer = (GamePlayer*)pChar;

    sPlayerOnlineTime* pOnlineTime = GetPlayerOnlineTimeById(pGamePlayer->GetDBCharacterID());
    if (pOnlineTime)
    {
        pOnlineTime->dwTimeInGame += pGamePlayer->GetOnLineTime();
    }
    else
    {
        sPlayerOnlineTime playeronlinetime;
        playeronlinetime.dwCharDbID = pGamePlayer->GetDBCharacterID();
        playeronlinetime.dwTimeInGame = pGamePlayer->GetOnLineTime();
        m_vecPlayerOnlineTime.push_back(playeronlinetime);
    }

    SYSTEMTIME systime;
    ::GetLocalTime( &systime );
    if ( systime.wHour == g_Cfg.m_nRefreshHour && systime.wMinute == g_Cfg.m_nRefreshMin)
    {
        m_vecPlayerOnlineTime.clear();
        // pGamePlayer->ClearPlayerVar();
    }
}
