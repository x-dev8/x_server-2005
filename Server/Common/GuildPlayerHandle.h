
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

    void GuildLevelUp();                          // �����������
    void GuildOfferBuild();                       // ���װﹱ
    void GuildCollect();                          // ����ļ��
    void GuildMasterDelate();                     // ���ɵ���
    void GuildDonate();                           // ���ɾ���
    bool GuildQuestRelease( uint32 nQuestType );  // �������񷢲�
    bool GuildShopLevelUp( uint8 uchLevel );      // ��������̵�ȼ�
    bool GuildConvene();                          // �����ټ�
	int16 GetGuildReleaseQuest();				  // �������񷢲�

    // ��Ա�ﹱ
    void OperateGuildOffer( uint8 uchOperate, int nValue );
    uint32 GetGuildOffer();

    // ��Ա��Ծ��
    void OperateGuildActivity( uint8 uchOperate, int nValue );
    uint32 GetGuildActivity();

    // ���ɽ�Ǯ
    void OperateGuildMoney( uint8 uchOperate, int nValue );
    uint32 GetGuildMoney();

    // ���ɾ���
    void OperateGuildExp( uint8 uchOperate, int nValue );
    uint32 GetGuildExp();

    // ����ʹ����
    void OperateGuildMission( uint8 uchOperate, int nValue );
    uint32 GetGuildMission();

    // ���ɽ���
    void OperateGuildSalary( uint8 uchOperate, int nValue );
    uint32 GetGuildSalary();

    // ���ɼ�������
    void OperateGuildVar( uint8 uchOperate, uint32 nIndex, short nValue );
    short GetGuildVar( uint32 nIndex );

    // ���ɵȼ�
    void OperateGuildLevel( uint8 uchOperate, int nValue );
    uint32 GetGuildLevel();

    uint8 GetGuildPositon();    // ��ð���ְλ

    void   TellGuildVar( int nKey, short nVar );
    void   TellAllGuildVar();
    void   ClearAllGuildVar();


    // ��¼����ʱ��
    bool RecordGuildTime( int nVarId );

    // �ж��Ƿ��ѹ����ɼ�¼ʱ��
    bool IsGuildExpired( int nVarId, int keyHour, int keyMinute, int minDuration );

    // ������ɼ�¼ʱ��
    void ClearGuildExpiredVar( int nVarId, int keyHour, int keyMinute, int minDuration, int nClearVarId );

