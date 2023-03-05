

class CScriptCmd_IsHaveFamily: public CScriptCommand
{
	virtual const char * GetCmdID() { return "IsHaveFamily"; }
	BOOL Create( WordParser* words );
	void Execute( CScriptVM* vm );
	void Release(){ delete this; }
};

class CScriptCmd_IsFamilyMaster: public CScriptCommand
{
	virtual const char * GetCmdID() { return "IsFamilyMaster"; }
	BOOL Create( WordParser* words );
	void Execute( CScriptVM* vm );
	void Release(){ delete this; }
};

class CScriptCmd_IsExistFamily: public CScriptCommand
{
	virtual const char * GetCmdID() { return "IsExistFamily"; }
	BOOL Create( WordParser* words );
	void Execute( CScriptVM* vm );
	void Release(){ delete this; }
};