/********************************************************************
	Created by UIEditor.exe
	FileName: D:\My Documents\桌面\FiveXing.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "me3d/Vector.h"
#include "MeUi/Animation/SlideAnimation.h"
#include "PlayerRole.h"
#include "EquipUIHelper.h"
#include "ItemEnableChangeSysBase.h"

#ifndef ID_FRAME_FiveXing
#define ID_FRAME_FiveXing		"ID_FRAME_FiveXing"
#endif  ID_FRAME_FiveXing
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
#ifndef ID_TEXT_Explain
#define ID_TEXT_Explain		"ID_TEXT_Explain"
#endif  ID_TEXT_Explain
#ifndef ID_PICTURE_ItemWall2
#define ID_PICTURE_ItemWall2		"ID_PICTURE_ItemWall2"
#endif  ID_PICTURE_ItemWall2
#ifndef ID_LISTIMG_Material
#define ID_LISTIMG_Material		"ID_LISTIMG_Material"
#endif  ID_LISTIMG_Material
#ifndef ID_PICTURE_ExplainWall
#define ID_PICTURE_ExplainWall		"ID_PICTURE_ExplainWall"
#endif  ID_PICTURE_ExplainWall
#ifndef ID_PICTURE_Jin
#define ID_PICTURE_Jin		"ID_PICTURE_Jin"
#endif  ID_PICTURE_Jin
#ifndef ID_PICTURE_Mu
#define ID_PICTURE_Mu		"ID_PICTURE_Mu"
#endif  ID_PICTURE_Mu
#ifndef ID_PICTURE_Shui
#define ID_PICTURE_Shui		"ID_PICTURE_Shui"
#endif  ID_PICTURE_Shui
#ifndef ID_PICTURE_Huo
#define ID_PICTURE_Huo		"ID_PICTURE_Huo"
#endif  ID_PICTURE_Huo
#ifndef ID_PICTURE_Tu
#define ID_PICTURE_Tu		"ID_PICTURE_Tu"
#endif  ID_PICTURE_Tu
#ifndef ID_PICTURE_WordWall 
#define ID_PICTURE_WordWall 		"ID_PICTURE_WordWall "
#endif  ID_PICTURE_WordWall 
#ifndef ID_TEXT_String
#define ID_TEXT_String		"ID_TEXT_String"
#endif  ID_TEXT_String
#ifndef ID_BUTTON_Sure
#define ID_BUTTON_Sure		"ID_BUTTON_Sure"
#endif  ID_BUTTON_Sure
#ifndef ID_BUTTON_Return
#define ID_BUTTON_Return		"ID_BUTTON_Return"
#endif  ID_BUTTON_Return
#ifndef ID_PICTURE_TitleWordReturn
#define ID_PICTURE_TitleWordReturn		"ID_PICTURE_TitleWordReturn"
#endif  ID_PICTURE_TitleWordReturn
#ifndef ID_TEXT_ExplainReturn
#define ID_TEXT_ExplainReturn		"ID_TEXT_ExplainReturn"
#endif  ID_TEXT_ExplainReturn
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
#ifndef ID_PICTURE_FiveXing1
#define ID_PICTURE_FiveXing1		"ID_PICTURE_FiveXing1"
#endif  ID_PICTURE_FiveXing1
#ifndef ID_PICTURE_FiveXing2
#define ID_PICTURE_FiveXing2		"ID_PICTURE_FiveXing2"
#endif  ID_PICTURE_FiveXing2
#ifndef ID_PICTURE_ReturnFiveXing1
#define ID_PICTURE_ReturnFiveXing1		"ID_PICTURE_ReturnFiveXing1"
#endif  ID_PICTURE_ReturnFiveXing1
#ifndef ID_PICTURE_ReturnFiveXing2
#define ID_PICTURE_ReturnFiveXing2		"ID_PICTURE_ReturnFiveXing2"
#endif  ID_PICTURE_ReturnFiveXing2
#ifndef ID_PICTURE_FiveXing3
#define ID_PICTURE_FiveXing3		"ID_PICTURE_FiveXing3"
#endif  ID_PICTURE_FiveXing3
#ifndef ID_PICTURE_ReturnFiveXing3
#define ID_PICTURE_ReturnFiveXing3		"ID_PICTURE_ReturnFiveXing3"
#endif  ID_PICTURE_ReturnFiveXing3

#include "UiBase.h"

class CUI_ID_FRAME_FiveXing :public CUIBase, CItemEnableChangeSysBase
{
	// Member
public:	
	CUI_ID_FRAME_FiveXing();
private:
	ControlFrame*	m_pID_FRAME_FiveXing;
// 	ControlPicture*	m_pID_PICTURE_RightTitle;
// 	ControlPicture*	m_pID_PICTURE_MiddleTitle;
// 	ControlButton*	m_pID_BUTTON_CLOSE;
// 	ControlButton*	m_pID_BUTTON_help;
	ControlPicture*	m_pID_PICTURE_ItemWall;
	ControlListImage*	m_pID_LISTIMG_Armour;
	ControlButton*	m_pID_BUTTON_Ok;
	ControlButton*	m_pID_BUTTON_Cancel;
	ControlText*	m_pID_TEXT_UseMoneyZ;
	ControlText*	m_pID_TEXT_UseMoney;
	ControlPicture*	m_pID_PICTURE_LeftTitle;
// 	ControlPicture*	m_pID_PICTURE_TitleWord;
// 	ControlText*	m_pID_TEXT_Explain;
// 	ControlPicture*	m_pID_PICTURE_ItemWall2;
	ControlListImage*	m_pID_LISTIMG_Material;
	ControlPicture*	m_pID_PICTURE_ExplainWall;
	ControlPicture*	m_pID_PICTURE_Jin;
	ControlPicture*	m_pID_PICTURE_Mu;
	ControlPicture*	m_pID_PICTURE_Shui;
	ControlPicture*	m_pID_PICTURE_Huo;
	ControlPicture*	m_pID_PICTURE_Tu;
	ControlPicture*	m_pID_PICTURE_WordWall ;
	ControlText*	m_pID_TEXT_String;
	ControlButton*	m_pID_BUTTON_Sure;
	ControlButton*	m_pID_BUTTON_Return;
// 	ControlPicture*	m_pID_PICTURE_TitleWordReturn;
// 	ControlText*	m_pID_TEXT_ExplainReturn;
    ControlText*	m_pID_TEXT_Word;
    ControlButton*	m_pID_BUTTON_Reset;
    ControlPicture*	m_pID_PICTURE_Flash;
    ControlPicture*	m_pID_PICTURE_FiveXing1;
    ControlPicture*	m_pID_PICTURE_FiveXing2;
    ControlPicture*	m_pID_PICTURE_ReturnFiveXing1;
    ControlPicture*	m_pID_PICTURE_ReturnFiveXing2;
    ControlPicture*	m_pID_PICTURE_FiveXing3;
    ControlPicture*	m_pID_PICTURE_ReturnFiveXing3;

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
	bool ID_BUTTON_SureOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ResetOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ReturnOnButtonClick( ControlObject* pSender );
	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

public:
	void RefreshArmour();
	void RefreshMaterial();
	//void RefreshNeedMoney( SCharItem* pItem );	
    virtual bool IsPackItemBeUsing( __int64 nGuid );

	static void OnVisibleChange( ControlObject* pUIObject ); 

    void RefreshOkButton();

	void SetVisiblePosition( const Vector& vPos ){ m_vVisiblePos = vPos; }
	const Vector& GetVisiblePosition() const { return m_vVisiblePos; }

	void SetOperate( uint8 chOperate ){ m_chOperate = chOperate; }
	uint8 GetOperate() const { return m_chOperate; }

	void ShowSuccessUI( EItemElements eType );
	void SetAtomVisible( uint8 chOperate );
	void SetAck(bool bAck) { m_bAck = bAck; }
	void Set_elemType( int type ) { m_elemType = type; }


private:
	void ClearAllList();
	void RefreshAllBagEnable();
	void SetDirty( bool bDirty ){ m_bDirty = bDirty; }
	bool IsDirty(){ return m_bDirty; }

    bool SetMaterial0(ControlObject* pSender, ControlIconDrag::S_ListImg *pItemDrag)
    {
        if( !pItemDrag )
            return false;

        ID_LISTIMG_MaterialOnIconRButtonUp( 0, 0 );
        OnFrameRun();

        ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
        if( pItemCommon )
        {
            bool bElements = false;
            if (pItemCommon->ucItemType == ItemDefine::ITEMTYPE_CHECKUP)
            {
                ItemDefine::SItemCheckUp* pItemCheckUp = (ItemDefine::SItemCheckUp*)pItemCommon;
                if( pItemCheckUp->stCheckUpType == ItemDefine::SItemCheckUp::ECD_Elements )
                //如果为清除鉴定材料
                if (m_chOperate == MsgSuitElementCheckupReq::ECD_Clear)
                {
                    if(pItemCheckUp->stEffectType == ItemDefine::SItemCheckUp::ECD_ElementsClear)
                        bElements = true;
                }
                else if(m_chOperate == MsgSuitElementCheckupReq::ECD_Checkup)
                {
                    if(pItemCheckUp->stEffectType == ItemDefine::SItemCheckUp::ECD_ElementsCheckUp)
                        bElements = true;
                }
            }

            if( bElements )
            {
                ItemDefine::SCreateMaterial* pMaterial = ( ItemDefine::SCreateMaterial* )pItemCommon;

                // 		if( ( pMaterial->stMaterialType == ItemDefine::ematerial_identify && GetPlatingType() != ePlatingType_Identify ) 
                // 			|| ( pMaterial->stMaterialType == CItemDetail::ematerial_OpenLight && GetPlatingType() != ePlatingType_KaiGuang ) )
                // 			return false;

                m_pID_LISTIMG_Material->Clear();			
                m_pID_LISTIMG_Material->SetItem( pItemDrag, 0 );
                m_pID_LISTIMG_Material->GetItemByIndex( 0 )->m_pkIconInfo->Count() = 1;
                m_pID_LISTIMG_Material->GetItemByIndex( 0 )->m_eEnable = eIcon_Enable;		
                // type		
                int nMaterialIndex = 0;
                thePlayerRole.GetBagTypeByItemGUID( pItemDrag->m_pkIconInfo->GetOnlyId(), m_eMaterialBagType, &nMaterialIndex );
                m_nMaterialGuid = pItemDrag->m_pkIconInfo->GetOnlyId();
                //物品在包裹里的id
                m_stMaterialIndex = static_cast<short>(nMaterialIndex);
                m_bMaterialBagEnable = false;
                SetDirty( true );
                return true;
            }
        }	
        return false;
    }

	struct FiveEleUIHelper
	{
		ControlPicture* m_pSuccessPic;
		int m_nSuccessStringIndex;
	};

	FiveEleUIHelper m_FiveEleHelper[ ItemElements_End ];
	ControlGroup m_FiveGroupHelper;

	void InitHelperUi();
	void SendSuitCheckMsg();
	void RefreshNeedMoney( SCharItem* pItem );
	void SetMoneyUi( DWORD dwMoney );

	//void UpdateArmourInfo( SCharItem* pItem, ControlList* pList );
	void SetArmourInfo( ControlIconDrag::S_ListImg*  pListImg );
	//void ClearMoney();	

	short m_stNormalBagIndex;        // 目标物品Index
	bool  m_bNormalBagEnable;
	EBagType m_eMaterialBagType;
	short m_stMaterialIndex;		 // 道具Index
	bool  m_bMaterialBagEnable;
	__int64 m_nMaterialGuid;

	bool  m_bDirty;

	Vector m_vVisiblePos;			 // 界面打开时的人物位置,用来自动关闭时使用

	uint8 m_chOperate; // 洗/鉴

    CSlideAnimation m_slideAnim; //序列帧动画

	bool            m_bAck;  
	int             m_elemType;
};

extern CUI_ID_FRAME_FiveXing s_CUI_ID_FRAME_FiveXing;
