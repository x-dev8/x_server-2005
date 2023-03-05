#ifndef __CAMPBATTLE_H__
#define __CAMPBATTLE_H__

/************************************************************************
                ��Ӫս���Ļ���, ������Ӫս�����ɼ̳д���
                Filename:     CampBattle.h 
                MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include <map>
#include "CampBattleDefine.h"
#include "GameTimer.h"
#include "Memory_Pool.h"

struct Msg;
class GamePlayer;
class BaseCharacter;
class CampBattleManager;

class CampBattle
{
public:
    CampBattle();
    virtual ~CampBattle(){};

    // ������Ӫս��
    template< class T > 
    static CampBattle* CreateBattle() { return CNewWithDebug< T >::Alloc( 1, "����CreateBattleʵ��" ); }

    // �ͷ���Ӫս��
    template< class T > 
    void ReleaseBattle( T* pCampBattle ) { CNewWithDebug< T >::Free( pCampBattle ); }
    virtual void Release() = 0;

    // ������ͼID
    unsigned int GetBattleMapID() const;
    void SetBattleMapID( unsigned int nValue );

    // ս���趨
    const CampBattleManager* GetBattleManager() const;
    void SetBattleManager( CampBattleManager* pManager );

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

    unsigned int GetCampBattleResource( unsigned char uchFightCamp );

    // ʤ����Դ��
    unsigned int GetWinResource() const;
    void SetWinResource( unsigned int nValue );

    // ս�����
    void AddBattlePlayer( unsigned int nPlayerID, BattlePlayer& xPlayer );
    BattlePlayer* GetBattlePlayer( unsigned int nPlayerID );
    int GetBattlePlayerCount( unsigned char uchFightCamp );

    // ��ø��������
    virtual unsigned int GetReliveIndex( GamePlayer* pPlayer );
    
     // ִ�и���
    unsigned char RunUpdate( unsigned int nCurrentTime );

    // ������Ӫ��Ϣ
    void SendCampMessage( Msg* pMessage, unsigned char uchFightCamp );

    // ����ս��ɱ��
    virtual void ProcessKillPlayer( BaseCharacter* pKiller, GamePlayer* pBeKill );

    // ����ս������
    void ProcessAddCampResource( unsigned char uchFightCamp, unsigned int nAddResource );

    // ����ս��״̬�ı�
    void ProcessStatusChange( unsigned char uchStatus );

    // ����ս�������Ϣ
    void SendBattlePlayerMessage( GamePlayer* pPlayer, unsigned char uchFightCamp );

    // �����Ƿ�μ���Ӫս����Ϣ
    virtual void SendEnterCampBattleMessage() = 0;

    // ����ɱ������
    virtual void KillCampBattleMonster( unsigned char uchFightCamp, unsigned int nPlayerID, int nMonsterID );

    // ����ս��״̬��Ϣ
    void SendBattleStatusMessage( GamePlayer* pPlayer = NULL );

    // ���Ͷ���˫����Ϣ
    void SendCampBattleMatchMessage( GamePlayer* pPlayer );

    // �����Ӫ��Ϣ
    unsigned char GetBattleFightCamp( unsigned int nUnitID );

    // ������ҵ���, �˳���Ϸ�߼�
    virtual void ProcessBattlePlayerOutLine( GamePlayer* pPlayer ){};
protected:

    // ����ս������״̬
    virtual void ProcessCampBattleEnterStatus(){};

    // ����ս��ս��״̬
    virtual void ProcessCampBattleFightStatus();

    // ����ս������״̬
    virtual void ProcessCampBattleEndStatus();

    // ����ı䵽ս��ս��״̬
    virtual void ProcessChangeToFightStatus();

    // ����ı䵽ս������״̬
    virtual void ProcessChangeToEndStatus();

    // ����ս�����
    void ProcessCalcCampBattleWinner();

    // ����ս�����
    virtual void ProcessCampBattleResult( unsigned char uchFightCamp ) = 0;

    // �����һ��ɱ��
    void PorcessFirstKillPlayer( const char* szKillerName, const char* szBeKillName );

    // ��������ɱ��
    void ProcessKeepKillPlayer( const char* szKillerName, int nKillCount, const char* szBeKillName );

    // ����ɱ
    void ProcessBeKillByPlayer( const char* szKillerName, BattlePlayer* pBeKillBattlePlayer );

    // ����ȫ����ɱ��
    void ProcessTotalKillPlayer( BattlePlayer* pKillerBattlePlayer, BattlePlayer* pBeKillBattlePlayer );

protected:
    typedef std::map< unsigned int, BattlePlayer > BattlePlayerMap;
    typedef BattlePlayerMap::iterator BattlePlayerMapIter;

    // �����趨
    CampBattleManager* m_pBattleManager;

    // �趨ʤ���Ļ���
    unsigned int m_nWinResource;

    // �����ĸ�����ͼID
    unsigned int m_nEctypeMapID;

    // ս��״̬
    unsigned char m_uchStatus;

    // �Ƿ��һ��ɱ��( ��˵�е�һѪ )
    bool m_bFirstKill;      

    // ս������˫��ID
    unsigned int m_nRedID;
    unsigned int m_nBlueID;

    // �����ս������б�
    BattlePlayerMap m_mapBattlePlayer;
    
    // ����
    unsigned int m_nRedResource;
    unsigned int m_nBlueResource;

	unsigned int m_RedTotleKillSum;
	unsigned int m_BlueTotleKillSum;


    // ս�����ٶ�ʱ��
    GameTimerEx m_xReleaseTimer;
};

inline unsigned int CampBattle::GetBattleMapID() const
{
    return m_nEctypeMapID;
}

inline void CampBattle::SetBattleMapID( unsigned int nValue )
{
    m_nEctypeMapID = nValue;
}

inline const CampBattleManager* CampBattle::GetBattleManager() const
{
    return m_pBattleManager;
}

inline void CampBattle::SetBattleManager( CampBattleManager* pManager )
{
    m_pBattleManager = pManager;
}

inline unsigned char CampBattle::GetStatus() const
{
    return m_uchStatus;
}

inline void CampBattle::SetStatus( unsigned char uchValue )
{
    m_uchStatus = uchValue;
}

inline bool CampBattle::GetFirstKill() const
{
    return m_bFirstKill;
}

inline void CampBattle::SetFirstKill( bool bValue )
{
    m_bFirstKill = bValue;
}

inline unsigned int CampBattle::GetRedID() const
{
    return m_nRedID;
}

inline void CampBattle::SetRedID( unsigned int nValue )
{
    m_nRedID = nValue;
}

inline unsigned int CampBattle::GetBlueID() const
{
    return m_nBlueID;
}

inline void CampBattle::SetBlueID( unsigned int nValue )
{
    m_nBlueID = nValue;
}

inline unsigned int CampBattle::GetRedResource() 
{
    return m_nRedResource;
}

inline void CampBattle::SetRedResource( unsigned int nValue )
{
	int ChangeValue = static_cast<int>(nValue);
	if(ChangeValue <0)
		ChangeValue = 0;
    m_nRedResource = ChangeValue;
}


inline void CampBattle::AddRedResource( unsigned int nValue )
{
    m_nRedResource += nValue;
}

inline unsigned int CampBattle::GetBlueResource() 
{
    return m_nBlueResource;
}

inline void CampBattle::SetBlueResource( unsigned int nValue )
{
	int ChangeValue = static_cast<int>(nValue);
	if(ChangeValue <0)
		ChangeValue = 0;
    m_nBlueResource = ChangeValue;
}

inline void CampBattle::AddBlueResource( unsigned int nValue )
{
    m_nBlueResource += nValue;
}


inline unsigned int CampBattle::GetWinResource() const
{
    return m_nWinResource;
}

inline void CampBattle::SetWinResource( unsigned int nValue )
{
    m_nWinResource = nValue;
}

#endif