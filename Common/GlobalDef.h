/********************************************************************
    Filename:     GlobalDef.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __COMMON_GLOBALDEF_H__
#define __COMMON_GLOBALDEF_H__

#pragma once

#include "MeRTLibsServer.h"
#include "MsgBase.h"
#include "ErrorCode.h"
#include "DataChunkWriter.h"
#include "FuncPerformanceLog.h"
#include "Dxsdk\d3dx9math.h"
#include "ResourcePath.h"
#include "PasswordDefine.h"
#include "TimeEx.h"
#include "IBAA_RandAlgorithm.h"
#include "GameDefineGlobal.h"
#include "GameDefineChar.h"
#include "GameDataType.h"

// ʹ���µĵ�¼����
#if 1

#ifndef __NEW_LOGIN__
#define __NEW_LOGIN__
#endif
 
#endif
////////////////////////////////////////////////////////////////////////////
//#define USE_OLD_LOGIN
//#ifndef __NEW_LOGIN__
//	#undef  __NEW_LOGIN__
//#endif
////////////////////////////////////////////////////////////////////////////

// [��Ϣ��ȫת��] BEGIN HANDLE END Ϊһ��  -�����µ�ָ��pTMessage
#define SAFE_CONVERSION_MESSAGE( messagepointer, messagetype ) \
	messagetype* pTMessage = (messagetype*)messagepointer; \
	CHECK_RETURN( pMessage->GetLength()!=sizeof(messagetype), ER_MessageLengthError); 

// [GameServer] BEGIN HANDLE END Ϊһ��
#define GAMESERVER_MESSAGE_MAPPING_BEGIN \
        switch ( dwType ) \
        {

#define GAMESERVER_MESSAGE_HANDLE( messageId , messageHandle ) \
        case messageId: \
            { \
                messageHandle( pMsg ); \
                return true; \
            } \
            break;

#define GAMESERVER_MESSAGE_MAPPING_END \
        }

// [DataBase] BEGIN HANDLE END Ϊһ��
#define DATABASE_MESSAGE_MAPPING_BEGIN \
    switch ( pMessage->type ) \
        {

#define DATABASE_MESSAGE_HANDLE( messageId , messageHandle ) \
        case messageId: \
            { \
                messageHandle( pMessage ); \
            } \
            break;

#define DATABASE_MESSAGE_MAPPING_END \
        }

// [Platform] BEGIN HANDLE END Ϊһ��
#define PLATFORM_MESSAGE_MAPPING_BEGIN \
    switch ( type ) \
        {

#define PLATFORM_MESSAGE_HANDLE( clientId, messageId , messageHandle ) \
        case messageId: \
            { \
                messageHandle( clientId, pMsg ); \
                return; \
            } \
            break;

#define PLATFORM_MESSAGE_MAPPING_END \
        }


// [��ͨ��] BEGIN HANDLE END Ϊһ��
#define MESSAGE_MAPPING_BEGIN \
        CHECK_RETURN( pMessage==NULL, ER_NullPointer); \
        switch ( msgType ) \
        {
//-1--[��]ת��[ֱ��]Handle([Null],pMessage )
#define MESSAGE_HANDLE_UNPACK( messageId, messageClassType, messageHandle ) \
		case messageId: \
				{ \
				messageHandle(pMessage ); \
				} \
				break;
//-2--[��ȫ]ת��[����]Handle([Null],pTMessage )
#define MESSAGE_HANDLE_USER( messageId, messageClassType, messageHandle ) \
		case messageId: \
			{ \
			    SAFE_CONVERSION_MESSAGE(pMessage, messageClassType ); \
				messageHandle(pTMessage ); \
			} \
			break;
//-3--[��]ת��[����]Handle([Null],pTMessage )
#define MESSAGE_HANDLE_USER_NOTCHECK( messageId, messageClassType, messageHandle ) \
		case messageId: \
			{ \
				messageClassType* pTMessage = (messageClassType*)pMessage; \
				messageHandle(pTMessage ); \
			} \
			break;
//-4--[��ȫ]ת��[����]Handle([pClient],pTMessage )
#define MESSAGE_HANDLE( messageId, messageClassType, messageHandle ) \
        case messageId: \
            { \
                SAFE_CONVERSION_MESSAGE(pMessage, messageClassType ); \
                messageHandle( pNetClient, pTMessage ); \
            } \
            break;
//-5--[��ȫ]ת��[����]Handle( [Null],pTMessage ) �ظ���
#define MESSAGE_HANDLE_1( messageId, messageClassType, messageHandle ) \
        case messageId: \
            { \
                SAFE_CONVERSION_MESSAGE(pMessage, messageClassType ); \
                messageHandle( pTMessage ); \
            } \
            break;
//-6--[��]ת��[����]Handle( [pClient],pTMessage )
#define MESSAGE_HANDLE_NOTCHECK( messageId, messageClassType, messageHandle ) \
        case messageId: \
            { \
                messageClassType* pTMessage = (messageClassType*)pMessage; \
                messageHandle( pNetClient, pTMessage ); \
            } \
            break;

#define MESSAGE_MAPPING_END \
        }
//////////////////////////////////////////////////////////////////////////
// С����Сֵ�����ĳֵ
#define FIX_NUMBER(l,n,m)\
    {\
    if( l < n )\
        {\
        l = m;\
        }\
    }
#define FIX_NORMAL(value) FIX_NUMBER(value,1,1)

#define FIX_NORMAL_ZERO(value) FIX_NUMBER( value, 0, 0)

//////////////////////////////////////////////////////////////////////////
// GlobalDef.h

//////////////////////////////////////////////////////////////////////////
#pragma warning( disable : 4800 )
//////////////////////////////////////////////////////////////////////////


#define MAX_NAME_CREATE          16
#define MAX_NAME_STRING          32
#define MAX_PASSWORD_STRING      32
#define MAX_TITLE_COUNT          255
#define MAX_RECIPE_COUNT         500
#define BORN_POINT_COUNT         6
#define IP_LENGTH                16
#define MAC_LENGTH               20
#define INVALID_SERVERID         0xffffffff
#define MAX_KILLINFO_COUNT       100
#define MAX_SPECIALQUEST_COUNT   10
#define MAX_AREAREPULATION_COUNT 10
#define MAX_FRIENDDEGREE_COUNT   13
#define MAX_PRESSKEYSUIT_COUNT   10         // ����һ����װ����
#define MAX_ACHIVEVMENT_COUNT    2000       // ����ɾ��ܼ�
#define MAX_PETIDENTIFY_COUNT    4000       // ����ͼ������
#define MAX_GUIDE_COUNT          1000       // ����ָ��
#define MAX_IDENTIFY_TOTAL		 65000		// ͼ�����ۼ�������

#define MAX_KILLSUM				 3000

#define MAPTILESIZE         (128.0f*0.02f) // ���ο�Ļ�����С ��λ�ռ����굥λ
#define CHUNK_SIZE          16.0f          // Chunck ��λ�ռ����굥λ
#define DORIDE_RATE         15000          // ��������ļ��

#define INVALID_CHAR_ID     -1

#define MOVEVELOCITY        (3.0f)                 // ÿ���ƶ�������Ҳ���������ƶ�����
#define ONESTEPCOST         (1000.0f/MOVEVELOCITY) // һ�����ĵ�ʱ�䣬����

#define CHAR_DEFAULTBODYSIZE 0.3
#define GLS_CheckBlockTime   (1000*60)		
#define PI	3.1415926f

//��Ϸ������Ϣ�Ѽ�������
#define DATACOLLECTINTERVAL  (1*1000) //һ�����Ѽ�һ����Ϣ(T)
#define SYNCCHARPOSINTERVAL  (5*1000) //��Ϸ������clinetͬ��������Ϣ�ļ��

#define QUEST_MAX        4
#define PKVALUEDAILY_MOD 5 // PKֵÿ���õ����ֵϵ��

#define PLUE_EXP_MODULUS     0.2
#define NEGATIVE_EXP_MODULUS 0.5
#define MOUNT_EXP_MODULUS    1.0

#define CHAR_REFRESHTIME 1000
#define EMISSIONFLYCOST 40
#define TEAM_EXP_DIS 60.0f
#define PackagePickDistance 1.5f            //ʰȡ��������Ч����
#define TARGET_VIEW_DIS 60.0f   
#define PickAuttonDistance 70.0f			//ʰȡ����ID_BUTTON_PickOn��ť��ʰȡ����

#define BaseMoveSpeed  5.0f

#define MAXEMISSIONNUM 6    //�����ͼ����������

#define SPELLACTION_CASTTIME 200
#define ONE_MIN              60000
#define ONE_SEC              1000
#define CheckPlayerPerTime   60000   // һ����
#define TellPlayerPerTime    1800000 // 30����

#define PKVALUEADD_PERTIME 2        // ÿ��ʱ������ӵ�PKֵ��ֻ�е�PKС��0ʱ

#define ECTYPEMONSTERSTARTID 110000 // ���ID�Ժ���Ǹ�������ID
#define ECTYPEMAPMONSTERIDLENGTH 4  // ������ͼ����ID��4λ
#define NORMALMAPMONSTERIDLENGTH 6  // ��ͨ��ͼ����ID��6λ
#define MAPLEVELPERPLAYERLEVEL 5    // ÿ����ͼ�ȼ���Ӧ�����ɫ5��
#define MAX_MAP_LEVEL 40            // Ŀǰ��ͼ��40���ȼ� (�����ɫ ÿ5��һ���ȼ�) 

#define PrivateShopSellItemDiscount 0.95  // ��̯��˰

// ��ɫ�Ƿ��赲

#define OneMinuteSecond ( 60 )          // 1��������
#define OneHourSecond   ( 60 * OneMinuteSecond )           // һСʱ������
#define OneDaySecond    ( 24 * OneHourSecond   )

#define OneMinuteMicroSecond ( 60 * 1000 )          // 1���Ӻ�����
#define OneHourMicroSecond   ( 60 * OneMinuteMicroSecond )           // һСʱ�ĺ�����
#define OneDayMicroSecond    ( 24 * OneHourMicroSecond   )

#define ItemUnLockTime ( 3 * 24 * 60 * 60 ) // 3��

// ��ȫ��ͼ
#define Safe_Map_Id     2
#define Safe_Map_PosX   183.0f
#define Safe_Map_PosY   194.0f
#define Safe_Map_Dir    0.0f

//#define MoBeiMapID     9         // Į����ͼID
//#define LiaoDongMapID  0         // �ɶ���ͼID
//#define DunHuangMapID  8         // �ػ͵�ͼID
//#define GaoGouLiMapID  1         // �߾�����ͼID

#define eMAX_TEMP_BUFF 0xFF
// CharacterServer Id
//#define CENTERLOGINSERVERID 99
#define CHARACTERSERVERID 100

#define WORLD_HEIGHT 40000.f


// ��Ǯ�ܶ������
#define MoneyUnit   10000
#define MaxMoney30 ( 20 * MoneyUnit )           // 30����Ǯ�ܶ����ֵ
#define MaxMoney40 ( 2000 * MoneyUnit )          // 40����Ǯ�ܶ����ֵ
#define MaxMoney55 ( 20000 * MoneyUnit )         // 55����Ǯ�ܶ����ֵ
#define MaxMoney60 ( 100000 * MoneyUnit )         // 55�����Ͻ�Ǯ�ܶ����ֵ


// �����ܶ������
#define JiaoZiUnit   10000
#define MaxJiaoZi30 ( 20 * JiaoZiUnit )              // 30����Ǯ�ܶ����ֵ
#define MaxJiaoZi40 ( 2000 * JiaoZiUnit )             // 40����Ǯ�ܶ����ֵ
#define MaxJiaoZi55 ( 20000 * JiaoZiUnit )           // 55����Ǯ�ܶ����ֵ
#define MaxJiaoZi60 ( 100000 * JiaoZiUnit )           // 55�����Ͻ�Ǯ�ܶ����ֵ

// �ٻ�������
#define CharSummonPetMaxCount   3

#define CHAT_STRINGMAX 500
//������Եȼ�
#define MaxSavvy 10

// ��Ч��HeroID
#define INVALID_HERO_ID		0xFFFF

//��Ч�ĵ�ͼID
#define INVALID_MAP_ID		0xffffffff

//��������
#define Hunting_MaxAccept_OneDay 10
#define MaxCount_Show 10


#define PwdCardLength (8) //�ܱ���ÿ����Ԫ���ַ�����
#define PwdCardSerialLength (32) //�ܱ���ÿ�������к�
// world define
const unsigned short ErrorUnsignedShortID = 0xffff;
const unsigned long  ErrorUnsignedLongID  = 0xffffffff;

const int dr_worldMaxPlayers      = 5000;
const int dr_worldMaxCharacters   = 200000; // World����ɫ��/*32767*/ 65535
const int dr_worldMaxStages       = 128;   // �������
const int dr_refreshstagezonerate = 1;     // ˢ�´��������Ƶ��

// stage define
const int dr_stageMaxCharacters  = 200000;     // Stage����ɫ��
const int dr_stageMaxAreas       = 32*32*8*8; // ���������
const int dr_stageMaxMapWidth    = 128*32;    // ��ͼ�����
const int dr_stageMaxMapHeight   = 128*32;    // ��ͼ���߶�
const int dr_stageAreaSize       = 12;        // 12 �����С ԭ�� 16
const int dr_stageAIInterval     = 200;       // ��ͼ�ڹ����˼��Ƶ��

// area define 
//const int dr_areaMaxCharacters   = dr_stageAreaSize*dr_stageAreaSize;   // Area����������ɫ��
const int dr_areaMaxCharacters   = 1024;   // Area����������ɫ��

// zone define
const int dr_stageMaxZones      = 32*32*16;
const int dr_zoneMaxCoveredArea = 256;

const int dr_MaxAttackTarget           = 16; //��๥��Ŀ��
const int dr_MaxNameString             = MAX_NAME_STRING;     // �û���
const int dr_MaxUserName               = dr_MaxNameString;
const int dr_MaxPassword               = MAX_PASSWORD_STRING; // ����
const int dr_MaxTongCount              = 9;
const int dr_MaxPublicMessagesPerCount = 100;
const int dr_MaxPlayerName             = dr_MaxNameString + 1;
const int dr_MaxTongName               = 8;
//const int dr_MaxTongNumber             = 9;
const int dr_MaxPath                   = 256;
const int dr_MaxChatString             = 1536;//2048;//1024;
const int dr_MaxOfficialTitle          = 16;
const int dr_MaxYearName               = 16;
const int dr_LengthDate                = 20;
const int dr_MaxReputeName             = 18;
const int dr_MaxOfficialLevel          = 10;

// ��Ʒ����
// ��Ʒ���ֵĳ���ӦΪӢ�İ���Щ���ߵ����ֻ�ܳ�,�����޸�Ϊ64,��ǰΪ32
const int dr_MaxItemName               = 2 * dr_MaxNameString;
const int dr_MaxItemDesc               = 100; //��Ʒ˵������
const int dr_MaxShopDesc               = 24;  // �����̵�˵��
const int dr_MaxQuestDesc              = 256; // ����˵��
const int dr_MaxQuestStateDesc         = 128; // ����״̬˵��
const int dr_MaxQuestNextState         = 4;   // ��һ��������״̬����
const int dr_MaxQuestState             = 10;  // ����״̬����
const int dw_MaxQuestReward            = 8;   // ���񱨳�
const int dr_MaxCharactersEachAccount  = 3;   // ÿ���˺�����3����ɫ

const unsigned long dr_MaxGuilSkillNum  = USHRT_MAX;     //������������
                                     
// �������                          
const int dr_MaxQuest                  = 3000;     // ���������
const int dr_MinQuestId                = 3000;     // ������ʼId
const int dr_MaxRemindQuestId          = 5000-1; // �������Id
const int dr_MaxQuestId                = dr_MinQuestId+dr_MaxQuest-1; // �������Id
const int dr_MaxActiveQuest            = 20/*10*/; // ���������
const int dr_MaxGameVersion            = 12;       // �汾�����
const int dr_MaxShopItem               = 50;       // �̵���Ʒ�����
const int dr_MaxShoper                 = 20;       // �̵������
const int dr_MaxBattleMasterCount      = 1;        // ��������������
const int dr_MaxBattleAttacker         = 1;        // ���ǹ���������

// ���ݱ���
const unsigned long dwAutoSaveDelay = 1000*60*5; //�Զ��洢���ʱ��
const unsigned int nSaveBatchNum    = 50;        //ÿ����ѭ������������

// �����
const float fDuelLength = 20.0f;
const float fDuelOutRange = 40.0f;

// �������
const float fSellBuyToNpcRange = 20.0f;
const float fSellDiscountRate  = 0.33f;
const float fReclaimDiscountRate  = 0.7f;

const int nReputeFlagCount = 26;

const unsigned short GameServerIdPrefix  = 0000;
const unsigned short GateServerIdPrefix  = 1000;
const unsigned short WorldServerIdPrefix = 2000;
const short          DiskServerId        = -1;
const unsigned long  EnterWorldMessageIntervalTime = 3000;

const uint32         bangGongMax = 65535;

const uint32         protectTime = 60 * 1000 * 30;

const short          manual_levelup = 29;//��ʼ�ֶ������ĵȼ�
const short          save_max_level_exp = 3;//�������3���ľ���

const static int	 MaxPetDuration = 5000;
//////////////////////////////////////////////////////////////////////////
// ö��
enum EGlobelConst
{ // ȫ����ö�ٶ���ĳ���    
    RAND_NUM               = 100,
    GEM_RAND_NUM           = 100, // ��ʯ��Ƕ�������
    ADD_STATUS_RAND_NUM    = 100, // buffer���õ������
    WARD_RAND_NUM          = 100,
    RAND_THOUSAND          = 1000,// ǧ�������
    MAX_LEVEL_LIMIT        = 200, // ��ߵĵȼ�
    ARMS_NAME_LENGTH       = 20,
    CANEQUIPITEM_HP_UNIT   = 100,
    MIN_ENMINYVALUE        = 10,  // ÿ���������ӵĳ��ֵ
    MULTIPLE_ENMINY        = 10,  // ���ϵ������
    ATTACK_FLOAT_COUNT     = 5,   // ��������ֵ��
    LEVEL_DISTANCE_SEGMENT = 5,   // �ȼ�����
    GEM_MAX_COUNT          = 3,   // ��ʯ������    
    CompoundItemID         = 0,
    ClearElementCount      = 5,   // ������װһ��ֻ��ϴ��5��
};

enum EConstDefine
{
    More_iCharPerAccount                = 3    // ÿ���˺���һ����Ϸ��������ӵ��3����ɫ
    ,More_iSkillCountPerLinkedSkills    = 5    // ÿ��������5����ʽ���
    ,More_iMaxLinkedSkills              = 5    // ÿ����ɫ�����и���
    ,More_iMaxCountOfAItem              = 30   // ÿ����Ʒ��һ����Ʒ�������ĸ���
    ,More_iMaxVars                      = 6000 // ��ɫϵͳ�����ĸ���
    ,QuestLimitTimeMaxCount             = 5    // ������ʱ����
    ,More_iMaxTempVars                  = 2000
    ,More_iMaxSysVars                   = 5000
    ,More_iMaxGuildVars                 = 500  // �����������
    ,More_iMaxAchieveVars               = 300  // �ɾͼ������� 

    ,VarTimeBeginRange                  = 500 // ��ʼʱ�� 2 �� short ��һ��ʱ��
    ,VarTimeEndRange                    = 999 // ����ʱ��

    //��ݱ�����ű�� ά���߻���ͣ�ĸ��ı仯
    ,More_exMainUIMax                    = 25//| 0--25  ��չ������� s_CUI_ID_FRAME_Exmain.m_pID_LISTIMG_exmain
    ,More_mainUIMax                      = 67//| 26--67 �������� s_CUI_ID_FRAME_MAIN.m_pID_LISTIMG_Hotkey(0,1,2����14��)
    ,More_ainUIMaxOnly                   = 14//|            (0,1,2����14��)
    ,More_rightSkill                     = 68//| 68     �Ҽ������ s_CUI_ID_FRAME_SelectSkill.m_pID_LISTIMG_skill
    ,More_rightShortcutBegin             = 69//| 69-80  �������� ��
    ,More_skillEducate                   = 81//| 81     ��������
    ,More_iHotkey                        = 82//| ����    enumConst::More_iHotkey ��Ϊ36

    ,const_iCharMaxLevel        = 200   //������ߵȼ�
    ,More_nMapSize              = 128   //��½�е�ͼ�Ĵ�С
    ,More_iMaxSkillByte         = 32    //        
    ,More_iMaxSkill             = More_iMaxSkillByte*8 //���8*32������
    ,More_iMaxXinFa             = 20    //���ѧϰ���ķ�
	,More_iMaxHeroSkill			= 3		//������������
    ,More_iMaxSkillKnown        = 100   //���ϰ�õļ���
    ,More_iCharDataRestoreCheck = 3000  //HP,MP�ָ���ʱ�䵥λ
    ,More_iCharPoisonCheck      = 3000  //�ж���Ѫ�ļ����
    ,More_iMaxLinkSymbolStone   = 3
    ,More_iMaxLinkNormalSkill   = 5
    ,Beginner_LevelLimit        = 5
    ,ObtainExp_LevelDiffLimit   = 5
    ,AttackMonster_MaxPlayer    = 20    
	,CheckDamageScoreTime		= 1000*10  
    ,Distance_ShareTeamExp      = 50    
    ,UpgradeSkillMaxLimit       = 10
    ,UpgradePropertyMaxLimit    = 300
    ,PowerPointMax              = 3
    ,PowerCountMax              = 300
	,More_nCardMax				= 128 //������Ͽ����������
	,More_nCardAchieve			= 32  //���Ƴɾ�����
	,More_nHuntingNum			= 32  //��ǰ��ҿ�ѡ��������������
};

enum EHandType
{
    HT_RightHand, // ����
    HT_LeftHand,  // ����
};

enum EConstItemId
{ //[0,999]
    const_ustItemMoney  = 1,     // Ǯ
    const_ustItemGold   = 6,     // Ԫ��
    SCAPEGOAT_ID        = 45000, // ����ID
    PALLADIUM_ID        = 14022 ,// �ػ���ʹID
    ITEM_LOCK_INTENSIFY = 4678,  // �����쾧
    NorPackageItemID    = 2,     // ��ͨ����
    MidPackageItemID    = 3,     // �еȰ���
    AdvPackageItemID    = 4,     // �߼�����
    PackageModelID      = 4000,  // ����ģ��id  
    HighShoutItemID     = 6108,  // ���纰������

    ResetPubQuestItemID1 = 6068,   // �ʰ�=>�ʰ���
    ResetPubQuestItemID2 = 15071,  // �ƹ�=>�о���

};

enum EWeaponType
{
    eWeaponType_Combat  , // ͽ��
    eWeaponType_Warrior , // սʿ
    eWeaponType_Mage    , // ��ʦ
    eWeaponType_Taoist  , // ��ʿ
    eWeaponType_Assassin, // �̿�
    eWeaponType_Hunter  , // ����
    eWeaponType_Sniper  , // ��ǹ
    eWeaponType_Shied   , // ����
    eWeapontype_Flag    , // ����
    eWeaponType_Max     ,
    eWeaponType_Invalid, // ��Ч��
};

enum EFightStatus
{ // ս��״̬��־ //�� 16��bit��
    eFIGHT_NOFLAG       = 0,    // û������״̬
    eFIGHT_RELIVE       = 1<<0, // ����
    eFIGHT_MISS         = 1<<1, // ����δ����
    eFIGHT_BEKILLED     = 1<<2, // Ŀ�걻ɱ
    eFIGHT_BACKSTRIKE   = 1<<3, // ����
    eFIGHT_CRITICALHIT  = 1<<4, // ����
    eFIGHT_CANCEL       = 1<<5, // ȡ��
    eFIGHT_ERROR        = 1<<6, // ս������
    eFIGHT_SUCKHP       = 1<<7, // ��Ѫ
    eFIGHT_DAMREFLECT   = 1<<8, // ����
    eFIGHT_SELFBEKILLED = 1<<9, // ��������ɱ
    eFIGHT_DAOXINGRESIST= 1<<10,// �����ֿ�
    eFIGHT_DAOXINGSTIFLE= 1<<11,// ����ѹ��
};

enum EReasonType
{ // ����ԭ��
    eREASON_NOFLAG      = 0,     // û������
    eREASON_NOTPERMIT   = 1<<0,  // ��������
    eREASON_ACK         = 1<<1,  // ȷ��
    eREASON_LOSTCONTROL = 1<<2,  // ʧȥ����
    eREASON_UNMOVEABLE  = 1<<3,  // �����ƶ�
    eREASON_UNARRIVABLE = 1<<4,  // ���ɴ�
    eREASON_OUTOFRANGE  = 1<<5,  // ������Χ
    eREASON_OUTOFSIGHT  = 1<<6,  // ������Ұ
    eREASON_MAYIDOIT    = 1<<20, // �ҿ�����
    eREASON_STOPIT      = 1<<21, // ͣ����
    eREASON_UNKNOWN     = 1<<31  // ԭ����
};

enum EPathDir
{ //·������
    DIR_0,
    DIR_45,
    DIR_90,
    DIR_135,
    DIR_180,
    DIR_225,
    DIR_270,
    DIR_315,
};

enum EActionType
{
    eAttack1,
    eAttack2,
    eAttack3,
    eAttack4,
    eAttack5,
    eMiss,      // ʧ׼
    eFightBack, // ����
    eResist,    // ��
    eHurt,
    eDead,
    eIdle,
    eWalk,
    eRun,

    eActionUnknown,
};

enum ENpcShowType
{
    eNormalNpc    = 0,    // ��ͨnpc
    eNotChangeDir = 1<<0, // ���������ת��
    eNotShadow    = 1<<1, // ��������Ӱ
};

enum EActionFlag
{
    eNormalFight  = 0,      // ��ͨ״̬
    eFighting     = 1 << 0, // ս����
    eSitting      = 2 << 1, // ���Ŷ���
    ePrepareFight = 3 << 1, // ׼��ս������
};

enum ENpcType
{
    eNT_Normal = 0   , // ��ͨNPC
    eNT_Restore      , // ҩƷ����
    eNT_Weapon       , // ��������
    eNT_Jewelry      , // ��������
    eNT_Dress        , // ��װ����
    eNT_Material     , // ��������
    eNT_Transport    , // ����npc
    eNT_Cavalry      , // ��������
    eNT_Storage      , // �ֿ�npc
    eNT_Star         , // ����npc
    eNT_MakeItemNpc  , // �ϳ�NPC
    eNT_Activity     , // �NPC
    eNT_Feudal       , // �ٸ�����NPC
    eNT_Sale         , // ��������NPC
    eNT_SpecialSale  , // ����һ���
    eNT_ScriptNpc    , // �ű�������NPC
	eNT_GongXun      , // ����NPC
	eNT_MingWang     , // ����NPC
	eNT_ShiZhuang    , // ʱװNPC
	eNT_WenDa        , // �ʴ�NPC
	eNT_JiNeng       , // ����NPC
	eNT_PeiJian      , // �������NPC
	eNT_ShiWu        , // ʳ��NPC
	eNT_YiZhan       , // ��վNPC
	eNT_ZaHuo        , // �ӻ�NPC
	eNT_FenJie       , // �ֽ�NPC
	eNT_QianZhuang   , // ǮׯNPC
	eNT_Pub          , // �ƹݻư�NPC
	eNT_MoveStar     , // ����
	eNT_SpecialRepair, // ����
	eNT_Patrol       , // Ѳ��
	eNT_Ship         , // ����
	eNT_KeepWord2    , // ����npc����2
	eNT_KeepWord3    , // ����npc����3
	eNT_KeepWord4    , // ����npc����4
	eNT_KeepWord5    , // ����npc����5
	eNT_KeepWord6    , // ����npc����6
	eNT_KeepWord7    , // ����npc����7
	eNT_KeepWord8    , // ����npc����8
	eNT_KeepWord9    , // ����npc����9
    eNT_Item        = 99  ,//��Ʒ��ʽNPC
    eNT_Battle      = 100 , //ս��Npc
	eNT_Elevator    = 101 , //����
	eNT_SpecialNpc  = 102 , //����NPC,���������ʾ
    eNT_Max,
};

enum EObjectType
{
    // �ܳ�ν
    Object_Dump = 0       , // �����κ�����npc
    Object_Player         , // ���
    Object_Npc            , // npc
    Object_Item           , // ����
    Object_Monster        , // ����
    Object_Effect         , // ����    

    // Object_Monster ����
    Object_MonsterNormal = 10, // һ��� �ֲ��ڵ�ͼ��һȺȺ�Ĺ� boss
    Object_MonsterPet        , // �ٻ���
    Object_MonsterIllusion   , // �����
    Object_MonsterResource   , // ��Դ��
    Object_MonsterTrap       , // ������ع�
    Object_MonsterCapture    , // ��׽�����
    Object_MonsterProtected  , // �������� �ڳ� ��
    Object_MonsterBuilding   , // ����
    Object_MonsterNurturePet , // ������
    Object_MonsterSpecial    , // ר����
    Object_MonsterPickup     , // ʰ��С��

    // Object_Npc ����
    Object_NpcNormal     = 50, // ��ͨ�ű�Npc
    Object_NpcFight          , // ��Ѳ��ս��Npc
    Object_NpcShip           , // ��Ship���ݵ�����Npc
};

namespace CheckAttack
{
    enum ECheckAttackResult
    {
        CanNotAttack = 0,   // ���ܹ���
        EnmityFightCamp,    // �ж���Ӫ
        EnmityCountry,      // �жԹ���
        EnmityForce,        // �ж�����
        EnmityTarget,       // ���Ŀ��
        AttackUnknow,
    };
}

namespace ForceDefine
{
    enum EConstDefine
    {
        NoneForce = 0,      // ������
        NormalPlayerForce,  // ��ͨ���
        EnmityPlayerForce,  // �������
        NormalNpcForce,     // ��ͨnpc����
        FightNpcForce,      // ս��npc����
        NormalMonsterForce, // ��ͨ��������
        PetMonsterForce,    // �����������
    };

    // �ж��Ƿ��ǳ������( ��ʱд������,�Ժ�Ҫʹ������ )
    static bool CheckEnmityForce( uint8 nFirstForce, uint8 nSecondForce )
    {
        switch ( nFirstForce )
        {
        case NoneForce:
        case NormalNpcForce:
            return false;
            break;
        case NormalPlayerForce:
        case EnmityPlayerForce:
            {
                switch ( nSecondForce )
                {
                case NormalMonsterForce:
                    return true;
                    break;
                }
            }
            break;
        case FightNpcForce:
            {
                switch ( nSecondForce )
                {
                //case EnmityPlayerForce:
                case NormalMonsterForce:
                    return true;
                    break;
                }
				return false;
            }
            break;
        case NormalMonsterForce:
            {
                switch ( nSecondForce )
                {
                case NormalPlayerForce:
                case EnmityPlayerForce:
                case PetMonsterForce:
                case FightNpcForce:
                    return true;
                    break;
                }
            }
            break;
        case PetMonsterForce:
            {
                switch ( nSecondForce )
                {
                case NormalMonsterForce:
                    return true;
                    break;
                }
            }
            break;
        default:
            break;
        }

        return false;
    }
}


// ����
enum ECountry
{
    //�޹��ң�����
    country_none    = 0,
    country_sanguo     , // 3��
    country_qin        , // ��
    country_npc        , // npc
    country_human      , // ����
    country_monster    , // ����
    country_naturalness, // ��Ȼ��
    country_max        ,
};

enum EBankTradeResult
{ // ���н��׽��
    eBankTradeResultSuccess = 0     // �ɹ�
    ,eBankTradeResultBankFull       // ���Ǯ����Ǯ������
    ,eBankTradeResultPlayerNotMoney // ���û����ô��Ǯ
    ,eBankTradeResultBankNotMoney   // Ǯ��û����ô��Ǯ
    ,eBankTradeResultUpgradeMax     // Ǯ��������߼�
    ,eBankTradeResultFalied         // δ֪����
};

enum BattleType
{ // ս������
    BT_Normal   = 0,  // ��ͨ
    BT_Master   = 1,  // ����
    BT_Attacker = -1, // ����
};

enum StorageTradeResult
{ //�ֿ⽻�׽��
    eStorageTradeResultSuccess = 0, // �ɹ�
    eStorageTradeResultUpgradeMax , // �ֿ�������߼�
    eStorageTradeResultFalied       // δ֪����
};

enum EDefaultPorts 
{  //������ʹ��Ĭ�϶˿� 
    // ��������
    DP_LoginServerListenClientPort        = 20003, // LoginServerĬ�ϼ����ͻ����ǵĶ˿�
    DP_GateServerListenClientPort         = 20004, // GateServerĬ�ϼ����ͻ��˵Ķ˿�
    DP_GameServerListenGateServerPort     = 20005, // GameServerĬ�ϼ���GateServer�˿�
    DP_AccountServerListenLoginServerPort = 20006, // AccountServerĬ�ϼ���LoginServer�˿�
    DP_DatabaseServerListenGameServerPort = 20007, // DatabaseServerĬ�ϼ���GameServer�˿�
    DP_GameServerListenGMPort             = 20008, // GameServerĬ�ϼ���GM���߶˿�
    DP_GameServerListenManagerToolPort    = 20009, // GameServerĬ�ϼ��������߶˿�
    DP_GameServerListenLoginServerPort    = 20010, // GameServerĬ�ϼ���LoginServer�˿�
    DP_LogServerListenGameServerPort      = 20011, // LogServerĬ�ϼ���GameServer�˿�
    DP_GameServerListenThunderPort        = 20012, // GameServerĬ�ϼ���Ѹ�׶˿�
    DP_CenterServerListenGameServerPort   = 20013, // CenterServerĬ�ϼ���GameServer�˿�
    DP_CenterServerListenLoginServerPort  = 20014, // CenterServerĬ�ϼ���LoginServer�˿�
};

enum EMonsterType
{ // ��¼��������
    eMT_NormalMonster,   // ��ͨ����
    eMT_LeaderMonster,   // ��Ӣ����
    eMT_BossMonster,     // Boss����
    eMT_GodMonster,      // �񻰹���
    eMT_IllusionMonster, // �������
    eMT_Trap,            // �������
    eMT_Herb,            // ��ҩ
    eMT_Mine,            // ����
    eMT_Wood,            // ľͷ
    eMT_Treasure,        // ����
    eMT_Building,        // ������
    eMT_Mount,           // ���
	eMT_Pet,			 // ����
    eMT_Collision,       // �赲��
    eMT_Insect,          // ����
    eMT_Protect,         // ���͹�
    eMT_Pickup,          // ʰ��С��
    eMT_MaxCount,        //
};

//������
enum TeamMangerEnum
{
    TeamMaxCount = 6000,			//�����Ŷ�����

    TeamMaxMember = 24,				//һ�������20��
    TeamMaxManipleMember = 5,		//һ��С��5��
    TeamMaxManipleCount = 4,		//һ����4��С��
    TeamUpdateInterval = 2000,		//��Ա��Ϣ2��ˢ��һ��
    TeamUpdateToCenter = 5000,      //Ϊ�˻�����ͬ��ѹ��,��Ա��Ϣ5��ͬ��һ��
    TeamSelfUpdate = 100000,        //���鴴����ÿ60����һ���Ƿ���Ч

    ReleaseSpaceTime = 1000,    
    TeamManipleDefalutId = -1,		//Ĭ���Զ�����С��
};

enum AssignModeType                 //���ģʽ
{
    AssignMode_FreeMode = 0,        //���ɷ���
    AssignMode_Team,                //���顣��
    AssignMode_Random,              //�漴����
    AssignMode_Assign,              //���䡣��
};

enum BoultAssignTeam                //������Ʒ�����
{
    BoultAssign_None = 0,           //δѡ��
    BoultAssign_ComeDown,           //��ȡ
    BoultAssign_GiveUp,             //����
};

enum ChangeAssignModeAnswer
{
    ChangeMode_None = 0, //δѡ��
    ChangeMode_Agree,    //ͬ��
    ChangeMode_Refuse,   //�ܾ�
};
//////////////////////////////////////////////////////////////////////////////////////////

enum EItemLevel
{
    eIL_Normal = 0,     // ��ͨ
    eIL_Choiceness = 1, // ��Ʒ
    eIL_Polish = 3,     // ��Ʒ
    eIL_Nonsuch = 4,    // ��Ʒ
    eIL_Holiness,       // ��Ʒ
};

// װ����������
enum EItemElements
{
    ItemElements_Init = 0,
    ItemElements_Metal,     // ��
    ItemElements_Wood,      // ľ
    ItemElements_Water,     // ˮ
    ItemElements_Fire,      // ��
    ItemElements_Earth,     // ��

    ItemElements_End,
};

// ��������
enum EFiveElements
{
    FiveElements_None = 0,
    FiveElements_Metal = ItemElements_Metal  ,       // ��
    FiveElements_Wood  = ItemElements_Wood   ,       // ľ
    FiveElements_Water = ItemElements_Water  ,       // ˮ
    FiveElements_Fire  = ItemElements_Fire   ,       // ��
    FiveElements_Earth = ItemElements_Earth  ,       // ��

    FiveElements_End,
};

enum EItemPickLevel
{
    eIPL_Nothing = 0,            // ��Ȩ��  (��ʱ��Ȩ��, �����򿪵İ����ر��Ժ�, Ҳ�����ʰȡȨ)
    eIPL_View    = 0x1,          // �鿴Ȩ  (�Ƿ��ܲ鿴�����Ʒ����)
    eIPL_Assign  = 0x2,          // ����Ȩ  (�������жϵ�, �����Ƕӳ�����ģʽʱ, �ӳ��з���Ȩ)
    eIPL_Pick    = 0x4,          // ʰȡȨ  (�����������ʰȡ�����Ʒ��Ȩ��)
    eIPL_Hold    = 0x8,          // ӵ��Ȩ  (���������Ʒ�Ѿ�������ĳ�����,��������Ѿ������ٻ�������Ʒ,�����Ȩ��һ����ʰȡ)

    eIPL_End     = 0xF,        
};

enum PackageItemInfo
{
    MaxPackageItemCount = 48,            // ����������Ʒ
    MaxPackageAccessCount = TeamMaxManipleMember,         // �Ժ���ܻ��ǹ�������,�����ܻᵽ100��

};

enum EPetType
{
    EPT_Skill = 0,  // ���ܳ�
    EPT_Protect  ,  // ������
    EPT_Capture  ,  // �����
    EPT_Nurture  ,  // ������
    EPT_Max      ,  // ���ĳ���
};

enum ECurPetTactic
{ // ����Ĵ������
    ePetCommandAI = 0,
    ePetAttackAI,
    ePetDefendAI, // ����ģʽ �����κη�Ӧ���� ֻ������
};

enum EJiFengItemStatus
{
    EJFIS_Delete = 0, // �Ѿ���ȡ
    EJFIS_Have   = 1, // ����δ��ȡ
};

//PKϵͳ ���
/////////////////////////////////////////////////////////////// 

//#define  MinPKValue             0           // ��СPKֵ
//#define  MaxPKValue             999         // ���PKֵ
#define  PKProtectLevel         30          // zhuxincong ���ݲ߻�Ҫ�� ���ֱ����ĵ�30 PK �����ȼ�
//#define  PKKillValue            1          // ɱ��һ��PKֵΪ0����ң������50��PKֵ
//#define  PKHellPunishValue      250          // 250 ������
//#define  PKHellleaveValue       200         // 200 �뿪����
#define  PKDropItemRate         30          // ������ұ�ɱ����30%���ʵ���1��δ�󶨵���Ʒ
#define  PKModeChangeDelayed    180000      // �л���PKģʽ���ӳ� 3����
//#define  PKValueUpdateTime      3600000      // ÿ 60���Ӽ��� 1��PKֵ
#define  PKCriticalTime         1800000     // ��ģʽ����ʱ��
#define  MaxHonourSum			10000		//����������ֵ
#define  MaxLevelAttack			20000		//�뿪ս��״̬20�����������ģʽ
enum PKMode
{
    PKMode_Normal = 0,		    // ��ͨģʽ
    PKMode_Fight     ,			// PKģʽ: ȫ��ģʽ �ɹ��������ѵ��������
	PKMode_Critical  ,			// ��ģʽ
	PKMode_Guild	 ,			// PKģʽ: ����ģʽ �ɹ��������Ѻ;���֮����������
	PKMode_AttackFight,			// ����ģʽ �Ϳ�ģʽ���� 
	PKMode_AttackGuild,			// ����ģʽ �Ϳ�ģʽ���� 
	PKMode_MaxValue  ,			// 
};
/////////////////////////////////////////////////////////////////

enum PlayerShowMode
{
	PSM_ShowAll = 0,		    // ��ʾ�������
	PSM_HideAll      ,			// �����������
	PSM_ShowAmity   ,			// ��ʾ���������
	PSM_ShowAntagonize	   ,	// ��ʾ��������ҡ�
	PSM_Max,
		
};

enum EItemHoldType
{
    eIHT_Nothing = 0,            // ��������������
    eIHT_Individual,             // ���ڸ���
    eIHT_Team,                   // ���ڶ���
    eIHT_Guild,                  // ���ڹ���
    eIHT_All,                    // ����������

    eIHT_End,                    
};

enum LoginValidateType
{ //��֤��ʽ
    LVT_AccountServer,    // ͨ�� �Լ��� AccountServer
    LVT_17173Interface,   // ͨ�� 17173 �ӿ�
    LVT_ThunderInterface, // ͨ�� Ѹ�� �ӿ�
    LVT_MAX,
};

enum eDllRet
{
    e_errorID      = 0, //��0 �� û������û�
    e_succ_adult   = 1, //��1�� ��֤�ɹ�(������)
    e_IDBeLock     = 2, //��2�� ���û�����ֹ��½
    e_unlegalityID = 3, //��3 �� �û������Ϸ�
    e_errorPWD     = 5, //��5�� chk����
    e_succ_minor   = 7, //��7�� ��֤�ɹ�(δ������)
    e_fail         = 9  //��9�� ��֤ʧ��
};

enum EServerType
{
    ST_LoginServer,     // ��¼������ 
    ST_CharacterServer, // ��½ѡ��������Ϸ������
    ST_GameServer,      // ��ͼ��Ϸ������
    ST_CenterServer,    // ���ķ�����
    ST_None,
};

enum ESwitchStageReqType
{   
    SSRT_EnterGameWorld,        // ��һ�ν�����Ϸ����
    SSRT_EnterGameServerMap,    // �����ͼ������ �з���Ϊ
    SSRT_EnterToCharacterLogin, // �ص�CharacterServer
    SSRT_FlyToMap,              // ���ڷ��ͷɵ�ͼ����
	SSRT_CHANGECHANNEL			// ��Ϸ���л�����
};

enum ESwitchStageAckType
{
    SSAT_EnterWorldUseDatabaseMapInfo,         // ������Ϸʹ�����ݿ��ĵ�ͼ��Ϣ
    SSAT_EnterWorldUseMessageMapInfo,          // ������Ϸʹ����GameServerʱ��ĵ�ͼ��Ϣ
    SSAT_LocalFlyToMap,                        // �����е�ͼ
    SSAT_EnterWorldUseDatabaseMapInfoBeCorrect,// ������Ϸʹ�����ݿ��ĵ�ͼ��Ϣ ��Ҫ����( ���ݿ���˴���ĵ�ͼID)
};

enum EClientStateType
{
    CST_NoState,                                       // ��״̬
    
    CST_InLoginQueueNotSendLoginInfo,                  // �ڵ�¼�����л�û�з���¼��Ϣ������Ip port��
    CST_InLoginQueueWaitGateInfo,                      // �ڵ�¼�����з��˵�¼��Ϣ

    CST_InCharacterServerWaitTargetGameServerGateInfo, // ��ר������ѡ��������������Ϸ��CharacterServer�ȴ�Ŀ��GameServer��GateServer��Ϣ
    CST_InGameServerWaitTargetGameServerGateInfo,      // ��GameServer�ϵȴ�Ŀ��GameServer��GateServer��Ϣ
    CST_InGameServerWaitTargetCharacterServerGateInfo, // ��GameServer�ϵȴ�Ŀ��ר������ѡ��������������Ϸ��CharacterServer��GateServer��Ϣ
    
    CST_WaitLoginServer2CharacterServer,               // �ȴ�LoginServer��ר������ѡ��������������Ϸ��CharacterServer
    CST_WaitCharacterServer2GameServer,                // �ȴ���CharacterServer��Ŀ��GameServer
    CST_WaitGameServer2GameServer,                     // �ȴ�GameServer���л�
    CST_WaitGameServer2CharacterServer,                // �ȴ�GameServer��CharacterServer�л�

    CST_InCharacterServer,                             // �Ѿ�����ר������ѡ��������������Ϸ��CharacterServer
    CST_InGameServer,                                  // �Ѿ�����ר��������Ϸ��MapGameServer
    CST_InGameServerPlaying,                           // �Ѿ���ר��������Ϸ��MapGameServer����Ϸ
};

// ��������
enum EReliveType
{
    eReliveTypeBorn = 0         , // ������
    eReliveTypeCity             , // ���Ǹ���
    eReliveTypeNearPos          , // ����ĸ����
    eReliveTypeOrigin           , // ԭ��
    eReliveTypeOriginFullHpMP   , // �Ŵ���ԭ�ظ�����Ѫ��״̬
    eReliveTypeSkill            , // ���ܸ���
};


enum EElementType
{ // ��Ԫ��
    eElement_Ice,    
    eElement_Fire,   
    eElement_Thunder,
    eElement_Wind,   
    eElement_Max,
};

enum EOperationType
{ // ����ö��
    EOT_Add,
    EOT_Sub,
    EOT_Mul,
    EOT_Div,
    EOT_Set,
};

enum EBagType
{
    BT_NormalItemBag   ,
    BT_PrivateShopBag  ,
    BT_StorageBag      ,
    BT_CompoundBag     ,
    BT_IntensifyBag    ,
    BT_ReduceBag       ,
    BT_UnSoulBag       ,
    BT_LockIntensifyBag,
    BT_EquipBag        ,
    BT_MaterialBag     ,
    BT_TaskBag         ,
    BT_MountBag        ,
    BT_PetBag          ,
    BT_All             ,
};

//��ɫ�����Ķ���
enum ECharItemBagConst
{
    ITEM_BAGMAX              = 100,             // ���� Normal ��Ʒ�������
    ITEM_BAGMATERIAL_MAX     = 60,              // ���� Material ��Ʒ�������
    ITEM_BAGTASK_MAX         = 35,              // ���� Task ��Ʒ�������
    ITEM_BAG_TOTAL           = ITEM_BAGMAX + ITEM_BAGMATERIAL_MAX + ITEM_BAGTASK_MAX,

    ITEM_DISTORY             = ITEM_BAGMAX + 1, // ɾ��������Ʒ�ĺ�

    ITEM_PRIVATE_SHOP_BAGMAX = 25,              // �����̵�
    ITEM_COMPOUND_BAGMAX     = 3 ,              // �ϳɱ���
    ITEM_BAGMAX_IN           = 10,
    ITEM_PACK_OLD            = 24,
    ITEM_MOUNT_MAXCOUNT      = 6 ,              // ���������
    ITEM_PET_MAXCOUNT        = 6 ,              // ���������
    ITEM_BREEDPET_MAXCOUNT   = 1 ,              // ��ֳ���������

    //ITEM_STORAGEMAX = 10,
    //ITEM_STOREMAX = 40,
    //ITEM_SYMBOLSTONEMAX = 30,
    //ITEM_ACTIONMAX = 50,
    //ITEM_TRADEMAX = 20,
    //ITEM_MATERIALMAX = 3
};

// ��������, ����ܵ�����ö��
#define RecipeSkillNumMax   4   // ���ֻ��ѧϰ���������

enum ERecipeType
{
    ERT_CaoYao,           // ��ҩ
    ERT_ZhuBao,           // �鱦
    ERT_DuanZao,          // ����
    ERT_ZhuJia,           // ����
    ERT_GongYi,           // ����
    ERT_XunMa,            // ѱ��
    ERT_GemLevelUp,       // ��ʯ����

    ERT_Default2,         // ��ʼֵ
    ERT_Default3,         // ��ʼֵ
    ERT_Default4,         // ��ʼֵ
    ERT_CaiKuang,         // �ɿ�
    ERT_CaiYao,           // ��ҩ
    ERT_BuZhuo,           // ��׽
    ERT_BuChong ,         // ����
    ERT_CatchPet,         // ��׽����

    ERT_MaxType = 24,     // �������
};

//��������������
enum EIntonateType
{
    IntonateType_UnKnow     ,   // δ֪
    IntonateType_Item       ,   // ��Ʒ
    IntonateType_NPC        ,   // NPC
};

enum ECharAttrType
{ // �������Ե�ö��
    //һ������
    CharAttr_Strength     , // ����
    CharAttr_Agility      , // ����
    CharAttr_Stamina      , // ����
    CharAttr_Intelligence , // ����
    CharAttr_BaseAttributeMaxCount,
    //��������
    CharAttr_HPMax = CharAttr_BaseAttributeMaxCount, // HP����
    CharAttr_MPMax                  ,   // MP����
    CharAttr_AttackPhysics          ,   // ��������
    CharAttr_AttackMagic            ,   // ħ��������
    CharAttr_DefendPhysics          ,   // �������
    CharAttr_DefendMagic            ,   // ħ������
    CharAttr_AttackSpeed            ,   // �����ٶ�
    CharAttr_MoveSpeed              ,   // �ƶ��ٶ�
    CharAttr_HPRestore              ,   // HP�ָ�
    CharAttr_MPRestore              ,   // MP�ָ�
    CharAttr_Exact                  ,   // ������
    CharAttr_Dodge                  ,   // ������
    CharAttr_Critical               ,   // ������
    CharAttr_Tenacity               ,   // ����
    CharAttr_CriticalIntensity      ,   // �����˺�
    CharAttr_BackStrike             ,   // �����˺�
    CharAttr_BackStrikeResist       ,   // ��������
    CharAttr_BreakStrike            ,   // �Ƽ��˺�
    CharAttr_StabStrike             ,   // �ᴩ�˺�
    CharAttr_ElementStrike          ,   // Ԫ���˺�
    CharAttr_ToxinStrike            ,   // �����˺�
    CharAttr_SpiritStrike           ,   // �����˺�
    CharAttr_BreakResist            ,   // �Ƽ׿���
    CharAttr_StabResist             ,   // �ᴩ����
    CharAttr_ElementResist          ,   // Ԫ�ؿ���
    CharAttr_ToxinResist            ,   // ���ؿ���
    CharAttr_SpiritResist           ,   // ������
    CharAttr_AttributMaxCount       , 

    //��������
    CharAttr_Level = CharAttr_AttributMaxCount, // �ȼ�                                    
    CharAttr_Reputation           , // ��ǰ����
    CharAttr_CurGetReputation     , // ��ǰ�������                
    CharAttr_Exploit              , // ��ǰ��ѫ
    CharAttr_CurGetExploit        , // ��ǰ��ù�ѫ                                                
    CharAttr_HP                   , // Ѫ��
    CharAttr_MP                   , // ħ�� 
    CharAttr_Exp                  , // ��ǰ����
    CharAttr_ExpNotUsed           , // δʹ�õľ���
    CharAttr_SkillExp             , // ���ܾ���
    CharAttr_SkillExpNotUsed      , // δʹ�õļ��ܾ���
    CharAttr_Energy               , // ����ֵ (��������)
    CharAttr_EnergyMax            , // ����ֵ���ֵ        45+����ȼ�(ILevel)*5
    CharAttr_Vigor                , // ���� (�ɼ�����)
    CharAttr_VigorMax             , // �������ֵ 45+����ȼ�(ILevel)*5

    ///////////////////////////////////////////////////////////////////////////////////
    CharAttr_CaoYao,           // ��ҩ
    CharAttr_ZhuBao,           // �鱦
    CharAttr_DuanZao,          // ����
    CharAttr_ZhuJia,           // ����
    CharAttr_GongYi,           // ����
    CharAttr_XunMa,            // ѱ��

    CharAttr_Default1,         // ��ʼֵ
    CharAttr_Default2,         // ��ʼֵ
    CharAttr_Default3,         // ��ʼֵ
    CharAttr_Default4,         // ��ʼֵ
    CharAttr_CaiKuang,         // �ɿ�
    CharAttr_CaiYao,           // ��ҩ
    CharAttr_BuZhuo,           // ��׽
    CharAttr_BuChong ,         // ����

    CharAttr_Max = CharAttr_CaoYao + ERT_MaxType,  // ���ֵ
    //////////////////////////////////////////////////////////////////////////////////
    CharAttr_AreaRepulation       , // ˢ�µ������� ( ������ GlobalFunction.h )
    CharAttr_CanReceivePrentice   , // ��ǰ��������ͽ��
    CharAttr_MasterLevel          , // ��ǰʦ�ŵȼ�
    CharAttr_MasterValue          , // ��ǰʦ������ֵ
    CharAttr_MasterExperience     , // ��ǰ������ֵ            
    CharAttr_GiddyResist          ,
    CharAttr_StandResist          ,
    CharAttr_SlowdownResist       ,
    CharAttr_TorpidResist         ,
    CharAttr_Death                , // ����
    CharAttr_Relive               , // ����
    CharAttr_HPHeal               , // ���ƻָ���HP
    CharAttr_HPRestoreEatDrug     , // ����ҩ�ָ�
    CharAttr_Profession           , // ְҵ�ı�
    CharAttr_SkillHPCost          , // ʹ�ü��ܵ�HPCost
    CharAttr_SkillMPCost          , // ʹ�ü��ܵ�MPCost
    CharAttr_Country              , // ����
    CharAttr_CurGetExp            , 
    CharAttr_XPValue              , // ʹ�ü��ܵ�XP Cost short
    CharAttr_MountExp             , // ���ﾭ�鵱ǰ
    CharAttr_MountChangeLevel     , // �ȼ����
    CharAttr_NextNotIntonate      ,
    CharAttr_CurMountHP           ,
    CharAttr_CurMountHPMax        ,
    CharAttr_GuildContribute      , // ��ǰ�ﹱ 
    CharAttr_CurGetGuildContribute, // ��ǰ��ðﹱ
    CharAttr_MaxKillMonsterCount  , // ���ɱ������
    CharAttr_CurKillMonsterCount  , // ��ǰɱ������
    CharAttr_Challenge            , // ��ǰս����̨����
    CharAttr_MountCountLimit      , // ��ӵ����������
    CharAttr_Honour               , // ��ǰ����
    CharAttr_CurGetHonour         , // ��ǰ�������   
    CharAttr_CountryScore         , // ��ǰ��ս����
    CharAttr_CurGetCountrySocre   , // ��ǰ��ù�ս����  
    CharAttr_StorageItemGrid      , // ��ǰ����Ʒ�ֿ����
    CharAttr_StorageMountGrid     , // ��ǰ������ֿ����
    CharAttr_FreeRelive           , // ��ǰ�ܼ���Ѹ������
    CharAttr_Daoxing              , // ��ǰ����
    CharAttr_CurGetDaoxing        , // ��ǰ��õ���
    CharAttr_BasePotential        , // ��ǰʣ��Ǳ����
    CharAttr_CurGetSkillExp       , // ��ǰ��ü��ܾ���
    CharAttr_ActivePetHP          , // ��ǰ��ս����Ѫ��
    CharAttr_ActivePetCurGetExp   , // ��ǰ��ս�����þ���
	CharAttr_LostExp			  , // ������ٵľ���
};


// �����������ͻ������������Ϣ����( ����������Ϣ���ͱ��붨����һ��  )
static unsigned short GetCharAttrByRecipeType( unsigned char uchType )
{
    if ( uchType >= ERT_MaxType )
    { return 0; }

    return CharAttr_CaoYao + ( uchType - ERT_CaoYao );
}

static unsigned short GetRecipeTypeByCharAttr( unsigned char uchAttr )
{
    return uchAttr - CharAttr_CaoYao;
}

enum eAddToClenResult
{
    eResult_NotFound = 0  //�Ҳ�������
    ,eResult_RepeatedAdd  //�ظ�����
    ,eResult_Success      //��ӳɹ�
    ,eResult_SameSex      //��ͼͬ����
    ,eResult_NotEnoughAge //δ���겻�����
    ,eResult_WrongTeacher //��ʦʧ��
    ,eResult_WrongStudent //��ͽ��ʧ��
    ,eResult_Excessive    //�ػ顢�Ľ��Ѱ�ʦ
};    

enum AN_S2A_OpenClientUI_Flag
{
    AN_S2A_OpenUI_NULL               = 0,
    AN_S2A_OpenUI_StoryBook          = 1,   //�򿪹�����
    AN_S2A_OpenUI_GuildIcon          = 2,   //�򿪰���ͼ��
    AN_S2A_OpenUI_Brother            = 3,   //���ֵ�
    AN_S2A_OpenUI_ChatBULL           = 4,   //��ȫ������--
    AN_S2A_OpenUI_ChatSHOUT          = 5,   //�򿪺��� ����������Ź���
    AN_S2A_OpenUI_ChatHIGHSHOUT      = 6,   //�򿪸ߺ� ����ͬȫ��-- ��ʵ�������]
    AN_S2A_OpenUI_IntensifyUI        = 7,   //ǿ��
    AN_S2A_OpenUI_UnSoulBoundUI      = 8,   //�����
    AN_S2A_OpenUI_ReduceUI           = 9,   //�ֽ�
    AN_S2A_OpenUI_ChatParticular1    = 10,  //��С��С��1 ����vip���
    AN_S2A_OpenUI_ChatParticular2    = 11,  //��С��С��2 ����vip���
    AN_S2A_OpenUI_ChatParticular3    = 12,  //��С��С��3 ����vip���
    AN_S2A_OpenUI_ChatParticular4    = 13,  //��С��С��4 ����vip���
    AN_S2A_OpenUI_ChatParticular5    = 14,  //��С��С��5 ����vip���
    AN_S2A_OpenUI_ChatParticular6    = 15,  //��С��С��6 ����vip���
    AN_S2A_OpenUI_ChatParticular7    = 16,  //��С��С��7 ����vip���
    AN_S2A_OpenUI_ChatParticular8    = 17,  //��С��С��8 ����vip���
    AN_S2A_OpenUI_ChatParticular9    = 18,  //��С��С��9 ����vip���
    AN_S2A_OpenUI_ChatParticular10   = 19,  //��С��С��10 ����vip���
    AN_S2A_OpenUI_LockIntensifyUI    = 20,  //����ǿ��UI
    AN_S2A_OpenUI_CopyMap_WSS        = 21,  //������ɽ��������
    AN_S2A_OpenUI_BiaoShi            = 22,  //����ʦ��ѯ
    AN_S2A_OpenUI_LearnSkill         = 23,  //�򿪼���ѧϰ����
    AN_S2A_OpenUI_Intensify          = 24,  //�����ǽ���
	AN_S2A_OpenUI_Identify			 = 25,  //�򿪼�������
	AN_S2A_OpenUI_KaiGuang			 = 26,  //�򿪿������
    AN_S2A_OpenUI_ShopChangePoint    = 27,  //�򿪽𶧶һ�����
    AN_S2A_OpenUI_Decompound         = 28,  //�򿪷ֽ����
	AN_S2A_OpenUI_LotteryAwards		 = 29,  // ���佱��˵������
	AN_S2A_OpenUI_MoveStarToEquip	 = 30,  // ���ǽ��棬���Ƶ�װ����
	AN_S2A_OpenUI_MoveStarToItem	 = 31,  // ���ǽ��棬���Ƶ�����ʯ��
	AN_S2A_OpenUI_FiveElement		 = 32,  // ����
//	AN_S2A_OpenUI_RealAward			 = 33,  // ʵ�ｱ��
	AN_S2A_OpenUI_FiveElementClear	 = 34,  // ϴ����
	AN_S2A_OpenUI_SpecialRepair		 = 35,  // ��������
	AN_S2A_OpenUI_EquipUpgrade		 = 36,  // װ������
    AN_S2A_OpenUI_FiveXingChange     = 37,  //���иı�
    AN_S2A_OpenUI_FinvXinigLevel     = 38,  //�����ᴿ
	AN_S2A_OpenUI_UpgradeSkillEquip	 = 39,  // ������װ����װ������
	AN_S2A_OpenUI_ChangeSkillEquip	 = 40,  // ת����װ����װ������
	AN_S2A_OpenUI_ShowScriptGif		 = 41,	// ��ʾ����GIF�Ľ���
	AN_S2A_OpenUI_JoinFight			 = 42,	// ��ʾJoinFight�Ľ���
    AN_S2A_OpenUI_ChangeName         = 43,  //�ı�����
	AN_S2A_OpenUI_PointShop			 = 44,  //�����̳�
	AN_S2A_OpenUI_WeaponUpgrade		 = 45,	// ��������
	AN_S2A_OpenUI_MoveStarUprade	 = 46,	//����ʯ����
	AN_S2A_OpenUI_StarMaterialUpgrade= 47,	//���ǲ�������
	AN_S2A_OpenUI_MailSystem		 = 48,
	AN_S2A_OpenUI_GoldTrade			 = 49,
    AN_S2A_OpenUI_CampBattle         = 50,  //��Ӫս��
    AN_S2A_OpenUI_FiveXingTrans      = 51,  //����ת��
    AN_S2A_OpenUI_CampBattleResMove  = 52,  //��Ӫս����Դ֮�䴫��
	AN_S2A_OpenUI_IntensifyStar      = 53,  //���������ǽ���
    AN_S2A_OpenUI_LearnCaoYao        = 54,  //��ҩѧϰ����
    AN_S2A_OpenUI_LearnZhuBao        = 55,  //�鱦ѧϰ����
    AN_S2A_OpenUI_LearnDuanZao       = 56,  //����ѧϰ����
    AN_S2A_OpenUI_LearnZhuJia        = 57,  //����ѧϰ����
    AN_S2A_OpenUI_LearnGongYi        = 58,  //����ѧϰ����
    AN_S2A_OpenUI_LearnXunMa         = 59,  //ѱ��ѧϰ����
    AN_S2A_OpenUI_LearnCaiKuang      = 60,  //�ɿ�ѧϰ����
    AN_S2A_OpenUI_LearnCaiYao        = 61,  //��ҩѧϰ����
    AN_S2A_OpenUI_LearnBuZhuo        = 62,  //��׽ѧϰ����
    AN_S2A_OpenUI_HookOffline        = 63,  //NPC���߹һ�
    AN_S2A_OpenUI_MountBreed         = 64,  //���ﷱֳ����
	AN_S2A_OpenUI_DELETESTUDENT      = 65,  //ɾ��ͽ��
	AN_S2A_OpenUI_Soul				 = 66,  //װ������
	AN_S2A_OpenUI_Hole				 = 67,  //װ�����
	AN_S2A_OpenUI_Gem				 = 68,  //��Ƕ��ʯ
	AN_S2A_OpenUI_GemRemove			 = 69,  //��ж��ʯ
	AN_S2A_OpenUI_GemReplace		 = 70,  //��ж��ʯ
	AN_S2A_OpenUI_Purple			 = 71,  //�̽�
	AN_S2A_OpenUI_ReOpenLight		 = 72,  //�̽��¯
	AN_S2A_OpenUI_Maintain			 = 73,  //��ֵ
	AN_S2A_OpenUI_Amulet			 = 74,  //�������ɫ
	AN_S2A_OpenUI_GemLevelUp		 = 75,  //��ʯ����
	AN_S2A_OpenUI_Charm				 = 76,  //��������
	AN_S2A_OpenUI_Recycle			 = 77,  //װ������
	AN_S2A_OpenUI_Melt				 = 78,  //װ������
	AN_S2A_OpenUI_CREATEGUILD        = 79, //�������
	AN_S2A_OpenUI_MaintainCross		 = 80,  //�缶��ֵ
	AN_S2A_OpenUI_XSJLevelUp		 = 81,  //ϴʯ������
	AN_S2A_OpenUI_ApplyJoinGuild		 = 82,  //�������
	AN_S2A_OpenUI_LevelOneGuildShop		 = 83,  //1������̵�
	AN_S2A_OpenUI_LevelTwoGuildShop		 = 84,  //2������̵�
	AN_S2A_OpenUI_LevelThreeGuildShop	 = 85,  //3������̵�
	AN_S2A_OpenUI_LevelFourGuildShop	 = 86,  //4������̵�
	AN_S2A_OpenUI_LevelFiveGuildShop	 = 87,  //5������̵�
	AN_S2A_OpenUI_LevelSixGuildShop		 = 88,  //6������̵�
    AN_S2A_OpenUI_PetStorage		     = 89,  //�������ֿ�
	AN_S2A_OpenUI_EquipqualityIdentify   = 90,  //װ��Ʒ�ʼ���
	AN_S2A_OpenUI_StallQuery		     = 91,	//��̯��ѯ
    AN_S2A_OpenUI_QuestCommitItem        = 92,	//�����ύ��Ʒ
    AN_S2A_OpenUI_PetBreed               = 93,	//���ﷱֳ
	AN_S2A_OpenUI_PetUp					 = 94,  //ʹ�ó�����������
	AN_S2A_OpenUI_PetStudy               = 95,  //���＼��ѧϰ
	AN_S2A_OPenUI_PetMaterialUp          = 96,  //������������
	AN_S2A_OpenUI_CreateFamily		 = 97,	// ��������
	AN_S2A_OpenUI_ApplyJoinFamily	 = 98,  // ����������
	AN_S2A_OpenUI_ZhujiangBianshen	 = 99,	// ��������
	AN_S2A_OpenUI_Achievement		 = 100,	// �ɾ�
	AN_S2A_OpenUI_ChangeCountry		 = 101, // �ı����
	AN_S2A_OpenUI_ShopCenter		 = 102, // �̳�
	AN_S2A_OpenUI_ItemTrade			 = 103, // ��Ʒ����			 
	AN_S2A_OpenUI_CaoYao			 = 104,  //��ҩ����
	AN_S2A_OpenUI_ZhuBao			 = 105,  //�鱦����
	AN_S2A_OpenUI_DuanZao			 = 106,  //�������
	AN_S2A_OpenUI_ZhuJia			 = 107,  //���׽���
	AN_S2A_OpenUI_GongYi			 = 108,  //���ս���
	AN_S2A_OpenUI_XunMa				 = 109,  //ѱ�����
	AN_S2A_OpenUI_CaiKuang			 = 110,  //�ɿ����
	AN_S2A_OpenUI_CaiYao			 = 111,  //��ҩ����
	AN_S2A_OpenUI_ShiTu				 = 112, //zhuxincong ������ʦͽ
	AN_S2A_OpenUI_ShiTu2			 = 113, //zhuxincong ������ʦͽ
	AN_S2A_OpenUI_Title				 = 114,
	AN_S2A_OpenUI_ZhuJianUp			 = 115, //����ͼ���ϳ�
	AN_S2A_OpenUI_TransferStar		 = 116, //ת�ǽ���
	AN_S2A_OpenUI_UnBind			 = 117, //������
	AN_S2A_OpenUI_MountStrengthen	 = 118,
	AN_S2A_OpenUI_CountryBaseInfo	 = 119,
	AN_S2A_OpenUI_AskPresent		 = 120,
	AN_S2A_OpenUI_MoveCountry		 = 121,
	AN_S2A_OpenUI_MaterialBag		 = 122, //���ϱ���
	AN_S2A_OpenUI_TaskBag			 = 123, //���񱳰�
    AN_S2A_OpenUI_RandAttribute		 = 124, //��ϴ�������
	AN_S2A_OpenUI_PetComPose		 = 125,
	AN_S2A_OpenUI_GuildChangeName    = 126,
	AN_S2A_OpenUI_QuestEntrust		= 127,
	AN_S2A_OpenUI_Hunting			 = 128, //��������
	AN_S2A_OpenUI_Card				 = 129, //����
	AN_S2A_OpenUI_MountMoveStar		 = 130,
	AN_S2A_OpenUI_AutoAttack		= 131,
	AN_S2A_OpenUI_Task				= 132,
	AN_S2A_OpenUI_ActivityList		= 133,
};

//��UI��Դ
enum AN_S2A_OpenClientUI_Type
{
    OpenClientUIType_Other = 0,     //
    OpenClientUIType_Quest    ,     // ����

    OpenClientUIType_Max
};

enum EIdleSubAction
{
    // Server��Client����һ��
    CS_SubAction_Normal,
    CS_SubAction_SitDown,        
    CS_SubAction_FightAction,
    CS_SubAction_Embrace,     // ӵ��
    CS_SubAction_Restore,     // ��ҩ����  
};

//��ͨ�������ĵ�ʱ��
enum ENormalAttackCostTime
{
    Fast_NormalAttackCostTime = 667
    ,Normal_NormalAttackCostTime = 1333
    ,Slow_NormalAttackCost = 2000
};

enum EItemBagProcessResult
{
    //����ɹ�
    ierr_Success = 0             // �����ɹ�
    ,ierr_notallitempushed       // �������е���Ʒ�������ˡ�ֻ������һ����
    ,ierr_NotHaveTargetCountItem // û���ƶ���Ŀ����Ʒ
    ,ierr_reachmaxcountofaitem   // �ﵽĳ����Ʒ�������
    ,ierr_ItemNotExist           // ��Ʒ������
    ,ierr_erritemid              // �������ƷID
    ,ierr_PackIsFull             // �����Ѿ�����
    ,ierr_CanNotOverlap          // �����ص�
    ,ierr_ItemIsLocked           // ��Ʒ�Ѿ�����
    ,ierr_IndexOutOfBagSize      // �±곬��������С
    ,ierr_RepeatedBigId          // BigId�ظ�
    ,ierr_PackItemPointerNull    // ʵ�ʱ�������ָ��Ϊ��
    ,ierr_ErrorItemGuid          // ������Ʒguid
    ,ierr_unknown
};

enum EHotKeyBagType
{ //��������
    //BagTypeMouse,           //����ϵĵ���
    BagTypePack,           
    //BagTypeEquip,           //װ���������������������ߣ�
    //BagTypeUse,             //����Ʒ��������Ҫ��Restore�ࣩ
    //BagTypeMaterial,        //ԭ�ϱ����������ϳ�ʹ�ã�
    //BagTypeReel,            //���ᱳ������������������Ʒ���缼�ܣ���ʯ��
    //BagTypeMedal,           //ѫ�±�������
    //BagTypeOther,           //�������û�з������Ʒ(���������)
    BagTypeSkill,             //���ܱ���
    //BagTypeSymbolstone,     //��ʯ����
    //BagTypeBaseaction,      //������������
    //BagTypeCommunityaction, //�罻����
    //BagTypeSocialaction,    //��Ⱥ����
    //BagTypeStore,           //�ֿ�
    //BagTypeTrade,           //���ױ���
    BagTypeHotkey,            //�ȼ�����
    //BagTypeProduceItem,     //���챳��(���ԭ�ϵģ�
    //BagTypeUpgradeEquip,    //���챳��(����װ����ħ������;װ��)
    BagTypeFunction,
    BagTypeActionUI,
    BagTypeMountSkill,        //���ﱳ������
    BagTypePetSkill,          //���ﱳ������
	BagTypeExpressionAction,  //���鶯��
	BagTypeHeroSkill,		  //�������ܱ���
    BagTypeMax,               //���ı�������
};

enum ProduceItemPos
{ //��������е�λ��
    ItemPos_Material1,
    ItemPos_Material2,
    ItemPos_Material3,
    ItemPos_Tool
};

//Ԫ�ض���
//enum enumElement
//{        
//    ELEMENT_FIRE = 0,
//    ELEMENT_ICE, 
//    ELEMENT_CLOUD,
//    ELEMENT_THUNDER,
//    ELEMENT_LIGHT,
//    ELEMENT_DARK,
//    eElement_Max
//};
//

enum enumCharStorage
{ //��ɫ�ֿ�Ķ���
    STORAGE_ITEMGRID_MAX  = 150,                     // ÿ���ֿ���������
    STORAGE_MOUNTGRID_MAX = 6 ,                      // ����ֿ���������
    PAGESIZE = 30,                                   // ÿҳ�ĸ�����Ŀ
    STORAGE_MAX = 30,                                // ������Ϸ�������ֿ���Ŀ
    STORAGE_ITEMMAX_IN_GRIDS = 99,                   // ÿ���ֿ�ÿ���������洢��Ʒ��Ŀ
    STORAGE_MAX_PAGE = STORAGE_ITEMGRID_MAX / PAGESIZE, // �ֿ�����ҳ��
};

enum enumPwd
{
    PWD_OF_ITEM = 20,
    PWD_OF_STORAGE = 20
};         

enum EHeadPic
{    //���ͷ��
    HeadPic_Male = 0,   //����ͷ��
    HeadPic_Female = 1, //Ů��ͷ��
};

enum ECharFightStatus
{
    PeaceStatus = 0, //��ƽģʽ    
    FightStatus = 1, //ս��ģʽ
};

enum ESitStatus
{
    StandStatus = 0, //վ��
    SitStatus = 1,   //����
};

enum EBodyStatus
{
    BodyStatusType_Max = 32,
    /*
    BodyStatus_Max = 4
    ,BodyStatus_Poison    = 1
    //�ж�
    //�߼�Ч��:ÿ���Ѫ
    //��ʾЧ��:��Ѫ��ʾΪ��ɫ
    //����Ѫ�Ƿ�̶��������в�ͬ���ж��̶�
    //,BodyStatus_Chaos
    //���ң��������ܿ��ƣ���ɫ�����Ҷ������ܹ���
    ,BodyStatus_Frost    = 1<<1            
    //����
    //�߼�Ч��:�ƶ������������������ٶ�ȫ�����룩
    //��ʾЧ��:������ɫ��Ϊ����ɫ            
    ,BodyStatus_Stone    = 1<<2
    //ʯ��
    //�߼�Ч��:�����ƶ������ܹ���
    //��ʾЧ��:������ʾ����ʯ��
    ,BodyStatus_Sleep    = 1<<3
    //��˯
    //�߼�Ч��:�����ƶ������ܹ��������������״̬
    //��ʾЧ��:�ɷ��л�˯������ͷ����ʾZZZZZ
    */        
};

enum EBodyType
{ //��ɫ��������
    BODYTYPE_MICRO = 0, //΢��
    BODYTYPE_MINI     , //С��
    BODYTYPE_MIDDLE   , //����
    BODYTYPE_LARGE    , //����
    BODYTYPE_HUGE     , //����
    BODYTYPE_MAX      ,
};

enum EDefColor
{ //װ����Ч����ɫ
    COLOR_RED = 0,                        // ��ɫ
    COLOR_BLUE,                            // ��ɫ
    COLOR_TEAL,                            // ��ɫ                    
    COLOR_PURPLE,                        // ��ɫ
    COLOR_YELLOW,                        // ��ɫ
    COLOR_ORANGE,                        // ��ɫ
    COLOR_GREEN,                        // ��ɫ
    COLOR_PINK,                            // �ۺ�ɫ
    COLOR_GRAY,                            // ��ɫ
    COLOR_LIGHTBLUE,                    // ����ɫ
    COLOR_DARKGREEN,                    // ����ɫ
    COLOR_BROWN,                        // ��ɫ
};

//��Ʒ���ָı�(�ϳɣ�������ǿ��)
enum enumItemProcess
{
    ITEMTYPE_INTENSIFY = 18,    //ǿ������
};

enum EOwnAttribute
{
    EOA_show_repute_name = 0,
    EOA_Max
};

enum PublicMessageType
{
    PMT_TEACHER,
    PMT_STUDENT,
};

enum EScriptType
{
    ST_NPC = 0               , // NPC����
    ST_QUEST                 , // ���񴥷�
    ST_LEVELUP               , // �ȼ�����
    ST_MONSTER               , // ���ﴥ��
    ST_USE_ITEM              , // ʹ�õ��ߴ���
    ST_INTO_AREA             , // �������鴥��
    ST_LEAVE_AREA            , // �뿪���鴥��
    ST_REAL_TIME             , // ��ʵʱ�䴥��
    ST_GAME_TIME             , // ��Ϸʱ�䴥��
    ST_ONLINE                , // ���ߴ���
    ST_CREATE_CHAR           , // �������
    ST_CHAR_DEAD             , // �������
    ST_GRAPHICCODE_CHECKRIGHT, // ���ͼ����֤��ɹ�
    ST_DelayTime             , // �ӳ�ʱ��ִ�нű�
    ST_OFFLINE               , // ���ߴ���
    ST_CANCELQUEST           , // ȡ������ʱ����
    //    ST_BANGUILD              , // �������˵�ʱ�����
    ST_GAMESTAGE             , // ��������
    ST_CHALLENGE             , // ������̨�ű�
    ST_MARRIAGE              , // ���ű�
    ST_PKBATTLE				 , //��Ӫ����
    ST_TEAMBATTLER           , // С�ӻ�ս�ű�
    ST_LEAVEGUILD            , // �뿪����
    ST_GUIDEQUEST            , // ָ������
    ST_TEACHERSTUDENT        , // ʦͽ�ű�
    ST_NPC_DEAD              , // Npc��������
	ST_CHAR_KILLCHAR		,	//���ɱ���ж���Ӫ���
	ST_ACHIEVE				 , //��ɳɾ�ʱ����
	ST_CARD_ACHIEVE			 , //��ɿ��Ƴɾ�ʱ����
	ST_ScriptSleep			,  //����нű�������������ֹ��
    ST_MAX                   , // ���
    ST_UNKNOW = -1           , // δ֪
};

enum GamePropertyEnum
{
    HP,
    MP,
    LEVEL,
};

//״̬�к�����
enum EStatusNegativeType
{
    SNT_GIDDY       ,   // ѣ��
    SNT_STAND       ,   // ����
    SNT_SLOWDOWN    ,   // ����
    SNT_TORPID      ,   // ��Ĭ
    SNT_HURT        ,   // �����˺�
    SNT_ATTR        ,   // ������������
    SNT_AFRAID      ,   // �־�
    SNT_SLEEP       ,   // ˯��
    SNT_DISTORTION  ,   // ����
    SNT_FROST       ,   // ����
    SNT_SNEERAT     ,   // ����
    SNT_FORGET      ,   // ����
    SNT_ILLIBERALITY,   // ����
    SNT_ATONY       ,   // ����
    SNT_ALLURE      ,   // �Ȼ�
    SNT_MaxCount    ,   // 
};

enum EInstantMovingType
{
    IMT_None,               // ��˲��
    IMT_Forward,            // ��ǰ˲��
    IMT_Backwards,          // ���˲��
    IMT_TargetBack,         // ˲�Ƶ�����
};

enum ETrafficType
{
    TT_Land,  // ½��
    TT_Water, // ˮ��
    TT_Sky,   // ����
};

enum EBoolValue
{
    BV_NeedTellClientCharInfo    = 1,
    BV_NotNeedTellClientCharInfo = 0,
    BV_NeedUseMessageMapInfo     = 1,
    BV_NotNeedUseMessageMapInfo  = 0,
    BV_LocalFlyMap               = 1,
    BV_NotLocalFlyMap            = 0,
    BV_SendMessage               = 1,
    BV_NotSendMessage            = 0,
    BV_FullHp                    = 1,
    BV_NotFullHp                 = 0,
    BV_SendUpAttrInfo            = 1,
    BV_NotSendUpAttrInfo         = 0,
    BV_ForSaveDb                 = 1,
    BV_NotForSaveDb              = 0,
};

enum EExitType
{
    ET_ExitGame,              // �����˳�
    ET_SwitchGameServer,      // �л�������
    ET_ReturnCharacterServer, // ���ؽ�ɫ��¼������
    ET_BeKick,                // �������߳���Ϸ �߱��� ������
	ET_SystemBeKick,          // ��ϵͳ�����߳���Ϸ �߱��� ������
    ET_ExceptionKick,         // �쳣�߳���Ϸ   ������ ��������
};

enum EAckEnterWorld
{
    Server_Ok = 0,
    Server_Busy = 1,
    Server_Full = 2,
    Server_LoginInfoError = 3,
};

enum ESaveType
{
    EST_None,          // ��״̬
    EST_ExitWorld,     // �˳���Ϸ�����ʱ��
    EST_ExitGameServer,// �˳�һ̨��������ʱ��
    EST_Time,          // ��ʱ
};

enum EBattleType
{
    BATTLE_ATTACK = -1,
    BATTLE_NORMAL = 0,
    BATTLE_GUARD  = 1
};

enum ETeamPosition
{
    ETP_None,          // ��
    ETP_Leader,        // �ӳ�
    ETP_ManipleLeader, // С�ӳ�
    ETP_Member,        // ��Ա
};

enum EPlatformQueryType
{
    ECT_XinShouCard       = 0, // ���ֿ�                 ( û�� 0, ����� 11, 1(ԭ�������ֿ�), 2(�µ����ֿ�) )
    ECT_17173Card         = 1, // 17173��Ȩ��            ( û�� 0, ����� 11, �� 22            )
    ECT_ZhiZunCardLevel   = 2, // ���𿨵ȼ�             ( 1, 2, 3, 4, 5 ,6                    )
    ECT_ZhiZunVipGift     = 3, // ����Vip�����          ( û�� 0, ����� 11, 1, 2, 3, 4, 5 ,6 )
    ECT_HuiGuiGift        = 4, // ����һع����         ( û�� 0, ����� 11, 1, 2             )
    ECT_ChongZhiFirstGift = 5, // �״γ�ֵ���           ( û�� 0, ����� 11, �� 22            )
    ECT_ChongZhiBackGift  = 6, // �����ͳ�ֵ�����ȼ��� ( û�� 0, ����� 11, 1, 2, 3, 4       )
};

enum ESpecialTaskType
{
	ESTT_Intensify,			//ǿ������
	ESTT_GemUp,				//��ʯ��������
	ESTT_Hole,				//���
	ESTT_EquipGem,			//��Ƕ
	ESTT_EquipStar,			//����
	ESTT_KillPlayer,		//ɱ�ж����(���Ǳ��������)
	ESTT_KillWei,			//ɱκ��
	ESTT_KillShu,			//ɱ���
	ESTT_KillWu,			//ɱ���
	ESTT_MAX
};

/*! \brief ��Ҵ��ڷ�����ϵͳ�е�״̬
*
*  
*
*/
enum  AntiAddictionState{
    enumAntiAddictionStateNormal    = 0,  //!< ����ʱ��
    enumAntiAddictionStateTired     = 1,  //!< ƣ��ʱ��
    enumAntiAddictionStateRest      = 2,  //!< ������ʱ��
};


//////////////////////////////////////////////////////////////////////////
// �ṹ��
#pragma pack(push,1)


// ��Ϸ����
struct SGameStage
{
    SGameStage()
    {
        bIsRun = true;
    }

    bool bIsRun;
    unsigned long  ulStageId;     
    unsigned short usPlayerCount; // ��ǰ�������������
};

// ��Ϸ����Op
struct SGameStageOp 
{
    enum OpType
    {
        OT_Update,
        OT_Remove,
    };

    enum EGameStageInfoType
    {
        GSIT_MapSetting,
        GSIT_RunStage,
    };

    char op;
    char gameStageInfoType; 
    SGameStage gs;
};

#define SHOP_ITEM_MAXCOUNT    100           // �̵������Ʒ����
struct SShopItem
{ // ����
    SShopItem():nId(-1), nCurCount(0), nMaxCount(0), nBasePrice(0),
        dwSellPrice(0), dwBuyPrice(0) {}

    int   nId;              // ��ƷID
    int   nCurCount;        // ��ǰ����
    int   nMaxCount;        // ��Ʒ�������
    int   nPerCount;        // ÿ�γ��۵��������
    int   nBasePrice;       // ԭʼ�۸�
    DWORD dwSellPrice;      // ���ۼ۸�
    DWORD dwBuyPrice;       // �չ��۸�
    unsigned char costType; // �۸�����
    unsigned short costItemID; // ��Ʒ����ʱ,��Ҫ����ƷID
    bool  bIsBound;         // �Ƿ��
};

struct SChannelInfo
{
    char szChannelName[MAX_NAME_STRING];
	uint8 chChannelStatus;
    unsigned long nServerId;
};

struct SServerInfo
{
    char nServerType;
    unsigned long nServerId;
};

struct SLoginInfoBase
{
    SLoginInfoBase()
    {
        memset( this, 0, sizeof(*this));
    }

    char         szIP[IP_LENGTH+1];          // IP
    int          nAccountID;                 // �˺�ID
    unsigned int LoginTime;                  // ��½ʱ��
    char         szAccount[MAX_NAME_STRING]; // ��½�˺�
	__int64      Sessionkey;
   // char         SessionKey[40+1];           // SessionKey
    //char         Password[50];               // ����
    //char         Seed[50];                   // ����
	char         szMac[MAC_LENGTH];			 // mac ��ַ
    int8         isWallow;                   // �Ƿ����
    bool operator == (SLoginInfoBase &other) { return Sessionkey = other.Sessionkey /*strcmp(SessionKey,other.SessionKey)==0*/;}
    bool operator == (__int64 other/*const char* other*/) { return Sessionkey == other/*strcmp(SessionKey,other)==0*/; }
};

struct SBurthenBase
{
    unsigned int nCurrentPlayerCount;
    unsigned int nMaxPlayerCount;
    unsigned int nGateCount;
};

struct SStageReqInfo
{
    SStageReqInfo()
    {
        bHaveInvalidInfo = false;
        nServerId        = ErrorUnsignedLongID;
    };

    unsigned long nServerId;
    unsigned long nMapId;
    float         fX;
    float         fY;
    float         fDir;
    bool          bHaveInvalidInfo;
};

struct SRankManager
{
    SRankManager()
    {
        memset(this,0,sizeof(SRankManager));
    }

    struct SRank
    {
        BYTE first;
        BYTE second;

        void WriteRank(CDataChunkWriter *w);
        void ReadRank(BYTE* bybuff,DWORD dwsize);            
    };
    void clear()
    {
        memset(this,0,sizeof(SRankManager));
    }

    void Write(BYTE idx,BYTE value)
    {
        int nIndex = idx/2;
        if ( nIndex<0 || nIndex>=16)
            return;
        
        if (idx%2)
            rankArray[nIndex].second = value;
        else
            rankArray[nIndex].first = value;
    }

    BYTE Read(WORD idx)
    {
        int nIndex = idx/2;
        if ( nIndex<0 || nIndex>=16)
            return 0;
        if (idx%2)
            return rankArray[idx/2].second;
        else
            return rankArray[idx/2].first;
    }

    SRank rankArray[16];

    void WriteRankManager(CDataChunkWriter *w);
    void ReadRankManager(BYTE* bybuff,DWORD dwsize);
};

struct SElement
{ // Ԫ������
    unsigned short item_stAtt;
    unsigned short item_stDef;
    unsigned short exec_stAtt;
    unsigned short exec_stDef;
    unsigned short status_stAtt;
    unsigned short status_stDef;
    unsigned short final_Att;
    unsigned short final_Def;

    SElement()
    {
        item_stAtt = 0;
        item_stDef = 0;
        exec_stAtt = 0;
        exec_stDef = 0;
        final_Att = 0;
        final_Def = 0;
        status_stAtt = 0;
        status_stDef = 0;
    }
    void UpdateFinal_Att( )
    {
        final_Att = item_stAtt+status_stAtt+exec_stAtt;
        if (final_Att < 0)
        {
            final_Att = 0;
        }
    }
    void UpdateFinal_Def( )
    {
        final_Def = item_stDef+status_stDef+exec_stDef;
        if (final_Def < 0)
        {
            final_Def = 0;
        }
    }
    unsigned short GetFinal_Def( )
    {
        if (final_Att < 0)
        {
            final_Att = 0;
        }
        return final_Def = item_stDef+status_stDef+exec_stDef;
    }
    unsigned short GetFinal_Att( )
    {
        if (final_Def < 0)
        {
            final_Def = 0;
        }
        return     final_Att = item_stAtt+status_stAtt+exec_stAtt;
    }

    void WriteElement(CDataChunkWriter *w);
    void ReadElement(BYTE* bybuff,DWORD dwsize);
}; 

struct SAreaRepulation
{
    enum EConstDefine
    {
        ECD_Max_Value = 500,
    };

    SAreaRepulation()
    {
        Reset();
    };

    short nMapID;
    int nCurrentReputation;
    int nMaxReputation;

    void Reset()
    {
        nMapID             = -1;
        nCurrentReputation = 0;
        nMaxReputation     = ECD_Max_Value;
    }
};

// �ƺ�����
class TitleData
{
public:
    TitleData() : m_ustTitleID( 0 ), m_n64AcquireTime( 0 ), m_nActiveTime( 0 ){ }
    TitleData( unsigned short ustTitleID, __int64 n64AcquireTime, unsigned int nActiveTime )
        : m_ustTitleID( ustTitleID ), m_n64AcquireTime( n64AcquireTime ), m_nActiveTime( nActiveTime ) { }

    bool operator == ( const TitleData& xData ) { return m_ustTitleID == xData.GetTitleID(); }
    bool operator == ( unsigned short ustTitleID ) { return m_ustTitleID == ustTitleID; }
    friend bool operator == ( const TitleData& xLeft, const TitleData& xRight ){ return xLeft.GetTitleID() == xRight.GetTitleID(); }
    friend bool operator ==( const TitleData& xData, unsigned short ustTitleID ) { return xData.GetTitleID() == ustTitleID; }

    unsigned short GetTitleID() const  { return m_ustTitleID; }
    __int64 GetAcquireTime() const     { return m_n64AcquireTime; }
    unsigned int GetActiveTime() const { return m_nActiveTime; }

    void SetTitleID( unsigned short ustValue ) { m_ustTitleID = ustValue; }
    void SetAcquireTime( __int64 n64Value )    { m_n64AcquireTime = n64Value; }
    void SetActiveTime( unsigned int nValue )  { m_nActiveTime = nValue; }


    // �ж��Ƿ��Ѿ�����
    bool IsPassLimitTime()
    {
        if ( m_nActiveTime == 0 )       //  = 0 ��Զ������
        { return false; }

        TimeEx xStartTime( m_n64AcquireTime );
        TimeSpan xTimeSpan( static_cast< DWORD >( m_nActiveTime ) );
        xStartTime += xTimeSpan;

        return TimeEx::IsPassCurrentTime( xStartTime.GetTime() );
    }

private:
    unsigned short m_ustTitleID;        // �ƺ�ID
    __int64 m_n64AcquireTime;           // �ƺŻ�õ�ʱ��
    unsigned int m_nActiveTime;         // �ƺŵ���Чʱ��  = 0 ������Ч
};

// ʦ������
class MasterData
{
public:
    MasterData() : m_uchMasterLevel( 1 ), m_dwMasterValue( 0 ){}

    unsigned char GetMasterLevel() const { return m_uchMasterLevel; }
    DWORD GetMasterValue() const { return m_dwMasterValue; }

    void SetMasterLevel( unsigned char uchValue ) { m_uchMasterLevel = uchValue; }
    void SetMasterValue( DWORD dwValue ) { m_dwMasterValue = dwValue; }
private:
    unsigned char m_uchMasterLevel;     // ʦ�ŵȼ�
    DWORD m_dwMasterValue;              // ����ֵ
};

// ��ƷColdDown����
#define MAX_RESTORE_COUNT 200
#define MAX_SAVERESTORE_COUNT 50
struct SColdDown
{
    SColdDown()
    {
        m_ustType = 0;
        m_dwStartTime = 0;
        m_dwPeriod = 0;
    }

    bool IsEmpty() { return m_ustType == 0 || m_dwStartTime == 0 || m_dwPeriod == 0; }

    unsigned short m_ustType;
    DWORD          m_dwStartTime; // ��ʼʱ��
    DWORD          m_dwPeriod;    // ����
};

struct SCharHeroInfo		//�������������ӵ����Խṹ
{
	SCharHeroInfo()
	{
		memset(this,0,sizeof(SCharHeroInfo));
	}
	int32		hpMax            ; // HP����
	int32		mpMax            ; // MP����
	int32		attackPhysics    ; // ��������
	int32		attackMagic      ; // ħ�������� 
	int32		defendPhysics    ; // �������
	int32		defendMagic      ; // ħ������
	int32		attackSpeed      ; // �����ٶ�
	int32		moveSpeed        ; // �ƶ��ٶ�
	int32		hpRestore        ; // HP�ָ�
	int32		mpRestore        ; // MP�ָ�
	int32		exact            ; // ������
	int32		dodge            ; // ������
	int32		critical         ; // ������ 
	int32		tenacity         ; // ����  
	int32		criticalIntensity; // �����˺�
	int32		backStrike       ; // �����˺�
	int32		backStrikeResist ; // ��������
	int32		breakStrike      ; // �Ƽ��˺�
	int32		stabStrike       ; // �ᴩ�˺�
	int32		elementStrike    ; // Ԫ���˺�
	int32		toxinStrike      ; // �����˺�
	int32		spiritStrike     ; // �����˺�
	int32		breakResist      ; // �Ƽ׿���
	int32		stabResist       ; // �ᴩ����
	int32		elementResist    ; // Ԫ�ؿ���
	int32		toxinResist      ; // ���ؿ���
	int32		spiritResist     ; // ������
};

struct SCharBaseInfo
{
    struct SCharAptotic
    {
        SCharAptotic()
        { memset( this, 0, sizeof( SCharAptotic ) ); }

        int8   szCharacterName[ dr_MaxPlayerName ]; // ����
        uint8  ucSex;                               // �Ա�
        uint16 usProfession;                        // ��ɫְҵ
        uint8  ucHeadPic;                           // ��ɫ��ͷ��
        uint8  ucCountry;                           // ����        
        int8   szYearName[dr_MaxYearName];          // �����������
        uint8  byYear;                              // ������
        uint8  byMonth;                             // ������
        uint8  byDay;                               // ������
    };

    struct SCharLiveInfo
    {
        SCharLiveInfo()
        {
            memset( this, 0, sizeof( SCharLiveInfo) );
            for ( int i=0; i<MAX_AREAREPULATION_COUNT; ++i )
            { xArea[i].Reset(); }
			hero_id = INVALID_HERO_ID;
			//dwMapID = INVALID_MAP_ID;
			//PrePosition = D3DXVECTOR3(0,0,0);
			dwKillPlayerSum =0;
			dwKillPlayerWeekSum =0;
			uchPosition = 0;
            ConsumeScore = 0;
            ChangeName = 0;
        }

        uint16          ustLevel;                             // �ȼ�
        uint32          dwMoney;                              // ��Ϸ��Ǯ
        uint32          jiaoZi;                               // ����(����)
        uint32          reputation;                           // ����ֵ
        uint32          exploit;                              // ��ѫֵ
        uint32          honour;                               // ����ֵ
        uint32          battleScore;                          // ս������
        uint32          dwCountryScore;                       // ��ս����
        uint32          jinDing;                              // ��(Ԫ��)
        uint32          jinPiao;                              // ��Ʊ(���)
        uint32          dwHelpFlag;                           // ������ʾ
        uint32          nHighShoutCount;                      // ����ĺ�������
        int             nHp;                                  // Ѫ��
        int             nMp;                                  // ħ��
        int             nXp;                                  // XPֵ
        int64           dwExp;                                // ��ǰ����
        int64           dwExpNotUsed;                         // δʹ�õľ���
        uint32          dwSkillExp;                           // ���ܾ���        
        uint32          dwSkillExpNotUsed;                    // δʹ�õļ��ܾ���
        uint16          ustSkillExpForSkillID;                // Ҫ�����ļ���ID
        uint16          activity;                             // ���� (��������)
        uint16          activityMax;                          // �������ֵ 45+����ȼ�(ILevel)*5
        uint16          vigor;                                // ���� (�ɼ�����)
        uint16          vigorMax;                             // �������ֵ 45+����ȼ�(ILevel)*5
        uint32          dwOnlineTime;                         // ���������ʱ��( ��λ; ���� )
        uint32          dwRewardItemInfo;                     // �������ʱ����ȡ��������Ϣ( ������32��, 32λ ÿһλ����ֵ 0 = û����ȡ, 1 = �Ѿ���ȡ�� )
        
        int16           nCurrentTitleID;                      // ��ǰ�ƺ�
        uint16          nCountryTitle;                        // ���ҳƺ�( �������Ҫ���������ݿ� )
        TitleData       xTitleData[MAX_TITLE_COUNT];          // �ƺ��б�
        SAreaRepulation xArea[MAX_AREAREPULATION_COUNT];      // ��������
        MasterData      xMasterData;                          // ʦ������
        
        SColdDown       xItemColdDown[MAX_SAVERESTORE_COUNT]; // ��Ʒ��colddownʱ��

        uint16          nRecipeSkillNum;                      // ����ܸ���
        uint16          nSkillPoint[ ERT_MaxType ];           // �������������������

        uint8           ucMountCount;                         // �������
        uint8           ucNormalBagSize;                      // ʵ����ͨ�����Ŀ��Ÿ���
        uint8           ucMaterialBagSize;                    // ʵ�ʲ��ϱ����Ŀ��Ÿ���
        uint8           nStorageItemGrid ;                    // �ֿ���Ʒ��������
        uint8           nStorageMountGrid;                    // �ֿ������������

        uint32          nRecordReliveTime;                    // ��¼��󸴻��ʱ��
        uint8           nFreeReliveCount ;                    // ��¼ÿ����Ѹ������

        uint32          nSysDoubleExpTime;                    // ϵͳ���͵�˫������ʱ��
        uint32          nItemDoubleExpTime;                   // ����˫������ʱ��

        uint32          daoxing;                              // ����
        uint16          basePotential;                        // ��ǰǱ����
        uint16          baseAssignValue[EBaseAttr_MaxSize];   // �Ѿ������Ǳ����
		uint16          hero_id;                              //���������ID
		char            TPHJRank;                             //����̫ƽ�þ��ĵȼ�

		//DWORD			dwMapID;							  //����̫ƽ�þ�֮ǰ��MapID
		//D3DXVECTOR3		PrePosition;						  //����̫ƽ�þ�֮ǰ������ 
		uint32			dwKillPlayerSum;					  //���ɱ������
		uint32			dwKillPlayerWeekSum;				  //��ұ���ɱ���� ÿ�������賿����

		uint8			uchPosition;						  //����ڹ����е�ְλ Ĭ��ֵΪPosition_None=0 ��ʾ��ְλ
        uint32          ConsumeScore;                         //LYH�̳ǻ���
		int			    ChangeName;
    }; 
    
    SCharBaseInfo()
    {
        memset( &aptotic,  0, sizeof( SCharAptotic ));
        memset( &liveinfo, 0, sizeof( SCharLiveInfo ));

        for ( int i = 0; i < MAX_AREAREPULATION_COUNT; ++i )
        {
            liveinfo.xArea[i].Reset();
        }
    };

    SCharAptotic  aptotic;
    SCharLiveInfo liveinfo;
    SBaseProperty baseProperty; // [ ������� ]
};

struct SSocietyRelation 
{ // ��ϵ
    SSocietyRelation()
    {
        memset( szPlayer, 0, sizeof(szPlayer) );
        Stype = 0;
    }
    DWORD Stype;                      // ����ϵ
    char  szPlayer[dr_MaxPlayerName]; // ����
};

struct SCharItem
{
    enum EConstDefine
    {
        EConstDefine_BaseRandMaxCount       = 7, // �����������
        EConstDefine_PurpleRandMaxCount     = 3, // ��ɫ�������
        EConstDefine_GemHoleMaxCount        = 4, // ������Ƕ��λ
        EConstDefine_SuitRandMaxCount       = 1, // ��װ�ľ���������� ������װ�����Ժ�
		EConstDefine_HasBaseRanded		    = 0xffff, // �������޸����������ʱ�����ֵ,��ʾ�Ѽ�������
        EConstDefine_TalismanRandMaxCount   = 7, // ������������
    };

    enum EEquipEvolveConstDefine
    {
        EEquipEvolve_SoulStampAddition  = 50, // װ�����̼ӳ�
    };

    enum ELevel
    {
        EL_Min    = 0 ,
        EL_Notice = 12 , // ����12��ȫ������
        EL_StarMax= 18, // װ�����18��	//ԭ����10�����ڸĳ�18
        EL_Max    = 18,
    };

    enum EUseType
    {
        EUT_None,
        EUT_AutoUse,
        EUT_Other,
    };

    enum EEquipDataFlagType
    {
        EEquipDataFlagType_SoulStamp = 1 << 0, // �Ƿ��������
        EEquipDataFlagType_Bounded   = 1 << 1, // �Ƿ��
        EEquipDataFlagType_Lock      = 1 << 2, // �Ƿ�����
    };

	//��������̫����...ɸѡ��
    struct SItemBaseInfo
    {
        SItemBaseInfo() { memset( this, 0, sizeof(SItemBaseInfo) ); }

        uint16  ustItemID                      ; // ��ƷID
        __int64 nOnlyInt                       ; // ��Ʒ����ΨһID
        int16   stPacketIdx                    ; // ������λ��
        uint16  ustItemCount                   ; // ����
        uint32  value1                         ; // ��ֵ  װ��������������value1�ĺ�8λ   ����ֱ���������ֵ
        __int64 n64UseTime                     ; // ��Ʒʹ�õĵ���ʱ��lo
        uint32  nLeftTime                      ; // ��Ʒʹ�õ�ʣ��ʱ��( ���ô洢�����ݿ�, ÿ�ν�ɫ���߼���һ��, ���ܿͻ��˼���, ʱ����ͬ, ȡ�����ı���ʱ��᲻ͬ )
        uint32  value2                         ; // ��ֵ�����Ըı䣬��HP,MP
        uint8   useType                        ; // ʹ������ 0 ������ 1 �����Զ�ʹ�� 2 �Ժ���
        char    szCreaterName[dr_MaxPlayerName]; // ӵ���ߵ�����
        uint8   flag                           ; // ��־λ �ο� EEquipDataFlagType
    };
/*
		ITEMTYPE_RESTORE = 0    , // �ָ�ҩƷ
		ITEMTYPE_WEAPON         , // ����----------------
		ITEMTYPE_ARMOUR         , // ����----------------
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
*/
    struct SEquipData
    {   // ��Ʒ����չ���� װ��ʱ����������������� ����ʱ��������ĸ���
        // ÿ�����ߵ�����ֻ����7��Ŀ  special0 ~ special6 (uint8 )
        // ��Բ�ͬ�ĵ��ߣ���ͬ�ĵ����в�ͬ������˵��
        // (����, �·�, Ь��, ����, ͷ��, ��Ʒ )
        // ���������ֵΪ0��ʾ����Ŀ��Ч!!
        SEquipData() { memset( this, 0, sizeof(SEquipData) );unBindCount = 0xffff; }

        float  usHP           ;                                 // װ���;ö�
        int32  usHpMax        ;                                 // װ���;ö����ֵ
        uint16 baseRands  [ EConstDefine_BaseRandMaxCount   ];  // ��ɫ�����������
        uint16 purpleRands[ EConstDefine_PurpleRandMaxCount ];  // ��ɫ�����������
        uint16 suitRands  [ EConstDefine_SuitRandMaxCount   ];  // ������װ�����������
        uint16 gemIds     [ EConstDefine_GemHoleMaxCount    ];  // Ƕ�ױ�ʯ
        uint8  gemHoleCount   ;                                 // װ�������
        uint8  ucLevel        ;                                 // װ��ǿ���Ǽ�
        uint8  quality        ;                                 // װ��Ʒ�� ��һ������ɫƷ�� ������������;
        uint8  element        ;                                 // �����ĸ�
		uint16 unBindCount	  ;									// װ�����Ĵ��� -1��ʾ���޽�� 0��ʾ�޷���� ������ʾ������ Ĭ��ֵΪ-1 ���ں������ļ����жԱ�
		float  fScore		  ;									// װ������
		uint32 ustEquipType	  ;                                 // װ������ ���Զ���
		uint8  ucSoulPer	  ;									// װ�����̼ӳɰٷֱ�
    };

    struct STalismanData
    {   // ������չ����
        STalismanData() { memset( this, 0, sizeof(STalismanData) ); }

        uint8  quality        ;                                 // ����Ʒ�� 1��Ʒ��2��Ʒ��3��Ʒ��4���5����
        uint8  level          ;                                 // �����ȼ�
        uint32 daoxing        ;                                 // ����
        uint32 nimbus         ;                                 // ����
        uint32 nimbusMax      ;                                 // �������ֵ
        uint16 nimbusRestore  ;                                 // �����ظ�
        int64  exp            ;                                 // ������
        uint16 talismanRands[EConstDefine_TalismanRandMaxCount];// ��������
        uint8  randAttrNumber ;                                 // ��������������
    };

	struct SPetEquipData
	{
		SPetEquipData() { memset( this, 0, sizeof(SPetEquipData) ); isTimeEnd = false;}
		int						Strength;//����
		int						Agility;//����
		int						Stamina;//����
		int						Intelligence;//����
		uint16					iEquipLevelReq;//�ȼ�����
		bool					isTimeEnd;//װ���Ƿ��Ѿ���Ч���� Ĭ��Ϊfalse
	};

    struct SStorageInfo
    {   
        SStorageInfo() { memset( this, 0, sizeof(SStorageInfo) ); }

        bool  bIsLocked;     // ( �����֪��Ϊɶ�������жϿͻ�����ס���ò����ı��� )
        int32 nStorageNpcId; // NPCid �ֿ�洢֮��
    };

    struct SLockInfo
    {
        SLockInfo() { memset( this, 0, sizeof(SLockInfo) ); }

        __int64 n64UnLockTime;   // �����ĵ���ʱ��( ����״̬ �� ����״̬���ֵΪ 0 )
        uint32  nUnLockLeftTime; // ����ʣ��ʱ��( ����������, �������ͻ�����ʾ )
    };

    SCharItem()
    {
        memset( this, 0, sizeof(SCharItem) );
		equipdata.unBindCount = 0xffff;
        bCanUse = true;
    }

    const bool operator==( const SCharItem& stItem ) const
    {
        //if( memcmp( this, &stItem, sizeof(SCharItem) ) == 0 )
          //  return true;
        if (itembaseinfo.ustItemID == stItem.itembaseinfo.ustItemID && itembaseinfo.nOnlyInt == stItem.itembaseinfo.nOnlyInt)
            return true;
        return false;
    }

    const bool operator!=( const SCharItem& stItem ) const
    {
        return !( *this == stItem );
    }

    const bool Included( const SCharItem& stItem ) const 
    {
        if( itembaseinfo.ustItemID == stItem.itembaseinfo.ustItemID )
        {
            if( itembaseinfo.ustItemCount >= stItem.itembaseinfo.ustItemCount )
                return true;
        }
        return false;
    }

    unsigned short GetItemID()   { return itembaseinfo.ustItemID; }
    void           SetItemID( unsigned short ustValue ){ itembaseinfo.ustItemID = ustValue; }
    unsigned short GetItemCount(){ return itembaseinfo.ustItemCount; }
    void           SetItemCount( unsigned short ustValue ) { itembaseinfo.ustItemCount = ustValue; }
    __int64        GetItemGuid() { return itembaseinfo.nOnlyInt; }
    bool           IsEmpty()     { return ( itembaseinfo.ustItemID == InvalidLogicNumber || itembaseinfo.nOnlyInt == InvalidLogicNumber || itembaseinfo.ustItemCount == 0 ); }
    void           Clear()       { itembaseinfo.ustItemID = InvalidLogicNumber; itembaseinfo.nOnlyInt = 0; itembaseinfo.ustItemCount = 0; }
    void           SetItemGuid( __int64 n64Value ) { itembaseinfo.nOnlyInt = n64Value; }

    // ����������װ���������� ����װ������Ч
    void          SetElements( unsigned char chValue ) { itembaseinfo.value1 = ( itembaseinfo.value1 & 0xFFFFFF00 ) | chValue; }
    unsigned char GetElements() { return static_cast< unsigned char >( itembaseinfo.value1 & 0xFF ); }

    // ������װ�ͼ�����װ
    void SetSuitLevel( unsigned char chValue )       // ������װװ��ǿ���ȼ�
    { 
        if ( chValue == 0 )
        {
            itembaseinfo.value1 = ( itembaseinfo.value1 & 0xFFFF00FF ); 
        }
        else
        {
            itembaseinfo.value1 = ( itembaseinfo.value1 & 0xFFFF00FF ) | ( chValue << 8 ); 
        }
    }     
    unsigned char GetSuitLevel() { return static_cast< unsigned char >( ( itembaseinfo.value1 & 0xFF00 ) >> 8 ); }       // �����װװ��ǿ���ȼ�

    //װ���Ǽ�
    void SetStarLevel( bool bRandom, uint8 nStarLevel )
    {
        if (nStarLevel == 0 ||  nStarLevel > EL_StarMax)
        { return; }

        if (bRandom)
        { equipdata.ucLevel = theRand.rand16() % (nStarLevel + 1); }
        else
        { equipdata.ucLevel = nStarLevel; }
    }

    bool IsOverdue( bool bSetLeftTime = false );
    bool IsSoulStamp() { return _HAS_FLAG( itembaseinfo.flag, EEquipDataFlagType_SoulStamp); } // �Ƿ��������
    bool IsBounded()   { return _HAS_FLAG( itembaseinfo.flag, EEquipDataFlagType_Bounded  ); } // �Ƿ񱻰�
    bool IsLock()      { return _HAS_FLAG( itembaseinfo.flag, EEquipDataFlagType_Lock     ); } // �Ƿ�����

    unsigned char GetSoulStampAddition() { return IsSoulStamp() ? EEquipEvolve_SoulStampAddition : 0 ; } //��Ʒ�������̺󣬻������������Ե�50%

    void SetSoulStamp( bool bValue ) 
    {
        if ( bValue )
        { _SET_FLAG( itembaseinfo.flag, EEquipDataFlagType_SoulStamp ); }
        else
        { _CLS_FLAG( itembaseinfo.flag, EEquipDataFlagType_SoulStamp ); }
    }

    void SetBounded( bool bValue )
    {
        if ( bValue )
        { _SET_FLAG( itembaseinfo.flag, EEquipDataFlagType_Bounded ); }
        else
        { _CLS_FLAG( itembaseinfo.flag, EEquipDataFlagType_Bounded ); }
    }

    void SetLock( bool bValue )
    {
        if ( bValue )
        { _SET_FLAG( itembaseinfo.flag, EEquipDataFlagType_Lock ); }
        else
        { 
            _CLS_FLAG( itembaseinfo.flag, EEquipDataFlagType_Lock ); 
            xLockInfo.n64UnLockTime = 0;
            xLockInfo.nUnLockLeftTime = 0;
        }
    }

	//�Ƿ�������װ��������Լ���(ǰ����װ��)
	bool HasBaseRanded() const
	{
		return equipdata.baseRands[0] != EConstDefine_HasBaseRanded;
	}

    bool IsPassUnLockTime( bool bSetLeftTime = false );

    void    SetUnLockTime( __int64 n64Time ) { xLockInfo.n64UnLockTime = n64Time; }
    __int64 GetUnLockTime() { return xLockInfo.n64UnLockTime; }

    void   SetUnLockLeftTime( uint32 nLeftTime ) { xLockInfo.nUnLockLeftTime = nLeftTime; }
    uint32 GetUnLockLeftTime() { return xLockInfo.nUnLockLeftTime; }

    void Write( CDataChunkWriter *w);
    void Read( BYTE* bybuff,DWORD dwsize );

    void ReadItemBaseInfo(ReadData inP,int nSize);
    void ReadEquipInfo   (ReadData inP,int nSize);
    void ReadTalismanInfo(ReadData inP,int nSize);
    void ReadStorgeInfo  (ReadData inP,int nSize);
    void ReadLockInfo    ( ReadData inP,int nSize );
	void ReadPetEquipInfo( ReadData inP,int nSize );

    bool          bCanUse       ;     // ֻ��Ϊ�߼�������Ϊ�洢
    SItemBaseInfo itembaseinfo  ;
    SEquipData    equipdata     ;
    STalismanData talismandata  ;
	SPetEquipData petequipdata	;
    SStorageInfo  storageinfo   ;
    SLockInfo     xLockInfo     ;
};

inline bool SortItemID( const SCharItem& left, const SCharItem& right )
{
    return ( left.itembaseinfo.ustItemID < right.itembaseinfo.ustItemID) ? true : false;
}


// �ķ�Ӱ�켼��״̬����ö�� ��g_szSkillStatusAttrTypeһ��
enum ESkillStatusAttrType
{
    SkillAttr_None = 0        ,
    SkillAttr_Strength        ,   //����
    SkillAttr_Agility         ,   //����
    SkillAttr_Stamina         ,   //����
    SkillAttr_Intelligence    ,   //����
    SkillAttr_HPDamage        ,   //�����˺�
    SkillAttr_HPRestore       ,   //��������
    SkillAttr_AOECharNum      ,   //��������
    SkillAttr_PhysicsAttack   ,   //������
    SkillAttr_MagicAttack     ,   //��������
    SkillAttr_PhysicsDefend   ,   //�������
    SkillAttr_MagicDefend     ,   //��������
    SkillAttr_Exact           ,   //����
    SkillAttr_Dodge           ,   //����
    SkillAttr_Critical        ,   //������
    SkillAttr_CriticalIntensity,  //�����˺�
    SkillAttr_Tenacity        ,   //����
    
    StatusAttr_Strength        ,   //����
    StatusAttr_Agility         ,   //����
    StatusAttr_Stamina         ,   //����
    StatusAttr_Intelligence    ,   //����
    StatusAttr_HPDamage        ,   //�����˺�
    StatusAttr_HPRestore       ,   //��������
    StatusAttr_PhysicsAttack   ,   //������
    StatusAttr_MagicAttack     ,   //��������
    StatusAttr_PhysicsDefend   ,   //�������
    StatusAttr_MagicDefend     ,   //��������
    StatusAttr_Exact           ,   //����
    StatusAttr_Dodge           ,   //����
    StatusAttr_Critical        ,   //������
    StatusAttr_CriticalIntensity,  //�����˺�
    StatusAttr_Tenacity        ,   //����
    StatusAttr_SuckDamage      ,   //�����˺�

	//����¼ӵģ��ͷ�������
	SkillAttr_AddHPMax		  ,		//HP����
	SkillAttr_AddMPMax		  ,		//MP����

    SkillAttr_MaxSize          ,   
};

static char* (g_szSkillStatusAttrType[]) =
{
    "SkillAttr_None"            ,
    "SkillAttr_Strength"        ,   //����
    "SkillAttr_Agility"         ,   //����
    "SkillAttr_Stamina"         ,   //����
    "SkillAttr_Intelligence"    ,   //����
    "SkillAttr_HPDamage"        ,   //�����˺�
    "SkillAttr_HPRestore"       ,   //��������
    "SkillAttr_AOECharNum"      ,   //��������
    "SkillAttr_PhysicsAttack"   ,   //������
    "SkillAttr_MagicAttack"     ,   //��������
    "SkillAttr_PhysicsDefend"   ,   //�������
    "SkillAttr_MagicDefend"     ,   //��������
    "SkillAttr_Exact"           ,   //����
    "SkillAttr_Dodge"           ,   //����
    "SkillAttr_Critical"        ,   //������
    "SkillAttr_CriticalIntensity" , //�����˺�
    "SkillAttr_Tenacity"        ,   //����

    "StatusAttr_Strength"        ,   //����
    "StatusAttr_Agility"         ,   //����
    "StatusAttr_Stamina"         ,   //����
    "StatusAttr_Intelligence"    ,   //����
    "StatusAttr_HPDamage"        ,   //�����˺�
    "StatusAttr_HPRestore"       ,   //��������
    "StatusAttr_PhysicsAttack"   ,   //������
    "StatusAttr_MagicAttack"     ,   //��������
    "StatusAttr_PhysicsDefend"   ,   //�������
    "StatusAttr_MagicDefend"     ,   //��������
    "StatusAttr_Exact"           ,   //����
    "StatusAttr_Dodge"           ,   //����
    "StatusAttr_Critical"        ,   //������
    "StatusAttr_CriticalIntensity",  //�����˺�
    "StatusAttr_Tenacity"        ,   //����
    "StatusAttr_SuckDamage"      ,   //�����˺�

	//����¼ӵģ��ͷ�������
	"SkillAttr_AddHPMax"		,	//HP����
	"SkillAttr_AddMPMax"		,	//MP����
};

struct SCharXinFa
{ // ��������ķ��Ķ���
    SCharXinFa()
    { Reset(); }

    void Reset()
    {
        memset(this, 0, sizeof(SCharXinFa));
    }

    void Write( CDataChunkWriter* w );
    void Read ( BYTE* buffer,DWORD size );

    unsigned short nXinFaID     ;
    unsigned char  nXinFaLevel  ;
};

struct SCharSkill
{ // ������ϼ��ܵĶ���
    SCharSkill()
    { Reset(); }

    void Reset()
    {
        memset(this, 0, sizeof(SCharSkill));
        bAvailable    = true;
    }

    void write( CDataChunkWriter* w );
    void read ( BYTE* buffer,DWORD size );
    
    unsigned short ustSkillID;      // ����ID
    unsigned char  stSkillLevel;    // �ȼ�
    DWORD          dwCurSkillExp;   // ���ܾ���
    bool           bAvailable;      // �ͻ���ʹ��

    unsigned int   nColdTime;       // ʣ�����ȴʱ��
};

struct SMountItem
{
    enum EConstDefine
    {
        MICD_MaxSkillCount = 12,        // ���＼�ܸ���
        MICD_InitiativeSkillIndex = 0,  // �������ܲۿ�ʼ����
        MICD_PassiveSkillIndex    = 6,  // �������ܲۿ�ʼ����

        MICD_MountBreedGeneration = 0,  // ���ﷱֳ����
        MICD_MountBreedQuality    = 2,  // ���ﷱֳƷ��
		MICD_MountMaxLevel		  = 12, // �������ǿ���ȼ�
    };

    struct SBaseInfo
    {
        SBaseInfo()
        { Reset(); }
        
        void Reset()
        {
            memset( this, 0, sizeof( SBaseInfo));
        }

        void ResetAttibute()
        {
            memset( baseAttribute,     0, sizeof(baseAttribute     ));
            memset( aptitudeAttribute, 0, sizeof(aptitudeAttribute ));
            memset( potentialAttribute,0, sizeof(potentialAttribute));
            memset( currentAttribute,  0, sizeof(currentAttribute  ));
        }

        SBaseInfo& operator= ( const SBaseInfo& v )
        {
            if ( this != &v )
            {
                id           = v.id;
                guid         = v.guid;
                isActive     = v.isActive;
                level        = v.level;
                exp          = v.exp;
                hp           = v.hp;
                hpMax        = v.hpMax;
                savvy        = v.savvy;
                generation   = v.generation;
                nextId       = v.nextId;
                quality      = v.quality;
                nPotentialPoint = v.nPotentialPoint;
                memcpy( baseAttribute, v.baseAttribute, sizeof(float) * EBaseAttr_MaxSize );
                memcpy( aptitudeAttribute, v.aptitudeAttribute, sizeof(float) * EBaseAttr_MaxSize );
                memcpy( potentialAttribute, v.potentialAttribute, sizeof(float) * EBaseAttr_MaxSize );
                memcpy( currentAttribute, v.currentAttribute, sizeof(float) * EBaseAttr_MaxSize );
                strncpy_s( szName, sizeof(szName), v.szName, sizeof(szName)-1 );
            }
            return *this;
        }

        void UpdateCurrentAttribute()
        {
            for ( int i=0; i<EBaseAttr_MaxSize; ++i)
            { 
                //�ɹ�ʽ: ���ﵱǰ������ֵ = �����ʼ������ֵ + ���ȼ�-1��*����ʼ����^0.16/(12.5^0.16)+�ɳ��ʣ�* ��ֵ 
                //currentAttribute[i] = baseAttribute[i] + (level-1) * ( pow( (float)baseAttribute[i], (float)0.16) / pow( (float)12.5, (float)0.16) + growRate ) * aptitudeAttribute[i];

                //�¹�ʽ: ���ﵱǰ������ֵ = �����ʼ������ֵ + ���ȼ�-1�� + �����Ǳ��
                //currentAttribute[i] = baseAttribute[i] + (level-1) + potentialAttribute[i];

				//�¹�ʽ1: ���ﵱǰ������ֵ = �����ʼ������ֵ + ǿ�������Ǳ��
				currentAttribute[i] = baseAttribute[i] + potentialAttribute[i];
				if (currentAttribute[i] <= 0.0f)
					currentAttribute[i] = baseAttribute[i];
            }
        }

        void Write( CDataChunkWriter* w );
        void Read( BYTE* szBuff,DWORD nSize );

        char        szName[ dr_MaxPlayerName ];     // ����
        uint16      id;                             // ��������ID
        int64       guid;                           // ��Ʒ����ΨһID
        uint8       isActive;                       // �Ƿ񱻼���
        uint16      level;                          // �ȼ�/ǿ���ȼ�
        int64       exp;                            // ����
        int16       hp;                             // ��������
        uint16      hpMax;                          // �����������ֵ
        uint16      savvy;                          // ����
        uint8       generation;                     // ����
        uint16      nextId;                         // ��һ����ID
        uint8       quality;                        // Ʒ��

        int		       nPotentialPoint;                // �ɷ���Ǳ����
        float          baseAttribute[EBaseAttr_MaxSize];        // ������ʼ����
        float          aptitudeAttribute[EBaseAttr_MaxSize];    // ��������
        float          potentialAttribute[EBaseAttr_MaxSize];   // �ѷ���Ǳ����/ǿ���ӳɵ�Ǳ����
        float          currentAttribute[EBaseAttr_MaxSize];     // ��ǰ����
    };
    
    struct SSkillInfo
    {
        SSkillInfo()
        { memset( this, 0, sizeof( SSkillInfo)); }

        bool              AddSkill    ( unsigned short skillId, unsigned short skillLevel = 1, uint8 beginIndex = 0 );
        bool              ReplaceSkill( unsigned short skillId, unsigned short skillLevel, int nIndex );
        bool              RemoveSkill ( unsigned short skillId );
        const SCharSkill* GetSkill    ( unsigned short skillId );
        int               GetCurrentSkillCount();
        void Reset();

        void Write( CDataChunkWriter* w );
        void Read( BYTE* szBuff, DWORD nSize );

        SCharSkill skills[MICD_MaxSkillCount]; // ����
        int16      initiativeSkillNumber;      // �����������ܲ۸���
    };

    struct LockInfo
    {   
        LockInfo() : bIsLocked( false ), n64UnLockTime( 0 ), nUnLockLeftTime( 0 ){}

        void Write( CDataChunkWriter* w );
        void Read( BYTE* szBuff, DWORD nSize );

        bool bIsLocked;         // ��Ʒ�Ƿ����
        __int64 n64UnLockTime;  // �����ĵ���ʱ��( ����״̬ �� ����״̬���ֵΪ 0 )
        uint32 nUnLockLeftTime;
    };


    unsigned short GetMountID() const { return baseInfo.id; }
    __int64 GetMountGuid() const { return baseInfo.guid; }
    const char* GetMountName() const { return baseInfo.szName; }

    bool IsPassUnLockTime( bool bSetLeftTime = false );
    bool IsLock() { return xLockInfo.bIsLocked; }
    void SetLock( bool bValue )
    {
        xLockInfo.bIsLocked = bValue;
        xLockInfo.n64UnLockTime = 0;
    }
    __int64 GetUnLockTime() { return xLockInfo.n64UnLockTime; }
    void SetUnLockTime( __int64 n64Time ) { xLockInfo.n64UnLockTime = n64Time; }

    void SetUnLockLeftTime( uint32 nLeftTime ) { xLockInfo.nUnLockLeftTime = nLeftTime; }
    uint32 GetUnLockLeftTime() { return xLockInfo.nUnLockLeftTime; }

    bool IsCanBreed()
    {
        if ( baseInfo.generation != MICD_MountBreedGeneration )
        { return false; }

        if ( baseInfo.quality < MICD_MountBreedQuality )
        { return false; }

        return true;
    }

    void Write( CDataChunkWriter* w);
    void Read( BYTE* bybuff,DWORD dwsize );

    SBaseInfo  baseInfo;
    SSkillInfo skillInfo;
    LockInfo xLockInfo;
};



struct SPetItem
{
    enum EPetConstDefine
    {
        PetDefine_MaxSkillCount     = 12, // ������
		
		PetEquip_Begin				= 0,
		PetEquip_One				= 0,
		PetEquip_Two				= 1,
		PetEquip_Three				= 2,
		PetEquip_Four				= 3,
		PetEquip_Fine				= 4,
		PetEquip_MaxSum				= 5, // ����װ����װ������
    };

    struct SBaseInfo
    {
        SBaseInfo()
        { Reset(); }

        void Reset()
        { memset( this, 0, sizeof( SBaseInfo)); }

        void ResetAttibute()
        {
            memset( baseAttribute,     0, sizeof(baseAttribute     ));
            memset( aptitudeAttribute, 0, sizeof(aptitudeAttribute ));
            memset( potentialAttribute,0, sizeof(potentialAttribute));
        }

        void Write( CDataChunkWriter* w );
        void Read( BYTE* szBuff,DWORD nSize );

        char    szName[ dr_MaxPlayerName ];     // ����
        uint32  petId;                          // ID
        uint16  itemId;                         // ��Ӧ��ƷID
        int     petType;                        // ��������
        int64   guid;                           // ��Ʒ����ΨһID
        uint8   isActive;                       // �Ƿ��ս
        uint16  level;                          // �ȼ�
        uint8   quality;                        // Ʒ��
        uint16  takeLevel;						// Я���ȼ�
        uint8   aptitudeLevel;                  // ���ʵȼ�
        uint8   attackType;						// ս�����
        uint16  battleValue;                    // ս����
        uint8   sex;							// �Ա�
        uint8   characterize;					// �Ը�
        int64   exp;                            // ����
        int32   daoxing;                        // ����
        int     hp;                             // ����ֵ
        uint8   loyalty;						// ���ֶ�
        uint32  duration;						// ����
        uint8   savvy;                          // ����
        uint8   bone ;							// ����
        uint8   isShowGrow;                     // �Ƿ���ʾ�ɳ���
        uint8   growStar;                       // �ɳ����Ǽ�
        uint16  growRate;                       // �ɳ���
        uint8   phyle;							// ����
        uint8   element;						// ����
        uint8   breedNum;                       // ��ֳ����
        uint8   generation;                     // ��������
        uint32  regenerateTime;                 // ��ս��ȴʱ��
        uint16  lastRealizeSkillLevel;          // ��һ�������ܵȼ�

        uint16	nPotentialPoint;                            // �ɷ���Ǳ����
        uint16  baseAttribute       [EBaseAttr_MaxSize];    // ������ʼ����
        uint16  potentialAttribute  [EBaseAttr_MaxSize];    // �ѷ���Ǳ����
        uint16  aptitudeAttribute   [EBaseAttr_MaxSize];    // ������������

		uint32	PetModeID;						// ������ģ��ID
		__int64 n64ModeUseTime;					// ����ģ�͵���ʱ�� ���ں��޸�PetModeID ģ��Ϊ0
		SCharItem PetEquip[PetEquip_MaxSum];	// �������ϵ�װ������ װ�����޸���� ֻӰ������

        uint16  GetCurrentBaseAttr( uint8 attrType );       // ��ǰ��������
        uint16  GetCurrentAptitude( uint8 attrType );       // ��ǰ��������
        uint32  GetFightAttribute ( uint8 attrType );       // ����ս������

		uint32	GetPetNewModeID();
		void	SetPetModeID(uint32 ModeID,__int64 EndTime);

		bool    IsExitesEquip();
    };

    struct SSkillInfo
    {
        SSkillInfo()
        { memset( this, 0, sizeof( SSkillInfo)); }

        bool              AddSkill    ( unsigned short skillId, unsigned short skillLevel = 1 );
        bool              ReplaceSkill( unsigned short skillId, unsigned short skillLevel, int nIndex );
        bool              RemoveSkill ( unsigned short skillId );
        const SCharSkill* GetSkill    ( unsigned short skillId );
        int               GetCurrentSkillCount();
        void Reset();

        void Write( CDataChunkWriter* w );
        void Read( BYTE* szBuff, DWORD nSize );

        SCharSkill skills[PetDefine_MaxSkillCount];  // ����
        uint8      initiativeSkillNumber;            // �����������ܲ۸���
    };

    struct SLockInfo
    {   
        SLockInfo() : bIsLocked( false ), n64UnLockTime( 0 ), nUnLockLeftTime( 0 ){}

        void Write( CDataChunkWriter* w );
        void Read( BYTE* szBuff, DWORD nSize );

        bool   bIsLocked;         // ��Ʒ�Ƿ����
        int64  n64UnLockTime;     // �����ĵ���ʱ��( ����״̬ �� ����״̬���ֵΪ 0 )
        uint32 nUnLockLeftTime;
    };

    struct SBreedInfo
    {
        int64   targetGuid    ;     // �������GUID
        uint32  targetCharDBID;     // �Է����DBID
        uint8   targetQuality ;     // �Է�����Ʒ��
        int64   commitTime    ;     // �ύʱ��

        void Clear() { memset( this, 0, sizeof( SBreedInfo )); }
        void Write( CDataChunkWriter* w );
        void Read( BYTE* szBuff, DWORD nSize );
    };

    int     GetPetID      () const { return baseInfo.petId;     }
    int64   GetPetGuid    () const { return baseInfo.guid ;     }
    const char* GetPetName() const { return baseInfo.szName;    }

    bool IsPassUnLockTime( bool bSetLeftTime = false );
    bool IsLock() { return xLockInfo.bIsLocked; }
    void SetLock( bool bValue )
    {
        xLockInfo.bIsLocked = bValue;
        xLockInfo.n64UnLockTime = 0;
    }
    int64 GetUnLockTime() { return xLockInfo.n64UnLockTime; }
    void  SetUnLockTime( int64 n64Time ) { xLockInfo.n64UnLockTime = n64Time; }

    void   SetUnLockLeftTime( uint32 nLeftTime ) { xLockInfo.nUnLockLeftTime = nLeftTime; }
    uint32 GetUnLockLeftTime() { return xLockInfo.nUnLockLeftTime; }

    void Write( CDataChunkWriter* w);
    void Read( BYTE* bybuff,DWORD dwsize );

    SBaseInfo  baseInfo;
    SSkillInfo skillInfo;
    SBreedInfo breedInfo;
    SLockInfo  xLockInfo;
};

struct SCharSkills
{
    SCharSkills()
    { }

    void write(CDataChunkWriter* w);
    void read(BYTE* bybuff,DWORD dwsize);

    SCharXinFa xinfa[ More_iMaxXinFa      ];
    SCharSkill skill[ More_iMaxSkillKnown ];
	SCharSkill heroSkill[More_iMaxHeroSkill];
};
 
enum EEquipPartType
{
    EEquipPartType_Helmet            , // ͷ��
    EEquipPartType_Armour            , // ����
    EEquipPartType_Glove             , // ����
    EEquipPartType_Shoe              , // Ь��
    EEquipPartType_Weapon            , // ������(ֻ��ʾ��λ��)
    EEquipPartType_WeaponMinor       , // ������
    EEquipPartType_Badge             , // ����
    EEquipPartType_Ring1             , // ��ָ1
    EEquipPartType_Ring2             , // ��ָ2
    EEquipPartType_Bangle1           , // ����1
    EEquipPartType_Bangle2           , // ����2
	EEquipPartType_Shoulder          , // ���
//    EEquipPartType_Manteau           , // ����
    EEquipPartType_Necklace          , // ����
    EEquipPartType_Sash              , // ����
    EEquipPartType_LeaderCard        , // ���ſ�
    EEquipPartType_Amulet            , // �����
    EEquipPartType_AecorativeGoods   , // װ�ε���Ʒ
    EEquipPartType_AecorativeClothing, // װ�ε��·�
	EEquipPartType_Trousers			 , // ����
    EEquipPartType_MaxEquitPart      , // ����װ������
};

struct SCharVisual
{
    enum EShowFlagType
    {
        EShowFlagType_Aecpratove = 1 << 0, // �Ƿ���ʾʱװ
        EShowFlagType_Helmet     = 1 << 1, // �Ƿ���ʾͷ��
        EShowFlagType_Signature  = 1 << 2, // �Ƿ���ʾ����
		EShowFlagType_Hero		 = 1 << 3, // �Ƿ���ʾ������̬
		EShowFlagType_RankTitle  = 1 << 4, // �Ƿ���ʾ����
    };

    uint16    hairId;                                   // ͷ��ģ��Id
    uint16    faceId;                                   // ����ģ��Id    
	uint8	  defaultModelIndex;						// ����ģ������
    uint8     showFlag;                                 // EShowFlagType
    float     fModelPercent;                            // ģ�����Űٷֱ�
    SCharItem equipitem[ EEquipPartType_MaxEquitPart ]; // ����װ���ĵ���
    SCharItem talisman;                                 // ����

    SCharVisual()
    {
        hairId        = 0;
        faceId        = 0;
        showFlag      = 0;
        fModelPercent = 1.0f;
		defaultModelIndex = 0;
    }

    SCharItem* GetVisual( uint8 part )
    {
        if ( part >= EEquipPartType_MaxEquitPart)
        { return NULL; }
        return &equipitem[ part ];
    }

    SCharItem* GetVisualArray()
    { return equipitem; }

    bool IsShowAecorative() 
    { return _HAS_FLAG( showFlag, EShowFlagType_Aecpratove); }  // �Ƿ���ʾʱװ

    bool IsShowHelmet()
    { return _HAS_FLAG( showFlag, EShowFlagType_Helmet); }      // �Ƿ���ʾͷ��

    bool IsShowSignature()
    { return _HAS_FLAG( showFlag, EShowFlagType_Signature); }   // �Ƿ���ʾ����

	bool IsShowHero()
	{ return _HAS_FLAG( showFlag, EShowFlagType_Hero); }		// �Ƿ���ʾ������̬

	bool IsShowRankTitle()
	{ return _HAS_FLAG( showFlag, EShowFlagType_RankTitle); }   // �Ƿ���ʾ����


    void ShowAecorative( bool bShow )
    {      
        if ( bShow )
        { _SET_FLAG( showFlag, EShowFlagType_Aecpratove ); }
        else
        { _CLS_FLAG( showFlag, EShowFlagType_Aecpratove ); }
    }

    void ShowHelmet( bool bShow )
    { // ��ʾͷ��
        if ( bShow )
        { _SET_FLAG( showFlag, EShowFlagType_Helmet ); }
        else
        { _CLS_FLAG( showFlag, EShowFlagType_Helmet ); }
    } 

    void ShowSignature( bool bShow )
    { // ��ʾ����
        if ( bShow )
        { _SET_FLAG( showFlag, EShowFlagType_Signature ); }
        else
        { _CLS_FLAG( showFlag, EShowFlagType_Signature ); }
    } 

	void ShowHero( bool bShow )
	{ // �Ƿ���ʾ������̬
		if ( bShow )
		{ _SET_FLAG( showFlag, EShowFlagType_Hero ); }
		else
		{ _CLS_FLAG( showFlag, EShowFlagType_Hero ); }
	} 

	void ShowRankTitle( bool bShow )
	{ // ��ʾ����
		if ( bShow )
		{ _SET_FLAG( showFlag, EShowFlagType_RankTitle ); }
		else
		{ _CLS_FLAG( showFlag, EShowFlagType_RankTitle ); }
	} 
    
    void WriteVisual ( CDataChunkWriter* w);
    void ReadVisual ( uint8* bybuff, uint32 dwsize );
};

struct SCharStorageData
{
    SCharStorageData()
    { memset( this, 0, sizeof(SCharStorageData) ); }

    typedef std::vector<SCharItem>      ItemSortContainer;
    typedef ItemSortContainer::iterator ItrItemSortContainer;

    uint32 dwStorageMoney;          // �ֿ����Ǯ
    SCharItem   stStorageItems[STORAGE_ITEMGRID_MAX] ;
    SMountItem  xStorageMounts[STORAGE_MOUNTGRID_MAX];

    SCharItem* GetItemByIndex( int nIndex )
    {
        if ( nIndex < 0 || nIndex >= STORAGE_ITEMGRID_MAX )
        { return NULL; }

        if ( stStorageItems[nIndex].itembaseinfo.ustItemID == InvalidLogicNumber || stStorageItems[nIndex].itembaseinfo.nOnlyInt == InvalidLogicNumber )
        { return NULL; }

        return &( stStorageItems[nIndex] );
    }

    SMountItem* GetMountByIndex( int nIndex )
    {
        if ( nIndex < 0 || nIndex >= STORAGE_MOUNTGRID_MAX )
        { return NULL; }

        if ( xStorageMounts[nIndex].baseInfo.id == InvalidLogicNumber || xStorageMounts[nIndex].baseInfo.guid  == InvalidLogicNumber )
        { return NULL; }

        return &( xStorageMounts[nIndex] );
    }

    void CleanUp()
    {
        ItemSortContainer items;
        for(int i = 0; i< STORAGE_ITEMGRID_MAX ; ++i)
        {
            if( stStorageItems[i].itembaseinfo.ustItemID == InvalidLogicNumber || stStorageItems[i].itembaseinfo.nOnlyInt == 0 )
                continue;

            items.push_back( stStorageItems[i] );

            stStorageItems[i].itembaseinfo.ustItemID = InvalidLogicNumber;
            stStorageItems[i].itembaseinfo.nOnlyInt  = 0;
            stStorageItems[i].bCanUse = false;
        }

        sort( items.begin(), items.end(), SortItemID);

        ItrItemSortContainer it    = items.begin();
        ItrItemSortContainer itEnd = items.end();
        for (int i=0; i< STORAGE_ITEMGRID_MAX && it != itEnd; ++it, ++i)
        {
            stStorageItems[i] = *it;
            stStorageItems[i].itembaseinfo.stPacketIdx = i;
        }
    }
};

struct SBattleResult
{ //ս��
    short shVictory; //ʤ��
    short shDraw;    //ƽ��
    short shFail;    //ʧ��
};

struct SGameWorldTime
{ //��Ϸʱ��
    short shYear;
    short shMonth;
    short shDay;
    short shHour;
    short shMinute;
};

struct SValueChanged
{
    union uData
    {  
        __int64 n64Value;
        uint32  dwValue;
        float   fValue;
        short   stValue;
        int     nValue;
    };
    unsigned short ustWhichAttr;
    uData          data;
};

struct SCharPosData
{
    uint32      dwMapID;
    int16       stX;
    int16       stY;
    D3DXVECTOR3 vPos;

    void WritePosData (CDataChunkWriter *w);
    void ReadPosData (BYTE* bybuff,DWORD dwsize);
};

enum EMail
{  
    EM_MoneySendMax        = 200 * 10000,      // ����200��
    EM_MailMaxCount        = 100,              // �ռ���ɱ����ʼ�������Ϊ100��    
    EM_MailFullNotifyCount = 90,               // ������������90��ϵͳ��ʾ��������    
    EM_AddressNameSize     = dr_MaxPlayerName, // ��ַ
    EM_HoldMailDays        = 30,               // ������Ĵ��ʱ��
    EM_MailFee             = 50,               // ÿ���ʼ�������    
    EM_MailContentMax      = 50 * 2,           // ÿ���ʼ�������ַ���    
    EM_TileMaxCount        = 32,               // �ʼ�����
    EM_MailAccessorySize   = 300,              // ������С
    EM_FromMaxCount        = 1,                // �����˵ĸ���
    EM_ToMaxCount          = 1,                // Ŀ��������
    EM_OtherSendMaxCount   = 6,                // ����
    EM_TargetMaxCount      = EM_ToMaxCount + EM_OtherSendMaxCount,
    EM_OwnerMaxCount       = EM_FromMaxCount + EM_TargetMaxCount,

    EM_FromIndex           = 0,                              // �������������е�λ��
    EM_ToIndex             = EM_FromIndex + EM_FromMaxCount, // �������������е�λ��
    EM_OtherIndex          = EM_ToIndex + EM_ToMaxCount,     // �������������е�λ��
};  

enum EMailOp
{
    EMO_None,         // �޲���
    EMO_Delete,       // ɾ���ʼ�
    EMO_Open,         // ���ʼ�
    EMO_GetMoney,     // ��Ǯ
    EMO_GetAccessory, // �ø���
};

struct SMail
{ // �ʼ�
    enum EMailType
    {
        EMT_System, // ϵͳ�ʼ�
        EMT_Player, // ����ʼ�
    };

    enum EMailState
    {
        EMS_NotOpen    = 0,  // δ��
        EMS_Open       = 1,  // ��
        EMS_HaveGetItem = 2, // �Ѿ����
    };

    enum EAccessoryType
    {
        EAT_None,  // �� �޸���
        EAT_Item,  // ����
        EAT_Mount, // ��
        EAT_Pet,   // ����
    };

    enum ETargetAddressResult
    {
        ETAR_Success,        // �ɹ� 
        ETAR_TargetNotExit,  // Ŀ�겻����
        ETAR_TargetMailFull, // Ŀ���ʼ��Ѿ���
    };

    struct SAddress
    {
        int8   addressName[ EM_AddressNameSize ]; // ��ɫ��
        uint32 charDbId;                          // ��ɫDbId
    };

    // Ŀ����
    struct SAddressResult
    {
        uint8           result;  // ���
        SMail::SAddress address; // �����˵ĵ�ַ        
    };

    struct SAccessory
    {
        uint8 type;                          // ��������
        uint8 content[EM_MailAccessorySize]; // ����
    };

    SMail()
    { Reset(); }

    void Reset()
    { memset( this, 0, sizeof(SMail) ); }

    int32      id;                         // �ʼ�Id
    uint8      type;                       // �ʼ�����
    uint8      state;                      // �ʼ�״̬
    int8       title[EM_TileMaxCount];     // ����
    SAddress   owners[EM_OwnerMaxCount];   // �����˵ĵ�ַ
    int8       content[EM_MailContentMax]; // �ʼ�����
    uint32     money;                      // ��Ǯ
    time_t     sendTime;                   // �ʼ�ʱ��
    SAccessory accessory;                  // ��������
};

struct SDBMail 
{
    enum EDeleteState
    {
        EDS_NotDelete = 1,
        EDS_Delete    = 0,
    };

    SDBMail()
    {
        deleteState = 0;
    }

    SMail  baseInfo;    // 
    uint16 deleteState; // ɾ������� ռ32��λ��
};

struct SShortCut
{
    int BagType;  // ���ڵı���������
    int BagIndex; // ���ڵı����е�λ��

    SShortCut() : BagType(-1), BagIndex(-1)
    { }

    void writeShortCut(CDataChunkWriter *w);
    void readShortCut(BYTE* bybuff,DWORD dwsize);
};

struct SHotKey 
{
    SShortCut  ShortCut;

    void writeMouseItem(CDataChunkWriter *w);
    void readMouseItem(BYTE* bybuff,DWORD dwsize);  
};

//��Ӧ��ʰȡȨ��
struct SPickAccessInfo
{
    uint32 dwPlayerDBID;
    uint8 chPickAccess;     // Ȩ�� (λ��Ĺ�ϵ)

    bool operator == (uint32 dwID) { return dwPlayerDBID == dwID; }
};

struct SMouseItem
{ //��mouse�ϼ�¼��item����
    //enum
    //{
    //    TypeNull,     // ��ʾ�����Ϊ�գ�û���κε���
    //    TypeFactItem, // ��ʾ����ϼ�¼������ĵ�������
    //    TypeNotItem,  // ��ʾ����ϼ�¼�Ĳ�����ĵ������ݣ��Ǽ��ܣ��ȡ�����
    //};
    //unsigned short type;
    SCharItem  ItemData;
    SShortCut  ShortCut;    
    void writeMouseItem(CDataChunkWriter *w);
    void readMouseItem(BYTE* bybuff,DWORD dwsize);        
};

// �ȼ�
struct SCharHotKeys
{
    SHotKey itemHotKey[More_iHotkey];

    void writeCharHotKeys(CDataChunkWriter *w);
    void readCharHotKeys(BYTE* bybuff,DWORD dwsize);        
};

struct SQuestTimeRecord
{ // �����ʱ���¼
    SQuestTimeRecord()
    {
        id = 0;
        time = 0;
    }

    uint16  id  ; // ����id
    __int64 time; // ����ʼʱ�� ���� ����ʱ�� (������Id��Ӧ������)
};

struct SSysVars
{
    SSysVars()
    {
        memset( szVars,    0, sizeof( szVars    ));
        memset( questTime, 0, sizeof( questTime ));
    }

    void writeVars( CDataChunkWriter* w );
    void readVars( ReadData inP,int nSize );

    short            szVars[ More_iMaxVars ];
    SQuestTimeRecord questTime[ QuestLimitTimeMaxCount ]; // �����ʱ������
};

struct SCardData
{
	SCardData()
	{
		Reset();
	}
	void Reset()
	{
		memset( shCardLevel, -1, sizeof( shCardLevel ) );
		memset( unCardAchieve, 0, sizeof ( unCardAchieve ));
	}

	void writeCardData( CDataChunkWriter* w );
	void readCardData( BYTE* bybuff,DWORD dwsize );

	short shCardLevel[ More_nCardMax ];
	uint8 unCardAchieve[ More_nCardAchieve ];
};

struct SRankTitleData
{
	SRankTitleData()
	{
		Reset();
	}

	void Reset()
	{
		shCurRankTitleId = -1;
		bGetSalary = 0;
		dGetSalaryTime = 0;
	}

	void writeRankTitleData( CDataChunkWriter* w );
	void readRankTitleData( BYTE* bybuff,DWORD dwsize );

	short shCurRankTitleId; //��ǰ����Id
	BYTE bGetSalary; //�����Ƿ����ٺ»
	DWORD dGetSalaryTime; //��ȡٺ»ˢ�µ�ʱ��
};

struct SHuntingData
{
	SHuntingData()
	{
		Reset();
	}
	void Reset()
	{
		memset( nCurRandIds, 0, sizeof(nCurRandIds) );
		nCount = 0;
		dFreeRefreshTime = 0;
	}

	void writeHuntingData( CDataChunkWriter* w );
	void readHuntingData( BYTE* bybuff,DWORD dwsize );

	int nCurRandIds[More_nHuntingNum]; //��������漴��������������
	int nCount; //�������Եĸ���
	DWORD dFreeRefreshTime; //���ˢ�µ�ʱ��
};

struct SCharBuff
{ //����״̬������
    enum StatusEventType
    {
        StatusEventType_Other,
        StatusEventType_Skill,
        StatusEventType_Mount,
    };

    int16           StatusID;        // ��״̬��id���    
    int16           iLevel;          // ���Ӹ�״̬�ĵȼ�(��� <= 0 ��ʾû�и���״̬)
    GameObjectId    masterId;        // ��״̬���ͷ��ߵ�ID    
    int             nEffectID;       // �ͻ�������Ч�������ڵ�ID
    uint8           bLastEffect;     // �Ƿ����һ����Ч
    uint32          dwStartTime;     // ��ʼʱ��
    uint32          dwPreDamage;     // �ϴν����˺���ʱ��
    uint32          dwDurationTime;  // ״̬����ʱ��
    int             restoreType;     // �洢����
    uint32          dwPlayerDBID;    // �ͷ��ߵ�DBID
    int64           nInt64StartTime; // δ��ʧЧʱ��
    uint8           bStop;           // �Ƿ�ֹͣ
    uint8           eventType    ;   // ������״̬������
    uint16          eventValue   ;   // ������״̬��ֵ
    uint8           lapoverNum   ;   // ���Ӵ���

    SCharBuff()
    { Reset(); }

    void Reset()
    {
        StatusID             = -1;
        iLevel               = -1;
        masterId             = InvalidGameObjectId;
        dwStartTime          = 0;
        dwPreDamage          = 0;
        nEffectID            = -1;
        bLastEffect          = false;
        dwDurationTime       = 0;
        restoreType          = false;
        dwPlayerDBID         = 0;
        nInt64StartTime      = -1;
        bStop                = 0;
        eventType            = 0;
        eventValue           = 0;
        lapoverNum           = 0;
    }

    void WriteBodyStatus( CDataChunkWriter *w       );
    void ReadBodyStatus ( BYTE* bybuff,DWORD dwsize );
};

struct SCharOtherDataClient0
{
    SCharOtherDataClient0()
    { memset( this, 0, sizeof(SCharOtherDataClient0) ); }
    
    SCharPosData  pos;
    SCharPosData  sBornPos;
    void WriteOtherDataClient0(CDataChunkWriter *w);
    void ReadOtherDataClient0 (BYTE* bybuff,DWORD dwsize);
};

struct SCharItemBagData
{
    SCharItemBagData()
    { }

    SCharItem       stPackItems     [ITEM_BAGMAX]           ;   // ��ͨ��������
    SCharItem       ciMaterialItems [ITEM_BAGMATERIAL_MAX]  ;   // ���ϰ�������
    SCharItem       ciTaskItems     [ITEM_BAGTASK_MAX]      ;   // �����������
    SMountItem      miItems         [ITEM_MOUNT_MAXCOUNT]   ;   // ����
    SPetItem        petItems        [ITEM_PET_MAXCOUNT]     ;   // ����
    SPetItem        petBreedItem                            ;   // ���ڷ�ֳ�ĳ���
};

//�ƺ�����Ҫ�õļ���
struct TitleCounter
{
    TitleCounter() : titleid(0), type(0), value(0), count(0) { }
   
    void Clear()
    {
        titleid = 0;
        type = 0;
        value = 0;
        count = 0;
    }

    bool IsEmpty() { return titleid == 0; }

    const unsigned short GetTitleID() const { return titleid; }
    const unsigned short GetType() const { return type; }
    const unsigned int GetValue() const { return value; }
    const unsigned int GetCount() const { return count; }

    void AddCount(unsigned short nCount) { count += nCount; }
    void SetCount(unsigned short nCount) { count = nCount; }

    void Write( CDataChunkWriter* w );
    void Read( BYTE* szBuff, DWORD nSize );

    unsigned short titleid;
    unsigned short type;
    unsigned int value;
    unsigned int count;
};

struct SRunTimeInfoToDB
{
    SRunTimeInfoToDB()
    {
        nEneryTime = 0;
        nMountActionTime = 0;
    }

    void Write (CDataChunkWriter *w);
    void Read( BYTE* buffer, DWORD size );

    uint32 nEneryTime;                // �����ۼ�ʱ��
    uint32 nVigorTime;                // �����ۼ�ʱ��
    uint32 nMountActionTime;          // ���������ۼ�ʱ��
};

struct SpecialQuestInfo
{
    SpecialQuestInfo() : nNpcID( 0 ), dwTime( 0 ) { }

    void Write (CDataChunkWriter *w);
    void Read( BYTE* buffer, DWORD size );

    GameObjectId nNpcID;
    unsigned int dwTime;
};

struct SPressKeySuit
{
    SPressKeySuit() { memset( this, 0, sizeof(SPressKeySuit)); }

    void Write (CDataChunkWriter *w);
    void Read( BYTE* buffer, DWORD size );

    char    keySuitName [ dr_MaxPlayerName ];               // һ����װ��
    int64   equipitem   [ EEquipPartType_MaxEquitPart ];    // װ����GUID
};

enum ECharTime64Var
{
    ECT_LastLoginTime       ,   // �ϴε�¼ʱ��
    ECT_LastOfflineTime     ,   // �ϴ�����ʱ��
    ECT_ChangeCountryTime   ,   // �ϴθ��Ĺ���ʱ��
    ECT_ExploitTime         ,   // ��ѫֵ����ʱ��

    ECT_MaxTimeVar  = 20    ,   // �������ϵ�ʱ���������
};

enum ECharTime32Var
{
    ETV32_RewardTime        ,   // ��ȡ����ʱ��

    ETV32_MaxTimeVar = 20   ,   
};

struct SExtendData
{
    SExtendData()
    { memset( this, 0, sizeof(SExtendData) ); }

    void          AddTitleCounter(TitleCounter& xcounter); 
    void          RemoveTitleCounter(short nTitleID);
    TitleCounter* GetTitleCounterByIndex(short nIndex);
    TitleCounter* GetTitleCounterByTitleID(short nID);
    TitleCounter* GetTitleCounterByConditionType(short nType, short nID);
    
    void Write (CDataChunkWriter *w);
    void Read( BYTE* buffer, DWORD size );

    SRunTimeInfoToDB xRunTime;  // ����ʱ����
    TitleCounter     nTitleCounters [MAX_TITLE_COUNT];          // ����ƺż���
    SpecialQuestInfo xPubQuestInfo  [MAX_SPECIALQUEST_COUNT];   // ��¼�ƹ�����ʱ����Ϣ
    SpecialQuestInfo xConQuestInfo  [MAX_SPECIALQUEST_COUNT];   // ��¼�����������Ϣ
    unsigned long    dwGuideQuestInfo;                          // ���������������
    bool             isOfflineHook   ;                          // ��һ���Ƿ����߹һ�
    uint32           totalHookTime   ;                          // �ۼ����߹һ�ʱ��

    int64            n64TimeVars    [ECT_MaxTimeVar];           // ʱ���������
    unsigned int     n32TimeVars    [ETV32_MaxTimeVar];         // 32λʱ���������

    //SPressKeySuit    xPressKeySuit  [MAX_PRESSKEYSUIT_COUNT];   // һ����װ
};

enum EGuideState
{
    EGuideState_UnFinish    = 0,
    EGuideState_Finish      = 1,
};

struct SCharKillPlayer
{
	unsigned int PlayerDBID;
	unsigned short Num;
};

struct SCharOtherDataClient : public SCharOtherDataClient0
{ 
    SCharOtherDataClient()
    {
        chProtectLockTime = 1;
        dwBanSpeakTime    = 0;

        memset( recipes,    0, sizeof(recipes) );
        memset( guideVars,  0, sizeof(guideVars) );

		PetDuration = 0;

		sevenDayStartTime = 0;
		equipTotalScore = 0;

		nThreeDayVision = 0;
		nThreeDayValue = 0;

		nBeginGameGeneralBattleTime = 0;
		
    }

    // �����ұ��� ��ҪUpDataItemPackInfo
    void writeOtherdataClient(CDataChunkWriter *w);
    void readOtherdataClient(BYTE* bybuff,DWORD dwsize);
    void readFightData(ReadData inP,int nsize);

    void  SetGuideVar( int16 nId, uint8 state );
    uint8 GetGuideVar( int16 nId );

    SCharSkills          skills;         // ���ܱ���
    SCharHotKeys         hotkeys;        // �ȼ�����            
    short                stMountId;      // ��ǰ�������ŵ�����Id [<0û�������� >0 һ���������������ս������]
    float                fDirX;          // ����X -1 Ĭ��
    float                fDirY;          // ����Y 0
    SCharBuff            sCharBodyStatus[BodyStatusType_Max];       // ״̬
    unsigned short       recipes        [MAX_RECIPE_COUNT];         // �����䷽
    unsigned char        chProtectLockTime;                         // ���ױ���ʱ��( ��λ���� )   
    unsigned long        dwBanSpeakTime;                            // ����ʱ��    ( ��λ���� )
    unsigned char        guideVars      [MAX_GUIDE_COUNT];          // ����ָ��
	unsigned int		 PetDuration;
	SCardData			 cards;							// ����
	__int64				 sevenDayStartTime;				// �����ֿ���ʱ��
	uint32				 equipTotalScore;				// װ���ܷ�
	SRankTitleData		 rankTitle;						// ����
	SHuntingData		 sHunting;						// ����

	unsigned int		nThreeDayValue;				// ��¼���3����3�յ���ȡ�����ļ�¼
	unsigned short		nThreeDayVision;				// ��¼����3��İ汾��Ϣ ��ͬ�İ汾��ʾ��ǰ�� nThreeDayValue �������

	__int64				nBeginGameGeneralBattleTime;	//����Լս��CDʱ��
};

struct SCharOtherData : public SCharOtherDataClient
{
    SCharOtherData()
    {
        dwHighShoutCDTime = 0;
        dwRecordKillMonsterTime = 0;
        dwRecordKillMonsterCount = 0;
        nRecordHonourTime = 0;
        nRecordHonourCount = 0;
        nGuildID = 0;
        dwLeaveGuildTime = 0;
		nFamilyID = 0;
		nRecordKillPlayerTime =0;
		nsuanimalID = 0;
		ClearKillInfo();
		exitGameTime = 0;
		LeaveExpHourSum = 0;
    }

    void WriteOtherDataBlob (CDataChunkWriter *w);
    void ReadOtherDataBlob (BYTE* bybuff,DWORD dwsize);
    void ReadOtherImport(ReadData inP,int nsize);

	void  ClearKillInfo();
	uint16 GetKillSum(unsigned int DBID);
	void  AddKIllPlayer(unsigned int DBID);
	uint16 GetAllKillSum();
	void SetExitTimeNow();
	void SetLeaveHourSum();
    
    SSysVars      vars;                        // �����ϵͳ����
    bool          bNewChar;                    // �Ƿ�Ϊ�½���ɫ
    unsigned long dwHighShoutCDTime;           // ���纰����ȴʣ��ʱ��    

	unsigned int		dwRecordKillMonsterTime;     // ��¼ɱ�ֵ����ʱ��
    unsigned int		dwRecordKillMonsterCount;    // ��¼ɱ�ֵĸ���

    unsigned int   nRecordHonourTime;          // ��¼���õ�������ʱ��
    unsigned short nRecordHonourCount;         // ��¼ÿ������ֵ

    SecondPassword xSecondPassword;            // ���2������

    unsigned int nGuildID;                     // ����ID  
    unsigned int dwLeaveGuildTime;             // �뿪���ɵ�ʱ��

	unsigned int nFamilyID;						// ����ID

	__int64 nRecordKillPlayerTime;				//��¼���ɱ���й���ҵ�ʱ��(��Ұ��)

	__int64  nsuanimalID;						//����ʱ�� ���ڳ�ս״̬�ĸ���ID

	//unsigned int PetDuration;					//��ҵ�ָ�ӵ�

	SCharKillPlayer		 KillList[MAX_KILLSUM];			// ��ҵ���ɱ�˼���
	__int64				 exitGameTime;					//����ϴ��뿪��Ϸ��ʱ��
	unsigned int		 LeaveExpHourSum;				// ���ߵ�Сʱ���ۼ�
};

struct SCharAchieve
{
    SCharAchieve() { memset( this, 0, sizeof(SCharAchieve)); }

    void Write( CDataChunkWriter *w );
    void Read ( BYTE* buffer, DWORD size );

    uint8   finishState ;   
    int64   finishTime  ;
};

struct SAchieveData
{
    SAchieveData() { memset( this, 0, sizeof(SAchieveData)); }

    void Write( CDataChunkWriter *w );
    void Read ( BYTE* buffer, DWORD size );

    uint32           achievePoint;  // �ɾ͵���
    uint32           achieveVars  [More_iMaxAchieveVars] ;
    SCharAchieve     xAchievements[MAX_ACHIVEVMENT_COUNT]; // ����ɾ�
};

struct SPetIdentify
{
    SPetIdentify() { Reset(); }

    void Reset() { memset( this, 0, sizeof(SPetIdentify)); }

    void Write( CDataChunkWriter *w );
    void Read ( BYTE* buffer, DWORD size );

    unsigned short  petType;        // ��������
    unsigned short  identifyTotal;  // ���������ۼ�
};

struct SIdentifyData
{
    SIdentifyData() { memset( this, 0, sizeof(SIdentifyData)); }

    void Write( CDataChunkWriter *w );
    void Read ( BYTE* buffer, DWORD size );

    bool AddPetIdentify         ( const SPetIdentify& xIdentify );
    bool RemovePetIdentify      ( uint16  petType );
    SPetIdentify* GetPetIdentify( uint16  petType );

    SPetIdentify    petIdentify[MAX_PETIDENTIFY_COUNT]; // ����ͼ��
};

struct SCharInfoClient
{ // �ͻ��˵Ľ�ɫ����
    SCharBaseInfo        baseinfo;
    SCharVisual          visual;
    SCharOtherDataClient otherdataclient;
    SCharItemBagData     ItemBagData;
};

struct SCharDBInfo
 { // ��ɫ���� DB ����
    SCharBaseInfo    baseinfo;      // ��������
    SCharVisual      visual;        // ��ɫ���
    SCharOtherData   otherdata;     // ��������
    SCharItemBagData itemData;      // ��������
    SExtendData      extendData;    // ��������
    SAchieveData     achieveData;   // �ɾ�����
    SIdentifyData    identifyData;  // ͼ������
};

struct RunTimePetInfo
{
    enum EPetType
    {
        Type_Pet = 0, // ����
        Type_Protect, // ������
        Type_Max,
    };

    RunTimePetInfo()
    { 
        nPetID      = 0;
        nPetIndex   = -1;
        nHp         = 0;
        nMp         = 0;
        varValue    = -1;
        nSummonSkillID = -1;
        memset( sCharBodyStatus, 0, sizeof(SCharBuff) * BodyStatusType_Max );
    }

    int                  nPetID;
    int16                nPetIndex;
    int                  nHp;
    int                  nMp;
    int                  varValue;                  // ����ֵ
    int16                nSummonSkillID;            // �ٻ�����
    SCharBuff sCharBodyStatus[BodyStatusType_Max];  // ״̬
	bool				 IsCanRide;
};

struct SRuntimeInfo
{ 
    SRuntimeInfo()
    {
        mountId                   = 0;
        dwProtectLockLeaveTime    = 0;
        dwUpdatePKValueTime       = 0;
        inFightTime               = 0;
        dwOnLineTime              = 0;

		nAntiAddictionDbOnlineTime = 0;
		nOffTimeAntiAddiction      = 0;
		nAntiAddicationStatus      = enumAntiAddictionStateNormal;
		bGetAntiAddictionInfo      = false;

        bReqRemoveMarriage        = false;
        bForceRemove              = false;
        nCountrySpeakSpaceTime    = 0;
		PkValueTimeLog			  = 0;
		OnLineTime				  = 0;
    }

    // ��ɫ���� Runtime ����
    short              mountId                  ; // ��ǰ�������ŵ�����Id [<0û�������� >0 һ���������������ս������]
    unsigned int       dwProtectLockLeaveTime   ; // ���ױ���ʣ��ʱ�� ( == 0,�Ѿ���������ʱ�� )
    int                nCountrySpeakSpaceTime   ; // ���ҷ�����ȴʱ��
    unsigned int       dwUpdatePKValueTime      ; // ������PK��ʱ��
    RunTimePetInfo     xPetInfo[EPT_Max]        ; // 1:���ܳ���  2:������ 3:�������
    uint32             inFightTime              ; // ��ս���е�ʱ��
    uint32             dwOnLineTime             ; // ��ɫ��������ʱ�� ( ��λ: ���� )
    SCharItem          xBuyBackItem[10]         ; // �ع���Ʒ�б�
    bool               bGetAntiAddictionInfo     ; // �Ƿ��Ѿ��õ���������Ϣ
    uint32             nAntiAddictionDbOnlineTime; // ���ߵ�λ���� ��ÿ��ͬ����ʱ���п��ܱ�ܴ�һ���˺��ڼ�����ͬʱ�棩
    uint32             nOffTimeAntiAddiction     ; // ���ߵ�λ����
    AntiAddictionState nAntiAddicationStatus     ; // ������״̬
    bool               bReqRemoveMarriage       ; // �����������
    bool               bForceRemove             ;
	uint32			   PkValueTimeLog			;//PKֵ��ʱ ���������ݿ�		
	uint32			   OnLineTime;				//����ʱ��
};

struct SAttrUp
{
    char  cType;
    short stWhichAttr;
};

struct SEffectDamage
{
    GameObjectId stWho;
    DWORD dwState;
    short stDamage;
};

struct SAttTargetResult
{
    SAttTargetResult()
    { Reset(); }

    void Reset()
    { memset( this, 0, sizeof( SAttTargetResult));}

    GameObjectId stTargetWho;        // ������Ŀ��
    GameObjectId stAttackerWho;      // ˭�ǹ�����

    int   stTagHpNum;         // Ŀ��������Hp
    int   stSrcHpNum;         // ������������Hp

    int   stTagMpNum;         // Ŀ��������Mp
    int   stSrcMpNum;         // ������������Mp

    int   nTagHp;             // ������Ŀ��ʣ�µ�hp
    int   nSrcHp;             // ������hp

    int   nTagMp;             // ������Ŀ��ʣ�µ�Mp
    int   nSrcMp;             // ������Mp

    short nBackAttack;        // Ŀ���ܱ�����������ֵ
    int   nShieldHp;          // ħ��������HP

    char  cBalanceType;       // ����Ӧ�õĽ��㷽ʽ
    short nStatusFlag;        // ״̬����flag
};

struct PublicMessageDd
{ // 445 
    char          type;                         // ��Ϣ����
    unsigned long playerDbId;                   // ��ɫdb id
    char          playername[dr_MaxPlayerName]; // ��ɫ����
    short         level;                        // �ȼ�
    short         profession;                   // ְҵ
    unsigned long time;                         // ����ʱ��
    char          addonInfo[4*100];             // ������Ϣ
};
enum sides
{
    e_blue = 0,
    e_red = 1,
    e_max
};

struct sKillPerSonTime 
{
    DWORD dwPlayerDBid;
    int nPlayerTimes;
    DWORD dwBeKilledTime;
};
typedef std::map<DWORD,sKillPerSonTime*> mapPersonkill;
//sbw_reputerank
//struct SReputeRank
//{
//    SReputeRank()
//    {
//        ::ZeroMemory(this,sizeof(SReputeRank));
//    }
//    DWORD current:4;
//    DWORD level:4;
//    DWORD skillId:8;
//    DWORD flags:16;
//    SReputeRank getReputeRankInf(DWORD    dw)
//    {
//        ::CopyMemory(this,&dw,sizeof(DWORD));
//        return *this;
//    }
//    void    sv_openrepute(WORD id,WORD level = 0);        //��һ�����
//    void    sv_setcurrent(WORD id,WORD level);                //���õ�ǰ��ͷ����Ϣ
//    void    sv_save(DWORD*    pdw);                                //����
//};

struct SGameProperty
{
    short stLevel;
    int   nHp;
    int   nMp;
};

struct SProcessTime
{
    char* szFunctionName;
    __int64 nTime;
};
    
struct SMovePos 
{
    SMovePos()
    { memset( this, 0, sizeof(SMovePos) ); }

    float fX;       // ���������X��
    float fY;       // ���������Y��
    float fZ;       // ���������Z��
    float fV;       // �����ٶȰٷݱ�(1Ϊ����).��0.8,1.2֮���
    float fStep;    // ����
    DWORD dwTime;   // ����Ŀ���ʱ��ͣ����ʱ��(����).
    short stSceneId;// ���ų���ID
    char  szActionName[32];
};

typedef std::vector<SMovePos> MovePosContainer;

struct SRoute
{
    unsigned int     mapId      ; // ��ͼId
    unsigned int     routeId    ; // ·��Id
    unsigned int     nextMapId  ; // ��һ�ŵ�ͼ
    unsigned int     nextRouteId; // ��һ��·��
    unsigned int     flyRoute   ; // �Ƿ��Ƿ���·��
    MovePosContainer allMovePos ; // ����·��
};

struct SAttackTarget 
{ // ���棬Ŀ�����ݣ�ÿ����������Ҫ��Ŀ��������
    bool		   bIsCharTarget; // �жϹ�����Ŀ���ǶԵ��滹���ر��npc
    GameObjectId   nCharID;       // ����Ŀ���ID
    D3DXVECTOR3	   vPos;		  // ����Ŀ���λ��
};

////////////////////////////////////////////////////////////////////////////////////////////////

// TellClient ����������
union UnionParam
{
    unsigned long nValue;
    float fValue;
    char szValue[dr_MaxPlayerName];
};

struct ItemDropControl
{
    ItemDropControl()
    {
        dwControlCount = 0;
        dwDropCount    = 0;
    }

    uint32 dwControlCount;      // ��ǰ��ֵ��
    uint32 dwDropCount;         // �Ѿ����˵ĸ���
};
typedef std::map< uint16, ItemDropControl > MapItemDropControl;
typedef MapItemDropControl::iterator MapItemDropControlIter;

const uint32 gJiFengItemValueMaxCount = 10;
const uint32 gJiFengItemSnMaxCount    = 32;
const uint32 gJiFengGainMaxCount      = 20;

struct SJiFengItemRecordPlatform
{
    int8   sn[gJiFengItemSnMaxCount+1];     // ������
    uint8  itemType;                        // ��Ʒ����
    uint16 itemId;                          // ��Ʒid
    uint16 itemCount;                       // ��Ʒ����
    uint16 value[gJiFengItemValueMaxCount]; // ��������
};

struct SJiFengItemRecordServer
{
    uint32                    id;   // id ����
    SJiFengItemRecordPlatform info; // ������Ϣ
};
typedef std::vector<SJiFengItemRecordServer> JiFengItemServerContainer;
typedef JiFengItemServerContainer::iterator  ItrJiFengItemServerContainer;

struct SJiFengItemRecordClient
{
    uint32 id;
    uint8  itemType;                        // ��Ʒ����
    uint16 itemId;                          // ��Ʒid
    uint16 itemCount;                       // ��Ʒ����
    uint16 value[gJiFengItemValueMaxCount]; // ��������
};

struct QuestScript
{
    QuestScript() : m_nVMId(-1) {}
    short stQuestId; // ����Id
    char  chState;   // ״̬
    int   m_nVMId;   // �ű�Id
    short stEnter;   // �ű����
};

//������Ӫö��
enum enumBattleInfluence
{	
    enumBattleInfluence_Max  = 0, 
	enumBattleInfluence_Red	 = 1,		//�췽, ��Ӫս���е��ƾ�
	enumBattleInfluence_Blue = 2,		//����, ��Ӫս���е����
};

//��������Ӫս���ĳ���
enum enumBattleConst
{	
	enumBattleConst_ResourcePosNum	= 5, 	//��Դ�����
};

//��������Ӫս����Դö��, ����
enum enumBattleResouce
{
	enumBattleResource_Beast	= 0,	//����
	enumBattleResource_Farm		= 1,	//ũ��
	enumBattleResource_Steel    = 2,	//����
	enumBattleResource_Wood		= 3,	//ľ��
	enumBattleResource_Gold		= 4,	//��
	enumBattleResource_Max		= 5,
};

struct AntiTime{
    uint32	_playTime;    //!< ʱ��������ȣ���λΪ����
    uint32  _notifyTime;  //!< ��ʾ�ļ������λΪ����
};

/*! \brief ������ϵͳ����ʱ�������ֵ
*
*  
*
*/
struct AntiAddictionTime{
    AntiTime _normal;  //!< ����ʱ��
    AntiTime _tired;   //!< ƣ��ʱ��
    AntiTime _rest;	   //!< ������ʱ�䣬���ֶ���playTimeֵ��ʾ�ۻ�����ʱ�������ʱ��
};

// end add


enum EEctypeSageDefine
{
    EctypeStageValue1 = 16,         // ��������IDƫ��
    EctypeStageValue2 = 0xFFFF,     //                  
};

#pragma pack(pop) 

//////////////////////////////////////////////////////////////////////////
// Typedef
typedef std::vector<std::string> StringContainer;
typedef StringContainer::iterator ItrStringContainer;

//////////////////////////////////////////////////////////////////////////
// funcion


inline DWORD EctypeId2MapId( DWORD dwEctypeId )
{
    return ( dwEctypeId & EctypeStageValue2 );
}

inline float LogBase(float fValue, float base)
{
   return log(fValue) / log(base);
}

inline float TileToFloat( int nTile )
{
    return nTile * MAPTILESIZE + MAPTILESIZE * 0.5f;
}

inline int16 FloatToTile( float fValue )
{
    return static_cast<int>( ceil( (fValue - MAPTILESIZE * 0.5f) / MAPTILESIZE ) );
}

inline int16 ChunckToTile( int nChunkValue )
{    
    return static_cast<int>(nChunkValue * CHUNK_SIZE / MAPTILESIZE + 0.5f);
}

inline int GetRand( int Min, int Max )
{
    if ( Max <= Min)
    { return Max; }

    return theRand.rand32() % (Max - Min + 1) + Min;
}

template< typename T >
inline int GetRandIndex( T* pProbability, int count, int randNumber )
{
    if (pProbability == NULL)
    { return 0; }

    int rate = 0;
    for (int i=0; i<count; ++i)
    {
        rate += pProbability[i];
        if (randNumber <= rate)
        { return i; }
    }

    return 0;
}

inline float GetRand( float Min, float Max )
{
    int nMin = (int)(Min * 100);
    int nMax = (int)(Max * 100);

    return GetRand( nMin, nMax ) / DEF_PER;
}

#define MaxMonsterIdLength 20
inline bool IsEctypeMonsterID( int nID )    // �����ֵ�ID��4λ�� Ȼ�����һ��6λID
{
    char chBuff[MaxMonsterIdLength + 1] = {0};
    sprintf_s( chBuff, MaxMonsterIdLength, "%d", nID );

    return strlen(chBuff) == ECTYPEMAPMONSTERIDLENGTH;
}

inline bool IsNormalMonsterID( int nID )
{
    char chBuff[MaxMonsterIdLength + 1] = {0};
    sprintf_s( chBuff, MaxMonsterIdLength, "%d", nID );

    return strlen(chBuff) == NORMALMAPMONSTERIDLENGTH;
}

inline int FormatEctypeMonsterID( int nID, unsigned short ustLevel )
{
    if ( IsNormalMonsterID( nID ) )        
    { return nID;}

    char szID[MaxMonsterIdLength + 1] = {0};

    sprintf_s( szID, MaxMonsterIdLength, "%d%02d", nID, ustLevel );

    return atoi( szID );
}

inline int GetEctypeMonsterID(int nID, unsigned short& ustLevel)          // ��ø�����ID ǰ4λ
{
    if ( IsEctypeMonsterID( nID ) )
    {
        ustLevel = 0;
        return nID;
    }
    
    char chBuff[MaxMonsterIdLength + 1] = {0};
    sprintf_s( chBuff, MaxMonsterIdLength, "%d", nID );

    ustLevel = atoi ( chBuff + 4 );
    chBuff[4] = 0;

    return atoi( chBuff );
}

// ��������Ƿ������������
inline bool CheckCreateName( const std::string& strName )
{
    if ( strName.empty() )
    { return false; }

	//strName.find( theXmlString.GetString(eClient_Chat_Begin) ) != string::npos )
    if (strName.find("'") != string::npos || strName.find("-") != string::npos ||
        strName.find("_") != string::npos || strName.find("%") != string::npos ||
        strName.find(" ") != string::npos || strName.find(":") != string::npos || strName.find("\\") != string::npos )
    { return false;}
    return true;
}

inline bool IsFloatZero(const float x, float epsilon = 1e-6f) 
{
    return fabs(x) < epsilon;
}

template< typename T >
inline void StrToIntArray( const char* str, T *iArray, int size, const char* split )
{
    if ( str == NULL || iArray == NULL || split == NULL || size == 0)
    { return; }

    int index = 0;
    char* token = NULL;
    char* next_token = NULL; 
    token = strtok_s ( const_cast<char*>( str ), split, &next_token ); 
    while( token != NULL ) { 
        if ( index >= size )
        { return; }

        iArray[index] = atoi( token );
        token = strtok_s( NULL, split, &next_token ); 
        ++index;
    } 
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
// ��¼log��ص�һЩ����
namespace LogDefine
{
    enum EConstDefine
    {
        // ��������ķ�ʽ
        ECD_DropType_Monster = 0,       // ɱ�ֵ���
        ECD_DropType_Player  = 1,       // ɱ�˵���
        ECD_DropType_Luck    = 2,       // ����15�ص���
    };

    enum ELogType
    {
        // Log������
        ELT_Unknow      = 0,            // ���������,��ʾ��������
        ELT_EnterGame   = 1,            // ��¼��־
        ELT_ExitGame    = 2,            // �ǳ���־
        ELT_Script      = 3,            // �ű���þ�����־��������
    };
}

namespace ServerDataDefine
{
    typedef unsigned char NodeType; // �ڵ�����
    typedef unsigned char Status;

    enum EnumDefine
    {
        // �ڵ�����
        Node_Root       = 0,  // ���ڵ�
        Node_Center     = 1,
        Node_Database   = 2,
        Node_Game       = 3,
        Node_Character  = 4,
        Node_Gate       = 5,
                       
        // ״̬        
        Status_Fine     = 0,  // ����
        Status_Busy     = 1,  // æ
        Status_Bad      = 2,  // ����
                       
        ErrorID         = 0xFFFFFFFF, // ����id

        DoNothing       = 0,      // ʲôҲ����
        ReqServerStatus = 1,      // ������Ϣ����������
        WaitForAck      = 2,      // �ȴ�����������Ӧ
        SendToPlat      = 3,      // ������Ϣ��ƽ̨�ر�������״̬

        WaitTime        = 10000,  // �ȴ���Ӧʱ��
        BusyTimeOut     = 3000,   // 3���ʾ�������е㿨��
    };
}

//������ƷID
enum SpecialItemID
{
	SID_ProtectStarSix		= 4505, //6�Ǳ�������
	SID_ProtectStarNine		= 4506, //9�Ǳ�������
	SID_ProtectStarTwelve	= 4507, //12�Ǳ�������
	SID_ProtectStarFifteen	= 4508, //15�Ǳ�������

	SID_ProtectMountFour	= 4746, //���ﱣ��4������
	SID_ProtectMountSeven	= 4747, //���ﱣ��7������
	SID_ProtectMountTen		= 4748, //���ﱣ��10������
	SID_MountStrengthen		= 4749, //����ǿ������

	SID_TRANSFERSTAR_DROP   = 5081, //ת�ǲ��ϵ���
	SID_TRABSFERSTAR_UNDROP = 5082, //ת�ǲ��ϲ�����

	SID_UnBindItem			= 4745,//װ������

	SID_GemUp_Level_One		= 5420, //һ����ʯ�ϳɲ���
	SID_GemUp_Level_Two		= 5421, //������ʯ�ϳɲ���
	SID_GemUp_Level_Three	= 5422, //������ʯ�ϳɲ���
	SID_GemUp_Level_Four	= 5423, //�ļ���ʯ�ϳɲ���

	SID_Identify_Material	= 4781, //װ����������

	SID_Gem_Material		= 5400, //��ʯ��Ƕ����
    SID_RandAttr_Material	= 4750, //װ��ϴ������Բ���

	SID_SuAnimalChangeName	= 4774,//����������

	SID_PetComPose			= 4775,

	SID_UnKnowItem			= 25, //δ֪����
};
#endif // __COMMON_GLOBALDEF_H__
