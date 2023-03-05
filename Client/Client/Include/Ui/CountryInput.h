/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\国家界面\CountryInput.h
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
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	void SetShowType( int showType );									//调用的原因
	bool EditInputIsVisable();											//输入法

	//服务端消息
	void GetAppointResult( const MsgCountryOfficialAppointAck* pMsg );	//获取任命结果
	void GetDismissResult( const MsgCountryOfficialRecallAck* pMsg );	//获取罢免结果
	void GetOperateResult( const MsgCountryOperateToPlayerAck* pMsg );	//获取操作结果(禁言、囚禁、赦免)
	void GetBeOperatedInfo( uint8 operateType );						//获取被操作信息
	void GetBeAppointInfo( const MsgCountryTellAppoint* pMsg );			//获取被任命信息
    void GetPlayerBeOperatedInfo( MsgTellOperateToCountry* pMsg );   // 获取玩家被国王XX信息

private:
	static bool InputBox_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );

	void ResetProperties();				//重置控件属性
	
private:
	int			m_nShowType;		//显示用途	
	std::string m_strDescribe;		//描述
	std::string m_strTips;			//提示
	std::string m_strPlayerName;	//玩家名

};
extern CUI_ID_FRAME_CountryInput s_CUI_ID_FRAME_CountryInput;
