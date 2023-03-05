#pragma once
#include "MeUi/MeUi.h"
#include "me3d/Vector.h"
#include "Ui/UIBase.h"
#include "ItemEnableChangeSysBase.h"
#include "GlobalDef.h"

#ifndef ID_FRAME_GemUp
#define ID_FRAME_GemUp		"ID_FRAME_GemUp"
#endif  ID_FRAME_GemUp
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_TEXT_Money
#define ID_TEXT_Money		"ID_TEXT_Money"
#endif  ID_TEXT_Money
#ifndef ID_LISTIMG_Gem6
#define ID_LISTIMG_Gem6		"ID_LISTIMG_Gem6"
#endif  ID_LISTIMG_Gem6
#ifndef ID_LISTIMG_Material
#define ID_LISTIMG_Material		"ID_LISTIMG_Material"
#endif  ID_LISTIMG_Material
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok
#ifndef ID_TEXT_Tip
#define ID_TEXT_Tip		"ID_TEXT_Tip"
#endif  ID_TEXT_Tip
#ifndef ID_PICTURE_StarEffect
#define ID_PICTURE_StarEffect		"ID_PICTURE_StarEffect"
#endif  ID_PICTURE_StarEffect
#ifndef ID_TEXT_TipAllDone
#define ID_TEXT_TipAllDone		"ID_TEXT_TipAllDone"
#endif  ID_TEXT_TipAllDone
#ifndef ID_PICTURE_Begin
#define ID_PICTURE_Begin		"ID_PICTURE_Begin"
#endif  ID_PICTURE_Begin
#ifndef ID_LISTIMG_Gem1
#define ID_LISTIMG_Gem1		"ID_LISTIMG_Gem1"
#endif  ID_LISTIMG_Gem1
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_LISTIMG_Gem2
#define ID_LISTIMG_Gem2		"ID_LISTIMG_Gem2"
#endif  ID_LISTIMG_Gem2
#ifndef ID_LISTIMG_Gem3
#define ID_LISTIMG_Gem3		"ID_LISTIMG_Gem3"
#endif  ID_LISTIMG_Gem3
#ifndef ID_LISTIMG_Gem4
#define ID_LISTIMG_Gem4		"ID_LISTIMG_Gem4"
#endif  ID_LISTIMG_Gem4
#ifndef ID_LISTIMG_Gem5
#define ID_LISTIMG_Gem5		"ID_LISTIMG_Gem5"
#endif  ID_LISTIMG_Gem5
#ifndef ID_TEXT_SuccessRatio
#define ID_TEXT_SuccessRatio		"ID_TEXT_SuccessRatio"
#endif  ID_TEXT_SuccessRatio
#ifndef ID_TEXT_TipFalseRecipe
#define ID_TEXT_TipFalseRecipe		"ID_TEXT_TipFalseRecipe"
#endif	ID_TEXT_TipFalseRecipe
#ifndef ID_TEXT_Success
#define ID_TEXT_Success		"ID_TEXT_Success"
#endif  ID_TEXT_Success
#ifndef ID_TEXT_Fail
#define ID_TEXT_Fail		"ID_TEXT_Fail"
#endif  ID_TEXT_Fail
#ifndef ID_CHECKBOX_X3
#define ID_CHECKBOX_X3		"ID_CHECKBOX_X3"
#endif  ID_CHECKBOX_X3
#ifndef ID_CHECKBOX_X4
#define ID_CHECKBOX_X4		"ID_CHECKBOX_X4"
#endif  ID_CHECKBOX_X4
#ifndef ID_CHECKBOX_X5
#define ID_CHECKBOX_X5		"ID_CHECKBOX_X5"
#endif  ID_CHECKBOX_X5
#ifndef ID_TEXT_Gem1_Name
#define ID_TEXT_Gem1_Name		"ID_TEXT_Gem1_Name"
#endif  ID_TEXT_Gem1_Name
#ifndef ID_TEXT_Gem2_Name
#define ID_TEXT_Gem2_Name		"ID_TEXT_Gem2_Name"
#endif  ID_TEXT_Gem2_Name
#ifndef ID_TEXT_MaterialName
#define ID_TEXT_MaterialName		"ID_TEXT_MaterialName"
#endif  ID_TEXT_MaterialName

const int nMaxGemNum = 5;

class CUI_ID_FRAME_GemUp :public CUIBase, CItemEnableChangeSysBase
{
	// Member
public:	
	enum EffectStatus
	{
		EffectStatus_No,
		EffectStatus_Fail,
		EffectStatus_Success
	};

	 CUI_ID_FRAME_GemUp();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_Gem6OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Gem6OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Gem6OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Gem6OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_Gem1OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Gem1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Gem1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Gem1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_Gem2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Gem2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Gem2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Gem2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Gem3OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Gem3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Gem3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Gem3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Gem4OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Gem4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Gem4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Gem4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Gem5OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Gem5OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Gem5OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Gem5OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	void ID_CHECKBOX_X3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_X4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_X5OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

    virtual bool IsPackItemBeUsing( __int64 nGuid );

	void SetEffectStatus(EffectStatus status){m_status = status;}
	void SetBeginTime(DWORD time){dwBeginTime = time;}

	ControlFrame* GetFrame(){return m_pID_FRAME_GemUp;}
private:
	ControlFrame*	m_pID_FRAME_GemUp;
	ControlButton*	m_pID_BUTTON_CLOSE;
	ControlText*	m_pID_TEXT_Money;
	ControlListImage*	m_pID_LISTIMG_Gem6;
	ControlListImage*	m_pID_LISTIMG_Material;
	ControlButton*	m_pID_BUTTON_Cancel;
	ControlButton*	m_pID_BUTTON_Ok;
	ControlText*	m_pID_TEXT_Tip;
	ControlPicture*	m_pID_PICTURE_StarEffect;
	ControlText*	m_pID_TEXT_TipAllDone;
	ControlPicture*	m_pID_PICTURE_Begin;
	ControlListImage*	m_pID_LISTIMG_Gem1;
	ControlButton*	m_pID_BUTTON_HELP;
	ControlListImage*	m_pID_LISTIMG_Gem2;
	ControlListImage*	m_pID_LISTIMG_Gem3;
	ControlListImage*	m_pID_LISTIMG_Gem4;
	ControlListImage*	m_pID_LISTIMG_Gem5;
	ControlText*	m_pID_TEXT_SuccessRatio;
	ControlText*	m_pID_TEXT_TipFalseRecipe;
	ControlText*	m_pID_TEXT_Success;
	ControlText*	m_pID_TEXT_Fail;
	ControlCheckBox*	m_pID_CHECKBOX_X3;
	ControlCheckBox*	m_pID_CHECKBOX_X4;
	ControlCheckBox*	m_pID_CHECKBOX_X5;
	ControlText*	m_pID_TEXT_Gem1_Name;
	ControlText*	m_pID_TEXT_Gem2_Name;
	ControlText*	m_pID_TEXT_MaterialName;

public:
	void SetVisiblePosition( const Vector& vPos ){ m_vVisiblePos = vPos; }
    bool IsOverDistance(const Vector& vCurPos);   //是否需要关闭界面
	void ProcessCloseUI();
	void ClearGems();
	bool OnGemDragOn(int nIndex,ControlListImage *pTargetImg,ControlIconDrag::S_ListImg* pItemDrag,ControlObject* pSender,short stEquipBagType = BT_NormalItemBag);
	bool OnGemMaterialDragOn(ControlListImage *pTargetImg,ControlIconDrag::S_ListImg* pItemDrag,ControlObject* pSender,short stEquipBagType = BT_NormalItemBag);
	void ClearGem(int nIndex,ControlListImage *pTargetImg);
	void ClearMaterial(ControlListImage *pTargetImg);
	void SendGemUpMsg(bool CheckBounded = true);
	static void	OnVisibleChange( ControlObject* pUIObject ); 
	void OnDragOn(ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc);
	void RefreshOkEnable();
	void RefreshTargetGem(unsigned short usItemID);
	int  GetGemIdByGems();
	void SetIsPocket(bool bValue){m_bIsPocket = bValue;}
	bool GetIsPocket(){return m_bIsPocket;}
	void RefreshMoney(unsigned int nmoney);

	void ShowGemName(ControlText* pText, ControlIconDrag::S_ListImg* pItemDrag);
	void ShowMaterialName(ControlIconDrag::S_ListImg* pItemDrag);

	void UpdateAll();

	void SetSelectCheck();
private:
	void RefreshSuccessRatio(void);

private:
	Vector			m_vVisiblePos;
	struct sGem
	{
		short			shBagType;   //宝石背包类型
		short			shIndex;	 // 宝石Index
		__int64			n64Guid;	 // 宝石Guid
		short           nCount;      //宝石数量
		sGem()
		{
			shBagType = -1;
			shIndex = -1;
			n64Guid = 0;
			nCount = 0;
		}
	};
	sGem     m_Gems[nMaxGemNum];
	sGem     m_GemMaterial;
	bool	 m_bIsPocket;
	uint8	 m_SelectGemNum;
	EffectStatus m_status;
	DWORD	 dwBeginTime;
	unsigned int m_money;

	ControlObject* m_lastpSender;
	ControlObject* m_lastpSender2;
	short m_EquipBagType;
	short m_EquipBagIndex;
	short m_MaterialBagType;
	short m_MaterialIndex;
};
extern CUI_ID_FRAME_GemUp s_CUI_ID_FRAME_GemUp;
