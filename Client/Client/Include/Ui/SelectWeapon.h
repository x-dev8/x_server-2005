/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Hero\Program\trunk\Client\Bin\Data\Ui\SelectWeapon.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "Me3d/Model/MexAnimCtrl.h"

#ifndef ID_FRAME_SelectWeapon
#define ID_FRAME_SelectWeapon		"ID_FRAME_SelectWeapon"
#endif  ID_FRAME_SelectWeapon
#ifndef ID_PICTURE_JobWall
#define ID_PICTURE_JobWall		"ID_PICTURE_JobWall"
#endif  ID_PICTURE_JobWall
#ifndef ID_BUTTON_Back
#define ID_BUTTON_Back		"ID_BUTTON_Back"
#endif  ID_BUTTON_Back
#ifndef ID_CHECKBOX_Spear
#define ID_CHECKBOX_Spear		"ID_CHECKBOX_Spear"
#endif  ID_CHECKBOX_Spear
#ifndef ID_CHECKBOX_Sword
#define ID_CHECKBOX_Sword		"ID_CHECKBOX_Sword"
#endif  ID_CHECKBOX_Sword
#ifndef ID_CHECKBOX_Staff
#define ID_CHECKBOX_Staff		"ID_CHECKBOX_Staff"
#endif  ID_CHECKBOX_Staff
#ifndef ID_CHECKBOX_Bow
#define ID_CHECKBOX_Bow		"ID_CHECKBOX_Bow"
#endif  ID_CHECKBOX_Bow
#ifndef ID_CHECKBOX_Fan
#define ID_CHECKBOX_Fan		"ID_CHECKBOX_Fan"
#endif  ID_CHECKBOX_Fan

class CUI_ID_FRAME_SelectWeapon
{
	// Member
public:	
	 CUI_ID_FRAME_SelectWeapon();
private:
	 ControlFrame*	m_pID_FRAME_SelectWeapon;
	 ControlPicture*	m_pID_PICTURE_JobWall;
	 ControlButton*	m_pID_BUTTON_Back;
	 ControlCheckBox*	m_pID_CHECKBOX_Spear;
	 ControlCheckBox*	m_pID_CHECKBOX_Sword;
	 ControlCheckBox*	m_pID_CHECKBOX_Staff;
	 ControlCheckBox*	m_pID_CHECKBOX_Bow;
	 ControlCheckBox*	m_pID_CHECKBOX_Fan;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_BackOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_SpearOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_SwordOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_StaffOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_BowOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_FanOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

    bool GetStateToSelect();
    void SetStateToSelect(bool bState = false);
    bool GetStateToCreate();
    void SetStateToCreate(bool bState = false);
    static bool frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );

protected:
    MeCamera*       m_pCamera;
    bool			m_bToCreate;

    D3DXVECTOR3     m_vEye;
    D3DXVECTOR3     m_vLookat;
    MexAnimCtrl*    m_pCameraModel;
    bool            m_bIsTileLoaded;

    void LoadScene();
};
extern CUI_ID_FRAME_SelectWeapon s_CUI_ID_FRAME_SelectWeapon;
