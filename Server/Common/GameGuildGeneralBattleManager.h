#pragma once
//ͬһ���͵�ͬһ��ͼ���й����ս��������
#include "BaseGameBattleManager.h"
#include "GameBattleDefine.h"
#include "GameGuildGeneralBattleConfig.h"
#include "GameGuildGeneralBattle.h"
class GameGuildGeneralBattle;
struct GameGuildGeneralBattleOnceInfo
{
	GameGuildGeneralBattleOnceInfo()
	{
		m_nConfigMapID = 0xffffffff;
		m_nLeftTime = 0;
		m_uchBattleStatus = GameBattleDefine::StatusInit;
	}
	void SetData(unsigned int IndexID,unsigned int SrcGuildID,unsigned int DestGuildID,__int64 LogBeginTime,unsigned int MapID,unsigned int nMonrySum,unsigned int nGuildMoneySum,unsigned int nGuildMessionSum)
	{
		ID =IndexID;
		RedGuildID = SrcGuildID;
		BlueGuildID = DestGuildID;
		BeginTime = LogBeginTime;
		m_nConfigMapID=MapID;
		MoneySum = nMonrySum;
		GuildMoneySum=nGuildMoneySum;
		GuildMissionSum=nGuildMessionSum;
		m_nConfigMapID = MapID;
		m_uchBattleStatus = GameBattleDefine::StatusInit;
	}
	unsigned int ID;//Ψһ���
	unsigned int RedGuildID;
	unsigned int BlueGuildID;

	__int64 BeginTime;
	//����
	unsigned int MoneySum;
	unsigned int GuildMoneySum;
	unsigned int GuildMissionSum;
	//ս��
	// ս����MapConfig ID
    unsigned int m_nConfigMapID;
    // ս��ʣ��ʱ��( ��λ: ���� )
    unsigned int m_nLeftTime;
    unsigned int m_nLastUpdateTime;
	// ս����״̬
    unsigned char m_uchBattleStatus;
	// ս��״̬ʣ��ʱ��
    unsigned int GetLeftTime() const { return m_nLeftTime; }
    void SetLeftTime( unsigned int nValue ) { m_nLeftTime = nValue; }
    void SubLeftTime( unsigned int nValue );
	// ս��MapID
    unsigned int GetMapID() const { return m_nConfigMapID; }
    void SetMapID( unsigned int nValue ) { m_nConfigMapID = nValue; }
	// ״̬
    unsigned char GetBattleStatus() const { return m_uchBattleStatus; }
    void SetBattleStatus( unsigned char uchValue ){ m_uchBattleStatus = uchValue; }

	void SetBeginTime(__int64 TimeLog){BeginTime = TimeLog;}
	void SetRedGuildID(unsigned int ID){RedGuildID =ID;}
	void SetBlueGuildID(unsigned int ID){BlueGuildID =ID;}

};
inline void GameGuildGeneralBattleOnceInfo::SubLeftTime( unsigned int nValue )
{
    if ( nValue >= m_nLeftTime )
    { m_nLeftTime = 0; }
    else
    { m_nLeftTime -= nValue; }
}
class GameGuildGeneralBattleManager : public BaseGameBattleManager
{
public:
    GameGuildGeneralBattleManager();
    virtual ~GameGuildGeneralBattleManager();

	void SetConfig(GameGuildGeneralBattleConfig& pConfig){m_pConfig = pConfig;}
	virtual void RunUpdate( unsigned int nCurrentTime );
	//���ù�������
	void SetkingdomMapInfo(const int map_id,const float map_x,const float map_y);
	inline int  GetKingdomMapID(){return m_KingdomMapID;}
	inline float  GetKingdomMapX(){return m_X;}
	inline float  GetKingdomMapY(){return m_Y;}

    // ���ս��
    void AddGameBattle( GameGuildGeneralBattle* pGameBattle );

    // ����ս��
    GameGuildGeneralBattle* GetGameBattleByPlayerID( unsigned int nPlayerID );
    GameGuildGeneralBattle* GetGameBattleByUnitID( unsigned int nUnitID );
	GameGuildGeneralBattle* GetGameBattleByID(unsigned int ID);
	GameGuildGeneralBattle* GetGameBattleByOnlyMapID(unsigned int MapID);

    // ս���趨
    GameGuildGeneralBattleConfig* GetBattleConfig() { return &m_pConfig; }

    // ��ʾ�������
    virtual bool ShowGameBattleEnter(GamePlayer* pPlayer );

    // ����ս��
    virtual bool EnterGameBattle( GamePlayer* pPlayer );

    // ����ս��״̬�ı�
    virtual void ProcessChangeStatus(unsigned int ID, unsigned char uchStatus );

	GameGuildGeneralBattleOnceInfo* GetGameBattleOnceInfo(unsigned int ID);
	void AddGameGuildGeneralBattleOnceInfo(unsigned int ID,unsigned int MapID,unsigned int SrcGuildID,unsigned int DestGuildID,__int64 BeginTime,unsigned int MoneySum,unsigned int GuildMoney,unsigned int GuildMission);

	virtual void Init();
	virtual void Destroy();

	void HandleGameGuildGeneralBattleStates(unsigned int ID);

	void KillGameBattleMonster( unsigned char uchFight, unsigned int nPlayerID, int nMonsterID ,unsigned int MapID);
protected:	
	// ����ս����ʼ��״̬
    virtual void ProcessBattleInitStatus(unsigned int ID,__int64 NowTime);

    // ����ս������״̬
    virtual void ProcessBattleEnterStatus(unsigned int ID,__int64 NowTime);

    // ����ս��ս��״̬
    virtual void ProcessBattleFightStatus(unsigned int ID,__int64 NowTime);

    // ����ս������״̬
    virtual void ProcessBattleEndStatus(unsigned int ID,__int64 NowTime);

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // ����ת��������״̬�߼�
    virtual void ProcessChangeToSignUpStatus(unsigned int ID);

    // ����ת����׼��״̬�߼�
    virtual void ProcessChangeToPrepareStatus(unsigned int ID);

    // ����ת��������״̬�߼�
    virtual void ProcessChangeToEnterStatus(unsigned int ID);

    // ����ת����ս��״̬�߼�
	virtual void ProcessChangeToFightStatus(unsigned int ID);

	// ����ת����������״̬�߼�
	virtual void ProcessChangeToEndStatus(unsigned int ID){};
    //////////////////////////////////////////////////////////////////////////////////////////////
    // ����ս��״̬�ı���Ϣ
    virtual void SendBattleStatusMessage(unsigned int ID, unsigned char uchStatus );

    // ����ս��ʣ��ʱ��
    void ProcessBattleLeftTime( unsigned int ID,unsigned int nCurrentTime );
protected:
	typedef std::map< unsigned int, GameGuildGeneralBattle* > GameBattleMap;
    typedef GameBattleMap::iterator GameBattleMapIter;

    // ����ս����map
    GameBattleMap m_mapGameBattle;

	// ��Ӧ���ҵ�����λ��(��Ҫ�����ɵ�ͼ,��֤��GAME SERVER����ս��������ȷִ��)
	int m_KingdomMapID;
	float m_X;
	float m_Y;

	int	m_BattleValue;//ս���Ľ���ֵ
	bool m_BattleValueIsOpen;

	std::map<unsigned int,GameGuildGeneralBattleOnceInfo> m_pInfoList;//���ݵļ���
	GameGuildGeneralBattleConfig m_pConfig;//�����ļ��Ķ���
};
inline GameGuildGeneralBattleOnceInfo* GameGuildGeneralBattleManager::GetGameBattleOnceInfo(unsigned int ID)
{
	if(m_pInfoList.count(ID) == 1)
		return &m_pInfoList[ID];
	else
		return NULL;
}