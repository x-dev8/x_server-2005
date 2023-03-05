/********************************************************************
    Filename:    PlayerAntiAddictionModule.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

public:
    void               UpdateAntiAddiction();                                  // 防沉迷整体Update
    void               UpdateAntiAddictionNotify();                            // 定时通知防沉迷提示给客户端
    void               UpdateSaveAntiAddiction();                              // 保存防沉迷时间到平台    
    void               ExitSaveAntiAddiction();                                // 退出保存防沉迷时间到平台
    AntiAddictionState CalcAntiAddictionStatus( uint32 totalTime );            // 根据时长判断玩家防沉迷状态
    uint32             GetAntiAddictionLimitTime( uint8 nAntiAddictionStatus );// 根据时长得到进入此状态的时间
    uint32             GetAntiAddictionOnlineTime();                           // 得到防沉迷Total在线时间
    void               ResetAntiAddictionNotifyIndex();                        // 充值防沉迷定时通知计数
    void               SendMsgWallowAbout( uint8 nType );                      // 发防沉迷信息

protected:
    bool               IsRunAntiAddiction(); // 是否进行防沉迷逻辑

protected:
    bool                _bNeedAntiAddiction           ; // 是否需要防沉迷 玩家是成年人
    uint32              _nHaveSaveAntiAddtionDuration ; // 已经保存到平台的流失时间 单位分钟
    __int64             _nAntiAddtionStatusChangeStamp; // 防沉迷状态改变时候的时间搓
    uint32              _nAntiAddtionNotifyIndex      ; // 防沉迷通知计数
    GameTimerEx         _xUpdateAntiAddictionTimer    ; // 轮训AntiAddiction定时器
    uint32              _nAntiAddtionTimeCount        ; // 提交给平台的间隔时间个数