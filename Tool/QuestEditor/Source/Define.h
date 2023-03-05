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

#define Default_Select "��ѡ��"
#define Quest_Root "�����б�"

enum Name_Type
{
	Enum_Map = 0,		//��ͼ
	Enum_Profession,	//ְҵ
	Enum_Quality,		//����Ʒ��
	Enum_Requirement,	//����Ҫ��
	Enum_Reward,		//������
	Enum_Title,
	Enum_Buff,
	Enum_Refer,			//�ύ��������
	Enum_Sex,
	Enum_Position,
	Enum_Item,
	Enum_Monster,
	Enum_QuestInfoType,
    Enum_IsRandStar,    // �Ƿ�����Ǽ�
    Enum_IsBound,       // �Ƿ��

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
	"����ID",
	"��������ID",
	"��������",
	"����Ʒ��",
	"��������ID",
	"��������",
	"����Ŀ��ID",
	"����Ŀ��",
	"��ͼID",
	"��ͼ����",
	"NPC ID",
	"NPC����",
	"Э������",
	"��������",
	"�ظ�����",
	"ɾ������",
	"ǰ����Ҫ��ƷID",
	"ǰ����Ҫ��Ʒ����",
	"�����Ҫ��ƷID",
	"�����Ҫ��Ʒ����",
	"������ƷID",
	"������Ʒ����",
};


static char* s_pszQuality[] = 
{
	"��ͨ������",
	"���õ�����",
	"���������",
	"׿Խ������",
	"��˵������",
	"ʷʫ������",
};

// ��Ӧö�� ERequirementTypes 
static char* s_pszRequement[] = 
{
	"��Ҫ��Ǯ",
	"��Ҫ��Ʒ",
	"��������",
	"ְҵ����",
	"�ȼ�����",
	"��Ҫ����",
	"�Ա�����",
	"��Ҫ����",
	"ɱ������",
	"ǰ������",
	"ʱ������",
	"����ϵ",
	"��Ҫ����",
	"��Ҫ���ܾ���",
    "��Ϊ����",
    "��Ҫ��������",
    "��������",
    "��Ҫ״̬",
    "����״̬",
    "�ķ��ȼ�",
    "��������",
    "����ȼ�",
    "����ID",
    "��������",
    "�����ս",
};

static char* s_pszReward[] = 
{
	"������Ǯ",
	"��������",
	"�������ܾ���",
	"������Ʒ",
	"��������",
    "������ѫ",
	"�����ƺ�",
	"����״̬",
	"������������",
    "�����ﹱ",
    "����������Ʒ",
    "��������",
    "��������",
	"���������Ǯ",
	"����ű����辭��"
};

static char* s_pszSex[] = 
{
	"��",
	"Ů",	
};

static char* s_pszIsRandStar[] = 
{
    "��",
    "��",
};

static char* s_pszIsBound[] =
{
    "��",
    "��",
};

static char* s_pszProfession[] = 
{
    "սʿ",
    "��ʦ",	
    "��ʦ",
    "�̿�",
    "����",
    "��ǹ",
};

static char* s_pszQuestInfoType[] = 
{
	"�����ߡ�",
	"���ɳ���",
	"�����",	
	"��������",	
	"���ٸ���",	
    "��ѭ����",
    "��Ѳ�ǡ�",
    "�����衿",	
    "���ر���",	
    "���ƺš�",	
    "��װ����",	
    "��Ȥζ��",	
    "����᡿",	
    "���ƹݡ�",
    "���ʰ�",
    "��������",
    "�����ˡ�",
    "��������",
    "�����С�",
    "��̽����",
};

//������Ϣ
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

	int nFindMatch;   //��ȷ����
};


//����� ��Ʒ����
struct MonsterAndDrop
{
	int nQuestId;
	int nVarId;

	int nMonsterId;   //����ID
	int nMonsterCount;	//����

	int nItemId;		//��ƷID
	int nItemCount;
	
	int nItemRate;		//����


	//////////////////////////////������ʾ��
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

