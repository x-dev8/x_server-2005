#ifndef __CAMPCOUNTRYBATTLEMANAGER_H__
#define __CAMPCOUNTRYBATTLEMANAGER_H__

/************************************************************************
            国家战场管理
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

    // 发送战场结果消息给CenterServer
    virtual void SendCountryBattleResultMessage( unsigned int nWinID, unsigned char uchWinType ,unsigned int nLoseID = NULL,unsigned int nCampBattle = NULL);

public:
	static CampCountryBattleManager& Instance()
	{
		static CampCountryBattleManager cth;
		return cth;
	}

	unsigned int GetGuildStrength(){ return m_nGuildStrength;}

protected:
    // 处理转换到准备状态逻辑
    virtual void ProcessChangeToPrepareStatus();

    // 处理转换到进入状态逻辑
    virtual void ProcessChangeToEnterStatus();

	virtual void ProcessChangeToFightStatus();

private:
    // 国家战场类型( 国王争夺战, 青龙争夺战, 朱雀争夺战 )
    unsigned char m_uchCountryBattleType;

    // 帮派报名时的帮派实力
    unsigned int m_nGuildStrength;

    // 报名成功的帮派
    unsigned int m_nSignUpGuildID;
};
#define  theCampCountry CampCountryBattleManager::Instance()
#endif