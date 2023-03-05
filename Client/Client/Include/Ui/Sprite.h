/********************************************************************
	Created by UIEditor.exe
	FileName: F:\project\Turbo\Bin\Client\Data\Ui\Sprite.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_Sprite
#define ID_FRAME_Sprite		"ID_FRAME_Sprite"
#endif  ID_FRAME_Sprite
#ifndef ID_TEXT_Sprite
#define ID_TEXT_Sprite		"ID_TEXT_Sprite"
#endif  ID_TEXT_Sprite

#include "UiBase.h"
class CUI_ID_FRAME_Sprite: public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_Sprite();
	ControlFrame*	m_pID_FRAME_Sprite;
	ControlText*	m_pID_TEXT_Sprite;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();

	void Refresh();

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:
	void ResetFramePos();
};
extern CUI_ID_FRAME_Sprite s_CUI_ID_FRAME_Sprite;