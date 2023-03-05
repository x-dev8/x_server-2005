#pragma once
class CScriptCmd_EnterGameGuildGeneralBattle: public CScriptCommand
{
    virtual const char * GetCmdID() { return "EnterGameGuildGeneralBattle"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};
class CScriptCmd_IsInGameGuildGeneralBattle: public CScriptCommand
{
    virtual const char * GetCmdID() { return "IsInGameGuildGeneralBattle"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};
class CScriptCmd_GetPlayerGameGuildGeneralBattleFigh: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetPlayerGameGuildGeneralBattleFigh"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};
class CScriptCmd_GetGameGuildGeneralBattleStates: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetGameGuildGeneralBattleStates"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }
};
class CScriptCmd_GetGameGuildGeneralBattleSource: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetGameGuildGeneralBattleSource"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

	unsigned int Fight;
};
class CScriptCmd_ChangeGameGuildGeneralBattleSource: public CScriptCommand
{
    virtual const char * GetCmdID() { return "ChangeGameGuildGeneralBattleSource"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

	unsigned int Fight;
	int Value;
};
class CScriptCmd_CreateGameGuildGeneralBattleMonsterByPlayer: public CScriptCommand
{
    virtual const char * GetCmdID() { return "CreateGameGuildGeneralBattleMonster1"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    int m_nMonsterID;
    int m_nCount;
    float m_fRadius;
    float m_fBodySize;
    int m_nRouteID;
};
class CScriptCmd_CreateGameGuildGeneralBattleMonsterBySetting: public CScriptCommand
{
    virtual const char * GetCmdID() { return "CreateGameGuildGeneralBattleMonster2"; }
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