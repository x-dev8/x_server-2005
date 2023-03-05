#ifndef __ERRORCODE_H__
#define __ERRORCODE_H__

// 函数返回类型枚举
enum EResult
{
    ER_Success,
    ER_Failed,
    ER_SystemException,
    ER_FileNotFound,
    ER_DirectoryNotExist,
    ER_ArgumentError,
    ER_ArgumentNull,
    ER_ArgumentOutOfRange,
    ER_IndexOutOfRange,
    ER_NullReference,
    ER_TypeError,
    ER_ParamterError,
    ER_IdOutMaxRange,
    ER_NullPointer,

    ER_MessageLengthError = 1000,
    ER_CreateWorkThreadFail,

    ER_InitFail,
    ER_LoadFileError,

    ER_MapCfgNotFound,
    ER_NotInTransportRegion,
    ER_NotTargetTransportRegion,

    //Net Message
    ER_MapGameServerPlayerIsFull,
    ER_NotGateServer,
    ER_NotCanUseGameServer,
    ER_ThisAccountHaveInPlayer,
    ER_GameServerNotExist,      // 游戏地图服务器不存在
    ER_ServerIsBusy,
    ER_SqlServiceFail,
    ER_NewPoolFail,             // 从池中New失败
    ER_NewNormalFail,           // 普通的New失败

    ER_JustForQueryHelp = 5000,
    ER_Log4CppInitFail,

    ER_EnterWorldQueue,                // 登录游戏排队
    ER_EnterWorldRequstDataBusy,       // 请求数据繁忙
    ER_EnterDatabaseBusy,              // DataServer繁忙
    ER_EnterWorldDbSqlException, 
    ER_EnterWorldInColdDown,           // 请求登陆消息在CoolDown中
    ER_EnterWorldSwitchStageTypeError, // 请求进入游戏世界类型错误

    ER_LocusGameServerNotExit,          // 所在的服务器不存在

    ER_CharacterServerCantBeGameServer, // CharacterServer不能作为GameServer
    ER_CharacterServerPlayerIsFull,     // CharacterServer的人数已经满
    ER_CharacterServerNotExit,          // CharacterServer不存在

    ER_CorrectMapGameServerNotExist,    // 纠正的目标地图游戏服务器不存在
    ER_ErrorTargetMapGameServerId,      // 错误的目标地图游戏服务器Id

    ER_AddLoginClientPeerFail,          // 添加登录用户失败
    ER_ClientPeerNewFail,               // ClientPeer New 失败

    ER_TargetNotActiveMount,            // 目标没有激活的坐骑
    ER_ClientPeerNotExist,              // ClientPeer不存在
    ER_SuccessBreak,                    // 成功并Break退出
    ER_ChangeJinDingFail,               // 兑换金锭失败
    ER_JinDingOperateFail,              // 金锭操作失败
    ER_ExchangeJinDingLevelLow,         // 

    ER_ItemConfigNotExist,              // 物品配置不存在
    ER_SplitItemNotExist,               // 被拆分物品不存在
    ER_SplitItemIndexGuidError,         // 被拆分物品位置所指guid错误
    ER_SplitItemTypeError,              // 被拆分物品类型错误
    ER_SplitItemCantBeSplit,            // 被拆分物品不可被拆分
    ER_SplitItemLevelError,             // 被拆分物品等级错误
    ER_SplitItemLevelMulError,          // 被拆分物品等级倍数错误
    ER_SplitItemQualityLevelError,      // 被拆分物品品质等级错误
    ER_SplitItemProductNotExit,         // 被拆分物品产出物不存在
    ER_SplitItemCreateFail,             // 拆分创建失败
    ER_SplitItemPopFail,                // 拆分pop失败
    ER_SplitItemPushFail,               // 拆分push失败
    ER_SplitItemConfigNotExist,         // 被拆分物品配置信息不存在

    ER_SQLConnectionReset,              // sql连接重置
    ER_CharNameHaveExist,
    ER_CharSlotFull,
    ER_ChangeNameItemNotExist,

    ER_XinShouCardAbout,         // 新手卡         ( 没有 0, 领过了 11, 有 22            )
    ER_17173CardAbout,           // 17173特权卡    ( 没有 0, 领过了 11, 有 22            )
    ER_ZhiZunCardLevelAbout,     // 至尊卡等级     ( 没有 0, 领过了 11, 1, 2, 3, 4, 5 ,6 )
    ER_ZhiZunVipGiftAbout,       // 至尊Vip卡礼包  ( 没有 0, 领过了 11, 1, 2, 3, 4, 5 ,6 )
    ER_HuiGuiGiftAbout,          // 老玩家回归礼包 ( 没有 0, 领过了 11, 1, 2             )
    ER_ChongZhiGiftAbout,        // 冲值返还礼包   ( 没有 0, 领过了 11, 1, 2, 3, 4, 5    )
    ER_ChongZhiBackGiftAbout,    // 多冲多送冲值返还等级段 ( 没有 0, 领过了 11, 1, 2, 3, 4       )

    ER_NotActiveMount = 6000,           // 没有激活的坐骑
    ER_NotEnoughEnjoyment,              // 坐骑生命不够
    ER_NotHaveThisMount,                // 找不到指定索引的坐骑 

    ER_OrganizeMaxMemberLimit,          // 组织成员最大人数限制
    ER_OrganizeHaveExist,               // 此组织已经存在
    ER_OrganizeMemberNotExist,          // 组织中无此成员
    ER_OrganizeNotExist,                // 组织不存在
    ER_OrganizeMemberHaveExist,         // 组织此成员已经存在
    ER_OrganizeRightNotEnough,          // 权限不够
    ER_TargetOrganizeHaveExist,         // 对方组织公会已经存在
    ER_TargetHaveInTheSameOrganize,     // 对方已经在自己的组织公会
    ER_TargetCannotIsSelf,              // 对象不能是自己
    ER_IsNotMaster,                     // 不是帮主
    ER_IsNotViceMaster,                 // 不是副帮主 
    ER_IsNotTongMaster,                 // 不是堂主
    ER_TargetPostionError,              // 目标职位不对
    ER_TongMemberCountLimit,            // 堂人数限制
    ER_TongCountLimit,                  // 堂数限制
    ER_IsNotTheSameTong,                // 不同堂
    ER_TongIdError,                     // 堂Id出错
    ER_InFightNotActiveMount,           // 正在战斗状态无法出战
    ER_InDeadNotActiveMount,            // 死亡状态无法出战
    ER_InMountConfigNotExist,           // 坐骑配置不存在
    ER_MountTakeLevelNotEnough,         // 携带坐骑的等级不够
    ER_HaveCapturePet,                  // 已经有捕获怪了
    ER_CaptureTargetInvalid,            // 捕获目标无效
    ER_CaptureFail,                     // 捕获宠物失败
    ER_TargetPkValueFail,               // pk值不符合要求
    ER_BeReliveTimeOver,                // 被复活的有效时间过了    

    ER_ActionHighFrequency,             // 行为太频繁
    ER_TakeMoneyCorrect,                // 携带金钱被纠正
    ER_StorageMoneyCorrect,             // 仓库金钱被纠正
    ER_JiFengGainNotItem,               // 没有刻意领取的积分道具
    ER_JiFengGainSuccess,               // 积分道具领取成功

    ER_InProtectLevel = 7000,           // 在PK保护等级内不能PK
    ER_LessPrivateShopLevel,            // 等级低于15级,不能摆摊
    ER_ActiveMountCanNotTrade,          // 出战的坐骑不能交易
    ER_MountCantLearnSkill,             // 无法学习此技能
    ER_HighShoutTimeLimitFail,          // 世界喊话时间限制
    ER_HighShoutNotEnoughMoney,         // 世界喊话没有足够的钱
    ER_HighShoutTimeLimitSuccess,       // 喊话成功只更新时间
    ER_InProtectLockTime,               // 安全锁保护时间
    ER_TeamMemberMustHaveQuest,         // 队伍中某某某没有此任务
    ER_TeamMemberAlreadyEntryMap,       // 队伍中某某某今天已经进入过地图了 
    ER_BanSpeakTime,                    // 你已被禁言了多少时间
    ER_InMyBlacklist,                   // 在自己黑名单中
    ER_InOtherBlacklist,                // 在对方黑名单中
    ER_LeaveStage,                      // 离开场景

    ER_SessionKeyOverTime,              // SessionKey过期
    ER_MoneyItemExchangePopFail,
    ER_IsLocked,                        // 物品被锁住,无法进行此操作
    ER_PrivateShopItemError,            // 你出售的物品信息不正确， 请重新整理摊铺！

    ER_SelfMaxMoneyLimit,               // 自己超过金钱总额超过限制
    ER_TargetMaxMoneyLimit,             // 对方金钱总额超过限制

    ER_MaleLevelLimit,                  // 男方必须满足%d级才能领取结婚任务
    ER_MaleLevelLimit1,                 // 男方必须满足%d级才能结婚
    ER_MaleLevelLimit2,                 // 男方必须满足%d级才能开启爱心岛
    ER_FemaleLevelLimit,                // 对方必须为女性,且不低于%d级
    ER_MustHaveTeam,                    // 双方必须在队伍中才能结婚
    ER_MustBeTeamHeader,                // 男方必须是队伍的队长
    ER_OnlyTwoTeamMember,               // 队伍中只能有双方两个人
    ER_TargetMustInTeam,                // 双方必须有且仅有好友关系
    ER_SelfAlreadyHaveMarriage,         // 你已经有配偶了
    ER_OnlyFriend,                      // 双方必须有且仅有好友关系
    ER_FriendlyLimit,                   // 双方好友度不足%d点
    ER_MustInArea,                      // 对方必须在你的身边
    ER_TargetAlreadyHaveMarriage,       // 对方已经有配偶了
    ER_CreateMustBeMarriage,            // 必须是夫妻才能开启婚庆场景
    ER_MarriageStageCountLimit,         // 婚庆场景已经达到最大数
    ER_CreateMarriageStageFailed,       // 婚庆场景创建失败, 请重试
    ER_MarriageStageNotExist,           // 婚庆场景尚未开启 或者 已经关闭 
    ER_MarriageStageAlreadyExist,       // 婚庆场景已经存在
    ER_MarriageMustInTeam,              // 你的配偶必须和你在同一队伍中才能领取任务

    ER_IsInOpenPrivateShop,             // 摆摊状态无法交易
    ER_IsBargainingNow,                 // 交易中不能摆摊

    ER_MailCreateIdFail,                // 邮件创建Id失败
    ER_MailAddFail,                     // 邮件加入容器中失败
    ER_MailCountLimit,                  // 邮件个数性质
    ER_MailNotExit,                     // 邮件不存在
    ER_MailCannotDelete,                // 邮件无法删除
    ER_MailProcessing,                  // 有邮件在处理中
    ER_MailTargetQueryFail,             // 邮件目标查询失败
    ER_MailItemHaveGet,                 // 邮件物品已经获得

    ER_LeaveGuildTimeLimit,             // 一天只能加入一次公会

    ER_AlreadyMaxMasterLevel,           // 已经是最大师门等级了
    ER_HaveNotGraduateMaster,           // 你还未完成出师任务
    ER_NotEnoughMasterValue,            // 你的威望值不够

    ER_MustBeMarriageCanFly,            // 只有夫妻关系才能使用此飞行道具
    ER_ItemFlyNotOnline,                // 对方不在线, 使用飞行道具失败 

    ER_RemoveRelationNeedMoney,         // 删除师徒关系需要%d金钱( 具体金钱在value 中 )
    ER_AddStudentMustInArea,            // 拜师收徒必须在%d米范围内
    ER_StudentMinLevelLimit,            // 徒弟等级不能低于%d级
    ER_StudentMaxLevelLimit,            // 徒弟等级不能超过%d级
    ER_StudentMinLevelSpan,             // 师徒等级相差不能低于%d级
    ER_GraduateMasterMustInTeam,        // 师傅必须在队伍中才能出师
    ER_GraduateMasterMustInArea,        // 师傅必须在%d米范围内才能出师

    ER_UseItemMustInArea,               // 对方必须在%d米范围内才能使用
    ER_UseItemOnlyFriend,               // 双方都是好友才可使用物品
    ER_UseItemToFriendTimeLimit,        // 一个好友一天只能赠送一次好友度
    ER_UseItemToFriendCountLimit,       // 一天只能给%d个好友赠送好友度

    ER_ReceiveFriendlyQuestMustHaveTeam, // 必须组队才能接好友度任务
    ER_ReceiveFriendlyQuestOnlyTwoMember, // 队伍中只能有2个人才能接好友度任务
    ER_ReceiveFriendlyQuestMustFriend,    // 队伍中的成员必须是好友才能接好友度任务
    ER_ReceiveFriendlyCountLimit,         // 同一个好友一天只能接一次好友度任务
    ER_HaveChangeMosterIdBuffNotShop,     // 拥有变身状态buff不能摆摊  

    ER_WaitNextTeamBattle,                // 报名队伍不满3队 请等待下一次报名
    ER_LevelErrorEnterTeamBattle,         // 你等级不够不能进入战场
    ER_PrivateChatLevelLimit,             // 对方小于%d级,无法收到你的私聊消息
    ER_CallNpcScriptFailDistance,         // 调用Npc脚本失败距离
    ER_CreateFileFail = 8000,
    ER_CreateFileMappingFail,

    ER_ErrorMountData,                  // 错误的马数据
    ER_MaxPubQuestCount,                // 酒馆任务最多只能同时接5个
    ER_MapViewOfFileFail,
    ER_SqlNotConnected,
    ER_MaxConQuestCount,                // 征伐任务最多只能同时接3个
    ER_SelfMaxJiaoZiLimit,              // 自己超过交子总额超过限制
    ER_ErrorMountPotential,             // 坐骑潜力点分配错误
    ER_CannotChangePKMode,              // PK值大于0,无法切换到其他模式
    ER_ChangePKModeOften,               // 频繁切换PK模式
    ER_PKModeCriticalNoTimer,           // 狂暴模式30分钟时限未到
    ER_PKModeCriticalNotShop,           // 狂暴模式不能摆摊 
    ER_NoExpToLevelUp,                  // 经验不足无法升级
    ER_NoLevelToLearnSkill,             // 等级不足无法学习技能
    ER_NoMoneyToLearnSkill,             // 金钱不足无法学习技能
    ER_NoExpToLearnSkill,               // 经验不足无法学习技能
    ER_NoMoneyToMountRestore,           // 金钱不足无法治疗坐骑
    ER_ErrorMountMasterLevel,           // 坐骑繁殖主坐骑等级小于60级
    ER_ErrorMountMasterMoney,           // 坐骑繁殖金钱不足
    ER_ErrorMountCannotBreed,           // 坐骑无法进行繁殖
    ER_ErrorMountNoNextId,              // 无法进行坐骑繁殖，主坐骑没有下一代马
    ER_ErrorMountSkillNumber,           // 已经开启技能槽
    ER_ErrorMountSkillForget,           // 所在位置没有技能
    ER_NoPointToLearnSkill,             // 熟练度不足无法提高生活技能
    ER_CanLearnMoreRecipeSkill,         // 生活技能已满
    ER_MountLevelIsOverPlayer5,         // 坐骑等级高于人物等级5级，无法增加经验
    ER_HookLevelNotHas,                 // 挂机档次错误
    ER_NoMoneyGetHookExp,               // 金钱不足无法领取经验
    ER_MountLevelCannotUseItem,         // 坐骑等级不足无法使用道具
    ER_ErrorMountHuanTongShuLevel,      // 坐骑携带等级小于40级无法使用还童书
    ER_ErrorMountHuanLongShuLevel,      // 坐骑携带等级小于80级无法使用还龙书
    ER_MountCannotUseHuanLongShu ,      // 该坐骑无法使用还龙书
    ER_EquipPressKeySuit,               // 没有该一键换装的设置
    ER_HonourTopLimit,                  // 今日荣誉值达到上限
    ER_NoOfflineHookExp,                // 没有离线挂机经验
    ER_OfflineHookLevel,                // 离线挂机等级不足
    ER_NoMoneyReliveOrigin,             // 金钱不足无法原地复活
    ER_MountTypeCannotBreed,            // 坐骑类型不同无法进行繁殖
    ER_ActiveMountStorage,              // 出战坐骑无法放入仓库
    ER_GetStorageMountFail,             // 仓库坐骑无法放入坐骑栏中
    ER_ReelMountTakeLevel,              // 坐骑携带等级不足 无法学习技能
    ER_ReelMountLevel,                  // 坐骑等级不足 无法学习技能
    ER_ReelMountPreSkill,               // 无法学习坐骑技能
    ER_ErrorMountHuanTongShu,           // 变异坐骑无法使用还童书

    ER_BuyGoodsNoJiaoZi,                // 交子不足无法购买
    ER_BuyGoodsNoMoney,                 // 金钱不足无法购买
    ER_SellItemReclaim,                 // 无法卖出,请到庄回那里进行回收
};

enum ESubResult
{
    ESR_NotExist     = 0,  // 不存在
    ESR_HaveGet      = 11, // 领过了
    ESR_Have         = 22, // 有
    ESR_ResourceFail = 23, // 资源错误
    ESR_BagFull      = 24,
};

#endif
