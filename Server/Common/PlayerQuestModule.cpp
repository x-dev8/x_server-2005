#include "GamePlayer.h"
#include "QuestManager.h"
#include "XmlStringLanguage.h"
#include "SpecialQuestManager.h"
#include "CountryConfig.h"
#include "LogEventService.h"
#include "SevenDays.h"
#include "HuntingQuestManager.h"

void GamePlayer::GetQuestCharVars( MsgTellCharVar* pMsg )
{       
    for( int i=0; i<More_iMaxVars; ++i )
    {
        short chVar = GetVar( i );
        if( chVar != 0 )
        { 
            if ( !pMsg->AddValue( i, chVar ) )
            { break; }
        }
    }
}

void GamePlayer::GetQuestTimes( MsgTellQuestTime* pMsg )
{
    for( int i=0; i<QuestLimitTimeMaxCount; ++i )
    {
        SQuestTimeRecord& record = gCharInfoServer.otherdata.vars.questTime[i];
        if ( record.id == 0)
        { break; }

        if ( !pMsg->AddValue( record.id, record.time ) )
        { break; }
    }
}

uint8 GamePlayer::GetQuestState( short stQuestId )
{       
    if( !theQuestManager.IsQuestIdValid( stQuestId ) )
    { return 0; }

    return theQuestManager.GetQuestState( GetVar( stQuestId ) );
}
bool GamePlayer::IfCanJoinQuest(unsigned int QuestID)
{
	//�ж�ָ�������Ƿ���Խ�ȡ
	 if( !theQuestManager.IsQuestIdValid( QuestID ) )
    { return false; }
	 SQuest* pQuest = theQuestManager.GetQuest( QuestID );
    if ( pQuest == NULL )
    { return false; }
	uint8 countryID = GetCountryId();
	if (pQuest->Country!=0 && countryID!=pQuest->Country)
	{
		return false;
	}
	if(theQuestManager.GetQuestState( GetVar( QuestID ) ) != QuestManager::eQuestNotGain)
		return false;//ֻ��δ��ȡ������ſ����ٽ�ȡ


	SQuest::RequirementTypeItr itr = pQuest->stReceiveRequirement.begin();
    SQuest::RequirementTypeItr end = pQuest->stReceiveRequirement.end();
    for( ; itr != end; ++itr )
    {
        switch ( itr->byType )
        {
        case SQuest::eRequirement_Money:                    // ���Ǯ�Ƿ��㹻
            {
                if ( GetMoney() < itr->Value )
                {
                    return false;
                }
            }       
            break;
        case SQuest::eRequirement_Item:                     //���õ��ߵĸ����Ƿ���������������
            {
                int nCount = GetItemCount( itr->Value );
                if( nCount < itr->MaxNum )
                {
                    return false;
                }
            }
            break;
        case SQuest::eRequirement_Energy:                   // �жϻ���ֵ
            {
                if ( gCharInfoServer.baseinfo.liveinfo.activity < itr->Value )
                {
                    return false;
                }
            }
            break;
        case SQuest::eRequirement_Level:                    // �жϵȼ�
            {
                if ( GetLevel() < itr->Value )
                {
                    return false;
                }
            }
            break;
        case SQuest::eRequirement_Reputation:               // �ж�����
            {
                if ( GetReputation() < itr->Value )
				{
                    return false;
                }
            }
            break;
        case SQuest::eRequirement_Sex:                      // �ж��Ա�
            {
                if ( itr->Value != Sex_Max && itr->Value != gCharInfoServer.baseinfo.aptotic.ucSex )
                {
                    return false;
                }
            }
            break;
        case SQuest::eRequirement_SocialRelation:
            {
            }
            break;
        case SQuest::eRequirement_Profession:               //��Ҫ���ڶ�������ƣ�1λ��ְҵ�ж�һ���Ƿ�������ְҵ
            {
                if ( ( itr->Value & ( 1 << gCharInfoServer.baseinfo.aptotic.usProfession ) ) == 0 )
                {
                    return false;
                }
            }
            break;
        case SQuest::eRequirement_Var:                      // �жϼ�������
            {
                if ( GetVar( itr->wVar ) < itr->MaxNum )
                {
                    return false;
                }
            }
            break;
        case SQuest::eRequirement_Quest: // ǰ������
            {
                uint8 nState = GetQuestState( itr->Value ); 
				if ( nState != QuestManager::eQuestDone) // ǰ������û�����
                {
                    return false;
                }
            }
            break;
        case SQuest::eRequirement_VarLimit:                 // ��������, �����ü�������, ������ȡ����
            {
                if ( GetVar( itr->wVar ) >= itr->MaxNum )
                { return false; }
            }   
            break;
        case SQuest::eRequirement_WeakCountry: 
            { // ��������
                if ( theGameCountryManager.GetWeakCountry() != GetCountry() )
                { return false; }
				
            }
            break;
        case SQuest::eRequirement_Status:
            {
                if ( !_buffManager.IsHaveStatus( itr->Value ) )
                { return false; }
            }
            break;
        case SQuest::eRequirement_NoStatus:   
            {
                if ( _buffManager.IsHaveStatus( itr->Value ) )
                { return false; }
            }
            break;
        case SQuest::eRequirement_XinFaLevel:   
            {
                if ( itr->Value == 0 )
                {
                    int nMaxLevel = 0;
                    for ( int i=0; i<_XinFaManager.GetXinFaNum(); ++i )
                    {
                        SCharXinFa* pCharXinFa = _XinFaManager.GetXinFaByIndex( i );
                        if ( pCharXinFa != NULL && pCharXinFa->nXinFaLevel > nMaxLevel )
                        { nMaxLevel = pCharXinFa->nXinFaLevel; }
                    }

                    if ( itr->MaxNum > nMaxLevel  )
                    { return false; }
                }
                else
                {
                    SCharXinFa* pCharXinFa = _XinFaManager.GetXinFaByID( itr->Value );
                    if ( pCharXinFa == NULL || itr->MaxNum > pCharXinFa->nXinFaLevel )
                    { return false; }
                }
            }
            break;
        case SQuest::eRequirement_PetNumber:
            {
                if ( itr->Value > _petManager.GetPetNumber()  )
                { return false; }
            }
            break;
        case SQuest::eRequirement_PetLevel:       
            {
                if ( itr->Value > _petManager.GetPetMaxLevel()  )
                { return false; }
            }
            break;
        case SQuest::eRequirement_PetID :     
            {
                if ( !_petManager.IsHavePet( itr->Value ) )
                { return false; }
            }
            break;
        case SQuest::eRequirement_PetType:   
            {
                if ( !_petManager.IsHavePetType( itr->Value ) )
                { return false; }
            }
            break;
        case SQuest::eRequirement_PetActive: 
            {
                if ( _petManager.GetActivePetIndex() == -1 )
                { return false; }
            }
            break;
        default:
            break;
        };
    }

    // �ж���ʱ����������
    SQuest::RequirementTypeItr itrCommit = pQuest->stCommitRequirement.begin();
    SQuest::RequirementTypeItr endCommit = pQuest->stCommitRequirement.end();
    for( ; itrCommit != endCommit; ++itrCommit )
    {
        SQuestRequirement& require = *itrCommit;
        switch ( require.byType )
        {
        case SQuest::eRequirement_Time:
            { // �ж�ʱ��
                if ( !SetQuestTime( QuestID, TimeEx::GetCurrentTime().GetTime() ))
                {
                    return false;
                }
            }
            break;
        default:
            break;
        }
    }
	return true;
}
bool GamePlayer::SetQuestState( short stQuestId, uint8 targetState )
{
    if( !theQuestManager.IsQuestIdValid( stQuestId ) )
    { return false; }

    //char chLastState = GetQuestState( stQuestId );
    //// ���񲻿��ܴ� ���״̬ �� �ѽ�״̬,�м��Ѿ�Ҫ���ɽ�״̬ ���� ���񲻿��ܴ� �ɽ�״̬ �� ���״̬  ( �߻���Ҫ������������,����ע�͵� )
    //if ( ( chLastState == -1 && chState == 1 ) || ( chLastState == 0 && chState == -1 ) )
    //{
    //    LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "����[%d] ��״̬[%d] �� ״̬[%d] ���Ϸ�!", stQuestId, chLastState, chState );
    //    return false; 
    //}   

    SQuest* pQuest = theQuestManager.GetQuest( stQuestId );
    if ( pQuest == NULL )
    { return false; }

	
	/*
	 * Author: 2012-10-8 15:48:11 liaojie
	 * Desc:   ���ӹ����ж�
	 */
	uint8 countryID = GetCountryId();
	if (pQuest->Country!=0 && countryID!=pQuest->Country)
	{
		return false;
	}

    // chState == 1 ������  chState == -1 ������� Ŀ��chState״̬
    // Ŀǰ������������ж϶��ڽű��У�����ֻ�ж�ǰ������
    switch ( targetState )
    {
    case QuestManager::eQuestGaining:
        { // ������
            // �жϽӵ������Ƿ�����
            SQuest::RequirementTypeItr itr = pQuest->stReceiveRequirement.begin();
            SQuest::RequirementTypeItr end = pQuest->stReceiveRequirement.end();
            for( ; itr != end; ++itr )
            {
                switch ( itr->byType )
                {
                case SQuest::eRequirement_Money:                    // ���Ǯ�Ƿ��㹻
                    {
                        if ( GetMoney() < itr->Value )
                        {
                            ShowInfo( false, 261, theXmlString.GetString(eTell_Client_CannotTaskBCMoney) );
                            return false;
                        }
                    }       
                    break;
                case SQuest::eRequirement_Item:                     //���õ��ߵĸ����Ƿ���������������
                    {
                        int nCount = GetItemCount( itr->Value );
                        if( nCount < itr->MaxNum )
                        {
                            ShowInfo( false, 261, theXmlString.GetString(eTell_Client_CannotTaskBCItem) );
                            return false;
                        }
                    }
                    break;
                case SQuest::eRequirement_Energy:                   // �жϻ���ֵ
                    {
                        if ( gCharInfoServer.baseinfo.liveinfo.activity < itr->Value )
                        {
                            ShowInfo( false, 261, theXmlString.GetString(eTell_Client_CannotTaskBCEnergy) );
                            return false;
                        }
                    }
                    break;
                case SQuest::eRequirement_Level:                    // �жϵȼ�
                    {
                        if ( GetLevel() < itr->Value )
                        {
                            ShowInfo( false, 261, theXmlString.GetString(eTell_Client_CannotTaskBCLevel), itr->Value );
                            return false;
                        }
                    }
                    break;
                case SQuest::eRequirement_Reputation:               // �ж�����
                    {
                        if ( GetReputation() < itr->Value )
                        {
                            ShowInfo( false, 261, theXmlString.GetString(eTell_Client_CannotTaskBCReputation) );
                            return false;
                        }
                    }
                    break;
                case SQuest::eRequirement_Sex:                      // �ж��Ա�
                    {
                        if ( itr->Value != Sex_Max && itr->Value != gCharInfoServer.baseinfo.aptotic.ucSex )
                        {
                            ShowInfo( false, 261, theXmlString.GetString(eTell_Client_CannotTaskBCSex) );
                            return false;
                        }
                    }
                    break;
                case SQuest::eRequirement_SocialRelation:
                    {
                    }
                    break;
                case SQuest::eRequirement_Profession:               //��Ҫ���ڶ�������ƣ�1λ��ְҵ�ж�һ���Ƿ�������ְҵ
                    {
                        if ( ( itr->Value & ( 1 << gCharInfoServer.baseinfo.aptotic.usProfession ) ) == 0 )
                        {
                            ShowInfo( false, 261, theXmlString.GetString(eTell_Client_CannotTaskBCProfession) );
                            return false;
                        }
                    }
                    break;
                case SQuest::eRequirement_Var:                      // �жϼ�������
                    {
                        if ( GetVar( itr->wVar ) < itr->MaxNum )
                        {
                            ShowInfo( false, 261, theXmlString.GetString(eTell_Client_CannotTaskBCFrontQuest)  );
                            return false;
                        }
                    }
                    break;
                case SQuest::eRequirement_Quest: // ǰ������
                    {
                        uint8 nState = GetQuestState( itr->Value ); 
                        if ( nState != QuestManager::eQuestDone) // ǰ������û�����
                        {
                            ShowInfo( false, 261, theXmlString.GetString(eTell_Client_CannotTaskBCFrontQuest) );
                            return false;
                        }
                    }
                    break;
                case SQuest::eRequirement_VarLimit:                 // ��������, �����ü�������, ������ȡ����
                    {
                        if ( GetVar( itr->wVar ) >= itr->MaxNum )
                        { return false; }
                    }   
                    break;
                case SQuest::eRequirement_WeakCountry: 
                    { // ��������
                        if ( theGameCountryManager.GetWeakCountry() != GetCountry() )
                        { return false; }
                    }
                    break;
                case SQuest::eRequirement_Status:
                    {
                        if ( !_buffManager.IsHaveStatus( itr->Value ) )
                        { return false; }
                    }
                    break;
                case SQuest::eRequirement_NoStatus:   
                    {
                        if ( _buffManager.IsHaveStatus( itr->Value ) )
                        { return false; }
                    }
                    break;
                case SQuest::eRequirement_XinFaLevel:   
                    {
                        if ( itr->Value == 0 )
                        {
                            int nMaxLevel = 0;
                            for ( int i=0; i<_XinFaManager.GetXinFaNum(); ++i )
                            {
                                SCharXinFa* pCharXinFa = _XinFaManager.GetXinFaByIndex( i );
                                if ( pCharXinFa != NULL && pCharXinFa->nXinFaLevel > nMaxLevel )
                                { nMaxLevel = pCharXinFa->nXinFaLevel; }
                            }

                            if ( itr->MaxNum > nMaxLevel  )
                            { return false; }
                        }
                        else
                        {
                            SCharXinFa* pCharXinFa = _XinFaManager.GetXinFaByID( itr->Value );
                            if ( pCharXinFa == NULL || itr->MaxNum > pCharXinFa->nXinFaLevel )
                            { return false; }
                        }
                    }
                    break;
                case SQuest::eRequirement_PetNumber:
                    {
                        if ( itr->Value > _petManager.GetPetNumber()  )
                        { return false; }
                    }
                    break;
                case SQuest::eRequirement_PetLevel:       
                    {
                        if ( itr->Value > _petManager.GetPetMaxLevel()  )
                        { return false; }
                    }
                    break;
                case SQuest::eRequirement_PetID :     
                    {
                        if ( !_petManager.IsHavePet( itr->Value ) )
                        { return false; }
                    }
                    break;
                case SQuest::eRequirement_PetType:   
                    {
                        if ( !_petManager.IsHavePetType( itr->Value ) )
                        { return false; }
                    }
                    break;
                case SQuest::eRequirement_PetActive: 
                    {
                        if ( _petManager.GetActivePetIndex() == -1 )
                        { return false; }
                    }
                    break;
                default:
                    break;
                };
            }

            // �ж���ʱ����������
            SQuest::RequirementTypeItr itrCommit = pQuest->stCommitRequirement.begin();
            SQuest::RequirementTypeItr endCommit = pQuest->stCommitRequirement.end();
            for( ; itrCommit != endCommit; ++itrCommit )
            {
                SQuestRequirement& require = *itrCommit;
                switch ( require.byType )
                {
                case SQuest::eRequirement_Time:
                    { // �ж�ʱ��
                        if ( !SetQuestTime( stQuestId, TimeEx::GetCurrentTime().GetTime() ))
                        {
                            ShowInfo( false, 261, "��ʱ�����ѳ�������" );
                            return false;
                        }
                    }
                    break;
                default:
                    break;
                }
            }

            char tempBuffer[128] = { 0 };
            sprintf_s( tempBuffer, sizeof( tempBuffer ) -1, "@%d", pQuest->QuestName );
            ShowInfo( false, 260, theXmlString.GetString(eClient_get_new_task), tempBuffer );

			MsgTellQuestTime xQuestTime;
			GetQuestTimes( &xQuestTime );
			SendMessageToClient( &xQuestTime );

            // ToModify 
            MsgScriptPlayerMusic msg;
            msg.header.stID = GetID();
            msg.stParameter = 0;
            msg.SetFileName( theXmlString.GetString(eClient_getnewtask_music_path) );
            GettheServer().SendMsgToSingle( &msg, this );
        }
        break;
    case QuestManager::eQuestDone:
        { // ����ƹ��������������߼�
            SQuest::RequirementTypeItr itr = pQuest->stCommitRequirement.begin();
            SQuest::RequirementTypeItr end = pQuest->stCommitRequirement.end();
            for( ; itr != end; ++itr )
            {
                switch ( itr->byType )
                {
                case SQuest::eRequirement_Time:
                    { // �ж�ʱ��
                        __int64 time = GetQuestTime( stQuestId );
                        TimeEx xStartTime( time );    // ����ʱ��
                        TimeEx xCurrentTime = TimeEx::GetCurrentTime(); // ��ǰʱ��
                        if ( xStartTime < xCurrentTime )		//�����ʱ���ж�ԭ��д����
                        { 
                            TimeSpan xSpan = xCurrentTime - xStartTime; 
                            if ( xSpan.GetTotalSeconds() > itr->Value )
                            {
                                ShowInfo( false, 261, "�������ѳ���ʱ��" );
                                return false;
                            }
                        }

                        // �ɹ��������ʱ���¼
                        SetQuestTime( stQuestId, 0 );
                    }
                    break;
                default:
                    break;
                }
            }
        }
        break;
    default:
        break;
    }

    if ( targetState == QuestManager::eQuestGaining )
    { // ����ƹ�����Ľ������߼�
        if ( pQuest->IsPubQuest() )
        {
            thePubQuestManager.ReceiveSpecialQuest( this, GetDBCharacterID(), pQuest->AcceptTargetId, pQuest->Id ); 
        }
        else if ( pQuest->IsConQuest() )
        {
            theConQuestManager.ReceiveSpecialQuest( this, GetDBCharacterID(), pQuest->AcceptTargetId, pQuest->Id ); 
        }
    }
    else 
    { // eQuestNotGain || eQuestDone
        if ( pQuest->IsPubQuest() )
        { // �ƹ� �ʰ�
            thePubQuestManager.DoneSpecialQuest( this, GetDBCharacterID(), pQuest->ReplyTargetId, pQuest->Id ); 
        }
        else if ( pQuest->IsConQuest() )
        { // ����
            theConQuestManager.DoneSpecialQuest( this, GetDBCharacterID(), pQuest->ReplyTargetId, pQuest->Id ); 
        }
    }

    // ���ñ���
    SetVar( stQuestId, theQuestManager.SetQuestState( GetVar( stQuestId ), targetState ) );
	
    return true;
}

char GamePlayer::GetPlayerCountVarState( short nCountVarIdx )
{
    if( nCountVarIdx < 0 || nCountVarIdx > dr_MinQuestId-1 )
    { return 0; }
    return GetVar( nCountVarIdx );
}

bool GamePlayer::IsQuestActive( short stQuestId )
{
    if ( !theQuestManager.IsQuestIdValid( stQuestId ))
    { return false; }

    return theQuestManager.IsQuestActive( GetQuestState( stQuestId ) );
}

bool GamePlayer::IsQuestDone( short stQuestId )
{
    if ( !theQuestManager.IsQuestIdValid( stQuestId ) )
    { return false; }

    return theQuestManager.IsQuestDone( GetQuestState( stQuestId ) );
}

bool GamePlayer::CanGetNewQuest()
{       
    int nActiveQuestCount = 0;
    for( int i = 0; i < dr_MaxQuest; ++i )
    {
        short nQuestId = dr_MinQuestId + i;
        if( theQuestManager.IsQuestActive( GetQuestState( nQuestId ) ) )
        {
            SQuest* pQuest = theQuestManager.GetQuest( nQuestId );
            if( pQuest == NULL || pQuest->IsPubQuest() )
            { continue; }

            if ( pQuest->IsCancel )
            {
                ++nActiveQuestCount;
                if ( nActiveQuestCount >= dr_MaxActiveQuest )
                { break; }
            }
        }
    }

    return ( nActiveQuestCount < dr_MaxActiveQuest );
}

void GamePlayer::Script_GetQuestState( short stQuestId, short stVarId )
{
    int nValue = 0;
    switch ( GetQuestState( stQuestId ))
    {
    case QuestManager::eQuestCantGain:
        nValue = -2;
        break;
    case QuestManager::eQuestNotGain:
        nValue = 0;
        break;
    case QuestManager::eQuestGaining:
        nValue = 1;
        break;
    case QuestManager::eQuestDone:
        nValue = -1;
        break;
	case QuestManager::eQuestFrozen:
		nValue = 3;
		break;
	case QuestManager::eQuestEntrustDone:
		nValue = 2;
		break;
    }

    SetVar( stVarId, nValue );
}

void GamePlayer::Script_GetPlayerCountVar( short nCountVarIdx, short stVarId )
{
    SetVar( stVarId, GetPlayerCountVarState( nCountVarIdx ) );
}

bool GamePlayer::Script_CanGetNewQuest( short stVarId )
{
	bool States = CanGetNewQuest();
	SetVar( stVarId, States ); 
	return States;
}

void GamePlayer::Script_CancelQuest( short stQuestId )
{
    SQuest* pQuest = theQuestManager.GetQuest( stQuestId );
    if( !pQuest )
    {
		#ifdef _DEBUG
        TellClient( "SQuest %ld load failed", stQuestId );
		#endif
        return;
    }

    if ( !pQuest->IsCancel )
    {
		#ifdef _DEBUG
        TellClient( "Cancel SQuest, SQuest %ld is can`t be abandon", stQuestId );
		#endif
        return;
    }

    // ��������ǳ��ڻ״̬
    if( !IsQuestActive( stQuestId ) )
    {
		#ifdef _DEBUG
        TellClient( "Cancel SQuest, SQuest %ld is not active", stQuestId );
		#endif
        return;
    }

    //��û�б�����
    //if( HaveProtectChar() )
    //{//����о�ɱ���Ĺ���
    //    KillProtectChar();
    //}

    // �����������Ӧ�ļ�������
    SQuest::RequirementTypeItr itrCommitReq = pQuest->stCommitRequirement.begin();
    for( ;itrCommitReq != pQuest->stCommitRequirement.end(); ++itrCommitReq )
    {
        switch ( itrCommitReq->byType )
        {
        case SQuest::eRequirement_Var:
        case SQuest::eRequirement_Monster:
        case SQuest::eRequirement_Item:
            if ( itrCommitReq->wVar < dr_MinQuestId && itrCommitReq->wVar >= 0 )
            {
                if( GetVar( itrCommitReq->wVar ) != 0 )
                { SetVar( itrCommitReq->wVar, 0 ); }
            }
            break;
        case SQuest::eRequirement_Time:
            {
                SetQuestTime( stQuestId, 0 );
            }
            break;
        default:
            break;
        }
    }

    SQuest::RequirementTypeItr itrReceiveReq = pQuest->stReceiveRequirement.begin();
    for( ;itrReceiveReq != pQuest->stReceiveRequirement.end();++itrReceiveReq)
    {
        switch (itrReceiveReq->byType)
        {
        case SQuest::eRequirement_Var:
        case SQuest::eRequirement_Monster:
        case SQuest::eRequirement_Item:
            if (itrReceiveReq->wVar < dr_MinQuestId && itrReceiveReq->wVar>=0)
            {
                if( GetVar( itrReceiveReq->wVar ) != 0 )
                { SetVar( itrReceiveReq->wVar, 0 ); }
            }
            break;
        default:
            break;
        }
    }

    // ȡ�����������ϵͳ������0
    SetQuestState( stQuestId, QuestManager::eQuestNotGain );

    char buf[ MAX_PATH + 1] = { 0 };
    sprintf_s( buf, MAX_PATH,CANCELQUESTS_SCRIPT_FILEPATH_FORMAT,stQuestId );
    int nVmId = GetScriptMgr()->CreateVM( ST_CANCELQUEST,buf, stQuestId );
    if (nVmId != -1)
    { GetScriptMgr()->StartupVM( ST_CANCELQUEST, stQuestId, this ); }

    char showbuf[128] = { 0 };
    sprintf_s( showbuf, sizeof( showbuf ) - 1,"@%d",pQuest->QuestName );
    ShowInfo(false, 260, theXmlString.GetString(eClient_AddInfo_2slk_62), showbuf );    // ������������״̬��ö��260

}

// ������ɽ�������
int GamePlayer::CalcGuildQuestReleaseRewardModulus( int nQuestID )
{
    if ( m_pGuild == NULL || m_pGuild->GetReleaseQuest() == 0 )
    { return 1; }

    const GuildConfig::ReleaseSetting& xSetting = theGuildConfig.GetReleaseSetting();
    const GuildConfig::ReleaseSetting::QuestSetting* pSetting = xSetting.GetQuestSetting( m_pGuild->GetReleaseQuest() );
    if ( pSetting == NULL || !pSetting->CheckQuest( nQuestID ) )
    { return 1; }

    switch ( GetGuildPositon() )
    {
    case GuildDefine::Position_Member:
    case GuildDefine::Position_FamilyMaster:
        return pSetting->GetMemberReward();
        break;
    case GuildDefine::Position_ViceMaster:
        return pSetting->GetViceReward();
        break;
    case GuildDefine::Position_Master:
        return pSetting->GetMasterReward();
        break;
    default:
        break;
    }

    return 1;
}

bool GamePlayer::Script_CheckDoneQuest( short stQuestId )
{
    SQuest* pQuest = theQuestManager.GetQuest( stQuestId );
    if( pQuest == NULL )
    { return false; }

    if( !IsQuestActive( stQuestId ) )
    { return false; }   // ��������ǳ��ڻ״̬

    return false;
}

//�ű��������
bool GamePlayer::Script_DoneQuest( short stQuestId )
{
    SQuest* pQuest = theQuestManager.GetQuest( stQuestId );
    if( pQuest == NULL )
    { return false; }

    if( !IsQuestActive( stQuestId ) )
    { return false; }   // ��������ǳ��ڻ״̬

    // ��������״̬
    bool bDone = SetQuestState( stQuestId, ( pQuest->IsRepeat ? QuestManager::eQuestNotGain : QuestManager::eQuestDone ) );

    // �����Ƿ���ö���Ľ���
    // �жϹ�������ʱ��, ����˫��
    int nRewardModulus = 1; 
    switch ( pQuest->chQuestType )
    {
    case SQuest::Type_CountryKing:      // ��������
        {
            nRewardModulus += IsCountryQuestOpen( CountryDefine::QuestType_King );
        }
        break;
    case SQuest::Type_CountryGeneral:   // ��������
        {
            nRewardModulus += IsCountryQuestOpen( CountryDefine::QuestType_General );

            // ���¹���ʵ��
            const CountryConfig::StrengthSetting& xSetting = theCountryConfig.GetStrengthSetting();
            m_pCountry->SendCountryDataChangeReq( CountryDefine::UpdateNowStrength, CountryDefine::OperateAdd, xSetting.GetQuestModulus() );

			m_pCountry->SetAddDoneQuestStrength(xSetting.GetQuestModulus());
        }
        break;
    case SQuest::Type_CountryLeft:      // ��������
        {
            nRewardModulus += IsCountryQuestOpen( CountryDefine::QuestType_CouncilorLeft );
        }
        break;
    case SQuest::Type_CountryRight:     // ̽������
        {
            nRewardModulus += IsCountryQuestOpen( CountryDefine::QuestType_CouncilorRight );
        }
        break;
    case SQuest::Type_Guild:            // ��������
        {
            nRewardModulus = CalcGuildQuestReleaseRewardModulus( stQuestId );
        }
        break;
    default:
        break;
    }

    //�в��ֽ�������û��ʵ��
    for( int i = 0; i < pQuest->stReward.size(); i++ )
    {
        SQuestReward* r = &pQuest->stReward[i];
        switch(r->byType)
        {
        case SQuest::eReward_Money:
            {
                int RewardValue = r->Value * nRewardModulus;
                OperateMoney( EOT_Add, RewardValue, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_DoneQuest);
            }
            break;
        case SQuest::eReward_Item:
            {
                //ֻ�������Ա��ְҵ��ͬ�ĵ���
                int tempsex = 0;
                if(r->shSex != Sex_Male&&r->shSex != Sex_Female&&r->shSex!= Sex_Max)
                {
                    tempsex = Sex_Max+1;
                }
                else
                    tempsex = r->shSex;

                if ((tempsex == gCharInfoServer.baseinfo.aptotic.ucSex|| tempsex==Sex_Max) && (r->shProfession & 1<<GetProfession() || r->shProfession == 0 ))
                {
                    if (GettheItemDetail().IsEquipItem(r->Value) )
                    {
                        AddEquipItem( r->Value , r->Number, EIGS_Quest, r->bIsBound, NULL, r->bIsStarRandom, r->nStarLevel );
                    }
                    else
                    {
                        AddItem( r->Value , r->Number, EIGS_Quest, r->bIsBound, NULL );
                    }

                }
            }
            break;
        case SQuest::eReward_Exp:
            {
                int RewardValue = r->Value * nRewardModulus;
				//�������� �ж���ҵĹ����Ƿ�Ϊ��ǿ��
				/*if(GetCountryId() != theGameCountryManager.GetStrongCountry() && GetCountryId() != theGameCountryManager.GetWeakCountry() && GetCountryId() !=CountryDefine::Country_Init)
				{
					RewardValue = RewardValue * 1.1;
				}
				else if(GetCountryId() != theGameCountryManager.GetStrongCountry() && GetCountryId() == theGameCountryManager.GetWeakCountry() && GetCountryId() !=CountryDefine::Country_Init)
				{
					RewardValue = RewardValue * 1.05;
				}*/
                Script_SetExp( RewardValue , SKW_SETADD, __FUNCTION__, __LINE__ );
            }
            break;
        case SQuest::eReward_SkillExp:
            {
                Script_SetSkillExp( r->Value * nRewardModulus, SKW_SETADD );
            }
            break;

        case SQuest::eReward_Title:
            {
                AddTitle(r->Value);
            }
            break;
        case SQuest::eReward_Reputation:
            {
                int nValue = r->Value * nRewardModulus;
                OperateReputation( EOT_Add, nValue, __FUNCTION__, __LINE__,ePlayerMoneySourceType_DoneQuest );
            }   
            break;
        case SQuest::eReward_Exploit:
            {
                int nValue = r->Value * nRewardModulus;
                OperateExploit( EOT_Add, nValue, __FUNCTION__, __LINE__,ePlayerMoneySourceType_DoneQuest );
            }
            break;
        case SQuest::eReward_GuildContribute:
            {
                OperateGuildOffer( GuildDefine::OperateAdd, r->Value * nRewardModulus );
            }
            break;
        case SQuest::eReward_JiaoZi:
            {
                int RewardValue = r->Value * nRewardModulus;
                OperateJiaoZi( EOT_Add, RewardValue, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_DoneQuest);
            }
            break;
        case SQuest::eReward_Honor:
            {
                int RewardValue = r->Value * nRewardModulus;
                OperateHonour( EOT_Add, RewardValue, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_DoneQuest);
            }
            break;
		case SQuest::eReward_CountryMoney:
			{
				//��ǰ���������ҽ�Ǯ
				int RewardValue = r->Value * nRewardModulus;
				//��ӹ��ҽ�Ǯ
				if(m_pCountry)
				{
					GS2CSCountryMoneyRaiseed xRaiseed;
					xRaiseed.nType = 0;
					xRaiseed.uchCountryID = m_pCountry->GetID();
					xRaiseed.nMoney       = RewardValue;
					GettheServer().SendMsgToCenterServer( &xRaiseed );
				}
			}
			break;
        default:
            break;
        }
    }

    // ����ľ��齱��
    DoneQuestRewardExp( pQuest, nRewardModulus );           

    //�����������
    UpdatePlayerCounterByCount(TitleConfig::Condition_Quest, stQuestId);

	//����7����
	_sevenDayManager.TriggerSevenDaysVar( (int)SevenDaysConfig::TD_SecondDay, stQuestId );

    MsgDoneQuest msg;
    msg.playerId = GetID();
    msg.nQuestId = stQuestId;
    GettheServer().SendMsgToSingle( &msg, this );

   // Log( "������� [%d]", pQuest->Id );
	//LYH��־���
	if(!theLogEventService.LogQuest(GetAccountID(),GetDBCharacterID(),pQuest->Id,GetCharName()))
	{
	Log( theXmlString.GetString(eServerLog_QuestOK), pQuest->Id );
	}
    return true;
}

bool GamePlayer::DoneSingleRequirementQuest( short stQuestId, int nRewardID )
{
    SQuest* pQuest = theQuestManager.GetQuest( stQuestId );
    if( pQuest == NULL )
    { return false; }

    if( !IsQuestActive( stQuestId ) )
    { return false; }   // ��������ǳ��ڻ״̬

    // ��������״̬
    bool bDone = SetQuestState( stQuestId, ( pQuest->IsRepeat ? QuestManager::eQuestNotGain : QuestManager::eQuestDone ) );

    // �����Ƿ���ö���Ľ���
    // �жϹ�������ʱ��, ����˫��
    int nRewardModulus = 1; 
    switch ( pQuest->chQuestType )
    {
    case SQuest::Type_CountryKing:      // ��������
        {
            nRewardModulus += IsCountryQuestOpen( CountryDefine::QuestType_King );
        }
        break;
    case SQuest::Type_CountryGeneral:   // ��������
        {
            nRewardModulus += IsCountryQuestOpen( CountryDefine::QuestType_General );

            // ���¹���ʵ��
            const CountryConfig::StrengthSetting& xSetting = theCountryConfig.GetStrengthSetting();
            m_pCountry->SendCountryDataChangeReq( CountryDefine::UpdateNowStrength, CountryDefine::OperateAdd, xSetting.GetQuestModulus() );

			m_pCountry->SetAddDoneQuestStrength(xSetting.GetQuestModulus());
        }
        break;
    case SQuest::Type_CountryLeft:      // ��������
        {
            nRewardModulus += IsCountryQuestOpen( CountryDefine::QuestType_CouncilorLeft );
        }
        break;
    case SQuest::Type_CountryRight:     // ̽������
        {
            nRewardModulus += IsCountryQuestOpen( CountryDefine::QuestType_CouncilorRight );
        }
        break;
    case SQuest::Type_Guild:            // ��������
        {
            nRewardModulus = CalcGuildQuestReleaseRewardModulus( stQuestId );
        }
        break;
    default:
        break;
    }

    //�в��ֽ�������û��ʵ��
    for( int i = 0; i < pQuest->stReward.size(); i++ )
    {
        SQuestReward* r = &pQuest->stReward[i];
        if ( r->RewardID != nRewardID )
        { continue; }

        switch(r->byType)
        {
        case SQuest::eReward_Money:
            {
                int RewardValue = r->Value * nRewardModulus;
                OperateMoney( EOT_Add, RewardValue, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_DoneQuest);
            }
            break;
        case SQuest::eReward_Item:
            {
                //ֻ�������Ա��ְҵ��ͬ�ĵ���
                int tempsex = 0;
                if(r->shSex != Sex_Male&&r->shSex != Sex_Female&&r->shSex!= Sex_Max)
                {
                    tempsex = Sex_Max+1;
                }
                else
                    tempsex = r->shSex;

                if ((tempsex == gCharInfoServer.baseinfo.aptotic.ucSex|| tempsex==Sex_Max) && (r->shProfession & 1<<GetProfession() || r->shProfession == 0 ))
                {
                    if (GettheItemDetail().IsEquipItem(r->Value) )
                    {
                        AddEquipItem( r->Value , r->Number, EIGS_Quest, r->bIsBound, NULL, r->bIsStarRandom, r->nStarLevel );
                    }
                    else
                    {
                        AddItem( r->Value , r->Number, EIGS_Quest, r->bIsBound, NULL );
                    }

                }
            }
            break;
        case SQuest::eReward_Exp:
            {
                int RewardValue = r->Value * nRewardModulus;
				/*if(GetCountryId() != theGameCountryManager.GetStrongCountry() && GetCountryId() != theGameCountryManager.GetWeakCountry() && GetCountryId() !=CountryDefine::Country_Init)
				{
					RewardValue = RewardValue * 1.1;
				}
				else if(GetCountryId() != theGameCountryManager.GetStrongCountry() && GetCountryId() == theGameCountryManager.GetWeakCountry() && GetCountryId() !=CountryDefine::Country_Init)
				{
					RewardValue = RewardValue * 1.05;
				}*/
                Script_SetExp( RewardValue , SKW_SETADD, __FUNCTION__, __LINE__ );
            }
            break;
        case SQuest::eReward_SkillExp:
            {
                Script_SetSkillExp( r->Value * nRewardModulus, SKW_SETADD );
            }
            break;

        case SQuest::eReward_Title:
            {
                AddTitle(r->Value);
            }
            break;
        case SQuest::eReward_Reputation:
            {
                int nValue = r->Value * nRewardModulus;
                OperateReputation( EOT_Add, nValue, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_DoneQuest);
            }   
            break;
        case SQuest::eReward_Exploit:
            {
                int nValue = r->Value * nRewardModulus;
                OperateExploit( EOT_Add, nValue, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_DoneQuest);
            }
            break;
        case SQuest::eReward_GuildContribute:
            {
                OperateGuildOffer( GuildDefine::OperateAdd, r->Value * nRewardModulus );
            }
            break;
        case SQuest::eReward_JiaoZi:
            {
                int RewardValue = r->Value * nRewardModulus;
                OperateJiaoZi( EOT_Add, RewardValue, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_DoneQuest);
            }
            break;
        case SQuest::eReward_Honor:
            {
                int RewardValue = r->Value * nRewardModulus;
                OperateHonour( EOT_Add, RewardValue, __FUNCTION__, __LINE__,ePlayerMoneySourceType_DoneQuest );
            }
            break;
		case SQuest::eReward_CountryMoney:
			{
				//��ǰ���������ҽ�Ǯ
				int RewardValue = r->Value * nRewardModulus;
				//��ӹ��ҽ�Ǯ
				if(m_pCountry)
				{
					GS2CSCountryMoneyRaiseed xRaiseed;
					xRaiseed.nType = 0;
					xRaiseed.uchCountryID = m_pCountry->GetID();
					xRaiseed.nMoney       = RewardValue;
					GettheServer().SendMsgToCenterServer( &xRaiseed );
				}
			}
			break;
        default:
            break;
        }
    }

    // ����ľ��齱��
    DoneQuestRewardExp( pQuest, nRewardModulus );           

    //�����������
    UpdatePlayerCounterByCount(TitleConfig::Condition_Quest, stQuestId);

    MsgDoneQuest msg;
    msg.playerId = GetID();
    msg.nQuestId = stQuestId;
    GettheServer().SendMsgToSingle( &msg, this );

	//LYH��־���
	if(!theLogEventService.LogQuest(GetAccountID(),GetDBCharacterID(),pQuest->Id,GetCharName()))
	{
		Log( theXmlString.GetString(eServerLog_QuestOK), pQuest->Id );
	}
    return true;
}

void GamePlayer::DoneQuestRewardExp(SQuest* pQuest, int nRewardModulus /* = 1 */)
{
	//��ʱȥ��,�߻�û�ж��⾭�齱��������,���������Ҫ�Ļ������ٸ����߼��ӻ�ȥ,by vvx 2012.10.19
	return;
    if ( pQuest == NULL )
    { return; }

    short QuestId = pQuest->Id;
    float RewardValue = 0.0f;

    if (QuestId == 5200)
    {    // �������
        RewardValue = GetLevel() * 200;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId > 5200 && QuestId <= 5249 )
    {
        RewardValue = GetLevel() * 200 +  GetVar(474) * GetLevel() * 250;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId > 5249 && QuestId <= 5265 )
    {
        RewardValue = 2 * (GetLevel() * 200 + GetVar(474) * GetLevel() * 250);
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId == 5001 )
    {   // һ��֮����������
        RewardValue = GetLevel() * 200;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId > 5001 && QuestId <= 5020 )
    {
        RewardValue = GetLevel() * 200 + GetVar(474) * GetLevel() * 150;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId > 5020 && QuestId <= 5039 )
    {
        RewardValue = (GetLevel() * 200 + GetVar(474) * GetLevel() * 150) * 2;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId == 5150 )
    {
        // פ�ر߽�
        RewardValue = GetLevel() * 2000;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId >= 5350 && QuestId <= 5354 )
    {    // �������
        RewardValue = GetLevel() * 1100;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId >= 5355 && QuestId <= 5359 )
    {   // �����ɱ
        RewardValue = GetLevel() * 1100;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId >= 5360 && QuestId <= 5364 )
    {    // ����鱨
        RewardValue = GetLevel() * 1100;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId >= 5365 && QuestId <= 5369 )
    {   // �������
        RewardValue = GetLevel() * 1100;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId >= 5481 && QuestId <= 5490 )
    {   // �˹�֮·
        RewardValue = GetLevel() * 40000;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId > 5490 && QuestId <= 5499 )
    {
        RewardValue = GetLevel() * 60000;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId > 5499 && QuestId <= 5503 )
    {
        RewardValue = GetLevel() * 80000;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId >= 5271 && QuestId <= 5281 )
    {    // �ﾺ����
        RewardValue = GetLevel() * 2250;
        RewardValue = floor(RewardValue);

    }
    else if ( QuestId == 5471 )
    {   // ��������
        RewardValue = (GetLevel() - 40) * 1200 + 11250;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId >= 5511 && QuestId <= 5515 )
    {   // ������Ͷ
        RewardValue = 1.1 * (3000 + (GetLevel() - 20) * 130);
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId > 5515 && QuestId <= 5519 )
    {
        RewardValue = 1.2 * (3000 + (GetLevel() - 20) * 130);
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId > 5519 && QuestId <= 5523 )
    {
        RewardValue = 1.3 * (3000 + (GetLevel() - 20) * 130);
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId > 5523 && QuestId <= 5527 )
    {
        RewardValue = 1.4 * (3000 + (GetLevel() - 20) * 130);
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId >= 3550 && QuestId <= 3565 )
    {   // �鸣�콵
        RewardValue = GetLevel() * 4500;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId >= 5531 && QuestId <= 5575 )
    {    // �������
        RewardValue = GetLevel() * 200 + GetVar(200) * GetLevel() * 50;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId == 5581 )
    {   // ����ľ
        RewardValue = 112500 + (GetLevel() - 40) * 12000;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId >= 5585 && QuestId <= 5586 )
    {   // ��Ụ��
        RewardValue = GetLevel() * 6000;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId >= 5122 && QuestId <= 5125 )
    {  // �ٸ�Ѻ��
        RewardValue = GetLevel() * 5000;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId == 5091 )
    {   // �����ĺ�
        RewardValue = GetLevel() * 3000;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId == 5580 )
    {   // ���ļ����
        RewardValue = GetLevel() * 20000;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId >= 5701 && QuestId <= 5720 )
    {   // ��������20�����֣�
        if ( pQuest->RankId == 0 )
        {
            RewardValue = 10000 + GetLevel() * 200;
            RewardValue = floor(RewardValue);
        }
        else if ( pQuest->RankId == 1 )
        {
            RewardValue = 10000 + GetLevel() * 600;
            RewardValue = floor(RewardValue);
        }
        else if ( pQuest->RankId == 2 )
        {
            RewardValue = 10000 + GetLevel() * 1000;
            RewardValue = floor(RewardValue);
        }
        else if ( pQuest->RankId == 3 )
        {
            RewardValue = 10000 + GetLevel() * 2000;
            RewardValue = floor(RewardValue);
        }
    } 
    else if ( QuestId >= 5721 && QuestId <= 5740 )
    {   // ��������30�����֣�
        if ( pQuest->RankId == 0 )
        {
            RewardValue = 20000 + GetLevel() * 300;
            RewardValue = floor(RewardValue);
        }
        else if ( pQuest->RankId == 1 )
        {
            RewardValue = 20000 + GetLevel() * 800;
            RewardValue = floor(RewardValue);
        }
        else if ( pQuest->RankId == 2 )
        {
            RewardValue = 20000 + GetLevel() * 1200;
            RewardValue = floor(RewardValue);
        }
        else if ( pQuest->RankId == 3 )
        {
            RewardValue = 20000 + GetLevel() * 2500;
            RewardValue = floor(RewardValue);
        }
    }
    else if ( QuestId >= 5741 && QuestId <= 5760 )
    {   // ��������40�����֣�
        if ( pQuest->RankId == 0 )
        {
            RewardValue = 50000 + GetLevel() * 400;
            RewardValue = floor(RewardValue);
        }
        else if ( pQuest->RankId == 1 )
        {
            RewardValue = 50000 + GetLevel() * 1000;
            RewardValue = floor(RewardValue);
        }
        else if ( pQuest->RankId == 2 )
        {
            RewardValue = 50000 + GetLevel() * 1500;
            RewardValue = floor(RewardValue);
        }
        else if ( pQuest->RankId == 3 )
        {
            RewardValue = 50000 + GetLevel() * 3000;
            RewardValue = floor(RewardValue);
        }
    }
    else if ( QuestId >= 5761 && QuestId <= 5780 )
    {   // ��������50�����֣�
        if ( pQuest->RankId == 0 )
        {
            RewardValue = 60000 + GetLevel() * 500;
            RewardValue = floor(RewardValue);
        }
        else if ( pQuest->RankId == 1 )
        {
            RewardValue = 60000 + GetLevel() * 1400;
            RewardValue = floor(RewardValue);
        }
        else if ( pQuest->RankId == 2 )
        {
            RewardValue = 60000 + GetLevel() * 1800;
            RewardValue = floor(RewardValue);
        }
        else if ( pQuest->RankId == 3 )
        {
            RewardValue = 60000 + GetLevel() * 4000;
            RewardValue = floor(RewardValue);
        }
    }
    else if ( QuestId >= 5590 && QuestId <= 5594 )
    { // ����ι��
        RewardValue = GetLevel() * 5000;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId == 5045 )
    {
        RewardValue = GetLevel() * 5000;
        RewardValue = floor(RewardValue);
    }

    if ( RewardValue <= 0.0f )
    { return; }

    RewardValue *= nRewardModulus; 
    Script_SetExp( RewardValue, SKW_SETADD, __FUNCTION__, __LINE__ );
}

__int64 GamePlayer::GetQuestTime( uint16 questId )
{
    for ( uint8 i=0; i<QuestLimitTimeMaxCount; ++i )
    {
        // ����������
        if ( gCharInfoServer.otherdata.vars.questTime[ i ].id == 0)
        { break; }
        
        if ( gCharInfoServer.otherdata.vars.questTime[ i ].id == questId )
        { return gCharInfoServer.otherdata.vars.questTime[ i ].time; }
    }
    
    return 0;
}

bool GamePlayer::SetQuestTime( uint16 questId, __int64 time )
{
    for ( uint8 i=0; i<QuestLimitTimeMaxCount; ++i )
    {
        // ����������
        if ( gCharInfoServer.otherdata.vars.questTime[ i ].id != 0)
        { continue; }

        gCharInfoServer.otherdata.vars.questTime[ i ].id   = questId;
        gCharInfoServer.otherdata.vars.questTime[ i ].time = time;
        return true;
    }

    return false;
}