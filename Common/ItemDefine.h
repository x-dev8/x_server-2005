/********************************************************************
Filename:     ItemDetail.h
MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_ITEMDEFINE_H__
#define __COMMON_ITEMDEFINE_H__

#pragma once

#include "GlobalDef.h"
#include "GameDefinePet.h"
#include "GameDefineChar.h"
#include "Array.h"

//��ʵ�� class CItemDetail ����ͷ�ļ� ��������̫�ʴ�
namespace ItemDefine
{
	enum EItemType
	{
		ITEMTYPE_RESTORE = 0    , // �ָ�ҩƷ
		ITEMTYPE_WEAPON         , // ����
		ITEMTYPE_ARMOUR         , // ����
		ITEMTYPE_SKILL          , // ����
		ITEMTYPE_STATUS         , // ״̬
		ITEMTYPE_ACTION         , // ��������
		ITEMTYPE_MATERIAL       , // ԭ��
		ITEMTYPE_GEM            , // ��ʯ
		ITEMTYPE_CREATEITEMRULE , // �ϳ��䷽
		ITEMTYPE_TASK           , // ����
		ITEMTYPE_OTHER          , // ����[ ������ ]
		ITEMTYPE_REEL           , // ����
		ITEMTYPE_TREASUREBOX    , // ����( ����Կ�� ) 
		ITEMTYPE_CHECKUP        , // ���������
		ITEMTYPE_REALAWARD      , // ������Ʒ��( ��������, ������ )
		ITEMTYPE_GUILD          , // ���ѹ��������İ�����
		ITEMTYPE_SPECIAL        , // ĳЩ�ض�ר�õ���Ʒ
		ITEMTYPE_TALISMAN       , // ����		
		ITEMTYPE_PETEQUIP		, // ����װ��
		ITEMTYPE_MAX            ,
	};

	enum enumProfessionType
	{
		ProfessionType_Normal            = 0
		,ProfessionType_Element
		,ProfessionType_Max
	};

	enum enumConst
	{
		const_iSkillUnderstandPCondition    = 5
		,const_iSkillUnderstandSCondition   = 5
		,const_iSkillUsingPCondition        = 5
		,const_iMaxSkillSpecialAttrNum      = 3
		,const_iEquipTypeNum                = 15
	};

	//enum enumSkillUseTarget
	//{
	//    usetarget_pos
	//    ,usetarget_friend
	//    ,usetarget_enemy
	//    ,usetarget_
	//};
	//��Χ�ͳ���ħ�����ԶԵ��淢��
	//���ܲ���Ч���Ķ��󣨱���һ�����ܶ����ѷ����������˺���ʱ��ȴ�ǶԵ��ˣ�

	enum MountOperaType
	{
		OperaType_Normal = 0,           // ��������
		OperaType_Control   ,           // ����ģʽ
	};

	enum enumMoveType
	{
		movetype_twofooted = 0          // ˫���ƶ�
		,movetype_fourfooted            // �����ƶ�
		,movetype_fly                   // �����ƶ�
		,movetype_reptile               // �����ƶ�
		,movetype_drive                 // ��ʻ�ƶ�
		,movetype_twowheel              // �����ƶ�
		,movetype_fourwheel             // �����ƶ�
	};

	enum enumEffCenter
	{
		center_no = 0         //û�г�����Ч��
		,center_metotarget    //���Լ�������
		,center_me            //���Լ���ǰλ��Ϊ����
		,center_target        //��Ŀ��λ��Ϊ����
	}; 

	enum enumMountAction
	{
		MountDrive = 0,
		MountWalk,
		MountWalkBackWards,
		MountRun,
		MountJump,
		MountFallToTheGroundRun,
		MountDrop,
		MountGlide,
		MountShuffleLeft,
		MountShuffleRight,
		MountNeigh,
		MountBackAttack,
		//MountAttackIdle,
		//MountAttackRun,
		//MountScabbard,
		//MountDraw,
		MountMaxActionNum
	};

	enum enumItemParam
	{   
		//��������Item��ID������������
		StartID_GameAction     = 100,
		EndID_GameAction       = 999,

		StartID_Skill          = 1000,
		EndID_Skill            = 2399,

		StartID_Status         = 2400,
		EndID_Status           = 3699,

		StartID_Material       = 3700,
		EndID_Material         = 5699,

		StartID_Restore        = 5700,
		EndID_Restore          = 6699,

		StartID_Reel           = 6700,
		EndID_Reel             = 7699,

		StartID_Weapon         = 7700,
		EndID_Weapon           = 10699,

		StartID_Armour         = 10700,
		EndID_Armour           = 12699,

		StartID_Task           = 12900,
		EndID_Task             = 19099,

		StartID_Restore1       = 19100,
		EndID_Restore1         = 19999,

		StartID_WeaponRand     = 20001,
		EndID_WeaponRand       = 20500,

		StartID_ArmourRand     = 20501,
		EndID_ArmourRand       = 20999,

		StartID_CreateItemRule = 21000,
		EndID_CreateItemRule   = 22000,

		StartID_Armour1        = 22001,
		EndID_Armour1          = 27000,

		StartID_Weapon1        = 27001,
		EndID_Weapon1          = 32000,

		StartID_Gem            = 32001,
		EndID_Gem              = 34000, 

		StartID_Special        = 34001,
		EndID_Special          = 36000, 

		StartID_MonsterCard    = 36001, // �������ͼ����
		EndID_MonsterCard      = 38500, 

		StartID_Talisman       = 38500,
		EndID_Talisman         = 40000,

		MaxNum_Weapon          = EndID_Weapon1 - StartID_Weapon1,
		MaxLevel_Weapon        = 11,

		MaxNum_Skill           = EndID_Skill - StartID_Skill + 1,
		MaxLevel_Skill         = 21,

		MaxNum_Status          = EndID_Status - StartID_Status + 1,
		MaxLevel_Status        = 21,
	};

	//enum enumSkillType
	//{
	//    skill_phycic,        //������ϵ�ļ���
	//    skill_magic            //ħ��
	//};

	//enum enumContinuousSkill
	//{
	//    cskill_attack            = 0    //��ι�������ļ���
	//    cskill_helper                //һ�μӳɵĸ�������
	//};

	enum enumWeaponAttackRate
	{
		attack_slow = 0 // ��������
		,attack_normal  // ��ͨ����
		,attack_fast    // ���ٹ���
	};

	//װ������
	enum enumEquipType
	{
		equip_Helmet             = 1<<0,  // ͷ��
		equip_Armour             = 1<<1,  // ����
		equip_Glove              = 1<<2,  // ����
		equip_Shoe               = 1<<3,  // Ь��
		equip_Weapon             = 1<<4,  // ������
		equip_WeaponMinor        = 1<<5,  // ������
		equip_Badge              = 1<<6,  // ����
		equip_Ring               = 1<<7,  // ��ָ
		equip_Bangle             = 1<<8,  // ����
		//        equip_Manteau            = 1<<9,  // ����
		equip_Shoulder           = 1<<9,  // ���
		equip_Necklace           = 1<<10, // ����
		equip_Sash               = 1<<11, // ����
		equip_LeaderCard         = 1<<12, // ���ſ�
		equip_Amulet             = 1<<13, // �����
		equip_AecorativeGoods    = 1<<14, // װ�ε���Ʒ
		equip_AecorativeClothing = 1<<15, // װ�ε��·�
		equip_Trousers			 = 1<<16, // ����

		equip_TypeMaxCount       = 17,
	};    

	//�������̶� ���Ʒ  ��Ʒ����ͨƷ������Ʒ����Ʒ
	enum enumItemClass
	{
		ItemClass_Worst = 0
		,ItemClass_Bad
		,ItemClass_Normal
		,ItemClass_Good
		,ItemClass_Best
		,ItemClass_Max
	};

	//��������
	//    ��ͨ����:һ��Ч��������Ҫ�������:����˺���˲���ƶ��������Ѫ
	//    ��������
	//    ˲���ƶ�    ˲���ƶ���Ŀ��ص�
	//    �����ӳ�:һ��Ч�����г���ʱ�䣬��:�ӹ�                
	//    �������� ���ܳ���ʱ��
	//    �ӹ���        �ӹ���6        5000
	//    �����Է�Χ����:�Է�Χ��Ŀ��ÿ��Ŀ��ÿ n �����һ������        
	//    �������� ���ܳ���ʱ�� ���ü��
	//    ����֮��    ��Ѫ30        5000        1000            
	//    ��ѩ����    ������20    5000        1000
	//    �����Է�Χ��������:�Է�Χ��Ŀ��ÿ��Ŀ��ÿ n �����һ������,���ó��� n1 ��            
	//    �������� ���ܳ���ʱ�� �ӳɳ���ʱ�� ���ü��
	//    �����⻷    �ӹ���6        5000        800            1000

	//��������
	enum ESkillType
	{
		skilltype_action    = 0, // �ڶ������Ž��������ģ�����
		skilltype_magic_hit = 1, // �ڶ������Ž�������㣬�ͷų�һ���������
		skilltype_magic_npc = 2, // �ڶ������Ž������ͷų�һ������npc
		skilltype_passive   = 3, // ��������
	};

	//�ͷ�����
	enum ECastType
	{
		casttype_singletarget             = 0, // ��һĿ��                   *
		casttype_singletargetcircleAOE    = 1, // ��һĿ��Բ�η�Χ           
		casttype_AOEPointCircleArea       = 2, // Ŀ��ص��Բ�η�Χ
		casttype_AOEcircleself            = 3, // ���Լ�Ϊ���ĵ�Բ�η�Χ���� *
		casttype_AOEquartercirlcefrontage = 4, // ����90�ȵ����ͷ�Χ����     *
		casttype_AOEhalfcirclefrontage    = 5, // ����180�ȵİ�Բ��Χ����
		casttype_AOEquartercirlcebackage  = 6, // ����90�ȵ����ͷ�Χ����
		casttype_AOEhalfcirclebackage     = 7, // ����180�ȵİ�Բ��Χ����
		casttype_AOETargetcirclearea      = 8, // ��ѡ��Ŀ��Ϊ���ĵ�Բ�η�Χ����
		casttype_MAX,
	};

	//���ܵġ���������
	//��ʽ
	//��ɱ��
	//ħ��
	enum enumSkillPowerType
	{
		//��ʽ
		skillpower_zhaoshi = 0
		//��ɱ��
		,skillpower_bishaji                        
		//ħ��
		,skillpower_magic
	};

	//״̬�Ľ��㹫ʽ����
	enum EStatusBalanceType
	{
		balance_status_type_none        , // Ĭ�Ͻ��㹫ʽ
		balance_status_type_restore     , // �ظ����㹫ʽ
		balance_status_type_timeexp     , // ʱ�侭��
		balance_status_type_mount       , // ���ﱻ������
	};

	// ��Ʒʹ��Ŀ��
	enum EUserTargetType
	{
		eTargetMe = 0   // ֻ���Լ�
		,eTargetEnemy   // ֻ�Եз�
		,eTargetSelf    // ���ѷ���
		,eTargetAll     // ��������
		,eTargetMount   // ������
		,eTargetFriend  // ������ʹ��
		,eTargetPet     // �Գ���
	};    

	enum ESkillCastCondition
	{
		SCC_Null,              // ������
		SCC_MustInFightState,  // ������ս��״̬
		SCC_MustOutFightState, // ���벻��ս��״̬
	};

	enum ECollectSkillID        // ����ܣ�������������
	{
		eCSI_CaiYao     = 2300, // ��ҩ
		eCSI_CaiKuang   = 2301, // �ɿ�
		eCSI_BuChong    = 2307, // ����
		eCSI_DuanZao    = 2309, // ����	
		eCSI_ZhuJia     = 2310, // ����
		eCSI_GongYi     = 2311, // ����
		eCSI_LianYao    = 2312, // ��ҩ
		eCSI_XunMa      = 2313, // ѱ��
		eCSI_ZhuBao     = 2314, // �鱦
		eCSI_CatchPet   = 2315, // ׽����

		// ����ͨ�ü���
		eCSI_GoBack     = 2302, // �س̼���
		eCSI_BuZhuo     = 2304, // ��׽
		eCSI_Treasure   = 2306, // �ɼ�������Ʒ
		eCSI_GoBack2    = 2390, // �����س�
	};

	enum ECannotJumpStatusID    // �޷���Ծ��״̬ID
	{
		eCJS_StatusID1  = 3350, // �ڳ�1
		eCJS_StatusID2  = 3351, // �ڳ�2   
	};

	enum EFlagModelID           // ����ģ��ID
	{
		eFMI_Start  = 9400,
		eFMI_End    = 9409
	};

	enum ESpecialSkillID
	{
		eSSI_Relive         = 1108      ,
		eSSI_MountMonster   = 2305      ,   // ������
		eSSI_PetActive      = 2316      ,   // �����ս����
	};

	enum ESpecialStatusID
	{
		ESSI_JiangHuInvitation = 3173   ,   // �������
		ESSI_DoubleExpStatus   = 3142   ,   // ˫������
	};

	enum ESpecialRestoreID
	{
		ESRI_ReliveItem =   6465        ,   // �������
	};

	enum ECostType
	{
		CT_Money = 0        ,   // Ǯ
		CT_Reputation       ,   // ����
		CT_Exploit          ,   // ��ѫ
		CT_Item             ,   // ��Ʒ
		CT_GuildOffer       ,   // �ﹱ
		CT_GuildMoney       ,   // ����ʽ�  ( ���������� )
		CT_GuildBuild       ,   // ��Ὠ���( ���������� )
		CT_CostType1        ,   // Ԥ���ֶ�
		CT_CostType2        ,   // Ԥ���ֶ�
		CT_CostType3        ,   // Ԥ���ֶ� 
		CT_CostType4        ,   // Ԥ���ֶ� 
		CT_JiaoZi           ,   // ����
		CT_Honour           ,   // ����
		CT_CountryScore     ,   // ��ս����
		CT_MasterValue = 20,    // ʦ������
	};

	enum EItemQuality
	{
		IQ_While,		// ��װ
		IQ_Green,		// ��װ
		IQ_DeepGreen,	// ����װ
		IQ_Blue,		// ��װ
		IQ_Purple,		// ��װ
		IQ_Orange,		// ��ɫ
		IQ_Gold,		// ��ɫ
		IQ_Red,			// ��ɫ
	};

	struct SItemCommon
	{
		SItemCommon()
		{
			memset(this, 0, sizeof(*this) );
			bCanSingingInterrupt = false;
			nDropMaxCount = -1;
		}

		bool  IsExclusive();                // �Ƿ���� 
		uint16 GetStackNum();               // ��ÿɵ�������
		const char* GetItemName();
		const char* GetItemDesc();
		const char* GetIconInItemBag();
		const char* GetIconTile();
		const char* GetIconSoundFile();
		const char* GetSingEffect();
		const char* GetAssoilEffect();
		const char* GetHurtEffect();

		bool IsCanEquip() const { return ucItemType == ITEMTYPE_ARMOUR || ucItemType == ITEMTYPE_WEAPON; }

		unsigned short ustItemID;
		unsigned int   dwItemNameAddr; // �������ֵ�ַ
		unsigned int   dwItemDescAddr; // ����������ַ
		int            nUseTime;       // ʹ��ʱ�� ��СʱΪ��λ��
		int            nBill;          // ��ֵ
		unsigned int   dwCost;         // ��Ʒ�۸�
		unsigned char  costType;       // �۸�����
		unsigned short costItemID;     // �۸���ƷID(��Ҫ��Ʒʱ,Ҫ���ֵ���ж�)
		unsigned short ustLevel;       // ��ƷƷ��(Skill��StatusΪ�ȼ�)
		unsigned int   dwSpecialCost;  // ������Ʒ�ĳ��ۼ۸�

		unsigned char  ucItemType;
		unsigned int   dwIconInItemBagAddr;
		unsigned int   dwIconSoundAddr;
		unsigned int   dwIconTileAddr;

		unsigned short ustModelIDOverGround;        
		char           cItemClass;           // �������̶�
		bool           bShowEquipEffect;     // �Ƿ���ʾװ����Ч ȱʡfalse
		unsigned short ustItemW,ustItemH;    // ռ�����
		bool           bIsCanDrop;           // �ɷ���
		bool           bIsCanMove;           // �ɷ��ƶ�
		bool           bIsCanDestory;        // �ɷ�����
		bool           bIsCanSellShop;       // �ɷ�����
		bool           bIsCanPushInStorage;  // �Ƿ���Է���ֿ� 1:���Է���;0:�����Է��롣
		bool           bIsCanLocked;         // ��Ʒ�ɷ����  1:���Լ���;0:�����Լ���
		unsigned int   dwSingEffect;         // ������Ч
		unsigned int   dwAssoilEffect;       // �ͷ���Ч
		unsigned int   dwHurtEffect;         // ������Ч
		unsigned short ustIconId;            // ICONID
		float          fWeight;              // ����
		bool           bIsCanTrade;          // �ɷ���
		unsigned int   dwUseSingTime;        // ʹ����Ʒ����ʱ��
		bool           bCanSingingInterrupt; // �Ƿ������п��Դ�� 0Ϊ������ 1Ϊ����
		unsigned char  byUserTarget;         // ����״̬ ����״̬�ȼ� ״̬���м��� ��Ʒʹ��Ŀ��
		bool           bIsCanBound;          // �ɷ��
		bool           bIsCanSplit;          // �ɷ���
		unsigned int   nDropControlCount;    // ��Ʒ���������ֵ
		bool           bIsClearControlCount; // �ﵽ�����Ժ��Ƿ������ֵ 
		int            nDropMaxCount;        // ��������������  -1=������ 0 = ������
		uint16         nStackNum;            // ���߿ɶѵ�����
		bool		   bIsSinging;			 // �ͻ���ר��
	};

	// ������������Ʒ���⹦��
	enum EMountRestoreItemSpecialFunction
	{
		EMRIF_None,
		EMRIF_RestoreHP,            //1 �ָ��������� (����)
		EMRIF_AddExp,               //2 ���������Ӿ���ֵ (��ѩ��)
		EMRIF_ResetPoint,           //3 ������ϴ�� (��Ԫ��)
		EMRIF_OpenSkill,            //4 ������
		EMRIF_ForgetSkill,          //5 Ц����
		EMRIF_HuanLongShu,          //6 ������
		EMRIF_HuanTongShu,          //7 ��ͯ��
	};

	// ������������Ʒ���⹦��
	enum EPetRestoreItemSpecialFunction
	{
		EPetFunc_None,                 // 
		EPetFunc_RestoreHP,            // 1�ָ�����HP
		EPetFunc_AddLife,              // 2���ӳ�������
		EPetFunc_AddLoyalty,           // 3���ӳ�����ֶ�
		EPetFunc_AddExp,               // 4���������Ӿ���ֵ 
		EPetFunc_AddSavvy,             // 5��������������
		EPetFunc_ResetPoint,           // 6������ϴ��
		EPetFunc_HuanTongShu,          // 7���ﻹͯ
		EPetFunc_OpenSkill,            // 8ѧϰ����
		EPetFunc_ForgetSkill,          // 9��������
	};

	//��ɫ��������Ʒ���⹦��
	enum ECharRestoreItemSpecialFunction
	{
		ECharFunc_ResetPoint = 3		// ϴ���Ե�
	};
	enum EItemRestoreType
	{
		EIRT_None       ,           // ����������Ʒ
		EIRT_RestoreHP  ,           // �ָ�HPҩƷ
		EIRT_RestoreMP  ,           // �ָ�MPҩƷ
		EIRT_Mount      ,           // ��������Ʒ
		EIRT_Epistar    ,           // ��Ԫ����Ʒ by cloud
	};

	enum ERestoreUseStatusType
	{
		EUseStatusType_None,        // ��
		EUseStatusType_NoFight,     // ս�������ʹ��
		EUseStatusType_InFight,     // ս���в���ʹ��
	};

	struct SItemRestore : public SItemCommon
	{
		SItemRestore()
		{   
			memset(this, 0, sizeof(*this) );
		}

		uint8          nRestoreType;      // ����Ʒ����
		uint32         dwAddHP;           // �����ӵ�HP
		uint32         dwAddMP;           // �����ӵ�MP
		uint32         dwAddExp;          // �����ӵľ���
		short          stSubHunger;       // ��������
		unsigned short ustSubStatusID;    // ���״̬
		unsigned short ustAddStatusID;    // ����״̬
		unsigned short ustAddStatusLevel; // ����״̬�ȼ�
		DWORD          dwCoolDown;        // colddown
		short          stCoolDownType;    // type
		bool           bExpendable;       // �Ƿ������(Ҳ�������������)
		bool           bIsReliveItem;     // �Ƿ񸴻���Ʒ
		uint8          nUseFightStatus;   // ս��ʹ��״̬
		short          stUseLevel;        // ʹ�õȼ�
		short          nMountUseLevel;    // ����ʹ�õȼ�
		bool           bHPAuto;           // �Ƿ��Զ��ظ�HP
		bool           bMPAuto;           // �Ƿ��Զ��ظ�MP
		bool           bAutoRelive;       // �Ƿ����ػ���ʹ
		//bool           bExclusive;        // �Ƿ��ռһ�����������򲻿ɵ���
		unsigned char  specialFunction;   // ����Ĺ���
		uint32         dwAddHPOnce;       // ÿ�����ӵ�HP
		uint32         dwAddMPOnce;       // ÿ�����ӵ�MP
		uint16         openSkillNum;      // ����������
		uint16         forgetSkillIndex;  // ��������λ�ü���
		uint8          petSavvy;          // ��������

		Array< bool, EArmType_MaxSize> arrayProfessionReq;         // ����Ʒ��ְҵ����
	};

	//װ��Ʒ�ʵȼ� 0�� 1�� 2�� 3�� 4�� 5��
	enum EEquipQualityLevel
	{
		//EQL_Gray    ,
		EQL_White   ,
		EQL_Green   ,
		EQL_DeepGreen   ,
		EQL_Blue    ,
		EQL_Purple  ,
		EQL_Orange  ,
		EQL_Golden  ,
		EQL_Red  ,
		EQL_Max
	};

	enum EEquipStatusTrigger
	{
		EEquipStatusTrigger_None        ,   
		EEquipStatusTrigger_Attack      ,   // ��������
		EEquipStatusTrigger_BeAttack    ,   // ����������
		EEquipStatusTrigger_Damage      ,   // �ܵ��˺�����
	};

	struct SItemCanEquip : public SItemCommon
	{
		enum EConstDefine
		{
			ECD_DistortionIdCount     = 3,
			ECD_AdditiveRandAttrCount = 7, // ���ӵ��������
			ECD_PurpleRandAttrCount   = 3, // ��ɫ���������
			ECD_HandModelCount    = 2,

			ECD_Repair_Normal     = 0,  // ��ͨ����
			ECD_Repair_Item       = 1,  // ��Ҫ��Ʒ������
			ECD_Repair_Exploit    = 2,  // ���Ĺ�ѫ
			ECD_Repair_Reputation = 3,  // ��������
			ECD_Repair_GuildOffer = 4,  // ���İﹱ
			ECD_SkillSuitCount    = 5,  // ������װ����
			ECD_ElementSuitCount  = 6,  // ������װ����
		};

		uint32 ustEquipType;                                      // װ������
		int8   arrayCanEquip[ EEquipPartType_MaxEquitPart ];      // ��λ�ɷ�װ�� 1:0
		int8   isCommon;                                          // �Ƿ���ͨ��װ��
		uint32 dwReplaceSkinAddr;                                 // ����Ƥ�����ֵ�ַ
		int8   isSpecular;                                        // �Ƿ��������Ч
		int8   isCanDistortion;                                   // �Ƿ���Ա���
		Array< uint16, ECD_DistortionIdCount > arrayDistortionId; // ���ε�ģ�͵�ID
		int8  cEquipSexReq;                                       // װ�����Ա����� ���==-1����û������
		Array< bool, EArmType_MaxSize> arrayEquipArmsReq;         // װ����ְҵ����
		int16 stEquipLevelReq;                                    // װ���ļ�������
		int   nPkValueNeed;                                       // pkֵ����
		int   nTitleNeed;                                         // �ƺ�����
		int16 stRepairPrice;                                      // ����۸�/��
		int   stHPMax;                                            // ����;ö�
		float fStatusRate;                                        // ״̬���м���(����)
		float fMyStatusRate;                                      // ״̬���м���(��)
		int16 stAddStatus;                                        // ����״̬(����)
		int16 stAddStatusLevel;                                   // ״̬�ȼ�(����)
		int8  nAddStatusTrigger;                                  // ����״̬������ʽ(����)
		int16 stMyAddStatus;                                      // ����״̬(��)
		int16 stMyAddStatusLevel ;                                // ״̬�ȼ�(��)
		int8  nMyAddStatusTrigger;                                // ����״̬������ʽ(��)

		//modified by junyi.chen begin
		//        int8 additiveRandCount;                                    // ���������������
		bool bRandWhenCreate;										//�Ƿ�װ������ʱ�����丽���������
		Array<uint16, ECD_AdditiveRandAttrCount> additiveRandCountRates;  // �����Ӧ����������������ĸ���,array[0] ��7���ĸ���,[1]��6����,�Դ�����
		uint8 additiveRandLvLowerLimit;								//����������Եȼ�����
		uint8 additiveRandLvUpperLimit;								//����������Եȼ�����
		//TODO:���Ż��ṹ
		Array<uint8, RT_AddAttrMaxSize> typeFilter;					//����ɸѡ.�����������ʱ,��Ӧ[EquipmentRandom.slk]��[Type]�ֶ�,ֻ����д���������������������
		//Array<uint8, RT_AddAttrMaxSize> typeFilter_hero;			//����ɸѡ.�����������ʱ,��Ӧ[EquipmentRandom.slk]��[Type]�ֶ�,ֻ����д���������������������

		//        Array<bool, ECD_AdditiveRandAttrCount> additiveRandFlags;  // �������������ʾ
		Array<uint16, ECD_AdditiveRandAttrCount> additiveRandFlags;  // �������������ʾ

		//        Array<int16,ECD_AdditiveRandAttrCount> additiveRandValues; // ���������ֵ
		//end
		int8 purpleRandCount;                                     // ��ɫ�����������
		Array<bool, ECD_PurpleRandAttrCount> purpleRandFlags;     // ��ɫ���������ʾ
		Array<int16,ECD_PurpleRandAttrCount> purpleRandValues;    // ��ɫ�����ֵ

		bool   bFashion;                                          // �Ƿ���ʱװ
		uint32 dwSoundAddr;                                       // ��Ч
		float  attackPhysics;                                     // ��������
		float  attackMagic;                                       // ħ��������
		float  attackSpeed;                                       // �����ٶ�
		float  exact     ;                                        // ������
		float  dodge     ;                                        // ������
		float  critical  ;                                        // ������
		float  tenacity  ;                                        // ����  
		//�¼� Ԫ������
		float  breakStrike;										  // �Ƽ��˺�
		float  breakResist;										  // �Ƽ׿���
		float  stabStrike;										  // �ᴩ�˺�
		float  stabResist;										  // �ᴩ����
		float  elementStrike;									  // Ԫ���˺�
		float  elementResist;									  // Ԫ�ؿ���
		float  toxinStrike;										  // �����˺�
		float  toxinResist;										  // ���ؿ���
		float  spiritStrike;									  // �����˺�
		float  spiritResist;									  // ������


		uint16 skillId;                                           // ����Id
		uint16 skillLevel;                                        // ���ܵȼ�
		uint8  uchRepairType;                                     // ��������
		uint32 nRepairValue;                                      // ���������ĵ�ֵ( �������Ʒ��Ϣ, ���ֵ������ƷID )
		int16  sPartCount;                                        // ��װ�������
		int16  sSuitID;                                           // ��װId
		bool   bIsElements;                                       // �Ƿ�������װ
		//������װ���������ID��װ������������װ�Ļ�nHeroID = 0;
		int    nHeroID;											  // ������װ������ID
		//
		uint16 unBindCount;										  //װ�����Ĵ��� -1Ϊ���޽�� 0Ϊ�޷���� ����Ϊ������


		SItemCanEquip()
		{ memset(this, 0, sizeof(*this) ); }

		const int8* GetReplaceSkin();
		const int8* GetSound();
		int8        IsCommon()   { return isCommon;   }
		int8        IsSpecular() { return isSpecular; }
		int8        GetCanEquipIndex() // ��ÿ���װ���Ĳ�λ
		{
			int8 chIndex = -1;
			for ( int i = 0; i < EEquipPartType_MaxEquitPart; ++i )
			{
				if ( arrayCanEquip[i] == 1 )
				{   
					chIndex = i;
					break;
				}
			}
			return chIndex;
		}

		bool IsSuitEquip()        { return sSuitID != 0; }              // �Ƿ�����װ����
		bool IsHeroSuitEquip()	  { return sSuitID != 0 && nHeroID != 0; }				// �Ƿ�������װ
		bool IsSkillSuitEquip()   { return ( sSuitID != 0 && sPartCount == ECD_SkillSuitCount ); }                  // �Ƿ��Ǽ�����װ����
		bool IsElementSuitEquip() { return ( sSuitID != 0 && sPartCount == ECD_ElementSuitCount && bIsElements ); } // �Ƿ���������װ����
		bool IsCannotEvolve()     { return !(ustEquipType < equip_LeaderCard) ; }
		bool RandWhenCreate()const{ return bRandWhenCreate; }	        //�Ƿ����ʱ�����丽���������
		bool HasEquipHp();
	};

	struct SItemWeapon : public SItemCanEquip
	{
		uint16  ustModelID[ ECD_HandModelCount ];
		uint16  ustIdleModelID;
		int16   stWeaponType;      // ��������
		float   fWeaponAttackRate; // �����ĻӶ��ٶ�
		bool    bTwoHandWeapon;    // �Ƿ���˫������
		float   fAtkRange;         // ������Χ
		int32   iShotEffectID;     // ������Ч�����������������Ҫ��д

		SItemWeapon()
		{ memset(this, 0, sizeof(*this) ); }  
	};

	struct SItemArmour : public SItemCanEquip
	{
		int8   isCape;     // �Ƿ�Ϊ����
		int8   isHeadWear; // �Ƿ�Ϊͷ��
		uint16 ustModelID[EArmType_MaxSize][2][2];
		int16  stTypeForInGem   ; // ǿ������
		float  defendPhysics    ; // �������
		float  defendMagic      ; // ħ������
		/*
		* Author: 2012-10-9 16:10:19 liaojie
		* Desc:   ���HP��MP
		*/
		int		Hp				; // HP
		int		Mp				; // MP

		SItemArmour()
		{ memset(this, 0, sizeof(*this) ); }

		char IsCape()              { return isCape;       } // �Ƿ�����
	};

	// ��Ʒ����,ԭ�����Ʒ�Ķ�Ӧ��ϵ
	struct SProduceItem
	{
		SProduceItem() : ustMaterialID("[ItemDetail.h]SProduceItem.ustMaterialID"),
			ustMaterialNum("[ItemDetail.h]SProduceItem.ustMaterialNum")
		{
			memset( this, 0x00, sizeof(*this) );
		}
		//unsigned short ustMaterialID[ 3 ];
		//unsigned short ustMaterialNum[ 3 ];
		Array<unsigned short, 3>    ustMaterialID;
		Array<unsigned short, 3>    ustMaterialNum;    //Luoz add
		unsigned short ustToolID;
		unsigned short ustSpriteSkillID;
		unsigned short ustSpriteSkillLevel;
		unsigned short ustResultGoodID;
		unsigned short ustSuccessRate;
	};

	////ħ�����ϵĽṹ
	//struct SItemMagic:public SItemCommon
	//{
	//    unsigned short ustSuccessRate;        //ǧ��֮...

	//    unsigned short ustSpecialRate[ 7 ];    //ǧ��֮...
	//    unsigned short ustAffectWeaponMin[ 7 ];
	//    unsigned short ustAffectWeaponMax[ 7 ];
	//    unsigned short ustAffectClothesMin[ 7 ];
	//    unsigned short ustAffectClothesMax[ 7 ];
	//    unsigned short ustAffectShoeMin[ 7 ];
	//    unsigned short ustAffectShoeMax[ 7 ];
	//    unsigned short ustAffectGloveMin[ 7 ];
	//    unsigned short ustAffectGloveMax[ 7 ];
	//    unsigned short ustHeadPieceMin[ 7 ];
	//    unsigned short ustHeadPieceMax[ 7 ];
	//    unsigned short ustDecorateMin[ 7 ];
	//    unsigned short ustDecorateMax[ 7 ];
	//    unsigned short ustStatusRate;
	//};

	//�����ܵ�ְҵ����
	struct SSkillProfessionCondition
	{
		short stProfessionID;
		short stNeedLevel;
	};

	//�����ܵļ���ʹ������
	struct SSkillUsedCondition
	{
		unsigned short ustSkillID;
		//�����������ܿ�������
		unsigned short ustMinUsed,ustMaxUsed;
	};

	//�����ܵ�����
	struct SSkillUnderstandCondition
	{
		SSkillUnderstandCondition() : profession("[ItemDetail.h]SSkillUnderstandCondition.profession"),
			skillused("[ItemDetail.h]SSkillUnderstandCondition.skillused")
		{
		}
		int iProfessionNum;
		//SSkillProfessionCondition    profession[ const_iSkillUnderstandPCondition ];
		Array<SSkillProfessionCondition, const_iSkillUnderstandPCondition>    profession;
		int iSkillUsedNum;
		//SSkillUsedCondition            skillused[ const_iSkillUnderstandSCondition ];
		Array<SSkillUsedCondition, const_iSkillUnderstandSCondition>    skillused;    //Luoz add
	};

	//ʹ�ü��ܵ�����
	struct SSkillUsingCondition
	{
		SSkillUsingCondition() : profession("[ItemDetail.h]SSkillUsingCondition.profession")
		{
		}
		int iProfessionNum;
		//SSkillProfessionCondition    profession[ const_iSkillUsingPCondition ];
		Array<SSkillProfessionCondition, const_iSkillUsingPCondition>    profession;
	};

	enum EnumSkillActionFlags
	{
		IS_AUTO_STOP        = 0x01,    // ʩ�ż�������ͣ�£���������Ծ
		CAN_MOUNT_CAST      = 0x02,    // ����ʱ��ʩ��
		IS_WHOLE_ACTION     = 0x04,    // ��ȫ��������
		CANNOT_JUMP_CAST    = 0x08,    // ��Ծʱ�޷�ʩ�ţ���ʩ��ʱ������Ծ
		ONLY_MOUNT_CAST     = 0x10,    // ֻ�������ͷ�
	};

	enum EnumMountSkillProfessionType   // ְҵ��ص�ֻ������ʩ�ŵļ���
	{
		MSPT_ALL            = 0x00,
		MSPT_SPEAR          = 0x01,
		MSPT_STAFF          = 0x02,
		MSPT_FAN            = 0x04,
		MSPT_SWORD          = 0x08,
		MSPT_BOW            = 0x10
	};

	enum ESkillHpLimitType
	{
		SHT_None,  // ��
		SHT_Above, // ����
		SHT_Under, // ����
		SHT_TargetAbove, // ����
		SHT_TargetUnder, // ����
	};

	enum ESpecialTargetType
	{
		STT_NONE = 0, // ��
		STT_MINHP,    // Ѫ����
		STT_MINMP,    // ������
		STT_MINLEVEL, // �ȼ����
	};

	enum ESkillCategoryType
	{
		SCT_Attack,     // �˹�������
		SCT_Passive,    // �˱�������
		SCT_Assistant,  // �˸�������

		SCT_MountPassive = 10,              // ���ﱻ������
		SCT_MountMasterInitiativeUnControl, // �������˲��ɿ���������
		SCT_MountMasterInitiativeControl,   // �������˿ɿ���������

		SCT_PetPassive = 20,                // ���ﱻ������
		SCT_PetMasterAutoUnControl,         // �������˲��ɿ���������
		SCT_PetMasterManualControl,         // �������˿ɿ���������

		//�������������͵Ļ��ӵ������������������͵��м�
		SCT_HeroPassive = 30,				// ������������
		SCT_HeroAttack,						// ������������
	};

	enum ESpecialSkillType
	{
		ESST_Normal = 0         ,   // ��������

		ESST_Capture            ,   // ����       ��װ����
		ESST_SuckFetch          ,   // ����       ��װ����
		ESST_BreakOut           ,   // ����       ��װ����
		ESST_CallGraphic        ,   // ������֤�� ��װ����
		ESST_Other              ,   // ����       ��װ����
		ESST_SuitMax    = 39    ,   // ��װ�����������

		ESST_Team               ,   // ���鼼��
		ESST_TeamRelive         ,   // ���鸴��
		ESST_TeamFly            ,   // ���鴫��
		ESST_TeamMax    = 79    ,   // ���鼼���������

		ESST_XPSkill    = 99    ,   // XP����
		ESST_PetActive  = 100   ,   // �����ս����
	};

	// ��������������
	enum ESkillGeneralType
	{
		generaltype_action   = 0, // ����Action����
		generaltype_magic    = 1, // ����Magic����
		generaltype_sequence = 2, // �������м���
		generaltype_passive  = 3, // ���ڱ�������
		generaltype_trigger  = 4, // ���ڱ�����������
	};


	//���Ҽ������ö���ı�־
	enum ESkillTarget
	{
		target_no          , // ��Ŀ��
		target_myself      , // ��
		target_friend      , // ����
		target_normalplayer, // ��ͨ���(������Ұ����Լ����˵���)
		target_enemy       , // ����(ֻ�ܶԵ���)
		target_dead        , // ����Ŀ��(ֻ������)
		target_herb        , // Ŀ���ҩ
		target_mine        , // Ŀ���
		target_wood        , // Ŀ��ľͷ
		target_treasure    , // Ŀ�걦��
		target_pet         , // petΪĿ��
		target_all         , // �����˶�����
		target_team        , // ����Ŀ��
		target_mount       , // Ŀ������
		target_insect      , // Ŀ������
		target_guild       , // ����
		target_campforce   , // ͬ��Ӫ����
	};

	enum ESkillCastTarget
	{ //����ʹ��Ŀ������
		casttarget_me           , // ���Լ�ΪĿ��
		casttarget_friendlive   , // ����������ΪĿ��
		casttarget_enemylive    , // ��������
		casttarget_live         , // ��������
		casttarget_pos          , // ��λ��ΪĿ��
		casttarget_friendcorpse , // ������ʬ��ΪĿ��
		casttarget_enemycorpse  , // �Ե���ʬ��ΪĿ��
		casttarget_corpse       , // ʬ��
		casttarget_herb         , // �Բ�ҩΪĿ��
		casttarget_mine         , // �Կ�ΪĿ��
		casttarget_wood         , // ��ľͷΪĿ��
		casttarget_treasure     , // �Ա���ΪĿ��
		casttarget_pet          , // �Գ���ΪĿ��
		casttarget_team         , // ����Ŀ��
		casttarget_mount        , // ����ΪĿ��
		casttarget_insect       , // ����ΪĿ��
		casttarget_guild        , // �����Ա
		casttarget_campforce    , // ͬ��Ӫ����
	};

	enum EPassiveSkillTarget
	{
		PassiveSkillTarget_Self             , // �����Լ��ı�������
		PassiveSkillTarget_AllPet           , // �������г���ļ���
		PassiveSkillTarget_TargetPet        , // ����Ŀ�����ļ���
		PassiveSkillTarget_SelfAndAllPet    , // �����Լ������г���ļ���
		PassiveSkillTarget_SelfAndTargetPet , // �����Լ���Ŀ�����ļ���
	};

	enum ESkillBalanceType
	{ // ��������
		balancetype_none                , // û���κν���
		balancetype_damagephysicaldefend, // ����������˺�����
		balancetype_damagemagicdefend   , // ��ħ�������˺�����
		balancetype_damagebothdefend    , // �����ħ�������˺�����
		balancetype_restorehpmp         , // ��HP����
		balancetype_relive              , // �������
	};

	enum EClearStatueType
	{
		CLEAR_STATUS_0   ,    
		CLEAR_STATUS_1   , 
		CLEAR_STATUS_2   , 
		CLEAR_STATUS_3   , 
		CLEAR_STATUS_4   , 
		CLEAR_MAX_STATUS ,
	};

	//������������
	enum EIntonateInterruptType
	{
		EIT_Normal      ,   // ��������
		EIT_Move        ,   // �ƶ����
		EIT_Jump        ,   // ��Ծ���
		EIT_Msg         ,   // ��Ϣ���
		EIT_Map         ,   // �л���ͼ
		EIT_Force       ,   // ǿ�ƴ��

		EIT_MaxType     ,   // �������
	};


	struct SItemSkill : public SItemCommon
	{ //���ܵĶ���
		enum EItemSkillConst
		{
			EItemSkillConst_ActionMaxSize           = 10,
			EItemSkillConst_ActionSpeedMaxSize      = 20,
			EItemSkillConst_SkillNeedMaxSize        = 3,
			EItemSkillConst_AddStatusMaxSize        = 2,
			EItemSkillConst_DispelStatusMaxSize     = 4,

			EItemSkillConst_AddDamageType_None          = 0,    //�޸����˺�
			EItemSkillConst_AddDamageType_Status        = 1,    //״̬�����˺�
			EItemSkillConst_AddDamageType_Profession    = 2,    //ְҵ�����˺�
			EItemSkillConst_AddDamageType_All           = 3,    //ȫ�����˺�

			EItemSkillConst_MeStatusFirstIndex      = 0,
			EItemSkillConst_MeStatusSecondIndex     = 1,

			EItemSkillConst_XinFaMaxSize            = 5, // ���������ķ�����
		};

		enum EMountSkillCategory
		{
			EMountSkillCategory_Aptitude    =   1,  // ������
			EMountSkillCategory_Restore     =   2,  // �ظ���
			EMountSkillCategory_Assist      =   3,  // ������
			EMountSkillCategory_Control     =   4,  // ������
			EMountSkillCategory_Profession  =   5,  // ְҵ��
			EMountSkillCategory_Special     =   6,  // ������
			EMountSkillCategory_MaxSize     =   7,
		};

		struct SEasyUseData
		{
			bool bApplyToFriend;
			bool bSkillWithDamage; // ������˺��ļ���
			bool bCanAttackPos;    // ���Թ�������

			SEasyUseData()
			{
				bApplyToFriend   = false;
				bSkillWithDamage = false;
				bCanAttackPos    = false;
			}
		};

		uint32                         dwSkillNameAddr;             // �������ֵ�ַ
		uint32						   dwRideAction;				// ��ս���ܶ���
		uint32						   dwRideIntonateAction;		// ��ս�������ܶ���
		Array<uint32, EItemSkillConst_ActionMaxSize> dwSkillAction; // ���ܶ�������
		uint16                         groupId;                     // ������ID
		uint16                         groupLevel;                  // ������ȼ�
		uint16                         ustLevel;                    // ���ܵĵȼ�
		uint16                         ustPrepTime;                 // ����ʱ�� (ms)
		bool                           bShowIntonateBar;            // �Ƿ���ʾ������ [�ͻ���ʹ��]
		uint32                         dwIntonateAction;            // ����׼������
		uint32                         dwIntonateEffectAddr;        // ������Ч  ( �� )
		uint32                         dwAttackerEffectAddr;        // ��������Ч( �� )
		uint32                         dwSkillEffectAddr;           // ������Ч  ( �� )
		uint32                         dwTargetEffectAddr;          // Ŀ����Ч  ( �� )
		uint32                         dwIntonateEffectAddr2;       // ������Ч  ( Ů )
		uint32                         dwAttackerEffectAddr2;       // ��������Ч( Ů )
		uint32                         dwSkillEffectAddr2;          // ������Ч  ( Ů )
		uint32                         dwTargetEffectAddr2;         // Ŀ����Ч  ( Ů )
		uint16                         ustIDTargetHitAction;        // Ŀ��NPC�����Ķ���
		uint8                          triggerType;                 // ���ܴ�������
		float                          actionRatio;                 // ���ܴ�������
		uint16                         normalAttackRatio;           // ��ͨ��˾��������
		int16                          ustMeAddStatusID[EItemSkillConst_AddStatusMaxSize];            // ����״̬���(���ҵ�)
		uint16                         ustMeAddStatusLevel[EItemSkillConst_AddStatusMaxSize];         // ����״̬�ȼ�(���ҵ�)
		int16                          ustDstAddStatusID[EItemSkillConst_AddStatusMaxSize];           // ����״̬���(���Է���)
		uint16                         ustDstAddStatusLevel[EItemSkillConst_AddStatusMaxSize];        // ����״̬�ȼ�(���Է���)
		uint16                         ustStatusHitRate;            // ״̬���м���
		uint32                         dwSubComboStatus;            // ���״̬λ��
		Array<uint32,CLEAR_MAX_STATUS> dwClearStatus;               // ���״̬ID
		uint16                         ustHoldTime;                 // ��Ӳʱ��
		uint16                         ustDamageBalanceType;        // ʹ�õ��˺����㹫ʽ
		Array<uint16, EItemSkillConst_ActionSpeedMaxSize>  ustSkillActionSpeed;  // ���ܶ����Ĳ����ٶ�
		uint16                         ustCostHP;                   // ����HP
		uint16                         ustCostHPPer;                // ����HP(%)
		uint16                         ustCostMP;                   // ����MP
		uint16                         ustCostMPPer;                // ����MP(%)    
		int16                          stSkillType;                 // ���ܵ�����(����ͨ�������Ǳ�ɱ��(��һ�ֱ�ɱ��)���Ƿ���(��һ������)�ǻ�ǽ�����ǻ���..)
		int16                          stGeneralType;               // ��������������(һ����Action���ͣ�һ����Magic����;һ�������м���,һ���Ǳ�������)
		int16                          stTargetType;                // ���õĶ�������
		int32                          iDurationTime;               // Ч���ĳ���ʱ��
		int32                          iDamageBalanceDelay;         // Ч���˺��Ľ�����
		int16                          stEffectCenterType;          // ����Ч����������
		bool                           bMoveInterrupt;              // �Ƿ��ƶ����      true Ϊ�ɴ�� false Ϊ���ɴ��
		int8                           cLearnProfessionReq;         // ���ܵ�ְҵ����
		int16                          stLearnLevelReq;             // ���ܵĵȼ�����
		float                          fRangeCanCast;               // ���ʩ������
		float                          fRangeCanCastMin;            // ��Сʩ������
		int16                          stDamageEffectDistance;      // �˺���Ч����(?)
		int16                          shCastType;                  // ʩ�ŷ�Χ����
		int16                          shMaxTargetNum;              // ���Ŀ�����
		float                          fAOEradius;                  // ��Χ���ܵİ뾶
		bool                           bNeedWeapon;                 // �Ƿ���Ҫ����
		int16                          stUseItem;                   // ʹ�ô˼�������Ҫ�ĵ���
		bool                           bHoldSkill;                  // ά�ּ��ܵĳ���ʱ��>0
		uint16                         ustHoldEffect;               // ά�ּ�����Ч
		uint32                         dwSkillCoolDownTime;         // ��ȴʱ��
		int32                          nSkillCoolDownType;          // ��ȴ���� 
		uint16                         ustCastTarget;               // ʩ��Ŀ��
		Array<int16,EItemSkillConst_SkillNeedMaxSize> stSkillNeed;      // ��������
		Array<int16,EItemSkillConst_SkillNeedMaxSize> stSkillLevelNeed; // ѧϰǣ�Ƽ��ܵȼ�
		int32                          stMoneyNeed;                 // ѧϰ�����Ǯ
		int16                          stWeaponNeed;                // ��������Ҫ��
		int16                          stEnmity;                    // �ü���������ɵĳ��ֵ�仯
		bool                           bContinueAtt;                // �Ƿ��������
		int16                          stSkillHitRate;              // ����������
		uint16                         ustSkillMaxLvl;              // �������ȼ�
		bool                           bNeedTestBackStrike;         // �Ƿ���Ҫ�����ж�
		float                          fBackStrikePlus;             // �����ӳ�
		bool                           bNeedTestAngle;              // �Ƿ���Ҫ�Ƕ��ж�
		float                          fAngle;                      // ʩ�ŽǶ�
		bool                           bEmissionSkill;              // �Ƿ��似��
		bool                           bAssaultSkill;               // �Ƿ��漼��
		bool                           bHideSkill;                  // �Ƿ����μ���
		bool                           bGiddyDischarge;             // ѣ���Ƿ�����ͷ�
		bool                           bCancelHideSkill;            // �Ƿ�᳷����ǰ������״̬
		bool                           bAutoAttackTarget;           // �Ƿ��Զ���������Ŀ��
		int32                          nLearnNeedExp;               // ѧϰ������Ҫ�ļ��ܾ���
		int32                          nSuckHpAtt;                  // ����HP
		int32                          nSuckMpAtt;                  // ����MP
		bool                           bIsRelive;                   // �Ƿ񸴻��
		float                          fReliveHp;                   // ��������HP
		float                          fReliveMp;                   // ����MP
		bool                           bSummonSkill;                // �Ƿ��ٻ�����
		int32                          nSummonMonsterId;            // �ٻ��ĳ���Id
		int16                          shPassiveSkillTarget;        // �����������ö���
		int32                          nPassiveSkillTargetSkillID;  // �����������õļ���ID
		int16                          stBackStrikeMeStatus;        // �������ҵ�״̬Id
		int16                          stBackStrikeMeStatusLevel;   // �������ҵ�״̬�ȼ�
		int16                          stBackStrikeDstStatus;       // �������Է���״̬
		int16                          stBackStrikeDstStatusLevel;  // �������Է���״̬�ȼ�
		float                          fBackStrikeStatusRate;       // ����״̬������
		char                           cHpLimitType;                // ʹ�ü���Ѫ�����Ƶ�����
		float                          fHpPerLimit;                 // ʹ�ü���Ѫ�����ưٷֱ�
		uint32                         ustInstantMovingType;        // �Ƿ�˲���ƶ�
		bool                           bIsAfterIllusion;            // �Ƿ������
		int32                          nInterruptIntonatingAbility; // ��������������
		bool                           bEnterFightStatus;           // �Ƿ����ս��״̬
		bool                           bIsCatchNurturePet;          // �Ƿ�׽����
		bool                           iskillpet;                   // �Ƿ�ɱ������
		bool                           ispettouseskill;             // �Ƿ�ʹ�����ͷż���
		uint16                         ustPetSkillID;               // ����ʹ�ü���ID
		uint16                         ustPetSkillLevel;            // ����ʹ�ü��ܵȼ�
		bool                           needpet;                     // �б�������ʹ�ü���
		int32                          iSkillActionFlags;           // ������Ϊ�����ۺϱ�־
		uint16                         usConsumeFightPower;         // ���ĵĶ���ֵ
		uint16                         usIncreaseFightPower;        // ���ӵĶ���ֵ
		uint32                         dwSkillDescription;          // ��������
		int32							nAddonDesc1;				// ������������ֵ
		int32							nAddonDesc2;				// ������������ֵ
		int32							nXinFaID;					// �����ķ�ID
		int32							nLearnNeedXinFaLevel;		//	ѧϰ��Ҫ�ķ��ȼ�
		uint32                         dwCommonCoolDownTime;        // ������ȴʱ��
		float                          fDamageRate;                 // �˺��ٷֱ�
		uint32                         dwDamageDelayBalanceTime;    // �˺��ӳٽ���ʱ��
		char                           cFightStateCastType;         // ս��״̬�ͷ�����
		bool                           bMustInBackUse;              // �����ڱ���ſɹ���
		uint16                         usSpecialTargetType;         // ����Ŀ���ж�
		float                          fFPDamageRatio;              // ����Ӱ���˺���
		bool                           bNextNotIntonate;            // ������������Ҫ����
		int8                           nNextNotIntonateNum;         // ������������Ҫ��������
		uint16                         sSkillCategory;              // �������� ESkillCategoryType
		bool                           bScriptRunSkill;             // �Ƿ�ű�ִ�м���
		int32                          iMountSkillProfessionType;   // ְҵ��ص�ֻ������ʩ�ŵļ��ܣ����嶨���EnumMountSkillProfessionType
		uint16                         usConsumeVigor;              // ���ĵľ���ֵ
		uint16                         specialSkillType;            // ��ɫ��������

		uint8                          additionalDamageType;	    // �����˺�����
		uint32                         additionalDamageStatus;	    // �����˺�״̬
		uint16                         additionalDamagePer;         // �����˺��ٷֱ�
		int8                           additionalDamageProfession;  // �����˺�ְҵ
		int16                          addtionalCritical;           // �����ʼӳ�

		uint16                         additionalPhyAttack;         // ������������
		uint16                         additionalMagAttack;         // ����ħ��������

		int8                           dispelNegativeType[EItemSkillConst_DispelStatusMaxSize];         // �������״̬����

		uint8                          mountSkillCategory;          // ���＼�����
		uint8                          mountAptitudeCategory;       // ���＼���������  
		uint16                         mountAptitudeModulus;        // ���＼��ϵ��

		int8                           petSkillCategory;            // ���＼�����
		int8                           petAutoSkillType ;           // �����Զ���������
		uint8                          petAutoSkillTriggerRate;     // �����Զ����ܻ�����������

		uint16                         releaseLapoverStatus;        // �ͷŵ��Ӽ���
		uint16                         breakStrike      ;           // �Ƽ��˺�
		uint16                         stabStrike       ;           // �ᴩ�˺�
		uint16                         elementStrike    ;           // Ԫ���˺�
		uint16                         toxinStrike      ;           // �����˺�
		uint16                         spiritStrike     ;           // �����˺�


		Array< bool, EArmType_MaxSize> arrayProfessionReq;          // �����ͷ���Ҫְҵ

		SEasyUseData                   easyusedata;                 // ���ײ�ѯ����

		SItemSkill() : dwSkillAction("[SItemSkill.dwSkillAction"),dwClearStatus("SItemSkill.dwClearStatus"),
			ustSkillActionSpeed("SItemSkill.ustSkillActionSpeed"), stSkillNeed("SItemSkill.stSkillNeed"), 
			stSkillLevelNeed("SItemSkill.stSkillLevelNeed")
		{
			bSummonSkill                = false;
			nSummonMonsterId            = -1;
			bAssaultSkill               = false;
			bCancelHideSkill            = true;
			bHideSkill                  = false;
			bGiddyDischarge             = false;
			bEmissionSkill              = false;
			bAutoAttackTarget           = false;
			bNeedTestBackStrike         = false;
			bNeedTestAngle              = false;
			fAngle                      = D3DX_PI;
			shCastType                  = 0;
			shMaxTargetNum              = 1;
			bIsAfterIllusion            = false;
			nInterruptIntonatingAbility = 0;
			bEnterFightStatus           = true;
			iskillpet                   = false;

			ustMeAddStatusID[0]         = -1;
			ustMeAddStatusLevel[0]      = 0 ;
			ustMeAddStatusID[1]         = -1;
			ustMeAddStatusLevel[1]      = 0 ;
			ustDstAddStatusID[0]        = -1;
			ustDstAddStatusLevel[0]     = 0 ;
			ustDstAddStatusID[1]        = -1;
			ustDstAddStatusLevel[1]     = 0 ;
		}
		const char* GetSkillName();
		const char* GetSkillRideAction();
		const char* GetSkillAction( int Index );
		const char* GetIntonateAction();
		const char* GetIntonateEffectName();
		const char* GetIntonateEffectName2();
		const char* GetAttackerEffectName();
		const char* GetAttackerEffectName2();
		const char* GetTargetEffectName();
		const char* GetTargetEffectName2();
		const char* GetSkillEffectName();
		const char* GetSkillEffectName2();
		const char* GetSkillDescription();
		const char* GetRideIntonateAction();

	};

	enum EStatusRestoreType
	{
		ESRT_OnlyInServer = 0,  // ��һ���������ڴ� ��Ч
		ESRT_OnlyInWorld,       // ��������Ϸ���緶Χ�ڴ� ��Ч
		ESRT_Forever,           // ����ʲôʱ�򶼴�
		ESRT_Never,             // ����ʲôʱ�򶼲���
		ESRT_OnlyInMap,         // ��ͬһ��ͼ�ڴ�   ��Ч
	};

	struct SItemStatus : public SItemCommon
	{ // ״̬�Ķ���
		enum EConstDefine 
		{
			ECD_TimeExpMulModulusCount = 5,
			ECD_DurationTimeForever    = -1, // ����Buffer

			ECD_ChangeSkillMaxSize     = 4,
		};

		uint16                        ustLevel          ; // ״̬�ȼ�
		uint32                        dwStatusEffectAddr; // ״̬��Ч
		uint32                        dwStatusActionAddr; // ״̬����
		bool                          bAvail            ; // �Ƿ�����״̬
		int32                         iDurationTime     ; // ״̬����ʱ��(ms)
		int32                         iBalanceDelayTime ; // Ӱ����ʱ��(ms)
		int16                         stType            ; // ״̬������
		int16                         stPriority        ; // ״̬�����ȼ���
		bool                          bIsCanCong        ; // �Ƿ�ɵ���
		int16                         stBalanceType     ; // ״̬���㹫ʽ
		bool                          bAttckedNoStatus  ; // �ܵ����������״̬
		bool                          bAttckNoStatus    ; // ���������״̬        
		int16                         changePhyAttackPer; // �ı���������%
		float                         changePhyAttack   ; // �ı���������
		int16                         changeMagAttackPer; // �ı�ħ��������%
		float                         changeMagAttack   ; // �ı�ħ��������
		Array<int16, EDefendType_Max> changeDefendPer   ; // �ı������%
		Array<float, EDefendType_Max> changeDefend      ; // �ı����
		int16                         changeHPMaxPer    ; // �������ֵ%
		int32                         stChanged_HPMax   ; // �������ֵ
		int16                         changeMPMaxPer    ; // �������ֵ%
		int32                         stChanged_MPMax   ; // �������ֵ
		int16                         resumeHPPer       ; // �����ָ�%
		int16                         resumeHP          ; // �����ָ�
		int16                         resumeMPPer       ; // �����ָ�%
		int16                         resumeMP          ; // �����ָ�
		int32                         stChanged_HP      ; // ��������
		int32                         stChanged_MP      ; // ��������
		int32                         recoverHPBasePer  ; // �ָ���������%
		int32                         recoverMPBasePer  ; // �ָ���������%
		int32                         recoverHPMaxPer   ; // �ָ���������%
		int32                         recoverMPMaxPer   ; // �ָ���������%
		int32                         changeActivityMax ; // ���Ļ�������
		int16                         stChanged_Hit     ; // ������������
		int16                         stChanged_Hedge   ; // ���Ķ�������
		int16                         changeTenacity    ; // ����
		int16                         changed_Critical  ; // �ı䱩����
		int16                         changed_CriticalIntensity    ; // �ı䱩���˺�
		float                         fChanged_ReboundVal     ; // �˺���������
		uint8                         nDamageReflectProability; // �˺���������
		int16                         stAbsorbExtraHPVal      ; // ��Ѫֵ
		float                         fSuckHpRate             ; // ��Ѫ����
		uint8                         nSuckHpProbability      ; // ��Ѫ�ļ���
		float                         fMoveSpeedChanged       ; // �ƶ��ٶ�
		int16                         nMoveSpeedPer           ; // �ƶ��ٶ� %
		float                         fAttSpeedPer            ; // �����ٶ�
		bool                          bIsMove                 ; // �Ƿ����ƶ�        
		bool                          bIsAtt                  ; // �Ƿ���������
		bool                          bIsUsingMagic           ; // �Ƿ���ʹ��ħ��   
		bool                          bIsBePhyAttack          ; // �Ƿ��ܱ�������
		bool                          bIsBeMagAttack          ; // �Ƿ��ܱ�ħ������
		bool                          bIsUsingTools           ; // �Ƿ���ʹ�õ��߾�
		int8                          stMagicShield           ; // ħ����
		float                         fSuckDamagePer          ; // �����˺��ٷֱ�
		int32                         stSuckDamageMax         ; // �����˺�����
		Array<int16, EBaseAttr_MaxSize> stAddBaseAttr         ; // һ�����Եļӳ�
		Array<int16, EBaseAttr_MaxSize> stAddBaseAttrPer      ; // һ�����Եļӳ�%
		bool                          bUseStateColour         ; // �Ƿ�ʹ��״̬��ɫ
		float                         fStateColourR           ; // �� /����״̬���������ɫ
		float                         fStateColourG           ; // ��
		float                         fStateColourB           ; // ��
		float                         fChangActionTime        ; // �ı䶯������ʱ��
		bool                          bIsChangActionTime      ; // �Ƿ�ı䶯������ʱ��
		bool                          bIsHide                 ; // �Ƿ����� 
		bool                          bIsFlyAir               ; // �Ƿ�����              
		bool                          bIsClearDamgeStatus     ; // �Ƿ�����к�״̬
		bool                          bIsReplaceOldStatus     ; // �Ƿ��滻����״̬
		int32                         nChangeMonsterID        ; // ����ID
		bool                          bIsAddBufferBeCSed      ; // ������ʱ��״̬
		int16                         stBeCsedAddBufferMeId   ; // ������ʱ��״̬Id
		int16                         stBeCsedAddBufferMeLevel; // ������ʱ��״̬Level
		bool                          bIsAddDeBufferToAttacker; // �Ƿ������������״̬
		float                         fAddDeBufferByHpPer     ; // �������߼�״̬HP����
		int16                         stAddDeBufferID         ; // �����������ӵ�״̬ID
		int16                         stAddDeBufferLevel      ; // �����������ӵ�״̬�ȼ�
		int32                         nSuperpositionCount     ; // ���ӵ�����
		int32                         restoreType             ; // �洢����
		int32                         nStandingEnmity         ; // �������
		float                         fAddExpMul              ; // ���鱶��
		float                         fAddSkillExpMul         ; // ���ܾ��鱶��
		int32                         nStatusAnim             ; // ״̬����
		bool                          bIsClearByDead          ; // ���������״̬
		int16                         stActualTime            ; // ������ʵʱ��(Сʱ)
		bool                          bIsRandRun              ; // �Ƿ��������
		bool                          bIsPetSupport           ; // �Ƿ��������˺�
		bool                          bBackAttckedDispel      ; // �ܵ����������״̬
		bool                          bMoveDispel             ; // �ƶ������״̬
		int16                         stChangedFightPoint        ; // ���Ķ�����
		Array<float, ECD_TimeExpMulModulusCount> timeExpModulus  ; // ʱ�����ӵĻ�����������
		float                         timeExpMul                 ; // ʱ�����ӵĻ�������ǰ���µı���
		uint32                        dwAnimationAddr            ; // ������
		bool                          bInvincible                ; // �޵�״̬
		int8                          negativeType               ; // ����״̬����
		uint8                         damagetohp                 ; // �˺�ת����hp
		bool                          bDisableCallGraphic        ; // �Ƿ����κ�����֤��
		uint16                        actionMapConfigId          ; // ��Ӧ���ڳ���id��������
		bool                          canCancel                  ; // �Ƿ����ȡ��
		uint8                         hurtImmunity               ; // �˺�����

		uint8                         attackModulus           ;    // ����ϵ��
		uint8                         defendModulus           ;    // ����ϵ��
		bool                          ifConsumeEnergy         ;    // �Ƿ���������
		bool                          ifStatusIntonate        ;    // �Ƿ��������״̬

		uint16                      changeSkillIds[ECD_ChangeSkillMaxSize]      ;   //�ı���ȴʱ��ļ���
		uint32                      changeSkillTimes[ECD_ChangeSkillMaxSize]    ;   //�ı似����ȴʱ��

		uint8                         addEquipAttrType        ;   // Ӱ��װ����������
		uint8                         addEquipAttrValuePer    ;   // Ӱ��װ�����Լӳ�

		float                         activityMul             ;   // ��������
		uint16                        reduceTax               ;   // ����˰��
		uint16                        deathDurabilityPer      ;   // ����װ���;öȽ���
		uint16                        deathMountHPDropPer     ;   // ����������������

		int32                         addMoney                ;   // ���ӽ�Ǯ         
		int32                         addReputation           ;   // ��������
		int32                         addExploit              ;   // ���ӹ�ѫ
		int32                         addHonour               ;   // ��������
		int32                         addMasterValue          ;   // ��������
		int32                         addBattleScore          ;   // ����ս������
		float                         reputationMul           ;   // ��������
		float                         exploitMul              ;   // ��ѫ����
		float                         honourMul               ;   // ��������
		float                         masterValueMul          ;   // ��������
		float                         battleScoreMul          ;   // ս�����ֱ���
		int32                         addHonourLimit          ;   // ������������

		uint8                         lapoverNum              ;   // ������������
		uint16                        lapoverValue            ;   // ����ֵ
		uint16                        lapoverMod              ;   // ����ϵ��

		uint16                        breakStrike             ;   // �Ƽ��˺�
		uint16                        stabStrike              ;   // �ᴩ�˺�
		uint16                        elementStrike           ;   // Ԫ���˺�
		uint16                        toxinStrike             ;   // �����˺�
		uint16                        spiritStrike            ;   // �����˺�

		uint16                        breakResist             ;   // �Ƽ׿���
		uint16                        stabResist              ;   // �ᴩ����
		uint16                        elementResist           ;   // Ԫ�ؿ���
		uint16                        toxinResist             ;   // ���ؿ���
		uint16                        spiritResist            ;   // ������

		int16                         addCatchPetRate         ;   // ���ӳ��ﲶ׽����

		bool						  canRide				  ;	  // �Ƿ���������
		uint16						  BeDamagePerHpMax		  ;   // ���˺��󲻹ܶ���ֵ,ÿ�ζ�ֻ���ٷֱ�����

		bool						  canGetHonour			  ;   // �Ƿ���Ի������
		bool						  canBeGetHonour		  ;	  // �Ƿ���Ա��������

		SItemStatus() : changeDefend("SItemStatus.changeDefend"),
			changeDefendPer("SItemStatus.changedDefendPer"),
			timeExpModulus("SItemStatus.timeExpModulus")
		{ 
			memset(this, 0, sizeof(*this) ); 
			canGetHonour = true;
			canBeGetHonour = true;
		}

		bool        IsForeverStatus()
		{ return iDurationTime == ECD_DurationTimeForever; } // �Ƿ�������Buffer
		const char* GetStatusEffectName();
		const char* GetStatusAction();
		const char* GetAnimationName();
		bool        IsHaveContinueValueChange();
		bool		IsCanGetHonour(){return canGetHonour;}
		bool	    IsCanBeGetHonour(){return canBeGetHonour;}
	};

	struct SItemAction : public SItemCommon
	{ //��Ҷ����Ķ���
		SItemAction()
		{
			memset(this, 0, sizeof(*this) );
		}
		unsigned short ustActionID; //����ID
		short    stType;            //�������ͣ�0���������� 1����Ⱥ���� 2���罻������
		short    stSinglePlayTime;  //���β���ʱ��
		short    stLastingPlayTime; //��������ʱ��
		bool     bLastFrameRemain;  //�������һ֡
	};

	struct SItemReel : public SItemCommon
	{ // ����Ķ���
		enum EConstDefine
		{
			ECD_RatioMaxSize = 6,
		};

		SItemReel()
		{
			memset(this, 0, sizeof(*this) );
		}
		unsigned short skillId;      // ����Id
		unsigned char  skillLevel;   // ����
		unsigned char  replaceRatio[ECD_RatioMaxSize]; // ����������ܵļ���
		unsigned char  mountTakeLevel;  // ����Я���ȼ�
		unsigned char  mountLevel;      // ����ȼ�
		unsigned char  petTakeLevel;    // ����Я���ȼ�
		unsigned char  petLevel;        // ����ȼ�
		unsigned long  costMoney;       // ���ѽ�Ǯ
	};

	struct SItemTask : public SItemCommon
	{
		SItemTask ()
		{ memset(this, 0, sizeof(*this) );}
	};

	enum EItemOtherType
	{
		OtherType_Unknow        ,   // δ֪
		OtherType_PetIdentify   ,   // ����ͼ��
		OtherType_ZhujiangIdentify   ,   // ����ͼ��
		OtherType_Mount				// ����
	};

	struct SItemOther : public SItemCommon
	{
		SItemOther ()
		{ memset(this, 0, sizeof(*this) );}

		unsigned char   otherType;  
		unsigned short  petType  ;  // �������ͼ������
	};

	// һЩ����, ת����ʹ�õĲ���
	struct SItemCheckUp : public SItemCommon
	{
		enum EConstDefine
		{
			// ��Ʒ��������
			ECD_MoveStar = 0,             // ���ǵ���
			ECD_Elements = 1,             // ���м�����
			ECD_Suit     = 2,             // ��װ����

			// ����Ч������
			ECD_ElementsClear   = 0,      // �������Ԫ��
			ECD_ElementsCheckUp = 1,      // ��������Ԫ��
			ECD_ElementsMove    = 2,      // ����ת��ʯͷ

			// ��װ
			ECD_SkillSuitLevel     = 0,   // ������װװ������
			ECD_SkillSuitChange    = 1,   // ������װװ��ת��
			ECD_SkillSuitAttribute = 2,   // ϴ������װ���Եĵ���
			ECD_ElementsSuitLevel  = 3,   // �����ᴿ����
			ECD_ElementsSuitChange = 4,   // ����ת������
		};

		SItemCheckUp ()
		{ memset( this, 0, sizeof( SItemCheckUp ) ); }

		//bool bExclusive;        // �Ƿ�ɵ���
		short stCheckUpType;    // ��Ʒ��������
		short stEffectType;     // ����Ч������
		short stEquipLevel;     // ��Ӧ��װ���ȼ�
		short stEffectLevel;    // ���õȼ� ( ����Ǽ�����װ��������, �����1-5���ȼ� )


		int nValue1;            // Ԥ���ֶ�1  �������װ������������, ���ֵ�����ǿ����װ���ϵ�ǿ����Ӧ����װ��ID  �����ECD_ElementsSuitLevel����, ���ֵ�Ƕ�Ӧ����������(��ľˮ����1-5, ��������ܼ���, ���ֵ�� ItemElements_End = 6 ) 
		int nValue2;            // Ԥ���ֶ�2  �������װ������������, ���ֵ�����ǿ����װ���ϵ�ǿ����Ӧ��Ůװ��ID
	};

	struct SItemRealAward : public SItemCommon
	{
		SItemRealAward ()
		{ memset( this, 0, sizeof( SItemRealAward ) );}

	};

	// ר����Ʒ
	struct SItemSpecial : public SItemCommon
	{
		SItemSpecial()
		{
			memset( this, 0, sizeof( SItemSpecial ) );
		}

		enum EConstDefine
		{
			ECD_MarriageCard = 1,       // ���ϲ��
			ECD_UnknowEquip	 = 2,       // δ����װ��
		};

		unsigned char uchSpecialType;   // ����
		//bool bExclusive;                // �Ƿ�ɵ���
	};

	// ����
	struct SItemTalisman : public SItemCommon
	{
		enum EConstDefine
		{

		};

		SItemTalisman()
		{
			memset( this, 0, sizeof( SItemTalisman ) );
		}

		int    iModelID;                                          // ģ��ID

		int8   iSexReq;                                           // �Ա�����
		Array< bool, EArmType_MaxSize> arrayEquipArmsReq;         // ְҵ����
		int16  iEquipLevelReq;                                    // ��������

		uint16 skillId;                                           // ����Id
		uint16 skillLevel;                                        // ���ܵȼ�

		uint32 daoxing          ; // ��������
		uint16 poolId           ; // ����������Գ�ID
		uint32 nimbusMax        ; // �������ֵ
		uint16 nimbusRestore    ; // �����ظ�
	};

	struct SItemPetEquip : public SItemCommon
	{
		//����װ��
		SItemPetEquip()
		{
			memset( this, 0, sizeof( SItemPetEquip ) );
		}

		//����װ��ֻ��һ������
		int						Strength;//����
		int						Agility;//����
		int						Stamina;//����
		int						Intelligence;//����

		uint16					iEquipLevelReq;//�ȼ�����

		int						iPos;//װ����λ��
	};

	struct SItemGuild : public SItemCommon
	{
		SItemGuild ()
		{ memset( this, 0, sizeof( SItemGuild ) );}

		enum EConstDefine
		{
			ECD_GuildBox = 0,   // �����ѹ�ھ���
			ECD_ClearRupture,   // ����ж�����
			ECD_MemberCall,     // �����ټ�����
		};

		unsigned char uchType;      // ������Ʒ������

		unsigned int nValue1;       // Ԥ����Value
		unsigned int nValue2;       // Ԥ����Value
	};

	struct SItemTreasureBox : public SItemCommon        // ��������
	{
		SItemTreasureBox ()
		{ memset( this, 0, sizeof( SItemTreasureBox ) );}

		enum TreasureBoxDefine
		{
			BoxType_Luck = 0,   // ҡ��������
			BoxType_Receive,    // �콱������
			BoxType_BoxKey,     // ���ӵ�Կ��
		};

		uint8  uchBoxType;    // ����
		uint8  uchLevel;      // �ȼ�
		uint16 ustCorrItemID; // ��Ӧ��ID( ���Ӷ�ӦԿ��, Կ�����Ӧ����, û�������� )
		uint16 ustNewItemID;  // ʹ�ú�������µ�id
	};

	struct SItemCard : public SItemCommon
	{
	};

	enum EGemType
	{
		egem_normal = 0,  // ��ͨ��ʯ
		egem_red       ,  // �챦ʯ
		egem_yellow    ,  // �Ʊ�ʯ
		egem_blue      ,  // ����ʯ
		egem_green     ,  // �̱�ʯ
		egem_special   ,  // ���ⱦʯ
		egem_max   
	};

	// ����Ƕ�ı�ʯ
	struct SItemGem : public SItemCommon
	{
		enum EConstDefine
		{
			CD_TypeCount  = 2,
			CD_ValueCount = 2,
		};

		SItemGem()
		{
			gemType          = 0;   
			gemLevel         = 0;    
			effectEquipPart  = 0;   
			preGemId         = 0;   
			preGemType       = 0;  
			useCostMoney     = 0;
			type[0]          = 0;
			type[1]          = 0;
		}

		uint8          gemType             ; // ��ʯ����
		uint8          gemLevel            ; // ��ʯ����
		uint32         effectEquipPart     ; // ���ò�λװ��
		uint16         preGemId            ; // ǰ�ü��ʯId
		uint8          preGemType          ; // ǰ�ü��ʯ����
		int32          useCostMoney        ; // ʹ�û���
		int16          levelLimit          ; // ���ö���ȼ�����
		uint16         type[CD_TypeCount]  ;    
		CustomValue    value[CD_ValueCount];
		uint16		   downGradeID;			 //��Ƕʧ�ܱ�ʯ������Ӧ�ĵ�һ���ı�ʯID

		bool CanEquipPart( uint32 equipPart ) // �ɷ������ڴ�װ��λ
		{ return effectEquipPart == 0 ? true : _HAS_FLAG( effectEquipPart, equipPart ); }
	};

	enum EMaterialType
	{
		ematerial_metal   = 0, // ����
		ematerial_wood       , // ľͷ
		ematerial_pelage     , // ëƤ
		ematerial_starlevel  , // ���ǲ���
		ematerial_compound   , // �ϳɸ���
		ematerial_identify   , // ��������
		ematerial_reidentify , // ������¯
		ematerial_stiletto   , // װ����ײ���
		ematerial_gemtakedown, // ��ʯ��ж����
		ematerial_gemlevelup , // ��ʯ��������
		ematerial_soulstamp  , // ������̲���
		ematerial_openlight  , // װ���̽����
		ematerial_reopenlight, // װ���̽��¯����
		ematerial_maintain   , // װ����ֵ����
		ematerial_maintacross, // װ���缶��ֵ����
		ematerial_charm      , // ������������
		ematerial_inlay		 , // ��Ƕ��
		ematerial_rateboll   , // ���ʱ���
		ematerial_gemcomposerune, // ��ʯ�ϳɷ�
		ematerial_zhujianguprune, // �����ϳ��������ʲ���
		ematerial_mountrune,	// ����ǿ������
		ematerial_max        
	};

	struct SCreateMaterial : public SItemCommon
	{
		int16  stMaterialType   ; // ��������
		float  fAddIntensifyRate[18]; // ����ǿ������
		int16  useLevel         ; // ����ʹ�õȼ�
		int16  levelLowLimit    ; // ���ö���ĵȼ�����
		int16  levelUpLimit     ; // ���ö���ĵȼ�����
		int16  starLevelLimit	; // �Ǽ�Ҫ��
		int16  useCostMoney     ; // ʹ�û���
		uint32 effectEquipPart  ; // ���ò�λװ��
		int16  equipQuality     ; // װ��Ʒ��Ҫ��
		uint32 nValue           ; // �������ݽṹ ��ײ�����˳����

		SCreateMaterial()
		{ 
			stMaterialType    = ematerial_max;
			//fAddIntensifyRate = 0;
			memset(fAddIntensifyRate, 0, 18*sizeof(float));
			levelLowLimit     = 0;
			levelUpLimit      = 0;
			starLevelLimit    = 0;
			starLevelLimit    = 0;
			effectEquipPart   = 0;
			nValue            = 0;
		}

		bool CanEquipPart( uint32 equipPart ) // �ɷ������ڴ�װ��λ
		{ return effectEquipPart == 0 ? true : _HAS_FLAG( effectEquipPart, equipPart ); }
	};

	struct SItemCreateItemRule : public SItemCommon
	{ //�ϳ��䷽
		struct SMaterial
		{   
			unsigned short ustItemID; //����ԭ��
			unsigned short ustCount;  //����ԭ�ϸ���
		};

		SItemCreateItemRule() :material("[ItemDetail.h]SItemCreateItemRule.material")
		{
			ustTargetItemID = InvalidLogicNumber;
			ustTargetItemID1 = InvalidLogicNumber;
			ustTargetItemID2 = InvalidLogicNumber;
		}
		//�ϳ�Ŀ��
		unsigned short ustTargetItemID;
		unsigned short ustTargetItemID1;
		unsigned short ustTargetItemID2;

		SItemCommon* pItemTarget;
		SItemCommon* pItemTarget1;
		SItemCommon* pItemTarget2;

		int iMaterialNum;
		Array<SMaterial, 4> material; //ԭ��

		//�ϳɳɹ���
		//float fCreateSuccRate;        
		//����1/1000
		int iCreateSuccRate;
		int iCreateSuccRate1;
		int iCreateSuccRate2;

		bool bIntensify;
		int  nNeedMenoy;
		int  nSingTime;
		int  nNeedEnergy;

		unsigned char ucCompoundType; // ��������
	};

	struct SItemCrystal : public SItemCommon
	{
		//unsigned short usCrystalId;
		//ˮ���ȼ�
		unsigned short usCrystalLevel;

	};

	struct SProfession
	{
		SProfession()
		{
			memset(this, 0, sizeof(*this) );
		}
		const char* GetName();
		const char* GetDesc();
		//std::string    szName;
		//std::string    szDesc;
		DWORD    dwNameAddr;
		DWORD    dwDescAddr;
		short    stType;
	};

	enum EMonsterVisualType
	{
		EMVT_Normal,       // �����˿ɼ�
		EMVT_MasterVisual, // ���˿ɼ�
	};

	enum EMonsterRewardType
	{
		EMRT_None,
		EMRT_CashMoney,
		EMRT_Reputation,
		EMRT_MaxSize
	};

	// ��XML�ж�Ӧ���ֶκ���
	/*<!--
	<> �������ֶα�ʾ��Ĭ��ֵ, ������ ������.monster�����е��ֶ�, Щ������

	MonsterID|����id,  MonsterPrefix|ǰ׺,  MonsterName|������, ModelID|ģ��id,  MonsterSound|����, MonsterType|����, BodyModify|������������, BodyLengthSize|���ʹ�С,
	MonsterLv|�ȼ�, MonsterExp|����ֵ, PhyAtk|������, MagicAtk|��������, PhyDef|�������, MagicDef|��������, Critical|������, CriticalIntensity|�����˺�,
	Tenacity|����, BackStrike|�����˺�, BackStrikeResist|��������, BreakStrike|�Ƽ�, BreakResist|�Ƽ׿���, StabStrike|�ᴩ�˺�, StabResist|�ᴩ����,
	ElementStrike|Ԫ���˺�, ElementResist|Ԫ�ؿ���, ToxinStrike|�����˺�, ToxinResist|���ؿ���,  SpiritStrike|�����˺�, SpiritResist|������,
	MaxMP|��ֵ����ֵ, RecoverMP|�����ָ��ٶ�, MaxHP|�������ֵ, RecoverHP|�����ָ��ٶ�, Hit|��ȷֵ(����), Dodge|�����(����), AtkSpeed|�����ٶ�, EyeShot|��Ұ,
	FightShot|ս����Ұ, AttackPhysicsMod|�﹥ϵ��, AttackMagicMod|����ϵ��, DefendPhysicsMod|���ϵ��, DefendMagicMod|����ϵ��, AttackFloatMin|������Сϵ��,
	AttackFloatMax|�������ϵ��, ChaseTime|׷��ʱ��, MoveSpeed|�ƶ��ٶ�, UseSkill1|���ü���1, UseSkill2|���ü���2, UseSkill3|���ü���3, 
	Skill1Lv|����1�ȼ�, Skill2Lv|����2�ȼ�, Skill3Lv|����3�ȼ�, ChanceOfSkill1|����1ʹ�ø���, ChanceOfSkill2|����2ʹ�ø���, ChanceOfSkill3|����3ʹ�ø���, 
	MinDropMoney|�����Ǯ��Сֵ, MaxDropMoney|�����Ǯ���ֵ, DropItemRate|��Ʒ���䱶��, IfInitiative|�Ƿ�������, MonsterSkin|����Ƥ��, MonsterAlpha|����͸����,
	<<ReviveTime|����ʱ��>>, IfDisappear|�Ƿ���ʧ, DisappearTime|��ʧʱ��, DeathScript|Ĭ�������ű�, AIScript|Ĭ��AI�ű�, MonsterWeaponSoundPrefix|����������Чǰ׺,
	MonsterArmorSoundPrefix|���������Чǰ׺, RunStep|���ﱼ�ܲ���, WalkStep|�������߲���, IfHalfLengthMonster|�Ƿ����°������, IfFourFeetMonster|�Ƿ��������,
	MonsterSide|������Ӫ, EnemityRate|��ޱ���, InitialEnemity|��Ұ�������, ResistUnmovable|�����ƶ����ֿ�, ResistUnatkable|���ܹ������ֿ�, ResistUncastable|����ʩ�����ֿ�,
	ResistUnitemusable|�����õ��߱��ֿ�, ExtraSkillExp|���⼼�ܾ���, MaxActArea|�����Χ, ChangePassive|ս���б�Ϊ������, PassiveTime|ս������������������,
	BaseEnmityRange|������ޱ��ַ�Χ, IdleMoveSpeed|�����ƶ��ٶ�, Citymonster|���й�(���ܱ��سǷ�����), Citydefmonster|���з��ع�(ֻ�������ǵ�), MonsterTitle|����ƺ�,
	FrontFoot|ǰ�Ż��ҽ�, BackFoot|��Ż����, NeedQuest|����������, MonsterReputation|��������, MonsterExploit|���ӹ�ѫ, RewardFriendly|�������Ѷ�, Daoxing|����,
	RewardDaoxing|��������, VisualType|��������, IdleMoveRate|���ƿ����ƶ���Ƶ��ֵ(���֮��),  BornProtectTime|��������ʱ��, RestoreSpaceTime|��Ѫ���ʱ��,
	CashMoney|�ɽ��׽�Ǯ, RewardStatusID����״̬ID, RewardMulType|������������, RewardMulValue|��������, IsFindParth|�Ƿ���Ѱ·, IsDynamicBlock|�Ƿ���붯̬�赲,
	CatchPetID|��Ӧ����ID, CatchBaseRate|��׽��������, PetQuality|�����ĳ���Ʒ��, Phyle|����, FiveElements|����, GroupID|������ID
	-->*/
	enum SMonsterDropType
	{
		SMDT_First = 1,
		SMDT_DPS   = 2,
	};

	struct SMonster 
	{ //����
		enum EConstDefine
		{
			MONSTER_SKILL_COUNT = 3,
		};

		int   iMonsterContainerIndex; // ��������
		int   stMonsterId;            // Id   ������ʱ��,110012  ����ֻ����1100 , 12�ǵȼ�,Ҫ������Ӧ��ҵȼ�������
		DWORD dwNameAddr;             // ��������ַ
		DWORD dwNamePrefix;           // ������ǰ׺��ַ
		int   iModelID;               // ģ��ID
		DWORD dwCreatureSoundAddr;    // ����������ַ
		DWORD dwSkinAddr;             // ����Ƥ����ַ
		DWORD dwWeaponSoundAddr;      // ����������Чǰ׺��ַ
		DWORD dwArmourSoundAddr;      // ���������Чǰ׺��ַ
		uint8 stProfession;           // ����ְҵ
		uint8 stMonsterType;          // ��������
		float fBodyLengthSize;        // �������ʹ�С
		float fBodySize;              // ���������������š�ע�⡿
		float fAlpha;                 // ����͸����
		short stLevel;                // ����
		int   nRewardExp;             // ӵ�еľ���ֵ(�����)
		int   nRewardReputation;      // ӵ�е�����ֵ(�����)
		int   nRewardExploit;         // ӵ�еĹ�ѫֵ
		int   nRewardFriendly;        // �������Ѷ�
		int   nRewardDaoxing;         // ��������
		int   nHPMax;                 // ���HP
		short stMPMax;                // ���MP
		short stHPRestore;            // HP�ָ��ٶ�
		short stMPRestore;            // MP�ָ��ٶ�
		short stExact;                // ��ȷ
		short stDodge;                // �ر���
		short stAttackRate;           // �����ٶ�
		float fPhysicAtt;             // �﹥
		float fMagicAtt;              // ����
		float fPhysicDef;             // ���
		float fMagicDef;              // ����

		float  critical             ; // ������
		uint16 criticalIntensity    ; // �����˺�
		uint16 tenacity             ; // ����
		uint16 backStrike           ; // �����˺�
		uint16 backStrikeResist     ; // ��������
		uint16 breakStrike          ; // �Ƽ��˺�
		uint16 stabStrike           ; // �ᴩ�˺�
		uint16 elementStrike        ; // Ԫ���˺�
		uint16 toxinStrike          ; // �����˺�
		uint16 spiritStrike         ; // �����˺�
		uint16 breakResist          ; // �Ƽ׿���
		uint16 stabResist           ; // �ᴩ����
		uint16 elementResist        ; // Ԫ�ؿ���
		uint16 toxinResist          ; // ���ؿ���
		uint16 spiritResist         ; // ������  

		// ����ϵ��
		float fAttackPhysicsMod;
		float fAttackMagicMod;

		// ����ϵ��
		float fDefendPhysicsMod;
		float fDefendMagicMod;

		short nAttackFloatMin ;     // ������Сϵ��
		short nAttackFloatMax ;     // �������ϵ�� 
		short stView;               // ��Ұ
		short stFightView;          // ս����Ұ
		DWORD dwCatchTime;          // ׷��ʱ��
		float fMoveSpeed;           // �ƶ��ٶ�
		float fIdleMoveSpeed;       // ����ʱ�ƶ��ٶ�
		float fMovingStep;          // ���߲���
		float fRunStep;             // �ܲ�����
		Array<uint16,MONSTER_SKILL_COUNT> iSkillID;     // ����ʹ�õļ���
		Array<uint8, MONSTER_SKILL_COUNT> stSkillLevel; // ��ʹ�ü��ܵĵȼ�
		Array<short, MONSTER_SKILL_COUNT> stSkillRate;  // ��ʹ�ü��ܵ�ʹ�ø���
		short  stDropMinMoney;        // �����Ǯ(min)
		short  stDropMaxMoney;        // �����Ǯ(max)
		float  fItemDropMultipleRate; // ��Ʒ���䱶��
		int    nReliveTime;           // ����ʱ��
		DWORD  dwDeadScriptAddr;      // ���������ű���ַ
		DWORD  dwAILuaScriptAddr;     // ����AI�ű���ַ
		int    nIsInitiative;         // �Ƿ�������
		uint32 nRandMoveRange;        // ����������Χ
		int    nIsHaveTwoHalfBody;    // �Ƿ����°������
		int    nIsHaveFourFoot;       // �Ƿ��������
		bool   bIsDisappear;          // �����Ƿ���ʧ
		DWORD  dwDisappearTime;       // ������ʧʱ��
		int    nEnmityRate;           // ��ޱ���
		int    nEnmity;               // ���
		int    nDaoxing;              // ����
		int    nResistMove;           // �ֿ�1
		int    nResistAtt;            // �ֿ�2
		int    nResistMagic;          // �ֿ�3
		int    nResistTools;          // �ֿ�4
		int    nSuperfluitySkillExp;  // ���⼼�ܾ���   ��ע:�ֶθ��� �������Ϊ�ɼ��� ���ֶ�Ϊ�۳�����ֵ
		int    nMaxRange;             // �����Χ
		int    nChangePassive;        // ս��ʱ�Ƿ��Ϊ������
		int    nPassiveTime;          // ��������ʱ��
		int    nBaseEnmityRange;      // ������ޱ�������
		int    nMonsterSide;          // ������Ӫ
		bool   bIsCityMonster;        // �Ƿ���й���
		bool   bIsCityDefMonster;     // �Ƿ���س��й���
		DWORD  strTitleAddress;       // �ƺ�
		DWORD  dwFrontFootPrintAddr;  // ǰ�Ż��ҽ�
		DWORD  dwBackFootPrintAddr;   // ��Ż����
		int    nRelativeQuest;        // ����������
		uint8  visualType;            // ��������
		uint16 nIdleMoveRate;         // ���ƿ����ƶ���Ƶ��ֵ ���֮һ
		DWORD  dwBornProtectTime;     // ��������ʱ��
		DWORD  dwRestoreSpaceTime;    // ��Ѫ���ʱ��

		//�������״̬����ֶ�
		uint16 nCashMoney;           // �ɽ��׽�Ǯ
		uint16 nRewardStatusID;      // ����״̬ID ������� ID 3173
		uint16 nRewardMulType ;      // ������������
		uint16 nRewardMulValue;      // ��������

		// Ѱ·�������
		bool	blIsFindParth;		// �Ƿ���Ѱ·
		bool	blIsDynamicBlock;	// �Ƿ���붯̬�赲

		// �������
		int     nCatchPetID;         // ��Ӧ����ID
		int16   nCatchBaseRate;      // ��׽�������� ���֮һ
		int8    nPetQuality;         // �����ĳ���Ʒ��    
		uint8   phyle  ;             // ����
		uint8   element;             // ����

		uint16	nGroupID;			// ������ID

		uint16  nDropType;			// ��������

		const char* GetName();
		const char* GetNamePrefix();
		const char* GetCreatureSound();
		const char* GetSkin();
		const char* GetDeadScript();
		const char* GetAILuaScript();
		const char* GetWeaponSound();
		const char* GetArmourSound();
		const char* GetFrontFootPrintPath(); // ǰ��ӡ
		const char* GetBackFootPrintPath();  // ���ӡ
		const char* GetTitle();

		SMonster() : iSkillID("[ItemDetail.h]SMonster.iSkillID"), stSkillLevel("[ItemDetail.h]SMonster.stSkillLevel"), stSkillRate("[ItemDetail.h]SMonster.stSkillRate")
		{ memset(this, 0, sizeof(*this) ); }
	};

	struct SPetMonster : public SMonster
	{
		enum EPetMonsterDefine
		{
			EPet_LvRealizeCount       = 10,
			EPet_RandSkillCount       = 10, // ���������
			EPet_ManualSkillCount     = 2 , // ����������
			EPet_AutoSkillCount       = 4 , // ����������
			EPet_BabyListIDCount      = 5 , // ���ﷱֳ��һ��ID
			EPet_DropItemIDCount      = 10,
		};

		SPetMonster()
		{ memset(this, 0, sizeof(*this)); }

		int            iPetContainerIndex;           // ��������
		int            itemId ;                      // ��Ӧ��ƷID
		DWORD          dwPetDescAddr;                // �������ַ
		DWORD          dwPetBornDescAddr;            // �����û�ص�
		DWORD          dwNameColor;                  // ����������ɫ
		int            petType;                      // ��������
		DWORD          dwPetTypeNameAddr;            // ������������
		unsigned char  catchQuality;                 // ��׽Ʒ�� ����ͭ
		unsigned char  catchLevel;                   // ��׽�ȼ�
		unsigned char  takeLevel;                    // Я���ȼ�
		int            babyId;                       // ����ID
		unsigned char  aberranceLevel;               // ����ȼ�
		bool           bIsAberrance;                 // �Ƿ�Ϊ�������
		bool           bIsBaby;                      // �Ƿ񱦱�
		unsigned char  food;                         // ʳ��
		int            duration;                     // ����
		unsigned char  attackType;                   // ��������
		int            regenerateTime;               // ��������ʱ��
		DWORD		   identifyTotal;				 // ���������ۼ�

		int            growthRate  [EPetGrowth_Count];      // �ɳ���
		int            aptitudeAttr[EBaseAttr_MaxSize];     // ��ʼ��������

		unsigned char  characterizeRate[EPetChar_Count];    // �Ը�

		unsigned char  skillNumControl;     // ���ܿ�����
		unsigned short talentSkillId;       // �츳����
		unsigned char  lvRealizeSkill   [EPet_LvRealizeCount];  // �ȼ�������
		unsigned short manualSkillId    [EPet_RandSkillCount];  // ������������ID
		unsigned short manualSkillRate  [EPet_RandSkillCount];  // �����������ܼ���
		unsigned short autoSkillId      [EPet_RandSkillCount];  // ���򱻶�����ID
		unsigned short autoSkillRate    [EPet_RandSkillCount];  // ���򱻶����ܼ���

		int            babyListId       [EPet_BabyListIDCount];
		int            babyListIdRate   [EPet_BabyListIDCount];

		unsigned short dropItemIds      [EPet_DropItemIDCount];

		const char* GetPetDesc();
		const char* GetPetBornDesc();
		const char* GetPetTypeName();

	};

	struct STraffic
	{
		STraffic()
		{
			memset(this, 0, sizeof(*this));
			nextTrafficId = -1;
		}

		const char* GetName(); // ����

		int   nID          ; // ID���
		DWORD dwNameAddr   ; // ���Ƶ�ַ
		int   nDromeID     ; // ������
		int   nMapID       ; // ��ͼID
		int   nRouteID     ; // ·��ID
		int32 nextTrafficId; // ��һ��Traffic
	};

	enum EMountQuality
	{
		EMQ_Ordinary    =   1,  //��ͨ��
		EMQ_Good        =   2,  //������
		EMQ_Excellent   =   3,  //��Ʒ��
		EMQ_Variation   =   4,  //������
	};

	//����
	struct SDrome
	{
		enum EConstDefine
		{
			DCD_SELFSKILLIDCOUNT    = 10,
			DCD_MASTERSKILLIDCOUNT  = 10,
			DCD_MASTERUSESKILLCOUNT = 10,
		};

		SDrome()
		{
			memset(this, 0, sizeof(*this));
		}
		const char* GetName();                    // ����
		const char* GetModelPath();               // ģ���ļ�·��
		const char* GetSkinName();                // ��ȡƤ������
		const char* GetMountEffectPath();         // ���������Ч·��
		const char* GetDisMountEffectPath();      // ���������Ч·��
		const char* GetRunSoundOfLeftFootPath();  // ��ŽŲ���
		const char* GetRunSoundOfRightFootPath(); // �ҽŽŲ���
		const char* GetNeightSoundPath();         // ԭ�ؽ���
		const char* GetFrontFootPrintPath();      // ǰ��ӡ
		const char* GetBackFootPrintPath();       // ���ӡ
		int         GetMountCameraHeight() { return nCameraHeight; } // ���̧�߸߶�
		const char* GetMountAction( int Index );  // ���ֶ�����
		const char* GetHeadPicPath();             // ͷ��·��

		short stId;                      // Id���
		short stIndex;                   // ����
		DWORD dwNameAddr;                // ���Ƶ�ַ
		DWORD dwModelAddr;               // ģ���ļ���ַ
		DWORD dwSkinAddr;                // Ƥ����ַ
		DWORD dwMountEffectAddr;         // ���������Ч·��
		DWORD dwDisMountEffectAddr;      // ���������Ч·��
		DWORD dwRunSoundOfLeftFootAddr;  // ��ŽŲ���
		DWORD dwRunSoundOfRightFootAddr; // �ҽŽŲ���
		DWORD dwNeightSoundAddr;         // ԭ�ؽ���
		DWORD dwFrontFootPrintAddr;      // ǰ��ӡ
		DWORD dwBackFootPrintAddr;       // ���ӡ
		Array<DWORD, MountMaxActionNum>  dwMountAction;

		int   nAddStatusID;              // ���ӵ�״̬ID
		short stOperaType;               // ��������
		short stType;                    // ����
		short stCarry;                   // ��������
		short shMoveType;                // �ƶ�����
		float fFlyHeight;                // ���и߶�
		float fInertia;                  // ����
		float fSpeed;                    // �ٶ�
		float fRunningStep;              // Run�Ĳ���
		float fWalkingStep;              // Walk�Ĳ���
		float fJumpingHeight;            // ��Ծ�߶�
		short stMaxRange;                // �����Χ
		float fDromeScaleCorrect;        // ������������
		float fRiderScaleCorrect;        // ������������
		//float fAccelerate;             // ���ٶ�
		//DWORD dwFireTime;              // ���ٳ���ʱ��
		DWORD dwMaxLifeTime;             // ���ʹ��ʱ��
		DWORD dwJumpAnimTime;            // ��Ծ��������ʱ��
		DWORD dwDropAnimTime;            // ���䶯������ʱ��
		DWORD dwFallToTheGroundRunTime;  // �����ܶ�������ʱ��
		float fJumpSpeed;                // �����ٶ�
		float fDropSpeed;                // �����ٶ�
		DWORD dwBlendJumpTime;           // ��������ʱ��
		int   nCameraHeight;             // ���̧�߸߶�
		DWORD dwHeadPicAddr;             // ͷ���ַ

		unsigned char  takeLevel;            // Я���ȼ�
		unsigned char  quality;              // ��ʼƷ��
		float          growMin;              // �ɳ�����Сֵ
		float          growMax;              // �ɳ������ֵ
		float          baseSum;              // ��ʼ���������ܺ�
		float          baseMin[EBaseAttr_MaxSize]; // ��ʼ����5��������Сֵ
		float          baseMax[EBaseAttr_MaxSize]; // ��ʼ����5���������ֵ
		float          addSum;               // ��ʼ���������ܺ�
		float          addMin[EBaseAttr_MaxSize];  // ��ʼ����5��������Сֵ
		float          addMax[EBaseAttr_MaxSize];  // ��ʼ����5���������ֵ
		unsigned short sawyMin;              // ������Сֵ
		unsigned short sawyMax;              // �������ֵ
		unsigned short selfSpeedSkillId;     // �����ٶȼ���
		unsigned char  selfSkillNum;         // �����ܸ���
		unsigned char  selfSkillRate;        // �����⼸�����ܵĸ���
		unsigned short selfSkillId[DCD_SELFSKILLIDCOUNT];         // ������������＼��
		unsigned char  masterSkillNum;                            // ���˱����������ܸ���
		unsigned char  masterSkillRate;                           // �����⼸�����ܵĸ���
		unsigned short masterSkillId[DCD_MASTERSKILLIDCOUNT];     // ����������������˱�����������
		unsigned char  masterUseSkillNum;                         // ���������������ܸ���
		unsigned char  masterUseSkillRate;                        // �����⼸�����ܵĸ���
		unsigned short masterUseSKillId[DCD_MASTERUSESKILLCOUNT]; // �����������������������������
		Array< unsigned short, 4 > arrayProbability;              // ϴ���4��Ʒ�ʵĸ���
		Array< unsigned short, 4 > arrayMountID;                  // ϴ���Ӧ�õ�������µ�id

		uint16         nextGeneration;      //��һ������
		uint16		   modelID[SMountItem::MICD_MountMaxLevel + 1];	   //ģ��ID
	};

	struct SUpBaseAttr
	{
		SUpBaseAttr() : Str("[ItemDetail.h]SUpBaseAttr.Str"),
			Agi("[ItemDetail.h]SUpBaseAttr.Agi"),
			Con("[ItemDetail.h]SUpBaseAttr.Con"),
			Mag("[ItemDetail.h]SUpBaseAttr.Mag"),
			Int("[ItemDetail.h]SUpBaseAttr.Int"),
			Charm("[ItemDetail.h]SUpBaseAttr.Charm")
		{
			memset(this, 0, sizeof(*this) );
		}
		short sLevel;        
		Array<short, EArmType_MaxSize>    Str;
		Array<short, EArmType_MaxSize>    Agi;
		Array<short, EArmType_MaxSize>    Con;
		Array<short, EArmType_MaxSize>    Mag;
		Array<short, EArmType_MaxSize>    Int;
		Array<short, EArmType_MaxSize>    Charm;
		short stSkillPoint;
	};

	struct TagEquipRequest
	{
		bool    bSex;
		bool    bProfession;
		bool    bLevel;
		bool    bStr; // ����        
		bool    bCons;// ����        
		bool    bAgi; // ����
		bool    bInt; // ����
		bool    bMag; // ħ��        
		bool    bCha; // ����
	};

	struct SRandAttribute
	{
		enum EConstDefine
		{
			CD_TypeCount  = 2,
			CD_ValueCount = 2,
		};

		SRandAttribute()
		{
			memset(this, 0, sizeof(*this) );
		}

		unsigned short id;
		short          level;        
		unsigned short type[CD_TypeCount];
		CustomValue    value[CD_ValueCount];
	};

	struct SEquipQualityIntensity
	{
		SEquipQualityIntensity()
		{
			ZeroMemory( this, sizeof(*this) );
		}

		uint8	nQuality;
		uint32	nColor;
		uint16	nIntensity;
	};

	enum eBulk
	{
		eBulk_Small = 0,
		eBulk_Normal,
		eBulk_Big
	};

	struct SItemNew
	{
		SItemNew()
		{
			memset(this, 0, sizeof(*this) );
		}
		float fHitMod;
		short stModelID;
		//DWORD dwIconFileName;
		//char cIconFileName[MAX_PATH];
		short stAttSpeed;
		float fAttRange;
		int nCost;
		short stIconId;
	};

	struct SCreatItemMod
	{
		SCreatItemMod()
		{
			memset(this, 0, sizeof(*this) );
		}

		unsigned short ustLevel;
		bool  bIsWeapon;
		bool  bIsArmour;
		short stItemType;
		short stItemSize;    
		std::vector <SItemNew*> vtItemNew;
	};

	struct sIcon
	{
		short stIconId;
		char sIconFile[MAX_PATH];
		//Array<char, MAX_PATH>    sIconFile;
	};

	struct ReputeStruct
	{
		int        usReputeID;
		std::string szReputeName;
		std::string szReputeExp;
		//����һ������
		Array< short, EBaseAttr_MaxSize>    stReputeBattr;
		int        usReputeFlag;
		bool    bInUsing;
	};

	enum ECreatureSound
	{
		CreatureSound_Idle    = 0 ,
		CreatureSound_Attack    ,
		CreatureSound_BeHit     ,
		CreatureSound_Dead      ,
		CreatureSound_Max
	};

	struct SCreatureSound
	{
		const char* GetName();
		DWORD dwCreatureNameAddr;
		Array< int, CreatureSound_Max > SoundNum;
	};

	//added by junyi.chen begin
	struct RandAttr
	{
		unsigned short	usID;
		unsigned short	usType;
	};


	//////////////////////////////////////////////////////////////////////////

	static char* (g_szWeaponType[]) = 
	{
		"Combat"  , // ͽ��
		"Warrior" , // սʿ
		"Mage"    , // ��ʦ
		"Taoist"  , // ��ʿ
		"Assassin", // �̿�
		"Hunter"  , // ����
		"Sniper"  , // ��ǹ
		"Shield"  , // ����
		"Flag"    , // ����
	};

	static char* (g_szItemType[]) =
	{
		"restore"       ,
		"weapon"        ,
		"armour"        ,
		"skill"         ,
		"status"        ,
		"action"        ,
		"material"      ,
		"gem"           ,
		"createitemrule",
		"task"          ,
		"other"         ,
		"reel"          ,
		"treasurebox"   ,
		"checkup"       ,
		"realaward"     ,
		"guilditem"     ,
		"special"       ,
		"talisman"		,
		"petequip"		,
	};

	// ��λ
	static char *(g_szCanEquip[])=
	{
		"Helmet"            , // ͷ��
		"Armour"            , // ����
		"Glove"             , // ����
		"Shoe"              , // Ь��
		"Weapon"            , // ������
		"WeaponMinor"       , // ������
		"Badge"             , // ����
		"Ring1"             , // ��ָ1
		"Ring2"             , // ��ָ2
		"Bangle1"           , // ����1
		"Bangle2"           , // ����2
		//    "Manteau"           , // ����
		"Shoulder"          , // ���
		"Necklace"          , // ����
		"Sash"              , // ����
		"LeaderCard"        , // ���ſ�
		"Amulet"            , // �����
		"AecorativeGoods"   , // װ�ε���Ʒ
		"AecorativeClothing", // װ�ε��·�
		"Trousers"			, // ����
	};

	static char*(g_szTargetString[])=
	{
		"target_no"          , // ��Ŀ��
		"target_myself"      , // �� ��ֻ���Լ���
		"target_friend"      , // ���ѣ�ֻ�Զ��ѣ�    
		"target_normalplayer", // ��ͨ��ң�������Ұ����Լ����˵��ˣ�
		"target_enemy"       , // ���ˣ�ֻ�ܶԵ��ˣ�
		"target_dead"        , // ����Ŀ�ֻ꣨�����ˣ�
		"target_herb"        , // Ŀ���ҩ
		"target_mine"        , // Ŀ���
		"target_wood"        , // Ŀ��ľͷ
		"target_treasure"    , // Ŀ�걦��
		"target_pet"         , // Ŀ��PET
		"target_all"         , // �����˶�����
		"target_team"        , // ����Ŀ��
		"target_mount"       , // Ŀ������
		"target_insect"      , // Ŀ������
		"target_guild"       , // ����
		"target_campforce"   , // ͬ��Ӫ����
	};

	static char*(g_szPassiveSkillTargetString[])=
	{
		"PassiveSkillTarget_Self"            , // �����Լ��ı�������
		"PassiveSkillTarget_AllPet"          , // �������г���ļ���
		"PassiveSkillTarget_TargetPet"       , // ����Ŀ�����ļ���
		"PassiveSkillTarget_SelfAndAllPet"   , // �����Լ������г���ļ���
		"PassiveSkillTarget_SelfAndTargetPet", // �����Լ���Ŀ�����ļ���
	};

	static char*(g_szMoveTypeString[])=
	{
		"movetype_twofooted" , // ˫���ƶ�
		"movetype_fourfooted", // �����ƶ�
		"movetype_fly"       , // �����ƶ�
		"movetype_reptile"   , // �����ƶ�
		"movetype_drive"     , // ��ʻ�ƶ�
		"movetype_twowheel"  , // �����ƶ�
		"movetype_fourwheel" , // �����ƶ�
	};

	static char*(g_szEffectCenter[])=
	{
		"center_no"        , // û�г�����Ч��
		"center_metotarget", // ���Լ�������
		"center_me"        , // ���Լ���ǰλ��Ϊ����
		"center_target"    , // ��Ŀ��λ��Ϊ����
	};

	static char*(g_szEquipType[])=
	{
		"Helmet"            , // ͷ��
		"Armour"            , // ����
		"Glove"             , // ����
		"Shoe"              , // Ь��
		"Weapon"            , // ������
		"WeaponMinor"       , // ������
		"Badge"             , // ����
		"Ring"              , // ��ָ
		"Bangle"            , // ����
		//    "Manteau"           , // ����
		"Shoulder"          , // ���
		"Necklace"          , // ����
		"Sash"              , // ����
		"LeaderCard"        , // ���ſ�
		"Amulet"            , // �����
		"AecorativeGoods"   , // װ�ε���Ʒ
		"AecorativeClothing", // װ�ε��·�
		"Trousers"			, // ����
	};

	static char* (g_szSkillType[])=
	{
		"skilltype_action",    // �ڶ������Ž��������ģ�����
		"skilltype_magic_hit", // �ڶ������Ž�������㣬�ͷų�һ���������
		"skilltype_magic_npc", // �ڶ������Ž������ͷų�һ������npc
		"skilltype_passive"    // ��������
	};

	static char* (g_szCastType[])=
	{
		"casttype_singletarget",             // ��һĿ��
		"casttype_singletargetcircleAOE",    // ��һĿ��Բ�η�Χ
		"casttype_AOEPointCircleArea",       // Ŀ��ص��Բ�η�Χ
		"casttype_AOEcircleself",            // ���Լ�Ϊ���ĵ�Բ�η�Χ����
		"casttype_AOEquartercirlcefrontage", // ����90�ȵ����ͷ�Χ����
		"casttype_AOEhalfcirclefrontage",    // ����180�ȵİ�Բ��Χ����
		"casttype_AOEquartercirlcebackage",  // ����90�ȵ����ͷ�Χ����
		"casttype_AOEhalfcirclebackage",     // ����180�ȵİ�Բ��Χ����
		"casttype_AOETargetcirclearea",      // ��ѡ������Ϊ���ĵ�Բ�η�Χ����
	};

	static char* (g_szSkillGeneralType[])=
	{
		"generaltype_action",   // ����Action����
		"generaltype_magic",    // ����Magic����
		"generaltype_sequence", // �������м���
		"generaltype_passive",  // ��������
		"generaltype_trigger",  // ���ڱ�����������
	};

	static char* (g_szMonsterType[])=
	{
		"monstertype_normal",
		"monstertype_leader",
		"monstertype_boss",
		"monstertype_god",
		"monstertype_illusion",
		"monstertype_trap",
		"monstertype_herb",
		"monstertype_mine",
		"monstertype_wood",
		"monstertype_treasure",
		"monstertype_building",
		"monstertype_mount",
		"monstertype_pet",
		"monstertype_collision",
		"monstertype_insect",
		"monstertype_protect",
		"monstertype_pickup",
	};

	static char* (g_szStatusAnimType[])=
	{
		"AnimType_None",
		"AnimType_Stun",
		"AnimType_FallOver",
		"AnimType_Freeze",
	};

	static char* (g_szBalanceType[])=
	{
		"balancetype_none"                  , // û���κν���
		"balancetype_damagephysicaldefend"  , // ��������˺�����
		"balancetype_damagemagicdefend"     , // ��ħ�������˺�����
		"balancetype_damagebothdefend"      , // �����ħ�����˺�����
		"balancetype_restorehpmp"           , // ��HP MP����
		"balancetype_relive"                , // �������
	};

	//״̬�Ľ��㹫ʽ����
	static char* (g_szStatusBalanceType[])=
	{
		"balance_status_type_none"          ,
		"balance_status_type_restore"       , // �ظ�����
		"balance_status_type_timeexp"       , // ʱ�侭��
		"balance_status_type_mount"         , // ���ﱻ������
	};

	//��������
	static char* (g_szActionType[])=
	{
		"baseaction"        ,
		"communityaction"   ,
		"socialaction"      ,
	};

	//�Ա�
	static char* (g_szSexType[])=
	{
		"male",
		"female",
	};

	//ְҵ
	static char* (g_szProfessionType[])=
	{
		"Warrior" , // սʿ
		"Mage"    , // ��ʦ
		"Taoist"  , // ��ʿ
		"Assassin", // �̿�
		"Hunter"  , // ����
		"Sniper"  , // ��ǹ
	};

	//ʩ��Ŀ�꣬�ͻ���
	//����Ƕ��Լ�ʹ�ã���ô����Ҫ���ָ�򹥻�Ŀ�ֱ꣬��ȡ��ɫ��ǰλ��
	//�������Ҫ����ʹ�ã���ô����Ŀ������ǽ�ɫ
	//�����λ��ʹ�ã���ô����Ŀ��Ϊλ�ã����ָ���ɫ��ȡ��ɫλ�ã�
	static char* (g_szSkillCastTarget[])=
	{
		"casttarget_me"            // �Լ�
		,"casttarget_friendlive"   // ͬ��
		,"casttarget_enemylive"    // ����
		,"casttarget_live"         // ���л��ŵĶ���
		,"casttarget_pos"          // ����
		,"casttarget_friendcorpse" // ͬ���ʬ��
		,"casttarget_enemycorpse"  // ���˵�ʬ��
		,"casttarget_corpse"       // ʬ��
		,"casttarget_herb"         // �Բ�ҩΪĿ��
		,"casttarget_mine"         // �Կ�ΪĿ��
		,"casttarget_wood"         // ��ľͷΪĿ��
		,"casttarget_treasure"     // �Ա���ΪĿ��
		,"casttarget_pet"          // PETĿ��
		,"casttarget_team"         // ����ΪĿ��
		,"casttarget_mount"        // ����ΪĿ��
		,"casttarget_insect"       // ����ΪĿ��
		,"casttarget_guild"        // �����Ա
		,"casttarget_campforce"    // ͬ��Ӫ����
	};

	//��������
	static char* (g_szWeaponElement[])=
	{    
		"physic"    ,
		"magic"     ,
		"forst"     ,
		"blaze"     ,
		"thunder"   ,
		"wind"      ,
		"all"
	};

	static char str_action[][32] = 
	{
		"idle"          ,//(����)   

		"idle1"         ,//(����)   new
		"idle2"         ,//(����)   new
		"specialidle"   ,//(�������)
		"attack_idle"   ,//(ս������)new
		"hurt"          ,//(����)	new
		"run"           ,//(����)
		"walk"          ,//(����)
		"stun"          ,

		"sit"           ,//(����)    
		"stup"          ,//(վ��)
		"dead",		//(ԭ�ص���)
		"dead1",	//(���w�˄�)  
		"pick",		//��ҩnew
		"hack",		//����new
		"dig",		//�ɿ�new
		"recital",	//����new
		"fire",		//ʦ�� new
		"defend",	//����new
		"sway",

		"attack1",//��ͨ����
		"attack2",//��ͨ����
		"attack3",//��ͨ����

		"walk_attack",
		"run_attack",

		//˫������		
		"double_attack_idle",// ս������
		"double_attack2",    //��ͨ����2   897    934  (912
		//��ͨ����3           941    988  (954
		//��ͨ����4           1003   1047 (1023
		"double_defend",	//����                1159   1174
		"double_recital",	//��������            1185   1215
		"double_recital1",	//��������            1185   1215
		"double_recital2",	//��������            1185   1215
		"double_recital3",	//��������            1185   1215
		"double_recital4",	//��������            1185   1215
		"double_recital5",	//��������            1185   1215
		"double_recital6",	//��������            1185   1215
		"double_fire",		//����ʦ��            1217   1256
		"double_hurt",		//����                1261   1275
		"double_dead",		//����                1282   1333
		"double_attack1",	//��ͨ����1    1337   1366  (1350
		"double_scabbard",	//������          1383   1426
		"double_draw",		//�γ�����         1433   1446
		"double_run",		//��˫�������ܲ�

		//��������
		"single_attack_idle",		//ս������       35      67
		"single_idle"	,			//��ս������		75     132
		//		walk,				//��·              135     167
		//		run,				//�ܲ�              180     199
		"single_attackr1",		//������ͨ����1     208     229  (218  
		"single_attackl1",		//������ͨ����2       238     260  (249  
		"single_attackr2",		//������ͨ����3       273     295 ��283
		"single_attackl2",		//������ͨ����4       304     326 ��313
		//�����ػ�            334     360 ��344
		//����                366     382 ��371
		"single_recital",			//��������            386     415
		"single_recital1",			//��������            386     415
		"single_recital2",			//��������            386     415
		"single_recital3",			//��������            386     415
		"single_recital4",			//��������            386     415
		"single_recital5",			//��������            386     415
		"single_recital6",			//��������            386     415
		"single_fire",			//����ʦ��            417     454
		"single_hurt",			//����                456     470
		"single_dead",			//����                475     520       
		"jump",			//����                604     618
		"drop",			//���                619     635
		"glide",			//ͣ��                647     666
		"falltothegroundrun",//�����                674     703
		"single_double_draw",		//˫�ְγ�����             741     754
		"single_double_scabbard",	//˫����������             710     740
		"single_draw",				//������������             760     790 
		"single_scabbard",			//���ְγ�����             791     804
		"single_walk_attackr1",		//�������ֹ���            2141     2172  (2154
		"single_walk_attackl1",		//�������ֹ���            2176     2207 ��2185
		"single_run",				//�õ��������ܲ�
		"single_run_attackr1",		//�ܲ����ֹ���            2212     2231 ��2221
		"single_run_attackl1",		//�ܲ����ֹ���            2233     2252 ��2243 
		"run_fire",					//�ܲ�ʩ��                2275     2294 ��2263
		"walk_fire",				//����ʩ��                2298     2329

		//���⶯��
		"strike",					//���              2341     2378 ��2359��2367
		"sting",					//�̼�               2401     2423 ��2409
		"brisance",					//����            2431     2455 ��2443
		"frenzy",					//��              2461     2485

		"single_run_scabbard",		// �ܲ��аγ�����
		"single_run_draw",			// �ܲ�����������
		"single_flag_run",          // ����run
		"single_flag_idle",          // ����idle
		"neigh",
		"shuffleleft",
		"shuffleright",
		"backattack",
		"single_yanwu",
		"mountattackidle",
		"mountattack_run",
		"single_mountattackidle",
		"single_mountattack_run",
		"single_mountscabbard",
		"single_mountdraw",
		"single_walk",
		"single_walkbackwards",
		"yongbao"
	};	

};

//////////////////////////////////////////////////////////////////////////

#endif // __COMMON_ITEMDEFINE_H__
