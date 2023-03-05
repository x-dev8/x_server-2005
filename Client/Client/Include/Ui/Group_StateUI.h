/********************************************************************
	Created by UIEditor.exe
	FileName: D:\Tj\Client\UI\Group_StateUI.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_StateUI
#define ID_FRAME_StateUI		"ID_FRAME_StateUI"
#endif  ID_FRAME_StateUI
#ifndef ID_LISTIMG_StateMe
#define ID_LISTIMG_StateMe		"ID_LISTIMG_StateMe"
#endif  ID_LISTIMG_StateMe

#include "UiBase.h"
class CUI_ID_FRAME_StateUI :public CUIBase
{
	// SGuildMember
public:	

	 CUI_ID_FRAME_StateUI();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_LISTIMG_StateMeOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_StateMeOnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_StateMeOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_StateMeOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    virtual void InitializeAtEnterWorld();

	void SetRefresh() { m_bRefresh = true; }
private:
	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����

public:
    ControlListImage* GetListImage(){if(!m_pID_FRAME_StateUI) return NULL;return m_pID_LISTIMG_StateMe;}

protected:
    ControlFrame*	m_pID_FRAME_StateUI;
    ControlListImage*	m_pID_LISTIMG_StateMe;

	float m_fCheckSpareTimeCD;	// ÿ����һ��BUFFʣ��ʱ��
	int m_nBufferCount;
	void			RefreshBuffer();
	int m_bRefresh;
};
extern CUI_ID_FRAME_StateUI s_CUI_ID_FRAME_StateUI;