#include "RelationManager.h"
#include "GameServerManager.h"
#include "XmlStringLanguage.h"
#include "CountryManager.h"
#include "RelationMessage.h"
#include "MySqlCommunication.h"

template<>  // 发送添加好友消息
void CenterRelation::ProcessAddRelation( RelationDataToServer& xData, unsigned char uchOperate  ,RelationDataToServer& xOldRelation)
{
    if ( uchOperate == RelationDefine::NotSendToClient )
    { return; }
 
    // 发消息给所有GameServer
    SendAddRelationToClient( xData );

    // 发消息给Database
    if ( xData.GetRelation() == RelationDefine::TempFriend )
    { return; }     // 临时好友不执行数据库操作

    SendAddRelationToDatabase( xData );

    // 处理添加高级关系逻辑
    ProcessAddHigherRelathion( xData );
}
template<>
void CenterRelation:: SendRelationMessage(Msg* pMsg)
{
	
}
template<>
void CenterRelation::ProcessAddHigherRelathion( RelationDataToServer& xData )
{
    switch ( xData.GetHigherRelation() )
    {
    case RelationDefine::Teacher:
        break;
    case RelationDefine::Student:
        UpdateRelationAttribute( RelationDefine::UpdateLastStudentTime, TimeEx::GetNowTime() );
        break;
    case RelationDefine::Marriage:
        {
            // 如果自己是国王, 且为男性, 
            CenterCountry* pCountry = theCenterCountryManager.GetCountry( GetCountry() );
            if ( pCountry != NULL && pCountry->GetPosition( GetID() ) == CountryDefine::Position_King /*&& GetSex() == Sex_Male*/ )
            {
				CenterRelation* pRelation = theCenterRelationManager.GetPlayerRelation( xData.GetID() );
                if ( pRelation != NULL )
                {
					//判断王后是否有官职
					if(pCountry->GetRight(pRelation->GetID()) != CountryDefine::Right_None)
					{
						for(int i =CountryDefine::Position_None;i<CountryDefine::Position_Max;++i)
						{
							if(pCountry->GetOfficial(i) && pCountry->GetOfficial(i)->GetID() == pRelation->GetID())
							{
								pCountry->ProcessCountryOfficialChange(i,CountryDefine::NoneID, "",0,0,0,0);
								break;
							}
						}
						 
					}
                    pCountry->ProcessCountryOfficialChange( CountryDefine::Position_Queen, pRelation->GetID(), pRelation->GetName(),-1,-1,-1,-1);
					/*CS2GSAddCountryOfficial msg;
					msg.uchCountryID = GetCountry();
					msg.uchPosition  = CountryDefine::Position_Queen;
					msg.nPlayerID    = pRelation->GetID();
					theGameServerManager.SendMessageToGameServers( &msg );*/
                }
            }
        }
        break;
    default:
        return;
    }
}

template<>      // 发送删除好友消息
void CenterRelation::ProcessRemoveRelation( unsigned int nPlayerID, unsigned short stRelation )
{
    // 发消息给GameServer
    SendRemoveRelationToClient( nPlayerID, stRelation );

    // 如果是2级关系
    ProcessRemoveHigherRelation( nPlayerID, stRelation );

    if ( stRelation == RelationDefine::TempFriend )
    { return; } // 临时好友不执行数据库操作

    // 更新到Database
    RelationDataToServer* pData = GetRelationData( nPlayerID );

    // 更新数据库关系
    SendUpdateRelationToDatabase( nPlayerID, RelationDefine::UpdateRelation, ( pData == NULL ? RelationDefine::InitRelation : pData->GetRelation() ) );
}

template<>
unsigned short CenterRelation::CheckCanAddStudent( unsigned int dwPlayerID )
{
    const MasterInfo* pInfo = theRelationConfig.GetMasterInfo( GetMasterLevel() );
    if ( pInfo == NULL )
    { return RelationDefine::CanNotReceivePrentice; }

    // 徒弟数量已经满了
    if ( GetStudentCount() >= pInfo->GetRecruitCount() )
    { return RelationDefine::StudentCountLimit; }

    const PrenticeLimit& xPrenticeLimit = theRelationConfig.GetPrenticeLimit();
    if ( !TimeEx::IsPassCurrentTime( GetLastAddStudentTime(), xPrenticeLimit.GetTeacherTimeSpan() * OneHourSecond ) )
    { return RelationDefine::AddStudentTimeLimit; }

    return RelationDefine::CanAddRelation;
}

template<>
unsigned short CenterRelation::CheckCanAddTeacher( unsigned int dwPlayerID )
{
    if ( IsHaveTeacher() )
    { return RelationDefine::AlreadyHaveTeacher; }

    const PrenticeLimit& xPrenticeLimit = theRelationConfig.GetPrenticeLimit();
    if ( !TimeEx::IsPassCurrentTime( GetLastAddTeacherTime(), xPrenticeLimit.GetStudentTimeSpan() * OneHourSecond ) )
    { return RelationDefine::AddTeacherTimeLimit; }

    return RelationDefine::CanAddRelation;
}

template<>
bool CenterRelation::CheckBrotherCount()
{
    return true;
}

template<>
void CenterRelation::SendAddFriendlyTimeList()
{
    if ( RecordTime::CheckRecordTime( m_dwAddFriendlyTime ) )
    {
        m_setAddFriendly.clear();
        RecordTime::SaveRecordTime( m_dwAddFriendlyTime );
    }

    if ( m_setAddFriendly.empty() )
    { return; }

    CS2GSMsgAddFriendlyTimeList xList;
    xList.dwSelfID = GetID();
    for ( AddFriendlyTimeIter iter = m_setAddFriendly.begin(); iter != m_setAddFriendly.end(); ++iter )
    {
        xList.AddPlayerID( *iter );
    }

    theGameServerManager.SendMessageToGameServers( &xList );
}

template<>  // 
void CenterRelation::SendReceiveQuestTimeList()
{
    if ( RecordTime::CheckRecordTime( m_dwReceiveQuestTime ) )
    {
        m_setReceiveQuest.clear();
        RecordTime::SaveRecordTime( m_dwReceiveQuestTime );
    }

    if ( m_setReceiveQuest.empty() )
    { return; }

    CS2GSMsgReceiveQuestTimeList xList;
    xList.dwSelfID = GetID();
    for ( AddFriendlyTimeIter iter = m_setReceiveQuest.begin(); iter != m_setReceiveQuest.end(); ++iter )
    {
        xList.AddPlayerID( *iter );
    }

    theGameServerManager.SendMessageToGameServers( &xList );
}

template<>  // 更新好友度给服务器
void CenterRelation::SendAddFriendlyTimeMessage( unsigned int dwPlayerID, bool bClear )
{
    GS2CSUpdateAddFriendlyTime xUpdate;
    xUpdate.dwSelfID   = GetID();
    xUpdate.dwPlayerID = dwPlayerID;
    xUpdate.bClear     = bClear;

    theGameServerManager.SendMessageToGameServers( &xUpdate );
}

template<>
void CenterRelation::SendReceiveQuestTimeMessage( unsigned int dwPlayerID, bool bClear )
{
    GS2CSUpdateReceiveQuestTime xUpdate;
    xUpdate.dwSelfID = GetID();
    xUpdate.dwPlayerID = dwPlayerID;
    xUpdate.bClear = bClear;

    theGameServerManager.SendMessageToGameServers( &xUpdate );
}

template<>
void CenterRelation::SendUpdateAttributeMessage( unsigned char uchType, __int64 n64Value )
{
    // 发送给Database, 保存入库
    CS2DBUpdateAttributeReq xReq;
    xReq.nPlayerID           = GetID();
    xReq.uchType             = uchType;
    xReq.xAttribute.n64Value = n64Value;
    theMysqlCommunication.PushReqMessage( &xReq, 0 );

    // 发送给GameServer
    CS2GSUpdateRelationAttribute xUpdate;
    xUpdate.nPlayerID           = GetID();
    xUpdate.uchType             = uchType;
    xUpdate.xAttribute.n64Value = n64Value;
    theGameServerManager.SendMessageToGameServers( &xUpdate );
}

template<>
void CenterRelation::SendUpdateAttributeMessage( unsigned char uchType, const char* szValue )
{
    switch ( uchType )
    {
    case RelationDefine::UpdateName:
        theCenterRelationManager.AddPlayerNameID( this );
        break;
    default:
        break;
    }

    // 发送给Database, 保存入库
    CS2DBUpdateAttributeReq xReq;
    xReq.nPlayerID = GetID();
    xReq.uchType   = uchType;
    HelperFunc::SafeNCpy( xReq.xAttribute.szValue, szValue, sizeof( xReq.xAttribute.szValue ) );
    theMysqlCommunication.PushReqMessage( &xReq, 0 );


    // 发送给GameServer
    CS2GSUpdateRelationAttribute xUpdate;
    xUpdate.nPlayerID = GetID();
    xUpdate.uchType   = uchType;
    HelperFunc::SafeNCpy( xUpdate.xAttribute.szValue, szValue, sizeof( xUpdate.xAttribute.szValue ) );
    theGameServerManager.SendMessageToGameServers( &xUpdate );
}

template<>
void CenterRelation::SendUpdatePersonalInfo( const PersonalInfo& xValue )
{
	// sendtoDB
	CS2DBUpdatePersonalInfoReq xReq;
	xReq.nPlayerID = GetID();
	xReq.xPersonalInfo.SetInfo( xValue );
	theMysqlCommunication.PushReqMessage( &xReq, 0 );

	// SendToGS
	CS2GSUpdatePersonalInfo xUpdate;
	xUpdate.nPlayerID = GetID();
	xUpdate.xPersonalInfo.SetInfo( xValue );
	theGameServerManager.SendMessageToGameServers( &xUpdate );
}

template<>
void CenterRelation::SendUpdateRelationDataMessage( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue )
{
    SendUpdateRelationToDatabase( nPlayerID, uchType, nValue );

    // 同步给GameServer
    CS2GSUpdateRelationData xUpdate;
    xUpdate.nPlayerID    = GetID();
    xUpdate.nTargetID    = nPlayerID;
    xUpdate.uchType      = uchType;
    xUpdate.xData.nValue = nValue;
    theGameServerManager.SendMessageToGameServers( &xUpdate );
}

template<>
void CenterRelation::SendUpdateRelationDataMessage( unsigned int nPlayerID, unsigned char uchType, const char* szValue )
{
    // 保存数据库
    SendUpdateRelationToDatabase( nPlayerID, uchType, szValue );

    // 同步给GameServer
    CS2GSUpdateRelationData xUpdate;
    xUpdate.nPlayerID = GetID();
    xUpdate.nTargetID = nPlayerID;
    xUpdate.uchType   = uchType;
    HelperFunc::SafeNCpy( xUpdate.xData.szValue, szValue, sizeof( xUpdate.xData.szValue ) );
    theGameServerManager.SendMessageToGameServers( &xUpdate );
}

template<>  // 添加关系到数据库
void CenterRelation::SendAddRelationToDatabase( RelationDataToServer& xData )
{
    CS2DBAddRelationReq xReq;
    xReq.nPlayerID = GetID();
    xReq.xData     = xData;
    theMysqlCommunication.PushReqMessage( &xReq, 0 );
}

template<>  // 发送添加好友关系到GameServer
void CenterRelation::SendAddRelationToClient( RelationDataToServer& xData )
{
    CS2GSAddRelationResult xResult;
    xResult.nReqID = GetID();
    xResult.xData = xData;
    theGameServerManager.SendMessageToGameServers( &xResult );
}

template<>  // 更新关系到数据库
void CenterRelation::SendUpdateRelationToDatabase( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue )
{
    // 保存数据库
    CS2DBUpdateRelationDataReq xReq;
    xReq.nPlayerID    = GetID();
    xReq.nTargetID    = nPlayerID;
    xReq.uchType      = uchType;
    xReq.xData.nValue = nValue;
    theMysqlCommunication.PushReqMessage( &xReq, 0 );
}

template<>  // 更新关系到数据库
void CenterRelation::SendUpdateRelationToDatabase( unsigned int nPlayerID, unsigned char uchType, const char* szValue )
{
    // 保存数据库
    CS2DBUpdateRelationDataReq xReq;
    xReq.nPlayerID = GetID();
    xReq.nTargetID = nPlayerID;
    xReq.uchType   = uchType;
    HelperFunc::SafeNCpy( xReq.xData.szValue, szValue, sizeof( xReq.xData.szValue ) );
    theMysqlCommunication.PushReqMessage( &xReq, 0 );
}

template<>  // 添加属性到数据库
void CenterRelation::SendAddAttributeToDatabase()
{
    CS2DBAddAttributeReq xReq;
    xReq.xAttribute = *this;
    theMysqlCommunication.PushReqMessage( &xReq, 0 );
}

template<>
void CenterRelation::SendRemoveRelationToClient( unsigned int nPlayerID, unsigned short stRelation )
{
    //更新给GameServer
    CS2GSRemoveRelationAck xAck;
    xAck.nReqID     = GetID();
    xAck.nAckID     = nPlayerID;
    xAck.stRelation = stRelation;
    theGameServerManager.SendMessageToGameServers( &xAck );
}

template<>
void CenterRelation::ProcessRemoveHigherRelation( unsigned int nPlayerID, unsigned short stRelation )
{
    int nStringID = 0;
    switch ( stRelation )
    {
    case RelationDefine::Marriage:
        {
            nStringID = eText_MailRemoveMarriage;

            // 如果是国王
            CenterCountry* pCountry = theCenterCountryManager.GetCountry( GetCountry() );
            if ( pCountry != NULL && pCountry->GetPosition( nPlayerID ) == CountryDefine::Position_Queen )
            {
                pCountry->ProcessCountryOfficialChange( CountryDefine::Position_Queen, CountryDefine::NoneID, "" ,0,0,0,0);
            }
        }
        break;
    case RelationDefine::Teacher:
        {
            nStringID = eText_MailRemoveTeacher;
            UpdateRelationAttribute( RelationDefine::UpdateLastTeacherTime, TimeEx::GetNowTime() ); // 设置下次拜师时间限制
        }
        break;
    case RelationDefine::Student:
        nStringID = eText_MailRemoveStudent;
        break;
    default:
        return;
    }

    if ( GetOnLine() )
    { return; }     // 在线就不发送邮件通知

    // 获得对方的信息
    CenterRelation* pRelaiton = theCenterRelationManager.GetPlayerRelation( nPlayerID );
    if ( pRelaiton == NULL )
    { return; }

    //GS2CSSendMailReq xReq;
    //xReq.charDbId = RelationDefine::InitID;

    //xReq.mail.type  = SMail::EMT_System;
    //xReq.mail.state = SMail::EMS_NotOpen;
    //xReq.mail.sendTime = TimeEx::GetNowTime();        

    //// 发信人
    //xReq.mail.owners[EM_FromIndex].charDbId = RelationDefine::InitID;
    //sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );

    //// 收件人
    //xReq.mail.owners[EM_ToIndex].charDbId = GetID();
    //HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName, GetName(), sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );

    //sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1,theXmlString.GetString( eText_MailSystemTitle ) );
    //sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1, theXmlString.GetString( nStringID ), pRelaiton->GetName() );
    //theMailSystemManager.OnGS2CSSendMailReq( &xReq, 0 );
}

template<>
void CenterRelation::SendRelationListToClient( unsigned int nAppointID )
{
    CS2GSRelationList xList;
    xList.xAttribute = *this;

    // 保证好友关系不会超过最大值
    for ( RelationMapIter iter = m_mapRelation.begin(); iter != m_mapRelation.end(); ++iter )
    {
        xList.AddRelationData( iter->second );
    }

    if ( nAppointID == RelationDefine::InitID )
    {
        theGameServerManager.SendMessageToGameServers( &xList );
    }
    else
    {
        GameServerPeer* pGameServer = theGameServerManager.GetGameServerPeer( nAppointID );
        if ( pGameServer != NULL )
        {
            pGameServer->Send( &xList );
        }
    }
}

template<>
void CenterRelation::ProcessPreDataLogin()
{
	if ( !GetOnLine() )//还没 上线标记时 才发送...否则的话说明已经发送过了
	{
		// 1先把自己的发过去
		if ( !theCenterRelationManager.HaveSendedRelationId( GetID() ) )
		{
			SendRelationListToClient(RelationDefine::InitID);
			theCenterRelationManager.AddSendedRelationId(GetID());
		}

		// 2再把和自己关联的发过去
		CenterRelation* pRelation = NULL;
		for ( RelationMapIter iter = m_mapRelation.begin(); iter != m_mapRelation.end(); ++iter )
		{
			if (theCenterRelationManager.HaveSendedRelationId( iter->first ))
				continue;

			pRelation = theCenterRelationManager.GetPlayerRelation( iter->first );
			if (pRelation )
			{
				pRelation->SendRelationListToClient(RelationDefine::InitID);
				theCenterRelationManager.AddSendedRelationId(pRelation->GetID());
			}
		}
	}
}

template<>
void CenterRelation::ProcessEnterWorld()
{
    SendOnLineMessage();    // 通知上线

    SendAddFriendlyTimeList();
    SendReceiveQuestTimeList();
}
template<>
void CenterRelation::ProcessExitWorld()
{
    SendOutLineMessage();
}

template<>      // 通知某玩家上线了
void CenterRelation::SendOnLineMessage()
{
    SetOnLine( true );      // 设置在线状态

    CS2GSRelationOnLine xOnline;
    xOnline.nPlayerID = GetID();
    theGameServerManager.SendMessageToGameServers( &xOnline );
}


template<>  // 通知玩家下线了
void CenterRelation::SendOutLineMessage()
{
    SetOnLine( false );      // 设置不在线状态

    CS2GSRelationOutLine xOutLine;
    xOutLine.nPlayerID = GetID();
    theGameServerManager.SendMessageToGameServers( &xOutLine );
}

template<>      // 检查仇人数量, 达到最大值时 删除一个
bool CenterRelation::CheckVendettaRelationCount()
{
    if ( GetRelationCount( RelationDefine::Vendetta ) < theRelationConfig.GetMaxVendettaCount() )
    { return true; }

    for ( RelationMapIter iter = m_mapRelation.begin(); iter != m_mapRelation.end(); ++iter )
    {
        if ( !iter->second.HaveRelation( RelationDefine::Vendetta ) )
        { continue; }

        if ( iter->second.GetLocked() )
        { continue; }

        return RemoveRelation( iter->second.GetID(), RelationDefine::Vendetta );
    }
    
    return false;;
}

template<>      // 直接发送查询结果给客户端
void CenterRelation::SendQueryAttributeResultToClient( unsigned int* pAttributeID, int nCount )
{
    MsgQueryAttributeResult xResult;

    for ( int i = 0; i < nCount; ++i )
    {
        CenterRelation* pRelation = theCenterRelationManager.GetPlayerRelation( pAttributeID[i] );
        if ( pRelation == NULL || !pRelation->GetOnLine() )
        { continue; }   // 在线的才发送给客户端

        xResult.AddAttribute( *pRelation );
    }

    theGameServerManager.SendMsgToSingleRemote( RelationDefine::InitID, &xResult, GetID() );
}

template<>
void CenterRelation::ProcessStudentLevelUp( unsigned int nPlayerID, int nLevel )
{
    if ( !IsHaveTeacher() )
    { return; }

    unsigned int nRewardExp = theRelationConfig.GetReportInfo().GetExpValue() * nLevel;
    unsigned int nRewardMasterValue = theRelationConfig.GetReportInfo().GetMasterValue() * nLevel;
    unsigned int nModulusValue = theRelationConfig.GetReportInfo().GetModulusValue();

    // 师傅的属性
    CenterRelation* pRelation = theCenterRelationManager.GetPlayerRelation( GetTeacherID() );
    if ( pRelation == NULL )
    { return; }

    if ( pRelation->GetOnLine() )   // 在线
    {
        CS2GSStudentLevelUp xLevelUp;
        xLevelUp.nPlayerID  = pRelation->GetID();
        xLevelUp.nStudentID = GetID();
        xLevelUp.bIsStudent = true;
        xLevelUp.nRewardExp = nRewardExp;
        xLevelUp.nRewardMasterValue = nRewardMasterValue;
        theGameServerManager.SendMessageToGameServers( &xLevelUp );
    }
    else    // 不在线
    {
        pRelation->UpdateRelationAttribute( RelationDefine::UpdateRewardExp, pRelation->GetRewardExp() + nRewardExp );
        pRelation->UpdateRelationAttribute( RelationDefine::UpdateRewardPrestige, pRelation->GetRewardPrestige() + nRewardMasterValue );
    }

    // 师傅的师傅的属性
    CenterRelation* pTeacherRelation = theCenterRelationManager.GetPlayerRelation( pRelation->GetTeacherID() );
    if ( pTeacherRelation == NULL )
    { return; }

    nRewardExp = nRewardExp * nModulusValue / 100;
    nRewardMasterValue = nRewardMasterValue * nRewardMasterValue / 100;

    if ( pTeacherRelation->GetOnLine() )   // 在线
    {
        CS2GSStudentLevelUp xLevelUp;
        xLevelUp.nPlayerID  = pTeacherRelation->GetID();
        xLevelUp.nStudentID = pRelation->GetID();
        xLevelUp.bIsStudent = false;
        xLevelUp.nRewardExp = nRewardExp;
        xLevelUp.nRewardMasterValue = nRewardMasterValue;
        theGameServerManager.SendMessageToGameServers( &xLevelUp );
    }
    else    // 不在线
    {
        pTeacherRelation->UpdateRelationAttribute( RelationDefine::UpdateRewardExp, pTeacherRelation->GetRewardExp() + nRewardExp );
        pTeacherRelation->UpdateRelationAttribute( RelationDefine::UpdateRewardPrestige, pTeacherRelation->GetRewardPrestige() + nRewardMasterValue );
    }
}

template<>
void CenterRelation::SendRelationGroupNameChangeMessage( unsigned char uchGroupID, const char* szValue )
{
    // 更新到数据库
    CS2DBUpdateRelationGroup xUpdate;
    xUpdate.nPlayerID  = GetID();
    xUpdate.uchGroupID = uchGroupID;
    HelperFunc::SafeNCpy( xUpdate.szGroup, szValue, sizeof( xUpdate.szGroup ) );
    theMysqlCommunication.PushReqMessage( &xUpdate, 0 );


    // 同步给GameServer
    CS2GSRelationGroupNameChange xChange;
    xChange.nPlayerID  = GetID();
    xChange.uchGroupID = uchGroupID;
    HelperFunc::SafeNCpy( xChange.szName, szValue, sizeof( xChange.szName ) );
    theGameServerManager.SendMessageToGameServers( &xChange );
}
