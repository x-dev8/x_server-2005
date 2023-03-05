/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\AchieveFinish.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_AchieveFinish
#define ID_FRAME_AchieveFinish		"ID_FRAME_AchieveFinish"
#endif  ID_FRAME_AchieveFinish
#ifndef ID_LISTIMG_Icon0
#define ID_LISTIMG_Icon0		"ID_LISTIMG_Icon0"
#endif  ID_LISTIMG_Icon0
#ifndef ID_TEXT_Number0
#define ID_TEXT_Number0		"ID_TEXT_Number0"
#endif  ID_TEXT_Number0
#ifndef ID_LISTIMG_Award0
#define ID_LISTIMG_Award0		"ID_LISTIMG_Award0"
#endif  ID_LISTIMG_Award0
#ifndef ID_TEXT_Content0
#define ID_TEXT_Content0		"ID_TEXT_Content0"
#endif  ID_TEXT_Content0
#ifndef ID_TEXT_Data0
#define ID_TEXT_Data0		"ID_TEXT_Data0"
#endif  ID_TEXT_Data0
#ifndef ID_BUTTON_Award0
#define ID_BUTTON_Award0		"ID_BUTTON_Award0"
#endif  ID_BUTTON_Award0
#ifndef ID_PICTURE_AchivementComplete0
#define ID_PICTURE_AchivementComplete0		"ID_PICTURE_AchivementComplete0"
#endif  ID_PICTURE_AchivementComplete0
#ifndef ID_TEXT_Top0
#define ID_TEXT_Top0		"ID_TEXT_Top0"
#endif  ID_TEXT_Top0
class CSmartAnimation;
#include "UIBase.h"
class CUI_ID_FRAME_AchieveFinish : public CUIBase
{
public:
	// Member
	CUI_ID_FRAME_AchieveFinish();
private:	
	 ControlFrame*	m_pID_FRAME_AchieveFinish;
	 ControlListImage*	m_pID_LISTIMG_Icon0;
	 ControlText*	m_pID_TEXT_Number0;
	 ControlListImage*	m_pID_LISTIMG_Award0;
	 ControlText*	m_pID_TEXT_Content0;
	 ControlText*	m_pID_TEXT_Data0;
	 ControlButton*	m_pID_BUTTON_Award0;
	 ControlPicture*	m_pID_PICTURE_AchivementComplete0;
	 ControlText*	m_pID_TEXT_Top0;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool OnFrameRenderNeedRedraw();
	bool ID_LISTIMG_Icon0OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Icon0OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Icon0OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Icon0OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Award0OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Award0OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Award0OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Award0OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_Award0OnButtonClick( ControlObject* pSender );
	void SetCurrAchieve(int val,int64 dwFinishTime);
	virtual void	ResetDevice( );

protected:
	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视
private:	
	int							m_currAchieve;
	DWORD						m_UIShowBeginTime;
	int64						m_64FinishTime;
	bool						m_bAnimationShowOnce;

	DWORD						m_ShowBeginTime;
	CSmartAnimation*			m_pCoolDownAni;
	CSmartAnimation*			GetCoolDownAniNotNULL() ;
};
extern CUI_ID_FRAME_AchieveFinish s_CUI_ID_FRAME_AchieveFinish;
