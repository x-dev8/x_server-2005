/********************************************************************
	Created by UIEditor.exe
	FileName: D:\SVNClient\sg_pro\3Guo_Main\FullClient\Data\Ui\ShowFirstAddYuanBao.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#ifndef ID_FRAME_ShowFirstAddYuanbao
#define ID_FRAME_ShowFirstAddYuanbao		"ID_FRAME_ShowFirstAddYuanbao"
#endif  ID_FRAME_ShowFirstAddYuanbao
#ifndef ID_BUTTON_OpenFirstAddYuanBao
#define ID_BUTTON_OpenFirstAddYuanBao		"ID_BUTTON_OpenFirstAddYuanBao"
#endif  ID_BUTTON_OpenFirstAddYuanBao

class CUI_ID_FRAME_ShowFirstAddYuanbao: public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_ShowFirstAddYuanbao();
	 ControlFrame*	m_pID_FRAME_ShowFirstAddYuanbao;
	 ControlButton*	m_pID_BUTTON_OpenFirstAddYuanBao;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_OpenFirstAddYuanBaoOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
	virtual bool IsHoldInMemory() const { return true; }

	void Update();
private:
	unsigned int		m_NowOnlyValue;
};
extern CUI_ID_FRAME_ShowFirstAddYuanbao s_CUI_ID_FRAME_ShowFirstAddYuanbao;
