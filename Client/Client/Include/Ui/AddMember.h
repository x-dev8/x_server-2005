/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Work\Run\Client\UI\AddMember.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "RelationDefine.h"

#ifndef ID_FRAME_ADD_MEMBER
#define ID_FRAME_ADD_MEMBER		"ID_FRAME_ADD_MEMBER"
#endif  ID_FRAME_ADD_MEMBER
#ifndef ID_TEXT_Msg
#define ID_TEXT_Msg		"ID_TEXT_Msg"
#endif  ID_TEXT_Msg
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_BUTTON_Cancle
#define ID_BUTTON_Cancle		"ID_BUTTON_Cancle"
#endif  ID_BUTTON_Cancle
#ifndef ID_PICTURE_15507
#define ID_PICTURE_15507		"ID_PICTURE_15507"
#endif  ID_PICTURE_15507
#ifndef ID_EDIT_AddName
#define ID_EDIT_AddName		"ID_EDIT_AddName"
#endif  ID_EDIT_AddName
#ifndef ID_LIST_ActivityList
#define ID_LIST_ActivityList		"ID_LIST_ActivityList"
#endif  ID_LIST_ActivityList

#include "UiBase.h"
class CUI_ID_FRAME_ADD_MEMBER :public CUIBase
{
	// SGuildMember
public:
    CUI_ID_FRAME_ADD_MEMBER();
private:
	 ControlFrame*	m_pID_FRAME_ADD_MEMBER;
	 ControlText*	m_pID_TEXT_Msg;
	 ControlButton*	m_pID_BUTTON_OK;
	 ControlButton*	m_pID_BUTTON_Cancle;
	// ControlPicture*	m_pID_PICTURE_15507;
	 ControlEdit*	m_pID_EDIT_AddName;
	// ControlList*	m_pID_LIST_ActivityList;
public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancleOnButtonClick( ControlObject* pSender );
	void ID_EDIT_AddNameOnEditEnter( ControlObject* pSender, const char* szData );
	//void ID_LIST_ActivityListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

    bool EditInputIsVisable();

	ControlEdit* GetpIDEditAddName();

	enum eFrameType {
		eFrameType_AddMember
		,eFrameType_CreateFamily
		,eFrameType_ChangeFirstFamilyName
		,eFrameType_ChangeSecFamilyName	
		,eFrameType_ChangeThirdFamilyName
		,eFrameType_ChangeFourthFamilyName
		,eFrameType_ChangeFifthFamilyName
		,eFrameType_AddFamilyMember
	};
	enum eFamilyID
	{
		eKey_FirstFamily = 1,
		eKey_SecondFamily,
		eKey_ThirdFamily,
		eKey_FourthFamily,
		eKey_FifthFamily,
	};
	void SetFrameType(eFrameType type) { meFrameType = type; }

private:

	eFrameType						meFrameType;

};
extern CUI_ID_FRAME_ADD_MEMBER s_CUI_ID_FRAME_ADD_MEMBER;