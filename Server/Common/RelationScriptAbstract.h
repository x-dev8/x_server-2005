

public:
    virtual bool IsHaveTeacher() = 0;           // 是否有师傅
    virtual int GetMasterLevel() = 0;           // 获得师门等级
    virtual bool MasterLevelUp() = 0;           // 提升师门等级
    virtual void AddMasterValue( unsigned short nValue ) = 0;   // 增加师门威望
    virtual void SubMasterValue( unsigned short nValue ) = 0;   // 减少师门威望
    virtual int GetMasterValue () = 0;                          // 获得师门威望值
    virtual void RegisterTeacher() = 0;         // 师傅报名
    virtual void RegisterStudent() = 0;         // 徒弟报名
    virtual void QueryTeacher() = 0;            // 查找师傅
    virtual void QueryStudent() = 0;            // 查找徒弟
    virtual void RemoveTeacher() = 0;           // 离开师门
    virtual void RemoveStudent() = 0;           // 开出徒弟
    virtual void QueryAddStudentLeftTime() = 0; // 查询收徒剩余时间
    virtual void QueryAddTeacherLeftTime() = 0; // 查询拜师剩余时间
    virtual void AddStudent() = 0;              // 收徒
    virtual bool IsCanRegisterTeacher() = 0;   // 是否能注册师傅
    virtual bool IsCanRegisterStudent() = 0;   // 是否能注册师傅
    virtual int GetStudentCount() = 0;          // 获得徒弟个数

    virtual int GetMaxFriendlyLevel() = 0;

    virtual bool IsCanReceiveFriendlyQuest() = 0;
    virtual void SaveReceiveFriendlyQuest() = 0;

    virtual bool GetReqRemoveMarriage() = 0;
    virtual bool GetForceRemove() = 0;

    // 结婚相关
    virtual bool CheckCanMarriage() = 0;
    virtual bool AddMarriage() = 0;
    virtual bool CheckCanReceiveMarriageQuest( bool bMarriage ) = 0;
    virtual bool RemoveMarriage( bool bForceRemove ) = 0;
    virtual bool CreageMarriageStage( unsigned short ustMapID ) = 0;
    virtual bool FlyToMarriageMap( unsigned short ustMapID, float fX, float fY, float fDir ) = 0;
