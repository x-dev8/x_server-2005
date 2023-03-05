/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Work\HeroRuntime\Client\UI\ActionUI.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "MeUi/MouseManager.h"
#include "UIBase.h"

#ifndef ID_FRAME_ActionUI
#define ID_FRAME_ActionUI		"ID_FRAME_ActionUI"
#endif  ID_FRAME_ActionUI
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_Property
#define ID_BUTTON_Property		"ID_BUTTON_Property"
#endif  ID_BUTTON_Property
#ifndef ID_BUTTON_Tesk
#define ID_BUTTON_Tesk		"ID_BUTTON_Tesk"
#endif  ID_BUTTON_Tesk
#ifndef ID_LISTIMG_Dictate
#define ID_LISTIMG_Dictate		"ID_LISTIMG_Dictate"
#endif  ID_LISTIMG_Dictate
#ifndef ID_LISTIMG_UI
#define ID_LISTIMG_UI		"ID_LISTIMG_UI"
#endif  ID_LISTIMG_UI
#ifndef ID_LISTIMG_Action
#define ID_LISTIMG_Action		"ID_LISTIMG_Action"
#endif  ID_LISTIMG_Action
#ifndef ID_BUTTON_help
#define ID_BUTTON_help	"ID_BUTTON_help"
#endif ID_BUTTON_help 

#include "UiBase.h"
class CUI_ID_FRAME_ActionUI  :public CUIBase
{
public:
	
public:
	CUI_ID_FRAME_ActionUI();
	// SGuildMember
private:	
	 ControlFrame*	m_pID_FRAME_ActionUI;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlButton*	m_pID_BUTTON_Property;
	 ControlButton*	m_pID_BUTTON_Tesk;
	 ControlListImage*	m_pID_LISTIMG_Dictate;
	 ControlListImage*	m_pID_LISTIMG_UI;
	// ControlListImage*	m_pID_LISTIMG_Action;
	 int				m_nCurFunction;
	 MouseManager::E_CursorType	m_enCursorType;

	 ControlButton*		m_pID_BUTTON_help;
	 static bool helpOnClick( ControlObject* pSender );
public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PropertyOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_TeskOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_DictateOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_DictateOnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_DictateOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_UIOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_UIOnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_UIOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ActionOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ActionOnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ActionOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_UIOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	
	void Process();

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect( );	// 关连控件
	virtual bool _UnLoadUI();								// 卸载UI
	virtual bool _IsVisable();								// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	bool UseFunction();
	bool UsePick();
	void SetCurFunction( const int nFunction );
	int	 GetCurFunction()			{ return m_nCurFunction;}
// 	void SetVisableLayout();
};
extern CUI_ID_FRAME_ActionUI s_CUI_ID_FRAME_ActionUI;
