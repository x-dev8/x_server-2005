/********************************************************************
Created by UIEditor.exe
FileName: E:\Code\RunTime\CLIENT\Data\UI\Target.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "GameDefineChar.h"
#include "MsgBase.h"
#ifndef ID_FRAME_Target
#define ID_FRAME_Target		"ID_FRAME_Target"
#endif  ID_FRAME_Target
#ifndef ID_TEXT_Name
#define ID_TEXT_Name		"ID_TEXT_Name"
#endif  ID_TEXT_Name
#ifndef ID_PROGRESS_Hp
#define ID_PROGRESS_Hp		"ID_PROGRESS_Hp"
#endif  ID_PROGRESS_Hp
#ifndef ID_PROGRESS_HpTail
#define ID_PROGRESS_HpTail		"ID_PROGRESS_HpTail"
#endif  ID_PROGRESS_HpTail
#ifndef ID_LISTIMG_Status
#define ID_LISTIMG_Status		"ID_LISTIMG_Status"
#endif  ID_LISTIMG_Status
#ifndef ID_TEXT_Lvl
#define ID_TEXT_Lvl		"ID_TEXT_Lvl"
#endif  ID_TEXT_Lvl
#ifndef ID_TEXT_TargetName
#define ID_TEXT_TargetName	"ID_TEXT_TargetName"
#endif ID_TEXT_TargetName
#ifndef ID_PICTURE_MonsterType
#define ID_PICTURE_MonsterType		"ID_PICTURE_MonsterType"
#endif  ID_PICTURE_MonsterType
#ifndef ID_TEXT_percent
#define ID_TEXT_percent	"ID_TEXT_percent"
#endif ID_TEXT_percent
#ifndef ID_PICTURE_Hair
#define ID_PICTURE_Hair	"ID_PICTURE_Hair"
#endif ID_PICTURE_Hair
#ifndef ID_PICTURE_Face
#define ID_PICTURE_Face	"ID_PICTURE_Face"
#endif ID_PICTURE_Face
#ifndef ID_PROGRESS_Mp
#define ID_PROGRESS_Mp		"ID_PROGRESS_Mp"
#endif  ID_PROGRESS_Mp
#ifndef ID_PICTURE_Target
#define ID_PICTURE_Target		"ID_PICTURE_Target"
#endif  ID_PICTURE_Target
#ifndef ID_PICTURE_TargetHair
#define ID_PICTURE_TargetHair		"ID_PICTURE_TargetHair"
#endif  ID_PICTURE_TargetHair
#ifndef ID_PICTURE_TargetFace
#define ID_PICTURE_TargetFace		"ID_PICTURE_TargetFace"
#endif  ID_PICTURE_TargetFace
#ifndef ID_PROGRESS_TargetHp
#define ID_PROGRESS_TargetHp		"ID_PROGRESS_TargetHp"
#endif  ID_PROGRESS_TargetHp
#ifndef ID_TEXT_TargetName
#define ID_TEXT_TargetName		"ID_TEXT_TargetName"
#endif  ID_TEXT_TargetName
#ifndef ID_PICTURE_Choose
#define ID_PICTURE_Choose		"ID_PICTURE_Choose"
#endif  ID_PICTURE_Choose
#ifndef ID_TEXT_TargetLvl
#define ID_TEXT_TargetLvl		"ID_TEXT_TargetLvl"
#endif  ID_TEXT_TargetLvl
#ifndef ID_PICTURE_BgTargetFace
#define ID_PICTURE_BgTargetFace		"ID_PICTURE_BgTargetFace"
#endif  ID_PICTURE_BgTargetFace
#ifndef ID_PICTURE_Hunter
#define ID_PICTURE_Hunter		"ID_PICTURE_Hunter"
#endif  ID_PICTURE_Hunter
#ifndef ID_PICTURE_Taoist
#define ID_PICTURE_Taoist		"ID_PICTURE_Taoist"
#endif  ID_PICTURE_Taoist
#ifndef ID_PICTURE_Warrior
#define ID_PICTURE_Warrior		"ID_PICTURE_Warrior"
#endif  ID_PICTURE_Warrior
#ifndef ID_PICTURE_Mage
#define ID_PICTURE_Mage		"ID_PICTURE_Mage"
#endif  ID_PICTURE_Mage
#ifndef ID_PICTURE_Assassin
#define ID_PICTURE_Assassin		"ID_PICTURE_Assassin"
#endif  ID_PICTURE_Assassin
#ifndef ID_PICTURE_Ren
#define ID_PICTURE_Ren "ID_PICTURE_Ren"
#endif ID_PICTURE_Ren
#ifndef ID_PICTURE_Ji
#define ID_PICTURE_Ji "ID_PICTURE_Ji"
#endif ID_PICTURE_Ji
#ifndef ID_PICTURE_Shen
#define ID_PICTURE_Shen "ID_PICTURE_Shen"
#endif ID_PICTURE_Shen
#ifndef ID_PICTURE_Gui
#define ID_PICTURE_Gui "ID_PICTURE_Gui"
#endif ID_PICTURE_Gui
#ifndef ID_PICTURE_Xian
#define  ID_PICTURE_Xian "ID_PICTURE_Xian"
#endif ID_PICTURE_Xian
#ifndef ID_PICTURE_Yao
#define  ID_PICTURE_Yao "ID_PICTURE_Yao"
#endif ID_PICTURE_Yao
#ifndef ID_PICTURE_Shou
#define ID_PICTURE_Shou "ID_PICTURE_Shou"
#endif ID_PICTURE_Shou
#ifndef ID_PICTURE_Mo
#define  ID_PICTURE_Mo "ID_PICTURE_Mo"
#endif ID_PICTURE_Mo
#ifndef ID_TEXT_HP
#define ID_TEXT_HP "ID_TEXT_HP"
#endif	ID_TEXT_HP
#ifndef ID_TEXT_Hero
#define ID_TEXT_Hero		"ID_TEXT_Hero"
#endif  ID_TEXT_Hero

class CPlayer;
#include "UiBase.h"
class CUI_ID_FRAME_Target :public CUIBase 
{
	// SGuildMember
private:	
	void ResetMembers();
	ControlFrame*	    m_pID_FRAME_Target;
	ControlText*	    m_pID_TEXT_Name;
	ControlProgress*	m_pID_PROGRESS_Hp;
	ControlProgress*	m_pID_PROGRESS_HpTail;
	ControlListImage*	m_pID_LISTIMG_Status;
	//ControlPicture*	m_pID_PICTURE_MonsterType;

	ControlText*		m_pID_TEXT_Lvl;
	ControlText*		_pText_TargetName;
	ControlText*		_pText_Percent;	//hp百分比
	ControlText*		m_pID_TEXT_HP;	//显示的生命值

	ControlPicture* m_pID_PICTURE_Hair;
	ControlPicture*     m_pID_PICTURE_Face;
	//ControlProgress*	m_pID_PROGRESS_Mp;

	ControlPicture*	    m_pID_PICTURE_Target;
	ControlPicture*	m_pID_PICTURE_TargetHair;
	ControlPicture*     m_pID_PICTURE_TargetFace;
	ControlProgress*	m_pID_PROGRESS_TargetHp;

	ControlText*	    m_pID_TEXT_TargetName;
	ControlPicture*	    m_pID_PICTURE_Choose;

    ControlText*        m_pID_TEXT_TargetLvl;
    ControlPicture*     m_pID_PICTURE_BgTargetFace;
    ControlPicture*     m_pID_PICTURE_ProPic[EArmType_Sniper];
	ControlPicture*     m_pID_PICTURE_Group[EPhyle_MaxCount];
	ControlGroup	    m_ttGroup;


	ControlPicture     *m_pID_PICTURE_Ren;
	ControlPicture     *m_pID_PICTURE_Ji;
	ControlPicture     *m_pID_PICTURE_Shen;
	ControlPicture     *m_pID_PICTURE_Gui;
	ControlPicture     *m_pID_PICTURE_Xian;
	ControlPicture     *m_pID_PICTURE_Yao;
	ControlPicture     *m_pID_PICTURE_Shou;
	ControlPicture     *m_pID_PICTURE_Mo;

	ControlText*	m_pID_TEXT_Hero;

public:
	CUI_ID_FRAME_Target();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_LISTIMG_StatusOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_StatusOnIconDragOff( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_StatusOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

public:
    virtual bool IsHoldInMemory() const { return true; }
    virtual void InitializeAtEnterWorld();
	void SetPlayer( const GameObjectId nId );
	int GetSelId() {return m_nSelId;}
	INT	 GetPlayerID() { return m_nSelId; }	
	void SetFollowPlayerId(int id);
	void SetPlayerTarget(CPlayer* target);
	int  GetFollowPlayerId() { return m_nFollowPlayerId; }
	ControlGroup& Get_ttGroup() { return m_ttGroup; }

	void ForceUpdate(){m_bForceUpdate = true;}
	bool IsTargetUIUpDateIng ; //lyh++ 针对tryuseSkill 加的变量

	void UpdateBeLongID(uint32 ID);
	void TeamStatesChange();

	void SetHeroName(const char* text, DWORD color);
private:
	const char* GetName() { return m_pID_TEXT_Name->GetText(); }
	static bool ID_FRAME_Target_OnRBClick( ControlObject* pSender );
	static bool ID_FRAME_TargetTarget_OnClick( ControlObject* pSender );
	void	setTargetName( const char* szName = NULL );
    void    CreateProgressAni();

	void    SetUIPicStates(bool IsHeader,bool IsTarget);
private:
	int m_nSelId;
	int m_nPlayerLevel;
	int m_nFollowPlayerId;
	int nTargetTargetId;
	bool m_bForceUpdate;
};
extern CUI_ID_FRAME_Target s_CUI_ID_FRAME_Target;