#ifndef __COMMON_MESSAGERANGEDEFINE_H__
#define __COMMON_MESSAGERANGEDEFINE_H__

#pragma once

enum EMessageRange
{
	//*********************************废弃
    CLIENTSERVER_MSG_BEGIN        = 1,    // 客户端到服务器的协议范围
    CLIENTSERVER_MSG_END          = 499,
	//*********************************废弃
    SERVERCLIENT_MSG_BEGIN        = 499, // 服务器到客户端的协议范围
    SERVERCLIENT_MSG_END          = 999,

	//[Game and Client]消息定义范围
    GAMEWORLD_MSG_BEGIN           = 1000,
    GAMEWORLD_MSG_END             = 3000,

    // [国家模块]<s2c>消息范围
    GAMEWORD_COUNTRYMSG_BEGIN,
    GAMEWORD_COUNTRYMSG_END   = GAMEWORD_COUNTRYMSG_BEGIN + 70,

    // 沙巴克争夺战消息范围  ************废弃
    GAMEWORD_CONTENDMSG_BEGIN, 
    GAMEWORD_CONTENDMSG_END = GAMEWORD_CONTENDMSG_BEGIN + 50,

    // [寄售模块]<s2c>消息范围
    GAMEWORD_CONSIGNMENTMSG_BEGIN, 
    GAMEWORD_CONSIGNMENTMSG_END = GAMEWORD_CONSIGNMENTMSG_BEGIN + 30,

    // 队伍&Pk系统消息范围*****************废弃
    GAMEWORD_TEAMCONTEND_BEGIN, 
    GAMEWORD_TEAMCONTEND_END = GAMEWORD_TEAMCONTEND_BEGIN + 20,

    // [关系模块]<s2c>消息范围
    GAMEWORD_RELATION_BEGIN, 
    GAMEWORD_RELATION_END = GAMEWORD_RELATION_BEGIN + 50,

    // [公会模块]<s2c>消息范围
    GAMEWORD_GUILDMSG_BEGIN,   
    GAMEWORD_GUILDMSG_END = GAMEWORD_GUILDMSG_BEGIN + 90,

    // [摆摊模块]<s2c>消息范围
    GAMEWORD_STALLMSG_BEGIN,   
    GAMEWORD_STALLMSG_END = GAMEWORD_STALLMSG_BEGIN + 30,

    // [交易模块]<s2c>消息范围
    GAMEWORD_BARGAININGMSG_BEGIN,   
    GAMEWORD_BARGAININGMSG_END = GAMEWORD_BARGAININGMSG_BEGIN + 20,

    // [密码保护模块]<s2c>消息范围
    GAMEWORLD_PASSWORD_BEGIN,   
    GAMEWORLD_PASSWORD_END = GAMEWORLD_PASSWORD_BEGIN + 20,

    // [阵营战场模块]<s2c>消息范围
    GAMEWORD_CAMPBATTLEMSG_BEGIN,   
    GAMEWORD_CAMPBATTLEMSG_END = GAMEWORD_CAMPBATTLEMSG_BEGIN + 90,

	// [家族模块]<s2c>消息范围
	GAMEWORD_FAMILYMSG_BEGIN,
	GAMEWORD_FAMILYMSG_END = GAMEWORD_FAMILYMSG_BEGIN + 90,

    // 服务器间消息定义范围 *************废弃
    S2S_MSG_BEGIN = 10000,
    S2S_MSG_END = S2S_MSG_BEGIN + 1000,

	// [Game and DBServer]消息定义范围
    DB_MSG_BEGIN,
    DB_MSG_END = DB_MSG_BEGIN + 200,

	//**********************废弃
    THIRDPARTYAPP_MSG_BEGIN,
    THIRDPARTYAPP_MSG_END = THIRDPARTYAPP_MSG_BEGIN + 1000,
	
	// [Center and Game] 之间的模块之外的协议范围
    CENTERGAME_MESSAGE_BEGIN,
    CENTERGAME_MESSAGE_END = CENTERGAME_MESSAGE_BEGIN + 1000,

    // [国家模块]<s2s>消息范围
    CENTERGAME_COUNTRY_BEGIN,
    CENTERGAME_COUNTRY_END = CENTERGAME_COUNTRY_BEGIN + 50,

    // 争夺战*****************废弃
    CENTERGAME_CONTEND_BEGIN,  
    CENTERGAME_CONTEND_END = CENTERGAME_CONTEND_BEGIN + 50,

    // [寄售模块]<s2s>消息范围
    CENTERGAME_CONSIGNMENT_BEGIN,  
    CENTERGAME_CONSIGNMENT_END = CENTERGAME_CONSIGNMENT_BEGIN + 30,

    // [关系模块]<s2s>消息范围
    CENTERGAME_RELATION_BEGIN, 
    CENTERGAME_RELATION_END = CENTERGAME_RELATION_BEGIN + 50,

    // [公会模块]<s2s>消息范围
    CENTERGAME_GUILD_BEGIN, 
    CENTERGAME_GUILD_END = CENTERGAME_GUILD_BEGIN + 90,

	// [家族模块]<s2s>消息范围
	CENTERGAME_FAMILY_BEGIN,
	CENTERGAME_FAMILY_END = CENTERGAME_FAMILY_BEGIN + 90,

	// [摆摊模块]<s2s>消息范围 [交易模块]<s2c>消息范围 [密码保护模块]<s2c>消息范围 [阵营战场模块]<s2c>消息范围

    // [Center and DBServer]消息范围
    SYSTEM_VAR_BEGIN, 
    SYSTEM_VAR_END = SYSTEM_VAR_BEGIN + 20,

	// [Center and Login]消息范围
    CENTERLOGIN_MESSAGE_BEGIN,
    CENTERLOGIN_MESSAGE_END = CENTERLOGIN_MESSAGE_BEGIN + 1000,

	// [Center and DBServer]消息范围 (跟上个重复了，貌似没用了不确定哦)
    CENTERDBSERVER_MESSAGE_BEGIN,
    CENTERDBSERVER_MESSAGE_END = CENTERDBSERVER_MESSAGE_BEGIN + 1000,

	// [等级封印模块]
	CENTERGAME_LEVELLIMIT_BEGIN,
	CENTERGAME_LEVELLIMIT_END = CENTERGAME_LEVELLIMIT_BEGIN + 50,

    // 平台与服务器出的消息范围
    PLATFORM_MESSAGE_BEGIN = 20000,
    PLATFORM_MESSAGE_END = PLATFORM_MESSAGE_BEGIN + 150,
	
	//*********************************废弃
    UU_MSG_BEGIN,
    UU_MSG_END = UU_MSG_BEGIN + 1000,

	//CenterLoginServer ***************废弃
	CENTER_LOGIN_SERVER_BEGIN,
	CENTER_LOGIN_SERVER_END = CENTER_LOGIN_SERVER_BEGIN + 10,

	// [全局数据模块]
	GLOBALDB_SERVER_BEGIN,
	GLOBALDB_SERVER_END = GLOBALDB_SERVER_BEGIN +10,

	// 皇帝消息范围 ********************废弃
    GAMEWORD_EMPERORMSG_BEGIN,
    GAMEWORD_EMPERORMSG_END   = GAMEWORD_EMPERORMSG_BEGIN + 70,

	// *****************废弃
	GAMEWORD_WANTED_BEGIN,
	GAMEWORD_WANTED_END   = GAMEWORD_WANTED_BEGIN + 40,

	// [委托任务模块]
	GAMEWORD_QUESTENTRUST_BEGIN,
	GAMEWORD_QUESTENTRUST_END = GAMEWORD_QUESTENTRUST_BEGIN+40,

	// [红蓝战场模块]
	GAMEBATTLE_BEGIN,
	GAMEBATTLE_END = GAMEBATTLE_BEGIN + 100,

	CSAUTH_BEGIN,
	CSAUTH_END = CSAUTH_BEGIN + 10,
};

enum EMessageModule
{
    EMessageModule_Default = ModuleType_None,
    EMessageModule_Relation   , // 关系模块
    EMessageModule_Country    , // 国家模块
    EMessageModule_Guild      , // 公会模块
    EMessageModule_Consignment, // 寄售模块
    EMessageModule_Stall      , // 摆摊模块
    EMessageModule_Bargaining , // 交易模块
    EMessageModule_Password   , // 密码保护模块
    EMessageModule_CampBattle , // 阵营战场模块
    EMessageModule_Platform   , // 平台模块 被重新设计后 成为了独立的协议段了
	EMessageModule_Family	  , // 家族模块
	EMessageModule_LEVELLIMIT , // 等级封印模块
	EMessageModule_GolbalDB	  ,	// 全局数据模块
	EMessageModule_Emperor    ,	// 皇帝模块 *****废弃
	EMessageModule_Wanted	  ,	// *************废弃
	EMessageModule_QuestEntrust,// 委托模块
	EMessageModule_GameBattle ,	// 红蓝战场
	EMessageModule_CSAuth,      // 反外挂模块
};

#endif // __COMMON_MESSAGERANGEDEFINE_H__
