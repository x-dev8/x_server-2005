/********************************************************************
	Created by UIEditor.exe
	FileName: F:\project\Turbo\Bin\Client\Data\Ui\SearchPrivateShop.h
*********************************************************************/

/*----------------------------------------------------------
desc	: 摊位查询系统的UI。
author	: zilong
version	: 1.0
date	: 2011-02-28
revision:
----------------------------------------------------------*/

#pragma once
#include "MeUi/MeUi.h"
#include "UiBase.h"
#include "StallDefine.h"

#ifndef ID_FRAME_QueryStall
#define ID_FRAME_QueryStall		"ID_FRAME_QueryStall"
#endif  ID_FRAME_QueryStall
#ifndef ID_BUTTON_Refurbish
#define ID_BUTTON_Refurbish		"ID_BUTTON_Refurbish"
#endif  ID_BUTTON_Refurbish
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_Pursue
#define ID_BUTTON_Pursue		"ID_BUTTON_Pursue"
#endif  ID_BUTTON_Pursue
#ifndef ID_LIST_FunctionLevel
#define ID_LIST_FunctionLevel		"ID_LIST_FunctionLevel"
#endif  ID_LIST_FunctionLevel
#ifndef ID_LIST_GunDong
#define ID_LIST_GunDong		"ID_LIST_GunDong"
#endif  ID_LIST_GunDong
#ifndef ID_LIST_NewFunction
#define ID_LIST_NewFunction		"ID_LIST_NewFunction"
#endif  ID_LIST_NewFunction
#ifndef ID_TEXT_ShopName
#define ID_TEXT_ShopName		"ID_TEXT_ShopName"
#endif  ID_TEXT_ShopName
#ifndef ID_TEXT_PlayerName
#define ID_TEXT_PlayerName		"ID_TEXT_PlayerName"
#endif  ID_TEXT_PlayerName
#ifndef ID_LIST_Player
#define ID_LIST_Player		"ID_LIST_Player"
#endif  ID_LIST_Player
#ifndef ID_LIST_Shop
#define ID_LIST_Shop		"ID_LIST_Shop"
#endif  ID_LIST_Shop
#ifndef ID_EDIT_Search
#define ID_EDIT_Search		"ID_EDIT_Search"
#endif  ID_EDIT_Search
#ifndef ID_BUTTON_Search
#define ID_BUTTON_Search		"ID_BUTTON_Search"
#endif  ID_BUTTON_Search
#ifndef ID_TEXT_Money
#define ID_TEXT_Money		"ID_TEXT_Money"
#endif  ID_TEXT_Money
#ifndef ID_COMBOBOX_SearchContent
#define ID_COMBOBOX_SearchContent		"ID_COMBOBOX_SearchContent"
#endif  ID_COMBOBOX_SearchContent

class CUI_ID_FRAME_QueryStall: public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_QueryStall();
	 ControlFrame*	m_pID_FRAME_QueryStall;
	 ControlButton*	m_pID_BUTTON_Refurbish;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlButton*	m_pID_BUTTON_Pursue;
	 ControlList*	m_pID_LIST_FunctionLevel;
	 ControlList*	m_pID_LIST_GunDong;
	 ControlList*	m_pID_LIST_NewFunction;
	 ControlText*	m_pID_TEXT_ShopName;
	 ControlText*	m_pID_TEXT_PlayerName;
	 ControlList*	m_pID_LIST_Player;
	 ControlList*	m_pID_LIST_Shop;
	 ControlEdit*	m_pID_EDIT_Search;
	 ControlButton*	m_pID_BUTTON_Search;
	 ControlText*	m_pID_TEXT_Money;
	 ControlComboBox*	m_pID_COMBOBOX_SearchContent;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_RefurbishOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PursueOnButtonClick( ControlObject* pSender );
	void ID_LIST_FunctionLevelOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_GunDongOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_NewFunctionOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_PlayerOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_ShopOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_EDIT_SearchOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_SearchOnButtonClick( ControlObject* pSender );
	void ID_COMBOBOX_SearchContentOnComboBoxChange( ControlObject* pSender, const char* szData );

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	        // 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

public:
	void AddStallInfo(StallDefine::SStallInfo *pInfos_, int count_);
	static void ID_LIST_Shop_OnLDBClick( ControlObject* pSender, ControlList::S_List* pItem );

	void SetVisiblePosition( const Vector& vPos ){ m_vVisiblePos = vPos; }

private:
	void Refresh();
	void OnTimeOut();
	bool IsTimeOut();

private:
	//bool m_bToSearch;	//true, 代表搜索；false, 代表获取所有摊位信息
	DWORD m_lastTime;	//上一次计时的时间。
	Vector m_vVisiblePos;			 // 界面打开时的人物位置,用来自动关闭时使用
};
extern CUI_ID_FRAME_QueryStall s_CUI_ID_FRAME_QueryStall;
