/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\ChatInfoBox.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
// #include "ChatListDlg.h"
#include "FaceDlg1.h"
#include "UIBase.h"
#include "GlobalDef.h"
#include "meui/ControlIconDrag.h"
#include <time.h>
#include <list>
#include <map>
#include "FreeTip.h"
#include "MessageDefine.h"

const int LAST_INFO_MAX		=	10;
const int MAX_FREETIP_COUNT =	3;

class CommonChatFrame 
{
	// Member
public:	
	CommonChatFrame();

	void _Initialize();

	void ClearHyberLinks();

protected:
	ControlFrame*	m_pChatInfoBox;
	ControlEdit*	m_pID_EDIT_INPUT;
	ControlButton*		m_pID_BUTTON_face;
	ControlText*	m_pChatInfoText;
	ControlButton*	m_pID_BUTTON_Enter;
	ControlButton*	m_pID_BUTTON_Bottom;

 	RECT faceRect;
	virtual	bool			IsShow() = 0;
	virtual	void			SetShow(bool bFlag) = 0;
public:
	virtual void			CalFaceRect();
	//--------------------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------------------
// 	enum CHAT_TYPE			//对应发送
// 	{
// 		CHAT_TYPE_NORMAL			= 1 << 1,    //普通聊天
// 		CHAT_TYPE_GUILD				= 1 << 2,    //公会聊天
// 		CHAT_TYPE_TERM				= 1 << 3,    //小队聊天
// 		CHAT_TYPE_PRIVATE			= 1 << 4,    //私聊
// 		CHAT_TYPE_MS				= 1 << 5,    //短信
// 		CHAT_TYPE_GAMEPROMPT		= 1 << 6,    //游戏提示 CHAT_TYPE_GAMEPROMPT
// 		CHAT_TYPE_BULL				= 1 << 7,    //全服公告 GM 运维
// 		CHAT_TYPE_SHOUT				= 1 << 8,    //喊话 区域服务器九宫格
// 		CHAT_TYPE_HIGHSHOUT			= 1 << 9,    //高喊 区域同全服-- 其实用于玩家
// 		CHAT_TYPE_GM				= 1 << 10,   //GM 玩家向GM发送求助信息
// 		CHAT_TYPE_SHOUT_VIP			= 1 << 11,   //喊话 区域服务器九宫格 用于vip的 迷你小喇叭
// 		CHAT_TYPE_HIGHSHOUT_VIP		= 1 << 12,   //高喊 区域同全服--     用于vip的 小喇叭
// 		CHAT_TYPE_BULL_VIP			= 1 << 13,   //全服公告--            用于vip的 麦克风
// 
// 		CHAT_TYPE_PARTICAL1_VIP		= 1 << 14,   //特殊的小道消息 用于vip
// 		CHAT_TYPE_PARTICAL2_VIP		= 1 << 15,   //特殊的小道消息 用于vip
// 		CHAT_TYPE_PARTICAL3_VIP		= 1 << 16,   //特殊的小道消息 用于vip
// 		CHAT_TYPE_PARTICAL4_VIP		= 1 << 17,   //特殊的小道消息 用于vip
// 		CHAT_TYPE_PARTICAL5_VIP		= 1 << 18,   //特殊的小道消息 用于vip
// 		CHAT_TYPE_PARTICAL6_VIP		= 1 << 19,   //特殊的小道消息 用于vip
// 		CHAT_TYPE_PARTICAL7_VIP		= 1 << 20,   //特殊的小道消息 用于vip
// 		CHAT_TYPE_PARTICAL8_VIP		= 1 << 21,   //特殊的小道消息 用于vip
// 		CHAT_TYPE_PARTICAL9_VIP		= 1 << 22,   //特殊的小道消息 用于vip
// 		CHAT_TYPE_PARTICAL10_VIP	= 1 << 23,   //特殊的小道消息 用于vip
// 		CHAT_TYPE_LEAGUE			= 1 << 24,   //联盟聊天
//  		CHAT_TYPE_PROGRAM_SYSTEM	= 1 << 25,   //程序系统通知
//         CHAT_TYPE_FIGHTINFO         = 1 << 26,   //战斗信息
// 		CHAT_TYPE_BATTLE			= 1 << 27,	 //战场阵营频道
// 
// 		CHAT_TYPE_COUNTRY			= 1 << 28,	 //国家频道
// 
// // 
// // 
// // 		CHAT_TYPE_NORMAL = 0,			//普通聊天
// // 		CHAT_TYPE_GUILD,			//公会聊天
// // 		CHAT_TYPE_TERM,				//小队聊天
// // 		CHAT_TYPE_PRIVATE,			//私聊
// // 		CHAT_TYPE_MS,				//短消息系统
// // 		CHAT_TYPE_GAMEPROMPT,				//系统
// // 		CHAT_TYPE_LEAGUE,           //联盟聊天
// // 
// // 		CHAT_TYPE_BULL,				//全服公告--目前只用于gm
// // 		CHAT_TYPE_SHOUT,			//喊话 区域服务器九宫格
// // 		CHAT_TYPE_HIGHSHOUT,		//高喊 区域同全服-- 其实用于玩家
// // 		CHAT_TYPE_GM,				//GM 玩家向GM发送求助信息
// 
// 		CHANNEL_MAX,
// 	};

// 	enum Hyber_Type
// 	{
// 		hyber_init_none,
// 
// 		hyber_one_firstline,					//***************[物品]*******
// 		//****************
// 		hyber_one_firstandsecondline,			//*************************[物
// 		//品]*************
// 		hyber_one_secondline,					//****************************
// 		//*****[物品]*****
// 
// 		hyber_two_all_firstline,				//*****[物品]******[物品]*****
// 		//****************
// 		hyber_two_two_firstandsecondline,		//*****[物品]**************[物
// 		//品]*************
// 		hyber_two_two_secondline,				//*****[物品]*****************
// 		//***[物品]********
// 		hyber_two_first_firstandsecondline,		//*************************[物
// 		//品]*[物品]*******
// 		hyber_two_all_secondline,				//****************************
// 		//*[物品]***[物品]*
// 
// 		hyber_three_all_firstline,				//**[物品]**[物品]****[物品]**
// 		//****************
// 		hyber_three_three_firstandsecondline,	//**[物品]**[物品]**********[物
// 		//品]*************
// 		hyber_three_three_secondline,			//**[物品]**[物品]************
// 		//**[物品]********
// 		hyber_three_two_firstandsecondline,		//**[物品]******************[物
// 		//品]***[物品]****
// 		hyber_three_two_secondline,				//**[物品]********************
// 		//**[物品]**[物品]
// 		hyber_three_first_firstandsecondline,	//**************************[物
// 		//品]**[物品]*[物品]
// 		hyber_three_all_secondline,				//*****************************
// 		//[物品][物品][物品]*
// 
// 		hyber_max
// 	};

	virtual void AddMyChatHistories( const char* szData );
	virtual void ID_EDIT_INPUTOnEditEnter( ControlObject* pSender, const char* szData ) = 0;
	bool ID_BUTTON_faceOnButtonClick( ControlObject* pSender );
	virtual bool ID_BUTTON_EnterOnButtonClick( ControlObject* pSender ){return true;}


	bool OnFrameRun();
	bool OnFrameRender();

	bool	IsFreeTipAllShow() const;

	// 找一个FreeTip的位置id
	int		FindFreeTipPosId() const;

	// 找一个隐藏的FreeTip的id
	FreeTipPos		FindFreeTipId() const;

	static void	ClearNoteId( int tipId );

	// 隐藏所有的FreeTip
	static void	HideAllFreeTip();

	// esc关闭操作
	static bool	EscCloseFreeTip();

	// 指定点是否在指定的FreeTip的Close Btn里有活动，返回一个它的索引
	int		PtInAllFreeTipBtn( int x, int y );

	// 指定点是否在指定的FreeTip里有活动，返回一个它的索引
	int		PtInAllFreeTip( int x, int y );

	// 渲染所有FreeTip
	void	RenderAllFreeTip();

	// 重新设置FreeTip
	void	ResetAllFreeTip();

	int		GetFreeTipState( FreeTipState state );

	// FreeTip移动开始处理
	bool	FreeTipMoveBeginProc( int x, int y );
	bool	FreeTipMoveProc( int x, int y );
	bool	FreeTipMoveEndProc( int x, int y );

	// 显示排序的操作
	static	int		FreeTipPopStack();
	bool			FreeTipPushStack( int tipId );
	void			FreeTipEraseStack( int tipId );
	void			FreeTipSetTop( int tipId );


public:


	void addHyberText( const char* text, __int64 onlyId = 0, int itemid = 0, int nType = 0 );
	void addHyberTextEx( const char* text, uint8 hyberType, int id, int level ); //技能，任务，宠物 等信息发送可能走这个流程

	static void HyberRBtnDown( ControlObject* pSender, const char* szName ,int eHyberType);
	static void HyberItemClick( ControlObject* pSender, unsigned char* pItem);
	static void HyberSkillClick( ControlObject* pSender, void* pData );
	static void HyberTaskClick( ControlObject* pSender, void* pData );
	static void HyberPetClick( ControlObject* pSender, void* pData );
	static void HyberMountClick( ControlObject* pSender, void* pData );

	// 进入物品超链接的回调
	static void HyberItemEnter( ControlObject* pSender, unsigned char* pItem );

	// 离开物品超链接的回调
	static void HyberItemLevel( ControlObject* pSender, unsigned char* pItem );

	static CommonChatFrame*		GetActiveChatFrame();
	static ControlEdit*			GetActiveEditInput();
	static ControlFrame*		GetActiveChatInfoBox();

	static int m_OptFreeTipId;

	static FreeTip m_FreeTip;

	static	FreeTip m_AllFreeTip[MAX_FREETIP_COUNT];
	static	int		m_NoteSort[MAX_FREETIP_COUNT];			// 需求中，左，右顺序加的记录变量
	static	int		m_RenderSort[MAX_FREETIP_COUNT];			// 需求后开先关的记录变量

	void SetPrivateName(const char* szName) { m_szPrivateToName = szName; }
	void SetPrivateToMe(const char* szName) { m_szPrivateToMe = szName; }

	void SetEditFocus();
	void SetEdtActive(bool bFlag);

	void ChangeImmPos();

	std::string	m_szPrivateToName;				//保存私聊对象名字
	std::string	m_szPrivateToMe;				//和我聊天的名字

	bool m_bEdtActive;		//记录输入框时候激活
	bool _bActiveInput;		//是否激活输入框

	bool m_bSendMsg;

	void SetChatType( DWORD dwChatType ){ m_dwChatType = dwChatType; }
	DWORD GetChatType(){ return m_dwChatType; }


	static void		SetActiveChatFrameByEdit(ControlEdit*	pID_EDIT_INPUT);
	static void Task_HyberOtherClick( ControlObject* pSender, const std::string& content ,int nId );

	void InitialCommonChat();

	void Begin2Input();

	void ShowTextInChatList(const std::string& str, const D3DCOLOR col = 0xffffffff,int nConver = MsgChat::CHAT_TYPE_NORMAL, char *szToName = NULL, 
		char* itemData = NULL,int cntHyber = 0, int nBagType = 0, MsgChat* msg = NULL );

	void SendChatMessage(int nDefaultChannel, const char* szData );

	virtual bool MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed ,ControlObject* pSender);
	// 聊天历史记录
	struct ChatHistory
	{
		std::string chatInfo;
		std::vector<__int64> hyberItemInfos;	//保存聊天 物品链接的ID
		std::vector<int> hyberItemIds;
		int			nAddressHyberCnt;
	};

	int			ItemHyberCnt;
	bool		IsSetPet;

	__int64		_HyberItemInfo[ITEM_HYBER_MAX_CNT];	//保存聊天 物品链接的ID
	int			_HyberItemId[ITEM_HYBER_MAX_CNT];
	std::string	_saveItemHyber[ITEM_HYBER_MAX_CNT];
	uint8		_HyberType[ITEM_HYBER_MAX_CNT];
	int			_nBagType;

	int			nAddressHyberCnt;

	typedef std::deque<ChatHistory> ChatHistories;
	ChatHistories chatHistories_;
	int currChatHistoryIndex_;

	static bool				isChatColdTimeXmlLoad;

	static void CommonChatFrame_EditOnLButtonDown(ControlObject* pSender, const char* szData);


	static bool ChatMsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed ,ControlObject* pSender);

	BOOL EditInputIsVisable();

	static void loadXmlChatColdTime();	//加载频道冷却时间 从xml文件读取

	void SetInputText(const char* szText)
	{
		if(szText)
			m_pID_EDIT_INPUT->SetText(szText);
	}

	const char* GetEditText();

	void addText( const char* text);

	bool addAddressText( int nMapId, int nMapX,int nMapY);

	void SendMsgChatNormal(const char* chat);

	void RefreshHyberCnt();
	static void EditDataChange( OUT ControlObject* pSender, OUT const char *szData );

	//---从xml读取的 策划填写的 各个频道的冷却时间
	static clock_t			_tmNormalColdTime;
	static clock_t			_tmGuildColdTime;
	static clock_t			_tmTeamColdTime;
	static clock_t			_tmPrivateColdTime;
	static clock_t			_tmMessageColdTime;
	static clock_t			_tmShoutColdTime;		//大喊 9宫格
	static clock_t			_tmHighShoutColdTime;	//高喊
	static clock_t			_tmLeagueColdTime;	//高喊
	static clock_t			_tmZhenYingColdTime;	//阵营
	static clock_t			_tmCountryColdTime;	//阵营

	clock_t			_tmNormalLastTime;
	clock_t			_tmGuildLastTime;
	clock_t			_tmTeamLastTime;
	clock_t			_tmPrivateLastTime;
	clock_t			_tmMessageLastTime;
	clock_t			_tmShoutLastTime;		//大喊 9宫格
	clock_t			_tmHighShoutLastTime;	//高喊
    clock_t         _tmLeagueLastTime;
	clock_t			_tmZhenYingLastTime;	//阵营
	clock_t			_tmCountryLastTime;	//阵营
private:

	virtual void InializeChatByChannel(){;}

// 	std::vector<std::string> m_lstPrivateName;	//私聊名字列表

	//--------------------------

	static std::string		_strNormalError;	
	static std::string		_strGuildError;	
	static std::string		_strTeamError;			//error 描述信息
	static std::string		_strPrivateError;	
	static std::string		_strMessageError;	
	static std::string		_strShoutError;	
	static std::string		_strHighShoutError;	
    static std::string		_strLeagueError;
	static std::string		_strZhenYingError;
	static std::string		_strCountryError;
	//-----------------------------------------	

    static int              _iNormalLevel;
    static int              _iGuildLevel;
    static int              _iTeamLevel;
    static int              _iPrivateLevel;
	static int              _iMessageLevel;
    static int              _iShoutLevel;
    static int              _iHighShoutLevel;
    static int              _iLeagueLevel;
	static int				_iZhenYingLevel;
	static int				_iCountryLevel;

	static std::vector<std::string> m_vecHelpInfo;	//打印的帮助信息 输入"/help" 的时候

	std::map< __int64, SMountItem > m_mapReceivedMount;

	bool CommandChat(const char *szCommand);			//处理这里的聊天　如快捷输入表情　"\睡觉"  "\n 你好"

	POINT m_ptMouseMove;

	// tip
// 	void ShowItemTip( bool bShow = true );
// 	bool m_bShowTip;
// 	ControlIconDrag::S_ListImg m_ShowItemTip;	
// 	int m_nTipX;
// 	int m_nTipY;

protected:
	DWORD m_dwChatType;


	bool m_bNeedMoveDown; // 聊天列表需要移到最后一行

public:
	int GetFontIndex();
	RECT GetRealRect();
	void SetPos(int x,int y);
	int GetFontSize();
	COLORREF GetFontColor();

	ControlEdit* GetEditInput();
};

inline bool CommonChatFrame::IsFreeTipAllShow() const
{
	for ( int idx = 0; idx < MAX_FREETIP_COUNT; ++idx )
	{
		if ( !m_AllFreeTip[idx].IsVisible() )
		{
			return false;
		}
	}

	return true;
}

inline int CommonChatFrame::FindFreeTipPosId() const
{
	for ( int idx = 0; idx < MAX_FREETIP_COUNT; ++idx )
	{
		if ( m_NoteSort[idx] == -1 )
		{
			return idx;
		}
	}

	return -1;
}

inline FreeTipPos CommonChatFrame::FindFreeTipId() const
{
	for ( int idx = 0; idx < MAX_FREETIP_COUNT; ++idx )
	{
		if ( !m_AllFreeTip[idx].IsVisible() )
		{
			return (FreeTipPos)idx;
		}
	}

	return POS_INVALID;
}

inline void CommonChatFrame::ClearNoteId( int tipId )
{
	for ( int idx = 0; idx < MAX_FREETIP_COUNT; ++idx )
	{
		if ( m_NoteSort[idx] == tipId )
		{
			m_NoteSort[idx] = -1;
			return ;
		}
	}
}
