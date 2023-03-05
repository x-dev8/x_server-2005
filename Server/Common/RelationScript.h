
public:
    virtual bool IsHaveTeacher();
    virtual int GetMasterLevel();                         // 获得师门等级
    virtual bool MasterLevelUp();                         // 提升师门等级
    virtual void AddMasterValue( unsigned short nValue ); // 增加师门威望
    virtual void SubMasterValue( unsigned short nValue ); // 减少师门威望
    virtual int GetMasterValue ();                        // 获得师门威望值
    virtual void RegisterTeacher();                       // 师傅报名
    virtual void RegisterStudent();                       // 徒弟报名
    virtual void QueryTeacher();                          // 查找师傅
    virtual void QueryStudent();                          // 查找徒弟
    virtual void RemoveTeacher();                         // 离开师门
    virtual void RemoveStudent();                         // 开出徒弟       
    virtual void QueryAddStudentLeftTime();               // 查询收徒剩余时间
    virtual void QueryAddTeacherLeftTime();               // 查询拜师剩余时间
    virtual void AddStudent();                            // 收徒
    virtual bool IsCanRegisterTeacher();                  // 判断能否注册师傅
    virtual bool IsCanRegisterStudent();                  // 判断能否注册徒弟
    virtual int GetStudentCount();                        // 获得徒弟个数

    // 获得好友里最高好友度的等级
    virtual int GetMaxFriendlyLevel();

    virtual bool IsCanReceiveFriendlyQuest();
    virtual void SaveReceiveFriendlyQuest();

    virtual bool GetReqRemoveMarriage();
    virtual bool GetForceRemove();

    // 结婚相关
    virtual bool CheckCanMarriage();
    virtual bool AddMarriage();
    virtual bool CheckCanReceiveMarriageQuest( bool bMarriage );
    virtual bool RemoveMarriage( bool bForceRemove );
    virtual bool CreageMarriageStage( unsigned short ustMapID );
    virtual bool FlyToMarriageMap( unsigned short ustMapID, float fX, float fY, float fDir );