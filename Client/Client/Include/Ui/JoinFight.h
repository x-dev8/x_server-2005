/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\JoinFight.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "MessageDefine.h"
#include "me3d/Vector.h"

#ifndef ID_FRAME_JoinFight
#define ID_FRAME_JoinFight		"ID_FRAME_JoinFight"
#endif  ID_FRAME_JoinFight
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_BUTTON_Cancle
#define ID_BUTTON_Cancle		"ID_BUTTON_Cancle"
#endif  ID_BUTTON_Cancle
#ifndef ID_LIST_List
#define ID_LIST_List		"ID_LIST_List"
#endif  ID_LIST_List
#ifndef ID_TEXT_Time
#define ID_TEXT_Time		"ID_TEXT_Time"
#endif  ID_TEXT_Time

#include "UiBase.h"
class CUI_ID_FRAME_JoinFight :public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_JoinFight();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancleOnButtonClick( ControlObject* pSender );
	void ID_LIST_ListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


    void Show( MsgShowBattleSignUpDlg* pMsg );
    void OnAck( MsgBattleSignUpAck* pMsg );
	void OnUpdateCount( MsgTellBattleSignUpCount* pMsg );
private:

	void OnOK();
	void Update(int id=-1);

	std::vector<MsgShowBattleSignUpDlg::SignUpInfo> m_SignUpInfo;
	unsigned int m_npcId;
	unsigned int m_time;
	unsigned int m_leftTime;
	unsigned int m_type;
protected:
	unsigned short m_usLastMinute;
	unsigned short m_usLastSecond;

	Vector m_vVisiblePos;			 // 界面打开时的人物位置,用来自动关闭时使用

    ControlFrame*	m_pID_FRAME_JoinFight;
    ControlButton*	m_pID_BUTTON_OK;
    ControlButton*	m_pID_BUTTON_Cancle;
    ControlList*	m_pID_LIST_List;
    ControlText*	m_pID_TEXT_Time;
};
extern CUI_ID_FRAME_JoinFight s_CUI_ID_FRAME_JoinFight;
