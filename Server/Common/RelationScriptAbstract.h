

public:
    virtual bool IsHaveTeacher() = 0;           // �Ƿ���ʦ��
    virtual int GetMasterLevel() = 0;           // ���ʦ�ŵȼ�
    virtual bool MasterLevelUp() = 0;           // ����ʦ�ŵȼ�
    virtual void AddMasterValue( unsigned short nValue ) = 0;   // ����ʦ������
    virtual void SubMasterValue( unsigned short nValue ) = 0;   // ����ʦ������
    virtual int GetMasterValue () = 0;                          // ���ʦ������ֵ
    virtual void RegisterTeacher() = 0;         // ʦ������
    virtual void RegisterStudent() = 0;         // ͽ�ܱ���
    virtual void QueryTeacher() = 0;            // ����ʦ��
    virtual void QueryStudent() = 0;            // ����ͽ��
    virtual void RemoveTeacher() = 0;           // �뿪ʦ��
    virtual void RemoveStudent() = 0;           // ����ͽ��
    virtual void QueryAddStudentLeftTime() = 0; // ��ѯ��ͽʣ��ʱ��
    virtual void QueryAddTeacherLeftTime() = 0; // ��ѯ��ʦʣ��ʱ��
    virtual void AddStudent() = 0;              // ��ͽ
    virtual bool IsCanRegisterTeacher() = 0;   // �Ƿ���ע��ʦ��
    virtual bool IsCanRegisterStudent() = 0;   // �Ƿ���ע��ʦ��
    virtual int GetStudentCount() = 0;          // ���ͽ�ܸ���

    virtual int GetMaxFriendlyLevel() = 0;

    virtual bool IsCanReceiveFriendlyQuest() = 0;
    virtual void SaveReceiveFriendlyQuest() = 0;

    virtual bool GetReqRemoveMarriage() = 0;
    virtual bool GetForceRemove() = 0;

    // ������
    virtual bool CheckCanMarriage() = 0;
    virtual bool AddMarriage() = 0;
    virtual bool CheckCanReceiveMarriageQuest( bool bMarriage ) = 0;
    virtual bool RemoveMarriage( bool bForceRemove ) = 0;
    virtual bool CreageMarriageStage( unsigned short ustMapID ) = 0;
    virtual bool FlyToMarriageMap( unsigned short ustMapID, float fX, float fY, float fDir ) = 0;
