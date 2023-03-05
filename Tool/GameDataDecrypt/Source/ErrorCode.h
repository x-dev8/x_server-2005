#ifndef __ERRORCODE_H__
#define __ERRORCODE_H__

// ������������ö��
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
    ER_GameServerNotExist,      // ��Ϸ��ͼ������������
    ER_ServerIsBusy,
    ER_SqlServiceFail,
    ER_NewPoolFail,             // �ӳ���Newʧ��
    ER_NewNormalFail,           // ��ͨ��Newʧ��

    ER_JustForQueryHelp = 5000,
    ER_Log4CppInitFail,

    ER_EnterWorldQueue,                // ��¼��Ϸ�Ŷ�
    ER_EnterWorldRequstDataBusy,       // �������ݷ�æ
    ER_EnterDatabaseBusy,              // DataServer��æ
    ER_EnterWorldDbSqlException, 
    ER_EnterWorldInColdDown,           // �����½��Ϣ��CoolDown��
    ER_EnterWorldSwitchStageTypeError, // ���������Ϸ�������ʹ���

    ER_LocusGameServerNotExit,          // ���ڵķ�����������

    ER_CharacterServerCantBeGameServer, // CharacterServer������ΪGameServer
    ER_CharacterServerPlayerIsFull,     // CharacterServer�������Ѿ���
    ER_CharacterServerNotExit,          // CharacterServer������

    ER_CorrectMapGameServerNotExist,    // ������Ŀ���ͼ��Ϸ������������
    ER_ErrorTargetMapGameServerId,      // �����Ŀ���ͼ��Ϸ������Id

    ER_AddLoginClientPeerFail,          // ��ӵ�¼�û�ʧ��
    ER_ClientPeerNewFail,               // ClientPeer New ʧ��

    ER_TargetNotActiveMount,            // Ŀ��û�м��������
    ER_ClientPeerNotExist,              // ClientPeer������
    ER_SuccessBreak,                    // �ɹ���Break�˳�
    ER_ChangeJinDingFail,               // �һ���ʧ��
    ER_JinDingOperateFail,              // �𶧲���ʧ��
    ER_ExchangeJinDingLevelLow,         // 

    ER_ItemConfigNotExist,              // ��Ʒ���ò�����
    ER_SplitItemNotExist,               // �������Ʒ������
    ER_SplitItemIndexGuidError,         // �������Ʒλ����ָguid����
    ER_SplitItemTypeError,              // �������Ʒ���ʹ���
    ER_SplitItemCantBeSplit,            // �������Ʒ���ɱ����
    ER_SplitItemLevelError,             // �������Ʒ�ȼ�����
    ER_SplitItemLevelMulError,          // �������Ʒ�ȼ���������
    ER_SplitItemQualityLevelError,      // �������ƷƷ�ʵȼ�����
    ER_SplitItemProductNotExit,         // �������Ʒ�����ﲻ����
    ER_SplitItemCreateFail,             // ��ִ���ʧ��
    ER_SplitItemPopFail,                // ���popʧ��
    ER_SplitItemPushFail,               // ���pushʧ��
    ER_SplitItemConfigNotExist,         // �������Ʒ������Ϣ������

    ER_SQLConnectionReset,              // sql��������
    ER_CharNameHaveExist,
    ER_CharSlotFull,
    ER_ChangeNameItemNotExist,

    ER_XinShouCardAbout,         // ���ֿ�         ( û�� 0, ����� 11, �� 22            )
    ER_17173CardAbout,           // 17173��Ȩ��    ( û�� 0, ����� 11, �� 22            )
    ER_ZhiZunCardLevelAbout,     // ���𿨵ȼ�     ( û�� 0, ����� 11, 1, 2, 3, 4, 5 ,6 )
    ER_ZhiZunVipGiftAbout,       // ����Vip�����  ( û�� 0, ����� 11, 1, 2, 3, 4, 5 ,6 )
    ER_HuiGuiGiftAbout,          // ����һع���� ( û�� 0, ����� 11, 1, 2             )
    ER_ChongZhiGiftAbout,        // ��ֵ�������   ( û�� 0, ����� 11, 1, 2, 3, 4, 5    )
    ER_ChongZhiBackGiftAbout,    // �����ͳ�ֵ�����ȼ��� ( û�� 0, ����� 11, 1, 2, 3, 4       )

    ER_NotActiveMount = 6000,           // û�м��������
    ER_NotEnoughEnjoyment,              // ������������
    ER_NotHaveThisMount,                // �Ҳ���ָ������������ 

    ER_OrganizeMaxMemberLimit,          // ��֯��Ա�����������
    ER_OrganizeHaveExist,               // ����֯�Ѿ�����
    ER_OrganizeMemberNotExist,          // ��֯���޴˳�Ա
    ER_OrganizeNotExist,                // ��֯������
    ER_OrganizeMemberHaveExist,         // ��֯�˳�Ա�Ѿ�����
    ER_OrganizeRightNotEnough,          // Ȩ�޲���
    ER_TargetOrganizeHaveExist,         // �Է���֯�����Ѿ�����
    ER_TargetHaveInTheSameOrganize,     // �Է��Ѿ����Լ�����֯����
    ER_TargetCannotIsSelf,              // ���������Լ�
    ER_IsNotMaster,                     // ���ǰ���
    ER_IsNotViceMaster,                 // ���Ǹ����� 
    ER_IsNotTongMaster,                 // ��������
    ER_TargetPostionError,              // Ŀ��ְλ����
    ER_TongMemberCountLimit,            // ����������
    ER_TongCountLimit,                  // ��������
    ER_IsNotTheSameTong,                // ��ͬ��
    ER_TongIdError,                     // ��Id����
    ER_InFightNotActiveMount,           // ����ս��״̬�޷���ս
    ER_InDeadNotActiveMount,            // ����״̬�޷���ս
    ER_InMountConfigNotExist,           // �������ò�����
    ER_MountTakeLevelNotEnough,         // Я������ĵȼ�����
    ER_HaveCapturePet,                  // �Ѿ��в������
    ER_CaptureTargetInvalid,            // ����Ŀ����Ч
    ER_CaptureFail,                     // �������ʧ��
    ER_TargetPkValueFail,               // pkֵ������Ҫ��
    ER_BeReliveTimeOver,                // ���������Чʱ�����    

    ER_ActionHighFrequency,             // ��Ϊ̫Ƶ��
    ER_TakeMoneyCorrect,                // Я����Ǯ������
    ER_StorageMoneyCorrect,             // �ֿ��Ǯ������
    ER_JiFengGainNotItem,               // û�п�����ȡ�Ļ��ֵ���
    ER_JiFengGainSuccess,               // ���ֵ�����ȡ�ɹ�

    ER_InProtectLevel = 7000,           // ��PK�����ȼ��ڲ���PK
    ER_LessPrivateShopLevel,            // �ȼ�����15��,���ܰ�̯
    ER_ActiveMountCanNotTrade,          // ��ս�����ﲻ�ܽ���
    ER_MountCantLearnSkill,             // �޷�ѧϰ�˼���
    ER_HighShoutTimeLimitFail,          // ���纰��ʱ������
    ER_HighShoutNotEnoughMoney,         // ���纰��û���㹻��Ǯ
    ER_HighShoutTimeLimitSuccess,       // �����ɹ�ֻ����ʱ��
    ER_InProtectLockTime,               // ��ȫ������ʱ��
    ER_TeamMemberMustHaveQuest,         // ������ĳĳĳû�д�����
    ER_TeamMemberAlreadyEntryMap,       // ������ĳĳĳ�����Ѿ��������ͼ�� 
    ER_BanSpeakTime,                    // ���ѱ������˶���ʱ��
    ER_InMyBlacklist,                   // ���Լ���������
    ER_InOtherBlacklist,                // �ڶԷ���������
    ER_LeaveStage,                      // �뿪����

    ER_SessionKeyOverTime,              // SessionKey����
    ER_MoneyItemExchangePopFail,
    ER_IsLocked,                        // ��Ʒ����ס,�޷����д˲���
    ER_PrivateShopItemError,            // ����۵���Ʒ��Ϣ����ȷ�� ����������̯�̣�

    ER_SelfMaxMoneyLimit,               // �Լ�������Ǯ�ܶ������
    ER_TargetMaxMoneyLimit,             // �Է���Ǯ�ܶ������

    ER_MaleLevelLimit,                  // �з���������%d��������ȡ�������
    ER_MaleLevelLimit1,                 // �з���������%d�����ܽ��
    ER_MaleLevelLimit2,                 // �з���������%d�����ܿ������ĵ�
    ER_FemaleLevelLimit,                // �Է�����ΪŮ��,�Ҳ�����%d��
    ER_MustHaveTeam,                    // ˫�������ڶ����в��ܽ��
    ER_MustBeTeamHeader,                // �з������Ƕ���Ķӳ�
    ER_OnlyTwoTeamMember,               // ������ֻ����˫��������
    ER_TargetMustInTeam,                // ˫���������ҽ��к��ѹ�ϵ
    ER_SelfAlreadyHaveMarriage,         // ���Ѿ�����ż��
    ER_OnlyFriend,                      // ˫���������ҽ��к��ѹ�ϵ
    ER_FriendlyLimit,                   // ˫�����ѶȲ���%d��
    ER_MustInArea,                      // �Է�������������
    ER_TargetAlreadyHaveMarriage,       // �Է��Ѿ�����ż��
    ER_CreateMustBeMarriage,            // �����Ƿ��޲��ܿ������쳡��
    ER_MarriageStageCountLimit,         // ���쳡���Ѿ��ﵽ�����
    ER_CreateMarriageStageFailed,       // ���쳡������ʧ��, ������
    ER_MarriageStageNotExist,           // ���쳡����δ���� ���� �Ѿ��ر� 
    ER_MarriageStageAlreadyExist,       // ���쳡���Ѿ�����
    ER_MarriageMustInTeam,              // �����ż���������ͬһ�����в�����ȡ����

    ER_IsInOpenPrivateShop,             // ��̯״̬�޷�����
    ER_IsBargainingNow,                 // �����в��ܰ�̯

    ER_MailCreateIdFail,                // �ʼ�����Idʧ��
    ER_MailAddFail,                     // �ʼ�����������ʧ��
    ER_MailCountLimit,                  // �ʼ���������
    ER_MailNotExit,                     // �ʼ�������
    ER_MailCannotDelete,                // �ʼ��޷�ɾ��
    ER_MailProcessing,                  // ���ʼ��ڴ�����
    ER_MailTargetQueryFail,             // �ʼ�Ŀ���ѯʧ��
    ER_MailItemHaveGet,                 // �ʼ���Ʒ�Ѿ����

    ER_LeaveGuildTimeLimit,             // һ��ֻ�ܼ���һ�ι���

    ER_AlreadyMaxMasterLevel,           // �Ѿ������ʦ�ŵȼ���
    ER_HaveNotGraduateMaster,           // �㻹δ��ɳ�ʦ����
    ER_NotEnoughMasterValue,            // �������ֵ����

    ER_MustBeMarriageCanFly,            // ֻ�з��޹�ϵ����ʹ�ô˷��е���
    ER_ItemFlyNotOnline,                // �Է�������, ʹ�÷��е���ʧ�� 

    ER_RemoveRelationNeedMoney,         // ɾ��ʦͽ��ϵ��Ҫ%d��Ǯ( �����Ǯ��value �� )
    ER_AddStudentMustInArea,            // ��ʦ��ͽ������%d�׷�Χ��
    ER_StudentMinLevelLimit,            // ͽ�ܵȼ����ܵ���%d��
    ER_StudentMaxLevelLimit,            // ͽ�ܵȼ����ܳ���%d��
    ER_StudentMinLevelSpan,             // ʦͽ�ȼ����ܵ���%d��
    ER_GraduateMasterMustInTeam,        // ʦ�������ڶ����в��ܳ�ʦ
    ER_GraduateMasterMustInArea,        // ʦ��������%d�׷�Χ�ڲ��ܳ�ʦ

    ER_UseItemMustInArea,               // �Է�������%d�׷�Χ�ڲ���ʹ��
    ER_UseItemOnlyFriend,               // ˫�����Ǻ��Ѳſ�ʹ����Ʒ
    ER_UseItemToFriendTimeLimit,        // һ������һ��ֻ������һ�κ��Ѷ�
    ER_UseItemToFriendCountLimit,       // һ��ֻ�ܸ�%d���������ͺ��Ѷ�

    ER_ReceiveFriendlyQuestMustHaveTeam, // ������Ӳ��ܽӺ��Ѷ�����
    ER_ReceiveFriendlyQuestOnlyTwoMember, // ������ֻ����2���˲��ܽӺ��Ѷ�����
    ER_ReceiveFriendlyQuestMustFriend,    // �����еĳ�Ա�����Ǻ��Ѳ��ܽӺ��Ѷ�����
    ER_ReceiveFriendlyCountLimit,         // ͬһ������һ��ֻ�ܽ�һ�κ��Ѷ�����
    ER_HaveChangeMosterIdBuffNotShop,     // ӵ�б���״̬buff���ܰ�̯  

    ER_WaitNextTeamBattle,                // �������鲻��3�� ��ȴ���һ�α���
    ER_LevelErrorEnterTeamBattle,         // ��ȼ��������ܽ���ս��
    ER_PrivateChatLevelLimit,             // �Է�С��%d��,�޷��յ����˽����Ϣ
    ER_CallNpcScriptFailDistance,         // ����Npc�ű�ʧ�ܾ���
    ER_CreateFileFail = 8000,
    ER_CreateFileMappingFail,

    ER_ErrorMountData,                  // �����������
    ER_MaxPubQuestCount,                // �ƹ��������ֻ��ͬʱ��5��
    ER_MapViewOfFileFail,
    ER_SqlNotConnected,
    ER_MaxConQuestCount,                // �����������ֻ��ͬʱ��3��
    ER_SelfMaxJiaoZiLimit,              // �Լ����������ܶ������
    ER_ErrorMountPotential,             // ����Ǳ����������
    ER_CannotChangePKMode,              // PKֵ����0,�޷��л�������ģʽ
    ER_ChangePKModeOften,               // Ƶ���л�PKģʽ
    ER_PKModeCriticalNoTimer,           // ��ģʽ30����ʱ��δ��
    ER_PKModeCriticalNotShop,           // ��ģʽ���ܰ�̯ 
    ER_NoExpToLevelUp,                  // ���鲻���޷�����
    ER_NoLevelToLearnSkill,             // �ȼ������޷�ѧϰ����
    ER_NoMoneyToLearnSkill,             // ��Ǯ�����޷�ѧϰ����
    ER_NoExpToLearnSkill,               // ���鲻���޷�ѧϰ����
    ER_NoMoneyToMountRestore,           // ��Ǯ�����޷���������
    ER_ErrorMountMasterLevel,           // ���ﷱֳ������ȼ�С��60��
    ER_ErrorMountMasterMoney,           // ���ﷱֳ��Ǯ����
    ER_ErrorMountCannotBreed,           // �����޷����з�ֳ
    ER_ErrorMountNoNextId,              // �޷��������ﷱֳ��������û����һ����
    ER_ErrorMountSkillNumber,           // �Ѿ��������ܲ�
    ER_ErrorMountSkillForget,           // ����λ��û�м���
    ER_NoPointToLearnSkill,             // �����Ȳ����޷���������
    ER_CanLearnMoreRecipeSkill,         // ���������
    ER_MountLevelIsOverPlayer5,         // ����ȼ���������ȼ�5�����޷����Ӿ���
    ER_HookLevelNotHas,                 // �һ����δ���
    ER_NoMoneyGetHookExp,               // ��Ǯ�����޷���ȡ����
    ER_MountLevelCannotUseItem,         // ����ȼ������޷�ʹ�õ���
    ER_ErrorMountHuanTongShuLevel,      // ����Я���ȼ�С��40���޷�ʹ�û�ͯ��
    ER_ErrorMountHuanLongShuLevel,      // ����Я���ȼ�С��80���޷�ʹ�û�����
    ER_MountCannotUseHuanLongShu ,      // �������޷�ʹ�û�����
    ER_EquipPressKeySuit,               // û�и�һ����װ������
    ER_HonourTopLimit,                  // ��������ֵ�ﵽ����
    ER_NoOfflineHookExp,                // û�����߹һ�����
    ER_OfflineHookLevel,                // ���߹һ��ȼ�����
    ER_NoMoneyReliveOrigin,             // ��Ǯ�����޷�ԭ�ظ���
    ER_MountTypeCannotBreed,            // �������Ͳ�ͬ�޷����з�ֳ
    ER_ActiveMountStorage,              // ��ս�����޷�����ֿ�
    ER_GetStorageMountFail,             // �ֿ������޷�������������
    ER_ReelMountTakeLevel,              // ����Я���ȼ����� �޷�ѧϰ����
    ER_ReelMountLevel,                  // ����ȼ����� �޷�ѧϰ����
    ER_ReelMountPreSkill,               // �޷�ѧϰ���＼��
    ER_ErrorMountHuanTongShu,           // ���������޷�ʹ�û�ͯ��

    ER_BuyGoodsNoJiaoZi,                // ���Ӳ����޷�����
    ER_BuyGoodsNoMoney,                 // ��Ǯ�����޷�����
    ER_SellItemReclaim,                 // �޷�����,�뵽ׯ��������л���
};

enum ESubResult
{
    ESR_NotExist     = 0,  // ������
    ESR_HaveGet      = 11, // �����
    ESR_Have         = 22, // ��
    ESR_ResourceFail = 23, // ��Դ����
    ESR_BagFull      = 24,
};

#endif
