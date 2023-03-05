/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\����\�½��ļ��� (22)\CrowdCarryMain.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_CrowdCarryMain
#define ID_FRAME_CrowdCarryMain		"ID_FRAME_CrowdCarryMain"
#endif  ID_FRAME_CrowdCarryMain
#ifndef ID_TEXT_Amount
#define ID_TEXT_Amount		"ID_TEXT_Amount"
#endif  ID_TEXT_Amount
#ifndef ID_BUTTON_Live
#define ID_BUTTON_Live		"ID_BUTTON_Live"
#endif  ID_BUTTON_Live
#ifndef ID_TEXT_CZ
#define ID_TEXT_CZ		"ID_TEXT_CZ"
#endif  ID_TEXT_CZ

#include "UIBase.h"

class CUI_ID_FRAME_CrowdCarryMain : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_CrowdCarryMain();
	 ControlFrame*	m_pID_FRAME_CrowdCarryMain;
	 ControlText*	m_pID_TEXT_Amount;
	 ControlButton*	m_pID_BUTTON_Live;
	 ControlText*	m_pID_TEXT_CZ;

public:
	void SetHostViewer();
	void SetPassagerViewer();
	void SetTotalSet( int totalNum );
	void UpdateLeftSets( int passagerNum );

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_LiveOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	        // �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����
private:	
	int			m_iTotalSets;					//�����λ�������������Ҫ�����ڽ�������ʾ��λ������ͳ���õģ���player��ϵ�������ԷŴ�����
};
extern CUI_ID_FRAME_CrowdCarryMain s_CUI_ID_FRAME_CrowdCarryMain;
