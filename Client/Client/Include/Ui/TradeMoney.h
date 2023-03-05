/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\����\TradeMoney.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_TradeMoney
#define ID_FRAME_TradeMoney		"ID_FRAME_TradeMoney"
#endif  ID_FRAME_TradeMoney
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_EDIT_Jin
#define ID_EDIT_Jin		"ID_EDIT_Jin"
#endif  ID_EDIT_Jin
#ifndef ID_EDIT_Yin
#define ID_EDIT_Yin		"ID_EDIT_Yin"
#endif  ID_EDIT_Yin
#ifndef ID_EDIT_Tong
#define ID_EDIT_Tong		"ID_EDIT_Tong"
#endif  ID_EDIT_Tong
#ifndef ID_BUTTON_Cancle
#define ID_BUTTON_Cancle		"ID_BUTTON_Cancle"
#endif  ID_BUTTON_Cancle
#ifndef ID_TEXT_Caption
#define ID_TEXT_Caption		"ID_TEXT_Caption"
#endif  ID_TEXT_Caption
#ifndef ID_TEXT_Describe
#define ID_TEXT_Describe		"ID_TEXT_Describe"
#endif  ID_TEXT_Describe


class CUI_ID_FRAME_TradeMoney : public CUIBase
{
public:
    typedef bool ( *funCallbackFun )( DWORD dwMoney, void *pData );

private:	
	 ControlFrame*	    m_pID_FRAME_TradeMoney;
	 ControlButton*	    m_pID_BUTTON_OK;
	 ControlEdit*	    m_pID_EDIT_Jin;
	 ControlEdit*	    m_pID_EDIT_Yin;
	 ControlEdit*	    m_pID_EDIT_Tong;
	 ControlButton*	    m_pID_BUTTON_Cancle;
     ControlText*       m_pID_TEXT_Caption;
     ControlText*       m_pID_TEXT_Describe;

public:	
    CUI_ID_FRAME_TradeMoney();
	bool EditInputIsVisable();
    bool OnFrameRun();
	bool OnFrameRender();
    bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancleOnButtonClick( ControlObject* pSender );

public:
	bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	bool _UnLoadUI();			// ж��UI
	bool _IsVisable();			// �Ƿ�ɼ�
	void _SetVisable( const bool bVisable );			// �����Ƿ����

    bool ShowMoneyInput( funCallbackFun fun, std::string strCaption = "", std::string strDescribe = "",
        DWORD dwMaxMoney = 0, void* pData = NULL, unsigned int nDataLength = 0 );

protected:
    void ResetMembers();
    static void EditDataChange( OUT ControlObject* pSender, OUT const char *szData );
    void CheckMoney();
    void SetCheckEnable( bool bEnable );
    bool IsCheckEnable();
    void SetMoney( DWORD dwMoney );
    DWORD GetMoney();

private:
    bool    m_bCheckMoney;          // �Ƿ��н�Ǯ������£�������Ҫ����Ƿ񳬹�����
    DWORD   m_dwMaxMoney;           // �����ӿ����õ���������Ǯ���ƣ�Ϊ0���ǲ�����

    funCallbackFun      m_pMoneyCallbackFun;
    void*               m_pData;

};
extern CUI_ID_FRAME_TradeMoney s_CUI_ID_FRAME_TradeMoney;
