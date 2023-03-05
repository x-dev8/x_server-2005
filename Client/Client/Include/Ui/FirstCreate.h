#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "wsCamera.h"
#include "GlobalDef.h"

#ifndef ID_FRAME_FirstCreate
#define ID_FRAME_FirstCreate		"ID_FRAME_FirstCreate"
#endif  ID_FRAME_FirstCreate
#ifndef ID_PICTURE_Bewrite
#define ID_PICTURE_Bewrite		"ID_PICTURE_Bewrite"
#endif  ID_PICTURE_Bewrite
#ifndef ID_CHECKBOX_Woman
#define ID_CHECKBOX_Woman		"ID_CHECKBOX_Woman"
#endif  ID_CHECKBOX_Woman
#ifndef ID_CHECKBOX_Man
#define ID_CHECKBOX_Man		"ID_CHECKBOX_Man"
#endif  ID_CHECKBOX_Man
#ifndef ID_TEXT_ProInfo
#define ID_TEXT_ProInfo		"ID_TEXT_ProInfo"
#endif  ID_TEXT_ProInfo
#ifndef ID_PICTURE_Spear
#define ID_PICTURE_Spear		"ID_PICTURE_Spear"
#endif  ID_PICTURE_Spear
#ifndef ID_PICTURE_Sword
#define ID_PICTURE_Sword		"ID_PICTURE_Sword"
#endif  ID_PICTURE_Sword
#ifndef ID_PICTURE_Fan
#define ID_PICTURE_Fan		"ID_PICTURE_Fan"
#endif  ID_PICTURE_Fan
#ifndef ID_PICTURE_Bow
#define ID_PICTURE_Bow		"ID_PICTURE_Bow"
#endif  ID_PICTURE_Bow
#ifndef ID_CHECKBOX_Spear
#define ID_CHECKBOX_Spear		"ID_CHECKBOX_Spear"
#endif  ID_CHECKBOX_Spear
#ifndef ID_CHECKBOX_Sword
#define ID_CHECKBOX_Sword		"ID_CHECKBOX_Sword"
#endif  ID_CHECKBOX_Sword
#ifndef ID_CHECKBOX_Fan
#define ID_CHECKBOX_Fan		"ID_CHECKBOX_Fan"
#endif  ID_CHECKBOX_Fan
#ifndef ID_CHECKBOX_Bow
#define ID_CHECKBOX_Bow		"ID_CHECKBOX_Bow"
#endif  ID_CHECKBOX_Bow
#ifndef ID_CHECKBOX_Staff
#define ID_CHECKBOX_Staff		"ID_CHECKBOX_Staff"
#endif  ID_CHECKBOX_Staff
#ifndef ID_BUTTON_Return
#define ID_BUTTON_Return		"ID_BUTTON_Return"
#endif  ID_BUTTON_Return
#ifndef ID_BUTTON_Select
#define ID_BUTTON_Select		"ID_BUTTON_Select"
#endif  ID_BUTTON_Select

#ifndef ID_PICTURE_HeiDong
#define ID_PICTURE_HeiDong		"ID_PICTURE_HeiDong"
#endif  ID_PICTURE_HeiDong

#ifndef ID_PICTURE_Background
#define ID_PICTURE_Background	"ID_PICTURE_Background"
#endif	ID_PICTURE_Background

#ifndef ID_PICTURE_vedio
#define ID_PICTURE_vedio		"ID_PICTURE_vedio"
#endif  ID_PICTURE_vedio

#ifndef ID_BUTTON_Back
#define ID_BUTTON_Back		"ID_BUTTON_Back"
#endif  ID_BUTTON_Back


#define MAX_PLAYER_NUM   8  //场景中有多少个角色模型

enum eManWomanClassState
{
	eManWomanClassState_NvJi,
	eManWomanClassState_NanWu,
	eManWomanClassState_Other
};

class CUI_ID_FRAME_FirstCreate : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_FirstCreate();
	 ControlFrame*	m_pID_FRAME_FirstCreate;
	 ControlPicture*	m_pID_PICTURE_Bewrite;
	 ControlCheckBox*	m_pID_CHECKBOX_Woman;
	 ControlCheckBox*	m_pID_CHECKBOX_Man;
	 ControlText*	m_pID_TEXT_ProInfo;
	 ControlPicture*	m_pID_PICTURE_Spear;
	 ControlPicture*	m_pID_PICTURE_Sword;
	 ControlPicture*	m_pID_PICTURE_Fan;
	 ControlPicture*	m_pID_PICTURE_Bow;
	 ControlPicture*	m_pID_PICTURE_Staff;	 
	 ControlCheckBox*	m_pID_CHECKBOX_Spear;
	 ControlCheckBox*	m_pID_CHECKBOX_Sword;
	 ControlCheckBox*	m_pID_CHECKBOX_Fan;
	 ControlCheckBox*	m_pID_CHECKBOX_Bow;
	 ControlCheckBox*	m_pID_CHECKBOX_Staff;
	 ControlButton*	m_pID_BUTTON_Return;
	 ControlButton*	m_pID_BUTTON_Select;
	 ControlPicture*	m_pID_PICTURE_HeiDong;
	 ControlPicture*	m_pID_PICTURE_Background;
	 ControlPicture*	m_pID_PICTURE_vedio;
	 ControlButton*	m_pID_BUTTON_Back;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_CHECKBOX_WomanOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_ManOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_JiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_DaoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_QiangOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_JianOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_WuOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_ReturnOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SelectOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_BackOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	static bool SelectModelLButtonDown(OUT ControlObject* pSender);
	static bool MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );
public:
	void  LoadScene();

	std::string GetPlayAnimBySel();
	void  PlayControlAnim();
	void  ChangeScene(int nIndex,int nSex);
	void  MoveCameraByIndex(std::string& strAnim);
	void  SetStateToCreate(bool bValue){m_bToCreate = bValue;}
	bool  GetStateToCreate(){return m_bToCreate;}

	void SetStateToSelect(bool bValue){m_bToSelect = bValue;}
	bool GetStateToSelect(){return m_bToSelect;}
	int  GetSex(){return m_bSex;}
	int  GetCountry(){return m_nCurrSel;}
public:
	void SortControl();
	void PlayAnimByActionName(MexAnimCtrl* pModel);
	int  TransLateIndex(std::string& strPro);
	int  PlayerToCamera(const char* pszName);

	void MoveToHole();
	void LocateHole( int x, int y );
	void SetMouseMoveAnim(const char* pszName){m_strMouseAnim = pszName;}

	void SetSelCheckBox(int nIndex);
	ControlFrame* GetFrame() { return m_pID_FRAME_FirstCreate; }

	/*
	 * 2012.6.30 wangshuai
	 * 根据当前选中的职业, 屏幕女戟和舞男
	 */
	void SetManWomanCheckboxState(eManWomanClassState state);

	void OnGameWindowMove(int x, int y);

private:
	ControlGroup m_Group;
	ControlPicture* m_pPic[EArmType_MaxSize - 1];

private:
	bool m_bIsTileLoaded;

	MeCamera  m_Camera;

	MexAnimCtrl* m_pCameraModel;
	TObjectInfo* m_pPlayerModel[MAX_PLAYER_NUM];

	D3DXVECTOR3     m_vEye;
	D3DXVECTOR3     m_vLookat;

	std::string m_strLastSel;  //记录上次选择的模型	void  PlayControlAnim();
	int   m_nCurrSel;          //当前选择模型
	std::string m_strLastPlayer; //记录上次选择的角色

	bool  m_bToCreate;
	bool  m_bToSelect;
	bool  m_bSex; //性别

	int		m_nSelModelIdx;		//选择的角色索引
	std::string m_strMouseAnim;
};
extern CUI_ID_FRAME_FirstCreate s_CUI_ID_FRAME_FirstCreate;
