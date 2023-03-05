
/************************************************************************
            Include in GamePlayer.h
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/

private:
    GameCountry* m_pCountry;
    int m_nCountrySpeakSpaceTime;           // 国家频道发言的间隔时间
    __int64 m_nCountryMountGUID;            // 国家坐骑GUID

protected:
    void SendCountryQuestStatusChangeAckMessage( uint8 nQuestType, uint8 nResult );
    void SendCountryOfficialAppointAckMessage( uint8 nPosition, uint32 nPlayerID, uint8 nResult );
    void SendCountryOperateToPlayerAckMessage( uint8 nOperate, uint8 nResult );
public:
    void InitPlayerCountry( GameCountry* pCountry ); 
    GameCountry* GetGameCountry() { return m_pCountry; }

    void InitCountryTitle( bool bSendMessage );     // 初始化国家称号
    void SetCountryTitle( unsigned short ustValue, bool bSendMessage ); // 设置国家称号
    uint8 GetCountryTitle() const;  // 获得国家称号
    uint8 GetCountryTitle( uint8 uchGuardType );    // 通过守护获得国家称号
    uint8 CalcCountryGuardTitle();

    uint8 GetCountryOfficial();
    void TellAllCountryName();
    void TellCountryQuestStatus();                  // 通知国家发布任务信息
    void TellWeakCountry();                         // 通知本国是弱国
	void TellStrongCountry();						// 通知本国是强国
    bool IsHaveCountryMaster( uint8 uchType,uint8 uchCountry = 0 );      // 是否有国王,青龙 朱雀
    bool IsCountryGuild( uint8 uchType );
    bool IsCountryMaster( uint8 uchType );
    bool IsCountryMount( SMountItem* pMount );
    bool ReceiveCountryMount( uint8 uchType);       // 领取国家坐骑
    SMountItem* GetCountryMount();                  // 是否有国家坐骑( 有的话 直接返回指针 )
    SMountItem* FindCountryMount();                 // 查找身上的国家坐骑
    void CheckCountryMount();
    bool CountryConenve();
    bool IsCountryQueen();
    bool IsCountryQuestOpen( uint8 uchType );
    bool CheckCanCountrySpeak();   // 是否能国家发言
	bool SetCountryKing();
	bool IsPlayerKing(); //判断玩家是不是国王
	void SetCountryTribute(int nValue,int countryid,int operType);
	int GetCountryTribute(int countryid);

    void AddCountryResource( uint8 uchType, uint32 nValue );
    void SubCountryResource( uint8 uchType, uint32 nValue );

    // 处理杀死其他国家玩家
    void ProcessCountryBeKilledByPlayer( GamePlayer* pBeKiller, unsigned int nMapCountry );
    // 处理增加国战积分
    void ProcessKillUpdateCountryScore( GamePlayer* pBeKiller );

    int GetWarSortIndex();

    bool ProcessCountryMsg( Msg* pMsg );
    void OnMsgQueryCountryInfoReq( Msg* pMsg );
    void OnMsgCountryNoticeChangeReq( Msg* pMsg );
    void OnMsgCountryQuestStatusChangeReq( Msg* pMsg );
    void OnMsgCountryOfficialAppointReq( Msg* pMsg );
    void OnMsgCountryOfficialRecallReq( Msg* pMsg );
    void OnMsgCountryRequestRaiseReq( Msg* pMsg );
    void OnMsgCountryRaiseToPlayerAck( Msg* pMsg );
    void OnMsgCountryFlyToBordersReq( Msg* pMsg );
    void OnMsgCountryOperateToPlayerReq( Msg* pMsg );
    void OnMsgCountryConveneAck( Msg* pMsg );
    void OnMsgCountryChangeReq( Msg* pMsg );
    void OnMsgChangeCountryNameReq( Msg* pMsg );
	void OnMsgCountryQuestFlyReq( Msg* pMsg );
	void OnMsgDelCountryOfficialReq( Msg* pMsg );
	void OnMsgLoadCountryInfoReq( Msg* pMsg );
	void OnMsgCountryBuffChangeAck( Msg* pMsg );