/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Code\RunTime\CLIENT\Data\UI\Message.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_MESSAGE
#define ID_FRAME_MESSAGE		"ID_FRAME_MESSAGE"
#endif  ID_FRAME_MESSAGE
#ifndef ID_EDIT_INFO
#define ID_EDIT_INFO		"ID_EDIT_INFO"
#endif  ID_EDIT_INFO
#ifndef ID_BUTTON_YES
#define ID_BUTTON_YES		"ID_BUTTON_YES"
#endif  ID_BUTTON_YES
#ifndef ID_BUTTON_NO
#define ID_BUTTON_NO		"ID_BUTTON_NO"
#endif  ID_BUTTON_NO
#ifndef ID_BUTTON_COMFIRM
#define ID_BUTTON_COMFIRM		"ID_BUTTON_COMFIRM"
#endif  ID_BUTTON_COMFIRM
#ifndef ID_TEXT_CAPTION
#define ID_TEXT_CAPTION		"ID_TEXT_CAPTION"
#endif  ID_TEXT_CAPTION
#ifndef ID_BUTTON_JieShou
#define ID_BUTTON_JieShou		"ID_BUTTON_JieShou"
#endif  ID_BUTTON_JieShou
#ifndef ID_BUTTON_JvJue
#define ID_BUTTON_JvJue		"ID_BUTTON_JvJue"
#endif  ID_BUTTON_JvJue
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_TEXT_CHECKLeft
#define ID_TEXT_CHECKLeft		"ID_TEXT_CHECKLeft"
#endif  ID_TEXT_CHECKLeft
#ifndef ID_CHECKBOX_CheckLeft
#define ID_CHECKBOX_CheckLeft		"ID_CHECKBOX_CheckLeft"
#endif  ID_CHECKBOX_CheckLeft
#ifndef ID_CHECKBOX_CheckRight
#define ID_CHECKBOX_CheckRight		"ID_CHECKBOX_CheckRight"
#endif  ID_CHECKBOX_CheckRight
#ifndef ID_CHECKBOX_CheckMiddle
#define ID_CHECKBOX_CheckMiddle		"ID_CHECKBOX_CheckMiddle"
#endif  ID_CHECKBOX_CheckMiddle
#ifndef ID_TEXT_CHECKRIGHT
#define ID_TEXT_CHECKRIGHT	"ID_TEXT_CHECKRIGHT"
#endif  ID_TEXT_CHECKRIGHT
#ifndef ID_TEXT_CHECKMiddle
#define ID_TEXT_CHECKMiddle		"ID_TEXT_CHECKMiddle"
#endif  ID_TEXT_CHECKMiddle
#ifndef ID_EDIT_INFO2
#define ID_EDIT_INFO2		"ID_EDIT_INFO2"
#endif  ID_EDIT_INFO2
#ifndef ID_PICTURE_Wall2
#define ID_PICTURE_Wall2		"ID_PICTURE_Wall2"
#endif  ID_PICTURE_Wall2
#ifndef ID_PICTURE_Wall
#define ID_PICTURE_Wall		"ID_PICTURE_Wall"
#endif  ID_PICTURE_Wall
#ifndef ID_BUTTON_YES2
#define ID_BUTTON_YES2		"ID_BUTTON_YES2"
#endif  ID_BUTTON_YES2
#ifndef ID_BUTTON_NO2
#define ID_BUTTON_NO2		"ID_BUTTON_NO2"
#endif  ID_BUTTON_NO2
#ifndef ID_BUTTON_MoveHei2
#define ID_BUTTON_MoveHei2		"ID_BUTTON_MoveHei2"
#endif  ID_BUTTON_MoveHei2
#ifndef ID_BUTTON_SeekEquip
#define ID_BUTTON_SeekEquip		"ID_BUTTON_SeekEquip"
#endif  ID_BUTTON_SeekEquip


#define MESSAGE_BOX_CHECK_NUM 3

#include "UiBase.h"
class CUI_ID_FRAME_MessageBox :public CUIBase
{
public:
    CUI_ID_FRAME_MessageBox();

	void ClearMessageCache();
	typedef bool (*funCallbackFun)( const char bPressYesButton, void *pData );
    typedef std::map<unsigned long, std::string> CheckInfoContainer;

	enum ERetType
	{
		eTypeNo				= 0,
		eTypeYes			= 1,
		eTypeExternal		= 2,
	};
	enum EType
	{   
        eTypeNothing       = 0,
		eTypeConfirm,	    // 确定
		eTypeCancel,             	// 取消
		eTypeYesNo,             	// 是/否
		eTypeYesNoExternal,             	// 是/否/额外
		eTypeAcceptReject,           // 接受/拒绝    
		eTypeYesNoSeek,           // 是/否/查看装备
	};

    enum MessageBoxType
    {
        eTypeNone        = 0,
        eTypeCheckLeft   = 1 << 1,  // Left CheckBox
        eTypeCheckRight  = 1 << 2,  // Right CheckBox
        eTypeCheckMiddle = 1 << 3   // Middle CheckBox
	};

	// struct
	struct S_MessageBox
	{
		S_MessageBox()
		{
			m_eType = eTypeConfirm;
			m_pCallbackFun = NULL;
			m_bModal = true;
			m_pData = NULL;
			dwStartTime = 0;
			dwAutoCloseTime = 0;
			bDefaultYES = true;
			useHotKeyCount = 0;
		}
		std::string m_strCaption;
		std::string m_strInfo;
		EType m_eType;
		bool m_bModal;
		funCallbackFun	m_pCallbackFun;
		void	*m_pData;
		//
		DWORD	dwStartTime;
		DWORD	dwAutoCloseTime;
		bool    bDefaultYES;
		int		useHotKeyCount;
	};

	struct MessageBoxResult 
    {
        std::map<unsigned long, bool> checks;
        bool ok;

        MessageBoxResult()
        {
            Reset();
        }

        void Reset()
        {
            checks.clear();
            ok = false;
        }
    };


	void Show( const char* szText, const char* szCaption = "", EType type = eTypeConfirm,
				const bool bModal = false, const funCallbackFun pFun = NULL,
                void *pData = NULL, const int nDataLength = 0
				);
    // bDefaultYES是自动关闭时消息框默认操作 
	bool SetAutoClose( DWORD dwSecond, bool bDefaultYES = true );
	// 时间到了
	bool IsTimeOut();

	bool OnButtonClick( char bResult );

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	// Button
	bool ID_BUTTON_YESOnButtonClick( ControlObject* pMe );
	// Button
	bool ID_BUTTON_NOOnButtonClick( ControlObject* pMe );
	// Button
	bool ID_BUTTON_COMFIRMOnButtonClick(ControlObject* pMe);
	bool ID_BUTTON_JieShouOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_JvJueOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_YES2OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_NO2OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_MoveHei2OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SeekEquipOnButtonClick( ControlObject* pSender );

	virtual bool IsHoldInMemory() const { return true; }

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

	void Refeash();

	void UpdateMsgInfo(const char* msgInfo);

    void closeAll( bool ok );
    void closeAllMatchString( int nOffset, const char* szText );     // 关闭从第nOffset个开始所有包含szText的message box，要慎重使用

    bool HasModaleMessageBox();
    bool HasMessageBoxMatchString(const char* szText);               // 是否有包含szText的message box

    static bool MessageBox_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );
    static void OnVisibleChanged( ControlObject* pSender );

    std::list<S_MessageBox> m_ltMessagBox;

    bool IsEnableOnButCancel();
    void SetButEnableCancel(bool bValue);
    void SetButVisableCancel(bool bValue);


    void SetButYesCaption(const char* pszValue);
    void SetButNoCaption(const char *pszValue);

    void SetButConfirmVisable(bool bValue);
    void SetButConfirmEnable(bool bValue);
    bool IsEnableOnButConfirm();

    const char *GetTextCaption();

private:
	void ResetMembers();
	void VisableButtons( EType type, S_MessageBox* msgBoxData );

    bool            m_bTimeOut;
    BOOL			m_bUnLoaded;
private:
    // SGuildMember
    ControlFrame*	m_pID_FRAME_MESSAGE;
    ControlText*	m_pID_EDIT_INFO;
    ControlButton*	m_pID_BUTTON_YES;
    ControlButton*	m_pID_BUTTON_NO;
    ControlButton*  m_pID_BUTTON_COMFIRM;
    ControlText*	m_pID_TEXT_CAPTION;
    ControlButton*	m_pID_BUTTON_JieShou;
    ControlButton*	m_pID_BUTTON_JvJue;
    ControlButton*	m_pID_BUTTON_Cancel;
    ControlCheckBox* m_pCheckLeft;
    ControlCheckBox* m_pCheckRight;
    ControlCheckBox* m_pCheckMiddle;
    ControlText*    m_pID_TEXT_CHECKRIGHT;
    ControlText*    m_pID_TEXT_CHECKLeft;
    ControlText*    m_pID_TEXT_CHECKMiddle;
    ControlText*	m_pID_EDIT_INFO2;
    ControlPicture*	m_pID_PICTURE_Wall2;
    ControlPicture*	m_pID_PICTURE_Wall;
    ControlButton*	m_pID_BUTTON_YES2;
    ControlButton*	m_pID_BUTTON_NO2;
    ControlButton*	m_pID_BUTTON_MoveHei2;
	ControlButton*	m_pID_BUTTON_SeekEquip;

};
extern CUI_ID_FRAME_MessageBox s_CUI_ID_FRAME_MessageBox;