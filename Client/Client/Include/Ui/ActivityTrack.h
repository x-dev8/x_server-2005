/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\ActivityTrack.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_ActivityTrack
#define ID_FRAME_ActivityTrack		"ID_FRAME_ActivityTrack"
#endif  ID_FRAME_ActivityTrack
#ifndef ID_LIST_TRACK
#define ID_LIST_TRACK		"ID_LIST_TRACK"
#endif  ID_LIST_TRACK
#ifndef ID_TEXT_Track
#define ID_TEXT_Track		"ID_TEXT_Track"
#endif  ID_TEXT_Track
#ifndef ID_TEXT_Time
#define ID_TEXT_Time		"ID_TEXT_Time"
#endif  ID_TEXT_Time
#ifndef ID_CHECKBOX_Flex
#define ID_CHECKBOX_Flex		"ID_CHECKBOX_Flex"
#endif  ID_CHECKBOX_Flex
#ifndef ID_BUTTON_Plus
#define ID_BUTTON_Plus		"ID_BUTTON_Plus"
#endif  ID_BUTTON_Plus
#ifndef ID_BUTTON_Sub
#define ID_BUTTON_Sub		"ID_BUTTON_Sub"
#endif  ID_BUTTON_Sub
#ifndef ID_TEXT_Remind
#define	ID_TEXT_Remind		"ID_TEXT_Remind"
#endif	ID_TEXT_Remind

struct SpecialActivity
{
	SpecialActivity()
	{
		bVisable = true;
		strName.clear();
		itemVec.clear();
	}
	std::string strName;
	std::vector<ControlList::S_List> itemVec;
	bool bVisable;
};

#include "UiBase.h"
class CUI_ID_FRAME_ActivityTrack :public CUIBase
{
private:
	// Member
	ControlFrame*	m_pID_FRAME_ActivityTrack;
	ControlList*	m_pID_LIST_TRACK;
	ControlText*	m_pID_TEXT_Track;
	ControlText*	m_pID_TEXT_Time;
	ControlCheckBox*	m_pID_CHECKBOX_Flex;
	ControlButton*	m_pID_BUTTON_Plus;
	ControlButton*	m_pID_BUTTON_Sub;
	ControlText*    m_pID_TEXT_Remind;

public:	
	CUI_ID_FRAME_ActivityTrack();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_PlusOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SubOnButtonClick( ControlObject* pSender );
	void ID_LIST_TRACKOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_CHECKBOX_FlexOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

	virtual bool IsHoldInMemory() const { return true; }
    virtual void InitializeAtEnterWorld();

	int GetTrackListItemCnt();
	void TrackAddItem( const ControlList::S_List* pItem, const bool bMoveDonw = true );
	ControlList::S_List* GetTrackListItem( int i ); 
	void TrackClear( bool b );
	int GetTrackStartIndex();
	int GetTrackItemShowCount();
	void SetShowStartHeight( int i );
	void SetTrackScrollValue( int i );
	bool IsExistListTrack(){ return m_pID_LIST_TRACK; }
	void SetTextTime(const char* chr);

	//added by zhuomeng.hu		[9/7/2010]
	bool AddSpecialActivity( const SpecialActivity* activity );		
	bool DelSpecialActivity( std::string strName );
	SpecialActivity* GetSpecialActivityPtr( std::string strName );
	bool SetSpecialActivityVisable( std::string strName, bool bVisable );
	void HideAllSpecial();
	void ShowAllSpecial();
	void RefreshAllSpecial();			// 为兼容老的活动而存在，不可调用
	void ClearAllSpecial();		

private:
	static void HyberOtherClick( ControlObject* pSender, const std::string& content ,int nId );

private:
	//功能扩展，与主活动界面分离	added by zhuomeng.hu		[9/7/2010]
	std::map<std::string, SpecialActivity>		m_specialActivityMap;	


};
extern CUI_ID_FRAME_ActivityTrack s_CUI_ID_FRAME_ActivityTrack;
