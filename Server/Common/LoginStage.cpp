#include "LoginStage.h"
#include "ShareData.h"
#include "GamePlayer.h"
#include "BaseCharacter.h"

#include "Configure.h"

LoginStage& GetTheLoginStage()
{
    static LoginStage instance; 
    return instance;
}

LoginStage::LoginStage() : m_dwLastProcessTime(0), m_dwCostTime(0)
{
	m_bOpenService = false;
}

LoginStage::~LoginStage()
{    
}

void LoginStage::UnInit()
{
    ItrCharacterIdContainer it    = _charIDs.begin();
    ItrCharacterIdContainer itEnd = _charIDs.end();
    for ( ; it!=itEnd; ++it)
    {
        theRunTimeData.ReleaseObject( *it, __FILE__, __LINE__ );
    }
    _charIDs.clear();
    _charIDQueues.clear();
}

bool LoginStage::KickCharByAccount( unsigned int dwAccount )
{   
    ItrCharacterIdContainer it    = _charIDs.begin();
    ItrCharacterIdContainer itEnd = _charIDs.end();
    for ( ; it!=itEnd; )
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( *it );
        if ( pChar==NULL )
        {
            it = _charIDs.erase( it );
            continue;
        }

        if ( !pChar->IsPlayer())
        {
            it = _charIDs.erase( it );
            continue;
        }

        GamePlayer* pGamePlayer = (GamePlayer*)(pChar);
	    if ( pGamePlayer == NULL )
	    {
            it = _charIDs.erase( it );
            continue;
	    }

        if ( pGamePlayer->GetAccountID() == dwAccount )
        {
            pGamePlayer->Log( "Exit By KickCharByAccount" );
            pGamePlayer->ExitWorld(__FUNCTION__, __FILE__, __LINE__);
            return true;
        }

        ++it;
    }

    return false;
}

void LoginStage::Run()
{
	DECLARE_TIME_TEST
    if (m_dwLastProcessTime == 0)
        m_dwLastProcessTime = HQ_TimeGetTime();

    m_dwCostTime = HQ_TimeGetTime() - m_dwLastProcessTime;
    m_dwLastProcessTime = HQ_TimeGetTime();

    ItrCharacterIdContainer it    = _charIDs.begin();
    ItrCharacterIdContainer itEnd = _charIDs.end();
	BEGIN_TIME_TEST( "LoginStage[5]" );
    for ( ; it!=itEnd;)
    {
		DECLARE_TIME_TEST
		BEGIN_TIME_TEST( "LoginStage[1]" );
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( *it );
        if( pChar == NULL )
        {
            //// 排队修改
            LeaveQueue( *it );
			it = _charIDs.erase( it );
            continue;
        }
		END_TIME_TEST_1( "LoginStage[1]",100 );
		BEGIN_TIME_TEST( "LoginStage[2]" );
        GamePlayer* pGamePlayer = (GamePlayer*)pChar;
		pChar->Run(m_dwCostTime);        
		END_TIME_TEST_1( "LoginStage[2]",100 );

		BEGIN_TIME_TEST( "LoginStage[3]" );
        if ( !pGamePlayer->IsInLoginStage())
        { // 在Run之后，玩家已经离开游戏 或者 已经进入正常的游戏场景
            //// 排队修改
            LeaveQueue( *it );
            it = _charIDs.erase( it );
            continue; 
        }
		END_TIME_TEST_1( "LoginStage[3]",100 );
        // 排队修改
		BEGIN_TIME_TEST( "LoginStage[4]" );
		if ( g_Cfg.dwServerID == CHARACTERSERVERID && 
			pGamePlayer->GetLastEnterWorldTime() != 0 && 
			HQ_TimeGetTime() - pGamePlayer->GetLastEnterWorldTime() > 30000 )
		{
		   // 超过10秒没有发进入游戏请求 踢他呀的
		   //// 排队修改
		   LeaveQueue( *it );
		   pGamePlayer->OnExit( NULL,ET_ExitGame );
		   it = _charIDs.erase( it );
		   continue;
		}
		END_TIME_TEST_1( "LoginStage[4]",100 );
        ++it;
    }
	END_TIME_TEST_1( "LoginStage[5]",100 );
}

int LoginStage::EnterQueue( GameObjectId stID )
{ // 进入排队
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( stID );
    if ( !pChar || !pChar->IsPlayer())
    { return -1; }

    _charIDQueues.push_back( stID );
    return _charIDQueues.size() - 1;
}

int LoginStage::LeaveQueue( GameObjectId stID )
{
    _charIDQueues.remove( stID );
    return _charIDQueues.size();
}

int LoginStage::GetLoginQueuePos( GameObjectId stID )
{
    ItrCharacterIdContainer it    = _charIDQueues.begin();
    ItrCharacterIdContainer itEnd = _charIDQueues.end();
    
    for (int i=0; it!=itEnd; ++it, ++i )
    {
        if ( *it == stID )
        { return i;}
    }
    return -1;
}

bool LoginStage::Enter( GameObjectId stID )
{   
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( stID );
    if ( !pChar || !pChar->IsPlayer())
        return false;
    
    // 是否在队列中
    if ( IsExist( stID ))
        return false;

    // 放入队列
    _charIDs.push_back( stID );
    return true;
}

bool LoginStage::IsExist( GameObjectId stID )
{
    ItrCharacterIdContainer it = std::find( _charIDs.begin(), _charIDs.end(), stID );
    if ( it != _charIDs.end() )
        return true;
    
    return false;
}
