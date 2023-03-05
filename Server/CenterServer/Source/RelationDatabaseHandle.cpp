#include "NormalLogicWorkThread.h"
#include "tstring.h"
#include "MySqlCommunication.h"

void NormalLogicWorkThread::OnQueryLoadRelationReq( BaseSqlMessage* pSqlMessage )
{
    LoadRelationAttribute( pSqlMessage );
    LoadRelationData( pSqlMessage );
}

void NormalLogicWorkThread::LoadRelationAttribute( BaseSqlMessage* pSqlMessage )
{
    char szSql[ 512 ] = { 0 };
    memset( szSql, 0,sizeof( szSql ) );
    uint32 result = ER_Success;
    sprintf_s( szSql, sizeof( szSql ) - 1, "select * from relationattribute;" );

    DB2CSRelationAttributeList xList;  

    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
        mysqlpp::StoreQueryResult res = mysqlQuery.store();
        if ( res && !res.empty() )
        {
            RelationAttributeToServer xAttribute;

            for (int i = 0; i < res.num_rows(); ++i )
            {
                xAttribute.SetID( res[i]["id"] );

                Common::_tstring strName;
                strName.fromUTF8( res[i]["name"] );
                xAttribute.SetName( strName.c_str() );

                xAttribute.SetHeadPic( res[i]["headpic"] );
                xAttribute.SetCountry( res[i]["country"] );
                xAttribute.SetProfession( res[i]["profession"] );
                xAttribute.SetSex( res[i]["sex"] );
                xAttribute.SetLevel( res[i]["level"] );
                xAttribute.SetGuildID( res[i]["guildid"] );
                xAttribute.SetPosition( res[i]["position"] );
				xAttribute.SetFamilyID( res[i]["familyid"]);
                xAttribute.SetMasterLevel( res[i]["masterlevel"] );
                xAttribute.SetTitleID( res[i]["titleid"] );
                xAttribute.SetMessageRefuse( res[i]["messagerefuse"] );
                xAttribute.SetRewardExp( res[i]["rewardexp"] );
                xAttribute.SetRewardPrestige( res[i]["rewardprestige"] );
                xAttribute.SetLastAddStudentTime( res[i]["lastaddstudenttime"] );
                xAttribute.SetLastAddTeacherTime( res[i]["lastaddteachertime"] );
                
                Common::_tstring strSignature;
                strSignature.fromUTF8( res[i]["signature"] );
                xAttribute.SetSignature( strSignature.c_str() );

                for ( int k = 0; k < RelationDefine::GroupCount; ++k )
                {
                    char szValue[30] = { 0 };
                    sprintf_s( szValue, sizeof( szValue ) - 1, "group%d", k + 1 );

                    Common::_tstring strGroup;
                    //TODO: CenterServer 偶尔会在此处 Dump 
                    std::string strBuff ( res[i][szValue] ) ;
                    strGroup.fromUTF8( strBuff.c_str() );
                    xAttribute.SetGroupName( k, strGroup.c_str() );
                }

				xAttribute.GetPersonalInfo().SetPersonalSex( res[i]["truesex"] );
				xAttribute.GetPersonalInfo().SetPersonalAge( res[i]["age"] );
				xAttribute.GetPersonalInfo().SetPersonalMonth( res[i]["birthmonth"] );
				xAttribute.GetPersonalInfo().SetPersonalDay( res[i]["birthday"] );
				xAttribute.GetPersonalInfo().SetStar( res[i]["star"] );
				xAttribute.GetPersonalInfo().SetShengXiao( res[i]["shengxiao"] );
				xAttribute.GetPersonalInfo().SetPersonalRight( res[i]["openright"] );

				Common::_tstring strValue;
				strValue.fromUTF8( res[i]["province"] );
				xAttribute.GetPersonalInfo().SetProvince( strValue.c_str() );
				strValue.fromUTF8( res[i]["city"] );
				xAttribute.GetPersonalInfo().SetCity( strValue.c_str() );
				strValue.fromUTF8( res[i]["trueprofession"] );
				xAttribute.GetPersonalInfo().SetProfession( strValue.c_str() );
				strValue.fromUTF8( res[i]["qq"] );
				xAttribute.GetPersonalInfo().SetQQ( strValue.c_str() );
				strValue.fromUTF8( res[i]["msn"] );
				xAttribute.GetPersonalInfo().SetMSN( strValue.c_str() );
				strValue.fromUTF8( res[i]["introduction"] );
				xAttribute.GetPersonalInfo().SetIntroduction( strValue.c_str() );

                xList.AddAttribute( xAttribute );
                if ( xList.IsFull() )
                {
                    theMysqlCommunication.PushAckMessage( &xList, pSqlMessage->nClientId );
                    xList.Reset();
                }
            }
        }
    TRYEND

    CHECK_SQL_RESULT( result ) // 执行检测

    theMysqlCommunication.PushAckMessage( &xList, pSqlMessage->nClientId ); 
}

void NormalLogicWorkThread::LoadRelationData( BaseSqlMessage* pSqlMessage )
{
    char szSql[ 512 ] = { 0 };
    memset( szSql, 0,sizeof( szSql ) );
    uint32 result = ER_Success;
    sprintf_s( szSql, sizeof( szSql ) - 1, "select * from relationdata;" );

    DB2CSRelationDataList xList;  

    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
        mysqlpp::StoreQueryResult res = mysqlQuery.store();
        if ( res && !res.empty() )
        {
            RelationDataToServer xData;
            unsigned int nPlayerID = 0;           
            for (int i = 0; i < res.num_rows(); ++i )
            {
                nPlayerID = res[i]["id1"];

                xData.SetID( res[i]["id2"] );
                xData.SetRelation( res[i]["relation"] );
                xData.SetFriendly( res[i]["friendly"] );
                xData.SetLocked( res[i]["locked"] );
                xData.SetGroupID( res[i]["groupid"] );

                Common::_tstring strRemark;
				if(strlen(res[i]["remark"]) > 0)
				{
					strRemark.fromUTF8( res[i]["remark"] );
				}
				
                xData.SetRemark( strRemark.c_str() );

                xList.AddRelationData( nPlayerID, xData );
                if ( xList.IsFull() )
                {
                    theMysqlCommunication.PushAckMessage( &xList, pSqlMessage->nClientId );
                    xList.Reset();
                }
            }
        }
    TRYEND

    CHECK_SQL_RESULT( result ) // 执行检测

    theMysqlCommunication.PushAckMessage( &xList, pSqlMessage->nClientId ); 
}

void NormalLogicWorkThread::OnAddRelationReq( BaseSqlMessage* pSqlMessage )
{
    CS2DBAddRelationReq *pReq = static_cast< CS2DBAddRelationReq* >( pSqlMessage->GetMessageAddress() );

	uint32 result = ER_Success;
	char szSql[ 512 ] = { 0 };
	//先删除在插入
	sprintf_s( szSql, sizeof( szSql ) - 1, "delete from relationdata where id1=%u and id2=%u;", pReq->nPlayerID, pReq->xData.GetID() );
	TRYBEGIN
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
		mysqlQuery.execute( szSql );
		mysqlQuery.reset();
	TRYEND
    
    strncpy_s(szSql, sizeof( szSql ), "insert into relationdata(id1,id2,relation,friendly,locked,groupid,remark) values(%0,%1,%2,%3,%4,%5,%6q);", sizeof( szSql ) - 1 );
    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
        mysqlQuery << szSql;
        mysqlQuery.parse();
        mysqlQuery.execute( mysqlpp::sql_int_unsigned( pReq->nPlayerID ), mysqlpp::sql_int_unsigned( pReq->xData.GetID() ),pReq->xData.GetRelation(),
            mysqlpp::sql_int_unsigned( pReq->xData.GetFriendly() ), pReq->xData.GetLocked(), pReq->xData.GetGroupID(), _tUTF8CHAR( pReq->xData.GetRemark() ) );
        mysqlQuery.reset();
    TRYEND
}

void NormalLogicWorkThread::OnUpdateRelationDataReq( BaseSqlMessage* pSqlMessage )
{
    CS2DBUpdateRelationDataReq *pReq = static_cast< CS2DBUpdateRelationDataReq* >( pSqlMessage->GetMessageAddress() );

    char szSql[ 512 ] = { 0 };

    switch ( pReq->uchType )
    {
    case RelationDefine::UpdateRelation:
        if ( pReq->xData.nValue != RelationDefine::InitRelation )
        {
            sprintf_s( szSql, sizeof( szSql ) - 1, "update relationdata set relation=%u where id1=%u and id2=%u;", pReq->xData.nValue, pReq->nPlayerID, pReq->nTargetID );
        }
        else
        {
            sprintf_s( szSql, sizeof( szSql ) - 1, "delete from relationdata where id1=%u and id2=%u;", pReq->nPlayerID, pReq->nTargetID );
        }
        break;
    case RelationDefine::UpdateSetFriendly:
        sprintf_s( szSql, sizeof( szSql ) - 1, "update relationdata set friendly=%u where id1=%u and id2=%u;", pReq->xData.nValue, pReq->nPlayerID, pReq->nTargetID );
        break;
    case RelationDefine::UpdateLocked:
        sprintf_s( szSql, sizeof( szSql ) - 1, "update relationdata set locked=%u where id1=%u and id2=%u;", pReq->xData.nValue, pReq->nPlayerID, pReq->nTargetID );
        break;
    case RelationDefine::UpdateGroupID:
        sprintf_s( szSql, sizeof( szSql ) - 1, "update relationdata set groupid=%u where id1=%u and id2=%u;", pReq->xData.nValue, pReq->nPlayerID, pReq->nTargetID );
        break;
    case RelationDefine::UpdateRemark:
        sprintf_s( szSql, sizeof( szSql ) - 1, "update relationdata set remark=\'%s\' where id1=%u and id2=%u;", _tUTF8CHAR(pReq->xData.szValue), pReq->nPlayerID, pReq->nTargetID );
        break;
    default:
        return;
        break;
    }

    uint32 result = ER_Success;
    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
        mysqlQuery.execute( szSql );
        mysqlQuery.reset();
    TRYEND
}

void NormalLogicWorkThread::OnAddAttributeReq( BaseSqlMessage* pSqlMessage )
{
    CS2DBAddAttributeReq *pReq = static_cast< CS2DBAddAttributeReq* >( pSqlMessage->GetMessageAddress() );
    RelationAttributeToServer& xAttribute = pReq->xAttribute;

    uint32 result = ER_Success;
    char szSql[ 512 ] = { 0 };

    sprintf_s( szSql, sizeof( szSql ) - 1, "delete from relationattribute where id=%ld;", xAttribute.GetID() );
    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
    mysqlQuery.execute( szSql );
    mysqlQuery.reset();
    TRYEND

    strncpy_s(szSql, sizeof( szSql ), "insert into relationattribute(id,name,headpic,country,profession,sex,level,guildid,position,familyid,masterlevel,messagerefuse,rewardexp,rewardprestige,lastaddstudenttime,lastaddteachertime,signature,"
        "titleid,group1,group2,group3,group4,group5,group6) values(%0,%1q,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16q,%17,%18q,%19q,%20q,%21q,%22q,%23q);", sizeof( szSql ) - 1 );

    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
        mysqlQuery << szSql;
        mysqlQuery.parse();
        mysqlQuery.execute( mysqlpp::sql_int_unsigned( xAttribute.GetID() ), _tUTF8CHAR( xAttribute.GetName() ), xAttribute.GetHeadPic(), xAttribute.GetCountry(), xAttribute.GetProfession(), xAttribute.GetSex(),
            xAttribute.GetLevel(), mysqlpp::sql_int_unsigned( xAttribute.GetGuildID() ), xAttribute.GetPosition(), xAttribute.GetFamilyID(), xAttribute.GetMasterLevel(), xAttribute.GetMessageRefuse(), mysqlpp::sql_int_unsigned( xAttribute.GetRewardExp() ),
            mysqlpp::sql_int_unsigned( xAttribute.GetRewardPrestige() ), mysqlpp::sql_bigint_unsigned( xAttribute.GetLastAddStudentTime() ), mysqlpp::sql_bigint_unsigned( xAttribute.GetLastAddTeacherTime() ), _tUTF8CHAR( xAttribute.GetSignature() ),
            xAttribute.GetTitleID(), _tUTF8CHAR( xAttribute.GetGroupName( 0 ) ), _tUTF8CHAR( xAttribute.GetGroupName( 1 ) ), _tUTF8CHAR( xAttribute.GetGroupName( 2 ) ), _tUTF8CHAR( xAttribute.GetGroupName( 3 ) ), _tUTF8CHAR( xAttribute.GetGroupName( 4 ) ),
            _tUTF8CHAR( xAttribute.GetGroupName( 5 ) ) );
        mysqlQuery.reset();
    TRYEND

    char szUpdateSql[ 512 ] = { 0 };
    sprintf_s( szUpdateSql, sizeof( szUpdateSql ) - 1, "update relationattribute set truesex=%d, age=%d, birthmonth=%d, birthday=%d, star=%d, \
       shengxiao=%d, openright=%d, province=\'%s\', city=\'%s\', trueprofession=\'%s\', qq=\'%s\', msn=\'%s\', introduction=\'%s\' where id=%u;",
       xAttribute.GetPersonalInfo().GetPersonalSex(), xAttribute.GetPersonalInfo().GetPersonalAge(), xAttribute.GetPersonalInfo().GetPersonalMonth(),
       xAttribute.GetPersonalInfo().GetPersonalDay(), xAttribute.GetPersonalInfo().GetStar(), xAttribute.GetPersonalInfo().GetShengXiao(),
       xAttribute.GetPersonalInfo().GetPersonalRight(), _tUTF8CHAR(xAttribute.GetPersonalInfo().GetProvince()), _tUTF8CHAR(xAttribute.GetPersonalInfo().GetCity()),
       _tUTF8CHAR(xAttribute.GetPersonalInfo().GetProfession()), _tUTF8CHAR(xAttribute.GetPersonalInfo().GetQQ()), _tUTF8CHAR(xAttribute.GetPersonalInfo().GetMSN()),
       _tUTF8CHAR(xAttribute.GetPersonalInfo().GetIntroduction()),  xAttribute.GetID()  );

    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
        mysqlQuery.execute( szUpdateSql );
        mysqlQuery.reset();
    TRYEND
}

void NormalLogicWorkThread::OnUpdatePersonalInfo( BaseSqlMessage* pSqlMessage )
{
	CS2DBUpdatePersonalInfoReq *pReq = static_cast< CS2DBUpdatePersonalInfoReq* >( pSqlMessage->GetMessageAddress() );
	char szSql[ 512 ] = { 0 };
	sprintf_s( szSql, sizeof( szSql ) - 1, "update relationattribute set truesex=%d, age=%d, birthmonth=%d, birthday=%d, star=%d, \
		shengxiao=%d, openright=%d, province=\'%s\', city=\'%s\', trueprofession=\'%s\', qq=\'%s\', msn=\'%s\', introduction=\'%s\' where id=%u;",
		pReq->xPersonalInfo.GetPersonalSex(), pReq->xPersonalInfo.GetPersonalAge(), pReq->xPersonalInfo.GetPersonalMonth(),
		pReq->xPersonalInfo.GetPersonalDay(), pReq->xPersonalInfo.GetStar(), pReq->xPersonalInfo.GetShengXiao(),
		pReq->xPersonalInfo.GetPersonalRight(), _tUTF8CHAR(pReq->xPersonalInfo.GetProvince()), _tUTF8CHAR(pReq->xPersonalInfo.GetCity()),
		_tUTF8CHAR(pReq->xPersonalInfo.GetProfession()), _tUTF8CHAR(pReq->xPersonalInfo.GetQQ()), _tUTF8CHAR(pReq->xPersonalInfo.GetMSN()),
		_tUTF8CHAR(pReq->xPersonalInfo.GetIntroduction()), pReq->nPlayerID );

	uint32 result = ER_Success;
	TRYBEGIN
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
	    mysqlQuery.execute( szSql );
	    mysqlQuery.reset();
	TRYEND

}

void NormalLogicWorkThread::OnUpdateAttributeReq( BaseSqlMessage* pSqlMessage )
{
    CS2DBUpdateAttributeReq *pReq = static_cast< CS2DBUpdateAttributeReq* >( pSqlMessage->GetMessageAddress() );
  
    char szSql[ 512 ] = { 0 };

    switch ( pReq->uchType )
    {
    case RelationDefine::UpdateLevel:
        sprintf_s( szSql, sizeof( szSql ) - 1, "update relationattribute set level=%I64u where id=%u;", pReq->xAttribute.n64Value, pReq->nPlayerID );
        break;
    case RelationDefine::UpdateHeadPic:
        sprintf_s( szSql, sizeof( szSql ) - 1, "update relationattribute set headpic=%I64u where id=%u;", pReq->xAttribute.n64Value, pReq->nPlayerID );
        break;
    case RelationDefine::UpdateCountry:
        sprintf_s( szSql, sizeof( szSql ) - 1, "update relationattribute set country=%I64u where id=%u;", pReq->xAttribute.n64Value, pReq->nPlayerID );
        break;
    case RelationDefine::UpdateProfession:
        sprintf_s( szSql, sizeof( szSql ) - 1, "update relationattribute set profession=%I64u where id=%u;", pReq->xAttribute.n64Value, pReq->nPlayerID );
        break;
    case RelationDefine::UpdateSex:
        sprintf_s( szSql, sizeof( szSql ) - 1, "update relationattribute set sex=%I64u where id=%u;", pReq->xAttribute.n64Value, pReq->nPlayerID );
        break;
    case RelationDefine::UpdateGuild:
        sprintf_s( szSql, sizeof( szSql ) - 1, "update relationattribute set guildid=%I64u where id=%u;", pReq->xAttribute.n64Value, pReq->nPlayerID );
        break;
    case RelationDefine::UpdatePosition:
        sprintf_s( szSql, sizeof( szSql ) - 1, "update relationattribute set position=%I64u where id=%u;", pReq->xAttribute.n64Value, pReq->nPlayerID );
        break;
	case RelationDefine::UpdateFamily:
		sprintf_s( szSql, sizeof( szSql ) - 1, "update relationattribute set familyid=%I64u where id=%u;", pReq->xAttribute.n64Value, pReq->nPlayerID );
		break;
    case RelationDefine::UpdateMasterLevel:
        sprintf_s( szSql, sizeof( szSql ) - 1, "update relationattribute set masterlevel=%I64u where id=%u;", pReq->xAttribute.n64Value, pReq->nPlayerID );
        break;
    case RelationDefine::UpdateMessageRefuse:
        sprintf_s( szSql, sizeof( szSql ) - 1, "update relationattribute set messagerefuse=%I64u where id=%u;", pReq->xAttribute.n64Value, pReq->nPlayerID );
        break;
    case RelationDefine::UpdateRewardExp:
        sprintf_s( szSql, sizeof( szSql ) - 1, "update relationattribute set rewardexp=%I64u where id=%u;", pReq->xAttribute.n64Value, pReq->nPlayerID );
        break;
    case RelationDefine::UpdateRewardPrestige:
        sprintf_s( szSql, sizeof( szSql ) - 1, "update relationattribute set rewardprestige=%I64u where id=%u;", pReq->xAttribute.n64Value, pReq->nPlayerID );
        break;
    case RelationDefine::UpdateLastStudentTime:
        sprintf_s( szSql, sizeof( szSql ) - 1, "update relationattribute set lastaddstudenttime=%I64u where id=%u;", pReq->xAttribute.n64Value, pReq->nPlayerID );
        break;
    case RelationDefine::UpdateLastTeacherTime:
        sprintf_s( szSql, sizeof( szSql ) - 1, "update relationattribute set lastaddteachertime=%I64u where id=%u;", pReq->xAttribute.n64Value, pReq->nPlayerID );
        break;
    case RelationDefine::UpdateName:
        sprintf_s( szSql, sizeof( szSql ) - 1, "update relationattribute set name=\'%s\' where id=%u;", _tUTF8CHAR( pReq->xAttribute.szValue ), pReq->nPlayerID );
        break;
    case RelationDefine::UpdateSignature:
        sprintf_s( szSql, sizeof( szSql ) - 1, "update relationattribute set signature=\'%s\' where id=%u;", _tUTF8CHAR( pReq->xAttribute.szValue ), pReq->nPlayerID );
        break;
    default:
        return;
        break;
    }

    uint32 result = ER_Success;
    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
        mysqlQuery.execute( szSql );
        mysqlQuery.reset();
    TRYEND
}

void NormalLogicWorkThread::OnUpdateRelationGroup( BaseSqlMessage* pSqlMessage )
{
    CS2DBUpdateRelationGroup *pReq = static_cast< CS2DBUpdateRelationGroup* >( pSqlMessage->GetMessageAddress() );

    char szSql[ 512 ] = { 0 };
    sprintf_s( szSql, sizeof( szSql ) - 1, "update relationattribute set group%d=\'%s\' where id=%u;", pReq->uchGroupID + 1, _tUTF8CHAR( pReq->szGroup ), pReq->nPlayerID );

    uint32 result = ER_Success;
    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
        mysqlQuery.execute( szSql );
        mysqlQuery.reset();
    TRYEND

    // 如果是清除某个好友分组
    if ( pReq->szGroup[0] == 0 )
    {
        sprintf_s( szSql, sizeof( szSql ) - 1, "update relationdata set groupid=%d where id1=%u and groupid=%d;", 0, pReq->nPlayerID, pReq->uchGroupID );
        TRYBEGIN
            mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
            mysqlQuery.execute( szSql );
            mysqlQuery.reset();
        TRYEND
    }
}

void NormalLogicWorkThread::OnQueryAttributeReq( BaseSqlMessage* pSqlMessage )
{
    GS2CSQueryAttributeReq *pReq = static_cast< GS2CSQueryAttributeReq* >( pSqlMessage->GetMessageAddress() );

    char szSql[ 512 ] = { 0 };
    sprintf_s( szSql, sizeof( szSql ) - 1, "select id from relationattribute where name like \'%%%s%%\';", /*pReq->uchCountry, */_tUTF8CHAR( pReq->szName ) );

    DB2CSQueryAttributeAck xAck;
    xAck.nPlayerID = pReq->nPlayerID;

    uint32 result = ER_Success;
    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
        mysqlpp::StoreQueryResult res = mysqlQuery.store();
        if ( res && !res.empty() )
        {
            for (int i = 0; i < res.num_rows(); ++i )
            {
                xAck.AddAttributeID( res[i]["id"] );
                if ( xAck.IsFull() )
                { break; }      // 满了就不发了, 做个限制
            }
        }
    TRYEND

    CHECK_SQL_RESULT( result ) // 执行检测
    theMysqlCommunication.PushAckMessage( &xAck, pSqlMessage->nClientId ); 
}

void NormalLogicWorkThread::OnFindPerson( BaseSqlMessage* pSqlMessage )
{
	GS2CSFindPersonReq* pReq = static_cast< GS2CSFindPersonReq* >( pSqlMessage->GetMessageAddress() );

	char szSql[ 512 ] = { 0 };
	bool bWhere = false;
	sprintf_s( szSql, sizeof( szSql ) - 1, "select id from relationattribute " );
	if ( ( pReq->uchUnlimit & RelationDefine::UnLimitSex ) == RelationDefine::UNLimitInit )
	{// 限制性别
		sprintf_s( szSql, sizeof( szSql ) - 1, "%s where truesex=%d", szSql, pReq->uchSex );
		bWhere = true;
	}
	if ( ( pReq->uchUnlimit & RelationDefine::UnLimitAge ) == RelationDefine::UNLimitInit )
	{// 限制年龄
		if ( bWhere )
		{
			sprintf_s( szSql, sizeof( szSql ) - 1, "%s and age>=%d and age<=%d", szSql, pReq->uchAgeMin, pReq->uchAgeMax );	
		}
		else
		{
			sprintf_s( szSql, sizeof( szSql ) - 1, "%s where age>=%d and age<=%d", szSql, pReq->uchAgeMin, pReq->uchAgeMax );
		}
		bWhere = true;
	}
	if ( ( pReq->uchUnlimit & RelationDefine::UnLimitPrv ) == RelationDefine::UNLimitInit )
	{// 限制省份
		if ( bWhere )
		{
			sprintf_s( szSql, sizeof( szSql ) - 1, "%s and province=\'%s\'",szSql, _tUTF8CHAR( pReq->szProvince ) );
		}
		else
		{
			sprintf_s( szSql, sizeof( szSql ) - 1, "%s where province=\'%s\'",szSql, _tUTF8CHAR( pReq->szProvince ) );
		}
		bWhere = true;
	}
	if ( ( pReq->uchUnlimit & RelationDefine::UnLimitCity ) == RelationDefine::UNLimitInit )
	{// 限制城市
		if ( bWhere )
		{
			sprintf_s( szSql, sizeof( szSql ) - 1, "%s and city=\'%s\'",szSql, _tUTF8CHAR( pReq->szCity ) );
		}
		else
		{
			sprintf_s( szSql, sizeof( szSql ) - 1, "%s where city=\'%s\'",szSql, _tUTF8CHAR( pReq->szCity ) );
		}
		bWhere = true;
	}

	DB2CSQueryAttributeAck xAck;
	xAck.nPlayerID = pReq->nPlayerID;

	uint32 result = ER_Success;
	TRYBEGIN
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
		mysqlpp::StoreQueryResult res = mysqlQuery.store();
		if ( res && !res.empty() )
		{
			for (int i = 0; i < res.num_rows(); ++i )
			{
				xAck.AddAttributeID( res[i]["id"] );
				if ( xAck.IsFull() )
				{ break; }      // 满了就不发了, 做个限制
			}
		}
	TRYEND

	CHECK_SQL_RESULT( result ) // 执行检测
	theMysqlCommunication.PushAckMessage( &xAck, pSqlMessage->nClientId ); 
}