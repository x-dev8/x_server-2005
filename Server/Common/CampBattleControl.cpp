#include "CampBattleControl.h"
#include "CampGuildBattleConfig.h"
#include "CampCountryBattleConfig.h"
#include "CountryDefine.h"
#include "ResourcePath.h"
#include "LogFileObjectNameEx.h"
#include "CampGuildUnionBattleManager.h"
#include "CampGuildUnionBattleConfig.h"
#include "DBMessageDefine.h"
#include "DatabaseConnectors.h"
CampBattleControl::CampBattleControl()
{
   /* m_vecManager.resize( CampDefine::BattleTypeMax );
    m_vecManager[ CampDefine::BattleTypeNone ] = NULL;*/
	m_vecManager.clear();

    m_xUpdateTimer.StartTimer( 1, CampDefine::UpdateSpaceTime );
}

void CampBattleControl::RegisterManager( CampBattleManager* pManager )
{
    if ( pManager == NULL )
    { return; }

    if ( pManager->GetBattleType() == CampDefine::BattleTypeNone/* || pManager->GetBattleType() >= m_vecManager.size() */)
    { return; }

    /*m_vecManager[ pManager->GetBattleType() ] = pManager;*/
	m_vecManager.push_back(pManager);
}

//CampBattleManager* CampBattleControl::GetManager( unsigned char uchType )
//{
//    if ( uchType >= m_vecManager.size() )
//    { return NULL; }
//
//    return m_vecManager.at( uchType );
//}

CampBattleManager* CampBattleControl::GetManagerBytypeAndCountry(unsigned char uchType, int uchcountry )
{
	//�����ļ� ������ ���� ������ս���ľ������ 
	//����ս�������� OK ��� ���ݹ���ID����
	//����ս�������� OK һ��GameServer�Ͼ�һ�� ������������
	//����Լս������ ��� �������� �ڸ��ݹ���ս���Ĺ���ID������ ��ǰ�����޷���ȡ����Լս������

	/*if ( uchType >= m_vecManager.size())
	{ return NULL; }	*/
	//�������ͻ�ȡս���Ĺ����� ս���й��ҵ����� �������޹��ҵĻ���
	for (int n = 0;n < m_vecManager.size();n++)//�������е�ս��
	{
		if (m_vecManager[n]->GetBattleType() == uchType)
		{
			if(m_vecManager[n]->GetBattleConfig())
			{
				for (int m =0;m < m_vecManager[n]->GetBattleConfig()->GetMapSettingCount();m++)
				{
					const CampBattleConfig::MapSetting* pMapSetting = m_vecManager[n]->GetBattleConfig()->GetMapSetting(m);
					if (pMapSetting && (pMapSetting->GetCountryID() == uchcountry ||  pMapSetting->GetCountryID() == 0))//Ϊ0��ʾս���޹��ҵĻ��� �����˿��Բμ�
					{
						return m_vecManager[n];
					}
				}
			}
		}
	}
	return NULL;
}

bool CampBattleControl::RegisterGuildBattleManger()
{
    static CampGuildBattleConfig s_xCampGuildBattleConfig;
    if ( !s_xCampGuildBattleConfig.LoadConfig( CAMPGUILDBATTLE_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" , CAMPGUILDBATTLE_FILEPATH ); 
        return false;
    }


    static CampGuildBattleManager s_xCampGuildBattleManater;
    s_xCampGuildBattleManater.SetBattleConfig( &s_xCampGuildBattleConfig );
    RegisterManager( &s_xCampGuildBattleManater );

    return true;
}
bool CampBattleControl::RegisterGuildUnionBattleManger()
{
    if ( !theCampGuildUnionBattleConfig.LoadConfig( CAMPGUILDUNIONBATTLE_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" , CAMPGUILDUNIONBATTLE_FILEPATH ); 
        return false;
    }
	static CampGuildUnionBattleManager s_xCampGuildUnionBattleManater;
	RegisterManager( &s_xCampGuildUnionBattleManater );
	return true;
}

bool CampBattleControl::RegisterKingBattleManger()
{
	for (int n = 0; n < CountryDefine::Country_Max;n++)
	{
		if (n == CountryDefine::Country_Init)
		{
			continue;
		}
		CampCountryBattleConfig* PCampKingBattleConfig = new CampCountryBattleConfig;		
		if ( !PCampKingBattleConfig->LoadConfig( CAMPKINGBATTLE_FILEPATH,n ) )
		{
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" , CAMPKINGBATTLE_FILEPATH ); 
			return false;
		}

		CampCountryBattleManager *s_xCampKingBattleManater = new CampCountryBattleManager;
		s_xCampKingBattleManater->SetBattleType(CampDefine::BattleTypeKing);//SetBattleType( CampDefine::BattleTypeKing );
		s_xCampKingBattleManater->SetCountryBattleType( CountryDefine::Battle_King );
		s_xCampKingBattleManater->SetBattleConfig(PCampKingBattleConfig);
		RegisterManager( s_xCampKingBattleManater );
	}

    /*static CampCountryBattleConfig s_xCampKingBattleConfig;
    if ( !s_xCampKingBattleConfig.LoadConfig( CAMPKINGBATTLE_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" , CAMPKINGBATTLE_FILEPATH ); 
        return false;
    }

    static CampCountryBattleManager s_xCampKingBattleManater;
    s_xCampKingBattleManater.SetBattleType( CampDefine::BattleTypeKing );
    s_xCampKingBattleManater.SetCountryBattleType( CountryDefine::Battle_King );
    s_xCampKingBattleManater.SetBattleConfig( &s_xCampKingBattleConfig );
    RegisterManager( &s_xCampKingBattleManater );*/

    return true;
}

bool CampBattleControl::RegisterDragonBattleManger()
{
	for (int n = 0; n < CountryDefine::Country_Max;n++)
	{
		if (n == CountryDefine::Country_Init)
		{
			continue;
		}
		CampCountryBattleConfig* PCampKingBattleConfig = new CampCountryBattleConfig;		
		if ( !PCampKingBattleConfig->LoadConfig( CAMPDRAGONBATTLE_FILEPATH,n ) )
		{
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" , CAMPDRAGONBATTLE_FILEPATH ); 
			return false;
		}

		/*static */CampCountryBattleManager* s_xCampDragonBattleManater = new CampCountryBattleManager;
		s_xCampDragonBattleManater->SetBattleType( CampDefine::BattleTypeDragon );
		s_xCampDragonBattleManater->SetCountryBattleType( CountryDefine::Battle_Dragon );
		s_xCampDragonBattleManater->SetBattleConfig(PCampKingBattleConfig);
		RegisterManager( s_xCampDragonBattleManater );
	}

  /*  static CampCountryBattleConfig s_xCampDragonBattleConfig;
    if ( !s_xCampDragonBattleConfig.LoadConfig( CAMPDRAGONBATTLE_FILEPATH) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" , CAMPDRAGONBATTLE_FILEPATH ); 
        return false;
    }

    static CampCountryBattleManager s_xCampDragonBattleManater;
    s_xCampDragonBattleManater.SetBattleType( CampDefine::BattleTypeDragon );
    s_xCampDragonBattleManater.SetCountryBattleType( CountryDefine::Battle_Dragon );
    s_xCampDragonBattleManater.SetBattleConfig( &s_xCampDragonBattleConfig );
    RegisterManager( &s_xCampDragonBattleManater );*/

    return true;
}

bool CampBattleControl::RegisterRosefinchBattleManger()
{
	for (int n = 0; n < CountryDefine::Country_Max;n++)
	{
		if (n == CountryDefine::Country_Init)
		{
			continue;
		}
		CampCountryBattleConfig* PCampKingBattleConfig = new CampCountryBattleConfig;		
		if ( !PCampKingBattleConfig->LoadConfig( CAMPROSEFINCHBATTLE_FILEPATH,n ) )
		{
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" , CAMPROSEFINCHBATTLE_FILEPATH ); 
			return false;
		}

		CampCountryBattleManager* s_xCampRosefinchBattleManater = new CampCountryBattleManager;
		s_xCampRosefinchBattleManater->SetBattleType( CampDefine::BattleTypeRosefinch );
		s_xCampRosefinchBattleManater->SetCountryBattleType( CountryDefine::Battle_Rosefinch );
		s_xCampRosefinchBattleManater->SetBattleConfig(PCampKingBattleConfig);
		RegisterManager( s_xCampRosefinchBattleManater );
	}
    /*static CampCountryBattleConfig s_xCampRosefinchBattleConfig;
    if ( !s_xCampRosefinchBattleConfig.LoadConfig( CAMPROSEFINCHBATTLE_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" , CAMPROSEFINCHBATTLE_FILEPATH ); 
        return false;
    }

    static CampCountryBattleManager s_xCampRosefinchBattleManater;
    s_xCampRosefinchBattleManater.SetBattleType( CampDefine::BattleTypeRosefinch );
    s_xCampRosefinchBattleManater.SetCountryBattleType( CountryDefine::Battle_Rosefinch );
    s_xCampRosefinchBattleManater.SetBattleConfig( &s_xCampRosefinchBattleConfig );
    RegisterManager( &s_xCampRosefinchBattleManater );*/

    return true;
}
bool CampBattleControl::InitCampBattleManager()
{
    // ע���������ս
    if ( !RegisterGuildBattleManger() )
    { return false; }

    // ע���������ս
    if ( !RegisterKingBattleManger() )
    { return false; }

	if(!RegisterGuildUnionBattleManger())
		return false;

	//zhuxincong ��ʱû��������ս�� ע��
    //// ע����������ս
    //if ( !RegisterDragonBattleManger() )
    //{ return false; }

    //// ע����ȸ����ս
    //if ( !RegisterRosefinchBattleManger() )
    //{ return false; }
    return true;
}
void CampBattleControl::RunUpdate( unsigned int nCurrentTime )
{
    if ( !m_xUpdateTimer.DoneTimer( nCurrentTime ) )
    { return; }

    for ( CampBattleManagerVectorIter iter = m_vecManager.begin(); iter != m_vecManager.end(); ++iter )
    {
        CampBattleManager* pManager = *iter;
        if ( pManager == NULL )
        { continue; }

        pManager->RunUpdate( nCurrentTime );
    }
}

CampBattle* CampBattleControl::GetCampBattle( unsigned char uchFightCamp, unsigned int nMapID,unsigned char countryid )
{
    if ( uchFightCamp == CampDefine::NoneCamp )
    { return NULL; }

    unsigned char uchBattleType = CampDefine::GetBattleTypeByCamp( uchFightCamp );
    CampBattleManager* pManager = GetManagerBytypeAndCountry( uchBattleType,countryid );
    if ( pManager == NULL )
    { return NULL; }

    return pManager->GetCampBattleByMapID( nMapID );
}

CampBattle* CampBattleControl::GetCampBattle( unsigned int nPlayerID )
{
    for ( CampBattleManagerVectorIter iter = m_vecManager.begin(); iter != m_vecManager.end(); ++iter )
    {
        CampBattleManager* pManager = *iter;
        if ( pManager == NULL )
        { continue; }

        CampBattle* pCampBattle = pManager->GetCampBattleByPlayerID( nPlayerID );
        if ( pCampBattle != NULL )
        { return pCampBattle; }
    }

    return NULL;
}
