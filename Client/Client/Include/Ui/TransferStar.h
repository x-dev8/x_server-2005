/********************************************************************
Created by UIEditor.exe
FileName: E:\新建文件夹\3Guo_Client_02.05\Data\Ui\TransferStar.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "ItemEnableChangeSysBase.h"

#ifndef ID_FRAME_TransferStar
#define ID_FRAME_TransferStar		"ID_FRAME_TransferStar"
#endif  ID_FRAME_TransferStar
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_TEXT_Money
#define ID_TEXT_Money		"ID_TEXT_Money"
#endif  ID_TEXT_Money
#ifndef ID_LISTIMG_Material
#define ID_LISTIMG_Material		"ID_LISTIMG_Material"
#endif  ID_LISTIMG_Material
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok
#ifndef ID_TEXT_Tip2
#define ID_TEXT_Tip2		"ID_TEXT_Tip2"
#endif  ID_TEXT_Tip2
#ifndef ID_TEXT_Tip1
#define ID_TEXT_Tip1		"ID_TEXT_Tip1"
#endif  ID_TEXT_Tip1
#ifndef ID_LISTIMG_SourceEquip
#define ID_LISTIMG_SourceEquip		"ID_LISTIMG_SourceEquip"
#endif  ID_LISTIMG_SourceEquip
#ifndef ID_LISTIMG_TargetEquip
#define ID_LISTIMG_TargetEquip		"ID_LISTIMG_TargetEquip"
#endif  ID_LISTIMG_TargetEquip
#ifndef ID_TEXT_Success
#define ID_TEXT_Success		"ID_TEXT_Success"
#endif  ID_TEXT_Success
#ifndef ID_TEXT_Fail
#define ID_TEXT_Fail		"ID_TEXT_Fail"
#endif  ID_TEXT_Fail
#ifndef ID_TEXT_SourceName
#define ID_TEXT_SourceName		"ID_TEXT_SourceName"
#endif  ID_TEXT_SourceName
#ifndef ID_TEXT_TargetName
#define ID_TEXT_TargetName		"ID_TEXT_TargetName"
#endif  ID_TEXT_TargetName
#ifndef ID_TEXT_MaterialName
#define ID_TEXT_MaterialName		"ID_TEXT_MaterialName"
#endif  ID_TEXT_MaterialName

class CUI_ID_FRAME_TransferStar:public CUIBase, CItemEnableChangeSysBase
{
	// Member
	enum ImgTpye
	{
		IT_Source,
		IT_Target,
		IT_Material,
	};
	
public:	
	enum EffectStatus
	{
		EffectStatus_No,
		EffectStatus_Fail,
		EffectStatus_Success
	};

	CUI_ID_FRAME_TransferStar();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_SourceEquipOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_SourceEquipOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SourceEquipOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SourceEquipOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_TargetEquipOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_TargetEquipOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_TargetEquipOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_TargetEquipOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	virtual bool IsPackItemBeUsing( __int64 nGuid );

	void TipsVisable();
	ControlFrame* GetFrame(){return m_pID_FRAME_TransferStar;}
	static void OnVisibleChange( ControlObject* pUIObject );

	void OnDragOn(ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc);
	void ClearImg(ImgTpye itype,ControlListImage *pTargetImg);
	bool IsSamePart(ControlIconDrag::S_ListImg * pSourceImg,ControlIconDrag::S_ListImg * pTargetImg);
	bool IsOverLevel(ControlIconDrag::S_ListImg * pSourceImg,ControlIconDrag::S_ListImg * pTargetImg);
	bool IsOverStarLevel(ControlIconDrag::S_ListImg * pSourceImg,ControlIconDrag::S_ListImg * pTargetImg);

	void RefreshOkButton();
	void RefreshMoney();
	void ClearAll();
	void UpdataAll();

	void SetEffectStatus(EffectStatus status){m_status = status;}
	void SetBeginTime(DWORD time){dwBeginTime = time;}
	void SetAckMsg(bool bAck){m_bAckMsg = bAck;}

	void ShowEquipName(ControlText* pText, ControlIconDrag::S_ListImg* pItemDrag);
	void ShowMaterialName(ControlIconDrag::S_ListImg* pItemDrag);

	void SendMsg();

private:
	ControlFrame*	m_pID_FRAME_TransferStar;
	ControlButton*	m_pID_BUTTON_CLOSE;
	ControlButton*	m_pID_BUTTON_HELP;
	ControlText*	m_pID_TEXT_Money;
	ControlListImage*	m_pID_LISTIMG_Material;
	ControlButton*	m_pID_BUTTON_Cancel;
	ControlButton*	m_pID_BUTTON_Ok;
	ControlText*	m_pID_TEXT_Tip2;
	ControlText*	m_pID_TEXT_Tip1;
	ControlListImage*	m_pID_LISTIMG_SourceEquip;
	ControlListImage*	m_pID_LISTIMG_TargetEquip;
	ControlText*	m_pID_TEXT_Success;
	ControlText*	m_pID_TEXT_Fail;
	ControlText*	m_pID_TEXT_SourceName;
	ControlText*	m_pID_TEXT_TargetName;
	ControlText*	m_pID_TEXT_MaterialName;

	struct SMaterials
	{
		uint8 nItemBagType  ;
		int16 nItemIndex    ;
		int64 nItemGuid     ;

		SMaterials()
		{
			nItemBagType = 0;
			nItemIndex = -1;
			nItemGuid = 0;
		}
	};

	SMaterials m_targetEquip;
	SMaterials m_sourceEquip;
	SMaterials m_material;

	EffectStatus m_status;
	DWORD dwBeginTime;

	bool m_bAckMsg;

	ControlObject* m_SourceSender;
	ControlObject* m_TargetSender;
	ControlObject* m_MaterialSender;

	bool m_bSourceBound;
	bool m_bTargetBound;
};
extern CUI_ID_FRAME_TransferStar s_CUI_ID_FRAME_TransferStar;