#include "FileDB.h"
#include "NewWithDebug.h"
#include "FuncPerformanceLog.h"
#include "CRC32.h"
#include "FileSearch.h"
#include "DatabaseConnectors.h"
#include "tstring.h"
#include "Configure.h"

// const DWORD SAVE_DELAY = 1000*60*30; // 30分钟将未保存成功的角色数据发送一次

#pragma warning( push )
#pragma warning( disable : 4311)

CFileDB::CFileDB()
{
}

CFileDB::~CFileDB()
{
}

bool CFileDB::SetPath(const char* path)
{
	if ( _mkdir( path ) != 0 )
	{
		int error = 0;
		_get_errno( &error );

		if ( error != EEXIST )
		{
			char errorString[ MAX_PATH + 1] ={};
			switch ( error )
			{
			case ENOENT:
				{
					sprintf_s( errorString, MAX_PATH, "FilePath Error: directory path error %s", path );
				}
				break;

			default:
				{
					sprintf_s( errorString, MAX_PATH, "FilePath Error: unknown error %s", path );
				}
				break;
			}

			MessageBox( NULL, errorString, "Game Server", MB_OK | MB_ICONERROR );

			return false;
		}
	}
	m_strFileDBPath = path;
	return true;
}

bool CFileDB::SaveCharAllData( GamePlayer* pGamePlayer, uint8 saveType, const S2SSwitchGate* pMessage /* = NULL */ )
{
    if ( NULL == pGamePlayer)
    { return false;}
    
    // 存储的准备工作
    pGamePlayer->UpdateCommonData( BV_ForSaveDb );
    //memset( pGamePlayer->gCharInfoServer.extendData.xKillInfo, -1, sizeof(KillInfo) * MAX_KILLINFO_COUNT );
    //pGamePlayer->CopyKillInfoToData( pGamePlayer->gCharInfoServer.extendData.xKillInfo, MAX_KILLINFO_COUNT );
    pGamePlayer->_recipeManager.UpdateDataToOwner();    

    if ( saveType == EST_ExitWorld )       // 下线了, 设置下次上线需要验证2级密码
    {
		//lyh++ ,如果玩家下线的时候，如果当前地图为副本地图，则踢出副本，设置下次上线的地方在配置文件中的需要的出生点。
		 MapConfig::MapData* pMapData = pGamePlayer->GetMapData();
		 if( pMapData && pMapData->IsEctypeMap())
		 {
			
			 const MapConfig::SpecRelivePosition* pSpecRelivePosition = pGamePlayer->GetSpecRelivePosition(pMapData); //先选择优先复活点。
			 if (!pSpecRelivePosition)
				{

					MapConfig::RelivePosition* pRelivePosition = pGamePlayer->GetRelivePosition(pMapData);
					 pGamePlayer->gCharInfoServer.otherdata.pos.dwMapID  = pRelivePosition->MapId;
                   
					 pGamePlayer->gCharInfoServer.otherdata.pos.vPos.x = pRelivePosition->PositionX;
					 pGamePlayer->gCharInfoServer.otherdata.pos.vPos.y = pRelivePosition->PositionY;
					  pGamePlayer->gCharInfoServer.otherdata.pos.stX =  FloatToTile(pRelivePosition->PositionX);
					  pGamePlayer->gCharInfoServer.otherdata.pos.stY =  FloatToTile(pRelivePosition->PositionY);

					
					//ProcessReliveToMap( pRelivePosition->MapId, pRelivePosition->PositionX, pRelivePosition->PositionY, pRelivePosition->Direction, xReliveInfo );
				}
			 else //有优先复活点 
				{
					pGamePlayer->gCharInfoServer.otherdata.pos.dwMapID  = pSpecRelivePosition->MapId;

					pGamePlayer->gCharInfoServer.otherdata.pos.vPos.x = pSpecRelivePosition->PositionX;
					pGamePlayer->gCharInfoServer.otherdata.pos.vPos.y = pSpecRelivePosition->PositionY;
					 pGamePlayer->gCharInfoServer.otherdata.pos.stX =  FloatToTile(pSpecRelivePosition->PositionX);
					 pGamePlayer->gCharInfoServer.otherdata.pos.stY =  FloatToTile(pSpecRelivePosition->PositionY);

					//ProcessReliveToMap( pSpecRelivePosition->MapId, pSpecRelivePosition->PositionX, pSpecRelivePosition->PositionY, pSpecRelivePosition->Direction, xReliveInfo );
				}

		 }
		
        pGamePlayer->gCharInfoServer.otherdata.xSecondPassword.SetHaveCheck( false );
        pGamePlayer->SetTimeVar( ECT_LastOfflineTime, TimeEx::GetNowTime() );            // 下线时间
    }

    DBMsgSaveCharacter msg;
    msg.header.stID = pGamePlayer->GetID();
    msg.accountId   = pGamePlayer->GetAccountID();
    msg.savetype    = saveType;
    if ( MakeSaveMsg( pGamePlayer->m_dbinfo.dwCharacterID, pGamePlayer, msg ) )
    {
        if ( saveType == EST_ExitGameServer && pMessage != NULL )   // 如果是切服, 保存新服的地图ID
        {
            msg.dbInfo.otherdata.pos.dwMapID = EctypeId2MapId( pMessage->dwMapID );   
            msg.dbInfo.otherdata.pos.stX     = FloatToTile( pMessage->fX );
            msg.dbInfo.otherdata.pos.stY     = FloatToTile( pMessage->fY );
            msg.dbInfo.otherdata.pos.vPos.x  = pMessage->fX;
            msg.dbInfo.otherdata.pos.vPos.y  = pMessage->fY;
            msg.dbInfo.otherdata.pos.vPos.z  = WORLD_HEIGHT;			

            D3DXVECTOR3 vDir = D3DXVECTOR3( cos( pMessage->fDir ), sin( pMessage->fDir ), 0.0f );
            D3DXVec3Normalize( &vDir, &vDir );
            msg.dbInfo.otherdata.fDirX       = vDir.x;
            msg.dbInfo.otherdata.fDirY       = vDir.y;
        }
		else  if ( saveType == EST_ExitWorld )
		{
			msg.dbInfo.otherdata.SetExitTimeNow();//设置下线时间处理
			pGamePlayer->gCharInfoServer.otherdata.exitGameTime = msg.dbInfo.otherdata.exitGameTime;
		}
        GettheDBCon().SendMsg( &msg, pGamePlayer->GetLifeCode() );
        return true;
    }
    return false;
}

bool CFileDB::MakeSaveMsg( uint32 dwCharacterID, GamePlayer* pGamePlayer, DBMsgSaveCharacter& msg )
{
    //ItrCharacterDataContainer itr = _NeedSavePlayers.find( dwCharacterID );
    //if (itr != _NeedSavePlayers.end())
    //{
    //    CharData& data = itr->second;
    //    FileSaveChar* pCharData = data.pData;
    //    msg.bOpenDB             = pCharData->bOpenDB;
    //    memcpy_s( &msg.dbInfo,      sizeof(msg.dbInfo),      &(pCharData->dbInfo),      sizeof(msg.dbInfo     ));
    //    memcpy_s( &msg.runtimeInfo, sizeof(msg.runtimeInfo), &(pCharData->runtimeInfo), sizeof(msg.runtimeInfo));
    //    memcpy_s( &msg.storageInfo, sizeof(msg.storageInfo), &(pCharData->storageInfo), sizeof(msg.storageInfo));

    //    msg.shServerId          = GameServerIdPrefix + g_Cfg.dwServerID;
    //    msg.subMarker           = pCharData->nCrc;
    //    msg.dwCharacterID       = dwCharacterID;
    //    msg.dwSaveTime          = 0;
    //    msg.nPKValue            = pCharData->nPKValue;
    //    msg.stPKProtectFlag     = pCharData->stPKProtectFlag;
    //    msg.nStayInHellTime     = pCharData->nStayInHellTime;
    //    msg.nGMLevel            = pCharData->nGMLevel;

    //    return true;
    //}

    msg.bOpenDB             = pGamePlayer->m_bStorageDBFlag;
    memcpy_s( &msg.dbInfo, sizeof(msg.dbInfo), &(pGamePlayer->gCharInfoServer), sizeof(msg.dbInfo));
    pGamePlayer->BuildRuntimeInfo( msg.runtimeInfo );    
    memcpy_s( &msg.storageInfo, sizeof(msg.storageInfo), &(pGamePlayer->_StorageBag), sizeof(msg.storageInfo));
    msg.shServerId          = GameServerIdPrefix + g_Cfg.dwServerID;
    msg.subMarker           = HQ_TimeGetTime()+rand();
    msg.dwCharacterID       = dwCharacterID;
    msg.dwSaveTime          = HQ_TimeGetTime() - pGamePlayer->GetPreSaveTime();
    msg.nPKValue            = pGamePlayer->GetPKValue();
    msg.stPKProtectFlag     = pGamePlayer->GetPKMode();
    msg.nGMLevel            = pGamePlayer->m_nGMLevel;

	//在太平幻境中退出，则回到最初进来的位置
	pGamePlayer->ProcessExitGameInTPHJ(msg);

    pGamePlayer->SetPreSaveTimeNow();
    return true;
}

CFileDB& GettheFileDB()
{
    static CFileDB s_theFileDB;
    return s_theFileDB;
}

#pragma warning( pop )
