/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\����\CountryResource.h
*********************************************************************/
#pragma once

#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_CountryResource
#define ID_FRAME_CountryResource		"ID_FRAME_CountryResource"
#endif  ID_FRAME_CountryResource
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_TEXT_Money
#define ID_TEXT_Money		"ID_TEXT_Money"
#endif  ID_TEXT_Money
#ifndef ID_BUTTON_MoneyInput
#define ID_BUTTON_MoneyInput		"ID_BUTTON_MoneyInput"
#endif  ID_BUTTON_MoneyInput

class CUI_ID_FRAME_CountryResource : public CUIBase
{
private:	
	 ControlFrame*	    m_pID_FRAME_CountryResource;
	 ControlButton*	    m_pID_BUTTON_OK;
	 ControlButton*	    m_pID_BUTTON_Cancel;
	 ControlText*	    m_pID_TEXT_Money;
	 ControlButton*	    m_pID_BUTTON_MoneyInput;

public:	
	CUI_ID_FRAME_CountryResource();
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_MoneyInputOnButtonClick( ControlObject* pSender );

	bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	bool _UnLoadUI();			// ж��UI
	bool _IsVisable();			// �Ƿ�ɼ�
	void _SetVisable( const bool bVisable );			// �����Ƿ����

    void ShowCountryDonate();
    static bool GetCountryDonateResult( DWORD dwMoney, void* pData );   // ����ļ���Ǯ����ص�

protected:
    void ResetMembers();
    void SetMoney( DWORD dwMoney );

private:
    DWORD       m_dwMoney;
};

extern CUI_ID_FRAME_CountryResource s_CUI_ID_FRAME_CountryResource;
