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

        int     nShowMode;      // 对应显示方式
        int     nColorId;       // 颜色Id
        DWORD   dwTime;         // 持续时间
        bool    bTopLevel;      // 是否置顶
        int     eShowState;     // 淡入淡出
        int     nChatType;      // 聊天频道
        bool    bAutoReply;     // 自动回复
        int     nInfoIndex;     // 此参数已无用
    };

    // 具体Type的用处请参照 ScreenInfo.config
    enum InfoType
    {
        //兼容老接口
        eType_Old_NotProcess                = 0,    // 不处理
        eType_OldScreen_BigTitle,
        eType_OldScreen_NormalTitle,
        eType_OldScreen_Info,
        eType_OldScreen_SmallInfo,
        eType_OldList_Info,

        eType_Map_Name                      = 8,    // 地图名

        eType_Map_FindPathFailed            = 10,   // 不支持跨地图寻路
        eType_Map_BigMapFindPath            = 13,   // 大地图界面寻路
        eType_Map_MiniMapFindPath           = 14,   // 小地图界面寻路
        eType_Map_SearchInfo                = 15,   // 地图查询
        eType_Map_AreaName                  = 16,   // 区域名
        eType_Map_AreaSafe                  = 17,   // 安全区域
        eType_Map_AreaDanger                = 18,   // 危险区域

        eType_Country_DefineBreak           = 20,   // 抵抗入侵信息
        eType_Country_Operate               = 21,   // 国家官员任免、禁言、囚禁、国家任务发布
        eType_Country_OfficialBeKilled      = 22,   // 国家官员被杀
        eType_Item_Get                      = 23,   // 获得物品
        eType_Item_TaskNeed                 = 25,   // 任务所需要条件计数
        eType_Info_ChatSys                  = 27,   // 接受任务、放弃任务
		eType_Info_GuildInfo				= 28,   //帮会系统

        eType_Operate_Failed                = 50,   // 技能（坐骑、采集、装备）条件不满足
        eType_Trade_FailedReason            = 51,   // 交易失败相关提示
        eType_Things_Get                    = 52,   // 获得物品
        eType_Country_Break                 = 53,   // 国家入侵信息
        eType_Skill_ToLearn                 = 54,   // 技能学习
        eType_Skill_Learnt                  = 55,   // 学会了技能
        eType_Item_UseFailed                = 56,   // 物品无法被使用
        eType_Status_Fight                  = 57,   // 战斗状态
        eType_Status_Hook                   = 58,   // 挂机状态
        eType_Shop_Private                  = 59,   // 摆摊提示
        eType_Horse_Tip                     = 60,   // 坐骑相关提示
        eType_Pack_Operate                  = 61,   // 背包物品操作
        eType_Combine_Success               = 62,   // 合成、分解成功
        eType_Combine_Failed                = 63,   // 合成、分解失败
        eType_EquipChange_Success           = 64,   // 换装成功
        eType_EquipChange_Failed            = 65,   // 换装失败
        eType_Trade_Success                 = 66,   // 交易成功
        eType_Trade_Failed                  = 67,   // 交易失败
        eType_Player_Rename                 = 68,   // 玩家重命名
        eType_Fix_Success                   = 69,   // 修理成功
        eType_Fix_Failed                    = 70,   // 修理失败
        eType_NPC_Talk                      = 71,   // NPC对话
        eType_Battle_SignUpSuccess          = 72,   // 战场报名成功
        eType_Follow                        = 73,   // 跟随
        eType_SmallHorn                     = 74,   // 小喇叭
        eType_Item_Arrange                  = 75,   // 分配模式
        eType_Main_Display                  = 76,   // 主界面提示
        eType_AttrFive_Success              = 78,   // 五行成功
        eType_AttrFive_Failed               = 79,   // 五行失败
        eType_OldRiseStar_Success           = 80,   // 升阶成功
        eType_OldRiseStar_Failed            = 81,   // 升阶失败
        eType_Mail_Receive                  = 82,   // 收取邮件
        eType_PickUp                        = 83,   // 拾取
        eType_Gem_Success                   = 84,   // 宝石成功
        eType_Gem_Failed                    = 85,   // 宝石失败
        eType_RiseGold_Success              = 86,   // 鎏金成功
        eType_RiseGold_Failed               = 87,   // 鎏金失败
        eType_Soul_Success                  = 88,   // 铭刻成功
        eType_Soul_Failed                   = 89,   // 铭刻失败
        eType_Maintain_Success              = 90,   // 保值成功
        eType_Maintain_Failed               = 91,   // 保值失败
        eType_MoveStar_Success              = 92,   // 移星成功
        eType_MoveStar_Failed               = 93,   // 移星失败
        eType_Identify                      = 94,   // 鉴定开光鉴定
        eType_Country_Tip                   = 95,   // 国家提示
        eType_Amulet_Success                = 96,   // 护身符成功
        eType_Chat_ChannelTip               = 97,   // 聊天频道提示
        eType_PKMode_Change                 = 98,   // PK模式变更
        eType_Platform_Belongs              = 99,   // 平台相关
        eType_Relive_Belongs                = 100,  // 复活相关
        eType_Guild_Belongs                 = 101,  // 帮会相关
        eType_Produce_Belongs               = 102,  // 生产相关
        eType_RiseStar_Success              = 103,  // 升星成功
        eType_RiseStar_Failed               = 104,  // 升星失败
        eType_Amulet_Failed                 = 105,  // 护身符失败
        eType_OneAnother                    = 106,  // 相依相偎
        eType_Team_MakeGroup                = 107,  // 组队
        eType_Player_Action                 = 108,  // 人物Action
        eType_Teacher_Belongs               = 109,  // 师徒相关
        eType_LevelUp_Belongs               = 110,  // 升级相关
        eType_Friend_Belongs                = 111,  // 好友相关
        eType_Title_Belongs                 = 112,  // 称号相关
        eType_Dual                          = 113,  // 比武提示
        eType_RankList                      = 114,  // 排行榜
        eType_Shop_City                     = 115,  // 商城
        eType_SeekEquip                     = 116,  // 观察
        eType_Mail_Success                  = 117,  // 邮件成功
        eType_Mail_Failed                   = 118,  // 邮件失败
        eType_Consignment_Success           = 119,  // 寄售成功
                                                       
        eType_Player_AttrUp                 = 120,  // 换装属性变高
                                                 
        eType_Consignment_Failed            = 121,  // 寄售失败
        eType_Battle_Success                = 122,  // 战场成功
        eType_Battle_Failed                 = 123,  // 战场失败
        eType_Ectype_Success                = 124,  // 副本成功
                                                  
        eType_SendFlower                    = 125,  // 送花
                                                  
        eType_Ectype_Failed                 = 126,  // 副本失败
                                                   
        eType_SendFlower_RandomTip          = 127,  // 送花公告内小提示

        eType_Store_Password                = 130,  // 仓库密码
        eType_Wealth_Protect                = 132,  // 财产保护设置
        eType_Addict_Protect                = 133,  // 防沉迷
        eType_MapChange_Failed              = 134,  // 地图跳转人满
                                                   
        eType_Marry_Success                 = 200,  // 结婚成功
        eType_Marry_Failed                  = 201,  // 结婚失败
        eType_Present_SendSuccess           = 202,  // 送礼成功
        eType_Present_SendFailed            = 203,  // 送礼失败
                                                   
        eType_Reputation_Change             = 204,  // 声望改变
        eType_Exploit_Change                = 205,  // 功勋改变
        eType_PKValue_Change                = 206,  // PK值改变
        eType_Money_Change                  = 207,  // 金钱改变
        eType_Honor_Change                  = 208,  // 荣誉改变
        eType_Prestige_Change               = 209,  // 威望改变

        eType_Invite_Guild                  = 210,  // 公会邀请
        eType_Invite_Team                   = 211,  // 组队邀请
                                                   
        eType_Kill_Info                     = 212,  // 杀人
        eType_BeKilled_Info                 = 213,  // 被杀
                                                   
        eType_Script_Tell                   = 214,  // tell过来的
                                                    
        eType_Player_AttrDown               = 215,  // 换装属性变低
        eType_UnRiseInfo_RandomTip          = 216,  // 换装属性内小提示
        eType_ListInfo_RandomTip            = 217,  // 右下角小提示
        eType_RiseInfo_RandomTip            = 218,  // 向上顶处小提示
        eType_SysInfo_RandomTip             = 219,  // 不向上顶处小提示
        eType_BigTile_RandomTip             = 220,  // 地图名处小提示
                                                    
        eType_Bull_System                   = 221,  // 系统
        eType_Bull_Broadcast                = 222,  // 公告
        eType_Bull_RandomTip                = 223,  // 系统公告内小提示
                                                   
        eType_Chat_RandomTip                = 224,  // 聊天内小提示
        eType_Tip_RandomTip                 = 225,  // 小提示
                                                   
        //来自服务器的                            
        eType_Server_MapSuccess             = 250,  // 地图相关字串
        eType_Server_MapError               = 251,  // 地图相关字串错误
        eType_Server_PlayerMatch_Success    = 252,  // 玩家没有匹配上
        eType_Server_PlayerMatch_Error      = 253,  // 玩家没有匹配上错误
        eType_Server_TeamTask_Success       = 254,  // 更新队伍任务相关
        eType_Server_TeamTask_Error         = 255,  // 更新队伍任务相关错误
        eType_Server_MoveCheck_Success      = 256,  // CheckMovingMsgSendTime
        eType_Server_MoveCheck_Error        = 257,  // CheckMovingMsgSendTime错误
        eType_Server_PickItem_Success       = 258,  // PickItem
        eType_Server_PickItem_Error         = 259,  // PickItem错误
        eType_Server_QuestState_Success     = 260,  // 设置任务状态
        eType_Server_QuestState_Error       = 261,  // 设置任务状态错误
        eType_Server_DataRefresh_Success    = 262,  // 刷新char数据
        eType_Server_DataRefresh_Error      = 263,  // 刷新char数据错误
        eType_Server_PrivateShop_Success    = 264,  // 个人摆摊
        eType_Server_PrivateShop_Error      = 265,  // 个人摆摊错误
        eType_Server_Attack_Success         = 266,  // 普通攻击
        eType_Server_Attack_Error           = 267,  // 普通攻击错误
        eType_Server_Mount_Success          = 268,  // 坐骑
        eType_Server_Mount_Error            = 269,  // 坐骑错误
        eType_Server_UseItem_Success        = 270,  // 使用物品
        eType_Server_UseItem_Error          = 271,  // 使用物品错误
        eType_Server_GetItem_Success        = 272,  // 获取物品
        eType_Server_GetItem_Error          = 273,  // 获取物品错误
        eType_Server_ScriptItem_Success     = 274,  // 脚本获得物品
        eType_Server_ScriptItem_Error       = 275,  // 脚本获得物品错误
        eType_Server_GraphicCode_Success    = 276,  // 请求验证码
        eType_Server_GraphicCode_Error      = 277,  // 请求验证码错误
        eType_Server_EnterWorld_Success     = 278,  // 角色进入
        eType_Server_EnterWorld_Error       = 279,  // 角色进入错误
        eType_Server_Exit_Success           = 280,  // 退出游戏服务器
        eType_Server_Exit_Error             = 281,  // 退出游戏服务器错误
        eType_Server_Others_Success         = 282,  // 其他
        eType_Server_Others_Error           = 283,  // 其他错误
        eType_Server_Max                    = 284,  // 服务器发送最大值

        // 脚本
        eType_Script_TalkGreen              = 285,  // Talk绿色
        eType_Script_TalkYellow             = 286,  // Talk黄色
        eType_Script_TalkRed                = 287,  // Talk红色
        eType_Script_TalkPurple             = 288,  // Talk紫色

        eType_HookOffline_Success           = 290,  // 离线挂机成功
        eType_HookOffline_Failed            = 291,  // 离线挂机失败
        eType_Honor_Get                     = 292,  // 获得荣誉值
        eType_Honor_Error                   = 293,  // 荣誉值错误

        eType_CountryBetray_Success         = 294,  // 叛国成功
        eType_CountryBetray_Failed          = 295,  // 叛国失败

		eType_FullBufRelive_Failed          = 297,	// 信春哥失败
		
		//师徒部分提示信息在屏幕中间
		eType_ShiTu_Belongs_Success         = 298,  // 
		eType_ShiTu_Belongs_Failed          = 299,  // 
		eType_Achievement					= 300,  // 成就成功
        eType_Achievement_Failed            = 301,  // 成就失败

        eType_CountryBattle_Broadcast       = 302,  // 国战公告
        eType_CountryBattle_None            = 303,  // 国战公告(预留)

        eType_CountryRaise_Broadcast        = 304,  // 募捐全服公告
        eType_CountryRaise_None             = 305,  // 募捐全服(预留)

		eType_Add_Marriage					= 306,  // 结婚通告
        eType_AddMarriage_None				= 307,  // 结婚(预留)

        eType_Country_ChangeName            = 308,  // 更改国号公告
        eType_Country_ChangeName_None       = 309,  // 国号(预留)

        eType_Activity_Broadcast            = 310,  // 活动开启公告
        eType_Activity_Broadcast_None       = 311,  // 活动(预留)

		eType_GuildCamp_Message             = 315,  // 帮会右下角提示
		eType_GuildCamp_Message_Failed      = 316,  // 帮会右下角错误提示(红色)

        eType_Exp_Change                    = 317,  // 经验倍率调整
        eType_Exp_Change_None               = 318,  // 经验倍率调整预留(红色)

        eType_TaskError_PackFull            = 319,  // 由于包裹满导致交任务失败
		eType_PetInfo                       = 320,  // 宠物
		eType_Family						= 321,	// 家族
		eType_FamilyEx						= 322,	// 家族右下角提示
		eType_PlayerGuide					= 323,	// 玩家新手指引
		eType_ScreenCenterCommon			= 324,	// 屏幕中央提示，这个提示只涉及成功和失败等反馈信息

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

    // 场景名对应图片资源Id
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

    void ShowInfoByType(    int   nInfoType,                  // 对应 InfoType
             const std::string&   strText,                    // 文本
                          char*   szToName    = NULL,
                          char*   szItemData  = NULL,
                            int   cntHyber    = 0,
                            int   nBagType    = 0
                            );
    
    // 重载，用于统一 BullSystem
    void ShowInfoByType(    int   nInfoType,
             const std::string&   strText,
                            int   nCount,
                     const bool   bPushFront = false 
                            );

    // 用于格式化
    void ShowInfoByFormat(  int   nInfoType,
                    const char*   szFormat,
                            ... );

    void ShowMapNameById( int nMapId );
    void ShowRegionName(const RECT* pRectFontSrc);

    bool LoadScreenInfoConfig( const std::string& strPath );

    // 为不改变属性改变信息显示的代码，只能将一个逻辑分2部分做
    void SetUnRiseInfoBegin();
    void SetUnRiseInfoEnd();

    void Render();

    // 区域名美术字
    void CalcDestRect( IN OUT RECT& rectDest, const RECT& rectSrc, int CenterX, int CenterY );
    void ShowSafeOrDangerName( const RECT* pRectFontSrc );

protected:
    void RenderMapName();                               // 渲染场景名
    void CalcAlpha( int &nAlpha, DWORD nStartTime, bool& );	
    void RenderSafeOrDangerName();

private:
    friend class Singleton<CScreenInfoManager>;
    CScreenInfoManager();
    void RenderRegionName();	

private:
    std::map<int, InfoAttribute>    m_infoAttrMap;

    // 场景名相关
    std::string         m_strMapPicPath;                // 图片路径
    int                 m_nMapFrameY;                   // 底板Y值
    int                 m_nMapTextY;                    // 文字Y值
    float               m_fMapFrameScale;               // 底板缩放
    float               m_fMapTextScale;                // 文字缩放
    DWORD               m_dwMapStatyTime;               // 持续时间
    DWORD               m_dwMapFadeinTime;              // 淡入时间
    DWORD               m_dwMapFadeoutTime;             // 淡出时间

    DWORD               m_dwMapNameBeginTime;           // 场景名显示时间
    bool                m_bShowMapNameBegin;            // 场景名显示是否开始
    RECT                m_rcSrcFrame;                   // 当前场景名底板美术资源区域
    RECT                m_rcSrcText;                    // 当前场景名文字美术资源区域

    std::map<int, RECT>             m_frameRectMap;     // 场景名底板美术资源区域表
    std::map<int, RECT>             m_textRectMap;      // 场景名文字美术资源区域表
    std::map<int, MapNameSetting>   m_mapNameMap;       // 场景名美术资源对照表

    //-----------------------       美术字      ------------------------------
    DWORD               m_dwRegionNameBeginTime;        // 场景名美术字显示时间
    bool                m_bShowRegionName;              // 场景名美术字显示是否开始
    RECT                m_rectArtFontSrc;
    RECT                m_rectArtFontDest;
    std::string         m_strArtFont;

    DWORD               m_dwSafeDangerNameBeginTime;
    bool                m_bShowSafeDangerName;
    RECT                m_rectSrc;
    RECT                m_rectDest;

};
