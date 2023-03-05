private:
    unsigned int m_nBargainingID;       // ����ID

protected:

    // ����Ƿ��ܽ���
    unsigned char CheckCanBargaining( GamePlayer* pTarget );

    // �����׽�Ǯ
    void ProcessBargainingMoneyReq( unsigned int nGameMoney, PlayerBargaining* pPlayerBargaining, GamePlayer* pTarget );

    // �����׽�
    void ProcessBargainingRMBReq( unsigned int nRMBMoney, PlayerBargaining* pPlayerBargaining, GamePlayer* pTarget );

    // ��������Ʒ
    void ProcessBargainingItemReq( unsigned char uchBargainingIndex, unsigned char uchBagType, unsigned char uchBagIndex, __int64 n64Guid, PlayerBargaining* pPlayerBargaining, GamePlayer* pTarget );

    // ����������
    void ProcessBargainingMountReq( unsigned char uchBargainingIndex, unsigned char uchBagType, unsigned char uchBagIndex, __int64 n64Guid, PlayerBargaining* pPlayerBargaining, GamePlayer* pTarget );

	// �����׳���
	void ProcessBargainingPetReq( unsigned char uchBargainingIndex, unsigned char uchBagType, unsigned char uchBagIndex, __int64 n64Guid, PlayerBargaining* pPlayerBargaining, GamePlayer* pTarget );

    // ����������
    void ProcessBargainingChangeData( PlayerBargaining* pPlayerBargaining, GamePlayer* pTarget, PlayerBargaining* pTargetPlayerBargaining );

    // ��齻��������
    bool CheckPlayerBargainingData( PlayerBargaining* pPlayerBargaining, unsigned char uchBargainingIndex, unsigned char uchBagType, __int64 n64Guid );

    // ��ý�����Ϣ
    PlayerBargaining* GetPlayerBargaining( GamePlayer*& pTargetPlayer, PlayerBargaining*& pTargetPlayerBargaining );
public:

    // ��ý���ID
    unsigned int GetBargainingID() const { return m_nBargainingID; }

    // ���ý���ID
    void SetBargainingID( unsigned int nValue ) { m_nBargainingID = nValue; }

    // �ж��Ƿ��ڽ�����
    bool HaveBargaining() const {  return m_nBargainingID != BargainingDefine::NoneID; }

    // ���ͽ��������Ӧ��Ϣ���ͻ���
    void SendBargainingAckMessage( unsigned char uchResult );

    // ���ͽ��׿�ʼ��Ϣ���ͻ���
    void SendBargainingStartMessage( GameObjectId ustPlayerID );

    // ���ͽ��׽�����Ϣ���ͻ���
    void SendBargainingFinishMessage( unsigned char uchFinishType );

    // ���ͽ�����Ʒ���ݴ�����Ϣ���ͻ���
    void SendBargainingDataErrorMessage( GameObjectId ustPlayerID, unsigned char uchResult );

    // ���ͽ�����Ʒ���ݸ��Լ�
    void SendBargainingDataAckMessage( unsigned char uchBargainingType, unsigned int nBargainingValue, unsigned char uchBargainingIndex, unsigned char uchBagType, unsigned char uchBagIndex, __int64 n64Guid );

    // ���ͽ�����Ʒ���ݸ��Է�
    void SendShowBargainingDataMessage( unsigned char uchBargainingType, unsigned int nBargainingValue, unsigned char uchBargainingIndex, void* pData, int nSize );

    // ���ͽ���״̬���ͻ���
    void SendBargainingStatusMessage( GameObjectId ustPlayerID, unsigned char uchStatus );

    // �����Ƴ�������Ʒ��Ϣ���ͻ���
    void SendRemoveBargainingDataMessage( GameObjectId ustPlayerID, unsigned char uchBargainingIndex );

    // �ж��Ƿ��ܽ�����Ʒ�ɹ�
    bool CheckCanBargainingChangeData( PlayerBargaining* pPlayerBargaining, GamePlayer* pTarget, PlayerBargaining* pTargetPlayerBargaining );

    // ������Ʒ
    void ProcessBargainingChangeData( GamePlayer* pTarget, PlayerBargaining* pTargetPlayerBargaining );

    /////////////////////////////////////////////////////////////////////////////////////////////
    // ��Ϣ����
    bool ProcessBargainingMsg( Msg* pMsg );

    // ���뽻��
    void OnMsgBargainingReq( Msg* pMsg );

    // �����Ƿ�ͬ�⽻��
    void OnMsgBargainingRequestAck( Msg* pMsg );

    // ������뽻����Ʒ
    void OnMsgBargainingDataReq( Msg* pMsg );

    // ��������
    void OnMsgBargainingLockReq( Msg* pMsg );

    // ����ȷ������
    void OnMsgBargainingFixReq( Msg* pMsg );

    // �����������
    void OnMsgBargainingCancelReq( Msg* pMsg );

    // �����Ƴ���Ʒ
    void OnMsgRemoveBargainingDataReq( Msg* pMsg );