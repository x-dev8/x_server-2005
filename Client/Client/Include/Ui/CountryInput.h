/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\����\���ҽ���\CountryInput.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "Country.h"

#ifndef ID_FRAME_CountryInput
#define ID_FRAME_CountryInput		"ID_FRAME_CountryInput"
#endif  ID_FRAME_CountryInput
#ifndef ID_TEXT_CountryInputDesc
#define ID_TEXT_CountryInputDesc		"ID_TEXT_CountryInputDesc"
#endif  ID_TEXT_CountryInputDesc
#ifndef ID_EDIT_CountryInputName
#define ID_EDIT_CountryInputName		"ID_EDIT_CountryInputName"
#endif  ID_EDIT_CountryInputName
#ifndef ID_TEXT_CountryInputTips
#define ID_TEXT_CountryInputTips		"ID_TEXT_CountryInputTips"
#endif  ID_TEXT_CountryInputTips
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel

#include "UiBase.h"
class CUI_ID_FRAME_CountryInput :public CUIBase
{
	// Member
private:	
	 ControlFrame*	m_pID_FRAME_CountryInput;
	 ControlText*	m_pID_TEXT_CountryInputDesc;
	 ControlEdit*	m_pID_EDIT_CountryInputName;
	 ControlText*	m_pID_TEXT_CountryInputTips;
	 ControlButton*	m_pID_BUTTON_OK;
	 ControlButton*	m_pID_BUTTON_Cancel;

public:	
	CUI_ID_FRAME_CountryInput();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_EDIT_CountryInputNameOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����
public:


	void SetShowType( int showType );									//���õ�ԭ��
	bool EditInputIsVisable();											//���뷨

	//�������Ϣ
	void GetAppointResult( const MsgCountryOfficialAppointAck* pMsg );	//��ȡ�������
	void GetDismissResult( const MsgCountryOfficialRecallAck* pMsg );	//��ȡ������
	void GetOperateResult( const MsgCountryOperateToPlayerAck* pMsg );	//��ȡ�������(���ԡ�����������)
	void GetBeOperatedInfo( uint8 operateType );						//��ȡ��������Ϣ
	void GetBeAppointInfo( const MsgCountryTellAppoint* pMsg );			//��ȡ��������Ϣ
    void GetPlayerBeOperatedInfo( MsgTellOperateToCountry* pMsg );   // ��ȡ��ұ�����XX��Ϣ

private:
	static bool InputBox_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );

	void ResetProperties();				//���ÿؼ�����
	
private:
	int			m_nShowType;		//��ʾ��;	
	std::string m_strDescribe;		//����
	std::string m_strTips;			//��ʾ
	std::string m_strPlayerName;	//�����

};
extern CUI_ID_FRAME_CountryInput s_CUI_ID_FRAME_CountryInput;
