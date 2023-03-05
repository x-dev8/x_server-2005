/********************************************************************
	Created by UIEditor.exe
	FileName: D:\My Documents\桌面\ui\Create.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "GlobalDef.h"
#include "PlayerEquip.h"
#include "EquipEnum.h"
#include "AvatarSystemSetting.h"
#include "Me3d/Model/MexAnimCtrl.h"
#include "Cfg.h"

#ifndef ID_FRAME_CREATE
#define ID_FRAME_CREATE		"ID_FRAME_CREATE"
#endif  ID_FRAME_CREATE
#ifndef ID_PICTURE_Property
#define ID_PICTURE_Property		"ID_PICTURE_Property"
#endif  ID_PICTURE_Property
#ifndef ID_PICTURE_Title
#define ID_PICTURE_Title		"ID_PICTURE_Title"
#endif  ID_PICTURE_Title
#ifndef ID_PICTURE_JobWall
#define ID_PICTURE_JobWall		"ID_PICTURE_JobWall"
#endif  ID_PICTURE_JobWall
#ifndef ID_EDIT_Name
#define ID_EDIT_Name		"ID_EDIT_Name"
#endif  ID_EDIT_Name
#ifndef ID_BUTTON_CheckName
#define ID_BUTTON_CheckName		"ID_BUTTON_CheckName"
#endif  ID_BUTTON_CheckName
#ifndef ID_PICTURE_HairWall
#define ID_PICTURE_HairWall		"ID_PICTURE_HairWall"
#endif  ID_PICTURE_HairWall
#ifndef ID_PICTURE_FaceWall
#define ID_PICTURE_FaceWall		"ID_PICTURE_FaceWall"
#endif  ID_PICTURE_FaceWall
#ifndef ID_BUTTON_HairL
#define ID_BUTTON_HairL		"ID_BUTTON_HairL"
#endif  ID_BUTTON_HairL
#ifndef ID_BUTTON_HairR
#define ID_BUTTON_HairR		"ID_BUTTON_HairR"
#endif  ID_BUTTON_HairR
#ifndef ID_BUTTON_HeadL
#define ID_BUTTON_HeadL		"ID_BUTTON_HeadL"
#endif  ID_BUTTON_HeadL
#ifndef ID_BUTTON_HeadR
#define ID_BUTTON_HeadR		"ID_BUTTON_HeadR"
#endif  ID_BUTTON_HeadR
#ifndef ID_PICTURE_TitlePic
#define ID_PICTURE_TitlePic		"ID_PICTURE_TitlePic"
#endif  ID_PICTURE_TitlePic
#ifndef ID_PICTURE_FenGe
#define ID_PICTURE_FenGe		"ID_PICTURE_FenGe"
#endif  ID_PICTURE_FenGe
#ifndef ID_BUTTON_TurnR
#define ID_BUTTON_TurnR		"ID_BUTTON_TurnR"
#endif  ID_BUTTON_TurnR
#ifndef ID_BUTTON_TurnL
#define ID_BUTTON_TurnL		"ID_BUTTON_TurnL"
#endif  ID_BUTTON_TurnL
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_BUTTON_Back
#define ID_BUTTON_Back		"ID_BUTTON_Back"
#endif  ID_BUTTON_Back
#ifndef ID_TEXT_Name
#define ID_TEXT_Name		"ID_TEXT_Name"
#endif  ID_TEXT_Name
#ifndef ID_TEXT_Hair
#define ID_TEXT_Hair		"ID_TEXT_Hair"
#endif  ID_TEXT_Hair
#ifndef ID_TEXT_Face
#define ID_TEXT_Face		"ID_TEXT_Face"
#endif  ID_TEXT_Face
#ifndef ID_TEXT_ProName
#define ID_TEXT_ProName		"ID_TEXT_ProName"
#endif  ID_TEXT_ProName
#ifndef ID_TEXT_ProInfo
#define ID_TEXT_ProInfo		"ID_TEXT_ProInfo"
#endif  ID_TEXT_ProInfo
#ifndef ID_PICTURE_Spear
#define ID_PICTURE_Spear		"ID_PICTURE_Spear"
#endif  ID_PICTURE_Spear
#ifndef ID_PICTURE_Sword
#define ID_PICTURE_Sword		"ID_PICTURE_Sword"
#endif  ID_PICTURE_Sword
#ifndef ID_PICTURE_Staff
#define ID_PICTURE_Staff		"ID_PICTURE_Staff"
#endif  ID_PICTURE_Staff
#ifndef ID_PICTURE_Fan
#define ID_PICTURE_Fan		"ID_PICTURE_Fan"
#endif  ID_PICTURE_Fan
#ifndef ID_PICTURE_Bow
#define ID_PICTURE_Bow		"ID_PICTURE_Bow"
#endif  ID_PICTURE_Bow
#ifndef ID_CHECKBOX_JobOther
#define ID_CHECKBOX_JobOther		"ID_CHECKBOX_JobOther"
#endif  ID_CHECKBOX_JobOther
#ifndef ID_TEXT_Sex
#define ID_TEXT_Sex		"ID_TEXT_Sex"
#endif  ID_TEXT_Sex
#ifndef ID_TEXT_Man
#define ID_TEXT_Man		"ID_TEXT_Man"
#endif  ID_TEXT_Man
#ifndef ID_TEXT_Woman
#define ID_TEXT_Woman		"ID_TEXT_Woman"
#endif  ID_TEXT_Woman
#ifndef ID_CHECKBOX_Man
#define ID_CHECKBOX_Man		"ID_CHECKBOX_Man"
#endif  ID_CHECKBOX_Man
#ifndef ID_CHECKBOX_Woman
#define ID_CHECKBOX_Woman		"ID_CHECKBOX_Woman"
#endif  ID_CHECKBOX_Woman
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
#ifndef ID_TEXT_HairZ
#define ID_TEXT_HairZ		"ID_TEXT_HairZ"
#endif  ID_TEXT_HairZ
#ifndef ID_TEXT_FaceZ
#define ID_TEXT_FaceZ		"ID_TEXT_FaceZ"
#endif  ID_TEXT_FaceZ
#ifndef ID_BUTTON_Random
#define ID_BUTTON_Random		"ID_BUTTON_Random"
#endif  ID_BUTTON_Random

#ifndef ID_BUTTON_Reset
#define ID_BUTTON_Reset		"ID_BUTTON_Reset"
#endif  ID_BUTTON_Reset



//	国家 added by zhuomeng.hu		[8/18/2010]
#ifndef ID_CHECKBOX_Country1
#define ID_CHECKBOX_Country1		"ID_CHECKBOX_Country1"
#endif  ID_CHECKBOX_Country1
#ifndef ID_CHECKBOX_Country2
#define ID_CHECKBOX_Country2		"ID_CHECKBOX_Country2"
#endif  ID_CHECKBOX_Country2
#ifndef ID_CHECKBOX_Country3
#define ID_CHECKBOX_Country3		"ID_CHECKBOX_Country3"
#endif  ID_CHECKBOX_Country3
#ifndef ID_CHECKBOX_Country4
#define ID_CHECKBOX_Country4		"ID_CHECKBOX_Country4"
#endif  ID_CHECKBOX_Country4
#ifndef ID_TEXT_CountryDesc
#define ID_TEXT_CountryDesc		"ID_TEXT_CountryDesc"
#endif  ID_TEXT_CountryDesc
#ifndef ID_PICTURE_CountryIcon1
#define ID_PICTURE_CountryIcon1		"ID_PICTURE_CountryIcon1"
#endif  ID_PICTURE_CountryIcon1
#ifndef ID_PICTURE_CountryIcon2
#define ID_PICTURE_CountryIcon2		"ID_PICTURE_CountryIcon2"
#endif  ID_PICTURE_CountryIcon2
#ifndef ID_PICTURE_CountryIcon3
#define ID_PICTURE_CountryIcon3		"ID_PICTURE_CountryIcon3"
#endif  ID_PICTURE_CountryIcon3
#ifndef ID_PICTURE_CountryIcon4
#define ID_PICTURE_CountryIcon4		"ID_PICTURE_CountryIcon4"
#endif  ID_PICTURE_CountryIcon4
#ifndef ID_PICTURE_CountryIconRandom
#define ID_PICTURE_CountryIconRandom		"ID_PICTURE_CountryIconRandom"
#endif  ID_PICTURE_CountryIconRandom
#ifndef ID_TEXT_CountryName
#define ID_TEXT_CountryName		"ID_TEXT_CountryName"
#endif  ID_TEXT_CountryName
#ifndef ID_CHECKBOX_CountryAuto
#define ID_CHECKBOX_CountryAuto		"ID_CHECKBOX_CountryAuto"
#endif  ID_CHECKBOX_CountryAuto
#ifndef ID_TEXT_CountryAutoText
#define ID_TEXT_CountryAutoText		"ID_TEXT_CountryAutoText"
#endif  ID_TEXT_CountryAutoText
#ifndef ID_TEXT_CountryAutoDesc
#define ID_TEXT_CountryAutoDesc		"ID_TEXT_CountryAutoDesc"
#endif  ID_TEXT_CountryAutoDesc
#ifndef ID_CHECKBOX_Portrait1
#define ID_CHECKBOX_Portrait1		"ID_CHECKBOX_Portrait1"
#endif  ID_CHECKBOX_Portrait1
#ifndef ID_CHECKBOX_Portrait2
#define ID_CHECKBOX_Portrait2		"ID_CHECKBOX_Portrait2"
#endif  ID_CHECKBOX_Portrait2
#ifndef ID_CHECKBOX_Portrait3
#define ID_CHECKBOX_Portrait3		"ID_CHECKBOX_Portrait3"
#endif  ID_CHECKBOX_Portrait3
#ifndef ID_CHECKBOX_Portrait4
#define ID_CHECKBOX_Portrait4		"ID_CHECKBOX_Portrait4"
#endif  ID_CHECKBOX_Portrait4
#ifndef ID_BUTTON_HeadUp
#define ID_BUTTON_HeadUp		"ID_BUTTON_HeadUp"
#endif  ID_BUTTON_HeadUp
#ifndef ID_BUTTON_HeadDown
#define ID_BUTTON_HeadDown		"ID_BUTTON_HeadDown"
#endif  ID_BUTTON_HeadDown
#ifndef ID_TEXT_ShengRi
#define ID_TEXT_ShengRi		"ID_TEXT_ShengRi"
#endif  ID_TEXT_ShengRi
#ifndef ID_TEXT_Month
#define ID_TEXT_Month		"ID_TEXT_Month"
#endif  ID_TEXT_Month
#ifndef ID_TEXT_Day
#define ID_TEXT_Day		"ID_TEXT_Day"
#endif  ID_TEXT_Day
#ifndef ID_COMBOBOX_Month
#define ID_COMBOBOX_Month		"ID_COMBOBOX_Month"
#endif  ID_COMBOBOX_Month
#ifndef ID_COMBOBOX_Day
#define ID_COMBOBOX_Day		"ID_COMBOBOX_Day"
#endif  ID_COMBOBOX_Day

class MeCamera;
class CPlayerAnim;
class CPlayer;
#ifndef ID_SCROLLBAREX_Stature
#define ID_SCROLLBAREX_Stature		"ID_SCROLLBAREX_Stature"
#endif  ID_SCROLLBAREX_Stature
#ifndef ID_TEXT_StatureZ
#define ID_TEXT_StatureZ		"ID_TEXT_StatureZ"
#endif  ID_TEXT_StatureZ
#ifndef ID_TEXT_Low
#define ID_TEXT_Low		"ID_TEXT_Low"
#endif  ID_TEXT_Low
#ifndef ID_TEXT_High
#define ID_TEXT_High		"ID_TEXT_High"
#endif  ID_TEXT_High

#ifndef ID_BUTTON_Near
#define ID_BUTTON_Near		"ID_BUTTON_Near"
#endif  ID_BUTTON_Near
#ifndef ID_BUTTON_Farness
#define ID_BUTTON_Farness		"ID_BUTTON_Farness"
#endif  ID_BUTTON_Farness

#ifndef ID_BUTTON_ArmourL
#define ID_BUTTON_ArmourL		"ID_BUTTON_ArmourL"
#endif  ID_BUTTON_ArmourL
#ifndef ID_BUTTON_ArmourR
#define ID_BUTTON_ArmourR		"ID_BUTTON_ArmourR"
#endif  ID_BUTTON_ArmourR
#ifndef ID_TEXT_Armour
#define ID_TEXT_Armour		"ID_TEXT_Armour"
#endif  ID_TEXT_Armour
#include "UiBase.h"
class CUI_ID_FRAME_CREATE :public CUIBase
{
public:	
	 CUI_ID_FRAME_CREATE();
	 enum ePortraitId
	 {
		 Portrait_First = 0,
		 Portrait_Second,
		 Portrait_Third,
		 Portrait_Forth,
	 };
	 // Member
private:
	 ControlFrame*	m_pID_FRAME_CREATE;
	 //ControlPicture*	m_pID_PICTURE_Property;
	 ControlPicture*	m_pID_PICTURE_Title;
	 ControlPicture*	m_pID_PICTURE_JobWall;
	 ControlEdit*	m_pID_EDIT_Name;
	 ControlButton*	m_pID_BUTTON_CheckName;
	 ControlPicture*	m_pID_PICTURE_HairWall;
	 ControlPicture*	m_pID_PICTURE_FaceWall;
	 ControlButton*	m_pID_BUTTON_HairL;
	 ControlButton*	m_pID_BUTTON_HairR;
	 ControlButton*	m_pID_BUTTON_HeadL;
	 ControlButton*	m_pID_BUTTON_HeadR;
	 ControlPicture*	m_pID_PICTURE_TitlePic;
	 ControlPicture*	m_pID_PICTURE_FenGe;
	 ControlButton*	m_pID_BUTTON_TurnR;
	 ControlButton*	m_pID_BUTTON_TurnL;
	 ControlButton*	m_pID_BUTTON_OK;
	 ControlButton*	m_pID_BUTTON_Back;
	 ControlText*	m_pID_TEXT_Name;
	 ControlText*	m_pID_TEXT_Hair;
	 ControlText*	m_pID_TEXT_Face;
	 ControlText*	m_pID_TEXT_ProName;
	 ControlText*	m_pID_TEXT_ProInfo;
// 	 ControlPicture*	m_pID_PICTURE_Spear;
// 	 ControlPicture*	m_pID_PICTURE_Sword;
// 	 ControlPicture*	m_pID_PICTURE_Staff;
// 	 ControlPicture*	m_pID_PICTURE_Fan;
// 	 ControlPicture*	m_pID_PICTURE_Bow;
	 ControlCheckBox*	m_pID_CHECKBOX_JobOther;
// 	 ControlText*	m_pID_TEXT_Sex;
// 	 ControlText*	m_pID_TEXT_Man;
// 	 ControlText*	m_pID_TEXT_Woman;
	 ControlCheckBox*	m_pID_CHECKBOX_Man;
	 ControlCheckBox*	m_pID_CHECKBOX_Woman;
	 ControlCheckBox*	m_pID_CHECKBOX_Spear;
	 ControlCheckBox*	m_pID_CHECKBOX_Sword;
	 ControlCheckBox*	m_pID_CHECKBOX_Staff;
	 ControlCheckBox*	m_pID_CHECKBOX_Bow;
	 ControlCheckBox*	m_pID_CHECKBOX_Fan;
// 	 ControlText*	m_pID_TEXT_HairZ;
// 	 ControlText*	m_pID_TEXT_FaceZ;
	 ControlButton*	m_pID_BUTTON_Random;
	 ControlButton*	m_pID_BUTTON_Reset;

	 ControlScrollBarEx*	m_pID_SCROLLBAREX_Stature;
	/* ControlText*	m_pID_TEXT_StatureZ;*/
	 ControlText*	m_pID_TEXT_Low;
	 ControlText*	m_pID_TEXT_High;

	 // 国家  added by zhuomeng.hu		[8/18/2010]
	 ControlCheckBox*	m_pID_CHECKBOX_Country1;
	 ControlCheckBox*	m_pID_CHECKBOX_Country2;
	 ControlCheckBox*	m_pID_CHECKBOX_Country3;
	 ControlCheckBox*	m_pID_CHECKBOX_Country4;
	 ControlText*	m_pID_TEXT_CountryDesc;
	 ControlPicture*	m_pID_PICTURE_CountryIcon1;
	 ControlPicture*	m_pID_PICTURE_CountryIcon2;
	 ControlPicture*	m_pID_PICTURE_CountryIcon3;
	 ControlPicture*	m_pID_PICTURE_CountryIcon4;
	 ControlPicture*	m_pID_PICTURE_CountryIconRandom;
	 ControlText*	m_pID_TEXT_CountryName;
	 ControlCheckBox*	m_pID_CHECKBOX_CountryAuto;
	 ControlText*	m_pID_TEXT_CountryAutoText;
	 ControlText*	m_pID_TEXT_CountryAutoDesc;

	 //  头像		added by zhuomeng.hu		[8/20/2010]
	 ControlCheckBox*	m_pID_CHECKBOX_Portrait1;
	 ControlCheckBox*	m_pID_CHECKBOX_Portrait2;
	 ControlCheckBox*	m_pID_CHECKBOX_Portrait3;
	 ControlCheckBox*	m_pID_CHECKBOX_Portrait4;
	 ControlButton*		m_pID_BUTTON_HeadUp;
	 ControlButton*		m_pID_BUTTON_HeadDown;

	 ControlText*	m_pID_TEXT_ShengRi;
	 ControlText*	m_pID_TEXT_Month;
	 ControlText*	m_pID_TEXT_Day;
	 ControlComboBox*	m_pID_COMBOBOX_Month;
	 ControlComboBox*	m_pID_COMBOBOX_Day;

	 ControlButton*	   m_pID_BUTTON_Near;
	 ControlButton*	   m_pID_BUTTON_Farness;

	 ControlText*	m_pID_TEXT_Armour;
	 ControlButton*	m_pID_BUTTON_ArmourL;
	 ControlButton*	m_pID_BUTTON_ArmourR;
public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_EDIT_NameOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_CheckNameOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HairLOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HairROnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HeadLOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HeadROnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_TurnROnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_TurnLOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_BackOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_ManOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_WomanOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_JiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_DaoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_WuOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_JianOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_QiangOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_JobOtherOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_RandomOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ResetOnButtonClick( ControlObject* pSender );

	void ID_SCROLLBAREX_StatureOnScrollBarExUpdatePos( ControlObject* pSender, int n );

	// 国家 added by zhuomeng.hu		[8/18/2010]
	void ID_CHECKBOX_Country1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Country2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Country3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Country4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_CountryAutoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	// 头像		added by zhuomeng.hu		[8/20/2010]
	void ID_CHECKBOX_Portrait1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Portrait2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Portrait3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Portrait4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_HeadUpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HeadDownOnButtonClick( ControlObject* pSender );

	void ID_COMBOBOX_MonthOnComboBoxChange( ControlObject* pSender, const char* szData );
	void ID_COMBOBOX_DayOnComboBoxChange( ControlObject* pSender, const char* szData );

	bool ID_BUTTON_NearOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FarnessOnButtonClick( ControlObject* pSender );

	bool ID_BUTTON_ArmourLOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ArmourROnButtonClick( ControlObject* pSender );
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	        // 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
    void RandomPression();              // 随机设置个职业

	void RefreshEffect();

public:
	ControlFrame* GetFrame() { return m_pID_FRAME_CREATE; }
    void SetStateToSelect(bool bState = false);
    bool GetStateToSelect();
	void EnableOKBtn();								//added by zhuomeng.hu		[9/3/2010]
    //void SetStateToSelectWeapon(bool bState = false);
    //bool GetStateToSelectWeapon();
    void Refresh( bool bUseDefault, bool bPlayAnim = true, bool bResetAnim = true );
    void InitProfession( int nProfession );
    bool PickPlayerOnLButtonUp();
    void Clear();
    static bool frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );

    HIMC GetImeInstance()
    {
        return s_hImcDef;
    }
    void SetImeInstance(HIMC hIme)
    {
        s_hImcDef = hIme;
    }
    void SetPlayerScaleDelta(float fDelta)
    {
        m_fPlayerScale += fDelta;
        if( m_fPlayerScale < gCfg.m_fPlayerScaleMin )
            m_fPlayerScale = gCfg.m_fPlayerScaleMin; 
        if( m_fPlayerScale > gCfg.m_fPlayerScaleMax )
            m_fPlayerScale = gCfg.m_fPlayerScaleMax; 
    }

	ControlEdit* GetEditName();

    void LoadPortrait();										                    //	加载头像		added by zhuomeng.hu		[8/24/2010]
    std::string GetPortraitName( int sex, int portraitId, bool bGrey = false );     // 获取头像文件名   added by ZhuoMeng.Hu		[9/19/2010]

	void RefreshPlayerAnim(int nSex,int nCountry);
public:
	static bool CreateRole(char bIsTell,void* pData);
	void SendCreateRoleMsg();
protected:
    void SetPlayerScaleByScrollBarValue(int nValue)
    {
		m_fPlayerScale = 0.8 + nValue / 1000.0 * 0.2;

		// 角色缩放范围是0.8 ~ 1.0
		if (m_fPlayerScale < 0.8f)
			m_fPlayerScale = 0.8;

		if (m_fPlayerScale > 1)
			m_fPlayerScale = 1;
    }
    void ResetStature();
    void SetSex(int sex);
	void UpdatePortrait( int sex, int selectId, int showRow );	//	更新头像		added by zhuomeng.hu		[8/24/2010]

    HIMC		    s_hImcDef;
    //bool            m_bToSelectWeapon;
    int			    m_nSex;
    int			    m_nCountry;
    int				m_nFace;
    int				m_nHair;
    int				m_nCloth;
    int				m_nHairColor;

	int             m_nDefaultHair;
	int             m_nDefaultFace;

	//added by zhuomeng.hu		[8/18/2010]
	int				m_nRealCountry;												//m_nCountry为职业标识，此处为国家定义
	int				m_nSelPortraitId;											//选中的头像ID
	int				m_nShowRow;													//当前显示头像的行数
	std::string		m_defPortrait;												//缺省背景文件路径
	std::vector< pair< std::string, std::string > >		m_malePortraitVec;		//保存男性头像文件路径
	std::vector< pair< std::string, std::string > >		m_femalePortraitVec;	//女性

    MeCamera        *m_pCamera;
    CPlayerAnim*	m_pPlayerAnim;
    CPlayer_SEquipment m_equip[ eKeyAll_Max ];
    CPlayer_SEquipment m_PlayerEquip[ eKeyAll_Max ];
    int             m_iMaleNum;
    int             m_iFemaleNum;
    BOOL		    m_bUpdateOnce;
    D3DXVECTOR3		m_vPlayerPos;
	float			m_fPlayerBaseScale;
    D3DXVECTOR3     m_vEye;
    D3DXVECTOR3     m_vLookat;
    FLOAT 			m_fRot;

    bool            m_bIsTileLoaded;

    CAvatarSystemSetting* m_pSetting;
    CAvatarSystemSetting::SDefSetting*	m_pSex;
    CAvatarSystemSetting::SDefSetting*	m_pMaleDressId;
    CAvatarSystemSetting::SDefSetting*	m_pFemaleDressId;
    CAvatarSystemSetting::SDefSetting*	m_pMaleFaceId;
    CAvatarSystemSetting::SDefSetting*	m_pFemaleFaceId;
    CAvatarSystemSetting::SDefSetting*	m_pMaleHairId;
    CAvatarSystemSetting::SDefSetting*	m_pFemaleHairId;
	CAvatarSystemSetting::SDefSetting*	m_pCountryId;		// 国家  added by zhuomeng.hu		[8/18/2010]

    MexAnimCtrl*    m_pCameraModel;
    bool            m_bNeedZoomIn;
    bool            m_bNeedZoomOut;
    bool            m_bCameraZoomIn;

	MexAnimCtrl*    m_pBGModel;

    float           m_fPlayerScale;     // 测试人物模型缩放
    CPlayer*        m_pPlayer;
    char            m_szEffectName[MAX_PATH];     // 人物播动作时的特效
    bool            m_bNeedPlayEffect;
    int             m_iEffectID;
	int             m_nSelEquip;
public:
	const char* GetXinZuo(int month,int day); //获得星座
	void InitDayCombobox(ControlComboBox* _pBox_, uint8 month_);
	void InitMonthCombobox(ControlComboBox* _pBox_);
};
extern CUI_ID_FRAME_CREATE s_CUI_ID_FRAME_CREATE;
