#ifndef __PLAYERRELATIONHANDLE_H__
#define __PLAYERRELATIONHANDLE_H__

private:
    GameRelation* m_pRelation;       // ��ϵ�ṹָ��
    bool m_bReqRemoveMarriage;       // �Ƿ��������������
    bool m_bForceRemove;             // �Ƿ���ǿ�����
    unsigned int m_nLastQueryTime;   // �ϴβ�ѯ��ʱ��
    unsigned int m_nLastFindPersonTime;	// �ϴβ�ѯ��������ʱ��
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

    bool MasterLevelUp();       // ���������ȼ�
    int GetMasterLevel() const; // ��������ȼ�

    // ʦ������
    uint32 GetMasterValue() const; // ���ʦ������
    void OperateMasterValue( uint8 uchOperateType, uint32 nValue );

    bool IsFriend( GamePlayer* pPlayer );               // �Ƿ����ҵĺ���
    bool CheckBlackListPlayer( GamePlayer* pPlayer );   // �Ƿ����ҵĺ�����

    void InitRelationAttribute( RelationAttribute& xAttribute );

    void AddRelation( const char* szName, uint16 stRelation );  // ��ӹ�ϵ
    void UpdateFriendly( uint32 dwPlayerID, uint8 uchOperate, uint32 ustFriendly ); // ���º��Ѷ�

    enum EMarriageOp
    {
        EMO_GainQuest      = 0, // ��ȡ�������
        EMO_Marriage       = 1, // ���
        EMO_OpenLoveIsLand = 2, // �������ĵ�
    };

    GamePlayer* Script_CheckCanMarriage( int nOp );      // ����ж�����������, ���ضԷ���ָ��
    bool Script_AddMarriage();             // �ж��Ƿ�����������
    bool Script_CheckCanReceiveMarriageQuest( bool bMarriage ); // �ж��ܷ���ȡ��������
    bool Script_RemoveMarriage( bool bForceRemove );
    bool Script_CreateMarriageStage( unsigned short ustMapID );         // ��������ͼ����
    bool Script_FlyToMarriageMap( unsigned short ustMapID, float fX, float fY, float fDir );    // �������ͼ
    bool Script_CheckCanAddStudent( MsgAddRelationReq* pAddFriend );    // �ж��ܷ��ʦ��ͽ
    bool SendDeleteRelationCheckMessage( uint32 dwFriendID, uint16 ustRelation );    // ����ɾ����ϵȷ����Ϣ
    bool GetReqRemoveMarriage() { return m_bReqRemoveMarriage; }
    void SetReqRemoveMarriage( bool bValue ) { m_bReqRemoveMarriage = bValue; }
    bool GetForceRemove() { return m_bForceRemove; }
    void SetForceRemove( bool bValue ) { m_bForceRemove = bValue; }

    void GetRelationNameByTitle( unsigned short ustTitleID, char* szName, int nSize );
    const char* GetMarriageName();

    int GetMaxFriendlyLevel();
    bool IsCanReceiveFriendlyQuest();
    void SaveReceiveFriendlyQuest();

    void ProcessRelationKilledByPlayer( GamePlayer* pPlayer );      // ��ĳ���ɱ��
    void ProcessRelationKillPlayer( GamePlayer* pPlayer );          // ɱ��ĳ���     

    void RegisterRelation( unsigned short ustRelation );
    void QueryRegisterRelation( unsigned short ustRelation );
    void RemoveTeacher();
    void AddStudent();
    bool IsCanRegisterTeacher();
    bool IsCanRegisterStudent();
    int GetStudentCount();

    // ����ͽ�ܵľ���ӳ�
    float CalcStudentExpModulus();

    // ��ѯ��ʦ ���� ��ͽ��ʱ��
    void QueryAddRelationLeftTime( unsigned short ustRelation );

    // ����ͽ�������߼�
    void ProcessStudentLevelUp( uint32 nStudentID, bool bIsStudent, uint32 nRewardExp, uint32 nRewardMasterValue );

    // ��Ϣ����
    bool ProcessRelationMsg( Msg* pMsg );

    // ������Ӻ���
    void OnMsgAddRelationReq( Msg* pMsg );           

    // ������º�����Ϣ
    void OnMsgUpdateRelationReq( Msg* pMsg );     

    // ��һ�Ӧ��ӹ�ϵ
    void OnMsgInviterRelationAck( Msg* pMsg );      

    // ����ɾ������
    bool OnMsgDeleteRelationReq( Msg* pMsg );        

    // ɾ������ȷ��
    void OnDeleteRelationCheckAck( Msg* pMsg );

    // ������������
    void OnMsgRelationLockReq( Msg* pMsg );

    // �����������
    void OnMsgRelationUnLockReq( Msg* pMsg );

    // ��ѯ����
    void OnMsgQueryAttributeReq( Msg* pMsg );

    // ����ע�ᵽʦ��,���� ͽ���б�
    void OnMsgRegisterRelationReq( Msg* pMsg );

    // �����޸���������
    void OnMsgSetReceiveStrangerReq( Msg* pMsg );

    // �����޸ĸ���ǩ��
    void OnMsgChangeSignatureReq( Msg* pMsg );

    // ������ӷ���
    void OnMsgRelationGroupAddReq( Msg* pMsg );

    // �����޸ķ�������
    void OnMsgRelationGroupChangeNameReq( Msg* pMsg );

    // ����ı���ѷ���
    void OnMsgRelationGroupChangeReq( Msg* pMsg );

    // ����ı䱸ע
    void OnMsgRelationRemarkChangeReq( Msg* pMsg );

	// ������ĸ�������
	void OnMsgChangePersonalInfo( Msg* pMsg );

	// ����������ѯ���
	void OnMsgFindPlayerByCondition( Msg* pMsg );

#endif