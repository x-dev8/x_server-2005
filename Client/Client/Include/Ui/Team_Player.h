/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\Hero\Program\trunk\Client\Bin\Data\Ui\Team_Player.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "Group_Me.h"

#ifndef ID_FRAME_Team_Player
#define ID_FRAME_Team_Player		"ID_FRAME_Team_Player"
#endif  ID_FRAME_Team_Player
#ifndef ID_LISTIMG_Status
#define ID_LISTIMG_Status		"ID_LISTIMG_Status"
#endif  ID_LISTIMG_Status
#ifndef ID_BUTTON_kick
#define ID_BUTTON_kick		"ID_BUTTON_kick"
#endif  ID_BUTTON_kick
#ifndef ID_PROGRESS_Hp
#define ID_PROGRESS_Hp		"ID_PROGRESS_Hp"
#endif  ID_PROGRESS_Hp
#ifndef ID_PROGRESS_Mp
#define ID_PROGRESS_Mp		"ID_PROGRESS_Mp"
#endif  ID_PROGRESS_Mp
#ifndef ID_TEXT_Name
#define ID_TEXT_Name		"ID_TEXT_Name"
#endif  ID_TEXT_Name
#ifndef ID_TEXT_LVL
#define ID_TEXT_LVL		"ID_TEXT_LVL"
#endif  ID_TEXT_LVL
#ifndef ID_PICTURE_talktipPic
#define ID_PICTURE_talktipPic		"ID_PICTURE_talktipPic"
#endif  ID_PICTURE_talktipPic
#ifndef ID_TEXT_talktip
#define ID_TEXT_talktip		"ID_TEXT_talktip"
#endif  ID_TEXT_talktip
#ifndef ID_PICTURE_chang_assignmodePic
#define ID_PICTURE_chang_assignmodePic		"ID_PICTURE_chang_assignmodePic"
#endif  ID_PICTURE_chang_assignmodePic
#ifndef ID_TEXT_chang_assignmode
#define ID_TEXT_chang_assignmode		"ID_TEXT_chang_assignmode"
#endif  ID_TEXT_chang_assignmode
#ifndef ID_BUTTON_agree
#define ID_BUTTON_agree		"ID_BUTTON_agree"
#endif  ID_BUTTON_agree
#ifndef ID_PICTURE_Corps
#define ID_PICTURE_Corps		"ID_PICTURE_Corps"
#endif  ID_PICTURE_Corps
#ifndef ID_PICTURE_Header2
#define ID_PICTURE_Header2		"ID_PICTURE_Header2"
#endif  ID_PICTURE_Header2
#ifndef ID_PICTURE_Face
#define ID_PICTURE_Face		"ID_PICTURE_Face"
#endif  ID_PICTURE_Face
#ifndef ID_PICTURE_choise1
#define ID_PICTURE_choise1		"ID_PICTURE_choise1"
#endif  ID_PICTURE_choise1
#ifndef ID_PICTURE_Pt1
#define ID_PICTURE_Pt1		"ID_PICTURE_Pt1"
#endif  ID_PICTURE_Pt1
#ifndef ID_PROGRESS_Pt1
#define ID_PROGRESS_Pt1		"ID_PROGRESS_Pt1"
#endif  ID_PROGRESS_Pt1
#ifndef ID_PICTURE_choise1pt
#define ID_PICTURE_choise1pt		"ID_PICTURE_choise1pt"
#endif  ID_PICTURE_choise1pt
#ifndef ID_PICTURE_sword
#define ID_PICTURE_sword		"ID_PICTURE_sword"
#endif  ID_PICTURE_sword
#ifndef ID_PICTURE_staff
#define ID_PICTURE_staff		"ID_PICTURE_staff"
#endif  ID_PICTURE_staff
#ifndef ID_PICTURE_spear
#define ID_PICTURE_spear		"ID_PICTURE_spear"
#endif  ID_PICTURE_spear
#ifndef ID_PICTURE_Fan
#define ID_PICTURE_Fan		"ID_PICTURE_Fan"
#endif  ID_PICTURE_Fan
#ifndef ID_PICTURE_Bow
#define ID_PICTURE_Bow		"ID_PICTURE_Bow"
#endif  ID_PICTURE_Bow
#ifndef ID_BUTTON_refuse
#define ID_BUTTON_refuse		"ID_BUTTON_refuse"
#endif  ID_BUTTON_refuse
#ifndef ID_TEXT_ShowHp
#define ID_TEXT_ShowHp		"ID_TEXT_ShowHp"
#endif  ID_TEXT_ShowHp
#ifndef ID_PICTURE_Tip
#define ID_PICTURE_Tip		"ID_PICTURE_Tip"
#endif  ID_PICTURE_Tip
#ifndef ID_TEXT_ShowMp
#define ID_TEXT_ShowMp		"ID_TEXT_ShowMp"
#endif  ID_TEXT_ShowMp
#ifndef ID_PICTURE_Hair
#define ID_PICTURE_Hair		"ID_PICTURE_Hair"
#endif  ID_PICTURE_Hair

#include "UiBase.h"
class CUI_ID_FRAME_Team_Player  :public CUINotManagedByUIMgr
{
	// Member
private:
	void ResetMembers();
	 ControlFrame*	m_pID_FRAME_Team_Player;
	 ControlListImage*	m_pID_LISTIMG_Status;
	 ControlButton*	m_pID_BUTTON_kick;
	 ControlProgress*	m_pID_PROGRESS_Hp;
	 ControlProgress*	m_pID_PROGRESS_Mp;
	 ControlText*	m_pID_TEXT_Name;
	 ControlText*	m_pID_TEXT_LVL;
	 ControlPicture*	m_pID_PICTURE_talktipPic;
	 ControlText*	m_pID_TEXT_talktip;
	 ControlPicture*	m_pID_PICTURE_chang_assignmodePic;
	 ControlText*	m_pID_TEXT_chang_assignmode;
	 ControlButton*	m_pID_BUTTON_agree;
	 ControlPicture*	m_pID_PICTURE_Corps;
	 ControlPicture*	m_pID_PICTURE_Header2;
	 ControlPicture*	m_pID_PICTURE_Face;
	 ControlPicture*	m_pID_PICTURE_choise1;
	 ControlPicture*	m_pID_PICTURE_Pt1;
	 ControlProgress*	m_pID_PROGRESS_Pt1;
	 ControlPicture*	m_pID_PICTURE_choise1pt;
	 ControlPicture*	m_pID_PICTURE_sword;
	 ControlPicture*	m_pID_PICTURE_staff;
	 ControlPicture*	m_pID_PICTURE_spear;
	 ControlPicture*	m_pID_PICTURE_Fan;
	 ControlPicture*	m_pID_PICTURE_Bow;
	 ControlButton*	m_pID_BUTTON_refuse;
	 ControlText*	m_pID_TEXT_ShowHp;
	 ControlPicture*	m_pID_PICTURE_Tip;
	 ControlText*	m_pID_TEXT_ShowMp;
	 ControlPicture*	m_pID_PICTURE_Hair;

public:	
	CUI_ID_FRAME_Team_Player(int frameIndex);
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_LISTIMG_StatusOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_StatusOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_StatusOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_StatusOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_kickOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_agreeOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_refuseOnButtonClick( ControlObject* pSender );

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

public:
	ControlFrame* GetFrame() { return m_pID_FRAME_Team_Player; }
	ControlPicture* GetPICTURE_choise1();
	ControlPicture* GetPICTURE_choise1pt();
	ControlPicture* GetPICTURE_Header2();
	ControlProgress* GetPROGRESS_Hp();
	ControlProgress* GetPROGRESS_Mp();
	ControlText* GetTEXT_ShowHp();
	ControlText* GetTEXT_ShowMp();
	ControlText* GetTEXT_Name();
	ControlText* GetTEXT_LVL();
	ControlListImage* GetLISTIMG_Status();
	ControlProgress* GetPROGRESS_Pt1();

	ControlText* GetTEXT_talktip();
	ControlPicture* GetPICTURE_talktipPic();

	int GetID() { return _nID; }
	static int			GetTeamPlayerIdFromDBId(DWORD dwDBId);
	void updata();
	void setAssignMode_willChange( unsigned char mode);
	void showChange_assignModeUI( bool bShow );
	void show_talktip(const char* talk);

	bool Refreah();
	void setInfo(int nID, int nSex);
	void SetPicHeader( bool bHeader);
	void showProfessionIcon(int profession);
	void SetVisablePetUI(bool v);
	static bool OnSelectLookPlayer( ControlObject* pSender );

private:
	static bool OnButtonClickHead( ControlObject* pSender );
	static bool OnSelectLockPet(ControlObject* pSender);
	bool OnAgree_ChangeAssignMode( ControlObject* pSender );
	bool OnRefuse_ChangeAssignMode( ControlObject* pSender );
    void CreateProgressAni();

private:
    int				_nID;		//玩家id
	int				_nPetID;	// pet id

	clock_t			tmStartShow;

	int m_FrameIndex;

	ControlFrame*			m_pObject;
	char	szFrameID[64];
	S_TextTipInfo m_TipInfo;

};

class TeamPlayerFrameMgr 
{
public:
	TeamPlayerFrameMgr();
	~TeamPlayerFrameMgr();
	void					Reset();
	void					SetVisable( const bool bVisable );			// 设置是否可视
	void					HidePicChoise();
	void					HidePicChoisept();
	void					updata();
	CUI_ID_FRAME_Team_Player*					CreateFrame(int index);
public:
	bool OnFrameRunIndexedFrame(int index);
	bool OnFrameRenderIndexedFrame(int index);
	bool ID_LISTIMG_StatusOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_StatusOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_StatusOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_StatusOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_kickOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_agreeOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_refuseOnButtonClick( ControlObject* pSender );
	CUI_ID_FRAME_Team_Player*				GetActiveTeamFrame();
	CUI_ID_FRAME_Team_Player*				GetTeamFrameByIndex(int index);
	CUI_ID_FRAME_Team_Player*				GetTeamFrameById(int id);
	CUI_ID_FRAME_Team_Player*				GetTeamFrameByDBId(int id);
	CUI_ID_FRAME_Team_Player*				GetTeamFrameByChildWidget(ControlObject* pSender);
	int  GetFrameIndexByChildWidget(ControlObject* pSender);

private: 
	std::vector<CUI_ID_FRAME_Team_Player*>			mTeamFrameArr;

	int	m_ActiveIndex;

};

extern TeamPlayerFrameMgr TeamPlayerFrameManage;
