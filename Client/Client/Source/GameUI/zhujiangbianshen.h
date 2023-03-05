/********************************************************************
	Created by UIEditor.exe
	FileName: F:\3Guo Client\Data\Ui\zhujiangbianshen.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UiBase.h"
#include "ItemEnableChangeSysBase.h"
#ifndef ID_FRAME_zhujiangbianshen
#define ID_FRAME_zhujiangbianshen		"ID_FRAME_zhujiangbianshen"
#endif  ID_FRAME_zhujiangbianshen
#ifndef ID_PICTURE_zhujiangtouxiang
#define ID_PICTURE_zhujiangtouxiang		"ID_PICTURE_zhujiangtouxiang"
#endif  ID_PICTURE_zhujiangtouxiang
#ifndef ID_PICTURE_nameLV
#define ID_PICTURE_nameLV		"ID_PICTURE_nameLV"
#endif  ID_PICTURE_nameLV
#ifndef ID_TEXT_jieshao
#define ID_TEXT_jieshao		"ID_TEXT_jieshao"
#endif  ID_TEXT_jieshao
#ifndef ID_PICTURE_ability
#define ID_PICTURE_ability		"ID_PICTURE_ability"
#endif  ID_PICTURE_ability
#ifndef ID_LISTIMG_skill
#define ID_LISTIMG_skill		"ID_LISTIMG_skill"
#endif  ID_LISTIMG_skill
#ifndef ID_BUTTON_dianjiangpai
#define ID_BUTTON_dianjiangpai		"ID_BUTTON_dianjiangpai"
#endif  ID_BUTTON_dianjiangpai
#ifndef ID_TEXT_money
#define ID_TEXT_money		"ID_TEXT_money"
#endif  ID_TEXT_money
#ifndef ID_TEXT_needLV
#define ID_TEXT_needLV		"ID_TEXT_needLV"
#endif  ID_TEXT_needLV
#ifndef ID_BUTTON_ok
#define ID_BUTTON_ok		"ID_BUTTON_ok"
#endif  ID_BUTTON_ok
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_LISTIMG_bianshenitem
#define ID_LISTIMG_bianshenitem		"ID_LISTIMG_bianshenitem"
#endif  ID_LISTIMG_bianshenitem
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_PICTURE_warability
#define ID_PICTURE_warability		"ID_PICTURE_warability"
#endif  ID_PICTURE_warability
#ifndef ID_LISTIMG_dianjiangpai
#define ID_LISTIMG_dianjiangpai		"ID_LISTIMG_dianjiangpai"
#endif	ID_LISTIMG_dianjiangpai

class CUI_ID_FRAME_zhujiangbianshen:public CUIBase, CItemEnableChangeSysBase
{
	// Member
public:	
	 CUI_ID_FRAME_zhujiangbianshen();
	 ControlFrame*	m_pID_FRAME_zhujiangbianshen;
	 ControlPicture*	m_pID_PICTURE_zhujiangtouxiang;
	 ControlPicture*	m_pID_PICTURE_nameLV;
	 ControlText*	m_pID_TEXT_jieshao;
	 ControlPicture*	m_pID_PICTURE_ability;
	 ControlListImage*	m_pID_LISTIMG_skill;
	 ControlButton*	m_pID_BUTTON_dianjiangpai;
	 ControlText*	m_pID_TEXT_money;
	 ControlText*	m_pID_TEXT_needLV;
	 ControlButton*	m_pID_BUTTON_ok;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlListImage*	m_pID_LISTIMG_bianshenitem;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlPicture*	m_pID_PICTURE_warability;
	 ControlListImage*	m_pID_LISTIMG_dianjiangpai;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_LISTIMG_skillOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_skillOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_skillOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_skillOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_dianjiangpaiOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_okOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_bianshenitemOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_bianshenitemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_bianshenitemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_bianshenitemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_dianjiangpaiOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_dianjiangpaiOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_dianjiangpaiOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_dianjiangpaiOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	//bool LoadUI();				// 载入UI
	//bool DoControlConnect();	// 关连控件
	//bool UnLoadUI();			// 卸载UI
	//bool IsVisable();			// 是否可见
	//void SetVisable( const bool bVisable );			// 设置是否可视

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
	virtual bool IsHoldInMemory() const { return true; }
	virtual void InitializeAtEnterWorld();
	virtual bool IsPackItemBeUsing( __int64 nGuid );
	void SendMsg();

public:
	void Refresh();
	bool clear();
	void SetItemID(uint16 ID){item_id = ID;}
	bool IsSkillList(const ControlObject* pObject);
	uint16 item_id;
	uint16 nItemIndex;
	__int64 OnlyItemID;
};


extern CUI_ID_FRAME_zhujiangbianshen s_CUI_ID_FRAME_zhujiangbianshen;
//extern int hero_id;