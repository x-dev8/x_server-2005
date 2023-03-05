/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\MoveCountry.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "ItemEnableChangeSysBase.h"
#ifndef ID_FRAME_changecountry
#define ID_FRAME_changecountry		"ID_FRAME_changecountry"
#endif  ID_FRAME_changecountry
#ifndef ID_CHECKBOX_countryA_A
#define ID_CHECKBOX_countryA_A		"ID_CHECKBOX_countryA_A"
#endif  ID_CHECKBOX_countryA_A
#ifndef ID_TEXT_countryAStrong
#define ID_TEXT_countryAStrong		"ID_TEXT_countryAStrong"
#endif  ID_TEXT_countryAStrong
#ifndef ID_TEXT_countryBStrong
#define ID_TEXT_countryBStrong		"ID_TEXT_countryBStrong"
#endif  ID_TEXT_countryBStrong
#ifndef ID_BUTTON_changecountry
#define ID_BUTTON_changecountry		"ID_BUTTON_changecountry"
#endif  ID_BUTTON_changecountry
#ifndef ID_BUTTON_canel
#define ID_BUTTON_canel		"ID_BUTTON_canel"
#endif  ID_BUTTON_canel
#ifndef ID_TEXT_itemname
#define ID_TEXT_itemname		"ID_TEXT_itemname"
#endif  ID_TEXT_itemname
#ifndef ID_LISTIMG_Material
#define ID_LISTIMG_Material		"ID_LISTIMG_Material"
#endif  ID_LISTIMG_Material
#ifndef ID_CHECKBOX_countryA_C
#define ID_CHECKBOX_countryA_C		"ID_CHECKBOX_countryA_C"
#endif  ID_CHECKBOX_countryA_C
#ifndef ID_CHECKBOX_countryA_B
#define ID_CHECKBOX_countryA_B		"ID_CHECKBOX_countryA_B"
#endif  ID_CHECKBOX_countryA_B
#ifndef ID_CHECKBOX_countryB_B
#define ID_CHECKBOX_countryB_B		"ID_CHECKBOX_countryB_B"
#endif  ID_CHECKBOX_countryB_B
#ifndef ID_CHECKBOX_countryB_C
#define ID_CHECKBOX_countryB_C		"ID_CHECKBOX_countryB_C"
#endif  ID_CHECKBOX_countryB_C
#ifndef ID_CHECKBOX_countryB_A
#define ID_CHECKBOX_countryB_A		"ID_CHECKBOX_countryB_A"
#endif  ID_CHECKBOX_countryB_A

class CUI_ID_FRAME_changecountry :public CUIBase, CItemEnableChangeSysBase
{
	// Member
public:	
	 CUI_ID_FRAME_changecountry();
	 ControlFrame*	m_pID_FRAME_changecountry;
	 ControlText*	m_pID_TEXT_countryAStrong;
	 ControlText*	m_pID_TEXT_countryBStrong;
	 ControlButton*	m_pID_BUTTON_changecountry;
	 ControlButton*	m_pID_BUTTON_canel;
	 ControlText*	m_pID_TEXT_itemname;
	 ControlListImage*	m_pID_LISTIMG_Material;
	 ControlCheckBox*	m_pID_CHECKBOX_countryA_A;
	 ControlCheckBox*	m_pID_CHECKBOX_countryA_C;
	 ControlCheckBox*	m_pID_CHECKBOX_countryA_B;
	 ControlCheckBox*	m_pID_CHECKBOX_countryB_B;
	 ControlCheckBox*	m_pID_CHECKBOX_countryB_C;
	 ControlCheckBox*	m_pID_CHECKBOX_countryB_A;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_CHECKBOX_countryA_AOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_changecountryOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_canelOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	void ID_CHECKBOX_countryA_COnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_countryA_BOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_countryB_BOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_countryB_COnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_countryB_AOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );// 设置是否可视
	virtual bool IsPackItemBeUsing( __int64 nGuid );

	static void OnVisibleChange( ControlObject* pUIObject );
private:
	void        SetCountry(uint8 CountryID);
	void		OnInit();
	void        OnCheckCountry(uint8 CountryID);
	void		OnUpdate();
	void		SetEmpty();
	bool		OnChangeCountry();
	void		SetChecked(ControlObject* pSender);
private:
	uint8		m_CountryID;//当前选择的国家ID
	uint32		m_BagItemSum;
	uint8		m_ACountryID;
	uint8		m_BCountryID;
	uint32		m_ItemID;
	uint32		m_ItemSum;
	DWORD		m_StepLogTime;
	bool		m_IsUse;
};
extern CUI_ID_FRAME_changecountry s_CUI_ID_FRAME_changecountry;
