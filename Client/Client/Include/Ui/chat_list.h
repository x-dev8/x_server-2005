/********************************************************************
Created by UIEditor.exe
FileName: D:\Tj\Client\UI\chat_list.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_BUTTON_Diaphaneity
#define ID_BUTTON_Diaphaneity		"ID_BUTTON_Diaphaneity"
#endif  ID_BUTTON_Diaphaneity
#ifndef ID_FRAME_chatInfoList
#define ID_FRAME_chatInfoList		"ID_FRAME_chatInfoList"
#endif  ID_FRAME_chatInfoList
#ifndef ID_BUTTON_Tuodong
#define ID_BUTTON_Tuodong		"ID_BUTTON_Tuodong"
#endif  ID_BUTTON_Tuodong
#ifndef ID_PICTURE_Di
#define ID_PICTURE_Di		"ID_PICTURE_Di"
#endif  ID_PICTURE_Di
#ifndef ID_BUTTON_Clear
#define ID_BUTTON_Clear		"ID_BUTTON_Clear"
#endif  ID_BUTTON_Clear
#ifndef ID_BUTTON_ChatSet
#define ID_BUTTON_ChatSet		"ID_BUTTON_ChatSet"
#endif  ID_BUTTON_ChatSet
#ifndef ID_CHECKBOX_Channel1
#define ID_CHECKBOX_Channel1		"ID_CHECKBOX_Channel1"
#endif  ID_CHECKBOX_Channel1
#ifndef ID_TEXT_Light
#define ID_TEXT_Light		"ID_TEXT_Light"
#endif  ID_TEXT_Light
#ifndef ID_CHECKBOX_Channel2
#define ID_CHECKBOX_Channel2		"ID_CHECKBOX_Channel2"
#endif  ID_CHECKBOX_Channel2
#ifndef ID_CHECKBOX_Channel3
#define ID_CHECKBOX_Channel3		"ID_CHECKBOX_Channel3"
#endif  ID_CHECKBOX_Channel3
#ifndef ID_CHECKBOX_Channel4
#define ID_CHECKBOX_Channel4		"ID_CHECKBOX_Channel4"
#endif  ID_CHECKBOX_Channel4
#ifndef ID_CHECKBOX_Channel5
#define ID_CHECKBOX_Channel5		"ID_CHECKBOX_Channel5"
#endif  ID_CHECKBOX_Channel5
#ifndef ID_CHECKBOX_Channel6
#define ID_CHECKBOX_Channel6		"ID_CHECKBOX_Channel6"
#endif  ID_CHECKBOX_Channel6
#ifndef ID_CHECKBOX_Channel7
#define ID_CHECKBOX_Channel7		"ID_CHECKBOX_Channel7"
#endif  ID_CHECKBOX_Channel7
#ifndef ID_CHECKBOX_Channel8
#define ID_CHECKBOX_Channel8		"ID_CHECKBOX_Channel8"
#endif  ID_CHECKBOX_Channel8
#ifndef ID_CHECKBOX_Channel9
#define ID_CHECKBOX_Channel9		"ID_CHECKBOX_Channel9"
#endif  ID_CHECKBOX_Channel9

//lyh做官员聊天频道
#ifndef ID_CHECKBOX_Channel11
#define ID_CHECKBOX_Channel11		"ID_CHECKBOX_Channel11"
#endif  ID_CHECKBOX_Channel11


//#ifndef ID_BUTTON_Action
//#define ID_BUTTON_Action		"ID_BUTTON_Action"
//#endif  ID_BUTTON_Action
#ifndef ID_BUTTON_History
#define ID_BUTTON_History		"ID_BUTTON_History"
#endif  ID_BUTTON_History
//#ifndef ID_BUTTON_Horn
//#define ID_BUTTON_Horn		"ID_BUTTON_Horn"
//#endif  ID_BUTTON_Horn
#ifndef ID_BUTTON_Save
#define ID_BUTTON_Save		"ID_BUTTON_Save"
#endif  ID_BUTTON_Save
#ifndef ID_Text_Info
#define ID_Text_Info		"ID_Text_Info"
#endif  ID_Text_Info
#ifndef ID_Text_HornInfo
#define ID_Text_HornInfo		"ID_Text_HornInfo"
#endif  ID_Text_HornInfo
#ifndef ID_BUTTON_Low
#define ID_BUTTON_Low		"ID_BUTTON_Low"
#endif  ID_BUTTON_Low
#ifndef ID_BUTTON_Show
#define ID_BUTTON_Show		"ID_BUTTON_Show"
#endif  ID_BUTTON_Show
#ifndef ID_BUTTON_Hide
#define ID_BUTTON_Hide		"ID_BUTTON_Hide"
#endif  ID_BUTTON_Hide
#ifndef ID_BUTTON_Open
#define ID_BUTTON_Open		"ID_BUTTON_Open"
#endif  ID_BUTTON_Open
#ifndef ID_PICTURE_OpenBg
#define ID_PICTURE_OpenBg		"ID_PICTURE_OpenBg"
#endif  ID_PICTURE_OpenBg
#ifndef ID_PROGRESS_Low
#define ID_PROGRESS_Low		"ID_PROGRESS_Low"
#endif  ID_PROGRESS_Low
#ifndef ID_PROGRESS_Horn
#define ID_PROGRESS_Horn		"ID_PROGRESS_Horn"
#endif  ID_PROGRESS_Horn

#ifndef ID_CHECKBOX_Channel10
#define ID_CHECKBOX_Channel10		"ID_CHECKBOX_Channel10"
#endif  ID_CHECKBOX_Channel10

#ifndef ID_PICTURE_SHOUT
#define ID_PICTURE_SHOUT		"ID_PICTURE_SHOUT"
#endif  ID_PICTURE_SHOUT


#define MAX_CHANNELTAB_COUNT 11

#include "UiBase.h"
class CUI_ID_FRAME_chatInfoList :public CUIBase
{
	// GuildMember
public:	
	CUI_ID_FRAME_chatInfoList();
private:
	ControlFrame*	    m_pID_FRAME_chatInfoList;
	ControlButton*	    m_pID_BUTTON_Tuodong;
	ControlButton*	    m_pID_BUTTON_Diaphaneity;
    ControlPicture*	    m_pID_PICTURE_Di;
    ControlButton*	    m_pID_BUTTON_ChatSet;
    ControlCheckBox*	m_pID_CHECKBOX_Channel1;
    ControlCheckBox*	m_pID_CHECKBOX_Channel2;
    ControlCheckBox*	m_pID_CHECKBOX_Channel3;
    ControlCheckBox*	m_pID_CHECKBOX_Channel4;
    ControlCheckBox*	m_pID_CHECKBOX_Channel5;
    ControlCheckBox*	m_pID_CHECKBOX_Channel6;
    ControlCheckBox*	m_pID_CHECKBOX_Channel7;
    ControlCheckBox*	m_pID_CHECKBOX_Channel8;
    ControlCheckBox*	m_pID_CHECKBOX_Channel9;
    ControlButton*	    m_pID_BUTTON_Clear;
    //ControlButton*	    m_pID_BUTTON_Action;
    ControlButton*	    m_pID_BUTTON_History;
    //ControlButton*	    m_pID_BUTTON_Horn;
    //ControlButton*	m_pID_BUTTON_Save;
    ControlText*	    m_pID_Text_Info;
    ControlText*	    m_pID_Text_HornInfo;
    ControlButton*	    m_pID_BUTTON_Low;
    ControlButton*	    m_pID_BUTTON_Show;
    ControlButton*	    m_pID_BUTTON_Hide;
    ControlButton*	    m_pID_BUTTON_Open;
    ControlPicture*     m_pID_PICTURE_OpenBg;

    ControlGroup	    m_groupSet;
    ControlGroup        m_listGroup;
	ControlTabGroup     m_tabGroup;
    ControlGroup        m_groupAll;
    ControlGroup        m_groupMenu;
	ControlProgress*	m_pID_PROGRESS_Low;
	ControlProgress*	m_pID_PROGRESS_Horn;

	ControlCheckBox*	m_pID_CHECKBOX_Channel10;
	ControlCheckBox*    m_pID_CHECKBOX_Channel11;
	ControlPicture*		m_pID_PICTURE_SHOUT;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_Text_InfoOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_ClearOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ChatSetOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_Channel1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Channel2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Channel3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Channel4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
    void ID_CHECKBOX_Channel5OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
    void ID_CHECKBOX_Channel6OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
    void ID_CHECKBOX_Channel7OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
    void ID_CHECKBOX_Channel8OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
    void ID_CHECKBOX_Channel9OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	//bool ID_BUTTON_ActionOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HistoryOnButtonClick( ControlObject* pSender );
	//bool ID_BUTTON_HornOnButtonClick( ControlObject* pSender );
	//bool ID_BUTTON_SaveOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_LowOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DiaphaneityOnButtonClick(ControlObject* pSender);
    bool ID_BUTTON_ShowOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_HideOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_OpenOnButtonClick( ControlObject* pSender );

	void ID_CHECKBOX_Channel10OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Channel11OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	
	virtual bool IsHoldInMemory() const { return true; }
    virtual void InitializeAtEnterWorld();

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	        // 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	virtual void ResetDevice();

public:
	void RenderTip();			// 渲染tip，放在ui后面
	void RefreshChannel();
	void RefreshChannelVisible( bool bVisible );
	void ShowChildrenUI(bool bVisible);
    void SetChatListChanged() { m_bChatListChanged = true; }
	void SetButtonToudongVisable( bool b );
	bool IsButtonToudongVisable();
	bool IsPtInObjectTuodong( INT x,INT y );
	EKeyType PtInHyberListInfo( INT x,INT y );
	bool IsPtInListObject( INT x,INT y  );
	ControlText* GetpIDTextInfo(){ return m_pID_Text_Info; }
	ControlText* GetpIDTextHorn(){ return m_pID_Text_HornInfo; }
	ControlProgress *GetpHornProgress(){ return m_pID_PROGRESS_Horn; }
	void ListInfoClear();
	void HornInfoClear();
	bool IsListInfoVisable();
	RECT GetPictureDi();
	void SetPictureDi( RECT* rect );
	RECT GetChatInfoListSize();
	void SetChatInfoListSize( RECT* rect );
	RECT GetListInfoSize();
	void SetListInfoSize( RECT* rect );
	RECT GetHornInfoSize();
	void SetHornInfoSize( RECT* rect );
	RECT GetHornProgressSize();
	void SetHornProgressSize( RECT* rect );
	void SetChangeSize(int size) { m_bChangeSize = size; }
	int GetChangeSize() { return m_bChangeSize; }
	int GetOldMousePosX() { return m_nOldMousePosX; }
	int GetOldMousePosY() { return m_nOldMousePosY; }
	void SetOldMousePosX(int x) { m_nOldMousePosX = x; }
	void SetOldMousePosY(int y) { m_nOldMousePosY = y; }
	int GetMinWidth() { return m_nMinWidth; }
	int GetMinHeight() { return m_nMinHeight; }
	int GetChannelStartIndex(int nIndex) const { return m_ChannelStartIndex[nIndex]; }
	bool IsInMaxFrame(int x, int y);
    
    // 杨凯需求
    void SetRealAlpha( float fAlpha );
    float GetRealAlpha();
    void SetTempAlpha( float fAlpha );
    void ShowAll( bool bShow );
    void VisableBtns( bool bVisable );
	void ShowGroupMenu( bool bShow ){m_groupMenu.SetVisible(bShow);}
    static void FrameMouseEnter( ControlObject* pSender );
    static void FrameMouseLeave( ControlObject* pSender );
	void	ShowLowButtonEffect(bool bShow){if (m_pID_PROGRESS_Low)	m_pID_PROGRESS_Low->SetVisable(bShow);}

	static bool ChangeSizeToPoint( int nX, int nY, bool bByDeviceReset = false );

private:

	// 进入聊天按钮区事件
	void OnEnterAndLeaveChatBtnAreaEvent( int x, int y );

	void OnEnterBtnArea();
	void OnLeaveBtnArea();

public:
	static const int MaxHornTextLength = 32;

protected:
	int					m_nOldMousePosX;
	int					m_nOldMousePosY;
	int					m_bChangeSize;
	int					m_nMinWidth;
	int					m_nMinHeight;
	float				m_fAlpha;			// 本界面的Alpha
	float				m_fAlphaSet;		// 设置本界面与InfoList界面的Alpha

	ControlCheckBox*	m_ChannelCtrl[MAX_CHANNELTAB_COUNT];
	int					m_ChannelStartIndex[MAX_CHANNELTAB_COUNT];

	bool				m_bChatListChanged;    // 聊天列表是否有变化

	RECT				m_ChatBtnRect;
	bool				m_IsEnterChatBtn;

};

extern CUI_ID_FRAME_chatInfoList s_CUI_ID_FRAME_chatInfoList;
