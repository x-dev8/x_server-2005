

class CScriptCmd_GetBattleCamp: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetBattleCamp"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_GetCampBattleStatus: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetCampBattleStatus"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    int m_nType;
	int m_nCountryid;
};

class CScriptCmd_ShowCampBattleSignUp: public CScriptCommand
{
    virtual const char * GetCmdID() { return "ShowCampBattleSignUp"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
    
    int m_nType;
};

class CScriptCmd_SignUpCampBattle: public CScriptCommand
{
    virtual const char * GetCmdID() { return "SignUpCampBattle"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    int m_nType;
};

class CScriptCmd_ShowCampBattleEnter: public CScriptCommand
{
    virtual const char * GetCmdID() { return "ShowCampBattleEnter"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    int m_nType;
};

class CScriptCmd_EnterCampBattle: public CScriptCommand
{
    virtual const char * GetCmdID() { return "EnterCampBattle"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    int m_nType;
};

class CScriptCmd_KillCampBattleMonster: public CScriptCommand
{
    virtual const char * GetCmdID() { return "KillCampBattleMonster"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    int m_nMonsterID;
};

class CScriptCmd_CreateCampMonsterByPlayer: public CScriptCommand
{
    virtual const char * GetCmdID() { return "CreateCampMonster1"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    int m_nMonsterID;
    int m_nCount;
    float m_fRadius;
    float m_fBodySize;
    int m_nRouteID;
};

class CScriptCmd_CreateCampMonsterBySetting: public CScriptCommand
{
    virtual const char * GetCmdID() { return "CreateCampMonster2"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    int m_nMonsterID;
    int m_nCount;
    int m_nMapID;
    float m_fPosX;
    float m_fPosY;
    int m_nFightCamp;
    float m_fRadius;
    float m_fBodySize;
    int m_nRouteID;
};


class CScriptCmd_QueryCampBattleSignUp: public CScriptCommand
{
    virtual const char * GetCmdID() { return "QueryCampBattleSignUp"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    unsigned char uchType;              // 战场类型
};


class CScriptCmd_ChangeCampBattleScore: public CScriptCommand
{
    virtual const char * GetCmdID() { return "ChangeCampBattleScore"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    int IsRadOrBlue;
	int ChangeType;
	int Value;
};

class CScriptCmd_GetCampBattleFight : public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetCampBattleFight"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};
