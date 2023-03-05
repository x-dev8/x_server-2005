/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\FriendView.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_FriendView
#define ID_FRAME_FriendView		"ID_FRAME_FriendView"
#endif  ID_FRAME_FriendView
#ifndef ID_TEXT_Name
#define ID_TEXT_Name		"ID_TEXT_Name"
#endif  ID_TEXT_Name
#ifndef ID_TEXT_PeopleName
#define ID_TEXT_PeopleName		"ID_TEXT_PeopleName"
#endif  ID_TEXT_PeopleName
#ifndef ID_PICTURE_PeopleHead
#define ID_PICTURE_PeopleHead		"ID_PICTURE_PeopleHead"
#endif  ID_PICTURE_PeopleHead
#ifndef ID_TEXT_Level
#define ID_TEXT_Level		"ID_TEXT_Level"
#endif  ID_TEXT_Level
#ifndef ID_TEXT_PeopleLevel
#define ID_TEXT_PeopleLevel		"ID_TEXT_PeopleLevel"
#endif  ID_TEXT_PeopleLevel
#ifndef ID_TEXT_Work
#define ID_TEXT_Work		"ID_TEXT_Work"
#endif  ID_TEXT_Work
#ifndef ID_TEXT_PeopleWork
#define ID_TEXT_PeopleWork		"ID_TEXT_PeopleWork"
#endif  ID_TEXT_PeopleWork
#ifndef ID_TEXT_FriendFavor
#define ID_TEXT_FriendFavor		"ID_TEXT_FriendFavor"
#endif  ID_TEXT_FriendFavor
#ifndef ID_TEXT_PeopleFriendFavor
#define ID_TEXT_PeopleFriendFavor		"ID_TEXT_PeopleFriendFavor"
#endif  ID_TEXT_PeopleFriendFavor
#ifndef ID_TEXT_Position
#define ID_TEXT_Position		"ID_TEXT_Position"
#endif  ID_TEXT_Position
#ifndef ID_TEXT_PeoplePosition
#define ID_TEXT_PeoplePosition		"ID_TEXT_PeoplePosition"
#endif  ID_TEXT_PeoplePosition
#ifndef ID_TEXT_Mood
#define ID_TEXT_Mood		"ID_TEXT_Mood"
#endif  ID_TEXT_Mood
#ifndef ID_TEXT_PeopleMood
#define ID_TEXT_PeopleMood		"ID_TEXT_PeopleMood"
#endif  ID_TEXT_PeopleMood
#ifndef ID_TEXT_Remark
#define ID_TEXT_Remark		"ID_TEXT_Remark"
#endif  ID_TEXT_Remark
#ifndef ID_TEXT_RemarkZ
#define ID_TEXT_RemarkZ		"ID_TEXT_RemarkZ"
#endif  ID_TEXT_RemarkZ
#ifndef ID_TEXT_CountryZ
#define ID_TEXT_CountryZ		"ID_TEXT_CountryZ"
#endif  ID_TEXT_CountryZ
#ifndef ID_TEXT_CountryName
#define ID_TEXT_CountryName		"ID_TEXT_CountryName"
#endif  ID_TEXT_CountryName
#ifndef ID_TEXT_ConfraternityJob
#define ID_TEXT_ConfraternityJob		"ID_TEXT_ConfraternityJob"
#endif  ID_TEXT_ConfraternityJob
#ifndef ID_TEXT_Relation
#define ID_TEXT_Relation		"ID_TEXT_Relation"
#endif  ID_TEXT_Relation

//生日
#ifndef ID_TEXT_Birthday
#define ID_TEXT_Birthday		"ID_TEXT_Birthday"
#endif  ID_TEXT_Birthday
#ifndef ID_TEXT_BirthdayDate
#define ID_TEXT_BirthdayDate		"ID_TEXT_BirthdayDate"
#endif  ID_TEXT_BirthdayDate

//状态
#ifndef ID_TEXT_Fettle
#define ID_TEXT_Fettle		"ID_TEXT_Fettle"
#endif  ID_TEXT_Fettle
#ifndef ID_TEXT_FettleName
#define ID_TEXT_FettleName		"ID_TEXT_FettleName"
#endif  ID_TEXT_FettleName

//位置
#ifndef ID_TEXT_Name
#define ID_TEXT_Name		"ID_TEXT_Name"
#endif  ID_TEXT_Name
#ifndef ID_TEXT_PositionNanme
#define ID_TEXT_PositionNanme		"ID_TEXT_PositionNanme"
#endif  ID_TEXT_PositionNanme

//称号
#ifndef ID_TEXT_Title
#define ID_TEXT_Title		"ID_TEXT_Title"
#endif  ID_TEXT_Title
#ifndef ID_TEXT_TitleName
#define ID_TEXT_TitleName		"ID_TEXT_TitleName"
#endif  ID_TEXT_TitleName

#ifndef ID_TEXT_Ip
#define ID_TEXT_Ip		"ID_TEXT_Ip"
#endif  ID_TEXT_Ip

class RelationDataToClient;
#include "UIBase.h"
class CUI_ID_FRAME_FriendView : public CUIBase
{
	// Member
private:	
	 ControlFrame*	m_pID_FRAME_FriendView;
	 ControlText*	m_pID_TEXT_Name;
	 ControlText*	m_pID_TEXT_PeopleName;
	 ControlPicture*	m_pID_PICTURE_PeopleHead;
	 ControlText*	m_pID_TEXT_Level;
	 ControlText*	m_pID_TEXT_PeopleLevel;
	 ControlText*	m_pID_TEXT_Work;
	 ControlText*	m_pID_TEXT_PeopleWork;
	 ControlText*	m_pID_TEXT_FriendFavor;
	 ControlText*	m_pID_TEXT_PeopleFriendFavor;
	 ControlText*	m_pID_TEXT_PeoplePosition;
	 ControlText*	m_pID_TEXT_Mood;
	 ControlText*	m_pID_TEXT_PeopleMood;
	 ControlText*	m_pID_TEXT_Remark;
	 ControlEdit*	m_pID_TEXT_RemarkZ;
	 ControlText*	m_pID_TEXT_CountryZ;
	 ControlText*	m_pID_TEXT_CountryName;
	 ControlText*	m_pID_TEXT_ConfraternityJob;
	 ControlText*	m_pID_TEXT_Relation;

	 ControlText*	m_pID_TEXT_Birthday;
	 ControlText*	m_pID_TEXT_BirthdayDate;

	 ControlText*	m_pID_TEXT_Fettle;
	 ControlText*	m_pID_TEXT_FettleName;

	 ControlText*	m_pID_TEXT_Position;
	 ControlText*	m_pID_TEXT_PositionNanme;

	 ControlText*	m_pID_TEXT_Title;
	 ControlText*	m_pID_TEXT_TitleName;

	 ControlText*	m_pID_TEXT_Ip;

public:	
	CUI_ID_FRAME_FriendView();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();

	ControlFrame* GetFrame() const { return m_pID_FRAME_FriendView; }
	void Refresh(RelationDataToClient*);
private:
	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视
};
extern CUI_ID_FRAME_FriendView s_CUI_ID_FRAME_FriendView;
