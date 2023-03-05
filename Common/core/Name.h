#pragma once

enum eName
{

	//==================新字符串定义=========================================================

	eLogin_UserPassError             = 0,    //用户名密码错误
	eLogin_VersionError              = 1,    //版本错误
	eLogin_UseOnline                 = 2,        //有用户在线
	eLogin_UnKnown                   = 3,            //未知
	eCreate_PlayerNameSame           = 4,    //用户名存在
	eDeletePlayerFail                = 5,    //删除角色失败
	eText_Enter_DeletePlayer         = 6,    //确定删除此玩家
	ePlayerCountIsFull               = 7,    // 角色数量已满
	eText_Disconnect                 = 8,       //与服务器连接断开
	eText_ConFail                    = 9,                    //连接失败
	eText_SelectServer               = 10,            //请选择服务器
	eText_DBID				         = 11,			//(ID:%d)
	eText_EnterUsePass               = 12,        //请输入用户名或密码
	eText_NowTryConnecting           = 13,       //正在尝试与服务器连接
	eText_NowLoadingGameData		 = 14,		// 正在读取游戏数据
	eText_KickAccounts				 = 15,		// 你的帐号被踢
	eText_Custom					 = 16,		// 自定义
	eText_CreateCheckNameOK          = 17, //恭喜！该人物名可以正常使用
	eText_CreateCheckNameNO          = 18, //对不起，该人物名已被他人使用
	eText_WaitEnterWorld			 = 19, //正在进入游戏，请稍候...
	eText_GraphicCodeTimeOut		 = 20, // 验证码验证超时
	eText_IsDelChar                  = 21, //角色已经被删除
	eText_DelChar_OK                 = 22, //角色删除成功
	eText_GraphicCodeErrorKick		 = 23, //验证码失败
	eText_CancelDel_Check            = 24, //取消删除角色
	eText_CancelDel_Success          = 25, //取消删除角色成功
	eText_CancelDel_Fail             = 26, //取消删除角色失败
	eText_LastIp					 = 27, //上一次登陆IP
	eText_LastAddress				 = 28, //上一次登陆地址
	eText_LastTime					 = 29, //上一次登陆时间
	eText_ProtectTimeAtLeast         = 30, //安全保护时间最少不得小于%d分钟
	eText_LowSetting				 = 31,
	eText_DefaultSetting			 = 32,
	eError_DetectInvalidPlus		 = 33,
	eText_Ping                       = 34, //网络延迟:%dms
	eIsExitGame                      = 35,//是否下线
	eClient_Minimap_ServerShow       = 36,    //当前服务器%s ping:%d
	eError_VideoCardToSlow			 = 37, //显卡配置过低
	eError_ServerBusy                = 38,//服务器繁忙\n请您再次尝试
	eServer_State1_Capitally         = 39,  //极佳
	eServer_State2_Nicer             = 40,      //良好
	eServer_State3_Busyness          = 41,   //繁忙
	eServer_State4_Jam               = 42,        //拥挤
	eServer_State5_Close             = 43,      //关闭
	eLogin_Error_UserFreezed		 = 44,	// 账号被冻结
	//eServer_State7_Defual =44,//" "
	//eServer_State6_maintenance = 45,//维护
	//eServer_State0_Close = 46,     //关闭
	eUI_ask                          = 47,                    //询问
	eClient_AddInfo_2slk_16          = 48,        //询问
	eLogin_TimeLongConnectFailed     = 49,    //无法连接服务器！
	eLogin_ServerBusy                = 50,    //服务器繁忙！
	eText_Confirm                    = 51,                    //确认
	eClient_AddInfo_2slk_122         = 52,        //%s【剩余 %d 秒】 
	eClient_AddInfo_2slk_130         = 53,        //验证剩余时间 %d 秒 
	eClient_AddInfo_2slk_131         = 54,        //验证时间已到 
	eClient_LoadCoreDataError        = 55,    //Client关键数据已损坏，请重新安装Client
	eGameSettingList_Sound			 = 56,		// 声音设置
	eText_AntiAddictionLess3Hour     = 57,       // 您累计在线时间已满%d小时
	eText_AntiAddiction3Hour         = 58,       // 您累计在线时间已满3小时，请您下线休息，做适当身体活动
	eText_AntiAddiction4to5Hour      = 59,       // 您已经进入疲劳游戏时间，您的游戏收益将降为正常值的50％，为了您的健康，请尽快下线休息，做适当身体活动，合理安排学习生活
	eText_AntiAddictionMoreThan5Hour = 60,       // 您已进入不健康游戏时间，为了您的健康，请您立即下线休息。如不下线，您的身体将受到损害，您的收益已降为零，直到您的累计下线时间满5小时后，才能恢复正常
	eGameSettingList_Refuse          = 61,       // 拒绝邀请提示
	eText_No_PF_Target				 = 62,         //没有目标可以前往
	eText_BanSpeak                   = 63,       //禁言时间剩余%d分钟
	eClient_AddInfo_2slk_132         = 64,        //男 
	eClient_AddInfo_2slk_133         = 65,        //女 
	eClient_IfSellItem1				 = 67,        //请确定是否需要卖出 %s  
	eClient_IfSellItem2				 = 68,        //请确定是否需要卖出 %s  
	eClient_IfSellItem3				 = 69,        //请确定是否需要卖出 %s  
	eClient_IfSellItem4				 = 70,        //请确定是否需要卖出 %s  
	eClient_IfSellItem5				 = 71,        //请确定是否需要卖出 %s  
	eClient_IfSellItem6				 = 72,        //请确定是否需要卖出 %s  
	eText_ProduceRate				 = 73, // 产出率
	eText_ExitGameCountDown          = 74, // 正在退出游戏
	////////////////////////////////////////////////////////////////
	///游戏设置左侧list列表项
	eGameSettingList_Self			= 75, // 自身信息
	eGameSettingList_Player			= 76, // 玩家信息
	eGameSettingList_Npc			= 77, // npc及场景
	eGameSettingList_Function		= 78, // 功能
	eGameSettingList_Mouse			= 79, // 鼠标设置


	eInitError_80				= 80,
	eInitError_81				= 81,
	eInitError_82				= 82,
	eInitError_83				= 83,
	eInitError_84				= 84,
	eInitError_85				= 85,
	eInitError_86				= 86,
	eInitError_87				= 87,
	eInitError_88				= 88,
	eInitError_89				= 89,
	eInitError_90				= 90,
	eInitError_91				= 91,
	eInitError_92				= 92,
	eInitError_93				= 93,
	eInitError_94				= 94,

	eText_ProtectTime           = 95,       // 安全时间:%s
	eText_ProtectTime_ChangeSucc = 96,      // 安全时间修改成功
	eText_CannotDoIt = 97,      // 安全保护下无法进行此操作
	eText_TradeFailed_PlayerInProtect = 98, // 对方在安全保护时间内，交易失败
	eText_ProtectTime_ChangeFailed = 99,    // 安全保护设置失败，请重新设置
	// dumpe提示
	eDumper_MessageBox_ClientError = 100,		// 客户端出现异常

	eText_PKMode_LevelLimit     = 101,          // %d级前无法更改攻击保护
	eText_PrivateShop_LevelLimit= 102,          // %d级前无法进行摆摊操作
	eText_SkillLevel            = 103,          // %d级
	eText_FindTheNpc				= 104,			// 寻找%s

	///////////////////////////////////////////
	/// title类型	(根据title.config中注释走)
	eTitleTypeText_JuQing		= 105,		// 剧情
	eTitleTypeText_GuanZhi		= 106,		// 官职
	eTitleTypeText_GuanFu		= 107,		// 官府
	eTitleTypeText_HuoDong		= 108,		// 活动
	eTitleTypeText_MinJian		= 109,		// 民间
	eTitleTypeText_GuanXi		= 110,		// 关系
	eTitleTypeText_MinWang		= 111,		// 名望
	eTitleTypeText_ChuanQi		= 112,		// 传奇
	eTitleTypeText_TeShu		= 113,		// 特殊
	eTitleTypeText_JueWei		= 114,		// 爵位		
	eTitleTypeText_Task_ForTitle		= 115,		// 任务
	eTitleTypeText_New1			= 116,
	eTitleTypeText_New2			= 117,

	eError_ClientMemoryLack		= 120,      // 内存不足，运行游戏需要600MB的物理内存

	eText_PKMode_NoChange       = 121,      // PK值大于0,无法切换到其他模式
	eText_PKMode_TimeLimit      = 122,      // 不能频繁切换PK模式（3分钟）
	eText_PKMode_FuryTimeLimit  = 123,      // 狂暴模式30分钟时限未到
	eText_PKMode_FuryNoShop     = 124,      // 狂暴模式不能摆摊

	eText_PKMode_Off            = 125,      // PK模式:关闭
	eText_PKMode_On             = 126,      // PK模式:开启
	eText_PKMode_Fury           = 127,      // PK模式:狂暴
	eText_NotInStallArea		=128, //不再摆摊区域

	eText_PKMode_GuildOn		= 129,		// 公会PK模式：开启
	eLeftType_Hp				= 130,		// Hp
	eLeftType_Mp				= 131,		// Mp

	eTitleTypeText_Task					= 135,		// 任务


	eText_ShowAllPlayer         = 136,   //显示所有玩家
	eText_HideAllPlayer         = 137,   //隐藏所有玩家
	eText_ShowAmityPlayer       = 138,   //显示友好玩家
	eText_ShowAntagonizePlayer  = 139,   //显示敌对玩家

    eLogin_ValidateUser			= 140,		// 验证用户
    eLogin_EnterGame			= 141,		// 正在进入游戏
    eLogin_Process				= 142,		// 处理中
    eLogin_ConnectGate			= 143,		// 连接游戏服务器

	eText_ServerShutdown1		= 144,		// 服务器将于%s后进行维护，请玩家及时下线，以免造成不必要的损失
	eText_ServerShutdown2		= 145,		// 服务器将于%s后进行维护，建议您等待维护结束后再进入游戏
	eText_ShowMapExpRate        = 146,      // 当前地图经验获取为%d%%
	eText_ShowChangeMapExpRate  = 147,      // %s已开启了%d%%倍经验
	eText_MapExp				= 148,		// 当前地图已开启%d倍经验奖励
	eText_MaxMoneyTip			= 149,		//包裹和仓库的金钱总上限\n1-20级10金\n21-40级100金\n41-55级1000金\n55级以上5000金\n到达上限后将无法进行交易和摆摊
	eLogin_AccountsError		= 151,		// 账号不存在
	eLogin_PasswordError		= 152,		// 密码错误
	eText_Area                  = 153,      //大区:%s
	eText_ServerName            = 154,      //当前服务器:%s
	eText_JiaoZiTip             = 155,      //交子:绑定货币，说明XXXXXX

	eText_BeiJing						 =156, //北京
	eText_ShangHai					 =157,//上海
	eText_TianJin						 =158,//天津
	eText_ChongQing				 =159,//重庆
	eText_NeiMengGu				 =160,//内蒙古
	eText_XinJiang						 =161,//新疆
	eText_XiZang						 =162,//西藏
	eText_NingXia						 =163,//宁夏
	eText_GuangXi						 =164,//广西
	eText_HongKong				 =165,//香港
	eText_MaCao						 =166,//澳门
	eText_HeiLongJiang			 =167,//黑龙江
	eText_JiLin								 =168,//吉林
	eText_LiaoNing					 =169,//辽宁
	eText_HeBei							 =170,//河北
	eText_ShanXi						 =171,//山西
	eText_QingHai						 =172,//青海
	eText_ShanDong					 =173,//山东
	eText_HeNan						 =174,//河南
	eText_JiangSu						 =175,//江苏
	eText_AnHui							 =176,//安徽
	eText_ZheJiang					 =177,//浙江
	eText_FuJian							 =178,//福建
	eText_JiangXi						 =179,//江西
	eText_HuNan						 =180,//湖南
	eText_HuBei							 =181,//湖北
	eText_GuangDong				 =182,//广东
	eText_TaiWan						 =183,//台湾
	eText_HaiNan						 =184,//海南
	eText_GanSu							 =185,//甘肃
	eText_Shan_Xi						 =186,//陕西
	eText_SiChuan						 =187,//四川
	eText_GuiZhou						 =188,//贵州
	eText_YunNan						 =189,//云南

	eGameSettingList_Tab        = 190,      //Tab功能设置
	eText_KuaiJieJian					=197,		//快捷键
	eText_CaoZuo						=198,		//操作
	eText_GuildOffer					= 199,		// 帮贡
	eText_Exploit						= 200,		// 功勋
	eText_Reputation				= 201,		// 声望
	eText_Energy						= 202,		// 活力
	eText_Vigor							= 203,		// 精力
	eText_PKValue						= 204,		// pk值


	eText_TheFinalAward			=205,				//系列任务\n终极奖励
	eText_TheAward				=206,				//物品

	eText_CannotShareExp		=207,				//队友位置:%s（与你距离过远，无法共享经验）
	eText_ShareExp				=208,				//队友位置:%s（在你的视野范围内，可以共享经验）
	eText_TalkToPlayer          =209,               //和 %s 聊天中
	eText_CannotConjurePetExit	=210,				//召唤兽尚未消失，无法再次召唤

	eText_EnableSoftKeyboard    =211,               //点击开启软键盘
	eText_DisableSoftKeyboard   =212,               //点击关闭软键盘
	eText_ReStartIntroduction   =213,               //你可以通过 游戏设置—功能—新手指引 继续开启新手引导
	eText_SuperPasswordExplain  =214,               //超级密码是修改您登陆密码和身份认证的重要途径，请妥善保管。\n超级密码由8-32位字母、数字及符号组成，区分大小写。
	eText_TodayKillMonster      =215,               //今日极限杀怪数量"今日极限杀怪数量:%d/%d"/
	eText_WaitingServerUpdate      =216,               //正在进行数据查询，请稍候...
	eText_FilterCharInfo        = 217,             //信息中带有非法字符，发送失败

	eText_TeamOffLine			= 218,             //离线

	eText_PubQuestItemCount		= 219,				// 行酒令数量
	eText_NotFindRepairItem		= 220,			// 没有指定的特修道具

	eText_GuildMoney			= 221,	// 帮会资金
	eText_GuildBuild			= 222,  // 帮会建设度
	eText_TimeOut				= 223,	// 已到期
	eText_OperateFailInProtectTime = 224,			//财产保护状态下无法进行此操作
	eText_ServerStatus          = 225,  //服务器爆满\n您可以继续尝试，或选择其他服务器进行登陆
	eText_OperateContinue       = 226, //继续
	eText_OperatorReturn        = 227, //返回
	eText_LauncherStart         = 228, //需要从Launcher启动
	eText_ErrorStart            = 229, //启动出错
	eText_AutoFightStart        = 230, //开始挂机
	eText_AutoFightEnd          = 231, //停止挂机
	eText_StarAll               = 232, //已经满星
	eText_Yes                   = 233, //是
	eText_No                    = 234, //否
	eText_SuperAll              = 235, //爆满
	eText_NameNoNull            = 236, //搜索名字不能为空
	eText_DragLockWarning		= 237, //拖拽警告

	eText_ScreenshotSaved		= 238, //截图%s保存成功至Screenshots文件夹下（按下F12可隐藏所有界面，进入照相模式）
	eText_PointShowInfo         = 239,  //未查询到您积分兑换的礼品信息
	eText_MarrySuccess          = 240,  //恭喜%s与%s喜结连理，祝福他们能相伴一生白头到老
	eText_UseItemFailed_InCD	= 242,	//物品正在冷却中，请稍后再试
	eText_AutoFightNoFindHP        = 243, //开始挂机
	eText_AutoFightNoFindMP         = 244, //停止挂机

	eText_Guild_CreateFamily = 245,
	eText_Guild_ChangeFamilyName = 246,
	eText_AutoFightUseRestorLev = 247, //自动挂机恢复药品使用等级不足
	eText_AutoFightNotStartCurState        = 248, //该状态下不能自动挂机


	eText_SkillUse_ProfessionLimit       = 258,  //职业不符，无法使用此技能

	eText_GameSettingHigh       = 260,  //高品质
	eText_GameSettingMiddle	    = 261,  //中品质
	eText_GameSettingLow        = 262,  //低品质
	eText_GameSettingCustom     = 263,  //自定义
	eText_Level	= 264,	//等级
	eText_GameTaskInfo          = 270,  //你没有举义令

	//十二生肖
	eText_AnimShu					=271, //鼠
	eText_AnimNiu						=272,//牛
	eText_AnimHU						=273,//虎
	eText_AnimTu						=274,//兔
	eText_AnimLong					=275,//龙
	eText_AnimShe					=276,//蛇
	eText_AnimMa						=277,//马
	eText_AnimYang					=278,//羊
	eText_AnimHou					=279,//猴
	eText_AnimJi						=280,//鸡
	eText_AnimGou					=281,//狗
	eText_AnimZhu					=282,//猪
	//十二星座
	eText_ConShuiPing				=284,//水瓶座   1.20 - 2.18
	eText_ConShuangYu			=285,//双鱼座   2.19 - 3.20
	eText_ConBaiYang				=286,//白羊座   3.21 - 4.20
	eText_ConJinNiu					=287,//金牛座   4.21 - 5.20
	eText_ConShuangZi			=288,//双子座   5.21 - 6.21
	eText_ConJuXie					=289,//巨蟹座   6.22 - 7.22
	eText_ConShiZi					=290,//狮子座   7.23 - 8.22
	eText_ConChuNv					=291,//处女座   8.23 - 9.22
	eText_ConTianCheng			=292,//天秤座   9.23 - 10.22
	eText_ConTianXie				=293,//天蝎座   10.23 - 11.21
	eText_ConSheShou				=294,//射手座   11.22 - 12.21
	eText_ConMoJie					=295,//摩羯座   12.22 - 1.19
	eText_CreateBrithDay			=296,//您的生日是%d月%d日,星座为%s,您确定创建吗？
	eText_SelPlayerDelLifeTime      =297,//角色删除剩余%d天
	//eUI_LevelUp                =300,                //你的等级提升了
	eTip_AlreadyMaxLevel		 = 300,				// 已到最高等级
	eUI_NextLevel                =301,                        //下一级
	eUI_NeedText                =302,            //需要
	eText_YouGet_Money         =303,        //    你得到了
	eText_Exp                    =304,        //
	//eText_SkillExp                =305,        //
	eText_YouSell				= 305, // 你卖出了%s,获得%s
	eText_YouLost                =306,        //    你失去了
	eText_Got                    =307,        //得到
	eText_BeginFight            =308,            //
	eText_ExitFight                =309,            //
	eCreate_NameError        =310,                //名字不合法
	eText_HPNoEnough        =311,
	eText_MPNoEnough        =312,
	eText_Motion_CantSing    =313,            //
	eText_PassiveSkill_NotUse=314,    //
	eText_StudySkill        =315,                //您学会了技能
	eText_PackMoneyCorrect	= 316,		// 包裹金钱超过上限，已进行回收
	eText_CannotUseSkillInCurStatus      = 317,        // 不能在当前状态下使用技能
	eText_StorageMoneyCorrect			 = 319, // 仓库金钱超过上限，已进行回收
	eText_TargetNotInTheView             = 320, // 目标不在视野内
	eText_Optional						 = 321, // (可选)
	eText_FCMOperateFailed				 = 322, // 防沉迷状态无法进行此操作
	eText_ItemUseLevel                   = 323, // 以你现在的等级还不能使用此物品
	eText_ItemUse_ProfessionLimit        = 324, // 职业不符，无法使用
	eText_Server_Chat_noGuild            = 325, // 你目前还没有加入任何公会！
	eText_Server_Chat_noTeam             = 326, // 你目前还没有加入任何队伍！
	eTextPlayer_PassiveNotUse            = 327, // 被动技能不可以被使用
	eTextBargainingError_OutRange           = 328,//目标距离太远，不可交易
	eTextDuelError_OutRange                 = 329,//目标距离太远，不可切磋
	eText_Chat_NotSeekEquip                    = 330, //不能查看其他玩家装备        
	eText_YouGet_N_S                        = 331, //你得到了 %d %s
	eUI_IsRelive        = 332, // 在复活你，是否接受？
	eUI_DeadReliveInfo  = 333, // 点击复活按钮，复活到最近的复活点
	eText_ReliveTimeOut = 334, // 复活有效时间已过，复活失败
	eText_MAXKILLMONSTER     = 335,  //杀怪数量已至当前的击杀上限
	//eClient_AddInfo_2slk_121        = 335,        //HERO[Version:%s] 
	eUI_CurPower = 336,//当前的能量
	eClient_customShortcutKeyRep = 337,    //此快捷键已经被占用了!
	eClient_Friend_ListInfoOutline    = 338,    //%-16s%-8s%-8s
	eLimitMapTime                    = 339,    // 倒计时:%d.%d
	eText_BeyondMoneyLimit		= 340,	// 您的金钱已经超过可携带的上限%d金，超出的金钱会在离线30分钟后被系统回收！
	//     eClient_FrdDlg_PK_Guild            = 341,    //公会保护模式
	eClient_PK_Team            = 341,    //保护模式:队伍
	eClient_PK_All               = 342,  //保护模式:全体
	eClient_PK_Sworn               = 343,  //保护模式:帮派
	eClient_PK_Guild                = 344,  //保护模式:帮派
	eClient_PK_League                  = 345,  //保护模式:同盟

	eText_PKRedNameCannotRelive     = 347, // 目标杀戮过重，无法被复活
	eText_BeyondPackMoneyLimit	= 348,	// 仓库存钱数已到达%d上限
	eCannotClearStatusByDead = 349,  //死亡后状态保留

	//////////////////////////////////////////////////////
	/// 技能作用范围
	eSkillCastType_Title			 = 350,		// 作用范围
	eSkillCastType_SingleTarget		 = 351,		// 单体
	eSkillCastType_PointCircle		 = 352,
	eSkillCastType_SelfCircle		 = 353,
	eSkillCastType_QuarterCirleFront = 354,
	eSkillCastType_PointAOE			 = 355,

	eText_QuitGameToLogin           = 356,  // 正在返回登陆界面，请稍后...\n
	eText_QuitGameToSelect          = 357,  // 正在返回角色界面，请稍后...\n
	eText_LevelNotReachable          = 358,  // 等级不够，无法查询此地图信息
	//eClient_send2GMUI_playerUseOtherTools    = 350,    //%s在游戏中使用外挂
	//eClient_send2GMUI_playerLock            = 351,    //%s被卡在了%s
	//eClient_send2GMUI_ChatSystem2Player        = 352,    //您已经法相信息到gm请等待处理
	//eClient_haveNotPackEx                    = 353,    //穷人没有能力打开附加包裹
	//eClient_DisDrome_Tip                    = 354, //下马提示
	//eClient_Minimap_show_eventInfoBen        = 355,    //正在进行:\n{#ff69cb34
	//eClient_Minimap_show_eventInfoEnd        = 356,    //#}
	//eClient_Minimap_show_eventNew            = 357,    //  {#ff00ff00=%s#} 活动开始 
	eClient_VassalName				= 359, // %s的奴仆
	eClient_PubItemDesc				= 360,  // 行酒令描述
	eClient_RoyalItemDesc			= 361,  // 黄榜令描述
	eClient_AddInfo_2slk_1         = 362,        //无效目标
	eClient_RegionMap_MousePosition         = 363,        //鼠标所指地图坐标  %d  %d
	eClient_IfUseItemForMount         = 364,        //是否需要对{#%x=%s#}使用{#%x=%s#}？
	eClient_AddInfo_2slk_5         = 365,        //您最多添加1个物品链接!
	eClient_AddInfo_Address         = 366,        //您最多添加1个地址链接
	eClient_IfUseItem				= 367,        //是否需要使用%s？
	eText_ChangeMapFailed_MapFull   = 368,      //目标地图人满为患，请稍后再试
	eClient_AddInfo_2slk_9         = 369,        //您没有加入任何工会
	eClient_AddInfo_2slk_11        = 370,        //被打断
	eClient_AddInfo_2slk_12        = 371,        //战斗中不能装备
	eClient_AddInfo_2slk_13        = 372,        //战斗中不能下线
	eClient_AddInfo_2slk_14        = 373,        //不能删除此物品?
	eClient_AddInfo_2slk_23        = 374,        //"提示"(小地图)
	eClient_AddInfo_2slk_27        = 375,        //"是否删除此物品?"
	eClient_AddInfo_2slk_28        = 376,        //"删除物品"

	////////////////////
	eTeam_TeamMate					= 377,		// 队友
	eTeam_InTeam					= 378,		// 队员
	eTeam_TeamLeader				= 379,		// 队长


	eText_CannotLootMount_InFight       = 380,  //战斗中无法驯服
	eText_CannotLootMount_WhenMounting  = 381,  //骑乘状态下无法驯服
	eText_CannotLootMount_CurrStatus    = 382,  //当前状态下无法驯服
	eClient_AddInfo_PFError        = 383,        //该地点无法寻路到达  
	eClient_AcceptNPC					= 384,  //%s的 %s 需要帮助，你可以前去看下
	eText_WaitForChangeMap              = 385,  // 等待传送中
	eText_ChangeMapServerBusy           = 386,  // 服务器繁忙
	eText_Interaction_InviteEmbrace     = 387,  //  %s 希望与您相依相偎，是否愿意？
	eText_QueryDiscardPet				= 388,  // 确定要放弃 %s 吗？
	eText_ChangeMountName				= 389,  // 输入骑宠名字
	eText_CannotShout_LevelNotMatch     = 390,  // 10级以下无法世界喊话
	eText_CannotCrossMapPathFind     = 391,  // 该NPC不支持跨地图寻路

	eTimeUnit_Second = 392, // 秒
	eTimeUnit_Minute = 393, // 分
	eTimeUnit_Hour = 394,   // 时
	eText_CannotCrossMapPathFindAddress = 395,   // 该地点无法跨地图寻路
	eClient_SetHotKey					= 396,  //输入按键设置->%s
	eClient_NotHotKey					= 397,  //未设置
	eClient_SucceedSetHotKey			= 399,  //按键设置成功

	eClient_AddInfo_2slk_86        = 398,        //%s 对你使用了物品 %s  
	
	eText_ZhenYingChat_NotInBattle	= 400,	// 尚未加入阵营

	eClient_AddInfo_2slk_126        = 401,        //%s %d 秒 
	eClient_NpcCoord_direct = 404,    //目的地

	eText_CreateChar_MaleShort      = 405,  // 精干
	eText_CreateChar_MaleTall       = 406,  // 魁梧
	eText_CreateChar_FemaleShort    = 407,  // 玲珑
	eText_CreateChar_FemaleTall     = 408,  // 高挑
	eText_NeedFillItem				= 409,  // 需要放入:{#%x=%s#}

	eText_IfUseLaBa					= 410,  // 世界喊话需要花费一个小喇叭，是否使用
	eText_HighShoutNeedLaBa			= 411,  // 只有携带小喇叭才能进行世界喊话
	eText_LoseOneLaBa				= 412,  // 失去一个小喇叭

	//eTellClient_IntegralMax = 409,//积分信息 积分最大值增加:%d,当前积分最大值:%d
	//eTellClient_Gm2Player_ShowName = 410,//GM发给PLAYER显示的名字
	//eTell_Client_ProjectCharDis = 411,//与护送怪物距离太远!
	//eClient_CantUseGood_ByDiffState             = 412, //当前状态不能使用物品
	eServer_picktime_eResultNotTeamHeader = 407,//"You`re not leader"    
	eText_CannotLoot_InFight					= 413,	// 战斗状态下无法采集
	eText_CannotLoot_WhenMounting				= 414,	// 骑乘状态下无法采集
	eText_LessNpcDialogTime = 415,  // 和NPC对话时间太快
	eText_SitFailed_InFighting					= 416,	// 战斗状态下无法坐下来
	eText_SitFailed_CurrStatus					= 417,	// 当前状态无法执行此操作
	eText_MaxPubTaskNumber						= 418,	// 同时最多只能接取%d个酒馆任务和皇榜任务
	//eText_SitFailed_WhenJumping					= 418,	// 不能在跳起来的时候坐下
	//eText_SitFailed_WhenMounting				= 419,	// 骑马状态下无法坐下来
	eText_RepairSuccess							= 419,	// 修理成功
	eText_GroupPanel_NearPlayerList				= 420,	// 附近玩家字符串格式
	eText_GroupPanel_TeamPlayerList				= 421,	// 玩家队伍字符串格式//eText_CreateCheckPeople              =61, //人物角色无法创建
	eText_LockSkill_No							= 422,	// 点击对快捷栏图标进行锁定
	eText_LockSkill_Yes							= 423,	// 点击取消快捷栏图标锁定
	//eText_YouGotAdditionalEncouragement = 423, //你获得额外的金钱和经验奖励。
	eText_AckNpc = 424, // 回复%s。
	eText_OperateFailedInCD = 425, // 操作过于频繁，请稍后尝试
	eUI_sCanNotFindString = 426, // 无法查找到搜索内容，请重新搜索
	eUI_CanNotDestroyActivedMount = 427, // 出战的坐骑无法被放生
	eText_TargetNoActiveMount	= 428, // 对方没有出战的坐骑
	eText_Point                            =    429,//点
	eText_Money_Gold	= 430, // 金
	eText_Money_Silver	= 431, // 银
	eText_Money_Copper	= 432, // 铜

	eText_Equip_Error_Sex			= 433, // 性别不符，无法装备
	eText_Equip_Error_Level			= 434, // 等级不符，无法装备
	eText_Equip_Error_Profession	= 435, // 职业不符，无法装备

	eClient_TrapName				= 436, //&lt;%s的陷阱&gt;

	eText_Follow_Cancel = 437,  // 取消跟随

	eText_PKMode_Peace = 438,  // 和平
	eText_PKMode_All = 439,  // 所有
	eText_PKMode_Guild = 440,  // 工会
	eText_PKMode_Team = 441,  // 组队

	eText_Mount_NotActived = 442, //先选择需要出战的坐骑
	eText_MountBag_NotSpace = 443, //兽栏没有空间

	eText_YouLost_N_S = 444, //失去 %d 个 %s

	eText_NotActiveAccounts = 445, //您的帐号未激活
	eText_NeedInputName = 446, // 请输入角色名

	eText_MaterialPackFull = 447,	//材料包裹已满
	eText_NormalPackFull = 448,		//普通包裹已满
	eText_TaskPackFull = 449,		//任务包裹已满

	eLogin_LoginHighFrequency = 450,		//您的登陆过于频繁，请等待 %d 秒后重新登录游戏
	eLogin_LoginQueue = 451,				//当前还有 %d 人排队，请耐心等待
	eLogin_UserAlreadyOnline = 452,		//您的帐号已在线，请等待 %d 秒后再此尝试登陆

	eText_NotChangePKMode = 454,		//15级前无法更改PK模式

	eSkillMaxLevel_Text  = 455,			//	技能最大等级

	/////////////////////////////////
	///捡到物品后，包裹即将不足的时候
	eText_AlmostFull_BagNormal		= 456,	// 普通包裹快满了，还有..个位置
	eText_AlmostFull_BagMaterial	= 457,	// 材料包裹快满了，还有..个位置
	eText_AlmostFull_BagTask		= 458,	// 任务包裹快满了，还有..个位置

	/////////////////////////////////
	///采集技能等级判断
	eText_LootFailed_HerbLevelNotMatch  = 459,  // 采药技能等级不够,需要技能等级%d级
	eText_LootFailed_MineLevelNotMatch  = 460,  // 挖矿技能等级不够,需要技能等级%d级
	eText_LootFailed_InsectLevelNotMatch= 461,  // 捕虫技能等级不够,需要技能等级%d级
	eText_LootFailed_VigorNotEnough     = 462,  // 精力不足
	eText_MountEnjoymentNotEnough		= 463,	// 坐骑生命不够

	/////////////////////////////////
	///包裹拾取
	eText_PackagePickUp_NotExist        = 464,  // 该物品已经被拾取
	eText_PackagePickUp_CannotPick      = 465,  // 该物品不属于你
	eText_PackagePickUp_AssignItem      = 466,  // [%s]被分配给了 %s
	eText_PackagePickUp_AssignFailed    = 467,  // 分配失败，对方已下线

	eText_Mount_Mate_Unable             = 468,  // 交配不能     为偷懒，这2 String是连着的
	eText_Mount_Mate_Able               = 469,

	eText_NoMoneyForWorldChat			= 470,  // 您的金钱不够，无法进行世界聊天

	eText_NoSkillForHerb				= 472,  // 未学会采药技能
	eText_NoSkillForMine				= 473,  // 未学会采矿技能
	eText_NoSkillForCatch				= 474,  // 未学会捕捉技能

	/////////////////////////////////
	///配方
	eText_RecipeAlreadyExist			= 475, // 已经存在
	eText_RecipeFull					= 476, // 满了
	eText_RecipeNoThis					= 477, // 没有此配方
	eText_RecipeUnknown					= 478, // 未知错误

	eText_ProduceSkillNpcDesc           = 479, // %s宗师:%s
	eText_Time							= 488, // 时间	

	/////////////////////////////////
	///坐骑
	eMountError_FullMount				= 490, // 坐骑数量已满
	eMountError_ActiveMountNotSupport	= 491, // 出战中的坐骑不能进行此操作

	eText_CurrentEnergy                 = 492, // 当前活力 %d
	eText_CurrentVigor                  = 493, // 当前精力 %d
	eText_NotEnoughVigorToHerb          = 494, // 精力值不够，无法采集草药
	eText_NotEnoughVigorToMine          = 495, // 精力值不够，无法采集矿石
	eText_NotEnoughVigorToInsect        = 496, // 精力值不够，无法捕虫
	/////////////////////////////////
	///装备升星
	eText_Intensify_MaterialItemLevel = 499, // 辅助材料等级不够
	eText_Intensify_StarSuccess		  = 500, // 装备升星成功
	eText_Intensify_StarFailed		  = 501, // 装备升星失败
	eText_Intensify_EquipNotMatch	  =	502, // 装备不匹配
	eText_Intensify_RepGem			  = 503, // 宝石等级不够
	eText_Intensify_MaxLevel		  = 504, // 强化到了最大等级
	eText_Intensify_NoItem			  = 505, // 物品不存在
	eText_Intensify_NoMoney			  = 507, // 没有足够的钱
	eText_Intensify_FailedItem		  = 508, // 错误的宝石材料
	eText_Intensify_AlreadyIdentify   = 509, // 已经鉴定过了
	eText_Intensify_NotIdentify		  = 510, // 还没有鉴定
	eText_Intensify_AlreadyKaiGuang	  = 511, // 开光过了
	eText_Intensify_IdentifySuccess	  = 512, // 鉴定成功
	eText_Intensify_KaiGuangSuccess	  = 513, // 开光成功
	eText_Intensify_CannotIdentify	  = 514, // 不能被鉴定

	//////////////////////////////////
	///鉴定/开光字串
	eText_Identify					  = 515, // 鉴定
	eText_KaiGuang					  = 516, // 开光
	eText_CannotIdentify              = 519, //不能被开光

	eText_MoveStarUpgrade_Progress	  = 520, // 升级

	eText_StarMaterialUpgrade_Progress= 521, // 合成
	eText_SpecialRepair_Progress		= 524, //特修
	eText_Decompound_Progress			= 525, //分解
	eText_Identify_Progress				= 526, //鉴定
	eText_OpenLight_Progress			= 527, //开光
	eText_Upgrade_Progress				= 528, //升阶
	eText_MoveStar_Progress				= 529, //移星


	eWarning_Cannot_Soul_ItemLowTo40	= 530,//40级以下装备无法铭刻
	eWarning_Cannot_Soul_Repeat			= 531,//该装备已经铭刻过，无法再次铭刻
	eText_Soul_Soul						= 532,//铭刻
	eText_Soul_Soul_Success				= 533,//铭刻成功
	eWarning_Cannot_Soul_PlayerLowTo45	= 534,//45级以下玩家无法铭刻
	eText_XiZi_Success					= 536,//装备洗紫成功
	eText_Recycle_Success				= 537,//装备回收成功
	eText_OpenLight_Success				= 538,//装备鎏金成功
	eWarning_CannotOpenLightRepeat		= 539,//装备已经鎏金过，无法再次鎏金
	eWarning_Hole_Full					= 540,//装备打孔数量已经到达最大数目，无法再次打孔

	eText_Hole_Success					= 541,//打孔成功
	eText_Maintain_Success				= 542,//装备保值成功
	eText_CrossMaintain_Success			= 543,//跨级保值成功

	eWarning_OpenLight_PlayerLowTo60	= 544,//玩家等级未达到60级无法使用鎏金
	eWarning_OpenLight_ItemLowTo60		= 545,//装备等级未达到60级无法进行鎏金
	eWarning_OpenLight_NoGolden			= 546,//装备品质未达到金色无法进行鎏金

	eWarning_ReOpenLight_PlayerLowTo60	= 547,//玩家等级未达到60级无法使用鎏金回炉
	eWarning_ReOpenLight_ItemLowTo60	= 548,//装备等级未达到60级无法进行鎏金回炉
	eWarning_ReOpenLight_NoPurple		= 549,//装备品质未达到紫色无法进行鎏金回炉


	eText_Gem_Success					= 550,//宝石镶嵌成功
	eText_GemRemove_Success				= 551,//宝石拆卸成功
	eWarning_Gem_Equip_First			= 552,//请先放入需要镶嵌的装备
	eText_GemReplace_Success			= 553,//宝石替换成功
	eText_GemUp_Success					= 554,//宝石升级成功
	eWarning_GemTypeError				= 555,//宝石类型不符，无法镶嵌
	eWarning_NoEmptyHole				= 556,//没有空余的宝石孔
	eWarning_GemInHole					= 557,//该孔已放入宝石
	eWarning_BagFull                    = 558,//您的背包已满，请先清理背包空间后再执行此操作
	eWarning_NotGemInHole				= 559,//该孔内无宝石，无法替换



	eText_HookOffline_Affirm            = 560,  // 是否确认开始离线挂机

	eWarning_Maintain_ItemLevel				= 561,//装备等级未达到60级无法保值
	eWarning_Maintain_SamePart				= 562,//部件相同的装备才可以进行保值
	eWarning_Maintain_PurpleItem			= 563,//请放入紫色装备
	eWarning_Maintain_GoldItem				= 564,//请放入黄色或紫色装备
	eWarning_CrossMaintain_Level			= 565,//跨级保值只能向上跨一级
	eWarning_Maintain_PlayerLevel			= 566,//玩家等级未达到60级无法进行保值
	eWarning_Maintain_NotSameLevel			= 567,//装备等级不同无法进行保值

	eWarning_Recycle_GoldItem				= 568,//只有金色以上品质的装备才能回收

	eWarning_Charm_BlueItem					= 569,//只有蓝色品质的装备才能吸收
	eWarning_Charm_Success					= 570,//符文吸收成功
	eWarning_Charm_Fail						= 571,//符文吸收失败

	eWarning_Amulet_ItemType				= 572,//只有护身符才能上色
	eWarning_Amulet_Symbol					= 573,//请放入吸入蓝色属性的符文
	eText_Amulet_Left						= 574,//该护身符还能上色:%d次
	eWarning_Amulet_Success					= 575,//符文吸收成功

	eWarning_GemUp_Success					= 576,//宝石升级成功
	eWarning_GemUp_ErrorGem					= 577,//该宝石不能升级
	eWarning_GemUp_ErrorType				= 578,//只有宝石才可以在这里升级

	eWarning_XSJUp_ErrorType				= 579,//洗石剂配置成功
	eWarning_XSJUp_Success					= 580,//洗石剂配置成功
	eWarning_XSJUp_LackMaterial				= 581,//材料不足无法配置

	eText_Star_Star							= 582,//%d星
	eWarning_AutoStar_LackMaterial			= 583,//材料不足无法继续升星
	eWarning_AutoStar_LackMoney				= 584,//金钱不足无法继续升星
	eWarning_AutoStar_Ok					= 585,//已经升到%d星
	eWarning_HaveSameBaseRand				= 586,//玉佩无法开光同类型属性

	//////////////////////////////////

	//排行榜
	eText_Rank_MeLevelIn = 589,        //<String Id="589" Value="您的当前等级为%s"/>
	eText_Rank_MeLevelOut = 590,         //<String Id="590" Value="您暂时还不在排行榜之内，请再接再厉!"/>

	eText_Tip_SoulStamp               = 591, // （铭刻+%d）
	eText_Info_SoulStamp              = 592, //该装备无法铸魂

	eText_Hole_ItemLevel              = 593, //装备等级不足10级，无法打孔

	// 物品名字前缀
	ePreItemText_LiangPin			  = 600, // 良品
	ePreItemText_JingPin			  = 601, // 精品
	ePreItemText_JiPin				  = 602, // 极品
	ePreItemText_ShenPin			  = 603, // 神品

	/////////////////////////////////
	// 坐骑 生活技能 离线挂机 相关
	eText_MountGeneration_First         = 630, // 初代
	eText_MountGeneration_Second        = 631, // 二代
	eText_MountRestore_NoMoney          = 632, // 金钱不足无法治疗坐骑
	eText_MountBreed_MasterLevel        = 633, // 坐骑繁殖主坐骑等级小于60级
	eText_MountBreed_NoMoney            = 634, // 坐骑繁殖金钱不足
	eText_MountBreed_Unable             = 635, // 坐骑无法进行繁殖
	eText_MountBreed_NoNext             = 636, // 无法进行坐骑繁殖，主坐骑没有下一代马
	eText_MountBreed_Success            = 637, // 坐骑繁殖成功
	eText_MountSkill_SlotAlreadyOpen    = 638, // 已经开启技能槽
	eText_MountSkill_SlotNoSkill        = 639, // 所在位置没有技能

	eText_BizSkill_NotEnoughExp         = 640, // 熟练度不足无法提高生活技能
	eText_BizSkill_AlreadyFull          = 641, // 生活技能已满

	eText_MountLevel_OverPlayer         = 642, // 坐骑等级高于人物等级5级，无法增加经验

	eText_Hook_NotHasLevel              = 643, // 挂机档次错误
	eText_Hook_NoMoneyToGetExp          = 644, // 金钱不足无法领取经验

	eText_UseItem_NotEnoughMountLevel   = 645, // 坐骑等级不足无法使用道具
	eText_UseItem_MountNotSelect        = 646, // 请先选中您要使用此道具的坐骑

	eText_PlsInputRightXY				= 650, //请输入想要前往地点的坐标

	eText_NoActiveMountSkillHole		= 651, //坐骑技能槽未激活，无法使用
	eText_MountLevel_HuanTongShu        = 660, // 坐骑携带等级小于40级无法使用还童书
	eText_MountLevel_HuanLongShu        = 661, // 坐骑携带等级小于80级无法使用还龙书
	eText_Mount_CantUseHuanLongShu      = 662, // 该坐骑无法使用还龙书
	eText_OneKeySuit_NoSet              = 663, // 没有该一键换装的设置
	eText_Honour_TopLimit               = 664, // 今日荣誉值达到上限
	eText_NoOffline_HookExp             = 665, // 没有离线挂机经验
	eText_OfflineHook_LevelLess         = 666, // 离线挂机等级不足
	eText_ReliveOrigin_NoMoney          = 667, // 金钱不足无法原地复活
	eText_MountType_CannotBreed         = 668, // 坐骑类型不同无法进行繁殖

	eText_BeKilled_NoHyperlink          = 669, // 你被 %s 杀死了
	eText_LevelNotmeet                  = 670, //等级不足
	eText_Hole_Failed                   = 680, //打孔失败
	eText_EquipNoIdentity               = 681, //该装备无法鉴定
	eText_BuhlNoExist                   = 682, //镶嵌符不存在
	eText_Gem_UpdateFailed              = 683, //宝石升级失败
	eText_Gem_SameType                  = 684, //同类型宝石只能镶嵌一个

	///熟练度
	eText_SkillPoint					= 701, // 熟练度
	eText_CaoYao_SkillPoint				= 702, // 0:草药
	eText_ZhuBao_SkillPoint				= 703, // 1:珠宝
	eText_DuanZao_SkillPoint		    = 704, // 2:锻造
	eText_ZhuJia_SkillPoint				= 705, // 3:铸甲
	eText_GongYi_SkillPoint				= 706, // 4:工艺
	eText_XunMa_SkillPoint				= 707, // 5:驯马
	eText_CaiYao_SkillPoint				= 708, // 6:采药
	eText_CaiKuang_SkillPoint			= 709, // 7:采矿
	eText_BuChong_SkillPoint			= 710, // 8:捕虫
	// 捕捉不要

	// 生活技能描述
	eText_CaoYao_Describe	            = 720,
	eText_ZhuBao_Describe	            = 721,
	eText_DuanZao_Describe	            = 722,
	eText_ZhuJia_Describe	            = 723,
	eText_GongYi_Describe	            = 724,
	eText_XunMa_Describe	            = 725,
	eText_CaiKuang_Describe	            = 726,
	eText_CaiYao_Describe	            = 727,
	eText_BuZhuo_Describe	            = 728,

	eText_CaoYao_Dcrb_MaxLevel	            = 740,
	eText_ZhuBao_Dcrb_MaxLevel	            = 741,
	eText_DuanZao_Dcrb_MaxLevel	            = 742,
	eText_ZhuJia_Dcrb_MaxLevel	            = 743,
	eText_GongYi_Dcrb_MaxLevel	            = 744,
	eText_XunMa_Dcrb_MaxLevel	            = 745,
	eText_CaiKuang_Dcrb_MaxLevel	        = 746,
	eText_CaiYao_Dcrb_MaxLevel	            = 747,
	eText_BuZhuo_Dcrb_MaxLevel	            = 748,

	eCreate_BirthdayError	= 800, //创建角色时生日信息有误

	eText_friend_sprite_name = 801, //小精灵名字
	eText_friend_sprite_tips = 802, //小精灵tips
	eText_friend_sprite_content = 803,

	eText_Mood_Text_TooLong = 804,	//心情长度过长。

	eText_Button_Tip_Mood = 805, //心情和称号编辑
	eText_Button_Tip_AddFriend = 806, //添加好友
	eText_Button_Tip_RemoveFriend = 807, //删除好友
	eText_Button_Tip_AddHeimingdan = 808, //添加黑名单
	eText_Button_Tip_Search = 809, //好友查询
	eText_Button_Tip_AddClass = 810, //增加好友分组
	eText_Friend_AddGroupMax  = 811, //分组数量已经为最大值
	eText_Friend_FindPlayerMax = 812, //玩家大于30级才能使用查询

	//换装提示
	eChangeSuitFail                   = 900,//换装失败
	eChangeSuitSuccess                = 901,//换装成功
	eChangeSuitCD                     = 902,//请稍后再次尝试
	eChangeSuitSave                   = 903,//保存成功

	eText_ExpressionAction_CoolDown	  = 904, // 操作太快，请稍后再次尝试
	eText_PreventWallow_Account		  = 906, // 防沉迷系统提示:您的帐号已被列入防沉迷

	eText_Rank_Level		  = 910, //<String Id="910" Value="本榜收录等级排名前200名的玩家，如果您在本榜有排名请到王城"/>
	eText_Rank_Fortune		  = 911, //<String Id="911" Value="本榜收录财富排名前200名的玩家，如果您在本榜有排名请到王城"/>
	eText_Rank_Fame		  = 912, //<String Id="912" Value="本榜收录名望排名前200名的玩家，如果您在本榜有排名请到王城"/>
	eText_Rank_Honor		  = 913, //<String Id="913" Value="本榜收录荣誉排名前200名的玩家，如果您在本榜有排名请到王城"/>
	eText_Rank_Offer		  = 914, //<String Id="914" Value="本榜收录帮贡排名前200名的玩家，如果您在本榜有排名请到王城"/>
	eText_Rank_Charm		  = 915, //<String Id="915" Value="本榜收录魅力排名前200名的玩家，如果您在本榜有排名请到王城"/>
	eText_Rank_PK		  = 916, //<String Id="916" Value="本榜收录红名排名前200名的玩家，如果您在本榜有排名请到王城"/>                
	eText_Rank_Kill		  = 917, //<String Id="917" Value="本榜收录杀敌排名前200名的玩家，如果您在本榜有排名请到王城"/>
	eText_Rank_GuildPower		  = 918, //<String Id="918" Value="本榜收录帮会排名前200名的帮会，如果您在本榜有排名请到王城"/>
	eText_Rank_CountryPower		  = 919, //<String Id="919" Value="本榜收录国家实力排名，如果您在本榜有排名请到王城"/>
	eText_Rank_Rose		  = 920, //<String Id="920" Value="本榜收录玫瑰排名前200名的玩家，如果您在本榜有排名请到王城"/>
	eText_Rank_Love		  = 921, //<String Id="921" Value="本榜收录恩爱排名前200名的玩家，如果您在本榜有排名请到王城"/>
	eText_Rank_Teacher		  = 922, //<String Id="922" Value="本榜收录名师实力排名前200名的玩家，如果您在本榜有排名请到王城"/>
	eText_Rank_BattleLevel		  = 923, //<String Id="923" Value="本榜收录战场等级排名前200名的玩家，如果您在本榜有排名请到王城"/>
	eText_Rank_BattlePoint		  = 924, //<String Id="924" Value="本榜收录战场积分排名前200名的玩家，如果您在本榜有排名请到王城"/>
	eText_Rank_Intelligence		  = 925, //<String Id="925" Value="本榜收录智力竞赛排名前200名的玩家，如果您在本榜有排名请到王城"/>
	eText_Rank_Fast		  = 926, //<String Id="926" Value="本榜收录快马加鞭排名前200名的玩家，如果您在本榜有排名请到王城"/>
	eText_Rank_Mount		  = 927, //<String Id="927" Value="本榜收录神兽四起排名前200名的玩家，如果您在本榜有排名请到王城"/>
	eText_Rank_Hero		  = 928, //<String Id="928" Value="本榜收录群雄弑神排名前200名的玩家，如果您在本榜有排名请到王城"/>
	eText_Rank_Horn		  = 929, //<String Id="929" Value="本榜收录小喇叭排名前200名的玩家，如果您在本榜有排名请到王城"/>
	eText_Rank_Firework		  = 930, //<String Id="930" Value="本榜收录烟花排名前200名的玩家，如果您在本榜有排名请到王城"/>
	eText_Rank_Jiangzhou		  = 931, //<String Id="931" Value="本榜收录江州劫法场排名前200名的玩家，如果您在本榜有排名请到王城"/>
	eText_Rank_Shihuang		  = 932, //<String Id="932" Value="本榜收录秦始皇陵排名前200名的玩家，如果您在本榜有排名请到王城"/>
	eText_Rank_Wanghai		  = 933, //<String Id="933" Value="本榜收录无渊亡海排名前200名的玩家，如果您在本榜有排名请到王城"/>
	eText_Rank_Qixing		  = 934, //<String Id="934" Value="本榜收录夜落七星排名前200名的玩家，如果您在本榜有排名请到王城"/>
	eText_Rank_Baihu		  = 935, //<String Id="935" Value="本榜收录白虎岭排名前200名的玩家，如果您在本榜有排名请到王城"/>
	eText_Rank_Qinlong		  = 936, //<String Id="936" Value="本榜收录青龙道排名前200名的玩家，如果您在本榜有排名请到王城"/>
	eText_Rank_Fenghuang		  = 937, //<String Id="937" Value="本榜收录凤凰山排名前200名的玩家，如果您在本榜有排名请到王城"/>
	eText_Rank_Xuanwu		  = 938, //<String Id="938" Value="本榜收录玄武岛排名前200名的玩家，如果您在本榜有排名请到王城"/>
	eText_Rank_GuildPoint	= 939, //<String Id="939" Value="本榜收录帮派积分排名前200名的帮派，您可以查看帮派积分排行信息。"/>

	eText_Ralation_AddRelationCoolTime = 950,//<String Id="950" Value="您还需要等候%d:%d:%d才能添加%s关系！"/>
	eText_Ralation_Marriage = 951,//<String Id="951" Value="夫妻"/>
	eText_Ralation_Teacher = 952,//<String Id="952" Value="师傅"/>
	eText_Ralation_Student = 953,//<String Id="953" Value="徒弟"/>
	eText_Ralation_Brother = 954,//<String Id="954" Value="结拜兄弟"/>
	eText_Ralation_Husband = 955,//<String Id="954" Value="丈夫"/>
	eText_Ralation_Wife = 956,//<String Id="954" Value="妻子"/>

	eText_Guild_Announcement = 960,	//帮会公告提示
	eText_Guild_Creed = 961,	//帮会宗旨提示
	eText_Guild_TellCreed = 962, //修改帮会宗旨的提示
	eText_Guild_Creed_Cd_Failed = 963, //cd时间未到，不能更改帮会宗旨
	eText_Guild_Creed_Money_Failed = 964, //金钱不够，不能更改帮会宗旨

	eText_Bull					= 1000,				//【公告】
	eText_SystemBull            =1001,            //【系统】
	eText_Chat_0                =1002,            //【密语】
	eText_Chat_2                = 1004,            //【队伍】
	eText_Chat_3                = 1005,            //【帮派】
	eText_Chat_4                = 1006,            //【帮派】
	eText_Chat_5                = 1007,            //【世界】
	eText_Chat_6                = 1008,            //【附近】
	eChatType_Normal                = 1009,    // 附近
	eChatType_Guild                    = 1010,    // 帮派
	eChatType_Team                    = 1011,    // 队伍
	eChatType_Private                = 1012,    // 密语
	//     eChatType_GM                    = 1013,    // GM
	eChatType_Shout				=1014,//帮派    
	eChatType_HightShout		=1015,//世界    
	eText_Chat_Alignment        = 1016,            //【同盟】
	eChatType_Alignment			=1017,//同盟    
	eText_ElementSuitArmour		= 1018,	//属性套装
	eText_SkillSuitArmour		= 1019,	//技能套装
	eText_Chat_ZhenYing			= 1020, //【阵营】
	eChatType_ZhenYing			= 1021, //阵营
	eChatType_XiaoLaBa			= 1025, //小喇叭图标
	eChatType_Near              = 1026, ////【附近】
	eChatType_Gang              = 1027, //[公会图片]

	eServer_chat_particular_vip1            = 1029,    //小道消息1
	eChatType_CountryString					= 1032,    // 国家字串
	eChatType_Country					= 1034,    // 国家图标
	eChatType_GuanYuan					= 1035,    // 官员图标
	//eClinet_marry_husband            = 1039,    //的老公
	//eClinet_marry_wife                = 1040,    //的老婆
	//eClient_prentice                = 1041,    //的徒弟
	eClient_Private_Begin               = 1042, //【~
	eClient_Chat_DuiNiShuo            = 1043,    //_】对你说:
	eClient_Chat_NiDui            = 1044,    //你对【~
	eClient_Chat_Shuo            = 1045,    //_】说:
	eClient_Chat_function_4            = 1046,    //对
	eText_Chat_Spec_LeftMark            = 1047,    //【
	eText_Chat_Spec_RightMark            = 1048,    //】
	eClient_Chat_Begin            = 1049,    //:
	eClient_Chat_Head_End            = 1050,    //_】:
	eClient_Player_Name_End            = 1051,    //]
	//     eClient_AddInfo_2slk_147        = 1052,        //%s对你说:%s\n 

	eText_YouGetXGlory					= 1056,		// 你获得了%d点荣誉		
	eText_YouGetXCountryScore			= 1057,		// 你获得了%d点国战积分
	eText_YouLoseXGlory					= 1058,		// 你失去了%d点荣誉
	eText_YouLoseXCountryScore			= 1059,		// 你失去了%d点国战积分
	//////////////////////////////////
	///称号
	eTitle_TileNotExist					= 1060,		// 没有此称号
	eTitle_AlreadyExist					= 1061,		// 已经拥有该称号了
	eTitle_ErrorId						= 1062,		// 错误的称号
	eTitle_Full							= 1063,		// 称号数量已满
	eTitle_UnknownError					= 1064,		// 未知的称号
	eTitle_RemoveSuccess				= 1065,		// 称号移除成功
	eTitle_AddSuccess					= 1066,		// 称号添加成功
	eTitle_CannotUplevel				= 1067,		// 称号[%s]不能升级
	eTitle_NextTitleName				= 1068,		// 称号[%s]

	eText_YouGetXExploit				= 1069,		// 你获得了%d点功勋
	eText_YouGetXReputation				= 1070,		// 你获得了%d点名望
	eText_YouLoseXExploit				= 1071,		// 你失去了%d点功勋
	eText_YouLoseXReputation			= 1072,		// 你失去了%d点名望
	eText_ChatSkillLevelUp				= 1073,		// %s等级提升到%d级
	eText_LifeSkillLevelupPoint			= 1074,		// %s提升了%d点
	/////////////////////////////////
	///熟练度补充
	eText_CaiKuangSkillPoint			= 1075,		// 采矿
	eText_CaiYaoSkillPoint				= 1076,		// 采药

	eText_YouGetGuildOffer				= 1077,		// 你获得了%d点帮贡
	eText_YouLoseGuildOffer				= 1078,		// 你失去了%d点帮贡
	eExchange_NotGuildOffer				= 1079,		// 帮贡不够，不能进行此项操作
	eText_YouGetAreaReputation			= 1080,		// 你获得了%d点%s声望
	eText_YouGet						= 1081,		// 你获得了
	eText_TitleNoUpdate                 = 1082,     //该称号无法升级
	eText_WeiWang1						= 1083,		// 威望
	eText_JiaoZiGet                     = 1084,     //获得了%s
	eText_JiaoZiLost                    = 1085,     //失去了%s
	eText_JiaoZiGold                    = 1086,     //金交子
	eText_JiaoZiSilver                  = 1087,     //银交子
	eText_JiaoZiCopper                  = 1088,     //铜交子

	eText_DaoHangStifle                 = 1091,     //道法压制 
	eText_DaoHangResist                 = 1092,     //道法抵抗

	eText_TalismanEquipSucess           = 1100,     //法宝装备成功
	eText_TalismanEquipFaild            = 1101,     //法宝装备失败
	eText_TalismanDaoHangNoEnough       = 1102,     //法宝道行不足
	eText_TalismanUnEquipFaild          = 1103,     //法宝卸载失败
	eText_TalismanDaoHangLimilt         = 1104,     //法宝道行限制:%d
	eText_TalismanQuility               = 1105,     //法宝品质:%s
	eText_TalismanNormal                = 1106,     //法宝:凡品
	eText_TalismanRight                 = 1107,     //法宝:良品
	eText_TalismanNicity                = 1108,     //法宝: 精品
	eText_TalismanImmortal              = 1109,     //法宝: 仙物
	eText_TalismanGold                  = 1110,     //法宝: 神器
	eText_TalismanBound                 = 1111,     //未绑定
	eText_TalismanNimBus                = 1112,     //灵气:%d/%d
	eText_TalismanNimBusRate            = 1113,     //灵气回复率:%d/秒

	eText_TargetInTeam            =1301,    //对方已在其他队伍中，组队失败
	eText_FindNotPlayer            =1302,    //    对方已下线，组队失败
	eText_AskJoinTeam            =1305,    //    {#fffa00=  %s#}申请加入队伍
	eText_TeamFail_TargetCancel            = 1306,    //对方拒绝了组队申请
	eText_TargetTeamFull                =1307,    //    对方队伍人数已满，申请失败
	eText_TeamFull                =1308,    //    队伍人数达到上限,邀请失败

	eText_InviteTeam				= 1309,//邀请组队
	eText_ApplyTeam				= 1310,//申请入队
	eText_Team_CannotChangeTeamMode = 1311, // 只有队长才能更改组队模式
	eText_Team_CannotChangeQuality  = 1312, // 只有队长才能更改分配品质
	eText_Team_NoApplyPages			= 1313, // 1/1
	eText_Team_HeadInviteFollow		= 1314, // 队长邀请你跟随？
	eText_Team_AgreeFollow			= 1315,	// %s同意跟随
	eText_Team_RefuseFollow			= 1316, // %s拒绝跟随
	eText_Team_CancelFollow			= 1317, // %s取消跟随
	eText_Team_InviteFollowInfoSend = 1318,	// 你已发出组队跟随邀请
	eText_Team_LeaderCancelFollow	= 1319, // 队长取消跟随
	eText_Team_JoinOneTeamSuccess	= 1320, // 你已成功加入了%s的队伍
	eText_Team_LeaveTeamYESNO		= 1321,	// 确定离开队伍
	eText_Team_DisbandTeamYESNO		= 1322,	// 确定要解散队伍
	eText_Team_KickSomeoneOffYESNO	= 1323,	// 你确定要将%s踢出队伍？
	eText_Team_PromotLeaderYESNO	= 1324, // 你确定要将队友%s提升为队长？
	eText_Team_ClearListYESNO		= 1325, // 确定要清空申请列表
	eText_Team_NoTeam               = 1326, // 你没有队伍
	eText_NearPlayerTeam          = 1327, //有队伍
	eText_NearPlayerNoTeam            = 1328, //无队伍		

	eText_TeamFail_NotSameCountry           = 1350,    //不同国家不能组队

	eText_GetAchievement			= 1351, // 你获得了%d成就点

	eText_Search_OfflineOrNotExist	= 1402,//"{#ffffffff=对方不在线或者不存在#}"/>
	eText_Team_Apply                        = 1403,    //发出组队申请    
	eText_TeamFail                          = 1404,    //    
	eText_TeamScuscc                        = 1405,    //
	eText_AddTeam_Ask                       = 1406,    //邀请加入队伍，是否同意？
	eUI_GuildCallOn                         = 1407,    //    
	eUI_SendTeam_fail                       = 1408,    //发送组队申请失败
	eUI_SendTeam                            = 1409,    //发送组队
	eText_NoneAddMe                         = 1410,    //不能加自己为好友
	eText_Friend							= 1411,	 //好友
	eText_Chouren							= 1412,  //仇人
	//     eText_AddFriRepeat                    = 1411,    //已经添加了%s为好友[删]
	//     eText_FriNotOnline                    = 1412,    //玩家%s不在线或你在其黑名单中[删]
	eText_FriOutLine                    = 1413,  //好友已经离线
	eText_FriCutDownLine                = 1414,    //(好友)下线了
	eText_TeamFail_AssignMode            = 1415,    //分配模式以改，组队失败 
	eText_Server_TeamTargetResquesting    = 1416,    //该玩家正在被邀请中...
	eText_Server_TeamRequestOnlyHeader    = 1417,    //只有队长才可以邀请别人加入队伍...[删]
	eText_ChouRenCutDownLine			=	1418,	//仇人 %s 下线了
	eText_TeamModeTips_FreeMode         = 1419,     //分配模式:自由拾取
	eText_TeamModeTips_AssignMode       = 1420,     //分配模式:队长分配(%s)
	eText_TeamModeTips_TeamMode         = 1421,     //分配模式:队伍分配(%s)
	eText_UpgradeTeam_Succeed            = 1422,    //%s被提升为队长
	eText_UpgradeTeam_Faild                = 1423,    //提升%s为队长失败
	eTextPlayer_GroupAssignMode0        = 1425,//%s邀请你加入队伍，你同意吗?\n队伍分配模式为: {#FFFFFF00=自由模式#}
	eTextPlayer_GroupAssignMode1        = 1426,//%s邀请你加入队伍，你同意吗?\n队伍分配模式为: {#FFFFFF00=队伍模式#}
	eTextPlayer_GroupAssignMode2        = 1427,//%s邀请你加入队伍，你同意吗?\n队伍分配模式为: {#FFFFFF00=随即模式#}
	eTextPlayer_GroupAssignMode3        = 1428,//%s邀请你加入队伍，你同意吗?\n队伍分配模式为: {#FFFFFF00=分配模式#}
	eTextPlayer_Change_AssignMode0        = 1429,//模式更改为:{#FFFFFF00=自由模式#}
	eTextPlayer_Change_AssignMode1        = 1430,//模式更改为:{#FFFFFF00=队伍模式#}
	eTextPlayer_Change_AssignMode2        = 1431,//模式更改为:{#FFFFFF00=随即模式#}
	eTextPlayer_Change_AssignMode3        = 1432,//模式更改为:{#FFFFFF00=分配模式#}
	eText_Client_show_assignMode_Freedom    = 1437, //当前队伍为:自由模式
	eText_Client_show_assignMode_Team        = 1438, //当前队伍为:队伍模式
	eText_Client_show_assignMode_Random        = 1439, //当前队伍为:随机模式
	eText_Client_show_assignMode_Assign        = 1440, //当前队伍为:分配模式
	eClinet_CorpsAssignMode0        = 1441,//%s邀请你加入团队，你同意吗?\n团队分配模式为: {#FFFFFF00=自由模式#}
	eClinet_CorpsAssignMode1        = 1442,//%s邀请你加入团队，你同意吗?\n团队分配模式为: {#FFFFFF00=队伍模式#}
	eClinet_CorpsAssignMode2        = 1443,//%s邀请你加入团队，你同意吗?\n团队分配模式为: {#FFFFFF00=随即模式#}
	eClinet_CorpsAssignMode3        = 1444,//%s邀请你加入团队，你同意吗?\n团队分配模式为: {#FFFFFF00=分配模式#}
	eText_ClientCrops_assignMode0        = 1449, //当前团队为:自由模式
	eText_ClientCrops_assignMode1        = 1450, //当前团队为:队伍模式
	eText_ClientCrops_assignMode2        = 1451, //当前团队为:随机模式
	eText_ClientCrops_assignMode3        = 1452, //当前团队为:分配模式
	eTextServer_Refuse_Change_AssignMode    = 1453,//%s拒绝了此次模式更改
	eTextServer_All_Refuse_change_assignmode= 1454,//所有人都放弃%s归属于队伍.
	eTextServer_Item_Adscripte_People        = 1455,//%s归属于%s
	eTextServer_People_Agree_changemode        = 1456,//%s同意了此次模式更改
	eTextServer_Select_Get_assign            = 1457,//%s选择了索取
	eTextServer_Select_Giveup_assign        = 1458,//%s放弃了
	eCorps_KickCorper                = 1459, //不能把自己踢出队伍
	eCorps_CorperCovManiple            = 1460, //不能把自己提为小队长
	eCorps_UpCorper                    = 1461, //提升为团长出错
	eClient_AddInfo_2slk_4         = 1462,        //团以满
	eCorps_MovePlayer                = 1463, //移动必须对2人
	eCorps_AuthorityError            = 1464, //权限不够
	eTextPlayer_InterchangeReqQue        = 1465,//%s 邀请你切磋武艺，是否愿意一试身手?
	eTextPlayer_InterchangeReqMsg       = 1466,//切磋邀请
	eTextPlayer_Underdog                = 1467,//你输给了%s
	eClient_AddInfo_2slk_115        = 1468,        //距离太远，不能邀请切磋。
	eClient_AddInfo_2slk_116        = 1469,        //对方正在切磋中。
	eClient_AddInfo_2slk_127        = 1470,        //%s在切磋中战胜了%s 
	eClient_AddInfo_2slk_129        = 1471,        //你正在离开切磋区域,%d秒后你将输掉比赛 
	eClient_Error_Me_InFightCanNotDuel        = 1472, // 战斗状态不能切磋
	eClient_Error_Target_InFightCanNotDuel    = 1473, // 对方在战斗状态不能切磋
	eClient_AddInfo_2slk_128        = 1474,        //未知目标 
	eText_Client_IsDel_Friend                = 1475,    //你确定要删除%s
	eText_Server2Client_FriendMoreMax        = 1476,    //好友数量已经超出最大上限
	eTextGuild_Ban_Error                    = 1477,//你没有驱逐公会成员的权限。
	eTextGuild_Ban_Check                    = 1478,//你确定要将%s驱逐出公会吗？
	eTextGuild_Leave_Check                  = 1479,//你确定要离开公会吗？
	eTextGuild_Leave_MasterError            = 1480,//你是会长，不能直接离开公会。
	eTextGuild_Disband_Error                = 1481,//你没有解散公会的权限。
	eTextGuild_Disband_Check                = 1482,//你确定要解散这个公会吗？
	eTextGuild_CreedForbindText	            = 1483,//帮派宗旨中含有非法字符
	eTextGuild_SetLevel_Error               = 1484,//你没有改变公会成员职位的权限。
	eTextGang_ZhuanRang						= 1485,//确定要转让帮派给{#fffa00=  %s#}吗？
	eTextGuild_Invite_Error                 = 1486,//你没有邀请公会成员的权限。
	eTextGuild_Create_Error_Name_Check      = 1487,//公会名称含有非法字符。
	eTextGuild_Create_Error_Name_Length     = 1488,//公会名称长度超出限制。
	eTextGuild_Create_Error_Name_None       = 1489,//公会名称不能为空。
	eTextGuild_Create_Error_Influence_None  = 1490,//公会所属势力不能为空。
	//     eTextGuild_Influence_Select             = 1491,//请选择公会势力
	//     eTextGuild_Influence_One                = 1492,//墨家
	//     eTextGuild_Influence_Two                = 1493,//会任
	eTextGuild_SetTitle_Error               = 1494,//你没有改变公会成员称号的权限。
	eTextGuild_SetTitle_Check               = 1495,//你确定要将{#FFFFD940=%s#}的称号定为{#FFd8ea62=%s#}吗？
	eTextGuild_GruntedRight_One             = 1496,//军团长
	eTextGuild_GruntedRight_Two             = 1497,//副军团长
	eTextGuild_GruntedRight_Three           = 1498,//会员
	//     eTextGuild_Rank_Mo_1                    = 1499,//墨卒
	eTextGuild_Rank_Mo_2                    = 1500,//参将
	eTextGuild_Rank_Mo_3                    = 1501,//部将
	eTextGuild_Rank_Mo_4                    = 1502,//副将
	//     eTextGuild_Tips_NeedExp                 = 1503,//需求经验值
	//     eTextGuild_Tips_TotalCredit             = 1504,//累积荣誉值
	//     eTextGuild_Tips_SetPercent              = 1505,//设置经验值捐献比例
	//     eTextGuild_Tips_Percent                 = 1506,//经验值捐献比例
	//     eTextGuild_Tips_GiveExp                 = 1507,//直接捐献经验值
	//     eTextGuild_Tips_GiveExpNum              = 1508,//捐献经验值数量

	//     eTextGuild_GiveExp_Check                = 1510,//你确定要将%d经验值捐献给公会?
	//     eTextGuild_RongYu                       = 1511,//荣誉值【%d/%d·%0.2f％】
	eTextGuild_GruntedRight_Set             = 1512,//%s被任命为%s
	eTextGuild_GruntedRight_Cancel          = 1513,//%s的%s职务被解除
	eTextGuild_GruntedRight_SetMe           = 1514,//你被任命为%s
	eTextGuild_GruntedRight_CancelMe        = 1515,//你的%s职务被解除
	//     eText_NoInfluence                       = 1514,//无阵营

	//     eTeam_UpManiple                   = 1516,    //%s 被提升为 %d 小队队长
	//     eTeam_DownManiple               = 1517,    //%s 被降为 小队队员
	eTeam_OprError1                    = 1518,    //此操作只能对单人
	eGuild_ReqInvite                = 1519,    //%s邀请你加入 %s 公会
	eClient_Frddlg_Fiendly          = 1520,    //%s\n性别：%s\n等级：%d\n职业：%s\n友好度：%d/%d(%d)
	//     eServer_AddPersonInBlackList    = 1520,    //%s 把你列为黑名单
	eServer_AddPersonInFriend        = 1521,    //%s 加你为好友
	eTip_Client_FriendListInfo        = 1522,    //<#fffcac01=等级 %d\n<#fffcac01=职业 %s\n<#fffcac01=性别 %s\n<#fffcac01=区域 %s\n<#fffcac01=PK %s\n
	eText_PKResult                  = 1523, //%s 杀死了 %s
	eText_PKResult_YouKillPlayer    = 1524, //你杀死了 %s

	eText_FriendPointUp				= 1525,//你和%s的亲密度增加了%d点
	//eClient_Frddlg_SendMegOutline    = 1525,    //发送信息必须选中一个队友![删]
	eClient_Frddlg_AddNotLaw        = 1526,    //你输入不合法，请重新输入
	eClient_Frddlg_AddSomePerson    = 1527,    //您添加%s为好友
	eClient_Frddlg_SomePersonOnline = 1528,    //%上线了


	//eClient_Bargain_InBlackList        = 1532,    //对方加你为黑名单[删]
	eClient_Deul_NoneAgreen            = 1533,    //对方不同意和你切磋


	eClient_PlayerTip_Level				= 1534,//
	eClient_PlayerTip_Profession				= 1535,//
	eClient_PlayerTip_PKMode				= 1536,//
	eClient_PlayerTip_TeamPro				= 1537,//
	eClient_PlayerTip_GangPro				= 1538,//
	eClient_PlayerTip_AlignPro				= 1539,//
	eClient_PlayerTip_AllPro				= 1540,//
	eClient_MonsterTip_Strong				= 1541,//
	eClient_MonsterTip_Normal				= 1542,//
	eClient_MonsterTip_Enhance				= 1543,//
	eClient_MonsterTip_Leader				= 1544,//
	eClient_MonsterTip_HerbLevel				= 1545,//
	eClient_MonsterTip_MineLevel				= 1546,//
	eClient_NpcTip_Title					= 1547,//

	eClient_ClearRupture_NoItem				= 1557,//
	eClient_ClearRupture_MaxOnce			= 1558,//

	eClient_MonsterTip_InsectLevel          = 1559,
	eClient_MonsterNameOnRegionMap          = 1560,//[%s]%s(%d级)
	eClient_MonsterNameOnRegionMap1          = 1561,//[%s]%s

	//     eClient_AddInfo_2slk_17        = 1569,        //捐献经验成功！
	//     eClient_AddInfo_2slk_18        = 1570,        //格式错误(公会图标)
	//     eClient_AddInfo_2slk_19        = 1571,        //尺寸错误(公会图标)
	//     eClient_AddInfo_2slk_20        = 1572,        //色深错误(公会图标)
	//     eClient_AddInfo_2slk_21        = 1573,        //成功!(公会图标)
	//     eClient_AddInfo_2slk_22        = 1574,        //失败(公会图标)


	//     eClient_AddInfo_2slk_120        = 1578,        //%s 被提升为团长！ 

	eClient_MonsterTitle = 1562,     //%s的小伙伴
	eClient_PlayerHideMode1 = 1563, //显示模式:显示全部
	eClient_PlayerHideMode2 = 1564, //显示模式:隐藏全部
	eClient_PlayerHideMode3 = 1565, //显示模式:显示本国玩家
	eClient_PlayerHideMode4 = 1566, //显示模式:显示敌国玩家





	eMessageBox_AgreeBeTeacher = 1590,//是否同意成为%s的师傅
	eMessageBox_AgreeBeStudent = 1591,//是否同意成为%s的徒弟
	eInviteLeague = 1592,//邀请联盟: %s请求与你的公会联盟
	eInviteLeagueCaption = 1593,//邀请联盟: 公会联盟
	eDisadverseLeague = 1594,//%s 帮派请求与你的帮派共享和平
	eDisadverseLeagueCaption = 1595,//解除敌对: 帮派和平
	eOneInvitePerTenMinute = 1596,//十分钟之内只能向同一帮派发送一次结盟邀请。
	eOneDisadversePerTenMinute = 1597,//十分钟之内只能向同一帮派发送一次握手言和。
	eGuildPeaseInfo = 1598,//你的帮派和%s帮派握手言和。
	eGuildLoseLeague = 1599,//你的帮派和%s帮派解除同盟。
	eGuildLeagueBeyondMax = 1600,//同盟关系已经达到最大数量。
	eGuildEnemyBeyondMax = 1601,//敌对关系已经达到最大数量。

	eText_Team_ItemRollLevel    = 1602,//需求品质:%s
	eText_TeamAssignMode_Free   = 1603,//自由拾取
	eText_TeamAssignMode_Team   = 1604,//队伍分配
	eText_TeamAssignMode_Assign = 1605,//队长分配
	eText_TeamBoultResult_Choose    = 1606,//%s 选择了需求[%s]:%d点
	eText_TeamBoultResult_Abandon   = 1607,//%s 选择了放弃[%s]
	eText_TeamBoultResult_Acquire   = 1608,//%s 获得了[%s]
	eText_TeamBoultResult_AllAbandon = 1609,//所有人都放弃了[%s]
	eText_TeamBoultResult_YouAbandon = 1610,//你选择了放弃[%s]

	eMessageBox_ReqMoveBlackList          = 1611, //你是否确定要移到黑名单 {#FFFFD940=%s#}？\n（师徒、配偶关系要移到黑名单后,解除关系需付费500银票） 
	eText_AddFriendReq						= 1612,//你申请和 %s 加为好友
	eInviteAddFriendCaption                   = 1613, // 请求加好友: 加好友申请
	eInviteAddFriend                          = 1614, // "{#fffffa00=%s#}已经加你为好友，是否添加对方为你的好友"/>

	eText_AddFriInVendettaList                    = 1615,    // 对方在你的仇人列表中
	eText_AddFriInBlackList                    = 1616,    // 对方在你的黑名单中
	eText_AddFriAlreadyInBlackList                    = 1617,    // 对方已经在你的黑名单中
	eClient_AttackDieInfo_1                     = 1618, // 你被 %s 杀死了 
	eClient_AddFriInFriendList                      = 1619, // 对方已经在你的好友列表中，操作失败
	//     eClient_IsAddInviterAsFriend                = 1620, // 是否加对方为好友

	eText_WordError							=1621,                //字符不合法

	eClient_Frddlg_AddFriendToBlack             = 1622,    // 您把%s加入黑名单
	eClient_Frddlg_AddFriendBlackToVendetta             = 1623,    // 您把%s加入仇人列表

	eClient_AddFriend = 1625,//请输入添加好友的名称
	eTell_Client_ResumeGang = 1626,//您想恢复帮派么？
	eTextGuild_DisplayName                  = 1627,//【%s·%s】
	eTextPlayer_WinOver                    = 1628,//你战胜了%s
	eTextPlayer_AddGang                    = 1629,//请输入邀请的玩家名称
	eText_FindGuildNpc						=1630,//您现在还没有帮派，点击NPC%s自动寻路至帮派管理员处创建帮派

	eTextPlayer_AddBlackFriend                    = 1637,//请输入要加入黑名单的玩家名称

	eText_InteractionFailed_TargetInFighting    = 1638, // 对方处于战斗中，邀请失败
	eText_InteractionFailed_TargetToFarAway     = 1639, // 对方距离过远，邀请失败
	eText_InteractionFailed_TargetDead          = 1640, // 对方已经死亡，邀请失败
	eText_InteractionFailed_TargetDisconnect    = 1641, // 对方已下线，邀请失败
	eText_InteractionFailed_TargetNoReply       = 1642, // 对方无响应，邀请失败
	eText_InteractionFailed_TargetInMounting    = 1643, // 对方处于骑乘状态，邀请失败
	eText_InteractionFailed_TargetInWater       = 1644, // 对方处于游泳状态，邀请失败
	eText_InteractionFailed_TargetInLooting     = 1645, // 对方处于采集状态，邀请失败
	eText_InteractionFailed_InMounting          = 1646, // 骑乘状态无法邀请相依相偎
	eText_InteractionFailed_InWater             = 1647, // 游泳状态无法邀请相依相偎
	eText_InteractionFailed_InLooting           = 1648, // 采集状态无法邀请相依相偎
	eText_InteractionFailed_IsDead              = 1649, // 死亡状态无法邀请相依相偎
	eText_InteractionFaided_InFighting          = 1650, // 战斗状态无法邀请相依相偎
	eText_StallFailed_InBattle				    = 1651, // 战斗战斗状态无法摆摊
	eText_PrivateShopError_InSwin				= 1652, // 游泳状态无法摆摊
	eText_PrivateShopError_InPick				= 1653, // 采集状态无法摆摊
	eText_PrivateShopError_InDead				= 1654, // 死亡状态无法摆摊

	eText_NewChannel							= 1655, // 新建聊天频道
	eText_Error_MaxChatChannel					= 1656, // 频道已满

	eText_NoAchievementFinish					= 1657, // 奖励已经全部领取

	eText_AddFriendFailed_SelfFull				= 1658, // 好友列表到达上限
	eText_AddFriendFailed_OtherFull				= 1659, // 对方好友列表到达上限
	eText_ShouldBeFriendFirst					= 1660, // 必须是好友关系
	eText_YouAreInChouRenList					= 1661, // 你在对方的仇人列表中，操作失败
	eText_AddRelationFailed						= 1662, // 添加失败
	eText_ExpActionFailed_InMounting			= 1663, // 骑乘状态无法使用表情动作
	eText_ExpActionFailed_InWater				= 1664, // 游泳状态无法使用表情动作
	eText_ExpActionFailed_InLooting				= 1665, // 采集状态无法使用表情动作
	eText_ExpActionFailed_IsDead				= 1666, // 死亡状态无法使用表情动作
	eText_ExpActionFailed_InFighting			= 1667, // 战斗状态无法使用表情动作
	eText_ExpActionFailed_InPrivateShop			= 1668, // 摆摊状态无法使用表情动作
	eText_ExpActionFailed_TargetTooFar			= 1669, // 距离过远，操作失败

	eTextGang_Master							= 1670,//帮主
	eTextGang_ViceMaster						= 1671,//副帮主
	eTextTong_Master							= 1672,//堂主
	eTextTong_Member							= 1673,//堂精英
	eTextGang_Member							= 1674,//普通成员
	eTextTong_ZhuanRang							= 1675,//你确定转让{#fffa00=  %s#}分堂给{#fffa00=  %s#}吗？
	eTextTong_ModifyName						= 1676,//请输入你想修改的分堂名称
	eTextTong_Exit								= 1677,//你确定要退出分堂吗？
	eTextTong_MasterChange						= 1678,//你确定要免去{#fffa00=  %s#}的堂主职位并委任{#fffa00=  %s#}为{#fffa00=  %s#}堂主么？
	eTextGang_ViceMasterRemove					= 1679,//你确定免去{#fffa00=  %s#}的副帮主职位吗？
	eTextGang_ViceMasterAssign					= 1680,//你确定要任命{#fffa00=  %s#}为副帮主吗？
	eTextTong_Invite0							= 1681,//{#fffa00=  %s#}邀请你加入{#fffa00=  %s#}帮派{#fffa00=  %s#}堂
	eTextTong_Invite1							= 1682,//{#fffa00=  %s#}邀请你加入{#fffa00=  %s#}堂
	eTextTong_Remove							= 1683,//你被移出了%s堂
	eTextTong_MaxNumber							= 1684,//%s 堂人数已满
	eTextGang_MaxRemove							= 1685,//当天开除成员数量已到达3名上限
	eTextTong_ExitError24						= 1686,//加入分堂24小时内无法退出
	eTextTong_MaxModifyName						= 1687,//当天修改分堂名称已到达1次上限
	eTextTong_ShowAllMember						= 1688,//显示全部
	eTextTong_ViceMasterChange					= 1689,//你确定要免去{#fffa00=  %s#}的副帮主职位并委任{#fffa00=  %s#}为{#fffa00=  %s#}为副帮主么？
	eTextTong_ZhuangRangViceMaster				= 1690,//你确定转让副帮主给{#fffa00=  %s#}吗？
	eTextDefautTongOneName						= 1691,//分堂1
	eTextDefautTongTwoName						= 1692,//分堂2
	eTextDefautTongThreeName					= 1693,//分堂3
	eTextDefautTongFourName						= 1694,//分堂4
	eTextDefautTongFiveName						= 1695,//分堂5
	eTextDefautTongSixName						= 1696,//分堂6
	eTextDefautTongSevenName					= 1697,//分堂7
	eTextDefautTongEightName					= 1698,//分堂8
	eTextDefautTongNineName						= 1699,//分堂9
	eTextDefautTongTenName						= 1700,//分堂10

	eErrorAlreadyInGang							= 1710,//对方已在其他帮会中
	eTextTong_MasterRemove						= 1711,//你确定要免去{#fffa00=  %s#}的{#fffa00=  %s#}堂堂主职位么？
	eErrorGangMaxNumber							= 1712,//帮会人数到达上限
	eErrorGangName								= 1713,//此帮会名已经被使用
	eErrorAlreadyInThisGang						= 1714,//该玩家已在本帮会中
	eTextJoinMyGang								= 1715,//%s加入帮会
	//因1716字段在string 中已经存在,虽然在这里并不存在
	eText_GangPlayerReach10				= 1717,// 玩家~%s_ 达到30级可以邀请加入帮派

	eText_NoXiaoLaBaForShout					= 1801,//身上没有小喇叭，无法进行喊话

	//---------------------- 交易相关 -----------------------
	eText_BargainFailed_SelfInTrade             = 1850, // 您正处于交易中
	eText_BargainFailed_OppoInTrade             = 1851, // 对方正在交易中
	eText_BargainFailed_SelfInStallage          = 1852, // 摆摊时无法交易
	eText_BargainFailed_OppoInStallage          = 1853, // 对方正在摆摊中
	eText_BargainFailed_OppoOutOfRange          = 1854, // 对方没有在交易范围内
	eText_BargainFailed_OppoRefuse              = 1855, // 对方拒绝交易
	eText_BargainSuccess_Request                = 1856, // 已发送交易申请
	eText_BargainSuccess_Finish                 = 1857, // 交易成功
	eText_BargainFailed_OutOfTime               = 1858, // 交易超时
	eText_BargainFailed_Cancel                  = 1859, // 交易取消
	eText_BargainFailed_Offline                 = 1860, // 玩家下线, 交易取消
	eText_BargainFailed_NoMoney                 = 1861, // 没有足够的金钱
	eText_BargainFailed_NoGold                  = 1862, // 没有足够的金锭
	eText_BargainFailed_MoneyMax                = 1863, // 金钱数量超过能携带的上限
	eText_BargainFailed_ItemError               = 1864, // 交易的道具信息不正确
	eText_BargainFailed_ItemBind                = 1865, // 交易的道具已锁定或者已绑定
	eText_BargainFailed_ItemOverdue             = 1866, // 交易的道具已过期
	eText_BargainFailed_ItemExist               = 1867, // 交易的道具已经在交易栏中了
	eText_BargainFailed_SlotFilled              = 1868, // 放入的交易栏已经有道具了
	eText_BargainFailed_ItemNoTrade             = 1869, // 交易的道具不能被交易
	eText_BargainFailed_PosError                = 1870, // 交易栏位置错误
	eText_BargainFailed_PackFull                = 1871, // 普通背包满了
	eText_BargainFailed_MaterialFull            = 1872, // 材料背包满了
	eText_BargainFailed_HouseFull               = 1873, // 坐骑背包满了
	eText_BargainFailed_ItemChange              = 1874, // 交易道具已经变更
	eText_BargainFailed_HouseBattle             = 1875, // 坐骑已出战, 不能交易
	eText_BargainFailed_LevelLess               = 1876, // 等级不足10级，不能交易金钱
	eText_BargainFailed_HouseLevelHigh          = 1877, // 坐骑等级太高，不能交易
	eText_BargainFailed_PlayerPetLimit			= 1878, // 超过对方领养上限,不能交易
	eText_BargainFailed_InFightState			= 1879,	// 处于战斗状态无法交易
	eText_Bargain_AddFailed						= 1880, // 超过宠物交易上限，无法再添加
	eText_Bargain_TargetInFightState			= 1881, // 对方处于战斗中，无法交易
	//-------------------------------------------------------

	eText_TaskTrackAll                          = 1900, //全部

	eText_MainMenu_Hotkey_State  = 1901, //<String Id="1901" Value="<#ff00ffff 人物\n<#ffffffff 快捷键:C"/>
	eText_MainMenu_Hotkey_Skill	 = 1902, //<String Id="1902" Value="<#ff00ffff 技能\n<#ffffffff 快捷键:X"/>
	eText_MainMenu_Hotkey_Vehicle = 1903, //<String Id="1903" Value="<#ff00ffff 坐骑\n<#ffffffff 快捷键:H"/>
	eText_MainMenu_Hotkey_Country = 1904, //<String Id="1904" Value="<#ff00ffff 国家\n<#ffffffff 快捷键:J"/>
	eText_MainMenu_Hotkey_Task = 1905, //<String Id="1905" Value="<#ff00ffff 任务\n<#ffffffff 快捷键:L"/>
	eText_MainMenu_Hotkey_Pack = 1906, //<String Id="1906" Value="<#ff00ffff 背包\n<#ffffffff 快捷键:B"/>
	eText_MainMenu_Hotkey_Fiend = 1907, //<String Id="1907" Value="<#ff00ffff 社交\n<#ffffffff 快捷键:F"/>
	eText_MainMenu_Hotkey_Guild = 1908, //<String Id="1908" Value="<#ff00ffff 帮会\n<#ffffffff 快捷键:G"/>
	eText_MainMenu_Hotkey_Team = 1909, //<String Id="1909" Value="<#ff00ffff 组队\n<#ffffffff 快捷键:T"/>
	eText_MainMenu_Hotkey_System  = 1910, //<String Id="1910" Value="<#ff00ffff 系统\n<#ffffffff 快捷键:Esc"/>

	eText_PropertyDlg_Tip_LiLiang_Warrior = 1911, //<String Id="1911" Value="<#ff00ffff 力量\n<#ffffffff 影响近程攻击和命中几率\n<#ffff8bd5 1点力量增加0.3近程攻击和0.01命中几率"/>
	eText_PropertyDlg_Tip_LiLiang_Assassin = 1912, //<String Id="1912" Value="<#ff00ffff 力量\n<#ffffffff 影响近程攻击和命中几率\n<#ffff8bd5 1点力量增加0.4近程攻击和0.01命中几率"/>
	eText_PropertyDlg_Tip_LiLiang_HunterTaoistMage	 = 1913, //<String Id="1913" Value="<#ff00ffff 力量\n<#ffffffff 影响命中几率\n<#ffff8bd5 1点力量增加0.02命中几率"/>
	eText_PropertyDlg_Tip_MinJie_Hunter = 1914, //<String Id="1914" Value="<#ff00ffff 敏捷\n<#ffffffff 影响远程攻击和躲闪几率\n<#ffff8bd5 1点敏捷增加0.4远程攻击和0.01躲闪几率"/>
	eText_PropertyDlg_Tip_MinJie_ExceptHunter  = 1915, //<String Id="1915" Value="<#ff00ffff 敏捷\n<#ffffffff 影响躲闪几率\n<#ffff8bd5 1点敏捷增加0.02躲闪几率"/>
	eText_PropertyDlg_Tip_ShuFa_Mage = 1916, //<String Id="1916" Value="<#ff00ffff 智慧\n<#ffffffff 影响魔法攻击和魔法上限\n<#ffff8bd5 1点智慧增加0.4魔法攻击和17点魔法上限"/>
	eText_PropertyDlg_Tip_ShuFa_Taoist = 1917, //<String Id="1917" Value="<#ff00ffff 智慧\n<#ffffffff 影响魔法攻击和魔法上限\n<#ffff8bd5 1点智慧增加0.3魔法攻击和17点魔法上限"/>
	eText_PropertyDlg_Tip_MPHuiFu_Warrior = 1918, //<String Id="1918" Value="<#ff00ffff 怒气回复\n<#ffffffff 影响人物怒气回复速度"/>
	eText_PropertyDlg_Tip_MPHuiFu_Assassin = 1919, //<String Id="1919" Value="<#ff00ffff 能量回复\n<#ffffffff 影响人物能量回复速度"/>
	eText_PropertyDlg_Tip_MPHuiFu_MageTaoist = 1920, //<String Id="1920" Value="<#ff00ffff 魔法回复\n<#ffffffff 影响人物魔法回复速度"/>
	eText_PropertyDlg_Tip_MPHuiFu_Hunter = 1921, //<String Id="1921" Value="<#ff00ffff 箭支回复\n<#ffffffff 影响人物箭支回复速度"/>

	eText_Can_Attend_Task						=1922,	// %d级可参加

	eText_PropertyDlg_Tip_Luqi						=1923,	//<String Id="1923" Value="{#ff00ffff 怒气\n{#ffffffff 当前怒气/怒气上限"/>
	eText_PropertyDlg_Tip_Power						=1924,	//<String Id="1924" Value="{#ff00ffff 能量\n{#ffffffff 当前能量/能量上限"/>
	eText_PropertyDlg_Tip_Magic						=1925,	//<String Id="1925" Value="{#ff00ffff 法力\n{#ffffffff 当前法力/法力上限"/>
	eText_PropertyDlg_Tip_Arrow						=1926,	//<String Id="1926" Value="{#ff00ffff 箭支\n{#ffffffff 当前箭支/箭支上限"/>

	eText_UITip_HotKey_Action = 1927,
	eText_UITip_HotKey_Activity = 1928,
	eText_UITip_HotKey_RankList,
	eText_UITip_HotKey_Epic,
	eText_UITip_HotKey_FightAssist,
	eText_UITip_HotKey_WealthProtect,
	eText_UITip_HotKey_Achievement,
	eText_UITip_HotKey_Map = 1934,
	eText_UITip_HotKey_DoubleExp = 1935,
	eText_UITip_HotKey_ActiveDay = 1936,

	eText_Mount_FeedError_FullHP = 1960, // 坐骑生命值已满





	eProfession_Warrior                         =2001,            //战士
	eProfession_Assassin                        =2002,            //魅影
	eProfession_Mage                            =2003,            //法师
	eProfession_Hunter                          =2004,            //猎人
	eProfession_Taoist                          =2005,            //天师

	eProfession_Unknown                         =2008,            //未知

	eEquip_Durable                              =2009,            //耐久
	eUI_NeedLevel                               =2010,            //需要级别
	eSex_Man                                    =2011,                        //
	eSex_FeMan                                  =2012,
	eUI_NeedSex                                 =2013,    
	eNeed_Profession                            =2014,                //职业需求
	eText_EquipLimit		                    =2015,          // 装备限制:

	eText_SuitSkill							    = 2017, // 套装技能:
	eText_Suit							        = 2018, // 套装:
	eTextPlayer_EquipFaild                      = 2019, ////装备失败
	eText_PartitionLine                         = 2020, //-------------------------        
	eUI_TipsSuit                                = 2021,        //套装说明:
	eTextPlayer_Faild                           = 2022,// 失败
	eText_IT_MATERIAL                           = 2023,        //原材料
	eText_IT_RESTORE                            = 2024,        //消耗品
	eText_IT_GEM                                = 2025,        //宝石
	eText_IT_TASK                               = 2026,        //任务物品
	eText_IT_Reel							    = 2027,		// 卷轴
	eText_Tip_GuildItem			                = 2028, // 帮会物品
	eText_AddGuildFailed_TimeLimit		        = 2029, // 退帮后24小时内无法再次加入帮会
	eUI_SoulBound                               = 2030, //装备绑定
	eUI_SoulBoundedCanotDo                      = 2031, //
	eTip_BelongerDone                           = 2032,//已有归属
	eUnsb_Suc                                   = 2033, //解除成功
	eUnsb_NotBound                              = 2034,//物品没有绑定
	eSing_UnSoulBound                           = 2035,
	eClient_Target_Hp_Percent                   = 2036,    //%4.1f ％
	eTip_PickBound					            = 2037, //拾取后绑定

	//     eMouseOnUI_Player_Police        = 2037,    //{#fff6e2cd=%s#}\\n{#fff6e2cd=等级 %d#}
	//     eMouseOnUI_Player_Normal        = 2038,    //{#fff6e2cd=%s#}\\n{#fff6e2cd=等级 %d#}
	//     eMouseOnUI_Player_Attacker        = 2039,    //{#fff6e2cd=%s#}\\n{#fff6e2cd=等级 %d#}
	//     eMouseOnUI_Player_Killer1        = 2040,    //{#fff6e2cd=%s#}\\n{#fff6e2cd=等级 %d#}
	//     eMouseOnUI_Player_Killer2        = 2041,    //{#fff6e2cd=%s#}\\n{#fff6e2cd=等级 %d#}
	//     eMouseOnUI_Player_Killer3        = 2042,    //{#fff6e2cd=%s#}\\n{#fff6e2cd=等级 %d#}
	//     eMouseOnUI_Player_Killer4        = 2043,    //{#fff6e2cd=%s#}\\n{#fff6e2cd=等级 %d#}
	//     eMouseOnUI_Player_Killer5        = 2044,    //{#fff6e2cd=%s#}\\n{#fff6e2cd=等级 %d#}
	//     eMouseOnUI_Npc_Normal            = 2045,    //{#FFfbd860=%s#}\\n{#FFfbd860=等级 %d#}
	//     eMouseOnUI_Monster_Material        = 2046,    //{#ffbfff00=%s#}\\n{#ffbfff00=等级 %d#}
	//     eMouseOnUI_Monster_Initiative    = 2047,    //{#ffff7200=%s#}\\n{#ffff7200=等级 %d#}
	// //     eMouseOnUI_Monster_Passivity    = 2048,    //{#ffd0d0d0=%s#}\\n{#ffd0d0d0=等级 %d#}
	//     eTipText_base_Overdue                    = 2049,    //    %d/%d/%d %d:%d
	//     eSystemInfo_Overdue_InPack                = 2050, //在包裹里面过期的物品
	//     eSystemInfo_Overdue_InStorage            = 2051, //在Storage里面过期的物品
	//     eSystemInfo_Overdue_InPrivateShop        = 2052, //在PrivateShop面过期的物品
	//     eSystemInfo_Overdue_InCompound            = 2053, //在InCompound里面过期的物品
	//     eSystemInfo_Overdue_InItensify            = 2054, //在Intensify里面过期的物品
	//     eSystemInfo_Overdue_InReduce            = 2055, //在Reduce里面过期的物品
	//     eSystemInfo_Overdue_InUnSoul            = 2056, //在Reduce里面过期的物品
	//     eSystemInfo_Overdue_InEquip                = 2057, //在Reduce里面过期的物品
	//     eSystemInfo_Overdue_InLockIntensicfy = 2058,//在LockIntensify里面过期的物品



	/////////////////////////////////
	///此段数字需要连续
	eEquipType_hair                       = 2063,	//头发
	eEquipType_helmet					 = 2064,	//头盔
	eEquipType_face                       = 2065,	//脸
	eEquipType_armour					 = 2066,	//衣服
	eEquipType_glove		                 = 2067,	//手套
	eEquipType_shoe                       = 2068,	//鞋子
	eEquipType_rhanditem		             = 2069,	//右手物品
	//eEquipType_lhanditem			         = 2070,	//左手物品
	eEquipType_headwear                   = 2071,	//头饰
	//eEquipType_HandShiedld                = 2072,	//盾牌
	eEquipType_Shoulder                   = 2073,	//肩甲
	eEquipType_Trousers                   = 2074,	//裤子
	eEquipType_accouterment               = 2075,	//饰品
	eEquipType_ring                       = 2076,	//戒指
	//eEquipType_bangle                     = 2077,	//勋章
	eEquipType_necklace                   = 2078,	//项链
	eEquipType_sash                       = 2079,	//腰带
	//eEquipType_TaositShild                = 2080,	//法器
	eWeapon_Spear					 = 2081,	//枪
	eWeapon_Staff					 = 2082,	//杖
	eWeapon_Fan						 = 2083,    //扇
	eWeapon_Sword					 = 2084,    //剑
	eWeapon_Bow						 = 2085,	//弓

	///技能作用对象
	eUI_SillTyps_TargetType			 =    2100,        //作用对象:

	eUI_SillTyps_Target_no			  =    2101,        //无目标
	eUI_SillTyps_Target_myself		  =    2102,        //自己
	eUI_SillTyps_Target_friend		  =    2103,        //自己\队友
	eUI_SillTyps_Target_normalplayer   =    2104,        //普通玩家
	eUI_SillTyps_Target_enemy		  =    2105,        //敌人
	eUI_SillTyps_Target_dead			  =    2106,        //死亡目标
	eUI_SillTyps_Target_herb			  =    2107,        //草药:
	eUI_SillTyps_Target_mine           =    2108,        //矿石
	eUI_SillTyps_Target_wood           =    2109,        //木头
	eUI_SillTyps_Target_treasure       =    2110,        //宝箱
	eUI_SillTyps_Target_pet            =    2111,        //宠物
	eUI_SillTyps_Target_all            =    2112,        //所有人
	eUI_SillTyps_Target_tream          =    2113,        //队伍
	eUI_SillTyps_Target_mount          =    2114,        //坐骑
	eUI_SillTyps_Target_guild		  =    2115,		//帮会成员

	eText_Day						= 2116,			// 天
	eText_Hour						= 2117,			// 小时

	eTip_sAddDaoxing					= 2118,	//道行
	eTip_sAddBreakStrike				= 2119, //破甲伤害
	eTip_sAddStabStrike					= 2120, //贯穿伤害
	eTip_sAddElementStrike				= 2121, //元素伤害
	eTip_sAddToxinStrike				= 2122, //毒素伤害
	eTip_sAddSpiritStrike				= 2123, //精神伤害
	eTip_sAddBreakResist				= 2124, //破甲抗性
	eTip_sAddStabResist					= 2125, //贯穿抗性
	eTip_sAddElementResist				= 2126, //元素抗性
	eTip_sAddToxinResist				= 2127, //毒素抗性
	eTip_sAddSpiritResist				= 2128, //精神抗性


	eText_NotSatisfySuitSkillCondition =    2201,		//请先装备对应的套装 

	eText_Debuf_Giddy                       = 2230, // 眩晕
	eText_Debuf_Afraid                      = 2231, // 恐惧
	eText_Debuf_Stand                       = 2232, // 定身
	eText_Debuf_Torpid                      = 2233, // 沉默
	eText_Debuf_Slowdown                    = 2234, // 减速

	eText_Buf_DamageDerate                  = 2235, // 伤害减免

	eText_Buf_ContBeMagAttack             = 2238, // 魔法免疫 (不能被魔法攻击)
	eText_Buf_ContBePhyAttack             = 2239, // 物理免疫 （不能被物理攻击）

	eText_Buf_BaseMPPerDecrease             = 2240, // 每%s秒损失基础%s上限的%d%%
	eText_Buf_Invisible                     = 2241, // 隐身
	eText_PlayAtt_Short                     = 2290, //近攻
	eText_PlayAtt_Long                      = 2291, //远攻
	eText_PlayAtt_Magic                     = 2292, //魔攻
	eText_PlayDef_Short                     = 2293, //近防
	eText_PlayDef_Long                      = 2294, //远防
	eText_PlayDef_Magic                     = 2295, //魔防

	eText_Buf_DamageMianYiCnt               = 2296, //伤害免疫：%d次

	eText_NeedSkillExp                      = 2299, //需要技能经验:%d/%d
	eText_StatusTip_BaseMPPer               = 2300, // 每%s秒恢复基础%s上限的%d%%
	eText_Title_SellPrice		            = 2301, // 卖出价格:
	eText_Buf_RestorMP                      = 2302,    //每隔 %0.1f 秒回复精力:%d 点\n
	eText_Skill_FrenzyPer                   = 2303,    //暴击率
	eText_Skill_DelayTimeRestorHP           = 2304,    //每隔 %0.1f 秒回复生命:%d 点    \n
	eText_Skill_ChangeFrenzy                = 2305,    //暴击威力
	eText_Buf_DecreaseMP                    = 2306,    //每隔 %0.1f 秒造成敌人精力流失:%d 点    \n
	eText_Skill_DelayTimeChangeHP           = 2307,    //每隔 %0.1f秒造成敌人生命伤害:%d 点    \n
	eUI_stPlayAtt_Frost                     = 2308,    //冰系攻击
	eUI_ePlayIceDef                         = 2309,        //冰系抗性
	eText_Title_ItemType		            = 2310, // 道具类型:
	eText_Skill_OnePointAddRate             = 2311,    //每颗星增加的攻击力ApointAddRate”的值*100
	eUI_ePlayPoisonDef                      = 2312,        //毒系抗性
	eUI_sDodge                              = 2313,        //回避        
	eUI_sExact                              = 2314,                //命中
	eText_Skill_RestorHP                    = 2315,    //生命恢复: %d %
	eUI_sMpMax                              = 2316,        //精力上限
	eText_Skill_ReboundHP                   = 2317,    //反弹伤害: %d%%
	eText_Title_Minute			            = 2318, // 分钟	
	eUI_stPlayAtt_Poison                    = 2319,    //毒系攻击
	eUI_sAddDef                             = 2320, // 附加防御:
	eUI_Hurt_AddPhisycsDam		            = 2321,		// 附加近程伤害
	eUI_Hurt_AddMagicDam		            = 2322,		// 附加远程伤害    
	eUI_nHpMax                              = 2323,        //生命上限
	eUI_sHpRestore                          = 2324,        //生命回复
	eUI_stChanged_MP                        = 2325,        //更改魔法
	eUI_stChanged_HP                        = 2326,        //更改生命
	eUI_stAttSpeedChanged                   = 2327,    //攻击速度
	eUI_stPlayAtt_Blaze                     = 2328,    //火系攻击
	eUI_ePlayFireDef                        = 2329,  //火系抗性
	eText_Title_Skill_Level		            = 2330, // 技能等级:
	eTip_Status_AddSkillExp              = 2331,    //技能经验值增加:%d 倍
	eText_Skill_SkillCoolDownTime        = 2332,    //技能冷却时间:%0.1f 秒
	eTip_SkillLearnNeedExp               = 2333,    //技能修炼值【%d/%d·%0.2f％】
	eText_Skill_AddRestorMP              = 2334,    //加快回复精力: %d 点\n
	eText_Skill_AddRestorMPPer           = 2335,    //加快回复精力速度: %d %%\n
	eText_Skill_AddRestorHP              = 2336,    //加快回复生命: %d 点\n
	eText_Skill_AddRestorHPPer           = 2337,    //加快回复生命速度: %d %%\n    
	eClient_AddInfo_2slk_119             = 2338,    //减少仇恨:%d 当前仇恨:%d
	eClient_AddInfo_2slk_118             = 2339,    //减少伤害仇恨:%d 当前仇恨:%d
	eUI_stChanged_HPMax                  = 2340,    //生命最大值
	eText_AllPro                         = 2341,    //所有职业
	eUI_sPhysicsDef                      = 2342,    //近程防御
	eText_Skill_AllDamage                = 2343,    //全伤害    
	eUI_ePlayAtt_Physics                 = 2344,    //近程攻击
	eUI_ePlayAtt_Magic                   = 2345,    //法术攻击
	eText_Skill_AddPhyAtt                = 2346,    //物理攻击增加: %d
	eText_Skill_AddPhyAttPer             = 2347,    //物理攻击增加百分比:%d%%
	eTip_Status_AddExp                   = 2348,    //经验值增加:%d 倍
	eUI_stPlayAtt_Thunder                = 2349,    //雷系攻击
	eUI_ePlayThunderDef                  = 2350,    //雷系抗性

	eTip_sNone					= 2351,		// 起始值
	eTip_sAddStrength			= 2352,		// 力量
	eTip_sAddAgility			= 2353,		// 敏捷
	eTip_sAddConstitution		= 2354,		// 体质（耐力）
	eTip_sAddIntelligence		= 2355,		// 智力（灵力）
	eTip_sAddShortAttack    	= 2356,		// 近攻
	eTip_sAddLongAttack			= 2357,		// 远攻
	eTip_sAddMagicAttack		= 2358,		// 魔攻
	eTip_sAddShortDefend		= 2359,		// 近防
	eTip_sAddMagicDefend		= 2360,		// 魔防
	eTip_sAddLongDefend			= 2361,		// 远防
	eTip_sAddExact      		= 2362,		// 命中
	eTip_sAddDodge				= 2363,		// 闪避
	eTip_sAddCritical   		= 2364,		// 暴击
	eTip_sAddTenacity   		= 2365,		// 韧性
	eTip_sAddCriticalIntensity	= 2366,		// 暴击伤害
	eTip_sAddHPMax      		= 2367,		// 生命
	eTip_sAddAPMax				= 2368,		// 弓箭
	eTip_sAddBPMax				= 2369,		// 子弹
	eTip_sAddFPMax  			= 2370,		// 怒气
	eTip_sAddEPMax          	= 2371,		// 能量
	eTip_sAddMPMax      		= 2372,		// 魔法
	eTip_sAddBaseAttr   		= 2373,		// 全基础属性
	eTip_sAddExpPer 			= 2374,		// 经验获得 百分比
	eTip_sAddEnergyMax      	= 2375,		// 活力上限
	eTip_sAddMoveSpeed  		= 2376,		// 移动速度 具体的值

	eTip_sAddHPRestoreRate      = 2377,     // 回血
	eTip_sAddMPRestoreRate      = 2378,     // 回魔

	eText_Skill_BurnMpPerDamage   = 2379,   // 吸收每点伤害损耗精力: %d 点  \n
	eText_Skill_CostExPower	      = 2380,	// 消耗斗气
	eText_Skill_CostMP            = 2381,   // 消耗精力: %d
	eText_Skill_CostMPPer         = 2382,   // 消耗精力: %d %%
	eText_Skill_CostHP            = 2383,   // 消耗生命: %d
	eText_Skill_CostHPPer         = 2384,   // 消耗生命: %d %%
	eTip_LearnSkillLevelReq     = 2385,     // 需要等级:%ld\n
	eTip_LearnSkillLevelNeed    = 2386,     // 需要技能:%ld级%s\n
	eText_Title_NeedSkillExp	= 2387,     // 需要技能经验:
	eTip_LearnSkillMoneyNeed    = 2388,     // 需要金钱:%ld\n
	eText_Title_UseDistance		= 2389,     // 施放距离:
	eText_Title_LearnCondition  = 2390,     // 学习条件:
	eTipForSkill_AddIntonateRate= 2391,     // 施法时间增加
	eUI_stChanged_MPMax         = 2392,     // 魔法最大值
	eTipForSkill_DoNight        = 2393,     // 夜晚有效
	eText_Title_UseImmediate	= 2394,     // 瞬间释放:
	eText_Skill_PrepTime        = 2395,     // 吟唱时间:%0.1f 秒
	eText_Title_UseForever		= 2396,     // 永久使用
	eText_Title_SuitName		= 2397,     // 套装名称:
	eText_Title_LeftTime		= 2398,     // 剩余时间:
	eText_Skill_NotStudy        = 2399,     // 未学习。
	eText_Skill_ExtraHP         = 2400,     // 造成伤害: %d %
	eText_Skill_BackStrikePer   = 2401,     // 增加背击伤害: %d%%
	eText_Skill_AddWardRate     = 2403,     // 增加招架几率AddWardRate
	eText_Skill_AddWardValue    = 2404,     // 增加招架值AddWardValue
	eText_Title_Bound			= 2405,     // 装备后绑定:
	eText_Title_WeaponType		= 2406,     // 装备类型:
	eText_Title_WeaponProperty	= 2407,	    // 装备属性:
	eText_Skill_DurationTime    = 2408,     //状态持续时间: %0.1f 秒\n
	eText_Skill_DurationActualTime = 2409, //状态持续时间: %d 小时\n
	eText_Skill_MaxAbsorb          = 2410,     //最大吸收
	eText_Bind_ByStarMove          = 2411,  // 移星后绑定
	eText_TeamSkillFailed_CoolDown = 2412, //队伍技能处于冷却中
	eText_TeamSkillFailed_NotAvailable = 2413, //未满足队伍技能的释放条件
	eUI_SkillCategory_Team		= 2414,	// 小队技能
	eUI_SkillCategory_Attack	= 2415,	// 主动技能
	eUI_SkillCategory_Passive	= 2416,	// 被动技能
	eUI_SkillCategory_Assistant	= 2417,	// 辅助技能
	eTip_sCastSpeed             = 2419, // 吟唱速度

	//////////////////////////////////////////////////////////////////////////
	/// 五行相关
	eText_GetJinAttribute		= 2420, //恭喜你受到金神的赐福，成功将装备附加上“金”属性
	eText_GetMuAttribute		= 2421, //恭喜你受到木神的赐福，成功将装备附加上“木”属性
	eText_GetShuiAttribute		= 2422, //恭喜你受到水神的赐福，成功将装备附加上“水”属性
	eText_GetHuoAttribute		= 2423, //恭喜你受到火神的赐福，成功将装备附加上“火”属性
	eText_GetTuAttribute		= 2424, //恭喜你受到土神的赐福，成功将装备附加上“土”属性
	eText_Error_ItemNotReady	= 2425, // 请确认放入了装备和指定的材料
	eText_Error_ItemNotElement	= 2426, // 该装备不是五行套装部件
	eText_Error_ItemAlreadyDid	= 2427, // 该装备已经鉴定过五行属性
	eText_WuXing_Tip_Jin		= 2428,	// 五行:金（带颜色）
	eText_WuXing_Tip_Mu			= 2429,	// 五行:木（带颜色）
	eText_WuXing_Tip_Shui		= 2430, // 五行:水（带颜色）
	eText_WuXing_Tip_Huo		= 2431,	// 五行:火（带颜色）
	eText_WuXing_Tip_Tu			= 2432,	// 五行:土（带颜色）
	eText_Wuxing_Tip_JinHurt	= 2433,	// 金属性
	eText_Wuxing_Tip_MuHurt		= 2434,
	eText_Wuxing_Tip_ShuiHurt	= 2435,
	eText_Wuxing_Tip_HuoHurt	= 2436,
	eText_Wuxing_Tip_TuHurt		= 2437,
	eText_Error_NotEnoughMoney  = 2438,// 没有足够的钱
	eText_Error_HaveNotElement	= 2439, // 没有五行属性, 不能清除
	eText_Error_ClearCountLimit	= 2440, // 一天只能清除%d次 枚举在Globaldef.h => ClearElementCount
	eText_Error_NotCheckupItem	= 2441,  // 不是鉴定五行的物品
	eText_Error_NotClearItem	= 2442,    // 不是清除五行的物品
	eText_Error_LevelError		= 2443,      // 物品和装备等级不符
	eText_Error_ClearSuccess	= 2444, // 净化成功
	eText_FiveXingSecret        = 2445, //全身提纯+4/+5后，激活神秘五行提纯
	eText_FiveXingUpdateResult  = 2446, //提纯等级:%d %s五行伤害:+%d
	eText_FiveXingChangeResult  = 2447,  //五行属性转换为: %s
	eText_FiveXingJin           = 2448, //金
	eText_FiveXingMu            = 2449, //木
	eText_FiveXingShui          = 2450, //水
	eText_FiveXingHuo           = 2451, //火
	eText_FiveXingTu            = 2452, //土
	eText_FiveXingUpdateTipJin  = 2453, //金五行提纯(+%d):
	eText_FiveXingUpdateTipMu   = 2454, //木五行提纯(+%d):
	eText_FiveXingUpdateTipShui = 2455, //水五行提纯(+%d):
	eText_FiveXingUpdateTipHuo  = 2456, //火五行提纯(+%d):
	eText_FiveXingUpdateTipTu   = 2457, //土五行提纯(+%d):
	eText_FiveXingDefaultTipJin = 2458, //#FFffff00五行套装全身提纯+3、+4、+5后将会激活隐藏属性
	eText_FiveXingDefaultTipMu  = 2459, //#FFffff00五行套装全身提纯+3、+4、+5后将会激活隐藏属性
	eText_FiveXingDefaultTipShui= 2460, //#FFffff00五行套装全身提纯+3、+4、+5后将会激活隐藏属性
	eText_FiveXingDefaultTipHuo = 2461, //#FFffff00五行套装全身提纯+3、+4、+5后将会激活隐藏属性
	eText_FiveXingDefaultTipTu  = 2462, //#FFffff00五行套装全身提纯+3、+4、+5后将会激活隐藏属性
	eClient_SendMailInfo        = 2465,        //有附件时，抄送人将无法获得邮件，确定发送？

	eText_EquipUpgrade_Success  = 2470,		//升阶成功
	eText_EquipUpgrade_Fail  = 2471,		//升阶失败
	eText_EquipUpgrade_Cannot  = 2472,		//该装备无法升阶
	eText_EquipUpgrade_NoOptional  = 2473,		//未放入继承道具，升阶后将会清除装备的所有属性，是否继续？
	eText_EquipUpgrade_CanNotUpgrade  = 2474,		//无法升阶到此装备
	eText_EquipUpgrade_LackMaterial  = 2475,		//材料不足，无法升阶
	eText_EquipUpgrade_ErrorMaterial  = 2476,		//材料错误，升阶失败
	eText_EquipUpgrade_ClearStarAttribute = 2477,	//升级后会清除升星属性

	eText_NotSpecialRepair		 = 2490, // 此物品无法特殊修理
	eText_NotNeedRepairFineEquip = 2491, // 此装备完好无损，无需进行特殊修理

	eText_stStrengthReq			= 2500,  //力量
	eText_stMinjieReq		    = 2501,  //敏捷
	eText_stTizhiReq			= 2502,  //体质
	eText_stShufaReq			= 2503,  //术法
	eText_stJinguReq			= 2504,  //筋骨

	eText_StallFailed_AddItemError          = 2550, // 向摊位中添加物品失败
	eText_StallFailed_SlotAlready           = 2551, // 摊位此位置有道具出售，不能添加
	eText_StallFailed_DataAlready           = 2552, // 此道具已经被添加到摊位中

	eText_StallQuery_StallName = 2553,	//店铺名
	eText_StallQuery_BossName = 2554, //店主名

	eText_StallFailed_AddBuyAllowStack      = 2560, // 只能收购可堆叠物品
	eText_Country_Free_NeedNotRemit         = 2561, // 不需要赦免

	eText_Stall_TradeRecord_Sell            = 2602, // ~%s_ 从您的个人商店购买了 %d 个 [%s]，您获得了 %s
	eText_Stall_TradeRecord_Buy             = 2603, // ~%s_ 向您出售了 %d 个 [%s]，您花费了 %s
	eTextPlayer_CloseShop                   = 2604, //%s 关掉了商店!

	eExchange_Ask                           = 2607, // %s请求交易,是否接受!

	eText_ItemNoPlace                       = 2609, // 背包栏没有空位置了
	eText_ChangeSuitFail                    = 2610, // 包裹已满，部分装备换装失败

	eClient_AddInfo_2slk_31                 = 2614, // 此物品不可交易
	eClient_AddInfo_2slk_35                 = 2615, // 对不起,此物品不能卖给商店!
	eText_ThisItemCanNotDrop                = 2616, // 本物品不能被丢弃
	eText_Stall_TipPrice                    = 2617, // 出售价格

	eUI_NotMemoy                            = 2619, // 你没有足够的钱!

	eText_StallFailed_NameError             = 2620, // 摊位名称非法
	eText_StallFailed_VenderMoneyLess       = 2621, // 没有足够的金钱收购摊位上的物品
	eText_StallFailed_VenderPackNoPlace     = 2622, // 没有足够的包裹空间收购所有的物品
	eText_StallFailed_Offline               = 2623, // 摊主已经不在线了
	eExChange_NoPermitInMorp                = 2624, // 变身状态无法摆摊
	eText_StallFailed_WealthProtect         = 2625, // 财产保护时间内不能摆摊
	eText_StallFailed_EmptyStallage         = 2626, // 不能开启一个空摊位
	eText_BargainFailed_InPrivateShop       = 2627, // 摆摊状态无法交易
	eText_StallFailed_InBargaining          = 2628, // 交易状态无法摆摊
	eUI_SendExchange                        = 2629, // 发送交易申请
	eUI_SendExchange_fail                   = 2630, // 发送交易申请失败
	eText_CanNotPushItemIntoStorage         = 2631, // 不能把物品放入仓库
	eText_ItemHaveBeenLocked                = 2632, // 物品已经加锁
	eText_ChangPrice                        = 2634, // 改变使物品价格
	eText_StallFailed_ItemNumError          = 2635, // 物品数量不正确
	eText_StallFailed_VenderNoMoney         = 2636, // 摊主没有足够的金钱收购了

	eText_Price_0                           = 2637, // 价格
	eText_StallFailed_VenderNoGold          = 2638, // 摊主没有足够的金锭收购了
	eText_StallFailed_VenderPackFull        = 2639, // 摊主包裹满了
	eExchange_UnKnown                       = 2640, // 交易失败
	eText_Client_Trade_Faild                = 2641, // 交易终止
	eText_StallFailed_VenderHouseFull       = 2642, // 摊主坐骑数量满了, 不能收购
	eText_MoneyNotEnoungh                   = 2643, // 金钱不足，无法进行此操作

	eText_Client_Trade_Faild_Distance       = 2646, // 与玩家距离过远,交易被终止
	eClient_AddInfo_2slk_10                 = 2647, // 没有可修理物品

	eText_StallFailed_TooMouchMoney         = 2648,	// 摆摊物品金额超过携带金钱上限
	eText_Player_Beyong_Max_Money           = 2649,	// 对方的金钱超过包裹和仓库的总金额上限，操作失败
	eText_StallFailed_StallageError         = 2650, // 摊位数据不正确, 请重新查看
	eText_StallFailed_ItemError             = 2651, // 物品错误，不能购买
	eText_StallFailed_StallageClose         = 2652, // 摊位已关闭
	eText_StallFailed_PriceChange           = 2653, // 摊位的物品价格已更改

	eExchange_NoJiaoziNoMoney               = 2654,
	eExchange_ExceedUpperLimit              = 2655,			// 购买数量不能超过%d
	eExchange_NotLingPai	                = 2656,            // 没有令牌!
	eExchange_NotMoney                      = 2657,            // 没有足够钱!
	eExchange_NotReputation                 = 2658,			// 没有足够名望
	eExchange_NotExploit	                = 2659,			// 没有足够功勋
	//eUI_Bank_LevelUp_error                = 2658,        //你身上钱不足,无法升级银行！
	//eUI_Bank_LevelUp_Text_0               = 2659,        //你升级银行需要
	eText_ChangeHorseName                   = 2660, //请输入你想修改的坐骑名称
	eUI_YouTo                               = 2661,            //你向
	eText_ChangePetName                     = 2662,//请输入你想修改的召唤兽名称
	//     eUI_GetGoldError_NotGold                = 2663,
	//     eShopCenterUI_GetYuanBao                = 2664, //获取一个金元宝
	eText_Client_Trade_Faild_Ride           = 2665,    //骑在马上不可交易,交易被终止
	eText_StallFailed_NoRide                = 2666, // 骑乘状态不可摆摊
	eClient_AddInfo_2slk_25                 = 2667,        //"骑在马上不可交易!"
	//eText_BankTradeBankNotMoney           = 2668,//钱柜里没这么多钱
	//eText_BankTradeUpgradeMax             = 2669,//钱柜已是最高级
	//eUI_InputSaveMoney                    = 2670,    //请输入您存钱的数量
	eText_Input_SaveCnt                     = 2671,                //请输入存入这类物品的数量
	//eUI_Take_Money                        = 2672,            //请输入您取钱的数量
	eText_Sell_Price                        = 2673,        //出入卖出的价格

	//eText_Ask_BuyCnt                      = 2675,                //请输入要购买的物品数量
	//eText_Input_MoveCnt                   = 2676,                //请输入移动的数量
	eText_EnterShopName                     = 2677,    //请填写你个人商店的名字!
	eText_StallFailed_NoItemMoveWhenOpen    = 2678,        //"请关闭商店后再操作!"

	eClient_ShopCenterNotStock		        = 2679, // 商城没有库存

	eUI_BuyConfirm            =2680,                //你确定要购买吗?

	//eUI_ShopNotItem            =2682,            //商店现在没有这么多物品
	eText_ShopRefeash        =2683,        //商店中的物品已刷新!
	eCannotRepairFashion                  = 2684, //不能修理时装
	//ePrivateShop_String0            = 2685,    //是否查看【%s】的个人商店？
	//eUI_InputGoldCovSilver    =         2686,//请输入要兑换金币的数量
	eText_OverCount            =2687,                //数量超过
	eText_Stallage_Default_Name             = 2688,	// %s 的商店

	//eText_BankTradePlayerNotMoney        = 2691,//玩家没有这么多钱
	//eText_BankTradeFalied                = 2692,//未知错误

	//eUI_Bank_LevelUp_Text_1 =2694,        //钱，确定升级银行?
	//eMsg_client_AddMoney = 2695,    //冲值
	eText_ItemMaxStoreNum                = 2696,//物品最大存储数目为:
	eText_Client_Doyou_Mend_CostGold        = 2697,    //修理共花费 %d 金 %d 铜,是否确认修理
	//eSing_client_C = 2698, //铜
	///////////////////////////////////////
	/// tip前缀
	//eTip_PreText_Normal						= 2698, // 基础
	//eTip_PreText_Addition1					= 2699,	// 附加1
	//eTip_PreText_Addition2					= 2700,	// 附加2
	//eTip_PreText_Addition3					= 2701,	// 附加3
	//eTip_PreText_Addition4					= 2702,	// 附加4
	//eTip_PreText_Addition5					= 2703,	// 附加5
	//eTip_PreText_Addition					    = 2704,	// 附加
	//eTip_PreText_KaiGuang					    = 2705,	// 开光
	//eTip_PreText_NoIdentify					= 2706, // 未鉴定
	//eTip_PreText_NoKaiGuang					= 2707, // 未开光

	eText_PrepareCost						= 2710, // 修理费用

	eText_ExPower							= 2711, // 斗气

	eText_Item_CurPageStorageFull           = 2714, //  仓库当前页已满，无法进行此操作！
	eText_Mount_StorageFull                 = 2715, // 坐骑仓库已满
	eText_Mount_CharCarryFull               = 2716, // 坐骑携带数量已达上限
	eText_Mount_InfoError                   = 2717, // 当前坐骑信息错误
	eText_Mount_ActivedNotAdmit             = 2718, // 出战坐骑无法放入仓库
	eText_Mount_StorageToCharErr            = 2719, // 仓库坐骑无法放入坐骑栏中
	eText_Mount_LearnSkill_CarryLvlLess     = 2720, // 坐骑携带等级不足 无法学习技能
	eText_Mount_LearnSkill_LvlLess          = 2721, // 坐骑等级不足 无法学习技能
	eText_Mount_LearnSkill_Failed           = 2722, // 无法学习坐骑技能

	eExchange_GloryNotEnough					= 2725, // 荣誉不够，不能进行此操作
	eText_Glory								= 2726, // 荣誉

	eTip_Resist_Coma						= 2730,	// 昏迷抗性
	eTip_Resist_Dread						= 2731,	// 恐惧抗性
	eTip_Resist_Silence						= 2732,	// 沉默抗性
	eTip_Resist_Slow						= 2733,	// 减速抗性

	eTip_sAddFPRestoreRate                  = 2734, // 怒气回复
	eTip_sAddEPRestoreRate                  = 2735, // 能量回复
	eTip_sAddAPRestoreRate                  = 2736, // 箭枝回复
	eTip_sAddBPRestoreRate                  = 2737, // 弹药回复 等待String添加

	eText_InfoTip_TeamInvite				= 2800, // 组队邀请
	eText_InfoTip_FriendInvite				= 2801, // 好友邀请
	eText_InfoTip_Convene					= 2802, // 召集令
	eText_InfoTip_Raise						= 2803, // 国家募捐
	eText_InfoTip_PlayerLevelUp				= 2804, // 人物升级
	eText_InfoTip_PetLevelUp				= 2805, // 宠物升级
	eText_InfoTip_FriendChat				= 2806, // 好友单聊
	eText_InfoTip_ImpeachKing				= 2807, // 弹劾国王
	eText_InfoTip_AnswerQst					= 2808, // 答题活动
	eText_InfoTip_GuildInvite				= 2809, // 帮会邀请
	eText_InfoTip_GuildMasterConvene				= 2810, // 帮主召集
	eText_InfoTip_GuildRaise				= 2811 , //帮会捐赠


	eText_LevelUp_ExpNotEnough              = 2900, // 经验不够，无法升级 
	eText_LearnSkill_LevelNotEnough         = 2901, // 等级不足无法学习技能
	eText_LearnSkill_GoldNotEnough          = 2902, // 金钱不足无法学习技能
	eText_LearnSkill_ExpNotEnough           = 2903, // 经验不足无法学习技能
	eText_LearnSkill_NoLearn                = 2904, //已经没有可学习的技能

	eText_LearnXinFa_LevelNotEnough         = 2920, // 等级条件不满足
	eText_LearnXinFa_GoldNotEnough          = 2921, // 金钱条件不满足
	eText_LearnXinFa_ExpNotEnough			= 2922,	//技能点数条件不满足
	eText_LearnXinFa_PreXinFaNotOk			= 2923,	//前置心法条件不满足
	eText_LearnXinFa_ProfessionNotOk		= 2924, //职业条件不满足
	eText_Configuration_XinFa_NotOk			= 2925,	//心法的配置文件不对
	eText_Configuration_Skill_NotOk			= 2926,	//技能的配置文件不对
	eText_LearnXinFa_Failure = 2927, //学习心法失败


	eWarning_CanNotPrivateChatBefore15			= 2980, //
	eWarning_CanNotMessageChatBefore15			= 2981, //
	eWarning_CanNotCountryChatBefore20			= 2982, //
	eWarning_CanNotPrivateChatToBefore15			= 2983, //
	eWarning_CanNotCountryChatNoCountry             = 2984, //没有国家不能使用国家频道聊天
	eWarning_CanNotCountryGYChat                = 2985, //你不是国家官员，不能使用此频道
	eText_SkillCanNotDrag											=3000,//被动技能无法拖动到其他位置
	eUI_SkillLevelup														= 3001,//你的技能等级提升了！
	eText_SkillLevelUp													= 3002,//技能等级升级到
	eText_SkillFailed_OnlyMounting							= 3003,//该技能只能骑乘状态下施放
	eText_SkillFailed_NotCorrectProfession				= 3004,//该技能只能%s使用
	eText_MountAlreadyLearnSkill								= 3005,//已经学会该技能，无法再次学习
	eTextPlayer_Break													= 3006,//打断
	eText_Get																	= 3007,//获得
	//     eUI_SillTyps_TargetType        =    3008,        //作用对象:
	eText_SkillFailed_UnableOperateInCurrentState                = 3008, // 在当前状态下，无法进行此操作
	eText_Skill_ChaseTarget                     = 3009, // 与目标距离过远，追击目标
	eAttack_Error_SafeArea                      = 3010, //安全区内无法攻击
	eText_SkillFailed_MustAtBack                = 3011, // 必须在目标背后才能施放此技能
	eText_SkillFailed_CannotUsePhysicsSkill     = 3012, // 当前状态不能使用物理技能
	eText_SkillFailed_CannotUseMagicSkill       = 3013, // 当前状态不能使用魔法技能
	eText_SkillFailed_TooFar					= 3014,	// 与目标距离过远，无法施放技能
	eText_SkillFailed_TooClose					= 3015,	// 与目标距离太近，无法施放技能
	eText_SkillFailed_NotEnoughMP				= 3016,	// 法力不足，无法施放此技能
	eText_SkillFailed_NotEnoughHP				= 3017,	// 气血不足，无法施放此技能
	eText_SkillFailed_NotEnoughExPower		    = 3018,	// 斗气不足，无法施放此技能
	eText_SkillFailed_WhenMounting				= 3019,	// 骑乘状态下，无法施放此技能
	eText_SkillFailed_NotCorrectTarget			= 3020,	// 不能对当前目标施放此技能
	eText_SkillFailed_NoTarget					= 3021,	// 请选择一个目标来施放技能
	eText_SkillFailed_NeedWeapon				= 3022,	// 没有装备武器，无法施放此技能
	eText_SkillFailed_WhenCoolDown				= 3023,	// 技能处于冷却中，无法施放
	eText_SkillFailed_NotFaceToTarget			= 3024,	// 必须要面对目标才能施放此技能
	eText_SkillFailed_CannotUseInFighting		= 3025, // 无法在战斗状态下施放此技能
	eText_SkillFailed_UseOnlyInFighting			= 3026,	// 只有处于战斗状态施放此技能
	eText_SkillFailed_Busy						= 3027,	// 已经有另一个动作处于进行中，无法施放此技能
	eText_SkillFailed_LackOfSomeItem			= 3028,	// 需要物品才能施放此技能
	eText_SkillFailed_HpLimit					= 3029,	// 血量条件不符合
	eText_SkillFailed_NeedPet					= 3030,	// 需要有召唤兽才能施放此技能
	eText_SkillFailed_CannotJump				= 3031,	// 跳跃中无法施放此技能
	eText_SkillFailed_InPrivateShop				= 3032,	// 摆摊状态下无法施放技能

	eClient_AddInfo_2slk_125        = 3301,        //任务[%s] 
	eClient_AddInfo_2slk_62        = 3302,        //"取消[%s]任务"
	//eClient_AddInfo_2slk_45        = 3303,        //任务[%s]
	eClient_get_new_task                    = 3304,    //新接任务 %s
	eText_Ask_Task            =3305,                    //是否放弃此任务
	eClient_task_AbandonTask        = 3306,    //此任务不可放弃!
	//eTell_Client_CannotTaskBCLevel        = 3307, //您的等级不够,不能接这个任务!
	eText_NeedItem            =3308,                    //需要任务物品
	eTextPlayer_QuestComp                = 3309, //[%s]任务完成
	eText_NoTaskItem					= 3310,	// 没有找到任务物品
	eText_NotEnoughTaskItem				= 3311,	// 提交任务物品不足

	eQuestType_1						= 3316,//主线任务
	eQuestType_2						= 3317,//支线任务
	eQuestType_3						= 3318,//活动任务
	eQuestType_4						= 3319,//副本任务
	eQuestType_5						= 3320,//官府任务
	eQuestType_6						= 3321,//循环任务
	eQuestType_7						= 3322,//巡城任务
	eQuestType_8						= 3323,//军需任务
	eQuestType_9						= 3324,//藏宝任务
	eQuestType_10						= 3325,//称号任务
	eQuestType_11						= 3326,//剧情任务
	eQuestType_12						= 3327,//趣味任务
	eQuestType_13						= 3328,//帮派任务
	eQuestType_14                       = 3329,//酒馆任务
	eQuestType_15                       = 3330,//皇榜任务
	eQuestType_16                       = 3331,//征伐任务
	eQuestType_17                       = 3332,//国运任务
	eQuestType_18                       = 3333,//出国任务
	eQuestType_19                       = 3334,//天行任务
	eQuestType_20                       = 3335,//探宝任务
	eQuestType_21                       = 3336,//奇遇任务
	eQuestType_22                       = 3337,//成就任务

	eText_QuestType_1					= 3350,//【主线】
	eText_QuestType_2					= 3351,//【支线】
	eText_QuestType_3					= 3352,//【活动】
	eText_QuestType_4					= 3353,//【副本】
	eText_QuestType_5					= 3354,//【官府】
	eText_QuestType_6					= 3355,//【循环】
	eText_QuestType_7					= 3356,//【巡城】
	eText_QuestType_8					= 3357,//【军需】
	eText_QuestType_9					= 3358,//【藏宝】
	eText_QuestType_10					= 3359,//【称号】
	eText_QuestType_11					= 3360,//【剧情】
	eText_QuestType_12					= 3361,//【趣味】
	eText_QuestType_13					= 3362,//【帮派】
	eText_QuestType_14                  = 3363,//【酒馆】
	eText_QuestType_15                  = 3364,//【皇榜】
	eText_QuestType_16                  = 3365,//【征伐】
	eText_QuestType_17                  = 3366,//【国运】
	eText_QuestType_18                  = 3367,//【出国】
	eText_QuestType_19                  = 3368,//【天行】
	eText_QuestType_20                  = 3369,//【探宝】
	eText_QuestType_21                  = 3370,//【奇遇】
	eText_QuestType_22                  = 3371,//【成就】

	//<!--selectbox-->
	eText_Quest_Select                  = 3375, //[%s]%d级

	eText_Quest_TaskDone                = 3376, //[%s]%s%s%s
	eText_Quest_TaskNone                = 3377, //[%s]%s%s"

	eText_Quest_TaskTrackDone           = 3378, //[%s]%s%s
	eText_Quest_TaskTrackNone           = 3379, //[%s]%s

	eText_Quest_NeedLevel               = 3390,//[Lv%d]
	eText_Quest_None                    = 3395,//(可接取)
	eText_Quest_Act                     = 3397,//(未完成)
	eText_Quest_Done                    = 3396,//(已完成)
	eText_Quest_MapName                 = 3398,//[%s]

	eText_Quest_Task                    = 3500, // {#fff4db30=任务:#}
	eText_Quest_TaskTarget              = 3501, //{#fff4db30=任务目标:#}
	eText_Quest_TaskDes                 = 3502, //{#fff4db30=任务描述:#
	eText_Quest_TaskReward              = 3503, //{#fff4db30=任务奖励:#}
	eText_Quest_TaskGold                = 3504, //{#fff4db30=金币奖励: #}
	eText_Quest_TaskExp                 = 3505, //{#fff4db30=经验奖励: %d#}
	eText_Quest_TaskMingWang            = 3506, //{#fff4db30=历练名望: %d#}
	eText_Quest_TaskGongXun             = 3507, //{#fff4db30=历练功勋: %d#}
	eText_Quest_TaskTitle               = 3508, //{#fff4db30=称号奖励: #}
	eText_Quest_TaskRongYu              = 3509, //{#fff4db30=历练荣誉: %d#}
	eText_Quest_TaskJiaozi              = 3510, //{#fff4db30=交子奖励: #}
	eText_Quest_TaskOK                  = 3511, //{#ff00ff00=好的#}
	eText_Quest_TaskLevel               = 3512, //{#ff00ff00=离开#}
	eText_Quest_TaskGuildContribute     = 3513, //{#fff4db30=历练帮贡:#} %d
	eText_Quest_TaskNeedItem            = 3514, //所需物品: %s (%ld/%ld)
	eText_Quest_TaskNeedMonster         = 3515, //所需杀怪: %s (%ld/%ld)
	eText_Quest_TaskAim						= 3516,//<String Id="3516" Value="目标: %s (%ld/%ld)"/>   
	eText_Quest_CountryMoney			=	3517, //{#fff4db30=国库资金奖励: %d#}


	eClient_AddInfo_2slk_124        = 3701,        //请选择要合成的物品！ 
	eText_CompSucess        =3702,        //合成成功
	eText_CompFail            =3703,            //合成失败
	eText_Material_Error_0    =3704,    //    原料不符合
	eText_Material_error_1    =3705,    //宝石等级已是最高级
	eClient_intensifying_str        = 3706,    //强化中...
	eSing_Reduce = 3707,
	eUI_IsCompound      = 3708, // 是否合成
	eStatusAddCompoundRate = 3709, //合成几率增加:%d%%
	eStatusAddIntensifyRate = 3710, //强化几率增加:%d%%
	eFiveXingDisplace_ProbTip = 3713,  //成功率:

	eFiveXingDisplace_ProbNum              = 3901,      //概率加成材料数量不符
	eFiveXingDisplace_ProbMaterial         = 3902,      //概率加成材料不符
	eFiveXingDisplace_JinDingLevel         = 3903,      //五行鉴定石等级不符
	eFiveXingDisplace_JinDingWrong         = 3904,      //五行鉴定石不符
	eFiveXingDisplace_LevelDistance        = 3905,      //两个装备等级相差太多
	eFiveXingDisplace_PartWrong            = 3906,      //装备部位不一样, 无法转移
	eFiveXingDisplace_NoFiveXingPart       = 3907,      //不是五行套装
	eFiveXingDisplace_NoFiveXing           = 3908,      //没有五行属性, 无法转移
	eFiveXingDisplace_NoExistPart          = 3909,      //装备不存在
	eFiveXingDisplace_Success              = 3910,      //五行转移成功
	eFiveXingDisplace_Faild                = 3911,      //五行转移失败

	eGangError_Change_AlreadlyBund = 4000,				//已经是同盟了"/>
	eGangError_Change_BundFull = 4001,			//" Value="同盟关系到达上限"/>
	eGangError_Change_InBund = 4002 ,			//<String Id="4002" Value="同盟关系，无法宣战"/>
	eGangError_Change_AlreadlyRupture = 4003,			//<String Id="4003" Value="已经是敌对关系"/>
	eGangError_Change_RuptureFull = 4004, 			//<String Id="4004" Value="敌对关系到达上限"/>
	eGangError_Change_InRupture = 4005,			//<String Id="4005" Value="目前是敌对关系，不能同盟"/>
	eGangError_Change_SelfLevelLess = 4006,			//<String Id="4006" Value="自己帮会等级不足，无法宣战"/>
	eGangError_Change_TargetLevelLess = 4007,			//<String Id="4007" Value="对方帮会等级不足，无法宣战"/>
	eGangError_Change_GreaterTargetLevel = 4008,			//<String Id="4008" Value="大于对方帮会的等级，无法宣战"/>
	eGangError_Change_NotEnoughMoney = 4009,			//<String Id="4009" Value="帮会没有足够的资金，无法宣战"/>
	eGangError_Change_NotEnoughGuild = 4010,

	eText_CountryBattle_King                = 4100, // 国王争夺战
	eText_CountryBattle_Dragon              = 4101, // 青龙战场
	eText_CountryBattle_Rosefinch           = 4102, // 朱雀战场

	eText_CountryBattle_EnterNotTime        = 4103, // 不是进入%s的时间，不能进入
	eText_CountryBattle_EnterNotGuild       = 4104, // 不是参与%s的帮会，不能进入
	eText_CountryBattle_NotCreate           = 4105, // %s副本还未创建出来
	eText_CountryBattle_GuildOwnRight       = 4106, // %s公会获得了进入%s的资格
	eText_CountryBattle_SignUp              = 4107, // %s报名开始，持续%s
	eText_CountryBattle_BattleBegin         = 4108, // %战斗开始，持续%s
	eText_CountryBattle_Open                = 4109, // %已开启，进入时间持续%s
	eText_CountryKing_ApplySuccess          = 4110, // %s公会第一次申请国王成功
	eText_CountryBattle_GuardSuccess        = 4111, // %s中，%s公会守护成功
	eText_CountryBattle_ChallengeSuccess    = 4112, // %s中，%s公会挑战成功
	eText_CountryBetray_Broadcast           = 4113, // %背叛了自己的国家%s
	eText_CountryBetray_Success             = 4114, // 叛国成功
	eText_CountryBetray_NoTeam              = 4115, // 叛国不能有队伍
	eText_CountryBetray_NoGuild             = 4116, // 叛国不能有帮派
	eText_CountryBetray_NoSameCountry       = 4117, // 不能叛往相同国家
	eText_CountryBetray_ErrorCountry        = 4118, // 错误的国家
	eText_CountryBetray_NoMoney             = 4119, // 没有足够的金钱
	eText_CountryBetray_NoMarry             = 4120, // 有夫妻关系不能改变国籍
	eText_CountryBetray_NoStudent           = 4121, // 有徒弟关系不能改变国籍
	eText_CountryBetray_NoTeacher           = 4122, // 有师傅关系不能改变国籍
	eText_CountryBetray_OncePerWeek         = 4123, // 一周只能改变一次国籍
	eText_CountryBattle_SignUpBeReplaced    = 4124, // 您的帮派在%s报名中被其他帮派顶替了
	eText_CountryBattle_QuitCountryWar		= 4125, // 一分钟后会自动离开战场

	eText_Country_BeWeak                    = 4150, // 您所在的国家变弱了
	eText_Country_KingChangeName            = 4151, // 国王%s更改了本国国号，国号为:%s
	eText_Country_ChangeNameSuccess         = 4152, // 更改国号成功
	eText_Country_ChangeNameNoRight         = 4153, // 您没有权限更改国号
	eText_Country_ChangeNameOnce            = 4154, // 一周只能修改一次国号
	eText_Country_ChangeNameError           = 4155, // 您输入的国号错误
	eText_Country_PleaseInputName           = 4156, // 请输入想要更改的国号
	eText_Country_ChangeNameTip             = 4157, // 国号只支持2个汉字
	eText_CountryWar_WillBegin              = 4158, // 屠城战将在30分钟后开始
	eText_CountryWar_Begin                  = 4159, // 屠城战开始
	eText_CountryWar_End                    = 4160, // 屠城战结束

	//eText_IfAskClearPwd                 =   4201,//您是否申请密码清除功能
	//eText_Succ_Of_App_ClearPwd          =   4202,//申请成功，15日后系统将自动清除物品加密密码。
	//eText_YouHaveAlreadyApplied         =   4203,//您已经申请过密码清除功能
	//eText_YouHaveLeft                   = 4204,//您还有
	//eText_DaysToClearItemProtectPwd     = 4205,//，天即可清除物品保护密码！
	//eText_ItemCannotBeenLocked           = 4206,//物品不能被加锁
	//eText_Lock                            = 4207, //IsLocked
	//eLockItemInfo         = 4208,//%d个物品已锁定，还可以锁定%d个物品!
	//eLockItemLimt            = 4209,//物品锁定限制已满!
	//eClient_AddInfo_2slk_26        = 4210,        //"请先设置物品加密密码"
	//eAsk_IsLockIntensify             =4211,               //是否锁定强化！花费500银票！
	//eTell_IntensifyMax             =4212,               //已经强化到最高级！
	//eTell_Locked             =4213,               //锁定强化过了的物品！
	//eSing_LockIntensify = 4214, //锁定强化！

	//eText_InputItemPwd                = 4216,    //请输入物品加密密码
	//eText_InputItemPwdAgain                = 4217,    //请重复输入加密密码
	//eText_InputPwdNotTheSame    = 4218,//两次输入的密码不一致
	//eText_ItemPwdError                  =4219,    //您输入的物品加密密码错误
	//eText_PwdNull                        = 4220, //物品加密密码不能为空  
	eClient_GameStageNextTime = 4400, //第%d波  剩余时间:%s
	eClinet_compound_string            = 4401,    //合成
	eClient_EctypeMap_Countdown        = 4402,      //副本剩余时间:%s

	eText_SplitFailed_ItemNotExist          = 4403, // 物品不存在，分解失败
	eText_SplitFailed_ItemIndexGuidError    = 4404, // 物品信息错误，分解失败
	eText_SplitFailed_ItemTypeLevelError    = 4405, // 只有%d级以上的生产武器才可被分解
	eText_SplitFailed_CantBeSplit           = 4406, // 此物品不可被分解
	eText_SplitFailed_QualityLevelError     = 4407, // 品质过低，无法分解
	eText_SplitFailed                       = 4408, // 分解失败
	eText_ConfirmSplit                      = 4409, // 是否需要分解 %s
	eText_SplitSuccess						= 4410, // 分解成功

	// 生产界面辅助材料Tips
	eText_CompoundMaterialTip_DaZao			= 4490,
	eText_CompoundMaterialTip_PengRen		= 4491,
	eText_CompoundMaterialTip_ChaYi			= 4492,
	eText_CompoundMaterialTip_LianYao		= 4493,
	eText_CompoundMaterialTip_JiaGong		= 4494,
	eText_CompoundMaterialTip_HeCheng		= 4495,

	eLuckGame_NextMission = 4500, //恭喜你的队伍获得了挑战下一关的资格"/>
	eLuckGame_Lost = 4501, //今天的挑战已经结束，请明天再来参加挑战"/>
	eLuckGame_Front = 4502, //上一关BOSS的怨念使他获得重生，勇敢的战斗吧"/>
	eLuckGame_Stay = 4503, //本一关BOSS的怨念使他获得重生，勇敢的战斗吧"/>
	eLuckGame_Jump = 4504, //恭喜你的队伍直接无视下关BOSS，获得前进两关的资格"/>
	eLuckGame_Double = 4505, //恭喜你的队伍获得了双倍奖励，快去寻找战利品吧"/>
	eLuckGame_Half = 4506, //很遗憾，你的队伍只获得了一半奖励，快去寻找战利品吧"/>

	eLuckGame_ConfirmGetAwards = 4510, //领取奖励后将无法继续挑战，是否确定领取"/>
	//eClient_actionList_0            = 4402,    //"拱手 /a1",
	//eClient_actionList_1            = 4403,    //"作揖 /a2",
	//eClient_actionList_2            = 4404,    //"激励 /a3",
	//eClient_actionList_3            = 4405,    //"拥抱 /a4",
	//eClient_actionList_4            = 4406,    //"举旗 /a5",
	//eClient_actionList_5            = 4407,    //"捧花 /a6",
	//eClient_actionList_6            = 4408,    //"亲吻 /a7",
	//eClient_actionList_7            = 4409,    //"正步走 /a8",
	//eClient_actionList_8            = 4410,    //"胜利的呼喊 /a9",
	//eClient_actionList_9            = 4411,    //"相依 /a10",
	//eClient_actionList_10            = 4412,    //"跪拜 /a11"



	eRegister_AlreadyExist				= 4700,//通行证已存在，请重新输入
	eRegister_EmptyPassport				= 4701,//通行证为空，请重新输入
	eRegister_EmptySupperPassword				= 4702,//超级密码为空，请重新输入
	eRegister_EmptyEmail				= 4703,//注册邮箱为空，请重新输入
	eRegister_ErrorPassword				= 4704,//登陆密码错误，请重新输入
	eRegister_ErrorPassword1				= 4705,//登陆密码长度由6-32个字符组成，区分大小写
	eRegister_ErrorSupperPassword				= 4706,//超级密码由6-32个字符组成，区分大小写
	eRegister_ErrorPassport				= 4707,//通行证长度由6-32位字母和数字组成，只能以字母开头
	eRegister_ErrorPassport1				= 4708,//通行证内含有禁用字符，请重新输入
	eRegister_ErrorEmail				= 4709,//邮箱错误，请重新输入
	eRegister_ErrorNewerCard				= 4710,//新手卡卡号错误，请重新输入
	eRegister_NotSamePassword				= 4711,//登陆密码填写不一致，请重新输入
	eRegister_NotSameSupperPassword				= 4712,//超级密码填写不一致，请重新输入
	eRegister_Agreement				= 4713,//请阅读并同意《武神通行证用户协议》和《武神通行证隐私权政策》
	eRegister_EmptyPassword				= 4714,//密码为空，请重新输入
	eRegister_OK				= 4715,//注册成功
	eRegister_Fail				= 4716,//注册失败
	eRegister_ErrorEmail1				= 4717,//安全邮箱长度为8-64位
	eRegister_CodeEmpty				= 4718,//验证码为空，请重新输入
	eRegister_CodeError				= 4719,//验证码输入错误，请重新输入

	//eLog_info_2slk_10    =4632,    //交易物品 开始 %s与%s




	//eRealAward_NameEmpty				= 4750,//请输入联系人名称
	//eRealAward_PhoneEmpty				= 4751,//请输入联系电话
	//eRealAward_EmailEmpty				= 4752,//请输入联系邮箱
	//eRealAward_CardEmpty				= 4753,//请输入身份证号码
	//eRealAward_EmailFormatError				= 4754,//邮箱格式错误，请重新输入
	//eRealAward_ItemError				= 4755,//该物品不存在，请仔细核对您的包裹物品
	//eRealAward_CardLengthError				= 4757,//身份证长度应为15或18位
	//eRealAward_Congratulation				= 4758,//恭喜您获得了“%s”！\n您可以通过官方网页中的获奖查询页面进行查询和领奖工作人员会尽快将奖励发放给您。





	eLog_info_2slk_33    =4654,    //清除状态 %s

	eClient_Err_Relive		= 4655, // 信春哥失败信息提示
	eText_Relive_FullHPMP	= 4656, // 奖励一次完美复活的机会j


	//<String Id="4801"  Value="升级成功"/>
	//<String Id="4802" Value="升级失败"/>
	//<String Id="4803" Value="该装备无法升级"/>
	//<String Id="4804" Value="金钱不足，无法升级"/>
	//<String Id="4805" Value="需要使用%s才能升级此装备"/>
	//<String Id="4806" Value="该装备已经满级，无法进行提升"/>
	//<String Id="4807" Value="道具等级过低，无法升级此装备"/>

	//<String Id="4811" Value="转换成功"/>
	//<String Id="4812" Value="转换失败"/>
	//<String Id="4813" Value="该装备无法转换"/>
	//<String Id="4814" Value="金钱不足，无法转换"/>

	eClient_SkillSuitUpgradeSuccess				= 4801, // 升级成功
	eClient_SkillSuitUpgradeFailed					= 4802, // 升级失败
	eClient_SkillSuitCannotUpgrade				= 4803, // 该装备无法升级
	eClient_SkillSuitUpgradeNoMoney			= 4804, // 金钱不足，无法升级
	eClient_SkillSuitUpgradeItemError			= 4805, // 需要使用%s才能升级此装备
	eClient_SkillSuitMaxLevel							= 4806, // 该装备已经满级，无法进行提升
	eClient_SkillSuitUpgradeLessItemLevel	= 4807, // 道具等级过低，无法升级此装备
	eClient_SkillSuitCannotUpStar					= 4808,//该物品无法升星

	eClient_SkillSuitChangeSuccess			= 4811, // 升级成功
	eClient_SkillSuitChangeFailed			= 4812, // 升级失败
	eClient_SkillSuitCannotChange			= 4813, // 该装备无法转换
	eClient_SkillSuitChangeNoMoney			= 4814, // 金钱不足，无法升级
	eClient_SkillSuitChangeItem1Error		= 4815, // 错误的转化道具
	eClient_SkillSuitChangeItem2Error		= 4816, // 错误的功勋材料
	eClient_SkillSuitLessChangeLevel		= 4817, // 提纯三级以上的装备才可进行转换

	eClient_FivexingTipUpdateSuccess        = 4831, //提纯成功
	eClient_FiveXingTipUpdateFailed         = 4832,  //提纯失败
	eClient_FiveXingTipUpdateNoCan          = 4833, //该装备无法提纯
	eClient_FiveXingTipUpdateNoMoney        = 4834, //金钱不足，无法提纯
	eClient_FiveXingTipMaterialError        = 4835, //材料不符，无法提纯
	eClient_FiveXingTipNoJianDing           = 4836, //需要先进行五行鉴定，才能进行提纯
	eClient_FiveXingUpdateNoLessThree       = 4837,//提纯三级以上的装备才可进行转换
	eClient_FiveXingTipJin                  = 4900,//&lt;#FFffff00五行:金
	eClient_FiveXingTipMu                   = 4901,//&lt;#FFffff00五行:木
	eClient_FiveXingTipShui                 = 4902,//&lt;#FFffff00五行:水
	eClient_FiveXingTipHuo                  = 4903,//&lt;#FFffff00五行:火
	eClient_FiveXingTipTu                   = 4904,//&lt;#FFffff00五行:土

	eClient_FiveXingTipJinHurt              = 4905, //%s+%d (水属性伤害+%d)
	eClient_FiveXingTipMuHurt               = 4906, //%s+%d (水属性伤害+%d)
	eClient_FiveXingTipShuiHurt             = 4907, //%s+%d (水属性伤害+%d)
	eClient_FiveXingTipHuoHurt              = 4908, //%s+%d (水属性伤害+%d)
	eClient_FiveXingTipTuHurt               = 4909, //%s+%d (水属性伤害+%d)
	//////////////////////////////////////////////////////////////////////////

	// 学所有技能的文字
	eText_LearnAllSkillCaption				= 4910, // 学习所有技能
	eText_LearnAllSkillText					= 4911, // 如果经验或者金钱不足，将无法全部学习，你确定还要继续吗？

	eText_MoveStarUpgradeSuccess			= 4950, // 升级成功
	eText_MoveStarUpgradeFailed				= 4951, // 升级失败
	eText_UpgradeFailed_IncorrectMaterial1	= 4952, // 该道具无法升级移星石
	eText_UpgradeFailed_IncorrectMaterial2	= 4953, // 材料不符，无法升级
	eText_UpgradeFailed_IncorrectMoveStarItem	= 4954, // 该移星石无法升级
	eText_UpgradeFailed_NotEnoughMoney		= 4955, // 金钱不足，无法升级

	eText_MaterialUpgradeSuccess			= 4960, // 合成成功
	eText_MaterialUpgradeFailed				= 4961,	// 合成失败
	eText_MaterialUpgradeFailed_NotEnoughMoney		= 4962, // 金钱不足，无法合成
	eText_MaterialUpgradeFailed_IncorrectMaterial1	= 4963, // 材料不符，无法合成
	eText_MaterialUpgradeFailed_IncorrectMaterial2	= 4964, // 该道具无法合成升星石
	eText_MaterialUpgradeFailed_IncorrectStarItem	= 4965, // 该升星石无法合成
	eText_MaterialUpgrade_PutOneItem		= 4966, // 请拆分后放入升星石
	eText_MaterialUpgrade_NotSameMaterial	= 4967, // 请放入相同的升星石

	eText_IntensifyStarFailed_LevelLimit	= 4970, // 装备等级需要达到60级
	eText_IntensifyStarFailed_StarLimit		= 4971, // 装备星级需要达到9星
	eText_IntensifyStarFailed_NoMaterial	= 4972, // 未放置必须道具，无法流光
	eText_IntensifyStarFailed_NoRateMaterial= 4973, // 至少放入一个流光概率加成道具
	eText_IntensifyStarFailed_NotEnoughMoney= 4974, // 金钱不足，无法流光
	eText_IntensifyStarFailed				= 4975, // 流光失败
	eText_IntensifyStarSucceed				= 4976, // 流光成功
	eText_IntensifyStarFailed_LackRateMaterial		= 4977, // 缺少增加概率材料
	eText_IntensifyStarFailed_WrongRateMaterialNum	= 4978, // 增加概率材料数量不正确
	eText_IntensifyStarFailed_IncorrectRateMaterial	= 4979, // 材料不符，无法流光

	eText_GIF_MouseRight		= 5354,		//gif鼠标图标右键
	eText_GIF_MouseLeft			= 5355,		//gif鼠标图标左键

	eText_DoubleExpDisable                  = 5493, // 双倍状态未激活 \n请点击“激活双倍经验”按钮
	eText_DoubleExpEnable                   = 5494, // 双倍时间启用中 \n默认将优先效果系统赠送的双倍时间
	eText_AutoAttack_BeginFailed_NoEnergy   = 5495, // 精力不足，无法自动挂机
	eText_AutoAttack_End_NoEnergy           = 5496, // 精力消耗完毕，停止自动挂机

	eText_ItemBind_ConfirmByDifInBound              = 5611, // 确认是否需要将绑定和不绑定的物品合一起
	eText_GuildSendMessageSuccess					= 5612,//请求信息已经发出
	//帮会
	eText_Guild_LevelGuild_Succeed = 5900,//离开帮会成功
	eText_Guild_LevelGuild_NotHaveGuild = 5901,//离开帮会不成功,没有加入任何帮会
	eText_Guild_LevelGuild_NotHaveRight = 5902,//离开帮会不成功,担任了职位, 无法直接退出帮派
	eText_Guild_LevelGuild_ChangeNotice = 5903,//修改公告的提示
	eText_Guild_TransferPosition_Master = 5904,//%s将帮主之位转让给%s，%s成为新帮主
	eText_Guild_TransferPosition_ViceMaster = 5905,// %s将副帮主之位转让给%s，%s成为新的副帮主
	eText_Guild_TransferPosition_FamilyMaster = 5906,//%s将堂主之位转让给%s，%s成为新堂主
	eText_Guild_IncreaseGuildMoney = 5907,//获得%d帮会资金
	eText_Guild_DecreaseGuildMoney = 5908,//失去%d帮会资金
	eText_Guild_IncreaseGuildExp = 5909,//获得%d帮会经验
	eText_Guild_DecreaseGuildExp = 5910,//失去%d帮会经验
	eText_Guild_IncreaseGuildLevel = 5911,//帮会等级提升到%d级
	// 
	eText_Guild_TransferSuccess	   =5950,//已成功转让职位
	eText_Guild_TransferNotHaveRight = 5951,//您没有转让职务的权限
	eText_Guild_TransferNotViceMaster=5952,//对方不是副帮主，不能被转让帮主职位
	eText_Guild_TransferLevelLess	 =5953,//对方等级不足，无法转让职务
	eText_Guild_TransferNotGuildMember=5954,//对方不是本帮成员，不能转让职务
	eText_Guild_TransferNotSameFamily =5955,//对方不是同一家族成员，不能转让族长职务
	eText_Guild_TransferIsKing		  =5956,//自己是国王，不能转让帮主
	// 
	eText_Guild_TimeLimit		  =5998,//离开帮派后24小时内,对方不能加入帮派
	eText_Guild_MasterCanNotZC    =5999,//家族长无法转出
	eText_Guild_AgreeJoin		   =6000,//同意加入帮派
	eText_Guild_CreateGuildSucceed = 6001, // 	<String Id="6001" Value="帮派创建成功"/>
	eText_Guild_InValideName = 6002, // <String Id="6002" Value="存在屏蔽字符，非法名字"/>
	eText_Guild_SameName = 6003, // <String Id="6003" Value="存在已相同名字的帮派"/>
	eText_Guild_AlreadyHadGuild = 6004, // <String Id="6004" Value="已经有帮派了，不能创建"/>
	eText_Guild_LevelLessThanThirty = 6005, // <String Id="6005" Value="等级不足30级"/>
	eText_Guild_NotEnoughMoney = 6006, // 	<String Id="6006" Value="没有足够的现银"/>
	eText_Guild_CreateFamilySucceed = 6007, // <String Id="6007" Value="分堂创建成功"/>
	eText_Guild_HaveNoRight = 6008, // 	<String Id="6008" Value="没有权限"/>
	eText_Guild_FamilyFull = 6009, // <String Id="6009" Value="分堂满了"/>
	eText_Guild_HaveSameFamily = 6010, // <String Id="6010" Value="存在相同名字的分堂"/>
	eText_Guild_ChangeSucceed = 6011, // <String Id="6011" Value="修改成功"/>
	eText_Guild_HaveNoRightChange = 6012, // <String Id="6012" Value="没有修改分堂名字的权利"/>
	eText_Guild_CanNotDeleteOrChangeEmptyFamily = 6013, // <String Id="6013" Value="空家族不能改名或者删除"/>
	eText_Guild_AssignSucceed = 6014, // <String Id="6014" Value="职位任命成功"/>
	eText_Guild_HaveNoRightAssign = 6015, // <String Id="6015" Value="没有权限任命"/>
	eText_Guild_SamePosition = 6016, // <String Id="6016" Value="已经是该职位"/>
	eText_Guild_HaveNoFamily = 6017, // 	<String Id="6017" Value="没有家族，不能任命为家族长"/>
	eText_Guild_KickOutGuildSucceed = 6018, // 	<String Id="6018" Value="踢出帮派成功"/>
	eText_Guild_HaveNoGuild = 6019, // 	<String Id="6019" Value="没有帮派"/>
	eText_Guild_KickGuildMemberFaild = 6020, // 	<String Id="6020" Value="无法踢人，该玩家有职位"/>
	eText_Guild_ChangeBangZhongSucceed = 6021, // 	<String Id="6021" Value="改变成功"/>
	eText_Guild_NoRightChange = 6022, // 	<String Id="6022" Value="没有权限，无法转移帮众"/>
	eText_Guild_NoNeedChange = 6023, // 	<String Id="6023" Value="相同的家族，不需要移动"/>
	eText_Guild_ChangeEmptyFamilyFaild = 6024, // 	<String Id="6024" Value="不能移动到空家族"/>
	eText_Guild_InviteSucceed = 6025, // 	<String Id="6025" Value="邀请成功"/>
	eText_Guild_MeHaveNoGuild = 6026, // 	<String Id="6026" Value="自己没有帮派"/>
	eText_Guild_NoRightInvite = 6027, // 	<String Id="6027" Value="没有邀请权限"/>
	eText_Guild_OtherCountry = 6028, // 	<String Id="6028" Value="不是本国的不能邀请"/>
	eText_Guild_PlayerOffline = 6029, // 	<String Id="6029" Value="对方不存在或者不在线"/>
	eText_Guild_HeHaveGuild = 6030, // 	<String Id="6030" Value="对方已有帮派"/>
	eText_Guild_LevelLessThanTwenty = 6031, // 	<String Id="6031" Value="对方等级不足20级，不能邀请加入帮派"/>
	eText_Guild_MemberFull = 6032, // 	<String Id="6032" Value="成员数已经满了"/>
	eText_Guild_RefuseJoin= 6033, // 	<String Id="6033" Value="拒绝加入帮派"/>
	eText_Guild_JoinGuildSucceed = 6034, // 	<String Id="6034" Value="加入帮派成功"/>
	eText_Guild_AlreadyInGuild = 6035, // 	<String Id="6035" Value="已有帮派无法申请"/>
	eText_Guild_LessThanApplyLevel = 6036, // 	<String Id="6036" Value="等级不足20级无法申请"/>
	eText_Guild_NotTheSameCountry = 6037, // 	<String Id="6037" Value="不是本国的不能申请"/>
	eText_Guild_MustWaitCoolTime = 6038, // 	<String Id="6038" Value="退帮以后24小时内不能加入帮派"/>
	eText_Guild_GuildIsNotExist = 6039, // 	<String Id="6039" Value="申请的帮派不存在"/>
	eText_Guild_TheDestGuildMemberFull = 6040, // 	<String Id="6040" Value="目标帮派成员数已经满了"/>
	eText_Guild_RefuseApply = 6041, // 	<String Id="6041" Value="拒绝申请加入"/>
	eText_Guild_TheAdminIsOffline = 6042, // 	<String Id="6042" Value="帮派管理不在线无法申请"/>
	eText_Guild_ActiveSucceed = 6043, // 	<String Id="6043" Value="激活成功"/>
	eText_Guild_NoRightActive = 6044, // 	<String Id="6044" Value="没有激活权限"/>
	eText_Guild_GuildLevelNotEnough = 6045, // 	<String Id="6045" Value="帮派等级不够，无法激活"/>
	eText_Guild_GuildExpNotEnough = 6046, // 	<String Id="6046" Value="没有足够的帮派经验无法激活"/>
	eText_Guild_AlreadyActived = 6047, // 	<String Id="6047" Value="已经激活成功"/>
	eText_Guild_FalseLevel = 6048, // 	<String Id="6048" Value="错误的等级"/>
	eText_Guild_GuildLevelUpSucceed = 6049, // 	<String Id="6049" Value="帮派升级成功"/>
	eText_Guild_NoRightLevelUp = 6050, // 	<String Id="6050" Value="没有升级权限"/>
	eText_Guild_NotEnoughGuildMoney = 6051, // 	<String Id="6051" Value="没有足够的帮派金钱"/>
	eText_Guild_NotEnoughGuildExp = 6052, // 	<String Id="6052" Value="没有足够的帮派经验"/>
	eText_Guild_IsMaxGuildLevel = 6053, // 	<String Id="6053" Value="已经是最大帮派等级"/>
	eText_InfoTip_GuildTanHe				= 6055, // 	<String Id="6055" Value="帮会弹劾"/>
	eText_Guild_GuildInvite			= 6054,	//<String Id="6054" Value="帮会邀请"/>
	eText_InfoTip_ApplyGuild					= 6056, // 	<String Id="6056" Value="入帮申请"/>
	eText_Guild_InviteJoinGuild = 6057, // 	<String Id="6057" Value="邀请您入帮"/>
	eText_Guild_FaQiTanHe = 6058, // 	<String Id="6058" Value="%s发起帮派弹劾"/>
	eText_Guild_ApplyJoinGuild = 6059, // 	<String Id="6059" Value="%s申请入帮"/>
	eText_Guild_NoBuyRight = 6060, //	<String Id="6060" Value="没有购买权限"/>
	eText_Guild_GuildShopNoActive = 6061, //<String Id="6061" Value="帮派商店没有激活"/>
	eText_Guild_ItemNotExist = 6062, //	<String Id="6062" Value="没有此物品出售"/>
	eText_Guild_NotEnoughOffer = 6063, //	<String Id="6063" Value="没有足够的帮贡"/>
	eText_Guild_ErrorShopLevel = 6064, //	<String Id="6064" Value="错误的商店等级"/>
	eText_Guild_SomeJoinSomeGuild = 6065, //	<String Id="6065" Value="玩家%s加入了%s帮派"/>
	eText_Guild_SomeLeaveSomeGuild = 6066, //	<String Id="6066" Value="玩家%s离开了帮派"/>
	eText_Guild_TanHeGuildResult = 6067, //<String Id="6067" Value="%s弹劾帮派%s"/>
	eText_Guild_GuildDisband = 6068, //<String Id="6068" Value="%s帮派解散了"/>
	eText_Guild_GuildInviteMessage = 6069, //<String Id="6069" Value="%s邀请你加入%s帮会"/>
	eText_Guild_UnableAppointMyself = 6070, //<String Id="6070" Value="不能对自己进行此操作"/>
	eText_Guild_SelectNothing = 6071, //<String Id="6071" Value="没有选中帮成员，不能进行此操作"/>
	eText_Guild_UnableTansferPositon = 6072, //    <String Id="6072" Value="不能越级进行此操作"/>
	eText_Guild_ApplyingMessageSending = 6073, //<String Id="6073" Value="申请已经发出，请等待回音！"/>
	eText_Guild_DelMember = 6074, //<String Id="6074" Value="确定要将该成员:%s 从帮会开除！"/>
	eText_Guild_DelMemberTile = 6075, //<String Id="6075" Value="帮会开除！"/>
	eText_Guild_UnReachTanHeTime = 6076, //<String Id="6076" Value="没有到达弹劾时间"/>
	eText_Guild_AlreadyBeTanHe = 6077, //<String Id="6077" Value="已有人发起了弹劾帮主"/>
	eText_Guild_LevelLessThanNeed = 6078, //<String Id="6078" Value="等级不足无法弹劾"/>
	eText_Guild_MaxExp = 6079, //<String Id="6079" Value="帮派经验已达到最大上限"/>
	eText_Guild_NoEnoughMoneyTanHe = 6080, //<String Id="6080" Value="没有足够的金钱无法弹劾"/>
	eText_Guild_OnLineLess = 6081, //<String Id="6081" Value="帮派在线成员少于20个无法发起弹劾！"/>
	eText_Guild_GuildMasterConvene = 6082, //<String Id="6082" Value="帮主召集阁下去%s:%s,是否响应召集令?"/>
	eText_Guild_OfferNotEnoughOffer = 6083,//<String Id="6083" Value="没有足够的帮贡"/>
	eText_Guild_OfferMaxGuildExp = 6084, //<String Id="6084" Value="帮派经验已经到达最大值了"/>
	eText_Guild_ReleaseSuccess = 6085, //<String Id="6085" Value="改变成功"/>6076, //
	eText_Guild_ReleaseNoRight = 6086,  //<String Id="6086" Value="没有权限"/>//
	eText_Guild_ReleaseLevelNoEnough = 6087,//<String Id="6087" Value="帮派等级不够"/>6076, //
	eText_Guild_ReleaseErrorTime = 6088,//<String Id="6088" Value="必须在22点以前发布"/>= 6076, //
	eText_Guild_ReleaseAlreadyRelease = 6089,//<String Id="6089" Value="已经发布了"/>6, //
	eText_Guild_ReleaseNotEnoughMoney = 6090,//<String Id="6090" Value="没有足够的金钱"/>76, //
	eText_Guild_ReleaseQuestError = 6091, //<String Id="6091" Value="不能发布此任务"/>//
	eText_Guild_DisbandTime = 6092, //<String Id="6092" Value="通知:由于阁下的帮派长时间帮众人数不达要求，系统将于%s解散贵帮！"/>//
	eText_Guild_ShopLevelUpSuccess = 6093, //<String Id="6093" Value="帮会商店升级成功"/>//
	eText_Guild_SbCreateGuild = 6094, //<String Id="6093" Value="通知:%s创建了%s帮！"/>//
	eText_Guild_GuildDenoteMoneyNotEnough = 6095, //<String Id="6095" Value="您当前的金钱不足"/>

	eFriend_MySignature						= 6096,//请输入心情描述
	eFriend_GroupName						= 6097,//请输入新的分组名称
	eFriend_Error_FullGroup					= 6098,//您目前的分组已满
	eFriend_Error_GroupRepeat				= 6099,//分组名称重复请重新输入
	eFriend_Warning_DeleteGroup				= 6100,//您确定要将该分组删除
	eFriend_FriendTag						= 6101,//请输入好友备注
	eFriend_Error_DefaultGroup				= 6102,//默认分组不能删除
	eFriend_ChangeFriendToGroup				= 6103,//您是否要移动:%s好友到
	eFriend_Error_Name                      = 6104,//未找到您所输入的玩家名称
	eText_Guild_AlreadyHaveFamily = 6105,//对方已经是堂主
	eText_Stallage_ChangeName               = 6110, // 请输入摊位名称
	eText_GuildChangeNameSuccess		=6111,//帮派分堂改名
	eText_GuildHaveNoFamily						=6112,//还没有分堂
	eText_Guild_GuildCreateSystemMessage = 6200, //		
	eText_Guild_GuildDenote = 6201,	//<String Id="6201" Value="帮会捐献说明:帮会每日帮主发起捐献一次，捐献的金钱帮会可以用来筹集帮会资金，可以开启更多的帮会任务和可以进行帮会升级。"/>
	eText_Guild_AgreeTanHe = 6202,	 	//<String Id="6202" Value="您同意弹劾本帮帮主"/>
	eText_Guild_DisagreeTanHe = 6203,	//<String Id="6203" Value="您不同意弹劾本帮帮主"/>,
	eText_Guild_ImpeachSend = 6204,	 	//<String Id="6204" Value="您发起了弹劾本帮帮主的请求，请等待帮会成员回应情况"/>
	eText_Guild_ImpeachSuccess = 6205,	//<String Id="6205" Value="%s弹劾本帮帮主成功，%s成为了本帮新的帮主"/>,
	eText_Guild_ImpeachFailed = 6206,	//<String Id="6206" Value="%s弹劾本帮帮主没有达到弹劾成功的要求，弹劾失败"/>
	eText_Guild_Master = 6207,
	eText_Guild_ViceMaster = 6208,
	eText_Guild_Tangzhu = 6209,
	eText_Guild_Bangzhong = 6210,
	eText_Guild_CanNotTransferPositionWhenIsKingGuild = 6211,//国王帮帮主无法转让职位
	eText_ShiTu_GetExpAndMasterValueByYourStudent = 6212,//徒弟升级，师傅获得经验与威望
	eText_ShiTu_GetExpAndMasterValueByYourGrandStudent = 6213,//徒弟的徒弟升级，师傅获得经验与威望

	eExitTip_InfoMore						= 6220,//详情

	eText_MoneyInput_Trade                  = 6255, // 请输入金额
	eText_MoneyInput_CountryDonate          = 6256, // 国家资源募捐
	eText_MoneyInput_GuildDonate            = 6257, // 帮会资源募捐
	eText_MoneyInput_DonateLimit            = 6258, // 您最多可募捐%s
	eText_CountryRise_Broadcast             = 6259, // %s为本国募捐了%s

	//lyh++ 服务器日志string 从6300 - 6900 都是服务器日志区间 
	//==================================================================
	eServerLog_Min                           = 6300,
	eServerLog_JiaoYiBegin                        = 6301,
	eServerLog_JiaoYiByMoney                      = 6302,
	eServerLog_JiaoYiByJingDing                      = 6303,
	eServerLog_JiaoYiByItem                     = 6304,
	eServerLog_JiaoYiByMount                     = 6305,
	eServerLog_JiaoYiByPet                     = 6306,
	eServerLog_JiaoYiEnd                     = 6307,
	eServerLog_FunExit                     = 6308,
	eServerLog_EnterGameServer                     = 6309,
	eServerLog_RoleShengWang                     = 6310,
	eServerLog_RoleLevJingyan                     = 6311,
	eServerLog_Mount1                     = 6312,
	eServerLog_Mount2                     = 6313,
	eServerLog_Mount3                    = 6314,
	eServerLog_Mount4                     = 6315,
	eServerLog_RoleChenghao                     = 6316,
	eServerLog_SkillUp                     = 6317,
	eServerLog_DBFlyMap                    = 6318,
	eServerLog_UseItem                  = 6319,
	eServerLog_NOrecord                  = 6320,
	eServerLog_DeleteItem                  = 6321,
	eServerLog_FlyMapError                  = 6322,
	eServerLog_NoUseSkill                   = 6323,
	eServerLog_NoUseSkill1                 = 6324,
	eServerLog_NoUseSkill2                = 6325,
	eServerLog_NoUseSkill3                = 6326,

	eServerLog_NoUseJobSkill                   = 6327,
	eServerLog_NoUseJobSkill1                 = 6328,
	eServerLog_NoUseJobSkill2                = 6329,
	eServerLog_NoUseJobSkill3                = 6330,

	eServerLog_NoUseDaoHang                   = 6331,
	eServerLog_NoUseDaoHang1                 = 6332,
	eServerLog_NoUseDaoHang2                = 6333,
	eServerLog_NoUseDaoHang3                = 6334,

	eServerLog_DropItemByDead              = 6335,
	eServerLog_DropItemByDead1              = 6336,

	eServerLog_NoFindChenghaoAdd          =6337,
	eServerLog_HeroDoneTiaozhuan          =6338,
	eServerLog_HeroToCharServer          =6339,
	eServerLog_HeroToGameServer            = 6340,
	eServerLog_HeroToOther            = 6341,
	eServerLog_HeroBeT            = 6342,
	eServerLog_UseHeroNoThisAccount            = 6343,

	eServerLog_EnterWorldBeT            = 6344,
	eServerLog_AddItemOK           = 6345,
	eServerLog_AddItemNoOK            = 6346,

	eServerLog_MoveItemSTD            = 6347,
	eServerLog_MoveItemDTS            = 6348,

	eServerLog_HeroBeT1            = 6349,

	eServerLog_ContGetMsg   = 6350,
	eServerLog_DBAkCharInfoError   = 6351,
	eServerLog_DBAkEnterWorldBeT   = 6352,
	eServerLog_GetMoneyZuoBi   = 6353,
	eServerLog_CunMoney   = 6354,
	eServerLog_QuMoney   = 6355,
	eServerLog_CunMoneyZuoBi   = 6356,
	eServerLog_QuestNoFind   = 6357,
	eServerLog_UseItemError   = 6358,
	eServerLog_GetMoreJingDing   = 6359,
	eServerLog_GetKard   = 6360,
	eServerLog_ItemPosChange   = 6361,
	eServerLog_GetItemByHuiGou   = 6362,
	eServerLog_JiFenDuiHuanNoOk   = 6363,
	eServerLog_JiFenDuiHuanNoOk1   = 6364,
	eServerLog_JiFenDuiHuanOk   = 6365,
	eServerLog_DeleMail   = 6366,
	eServerLog_OpenMail   = 6367,
	eServerLog_MoneyMail   = 6368,
	eServerLog_ItemMail   = 6369,
	eServerLog_CreateRoleNoOk   = 6370,
	eServerLog_CreateRole   = 6371,
	eServerLog_QingQiuTiaoZhuan   = 6372,
	eServerLog_QingQiuTiaoZhuan1  = 6373,
	eServerLog_YanChiLiHai  = 6374,
	eServerLog_QingQiuToMap  = 6375,
	eServerLog_QuestOK  = 6376,
	eServerLog_GetOrSaveMoney  = 6377,
	eServerLog_JiShou  = 6378,
	eServerLog_HeChengDelItem  = 6379,
	eServerLog_HeChengDelItem2  = 6380,
	eServerLog_UpStar  = 6381,
	eServerLog_IdentifyOk  = 6382,
	eServerLog_LiuJinOk  = 6383,
	eServerLog_IdentifyOk2  = 6384,
	eServerLog_LiuJinOk2  = 6385,
	eServerLog_OpenHole  = 6386,
	eServerLog_XiangQian  = 6387,
	eServerLog_ChaiXieBaoshi  = 6388,
	eServerLog_TiHuanBaoshi  = 6389,
	eServerLog_LingHunMingke  = 6390,
	eServerLog_UpNoFindNewItem  = 6391,
	eServerLog_UpItemOk = 6392,
	eServerLog_SameLevItemKeepValue = 6393,
	eServerLog_UnSameLevItemKeepValue = 6394,
	eServerLog_FuWenBuXiLanShiBai = 6395,
	eServerLog_FuWenBuXiLanChengGong = 6396,
	eServerLog_HuShenFuXiLanChengGong = 6397,
	eServerLog_NotJiLuByTime = 6398,
	eServerLog_OnLineHaveErrorItemInBag = 6399,
	eServerLog_CreateFromDataItemDuoCiChuXian = 6400,
	eServerLog_SendMail = 6401,
	eServerLog_Getmount = 6402,
	eServerLog_Delmount = 6403,
	eServerLog_GetPet = 6404,
	eServerLog_DelPet = 6405,
	eServerLog_WaiGuaXingWei = 6406,
	eServerLog_LingQuMail = 6407,
	eServerLog_LingQuMail1 = 6408,
	eServerLog_LingQuMail2 = 6409,
	eServerLog_Block = 6410,
	eServerLog_FuBenExit = 6411,
	eServerLog_CantFindMap = 6412,
	eServerLog_GetPoint = 6413,
	eServerLog_BagSize = 6414,
	eServerLog_leaveFail = 6415,
	eServerLog_EnterFail = 6416,
	eServerLog_CurScript = 6417,
	eServerLog_DoRideFail = 6418,
	eServerLog_Deadmap = 6419,
	eServerLog_UseBotCommand = 6420,
	eServerLog_UseGmCommand = 6421,

	eServerLog_FangChenMi1 = 6422,
	eServerLog_FangChenMi2 = 6423,
	eServerLog_FangChenMi3 = 6424,
	eServerLog_FangChenMi4 = 6425,
	eServerLog_FangChenMi5 = 6426,
	eServerLog_DeleRole = 6427,
	eServerLog_DeleAllGataClient = 6428,

	eServerLog_UpStar_Material = 6429,
	eServerLog_UpStar_ProtectMaterial = 6430,


	eServerLog_Max                          = 6900,
	//==================================================================
	//屠城战
	eText_CountryBattle_CountryName         = 6915, // %s国击杀:
	eText_CountryBattle_KillNumber          = 6916, // %d人！

	//帮会战
	eText_GuildCamp_TimeToCampStart = 6919,//离帮会开始
	eText_GuildCamp_TimeToCampEnd = 6920,//离帮会结束

	// Begin复活界面
	/*"您已被~%s_击杀，可选择“转世重生”，或倒计时结束将您复活到王城（234，366）。\n
	%s级以下玩家每天可免费使用%s次原地复活，%s级以上每天可免费使用%s次。\n
	免费原地复活使用完后，若再使用原地复活，需消耗复活丹或元宝，系统将优先使用包裹中的复活丹，当复活丹消耗完，则前三次复活，每次扣除1元宝，第四次开始扣除2元宝。\n
	您今天还有%d次免费原地复活。*/
	eReliveUI_Relive	= 6924,//转世复活 		
	eReliveUI_Entrance	= 6925,//副本入口复活
	eReliveUI_Battle	= 6926,//战场复活
	// End复活界面
	eText_GuildCamp_Tip					= 7000, //帮会战Tip
	eText_GuildCamp_FlyToNpc			= 7001, //帮会战，TransferToNpc上显示的文字
	eText_GuildCamp_EnterBattleFiled = 7002,//进入帮会战界面上的说明
	eText_GuildCamp_EnterBattleReq	= 7003,//请求进入消息已发出
	eText_GuildCamp_TimeBeforeBattle = 7004,//提示:还没有进入帮会战阶段，敬请等候！
	eText_GuildCamp_NotSignUp = 7005, //提示:必须是报名帮派才能进入帮会战场！
	eText_GuildCamp_BattleResult = 7006,//帮派战结果
	eText_GuildCamp_SignUpSuccess = 7007,//报名成功
	eText_GuildCamp_WrongTime = 7008,//不是报名时间
	eText_GuildCamp_MustMaster = 7009,//必须是帮主才能报名
	eText_GuildCamp_MemberNumNotEnough = 7010,//帮派成员不足
	eText_GuildCamp_AlreadySignUp = 7011,//已经报名了
	eText_GuildCamp_BullSystem_SignUp = 7012,//帮会战报名的系统公告
	eText_GuildCamp_BullSystem_Prepare = 7013,//帮会战准备状态的系统公告
	eText_GuildCamp_BullSystem_Enter = 7014,//进入帮会战场状态的系统公告
	eText_GuildCamp_BullSystem_Fight = 7015,//战场战斗状态的系统公告
	eText_GuildCamp_BullSystem_Over = 7016,//帮会战结束的系统公告
	eText_GuildCamp_BullSystem_MatchNoTeam = 7017,//"对不起，今日由于贵帮是最后一个报名，且总帮派报名数为奇数，所以贵帮没有竞技对手，不能参加今日帮派战，请下次提早申请！"/>
	eText_GuildCamp = 7018,//帮会争夺战

	eText_KingCamp_EnterBattleInfo = 7030,//国王争夺战进入框上的提示
	eText_KingCamp_TimeToCampStart = 7031,//离国王争夺战开始
	eText_KingCamp_TimeToCampEnd = 7032,//离国王争夺战结束
	eText_Camp_SignUpReplace = 7033,// 通知帮派帮主, 你的报名中被其他帮派顶替了
	eText_Camp_CountryBattleGuild = 7034,// 全国广播某个帮派获得了战场资格
	eText_Camp_CountryBattleResult = 7035,// 通知国家战场结果
	eText_KingCamp_Tip = 7036,// 国王争夺战
	eText_KingCamp_FlyToNpc			= 7037, //国王战，TransferToNpc上显示的文字
	eText_KingCamp_SignUpEnd_MustBeEnterInThreeMin			= 7038,//全国广播:国王争夺战报名结束，挑战帮和国王帮成员请在3分钟内进入战场
	eText_KingCamp_SignUpTime			= 7039,//国王争夺战开始报名。
	eText_KingCamp_FightStart = 7040,//国王争夺战开始
	eText_KingCamp_EnterBattleReq	= 7041,//请求进入消息已发出
	eText_Camp_LevelLess	= 7042,//等级不足
	eText_Camp_MaxCount	= 7043,//人数已满
	eText_KingCamp_HaveFourLive = 7044,//还剩4条命
	eText_KingCamp_HaveThreeLive = 7045,//还剩3条命
	eText_KingCamp_HaveTwoLive = 7046,//还剩2条命
	eText_KingCamp_HaveOneLive = 7047,//还剩1条命
	eText_KingCamp_HaveZeroLive = 7048,//还剩0条命


	eText_CountryTitle_King					=8700, //国王
	eText_CountryTitle_General				=8701, //大将军
	eText_CountryTitle_Queen				=8702, //王后
	eText_CountryTitle_CouncilorLeft		=8703, //司马
	eText_CountryTitle_CouncilorRight		=8704, //丞相
	eText_CountryTitle_CaptorLeft			=8705, //左将军
	eText_CountryTitle_CaptorRight			=8706, //右将军
	eText_CountryTitle_KingGuard			=8707, //国王守护卫队
	eText_CountryTitle_Dragon				=8708, //青龙之主
	eText_CountryTitle_DragonGuard			=8709, //青龙守护
	eText_CountryTitle_Rosefinch			=8710, //朱雀之主
	eText_CountryTitle_RosefinchGuard		=8711, //朱雀守护

	eText_Country_Appoint_Already			=8720, //已经是该职位
	eText_Country_Appoint_BeAppoint			=8721, //被任命
	eText_Country_Appoint_BeDismiss			=8722, //被罢免	
	eText_Country_Appoint_NoGuild		    =8723, //没有公会
	eText_Country_Appoint_NoItem			=8724, //没有任免官员的物品

	// 带颜色的
	eText_CountryTitle_King_Col				=8730, //国王
	eText_CountryTitle_General_Col			=8731, //大将军
	eText_CountryTitle_Queen_Col			=8732, //王后
	eText_CountryTitle_CouncilorLeft_Col	=8733, //司马
	eText_CountryTitle_CouncilorRight_Col	=8734, //丞相
	eText_CountryTitle_CaptorLeft_Col		=8735, //左将军
	eText_CountryTitle_CaptorRight_Col		=8736, //右将军
	eText_CountryTitle_KingGuard_Col		=8737, //国王守护卫队
	eText_CountryTitle_Dragon_Col			=8738, //青龙之主
	eText_CountryTitle_DragonGuard_Col		=8739, //青龙守护
	eText_CountryTitle_Rosefinch_Col		=8740, //朱雀之主
	eText_CountryTitle_RosefinchGuard_Col	=8741, //朱雀守护



	eText_CountryConvene_Distribute			=8750, //发布了召集令

	eText_CountryConvene_NotRight			=8751, //无权限
	eText_CountryConvene_TimeLimit			=8752, //次数限制
	eText_CountryConvene_NotEnoughMoney		=8753, //缺钱
	eText_CountryConvene_Success			=8754, //发布成功

	eText_CountryConvene_YesOrNo			=8760, //是否前往

	eText_CountryBattle_SignUp_Success      = 8770, // 战场报名成功
	eText_CountryBattle_SignUp_NotTime      = 8771, // 不是报名时间不能报名
	eText_CountryBattle_SignUp_MustMaster   = 8772, // 必须是帮会长才可以报名
	eText_CountryBattle_SignUp_LevelLess    = 8773, // 帮会必须达到2级才能报名
	eText_CountryBattle_SignUp_MemberLess   = 8774, // 帮会成员必须达到30人才能报名
	eText_CountryBattle_SignUp_StrengthLess = 8775, // 帮会实力不足其他报名帮会, 无法报名
	eText_CountryBattle_SignUp_MoreMoney    = 8776, // 没有足够的帮贡
	eText_CountryBattle_SignUp_Already      = 8777, // 已经报名了
	eText_CountryBattle_SignUp_CanNot       = 8778, // 不能报名此战场                       

	eText_Country_PlayerBeSilence            =8850, // 被禁言
	eText_Country_PlayerBePrison             =8851, // 被囚禁
	eText_Country_PlayerBeFree               =8852, // 被赦免

	eText_CountryPos_King					 =8890, // 国王
	eText_CountryPos_Queen					 =8891, // 王后
	eText_CountryPos_LCouncilor				 =8892, // 司马
	eText_CountryPos_RCouncilor				 =8893, // 丞相
	eText_CountryPos_General				 =8894, // 大将军
	eText_CountryPos_LCaptor				 =8895, // 左将军
	eText_CountryPos_RCaptor				 =8896, // 右将军
	eText_CountryPos_QueenMale				 =8897, // 亲王

	eText_Country_Silence					 =8900,	// 禁言
	eText_Country_Prison					 =8901,	// 囚禁
	eText_Country_Free						 =8902,	// 赦免
	eText_Country_CountLeft					 =8903, // 本日剩余次数
	eText_Country_Tips						 =8904, // 提示
	eText_Country_AppointDaJiangJun			 =8905, // 任命大将军
	eText_Country_AppointSiMa				 =8906, // 任命司马
	eText_Country_AppointChengXiang			 =8907, // 任命丞相
	eText_Country_AppointZuoJiangJun		 =8908, // 任命左将军
	eText_Country_AppointYouJiangJun		 =8909, // 任命右将军

	eText_Country_Task_GuoYun				 =8910,	//国运令
	eText_Country_Task_ChuGuo				 =8911,	//出国令
	eText_Country_Task_TanBao				 =8912,	//探宝令
	eText_Country_Task_TianXing				 =8913,	//天行令
	eText_Country_Task_NotDbt				 =8914,	//未发布
	eText_Country_Task_Dbt					 =8915,	//发布

	eText_Country_Raise_Success				 =8916,	//募集资金成功
	eText_Country_Raise_NotRight			 =8917, //没有权限
	eText_Country_Raise_TimeLimit			 =8918, //一天只能募集一次

	eText_Country_Broadcast_Success			 =8919, //发布公告成功
	eText_Country_Broadcast_NotRight		 =8920, //没有权限
	eText_Country_Broadcast_TimeLimit		 =8921, //次数限制
	eText_Country_Broadcast_NotEnoughMoney	 =8922, //金钱不足

	eText_Country_Appoint_NotFound			 =8923,	//未找到该玩家
	eText_Country_Appoint_Success			 =8924, //任命官员成功
	eText_Country_Appoint_NotRight			 =8925, //您没有权限任命官员
	eText_Country_Appoint_NotCountryMember	 =8926, //不是本国玩家不能任命为官员
	eText_Country_Appoint_NotOnline			 =8927, //您任命的玩家不在线，无法完成任命
	eText_Country_Appoint_LevelLess			 =8928, //您任命的玩家不足45级，无法任命为官员
	eText_Country_Dismiss_Success			 =8929, //罢免官员成功
	eText_Country_Dismiss_NotRight			 =8930, //您没有权限罢免官员

	eText_Country_Slience_Success			 =8931, //该玩家已被您禁言
	eText_Country_Slience_NotRight			 =8932, //您没有禁言的权限
	eText_Country_Slience_TimeLimit			 =8933, //您每天最多只能禁言3次
	eText_Country_Slience_NotEnoughMoney	 =8934, //国家资金限制，暂时不用
	eText_Country_Slience_NotOnLine			 =8935, //目标玩家现在不在线，无法对其禁言
	eText_Country_Slience_NotSameCountry	 =8936, //目标玩家不是本国国民，您无权对其禁言

	eText_Country_Prison_Success			 =8937, //该玩家已被您囚禁
	eText_Country_Prison_NotRight			 =8938, //您没有囚禁的权限
	eText_Country_Prison_TimeLimit			 =8939, //您每天最多只能囚禁他人3次
	eText_Country_Prison_NotEnoughMoney		 =8940, //国家资金限制，暂时不用
	eText_Country_Prison_NotOnLine			 =8941, //目标玩家现在不在线，无法将其囚禁
	eText_Country_Prison_NotSameCountry		 =8942, //目标玩家不是本国国民，您无权将其囚禁

	eText_Country_Free_Success				 =8943, //该玩家已被您赦免
	eText_Country_Free_NotRight				 =8944, //您没有赦免的权限
	eText_Country_Free_TimeLimit			 =8945, //您每天最多只能赦免他人3次
	eText_Country_Free_NotEnoughMoney		 =8946, //国家资金限制，暂时不用
	eText_Country_Free_NotOnLine			 =8947, //目标玩家现在不在线，无法将其赦免
	eText_Country_Free_NotSameCountry		 =8949, //目标玩家不是本国国民，您无权将其赦免

	eText_Country_Operate_Slience			 =8950, //您被国王禁言了
	eText_Country_Operate_Prison			 =8951, //您被国王囚禁了
	eText_Country_Operate_Free				 =8952, //您被国王赦免了

	eText_Country_Task_Success				 =8953, //国务发布成功
	eText_Country_Task_NotRight				 =8954, //您没有权限发布国务
	eText_Country_Task_Already				 =8955, //该国务已经发布
	eText_Country_Task_NotEnoughMoney		 =8956, //国家资源不足，无法发布国务

	eText_Country_Task_BullBegin			 =8957, //已经发布
	eText_Country_Task_BullEnd				 =8958, //已经结束

	eText_Country_Donate_Success			 =8960,	//募集成功
	eText_Country_Donate_LevelLess			 =8961,	//人物等级不够
	eText_Country_Donate_NotEnoughMoney		 =8962,	//人物金钱不足
	eText_Country_Donate_ErrorRaiseMoney	 =8963,	//募集金钱超过最大值
	eText_Country_Donate_NotRaiseTime		 =8964,	//不在募集时段 不能募集
	eText_Country_Donate_CountryMoneyMax	 =8965,	//国家资金已经最大了，无法募集

	eText_Country_Describe_Random            =8966, //随机国家说明

	eText_Country_Kill_Offical				 =8970,	//杀死官员
	eText_Country_Border_Fight				 =8971, //边境入侵 
	eText_Country_Border_Defend				 =8972, //抵御入侵 

	eText_Country_Fly_NoRight				 =8973, //只有左捕和右捕才能进行传送 
	eText_Country_Fly_Overdue				 =8974, //坐标失效 

	eText_Country_Mount_Success				 =8975,	//领取坐骑成功
	eText_Country_Mount_NotRight			 =8976,	//没有领取坐骑的权限
	eText_Country_Mount_Alreadly			 =8977,	//已经领取过坐骑
	eText_Country_Mount_NotHave				 =8978,	//没有您对应等级的坐骑
	eText_Country_Mount_MaxCount			 =8979,	//坐骑携带数量已到上限

	eText_Country_Describe_LouLan			 =8980,	//楼兰国家说明
	eText_Country_Describe_KunLun			 =8981,	//昆仑国家说明
	eText_Country_Describe_DunHuang			 =8982,	//敦煌国家说明
	eText_Country_Describe_LaiYin			 =8983,	//莱茵国家说明

	//国家任命相关 （国家公告相关）
	eText_Country_Operate_Appoint               =8984, //%s玩家功勋卓著，特被任命为%s职位，希望再接再厉，壮大我国！
	eText_Country_Operate_Dismiss               =8985, //%s官员身体不适，辞去官职，告老还乡
	eText_Country_Operate_Define1               =8986, //太师
	eText_Country_Operate_Define2               =8987, //大都督
	eText_Country_Operate_Define3               =8988, //太尉
	eText_Country_Operate_Define4               =8989, //中郎将


	eText_CountryName						 =8995,	// 新手
	eText_Country_LouLan					 =8996, // 楼兰王国
	eText_Country_KunLun					 =8997, // 昆仑王国
	eText_Country_DunHuang					 =8998, // 敦煌王国
	eText_Country_LaiYin					 =8999, // 莱茵王国



	eTextServer_ChangeCorp_AssignMode0       =9000, // 成功转换为团队！\n分配模式为:自由模式		
	eTextServer_ChangeCorp_AssignMode1       =9001, // 成功转换为团队！\n分配模式为:队伍模式		
	eTextServer_ChangeCorp_AssignMode2       =9002, // 成功转换为团队！\n分配模式为:随即模式		
	eTextServer_ChangeCorp_AssignMode3       =9003, // 成功转换为团队！\n分配模式为:分配模式		
	eText_Client_GreatGuild_NameFaild        =9004, // 创建公会名字不合法		
	eText_Server_TeamJoinSuccess             =9005, // 加入队伍成功!		
	eText_Server_TeamDisband                 =9006, // 队伍解散		
	eText_Server_TeamLeaved                  =9007, // 你已离开队伍!		
	eClient_AddInfo_2slk_148                 =9008, // 你对%s说:%s\n 		
	eClient_AddInfo_2slk_149                 =9009, // 不存在或不在线 		
	eTellClient_HighShoutCountLimit          =9010, // 您已到每天天下喊话次数		
	eServer_lessShoutChatColdtime            =9011, // 小于呐喊频道聊天冷却时间，还剩%d秒		
	eServer_lessHighShoutChatColdtime        =9012, // 小于天下频道聊天冷却时间，还剩%d秒		
	eClient_AddInfo_2slk_141                 =9013, // 小于呐喊频道聊天冷却时间，还剩%d秒		
	eClient_AddInfo_2slk_142                 =9014, // 小于天下频道聊天冷却时间，还剩%d秒 		
	eServer_chat_particular_vip2             =9015, // 小道消息2		
	eServer_chat_particular_vip3             =9016, // 小道消息3		
	eServer_chat_particular_vip4             =9017, // 小道消息4		
	eServer_chat_particular_vip5             =9018, // 小道消息5		
	eServer_chat_particular_vip6             =9019, // 小道消息6		
	eServer_chat_particular_vip7             =9020, // 小道消息7		
	eServer_chat_particular_vip8             =9021, // 小道消息8		
	eServer_chat_particular_vip9             =9022, // 小道消息9		
	eServer_chat_particular_vip10            =9023, // 小道消息10		
	eTextServer_Answer_Change_AssignMode0    =9024, // 分配模式已更改为:自由模式		
	eTextServer_Answer_Change_AssignMode1    =9025, // 分配模式已更改为:队伍模式		
	eTextServer_Answer_Change_AssignMode2    =9026, // 分配模式已更改为:随即模式		
	eTextServer_Answer_Change_AssignMode3    =9027, // 分配模式已更改为:分配模式		
	eClient_getnewtask_music_path            =9028,    //data/datasoun/1.wav		
	eEnterRaidMapTell =9029,  //准备进入[%s],请稍候...	
	eCostSilverYunDiRelive =9030,     //原地复活		
	eCostSilverWanMeiRelive =9031,     //完美复活		
	eTellClient_OnlineTime                  =9032,//已在线%d分钟,注意休息!	
	eTellClient_GetExp                       =9033,//获得%d%%的经验和%d%%的技能经验		
	eTellClient_ClearOnlineTime          =9034,//在线时间清0		
	eTellClient_OnlineTimeAndHour                  =9035,//已在线%d小时%d分钟,注意休息!	
	eClient_AddInfo_2slk_2         =9036,        //不能攻击公会成员		
	eClient_AddInfo_2slk_3         =9037,        //不能攻击队伍成员		
	eClient_AddInfo_2slk_44        =9038,        //"当前副本人数已达上限!"		
	eClient_AddInfo_2slk_46        =9039,        //"当前此副本数量已达上限"		
	eClient_AddInfo_2slk_49        =9040,        //"无法移动，请正确回答验证码图片上的文字"		
	eClient_AddInfo_2slk_50        =9041,        //"验证成功"		
	eClient_AddInfo_2slk_51        =9042,        //"几秒钟后将更换验证图片重新验证"		
	eClient_AddInfo_2slk_52        =9043,        //"开店中不可使用物品!"		
	eClient_AddInfo_2slk_53        =9044,        //"过期物品不可使用!"		
	eClient_AddInfo_2slk_54        =9045,        //"骑乘状态不可开店"		
	eClient_AddInfo_2slk_55        =9046,        //"开店状态不可攻击"		
	eClient_AddInfo_2slk_56        =9047,        //"本地图不可骑乘"		
	eClient_AddInfo_2slk_57        =9048,        //"开店状态不可骑乘"		
	eClient_AddInfo_2slk_58        =9049,        //"隐身状态中不能骑马"		
	eClient_AddInfo_2slk_59        =9050,        //"战斗中不可骑乘"		
	eClient_AddInfo_2slk_60        =9051,        //"两次骑乘间隔过短"		
	eClient_AddInfo_2slk_61        =9052,        //"背包满了!物品掉在了地上"  		
	eClient_AddInfo_2slk_114        =9053,        //目标距离太远，不能查看！		
	eClient_AddInfo_2slk_78        =9054,        //"当前状态不能移动" 		
	eClient_AddInfo_2slk_79        =9055,        //"活力增加 %d 点！当前活力为:%d"  		
	eClient_AddInfo_2slk_81        =9056,        //您的移动过快了111，请休息一下		
	eClient_AddInfo_2slk_82        =9057,        //您的移动过快了222，请休息一下		
	eClient_AddInfo_2slk_83        =9058,        //您的移动过快了333请休息一下！ %d  		
	eClient_AddInfo_2slk_110        =9059,        //没有选中目标		
	eClient_AddInfo_2slk_139        =9060,        //%s 被 %s 攻击掉血 %d		
	eClient_AddInfo_2slk_146        =9061,        //获得物品:%s\n 		
	eServer_picktime_eResultTaskItem =9062,    //"Can`t obtain question item"		
	eServer_picktime_eResultUnknow =9063,        //"You can`t obtain this item"		
	eServer_obtain_item                =9064,    //%s obtain 1 %s		
	eTellClient_IntegralMax =9065,//积分信息 积分最大值增加:%d,当前积分最大值:%d	
	eTellClient_Gm2Player_ShowName =9066,//GM发给PLAYER显示的名字		
	eTell_Client_ProtectCharDis =9067,//与护送怪物距离太远!		
	eClient_CantUseGood_ByDiffState             =9068, //当前状态不能使用物品		
	eText_ItemNoPlaceToWaring =9069, //背包已满，请注意交易物品丢落在地上。		
	eText_Copper =9070, // 铜		
	eUI_Yes                    =9071,		
	eUI_NO                    =9072,		
	eText_Chat_1                =9073,            //[交易]:		
	eTell_Client_ServerExpPer =9074,		
	eTell_Client_ServerSkillExpPer =9075,		
	eNotEnoughEmnity    =9076, // 没有足够的钱		
	eLog_OtherBagItem_In_Compound      =9077, // 背包信息 人物进入游戏世界加入合成背包物品[%s ID:%s 数量:%d]其他属性:%s		
	eLog_OtherBagItem_In_Intensify     =9078, // 背包信息 人物进入游戏世界加入强化背包物品[%s ID:%s 数量:%d]其他属性:%s		
	eLog_OtherBagItem_In_Reduce        =9079, // 背包信息 人物进入游戏世界加入分解背包物品[%s ID:%s 数量:%d]其他属性:%s		
	eLog_OtherBagItem_In_Unsoul        =9080, // 背包信息 人物进入游戏世界加入解除绑定背包物品[%s ID:%s 数量:%d]其他属性:%s		
	eLog_OtherBagItem_In_PrivateShop   =9081, // 背包信息 人物进入游戏世界加入个人商店物品[%s ID:%s 数量:%d]其他属性:%s		
	eLog_OtherBagItem_In_LockIntensify =9082, // 背包信息 人物进入游戏世界加入强化锁定背包物品[%s ID:%s 数量:%d]其他属性:%s		
	eLog_OtherBagItem_Exit_Compound =9083,      // 背包信息 人物离开游戏世界加入合成背包物品[%s ID:%s 数量: %d]其他属性:%s		
	eLog_OtherBagItem_Exit_Intensify =9084,     // 背包信息 人物离开游戏世界加入强化背包物品[%s ID:%s 数量: %d]其他属性:%s		
	eLog_OtherBagItem_Exit_Reduce =9085,        // 背包信息 人物离开游戏世界加入分解背包物品[%s ID:%s 数量: %d]其他属性:%s		
	eLog_OtherBagItem_Exit_Unsoul =9086,        // 背包信息 人物离开游戏世界加入解除绑定背包物品[%s ID:%s 数量: %d]其他属性:%s		
	eLog_OtherBagItem_Exit_PrivateShop =9087,   // 背包信息 人物离开游戏世界加入个人商店物品[%s ID:%s 数量: %d]其他属性:%s		
	eLog_OtherBagItem_Exit_LockIntensify =9088, // 背包信息 人物离开游戏世界加入强化锁定背包物品[%s ID:%s 数量: %d]其他属性:%s		
	eTextGuild_No_Master                    =9089,//对不起，你不是帮派长，没有权限修改		
	eText_Guild_Addition_Exp                =9090,//你得到帮派经验%d		
	eTextGuild_Error_Create_NullName =9091,            //你所在的公会已经被解散		
	eTextGuild_Error_Create_NameError =9092,           //创建公会名称有非法字符!		
	eTextGuild_Error_Create_NameLong =9093,            //创建公会失败!公会名太长		
	eTextGuild_Error_Create_NameHaveNull =9094,        //创建公会失败!公会名不能包含空格		
	eTextGuild_Error_Create_PlayLevelNoEnough =9095,           //创建公会失败!创建人等级不够		
	eTextGuild_Error_Create_HaveGuild =9096,           //创建公会失败!你已经加入了公会		
	eTextGuild_Error_Create_HaveName =9097,            //创建公会失败!公会名[%s]已存在		
	eTextGuild_Create_Bull =9098,                      //【%s】公会即日成立，特此昭告天下。		
	eClient_AddInfo_2slk_84        =9099,        //%s 拒绝加入公会		
	eClient_AddInfo_2slk_71        =9100,        //"账号被重新登陆，你与服务器的连接将断开"		
	eClient_OpFailReasonInBlacklist             =9101, // 操作失败,你在 %s 黑名单中	
	eClient_AddInfo_2slk_45        =9102,        //任务[%s]		
	eLog_info_2slk_19    =9103,    //怪物掉落物品 %s[%s]		
	eLog_info_2slk_21    =9104,    //任务 %s 变量[%d]变为 %d		
	eLog_info_2slk_22    =9105,    //任务 %s 变量[%d]变为 %d		
	eLog_info_2slk_54    =9106,    //退出游戏世界, ip[%s], 本次在线游戏时间[%u]分钟, 总在线时长[%u]分钟	
	eLog_info_2slk_163 =9107, //退出游戏金钱信息 当前的金钱%d 仓库金钱%d 银票%d		
	eLog_info_2slk_146    =9108,    //得到物品 捡东西[ID:%d,数量:%d]	
	eLog_info_2slk_55    =9109,    //拾取物品 物品:%s GUID:%s 数量:%d		
	eLog_info_2slk_56    =9110,    //丢弃物品 物品:%s GUID:%s 数量:%d		
	eLog_info_2slk_57    =9111,    //脚本属性变更 Index号:%d 变量值改为:%d		
	eLog_info_2slk_158    =9112,    //移动物品 背包物品位置更改:Dst Idx[%d] id[%d] cnt[%d] -> Src Idx[%d] id[%d] cnt[%d]		
	eLog_info_2slk_62    =9113,    //使用物品 自身(HP:%d MP:%d) 目标(%s ID:%d HP:%d MP:%d) 使用物品:%s 时间:%d		
	eServer_picktime_eResultItemTime =9114,    //"Item safe time %d`s"		
	eClient_AddInfo_2slk_88        =9115,        //当前地图ID:%ld 所有Character数量:%d 玩家数量:%d  		
	eClient_AddInfo_2slk_89        =9116,        //地图上未复活的怪数量:%d  		
	eClient_AddInfo_2slk_90        =9117,        //上次保存时间间隔 %d 		
	eClient_AddInfo_2slk_91         =9118,        //"伤害仇恨显示开关:%d"		
	eClient_AddInfo_2slk_92         =9119,        //服务器坐标显示开关:%d		
	eClient_AddInfo_2slk_93         =9120,        //玩家使用技能物品日志开启		
	eClient_AddInfo_2slk_94         =9121,        //玩家使用技能物品日志关闭		
	eClient_AddInfo_2slk_95         =9122,        //玩家坐标Map:%d | X:%d | Y:%d		
	eClient_AddInfo_2slk_99         =9123,        //当前没有选中怪物		
	eClient_AddInfo_2slk_100        =9124,        //查找怪物失败！当前怪物ID:%d		
	eClient_AddInfo_2slk_101        =9125,        //当前选中的不是怪物		
	eClient_AddInfo_2slk_102        =9126,        //当前怪物的AI是否开启:%d		
	eClient_AddInfo_2slk_103        =9127,        //当前怪物ID:%d，怪物当前目标ID:%d		
	eClient_AddInfo_2slk_104        =9128,        //当前怪物使用技能ID:%d，技能等级:%d		
	eClient_AddInfo_2slk_105        =9129,        //当前怪物地图ID:%d，X:%d，Y:%d		
	eClient_AddInfo_2slk_106        =9130,        //当前怪物目的地X:%d，Y:%d		
	eClient_AddInfo_2slk_107        =9131,        //当前怪物对你的仇恨:%d		
	eClient_AddInfo_2slk_108        =9132,        //当前怪物的仇恨玩家数:%d		
	eClient_AddInfo_2slk_109        =9133,        //当前怪物目标地图ID:%d，X:%d，Y:%d		
	eLog_info_2slk_60    =9134,    //技能升级 技能:%s ID:%d 升到%d级		
	eLog_info_2slk_61    =9135,    //销毁物品 物品:%s GUID:%s		
	eLog_info_2slk_63    =9136,    //商店错误 无此商店		
	eLog_info_2slk_65    =9137,    //NPC过远 当前距:%f		
	eLog_info_2slk_68    =9138,    //商店错误 商店没这么多的量		
	eLog_info_2slk_69    =9139,    //物品错误 ItemDetail找不到此物品Id:%d		
	eLog_info_2slk_70    =9140,    //购买失败 没的足够多的钱 当前钱:%d		
	eLog_info_2slk_71    =9141,    //创建物品失败 物品类型Id:%d		
	eLog_info_2slk_72    =9142,    //购买物品 物品:%s ID:%s 数量:%d 从 NPC:%s		
	eLog_info_2slk_73    =9143,    //物品错误 背包中无此物品		
	eLog_info_2slk_74    =9144,    //物品错误 背包中无此物品		
	eLog_info_2slk_75    =9145,    //物品错误 背包中物品没这么多		
	eLog_info_2slk_77    =9146,    //物品错误 物品:%s 不能卖给商店!		
	eLog_info_2slk_78    =9147,    //买卖错误 卖给商店的量大于每批次量		
	eLog_info_2slk_79    =9148,    //物品错误 不是此类物品 物品类型:%d 目标类型:%d		
	eLog_info_2slk_80    =9149,    //出售物品 物品:%s ID:%s 数量:%d 给 NPC:%s		
	eLog_info_2slk_81    =9150,    //进入游戏金钱信息 当前的金钱%d 仓库金钱%d 银票%d		
	eLog_info_2slk_82    =9151,    //学习技能 技能:%s ID:%d		
	eLog_info_2slk_83    =9152,    //遗忘技能 技能:%s ID:%d		
	eLog_info_2slk_85    =9153,    //添加仓库物品 物品:%s GUID:%s 数量:%d 位置: %d		
	eLog_info_2slk_27    =9154,    //AccountID:%d GetYuanBao GUID:%s ItemID:%d		
	eLog_info_2slk_28    =9155,    //AccountID:%d UpdateYuanBao GUID:%s ItemID:%d		
	eLog_info_2slk_147   =9156,    //使用道具纪录 UseItem将装备从背包中取出[%s ID:%d]		
	eLog_info_2slk_148   =9157,    //使用道具纪录 UseItem如果有旧的装备，则放回背包内[ID:%d,数量 %d]	
	eLog_info_2slk_149   =9158,    //使用道具纪录 UseItem将装备放回背包内(因为不能装备)[ID:%d,数量 %d]	
	eLog_info_2slk_41    =9159,    //移动超标 低 超标速度%f(%f/%d) 此时荣誉值%d 此时移动速度%f		
	eLog_info_2slk_42    =9160,    //移动超标 中 超标速度%f(%f/%d) 此时荣誉值%d 此时移动速度%f		
	eLog_info_2slk_43    =9161,    //移动超标 高 超标速度%f(%f/%d) 此时荣誉值%d 此时移动速度%f		
	eLog_info_2slk_44    =9162,    //信誉变更 信誉值为%d 将其强行踢下线		
	eLog_info_2slk_46    =9163,    //信誉变更 信誉值为%d 记录在案 将荣誉设为20000		
	eLog_info_2slk_47    =9164,    //信誉变更 信誉值为%d 记录在案 将荣誉设为20000		
	eLog_info_2slk_48    =9165,    //使用外挂 严重移动消息错误用了外挂改数据		
	eLog_info_2slk_49    =9166,    //使用外挂 严重移动消息错误用了外挂改数据		
	eLog_info_2slk_50    =9167,    //使用外挂 移动消息错误用了变速齿轮 %d 		
	eLog_info_2slk_51    =9168,    //移动错误 在路途上　路点ID%d 路点名字%s		
	eLog_info_2slk_52    =9169,    //移动错误 在路途上　路点ID%d		
	eClient_AddInfo_2slk_150        =9170,        //"梁城被攻破，城战结束！" 		
	eClient_AddInfo_2slk_134        =9171,        //【%s】公会积分为 %d		
	eClient_AddInfo_2slk_135        =9172,        //【%s】公会成为梁城新的主人		
	eClient_AddInfo_2slk_63        =9173,        //"进攻梁城的名额已满，不能报名"  		
	eClient_AddInfo_2slk_64        =9174,        //"你还没有加入公会，不能报名"  		
	eClient_AddInfo_2slk_65        =9175,        //"你不是会长或者副会长，不能报名"  		
	eClient_AddInfo_2slk_70        =9176,        //"你所在的公会已经报名成功，不能再次报名"  		
	eLog_info_2slk_29    =9177,    //升级 从:%d　到:%d　		
	eLog_info_2slk_30    =9178,    //杀怪[%s]获得经验: [%d]
	eLog_info_2slk_36    =9179,    //普通攻击 自身(HP:%d MP:%d PK值:%d 等级:%d 坐标:%d:%d:%d) 受击者(%s ID:%d HP:%d MP:%d 等级:%d 坐标:%d:%d:%d) 时间:%d		
	eLog_info_2slk_38    =9180,    //宠物攻击 自身(HP:%d MP:%d PK值:%d 等级:%d 坐标:%d:%d:%d) 宠物:%s 受击者(%s ID:%d HP:%d MP:%d 等级:%d 坐标:%d:%d:%d ) 时间:%d		
	eLog_info_2slk_39    =9181,    //GettheItemDetail().GetItemByID Failed ItemID[%d]		
	eLog_info_2slk_40    =9182,    //掉落物品 物品:%s GUID:%s 数量:%d		
	eLog_info_2slk_25    =9183,    //CharacterFormulaService::ApplyExp(pTarget->IsDead())获得%d经验值(团对)		
	eLog_info_2slk_26    =9184,    //CharacterFormulaService::ApplyExp()获得%d经验值（团对）		
	eLog_info_2slk_35    =9185,    //脚本或者其他获得经验: [%d]		
	eClient_AddInfo_2slk_137        =9186,        //%s加入队伍		
	eClient_AddInfo_2slk_138        =9187,        //%s离开队伍		
	eLog_info_2slk_23    =9188,    //加入队伍 队伍中成员		
	eLog_info_2slk_24    =9189,    //加入队伍 队伍中成员		
	eText_NoGuild        =9190,//无公会		
	eLog_info_2slk_7    =9191,    //Learn Skill failed:%d		
	eLog_info_2slk_8    =9192,    //Learn Skill success:%d		
	eClient_AddInfo_2slk_72        =9193,        //"此副本将被销毁,你将被传送出去"	
	eClient_AddInfo_2slk_73        =9194,        //"此团队副本已不属于你,你将被传送出去"	
	eClient_AddInfo_2slk_74        =9195,        //"此多团队副本已不属于你,你将被传送出去"	
	eTell_Client_KillAndAddPkValue =9196,//你杀死了%s,获得%d点荣誉!	
	eLog_info_2slk_137    =9197,    //杀死玩家 目标玩家:%s:%d 当前PK值:%d 等级:%d 对方等级:%d 坐标[%d:%d:%d]目标坐标[%d:%d:%d] 时间:%d		
	eLog_info_2slk_138    =9198,    //杀死玩家 目标玩家:%s:%d 但是最后一次攻击时间间隔太长 时间:%d 最后攻击时间:%d		
	eLog_info_2slk_139    =9199,    //杀死玩家 目标玩家:%s:%d 但是没有找到攻击记录 时间:%d		
	eLog_info_2slk_140    =9200,    //脚本删除 物品:%s 数量:%d		
	eLog_info_2slk_141    =9201,    //脚本获得 %d个物品:%s ID:%s		
	eLog_info_2slk_142    =9202,    //脚本获得 %d个物品:%s 但背包满了!物品掉在了地上		
	eLog_info_2slk_143    =9203,    //拾取包裹获得 %d个物品:%s 但背包满了!		
	eLog_info_2slk_144    =9204,    //%d个物品:%s 失败		
	eLog_info_2slk_126    =9205,    //使用技能 HP:%d MP:%d 对 %s(%d HP:%d MP:%d) 使用技能:%s 时间:%d		
	eLog_info_2slk_127    =9206,    //使用技能 HP:%d MP:%d 使用技能:%s 时间:%d		
	eLog_info_2slk_128    =9207,    //冲值错误 服务器拒绝 冲值价值为负的东西ItemName:%s 冲值失败		
	eLog_info_2slk_129    =9208,    //冲值成功 给物品:%s ID:%s 的物品冲值成功 物品过期时间为: %d/%d/%d %d:%d		
	eLog_info_2slk_130    =9209,    //冲值失败 给物品:%s ID:%s 的物品冲值		
	eLog_info_2slk_14    =9210,    //得到物品 物品:%s GUID:%s 数量:%d		
	eLog_info_2slk_156    =9211,    //领取元宝 ID:%d 数量:%d		
	eLog_info_2slk_0    =9212,    //第%ld的if语句没有匹配完整.\n		
	eLog_info_2slk_1    =9213,    //第%ld的else语句没有匹配完整.\n		
	eLog_info_2slk_2    =9214,    //第%ld的endif语句没有匹配完整.\n		
	eLog_info_2slk_3    =9215,    //第%ld的proc_start语句非法嵌入.\n		
	eLog_info_2slk_4    =9216,    //第%ld的proc_end语句非法嵌入.\n		
	eLog_info_2slk_5    =9217,    //第%ld行的if语句匹配不完整.\n		
	eLog_info_2slk_6    =9218,    //第%ld行下标越界.\n		
	eLog_info_2slk_131    =9219,    //金锭操作 起始数量: %u		
	eLog_info_2slk_132    =9220,    //金锭操作 增加数量: %u, 当前数量: %u		
	eLog_info_2slk_133    =9221,    //金锭操作 减少数量: %u		
	eLog_info_2slk_134    =9222,    //金锭操作 目前银票数量: %u		
	eLog_info_2slk_135    =9223,    //删除物品 物品:%s 数量:%d		
	eLog_info_2slk_136    =9224,    //商城购买 物品:%s GUID:%s 数量:%d 从商城购买		
	eClient_AddInfo_2slk_136        =9225,        //在线玩家总数=%ld	
	eLog_info_2slk_150    =9226,    //装备纪录 OnEquipToWhere将装备从背包中取出[%s ID:%d]		
	eLog_info_2slk_151    =9227,    //装备纪录 OnEquipToWhere如果有旧的装备，则放回背包内[ID:%d,数量 %d]	
	eLog_info_2slk_152    =9228,    //装备纪录 OnEquip将装备从背包中取出[%s ID:%d]		
	eLog_info_2slk_153    =9229,    //装备纪录 OnEquip如果有旧的装备，则放回背包内[ID:%d,数量 %d]	
	eLog_info_2slk_154    =9230,    //装备纪录 UnEquip[ID:%d,数量 %d]	
	eLog_info_2slk_98     =9231,    //物品过期 物品:%s ID:%s 数量:%d 过期日期:%d/%d/%d %d:%d:%d		
	eLog_info_2slk_102    =9232,    //冲值 给物品:%s ID:%s 的物品冲值 物品过期时间:%d/%d/%d %d:%d		
	eLog_info_2slk_103    =9233,    //冲值 给物品:%s ID:%s 的物品冲值 物品过期时间:%d/%d/%d %d:%d		
	eLog_info_2slk_104    =9234,    //冲值 给物品:%s ID:%s 的物品冲值 物品过期时间:%d/%d/%d %d:%d		
	eLog_info_2slk_105    =9235,    //[%s:%d]失去金钱 失去金钱%d 当前金钱%d		
	eLog_info_2slk_106    =9236,    //[%s:%d]得到金钱 得到金钱%d 当前金钱%d		
	eLog_info_2slk_107    =9237,    //进入游戏背包信息 \t%s ID[%d] GUID[%s] Count[%d] Pos[%d] Other[%s]		
	eLog_info_2slk_108    =9238,    //背包信息 发给DB消息中背包中的物品 \t%s ID[%d] GUID[%s] Count[%d] Other[%s]	
	eLog_info_2slk_109    =9239,    //移动物品 GUID:%s ID:%d 数量:%d 从背包到强化石头		
	eLog_info_2slk_110    =9240,    //移动物品 GUID:%s ID:%d 数量:%d 从强化石头到背包		
	eLog_info_2slk_111    =9241,    //移动物品 GUID:%s ID:%d 数量:%d 从背包到强化装备		
	eLog_info_2slk_112    =9242,    //移动物品 GUID:%s ID:%d 数量:%d 从强化石头到背包		
	eLog_info_2slk_113    =9243,    //移动物品 GUID:%s ID:%d 数量:%d 从背包到强化材料Luck		
	eLog_info_2slk_114    =9244,    //移动物品 GUID:%s ID:%d 数量:%d 从强化材料Luck到背包		
	eLog_info_2slk_115    =9245,    //移动物品 GUID:%s ID:%d 数量:%d 从分解背包移动到装备		
	eLog_info_2slk_116    =9246,    //移动物品 GUID:%s ID:%d 数量:%d 从装备移动到分解背包		
	eLog_info_2slk_117    =9247,    //移动物品 GUID:%s ID:%d 数量:%d 从分解成品移动到背包		
	eLog_info_2slk_118    =9248,    //分解物品 ID:%d GUID:%s		
	eLog_info_2slk_119    =9249,    //分解获得物品 ID:%d GUID:%s		
	eLog_info_2slk_120    =9250,    //解除绑定物品 ID:%d GUID:%s		
	eLog_info_2slk_121    =9251,    //移动物品 GUID:%s ID:%d 数量:%d 从背包移动到解绑		
	eLog_info_2slk_122    =9252,    //移动物品 GUID:%s ID:%d 数量:%d 从背包移动到解绑		
	eLog_info_2slk_123    =9253,    //移动物品 GUID:%s ID:%d 数量:%d 从背包移动到锁强化		
	eLog_info_2slk_124    =9254,    //移动物品 GUID:%s ID:%d 数量:%d 从锁强化移动到背包		
	eLog_info_2slk_125    =9255,    //锁定强化 ID:%d GUID:%s 当前强化等级:%d		
	eLog_info_2slk_155    =9256,    //合成添加物品[ID:%d,数量:%d]	
	eLog_info_2slk_165    =9257,    //退出游戏装备栏信息 游戏世界装备栏物品:%s ID:%s 数量:%d		
	eLog_info_2slk_166    =9258,    //进入游戏装备栏信息 游戏世界装备栏物品:%s ID:%s 数量:%d		
	eLog_info_2slk_9      =9259,    //交易物品 开始 %s与%s		
	eLog_info_2slk_11     =9260,    //失去物品 物品:%s GUID:%s 数量:%d 		
	eLog_info_2slk_12     =9261,    //失去物品 物品:%s GUID:%s 数量:%d 		
	eLog_info_2slk_13     =9262,    //得到物品 物品:%s GUID:%s 数量:%d 背包放不下将掉到地上		
	eLog_info_2slk_15     =9263,    //得到物品 物品:%s GUID:%s 数量:%d 背包放不下将掉到地上		
	eLog_info_2slk_16     =9264,    //得到物品 物品:%s GUID:%s 数量:%d		
	eLog_info_2slk_17     =9265,    //交易物品 完成 %s与%s		
	eLog_info_2slk_86     =9266,    //移动物品 GUID:%s ID:%d 数量:%d 从背包移动到个人商店		
	eLog_info_2slk_87     =9267,    //移动物品 GUID:%s ID:%d 数量:%d 从个人商店移动到个人商店		
	eLog_info_2slk_88     =9268,    //移动物品 GUID:%s ID:%d 数量:%d 从个人商店移动到背包		
	eLog_info_2slk_89     =9269,    //移动物品 物品:%s GUID:%s 数量:%d 从背包移动至仓库		
	eLog_info_2slk_90     =9270,    //移动物品 物品:%s GUID:%s 数量:%d 从仓库移动至背包		
	eLog_info_2slk_91     =9271,    //清除状态 物品:%s		
	eLog_info_2slk_92     =9272,    //购买物品 玩家:%s ID:%ld 个人商店物品:%s GUID:%s 数量:%d		
	eLog_info_2slk_93     =9273,    //出售物品 玩家:%s ID:%ld 个人商店物品:%s GUID:%s 数量:%d		
	eLog_info_2slk_94     =9274,    //移动物品 物品GUID:%s 类型ID:%d 数量:%d 从合成成品移动到背包		
	eLog_info_2slk_95     =9275,    //移动物品 物品GUID:%s 类型ID:%d 数量:%d 从合成材料移动到背包		
	eLog_info_2slk_96     =9276,    //移动物品 物品GUID:%s 类型ID:%d 数量:%d 从背包移动到合成材料		
	eLog_info_2slk_97     =9277,    //合成物品 类型ID:%d GUID:%s		
	eLog_info_2slk_159    =9278,    //移动物品 仓库->仓库: %d %d -> %d %d		
	eLog_info_2slk_160    =9279,    //移动物品 物品GUID:%s 类型ID:%d 数量:%d 从合成材料移动到背包		
	eLog_info_2slk_161    =9280,    //添加物品 向包裹添加物品[GUID:%s,ID:%d,数量 %d]
	eLog_IntensifySucc_Info1 =9281,//强化物品 成功 武器名字:%s GUID:%s 强化前等级:%d 强化后等级:%d 使用的空离:%s 使用的符咒:%s		
	eLog_IntensifySucc_Info2 =9282,//强化物品 成功 武器名字:%s GUID:%s 强化前等级:%d 强化后等级:%d 使用的空离:%s 		
	eLog_IntensifyFail_Info1 =9283,//强化物品 失败 武器名字:%s GUID:%s 强化前等级:%d 强化后等级:%d 使用的空离:%s 使用的符咒:%s		
	eLog_IntensifyFail_Info2 =9284,//强化物品 失败 武器名字:%s GUID:%s 强化前等级:%d 强化后等级:%d 使用的空离:%s 		
	eTextGuild_Error_NotMember =9285,              //目标不是公会成员		
	eTextGuild_Success_Create =9286,               //创建公会成功		
	eTextGuild_Error_Disband_CityMaster =9287,     //梁城占有者不能解散公会		
	eTextGuild_Error_Disband_NotMaster =9288,      //你不是会长，不能解散公会		
	eTell_Client_KillAndSubPkValue =9289,//你杀死了%s,减少%d点荣誉!	
	eClient_Frddlg_CantBlackIsStudent           =9290, // %s 是你徒弟无法加入黑名单		
	eClient_Frddlg_CantToBlackBecauseIsMarrage  =9291, // %s 是你伴侣无法加入黑名单		
	eLog_info_2slk_20    =9292,    //杀死怪物 %s[%d]		
	eClient_AddInfo_2slk_111        =9293,        //您不属于任何公会，不能邀请别人加入.		
	eClient_AddInfo_2slk_112        =9294,        //您邀请的玩家不存在或者不在线.		
	eLog_OnEquip_PushError                =9295, //OnEquip_PushError则放回背包内[ID:%d,数量 %d]    	
	eLog_AddIntegral                      =9296, //积分增加 积分增加:%d点,当前积分为:%d,积分最大值:%d
	eTell_Client_AddPkValuePerTime        =9297, //增加%d点荣誉值		
	eLog_CreateID2_Debug                  =9298, //CreateID调试 创建CreateID2[%s]		
	eClient_AddInfo_2slk_113        =9299,        //当前地图轮循时间 %d ms		
	eLog_info_2slk_164 =9300, //退出游戏背包信息 游戏世界背包物品 \t%s ID[%d] GUID[%s] Count[%d] Pos[%d %s]
	eClient_Error_Me_InFightCanNotAddFriend     =9301, // 战斗状态不能加好友		
	eClient_Error_Target_InFightCanNotAddFriend =9302, // 对方在战斗状态不能加好友		
	eServer_AddPersonMarriage        =9303,        //%s和你结为夫妇		
	eServer_AddPersonBrother            =9304,        //%s和你结为兄弟		
	eServer_AddPersonTeacher        =9305,        //%s收你为徒		
	eServer_AddPersonStudent            =9306,        //%s拜你为师傅    		
	eLog_info_2slk_145    =9307,    //"元宝换银票[ID:%d 数量:%d]"		
	eTextGuild_Error_Disband_NoGuild =9308,            //你还没有加入公会		
	eMessageBox_GuildMasterOffline        =9309, // [%s]公会会长不在线		
	eMessageBox_LeagueErrorNotGuildMaster =9310, // 你不是会长不能做联盟操作		
	eTellClient_AgreeLeague               =9311, //%s 公会接受你的公会联盟！		
	eTellClient_RefuseLeague              =9312, //%s 公会拒绝你的联盟申请！		
	eClinet_people_join_team        =9313,    //%s 加入队伍		
	eLog_info_2slk_31    =9314,    //获得技能经验 技能名:%s 经验:%s		
	eLog_info_2slk_32    =9315,    //技能经验 技能名:%s 经验:%s		
	eLog_ExitWorldPkValue                =9316,  //人物离开游戏世界荣誉值%d		
	eLog_Exit_shenqi              =9317,//人物离开游戏世界神气值%d		
	eMessageBox_InviterIsOffline          =9318, // 你邀请的人不在线 		
	eTellClient_RefuseAddFriend               =9319, // %s 拒绝你加好友请求！		
	eTellClient_PKValueDailyMax           =9320, //今日获得荣誉值已到最大!		
	eLog_EnterWord_zhenying              =9321,//人物进入游戏世界阵营贡献值%d		
	eLog_EnterWord_lingqian              =9322,//人物进入游戏世界灵潜值%d		
	eLog_EnterWord_taozhu1              =9323,//人物进入游戏世界陶朱2949贡献值%d		
	eLog_Exit_taozhu2              =9324,//人物离开游戏世界陶朱2950贡献值%d		
	eLog_Exit_zhenying              =9325,//人物离开游戏世界阵营贡献值%d		
	eLog_Exit_lingqian              =9326,//人物离开游戏世界灵潜值%d		
	eTellClient_RelationNeutralism        =9327, //%s 公会和 %s 公会中立 		
	eTellClient_RelationLeague            =9328, //%s 公会和 %s 公会联盟		
	eTellClient_RelationAdverse           =9329, //%s 公会和 %s 公会敌对		
	eLog_EnterWord_taozhu2              =9330,//人物进入游戏世界陶朱2950贡献值%d		
	eLog_EnterWord_shenqi              =9331,//人物进入游戏世界神气值%d		
	eLog_EnterWorldPkValue                =9332, //人物进入游戏世界荣誉值%d		
	eLog_Exit_taozhu1              =9333,//人物离开游戏世界灵陶朱2949献值%d		
	eTextGuild_Error_Disband_Battle =9334,         //已经报名参加城战的公会不能被解散		
	eTextGuild_Error_Invite_Battle =9335,          //正在参加城战的公会不能招收新成员		
	eTextGuild_Error_Invite_TargetHaveGuild =9336, //对方已经加入一个公会		
	eTextGuild_Error_Invite_MemberNumMax =9337,    //公会人数已经达到上限%d人		
	eTextGuild_Error_Invite_NotMaster =9338,       //你不是会长，不能邀请成员		
	eTextGuild_Error_Ban_Battle =9339,             //对方正在参加城战，暂时不能被开除		
	eTextGuild_Error_Ban_NotMaster =9340,          //你不是会长，不能开除成员		
	eTextGuild_Error_Leave_Battle =9341,           //参加城战时不能退会		
	eTextGuild_Error_Leave_Master =9342,           //会长不能直接退出行会		
	eTextGuild_Error_Join_MemberMax =9343,         //对方公会人数已满		
	eTextGuild_Join =9344,                         //你加入了【%s】公会		
	eTextGuild_Join_Member =9345,                  //%s 加入了公会		
	eTextGuild_Ban_Member =9346,                   //%s 被请离了公会		
	eTextGuild_Leave_Member =9347,                 //%s 离开了公会		
	eTextGuild_GetExp                       =9348,//你所在的公会获得%d经验值		
	eTell_Client_CannotTaskBCLevel        =9349, //您的等级不够,不能接这个任务!	
	eTell_Client_CannotTaskBCMoney =9350,//您的钱不够,不能接这个任务!	
	eTell_Client_CannotTaskBCFrontQuest =9351, // 您没有完成前置任务		
	eTell_Client_CannotTaskBCItem = 9352,//您没有指定的任务道具,不能接这个任务!
	eTell_Client_CannotTaskBCEnergy = 9353,//您的活力不够,不能接这个任务!
	eTell_Client_CannotTaskBCReputation = 9354,//您的声望不够,不能接这个任务!
	eTell_Client_CannotTaskBCSex = 9355,//您的性别不适合接这个任务!
	eTell_Client_CannotTaskBCProfession = 9356,//您的兵种不适合接这个任务!
	eServer_AddVendetta             =    9357,            //你被%s杀死
	eTextGuild_Disband = 9358,                      //你所在的公会已经被解散
	eTellClient_ShopCenterOff = 9359,//商城信息 今日商城折扣%%n!
	eGetYuanBao                     = 9360, //获取网站塞入物品
	eGetYuanBaoFaild                = 9361, //获取元宝失败（无物品可以获得）
	eTell_Client_CostAndRemain = 9362, //花费%d货币，余额%d货币 **这里开始17173用
	eUpdateYuanBaoSucc              = 9363, //提交元宝成功
	eUpdateYuanBaoFaild             = 9364, //提交元宝失败
	eUI_ShopCenterBuyno_stock_item        = 9365,
	eUI_ShopCenterBuySucess                = 9366,
	eText_TwoHandEqiupError_0            =    9367,
	eText_TwoHandEqiupError_2            =    9368,
	eClient_Error_Me_InFightCanNotBargain     = 9369, // 战斗状态不能交易
	eClient_Error_Target_InFightCanNotBargain = 9370, // 对方在战斗状态不能交易
	eClient_AddInfo_2slk_87        = 9371,        //目标距离太远，不能交易！  
	eSystemInfo_ResetTime_CantBuy        = 9372,    //过期商品不能购买
	eSystemInfo_ResetTime_CantCompound    = 9373,//过期物品不能用于合成
	eSystemInfo_ResetTime_CantInlay        = 9374, //过期物品不能强化
	eClient_AddInfo_2slk_117         = 9375,        //过期物品不能分解
	eTellClient_NotSilver            = 9376,      //没有足够的银票!
	eClient_AddInfo_2slk_75        = 9377,        //"对方金钱将会超过 %d 上限"
	eClient_AddInfo_2slk_76        = 9378,        //自己金钱将会超过 %d 上限
	eTextGuild_Error_TargetIsSelf = 9379,           //不能对自己执行这个操作
	ePack_NotGrid                   = 9380,                //没有空间!
	eTellClient_RefuseEmbrace       = 9381, // %s 拒绝与你拥抱！
	eTellClient_AgreeStopAdverse    = 9382, //%s 公会接受你的握手言和！		
	eTellClient_RefuseStopAdverse   = 9383, //%s 公会拒绝你的握手言和申请！

	eTellClient_NotEnoughReputation = 9384, // 购买失败 没的足够多的声望 当前声望:%d
	eTellClient_NotEnoughExploit    = 9385, // 购买失败 没的足够多的荣誉 当前荣誉:%d
	eTellAllClient_EquipLevelUpToMax = 9386,// "恭喜玩家 %s 经过不懈努力成功将装备[%s]升至九星"
	eTellClient_LessMapMinLevel      = 9387, // 你的等级小于%d级，无法进入该地图
	eTellClient_NotEnoughItem        = 9388, // 购买失败 没的足够多的%s 当前数量:%d
	eTellClient_FlyOnlyTeamHeader    = 9389,  // 队长未进入副本，无法传送
	eTellClient_TeamMemberMustArlound = 9390,   // 只有所有队员在附近才能进入
	eTellClient_TeamMemberMustGreaterMapLevel = 9391,   // 所有队员都需要%d级才能进入此副本
	eTellClient_ActiveMountCanNotTrade       = 9292,    // 出战的马不能交易
	eLog_info_2slk_170                      = 9393,  // 移动物品 GUID:%s ID:%d 数量:%d 从马的背包移动到个人商店	
	eTellClient_TeamMemberMustHaveQuest = 9394,       // %s没有接此任务,不能进入此副本
	eChatFormat                         = 9395,
	eTellClient_PunishLeaveTime         = 9396,       // 红名惩罚时间还剩%d秒
	eTellClient_AlreadyEnterOnce		= 9397,      // 已经进入过一次 
	eTellClient_RollCount               = 9398,      //%s掷出了%d
	eClient_AddInfo_2slk_120            = 9399,      // 副本重置中,请稍后再进
	eClient_TellPlayerInMyBlacklist     = 9400,      // %s在你黑名单中,无法进行此操作
	eClient_FlyMapGreaterThanMax        = 9401,      // 传送失败,%s已经进入该地图超过%d次!
	eClient_WaitLeaveStage              = 9402,      // %d秒后,你将被传送出此地图!

	eLog_JingPiao_1                  = 9403,  // 金票操作 起始数量: %u
	eLog_JingPiao_2                  = 9404,  // 金票操作 增加数量: %u, 当前数量: %u
	eLog_JingPiao_3                  = 9405,  // 金票操作 减少数量: %u, 当前数量: %u
	eLog_JingPiao_4                  = 9406,  // 金票操作 设置数量: %u, 当前数量: %u
	eLog_PickItemPack                = 9407,  // 获得物品 : [%s] ID : [%d] GUID : [%I64u] 数量 : [%d]
	eLog_Info_ExpPercent             = 9408,  //"经验系数 队伍系数 : [%0.2f] 防沉迷 : [%0.2f] 全服系数:[%0.2f] 状态系数:[%0.2f] 个人系数:[%0.2f]"
	eLog_JinDing_FromDb              = 9409,  // 金锭兑换
	eLog_DropPackage                 = 9410,  // 由[%d]方式掉落包裹在 地图 : [%u], 坐标( %0.2f, %0.2f )
	eLog_PickPackage                 = 9411,  // 请求拾取由[%d]方式掉落的包裹
	eTellClient_NotEnoughGuildOffer  = 9412,  // 购买失败 没的足够多的帮贡 当前帮贡:%d
	eText_OpenTreasureBox            = 9414,  // 玩家 %s 打开 %s 获得 %s 物品 %d 个
	eTellClient_ReleaseGameStage     = 9415,  // [%s]地图将在[%d]分钟后关闭, 在此地图的玩家请离开该地图或者做好下线准备
	eTell_NotEnoughGuildMoney        = 9416,  // 购买失败 没的足够多的帮会资金 当前帮会资金:%d  
	eTell_NotEnoughGuildBuild        = 9417,  // 购买失败 没的足够多的帮会建设度 当前帮会建设度:%d
	eTell_NotEnoughMoBeiReputation   = 9418,  // 购买失败 没的足够多的漠北地区声望 当前漠北地区声望:%d
	eTell_NotEnoughLiaoDongReputation = 9419, // 购买失败 没的足够多的辽东地区声望 当前辽东地区声望:%d
	eTell_NotEnoughDunHuangReputation = 9420, // 购买失败 没的足够多的敦煌地区声望 当前敦煌地区声望:%d
	eTell_NotEnoughGaoGouLiReputation = 9421, // 购买失败 没的足够多的高句丽地区声望 当前高句丽地区声望:%d
	eTell_OnlyGuildMaster            = 9422,  // 只有帮主才有购买此物品的权限
	eTell_NotEnoughMasterValue       = 9423,  // 购买失败 没的足够多的师门威望, 当前师门威望值:%d
	eTellClient_Marriage             = 9424,   // %s与%s喜结良缘
	eTellClient_LuckReward           = 9425,   // 经过艰苦卓绝的战斗，~%s_所在的队伍终于通过“月光宝盒”第%d关的考验，恭喜他们获得丰厚奖励！
	eTellClient_EquipLevelUpTo10     = 9426,   // %s凭借着非一般的毅力，成功地将装备[%s]升至%s星。在其光辉的照耀下，全服所有玩家都获得了高额的经验奖励
	eTellClient_NotEnoughHonour      = 9427,   // 购买失败 没的足够多的荣誉 当前荣誉:%d
	eTellAllClient_GetItemToMaxLev   = 9428,   //"恭喜玩家 %s 经过不懈努力成功获得紫色品质[%s]"
	eTellAllClient_GetMaxLevItemByJD   = 9429,   //"玩家%s人品爆发，鉴定出一个[%s]"

	// 人物进入退出游戏世界背包、装备等物品信息表头
	eLog_EnterWorld_Normal_Bag_Begin            = 9431,  // [:T9431]\t=========人物进入游戏世界普通背包信息Begin=========
	eLog_EnterWorld_Normal_Bag_End              = 9432,  // [:T9432]\t=========人物进入游戏世界普通背包信息End===========
	eLog_EnterWorld_Material_Bag_Begin          = 9433,  // [:T9433]\t=========人物进入游戏世界材料背包信息Begin=========
	eLog_EnterWorld_Material_Bag_End            = 9434,  // [:T9434]\t=========人物进入游戏世界材料背包信息End===========
	eLog_EnterWorld_DB_Begin                    = 9435,  // [:T9435]\t=========发给DB消息中背包物品信息Begin=========
	eLog_EnterWorld_DB_End                      = 9436,  // [:T9436]\t=========发给DB消息中背包物品信息End===========
	eLog_ExitWorld_Normal_Bag_Begin             = 9437,  // [:T9437]\t=========人物退出游戏世界普通背包信息Begin===========
	eLog_ExitWorld_Normal_Bag_End               = 9438,  // [:T9438]\t=========人物退出游戏世界普通背包信息End=============
	eLog_ExitWorld_Material_Bag_Begin           = 9439,  // [:T9439]\t=========人物退出游戏世界材料背包信息Begin===========
	eLog_ExitWorld_Material_Bag_End             = 9440,  // [:T9440]\t=========人物退出游戏世界材料背包信息End=============
	eLog_EnterWorld_EquipInfo_Begin             = 9441,  // [:T9441]\t=========进入游戏装备栏信息Begin===============
	eLog_EnterWorld_EquipInfo_End               = 9442,  // [:T9442]\t=========进入游戏装备栏信息End=================
	eLog_ExitWorld_EquipInfo_Begin              = 9443,  // [:T9443]\t=========退出游戏装备栏信息Begin=============
	eLog_ExitWorld_EquipInfo_End                = 9444,  // [:T9444]\t=========退出游戏装备栏信息End===============

	eLog_Exploit_1                   = 9445,  // [%s:%d]功勋操作 起始数量: %u
	eLog_Exploit_2                   = 9446,  // [%s:%d]功勋操作 增加数量: %u, 当前数量: %u
	eLog_Exploit_3                   = 9447,  // [%s:%d]功勋操作 减少数量: %u, 当前数量: %u
	eLog_Exploit_4                   = 9448,  // [%s:%d]功勋操作 设置数量: %u, 当前数量: %u
	eLog_Reputation_1                = 9449,  // [%s:%d]声望操作 起始数量: %u
	eLog_Reputation_2                = 9450,  // [%s:%d]声望操作 增加数量: %u, 当前数量: %u
	eLog_Reputation_3                = 9451,  // [%s:%d]声望操作 减少数量: %u, 当前数量: %u
	eLog_Reputation_4                = 9452,  // [%s:%d]声望操作 设置数量: %u, 当前数量: %u
	eLog_Honour_1                    = 9453,  // [%s:%d]荣誉操作 起始数量: %u
	eLog_Honour_2                    = 9454,  // [%s:%d]荣誉操作 增加数量: %u, 当前数量: %u
	eLog_Honour_3                    = 9455,  // [%s:%d]荣誉操作 减少数量: %u, 当前数量: %u
	eLog_Honour_4                    = 9456,  // [%s:%d]荣誉操作 设置数量: %u, 当前数量: %u
	eLog_CountryScore_1              = 9457,  // [%s:%d]国战积分操作 起始数量: %u
	eLog_CountryScore_2              = 9458,  // [%s:%d]国战积分操作 增加数量: %u, 当前数量: %u
	eLog_CountryScore_3              = 9459,  // [%s:%d]国战积分操作 减少数量: %u, 当前数量: %u
	eLog_CountryScore_4              = 9460,  // [%s:%d]国战积分操作 设置数量: %u, 当前数量: %u
	eLog_Exp_1                       = 9461,  // [%s:%d]经验操作 增加数量: %I64u
	eLog_Exp_2                       = 9462,  // [%s:%d]经验操作 减少数量: %I64u
	eLog_Exp_3                       = 9463,  // [%s:%d]经验操作 设置数量: %I64u
	eLog_JiaoZi_1                    = 9464,  // [%s:%d]交子操作 起始数量: %u
	eLog_JiaoZi_2                    = 9465,  // [%s:%d]交子操作 增加数量: %u, 当前数量: %u
	eLog_JiaoZi_3                    = 9466,  // [%s:%d]交子操作 减少数量: %u, 当前数量: %u
	eLog_JiaoZi_4                    = 9467,  // [%s:%d]交子操作 设置数量: %u, 当前数量: %u
	eLog_Money_1                     = 9468,  // [%s:%d]金钱操作 起始数量: %u
	eLog_Money_2                     = 9469,  // [%s:%d]金钱操作 增加数量: %u, 当前数量: %u
	eLog_Money_3                     = 9470,  // [%s:%d]金钱操作 减少数量: %u, 当前数量: %u
	eLog_Money_4                     = 9471,  // [%s:%d]金钱操作 设置数量: %u, 当前数量: %u

	eLog_DoneQuest_RewardExp         = 9700,  // 完成%d任务，获得 %d 经验
	eLog_FirstEnterWord              = 9701,  // 进入游戏世界 [IP:%s][MAC:%s]
	eLog_DoneQuest_RewardMoney       = 9702,  // 完成%d任务，获得 %d 金钱
	eLog_CreateGuildLog              = 9703,  // 创建了 %s 公会
	eLog_LeaveGuildLog               = 9704,  // 离开了 %s 公会,当前公会总人数 %d 个
	eLog_GuildBanLog                 = 9705,  // 踢出%s玩家出%s公会,当前公会总人数 %d 个
	eLog_TransferGuildMaster         = 9706,  // 转让会长给 %s 玩家
	eLog_TransferGuildViceMaster     = 9707,  // 转让副会长给 %s 玩家
	eLog_TransferGuildTongMaster     = 9708,  // 转让堂主给 %s 玩家
	eLog_AwardViceMaster             = 9709,  // 授予玩家 %s 为 %s 公会的副会长
	eLog_RemoveViceMaster            = 9710,  // 撤销玩家 %s 在 %s 公会的副会长职位
	eLog_AwardTongMaster             = 9711,  // 授予玩家 %s 为 %s 公会的 %d 堂主职位
	eLog_RemoveTongMaster            = 9712,  // 撤销玩家 %s 为 %s 公会的 %d 堂主职位
	eLog_ExitTong                    = 9713,  // 退出了 %s 公会的 %d 堂
	eLog_InviteEnterGuild            = 9714,  // 被 %d 邀请进入 [%d] [%s] 公会
	eLog_DisMissGuild                = 9715,  // 解散 %s 公会
	eLog_GuildUpLevel                = 9716,  // [%d] [%s] 公会从 %d 升级到 %d
	eLog_AddGuildOffer               = 9717,  // 增加在 %s 公会 %d 的帮贡
	eLog_SubGuildOffer               = 9718,  // 减少在 %s 公会 %d 的帮贡
	eLog_AddGuildMoney               = 9719,  // 增加在 %s 公会 %d 的资金
	eLog_SubGuildMoney               = 9720,  // 减少在 %s 公会 %d 的资金
	eLog_LeagueGuild                 = 9721,  // %s 公会和 %s 公会联盟
	eLog_AdverseGuild                = 9722,  // %s 公会和 %s 公会敌对
	eLog_Disadverse                  = 9723,  // %s 公会和 %s 公会中立
	eLog_AddTong                     = 9724,  // 邀请 %s 玩家加入 %s 公会 %d 堂
	eLog_RemoveTong                  = 9725,  // %s 玩家被移除 %s 公会 %d 堂
	eLog_DoneQuest_RewardItem        = 9726,  // 完成%d任务，获得 %s 道具
	eLog_DoneQuest_RewardTitle       = 9727,  // 完成%d任务，获得 %s 称号
	eLog_DoneQuest_RewardReputation  = 9728,  // 完成%d任务，获得 %d 荣誉
	eLog_DoneQuest_RewardExploit     = 9729,  // 完成%d任务，获得 %d 功勋
	eLog_DoneQuest_RewardGuildContribute = 9730, // 完成%d任务，获得 %d 帮贡
	eLog_DoneQuest_RewardAddtionExp  = 9731,  // 完成%d任务，获得 %d 额外经验
	eLog_Buffer_AddExp               = 9732,  // 通过 %s Buff，获得 %d 经验
	eLog_MoneyItemChange             = 9733,  // :T0005 兑换 %I64u %s %d %s %s %s %s
	eLog_MoneyItemChangeReq          = 9734,  // :T0006 向平台提交兑换 %I64u %s %d %s %s %s %s
	eLog_CancelStatus                = 9735,  // 取消状态 %s
	eLog_OpenTreasureBox             = 9736,  //开启[%s]宝箱，[ID:%u,GUID:%I64u]，获得宝箱中的宝物[%s][%d]个
	eLog_TeamLuckReward              = 9737,   //%s的队伍在月光宝盒副本第[%d]关%s
	eLog_CharLuckReward              = 9738,   //%s在月光宝盒副本第[%d]关%s
	eLog_UseItemToFriend             = 9739,   // 对好友[%s]使用物品[%s][%d]个, 添加好友度[%u]
	eLog_KickByCheckCheat            = 9740,   // 检测代码返回结果[%0x], 判定使用外挂, 被T下线   
	eLog_Lost_JiaoZi                 = 9741,    //失去交子 失去交子%d 当前交子%d		
	eLog_Get_JiaoZi                  = 9742,    //得到交子 得到交子%d 当前交子%d
	eLog_DoneQuest_RewardJiaoZi      = 9743,    // 完成%d任务，获得 %d 交子
	eLog_DoneQuest_RewardHonor       = 9744,    // 完成%d任务，获得 %d 荣誉
	eText_CountryReward				 = 9745,	// 国王奖励的文本

	eText_ReqRmbPoint				 = 10000, // 正在请求rmb点数
	eText_ExchangeNeedPoint			 = 10001, // 此次兑换需要花费您%d
	eText_RemainRmbPoint			 = 10002, // 您目前的帐户上还拥有%d点
	eText_ExchangeRmbPoint			 = 10003, // 正在处理中...
	eText_NotEnoughJinDing			 = 10004, // 没有足够的金锭
	eText_NotEnoughJinPiao			 = 10005, // 没有足够的金票
	eText_NotItemShopCenter			 = 10006, // 该物品已售完
	eText_ExchangeJinDingLevelLow    = 10007, // 等级%d以上才能兑换金锭
	eText_GetJinDing				 = 10008, // 你得到了%d金锭
	eText_LoseJinDing				 = 10009, // 你失去了%d金锭
	eText_GetJinPiao				 = 10010, // 你得到了%d金票
	eText_LoseJinPiao				 = 10011, // 你失去了%d金票
	eText_ChangePoint                = 10012, //"兑换率:1点=%d金锭"
	eText_OwnGold                    = 10013, //"目前游戏中还拥有 %d 金锭"
	eText_UnderLevel15               = 10014, // 15级一下不可以使用商城
	eText_LoseShopConsumeScore		 = 10015, // 你失去了%d积分
	eText_NotEnoughShopConsumeScore	 = 10016, // 没有足够的商城积分
	eText_AddShopConsumeScore		 = 10017, // 你得到了%d积分

	eText_TradeOriginPrice           = 10019,//原价:%d
	eText_TradeFinalPrice            = 10020,//优惠:%d
	eText_TradePrice                 = 10021,//""

	eText_UpdateShopCenter 		    = 10022, // 商城更新提示
	eText_ShopCenterFindPath        = 10023, //购买成功可至%s处兑换道具，是否现在寻路前往
	eText_ShopCenterTypeAll         = 10024, //全部
	eText_RegisterNoFriend          = 10025, //指定的玩家必须是你的好友
	eText_RegisterError             = 10026, //系统错误
	eText_RegisterErrorOp           = 10027, //错误的操作
	eText_RegisterNoBuyMySelf       = 10028, //不能买卖自己的单子
	eText_RegisterNoCancelOther     = 10029, //不能撤销其他玩家的单子
	eText_RegisterWaiting           = 10030, //等待处理中

	eText_AuctionItemState_Status_Init	= 10031, // 初始状态
	eText_AuctionItemState_Running	= 10032, // 委托中
	eText_AuctionItemState_Terminate= 10033, // 已终止
	eText_AuctionItemState_TimeOut	= 10034, // 已到期

	eText_SystemAuction_Status_Running	   = 10035,    //挂单中
	eText_SystemAuctionError_Status_BuySuccess   = 10036,    //购买成功
	eText_SystemAuctionError_Status_SellSuccess   = 10037,    //出售成功
	eText_SystemAuctionError_Status_Buyed	   = 10038,    //已经购买
	eText_SystemAuctionError_Status_Selled  = 10039,    //已售出
	eText_SystemAuctionError_SystemBusy   = 10040,    //系统繁忙，请稍后尝试
	eText_SystemAuctionError_TooMoney = 10041,    //金钱数量超限
	eText_SystemAuctionError_NoItem = 10042,    //购买失败，请刷新列表后重新查看
	eText_SystemAuctionError_BuyType   = 10043,    //错误购买类型
	eText_SystemAuctionError_NoAccount   = 10044,    //账户资金不足，操作失败
	eText_SystemAuctionError_CannotBuySelfItem   = 10045,    //无法购买自己的单据，请刷新列表后选择其他单据进行购买
	eText_GoldTrade_BuyConfirm      = 10046,    //将以%s的价格购买%d金锭，是否确定？
	eText_GoldTrade_SellConfirm     = 10047,    //将以%s的价格出售%d金锭，是否确定？
	eText_GoldTrade_TooLess         = 10048,    //单次委托最少交易额度为15金锭
	eText_TellWorldMoneyAuction		= 10049,//金锭寄售通知全服

	eText_UnderLevel15RankList		= 10050, // 15级以下不可使用排行榜
	eText_LoginNeedPwdProtect		= 10051, // 您的帐号已绑定密保卡，请使用密保卡登陆
	eText_LoginNoPwdProtect			= 10052, // 您的帐号未绑定密保卡，请取消密保卡登陆
	eText_PasswordProtectString		= 10053, // 请输入第%c行，第%c列的数字:
	eText_LoginPwdProtectFailed		= 10054, // 密保卡输入错误
	eText_LoginPwdProtectTimeOut	= 10055, // 验证超时，请您重新登陆

	eText_GoldTrade_Cancel          = 10056,//是否需要取消该寄售单据?
	eText_GoldTrade_Sell            = 10057,//出售
	eText_GoldTrade_Buy             = 10058,//收购
	eText_GoldTrade_BuyConfirmleft  = 10059,//是否要用%s的价格收购%d金锭？
	eText_GoldTrade_SellConfirmleft = 10060,//是否要用%s的价格出售%d金锭？


	eText_NoXinShouCard				= 10061, // 未查询到您的新手卡使用记录
	eText_No17173Card				= 10062, // 未查询到您的17173特权卡使用记录
	eText_NoZhiZunCard				= 10063, // 未查询到您的至尊卡等级
	eText_NoZhiZunVipGift			= 10064, // 未查询到您的至尊Vip卡使用记录
	eText_NoHuiGuiGift				= 10065, // 未查询到您的老玩家回归礼包可领取记录
	eText_NoChongZhiGift			= 10066, // 未查询到您的冲值返还礼包可领取记录
	eText_NoChongZhiBackJinDing		= 10067, // 未查询到您的多充多送礼包可领取记录

	eText_GotXinShouCard			= 10068, // 已领取过新手卡，无法再次领取
	eText_Got17173Card				= 10069, // 已领取过17173特权卡，无法再次领取
	eText_ZhiZunCardLevel			= 10070, // 您的至尊卡等级为%s卡
	eText_GotZhiZunVipGift			= 10071, // 已领取过至尊Vip卡，无法再次领取
	eText_GotHuiGuiGift				= 10072, // 已领取过老玩家回归礼包，无法再次领取
	eText_GotChongZhiGift			= 10073, // 已领取过冲值返还礼包，无法再次领取
	eText_GotChongZhiBackJinDing	= 10074, // 已领取过多充多送礼包，无法再次领取

	eText_GetCardGiftSuccess		= 10075, // 领取成功
	eText_GetCardGiftFailed			= 10076, // 领取失败

	eText_GetZhiZunCard				= 10077, // 武神至尊卡		（1级）
	eText_GetZhiZunYinCard			= 10078, // 武神至尊银卡	（2级）
	eText_GetZhiZunJinCard			= 10079, // 武神至尊金卡	（3级）
	eText_GetZhiZunBaiJinCard		= 10080, // 武神至尊白金卡	（4级）
	eText_GetZhiZunZuanShiCard		= 10081, // 武神至尊钻石卡	（5级）
	eText_GetZhiZunHuangGuanCard	= 10082, // 武神至尊皇冠卡	（6级）

	eText_RegisterBuyString         = 10092, //单价由低至高，指定给我的，金锭由少至多，金锭由多至少，指定金锭数量
	eText_RegisterSellString        = 10093, //单价由高至低，指定给我的，金锭由少至多，金锭由多至少，指定金锭数量

	eText_ER_HaveNotXinShouCard = 10100,
	eText_ER_XinShouCardCreateFail1 = 10101,
	eText_ER_XinShouCardCreateFail2 = 10102,
	eText_ER_XinShouCardPushFail1 = 10103,
	eText_ER_NotNeiCeJinPiao = 10104,
	eText_ER_NotNeiCeJinDing = 10105,

	eText_ER_HaveNotXinShouItem		= 10106,          // 没有新手道具
	eText_ER_XinShouItemCreateFail1 = 10107,
	eText_ER_XinShouItemCreateFail2 = 10108,
	eText_ER_XinShouItemPushFail1	= 10109,

	eText_OnlineAward				= 10150,	//您将会在%d分%d秒后获得第%d份神秘礼物
	eText_OnlineAward2				= 10151,	//恭喜，您获得的第%d份礼物是%s，请打开背包查看……
	eText_OnlineAwardAlreadyGet		= 10152,	//您已领取过该奖励，无法重新领取
	eText_OnineAwardNoReward		= 10153,	//领取奖励出错，请更新客户端
	eText_OnlineAwardPretime		= 10154,	//您将在%s以后获得以上奖励

	eText_ChangeNameNoItem          = 10170,    //未找到改名道具，改名失败
	eText_ChangeNameSuccess         = 10171,    //改名成功

	eText_FriendLevel1				= 10181,	//萍水相逢
	eText_FriendLevel2				= 10182,	//高情厚谊
	eText_FriendLevel3				= 10183,	//情同手足
	eText_FriendLevel4				= 10184,	//莫逆于心
	eText_FriendLevel5				= 10185,	//生死不渝

	eText_Vendetta					= 10189,	//血海深仇
	eText_TempFriend				= 10190,	//素不相识
	eText_BlackList1				= 10191,	//陌生人


	eText_FightInfoHurt            = 10201,   //"%s对%s使用%s,造成%d%s伤害"
	eText_NearDistance             = 10202,   //近程
	eText_FarDistance              = 10203,   //远程
	eText_Critical                 = 10204,   //暴击
	eText_BackHit                  = 10205,   //背袭 + %d
	eText_NormalAttack             = 10206,   //普通攻击
	eText_MagicAttack              = 10207,   //%d级%s
	eText_Your                     = 10208,   //你
	eText_Relive                   = 10209,   //"%s对%s使用了复活术"
	eText_Miss                     = 10210,   //%s躲闪了%s的攻击
	eText_NoHit                    = 10212,   //%s的攻击未命中%s"
	eText_SkillBuf                 = 10213,   //你使用了%s,获得了%s状态"
	eText_UseSkillBuf              = 10214,   //%s对%s使用%s,%s获得了%s状态
	eText_RestoreHpBySelf          = 10215,   //你使用了%s,恢复生命%d点
	eText_RestoreHp                = 10216,   //%s对%s使用了%s,%s恢复生命%d点
	eText_AddHp                    = 10217,   //%s因%d级%s状态恢复了%d点生命
	eText_ReduceHp                 = 10218,   //%s因%d级%s状态减少了%d点
	eText_FightGetExp              = 10219,   //你获得了%d经验
	eText_UseSkill                 = 10220,   //%s对%s使用了%s
	eText_MySelfSkill              = 10221,   //你使用了%s
	eText_AddSkillExp              = 10222,   //你获得了%u点技能经验
	eText_AddHpBySkill             = 10223,   //%s受到吸血效果恢复了%d点生命
	eText_ReduceHpBySkill          = 10224,   //%s受到反伤效果减少了%d点生命
	eText_LoseSkillExp			   = 10225,	  //你失去了%u点技能经验
	eText_RestoreMpBySelf			= 10226,	  //你使用了%s,恢复魔法%d点
	eText_RestoreMp					= 10227,	  //%s受到%d级%s状态恢复了%d点魔法

	eText_ReduceMP                 = 10228,   //%s因%d级%s状态减少了%d点

	eText_ItemLocked               = 10251,   //已加锁
	eText_ItemUnLocked             = 10252,   //%s 解锁
	eText_ItemLockedContext        = 10253,   //物品加锁后将无法进行交易、摆摊及摧毁，是否继续？
	eText_MountLockedContext       = 10254,   //坐骑加锁后将无法进行交易、摆摊及摧毁，是否继续？
	eText_ItemUnLockedContext      = 10255,   //开启解锁后3天，将会自动解锁，是否继续？

	eText_ItemLockSale             = 10256,   //物品已锁，无法卖出
	eText_ItemLockExchange         = 10257,   //物品已锁，无法交易
	eText_ItemLockDestory          = 10258,   //物品已锁，无法销毁
	eText_MountLockExchange        = 10259,   //坐骑已锁，无法交易
	eText_MountLockedSetFree       = 10260,   //坐骑已锁，无法放生


	eText_ItemHasLocked            = 10261,   //物品已加锁
	eText_MountHasLocked           = 10262,   //坐骑已加锁
	eText_ItemHasNotLocked         = 10263,   //物品未加锁
	eText_MountHasNotLocked        = 10264,   //坐骑未加锁
	eText_ItemCannotLock           = 10265,   //物品无法加锁
	eText_IsLocked				   = 10267,	  //物品已加锁，无法进行此操作

	eText_ItemCannotUnlock         = 10268,   //物品正处于解锁状态，无法再次解锁
	eText_MountCannotUnlock        = 10269,   //坐骑正处于解锁状态，无法再次解锁

	eText_ItemLockShop             = 10270,   //物品已加锁，无法摆摊
	eText_MountLockShop            = 10271,   //坐骑已加锁，无法摆摊
	eText_PetLockShop = 10272, //宠物已加锁，无法摆摊
	eText_PetInBattle = 10273, //宠物已出战，无法摆摊

	eText_SecondPasswordSetSucceed = 10280,   //二级密码设置成功
	eText_SecondPasswordChangeSucceed  = 10281,//二级密码更改成功
	eText_SecondPasswordWrong      = 10282,    //二级密码错误
	eText_SecondPasswordDiffer     = 10283,    //二级密码不一致
	eText_SecondPasswordStyleError = 10284,	   //二级密码格式错误
	eText_SecondPasswordSizeError  = 10285,    //二级密码长度错误
	eText_SecondPasswordRelieve    = 10286,    //二级密码解除
	//	eText_SecondPasswordRemainTime = 10287,    //二级密码剩余时间
	eText_SecondPasswordUndo       = 10287,    //强制解锁已开启
	eText_SecondPasswordcancel     = 10288,    //仓库密码输入成功，强制解除自动取消
	eText_SecondPasswordUndoTime   = 10289,    //仓库密码将在%s后强制解除
	eText_SecondPasswordIsUndo     = 10290,    //仓库密码正处于强制解锁状态
	eText_SecondPasswordUndoInfo   = 10291,    //仓库密码强制解除提示
	eText_AlreadyHaveSecendPsw     = 10292,    //已经有二级密码了

	eText_MailItemNoSender         = 10401,    //此物品无法邮寄
	eText_MailTitleError           = 10402,    //标题填写有误，请重新填写
	eText_MailSenderError          = 10403,    //送信人填写有误
	eText_MailContentError         = 10404,    //正文填写有误，请重新填写
	eText_MailMoneyNoEnough        = 10405,    //金钱不足
	eText_MailItemError            = 10406,    //物品有误
	eText_MailHasItem              = 10407,    //请先取出物品后再进行转发
	eText_MailHasMoney             = 10408,    //请先取出金钱后再进行转发
	eText_MailTranslate            = 10409,    //转发:
	eText_MailResponce             = 10410,    //回复:
	eText_MailSendNeedMoney        = 10411,    //邮资:
	eText_MailNewNotify            = 10412,    //%s给你发了封邮件，请前去飞鸽传书处查看
	eText_MailItemNotify           = 10413,    //该邮件尚有附件未取出，是否删除？
	eText_MailSendSuccess          = 10414,    //发送成功
	eText_MailSendFriend           = 10415,    //发信人或抄送人必须为好友
	eText_MailTargetName           = 10416,    //目标名字无效
	eText_MailTarget               = 10417,    //目标不存在
	eText_MailTooMuchMoney         = 10418,    //邮寄金钱超过上限
	eText_MailAccessoryError       = 10419,    //附件无效，请重新打开邮件查看            
	eText_MailProcsssing           = 10420,    //邮件正在处理中
	eText_MailTitleWrong           = 10421,    //Title不合法
	eText_MailContentWrong         = 10422,    //Content不合法
	eText_MailSize                 = 10423,    //邮件个数到达上限
	eText_MailNoExist              = 10424,    //该邮件不存在
	eText_MailDelFailed            = 10425,    //该邮件无法删除
	eText_MailFindFailed           = 10426,    //邮件目标查询失败
	eText_MailHasGetItem           = 10427,    //邮件物品已经获得，请重新打开邮件查看
	eText_MailReceivedError        = 10428,    //收信人填写有误，请重新选择
	eText_MailReceivedTip          = 10429,    //发件人:
	eText_MailTitleTip             = 10430,    //主题:
	eText_MailLifeTip              = 10431,    //剩余:
	eText_MailTargetQueryFail	   = 10432,	   //收件人目前无法获得新邮件



	eText_TeacherLevel				= 10601, //师门等级:%d
	eText_LiLian					= 10602, //我的历练:%u
	eText_WeiWang					= 10603, //我的威望:%s
	eText_NoStudent					= 10604, //尚未收徒，可以收10级以上的玩家做徒弟
	eText_NoTeacher					= 10605, //尚未拜师，可以拜40级以上的玩家为师傅
	eText_StudentLevelLimit			= 10606, //徒弟等级必须大于%d级
	eText_TeacherLevelLimit			= 10607, //师父等级必须大于%d级
	eText_TeacherStudentLevelBeyond = 10608, //师徒等级差必须在%d级以上
	eText_TeacherStudentCannotBeCouple	= 10609, //夫妻之间无法建立师徒关系
	eText_CannotAddTeacher			= 10610, //已经出师，无法再次拜师
	eText_CanHaveOneTeacher			= 10611, //只能拜一个师傅
	eText_BeyondStudentMax			= 10612, //只能收%d个徒弟
	eText_CannotReceivePrentice		= 10613, //尚未出师，无法创建师门
	eText_InviteYouAsStudent		= 10614, //%s想要收你为徒\n是否愿意？
	eText_InviteYouAsTeacher		= 10615, //%s想要拜你为师\n是否愿意？
	eText_CannotKickTeacherTimeLimit	= 10616, //拜师后的三天内无法解除师徒关系
	eText_CannotKickStudentTimeLimit	= 10617, //收徒后的三天内无法与该徒弟师徒关系
	eText_YouGetWeiWang				= 10618, //你增加了%d点威望值
	eText_YouLoseWeiWang			= 10619, //你失去了%d点威望值
	eText_WeiWangBeyondMaxCannotUpgrade	= 10620, //威望值到达上限，无法进行提升
	eText_YouGetLiLian				= 10621, //你增加了%d点历练值
	eText_ReportToTeacherSucceed	= 10622, //汇报成功
	eText_GetReportFromStudent		= 10623, //你接受了徒弟%s的汇报，获得了%u点威望值
	eText_DirectSucceed				= 10624, //指点成功
	eText_GetDirectFromTeacher		= 10625, //你接受了师傅的指点，获得了%u点经验值
	eText_AddTeacherStudentMaxDist	= 10626, //双方距离过远
	eText_ConfirmKickStudent		= 10627, //是否要将%s逐出师门？\n逐出成功后需要扣除%d金
	eText_ConfirmLeaveTeacher		= 10628, //是否要叛离师门？\n叛离成功后需要扣除%d金
	eText_LeaveTeacherStudent		= 10630, //~%s_与你解除了师徒关系
	eText_KickTeacherStudent		= 10631, //你与~%s_解除了师徒关系
	eText_TeacherNotOnline			= 10633, //师傅不在线
	eText_StudentNotOnline			= 10634, //徒弟不在线
	eText_BeyondDirectMax			= 10635, //每天只能指点一次
	eText_CannotReport_NoLiLian		= 10636, //没有历练值不能进行汇报
	eText_InviteTeacherSucceed		= 10637, //幸运的被%s看中，成功拜入其门下
	eText_InviteStudentSucceed		= 10638, //成功的将根骨奇佳的%s收为弟子
	eText_TeacherOnline				= 10639, //你的师傅 ~%s_ 上线了
	eText_StudentOnline				= 10640, //你的徒弟 ~%s_ 上线了
	eText_TeacherOffline			= 10641, //你的师傅 ~%s_ 下线了
	eText_StudentOffline			= 10642, //你的徒弟 ~%s_ 下线了
	eText_CannotBeTeacher			= 10643, //还没有师门不能招收徒弟
	eText_OtherCannotBeTeacher		= 10644, //对方还没有师门不能招收徒弟
	eText_BeyondTeacherLevel		= 10645, //师门等级到达上限
	eText_OtherBeyondStudentMax		= 10646, //对方的徒弟数量已经达到最大值
	eText_NotFinishTeacherTask		= 10647, //尚未完成出师任务
	eText_OtherHasTeacher			= 10648, //对方已经有师傅了
	eText_NotEnoughWeiWang			= 10649, //你的威望值不够

	eText_CanUseWithWifeHusband		= 10650, //只有夫妻才能使用此道具
	eText_CannotUseOtherOffline		= 10651, //对方不在线，道具使用失败

	eGameSettingList_Sell          = 51, // 买卖设置
	eText_NotEnoughMoneyLeaveTeacher= 10652, //删除师徒关系需要%d金钱
	eText_AddTeacherStudentMaxDist1	= 10653, //拜师收徒必须在%d米范围内
	eText_BeyondStudentLevelMax		= 10654, //徒弟等级不能超过%d级
	eText_TeacherMustInTeam			= 10655, //师傅必须在队伍中才能出师
	eText_MasterLevelChange			= 10656, //师门等级变更为:%d级
	eText_FinishGraduateTask		= 10657, //出师成功
	eText_YouLoseLiLian				= 10658, //你失去了%u历练值
	eText_GraduateDistLimit			= 10659, //师傅必须在%d米范围内才能出师
	eText_InviteTeacher				= 10660, //申请向~%s_拜师
	eText_InviteStudent				= 10661, //申请向~%s_收徒
	eText_CanInviteStudent			= 10662, //恭喜你成功拥有了自己的师门
	eText_StudentGraduate			= 10663, //你的徒弟~%s_出师成功
	eText_NeedCreateShiMen			= 10664, //尚未创建师门，请去太原&lt;何师仁&gt;处创建师门
	eText_DelFriendFailed_NotExist = 10665, //不存在这个关系
	eText_DelFriendFailed_CannotDelete	= 10666, //不能删除这个关系
	eText_TeacherMustInArea			= 10667, //你的师父必须在10米范围之内
	eText_StudentMustInArea			= 10668, //你的徒弟必须在10米范围之内
	eText_AddStudentNumLimit		= 10669, //一天只能收三个徒弟
	eText_AddTeacherNumLimit		= 10670, //一天只能拜师一次
	eText_TargetAddStudentLimit		= 10671, //对方今日收徒数量到达上限
	eText_TargetAddTeacherLimit		= 10672, //对方今日已拜过师
	eText_RefuseMarry				= 10673, //~%s_ 拒绝了您的求婚
	eText_RefuseAddTeacher			= 10674, //~%s_ 拒绝收您为徒
	eText_RefuseAddStudent			= 10675, //~%s_ 拒绝拜您为师
	eText_ReportDesc				= 10676, //当你对师父进行历练汇报时，需确定师父在你身边
	eText_TeachDesc					= 10677, //当你对徒弟进行经验指点时，需确定徒弟在你身边
	eText_TeacherAndStudentLevelDiff	= 10678,//师徒的等级差别
	eText_MustBeSameCountry = 10679,//必须同一国家才能添加此关系
	eText_IsAlreadyYourTeacher = 10680,//已经是你师父
	eText_IsAlreadyYourStudent = 10681,//对方已近是你徒弟，不能进行此操作

	eText_GivePresentFailed_ShouldBeFriend	= 10800, //必须是好友，才能赠送礼物
	eText_GivePresentFailed_TooFar			= 10801, //距离过远，赠送失败
	eText_GivePresentFailed_TimeLimit		= 10803, //每天只能给每个好友赠送%d次礼物
	eText_GivePresentFailed_CountLimit		= 10804, //今天已经赠送过%d次礼物了
	eText_GivePresentFailed_ItemCannotGive	= 10805, //此物品无法赠送
	eText_GivePresent_ShowBull				= 10806, //%s收到了%s赠送的%d个%s，%s对%s好感大增
	eText_ReceiveFriendlyQuestMustHaveTeam	= 10807, //必须组队才能接取此任务
	eText_ReceiveFriendlyQuestOnlyTwoMember	= 10808, //队伍中只能有2个人才能接取此任务
	eText_ReceiveFriendlyQuestMustFriend	= 10809, //队伍中的成员必须是好友才能接取此任务
	eText_ReceiveFriendlyCountLimit			= 10810, //同一个好友一天只能接一次亲密度任务
	eText_ApplyMessageSending  = 10811,
	eText_CountryChange        = 10812, //您已经加入了%s国

	eText_Biaoche_NeedMountOff	= 10813,		//镖车前，请下坐骑
	eText_Biaoche_NoJump		= 10814,		//跳跃时不能骑到镖车上
	eText_Biaoche_OutOfRange	= 10815,		//离镖车太远了，无法上镖车护送!
	eText_Biaoche_NoMove		= 10816,		//移动中不能骑到镖车上

	eText_ItemDecompose_Cant		= 10817,	//此物品无法分解
	eText_TaskNotDone				= 10818,	//你的任务未完成
	eText_ClickCreatePlayer			= 10819,	//点击创建角色
	eText_QiDian				    = 10820,	//寻路的开头 通过%s 到 %s
	eText_YiDongLuJing				= 10821,	//移动路径
	eText_LuJing1					= 10822,    //通过%s，进入%s
	eText_FindNpc					= 10823,    //找到%s
	eText_More						= 10824,    //......(更多路径的表示方式)
	//add by liaojie
	eTip_sAddHPDamage				= 10825,	// 附加伤害
	eTip_sAddHPRestore				= 10826,	// 附加治疗
	eTip_sAddAOE					= 10827,	// 攻击人数
	eTip_sAddSuckDamage				= 10828,	// 吸收伤害
	e_ChangeNpcName 				= 10829,	// 兑换NPC名字
	eText_SkillNeedLevel			= 10830,	// {#%x=需要等级:#}
	eText_SkillNotGain				= 10831,	// 未领悟
	eText_SkillAlreadyGain			= 10832,	// 已领悟
	eText_SkillLearn__LevelLess		= 10833,	// 人物等级不够，学习该心法需要%d级

	/////////////等级封印的一些在这里///////////////////////////
	eText_WaitLimitInfo             = 10834,    //正在获取等级封印信息,请稍候...
	eText_NoActiveLimit             = 10835,    //等级封印:%d级(未激活) 
	eText_ActiveLimit               = 10836,    //等级封印:%d级(由%s激活)\n解封时间:%s
	eText_DoneLimit                 = 10837,    //等级封印结束
	eText_BaseAttrInEquip			= 10838,	//基础属性:
	eText_RandAttrInEquip			= 10839,	//随机属性:
	eText_GuildApplyCooldownTip		= 10840,	//军团申请冷却中,请%d秒后再试
	eText_StallFailed_InDueling     = 10841,    //决斗时不能摆摊
	eText_ExchangeFailed_InDueling  = 10842,    //决斗时不能交易
	eText_GetingCharacter           = 10843,    //正在获取角色信息...
	eText_NoChoseProtectStar		= 10844,	//没选择保星石提示
	eText_NoProtectStarMaterial		= 10845,	//“您没有对应装备当前星等的保星石，无法进行升星保护，请取消“使用保护材料”选项”
	eText_StarMaterialNoEnough		= 10846,	//升星材料不够之前的选择数量提示
	eText_StarLEvolveNoMomeny		= 10847,	//升星钱币不足提示
	eText_Mood						= 10848,	// 心情(个人签名)
	eText_Title						= 10849,	// 称号
	eText_CantCallFuJianWhenMoing   = 10850,	// 移动时不能召唤副将
	eText_ZhuJiangUpBound			= 10851,	//提示：“将绑定物品与不绑定物品合成，合成出的将为绑定物品，是否继续？”
	eText_ZhuJiangUp_Success		= 10852,	//主将升级成功
	eText_ZhuJiangUp_Failed			= 10853,	//主将升级失败
	eText_StarProtect_Text			= 10854,	//“星保护”
	eText_MaterialStar_UnderSix		= 10855,	//6星以下的装备升星，无法使用升星保护功能
	eText_MaterialStar_BeyondSix	= 10856,	//6星以上的升星，建议使用保星材料，升星失败退回保护星
	eText_ZhuJiangMaterial_NoEnough = 10857,	//主将转身所需材料不足，转身主将失败
	eTextMoney_Gold						= 10858,    //%d金
	eTextMoney_Silver					= 10859,    //%d银
	eTextMoney_Copper					= 10860,    //%d铜
	eTextMoney_StringSilver				= 10861,    //%s%d银
	eTextMoney_StringCopper				= 10862,    //%s%d铜
	eText_TransferStar_WrongPart		= 10863,	//部件不同的武器以及装备不可以转化星级
	eText_TransferStar_WrongLevel		= 10864,	//原装备等级必须小于等于目标装备并且等级相差不能超越10级
	eText_TransferStar_WrongStarLevel	= 10865,	//目标装备的强化等级大于原装备无法进行转星
	eText_TransferStar_SourceStarLevel  = 10866,	//原装备星级必须大于0
	eText_TransferStarAck_FailDrop		= 10867,	//降%d星，源装备%d星，目标装备%d星
	eText_TransferStarAck_Success		= 10868,	//转星成功
	eText_TransferStarAck_Fail			= 10869,	//转星失败，星级不变
	eText_InputHaveForbiddenWord        = 10870,	//您输入的文字中含有违禁字
	eText_SelfQuitGuildTip              = 10871,	//你离开了军团
	eText_MountStrengthen_UnderFour		= 10872,	//4级以下坐骑，无法使用保护功能
	eText_MountStrengthen_BeyongFour	= 10873,	//4级以上坐骑，建议使用保护功能，强化失败退回保护等级
	eText_MountStrengthen_Success		= 10874,	//坐骑强化成功
	eText_MountStrengthen_Fail			= 10875,	//坐骑强化失败
	eText_MountStrengthen_MaxLevel		= 10876,	//当前坐骑已是最高等级，不能用于强化
	eText_MountStrengthen_ActivedMount  = 10877,	//出战坐骑不能强化
	eText_BeDamagePerHPMax              = 10878,    //每次受到伤害损失最大生命值的%%d
	eText_Gem_Failed					= 10879,	//宝石镶嵌失败
	eText_YabiaoState_UseSkill			= 10880,	//押镖状态下不能使用技能
	eText_YabiaoState_UseItem			= 10881,	//押镖状态下不能使用物品
	eText_Hole_OtherItem				= 10882,	//非装备物品，无法打孔
	eText_EnterGame_Error				= 10883,	//进入游戏失败，请重新登录
	eText_Bind_Money					= 10884,	//(绑银)
	eText_BianShen_Bound				= 10885,    //变身后图鉴绑定，是否继续？
	eText_AskPresent_LengthError		= 10886,	//激活码长度错误
	eText_StarLevelUp_NoSelect			= 10887,	//您的装备已达6星，建议勾选"使用保护材料"，使用保护材料
	eText_TransferStar_MaterialDrop		= 10888,	//转星后，失败降1~3星
	eText_TransferStar_MaterialUnDrop	= 10889,	//转星后，失败不降星
	eText_Gem_ErrorItem					= 10890,	//该物品无法镶嵌宝石
	eText_GemRemove_ErrorItem			= 10891,	//该物品无法进行宝石拆除操作
	eText_GemRemove_NoGem				= 10892,	//该装备未进行宝石镶嵌，无法进行宝石拆除操作
	eText_MountStrengthen_NoSelect		= 10893,	//您的坐骑已经达到4星，建议勾选“使用保护材料”，并放入“初级净化符”
	eText_MountStrengthen_NoProtect		= 10894,	//您的保护材料不足，继续强化，失败后降级无保护
	eText_ZhuJianUp_Material			= 10895,	//%s，提升%d成功率
	eText_HIGHSHOUT_VIP_NoCountry		= 10896,	//天下喊话时没国家显示的内容
	eText_YouGet_MOUNT					= 10897,    //你成功注册了%d个坐骑:%s
	eText_FRIEND_ONLINE					= 10898,    //在线
	eText_FRIEND_OFFLINE				= 10899,    //下线
	eText_FRIEND_BIRTHDAY				= 10900,    //%2d月%2d日
	eText_GemUp_MaxLevel				= 10901,	//当前宝石已是最高等级，不能进行合成
	eText_Title_ChangeSuccess			= 10902,	//修改个性签名成功
	eText_REGEDIT_PET                   = 10903,    // 成功注册副将图鉴:%s
	eText_REPEATEDLY_PET                = 10904,    // 副将图鉴:%s已注册,无法重复注册
	eText_QUESTEND		                = 10905,    // 关闭
	eText_NoActivity					= 10906,    // 无活动奖励或者已经领取过了,请至官网确认
	eText_SNError						= 10907,    // 输出入的序列号错误,无此序列号对应的礼包奖励
	eText_AccountError					= 10908,    // 该帐号已经领取过此类型的礼包,无法再领取
	eText_CharacterError				= 10909,    // 该角色已经领取过此类型的礼包,无法再领取
	eText_Unkown						= 10910,    // 未知错误
	eText_PlatformCaption				= 10911,    // 错误
	eText_Equip_Cannot_Sell				= 10912,	// 无法出售
	eText_ActivitySucc					= 10913,    // 领取活动奖励成功,请注意查看邮件
	eText_PresentSucc					= 10914,    // 序列号兑换成功,请注意查看邮件
	eText_SuitAffect					= 10915,	// 全身%d件+%d:
	eText_MountStrengthen_ErrorMount	= 10916,	// 该坐骑无法强化
	eText_EquipScore					= 10917,	// 装备评分:
	eText_BlockAccount					= 10918,	// 您的帐号已被锁定,将在%d分钟后解锁,如有疑问请联系客服人员!
	eTellClient_MountLevelUpTo10		= 10919,	// %s凭借着非一般的毅力，成功地将坐骑[%s]强化至%s级。
	eText_MailState_Read				= 10920,	// 已读
	eText_MailState_UnRead				= 10921,	// 未读
	eText_CardIcon_Level				= 10922,	// 星
	eText_CardIcon_Get					= 10923,	// 已收集
	eText_CardIcon_UnGet				= 10924,	// 未收集
	eText_CardIcon_GetNum				= 10925,	// 进度:
	eText_CardIcon_Lack					= 10926,	// 缺少:
	eText_CardIcon_HadGet				= 10927,	// 已领取
	eText_SevenDays_UnStart				= 10928,	// 未开启
	eText_SevenDays_CanGain				= 10929,	// 可接取
	eText_SevenDays_UnderWay			= 10930,	// 进行中
	eText_SevenDays_DoneUnGet			= 10931,	// 完成，未领奖
	eText_SevenDays_DoneGet				= 10932,	// 已完成
	eText_SevenDays_GetTask_Sucess		= 10933,	// 领取任务成功
	eText_SevenDays_GetTask_Fail		= 10934,	// 领取任务失败
	eText_AddItem_Type1					= 10935,	// %s %s通过%s，获得[%s]
	eText_AddItem_Type2					= 10936,	// %s %s通过NPC%s，获得[%s]
	eText_AddItem_Type3					= 10937,	// %s %s通过击杀怪物%s，获得[%s]
	eText_SelectChannel_TimeOut			= 10938,	// 选择时间到
	eText_Login_ErrorServer				= 10939,	// 服务器正在维护，请从新选择服务器
	eText_eChangeChannelRet_Error		= 10940,	// 选择的分线错误
	eText_eChangeChannelRet_Same		= 10941,	// 与当前分线相同
	eText_eChangeChannelRet_Dead		= 10942,	// 死亡时不能选择
	eText_eChangeChannelRet_Fight		= 10943,	// 战斗状态不能选择
	eText_Decompose_HasGem				= 10944,	// 该装备镶嵌了宝石，是否分解？
	eText_Decompose_HasStarLevel		= 10945,	// 该装备强化过，是否分解？
	eText_Ping_FPS						= 10946,	// 帧数:
	eText_Server_Unknow					= 10947,	// 未知
	eText_Server_Ping					= 10948,	// %d毫秒
	eText_Server_UnderOne				= 10949,	// < 1毫秒
	eText_AddInfo_BagTypeErr			= 10950,	// 不同类型的物品不能一起
	eText_CharAttr_LossExp				= 10951,	// 你失去%d点经验
	eText_Advancement_Fail				= 10952,	// 升官失败
	eText_Advancement_Succeed			= 10953,	// 升官成功
	eText_StarMaterialBound				= 10954,	// 材料绑定，升星后装备绑定，是否继续？
	eText_EquipOwner					= 10955,	// 锻造者：
	eText_YaBiao_Flytomap				= 10956,	// 押镖状态下不能传送

	eText_GuildBattle_NoBoss			= 10957,	// 未刷新
	eText_TransferStar_Bound			= 10958,	// 转星之后源装备与目标装备都绑定，是否继续？
	eText_Hunting_UnAccept				= 10959,	// 未接受
	eText_Hunting_Accept				= 10960,	// 已接受
	eText_Hunting_CannotRefresh			= 10961,	// 没有未接任务，无法刷新
	eText_Hunting_NoJinPiao				= 10962,	// 没有足够晶钻
	eText_QueryDiscardMount				= 10963,	// 确定要放生 %s 吗？
	eText_ReliveOrigin_NoItem			= 10964,	// 复活丹数量不够
	eText_Cannot_Soul_LevelError		= 10965,	// 该等级装备不能铸魂
	eText_PrivateShopOpen				= 10966,	// 摆摊状态下不能进行此操作

	////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////
	eText_JoinFightRemainTime		= 20006,	//本次报名剩余%s秒
	eText_JoinFightCountDown		= 20007,	//本次擂台即将于%s后开始

	eText_CampBattleOne             = 20100,  //隋军
	eText_CampBattleTwo             = 20101,  //唐军
	eText_CampBattleGetSuccess      = 20102,  //%s获得胜利
	eText_CampBattlePingJu          = 20103,  //双方平局
	eText_CampBattleRequestSuccess  = 20104,  //战场申请成功
	eText_CampBattleRequest         = 20105,  //战场报名
	eText_CampBattleNoRequest       = 20106,  //当前不能报名
	eText_CampBattleWrongRoom       = 20107,  //错误的房间号
	eText_CampBattleOpen            = 20108,  //%s战场已开启，是否进入？
	eText_CampBattleResource        = 20109,  //资源点:%d 资源分:%d/%d
	eText_CampBattleResChange       = 20110,  //%s已被%s军英雄%s占领
	eText_CampBattleResOne          = 20111,  //马场
	eText_CampBattleResTwo          = 20112,  //农田
	eText_CampBattleResThree        = 20113,  //武器库
	eText_CampBattleResFour         = 20114,  //伐木场
	eText_CampBattleResFive         = 20115,  //矿坑
	eText_CampBattleLeftTime        = 20116,  //战场退出倒计时:%d%s
	eText_CampBattleSelectCamp      = 20117,  //请选择阵营
	eText_CampBattleCurCamp         = 20118,  //当前报名阵营
	eText_CampBattleCurRoom         = 20119,  //当前选择阵营
	eText_CampBattleMesBox          = 20120,  //邙山之战已经打响\n是否进入战场？

	eText_CampBattleKillAmount      = 20121,  //%s正在大杀特杀
	eText_CampBattleKillControl     = 20122,  //%s已经主宰了比赛
	eText_CampBattleKillNoPeople    = 20123,  //%s已经无人可挡
	eText_CampBattleKillMonster     = 20124,  //%s真的跟妖怪一样
	eText_CampBattleGoldLike        = 20125,  //%s已经超越神的杀戮
	eText_CampBattleBeKillAmount    = 20126,  //%s终结了%s的大杀特杀
	eText_CampBattleBeKillControl   = 20127,  //%s终结了%s的主宰比赛
	eText_CampBattleBeKillNoPeople  = 20128,  //%s终结了%s无人能挡的杀戮
	eText_CampBattleBeKillMonster   = 20129,  //%s终结了%s妖怪般的杀戮
	eText_CampBattleBeKillGoldLike  = 20130,  //%s终结了%s超越神的杀戮
	eText_MailNoSelect              = 20131,  //无勾选邮件，删除失败

	eText_PKBattleSign				= 20132,  //邙山之战报名开启
	eText_PKBattleFight				= 20133,  //邙山之战战斗开启
	eText_PKBattleLastFight			= 20134,  //邙山之战最后一轮开启
	eText_CampBattleEndRequest      = 20135,  //本轮战场已开启，请等待下个时段再来报名
	eText_CampBattleLastNoOver      = 20136,  //上一轮还没有结束
	eText_CampBattleKillMySelf      = 20137,  //%s杀死了我方将领%s
	eText_CampBattleKillHerSelf     = 20138,  //%s杀死了敌方将领%s
	eText_PKBattleGotoHaveBuff      = 20139,  //当前还不能传送
	eText_PKBattleNotSelfOccupy     = 20140,  //不是己方占领
	eText_PKBattleErrorGotoPos      = 20141,  //错误的传送地点
	eText_CampBattleRule            = 20142,  //阵营战场报名规则
	eText_CampBattleRequestLeftTime = 20143,  //距离下场报名开启剩余%s
	eText_CampBattleNoSend          = 20144,  //此地密道尚未修复，无法进行传送
	eText_CampBattleSendInfo        = 20145,  //是否要通过密道前往{#fffffa00=%s#}？
	eText_PKBattleNoMatch           = 20146,  //阵营战场没有匹配上
	eText_PKBattleNoMatchRoundEnd   = 20148,  //阵营战场最后一轮，没有匹配上

	eText_TeamBattleResource		= 20300,  //战场排名:%d  获取资源:%d/%d  死亡人数:%d
	eText_TeamBattleCostTime		= 20301,  //已用时间:%s
	eText_TeamBattleWin				= 20302,  //胜利
	eText_TeamBattleLost			= 20303,  //失败
	eText_TeamBattleSignup			= 20304,  //只有队长才能报名
	eText_TeamBattleName			= 20305,  //%s的队伍
	eText_TeamBattleRule			= 20306,  //小队战场规则说明
	eText_TeamBattleWaitWorning		= 20307,  //报名队伍不满3队 请等待下一次报名
	eText_TeamBattleLevelWorning	= 20308,  //等级不够，无法进入战场
	eText_TeamBattleNotify			= 20311,  //20311 - 20316队伍的排行提示

	eText_XinFaLevel				= 20400, //\n心法等级:%d
	eText_XinFaLearnLevel			= 20401, //\n学习等级:%d
	eText_XinFaCurrEffect			= 20402, //\n当前心法效果:
	eText_XinFaCurrLevel			= 20403, //当前层数:
	eText_XInFaNextLevel			= 20404, //下一层数:
	eText_XinFaNeedLevel			= 20405, //需求玩家等级
	eText_XinFaCengShu				= 20406, //层数
	eText_XinFaNeedCengShu			= 20407, //{#%x=需求心法层数:%d#}
	eText_XinFaSkillLevel			= 20408, //{#%x=等级:#}%d

	eText_StringCommon1             = 30001, //Common::_tstring strComment = "\nNeedLeve 活动需求等级(1～70)\n\ Quality  活动推荐度  (1～5 )\r\n\        MapPosX,MapPosY     (无发布NPC活动 寻路地点坐标)\n\        Duration 活动持续时间(单位:分)\n\        Count    活动次数限制(1~99 or -1为无限次数)\n\        ComleteId  活动次数计数变量(脚本自定义)
	eText_StringCommon2             = 30002, //Common::_tstring strComment = "Recipe ID 为配方的编号\Name      为配方的中文名称\Type      配方的类型.\PrimaryMaterials 主要的配方\Material Id 主要配方里材料的编号\Count      主要配方需要的材料数量\CastTime   合成的吟唱时间\NeedEnergy 消耗的活力值\NeedMoney  消耗的金钱\Probility  产出的概率\ProficiencyLimit 生产物品能提升到的熟练度上限
	eText_StringOpenFailed          = 30003, //打开失败!
	eText_StringMoveRecord          = 30004, //移动路径记录
	eText_StringName                = 30005, //名字:%s  编号:%d  坐标(x=%d, y=%d)
	eText_BillBoardFailed           = 30006, //加修改公告失败的字串
	eText_ItemNewFailed             = 30007, //CItemDetail构造申请内存
	eText_StringNoArried            = 30008, //该npc被禁止寻路到达！
	eText_StringQuest               = 30009, //QuestInfo::CreateQuest中创建SQuest
	eText_StringPersonName          = 30010, //名字
	eText_StringContext             = 30011, //内容
	eText_StringUpdateFaild         = 30012, //升阶失败
	eText_StringPlayerName          = 30013, //玩家姓名
	eText_StringPlayerLevel         = 30014, //玩家等级
	eText_StringPalyerProfession    = 30015, //玩家职业
	eText_StringNew                 = 30016, //新品
	eText_StringHot                 = 30017, //热卖
	eText_StringYuanZhong           = 30018, //元宗
	eText_StringNoPlayer            = 30019, //没有这个名字“%s”的npc或怪物
	eText_StringSingleName          = 30020, //飞起一剑
	eText_StringSingle              = 30021, //单机
	eText_StringQuedePos            = 30022, //你目前排的队列位置是: %d\n当前服务器总人数为: %d
	eText_StringFontSong            = 30023, //宋体

	eText_BargainFailedError1		= 30024, //物品错误, 请整理包裹 
	eText_BargainFailedError2		= 30025, //物品被锁定, 不能交易 
	eText_BargainFailedError3		= 30026, //数据错误( 可能是数据结构长度有错 ) 
	eText_BargainFailedError4		= 30027, //出战的马不能交易 
	eText_BargainFailedError5		= 30028, //此物品已经在交易 
	eText_BargainFailedError6		= 30029, //携带金钱超过限制 
	eText_BargainFailedError7		= 30030, //对方所要交易的物品数据异常，交易失败                               
	eText_BargainFailedError8		= 30031, //对方所要交易的物品已锁定，交易失败                                
	eText_BargainFailedError9		= 30032, //对方所要交易的物品数据错误，交易失败                        
	eText_BargainFailedError10		= 30033, //对方坐骑处于出战状态，交易失败                                   
	eText_BargainFailedError11		= 30034, //对方物品已经在交易，交易失败                                   
	eText_BargainFailedError12		= 30035, //对方携带金钱超过限制，交易失败                                   

	eText_QuestNoFight              = 30049, //只能在战斗状态下使用
	eText_QuestInFight              = 30050, //战斗状态下无法使用

	eText_PrivateShopItemError		= 30051, //摆摊物品数据异常，请整理包裹后重新放置

	eText_MarryMenTask              = 30100,//申请方必须为男方且必须达到%d级才能进行结婚任务
	eText_MarryMustMen              = 30101,//对方必须为女性,且等级不低于%d级
	eText_MarryTask                 = 30102,//男女双方必须同在队伍中才可进行结婚任务
	eText_MarryIsLeader             = 30103,//男方必须是队伍的队长
	eText_MarryOnlyTwoPeople        = 30104,//队伍中只能有男女双方两人
	eText_MarryInSameTeam           = 30105,//对方必须在队伍中
	eText_MarryHasWift              = 30106,//你已经有妻子了
	eText_MarryMustIsFriend         = 30107,//双方必须有好友关系且无其他关系
	eText_MarryFriendNoEnough       = 30108, //双方好友度不足%d点
	eText_MarryInSameSceen          = 30109,//对方必须在你身边
	eText_MarryHasHoushand          = 30110,//对方已经有丈夫了
	eText_MarryRelation             = 30111,//必须是夫妻关系才能开启婚庆场景
	eText_MarrySceneMax             = 30112,//婚庆场景已经达到最大数
	eText_MarrySceneCreateFailed    = 30113, //婚庆场景创建失败, 请重试
	eText_MarrySceneNoOpen          = 30114,//婚庆场景尚未开启
	eText_MarryAskMarryInfo         = 30115,//求婚申请
	eText_MarryAskMarry             = 30116,//{#fffffa00=%s#}向你求婚
	eText_MarrySceneOpen            = 30117,//婚庆场景已开启
	eText_MarrySexInSameTeam        = 30118,//只有夫妻双方在同一队伍中才能完成任务
	eText_MarryHusband              = 30119,//老公
	eText_MarryWife                 = 30120,//老婆
	eText_HusbandOnline				= 30121, //你的老公 ~%s_ 上线了
	eText_WifeOnline				= 30122, //你的老婆 ~%s_ 上线了
	eText_HusbandOffline			= 30123, //你的老公 ~%s_ 下线了
	eText_WifeOffline				= 30124, //你的老婆 ~%s_ 下线了
	eText_ReqDivorce				= 30125, //%s请求协议离婚，\n是否同意？
	eText_DivorceSucceed			= 30126, //协议离婚成功
	eText_DivorceFailed				= 30127, //协议离婚失败
	eText_MaleLevelLimit1			= 30128, //申请方必须为男方且必须满足%d级才能结婚
	eText_MaleLevelLimit2			= 30129, //申请方必须为男方且必须满足%d级才能开启爱心岛

	eText_KillMonsterBroadcast      = 30300, //%s在%s打败了%s之后以外的从地上发现了%s

	eText_MailSystemTitle           = 30500, // 系统消息
	eText_MailSystemName            = 30501, // 系统
	eText_MailRemoveMarriage        = 30502, // %s已与你解除夫妻关系，你们夫妻缘分已尽，您可在茫茫人海中重新寻觅另一半前往扬州红线处展开新的姻缘试炼
	eText_MailRemoveTeacher         = 30503, // %s已与你解除师徒关系，你们师徒缘分已尽，您可在茫茫人海中重新招收一名弟子进行指导
	eText_MailRemoveStudent         = 30504, // %s已与你解除师徒关系，你们师徒缘分已尽，您可在茫茫人海中重新寻找一名师傅进行请教
	eText_MailBeKickedFromFamily	= 30505, // 你已经被家族长踢出家族！
	eText_MailFamilyDisbanded		= 30506, // 家族已经被解散，您已经离开家族！

	eText_Stall_Pet_Used = 30600, //宠物已出战，无法摆摊
	eText_Stall_No_Item = 30601, //没有道具，无法摆摊
	eText_Stall_Rent = 30602,	//摊位费
	eText_Stall_Tax = 30603, //税收
	eText_Stall_YesNo = 30604, //是否开始在此摆摊
	eText_Stall_offLine_login = 30605, //该帐号正处于离线摆摊状态，请稍后再登陆
	eText_Stall_Not_Right_Item = 30606, //该物品未满足代工条件
	eText_Stall_Proxy_Succeed = 30607,	//购买代工成功
	eText_Stall_Too_Near = 30608,	//距离过近，无法摆摊
	eText_Stall_Choose_Tip = 30609,	//摆摊选择框的提示
	eText_PetAliveTime        = 30610,//宠物复活时间
	eText_NotEnoughMoneyForOffline = 30611,//没有足够的钱去离线摆摊
	eText_NotEnoughMoneyFonOnline  =30612,//没有足够的钱去在线摆摊
	eText_NormalTextStall      =30613,//本地为普通摆摊区域
	eText_NoticeForStall	   =30614,//带有元宝字样的只能够在制定区域摆摊

	eText_CarryTimeLimit      = 31000,//超出最大活动范围,%d秒后离开载具
	eText_CarryGetBack        = 31001,//您回到了活动范围内
	eText_CountryRewardbiaoti		  = 31002,//国战邮件标题
	eText_CountryRewardneirong		  = 31003,//国战邮件内容

	eText_360VirusInfoTip           = 60100, //正在扫描内存，请稍候……
	eText_360VirusInfoScanFile      = 60101, //正在扫描:%s
	eText_360VirusInfoFindVirus     = 60102, //发现木马病毒:%s
	eText_360VirusInfoVirusPath     = 60103, //文件路径:%s


	//A阵营战场房间号
	eText_CampBattleARoom1           = 91550, //
	eText_CampBattleARoom2           = 91551, //
	eText_CampBattleARoom3           = 91552, //
	eText_CampBattleARoom4           = 91553, //
	eText_CampBattleARoom5           = 91554, //
	eText_CampBattleARoom6           = 91555, //
	eText_CampBattleARoom7           = 91556, //
	eText_CampBattleARoom8           = 91557, //
	eText_CampBattleARoom9           = 91558, //
	eText_CampBattleARoom10          = 91559, //
	eText_CampBattleARoom11          = 91560, //
	eText_CampBattleARoom12          = 91561, //

	//B阵营战场房间号
	eText_CampBattleBRoom1           = 91570, //
	eText_CampBattleBRoom2           = 91571, //
	eText_CampBattleBRoom3           = 91572, //
	eText_CampBattleBRoom4           = 91573, //
	eText_CampBattleBRoom5           = 91574, //
	eText_CampBattleBRoom6           = 91575, //
	eText_CampBattleBRoom7           = 91576, //
	eText_CampBattleBRoom8           = 91577, //
	eText_CampBattleBRoom9           = 91578, //
	eText_CampBattleBRoom10          = 91579, //
	eText_CampBattleBRoom11          = 91580, //
	eText_CampBattleBRoom12          = 91581, //

	// 最佳装备的常用文字
	eText_BestEquip1					= 92000, // 最适合的装备
	eText_BestEquip2					= 92001, // 档次%d 等级%d
	eText_BestEquip3					= 92002, // %s获取方式

	// 搭载坐骑相关
	eText_SameTeamLimit					= 93000, // 必须和主人同一个队伍才可以搭载他坐骑！
	eText_InviteGetOn					= 93001, // %s邀请您上他的坐骑！
	eText_RequestGetOn					= 93002, // %s请求上您的坐骑！
	eText_RejectInvite					= 93003, // %s拒绝您上坐骑的邀请！
	eText_RejectRequest					= 93004, // %s拒绝您上坐骑的申请！
	eText_KickOffByHost					= 93005, // 你已被主人踢下马了
	eText_OnMultiMount					= 93006, // 你已经在多人坐骑上了
	eText_NoMultiMount					= 93007, // 你还没有骑上多人坐骑，不能邀请

	eText_PetNoData                     = 94000, //没有找到宠物数据
	eText_PetPointError                 = 94001, //宠物潜力点分配错误
	eText_PetEnough                     = 94002, //携带宠物已满
	eText_PetLessTakeLevel              = 94003, //携带等级不足
	eText_PetNoFight                    = 94004, //战斗状态宠物无法出战
	eText_PetDead                       = 94005, //死亡状态宠物无法出战
	eText_PetNoLife                     = 94006, //寿命不足宠物无法出战
	eText_PetNoHappy                    = 94007, //快乐度不足宠物无法出战
	eText_PetNoReLife                   = 94008, //重生时间还未到
	eText_PetReturnLife                 = 94009, //繁殖过的宠物无法还童
	eText_PetNoReturnLife               = 94010, //变异宠物无法还童
	eText_PetFailLearnSkill             = 94011, //宠物技能学习失败
	eText_PetFailFanZhi                 = 94012, //繁殖失败
	eText_PetNoInTeam                   = 94013, //您没有处于队伍中
	eText_PetMoreTwo                    = 94014, //您的队伍超过了2名
	eText_PetNoLeader                   = 94015, //您不是队伍的队长
	eText_PetNoTeamer                   = 94016, //队友不在旁边
	eText_PetHaveFanZhi                 = 94017, //已经有宠物在繁殖中
	eText_PetFailSelect                 = 94018, //宠物选择失败
	eText_PetTradeMySelf                = 94019, //自己开始宠物交易
	eText_PetTradeTarget                = 94020, //对方开始宠物交易
	eText_PetLockMySelf                 = 94021, //自己锁定宠物
	eText_PetLockTarget                 = 94022, //对方锁定宠物
	eText_PetConfirmMySelf              = 94023, //自己确定宠物交易
	eText_PetConfirmTarget              = 94024, //对方确定宠物交易
	eText_PetScessFanZi                 = 94025, //繁殖成功
	eText_PetFailFanZi                  = 94026, //繁殖失败
	eText_PetTimeOutFanZi               = 94027, //繁殖超时
	eText_PetCancel                     = 94028, //对方取消繁殖
	eText_PetTargetExit                 = 94029, //对方下线，繁殖取消	
	eText_PetConfirmFail                = 94030, //宠物确认失败
	eText_PetNoFanZi                    = 94031, //没有繁殖宠物
	eText_PetNoElapse                   = 94032, //时间间隔未到
	eText_PetNoSpace                    = 94033, //宠物栏已经满
	eText_PetGet                        = 94043, //获得宠物
	eText_PetLevel                      = 94044, //放生宠物

	eText_PetLevelSkill               = 94045,//宠物等级不足学习失败
	eText_PetSkillMoney            = 94046,//金钱不足无法学习
	eText_PetSavvyUpMoney    = 94047,//金钱不足无法提升悟性
	eText_PetSavvyBone             = 94048,//根骨不足无法提升悟性
	eText_PetSavvyUp                 = 94049,//宠物提升悟性失败
	eText_PetIsActivePet			   = 94050,//出战宠物无法进行操作
	//全部族系
	eText_PhyleAll							= 94051,//全部族系
	eText_PhyleHuman					= 94052, //人类
	eText_PhyleMachine				= 94053, //机器
	eText_PhyleBeast						= 94054, //兽类
	eText_PhyleImmortal				= 94055, //仙族
	eText_PhyleGhost					= 94056,//鬼族
	eText_PhyleBogey					= 94057,//妖族
	eText_PhyleDeity						= 94058,//神族
	eText_PhyleDemon					= 94059,//魔族

	eText_MissionCountFirst			= 94060,	// 使命点未达到要求已被系统计数，请积极管理帮派！
	eText_MissionCountSecond		= 94061,	// 帮派已经到达危险期，请注意及时管理！
	eText_MissionCountThird			= 94062,	// 很遗憾，帮派因管理不善，导致系统收回，帮派解散！

	eText_PetStudySuccess                     = 94070, //宠物学习成功
	eText_PetSavvyUpSuccess					= 94071,//宠物悟性提升成功
	eText_SelectSamePet							= 94072,//选择了相同的宠物
	eText_CatchSkillLevel							= 94073,//宠物捕捉技能等级不足
	eText_PetIdentify									= 94074,//没有宠物图鉴无法捕捉
	eText_PetCatchFail								= 94075,//捕捉宠物失败
	eText_PetCatchSuccess						= 94076, //捕捉宠物成功
	eText_PetIsActivedCannotSelect		 = 94077,//宠物处于出战状态不能被选择
	eText_PetSavvyFull								= 94078,//宠物悟性已满10级，或者成年宠物不能被提升悟性
	eText_PetCannotMaterial					= 94079,//该宠物不能用作材料宠物
	eText_PetSelectFirst							= 94080,//请先选择需要提升悟性的宠物
	eText_PetNoneItem							= 94081,//尚未添加道具材料
	eText_PetCannotCatch						= 94082,//该宠物不能被捕捉
	//宠物性格
	eText_PetPoltroon								= 94083,//胆小
	eText_PetWariness								= 94084,//谨慎
	eText_PetLoyal										= 94085,//忠诚
	eText_PetCanniness							= 94086,//精明
	eText_PetBravery									= 94087,//勇猛

	eText_PetChuZhan								= 94088,//宠物出战吟唱条
	eText_PetLevelUp								= 94089,//您的宠物[%s]等级升至[%d]级
	eText_PetSavvyLevelUp						= 94090,//您的宠物[%s]因为升级眼前一亮,领悟了技能[%s]
	eText_PetBreedMaxNum					= 94091,//宠物繁殖次数已满
	eText_PetChuZhanLevelNotEnough= 94092,//宠物出战等级不足
	eText_PetNameGen							=94093,//%d代%s
	eText_PetLoyaltyLower						= 94094,//宠物快乐度不足无法繁殖
	eText_PetDruationLower					= 94095,//宠物寿命不足无法繁殖
	eText_PetBookLearnSkill					= 94096,//您的宠物%s通过技能书学会了技能%s
	eText_HasPetSkill								= 94097,//宠物已经学习了该技能
	eText_PetSkillGroupLevel					= 94098,//宠物已经学习高级技能
	eText_PetReplaceSkill							= 94099,//您的宠物%s 学会了%s替换了%s
	eText_MonsterCatchLevelNotEnough = 94100,//怪物捕捉需要%d等级
	eText_PetActiveCannotFanZhi				 =94101,//出战宠物无法被选择繁殖
	eText_PetCannotFanZhi							 =94102,//不能选择成年宠物或者变异宠物进行繁殖!
	eText_PetTypeNotCatch						 = 94103,//您的队友已选择了[%s],您必须要选择同类型的宠物! 
	eText_PetSexNotCatch							 = 94104,//您的队友已选择了[%s]的宠物,您必须要选择不同性别的宠物!
	eText_PetMale											 = 94105,//雄性
	eText_PetFemale										 = 94106,//雌性

	eText_PetNoEnoughMoney  				 = 94107,//金钱不足无法领取
	eText_PetNeedMoneySingel				 = 94108,//单人领取需要金钱
	eText_SelfCancelLockPet						 = 94109,//自己取消锁定宠物
	eText_TargetCancelLockPet					 = 94110,//对方取消锁定宠物
	eText_TeamPlayerPeting						 = 94111,//队伍里有队员尚有宠物在繁殖中,不能重复繁殖!
	eText_PetSource_Other							 = 94112,//其他
	eText_PetSource_Skill								 = 94113,//捕捉
	eText_PetSource_BabyBreed				 = 94114,//繁殖得到宝宝
	eText_PetSource_Stall							 = 94115,//交易
	eText_PetSource_Breed							 =94116, //繁殖得到成年的
	eText_PetDisappear								 =94117,//宠物因繁殖而消失
	eText_PetLost											 =94118,//宠物伤心过度走了
	eText_PetBreedTime								 =94119,//宠物繁殖时间到了快去领取
	eText_PetGenerationNotCatch				 =94120,//二代以上宠物无法被选择
	eText_PetBoneNotEnough					 =94121,//作材料的宠物的根骨必须大于被提成宠物的根骨
	eText_PetFangshengLost						 =94122,//宠物%s因放生而消失
	eText_PetSavvyUpLost							 =94123,//宠物%s因提升悟性而消失
	eText_PetBreedLost								 =94124,//宠物%s因繁殖而消失
	eText_PetStallLost									 =94125,//宠物%s因交易而消失
	eText_PetTeamPlayerGet						 =94126,//队友%s领取了宠物
	eText_PetLearnAdvanceSkillOnBase	 =94127,//您的宠物在%s的基础上,习得了%s!
	eText_PetSavvyReduce							 =94128,//宠物一不小心悟性降低到了%d!
	eText_PetBreedSuccess							 = 94200,        //~%s_ 通过宠物繁殖获得新的宠物 [%s] 
	eText_HaveNonePetCard						 =94201, //目前还有没有该怪物的卡片
	eText_HaveNonePet							 =94202,//您目前还没有宠物，可以通过捕捉或繁殖等得到宠物
	eText_FamilyCreateSuccess			= 95001,		//创建家族成功
	eText_FamilyErrorName				= 95002,		//家族命名非法
	eText_FamilyRepeatName				= 95003,		//家族名已存在
	eText_FamilyCreateSuccessTip		= 95004,		//玩家%s成功创立家族%s
	eText_FamilyInviteTip				= 95005,		//玩家%s邀请你加入家族%s
	eText_FamilyInvite					= 95006,		//邀请加入家族
	eText_FamilyInviteAckSuccess		= 95007,		//邀请成功
	eText_FamilyInviteAckNoFamily		= 95008,		//你没有家族
	eText_FamilyInviteAckNoRight		= 95009,		//你没有权限邀请
	eText_FamilyInviteAckOffline		= 95010,		//你邀请的玩家不存在或不在线
	eText_FamilyInviteAckHaveFamily		= 95011,		//对方已经有了家族
	eText_FamilyInviteAckLevelLimit		= 95012,		//对方等级不够，不能邀请加入家族
	eText_FamilyInviteAckFamilyFull		= 95013,		//成员数已经满了
	eText_FamilyInviteAckRefuse			= 95014,		//对方拒绝加入家族
	eText_FamilyKickoutTip				= 95015,		//你确定要将玩家%s踢出家族！
	eText_FamilyKickout					= 95016,		//踢出家族
	eText_FamilyQuitYesNo				= 95017,		//你确定要退出家族
	eText_FamilyQuit					= 95018,		//退出家族
	eText_FamilyQuitTip					= 95019,		//玩家%s离开了家族%s
	eText_FamilyJoinTip					= 95020,		//玩家%s加入了家族%s
	eText_FamilyModifyNoteSuccess		= 95021,		//修改家族公告成功！
	eText_FamilyModifyNoteFailed		= 95022,		//修改家族公告失败！
	eText_FamilyContributeSuccess		= 95023,		//家族资金捐献%d金%d银%d铜成功！
	eText_FamilyContributeFailed		= 95024,		//家族资金到达上限，捐献失败！
	eText_FamilyContributeTip			= 95025,		//玩家%s捐献了家族资金%d金%d银%d铜
	eText_FamilyUpgradeAckSuccess		= 95026,		//家族升级成功！
	eText_FamilyUpgradeAckFailed		= 95027,		//家族升级失败！
	eText_FamilyHaveNoFamily			= 95028,		//你还没有家族！
	eText_FamilyIncorrectName			= 95029,		//家族名长度不合法！
	eText_FamilyNoteLenIncorrect		= 95030,		//输入家族公告长度不合法！
	eText_FamilyAimLenIncorrect			= 95031,		//输入家族宗旨长度不合法！
	eText_FamilyRequestSuccess			= 95032,		//成功加入了%s家族
	eText_FamilyLevelNotEnough			= 95033,		//等级不足
	eText_FamilyRefuseJionIn24			= 95034,		//退家族以后24小时内不能加入家族
	eText_FamilyNoSuchFamily			= 95035,		//申请的家族不存在
	eText_FamilyFull					= 95036,		//目标家族成员数已经满了
	eText_FamilyRefuseJion				= 95037,		//拒绝加入
	eText_FamilyManagerOffline			= 95038,		//家族管理员都不在线
	eText_FamilyPlayer					= 95039,		//玩家
	eText_FamilyPlayerReach10			= 95040,		//已升到10级，可以邀请加入家族
	eText_FamilyRequestMsg				= 95041,		//输入家族申请消息长度不合法！

	eText_FamilyCantChat				= 95042,		//你还没有家族，不能在家族频道聊天
	eText_FamilySureExpel				= 95043,		//你确定要转让族长！
	eText_FamilySureUpgrad				= 95044,		//你确定要升级家族！\n下一级别是%d级 \n需要消耗繁荣度%d,需要消耗金钱%s
	eText_FamilyLeader					= 95045,		//族长
	eText_FamilySuccessedLeave			= 95046,		//你已成功退出家族%s
	eText_FamilyBeKickout				= 95047,		//你已被族长%s踢出了家族
	eText_FamilyRefuseInviteIn24		= 95048,		//退家族以后24小时内不能被邀请加入家族

	eText_FamilyModifyAimSucc			= 95049,		//修改家族宗旨成功
	eText_FamilyOnceInWeek				= 95050,		//拒绝修改，一周内只能修改一次
	eText_FamilyModifyAimFailed			= 95051,		//修改家族宗旨失败
	eText_FamilyMaxLevel				= 95052,		//你的家族已是满级
	eText_FamilyLevelNotEnogh			= 95053,		//你的等级不够，不能加入家族
	eText_FamilyAimForbiddenWords		= 95054,		//家族宗旨含有非法字符，请重新输入
	eText_FamilyNoteForbiddenWords		= 95055,		//公告含有非法字符
	eText_FamilyJoinSucess				= 95056,		//你已成功发送申请加入家族
	eText_FamilyLevelReachTo			= 95057,		//你的家族已升级到%d级
	eText_FamilyInputName				= 95058,		//请输入要添加玩家的名字
	eText_FamilyAlreadyHave				= 95059,		//你已经加入家族，无法再申请
	eText_FamilyTransferFailed			= 95060,		//转让族长失败，你没有这个权限
	eText_FamilyYouAreLeader			= 95061,		//你已成为%s家族族长
	eText_FamilyTransFailedNoPlayer		= 95062,		//转让族长失败，玩家不存在
	eText_FamilyYourLevelNotEnough		= 95063,		//等级不足，不能创建家族
	eText_FamilyYourMoneyNoteEnough		= 94064,		//背包金钱不足，不能创建家族

	eText_GuideASDWMovePlayer			= 96001,		//请按ASDW键移动角色
	eText_GuideClickMovePlayer			= 96002,		//请用鼠标左键点击地面
	eText_GuideRMouseRote				= 96003,		//请按鼠标右键拖动旋转视角
	eText_GuideSpaceJump				= 96004,		//请按空格键跳跃
	eText_GuideFinishMovePlayer			= 96005,		//你已完成移动角色操作
	eText_GuideFinishLMouseOpt			= 96006,		//你已完成鼠标左键操作
	eText_GuideFinishRMouseOpt			= 96007,		//你已完成鼠标右键操作
	eText_GuideFinishSpaceOpt			= 96008,		//你已完成按空格跳跃操作
	eText_GuideIsNewPlayer				= 96009,		//你是否新玩家？选择\"是\"将启动教程，\"否\"直接进入游戏
	eText_GuideMovePlayerUp				= 96010,		//请按W键向前移动角色
	eText_GuideMovePlayerDown			= 96011,		//请按S键向后移动角色
	eText_GuideMovePlayerLeft			= 96012,		//请按鼠标右键+A键向左移动角色
	eText_GuideMovePlayerRight			= 96013,		//请按鼠标右键+D键向右移动角色
	eText_GuideFinishMovePlayerUp		= 96014,		//你已完成向前移动角色操作
	eText_GuideFinishMovePlayerDown		= 96015,		//你已完成向后移动角色操作
	eText_GuideFinishMovePlayerLeft		= 96016,		//你已完成向左移动角色操作
	eText_GuideFinishMovePlayerRight	= 96017,		//你已完成向右移动角色操作

	//主将变身相关
	eText_ZhuJiangHpMaxAdd				= 98000,		//HP上限增加%d
	eText_ZhuJiangMpMaxAdd				= 98001,		//MP上限增加%d
	eText_ZhuJiangAttackPhysicsAdd		= 98002,		//物理攻击增加%d
	eText_ZhuJiangAttackMagicAdd		= 98003,		//物理防御增加%d
	eText_ZhuJiangDefendPhysicsAdd		= 98004,		//魔法攻击增加%d
	eText_ZhuJiangDefendMagicAdd		= 98005,		//魔法防御增加%d
	eText_ZhuJiangExactAdd				= 98006,		//命中增加%d
	eText_ZhuJiangDodgeAdd				= 98007,		//闪避增加%d
	eText_ZhuJiangCriticalAdd			= 98008,		//暴击增加%d
	eText_ZhuJiangTenacityAdd			= 98009,		//韧性增加%d

	eText_ZhuJiangSuccess				= 99100,		//变身成功
	eText_ZhuJiangNoHero				= 99101,		//找不到对应主将，变身失败
	eText_ZhuJiangNoMaterial			= 99102,		//没有足够材料，变身失败
	eText_ZhuJiangNoMoney				= 99103,		//没有足够金钱，变身失败
	eText_ZhuJiangNoLevel				= 99104,		//等级不够，变身失败
	eText_ZhuJiangPopErro				= 99105,		//相关物品不能被消耗，变身失败
	eText_ZhuJiangSexErro				= 99106,		//性别不符合，变身失败
	eText_ZhuJiangFail					= 99107,		//变身失败

	eClient_AddInfo_2slk_NoRide			= 99200,		//该状态下不能骑马
	eText_FuJiang_NotActived			= 99201,		//请选择需要出战的副将
	eText_CoutryActived					= 99202,		//当前没有国家活动
	eText_NoPetActived                  = 99203,        //没有出战的副将，使用道具失败  
	eText_LostThings                    = 99204,        //你失去了%d%s!
	eText_MovingContZHFJ                = 99205,        //移动中不能召唤副将
	eText_ContEnterTPHJ_Onbiaoche       = 99206,    //运镖过程中不能进入太平幻境
	eText_TargetMapCont_OnRiding        = 99207,       //目标地图不可骑乘，请先下马
	eText_ActivePetContStudySill        = 99208,    //出战宠物不能进行技能学习，请先收回。
	eText_PetError_OnActive             = 99209,    //当前地图不能召唤宠物

	eText_UnBind						= 99210,
	eText_UnBind_Non					= 99211,
	eText_UnBind_Num					= 99212,
	eText_UnBind_Error1					= 99213,
	eText_UnBind_Error2					= 99214,
	eText_UnBind_Error3					= 99215,
	eText_UnBind_Error4					= 99216,
	eText_UnBind_Error5					= 99217,
	eText_UnBind_Error6					= 99218,
	eText_UnBind_Error7					= 99219,
	eText_UnBind_Error8					= 99220,
	eText_UnBind_Info					= 99221,
	eText_ContThisOp                    = 99222, 

	eText_KillPlayerNUM                 = 99223, 
	eText_Kill50Player                  = 99224, 
	eText_PKModeAttact					= 99225,

	eText_Country_BeStrong				= 99226,//国家变强了

	eText_Country_Strongth				= 99227,
	eText_Country_Weak					= 99228,
	eText_Country_Normal				= 99229,

	eText_GuildSQError1					= 99230,
	eText_GuildSQ						= 99231,


	eText_CountryRaiseTitle				= 99232,
	etext_CountryRaiseContext			= 99233,
	eText_GuildRaiseTitle				= 99234,
	etext_GuildRaiseContext				= 99235,

	eText_Guild_NotCountry				= 99236,
	eText_FamilyNotCountry				= 99237,

	eText_TeamFail_NotOnLine			= 99238,

	eText_Quest_TaskScriptExp           = 99239, //{#fff4db30=经验奖励: %d#}
	eText_Quest_ScriptExp1				= 99240,
	eText_Quest_ScriptExp2				= 99241,
	eText_WeopenHpWhithZero             = 99242, //武器损坏，不能进行攻击

	eText_UnBind_Sec					= 99243,
	eText_NonCountryByCountry			= 99244,
	eText_NonCountryByGuild				= 99245,

	eText_CountryBetray_Item			= 99246,
	eText_CountryBetray_Office			= 99247,
	eText_CountryBetray_config			= 99248,

	eText_CountryInfoGY					= 99249,
	eText_CountryInfoGT					= 99250,
	eText_CountryInfoHL					= 99251,
	eText_CountryInfoBS					= 99252,

	eText_CountryBetray_MaxLevel		= 99253,
	eText_CountryBetray_MinLeve			= 99254,
	eText_CountryBetray_QuestState		= 99255,

	eText_SuAnimalRecive				= 99256,

	eText_GuildGG						= 99257,
	eText_CountryGG						= 99258,


	eText_GuildUnionCamp				= 99259,//帮会联合争夺战
	eText_GuildUnionCamp_BullSystem_SignUp	= 99260,//帮会战报名的系统公告
	eText_GuildUnionCamp_BullSystem_Prepare = 99261,//帮会战准备状态的系统公告
	eText_GuildUnionCamp_TimeToCampStart	= 99262,//离帮派争夺战开始
	eText_GuildUnionCamp_BullSystem_Enter	= 99263,//进入帮会战场状态的系统公告
	eText_GuildUnionCamp_TimeToCampEnd		= 99264,//离帮派争夺战结束
	eText_GuildUnionCamp_BullSystem_Fight	= 99265,//战场战斗状态的系统公告
	eText_GuildUnionCamp_BullSystem_Over	= 99266,//帮会战结束的系统公告
	eText_GuildUnionCamp_EnterBattleInfo	= 99267,//帮派争夺战进入框上的提示
	eText_Camp_GuildUnionBattleResult		= 99268,// 通知帮派战场结果
	eText_SignUp_GuildUnionBattleSumError	= 99269,//当前轮数不可以报名
	eText_SignUp_GuildUnionBattleNone		= 99270,//当前战场不需要报名 开始后可以直接参与
	eText_SignUp_GuildBattleFull			= 99271,//报名人数已满
	eText_Enter_BattleSumError				= 99272,//不是指定胜利公会 不可以进入


	eText_CountryReward_Title_King				= 99273,
	eText_CountryReward_Contentt_King			= 99274,

	eText_CountryReward_Title_Queen				= 99275,
	eText_CountryReward_Contentt_Queen			= 99276,

	eText_CountryReward_Title_QinWan			= 99277,
	eText_CountryReward_Contentt_QinWan			= 99278,

	eText_CountryReward_Title_General			= 99279,
	eText_CountryReward_Contentt_General		= 99280,

	eText_CountryReward_Title_CouncilorRight	= 99281,
	eText_CountryReward_Contentt_CouncilorRight	= 99282,

	eText_CountryReward_Title_CouncilorLeft		= 99283,
	eText_CountryReward_Contentt_CouncilorLeft	= 99284,

	eText_CountryReward_Title_CaptorRight		= 99285,
	eText_CountryReward_Contentt_CaptorRight	= 99286,

	eText_CountryReward_Title_CaptorLef			= 99287,
	eText_CountryReward_Contentt_CaptorLeft		= 99288,
	eText_CountryKing_New						= 99289,//%s成为 %s 国的新国王

	eText_Country_Battle_None					= 99290,

	eText_WorldBattle_Prepare					= 99291,
	eText_WorldBattle_Fight						= 99292,
	eText_WorldBattle_End						= 99293,

	eText_MonsterNurtureInfo_Buff				= 99294,

	eText_Country_Dismiss_Del					= 99295,//辞去官职成功
	eText_Country_Dismiss_Del_Not				= 99296,//辞去官职失败 无官职
	eText_Country_Dismiss_Del_King				= 99297,//国王不可以辞去官职
	eText_Country_Dismiss_Del_Queen				= 99298,//王后或者亲王不可以辞去官职
	eText_Country_Dismiss_Del_NonCountry		= 99299,//无国家不可以辞去官职

	eText_CampBattle_TimeShow					= 99300,//%d天%d小时%d分钟%d秒
	eText_CampBatrle_Info						= 99301,//星期%d %d小时%d分钟 持续 %d分钟
	eText_CampGuildBattle_States_0				= 99302,//公会战开始报名 时间为 %s
	eText_CampGuildBattle_States_1				= 99303,//公会战开始准备 时间为 %s
	eText_CampGuildBattle_States_2				= 99304,//公会战开始进入 时间为 %s
	eText_CampGuildBattle_States_3				= 99305,//公会战开始战斗 时间为 %s
	eText_CampGuildBattle_States_4				= 99306,//公会战结束  时间为 %s
	eText_CampCountryBattle_States_0			= 99307,//国王战开始报名 时间为 %s
	eText_CampCountryBattle_States_1			= 99308,//国王战开始准备 时间为 %s
	eText_CampCountryBattle_States_2			= 99309,//国王战开始进入 时间为 %s
	eText_CampCountryBattle_States_3			= 99310,//国王战开始战斗 时间为 %s
	eText_CampCountryBattle_States_4			= 99311,//国王战结束  时间为 %s
	eText_CampGuildUnionBattle_States_0			= 99312,//公会联合战开始报名 时间为 %s
	eText_CampGuildUnionBattle_States_1			= 99313,//公会联合战开始准备 时间为 %s
	eText_CampGuildUnionBattle_States_2			= 99314,//公会联合战开始进入 时间为 %s
	eText_CampGuildUnionBattle_States_3			= 99315,//公会联合战开始战斗 时间为 %s
	eText_CampGuildUnionBattle_States_4			= 99316,//公会联合战结束  时间为 %s
	eText_CampWordBattle_States_1				= 99317,//野外战开始准备 时间为 %s
	eText_CampWordBattle_States_3				= 99318,//野外战开始战斗 时间为 %s
	eText_CampWordBattle_States_4				= 99319,//野外战结束  时间为 %s


	eText_LeaveTeam								= 99320,//将在%秒后离开队伍 请尽快回到指定区域
	eText_NonLeaveTeam							= 99321,//已经回到合适区域 离开队伍命令取消

	eText_CampBattle_SignUp						= 99322,//报名
	eText_CampBattle_Prepare					= 99323,//准备
	eText_CampBattle_Enter						= 99324,//进入
	eText_CampBattle_Fight						= 99325,//开始
	eText_CampBattle_End						= 99326,//结束


	eText_GuildCampBattle_Non					= 99327,//目标错误
	eText_GuildCampBattle_Master				= 99328,//不是帮主
	eText_GuildCampBattle_Level					= 99329,//目标等级不够
	eText_GuildCampBattle_Position				= 99330,//目标职业不对
	eText_GuildCampBattle_Offer					= 99331,//目标帮贡不够
	eText_GuildCampBattle_MaxSum				= 99332,//超过最大数量
	eText_GuildCampBattle_Dou					= 99333,//目标已有相同权限

	eText_GuildCampBattle_Country				= 99334,
	eText_GuildCampBattle_Guild					= 99335,
	eText_GuildCampBattle_GuildUnion			= 99336,

	eText_GuildCampBattle_NonSelect				= 99337,//设置失败 未选择指定玩家

	eText_SuAnimalChangeName					= 99338,
	eText_ActionPetNon							= 99339,

	eText_PetEquip_Remove_Title					= 99340,
	eText_PetEquip_Remove_Context				= 99341,

	eText_Pet_Non								= 99342,//未选择副将
	eText_Pet_Action							= 99343,//副将未出战
	eText_Pet_Equip_Non							= 99344,//指定副将装备不存在
	eText_Pet_Equip_TypeError					= 99345,//非副将装备
	eText_Pet_Equip_Level						= 99346,//等级不够
	eText_Pet_Equip_TimeEnd						= 99347,//装备过期
	eText_Pet_Equip_Pos							= 99348,//非特定栏位
	eText_Pet_Equip_BagFull						= 99349,//背包已满

	eText_PetComPose_NorOne						= 99350,//当前副将已经被选择
	eText_PetComPose_None						= 99351,//选择副将不存在
	eText_PetComPose_Erro1						= 99352,//合成失败 未选择2个副将
	eText_PetComPose_Erro2						= 99353,//合成失败 选择副将不存在
	eText_PetComPose_Erro3						= 99354,//合成失败 选择副将处于出战状态
	eText_PetComPose_Erro4						= 99355,//合成失败 材料不足

	eText_Title_Sec								= 99356,//秒

	eText_PKMode_NonGuid						= 99357,

	eText_Char_PetInfo							= 99358,

	eText_Guild_SellItem						= 99359,

	eText_Bag_ShopMove							= 99360,
	eText_Bag_CKMove							= 99361,

	eText_ShopCenter_Jifen					     	= 99362, //积分商城
	eText_ShopCenter_Bangjin						= 99363, //绑金商城
	eText_ShopCenter_YuanBao						= 99364,//元宝商城
	eText_ShopCenter_All							= 99365, //全部
    eText_ShopCenter_Hot							= 99366, //热卖
	eText_ShopCenter_New							= 99367, //新品

	eText_PetEquipError								= 99368,//副将身上有装备 无法进行操作

	eText_GuildBattle_Secc							= 99369,//配对成功
	eText_GuildBattle_OneLose						= 99370,//%s公会参战人数过少 %s公会活动胜利
	eText_GuildBattle_TwoLose						= 99371,//%s公会和%s公会参战人数过时 战场自动结束
	eText_GuildBattle_Win							= 99372,//血战沙场胜利
	eText_GuildBattle_Lose							= 99373,//血战沙场失败

	eText_GuildChangeName_NotMaster					= 99374,//非公会会长可以改名
	eText_GuildChangeName_NonChange					= 99375,//公会名称无变化
	eText_GuildChangeName_Error						= 99376,//公会名称包含非法关键字
	eText_GuildChangeName_Error2					= 99377,//公会名称过短
	eText_GuildChangeName_Error3					= 99378,//公会名称过长
	eText_GuildChangeName_Error4					= 99379,//公会名称保护非法字符
	eText_RoleChangeName_Error						= 99380,//名称错误 请重新输入
	eText_GuildChangeName_Error5					= 99381,
	
	eText_PKEnterJianYu								= 99382,

	eClient_AddInfo_CampBattleDuel					= 99383,//战场不可以比武

	eClient_AddInfo_CurMapCantDuel					= 99384,//当前地图不能切磋
	eClient_AddInfo_CurZoomCantDuel					= 99385,//当前区域不能切磋
	eClient_AddInfo_EndTimeCountryTime				= 99386,

	eClient_FlyToMap_Stall							= 99387,//摆摊不可以传送
	eClient_CampBattle_Team							= 99388,//在战场不可以创建队伍
	eClient_PkValue_ADD								= 99389,//获得%d点PK值
	eClient_CountryRaiseItem						= 99390,//%s国 %s为国家捐献大量资金，获得募捐大礼包
	eClient_GuildRaiseItem							= 99391,//%s国 %s为公会捐献大量资金，获得募捐大礼包
	eClient_PkValue_Del								= 99392,//减少%d点PK值

	eClient_ClearTeam_NonTeamHeader					= 99393,
	eClient_ClearTeam_NonTeam						= 99394,
	eClient_ClearTeam_TeamMemberError				= 99395,
	eClient_ClearTeam_CD							= 99396,//您的操作过于,请在%s秒以后再次尝试!
	eClient_ClearTeam_TeamMemberSucc				= 99397,//副本重置成功!

	eText_Guild_NotEnoughMission					= 99398,//没有足够的使命点
	eText_Quest_Frozen								= 99399,//(已冻结)

	eText_QuestEntrust_TimeEndTitile				= 99400,
	eText_QuestEntrust_TimeEndContent				= 99401,

	eText_QuestEntrust_DelTitle						= 99402,
	eText_QuestEntrust_DelContent					= 99403,

	eText_QuestEntrust_SeccTitle					= 99404,
	eText_QuestEntrust_SeccContent					= 99405,

	eText_QuestEntrust_QuestIDError					= 99406,
	eText_QuestEntrust_NonEntrust					= 99407,
	eText_QuestEntrust_NonDel						= 99408,
	eText_QuestEntrust_NonCanel						= 99409,
	eText_QuestEntrust_Join							= 99410,
	eText_QuestEntrust_NonSec						= 99411,

	eText_AddQuestEntrust_NonQuest				    = 99412,
	eText_AddQuestEntrust_ErrorQuest				= 99413,
	eText_AddQuestEntrust_NonItem					= 99414,
	eText_AddQuestEntrust_ItemError					= 99415,

	eText_QuestEntrust_JoinBuff						= 99416,
	eText_QuestEntrust_JoinQuest					= 99417,

	eText_QuestEntrust_EndTimeLast					= 99418,

	eText_GuildGeneral_Secc_Title					= 99419,
	eText_GuildGeneral_Secc_Content					= 99420,

	eText_GuildGeneral_TimeToGameBattleStart		= 99421,
	eText_GuildGeneral_BullSystem_Enter				= 99422,
	eText_GuildGeneral_TimeToGameBattleEnd			= 99423,
	eText_GuildGeneral_BullSystem_Fight				= 99424,
	eText_GuildGeneral_BullSystem_Over				= 99425,
	eText_GuildGeneral_BattleResult					= 99426,

	eText_GuildGeneral_NonGuild						= 99427,
	eText_GuildGeneral_TimeError					= 99428,
	eText_GuildGeneral_TargetGuildNon				= 99429,
	eText_GuildGeneral_MissionError					= 99430,
	eText_GuildGeneral_GuildMoneyError				= 99431,
	eText_GuildGeneral_MoneyError					= 99432,
	eText_GuildGeneral_NotMaster					= 99433,
	eText_GuildGeneral_RewardError					= 99434,
	eText_GuildGeneral_MasterNotOnLine				= 99435,
	eText_GuildGeneral_AddBattleWorldInfo			= 99436,//%s %s 公会开战
	eText_AddGuildGeneralTip						= 99437,
	eText_GuildGeneral_CanelBattle					= 99438,//xx军团自认实力不济，向xx军团缴械投降
	eText_GuildGeneral_AddBattle					= 99439,//xx军团接受xx军团的挑战，双方会在星期x一决雌雄
	eText_GuildGeneral_AddBattleDel					= 99440,//对方拒绝挑战
	eText_GuildGeneral_AddBattleOK					= 99441,//对方接受挑战
	eText_GuildGeneralBattle_Name					= 99442,

	eText_QuestEntrust_NonMoney						= 99443,
	eText_QuestEntrust_NonStates					= 99444,

	eText_QuestEntrust_CancelError					= 99445,

	eText_FlyToPositionTip							= 99446,
	eText_FlyToPosition_TimeOut						= 99447,

	eText_Country_IncreaseGuildMoney				= 99448,//获得%d帮会资金
	eText_Country_DecreaseGuildMoney				 = 99449,//失去%d帮会资金

	eText_FlyToPositionTip_Country					= 99450,
	eText_FlyToPositionTip_Guild					= 99451,

	eText_QuestEntrust_JoinDoubleQuestError			= 99452,

	eText_Quest_IsSingleRequirement					= 99453,

	eText_QuestEntrust_NonMoneySum					= 99454,
	eText_QuestEntrust_QuestDrop					= 99455,

	eText_ChangeEquip_ErrorStates					= 99456,
	eText_AddRelationMarriageInfo					= 99457,

	eText_ThreeDay_Mail_Context						= 99458,
	eText_ThreeDay_Mail_Title						= 99459,
	eText_ThreeDay_Time								= 99460,

	eText_Country_NowGuildMoney						= 99461,

	eText_GuildMission_First_Title					= 99462,
	eText_GuildMission_First_Context				= 99463,

	eText_GuildMission_Two_Title					= 99464,
	eText_GuildMission_Two_Context					= 99465,

	eText_GuildMission_Three_Title					= 99466,
	eText_GuildMission_Three_Context				= 99467,

	eText_GuildMission_Non_Title					= 99468,
	eText_GuildMission_Non_Context					= 99469,

	eText_Guild_Del_Title							= 99470,
	eText_Guild_Del_Context							= 99471,

	eText_AutoAttack_OpenTeam_Profession			= 99472,

	eText_YuanBaoStates_Title						= 99473,
	eText_YuanBaoStates_Context						= 99474,

	eText_GuildGeneral_TargetMissionError			= 99475,
	eText_GuildGeneral_TargetGuildMoneyError		= 99476,
	eText_GuildGeneral_TargetMoneyError				= 99477,

	eClient_FlyToBattle_InTeam						= 99478,

	eText_GameGeneralBattle_BeginTimeStep			= 99479,
	eText_GameGeneralBattle_AddTimeError			= 99480,
	eText_Script_GuildCampBattlePoint_Rank			= 99481,//公会血战沙场积分排行榜的排名描述
	eText_GuildGeneral_Target_WriteMsg				= 99482,
	eText_GuildGaneral_TimeError					= 99483,

	eText_MountMoveStar_OleMountNull				= 99484,//源坐骑未设置
	eText_MountMoveStar_NewMountNull				= 99485,//新坐骑未设置
	eText_MountMoveStar_MountStarLevel				= 99486,//移星坐骑等级错误
	eText_MountMoveStar_MoneyError					= 99487,//金钱不足
	eText_MountMoveStar_ItemError					= 99488,//材料不足
	eText_MountMoveStar_SetMountError				= 99489,//设置坐骑 需要先取消已经选择的坐骑

	eText_MountMoveStar_NewMountActionError			= 99490,
	eText_MountMoveStar_OldMountActionError			= 99491,


	eText_EpistarPointSucc							= 99492,//晶元点添加成功
	eText_EpistarPointError							= 99493,//晶元点添加失败
	eLogin_ServerFull								= 99494,//服务器爆满

	eText_MountMoveStar_OneMount					= 99495,//源坐骑和目标坐骑为同一坐骑 不可以移星
	eText_MountMoveStar_Level						= 99496,//源坐骑等级 小于等于 目标坐骑的等级 不可以移星
	eText_MountMoveStar_NewMountError				= 99497,//目标坐骑无法强化 不可以移星
	eText_MountMoveStar_OldMountError				= 99498,//源坐骑无法强化 不可以移星

	eText_QuestEnterst_QuestStates					= 99499,

	eText_Guild_GameBattleCD						= 99500,
	eText_Guild_GameBattleExites					= 99501,

	eText_PurpleMaterialBound						= 99502,
	eText_RepurpleMaterialBound						= 99503,
	eText_EquipMaterialBound						= 99504,

	eText_GuildMember_OnLineNull					= 99505,
	eText_GuildMember_OnLineTime					= 99506,

	eText_PlayerPoint_Add_Info						= 99507,//
	eText_PlayerPoint_Del_Info						= 99508,
	eText_PlayerPoint_Set_Info						= 99509,

	eText_PlayerPoint_Info_Guild					= 99510,//
	eText_PlayerPoint_Info_Player					= 99511,
	eText_PlayerPoint_Info_Country					= 99512,

	eText_PetComPose_Equip							= 99513,
	eText_GetSalary_CD								= 99514,
	eText_PetCompose_LevelMessage					= 99515,
	eText_Login_MacFull								= 99516,
	eLogin_PassWordCard								= 99517,		// 验证用户
	etext_Login_PwdCardError						= 99518,
	eText_MountMoveLevel_Success					= 99519,//坐骑移星成功 当前等级为%d
	eText_Pet_MaxSavvy								= 99520,//副将悟性已经到最高等级 无法强化
	eText_Pet_WorldInfo								= 99521,//%s将副将%s的悟性强化到%d
	eMaxText
};

class Name
{
public:
	Name();
public:
	~Name();
};
