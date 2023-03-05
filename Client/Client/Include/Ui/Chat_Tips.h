/********************************************************************
	Created by UIEditor.exe
	FileName: E:\temp\Chat_Tips.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_Chat_Tips
#define ID_FRAME_Chat_Tips		"ID_FRAME_Chat_Tips"
#endif  ID_FRAME_Chat_Tips
#ifndef ID_PICTURE_6527
#define ID_PICTURE_6527		"ID_PICTURE_6527"
#endif  ID_PICTURE_6527
#ifndef ID_BUTTON_Tips
#define ID_BUTTON_Tips		"ID_BUTTON_Tips"
#endif  ID_BUTTON_Tips
#ifndef ID_LIST_Tiplist
#define ID_LIST_Tiplist		"ID_LIST_Tiplist"
#endif  ID_LIST_Tiplist

class CUI_ID_FRAME_Chat_Tips
{
	// Member
public:	
	 CUI_ID_FRAME_Chat_Tips();
private:
	 ControlFrame*	m_pID_FRAME_Chat_Tips;
	 ControlPicture*	m_pID_PICTURE_6527;
	 ControlButton*	m_pID_BUTTON_Tips;
	 ControlList*	m_pID_LIST_Tiplist;
public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_TipsOnButtonClick( ControlObject* pSender );
	void ID_LIST_TiplistOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	void	AddRemindPlayer(const char* pPlayer,const char* pInfo);
	void	RemoveRemindPlayer(const char* pPlayer);
	void	SetRemindVisable(const bool bVisable );
	void	Clear();

	void	SetTipListVisable( bool b );
	void	SetPicture6527( bool b );
private:

	static void ID_List_TiplistOnLBClick( ControlObject* pSender, ControlList::S_List* pItem );



	std::list<std::string>					m_RemindPlayerList;


};
extern CUI_ID_FRAME_Chat_Tips s_CUI_ID_FRAME_Chat_Tips;
