#pragma once
//����Լսս��
#include "BaseGameBattle.h"
#include "Memory_Pool.h"
#include "MonsterBaseEx.h"
#include "GameGuildGeneralBattleManager.h"
#include "GamePlayer.h"
class GameGuildGeneralBattleManager;
class GameGuildGeneralBattle : public BaseGameBattle, INHERIT_POOL_PARAM( GameGuildGeneralBattle, 25 )
{
public:
    GameGuildGeneralBattle();
	~GameGuildGeneralBattle(){}

	virtual unsigned char  RunUpdate( unsigned int nCurrentTime );

	unsigned int GetBattleIndexID(){return m_ID;}
	void SetData(unsigned int ID,unsigned int nMoneySum,unsigned int nGuildMoneySum,unsigned int nGuildMission);

	// ������Ӫս��
    template< class T > 
    static GameGuildGeneralBattle* CreateGameGuildGeneralBattle() { return CNewWithDebug< T >::Alloc( 1, "����CreateBattleʵ��" ); }

    // �ͷ���Ӫս��
    template< class T > 
    void ReleaseGameGuildGeneralBattle( T* pGameBattle ) { CNewWithDebug< T >::Free( pGameBattle ); }

    // ������ͼID
    unsigned int GetBattleMapID() const;
    void SetBattleMapID( unsigned int nValue );

    // ״̬
    unsigned char GetStatus() const;
    void SetStatus( unsigned char uchValue );

    // һѪ
    bool GetFirstKill() const;
    void SetFirstKill( bool bValue );

    // �췽ID
    unsigned int GetRedID() const;
    void SetRedID( unsigned int nValue );

    // ����ID
    unsigned int GetBlueID() const;
    void SetBlueID( unsigned int nValue );

    // �췽��Դ��
    unsigned int GetRedResource() ;
    void SetRedResource( unsigned int nValue );
    void AddRedResource( unsigned int nValue );

    // ������Դ��
    unsigned int GetBlueResource() ;
    void SetBlueResource( unsigned int nValue );
    void AddBlueResource( unsigned int nValue );

    unsigned int GetGameBattleResource( unsigned char uchFight );

    // ʤ����Դ��
    unsigned int GetWinResource() const;
    void SetWinResource( unsigned int nValue );

    // ս�����
    void AddBattlePlayer( unsigned int nPlayerID, GameBattleDefine::BattlePlayer& xPlayer );
    GameBattleDefine::BattlePlayer* GetBattlePlayer( unsigned int nPlayerID );
    int GetBattlePlayerCount( unsigned char uchFight );

    // ��ø��������
    virtual unsigned int GetReliveIndex( GamePlayer* pPlayer );

    // ������Ӫ��Ϣ
    void SendGameBattleMessage( Msg* pMessage, unsigned char uchFight );

    // ����ս��ɱ��
    virtual void ProcessKillPlayer( BaseCharacter* pKiller, GamePlayer* pBeKill );

    // ����ս������
    void ProcessAddGameBattleResource( unsigned char uchFight, unsigned int nAddResource );

    // ����ս��״̬�ı�
    void ProcessStatusChange( unsigned char uchStatus );

    // ����ս�������Ϣ
    void SendBattlePlayerMessage( GamePlayer* pPlayer, unsigned char uchFight );

    // ����ս��״̬��Ϣ
    void SendBattleStatusMessage( GamePlayer* pPlayer = NULL );

    // ���Ͷ���˫����Ϣ
    void SendGameBattleMatchMessage( GamePlayer* pPlayer );

    // �����Ӫ��Ϣ
    unsigned char GetGameBattleFight( unsigned int nUnitID );

    // ������ҵ���, �˳���Ϸ�߼�
    virtual void ProcessBattlePlayerOutLine( GamePlayer* pPlayer ){};

	virtual void Release();
    virtual void SendEnterGameBattleMessage();

    virtual void KillGameBattleMonster( unsigned char uchFight, unsigned int nPlayerID, int nMonsterID );
	
	void SetGuildGameBattleTimeMap();

	virtual void Init();
	virtual void Destroy();

	GameGuildGeneralBattleManager* GetGameBattleManager() {return m_pManager;}
	void SetGameBattleManager(GameGuildGeneralBattleManager* nGameBattleManager){m_pManager = nGameBattleManager;}
protected:
	class RefreshIndex
    {
    public:
        RefreshIndex() : nRedIndex( 0 ), nBlueIndex( 0 ), nMaxRedIndex( 0 ), nMaxBlueIndex( 0 ){}

        int GetRedIndex() { return nRedIndex; }
        int GetBlueIndex() { return nBlueIndex; }
        int GetMaxRedIndex() { return nMaxRedIndex; }
        int GetMaxBlueIndex() { return nMaxBlueIndex; }

        void SetRedIndex( int nValue ) { nRedIndex = nValue; }
        void SetBlueIndex( int nValue ) { nBlueIndex = nValue; }
        void SetMaxRedIndex( int nValue ) { nMaxRedIndex = nValue; }
        void SetMaxBlueIndex( int nValue ) { nMaxBlueIndex = nValue; }
    private:
        int nRedIndex;
        int nMaxRedIndex;
        int nBlueIndex;
        int nMaxBlueIndex;
    };
    virtual void ProcessGameBattleEnterStatus();
    void ProcessRefreshNormalMonster();
	void ProcessBoss();
    void SendGameBattleResourceMessage();


    void ProcessRefreshGameBattleMonster();
    // ����ս��ս��״̬
    virtual void ProcessGameBattleFightStatus();

    // ����ս������״̬
    virtual void ProcessGameBattleEndStatus();

    // ����ı䵽ս��ս��״̬
    virtual void ProcessChangeToFightStatus();

    // ����ı䵽ս������״̬
    virtual void ProcessChangeToEndStatus();

    // ����ս�����
    void ProcessCalcGameBattleWinner();

    // ����ս�����
    virtual void ProcessGameBattleResult( unsigned char uchFight );

    // �����һ��ɱ��
    void PorcessFirstKillPlayer( const char* szKillerName, const char* szBeKillName );

    // ��������ɱ��
    void ProcessKeepKillPlayer( const char* szKillerName, int nKillCount, const char* szBeKillName );

    // ����ɱ
    void ProcessBeKillByPlayer( const char* szKillerName, GameBattleDefine::BattlePlayer* pBeKillBattlePlayer );

    // ����ȫ����ɱ��
    void ProcessTotalKillPlayer( GameBattleDefine::BattlePlayer* pKillerBattlePlayer, GameBattleDefine::BattlePlayer* pBeKillBattlePlayer );
private:
	// ս������˫��ID
	unsigned int m_ID;
    unsigned int m_nRedID;
    unsigned int m_nBlueID;
	unsigned int MoneySum;
	unsigned int GuildMoneySum;
	unsigned int GuildMession;

	typedef std::map< unsigned int, GameBattleDefine::BattlePlayer > BattlePlayerMap;
    typedef BattlePlayerMap::iterator BattlePlayerMapIter;

    // �趨ʤ���Ļ���
    unsigned int m_nWinResource;

    // �����ĸ�����ͼID
    unsigned int m_nEctypeMapID;

    // ս��״̬
    unsigned char m_uchStatus;

    // �Ƿ��һ��ɱ��( ��˵�е�һѪ )
    bool m_bFirstKill;      

    

    // �����ս������б�
    BattlePlayerMap m_mapBattlePlayer;
    
    // ����
    unsigned int m_nRedResource;
    unsigned int m_nBlueResource;

	unsigned int m_RedTotleKillSum;
	unsigned int m_BlueTotleKillSum;

    // ս�����ٶ�ʱ��
    GameTimerEx m_xReleaseTimer;

	GameTimerEx m_xRefreshTimer; // ˢ�ֶ�ʱ��
	std::map<int,GameTimerEx> m_xNormalTimer ; // Normal��ˢ��

    typedef std::map< int, RefreshIndex > RefreshIndexMap;
    typedef RefreshIndexMap::iterator RefreshIndexMapIter;
   
    RefreshIndexMap m_mapRefreshIndex; // ˢ���趨

	vector<GameObjectId> m_RedBarracks;
	MonsterBaseEx* m_RedBoss;
	vector<GameObjectId> m_BlueBarracks;
	MonsterBaseEx* m_BlueBoss;
	int m_RedBarracksDeadSum;
	int m_BlueBarracksDeadSum;

	GameGuildGeneralBattleManager* m_pManager;//������
};
inline void GameGuildGeneralBattle::SetData(unsigned int ID,unsigned int nMoneySum,unsigned int nGuildMoneySum,unsigned int nGuildMission)
{
	m_ID = ID;
	MoneySum = nMoneySum;
	GuildMoneySum = nGuildMoneySum;
	GuildMession= nGuildMission;
}
inline unsigned int GameGuildGeneralBattle::GetBattleMapID() const
{
    return m_nEctypeMapID;
}

inline void GameGuildGeneralBattle::SetBattleMapID( unsigned int nValue )
{
    m_nEctypeMapID = nValue;
}

inline unsigned char GameGuildGeneralBattle::GetStatus() const
{
    return m_uchStatus;
}

inline bool GameGuildGeneralBattle::GetFirstKill() const
{
    return m_bFirstKill;
}

inline void GameGuildGeneralBattle::SetFirstKill( bool bValue )
{
    m_bFirstKill = bValue;
}

inline unsigned int GameGuildGeneralBattle::GetRedID() const
{
    return m_nRedID;
}

inline void GameGuildGeneralBattle::SetRedID( unsigned int nValue )
{
    m_nRedID = nValue;
}

inline unsigned int GameGuildGeneralBattle::GetBlueID() const
{
    return m_nBlueID;
}

inline void GameGuildGeneralBattle::SetBlueID( unsigned int nValue )
{
    m_nBlueID = nValue;
}

inline unsigned int GameGuildGeneralBattle::GetRedResource() 
{
    return m_nRedResource;
}

inline void GameGuildGeneralBattle::SetRedResource( unsigned int nValue )
{
	int ChangeValue = static_cast<int>(nValue);
	if(ChangeValue<0)
		ChangeValue = 0;
    m_nRedResource = ChangeValue;
}


inline void GameGuildGeneralBattle::AddRedResource( unsigned int nValue )
{
    m_nRedResource += nValue;
}

inline unsigned int GameGuildGeneralBattle::GetBlueResource() 
{
    return m_nBlueResource;
}

inline void GameGuildGeneralBattle::SetBlueResource( unsigned int nValue )
{
	int ChangeValue = static_cast<int>(nValue);
	if(ChangeValue<0)
		ChangeValue = 0;
    m_nBlueResource = ChangeValue;
}

inline void GameGuildGeneralBattle::AddBlueResource( unsigned int nValue )
{
    m_nBlueResource += nValue;
}


inline unsigned int GameGuildGeneralBattle::GetWinResource() const
{
    return m_nWinResource;
}

inline void GameGuildGeneralBattle::SetWinResource( unsigned int nValue )
{
    m_nWinResource = nValue;
}