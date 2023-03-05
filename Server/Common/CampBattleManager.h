#ifndef __CAMPBATTLEMANAGER_H__
#define __CAMPBATTLEMANAGER_H__

/************************************************************************
                阵营战场管理的基类
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

    // 国家
    unsigned char GetCountryID() const { return m_uchCountryID; }
    void SetCountryID( unsigned char uchValue ) { m_uchCountryID = uchValue; }
	
    // 战场MapID
    unsigned int GetMapID() const { return m_nConfigMapID; }
    void SetMapID( unsigned int nValue ) { m_nConfigMapID = nValue; }

	//设置国家主城
	void SetkingdomMapInfo(const int map_id,const float map_x,const float map_y);
	inline int  GetKingdomMapID(){return m_KingdomMapID;}
	inline float  GetKingdomMapX(){return m_X;}
	inline float  GetKingdomMapY(){return m_Y;}

    // 类型
    unsigned char GetBattleType() const { return m_uchBattleType; }
    void SetBattleType( unsigned char uchValue ) { m_uchBattleType = uchValue; }
    bool IsCountryBattle() const { return m_uchBattleType == CampDefine::BattleTypeKing || m_uchBattleType == CampDefine::BattleTypeDragon || m_uchBattleType == CampDefine::BattleTypeRosefinch; }

    // 状态
    unsigned char GetBattleStatus() const { return m_uchBattleStatus; }
    void SetBattleStatus( unsigned char uchValue ){ m_uchBattleStatus = uchValue; }

    // 战场状态剩余时间
    unsigned int GetLeftTime() const { return m_nLeftTime; }
    void SetLeftTime( unsigned int nValue ) { m_nLeftTime = nValue; }
    void SubLeftTime( unsigned int nValue );

    // 自动更新
    void RunUpdate( unsigned int nCurrentTime );

    // 添加一个报名的ID
    void AddSignUpUnit( unsigned int nUnitID );

    // 判断是否已经报名了
    bool IsSignUpUnit( unsigned int nUnitID );

    // 删除一个报名的ID
    void RemoveSignUpUnit( unsigned int nUnitID );

    // 添加战场
    void AddCampBattle( CampBattle* pCampBattle );

    // 查找战场
    CampBattle* GetCampBattleByMapID( unsigned int nMapID );
    virtual CampBattle* GetCampBattleByPlayerID( unsigned int nPlayerID );
    CampBattle* GetCampBattleByUnitID( unsigned int nUnitID );

    // 战场设定
    const CampBattleConfig* GetBattleConfig() const { return m_pBattleConfig; }
    void SetBattleConfig( CampBattleConfig* pConfig ) { m_pBattleConfig = pConfig; }

    // 显示报名窗口
    virtual bool ShowCampBattleSignUp( GamePlayer* pPlayer );

    // 战场报名
    virtual bool SignUpCampBattle( GamePlayer* pPlayer ) = 0;

    // 显示进入界面
    virtual bool ShowCampBattleEnter( GamePlayer* pPlayer ) = 0;

    // 进入战场
    virtual bool EnterCampBattle( GamePlayer* pPlayer ) = 0;

    // 处理战场状态改变
    virtual void ProcessChangeStatus( unsigned char uchStatus );

    // 发送国家战场结果消息
    virtual void SendCountryBattleResultMessage( unsigned int nWinID, unsigned char uchWinType,unsigned int nLoseID,unsigned int nCampBattle  )
	{
		//zhuxincong 加下看下有没有效果
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
    // 处理战场初始化状态
    virtual void ProcessBattleInitStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );

    // 处理战场报名状态
    virtual void ProcessBattleSignUpStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );

    // 处理战场准备状态
    virtual void ProcessBattlePrepareStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );

    // 处理战场进入状态
    virtual void ProcessBattleEnterStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );

    // 处理战场战斗状态
    virtual void ProcessBattleFightStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );

    // 处理战场结束状态
    virtual void ProcessBattleEndStatus();

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // 判断是否到了战场报名时间
    bool CheckBattleSignUpTime( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );

    // 判断是否到了战场准备时间
    bool CheckBattlePrepareTime( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );

    // 判断是否到了战场进入时间
    bool CheckBattleEnterTime( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );

    // 判断是否到了战场战斗时间
    bool CheckBattleFightTime( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );

    // 判断是否到了战场结束时间
    bool CheckBattleEndTime( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // 处理转换到报名状态逻辑
    virtual void ProcessChangeToSignUpStatus();

    // 处理转换到准备状态逻辑
    virtual void ProcessChangeToPrepareStatus() = 0;

    // 处理转换到进入状态逻辑
    virtual void ProcessChangeToEnterStatus() = 0;

    // 处理转换到战斗状态逻辑
	virtual void ProcessChangeToFightStatus();

	// 处理转换到结束的状态逻辑
	virtual void ProcessChangeToEndStatus(){};
    //////////////////////////////////////////////////////////////////////////////////////////////
    // 发送战场状态改变消息
    virtual void SendBattleStatusMessage( unsigned char uchStatus );

    ////////////////////////////////////////////////////////////////////

    // 报名战场
    bool SignUpCampBattle( GamePlayer* pPlayer, unsigned int nUnitID);

    // 显示进入阵营战场窗口
    bool ShowCampBattleEnter( GamePlayer* pPlayer, unsigned int nUnitID );

    // 进入阵营战场
    bool EnterCampBattle( GamePlayer* pPlayer, unsigned int nUnitID );

    // 处理战场剩余时间
    void ProcessBattleLeftTime( unsigned int nCurrentTime );
protected:
    typedef std::map< unsigned int, CampBattle* > CampBattleMap;
    typedef CampBattleMap::iterator CampBattleMapIter;

    typedef std::vector< unsigned int > SignUpVector;
    typedef SignUpVector::iterator SignUpVectorIter;

    typedef std::map< unsigned int, unsigned int > MatchUnitMap;
    typedef MatchUnitMap::iterator MatchUnitMapIter;

    // 国家
    unsigned char m_uchCountryID;

    // 战场的MapConfig ID
    unsigned int m_nConfigMapID;

    // 战场的类型
    unsigned char m_uchBattleType;

    // 战场的状态
    unsigned char m_uchBattleStatus;

    // 保存战场的map
    CampBattleMap m_mapCampBattle;

    // 保存报名的vector
    SignUpVector m_vecSignUp;

    // 保存对阵信息列表
    MatchUnitMap m_mapMatchUnit;

    // 配置设定
    CampBattleConfig* m_pBattleConfig;

    // 战场剩余时间( 单位: 毫秒 )
    unsigned int m_nLeftTime;
    unsigned int m_nLastUpdateTime;

	// 对应国家的主城位置(主要用来飞地图,保证跨GAME SERVER飞入战场可以正确执行)
	int m_KingdomMapID;
	float m_X;
	float m_Y;

	int	m_BattleValue;//战场的进入值
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