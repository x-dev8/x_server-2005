#ifndef AN_CONFIG_COLOR_H_
#define AN_CONFIG_COLOR_H_

#include <Windows.h>
#include <map>

enum ColorConfigure
{
	CC_CONFIG_INVALID = -1,

	CC_CHAT_NORMAL	= 0,	//��ͨ������ɫ
	CC_CHAT_PERSONAL,		//˽����ɫ
	CC_CHAT_GUILD,			//����������ɫ
	CC_CHAT_TEAM,			//����������ɫ
	CC_CHAT_SYSTEM,			//ϵͳ������ɫ
	CC_CHAT_BULL,			//ȫ������������ɫ
	CC_CHAT_LEAGUE,			//ͬ��������ɫ	
	CC_CHAT_HIGHSHOUT,		//ȫ������(�������)��ɫ
	CC_CHAT_FAMILY,			//��������

	CC_TASK_MORE6,		//����ȼ��������6��ɫ
	CC_TASK_MORE3,			//����ȼ��������3��ɫ
	CC_TASK_LESS3ANDMORE3 = 10,	//�������� -3~~3��ɫ
	CC_TASK_LESS3,			//����ȼ�С�����3	��ɫ
	CC_TASK_LESS6,			//����ȼ�С�����6��ɫ
    CC_TASK_NAME,           //����׷��������������ɫ
    CC_TASK_DONE,           //����׷��������ɵ�����Ŀ����ɫ
    CC_TASK_NONE,           //����׷����δ��ɵ�����Ŀ����ɫ
	//�������player(����player��item��npc��monster�ȵ�)
	CC_ENTITY_PLAYER,			//��� �����Լ���ɫ
	CC_ENTITY_NPC,				//npc��ɫ
	CC_ENTITY_ITEMLESS2,			//���䵽���ϵ���Ʒ Ʒ��С��2����ɫ
	CC_ENTITY_MONSTER_INITIATIVE,	//����������ɫ
	CC_ENTITY_MONSTER_PASSIVITY = 20,	//����������ɫ
	CC_ENTITY_MONSTER_PROFESSION,	//�ɼ���Ʒ(���������ڹ���)��ɫ

    CC_GUILD_MASTER,                //����᳤��ɫ
    CC_GUILD_VICEMASTER,            //���ḱ�᳤��ɫ
    CC_GUILD_MEMBER,                //�����Ա��ɫ
    CC_GUILD_OFFLINE,               //�������߻�Ա��ɫ

    CC_FRIEND_ONLINE,               //����������ɫ
    CC_FRIEND_OFFLINE,               //����������ɫ

    CC_CHARACTER_DEL,               //ѡ�˽��汻ɾ���Ľ�ɫ��ɫ

	CC_MINIMAP_TIP,					//С��ͼtip������ɫ
	CC_CHAT_HYBER_DOWNLINE = 30,	//����������ֻ��»�����ɫ

	CC_NPCLIST_MAPNAME = 31,		//���ͼ������ʾ������ɫ
	
	CC_NPCLIST_NPCTYPE_1,			//npc�б���ɫ��ʾ ���� ��ͨ 
	CC_NPCLIST_NPCTYPE_2,			//npc�б���ɫ��ʾ ���� ҩƷ�����������Ρ����ߡ�����һ�����
	CC_NPCLIST_NPCTYPE_3,			//npc�б���ɫ��ʾ ���� ���������̡���������
	CC_NPCLIST_NPCTYPE_4,			//npc�б���ɫ��ʾ ���� ���͵�
	CC_NPCLIST_NPCTYPE_5,			//npc�б���ɫ��ʾ ���� �ֿ⡢��������
	CC_NPCLIST_NPCTYPE_6,			//npc�б���ɫ��ʾ ���� �ϳɡ�����
	CC_NPCLIST_NPCTYPE_7 = 38,		//npc�б���ɫ��ʾ ����ٸ�����

	CC_ITME_SHOW		=	 39,	//��Ʒ����
	CC_ITME_TYPE		=	 40,	//��Ʒ����
	CC_ITME_PRONEED		=	 41,	//ְҵ����
	CC_ITEM_LVLNEED		=	 42,	//��Ҫ����
	CC_ITEM_WEAR		=	 43,	//�;�
	
    CC_NAME_Pet      =    44,    //�ٻ�����ɫ
    CC_NAME_POLICE      =    45,                 //���������ɫ
    CC_NAME_KILL_1      =    46,                 //���������ɫ �ȼ�1
    CC_NAME_KILL_2      =    47,                 //���������ɫ �ȼ�2
    CC_NAME_KILL_3      =    48,                 //���������ɫ �ȼ�3
    CC_NAME_KILL_4      =    49,                 //���������ɫ �ȼ�4
    CC_NAME_KILL_5      =    50,                 //���������ɫ �ȼ�5
    CC_NAME_ATTACKER    =    51,                 //���������ɫ
    CC_NAME_GUILD       =    52,                 //��ҹ���������ɫ

	CC_CUSTOM_SHORTCUTKEY	= 53,	//����Զ����ݼ�list������ɫ
	CC_CUSTOM_KEYFCOUT		= 54,	//����Զ����ݼ�list���µȴ�������ɫ
	CC_ITEM_EQUIPTYPE		= 55,	//EquipType

	CC_TASK_INFO			= 56,	//������Ϣ������ɫ
	CC_TASK_STATE			= 57,	//������ʾ������ɫ
	CC_NPCDIALOG_INFO		= 58,	//npc�Ի�����������ɫ selectBox.cpp.m_pID_TEXT_Info
	CC_NPCSELECKBOX_INFO	= 59,	//npcѡ��Ի�������ɫ NpcChatDialogBox.cpp.m_pID_TEXT_Info
	CC_MESSGEBOX_TEXT		= 60,	//messagebox ������ɫ

	CC_LISTSELECTON			= 61,	//listѡ��itemʱ�����ɫ


	CC_CORPS_Robber			= 62,	//ְҵ
	CC_CORPS_Warrior		= 63,	//ְҵ
	CC_CORPS_Archer			= 64,	//ְҵ
	CC_CORPS_Taoist			= 65,	//ְҵ
	CC_CORPS_Wizard			= 66,	//ְҵ

	CC_TEXT_ExpAllot		= 67,	//������׽���Text��ɫ
	CC_SHOP_Desc			= 68,		//�̵�ע��
	CC_SHOP_Storage			= 69,		//�̵�ֿ�

	CC_SHOP_Price			= 70,		//�̵���ͨ�۸�
	CC_SHOP_MemberPrice		= 71,		//�̵�VIP�۸�
	CC_SHOP_Price2			= 72,		//�̵���ͨ�۸�(��Ϸ�ҹ���)
	CC_SHOP_MemberPrice2	= 73,		//�̵�VIP�۸�(��Ϸ�ҹ���)

	CC_SHOP_ItemName		= 74,		//�̵���Ʒ��
	
	CC_SHOP_Agio			= 75,		//�̵�Agio
	CC_LoginUI_TextInfo		= 76,		//loginUI test������ɫ
	CC_SkillTip_target		= 77,		//���ö���
	CC_ItemTip_suitNoneAll	= 78,		//skill_ tip ��װû����ȫ
	CC_ItemTip_suitALL		= 79,		//skill_ tip ��װ��ȫ 
	
	CC_CreateUI_StrNote     = 80,
	CC_CreateUI_Property     = 81,
	CC_CreateUI_ProName    = 82,


	CC_ServerInfoColor_0	=	83,
	CC_ServerInfoColor_1	=	84,
	CC_ServerInfoColor_2	=	85,
	CC_ServerInfoColor_3	=	86,
	CC_ServerInfoColor_4	=	87,
	CC_ServerInfoColor_5	=	88,
	CC_ServerInfoColor_6	=	89,
	CC_ServerInfoColor_7	=	90,
	CC_ServerInfoColor_8	=	91,
	CC_ServerInfoColor_9	=	92,
	CC_ServerInfoColor_10	=	93,

	CC_Client_Eventtime_description	= 94,	//event_time_description
	CC_Client_Eventtime_hortation	= 95,	//event_time_hortation
	CC_Client_Eventtime_timeinfo	= 96,	//event_time_timeinfo
	CC_Client_Eventtime_more		= 97,	//event_time_more

	CC_CompoundInfo_Icon_Enable		= 98,	//�ͻ��˺ϳɱ� icon ���õ�������ɫ
	CC_CompoundInfo_Icon_Disable	= 99,	//�ͻ��˺ϳɱ� icon �����õ�������ɫ

	CC_Intensify_Text_Color_1 = 100,   //ǿ��������ʾ��ɫ
	CC_Intensify_Text_Color_2 = 101,
	CC_Intensify_Text_Color_3 = 102,
	CC_Intensify_Text_Color_4 = 103,

    CC_GUILD_CITYMASTER = 104,

	CC_PlayerNormal = 105,	// �������������ɫ
	CC_PlayerEnemy = 106,	// �ж����������ɫ
	CC_PlayerLeague = 107,	// ͬ�����������ɫ
	CC_PlayerTile = 108,	// ��ҳƺ�������ɫ
	CC_Guild = 109,			// ����������ɫ
    CC_NPCTile = 110,		// NPC�ƺ�������ɫ
	CC_NPC = 111,			// NPC������ɫ
	

	CC_MonsterNormal = 112,	// ������������ɫ
	CC_MonsterLevelRange5,	// �����ֵȼ� - ��ҵȼ� = -5 ~ 5
	CC_MonsterLevelLow5,	// �����ֵȼ� - ��ҵȼ� = < -5
	CC_MonsterLevelUp5,		// �����ֵȼ� - ��ҵȼ� = > 5

	CC_ItemLevel1,          // �ȼ�Ϊ1�ĵ���������ɫ
	CC_ItemLevel2,          // �ȼ�Ϊ2�ĵ���������ɫ
	CC_ItemLevel3,          // �ȼ�Ϊ3�ĵ���������ɫ
	CC_ItemLevel4,          // �ȼ�Ϊ4�ĵ���������ɫ
	CC_ItemLevel5,          // �ȼ�Ϊ5�ĵ���������ɫ
	CC_ItemLevel6,          // �ȼ�Ϊ6�ĵ���������ɫ
	CC_PathFindLinker,          // Ѱ·���ӵ���ɫ

	CC_ZoneNameTip,          // zone������ɫ
	CC_TileNameTip,          // ����tile������ɫ

	CC_TaskRank0,			// Ʒ��Ϊ0������
	CC_TaskRank1,            // Ʒ��Ϊ1��������Զ��ʾ����ɫ
	CC_TaskRank2,            // Ʒ��Ϊ2��������Զ��ʾ����ɫ
	CC_TaskRank3,            // Ʒ��Ϊ3��������Զ��ʾ����ɫ
	CC_TaskRank4,            // Ʒ��Ϊ4��������Զ��ʾ����ɫ
	CC_HighLightNpcName,          // ����npc����ɫ

	CC_MessageSelfName,          // ����Ϣ���Լ����Ƶ���ɫ
	CC_MessageOtherName,          // ����Ϣ�жԷ����Ƶ���ɫ
	CC_MessageSelfWord,          // ����Ϣ���Լ��������ݵ���ɫ
	CC_MessageOtherWord,          // ����Ϣ�жԷ��������ݵ���ɫ

	CC_PlayerTip_NameP1 = 150,		//Tips������������ֵİ�������ɫ
	CC_PlayerTip_NameP2,		//Tips������������ֵ����ŵ���ɫ
	CC_PlayerTip_NameP3,		//Tips������������ֵĺ��յ���ɫ
	CC_PlayerTip_NameP4,		//Tips������������ֵĽ�������ɫ
	CC_PlayerTip_NameP5,		//Tips������������ֵķ������ɫ
	CC_PlayerTip_Gang = 158,			//Tips��������ҹ���������ɫ
	CC_PlayerTip_Level,			//Tips��������ҵȼ�����ɫ
	CC_PlayerTip_Profession,			//Tips���������ְҵ����ɫ
	CC_PlayerTip_PkMode,			//Tips���������PKģʽ����ɫ

	CC_MonsterTip_Name = 163,			//Tips���������������ɫ
	CC_MonsterTip_Title,			//Tips���������ƺŵ���ɫ
	CC_MonsterTip_Level,			//Tips���������ȼ�����ɫ
	CC_MonsterTip_Strong,			//Tips���������ǿ�ȵ���ɫ
	CC_MonsterTip_SkillOK = 168,			//Tips�����������ܵȼ��������ɫ
	CC_MonsterTip_SkillFail,			//Tips�����������ܵȼ����������ɫ

	CC_NpcTip_Name = 170,			//Tips������NPC���ֵ���ɫ
	CC_NpcTip_Title,			//Tips������NPC�ƺŵ���ɫ
	CC_NpcTip_Level,			//Tips������NPC�ȼ�����ɫ

	CC_ElevenBlueName = 189,		//11������
	CC_TenBlueName ,		//10������
	CC_NineBlueName,
	CC_EightBlueName,
	CC_SevenBlueName,
	CC_SixBlueName,
	CC_FiveBlueName,
	CC_FourBlueName,
	CC_ThreeBlueName,
	CC_TwoBlueName,
	CC_OneBlueName,
	CC_WhiteName,				//����
	CC_OrangeName,				//��ɫ����
	CC_OneRedName,
	CC_TwoRedName,
	CC_ThreeRedName,
	CC_FourRedName,
	CC_FiveRedName,
	CC_SixRedName,
	CC_SevenRedName,
	CC_EightRedName,
	CC_NineRedName,
	CC_TenRedName,
 	CC_ElevenRedName,
	CC_Exp,
	CC_Exploit,
	CC_Reputation,
	CC_SkillLevelUp,
	CC_Pick,
	CC_SystemPromp,
	CC_Center_MapInfo,
	CC_Center_ImmediateInfo,
	CC_Center_WarningErrorInfo,
	CC_Center_OtherInfo,
	CC_CHAT_PLAYERNAME, // ���촰�������������ɫ
	CC_CHAT_VIP_PLAYERNAME,	// ���촰����VIP���������ɫ
	CC_PRIVATE_SHOP_MONEY,	// ��̯���׼�¼���ý�Ǯ
    CC_MAILTIP,          //�ʼ�Tip
    CC_CampBattleSame,    //ͬ��Ӫ
    CC_CampBattleNoSame,  //��ͬ��Ӫ
    CC_CampBattleSameInList,  //��ͬ��Ӫ�г�Ա�б�����ʾ
	CC_CHAT_ZHENYING,	// ��ӪƵ��
	CC_CHAT_COUNTRY,	// ����Ƶ��
	CC_CHAT_XIAOLABA,	// С����Ƶ��
	CC_Gem_Attribute,	// ��ʯ����������ɫ
	CC_ContryTitle,		// ��ְ�ƺţ�����ͷ��
	CC_PetTitle,		// ����ƺţ�xx�ĳ��

    CC_BESTEQUIP_GETMODE,	// װ����ȡ��ʽ
    CC_BESTEQUIP_INFO,		// װ����ȡ��ʽ˵��
    CC_BESTEQUIP_OTHERINFO,	// װ����ȡ��ʽ����˵��
    CC_BESTEQUIP_TIP,		// װ����ȡ��ʾ

    CC_Player_OtherCountry          = 240,      // ͷ��������ɫ
    CC_Pet_OtherCountry             = 241,
    CC_PetTitle_OtherCountry        = 242,
    CC_NPC_OtherCountry             = 243,
    CC_NPC_NoCountry                = 244,

    CC_ActivityDay_LevelReach       = 245,      // ����ָ���ȼ��ﵽ��ɫ
    CC_ActivityDay_LevelNotReach    = 246,      // δ�ﵽ

    // ��Ʒ�����ܡ�״̬ Tip ��ɫ����        added by zhuomeng.hu		[12/3/2010]
    /***************************************************************/
    CC_ItemTip_Name_Quality0        = 250,      // Ʒ��
    CC_ItemTip_Name_Quality1,
    CC_ItemTip_Name_Quality2,
    CC_ItemTip_Name_Quality3,
    CC_ItemTip_Name_Quality4,
    CC_ItemTip_Name_Quality5,
	CC_ItemTip_Name_Quality6,
	CC_ItemTip_Name_Quality7,

    CC_ItemTip_SkillName            = 260,      // ��Ʒ��
    CC_ItemTip_ItemType             = 261,      // ��Ʒ����

    CC_ItemTip_ItemBind             = 262,      // ��Ʒ�Ѱ�

    CC_ItemTip_Endure_Nonzero       = 263,      // �;÷�0
    CC_ItemTip_Endure_Zero          = 264,      // �;�Ϊ0

    CC_ItemTip_Lock                 = 265,      // ����
    CC_ItemTip_Unlock               = 266,      // ����

    CC_ItemTip_Require_Reach        = 267,      // ��װ����ﵽ
    CC_ItemTip_Require_NotReach     = 268,      // ��װ����δ�ﵽ

    CC_ItemTip_BaseAttr             = 269,      // װ����������
    CC_ItemTip_RandAttr             = 270,      // װ�������������
    CC_ItemTip_PurpleAttr           = 271,      // װ���̽�����
    CC_ItemTip_GemAttr              = 272,      // װ����ʯ��Ƕ����

    CC_ItemTip_SuitPart_Have        = 273,      // ����װ����
    CC_ItemTip_SuitPart_NotHave     = 274,      // ����װ����
    CC_ItemTip_SuitAttr_Have        = 275,      // ����װ����
    CC_ItemTip_SuitAttr_NotHave     = 276,      // ����װ����

    CC_ItemTip_EquipDes_Default     = 277,      // װ������Ĭ����ɫ

    CC_ItemTip_Identify             = 278,      // װ�������ļ����������Ѿ�û��

    CC_ItemTip_SellPrice            = 279,      // ��Ʒ�ۼ�
    CC_ItemTip_FixPrice             = 280,      // ����۸�

    CC_ItemTip_Item_Introduction    = 281,      // ��Ʒ�����ܽ���

    CC_ItemTip_RestoreTime          = 282,      // ����Ʒʹ�ô���

    CC_ItemTip_Gem                  = 283,      // ��ʯ������

    CC_ItemTip_Skill_NextLevel      = 284,      // ������������һ����
    CC_ItemTip_Skill_MaxLevel       = 285,      // �����������Ѵﵽ���ȼ���
    CC_ItemTip_Skill_NotLearn       = 286,      // ����������δѧϰ��
    CC_ItemTip_Skill_Level          = 287,      // �����������ȼ���
    CC_ItemTip_Skill_LearnNotReach  = 288,      // ѧϰ��������δ�ﵽ

    CC_ItemTip_EventItem_Des        = 289,      // �¼�(����?)��������
    
    CC_ItemTip_Item_LeftTime        = 290,      // ��Ʒʣ��ʱ��

    CC_ItemTip_Other                = 291,      // ���������ɫ

    CC_ItemTip_NowEquip             = 292,      // ��ǰװ��

	CC_Achievement_OK				= 293,      // �ɾ����
	CC_Achievement_Gray             = 294,      // �ɾ�δ���

	CC_MapName                      = 320,      // ��ͼ����
    /***************************************************************/
	CC_PetColor_Taupe           = 321,//����ɫ
	CC_PetColor_Red				   = 322,//��ɫ
	CC_PetColor_Blue			   = 323,//��ɫ
	CC_PetColor_Green			   = 324,//��ɫ
	CC_PetColor_White			   = 325,//��ɫ
	CC_NearPlayerNoTeam            = 326, //��������޶���
	CC_NearPlayerTeam              = 327, //��������ж��� 
	CC_ZhuJiang_Name			   = 328, //������������ɫ
	CC_Activity_Default			   = 329, //�Ĭ����ɫ
	CC_Activity_Start			   = 330, //�������
	CC_Activity_Close			   = 331, //��ر�
	CC_Activity_Finish			   = 332, //����
	CC_Activity_Ready			   = 333, //�Ԥ��
	CC_Activity_NoStart			   = 334, //�δ��ʼ
	CC_ZhuJiang_Attr			   = 335, //��������
    CC_Chat_ChatGuanYuan           = 336, //��ԱƵ��������ɫ
	CC_TeamPlayer				   = 337, //��Ӷ���������ɫ
	CC_CONFIG_MAX
};
class CColor_Configure
{
public:
	CColor_Configure();
	virtual ~CColor_Configure();

public:
	void	load();
	DWORD	ARGBtoDWORD(int a, int r, int g, int b);

	DWORD	getColor(ColorConfigure type);

	DWORD	GetPkNameColor( int nPkType );
private:
	DWORD	mAllColor[CC_CONFIG_MAX];
};

extern CColor_Configure Color_Config;

#endif

