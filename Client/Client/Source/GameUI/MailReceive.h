/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Hero\trunk\Bin\Client\Data\Ui\MailReceive.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include <vector>
#include "GlobalDef.h"
#include "SystemMail.h"

#ifndef ID_FRAME_MailReceive
#define ID_FRAME_MailReceive		"ID_FRAME_MailReceive"
#endif  ID_FRAME_MailReceive
#ifndef ID_TEXT_Filter
#define ID_TEXT_Filter		"ID_TEXT_Filter"
#endif  ID_TEXT_Filter
#ifndef ID_PICTURE_MailList
#define ID_PICTURE_MailList		"ID_PICTURE_MailList"
#endif  ID_PICTURE_MailList
#ifndef ID_TEXT_AutoDelete
#define ID_TEXT_AutoDelete		"ID_TEXT_AutoDelete"
#endif  ID_TEXT_AutoDelete
#ifndef ID_CHECKBOX_AutoDelete
#define ID_CHECKBOX_AutoDelete		"ID_CHECKBOX_AutoDelete"
#endif  ID_CHECKBOX_AutoDelete
#ifndef ID_LISTIMG_MailIcon
#define ID_LISTIMG_MailIcon		"ID_LISTIMG_MailIcon"
#endif  ID_LISTIMG_MailIcon
#ifndef ID_COMBOBOX_Filter
#define ID_COMBOBOX_Filter		"ID_COMBOBOX_Filter"
#endif  ID_COMBOBOX_Filter
#ifndef ID_CHECKBOX_Select1
#define ID_CHECKBOX_Select1		"ID_CHECKBOX_Select1"
#endif  ID_CHECKBOX_Select1
#ifndef ID_CHECKBOX_Select2
#define ID_CHECKBOX_Select2		"ID_CHECKBOX_Select2"
#endif  ID_CHECKBOX_Select2
#ifndef ID_CHECKBOX_Select3
#define ID_CHECKBOX_Select3		"ID_CHECKBOX_Select3"
#endif  ID_CHECKBOX_Select3
#ifndef ID_CHECKBOX_Select4
#define ID_CHECKBOX_Select4		"ID_CHECKBOX_Select4"
#endif  ID_CHECKBOX_Select4
#ifndef ID_CHECKBOX_Select5
#define ID_CHECKBOX_Select5		"ID_CHECKBOX_Select5"
#endif  ID_CHECKBOX_Select5
#ifndef ID_CHECKBOX_Select6
#define ID_CHECKBOX_Select6		"ID_CHECKBOX_Select6"
#endif  ID_CHECKBOX_Select6
#ifndef ID_CHECKBOX_SelectAll
#define ID_CHECKBOX_SelectAll		"ID_CHECKBOX_SelectAll"
#endif  ID_CHECKBOX_SelectAll
#ifndef ID_TEXT_SelectAll
#define ID_TEXT_SelectAll		"ID_TEXT_SelectAll"
#endif  ID_TEXT_SelectAll
#ifndef ID_TEXT_Page
#define ID_TEXT_Page		"ID_TEXT_Page"
#endif  ID_TEXT_Page
#ifndef ID_TEXT_MailInfo1
#define ID_TEXT_MailInfo1		"ID_TEXT_MailInfo1"
#endif  ID_TEXT_MailInfo1
#ifndef ID_TEXT_MailInfo2
#define ID_TEXT_MailInfo2		"ID_TEXT_MailInfo2"
#endif  ID_TEXT_MailInfo2
#ifndef ID_TEXT_MailInfo3
#define ID_TEXT_MailInfo3		"ID_TEXT_MailInfo3"
#endif  ID_TEXT_MailInfo3
#ifndef ID_TEXT_MailInfo4
#define ID_TEXT_MailInfo4		"ID_TEXT_MailInfo4"
#endif  ID_TEXT_MailInfo4
#ifndef ID_TEXT_MailInfo5
#define ID_TEXT_MailInfo5		"ID_TEXT_MailInfo5"
#endif  ID_TEXT_MailInfo5
#ifndef ID_TEXT_MailInfo6
#define ID_TEXT_MailInfo6		"ID_TEXT_MailInfo6"
#endif  ID_TEXT_MailInfo6
#ifndef ID_TEXT_MailInfo7
#define ID_TEXT_MailInfo7		"ID_TEXT_MailInfo7"
#endif  ID_TEXT_MailInfo7
#ifndef ID_TEXT_MailInfo8
#define ID_TEXT_MailInfo8		"ID_TEXT_MailInfo8"
#endif  ID_TEXT_MailInfo8
#ifndef ID_CHECKBOX_Select7
#define ID_CHECKBOX_Select7		"ID_CHECKBOX_Select7"
#endif  ID_CHECKBOX_Select7
#ifndef ID_CHECKBOX_Select8
#define ID_CHECKBOX_Select8		"ID_CHECKBOX_Select8"
#endif  ID_CHECKBOX_Select8
#ifndef ID_TEXT_MailTitle1
#define ID_TEXT_MailTitle1		"ID_TEXT_MailTitle1"
#endif  ID_TEXT_MailTitle1
#ifndef ID_TEXT_MailTitle2
#define ID_TEXT_MailTitle2		"ID_TEXT_MailTitle2"
#endif  ID_TEXT_MailTitle2
#ifndef ID_TEXT_MailTitle3
#define ID_TEXT_MailTitle3		"ID_TEXT_MailTitle3"
#endif  ID_TEXT_MailTitle3
#ifndef ID_TEXT_MailTitle4
#define ID_TEXT_MailTitle4		"ID_TEXT_MailTitle4"
#endif  ID_TEXT_MailTitle4
#ifndef ID_TEXT_MailTitle5
#define ID_TEXT_MailTitle5		"ID_TEXT_MailTitle5"
#endif  ID_TEXT_MailTitle5
#ifndef ID_TEXT_MailTitle6
#define ID_TEXT_MailTitle6		"ID_TEXT_MailTitle6"
#endif  ID_TEXT_MailTitle6
#ifndef ID_TEXT_MailTitle7
#define ID_TEXT_MailTitle7		"ID_TEXT_MailTitle7"
#endif  ID_TEXT_MailTitle7
#ifndef ID_TEXT_MailTitle8
#define ID_TEXT_MailTitle8		"ID_TEXT_MailTitle8"
#endif  ID_TEXT_MailTitle8
#ifndef ID_TEXT_LeaveTime1
#define ID_TEXT_LeaveTime1		"ID_TEXT_LeaveTime1"
#endif  ID_TEXT_LeaveTime1
#ifndef ID_TEXT_LeaveTime2
#define ID_TEXT_LeaveTime2		"ID_TEXT_LeaveTime2"
#endif  ID_TEXT_LeaveTime2
#ifndef ID_TEXT_LeaveTime3
#define ID_TEXT_LeaveTime3		"ID_TEXT_LeaveTime3"
#endif  ID_TEXT_LeaveTime3
#ifndef ID_TEXT_LeaveTime4
#define ID_TEXT_LeaveTime4		"ID_TEXT_LeaveTime4"
#endif  ID_TEXT_LeaveTime4
#ifndef ID_TEXT_LeaveTime5
#define ID_TEXT_LeaveTime5		"ID_TEXT_LeaveTime5"
#endif  ID_TEXT_LeaveTime5
#ifndef ID_TEXT_LeaveTime6
#define ID_TEXT_LeaveTime6		"ID_TEXT_LeaveTime6"
#endif  ID_TEXT_LeaveTime6
#ifndef ID_TEXT_LeaveTime7
#define ID_TEXT_LeaveTime7		"ID_TEXT_LeaveTime7"
#endif  ID_TEXT_LeaveTime7
#ifndef ID_TEXT_LeaveTime8
#define ID_TEXT_LeaveTime8		"ID_TEXT_LeaveTime8"
#endif  ID_TEXT_LeaveTime8
#ifndef ID_BUTTON_Pageup
#define ID_BUTTON_Pageup		"ID_BUTTON_Pageup"
#endif  ID_BUTTON_Pageup
#ifndef ID_BUTTON_Pagedown
#define ID_BUTTON_Pagedown		"ID_BUTTON_Pagedown"
#endif  ID_BUTTON_Pagedown
#ifndef ID_BUTTON_Delete
#define ID_BUTTON_Delete		"ID_BUTTON_Delete"
#endif  ID_BUTTON_Delete
#ifndef ID_LIST_MailList
#define ID_LIST_MailList		"ID_LIST_MailList"
#endif  ID_LIST_MailList
#ifndef ID_LISTIMG_ItemIcon
#define ID_LISTIMG_ItemIcon		"ID_LISTIMG_ItemIcon"
#endif  ID_LISTIMG_ItemIcon
#ifndef ID_CHECKBOX_AcceptMail
#define ID_CHECKBOX_AcceptMail		"ID_CHECKBOX_AcceptMail"
#endif  ID_CHECKBOX_AcceptMail
#ifndef ID_CHECKBOX_WriteMail
#define ID_CHECKBOX_WriteMail		"ID_CHECKBOX_WriteMail"
#endif  ID_CHECKBOX_WriteMail
#ifndef ID_TEXT_State6
#define ID_TEXT_State6		"ID_TEXT_State6"
#endif  ID_TEXT_State6
#ifndef ID_TEXT_State5
#define ID_TEXT_State5		"ID_TEXT_State5"
#endif  ID_TEXT_State5
#ifndef ID_TEXT_State4
#define ID_TEXT_State4		"ID_TEXT_State4"
#endif  ID_TEXT_State4
#ifndef ID_TEXT_State3
#define ID_TEXT_State3		"ID_TEXT_State3"
#endif  ID_TEXT_State3
#ifndef ID_TEXT_State2
#define ID_TEXT_State2		"ID_TEXT_State2"
#endif  ID_TEXT_State2
#ifndef ID_TEXT_State1
#define ID_TEXT_State1		"ID_TEXT_State1"
#endif  ID_TEXT_State1


#define  MAXSHOWNUM      6

#include "UiBase.h"
class CUI_ID_FRAME_MailReceive :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_MailReceive();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	//void ID_CHECKBOX_AutoDeleteOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_LISTIMG_MailIconOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MailIconOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MailIconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MailIconOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	void ID_COMBOBOX_FilterOnComboBoxChange( ControlObject* pSender, const char* szData );
	void ID_CHECKBOX_Select1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Select2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Select3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Select4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Select5OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Select6OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_SelectAllOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_PageupOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PagedownOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DeleteOnButtonClick( ControlObject* pSender );
    void ID_LIST_MailListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
    bool ID_LISTIMG_ItemIconOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
    bool ID_LISTIMG_ItemIconOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    bool ID_LISTIMG_ItemIconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    bool ID_LISTIMG_ItemIconOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	void ID_CHECKBOX_AcceptMailOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked );
	void ID_CHECKBOX_WriteMailOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked );

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:
public:
    void Init();
    void InitCombox();

    void UpdateMail();
    void RefreshMailInfo(int nIndex,SMail& mail);  //刷新邮件
    void RefreshPage();   //刷新钱币
    void Refresh();
    void ReadMail(int nIndex);  //阅读邮件
	void SendMailListReq();	//发送请求邮件列表的信息

    void ClearContorData();
    bool IsExistItemInMailList();
    void DeleteMailInList();
    static bool ProcessDeleteMail(const char  bYesPress,void *pData);

    ControlFrame *GetFrame(){return m_pID_FRAME_MailReceive;}

private:
    int                 m_nCurPage;    //当前页数,默认1页
    MailFilter          m_FilterType;  //过滤类型
private:
	void ResetMembers();
    ControlFrame*	m_pID_FRAME_MailReceive;
    ControlText*	m_pID_TEXT_Filter;
//     ControlPicture*	m_pID_PICTURE_MailList;
//     ControlText*	m_pID_TEXT_AutoDelete;
//     ControlCheckBox*	m_pID_CHECKBOX_AutoDelete;
    ControlListImage*	m_pID_LISTIMG_MailIcon;
    ControlComboBox*	m_pID_COMBOBOX_Filter;
    ControlCheckBox*	m_pID_CHECKBOX_Select1;
    ControlCheckBox*	m_pID_CHECKBOX_Select2;
    ControlCheckBox*	m_pID_CHECKBOX_Select3;
    ControlCheckBox*	m_pID_CHECKBOX_Select4;
    ControlCheckBox*	m_pID_CHECKBOX_Select5;
    ControlCheckBox*	m_pID_CHECKBOX_Select6;

    ControlCheckBox*	m_pID_CHECKBOX_SelectAll;
    ControlText*	m_pID_TEXT_SelectAll;
    ControlText*	m_pID_TEXT_Page;
    ControlText*	m_pID_TEXT_MailInfo1;
    ControlText*	m_pID_TEXT_MailInfo2;
    ControlText*	m_pID_TEXT_MailInfo3;
    ControlText*	m_pID_TEXT_MailInfo4;
    ControlText*	m_pID_TEXT_MailInfo5;
    ControlText*	m_pID_TEXT_MailInfo6;

    ControlText*	m_pID_TEXT_MailTitle1;
    ControlText*	m_pID_TEXT_MailTitle2;
    ControlText*	m_pID_TEXT_MailTitle3;
    ControlText*	m_pID_TEXT_MailTitle4;
    ControlText*	m_pID_TEXT_MailTitle5;
    ControlText*	m_pID_TEXT_MailTitle6;

    ControlText*	m_pID_TEXT_LeaveTime1;
    ControlText*	m_pID_TEXT_LeaveTime2;
    ControlText*	m_pID_TEXT_LeaveTime3;
    ControlText*	m_pID_TEXT_LeaveTime4;
    ControlText*	m_pID_TEXT_LeaveTime5;
    ControlText*	m_pID_TEXT_LeaveTime6;

    ControlButton*	m_pID_BUTTON_Pageup;
    ControlButton*	m_pID_BUTTON_Pagedown;
    ControlButton*	m_pID_BUTTON_Delete;

    ControlList*	m_pID_LIST_MailList;
    ControlListImage*	m_pID_LISTIMG_ItemIcon;

	ControlCheckBox*	m_pID_CheckBox_AcceptMail;
	ControlCheckBox*	m_pID_CheckBox_WriteMail;

	ControlText*	m_pID_TEXT_State6;
	ControlText*	m_pID_TEXT_State5;
	ControlText*	m_pID_TEXT_State4;
	ControlText*	m_pID_TEXT_State3;
	ControlText*	m_pID_TEXT_State2;
	ControlText*	m_pID_TEXT_State1;

    ControlCheckBox* m_CheckBox[MAXSHOWNUM];  //便于遍历ControlCheckBox
    ControlText*     m_TextMailInfo[MAXSHOWNUM];       //邮件信息
    ControlText*     m_TextMailTitle[MAXSHOWNUM];      //邮件标题
    ControlText*     m_TextMailLevelTime[MAXSHOWNUM];  //剩余时间
	ControlText*	 m_TextMailStates[MAXSHOWNUM];	   //是否阅读
};
extern CUI_ID_FRAME_MailReceive s_CUI_ID_FRAME_MailReceive;
