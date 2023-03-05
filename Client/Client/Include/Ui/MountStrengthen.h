/********************************************************************
Created by UIEditor.exe
FileName: E:\新建文件夹\3Guo_Client_02.05\Data\Ui\MountStrengthen.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "ItemEnableChangeSysBase.h"

#ifndef ID_FRAME_MountStrengthen
#define ID_FRAME_MountStrengthen		"ID_FRAME_MountStrengthen"
#endif  ID_FRAME_MountStrengthen
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok
#ifndef ID_TEXT_UseMoney
#define ID_TEXT_UseMoney		"ID_TEXT_UseMoney"
#endif  ID_TEXT_UseMoney
#ifndef ID_LISTIMG_Protect
#define ID_LISTIMG_Protect		"ID_LISTIMG_Protect"
#endif  ID_LISTIMG_Protect
#ifndef ID_LISTIMG_Material
#define ID_LISTIMG_Material		"ID_LISTIMG_Material"
#endif  ID_LISTIMG_Material
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_LISTIMG_Mount
#define ID_LISTIMG_Mount		"ID_LISTIMG_Mount"
#endif  ID_LISTIMG_Mount
#ifndef ID_TEXT_SuccessRatio
#define ID_TEXT_SuccessRatio		"ID_TEXT_SuccessRatio"
#endif  ID_TEXT_SuccessRatio
#ifndef ID_TEXT_Fail
#define ID_TEXT_Fail		"ID_TEXT_Fail"
#endif  ID_TEXT_Fail
#ifndef ID_TEXT_Success
#define ID_TEXT_Success		"ID_TEXT_Success"
#endif  ID_TEXT_Success
#ifndef ID_TEXT_MaterialName
#define ID_TEXT_MaterialName		"ID_TEXT_MaterialName"
#endif  ID_TEXT_MaterialName
#ifndef ID_TEXT_MountName
#define ID_TEXT_MountName		"ID_TEXT_MountName"
#endif  ID_TEXT_MountName
#ifndef ID_TEXT_PeotectName
#define ID_TEXT_PeotectName		"ID_TEXT_PeotectName"
#endif  ID_TEXT_PeotectName
#ifndef ID_CHECKBOX_Use_Protect
#define ID_CHECKBOX_Use_Protect		"ID_CHECKBOX_Use_Protect"
#endif  ID_CHECKBOX_Use_Protect
#ifndef ID_TEXT_T1
#define ID_TEXT_T1		"ID_TEXT_T1"
#endif  ID_TEXT_T1
#ifndef ID_TEXT_T2
#define ID_TEXT_T2		"ID_TEXT_T2"
#endif  ID_TEXT_T2
#ifndef ID_TEXT_T3
#define ID_TEXT_T3		"ID_TEXT_T3"
#endif  ID_TEXT_T3
#ifndef ID_TEXT_T4
#define ID_TEXT_T4		"ID_TEXT_T4"
#endif  ID_TEXT_T4

class CUI_ID_FRAME_MountStrengthen : public CUIBase, CItemEnableChangeSysBase
{
	// Member
	enum ItemType
	{
		ITP_Mount,
		ITP_Material,
	};
public:	
	enum EffectStatus
	{
		EffectStatus_No,
		EffectStatus_Fail,
		EffectStatus_Success
	};

	CUI_ID_FRAME_MountStrengthen();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_ProtectOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ProtectOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ProtectOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ProtectOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_MountOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MountOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MountOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MountOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	void ID_CHECKBOX_Use_ProtectOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	virtual bool IsPackItemBeUsing( __int64 nGuid );

	ControlFrame* GetFrame(){return m_pID_FRAME_MountStrengthen;}
	static void OnVisibleChange( ControlObject* pUIObject );

	void ClearImg(ItemType itype,ControlListImage *pTargetImg);
	void ClearAll();
	void ShowMountName(ControlIconDrag::S_ListImg* pItemDrag);
	void ShowMaterialName(ControlIconDrag::S_ListImg* pItemDrag);
	void ShowProtectName(ControlIconDrag::S_ListImg* pItemDrag);

	void ShowProtectMaterialIcon();
	uint16 GetProtectMatrialID(uint16 item_level);
	ControlIconDrag::S_ListImg* RetriveMaterialImg( short itemId ,int& nIndex);

	void RefreshOkButton();
	void RefreshMoney();
	void RefreshProbability();

	void SetEffectStatus(EffectStatus status){m_status = status;}
	void SetBeginTime(DWORD time){dwBeginTime = time;}

	void SendMsg();
	void UpdataAll();
	void TipsVisiable();
	void SetAckMsg(bool b){ m_bAckMsg = b; }

	void ShowMaterialIcon();

private:
	ControlFrame*	m_pID_FRAME_MountStrengthen;
	ControlButton*	m_pID_BUTTON_CLOSE;
	ControlButton*	m_pID_BUTTON_HELP;
	ControlButton*	m_pID_BUTTON_Ok;
	ControlText*	m_pID_TEXT_UseMoney;
	ControlListImage*	m_pID_LISTIMG_Protect;
	ControlListImage*	m_pID_LISTIMG_Material;
	ControlButton*	m_pID_BUTTON_Cancel;
	ControlListImage*	m_pID_LISTIMG_Mount;
	ControlText*	m_pID_TEXT_SuccessRatio;
	ControlText*	m_pID_TEXT_Fail;
	ControlText*	m_pID_TEXT_Success;
	ControlText*	m_pID_TEXT_MaterialName;
	ControlText*	m_pID_TEXT_MountName;
	ControlText*	m_pID_TEXT_PeotectName;
	ControlCheckBox*	m_pID_CHECKBOX_Use_Protect;
	ControlText*	m_pID_TEXT_T1;
	ControlText*	m_pID_TEXT_T2;
	ControlText*	m_pID_TEXT_T3;
	ControlText*	m_pID_TEXT_T4;

	int16 m_nMaterialIndex;		//材料Index
	int64 m_nMaterialGuid;		//材料Guid

	int8  m_nMountIndex;		//坐骑数组下标
	int64 m_nMountGuid;			//坐骑Guid

	uint8 m_unProtectNum;		//保护的等级

	EffectStatus m_status;
	DWORD dwBeginTime;

	ControlObject* m_MountSender;
	ControlObject* m_MaterialSender;
	bool m_bAckMsg;

	uint8				m_lastStarLevel;
};
extern CUI_ID_FRAME_MountStrengthen s_CUI_ID_FRAME_MountStrengthen;
