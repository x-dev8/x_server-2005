/********************************************************************
	Created by UIEditor.exe
	FileName: E:\sanguo\Data\Ui\OnBiaoChe.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_OnBiaoChe
#define ID_FRAME_OnBiaoChe		"ID_FRAME_OnBiaoChe"
#endif  ID_FRAME_OnBiaoChe
#ifndef ID_BUTTON_OnVehicle
#define ID_BUTTON_OnVehicle		"ID_BUTTON_OnVehicle"
#endif  ID_BUTTON_OnVehicle
#ifndef ID_BUTTON_LeaveVehicle
#define ID_BUTTON_LeaveVehicle		"ID_BUTTON_LeaveVehicle"
#endif  ID_BUTTON_LeaveVehicle


class CPlayer;
class CUI_ID_FRAME_OnBiaoChe:public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_OnBiaoChe();
	 ControlFrame*	m_pID_FRAME_OnBiaoChe;
	 ControlButton*	m_pID_BUTTON_OnVehicle;
	 ControlButton*	m_pID_BUTTON_LeaveVehicle;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_OnVehicleOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_LeaveVehicleOnButtonClick( ControlObject* pSender );

	virtual bool IsHoldInMemory() const { return true; }

	void SetBiaoche(CPlayer *player);
	bool HaveBiaoche(){return mBiaoche!=NULL;}

	// ��ʾ���ڳ���ť
	void ShowBiaocheGetOnButton();

private:
	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����
	bool GetCanOp();

private:
	// ��ǰ�ڳ�CPlayer����
	CPlayer *mBiaoche;
	DWORD m_OpLastTime; 

};
extern CUI_ID_FRAME_OnBiaoChe s_CUI_ID_FRAME_OnBiaoChe;
