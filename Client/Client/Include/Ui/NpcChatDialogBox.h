/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Code\RunTime\CLIENT\Data\UI\NpcChatDialogBox.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "..\NpcCoord.h"

#ifndef ID_FRAME_NpcChatDialogBox
#define ID_FRAME_NpcChatDialogBox		"ID_FRAME_NpcChatDialogBox"
#endif  ID_FRAME_NpcChatDialogBox
#ifndef ID_BUTTON_Next
#define ID_BUTTON_Next		"ID_BUTTON_Next"
#endif  ID_BUTTON_Next
#ifndef ID_BUTTON_Close
#define ID_BUTTON_Close		"ID_BUTTON_Close"
#endif  ID_BUTTON_Close
#ifndef ID_TEXT_Info
#define ID_TEXT_Info		"ID_TEXT_Info"
#endif  ID_TEXT_Info
#ifndef ID_TEXT_Name
#define ID_TEXT_Name		"ID_TEXT_Name"
#endif  ID_TEXT_Name
#ifndef ID_PICTURE_Head
#define ID_PICTURE_Head		"ID_PICTURE_Head"
#endif  ID_PICTURE_Head
#ifndef ID_BUTTON_EXIT
#define ID_BUTTON_EXIT		"ID_BUTTON_EXIT"
#endif  ID_BUTTON_EXIT
#ifndef ID_PICTURE_NpcHead
#define ID_PICTURE_NpcHead		"ID_PICTURE_NpcHead"
#endif  ID_PICTURE_NpcHead

#include "UiBase.h"
class CUI_ID_FRAME_NpcChatDialogBox :public CUIBase
{
public:
    CUI_ID_FRAME_NpcChatDialogBox();

    // Frame
	bool OnFrameRun();
	bool OnFrameRender();
	// Button
	bool ID_BUTTON_NextOnButtonClick( ControlObject* pSender );
	// Button
	bool ID_BUTTON_CloseOnButtonClick( ControlObject* pSender );
	// Button
	bool ID_BUTTON_EXITOnButtonClick( ControlObject* pSender );

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	const char* GetNpcName();
	void	SetDialogName( const char* szName );

	void	SetNpc( int nId, UINT nImgID = 0 );
    void    SetChatNpc( int nId );
	void	ShowDialog( const std::string& strData, bool bShowNext );
	void	CloseDialog();
	void	SetButtonEnable( bool bEnabel );
	void	CancelScript();	// 强行中止脚本
	void	ReqScript();
	void	ShowIntonateBar( DWORD dwTime, const char* pName=NULL );
	void	RetrieveNpcPic();
	void	SetScriptCanceled(bool bCanceld);
	bool	GetScriptCanceled();
	int		GetChatNpc();

    bool    IsScriptCancel(){return m_bScriptCanceled;}

    bool    IsButCloseVisable();

	//触发键盘Enter消息事件
    bool frame_BackmsgClick(UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed);

	static void TextInfo_HyberClick( ControlObject* pSender, const char* szData );

private:
    // SGuildMember
    ControlFrame*	m_pID_FRAME_NpcChatDialogBox;
    ControlButton*	m_pID_BUTTON_Next;
    ControlButton*	m_pID_BUTTON_Close;
    ControlText*	m_pID_TEXT_Info;
    ControlText*	m_pID_TEXT_Name;
    ControlPicture*	m_pID_PICTURE_Head;
    ControlButton*	m_pID_BUTTON_EXIT;
    ControlPicture* m_pID_PICTURE_NpcHead;
private:
    std::string		m_szText;

    bool	        m_bWaitIntonate;
    DWORD	        m_dwLastIntonateTime;
    DWORD	        m_dwIntonatePressTime;
    bool	        m_bQuestNpc;
    DWORD	        m_dwLastTime;
    int		        m_nNpcId;
    bool            m_bScriptCanceled;
};
extern CUI_ID_FRAME_NpcChatDialogBox s_CUI_ID_FRAME_NpcChatDialogBox;