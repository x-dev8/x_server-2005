#include "Country.h"
#include "CountryManager.h"
#include "TimeEx.h"
#include "GlobalFunction.h"
#include "GameServerManager.h"
#include "CountryMessage.h"
#include "MySqlCommunication.h"
#include "CountryConfig.h"
#include "RelationManager.h"
#include "GuildManager.h"
#include "CountryReward.h"

template<>
void CenterCountry::InitCountryInfo()
{
    RecordTime::SaveRecordTime( nRecordTime );      // ��ʼ��ʱ��

    // ��ʼ���߾�ս����¼
    int nSize = theCountryConfig.GetBordersFightCount();
	// zhuxincong 9.22 ��ʼ���ﹱ
	int nTribute = theCountryConfig.GetFitstTribute();
    if ( nSize <= 0 )
    { nSize = CountryDefine::MaxBordersFightCount; }

    vecBordersFight.resize( nSize );
}

template<>
void CenterCountry::RunUpdate( unsigned int nCurrentTime )
{
    // �������
    if ( RecordTime::CheckRecordTime( nRecordTime ) )
    {
        // ���ڲ�ͬ��, 
        RecordTime::SaveRecordTime( nRecordTime );

        // ��ձ���
        ClearAllOperateTime();
        StartSaveTimer( nCurrentTime );

        // ����Ϣ֪ͨGameServer
        CS2GSCountryDateChangeed xChangeed;
        xChangeed.uchCountryID = GetID();
        theGameServerManager.SendMessageToGameServers( &xChangeed );
    }

    //  ��鼸���������񷢲�ʱ��
    for ( int i = CountryDefine::QuestType_None + 1; i < CountryDefine::QuestType_Max; ++i )
    {
        if ( xOperate[ i ].GetStartTime() != 0 )
        {
            const CountryConfig::QuestSetting* pSetting = theCountryConfig.GetQuestSetting( i );
            if ( pSetting == NULL )
            { continue; }

            TimeEx xStartTime( xOperate[ i ].GetStartTime() );
            DWORD dwSpanTime = pSetting->GetKeepTime();
            TimeSpan xSpan( dwSpanTime );
            xStartTime += xSpan;

            if ( TimeEx::IsPassCurrentTime( xStartTime.GetTime() ) )
            {
                CS2GSCountryQuestStatusStop xStop;
                xStop.uchCountryID = GetID();
                xStop.uchQuestType = i;
                theGameServerManager.SendMessageToGameServers( &xStop );

                xOperate[ i ].SetStartTime( 0 );
            }
            StartSaveTimer( nCurrentTime );
        }
    }

    // ÿ������һ�ι���ʵ��
   // ProcessCalcCountryStrength( nCurrentTime );

    // �ж��Ƿ�Ҫ����
    if ( m_xSaveTimer.DoneTimer() )
    { SaveToDatabase(); }
}

template<>
void CenterCountry::SaveToDatabase()
{
    CS2DBCountryDataSaveReq xReq;
    xReq.xData = *this;
    theMysqlCommunication.PushReqMessage( &xReq, 0 );
}

template<>
void CenterCountry::SendNoticeChangeMessage( unsigned int nPlayerID )
{
    StartSaveTimer( HQ_TimeGetTime() );

    // ��Ϣͬ�������з�����
    CS2GSCountryNoticeChangeAck xAck;
    xAck.uchCountryID = GetID();
    xAck.nPlayerID    = nPlayerID;
    strncpy_s( xAck.szNotice, sizeof( xAck.szNotice ), GetNotice(), sizeof( xAck.szNotice ) - 1 ); 
    theGameServerManager.SendMessageToGameServers( &xAck );
}
template<>
void CenterCountry::SendCountryInfoChangeMessage(const char * szInfo,__int64 Time,int Value)
{
	//ֱ�ӷ�������浽���ݿ�ȥ
	CS2DBRequestCountryInfoReq msgDB;
	msgDB.CountryID = GetID();
	msgDB.Value = Value;
	strncpy_s( msgDB.Info, sizeof( msgDB.Info )-1, szInfo, sizeof( msgDB.Info ) - 1 ); 
	msgDB.Time = Time;
	theMysqlCommunication.PushReqMessage( &msgDB, 0 );
	//ͬ�������е�GameServer
	CS2GSAddCountryInfoAck msg;
	msg.uchCountryID = GetID();
	strncpy_s( msg.szNotice, sizeof( msg.szNotice )-1, szInfo, sizeof( msg.szNotice ) - 1 ); 
	msg.Time = Time;
	msg.Value = Value;
	theGameServerManager.SendMessageToGameServers( &msg );
}
template<>
void CenterCountry::ProcessCalcCountryStrength( unsigned int nCurrentTime )
{
    /*static SYSTEMTIME xDate;
    ::GetLocalTime( &xDate );

    if ( xDate.wMinute == 0 && xDate.wHour == 0 && xDate.wDayOfWeek == 1 )
    { m_xStrengthTimer.StartTimer( nCurrentTime, 65000 ); }

    if ( m_xStrengthTimer.DoneTimer() )
    {
        SendUpdateCountryDataMessage( CountryDefine::UpdateLastStrength, GetNowStrength() );
        SendUpdateCountryDataMessage( CountryDefine::UpdateNowStrength, 0 );
    }*/
	//�������� �ͱ��ܵ�ʵ�� ���ҷ�����Ϣ
	UpdateCountryData(CountryDefine::UpdateLastStrength,GetNowStrength());
	//��ȡ���ұ��ܵ�ʵ��
	//1.���һЩ��Ҫÿ�����������
	nDoneQuestStrength = 0;
	for(int i =CountryDefine::QuestType_None;i<CountryDefine::QuestType_Max;++i)
	{
		nQuestSum[i] = 0;
	}
	//2.���ҹ�Ʒ���������ָ�����
	UpdateCountryData( CountryDefine::UpdateTribute, InitTribute );

	//UpdateCountryData(CountryDefine::UpdateNowStrength, 0);
    //SendUpdateCountryDataMessage( CountryDefine::UpdateNowStrength, 0 );
}

template<>
void CenterCountry::SendUpdateCountryDataMessage( unsigned char uchType, __int64 n64Value )
{
    switch ( uchType )
    {
    case CountryDefine::CancelKingGuild:    // ������й��ҹ�Ա
        SetKingGuild( CountryDefine::NoneID );
        ClearOfficial();
        break;
    case CountryDefine::CancelRosefinchGuild:
        SetDragonGuild( CountryDefine::NoneID );
        break;
    case CountryDefine::CancelDragonGuild:
        SetRosefinchGuild( CountryDefine::NoneID );
        break;
    default:
        break;
    }

    StartSaveTimer( HQ_TimeGetTime() );

    CS2GSCountryDataUpdate xUpdate;
    xUpdate.uchCountryID  = GetID();
    xUpdate.uchUpdateType = uchType;
    xUpdate.n64Value      = n64Value;
    theGameServerManager.SendMessageToGameServers( &xUpdate );
}

template<>
void CenterCountry::ProcessCountryOfficialChange( unsigned char uchPosition, unsigned int nPlayerID, const char* szName,uint8 sexID,uint16 faceID,uint16 headerID,uint16 professionID,SCharItem* pItem )
{
    // ����ְλ
	if((sexID == 0xFF || faceID ==0xFFFF || headerID == 0xFFFF || professionID == 0xFFFF) && nPlayerID != 0)
	{
		//��ǰ��Ա�������ȱʧ �����ݿ������ȡ
		CS2DBCountryOfficeReq msg;
		msg.nPlayerID = nPlayerID;
		msg.countryID = GetID();
		msg.uchPosition = uchPosition;
		HelperFunc::SafeNCpy( msg.szName, szName, sizeof( msg.szName ) );
		theMysqlCommunication.PushReqMessage( &msg, 0 );
		return;
	}
	
	//�ж�ְλ�Ƿ�Ϊͬһ��
	bool IsOnePlayer = ((nPlayerID == GetOfficial(uchPosition)->GetID()) && nPlayerID != CountryDefine::ErrorID);

	StartSaveTimer( HQ_TimeGetTime() );
    AppointOfficial( uchPosition, nPlayerID, szName,sexID,faceID,headerID,professionID);
	
	CS2GSCountryOfficialChange xChange;
    xChange.uchCountryID = GetID();
    xChange.uchPosition  = uchPosition;
    xChange.nPlayerID    = nPlayerID;
	xChange.sexID = sexID;
	xChange.faceID = faceID;
	xChange.headerID = headerID;
	xChange.professionID = professionID;
    HelperFunc::SafeNCpy( xChange.szName, szName, sizeof( xChange.szName ) );
    theGameServerManager.SendMessageToGameServers( &xChange );

    switch ( uchPosition )
    {
    case CountryDefine::Position_King:      // ����ǹ���
        {
			

            int nMarriageID = RelationDefine::InitID;
            char szMarriageName[ RelationDefine::MaxNameLength ] = { 0 };

            // �ж��Ƿ�������
            CenterRelation* pRelation = theCenterRelationManager.GetPlayerRelation( nPlayerID );
            if ( pRelation != NULL && pRelation->GetMarriageID() != RelationDefine::InitID )
            {
                CenterRelation* pMarriageRelaion = theCenterRelationManager.GetPlayerRelation(  pRelation->GetMarriageID() );
				//����Ϊ���� ���ǲ�һ��ΪŮ��	
                //if ( pMarriageRelaion != NULL && pMarriageRelaion->GetSex() == Sex_Female )
				if ( pMarriageRelaion != NULL)
                {
                    nMarriageID = pMarriageRelaion->GetID();
                    HelperFunc::SafeNCpy( szMarriageName, pMarriageRelaion->GetName(), sizeof( szMarriageName ) );
					//�������GameServer  ֪ͨ�������ûʺ������
					/*CS2GSAddCountryOfficial msg;
					msg.uchCountryID = GetID();
					msg.uchPosition  = CountryDefine::Position_Queen;
					msg.nPlayerID    = nMarriageID;
					theGameServerManager.SendMessageToGameServers( &msg );*/
                }
            }
			if(!IsOnePlayer)
			{
				CS2GSCountryOfficialReward cenmsg;
				cenmsg.nPlayerID = nPlayerID;
				cenmsg.uchPosition = CountryDefine::Position_King;
				HelperFunc::SafeNCpy( cenmsg.szName, szMarriageName, sizeof( cenmsg.szName ) );
				theGameServerManager.SendMsgToSingleGameServers(&cenmsg);
			}
			if(nMarriageID != RelationDefine::InitID)
			{
				if(GetRight(nMarriageID) != CountryDefine::Right_None)
				{
					for(int i =CountryDefine::Position_None;i<CountryDefine::Position_Max;++i)
					{
						if(GetOfficial(i) && GetOfficial(i)->GetID() == nMarriageID)
						{
							ProcessCountryOfficialChange(i,CountryDefine::NoneID, "",0,0,0,0);
							break;
						}
					}
					 
				}
				ProcessCountryOfficialChange( CountryDefine::Position_Queen, nMarriageID, szMarriageName ,-1,-1,-1,-1);
			}
        }
    	break;
	case CountryDefine::Position_Queen:
		{
			if(!IsOnePlayer)
			{
				CS2GSCountryOfficialReward cenmsg;
				cenmsg.nPlayerID = nPlayerID;
				cenmsg.uchPosition = CountryDefine::Position_Queen;
				theGameServerManager.SendMsgToSingleGameServers(&cenmsg);
			}
		}
		break;
    default:
        break;
    }
}

template<>  // ������Ұ�����Ϣ�ı�
void CenterCountry::ProcessCountryGuildCancel( unsigned int nGuildID )
{
    // ������
    if ( GetKingGuild() == nGuildID )
    { 
        return UpdateCountryData( CountryDefine::CancelKingGuild, GuildDefine::InitID );
    }

    // ������
    if ( GetDragonGuild() == nGuildID )
    {
        return UpdateCountryData( CountryDefine::CancelDragonGuild, GuildDefine::InitID );
    }

    // ��ȸ��
    if ( GetRosefinchGuild() == nGuildID )
    {
        return UpdateCountryData( CountryDefine::CancelRosefinchGuild, GuildDefine::InitID );
    }  
}


template<>  
void CenterCountry::ProcessCountryBattleResult( unsigned char uchBattleType, unsigned char uchWinType, unsigned int nGuildID,unsigned int nLoseGuildID,SCharItem* pItem,unsigned int nCampBattle)
{
    // ͬ����������
    CS2GSCountryBattleResult xResult;
    xResult.uchCountryID  = GetID();
    xResult.uchBattleType = uchBattleType;
    xResult.uchWinType    = uchWinType;
    xResult.nGuildID      = nGuildID;
	xResult.nLoseGuildID  = nLoseGuildID;
	xResult.nCampBattle = nCampBattle;
    theGameServerManager.SendMessageToGameServers( &xResult );
    if ( uchWinType == CountryDefine::BattleWin_Guard )
    { return; }

    switch ( uchBattleType )
    {
    case CountryDefine::Battle_King:        // ����������ս
        {
            UpdateCountryData( CountryDefine::CancelKingGuild, GuildDefine::InitID );
            UpdateCountryData( CountryDefine::UpdateKingGuild, nGuildID );

            CenterGuild* pGuild = theCenterGuildManager.GetGuild( nGuildID );
            if ( pGuild == NULL )
            { return; }

            GuildMember* pMember = pGuild->GetMember( pGuild->GetMasterID() );
            if ( pMember == NULL )
            { return; }

            // ���¹�Ա
			//zhuxincong 
            //ProcessCountryOfficialChange( CountryDefine::Position_King, pMember->GetID(), pMember->GetName());
        }
        break;
    case CountryDefine::Battle_Dragon:      // ����������ս
        {
            UpdateCountryData( CountryDefine::CancelDragonGuild, GuildDefine::InitID );
            UpdateCountryData( CountryDefine::UpdateDragonGuild, nGuildID );
        }
        break;
    case CountryDefine::Battle_Rosefinch:   // ��ȸ������ս
        {
            UpdateCountryData( CountryDefine::CancelRosefinchGuild, GuildDefine::InitID );
            UpdateCountryData( CountryDefine::UpdateRosefinchGuild, nGuildID );
        }
        break;
    default:
        return;
    }
}


