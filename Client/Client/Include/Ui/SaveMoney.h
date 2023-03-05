/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Document\仓库存钱\SaveMoney.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_SaveMoney
#define ID_FRAME_SaveMoney		"ID_FRAME_SaveMoney"
#endif  ID_FRAME_SaveMoney
#ifndef ID_TEXT_Msg
#define ID_TEXT_Msg		"ID_TEXT_Msg"
#endif  ID_TEXT_Msg
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
// #ifndef ID_BUTTON_Cancle
// #define ID_BUTTON_Cancle		"ID_BUTTON_Cancle"
// #endif  ID_BUTTON_Cancle
#ifndef ID_PICTURE_Jin
#define ID_PICTURE_Jin		"ID_PICTURE_Jin"
#endif  ID_PICTURE_Jin
#ifndef ID_PICTURE_Ying
#define ID_PICTURE_Ying		"ID_PICTURE_Ying"
#endif  ID_PICTURE_Ying
#ifndef ID_PICTURE_Tong
#define ID_PICTURE_Tong		"ID_PICTURE_Tong"
#endif  ID_PICTURE_Tong
#ifndef ID_EDIT_Jin
#define ID_EDIT_Jin		"ID_EDIT_Jin"
#endif  ID_EDIT_Jin
#ifndef ID_EDIT_Yin
#define ID_EDIT_Yin		"ID_EDIT_Yin"
#endif  ID_EDIT_Yin
#ifndef ID_EDIT_Tong
#define ID_EDIT_Tong		"ID_EDIT_Tong"
#endif  ID_EDIT_Tong
#ifndef ID_TEXT_MsgGet
#define ID_TEXT_MsgGet		"ID_TEXT_MsgGet"
#endif  ID_TEXT_MsgGet

#include "UiBase.h"
class CUI_ID_FRAME_SaveMoney :public CUIBase
{
	// Member
private:
	 ControlFrame*	m_pID_FRAME_SaveMoney;
	 ControlText*	m_pID_TEXT_Msg;
	 ControlButton*	m_pID_BUTTON_OK;
// 	 ControlButton*	m_pID_BUTTON_Cancle;
	 ControlPicture*	m_pID_PICTURE_Jin;
	 ControlPicture*	m_pID_PICTURE_Ying;
	 ControlPicture*	m_pID_PICTURE_Tong;
	 ControlEdit*	m_pID_EDIT_Jin;
	 ControlEdit*	m_pID_EDIT_Yin;
	 ControlEdit*	m_pID_EDIT_Tong;
	 ControlText*	m_pID_TEXT_MsgGet;

public:	
	CUI_ID_FRAME_SaveMoney();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
// 	bool ID_BUTTON_CancleOnButtonClick( ControlObject* pSender );
	void ID_EDIT_JinOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_YinOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_TongOnEditEnter( ControlObject* pSender, const char* szData );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

    void SetStorageType( unsigned char type ) { m_ucStorageType = type; }
	static bool frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );

protected:
	void CheckMoney();

    unsigned char   m_ucStorageType;    // MsgStorageMoneyReq::Operation类型
    int             m_iGold;
    int             m_iSilver;
    int             m_iCopper;

	float			m_fCheckMoneyCD;	// 每0.5秒检查一次钱，单位秒
};
extern CUI_ID_FRAME_SaveMoney s_CUI_ID_FRAME_SaveMoney;
