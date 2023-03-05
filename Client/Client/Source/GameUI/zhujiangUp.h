/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_03.01\Data\Ui\zhujiangUp.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "ItemEnableChangeSysBase.h"
#include "GlobalDef.h"

#ifndef ID_FRAME_ZhuJianUp
#define ID_FRAME_ZhuJianUp		"ID_FRAME_ZhuJianUp"
#endif  ID_FRAME_ZhuJianUp
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_TEXT_Money
#define ID_TEXT_Money		"ID_TEXT_Money"
#endif  ID_TEXT_Money
#ifndef ID_LISTIMG_ZJ6
#define ID_LISTIMG_ZJ6		"ID_LISTIMG_ZJ6"
#endif  ID_LISTIMG_ZJ6
#ifndef ID_LISTIMG_Material
#define ID_LISTIMG_Material		"ID_LISTIMG_Material"
#endif  ID_LISTIMG_Material
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok
#ifndef ID_LISTIMG_ZJ1
#define ID_LISTIMG_ZJ1		"ID_LISTIMG_ZJ1"
#endif  ID_LISTIMG_ZJ1
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_LISTIMG_ZJ2
#define ID_LISTIMG_ZJ2		"ID_LISTIMG_ZJ2"
#endif  ID_LISTIMG_ZJ2
#ifndef ID_LISTIMG_ZJ3
#define ID_LISTIMG_ZJ3		"ID_LISTIMG_ZJ3"
#endif  ID_LISTIMG_ZJ3
#ifndef ID_LISTIMG_ZJ4
#define ID_LISTIMG_ZJ4		"ID_LISTIMG_ZJ4"
#endif  ID_LISTIMG_ZJ4
#ifndef ID_LISTIMG_ZJ5
#define ID_LISTIMG_ZJ5		"ID_LISTIMG_ZJ5"
#endif  ID_LISTIMG_ZJ5
#ifndef ID_TEXT_SuccessRatio
#define ID_TEXT_SuccessRatio		"ID_TEXT_SuccessRatio"
#endif  ID_TEXT_SuccessRatio
#ifndef ID_TEXT_Success
#define ID_TEXT_Success		"ID_TEXT_Success"
#endif  ID_TEXT_Success
#ifndef ID_TEXT_Fail
#define ID_TEXT_Fail		"ID_TEXT_Fail"
#endif  ID_TEXT_Fail
#ifndef ID_TEXT_Tu1_Name
#define ID_TEXT_Tu1_Name		"ID_TEXT_Tu1_Name"
#endif  ID_TEXT_Tu1_Name
#ifndef ID_TEXT_Tu2_Name
#define ID_TEXT_Tu2_Name		"ID_TEXT_Tu2_Name"
#endif  ID_TEXT_Tu2_Name
#ifndef ID_TEXT_Tip
#define ID_TEXT_Tip		"ID_TEXT_Tip"
#endif  ID_TEXT_Tip
#ifndef ID_TEXT_MaterialName
#define ID_TEXT_MaterialName		"ID_TEXT_MaterialName"
#endif  ID_TEXT_MaterialName

const int nMaxZhuJiangNum = 5;

class CUI_ID_FRAME_ZhuJianUp:public CUIBase, CItemEnableChangeSysBase
{
	// Member
public:	
	enum EffectStatus
	{
		EffectStatus_No,
		EffectStatus_Fail,
		EffectStatus_Success
	};

	 CUI_ID_FRAME_ZhuJianUp();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_ZJ6OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ZJ6OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ6OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ6OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_ZJ1OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ZJ1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_ZJ2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ZJ2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ3OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ZJ3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ4OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ZJ4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ5OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ZJ5OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ5OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ZJ5OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	virtual bool IsPackItemBeUsing( __int64 nGuid );

	ControlFrame* GetFrame(){return m_pID_FRAME_ZhuJianUp;}
	void SendZhuJiangUpMsg();
	static void OnVisibleChange( ControlObject* pUIObject );

	void SetEffectStatus(EffectStatus status){m_status = status;}
	void SetBeginTime(DWORD time){dwBeginTime = time;}

	void RefreshSuccessRatio();
	void RefreshOkEnable();
	void RefreshMoney();
	void ShowOutputImg();
	void ClearGem(int nIndex,ControlListImage *pTargetImg);
	void ClearMaterial(ControlListImage *pTargetImg);
	void ClearGems();
	bool OnGemDragOn(int nIndex,ControlListImage *pTargetImg,ControlIconDrag::S_ListImg* pItemDrag,ControlObject* pSender,short stEquipBagType = BT_NormalItemBag);
	bool OnGemMaterialDragOn(ControlListImage *pTargetImg,ControlIconDrag::S_ListImg* pItemDrag,ControlObject* pSender,short stEquipBagType = BT_NormalItemBag);
	void OnDragOn(ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc);

	void UpdateAll();

	void ShowItemName(ControlText* pText, ControlIconDrag::S_ListImg* pItemDrag);
	void ShowMaterialName(ControlIconDrag::S_ListImg* pItemDrag);

private:
	ControlFrame*	m_pID_FRAME_ZhuJianUp;
	ControlButton*	m_pID_BUTTON_CLOSE;
	ControlText*	m_pID_TEXT_Money;
	ControlListImage*	m_pID_LISTIMG_ZJ6;
	ControlListImage*	m_pID_LISTIMG_Material;
	ControlButton*	m_pID_BUTTON_Cancel;
	ControlButton*	m_pID_BUTTON_Ok;
	ControlListImage*	m_pID_LISTIMG_ZJ1;
	ControlButton*	m_pID_BUTTON_HELP;
	ControlListImage*	m_pID_LISTIMG_ZJ2;
	ControlListImage*	m_pID_LISTIMG_ZJ3;
	ControlListImage*	m_pID_LISTIMG_ZJ4;
	ControlListImage*	m_pID_LISTIMG_ZJ5;
	ControlText*	m_pID_TEXT_SuccessRatio;
	ControlText*	m_pID_TEXT_Success;
	ControlText*	m_pID_TEXT_Fail;
	ControlText*	m_pID_TEXT_Tu1_Name;
	ControlText*	m_pID_TEXT_Tu2_Name;
	ControlText*	m_pID_TEXT_Tip;
	ControlText*	m_pID_TEXT_MaterialName;

	struct sGem
	{
		short			shBagType;   //主将图背包类型
		short			shIndex;	 // 主将图Index
		__int64			n64Guid;	 // 主将图Guid
		unsigned short	ushItemId;	 //itemid
		uint8			unCount;	 //个数

		sGem()
		{
			shBagType = -1;
			shIndex = -1;
			n64Guid = 0;
			ushItemId = 0;
			unCount = 0;
		}
	};
	sGem     m_Gems[nMaxZhuJiangNum];
	sGem     m_GemMaterial;

	EffectStatus m_status;
	DWORD dwBeginTime;

	ControlObject* m_lastpSender;
	ControlObject* m_lastpSender2;
	short m_EquipBagType;
	short m_EquipBagIndex;
	short m_MaterialBagType;
	short m_MaterialIndex;
};

extern CUI_ID_FRAME_ZhuJianUp s_CUI_ID_FRAME_ZhuJianUp;
