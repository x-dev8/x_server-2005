/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Code\RunTime\CLIENT\Data\UI\Property.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#ifndef ID_FRAME_Property
#define ID_FRAME_Property		"ID_FRAME_Property"
#endif  ID_FRAME_Property
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_TEXT_Hp
#define ID_TEXT_Hp		"ID_TEXT_Hp"
#endif  ID_TEXT_Hp
#ifndef ID_TEXT_Mp
#define ID_TEXT_Mp		"ID_TEXT_Mp"
#endif  ID_TEXT_Mp
#ifndef ID_TEXT_Str
#define ID_TEXT_Str		"ID_TEXT_Str"
#endif  ID_TEXT_Str
#ifndef ID_TEXT_Def
#define ID_TEXT_Def		"ID_TEXT_Def"
#endif  ID_TEXT_Def
#ifndef ID_TEXT_LHandAtt
#define ID_TEXT_LHandAtt		"ID_TEXT_LHandAtt"
#endif  ID_TEXT_LHandAtt
#ifndef ID_TEXT_Hit
#define ID_TEXT_Hit		"ID_TEXT_Hit"
#endif  ID_TEXT_Hit
#ifndef ID_TEXT_Frost
#define ID_TEXT_Frost		"ID_TEXT_Frost"
#endif  ID_TEXT_Frost
#ifndef ID_TEXT_Blaze
#define ID_TEXT_Blaze		"ID_TEXT_Blaze"
#endif  ID_TEXT_Blaze
#ifndef ID_TEXT_Thunder
#define ID_TEXT_Thunder		"ID_TEXT_Thunder"
#endif  ID_TEXT_Thunder
#ifndef ID_TEXT_Poison
#define ID_TEXT_Poison		"ID_TEXT_Poison"
#endif  ID_TEXT_Poison
#ifndef ID_BUTTON_Actiion
#define ID_BUTTON_Actiion		"ID_BUTTON_Actiion"
#endif  ID_BUTTON_Actiion
#ifndef ID_BUTTON_Base
#define ID_BUTTON_Base		"ID_BUTTON_Base"
#endif  ID_BUTTON_Base
#ifndef ID_TEXT_FrostAtt
#define ID_TEXT_FrostAtt		"ID_TEXT_FrostAtt"
#endif  ID_TEXT_FrostAtt
#ifndef ID_TEXT_BlazeAtt
#define ID_TEXT_BlazeAtt		"ID_TEXT_BlazeAtt"
#endif  ID_TEXT_BlazeAtt
#ifndef ID_TEXT_ThunderAtt
#define ID_TEXT_ThunderAtt		"ID_TEXT_ThunderAtt"
#endif  ID_TEXT_ThunderAtt
#ifndef ID_TEXT_PoisonAtt
#define ID_TEXT_PoisonAtt		"ID_TEXT_PoisonAtt"
#endif  ID_TEXT_PoisonAtt
#ifndef ID_TEXT_MpAtk
#define ID_TEXT_MpAtk		"ID_TEXT_MpAtk"
#endif ID_TEXT_MpAtk

#include "UiBase.h"
class CUI_ID_FRAME_Property :public CUIBase 
{
	// SGuildMember
public:	
	CUI_ID_FRAME_Property();
private:
	void ResetMembers();
	 ControlFrame*	m_pID_FRAME_Property;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlText*	m_pID_TEXT_Hp;
	 ControlText*	m_pID_TEXT_Mp;
	 ControlText*	m_pID_TEXT_Str;
	 ControlText*	m_pID_TEXT_Def;
	 ControlText*	m_pID_TEXT_LHandAtt;
	 ControlText*	m_pID_TEXT_Hit;

	 ControlText*	m_pID_TEXT_Frost;
	 ControlText*	m_pID_TEXT_Blaze;
	 ControlText*	m_pID_TEXT_Thunder;
	 ControlText*	m_pID_TEXT_Poison;
	 ControlButton*	m_pID_BUTTON_Actiion;
	 ControlButton*	m_pID_BUTTON_Base;
	 ControlText*	m_pID_TEXT_FrostAtt;
	 ControlText*	m_pID_TEXT_BlazeAtt;
	 ControlText*	m_pID_TEXT_ThunderAtt;
	 ControlText*	m_pID_TEXT_PoisonAtt;
	 ControlText*	m_pID_TEXT_MpAtk;		//魔法攻击
	 bool			m_bIsMySafe;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );

	bool ID_BUTTON_ActiionOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_BaseOnButtonClick( ControlObject* pSender );
	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );
public:


private:
	void Refeash();				// Refeash
};
extern CUI_ID_FRAME_Property s_CUI_ID_FRAME_Property;