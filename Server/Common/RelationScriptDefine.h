

class CScriptCmd_IsHaveTeacher: public CScriptCommand
{
    virtual const char * GetCmdID() { return "IsHaveTeacher"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};


class CScriptCmd_GetMasterLevel: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetMasterLevel"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_MasterLevelUp: public CScriptCommand
{
    virtual const char * GetCmdID() { return "MasterLevelUp"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_AddMasterValue: public CScriptCommand
{
    virtual const char * GetCmdID() { return "AddMasterValue"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    //unsigned short m_ustValue;
    CScriptCmd__SetVar::Param m_Value;
};

class CScriptCmd_SubMasterValue: public CScriptCommand
{
    virtual const char * GetCmdID() { return "SubMasterValue"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    //unsigned short m_ustValue;
    CScriptCmd__SetVar::Param m_Value;
};


class CScriptCmd_GetMasterValue: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetMasterValue"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    unsigned short m_ustValue;
};

class CScriptCmd_RegisterTeacher: public CScriptCommand
{
    virtual const char * GetCmdID() { return "RegisterTeacher"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};


class CScriptCmd_RegisterStudent: public CScriptCommand
{
    virtual const char * GetCmdID() { return "RegisterStudent"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

};

class CScriptCmd_QueryTeacher: public CScriptCommand
{
    virtual const char * GetCmdID() { return "QueryTeacher"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_QueryStudent: public CScriptCommand
{
    virtual const char * GetCmdID() { return "QueryStudent"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_CheckCanMarriage: public CScriptCommand
{
    virtual const char * GetCmdID() { return "CheckCanMarriage"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_AddMarriage: public CScriptCommand
{
    virtual const char * GetCmdID() { return "AddMarriage"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_RemoveMarriage: public CScriptCommand
{
    virtual const char * GetCmdID() { return "RemoveMarriage"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    bool m_bForceRemove;
};

class CScriptCmd_CheckCanReceiveMarriageQuest: public CScriptCommand
{
    virtual const char * GetCmdID() { return "CheckCanReceiveMarriageQuest"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    bool m_bMarriage;
};

class CScriptCmd_CreageMarriageStage: public CScriptCommand
{
    virtual const char * GetCmdID() { return "CreageMarriageStage"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    unsigned short m_ustMapID;
};


class CScriptCmd_FlyToMarriageMap: public CScriptCommand
{
    virtual const char * GetCmdID() { return "FlyToMarriageMap"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    unsigned short m_ustMapID;
    float m_fX;
    float m_fY;
    float m_fDir;
};


class CScriptCmd_GetMaxFriendlyLevel: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetMaxFriendlyLevel"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_IsCanReceiveFriendlyQuest: public CScriptCommand
{
    virtual const char * GetCmdID() { return "IsCanReceiveFriendlyQuest"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};


class CScriptCmd_SaveReceiveFriendlyQuest: public CScriptCommand
{
    virtual const char * GetCmdID() { return "SaveReceiveFriendlyQuest"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_GetReqRemoveMarriage: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetReqRemoveMarriage"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_GetForceRemove: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetForceRemove"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_AddStudent: public CScriptCommand
{
    virtual const char * GetCmdID() { return "AddStudent"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_RemoveTeacher: public CScriptCommand
{
    virtual const char * GetCmdID() { return "RemoveTeacher"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};



class CScriptCmd_IsCanRegisterTeacher: public CScriptCommand
{
    virtual const char * GetCmdID() { return "IsCanRegisterTeacher"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_IsCanRegisterStudent: public CScriptCommand
{
    virtual const char * GetCmdID() { return "IsCanRegisterStudent"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};


class CScriptCmd_GetStudentCount: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetStudentCount"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_QueryAddStudentLeftTime: public CScriptCommand
{
    virtual const char * GetCmdID() { return "QueryAddStudentLeftTime"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_QueryAddTeacherLeftTime: public CScriptCommand
{
    virtual const char * GetCmdID() { return "QueryAddTeacherLeftTime"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};
