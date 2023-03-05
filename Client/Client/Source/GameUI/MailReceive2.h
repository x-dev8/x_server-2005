/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\邮件\MailReceive2.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "GlobalDef.h"
#ifndef ID_FRAME_MailReceive2
#define ID_FRAME_MailReceive2		"ID_FRAME_MailReceive2"
#endif  ID_FRAME_MailReceive2
#ifndef ID_PICTURE_Title
#define ID_PICTURE_Title		"ID_PICTURE_Title"
#endif  ID_PICTURE_Title
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_Help
#define ID_BUTTON_Help		"ID_BUTTON_HELP"
#endif  ID_BUTTON_Help
#ifndef ID_PICTURE_MailContent
#define ID_PICTURE_MailContent		"ID_PICTURE_MailContent"
#endif  ID_PICTURE_MailContent
#ifndef ID_TEXT_Content
#define ID_TEXT_Content		"ID_TEXT_Content"
#endif  ID_TEXT_Content
#ifndef ID_LISTIMG_MailMoney
#define ID_LISTIMG_MailMoney		"ID_LISTIMG_MailMoney"
#endif  ID_LISTIMG_MailMoney
#ifndef ID_TEXT_From
#define ID_TEXT_From		"ID_TEXT_From"
#endif  ID_TEXT_From
#ifndef ID_TEXT_MailTitle
#define ID_TEXT_MailTitle		"ID_TEXT_MailTitle"
#endif  ID_TEXT_MailTitle
#ifndef ID_TEXT_MailTitleName
#define ID_TEXT_MailTitleName		"ID_TEXT_MailTitleName"
#endif  ID_TEXT_MailTitleName
#ifndef ID_TEXT_FromName
#define ID_TEXT_FromName		"ID_TEXT_FromName"
#endif  ID_TEXT_FromName
#ifndef ID_BUTTON_Delete
#define ID_BUTTON_Delete		"ID_BUTTON_Delete"
#endif  ID_BUTTON_Delete
#ifndef ID_BUTTON_Trans
#define ID_BUTTON_Trans		"ID_BUTTON_Trans"
#endif  ID_BUTTON_Trans
#ifndef ID_BUTTON_Re
#define ID_BUTTON_Re		"ID_BUTTON_Re"
#endif  ID_BUTTON_Re
#ifndef ID_BUTTON_Return
#define ID_BUTTON_Return		"ID_BUTTON_Return"
#endif  ID_BUTTON_Return
#ifndef ID_TEXT_SendTarget
#define ID_TEXT_SendTarget		"ID_TEXT_SendTarget"
#endif  ID_TEXT_SendTarget
#ifndef ID_TEXT_SendTargetName
#define ID_TEXT_SendTargetName		"ID_TEXT_SendTargetName"
#endif  ID_TEXT_SendTargetName
#ifndef ID_TEXT_CopyTarget
#define ID_TEXT_CopyTarget		"ID_TEXT_CopyTarget"
#endif  ID_TEXT_CopyTarget
#ifndef ID_TEXT_CopyTargetName
#define ID_TEXT_CopyTargetName		"ID_TEXT_CopyTargetName"
#endif  ID_TEXT_CopyTargetName

#include "UiBase.h"
class CUI_ID_FRAME_MailReceive2 :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_MailReceive2();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HelpOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_MailMoneyOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MailMoneyOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MailMoneyOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MailMoneyOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_DeleteOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_TransOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ReOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ReturnOnButtonClick( ControlObject* pSender );

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

public:
    void DeleteMail();
    void UpdateMail(SMail &mail);
    bool IsExistItem(ControlListImage* pImg);
    void ProcessMail(ControlListImage::S_ListImg* pImgItem);
    void ClearItem(int nIndex);
	void GetAllItem();
    ControlFrame*	m_pID_FRAME_MailReceive2;
private:
    void ClearControlData();


    void GetMoneyByMailMsg();
    void GetItemByMailMsg(ControlListImage::S_ListImg* pImgItem);
    void OpenMailMsg();
private:
    uint32 m_mailId;
    int    m_MailAccessory;
    bool   m_bShow;
private:
	void ResetMembers();
    ControlPicture*	m_pID_PICTURE_Title;
    ControlButton*	m_pID_BUTTON_CLOSE;
    ControlButton*	m_pID_BUTTON_Help;
    ControlPicture*	m_pID_PICTURE_MailContent;
    ControlText*	m_pID_TEXT_Content;
    ControlListImage*	m_pID_LISTIMG_MailMoney;
    ControlText*	m_pID_TEXT_From;
    ControlText*	m_pID_TEXT_MailTitle;
    ControlText*	m_pID_TEXT_MailTitleName;
    ControlText*	m_pID_TEXT_FromName;
    ControlButton*	m_pID_BUTTON_Delete;
    ControlButton*	m_pID_BUTTON_Trans;
    ControlButton*	m_pID_BUTTON_Re;
    ControlButton*	m_pID_BUTTON_Return;
    ControlText*	m_pID_TEXT_SendTarget;
    ControlText*	m_pID_TEXT_SendTargetName;
    ControlText*	m_pID_TEXT_CopyTarget;
    ControlText*	m_pID_TEXT_CopyTargetName;
};
extern CUI_ID_FRAME_MailReceive2 s_CUI_ID_FRAME_MailReceive2;
