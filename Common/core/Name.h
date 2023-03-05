#pragma once

enum eName
{

	//==================���ַ�������=========================================================

	eLogin_UserPassError             = 0,    //�û����������
	eLogin_VersionError              = 1,    //�汾����
	eLogin_UseOnline                 = 2,        //���û�����
	eLogin_UnKnown                   = 3,            //δ֪
	eCreate_PlayerNameSame           = 4,    //�û�������
	eDeletePlayerFail                = 5,    //ɾ����ɫʧ��
	eText_Enter_DeletePlayer         = 6,    //ȷ��ɾ�������
	ePlayerCountIsFull               = 7,    // ��ɫ��������
	eText_Disconnect                 = 8,       //����������ӶϿ�
	eText_ConFail                    = 9,                    //����ʧ��
	eText_SelectServer               = 10,            //��ѡ�������
	eText_DBID				         = 11,			//(ID:%d)
	eText_EnterUsePass               = 12,        //�������û���������
	eText_NowTryConnecting           = 13,       //���ڳ��������������
	eText_NowLoadingGameData		 = 14,		// ���ڶ�ȡ��Ϸ����
	eText_KickAccounts				 = 15,		// ����ʺű���
	eText_Custom					 = 16,		// �Զ���
	eText_CreateCheckNameOK          = 17, //��ϲ������������������ʹ��
	eText_CreateCheckNameNO          = 18, //�Բ��𣬸��������ѱ�����ʹ��
	eText_WaitEnterWorld			 = 19, //���ڽ�����Ϸ�����Ժ�...
	eText_GraphicCodeTimeOut		 = 20, // ��֤����֤��ʱ
	eText_IsDelChar                  = 21, //��ɫ�Ѿ���ɾ��
	eText_DelChar_OK                 = 22, //��ɫɾ���ɹ�
	eText_GraphicCodeErrorKick		 = 23, //��֤��ʧ��
	eText_CancelDel_Check            = 24, //ȡ��ɾ����ɫ
	eText_CancelDel_Success          = 25, //ȡ��ɾ����ɫ�ɹ�
	eText_CancelDel_Fail             = 26, //ȡ��ɾ����ɫʧ��
	eText_LastIp					 = 27, //��һ�ε�½IP
	eText_LastAddress				 = 28, //��һ�ε�½��ַ
	eText_LastTime					 = 29, //��һ�ε�½ʱ��
	eText_ProtectTimeAtLeast         = 30, //��ȫ����ʱ�����ٲ���С��%d����
	eText_LowSetting				 = 31,
	eText_DefaultSetting			 = 32,
	eError_DetectInvalidPlus		 = 33,
	eText_Ping                       = 34, //�����ӳ�:%dms
	eIsExitGame                      = 35,//�Ƿ�����
	eClient_Minimap_ServerShow       = 36,    //��ǰ������%s ping:%d
	eError_VideoCardToSlow			 = 37, //�Կ����ù���
	eError_ServerBusy                = 38,//��������æ\n�����ٴγ���
	eServer_State1_Capitally         = 39,  //����
	eServer_State2_Nicer             = 40,      //����
	eServer_State3_Busyness          = 41,   //��æ
	eServer_State4_Jam               = 42,        //ӵ��
	eServer_State5_Close             = 43,      //�ر�
	eLogin_Error_UserFreezed		 = 44,	// �˺ű�����
	//eServer_State7_Defual =44,//" "
	//eServer_State6_maintenance = 45,//ά��
	//eServer_State0_Close = 46,     //�ر�
	eUI_ask                          = 47,                    //ѯ��
	eClient_AddInfo_2slk_16          = 48,        //ѯ��
	eLogin_TimeLongConnectFailed     = 49,    //�޷����ӷ�������
	eLogin_ServerBusy                = 50,    //��������æ��
	eText_Confirm                    = 51,                    //ȷ��
	eClient_AddInfo_2slk_122         = 52,        //%s��ʣ�� %d �롿 
	eClient_AddInfo_2slk_130         = 53,        //��֤ʣ��ʱ�� %d �� 
	eClient_AddInfo_2slk_131         = 54,        //��֤ʱ���ѵ� 
	eClient_LoadCoreDataError        = 55,    //Client�ؼ��������𻵣������°�װClient
	eGameSettingList_Sound			 = 56,		// ��������
	eText_AntiAddictionLess3Hour     = 57,       // ���ۼ�����ʱ������%dСʱ
	eText_AntiAddiction3Hour         = 58,       // ���ۼ�����ʱ������3Сʱ������������Ϣ�����ʵ�����
	eText_AntiAddiction4to5Hour      = 59,       // ���Ѿ�����ƣ����Ϸʱ�䣬������Ϸ���潫��Ϊ����ֵ��50����Ϊ�����Ľ������뾡��������Ϣ�����ʵ�������������ѧϰ����
	eText_AntiAddictionMoreThan5Hour = 60,       // ���ѽ��벻������Ϸʱ�䣬Ϊ�����Ľ�������������������Ϣ���粻���ߣ��������彫�ܵ��𺦣����������ѽ�Ϊ�㣬ֱ�������ۼ�����ʱ����5Сʱ�󣬲��ָܻ�����
	eGameSettingList_Refuse          = 61,       // �ܾ�������ʾ
	eText_No_PF_Target				 = 62,         //û��Ŀ�����ǰ��
	eText_BanSpeak                   = 63,       //����ʱ��ʣ��%d����
	eClient_AddInfo_2slk_132         = 64,        //�� 
	eClient_AddInfo_2slk_133         = 65,        //Ů 
	eClient_IfSellItem1				 = 67,        //��ȷ���Ƿ���Ҫ���� %s  
	eClient_IfSellItem2				 = 68,        //��ȷ���Ƿ���Ҫ���� %s  
	eClient_IfSellItem3				 = 69,        //��ȷ���Ƿ���Ҫ���� %s  
	eClient_IfSellItem4				 = 70,        //��ȷ���Ƿ���Ҫ���� %s  
	eClient_IfSellItem5				 = 71,        //��ȷ���Ƿ���Ҫ���� %s  
	eClient_IfSellItem6				 = 72,        //��ȷ���Ƿ���Ҫ���� %s  
	eText_ProduceRate				 = 73, // ������
	eText_ExitGameCountDown          = 74, // �����˳���Ϸ
	////////////////////////////////////////////////////////////////
	///��Ϸ�������list�б���
	eGameSettingList_Self			= 75, // ������Ϣ
	eGameSettingList_Player			= 76, // �����Ϣ
	eGameSettingList_Npc			= 77, // npc������
	eGameSettingList_Function		= 78, // ����
	eGameSettingList_Mouse			= 79, // �������


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

	eText_ProtectTime           = 95,       // ��ȫʱ��:%s
	eText_ProtectTime_ChangeSucc = 96,      // ��ȫʱ���޸ĳɹ�
	eText_CannotDoIt = 97,      // ��ȫ�������޷����д˲���
	eText_TradeFailed_PlayerInProtect = 98, // �Է��ڰ�ȫ����ʱ���ڣ�����ʧ��
	eText_ProtectTime_ChangeFailed = 99,    // ��ȫ��������ʧ�ܣ�����������
	// dumpe��ʾ
	eDumper_MessageBox_ClientError = 100,		// �ͻ��˳����쳣

	eText_PKMode_LevelLimit     = 101,          // %d��ǰ�޷����Ĺ�������
	eText_PrivateShop_LevelLimit= 102,          // %d��ǰ�޷����а�̯����
	eText_SkillLevel            = 103,          // %d��
	eText_FindTheNpc				= 104,			// Ѱ��%s

	///////////////////////////////////////////
	/// title����	(����title.config��ע����)
	eTitleTypeText_JuQing		= 105,		// ����
	eTitleTypeText_GuanZhi		= 106,		// ��ְ
	eTitleTypeText_GuanFu		= 107,		// �ٸ�
	eTitleTypeText_HuoDong		= 108,		// �
	eTitleTypeText_MinJian		= 109,		// ���
	eTitleTypeText_GuanXi		= 110,		// ��ϵ
	eTitleTypeText_MinWang		= 111,		// ����
	eTitleTypeText_ChuanQi		= 112,		// ����
	eTitleTypeText_TeShu		= 113,		// ����
	eTitleTypeText_JueWei		= 114,		// ��λ		
	eTitleTypeText_Task_ForTitle		= 115,		// ����
	eTitleTypeText_New1			= 116,
	eTitleTypeText_New2			= 117,

	eError_ClientMemoryLack		= 120,      // �ڴ治�㣬������Ϸ��Ҫ600MB�������ڴ�

	eText_PKMode_NoChange       = 121,      // PKֵ����0,�޷��л�������ģʽ
	eText_PKMode_TimeLimit      = 122,      // ����Ƶ���л�PKģʽ��3���ӣ�
	eText_PKMode_FuryTimeLimit  = 123,      // ��ģʽ30����ʱ��δ��
	eText_PKMode_FuryNoShop     = 124,      // ��ģʽ���ܰ�̯

	eText_PKMode_Off            = 125,      // PKģʽ:�ر�
	eText_PKMode_On             = 126,      // PKģʽ:����
	eText_PKMode_Fury           = 127,      // PKģʽ:��
	eText_NotInStallArea		=128, //���ٰ�̯����

	eText_PKMode_GuildOn		= 129,		// ����PKģʽ������
	eLeftType_Hp				= 130,		// Hp
	eLeftType_Mp				= 131,		// Mp

	eTitleTypeText_Task					= 135,		// ����


	eText_ShowAllPlayer         = 136,   //��ʾ�������
	eText_HideAllPlayer         = 137,   //�����������
	eText_ShowAmityPlayer       = 138,   //��ʾ�Ѻ����
	eText_ShowAntagonizePlayer  = 139,   //��ʾ�ж����

    eLogin_ValidateUser			= 140,		// ��֤�û�
    eLogin_EnterGame			= 141,		// ���ڽ�����Ϸ
    eLogin_Process				= 142,		// ������
    eLogin_ConnectGate			= 143,		// ������Ϸ������

	eText_ServerShutdown1		= 144,		// ����������%s�����ά��������Ҽ�ʱ���ߣ�������ɲ���Ҫ����ʧ
	eText_ServerShutdown2		= 145,		// ����������%s�����ά�����������ȴ�ά���������ٽ�����Ϸ
	eText_ShowMapExpRate        = 146,      // ��ǰ��ͼ�����ȡΪ%d%%
	eText_ShowChangeMapExpRate  = 147,      // %s�ѿ�����%d%%������
	eText_MapExp				= 148,		// ��ǰ��ͼ�ѿ���%d�����齱��
	eText_MaxMoneyTip			= 149,		//�����Ͳֿ�Ľ�Ǯ������\n1-20��10��\n21-40��100��\n41-55��1000��\n55������5000��\n�������޺��޷����н��׺Ͱ�̯
	eLogin_AccountsError		= 151,		// �˺Ų�����
	eLogin_PasswordError		= 152,		// �������
	eText_Area                  = 153,      //����:%s
	eText_ServerName            = 154,      //��ǰ������:%s
	eText_JiaoZiTip             = 155,      //����:�󶨻��ң�˵��XXXXXX

	eText_BeiJing						 =156, //����
	eText_ShangHai					 =157,//�Ϻ�
	eText_TianJin						 =158,//���
	eText_ChongQing				 =159,//����
	eText_NeiMengGu				 =160,//���ɹ�
	eText_XinJiang						 =161,//�½�
	eText_XiZang						 =162,//����
	eText_NingXia						 =163,//����
	eText_GuangXi						 =164,//����
	eText_HongKong				 =165,//���
	eText_MaCao						 =166,//����
	eText_HeiLongJiang			 =167,//������
	eText_JiLin								 =168,//����
	eText_LiaoNing					 =169,//����
	eText_HeBei							 =170,//�ӱ�
	eText_ShanXi						 =171,//ɽ��
	eText_QingHai						 =172,//�ຣ
	eText_ShanDong					 =173,//ɽ��
	eText_HeNan						 =174,//����
	eText_JiangSu						 =175,//����
	eText_AnHui							 =176,//����
	eText_ZheJiang					 =177,//�㽭
	eText_FuJian							 =178,//����
	eText_JiangXi						 =179,//����
	eText_HuNan						 =180,//����
	eText_HuBei							 =181,//����
	eText_GuangDong				 =182,//�㶫
	eText_TaiWan						 =183,//̨��
	eText_HaiNan						 =184,//����
	eText_GanSu							 =185,//����
	eText_Shan_Xi						 =186,//����
	eText_SiChuan						 =187,//�Ĵ�
	eText_GuiZhou						 =188,//����
	eText_YunNan						 =189,//����

	eGameSettingList_Tab        = 190,      //Tab��������
	eText_KuaiJieJian					=197,		//��ݼ�
	eText_CaoZuo						=198,		//����
	eText_GuildOffer					= 199,		// �ﹱ
	eText_Exploit						= 200,		// ��ѫ
	eText_Reputation				= 201,		// ����
	eText_Energy						= 202,		// ����
	eText_Vigor							= 203,		// ����
	eText_PKValue						= 204,		// pkֵ


	eText_TheFinalAward			=205,				//ϵ������\n�ռ�����
	eText_TheAward				=206,				//��Ʒ

	eText_CannotShareExp		=207,				//����λ��:%s����������Զ���޷������飩
	eText_ShareExp				=208,				//����λ��:%s���������Ұ��Χ�ڣ����Թ����飩
	eText_TalkToPlayer          =209,               //�� %s ������
	eText_CannotConjurePetExit	=210,				//�ٻ�����δ��ʧ���޷��ٴ��ٻ�

	eText_EnableSoftKeyboard    =211,               //������������
	eText_DisableSoftKeyboard   =212,               //����ر������
	eText_ReStartIntroduction   =213,               //�����ͨ�� ��Ϸ���á����ܡ�����ָ�� ����������������
	eText_SuperPasswordExplain  =214,               //�����������޸�����½����������֤����Ҫ;���������Ʊ��ܡ�\n����������8-32λ��ĸ�����ּ�������ɣ����ִ�Сд��
	eText_TodayKillMonster      =215,               //���ռ���ɱ������"���ռ���ɱ������:%d/%d"/
	eText_WaitingServerUpdate      =216,               //���ڽ������ݲ�ѯ�����Ժ�...
	eText_FilterCharInfo        = 217,             //��Ϣ�д��зǷ��ַ�������ʧ��

	eText_TeamOffLine			= 218,             //����

	eText_PubQuestItemCount		= 219,				// �о�������
	eText_NotFindRepairItem		= 220,			// û��ָ�������޵���

	eText_GuildMoney			= 221,	// ����ʽ�
	eText_GuildBuild			= 222,  // ��Ὠ���
	eText_TimeOut				= 223,	// �ѵ���
	eText_OperateFailInProtectTime = 224,			//�Ʋ�����״̬���޷����д˲���
	eText_ServerStatus          = 225,  //����������\n�����Լ������ԣ���ѡ���������������е�½
	eText_OperateContinue       = 226, //����
	eText_OperatorReturn        = 227, //����
	eText_LauncherStart         = 228, //��Ҫ��Launcher����
	eText_ErrorStart            = 229, //��������
	eText_AutoFightStart        = 230, //��ʼ�һ�
	eText_AutoFightEnd          = 231, //ֹͣ�һ�
	eText_StarAll               = 232, //�Ѿ�����
	eText_Yes                   = 233, //��
	eText_No                    = 234, //��
	eText_SuperAll              = 235, //����
	eText_NameNoNull            = 236, //�������ֲ���Ϊ��
	eText_DragLockWarning		= 237, //��ק����

	eText_ScreenshotSaved		= 238, //��ͼ%s����ɹ���Screenshots�ļ����£�����F12���������н��棬��������ģʽ��
	eText_PointShowInfo         = 239,  //δ��ѯ�������ֶһ�����Ʒ��Ϣ
	eText_MarrySuccess          = 240,  //��ϲ%s��%sϲ������ף�����������һ����ͷ����
	eText_UseItemFailed_InCD	= 242,	//��Ʒ������ȴ�У����Ժ�����
	eText_AutoFightNoFindHP        = 243, //��ʼ�һ�
	eText_AutoFightNoFindMP         = 244, //ֹͣ�һ�

	eText_Guild_CreateFamily = 245,
	eText_Guild_ChangeFamilyName = 246,
	eText_AutoFightUseRestorLev = 247, //�Զ��һ��ָ�ҩƷʹ�õȼ�����
	eText_AutoFightNotStartCurState        = 248, //��״̬�²����Զ��һ�


	eText_SkillUse_ProfessionLimit       = 258,  //ְҵ�������޷�ʹ�ô˼���

	eText_GameSettingHigh       = 260,  //��Ʒ��
	eText_GameSettingMiddle	    = 261,  //��Ʒ��
	eText_GameSettingLow        = 262,  //��Ʒ��
	eText_GameSettingCustom     = 263,  //�Զ���
	eText_Level	= 264,	//�ȼ�
	eText_GameTaskInfo          = 270,  //��û�о�����

	//ʮ����Ф
	eText_AnimShu					=271, //��
	eText_AnimNiu						=272,//ţ
	eText_AnimHU						=273,//��
	eText_AnimTu						=274,//��
	eText_AnimLong					=275,//��
	eText_AnimShe					=276,//��
	eText_AnimMa						=277,//��
	eText_AnimYang					=278,//��
	eText_AnimHou					=279,//��
	eText_AnimJi						=280,//��
	eText_AnimGou					=281,//��
	eText_AnimZhu					=282,//��
	//ʮ������
	eText_ConShuiPing				=284,//ˮƿ��   1.20 - 2.18
	eText_ConShuangYu			=285,//˫����   2.19 - 3.20
	eText_ConBaiYang				=286,//������   3.21 - 4.20
	eText_ConJinNiu					=287,//��ţ��   4.21 - 5.20
	eText_ConShuangZi			=288,//˫����   5.21 - 6.21
	eText_ConJuXie					=289,//��з��   6.22 - 7.22
	eText_ConShiZi					=290,//ʨ����   7.23 - 8.22
	eText_ConChuNv					=291,//��Ů��   8.23 - 9.22
	eText_ConTianCheng			=292,//�����   9.23 - 10.22
	eText_ConTianXie				=293,//��Ы��   10.23 - 11.21
	eText_ConSheShou				=294,//������   11.22 - 12.21
	eText_ConMoJie					=295,//Ħ����   12.22 - 1.19
	eText_CreateBrithDay			=296,//����������%d��%d��,����Ϊ%s,��ȷ��������
	eText_SelPlayerDelLifeTime      =297,//��ɫɾ��ʣ��%d��
	//eUI_LevelUp                =300,                //��ĵȼ�������
	eTip_AlreadyMaxLevel		 = 300,				// �ѵ���ߵȼ�
	eUI_NextLevel                =301,                        //��һ��
	eUI_NeedText                =302,            //��Ҫ
	eText_YouGet_Money         =303,        //    ��õ���
	eText_Exp                    =304,        //
	//eText_SkillExp                =305,        //
	eText_YouSell				= 305, // ��������%s,���%s
	eText_YouLost                =306,        //    ��ʧȥ��
	eText_Got                    =307,        //�õ�
	eText_BeginFight            =308,            //
	eText_ExitFight                =309,            //
	eCreate_NameError        =310,                //���ֲ��Ϸ�
	eText_HPNoEnough        =311,
	eText_MPNoEnough        =312,
	eText_Motion_CantSing    =313,            //
	eText_PassiveSkill_NotUse=314,    //
	eText_StudySkill        =315,                //��ѧ���˼���
	eText_PackMoneyCorrect	= 316,		// ������Ǯ�������ޣ��ѽ��л���
	eText_CannotUseSkillInCurStatus      = 317,        // �����ڵ�ǰ״̬��ʹ�ü���
	eText_StorageMoneyCorrect			 = 319, // �ֿ��Ǯ�������ޣ��ѽ��л���
	eText_TargetNotInTheView             = 320, // Ŀ�겻����Ұ��
	eText_Optional						 = 321, // (��ѡ)
	eText_FCMOperateFailed				 = 322, // ������״̬�޷����д˲���
	eText_ItemUseLevel                   = 323, // �������ڵĵȼ�������ʹ�ô���Ʒ
	eText_ItemUse_ProfessionLimit        = 324, // ְҵ�������޷�ʹ��
	eText_Server_Chat_noGuild            = 325, // ��Ŀǰ��û�м����κι��ᣡ
	eText_Server_Chat_noTeam             = 326, // ��Ŀǰ��û�м����κζ��飡
	eTextPlayer_PassiveNotUse            = 327, // �������ܲ����Ա�ʹ��
	eTextBargainingError_OutRange           = 328,//Ŀ�����̫Զ�����ɽ���
	eTextDuelError_OutRange                 = 329,//Ŀ�����̫Զ�������д�
	eText_Chat_NotSeekEquip                    = 330, //���ܲ鿴�������װ��        
	eText_YouGet_N_S                        = 331, //��õ��� %d %s
	eUI_IsRelive        = 332, // �ڸ����㣬�Ƿ���ܣ�
	eUI_DeadReliveInfo  = 333, // ������ť���������ĸ����
	eText_ReliveTimeOut = 334, // ������Чʱ���ѹ�������ʧ��
	eText_MAXKILLMONSTER     = 335,  //ɱ������������ǰ�Ļ�ɱ����
	//eClient_AddInfo_2slk_121        = 335,        //HERO[Version:%s] 
	eUI_CurPower = 336,//��ǰ������
	eClient_customShortcutKeyRep = 337,    //�˿�ݼ��Ѿ���ռ����!
	eClient_Friend_ListInfoOutline    = 338,    //%-16s%-8s%-8s
	eLimitMapTime                    = 339,    // ����ʱ:%d.%d
	eText_BeyondMoneyLimit		= 340,	// ���Ľ�Ǯ�Ѿ�������Я��������%d�𣬳����Ľ�Ǯ��������30���Ӻ�ϵͳ���գ�
	//     eClient_FrdDlg_PK_Guild            = 341,    //���ᱣ��ģʽ
	eClient_PK_Team            = 341,    //����ģʽ:����
	eClient_PK_All               = 342,  //����ģʽ:ȫ��
	eClient_PK_Sworn               = 343,  //����ģʽ:����
	eClient_PK_Guild                = 344,  //����ģʽ:����
	eClient_PK_League                  = 345,  //����ģʽ:ͬ��

	eText_PKRedNameCannotRelive     = 347, // Ŀ��ɱ¾���أ��޷�������
	eText_BeyondPackMoneyLimit	= 348,	// �ֿ��Ǯ���ѵ���%d����
	eCannotClearStatusByDead = 349,  //������״̬����

	//////////////////////////////////////////////////////
	/// �������÷�Χ
	eSkillCastType_Title			 = 350,		// ���÷�Χ
	eSkillCastType_SingleTarget		 = 351,		// ����
	eSkillCastType_PointCircle		 = 352,
	eSkillCastType_SelfCircle		 = 353,
	eSkillCastType_QuarterCirleFront = 354,
	eSkillCastType_PointAOE			 = 355,

	eText_QuitGameToLogin           = 356,  // ���ڷ��ص�½���棬���Ժ�...\n
	eText_QuitGameToSelect          = 357,  // ���ڷ��ؽ�ɫ���棬���Ժ�...\n
	eText_LevelNotReachable          = 358,  // �ȼ��������޷���ѯ�˵�ͼ��Ϣ
	//eClient_send2GMUI_playerUseOtherTools    = 350,    //%s����Ϸ��ʹ�����
	//eClient_send2GMUI_playerLock            = 351,    //%s��������%s
	//eClient_send2GMUI_ChatSystem2Player        = 352,    //���Ѿ�������Ϣ��gm��ȴ�����
	//eClient_haveNotPackEx                    = 353,    //����û�������򿪸��Ӱ���
	//eClient_DisDrome_Tip                    = 354, //������ʾ
	//eClient_Minimap_show_eventInfoBen        = 355,    //���ڽ���:\n{#ff69cb34
	//eClient_Minimap_show_eventInfoEnd        = 356,    //#}
	//eClient_Minimap_show_eventNew            = 357,    //  {#ff00ff00=%s#} ���ʼ 
	eClient_VassalName				= 359, // %s��ū��
	eClient_PubItemDesc				= 360,  // �о�������
	eClient_RoyalItemDesc			= 361,  // �ư�������
	eClient_AddInfo_2slk_1         = 362,        //��ЧĿ��
	eClient_RegionMap_MousePosition         = 363,        //�����ָ��ͼ����  %d  %d
	eClient_IfUseItemForMount         = 364,        //�Ƿ���Ҫ��{#%x=%s#}ʹ��{#%x=%s#}��
	eClient_AddInfo_2slk_5         = 365,        //��������1����Ʒ����!
	eClient_AddInfo_Address         = 366,        //��������1����ַ����
	eClient_IfUseItem				= 367,        //�Ƿ���Ҫʹ��%s��
	eText_ChangeMapFailed_MapFull   = 368,      //Ŀ���ͼ����Ϊ�������Ժ�����
	eClient_AddInfo_2slk_9         = 369,        //��û�м����κι���
	eClient_AddInfo_2slk_11        = 370,        //�����
	eClient_AddInfo_2slk_12        = 371,        //ս���в���װ��
	eClient_AddInfo_2slk_13        = 372,        //ս���в�������
	eClient_AddInfo_2slk_14        = 373,        //����ɾ������Ʒ?
	eClient_AddInfo_2slk_23        = 374,        //"��ʾ"(С��ͼ)
	eClient_AddInfo_2slk_27        = 375,        //"�Ƿ�ɾ������Ʒ?"
	eClient_AddInfo_2slk_28        = 376,        //"ɾ����Ʒ"

	////////////////////
	eTeam_TeamMate					= 377,		// ����
	eTeam_InTeam					= 378,		// ��Ա
	eTeam_TeamLeader				= 379,		// �ӳ�


	eText_CannotLootMount_InFight       = 380,  //ս�����޷�ѱ��
	eText_CannotLootMount_WhenMounting  = 381,  //���״̬���޷�ѱ��
	eText_CannotLootMount_CurrStatus    = 382,  //��ǰ״̬���޷�ѱ��
	eClient_AddInfo_PFError        = 383,        //�õص��޷�Ѱ·����  
	eClient_AcceptNPC					= 384,  //%s�� %s ��Ҫ�����������ǰȥ����
	eText_WaitForChangeMap              = 385,  // �ȴ�������
	eText_ChangeMapServerBusy           = 386,  // ��������æ
	eText_Interaction_InviteEmbrace     = 387,  //  %s ϣ�������������ˣ��Ƿ�Ը�⣿
	eText_QueryDiscardPet				= 388,  // ȷ��Ҫ���� %s ��
	eText_ChangeMountName				= 389,  // �����������
	eText_CannotShout_LevelNotMatch     = 390,  // 10�������޷����纰��
	eText_CannotCrossMapPathFind     = 391,  // ��NPC��֧�ֿ��ͼѰ·

	eTimeUnit_Second = 392, // ��
	eTimeUnit_Minute = 393, // ��
	eTimeUnit_Hour = 394,   // ʱ
	eText_CannotCrossMapPathFindAddress = 395,   // �õص��޷����ͼѰ·
	eClient_SetHotKey					= 396,  //���밴������->%s
	eClient_NotHotKey					= 397,  //δ����
	eClient_SucceedSetHotKey			= 399,  //�������óɹ�

	eClient_AddInfo_2slk_86        = 398,        //%s ����ʹ������Ʒ %s  
	
	eText_ZhenYingChat_NotInBattle	= 400,	// ��δ������Ӫ

	eClient_AddInfo_2slk_126        = 401,        //%s %d �� 
	eClient_NpcCoord_direct = 404,    //Ŀ�ĵ�

	eText_CreateChar_MaleShort      = 405,  // ����
	eText_CreateChar_MaleTall       = 406,  // ����
	eText_CreateChar_FemaleShort    = 407,  // ����
	eText_CreateChar_FemaleTall     = 408,  // ����
	eText_NeedFillItem				= 409,  // ��Ҫ����:{#%x=%s#}

	eText_IfUseLaBa					= 410,  // ���纰����Ҫ����һ��С���ȣ��Ƿ�ʹ��
	eText_HighShoutNeedLaBa			= 411,  // ֻ��Я��С���Ȳ��ܽ������纰��
	eText_LoseOneLaBa				= 412,  // ʧȥһ��С����

	//eTellClient_IntegralMax = 409,//������Ϣ �������ֵ����:%d,��ǰ�������ֵ:%d
	//eTellClient_Gm2Player_ShowName = 410,//GM����PLAYER��ʾ������
	//eTell_Client_ProjectCharDis = 411,//�뻤�͹������̫Զ!
	//eClient_CantUseGood_ByDiffState             = 412, //��ǰ״̬����ʹ����Ʒ
	eServer_picktime_eResultNotTeamHeader = 407,//"You`re not leader"    
	eText_CannotLoot_InFight					= 413,	// ս��״̬���޷��ɼ�
	eText_CannotLoot_WhenMounting				= 414,	// ���״̬���޷��ɼ�
	eText_LessNpcDialogTime = 415,  // ��NPC�Ի�ʱ��̫��
	eText_SitFailed_InFighting					= 416,	// ս��״̬���޷�������
	eText_SitFailed_CurrStatus					= 417,	// ��ǰ״̬�޷�ִ�д˲���
	eText_MaxPubTaskNumber						= 418,	// ͬʱ���ֻ�ܽ�ȡ%d���ƹ�����ͻʰ�����
	//eText_SitFailed_WhenJumping					= 418,	// ��������������ʱ������
	//eText_SitFailed_WhenMounting				= 419,	// ����״̬���޷�������
	eText_RepairSuccess							= 419,	// ����ɹ�
	eText_GroupPanel_NearPlayerList				= 420,	// ��������ַ�����ʽ
	eText_GroupPanel_TeamPlayerList				= 421,	// ��Ҷ����ַ�����ʽ//eText_CreateCheckPeople              =61, //�����ɫ�޷�����
	eText_LockSkill_No							= 422,	// ����Կ����ͼ���������
	eText_LockSkill_Yes							= 423,	// ���ȡ�������ͼ������
	//eText_YouGotAdditionalEncouragement = 423, //���ö���Ľ�Ǯ�;��齱����
	eText_AckNpc = 424, // �ظ�%s��
	eText_OperateFailedInCD = 425, // ��������Ƶ�������Ժ���
	eUI_sCanNotFindString = 426, // �޷����ҵ��������ݣ�����������
	eUI_CanNotDestroyActivedMount = 427, // ��ս�������޷�������
	eText_TargetNoActiveMount	= 428, // �Է�û�г�ս������
	eText_Point                            =    429,//��
	eText_Money_Gold	= 430, // ��
	eText_Money_Silver	= 431, // ��
	eText_Money_Copper	= 432, // ͭ

	eText_Equip_Error_Sex			= 433, // �Ա𲻷����޷�װ��
	eText_Equip_Error_Level			= 434, // �ȼ��������޷�װ��
	eText_Equip_Error_Profession	= 435, // ְҵ�������޷�װ��

	eClient_TrapName				= 436, //&lt;%s������&gt;

	eText_Follow_Cancel = 437,  // ȡ������

	eText_PKMode_Peace = 438,  // ��ƽ
	eText_PKMode_All = 439,  // ����
	eText_PKMode_Guild = 440,  // ����
	eText_PKMode_Team = 441,  // ���

	eText_Mount_NotActived = 442, //��ѡ����Ҫ��ս������
	eText_MountBag_NotSpace = 443, //����û�пռ�

	eText_YouLost_N_S = 444, //ʧȥ %d �� %s

	eText_NotActiveAccounts = 445, //�����ʺ�δ����
	eText_NeedInputName = 446, // �������ɫ��

	eText_MaterialPackFull = 447,	//���ϰ�������
	eText_NormalPackFull = 448,		//��ͨ��������
	eText_TaskPackFull = 449,		//�����������

	eLogin_LoginHighFrequency = 450,		//���ĵ�½����Ƶ������ȴ� %d ������µ�¼��Ϸ
	eLogin_LoginQueue = 451,				//��ǰ���� %d ���Ŷӣ������ĵȴ�
	eLogin_UserAlreadyOnline = 452,		//�����ʺ������ߣ���ȴ� %d ����ٴ˳��Ե�½

	eText_NotChangePKMode = 454,		//15��ǰ�޷�����PKģʽ

	eSkillMaxLevel_Text  = 455,			//	�������ȼ�

	/////////////////////////////////
	///����Ʒ�󣬰������������ʱ��
	eText_AlmostFull_BagNormal		= 456,	// ��ͨ���������ˣ�����..��λ��
	eText_AlmostFull_BagMaterial	= 457,	// ���ϰ��������ˣ�����..��λ��
	eText_AlmostFull_BagTask		= 458,	// ������������ˣ�����..��λ��

	/////////////////////////////////
	///�ɼ����ܵȼ��ж�
	eText_LootFailed_HerbLevelNotMatch  = 459,  // ��ҩ���ܵȼ�����,��Ҫ���ܵȼ�%d��
	eText_LootFailed_MineLevelNotMatch  = 460,  // �ڿ��ܵȼ�����,��Ҫ���ܵȼ�%d��
	eText_LootFailed_InsectLevelNotMatch= 461,  // ���漼�ܵȼ�����,��Ҫ���ܵȼ�%d��
	eText_LootFailed_VigorNotEnough     = 462,  // ��������
	eText_MountEnjoymentNotEnough		= 463,	// ������������

	/////////////////////////////////
	///����ʰȡ
	eText_PackagePickUp_NotExist        = 464,  // ����Ʒ�Ѿ���ʰȡ
	eText_PackagePickUp_CannotPick      = 465,  // ����Ʒ��������
	eText_PackagePickUp_AssignItem      = 466,  // [%s]��������� %s
	eText_PackagePickUp_AssignFailed    = 467,  // ����ʧ�ܣ��Է�������

	eText_Mount_Mate_Unable             = 468,  // ���䲻��     Ϊ͵������2 String�����ŵ�
	eText_Mount_Mate_Able               = 469,

	eText_NoMoneyForWorldChat			= 470,  // ���Ľ�Ǯ�������޷�������������

	eText_NoSkillForHerb				= 472,  // δѧ���ҩ����
	eText_NoSkillForMine				= 473,  // δѧ��ɿ���
	eText_NoSkillForCatch				= 474,  // δѧ�Ჶ׽����

	/////////////////////////////////
	///�䷽
	eText_RecipeAlreadyExist			= 475, // �Ѿ�����
	eText_RecipeFull					= 476, // ����
	eText_RecipeNoThis					= 477, // û�д��䷽
	eText_RecipeUnknown					= 478, // δ֪����

	eText_ProduceSkillNpcDesc           = 479, // %s��ʦ:%s
	eText_Time							= 488, // ʱ��	

	/////////////////////////////////
	///����
	eMountError_FullMount				= 490, // ������������
	eMountError_ActiveMountNotSupport	= 491, // ��ս�е����ﲻ�ܽ��д˲���

	eText_CurrentEnergy                 = 492, // ��ǰ���� %d
	eText_CurrentVigor                  = 493, // ��ǰ���� %d
	eText_NotEnoughVigorToHerb          = 494, // ����ֵ�������޷��ɼ���ҩ
	eText_NotEnoughVigorToMine          = 495, // ����ֵ�������޷��ɼ���ʯ
	eText_NotEnoughVigorToInsect        = 496, // ����ֵ�������޷�����
	/////////////////////////////////
	///װ������
	eText_Intensify_MaterialItemLevel = 499, // �������ϵȼ�����
	eText_Intensify_StarSuccess		  = 500, // װ�����ǳɹ�
	eText_Intensify_StarFailed		  = 501, // װ������ʧ��
	eText_Intensify_EquipNotMatch	  =	502, // װ����ƥ��
	eText_Intensify_RepGem			  = 503, // ��ʯ�ȼ�����
	eText_Intensify_MaxLevel		  = 504, // ǿ���������ȼ�
	eText_Intensify_NoItem			  = 505, // ��Ʒ������
	eText_Intensify_NoMoney			  = 507, // û���㹻��Ǯ
	eText_Intensify_FailedItem		  = 508, // ����ı�ʯ����
	eText_Intensify_AlreadyIdentify   = 509, // �Ѿ���������
	eText_Intensify_NotIdentify		  = 510, // ��û�м���
	eText_Intensify_AlreadyKaiGuang	  = 511, // �������
	eText_Intensify_IdentifySuccess	  = 512, // �����ɹ�
	eText_Intensify_KaiGuangSuccess	  = 513, // ����ɹ�
	eText_Intensify_CannotIdentify	  = 514, // ���ܱ�����

	//////////////////////////////////
	///����/�����ִ�
	eText_Identify					  = 515, // ����
	eText_KaiGuang					  = 516, // ����
	eText_CannotIdentify              = 519, //���ܱ�����

	eText_MoveStarUpgrade_Progress	  = 520, // ����

	eText_StarMaterialUpgrade_Progress= 521, // �ϳ�
	eText_SpecialRepair_Progress		= 524, //����
	eText_Decompound_Progress			= 525, //�ֽ�
	eText_Identify_Progress				= 526, //����
	eText_OpenLight_Progress			= 527, //����
	eText_Upgrade_Progress				= 528, //����
	eText_MoveStar_Progress				= 529, //����


	eWarning_Cannot_Soul_ItemLowTo40	= 530,//40������װ���޷�����
	eWarning_Cannot_Soul_Repeat			= 531,//��װ���Ѿ����̹����޷��ٴ�����
	eText_Soul_Soul						= 532,//����
	eText_Soul_Soul_Success				= 533,//���̳ɹ�
	eWarning_Cannot_Soul_PlayerLowTo45	= 534,//45����������޷�����
	eText_XiZi_Success					= 536,//װ��ϴ�ϳɹ�
	eText_Recycle_Success				= 537,//װ�����ճɹ�
	eText_OpenLight_Success				= 538,//װ���̽�ɹ�
	eWarning_CannotOpenLightRepeat		= 539,//װ���Ѿ��̽�����޷��ٴ��̽�
	eWarning_Hole_Full					= 540,//װ����������Ѿ����������Ŀ���޷��ٴδ��

	eText_Hole_Success					= 541,//��׳ɹ�
	eText_Maintain_Success				= 542,//װ����ֵ�ɹ�
	eText_CrossMaintain_Success			= 543,//�缶��ֵ�ɹ�

	eWarning_OpenLight_PlayerLowTo60	= 544,//��ҵȼ�δ�ﵽ60���޷�ʹ���̽�
	eWarning_OpenLight_ItemLowTo60		= 545,//װ���ȼ�δ�ﵽ60���޷������̽�
	eWarning_OpenLight_NoGolden			= 546,//װ��Ʒ��δ�ﵽ��ɫ�޷������̽�

	eWarning_ReOpenLight_PlayerLowTo60	= 547,//��ҵȼ�δ�ﵽ60���޷�ʹ���̽��¯
	eWarning_ReOpenLight_ItemLowTo60	= 548,//װ���ȼ�δ�ﵽ60���޷������̽��¯
	eWarning_ReOpenLight_NoPurple		= 549,//װ��Ʒ��δ�ﵽ��ɫ�޷������̽��¯


	eText_Gem_Success					= 550,//��ʯ��Ƕ�ɹ�
	eText_GemRemove_Success				= 551,//��ʯ��ж�ɹ�
	eWarning_Gem_Equip_First			= 552,//���ȷ�����Ҫ��Ƕ��װ��
	eText_GemReplace_Success			= 553,//��ʯ�滻�ɹ�
	eText_GemUp_Success					= 554,//��ʯ�����ɹ�
	eWarning_GemTypeError				= 555,//��ʯ���Ͳ������޷���Ƕ
	eWarning_NoEmptyHole				= 556,//û�п���ı�ʯ��
	eWarning_GemInHole					= 557,//�ÿ��ѷ��뱦ʯ
	eWarning_BagFull                    = 558,//���ı��������������������ռ����ִ�д˲���
	eWarning_NotGemInHole				= 559,//�ÿ����ޱ�ʯ���޷��滻



	eText_HookOffline_Affirm            = 560,  // �Ƿ�ȷ�Ͽ�ʼ���߹һ�

	eWarning_Maintain_ItemLevel				= 561,//װ���ȼ�δ�ﵽ60���޷���ֵ
	eWarning_Maintain_SamePart				= 562,//������ͬ��װ���ſ��Խ��б�ֵ
	eWarning_Maintain_PurpleItem			= 563,//�������ɫװ��
	eWarning_Maintain_GoldItem				= 564,//������ɫ����ɫװ��
	eWarning_CrossMaintain_Level			= 565,//�缶��ֵֻ�����Ͽ�һ��
	eWarning_Maintain_PlayerLevel			= 566,//��ҵȼ�δ�ﵽ60���޷����б�ֵ
	eWarning_Maintain_NotSameLevel			= 567,//װ���ȼ���ͬ�޷����б�ֵ

	eWarning_Recycle_GoldItem				= 568,//ֻ�н�ɫ����Ʒ�ʵ�װ�����ܻ���

	eWarning_Charm_BlueItem					= 569,//ֻ����ɫƷ�ʵ�װ����������
	eWarning_Charm_Success					= 570,//�������ճɹ�
	eWarning_Charm_Fail						= 571,//��������ʧ��

	eWarning_Amulet_ItemType				= 572,//ֻ�л����������ɫ
	eWarning_Amulet_Symbol					= 573,//�����������ɫ���Եķ���
	eText_Amulet_Left						= 574,//�û����������ɫ:%d��
	eWarning_Amulet_Success					= 575,//�������ճɹ�

	eWarning_GemUp_Success					= 576,//��ʯ�����ɹ�
	eWarning_GemUp_ErrorGem					= 577,//�ñ�ʯ��������
	eWarning_GemUp_ErrorType				= 578,//ֻ�б�ʯ�ſ�������������

	eWarning_XSJUp_ErrorType				= 579,//ϴʯ�����óɹ�
	eWarning_XSJUp_Success					= 580,//ϴʯ�����óɹ�
	eWarning_XSJUp_LackMaterial				= 581,//���ϲ����޷�����

	eText_Star_Star							= 582,//%d��
	eWarning_AutoStar_LackMaterial			= 583,//���ϲ����޷���������
	eWarning_AutoStar_LackMoney				= 584,//��Ǯ�����޷���������
	eWarning_AutoStar_Ok					= 585,//�Ѿ�����%d��
	eWarning_HaveSameBaseRand				= 586,//�����޷�����ͬ��������

	//////////////////////////////////

	//���а�
	eText_Rank_MeLevelIn = 589,        //<String Id="589" Value="���ĵ�ǰ�ȼ�Ϊ%s"/>
	eText_Rank_MeLevelOut = 590,         //<String Id="590" Value="����ʱ���������а�֮�ڣ����ٽ�����!"/>

	eText_Tip_SoulStamp               = 591, // ������+%d��
	eText_Info_SoulStamp              = 592, //��װ���޷�����

	eText_Hole_ItemLevel              = 593, //װ���ȼ�����10�����޷����

	// ��Ʒ����ǰ׺
	ePreItemText_LiangPin			  = 600, // ��Ʒ
	ePreItemText_JingPin			  = 601, // ��Ʒ
	ePreItemText_JiPin				  = 602, // ��Ʒ
	ePreItemText_ShenPin			  = 603, // ��Ʒ

	/////////////////////////////////
	// ���� ����� ���߹һ� ���
	eText_MountGeneration_First         = 630, // ����
	eText_MountGeneration_Second        = 631, // ����
	eText_MountRestore_NoMoney          = 632, // ��Ǯ�����޷���������
	eText_MountBreed_MasterLevel        = 633, // ���ﷱֳ������ȼ�С��60��
	eText_MountBreed_NoMoney            = 634, // ���ﷱֳ��Ǯ����
	eText_MountBreed_Unable             = 635, // �����޷����з�ֳ
	eText_MountBreed_NoNext             = 636, // �޷��������ﷱֳ��������û����һ����
	eText_MountBreed_Success            = 637, // ���ﷱֳ�ɹ�
	eText_MountSkill_SlotAlreadyOpen    = 638, // �Ѿ��������ܲ�
	eText_MountSkill_SlotNoSkill        = 639, // ����λ��û�м���

	eText_BizSkill_NotEnoughExp         = 640, // �����Ȳ����޷���������
	eText_BizSkill_AlreadyFull          = 641, // ���������

	eText_MountLevel_OverPlayer         = 642, // ����ȼ���������ȼ�5�����޷����Ӿ���

	eText_Hook_NotHasLevel              = 643, // �һ����δ���
	eText_Hook_NoMoneyToGetExp          = 644, // ��Ǯ�����޷���ȡ����

	eText_UseItem_NotEnoughMountLevel   = 645, // ����ȼ������޷�ʹ�õ���
	eText_UseItem_MountNotSelect        = 646, // ����ѡ����Ҫʹ�ô˵��ߵ�����

	eText_PlsInputRightXY				= 650, //��������Ҫǰ���ص������

	eText_NoActiveMountSkillHole		= 651, //���＼�ܲ�δ����޷�ʹ��
	eText_MountLevel_HuanTongShu        = 660, // ����Я���ȼ�С��40���޷�ʹ�û�ͯ��
	eText_MountLevel_HuanLongShu        = 661, // ����Я���ȼ�С��80���޷�ʹ�û�����
	eText_Mount_CantUseHuanLongShu      = 662, // �������޷�ʹ�û�����
	eText_OneKeySuit_NoSet              = 663, // û�и�һ����װ������
	eText_Honour_TopLimit               = 664, // ��������ֵ�ﵽ����
	eText_NoOffline_HookExp             = 665, // û�����߹һ�����
	eText_OfflineHook_LevelLess         = 666, // ���߹һ��ȼ�����
	eText_ReliveOrigin_NoMoney          = 667, // ��Ǯ�����޷�ԭ�ظ���
	eText_MountType_CannotBreed         = 668, // �������Ͳ�ͬ�޷����з�ֳ

	eText_BeKilled_NoHyperlink          = 669, // �㱻 %s ɱ����
	eText_LevelNotmeet                  = 670, //�ȼ�����
	eText_Hole_Failed                   = 680, //���ʧ��
	eText_EquipNoIdentity               = 681, //��װ���޷�����
	eText_BuhlNoExist                   = 682, //��Ƕ��������
	eText_Gem_UpdateFailed              = 683, //��ʯ����ʧ��
	eText_Gem_SameType                  = 684, //ͬ���ͱ�ʯֻ����Ƕһ��

	///������
	eText_SkillPoint					= 701, // ������
	eText_CaoYao_SkillPoint				= 702, // 0:��ҩ
	eText_ZhuBao_SkillPoint				= 703, // 1:�鱦
	eText_DuanZao_SkillPoint		    = 704, // 2:����
	eText_ZhuJia_SkillPoint				= 705, // 3:����
	eText_GongYi_SkillPoint				= 706, // 4:����
	eText_XunMa_SkillPoint				= 707, // 5:ѱ��
	eText_CaiYao_SkillPoint				= 708, // 6:��ҩ
	eText_CaiKuang_SkillPoint			= 709, // 7:�ɿ�
	eText_BuChong_SkillPoint			= 710, // 8:����
	// ��׽��Ҫ

	// ���������
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

	eCreate_BirthdayError	= 800, //������ɫʱ������Ϣ����

	eText_friend_sprite_name = 801, //С��������
	eText_friend_sprite_tips = 802, //С����tips
	eText_friend_sprite_content = 803,

	eText_Mood_Text_TooLong = 804,	//���鳤�ȹ�����

	eText_Button_Tip_Mood = 805, //����ͳƺű༭
	eText_Button_Tip_AddFriend = 806, //��Ӻ���
	eText_Button_Tip_RemoveFriend = 807, //ɾ������
	eText_Button_Tip_AddHeimingdan = 808, //��Ӻ�����
	eText_Button_Tip_Search = 809, //���Ѳ�ѯ
	eText_Button_Tip_AddClass = 810, //���Ӻ��ѷ���
	eText_Friend_AddGroupMax  = 811, //���������Ѿ�Ϊ���ֵ
	eText_Friend_FindPlayerMax = 812, //��Ҵ���30������ʹ�ò�ѯ

	//��װ��ʾ
	eChangeSuitFail                   = 900,//��װʧ��
	eChangeSuitSuccess                = 901,//��װ�ɹ�
	eChangeSuitCD                     = 902,//���Ժ��ٴγ���
	eChangeSuitSave                   = 903,//����ɹ�

	eText_ExpressionAction_CoolDown	  = 904, // ����̫�죬���Ժ��ٴγ���
	eText_PreventWallow_Account		  = 906, // ������ϵͳ��ʾ:�����ʺ��ѱ����������

	eText_Rank_Level		  = 910, //<String Id="910" Value="������¼�ȼ�����ǰ200������ң�������ڱ����������뵽����"/>
	eText_Rank_Fortune		  = 911, //<String Id="911" Value="������¼�Ƹ�����ǰ200������ң�������ڱ����������뵽����"/>
	eText_Rank_Fame		  = 912, //<String Id="912" Value="������¼��������ǰ200������ң�������ڱ����������뵽����"/>
	eText_Rank_Honor		  = 913, //<String Id="913" Value="������¼��������ǰ200������ң�������ڱ����������뵽����"/>
	eText_Rank_Offer		  = 914, //<String Id="914" Value="������¼�ﹱ����ǰ200������ң�������ڱ����������뵽����"/>
	eText_Rank_Charm		  = 915, //<String Id="915" Value="������¼��������ǰ200������ң�������ڱ����������뵽����"/>
	eText_Rank_PK		  = 916, //<String Id="916" Value="������¼��������ǰ200������ң�������ڱ����������뵽����"/>                
	eText_Rank_Kill		  = 917, //<String Id="917" Value="������¼ɱ������ǰ200������ң�������ڱ����������뵽����"/>
	eText_Rank_GuildPower		  = 918, //<String Id="918" Value="������¼�������ǰ200���İ�ᣬ������ڱ����������뵽����"/>
	eText_Rank_CountryPower		  = 919, //<String Id="919" Value="������¼����ʵ��������������ڱ����������뵽����"/>
	eText_Rank_Rose		  = 920, //<String Id="920" Value="������¼õ������ǰ200������ң�������ڱ����������뵽����"/>
	eText_Rank_Love		  = 921, //<String Id="921" Value="������¼��������ǰ200������ң�������ڱ����������뵽����"/>
	eText_Rank_Teacher		  = 922, //<String Id="922" Value="������¼��ʦʵ������ǰ200������ң�������ڱ����������뵽����"/>
	eText_Rank_BattleLevel		  = 923, //<String Id="923" Value="������¼ս���ȼ�����ǰ200������ң�������ڱ����������뵽����"/>
	eText_Rank_BattlePoint		  = 924, //<String Id="924" Value="������¼ս����������ǰ200������ң�������ڱ����������뵽����"/>
	eText_Rank_Intelligence		  = 925, //<String Id="925" Value="������¼������������ǰ200������ң�������ڱ����������뵽����"/>
	eText_Rank_Fast		  = 926, //<String Id="926" Value="������¼����ӱ�����ǰ200������ң�������ڱ����������뵽����"/>
	eText_Rank_Mount		  = 927, //<String Id="927" Value="������¼������������ǰ200������ң�������ڱ����������뵽����"/>
	eText_Rank_Hero		  = 928, //<String Id="928" Value="������¼Ⱥ��߱������ǰ200������ң�������ڱ����������뵽����"/>
	eText_Rank_Horn		  = 929, //<String Id="929" Value="������¼С��������ǰ200������ң�������ڱ����������뵽����"/>
	eText_Rank_Firework		  = 930, //<String Id="930" Value="������¼�̻�����ǰ200������ң�������ڱ����������뵽����"/>
	eText_Rank_Jiangzhou		  = 931, //<String Id="931" Value="������¼���ݽٷ�������ǰ200������ң�������ڱ����������뵽����"/>
	eText_Rank_Shihuang		  = 932, //<String Id="932" Value="������¼��ʼ��������ǰ200������ң�������ڱ����������뵽����"/>
	eText_Rank_Wanghai		  = 933, //<String Id="933" Value="������¼��Ԩ��������ǰ200������ң�������ڱ����������뵽����"/>
	eText_Rank_Qixing		  = 934, //<String Id="934" Value="������¼ҹ����������ǰ200������ң�������ڱ����������뵽����"/>
	eText_Rank_Baihu		  = 935, //<String Id="935" Value="������¼�׻�������ǰ200������ң�������ڱ����������뵽����"/>
	eText_Rank_Qinlong		  = 936, //<String Id="936" Value="������¼����������ǰ200������ң�������ڱ����������뵽����"/>
	eText_Rank_Fenghuang		  = 937, //<String Id="937" Value="������¼���ɽ����ǰ200������ң�������ڱ����������뵽����"/>
	eText_Rank_Xuanwu		  = 938, //<String Id="938" Value="������¼���䵺����ǰ200������ң�������ڱ����������뵽����"/>
	eText_Rank_GuildPoint	= 939, //<String Id="939" Value="������¼���ɻ�������ǰ200���İ��ɣ������Բ鿴���ɻ���������Ϣ��"/>

	eText_Ralation_AddRelationCoolTime = 950,//<String Id="950" Value="������Ҫ�Ⱥ�%d:%d:%d�������%s��ϵ��"/>
	eText_Ralation_Marriage = 951,//<String Id="951" Value="����"/>
	eText_Ralation_Teacher = 952,//<String Id="952" Value="ʦ��"/>
	eText_Ralation_Student = 953,//<String Id="953" Value="ͽ��"/>
	eText_Ralation_Brother = 954,//<String Id="954" Value="����ֵ�"/>
	eText_Ralation_Husband = 955,//<String Id="954" Value="�ɷ�"/>
	eText_Ralation_Wife = 956,//<String Id="954" Value="����"/>

	eText_Guild_Announcement = 960,	//��ṫ����ʾ
	eText_Guild_Creed = 961,	//�����ּ��ʾ
	eText_Guild_TellCreed = 962, //�޸İ����ּ����ʾ
	eText_Guild_Creed_Cd_Failed = 963, //cdʱ��δ�������ܸ��İ����ּ
	eText_Guild_Creed_Money_Failed = 964, //��Ǯ���������ܸ��İ����ּ

	eText_Bull					= 1000,				//�����桿
	eText_SystemBull            =1001,            //��ϵͳ��
	eText_Chat_0                =1002,            //�����
	eText_Chat_2                = 1004,            //�����顿
	eText_Chat_3                = 1005,            //�����ɡ�
	eText_Chat_4                = 1006,            //�����ɡ�
	eText_Chat_5                = 1007,            //�����硿
	eText_Chat_6                = 1008,            //��������
	eChatType_Normal                = 1009,    // ����
	eChatType_Guild                    = 1010,    // ����
	eChatType_Team                    = 1011,    // ����
	eChatType_Private                = 1012,    // ����
	//     eChatType_GM                    = 1013,    // GM
	eChatType_Shout				=1014,//����    
	eChatType_HightShout		=1015,//����    
	eText_Chat_Alignment        = 1016,            //��ͬ�ˡ�
	eChatType_Alignment			=1017,//ͬ��    
	eText_ElementSuitArmour		= 1018,	//������װ
	eText_SkillSuitArmour		= 1019,	//������װ
	eText_Chat_ZhenYing			= 1020, //����Ӫ��
	eChatType_ZhenYing			= 1021, //��Ӫ
	eChatType_XiaoLaBa			= 1025, //С����ͼ��
	eChatType_Near              = 1026, ////��������
	eChatType_Gang              = 1027, //[����ͼƬ]

	eServer_chat_particular_vip1            = 1029,    //С����Ϣ1
	eChatType_CountryString					= 1032,    // �����ִ�
	eChatType_Country					= 1034,    // ����ͼ��
	eChatType_GuanYuan					= 1035,    // ��Աͼ��
	//eClinet_marry_husband            = 1039,    //���Ϲ�
	//eClinet_marry_wife                = 1040,    //������
	//eClient_prentice                = 1041,    //��ͽ��
	eClient_Private_Begin               = 1042, //��~
	eClient_Chat_DuiNiShuo            = 1043,    //_������˵:
	eClient_Chat_NiDui            = 1044,    //��ԡ�~
	eClient_Chat_Shuo            = 1045,    //_��˵:
	eClient_Chat_function_4            = 1046,    //��
	eText_Chat_Spec_LeftMark            = 1047,    //��
	eText_Chat_Spec_RightMark            = 1048,    //��
	eClient_Chat_Begin            = 1049,    //:
	eClient_Chat_Head_End            = 1050,    //_��:
	eClient_Player_Name_End            = 1051,    //]
	//     eClient_AddInfo_2slk_147        = 1052,        //%s����˵:%s\n 

	eText_YouGetXGlory					= 1056,		// ������%d������		
	eText_YouGetXCountryScore			= 1057,		// ������%d���ս����
	eText_YouLoseXGlory					= 1058,		// ��ʧȥ��%d������
	eText_YouLoseXCountryScore			= 1059,		// ��ʧȥ��%d���ս����
	//////////////////////////////////
	///�ƺ�
	eTitle_TileNotExist					= 1060,		// û�д˳ƺ�
	eTitle_AlreadyExist					= 1061,		// �Ѿ�ӵ�иóƺ���
	eTitle_ErrorId						= 1062,		// ����ĳƺ�
	eTitle_Full							= 1063,		// �ƺ���������
	eTitle_UnknownError					= 1064,		// δ֪�ĳƺ�
	eTitle_RemoveSuccess				= 1065,		// �ƺ��Ƴ��ɹ�
	eTitle_AddSuccess					= 1066,		// �ƺ���ӳɹ�
	eTitle_CannotUplevel				= 1067,		// �ƺ�[%s]��������
	eTitle_NextTitleName				= 1068,		// �ƺ�[%s]

	eText_YouGetXExploit				= 1069,		// ������%d�㹦ѫ
	eText_YouGetXReputation				= 1070,		// ������%d������
	eText_YouLoseXExploit				= 1071,		// ��ʧȥ��%d�㹦ѫ
	eText_YouLoseXReputation			= 1072,		// ��ʧȥ��%d������
	eText_ChatSkillLevelUp				= 1073,		// %s�ȼ�������%d��
	eText_LifeSkillLevelupPoint			= 1074,		// %s������%d��
	/////////////////////////////////
	///�����Ȳ���
	eText_CaiKuangSkillPoint			= 1075,		// �ɿ�
	eText_CaiYaoSkillPoint				= 1076,		// ��ҩ

	eText_YouGetGuildOffer				= 1077,		// ������%d��ﹱ
	eText_YouLoseGuildOffer				= 1078,		// ��ʧȥ��%d��ﹱ
	eExchange_NotGuildOffer				= 1079,		// �ﹱ���������ܽ��д������
	eText_YouGetAreaReputation			= 1080,		// ������%d��%s����
	eText_YouGet						= 1081,		// ������
	eText_TitleNoUpdate                 = 1082,     //�óƺ��޷�����
	eText_WeiWang1						= 1083,		// ����
	eText_JiaoZiGet                     = 1084,     //�����%s
	eText_JiaoZiLost                    = 1085,     //ʧȥ��%s
	eText_JiaoZiGold                    = 1086,     //����
	eText_JiaoZiSilver                  = 1087,     //������
	eText_JiaoZiCopper                  = 1088,     //ͭ����

	eText_DaoHangStifle                 = 1091,     //����ѹ�� 
	eText_DaoHangResist                 = 1092,     //�����ֿ�

	eText_TalismanEquipSucess           = 1100,     //����װ���ɹ�
	eText_TalismanEquipFaild            = 1101,     //����װ��ʧ��
	eText_TalismanDaoHangNoEnough       = 1102,     //�������в���
	eText_TalismanUnEquipFaild          = 1103,     //����ж��ʧ��
	eText_TalismanDaoHangLimilt         = 1104,     //������������:%d
	eText_TalismanQuility               = 1105,     //����Ʒ��:%s
	eText_TalismanNormal                = 1106,     //����:��Ʒ
	eText_TalismanRight                 = 1107,     //����:��Ʒ
	eText_TalismanNicity                = 1108,     //����: ��Ʒ
	eText_TalismanImmortal              = 1109,     //����: ����
	eText_TalismanGold                  = 1110,     //����: ����
	eText_TalismanBound                 = 1111,     //δ��
	eText_TalismanNimBus                = 1112,     //����:%d/%d
	eText_TalismanNimBusRate            = 1113,     //�����ظ���:%d/��

	eText_TargetInTeam            =1301,    //�Է��������������У����ʧ��
	eText_FindNotPlayer            =1302,    //    �Է������ߣ����ʧ��
	eText_AskJoinTeam            =1305,    //    {#fffa00=  %s#}����������
	eText_TeamFail_TargetCancel            = 1306,    //�Է��ܾ����������
	eText_TargetTeamFull                =1307,    //    �Է�������������������ʧ��
	eText_TeamFull                =1308,    //    ���������ﵽ����,����ʧ��

	eText_InviteTeam				= 1309,//�������
	eText_ApplyTeam				= 1310,//�������
	eText_Team_CannotChangeTeamMode = 1311, // ֻ�жӳ����ܸ������ģʽ
	eText_Team_CannotChangeQuality  = 1312, // ֻ�жӳ����ܸ��ķ���Ʒ��
	eText_Team_NoApplyPages			= 1313, // 1/1
	eText_Team_HeadInviteFollow		= 1314, // �ӳ���������棿
	eText_Team_AgreeFollow			= 1315,	// %sͬ�����
	eText_Team_RefuseFollow			= 1316, // %s�ܾ�����
	eText_Team_CancelFollow			= 1317, // %sȡ������
	eText_Team_InviteFollowInfoSend = 1318,	// ���ѷ�����Ӹ�������
	eText_Team_LeaderCancelFollow	= 1319, // �ӳ�ȡ������
	eText_Team_JoinOneTeamSuccess	= 1320, // ���ѳɹ�������%s�Ķ���
	eText_Team_LeaveTeamYESNO		= 1321,	// ȷ���뿪����
	eText_Team_DisbandTeamYESNO		= 1322,	// ȷ��Ҫ��ɢ����
	eText_Team_KickSomeoneOffYESNO	= 1323,	// ��ȷ��Ҫ��%s�߳����飿
	eText_Team_PromotLeaderYESNO	= 1324, // ��ȷ��Ҫ������%s����Ϊ�ӳ���
	eText_Team_ClearListYESNO		= 1325, // ȷ��Ҫ��������б�
	eText_Team_NoTeam               = 1326, // ��û�ж���
	eText_NearPlayerTeam          = 1327, //�ж���
	eText_NearPlayerNoTeam            = 1328, //�޶���		

	eText_TeamFail_NotSameCountry           = 1350,    //��ͬ���Ҳ������

	eText_GetAchievement			= 1351, // ������%d�ɾ͵�

	eText_Search_OfflineOrNotExist	= 1402,//"{#ffffffff=�Է������߻��߲�����#}"/>
	eText_Team_Apply                        = 1403,    //�����������    
	eText_TeamFail                          = 1404,    //    
	eText_TeamScuscc                        = 1405,    //
	eText_AddTeam_Ask                       = 1406,    //���������飬�Ƿ�ͬ�⣿
	eUI_GuildCallOn                         = 1407,    //    
	eUI_SendTeam_fail                       = 1408,    //�����������ʧ��
	eUI_SendTeam                            = 1409,    //�������
	eText_NoneAddMe                         = 1410,    //���ܼ��Լ�Ϊ����
	eText_Friend							= 1411,	 //����
	eText_Chouren							= 1412,  //����
	//     eText_AddFriRepeat                    = 1411,    //�Ѿ������%sΪ����[ɾ]
	//     eText_FriNotOnline                    = 1412,    //���%s�����߻��������������[ɾ]
	eText_FriOutLine                    = 1413,  //�����Ѿ�����
	eText_FriCutDownLine                = 1414,    //(����)������
	eText_TeamFail_AssignMode            = 1415,    //����ģʽ�Ըģ����ʧ�� 
	eText_Server_TeamTargetResquesting    = 1416,    //��������ڱ�������...
	eText_Server_TeamRequestOnlyHeader    = 1417,    //ֻ�жӳ��ſ���������˼������...[ɾ]
	eText_ChouRenCutDownLine			=	1418,	//���� %s ������
	eText_TeamModeTips_FreeMode         = 1419,     //����ģʽ:����ʰȡ
	eText_TeamModeTips_AssignMode       = 1420,     //����ģʽ:�ӳ�����(%s)
	eText_TeamModeTips_TeamMode         = 1421,     //����ģʽ:�������(%s)
	eText_UpgradeTeam_Succeed            = 1422,    //%s������Ϊ�ӳ�
	eText_UpgradeTeam_Faild                = 1423,    //����%sΪ�ӳ�ʧ��
	eTextPlayer_GroupAssignMode0        = 1425,//%s�����������飬��ͬ����?\n�������ģʽΪ: {#FFFFFF00=����ģʽ#}
	eTextPlayer_GroupAssignMode1        = 1426,//%s�����������飬��ͬ����?\n�������ģʽΪ: {#FFFFFF00=����ģʽ#}
	eTextPlayer_GroupAssignMode2        = 1427,//%s�����������飬��ͬ����?\n�������ģʽΪ: {#FFFFFF00=�漴ģʽ#}
	eTextPlayer_GroupAssignMode3        = 1428,//%s�����������飬��ͬ����?\n�������ģʽΪ: {#FFFFFF00=����ģʽ#}
	eTextPlayer_Change_AssignMode0        = 1429,//ģʽ����Ϊ:{#FFFFFF00=����ģʽ#}
	eTextPlayer_Change_AssignMode1        = 1430,//ģʽ����Ϊ:{#FFFFFF00=����ģʽ#}
	eTextPlayer_Change_AssignMode2        = 1431,//ģʽ����Ϊ:{#FFFFFF00=�漴ģʽ#}
	eTextPlayer_Change_AssignMode3        = 1432,//ģʽ����Ϊ:{#FFFFFF00=����ģʽ#}
	eText_Client_show_assignMode_Freedom    = 1437, //��ǰ����Ϊ:����ģʽ
	eText_Client_show_assignMode_Team        = 1438, //��ǰ����Ϊ:����ģʽ
	eText_Client_show_assignMode_Random        = 1439, //��ǰ����Ϊ:���ģʽ
	eText_Client_show_assignMode_Assign        = 1440, //��ǰ����Ϊ:����ģʽ
	eClinet_CorpsAssignMode0        = 1441,//%s����������Ŷӣ���ͬ����?\n�Ŷӷ���ģʽΪ: {#FFFFFF00=����ģʽ#}
	eClinet_CorpsAssignMode1        = 1442,//%s����������Ŷӣ���ͬ����?\n�Ŷӷ���ģʽΪ: {#FFFFFF00=����ģʽ#}
	eClinet_CorpsAssignMode2        = 1443,//%s����������Ŷӣ���ͬ����?\n�Ŷӷ���ģʽΪ: {#FFFFFF00=�漴ģʽ#}
	eClinet_CorpsAssignMode3        = 1444,//%s����������Ŷӣ���ͬ����?\n�Ŷӷ���ģʽΪ: {#FFFFFF00=����ģʽ#}
	eText_ClientCrops_assignMode0        = 1449, //��ǰ�Ŷ�Ϊ:����ģʽ
	eText_ClientCrops_assignMode1        = 1450, //��ǰ�Ŷ�Ϊ:����ģʽ
	eText_ClientCrops_assignMode2        = 1451, //��ǰ�Ŷ�Ϊ:���ģʽ
	eText_ClientCrops_assignMode3        = 1452, //��ǰ�Ŷ�Ϊ:����ģʽ
	eTextServer_Refuse_Change_AssignMode    = 1453,//%s�ܾ��˴˴�ģʽ����
	eTextServer_All_Refuse_change_assignmode= 1454,//�����˶�����%s�����ڶ���.
	eTextServer_Item_Adscripte_People        = 1455,//%s������%s
	eTextServer_People_Agree_changemode        = 1456,//%sͬ���˴˴�ģʽ����
	eTextServer_Select_Get_assign            = 1457,//%sѡ������ȡ
	eTextServer_Select_Giveup_assign        = 1458,//%s������
	eCorps_KickCorper                = 1459, //���ܰ��Լ��߳�����
	eCorps_CorperCovManiple            = 1460, //���ܰ��Լ���ΪС�ӳ�
	eCorps_UpCorper                    = 1461, //����Ϊ�ų�����
	eClient_AddInfo_2slk_4         = 1462,        //������
	eCorps_MovePlayer                = 1463, //�ƶ������2��
	eCorps_AuthorityError            = 1464, //Ȩ�޲���
	eTextPlayer_InterchangeReqQue        = 1465,//%s �������д����գ��Ƿ�Ը��һ������?
	eTextPlayer_InterchangeReqMsg       = 1466,//�д�����
	eTextPlayer_Underdog                = 1467,//�������%s
	eClient_AddInfo_2slk_115        = 1468,        //����̫Զ�����������д衣
	eClient_AddInfo_2slk_116        = 1469,        //�Է������д��С�
	eClient_AddInfo_2slk_127        = 1470,        //%s���д���սʤ��%s 
	eClient_AddInfo_2slk_129        = 1471,        //�������뿪�д�����,%d����㽫������� 
	eClient_Error_Me_InFightCanNotDuel        = 1472, // ս��״̬�����д�
	eClient_Error_Target_InFightCanNotDuel    = 1473, // �Է���ս��״̬�����д�
	eClient_AddInfo_2slk_128        = 1474,        //δ֪Ŀ�� 
	eText_Client_IsDel_Friend                = 1475,    //��ȷ��Ҫɾ��%s
	eText_Server2Client_FriendMoreMax        = 1476,    //���������Ѿ������������
	eTextGuild_Ban_Error                    = 1477,//��û�����𹫻��Ա��Ȩ�ޡ�
	eTextGuild_Ban_Check                    = 1478,//��ȷ��Ҫ��%s�����������
	eTextGuild_Leave_Check                  = 1479,//��ȷ��Ҫ�뿪������
	eTextGuild_Leave_MasterError            = 1480,//���ǻ᳤������ֱ���뿪���ᡣ
	eTextGuild_Disband_Error                = 1481,//��û�н�ɢ�����Ȩ�ޡ�
	eTextGuild_Disband_Check                = 1482,//��ȷ��Ҫ��ɢ���������
	eTextGuild_CreedForbindText	            = 1483,//������ּ�к��зǷ��ַ�
	eTextGuild_SetLevel_Error               = 1484,//��û�иı乫���Աְλ��Ȩ�ޡ�
	eTextGang_ZhuanRang						= 1485,//ȷ��Ҫת�ð��ɸ�{#fffa00=  %s#}��
	eTextGuild_Invite_Error                 = 1486,//��û�����빫���Ա��Ȩ�ޡ�
	eTextGuild_Create_Error_Name_Check      = 1487,//�������ƺ��зǷ��ַ���
	eTextGuild_Create_Error_Name_Length     = 1488,//�������Ƴ��ȳ������ơ�
	eTextGuild_Create_Error_Name_None       = 1489,//�������Ʋ���Ϊ�ա�
	eTextGuild_Create_Error_Influence_None  = 1490,//����������������Ϊ�ա�
	//     eTextGuild_Influence_Select             = 1491,//��ѡ�񹫻�����
	//     eTextGuild_Influence_One                = 1492,//ī��
	//     eTextGuild_Influence_Two                = 1493,//����
	eTextGuild_SetTitle_Error               = 1494,//��û�иı乫���Ա�ƺŵ�Ȩ�ޡ�
	eTextGuild_SetTitle_Check               = 1495,//��ȷ��Ҫ��{#FFFFD940=%s#}�ĳƺŶ�Ϊ{#FFd8ea62=%s#}��
	eTextGuild_GruntedRight_One             = 1496,//���ų�
	eTextGuild_GruntedRight_Two             = 1497,//�����ų�
	eTextGuild_GruntedRight_Three           = 1498,//��Ա
	//     eTextGuild_Rank_Mo_1                    = 1499,//ī��
	eTextGuild_Rank_Mo_2                    = 1500,//�ν�
	eTextGuild_Rank_Mo_3                    = 1501,//����
	eTextGuild_Rank_Mo_4                    = 1502,//����
	//     eTextGuild_Tips_NeedExp                 = 1503,//������ֵ
	//     eTextGuild_Tips_TotalCredit             = 1504,//�ۻ�����ֵ
	//     eTextGuild_Tips_SetPercent              = 1505,//���þ���ֵ���ױ���
	//     eTextGuild_Tips_Percent                 = 1506,//����ֵ���ױ���
	//     eTextGuild_Tips_GiveExp                 = 1507,//ֱ�Ӿ��׾���ֵ
	//     eTextGuild_Tips_GiveExpNum              = 1508,//���׾���ֵ����

	//     eTextGuild_GiveExp_Check                = 1510,//��ȷ��Ҫ��%d����ֵ���׸�����?
	//     eTextGuild_RongYu                       = 1511,//����ֵ��%d/%d��%0.2f����
	eTextGuild_GruntedRight_Set             = 1512,//%s������Ϊ%s
	eTextGuild_GruntedRight_Cancel          = 1513,//%s��%sְ�񱻽��
	eTextGuild_GruntedRight_SetMe           = 1514,//�㱻����Ϊ%s
	eTextGuild_GruntedRight_CancelMe        = 1515,//���%sְ�񱻽��
	//     eText_NoInfluence                       = 1514,//����Ӫ

	//     eTeam_UpManiple                   = 1516,    //%s ������Ϊ %d С�Ӷӳ�
	//     eTeam_DownManiple               = 1517,    //%s ����Ϊ С�Ӷ�Ա
	eTeam_OprError1                    = 1518,    //�˲���ֻ�ܶԵ���
	eGuild_ReqInvite                = 1519,    //%s��������� %s ����
	eClient_Frddlg_Fiendly          = 1520,    //%s\n�Ա�%s\n�ȼ���%d\nְҵ��%s\n�Ѻöȣ�%d/%d(%d)
	//     eServer_AddPersonInBlackList    = 1520,    //%s ������Ϊ������
	eServer_AddPersonInFriend        = 1521,    //%s ����Ϊ����
	eTip_Client_FriendListInfo        = 1522,    //<#fffcac01=�ȼ� %d\n<#fffcac01=ְҵ %s\n<#fffcac01=�Ա� %s\n<#fffcac01=���� %s\n<#fffcac01=PK %s\n
	eText_PKResult                  = 1523, //%s ɱ���� %s
	eText_PKResult_YouKillPlayer    = 1524, //��ɱ���� %s

	eText_FriendPointUp				= 1525,//���%s�����ܶ�������%d��
	//eClient_Frddlg_SendMegOutline    = 1525,    //������Ϣ����ѡ��һ������![ɾ]
	eClient_Frddlg_AddNotLaw        = 1526,    //�����벻�Ϸ�������������
	eClient_Frddlg_AddSomePerson    = 1527,    //�����%sΪ����
	eClient_Frddlg_SomePersonOnline = 1528,    //%������


	//eClient_Bargain_InBlackList        = 1532,    //�Է�����Ϊ������[ɾ]
	eClient_Deul_NoneAgreen            = 1533,    //�Է���ͬ������д�


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
	eClient_MonsterNameOnRegionMap          = 1560,//[%s]%s(%d��)
	eClient_MonsterNameOnRegionMap1          = 1561,//[%s]%s

	//     eClient_AddInfo_2slk_17        = 1569,        //���׾���ɹ���
	//     eClient_AddInfo_2slk_18        = 1570,        //��ʽ����(����ͼ��)
	//     eClient_AddInfo_2slk_19        = 1571,        //�ߴ����(����ͼ��)
	//     eClient_AddInfo_2slk_20        = 1572,        //ɫ�����(����ͼ��)
	//     eClient_AddInfo_2slk_21        = 1573,        //�ɹ�!(����ͼ��)
	//     eClient_AddInfo_2slk_22        = 1574,        //ʧ��(����ͼ��)


	//     eClient_AddInfo_2slk_120        = 1578,        //%s ������Ϊ�ų��� 

	eClient_MonsterTitle = 1562,     //%s��С���
	eClient_PlayerHideMode1 = 1563, //��ʾģʽ:��ʾȫ��
	eClient_PlayerHideMode2 = 1564, //��ʾģʽ:����ȫ��
	eClient_PlayerHideMode3 = 1565, //��ʾģʽ:��ʾ�������
	eClient_PlayerHideMode4 = 1566, //��ʾģʽ:��ʾ�й����





	eMessageBox_AgreeBeTeacher = 1590,//�Ƿ�ͬ���Ϊ%s��ʦ��
	eMessageBox_AgreeBeStudent = 1591,//�Ƿ�ͬ���Ϊ%s��ͽ��
	eInviteLeague = 1592,//��������: %s��������Ĺ�������
	eInviteLeagueCaption = 1593,//��������: ��������
	eDisadverseLeague = 1594,//%s ������������İ��ɹ����ƽ
	eDisadverseLeagueCaption = 1595,//����ж�: ���ɺ�ƽ
	eOneInvitePerTenMinute = 1596,//ʮ����֮��ֻ����ͬһ���ɷ���һ�ν������롣
	eOneDisadversePerTenMinute = 1597,//ʮ����֮��ֻ����ͬһ���ɷ���һ�������Ժ͡�
	eGuildPeaseInfo = 1598,//��İ��ɺ�%s���������Ժ͡�
	eGuildLoseLeague = 1599,//��İ��ɺ�%s���ɽ��ͬ�ˡ�
	eGuildLeagueBeyondMax = 1600,//ͬ�˹�ϵ�Ѿ��ﵽ���������
	eGuildEnemyBeyondMax = 1601,//�жԹ�ϵ�Ѿ��ﵽ���������

	eText_Team_ItemRollLevel    = 1602,//����Ʒ��:%s
	eText_TeamAssignMode_Free   = 1603,//����ʰȡ
	eText_TeamAssignMode_Team   = 1604,//�������
	eText_TeamAssignMode_Assign = 1605,//�ӳ�����
	eText_TeamBoultResult_Choose    = 1606,//%s ѡ��������[%s]:%d��
	eText_TeamBoultResult_Abandon   = 1607,//%s ѡ���˷���[%s]
	eText_TeamBoultResult_Acquire   = 1608,//%s �����[%s]
	eText_TeamBoultResult_AllAbandon = 1609,//�����˶�������[%s]
	eText_TeamBoultResult_YouAbandon = 1610,//��ѡ���˷���[%s]

	eMessageBox_ReqMoveBlackList          = 1611, //���Ƿ�ȷ��Ҫ�Ƶ������� {#FFFFD940=%s#}��\n��ʦͽ����ż��ϵҪ�Ƶ���������,�����ϵ�踶��500��Ʊ�� 
	eText_AddFriendReq						= 1612,//������� %s ��Ϊ����
	eInviteAddFriendCaption                   = 1613, // ����Ӻ���: �Ӻ�������
	eInviteAddFriend                          = 1614, // "{#fffffa00=%s#}�Ѿ�����Ϊ���ѣ��Ƿ���ӶԷ�Ϊ��ĺ���"/>

	eText_AddFriInVendettaList                    = 1615,    // �Է�����ĳ����б���
	eText_AddFriInBlackList                    = 1616,    // �Է�����ĺ�������
	eText_AddFriAlreadyInBlackList                    = 1617,    // �Է��Ѿ�����ĺ�������
	eClient_AttackDieInfo_1                     = 1618, // �㱻 %s ɱ���� 
	eClient_AddFriInFriendList                      = 1619, // �Է��Ѿ�����ĺ����б��У�����ʧ��
	//     eClient_IsAddInviterAsFriend                = 1620, // �Ƿ�ӶԷ�Ϊ����

	eText_WordError							=1621,                //�ַ����Ϸ�

	eClient_Frddlg_AddFriendToBlack             = 1622,    // ����%s���������
	eClient_Frddlg_AddFriendBlackToVendetta             = 1623,    // ����%s��������б�

	eClient_AddFriend = 1625,//��������Ӻ��ѵ�����
	eTell_Client_ResumeGang = 1626,//����ָ�����ô��
	eTextGuild_DisplayName                  = 1627,//��%s��%s��
	eTextPlayer_WinOver                    = 1628,//��սʤ��%s
	eTextPlayer_AddGang                    = 1629,//������������������
	eText_FindGuildNpc						=1630,//�����ڻ�û�а��ɣ����NPC%s�Զ�Ѱ·�����ɹ���Ա����������

	eTextPlayer_AddBlackFriend                    = 1637,//������Ҫ������������������

	eText_InteractionFailed_TargetInFighting    = 1638, // �Է�����ս���У�����ʧ��
	eText_InteractionFailed_TargetToFarAway     = 1639, // �Է������Զ������ʧ��
	eText_InteractionFailed_TargetDead          = 1640, // �Է��Ѿ�����������ʧ��
	eText_InteractionFailed_TargetDisconnect    = 1641, // �Է������ߣ�����ʧ��
	eText_InteractionFailed_TargetNoReply       = 1642, // �Է�����Ӧ������ʧ��
	eText_InteractionFailed_TargetInMounting    = 1643, // �Է��������״̬������ʧ��
	eText_InteractionFailed_TargetInWater       = 1644, // �Է�������Ӿ״̬������ʧ��
	eText_InteractionFailed_TargetInLooting     = 1645, // �Է����ڲɼ�״̬������ʧ��
	eText_InteractionFailed_InMounting          = 1646, // ���״̬�޷�������������
	eText_InteractionFailed_InWater             = 1647, // ��Ӿ״̬�޷�������������
	eText_InteractionFailed_InLooting           = 1648, // �ɼ�״̬�޷�������������
	eText_InteractionFailed_IsDead              = 1649, // ����״̬�޷�������������
	eText_InteractionFaided_InFighting          = 1650, // ս��״̬�޷�������������
	eText_StallFailed_InBattle				    = 1651, // ս��ս��״̬�޷���̯
	eText_PrivateShopError_InSwin				= 1652, // ��Ӿ״̬�޷���̯
	eText_PrivateShopError_InPick				= 1653, // �ɼ�״̬�޷���̯
	eText_PrivateShopError_InDead				= 1654, // ����״̬�޷���̯

	eText_NewChannel							= 1655, // �½�����Ƶ��
	eText_Error_MaxChatChannel					= 1656, // Ƶ������

	eText_NoAchievementFinish					= 1657, // �����Ѿ�ȫ����ȡ

	eText_AddFriendFailed_SelfFull				= 1658, // �����б�������
	eText_AddFriendFailed_OtherFull				= 1659, // �Է������б�������
	eText_ShouldBeFriendFirst					= 1660, // �����Ǻ��ѹ�ϵ
	eText_YouAreInChouRenList					= 1661, // ���ڶԷ��ĳ����б��У�����ʧ��
	eText_AddRelationFailed						= 1662, // ���ʧ��
	eText_ExpActionFailed_InMounting			= 1663, // ���״̬�޷�ʹ�ñ��鶯��
	eText_ExpActionFailed_InWater				= 1664, // ��Ӿ״̬�޷�ʹ�ñ��鶯��
	eText_ExpActionFailed_InLooting				= 1665, // �ɼ�״̬�޷�ʹ�ñ��鶯��
	eText_ExpActionFailed_IsDead				= 1666, // ����״̬�޷�ʹ�ñ��鶯��
	eText_ExpActionFailed_InFighting			= 1667, // ս��״̬�޷�ʹ�ñ��鶯��
	eText_ExpActionFailed_InPrivateShop			= 1668, // ��̯״̬�޷�ʹ�ñ��鶯��
	eText_ExpActionFailed_TargetTooFar			= 1669, // �����Զ������ʧ��

	eTextGang_Master							= 1670,//����
	eTextGang_ViceMaster						= 1671,//������
	eTextTong_Master							= 1672,//����
	eTextTong_Member							= 1673,//�þ�Ӣ
	eTextGang_Member							= 1674,//��ͨ��Ա
	eTextTong_ZhuanRang							= 1675,//��ȷ��ת��{#fffa00=  %s#}���ø�{#fffa00=  %s#}��
	eTextTong_ModifyName						= 1676,//�����������޸ĵķ�������
	eTextTong_Exit								= 1677,//��ȷ��Ҫ�˳�������
	eTextTong_MasterChange						= 1678,//��ȷ��Ҫ��ȥ{#fffa00=  %s#}������ְλ��ί��{#fffa00=  %s#}Ϊ{#fffa00=  %s#}����ô��
	eTextGang_ViceMasterRemove					= 1679,//��ȷ����ȥ{#fffa00=  %s#}�ĸ�����ְλ��
	eTextGang_ViceMasterAssign					= 1680,//��ȷ��Ҫ����{#fffa00=  %s#}Ϊ��������
	eTextTong_Invite0							= 1681,//{#fffa00=  %s#}���������{#fffa00=  %s#}����{#fffa00=  %s#}��
	eTextTong_Invite1							= 1682,//{#fffa00=  %s#}���������{#fffa00=  %s#}��
	eTextTong_Remove							= 1683,//�㱻�Ƴ���%s��
	eTextTong_MaxNumber							= 1684,//%s ����������
	eTextGang_MaxRemove							= 1685,//���쿪����Ա�����ѵ���3������
	eTextTong_ExitError24						= 1686,//�������24Сʱ���޷��˳�
	eTextTong_MaxModifyName						= 1687,//�����޸ķ��������ѵ���1������
	eTextTong_ShowAllMember						= 1688,//��ʾȫ��
	eTextTong_ViceMasterChange					= 1689,//��ȷ��Ҫ��ȥ{#fffa00=  %s#}�ĸ�����ְλ��ί��{#fffa00=  %s#}Ϊ{#fffa00=  %s#}Ϊ������ô��
	eTextTong_ZhuangRangViceMaster				= 1690,//��ȷ��ת�ø�������{#fffa00=  %s#}��
	eTextDefautTongOneName						= 1691,//����1
	eTextDefautTongTwoName						= 1692,//����2
	eTextDefautTongThreeName					= 1693,//����3
	eTextDefautTongFourName						= 1694,//����4
	eTextDefautTongFiveName						= 1695,//����5
	eTextDefautTongSixName						= 1696,//����6
	eTextDefautTongSevenName					= 1697,//����7
	eTextDefautTongEightName					= 1698,//����8
	eTextDefautTongNineName						= 1699,//����9
	eTextDefautTongTenName						= 1700,//����10

	eErrorAlreadyInGang							= 1710,//�Է��������������
	eTextTong_MasterRemove						= 1711,//��ȷ��Ҫ��ȥ{#fffa00=  %s#}��{#fffa00=  %s#}������ְλô��
	eErrorGangMaxNumber							= 1712,//���������������
	eErrorGangName								= 1713,//�˰�����Ѿ���ʹ��
	eErrorAlreadyInThisGang						= 1714,//��������ڱ������
	eTextJoinMyGang								= 1715,//%s������
	//��1716�ֶ���string ���Ѿ�����,��Ȼ�����ﲢ������
	eText_GangPlayerReach10				= 1717,// ���~%s_ �ﵽ30����������������

	eText_NoXiaoLaBaForShout					= 1801,//����û��С���ȣ��޷����к���

	//---------------------- ������� -----------------------
	eText_BargainFailed_SelfInTrade             = 1850, // �������ڽ�����
	eText_BargainFailed_OppoInTrade             = 1851, // �Է����ڽ�����
	eText_BargainFailed_SelfInStallage          = 1852, // ��̯ʱ�޷�����
	eText_BargainFailed_OppoInStallage          = 1853, // �Է����ڰ�̯��
	eText_BargainFailed_OppoOutOfRange          = 1854, // �Է�û���ڽ��׷�Χ��
	eText_BargainFailed_OppoRefuse              = 1855, // �Է��ܾ�����
	eText_BargainSuccess_Request                = 1856, // �ѷ��ͽ�������
	eText_BargainSuccess_Finish                 = 1857, // ���׳ɹ�
	eText_BargainFailed_OutOfTime               = 1858, // ���׳�ʱ
	eText_BargainFailed_Cancel                  = 1859, // ����ȡ��
	eText_BargainFailed_Offline                 = 1860, // �������, ����ȡ��
	eText_BargainFailed_NoMoney                 = 1861, // û���㹻�Ľ�Ǯ
	eText_BargainFailed_NoGold                  = 1862, // û���㹻�Ľ�
	eText_BargainFailed_MoneyMax                = 1863, // ��Ǯ����������Я��������
	eText_BargainFailed_ItemError               = 1864, // ���׵ĵ�����Ϣ����ȷ
	eText_BargainFailed_ItemBind                = 1865, // ���׵ĵ��������������Ѱ�
	eText_BargainFailed_ItemOverdue             = 1866, // ���׵ĵ����ѹ���
	eText_BargainFailed_ItemExist               = 1867, // ���׵ĵ����Ѿ��ڽ���������
	eText_BargainFailed_SlotFilled              = 1868, // ����Ľ������Ѿ��е�����
	eText_BargainFailed_ItemNoTrade             = 1869, // ���׵ĵ��߲��ܱ�����
	eText_BargainFailed_PosError                = 1870, // ������λ�ô���
	eText_BargainFailed_PackFull                = 1871, // ��ͨ��������
	eText_BargainFailed_MaterialFull            = 1872, // ���ϱ�������
	eText_BargainFailed_HouseFull               = 1873, // ���ﱳ������
	eText_BargainFailed_ItemChange              = 1874, // ���׵����Ѿ����
	eText_BargainFailed_HouseBattle             = 1875, // �����ѳ�ս, ���ܽ���
	eText_BargainFailed_LevelLess               = 1876, // �ȼ�����10�������ܽ��׽�Ǯ
	eText_BargainFailed_HouseLevelHigh          = 1877, // ����ȼ�̫�ߣ����ܽ���
	eText_BargainFailed_PlayerPetLimit			= 1878, // �����Է���������,���ܽ���
	eText_BargainFailed_InFightState			= 1879,	// ����ս��״̬�޷�����
	eText_Bargain_AddFailed						= 1880, // �������ｻ�����ޣ��޷������
	eText_Bargain_TargetInFightState			= 1881, // �Է�����ս���У��޷�����
	//-------------------------------------------------------

	eText_TaskTrackAll                          = 1900, //ȫ��

	eText_MainMenu_Hotkey_State  = 1901, //<String Id="1901" Value="<#ff00ffff ����\n<#ffffffff ��ݼ�:C"/>
	eText_MainMenu_Hotkey_Skill	 = 1902, //<String Id="1902" Value="<#ff00ffff ����\n<#ffffffff ��ݼ�:X"/>
	eText_MainMenu_Hotkey_Vehicle = 1903, //<String Id="1903" Value="<#ff00ffff ����\n<#ffffffff ��ݼ�:H"/>
	eText_MainMenu_Hotkey_Country = 1904, //<String Id="1904" Value="<#ff00ffff ����\n<#ffffffff ��ݼ�:J"/>
	eText_MainMenu_Hotkey_Task = 1905, //<String Id="1905" Value="<#ff00ffff ����\n<#ffffffff ��ݼ�:L"/>
	eText_MainMenu_Hotkey_Pack = 1906, //<String Id="1906" Value="<#ff00ffff ����\n<#ffffffff ��ݼ�:B"/>
	eText_MainMenu_Hotkey_Fiend = 1907, //<String Id="1907" Value="<#ff00ffff �罻\n<#ffffffff ��ݼ�:F"/>
	eText_MainMenu_Hotkey_Guild = 1908, //<String Id="1908" Value="<#ff00ffff ���\n<#ffffffff ��ݼ�:G"/>
	eText_MainMenu_Hotkey_Team = 1909, //<String Id="1909" Value="<#ff00ffff ���\n<#ffffffff ��ݼ�:T"/>
	eText_MainMenu_Hotkey_System  = 1910, //<String Id="1910" Value="<#ff00ffff ϵͳ\n<#ffffffff ��ݼ�:Esc"/>

	eText_PropertyDlg_Tip_LiLiang_Warrior = 1911, //<String Id="1911" Value="<#ff00ffff ����\n<#ffffffff Ӱ����̹��������м���\n<#ffff8bd5 1����������0.3���̹�����0.01���м���"/>
	eText_PropertyDlg_Tip_LiLiang_Assassin = 1912, //<String Id="1912" Value="<#ff00ffff ����\n<#ffffffff Ӱ����̹��������м���\n<#ffff8bd5 1����������0.4���̹�����0.01���м���"/>
	eText_PropertyDlg_Tip_LiLiang_HunterTaoistMage	 = 1913, //<String Id="1913" Value="<#ff00ffff ����\n<#ffffffff Ӱ�����м���\n<#ffff8bd5 1����������0.02���м���"/>
	eText_PropertyDlg_Tip_MinJie_Hunter = 1914, //<String Id="1914" Value="<#ff00ffff ����\n<#ffffffff Ӱ��Զ�̹����Ͷ�������\n<#ffff8bd5 1����������0.4Զ�̹�����0.01��������"/>
	eText_PropertyDlg_Tip_MinJie_ExceptHunter  = 1915, //<String Id="1915" Value="<#ff00ffff ����\n<#ffffffff Ӱ���������\n<#ffff8bd5 1����������0.02��������"/>
	eText_PropertyDlg_Tip_ShuFa_Mage = 1916, //<String Id="1916" Value="<#ff00ffff �ǻ�\n<#ffffffff Ӱ��ħ��������ħ������\n<#ffff8bd5 1���ǻ�����0.4ħ��������17��ħ������"/>
	eText_PropertyDlg_Tip_ShuFa_Taoist = 1917, //<String Id="1917" Value="<#ff00ffff �ǻ�\n<#ffffffff Ӱ��ħ��������ħ������\n<#ffff8bd5 1���ǻ�����0.3ħ��������17��ħ������"/>
	eText_PropertyDlg_Tip_MPHuiFu_Warrior = 1918, //<String Id="1918" Value="<#ff00ffff ŭ���ظ�\n<#ffffffff Ӱ������ŭ���ظ��ٶ�"/>
	eText_PropertyDlg_Tip_MPHuiFu_Assassin = 1919, //<String Id="1919" Value="<#ff00ffff �����ظ�\n<#ffffffff Ӱ�����������ظ��ٶ�"/>
	eText_PropertyDlg_Tip_MPHuiFu_MageTaoist = 1920, //<String Id="1920" Value="<#ff00ffff ħ���ظ�\n<#ffffffff Ӱ������ħ���ظ��ٶ�"/>
	eText_PropertyDlg_Tip_MPHuiFu_Hunter = 1921, //<String Id="1921" Value="<#ff00ffff ��֧�ظ�\n<#ffffffff Ӱ�������֧�ظ��ٶ�"/>

	eText_Can_Attend_Task						=1922,	// %d���ɲμ�

	eText_PropertyDlg_Tip_Luqi						=1923,	//<String Id="1923" Value="{#ff00ffff ŭ��\n{#ffffffff ��ǰŭ��/ŭ������"/>
	eText_PropertyDlg_Tip_Power						=1924,	//<String Id="1924" Value="{#ff00ffff ����\n{#ffffffff ��ǰ����/��������"/>
	eText_PropertyDlg_Tip_Magic						=1925,	//<String Id="1925" Value="{#ff00ffff ����\n{#ffffffff ��ǰ����/��������"/>
	eText_PropertyDlg_Tip_Arrow						=1926,	//<String Id="1926" Value="{#ff00ffff ��֧\n{#ffffffff ��ǰ��֧/��֧����"/>

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

	eText_Mount_FeedError_FullHP = 1960, // ��������ֵ����





	eProfession_Warrior                         =2001,            //սʿ
	eProfession_Assassin                        =2002,            //��Ӱ
	eProfession_Mage                            =2003,            //��ʦ
	eProfession_Hunter                          =2004,            //����
	eProfession_Taoist                          =2005,            //��ʦ

	eProfession_Unknown                         =2008,            //δ֪

	eEquip_Durable                              =2009,            //�;�
	eUI_NeedLevel                               =2010,            //��Ҫ����
	eSex_Man                                    =2011,                        //
	eSex_FeMan                                  =2012,
	eUI_NeedSex                                 =2013,    
	eNeed_Profession                            =2014,                //ְҵ����
	eText_EquipLimit		                    =2015,          // װ������:

	eText_SuitSkill							    = 2017, // ��װ����:
	eText_Suit							        = 2018, // ��װ:
	eTextPlayer_EquipFaild                      = 2019, ////װ��ʧ��
	eText_PartitionLine                         = 2020, //-------------------------        
	eUI_TipsSuit                                = 2021,        //��װ˵��:
	eTextPlayer_Faild                           = 2022,// ʧ��
	eText_IT_MATERIAL                           = 2023,        //ԭ����
	eText_IT_RESTORE                            = 2024,        //����Ʒ
	eText_IT_GEM                                = 2025,        //��ʯ
	eText_IT_TASK                               = 2026,        //������Ʒ
	eText_IT_Reel							    = 2027,		// ����
	eText_Tip_GuildItem			                = 2028, // �����Ʒ
	eText_AddGuildFailed_TimeLimit		        = 2029, // �˰��24Сʱ���޷��ٴμ�����
	eUI_SoulBound                               = 2030, //װ����
	eUI_SoulBoundedCanotDo                      = 2031, //
	eTip_BelongerDone                           = 2032,//���й���
	eUnsb_Suc                                   = 2033, //����ɹ�
	eUnsb_NotBound                              = 2034,//��Ʒû�а�
	eSing_UnSoulBound                           = 2035,
	eClient_Target_Hp_Percent                   = 2036,    //%4.1f ��
	eTip_PickBound					            = 2037, //ʰȡ���

	//     eMouseOnUI_Player_Police        = 2037,    //{#fff6e2cd=%s#}\\n{#fff6e2cd=�ȼ� %d#}
	//     eMouseOnUI_Player_Normal        = 2038,    //{#fff6e2cd=%s#}\\n{#fff6e2cd=�ȼ� %d#}
	//     eMouseOnUI_Player_Attacker        = 2039,    //{#fff6e2cd=%s#}\\n{#fff6e2cd=�ȼ� %d#}
	//     eMouseOnUI_Player_Killer1        = 2040,    //{#fff6e2cd=%s#}\\n{#fff6e2cd=�ȼ� %d#}
	//     eMouseOnUI_Player_Killer2        = 2041,    //{#fff6e2cd=%s#}\\n{#fff6e2cd=�ȼ� %d#}
	//     eMouseOnUI_Player_Killer3        = 2042,    //{#fff6e2cd=%s#}\\n{#fff6e2cd=�ȼ� %d#}
	//     eMouseOnUI_Player_Killer4        = 2043,    //{#fff6e2cd=%s#}\\n{#fff6e2cd=�ȼ� %d#}
	//     eMouseOnUI_Player_Killer5        = 2044,    //{#fff6e2cd=%s#}\\n{#fff6e2cd=�ȼ� %d#}
	//     eMouseOnUI_Npc_Normal            = 2045,    //{#FFfbd860=%s#}\\n{#FFfbd860=�ȼ� %d#}
	//     eMouseOnUI_Monster_Material        = 2046,    //{#ffbfff00=%s#}\\n{#ffbfff00=�ȼ� %d#}
	//     eMouseOnUI_Monster_Initiative    = 2047,    //{#ffff7200=%s#}\\n{#ffff7200=�ȼ� %d#}
	// //     eMouseOnUI_Monster_Passivity    = 2048,    //{#ffd0d0d0=%s#}\\n{#ffd0d0d0=�ȼ� %d#}
	//     eTipText_base_Overdue                    = 2049,    //    %d/%d/%d %d:%d
	//     eSystemInfo_Overdue_InPack                = 2050, //�ڰ���������ڵ���Ʒ
	//     eSystemInfo_Overdue_InStorage            = 2051, //��Storage������ڵ���Ʒ
	//     eSystemInfo_Overdue_InPrivateShop        = 2052, //��PrivateShop����ڵ���Ʒ
	//     eSystemInfo_Overdue_InCompound            = 2053, //��InCompound������ڵ���Ʒ
	//     eSystemInfo_Overdue_InItensify            = 2054, //��Intensify������ڵ���Ʒ
	//     eSystemInfo_Overdue_InReduce            = 2055, //��Reduce������ڵ���Ʒ
	//     eSystemInfo_Overdue_InUnSoul            = 2056, //��Reduce������ڵ���Ʒ
	//     eSystemInfo_Overdue_InEquip                = 2057, //��Reduce������ڵ���Ʒ
	//     eSystemInfo_Overdue_InLockIntensicfy = 2058,//��LockIntensify������ڵ���Ʒ



	/////////////////////////////////
	///�˶�������Ҫ����
	eEquipType_hair                       = 2063,	//ͷ��
	eEquipType_helmet					 = 2064,	//ͷ��
	eEquipType_face                       = 2065,	//��
	eEquipType_armour					 = 2066,	//�·�
	eEquipType_glove		                 = 2067,	//����
	eEquipType_shoe                       = 2068,	//Ь��
	eEquipType_rhanditem		             = 2069,	//������Ʒ
	//eEquipType_lhanditem			         = 2070,	//������Ʒ
	eEquipType_headwear                   = 2071,	//ͷ��
	//eEquipType_HandShiedld                = 2072,	//����
	eEquipType_Shoulder                   = 2073,	//���
	eEquipType_Trousers                   = 2074,	//����
	eEquipType_accouterment               = 2075,	//��Ʒ
	eEquipType_ring                       = 2076,	//��ָ
	//eEquipType_bangle                     = 2077,	//ѫ��
	eEquipType_necklace                   = 2078,	//����
	eEquipType_sash                       = 2079,	//����
	//eEquipType_TaositShild                = 2080,	//����
	eWeapon_Spear					 = 2081,	//ǹ
	eWeapon_Staff					 = 2082,	//��
	eWeapon_Fan						 = 2083,    //��
	eWeapon_Sword					 = 2084,    //��
	eWeapon_Bow						 = 2085,	//��

	///�������ö���
	eUI_SillTyps_TargetType			 =    2100,        //���ö���:

	eUI_SillTyps_Target_no			  =    2101,        //��Ŀ��
	eUI_SillTyps_Target_myself		  =    2102,        //�Լ�
	eUI_SillTyps_Target_friend		  =    2103,        //�Լ�\����
	eUI_SillTyps_Target_normalplayer   =    2104,        //��ͨ���
	eUI_SillTyps_Target_enemy		  =    2105,        //����
	eUI_SillTyps_Target_dead			  =    2106,        //����Ŀ��
	eUI_SillTyps_Target_herb			  =    2107,        //��ҩ:
	eUI_SillTyps_Target_mine           =    2108,        //��ʯ
	eUI_SillTyps_Target_wood           =    2109,        //ľͷ
	eUI_SillTyps_Target_treasure       =    2110,        //����
	eUI_SillTyps_Target_pet            =    2111,        //����
	eUI_SillTyps_Target_all            =    2112,        //������
	eUI_SillTyps_Target_tream          =    2113,        //����
	eUI_SillTyps_Target_mount          =    2114,        //����
	eUI_SillTyps_Target_guild		  =    2115,		//����Ա

	eText_Day						= 2116,			// ��
	eText_Hour						= 2117,			// Сʱ

	eTip_sAddDaoxing					= 2118,	//����
	eTip_sAddBreakStrike				= 2119, //�Ƽ��˺�
	eTip_sAddStabStrike					= 2120, //�ᴩ�˺�
	eTip_sAddElementStrike				= 2121, //Ԫ���˺�
	eTip_sAddToxinStrike				= 2122, //�����˺�
	eTip_sAddSpiritStrike				= 2123, //�����˺�
	eTip_sAddBreakResist				= 2124, //�Ƽ׿���
	eTip_sAddStabResist					= 2125, //�ᴩ����
	eTip_sAddElementResist				= 2126, //Ԫ�ؿ���
	eTip_sAddToxinResist				= 2127, //���ؿ���
	eTip_sAddSpiritResist				= 2128, //������


	eText_NotSatisfySuitSkillCondition =    2201,		//����װ����Ӧ����װ 

	eText_Debuf_Giddy                       = 2230, // ѣ��
	eText_Debuf_Afraid                      = 2231, // �־�
	eText_Debuf_Stand                       = 2232, // ����
	eText_Debuf_Torpid                      = 2233, // ��Ĭ
	eText_Debuf_Slowdown                    = 2234, // ����

	eText_Buf_DamageDerate                  = 2235, // �˺�����

	eText_Buf_ContBeMagAttack             = 2238, // ħ������ (���ܱ�ħ������)
	eText_Buf_ContBePhyAttack             = 2239, // �������� �����ܱ���������

	eText_Buf_BaseMPPerDecrease             = 2240, // ÿ%s����ʧ����%s���޵�%d%%
	eText_Buf_Invisible                     = 2241, // ����
	eText_PlayAtt_Short                     = 2290, //����
	eText_PlayAtt_Long                      = 2291, //Զ��
	eText_PlayAtt_Magic                     = 2292, //ħ��
	eText_PlayDef_Short                     = 2293, //����
	eText_PlayDef_Long                      = 2294, //Զ��
	eText_PlayDef_Magic                     = 2295, //ħ��

	eText_Buf_DamageMianYiCnt               = 2296, //�˺����ߣ�%d��

	eText_NeedSkillExp                      = 2299, //��Ҫ���ܾ���:%d/%d
	eText_StatusTip_BaseMPPer               = 2300, // ÿ%s��ָ�����%s���޵�%d%%
	eText_Title_SellPrice		            = 2301, // �����۸�:
	eText_Buf_RestorMP                      = 2302,    //ÿ�� %0.1f ��ظ�����:%d ��\n
	eText_Skill_FrenzyPer                   = 2303,    //������
	eText_Skill_DelayTimeRestorHP           = 2304,    //ÿ�� %0.1f ��ظ�����:%d ��    \n
	eText_Skill_ChangeFrenzy                = 2305,    //��������
	eText_Buf_DecreaseMP                    = 2306,    //ÿ�� %0.1f ����ɵ��˾�����ʧ:%d ��    \n
	eText_Skill_DelayTimeChangeHP           = 2307,    //ÿ�� %0.1f����ɵ��������˺�:%d ��    \n
	eUI_stPlayAtt_Frost                     = 2308,    //��ϵ����
	eUI_ePlayIceDef                         = 2309,        //��ϵ����
	eText_Title_ItemType		            = 2310, // ��������:
	eText_Skill_OnePointAddRate             = 2311,    //ÿ�������ӵĹ�����ApointAddRate����ֵ*100
	eUI_ePlayPoisonDef                      = 2312,        //��ϵ����
	eUI_sDodge                              = 2313,        //�ر�        
	eUI_sExact                              = 2314,                //����
	eText_Skill_RestorHP                    = 2315,    //�����ָ�: %d %
	eUI_sMpMax                              = 2316,        //��������
	eText_Skill_ReboundHP                   = 2317,    //�����˺�: %d%%
	eText_Title_Minute			            = 2318, // ����	
	eUI_stPlayAtt_Poison                    = 2319,    //��ϵ����
	eUI_sAddDef                             = 2320, // ���ӷ���:
	eUI_Hurt_AddPhisycsDam		            = 2321,		// ���ӽ����˺�
	eUI_Hurt_AddMagicDam		            = 2322,		// ����Զ���˺�    
	eUI_nHpMax                              = 2323,        //��������
	eUI_sHpRestore                          = 2324,        //�����ظ�
	eUI_stChanged_MP                        = 2325,        //����ħ��
	eUI_stChanged_HP                        = 2326,        //��������
	eUI_stAttSpeedChanged                   = 2327,    //�����ٶ�
	eUI_stPlayAtt_Blaze                     = 2328,    //��ϵ����
	eUI_ePlayFireDef                        = 2329,  //��ϵ����
	eText_Title_Skill_Level		            = 2330, // ���ܵȼ�:
	eTip_Status_AddSkillExp              = 2331,    //���ܾ���ֵ����:%d ��
	eText_Skill_SkillCoolDownTime        = 2332,    //������ȴʱ��:%0.1f ��
	eTip_SkillLearnNeedExp               = 2333,    //��������ֵ��%d/%d��%0.2f����
	eText_Skill_AddRestorMP              = 2334,    //�ӿ�ظ�����: %d ��\n
	eText_Skill_AddRestorMPPer           = 2335,    //�ӿ�ظ������ٶ�: %d %%\n
	eText_Skill_AddRestorHP              = 2336,    //�ӿ�ظ�����: %d ��\n
	eText_Skill_AddRestorHPPer           = 2337,    //�ӿ�ظ������ٶ�: %d %%\n    
	eClient_AddInfo_2slk_119             = 2338,    //���ٳ��:%d ��ǰ���:%d
	eClient_AddInfo_2slk_118             = 2339,    //�����˺����:%d ��ǰ���:%d
	eUI_stChanged_HPMax                  = 2340,    //�������ֵ
	eText_AllPro                         = 2341,    //����ְҵ
	eUI_sPhysicsDef                      = 2342,    //���̷���
	eText_Skill_AllDamage                = 2343,    //ȫ�˺�    
	eUI_ePlayAtt_Physics                 = 2344,    //���̹���
	eUI_ePlayAtt_Magic                   = 2345,    //��������
	eText_Skill_AddPhyAtt                = 2346,    //����������: %d
	eText_Skill_AddPhyAttPer             = 2347,    //���������Ӱٷֱ�:%d%%
	eTip_Status_AddExp                   = 2348,    //����ֵ����:%d ��
	eUI_stPlayAtt_Thunder                = 2349,    //��ϵ����
	eUI_ePlayThunderDef                  = 2350,    //��ϵ����

	eTip_sNone					= 2351,		// ��ʼֵ
	eTip_sAddStrength			= 2352,		// ����
	eTip_sAddAgility			= 2353,		// ����
	eTip_sAddConstitution		= 2354,		// ���ʣ�������
	eTip_sAddIntelligence		= 2355,		// ������������
	eTip_sAddShortAttack    	= 2356,		// ����
	eTip_sAddLongAttack			= 2357,		// Զ��
	eTip_sAddMagicAttack		= 2358,		// ħ��
	eTip_sAddShortDefend		= 2359,		// ����
	eTip_sAddMagicDefend		= 2360,		// ħ��
	eTip_sAddLongDefend			= 2361,		// Զ��
	eTip_sAddExact      		= 2362,		// ����
	eTip_sAddDodge				= 2363,		// ����
	eTip_sAddCritical   		= 2364,		// ����
	eTip_sAddTenacity   		= 2365,		// ����
	eTip_sAddCriticalIntensity	= 2366,		// �����˺�
	eTip_sAddHPMax      		= 2367,		// ����
	eTip_sAddAPMax				= 2368,		// ����
	eTip_sAddBPMax				= 2369,		// �ӵ�
	eTip_sAddFPMax  			= 2370,		// ŭ��
	eTip_sAddEPMax          	= 2371,		// ����
	eTip_sAddMPMax      		= 2372,		// ħ��
	eTip_sAddBaseAttr   		= 2373,		// ȫ��������
	eTip_sAddExpPer 			= 2374,		// ������ �ٷֱ�
	eTip_sAddEnergyMax      	= 2375,		// ��������
	eTip_sAddMoveSpeed  		= 2376,		// �ƶ��ٶ� �����ֵ

	eTip_sAddHPRestoreRate      = 2377,     // ��Ѫ
	eTip_sAddMPRestoreRate      = 2378,     // ��ħ

	eText_Skill_BurnMpPerDamage   = 2379,   // ����ÿ���˺���ľ���: %d ��  \n
	eText_Skill_CostExPower	      = 2380,	// ���Ķ���
	eText_Skill_CostMP            = 2381,   // ���ľ���: %d
	eText_Skill_CostMPPer         = 2382,   // ���ľ���: %d %%
	eText_Skill_CostHP            = 2383,   // ��������: %d
	eText_Skill_CostHPPer         = 2384,   // ��������: %d %%
	eTip_LearnSkillLevelReq     = 2385,     // ��Ҫ�ȼ�:%ld\n
	eTip_LearnSkillLevelNeed    = 2386,     // ��Ҫ����:%ld��%s\n
	eText_Title_NeedSkillExp	= 2387,     // ��Ҫ���ܾ���:
	eTip_LearnSkillMoneyNeed    = 2388,     // ��Ҫ��Ǯ:%ld\n
	eText_Title_UseDistance		= 2389,     // ʩ�ž���:
	eText_Title_LearnCondition  = 2390,     // ѧϰ����:
	eTipForSkill_AddIntonateRate= 2391,     // ʩ��ʱ������
	eUI_stChanged_MPMax         = 2392,     // ħ�����ֵ
	eTipForSkill_DoNight        = 2393,     // ҹ����Ч
	eText_Title_UseImmediate	= 2394,     // ˲���ͷ�:
	eText_Skill_PrepTime        = 2395,     // ����ʱ��:%0.1f ��
	eText_Title_UseForever		= 2396,     // ����ʹ��
	eText_Title_SuitName		= 2397,     // ��װ����:
	eText_Title_LeftTime		= 2398,     // ʣ��ʱ��:
	eText_Skill_NotStudy        = 2399,     // δѧϰ��
	eText_Skill_ExtraHP         = 2400,     // ����˺�: %d %
	eText_Skill_BackStrikePer   = 2401,     // ���ӱ����˺�: %d%%
	eText_Skill_AddWardRate     = 2403,     // �����мܼ���AddWardRate
	eText_Skill_AddWardValue    = 2404,     // �����м�ֵAddWardValue
	eText_Title_Bound			= 2405,     // װ�����:
	eText_Title_WeaponType		= 2406,     // װ������:
	eText_Title_WeaponProperty	= 2407,	    // װ������:
	eText_Skill_DurationTime    = 2408,     //״̬����ʱ��: %0.1f ��\n
	eText_Skill_DurationActualTime = 2409, //״̬����ʱ��: %d Сʱ\n
	eText_Skill_MaxAbsorb          = 2410,     //�������
	eText_Bind_ByStarMove          = 2411,  // ���Ǻ��
	eText_TeamSkillFailed_CoolDown = 2412, //���鼼�ܴ�����ȴ��
	eText_TeamSkillFailed_NotAvailable = 2413, //δ������鼼�ܵ��ͷ�����
	eUI_SkillCategory_Team		= 2414,	// С�Ӽ���
	eUI_SkillCategory_Attack	= 2415,	// ��������
	eUI_SkillCategory_Passive	= 2416,	// ��������
	eUI_SkillCategory_Assistant	= 2417,	// ��������
	eTip_sCastSpeed             = 2419, // �����ٶ�

	//////////////////////////////////////////////////////////////////////////
	/// �������
	eText_GetJinAttribute		= 2420, //��ϲ���ܵ�����Ĵ͸����ɹ���װ�������ϡ�������
	eText_GetMuAttribute		= 2421, //��ϲ���ܵ�ľ��Ĵ͸����ɹ���װ�������ϡ�ľ������
	eText_GetShuiAttribute		= 2422, //��ϲ���ܵ�ˮ��Ĵ͸����ɹ���װ�������ϡ�ˮ������
	eText_GetHuoAttribute		= 2423, //��ϲ���ܵ�����Ĵ͸����ɹ���װ�������ϡ�������
	eText_GetTuAttribute		= 2424, //��ϲ���ܵ�����Ĵ͸����ɹ���װ�������ϡ���������
	eText_Error_ItemNotReady	= 2425, // ��ȷ�Ϸ�����װ����ָ���Ĳ���
	eText_Error_ItemNotElement	= 2426, // ��װ������������װ����
	eText_Error_ItemAlreadyDid	= 2427, // ��װ���Ѿ���������������
	eText_WuXing_Tip_Jin		= 2428,	// ����:�𣨴���ɫ��
	eText_WuXing_Tip_Mu			= 2429,	// ����:ľ������ɫ��
	eText_WuXing_Tip_Shui		= 2430, // ����:ˮ������ɫ��
	eText_WuXing_Tip_Huo		= 2431,	// ����:�𣨴���ɫ��
	eText_WuXing_Tip_Tu			= 2432,	// ����:��������ɫ��
	eText_Wuxing_Tip_JinHurt	= 2433,	// ������
	eText_Wuxing_Tip_MuHurt		= 2434,
	eText_Wuxing_Tip_ShuiHurt	= 2435,
	eText_Wuxing_Tip_HuoHurt	= 2436,
	eText_Wuxing_Tip_TuHurt		= 2437,
	eText_Error_NotEnoughMoney  = 2438,// û���㹻��Ǯ
	eText_Error_HaveNotElement	= 2439, // û����������, �������
	eText_Error_ClearCountLimit	= 2440, // һ��ֻ�����%d�� ö����Globaldef.h => ClearElementCount
	eText_Error_NotCheckupItem	= 2441,  // ���Ǽ������е���Ʒ
	eText_Error_NotClearItem	= 2442,    // ����������е���Ʒ
	eText_Error_LevelError		= 2443,      // ��Ʒ��װ���ȼ�����
	eText_Error_ClearSuccess	= 2444, // �����ɹ�
	eText_FiveXingSecret        = 2445, //ȫ���ᴿ+4/+5�󣬼������������ᴿ
	eText_FiveXingUpdateResult  = 2446, //�ᴿ�ȼ�:%d %s�����˺�:+%d
	eText_FiveXingChangeResult  = 2447,  //��������ת��Ϊ: %s
	eText_FiveXingJin           = 2448, //��
	eText_FiveXingMu            = 2449, //ľ
	eText_FiveXingShui          = 2450, //ˮ
	eText_FiveXingHuo           = 2451, //��
	eText_FiveXingTu            = 2452, //��
	eText_FiveXingUpdateTipJin  = 2453, //�������ᴿ(+%d):
	eText_FiveXingUpdateTipMu   = 2454, //ľ�����ᴿ(+%d):
	eText_FiveXingUpdateTipShui = 2455, //ˮ�����ᴿ(+%d):
	eText_FiveXingUpdateTipHuo  = 2456, //�������ᴿ(+%d):
	eText_FiveXingUpdateTipTu   = 2457, //�������ᴿ(+%d):
	eText_FiveXingDefaultTipJin = 2458, //#FFffff00������װȫ���ᴿ+3��+4��+5�󽫻ἤ����������
	eText_FiveXingDefaultTipMu  = 2459, //#FFffff00������װȫ���ᴿ+3��+4��+5�󽫻ἤ����������
	eText_FiveXingDefaultTipShui= 2460, //#FFffff00������װȫ���ᴿ+3��+4��+5�󽫻ἤ����������
	eText_FiveXingDefaultTipHuo = 2461, //#FFffff00������װȫ���ᴿ+3��+4��+5�󽫻ἤ����������
	eText_FiveXingDefaultTipTu  = 2462, //#FFffff00������װȫ���ᴿ+3��+4��+5�󽫻ἤ����������
	eClient_SendMailInfo        = 2465,        //�и���ʱ�������˽��޷�����ʼ���ȷ�����ͣ�

	eText_EquipUpgrade_Success  = 2470,		//���׳ɹ�
	eText_EquipUpgrade_Fail  = 2471,		//����ʧ��
	eText_EquipUpgrade_Cannot  = 2472,		//��װ���޷�����
	eText_EquipUpgrade_NoOptional  = 2473,		//δ����̳е��ߣ����׺󽫻����װ�����������ԣ��Ƿ������
	eText_EquipUpgrade_CanNotUpgrade  = 2474,		//�޷����׵���װ��
	eText_EquipUpgrade_LackMaterial  = 2475,		//���ϲ��㣬�޷�����
	eText_EquipUpgrade_ErrorMaterial  = 2476,		//���ϴ�������ʧ��
	eText_EquipUpgrade_ClearStarAttribute = 2477,	//������������������

	eText_NotSpecialRepair		 = 2490, // ����Ʒ�޷���������
	eText_NotNeedRepairFineEquip = 2491, // ��װ������������������������

	eText_stStrengthReq			= 2500,  //����
	eText_stMinjieReq		    = 2501,  //����
	eText_stTizhiReq			= 2502,  //����
	eText_stShufaReq			= 2503,  //����
	eText_stJinguReq			= 2504,  //���

	eText_StallFailed_AddItemError          = 2550, // ��̯λ�������Ʒʧ��
	eText_StallFailed_SlotAlready           = 2551, // ̯λ��λ���е��߳��ۣ��������
	eText_StallFailed_DataAlready           = 2552, // �˵����Ѿ�����ӵ�̯λ��

	eText_StallQuery_StallName = 2553,	//������
	eText_StallQuery_BossName = 2554, //������

	eText_StallFailed_AddBuyAllowStack      = 2560, // ֻ���չ��ɶѵ���Ʒ
	eText_Country_Free_NeedNotRemit         = 2561, // ����Ҫ����

	eText_Stall_TradeRecord_Sell            = 2602, // ~%s_ �����ĸ����̵깺���� %d �� [%s]��������� %s
	eText_Stall_TradeRecord_Buy             = 2603, // ~%s_ ���������� %d �� [%s]���������� %s
	eTextPlayer_CloseShop                   = 2604, //%s �ص����̵�!

	eExchange_Ask                           = 2607, // %s������,�Ƿ����!

	eText_ItemNoPlace                       = 2609, // ������û�п�λ����
	eText_ChangeSuitFail                    = 2610, // ��������������װ����װʧ��

	eClient_AddInfo_2slk_31                 = 2614, // ����Ʒ���ɽ���
	eClient_AddInfo_2slk_35                 = 2615, // �Բ���,����Ʒ���������̵�!
	eText_ThisItemCanNotDrop                = 2616, // ����Ʒ���ܱ�����
	eText_Stall_TipPrice                    = 2617, // ���ۼ۸�

	eUI_NotMemoy                            = 2619, // ��û���㹻��Ǯ!

	eText_StallFailed_NameError             = 2620, // ̯λ���ƷǷ�
	eText_StallFailed_VenderMoneyLess       = 2621, // û���㹻�Ľ�Ǯ�չ�̯λ�ϵ���Ʒ
	eText_StallFailed_VenderPackNoPlace     = 2622, // û���㹻�İ����ռ��չ����е���Ʒ
	eText_StallFailed_Offline               = 2623, // ̯���Ѿ���������
	eExChange_NoPermitInMorp                = 2624, // ����״̬�޷���̯
	eText_StallFailed_WealthProtect         = 2625, // �Ʋ�����ʱ���ڲ��ܰ�̯
	eText_StallFailed_EmptyStallage         = 2626, // ���ܿ���һ����̯λ
	eText_BargainFailed_InPrivateShop       = 2627, // ��̯״̬�޷�����
	eText_StallFailed_InBargaining          = 2628, // ����״̬�޷���̯
	eUI_SendExchange                        = 2629, // ���ͽ�������
	eUI_SendExchange_fail                   = 2630, // ���ͽ�������ʧ��
	eText_CanNotPushItemIntoStorage         = 2631, // ���ܰ���Ʒ����ֿ�
	eText_ItemHaveBeenLocked                = 2632, // ��Ʒ�Ѿ�����
	eText_ChangPrice                        = 2634, // �ı�ʹ��Ʒ�۸�
	eText_StallFailed_ItemNumError          = 2635, // ��Ʒ��������ȷ
	eText_StallFailed_VenderNoMoney         = 2636, // ̯��û���㹻�Ľ�Ǯ�չ���

	eText_Price_0                           = 2637, // �۸�
	eText_StallFailed_VenderNoGold          = 2638, // ̯��û���㹻�Ľ��չ���
	eText_StallFailed_VenderPackFull        = 2639, // ̯����������
	eExchange_UnKnown                       = 2640, // ����ʧ��
	eText_Client_Trade_Faild                = 2641, // ������ֹ
	eText_StallFailed_VenderHouseFull       = 2642, // ̯��������������, �����չ�
	eText_MoneyNotEnoungh                   = 2643, // ��Ǯ���㣬�޷����д˲���

	eText_Client_Trade_Faild_Distance       = 2646, // ����Ҿ����Զ,���ױ���ֹ
	eClient_AddInfo_2slk_10                 = 2647, // û�п�������Ʒ

	eText_StallFailed_TooMouchMoney         = 2648,	// ��̯��Ʒ����Я����Ǯ����
	eText_Player_Beyong_Max_Money           = 2649,	// �Է��Ľ�Ǯ���������Ͳֿ���ܽ�����ޣ�����ʧ��
	eText_StallFailed_StallageError         = 2650, // ̯λ���ݲ���ȷ, �����²鿴
	eText_StallFailed_ItemError             = 2651, // ��Ʒ���󣬲��ܹ���
	eText_StallFailed_StallageClose         = 2652, // ̯λ�ѹر�
	eText_StallFailed_PriceChange           = 2653, // ̯λ����Ʒ�۸��Ѹ���

	eExchange_NoJiaoziNoMoney               = 2654,
	eExchange_ExceedUpperLimit              = 2655,			// �����������ܳ���%d
	eExchange_NotLingPai	                = 2656,            // û������!
	eExchange_NotMoney                      = 2657,            // û���㹻Ǯ!
	eExchange_NotReputation                 = 2658,			// û���㹻����
	eExchange_NotExploit	                = 2659,			// û���㹻��ѫ
	//eUI_Bank_LevelUp_error                = 2658,        //������Ǯ����,�޷��������У�
	//eUI_Bank_LevelUp_Text_0               = 2659,        //������������Ҫ
	eText_ChangeHorseName                   = 2660, //�����������޸ĵ���������
	eUI_YouTo                               = 2661,            //����
	eText_ChangePetName                     = 2662,//�����������޸ĵ��ٻ�������
	//     eUI_GetGoldError_NotGold                = 2663,
	//     eShopCenterUI_GetYuanBao                = 2664, //��ȡһ����Ԫ��
	eText_Client_Trade_Faild_Ride           = 2665,    //�������ϲ��ɽ���,���ױ���ֹ
	eText_StallFailed_NoRide                = 2666, // ���״̬���ɰ�̯
	eClient_AddInfo_2slk_25                 = 2667,        //"�������ϲ��ɽ���!"
	//eText_BankTradeBankNotMoney           = 2668,//Ǯ����û��ô��Ǯ
	//eText_BankTradeUpgradeMax             = 2669,//Ǯ��������߼�
	//eUI_InputSaveMoney                    = 2670,    //����������Ǯ������
	eText_Input_SaveCnt                     = 2671,                //���������������Ʒ������
	//eUI_Take_Money                        = 2672,            //��������ȡǮ������
	eText_Sell_Price                        = 2673,        //���������ļ۸�

	//eText_Ask_BuyCnt                      = 2675,                //������Ҫ�������Ʒ����
	//eText_Input_MoveCnt                   = 2676,                //�������ƶ�������
	eText_EnterShopName                     = 2677,    //����д������̵������!
	eText_StallFailed_NoItemMoveWhenOpen    = 2678,        //"��ر��̵���ٲ���!"

	eClient_ShopCenterNotStock		        = 2679, // �̳�û�п��

	eUI_BuyConfirm            =2680,                //��ȷ��Ҫ������?

	//eUI_ShopNotItem            =2682,            //�̵�����û����ô����Ʒ
	eText_ShopRefeash        =2683,        //�̵��е���Ʒ��ˢ��!
	eCannotRepairFashion                  = 2684, //��������ʱװ
	//ePrivateShop_String0            = 2685,    //�Ƿ�鿴��%s���ĸ����̵ꣿ
	//eUI_InputGoldCovSilver    =         2686,//������Ҫ�һ���ҵ�����
	eText_OverCount            =2687,                //��������
	eText_Stallage_Default_Name             = 2688,	// %s ���̵�

	//eText_BankTradePlayerNotMoney        = 2691,//���û����ô��Ǯ
	//eText_BankTradeFalied                = 2692,//δ֪����

	//eUI_Bank_LevelUp_Text_1 =2694,        //Ǯ��ȷ����������?
	//eMsg_client_AddMoney = 2695,    //��ֵ
	eText_ItemMaxStoreNum                = 2696,//��Ʒ���洢��ĿΪ:
	eText_Client_Doyou_Mend_CostGold        = 2697,    //�������� %d �� %d ͭ,�Ƿ�ȷ������
	//eSing_client_C = 2698, //ͭ
	///////////////////////////////////////
	/// tipǰ׺
	//eTip_PreText_Normal						= 2698, // ����
	//eTip_PreText_Addition1					= 2699,	// ����1
	//eTip_PreText_Addition2					= 2700,	// ����2
	//eTip_PreText_Addition3					= 2701,	// ����3
	//eTip_PreText_Addition4					= 2702,	// ����4
	//eTip_PreText_Addition5					= 2703,	// ����5
	//eTip_PreText_Addition					    = 2704,	// ����
	//eTip_PreText_KaiGuang					    = 2705,	// ����
	//eTip_PreText_NoIdentify					= 2706, // δ����
	//eTip_PreText_NoKaiGuang					= 2707, // δ����

	eText_PrepareCost						= 2710, // �������

	eText_ExPower							= 2711, // ����

	eText_Item_CurPageStorageFull           = 2714, //  �ֿ⵱ǰҳ�������޷����д˲�����
	eText_Mount_StorageFull                 = 2715, // ����ֿ�����
	eText_Mount_CharCarryFull               = 2716, // ����Я�������Ѵ�����
	eText_Mount_InfoError                   = 2717, // ��ǰ������Ϣ����
	eText_Mount_ActivedNotAdmit             = 2718, // ��ս�����޷�����ֿ�
	eText_Mount_StorageToCharErr            = 2719, // �ֿ������޷�������������
	eText_Mount_LearnSkill_CarryLvlLess     = 2720, // ����Я���ȼ����� �޷�ѧϰ����
	eText_Mount_LearnSkill_LvlLess          = 2721, // ����ȼ����� �޷�ѧϰ����
	eText_Mount_LearnSkill_Failed           = 2722, // �޷�ѧϰ���＼��

	eExchange_GloryNotEnough					= 2725, // �������������ܽ��д˲���
	eText_Glory								= 2726, // ����

	eTip_Resist_Coma						= 2730,	// ���Կ���
	eTip_Resist_Dread						= 2731,	// �־忹��
	eTip_Resist_Silence						= 2732,	// ��Ĭ����
	eTip_Resist_Slow						= 2733,	// ���ٿ���

	eTip_sAddFPRestoreRate                  = 2734, // ŭ���ظ�
	eTip_sAddEPRestoreRate                  = 2735, // �����ظ�
	eTip_sAddAPRestoreRate                  = 2736, // ��֦�ظ�
	eTip_sAddBPRestoreRate                  = 2737, // ��ҩ�ظ� �ȴ�String���

	eText_InfoTip_TeamInvite				= 2800, // �������
	eText_InfoTip_FriendInvite				= 2801, // ��������
	eText_InfoTip_Convene					= 2802, // �ټ���
	eText_InfoTip_Raise						= 2803, // ����ļ��
	eText_InfoTip_PlayerLevelUp				= 2804, // ��������
	eText_InfoTip_PetLevelUp				= 2805, // ��������
	eText_InfoTip_FriendChat				= 2806, // ���ѵ���
	eText_InfoTip_ImpeachKing				= 2807, // ��������
	eText_InfoTip_AnswerQst					= 2808, // ����
	eText_InfoTip_GuildInvite				= 2809, // �������
	eText_InfoTip_GuildMasterConvene				= 2810, // �����ټ�
	eText_InfoTip_GuildRaise				= 2811 , //������


	eText_LevelUp_ExpNotEnough              = 2900, // ���鲻�����޷����� 
	eText_LearnSkill_LevelNotEnough         = 2901, // �ȼ������޷�ѧϰ����
	eText_LearnSkill_GoldNotEnough          = 2902, // ��Ǯ�����޷�ѧϰ����
	eText_LearnSkill_ExpNotEnough           = 2903, // ���鲻���޷�ѧϰ����
	eText_LearnSkill_NoLearn                = 2904, //�Ѿ�û�п�ѧϰ�ļ���

	eText_LearnXinFa_LevelNotEnough         = 2920, // �ȼ�����������
	eText_LearnXinFa_GoldNotEnough          = 2921, // ��Ǯ����������
	eText_LearnXinFa_ExpNotEnough			= 2922,	//���ܵ�������������
	eText_LearnXinFa_PreXinFaNotOk			= 2923,	//ǰ���ķ�����������
	eText_LearnXinFa_ProfessionNotOk		= 2924, //ְҵ����������
	eText_Configuration_XinFa_NotOk			= 2925,	//�ķ��������ļ�����
	eText_Configuration_Skill_NotOk			= 2926,	//���ܵ������ļ�����
	eText_LearnXinFa_Failure = 2927, //ѧϰ�ķ�ʧ��


	eWarning_CanNotPrivateChatBefore15			= 2980, //
	eWarning_CanNotMessageChatBefore15			= 2981, //
	eWarning_CanNotCountryChatBefore20			= 2982, //
	eWarning_CanNotPrivateChatToBefore15			= 2983, //
	eWarning_CanNotCountryChatNoCountry             = 2984, //û�й��Ҳ���ʹ�ù���Ƶ������
	eWarning_CanNotCountryGYChat                = 2985, //�㲻�ǹ��ҹ�Ա������ʹ�ô�Ƶ��
	eText_SkillCanNotDrag											=3000,//���������޷��϶�������λ��
	eUI_SkillLevelup														= 3001,//��ļ��ܵȼ������ˣ�
	eText_SkillLevelUp													= 3002,//���ܵȼ�������
	eText_SkillFailed_OnlyMounting							= 3003,//�ü���ֻ�����״̬��ʩ��
	eText_SkillFailed_NotCorrectProfession				= 3004,//�ü���ֻ��%sʹ��
	eText_MountAlreadyLearnSkill								= 3005,//�Ѿ�ѧ��ü��ܣ��޷��ٴ�ѧϰ
	eTextPlayer_Break													= 3006,//���
	eText_Get																	= 3007,//���
	//     eUI_SillTyps_TargetType        =    3008,        //���ö���:
	eText_SkillFailed_UnableOperateInCurrentState                = 3008, // �ڵ�ǰ״̬�£��޷����д˲���
	eText_Skill_ChaseTarget                     = 3009, // ��Ŀ������Զ��׷��Ŀ��
	eAttack_Error_SafeArea                      = 3010, //��ȫ�����޷�����
	eText_SkillFailed_MustAtBack                = 3011, // ������Ŀ�걳�����ʩ�Ŵ˼���
	eText_SkillFailed_CannotUsePhysicsSkill     = 3012, // ��ǰ״̬����ʹ��������
	eText_SkillFailed_CannotUseMagicSkill       = 3013, // ��ǰ״̬����ʹ��ħ������
	eText_SkillFailed_TooFar					= 3014,	// ��Ŀ������Զ���޷�ʩ�ż���
	eText_SkillFailed_TooClose					= 3015,	// ��Ŀ�����̫�����޷�ʩ�ż���
	eText_SkillFailed_NotEnoughMP				= 3016,	// �������㣬�޷�ʩ�Ŵ˼���
	eText_SkillFailed_NotEnoughHP				= 3017,	// ��Ѫ���㣬�޷�ʩ�Ŵ˼���
	eText_SkillFailed_NotEnoughExPower		    = 3018,	// �������㣬�޷�ʩ�Ŵ˼���
	eText_SkillFailed_WhenMounting				= 3019,	// ���״̬�£��޷�ʩ�Ŵ˼���
	eText_SkillFailed_NotCorrectTarget			= 3020,	// ���ܶԵ�ǰĿ��ʩ�Ŵ˼���
	eText_SkillFailed_NoTarget					= 3021,	// ��ѡ��һ��Ŀ����ʩ�ż���
	eText_SkillFailed_NeedWeapon				= 3022,	// û��װ���������޷�ʩ�Ŵ˼���
	eText_SkillFailed_WhenCoolDown				= 3023,	// ���ܴ�����ȴ�У��޷�ʩ��
	eText_SkillFailed_NotFaceToTarget			= 3024,	// ����Ҫ���Ŀ�����ʩ�Ŵ˼���
	eText_SkillFailed_CannotUseInFighting		= 3025, // �޷���ս��״̬��ʩ�Ŵ˼���
	eText_SkillFailed_UseOnlyInFighting			= 3026,	// ֻ�д���ս��״̬ʩ�Ŵ˼���
	eText_SkillFailed_Busy						= 3027,	// �Ѿ�����һ���������ڽ����У��޷�ʩ�Ŵ˼���
	eText_SkillFailed_LackOfSomeItem			= 3028,	// ��Ҫ��Ʒ����ʩ�Ŵ˼���
	eText_SkillFailed_HpLimit					= 3029,	// Ѫ������������
	eText_SkillFailed_NeedPet					= 3030,	// ��Ҫ���ٻ��޲���ʩ�Ŵ˼���
	eText_SkillFailed_CannotJump				= 3031,	// ��Ծ���޷�ʩ�Ŵ˼���
	eText_SkillFailed_InPrivateShop				= 3032,	// ��̯״̬���޷�ʩ�ż���

	eClient_AddInfo_2slk_125        = 3301,        //����[%s] 
	eClient_AddInfo_2slk_62        = 3302,        //"ȡ��[%s]����"
	//eClient_AddInfo_2slk_45        = 3303,        //����[%s]
	eClient_get_new_task                    = 3304,    //�½����� %s
	eText_Ask_Task            =3305,                    //�Ƿ����������
	eClient_task_AbandonTask        = 3306,    //�����񲻿ɷ���!
	//eTell_Client_CannotTaskBCLevel        = 3307, //���ĵȼ�����,���ܽ��������!
	eText_NeedItem            =3308,                    //��Ҫ������Ʒ
	eTextPlayer_QuestComp                = 3309, //[%s]�������
	eText_NoTaskItem					= 3310,	// û���ҵ�������Ʒ
	eText_NotEnoughTaskItem				= 3311,	// �ύ������Ʒ����

	eQuestType_1						= 3316,//��������
	eQuestType_2						= 3317,//֧������
	eQuestType_3						= 3318,//�����
	eQuestType_4						= 3319,//��������
	eQuestType_5						= 3320,//�ٸ�����
	eQuestType_6						= 3321,//ѭ������
	eQuestType_7						= 3322,//Ѳ������
	eQuestType_8						= 3323,//��������
	eQuestType_9						= 3324,//�ر�����
	eQuestType_10						= 3325,//�ƺ�����
	eQuestType_11						= 3326,//��������
	eQuestType_12						= 3327,//Ȥζ����
	eQuestType_13						= 3328,//��������
	eQuestType_14                       = 3329,//�ƹ�����
	eQuestType_15                       = 3330,//�ʰ�����
	eQuestType_16                       = 3331,//��������
	eQuestType_17                       = 3332,//��������
	eQuestType_18                       = 3333,//��������
	eQuestType_19                       = 3334,//��������
	eQuestType_20                       = 3335,//̽������
	eQuestType_21                       = 3336,//��������
	eQuestType_22                       = 3337,//�ɾ�����

	eText_QuestType_1					= 3350,//�����ߡ�
	eText_QuestType_2					= 3351,//��֧�ߡ�
	eText_QuestType_3					= 3352,//�����
	eText_QuestType_4					= 3353,//��������
	eText_QuestType_5					= 3354,//���ٸ���
	eText_QuestType_6					= 3355,//��ѭ����
	eText_QuestType_7					= 3356,//��Ѳ�ǡ�
	eText_QuestType_8					= 3357,//�����衿
	eText_QuestType_9					= 3358,//���ر���
	eText_QuestType_10					= 3359,//���ƺš�
	eText_QuestType_11					= 3360,//�����顿
	eText_QuestType_12					= 3361,//��Ȥζ��
	eText_QuestType_13					= 3362,//�����ɡ�
	eText_QuestType_14                  = 3363,//���ƹݡ�
	eText_QuestType_15                  = 3364,//���ʰ�
	eText_QuestType_16                  = 3365,//��������
	eText_QuestType_17                  = 3366,//�����ˡ�
	eText_QuestType_18                  = 3367,//��������
	eText_QuestType_19                  = 3368,//�����С�
	eText_QuestType_20                  = 3369,//��̽����
	eText_QuestType_21                  = 3370,//��������
	eText_QuestType_22                  = 3371,//���ɾ͡�

	//<!--selectbox-->
	eText_Quest_Select                  = 3375, //[%s]%d��

	eText_Quest_TaskDone                = 3376, //[%s]%s%s%s
	eText_Quest_TaskNone                = 3377, //[%s]%s%s"

	eText_Quest_TaskTrackDone           = 3378, //[%s]%s%s
	eText_Quest_TaskTrackNone           = 3379, //[%s]%s

	eText_Quest_NeedLevel               = 3390,//[Lv%d]
	eText_Quest_None                    = 3395,//(�ɽ�ȡ)
	eText_Quest_Act                     = 3397,//(δ���)
	eText_Quest_Done                    = 3396,//(�����)
	eText_Quest_MapName                 = 3398,//[%s]

	eText_Quest_Task                    = 3500, // {#fff4db30=����:#}
	eText_Quest_TaskTarget              = 3501, //{#fff4db30=����Ŀ��:#}
	eText_Quest_TaskDes                 = 3502, //{#fff4db30=��������:#
	eText_Quest_TaskReward              = 3503, //{#fff4db30=������:#}
	eText_Quest_TaskGold                = 3504, //{#fff4db30=��ҽ���: #}
	eText_Quest_TaskExp                 = 3505, //{#fff4db30=���齱��: %d#}
	eText_Quest_TaskMingWang            = 3506, //{#fff4db30=��������: %d#}
	eText_Quest_TaskGongXun             = 3507, //{#fff4db30=������ѫ: %d#}
	eText_Quest_TaskTitle               = 3508, //{#fff4db30=�ƺŽ���: #}
	eText_Quest_TaskRongYu              = 3509, //{#fff4db30=��������: %d#}
	eText_Quest_TaskJiaozi              = 3510, //{#fff4db30=���ӽ���: #}
	eText_Quest_TaskOK                  = 3511, //{#ff00ff00=�õ�#}
	eText_Quest_TaskLevel               = 3512, //{#ff00ff00=�뿪#}
	eText_Quest_TaskGuildContribute     = 3513, //{#fff4db30=�����ﹱ:#} %d
	eText_Quest_TaskNeedItem            = 3514, //������Ʒ: %s (%ld/%ld)
	eText_Quest_TaskNeedMonster         = 3515, //����ɱ��: %s (%ld/%ld)
	eText_Quest_TaskAim						= 3516,//<String Id="3516" Value="Ŀ��: %s (%ld/%ld)"/>   
	eText_Quest_CountryMoney			=	3517, //{#fff4db30=�����ʽ���: %d#}


	eClient_AddInfo_2slk_124        = 3701,        //��ѡ��Ҫ�ϳɵ���Ʒ�� 
	eText_CompSucess        =3702,        //�ϳɳɹ�
	eText_CompFail            =3703,            //�ϳ�ʧ��
	eText_Material_Error_0    =3704,    //    ԭ�ϲ�����
	eText_Material_error_1    =3705,    //��ʯ�ȼ�������߼�
	eClient_intensifying_str        = 3706,    //ǿ����...
	eSing_Reduce = 3707,
	eUI_IsCompound      = 3708, // �Ƿ�ϳ�
	eStatusAddCompoundRate = 3709, //�ϳɼ�������:%d%%
	eStatusAddIntensifyRate = 3710, //ǿ����������:%d%%
	eFiveXingDisplace_ProbTip = 3713,  //�ɹ���:

	eFiveXingDisplace_ProbNum              = 3901,      //���ʼӳɲ�����������
	eFiveXingDisplace_ProbMaterial         = 3902,      //���ʼӳɲ��ϲ���
	eFiveXingDisplace_JinDingLevel         = 3903,      //���м���ʯ�ȼ�����
	eFiveXingDisplace_JinDingWrong         = 3904,      //���м���ʯ����
	eFiveXingDisplace_LevelDistance        = 3905,      //����װ���ȼ����̫��
	eFiveXingDisplace_PartWrong            = 3906,      //װ����λ��һ��, �޷�ת��
	eFiveXingDisplace_NoFiveXingPart       = 3907,      //����������װ
	eFiveXingDisplace_NoFiveXing           = 3908,      //û����������, �޷�ת��
	eFiveXingDisplace_NoExistPart          = 3909,      //װ��������
	eFiveXingDisplace_Success              = 3910,      //����ת�Ƴɹ�
	eFiveXingDisplace_Faild                = 3911,      //����ת��ʧ��

	eGangError_Change_AlreadlyBund = 4000,				//�Ѿ���ͬ����"/>
	eGangError_Change_BundFull = 4001,			//" Value="ͬ�˹�ϵ��������"/>
	eGangError_Change_InBund = 4002 ,			//<String Id="4002" Value="ͬ�˹�ϵ���޷���ս"/>
	eGangError_Change_AlreadlyRupture = 4003,			//<String Id="4003" Value="�Ѿ��ǵжԹ�ϵ"/>
	eGangError_Change_RuptureFull = 4004, 			//<String Id="4004" Value="�жԹ�ϵ��������"/>
	eGangError_Change_InRupture = 4005,			//<String Id="4005" Value="Ŀǰ�ǵжԹ�ϵ������ͬ��"/>
	eGangError_Change_SelfLevelLess = 4006,			//<String Id="4006" Value="�Լ����ȼ����㣬�޷���ս"/>
	eGangError_Change_TargetLevelLess = 4007,			//<String Id="4007" Value="�Է����ȼ����㣬�޷���ս"/>
	eGangError_Change_GreaterTargetLevel = 4008,			//<String Id="4008" Value="���ڶԷ����ĵȼ����޷���ս"/>
	eGangError_Change_NotEnoughMoney = 4009,			//<String Id="4009" Value="���û���㹻���ʽ��޷���ս"/>
	eGangError_Change_NotEnoughGuild = 4010,

	eText_CountryBattle_King                = 4100, // ��������ս
	eText_CountryBattle_Dragon              = 4101, // ����ս��
	eText_CountryBattle_Rosefinch           = 4102, // ��ȸս��

	eText_CountryBattle_EnterNotTime        = 4103, // ���ǽ���%s��ʱ�䣬���ܽ���
	eText_CountryBattle_EnterNotGuild       = 4104, // ���ǲ���%s�İ�ᣬ���ܽ���
	eText_CountryBattle_NotCreate           = 4105, // %s������δ��������
	eText_CountryBattle_GuildOwnRight       = 4106, // %s�������˽���%s���ʸ�
	eText_CountryBattle_SignUp              = 4107, // %s������ʼ������%s
	eText_CountryBattle_BattleBegin         = 4108, // %ս����ʼ������%s
	eText_CountryBattle_Open                = 4109, // %�ѿ���������ʱ�����%s
	eText_CountryKing_ApplySuccess          = 4110, // %s�����һ����������ɹ�
	eText_CountryBattle_GuardSuccess        = 4111, // %s�У�%s�����ػ��ɹ�
	eText_CountryBattle_ChallengeSuccess    = 4112, // %s�У�%s������ս�ɹ�
	eText_CountryBetray_Broadcast           = 4113, // %�������Լ��Ĺ���%s
	eText_CountryBetray_Success             = 4114, // �ѹ��ɹ�
	eText_CountryBetray_NoTeam              = 4115, // �ѹ������ж���
	eText_CountryBetray_NoGuild             = 4116, // �ѹ������а���
	eText_CountryBetray_NoSameCountry       = 4117, // ����������ͬ����
	eText_CountryBetray_ErrorCountry        = 4118, // ����Ĺ���
	eText_CountryBetray_NoMoney             = 4119, // û���㹻�Ľ�Ǯ
	eText_CountryBetray_NoMarry             = 4120, // �з��޹�ϵ���ܸı����
	eText_CountryBetray_NoStudent           = 4121, // ��ͽ�ܹ�ϵ���ܸı����
	eText_CountryBetray_NoTeacher           = 4122, // ��ʦ����ϵ���ܸı����
	eText_CountryBetray_OncePerWeek         = 4123, // һ��ֻ�ܸı�һ�ι���
	eText_CountryBattle_SignUpBeReplaced    = 4124, // ���İ�����%s�����б��������ɶ�����
	eText_CountryBattle_QuitCountryWar		= 4125, // һ���Ӻ���Զ��뿪ս��

	eText_Country_BeWeak                    = 4150, // �����ڵĹ��ұ�����
	eText_Country_KingChangeName            = 4151, // ����%s�����˱������ţ�����Ϊ:%s
	eText_Country_ChangeNameSuccess         = 4152, // ���Ĺ��ųɹ�
	eText_Country_ChangeNameNoRight         = 4153, // ��û��Ȩ�޸��Ĺ���
	eText_Country_ChangeNameOnce            = 4154, // һ��ֻ���޸�һ�ι���
	eText_Country_ChangeNameError           = 4155, // ������Ĺ��Ŵ���
	eText_Country_PleaseInputName           = 4156, // ��������Ҫ���ĵĹ���
	eText_Country_ChangeNameTip             = 4157, // ����ֻ֧��2������
	eText_CountryWar_WillBegin              = 4158, // ����ս����30���Ӻ�ʼ
	eText_CountryWar_Begin                  = 4159, // ����ս��ʼ
	eText_CountryWar_End                    = 4160, // ����ս����

	//eText_IfAskClearPwd                 =   4201,//���Ƿ����������������
	//eText_Succ_Of_App_ClearPwd          =   4202,//����ɹ���15�պ�ϵͳ���Զ������Ʒ�������롣
	//eText_YouHaveAlreadyApplied         =   4203,//���Ѿ�����������������
	//eText_YouHaveLeft                   = 4204,//������
	//eText_DaysToClearItemProtectPwd     = 4205,//���켴�������Ʒ�������룡
	//eText_ItemCannotBeenLocked           = 4206,//��Ʒ���ܱ�����
	//eText_Lock                            = 4207, //IsLocked
	//eLockItemInfo         = 4208,//%d����Ʒ������������������%d����Ʒ!
	//eLockItemLimt            = 4209,//��Ʒ������������!
	//eClient_AddInfo_2slk_26        = 4210,        //"����������Ʒ��������"
	//eAsk_IsLockIntensify             =4211,               //�Ƿ�����ǿ��������500��Ʊ��
	//eTell_IntensifyMax             =4212,               //�Ѿ�ǿ������߼���
	//eTell_Locked             =4213,               //����ǿ�����˵���Ʒ��
	//eSing_LockIntensify = 4214, //����ǿ����

	//eText_InputItemPwd                = 4216,    //��������Ʒ��������
	//eText_InputItemPwdAgain                = 4217,    //���ظ������������
	//eText_InputPwdNotTheSame    = 4218,//������������벻һ��
	//eText_ItemPwdError                  =4219,    //���������Ʒ�����������
	//eText_PwdNull                        = 4220, //��Ʒ�������벻��Ϊ��  
	eClient_GameStageNextTime = 4400, //��%d��  ʣ��ʱ��:%s
	eClinet_compound_string            = 4401,    //�ϳ�
	eClient_EctypeMap_Countdown        = 4402,      //����ʣ��ʱ��:%s

	eText_SplitFailed_ItemNotExist          = 4403, // ��Ʒ�����ڣ��ֽ�ʧ��
	eText_SplitFailed_ItemIndexGuidError    = 4404, // ��Ʒ��Ϣ���󣬷ֽ�ʧ��
	eText_SplitFailed_ItemTypeLevelError    = 4405, // ֻ��%d�����ϵ����������ſɱ��ֽ�
	eText_SplitFailed_CantBeSplit           = 4406, // ����Ʒ���ɱ��ֽ�
	eText_SplitFailed_QualityLevelError     = 4407, // Ʒ�ʹ��ͣ��޷��ֽ�
	eText_SplitFailed                       = 4408, // �ֽ�ʧ��
	eText_ConfirmSplit                      = 4409, // �Ƿ���Ҫ�ֽ� %s
	eText_SplitSuccess						= 4410, // �ֽ�ɹ�

	// �������渨������Tips
	eText_CompoundMaterialTip_DaZao			= 4490,
	eText_CompoundMaterialTip_PengRen		= 4491,
	eText_CompoundMaterialTip_ChaYi			= 4492,
	eText_CompoundMaterialTip_LianYao		= 4493,
	eText_CompoundMaterialTip_JiaGong		= 4494,
	eText_CompoundMaterialTip_HeCheng		= 4495,

	eLuckGame_NextMission = 4500, //��ϲ��Ķ���������ս��һ�ص��ʸ�"/>
	eLuckGame_Lost = 4501, //�������ս�Ѿ������������������μ���ս"/>
	eLuckGame_Front = 4502, //��һ��BOSS��Թ��ʹ������������¸ҵ�ս����"/>
	eLuckGame_Stay = 4503, //��һ��BOSS��Թ��ʹ������������¸ҵ�ս����"/>
	eLuckGame_Jump = 4504, //��ϲ��Ķ���ֱ�������¹�BOSS�����ǰ�����ص��ʸ�"/>
	eLuckGame_Double = 4505, //��ϲ��Ķ�������˫����������ȥѰ��ս��Ʒ��"/>
	eLuckGame_Half = 4506, //���ź�����Ķ���ֻ�����һ�뽱������ȥѰ��ս��Ʒ��"/>

	eLuckGame_ConfirmGetAwards = 4510, //��ȡ�������޷�������ս���Ƿ�ȷ����ȡ"/>
	//eClient_actionList_0            = 4402,    //"���� /a1",
	//eClient_actionList_1            = 4403,    //"��Ҿ /a2",
	//eClient_actionList_2            = 4404,    //"���� /a3",
	//eClient_actionList_3            = 4405,    //"ӵ�� /a4",
	//eClient_actionList_4            = 4406,    //"���� /a5",
	//eClient_actionList_5            = 4407,    //"���� /a6",
	//eClient_actionList_6            = 4408,    //"���� /a7",
	//eClient_actionList_7            = 4409,    //"������ /a8",
	//eClient_actionList_8            = 4410,    //"ʤ���ĺ��� /a9",
	//eClient_actionList_9            = 4411,    //"���� /a10",
	//eClient_actionList_10            = 4412,    //"��� /a11"



	eRegister_AlreadyExist				= 4700,//ͨ��֤�Ѵ��ڣ�����������
	eRegister_EmptyPassport				= 4701,//ͨ��֤Ϊ�գ�����������
	eRegister_EmptySupperPassword				= 4702,//��������Ϊ�գ�����������
	eRegister_EmptyEmail				= 4703,//ע������Ϊ�գ�����������
	eRegister_ErrorPassword				= 4704,//��½�����������������
	eRegister_ErrorPassword1				= 4705,//��½���볤����6-32���ַ���ɣ����ִ�Сд
	eRegister_ErrorSupperPassword				= 4706,//����������6-32���ַ���ɣ����ִ�Сд
	eRegister_ErrorPassport				= 4707,//ͨ��֤������6-32λ��ĸ��������ɣ�ֻ������ĸ��ͷ
	eRegister_ErrorPassport1				= 4708,//ͨ��֤�ں��н����ַ�������������
	eRegister_ErrorEmail				= 4709,//�����������������
	eRegister_ErrorNewerCard				= 4710,//���ֿ����Ŵ�������������
	eRegister_NotSamePassword				= 4711,//��½������д��һ�£�����������
	eRegister_NotSameSupperPassword				= 4712,//����������д��һ�£�����������
	eRegister_Agreement				= 4713,//���Ķ���ͬ�⡶����ͨ��֤�û�Э�顷�͡�����ͨ��֤��˽Ȩ���ߡ�
	eRegister_EmptyPassword				= 4714,//����Ϊ�գ�����������
	eRegister_OK				= 4715,//ע��ɹ�
	eRegister_Fail				= 4716,//ע��ʧ��
	eRegister_ErrorEmail1				= 4717,//��ȫ���䳤��Ϊ8-64λ
	eRegister_CodeEmpty				= 4718,//��֤��Ϊ�գ�����������
	eRegister_CodeError				= 4719,//��֤�������������������

	//eLog_info_2slk_10    =4632,    //������Ʒ ��ʼ %s��%s




	//eRealAward_NameEmpty				= 4750,//��������ϵ������
	//eRealAward_PhoneEmpty				= 4751,//��������ϵ�绰
	//eRealAward_EmailEmpty				= 4752,//��������ϵ����
	//eRealAward_CardEmpty				= 4753,//���������֤����
	//eRealAward_EmailFormatError				= 4754,//�����ʽ��������������
	//eRealAward_ItemError				= 4755,//����Ʒ�����ڣ�����ϸ�˶����İ�����Ʒ
	//eRealAward_CardLengthError				= 4757,//���֤����ӦΪ15��18λ
	//eRealAward_Congratulation				= 4758,//��ϲ������ˡ�%s����\n������ͨ���ٷ���ҳ�еĻ񽱲�ѯҳ����в�ѯ���콱������Ա�ᾡ�콫�������Ÿ�����





	eLog_info_2slk_33    =4654,    //���״̬ %s

	eClient_Err_Relive		= 4655, // �Ŵ���ʧ����Ϣ��ʾ
	eText_Relive_FullHPMP	= 4656, // ����һ����������Ļ���j


	//<String Id="4801"  Value="�����ɹ�"/>
	//<String Id="4802" Value="����ʧ��"/>
	//<String Id="4803" Value="��װ���޷�����"/>
	//<String Id="4804" Value="��Ǯ���㣬�޷�����"/>
	//<String Id="4805" Value="��Ҫʹ��%s����������װ��"/>
	//<String Id="4806" Value="��װ���Ѿ��������޷���������"/>
	//<String Id="4807" Value="���ߵȼ����ͣ��޷�������װ��"/>

	//<String Id="4811" Value="ת���ɹ�"/>
	//<String Id="4812" Value="ת��ʧ��"/>
	//<String Id="4813" Value="��װ���޷�ת��"/>
	//<String Id="4814" Value="��Ǯ���㣬�޷�ת��"/>

	eClient_SkillSuitUpgradeSuccess				= 4801, // �����ɹ�
	eClient_SkillSuitUpgradeFailed					= 4802, // ����ʧ��
	eClient_SkillSuitCannotUpgrade				= 4803, // ��װ���޷�����
	eClient_SkillSuitUpgradeNoMoney			= 4804, // ��Ǯ���㣬�޷�����
	eClient_SkillSuitUpgradeItemError			= 4805, // ��Ҫʹ��%s����������װ��
	eClient_SkillSuitMaxLevel							= 4806, // ��װ���Ѿ��������޷���������
	eClient_SkillSuitUpgradeLessItemLevel	= 4807, // ���ߵȼ����ͣ��޷�������װ��
	eClient_SkillSuitCannotUpStar					= 4808,//����Ʒ�޷�����

	eClient_SkillSuitChangeSuccess			= 4811, // �����ɹ�
	eClient_SkillSuitChangeFailed			= 4812, // ����ʧ��
	eClient_SkillSuitCannotChange			= 4813, // ��װ���޷�ת��
	eClient_SkillSuitChangeNoMoney			= 4814, // ��Ǯ���㣬�޷�����
	eClient_SkillSuitChangeItem1Error		= 4815, // �����ת������
	eClient_SkillSuitChangeItem2Error		= 4816, // ����Ĺ�ѫ����
	eClient_SkillSuitLessChangeLevel		= 4817, // �ᴿ�������ϵ�װ���ſɽ���ת��

	eClient_FivexingTipUpdateSuccess        = 4831, //�ᴿ�ɹ�
	eClient_FiveXingTipUpdateFailed         = 4832,  //�ᴿʧ��
	eClient_FiveXingTipUpdateNoCan          = 4833, //��װ���޷��ᴿ
	eClient_FiveXingTipUpdateNoMoney        = 4834, //��Ǯ���㣬�޷��ᴿ
	eClient_FiveXingTipMaterialError        = 4835, //���ϲ������޷��ᴿ
	eClient_FiveXingTipNoJianDing           = 4836, //��Ҫ�Ƚ������м��������ܽ����ᴿ
	eClient_FiveXingUpdateNoLessThree       = 4837,//�ᴿ�������ϵ�װ���ſɽ���ת��
	eClient_FiveXingTipJin                  = 4900,//&lt;#FFffff00����:��
	eClient_FiveXingTipMu                   = 4901,//&lt;#FFffff00����:ľ
	eClient_FiveXingTipShui                 = 4902,//&lt;#FFffff00����:ˮ
	eClient_FiveXingTipHuo                  = 4903,//&lt;#FFffff00����:��
	eClient_FiveXingTipTu                   = 4904,//&lt;#FFffff00����:��

	eClient_FiveXingTipJinHurt              = 4905, //%s+%d (ˮ�����˺�+%d)
	eClient_FiveXingTipMuHurt               = 4906, //%s+%d (ˮ�����˺�+%d)
	eClient_FiveXingTipShuiHurt             = 4907, //%s+%d (ˮ�����˺�+%d)
	eClient_FiveXingTipHuoHurt              = 4908, //%s+%d (ˮ�����˺�+%d)
	eClient_FiveXingTipTuHurt               = 4909, //%s+%d (ˮ�����˺�+%d)
	//////////////////////////////////////////////////////////////////////////

	// ѧ���м��ܵ�����
	eText_LearnAllSkillCaption				= 4910, // ѧϰ���м���
	eText_LearnAllSkillText					= 4911, // ���������߽�Ǯ���㣬���޷�ȫ��ѧϰ����ȷ����Ҫ������

	eText_MoveStarUpgradeSuccess			= 4950, // �����ɹ�
	eText_MoveStarUpgradeFailed				= 4951, // ����ʧ��
	eText_UpgradeFailed_IncorrectMaterial1	= 4952, // �õ����޷���������ʯ
	eText_UpgradeFailed_IncorrectMaterial2	= 4953, // ���ϲ������޷�����
	eText_UpgradeFailed_IncorrectMoveStarItem	= 4954, // ������ʯ�޷�����
	eText_UpgradeFailed_NotEnoughMoney		= 4955, // ��Ǯ���㣬�޷�����

	eText_MaterialUpgradeSuccess			= 4960, // �ϳɳɹ�
	eText_MaterialUpgradeFailed				= 4961,	// �ϳ�ʧ��
	eText_MaterialUpgradeFailed_NotEnoughMoney		= 4962, // ��Ǯ���㣬�޷��ϳ�
	eText_MaterialUpgradeFailed_IncorrectMaterial1	= 4963, // ���ϲ������޷��ϳ�
	eText_MaterialUpgradeFailed_IncorrectMaterial2	= 4964, // �õ����޷��ϳ�����ʯ
	eText_MaterialUpgradeFailed_IncorrectStarItem	= 4965, // ������ʯ�޷��ϳ�
	eText_MaterialUpgrade_PutOneItem		= 4966, // ���ֺ��������ʯ
	eText_MaterialUpgrade_NotSameMaterial	= 4967, // �������ͬ������ʯ

	eText_IntensifyStarFailed_LevelLimit	= 4970, // װ���ȼ���Ҫ�ﵽ60��
	eText_IntensifyStarFailed_StarLimit		= 4971, // װ���Ǽ���Ҫ�ﵽ9��
	eText_IntensifyStarFailed_NoMaterial	= 4972, // δ���ñ�����ߣ��޷�����
	eText_IntensifyStarFailed_NoRateMaterial= 4973, // ���ٷ���һ��������ʼӳɵ���
	eText_IntensifyStarFailed_NotEnoughMoney= 4974, // ��Ǯ���㣬�޷�����
	eText_IntensifyStarFailed				= 4975, // ����ʧ��
	eText_IntensifyStarSucceed				= 4976, // ����ɹ�
	eText_IntensifyStarFailed_LackRateMaterial		= 4977, // ȱ�����Ӹ��ʲ���
	eText_IntensifyStarFailed_WrongRateMaterialNum	= 4978, // ���Ӹ��ʲ�����������ȷ
	eText_IntensifyStarFailed_IncorrectRateMaterial	= 4979, // ���ϲ������޷�����

	eText_GIF_MouseRight		= 5354,		//gif���ͼ���Ҽ�
	eText_GIF_MouseLeft			= 5355,		//gif���ͼ�����

	eText_DoubleExpDisable                  = 5493, // ˫��״̬δ���� \n����������˫�����顱��ť
	eText_DoubleExpEnable                   = 5494, // ˫��ʱ�������� \nĬ�Ͻ�����Ч��ϵͳ���͵�˫��ʱ��
	eText_AutoAttack_BeginFailed_NoEnergy   = 5495, // �������㣬�޷��Զ��һ�
	eText_AutoAttack_End_NoEnergy           = 5496, // ����������ϣ�ֹͣ�Զ��һ�

	eText_ItemBind_ConfirmByDifInBound              = 5611, // ȷ���Ƿ���Ҫ���󶨺Ͳ��󶨵���Ʒ��һ��
	eText_GuildSendMessageSuccess					= 5612,//������Ϣ�Ѿ�����
	//���
	eText_Guild_LevelGuild_Succeed = 5900,//�뿪���ɹ�
	eText_Guild_LevelGuild_NotHaveGuild = 5901,//�뿪��᲻�ɹ�,û�м����κΰ��
	eText_Guild_LevelGuild_NotHaveRight = 5902,//�뿪��᲻�ɹ�,������ְλ, �޷�ֱ���˳�����
	eText_Guild_LevelGuild_ChangeNotice = 5903,//�޸Ĺ������ʾ
	eText_Guild_TransferPosition_Master = 5904,//%s������֮λת�ø�%s��%s��Ϊ�°���
	eText_Guild_TransferPosition_ViceMaster = 5905,// %s��������֮λת�ø�%s��%s��Ϊ�µĸ�����
	eText_Guild_TransferPosition_FamilyMaster = 5906,//%s������֮λת�ø�%s��%s��Ϊ������
	eText_Guild_IncreaseGuildMoney = 5907,//���%d����ʽ�
	eText_Guild_DecreaseGuildMoney = 5908,//ʧȥ%d����ʽ�
	eText_Guild_IncreaseGuildExp = 5909,//���%d��ᾭ��
	eText_Guild_DecreaseGuildExp = 5910,//ʧȥ%d��ᾭ��
	eText_Guild_IncreaseGuildLevel = 5911,//���ȼ�������%d��
	// 
	eText_Guild_TransferSuccess	   =5950,//�ѳɹ�ת��ְλ
	eText_Guild_TransferNotHaveRight = 5951,//��û��ת��ְ���Ȩ��
	eText_Guild_TransferNotViceMaster=5952,//�Է����Ǹ����������ܱ�ת�ð���ְλ
	eText_Guild_TransferLevelLess	 =5953,//�Է��ȼ����㣬�޷�ת��ְ��
	eText_Guild_TransferNotGuildMember=5954,//�Է����Ǳ����Ա������ת��ְ��
	eText_Guild_TransferNotSameFamily =5955,//�Է�����ͬһ�����Ա������ת���峤ְ��
	eText_Guild_TransferIsKing		  =5956,//�Լ��ǹ���������ת�ð���
	// 
	eText_Guild_TimeLimit		  =5998,//�뿪���ɺ�24Сʱ��,�Է����ܼ������
	eText_Guild_MasterCanNotZC    =5999,//���峤�޷�ת��
	eText_Guild_AgreeJoin		   =6000,//ͬ��������
	eText_Guild_CreateGuildSucceed = 6001, // 	<String Id="6001" Value="���ɴ����ɹ�"/>
	eText_Guild_InValideName = 6002, // <String Id="6002" Value="���������ַ����Ƿ�����"/>
	eText_Guild_SameName = 6003, // <String Id="6003" Value="��������ͬ���ֵİ���"/>
	eText_Guild_AlreadyHadGuild = 6004, // <String Id="6004" Value="�Ѿ��а����ˣ����ܴ���"/>
	eText_Guild_LevelLessThanThirty = 6005, // <String Id="6005" Value="�ȼ�����30��"/>
	eText_Guild_NotEnoughMoney = 6006, // 	<String Id="6006" Value="û���㹻������"/>
	eText_Guild_CreateFamilySucceed = 6007, // <String Id="6007" Value="���ô����ɹ�"/>
	eText_Guild_HaveNoRight = 6008, // 	<String Id="6008" Value="û��Ȩ��"/>
	eText_Guild_FamilyFull = 6009, // <String Id="6009" Value="��������"/>
	eText_Guild_HaveSameFamily = 6010, // <String Id="6010" Value="������ͬ���ֵķ���"/>
	eText_Guild_ChangeSucceed = 6011, // <String Id="6011" Value="�޸ĳɹ�"/>
	eText_Guild_HaveNoRightChange = 6012, // <String Id="6012" Value="û���޸ķ������ֵ�Ȩ��"/>
	eText_Guild_CanNotDeleteOrChangeEmptyFamily = 6013, // <String Id="6013" Value="�ռ��岻�ܸ�������ɾ��"/>
	eText_Guild_AssignSucceed = 6014, // <String Id="6014" Value="ְλ�����ɹ�"/>
	eText_Guild_HaveNoRightAssign = 6015, // <String Id="6015" Value="û��Ȩ������"/>
	eText_Guild_SamePosition = 6016, // <String Id="6016" Value="�Ѿ��Ǹ�ְλ"/>
	eText_Guild_HaveNoFamily = 6017, // 	<String Id="6017" Value="û�м��壬��������Ϊ���峤"/>
	eText_Guild_KickOutGuildSucceed = 6018, // 	<String Id="6018" Value="�߳����ɳɹ�"/>
	eText_Guild_HaveNoGuild = 6019, // 	<String Id="6019" Value="û�а���"/>
	eText_Guild_KickGuildMemberFaild = 6020, // 	<String Id="6020" Value="�޷����ˣ��������ְλ"/>
	eText_Guild_ChangeBangZhongSucceed = 6021, // 	<String Id="6021" Value="�ı�ɹ�"/>
	eText_Guild_NoRightChange = 6022, // 	<String Id="6022" Value="û��Ȩ�ޣ��޷�ת�ư���"/>
	eText_Guild_NoNeedChange = 6023, // 	<String Id="6023" Value="��ͬ�ļ��壬����Ҫ�ƶ�"/>
	eText_Guild_ChangeEmptyFamilyFaild = 6024, // 	<String Id="6024" Value="�����ƶ����ռ���"/>
	eText_Guild_InviteSucceed = 6025, // 	<String Id="6025" Value="����ɹ�"/>
	eText_Guild_MeHaveNoGuild = 6026, // 	<String Id="6026" Value="�Լ�û�а���"/>
	eText_Guild_NoRightInvite = 6027, // 	<String Id="6027" Value="û������Ȩ��"/>
	eText_Guild_OtherCountry = 6028, // 	<String Id="6028" Value="���Ǳ����Ĳ�������"/>
	eText_Guild_PlayerOffline = 6029, // 	<String Id="6029" Value="�Է������ڻ��߲�����"/>
	eText_Guild_HeHaveGuild = 6030, // 	<String Id="6030" Value="�Է����а���"/>
	eText_Guild_LevelLessThanTwenty = 6031, // 	<String Id="6031" Value="�Է��ȼ�����20������������������"/>
	eText_Guild_MemberFull = 6032, // 	<String Id="6032" Value="��Ա���Ѿ�����"/>
	eText_Guild_RefuseJoin= 6033, // 	<String Id="6033" Value="�ܾ��������"/>
	eText_Guild_JoinGuildSucceed = 6034, // 	<String Id="6034" Value="������ɳɹ�"/>
	eText_Guild_AlreadyInGuild = 6035, // 	<String Id="6035" Value="���а����޷�����"/>
	eText_Guild_LessThanApplyLevel = 6036, // 	<String Id="6036" Value="�ȼ�����20���޷�����"/>
	eText_Guild_NotTheSameCountry = 6037, // 	<String Id="6037" Value="���Ǳ����Ĳ�������"/>
	eText_Guild_MustWaitCoolTime = 6038, // 	<String Id="6038" Value="�˰��Ժ�24Сʱ�ڲ��ܼ������"/>
	eText_Guild_GuildIsNotExist = 6039, // 	<String Id="6039" Value="����İ��ɲ�����"/>
	eText_Guild_TheDestGuildMemberFull = 6040, // 	<String Id="6040" Value="Ŀ����ɳ�Ա���Ѿ�����"/>
	eText_Guild_RefuseApply = 6041, // 	<String Id="6041" Value="�ܾ��������"/>
	eText_Guild_TheAdminIsOffline = 6042, // 	<String Id="6042" Value="���ɹ��������޷�����"/>
	eText_Guild_ActiveSucceed = 6043, // 	<String Id="6043" Value="����ɹ�"/>
	eText_Guild_NoRightActive = 6044, // 	<String Id="6044" Value="û�м���Ȩ��"/>
	eText_Guild_GuildLevelNotEnough = 6045, // 	<String Id="6045" Value="���ɵȼ��������޷�����"/>
	eText_Guild_GuildExpNotEnough = 6046, // 	<String Id="6046" Value="û���㹻�İ��ɾ����޷�����"/>
	eText_Guild_AlreadyActived = 6047, // 	<String Id="6047" Value="�Ѿ�����ɹ�"/>
	eText_Guild_FalseLevel = 6048, // 	<String Id="6048" Value="����ĵȼ�"/>
	eText_Guild_GuildLevelUpSucceed = 6049, // 	<String Id="6049" Value="���������ɹ�"/>
	eText_Guild_NoRightLevelUp = 6050, // 	<String Id="6050" Value="û������Ȩ��"/>
	eText_Guild_NotEnoughGuildMoney = 6051, // 	<String Id="6051" Value="û���㹻�İ��ɽ�Ǯ"/>
	eText_Guild_NotEnoughGuildExp = 6052, // 	<String Id="6052" Value="û���㹻�İ��ɾ���"/>
	eText_Guild_IsMaxGuildLevel = 6053, // 	<String Id="6053" Value="�Ѿ��������ɵȼ�"/>
	eText_InfoTip_GuildTanHe				= 6055, // 	<String Id="6055" Value="��ᵯ��"/>
	eText_Guild_GuildInvite			= 6054,	//<String Id="6054" Value="�������"/>
	eText_InfoTip_ApplyGuild					= 6056, // 	<String Id="6056" Value="�������"/>
	eText_Guild_InviteJoinGuild = 6057, // 	<String Id="6057" Value="���������"/>
	eText_Guild_FaQiTanHe = 6058, // 	<String Id="6058" Value="%s������ɵ���"/>
	eText_Guild_ApplyJoinGuild = 6059, // 	<String Id="6059" Value="%s�������"/>
	eText_Guild_NoBuyRight = 6060, //	<String Id="6060" Value="û�й���Ȩ��"/>
	eText_Guild_GuildShopNoActive = 6061, //<String Id="6061" Value="�����̵�û�м���"/>
	eText_Guild_ItemNotExist = 6062, //	<String Id="6062" Value="û�д���Ʒ����"/>
	eText_Guild_NotEnoughOffer = 6063, //	<String Id="6063" Value="û���㹻�İﹱ"/>
	eText_Guild_ErrorShopLevel = 6064, //	<String Id="6064" Value="������̵�ȼ�"/>
	eText_Guild_SomeJoinSomeGuild = 6065, //	<String Id="6065" Value="���%s������%s����"/>
	eText_Guild_SomeLeaveSomeGuild = 6066, //	<String Id="6066" Value="���%s�뿪�˰���"/>
	eText_Guild_TanHeGuildResult = 6067, //<String Id="6067" Value="%s��������%s"/>
	eText_Guild_GuildDisband = 6068, //<String Id="6068" Value="%s���ɽ�ɢ��"/>
	eText_Guild_GuildInviteMessage = 6069, //<String Id="6069" Value="%s���������%s���"/>
	eText_Guild_UnableAppointMyself = 6070, //<String Id="6070" Value="���ܶ��Լ����д˲���"/>
	eText_Guild_SelectNothing = 6071, //<String Id="6071" Value="û��ѡ�а��Ա�����ܽ��д˲���"/>
	eText_Guild_UnableTansferPositon = 6072, //    <String Id="6072" Value="����Խ�����д˲���"/>
	eText_Guild_ApplyingMessageSending = 6073, //<String Id="6073" Value="�����Ѿ���������ȴ�������"/>
	eText_Guild_DelMember = 6074, //<String Id="6074" Value="ȷ��Ҫ���ó�Ա:%s �Ӱ�Ὺ����"/>
	eText_Guild_DelMemberTile = 6075, //<String Id="6075" Value="��Ὺ����"/>
	eText_Guild_UnReachTanHeTime = 6076, //<String Id="6076" Value="û�е��ﵯ��ʱ��"/>
	eText_Guild_AlreadyBeTanHe = 6077, //<String Id="6077" Value="�����˷����˵�������"/>
	eText_Guild_LevelLessThanNeed = 6078, //<String Id="6078" Value="�ȼ������޷�����"/>
	eText_Guild_MaxExp = 6079, //<String Id="6079" Value="���ɾ����Ѵﵽ�������"/>
	eText_Guild_NoEnoughMoneyTanHe = 6080, //<String Id="6080" Value="û���㹻�Ľ�Ǯ�޷�����"/>
	eText_Guild_OnLineLess = 6081, //<String Id="6081" Value="�������߳�Ա����20���޷���������"/>
	eText_Guild_GuildMasterConvene = 6082, //<String Id="6082" Value="�����ټ�����ȥ%s:%s,�Ƿ���Ӧ�ټ���?"/>
	eText_Guild_OfferNotEnoughOffer = 6083,//<String Id="6083" Value="û���㹻�İﹱ"/>
	eText_Guild_OfferMaxGuildExp = 6084, //<String Id="6084" Value="���ɾ����Ѿ��������ֵ��"/>
	eText_Guild_ReleaseSuccess = 6085, //<String Id="6085" Value="�ı�ɹ�"/>6076, //
	eText_Guild_ReleaseNoRight = 6086,  //<String Id="6086" Value="û��Ȩ��"/>//
	eText_Guild_ReleaseLevelNoEnough = 6087,//<String Id="6087" Value="���ɵȼ�����"/>6076, //
	eText_Guild_ReleaseErrorTime = 6088,//<String Id="6088" Value="������22����ǰ����"/>= 6076, //
	eText_Guild_ReleaseAlreadyRelease = 6089,//<String Id="6089" Value="�Ѿ�������"/>6, //
	eText_Guild_ReleaseNotEnoughMoney = 6090,//<String Id="6090" Value="û���㹻�Ľ�Ǯ"/>76, //
	eText_Guild_ReleaseQuestError = 6091, //<String Id="6091" Value="���ܷ���������"/>//
	eText_Guild_DisbandTime = 6092, //<String Id="6092" Value="֪ͨ:���ڸ��µİ��ɳ�ʱ�������������Ҫ��ϵͳ����%s��ɢ��"/>//
	eText_Guild_ShopLevelUpSuccess = 6093, //<String Id="6093" Value="����̵������ɹ�"/>//
	eText_Guild_SbCreateGuild = 6094, //<String Id="6093" Value="֪ͨ:%s������%s�"/>//
	eText_Guild_GuildDenoteMoneyNotEnough = 6095, //<String Id="6095" Value="����ǰ�Ľ�Ǯ����"/>

	eFriend_MySignature						= 6096,//��������������
	eFriend_GroupName						= 6097,//�������µķ�������
	eFriend_Error_FullGroup					= 6098,//��Ŀǰ�ķ�������
	eFriend_Error_GroupRepeat				= 6099,//���������ظ�����������
	eFriend_Warning_DeleteGroup				= 6100,//��ȷ��Ҫ���÷���ɾ��
	eFriend_FriendTag						= 6101,//��������ѱ�ע
	eFriend_Error_DefaultGroup				= 6102,//Ĭ�Ϸ��鲻��ɾ��
	eFriend_ChangeFriendToGroup				= 6103,//���Ƿ�Ҫ�ƶ�:%s���ѵ�
	eFriend_Error_Name                      = 6104,//δ�ҵ�����������������
	eText_Guild_AlreadyHaveFamily = 6105,//�Է��Ѿ�������
	eText_Stallage_ChangeName               = 6110, // ������̯λ����
	eText_GuildChangeNameSuccess		=6111,//���ɷ��ø���
	eText_GuildHaveNoFamily						=6112,//��û�з���
	eText_Guild_GuildCreateSystemMessage = 6200, //		
	eText_Guild_GuildDenote = 6201,	//<String Id="6201" Value="������˵��:���ÿ�հ����������һ�Σ����׵Ľ�Ǯ�����������Ｏ����ʽ𣬿��Կ�������İ������Ϳ��Խ��а��������"/>
	eText_Guild_AgreeTanHe = 6202,	 	//<String Id="6202" Value="��ͬ�ⵯ���������"/>
	eText_Guild_DisagreeTanHe = 6203,	//<String Id="6203" Value="����ͬ�ⵯ���������"/>,
	eText_Guild_ImpeachSend = 6204,	 	//<String Id="6204" Value="�������˵������������������ȴ�����Ա��Ӧ���"/>
	eText_Guild_ImpeachSuccess = 6205,	//<String Id="6205" Value="%s������������ɹ���%s��Ϊ�˱����µİ���"/>,
	eText_Guild_ImpeachFailed = 6206,	//<String Id="6206" Value="%s�����������û�дﵽ�����ɹ���Ҫ�󣬵���ʧ��"/>
	eText_Guild_Master = 6207,
	eText_Guild_ViceMaster = 6208,
	eText_Guild_Tangzhu = 6209,
	eText_Guild_Bangzhong = 6210,
	eText_Guild_CanNotTransferPositionWhenIsKingGuild = 6211,//����������޷�ת��ְλ
	eText_ShiTu_GetExpAndMasterValueByYourStudent = 6212,//ͽ��������ʦ����þ���������
	eText_ShiTu_GetExpAndMasterValueByYourGrandStudent = 6213,//ͽ�ܵ�ͽ��������ʦ����þ���������

	eExitTip_InfoMore						= 6220,//����

	eText_MoneyInput_Trade                  = 6255, // ��������
	eText_MoneyInput_CountryDonate          = 6256, // ������Դļ��
	eText_MoneyInput_GuildDonate            = 6257, // �����Դļ��
	eText_MoneyInput_DonateLimit            = 6258, // ������ļ��%s
	eText_CountryRise_Broadcast             = 6259, // %sΪ����ļ����%s

	//lyh++ ��������־string ��6300 - 6900 ���Ƿ�������־���� 
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
	//����ս
	eText_CountryBattle_CountryName         = 6915, // %s����ɱ:
	eText_CountryBattle_KillNumber          = 6916, // %d�ˣ�

	//���ս
	eText_GuildCamp_TimeToCampStart = 6919,//���Ὺʼ
	eText_GuildCamp_TimeToCampEnd = 6920,//�������

	// Begin�������
	/*"���ѱ�~%s_��ɱ����ѡ��ת�����������򵹼�ʱ��������������ǣ�234��366����\n
	%s���������ÿ������ʹ��%s��ԭ�ظ��%s������ÿ������ʹ��%s�Ρ�\n
	���ԭ�ظ���ʹ���������ʹ��ԭ�ظ�������ĸ����Ԫ����ϵͳ������ʹ�ð����еĸ��������������꣬��ǰ���θ��ÿ�ο۳�1Ԫ�������Ĵο�ʼ�۳�2Ԫ����\n
	�����컹��%d�����ԭ�ظ��*/
	eReliveUI_Relive	= 6924,//ת������ 		
	eReliveUI_Entrance	= 6925,//������ڸ���
	eReliveUI_Battle	= 6926,//ս������
	// End�������
	eText_GuildCamp_Tip					= 7000, //���սTip
	eText_GuildCamp_FlyToNpc			= 7001, //���ս��TransferToNpc����ʾ������
	eText_GuildCamp_EnterBattleFiled = 7002,//������ս�����ϵ�˵��
	eText_GuildCamp_EnterBattleReq	= 7003,//���������Ϣ�ѷ���
	eText_GuildCamp_TimeBeforeBattle = 7004,//��ʾ:��û�н�����ս�׶Σ�����Ⱥ�
	eText_GuildCamp_NotSignUp = 7005, //��ʾ:�����Ǳ������ɲ��ܽ�����ս����
	eText_GuildCamp_BattleResult = 7006,//����ս���
	eText_GuildCamp_SignUpSuccess = 7007,//�����ɹ�
	eText_GuildCamp_WrongTime = 7008,//���Ǳ���ʱ��
	eText_GuildCamp_MustMaster = 7009,//�����ǰ������ܱ���
	eText_GuildCamp_MemberNumNotEnough = 7010,//���ɳ�Ա����
	eText_GuildCamp_AlreadySignUp = 7011,//�Ѿ�������
	eText_GuildCamp_BullSystem_SignUp = 7012,//���ս������ϵͳ����
	eText_GuildCamp_BullSystem_Prepare = 7013,//���ս׼��״̬��ϵͳ����
	eText_GuildCamp_BullSystem_Enter = 7014,//������ս��״̬��ϵͳ����
	eText_GuildCamp_BullSystem_Fight = 7015,//ս��ս��״̬��ϵͳ����
	eText_GuildCamp_BullSystem_Over = 7016,//���ս������ϵͳ����
	eText_GuildCamp_BullSystem_MatchNoTeam = 7017,//"�Բ��𣬽������ڹ�������һ�����������ܰ��ɱ�����Ϊ���������Թ��û�о������֣����ܲμӽ��հ���ս�����´��������룡"/>
	eText_GuildCamp = 7018,//�������ս

	eText_KingCamp_EnterBattleInfo = 7030,//��������ս������ϵ���ʾ
	eText_KingCamp_TimeToCampStart = 7031,//���������ս��ʼ
	eText_KingCamp_TimeToCampEnd = 7032,//���������ս����
	eText_Camp_SignUpReplace = 7033,// ֪ͨ���ɰ���, ��ı����б��������ɶ�����
	eText_Camp_CountryBattleGuild = 7034,// ȫ���㲥ĳ�����ɻ����ս���ʸ�
	eText_Camp_CountryBattleResult = 7035,// ֪ͨ����ս�����
	eText_KingCamp_Tip = 7036,// ��������ս
	eText_KingCamp_FlyToNpc			= 7037, //����ս��TransferToNpc����ʾ������
	eText_KingCamp_SignUpEnd_MustBeEnterInThreeMin			= 7038,//ȫ���㲥:��������ս������������ս��͹������Ա����3�����ڽ���ս��
	eText_KingCamp_SignUpTime			= 7039,//��������ս��ʼ������
	eText_KingCamp_FightStart = 7040,//��������ս��ʼ
	eText_KingCamp_EnterBattleReq	= 7041,//���������Ϣ�ѷ���
	eText_Camp_LevelLess	= 7042,//�ȼ�����
	eText_Camp_MaxCount	= 7043,//��������
	eText_KingCamp_HaveFourLive = 7044,//��ʣ4����
	eText_KingCamp_HaveThreeLive = 7045,//��ʣ3����
	eText_KingCamp_HaveTwoLive = 7046,//��ʣ2����
	eText_KingCamp_HaveOneLive = 7047,//��ʣ1����
	eText_KingCamp_HaveZeroLive = 7048,//��ʣ0����


	eText_CountryTitle_King					=8700, //����
	eText_CountryTitle_General				=8701, //�󽫾�
	eText_CountryTitle_Queen				=8702, //����
	eText_CountryTitle_CouncilorLeft		=8703, //˾��
	eText_CountryTitle_CouncilorRight		=8704, //ة��
	eText_CountryTitle_CaptorLeft			=8705, //�󽫾�
	eText_CountryTitle_CaptorRight			=8706, //�ҽ���
	eText_CountryTitle_KingGuard			=8707, //�����ػ�����
	eText_CountryTitle_Dragon				=8708, //����֮��
	eText_CountryTitle_DragonGuard			=8709, //�����ػ�
	eText_CountryTitle_Rosefinch			=8710, //��ȸ֮��
	eText_CountryTitle_RosefinchGuard		=8711, //��ȸ�ػ�

	eText_Country_Appoint_Already			=8720, //�Ѿ��Ǹ�ְλ
	eText_Country_Appoint_BeAppoint			=8721, //������
	eText_Country_Appoint_BeDismiss			=8722, //������	
	eText_Country_Appoint_NoGuild		    =8723, //û�й���
	eText_Country_Appoint_NoItem			=8724, //û�������Ա����Ʒ

	// ����ɫ��
	eText_CountryTitle_King_Col				=8730, //����
	eText_CountryTitle_General_Col			=8731, //�󽫾�
	eText_CountryTitle_Queen_Col			=8732, //����
	eText_CountryTitle_CouncilorLeft_Col	=8733, //˾��
	eText_CountryTitle_CouncilorRight_Col	=8734, //ة��
	eText_CountryTitle_CaptorLeft_Col		=8735, //�󽫾�
	eText_CountryTitle_CaptorRight_Col		=8736, //�ҽ���
	eText_CountryTitle_KingGuard_Col		=8737, //�����ػ�����
	eText_CountryTitle_Dragon_Col			=8738, //����֮��
	eText_CountryTitle_DragonGuard_Col		=8739, //�����ػ�
	eText_CountryTitle_Rosefinch_Col		=8740, //��ȸ֮��
	eText_CountryTitle_RosefinchGuard_Col	=8741, //��ȸ�ػ�



	eText_CountryConvene_Distribute			=8750, //�������ټ���

	eText_CountryConvene_NotRight			=8751, //��Ȩ��
	eText_CountryConvene_TimeLimit			=8752, //��������
	eText_CountryConvene_NotEnoughMoney		=8753, //ȱǮ
	eText_CountryConvene_Success			=8754, //�����ɹ�

	eText_CountryConvene_YesOrNo			=8760, //�Ƿ�ǰ��

	eText_CountryBattle_SignUp_Success      = 8770, // ս�������ɹ�
	eText_CountryBattle_SignUp_NotTime      = 8771, // ���Ǳ���ʱ�䲻�ܱ���
	eText_CountryBattle_SignUp_MustMaster   = 8772, // �����ǰ�᳤�ſ��Ա���
	eText_CountryBattle_SignUp_LevelLess    = 8773, // ������ﵽ2�����ܱ���
	eText_CountryBattle_SignUp_MemberLess   = 8774, // ����Ա����ﵽ30�˲��ܱ���
	eText_CountryBattle_SignUp_StrengthLess = 8775, // ���ʵ�����������������, �޷�����
	eText_CountryBattle_SignUp_MoreMoney    = 8776, // û���㹻�İﹱ
	eText_CountryBattle_SignUp_Already      = 8777, // �Ѿ�������
	eText_CountryBattle_SignUp_CanNot       = 8778, // ���ܱ�����ս��                       

	eText_Country_PlayerBeSilence            =8850, // ������
	eText_Country_PlayerBePrison             =8851, // ������
	eText_Country_PlayerBeFree               =8852, // ������

	eText_CountryPos_King					 =8890, // ����
	eText_CountryPos_Queen					 =8891, // ����
	eText_CountryPos_LCouncilor				 =8892, // ˾��
	eText_CountryPos_RCouncilor				 =8893, // ة��
	eText_CountryPos_General				 =8894, // �󽫾�
	eText_CountryPos_LCaptor				 =8895, // �󽫾�
	eText_CountryPos_RCaptor				 =8896, // �ҽ���
	eText_CountryPos_QueenMale				 =8897, // ����

	eText_Country_Silence					 =8900,	// ����
	eText_Country_Prison					 =8901,	// ����
	eText_Country_Free						 =8902,	// ����
	eText_Country_CountLeft					 =8903, // ����ʣ�����
	eText_Country_Tips						 =8904, // ��ʾ
	eText_Country_AppointDaJiangJun			 =8905, // �����󽫾�
	eText_Country_AppointSiMa				 =8906, // ����˾��
	eText_Country_AppointChengXiang			 =8907, // ����ة��
	eText_Country_AppointZuoJiangJun		 =8908, // �����󽫾�
	eText_Country_AppointYouJiangJun		 =8909, // �����ҽ���

	eText_Country_Task_GuoYun				 =8910,	//������
	eText_Country_Task_ChuGuo				 =8911,	//������
	eText_Country_Task_TanBao				 =8912,	//̽����
	eText_Country_Task_TianXing				 =8913,	//������
	eText_Country_Task_NotDbt				 =8914,	//δ����
	eText_Country_Task_Dbt					 =8915,	//����

	eText_Country_Raise_Success				 =8916,	//ļ���ʽ�ɹ�
	eText_Country_Raise_NotRight			 =8917, //û��Ȩ��
	eText_Country_Raise_TimeLimit			 =8918, //һ��ֻ��ļ��һ��

	eText_Country_Broadcast_Success			 =8919, //��������ɹ�
	eText_Country_Broadcast_NotRight		 =8920, //û��Ȩ��
	eText_Country_Broadcast_TimeLimit		 =8921, //��������
	eText_Country_Broadcast_NotEnoughMoney	 =8922, //��Ǯ����

	eText_Country_Appoint_NotFound			 =8923,	//δ�ҵ������
	eText_Country_Appoint_Success			 =8924, //������Ա�ɹ�
	eText_Country_Appoint_NotRight			 =8925, //��û��Ȩ��������Ա
	eText_Country_Appoint_NotCountryMember	 =8926, //���Ǳ�����Ҳ�������Ϊ��Ա
	eText_Country_Appoint_NotOnline			 =8927, //����������Ҳ����ߣ��޷��������
	eText_Country_Appoint_LevelLess			 =8928, //����������Ҳ���45�����޷�����Ϊ��Ա
	eText_Country_Dismiss_Success			 =8929, //�����Ա�ɹ�
	eText_Country_Dismiss_NotRight			 =8930, //��û��Ȩ�ް����Ա

	eText_Country_Slience_Success			 =8931, //������ѱ�������
	eText_Country_Slience_NotRight			 =8932, //��û�н��Ե�Ȩ��
	eText_Country_Slience_TimeLimit			 =8933, //��ÿ�����ֻ�ܽ���3��
	eText_Country_Slience_NotEnoughMoney	 =8934, //�����ʽ����ƣ���ʱ����
	eText_Country_Slience_NotOnLine			 =8935, //Ŀ��������ڲ����ߣ��޷��������
	eText_Country_Slience_NotSameCountry	 =8936, //Ŀ����Ҳ��Ǳ�����������Ȩ�������

	eText_Country_Prison_Success			 =8937, //������ѱ�������
	eText_Country_Prison_NotRight			 =8938, //��û��������Ȩ��
	eText_Country_Prison_TimeLimit			 =8939, //��ÿ�����ֻ����������3��
	eText_Country_Prison_NotEnoughMoney		 =8940, //�����ʽ����ƣ���ʱ����
	eText_Country_Prison_NotOnLine			 =8941, //Ŀ��������ڲ����ߣ��޷���������
	eText_Country_Prison_NotSameCountry		 =8942, //Ŀ����Ҳ��Ǳ�����������Ȩ��������

	eText_Country_Free_Success				 =8943, //������ѱ�������
	eText_Country_Free_NotRight				 =8944, //��û�������Ȩ��
	eText_Country_Free_TimeLimit			 =8945, //��ÿ�����ֻ����������3��
	eText_Country_Free_NotEnoughMoney		 =8946, //�����ʽ����ƣ���ʱ����
	eText_Country_Free_NotOnLine			 =8947, //Ŀ��������ڲ����ߣ��޷���������
	eText_Country_Free_NotSameCountry		 =8949, //Ŀ����Ҳ��Ǳ�����������Ȩ��������

	eText_Country_Operate_Slience			 =8950, //��������������
	eText_Country_Operate_Prison			 =8951, //��������������
	eText_Country_Operate_Free				 =8952, //��������������

	eText_Country_Task_Success				 =8953, //���񷢲��ɹ�
	eText_Country_Task_NotRight				 =8954, //��û��Ȩ�޷�������
	eText_Country_Task_Already				 =8955, //�ù����Ѿ�����
	eText_Country_Task_NotEnoughMoney		 =8956, //������Դ���㣬�޷���������

	eText_Country_Task_BullBegin			 =8957, //�Ѿ�����
	eText_Country_Task_BullEnd				 =8958, //�Ѿ�����

	eText_Country_Donate_Success			 =8960,	//ļ���ɹ�
	eText_Country_Donate_LevelLess			 =8961,	//����ȼ�����
	eText_Country_Donate_NotEnoughMoney		 =8962,	//�����Ǯ����
	eText_Country_Donate_ErrorRaiseMoney	 =8963,	//ļ����Ǯ�������ֵ
	eText_Country_Donate_NotRaiseTime		 =8964,	//����ļ��ʱ�� ����ļ��
	eText_Country_Donate_CountryMoneyMax	 =8965,	//�����ʽ��Ѿ�����ˣ��޷�ļ��

	eText_Country_Describe_Random            =8966, //�������˵��

	eText_Country_Kill_Offical				 =8970,	//ɱ����Ա
	eText_Country_Border_Fight				 =8971, //�߾����� 
	eText_Country_Border_Defend				 =8972, //�������� 

	eText_Country_Fly_NoRight				 =8973, //ֻ���󲶺��Ҳ����ܽ��д��� 
	eText_Country_Fly_Overdue				 =8974, //����ʧЧ 

	eText_Country_Mount_Success				 =8975,	//��ȡ����ɹ�
	eText_Country_Mount_NotRight			 =8976,	//û����ȡ�����Ȩ��
	eText_Country_Mount_Alreadly			 =8977,	//�Ѿ���ȡ������
	eText_Country_Mount_NotHave				 =8978,	//û������Ӧ�ȼ�������
	eText_Country_Mount_MaxCount			 =8979,	//����Я�������ѵ�����

	eText_Country_Describe_LouLan			 =8980,	//¥������˵��
	eText_Country_Describe_KunLun			 =8981,	//���ع���˵��
	eText_Country_Describe_DunHuang			 =8982,	//�ػ͹���˵��
	eText_Country_Describe_LaiYin			 =8983,	//�������˵��

	//����������� �����ҹ�����أ�
	eText_Country_Operate_Appoint               =8984, //%s��ҹ�ѫ׿�����ر�����Ϊ%sְλ��ϣ���ٽ�������׳���ҹ���
	eText_Country_Operate_Dismiss               =8985, //%s��Ա���岻�ʣ���ȥ��ְ�����ϻ���
	eText_Country_Operate_Define1               =8986, //̫ʦ
	eText_Country_Operate_Define2               =8987, //�󶼶�
	eText_Country_Operate_Define3               =8988, //̫ξ
	eText_Country_Operate_Define4               =8989, //���ɽ�


	eText_CountryName						 =8995,	// ����
	eText_Country_LouLan					 =8996, // ¥������
	eText_Country_KunLun					 =8997, // ��������
	eText_Country_DunHuang					 =8998, // �ػ�����
	eText_Country_LaiYin					 =8999, // ��������



	eTextServer_ChangeCorp_AssignMode0       =9000, // �ɹ�ת��Ϊ�Ŷӣ�\n����ģʽΪ:����ģʽ		
	eTextServer_ChangeCorp_AssignMode1       =9001, // �ɹ�ת��Ϊ�Ŷӣ�\n����ģʽΪ:����ģʽ		
	eTextServer_ChangeCorp_AssignMode2       =9002, // �ɹ�ת��Ϊ�Ŷӣ�\n����ģʽΪ:�漴ģʽ		
	eTextServer_ChangeCorp_AssignMode3       =9003, // �ɹ�ת��Ϊ�Ŷӣ�\n����ģʽΪ:����ģʽ		
	eText_Client_GreatGuild_NameFaild        =9004, // �����������ֲ��Ϸ�		
	eText_Server_TeamJoinSuccess             =9005, // �������ɹ�!		
	eText_Server_TeamDisband                 =9006, // �����ɢ		
	eText_Server_TeamLeaved                  =9007, // �����뿪����!		
	eClient_AddInfo_2slk_148                 =9008, // ���%s˵:%s\n 		
	eClient_AddInfo_2slk_149                 =9009, // �����ڻ����� 		
	eTellClient_HighShoutCountLimit          =9010, // ���ѵ�ÿ�����º�������		
	eServer_lessShoutChatColdtime            =9011, // С���ź�Ƶ��������ȴʱ�䣬��ʣ%d��		
	eServer_lessHighShoutChatColdtime        =9012, // С������Ƶ��������ȴʱ�䣬��ʣ%d��		
	eClient_AddInfo_2slk_141                 =9013, // С���ź�Ƶ��������ȴʱ�䣬��ʣ%d��		
	eClient_AddInfo_2slk_142                 =9014, // С������Ƶ��������ȴʱ�䣬��ʣ%d�� 		
	eServer_chat_particular_vip2             =9015, // С����Ϣ2		
	eServer_chat_particular_vip3             =9016, // С����Ϣ3		
	eServer_chat_particular_vip4             =9017, // С����Ϣ4		
	eServer_chat_particular_vip5             =9018, // С����Ϣ5		
	eServer_chat_particular_vip6             =9019, // С����Ϣ6		
	eServer_chat_particular_vip7             =9020, // С����Ϣ7		
	eServer_chat_particular_vip8             =9021, // С����Ϣ8		
	eServer_chat_particular_vip9             =9022, // С����Ϣ9		
	eServer_chat_particular_vip10            =9023, // С����Ϣ10		
	eTextServer_Answer_Change_AssignMode0    =9024, // ����ģʽ�Ѹ���Ϊ:����ģʽ		
	eTextServer_Answer_Change_AssignMode1    =9025, // ����ģʽ�Ѹ���Ϊ:����ģʽ		
	eTextServer_Answer_Change_AssignMode2    =9026, // ����ģʽ�Ѹ���Ϊ:�漴ģʽ		
	eTextServer_Answer_Change_AssignMode3    =9027, // ����ģʽ�Ѹ���Ϊ:����ģʽ		
	eClient_getnewtask_music_path            =9028,    //data/datasoun/1.wav		
	eEnterRaidMapTell =9029,  //׼������[%s],���Ժ�...	
	eCostSilverYunDiRelive =9030,     //ԭ�ظ���		
	eCostSilverWanMeiRelive =9031,     //��������		
	eTellClient_OnlineTime                  =9032,//������%d����,ע����Ϣ!	
	eTellClient_GetExp                       =9033,//���%d%%�ľ����%d%%�ļ��ܾ���		
	eTellClient_ClearOnlineTime          =9034,//����ʱ����0		
	eTellClient_OnlineTimeAndHour                  =9035,//������%dСʱ%d����,ע����Ϣ!	
	eClient_AddInfo_2slk_2         =9036,        //���ܹ��������Ա		
	eClient_AddInfo_2slk_3         =9037,        //���ܹ��������Ա		
	eClient_AddInfo_2slk_44        =9038,        //"��ǰ���������Ѵ�����!"		
	eClient_AddInfo_2slk_46        =9039,        //"��ǰ�˸��������Ѵ�����"		
	eClient_AddInfo_2slk_49        =9040,        //"�޷��ƶ�������ȷ�ش���֤��ͼƬ�ϵ�����"		
	eClient_AddInfo_2slk_50        =9041,        //"��֤�ɹ�"		
	eClient_AddInfo_2slk_51        =9042,        //"�����Ӻ󽫸�����֤ͼƬ������֤"		
	eClient_AddInfo_2slk_52        =9043,        //"�����в���ʹ����Ʒ!"		
	eClient_AddInfo_2slk_53        =9044,        //"������Ʒ����ʹ��!"		
	eClient_AddInfo_2slk_54        =9045,        //"���״̬���ɿ���"		
	eClient_AddInfo_2slk_55        =9046,        //"����״̬���ɹ���"		
	eClient_AddInfo_2slk_56        =9047,        //"����ͼ�������"		
	eClient_AddInfo_2slk_57        =9048,        //"����״̬�������"		
	eClient_AddInfo_2slk_58        =9049,        //"����״̬�в�������"		
	eClient_AddInfo_2slk_59        =9050,        //"ս���в������"		
	eClient_AddInfo_2slk_60        =9051,        //"������˼������"		
	eClient_AddInfo_2slk_61        =9052,        //"��������!��Ʒ�����˵���"  		
	eClient_AddInfo_2slk_114        =9053,        //Ŀ�����̫Զ�����ܲ鿴��		
	eClient_AddInfo_2slk_78        =9054,        //"��ǰ״̬�����ƶ�" 		
	eClient_AddInfo_2slk_79        =9055,        //"�������� %d �㣡��ǰ����Ϊ:%d"  		
	eClient_AddInfo_2slk_81        =9056,        //�����ƶ�������111������Ϣһ��		
	eClient_AddInfo_2slk_82        =9057,        //�����ƶ�������222������Ϣһ��		
	eClient_AddInfo_2slk_83        =9058,        //�����ƶ�������333����Ϣһ�£� %d  		
	eClient_AddInfo_2slk_110        =9059,        //û��ѡ��Ŀ��		
	eClient_AddInfo_2slk_139        =9060,        //%s �� %s ������Ѫ %d		
	eClient_AddInfo_2slk_146        =9061,        //�����Ʒ:%s\n 		
	eServer_picktime_eResultTaskItem =9062,    //"Can`t obtain question item"		
	eServer_picktime_eResultUnknow =9063,        //"You can`t obtain this item"		
	eServer_obtain_item                =9064,    //%s obtain 1 %s		
	eTellClient_IntegralMax =9065,//������Ϣ �������ֵ����:%d,��ǰ�������ֵ:%d	
	eTellClient_Gm2Player_ShowName =9066,//GM����PLAYER��ʾ������		
	eTell_Client_ProtectCharDis =9067,//�뻤�͹������̫Զ!		
	eClient_CantUseGood_ByDiffState             =9068, //��ǰ״̬����ʹ����Ʒ		
	eText_ItemNoPlaceToWaring =9069, //������������ע�⽻����Ʒ�����ڵ��ϡ�		
	eText_Copper =9070, // ͭ		
	eUI_Yes                    =9071,		
	eUI_NO                    =9072,		
	eText_Chat_1                =9073,            //[����]:		
	eTell_Client_ServerExpPer =9074,		
	eTell_Client_ServerSkillExpPer =9075,		
	eNotEnoughEmnity    =9076, // û���㹻��Ǯ		
	eLog_OtherBagItem_In_Compound      =9077, // ������Ϣ ���������Ϸ�������ϳɱ�����Ʒ[%s ID:%s ����:%d]��������:%s		
	eLog_OtherBagItem_In_Intensify     =9078, // ������Ϣ ���������Ϸ�������ǿ��������Ʒ[%s ID:%s ����:%d]��������:%s		
	eLog_OtherBagItem_In_Reduce        =9079, // ������Ϣ ���������Ϸ�������ֽⱳ����Ʒ[%s ID:%s ����:%d]��������:%s		
	eLog_OtherBagItem_In_Unsoul        =9080, // ������Ϣ ���������Ϸ����������󶨱�����Ʒ[%s ID:%s ����:%d]��������:%s		
	eLog_OtherBagItem_In_PrivateShop   =9081, // ������Ϣ ���������Ϸ�����������̵���Ʒ[%s ID:%s ����:%d]��������:%s		
	eLog_OtherBagItem_In_LockIntensify =9082, // ������Ϣ ���������Ϸ�������ǿ������������Ʒ[%s ID:%s ����:%d]��������:%s		
	eLog_OtherBagItem_Exit_Compound =9083,      // ������Ϣ �����뿪��Ϸ�������ϳɱ�����Ʒ[%s ID:%s ����: %d]��������:%s		
	eLog_OtherBagItem_Exit_Intensify =9084,     // ������Ϣ �����뿪��Ϸ�������ǿ��������Ʒ[%s ID:%s ����: %d]��������:%s		
	eLog_OtherBagItem_Exit_Reduce =9085,        // ������Ϣ �����뿪��Ϸ�������ֽⱳ����Ʒ[%s ID:%s ����: %d]��������:%s		
	eLog_OtherBagItem_Exit_Unsoul =9086,        // ������Ϣ �����뿪��Ϸ����������󶨱�����Ʒ[%s ID:%s ����: %d]��������:%s		
	eLog_OtherBagItem_Exit_PrivateShop =9087,   // ������Ϣ �����뿪��Ϸ�����������̵���Ʒ[%s ID:%s ����: %d]��������:%s		
	eLog_OtherBagItem_Exit_LockIntensify =9088, // ������Ϣ �����뿪��Ϸ�������ǿ������������Ʒ[%s ID:%s ����: %d]��������:%s		
	eTextGuild_No_Master                    =9089,//�Բ����㲻�ǰ��ɳ���û��Ȩ���޸�		
	eText_Guild_Addition_Exp                =9090,//��õ����ɾ���%d		
	eTextGuild_Error_Create_NullName =9091,            //�����ڵĹ����Ѿ�����ɢ		
	eTextGuild_Error_Create_NameError =9092,           //�������������зǷ��ַ�!		
	eTextGuild_Error_Create_NameLong =9093,            //��������ʧ��!������̫��		
	eTextGuild_Error_Create_NameHaveNull =9094,        //��������ʧ��!���������ܰ����ո�		
	eTextGuild_Error_Create_PlayLevelNoEnough =9095,           //��������ʧ��!�����˵ȼ�����		
	eTextGuild_Error_Create_HaveGuild =9096,           //��������ʧ��!���Ѿ������˹���		
	eTextGuild_Error_Create_HaveName =9097,            //��������ʧ��!������[%s]�Ѵ���		
	eTextGuild_Create_Bull =9098,                      //��%s�����ἴ�ճ������ش��Ѹ����¡�		
	eClient_AddInfo_2slk_84        =9099,        //%s �ܾ����빫��		
	eClient_AddInfo_2slk_71        =9100,        //"�˺ű����µ�½����������������ӽ��Ͽ�"		
	eClient_OpFailReasonInBlacklist             =9101, // ����ʧ��,���� %s ��������	
	eClient_AddInfo_2slk_45        =9102,        //����[%s]		
	eLog_info_2slk_19    =9103,    //���������Ʒ %s[%s]		
	eLog_info_2slk_21    =9104,    //���� %s ����[%d]��Ϊ %d		
	eLog_info_2slk_22    =9105,    //���� %s ����[%d]��Ϊ %d		
	eLog_info_2slk_54    =9106,    //�˳���Ϸ����, ip[%s], ����������Ϸʱ��[%u]����, ������ʱ��[%u]����	
	eLog_info_2slk_163 =9107, //�˳���Ϸ��Ǯ��Ϣ ��ǰ�Ľ�Ǯ%d �ֿ��Ǯ%d ��Ʊ%d		
	eLog_info_2slk_146    =9108,    //�õ���Ʒ ����[ID:%d,����:%d]	
	eLog_info_2slk_55    =9109,    //ʰȡ��Ʒ ��Ʒ:%s GUID:%s ����:%d		
	eLog_info_2slk_56    =9110,    //������Ʒ ��Ʒ:%s GUID:%s ����:%d		
	eLog_info_2slk_57    =9111,    //�ű����Ա�� Index��:%d ����ֵ��Ϊ:%d		
	eLog_info_2slk_158    =9112,    //�ƶ���Ʒ ������Ʒλ�ø���:Dst Idx[%d] id[%d] cnt[%d] -> Src Idx[%d] id[%d] cnt[%d]		
	eLog_info_2slk_62    =9113,    //ʹ����Ʒ ����(HP:%d MP:%d) Ŀ��(%s ID:%d HP:%d MP:%d) ʹ����Ʒ:%s ʱ��:%d		
	eServer_picktime_eResultItemTime =9114,    //"Item safe time %d`s"		
	eClient_AddInfo_2slk_88        =9115,        //��ǰ��ͼID:%ld ����Character����:%d �������:%d  		
	eClient_AddInfo_2slk_89        =9116,        //��ͼ��δ����Ĺ�����:%d  		
	eClient_AddInfo_2slk_90        =9117,        //�ϴα���ʱ���� %d 		
	eClient_AddInfo_2slk_91         =9118,        //"�˺������ʾ����:%d"		
	eClient_AddInfo_2slk_92         =9119,        //������������ʾ����:%d		
	eClient_AddInfo_2slk_93         =9120,        //���ʹ�ü�����Ʒ��־����		
	eClient_AddInfo_2slk_94         =9121,        //���ʹ�ü�����Ʒ��־�ر�		
	eClient_AddInfo_2slk_95         =9122,        //�������Map:%d | X:%d | Y:%d		
	eClient_AddInfo_2slk_99         =9123,        //��ǰû��ѡ�й���		
	eClient_AddInfo_2slk_100        =9124,        //���ҹ���ʧ�ܣ���ǰ����ID:%d		
	eClient_AddInfo_2slk_101        =9125,        //��ǰѡ�еĲ��ǹ���		
	eClient_AddInfo_2slk_102        =9126,        //��ǰ�����AI�Ƿ���:%d		
	eClient_AddInfo_2slk_103        =9127,        //��ǰ����ID:%d�����ﵱǰĿ��ID:%d		
	eClient_AddInfo_2slk_104        =9128,        //��ǰ����ʹ�ü���ID:%d�����ܵȼ�:%d		
	eClient_AddInfo_2slk_105        =9129,        //��ǰ�����ͼID:%d��X:%d��Y:%d		
	eClient_AddInfo_2slk_106        =9130,        //��ǰ����Ŀ�ĵ�X:%d��Y:%d		
	eClient_AddInfo_2slk_107        =9131,        //��ǰ�������ĳ��:%d		
	eClient_AddInfo_2slk_108        =9132,        //��ǰ����ĳ�������:%d		
	eClient_AddInfo_2slk_109        =9133,        //��ǰ����Ŀ���ͼID:%d��X:%d��Y:%d		
	eLog_info_2slk_60    =9134,    //�������� ����:%s ID:%d ����%d��		
	eLog_info_2slk_61    =9135,    //������Ʒ ��Ʒ:%s GUID:%s		
	eLog_info_2slk_63    =9136,    //�̵���� �޴��̵�		
	eLog_info_2slk_65    =9137,    //NPC��Զ ��ǰ��:%f		
	eLog_info_2slk_68    =9138,    //�̵���� �̵�û��ô�����		
	eLog_info_2slk_69    =9139,    //��Ʒ���� ItemDetail�Ҳ�������ƷId:%d		
	eLog_info_2slk_70    =9140,    //����ʧ�� û���㹻���Ǯ ��ǰǮ:%d		
	eLog_info_2slk_71    =9141,    //������Ʒʧ�� ��Ʒ����Id:%d		
	eLog_info_2slk_72    =9142,    //������Ʒ ��Ʒ:%s ID:%s ����:%d �� NPC:%s		
	eLog_info_2slk_73    =9143,    //��Ʒ���� �������޴���Ʒ		
	eLog_info_2slk_74    =9144,    //��Ʒ���� �������޴���Ʒ		
	eLog_info_2slk_75    =9145,    //��Ʒ���� ��������Ʒû��ô��		
	eLog_info_2slk_77    =9146,    //��Ʒ���� ��Ʒ:%s ���������̵�!		
	eLog_info_2slk_78    =9147,    //�������� �����̵��������ÿ������		
	eLog_info_2slk_79    =9148,    //��Ʒ���� ���Ǵ�����Ʒ ��Ʒ����:%d Ŀ������:%d		
	eLog_info_2slk_80    =9149,    //������Ʒ ��Ʒ:%s ID:%s ����:%d �� NPC:%s		
	eLog_info_2slk_81    =9150,    //������Ϸ��Ǯ��Ϣ ��ǰ�Ľ�Ǯ%d �ֿ��Ǯ%d ��Ʊ%d		
	eLog_info_2slk_82    =9151,    //ѧϰ���� ����:%s ID:%d		
	eLog_info_2slk_83    =9152,    //�������� ����:%s ID:%d		
	eLog_info_2slk_85    =9153,    //��Ӳֿ���Ʒ ��Ʒ:%s GUID:%s ����:%d λ��: %d		
	eLog_info_2slk_27    =9154,    //AccountID:%d GetYuanBao GUID:%s ItemID:%d		
	eLog_info_2slk_28    =9155,    //AccountID:%d UpdateYuanBao GUID:%s ItemID:%d		
	eLog_info_2slk_147   =9156,    //ʹ�õ��߼�¼ UseItem��װ���ӱ�����ȡ��[%s ID:%d]		
	eLog_info_2slk_148   =9157,    //ʹ�õ��߼�¼ UseItem����оɵ�װ������Żر�����[ID:%d,���� %d]	
	eLog_info_2slk_149   =9158,    //ʹ�õ��߼�¼ UseItem��װ���Żر�����(��Ϊ����װ��)[ID:%d,���� %d]	
	eLog_info_2slk_41    =9159,    //�ƶ����� �� �����ٶ�%f(%f/%d) ��ʱ����ֵ%d ��ʱ�ƶ��ٶ�%f		
	eLog_info_2slk_42    =9160,    //�ƶ����� �� �����ٶ�%f(%f/%d) ��ʱ����ֵ%d ��ʱ�ƶ��ٶ�%f		
	eLog_info_2slk_43    =9161,    //�ƶ����� �� �����ٶ�%f(%f/%d) ��ʱ����ֵ%d ��ʱ�ƶ��ٶ�%f		
	eLog_info_2slk_44    =9162,    //������� ����ֵΪ%d ����ǿ��������		
	eLog_info_2slk_46    =9163,    //������� ����ֵΪ%d ��¼�ڰ� ��������Ϊ20000		
	eLog_info_2slk_47    =9164,    //������� ����ֵΪ%d ��¼�ڰ� ��������Ϊ20000		
	eLog_info_2slk_48    =9165,    //ʹ����� �����ƶ���Ϣ����������Ҹ�����		
	eLog_info_2slk_49    =9166,    //ʹ����� �����ƶ���Ϣ����������Ҹ�����		
	eLog_info_2slk_50    =9167,    //ʹ����� �ƶ���Ϣ�������˱��ٳ��� %d 		
	eLog_info_2slk_51    =9168,    //�ƶ����� ��·;�ϡ�·��ID%d ·������%s		
	eLog_info_2slk_52    =9169,    //�ƶ����� ��·;�ϡ�·��ID%d		
	eClient_AddInfo_2slk_150        =9170,        //"���Ǳ����ƣ���ս������" 		
	eClient_AddInfo_2slk_134        =9171,        //��%s���������Ϊ %d		
	eClient_AddInfo_2slk_135        =9172,        //��%s�������Ϊ�����µ�����		
	eClient_AddInfo_2slk_63        =9173,        //"�������ǵ��������������ܱ���"  		
	eClient_AddInfo_2slk_64        =9174,        //"�㻹û�м��빫�ᣬ���ܱ���"  		
	eClient_AddInfo_2slk_65        =9175,        //"�㲻�ǻ᳤���߸��᳤�����ܱ���"  		
	eClient_AddInfo_2slk_70        =9176,        //"�����ڵĹ����Ѿ������ɹ��������ٴα���"  		
	eLog_info_2slk_29    =9177,    //���� ��:%d����:%d��		
	eLog_info_2slk_30    =9178,    //ɱ��[%s]��þ���: [%d]
	eLog_info_2slk_36    =9179,    //��ͨ���� ����(HP:%d MP:%d PKֵ:%d �ȼ�:%d ����:%d:%d:%d) �ܻ���(%s ID:%d HP:%d MP:%d �ȼ�:%d ����:%d:%d:%d) ʱ��:%d		
	eLog_info_2slk_38    =9180,    //���﹥�� ����(HP:%d MP:%d PKֵ:%d �ȼ�:%d ����:%d:%d:%d) ����:%s �ܻ���(%s ID:%d HP:%d MP:%d �ȼ�:%d ����:%d:%d:%d ) ʱ��:%d		
	eLog_info_2slk_39    =9181,    //GettheItemDetail().GetItemByID Failed ItemID[%d]		
	eLog_info_2slk_40    =9182,    //������Ʒ ��Ʒ:%s GUID:%s ����:%d		
	eLog_info_2slk_25    =9183,    //CharacterFormulaService::ApplyExp(pTarget->IsDead())���%d����ֵ(�Ŷ�)		
	eLog_info_2slk_26    =9184,    //CharacterFormulaService::ApplyExp()���%d����ֵ���Ŷԣ�		
	eLog_info_2slk_35    =9185,    //�ű�����������þ���: [%d]		
	eClient_AddInfo_2slk_137        =9186,        //%s�������		
	eClient_AddInfo_2slk_138        =9187,        //%s�뿪����		
	eLog_info_2slk_23    =9188,    //������� �����г�Ա		
	eLog_info_2slk_24    =9189,    //������� �����г�Ա		
	eText_NoGuild        =9190,//�޹���		
	eLog_info_2slk_7    =9191,    //Learn Skill failed:%d		
	eLog_info_2slk_8    =9192,    //Learn Skill success:%d		
	eClient_AddInfo_2slk_72        =9193,        //"�˸�����������,�㽫�����ͳ�ȥ"	
	eClient_AddInfo_2slk_73        =9194,        //"���ŶӸ����Ѳ�������,�㽫�����ͳ�ȥ"	
	eClient_AddInfo_2slk_74        =9195,        //"�˶��ŶӸ����Ѳ�������,�㽫�����ͳ�ȥ"	
	eTell_Client_KillAndAddPkValue =9196,//��ɱ����%s,���%d������!	
	eLog_info_2slk_137    =9197,    //ɱ����� Ŀ�����:%s:%d ��ǰPKֵ:%d �ȼ�:%d �Է��ȼ�:%d ����[%d:%d:%d]Ŀ������[%d:%d:%d] ʱ��:%d		
	eLog_info_2slk_138    =9198,    //ɱ����� Ŀ�����:%s:%d �������һ�ι���ʱ����̫�� ʱ��:%d ��󹥻�ʱ��:%d		
	eLog_info_2slk_139    =9199,    //ɱ����� Ŀ�����:%s:%d ����û���ҵ�������¼ ʱ��:%d		
	eLog_info_2slk_140    =9200,    //�ű�ɾ�� ��Ʒ:%s ����:%d		
	eLog_info_2slk_141    =9201,    //�ű���� %d����Ʒ:%s ID:%s		
	eLog_info_2slk_142    =9202,    //�ű���� %d����Ʒ:%s ����������!��Ʒ�����˵���		
	eLog_info_2slk_143    =9203,    //ʰȡ������� %d����Ʒ:%s ����������!		
	eLog_info_2slk_144    =9204,    //%d����Ʒ:%s ʧ��		
	eLog_info_2slk_126    =9205,    //ʹ�ü��� HP:%d MP:%d �� %s(%d HP:%d MP:%d) ʹ�ü���:%s ʱ��:%d		
	eLog_info_2slk_127    =9206,    //ʹ�ü��� HP:%d MP:%d ʹ�ü���:%s ʱ��:%d		
	eLog_info_2slk_128    =9207,    //��ֵ���� �������ܾ� ��ֵ��ֵΪ���Ķ���ItemName:%s ��ֵʧ��		
	eLog_info_2slk_129    =9208,    //��ֵ�ɹ� ����Ʒ:%s ID:%s ����Ʒ��ֵ�ɹ� ��Ʒ����ʱ��Ϊ: %d/%d/%d %d:%d		
	eLog_info_2slk_130    =9209,    //��ֵʧ�� ����Ʒ:%s ID:%s ����Ʒ��ֵ		
	eLog_info_2slk_14    =9210,    //�õ���Ʒ ��Ʒ:%s GUID:%s ����:%d		
	eLog_info_2slk_156    =9211,    //��ȡԪ�� ID:%d ����:%d		
	eLog_info_2slk_0    =9212,    //��%ld��if���û��ƥ������.\n		
	eLog_info_2slk_1    =9213,    //��%ld��else���û��ƥ������.\n		
	eLog_info_2slk_2    =9214,    //��%ld��endif���û��ƥ������.\n		
	eLog_info_2slk_3    =9215,    //��%ld��proc_start���Ƿ�Ƕ��.\n		
	eLog_info_2slk_4    =9216,    //��%ld��proc_end���Ƿ�Ƕ��.\n		
	eLog_info_2slk_5    =9217,    //��%ld�е�if���ƥ�䲻����.\n		
	eLog_info_2slk_6    =9218,    //��%ld���±�Խ��.\n		
	eLog_info_2slk_131    =9219,    //�𶧲��� ��ʼ����: %u		
	eLog_info_2slk_132    =9220,    //�𶧲��� ��������: %u, ��ǰ����: %u		
	eLog_info_2slk_133    =9221,    //�𶧲��� ��������: %u		
	eLog_info_2slk_134    =9222,    //�𶧲��� Ŀǰ��Ʊ����: %u		
	eLog_info_2slk_135    =9223,    //ɾ����Ʒ ��Ʒ:%s ����:%d		
	eLog_info_2slk_136    =9224,    //�̳ǹ��� ��Ʒ:%s GUID:%s ����:%d ���̳ǹ���		
	eClient_AddInfo_2slk_136        =9225,        //�����������=%ld	
	eLog_info_2slk_150    =9226,    //װ����¼ OnEquipToWhere��װ���ӱ�����ȡ��[%s ID:%d]		
	eLog_info_2slk_151    =9227,    //װ����¼ OnEquipToWhere����оɵ�װ������Żر�����[ID:%d,���� %d]	
	eLog_info_2slk_152    =9228,    //װ����¼ OnEquip��װ���ӱ�����ȡ��[%s ID:%d]		
	eLog_info_2slk_153    =9229,    //װ����¼ OnEquip����оɵ�װ������Żر�����[ID:%d,���� %d]	
	eLog_info_2slk_154    =9230,    //װ����¼ UnEquip[ID:%d,���� %d]	
	eLog_info_2slk_98     =9231,    //��Ʒ���� ��Ʒ:%s ID:%s ����:%d ��������:%d/%d/%d %d:%d:%d		
	eLog_info_2slk_102    =9232,    //��ֵ ����Ʒ:%s ID:%s ����Ʒ��ֵ ��Ʒ����ʱ��:%d/%d/%d %d:%d		
	eLog_info_2slk_103    =9233,    //��ֵ ����Ʒ:%s ID:%s ����Ʒ��ֵ ��Ʒ����ʱ��:%d/%d/%d %d:%d		
	eLog_info_2slk_104    =9234,    //��ֵ ����Ʒ:%s ID:%s ����Ʒ��ֵ ��Ʒ����ʱ��:%d/%d/%d %d:%d		
	eLog_info_2slk_105    =9235,    //[%s:%d]ʧȥ��Ǯ ʧȥ��Ǯ%d ��ǰ��Ǯ%d		
	eLog_info_2slk_106    =9236,    //[%s:%d]�õ���Ǯ �õ���Ǯ%d ��ǰ��Ǯ%d		
	eLog_info_2slk_107    =9237,    //������Ϸ������Ϣ \t%s ID[%d] GUID[%s] Count[%d] Pos[%d] Other[%s]		
	eLog_info_2slk_108    =9238,    //������Ϣ ����DB��Ϣ�б����е���Ʒ \t%s ID[%d] GUID[%s] Count[%d] Other[%s]	
	eLog_info_2slk_109    =9239,    //�ƶ���Ʒ GUID:%s ID:%d ����:%d �ӱ�����ǿ��ʯͷ		
	eLog_info_2slk_110    =9240,    //�ƶ���Ʒ GUID:%s ID:%d ����:%d ��ǿ��ʯͷ������		
	eLog_info_2slk_111    =9241,    //�ƶ���Ʒ GUID:%s ID:%d ����:%d �ӱ�����ǿ��װ��		
	eLog_info_2slk_112    =9242,    //�ƶ���Ʒ GUID:%s ID:%d ����:%d ��ǿ��ʯͷ������		
	eLog_info_2slk_113    =9243,    //�ƶ���Ʒ GUID:%s ID:%d ����:%d �ӱ�����ǿ������Luck		
	eLog_info_2slk_114    =9244,    //�ƶ���Ʒ GUID:%s ID:%d ����:%d ��ǿ������Luck������		
	eLog_info_2slk_115    =9245,    //�ƶ���Ʒ GUID:%s ID:%d ����:%d �ӷֽⱳ���ƶ���װ��		
	eLog_info_2slk_116    =9246,    //�ƶ���Ʒ GUID:%s ID:%d ����:%d ��װ���ƶ����ֽⱳ��		
	eLog_info_2slk_117    =9247,    //�ƶ���Ʒ GUID:%s ID:%d ����:%d �ӷֽ��Ʒ�ƶ�������		
	eLog_info_2slk_118    =9248,    //�ֽ���Ʒ ID:%d GUID:%s		
	eLog_info_2slk_119    =9249,    //�ֽ�����Ʒ ID:%d GUID:%s		
	eLog_info_2slk_120    =9250,    //�������Ʒ ID:%d GUID:%s		
	eLog_info_2slk_121    =9251,    //�ƶ���Ʒ GUID:%s ID:%d ����:%d �ӱ����ƶ������		
	eLog_info_2slk_122    =9252,    //�ƶ���Ʒ GUID:%s ID:%d ����:%d �ӱ����ƶ������		
	eLog_info_2slk_123    =9253,    //�ƶ���Ʒ GUID:%s ID:%d ����:%d �ӱ����ƶ�����ǿ��		
	eLog_info_2slk_124    =9254,    //�ƶ���Ʒ GUID:%s ID:%d ����:%d ����ǿ���ƶ�������		
	eLog_info_2slk_125    =9255,    //����ǿ�� ID:%d GUID:%s ��ǰǿ���ȼ�:%d		
	eLog_info_2slk_155    =9256,    //�ϳ������Ʒ[ID:%d,����:%d]	
	eLog_info_2slk_165    =9257,    //�˳���Ϸװ������Ϣ ��Ϸ����װ������Ʒ:%s ID:%s ����:%d		
	eLog_info_2slk_166    =9258,    //������Ϸװ������Ϣ ��Ϸ����װ������Ʒ:%s ID:%s ����:%d		
	eLog_info_2slk_9      =9259,    //������Ʒ ��ʼ %s��%s		
	eLog_info_2slk_11     =9260,    //ʧȥ��Ʒ ��Ʒ:%s GUID:%s ����:%d 		
	eLog_info_2slk_12     =9261,    //ʧȥ��Ʒ ��Ʒ:%s GUID:%s ����:%d 		
	eLog_info_2slk_13     =9262,    //�õ���Ʒ ��Ʒ:%s GUID:%s ����:%d �����Ų��½���������		
	eLog_info_2slk_15     =9263,    //�õ���Ʒ ��Ʒ:%s GUID:%s ����:%d �����Ų��½���������		
	eLog_info_2slk_16     =9264,    //�õ���Ʒ ��Ʒ:%s GUID:%s ����:%d		
	eLog_info_2slk_17     =9265,    //������Ʒ ��� %s��%s		
	eLog_info_2slk_86     =9266,    //�ƶ���Ʒ GUID:%s ID:%d ����:%d �ӱ����ƶ��������̵�		
	eLog_info_2slk_87     =9267,    //�ƶ���Ʒ GUID:%s ID:%d ����:%d �Ӹ����̵��ƶ��������̵�		
	eLog_info_2slk_88     =9268,    //�ƶ���Ʒ GUID:%s ID:%d ����:%d �Ӹ����̵��ƶ�������		
	eLog_info_2slk_89     =9269,    //�ƶ���Ʒ ��Ʒ:%s GUID:%s ����:%d �ӱ����ƶ����ֿ�		
	eLog_info_2slk_90     =9270,    //�ƶ���Ʒ ��Ʒ:%s GUID:%s ����:%d �Ӳֿ��ƶ�������		
	eLog_info_2slk_91     =9271,    //���״̬ ��Ʒ:%s		
	eLog_info_2slk_92     =9272,    //������Ʒ ���:%s ID:%ld �����̵���Ʒ:%s GUID:%s ����:%d		
	eLog_info_2slk_93     =9273,    //������Ʒ ���:%s ID:%ld �����̵���Ʒ:%s GUID:%s ����:%d		
	eLog_info_2slk_94     =9274,    //�ƶ���Ʒ ��ƷGUID:%s ����ID:%d ����:%d �Ӻϳɳ�Ʒ�ƶ�������		
	eLog_info_2slk_95     =9275,    //�ƶ���Ʒ ��ƷGUID:%s ����ID:%d ����:%d �Ӻϳɲ����ƶ�������		
	eLog_info_2slk_96     =9276,    //�ƶ���Ʒ ��ƷGUID:%s ����ID:%d ����:%d �ӱ����ƶ����ϳɲ���		
	eLog_info_2slk_97     =9277,    //�ϳ���Ʒ ����ID:%d GUID:%s		
	eLog_info_2slk_159    =9278,    //�ƶ���Ʒ �ֿ�->�ֿ�: %d %d -> %d %d		
	eLog_info_2slk_160    =9279,    //�ƶ���Ʒ ��ƷGUID:%s ����ID:%d ����:%d �Ӻϳɲ����ƶ�������		
	eLog_info_2slk_161    =9280,    //�����Ʒ ����������Ʒ[GUID:%s,ID:%d,���� %d]
	eLog_IntensifySucc_Info1 =9281,//ǿ����Ʒ �ɹ� ��������:%s GUID:%s ǿ��ǰ�ȼ�:%d ǿ����ȼ�:%d ʹ�õĿ���:%s ʹ�õķ���:%s		
	eLog_IntensifySucc_Info2 =9282,//ǿ����Ʒ �ɹ� ��������:%s GUID:%s ǿ��ǰ�ȼ�:%d ǿ����ȼ�:%d ʹ�õĿ���:%s 		
	eLog_IntensifyFail_Info1 =9283,//ǿ����Ʒ ʧ�� ��������:%s GUID:%s ǿ��ǰ�ȼ�:%d ǿ����ȼ�:%d ʹ�õĿ���:%s ʹ�õķ���:%s		
	eLog_IntensifyFail_Info2 =9284,//ǿ����Ʒ ʧ�� ��������:%s GUID:%s ǿ��ǰ�ȼ�:%d ǿ����ȼ�:%d ʹ�õĿ���:%s 		
	eTextGuild_Error_NotMember =9285,              //Ŀ�겻�ǹ����Ա		
	eTextGuild_Success_Create =9286,               //��������ɹ�		
	eTextGuild_Error_Disband_CityMaster =9287,     //����ռ���߲��ܽ�ɢ����		
	eTextGuild_Error_Disband_NotMaster =9288,      //�㲻�ǻ᳤�����ܽ�ɢ����		
	eTell_Client_KillAndSubPkValue =9289,//��ɱ����%s,����%d������!	
	eClient_Frddlg_CantBlackIsStudent           =9290, // %s ����ͽ���޷����������		
	eClient_Frddlg_CantToBlackBecauseIsMarrage  =9291, // %s ��������޷����������		
	eLog_info_2slk_20    =9292,    //ɱ������ %s[%d]		
	eClient_AddInfo_2slk_111        =9293,        //���������κι��ᣬ����������˼���.		
	eClient_AddInfo_2slk_112        =9294,        //���������Ҳ����ڻ��߲�����.		
	eLog_OnEquip_PushError                =9295, //OnEquip_PushError��Żر�����[ID:%d,���� %d]    	
	eLog_AddIntegral                      =9296, //�������� ��������:%d��,��ǰ����Ϊ:%d,�������ֵ:%d
	eTell_Client_AddPkValuePerTime        =9297, //����%d������ֵ		
	eLog_CreateID2_Debug                  =9298, //CreateID���� ����CreateID2[%s]		
	eClient_AddInfo_2slk_113        =9299,        //��ǰ��ͼ��ѭʱ�� %d ms		
	eLog_info_2slk_164 =9300, //�˳���Ϸ������Ϣ ��Ϸ���米����Ʒ \t%s ID[%d] GUID[%s] Count[%d] Pos[%d %s]
	eClient_Error_Me_InFightCanNotAddFriend     =9301, // ս��״̬���ܼӺ���		
	eClient_Error_Target_InFightCanNotAddFriend =9302, // �Է���ս��״̬���ܼӺ���		
	eServer_AddPersonMarriage        =9303,        //%s�����Ϊ��		
	eServer_AddPersonBrother            =9304,        //%s�����Ϊ�ֵ�		
	eServer_AddPersonTeacher        =9305,        //%s����Ϊͽ		
	eServer_AddPersonStudent            =9306,        //%s����Ϊʦ��    		
	eLog_info_2slk_145    =9307,    //"Ԫ������Ʊ[ID:%d ����:%d]"		
	eTextGuild_Error_Disband_NoGuild =9308,            //�㻹û�м��빫��		
	eMessageBox_GuildMasterOffline        =9309, // [%s]����᳤������		
	eMessageBox_LeagueErrorNotGuildMaster =9310, // �㲻�ǻ᳤���������˲���		
	eTellClient_AgreeLeague               =9311, //%s ���������Ĺ������ˣ�		
	eTellClient_RefuseLeague              =9312, //%s ����ܾ�����������룡		
	eClinet_people_join_team        =9313,    //%s �������		
	eLog_info_2slk_31    =9314,    //��ü��ܾ��� ������:%s ����:%s		
	eLog_info_2slk_32    =9315,    //���ܾ��� ������:%s ����:%s		
	eLog_ExitWorldPkValue                =9316,  //�����뿪��Ϸ��������ֵ%d		
	eLog_Exit_shenqi              =9317,//�����뿪��Ϸ��������ֵ%d		
	eMessageBox_InviterIsOffline          =9318, // ��������˲����� 		
	eTellClient_RefuseAddFriend               =9319, // %s �ܾ���Ӻ�������		
	eTellClient_PKValueDailyMax           =9320, //���ջ������ֵ�ѵ����!		
	eLog_EnterWord_zhenying              =9321,//���������Ϸ������Ӫ����ֵ%d		
	eLog_EnterWord_lingqian              =9322,//���������Ϸ������Ǳֵ%d		
	eLog_EnterWord_taozhu1              =9323,//���������Ϸ��������2949����ֵ%d		
	eLog_Exit_taozhu2              =9324,//�����뿪��Ϸ��������2950����ֵ%d		
	eLog_Exit_zhenying              =9325,//�����뿪��Ϸ������Ӫ����ֵ%d		
	eLog_Exit_lingqian              =9326,//�����뿪��Ϸ������Ǳֵ%d		
	eTellClient_RelationNeutralism        =9327, //%s ����� %s �������� 		
	eTellClient_RelationLeague            =9328, //%s ����� %s ��������		
	eTellClient_RelationAdverse           =9329, //%s ����� %s ����ж�		
	eLog_EnterWord_taozhu2              =9330,//���������Ϸ��������2950����ֵ%d		
	eLog_EnterWord_shenqi              =9331,//���������Ϸ��������ֵ%d		
	eLog_EnterWorldPkValue                =9332, //���������Ϸ��������ֵ%d		
	eLog_Exit_taozhu1              =9333,//�����뿪��Ϸ����������2949��ֵ%d		
	eTextGuild_Error_Disband_Battle =9334,         //�Ѿ������μӳ�ս�Ĺ��᲻�ܱ���ɢ		
	eTextGuild_Error_Invite_Battle =9335,          //���ڲμӳ�ս�Ĺ��᲻�������³�Ա		
	eTextGuild_Error_Invite_TargetHaveGuild =9336, //�Է��Ѿ�����һ������		
	eTextGuild_Error_Invite_MemberNumMax =9337,    //���������Ѿ��ﵽ����%d��		
	eTextGuild_Error_Invite_NotMaster =9338,       //�㲻�ǻ᳤�����������Ա		
	eTextGuild_Error_Ban_Battle =9339,             //�Է����ڲμӳ�ս����ʱ���ܱ�����		
	eTextGuild_Error_Ban_NotMaster =9340,          //�㲻�ǻ᳤�����ܿ�����Ա		
	eTextGuild_Error_Leave_Battle =9341,           //�μӳ�սʱ�����˻�		
	eTextGuild_Error_Leave_Master =9342,           //�᳤����ֱ���˳��л�		
	eTextGuild_Error_Join_MemberMax =9343,         //�Է�������������		
	eTextGuild_Join =9344,                         //������ˡ�%s������		
	eTextGuild_Join_Member =9345,                  //%s �����˹���		
	eTextGuild_Ban_Member =9346,                   //%s �������˹���		
	eTextGuild_Leave_Member =9347,                 //%s �뿪�˹���		
	eTextGuild_GetExp                       =9348,//�����ڵĹ�����%d����ֵ		
	eTell_Client_CannotTaskBCLevel        =9349, //���ĵȼ�����,���ܽ��������!	
	eTell_Client_CannotTaskBCMoney =9350,//����Ǯ����,���ܽ��������!	
	eTell_Client_CannotTaskBCFrontQuest =9351, // ��û�����ǰ������		
	eTell_Client_CannotTaskBCItem = 9352,//��û��ָ�����������,���ܽ��������!
	eTell_Client_CannotTaskBCEnergy = 9353,//���Ļ�������,���ܽ��������!
	eTell_Client_CannotTaskBCReputation = 9354,//������������,���ܽ��������!
	eTell_Client_CannotTaskBCSex = 9355,//�����Ա��ʺϽ��������!
	eTell_Client_CannotTaskBCProfession = 9356,//���ı��ֲ��ʺϽ��������!
	eServer_AddVendetta             =    9357,            //�㱻%sɱ��
	eTextGuild_Disband = 9358,                      //�����ڵĹ����Ѿ�����ɢ
	eTellClient_ShopCenterOff = 9359,//�̳���Ϣ �����̳��ۿ�%%n!
	eGetYuanBao                     = 9360, //��ȡ��վ������Ʒ
	eGetYuanBaoFaild                = 9361, //��ȡԪ��ʧ�ܣ�����Ʒ���Ի�ã�
	eTell_Client_CostAndRemain = 9362, //����%d���ң����%d���� **���￪ʼ17173��
	eUpdateYuanBaoSucc              = 9363, //�ύԪ���ɹ�
	eUpdateYuanBaoFaild             = 9364, //�ύԪ��ʧ��
	eUI_ShopCenterBuyno_stock_item        = 9365,
	eUI_ShopCenterBuySucess                = 9366,
	eText_TwoHandEqiupError_0            =    9367,
	eText_TwoHandEqiupError_2            =    9368,
	eClient_Error_Me_InFightCanNotBargain     = 9369, // ս��״̬���ܽ���
	eClient_Error_Target_InFightCanNotBargain = 9370, // �Է���ս��״̬���ܽ���
	eClient_AddInfo_2slk_87        = 9371,        //Ŀ�����̫Զ�����ܽ��ף�  
	eSystemInfo_ResetTime_CantBuy        = 9372,    //������Ʒ���ܹ���
	eSystemInfo_ResetTime_CantCompound    = 9373,//������Ʒ�������ںϳ�
	eSystemInfo_ResetTime_CantInlay        = 9374, //������Ʒ����ǿ��
	eClient_AddInfo_2slk_117         = 9375,        //������Ʒ���ֽܷ�
	eTellClient_NotSilver            = 9376,      //û���㹻����Ʊ!
	eClient_AddInfo_2slk_75        = 9377,        //"�Է���Ǯ���ᳬ�� %d ����"
	eClient_AddInfo_2slk_76        = 9378,        //�Լ���Ǯ���ᳬ�� %d ����
	eTextGuild_Error_TargetIsSelf = 9379,           //���ܶ��Լ�ִ���������
	ePack_NotGrid                   = 9380,                //û�пռ�!
	eTellClient_RefuseEmbrace       = 9381, // %s �ܾ�����ӵ����
	eTellClient_AgreeStopAdverse    = 9382, //%s ���������������Ժͣ�		
	eTellClient_RefuseStopAdverse   = 9383, //%s ����ܾ���������Ժ����룡

	eTellClient_NotEnoughReputation = 9384, // ����ʧ�� û���㹻������� ��ǰ����:%d
	eTellClient_NotEnoughExploit    = 9385, // ����ʧ�� û���㹻������� ��ǰ����:%d
	eTellAllClient_EquipLevelUpToMax = 9386,// "��ϲ��� %s ������иŬ���ɹ���װ��[%s]��������"
	eTellClient_LessMapMinLevel      = 9387, // ��ĵȼ�С��%d�����޷�����õ�ͼ
	eTellClient_NotEnoughItem        = 9388, // ����ʧ�� û���㹻���%s ��ǰ����:%d
	eTellClient_FlyOnlyTeamHeader    = 9389,  // �ӳ�δ���븱�����޷�����
	eTellClient_TeamMemberMustArlound = 9390,   // ֻ�����ж�Ա�ڸ������ܽ���
	eTellClient_TeamMemberMustGreaterMapLevel = 9391,   // ���ж�Ա����Ҫ%d�����ܽ���˸���
	eTellClient_ActiveMountCanNotTrade       = 9292,    // ��ս�����ܽ���
	eLog_info_2slk_170                      = 9393,  // �ƶ���Ʒ GUID:%s ID:%d ����:%d ����ı����ƶ��������̵�	
	eTellClient_TeamMemberMustHaveQuest = 9394,       // %sû�нӴ�����,���ܽ���˸���
	eChatFormat                         = 9395,
	eTellClient_PunishLeaveTime         = 9396,       // �����ͷ�ʱ�仹ʣ%d��
	eTellClient_AlreadyEnterOnce		= 9397,      // �Ѿ������һ�� 
	eTellClient_RollCount               = 9398,      //%s������%d
	eClient_AddInfo_2slk_120            = 9399,      // ����������,���Ժ��ٽ�
	eClient_TellPlayerInMyBlacklist     = 9400,      // %s�����������,�޷����д˲���
	eClient_FlyMapGreaterThanMax        = 9401,      // ����ʧ��,%s�Ѿ�����õ�ͼ����%d��!
	eClient_WaitLeaveStage              = 9402,      // %d���,�㽫�����ͳ��˵�ͼ!

	eLog_JingPiao_1                  = 9403,  // ��Ʊ���� ��ʼ����: %u
	eLog_JingPiao_2                  = 9404,  // ��Ʊ���� ��������: %u, ��ǰ����: %u
	eLog_JingPiao_3                  = 9405,  // ��Ʊ���� ��������: %u, ��ǰ����: %u
	eLog_JingPiao_4                  = 9406,  // ��Ʊ���� ��������: %u, ��ǰ����: %u
	eLog_PickItemPack                = 9407,  // �����Ʒ : [%s] ID : [%d] GUID : [%I64u] ���� : [%d]
	eLog_Info_ExpPercent             = 9408,  //"����ϵ�� ����ϵ�� : [%0.2f] ������ : [%0.2f] ȫ��ϵ��:[%0.2f] ״̬ϵ��:[%0.2f] ����ϵ��:[%0.2f]"
	eLog_JinDing_FromDb              = 9409,  // �𶧶һ�
	eLog_DropPackage                 = 9410,  // ��[%d]��ʽ��������� ��ͼ : [%u], ����( %0.2f, %0.2f )
	eLog_PickPackage                 = 9411,  // ����ʰȡ��[%d]��ʽ����İ���
	eTellClient_NotEnoughGuildOffer  = 9412,  // ����ʧ�� û���㹻��İﹱ ��ǰ�ﹱ:%d
	eText_OpenTreasureBox            = 9414,  // ��� %s �� %s ��� %s ��Ʒ %d ��
	eTellClient_ReleaseGameStage     = 9415,  // [%s]��ͼ����[%d]���Ӻ�ر�, �ڴ˵�ͼ��������뿪�õ�ͼ������������׼��
	eTell_NotEnoughGuildMoney        = 9416,  // ����ʧ�� û���㹻��İ���ʽ� ��ǰ����ʽ�:%d  
	eTell_NotEnoughGuildBuild        = 9417,  // ����ʧ�� û���㹻��İ�Ὠ��� ��ǰ��Ὠ���:%d
	eTell_NotEnoughMoBeiReputation   = 9418,  // ����ʧ�� û���㹻���Į���������� ��ǰĮ����������:%d
	eTell_NotEnoughLiaoDongReputation = 9419, // ����ʧ�� û���㹻����ɶ��������� ��ǰ�ɶ���������:%d
	eTell_NotEnoughDunHuangReputation = 9420, // ����ʧ�� û���㹻��Ķػ͵������� ��ǰ�ػ͵�������:%d
	eTell_NotEnoughGaoGouLiReputation = 9421, // ����ʧ�� û���㹻��ĸ߾����������� ��ǰ�߾�����������:%d
	eTell_OnlyGuildMaster            = 9422,  // ֻ�а������й������Ʒ��Ȩ��
	eTell_NotEnoughMasterValue       = 9423,  // ����ʧ�� û���㹻���ʦ������, ��ǰʦ������ֵ:%d
	eTellClient_Marriage             = 9424,   // %s��%sϲ����Ե
	eTellClient_LuckReward           = 9425,   // �������׿����ս����~%s_���ڵĶ�������ͨ�����¹ⱦ�С���%d�صĿ��飬��ϲ���ǻ�÷������
	eTellClient_EquipLevelUpTo10     = 9426,   // %sƾ���ŷ�һ����������ɹ��ؽ�װ��[%s]����%s�ǡ������Ե���ҫ�£�ȫ��������Ҷ�����˸߶�ľ��齱��
	eTellClient_NotEnoughHonour      = 9427,   // ����ʧ�� û���㹻������� ��ǰ����:%d
	eTellAllClient_GetItemToMaxLev   = 9428,   //"��ϲ��� %s ������иŬ���ɹ������ɫƷ��[%s]"
	eTellAllClient_GetMaxLevItemByJD   = 9429,   //"���%s��Ʒ������������һ��[%s]"

	// ��������˳���Ϸ���米����װ������Ʒ��Ϣ��ͷ
	eLog_EnterWorld_Normal_Bag_Begin            = 9431,  // [:T9431]\t=========���������Ϸ������ͨ������ϢBegin=========
	eLog_EnterWorld_Normal_Bag_End              = 9432,  // [:T9432]\t=========���������Ϸ������ͨ������ϢEnd===========
	eLog_EnterWorld_Material_Bag_Begin          = 9433,  // [:T9433]\t=========���������Ϸ������ϱ�����ϢBegin=========
	eLog_EnterWorld_Material_Bag_End            = 9434,  // [:T9434]\t=========���������Ϸ������ϱ�����ϢEnd===========
	eLog_EnterWorld_DB_Begin                    = 9435,  // [:T9435]\t=========����DB��Ϣ�б�����Ʒ��ϢBegin=========
	eLog_EnterWorld_DB_End                      = 9436,  // [:T9436]\t=========����DB��Ϣ�б�����Ʒ��ϢEnd===========
	eLog_ExitWorld_Normal_Bag_Begin             = 9437,  // [:T9437]\t=========�����˳���Ϸ������ͨ������ϢBegin===========
	eLog_ExitWorld_Normal_Bag_End               = 9438,  // [:T9438]\t=========�����˳���Ϸ������ͨ������ϢEnd=============
	eLog_ExitWorld_Material_Bag_Begin           = 9439,  // [:T9439]\t=========�����˳���Ϸ������ϱ�����ϢBegin===========
	eLog_ExitWorld_Material_Bag_End             = 9440,  // [:T9440]\t=========�����˳���Ϸ������ϱ�����ϢEnd=============
	eLog_EnterWorld_EquipInfo_Begin             = 9441,  // [:T9441]\t=========������Ϸװ������ϢBegin===============
	eLog_EnterWorld_EquipInfo_End               = 9442,  // [:T9442]\t=========������Ϸװ������ϢEnd=================
	eLog_ExitWorld_EquipInfo_Begin              = 9443,  // [:T9443]\t=========�˳���Ϸװ������ϢBegin=============
	eLog_ExitWorld_EquipInfo_End                = 9444,  // [:T9444]\t=========�˳���Ϸװ������ϢEnd===============

	eLog_Exploit_1                   = 9445,  // [%s:%d]��ѫ���� ��ʼ����: %u
	eLog_Exploit_2                   = 9446,  // [%s:%d]��ѫ���� ��������: %u, ��ǰ����: %u
	eLog_Exploit_3                   = 9447,  // [%s:%d]��ѫ���� ��������: %u, ��ǰ����: %u
	eLog_Exploit_4                   = 9448,  // [%s:%d]��ѫ���� ��������: %u, ��ǰ����: %u
	eLog_Reputation_1                = 9449,  // [%s:%d]�������� ��ʼ����: %u
	eLog_Reputation_2                = 9450,  // [%s:%d]�������� ��������: %u, ��ǰ����: %u
	eLog_Reputation_3                = 9451,  // [%s:%d]�������� ��������: %u, ��ǰ����: %u
	eLog_Reputation_4                = 9452,  // [%s:%d]�������� ��������: %u, ��ǰ����: %u
	eLog_Honour_1                    = 9453,  // [%s:%d]�������� ��ʼ����: %u
	eLog_Honour_2                    = 9454,  // [%s:%d]�������� ��������: %u, ��ǰ����: %u
	eLog_Honour_3                    = 9455,  // [%s:%d]�������� ��������: %u, ��ǰ����: %u
	eLog_Honour_4                    = 9456,  // [%s:%d]�������� ��������: %u, ��ǰ����: %u
	eLog_CountryScore_1              = 9457,  // [%s:%d]��ս���ֲ��� ��ʼ����: %u
	eLog_CountryScore_2              = 9458,  // [%s:%d]��ս���ֲ��� ��������: %u, ��ǰ����: %u
	eLog_CountryScore_3              = 9459,  // [%s:%d]��ս���ֲ��� ��������: %u, ��ǰ����: %u
	eLog_CountryScore_4              = 9460,  // [%s:%d]��ս���ֲ��� ��������: %u, ��ǰ����: %u
	eLog_Exp_1                       = 9461,  // [%s:%d]������� ��������: %I64u
	eLog_Exp_2                       = 9462,  // [%s:%d]������� ��������: %I64u
	eLog_Exp_3                       = 9463,  // [%s:%d]������� ��������: %I64u
	eLog_JiaoZi_1                    = 9464,  // [%s:%d]���Ӳ��� ��ʼ����: %u
	eLog_JiaoZi_2                    = 9465,  // [%s:%d]���Ӳ��� ��������: %u, ��ǰ����: %u
	eLog_JiaoZi_3                    = 9466,  // [%s:%d]���Ӳ��� ��������: %u, ��ǰ����: %u
	eLog_JiaoZi_4                    = 9467,  // [%s:%d]���Ӳ��� ��������: %u, ��ǰ����: %u
	eLog_Money_1                     = 9468,  // [%s:%d]��Ǯ���� ��ʼ����: %u
	eLog_Money_2                     = 9469,  // [%s:%d]��Ǯ���� ��������: %u, ��ǰ����: %u
	eLog_Money_3                     = 9470,  // [%s:%d]��Ǯ���� ��������: %u, ��ǰ����: %u
	eLog_Money_4                     = 9471,  // [%s:%d]��Ǯ���� ��������: %u, ��ǰ����: %u

	eLog_DoneQuest_RewardExp         = 9700,  // ���%d���񣬻�� %d ����
	eLog_FirstEnterWord              = 9701,  // ������Ϸ���� [IP:%s][MAC:%s]
	eLog_DoneQuest_RewardMoney       = 9702,  // ���%d���񣬻�� %d ��Ǯ
	eLog_CreateGuildLog              = 9703,  // ������ %s ����
	eLog_LeaveGuildLog               = 9704,  // �뿪�� %s ����,��ǰ���������� %d ��
	eLog_GuildBanLog                 = 9705,  // �߳�%s��ҳ�%s����,��ǰ���������� %d ��
	eLog_TransferGuildMaster         = 9706,  // ת�û᳤�� %s ���
	eLog_TransferGuildViceMaster     = 9707,  // ת�ø��᳤�� %s ���
	eLog_TransferGuildTongMaster     = 9708,  // ת�������� %s ���
	eLog_AwardViceMaster             = 9709,  // ������� %s Ϊ %s ����ĸ��᳤
	eLog_RemoveViceMaster            = 9710,  // ������� %s �� %s ����ĸ��᳤ְλ
	eLog_AwardTongMaster             = 9711,  // ������� %s Ϊ %s ����� %d ����ְλ
	eLog_RemoveTongMaster            = 9712,  // ������� %s Ϊ %s ����� %d ����ְλ
	eLog_ExitTong                    = 9713,  // �˳��� %s ����� %d ��
	eLog_InviteEnterGuild            = 9714,  // �� %d ������� [%d] [%s] ����
	eLog_DisMissGuild                = 9715,  // ��ɢ %s ����
	eLog_GuildUpLevel                = 9716,  // [%d] [%s] ����� %d ������ %d
	eLog_AddGuildOffer               = 9717,  // ������ %s ���� %d �İﹱ
	eLog_SubGuildOffer               = 9718,  // ������ %s ���� %d �İﹱ
	eLog_AddGuildMoney               = 9719,  // ������ %s ���� %d ���ʽ�
	eLog_SubGuildMoney               = 9720,  // ������ %s ���� %d ���ʽ�
	eLog_LeagueGuild                 = 9721,  // %s ����� %s ��������
	eLog_AdverseGuild                = 9722,  // %s ����� %s ����ж�
	eLog_Disadverse                  = 9723,  // %s ����� %s ��������
	eLog_AddTong                     = 9724,  // ���� %s ��Ҽ��� %s ���� %d ��
	eLog_RemoveTong                  = 9725,  // %s ��ұ��Ƴ� %s ���� %d ��
	eLog_DoneQuest_RewardItem        = 9726,  // ���%d���񣬻�� %s ����
	eLog_DoneQuest_RewardTitle       = 9727,  // ���%d���񣬻�� %s �ƺ�
	eLog_DoneQuest_RewardReputation  = 9728,  // ���%d���񣬻�� %d ����
	eLog_DoneQuest_RewardExploit     = 9729,  // ���%d���񣬻�� %d ��ѫ
	eLog_DoneQuest_RewardGuildContribute = 9730, // ���%d���񣬻�� %d �ﹱ
	eLog_DoneQuest_RewardAddtionExp  = 9731,  // ���%d���񣬻�� %d ���⾭��
	eLog_Buffer_AddExp               = 9732,  // ͨ�� %s Buff����� %d ����
	eLog_MoneyItemChange             = 9733,  // :T0005 �һ� %I64u %s %d %s %s %s %s
	eLog_MoneyItemChangeReq          = 9734,  // :T0006 ��ƽ̨�ύ�һ� %I64u %s %d %s %s %s %s
	eLog_CancelStatus                = 9735,  // ȡ��״̬ %s
	eLog_OpenTreasureBox             = 9736,  //����[%s]���䣬[ID:%u,GUID:%I64u]����ñ����еı���[%s][%d]��
	eLog_TeamLuckReward              = 9737,   //%s�Ķ������¹ⱦ�и�����[%d]��%s
	eLog_CharLuckReward              = 9738,   //%s���¹ⱦ�и�����[%d]��%s
	eLog_UseItemToFriend             = 9739,   // �Ժ���[%s]ʹ����Ʒ[%s][%d]��, ��Ӻ��Ѷ�[%u]
	eLog_KickByCheckCheat            = 9740,   // �����뷵�ؽ��[%0x], �ж�ʹ�����, ��T����   
	eLog_Lost_JiaoZi                 = 9741,    //ʧȥ���� ʧȥ����%d ��ǰ����%d		
	eLog_Get_JiaoZi                  = 9742,    //�õ����� �õ�����%d ��ǰ����%d
	eLog_DoneQuest_RewardJiaoZi      = 9743,    // ���%d���񣬻�� %d ����
	eLog_DoneQuest_RewardHonor       = 9744,    // ���%d���񣬻�� %d ����
	eText_CountryReward				 = 9745,	// �����������ı�

	eText_ReqRmbPoint				 = 10000, // ��������rmb����
	eText_ExchangeNeedPoint			 = 10001, // �˴ζһ���Ҫ������%d
	eText_RemainRmbPoint			 = 10002, // ��Ŀǰ���ʻ��ϻ�ӵ��%d��
	eText_ExchangeRmbPoint			 = 10003, // ���ڴ�����...
	eText_NotEnoughJinDing			 = 10004, // û���㹻�Ľ�
	eText_NotEnoughJinPiao			 = 10005, // û���㹻�Ľ�Ʊ
	eText_NotItemShopCenter			 = 10006, // ����Ʒ������
	eText_ExchangeJinDingLevelLow    = 10007, // �ȼ�%d���ϲ��ܶһ���
	eText_GetJinDing				 = 10008, // ��õ���%d��
	eText_LoseJinDing				 = 10009, // ��ʧȥ��%d��
	eText_GetJinPiao				 = 10010, // ��õ���%d��Ʊ
	eText_LoseJinPiao				 = 10011, // ��ʧȥ��%d��Ʊ
	eText_ChangePoint                = 10012, //"�һ���:1��=%d��"
	eText_OwnGold                    = 10013, //"Ŀǰ��Ϸ�л�ӵ�� %d ��"
	eText_UnderLevel15               = 10014, // 15��һ�²�����ʹ���̳�
	eText_LoseShopConsumeScore		 = 10015, // ��ʧȥ��%d����
	eText_NotEnoughShopConsumeScore	 = 10016, // û���㹻���̳ǻ���
	eText_AddShopConsumeScore		 = 10017, // ��õ���%d����

	eText_TradeOriginPrice           = 10019,//ԭ��:%d
	eText_TradeFinalPrice            = 10020,//�Ż�:%d
	eText_TradePrice                 = 10021,//""

	eText_UpdateShopCenter 		    = 10022, // �̳Ǹ�����ʾ
	eText_ShopCenterFindPath        = 10023, //����ɹ�����%s���һ����ߣ��Ƿ�����Ѱ·ǰ��
	eText_ShopCenterTypeAll         = 10024, //ȫ��
	eText_RegisterNoFriend          = 10025, //ָ������ұ�������ĺ���
	eText_RegisterError             = 10026, //ϵͳ����
	eText_RegisterErrorOp           = 10027, //����Ĳ���
	eText_RegisterNoBuyMySelf       = 10028, //���������Լ��ĵ���
	eText_RegisterNoCancelOther     = 10029, //���ܳ���������ҵĵ���
	eText_RegisterWaiting           = 10030, //�ȴ�������

	eText_AuctionItemState_Status_Init	= 10031, // ��ʼ״̬
	eText_AuctionItemState_Running	= 10032, // ί����
	eText_AuctionItemState_Terminate= 10033, // ����ֹ
	eText_AuctionItemState_TimeOut	= 10034, // �ѵ���

	eText_SystemAuction_Status_Running	   = 10035,    //�ҵ���
	eText_SystemAuctionError_Status_BuySuccess   = 10036,    //����ɹ�
	eText_SystemAuctionError_Status_SellSuccess   = 10037,    //���۳ɹ�
	eText_SystemAuctionError_Status_Buyed	   = 10038,    //�Ѿ�����
	eText_SystemAuctionError_Status_Selled  = 10039,    //���۳�
	eText_SystemAuctionError_SystemBusy   = 10040,    //ϵͳ��æ�����Ժ���
	eText_SystemAuctionError_TooMoney = 10041,    //��Ǯ��������
	eText_SystemAuctionError_NoItem = 10042,    //����ʧ�ܣ���ˢ���б�����²鿴
	eText_SystemAuctionError_BuyType   = 10043,    //����������
	eText_SystemAuctionError_NoAccount   = 10044,    //�˻��ʽ��㣬����ʧ��
	eText_SystemAuctionError_CannotBuySelfItem   = 10045,    //�޷������Լ��ĵ��ݣ���ˢ���б��ѡ���������ݽ��й���
	eText_GoldTrade_BuyConfirm      = 10046,    //����%s�ļ۸���%d�𶧣��Ƿ�ȷ����
	eText_GoldTrade_SellConfirm     = 10047,    //����%s�ļ۸����%d�𶧣��Ƿ�ȷ����
	eText_GoldTrade_TooLess         = 10048,    //����ί�����ٽ��׶��Ϊ15��
	eText_TellWorldMoneyAuction		= 10049,//�𶧼���֪ͨȫ��

	eText_UnderLevel15RankList		= 10050, // 15�����²���ʹ�����а�
	eText_LoginNeedPwdProtect		= 10051, // �����ʺ��Ѱ��ܱ�������ʹ���ܱ�����½
	eText_LoginNoPwdProtect			= 10052, // �����ʺ�δ���ܱ�������ȡ���ܱ�����½
	eText_PasswordProtectString		= 10053, // �������%c�У���%c�е�����:
	eText_LoginPwdProtectFailed		= 10054, // �ܱ����������
	eText_LoginPwdProtectTimeOut	= 10055, // ��֤��ʱ���������µ�½

	eText_GoldTrade_Cancel          = 10056,//�Ƿ���Ҫȡ���ü��۵���?
	eText_GoldTrade_Sell            = 10057,//����
	eText_GoldTrade_Buy             = 10058,//�չ�
	eText_GoldTrade_BuyConfirmleft  = 10059,//�Ƿ�Ҫ��%s�ļ۸��չ�%d�𶧣�
	eText_GoldTrade_SellConfirmleft = 10060,//�Ƿ�Ҫ��%s�ļ۸����%d�𶧣�


	eText_NoXinShouCard				= 10061, // δ��ѯ���������ֿ�ʹ�ü�¼
	eText_No17173Card				= 10062, // δ��ѯ������17173��Ȩ��ʹ�ü�¼
	eText_NoZhiZunCard				= 10063, // δ��ѯ���������𿨵ȼ�
	eText_NoZhiZunVipGift			= 10064, // δ��ѯ����������Vip��ʹ�ü�¼
	eText_NoHuiGuiGift				= 10065, // δ��ѯ����������һع��������ȡ��¼
	eText_NoChongZhiGift			= 10066, // δ��ѯ�����ĳ�ֵ�����������ȡ��¼
	eText_NoChongZhiBackJinDing		= 10067, // δ��ѯ�����Ķ������������ȡ��¼

	eText_GotXinShouCard			= 10068, // ����ȡ�����ֿ����޷��ٴ���ȡ
	eText_Got17173Card				= 10069, // ����ȡ��17173��Ȩ�����޷��ٴ���ȡ
	eText_ZhiZunCardLevel			= 10070, // �������𿨵ȼ�Ϊ%s��
	eText_GotZhiZunVipGift			= 10071, // ����ȡ������Vip�����޷��ٴ���ȡ
	eText_GotHuiGuiGift				= 10072, // ����ȡ������һع�������޷��ٴ���ȡ
	eText_GotChongZhiGift			= 10073, // ����ȡ����ֵ����������޷��ٴ���ȡ
	eText_GotChongZhiBackJinDing	= 10074, // ����ȡ��������������޷��ٴ���ȡ

	eText_GetCardGiftSuccess		= 10075, // ��ȡ�ɹ�
	eText_GetCardGiftFailed			= 10076, // ��ȡʧ��

	eText_GetZhiZunCard				= 10077, // ��������		��1����
	eText_GetZhiZunYinCard			= 10078, // ������������	��2����
	eText_GetZhiZunJinCard			= 10079, // ���������	��3����
	eText_GetZhiZunBaiJinCard		= 10080, // ��������׽�	��4����
	eText_GetZhiZunZuanShiCard		= 10081, // ����������ʯ��	��5����
	eText_GetZhiZunHuangGuanCard	= 10082, // ��������ʹڿ�	��6����

	eText_RegisterBuyString         = 10092, //�����ɵ����ߣ�ָ�����ҵģ����������࣬���ɶ����٣�ָ��������
	eText_RegisterSellString        = 10093, //�����ɸ����ͣ�ָ�����ҵģ����������࣬���ɶ����٣�ָ��������

	eText_ER_HaveNotXinShouCard = 10100,
	eText_ER_XinShouCardCreateFail1 = 10101,
	eText_ER_XinShouCardCreateFail2 = 10102,
	eText_ER_XinShouCardPushFail1 = 10103,
	eText_ER_NotNeiCeJinPiao = 10104,
	eText_ER_NotNeiCeJinDing = 10105,

	eText_ER_HaveNotXinShouItem		= 10106,          // û�����ֵ���
	eText_ER_XinShouItemCreateFail1 = 10107,
	eText_ER_XinShouItemCreateFail2 = 10108,
	eText_ER_XinShouItemPushFail1	= 10109,

	eText_OnlineAward				= 10150,	//��������%d��%d����õ�%d����������
	eText_OnlineAward2				= 10151,	//��ϲ������õĵ�%d��������%s����򿪱����鿴����
	eText_OnlineAwardAlreadyGet		= 10152,	//������ȡ���ý������޷�������ȡ
	eText_OnineAwardNoReward		= 10153,	//��ȡ������������¿ͻ���
	eText_OnlineAwardPretime		= 10154,	//������%s�Ժ������Ͻ���

	eText_ChangeNameNoItem          = 10170,    //δ�ҵ��������ߣ�����ʧ��
	eText_ChangeNameSuccess         = 10171,    //�����ɹ�

	eText_FriendLevel1				= 10181,	//Ƽˮ���
	eText_FriendLevel2				= 10182,	//�������
	eText_FriendLevel3				= 10183,	//��ͬ����
	eText_FriendLevel4				= 10184,	//Ī������
	eText_FriendLevel5				= 10185,	//��������

	eText_Vendetta					= 10189,	//Ѫ�����
	eText_TempFriend				= 10190,	//�ز���ʶ
	eText_BlackList1				= 10191,	//İ����


	eText_FightInfoHurt            = 10201,   //"%s��%sʹ��%s,���%d%s�˺�"
	eText_NearDistance             = 10202,   //����
	eText_FarDistance              = 10203,   //Զ��
	eText_Critical                 = 10204,   //����
	eText_BackHit                  = 10205,   //��Ϯ + %d
	eText_NormalAttack             = 10206,   //��ͨ����
	eText_MagicAttack              = 10207,   //%d��%s
	eText_Your                     = 10208,   //��
	eText_Relive                   = 10209,   //"%s��%sʹ���˸�����"
	eText_Miss                     = 10210,   //%s������%s�Ĺ���
	eText_NoHit                    = 10212,   //%s�Ĺ���δ����%s"
	eText_SkillBuf                 = 10213,   //��ʹ����%s,�����%s״̬"
	eText_UseSkillBuf              = 10214,   //%s��%sʹ��%s,%s�����%s״̬
	eText_RestoreHpBySelf          = 10215,   //��ʹ����%s,�ָ�����%d��
	eText_RestoreHp                = 10216,   //%s��%sʹ����%s,%s�ָ�����%d��
	eText_AddHp                    = 10217,   //%s��%d��%s״̬�ָ���%d������
	eText_ReduceHp                 = 10218,   //%s��%d��%s״̬������%d��
	eText_FightGetExp              = 10219,   //������%d����
	eText_UseSkill                 = 10220,   //%s��%sʹ����%s
	eText_MySelfSkill              = 10221,   //��ʹ����%s
	eText_AddSkillExp              = 10222,   //������%u�㼼�ܾ���
	eText_AddHpBySkill             = 10223,   //%s�ܵ���ѪЧ���ָ���%d������
	eText_ReduceHpBySkill          = 10224,   //%s�ܵ�����Ч��������%d������
	eText_LoseSkillExp			   = 10225,	  //��ʧȥ��%u�㼼�ܾ���
	eText_RestoreMpBySelf			= 10226,	  //��ʹ����%s,�ָ�ħ��%d��
	eText_RestoreMp					= 10227,	  //%s�ܵ�%d��%s״̬�ָ���%d��ħ��

	eText_ReduceMP                 = 10228,   //%s��%d��%s״̬������%d��

	eText_ItemLocked               = 10251,   //�Ѽ���
	eText_ItemUnLocked             = 10252,   //%s ����
	eText_ItemLockedContext        = 10253,   //��Ʒ�������޷����н��ס���̯���ݻ٣��Ƿ������
	eText_MountLockedContext       = 10254,   //����������޷����н��ס���̯���ݻ٣��Ƿ������
	eText_ItemUnLockedContext      = 10255,   //����������3�죬�����Զ��������Ƿ������

	eText_ItemLockSale             = 10256,   //��Ʒ�������޷�����
	eText_ItemLockExchange         = 10257,   //��Ʒ�������޷�����
	eText_ItemLockDestory          = 10258,   //��Ʒ�������޷�����
	eText_MountLockExchange        = 10259,   //�����������޷�����
	eText_MountLockedSetFree       = 10260,   //�����������޷�����


	eText_ItemHasLocked            = 10261,   //��Ʒ�Ѽ���
	eText_MountHasLocked           = 10262,   //�����Ѽ���
	eText_ItemHasNotLocked         = 10263,   //��Ʒδ����
	eText_MountHasNotLocked        = 10264,   //����δ����
	eText_ItemCannotLock           = 10265,   //��Ʒ�޷�����
	eText_IsLocked				   = 10267,	  //��Ʒ�Ѽ������޷����д˲���

	eText_ItemCannotUnlock         = 10268,   //��Ʒ�����ڽ���״̬���޷��ٴν���
	eText_MountCannotUnlock        = 10269,   //���������ڽ���״̬���޷��ٴν���

	eText_ItemLockShop             = 10270,   //��Ʒ�Ѽ������޷���̯
	eText_MountLockShop            = 10271,   //�����Ѽ������޷���̯
	eText_PetLockShop = 10272, //�����Ѽ������޷���̯
	eText_PetInBattle = 10273, //�����ѳ�ս���޷���̯

	eText_SecondPasswordSetSucceed = 10280,   //�����������óɹ�
	eText_SecondPasswordChangeSucceed  = 10281,//����������ĳɹ�
	eText_SecondPasswordWrong      = 10282,    //�����������
	eText_SecondPasswordDiffer     = 10283,    //�������벻һ��
	eText_SecondPasswordStyleError = 10284,	   //���������ʽ����
	eText_SecondPasswordSizeError  = 10285,    //�������볤�ȴ���
	eText_SecondPasswordRelieve    = 10286,    //����������
	//	eText_SecondPasswordRemainTime = 10287,    //��������ʣ��ʱ��
	eText_SecondPasswordUndo       = 10287,    //ǿ�ƽ����ѿ���
	eText_SecondPasswordcancel     = 10288,    //�ֿ���������ɹ���ǿ�ƽ���Զ�ȡ��
	eText_SecondPasswordUndoTime   = 10289,    //�ֿ����뽫��%s��ǿ�ƽ��
	eText_SecondPasswordIsUndo     = 10290,    //�ֿ�����������ǿ�ƽ���״̬
	eText_SecondPasswordUndoInfo   = 10291,    //�ֿ�����ǿ�ƽ����ʾ
	eText_AlreadyHaveSecendPsw     = 10292,    //�Ѿ��ж���������

	eText_MailItemNoSender         = 10401,    //����Ʒ�޷��ʼ�
	eText_MailTitleError           = 10402,    //������д������������д
	eText_MailSenderError          = 10403,    //��������д����
	eText_MailContentError         = 10404,    //������д������������д
	eText_MailMoneyNoEnough        = 10405,    //��Ǯ����
	eText_MailItemError            = 10406,    //��Ʒ����
	eText_MailHasItem              = 10407,    //����ȡ����Ʒ���ٽ���ת��
	eText_MailHasMoney             = 10408,    //����ȡ����Ǯ���ٽ���ת��
	eText_MailTranslate            = 10409,    //ת��:
	eText_MailResponce             = 10410,    //�ظ�:
	eText_MailSendNeedMoney        = 10411,    //����:
	eText_MailNewNotify            = 10412,    //%s���㷢�˷��ʼ�����ǰȥ�ɸ봫�鴦�鿴
	eText_MailItemNotify           = 10413,    //���ʼ����и���δȡ�����Ƿ�ɾ����
	eText_MailSendSuccess          = 10414,    //���ͳɹ�
	eText_MailSendFriend           = 10415,    //�����˻����˱���Ϊ����
	eText_MailTargetName           = 10416,    //Ŀ��������Ч
	eText_MailTarget               = 10417,    //Ŀ�겻����
	eText_MailTooMuchMoney         = 10418,    //�ʼĽ�Ǯ��������
	eText_MailAccessoryError       = 10419,    //������Ч�������´��ʼ��鿴            
	eText_MailProcsssing           = 10420,    //�ʼ����ڴ�����
	eText_MailTitleWrong           = 10421,    //Title���Ϸ�
	eText_MailContentWrong         = 10422,    //Content���Ϸ�
	eText_MailSize                 = 10423,    //�ʼ�������������
	eText_MailNoExist              = 10424,    //���ʼ�������
	eText_MailDelFailed            = 10425,    //���ʼ��޷�ɾ��
	eText_MailFindFailed           = 10426,    //�ʼ�Ŀ���ѯʧ��
	eText_MailHasGetItem           = 10427,    //�ʼ���Ʒ�Ѿ���ã������´��ʼ��鿴
	eText_MailReceivedError        = 10428,    //��������д����������ѡ��
	eText_MailReceivedTip          = 10429,    //������:
	eText_MailTitleTip             = 10430,    //����:
	eText_MailLifeTip              = 10431,    //ʣ��:
	eText_MailTargetQueryFail	   = 10432,	   //�ռ���Ŀǰ�޷�������ʼ�



	eText_TeacherLevel				= 10601, //ʦ�ŵȼ�:%d
	eText_LiLian					= 10602, //�ҵ�����:%u
	eText_WeiWang					= 10603, //�ҵ�����:%s
	eText_NoStudent					= 10604, //��δ��ͽ��������10�����ϵ������ͽ��
	eText_NoTeacher					= 10605, //��δ��ʦ�����԰�40�����ϵ����Ϊʦ��
	eText_StudentLevelLimit			= 10606, //ͽ�ܵȼ��������%d��
	eText_TeacherLevelLimit			= 10607, //ʦ���ȼ��������%d��
	eText_TeacherStudentLevelBeyond = 10608, //ʦͽ�ȼ��������%d������
	eText_TeacherStudentCannotBeCouple	= 10609, //����֮���޷�����ʦͽ��ϵ
	eText_CannotAddTeacher			= 10610, //�Ѿ���ʦ���޷��ٴΰ�ʦ
	eText_CanHaveOneTeacher			= 10611, //ֻ�ܰ�һ��ʦ��
	eText_BeyondStudentMax			= 10612, //ֻ����%d��ͽ��
	eText_CannotReceivePrentice		= 10613, //��δ��ʦ���޷�����ʦ��
	eText_InviteYouAsStudent		= 10614, //%s��Ҫ����Ϊͽ\n�Ƿ�Ը�⣿
	eText_InviteYouAsTeacher		= 10615, //%s��Ҫ����Ϊʦ\n�Ƿ�Ը�⣿
	eText_CannotKickTeacherTimeLimit	= 10616, //��ʦ����������޷����ʦͽ��ϵ
	eText_CannotKickStudentTimeLimit	= 10617, //��ͽ����������޷����ͽ��ʦͽ��ϵ
	eText_YouGetWeiWang				= 10618, //��������%d������ֵ
	eText_YouLoseWeiWang			= 10619, //��ʧȥ��%d������ֵ
	eText_WeiWangBeyondMaxCannotUpgrade	= 10620, //����ֵ�������ޣ��޷���������
	eText_YouGetLiLian				= 10621, //��������%d������ֵ
	eText_ReportToTeacherSucceed	= 10622, //�㱨�ɹ�
	eText_GetReportFromStudent		= 10623, //�������ͽ��%s�Ļ㱨�������%u������ֵ
	eText_DirectSucceed				= 10624, //ָ��ɹ�
	eText_GetDirectFromTeacher		= 10625, //�������ʦ����ָ�㣬�����%u�㾭��ֵ
	eText_AddTeacherStudentMaxDist	= 10626, //˫�������Զ
	eText_ConfirmKickStudent		= 10627, //�Ƿ�Ҫ��%s���ʦ�ţ�\n����ɹ�����Ҫ�۳�%d��
	eText_ConfirmLeaveTeacher		= 10628, //�Ƿ�Ҫ����ʦ�ţ�\n����ɹ�����Ҫ�۳�%d��
	eText_LeaveTeacherStudent		= 10630, //~%s_��������ʦͽ��ϵ
	eText_KickTeacherStudent		= 10631, //����~%s_�����ʦͽ��ϵ
	eText_TeacherNotOnline			= 10633, //ʦ��������
	eText_StudentNotOnline			= 10634, //ͽ�ܲ�����
	eText_BeyondDirectMax			= 10635, //ÿ��ֻ��ָ��һ��
	eText_CannotReport_NoLiLian		= 10636, //û������ֵ���ܽ��л㱨
	eText_InviteTeacherSucceed		= 10637, //���˵ı�%s���У��ɹ�����������
	eText_InviteStudentSucceed		= 10638, //�ɹ��Ľ�������ѵ�%s��Ϊ����
	eText_TeacherOnline				= 10639, //���ʦ�� ~%s_ ������
	eText_StudentOnline				= 10640, //���ͽ�� ~%s_ ������
	eText_TeacherOffline			= 10641, //���ʦ�� ~%s_ ������
	eText_StudentOffline			= 10642, //���ͽ�� ~%s_ ������
	eText_CannotBeTeacher			= 10643, //��û��ʦ�Ų�������ͽ��
	eText_OtherCannotBeTeacher		= 10644, //�Է���û��ʦ�Ų�������ͽ��
	eText_BeyondTeacherLevel		= 10645, //ʦ�ŵȼ���������
	eText_OtherBeyondStudentMax		= 10646, //�Է���ͽ�������Ѿ��ﵽ���ֵ
	eText_NotFinishTeacherTask		= 10647, //��δ��ɳ�ʦ����
	eText_OtherHasTeacher			= 10648, //�Է��Ѿ���ʦ����
	eText_NotEnoughWeiWang			= 10649, //�������ֵ����

	eText_CanUseWithWifeHusband		= 10650, //ֻ�з��޲���ʹ�ô˵���
	eText_CannotUseOtherOffline		= 10651, //�Է������ߣ�����ʹ��ʧ��

	eGameSettingList_Sell          = 51, // ��������
	eText_NotEnoughMoneyLeaveTeacher= 10652, //ɾ��ʦͽ��ϵ��Ҫ%d��Ǯ
	eText_AddTeacherStudentMaxDist1	= 10653, //��ʦ��ͽ������%d�׷�Χ��
	eText_BeyondStudentLevelMax		= 10654, //ͽ�ܵȼ����ܳ���%d��
	eText_TeacherMustInTeam			= 10655, //ʦ�������ڶ����в��ܳ�ʦ
	eText_MasterLevelChange			= 10656, //ʦ�ŵȼ����Ϊ:%d��
	eText_FinishGraduateTask		= 10657, //��ʦ�ɹ�
	eText_YouLoseLiLian				= 10658, //��ʧȥ��%u����ֵ
	eText_GraduateDistLimit			= 10659, //ʦ��������%d�׷�Χ�ڲ��ܳ�ʦ
	eText_InviteTeacher				= 10660, //������~%s_��ʦ
	eText_InviteStudent				= 10661, //������~%s_��ͽ
	eText_CanInviteStudent			= 10662, //��ϲ��ɹ�ӵ�����Լ���ʦ��
	eText_StudentGraduate			= 10663, //���ͽ��~%s_��ʦ�ɹ�
	eText_NeedCreateShiMen			= 10664, //��δ����ʦ�ţ���ȥ̫ԭ&lt;��ʦ��&gt;������ʦ��
	eText_DelFriendFailed_NotExist = 10665, //�����������ϵ
	eText_DelFriendFailed_CannotDelete	= 10666, //����ɾ�������ϵ
	eText_TeacherMustInArea			= 10667, //���ʦ��������10�׷�Χ֮��
	eText_StudentMustInArea			= 10668, //���ͽ�ܱ�����10�׷�Χ֮��
	eText_AddStudentNumLimit		= 10669, //һ��ֻ��������ͽ��
	eText_AddTeacherNumLimit		= 10670, //һ��ֻ�ܰ�ʦһ��
	eText_TargetAddStudentLimit		= 10671, //�Է�������ͽ������������
	eText_TargetAddTeacherLimit		= 10672, //�Է������Ѱݹ�ʦ
	eText_RefuseMarry				= 10673, //~%s_ �ܾ����������
	eText_RefuseAddTeacher			= 10674, //~%s_ �ܾ�����Ϊͽ
	eText_RefuseAddStudent			= 10675, //~%s_ �ܾ�����Ϊʦ
	eText_ReportDesc				= 10676, //�����ʦ�����������㱨ʱ����ȷ��ʦ���������
	eText_TeachDesc					= 10677, //�����ͽ�ܽ��о���ָ��ʱ����ȷ��ͽ���������
	eText_TeacherAndStudentLevelDiff	= 10678,//ʦͽ�ĵȼ����
	eText_MustBeSameCountry = 10679,//����ͬһ���Ҳ�����Ӵ˹�ϵ
	eText_IsAlreadyYourTeacher = 10680,//�Ѿ�����ʦ��
	eText_IsAlreadyYourStudent = 10681,//�Է��ѽ�����ͽ�ܣ����ܽ��д˲���

	eText_GivePresentFailed_ShouldBeFriend	= 10800, //�����Ǻ��ѣ�������������
	eText_GivePresentFailed_TooFar			= 10801, //�����Զ������ʧ��
	eText_GivePresentFailed_TimeLimit		= 10803, //ÿ��ֻ�ܸ�ÿ����������%d������
	eText_GivePresentFailed_CountLimit		= 10804, //�����Ѿ����͹�%d��������
	eText_GivePresentFailed_ItemCannotGive	= 10805, //����Ʒ�޷�����
	eText_GivePresent_ShowBull				= 10806, //%s�յ���%s���͵�%d��%s��%s��%s�øд���
	eText_ReceiveFriendlyQuestMustHaveTeam	= 10807, //������Ӳ��ܽ�ȡ������
	eText_ReceiveFriendlyQuestOnlyTwoMember	= 10808, //������ֻ����2���˲��ܽ�ȡ������
	eText_ReceiveFriendlyQuestMustFriend	= 10809, //�����еĳ�Ա�����Ǻ��Ѳ��ܽ�ȡ������
	eText_ReceiveFriendlyCountLimit			= 10810, //ͬһ������һ��ֻ�ܽ�һ�����ܶ�����
	eText_ApplyMessageSending  = 10811,
	eText_CountryChange        = 10812, //���Ѿ�������%s��

	eText_Biaoche_NeedMountOff	= 10813,		//�ڳ�ǰ����������
	eText_Biaoche_NoJump		= 10814,		//��Ծʱ�����ﵽ�ڳ���
	eText_Biaoche_OutOfRange	= 10815,		//���ڳ�̫Զ�ˣ��޷����ڳ�����!
	eText_Biaoche_NoMove		= 10816,		//�ƶ��в����ﵽ�ڳ���

	eText_ItemDecompose_Cant		= 10817,	//����Ʒ�޷��ֽ�
	eText_TaskNotDone				= 10818,	//�������δ���
	eText_ClickCreatePlayer			= 10819,	//���������ɫ
	eText_QiDian				    = 10820,	//Ѱ·�Ŀ�ͷ ͨ��%s �� %s
	eText_YiDongLuJing				= 10821,	//�ƶ�·��
	eText_LuJing1					= 10822,    //ͨ��%s������%s
	eText_FindNpc					= 10823,    //�ҵ�%s
	eText_More						= 10824,    //......(����·���ı�ʾ��ʽ)
	//add by liaojie
	eTip_sAddHPDamage				= 10825,	// �����˺�
	eTip_sAddHPRestore				= 10826,	// ��������
	eTip_sAddAOE					= 10827,	// ��������
	eTip_sAddSuckDamage				= 10828,	// �����˺�
	e_ChangeNpcName 				= 10829,	// �һ�NPC����
	eText_SkillNeedLevel			= 10830,	// {#%x=��Ҫ�ȼ�:#}
	eText_SkillNotGain				= 10831,	// δ����
	eText_SkillAlreadyGain			= 10832,	// ������
	eText_SkillLearn__LevelLess		= 10833,	// ����ȼ�������ѧϰ���ķ���Ҫ%d��

	/////////////�ȼ���ӡ��һЩ������///////////////////////////
	eText_WaitLimitInfo             = 10834,    //���ڻ�ȡ�ȼ���ӡ��Ϣ,���Ժ�...
	eText_NoActiveLimit             = 10835,    //�ȼ���ӡ:%d��(δ����) 
	eText_ActiveLimit               = 10836,    //�ȼ���ӡ:%d��(��%s����)\n���ʱ��:%s
	eText_DoneLimit                 = 10837,    //�ȼ���ӡ����
	eText_BaseAttrInEquip			= 10838,	//��������:
	eText_RandAttrInEquip			= 10839,	//�������:
	eText_GuildApplyCooldownTip		= 10840,	//����������ȴ��,��%d�������
	eText_StallFailed_InDueling     = 10841,    //����ʱ���ܰ�̯
	eText_ExchangeFailed_InDueling  = 10842,    //����ʱ���ܽ���
	eText_GetingCharacter           = 10843,    //���ڻ�ȡ��ɫ��Ϣ...
	eText_NoChoseProtectStar		= 10844,	//ûѡ����ʯ��ʾ
	eText_NoProtectStarMaterial		= 10845,	//����û�ж�Ӧװ����ǰ�ǵȵı���ʯ���޷��������Ǳ�������ȡ����ʹ�ñ������ϡ�ѡ�
	eText_StarMaterialNoEnough		= 10846,	//���ǲ��ϲ���֮ǰ��ѡ��������ʾ
	eText_StarLEvolveNoMomeny		= 10847,	//����Ǯ�Ҳ�����ʾ
	eText_Mood						= 10848,	// ����(����ǩ��)
	eText_Title						= 10849,	// �ƺ�
	eText_CantCallFuJianWhenMoing   = 10850,	// �ƶ�ʱ�����ٻ�����
	eText_ZhuJiangUpBound			= 10851,	//��ʾ����������Ʒ�벻����Ʒ�ϳɣ��ϳɳ��Ľ�Ϊ����Ʒ���Ƿ��������
	eText_ZhuJiangUp_Success		= 10852,	//���������ɹ�
	eText_ZhuJiangUp_Failed			= 10853,	//��������ʧ��
	eText_StarProtect_Text			= 10854,	//���Ǳ�����
	eText_MaterialStar_UnderSix		= 10855,	//6�����µ�װ�����ǣ��޷�ʹ�����Ǳ�������
	eText_MaterialStar_BeyondSix	= 10856,	//6�����ϵ����ǣ�����ʹ�ñ��ǲ��ϣ�����ʧ���˻ر�����
	eText_ZhuJiangMaterial_NoEnough = 10857,	//����ת��������ϲ��㣬ת������ʧ��
	eTextMoney_Gold						= 10858,    //%d��
	eTextMoney_Silver					= 10859,    //%d��
	eTextMoney_Copper					= 10860,    //%dͭ
	eTextMoney_StringSilver				= 10861,    //%s%d��
	eTextMoney_StringCopper				= 10862,    //%s%dͭ
	eText_TransferStar_WrongPart		= 10863,	//������ͬ�������Լ�װ��������ת���Ǽ�
	eText_TransferStar_WrongLevel		= 10864,	//ԭװ���ȼ�����С�ڵ���Ŀ��װ�����ҵȼ����ܳ�Խ10��
	eText_TransferStar_WrongStarLevel	= 10865,	//Ŀ��װ����ǿ���ȼ�����ԭװ���޷�����ת��
	eText_TransferStar_SourceStarLevel  = 10866,	//ԭװ���Ǽ��������0
	eText_TransferStarAck_FailDrop		= 10867,	//��%d�ǣ�Դװ��%d�ǣ�Ŀ��װ��%d��
	eText_TransferStarAck_Success		= 10868,	//ת�ǳɹ�
	eText_TransferStarAck_Fail			= 10869,	//ת��ʧ�ܣ��Ǽ�����
	eText_InputHaveForbiddenWord        = 10870,	//������������к���Υ����
	eText_SelfQuitGuildTip              = 10871,	//���뿪�˾���
	eText_MountStrengthen_UnderFour		= 10872,	//4����������޷�ʹ�ñ�������
	eText_MountStrengthen_BeyongFour	= 10873,	//4�������������ʹ�ñ������ܣ�ǿ��ʧ���˻ر����ȼ�
	eText_MountStrengthen_Success		= 10874,	//����ǿ���ɹ�
	eText_MountStrengthen_Fail			= 10875,	//����ǿ��ʧ��
	eText_MountStrengthen_MaxLevel		= 10876,	//��ǰ����������ߵȼ�����������ǿ��
	eText_MountStrengthen_ActivedMount  = 10877,	//��ս���ﲻ��ǿ��
	eText_BeDamagePerHPMax              = 10878,    //ÿ���ܵ��˺���ʧ�������ֵ��%%d
	eText_Gem_Failed					= 10879,	//��ʯ��Ƕʧ��
	eText_YabiaoState_UseSkill			= 10880,	//Ѻ��״̬�²���ʹ�ü���
	eText_YabiaoState_UseItem			= 10881,	//Ѻ��״̬�²���ʹ����Ʒ
	eText_Hole_OtherItem				= 10882,	//��װ����Ʒ���޷����
	eText_EnterGame_Error				= 10883,	//������Ϸʧ�ܣ������µ�¼
	eText_Bind_Money					= 10884,	//(����)
	eText_BianShen_Bound				= 10885,    //�����ͼ���󶨣��Ƿ������
	eText_AskPresent_LengthError		= 10886,	//�����볤�ȴ���
	eText_StarLevelUp_NoSelect			= 10887,	//����װ���Ѵ�6�ǣ����鹴ѡ"ʹ�ñ�������"��ʹ�ñ�������
	eText_TransferStar_MaterialDrop		= 10888,	//ת�Ǻ�ʧ�ܽ�1~3��
	eText_TransferStar_MaterialUnDrop	= 10889,	//ת�Ǻ�ʧ�ܲ�����
	eText_Gem_ErrorItem					= 10890,	//����Ʒ�޷���Ƕ��ʯ
	eText_GemRemove_ErrorItem			= 10891,	//����Ʒ�޷����б�ʯ�������
	eText_GemRemove_NoGem				= 10892,	//��װ��δ���б�ʯ��Ƕ���޷����б�ʯ�������
	eText_MountStrengthen_NoSelect		= 10893,	//���������Ѿ��ﵽ4�ǣ����鹴ѡ��ʹ�ñ������ϡ��������롰������������
	eText_MountStrengthen_NoProtect		= 10894,	//���ı������ϲ��㣬����ǿ����ʧ�ܺ󽵼��ޱ���
	eText_ZhuJianUp_Material			= 10895,	//%s������%d�ɹ���
	eText_HIGHSHOUT_VIP_NoCountry		= 10896,	//���º���ʱû������ʾ������
	eText_YouGet_MOUNT					= 10897,    //��ɹ�ע����%d������:%s
	eText_FRIEND_ONLINE					= 10898,    //����
	eText_FRIEND_OFFLINE				= 10899,    //����
	eText_FRIEND_BIRTHDAY				= 10900,    //%2d��%2d��
	eText_GemUp_MaxLevel				= 10901,	//��ǰ��ʯ������ߵȼ������ܽ��кϳ�
	eText_Title_ChangeSuccess			= 10902,	//�޸ĸ���ǩ���ɹ�
	eText_REGEDIT_PET                   = 10903,    // �ɹ�ע�ḱ��ͼ��:%s
	eText_REPEATEDLY_PET                = 10904,    // ����ͼ��:%s��ע��,�޷��ظ�ע��
	eText_QUESTEND		                = 10905,    // �ر�
	eText_NoActivity					= 10906,    // �޻���������Ѿ���ȡ����,��������ȷ��
	eText_SNError						= 10907,    // ���������кŴ���,�޴����кŶ�Ӧ���������
	eText_AccountError					= 10908,    // ���ʺ��Ѿ���ȡ�������͵����,�޷�����ȡ
	eText_CharacterError				= 10909,    // �ý�ɫ�Ѿ���ȡ�������͵����,�޷�����ȡ
	eText_Unkown						= 10910,    // δ֪����
	eText_PlatformCaption				= 10911,    // ����
	eText_Equip_Cannot_Sell				= 10912,	// �޷�����
	eText_ActivitySucc					= 10913,    // ��ȡ������ɹ�,��ע��鿴�ʼ�
	eText_PresentSucc					= 10914,    // ���кŶһ��ɹ�,��ע��鿴�ʼ�
	eText_SuitAffect					= 10915,	// ȫ��%d��+%d:
	eText_MountStrengthen_ErrorMount	= 10916,	// �������޷�ǿ��
	eText_EquipScore					= 10917,	// װ������:
	eText_BlockAccount					= 10918,	// �����ʺ��ѱ�����,����%d���Ӻ����,������������ϵ�ͷ���Ա!
	eTellClient_MountLevelUpTo10		= 10919,	// %sƾ���ŷ�һ����������ɹ��ؽ�����[%s]ǿ����%s����
	eText_MailState_Read				= 10920,	// �Ѷ�
	eText_MailState_UnRead				= 10921,	// δ��
	eText_CardIcon_Level				= 10922,	// ��
	eText_CardIcon_Get					= 10923,	// ���ռ�
	eText_CardIcon_UnGet				= 10924,	// δ�ռ�
	eText_CardIcon_GetNum				= 10925,	// ����:
	eText_CardIcon_Lack					= 10926,	// ȱ��:
	eText_CardIcon_HadGet				= 10927,	// ����ȡ
	eText_SevenDays_UnStart				= 10928,	// δ����
	eText_SevenDays_CanGain				= 10929,	// �ɽ�ȡ
	eText_SevenDays_UnderWay			= 10930,	// ������
	eText_SevenDays_DoneUnGet			= 10931,	// ��ɣ�δ�콱
	eText_SevenDays_DoneGet				= 10932,	// �����
	eText_SevenDays_GetTask_Sucess		= 10933,	// ��ȡ����ɹ�
	eText_SevenDays_GetTask_Fail		= 10934,	// ��ȡ����ʧ��
	eText_AddItem_Type1					= 10935,	// %s %sͨ��%s�����[%s]
	eText_AddItem_Type2					= 10936,	// %s %sͨ��NPC%s�����[%s]
	eText_AddItem_Type3					= 10937,	// %s %sͨ����ɱ����%s�����[%s]
	eText_SelectChannel_TimeOut			= 10938,	// ѡ��ʱ�䵽
	eText_Login_ErrorServer				= 10939,	// ����������ά���������ѡ�������
	eText_eChangeChannelRet_Error		= 10940,	// ѡ��ķ��ߴ���
	eText_eChangeChannelRet_Same		= 10941,	// �뵱ǰ������ͬ
	eText_eChangeChannelRet_Dead		= 10942,	// ����ʱ����ѡ��
	eText_eChangeChannelRet_Fight		= 10943,	// ս��״̬����ѡ��
	eText_Decompose_HasGem				= 10944,	// ��װ����Ƕ�˱�ʯ���Ƿ�ֽ⣿
	eText_Decompose_HasStarLevel		= 10945,	// ��װ��ǿ�������Ƿ�ֽ⣿
	eText_Ping_FPS						= 10946,	// ֡��:
	eText_Server_Unknow					= 10947,	// δ֪
	eText_Server_Ping					= 10948,	// %d����
	eText_Server_UnderOne				= 10949,	// < 1����
	eText_AddInfo_BagTypeErr			= 10950,	// ��ͬ���͵���Ʒ����һ��
	eText_CharAttr_LossExp				= 10951,	// ��ʧȥ%d�㾭��
	eText_Advancement_Fail				= 10952,	// ����ʧ��
	eText_Advancement_Succeed			= 10953,	// ���ٳɹ�
	eText_StarMaterialBound				= 10954,	// ���ϰ󶨣����Ǻ�װ���󶨣��Ƿ������
	eText_EquipOwner					= 10955,	// �����ߣ�
	eText_YaBiao_Flytomap				= 10956,	// Ѻ��״̬�²��ܴ���

	eText_GuildBattle_NoBoss			= 10957,	// δˢ��
	eText_TransferStar_Bound			= 10958,	// ת��֮��Դװ����Ŀ��װ�����󶨣��Ƿ������
	eText_Hunting_UnAccept				= 10959,	// δ����
	eText_Hunting_Accept				= 10960,	// �ѽ���
	eText_Hunting_CannotRefresh			= 10961,	// û��δ�������޷�ˢ��
	eText_Hunting_NoJinPiao				= 10962,	// û���㹻����
	eText_QueryDiscardMount				= 10963,	// ȷ��Ҫ���� %s ��
	eText_ReliveOrigin_NoItem			= 10964,	// �����������
	eText_Cannot_Soul_LevelError		= 10965,	// �õȼ�װ����������
	eText_PrivateShopOpen				= 10966,	// ��̯״̬�²��ܽ��д˲���

	////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////
	eText_JoinFightRemainTime		= 20006,	//���α���ʣ��%s��
	eText_JoinFightCountDown		= 20007,	//������̨������%s��ʼ

	eText_CampBattleOne             = 20100,  //���
	eText_CampBattleTwo             = 20101,  //�ƾ�
	eText_CampBattleGetSuccess      = 20102,  //%s���ʤ��
	eText_CampBattlePingJu          = 20103,  //˫��ƽ��
	eText_CampBattleRequestSuccess  = 20104,  //ս������ɹ�
	eText_CampBattleRequest         = 20105,  //ս������
	eText_CampBattleNoRequest       = 20106,  //��ǰ���ܱ���
	eText_CampBattleWrongRoom       = 20107,  //����ķ����
	eText_CampBattleOpen            = 20108,  //%sս���ѿ������Ƿ���룿
	eText_CampBattleResource        = 20109,  //��Դ��:%d ��Դ��:%d/%d
	eText_CampBattleResChange       = 20110,  //%s�ѱ�%s��Ӣ��%sռ��
	eText_CampBattleResOne          = 20111,  //��
	eText_CampBattleResTwo          = 20112,  //ũ��
	eText_CampBattleResThree        = 20113,  //������
	eText_CampBattleResFour         = 20114,  //��ľ��
	eText_CampBattleResFive         = 20115,  //���
	eText_CampBattleLeftTime        = 20116,  //ս���˳�����ʱ:%d%s
	eText_CampBattleSelectCamp      = 20117,  //��ѡ����Ӫ
	eText_CampBattleCurCamp         = 20118,  //��ǰ������Ӫ
	eText_CampBattleCurRoom         = 20119,  //��ǰѡ����Ӫ
	eText_CampBattleMesBox          = 20120,  //��ɽ֮ս�Ѿ�����\n�Ƿ����ս����

	eText_CampBattleKillAmount      = 20121,  //%s���ڴ�ɱ��ɱ
	eText_CampBattleKillControl     = 20122,  //%s�Ѿ������˱���
	eText_CampBattleKillNoPeople    = 20123,  //%s�Ѿ����˿ɵ�
	eText_CampBattleKillMonster     = 20124,  //%s��ĸ�����һ��
	eText_CampBattleGoldLike        = 20125,  //%s�Ѿ���Խ���ɱ¾
	eText_CampBattleBeKillAmount    = 20126,  //%s�ս���%s�Ĵ�ɱ��ɱ
	eText_CampBattleBeKillControl   = 20127,  //%s�ս���%s�����ױ���
	eText_CampBattleBeKillNoPeople  = 20128,  //%s�ս���%s�����ܵ���ɱ¾
	eText_CampBattleBeKillMonster   = 20129,  //%s�ս���%s���ְ��ɱ¾
	eText_CampBattleBeKillGoldLike  = 20130,  //%s�ս���%s��Խ���ɱ¾
	eText_MailNoSelect              = 20131,  //�޹�ѡ�ʼ���ɾ��ʧ��

	eText_PKBattleSign				= 20132,  //��ɽ֮ս��������
	eText_PKBattleFight				= 20133,  //��ɽ֮սս������
	eText_PKBattleLastFight			= 20134,  //��ɽ֮ս���һ�ֿ���
	eText_CampBattleEndRequest      = 20135,  //����ս���ѿ�������ȴ��¸�ʱ����������
	eText_CampBattleLastNoOver      = 20136,  //��һ�ֻ�û�н���
	eText_CampBattleKillMySelf      = 20137,  //%sɱ�����ҷ�����%s
	eText_CampBattleKillHerSelf     = 20138,  //%sɱ���˵з�����%s
	eText_PKBattleGotoHaveBuff      = 20139,  //��ǰ�����ܴ���
	eText_PKBattleNotSelfOccupy     = 20140,  //���Ǽ���ռ��
	eText_PKBattleErrorGotoPos      = 20141,  //����Ĵ��͵ص�
	eText_CampBattleRule            = 20142,  //��Ӫս����������
	eText_CampBattleRequestLeftTime = 20143,  //�����³���������ʣ��%s
	eText_CampBattleNoSend          = 20144,  //�˵��ܵ���δ�޸����޷����д���
	eText_CampBattleSendInfo        = 20145,  //�Ƿ�Ҫͨ���ܵ�ǰ��{#fffffa00=%s#}��
	eText_PKBattleNoMatch           = 20146,  //��Ӫս��û��ƥ����
	eText_PKBattleNoMatchRoundEnd   = 20148,  //��Ӫս�����һ�֣�û��ƥ����

	eText_TeamBattleResource		= 20300,  //ս������:%d  ��ȡ��Դ:%d/%d  ��������:%d
	eText_TeamBattleCostTime		= 20301,  //����ʱ��:%s
	eText_TeamBattleWin				= 20302,  //ʤ��
	eText_TeamBattleLost			= 20303,  //ʧ��
	eText_TeamBattleSignup			= 20304,  //ֻ�жӳ����ܱ���
	eText_TeamBattleName			= 20305,  //%s�Ķ���
	eText_TeamBattleRule			= 20306,  //С��ս������˵��
	eText_TeamBattleWaitWorning		= 20307,  //�������鲻��3�� ��ȴ���һ�α���
	eText_TeamBattleLevelWorning	= 20308,  //�ȼ��������޷�����ս��
	eText_TeamBattleNotify			= 20311,  //20311 - 20316�����������ʾ

	eText_XinFaLevel				= 20400, //\n�ķ��ȼ�:%d
	eText_XinFaLearnLevel			= 20401, //\nѧϰ�ȼ�:%d
	eText_XinFaCurrEffect			= 20402, //\n��ǰ�ķ�Ч��:
	eText_XinFaCurrLevel			= 20403, //��ǰ����:
	eText_XInFaNextLevel			= 20404, //��һ����:
	eText_XinFaNeedLevel			= 20405, //������ҵȼ�
	eText_XinFaCengShu				= 20406, //����
	eText_XinFaNeedCengShu			= 20407, //{#%x=�����ķ�����:%d#}
	eText_XinFaSkillLevel			= 20408, //{#%x=�ȼ�:#}%d

	eText_StringCommon1             = 30001, //Common::_tstring strComment = "\nNeedLeve �����ȼ�(1��70)\n\ Quality  ��Ƽ���  (1��5 )\r\n\        MapPosX,MapPosY     (�޷���NPC� Ѱ·�ص�����)\n\        Duration �����ʱ��(��λ:��)\n\        Count    ���������(1~99 or -1Ϊ���޴���)\n\        ComleteId  �������������(�ű��Զ���)
	eText_StringCommon2             = 30002, //Common::_tstring strComment = "Recipe ID Ϊ�䷽�ı��\Name      Ϊ�䷽����������\Type      �䷽������.\PrimaryMaterials ��Ҫ���䷽\Material Id ��Ҫ�䷽����ϵı��\Count      ��Ҫ�䷽��Ҫ�Ĳ�������\CastTime   �ϳɵ�����ʱ��\NeedEnergy ���ĵĻ���ֵ\NeedMoney  ���ĵĽ�Ǯ\Probility  �����ĸ���\ProficiencyLimit ������Ʒ��������������������
	eText_StringOpenFailed          = 30003, //��ʧ��!
	eText_StringMoveRecord          = 30004, //�ƶ�·����¼
	eText_StringName                = 30005, //����:%s  ���:%d  ����(x=%d, y=%d)
	eText_BillBoardFailed           = 30006, //���޸Ĺ���ʧ�ܵ��ִ�
	eText_ItemNewFailed             = 30007, //CItemDetail���������ڴ�
	eText_StringNoArried            = 30008, //��npc����ֹѰ·���
	eText_StringQuest               = 30009, //QuestInfo::CreateQuest�д���SQuest
	eText_StringPersonName          = 30010, //����
	eText_StringContext             = 30011, //����
	eText_StringUpdateFaild         = 30012, //����ʧ��
	eText_StringPlayerName          = 30013, //�������
	eText_StringPlayerLevel         = 30014, //��ҵȼ�
	eText_StringPalyerProfession    = 30015, //���ְҵ
	eText_StringNew                 = 30016, //��Ʒ
	eText_StringHot                 = 30017, //����
	eText_StringYuanZhong           = 30018, //Ԫ��
	eText_StringNoPlayer            = 30019, //û��������֡�%s����npc�����
	eText_StringSingleName          = 30020, //����һ��
	eText_StringSingle              = 30021, //����
	eText_StringQuedePos            = 30022, //��Ŀǰ�ŵĶ���λ����: %d\n��ǰ������������Ϊ: %d
	eText_StringFontSong            = 30023, //����

	eText_BargainFailedError1		= 30024, //��Ʒ����, ��������� 
	eText_BargainFailedError2		= 30025, //��Ʒ������, ���ܽ��� 
	eText_BargainFailedError3		= 30026, //���ݴ���( ���������ݽṹ�����д� ) 
	eText_BargainFailedError4		= 30027, //��ս�����ܽ��� 
	eText_BargainFailedError5		= 30028, //����Ʒ�Ѿ��ڽ��� 
	eText_BargainFailedError6		= 30029, //Я����Ǯ�������� 
	eText_BargainFailedError7		= 30030, //�Է���Ҫ���׵���Ʒ�����쳣������ʧ��                               
	eText_BargainFailedError8		= 30031, //�Է���Ҫ���׵���Ʒ������������ʧ��                                
	eText_BargainFailedError9		= 30032, //�Է���Ҫ���׵���Ʒ���ݴ��󣬽���ʧ��                        
	eText_BargainFailedError10		= 30033, //�Է����ﴦ�ڳ�ս״̬������ʧ��                                   
	eText_BargainFailedError11		= 30034, //�Է���Ʒ�Ѿ��ڽ��ף�����ʧ��                                   
	eText_BargainFailedError12		= 30035, //�Է�Я����Ǯ�������ƣ�����ʧ��                                   

	eText_QuestNoFight              = 30049, //ֻ����ս��״̬��ʹ��
	eText_QuestInFight              = 30050, //ս��״̬���޷�ʹ��

	eText_PrivateShopItemError		= 30051, //��̯��Ʒ�����쳣����������������·���

	eText_MarryMenTask              = 30100,//���뷽����Ϊ�з��ұ���ﵽ%d�����ܽ��н������
	eText_MarryMustMen              = 30101,//�Է�����ΪŮ��,�ҵȼ�������%d��
	eText_MarryTask                 = 30102,//��Ů˫������ͬ�ڶ����вſɽ��н������
	eText_MarryIsLeader             = 30103,//�з������Ƕ���Ķӳ�
	eText_MarryOnlyTwoPeople        = 30104,//������ֻ������Ů˫������
	eText_MarryInSameTeam           = 30105,//�Է������ڶ�����
	eText_MarryHasWift              = 30106,//���Ѿ���������
	eText_MarryMustIsFriend         = 30107,//˫�������к��ѹ�ϵ����������ϵ
	eText_MarryFriendNoEnough       = 30108, //˫�����ѶȲ���%d��
	eText_MarryInSameSceen          = 30109,//�Է������������
	eText_MarryHasHoushand          = 30110,//�Է��Ѿ����ɷ���
	eText_MarryRelation             = 30111,//�����Ƿ��޹�ϵ���ܿ������쳡��
	eText_MarrySceneMax             = 30112,//���쳡���Ѿ��ﵽ�����
	eText_MarrySceneCreateFailed    = 30113, //���쳡������ʧ��, ������
	eText_MarrySceneNoOpen          = 30114,//���쳡����δ����
	eText_MarryAskMarryInfo         = 30115,//�������
	eText_MarryAskMarry             = 30116,//{#fffffa00=%s#}�������
	eText_MarrySceneOpen            = 30117,//���쳡���ѿ���
	eText_MarrySexInSameTeam        = 30118,//ֻ�з���˫����ͬһ�����в����������
	eText_MarryHusband              = 30119,//�Ϲ�
	eText_MarryWife                 = 30120,//����
	eText_HusbandOnline				= 30121, //����Ϲ� ~%s_ ������
	eText_WifeOnline				= 30122, //������� ~%s_ ������
	eText_HusbandOffline			= 30123, //����Ϲ� ~%s_ ������
	eText_WifeOffline				= 30124, //������� ~%s_ ������
	eText_ReqDivorce				= 30125, //%s����Э����飬\n�Ƿ�ͬ�⣿
	eText_DivorceSucceed			= 30126, //Э�����ɹ�
	eText_DivorceFailed				= 30127, //Э�����ʧ��
	eText_MaleLevelLimit1			= 30128, //���뷽����Ϊ�з��ұ�������%d�����ܽ��
	eText_MaleLevelLimit2			= 30129, //���뷽����Ϊ�з��ұ�������%d�����ܿ������ĵ�

	eText_KillMonsterBroadcast      = 30300, //%s��%s�����%s֮������Ĵӵ��Ϸ�����%s

	eText_MailSystemTitle           = 30500, // ϵͳ��Ϣ
	eText_MailSystemName            = 30501, // ϵͳ
	eText_MailRemoveMarriage        = 30502, // %s�����������޹�ϵ�����Ƿ���Ե���Ѿ���������ãã�˺�������Ѱ����һ��ǰ�����ݺ��ߴ�չ���µ���Ե����
	eText_MailRemoveTeacher         = 30503, // %s��������ʦͽ��ϵ������ʦͽԵ���Ѿ���������ãã�˺�����������һ�����ӽ���ָ��
	eText_MailRemoveStudent         = 30504, // %s��������ʦͽ��ϵ������ʦͽԵ���Ѿ���������ãã�˺�������Ѱ��һ��ʦ���������
	eText_MailBeKickedFromFamily	= 30505, // ���Ѿ������峤�߳����壡
	eText_MailFamilyDisbanded		= 30506, // �����Ѿ�����ɢ�����Ѿ��뿪���壡

	eText_Stall_Pet_Used = 30600, //�����ѳ�ս���޷���̯
	eText_Stall_No_Item = 30601, //û�е��ߣ��޷���̯
	eText_Stall_Rent = 30602,	//̯λ��
	eText_Stall_Tax = 30603, //˰��
	eText_Stall_YesNo = 30604, //�Ƿ�ʼ�ڴ˰�̯
	eText_Stall_offLine_login = 30605, //���ʺ����������߰�̯״̬�����Ժ��ٵ�½
	eText_Stall_Not_Right_Item = 30606, //����Ʒδ�����������
	eText_Stall_Proxy_Succeed = 30607,	//��������ɹ�
	eText_Stall_Too_Near = 30608,	//����������޷���̯
	eText_Stall_Choose_Tip = 30609,	//��̯ѡ������ʾ
	eText_PetAliveTime        = 30610,//���︴��ʱ��
	eText_NotEnoughMoneyForOffline = 30611,//û���㹻��Ǯȥ���߰�̯
	eText_NotEnoughMoneyFonOnline  =30612,//û���㹻��Ǯȥ���߰�̯
	eText_NormalTextStall      =30613,//����Ϊ��ͨ��̯����
	eText_NoticeForStall	   =30614,//����Ԫ��������ֻ�ܹ����ƶ������̯

	eText_CarryTimeLimit      = 31000,//���������Χ,%d����뿪�ؾ�
	eText_CarryGetBack        = 31001,//���ص��˻��Χ��
	eText_CountryRewardbiaoti		  = 31002,//��ս�ʼ�����
	eText_CountryRewardneirong		  = 31003,//��ս�ʼ�����

	eText_360VirusInfoTip           = 60100, //����ɨ���ڴ棬���Ժ򡭡�
	eText_360VirusInfoScanFile      = 60101, //����ɨ��:%s
	eText_360VirusInfoFindVirus     = 60102, //����ľ����:%s
	eText_360VirusInfoVirusPath     = 60103, //�ļ�·��:%s


	//A��Ӫս�������
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

	//B��Ӫս�������
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

	// ���װ���ĳ�������
	eText_BestEquip1					= 92000, // ���ʺϵ�װ��
	eText_BestEquip2					= 92001, // ����%d �ȼ�%d
	eText_BestEquip3					= 92002, // %s��ȡ��ʽ

	// �����������
	eText_SameTeamLimit					= 93000, // ���������ͬһ������ſ��Դ��������
	eText_InviteGetOn					= 93001, // %s���������������
	eText_RequestGetOn					= 93002, // %s�������������
	eText_RejectInvite					= 93003, // %s�ܾ�������������룡
	eText_RejectRequest					= 93004, // %s�ܾ�������������룡
	eText_KickOffByHost					= 93005, // ���ѱ�������������
	eText_OnMultiMount					= 93006, // ���Ѿ��ڶ�����������
	eText_NoMultiMount					= 93007, // �㻹û�����϶��������������

	eText_PetNoData                     = 94000, //û���ҵ���������
	eText_PetPointError                 = 94001, //����Ǳ����������
	eText_PetEnough                     = 94002, //Я����������
	eText_PetLessTakeLevel              = 94003, //Я���ȼ�����
	eText_PetNoFight                    = 94004, //ս��״̬�����޷���ս
	eText_PetDead                       = 94005, //����״̬�����޷���ս
	eText_PetNoLife                     = 94006, //������������޷���ս
	eText_PetNoHappy                    = 94007, //���ֶȲ�������޷���ս
	eText_PetNoReLife                   = 94008, //����ʱ�仹δ��
	eText_PetReturnLife                 = 94009, //��ֳ���ĳ����޷���ͯ
	eText_PetNoReturnLife               = 94010, //��������޷���ͯ
	eText_PetFailLearnSkill             = 94011, //���＼��ѧϰʧ��
	eText_PetFailFanZhi                 = 94012, //��ֳʧ��
	eText_PetNoInTeam                   = 94013, //��û�д��ڶ�����
	eText_PetMoreTwo                    = 94014, //���Ķ��鳬����2��
	eText_PetNoLeader                   = 94015, //�����Ƕ���Ķӳ�
	eText_PetNoTeamer                   = 94016, //���Ѳ����Ա�
	eText_PetHaveFanZhi                 = 94017, //�Ѿ��г����ڷ�ֳ��
	eText_PetFailSelect                 = 94018, //����ѡ��ʧ��
	eText_PetTradeMySelf                = 94019, //�Լ���ʼ���ｻ��
	eText_PetTradeTarget                = 94020, //�Է���ʼ���ｻ��
	eText_PetLockMySelf                 = 94021, //�Լ���������
	eText_PetLockTarget                 = 94022, //�Է���������
	eText_PetConfirmMySelf              = 94023, //�Լ�ȷ�����ｻ��
	eText_PetConfirmTarget              = 94024, //�Է�ȷ�����ｻ��
	eText_PetScessFanZi                 = 94025, //��ֳ�ɹ�
	eText_PetFailFanZi                  = 94026, //��ֳʧ��
	eText_PetTimeOutFanZi               = 94027, //��ֳ��ʱ
	eText_PetCancel                     = 94028, //�Է�ȡ����ֳ
	eText_PetTargetExit                 = 94029, //�Է����ߣ���ֳȡ��	
	eText_PetConfirmFail                = 94030, //����ȷ��ʧ��
	eText_PetNoFanZi                    = 94031, //û�з�ֳ����
	eText_PetNoElapse                   = 94032, //ʱ����δ��
	eText_PetNoSpace                    = 94033, //�������Ѿ���
	eText_PetGet                        = 94043, //��ó���
	eText_PetLevel                      = 94044, //��������

	eText_PetLevelSkill               = 94045,//����ȼ�����ѧϰʧ��
	eText_PetSkillMoney            = 94046,//��Ǯ�����޷�ѧϰ
	eText_PetSavvyUpMoney    = 94047,//��Ǯ�����޷���������
	eText_PetSavvyBone             = 94048,//���ǲ����޷���������
	eText_PetSavvyUp                 = 94049,//������������ʧ��
	eText_PetIsActivePet			   = 94050,//��ս�����޷����в���
	//ȫ����ϵ
	eText_PhyleAll							= 94051,//ȫ����ϵ
	eText_PhyleHuman					= 94052, //����
	eText_PhyleMachine				= 94053, //����
	eText_PhyleBeast						= 94054, //����
	eText_PhyleImmortal				= 94055, //����
	eText_PhyleGhost					= 94056,//����
	eText_PhyleBogey					= 94057,//����
	eText_PhyleDeity						= 94058,//����
	eText_PhyleDemon					= 94059,//ħ��

	eText_MissionCountFirst			= 94060,	// ʹ����δ�ﵽҪ���ѱ�ϵͳ�����������������ɣ�
	eText_MissionCountSecond		= 94061,	// �����Ѿ�����Σ���ڣ���ע�⼰ʱ����
	eText_MissionCountThird			= 94062,	// ���ź�������������ƣ�����ϵͳ�ջأ����ɽ�ɢ��

	eText_PetStudySuccess                     = 94070, //����ѧϰ�ɹ�
	eText_PetSavvyUpSuccess					= 94071,//�������������ɹ�
	eText_SelectSamePet							= 94072,//ѡ������ͬ�ĳ���
	eText_CatchSkillLevel							= 94073,//���ﲶ׽���ܵȼ�����
	eText_PetIdentify									= 94074,//û�г���ͼ���޷���׽
	eText_PetCatchFail								= 94075,//��׽����ʧ��
	eText_PetCatchSuccess						= 94076, //��׽����ɹ�
	eText_PetIsActivedCannotSelect		 = 94077,//���ﴦ�ڳ�ս״̬���ܱ�ѡ��
	eText_PetSavvyFull								= 94078,//������������10�������߳�����ﲻ�ܱ���������
	eText_PetCannotMaterial					= 94079,//�ó��ﲻ���������ϳ���
	eText_PetSelectFirst							= 94080,//����ѡ����Ҫ�������Եĳ���
	eText_PetNoneItem							= 94081,//��δ��ӵ��߲���
	eText_PetCannotCatch						= 94082,//�ó��ﲻ�ܱ���׽
	//�����Ը�
	eText_PetPoltroon								= 94083,//��С
	eText_PetWariness								= 94084,//����
	eText_PetLoyal										= 94085,//�ҳ�
	eText_PetCanniness							= 94086,//����
	eText_PetBravery									= 94087,//����

	eText_PetChuZhan								= 94088,//�����ս������
	eText_PetLevelUp								= 94089,//���ĳ���[%s]�ȼ�����[%d]��
	eText_PetSavvyLevelUp						= 94090,//���ĳ���[%s]��Ϊ������ǰһ��,�����˼���[%s]
	eText_PetBreedMaxNum					= 94091,//���ﷱֳ��������
	eText_PetChuZhanLevelNotEnough= 94092,//�����ս�ȼ�����
	eText_PetNameGen							=94093,//%d��%s
	eText_PetLoyaltyLower						= 94094,//������ֶȲ����޷���ֳ
	eText_PetDruationLower					= 94095,//�������������޷���ֳ
	eText_PetBookLearnSkill					= 94096,//���ĳ���%sͨ��������ѧ���˼���%s
	eText_HasPetSkill								= 94097,//�����Ѿ�ѧϰ�˸ü���
	eText_PetSkillGroupLevel					= 94098,//�����Ѿ�ѧϰ�߼�����
	eText_PetReplaceSkill							= 94099,//���ĳ���%s ѧ����%s�滻��%s
	eText_MonsterCatchLevelNotEnough = 94100,//���ﲶ׽��Ҫ%d�ȼ�
	eText_PetActiveCannotFanZhi				 =94101,//��ս�����޷���ѡ��ֳ
	eText_PetCannotFanZhi							 =94102,//����ѡ����������߱��������з�ֳ!
	eText_PetTypeNotCatch						 = 94103,//���Ķ�����ѡ����[%s],������Ҫѡ��ͬ���͵ĳ���! 
	eText_PetSexNotCatch							 = 94104,//���Ķ�����ѡ����[%s]�ĳ���,������Ҫѡ��ͬ�Ա�ĳ���!
	eText_PetMale											 = 94105,//����
	eText_PetFemale										 = 94106,//����

	eText_PetNoEnoughMoney  				 = 94107,//��Ǯ�����޷���ȡ
	eText_PetNeedMoneySingel				 = 94108,//������ȡ��Ҫ��Ǯ
	eText_SelfCancelLockPet						 = 94109,//�Լ�ȡ����������
	eText_TargetCancelLockPet					 = 94110,//�Է�ȡ����������
	eText_TeamPlayerPeting						 = 94111,//�������ж�Ա���г����ڷ�ֳ��,�����ظ���ֳ!
	eText_PetSource_Other							 = 94112,//����
	eText_PetSource_Skill								 = 94113,//��׽
	eText_PetSource_BabyBreed				 = 94114,//��ֳ�õ�����
	eText_PetSource_Stall							 = 94115,//����
	eText_PetSource_Breed							 =94116, //��ֳ�õ������
	eText_PetDisappear								 =94117,//������ֳ����ʧ
	eText_PetLost											 =94118,//�������Ĺ�������
	eText_PetBreedTime								 =94119,//���ﷱֳʱ�䵽�˿�ȥ��ȡ
	eText_PetGenerationNotCatch				 =94120,//�������ϳ����޷���ѡ��
	eText_PetBoneNotEnough					 =94121,//�����ϵĳ���ĸ��Ǳ�����ڱ���ɳ���ĸ���
	eText_PetFangshengLost						 =94122,//����%s���������ʧ
	eText_PetSavvyUpLost							 =94123,//����%s���������Զ���ʧ
	eText_PetBreedLost								 =94124,//����%s��ֳ����ʧ
	eText_PetStallLost									 =94125,//����%s���׶���ʧ
	eText_PetTeamPlayerGet						 =94126,//����%s��ȡ�˳���
	eText_PetLearnAdvanceSkillOnBase	 =94127,//���ĳ�����%s�Ļ�����,ϰ����%s!
	eText_PetSavvyReduce							 =94128,//����һ��С�����Խ��͵���%d!
	eText_PetBreedSuccess							 = 94200,        //~%s_ ͨ�����ﷱֳ����µĳ��� [%s] 
	eText_HaveNonePetCard						 =94201, //Ŀǰ����û�иù���Ŀ�Ƭ
	eText_HaveNonePet							 =94202,//��Ŀǰ��û�г������ͨ����׽��ֳ�ȵõ�����
	eText_FamilyCreateSuccess			= 95001,		//��������ɹ�
	eText_FamilyErrorName				= 95002,		//���������Ƿ�
	eText_FamilyRepeatName				= 95003,		//�������Ѵ���
	eText_FamilyCreateSuccessTip		= 95004,		//���%s�ɹ���������%s
	eText_FamilyInviteTip				= 95005,		//���%s������������%s
	eText_FamilyInvite					= 95006,		//����������
	eText_FamilyInviteAckSuccess		= 95007,		//����ɹ�
	eText_FamilyInviteAckNoFamily		= 95008,		//��û�м���
	eText_FamilyInviteAckNoRight		= 95009,		//��û��Ȩ������
	eText_FamilyInviteAckOffline		= 95010,		//���������Ҳ����ڻ�����
	eText_FamilyInviteAckHaveFamily		= 95011,		//�Է��Ѿ����˼���
	eText_FamilyInviteAckLevelLimit		= 95012,		//�Է��ȼ���������������������
	eText_FamilyInviteAckFamilyFull		= 95013,		//��Ա���Ѿ�����
	eText_FamilyInviteAckRefuse			= 95014,		//�Է��ܾ��������
	eText_FamilyKickoutTip				= 95015,		//��ȷ��Ҫ�����%s�߳����壡
	eText_FamilyKickout					= 95016,		//�߳�����
	eText_FamilyQuitYesNo				= 95017,		//��ȷ��Ҫ�˳�����
	eText_FamilyQuit					= 95018,		//�˳�����
	eText_FamilyQuitTip					= 95019,		//���%s�뿪�˼���%s
	eText_FamilyJoinTip					= 95020,		//���%s�����˼���%s
	eText_FamilyModifyNoteSuccess		= 95021,		//�޸ļ��幫��ɹ���
	eText_FamilyModifyNoteFailed		= 95022,		//�޸ļ��幫��ʧ�ܣ�
	eText_FamilyContributeSuccess		= 95023,		//�����ʽ����%d��%d��%dͭ�ɹ���
	eText_FamilyContributeFailed		= 95024,		//�����ʽ𵽴����ޣ�����ʧ�ܣ�
	eText_FamilyContributeTip			= 95025,		//���%s�����˼����ʽ�%d��%d��%dͭ
	eText_FamilyUpgradeAckSuccess		= 95026,		//���������ɹ���
	eText_FamilyUpgradeAckFailed		= 95027,		//��������ʧ�ܣ�
	eText_FamilyHaveNoFamily			= 95028,		//�㻹û�м��壡
	eText_FamilyIncorrectName			= 95029,		//���������Ȳ��Ϸ���
	eText_FamilyNoteLenIncorrect		= 95030,		//������幫�泤�Ȳ��Ϸ���
	eText_FamilyAimLenIncorrect			= 95031,		//���������ּ���Ȳ��Ϸ���
	eText_FamilyRequestSuccess			= 95032,		//�ɹ�������%s����
	eText_FamilyLevelNotEnough			= 95033,		//�ȼ�����
	eText_FamilyRefuseJionIn24			= 95034,		//�˼����Ժ�24Сʱ�ڲ��ܼ������
	eText_FamilyNoSuchFamily			= 95035,		//����ļ��岻����
	eText_FamilyFull					= 95036,		//Ŀ������Ա���Ѿ�����
	eText_FamilyRefuseJion				= 95037,		//�ܾ�����
	eText_FamilyManagerOffline			= 95038,		//�������Ա��������
	eText_FamilyPlayer					= 95039,		//���
	eText_FamilyPlayerReach10			= 95040,		//������10������������������
	eText_FamilyRequestMsg				= 95041,		//�������������Ϣ���Ȳ��Ϸ���

	eText_FamilyCantChat				= 95042,		//�㻹û�м��壬�����ڼ���Ƶ������
	eText_FamilySureExpel				= 95043,		//��ȷ��Ҫת���峤��
	eText_FamilySureUpgrad				= 95044,		//��ȷ��Ҫ�������壡\n��һ������%d�� \n��Ҫ���ķ��ٶ�%d,��Ҫ���Ľ�Ǯ%s
	eText_FamilyLeader					= 95045,		//�峤
	eText_FamilySuccessedLeave			= 95046,		//���ѳɹ��˳�����%s
	eText_FamilyBeKickout				= 95047,		//���ѱ��峤%s�߳��˼���
	eText_FamilyRefuseInviteIn24		= 95048,		//�˼����Ժ�24Сʱ�ڲ��ܱ�����������

	eText_FamilyModifyAimSucc			= 95049,		//�޸ļ�����ּ�ɹ�
	eText_FamilyOnceInWeek				= 95050,		//�ܾ��޸ģ�һ����ֻ���޸�һ��
	eText_FamilyModifyAimFailed			= 95051,		//�޸ļ�����ּʧ��
	eText_FamilyMaxLevel				= 95052,		//��ļ�����������
	eText_FamilyLevelNotEnogh			= 95053,		//��ĵȼ����������ܼ������
	eText_FamilyAimForbiddenWords		= 95054,		//������ּ���зǷ��ַ�������������
	eText_FamilyNoteForbiddenWords		= 95055,		//���溬�зǷ��ַ�
	eText_FamilyJoinSucess				= 95056,		//���ѳɹ���������������
	eText_FamilyLevelReachTo			= 95057,		//��ļ�����������%d��
	eText_FamilyInputName				= 95058,		//������Ҫ�����ҵ�����
	eText_FamilyAlreadyHave				= 95059,		//���Ѿ�������壬�޷�������
	eText_FamilyTransferFailed			= 95060,		//ת���峤ʧ�ܣ���û�����Ȩ��
	eText_FamilyYouAreLeader			= 95061,		//���ѳ�Ϊ%s�����峤
	eText_FamilyTransFailedNoPlayer		= 95062,		//ת���峤ʧ�ܣ���Ҳ�����
	eText_FamilyYourLevelNotEnough		= 95063,		//�ȼ����㣬���ܴ�������
	eText_FamilyYourMoneyNoteEnough		= 94064,		//������Ǯ���㣬���ܴ�������

	eText_GuideASDWMovePlayer			= 96001,		//�밴ASDW���ƶ���ɫ
	eText_GuideClickMovePlayer			= 96002,		//�����������������
	eText_GuideRMouseRote				= 96003,		//�밴����Ҽ��϶���ת�ӽ�
	eText_GuideSpaceJump				= 96004,		//�밴�ո����Ծ
	eText_GuideFinishMovePlayer			= 96005,		//��������ƶ���ɫ����
	eText_GuideFinishLMouseOpt			= 96006,		//�����������������
	eText_GuideFinishRMouseOpt			= 96007,		//�����������Ҽ�����
	eText_GuideFinishSpaceOpt			= 96008,		//������ɰ��ո���Ծ����
	eText_GuideIsNewPlayer				= 96009,		//���Ƿ�����ң�ѡ��\"��\"�������̳̣�\"��\"ֱ�ӽ�����Ϸ
	eText_GuideMovePlayerUp				= 96010,		//�밴W����ǰ�ƶ���ɫ
	eText_GuideMovePlayerDown			= 96011,		//�밴S������ƶ���ɫ
	eText_GuideMovePlayerLeft			= 96012,		//�밴����Ҽ�+A�������ƶ���ɫ
	eText_GuideMovePlayerRight			= 96013,		//�밴����Ҽ�+D�������ƶ���ɫ
	eText_GuideFinishMovePlayerUp		= 96014,		//���������ǰ�ƶ���ɫ����
	eText_GuideFinishMovePlayerDown		= 96015,		//�����������ƶ���ɫ����
	eText_GuideFinishMovePlayerLeft		= 96016,		//������������ƶ���ɫ����
	eText_GuideFinishMovePlayerRight	= 96017,		//������������ƶ���ɫ����

	//�����������
	eText_ZhuJiangHpMaxAdd				= 98000,		//HP��������%d
	eText_ZhuJiangMpMaxAdd				= 98001,		//MP��������%d
	eText_ZhuJiangAttackPhysicsAdd		= 98002,		//����������%d
	eText_ZhuJiangAttackMagicAdd		= 98003,		//�����������%d
	eText_ZhuJiangDefendPhysicsAdd		= 98004,		//ħ����������%d
	eText_ZhuJiangDefendMagicAdd		= 98005,		//ħ����������%d
	eText_ZhuJiangExactAdd				= 98006,		//��������%d
	eText_ZhuJiangDodgeAdd				= 98007,		//��������%d
	eText_ZhuJiangCriticalAdd			= 98008,		//��������%d
	eText_ZhuJiangTenacityAdd			= 98009,		//��������%d

	eText_ZhuJiangSuccess				= 99100,		//����ɹ�
	eText_ZhuJiangNoHero				= 99101,		//�Ҳ�����Ӧ����������ʧ��
	eText_ZhuJiangNoMaterial			= 99102,		//û���㹻���ϣ�����ʧ��
	eText_ZhuJiangNoMoney				= 99103,		//û���㹻��Ǯ������ʧ��
	eText_ZhuJiangNoLevel				= 99104,		//�ȼ�����������ʧ��
	eText_ZhuJiangPopErro				= 99105,		//�����Ʒ���ܱ����ģ�����ʧ��
	eText_ZhuJiangSexErro				= 99106,		//�Ա𲻷��ϣ�����ʧ��
	eText_ZhuJiangFail					= 99107,		//����ʧ��

	eClient_AddInfo_2slk_NoRide			= 99200,		//��״̬�²�������
	eText_FuJiang_NotActived			= 99201,		//��ѡ����Ҫ��ս�ĸ���
	eText_CoutryActived					= 99202,		//��ǰû�й��һ
	eText_NoPetActived                  = 99203,        //û�г�ս�ĸ�����ʹ�õ���ʧ��  
	eText_LostThings                    = 99204,        //��ʧȥ��%d%s!
	eText_MovingContZHFJ                = 99205,        //�ƶ��в����ٻ�����
	eText_ContEnterTPHJ_Onbiaoche       = 99206,    //���ڹ����в��ܽ���̫ƽ�þ�
	eText_TargetMapCont_OnRiding        = 99207,       //Ŀ���ͼ������ˣ���������
	eText_ActivePetContStudySill        = 99208,    //��ս���ﲻ�ܽ��м���ѧϰ�������ջء�
	eText_PetError_OnActive             = 99209,    //��ǰ��ͼ�����ٻ�����

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

	eText_Country_BeStrong				= 99226,//���ұ�ǿ��

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

	eText_Quest_TaskScriptExp           = 99239, //{#fff4db30=���齱��: %d#}
	eText_Quest_ScriptExp1				= 99240,
	eText_Quest_ScriptExp2				= 99241,
	eText_WeopenHpWhithZero             = 99242, //�����𻵣����ܽ��й���

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


	eText_GuildUnionCamp				= 99259,//�����������ս
	eText_GuildUnionCamp_BullSystem_SignUp	= 99260,//���ս������ϵͳ����
	eText_GuildUnionCamp_BullSystem_Prepare = 99261,//���ս׼��״̬��ϵͳ����
	eText_GuildUnionCamp_TimeToCampStart	= 99262,//���������ս��ʼ
	eText_GuildUnionCamp_BullSystem_Enter	= 99263,//������ս��״̬��ϵͳ����
	eText_GuildUnionCamp_TimeToCampEnd		= 99264,//���������ս����
	eText_GuildUnionCamp_BullSystem_Fight	= 99265,//ս��ս��״̬��ϵͳ����
	eText_GuildUnionCamp_BullSystem_Over	= 99266,//���ս������ϵͳ����
	eText_GuildUnionCamp_EnterBattleInfo	= 99267,//��������ս������ϵ���ʾ
	eText_Camp_GuildUnionBattleResult		= 99268,// ֪ͨ����ս�����
	eText_SignUp_GuildUnionBattleSumError	= 99269,//��ǰ���������Ա���
	eText_SignUp_GuildUnionBattleNone		= 99270,//��ǰս������Ҫ���� ��ʼ�����ֱ�Ӳ���
	eText_SignUp_GuildBattleFull			= 99271,//������������
	eText_Enter_BattleSumError				= 99272,//����ָ��ʤ������ �����Խ���


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
	eText_CountryKing_New						= 99289,//%s��Ϊ %s �����¹���

	eText_Country_Battle_None					= 99290,

	eText_WorldBattle_Prepare					= 99291,
	eText_WorldBattle_Fight						= 99292,
	eText_WorldBattle_End						= 99293,

	eText_MonsterNurtureInfo_Buff				= 99294,

	eText_Country_Dismiss_Del					= 99295,//��ȥ��ְ�ɹ�
	eText_Country_Dismiss_Del_Not				= 99296,//��ȥ��ְʧ�� �޹�ְ
	eText_Country_Dismiss_Del_King				= 99297,//���������Դ�ȥ��ְ
	eText_Country_Dismiss_Del_Queen				= 99298,//����������������Դ�ȥ��ְ
	eText_Country_Dismiss_Del_NonCountry		= 99299,//�޹��Ҳ����Դ�ȥ��ְ

	eText_CampBattle_TimeShow					= 99300,//%d��%dСʱ%d����%d��
	eText_CampBatrle_Info						= 99301,//����%d %dСʱ%d���� ���� %d����
	eText_CampGuildBattle_States_0				= 99302,//����ս��ʼ���� ʱ��Ϊ %s
	eText_CampGuildBattle_States_1				= 99303,//����ս��ʼ׼�� ʱ��Ϊ %s
	eText_CampGuildBattle_States_2				= 99304,//����ս��ʼ���� ʱ��Ϊ %s
	eText_CampGuildBattle_States_3				= 99305,//����ս��ʼս�� ʱ��Ϊ %s
	eText_CampGuildBattle_States_4				= 99306,//����ս����  ʱ��Ϊ %s
	eText_CampCountryBattle_States_0			= 99307,//����ս��ʼ���� ʱ��Ϊ %s
	eText_CampCountryBattle_States_1			= 99308,//����ս��ʼ׼�� ʱ��Ϊ %s
	eText_CampCountryBattle_States_2			= 99309,//����ս��ʼ���� ʱ��Ϊ %s
	eText_CampCountryBattle_States_3			= 99310,//����ս��ʼս�� ʱ��Ϊ %s
	eText_CampCountryBattle_States_4			= 99311,//����ս����  ʱ��Ϊ %s
	eText_CampGuildUnionBattle_States_0			= 99312,//��������ս��ʼ���� ʱ��Ϊ %s
	eText_CampGuildUnionBattle_States_1			= 99313,//��������ս��ʼ׼�� ʱ��Ϊ %s
	eText_CampGuildUnionBattle_States_2			= 99314,//��������ս��ʼ���� ʱ��Ϊ %s
	eText_CampGuildUnionBattle_States_3			= 99315,//��������ս��ʼս�� ʱ��Ϊ %s
	eText_CampGuildUnionBattle_States_4			= 99316,//��������ս����  ʱ��Ϊ %s
	eText_CampWordBattle_States_1				= 99317,//Ұ��ս��ʼ׼�� ʱ��Ϊ %s
	eText_CampWordBattle_States_3				= 99318,//Ұ��ս��ʼս�� ʱ��Ϊ %s
	eText_CampWordBattle_States_4				= 99319,//Ұ��ս����  ʱ��Ϊ %s


	eText_LeaveTeam								= 99320,//����%����뿪���� �뾡��ص�ָ������
	eText_NonLeaveTeam							= 99321,//�Ѿ��ص��������� �뿪��������ȡ��

	eText_CampBattle_SignUp						= 99322,//����
	eText_CampBattle_Prepare					= 99323,//׼��
	eText_CampBattle_Enter						= 99324,//����
	eText_CampBattle_Fight						= 99325,//��ʼ
	eText_CampBattle_End						= 99326,//����


	eText_GuildCampBattle_Non					= 99327,//Ŀ�����
	eText_GuildCampBattle_Master				= 99328,//���ǰ���
	eText_GuildCampBattle_Level					= 99329,//Ŀ��ȼ�����
	eText_GuildCampBattle_Position				= 99330,//Ŀ��ְҵ����
	eText_GuildCampBattle_Offer					= 99331,//Ŀ��ﹱ����
	eText_GuildCampBattle_MaxSum				= 99332,//�����������
	eText_GuildCampBattle_Dou					= 99333,//Ŀ��������ͬȨ��

	eText_GuildCampBattle_Country				= 99334,
	eText_GuildCampBattle_Guild					= 99335,
	eText_GuildCampBattle_GuildUnion			= 99336,

	eText_GuildCampBattle_NonSelect				= 99337,//����ʧ�� δѡ��ָ�����

	eText_SuAnimalChangeName					= 99338,
	eText_ActionPetNon							= 99339,

	eText_PetEquip_Remove_Title					= 99340,
	eText_PetEquip_Remove_Context				= 99341,

	eText_Pet_Non								= 99342,//δѡ�񸱽�
	eText_Pet_Action							= 99343,//����δ��ս
	eText_Pet_Equip_Non							= 99344,//ָ������װ��������
	eText_Pet_Equip_TypeError					= 99345,//�Ǹ���װ��
	eText_Pet_Equip_Level						= 99346,//�ȼ�����
	eText_Pet_Equip_TimeEnd						= 99347,//װ������
	eText_Pet_Equip_Pos							= 99348,//���ض���λ
	eText_Pet_Equip_BagFull						= 99349,//��������

	eText_PetComPose_NorOne						= 99350,//��ǰ�����Ѿ���ѡ��
	eText_PetComPose_None						= 99351,//ѡ�񸱽�������
	eText_PetComPose_Erro1						= 99352,//�ϳ�ʧ�� δѡ��2������
	eText_PetComPose_Erro2						= 99353,//�ϳ�ʧ�� ѡ�񸱽�������
	eText_PetComPose_Erro3						= 99354,//�ϳ�ʧ�� ѡ�񸱽����ڳ�ս״̬
	eText_PetComPose_Erro4						= 99355,//�ϳ�ʧ�� ���ϲ���

	eText_Title_Sec								= 99356,//��

	eText_PKMode_NonGuid						= 99357,

	eText_Char_PetInfo							= 99358,

	eText_Guild_SellItem						= 99359,

	eText_Bag_ShopMove							= 99360,
	eText_Bag_CKMove							= 99361,

	eText_ShopCenter_Jifen					     	= 99362, //�����̳�
	eText_ShopCenter_Bangjin						= 99363, //����̳�
	eText_ShopCenter_YuanBao						= 99364,//Ԫ���̳�
	eText_ShopCenter_All							= 99365, //ȫ��
    eText_ShopCenter_Hot							= 99366, //����
	eText_ShopCenter_New							= 99367, //��Ʒ

	eText_PetEquipError								= 99368,//����������װ�� �޷����в���

	eText_GuildBattle_Secc							= 99369,//��Գɹ�
	eText_GuildBattle_OneLose						= 99370,//%s�����ս�������� %s����ʤ��
	eText_GuildBattle_TwoLose						= 99371,//%s�����%s�����ս������ʱ ս���Զ�����
	eText_GuildBattle_Win							= 99372,//Ѫսɳ��ʤ��
	eText_GuildBattle_Lose							= 99373,//Ѫսɳ��ʧ��

	eText_GuildChangeName_NotMaster					= 99374,//�ǹ���᳤���Ը���
	eText_GuildChangeName_NonChange					= 99375,//���������ޱ仯
	eText_GuildChangeName_Error						= 99376,//�������ư����Ƿ��ؼ���
	eText_GuildChangeName_Error2					= 99377,//�������ƹ���
	eText_GuildChangeName_Error3					= 99378,//�������ƹ���
	eText_GuildChangeName_Error4					= 99379,//�������Ʊ����Ƿ��ַ�
	eText_RoleChangeName_Error						= 99380,//���ƴ��� ����������
	eText_GuildChangeName_Error5					= 99381,
	
	eText_PKEnterJianYu								= 99382,

	eClient_AddInfo_CampBattleDuel					= 99383,//ս�������Ա���

	eClient_AddInfo_CurMapCantDuel					= 99384,//��ǰ��ͼ�����д�
	eClient_AddInfo_CurZoomCantDuel					= 99385,//��ǰ�������д�
	eClient_AddInfo_EndTimeCountryTime				= 99386,

	eClient_FlyToMap_Stall							= 99387,//��̯�����Դ���
	eClient_CampBattle_Team							= 99388,//��ս�������Դ�������
	eClient_PkValue_ADD								= 99389,//���%d��PKֵ
	eClient_CountryRaiseItem						= 99390,//%s�� %sΪ���Ҿ��״����ʽ𣬻��ļ������
	eClient_GuildRaiseItem							= 99391,//%s�� %sΪ������״����ʽ𣬻��ļ������
	eClient_PkValue_Del								= 99392,//����%d��PKֵ

	eClient_ClearTeam_NonTeamHeader					= 99393,
	eClient_ClearTeam_NonTeam						= 99394,
	eClient_ClearTeam_TeamMemberError				= 99395,
	eClient_ClearTeam_CD							= 99396,//���Ĳ�������,����%s���Ժ��ٴγ���!
	eClient_ClearTeam_TeamMemberSucc				= 99397,//�������óɹ�!

	eText_Guild_NotEnoughMission					= 99398,//û���㹻��ʹ����
	eText_Quest_Frozen								= 99399,//(�Ѷ���)

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
	eText_GuildGeneral_AddBattleWorldInfo			= 99436,//%s %s ���Ὺս
	eText_AddGuildGeneralTip						= 99437,
	eText_GuildGeneral_CanelBattle					= 99438,//xx��������ʵ�����ã���xx���Ž�еͶ��
	eText_GuildGeneral_AddBattle					= 99439,//xx���Ž���xx���ŵ���ս��˫����������xһ������
	eText_GuildGeneral_AddBattleDel					= 99440,//�Է��ܾ���ս
	eText_GuildGeneral_AddBattleOK					= 99441,//�Է�������ս
	eText_GuildGeneralBattle_Name					= 99442,

	eText_QuestEntrust_NonMoney						= 99443,
	eText_QuestEntrust_NonStates					= 99444,

	eText_QuestEntrust_CancelError					= 99445,

	eText_FlyToPositionTip							= 99446,
	eText_FlyToPosition_TimeOut						= 99447,

	eText_Country_IncreaseGuildMoney				= 99448,//���%d����ʽ�
	eText_Country_DecreaseGuildMoney				 = 99449,//ʧȥ%d����ʽ�

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
	eText_Script_GuildCampBattlePoint_Rank			= 99481,//����Ѫսɳ���������а����������
	eText_GuildGeneral_Target_WriteMsg				= 99482,
	eText_GuildGaneral_TimeError					= 99483,

	eText_MountMoveStar_OleMountNull				= 99484,//Դ����δ����
	eText_MountMoveStar_NewMountNull				= 99485,//������δ����
	eText_MountMoveStar_MountStarLevel				= 99486,//��������ȼ�����
	eText_MountMoveStar_MoneyError					= 99487,//��Ǯ����
	eText_MountMoveStar_ItemError					= 99488,//���ϲ���
	eText_MountMoveStar_SetMountError				= 99489,//�������� ��Ҫ��ȡ���Ѿ�ѡ�������

	eText_MountMoveStar_NewMountActionError			= 99490,
	eText_MountMoveStar_OldMountActionError			= 99491,


	eText_EpistarPointSucc							= 99492,//��Ԫ����ӳɹ�
	eText_EpistarPointError							= 99493,//��Ԫ�����ʧ��
	eLogin_ServerFull								= 99494,//����������

	eText_MountMoveStar_OneMount					= 99495,//Դ�����Ŀ������Ϊͬһ���� ����������
	eText_MountMoveStar_Level						= 99496,//Դ����ȼ� С�ڵ��� Ŀ������ĵȼ� ����������
	eText_MountMoveStar_NewMountError				= 99497,//Ŀ�������޷�ǿ�� ����������
	eText_MountMoveStar_OldMountError				= 99498,//Դ�����޷�ǿ�� ����������

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
	eLogin_PassWordCard								= 99517,		// ��֤�û�
	etext_Login_PwdCardError						= 99518,
	eText_MountMoveLevel_Success					= 99519,//�������ǳɹ� ��ǰ�ȼ�Ϊ%d
	eText_Pet_MaxSavvy								= 99520,//���������Ѿ�����ߵȼ� �޷�ǿ��
	eText_Pet_WorldInfo								= 99521,//%s������%s������ǿ����%d
	eMaxText
};

class Name
{
public:
	Name();
public:
	~Name();
};
