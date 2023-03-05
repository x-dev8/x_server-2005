/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\yang.xu\桌面\宠物\PetUp.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "GlobalDef.h"
#include "PlayerAnimCtrl.h"
#include "UIBase.h"

#ifndef ID_FRAME_PetUp
#define ID_FRAME_PetUp		"ID_FRAME_PetUp"
#endif  ID_FRAME_PetUp
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_TEXT_TitleTop
#define ID_TEXT_TitleTop		"ID_TEXT_TitleTop"
#endif  ID_TEXT_TitleTop
#ifndef ID_PICTURE_Motherboard
#define ID_PICTURE_Motherboard		"ID_PICTURE_Motherboard"
#endif  ID_PICTURE_Motherboard
#ifndef ID_TEXT_PetNameTitle
#define ID_TEXT_PetNameTitle		"ID_TEXT_PetNameTitle"
#endif  ID_TEXT_PetNameTitle
#ifndef ID_LIST_PetName
#define ID_LIST_PetName		"ID_LIST_PetName"
#endif  ID_LIST_PetName
#ifndef ID_BUTTON_Sure
#define ID_BUTTON_Sure		"ID_BUTTON_Sure"
#endif  ID_BUTTON_Sure
#ifndef ID_BUTTON_Examine
#define ID_BUTTON_Examine		"ID_BUTTON_Examine"
#endif  ID_BUTTON_Examine
#ifndef ID_TEXT_Explain
#define ID_TEXT_Explain		"ID_TEXT_Explain"
#endif  ID_TEXT_Explain
#ifndef ID_TEXT_NowApperception
#define ID_TEXT_NowApperception		"ID_TEXT_NowApperception"
#endif  ID_TEXT_NowApperception
#ifndef ID_TEXT_Probability
#define ID_TEXT_Probability		"ID_TEXT_Probability"
#endif  ID_TEXT_Probability
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_TEXT_Explain0
#define ID_TEXT_Explain0		"ID_TEXT_Explain0"
#endif  ID_TEXT_Explain0
#ifndef ID_TEXT_TextZ0
#define ID_TEXT_TextZ0		"ID_TEXT_TextZ0"
#endif  ID_TEXT_TextZ0
#ifndef ID_TEXT_PetName0
#define ID_TEXT_PetName0		"ID_TEXT_PetName0"
#endif  ID_TEXT_PetName0
#ifndef ID_BUTTON_Choice0
#define ID_BUTTON_Choice0		"ID_BUTTON_Choice0"
#endif  ID_BUTTON_Choice0
#ifndef ID_TEXT_TextZ1
#define ID_TEXT_TextZ1		"ID_TEXT_TextZ1"
#endif  ID_TEXT_TextZ1
#ifndef ID_TEXT_PetName1
#define ID_TEXT_PetName1		"ID_TEXT_PetName1"
#endif  ID_TEXT_PetName1
#ifndef ID_BUTTON_Choice1
#define ID_BUTTON_Choice1		"ID_BUTTON_Choice1"
#endif  ID_BUTTON_Choice1
#ifndef ID_TEXT_ConsumeMoney
#define ID_TEXT_ConsumeMoney		"ID_TEXT_ConsumeMoney"
#endif  ID_TEXT_ConsumeMoney
#ifndef ID_TEXT_LockedMoney
#define ID_TEXT_LockedMoney		"ID_TEXT_LockedMoney"
#endif  ID_TEXT_LockedMoney
#ifndef ID_TEXT_CurrentMoney
#define ID_TEXT_CurrentMoney		"ID_TEXT_CurrentMoney"
#endif  ID_TEXT_CurrentMoney
#ifndef ID_TEXT_NowGenGu
#define ID_TEXT_NowGenGu "ID_TEXT_NowGenGu"
#endif ID_TEXT_NowGenGu

class CUI_ID_FRAME_SuAnimalUp:public CUIBase
{
	// Member
private:	

	 ControlFrame*	m_pID_FRAME_PetUp;
	 ControlButton*	m_pID_BUTTON_HELP;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlText*	m_pID_TEXT_TitleTop;
	 ControlPicture*	m_pID_PICTURE_Motherboard;
	 ControlText*	m_pID_TEXT_PetNameTitle;
	 ControlList*	m_pID_LIST_PetName;
	 ControlButton*	m_pID_BUTTON_Sure;
	 ControlButton*	m_pID_BUTTON_Examine;
	 ControlText*	m_pID_TEXT_Explain;
	 ControlText*	m_pID_TEXT_NowApperception;
	 ControlText*	m_pID_TEXT_Probability;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlText*	m_pID_TEXT_Explain0;
	 ControlText*	m_pID_TEXT_TextZ0;
	 ControlText*	m_pID_TEXT_PetName0;
	 ControlButton*	m_pID_BUTTON_Choice0;
	 ControlText*	m_pID_TEXT_TextZ1;
	 ControlText*	m_pID_TEXT_PetName1;
	 ControlButton*	m_pID_BUTTON_Choice1;
	 ControlText*	m_pID_TEXT_ConsumeMoney;
	 ControlText*	m_pID_TEXT_LockedMoney;
	 ControlText*	m_pID_TEXT_CurrentMoney;
	ControlText*    m_pID_TEXT_NowGenGu;
public:	
	// Frame
	CUI_ID_FRAME_SuAnimalUp();
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	void ID_LIST_PetNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_SureOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ExamineOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Choice0OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Choice1OnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
private:	
	struct PetUp_Struct
	{
		PetUp_Struct() { memset(this,0,sizeof(PetUp_Struct));}
		uint8 nSrcPetIndex; // 材料宠物索引
		int64 nSrcPetGuid ; // 材料宠物GUID
		uint8 nDstPetIndex; // 目标宠物索引
		int64 nDstPetGuid ; // 目标宠物GUID
		int	  petType;			//目标宠物类型  材料宠物必须要和目标宠物的类型一致才可以当作材料宠物
		int	  m_GenGu;	   //所选择宠物的根骨
		int     m_srcGenGu; //材料宠物的根骨
	};
	PetUp_Struct  m_UpData;
	int m_nLastHeight;
	bool m_bNeedRefresh;

	int64    m_CurrentSelectPet;  //当前选择的宠物
public:
	void RefreshMoney();  //刷钱
	void RefreshMonsy(SPetItem &mount);  //根据当前选择的被提升的宠物刷新金钱。动态改变金钱数量
	void Refresh_Help(bool _is);

	void SetNeed_Refresh(bool _need) {m_bNeedRefresh = _need;}
	//void Refresh_Help(bool _is);
	void Refresh(bool bNeed) {SetNeed_Refresh(true); }
	void RefreshProperty();
	void RefreshPetList();
	void RefreshByMoneyChange();//从uibase中继承过来的虚函数，用来当金钱改变时刷新当前金钱数目
};
extern CUI_ID_FRAME_SuAnimalUp s_CUI_ID_FRAME_SuAnimalUp;

