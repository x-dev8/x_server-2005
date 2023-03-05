#pragma once

#include "afxwin.h"
#include "afxcmn.h"

#include "XListCtrl/XListCtrl.h"
#include "GlobalDef.h"
#include "QuestData.h"
#include "QuestManager.h"
#include "MyTreeCtrl.h"
#include "direct.h"
#include "folder_dialog.h"
#include "application_config.h"
#include "MapConfig.h"
#include "ItemDetail.h"
#include "NpcManager.h"
#include "NpcInfo.h"
#include "PositionInfo.h"
#include "TitleConfig.h"

#include "XmlStringLanguage.h"
#include "DropQuestItem.h"

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define SaveShow_Timer_Id 0x1

#define Red_Ground_Color		RGB(255, 0, 0)
#define Default_Grund_Color		RGB(255, 255, 255)
#define Green_Ground_Color		RGB(0, 255, 0)
#define Blue_Ground_Color		RGB(0, 255, 255)

#define Monster_Left_Color		RGB(0,255,45)
#define Monster_Right_Color		RGB(0, 255, 159)

#define Item_Left_Color			RGB(0,255,255)
#define Item_Right_Color		RGB(64, 255, 255)

#define theQuestInfo QuestInfo::Instance()
#define theQuestManager QuestManager::Instance()

#define SafeDelete(p) { if(p != NULL) { delete p; p = NULL; } }


#define Max_Level 200
#define StringId_Count 50


#define Item_File_Path		"..\\Data\\Config\\Data.config"
#define Map_File_Path		"..\\Data\\Config\\Map.config"
#define Npc_File_Path		"..\\Data\\Config\\Npc.config"
#define Repute_File_Path	"..\\Data\\Config\\Title.config"
#define String_File_Path	"..\\Data\\Quest\\Client"
#define Position_File_Path	"..\\Data\\Config\\Position.config"
#define InitPath			"..\\Data\\Quest\\"
#define COMMONQUEST         "..\\Data\\Quest\\Common.quest"

#define SUB_STRING1 ";"
#define SUB_STRING2 ","
#define SUB_STRING3 "-"
#define Client_Path "\\Client"
#define Server_Path "\\Server"
#define Quest_File_Ext ".quest"
#define Drop_Item_File "QuestMonsterDropItem.config"
#define Common_Quest_File "Common.quest"

#define QuestIndex_File  "QuestIndex.dat"

#define Default_Select "请选择"
#define Quest_Root "任务列表"

enum Name_Type
{
	Enum_Map = 0,		//地图
	Enum_Profession,	//职业
	Enum_Quality,		//任务品质
	Enum_Requirement,	//任务要求
	Enum_Reward,		//任务奖励
	Enum_Title,
	Enum_Buff,
	Enum_Refer,			//提交任务类型
	Enum_Sex,
	Enum_Position,
	Enum_Item,
	Enum_Monster,
	Enum_QuestInfoType,
    Enum_IsRandStar,    // 是否随机星级
    Enum_IsBound,       // 是否绑定

	Enum_End,			
};

enum FindType
{
	Enum_QuestId = 0,  //
	Enum_QuestNameId,
	Enum_QuestName,
	Enum_QuestLevel,
	Enum_QuestContentId,
	Enum_QuestContent,
	Enum_QuestTargetId,
	Enum_QuestTarget,
	Enum_QuestMapId,
	Enum_QuestMapName,
	Enum_QuestNpcId,
	Enum_QuestNpcName,
	Enum_QuestCanAssist, 
	Enum_QuestCanShare,
	Enum_QuestRepeate,
	Enum_QuestCancel,
	Enum_QuestPreRequementItemId,
	Enum_QuestPreRequementItemName,
	Enum_QuestPostRequementItemId,
	Enum_QuestPostRequementItemName,
	Enum_QuestRewardItemId,
	Enum_QuestRewardItemName,

	Enum_QuestMax,
};

static char* s_pFindType[] = 
{
	"任务ID",
	"任务名称ID",
	"任务名称",
	"任务品质",
	"任务描述ID",
	"任务描述",
	"任务目标ID",
	"任务目标",
	"地图ID",
	"地图名称",
	"NPC ID",
	"NPC名称",
	"协助任务",
	"共享任务",
	"重复任务",
	"删除任务",
	"前置需要物品ID",
	"前置需要物品名称",
	"完成需要物品ID",
	"完成需要物品名称",
	"奖励物品ID",
	"奖励物品名称",
};


static char* s_pszQuality[] = 
{
	"普通的任务",
	"良好的任务",
	"优秀的任务",
	"卓越的任务",
	"传说的任务",
	"史诗的任务",
};

// 对应枚举 ERequirementTypes 
static char* s_pszRequement[] = 
{
	"需要金钱",
	"需要物品",
	"记数变量",
	"职业限制",
	"等级限制",
	"需要声望",
	"性别限制",
	"需要活力",
	"杀死怪物",
	"前置任务",
	"时间限制",
	"社会关系",
	"需要经验",
	"需要技能经验",
    "行为任务",
    "需要记数限制",
    "弱国任务",
    "需要状态",
    "无需状态",
    "心法等级",
    "宠物数量",
    "宠物等级",
    "宠物ID",
    "宠物类型",
    "宠物出战",
};

static char* s_pszReward[] = 
{
	"奖励金钱",
	"奖励经验",
	"奖励技能经验",
	"奖励物品",
	"奖励声望",
    "奖励功勋",
	"奖励称号",
	"奖励状态",
	"奖励记数变量",
    "奖励帮贡",
    "奖励特殊物品",
    "奖励交子",
    "奖励荣誉",
	"奖励国库金钱",
	"奖金脚本给予经验"
};

static char* s_pszSex[] = 
{
	"男",
	"女",	
};

static char* s_pszIsRandStar[] = 
{
    "否",
    "是",
};

static char* s_pszIsBound[] =
{
    "否",
    "是",
};

static char* s_pszProfession[] = 
{
    "战士",
    "乐师",	
    "法师",
    "刺客",
    "猎人",
    "火枪",
};

static char* s_pszQuestInfoType[] = 
{
	"【主线】",
	"【成长】",
	"【活动】",	
	"【副本】",	
	"【官府】",	
    "【循环】",
    "【巡城】",
    "【军需】",	
    "【藏宝】",	
    "【称号】",	
    "【装备】",	
    "【趣味】",	
    "【帮会】",	
    "【酒馆】",
    "【皇榜】",
    "【征伐】",
    "【国运】",
    "【出国】",
    "【天行】",
    "【探宝】",
};

//设置信息
struct SetInfo
{
	SetInfo()
	{
		strName.clear();
		nValue = -1;
	}

	string strName;
	int nValue;

	friend bool operator < (const SetInfo &xLeft, const SetInfo &xRight)
	{
		return (xLeft.nValue < xRight.nValue);
	}
};

typedef vector<SetInfo>::iterator setiter;
typedef vector<SQuestRequirement>::iterator reqiter;
typedef vector<SQuestReward>::iterator rewarditer;
typedef QuestInfo::itrSQuests questiter;



struct FindInfo
{
	FindInfo() { nFindMatch = 0; }

	int nFindMatch;   //精确查找
};


//怪物和 物品关联
struct MonsterAndDrop
{
	int nQuestId;
	int nVarId;

	int nMonsterId;   //怪物ID
	int nMonsterCount;	//数量

	int nItemId;		//物品ID
	int nItemCount;
	
	int nItemRate;		//掉率


	//////////////////////////////程序显示用
	MonsterAndDrop()
	{
		Clear();
	}

	void Clear()
	{
		nVarId = -1;
		nQuestId = -1;

		nMonsterId = -1;
		nMonsterCount = 0;

		nItemId = -1;
		nItemCount = 0;
		nItemRate = 0;
	}
};

