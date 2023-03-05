#ifndef __CAMPBATTLEMANAGER_H__
#define __CAMPBATTLEMANAGER_H__

/************************************************************************
                ��Ӫս������Ļ���
                Filename:     CampBattleManager.h 
                MaintenanceMan Mail: lori227@live.cn

************************************************************************/
#include <map>
#include <vector>
#include "CampBattleDefine.h"
#include "BaseCampBattleManager.h"
class CampBattle;
class CampBattleConfig;
class GamePlayer;

class CampBattleManager
{
public:
    CampBattleManager();
    virtual ~CampBattleManager();

    // ����
    unsigned char GetCountryID() const { return m_uchCountryID; }
    void SetCountryID( unsigned char uchValue ) { m_uchCountryID = uchValue; }
	
    // ս��MapID
    unsigned int GetMapID() const { return m_nConfigMapID; }
    void SetMapID( unsigned int nValue ) { m_nConfigMapID = nValue; }

	//���ù�������
	void SetkingdomMapInfo(const int map_id,const float map_x,const float map_y);
	inline int  GetKingdomMapID(){return m_KingdomMapID;}
	inline float  GetKingdomMapX(){return m_X;}
	inline float  GetKingdomMapY(){return m_Y;}

    // ����
    unsigned char GetBattleType() const { return m_uchBattleType; }
    void SetBattleType( unsigned char uchValue ) { m_uchBattleType = uchValue; }
    bool IsCountryBattle() const { return m_uchBattleType == CampDefine::BattleTypeKing || m_uchBattleType == CampDefine::BattleTypeDragon || m_uchBattleType == CampDefine::BattleTypeRosefinch; }

    // ״̬
    unsigned char GetBattleStatus() const { return m_uchBattleStatus; }
    void SetBattleStatus( unsigned char uchValue ){ m_uchBattleStatus = uchValue; }

    // ս��״̬ʣ��ʱ��
    unsigned int GetLeftTime() const { return m_nLeftTime; }
    void SetLeftTime( unsigned int nValue ) { m_nLeftTime = nValue; }
    void SubLeftTime( unsigned int nValue );

    // �Զ�����
    void RunUpdate( unsigned int nCurrentTime );

    // ���һ��������ID
    void AddSignUpUnit( unsigned int nUnitID );

    // �ж��Ƿ��Ѿ�������
    bool IsSignUpUnit( unsigned int nUnitID );

    // ɾ��һ��������ID
    void RemoveSignUpUnit( unsigned int nUnitID );

    // ���ս��
    void AddCampBattle( CampBattle* pCampBattle );

    // ����ս��
    CampBattle* GetCampBattleByMapID( unsigned int nMapID );
    virtual CampBattle* GetCampBattleByPlayerID( unsigned int nPlayerID );
    CampBattle* GetCampBattleByUnitID( unsigned int nUnitID );

    // ս���趨
    const CampBattleConfig* GetBattleConfig() const { return m_pBattleConfig; }
    void SetBattleConfig( CampBattleConfig* pConfig ) { m_pBattleConfig = pConfig; }

    // ��ʾ��������
    virtual bool ShowCampBattleSignUp( GamePlayer* pPlayer );

    // ս������
    virtual bool SignUpCampBattle( GamePlayer* pPlayer ) = 0;

    // ��ʾ�������
    virtual bool ShowCampBattleEnter( GamePlayer* pPlayer ) = 0;

    // ����ս��
    virtual bool EnterCampBattle( GamePlayer* pPlayer ) = 0;

    // ����ս��״̬�ı�
    virtual void ProcessChangeStatus( unsigned char uchStatus );

    // ���͹���ս�������Ϣ
    virtual void SendCountryBattleResultMessage( unsigned int nWinID, unsigned char uchWinType,unsigned int nLoseID,unsigned int nCampBattle  )
	{
		//zhuxincong ���¿�����û��Ч��
		/*GS2CSCountryBattleResult xResult;
		xResult.uchCountryID  = GetCountryID();
		xResult.uchBattleType = GetCountryBattleType();
		xResult.nGuildID      = nWinID;
		xResult.uchWinType    = uchWinType;
		xResult.nLoseGuildID = nLoseID;
		xResult.nCampBattle = nCampBattle;
		GettheServer().SendMsgToCenterServer( &xResult );*/
	};
protected:
    // ����ս����ʼ��״̬
    virtual void ProcessBattleInitStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );

    // ����ս������״̬
    virtual void ProcessBattleSignUpStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );

    // ����ս��׼��״̬
    virtual void ProcessBattlePrepareStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );

    // ����ս������״̬
    virtual void ProcessBattleEnterStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );

    // ����ս��ս��״̬
    virtual void ProcessBattleFightStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );

    // ����ս������״̬
    virtual void ProcessBattleEndStatus();

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // �ж��Ƿ���ս������ʱ��
    bool CheckBattleSignUpTime( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );

    // �ж��Ƿ���ս��׼��ʱ��
    bool CheckBattlePrepareTime( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );

    // �ж��Ƿ���ս������ʱ��
    bool CheckBattleEnterTime( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );

    // �ж��Ƿ���ս��ս��ʱ��
    bool CheckBattleFightTime( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );

    // �ж��Ƿ���ս������ʱ��
    bool CheckBattleEndTime( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // ����ת��������״̬�߼�
    virtual void ProcessChangeToSignUpStatus();

    // ����ת����׼��״̬�߼�
    virtual void ProcessChangeToPrepareStatus() = 0;

    // ����ת��������״̬�߼�
    virtual void ProcessChangeToEnterStatus() = 0;

    // ����ת����ս��״̬�߼�
	virtual void ProcessChangeToFightStatus();

	// ����ת����������״̬�߼�
	virtual void ProcessChangeToEndStatus(){};
    //////////////////////////////////////////////////////////////////////////////////////////////
    // ����ս��״̬�ı���Ϣ
    virtual void SendBattleStatusMessage( unsigned char uchStatus );

    ////////////////////////////////////////////////////////////////////

    // ����ս��
    bool SignUpCampBattle( GamePlayer* pPlayer, unsigned int nUnitID);

    // ��ʾ������Ӫս������
    bool ShowCampBattleEnter( GamePlayer* pPlayer, unsigned int nUnitID );

    // ������Ӫս��
    bool EnterCampBattle( GamePlayer* pPlayer, unsigned int nUnitID );

    // ����ս��ʣ��ʱ��
    void ProcessBattleLeftTime( unsigned int nCurrentTime );
protected:
    typedef std::map< unsigned int, CampBattle* > CampBattleMap;
    typedef CampBattleMap::iterator CampBattleMapIter;

    typedef std::vector< unsigned int > SignUpVector;
    typedef SignUpVector::iterator SignUpVectorIter;

    typedef std::map< unsigned int, unsigned int > MatchUnitMap;
    typedef MatchUnitMap::iterator MatchUnitMapIter;

    // ����
    unsigned char m_uchCountryID;

    // ս����MapConfig ID
    unsigned int m_nConfigMapID;

    // ս��������
    unsigned char m_uchBattleType;

    // ս����״̬
    unsigned char m_uchBattleStatus;

    // ����ս����map
    CampBattleMap m_mapCampBattle;

    // ���汨����vector
    SignUpVector m_vecSignUp;

    // ���������Ϣ�б�
    MatchUnitMap m_mapMatchUnit;

    // �����趨
    CampBattleConfig* m_pBattleConfig;

    // ս��ʣ��ʱ��( ��λ: ���� )
    unsigned int m_nLeftTime;
    unsigned int m_nLastUpdateTime;

	// ��Ӧ���ҵ�����λ��(��Ҫ�����ɵ�ͼ,��֤��GAME SERVER����ս��������ȷִ��)
	int m_KingdomMapID;
	float m_X;
	float m_Y;

	int	m_BattleValue;//ս���Ľ���ֵ
	bool m_BattleValueIsOpen;
};

inline void CampBattleManager::SubLeftTime( unsigned int nValue )
{
    if ( nValue >= m_nLeftTime )
    { m_nLeftTime = 0; }
    else
    { m_nLeftTime -= nValue; }
}

#endif