public:
    // ����Ϣ����� ϵͳ�ұ߿����Ϣ
    virtual void ShowInfo       ( bool bTile, int type, const char* string, ... );
    virtual void ShowInfo       ( const char* string, bool bTile = false, int type = 282 );
    virtual void ShowInfo       ( bool bTile, int type, unsigned short ustStringID, UnionParam* pParam = NULL, int nCount = 0 );
    virtual bool IsCanSwitchStage();     
    virtual void SendVerifyPos  (); // ���ͽ���������Ϣ    
    virtual void TellClient     ( const char* string, ... );   
    virtual void TellClient     ( unsigned short ustStringID, UnionParam *pParam = NULL, int nCount = 0 );
    virtual void ShowFormatInfo ( const char* szFormat, ... );
    virtual void ShowMsgBox     ( const char* string, ... );

    void         SendChangeMapMessageToClient( DWORD dwMapId, short nTileX, short nTileY, BYTE byDir, float fDir ); // ��ͼ��ת
    void         SetDeathWaitForRelive( bool bFlag ) { m_bDeathAndWaitForRelive = bFlag; }

    // ���ڳ���ƶ�
    void         DoAssaultMoving( float fDistance, int nInstantMovingType );                       

    // �������
    bool         DoHitch( int nTrafficID, bool bBack );             // ���д���ƶ�
    void         DoHitchMoving( int nTrafficID );                   // ���д���ƶ�
    void         CancelHitchMoving();                               // ��������ƶ�
    int          GetCurTrafficID();                                 // ��ȡ��ǰ·�ߵ�ID    
    long         TryRespondChangeStage();                           // ������Ӧ�ͻ����г���ЧӦ

    // �ƶ�
    BOOL         CheckMoving();                                    // ����ƶ���Ϣ�ĺϷ���
    bool         CheckPosRightful();                               // ���λ�õ���ȷ��
    void         CheckCredit();                                    // �������ֵ�Ƿ���ȷ
    bool         CheckMovingMsgSendTime( DWORD dwSendTime );       // ����ƶ���Ϣ�Ϸ�ʱ�����ȷ��
    void         ResetCheckMoving();                               // ����Ҫ���Ե��ƶ���Ϣ(��ʼ��һ�ֵ��ƶ�����)
    void         SendVerifyPos( float fx, float fy );              // ��������    
    bool         IsNeedFixWorldCoordinate( int tileX, int tileY ); // �����µĸ������� �ж��Ƿ���Ҫ�����ͻ�����������ϵ���� float

    // �������
    void         IntonateInterrupt( int8 nType, char* szCallFun );

    DWORD        GetLastReceiveMoveMessageTime() const         { return dwLastReceiveMoveMessageTime; }
    void         SetLastReceiveMoveMessageTime( DWORD dwtime ) { dwLastReceiveMoveMessageTime = dwtime; }

protected:
    // ��Ϣ
    virtual void OnQueryMove        ( Msg* pMsg );
    virtual void OnQueryDisplayName ( Msg* pMsg );
    virtual void OnGetLag           ( Msg* pMsg );
    virtual void OnPingMsg          ( Msg* pMsg );      // �Կͻ��˷��͹�����PING��Ϣ�Ĵ���
    virtual void OnGetPlayerInfo    ( Msg* pMsg );      // �ͻ��˷�����������֪��Ī��npc������

    // ��������ƶ����߼�
    virtual void OnMsgPlayerMovingPos     ( const Msg* pMsg );
    virtual void OnMsgPlayerMovingPosToDir( const Msg* pMsg );
    virtual void OnMsgPlayerPos           ( const Msg* pMsg );
    virtual void OnMsgPlayerDir           ( const Msg* pMsg );
    virtual void OnMsgPlayerPosAndDir     ( const Msg* pMsg );
    virtual void OnReqChangeDir           ( const Msg* pMsg );

	// �ύһ���ƶ��Ϸ��Է���������Ϣ
	void ReqPlayerMoveAnalysis( D3DXVECTOR3& posMoveTo );

    // ��Ϊ����
    virtual void OnMsgIntonateInterrupt( const Msg* pMsg );
    virtual void OnMsgJump             ( const Msg* pMsg );
    virtual void OnMsgDrawWeapon       ( const Msg* pMsg );
    virtual void OnMsgDrawInWeapon     ( const Msg* pMsg );
    virtual void OnQueryCharAround     ( const Msg* pMsg );
    virtual void OnMsgReadytoUseSpecialSkill( Msg* pMsg  );

public:
    CGraphicCodeCheck m_graphiccodecheck;

    //////////////////////////////////////////////////////////////////////////
    // ��Ա����
protected:
    uint32      dwLastReceiveMoveMessageTime         ; // ���һ���յ��ƶ���Ϣ��ʱ��
    DWORD       _lastVerifyPosTime                   ; // �������λ�õ�ʱ���¼
    DWORD       _lastHitchMovingTime                 ; // ���ʹ���ƶ���Ϣ��ʱ���¼
    int         m_nCredit                            ; // ��¼��ҵ�����ֵ
    bool        m_bPosDebugOpen                      ; // �Լ���λ����ʾ����
    uint8       m_nKickCount                         ; // ��¼�ߵĴ���
    DWORD       m_dwEnterWorldClientTime             ; // ��¼��ҽ�����Ϸ����Ŀͻ���ʱ��
    DWORD       m_dwEnterWorldServerTime             ; // ��¼��ҽ�����Ϸ����ķ����ʱ��
    DWORD       m_dwClientLastSendMovingMsgTime      ; // ��¼�ͻ�������͸��������ƶ���Ϣ��ʱ��
    DWORD       m_dwClientLastSendMovingMsgServerTime; // �ͻ�������͸��������ƶ���Ϣ�ķ�����ʱ��
    bool        m_bAssaultMovingProcess              ; // ��漼�ܵ����⴦��
    DWORD       m_dwClientPassedTimePerCheck         ; // ÿ�β���ʱ�� �ͻ����ۼƵľ�����ʱ�䳤��
    float       m_fLastMoveSpeedPerCheck             ; // ÿ�μ�Ᵽ�����һ�ε��ƶ��ٶȣ�Ϊ��� ���״̬���ٵ��ж�
    D3DXVECTOR3 m_vStartMovingPosPerCheck            ; // ÿ�μ��ʱ��¼������
    D3DXVECTOR3 m_vMovingBufPerCheck                 ; // ÿ�ε��ƶ���������
    bool        m_bDeathAndWaitForRelive             ; // �Ƿ��ɫ�Ѿ��������ȴ�����
    char        m_cMoveSerial                        ; // �ƶ����к�
    uint8       m_ucCharStatus                       ; // �ε�״̬

    // ·���ƶ�
    bool        m_bHitchMoving                       ; // ����ƶ�
    bool        m_bHitchBack                         ; // �Ƿ�����·��˻���
    int         m_nTrafficID                         ; // ���·�ߵ�ID
    uint16      m_dwRouteStep                        ; // ��˵ĵڼ���·��
    GameTimerEx m_xHitchMoveTimer                    ; // ·���ƶ�ͣ��ʱ��
