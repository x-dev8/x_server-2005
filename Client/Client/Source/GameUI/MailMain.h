/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\MailMain.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "GlobalDef.h"
#include <D3Dx9.h>
#include "bag\ItemBag2.h"
#include "PackItemEnableManager.h"

#ifndef ID_FRAME_MailMain
#define ID_FRAME_MailMain		"ID_FRAME_MailMain"
#endif  ID_FRAME_MailMain
#ifndef ID_PICTURE_Title
#define ID_PICTURE_Title		"ID_PICTURE_Title"
#endif  ID_PICTURE_Title
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_Help
#define ID_BUTTON_Help		"ID_BUTTON_HELP"
#endif  ID_BUTTON_Help
#ifndef ID_PICTURE_BackGround
#define ID_PICTURE_BackGround		"ID_PICTURE_BackGround"
#endif  ID_PICTURE_BackGround
#ifndef ID_CHECKBOX_SendMail
#define ID_CHECKBOX_SendMail		"ID_CHECKBOX_SendMail"
#endif  ID_CHECKBOX_SendMail
#ifndef ID_CHECKBOX_ReceiveMail
#define ID_CHECKBOX_ReceiveMail		"ID_CHECKBOX_ReceiveMail"
#endif  ID_CHECKBOX_ReceiveMail
#ifndef ID_TEXT_SendTarget
#define ID_TEXT_SendTarget		"ID_TEXT_SendTarget"
#endif  ID_TEXT_SendTarget
#ifndef ID_TEXT_CopyTarget
#define ID_TEXT_CopyTarget		"ID_TEXT_CopyTarget"
#endif  ID_TEXT_CopyTarget
#ifndef ID_TEXT_MailTitle
#define ID_TEXT_MailTitle		"ID_TEXT_MailTitle"
#endif  ID_TEXT_MailTitle
#ifndef ID_PICTURE_SendTarget
#define ID_PICTURE_SendTarget		"ID_PICTURE_SendTarget"
#endif  ID_PICTURE_SendTarget
#ifndef ID_PICTURE_MailTitle
#define ID_PICTURE_MailTitle		"ID_PICTURE_MailTitle"
#endif  ID_PICTURE_MailTitle
#ifndef ID_EDIT_MailTitle
#define ID_EDIT_MailTitle		"ID_EDIT_MailTitle"
#endif  ID_EDIT_MailTitle
#ifndef ID_PICTURE_CopyTarget
#define ID_PICTURE_CopyTarget		"ID_PICTURE_CopyTarget"
#endif  ID_PICTURE_CopyTarget
#ifndef ID_EDIT_CopyTarget
#define ID_EDIT_CopyTarget		"ID_EDIT_CopyTarget"
#endif  ID_EDIT_CopyTarget
#ifndef ID_PICTURE_MailContent
#define ID_PICTURE_MailContent		"ID_PICTURE_MailContent"
#endif  ID_PICTURE_MailContent
#ifndef ID_EDIT_MailContent
#define ID_EDIT_MailContent		"ID_EDIT_MailContent"
#endif  ID_EDIT_MailContent
#ifndef ID_LISTIMG_MailItem
#define ID_LISTIMG_MailItem		"ID_LISTIMG_MailItem"
#endif  ID_LISTIMG_MailItem
#ifndef ID_TEXT_Cost
#define ID_TEXT_Cost		"ID_TEXT_Cost"
#endif  ID_TEXT_Cost
#ifndef ID_BUTTON_Reset
#define ID_BUTTON_Reset		"ID_BUTTON_Reset"
#endif  ID_BUTTON_Reset
#ifndef ID_TEXT_MailItem
#define ID_TEXT_MailItem		"ID_TEXT_MailItem"
#endif  ID_TEXT_MailItem
#ifndef ID_COMBOBOX_SendTarget
#define ID_COMBOBOX_SendTarget		"ID_COMBOBOX_SendTarget"
#endif  ID_COMBOBOX_SendTarget
#ifndef ID_BUTTON_Send
#define ID_BUTTON_Send		"ID_BUTTON_Send"
#endif  ID_BUTTON_Send
#ifndef ID_PICTURE_Jin
#define ID_PICTURE_Jin		"ID_PICTURE_Jin"
#endif  ID_PICTURE_Jin
#ifndef ID_EDIT_Jin
#define ID_EDIT_Jin		"ID_EDIT_Jin"
#endif  ID_EDIT_Jin
#ifndef ID_PICTURE_Ying
#define ID_PICTURE_Ying		"ID_PICTURE_Ying"
#endif  ID_PICTURE_Ying
#ifndef ID_EDIT_Ying
#define ID_EDIT_Ying		"ID_EDIT_Ying"
#endif  ID_EDIT_Ying
#ifndef ID_PICTURE_Tong
#define ID_PICTURE_Tong		"ID_PICTURE_Tong"
#endif  ID_PICTURE_Tong
#ifndef ID_EDIT_Tong
#define ID_EDIT_Tong		"ID_EDIT_Tong"
#endif  ID_EDIT_Tong
#ifndef ID_TEXT_MailMoney
#define ID_TEXT_MailMoney		"ID_TEXT_MailMoney"
#endif  ID_TEXT_MailMoney
#ifndef ID_PICTURE_JinPic
#define ID_PICTURE_JinPic		"ID_PICTURE_JinPic"
#endif  ID_PICTURE_JinPic
#ifndef ID_PICTURE_YingPic
#define ID_PICTURE_YingPic		"ID_PICTURE_YingPic"
#endif  ID_PICTURE_YingPic
#ifndef ID_PICTURE_TongPic
#define ID_PICTURE_TongPic		"ID_PICTURE_TongPic"
#endif  ID_PICTURE_TongPic
#ifndef ID_COMBOBOX_CopyTarget
#define ID_COMBOBOX_CopyTarget		"ID_COMBOBOX_CopyTarget"
#endif  ID_COMBOBOX_CopyTarget
#ifndef ID_COMBOBOX_MailTitle
#define ID_COMBOBOX_MailTitle		"ID_COMBOBOX_MailTitle"
#endif  ID_COMBOBOX_MailTitle
#ifndef ID_EDIT_SendTarget
#define ID_EDIT_SendTarget		"ID_EDIT_SendTarget"
#endif  ID_EDIT_SendTarget


enum MailType
{
    MailType_Recieve,  //收件
    MailType_Send,     //发件
    MailType_None,     //无
};


#include "UiBase.h"
class CUI_ID_FRAME_MailMain :public CUIBase, CItemEnableChangeSysBase
{
	// Member
public:	
	 CUI_ID_FRAME_MailMain();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HelpOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_SendMailOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_ReceiveMailOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_EDIT_MailTitleOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_CopyTargetOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_MailContentOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_LISTIMG_MailItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MailItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MailItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MailItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_ResetOnButtonClick( ControlObject* pSender );
	void ID_COMBOBOX_SendTargetOnComboBoxChange( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_SendOnButtonClick( ControlObject* pSender );
	void ID_EDIT_JinOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_YingOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_TongOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_COMBOBOX_CopyTargetOnComboBoxChange( ControlObject* pSender, const char* szData );
	void ID_COMBOBOX_MailTitleOnComboBoxChange( ControlObject* pSender, const char* szData );

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

	ControlFrame* GetFrame() { return m_pID_FRAME_MailMain; }
    void RefreshMailMoney();  //刷新邮资
	
public:
    void ToggleUI(MailType type);

    void InitData();
    bool EditInputIsVisable();

    void ClearControl();
    void ClearMoney();  //清空钱
    void ClearItem();  //清空物品
	void AddOldTitle(const char* strTitle);
    bool SendMail();

    bool CheckValidItem(ControlIconDrag::S_ListImg *pImg,int nBagType);  //检验物品合法性

    void ClearImage(ControlIconDrag::S_ListImg *pImg);

    void SetButMailState(bool bEnable);

    void TranslateMail(uint32 mailId);//转发信件

    void ResponseMail(uint32 mailId); //回复信件

    void RefreshEnable(int nOldBagType,int nOldIndex,int nNewBagType,int nNewIndex);//更新背包道具是否可以使用

    void SetVisiblePosition(const D3DXVECTOR3 &vPos);  //设置开启界面玩家坐标
    bool IsOverDistance(const D3DXVECTOR3& vCurPos);   //是否需要关闭界面

    bool IsHaveFocus();
    void RefreshCopySender();  //刷新抄送人

    virtual bool IsPackItemBeUsing( __int64 nGuid );    // 背包物品Enable态 统一管理

    int      m_bagType;  //用于存放背包类型
    int      m_nIndex;   //物品索引
private:
    bool GetMailTitle(char* pszTitle, int nByte);                       //获得发送的标题
    bool GetMailSender(SMail::SAddress *pAddress,int nCount);                      //获得发信人
    bool GetMailContext(char* pszContext,int nByte);                    //获得发送的正文
    bool GetMoney(uint32 &uMoney,bool bNeed = false);                                      //获得发送的钱
    bool GetMailItem(uint8 bagType,uint16 &bagIndex,__int64 &itemBigId);  //获得物件

	static void EditDataChange( OUT ControlObject* pSender, OUT const char *szData );
    static void OnVisibleChange( ControlObject* pUIObject ); 

private:
    MailType m_MailType;

    D3DXVECTOR3  m_vVisualPos;   //打开界面时玩家坐标


private:
	void ResetMembers();
	static void EditDataChangeEx( OUT ControlObject* pSender, OUT const char *szData );
    ControlFrame*	m_pID_FRAME_MailMain;
    ControlPicture*	m_pID_PICTURE_Title;
    ControlButton*	m_pID_BUTTON_CLOSE;
    ControlButton*	m_pID_BUTTON_Help;
    ControlPicture*	m_pID_PICTURE_BackGround;
    ControlCheckBox*	m_pID_CHECKBOX_SendMail;
    ControlCheckBox*	m_pID_CHECKBOX_ReceiveMail;
	ControlComboBox*	m_pID_COMBOBOX_MailTitle;
    ControlText*	m_pID_TEXT_SendTarget;
    ControlText*	m_pID_TEXT_CopyTarget;
    ControlText*	m_pID_TEXT_MailTitle;
    //ControlPicture*	m_pID_PICTURE_SendTarget;
    ControlPicture*	m_pID_PICTURE_MailTitle;
    ControlEdit*	m_pID_EDIT_MailTitle;
    ControlPicture*	m_pID_PICTURE_CopyTarget;
    ControlEdit*	m_pID_EDIT_CopyTarget;
    ControlPicture*	m_pID_PICTURE_MailContent;
    ControlEdit*	m_pID_EDIT_MailContent;
    ControlListImage*	m_pID_LISTIMG_MailItem;
    ControlText*	m_pID_TEXT_Cost;
    ControlButton*	m_pID_BUTTON_Reset;
    ControlText*	m_pID_TEXT_MailItem;
    ControlComboBox*	m_pID_COMBOBOX_SendTarget;
    ControlButton*	m_pID_BUTTON_Send;
    ControlPicture*	m_pID_PICTURE_Jin;
    ControlEdit*	m_pID_EDIT_Jin;
    ControlPicture*	m_pID_PICTURE_Ying;
    ControlEdit*	m_pID_EDIT_Ying;
    ControlPicture*	m_pID_PICTURE_Tong;
    ControlEdit*	m_pID_EDIT_Tong;
	ControlEdit*	m_pID_EDIT_SendTarget;
    ControlText*	m_pID_TEXT_MailMoney;
    ControlPicture*	m_pID_PICTURE_JinPic;
    ControlPicture*	m_pID_PICTURE_YingPic;
    ControlPicture*	m_pID_PICTURE_TongPic;

    ControlRadioGroup  m_TypeRadioGroup;
    ControlGroup       m_TypeGroup;
    ControlComboBox*   m_pID_COMBOBOX_CopyTarget;
	static const int MAX_OLD_TITLE_COUNT = 5;
	string m_strOldTitle[MAX_OLD_TITLE_COUNT];
	__int64				m_LogID;
};
extern CUI_ID_FRAME_MailMain s_CUI_ID_FRAME_MailMain;
