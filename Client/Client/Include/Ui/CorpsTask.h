/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\����\�½��ļ��� (6)\CorpsTask.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_CorpsTask
#define ID_FRAME_CorpsTask		"ID_FRAME_CorpsTask"
#endif  ID_FRAME_CorpsTask
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_True
#define ID_BUTTON_True		"ID_BUTTON_True"
#endif  ID_BUTTON_True
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_LISTIMG_Icon
#define ID_LISTIMG_Icon		"ID_LISTIMG_Icon"
#endif  ID_LISTIMG_Icon

#include "UiBase.h"

class CUI_ID_FRAME_CorpsTask : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_CorpsTask();
	 ControlFrame*	m_pID_FRAME_CorpsTask;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlButton*	m_pID_BUTTON_True;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlListImage*	m_pID_LISTIMG_Icon;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_TrueOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_IconOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_IconOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_IconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_IconOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	bool _UnLoadUI();			// ж��UI
	bool _IsVisable();			// �Ƿ�ɼ�
	void _SetVisable( const bool bVisable );			// �����Ƿ����


public:
	void SetQuestID( short id );
protected:
	bool IsItemAlreadyIn( __int64 uuid );	//����Ƿ�ӱ��������Ϲ�����
private:	
	std::vector<__int64>	m_vtRequestItemUUID;//��ʱ�����ã�����Ҫ�ύ����Ʒ
	short m_nQuestID;			//����ID
	int m_nNpcId;
};
extern CUI_ID_FRAME_CorpsTask s_CUI_ID_FRAME_CorpsTask;
