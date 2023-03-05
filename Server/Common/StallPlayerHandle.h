

public:
	enum StallState
	{
		SS_None,	// 不在摆摊
		SS_Normal,	// 在线摆摊
		SS_Offline,	// 离线摆摊
	};

private:
    uint8        m_nStallState;     // 摆摊状态,参见枚举StallState
    char         m_szStallTitle[ StallDefine::MaxStallTitle ]; // 摊位标题
    StallEx      m_xStall;           // 摆摊管理
	uint32		 m_nOfflineStallEndTime;	// 离线摆摊结束时间点
	uint8		 m_nSetmealID;	// 套餐ID

protected:
    // 检测摆摊物品是否有效
    bool CheckStallItemValid( SCharItem* pCharItem, unsigned char uchStallIndex, StallData* pData );

    // 检测摆摊马是否有效
    bool CheckStallMountValid( SMountItem* pMount, unsigned char uchStallIndex, StallData* pData );

    // 检测摆摊宠物是否有效
    bool CheckStallPetValid( SPetItem* pPet, unsigned char uchStallIndex, StallData* pData );

    // 处理出售物品
    bool ProcessStallSellItem( GamePlayer* pPlayer, unsigned char uchStallIndex, unsigned char uchCount, StallData* pStallData, std::string& strItemName );

    // 处理出售坐骑
    bool ProcessStallSellMount( GamePlayer* pPlayer, unsigned char uchStallIndex, StallData* pStallData, std::string& strMountName );

    // 处理出售宠物
    bool ProcessStallSellPet ( GamePlayer* pPlayer, unsigned char uchStallIndex, StallData* pStallData, std::string& strPetName );

    // 处理收购物品
    bool ProcessStallBuyItem( GamePlayer* pPlayer, StallData* pStallData, unsigned char uchCount, unsigned char uchBagType, unsigned char uchBagIndex, __int64 n64Guid, std::string& strItemName );

    // 处理收购坐骑
    bool ProcessStallBuyMount( GamePlayer* pPlayer, StallData* pStallData, unsigned char uchBagIndex, __int64 n64Guid, std::string& strMountName );

    // 处理收购宠物
    bool ProcessStallBuyPet ( GamePlayer* pPlayer, StallData* pStallData, unsigned char uchBagIndex, __int64 n64Guid, std::string& strPetName );

    // 发送更新摊位消息给客户端
    void SendUpdateStallDataMessage( unsigned char uchStallIndex, StallData& xData );

    // 通知客户端某人购买or出售了物品
    void SendTellBuyOrSellStallDataMessage( GamePlayer* pPlayer, unsigned char uchStallType, const char* szItemName, unsigned char uchCount, unsigned int nGameMoney, unsigned int nRMBMoney );

	// 检查摆摊间隔限制
	bool CheckStallDist( GameStage* pStage, float fDistance );

public:
    // 初始化摆摊信息
    void InitStall();

    // 设置正在摆摊
    void SetStallOpen( bool bValue );

	// 设置正在离线摆摊
	void SetStallOpenOffline( bool bValue );

    // 获得是否正在摆摊
    bool GetStallOpen() const { return SS_Normal == m_nStallState; }

	// 获得是否正在离线摆摊
	bool GetStallOpenOffline() const { return SS_Offline == m_nStallState; }

	bool IsOpenStall()	const	{ return SS_Normal == m_nStallState || SS_Offline == m_nStallState; }

	// 设置离线摆摊结束时间点
	void SetOfflineStallEndTime( uint32 nEndTime )	{ m_nOfflineStallEndTime = nEndTime; }

	// 获得离线摆摊结束时间点
	uint32 GetOfflineStallEndTime() const	{ return m_nOfflineStallEndTime; }

	// 检查是否满足离线摆摊花费
	bool IsSatisfyCost( StallConfig::CostSetmeal* pCostSetmeal );

	// 扣除离线摆摊花费
	bool RemoveStallCost( StallConfig::CostSetmeal* pCostSetmeal );

    // 获得摆摊模型ID
    unsigned int GetStallModelID( bool blIsOffline );

	// 设置套餐ID
	void SetSetmealID( uint8 nSetmealID )	{ m_nSetmealID = nSetmealID; }

	// 获得套餐ID
	uint8 GetSetmealID()	{ return m_nSetmealID; }

    // 设置摊位标语
    void SetStallTitle( const char* szTitle ){ strncpy_s( m_szStallTitle, sizeof( m_szStallTitle ), szTitle, sizeof( m_szStallTitle ) - 1 ); }

    // 获得摊位标语
    const char* GetStallTitle() const { return m_szStallTitle; }

    // 打开自己的摆摊界面, 服务器同步摆摊物品
    void ProcessOpenStallWindow();

    // 请求开始摆摊
    void ProcessStartStall( const char* szTitle, bool blIsOfflineStall = false );

    // 关闭摊位
    void CloseStall();

    // 检测摆摊道具是否有效
    bool CheckStallDataValid( unsigned char uchIndex, StallData* pData );

    // 显示摊位信息给玩家
    void ShowStallDataToPlayer( GamePlayer* pPlayer );

    // 获得摆摊中物品数据
    void GetSellDataToClient( StallData& xStallData, SellDataToClient& xSellDataToClient );

    // 处理玩家购买自己摊位上的物品
    void ProcessStallSell( GamePlayer* pPlayer, unsigned char uchStallIndex, unsigned int nGameMoneyPrice, unsigned int nRMBMoneyPrice, unsigned char uchCount, __int64 n64Guid );

    // 处理玩家出售物品到自己摊位
    void ProcessStallBuy( GamePlayer* pPlayer, unsigned char uchStallIndex, unsigned int nGameMoneyPrice, unsigned int nRMBMoneyPrice, unsigned char uchCount, unsigned char uchBagType, unsigned char uchBagIndex, __int64 n64Guid );

    // 通知打开摊位的人, 摊位某个位置的数量信息
    void SendTellStallDataCountMessage( unsigned char uchStallIndex, unsigned char uchCount );

    // 发摆摊基本消息
    void ShowStallInfo( GamePlayer* pTarget );

    /////////////////////////////////////////////////////////////////////////////////////////////
    // 消息处理
    bool ProcessStallMsg( Msg* pMsg );

    // 添加一个出售的物品
    void OnMsgAddSellDataReq( Msg* pMsg );

    // 添加一个收购的物品
    void OnMsgAddBuyDataReq( Msg* pMsg );

    // 申请摆摊
    void OnMsgStartStallReq( Msg* pMsg );

    // 关闭摆摊
    void OnMsgCloseStallReq( Msg* pMsg );

    // 请求打开一个摊位
    void OnMsgOpenStallReq( Msg* pMsg );

    // 请求购买摊位上的一个物品
    void OnMsgBuyStallReq( Msg* pMsg );

    // 请求出售物品到摊位上
    void OnMsgSellStallReq( Msg* pMsg );

    // 移动摊位上的物品
    void OnMsgMoveStallDataReq( Msg* pMsg );

    // 删除摊位上的物品
    void OnMsgRemoveStallDataReq( Msg* pMsg );

    // 请求修改摊位标题
    void OnMsgChangeStallTitleReq( Msg* pMsg );

    // 请求修改摊位价格
    void OnMsgChangeStallPriceReq( Msg* pMsg );

	//搜索符合要求的摊位信息
	void OnMsgStallQuery( Msg* pMsg );
