

class CScriptCmd_GetGuildId: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetGuildId"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_IsHaveGuild: public CScriptCommand
{
    virtual const char * GetCmdID() { return "IsHaveGuild"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_IsGuildMaster: public CScriptCommand
{
    virtual const char * GetCmdID() { return "IsGuildMaster"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};


class CScriptCmd_GetGuildOffer: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetGuildOffer"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};


class CScriptCmd_AddGuildOffer: public CScriptCommand
{
    virtual const char * GetCmdID() { return "AddGuildOffer"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    //int nCredit;
    CScriptCmd__SetVar::Param m_Credit;
};

class CScriptCmd_DecGuildOffer: public CScriptCommand
{
    virtual const char * GetCmdID() { return "DecGuildOffer"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    //int nCredit;
    CScriptCmd__SetVar::Param m_Credit;
};

class CScriptCmd_GetGuildActivity: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetGuildActivity"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};


class CScriptCmd_AddGuildActivity: public CScriptCommand
{
    virtual const char * GetCmdID() { return "AddGuildActivity"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    int nCredit;
};

class CScriptCmd_DecGuildActivity: public CScriptCommand
{
    virtual const char * GetCmdID() { return "DecGuildActivity"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    int nCredit;
};

class CScriptCmd_GetGuildBuild: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetGuildBuild"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_AddGuildBuild: public CScriptCommand
{
    virtual const char * GetCmdID() { return "AddGuildBuild"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    //int nCredit;
    CScriptCmd__SetVar::Param m_Credit;
};

class CScriptCmd_DecGuildBuild: public CScriptCommand
{
    virtual const char * GetCmdID() { return "DecGuildBuild"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    //int nCredit;
    CScriptCmd__SetVar::Param m_Credit;
};

class CScriptCmd_GetGuildMoney: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetGuildMoney"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_AddGuildMoney: public CScriptCommand
{
    virtual const char * GetCmdID() { return "AddGuildMoney"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    //int nValue;
    CScriptCmd__SetVar::Param m_Value;
};

class CScriptCmd_DecGuildMoney: public CScriptCommand
{
    virtual const char * GetCmdID() { return "DecGuildMoney"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    //int nValue;
    CScriptCmd__SetVar::Param m_Value;
};

class CScriptCmd_GetGuildMission: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetGuildMission"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_AddGuildMission: public CScriptCommand
{
    virtual const char * GetCmdID() { return "AddGuildMission"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    int nValue;
};

class CScriptCmd_DecGuildMission: public CScriptCommand
{
    virtual const char * GetCmdID() { return "DecGuildMission"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    int nValue;
};

class CScriptCmd_GetGuildSalary: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetGuildSalary"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_AddGuildSalary: public CScriptCommand
{
    virtual const char * GetCmdID() { return "AddGuildSalary"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    int nValue;
};

class CScriptCmd_DecGuildSalary: public CScriptCommand
{
    virtual const char * GetCmdID() { return "DecGuildSalary"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    int nValue;
};


class CScriptCmd_GetGuildLevel: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetGuildLevel"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_SetGuildLevel: public CScriptCommand
{
    virtual const char * GetCmdID() { return "SetGuildLevel"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    int nValue;
};

class CScriptCmd_AddGuildVar: public CScriptCommand
{
    virtual const char * GetCmdID() { return "AddGuildVar"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    //int m_nIndex;
    //int m_nValue;
    CScriptCmd__SetVar::Param m_Index;
    CScriptCmd__SetVar::Param m_Value;
};

class CScriptCmd_DecGuildVar: public CScriptCommand
{
    virtual const char * GetCmdID() { return "DecGuildVar"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    //int m_nIndex;
    //int m_nValue;
    CScriptCmd__SetVar::Param m_Index;
    CScriptCmd__SetVar::Param m_Value;
};

class CScriptCmd_SetGuildVar: public CScriptCommand
{
    virtual const char * GetCmdID() { return "SetGuildVar"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    //int m_nIndex;
    //int m_nValue;
    CScriptCmd__SetVar::Param m_Index;
    CScriptCmd__SetVar::Param m_Value;
};

class CScriptCmd_GetGuildVar: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetGuildVar"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    //int m_nIndex;
    CScriptCmd__SetVar::Param m_Index;
};

class CScriptCmd_RecordGuildTimeVar: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetGuildVar"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    //int nVarId;
    CScriptCmd__SetVar::Param m_VarId;
};

class CScriptCmd_IsGuildTimeVarPassOneDay: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetGuildVar"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    int nVarId;
};


class CScriptCmd_ClearGuildTimeVar: public CScriptCommand
{
    virtual const char * GetCmdID() { return "ClearGuildExpiredVar"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    //int nVarId;
    CScriptCmd__SetVar::Param m_VarId;
    CScriptCmd__SetVar::Param m_ClearVarId;
};

class CScriptCmd_GuildLevelUp: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GuildLevelUp"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_GuildOfferBuild: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GuildOfferBuild"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_GuildCollect: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GuildCollect"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_GuildMasterDelate: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GuildMasterDelate"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_GuildDonate: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GuildDonate"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_GuildQuestRelease: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GuildQuestRelease"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    int nQuestID;
};

class CScriptCmd_GetGuildReleaseQuest: public CScriptCommand
{
	virtual const char * GetCmdID() { return "GetGuildReleaseQuest"; }
	BOOL Create( WordParser* words );
	void Execute( CScriptVM* vm );
	void Release(){ delete this; }
};

class CScriptCmd_AddGuildBuffByMapID: public CScriptCommand
{
	virtual const char * GetCmdID() { return "AddGuildBuffByMapID"; }
	BOOL Create( WordParser* words );
	void Execute( CScriptVM* pVM);
	void Release(){ delete this; }

	CScriptCmd__SetVar::Param m_MapID;
	CScriptCmd__SetVar::Param m_BuffID;
    CScriptCmd__SetVar::Param m_BuffLevel;
};

class CScriptCmd_GuildShopLevel: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GuildShopLevelUp"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    int nLevel;
};

class CScriptCmd_GuildConvene: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GuildConvene"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_GetGuildMemberPosition: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetGuildMemberPosition"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};
