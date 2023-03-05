/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\PetCompose.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "ItemEnableChangeSysBase.h"
#include "GlobalDef.h"
#ifndef ID_FRAME_PetCompose
#define ID_FRAME_PetCompose		"ID_FRAME_PetCompose"
#endif  ID_FRAME_PetCompose
#ifndef ID_LISTIMG_Material
#define ID_LISTIMG_Material		"ID_LISTIMG_Material"
#endif  ID_LISTIMG_Material
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_BUTTON_Canel
#define ID_BUTTON_Canel		"ID_BUTTON_Canel"
#endif  ID_BUTTON_Canel
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_TEXT_Material
#define ID_TEXT_Material		"ID_TEXT_Material"
#endif  ID_TEXT_Material
#ifndef ID_LIST_PetList
#define ID_LIST_PetList		"ID_LIST_PetList"
#endif  ID_LIST_PetList
#ifndef ID_BUTTON_PetMain
#define ID_BUTTON_PetMain		"ID_BUTTON_PetMain"
#endif  ID_BUTTON_PetMain
#ifndef ID_BUTTON_PetSecond
#define ID_BUTTON_PetSecond		"ID_BUTTON_PetSecond"
#endif  ID_BUTTON_PetSecond
#ifndef ID_TEXT_PetMain
#define ID_TEXT_PetMain		"ID_TEXT_PetMain"
#endif  ID_TEXT_PetMain
#ifndef ID_TEXT_PetSecond
#define ID_TEXT_PetSecond		"ID_TEXT_PetSecond"
#endif  ID_TEXT_PetSecond


#ifndef ID_LIST_Pic
#define ID_LIST_Pic		"ID_LIST_Pic"
#endif  ID_LIST_Pic


#ifndef ID_PICTURE_PetMain
#define ID_PICTURE_PetMain		"ID_PICTURE_PetMain"
#endif  ID_PICTURE_PetMain
#ifndef ID_PICTURE_PetSecond
#define ID_PICTURE_PetSecond		"ID_PICTURE_PetSecond"
#endif  ID_PICTURE_PetSecond
#ifndef ID_BUTTON_PetMainCanel
#define ID_BUTTON_PetMainCanel		"ID_BUTTON_PetMainCanel"
#endif  ID_BUTTON_PetMainCanel
#ifndef ID_BUTTON_PetSecondCanel
#define ID_BUTTON_PetSecondCanel		"ID_BUTTON_PetSecondCanel"
#endif  ID_BUTTON_PetSecondCanel


#ifndef ID_BUTTON_PetMainOpen
#define ID_BUTTON_PetMainOpen		"ID_BUTTON_PetMainOpen"
#endif  ID_BUTTON_PetMainOpen
#ifndef ID_BUTTON_PetSecondOpen
#define ID_BUTTON_PetSecondOpen		"ID_BUTTON_PetSecondOpen"
#endif  ID_BUTTON_PetSecondOpen

//#ifndef ID_TEXT_Money
//#define ID_TEXT_Money		"ID_TEXT_Money"
//#endif  ID_TEXT_Money

class CUI_ID_FRAME_PetCompose :public CUIBase , CItemEnableChangeSysBase
{
	// Member
public:	
	 CUI_ID_FRAME_PetCompose();
	 ControlFrame*	m_pID_FRAME_PetCompose;
	 ControlListImage*	m_pID_LISTIMG_Material;
	 ControlButton*	m_pID_BUTTON_OK;
	 ControlButton*	m_pID_BUTTON_Canel;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlText*	m_pID_TEXT_Material;
	 ControlList*	m_pID_LIST_PetList;
	 ControlButton*	m_pID_BUTTON_PetMain;
	 ControlButton*	m_pID_BUTTON_PetSecond;
	 ControlText*	m_pID_TEXT_PetMain;
	 ControlText*	m_pID_TEXT_PetSecond;
	 ControlList*   m_pID_LIST_Pic;

	 ControlPicture*	m_pID_PICTURE_PetMain;
	 ControlPicture*	m_pID_PICTURE_PetSecond;
	 ControlButton*	m_pID_BUTTON_PetMainCanel;
	 ControlButton*	m_pID_BUTTON_PetSecondCanel;

	 ControlButton*	m_pID_BUTTON_PetMainOpen;
	 ControlButton*	m_pID_BUTTON_PetSecondOpen;
	 
	 //ControlText*	m_pID_TEXT_Money;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CanelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	void ID_LIST_PetListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_PicOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_PetMainOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PetSecondOnButtonClick( ControlObject* pSender );

	bool ID_BUTTON_PetMainCanelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PetSecondCanelOnButtonClick( ControlObject* pSender );

	bool ID_BUTTON_PetMainOpenOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PetSecondOpenOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );// 设置是否可视
	virtual bool IsPackItemBeUsing( __int64 nGuid );
private:
	void OnInit();
	void SetEmpty();
	void SetPetToMain();
	void SetPetToSecond();
	void SetMaterial();
	void UpdateMaterial();
	void OnPetCompose();
	void UpdatePetPic();
	void SetPetPic(SPetItem* pPet,bool IsMain);
private:
	uint32		m_ItemID;
	uint32		m_ItemSum;
	__int64		m_MainGuID;
	__int64		m_SecGuID;
	uint32		m_BagItemSum;
	DWORD		m_StepLogTime;
	bool		m_IsEnterItem;
};
extern CUI_ID_FRAME_PetCompose s_CUI_ID_FRAME_PetCompose;