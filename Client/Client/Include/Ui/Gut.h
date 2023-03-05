#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "QuestDefine.h"

#ifndef ID_FRAME_Gut
#define ID_FRAME_Gut		"ID_FRAME_Gut"
#endif  ID_FRAME_Gut
#ifndef ID_TEXT_GoOn
#define ID_TEXT_GoOn		"ID_TEXT_GoOn"
#endif  ID_TEXT_GoOn
#ifndef ID_PICTURE_Backdrop
#define ID_PICTURE_Backdrop		"ID_PICTURE_Backdrop"
#endif  ID_PICTURE_Backdrop
#ifndef ID_TEXT_TextTitle
#define ID_TEXT_TextTitle		"ID_TEXT_TextTitle"
#endif  ID_TEXT_TextTitle
#ifndef ID_TEXT_NpcGut
#define ID_TEXT_NpcGut		"ID_TEXT_NpcGut"
#endif  ID_TEXT_NpcGut
#ifndef ID_BUTTON_Continue
#define ID_BUTTON_Continue		"ID_BUTTON_Continue"
#endif  ID_BUTTON_Continue
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_BUTTON_Refuse
#define ID_BUTTON_Refuse		"ID_BUTTON_Refuse"
#endif  ID_BUTTON_Refuse
#ifndef ID_BUTTON_Finish
#define ID_BUTTON_Finish		"ID_BUTTON_Finish"
#endif  ID_BUTTON_Finish
#ifndef ID_BUTTON_Accept
#define ID_BUTTON_Accept		"ID_BUTTON_Accept"
#endif  ID_BUTTON_Accept
#ifndef ID_PICTURE_NPC
#define ID_PICTURE_NPC		"ID_PICTURE_NPC"
#endif  ID_PICTURE_NPC
#ifndef ID_LIST_PlayerGut
#define ID_LIST_PlayerGut		"ID_LIST_PlayerGut"
#endif  ID_LIST_PlayerGut
#ifndef ID_TEXT_Money
#define ID_TEXT_Money		"ID_TEXT_Money"
#endif  ID_TEXT_Money
#ifndef ID_TEXT_EXP
#define ID_TEXT_EXP		"ID_TEXT_EXP"
#endif  ID_TEXT_EXP
#ifndef ID_LISTIMG_4592
#define ID_LISTIMG_4592		"ID_LISTIMG_4592"
#endif  ID_LISTIMG_4592
#ifndef ID_PICTURE_PlayerBase
#define ID_PICTURE_PlayerBase		"ID_PICTURE_PlayerBase"
#endif  ID_PICTURE_PlayerBase
#ifndef ID_PICTURE_PlayerBase1
#define ID_PICTURE_PlayerBase1		"ID_PICTURE_PlayerBase1"
#endif  ID_PICTURE_PlayerBase1
#ifndef ID_PICTURE_Up
#define ID_PICTURE_Up		"ID_PICTURE_Up"
#endif  ID_PICTURE_Up
#ifndef ID_PICTURE_Down
#define ID_PICTURE_Down		"ID_PICTURE_Down"
#endif  ID_PICTURE_Down
#ifndef ID_BUTTON_1148
#define ID_BUTTON_1148		"ID_BUTTON_1148"
#endif  ID_BUTTON_1148
#ifndef ID_TEXT_CountryMoney
#define ID_TEXT_CountryMoney		"ID_TEXT_CountryMoney"
#endif  ID_TEXT_CountryMoney
class CPlayer;
class CPlayerAnim;
class CUI_ID_FRAME_Gut : public CUIBase, public CUIRenderAnim
{
	// Member
public:
	 CUI_ID_FRAME_Gut();
private:	
	 ControlFrame*	m_pID_FRAME_Gut;
	 ControlText*	m_pID_TEXT_GoOn;
	 ControlPicture*	m_pID_PICTURE_Backdrop;
	 ControlText*	m_pID_TEXT_TextTitle;
	 ControlText*	m_pID_TEXT_NpcGut;
	 ControlButton*	m_pID_BUTTON_Continue;
	 ControlButton*	m_pID_BUTTON_OK;
	 ControlButton*	m_pID_BUTTON_Refuse;
	 ControlButton*	m_pID_BUTTON_Finish;
	 ControlButton*	m_pID_BUTTON_Accept;
	 ControlPicture*	m_pID_PICTURE_NPC;
	 ControlList*	m_pID_LIST_PlayerGut;
	 ControlText*	m_pID_TEXT_EXP;
	 ControlText*	m_pID_TEXT_Money;
	 ControlListImage*	m_pID_LISTIMG_4592;
	 ControlPicture*	m_pID_PICTURE_PlayerBase;
	 ControlPicture*	m_pID_PICTURE_PlayerBase1;
	 ControlPicture*	m_pID_PICTURE_Up;
	 ControlPicture*	m_pID_PICTURE_Down;
	 ControlButton*	m_pID_BUTTON_1148;
	 ControlText*	m_pID_TEXT_CountryMoney;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_ContinueOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_RefuseOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FinishOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_AcceptOnButtonClick( ControlObject* pSender );
	void ID_LIST_PlayerGutOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_LISTIMG_4592OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_4592OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_4592OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_4592OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_1148OnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:
	void SetNpc(int nNpcId);
	int  GetNpc(){return m_nNpcID;}
	void Show(int nType,const std::string& info,short nQuestId,const std::string& title);
	virtual bool IsHoldInMemory() const {return true;}
	virtual void InitializeAtEnterWorld();
	void  StartScript(int nNpcId);
	void  EndNpcScript();

	static bool MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );
private:
	int m_nModelId;
	int m_nNpcID;
public:
	bool LoadTalk(short sQuestId,int nType);
	bool ContinueTalk();
	void UpdateInfo(SQuestTalk *pTalk);
	void ShowControlByType();
	void ShowTaskAward();
	void UpdateQuestBg(int nNpcId);
	float GetNpcHeight();
	void SetNpcHeightModel(float fHeight,float fScale,float fViewHeight);
	void SetNpcGutText(const char* pszText);
	ControlFrame* GetFrame(){return m_pID_FRAME_Gut;}
public:
	virtual void ResetDevice();
private:
	void ResetControlSize();
	void ShowBgPic();
private:
	QuestTalks m_vTalks;
	int        m_nShowType;
	int        m_nQuestID;  //任务ID
	ControlGroup m_GroupAward;
	ControlGroup m_GroupMe;
	std::string  m_BgPic;

	float     m_fStature;
};
extern CUI_ID_FRAME_Gut s_CUI_ID_FRAME_Gut;
