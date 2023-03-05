/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_02.05\Data\Ui\SelectChannel.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "GlobalDef.h"
#include "MessageDefine.h"

#ifndef ID_FRAME_SelectChannel
#define ID_FRAME_SelectChannel		"ID_FRAME_SelectChannel"
#endif  ID_FRAME_SelectChannel
#ifndef ID_LIST_Name
#define ID_LIST_Name		"ID_LIST_Name"
#endif  ID_LIST_Name
#ifndef ID_TEXT_Time
#define ID_TEXT_Time		"ID_TEXT_Time"
#endif  ID_TEXT_Time
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_LIST_State
#define ID_LIST_State		"ID_LIST_State"
#endif  ID_LIST_State
#ifndef ID_LIST_Select
#define ID_LIST_Select		"ID_LIST_Select"
#endif  ID_LIST_Select
#ifndef ID_BUTTON_SelectRandom
#define ID_BUTTON_SelectRandom		"ID_BUTTON_SelectRandom"
#endif  ID_BUTTON_SelectRandom

class CUI_ID_FRAME_SelectChannel : public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_SelectChannel();
	virtual ~CUI_ID_FRAME_SelectChannel();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_LIST_NameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	void ID_LIST_StateOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_SelectOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	static void ID_LIST_SelectOnLDBClick( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_SelectRandomOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	void AddChannelInfo( MsgChannelInfo* pInfo );
	void Refresh();

	void SetSelectFlag( bool flag ) { m_bSelect = flag; }
	bool IsChannelSelected() { return m_bSelect; }
	void ClearData();

	std::string GetChannelName();

	static bool MessageBox_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );

	void SelectChannelRandom( int Index = -1 );

	int GetLastChannelIndex() { return m_nlastChannelIndex; }
	void SetLastChannelIndex( int nIndex ) { m_nlastChannelIndex = nIndex; }

	void SetChannelInfoOpen( bool bOpen ) { m_bChannelInfo_Open = bOpen; }
	bool IsChannelInfoOpen() { return m_bChannelInfo_Open; }

	void SelectTheRightChannel();

private:	
	 ControlFrame*	m_pID_FRAME_SelectChannel;
	 ControlList*	m_pID_LIST_Name;
	 ControlText*	m_pID_TEXT_Time;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlList*	m_pID_LIST_State;
	 ControlList*	m_pID_LIST_Select;
	 ControlButton*	m_pID_BUTTON_SelectRandom;

	 DWORD	dwStartTime;
	 DWORD	dwAutoCloseTime;

	 int m_nCurChannelIndex;
	 bool m_bSelect;
	 int m_nlastChannelIndex;

	 bool m_bChannelInfo_Open;

	 std::vector< SChannelInfo > m_vecChannelInfo;
};
extern CUI_ID_FRAME_SelectChannel s_CUI_ID_FRAME_SelectChannel;
