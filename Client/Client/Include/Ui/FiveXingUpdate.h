/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\4xing\FiveXingUpdate.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "FiveXingBase.h"

#ifndef ID_FRAME_FiveXingUpdate
#define ID_FRAME_FiveXingUpdate		"ID_FRAME_FiveXingUpdate"
#endif  ID_FRAME_FiveXingUpdate
#ifndef ID_PICTURE_RightTitle
#define ID_PICTURE_RightTitle		"ID_PICTURE_RightTitle"
#endif  ID_PICTURE_RightTitle
#ifndef ID_PICTURE_MiddleTitle
#define ID_PICTURE_MiddleTitle		"ID_PICTURE_MiddleTitle"
#endif  ID_PICTURE_MiddleTitle
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_help
#define ID_BUTTON_help		"ID_BUTTON_help"
#endif  ID_BUTTON_help
#ifndef ID_PICTURE_ItemWall
#define ID_PICTURE_ItemWall		"ID_PICTURE_ItemWall"
#endif  ID_PICTURE_ItemWall
#ifndef ID_LISTIMG_Armour
#define ID_LISTIMG_Armour		"ID_LISTIMG_Armour"
#endif  ID_LISTIMG_Armour
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
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
#ifndef ID_PICTURE_Flash
#define ID_PICTURE_Flash		"ID_PICTURE_Flash"
#endif  ID_PICTURE_Flash
#ifndef ID_LISTIMG_Material
#define ID_LISTIMG_Material		"ID_LISTIMG_Material"
#endif  ID_LISTIMG_Material
#ifndef ID_LISTIMG_Material2
#define ID_LISTIMG_Material2		"ID_LISTIMG_Material2"
#endif  ID_LISTIMG_Material2
#ifndef ID_LISTIMG_Material3
#define ID_LISTIMG_Material3		"ID_LISTIMG_Material3"
#endif  ID_LISTIMG_Material3
#ifndef ID_PICTURE_ItemWall
#define ID_PICTURE_ItemWall		"ID_PICTURE_ItemWall"
#endif  ID_PICTURE_ItemWall
#ifndef ID_TEXT_Word
#define ID_TEXT_Word		"ID_TEXT_Word"
#endif  ID_TEXT_Word
#ifndef ID_BUTTON_Reset
#define ID_BUTTON_Reset		"ID_BUTTON_Reset"
#endif  ID_BUTTON_Reset
#ifndef ID_PICTURE_Flash
#define ID_PICTURE_Flash		"ID_PICTURE_Flash"
#endif  ID_PICTURE_Flash

#include "UiBase.h"
class CUI_ID_FRAME_FiveXingUpdate : public CFiveXingBase ,public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_FiveXingUpdate();
private:
	 ControlFrame*	m_pID_FRAME_FiveXingUpdate;
	 ControlPicture*	m_pID_PICTURE_RightTitle;
	 ControlPicture*	m_pID_PICTURE_MiddleTitle;
// 	 ControlButton*	m_pID_BUTTON_CLOSE;
// 	 ControlButton*	m_pID_BUTTON_help;
	 ControlPicture*	m_pID_PICTURE_ItemWall;
	 ControlListImage*	m_pID_LISTIMG_Armour;
	 ControlButton*	m_pID_BUTTON_Ok;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlText*	m_pID_TEXT_UseMoneyZ;
	 ControlText*	m_pID_TEXT_UseMoney;
	 ControlPicture*	m_pID_PICTURE_LeftTitle;
//	 ControlPicture*	m_pID_PICTURE_TitleWord;
	 ControlPicture*	m_pID_PICTURE_Flash;
	 ControlListImage*	m_pID_LISTIMG_Material;
	 ControlListImage*	m_pID_LISTIMG_Material2;
	 ControlListImage*	m_pID_LISTIMG_Material3;
     ControlText*	m_pID_TEXT_Word;
     ControlButton*	m_pID_BUTTON_Reset;

     ControlGroup       m_GroupMaterial;
public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
// 	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
// 	bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Material2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material3OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Material3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    bool ID_BUTTON_ResetOnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

	ControlFrame* GetFrame() {return m_pID_FRAME_FiveXingUpdate;}

    static void OnVisibleChange( ControlObject* pUIObject ); 

    virtual void Init();
    virtual void Clear();

    void SetMoneyUI(SCharItem *pItem);  //设置钱币

    void OnAck(MsgSuitLevelUpAck* pAck);

    void ShowResult();

    void RefreshOkButton();
    bool SetMaterial0(ControlObject* pSender, ControlIconDrag::S_ListImg *pItemDrag)
    {
        if(!pItemDrag)
            return false;

        char szError[256];
        memset(szError,0L,sizeof(szError));
        //是否为五行灵珠
        if(!IsFiveXingItem(pItemDrag->m_pkIconInfo->GetItemId(),ItemDefine::ITEMTYPE_CHECKUP,  \
            ItemDefine::SItemCheckUp::ECD_Elements,ItemDefine::SItemCheckUp::ECD_ElementsCheckUp,szError))
        {
            return false;
        }

        //保存数据
        if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pSender) )
            SetFiveXingItem(pItemDrag,BT_NormalItemBag,CFiveXingBase::enum_FiveXingElement);
        else if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag, pSender) )
            SetFiveXingItem(pItemDrag,BT_MaterialBag,CFiveXingBase::enum_FiveXingElement);

        //刷新道具
        UpdataItem(m_pID_LISTIMG_Material,pItemDrag);

//         bool bEnable = true;
//         for (int i = 0;i < enum_FiveXingMax;++i)    
//             if(m_FiveXing[i].m_nIndex == -1)
//                 bEnable = false;
// 
//         m_pID_BUTTON_Ok->SetEnable(bEnable);

        RefreshOkButton();

        return true;
    }

    bool SetMaterial1(ControlObject* pSender, ControlIconDrag::S_ListImg *pItemDrag)
    {
        if(!pItemDrag)
            return false;

        char szError[256];
        memset(szError,0L,sizeof(szError));
        //是否五行提纯材料
        if(!IsFiveXingItem(pItemDrag->m_pkIconInfo->GetItemId(),ItemDefine::ITEMTYPE_CHECKUP,  \
            ItemDefine::SItemCheckUp::ECD_Suit,ItemDefine::SItemCheckUp::ECD_ElementsSuitLevel,szError))
        {
            return false;
        }

        //保存数据
        if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pSender) )
            SetFiveXingItem(pItemDrag,BT_NormalItemBag,CFiveXingBase::enum_FiveXingMaterial);
        else if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag, pSender) )
            SetFiveXingItem(pItemDrag,BT_MaterialBag,CFiveXingBase::enum_FiveXingMaterial);

        //刷新材料
        UpdataItem(m_pID_LISTIMG_Material2,pItemDrag);

//         bool bEnable = true;
//         for (int i = 0;i < enum_FiveXingMax;++i)    
//             if(m_FiveXing[i].m_nIndex == -1)
//                 bEnable = false;
// 
//         m_pID_BUTTON_Ok->SetEnable(bEnable);
        RefreshOkButton();

        return true;
    }

    bool SetMaterial2(ControlObject* pSender, ControlIconDrag::S_ListImg *pItemDrag)
    {
        if(!pItemDrag)
            return false;

        //是否为功勋名望道具
        if(!IsFiveXingReputationItem(pItemDrag))
            return false;

        //保存数据
        if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pSender) )
            SetFiveXingItem(pItemDrag,BT_NormalItemBag,CFiveXingBase::enum_FiveXingExploit);
        else if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag, pSender) )
            SetFiveXingItem(pItemDrag,BT_MaterialBag,CFiveXingBase::enum_FiveXingExploit);

        //刷新材料
        UpdataItem(m_pID_LISTIMG_Material3,pItemDrag);

//         bool bEnable = true;
//         for (int i = 0;i < enum_FiveXingMax;++i)    
//             if(m_FiveXing[i].m_nIndex == -1)
//                 bEnable = false;
// 
//         m_pID_BUTTON_Ok->SetEnable(bEnable);
        RefreshOkButton();
        return true;
    }

};
extern CUI_ID_FRAME_FiveXingUpdate s_CUI_ID_FRAME_FiveXingUpdate;
