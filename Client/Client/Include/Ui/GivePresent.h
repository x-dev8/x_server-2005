/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Document\�߻��ĵ�\GivePresent.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "ItemEnableChangeSysBase.h"

#ifndef ID_FRAME_GivePresent
#define ID_FRAME_GivePresent		"ID_FRAME_GivePresent"
#endif  ID_FRAME_GivePresent
#ifndef ID_PICTURE_RightTitle
#define ID_PICTURE_RightTitle		"ID_PICTURE_RightTitle"
#endif  ID_PICTURE_RightTitle
#ifndef ID_PICTURE_MiddleTitle
#define ID_PICTURE_MiddleTitle		"ID_PICTURE_MiddleTitle"
#endif  ID_PICTURE_MiddleTitle
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_help
#define ID_BUTTON_help		"ID_BUTTON_help"
#endif  ID_BUTTON_help
#ifndef ID_PICTURE_ItemWall
#define ID_PICTURE_ItemWall		"ID_PICTURE_ItemWall"
#endif  ID_PICTURE_ItemWall
#ifndef ID_LISTIMG_Item
#define ID_LISTIMG_Item		"ID_LISTIMG_Item"
#endif  ID_LISTIMG_Item
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_PICTURE_LeftTitle
#define ID_PICTURE_LeftTitle		"ID_PICTURE_LeftTitle"
#endif  ID_PICTURE_LeftTitle
#ifndef ID_PICTURE_TitleWord
#define ID_PICTURE_TitleWord		"ID_PICTURE_TitleWord"
#endif  ID_PICTURE_TitleWord
#ifndef ID_TEXT_Explain
#define ID_TEXT_Explain		"ID_TEXT_Explain"
#endif  ID_TEXT_Explain

#include "UiBase.h"

class CUI_ID_FRAME_GivePresent :public CUIBase, CItemEnableChangeSysBase
{
	// Member
private:
	ControlFrame*	m_pID_FRAME_GivePresent;
	ControlPicture*	m_pID_PICTURE_RightTitle;
	ControlPicture*	m_pID_PICTURE_MiddleTitle;
	ControlButton*	m_pID_BUTTON_CLOSE;
	ControlButton*	m_pID_BUTTON_help;
	ControlPicture*	m_pID_PICTURE_ItemWall;
	ControlListImage*	m_pID_LISTIMG_Item;
	ControlButton*	m_pID_BUTTON_Ok;
	ControlButton*	m_pID_BUTTON_Cancel;
	ControlPicture*	m_pID_PICTURE_LeftTitle;
	ControlPicture*	m_pID_PICTURE_TitleWord;
	ControlText*	m_pID_TEXT_Explain;

public:	
	CUI_ID_FRAME_GivePresent();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_ItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );

	virtual bool IsPackItemBeUsing( __int64 nGuid );

private:
	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����
public:


	bool SetTarget(short shPlayerID);
	bool PutItemFromPack(ControlObject* pSender, ControlIconDrag::S_ListImg* pItemDrag, int iBagType, int iItemIndex);	// Ĭ���Ǵ���ͨ��������Ʒ
	void OnFailed();

private:
	static void OnVisibleChanged(ControlObject* pSender);

	void EnableBagItem( bool bEnable, int iBagType, int iItemIndex );
	void ClearItem();

	short			m_shTargetID;						// ���ͺ�������
	int				m_iBagType;							// ��������
	int				m_iItemIndex;						// ������λ��
	__int64			m_n64ItemGuild;						// ��ƷGUID
	int				m_iItemCount;						// ��Ʒ����
	DWORD			m_dwCDEndTime;						// ��ƷCD����ʱ��
};
extern CUI_ID_FRAME_GivePresent s_CUI_ID_FRAME_GivePresent;
