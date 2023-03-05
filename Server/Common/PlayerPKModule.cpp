#include "GamePlayer.h"
#include "MapConfig.h"
#include "DuelHandler.h"
#include "TeamManager.h"
#include "ShareData.h"
#include "GameTime.h"
#include "GameWorld.h"
#include "PKConfig.h"
#include "SevenDays.h"
#include "XmlStringLanguage.h"
#include "GlobalDBManager.h"

void GamePlayer::SetPKValue( int nValue, char chOp /* = Op_Add */, unsigned char chSendMessage /* = 1 */ )
{
    if ( chOp == PKValueOp_Set )
    {
        m_nPKValue = nValue;
        if ( m_nPKValue > /*MaxPKValue*/thePKConfig.GetMaxPKValue() )
        { 
            m_nPKValue = /*MaxPKValue*/thePKConfig.GetMaxPKValue();
        }
        if ( m_nPKValue < /*MinPKValue*/ thePKConfig.GetMinPKValue())
        {
            m_nPKValue = /*MinPKValue*/thePKConfig.GetMinPKValue();
        }
    }
    else if ( chOp == PKValueOp_Add && nValue > 0 )
    {
        int nTempPkValue = m_nPKValue;
        m_nPKValue += nValue;
        if ( m_nPKValue > /*MaxPKValue*/thePKConfig.GetMaxPKValue() )
        { 
            m_nPKValue = /*MaxPKValue*/thePKConfig.GetMaxPKValue();
        }
        else if ( nTempPkValue < 0 )        
        {
            if ( m_nPKValue > 0 )       // ʹ�õ���ϴ��ʱ, ֻ��ϴ������
            {
                m_nPKValue = 0;         
            }
        }
    }
    else if ( chOp == PKValueOp_Reduce && nValue > 0 )
    {
        int nTempPkValue = m_nPKValue;
        m_nPKValue -= nValue;
        if ( m_nPKValue < /*MinPKValue*/thePKConfig.GetMinPKValue() )
        {
            m_nPKValue = /*MinPKValue*/thePKConfig.GetMinPKValue();
        }
        else if ( nTempPkValue > 0 )
        {
            if ( m_nPKValue < 0 )
            {
                m_nPKValue = 0;
            }
        }
    }
    else
    {
        return; 
    }

    if ( chSendMessage == BV_SendMessage )
    {
        TellClientPKValue();
    }
}

bool GamePlayer::GMSetPKMode( uint8 nMode )
{
    if ( nMode >= PKMode_MaxValue )
    { return false; }
		
    this->m_nPKMode = nMode;

    //�����ģʽ����
    if ( GetPKMode() == PKMode_Critical)
    { EnterCriticalMode(); }

    m_gtUpdatePKModeTimer.StopTimer();

    TellClientPKValue();
    return true;
}
bool GamePlayer::SetPKMode( uint8 nMode, uint8 chSendMessage )
{
    if ( nMode >= PKMode_MaxValue )
    { return false; }

    if ( GetPKMode() == nMode )
    { return false; }

    if ( GetLevel() < g_Cfg.m_nPKProtectLevel )
    {
        if ( chSendMessage == BV_SendMessage )
        {
            MsgAckResult xResult;     
            xResult.result = ER_InProtectLevel;
            xResult.value = g_Cfg.m_nPKProtectLevel;
            GettheServer().SendMsgToSingle( &xResult, this );
            return false;
        } 
    }

    if ( nMode != PKMode_Critical )
    {
        switch(m_nPKMode)
        {
        case PKMode_Normal:
			{
				if (nMode != PKMode_AttackFight && nMode != PKMode_AttackGuild && m_gtUpdatePKModeTimer.IsStart() )
                {
                    if ( chSendMessage == BV_SendMessage )
                    {
                        MsgAckResult xResult;     
                        xResult.result = ER_ChangePKModeOften;
                        xResult.value = m_nPKValue;
                        GettheServer().SendMsgToSingle( &xResult, this );
                    }
                    return false;
                }
			}
			break;
		case PKMode_Guild:
			{
				if( nMode == PKMode_Normal && m_gtUpdatePKModeTimer.IsStart())
				{
					if ( chSendMessage == BV_SendMessage )
                    {
                        MsgAckResult xResult;     
                        xResult.result = ER_ChangePKModeOften;
                        xResult.value = m_nPKValue;
                        GettheServer().SendMsgToSingle( &xResult, this );
                    }
                    return false;
				}
				else if(nMode ==PKMode_AttackFight)
					return false;
			}
			break;
		case PKMode_Fight:
			{ 
				if( nMode == PKMode_Normal && m_gtUpdatePKModeTimer.IsStart())
				{
					if ( chSendMessage == BV_SendMessage )
                    {
                        MsgAckResult xResult;     
                        xResult.result = ER_ChangePKModeOften;
                        xResult.value = m_nPKValue;
                        GettheServer().SendMsgToSingle( &xResult, this );
                    }
                    return false;
				}
				else if(nMode == PKMode_AttackGuild)
					return false;
			}
			break;
        case PKMode_Critical:
            {// ��� PKֵ���� 1 ���ܸı��ģʽ
				if ( m_nPKValue >= /*0*/ thePKConfig.GetEnterCriticalPK() )
                {
                    if ( chSendMessage == BV_SendMessage )
                    {
                        MsgAckResult xResult;     
                        xResult.result = ER_CannotChangePKMode;
                        xResult.value = m_nPKValue;
                        GettheServer().SendMsgToSingle( &xResult, this );
                    }
                    return false;
                }
				if(nMode == PKMode_AttackFight || nMode == PKMode_AttackGuild)
					return false;
                // 30����ʱ�仹δ��
                if ( m_gtUpdateCriticalModeTimer.IsStart() )
                {
                    if ( chSendMessage == BV_SendMessage )
                    {
                        MsgAckResult xResult;     
                        xResult.result = ER_PKModeCriticalNoTimer;
                        xResult.value = m_nPKValue;
                        GettheServer().SendMsgToSingle( &xResult, this );
                    }
                    return false;
                }
            }
            break;
		case PKMode_AttackFight:
		case PKMode_AttackGuild:
			{
				//����ģʽ �ж���ʱ�䵽���л� ���� �ͻ����ֶ��л��� 		
				if (!m_IsUpdateLevelPKAttMode && chSendMessage == BV_SendMessage )
                {
                    MsgAckResult xResult;     
                    xResult.result = ER_ChangePKModeAttact;
                    xResult.value = m_nPKValue;
                    GettheServer().SendMsgToSingle( &xResult, this );
					return false;//�ڷ���ģʽ�ǲ������ֶ��л���
                }
			}
			break;
        }
    }

    //����PKģʽ
	if((m_nPKMode == PKMode_Normal && (nMode == PKMode_Guild || nMode == PKMode_Fight)) ||
	(nMode == PKMode_Normal && (m_nPKMode == PKMode_Guild || nMode == PKMode_Fight)))
		 m_gtUpdatePKModeTimer.StartTimer( HQ_TimeGetTime(), PKModeChangeDelayed );

	if((m_nPKMode == PKMode_AttackFight || m_nPKMode== PKMode_AttackFight) && m_AttertUpdateTime.IsStart())
		m_AttertUpdateTime.StopTimer(); 
    this->m_nPKMode = nMode;

    //�����ģʽ����
    if ( GetPKMode() == PKMode_Critical)
    { EnterCriticalMode(); }

    if ( chSendMessage == BV_SendMessage )
    {
        TellClientPKValue();
    }

    return true;
}
bool GamePlayer::CheckCanAttackPlayer( GamePlayer* pTarget )
{
    if ( this == NULL || pTarget == NULL || this == pTarget )
    { return false; }

    if( theDuelHandler()->IsDuelFight( GetID(), pTarget->GetID() ) )
    { return true; }    //������ң�����Ǿ������ߴ���PK���򣬿��Թ���

    if ( GetLevel() < g_Cfg.m_nPKProtectLevel || pTarget->GetLevel() < g_Cfg.m_nPKProtectLevel )
    { return false; }   // С��PK�����ȼ�

    if ( IsOpenStall() || pTarget->IsOpenStall() )
    { return false; }   // ��̯���޷�����

    if ( pTarget->GetProtectTime() > 0 )
    { return false; }   // �ж϶Է��Ƿ��ڱ���ʱ����

    if ( pTarget->_buffManager.IsInvincible() )
    { return false; }   // �޵�״̬���ܹ���

    if ( GetMapID() != pTarget->GetMapID() )
    { return false; }   // ����ͬһ��ͼ

	//ͬһ�����޷�PK
	GameTeam * pTeam = theGameTeamManager.GetTeam(pTarget->GetTeamID());
	if(pTeam && GetTeamID() == pTarget->GetTeamID())
	{
		return false;
	}

    //�ж��Ƿ���pk��ͼ
    MapConfig::MapData* pTargetMapData = pTarget->GetMapData();
    if ( pTargetMapData == NULL )
    { return false; }

    // ��Ϸû�п�PKģʽ
    if( !g_Cfg.bPKOpen /*|| IsInPKDisableZone() || pTarget->IsInPKDisableZone() */)
    { return false; }    

    //��ͼPKģʽ
    int nMapPKMode  = pTargetMapData->CanPk ;
    //�Լ���PKģʽ

	// �����Ǽ�鵱ǰ��ͼ�ܷ�PK, ��ȷ��ˢ������(�����ǰZone��PKģʽ����Ч��)
    GameStage *pStage = theGameWorld.GetStageById( pTarget->GetMapID() );
    if ( pStage == NULL )
    { return false; }

    GameZone *pZone =  pStage->GetZone( pTarget->GetCurZoneID() );
	if ( pZone != NULL && pZone->GetZonePKMode() != MapConfig::MapData::EPKM_None_PK )
    {
		// ����PKģʽ���ڵ�ͼPKģʽ
		nMapPKMode = pZone->GetZonePKMode();
	}
	//�¼Ӿ���PKģʽ ��Ҫ����ж�
	//if(IsInOneGuild(pTarget) && GetPKMode() == PKMode_Guild) //����Ҵ��ھ���ģʽ �Һ�Ŀ��ͬһ����
    switch ( nMapPKMode )
    {
    case MapConfig::MapData::EPKM_UnAllow_PK:
        { return false; }
        break;
    case MapConfig::MapData::EPKM_Critical_PK:
        {
            // �ж� �Լ� �� �������ߵĶ��� ( ��ͱ�������  ͬ���һ�����ܴ� )
            if ( GetTeamID() != TeamDefine::NoneSessionID && pTarget->GetTeamID() != TeamDefine::NoneSessionID )
            {
                if ( GetTeamID() == pTarget->GetTeamID() )
                { return false; }
            }

            if ( GetPKMode() != PKMode_Critical )
            { return false; }
        }
        break;
    case MapConfig::MapData::EPKM_Allow_PK:
        {
            // �ж� �Լ� �� �������ߵĶ��� ( ��ͱ�������  ͬ���һ�����ܴ� )
            if ( GetTeamID() != TeamDefine::NoneSessionID && pTarget->GetTeamID() != TeamDefine::NoneSessionID )
            {
                if ( GetTeamID() == pTarget->GetTeamID() )
                { return false; }
            }

            // �ж��Լ���ģʽ
            switch ( GetPKMode() )   
            {
            case PKMode_Normal:     // ��ͨģʽ���������ģʽ��ҿ��Խ��й���
                {
                    if (pTarget->GetPKMode() != PKMode_Critical)
                    { return false; }
                }
                break;
			case PKMode_Guild:
				{
					if(IsInOneGuild(pTarget))
						return false;
				}
				break;
            case PKMode_Fight:      // ���ڿ���PKģʽ����ҺͿ�״̬����Ҷ����Խ��й���
                {
                     /*if (pTarget->GetPKMode() == PKMode_Normal)
                    { return false; }*/
					return true;
                }
                break;
			case PKMode_AttackFight:
				{
					return true;
				}
				break;
			case PKMode_AttackGuild:
				{
					if(IsInOneGuild(pTarget))
						return false;
				}
				break;
            case PKMode_Critical:   // ��ģʽ
                { return true; }
                break;
            }
        }
        break;
    case MapConfig::MapData::EPKM_Normal_PK:
        {
            // �ж� �Լ� �� �������ߵĶ��� ( ��ͱ�������  ͬ���һ�����ܴ� )
            if ( GetTeamID() != TeamDefine::NoneSessionID && pTarget->GetTeamID() != TeamDefine::NoneSessionID )
            {
                if ( GetTeamID() == pTarget->GetTeamID() )
                { return false; }
            }

            if ( GetCountry() != pTarget->GetCountry() )
            { return true; }    // ����ͬһ���ҵĿ��Թ���

            // �ж��Լ���ģʽ
            switch ( GetPKMode() )   
            {
            case PKMode_Normal:     // ��ͨģʽ���������ģʽ��ҿ��Խ��й���
                {
                    if (pTarget->GetPKMode() != PKMode_Critical)
                    { return false; }
                }
                break;
			case PKMode_Guild:
				{
					if(IsInOneGuild(pTarget))
						return false;
				}
				break;
            case PKMode_Fight:      // ���ڿ���PKģʽ����ҺͿ�״̬����Ҷ����Խ��й���
                {
                   /* if (pTarget->GetPKMode() == PKMode_Normal)
                    { return false; }*/
					return true;
                }
                break;
			case PKMode_AttackFight:
				{
					return true;
				}
				break;
			case PKMode_AttackGuild:
				{
					if(IsInOneGuild(pTarget))
						return false;
				}
				break;
            case PKMode_Critical:   // ��ģʽ
                { return true; }
                break;
            }
        }
        break;
    case MapConfig::MapData::EPKM_Group_PK:         // ��Ӫս��
        { return GetFightCamp() != pTarget->GetFightCamp() ; }
        break;
    case MapConfig::MapData::EPKM_Guild_PK:         // ����ս��
        {	
            if ( GetGuildID() == GuildDefine::InitID || pTarget->GetGuildID() == GuildDefine::InitID )
            { return false; }

            return GetGuildID() != pTarget->GetGuildID();
        }
        break;
	case MapConfig::MapData::EPKM_WorldBattle_PK:
		{
			//Ұ�����ս������ģʽ
			uint32 CountryID = theGameGlobalDBManager.GetMapCountryID();
			if(CountryID == CountryDefine::Country_Init)
			{
				//���й��Ҷ����Ѻõ�
				return false;
			}
			else
			{
				if(GetCountryId() == CountryID)
				{
					if(pTarget->GetCountryId() != CountryID)
						return true;
					else
						return false;
				}
				else
				{
					if(pTarget->GetCountryId() == CountryID)
						return true;
					else
						return false;
				}
			}
		}
		break;
    case MapConfig::MapData::EPKM_Free_PK:
        { return true; }
        break;
    case MapConfig::MapData::EPKM_Team_PK:          // ����ս��
        { return GetTeamID() != pTarget->GetTeamID(); }
        break;
    case MapConfig::MapData::EPKM_Challenge_PK:     // ������̨
        { return true; }
        break;
    case MapConfig::MapData::EPKM_Contend_PK:
        {
            // �ж� �Լ� �� �������ߵĶ��� ( ��ͱ�������  ͬ���һ�����ܴ� )
            if ( GetTeamID() != TeamDefine::NoneSessionID && pTarget->GetTeamID() != TeamDefine::NoneSessionID )
            {
                if ( GetTeamID() == pTarget->GetTeamID() )
                { return false; }
            }
        }
        break;
    }

    return true;
}


void GamePlayer::AttackChar( BaseCharacter* pChar )
{
    if( pChar == NULL || pChar->GetID() == GetID() )
        return;

    if( pChar->IsPlayer() )
    {
        AttackPlayer( (GamePlayer*)pChar );
    }
    else if( pChar->IsMonster() )
    {
        MonsterBaseEx* pAIChar = static_cast< MonsterBaseEx*>( pChar );
        GamePlayer* pMaster = pAIChar->GetMasterPlayer();
        if ( pMaster != NULL )
        { AttackPlayer( pMaster, true ); }
    }
}
void GamePlayer::AttactOrAssistChar(BaseCharacter* pChar)
{
	if( pChar == NULL || pChar->GetID() == GetID() )
        return;
    if( pChar->IsPlayer() )
    {
        OnAttactOrAssistPlayer( (GamePlayer*)pChar);
    }
    else if( pChar->IsMonster() )
    {
        MonsterBaseEx* pAIChar = static_cast< MonsterBaseEx*>( pChar );
        GamePlayer* pMaster = pAIChar->GetMasterPlayer();
        if ( pMaster != NULL )
        { OnAttactOrAssistPlayer( pMaster);}
    }
}
void GamePlayer::AttackPlayer ( GamePlayer* pTarget, bool bSummonPet /*= false */)
{
    //if ( !IsCanAttackPlayer(pTarget) )
    //{ return; }
	//����Ҷ�ָ����ҷ���������ʱ��
	//OnAttactOrAssistPlayer(pTarget);
}

void GamePlayer::KillChar( BaseCharacter* pChar )
{
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar ); 
    KillPlayer( pPlayer );
}

void GamePlayer::KillPlayer( GamePlayer* pTarget ) 
{
    if ( this == NULL || pTarget == NULL )
    { return; }

	//theGameWantedManager.OnPlayerDead(pTarget->GetDBCharacterID(),GetDBCharacterID());

    if (GetCountry() != pTarget->GetCountry())
    {// ��ͬ���ҵ�����������ֵ
		//�ж��Ƿ���ս������
		pTarget->OnPkDead();
		gCharInfoServer.otherdata.AddKIllPlayer(pTarget->GetDBCharacterID());
		if(!IsInBattleMap())
		{
			bool IsGetHonour = (!GetBuffManager() || GetBuffManager()->GetIsCanGetHonour()) && (!pTarget->GetBuffManager() || pTarget->GetBuffManager()->GetIsCanBeGetHonour());
			if(/*m_KillPlayerMap.OnKillPlayer(this,pTarget) &&*/ IsGetHonour && gCharInfoServer.otherdata.GetKillSum(pTarget->GetDBCharacterID()) <= g_Cfg.OncePlayerKillSum )
			{
				_ProcessHonour ( pTarget );	
			}

			//���������ʹ���� �ж�ʹ����ÿ����������
			uint16 KillSum = gCharInfoServer.otherdata.GetAllKillSum();
			if(KillSum * g_Cfg.KillPlayerMission < g_Cfg.MaxMissionSum)	
			{
				OperateGuildMission( GuildDefine::OperateAdd,min(g_Cfg.KillPlayerMission,g_Cfg.MaxMissionSum - KillSum * g_Cfg.KillPlayerMission));
			}
		}
		
		OnAddKillPlayerSum(pTarget);//����ɱ����

		TriggerSpecialQuest(ESTT_KillPlayer);
		switch (pTarget->GetCountry())
		{
		case CountryDefine::Country_LouLan:
			TriggerSpecialQuest(ESTT_KillWei);
			break;
		case CountryDefine::Country_KunLun:
			TriggerSpecialQuest(ESTT_KillShu);
			break;
		case CountryDefine::Country_DunHuang:
			TriggerSpecialQuest(ESTT_KillWu);
			break;
		}
		//���ɱ���ж���Ӫ����� ���ǵ��ýű�����
		GetScriptMgr()->StartupVM( ST_CHAR_KILLCHAR, 0, this );//ɱ���ж���Ӫ�����

    }
    else
    {// ͬһ�����ҵ���ˢ��PKֵ
        _ProcessPKValue( pTarget );
    }
}

void GamePlayer::_ProcessHonour ( GamePlayer* pTarget )
{
    if ( this == NULL || pTarget == NULL )
    { return; }

    if (GetCountry() == pTarget->GetCountry())
    { return; }

    MapConfig::MapData* pMapData = GetMapData();
    if ( pMapData == NULL )
    { return; }

    if ( RecordTime::CheckRecordTime( GetHonourRecordTime() ) )
    {
        ClearHonourRecord();
        RecordTime::SaveRecordTime( gCharInfoServer.otherdata.nRecordHonourTime );
    }

    if (GetHonourRecord() > GetHonourTopLimit())
    {
        MsgAckResult msg;
        msg.result = ER_HonourTopLimit;
        GettheServer().SendMsgToSingle(&msg, this);
        return;
    }

    int16 nHonour = 0;
	if(GetLevel() - pTarget->GetLevel() >= g_Cfg.LevelLimit)
	{
		nHonour = 0;
	}
	else if (pMapData->CountryID == GetCountry())
    { 
		//nHonour = PKHonour_SelfCountry;
		nHonour = g_Cfg.CountryKillPlayerHonour;
	}
	else
	{
		nHonour = g_Cfg.KillPlayerHonour;
	}
    
    /*else
    { nHonour = PKHonour_ForeignCountry; }*/

    // ��ҵ�������
    GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
    if ( pTeam == NULL )
    {
		/*
		 *	Author 2012-11-28 zhuxincong
		 *	DESC: �߻�����
		 ͬ���Լ�10���ȼ�����PK ���15��
		 �����Լ�10�����20��
		 �����Լ�20�����30��
		 �����Լ�10�����5��
		 �����Լ�20��������

		 */
		/*if (GetLevel() >= pTarget->GetLevel())
		{
			if (GetLevel() - pTarget->GetLevel() <= 10)
			{
				//nHonour = PKHoniur15;
				nHonour = PKHoniur6;
			}
			else if (GetLevel() - pTarget->GetLevel() >=20)
			{
				nHonour = 0;
			}
			else if (GetLevel() - pTarget->GetLevel() >= 10)
			{
				nHonour = PKHoniur6;
			}
		}
		else
		{
			if (abs(GetLevel() - pTarget->GetLevel()) <= 10)
			{
				//nHonour = PKHoniur15;
				nHonour = PKHoniur6;
			}
			else if (abs(GetLevel() - pTarget->GetLevel()) >=20)
			{
				//nHonour = PKHonour_ForeignCountry;
				nHonour = PKHoniur6;
			}
			else if (abs(GetLevel() - pTarget->GetLevel()) >= 10)
			{
				//nHonour = PKHoniur20;
				nHonour = PKHoniur6;
			}
		}*/
		/*if(!pTarget->IsInNormalMap())
			nHonour = PKHoniur6;
		else if(GetLevel() - pTarget->GetLevel() >= 20)
			nHonour = 0;
		else
			nHonour = PKHoniur6;*/
		
        //if (GetLevel() - pTarget->GetLevel() < 20)
        //{
        OperateHonour( EOT_Add, nHonour, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_KillPerson);
        //}
		//����7����
		//_sevenDayManager.TriggerSevenDaysVar( (int)SevenDaysConfig::TD_ThirdDay, nHonour );
    }
    else
    {
        //�����Ч��Ա����
        unsigned int nAreaCount = pTeam->GetTeamMemberCountInMap( pTarget->GetMapID(), pTarget->GetFloatX(), pTarget->GetFloatY() );
        if ( nAreaCount == 0 ) 
        { nAreaCount = 1;}

        for( int i = 0; i < pTeam->TeamMemberCount(); ++i )
        {
            GamePlayer* pPlayer = pTeam->GetMemberPlayer( pTeam->GetMemberIDByIndex( i ) );
            if ( pPlayer == NULL || pPlayer->IsDead() ) 
            { continue; }

            if( !pPlayer->IsPlayer() || !pPlayer->IsInMapArea(pTarget->GetMapID(), pTarget->GetFloatX(), pTarget->GetFloatY(),g_Cfg.TeamHonourDis /*TEAM_EXP_DIS*/) )
            { continue; }

			/*if (pPlayer->GetLevel() >= pTarget->GetLevel())
			{
				if (pPlayer->GetLevel() - pTarget->GetLevel() <= 10)
				{
					nHonour = PKHoniur6;
					//nHonour = PKHoniur15;
				}
				else if (pPlayer->GetLevel() - pTarget->GetLevel() >=20)
				{
					nHonour = 0;
				}
				else if (pPlayer->GetLevel() - pTarget->GetLevel() >= 10)
				{
					nHonour = PKHoniur6;
				}
			}
			else
			{
				if (abs(pPlayer->GetLevel() - pTarget->GetLevel()) <= 10)
				{
					nHonour = PKHoniur6;
					//nHonour = PKHoniur15;
				}
				else if (abs(pPlayer->GetLevel() - pTarget->GetLevel()) >=20)
				{
					nHonour = PKHoniur6;
					//nHonour = PKHonour_ForeignCountry;
				}
				else if (abs(pPlayer->GetLevel() - pTarget->GetLevel()) >= 10)
				{
					nHonour = PKHoniur6;
					//nHonour = PKHoniur20;
				}
			}*/
			/*if(!pTarget->IsInNormalMap())
				nHonour = PKHoniur6;
			else if(GetLevel() - pTarget->GetLevel() >= 20)
				nHonour = 0;
			else
				nHonour = PKHoniur6;*/
			int16 nAvgHonour = nHonour;
			if(pPlayer == this)
				nAvgHonour = nHonour - g_Cfg.TeamDelHonour;
			else
				nAvgHonour = g_Cfg.TeamOtherPlayerHonour;			
			pPlayer->OperateHonour( EOT_Add, nAvgHonour, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_KillPerson);

			//����7����
			//pPlayer->_sevenDayManager.TriggerSevenDaysVar( (int)SevenDaysConfig::TD_ThirdDay, nAvgHonour );

            /*if (pPlayer->GetLevel() - pTarget->GetLevel() < 20 )
            {
                pPlayer->OperateHonour( EOT_Add, nAvgHonour, __FUNCTION__, __LINE__ );
            }*/
        }
    }

}

void GamePlayer::_ProcessPKValue( GamePlayer* pTarget )
{
    if ( this == NULL || pTarget == NULL )
    { return; }

    if (GetCountry() != pTarget->GetCountry())
    { return; }

    // �����д�
    if( theDuelHandler()->IsDuelFight( GetID(), pTarget->GetID() ) )
    { return; }

    // �ж��Ƿ���pk��ͼ
    MapConfig::MapData* pTargetMapData = GetMapData();
    if ( pTargetMapData == NULL )
    { return; }

    switch ( pTargetMapData->CanPk )
    {
    case MapConfig::MapData::EPKM_UnAllow_PK:
    case MapConfig::MapData::EPKM_Critical_PK:
    case MapConfig::MapData::EPKM_Allow_PK:
    case MapConfig::MapData::EPKM_Normal_PK:
        {
            if ( pTarget->GetProtectTime() > 0 )
            { return; }     // ����ʱ���ڲ�����PKֵ

            if ( pTarget->GetPKMode() == PKMode_Critical || pTarget->GetPKValue() >= thePKConfig.GetEnterCriticalPK()/*0*/ )
            { return; }     // �κ����ɱ����ģʽ��Ҷ����ı�PKֵ 

            //ͬ��PKģʽ���ı�PKֵ
            if (/* (GetPKMode() == PKMode_Fight || GetPKMode() == PKMode_Guild ) && */(pTarget->GetPKMode() == PKMode_Fight || pTarget->GetPKMode() == PKMode_Guild))
            { return; } 
	
			if(pTarget->GetPKMode() == PKMode_AttackFight || pTarget->GetPKMode() == PKMode_AttackGuild)//����ģʽ�±�ɱ������PKֵ
				return;
			//ӵ������Ȩ�������ɱ�˲���Pkֵ
			GameCountry * pCountry = theGameCountryManager.GetCountry(GetCountryId());
			if(pCountry && pCountry->IsHaveRight(CountryDefine::Right_PK,GetDBCharacterID()))
				return;
            //��PKֵ
            SetPKValue( /*PKKillValue*/thePKConfig.GetPKKillValue(), PKValueOp_Add, BV_SendMessage );
            ProcessPKPunish();
        }
        break;
    default:
        break;
    }
}

bool GamePlayer::IsEffectKill( unsigned int dwPlayerDBID )
{
    if ( dwPlayerDBID == InvalidLogicNumber )
    { return false; }

    return true;
}

void GamePlayer::EnterCriticalMode()
{
    m_gtUpdateCriticalModeTimer.StartTimer( HQ_TimeGetTime(), PKCriticalTime );
}

void GamePlayer::TellClientPKValue( bool bSendToView /* = true */ )
{      
    if ( this == NULL )
    { return; }

    MsgPKStateChange change;
    change.shCharID       = GetID();
    change.nPKMode        = GetPKMode();
    change.nPKValue       = GetPKValue();

    if ( bSendToView )
    {
        GettheServer().SendMsgToView( &change, GetID(), false );
    }
    else
    {
        GettheServer().SendMsgToSingle( &change, this );
    }
}

void GamePlayer::PKProcessRun( unsigned int dwCostTime )
{
    //����PKֵ
	if ( GetPKValue() >= 0 /*thePKConfig.GetEnterCriticalPK()*/)
    {
        if ( GetPKMode() != PKMode_Critical  && GetPKValue() >= thePKConfig.GetEnterCriticalPK())
        {
            SetPKMode( PKMode_Critical );
        }
		if(!m_gtUpdatePKValueTimer.IsStart() && gTransferRuntimeInfo.PkValueTimeLog == 0)
			gTransferRuntimeInfo.PkValueTimeLog = HQ_TimeGetTime();
		m_gtUpdatePKValueTimer.StartTimer(gTransferRuntimeInfo.PkValueTimeLog, /*PKValueUpdateTime*/thePKConfig.GetPKValueUpdateTime() );
        if ( m_gtUpdatePKValueTimer.DoneTimer() )
        {
            SetPKValue( 1, PKValueOp_Reduce );
			if ( GetPKValue() >=0/* thePKConfig.GetEnterCriticalPK()*//*0*/ )
			{
				gTransferRuntimeInfo.PkValueTimeLog = HQ_TimeGetTime();
				m_gtUpdatePKValueTimer.StartTimer(gTransferRuntimeInfo.PkValueTimeLog, /*PKValueUpdateTime*/thePKConfig.GetPKValueUpdateTime() );
			}
			else
				gTransferRuntimeInfo.PkValueTimeLog = 0;
        }
    }

    //���¿�״̬
    if ( GetPKMode() == PKMode_Critical )
    {
        if ( m_gtUpdateCriticalModeTimer.DoneTimer() )
        {
            if ( GetPKValue() < /*0*/ thePKConfig.GetEnterCriticalPK())
            { SetPKMode( PKMode_Normal ); }
        }
    }

    m_gtUpdatePKModeTimer.DoneTimer();

    if ( GetPKValue() < 0 )
    { SetPKValue( 0 , PKValueOp_Set ); }

	m_KillPlayerMap.Update();//������ҵ�ɱ���б��¼
	OnUpdateClearKillPlayerWeekSum();//����ÿ��ɱ������
	OnPlayerLeaveAttack();
	OnLevelAttackMode();//�뿪����ģʽ
}

void GamePlayer::ProcessPKPunish()
{
	//����ҵ�PKֵ�������õĽ��������PKֵ��ʱ�� ��������ҽ������ 
	//��PKֵ���ڽ��������ֵ��ʱ�� ���û�������ʾ��ɫ������

	if(GetMapData() &&  GetMapData()->IsEctypeMap())
		return;
    if ( GetPKValue() < /*PKHellPunishValue*/thePKConfig.GetEnterJianYu() )
    { return; }

    const CountryConfig::SpecialMapSetting* pPrisonMap = theCountryConfig.GetPrisonMapSetting( GetCountry() );
    if( pPrisonMap == NULL )
    { return; }

    // 3��ŷ���
    SetWaitChangeStage( GamePlayer::LeaveStage, pPrisonMap->GetMapID(), pPrisonMap->GetPosX(), pPrisonMap->GetPosY(), pPrisonMap->GetDir(),3, false );

	//���͹���
	char Info[256];
	sprintf_s(Info,127,theXmlString.GetString(thePKConfig.GetCommonID()),GetCharInfo().baseinfo.aptotic.szCharacterName);
	//������ַ������͵�ȫ������
	MsgChat xChat( MsgChat::CHAT_TYPE_BULL );
	xChat.SetString( Info );
	GettheServer().SendMsgToWorld( &xChat, true );  
}

int GamePlayer::GetHonourTopLimit()
{
	return g_Cfg.MaxHonour;
    //return 0;// GetLevel() * 10 + _buffManager.GetAddHonourLimit();
}
bool GamePlayer::IsInOneGuild(GamePlayer* pTarget)
{
	if(!pTarget) return false;
	if ( GetGuildID() == GuildDefine::InitID || pTarget->GetGuildID() == GuildDefine::InitID )
		return false;
    return GetGuildID() == pTarget->GetGuildID();
}
void GamePlayer::OnAddKillPlayerSum(GamePlayer* pTarget)
{
	if(!pTarget) return;
	if(GetCountryId() == pTarget->GetCountryId()) return;//ͬһ���Ҳ�����
	//�жϵ�ͼ ֻ��Ұ��ż���
	if(!pTarget->IsInNormalMap())
		return;
	++gCharInfoServer.baseinfo.liveinfo.dwKillPlayerSum;//��ɱ����
	++gCharInfoServer.baseinfo.liveinfo.dwKillPlayerWeekSum;//������ɱ����
	//RecordTime::SaveRecordTime( gCharInfoServer.otherdata.nRecordKillPlayerTime );//���ú����ɱ�˵�ʱ��
	time_t now;
	time(&now);
	
	gCharInfoServer.otherdata.nRecordKillPlayerTime = now;

	
	MsgKillPlayerNumAck msg;
	msg.nAllKillNum = gCharInfoServer.baseinfo.liveinfo.dwKillPlayerSum;
	msg.nWeekKillNum = gCharInfoServer.baseinfo.liveinfo.dwKillPlayerWeekSum;
	//�����������ҿͻ���
	SendMessageToClient(&msg);
	//����ɱ�����ﵽ
	if(gCharInfoServer.baseinfo.liveinfo.dwKillPlayerSum >=	10000)
	{
		//�ɾ� ���Ī��
	}	
	else if(gCharInfoServer.baseinfo.liveinfo.dwKillPlayerSum >= 1000)
	{
		//�ɾ� һ�ﵱǧ
	}
	else if(gCharInfoServer.baseinfo.liveinfo.dwKillPlayerSum >= 100)
	{
		//�ɾ� ����ն
	}
}
void GamePlayer::OnUpdateClearKillPlayerWeekSum()
{
	//�жϵ�ǰʱ��Ϊ��6 0�� ����� ����ɱ����
	time_t now;		
	struct tm *fmt;	
	time(&now);	
	fmt = localtime(&now);	
	if(fmt->tm_wday== 0 && fmt->tm_hour == 0 && fmt->tm_min == 0 && fmt->tm_sec ==0)
	{
		gCharInfoServer.baseinfo.liveinfo.dwKillPlayerWeekSum = 0;
		//��������
		MsgKillPlayerNumAck msg;
		msg.nAllKillNum = gCharInfoServer.baseinfo.liveinfo.dwKillPlayerSum;
		msg.nWeekKillNum = 0;
		SendMessageToClient(&msg);
	}
}
void GamePlayer::OnCheckKillPlayerSum()
{
	//�������ϴ����ߵ�ʱ�� 
	//��ȡ�ϴμ���ʱ��
	time_t logtime =gCharInfoServer.otherdata.nRecordKillPlayerTime;//��ȡ������ɱ�˵�ʱ��
	//�жϵ�ǰ
	time_t nowtime;
	time(&nowtime);
	
	double SpanTime = difftime(nowtime,logtime);

	struct tm sysLogTime(*localtime(&logtime));	

	struct tm sysNowTime(*localtime(&nowtime));	

	bool states = false;
	if(7*24*60*60 <= SpanTime)
	{
		//���ʱ�䳬��һ������
		states = true;
	}
	else if(sysLogTime.tm_wday == 0 && sysLogTime.tm_hour == 0 && sysLogTime.tm_min ==0 && sysLogTime.tm_sec ==0)
	{
		states = false;
	}
	else if(sysNowTime.tm_mday == sysLogTime.tm_mday && sysNowTime.tm_mon == sysLogTime.tm_mon && sysNowTime.tm_year == sysLogTime.tm_year)
	{
		//ͬһ��
		states = false;
	}
	else
	{
		//����ͬһ�� �Ҳ��С��һ������
		if(sysNowTime.tm_wday > sysLogTime.tm_wday)
			states = false;
		else
			states = true;
	}
	if(states)
	{
		gCharInfoServer.baseinfo.liveinfo.dwKillPlayerWeekSum = 0;
	}
}
void GamePlayer::OnPkDead()
{
	m_KillPlayerMap.OnDead();
}
bool GamePlayer::IsInNormalMap()
{
	//�ж�ָ������Ƿ�����ͨ��ͼ����
	MapConfig::MapData* pTargetMapData = GetMapData();
	if(!pTargetMapData) return false;
	if(pTargetMapData->IsEctypeMap())
		return false;
	return true;
}
void GamePlayer::OnPlayerLeaveAttack()
{
	//������뿪ս��״̬��ʱ��
	if(!HaveFighteFlag(eFighting) && (GetPKMode() == PKMode_AttackFight || GetPKMode() == PKMode_AttackGuild) && !m_AttertUpdateTime.IsStart())
	{
		//����20��ļ�ʱ�� 20�����������뿪ģʽ
		m_AttertUpdateTime.StartTimer( HQ_TimeGetTime(), MaxLevelAttack );
	}
}
void GamePlayer::OnLevelAttackMode()
{
	//������뿪ģʽ
	if(m_AttertUpdateTime.IsStart() && m_AttertUpdateTime.DoneTimer())
	{
		m_IsUpdateLevelPKAttMode = true;
 		if(GetPKMode() == PKMode_AttackFight )
			SetPKMode(PKMode_Fight,true);
		else if(GetPKMode() == PKMode_AttackGuild)
			SetPKMode(PKMode_Guild,true);	
		m_AttertUpdateTime.StopTimer();
		m_IsUpdateLevelPKAttMode = false;
	}
}
void GamePlayer::OnAttactOrAssistPlayer(GamePlayer* pPlayer)
{
	if(!pPlayer ||  GetPKMode() == PKMode_Critical) return;
	if (GetCountry() != pPlayer->GetCountry()) return;//��ͬ��������ν������ģʽ
	if( theDuelHandler()->IsDuelFight( GetID(), pPlayer->GetID() ) ) // ��ֹ�ھ�������ɱ¾ģʽ lrt
		return;

	if(pPlayer->GetPKMode() == PKMode_AttackFight || pPlayer->GetPKMode() == PKMode_AttackGuild)
	{
		//�κι������߸��� �����ֵ���� ������Ϊ��ɫ
		if(GetPKMode() == PKMode_Fight)
		{
			if(SetPKMode(PKMode_AttackFight,true) && m_AttertUpdateTime.CheckStart())
				m_AttertUpdateTime.StopTimer();
		}
		else if(GetPKMode() == PKMode_Guild)
		{
			if(SetPKMode(PKMode_AttackGuild,true) && m_AttertUpdateTime.CheckStart())
				m_AttertUpdateTime.StopTimer();
		}
		else if(GetPKMode() == PKMode_AttackGuild || GetPKMode() == PKMode_AttackFight)
		{
			//ˢ�³���ʱ��
			if(m_AttertUpdateTime.CheckStart())
				m_AttertUpdateTime.StopTimer();
		}
		else 
		{
			if(SetPKMode(PKMode_AttackFight,true) && m_AttertUpdateTime.CheckStart())
				m_AttertUpdateTime.StopTimer();
		}
		return;
	}
	else if(CheckCanAttackPlayer(pPlayer))
	{
		//ս���ﲻ����
		//�ж��Ƿ���pk��ͼ
		MapConfig::MapData* pTargetMapData = pPlayer->GetMapData();
		if ( pTargetMapData != NULL )
		{
			int nMapPKMode  = pTargetMapData->CanPk ;
			GameStage *pStage = theGameWorld.GetStageById( pPlayer->GetMapID() );
			if(pStage)
			{
				GameZone *pZone =  pStage->GetZone( pPlayer->GetCurZoneID() );
				if ( pZone != NULL && pZone->GetZonePKMode() != MapConfig::MapData::EPKM_None_PK )
					nMapPKMode = pZone->GetZonePKMode();
			}
			if(MapConfig::MapData::EPKM_Guild_PK == nMapPKMode || nMapPKMode == MapConfig::MapData::EPKM_WorldBattle_PK)
				return;
		}
		//�������Ŀ�� Ŀ��Ϊ��ɫ����
		if(pPlayer->GetPKMode() == PKMode_Normal)
		{
			if(GetPKMode() == PKMode_Fight)
			{
				if(SetPKMode(PKMode_AttackFight,true) && m_AttertUpdateTime.CheckStart())
					m_AttertUpdateTime.StopTimer();
			}
			else if(GetPKMode() == PKMode_Guild)
			{
				if(SetPKMode(PKMode_AttackGuild,true) && m_AttertUpdateTime.CheckStart())
					m_AttertUpdateTime.StopTimer();
			}
			else if(GetPKMode() == PKMode_AttackGuild || GetPKMode() == PKMode_AttackFight)
			{
				//ˢ�³���ʱ��
				if(m_AttertUpdateTime.CheckStart())
					m_AttertUpdateTime.StopTimer();
			}
			else 
			{
				if(SetPKMode(PKMode_AttackFight,true) && m_AttertUpdateTime.CheckStart())
					m_AttertUpdateTime.StopTimer();
			}
			return;
		}
	}
}