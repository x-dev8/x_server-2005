/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Document\保护设置\PkSet.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "GlobalDef.h"
#ifndef ID_FRAME_PkSet
#define ID_FRAME_PkSet		"ID_FRAME_PkSet"
#endif  ID_FRAME_PkSet
#ifndef ID_PICTURE_ImageWall
#define ID_PICTURE_ImageWall		"ID_PICTURE_ImageWall"
#endif  ID_PICTURE_ImageWall
#ifndef ID_TEXT_Sworn
#define ID_TEXT_Sworn		"ID_TEXT_Sworn"
#endif  ID_TEXT_Sworn
#ifndef ID_TEXT_Guild
#define ID_TEXT_Guild		"ID_TEXT_Guild"
#endif  ID_TEXT_Guild
#ifndef ID_TEXT_All
#define ID_TEXT_All		"ID_TEXT_All"
#endif  ID_TEXT_All
#ifndef ID_TEXT_League
#define ID_TEXT_League		"ID_TEXT_League"
#endif  ID_TEXT_League
#ifndef ID_CHECKBOX_Sworn
#define ID_CHECKBOX_Sworn		"ID_CHECKBOX_Sworn"
#endif  ID_CHECKBOX_Sworn
#ifndef ID_CHECKBOX_Guild
#define ID_CHECKBOX_Guild		"ID_CHECKBOX_Guild"
#endif  ID_CHECKBOX_Guild
#ifndef ID_CHECKBOX_League
#define ID_CHECKBOX_League		"ID_CHECKBOX_League"
#endif  ID_CHECKBOX_League
#ifndef ID_CHECKBOX_All
#define ID_CHECKBOX_All		"ID_CHECKBOX_All"
#endif  ID_CHECKBOX_All
#ifndef ID_PICTURE_30013
#define ID_PICTURE_30013		"ID_PICTURE_30013"
#endif  ID_PICTURE_30013
#ifndef ID_PICTURE_13560
#define ID_PICTURE_13560		"ID_PICTURE_13560"
#endif  ID_PICTURE_13560
#ifndef ID_PICTURE_25141
#define ID_PICTURE_25141		"ID_PICTURE_25141"
#endif  ID_PICTURE_25141
#ifndef ID_PICTURE_32481
#define ID_PICTURE_32481		"ID_PICTURE_32481"
#endif  ID_PICTURE_32481
#ifndef ID_TEXT_Lvl
#define ID_TEXT_Lvl		"ID_TEXT_Lvl"
#endif  ID_TEXT_Lvl
#ifndef ID_SCROLLBAREX_Lvl
#define ID_SCROLLBAREX_Lvl		"ID_SCROLLBAREX_Lvl"
#endif  ID_SCROLLBAREX_Lvl
#ifndef ID_CHECKBOX_Hp
#define ID_CHECKBOX_Hp		"ID_CHECKBOX_Hp"
#endif  ID_CHECKBOX_Hp
#ifndef ID_CHECKBOX_Mp
#define ID_CHECKBOX_Mp		"ID_CHECKBOX_Mp"
#endif  ID_CHECKBOX_Mp
#ifndef ID_CHECKBOX_Dander
#define ID_CHECKBOX_Dander		"ID_CHECKBOX_Dander"
#endif  ID_CHECKBOX_Dander
#ifndef ID_TEXT_Hp
#define ID_TEXT_Hp		"ID_TEXT_Hp"
#endif  ID_TEXT_Hp
#ifndef ID_TEXT_Mp
#define ID_TEXT_Mp		"ID_TEXT_Mp"
#endif  ID_TEXT_Mp
#ifndef ID_TEXT_Dander
#define ID_TEXT_Dander		"ID_TEXT_Dander"
#endif  ID_TEXT_Dander
#ifndef ID_CHECKBOX_Red
#define ID_CHECKBOX_Red		"ID_CHECKBOX_Red"
#endif  ID_CHECKBOX_Red
#ifndef ID_CHECKBOX_White
#define ID_CHECKBOX_White		"ID_CHECKBOX_White"
#endif  ID_CHECKBOX_White
#ifndef ID_CHECKBOX_Blue
#define ID_CHECKBOX_Blue		"ID_CHECKBOX_Blue"
#endif  ID_CHECKBOX_Blue
#ifndef ID_TEXT_Red
#define ID_TEXT_Red		"ID_TEXT_Red"
#endif  ID_TEXT_Red
#ifndef ID_TEXT_White
#define ID_TEXT_White		"ID_TEXT_White"
#endif  ID_TEXT_White
#ifndef ID_TEXT_Blue
#define ID_TEXT_Blue		"ID_TEXT_Blue"
#endif  ID_TEXT_Blue

class CUI_ID_FRAME_PkSet
{
	// Member
public:	
	 CUI_ID_FRAME_PkSet();
private:
	void ResetMembers();
	 ControlFrame*	m_pID_FRAME_PkSet;
	 ControlPicture*	m_pID_PICTURE_ImageWall;
	 ControlText*	m_pID_TEXT_Sworn;
	 ControlText*	m_pID_TEXT_Guild;
	 ControlText*	m_pID_TEXT_All;
	 ControlText*	m_pID_TEXT_League;
	 ControlCheckBox*	m_pID_CHECKBOX_Sworn;
	 ControlCheckBox*	m_pID_CHECKBOX_Guild;
	 ControlCheckBox*	m_pID_CHECKBOX_League;
	 ControlCheckBox*	m_pID_CHECKBOX_All;
	 ControlPicture*	m_pID_PICTURE_30013;
	 ControlPicture*	m_pID_PICTURE_13560;
	 ControlPicture*	m_pID_PICTURE_25141;
	 ControlPicture*	m_pID_PICTURE_32481;
	 ControlText*	m_pID_TEXT_Lvl;
	 ControlScrollBarEx*	m_pID_SCROLLBAREX_Lvl;
	 ControlCheckBox*	m_pID_CHECKBOX_Hp;
	 ControlCheckBox*	m_pID_CHECKBOX_Mp;
	 ControlCheckBox*	m_pID_CHECKBOX_Dander;
	 ControlText*	m_pID_TEXT_Hp;
	 ControlText*	m_pID_TEXT_Mp;
	 ControlText*	m_pID_TEXT_Dander;
	 ControlCheckBox*	m_pID_CHECKBOX_Red;
	 ControlCheckBox*	m_pID_CHECKBOX_White;
	 ControlCheckBox*	m_pID_CHECKBOX_Blue;
	 ControlText*	m_pID_TEXT_Red;
	 ControlText*	m_pID_TEXT_White;
	 ControlText*	m_pID_TEXT_Blue;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_CHECKBOX_SwornOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_GuildOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_LeagueOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_AllOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_SCROLLBAREX_LvlOnScrollBarExUpdatePos( ControlObject* pSender, int n );
	void ID_CHECKBOX_HpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_MpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_DanderOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_RedOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_WhiteOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_BlueOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

    bool OnOkButtonClick( ControlObject* pSender );
    bool OnCancelButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	void RefreshHpMpUI();
	bool SetFrameFather(ControlObject* pFather);

private:
	ControlCheckBox* pCheck[PKMode_MaxValue];
	void RefreshUI();
	void SendMessage();
	short	 m_nPkLevel;
	short	 stPkTrueLevel;
	short	 m_nPkOldLevel;
};
extern CUI_ID_FRAME_PkSet s_CUI_ID_FRAME_PkSet;
