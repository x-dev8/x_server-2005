#ifndef __CAMPCOUNTRYBATTLEMANAGER_H__
#define __CAMPCOUNTRYBATTLEMANAGER_H__

/************************************************************************
            ����ս������
            FileName    CampCountryBattleManager.h
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "CampBattleManager.h"

class CampCountryBattleManager : public CampBattleManager
{
public:
    CampCountryBattleManager();
    virtual ~CampCountryBattleManager(){};

    virtual bool SignUpCampBattle( GamePlayer* pPlayer );

    virtual bool ShowCampBattleEnter( GamePlayer* pPlayer );

    virtual bool EnterCampBattle( GamePlayer* pPlayer );

    void SetCountryBattleType( unsigned char uchValue ) { m_uchCountryBattleType = uchValue; }
    unsigned char GetCountryBattleType() const { return m_uchCountryBattleType; }

    unsigned int GetSignUpGuildID() const { return m_nSignUpGuildID; }

    // ����ս�������Ϣ��CenterServer
    virtual void SendCountryBattleResultMessage( unsigned int nWinID, unsigned char uchWinType ,unsigned int nLoseID = NULL,unsigned int nCampBattle = NULL);

public:
	static CampCountryBattleManager& Instance()
	{
		static CampCountryBattleManager cth;
		return cth;
	}

	unsigned int GetGuildStrength(){ return m_nGuildStrength;}

protected:
    // ����ת����׼��״̬�߼�
    virtual void ProcessChangeToPrepareStatus();

    // ����ת��������״̬�߼�
    virtual void ProcessChangeToEnterStatus();

	virtual void ProcessChangeToFightStatus();

private:
    // ����ս������( ��������ս, ��������ս, ��ȸ����ս )
    unsigned char m_uchCountryBattleType;

    // ���ɱ���ʱ�İ���ʵ��
    unsigned int m_nGuildStrength;

    // �����ɹ��İ���
    unsigned int m_nSignUpGuildID;
};
#define  theCampCountry CampCountryBattleManager::Instance()
#endif