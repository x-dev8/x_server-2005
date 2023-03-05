/********************************************************************
	Created by UIEditor.exe
	FileName: D:\My Documents\桌面\新建文件夹 (2)\ShopRegiste.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "GlobalDef.h"

#ifndef ID_FRAME_ShopRegiste
#define ID_FRAME_ShopRegiste		"ID_FRAME_ShopRegiste"
#endif  ID_FRAME_ShopRegiste
#ifndef ID_PICTURE_Di
#define ID_PICTURE_Di		"ID_PICTURE_Di"
#endif  ID_PICTURE_Di
#ifndef ID_PICTURE_Di1
#define ID_PICTURE_Di1		"ID_PICTURE_Di1"
#endif  ID_PICTURE_Di1
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_help
#define ID_BUTTON_help		"ID_BUTTON_help"
#endif  ID_BUTTON_help
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
// #ifndef ID_TEXT_Title
// #define ID_TEXT_Title		"ID_TEXT_Title"
// #endif  ID_TEXT_Title
#ifndef ID_BUTTON_Clear
#define ID_BUTTON_Clear		"ID_BUTTON_Clear"
#endif  ID_BUTTON_Clear
#ifndef ID_LIST_Registe
#define ID_LIST_Registe		"ID_LIST_Registe"
#endif  ID_LIST_Registe

#include "UiBase.h"
class CUI_ID_FRAME_ShopRegiste :public CUIBase
{
	// Member
private:
	void ResetMembers();
	 ControlFrame*	m_pID_FRAME_ShopRegiste;
// 	 ControlPicture*	m_pID_PICTURE_Di;
// 	 ControlPicture*	m_pID_PICTURE_Di1;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 //ControlButton*	m_pID_BUTTON_help;
	 ControlButton*	m_pID_BUTTON_Cancel;
// 	 ControlText*	m_pID_TEXT_Title;
	 ControlButton*	m_pID_BUTTON_Clear;
	 ControlList*	m_pID_LIST_Registe;

public:	
	CUI_ID_FRAME_ShopRegiste();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	//bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ClearOnButtonClick( ControlObject* pSender );
	void ID_LIST_RegisteOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );


	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	// 每件卖出物品的结构
	struct ShopSellRecord
	{
		ShopSellRecord(){
			m_chCount = 0;
		}
		SCharItem m_stItem;
		uint8 m_chCount;
	};

	typedef std::vector< ShopSellRecord > ShopSellRecordContainer;
	typedef ShopSellRecordContainer::iterator ShopSellRecordIter;

	void ClearTradeInfo();
	void AddTradeInfo( const char* pszTradeInfo, DWORD dwMoney,char* itemData = NULL);
private:
	void AddSellRecord( const SCharItem& stItem, int nCount )
	{
		ShopSellRecord record;
		record.m_stItem = stItem;
		record.m_chCount = nCount;
		m_Records.push_back( record );
	}
	ShopSellRecordContainer m_Records;

};
extern CUI_ID_FRAME_ShopRegiste s_CUI_ID_FRAME_ShopRegiste;
