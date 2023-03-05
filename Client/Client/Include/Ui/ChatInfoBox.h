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
#include "CommonChatFrame.h"
#ifndef ChatInfoBox
#define ChatInfoBox		"ChatInfoBox"
#endif  ChatInfoBox
#ifndef ID_PICTURE_BgInput
#define ID_PICTURE_BgInput		"ID_PICTURE_BgInput"
#endif  ID_PICTURE_BgInput
#ifndef ID_EDIT_INPUT
#define ID_EDIT_INPUT		"ID_EDIT_INPUT"
#endif  ID_EDIT_INPUT
#ifndef ID_BUTTON_Enter
#define ID_BUTTON_Enter		"ID_BUTTON_Enter"
#endif  ID_BUTTON_Enter
#ifndef ID_BUTTON_face
#define ID_BUTTON_face		"ID_BUTTON_face"
#endif  ID_BUTTON_face
#ifndef ID_BUTTON_Horn
#define ID_BUTTON_Horn		"ID_BUTTON_Horn"
#endif  ID_BUTTON_Horn
#ifndef ID_BUTTON_ChatPrivate
#define ID_BUTTON_ChatPrivate		"ID_BUTTON_ChatPrivate"
#endif  ID_BUTTON_ChatPrivate
#ifndef ID_BUTTON_BTeam
#define ID_BUTTON_BTeam		"ID_BUTTON_BTeam"
#endif  ID_BUTTON_BTeam
#ifndef ID_BUTTON_BGuild1
#define ID_BUTTON_BGuild1		"ID_BUTTON_BGuild1"
#endif  ID_BUTTON_BGuild1
#ifndef ID_BUTTON_BCountry
#define ID_BUTTON_BCountry		"ID_BUTTON_BCountry"
#endif  ID_BUTTON_BCountry
#ifndef ID_BUTTON_BHightShout
#define ID_BUTTON_BHightShout		"ID_BUTTON_BHightShout"
#endif  ID_BUTTON_BHightShout
#ifndef ID_PICTURE_Di
#define ID_PICTURE_Di		"ID_PICTURE_Di"
#endif  ID_PICTURE_Di
#ifndef ID_CHECKBOX_BHightShout
#define ID_CHECKBOX_BHightShout		"ID_CHECKBOX_BHightShout"
#endif  ID_CHECKBOX_BHightShout
#ifndef ID_CHECKBOX_BCountry
#define ID_CHECKBOX_BCountry		"ID_CHECKBOX_BCountry"
#endif  ID_CHECKBOX_BCountry
#ifndef ID_CHECKBOX_BGuild1
#define ID_CHECKBOX_BGuild1		"ID_CHECKBOX_BGuild1"
#endif  ID_CHECKBOX_BGuild1
#ifndef ID_CHECKBOX_BTeam
#define ID_CHECKBOX_BTeam		"ID_CHECKBOX_BTeam"
#endif  ID_CHECKBOX_BTeam
#ifndef ID_CHECKBOX_ChatPrivate
#define ID_CHECKBOX_ChatPrivate		"ID_CHECKBOX_ChatPrivate"
#endif  ID_CHECKBOX_ChatPrivate
#ifndef ID_CHECKBOX_BPublic
#define ID_CHECKBOX_BPublic		"ID_CHECKBOX_BPublic"
#endif  ID_CHECKBOX_BPublic
#ifndef ID_BUTTON_ChatOutType
#define ID_BUTTON_ChatOutType		"ID_BUTTON_ChatOutType"
#endif  ID_BUTTON_ChatOutType
#ifndef ID_BUTTON_PinBi
#define ID_BUTTON_PinBi		"ID_BUTTON_PinBi"
#endif  ID_BUTTON_PinBi

#ifndef ID_BUTTON_Family
#define ID_BUTTON_Family		"ID_BUTTON_Family"
#endif  ID_BUTTON_Family

#ifndef ID_CHECKBOX_Family
#define ID_CHECKBOX_Family		"ID_CHECKBOX_Family"
#endif  ID_CHECKBOX_Family

//lyh++ 

#ifndef ID_BUTTON_GuanYuan
#define ID_BUTTON_GuanYuan		"ID_BUTTON_GuanYuan"
#endif  ID_BUTTON_GuanYuan

#ifndef ID_CHECKBOX_GuanYuan
#define ID_CHECKBOX_GuanYuan		"ID_CHECKBOX_GuanYuan"
#endif  ID_CHECKBOX_GuanYuan

const int MAX_CHANNEL		=	8;		//（8个聊天频道）修改现在是9
const int MAX_FRAMETIME		=	2;	//聊天面板消失时间
const int MAX_USERINFO		=	7;
const int BLEND_CHATDLG		=	0x88;	//聊天面板的透明值
const DWORD CHAT_BG			=	0x7f000000;
const int MAX_SHOWITEMNUMBER =	20;

#define SYSTEM_COLOR 0xffffff00

class CUI_ChatInfoBox :  public CommonChatFrame,public CUIBase
{
	// Member
public:	
	CUI_ChatInfoBox();
    virtual bool IsHoldInMemory() const { return true; }
    virtual void InitializeAtEnterWorld();
	enum CHAT_TYPE
	{//聊天类型
		CHAT_TEAM,
		CHAT_GUILD,
		CHAT_COUNTRY,
		CHAT_PUBLIC,
		CHAT_PRIVATE,
		CHAT_FAMILY,
		CHAT_GY,

		CHAT_MAX,
	};
private:
	ControlPicture*	m_pID_PICTURE_BgInput;
	ControlButton*	m_pID_BUTTON_Enter;
	ControlButton*	m_pID_BUTTON_face;
	ControlButton*	m_pID_BUTTON_Horn;
	ControlButton*	m_pID_BUTTON_ChatPrivate;
	ControlButton*	m_pID_BUTTON_BTeam;
	ControlButton*	m_pID_BUTTON_BGuild1;
	ControlButton*	m_pID_BUTTON_BCountry;
	ControlButton*	m_pID_BUTTON_BHightShout;
	ControlPicture*	m_pID_PICTURE_Di;
	ControlCheckBox*	m_pID_CHECKBOX_BHightShout;
	ControlCheckBox*	m_pID_CHECKBOX_BCountry;
	ControlCheckBox*	m_pID_CHECKBOX_BGuild1;
	ControlCheckBox*	m_pID_CHECKBOX_BTeam;
	ControlCheckBox*	m_pID_CHECKBOX_ChatPrivate;
	ControlCheckBox*	m_pID_CHECKBOX_BPublic;
   
	//lyh++ 官员频道按钮
   ControlCheckBox*	m_pID_CHECKBOX_BGuanYuan;
   ControlButton*	m_pID_BUTTON_BGuanYuan;

	ControlButton*	m_pID_BUTTON_ChatOutType;

	ControlButton*		m_pID_BUTTON_PinBi;

	ControlButton*	m_pID_BUTTON_Family;
	ControlCheckBox*	m_pID_CHECKBOX_Family;

	ControlRadioGroup	m_channelRadioGroup;
	ControlGroup		m_receiveRadioGroup;
	ControlGroup		m_channelGroup;
public:
	// Frame
	bool ID_BUTTON_ChatOutTypeOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ChatPrivateOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_BTeamOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_BGuild1OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_BCountryOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_BHightShoutOnButtonClick( ControlObject* pSender );
	virtual void ID_EDIT_INPUTOnEditEnter( ControlObject* pSender, const char* szData );

	//void ID_CHECKBOX_NormalOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_PinBiOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_HornOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_BPublicOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_BTeamOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_BGuild1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_BHightShoutOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_BCountryOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	//void ID_CHECKBOX_BZhenying2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_ChatPrivateOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	virtual bool ID_BUTTON_EnterOnButtonClick( ControlObject* pSender );
	//void ID_CHECKBOX_BZhenyingOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	bool ID_BUTTON_FamilyOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_FamilyOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

    //lyh++
	void ID_CHECKBOX_GuanYuanOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_GuanYuanOnButtonClick( ControlObject* pSender );

	
	void SetChatTypeChannel(unsigned int type);  //用来对外提供设置当前聊天频道的接口
	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	virtual	bool			IsShow() {return IsVisable();}
	virtual	void			SetShow(bool bFlag) {SetVisable(bFlag);}

	bool OnClickChannelButton(void);

public:
	//--------------------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------------------
	static void HyberClickPrivateChat( ControlObject* pSender, const char* szName );
	void AddInfo( const std::string& str, const D3DCOLOR col = 0xffffffff, const UINT nType = MsgChat::CHAT_TYPE_GAMEPROMPT, char *szToName = NULL, 
		char* itemData = NULL, int cntHyber = 0, int nBagType = 0, bool bAutoReply = false, MsgChat* msg = NULL );
	void Begin2Secret( const char* szStr);	//开始对某某某说悄悄话 szStr 为某某某的名字

	void Refresh(int nStartIndex);

	virtual void ClearChat();
	void ClearChatShow();

	// added, jiayi, [2009/11/19]
	void SetChatChannelIndex( int nIndex );
	int GetChatChannelIndex(){ return m_nChatChannelIndex; }

	unsigned int GetCurrChatInfoIndex() const { return m_nCurrChatInfoIndex; }

	int		GetDefalutChannel() const				{ return _nDefaultChannel; }
	int		GetCurrentChannel()	const				{ return _nCurrentChannel; }
	void	SetCurrentChannel(int nChannle)
	{
		if( nChannle < MsgChat::CHAT_TYPE_NORMAL || nChannle > MsgChat::CHAT_TYPE_COUNTRYOFFICIAL) //lyh++
			return;
		_nCurrentChannel = nChannle; 
	}

	void r_ShortcutPrivate();	//r 键 快捷恢复私聊
	void AddPrivateUser(const char *szUser);			//添加私聊对象
	void ClearChatInfoList() { m_pChatInfoText = NULL; }
protected:
	virtual void			CalFaceRect();

	virtual void InializeChatByChannel();
	virtual bool MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed ,ControlObject* pSender);
	void SetChatOutTypeText(const char* szText)
	{
		//if(szText && m_pID_BUTTON_ChatOutType )
		//	m_pID_BUTTON_ChatOutType->SetCaption(szText);
	}

	void SetChatOutTypeButton(ControlObject *pSender_);
	//频道的控制
	int		_nDefaultChannel;//默认保存的频道 即chatout按钮显示的什么 只能通过鼠标点击更改 频道 回车打开输入框取这个频道
	int		_nCurrentChannel;//保存当前的频道 即由输入框可以直接控制输出的频道 lua取这个频道


	void ToggleNext();
	void ToggleChannel(ControlObject* pSender, int type);	
	void SetChatColor(D3DCOLOR color);

	struct ChatInfo
	{
		std::string text;
		std::string toName;
		D3DCOLOR color;
		UINT nType;
		int cntHyber;
		int nBagType;
		unsigned int			nChatInfoIndex;
		SCharItem normalItems[ITEM_HYBER_MAX_CNT];
		SMountItem mountItems[ITEM_HYBER_MAX_CNT];
		SPetItem   petItems[ITEM_HYBER_MAX_CNT];
	};

	std::list<ChatInfo> m_chatInfos;
	bool m_bAddChatInfo;
	void _Refresh(int nStartIndex);
	unsigned int			m_nCurrChatInfoIndex;
protected:
	int			m_nChatChannelIndex;

	// 频道命令
public:
	struct ChatCommand
	{
		int iChatType;
		std::string strCommandCn;	// 中文命令
		std::string strCommandEn;	// 英文命令
	};

protected:
	void LoadChatCommand();
	void ProcessAndSendChatMessage(int nDefaultChannel, const char* szData);	// 分析频道命令，发送聊天消息

	std::vector<ChatCommand> m_vecChatCommand;

};
extern CUI_ChatInfoBox s_CUI_ChatInfoBox;
