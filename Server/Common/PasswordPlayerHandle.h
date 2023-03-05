private:
    uint8 m_uchOperator;      // 2级密码的验证操作

protected:
    bool CheckCanOperator( unsigned int nFlag, unsigned char uchOperate );

    void ProcessSecondPwdOperator( unsigned char uchOperate );

public:
    // 消息使用
    bool ProcessPasswordMsg(Msg* pMsg);

    void OnMsgSetSecondPasswordReq( Msg* pMsg );
    void OnMsgReSetSecondPasswordReq( Msg* pMsg );
    void OnMsgClearSecondPasswordReq( Msg* pMsg );
    void OnMsgCheckSecondPasswordAck( Msg* pMsg );
    void OnMsgPasswordSetProtectReq( Msg* pMsg );
    void OnMsgPasswordSetProtectAck( Msg* pMsg );
    void OnMsgChangeProtectReq( Msg* pMsg );

    // 财产保护下判断是否可以进行某操作
    bool ProcessSecondPasswordOperate( unsigned int nFlag, unsigned char uchOperate );

