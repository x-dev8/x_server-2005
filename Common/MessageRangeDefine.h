#ifndef __COMMON_MESSAGERANGEDEFINE_H__
#define __COMMON_MESSAGERANGEDEFINE_H__

#pragma once

enum EMessageRange
{
	//*********************************����
    CLIENTSERVER_MSG_BEGIN        = 1,    // �ͻ��˵���������Э�鷶Χ
    CLIENTSERVER_MSG_END          = 499,
	//*********************************����
    SERVERCLIENT_MSG_BEGIN        = 499, // ���������ͻ��˵�Э�鷶Χ
    SERVERCLIENT_MSG_END          = 999,

	//[Game and Client]��Ϣ���巶Χ
    GAMEWORLD_MSG_BEGIN           = 1000,
    GAMEWORLD_MSG_END             = 3000,

    // [����ģ��]<s2c>��Ϣ��Χ
    GAMEWORD_COUNTRYMSG_BEGIN,
    GAMEWORD_COUNTRYMSG_END   = GAMEWORD_COUNTRYMSG_BEGIN + 70,

    // ɳ�Ϳ�����ս��Ϣ��Χ  ************����
    GAMEWORD_CONTENDMSG_BEGIN, 
    GAMEWORD_CONTENDMSG_END = GAMEWORD_CONTENDMSG_BEGIN + 50,

    // [����ģ��]<s2c>��Ϣ��Χ
    GAMEWORD_CONSIGNMENTMSG_BEGIN, 
    GAMEWORD_CONSIGNMENTMSG_END = GAMEWORD_CONSIGNMENTMSG_BEGIN + 30,

    // ����&Pkϵͳ��Ϣ��Χ*****************����
    GAMEWORD_TEAMCONTEND_BEGIN, 
    GAMEWORD_TEAMCONTEND_END = GAMEWORD_TEAMCONTEND_BEGIN + 20,

    // [��ϵģ��]<s2c>��Ϣ��Χ
    GAMEWORD_RELATION_BEGIN, 
    GAMEWORD_RELATION_END = GAMEWORD_RELATION_BEGIN + 50,

    // [����ģ��]<s2c>��Ϣ��Χ
    GAMEWORD_GUILDMSG_BEGIN,   
    GAMEWORD_GUILDMSG_END = GAMEWORD_GUILDMSG_BEGIN + 90,

    // [��̯ģ��]<s2c>��Ϣ��Χ
    GAMEWORD_STALLMSG_BEGIN,   
    GAMEWORD_STALLMSG_END = GAMEWORD_STALLMSG_BEGIN + 30,

    // [����ģ��]<s2c>��Ϣ��Χ
    GAMEWORD_BARGAININGMSG_BEGIN,   
    GAMEWORD_BARGAININGMSG_END = GAMEWORD_BARGAININGMSG_BEGIN + 20,

    // [���뱣��ģ��]<s2c>��Ϣ��Χ
    GAMEWORLD_PASSWORD_BEGIN,   
    GAMEWORLD_PASSWORD_END = GAMEWORLD_PASSWORD_BEGIN + 20,

    // [��Ӫս��ģ��]<s2c>��Ϣ��Χ
    GAMEWORD_CAMPBATTLEMSG_BEGIN,   
    GAMEWORD_CAMPBATTLEMSG_END = GAMEWORD_CAMPBATTLEMSG_BEGIN + 90,

	// [����ģ��]<s2c>��Ϣ��Χ
	GAMEWORD_FAMILYMSG_BEGIN,
	GAMEWORD_FAMILYMSG_END = GAMEWORD_FAMILYMSG_BEGIN + 90,

    // ����������Ϣ���巶Χ *************����
    S2S_MSG_BEGIN = 10000,
    S2S_MSG_END = S2S_MSG_BEGIN + 1000,

	// [Game and DBServer]��Ϣ���巶Χ
    DB_MSG_BEGIN,
    DB_MSG_END = DB_MSG_BEGIN + 200,

	//**********************����
    THIRDPARTYAPP_MSG_BEGIN,
    THIRDPARTYAPP_MSG_END = THIRDPARTYAPP_MSG_BEGIN + 1000,
	
	// [Center and Game] ֮���ģ��֮���Э�鷶Χ
    CENTERGAME_MESSAGE_BEGIN,
    CENTERGAME_MESSAGE_END = CENTERGAME_MESSAGE_BEGIN + 1000,

    // [����ģ��]<s2s>��Ϣ��Χ
    CENTERGAME_COUNTRY_BEGIN,
    CENTERGAME_COUNTRY_END = CENTERGAME_COUNTRY_BEGIN + 50,

    // ����ս*****************����
    CENTERGAME_CONTEND_BEGIN,  
    CENTERGAME_CONTEND_END = CENTERGAME_CONTEND_BEGIN + 50,

    // [����ģ��]<s2s>��Ϣ��Χ
    CENTERGAME_CONSIGNMENT_BEGIN,  
    CENTERGAME_CONSIGNMENT_END = CENTERGAME_CONSIGNMENT_BEGIN + 30,

    // [��ϵģ��]<s2s>��Ϣ��Χ
    CENTERGAME_RELATION_BEGIN, 
    CENTERGAME_RELATION_END = CENTERGAME_RELATION_BEGIN + 50,

    // [����ģ��]<s2s>��Ϣ��Χ
    CENTERGAME_GUILD_BEGIN, 
    CENTERGAME_GUILD_END = CENTERGAME_GUILD_BEGIN + 90,

	// [����ģ��]<s2s>��Ϣ��Χ
	CENTERGAME_FAMILY_BEGIN,
	CENTERGAME_FAMILY_END = CENTERGAME_FAMILY_BEGIN + 90,

	// [��̯ģ��]<s2s>��Ϣ��Χ [����ģ��]<s2c>��Ϣ��Χ [���뱣��ģ��]<s2c>��Ϣ��Χ [��Ӫս��ģ��]<s2c>��Ϣ��Χ

    // [Center and DBServer]��Ϣ��Χ
    SYSTEM_VAR_BEGIN, 
    SYSTEM_VAR_END = SYSTEM_VAR_BEGIN + 20,

	// [Center and Login]��Ϣ��Χ
    CENTERLOGIN_MESSAGE_BEGIN,
    CENTERLOGIN_MESSAGE_END = CENTERLOGIN_MESSAGE_BEGIN + 1000,

	// [Center and DBServer]��Ϣ��Χ (���ϸ��ظ��ˣ�ò��û���˲�ȷ��Ŷ)
    CENTERDBSERVER_MESSAGE_BEGIN,
    CENTERDBSERVER_MESSAGE_END = CENTERDBSERVER_MESSAGE_BEGIN + 1000,

	// [�ȼ���ӡģ��]
	CENTERGAME_LEVELLIMIT_BEGIN,
	CENTERGAME_LEVELLIMIT_END = CENTERGAME_LEVELLIMIT_BEGIN + 50,

    // ƽ̨�������������Ϣ��Χ
    PLATFORM_MESSAGE_BEGIN = 20000,
    PLATFORM_MESSAGE_END = PLATFORM_MESSAGE_BEGIN + 150,
	
	//*********************************����
    UU_MSG_BEGIN,
    UU_MSG_END = UU_MSG_BEGIN + 1000,

	//CenterLoginServer ***************����
	CENTER_LOGIN_SERVER_BEGIN,
	CENTER_LOGIN_SERVER_END = CENTER_LOGIN_SERVER_BEGIN + 10,

	// [ȫ������ģ��]
	GLOBALDB_SERVER_BEGIN,
	GLOBALDB_SERVER_END = GLOBALDB_SERVER_BEGIN +10,

	// �ʵ���Ϣ��Χ ********************����
    GAMEWORD_EMPERORMSG_BEGIN,
    GAMEWORD_EMPERORMSG_END   = GAMEWORD_EMPERORMSG_BEGIN + 70,

	// *****************����
	GAMEWORD_WANTED_BEGIN,
	GAMEWORD_WANTED_END   = GAMEWORD_WANTED_BEGIN + 40,

	// [ί������ģ��]
	GAMEWORD_QUESTENTRUST_BEGIN,
	GAMEWORD_QUESTENTRUST_END = GAMEWORD_QUESTENTRUST_BEGIN+40,

	// [����ս��ģ��]
	GAMEBATTLE_BEGIN,
	GAMEBATTLE_END = GAMEBATTLE_BEGIN + 100,

	CSAUTH_BEGIN,
	CSAUTH_END = CSAUTH_BEGIN + 10,
};

enum EMessageModule
{
    EMessageModule_Default = ModuleType_None,
    EMessageModule_Relation   , // ��ϵģ��
    EMessageModule_Country    , // ����ģ��
    EMessageModule_Guild      , // ����ģ��
    EMessageModule_Consignment, // ����ģ��
    EMessageModule_Stall      , // ��̯ģ��
    EMessageModule_Bargaining , // ����ģ��
    EMessageModule_Password   , // ���뱣��ģ��
    EMessageModule_CampBattle , // ��Ӫս��ģ��
    EMessageModule_Platform   , // ƽ̨ģ�� ��������ƺ� ��Ϊ�˶�����Э�����
	EMessageModule_Family	  , // ����ģ��
	EMessageModule_LEVELLIMIT , // �ȼ���ӡģ��
	EMessageModule_GolbalDB	  ,	// ȫ������ģ��
	EMessageModule_Emperor    ,	// �ʵ�ģ�� *****����
	EMessageModule_Wanted	  ,	// *************����
	EMessageModule_QuestEntrust,// ί��ģ��
	EMessageModule_GameBattle ,	// ����ս��
	EMessageModule_CSAuth,      // �����ģ��
};

#endif // __COMMON_MESSAGERANGEDEFINE_H__
