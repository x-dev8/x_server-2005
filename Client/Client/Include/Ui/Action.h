/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Hero\Program\trunk\Bin\Client\Data\Ui\Action.h
	表情动作
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "ExpActionConfig.h"

#ifndef ID_FRAME_Action
#define ID_FRAME_Action		"ID_FRAME_Action"
#endif  ID_FRAME_Action
#ifndef ID_PICTURE_TitleDi
#define ID_PICTURE_TitleDi		"ID_PICTURE_TitleDi"
#endif  ID_PICTURE_TitleDi
#ifndef ID_BUTTON_help
#define ID_BUTTON_help		"ID_BUTTON_help"
#endif  ID_BUTTON_help
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_LISTIMG_ActionIcon
#define ID_LISTIMG_ActionIcon		"ID_LISTIMG_ActionIcon"
#endif  ID_LISTIMG_ActionIcon
#ifndef ID_TEXT_Name
#define ID_TEXT_Name		"ID_TEXT_Name"
#endif  ID_TEXT_Name
#ifndef ID_TEXT_Name1
#define ID_TEXT_Name1		"ID_TEXT_Name1"
#endif  ID_TEXT_Name1
#ifndef ID_TEXT_Name2
#define ID_TEXT_Name2		"ID_TEXT_Name2"
#endif  ID_TEXT_Name2
#ifndef ID_TEXT_Name3
#define ID_TEXT_Name3		"ID_TEXT_Name3"
#endif  ID_TEXT_Name3
#ifndef ID_TEXT_Name4
#define ID_TEXT_Name4		"ID_TEXT_Name4"
#endif  ID_TEXT_Name4
#ifndef ID_TEXT_Name5
#define ID_TEXT_Name5		"ID_TEXT_Name5"
#endif  ID_TEXT_Name5
#ifndef ID_TEXT_Name6
#define ID_TEXT_Name6		"ID_TEXT_Name6"
#endif  ID_TEXT_Name6
#ifndef ID_TEXT_Name7
#define ID_TEXT_Name7		"ID_TEXT_Name7"
#endif  ID_TEXT_Name7
#ifndef ID_TEXT_Name8
#define ID_TEXT_Name8		"ID_TEXT_Name8"
#endif  ID_TEXT_Name8
#ifndef ID_TEXT_Name9
#define ID_TEXT_Name9		"ID_TEXT_Name9"
#endif  ID_TEXT_Name9
#ifndef ID_TEXT_Page
#define ID_TEXT_Page		"ID_TEXT_Page"
#endif  ID_TEXT_Page
#ifndef ID_BUTTON_Pageup
#define ID_BUTTON_Pageup		"ID_BUTTON_Pageup"
#endif  ID_BUTTON_Pageup
#ifndef ID_BUTTON_Pagedown
#define ID_BUTTON_Pagedown		"ID_BUTTON_Pagedown"
#endif  ID_BUTTON_Pagedown
#ifndef ID_TEXT_Name10
#define ID_TEXT_Name10		"ID_TEXT_Name10"
#endif  ID_TEXT_Name10
#ifndef ID_TEXT_Name11
#define ID_TEXT_Name11		"ID_TEXT_Name11"
#endif  ID_TEXT_Name11

#include "UiBase.h"
class CUI_ID_FRAME_Action :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_Action();
private:
	 ControlFrame*	m_pID_FRAME_Action;
// 	 ControlPicture*	m_pID_PICTURE_TitleDi;
// 	 ControlButton*	m_pID_BUTTON_help;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlListImage*	m_pID_LISTIMG_ActionIcon;
	 ControlText*	m_pID_TEXT_Name;
	 ControlText*	m_pID_TEXT_Name1;
	 ControlText*	m_pID_TEXT_Name2;
	 ControlText*	m_pID_TEXT_Name3;
	 ControlText*	m_pID_TEXT_Name4;
	 ControlText*	m_pID_TEXT_Name5;
	 ControlText*	m_pID_TEXT_Name6;
	 ControlText*	m_pID_TEXT_Name7;
	 ControlText*	m_pID_TEXT_Name8;
	 ControlText*	m_pID_TEXT_Name9;
	 ControlText*	m_pID_TEXT_Page;
	 ControlButton*	m_pID_BUTTON_Pageup;
	 ControlButton*	m_pID_BUTTON_Pagedown;
	 ControlText*	m_pID_TEXT_Name10;
	 ControlText*	m_pID_TEXT_Name11;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	//bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_ActionIconOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ActionIconOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ActionIconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ActionIconOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_PageupOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PagedownOnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );				// 设置是否可视
public:


	bool IsActionList( ControlObject* pListImg);
	ControlFrame* GetFrame() { return m_pID_FRAME_Action; }

private:
	void Init();										// 初始化界面数据
	void SetIcon(int index, const ExpAction* pAction);	// 设置一个动作
	bool ShowPage(unsigned short ustPageNo);			// 显示第几页

	std::vector<ControlText*> m_vecDescriptions;		// 根据m_pID_LISTIMG_ActionIcon长度设置描述显示
	unsigned short m_ustCurPage;						// 当前页数，从0开始
	unsigned short m_ustPageNum;						// 总页数
	unsigned short m_ustIconNumPerPage;					// 每页显示Icon个数
	bool m_bInited;
};
extern CUI_ID_FRAME_Action s_CUI_ID_FRAME_Action;
