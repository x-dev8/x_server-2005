/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Users\zhangjiayi.SHENWANG\Desktop\TaskDialog.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "QuestDefine.h"
#include "QuestDefine.h"

#ifndef ID_FRAME_TaskDialog
#define ID_FRAME_TaskDialog		"ID_FRAME_TaskDialog"
#endif  ID_FRAME_TaskDialog
#ifndef ID_PICTURE_Player
#define ID_PICTURE_Player		"ID_PICTURE_Player"
#endif  ID_PICTURE_Player
#ifndef ID_PICTURE_NPC
#define ID_PICTURE_NPC		"ID_PICTURE_NPC"
#endif  ID_PICTURE_NPC
#ifndef ID_TEXT_Info
#define ID_TEXT_Info		"ID_TEXT_Info"
#endif  ID_TEXT_Info
#ifndef ID_TEXT_Tips
#define ID_TEXT_Tips		"ID_TEXT_Tips"
#endif  ID_TEXT_Tips
#ifndef ID_PICTURE_TipsPic
#define ID_PICTURE_TipsPic		"ID_PICTURE_TipsPic"
#endif  ID_PICTURE_TipsPic
#ifndef ID_LIST_Option
#define ID_LIST_Option		"ID_LIST_Option"
#endif  ID_LIST_Option

class CUI_ID_FRAME_TaskDialog : public CUIBase
{
	// Member
private:	
	 ControlFrame*	m_pID_FRAME_TaskDialog;
	 ControlPicture*	m_pID_PICTURE_Player;
	 ControlPicture*	m_pID_PICTURE_NPC;
	 ControlText*	m_pID_TEXT_Info;
	 ControlText*	m_pID_TEXT_Tips;
	 ControlPicture*	m_pID_PICTURE_TipsPic;
	 ControlList*	m_pID_LIST_Option;

private:
	QuestTalks	m_vTalks;
	//�����꼴������һ����˵����false������ǵ���ѡ��ʱ�������겻��ת
	bool m_bClickToContinue;
	bool m_bDirty;

	// �������ʹ��
	int m_nNpcId;
	bool m_bShow;

public:	
	CUI_ID_FRAME_TaskDialog();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();

	bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	bool _UnLoadUI();			// ж��UI
	bool _IsVisable();			// �Ƿ�ɼ�
	void _SetVisable( const bool bVisable );			// �����Ƿ����
	virtual bool IsHoldInMemory() const { return true; }
	virtual void InitializeAtEnterWorld();

	void ID_LIST_OptionOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	static bool MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );

public:
	bool PlayTalk( int nNpcId, bool bShow );
	bool IsClickToContinue(){ return m_bClickToContinue; }
	bool ContinueTalk();
	void SetDirty( bool bDirty ){ m_bDirty = bDirty; }

private:
	const std::string& GetBigHeadPicName( int nNpcId );
	const std::string GetPlayerHeadPicName();
	void SendRefreshMsg( uint16 questId, uint8 talkType );

private:	
};
extern CUI_ID_FRAME_TaskDialog s_CUI_ID_FRAME_TaskDialog;
