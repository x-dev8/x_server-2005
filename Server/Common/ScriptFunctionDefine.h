#ifndef __SCRIPT_FUNCTION_DEFINE_H__
#define __SCRIPT_FUNCTION_DEFINE_H__

#include "ScriptFunctionSupport.h"
#include "ScriptCommand.h"

namespace ServerTable
{
    enum
    {
        eNone,
        eOfficialLevel
    };
};
//
// 设置系统变量
class CScriptCmd__SetVar:public CScriptCommand
{
public:
    enum
    {
        MAX_SCRIPT_SET_PARAM = 4
    };
    struct Param
    {
        Param()
        {
            bIsKey = false;
            nNumber = 0;
            pszString = NULL;
        }
        ~Param()
        {
            if( pszString )
            {
                delete[] pszString;
                pszString = NULL;
            }
        }
        void        SetNumber( int n ){ nNumber = n; }
        int         GetNumber(){ return nNumber; }
        void        SetString( const char* p );
        const char* GetString(){ return pszString; }
        void        SetIsKey( bool b ){ bIsKey = b; }
        bool        IsKey(){ return bIsKey; }

    private:
        int nNumber;
        char* pszString;
        bool bIsKey;
    };
public:
    virtual const char * GetCmdID(){ return "set"; }
    BOOL        Create( WordParser* words );
    void        Execute( CScriptVM* vm );
    void        Release(){ delete this; }

    Param        m_params[MAX_SCRIPT_SET_PARAM];
    int            m_nParamCount;
};
// 显示对话框
class CScriptCmd_Dlg:public CScriptCommand
{
public:
    virtual const char * GetCmdID(){ return "dlg"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    std::string               m_strText;
    std::vector<int>          m_vtKey;
    int                       iButtionFlag;
    CScriptCmd__SetVar::Param _paramValue;
};
// 显示对话框
class CScriptCmd_NpcMainDlg:public CScriptCommand
{
public:
    virtual const char * GetCmdID(){ return "NpcMainDlg"; }
    BOOL Create( WordParser* words );
    void Execute( CScriptVM* vm );
    void Release(){ delete this; }

    std::string               m_strText;
    std::vector<int>          m_vtKey;
    int                       iButtionFlag;
    CScriptCmd__SetVar::Param _paramValue;
};

// 商店
class CScriptCmd_Shop:public CScriptCommand
{
public:
    virtual const char * GetCmdID(){ return "shop"; }
    BOOL        Create( WordParser* words );
//    int            m_nItemCount;
//    short        m_stItemIds[MAX_SCRIPT_SHOP_ITEM];
    int            m_nShopId;
    void        Execute( CScriptVM* vm );
    void        Release(){ delete this; }
};
// 切换地图
class CScriptCmd_FlyToMap:public CScriptCommand
{
public:
    virtual const char * GetCmdID(){ return "flytomap"; }
    BOOL        Create( WordParser* words );
    void        Release(){ delete this; }
    //int         m_nMapId;
    //POINT       m_ptLoc;
    // 下面三个参数可以使用变量传入
    CScriptCmd__SetVar::Param m_nMapId;
    CScriptCmd__SetVar::Param m_LocX;
    CScriptCmd__SetVar::Param m_LocY;

    float       m_fDir;
    unsigned char m_chFlyType;            // 0 = 个人 1 = 队伍  2 = 公会
    bool        m_bCheckHeader;         // 是否判断队长
    //int         m_nQuestID;
    CScriptCmd__SetVar::Param m_QuestId;    // 任务ID
    void        Execute( CScriptVM* vm );
};

// 切换地图
class CScriptCmd_CallAllTeamPlayerFlyToMap:public CScriptCommand
{
public:
    virtual const char * GetCmdID(){ return "CallAllTeamPlayerFlyToMap"; }
    BOOL        Create( WordParser* words );
    void        Release(){ delete this; }
    int         m_nMapId;
    POINT       m_ptLoc;
    float       m_fDir;
    void        Execute( CScriptVM* vm );
};

class CScriptCmd_Broadcast:public CScriptCommand
{
public:
    CScriptCmd_Broadcast(){}
    virtual const char * GetCmdID() { return "bc"; }
    BOOL        Create( WordParser* words );
    void        Execute( CScriptVM* vm );
    void        Release(){ delete this; }
    //
    int m_nType;      // 公告类型, 0 = 本服务器系统  1 = 全世界系统； 3 = 本服务器公告  4 = 全世界器公告
    std::string m_strMsg;
    std::vector<int> m_vtKey;
};

class CScriptCmd_Ask: public CScriptCommand
{
    enum
    {
        eMaxItem       = 8,
        eMaxItemLength = 32,
        eBufferLength  = 1024,
    };
    virtual const char * GetCmdID() { return "ask"; }
    BOOL        Create( WordParser* words );
    void        Execute( CScriptVM* vm );
    void        Release(){ delete this; }

    char        m_szItems[eBufferLength];
};

class CScriptCmd_RemoveAllEquip: public CScriptCommand
{
    virtual const char * GetCmdID() { return "RemoveAllEquip"; }
    BOOL        Create( WordParser* words );
    void        Execute( CScriptVM* vm );
    void        Release(){ delete this; }
};

class CScriptCmd_SetBornPoint: public CScriptCommand
{
    virtual const char * GetCmdID() { return "SetBornPoint"; }
    BOOL           Create( WordParser* words );
    void           Execute( CScriptVM* vm );
    void        Release(){ delete this; }

    DWORD    m_dwMapID;
    int        m_iPosX, m_iPosY;
};

//{ add by ^^
class CScriptCmd_HaveThisItem: public CScriptCommand
{
    virtual const char * GetCmdID() { return "HaveThisItem"; }
    BOOL           Create( WordParser* words );
    void           Execute( CScriptVM* vm );
    void        Release(){ delete this; }

    char            m_ItemName[100];
    int             m_ItemNum;
};

class CScriptCmd_HaveThisTitle : public CScriptCommand
{
    virtual const char * GetCmdID() { return "HaveThisTitle"; }
    BOOL           Create( WordParser* words );
    void           Execute( CScriptVM* vm );
    void        Release(){ delete this; }

    //unsigned short m_nTitleID;
    CScriptCmd__SetVar::Param m_TitleID;
};

class CScriptCmd_RemoveThisItem: public CScriptCommand
{
    virtual const char * GetCmdID() { return "RemoveThisItem"; }
    BOOL           Create( WordParser* words );
    void           Execute( CScriptVM* vm );
    void        Release(){ delete this; }

    char            m_ItemName[100];
    int             m_ItemNumber;
};


class CScriptCmd_IsThisItemEquipped: public CScriptCommand
{
    virtual const char * GetCmdID() { return "IsThisItemEquipped"; }
    BOOL        Create( WordParser* words );
    void        Execute( CScriptVM* vm );
    void        Release(){ delete this; }
    //
    char            m_ItemName[100];
};

class CScriptCmd_IsThisSkillActived: public CScriptCommand
{
    virtual const char * GetCmdID() { return "IsThisSkillActived"; }
    BOOL        Create( WordParser* words );
    void        Execute( CScriptVM* vm );
    void        Release(){ delete this; }
    //
    //unsigned short    ustSkillItemID;
    //unsigned short    ustSkillLevel;
    CScriptCmd__SetVar::Param m_SkillId;
    CScriptCmd__SetVar::Param m_SkillLevel;
};


class CScriptCmd_GetWeekKillNum: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetWeekKillNum"; }
    BOOL        Create( WordParser* words );
    void        Execute( CScriptVM* vm );
    void        Release(){ delete this; }
};
class CScriptCmd_GetAllKillNum: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetAllKillNum"; }
    BOOL        Create( WordParser* words );
    void        Execute( CScriptVM* vm );
    void        Release(){ delete this; }
};
class CScriptCmd_GetSeriesKillNum: public CScriptCommand
{
    virtual const char * GetCmdID() { return "GetSeriesKillNum"; }
    BOOL        Create( WordParser* words );
    void        Execute( CScriptVM* vm );
    void        Release(){ delete this; }
};

class CScriptCmd_ProcTimeStep: public CScriptCommand
{
    virtual const char * GetCmdID() { return "ProcTimeStep"; }
    BOOL        Create( WordParser* words );
    void        Execute( CScriptVM* vm );
    void        Release(){ delete this; }
    //
    //unsigned short    ustSkillItemID;
    //unsigned short    ustSkillLevel;
    CScriptCmd__SetVar::Param m_StringID;
    CScriptCmd__SetVar::Param m_TimeStep;
};


//class CScriptCmd_StateChangeBringOn: public CScriptCommand
//{
//    virtual const char* GetCmdID(){ return "MonsterAIScript_StateChangeBringOn"; }
//    BOOL        Create( WordParser* words );
//    void        Execute( CScriptVM* vm );
//    void        Release(){ delete this;    }
//    
//
//
//};

//class CScriptCmd_NormalAttack: public CScriptCommand
//{
//    virtual const char* GetCmdID(){ return "MonsterAIScript_NormalAttack"; }
//    BOOL        Create( WordParser* words );
//    void        Execute( CScriptVM* vm );
//    void        Release(){ delete this;    }
//};
class CScriptCmd_HaveThisItem_Byid: public CScriptCommand
{
    virtual const char * GetCmdID() { return "HaveThisItem_Byid"; }
    BOOL           Create( WordParser* words );
    void           Execute( CScriptVM* vm );
    void        Release(){ delete this; }

    //unsigned short    m_ItemId;
    CScriptCmd__SetVar::Param m_ItemId; // 物品Id，变量
    int             m_ItemNum;
};

class CScriptCmd_RemoveThisItem_Byid: public CScriptCommand
{
    virtual const char * GetCmdID() { return "RemoveThisItem_Byid"; }
    BOOL           Create( WordParser* words );
    void           Execute( CScriptVM* vm );
    void        Release(){ delete this; }

    //unsigned short    m_ItemId;
    //int                m_ItemNumber;
    CScriptCmd__SetVar::Param m_ItemId;
    CScriptCmd__SetVar::Param m_ItemNumber;
};

class CScriptCmd_IsThisItemEquipped_Byid: public CScriptCommand
{
    virtual const char * GetCmdID() { return "IsThisItemEquipped_Byid"; }
    BOOL        Create( WordParser* words );
    void        Execute( CScriptVM* vm );
    void        Release(){ delete this; }
    //
    unsigned short    m_ItemId;
};


class CScriptCmd_ChangeTimeHandleStates:public CScriptCommand
{
public:
    CScriptCmd_ChangeTimeHandleStates(){}
    virtual const char * GetCmdID() { return "ChangeTimeHandleStates"; }
    BOOL        Create( WordParser* words );
    void        Execute( CScriptVM* vm );
    void        Release(){ delete this; }
    //
    unsigned int Index;
	int			 StatesValue;
};

class CScriptCmd_ResetTimeHandleStates:public CScriptCommand
{
public:
    CScriptCmd_ResetTimeHandleStates(){}
    virtual const char * GetCmdID() { return "ResetTimeHandleStates"; }
    BOOL        Create( WordParser* words );
    void        Execute( CScriptVM* vm );
    void        Release(){ delete this; }
    //
    unsigned int Index;
};


class CScriptCmd_ClearTimeHandle:public CScriptCommand
{
public:
    CScriptCmd_ClearTimeHandle(){}
    virtual const char * GetCmdID() { return "ClearTimeHandle"; }
    BOOL        Create( WordParser* words );
    void        Execute( CScriptVM* vm );
    void        Release(){ delete this; }
    //
    unsigned int Index;
};

class CScriptCmd_SetWorldBattleCountry:public CScriptCommand
{
public:
    CScriptCmd_SetWorldBattleCountry(){}
    virtual const char * GetCmdID() { return "SetWorldBattleCountry"; }
    BOOL        Create( WordParser* words );
    void        Execute( CScriptVM* vm );
    void        Release(){ delete this; }

    int CountryID;
};

class CScriptCmd_ChangeGamePlayerDuration:public CScriptCommand
{
public:
    CScriptCmd_ChangeGamePlayerDuration(){}
    virtual const char * GetCmdID() { return "ChangeGamePlayerDuration"; }
    BOOL        Create( WordParser* words );
    void        Execute( CScriptVM* vm );
    void        Release(){ delete this; }

    int			Count;//修改数量 整数为加 负数为减
};

class CScriptCmd_GetGamePlayerDuration:public CScriptCommand
{
public:
    CScriptCmd_GetGamePlayerDuration(){}
    virtual const char * GetCmdID() { return "GetGamePlayerDuration"; }
    BOOL        Create( WordParser* words );
    void        Execute( CScriptVM* vm );
    void        Release(){ delete this; }
};

class CScriptCmd_AddFriendPoint:public CScriptCommand
{
public:
	CScriptCmd_AddFriendPoint(){}
	virtual const char * GetCmdID() { return "AddFriendPoint"; }
	BOOL        Create( WordParser* words );
	void        Execute( CScriptVM* vm );
	void        Release(){ delete this; }

	int distance;
	int FriendlyPoint;
};

class CScriptCmd_AddEquipRandAttrItem : public CScriptCommand
{
public:
	CScriptCmd_AddEquipRandAttrItem(){}
	virtual const char * GetCmdID() { return "AddEquipRandAttrItem"; }
	BOOL        Create( WordParser* words );
	void        Execute( CScriptVM* vm );
	void        Release(){ delete this; }

	unsigned short ustItemid;
	bool bIsBound;
	int nRandId1;
	int nRandId2;
	int nRandId3;
	int nRandId4;
	int nRandId5;
	int nRandId6;
	int nRandId7;

	int nSysType;
	int nTypeID;
};

class CScriptCmd_ChangePetMode : public CScriptCommand
{
public:
	CScriptCmd_ChangePetMode(){}
	virtual const char * GetCmdID() { return "ChangePetMode"; }
	BOOL        Create( WordParser* words );
	void        Execute( CScriptVM* vm );
	void        Release(){ delete this; }
	//脚本修改副将身上的模型
	int			ModeID;
	int			Sec;//-1为无限时间
};
class CScriptCmd_UseItem : public CScriptCommand
{
public:
	CScriptCmd_UseItem(){}
	virtual const char * GetCmdID() { return "UseItem"; }
	BOOL        Create( WordParser* words );
	void        Execute( CScriptVM* vm );
	void        Release(){ delete this; }

	unsigned short ustItemid;
};


class CScriptCmd_GetPlayerStates : public CScriptCommand
{
public:
	CScriptCmd_GetPlayerStates(){}
	virtual const char * GetCmdID() { return "GetPlayerStates"; }
	BOOL        Create( WordParser* words );
	void        Execute( CScriptVM* vm );
	void        Release(){ delete this; }
};

class CScriptCmd_AddCard : public CScriptCommand
{
public:
	CScriptCmd_AddCard() {}
	virtual const char* GetCmdID() { return "AddCard"; }
	BOOL        Create( WordParser* words );
	void        Execute( CScriptVM* vm );
	void        Release(){ delete this; }

	short stCardID;
	short stLevel;
};

class CScriptCmd_TriggerSevenDays : public CScriptCommand
{
public:
	CScriptCmd_TriggerSevenDays(){}
	virtual const char * GetCmdID() { return "TriggerSevenDays"; }
	BOOL        Create( WordParser* words );
	void        Execute( CScriptVM* vm );
	void        Release(){ delete this; }
};

class CScriptCmd_IsInFight : public CScriptCommand
{
public:
	CScriptCmd_IsInFight(){}
	virtual const char * GetCmdID() { return "IsInFight"; }
	BOOL        Create( WordParser* words );
	void        Execute( CScriptVM* vm );
	void        Release(){ delete this; }
};

class CScriptCmd_IsMountFull : public CScriptCommand
{
public:
	CScriptCmd_IsMountFull(){}
	virtual const char * GetCmdID() { return "IsMountFull"; }
	BOOL        Create( WordParser* words );
	void        Execute( CScriptVM* vm );
	void        Release(){ delete this; }
};

class CScriptCmd_SetScriptStates : public CScriptCommand
{
public:
	CScriptCmd_SetScriptStates(){}
	virtual const char * GetCmdID() { return "SetScriptStates"; }
	BOOL        Create( WordParser* words );
	void        Execute( CScriptVM* vm );
	void        Release(){ delete this; }

	unsigned short States;
};

class CScriptCmd_CanFlyToCouple  : public CScriptCommand
{
public:
	CScriptCmd_CanFlyToCouple(){}
	virtual const char * GetCmdID() { return "CanFlyToCouple"; }
	BOOL        Create( WordParser* words );
	void        Execute( CScriptVM* vm );
	void        Release(){ delete this; }

	unsigned int Relation;
};

class CScriptCmd_DropQuestEntrust  : public CScriptCommand
{
public:
	CScriptCmd_DropQuestEntrust(){}
	virtual const char * GetCmdID() { return "DropQuestEntrust"; }
	BOOL        Create( WordParser* words );
	void        Execute( CScriptVM* vm );
	void        Release(){ delete this; }
};
class CScriptCmd_DoneQuestEntrust  : public CScriptCommand
{
public:
	CScriptCmd_DoneQuestEntrust(){}
	virtual const char * GetCmdID() { return "DoneQuestEntrust"; }
	BOOL        Create( WordParser* words );
	void        Execute( CScriptVM* vm );
	void        Release(){ delete this; }
};

class CScriptCmd_GetTodayHuntingCount : public CScriptCommand
{
public:
	CScriptCmd_GetTodayHuntingCount(){}
	virtual const char * GetCmdID() { return "GetTodayHuntingCount"; }
	BOOL        Create( WordParser* words );
	void        Execute( CScriptVM* vm );
	void        Release(){ delete this; }
};

class CScriptCmd_OperateHuntingCount : public CScriptCommand
{
public:
	CScriptCmd_OperateHuntingCount() {}
	virtual const char* GetCmdID() { return "OperateHuntingCount"; }
	BOOL        Create( WordParser* words );
	void        Execute( CScriptVM* vm );
	void        Release(){ delete this; }

	int nType;
	int nValue;
};

class CScriptCmd_DoneHuntingQuest : public CScriptCommand
{
public:
	CScriptCmd_DoneHuntingQuest(){}
	virtual const char * GetCmdID() { return "DoneHuntingQuest"; }
	BOOL        Create( WordParser* words );
	void        Execute( CScriptVM* vm );
	void        Release(){ delete this; }

	int nId;
};


class CScriptCmd_CanelQuestEntrust  : public CScriptCommand
{
public:
	CScriptCmd_CanelQuestEntrust(){}
	virtual const char * GetCmdID() { return "CanelQuestEntrust"; }
	BOOL        Create( WordParser* words );
	void        Execute( CScriptVM* vm );
	void        Release(){ delete this; }

	int QuestID;
};

class CScriptCmd_FlytoPosition  : public CScriptCommand
{
public:
	CScriptCmd_FlytoPosition(){}
	virtual const char * GetCmdID() { return "FlytoPosition"; }
	BOOL        Create( WordParser* words );
	void        Execute( CScriptVM* vm );
	void        Release(){ delete this; }

	int			Type;
};

class CScriptCmd_AddHonourByTeam  : public CScriptCommand
{
public:
	CScriptCmd_AddHonourByTeam(){}
	virtual const char * GetCmdID() { return "AddHonourByTeam"; }
	BOOL        Create( WordParser* words );
	void        Execute( CScriptVM* vm );
	void        Release(){ delete this; }

	int			Num;
};


class CScriptCmd_GetStrongCountry  : public CScriptCommand
{
public:
	CScriptCmd_GetStrongCountry(){}
	virtual const char * GetCmdID() { return "GetStrongCountry"; }
	BOOL        Create( WordParser* words );
	void        Execute( CScriptVM* vm );
	void        Release(){ delete this; }
};
class CScriptCmd_GetWeakCountry  : public CScriptCommand
{
public:
	CScriptCmd_GetWeakCountry(){}
	virtual const char * GetCmdID() { return "GetWeakCountry"; }
	BOOL        Create( WordParser* words );
	void        Execute( CScriptVM* vm );
	void        Release(){ delete this; }
};

class CScriptCmd_ChangePlayerPoint  : public CScriptCommand
{
public:
	CScriptCmd_ChangePlayerPoint(){}
	virtual const char * GetCmdID() { return "ChangePlayerPoint"; }
	BOOL        Create( WordParser* words );
	void        Execute( CScriptVM* vm );
	void        Release(){ delete this; }

	int			Op;
	int			Value;
	int			States;
};

class CScriptCmd_SetMonsterArray  : public CScriptCommand
{
public:
	CScriptCmd_SetMonsterArray(){}
	virtual const char * GetCmdID() { return "SetMonsterArray"; }
	BOOL        Create( WordParser* words );
	void        Execute( CScriptVM* vm );
	void        Release(){ delete this; }

	int			Index;
	int			Value;
};

class CScriptCmd_GetMonsterArray  : public CScriptCommand
{
public:
	CScriptCmd_GetMonsterArray(){}
	virtual const char * GetCmdID() { return "GetMonsterArray"; }
	BOOL        Create( WordParser* words );
	void        Execute( CScriptVM* vm );
	void        Release(){ delete this; }

	int			Index;
};
//////////////////////////////////////////////////////////////////////////////////
#include "CountryScriptDefine.h"
#include "RelationScriptDefine.h"
#include "GuildScriptDefine.h"
#include "CampBattleScriptDefine.h"
#include "FamilyScriptDefine.h"
#include "GameBattleScriptDefine.h"
//////////////////////////////////////////////////////////////////////

#endif // __SCRIPT_FUNCTION_DEFINE_H__
