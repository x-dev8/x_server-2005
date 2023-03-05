
/************************************************************************
Include in GamePlayer.h
MaintenanceMan Mail: lori227@live.cn
************************************************************************/

private:
    GameGuild* m_pGuild;
public:
    bool ProcessGuildMsg( Msg* pMsg );

    void OnMsgCreateGuildReq( Msg* pMsg );
    void OnMsgLeaveGuildReq( Msg* pMsg );
    void OnMsgKickGuildReq( Msg* pMsg );
    void OnMsgInviteGuildReq( Msg* pMsg );
    void OnMsgInviteJoinGuildAck( Msg* pMsg );
    void OnMsgJoinGuildReq( Msg* pMsg );
    void OnMsgRequestJoinGuildAck( Msg* pMsg );
    void OnMsgQueryGuildDataReq( Msg* pMsg );
    void OnMsgGuildNoticeChangeReq( Msg* pMsg );
    void OnMsgGuildResignPositionReq( Msg* pMsg );
    void OnMsgGuildTransferPositionReq( Msg* pMsg );
    void OnMsgGuildCreateFamilyReq( Msg* pMsg );
    void OnMsgGuildFamilyChangeReq( Msg* pMsg );
    void OnMsgGuildMemberFamilyChangeReq( Msg* pMsg );
    void OnMsgGuildAssignPositionReq( Msg* pMsg );
    void OnMsgGuildDelateAgreeAck( Msg* pMsg );
    void OnMsgGuildDonateAck( Msg* pMsg );
    void OnMsgGuildBuyItemReq( Msg* pMsg );
    void OnMsgGuildShopLevelUpReq( Msg* pMsg );
    void OnMsgGuildConveneAck( Msg* pMsg );
	void OnMsgChangeGuildAimReq( Msg* pMsg );
	void OnMsgSetGuildCampBattleValue( Msg* pMsg );

	void OnMsgChangeGuldNameReq( Msg* pMsg );

    void InitPlayerGuild();
    GameGuild* GetGuild() { return m_pGuild; }
    void SetGuild( GameGuild* pGuild ) { m_pGuild = pGuild; }
    bool HaveGuild() const { return m_pGuild != NULL; }
    uint32 GetGuildID() const;
    void SetGuildID( uint32 nGuildID );

    virtual bool IsGuildMember( BaseCharacter* pChar );

    void ProcessJoinGuild( GameGuild* pGuild );
    void ProcessLeaveGuild( GameGuild* pGuild );
    void ProcessGuildPositionChange();

    void GuildLevelUp();                          // 请求帮派升级
    void GuildOfferBuild();                       // 捐献帮贡
    void GuildCollect();                          // 帮派募集
    void GuildMasterDelate();                     // 帮派弹劾
    void GuildDonate();                           // 帮派捐献
    bool GuildQuestRelease( uint32 nQuestType );  // 帮派任务发布
    bool GuildShopLevelUp( uint8 uchLevel );      // 激活帮派商店等级
    bool GuildConvene();                          // 帮派召集
	int16 GetGuildReleaseQuest();				  // 帮派任务发布

    // 成员帮贡
    void OperateGuildOffer( uint8 uchOperate, int nValue );
    uint32 GetGuildOffer();

    // 成员活跃度
    void OperateGuildActivity( uint8 uchOperate, int nValue );
    uint32 GetGuildActivity();

    // 帮派金钱
    void OperateGuildMoney( uint8 uchOperate, int nValue );
    uint32 GetGuildMoney();

    // 帮派经验
    void OperateGuildExp( uint8 uchOperate, int nValue );
    uint32 GetGuildExp();

    // 帮派使命点
    void OperateGuildMission( uint8 uchOperate, int nValue );
    uint32 GetGuildMission();

    // 帮派津贴
    void OperateGuildSalary( uint8 uchOperate, int nValue );
    uint32 GetGuildSalary();

    // 帮派记数变量
    void OperateGuildVar( uint8 uchOperate, uint32 nIndex, short nValue );
    short GetGuildVar( uint32 nIndex );

    // 帮派等级
    void OperateGuildLevel( uint8 uchOperate, int nValue );
    uint32 GetGuildLevel();

    uint8 GetGuildPositon();    // 获得帮派职位

    void   TellGuildVar( int nKey, short nVar );
    void   TellAllGuildVar();
    void   ClearAllGuildVar();


    // 记录帮派时间
    bool RecordGuildTime( int nVarId );

    // 判断是否已过帮派记录时间
    bool IsGuildExpired( int nVarId, int keyHour, int keyMinute, int minDuration );

    // 清除帮派记录时间
    void ClearGuildExpiredVar( int nVarId, int keyHour, int keyMinute, int minDuration, int nClearVarId );

