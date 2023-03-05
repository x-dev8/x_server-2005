/********************************************************************
	Created by UIEditor.exe
	FileName: D:\FullBag(13.10.181)\Data\Ui\ShowThreeDay.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#ifndef ID_FRAME_ShowThreeDay
#define ID_FRAME_ShowThreeDay		"ID_FRAME_ShowThreeDay"
#endif  ID_FRAME_ShowThreeDay
#ifndef ID_TEXT_Time
#define ID_TEXT_Time		"ID_TEXT_Time"
#endif  ID_TEXT_Time
#ifndef ID_TEXT_Effect
#define ID_TEXT_Effect		"ID_TEXT_Effect"
#endif  ID_TEXT_Effect

class CUI_ID_FRAME_ShowThreeDay : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_ShowThreeDay();
	 ControlFrame*	m_pID_FRAME_ShowThreeDay;
	 ControlText*	m_pID_TEXT_Time;
	 ControlText*	m_pID_TEXT_Effect;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();

	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����
	virtual void InitializeAtEnterWorld();
	virtual bool IsHoldInMemory() const { return true; }


	bool ID_TEXT_EffectOnButtonClick( ControlObject* pSender );
private:
	void OnUpdate();
	void OnUpdateTime();
};
extern CUI_ID_FRAME_ShowThreeDay s_CUI_ID_FRAME_ShowThreeDay;
