#ifndef __COUNTRYSCRIPTDEFINE_H__
#define __COUNTRYSCRIPTDEFINE_H__

class CScriptCmd_IsHaveCountryMaster: public CScriptCommand
{
    virtual const char * GetCmdID() { return "IsHaveCountryMaster"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    unsigned char uchType;              // 战场类型
    unsigned char uchCountry;           // 国家
};

class CScriptCmd_ReceiveCountryMount: public CScriptCommand
{
    virtual const char * GetCmdID() { return "ReceiveCountryMount"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    unsigned char uchType;              // 战场类型
};

class CScriptCmd_CountryConenve: public CScriptCommand
{
    virtual const char * GetCmdID() { return "CountryConenve"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_IsCountryMaster: public CScriptCommand
{
    virtual const char * GetCmdID() { return "IsCountryMaster"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    unsigned char uchType;              // 战场类型
};

class CScriptCmd_IsCountryGuild: public CScriptCommand
{
    virtual const char * GetCmdID() { return "IsCountryGuild"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    unsigned char uchType;              // 战场类型
};

class CScriptCmd_IsCountryQueen: public CScriptCommand
{
    virtual const char * GetCmdID() { return "IsCountryQueen"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_AddCountryResource: public CScriptCommand
{
    virtual const char * GetCmdID() { return "AddCountryResource"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    unsigned char uchType;              // 资源类型
    unsigned int nValue;                // 值
};

class CScriptCmd_SubCountryResource: public CScriptCommand
{
    virtual const char * GetCmdID() { return "SubCountryResource"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    unsigned char uchType;              // 资源类型
    unsigned int nValue;                // 值
};

class CScriptCmd_GetCountryID: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetCountryID"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_IsCountryQuestOpen: public CScriptCommand
{
    virtual const char * GetCmdID() { return "IsCountryQuestOpen"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    unsigned char uchType;              // 类型
};


class CScriptCmd_GetCountryScore: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetCountryScore"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_AddCountryScore: public CScriptCommand
{
    virtual const char * GetCmdID() { return "AddCountryScore"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    int nValue;              // 数值
};

class CScriptCmd_SubCountryScore: public CScriptCommand
{
    virtual const char * GetCmdID() { return "SubCountryScore"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    int nValue;              // 数值
};

class CScriptCmd_SetCountryScore: public CScriptCommand
{
    virtual const char * GetCmdID() { return "SetCountryScore"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    int nValue;              // 数值
};

class CScriptCmd_GetCountryOfficial: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetCountryOfficial"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_GetWarSortIndex: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetWarSortIndex"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_IsInCountryWarFight: public CScriptCommand
{
    virtual const char * GetCmdID() { return "IsInCountryWarFight"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};

class CScriptCmd_SetCountryKing : public CScriptCommand
{
	virtual const char * GetCmdID() { return "SetCountryKing"; }
	BOOL Create( WordParser* words );
	void Execute( CScriptVM* vm );
	void Release(){ delete this; }
};

class CScriptCmd_SetCountryTribute : public CScriptCommand
{
	virtual const char * GetCmdID() { return "SetCountryTribute"; }
	BOOL Create( WordParser* words );
	void Execute( CScriptVM* vm );
	void Release(){ delete this; }

	int nValue;              // 数值
	int countryid;			//国家ID
};

class CScriptCmd_GetCountryTribute : public CScriptCommand
{
	virtual const char * GetCmdID() { return "GetCountryTribute"; }
	BOOL Create( WordParser* words );
	void Execute( CScriptVM* vm );
	void Release(){ delete this; }

	int countryid;			//国家ID
};


class CScriptCmd_AddCountryTribute : public CScriptCommand
{
	virtual const char * GetCmdID() { return "AddCountryTribute"; }
	BOOL Create( WordParser* words );
	void Execute( CScriptVM* vm );
	void Release(){ delete this; }

	int nValue;              // 数值
	int countryid;			//国家ID
};


class CScriptCmd_SubCountryTribute : public CScriptCommand
{
	virtual const char * GetCmdID() { return "SubCountryTribute"; }
	BOOL Create( WordParser* words );
	void Execute( CScriptVM* vm );
	void Release(){ delete this; }

	int nValue;              // 数值
	int countryid;			//国家ID
};


class CScriptCmd_IsPlayerKing : public CScriptCommand
{
	virtual const char * GetCmdID() { return "IsPlayKing"; }
	BOOL Create( WordParser* words );
	void Execute( CScriptVM* vm );
	void Release(){ delete this; }
}; 

class CScriptCmd_AddCountryInfo : public CScriptCommand
{
	virtual const char * GetCmdID() { return "AddCountryInfo"; }
	BOOL Create( WordParser* words );
	void Execute( CScriptVM* vm );
	void Release(){ delete this; }

	string Info;
	//char Info[CountryDefine::MaxCountryInfoLength];
	bool IsUseName;
	int Value;
}; 

#endif