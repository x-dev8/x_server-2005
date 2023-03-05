/********************************************************************
	Created by UIEditor.exe
	FileName: D:\My Documents\桌面\BatchShop.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_BatchShop
#define ID_FRAME_BatchShop		"ID_FRAME_BatchShop"
#endif  ID_FRAME_BatchShop
#ifndef ID_TEXT_Msg
#define ID_TEXT_Msg		"ID_TEXT_Msg"
#endif  ID_TEXT_Msg
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_BUTTON_Cancle
#define ID_BUTTON_Cancle		"ID_BUTTON_Cancle"
#endif  ID_BUTTON_Cancle
#ifndef ID_PICTURE_TotalPriceWall
#define ID_PICTURE_TotalPriceWall		"ID_PICTURE_TotalPriceWall"
#endif  ID_PICTURE_TotalPriceWall
#ifndef ID_TEXT_TotalPriceZ
#define ID_TEXT_TotalPriceZ		"ID_TEXT_TotalPriceZ"
#endif  ID_TEXT_TotalPriceZ
#ifndef ID_TEXT_TotalPrice
#define ID_TEXT_TotalPrice		"ID_TEXT_TotalPrice"
#endif  ID_TEXT_TotalPrice
#ifndef ID_PICTURE_Number
#define ID_PICTURE_Number		"ID_PICTURE_Number"
#endif  ID_PICTURE_Number
#ifndef ID_EDIT_Number
#define ID_EDIT_Number		"ID_EDIT_Number"
#endif  ID_EDIT_Number
#ifndef ID_BUTTON_Up
#define ID_BUTTON_Up		"ID_BUTTON_Up"
#endif  ID_BUTTON_Up
#ifndef ID_BUTTON_Down
#define ID_BUTTON_Down		"ID_BUTTON_Down"
#endif  ID_BUTTON_Down
#ifndef ID_BUTTON_Max
#define ID_BUTTON_Max		"ID_BUTTON_Max"
#endif  ID_BUTTON_Max

typedef bool (*funBatchCallbackFun)( const char* szInputData, void *pData );

#include "UiBase.h"
class CUI_ID_FRAME_BatchShop :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_BatchShop();
private:
	 ControlFrame*	m_pID_FRAME_BatchShop;
	 ControlText*	m_pID_TEXT_Msg;
	 ControlButton*	m_pID_BUTTON_OK;
	 ControlButton*	m_pID_BUTTON_Cancle;
	 ControlPicture*	m_pID_PICTURE_TotalPriceWall;
	 ControlText*	m_pID_TEXT_TotalPriceZ;
	 ControlText*	m_pID_TEXT_TotalPrice;
	 ControlPicture*	m_pID_PICTURE_Number;
	 ControlEdit*	m_pID_EDIT_Number;
	 ControlButton*	m_pID_BUTTON_Up;
	 ControlButton*	m_pID_BUTTON_Down;
	 ControlButton*	m_pID_BUTTON_Max;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancleOnButtonClick( ControlObject* pSender );
	void ID_EDIT_NumberOnEditEnter( ControlObject* pSender, const char* szData );	
	bool ID_BUTTON_UpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DownOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_MaxOnButtonClick( ControlObject* pSender );
	bool EditInputIsVisable();

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

	void Refresh();

public:
	static void Show( const char* szCaption, const bool bIsNumber = true, const bool bModal = true,
		const funBatchCallbackFun pFun = NULL, void *pData = NULL, const int nDataLength = 0 , const bool bIfPwd = false,int nMaxLength = 2,bool bPrivateShop = false);
	static bool InputBox_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );
	static void EditDataChange( OUT ControlObject* pSender, OUT const char *szData );

	void SetMaxValue(int max) 
	{
		m_nMaxNumber = max;
		m_pID_EDIT_Number->SetNumberLimit(true, 0, m_nMaxNumber);
	}

	void SetEditDataChangedCallback(ControlEdit::funOnTextChanged fun)
	{
		m_pID_EDIT_Number->SetTextChangedFun(fun);
	}

	void SetEditNumber( int i );
	void SetTextTotalPrice( string str );
	const char* GetEditNumberText();
private:
	int m_nMaxNumber;

	static bool ms_bPrivateShop;
};
extern CUI_ID_FRAME_BatchShop s_CUI_ID_FRAME_BatchShop;
