/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Document\�߻��ĵ�\����\MoveStarUpgrade.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "me3d/Vector.h"
#include "MeUi/Animation/SlideAnimation.h"
#include "ItemEnableChangeSysBase.h"

#ifndef ID_FRAME_MoveStarUpgrade
#define ID_FRAME_MoveStarUpgrade		"ID_FRAME_MoveStarUpgrade"
#endif  ID_FRAME_MoveStarUpgrade
#ifndef ID_PICTURE_Material2
#define ID_PICTURE_Material2		"ID_PICTURE_Material2"
#endif  ID_PICTURE_Material2
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_help
#define ID_BUTTON_help		"ID_BUTTON_help"
#endif  ID_BUTTON_help
#ifndef ID_LISTIMG_Result
#define ID_LISTIMG_Result		"ID_LISTIMG_Result"
#endif  ID_LISTIMG_Result
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
#ifndef ID_PICTURE_Material
#define ID_PICTURE_Material		"ID_PICTURE_Material"
#endif  ID_PICTURE_Material
#ifndef ID_LISTIMG_Material
#define ID_LISTIMG_Material		"ID_LISTIMG_Material"
#endif  ID_LISTIMG_Material
#ifndef ID_LISTIMG_Material2
#define ID_LISTIMG_Material2		"ID_LISTIMG_Material2"
#endif  ID_LISTIMG_Material2
#ifndef ID_TEXT_RateZ
#define ID_TEXT_RateZ		"ID_TEXT_RateZ"
#endif  ID_TEXT_RateZ
#ifndef ID_TEXT_Rate
#define ID_TEXT_Rate		"ID_TEXT_Rate"
#endif  ID_TEXT_Rate
#ifndef ID_PICTURE_MoveStarUpgradeEffect
#define ID_PICTURE_MoveStarUpgradeEffect		"ID_PICTURE_MoveStarUpgradeEffect"
#endif  ID_PICTURE_MoveStarUpgradeEffect

#include "UiBase.h"
class CUI_ID_FRAME_MoveStarUpgrade :public CUIBase, CItemEnableChangeSysBase
{
	// Member
public:	
	 CUI_ID_FRAME_MoveStarUpgrade();
private:
	 ControlFrame*		m_pID_FRAME_MoveStarUpgrade;
// 	 ControlPicture*	m_pID_PICTURE_Material2;
// 	 ControlButton*		m_pID_BUTTON_CLOSE;
// 	 ControlButton*		m_pID_BUTTON_help;
	 ControlListImage*	m_pID_LISTIMG_Result;
	 ControlButton*		m_pID_BUTTON_Ok;
	 ControlButton*		m_pID_BUTTON_Cancel;
	 ControlText*		m_pID_TEXT_UseMoneyZ;
	 ControlText*		m_pID_TEXT_UseMoney;
	 ControlPicture*	m_pID_PICTURE_Material;
	 ControlListImage*	m_pID_LISTIMG_Material;
	 //ControlListImage*	m_pID_LISTIMG_Material2;
	 ControlText*		m_pID_TEXT_RateZ;
	 ControlText*		m_pID_TEXT_Rate;
	 ControlPicture*	m_pID_PICTURE_MoveStarUpgradeEffect;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
// 	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
// 	bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_ResultOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ResultOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ResultOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ResultOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
// 	bool ID_LISTIMG_Material2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
// 	bool ID_LISTIMG_Material2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
// 	bool ID_LISTIMG_Material2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
// 	bool ID_LISTIMG_Material2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	
private:
	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����

public:
	bool PutItemFromPack( ControlObject* pSender, ControlIconDrag::S_ListImg* pItemDrag, int iBagType, int iItemIndex );
	void ClearAll();
	void ClearMaterials();
	void OnUpgradeFailed();

	static void OnVisibleChanged(ControlObject* pSender);
    virtual bool IsPackItemBeUsing( __int64 nGuid );

	ControlFrame* GetFrame() {return m_pID_FRAME_MoveStarUpgrade;}

private:
	bool SetMoveStarItemBagIndex(int iBagType, int index, __int64 n64Guid);
	bool SetMaterial1(int iBagType, int index, __int64 n64Guid);
	void ClearMoveStarItem();
	void ClearMaterial1();
#if 0
	bool SetMaterial2(int iBagType, int index, __int64 n64Guid);
	void ClearMaterial2();
#endif
	void RefreshRateAndMoney(float rate, DWORD dwMoney);
	bool CanUpgrate(bool bShowInfo);
	void EnableBagItem(bool bEnable, int iBagType, int iItemIndex);
	void ClearAnim();

	Vector			m_vVisiblePos;

	int				m_iMoveStarItemIndex;	// ����ʯ��������
	__int64			m_n64MoveStarItemGuid;	// ����ʯGUID
	int				m_iMoveStarItemId;		// ����ʯ��ƷID

	int				m_iMaterialItemId;		// ��������ʯ�ӱ����ò���ID
	float			m_fRate;				// �ɹ�����
	DWORD			m_dwCostMoney;			// ���Ľ�Ǯ

	uint8			m_uchItemBagType1;		// ����ʹ�õĲ��ϱ�������
	int				m_iMaterialIndex1;		// ����ʹ�õĲ��ϵ�����
	__int64			m_n64MaterialGuid1;
	short			m_shMaterialCount;		// ���ϸ���

#if 0
	uint8			m_uchItemBagType2;		// ���ʼӳɲ��ϵı�������
	int				m_iMaterialIndex2;      // ���ʼӳɲ��ϵ����� ( û�зżӳɲ������ó� -1 )
	__int64			m_n64MaterialGuid2;
#endif
	float			m_fAdditionalRate;		// ���Ӳ��ϳɹ���

	CSlideAnimation m_slideAnim;			//����֡����
	bool			m_bStartAnim;

	bool			m_bStartIntonate;
	int				m_nIntonateTime;		// ����ʱ�䣬����
	DWORD			m_dwStartIntonateTime;	// ��ʼ����ʱ��
};
extern CUI_ID_FRAME_MoveStarUpgrade s_CUI_ID_FRAME_MoveStarUpgrade;
