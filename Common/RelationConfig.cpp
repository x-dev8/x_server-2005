#include "RelationConfig.h"
#include "RapidXml/MeRapidXml.h"

bool RelationConfig::LoadRelationConfig( const char* szFile )
{
    m_vecExtendFriendly.clear();
    m_vecTeamBuffer.clear();
    m_vecLevelInfo.clear();
    m_vecTeamSkill.clear();
    m_vecMasterInfo.clear();
    m_vecFriendBuffer.clear();
	m_vecGuildBuffer.clear();

    if ( szFile == NULL || *szFile == 0 )
    { return false; }

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( szFile, 1 ) )
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if ( pRoot == NULL )
    { return false; }

    MeXmlElement* pFriendLevel = pRoot->FirstChildElement( "FriendLevel" );
    if ( pFriendLevel == NULL )
    { return false; }

    int nMaxLevel;
    if ( pFriendLevel->Attribute( "MaxLevel", &nMaxLevel ) == NULL || nMaxLevel == 0 )
    { return false; }

    SetMaxFriendLevel( nMaxLevel );

    int mMaxFriendly;
    if ( pFriendLevel->Attribute( "MaxFriendly", &mMaxFriendly ) == NULL || mMaxFriendly == 0 )
    { return false; }

    SetMaxFriendly( mMaxFriendly );

    m_vecLevelInfo.resize( nMaxLevel + 1 );

    MeXmlElement* pFriend = pFriendLevel->FirstChildElement( "Friend" );
    while ( pFriend != NULL )
    {
        int nLevel;
        if ( pFriend->Attribute( "Level", &nLevel ) == NULL || nLevel == 0 )
        { return false; }

        LevelInfo xFriendLevel;
        int nFriendly;
        if ( pFriend->Attribute( "Friendly", &nFriendly ) == NULL )
        { return false; }
        xFriendLevel.SetFriendly( nFriendly );

        int nStringID;
        if ( pFriend->Attribute( "NameID", &nStringID ) == NULL )
        { return false; }
        xFriendLevel.SetStringID( nStringID );

        if ( !AddFriendInfo( nLevel, xFriendLevel ) )
        { return false; }

        pFriend = pFriend->NextSiblingElement();
    }


    //MeXmlElement* pExtendFriendly = pRoot->FirstChildElement( "ExtendFriendly" );
    //if ( pExtendFriendly == NULL )
    //{ return false; }

    //m_vecExtendFriendly.resize( ExtendType_Max );
    //MeXmlElement* pExtend = pExtendFriendly->FirstChildElement( "Extend" );
    //while ( pExtend != NULL )
    //{
    //    int nType;
    //    if ( pExtend->Attribute( "Type", &nType ) == NULL )
    //    { return false; }

    //    int nValue;
    //    if ( pExtend->Attribute( "Value", &nValue ) == NULL )
    //    { return false; }

    //    if ( !AddExtendFriendly( nType, nValue ) )
    //    { return false; }

    //    pExtend = pExtend->NextSiblingElement();
    //}

    MeXmlElement* pTeamBuffers = pRoot->FirstChildElement( "TeamBuffers" );
    if ( pTeamBuffers == NULL )
    { return false; }

    // 关系Buffer
    MeXmlElement* pFriendBuffer = pTeamBuffers->FirstChildElement( "FriendBuffer" );
    if ( pFriendBuffer == NULL )
    { return false; }
    m_vecFriendBuffer.resize( m_uchMaxFriendLevel + 1 );
    MeXmlElement* pFriendBuff = pFriendBuffer->FirstChildElement( "Friend" );
    while ( pFriendBuff != NULL )
    {
        int nLevel;
        if ( pFriendBuff->Attribute( "Level", &nLevel ) == NULL || nLevel == 0 )
        { return false; }

        MeXmlElement* pBuffer = pFriendBuff->FirstChildElement( "Buffer" );
        while ( pBuffer != NULL )
        {
            int nProfession;
            if ( pBuffer->Attribute( "Profession", &nProfession ) == NULL )
            { return false; }

            TeamBuffer xTeamBuffer;

            int nBufferID;
            if ( pBuffer->Attribute( "BufferID", &nBufferID ) == NULL )
            { return false; }
            xTeamBuffer.SetBufferID( nBufferID );

            int nBufferLevel;
            if ( pBuffer->Attribute( "Level", &nBufferLevel ) == NULL )
            { return false; }
            xTeamBuffer.SetBufferLevel( nBufferLevel );

            if ( !AddFriendBuffer( nLevel, xTeamBuffer ) )
            { return false; }

            pBuffer = pBuffer->NextSiblingElement();
        }

        pFriendBuff = pFriendBuff->NextSiblingElement();
    }

    // 队伍Buffer
    MeXmlElement* pTeamBuffer = pTeamBuffers->FirstChildElement( "TeamBuffer" );
    if ( pTeamBuffer == NULL )
    { return false; }
    m_vecTeamBuffer.resize( 6 );
    MeXmlElement* pTeam = pTeamBuffer->FirstChildElement( "Team" );
    while ( pTeam != NULL )
    {
        int nTeamCount;
        if ( pTeam->Attribute( "Count", &nTeamCount ) == NULL || nTeamCount == 0 )
        { return false; }

        MeXmlElement* pBuffer = pTeam->FirstChildElement( "Buffer" );
        while ( pBuffer != NULL )
        {
            int nProfession;
            if ( pBuffer->Attribute( "Profession", &nProfession ) == NULL )
            { return false; }

            TeamBuffer xTeamBuffer;

            int nBufferID;
            if ( pBuffer->Attribute( "BufferID", &nBufferID ) == NULL )
            { return false; }
            xTeamBuffer.SetBufferID( nBufferID );

            int nLevel;
            if ( pBuffer->Attribute( "Level", &nLevel ) == NULL )
            { return false; }
            xTeamBuffer.SetBufferLevel( nLevel );

            if ( !AddTeamBuffer( nTeamCount, xTeamBuffer ) )
            { return false; }

            pBuffer = pBuffer->NextSiblingElement();
        }

        pTeam = pTeam->NextSiblingElement();
    }

	//军团buffer
	MeXmlElement* pGuildBuffer = pTeamBuffers->FirstChildElement( "GuildBuffer" );
	if ( pGuildBuffer == NULL )
	{ return false; }
	m_vecGuildBuffer.resize( 6 );
	MeXmlElement* pGuild = pGuildBuffer->FirstChildElement( "Guild" );
	while ( pGuild != NULL )
	{
		int nGuildLevel;
		if ( pGuild->Attribute( "Level", &nGuildLevel ) == NULL || nGuildLevel == 0 )
		{ return false; }

		MeXmlElement* pBuffer = pGuild->FirstChildElement( "Buffer" );
		while ( pBuffer != NULL )
		{
			int nProfession;
			if ( pBuffer->Attribute( "Profession", &nProfession ) == NULL )
			{ return false; }

			TeamBuffer xTeamBuffer;

			int nBufferID;
			if ( pBuffer->Attribute( "BufferID", &nBufferID ) == NULL )
			{ return false; }
			xTeamBuffer.SetBufferID( nBufferID );

			int nLevel;
			if ( pBuffer->Attribute( "Level", &nLevel ) == NULL )
			{ return false; }
			xTeamBuffer.SetBufferLevel( nLevel );

			if ( !AddGuildBuffer( nGuildLevel, xTeamBuffer ) )
			{ return false; }

			pBuffer = pBuffer->NextSiblingElement();
		}

		pGuild = pGuild->NextSiblingElement();
	}

    MeXmlElement* pTeamSkills = pRoot->FirstChildElement( "TeamSkills" );
    if ( pTeamSkills == NULL )
    { return false; }

    m_vecTeamSkill.resize( GetMaxFriendLevel() + 1 );
    MeXmlElement* pTeamSkill = pTeamSkills->FirstChildElement( "TeamSkill" );
    while ( pTeamSkill != NULL )
    {
        int nFriendLevel;
        if ( pTeamSkill->Attribute( "FriendLevel", &nFriendLevel ) == NULL )
        { return false; }

        MeXmlElement* pProfession = pTeamSkill->FirstChildElement( "Profession" );
        while ( pProfession != NULL )
        {
            int nProfession;
            if ( pProfession->Attribute( "Type", &nProfession ) == NULL )
            { return false; }

            MeXmlElement* pSkill = pProfession->FirstChildElement( "Skill" );
            while ( pSkill != NULL )
            {
                TeamSkill xTeamSkill;

                int nSkillID;
                if ( pSkill->Attribute( "SkillID", &nSkillID ) == NULL )
                { return false; }
                xTeamSkill.SetSkillID( nSkillID );

                int nLevel;
                if ( pSkill->Attribute( "Level", &nLevel ) == NULL )
                { return false; }
                xTeamSkill.SetSkillLevel( nLevel );

                if ( !AddTeamSkill( nFriendLevel, nProfession, xTeamSkill ) )
                { return false; }

                pSkill = pSkill->NextSiblingElement();
            }

            pProfession = pProfession->NextSiblingElement();
        }

        pTeamSkill = pTeamSkill->NextSiblingElement();
    }

    MeXmlElement* pRelationCount = pRoot->FirstChildElement( "RelationCount" );
    if ( pRelationCount == NULL )
    { return false; }

    MeXmlElement* pTempFriendCount = pRelationCount->FirstChildElement( "TempFriendMaxCount" );
    if ( pTempFriendCount == NULL )
    { return false; }

    int nCount;
    if ( pTempFriendCount->Attribute( "Count", &nCount ) != NULL )
    { m_nMaxTempFriendCount = nCount; }

    MeXmlElement* pFriendCount = pRelationCount->FirstChildElement( "FriendMaxCount" );
    if ( pFriendCount == NULL )
    { return false; }
    if ( pFriendCount->Attribute( "Count", &nCount ) != NULL )
    { m_nMaxFriendCount = nCount; }

    MeXmlElement* pBlackListCount = pRelationCount->FirstChildElement( "BlackListMaxCount" );
    if ( pBlackListCount == NULL )
    { return false; }
    if ( pBlackListCount->Attribute( "Count", &nCount ) != NULL )
    { m_nMaxBlackListCout = nCount; }

    MeXmlElement* pVendettaCount = pRelationCount->FirstChildElement( "VendettaMaxCount" );
    if ( pVendettaCount == NULL )
    { return false; }
    if ( pVendettaCount->Attribute( "Count", &nCount ) != NULL )
    { m_nMaxVendettaCount = nCount; }

    MeXmlElement* pStudentCount = pRelationCount->FirstChildElement( "StudentMaxCount" );
    if ( pStudentCount == NULL )
    { return false; }

    int nMaxMasterLevel;
    if ( pStudentCount->Attribute( "MaxLevel", &nMaxMasterLevel ) == NULL )
    { return false; }
    m_nMaxMasterLevel = nMaxMasterLevel;
    m_vecMasterInfo.resize( nMaxMasterLevel + 1 );
    MeXmlElement* pMasterInfo = pStudentCount->FirstChildElement( "MasterInfo" );
    while ( pMasterInfo != NULL )
    {
        int nLevel;
        if ( pMasterInfo->Attribute( "Level", &nLevel ) == NULL )
        { return false; }

        MasterInfo xInfo;

        int nNeedMasterValue;
        if ( pMasterInfo->Attribute( "NeedMasterValue", &nNeedMasterValue ) == NULL )
        { return false; }
        xInfo.SetNeedMasterValue( nNeedMasterValue );

        int nMaxMasterValue;
        if ( pMasterInfo->Attribute( "MaxMasterValue", &nMaxMasterValue ) == NULL || nMaxMasterValue == 0 )
        { return false; }
        xInfo.SetMaxMasterValue( nMaxMasterValue );

        int nRecruitCount;
        if ( pMasterInfo->Attribute( "RecruitCount", &nRecruitCount ) == NULL || nRecruitCount == 0 )
        { return false; }
        xInfo.SetRecruitCount( nRecruitCount );

        int nTitleID;
        if ( pMasterInfo->Attribute( "TitleID", &nTitleID ) == NULL )
        { return false; }
        xInfo.SetMasterTitleID( nTitleID );

        if ( !AddMasterInfo( nLevel, xInfo ) )
        { return false; }

        pMasterInfo = pMasterInfo->NextSiblingElement();
    }

    MeXmlElement* pUpdateFriendly = pRoot->FirstChildElement( "UpdateFriendly" );
    if ( pUpdateFriendly == NULL )
    { return false; }

    int nTimeSpan;
    if ( pUpdateFriendly->Attribute( "TimeSpan", &nTimeSpan ) == NULL || nTimeSpan == 0 )
    { return false; }
    m_dwUpdateFriendlySpan = nTimeSpan * 1000;

    int nAddFriendly;
    if ( pUpdateFriendly->Attribute( "AddFriendly", &nAddFriendly ) == NULL || nAddFriendly == 0 )
    { return false; }
    m_ustAddFriendly = nAddFriendly;

    int nSubFriendly;
    if ( pUpdateFriendly->Attribute( "KillSubFriendly", &nSubFriendly ) == NULL )
    { return false; }
    m_ustKillSubFriendly = nSubFriendly;

    // 结婚最低好友度
    MeXmlElement* pMarriageFriendly = pRoot->FirstChildElement( "MarriageFriendly" );
    if ( pMarriageFriendly == NULL )
    { return false; }

    int nMarriageFriendly;
    if ( pMarriageFriendly->Attribute( "Value", &nMarriageFriendly ) == NULL || nMarriageFriendly == 0 )
    { return false; }
    m_dwMarriageFriendly = nMarriageFriendly;

    int nMarriageLevel;
    if ( pMarriageFriendly->Attribute( "MaleLevel", &nMarriageLevel ) == NULL || nMarriageLevel == 0 )
    { return false; }
    m_ustMarriageMaleLevel = nMarriageLevel;

    if ( pMarriageFriendly->Attribute( "FemaleLevel", &nMarriageLevel ) == NULL || nMarriageLevel == 0 )
    { return false; }
    m_ustMarriageFemaleLevel = nMarriageLevel;

    MeXmlElement* pPrenticeExpModulus = pRoot->FirstChildElement( "PrenticeExpModulus" );
    if ( pPrenticeExpModulus != NULL )
    {
        int nLevelDistance;
        if ( pPrenticeExpModulus->Attribute( "LevelDistance", &nLevelDistance ) != NULL )
        { m_xStudentExpModulus.SetLevelDistance( nLevelDistance ); }

        double dExpModulus;
        if ( pPrenticeExpModulus->Attribute( "NoTeamModulus", &dExpModulus ) != NULL )
        { m_xStudentExpModulus.SetNoTeamModulus( static_cast< float >( dExpModulus ) ); }

        if ( pPrenticeExpModulus->Attribute( "HaveTeamModulus", &dExpModulus ) != NULL )
        { m_xStudentExpModulus.SetHaveTeamModulus( static_cast< float >( dExpModulus ) ); }
    }

    // 拜师 收徒的限制
    MeXmlElement* pPrenticeLimit = pRoot->FirstChildElement( "PrenticeLimit" );
    if ( pPrenticeLimit == NULL )
    { return false; }

    int nStudentMinLevel;
    if ( pPrenticeLimit->Attribute( "StudentMinLevel", &nStudentMinLevel ) == NULL )
    { return false; }
    m_xPrenticeLimit.SetMinStudentLevel( nStudentMinLevel );

    int nTeacherMinLevel;
    if ( pPrenticeLimit->Attribute( "TeacherMinLevel", &nTeacherMinLevel ) == NULL )
    { return false; }
    m_xPrenticeLimit.SetMinTeacherLevel( nTeacherMinLevel );

    int nPrenticeLimitMinLevelSpan;
    if ( pPrenticeLimit->Attribute( "MinLevelSpan", &nPrenticeLimitMinLevelSpan ) == NULL )
    { return false; }
    m_xPrenticeLimit.SetMinLevelSpan( nPrenticeLimitMinLevelSpan );

    int nTeacherTimeSpan;
    if ( pPrenticeLimit->Attribute( "TeacherTimeSpan", &nTeacherTimeSpan ) == NULL )
    { return false; }
    m_xPrenticeLimit.SetTeacherTimeSpan( nTeacherTimeSpan );

    int nStudentTimeSpan;
    if ( pPrenticeLimit->Attribute( "StudentTimeSpan", &nStudentTimeSpan ) == NULL )
    { return false; }
    m_xPrenticeLimit.SetStudentTimeSpan( nStudentTimeSpan );

    // 删除关系扣钱
    MeXmlElement* pRemoveCostMoney = pRoot->FirstChildElement( "RemoveRelation" );
    if ( pRemoveCostMoney == NULL )
    { return false; }

    MeXmlElement* pRemoveMaster = pRemoveCostMoney->FirstChildElement( "RemoveMaster" );
    if ( pRemoveMaster == NULL )
    { return false; }
    int nCostMoney;
    if ( pRemoveMaster->Attribute( "CostMoney", &nCostMoney ) == NULL )
    { return false; }
    m_dwRemoveMasterCostMoney = nCostMoney;

    MeXmlElement* pRemovePrentice = pRemoveCostMoney->FirstChildElement( "RemovePrentice" );
    if ( pRemovePrentice == NULL )
    { return false; }
    if ( pRemovePrentice->Attribute( "CostMoney", &nCostMoney ) == NULL )
    { return false; }
    m_dwRemovePrenticeCostMoney = nCostMoney;

    // 师徒指点 汇报
    MeXmlElement* pReport = pRoot->FirstChildElement( "Report" );
    if ( pReport == NULL )
    { return false; }

    int nMasterValue;
    if ( pReport->Attribute( "MasterValue", &nMasterValue ) == NULL )
    { return false; }
    m_xReportInfo.SetMasterValue( nMasterValue );

    int nExpValue;
    if ( pReport->Attribute( "ExpValue", &nExpValue ) == NULL )
    { return false; }
    m_xReportInfo.SetExpValue( nExpValue );

    int nModulusValue;
    if ( pReport->Attribute( "ModulusValue", &nModulusValue ) == NULL )
    { return false; }
    m_xReportInfo.SetModulusValue( nModulusValue );

    return true;
}