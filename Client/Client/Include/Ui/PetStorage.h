/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\PetStorage.h
*********************************************************************/
#pragma once

#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "GlobalDef.h"
#include "me3d/Vector.h"

#ifndef ID_FRAME_PetStorage
#define ID_FRAME_PetStorage		"ID_FRAME_PetStorage"
#endif  ID_FRAME_PetStorage
#ifndef ID_BUTTON_Info
#define ID_BUTTON_Info		"ID_BUTTON_Info"
#endif  ID_BUTTON_Info
#ifndef ID_BUTTON_Get
#define ID_BUTTON_Get		"ID_BUTTON_Get"
#endif  ID_BUTTON_Get
#ifndef ID_TEXT_Space
#define ID_TEXT_Space		"ID_TEXT_Space"
#endif  ID_TEXT_Space
#ifndef ID_LISTIMG_PetIcon1
#define ID_LISTIMG_PetIcon1		"ID_LISTIMG_PetIcon1"
#endif  ID_LISTIMG_PetIcon1
#ifndef ID_LISTIMG_PetIcon2
#define ID_LISTIMG_PetIcon2		"ID_LISTIMG_PetIcon2"
#endif  ID_LISTIMG_PetIcon2
#ifndef ID_LISTIMG_PetIcon3
#define ID_LISTIMG_PetIcon3		"ID_LISTIMG_PetIcon3"
#endif  ID_LISTIMG_PetIcon3
#ifndef ID_LISTIMG_PetIcon4
#define ID_LISTIMG_PetIcon4		"ID_LISTIMG_PetIcon4"
#endif  ID_LISTIMG_PetIcon4
#ifndef ID_LISTIMG_PetIcon5
#define ID_LISTIMG_PetIcon5		"ID_LISTIMG_PetIcon5"
#endif  ID_LISTIMG_PetIcon5
#ifndef ID_LISTIMG_PetIcon6
#define ID_LISTIMG_PetIcon6		"ID_LISTIMG_PetIcon6"
#endif  ID_LISTIMG_PetIcon6
#ifndef ID_TEXT_PetName1
#define ID_TEXT_PetName1		"ID_TEXT_PetName1"
#endif  ID_TEXT_PetName1
#ifndef ID_TEXT_PetName2
#define ID_TEXT_PetName2		"ID_TEXT_PetName2"
#endif  ID_TEXT_PetName2
#ifndef ID_TEXT_PetName3
#define ID_TEXT_PetName3		"ID_TEXT_PetName3"
#endif  ID_TEXT_PetName3
#ifndef ID_TEXT_PetName4
#define ID_TEXT_PetName4		"ID_TEXT_PetName4"
#endif  ID_TEXT_PetName4
#ifndef ID_TEXT_PetName5
#define ID_TEXT_PetName5		"ID_TEXT_PetName5"
#endif  ID_TEXT_PetName5
#ifndef ID_TEXT_PetName6
#define ID_TEXT_PetName6		"ID_TEXT_PetName6"
#endif  ID_TEXT_PetName6
#ifndef ID_TEXT_PetLvl1
#define ID_TEXT_PetLvl1		"ID_TEXT_PetLvl1"
#endif  ID_TEXT_PetLvl1
#ifndef ID_TEXT_PetLvl2
#define ID_TEXT_PetLvl2		"ID_TEXT_PetLvl2"
#endif  ID_TEXT_PetLvl2
#ifndef ID_TEXT_PetLvl3
#define ID_TEXT_PetLvl3		"ID_TEXT_PetLvl3"
#endif  ID_TEXT_PetLvl3
#ifndef ID_TEXT_PetLvl4
#define ID_TEXT_PetLvl4		"ID_TEXT_PetLvl4"
#endif  ID_TEXT_PetLvl4
#ifndef ID_TEXT_PetLvl5
#define ID_TEXT_PetLvl5		"ID_TEXT_PetLvl5"
#endif  ID_TEXT_PetLvl5
#ifndef ID_TEXT_PetLvl6
#define ID_TEXT_PetLvl6		"ID_TEXT_PetLvl6"
#endif  ID_TEXT_PetLvl6
#ifndef ID_TEXT_Race1
#define ID_TEXT_Race1		"ID_TEXT_Race1"
#endif  ID_TEXT_Race1
#ifndef ID_TEXT_Race2
#define ID_TEXT_Race2		"ID_TEXT_Race2"
#endif  ID_TEXT_Race2
#ifndef ID_TEXT_Race3
#define ID_TEXT_Race3		"ID_TEXT_Race3"
#endif  ID_TEXT_Race3
#ifndef ID_TEXT_Race4
#define ID_TEXT_Race4		"ID_TEXT_Race4"
#endif  ID_TEXT_Race4
#ifndef ID_TEXT_Race5
#define ID_TEXT_Race5		"ID_TEXT_Race5"
#endif  ID_TEXT_Race5
#ifndef ID_TEXT_Race6
#define ID_TEXT_Race6		"ID_TEXT_Race6"
#endif  ID_TEXT_Race6
#ifndef ID_TEXT_Strength1
#define ID_TEXT_Strength1		"ID_TEXT_Strength1"
#endif  ID_TEXT_Strength1
#ifndef ID_TEXT_Strength2
#define ID_TEXT_Strength2		"ID_TEXT_Strength2"
#endif  ID_TEXT_Strength2
#ifndef ID_TEXT_Strength3
#define ID_TEXT_Strength3		"ID_TEXT_Strength3"
#endif  ID_TEXT_Strength3
#ifndef ID_TEXT_Strength4
#define ID_TEXT_Strength4		"ID_TEXT_Strength4"
#endif  ID_TEXT_Strength4
#ifndef ID_TEXT_Strength5
#define ID_TEXT_Strength5		"ID_TEXT_Strength5"
#endif  ID_TEXT_Strength5
#ifndef ID_TEXT_Strength6
#define ID_TEXT_Strength6		"ID_TEXT_Strength6"
#endif  ID_TEXT_Strength6
#ifndef ID_TEXT_Agility1
#define ID_TEXT_Agility1		"ID_TEXT_Agility1"
#endif  ID_TEXT_Agility1
#ifndef ID_TEXT_Agility2
#define ID_TEXT_Agility2		"ID_TEXT_Agility2"
#endif  ID_TEXT_Agility2
#ifndef ID_TEXT_Agility3
#define ID_TEXT_Agility3		"ID_TEXT_Agility3"
#endif  ID_TEXT_Agility3
#ifndef ID_TEXT_Agility4
#define ID_TEXT_Agility4		"ID_TEXT_Agility4"
#endif  ID_TEXT_Agility4
#ifndef ID_TEXT_Agility5
#define ID_TEXT_Agility5		"ID_TEXT_Agility5"
#endif  ID_TEXT_Agility5
#ifndef ID_TEXT_Agility6
#define ID_TEXT_Agility6		"ID_TEXT_Agility6"
#endif  ID_TEXT_Agility6
#ifndef ID_TEXT_Stamina1
#define ID_TEXT_Stamina1		"ID_TEXT_Stamina1"
#endif  ID_TEXT_Stamina1
#ifndef ID_TEXT_Stamina2
#define ID_TEXT_Stamina2		"ID_TEXT_Stamina2"
#endif  ID_TEXT_Stamina2
#ifndef ID_TEXT_Stamina3
#define ID_TEXT_Stamina3		"ID_TEXT_Stamina3"
#endif  ID_TEXT_Stamina3
#ifndef ID_TEXT_Stamina4
#define ID_TEXT_Stamina4		"ID_TEXT_Stamina4"
#endif  ID_TEXT_Stamina4
#ifndef ID_TEXT_Stamina5
#define ID_TEXT_Stamina5		"ID_TEXT_Stamina5"
#endif  ID_TEXT_Stamina5
#ifndef ID_TEXT_Stamina6
#define ID_TEXT_Stamina6		"ID_TEXT_Stamina6"
#endif  ID_TEXT_Stamina6
#ifndef ID_TEXT_Intellect1
#define ID_TEXT_Intellect1		"ID_TEXT_Intellect1"
#endif  ID_TEXT_Intellect1
#ifndef ID_TEXT_Intellect2
#define ID_TEXT_Intellect2		"ID_TEXT_Intellect2"
#endif  ID_TEXT_Intellect2
#ifndef ID_TEXT_Intellect3
#define ID_TEXT_Intellect3		"ID_TEXT_Intellect3"
#endif  ID_TEXT_Intellect3
#ifndef ID_TEXT_Intellect4
#define ID_TEXT_Intellect4		"ID_TEXT_Intellect4"
#endif  ID_TEXT_Intellect4
#ifndef ID_TEXT_Intellect5
#define ID_TEXT_Intellect5		"ID_TEXT_Intellect5"
#endif  ID_TEXT_Intellect5
#ifndef ID_TEXT_Intellect6
#define ID_TEXT_Intellect6		"ID_TEXT_Intellect6"
#endif  ID_TEXT_Intellect6
#ifndef ID_PICTURE_Empty1
#define ID_PICTURE_Empty1		"ID_PICTURE_Empty1"
#endif  ID_PICTURE_Empty1
#ifndef ID_PICTURE_Empty2
#define ID_PICTURE_Empty2		"ID_PICTURE_Empty2"
#endif  ID_PICTURE_Empty2
#ifndef ID_PICTURE_Empty3
#define ID_PICTURE_Empty3		"ID_PICTURE_Empty3"
#endif  ID_PICTURE_Empty3
#ifndef ID_PICTURE_Empty4
#define ID_PICTURE_Empty4		"ID_PICTURE_Empty4"
#endif  ID_PICTURE_Empty4
#ifndef ID_PICTURE_Empty5
#define ID_PICTURE_Empty5		"ID_PICTURE_Empty5"
#endif  ID_PICTURE_Empty5
#ifndef ID_PICTURE_Empty6
#define ID_PICTURE_Empty6		"ID_PICTURE_Empty6"
#endif  ID_PICTURE_Empty6
#ifndef ID_PICTURE_Lock1
#define ID_PICTURE_Lock1		"ID_PICTURE_Lock1"
#endif  ID_PICTURE_Lock1
#ifndef ID_PICTURE_Lock2
#define ID_PICTURE_Lock2		"ID_PICTURE_Lock2"
#endif  ID_PICTURE_Lock2
#ifndef ID_PICTURE_Lock3
#define ID_PICTURE_Lock3		"ID_PICTURE_Lock3"
#endif  ID_PICTURE_Lock3
#ifndef ID_PICTURE_Lock4
#define ID_PICTURE_Lock4		"ID_PICTURE_Lock4"
#endif  ID_PICTURE_Lock4
#ifndef ID_PICTURE_Lock5
#define ID_PICTURE_Lock5		"ID_PICTURE_Lock5"
#endif  ID_PICTURE_Lock5
#ifndef ID_PICTURE_Lock6
#define ID_PICTURE_Lock6		"ID_PICTURE_Lock6"
#endif  ID_PICTURE_Lock6
#ifndef ID_CHECKBOX_Space1
#define ID_CHECKBOX_Space1		"ID_CHECKBOX_Space1"
#endif  ID_CHECKBOX_Space1
#ifndef ID_CHECKBOX_Space2
#define ID_CHECKBOX_Space2		"ID_CHECKBOX_Space2"
#endif  ID_CHECKBOX_Space2
#ifndef ID_CHECKBOX_Space3
#define ID_CHECKBOX_Space3		"ID_CHECKBOX_Space3"
#endif  ID_CHECKBOX_Space3
#ifndef ID_CHECKBOX_Space4
#define ID_CHECKBOX_Space4		"ID_CHECKBOX_Space4"
#endif  ID_CHECKBOX_Space4
#ifndef ID_CHECKBOX_Space5
#define ID_CHECKBOX_Space5		"ID_CHECKBOX_Space5"
#endif  ID_CHECKBOX_Space5
#ifndef ID_CHECKBOX_Space6
#define ID_CHECKBOX_Space6		"ID_CHECKBOX_Space6"
#endif  ID_CHECKBOX_Space6

class CUI_ID_FRAME_PetStorage : public CUIBase
{
private:	
	 ControlFrame*	    m_pID_FRAME_PetStorage;
	 ControlButton*	    m_pID_BUTTON_Info;
	 ControlButton*	    m_pID_BUTTON_Get;
	 ControlText*	    m_pID_TEXT_Space;
	 ControlListImage*	m_pID_LISTIMG_PetIcon[STORAGE_MOUNTGRID_MAX];
	 ControlText*	    m_pID_TEXT_PetName[STORAGE_MOUNTGRID_MAX];
	 ControlText*	    m_pID_TEXT_PetLvl[STORAGE_MOUNTGRID_MAX];
	 ControlText*	    m_pID_TEXT_Race[STORAGE_MOUNTGRID_MAX];
	 ControlText*	    m_pID_TEXT_Strength[STORAGE_MOUNTGRID_MAX];
	 ControlText*	    m_pID_TEXT_Agility[STORAGE_MOUNTGRID_MAX];
	 ControlText*	    m_pID_TEXT_Stamina[STORAGE_MOUNTGRID_MAX];
	 ControlText*	    m_pID_TEXT_Intellect[STORAGE_MOUNTGRID_MAX];
	 ControlPicture*	m_pID_PICTURE_Empty[STORAGE_MOUNTGRID_MAX];
	 ControlPicture*	m_pID_PICTURE_Lock[STORAGE_MOUNTGRID_MAX];
	 ControlCheckBox*	m_pID_CHECKBOX_Space[STORAGE_MOUNTGRID_MAX];

     ControlGroup       m_groupPet[STORAGE_MOUNTGRID_MAX];

public:	
    CUI_ID_FRAME_PetStorage();
    bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_InfoOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_GetOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_Space1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Space2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Space3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Space4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Space5OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Space6OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

public:
	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视

    void ShowPetStorage( bool bShow );
    void Refresh();
    int  GetStorageEmptySlot();

	void SetVisiblePosition( const Vector& vPos ){ m_vVisiblePos = vPos; }
protected:
    static void OnVisibleChange( ControlObject* pUIObject ); 
    void ResetMembers();
    void ResetStorageSelect();
    bool SetCurrentSelectIndex( int nIndex );
    void SeekPetByIndex( int nIndex );
    void TakeOutMount();

private:
    int     m_nPetSelectIndex;                          // 当前坐骑仓库中选中的索引
    int     m_nMountNumInStorage;                       // 当前坐骑仓库中的坐骑数量
	Vector	m_vVisiblePos;			                    // 打开时的人物位置,用来自动关闭时使用

};

extern CUI_ID_FRAME_PetStorage s_CUI_ID_FRAME_PetStorage;
