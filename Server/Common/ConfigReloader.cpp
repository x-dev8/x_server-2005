#include "ConfigReloader.h"
#include "ResourcePath.h"
#include "ItemDetailConfig.h"
#include "ColorScreen.h"
#include "Singleton.h"

ConfigReloader& GetConfigReloader()
{
	if (eRCFGTYPE_MAX != sizeof(g_szResourceCfgPath)/sizeof(char*))
	{
		COLOR_MESSAGE( COLOR_RED, "error!! size:g_szResourceCfgPath != eRCFGTYPE_MAX \n" );
	}
	static ConfigReloader instance;
	return instance;
}

void ConfigReloader::ConfigReloaderThreadFunc( void* pVoid )
{
	ConfigReloader* pReloader = static_cast< ConfigReloader* >( pVoid );
	if ( NULL == pReloader )
	{ return; }

	ReloadReqMsgQueue tempQueue;
	{
		CSALocker lock( pReloader->_lockReqQueue );
		tempQueue = pReloader->_reqQueue;
		pReloader->_reqQueue.clear();
	}

	ItrReloadReqMsgQueue itr = tempQueue.begin();
	ItrReloadReqMsgQueue endItr = tempQueue.end();
	for ( ; itr != endItr; ++itr )
	{
		switch ( itr->nReloadType )
		{
#ifdef _GAME_SERVER_
		// �����gameserver����
		case eRCFGTYPE_SHOPCENTER:
			break;
#else
		// �����CenterServer����
		case eRCFGTYPE_MOUNTSTRENGTHEN:
		case eRCFGTYPE_STARLEVELUP:
			break;
#endif

		default:
			{
				ItrCfgSingletionsMap it = pReloader->m_mapCfgSingletions.find(itr->nReloadType);
				if ( it == pReloader->m_mapCfgSingletions.end())
				{
					LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "ResourceCfgType is:%d path:%s, but canot ReLoad!", itr->nReloadType,g_szResourceCfgPath[itr->nReloadType] );
					break;
				}
				LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "ResourceCfgType is:%d path:%s, Start Loading...!", itr->nReloadType,g_szResourceCfgPath[itr->nReloadType] );
				if (!it->second->MultiReloadConfig(g_szResourceCfgPath[itr->nReloadType]))
				{
					LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "ResourceCfgType is:%d��ReLoad Fail!", itr->nReloadType );
				}
				// �������׼���滻
				AckReloadMsg ackMsg;
				ackMsg.nReloadType = itr->nReloadType;
				pReloader->AddConfigReloadAckMsg( ackMsg );
			}
			break;
		}
	}

	static const int nSleepTime = 10; //g_Cfg.m_bSleepTime;
	Sleep( nSleepTime );
}

void ConfigReloader::Update()
{
	AckReloadMsgQueue tempQueue;
	{
		CSALocker lock( _lockAckQueue );
		tempQueue = _ackQueue;
		_ackQueue.clear();
	}

	ItrAckReloadMsgQueue itr = tempQueue.begin();
	ItrAckReloadMsgQueue endItr = tempQueue.end();
	for ( ; itr != endItr; ++itr )
	{
		ItrCfgSingletionsMap it = m_mapCfgSingletions.find(itr->nReloadType);
		if ( it != m_mapCfgSingletions.end())
		{
			it->second->ReplaceInstance();
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "ResourceCfgType is:%d path:%s, ReLoad OK!", itr->nReloadType, g_szResourceCfgPath[itr->nReloadType] );
		}
		else
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "ResourceCfgType is:%d path:%s, ReplaceInstance Fail!", itr->nReloadType, g_szResourceCfgPath[itr->nReloadType] );
	}
}

void ConfigReloader::AddConfigReloadReqMsg( ReloadReqMsg& reqMsg )
{
	CSALocker lock( _lockReqQueue );
	_reqQueue.push_back(reqMsg);
}

void ConfigReloader::AddConfigReloadAckMsg( AckReloadMsg& ackMsg )
{
	CSALocker lock( _lockAckQueue );
	_ackQueue.push_back(ackMsg);
}

void ConfigReloader::OnReloadFinishedForRegister(int nType,ICfgSingletionBase* pCfgSingl)
{
	ItrCfgSingletionsMap it = m_mapCfgSingletions.find(nType);
	if (it == m_mapCfgSingletions.end())
	{
		m_mapCfgSingletions.insert(std::make_pair(nType,pCfgSingl));
	}
	else
	{
		m_mapCfgSingletions[nType] = pCfgSingl;
	}
}
// bool ConfigReloader::ReloadItemDetail( CItemDetailConfig* pConfigInst )
// {
// 	//��ȡ�������������Ϣ
// 	if (!pConfigInst->InitItemDetail())
// 	{
// 		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"%s Fail! \n","InitItemDetail");
// 		return false;
// 	}
// 
// 	//���ع�������
// 	if (!pConfigInst->LoadXmlMonster(MONSTERCONFIG_FILEPATH))
// 	{
// 		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"%s Fail! \n","LoadXmlMonster");
// 		return false;
// 	}
// 
// 	//���س�������
// 	if (!theItemDetailConfig.LoadXmlPetMonster(PETCONFIG_FILEPATH))
// 	{
// 		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error] ",PETCONFIG_FILEPATH );
// 		return false;
// 	}
// 	else
// 	{
// 		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ",PETCONFIG_FILEPATH );
// 	}
// 
// 	//������������
// 	if (!pConfigInst->LoadXmlMount(MOUNTCONFIG_FILEPATH))
// 	{
// 		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"%s Fail! \n","LoadXmlMount");
// 		return false;
// 	}
// 
// 	//����װ���������
// 	if (!pConfigInst->LoadXmlRand(EQUIPMENTRANDOM_FILEPATH))
// 	{
// 		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"%s Fail! \n","LoadXmlRand");
// 		return false;
// 	}
// 
// 	//����װ��ǿ��ϵ��
// 	if (!pConfigInst->LoadXmlEquipQualityIntensity(EQUIPQUALITYINTENSITY_FILEPATH))
// 	{
// 		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"%s Fail! \n","LoadXmlEquipQualityIntensity");
// 		return false;
// 	}
// 
// 	//���ؽ�ͨ�������Ϣ
// 	if (!pConfigInst->LoadSlkTraffic(TRAFFIC_FILEPATH))
// 	{
// 		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"%s Fail! \n","LoadSlkTraffic");
// 		return false;
// 	}
// 	return true;
// }
// 
// 
