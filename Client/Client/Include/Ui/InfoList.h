/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\InfoList.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "Country.h"
#include "ScreenInfoManager.h"

#ifndef ID_FRAME_InfoList
#define ID_FRAME_InfoList		"ID_FRAME_InfoList"
#endif  ID_FRAME_InfoList
#ifndef ID_PICTURE_BgFrame
#define ID_PICTURE_BgFrame		"ID_PICTURE_BgFrame"
#endif  ID_PICTURE_BgFrame
#ifndef ID_BUTTON_Bottom
#define ID_BUTTON_Bottom		"ID_BUTTON_Bottom"
#endif  ID_BUTTON_Bottom
#ifndef ID_TEXT_Info
#define ID_TEXT_Info		"ID_TEXT_Info"
#endif  ID_TEXT_Info
#ifndef ID_BUTTON_Show
#define ID_BUTTON_Show		"ID_BUTTON_Show"
#endif  ID_BUTTON_Show
#ifndef ID_BUTTON_Hide
#define ID_BUTTON_Hide		"ID_BUTTON_Hide"
#endif  ID_BUTTON_Hide
#ifndef ID_BUTTON_Clear
#define ID_BUTTON_Clear		"ID_BUTTON_Clear"
#endif  ID_BUTTON_Clear

#include "ChatInfoBox.h"
class CUI_ID_FRAME_InfoList :public CUI_ChatInfoBox
{
private:
    struct AlphaLevel
    {
        float       fAlpha;
        AlphaLevel* pNext;
    };

private:	
    // Member
    ControlFrame*	    m_pID_FRAME_InfoList;
    ControlPicture*	    m_pID_PICTURE_BgFrame;
    ControlButton*	    m_pID_BUTTON_Bottom;
    ControlText*	    m_pID_TEXT_Info;
    ControlButton*      m_pID_BUTTON_Show;
    ControlButton*      m_pID_BUTTON_Hide;
    ControlGroup        m_groupAll;
    ControlButton*      m_pID_BUTTON_Clear;

public:	
	CUI_ID_FRAME_InfoList();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_BottomOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_ClearOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_ShowOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_HideOnButtonClick( ControlObject* pSender );
    virtual bool IsHoldInMemory() const { return true; }
	virtual void	InitializeAtEnterWorld();			        // 每次登陆游戏调用的逻辑

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

public:
	void Task_HyberOtherClick( ControlObject* pSender, const char* szData );
	void GetBorderFightInfo( const MsgTellCountryBordersFight* pMsg );
	void GetBorderDefendInfo( const MsgTellCountryKillEnemy* pMsg );
    ControlFrame* GetFrame();
	virtual void ClearChat();
    void SetRealAlpha( float fAlpha );
    void VisableBtns( bool bVisable );

private:
    virtual void AddInfo( const std::string& str, const D3DCOLOR col = 0xffffffff, const UINT nType = MsgChat::CHAT_TYPE_GAMEPROMPT,
        char *szToName = NULL, char* itemData = NULL, int cntHyber = 0, int nBagType = 0, bool bAutoReply = false );
    
protected:
    void _AddInfo( const std::string& str, const D3DCOLOR col = 0xffffffff, const UINT nType = MsgChat::CHAT_TYPE_GAMEPROMPT,
        char *szToName = NULL, char* itemData = NULL, int cntHyber = 0, int nBagType = 0, bool bAutoReply = false );

private:
	bool AddNewInfo( const char* str, bool bSkippSame );
// 	void DeleteOverdueInfo( std::string str );
	bool IsLocationOverdue( std::string str );
// 	void Refresh();
	void ResetProperties();

    // 杨凯需求
    float GetRealAlpha();
    void SetTempAlpha( float fAlpha );
    void ShowAll( bool bShow );
    static void FrameMouseEnter( ControlObject* pSender );
    static void FrameMouseLeave( ControlObject* pSender );

	struct SOverdueInfo
    {
		std::string			m_info;
		DWORD				m_BornedTime;
	};
private:	
// 	std::deque<std::string>     m_infoDeq;
	std::deque<SOverdueInfo>    m_inbreakDeq;
    float                       m_fAlpha;

private:
    friend class CScreenInfoManager;
};
extern CUI_ID_FRAME_InfoList s_CUI_ID_FRAME_InfoList;
