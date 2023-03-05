
/************************************************************************
            Include in GamePlayer.h
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/

private:
    GameCountry* m_pCountry;
    int m_nCountrySpeakSpaceTime;           // ����Ƶ�����Եļ��ʱ��
    __int64 m_nCountryMountGUID;            // ��������GUID

protected:
    void SendCountryQuestStatusChangeAckMessage( uint8 nQuestType, uint8 nResult );
    void SendCountryOfficialAppointAckMessage( uint8 nPosition, uint32 nPlayerID, uint8 nResult );
    void SendCountryOperateToPlayerAckMessage( uint8 nOperate, uint8 nResult );
public:
    void InitPlayerCountry( GameCountry* pCountry ); 
    GameCountry* GetGameCountry() { return m_pCountry; }

    void InitCountryTitle( bool bSendMessage );     // ��ʼ�����ҳƺ�
    void SetCountryTitle( unsigned short ustValue, bool bSendMessage ); // ���ù��ҳƺ�
    uint8 GetCountryTitle() const;  // ��ù��ҳƺ�
    uint8 GetCountryTitle( uint8 uchGuardType );    // ͨ���ػ���ù��ҳƺ�
    uint8 CalcCountryGuardTitle();

    uint8 GetCountryOfficial();
    void TellAllCountryName();
    void TellCountryQuestStatus();                  // ֪ͨ���ҷ���������Ϣ
    void TellWeakCountry();                         // ֪ͨ����������
	void TellStrongCountry();						// ֪ͨ������ǿ��
    bool IsHaveCountryMaster( uint8 uchType,uint8 uchCountry = 0 );      // �Ƿ��й���,���� ��ȸ
    bool IsCountryGuild( uint8 uchType );
    bool IsCountryMaster( uint8 uchType );
    bool IsCountryMount( SMountItem* pMount );
    bool ReceiveCountryMount( uint8 uchType);       // ��ȡ��������
    SMountItem* GetCountryMount();                  // �Ƿ��й�������( �еĻ� ֱ�ӷ���ָ�� )
    SMountItem* FindCountryMount();                 // �������ϵĹ�������
    void CheckCountryMount();
    bool CountryConenve();
    bool IsCountryQueen();
    bool IsCountryQuestOpen( uint8 uchType );
    bool CheckCanCountrySpeak();   // �Ƿ��ܹ��ҷ���
	bool SetCountryKing();
	bool IsPlayerKing(); //�ж�����ǲ��ǹ���
	void SetCountryTribute(int nValue,int countryid,int operType);
	int GetCountryTribute(int countryid);

    void AddCountryResource( uint8 uchType, uint32 nValue );
    void SubCountryResource( uint8 uchType, uint32 nValue );

    // ����ɱ�������������
    void ProcessCountryBeKilledByPlayer( GamePlayer* pBeKiller, unsigned int nMapCountry );
    // �������ӹ�ս����
    void ProcessKillUpdateCountryScore( GamePlayer* pBeKiller );

    int GetWarSortIndex();

    bool ProcessCountryMsg( Msg* pMsg );
    void OnMsgQueryCountryInfoReq( Msg* pMsg );
    void OnMsgCountryNoticeChangeReq( Msg* pMsg );
    void OnMsgCountryQuestStatusChangeReq( Msg* pMsg );
    void OnMsgCountryOfficialAppointReq( Msg* pMsg );
    void OnMsgCountryOfficialRecallReq( Msg* pMsg );
    void OnMsgCountryRequestRaiseReq( Msg* pMsg );
    void OnMsgCountryRaiseToPlayerAck( Msg* pMsg );
    void OnMsgCountryFlyToBordersReq( Msg* pMsg );
    void OnMsgCountryOperateToPlayerReq( Msg* pMsg );
    void OnMsgCountryConveneAck( Msg* pMsg );
    void OnMsgCountryChangeReq( Msg* pMsg );
    void OnMsgChangeCountryNameReq( Msg* pMsg );
	void OnMsgCountryQuestFlyReq( Msg* pMsg );
	void OnMsgDelCountryOfficialReq( Msg* pMsg );
	void OnMsgLoadCountryInfoReq( Msg* pMsg );
	void OnMsgCountryBuffChangeAck( Msg* pMsg );