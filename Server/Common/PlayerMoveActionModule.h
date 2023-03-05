public:
    // 发消息给玩家 系统右边框的消息
    virtual void ShowInfo       ( bool bTile, int type, const char* string, ... );
    virtual void ShowInfo       ( const char* string, bool bTile = false, int type = 282 );
    virtual void ShowInfo       ( bool bTile, int type, unsigned short ustStringID, UnionParam* pParam = NULL, int nCount = 0 );
    virtual bool IsCanSwitchStage();     
    virtual void SendVerifyPos  (); // 发送矫正坐标消息    
    virtual void TellClient     ( const char* string, ... );   
    virtual void TellClient     ( unsigned short ustStringID, UnionParam *pParam = NULL, int nCount = 0 );
    virtual void ShowFormatInfo ( const char* szFormat, ... );
    virtual void ShowMsgBox     ( const char* string, ... );

    void         SendChangeMapMessageToClient( DWORD dwMapId, short nTileX, short nTileY, BYTE byDir, float fDir ); // 地图跳转
    void         SetDeathWaitForRelive( bool bFlag ) { m_bDeathAndWaitForRelive = bFlag; }

    // 正在冲锋移动
    void         DoAssaultMoving( float fDistance, int nInstantMovingType );                       

    // 个人骑乘
    bool         DoHitch( int nTrafficID, bool bBack );             // 进行搭乘移动
    void         DoHitchMoving( int nTrafficID );                   // 进行搭乘移动
    void         CancelHitchMoving();                               // 结束搭乘移动
    int          GetCurTrafficID();                                 // 获取当前路线的ID    
    long         TryRespondChangeStage();                           // 尝试响应客户端切场景效应

    // 移动
    BOOL         CheckMoving();                                    // 检测移动消息的合法性
    bool         CheckPosRightful();                               // 检测位置的正确性
    void         CheckCredit();                                    // 检测荣誉值是否正确
    bool         CheckMovingMsgSendTime( DWORD dwSendTime );       // 检测移动消息上发时间的正确性
    void         ResetCheckMoving();                               // 重置要测试的移动信息(开始新一轮的移动测试)
    void         SendVerifyPos( float fx, float fy );              // 矫正坐标    
    bool         IsNeedFixWorldCoordinate( int tileX, int tileY ); // 传入新的格子坐标 判断是否需要纠正客户端世界坐标系坐标 float

    // 吟唱打断
    void         IntonateInterrupt( int8 nType, char* szCallFun );

    DWORD        GetLastReceiveMoveMessageTime() const         { return dwLastReceiveMoveMessageTime; }
    void         SetLastReceiveMoveMessageTime( DWORD dwtime ) { dwLastReceiveMoveMessageTime = dwtime; }

protected:
    // 消息
    virtual void OnQueryMove        ( Msg* pMsg );
    virtual void OnQueryDisplayName ( Msg* pMsg );
    virtual void OnGetLag           ( Msg* pMsg );
    virtual void OnPingMsg          ( Msg* pMsg );      // 对客户端法送过来的PING消息的处理
    virtual void OnGetPlayerInfo    ( Msg* pMsg );      // 客户端发过来的请求知道莫个npc的数据

    // 处理玩家移动的逻辑
    virtual void OnMsgPlayerMovingPos     ( const Msg* pMsg );
    virtual void OnMsgPlayerMovingPosToDir( const Msg* pMsg );
    virtual void OnMsgPlayerPos           ( const Msg* pMsg );
    virtual void OnMsgPlayerDir           ( const Msg* pMsg );
    virtual void OnMsgPlayerPosAndDir     ( const Msg* pMsg );
    virtual void OnReqChangeDir           ( const Msg* pMsg );

	// 提交一个移动合法性分析请求消息
	void ReqPlayerMoveAnalysis( D3DXVECTOR3& posMoveTo );

    // 行为动作
    virtual void OnMsgIntonateInterrupt( const Msg* pMsg );
    virtual void OnMsgJump             ( const Msg* pMsg );
    virtual void OnMsgDrawWeapon       ( const Msg* pMsg );
    virtual void OnMsgDrawInWeapon     ( const Msg* pMsg );
    virtual void OnQueryCharAround     ( const Msg* pMsg );
    virtual void OnMsgReadytoUseSpecialSkill( Msg* pMsg  );

public:
    CGraphicCodeCheck m_graphiccodecheck;

    //////////////////////////////////////////////////////////////////////////
    // 成员变量
protected:
    uint32      dwLastReceiveMoveMessageTime         ; // 最后一次收到移动信息的时间
    DWORD       _lastVerifyPosTime                   ; // 检查人物位置的时间记录
    DWORD       _lastHitchMovingTime                 ; // 发送搭乘移动消息的时间记录
    int         m_nCredit                            ; // 记录玩家的信誉值
    bool        m_bPosDebugOpen                      ; // 自己的位置显示开关
    uint8       m_nKickCount                         ; // 记录踢的次数
    DWORD       m_dwEnterWorldClientTime             ; // 记录玩家进入游戏世界的客户端时间
    DWORD       m_dwEnterWorldServerTime             ; // 记录玩家进入游戏世界的服务端时间
    DWORD       m_dwClientLastSendMovingMsgTime      ; // 记录客户端最后发送给服务器移动消息的时间
    DWORD       m_dwClientLastSendMovingMsgServerTime; // 客户端最后发送给服务器移动消息的服务器时间
    bool        m_bAssaultMovingProcess              ; // 冲锋技能的特殊处理
    DWORD       m_dwClientPassedTimePerCheck         ; // 每次测试时候 客户端累计的经过的时间长度
    float       m_fLastMoveSpeedPerCheck             ; // 每次检测保存的上一次的移动速度，为冲锋 坚决状态加速的判定
    D3DXVECTOR3 m_vStartMovingPosPerCheck            ; // 每次检测时记录的坐标
    D3DXVECTOR3 m_vMovingBufPerCheck                 ; // 每次的移动量保存器
    bool        m_bDeathAndWaitForRelive             ; // 是否角色已经死亡，等待复生
    char        m_cMoveSerial                        ; // 移动序列号
    uint8       m_ucCharStatus                       ; // 拔刀状态

    // 路点移动
    bool        m_bHitchMoving                       ; // 搭乘移动
    bool        m_bHitchBack                         ; // 是否是沿路搭乘回来
    int         m_nTrafficID                         ; // 搭乘路线的ID
    uint16      m_dwRouteStep                        ; // 搭乘的第几个路点
    GameTimerEx m_xHitchMoveTimer                    ; // 路点移动停留时间
