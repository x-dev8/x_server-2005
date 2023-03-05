/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\Hero\Program\trunk\Client\Bin\Data\Ui\WorldMap.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_WorldMap
#define ID_FRAME_WorldMap		"ID_FRAME_WorldMap"
#endif  ID_FRAME_WorldMap
#ifndef ID_PICTURE_TitleDi
#define ID_PICTURE_TitleDi		"ID_PICTURE_TitleDi"
#endif  ID_PICTURE_TitleDi
#ifndef ID_PICTURE_WorldMap
#define ID_PICTURE_WorldMap		"ID_PICTURE_WorldMap"
#endif  ID_PICTURE_WorldMap
#ifndef ID_PICTURE_StoryMap
#define ID_PICTURE_StoryMap		"ID_PICTURE_StoryMap"
#endif  ID_PICTURE_StoryMap
#ifndef ID_PICTURE_BgCountryInfo
#define ID_PICTURE_BgCountryInfo		"ID_PICTURE_BgCountryInfo"
#endif  ID_PICTURE_BgCountryInfo
#ifndef ID_TEXT_TitleCountryMap
#define ID_TEXT_TitleCountryMap		"ID_TEXT_TitleCountryMap"
#endif  ID_TEXT_TitleCountryMap
#ifndef ID_BUTTON_AreaMap
#define ID_BUTTON_AreaMap		"ID_BUTTON_AreaMap"
#endif  ID_BUTTON_AreaMap
// #ifndef ID_BUTTON_Close
// #define ID_BUTTON_Close		"ID_BUTTON_Close"
// #endif  ID_BUTTON_Close
#ifndef ID_BUTTON_Help
#define ID_BUTTON_Help		"ID_BUTTON_Help"
#endif  ID_BUTTON_Help
#ifndef ID_PICTURE_FenGe
#define ID_PICTURE_FenGe		"ID_PICTURE_FenGe"
#endif  ID_PICTURE_FenGe
#ifndef ID_TEXT_CountryName
#define ID_TEXT_CountryName		"ID_TEXT_CountryName"
#endif  ID_TEXT_CountryName
#ifndef ID_TEXT_CountryDesc
#define ID_TEXT_CountryDesc		"ID_TEXT_CountryDesc"
#endif  ID_TEXT_CountryDesc
#ifndef ID_TEXT_TitleStoryMap
#define ID_TEXT_TitleStoryMap		"ID_TEXT_TitleStoryMap"
#endif  ID_TEXT_TitleStoryMap
#ifndef ID_BUTTON_WorldMap
#define ID_BUTTON_WorldMap		"ID_BUTTON_WorldMap"
#endif  ID_BUTTON_WorldMap
#ifndef ID_BUTTON_StoryMap
#define ID_BUTTON_StoryMap		"ID_BUTTON_StoryMap"
#endif  ID_BUTTON_StoryMap

#include "UiBase.h"
class CUI_ID_FRAME_WorldMap :public CUIBase
{
	// Member
private:
	void ResetMembers();
	 ControlFrame*	m_pID_FRAME_WorldMap;
	 //ControlPicture*	m_pID_PICTURE_TitleDi;
	 ControlPicture*	m_pID_PICTURE_WorldMap;
	 ControlPicture*	m_pID_PICTURE_StoryMap;
	 ControlPicture*	m_pID_PICTURE_BgCountryInfo;
	 //ControlPicture*	m_pID_PICTURE_BgSelect;
	 ControlButton*	m_pID_BUTTON_AreaMap;
	 ControlText*	m_pID_TEXT_TitleCountryMap;
// 	 ControlButton*	m_pID_BUTTON_Close;
	 //ControlButton*	m_pID_BUTTON_Help;
	 ControlPicture*	m_pID_PICTURE_FenGe;
	 ControlText*	m_pID_TEXT_CountryName;
	 ControlText*	m_pID_TEXT_CountryDesc;
	 ControlText*	m_pID_TEXT_TitleStoryMap;
	 ControlButton*	m_pID_BUTTON_WorldMap;
	 ControlButton*	m_pID_BUTTON_StoryMap;

public:	
	CUI_ID_FRAME_WorldMap();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_AreaMapOnButtonClick( ControlObject* pSender );
// 	bool ID_BUTTON_CloseOnButtonClick( ControlObject* pSender );
	//bool ID_BUTTON_HelpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_WorldMapOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_StoryMapOnButtonClick( ControlObject* pSender );

	void SetVisable( const bool bVisable ,bool isWorldMap = true);			
	void			SetPos(int x,int y);
	ControlFrame* GetFrame() const { return m_pID_FRAME_WorldMap; }

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable ,bool isWorldMap = true);			// 设置是否可视
public:


private:
	std::map<int,void*>				buttonMap;
	std::map<int,void*>				buttonStoryMap;
	void RefreshButtonStatus();
	bool							m_isWorldMap;
	bool RefreshMapMode();
};
extern CUI_ID_FRAME_WorldMap s_CUI_ID_FRAME_WorldMap;
