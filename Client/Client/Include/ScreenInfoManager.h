#pragma once
#include "Singleton.h"
#include "ShowScreenText.h"
#include "InfoList.h"
#include "MessageDefine.h"

class CScreenInfoManager : public Singleton<CScreenInfoManager>
{
public:
    struct InfoAttribute
    {
        InfoAttribute()
        {
            nShowMode   = -1;
            nColorId    = -1;
            dwTime      = 0;
            bTopLevel  = false;
            eShowState  = CShowScreenText::eShowFadein;
            nChatType   = MsgChat::CHAT_TYPE_GAMEPROMPT;
            bAutoReply  = false;
            nInfoIndex  = -1;
        }

        void operator = ( const InfoAttribute& infoAttr )
        {
            nShowMode = infoAttr.nShowMode;
            nColorId = infoAttr.nColorId;
            dwTime = infoAttr.dwTime;
            bTopLevel = infoAttr.bTopLevel;
            eShowState = infoAttr.eShowState;
            nChatType = infoAttr.nChatType;
            bAutoReply = infoAttr.bAutoReply;
            nInfoIndex = infoAttr.nInfoIndex;
        }

        int     nShowMode;      // ��Ӧ��ʾ��ʽ
        int     nColorId;       // ��ɫId
        DWORD   dwTime;         // ����ʱ��
        bool    bTopLevel;      // �Ƿ��ö�
        int     eShowState;     // ���뵭��
        int     nChatType;      // ����Ƶ��
        bool    bAutoReply;     // �Զ��ظ�
        int     nInfoIndex;     // �˲���������
    };

    // ����Type���ô������ ScreenInfo.config
    enum InfoType
    {
        //�����Ͻӿ�
        eType_Old_NotProcess                = 0,    // ������
        eType_OldScreen_BigTitle,
        eType_OldScreen_NormalTitle,
        eType_OldScreen_Info,
        eType_OldScreen_SmallInfo,
        eType_OldList_Info,

        eType_Map_Name                      = 8,    // ��ͼ��

        eType_Map_FindPathFailed            = 10,   // ��֧�ֿ��ͼѰ·
        eType_Map_BigMapFindPath            = 13,   // ���ͼ����Ѱ·
        eType_Map_MiniMapFindPath           = 14,   // С��ͼ����Ѱ·
        eType_Map_SearchInfo                = 15,   // ��ͼ��ѯ
        eType_Map_AreaName                  = 16,   // ������
        eType_Map_AreaSafe                  = 17,   // ��ȫ����
        eType_Map_AreaDanger                = 18,   // Σ������

        eType_Country_DefineBreak           = 20,   // �ֿ�������Ϣ
        eType_Country_Operate               = 21,   // ���ҹ�Ա���⡢���ԡ��������������񷢲�
        eType_Country_OfficialBeKilled      = 22,   // ���ҹ�Ա��ɱ
        eType_Item_Get                      = 23,   // �����Ʒ
        eType_Item_TaskNeed                 = 25,   // ��������Ҫ��������
        eType_Info_ChatSys                  = 27,   // �������񡢷�������
		eType_Info_GuildInfo				= 28,   //���ϵͳ

        eType_Operate_Failed                = 50,   // ���ܣ�����ɼ���װ��������������
        eType_Trade_FailedReason            = 51,   // ����ʧ�������ʾ
        eType_Things_Get                    = 52,   // �����Ʒ
        eType_Country_Break                 = 53,   // ����������Ϣ
        eType_Skill_ToLearn                 = 54,   // ����ѧϰ
        eType_Skill_Learnt                  = 55,   // ѧ���˼���
        eType_Item_UseFailed                = 56,   // ��Ʒ�޷���ʹ��
        eType_Status_Fight                  = 57,   // ս��״̬
        eType_Status_Hook                   = 58,   // �һ�״̬
        eType_Shop_Private                  = 59,   // ��̯��ʾ
        eType_Horse_Tip                     = 60,   // ���������ʾ
        eType_Pack_Operate                  = 61,   // ������Ʒ����
        eType_Combine_Success               = 62,   // �ϳɡ��ֽ�ɹ�
        eType_Combine_Failed                = 63,   // �ϳɡ��ֽ�ʧ��
        eType_EquipChange_Success           = 64,   // ��װ�ɹ�
        eType_EquipChange_Failed            = 65,   // ��װʧ��
        eType_Trade_Success                 = 66,   // ���׳ɹ�
        eType_Trade_Failed                  = 67,   // ����ʧ��
        eType_Player_Rename                 = 68,   // ���������
        eType_Fix_Success                   = 69,   // ����ɹ�
        eType_Fix_Failed                    = 70,   // ����ʧ��
        eType_NPC_Talk                      = 71,   // NPC�Ի�
        eType_Battle_SignUpSuccess          = 72,   // ս�������ɹ�
        eType_Follow                        = 73,   // ����
        eType_SmallHorn                     = 74,   // С����
        eType_Item_Arrange                  = 75,   // ����ģʽ
        eType_Main_Display                  = 76,   // ��������ʾ
        eType_AttrFive_Success              = 78,   // ���гɹ�
        eType_AttrFive_Failed               = 79,   // ����ʧ��
        eType_OldRiseStar_Success           = 80,   // ���׳ɹ�
        eType_OldRiseStar_Failed            = 81,   // ����ʧ��
        eType_Mail_Receive                  = 82,   // ��ȡ�ʼ�
        eType_PickUp                        = 83,   // ʰȡ
        eType_Gem_Success                   = 84,   // ��ʯ�ɹ�
        eType_Gem_Failed                    = 85,   // ��ʯʧ��
        eType_RiseGold_Success              = 86,   // �̽�ɹ�
        eType_RiseGold_Failed               = 87,   // �̽�ʧ��
        eType_Soul_Success                  = 88,   // ���̳ɹ�
        eType_Soul_Failed                   = 89,   // ����ʧ��
        eType_Maintain_Success              = 90,   // ��ֵ�ɹ�
        eType_Maintain_Failed               = 91,   // ��ֵʧ��
        eType_MoveStar_Success              = 92,   // ���ǳɹ�
        eType_MoveStar_Failed               = 93,   // ����ʧ��
        eType_Identify                      = 94,   // �����������
        eType_Country_Tip                   = 95,   // ������ʾ
        eType_Amulet_Success                = 96,   // ������ɹ�
        eType_Chat_ChannelTip               = 97,   // ����Ƶ����ʾ
        eType_PKMode_Change                 = 98,   // PKģʽ���
        eType_Platform_Belongs              = 99,   // ƽ̨���
        eType_Relive_Belongs                = 100,  // �������
        eType_Guild_Belongs                 = 101,  // ������
        eType_Produce_Belongs               = 102,  // �������
        eType_RiseStar_Success              = 103,  // ���ǳɹ�
        eType_RiseStar_Failed               = 104,  // ����ʧ��
        eType_Amulet_Failed                 = 105,  // �����ʧ��
        eType_OneAnother                    = 106,  // ��������
        eType_Team_MakeGroup                = 107,  // ���
        eType_Player_Action                 = 108,  // ����Action
        eType_Teacher_Belongs               = 109,  // ʦͽ���
        eType_LevelUp_Belongs               = 110,  // �������
        eType_Friend_Belongs                = 111,  // �������
        eType_Title_Belongs                 = 112,  // �ƺ����
        eType_Dual                          = 113,  // ������ʾ
        eType_RankList                      = 114,  // ���а�
        eType_Shop_City                     = 115,  // �̳�
        eType_SeekEquip                     = 116,  // �۲�
        eType_Mail_Success                  = 117,  // �ʼ��ɹ�
        eType_Mail_Failed                   = 118,  // �ʼ�ʧ��
        eType_Consignment_Success           = 119,  // ���۳ɹ�
                                                       
        eType_Player_AttrUp                 = 120,  // ��װ���Ա��
                                                 
        eType_Consignment_Failed            = 121,  // ����ʧ��
        eType_Battle_Success                = 122,  // ս���ɹ�
        eType_Battle_Failed                 = 123,  // ս��ʧ��
        eType_Ectype_Success                = 124,  // �����ɹ�
                                                  
        eType_SendFlower                    = 125,  // �ͻ�
                                                  
        eType_Ectype_Failed                 = 126,  // ����ʧ��
                                                   
        eType_SendFlower_RandomTip          = 127,  // �ͻ�������С��ʾ

        eType_Store_Password                = 130,  // �ֿ�����
        eType_Wealth_Protect                = 132,  // �Ʋ���������
        eType_Addict_Protect                = 133,  // ������
        eType_MapChange_Failed              = 134,  // ��ͼ��ת����
                                                   
        eType_Marry_Success                 = 200,  // ���ɹ�
        eType_Marry_Failed                  = 201,  // ���ʧ��
        eType_Present_SendSuccess           = 202,  // ����ɹ�
        eType_Present_SendFailed            = 203,  // ����ʧ��
                                                   
        eType_Reputation_Change             = 204,  // �����ı�
        eType_Exploit_Change                = 205,  // ��ѫ�ı�
        eType_PKValue_Change                = 206,  // PKֵ�ı�
        eType_Money_Change                  = 207,  // ��Ǯ�ı�
        eType_Honor_Change                  = 208,  // �����ı�
        eType_Prestige_Change               = 209,  // �����ı�

        eType_Invite_Guild                  = 210,  // ��������
        eType_Invite_Team                   = 211,  // �������
                                                   
        eType_Kill_Info                     = 212,  // ɱ��
        eType_BeKilled_Info                 = 213,  // ��ɱ
                                                   
        eType_Script_Tell                   = 214,  // tell������
                                                    
        eType_Player_AttrDown               = 215,  // ��װ���Ա��
        eType_UnRiseInfo_RandomTip          = 216,  // ��װ������С��ʾ
        eType_ListInfo_RandomTip            = 217,  // ���½�С��ʾ
        eType_RiseInfo_RandomTip            = 218,  // ���϶���С��ʾ
        eType_SysInfo_RandomTip             = 219,  // �����϶���С��ʾ
        eType_BigTile_RandomTip             = 220,  // ��ͼ����С��ʾ
                                                    
        eType_Bull_System                   = 221,  // ϵͳ
        eType_Bull_Broadcast                = 222,  // ����
        eType_Bull_RandomTip                = 223,  // ϵͳ������С��ʾ
                                                   
        eType_Chat_RandomTip                = 224,  // ������С��ʾ
        eType_Tip_RandomTip                 = 225,  // С��ʾ
                                                   
        //���Է�������                            
        eType_Server_MapSuccess             = 250,  // ��ͼ����ִ�
        eType_Server_MapError               = 251,  // ��ͼ����ִ�����
        eType_Server_PlayerMatch_Success    = 252,  // ���û��ƥ����
        eType_Server_PlayerMatch_Error      = 253,  // ���û��ƥ���ϴ���
        eType_Server_TeamTask_Success       = 254,  // ���¶����������
        eType_Server_TeamTask_Error         = 255,  // ���¶���������ش���
        eType_Server_MoveCheck_Success      = 256,  // CheckMovingMsgSendTime
        eType_Server_MoveCheck_Error        = 257,  // CheckMovingMsgSendTime����
        eType_Server_PickItem_Success       = 258,  // PickItem
        eType_Server_PickItem_Error         = 259,  // PickItem����
        eType_Server_QuestState_Success     = 260,  // ��������״̬
        eType_Server_QuestState_Error       = 261,  // ��������״̬����
        eType_Server_DataRefresh_Success    = 262,  // ˢ��char����
        eType_Server_DataRefresh_Error      = 263,  // ˢ��char���ݴ���
        eType_Server_PrivateShop_Success    = 264,  // ���˰�̯
        eType_Server_PrivateShop_Error      = 265,  // ���˰�̯����
        eType_Server_Attack_Success         = 266,  // ��ͨ����
        eType_Server_Attack_Error           = 267,  // ��ͨ��������
        eType_Server_Mount_Success          = 268,  // ����
        eType_Server_Mount_Error            = 269,  // �������
        eType_Server_UseItem_Success        = 270,  // ʹ����Ʒ
        eType_Server_UseItem_Error          = 271,  // ʹ����Ʒ����
        eType_Server_GetItem_Success        = 272,  // ��ȡ��Ʒ
        eType_Server_GetItem_Error          = 273,  // ��ȡ��Ʒ����
        eType_Server_ScriptItem_Success     = 274,  // �ű������Ʒ
        eType_Server_ScriptItem_Error       = 275,  // �ű������Ʒ����
        eType_Server_GraphicCode_Success    = 276,  // ������֤��
        eType_Server_GraphicCode_Error      = 277,  // ������֤�����
        eType_Server_EnterWorld_Success     = 278,  // ��ɫ����
        eType_Server_EnterWorld_Error       = 279,  // ��ɫ�������
        eType_Server_Exit_Success           = 280,  // �˳���Ϸ������
        eType_Server_Exit_Error             = 281,  // �˳���Ϸ����������
        eType_Server_Others_Success         = 282,  // ����
        eType_Server_Others_Error           = 283,  // ��������
        eType_Server_Max                    = 284,  // �������������ֵ

        // �ű�
        eType_Script_TalkGreen              = 285,  // Talk��ɫ
        eType_Script_TalkYellow             = 286,  // Talk��ɫ
        eType_Script_TalkRed                = 287,  // Talk��ɫ
        eType_Script_TalkPurple             = 288,  // Talk��ɫ

        eType_HookOffline_Success           = 290,  // ���߹һ��ɹ�
        eType_HookOffline_Failed            = 291,  // ���߹һ�ʧ��
        eType_Honor_Get                     = 292,  // �������ֵ
        eType_Honor_Error                   = 293,  // ����ֵ����

        eType_CountryBetray_Success         = 294,  // �ѹ��ɹ�
        eType_CountryBetray_Failed          = 295,  // �ѹ�ʧ��

		eType_FullBufRelive_Failed          = 297,	// �Ŵ���ʧ��
		
		//ʦͽ������ʾ��Ϣ����Ļ�м�
		eType_ShiTu_Belongs_Success         = 298,  // 
		eType_ShiTu_Belongs_Failed          = 299,  // 
		eType_Achievement					= 300,  // �ɾͳɹ�
        eType_Achievement_Failed            = 301,  // �ɾ�ʧ��

        eType_CountryBattle_Broadcast       = 302,  // ��ս����
        eType_CountryBattle_None            = 303,  // ��ս����(Ԥ��)

        eType_CountryRaise_Broadcast        = 304,  // ļ��ȫ������
        eType_CountryRaise_None             = 305,  // ļ��ȫ��(Ԥ��)

		eType_Add_Marriage					= 306,  // ���ͨ��
        eType_AddMarriage_None				= 307,  // ���(Ԥ��)

        eType_Country_ChangeName            = 308,  // ���Ĺ��Ź���
        eType_Country_ChangeName_None       = 309,  // ����(Ԥ��)

        eType_Activity_Broadcast            = 310,  // ���������
        eType_Activity_Broadcast_None       = 311,  // �(Ԥ��)

		eType_GuildCamp_Message             = 315,  // ������½���ʾ
		eType_GuildCamp_Message_Failed      = 316,  // ������½Ǵ�����ʾ(��ɫ)

        eType_Exp_Change                    = 317,  // ���鱶�ʵ���
        eType_Exp_Change_None               = 318,  // ���鱶�ʵ���Ԥ��(��ɫ)

        eType_TaskError_PackFull            = 319,  // ���ڰ��������½�����ʧ��
		eType_PetInfo                       = 320,  // ����
		eType_Family						= 321,	// ����
		eType_FamilyEx						= 322,	// �������½���ʾ
		eType_PlayerGuide					= 323,	// �������ָ��
		eType_ScreenCenterCommon			= 324,	// ��Ļ������ʾ�������ʾֻ�漰�ɹ���ʧ�ܵȷ�����Ϣ

        eType_Max
    };

    enum ShowMode
    {
        Mode_None               = 0,
        Mode_BigTitle,
        Mode_SingleLineInfo,
        Mode_RiseInfo,
        Mode_RightListInfo,
        Mode_MultiLineInfo,
        Mode_BottomInfo,
        Mode_MessageBoxInfo,
        Mode_BullSystem,
        Mode_ChatChannel,
        Mode_RandomTip,
        Mode_Max
    };

    // ��������ӦͼƬ��ԴId
    struct MapNameSetting
    {
        MapNameSetting()
        {
            nFrameId = 0;
            nTextId = 0;
        }
        int nFrameId;
        int nTextId;
    };

public:
    ~CScreenInfoManager();

    void ShowInfoByType(    int   nInfoType,                  // ��Ӧ InfoType
             const std::string&   strText,                    // �ı�
                          char*   szToName    = NULL,
                          char*   szItemData  = NULL,
                            int   cntHyber    = 0,
                            int   nBagType    = 0
                            );
    
    // ���أ�����ͳһ BullSystem
    void ShowInfoByType(    int   nInfoType,
             const std::string&   strText,
                            int   nCount,
                     const bool   bPushFront = false 
                            );

    // ���ڸ�ʽ��
    void ShowInfoByFormat(  int   nInfoType,
                    const char*   szFormat,
                            ... );

    void ShowMapNameById( int nMapId );
    void ShowRegionName(const RECT* pRectFontSrc);

    bool LoadScreenInfoConfig( const std::string& strPath );

    // Ϊ���ı����Ըı���Ϣ��ʾ�Ĵ��룬ֻ�ܽ�һ���߼���2������
    void SetUnRiseInfoBegin();
    void SetUnRiseInfoEnd();

    void Render();

    // ������������
    void CalcDestRect( IN OUT RECT& rectDest, const RECT& rectSrc, int CenterX, int CenterY );
    void ShowSafeOrDangerName( const RECT* pRectFontSrc );

protected:
    void RenderMapName();                               // ��Ⱦ������
    void CalcAlpha( int &nAlpha, DWORD nStartTime, bool& );	
    void RenderSafeOrDangerName();

private:
    friend class Singleton<CScreenInfoManager>;
    CScreenInfoManager();
    void RenderRegionName();	

private:
    std::map<int, InfoAttribute>    m_infoAttrMap;

    // ���������
    std::string         m_strMapPicPath;                // ͼƬ·��
    int                 m_nMapFrameY;                   // �װ�Yֵ
    int                 m_nMapTextY;                    // ����Yֵ
    float               m_fMapFrameScale;               // �װ�����
    float               m_fMapTextScale;                // ��������
    DWORD               m_dwMapStatyTime;               // ����ʱ��
    DWORD               m_dwMapFadeinTime;              // ����ʱ��
    DWORD               m_dwMapFadeoutTime;             // ����ʱ��

    DWORD               m_dwMapNameBeginTime;           // ��������ʾʱ��
    bool                m_bShowMapNameBegin;            // ��������ʾ�Ƿ�ʼ
    RECT                m_rcSrcFrame;                   // ��ǰ�������װ�������Դ����
    RECT                m_rcSrcText;                    // ��ǰ����������������Դ����

    std::map<int, RECT>             m_frameRectMap;     // �������װ�������Դ�����
    std::map<int, RECT>             m_textRectMap;      // ����������������Դ�����
    std::map<int, MapNameSetting>   m_mapNameMap;       // ������������Դ���ձ�

    //-----------------------       ������      ------------------------------
    DWORD               m_dwRegionNameBeginTime;        // ��������������ʾʱ��
    bool                m_bShowRegionName;              // ��������������ʾ�Ƿ�ʼ
    RECT                m_rectArtFontSrc;
    RECT                m_rectArtFontDest;
    std::string         m_strArtFont;

    DWORD               m_dwSafeDangerNameBeginTime;
    bool                m_bShowSafeDangerName;
    RECT                m_rectSrc;
    RECT                m_rectDest;

};
