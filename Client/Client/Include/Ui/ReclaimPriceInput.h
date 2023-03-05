/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\ReclaimPriceInput.h
*********************************************************************/
#pragma once

#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_Reclaim
#define ID_FRAME_Reclaim		"ID_FRAME_Reclaim"
#endif  ID_FRAME_Reclaim
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_TEXT_TotalPrice
#define ID_TEXT_TotalPrice		"ID_TEXT_TotalPrice"
#endif  ID_TEXT_TotalPrice
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
#ifndef ID_BUTTON_Cancle
#define ID_BUTTON_Cancle		"ID_BUTTON_Cancle"
#endif  ID_BUTTON_Cancle
#ifndef ID_EDIT_Jin
#define ID_EDIT_Jin		"ID_EDIT_Jin"
#endif  ID_EDIT_Jin
#ifndef ID_EDIT_Yin
#define ID_EDIT_Yin		"ID_EDIT_Yin"
#endif  ID_EDIT_Yin
#ifndef ID_EDIT_Tong
#define ID_EDIT_Tong		"ID_EDIT_Tong"
#endif  ID_EDIT_Tong

class CUI_ID_FRAME_Reclaim : public CUIBase
{
public:
    typedef bool ( *funCallbackFun )( DWORD dwPrice, int nCount, void *pData );

private:	
	 ControlFrame*	m_pID_FRAME_Reclaim;
	 ControlButton*	m_pID_BUTTON_OK;
	 ControlEdit*	m_pID_EDIT_Number;
	 ControlButton*	m_pID_BUTTON_Up;
	 ControlButton*	m_pID_BUTTON_Down;
	 ControlButton*	m_pID_BUTTON_Max;
	 ControlButton*	m_pID_BUTTON_Cancle;
	 ControlEdit*	m_pID_EDIT_Jin;
	 ControlEdit*	m_pID_EDIT_Yin;
	 ControlEdit*	m_pID_EDIT_Tong;
     ControlText*   m_pID_TEXT_TotalPrice;

public:	
    CUI_ID_FRAME_Reclaim();
    ~CUI_ID_FRAME_Reclaim();
    bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_UpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DownOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_MaxOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancleOnButtonClick( ControlObject* pSender );

	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视

    void    Show( funCallbackFun func, void* pData, unsigned int uiDataLength );
    bool    EditInputIsVisable();	
    DWORD   GetPrice();
    void    SetPrice( DWORD dwPrice );
    int     GetCount();
    void    SetCount( int nCount );
    void    SetTotalPriceString( const std::string& strPrice );

protected:
    void ResetMembers();
    static void EditDataChange( OUT ControlObject* pSender, OUT const char *szData );
    static bool InputBox_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );

private:
    const int       m_nItemMaxNum;
    
    void*           m_pData;
    funCallbackFun  m_pfCallBackFun;

};

extern CUI_ID_FRAME_Reclaim s_CUI_ID_FRAME_Reclaim;
