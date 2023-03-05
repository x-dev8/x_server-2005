/********************************************************************
	Created by UIEditor.exe
	FileName: D:\SVNClient\sg_pro\3Guo_Main\FullClient\Data\Ui\FirstAddYuanBao.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#ifndef ID_FRAME_FirstAddYuanBao
#define ID_FRAME_FirstAddYuanBao		"ID_FRAME_FirstAddYuanBao"
#endif  ID_FRAME_FirstAddYuanBao
#ifndef ID_LISTIMG_ItemTips
#define ID_LISTIMG_ItemTips		"ID_LISTIMG_ItemTips"
#endif  ID_LISTIMG_ItemTips
#ifndef ID_BUTTON_ActionAddress
#define ID_BUTTON_ActionAddress		"ID_BUTTON_ActionAddress"
#endif  ID_BUTTON_ActionAddress
#ifndef ID_BUTTON_GetReword
#define ID_BUTTON_GetReword		"ID_BUTTON_GetReword"
#endif  ID_BUTTON_GetReword
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_TEXT_StrOne
#define ID_TEXT_StrOne		"ID_TEXT_StrOne"
#endif  ID_TEXT_StrOne
#ifndef ID_TEXT_StrTwo
#define ID_TEXT_StrTwo		"ID_TEXT_StrTwo"
#endif  ID_TEXT_StrTwo
#ifndef ID_TEXT_Info
#define ID_TEXT_Info		"ID_TEXT_Info"
#endif  ID_TEXT_Info

class CUI_ID_FRAME_FirstAddYuanBao : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_FirstAddYuanBao();
	 ControlFrame*	m_pID_FRAME_FirstAddYuanBao;
	 ControlListImage*	m_pID_LISTIMG_ItemTips;
	 ControlButton*	m_pID_BUTTON_ActionAddress;
	 ControlButton*	m_pID_BUTTON_GetReword;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlText*	m_pID_TEXT_StrOne;
	 ControlText*	m_pID_TEXT_StrTwo;
	 ControlText*	m_pID_TEXT_Info;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_LISTIMG_ItemTipsOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ItemTipsOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ItemTipsOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ItemTipsOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_ActionAddressOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_GetRewordOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	void OnShow(unsigned int Value);//显示指定的数据
	void SetEmpty();

	void Update();

	void GetReward();
private:
	unsigned int		m_OnlyValue;//当前显示的数据标记值
};
extern CUI_ID_FRAME_FirstAddYuanBao s_CUI_ID_FRAME_FirstAddYuanBao;
