#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "ItemEnableChangeSysBase.h"
#include "ItemDetail.h"
#include "EquipEvolve.h"

#ifndef ID_FRAME_IdentifyQuality
#define ID_FRAME_IdentifyQuality		"ID_FRAME_IdentifyQuality"
#endif  ID_FRAME_IdentifyQuality
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_TEXT_Money
#define ID_TEXT_Money		"ID_TEXT_Money"
#endif  ID_TEXT_Money
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok

#ifndef ID_LISTIMG_Armour
#define ID_LISTIMG_Armour		"ID_LISTIMG_Armour"
#endif  ID_LISTIMG_Armour
#ifndef ID_LIST_Introduce
#define  ID_LIST_Introduce "ID_LIST_Introduce"
#endif ID_LIST_Introduce
#ifndef ID_TEXT_Effect
#define ID_TEXT_Effect			"ID_TEXT_Effect"
#endif	ID_TEXT_Effect
#ifndef ID_TEXT_Success
#define ID_TEXT_Success			"ID_TEXT_Success"
#endif	ID_TEXT_Success
#ifndef ID_TEXT_Fail
#define ID_TEXT_Fail			"ID_TEXT_Fail"
#endif	ID_TEXT_Fail
#ifndef ID_LISTIMG_Material
#define ID_LISTIMG_Material		"ID_LISTIMG_Material"
#endif  ID_LISTIMG_Material
#ifndef ID_TEXT_Material_NotEnougth
#define ID_TEXT_Material_NotEnougth		"ID_TEXT_Material_NotEnougth"
#endif  ID_TEXT_Material_NotEnougth
#ifndef ID_TEXT_EquipName
#define ID_TEXT_EquipName		"ID_TEXT_EquipName"
#endif  ID_TEXT_EquipName
#ifndef ID_TEXT_MaterialName
#define ID_TEXT_MaterialName		"ID_TEXT_MaterialName"
#endif  ID_TEXT_MaterialName

class CUI_ID_FRAME_IdentifyQuality :public CUIBase, CItemEnableChangeSysBase
{
	// Member
public:	
	 CUI_ID_FRAME_IdentifyQuality();
	 enum ePlatingType
	 {
		 ePlatingType_Identify, // 鉴定
		 ePlatingType_KaiGuang,   // 开光
		 ePlatingType_Count
	 };
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	
	void SetEffectStatus(EquipEvolveUI::EffectStatus status){m_status = status;}
	void SetBeginTime(DWORD time){dwBeginTime = time;}

	ControlIconDrag::S_ListImg* RetriveMaterialImg( short itemId ,int& nIndex);
	void ClearMaterialIcon();

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

public:
	// 会改变背包的 Enable 态的系统需要的接口       added by zhuomeng.hu		[12/30/2010]
	virtual bool IsPackItemBeUsing( __int64 nGuid );
private:
	ControlFrame*	m_pID_FRAME_IdentifyQuality;
	ControlButton*	m_pID_BUTTON_CLOSE;
	ControlButton*	m_pID_BUTTON_HELP;
	ControlText*	m_pID_TEXT_Money;
	ControlButton*	m_pID_BUTTON_Cancel;
	ControlButton*	m_pID_BUTTON_Ok;
	
	ControlListImage*	m_pID_LISTIMG_Armour;
	ControlList      *m_PID_LIST_Introduce;
	ControlText*	m_pID_TEXT_Effect;
	ControlText*	m_pID_TEXT_Success;
	ControlText*	m_pID_TEXT_Fail;
	ControlListImage*	m_pID_LISTIMG_Material;
	ControlText*	m_pID_TEXT_Material_NotEnougth;
	ControlText*	m_pID_TEXT_EquipName;
	ControlText*	m_pID_TEXT_MaterialName;

	DWORD dwBeginTime;
	EquipEvolveUI::EffectStatus m_status;
	bool m_bSendMsg;
public:
	void Clear();
	void SetVisiblePosition(const Vector &vPos);  //设置开启界面玩家坐标
	bool IsOverDistance(const Vector& vCurPos);   //是否需要关闭界面
	void RefreshMoney(int nMoney);     //刷新金币
	void RefreshEquipQuility(ItemDefine::SItemCommon *pCommon);        //刷新装备描述
	bool SendIdentifyMsg();
	void RrefreshItem(SCharItem& m_item); //刷新装备的属性
	void RefreshItemInfo(SCharItem &m_item);  //刷新鉴定后的装备描述
	void RefreshOKButton();
	void ShowMaterialIcon();
	void ShowMaterialName(ControlIconDrag::S_ListImg* pItemDrag);
private:
	Vector m_vVisualPos;
	__int64	m_stEquipBagGuid;			//作用物品Guid
	short   m_stBagIndex;

	short m_MaterialBagIndex;
	int64 m_MaterialBagGuide;
public:
	static void OnVisibleChange(ControlObject* pUIObject);
};
extern CUI_ID_FRAME_IdentifyQuality s_CUI_ID_FRAME_IdentifyQuality;
