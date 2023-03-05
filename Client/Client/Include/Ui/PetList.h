/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\����\PetList.h
*********************************************************************/
#pragma once

#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_PetList
#define ID_FRAME_PetList		"ID_FRAME_PetList"
#endif  ID_FRAME_PetList
#ifndef ID_LIST_PetList
#define ID_LIST_PetList		"ID_LIST_PetList"
#endif  ID_LIST_PetList
#ifndef ID_BUTTON_Info
#define ID_BUTTON_Info		"ID_BUTTON_Info"
#endif  ID_BUTTON_Info
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK

class CUI_ID_FRAME_PetList : public CUIBase
{
private:	
	 ControlFrame*	m_pID_FRAME_PetList;
	 ControlList*	m_pID_LIST_PetList;
	 ControlButton*	m_pID_BUTTON_Info;
	 ControlButton*	m_pID_BUTTON_OK;

public:	
    CUI_ID_FRAME_PetList();
    bool OnFrameRun();
	bool OnFrameRender();
	void ID_LIST_PetListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_InfoOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );

public:
	bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	bool _UnLoadUI();			// ж��UI
	bool _IsVisable();			// �Ƿ�ɼ�
	void _SetVisable( const bool bVisable );			// �����Ƿ����

    void ShowPetList( bool bShow );
    void Refresh();
    int  GetCharEmptySlot();

protected:
    static void OnVisibleChange( ControlObject* pUIObject );
    void ResetMembers();
    void SetCurrentSelectIndex( int nIndex );
    void SeekPetByIndex( int nIndex );
    void StoreMount();

private:
    int     m_nCurSelectId;

};
extern CUI_ID_FRAME_PetList s_CUI_ID_FRAME_PetList;
