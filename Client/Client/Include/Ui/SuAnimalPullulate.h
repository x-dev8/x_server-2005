/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Turbo\MEUI\3.14-3.19\宠物界面\宠物提升悟性 鉴定成功率 右键菜单界面\SuAnimalPullulate.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "GlobalDef.h"
#include "PlayerAnimCtrl.h"
#include "UIBase.h"

#ifndef ID_FRAME_SuAnimalPullulate
#define ID_FRAME_SuAnimalPullulate		"ID_FRAME_SuAnimalPullulate"
#endif  ID_FRAME_SuAnimalPullulate
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_PICTURE_Yingxiang
#define ID_PICTURE_Yingxiang		"ID_PICTURE_Yingxiang"
#endif  ID_PICTURE_Yingxiang
#ifndef ID_BUTTON_Right
#define ID_BUTTON_Right		"ID_BUTTON_Right"
#endif  ID_BUTTON_Right
#ifndef ID_BUTTON_Left
#define ID_BUTTON_Left		"ID_BUTTON_Left"
#endif  ID_BUTTON_Left
#ifndef ID_BUTTON_Sure
#define ID_BUTTON_Sure		"ID_BUTTON_Sure"
#endif  ID_BUTTON_Sure
#ifndef ID_LISTIMG_PetIcon
#define ID_LISTIMG_PetIcon		"ID_LISTIMG_PetIcon"
#endif  ID_LISTIMG_PetIcon
#ifndef ID_TEXT_Generation
#define ID_TEXT_Generation		"ID_TEXT_Generation"
#endif  ID_TEXT_Generation
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_LIST_ShouLan
#define ID_LIST_ShouLan		"ID_LIST_ShouLan"
#endif  ID_LIST_ShouLan
#ifndef ID_LIST_War
#define ID_LIST_War		"ID_LIST_War"
#endif  ID_LIST_War
#ifndef ID_BUTTON_Select
#define ID_BUTTON_Select		"ID_BUTTON_Select"
#endif  ID_BUTTON_Select
#ifndef ID_BUTTON_Look
#define ID_BUTTON_Look		"ID_BUTTON_Look"
#endif  ID_BUTTON_Look
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_TEXT_Cost
#define ID_TEXT_Cost		"ID_TEXT_Cost"
#endif  ID_TEXT_Cost
#ifndef ID_TEXT_Money1
#define ID_TEXT_Money1		"ID_TEXT_Money1"
#endif  ID_TEXT_Money1
#ifndef ID_TEXT_Money2
#define ID_TEXT_Money2		"ID_TEXT_Money2"
#endif  ID_TEXT_Money2
#ifndef ID_TEXT_Info
#define ID_TEXT_Info		"ID_TEXT_Info"
#endif  ID_TEXT_Info

class CUI_ID_FRAME_SuAnimalPullulate:public CUIBase
{
	// Member
private:	

	 ControlFrame*	m_pID_FRAME_SuAnimalPullulate;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlPicture*	m_pID_PICTURE_Yingxiang;
	 ControlButton*	m_pID_BUTTON_Right;
	 ControlButton*	m_pID_BUTTON_Left;
	 ControlButton*	m_pID_BUTTON_Sure;
	 ControlListImage*	m_pID_LISTIMG_PetIcon;
	 ControlText*	m_pID_TEXT_Generation;
	 ControlButton*	m_pID_BUTTON_HELP;
	 ControlList*	m_pID_LIST_ShouLan;
	 ControlList*	m_pID_LIST_War;
	 ControlButton*	m_pID_BUTTON_Select;
	 ControlButton*	m_pID_BUTTON_Look;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlText*	m_pID_TEXT_Cost;
	 ControlText*	m_pID_TEXT_Money1;
	 ControlText*	m_pID_TEXT_Money2;
	 ControlText*	m_pID_TEXT_Info;

public:	
	// Frame
	CUI_ID_FRAME_SuAnimalPullulate();
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_RightOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_LeftOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SureOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_PetIconOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_PetIconOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetIconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_PetIconOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	void ID_LIST_ShouLanOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_WarOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_SelectOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_LookOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );

	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视

private:	
	bool m_bRotate;
	int	  m_nModelId; 
	CPlayer*			m_pPlayer;
	CPlayerAnim*        m_pPlayerAnim;
	float			m_fRotateZ;
public:
	void RenderMount( int nMountId, CPlayerAnim* pAnim, float fRotateZ, const RECT& rt );
	void ChangeModel(SPetItem &mount, CPlayerAnim* pAnim, int& iOldModelId );
	void RenderViewport();
	static bool UIPetPull_RightLBD(INT nX,INT nY);
	static bool UIPetPull_LeftLBD(INT nX,INT nY);
	void SetRotate(bool bRotate) {m_bRotate = bRotate;}
	void PetSelectChange(int nindex);
	bool ReadyOk();
	void Refresh_Help(bool _is);
	void RefreshItemInfo();
	void RefreshMoney();
	short GetCurrentMountIndex();
};
extern CUI_ID_FRAME_SuAnimalPullulate s_CUI_ID_FRAME_SuAnimalPullulate;
