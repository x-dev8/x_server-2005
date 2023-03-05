#pragma once
#include "Singleton.h"
#include "GlobalDBMessage.h"
#include "RunStatus.h"
enum GlobalDBUpdate
{
	UpdateBattleSum = 0,
	UpdateMapCountryID = 1,
	UpdateTimeHandleLog = 2,
	UpdateTimeHandleState = 3,
};
template< class T >
class GlobalDBManager : public ISingletion< GlobalDBManager< T > >
{
public:
	GlobalDBManager();
	~GlobalDBManager(){m_GlobalDB.Destroy();};

	//从数据库读取全部的数据 或者是从center读取全部的数据
	void InitGlobalDB();
	// 设置是否加载完成
	void SetLoadSuccess( bool bValue );

	//保存数据到数据库 或者是保存数据到center
	void SaveGlobalDB();

	//设置数据
	void LoadGlobalDB(GlobalDB& info);

	void UpdateGlobalDBData( unsigned char uchType,unsigned int Index, __int64 n64Value );
	const GlobalDB& GetGlobalDB() const {return m_GlobalDB;}

	unsigned int GetBattleSum(){return m_GlobalDB.GetBattleSum();}
	void SetBattleSum(unsigned int Value);

	unsigned int GetMapCountryID(){return m_GlobalDB.GetMapCountryID();}
	void SetMapCountryID(unsigned int Value);

	__int64 GetTimeHandleLog(unsigned int Index){return m_GlobalDB.GetTimeHandleLog(Index);}
	void SetTimeHandleLog(unsigned int Index,__int64 Value);

	int GetTimeHandleState(unsigned int Index){return m_GlobalDB.GetTimeHandleState(Index);}
	void SetTimeHandleState(unsigned int Index,int Value);
private:
	void SendUpdateGlobalDBDataMessage( unsigned char uchType,unsigned int Index, __int64 n64Value );
private:
	GlobalDB m_GlobalDB;
	bool _bLoadSuccess;
};

template < class T >
GlobalDBManager<T>::GlobalDBManager()
{
	_bLoadSuccess = false;
}

template < class T >
void GlobalDBManager<T>::SetLoadSuccess( bool bValue )
{
	_bLoadSuccess = bValue;
	if (bValue)
	{
		theRunStatus.SetLoadSuccess(RunStatusDefine::LoadGlobalDBSuccess);
	}
}

template< class T >
void GlobalDBManager< T >::UpdateGlobalDBData( unsigned char uchType,unsigned int Index, __int64 n64Value )
{
    switch( uchType )
    {
    case UpdateBattleSum:
		m_GlobalDB.SetBattleSum(static_cast< unsigned int >( n64Value ));
		break;
	case UpdateMapCountryID:
		m_GlobalDB.SetMapCountryID(static_cast< unsigned int >( n64Value ));
		break;
	case UpdateTimeHandleLog:
		m_GlobalDB.SetTimeHandleLog(Index,n64Value);
		break;
	case UpdateTimeHandleState:
		m_GlobalDB.SetTimeHandleState(Index,static_cast< int >(n64Value));
		break;
    default:
        return;
    }
    SendUpdateGlobalDBDataMessage( uchType,Index,n64Value );
}
class ClientPeer;
typedef GlobalDBManager<ClientPeer> CenterGlobalDBManager;
#define theCenterGlobalDBManager CenterGlobalDBManager::Instance()

class GamePlayer;
typedef GlobalDBManager<GamePlayer> GameGlobalDBManager;
#define theGameGlobalDBManager GameGlobalDBManager::Instance()