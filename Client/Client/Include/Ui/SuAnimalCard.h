/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\yang.xu\桌面\宠物\PetCard.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "GlobalDef.h"
#include "PlayerAnimCtrl.h"
#include "UIBase.h"

#ifndef ID_FRAME_PetCard
#define ID_FRAME_PetCard		"ID_FRAME_PetCard"
#endif  ID_FRAME_PetCard
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_TEXT_TitleTop
#define ID_TEXT_TitleTop		"ID_TEXT_TitleTop"
#endif  ID_TEXT_TitleTop
#ifndef ID_PICTURE_PetModel
#define ID_PICTURE_PetModel		"ID_PICTURE_PetModel"
#endif  ID_PICTURE_PetModel
#ifndef ID_BUTTON_ToLeft
#define ID_BUTTON_ToLeft		"ID_BUTTON_ToLeft"
#endif  ID_BUTTON_ToLeft
#ifndef ID_BUTTON_ToRight
#define ID_BUTTON_ToRight		"ID_BUTTON_ToRight"
#endif  ID_BUTTON_ToRight
#ifndef ID_TEXT_Phyle
#define ID_TEXT_Phyle		"ID_TEXT_Phyle"
#endif  ID_TEXT_Phyle
#ifndef ID_LISTIMG_CatchLv
#define ID_LISTIMG_CatchLv		"ID_LISTIMG_CatchLv"
#endif  ID_LISTIMG_CatchLv
#ifndef ID_TEXT_PetNameTitle
#define ID_TEXT_PetNameTitle		"ID_TEXT_PetNameTitle"
#endif  ID_TEXT_PetNameTitle
#ifndef ID_LIST_PetName
#define ID_LIST_PetName		"ID_LIST_PetName"
#endif  ID_LIST_PetName
#ifndef ID_TEXT_Attribute
#define ID_TEXT_Attribute		"ID_TEXT_Attribute"
#endif  ID_TEXT_Attribute
#ifndef ID_TEXT_Lv
#define ID_TEXT_Lv		"ID_TEXT_Lv"
#endif  ID_TEXT_Lv
#ifndef ID_LISTIMG_Genre
#define ID_LISTIMG_Genre		"ID_LISTIMG_Genre"
#endif  ID_LISTIMG_Genre
#ifndef ID_TEXT_Dower
#define ID_TEXT_Dower		"ID_TEXT_Dower"
#endif  ID_TEXT_Dower
#ifndef ID_TEXT_DowerLvZ
#define ID_TEXT_DowerLvZ		"ID_TEXT_DowerLvZ"
#endif  ID_TEXT_DowerLvZ
#ifndef ID_TEXT_TEXTZ
#define ID_TEXT_TEXTZ		"ID_TEXT_TEXTZ"
#endif  ID_TEXT_TEXTZ
#ifndef ID_LIST_IconName
#define ID_LIST_IconName		"ID_LIST_IconName"
#endif  ID_LIST_IconName
#ifndef ID_LISTIMG_Icon
#define ID_LISTIMG_Icon		"ID_LISTIMG_Icon"
#endif  ID_LISTIMG_Icon
#ifndef ID_TEXT_TEXTZ0
#define ID_TEXT_TEXTZ0		"ID_TEXT_TEXTZ0"
#endif  ID_TEXT_TEXTZ0
#ifndef ID_TEXT_Introduce
#define ID_TEXT_Introduce		"ID_TEXT_Introduce"
#endif  ID_TEXT_Introduce
#ifndef ID_TEXT_TEXTZ1
#define ID_TEXT_TEXTZ1		"ID_TEXT_TEXTZ1"
#endif  ID_TEXT_TEXTZ1
#ifndef ID_TEXT_Address
#define ID_TEXT_Address		"ID_TEXT_Address"
#endif  ID_TEXT_Address
#ifndef ID_BUTTON_PageUp
#define ID_BUTTON_PageUp		"ID_BUTTON_PageUp"
#endif  ID_BUTTON_PageUp
#ifndef ID_BUTTON_PageDown
#define ID_BUTTON_PageDown		"ID_BUTTON_PageDown"
#endif  ID_BUTTON_PageDown
#ifndef ID_TEXT_Page
#define ID_TEXT_Page		"ID_TEXT_Page"
#endif  ID_TEXT_Page
#ifndef ID_BUTTON_Return
#define ID_BUTTON_Return		"ID_BUTTON_Return"
#endif  ID_BUTTON_Return
#ifndef ID_TEXT_ForceZ
#define ID_TEXT_ForceZ		"ID_TEXT_ForceZ"
#endif  ID_TEXT_ForceZ
#ifndef ID_TEXT_NimbusZ
#define ID_TEXT_NimbusZ		"ID_TEXT_NimbusZ"
#endif  ID_TEXT_NimbusZ
#ifndef ID_TEXT_StaminaZ
#define ID_TEXT_StaminaZ		"ID_TEXT_StaminaZ"
#endif  ID_TEXT_StaminaZ
#ifndef ID_TEXT_CelerityZ
#define ID_TEXT_CelerityZ		"ID_TEXT_CelerityZ"
#endif  ID_TEXT_CelerityZ
#ifndef ID_PICTURE_LeiBieWu
#define ID_PICTURE_LeiBieWu		"ID_PICTURE_LeiBieWu"
#endif  ID_PICTURE_LeiBieWu
#ifndef ID_PICTURE_LeiBieFa
#define ID_PICTURE_LeiBieFa		"ID_PICTURE_LeiBieFa"
#endif  ID_PICTURE_LeiBieFa
#ifndef ID_PICTURE_WXTu
#define ID_PICTURE_WXTu		"ID_PICTURE_WXTu"
#endif  ID_PICTURE_WXTu
#ifndef ID_PICTURE_WXJin
#define ID_PICTURE_WXJin		"ID_PICTURE_WXJin"
#endif  ID_PICTURE_WXJin
#ifndef ID_PICTURE_WXMu
#define ID_PICTURE_WXMu		"ID_PICTURE_WXMu"
#endif  ID_PICTURE_WXMu
#ifndef ID_PICTURE_WXShui
#define ID_PICTURE_WXShui		"ID_PICTURE_WXShui"
#endif  ID_PICTURE_WXShui
#ifndef ID_PICTURE_WXHuo
#define ID_PICTURE_WXHuo		"ID_PICTURE_WXHuo"
#endif  ID_PICTURE_WXHuo
#ifndef ID_PICTURE_ZhongZuRen
#define ID_PICTURE_ZhongZuRen		"ID_PICTURE_ZhongZuRen"
#endif  ID_PICTURE_ZhongZuRen
#ifndef ID_PICTURE_ZhongZuJi
#define ID_PICTURE_ZhongZuJi		"ID_PICTURE_ZhongZuJi"
#endif  ID_PICTURE_ZhongZuJi
#ifndef ID_PICTURE_ZhongZuShou
#define ID_PICTURE_ZhongZuShou		"ID_PICTURE_ZhongZuShou"
#endif  ID_PICTURE_ZhongZuShou
#ifndef ID_PICTURE_ZhongZuXian
#define ID_PICTURE_ZhongZuXian		"ID_PICTURE_ZhongZuXian"
#endif  ID_PICTURE_ZhongZuXian
#ifndef ID_PICTURE_ZhongZuGui
#define ID_PICTURE_ZhongZuGui		"ID_PICTURE_ZhongZuGui"
#endif  ID_PICTURE_ZhongZuGui
#ifndef ID_PICTURE_ZhongZuYao
#define ID_PICTURE_ZhongZuYao		"ID_PICTURE_ZhongZuYao"
#endif  ID_PICTURE_ZhongZuYao
#ifndef ID_PICTURE_ZhongZuShen
#define ID_PICTURE_ZhongZuShen		"ID_PICTURE_ZhongZuShen"
#endif  ID_PICTURE_ZhongZuShen
#ifndef ID_PICTURE_ZhongZuMo
#define ID_PICTURE_ZhongZuMo		"ID_PICTURE_ZhongZuMo"
#endif  ID_PICTURE_ZhongZuMo
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
#ifndef ID_PICTURE_ZiZhi
#define ID_PICTURE_ZiZhi		"ID_PICTURE_ZiZhi"
#endif  ID_PICTURE_ZiZhi
#ifndef ID_PICTURE_Force
#define ID_PICTURE_Force		"ID_PICTURE_Force"
#endif  ID_PICTURE_Force
#ifndef ID_PICTURE_Nimbus
#define ID_PICTURE_Nimbus		"ID_PICTURE_Nimbus"
#endif  ID_PICTURE_Nimbus
#ifndef ID_PICTURE_Stamina
#define ID_PICTURE_Stamina		"ID_PICTURE_Stamina"
#endif  ID_PICTURE_Stamina
#ifndef ID_PICTURE_Celerity
#define ID_PICTURE_Celerity		"ID_PICTURE_Celerity"
#endif  ID_PICTURE_Celerity
#ifndef ID_TEXT_DowerLv
#define ID_TEXT_DowerLv		"ID_TEXT_DowerLv"
#endif  ID_TEXT_DowerLv
#ifndef ID_PICTURE_BianShen
#define ID_PICTURE_BianShen		"ID_PICTURE_BianShen"
#endif  ID_PICTURE_BianShen
#ifndef ID_TEXT_LiLZZ
#define ID_TEXT_LiLZZ		"ID_TEXT_LiLZZ"
#endif  ID_TEXT_LiLZZ
#ifndef ID_TEXT_LLZZ
#define ID_TEXT_LLZZ		"ID_TEXT_LLZZ"
#endif  ID_TEXT_LLZZ
#ifndef ID_TEXT_Name
#define ID_TEXT_Name		"ID_TEXT_Name"
#endif  ID_TEXT_Name
#ifndef ID_TEXT_MJZZ
#define ID_TEXT_MJZZ		"ID_TEXT_MJZZ"
#endif  ID_TEXT_MJZZ
#ifndef ID_LISTIMG_Icon_1
#define ID_LISTIMG_Icon_1		"ID_LISTIMG_Icon_1"
#endif  ID_LISTIMG_Icon_1
#ifndef ID_PICTURE_BianShen
#define ID_PICTURE_BianShen		"ID_PICTURE_BianShen"
#endif  ID_PICTURE_BianShen
#ifndef ID_TEXT_NLZZ
#define ID_TEXT_NLZZ "ID_TEXT_NLZZ"
#endif ID_TEXT_NLZZ
#ifndef ID_CHECKBOX_BianShen
#define ID_CHECKBOX_BianShen		"ID_CHECKBOX_BianShen"
#endif  ID_CHECKBOX_BianShen
#ifndef ID_CHECKBOX_ZiZhi
#define ID_CHECKBOX_ZiZhi		"ID_CHECKBOX_ZiZhi"
#endif  ID_CHECKBOX_ZiZhi
#ifndef ID_TEXT_CardAmount
#define ID_TEXT_CardAmount "ID_TEXT_CardAmount"
#endif ID_TEXT_CardAmount

class CUI_ID_FRAME_SuAnimalCard:public CUIBase
{
	// Member
private:	

	 ControlFrame*	m_pID_FRAME_PetCard;
	 ControlButton*	m_pID_BUTTON_HELP;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlText*	m_pID_TEXT_TitleTop;
	 ControlPicture*	m_pID_PICTURE_PetModel;
	 ControlButton*	m_pID_BUTTON_ToLeft;
	 ControlButton*	m_pID_BUTTON_ToRight;
	 ControlText*	m_pID_TEXT_Phyle;
	 ControlListImage*	m_pID_LISTIMG_CatchLv;
	 ControlText*	m_pID_TEXT_PetNameTitle;
	 ControlList*	m_pID_LIST_PetName;
	 ControlText*	m_pID_TEXT_Attribute;
	 ControlText*	m_pID_TEXT_Lv;
	 ControlListImage*	m_pID_LISTIMG_Genre;
	 ControlText*	m_pID_TEXT_Dower;
	 ControlText*	m_pID_TEXT_DowerLvZ;
	 ControlText*	m_pID_TEXT_TEXTZ;
	 ControlList*	m_pID_LIST_IconName;
	 ControlListImage*	m_pID_LISTIMG_Icon;
	 ControlText*	m_pID_TEXT_TEXTZ0;
	 ControlText*	m_pID_TEXT_Introduce;
	 ControlText*	m_pID_TEXT_TEXTZ1;
	 ControlText*	m_pID_TEXT_Address;
	 ControlButton*	m_pID_BUTTON_PageUp;
	 ControlButton*	m_pID_BUTTON_PageDown;
	 ControlText*	m_pID_TEXT_Page;
	 ControlButton*	m_pID_BUTTON_Return;
	 ControlText*	m_pID_TEXT_ForceZ;
	 ControlText*	m_pID_TEXT_NimbusZ;
	 ControlText*	m_pID_TEXT_StaminaZ;
	 ControlText*	m_pID_TEXT_CelerityZ;
	 ControlPicture*	m_pID_PICTURE_LeiBieWu;
	 ControlPicture*	m_pID_PICTURE_LeiBieFa;
	 ControlPicture*	m_pID_PICTURE_WXTu;
	 ControlPicture*	m_pID_PICTURE_WXJin;
	 ControlPicture*	m_pID_PICTURE_WXMu;
	 ControlPicture*	m_pID_PICTURE_WXShui;
	 ControlPicture*	m_pID_PICTURE_WXHuo;
	 ControlPicture*	m_pID_PICTURE_ZhongZuRen;
	 ControlPicture*	m_pID_PICTURE_ZhongZuJi;
	 ControlPicture*	m_pID_PICTURE_ZhongZuShou;
	 ControlPicture*	m_pID_PICTURE_ZhongZuXian;
	 ControlPicture*	m_pID_PICTURE_ZhongZuGui;
	 ControlPicture*	m_pID_PICTURE_ZhongZuYao;
	 ControlPicture*	m_pID_PICTURE_ZhongZuShen;
	 ControlPicture*	m_pID_PICTURE_ZhongZuMo;
	 ControlCheckBox* m_phyleIcon[EPhyle_MaxCount+1];
// 	 ControlCheckBox*	m_pID_CHECKBOX_Full;
// 	 ControlCheckBox*	m_pID_CHECKBOX_Ren;
// 	 ControlCheckBox*	m_pID_CHECKBOX_Shen;
// 	 ControlCheckBox*	m_pID_CHECKBOX_Xian;
// 	 ControlCheckBox*	m_pID_CHECKBOX_Ji;
// 	 ControlCheckBox*	m_pID_CHECKBOX_Mo;
// 	 ControlCheckBox*	m_pID_CHECKBOX_Gui;
// 	 ControlCheckBox*	m_pID_CHECKBOX_Yao;
// 	 ControlCheckBox*	m_pID_CHECKBOX_Shou;
	 ControlPicture*	m_pID_PICTURE_ZiZhi;
	 ControlPicture*	m_pID_PICTURE_Force;
	 ControlPicture*	m_pID_PICTURE_Nimbus;
	 ControlPicture*	m_pID_PICTURE_Stamina;
	 ControlPicture*	m_pID_PICTURE_Celerity;
	 ControlText*	m_pID_TEXT_LiLZZ;
	 ControlText*	m_pID_TEXT_LLZZ;
	 ControlText*	m_pID_TEXT_Name;
	 ControlText*	m_pID_TEXT_MJZZ;
	 ControlText *  m_pID_TEXT_NLZZ;
	 ControlListImage*	m_pID_LISTIMG_Icon_1;
	 ControlPicture*	m_pID_PICTURE_BianShen;
	ControlText*    m_pID_TEXT_DowerLv;
	 ControlCheckBox*	m_pID_CHECKBOX_ZiZhi;
	 ControlCheckBox*	m_pID_CHECKBOX_BianShen;
	 ControlText*		m_pID_TEXT_CardAmount;
public:	
	// Frame
	CUI_ID_FRAME_SuAnimalCard();
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ToLeftOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ToRightOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_CatchLvOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_CatchLvOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_CatchLvOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_CatchLvOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	void ID_LIST_PetNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_LISTIMG_GenreOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_GenreOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_GenreOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_GenreOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	void ID_LIST_IconNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_LISTIMG_IconOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_IconOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_IconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_IconOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_PageUpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PageDownOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ReturnOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_FullOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_RenOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_ShenOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_XianOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_JiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_MoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_GuiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_YaoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_ShouOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	/*bool ID_LISTIMG_IconOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );*/
// 	bool ID_LISTIMG_IconOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
// 	bool ID_LISTIMG_IconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
// 	bool ID_LISTIMG_IconOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	void ID_CHECKBOX_ZiZhiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_BianShenOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	virtual bool _LoadUI();															// 载入UI
	bool DoControlConnect();													// 关连控件
	virtual bool _UnLoadUI();													// 卸载UI
	virtual bool _IsVisable();														// 是否可见
	virtual void _SetVisable( const bool bVisable );				// 设置是否可视

	void RefreshPage(ItemDefine::SPetMonster* m_pet,int phyle);
private:	
	bool m_bRotate;
	int	  m_nModelId; 
	CPlayer*			m_pPlayer;
	CPlayerAnim*        m_pPlayerAnim;
	float			m_fRotateZ;
	void	SetElement(int n_element);												//设置五行
	void    SetAttackType(int n_index);												//设置攻击类型
	void    SetPhyle(int n_id);																//设置种族
	void	SetCatchLvl(int n_id);															//设置捕捉品质
	void	SetTakeLevel(int n_id);														//设置携带等级
	void    SetBaseProperty(ItemDefine::SPetMonster *m_pet); //设置灵力值等
	std::vector<ItemDefine::SPetMonster*> m_vecPetMonster;
	int		m_currentphyle;  //当前种族类型。返回目录时需要用到
	int		m_currentPetId;
	void SortControlGroup();
	ControlGroup m_GroupZiZhi;
	ControlGroup m_GroupBianShen;
	int mCurrPage; //用来记录当前怪物页码。
public:
	void RenderMount( int nMountId, CPlayerAnim* pAnim, float fRotateZ, const RECT& rt );
	void ChangeModel(int modelId, CPlayerAnim* pAnim, int& iOldModelId);
	void RenderViewport();
	static bool UIPetCard_RightLBD(INT nX,INT nY);
	static bool UIPetCard_LeftLBD(INT nX,INT nY);
	void SetRotate(bool bRotate) {m_bRotate = bRotate;}
	void SetCurrentPhyle(std::vector<ItemDefine::SPetMonster*> &m_vecPet);
	void RefreshCheckBoxStatus(int m_currentPhyle);
	void SetCurrPage(int nindex);
	void SetCurrPetTypePic(int pettype);
	ControlFrame *GetFrame() { return m_pID_FRAME_PetCard;}
};
extern CUI_ID_FRAME_SuAnimalCard s_CUI_ID_FRAME_SuAnimalCard;

