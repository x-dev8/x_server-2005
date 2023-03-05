/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\yang.xu\桌面\宠物\PetCardList.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "GlobalDef.h"
#include "PlayerAnimCtrl.h"
#include "UIBase.h"
#include "MsgBase.h"
#include "MessageDefine.h"

#ifndef ID_FRAME_PetCardList
#define ID_FRAME_PetCardList		"ID_FRAME_PetCardList"
#endif  ID_FRAME_PetCardList
#ifndef ID_TEXT_PetTitle
#define ID_TEXT_PetTitle		"ID_TEXT_PetTitle"
#endif  ID_TEXT_PetTitle
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_COMBOBOX_Distribute
#define ID_COMBOBOX_Distribute		"ID_COMBOBOX_Distribute"
#endif  ID_COMBOBOX_Distribute
#ifndef ID_EDIT_Content
#define ID_EDIT_Content		"ID_EDIT_Content"
#endif  ID_EDIT_Content
#ifndef ID_BUTTON_Lookup
#define ID_BUTTON_Lookup		"ID_BUTTON_Lookup"
#endif  ID_BUTTON_Lookup
#ifndef ID_LIST_PetName
#define ID_LIST_PetName		"ID_LIST_PetName"
#endif  ID_LIST_PetName
#ifndef ID_BUTTON_PageUp
#define ID_BUTTON_PageUp		"ID_BUTTON_PageUp"
#endif  ID_BUTTON_PageUp
#ifndef ID_BUTTON_PageDown
#define ID_BUTTON_PageDown		"ID_BUTTON_PageDown"
#endif  ID_BUTTON_PageDown
#ifndef ID_TEXT_Page
#define ID_TEXT_Page		"ID_TEXT_Page"
#endif  ID_TEXT_Page
#ifndef ID_CHECKBOX_Full
#define ID_CHECKBOX_Full		"ID_CHECKBOX_Full"
#endif  ID_CHECKBOX_Full
#ifndef ID_CHECKBOX_Ren
#define ID_CHECKBOX_Ren		"ID_CHECKBOX_Ren"
#endif  ID_CHECKBOX_Ren
#ifndef ID_CHECKBOX_Shen
#define ID_CHECKBOX_Shen		"ID_CHECKBOX_Shen"
#endif  ID_CHECKBOX_Shen
#ifndef ID_CHECKBOX_Xian
#define ID_CHECKBOX_Xian		"ID_CHECKBOX_Xian"
#endif  ID_CHECKBOX_Xian
#ifndef ID_CHECKBOX_Ji
#define ID_CHECKBOX_Ji		"ID_CHECKBOX_Ji"
#endif  ID_CHECKBOX_Ji
#ifndef ID_CHECKBOX_Mo
#define ID_CHECKBOX_Mo		"ID_CHECKBOX_Mo"
#endif  ID_CHECKBOX_Mo
#ifndef ID_CHECKBOX_Gui
#define ID_CHECKBOX_Gui		"ID_CHECKBOX_Gui"
#endif  ID_CHECKBOX_Gui
#ifndef ID_CHECKBOX_Yao
#define ID_CHECKBOX_Yao		"ID_CHECKBOX_Yao"
#endif  ID_CHECKBOX_Yao
#ifndef ID_CHECKBOX_Shou
#define ID_CHECKBOX_Shou		"ID_CHECKBOX_Shou"
#endif  ID_CHECKBOX_Shou
#ifndef ID_TEXT_Name
#define ID_TEXT_Name		"ID_TEXT_Name"
#endif  ID_TEXT_Name
#ifndef ID_TEXT_Info
#define ID_TEXT_Info		"ID_TEXT_Info"
#endif  ID_TEXT_Info
#ifndef ID_LIST_CardAmount
#define  ID_LIST_CardAmount "ID_LIST_CardAmount"
#endif ID_LIST_CardAmount
#ifndef ID_PICTURE_ZhongZu
#define ID_PICTURE_ZhongZu "ID_PICTURE_ZhongZu"
#endif ID_PICTURE_ZhongZu
#ifndef ID_PICTURE_Ren
#define ID_PICTURE_Ren		"ID_PICTURE_Ren"
#endif  ID_PICTURE_Ren
#ifndef ID_PICTURE_Shen
#define ID_PICTURE_Shen		"ID_PICTURE_Shen"
#endif  ID_PICTURE_Shen
#ifndef ID_PICTURE_Ji
#define ID_PICTURE_Ji		"ID_PICTURE_Ji"
#endif  ID_PICTURE_Ji
#ifndef ID_PICTURE_Xian
#define ID_PICTURE_Xian		"ID_PICTURE_Xian"
#endif  ID_PICTURE_Xian
#ifndef ID_PICTURE_Mo
#define ID_PICTURE_Mo		"ID_PICTURE_Mo"
#endif  ID_PICTURE_Mo
#ifndef ID_PICTURE_Gui
#define ID_PICTURE_Gui		"ID_PICTURE_Gui"
#endif  ID_PICTURE_Gui
#ifndef ID_PICTURE_Yao
#define ID_PICTURE_Yao		"ID_PICTURE_Yao"
#endif  ID_PICTURE_Yao
#ifndef ID_PICTURE_Shou
#define ID_PICTURE_Shou		"ID_PICTURE_Shou"
#endif  ID_PICTURE_Shou
#ifndef ID_PICTURE_Full
#define ID_PICTURE_Full		"ID_PICTURE_Full"
#endif  ID_PICTURE_Full

#ifndef ID_BUTTON_PageUpFrist
#define ID_BUTTON_PageUpFrist		"ID_BUTTON_PageUpFrist"
#endif  ID_BUTTON_PageUpFrist

#ifndef ID_BUTTON_PageDownLast
#define ID_BUTTON_PageDownLast		"ID_BUTTON_PageDownLast"
#endif  ID_BUTTON_PageDownLast

class CUI_ID_FRAME_SuAnimalCardList:public CUIBase
{
	// Member
private:	

	 ControlFrame*	m_pID_FRAME_PetCardList;
	 ControlText*	m_pID_TEXT_PetTitle;
	 ControlButton*	m_pID_BUTTON_HELP;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlComboBox*	m_pID_COMBOBOX_Distribute;
	 ControlEdit*	m_pID_EDIT_Content;
	 ControlButton*	m_pID_BUTTON_Lookup;
	 ControlList*	m_pID_LIST_PetName;
	 ControlButton*	m_pID_BUTTON_PageUp;
	 ControlButton*	m_pID_BUTTON_PageDown;

	 ControlButton*	m_pID_BUTTON_PageUpFrist;
	 ControlButton*	m_pID_BUTTON_PageDownLast;

	 ControlText*	m_pID_TEXT_Page;
	 ControlCheckBox*	m_pID_CHECKBOX_Full;
	 ControlCheckBox*	m_pID_CHECKBOX_Ren;
	 ControlCheckBox*	m_pID_CHECKBOX_Shen;
	 ControlCheckBox*	m_pID_CHECKBOX_Xian;
	 ControlCheckBox*	m_pID_CHECKBOX_Ji;
	 ControlCheckBox*	m_pID_CHECKBOX_Mo;
	 ControlCheckBox*	m_pID_CHECKBOX_Gui;
	 ControlCheckBox*	m_pID_CHECKBOX_Yao;
	 ControlCheckBox*	m_pID_CHECKBOX_Shou;
	 ControlText*	m_pID_TEXT_Name;
	 ControlText*	m_pID_TEXT_Info;
	ControlList *     m_pID_LIST_CardAmount;
	ControlPicture*	m_pID_PICTURE_ZhongZu;
	ControlPicture*	m_pID_PICTURE_Ren;
	ControlPicture*	m_pID_PICTURE_Shen;
	ControlPicture*	m_pID_PICTURE_Ji;
	ControlPicture*	m_pID_PICTURE_Xian;
	ControlPicture*	m_pID_PICTURE_Mo;
	ControlPicture*	m_pID_PICTURE_Gui;
	ControlPicture*	m_pID_PICTURE_Yao;
	ControlPicture*	m_pID_PICTURE_Shou;
	ControlPicture*	m_pID_PICTURE_Full;
public:	
	// Frame
	CUI_ID_FRAME_SuAnimalCardList();
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	void ID_COMBOBOX_DistributeOnComboBoxChange( ControlObject* pSender, const char* szData );
	void ID_EDIT_ContentOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_LookupOnButtonClick( ControlObject* pSender );
	void ID_LIST_PetNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_PageUpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PageDownOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_FullOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_RenOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_ShenOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_XianOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_JiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_MoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_GuiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_YaoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_ShouOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	bool ID_BUTTON_PageUpFristOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PageDownLastOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
	void RefreshPage(int petPhyle);
private:	
	int m_nCurPage;
	int nTotalPage;
	int m_nLastHeight;
private:
	std::vector<SPetIdentify> m_petIdentify;
	// SPetIdentify    m_petIdentify[MAX_PETIDENTIFY_COUNT]; // 所有的宠物图鉴
	static bool m_IsClicked;
	int m_pettype;  //暂存用来存储列表中的宠物类型，为第二次点击使用
	typedef std::map< int, std::vector< ItemDefine::SPetMonster* >> PetInfoMap; //图鉴的存储数据
	PetInfoMap m_petInfoMap;

	int CurrentSelectPhyle;  //当前选择的种族
	int CurrentPetNum;        // 当前种族中的宠物数量
	void SetCurrentPetNum(int phyle);
	std::vector<ItemDefine::SPetMonster*> m_vecPetResult;  //搜索结果
	std::vector<ItemDefine::SPetMonster*> m_vecPetAllInfo; //某种族的全部数据
	SIdentifyData    m_identifyData;												  //所有图鉴数据
public:
	void RefreshPetList(int petPhyle = EPhyle_MaxCount);    //根据不同的种族显示不同的宠物列表
	void ShowPetPhyleInfo(int petPhyle);
	const char* GetPhyleInfo(int petPhyle);
	void RefreshCheckBoxStatus(int m_currentPhyle);
	bool EditInputIsVisable();
	void UpdateIdentify(Msg *msg);
	void UpdateAllIdentify(Msg *msg);
	SPetIdentify* GetSIdentifyData(uint16  petType ) { return m_identifyData.GetPetIdentify(petType);}
	void SetPhylePic(int petPhyle);
	bool sortPetMonster(std::vector<ItemDefine::SPetMonster*>::iterator itor1,std::vector<ItemDefine::SPetMonster*>::iterator itor2);
};
extern CUI_ID_FRAME_SuAnimalCardList s_CUI_ID_FRAME_SuAnimalCardList;

