private:
    uint8 m_uchOperator;      // 2���������֤����

protected:
    bool CheckCanOperator( unsigned int nFlag, unsigned char uchOperate );

    void ProcessSecondPwdOperator( unsigned char uchOperate );

public:
    // ��Ϣʹ��
    bool ProcessPasswordMsg(Msg* pMsg);

    void OnMsgSetSecondPasswordReq( Msg* pMsg );
    void OnMsgReSetSecondPasswordReq( Msg* pMsg );
    void OnMsgClearSecondPasswordReq( Msg* pMsg );
    void OnMsgCheckSecondPasswordAck( Msg* pMsg );
    void OnMsgPasswordSetProtectReq( Msg* pMsg );
    void OnMsgPasswordSetProtectAck( Msg* pMsg );
    void OnMsgChangeProtectReq( Msg* pMsg );

    // �Ʋ��������ж��Ƿ���Խ���ĳ����
    bool ProcessSecondPasswordOperate( unsigned int nFlag, unsigned char uchOperate );

