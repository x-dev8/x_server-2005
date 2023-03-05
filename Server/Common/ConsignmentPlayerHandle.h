
private:
    uint32 m_nRMBMoney;         // 金锭存款
    uint32 m_nGameMoney;        // 游戏币存款

    bool m_bIsWaitProcess;      // 是否在等待操作
    uint32 m_dwLastOperateTime; // 上次操作时间

public:

    void InitPlayerConsignment();
    void SetPlayerConsignmentProcessing();
    bool CheckPlayerConsignmentProcessing();
    void SetPlayerConsignmentAccount( uint32 nRMBMoney, uint32 nGameMoney );

    void OpenConsignmentMoneyWindow(bool bGetAll = false);        // 打开金锭寄售窗口

    virtual bool ProcessConsignmentMessage( Msg* pMessage );
    virtual void OnMsgConsignmentCount( Msg* pMessage );
    virtual void OnCS2GSConsignmentOperate( Msg* pMessage );
    virtual void OnCS2GSOperateMoneyAck( Msg* pMessage );

    virtual void OnMsgQueryConsignmentList( Msg* pMessage );
    virtual void OnMsgOperateMoneyReq( Msg* pMessage );
    virtual void OnMsgConsignmentMoneyReq( Msg* pMessage );
    virtual void OnMsgConsignmentMoneyHistroy( Msg* pMessage );
    virtual void OnMsgConsignmentOperateReq( Msg* pMessage );

	//
	//virtual void OnMsgConsignmentItemReq(Msg* pMessage);

