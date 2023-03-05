#ifndef __PLAYERRELATIONHANDLE_H__
#define __PLAYERRELATIONHANDLE_H__

private:
    GameRelation* m_pRelation;       // 关系结构指针
    bool m_bReqRemoveMarriage;       // 是否是主动请求离婚
    bool m_bForceRemove;             // 是否是强制离婚
    unsigned int m_nLastQueryTime;   // 上次查询的时间
    unsigned int m_nLastFindPersonTime;	// 上次查询个人资料时间
protected:
    bool CheckCanMarriage( unsigned int dwMarriageID, int nOp );
    void SendAddRelationAckMessage( int nRelation, int nGroupID, const char* szName, int nResult );
public:
    void InitPlayerRelation( GameRelation* pRelation );
    GameRelation* GetRelation()  { return m_pRelation; }
    uint32 GetTeacherID() const  { return m_pRelation->GetTeacherID(); }
    bool IsHaveTeacher() const   { return GetTeacherID() != RelationDefine::InitID; }
    uint32 GetMarriageID() const { return m_pRelation->GetMarriageID(); }
    bool IsHaveMarriage() const  { return GetMarriageID() != RelationDefine::InitID; }
    bool IsHaveStudent() const { return m_pRelation->GetStudentCount() > 0; }

    bool MasterLevelUp();       // 提升威望等级
    int GetMasterLevel() const; // 获得威望等级

    // 师门威望
    uint32 GetMasterValue() const; // 获得师门威望
    void OperateMasterValue( uint8 uchOperateType, uint32 nValue );

    bool IsFriend( GamePlayer* pPlayer );               // 是否是我的好友
    bool CheckBlackListPlayer( GamePlayer* pPlayer );   // 是否是我的黑名单

    void InitRelationAttribute( RelationAttribute& xAttribute );

    void AddRelation( const char* szName, uint16 stRelation );  // 添加关系
    void UpdateFriendly( uint32 dwPlayerID, uint8 uchOperate, uint32 ustFriendly ); // 更新好友度

    enum EMarriageOp
    {
        EMO_GainQuest      = 0, // 领取结婚任务
        EMO_Marriage       = 1, // 结婚
        EMO_OpenLoveIsLand = 2, // 开启爱心岛
    };

    GamePlayer* Script_CheckCanMarriage( int nOp );      // 如果判断满足结婚条件, 返回对方的指针
    bool Script_AddMarriage();             // 判断是否满足结婚条件
    bool Script_CheckCanReceiveMarriageQuest( bool bMarriage ); // 判断能否领取婚姻任务
    bool Script_RemoveMarriage( bool bForceRemove );
    bool Script_CreateMarriageStage( unsigned short ustMapID );         // 创建结婚地图场景
    bool Script_FlyToMarriageMap( unsigned short ustMapID, float fX, float fY, float fDir );    // 进入结婚地图
    bool Script_CheckCanAddStudent( MsgAddRelationReq* pAddFriend );    // 判断能否拜师收徒
    bool SendDeleteRelationCheckMessage( uint32 dwFriendID, uint16 ustRelation );    // 发送删除关系确认消息
    bool GetReqRemoveMarriage() { return m_bReqRemoveMarriage; }
    void SetReqRemoveMarriage( bool bValue ) { m_bReqRemoveMarriage = bValue; }
    bool GetForceRemove() { return m_bForceRemove; }
    void SetForceRemove( bool bValue ) { m_bForceRemove = bValue; }

    void GetRelationNameByTitle( unsigned short ustTitleID, char* szName, int nSize );
    const char* GetMarriageName();

    int GetMaxFriendlyLevel();
    bool IsCanReceiveFriendlyQuest();
    void SaveReceiveFriendlyQuest();

    void ProcessRelationKilledByPlayer( GamePlayer* pPlayer );      // 被某玩家杀死
    void ProcessRelationKillPlayer( GamePlayer* pPlayer );          // 杀死某玩家     

    void RegisterRelation( unsigned short ustRelation );
    void QueryRegisterRelation( unsigned short ustRelation );
    void RemoveTeacher();
    void AddStudent();
    bool IsCanRegisterTeacher();
    bool IsCanRegisterStudent();
    int GetStudentCount();

    // 计算徒弟的经验加成
    float CalcStudentExpModulus();

    // 查询拜师 或者 收徒的时间
    void QueryAddRelationLeftTime( unsigned short ustRelation );

    // 处理徒弟升级逻辑
    void ProcessStudentLevelUp( uint32 nStudentID, bool bIsStudent, uint32 nRewardExp, uint32 nRewardMasterValue );

    // 消息处理
    bool ProcessRelationMsg( Msg* pMsg );

    // 请求添加好友
    void OnMsgAddRelationReq( Msg* pMsg );           

    // 请求更新好友信息
    void OnMsgUpdateRelationReq( Msg* pMsg );     

    // 玩家回应添加关系
    void OnMsgInviterRelationAck( Msg* pMsg );      

    // 请求删除好友
    bool OnMsgDeleteRelationReq( Msg* pMsg );        

    // 删除好友确认
    void OnDeleteRelationCheckAck( Msg* pMsg );

    // 请求锁定仇人
    void OnMsgRelationLockReq( Msg* pMsg );

    // 请求解锁仇人
    void OnMsgRelationUnLockReq( Msg* pMsg );

    // 查询好友
    void OnMsgQueryAttributeReq( Msg* pMsg );

    // 请求注册到师傅,或者 徒弟列表
    void OnMsgRegisterRelationReq( Msg* pMsg );

    // 请求修改聊天设置
    void OnMsgSetReceiveStrangerReq( Msg* pMsg );

    // 请求修改个性签名
    void OnMsgChangeSignatureReq( Msg* pMsg );

    // 请求添加分组
    void OnMsgRelationGroupAddReq( Msg* pMsg );

    // 请求修改分组名字
    void OnMsgRelationGroupChangeNameReq( Msg* pMsg );

    // 请求改变好友分组
    void OnMsgRelationGroupChangeReq( Msg* pMsg );

    // 请求改变备注
    void OnMsgRelationRemarkChangeReq( Msg* pMsg );

	// 请求更改各人资料
	void OnMsgChangePersonalInfo( Msg* pMsg );

	// 根据条件查询玩家
	void OnMsgFindPlayerByCondition( Msg* pMsg );

#endif