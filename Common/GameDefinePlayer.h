/********************************************************************
    Filename:    GameDefinePlayer.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_GAMEDEFINEPLAYER_H__
#define __COMMON_GAMEDEFINEPLAYER_H__

#pragma once

#pragma pack ( push, 1 )

enum ENumeric
{
    NUMERIC_ZERO,
    NUMERIC_ONE,
    NUMERIC_TWO,
    NUMERIC_THREE,
    NUMERIC_FOUR,
    NUMERIC_FIVE,
    NUMERIC_SIX,
    NUMERIC_SEVEN,
    NUMERIC_EIGHT,
    NUMERIC_NINE ,
    NUMERIC_TEN ,
};

static const char* s_szChineseNumericString[] = { "��", "һ", "��", "��", "��", "��", "��", "��", "��", "��", "ʮ","ʮһ","ʮ��","ʮ��","ʮ��","ʮ��","ʮ��","ʮ��","ʮ��" };

enum ESendMessageState
{
    SEND_READY  ,   // δ����
    SENDING     ,   // ������
    SNED_OVER   ,   // �������
};

//��Ʒ�����Դ
enum EItemGetSource
{
    EIGS_UnKnow         ,    // δ֪
    EIGS_OnlineReward   ,    // ���߽���
    EIGS_Quest          ,    // �������
    EIGS_Achieve        ,    // �ɾͽ���
    EIGS_DropItem       ,    // ��ֵ���
    EIGS_TreasureBox    ,    // ������
    EIGS_JiFengShop     ,    // �����̵�
    EIGS_NpcShop        ,    // NPC�̵�
    EIGS_Bargaining     ,    // ����
    EIGS_Stall          ,    // ��̯
    EIGS_Script         ,    // �ű����
    EIGS_Upgrade        ,    // װ������
    EIGS_Compose        ,    // �ϳ�
    EIGS_GemTakeDown    ,    // ��ʯ��ж
    EIGS_FromPlat       ,    // ͨ��ƽ̨���
	EIGS_GemInlayFail   ,    // ��Ƕʧ�ܽ���
	EIGS_UnknowIdentify ,    // װ��δ֪����
	EIGS_Mail			,	 // �ʼ�
	EIGS_Decompose		,	 // �ֽ�
};

//���¼���������Դ
enum EWhereForeRecalcProperty
{
    EWRP_Init           ,    // ��ʼ��
    EWRP_Equip          ,    // װ��
    EWRP_Level          ,    // ����
    EWRP_Skill          ,    // ����
    EWRP_Status         ,    // ״̬
    EWRP_Title          ,    // �ƺ�
    EWRP_Relive         ,    // ����
    EWRP_Potential      ,    // ����Ǳ����
};

//////////////////////////////////////////////////////////////////////////
//  �ɾ�ϵͳ���

//�ɾʹ���
enum EAchieveMainType
{
    EAM_EverydayAchieve     = 1,    // �������
    EAM_AdolesceAchieve     = 2,    // �ɳ�֮·
    EAM_TougheningAchieve   = 3,    // ��������
    EAM_ArmamentAchieve     = 4,    // �������
    EAM_BattleAchieve       = 5,    // ԡѪɳ��
};

enum EAchieveValueType
{
    EAT_OnlineTime          = 1     ,   //����ʱ��
    EAT_LoginDay            = 2     ,   //��½����
    EAT_BillAmount          = 3     ,   //�ۼƳ�ֵ      [δ����]
    EAT_Level               = 4     ,   //���˵ȼ�
    EAT_Reputation          = 5     ,   //��������
    EAT_Honour              = 6     ,   //��������
    EAT_Exploit             = 7     ,   //���˹�ѫ
    EAT_Prestige            = 8     ,   //��������

    EAT_FirstTeam           = 9     ,   //��һ�����    
    EAT_FirstFriend         = 10    ,   //��һ�μӺ���  
    EAT_FirstMaster         = 11    ,   //��һ�ΰ�ʦ    
    EAT_FirstStudent        = 12    ,   //��һ����ͽ    
    EAT_JoinGuild           = 13    ,   //��һ�μ������
    EAT_CreateGuild         = 14    ,   //��һ�ν�������

    EAT_EquipStar           = 15    ,   //װ����9��
    EAT_EquipStamp          = 16    ,   //װ������
    EAT_EquipGem            = 17    ,   //��ʯ��Ƕ
    EAT_EquipOpen           = 18    ,   //װ���̽�
    EAT_EquipAmulet         = 19    ,   //�����

    EAT_BuyWeapon           = 20    ,   //��һ������
    EAT_BuyRestore          = 21    ,   //��һ��ҩƷ
    EAT_BuyArmour           = 22    ,   //��һ������
    EAT_BuyOrnament         = 23    ,   //��һ����Ʒ
    EAT_BuyHonour           = 24    ,   //��һ��ѫ��    [δ����]

    EAT_EquipExchange       = 25    ,   //�һ�װ��      [δ����]
    EAT_GuildCloak          = 26    ,   //����������  [δ����]
    EAT_Money               = 27    ,   //��Ǯ
    EAT_JiaoZi              = 28    ,   //����
    EAT_RecipeSkill         = 29    ,   //ѧϰ�����

    EAT_Rank1               = 30    ,   //���а�
    EAT_Rank2               = 31    ,   //���а�
    EAT_Rank3               = 32    ,   //���а�
    EAT_Rank4               = 33    ,   //���а�
    EAT_Rank5               = 34    ,   //���а�
    EAT_Rank6               = 35    ,   //���а�
    EAT_Rank7               = 36    ,   //���а�
    EAT_Rank8               = 37    ,   //���а�

    EAT_GoodMount           = 38    ,   //ץһƥ��Ʒ��
    EAT_ExcellentMount      = 39    ,   //ץһƥ��Ʒ��
    EAT_VariationMount      = 40    ,   //ץһƥ������
    EAT_MountLevel          = 41    ,   //��������

    //////////////////////////////////////////////////////////////////////////
    //  �ű�����

	EAT_FinishTask			= 42	,	//���X����������   
	EAT_EctypeCount_HJJ		= 43	,	//���X�λƽ������
    //43	�ۼ����X�ΰ�ᰵս	
    //44	�ۼ����X�ΰ�Ụ��	
    //45	�ۼ����X�ΰ������	
    //46	�ۼ����X�ΰ���ħ	
    //47	�ۼ����X�˰��ͼ��	
    //48	�ۼ��Ͻ�X�ΰ��ļ����
    //49	�ۼ��Ͻ�X�ΰﹱ����
    //50	�μ�һ�ΰ��ս
    //51	��Ӯһ�ΰ��ս
    //52	�ۼƲμ�X�ΰ��ս	
    //53	�ۼƳɹ����ٵй��ڳ�	
    //54	�ۼƳɹ����ٵй�����	
    //55	�ۼƻ�ɱ�й����	
    //56	�ۼ����X�ι�������	
    //57	�ۼ����X�γ�������	

    EAT_AddTitle            = 58    ,   //��óƺ�	  

    //////////////////////////////////////////////////////////////////////////
    //  �ű�����

    //59	�μӹ�������ս
    //60	�μ�����֮������ս
    //61	�μ���ȸ֮������ս
    //62	�ۼ����X�������ĺ�����
    //63	�ۼ����X���Ĵ�鳼����
    //64	�ۼ����X�����ִ������
    //65	�ۼ����X�ο���ӱ�����
    //66	�ۼ����X�θ�����������
    //67	�ۼ����X���콵��������
    //68	�ۼ����X����������
    //69	�ۼ����X����˰����
    //70	����������ͨ��
    //71	��ʱ��ɱ����BOSS
    //72	�ۼ���ɸ���ͨ�ش���
    //73	�ۼ�X�λ�ɱͬһ������BOSS
    //74	ͬʱ��ɼ�������
    //75	��ɽ��ݷ�������
    //76	��������ɽ����
    //77	��ɰ׻��븱��
    //78	�������������
    //79	��ɷ��ɽ����
    //80	������䵺����
    //81	����ػʵع�����
    //82	�����ԩ��������
    //83	���ҹ�����Ǹ���
    //84	��ɽ��ݷ���������������С�ڼ���
    //85	��������ɽ������������С�ڼ���
    //86	��ɰ׻��븱����������С�ڼ���
    //87	���������������������С�ڼ���
    //88	��ɷ��ɽ������������С�ڼ���
    //89	������䵺������������С�ڼ���
    //90	����ػʵع�������������С�ڼ���
    //91	�����ԩ����������������С�ڼ���
    //92	���ҹ�����Ǹ�����������С�ڼ���
	EAT_FinishActivity				= 93		//��ɻ����
};

enum ECharAchieveState
{
    ECS_Unfinished  ,   // δ���
    ECS_Finished    ,   // �����
    ECS_GetReward   ,   // ���콱
    ECS_MaxCount    ,
};


enum EAchieveCompare
{
    EAC_Greater     ,   // ����
    EAC_Equal       ,   // ����
    EAC_Less        ,   // ����
};

//////////////////////////////////////////////////////////////////////////

#define CHAR_AUTO_LEVELUP           10  //����Զ������ȼ�
#define CHAR_OFFLINE_HOOK_LEVEL     40  //������߹һ��ȼ�
#define CHAR_RELIVEMAP_LEVEL        10  //���������ȼ�

////ս��ŭ���ظ� ��ͨ����ŭ��+5 ������ŭ��+2
//#define CHAR_WARRIOR_ATTACK_RESTORE_MP     5
//#define CHAR_WARRIOR_BEATTACK_RESTORE_MP   2

//�������
#define MOUNT_HP_RESTORE_COST    7   //  �ָ���������ֵÿ10�㻨��7ͭ
#define MOUNT_HP_CONSUME         4   //  ��������ֵÿСʱ�½�4��
#define MOUNT_LOWEST_ACTIVE_HP   1   //  �����ս����ֵ

#define MOUNT_HP_DROP_KILLED_BY_PALYER   10  //���������ɱ���½�10��
#define MOUNT_HP_DROP_KILLED_BY_MONSTER  20  //������ɱ���½�20��

#define MOUNT_BREED_MASTER_LEVEL    60  // ��˷�ֳ�ȼ�������Ϊ60��
#define MOUNT_BREED_MONEY  1000         // ���ﷱֳ�����Ǯ

//���XP�������
#define DEF_CHAR_XP_LIMIT       1000
#define DEF_XP_NOFIGHT_RESTORE  2       // �������Ϸ�еȴ��ظ���ÿ10��ظ�2��
#define DEF_XP_FIGHT_RESTORE    1       // �������Ϸ�д�֣�ÿ��һ�¹���ظ�1��

//װ�����
const int CharmAbsorbProbabilitys[SCharItem::EConstDefine_BaseRandMaxCount] = { 80, 40, 10, 0, 0, 0, 0 } ;   //���Ĳ���������

enum PKManagerEnum
{
    PKValueOp_Set    = 0,          
    PKValueOp_Add    = 1,
    PKValueOp_Reduce = 2,
};

enum EPKManagerConstDefine
{
    PKHonour_SelfCountry      = 12,
    PKHonour_ForeignCountry   = 30,
	PKHoniur15				  = 15,
	PKHoniur20		          = 20,
	PKHoniur5			      = 5,
	PKHoniur6				  = 6,

};

#define OFFLINE_HOOK_MAX_TIME       7 * 24 * 60 * 60 * 1000         //���߹һ�ʱ�������ۻ�7��

#define CHAR_SYS_DOUBLE_EXP_MAX_TIME     300  * OneMinuteMicroSecond     //ϵͳ˫������ʱ�����300����
#define CHAR_ITEM_DOUBLE_EXP_MAX_TIME    9999 * OneMinuteMicroSecond     //����˫������ʱ�����9999����

#pragma pack ( pop )

#endif // __COMMON_GAMEDEFINEPLAYER_H__
