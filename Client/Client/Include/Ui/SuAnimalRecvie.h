/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\SuAnimalRecvie.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#ifndef ID_FRAME_SuAnimalRecvie
#define ID_FRAME_SuAnimalRecvie		"ID_FRAME_SuAnimalRecvie"
#endif  ID_FRAME_SuAnimalRecvie
#ifndef ID_BUTTON_Recvie
#define ID_BUTTON_Recvie		"ID_BUTTON_Recvie"
#endif  ID_BUTTON_Recvie

class CUI_ID_FRAME_SuAnimalRecvie : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_SuAnimalRecvie();
	 ControlFrame*	m_pID_FRAME_SuAnimalRecvie;
	 ControlButton*	m_pID_BUTTON_Recvie;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_RecvieOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );// 设置是否可视
	virtual void InitializeAtEnterWorld();
	virtual bool IsHoldInMemory() const { return true; }
};
extern CUI_ID_FRAME_SuAnimalRecvie s_CUI_ID_FRAME_SuAnimalRecvie;
