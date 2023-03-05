
public:
    virtual bool IsHaveTeacher();
    virtual int GetMasterLevel();                         // ���ʦ�ŵȼ�
    virtual bool MasterLevelUp();                         // ����ʦ�ŵȼ�
    virtual void AddMasterValue( unsigned short nValue ); // ����ʦ������
    virtual void SubMasterValue( unsigned short nValue ); // ����ʦ������
    virtual int GetMasterValue ();                        // ���ʦ������ֵ
    virtual void RegisterTeacher();                       // ʦ������
    virtual void RegisterStudent();                       // ͽ�ܱ���
    virtual void QueryTeacher();                          // ����ʦ��
    virtual void QueryStudent();                          // ����ͽ��
    virtual void RemoveTeacher();                         // �뿪ʦ��
    virtual void RemoveStudent();                         // ����ͽ��       
    virtual void QueryAddStudentLeftTime();               // ��ѯ��ͽʣ��ʱ��
    virtual void QueryAddTeacherLeftTime();               // ��ѯ��ʦʣ��ʱ��
    virtual void AddStudent();                            // ��ͽ
    virtual bool IsCanRegisterTeacher();                  // �ж��ܷ�ע��ʦ��
    virtual bool IsCanRegisterStudent();                  // �ж��ܷ�ע��ͽ��
    virtual int GetStudentCount();                        // ���ͽ�ܸ���

    // ��ú�������ߺ��Ѷȵĵȼ�
    virtual int GetMaxFriendlyLevel();

    virtual bool IsCanReceiveFriendlyQuest();
    virtual void SaveReceiveFriendlyQuest();

    virtual bool GetReqRemoveMarriage();
    virtual bool GetForceRemove();

    // ������
    virtual bool CheckCanMarriage();
    virtual bool AddMarriage();
    virtual bool CheckCanReceiveMarriageQuest( bool bMarriage );
    virtual bool RemoveMarriage( bool bForceRemove );
    virtual bool CreageMarriageStage( unsigned short ustMapID );
    virtual bool FlyToMarriageMap( unsigned short ustMapID, float fX, float fY, float fDir );