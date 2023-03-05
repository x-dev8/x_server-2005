
private:
    uint32 m_nRMBMoney;         // �𶧴��
    uint32 m_nGameMoney;        // ��Ϸ�Ҵ��

    bool m_bIsWaitProcess;      // �Ƿ��ڵȴ�����
    uint32 m_dwLastOperateTime; // �ϴβ���ʱ��

public:

    void InitPlayerConsignment();
    void SetPlayerConsignmentProcessing();
    bool CheckPlayerConsignmentProcessing();
    void SetPlayerConsignmentAccount( uint32 nRMBMoney, uint32 nGameMoney );

    void OpenConsignmentMoneyWindow(bool bGetAll = false);        // �򿪽𶧼��۴���

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

