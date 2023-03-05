#ifndef __LogServerMessageDefine_H__
#define __LogServerMessageDefine_H__

#pragma once

#include "MsgBase.h"

#pragma pack( push, 1 )

enum ELogMessageDefine
{
	LOGMSG_BEGIN_TEST         = 1,//��ʼ��Э������.Ҳ��Ϊ����Э��ʹ��
	LOGMSG_SynServerid,			//ͬ��serverid
	LOGMSG_OnlineInfo,			//������Ϣ
	LOGMSG_INOUNTINFO,			//player������log
	LOGMSG_ITEMGAIN,			//�����Ʒlog
	LOGMSG_ITEMTRADE,			//��Ʒ����(��ͨ)log
	LOGMSG_ITEMCONSUME,			//������Ʒ
	LOGMSG_ITEMUPGRADE,			//������Ʒ����

	LOGMSG_QUESTLOG,			//������־
	LOGMSG_CURRENCY,			//������ͨ��־
	LOGMSG_EXPLOG,				//����ı�log
	LOGMSG_LEVCHANGE,			//�ȼ��ı�

	LOGMSG_MAILLOG,				//�ʼ���־

	LOGMSG_GUILDLOG,			//������־
	LOGMSG_GUILDDETAIL,			//����������־

	LOGMSG_GMCOMMAND,			//����GM����
	LOGMSG_CHATINFO,            //����

	LOGMSG_max
};

struct TestLogMessage:public Msg
{
	TestLogMessage()
	{
		header.dwType = LOGMSG_BEGIN_TEST;
		header.stLength = sizeof(TestLogMessage);
		memset(frondose,0,sizeof(char)*128);
	}
	uint32     account_id;
	uint32	   character_id;
	SYSTEMTIME _time;
	char	   frondose[128];
};

struct S2LSynServerid:public Msg
{
	S2LSynServerid()
	{
		header.dwType = LOGMSG_SynServerid;
		header.stLength = sizeof(S2LSynServerid);
		serverid = -1;
	}
	int serverid;
};

struct CS2LOnlineInfo:public Msg
{
	CS2LOnlineInfo()
	{
		header.dwType = LOGMSG_OnlineInfo;
		header.stLength = sizeof(CS2LOnlineInfo);
		memset(frondose,0,sizeof(char)*512);
	}
	uint16 login;
	uint16 normalquit;
	uint16 kickquit;
	uint16 total;
	char   frondose[512];
	SYSTEMTIME _time;
};

struct LogPlayerInfo
{

	LogPlayerInfo()
	{
         memset(chName,0,sizeof(chName));
	}
	uint32     account_id;
	uint32	   character_id;
	char	   chName[20];
	SYSTEMTIME _time;
};

struct LogItemInfo
{

	LogItemInfo()
	{
       memset(ItemName,0,sizeof(ItemName));
	}

	uint16			item_id;
	__int64			item_guid;
	uint16			item_count;
	
	char	        ItemName[20];
};

enum ePlayerLogInfo
{
	ePlayerLogInfo_login = 1,	//��ɫ������Ϸ V
	ePlayerLogInfo_logout = 0,  //��ɫ�뿪��Ϸ V

	ePlayerExp_Kill		= 0,	//ɱ�ֻ�þ��� VV
	ePlayerExp_Script	= 1,	//�ű������������ VVV
	ePlayerExp_TransSkill = 2,	//ѧϰ�������ľ��� V
	
	ePlayerCurrency_Add = 0,	//���ӽ�Ǯ V
	ePlayerCurrency_Sub = 1,	//���ٽ�Ǯ V

	ePlayerMoneyType_BMoney = 0,	//���� V
	ePlayerMoneyType_Money = 1,		//���� V
	ePlayerMoneyType_BGold = 2,		//��� V
	ePlayerMoneyType_Gold = 3,		//Ԫ��  V

	ePlayerMoneyType_Jifen= 4,		//�̳ǻ���
	ePlayerMoneyType_Rongyu = 5,	//����
    ePlayerMoneyType_ShengWang = 6,  //����
    ePlayerMoneyType_GongXun = 7,   //��ѫ

	ePlayerMoneySourceType_Unkown					= -1, // λ��
	ePlayerMoneySourceType_Bargain					= 0, // ����
	ePlayerMoneySourceType_ReliveTypeOrigin			= 1,//ԭ�ظ���
	ePlayerMoneySourceType_ReliveTypeOriginFullHpMP = 2,//��������
	ePlayerMoneySourceType_UseReelItemToPet			= 3,//ʹ����Ʒ����ѧϰ����
	ePlayerMoneySourceType_KillMonsterSpecialReward = 4,//ɱ����������⽱��
	ePlayerMoneySourceType_ChangeCountry			= 5,//�ı����
	ePlayerMoneySourceType_GMAddmoney				= 6,//GM AddMoney����
	ePlayerMoneySourceType_NPCShop					= 7,//ϵͳ�̵�
	ePlayerMoneySourceType_Storage					= 8,//�ֿ�
	ePlayerMoneySourceType_BuyBack					= 9,//�ع�
	ePlayerMoneySourceType_PetSavvyUp				= 10,//������������
	ePlayerMoneySourceType_PetBreedConfirm			= 11,//���ﷱֳ
	ePlayerMoneySourceType_PetBreedAcquire			= 12,//��ȡ��ֳ����
	ePlayerMoneySourceType_BianShen					= 13,//��������
	ePlayerMoneySourceType_DoneQuest				= 14,//�������
	ePlayerMoneySourceType_Consignment				= 15,//����
	ePlayerMoneySourceType_CountryRaise				= 16,//����ļ��
	ePlayerMoneySourceType_ItemReclaim				= 17,//װ������
	ePlayerMoneySourceType_CreateFamily				= 18,//��������
	ePlayerMoneySourceType_FamilyDonate				= 19,//�������
	ePlayerMoneySourceType_GuildDelate				= 20,//���ᵯ��
	ePlayerMoneySourceType_CreateGuild				= 21,//��������
	ePlayerMoneySourceType_ChangeGuildAim			= 22,//�ı乤������
	ePlayerMoneySourceType_Luck						= 23,//���˴���
	ePlayerMoneySourceType_SendMail					= 24,//����
	ePlayerMoneySourceType_MailCache				= 25,//�ʼ�����
	ePlayerMoneySourceType_Scprit					= 26,//�ű�����
	ePlayerMoneySourceType_StallRevenue				= 27,//��̯ռ��˰
	ePlayerMoneySourceType_StallSetmeal				= 28,//��̯�ײ�
	ePlayerMoneySourceType_Stall					= 29,//�����̵�
	ePlayerMoneySourceType_BuffAdd					= 30,//״̬��������
	ePlayerMoneySourceType_OfflineHookExp			= 31,//���߹һ���þ���
	ePlayerMoneySourceType_UpSkill					= 32,//���������ķ�
	ePlayerMoneySourceType_MoveStarLevelUp			= 33,//����ת��ʯ
	ePlayerMoneySourceType_SuitElementCheck			= 34,//��װ����
	ePlayerMoneySourceType_RepairItem				= 35,//����
	ePlayerMoneySourceType_MountStreng				= 36,//����ǿ��
	ePlayerMoneySourceType_LearnSkill				= 37,//ѧϰ�����ķ�
	ePlayerMoneySourceType_ItemCompose				= 38,//�ϳ���Ʒ
	ePlayerMoneySourceType_ComposeGem				= 39,//�ϳɱ�ʯ
	ePlayerMoneySourceType_ComposeZhujiang			= 40,//�����ϳ�
	ePlayerMoneySourceType_Intensify				= 41,//����ǿ��
	ePlayerMoneySourceType_Identify					= 42,//�������ﷱ��
	ePlayerMoneySourceType_MountBreed				= 43,//���ﷱ��
	ePlayerMoneySourceType_RestoreMountHP			= 44,//�ظ���������
	ePlayerMoneySourceType_SuitElementMove			= 45,//��װ���Դ���
	ePlayerMoneySourceType_ElementSuitChange		= 46,//��װ�漴ת������
	ePlayerMoneySourceType_SkillSuitChange			= 47,//��װ���ܸı� 
	ePlayerMoneySourceType_ElementSuitLevelUp		= 48,//��װ��������
	ePlayerMoneySourceType_SkillSuitLevelUp			= 49,//��װ�������� 
	ePlayerMoneySourceType_EquipAmuletAbsorb		= 50,//���������
	ePlayerMoneySourceType_EquipCharmAbsorb			= 51,//�������� 
	ePlayerMoneySourceType_EquipMaintainCross		= 52,//װ����ֵ
	ePlayerMoneySourceType_TransferStar				= 53,//ת��
	ePlayerMoneySourceType_RandAttribute			= 54,//װ��������� 
	ePlayerMoneySourceType_EquipUpgrade				= 55,//װ��������
	ePlayerMoneySourceType_SoulStamp				= 56,//���������Ʒ
	ePlayerMoneySourceType_GemReplace				= 57,//�滻��ʯ
	ePlayerMoneySourceType_GemTakeDown				= 58,//��ж��ʯ
	ePlayerMoneySourceType_Hole						= 59,//���
	ePlayerMoneySourceType_EquipReOpenLight			= 60,//�ؿ���
	ePlayerMoneySourceType_EquipOpenLight			= 61,//����
	ePlayerMoneySourceType_EquipIdentify			= 62,//����
	ePlayerMoneySourceType_ShopCenter				= 63,//�̳�
	ePlayerMoneySourceType_ResetItemTime			= 64,//��ֵ��ʱװ������
	ePlayerMoneySourceType_DBMsgSetBillingMoney		= 65,//DB SERVERͬ��
	ePlayerMoneySourceType_Cache					= 66,//��ֵ
	ePlayerMoneySourceType_KillPerson				= 67,//ɱ�˻��
	ePlayerMoneySourceType_QuestEntrust				= 68,//����ί��
};

enum eItemLogInfo
{
	//�����Ʒ
	//eItemLogInfo_GainItem_Pick			= 0,  //ʰȡ�����Ʒ
	//eItemLogInfo_GainItem_Script		= 1,  //�ű������Ʒ
	//eItemLogInfo_GainItem_Shop			= 2,  //��ͨ�̵�����Ʒ
	//eItemLogInfo_GainItem_ShopCenter	= 3,  //�̳ǻ����Ʒ
	//eItemLogInfo_GainItem_Bargain		= 4,  //���׻����Ʒ
	//eItemLogInfo_GainItem_Mail			= 5,  //�ʼ������Ʒ

	//EIGS_UnKnow        =  0  ,    // δ֪ V
	//EIGS_OnlineReward   ,    // ���߽��� V
	//EIGS_Quest          ,    // ������� V
	//EIGS_Achieve        ,    // �ɾͽ��� V
	//EIGS_DropItem       ,    // ��ֵ��� V
	//EIGS_TreasureBox    ,    // ������ 
	//EIGS_JiFengShop     ,    // �����̵�
	//EIGS_NpcShop        ,    // NPC�̵� V
	//EIGS_Bargaining     ,    // ���� V
	//EIGS_Stall          ,    // ��̯ V
	//EIGS_Script         ,    // �ű���� V
	//EIGS_Upgrade        ,    // װ������ 
	//EIGS_Compose        ,    // �ϳ� V 
	//EIGS_GemTakeDown    ,    // ��ʯ��ж V
	//EIGS_FromPlat       ,    // ͨ��ƽ̨���
	//EIGS_GemInlayFail   ,    // ��Ƕʧ�ܽ���
	//EIGS_UnknowIdentify ,    // װ��δ֪���� V


	//������Ʒ
	eItemTrade_PrivateShop				= 0,	//��̯ V
	eItemTrade_Bargain					= 1,	//���� V

	//������Ʒ(ʧȥ��Ʒ)
	eItemLogInfo_ItemConsume_Use		= 0,   //ʹ����Ʒ V
	eItemLogInfo_ItemConsume_SellNpc	= 1,   //����NPC V
	eItemLogInfo_ItemConsume_Destroy	= 2,   //�ݻ� V
	eItemLogInfo_ItemConsume_Decompose	= 3,   //�ֽ� V
	eItemLogInfo_ItemConsume_Script		= 4,   //�ű�
	eItemLogInfo_ItemConsume_Bargain	= 5,   //���� V
	eItemLogInfo_ItemConsume_Mail		= 6,   //�ʼ� V
	eItemLogInfo_ItemConsume_DeadDrop		= 7,   //��������
	eItemLogInfo_ItemConsume_UnBind		= 8,   //���ʧȥ V
	eItemLogInfo_ItemConsume_UseLuck		= 9,   //ҡ��
	eItemLogInfo_ItemConsume_UpItem		= 10,   //���� V
	eItemLogInfo_ItemConsume_OnLineReward   = 11,   //���߽�����ȡʧ��
	eItemLogInfo_ItemConsume_ChangeCountry = 12,  //�ѹ��� V
	eItemLogInfo_ItemConsume_CountryPosition = 13, //����ְλ�ı�
	


	//������Ʒ
	eItemLogInfo_ItemUpgrade_Intensify	= 0,   //���� V
	eItemLogInfo_ItemUpgrade_MountIntensify	= 1,   //�������� V
	eItemLogInfo_ItemUpgrade_TradeStar	= 2,   //ת�� V
	eItemLogInfo_ItemUpgrade_Hole		= 3,   //��� V
	eItemLogInfo_ItemUpgrade_InsertHole	= 4,   //��Ƕ V
	eItemLogInfo_ItemUpgrade_OutGem		= 5,   //�α�ʯ V
	eItemLogInfo_ItemUpgrade_Random		= 6,   //ϴ��� V
	eItemLogInfo_ItemUpgrade_OpenLight	= 7,   //�̽�
	eItemLogInfo_ItemUpgrade_ReOpenLight= 8,   //��¯
	eItemLogInfo_ItemUpgrade_SoulStamp  = 9,   //����
};

enum eSystemLogInfo
{
	eSystemLogInfo_guild_create = 0, // �������� V
	eSystemLogInfo_guild_disband = 1, //�Զ���ɢ V
	eSystemLogInfo_guild_LevelUp = 2, // ���� V
	eSystemLogInfo_guild_SignUpKingWar = 3, // ��������ս V
	eSystemLogInfo_guild_sysdisband = 4,  //ϵͳ��ɢ 

};

struct GS2LPlayerInOutLog:public Msg
{
	GS2LPlayerInOutLog()
	{
		header.dwType = LOGMSG_INOUNTINFO;
		header.stLength = sizeof(GS2LPlayerInOutLog);
		memset(IpAddr,0,sizeof(IpAddr));
		memset(scMac,0,sizeof(scMac));
	}
	LogPlayerInfo   logcommon;
	char			IpAddr[20];
	char			scMac[20];//MAC_LENGTH
	int16			Logtype;
	uint32			onlinetime;
	uint16			lv;
	uint16			country;
	
};

struct GS2LItemGain:public Msg
{
	GS2LItemGain()
	{
		header.dwType = LOGMSG_ITEMGAIN;
		header.stLength = sizeof(GS2LItemGain);
	}
	LogPlayerInfo    logcommon;
	LogItemInfo		 logitem;
	int16			 logtype;
};

struct GS2LItemTrade:public Msg
{
	GS2LItemTrade()
	{
		header.stLength = sizeof(GS2LItemTrade);
		header.dwType =LOGMSG_ITEMTRADE; 
		memset(buyerName,0,sizeof(buyerName));
		memset(sellerName,0,sizeof(sellerName));
	}
	SYSTEMTIME _time;
	uint32		buyer_accid;
	uint32		buyer_chaid;
	char        buyerName[20];
	uint32		seller_accid;
	uint32		seller_chaid;
	char        sellerName[20];
	LogItemInfo	logitem;
	uint32		item_cost;
	int16		logtype;
};


struct GS2LItemConsume:public Msg
{
	GS2LItemConsume()
	{
		header.dwType = LOGMSG_ITEMCONSUME;
		header.stLength = sizeof(GS2LItemConsume);
	}
	LogPlayerInfo	logcommon;
	LogItemInfo		logitem;
	int16			logtype;
	uint16			item_LaveCount;
};

struct GS2LItemUpgrade:public Msg
{
	GS2LItemUpgrade()
	{
		header.dwType = LOGMSG_ITEMUPGRADE;
		header.stLength = sizeof(GS2LItemUpgrade);

		memset(previous,0,sizeof(uint16)*7);
		memset(current,0,sizeof(uint16)*7);
	}
	LogPlayerInfo	logcommon;
	LogItemInfo		logitem;
	uint16			previous[7];
	uint16			current[7];
	int16			result;
	int16			logtype;
};

struct GS2LQuestLog:public Msg
{
	GS2LQuestLog()
	{
		header.stLength = sizeof(GS2LQuestLog);
		header.dwType = LOGMSG_QUESTLOG;
	}
	LogPlayerInfo logcommon;
	uint32		  questid;
};

struct GS2LCurrencyLog:public Msg
{
	GS2LCurrencyLog()
	{
		header.dwType = LOGMSG_CURRENCY;
		header.stLength = sizeof(GS2LCurrencyLog);
	}
	LogPlayerInfo logcommon;
	int16		  money_type;
	int32		  count;
	int16		  logtype;
	int16		  sourcetype;
};

struct GS2LExpLog:public Msg
{
	GS2LExpLog()
	{
		header.dwType = LOGMSG_EXPLOG;
		header.stLength = sizeof(GS2LExpLog);
	}
	LogPlayerInfo logcommon;
	int32		  _exp;
	int16		  logtype;
	int32		  monsterid;
};

struct GS2LLevelChange:public Msg
{
	GS2LLevelChange()
	{
		header.dwType = LOGMSG_LEVCHANGE;
		header.stLength =sizeof(GS2LLevelChange);
	}
	LogPlayerInfo logcommon;
	uint16		  previouslev;
	uint16		  newlev;
};

struct S2LMailLog:public Msg
{
	S2LMailLog()
	{
		header.dwType = LOGMSG_MAILLOG;
		header.stLength = sizeof(S2LMailLog);
	}
	SYSTEMTIME	_time;
	uint32		send_accid;
	uint32		send_chid;
	uint32		recv_chid;
	char		mail_title[32];
	char		mail_detail[100];
	char        send_CharName[20];
	char        recv_CharName[20];
	char        ItemName[20];
	uint16		item_id;
	uint16		item_count;
	uint32		money;
	__int64      item_Guid;
};

struct S2LGuildLog:public Msg
{
	S2LGuildLog()
	{
		header.dwType = LOGMSG_GUILDLOG;
		header.stLength = sizeof(S2LGuildLog);
	}
	LogPlayerInfo logcommon;
	uint32		  guild_id;
	int16		  logtype;
};

struct S2LGuildDetailLog:public Msg
{
	S2LGuildDetailLog()
	{
		header.dwType = LOGMSG_GUILDDETAIL;
		header.stLength = sizeof(S2LGuildDetailLog);
	}
	LogPlayerInfo logcommon;
	uint32		  guild_id;
	int32		  moneychange;
	int32		  expchange;
	int32		  missionchange;
};

struct GS2LGMCommand:public Msg
{
	GS2LGMCommand()
	{
		header.dwType = LOGMSG_GMCOMMAND;
		header.stLength = sizeof(GS2LGMCommand);
		memset(frondose,0,sizeof(char)*128);
		memset(name,0,sizeof(char)*32);
		memset(ipAddr,0,sizeof(char)*32);
	}
	LogPlayerInfo logcommon;
	char   name[32];
	char   ipAddr[32];
	char   frondose[128];
};

struct GS2LChatInfo:public Msg
{
	GS2LChatInfo()
	{
		header.dwType = LOGMSG_CHATINFO;
		header.stLength = sizeof(GS2LChatInfo);
		memset(content,0,sizeof(char)*500);
		memset(TargetCharName,0,sizeof(char)*20);
	}
	LogPlayerInfo logcommon;
	char		  content[500];
	char		  TargetCharName[20];
	uint32		  target_id;
	int16		  chat_type;
};

#pragma pack( pop ) 

#endif