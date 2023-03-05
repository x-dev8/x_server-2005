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
	//判断指定任务是否可以接取
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
		return false;//只有未接取的任务才可以再接取


	SQuest::RequirementTypeItr itr = pQuest->stReceiveRequirement.begin();
    SQuest::RequirementTypeItr end = pQuest->stReceiveRequirement.end();
    for( ; itr != end; ++itr )
    {
        switch ( itr->byType )
        {
        case SQuest::eRequirement_Money:                    // 检查钱是否足够
            {
                if ( GetMoney() < itr->Value )
                {
                    return false;
                }
            }       
            break;
        case SQuest::eRequirement_Item:                     //检查该道具的个数是否满足接任务的条件
            {
                int nCount = GetItemCount( itr->Value );
                if( nCount < itr->MaxNum )
                {
                    return false;
                }
            }
            break;
        case SQuest::eRequirement_Energy:                   // 判断活力值
            {
                if ( gCharInfoServer.baseinfo.liveinfo.activity < itr->Value )
                {
                    return false;
                }
            }
            break;
        case SQuest::eRequirement_Level:                    // 判断等级
            {
                if ( GetLevel() < itr->Value )
                {
                    return false;
                }
            }
            break;
        case SQuest::eRequirement_Reputation:               // 判断声望
            {
                if ( GetReputation() < itr->Value )
				{
                    return false;
                }
            }
            break;
        case SQuest::eRequirement_Sex:                      // 判断性别
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
        case SQuest::eRequirement_Profession:               //主要用于多兵种限制，1位移职业判断一下是否存允许该职业
            {
                if ( ( itr->Value & ( 1 << gCharInfoServer.baseinfo.aptotic.usProfession ) ) == 0 )
                {
                    return false;
                }
            }
            break;
        case SQuest::eRequirement_Var:                      // 判断记数变量
            {
                if ( GetVar( itr->wVar ) < itr->MaxNum )
                {
                    return false;
                }
            }
            break;
        case SQuest::eRequirement_Quest: // 前置任务
            {
                uint8 nState = GetQuestState( itr->Value ); 
				if ( nState != QuestManager::eQuestDone) // 前置任务没有完成
                {
                    return false;
                }
            }
            break;
        case SQuest::eRequirement_VarLimit:                 // 记数限制, 超过该记数限制, 不能领取任务
            {
                if ( GetVar( itr->wVar ) >= itr->MaxNum )
                { return false; }
            }   
            break;
        case SQuest::eRequirement_WeakCountry: 
            { // 弱国任务
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

    // 判断是时间限制任务
    SQuest::RequirementTypeItr itrCommit = pQuest->stCommitRequirement.begin();
    SQuest::RequirementTypeItr endCommit = pQuest->stCommitRequirement.end();
    for( ; itrCommit != endCommit; ++itrCommit )
    {
        SQuestRequirement& require = *itrCommit;
        switch ( require.byType )
        {
        case SQuest::eRequirement_Time:
            { // 判断时间
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
    //// 任务不可能从 完成状态 到 已接状态,中间已经要到可接状态 或者 任务不可能从 可接状态 到 完成状态  ( 策划需要有这样的流程,所以注释掉 )
    //if ( ( chLastState == -1 && chState == 1 ) || ( chLastState == 0 && chState == -1 ) )
    //{
    //    LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "任务[%d] 从状态[%d] 到 状态[%d] 不合法!", stQuestId, chLastState, chState );
    //    return false; 
    //}   

    SQuest* pQuest = theQuestManager.GetQuest( stQuestId );
    if ( pQuest == NULL )
    { return false; }

	
	/*
	 * Author: 2012-10-8 15:48:11 liaojie
	 * Desc:   增加国家判断
	 */
	uint8 countryID = GetCountryId();
	if (pQuest->Country!=0 && countryID!=pQuest->Country)
	{
		return false;
	}

    // chState == 1 接任务  chState == -1 完成任务 目标chState状态
    // 目前完成任务条件判断都在脚本中，程序只判断前置条件
    switch ( targetState )
    {
    case QuestManager::eQuestGaining:
        { // 接任务
            // 判断接的条件是否满足
            SQuest::RequirementTypeItr itr = pQuest->stReceiveRequirement.begin();
            SQuest::RequirementTypeItr end = pQuest->stReceiveRequirement.end();
            for( ; itr != end; ++itr )
            {
                switch ( itr->byType )
                {
                case SQuest::eRequirement_Money:                    // 检查钱是否足够
                    {
                        if ( GetMoney() < itr->Value )
                        {
                            ShowInfo( false, 261, theXmlString.GetString(eTell_Client_CannotTaskBCMoney) );
                            return false;
                        }
                    }       
                    break;
                case SQuest::eRequirement_Item:                     //检查该道具的个数是否满足接任务的条件
                    {
                        int nCount = GetItemCount( itr->Value );
                        if( nCount < itr->MaxNum )
                        {
                            ShowInfo( false, 261, theXmlString.GetString(eTell_Client_CannotTaskBCItem) );
                            return false;
                        }
                    }
                    break;
                case SQuest::eRequirement_Energy:                   // 判断活力值
                    {
                        if ( gCharInfoServer.baseinfo.liveinfo.activity < itr->Value )
                        {
                            ShowInfo( false, 261, theXmlString.GetString(eTell_Client_CannotTaskBCEnergy) );
                            return false;
                        }
                    }
                    break;
                case SQuest::eRequirement_Level:                    // 判断等级
                    {
                        if ( GetLevel() < itr->Value )
                        {
                            ShowInfo( false, 261, theXmlString.GetString(eTell_Client_CannotTaskBCLevel), itr->Value );
                            return false;
                        }
                    }
                    break;
                case SQuest::eRequirement_Reputation:               // 判断声望
                    {
                        if ( GetReputation() < itr->Value )
                        {
                            ShowInfo( false, 261, theXmlString.GetString(eTell_Client_CannotTaskBCReputation) );
                            return false;
                        }
                    }
                    break;
                case SQuest::eRequirement_Sex:                      // 判断性别
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
                case SQuest::eRequirement_Profession:               //主要用于多兵种限制，1位移职业判断一下是否存允许该职业
                    {
                        if ( ( itr->Value & ( 1 << gCharInfoServer.baseinfo.aptotic.usProfession ) ) == 0 )
                        {
                            ShowInfo( false, 261, theXmlString.GetString(eTell_Client_CannotTaskBCProfession) );
                            return false;
                        }
                    }
                    break;
                case SQuest::eRequirement_Var:                      // 判断记数变量
                    {
                        if ( GetVar( itr->wVar ) < itr->MaxNum )
                        {
                            ShowInfo( false, 261, theXmlString.GetString(eTell_Client_CannotTaskBCFrontQuest)  );
                            return false;
                        }
                    }
                    break;
                case SQuest::eRequirement_Quest: // 前置任务
                    {
                        uint8 nState = GetQuestState( itr->Value ); 
                        if ( nState != QuestManager::eQuestDone) // 前置任务没有完成
                        {
                            ShowInfo( false, 261, theXmlString.GetString(eTell_Client_CannotTaskBCFrontQuest) );
                            return false;
                        }
                    }
                    break;
                case SQuest::eRequirement_VarLimit:                 // 记数限制, 超过该记数限制, 不能领取任务
                    {
                        if ( GetVar( itr->wVar ) >= itr->MaxNum )
                        { return false; }
                    }   
                    break;
                case SQuest::eRequirement_WeakCountry: 
                    { // 弱国任务
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

            // 判断是时间限制任务
            SQuest::RequirementTypeItr itrCommit = pQuest->stCommitRequirement.begin();
            SQuest::RequirementTypeItr endCommit = pQuest->stCommitRequirement.end();
            for( ; itrCommit != endCommit; ++itrCommit )
            {
                SQuestRequirement& require = *itrCommit;
                switch ( require.byType )
                {
                case SQuest::eRequirement_Time:
                    { // 判断时间
                        if ( !SetQuestTime( stQuestId, TimeEx::GetCurrentTime().GetTime() ))
                        {
                            ShowInfo( false, 261, "限时任务已超过上限" );
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
        { // 处理酒馆任务的完成任务逻辑
            SQuest::RequirementTypeItr itr = pQuest->stCommitRequirement.begin();
            SQuest::RequirementTypeItr end = pQuest->stCommitRequirement.end();
            for( ; itr != end; ++itr )
            {
                switch ( itr->byType )
                {
                case SQuest::eRequirement_Time:
                    { // 判断时间
                        __int64 time = GetQuestTime( stQuestId );
                        TimeEx xStartTime( time );    // 到期时间
                        TimeEx xCurrentTime = TimeEx::GetCurrentTime(); // 当前时间
                        if ( xStartTime < xCurrentTime )		//这儿的时间判断原来写错了
                        { 
                            TimeSpan xSpan = xCurrentTime - xStartTime; 
                            if ( xSpan.GetTotalSeconds() > itr->Value )
                            {
                                ShowInfo( false, 261, "您任务已超过时间" );
                                return false;
                            }
                        }

                        // 成功清掉任务时间纪录
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
    { // 处理酒馆任务的接任务逻辑
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
        { // 酒馆 皇榜
            thePubQuestManager.DoneSpecialQuest( this, GetDBCharacterID(), pQuest->ReplyTargetId, pQuest->Id ); 
        }
        else if ( pQuest->IsConQuest() )
        { // 征伐
            theConQuestManager.DoneSpecialQuest( this, GetDBCharacterID(), pQuest->ReplyTargetId, pQuest->Id ); 
        }
    }

    // 设置变量
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

    // 如果任务不是出于活动状态
    if( !IsQuestActive( stQuestId ) )
    {
		#ifdef _DEBUG
        TellClient( "Cancel SQuest, SQuest %ld is not active", stQuestId );
		#endif
        return;
    }

    //有没有保护怪
    //if( HaveProtectChar() )
    //{//如果有就杀死改怪物
    //    KillProtectChar();
    //}

    // 清除此任务相应的记数变量
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

    // 取消任务后，任务系统变量置0
    SetQuestState( stQuestId, QuestManager::eQuestNotGain );

    char buf[ MAX_PATH + 1] = { 0 };
    sprintf_s( buf, MAX_PATH,CANCELQUESTS_SCRIPT_FILEPATH_FORMAT,stQuestId );
    int nVmId = GetScriptMgr()->CreateVM( ST_CANCELQUEST,buf, stQuestId );
    if (nVmId != -1)
    { GetScriptMgr()->StartupVM( ST_CANCELQUEST, stQuestId, this ); }

    char showbuf[128] = { 0 };
    sprintf_s( showbuf, sizeof( showbuf ) - 1,"@%d",pQuest->QuestName );
    ShowInfo(false, 260, theXmlString.GetString(eClient_AddInfo_2slk_62), showbuf );    // 复用设置任务状态的枚举260

}

// 计算帮派奖励倍数
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
    { return false; }   // 如果任务不是出于活动状态

    return false;
}

//脚本完成任务
bool GamePlayer::Script_DoneQuest( short stQuestId )
{
    SQuest* pQuest = theQuestManager.GetQuest( stQuestId );
    if( pQuest == NULL )
    { return false; }

    if( !IsQuestActive( stQuestId ) )
    { return false; }   // 如果任务不是出于活动状态

    // 设置任务状态
    bool bDone = SetQuestState( stQuestId, ( pQuest->IsRepeat ? QuestManager::eQuestNotGain : QuestManager::eQuestDone ) );

    // 计算是否额获得额外的奖励
    // 判断国家任务时段, 奖励双倍
    int nRewardModulus = 1; 
    switch ( pQuest->chQuestType )
    {
    case SQuest::Type_CountryKing:      // 国运任务
        {
            nRewardModulus += IsCountryQuestOpen( CountryDefine::QuestType_King );
        }
        break;
    case SQuest::Type_CountryGeneral:   // 出国任务
        {
            nRewardModulus += IsCountryQuestOpen( CountryDefine::QuestType_General );

            // 更新国家实力
            const CountryConfig::StrengthSetting& xSetting = theCountryConfig.GetStrengthSetting();
            m_pCountry->SendCountryDataChangeReq( CountryDefine::UpdateNowStrength, CountryDefine::OperateAdd, xSetting.GetQuestModulus() );

			m_pCountry->SetAddDoneQuestStrength(xSetting.GetQuestModulus());
        }
        break;
    case SQuest::Type_CountryLeft:      // 天行任务
        {
            nRewardModulus += IsCountryQuestOpen( CountryDefine::QuestType_CouncilorLeft );
        }
        break;
    case SQuest::Type_CountryRight:     // 探宝任务
        {
            nRewardModulus += IsCountryQuestOpen( CountryDefine::QuestType_CouncilorRight );
        }
        break;
    case SQuest::Type_Guild:            // 帮派任务
        {
            nRewardModulus = CalcGuildQuestReleaseRewardModulus( stQuestId );
        }
        break;
    default:
        break;
    }

    //有部分奖励类型没有实现
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
                //只奖励是性别和职业相同的道具
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
				//奖励经验 判断玩家的国家是否为非强国
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
				//当前任务奖励国家金钱
				int RewardValue = r->Value * nRewardModulus;
				//添加国家金钱
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

    // 额外的经验奖励
    DoneQuestRewardExp( pQuest, nRewardModulus );           

    //更新任务记数
    UpdatePlayerCounterByCount(TitleConfig::Condition_Quest, stQuestId);

	//触发7天乐
	_sevenDayManager.TriggerSevenDaysVar( (int)SevenDaysConfig::TD_SecondDay, stQuestId );

    MsgDoneQuest msg;
    msg.playerId = GetID();
    msg.nQuestId = stQuestId;
    GettheServer().SendMsgToSingle( &msg, this );

   // Log( "完成任务 [%d]", pQuest->Id );
	//LYH日志添加
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
    { return false; }   // 如果任务不是出于活动状态

    // 设置任务状态
    bool bDone = SetQuestState( stQuestId, ( pQuest->IsRepeat ? QuestManager::eQuestNotGain : QuestManager::eQuestDone ) );

    // 计算是否额获得额外的奖励
    // 判断国家任务时段, 奖励双倍
    int nRewardModulus = 1; 
    switch ( pQuest->chQuestType )
    {
    case SQuest::Type_CountryKing:      // 国运任务
        {
            nRewardModulus += IsCountryQuestOpen( CountryDefine::QuestType_King );
        }
        break;
    case SQuest::Type_CountryGeneral:   // 出国任务
        {
            nRewardModulus += IsCountryQuestOpen( CountryDefine::QuestType_General );

            // 更新国家实力
            const CountryConfig::StrengthSetting& xSetting = theCountryConfig.GetStrengthSetting();
            m_pCountry->SendCountryDataChangeReq( CountryDefine::UpdateNowStrength, CountryDefine::OperateAdd, xSetting.GetQuestModulus() );

			m_pCountry->SetAddDoneQuestStrength(xSetting.GetQuestModulus());
        }
        break;
    case SQuest::Type_CountryLeft:      // 天行任务
        {
            nRewardModulus += IsCountryQuestOpen( CountryDefine::QuestType_CouncilorLeft );
        }
        break;
    case SQuest::Type_CountryRight:     // 探宝任务
        {
            nRewardModulus += IsCountryQuestOpen( CountryDefine::QuestType_CouncilorRight );
        }
        break;
    case SQuest::Type_Guild:            // 帮派任务
        {
            nRewardModulus = CalcGuildQuestReleaseRewardModulus( stQuestId );
        }
        break;
    default:
        break;
    }

    //有部分奖励类型没有实现
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
                //只奖励是性别和职业相同的道具
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
				//当前任务奖励国家金钱
				int RewardValue = r->Value * nRewardModulus;
				//添加国家金钱
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

    // 额外的经验奖励
    DoneQuestRewardExp( pQuest, nRewardModulus );           

    //更新任务记数
    UpdatePlayerCounterByCount(TitleConfig::Condition_Quest, stQuestId);

    MsgDoneQuest msg;
    msg.playerId = GetID();
    msg.nQuestId = stQuestId;
    GettheServer().SendMsgToSingle( &msg, this );

	//LYH日志添加
	if(!theLogEventService.LogQuest(GetAccountID(),GetDBCharacterID(),pQuest->Id,GetCharName()))
	{
		Log( theXmlString.GetString(eServerLog_QuestOK), pQuest->Id );
	}
    return true;
}

void GamePlayer::DoneQuestRewardExp(SQuest* pQuest, int nRewardModulus /* = 1 */)
{
	//暂时去掉,策划没有额外经验奖励的需求,如果后续需要的话可以再根据逻辑加回去,by vvx 2012.10.19
	return;
    if ( pQuest == NULL )
    { return; }

    short QuestId = pQuest->Id;
    float RewardValue = 0.0f;

    if (QuestId == 5200)
    {    // 日理万机
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
    {   // 一己之力，填充国库
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
        // 驻守边疆
        RewardValue = GetLevel() * 2000;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId >= 5350 && QuestId <= 5354 )
    {    // 异国锄奸
        RewardValue = GetLevel() * 1100;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId >= 5355 && QuestId <= 5359 )
    {   // 异国刺杀
        RewardValue = GetLevel() * 1100;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId >= 5360 && QuestId <= 5364 )
    {    // 异国情报
        RewardValue = GetLevel() * 1100;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId >= 5365 && QuestId <= 5369 )
    {   // 异国夺旗
        RewardValue = GetLevel() * 1100;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId >= 5481 && QuestId <= 5490 )
    {   // 兴国之路
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
    {    // 物竞天择
        RewardValue = GetLevel() * 2250;
        RewardValue = floor(RewardValue);

    }
    else if ( QuestId == 5471 )
    {   // 铁人三项
        RewardValue = (GetLevel() - 40) * 1200 + 11250;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId >= 5511 && QuestId <= 5515 )
    {   // 意气相投
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
    {   // 洪福天降
        RewardValue = GetLevel() * 4500;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId >= 5531 && QuestId <= 5575 )
    {    // 帮会内政
        RewardValue = GetLevel() * 200 + GetVar(200) * GetLevel() * 50;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId == 5581 )
    {   // 帮会黑木
        RewardValue = 112500 + (GetLevel() - 40) * 12000;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId >= 5585 && QuestId <= 5586 )
    {   // 帮会护送
        RewardValue = GetLevel() * 6000;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId >= 5122 && QuestId <= 5125 )
    {  // 官府押运
        RewardValue = GetLevel() * 5000;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId == 5091 )
    {   // 云游四海
        RewardValue = GetLevel() * 3000;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId == 5580 )
    {   // 帮会募集卷
        RewardValue = GetLevel() * 20000;
        RewardValue = floor(RewardValue);
    }
    else if ( QuestId >= 5701 && QuestId <= 5720 )
    {   // 绿林任务（20级绿林）
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
    {   // 绿林任务（30级绿林）
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
    {   // 绿林任务（40级绿林）
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
    {   // 绿林任务（50级绿林）
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
    { // 灵兽喂养
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
        // 结束就跳出
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
        // 结束就跳出
        if ( gCharInfoServer.otherdata.vars.questTime[ i ].id != 0)
        { continue; }

        gCharInfoServer.otherdata.vars.questTime[ i ].id   = questId;
        gCharInfoServer.otherdata.vars.questTime[ i ].time = time;
        return true;
    }

    return false;
}