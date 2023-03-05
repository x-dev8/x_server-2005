/********************************************************************
	Created by UIEditor.exe
	FileName: D:\Program\XSanguoRun\Client\UI\Group_DeBuffUI.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_DeBuffUI
#define ID_FRAME_DeBuffUI		"ID_FRAME_DeBuffUI"
#endif  ID_FRAME_DeBuffUI
#ifndef ID_LISTIMG_DeBuffMe
#define ID_LISTIMG_DeBuffMe		"ID_LISTIMG_DeBuffMe"
#endif  ID_LISTIMG_DeBuffMe

#include "UiBase.h"
class CUI_ID_FRAME_DeBuffUI :public CUIBase
{
	// SGuildMember
public:	
	CUI_ID_FRAME_DeBuffUI();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_LISTIMG_DeBuffMeOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_DeBuffMeOnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_DeBuffMeOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    virtual void InitializeAtEnterWorld();
	void SetRefresh() { m_bRefresh = true; }

private:
	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����

public:
    void ClearListImage();
    virtual void SetVisableListImage(bool bVisable);
    ControlListImage* GetListImage(){if(!m_pID_FRAME_DeBuffUI) return NULL;return m_pID_LISTIMG_DeBuffMe;}
	bool IfHPBuffID ();
	bool IfMPBuffID ();

private:
    ControlFrame*	m_pID_FRAME_DeBuffUI;
    ControlListImage*	m_pID_LISTIMG_DeBuffMe;
	float m_fCheckSpareTimeCD;	// ÿ����һ��BUFFʣ��ʱ��
	int m_nBufferCount;
	void			RefreshBuffer();
	int m_bRefresh;
	int m_bBuffId; //buffID
};

extern CUI_ID_FRAME_DeBuffUI s_CUI_ID_FRAME_DeBuffUI;