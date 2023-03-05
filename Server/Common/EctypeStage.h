#ifndef __ECTYPTESTAGE_H__
#define __ECTYPTESTAGE_H__

#include "GameStage.h"
#include "LuaPlus/LuaPlus.h"

class EctypeStage : public GameStage
{
public:
    EctypeStage();
    virtual ~EctypeStage();

    virtual void Release() = 0;

	// �ж��Ƿ�Ҫ���� ���¼���Ƿ�Ҫ��������
    virtual void CheckStageValid();

	// ��ʼ������
    virtual bool Initialize( MapConfig::MapData* pMapData, uint32 nStageID, uint32 nMapLevel );

	// ִ�и���
    virtual void RunUpdate();

	// �����ø������� ��������������Ĭ����3����,��3�����ڼ��ǿ������»ָ���
    virtual void SetStageWaitRelease( bool bRelease ,bool bNow = false);

	// �Ƿ�ȴ�����
    virtual bool IsStageWaitingRelease();

	// �Ƿ�Ҫ����
    virtual bool IsStageRelease();

	// ���Ҫ�޳������
    virtual void CheckKickOutPlayer( BaseCharacter* pChar );

    // �����ĵȼ�
    void SetStageLevel( int nValue ) { m_nStageLevel = nValue; }
    virtual int GetStageLevel() { return m_nStageLevel; }

    // ����ʱ��
    void SetStageKeepTime( uint32 nValue );

    // ����ʣ��ʱ��
    uint32 GetStageRemainTime();

	uint32 GetStageCreateTime();
    
    virtual void RecordPlayerDeath ( GamePlayer* pPlayer );
    virtual uint16 GetPlayerDeathCount( GamePlayer* pPlayer );

    // ����ר��ID
    void SetSpecialID( uint32 dwFirstID, uint32 dwSecondID );
    bool IsSpecialID( uint32 dwID );

    virtual bool CheckCanEnterStage( GamePlayer* pPlayer );

    // ���÷ֶ��¹ֵ��¸��׶�
    void SetNextRefreshStage( int nValue ) { m_nNextRefreshStage = nValue; }

    // ��ʼ���ű� LuaInit
    uint32 InitLuaScript(); 

    // ��ʼlua��ʱ��
    void LuaStartTimer( uint8 id, uint32 interval );

    // ֹͣlua��ʱ��
    void LuaStopTimer( uint8 id );

    // ����lua��ʱ��
    void UpdateLuaTimer();

    // ���˸���, ����鸱��, ����ɸ���ԤԼ�б�
    void AddReserve( uint32 nID );
    void RemoveReserve( uint32 nID );
    bool HaveReserve( uint32 nID );

protected:
    virtual bool 			ProcessEnterStage( GamePlayer* pPlayer );
    virtual void 			ProcessLeaveStage( GamePlayer* pPlayer );
    virtual eEctypeKickType WhyKickOutPlayer ( GamePlayer* pPlayer );

    // �Ƿ���ԤԼ
    bool HaveReserve();

    // �ֶ�ˢ����
    void RefreshMonsterByStage();

    // �������뿪��ʱ��
    void ClearPlayerLeaveTime();

    // ����ԤԼ�б�
    void UpdateReserve();

protected:

    typedef std::map< uint32, uint16 > DeathCountMap;
    typedef DeathCountMap::iterator DeathCountMapIter;

    typedef std::map< uint32, uint32 > PlayerLeaveTime;
    typedef PlayerLeaveTime::iterator PlayerLeaveTimeIter;

    typedef std::map< uint32, uint32 > ReserveMap;
    typedef ReserveMap::iterator ReserveMapIter;

    // �����ȼ�( ����ȼ��Ƕ����ƽ���ȼ� ���� ���˸����ĵȼ�, Ĭ��Ϊ0, �����Ƶȼ� )
    int m_nStageLevel;

    // ��������ʱ��
    uint32 m_nStageCreateTime;

    // ����ʱ��
    uint32 m_nStageKeepTime;

    // ԤԼ�б�
    ReserveMap m_mapReserve;

    // �������ٶ�ʱ��
    GameTimerEx m_xReleaseTimer;

    // ��¼��Ҹ�����������
    DeathCountMap m_mapPlayerDeath; 

    // �������׶�ˢ�ֵĵڼ��׶�
    int m_nNextRefreshStage; 

    // ��һ��ˢ�»�ʣ����ʱ��
    int m_dwNextRefreshTime; 

    // �ϴ�ˢ��ʱ��
    int m_dwLastRefreshTime;

    // ��鳡����ר�ó�������
    std::pair< uint32, uint32 > m_pairSpecialID; 

    // ����뿪����ʱ��
    PlayerLeaveTime m_mapPlayerLeaveTime;

    // ����lua������
    LuaStateOwner _luaScript; 

    // �Ƿ��нű�
    bool _bHaveScript; 

    // ����ʱ�� ��new��̬�����²߻�Ϲ��
    GameTimerEx _timers[ StageDefine::ETimerType_Max ]; 
};

//////////////////////////////////////////////////////////////////////////////////////////
inline void EctypeStage::SetStageKeepTime(  uint32 nValue )
{
    m_nStageKeepTime = nValue;
}

inline uint32 EctypeStage::GetStageRemainTime()
{
    return m_nStageKeepTime - GameTime::GetPassTime( HQ_TimeGetTime(), m_nStageCreateTime );
}

inline uint32 EctypeStage::GetStageCreateTime()
{
	return m_nStageCreateTime;
}

inline bool EctypeStage::IsStageWaitingRelease()
{
    return m_xReleaseTimer.IsStart();
}

inline bool EctypeStage::IsStageRelease()
{
    return m_xReleaseTimer.DoneTimer();
}

inline void EctypeStage::SetSpecialID( uint32 dwFirstID, uint32 dwSecondID )
{
    m_pairSpecialID.first  = dwFirstID; 
    m_pairSpecialID.second = dwSecondID; 
}

inline bool EctypeStage::IsSpecialID( uint32 dwID )
{
    return m_pairSpecialID.first == dwID || m_pairSpecialID.second == dwID;
}

inline void EctypeStage::AddReserve( uint32 nID )
{
    m_mapReserve[ nID ] = HQ_TimeGetTime(); 
}

inline void EctypeStage::RemoveReserve( uint32 nID )
{
    m_mapReserve.erase( nID );
}

inline bool EctypeStage::HaveReserve()
{
    return !m_mapReserve.empty();
}

inline bool EctypeStage::HaveReserve( uint32 nID )
{
    ReserveMapIter iter = m_mapReserve.find( nID );

    return iter != m_mapReserve.end();
}

#endif
