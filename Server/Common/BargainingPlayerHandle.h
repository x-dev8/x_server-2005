private:
    unsigned int m_nBargainingID;       // 交易ID

protected:

    // 检查是否能交易
    unsigned char CheckCanBargaining( GamePlayer* pTarget );

    // 请求交易金钱
    void ProcessBargainingMoneyReq( unsigned int nGameMoney, PlayerBargaining* pPlayerBargaining, GamePlayer* pTarget );

    // 请求交易金锭
    void ProcessBargainingRMBReq( unsigned int nRMBMoney, PlayerBargaining* pPlayerBargaining, GamePlayer* pTarget );

    // 请求交易物品
    void ProcessBargainingItemReq( unsigned char uchBargainingIndex, unsigned char uchBagType, unsigned char uchBagIndex, __int64 n64Guid, PlayerBargaining* pPlayerBargaining, GamePlayer* pTarget );

    // 请求交易坐骑
    void ProcessBargainingMountReq( unsigned char uchBargainingIndex, unsigned char uchBagType, unsigned char uchBagIndex, __int64 n64Guid, PlayerBargaining* pPlayerBargaining, GamePlayer* pTarget );

	// 请求交易宠物
	void ProcessBargainingPetReq( unsigned char uchBargainingIndex, unsigned char uchBagType, unsigned char uchBagIndex, __int64 n64Guid, PlayerBargaining* pPlayerBargaining, GamePlayer* pTarget );

    // 处理交易请求
    void ProcessBargainingChangeData( PlayerBargaining* pPlayerBargaining, GamePlayer* pTarget, PlayerBargaining* pTargetPlayerBargaining );

    // 检查交易栏道具
    bool CheckPlayerBargainingData( PlayerBargaining* pPlayerBargaining, unsigned char uchBargainingIndex, unsigned char uchBagType, __int64 n64Guid );

    // 获得交易信息
    PlayerBargaining* GetPlayerBargaining( GamePlayer*& pTargetPlayer, PlayerBargaining*& pTargetPlayerBargaining );
public:

    // 获得交易ID
    unsigned int GetBargainingID() const { return m_nBargainingID; }

    // 设置交易ID
    void SetBargainingID( unsigned int nValue ) { m_nBargainingID = nValue; }

    // 判断是否在交易中
    bool HaveBargaining() const {  return m_nBargainingID != BargainingDefine::NoneID; }

    // 发送交易申请回应消息给客户端
    void SendBargainingAckMessage( unsigned char uchResult );

    // 发送交易开始消息给客户端
    void SendBargainingStartMessage( GameObjectId ustPlayerID );

    // 发送交易结束消息给客户端
    void SendBargainingFinishMessage( unsigned char uchFinishType );

    // 发送交易物品数据错误消息给客户端
    void SendBargainingDataErrorMessage( GameObjectId ustPlayerID, unsigned char uchResult );

    // 发送交易物品数据给自己
    void SendBargainingDataAckMessage( unsigned char uchBargainingType, unsigned int nBargainingValue, unsigned char uchBargainingIndex, unsigned char uchBagType, unsigned char uchBagIndex, __int64 n64Guid );

    // 发送交易物品数据给对方
    void SendShowBargainingDataMessage( unsigned char uchBargainingType, unsigned int nBargainingValue, unsigned char uchBargainingIndex, void* pData, int nSize );

    // 发送交易状态给客户端
    void SendBargainingStatusMessage( GameObjectId ustPlayerID, unsigned char uchStatus );

    // 发送移除交易物品消息给客户端
    void SendRemoveBargainingDataMessage( GameObjectId ustPlayerID, unsigned char uchBargainingIndex );

    // 判断是否能交易物品成功
    bool CheckCanBargainingChangeData( PlayerBargaining* pPlayerBargaining, GamePlayer* pTarget, PlayerBargaining* pTargetPlayerBargaining );

    // 交换物品
    void ProcessBargainingChangeData( GamePlayer* pTarget, PlayerBargaining* pTargetPlayerBargaining );

    /////////////////////////////////////////////////////////////////////////////////////////////
    // 消息处理
    bool ProcessBargainingMsg( Msg* pMsg );

    // 申请交易
    void OnMsgBargainingReq( Msg* pMsg );

    // 回馈是否同意交易
    void OnMsgBargainingRequestAck( Msg* pMsg );

    // 请求加入交易物品
    void OnMsgBargainingDataReq( Msg* pMsg );

    // 请求锁定
    void OnMsgBargainingLockReq( Msg* pMsg );

    // 请求确定交易
    void OnMsgBargainingFixReq( Msg* pMsg );

    // 请求结束交易
    void OnMsgBargainingCancelReq( Msg* pMsg );

    // 请求移除物品
    void OnMsgRemoveBargainingDataReq( Msg* pMsg );