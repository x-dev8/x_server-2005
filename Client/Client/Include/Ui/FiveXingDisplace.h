/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\FiveXingDisplace.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "FiveXingBase.h"

#ifndef ID_FRAME_FiveXingDisplace
#define ID_FRAME_FiveXingDisplace		"ID_FRAME_FiveXingDisplace"
#endif  ID_FRAME_FiveXingDisplace
#ifndef ID_PICTURE_MiddleTitle
#define ID_PICTURE_MiddleTitle		"ID_PICTURE_MiddleTitle"
#endif  ID_PICTURE_MiddleTitle
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_help
#define ID_BUTTON_help		"ID_BUTTON_help"
#endif  ID_BUTTON_help
#ifndef ID_LISTIMG_Armour
#define ID_LISTIMG_Armour		"ID_LISTIMG_Armour"
#endif  ID_LISTIMG_Armour
#ifndef ID_TEXT_UseMoneyZ
#define ID_TEXT_UseMoneyZ		"ID_TEXT_UseMoneyZ"
#endif  ID_TEXT_UseMoneyZ
#ifndef ID_TEXT_UseMoney
#define ID_TEXT_UseMoney		"ID_TEXT_UseMoney"
#endif  ID_TEXT_UseMoney
#ifndef ID_PICTURE_LeftTitle
#define ID_PICTURE_LeftTitle		"ID_PICTURE_LeftTitle"
#endif  ID_PICTURE_LeftTitle
#ifndef ID_PICTURE_TitleWord
#define ID_PICTURE_TitleWord		"ID_PICTURE_TitleWord"
#endif  ID_PICTURE_TitleWord
#ifndef ID_LISTIMG_Material
#define ID_LISTIMG_Material		"ID_LISTIMG_Material"
#endif  ID_LISTIMG_Material
#ifndef ID_LISTIMG_Material2
#define ID_LISTIMG_Material2		"ID_LISTIMG_Material2"
#endif  ID_LISTIMG_Material2
#ifndef ID_PICTURE_Title
#define ID_PICTURE_Title		"ID_PICTURE_Title"
#endif  ID_PICTURE_Title
#ifndef ID_LISTIMG_Aim
#define ID_LISTIMG_Aim		"ID_LISTIMG_Aim"
#endif  ID_LISTIMG_Aim
#ifndef ID_PICTURE_Arrow
#define ID_PICTURE_Arrow		"ID_PICTURE_Arrow"
#endif  ID_PICTURE_Arrow
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_PICTURE_Jin
#define ID_PICTURE_Jin		"ID_PICTURE_Jin"
#endif  ID_PICTURE_Jin
#ifndef ID_PICTURE_Tu
#define ID_PICTURE_Tu		"ID_PICTURE_Tu"
#endif  ID_PICTURE_Tu
#ifndef ID_PICTURE_Huo
#define ID_PICTURE_Huo		"ID_PICTURE_Huo"
#endif  ID_PICTURE_Huo
#ifndef ID_PICTURE_Mu
#define ID_PICTURE_Mu		"ID_PICTURE_Mu"
#endif  ID_PICTURE_Mu
#ifndef ID_PICTURE_Shui
#define ID_PICTURE_Shui		"ID_PICTURE_Shui"
#endif  ID_PICTURE_Shui
#ifndef ID_PICTURE_Flash
#define ID_PICTURE_Flash		"ID_PICTURE_Flash"
#endif  ID_PICTURE_Flash
#ifndef ID_TEXT_Rate
#define ID_TEXT_Rate		"ID_TEXT_Rate"
#endif  ID_TEXT_Rate

#include "UiBase.h"
class CUI_ID_FRAME_FiveXingDisplace : public CFiveXingBase ,public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_FiveXingDisplace();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
// 	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
// 	bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Material2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_AimOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_AimOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_AimOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_AimOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

public:
    virtual void Init(); 
    virtual void Clear();

    void SetMoneyUI(DWORD dwMoney);  //设置钱币
    bool IsFiveXingDisplace(ControlObject *pSender);   //是否为五行转移界面
    void ShowResult();

    void RefreshOkButton();
    void ClearAll();

    bool IsFiveXingStone(ControlIconDrag::S_ListImg *pItem,char *pszError = NULL,int nLen = 0);
    bool IsFiveXingLuckStone(ControlIconDrag::S_ListImg *pItem);  //是否为五行祝福石

    bool IsMoneyEnough(DWORD dwMoney);
    void UpdateProb(int nCount);  //更新概率

    bool SetMaterial0(ControlObject* pSender, ControlIconDrag::S_ListImg *pItemDrag);
    bool SetMaterial1(ControlObject* pSender, ControlIconDrag::S_ListImg *pItemDrag);
    static void OnVisibleChange( ControlObject* pUIObject ); 

    bool IsSamePart(ControlIconDrag::S_ListImg *pItemSrc,ControlIconDrag::S_ListImg *pItemDrag);  //是否部位相同

	ControlFrame* GetFrame() {return m_pID_FRAME_FiveXingDisplace;}

private:
    ControlGroup m_ControlGroup;     //组  
private:
    ControlFrame*	m_pID_FRAME_FiveXingDisplace;
    ControlPicture*	m_pID_PICTURE_MiddleTitle;
//     ControlButton*	m_pID_BUTTON_CLOSE;
//     ControlButton*	m_pID_BUTTON_help;
    ControlListImage*	m_pID_LISTIMG_Armour;
    ControlText*	m_pID_TEXT_UseMoneyZ;
    ControlText*	m_pID_TEXT_UseMoney;
    ControlPicture*	m_pID_PICTURE_LeftTitle;
    //ControlPicture*	m_pID_PICTURE_TitleWord;
    ControlListImage*	m_pID_LISTIMG_Material;
    ControlListImage*	m_pID_LISTIMG_Material2;
    ControlPicture*	m_pID_PICTURE_Title;
    ControlListImage*	m_pID_LISTIMG_Aim;
    ControlPicture*	m_pID_PICTURE_Arrow;
    ControlButton*	m_pID_BUTTON_Ok;
    ControlButton*	m_pID_BUTTON_Cancel;
    ControlPicture*	m_pID_PICTURE_Jin;
    ControlPicture*	m_pID_PICTURE_Tu;
    ControlPicture*	m_pID_PICTURE_Huo;
    ControlPicture*	m_pID_PICTURE_Mu;
    ControlPicture*	m_pID_PICTURE_Shui;
    ControlPicture*	m_pID_PICTURE_Flash;
    ControlText*	m_pID_TEXT_Rate;
};
extern CUI_ID_FRAME_FiveXingDisplace s_CUI_ID_FRAME_FiveXingDisplace;
