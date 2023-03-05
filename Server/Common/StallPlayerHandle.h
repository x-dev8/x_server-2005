

public:
	enum StallState
	{
		SS_None,	// ���ڰ�̯
		SS_Normal,	// ���߰�̯
		SS_Offline,	// ���߰�̯
	};

private:
    uint8        m_nStallState;     // ��̯״̬,�μ�ö��StallState
    char         m_szStallTitle[ StallDefine::MaxStallTitle ]; // ̯λ����
    StallEx      m_xStall;           // ��̯����
	uint32		 m_nOfflineStallEndTime;	// ���߰�̯����ʱ���
	uint8		 m_nSetmealID;	// �ײ�ID

protected:
    // ����̯��Ʒ�Ƿ���Ч
    bool CheckStallItemValid( SCharItem* pCharItem, unsigned char uchStallIndex, StallData* pData );

    // ����̯���Ƿ���Ч
    bool CheckStallMountValid( SMountItem* pMount, unsigned char uchStallIndex, StallData* pData );

    // ����̯�����Ƿ���Ч
    bool CheckStallPetValid( SPetItem* pPet, unsigned char uchStallIndex, StallData* pData );

    // ���������Ʒ
    bool ProcessStallSellItem( GamePlayer* pPlayer, unsigned char uchStallIndex, unsigned char uchCount, StallData* pStallData, std::string& strItemName );

    // �����������
    bool ProcessStallSellMount( GamePlayer* pPlayer, unsigned char uchStallIndex, StallData* pStallData, std::string& strMountName );

    // ������۳���
    bool ProcessStallSellPet ( GamePlayer* pPlayer, unsigned char uchStallIndex, StallData* pStallData, std::string& strPetName );

    // �����չ���Ʒ
    bool ProcessStallBuyItem( GamePlayer* pPlayer, StallData* pStallData, unsigned char uchCount, unsigned char uchBagType, unsigned char uchBagIndex, __int64 n64Guid, std::string& strItemName );

    // �����չ�����
    bool ProcessStallBuyMount( GamePlayer* pPlayer, StallData* pStallData, unsigned char uchBagIndex, __int64 n64Guid, std::string& strMountName );

    // �����չ�����
    bool ProcessStallBuyPet ( GamePlayer* pPlayer, StallData* pStallData, unsigned char uchBagIndex, __int64 n64Guid, std::string& strPetName );

    // ���͸���̯λ��Ϣ���ͻ���
    void SendUpdateStallDataMessage( unsigned char uchStallIndex, StallData& xData );

    // ֪ͨ�ͻ���ĳ�˹���or��������Ʒ
    void SendTellBuyOrSellStallDataMessage( GamePlayer* pPlayer, unsigned char uchStallType, const char* szItemName, unsigned char uchCount, unsigned int nGameMoney, unsigned int nRMBMoney );

	// ����̯�������
	bool CheckStallDist( GameStage* pStage, float fDistance );

public:
    // ��ʼ����̯��Ϣ
    void InitStall();

    // �������ڰ�̯
    void SetStallOpen( bool bValue );

	// �����������߰�̯
	void SetStallOpenOffline( bool bValue );

    // ����Ƿ����ڰ�̯
    bool GetStallOpen() const { return SS_Normal == m_nStallState; }

	// ����Ƿ��������߰�̯
	bool GetStallOpenOffline() const { return SS_Offline == m_nStallState; }

	bool IsOpenStall()	const	{ return SS_Normal == m_nStallState || SS_Offline == m_nStallState; }

	// �������߰�̯����ʱ���
	void SetOfflineStallEndTime( uint32 nEndTime )	{ m_nOfflineStallEndTime = nEndTime; }

	// ������߰�̯����ʱ���
	uint32 GetOfflineStallEndTime() const	{ return m_nOfflineStallEndTime; }

	// ����Ƿ��������߰�̯����
	bool IsSatisfyCost( StallConfig::CostSetmeal* pCostSetmeal );

	// �۳����߰�̯����
	bool RemoveStallCost( StallConfig::CostSetmeal* pCostSetmeal );

    // ��ð�̯ģ��ID
    unsigned int GetStallModelID( bool blIsOffline );

	// �����ײ�ID
	void SetSetmealID( uint8 nSetmealID )	{ m_nSetmealID = nSetmealID; }

	// ����ײ�ID
	uint8 GetSetmealID()	{ return m_nSetmealID; }

    // ����̯λ����
    void SetStallTitle( const char* szTitle ){ strncpy_s( m_szStallTitle, sizeof( m_szStallTitle ), szTitle, sizeof( m_szStallTitle ) - 1 ); }

    // ���̯λ����
    const char* GetStallTitle() const { return m_szStallTitle; }

    // ���Լ��İ�̯����, ������ͬ����̯��Ʒ
    void ProcessOpenStallWindow();

    // ����ʼ��̯
    void ProcessStartStall( const char* szTitle, bool blIsOfflineStall = false );

    // �ر�̯λ
    void CloseStall();

    // ����̯�����Ƿ���Ч
    bool CheckStallDataValid( unsigned char uchIndex, StallData* pData );

    // ��ʾ̯λ��Ϣ�����
    void ShowStallDataToPlayer( GamePlayer* pPlayer );

    // ��ð�̯����Ʒ����
    void GetSellDataToClient( StallData& xStallData, SellDataToClient& xSellDataToClient );

    // ������ҹ����Լ�̯λ�ϵ���Ʒ
    void ProcessStallSell( GamePlayer* pPlayer, unsigned char uchStallIndex, unsigned int nGameMoneyPrice, unsigned int nRMBMoneyPrice, unsigned char uchCount, __int64 n64Guid );

    // ������ҳ�����Ʒ���Լ�̯λ
    void ProcessStallBuy( GamePlayer* pPlayer, unsigned char uchStallIndex, unsigned int nGameMoneyPrice, unsigned int nRMBMoneyPrice, unsigned char uchCount, unsigned char uchBagType, unsigned char uchBagIndex, __int64 n64Guid );

    // ֪ͨ��̯λ����, ̯λĳ��λ�õ�������Ϣ
    void SendTellStallDataCountMessage( unsigned char uchStallIndex, unsigned char uchCount );

    // ����̯������Ϣ
    void ShowStallInfo( GamePlayer* pTarget );

    /////////////////////////////////////////////////////////////////////////////////////////////
    // ��Ϣ����
    bool ProcessStallMsg( Msg* pMsg );

    // ���һ�����۵���Ʒ
    void OnMsgAddSellDataReq( Msg* pMsg );

    // ���һ���չ�����Ʒ
    void OnMsgAddBuyDataReq( Msg* pMsg );

    // �����̯
    void OnMsgStartStallReq( Msg* pMsg );

    // �رհ�̯
    void OnMsgCloseStallReq( Msg* pMsg );

    // �����һ��̯λ
    void OnMsgOpenStallReq( Msg* pMsg );

    // ������̯λ�ϵ�һ����Ʒ
    void OnMsgBuyStallReq( Msg* pMsg );

    // ���������Ʒ��̯λ��
    void OnMsgSellStallReq( Msg* pMsg );

    // �ƶ�̯λ�ϵ���Ʒ
    void OnMsgMoveStallDataReq( Msg* pMsg );

    // ɾ��̯λ�ϵ���Ʒ
    void OnMsgRemoveStallDataReq( Msg* pMsg );

    // �����޸�̯λ����
    void OnMsgChangeStallTitleReq( Msg* pMsg );

    // �����޸�̯λ�۸�
    void OnMsgChangeStallPriceReq( Msg* pMsg );

	//��������Ҫ���̯λ��Ϣ
	void OnMsgStallQuery( Msg* pMsg );
