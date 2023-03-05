/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\Hole.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "GemBase.h"

#ifndef ID_FRAME_Hole
#define ID_FRAME_Hole		"ID_FRAME_Hole"
#endif  ID_FRAME_Hole
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
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
#ifndef ID_TEXT_HoleTip
#define ID_TEXT_HoleTip		"ID_TEXT_HoleTip"
#endif  ID_TEXT_HoleTip
#ifndef ID_TEXT_HoleNumber
#define ID_TEXT_HoleNumber		"ID_TEXT_HoleNumber"
#endif  ID_TEXT_HoleNumber
#ifndef ID_PICTURE_StarEffect
#define ID_PICTURE_StarEffect		"ID_PICTURE_StarEffect"
#endif  ID_PICTURE_StarEffect
#ifndef ID_PICTURE_Open1
#define ID_PICTURE_Open1		"ID_PICTURE_Open1"
#endif  ID_PICTURE_Open1
#ifndef ID_PICTURE_Open2
#define ID_PICTURE_Open2		"ID_PICTURE_Open2"
#endif  ID_PICTURE_Open2
#ifndef ID_PICTURE_Open3
#define ID_PICTURE_Open3		"ID_PICTURE_Open3"
#endif  ID_PICTURE_Open3
#ifndef ID_PICTURE_Open4
#define ID_PICTURE_Open4		"ID_PICTURE_Open4"
#endif  ID_PICTURE_Open4
#ifndef ID_LISTIMG_Hole1
#define ID_LISTIMG_Hole1		"ID_LISTIMG_Hole1"
#endif  ID_LISTIMG_Hole1
#ifndef ID_LISTIMG_Hole2
#define ID_LISTIMG_Hole2		"ID_LISTIMG_Hole2"
#endif  ID_LISTIMG_Hole2
#ifndef ID_LISTIMG_Hole3
#define ID_LISTIMG_Hole3		"ID_LISTIMG_Hole3"
#endif  ID_LISTIMG_Hole3
#ifndef ID_LISTIMG_Hole4
#define ID_LISTIMG_Hole4		"ID_LISTIMG_Hole4"
#endif  ID_LISTIMG_Hole4
#ifndef ID_PICTURE_Lock1
#define ID_PICTURE_Lock1		"ID_PICTURE_Lock1"
#endif  ID_PICTURE_Lock1
#ifndef ID_PICTURE_Lock2
#define ID_PICTURE_Lock2		"ID_PICTURE_Lock2"
#endif  ID_PICTURE_Lock2
#ifndef ID_PICTURE_Lock3
#define ID_PICTURE_Lock3		"ID_PICTURE_Lock3"
#endif  ID_PICTURE_Lock3
#ifndef ID_PICTURE_Lock4
#define ID_PICTURE_Lock4		"ID_PICTURE_Lock4"
#endif  ID_PICTURE_Lock4
#ifndef ID_PICTURE_Begin
#define ID_PICTURE_Begin		"ID_PICTURE_Begin"
#endif  ID_PICTURE_Begin
#ifndef ID_LISTIMG_Armour
#define ID_LISTIMG_Armour		"ID_LISTIMG_Armour"
#endif  ID_LISTIMG_Armour
#ifndef ID_TEXT_SuccessRatio
#define ID_TEXT_SuccessRatio		"ID_TEXT_SuccessRatio"
#endif  ID_TEXT_SuccessRatio
//#ifndef ID_TEXT_Effect
//#define ID_TEXT_Effect			"ID_TEXT_Effect"
//#endif	ID_TEXT_Effect
//#ifndef ID_TEXT_Success
//#define ID_TEXT_Success			"ID_TEXT_Success"
//#endif	ID_TEXT_Success
//#ifndef ID_TEXT_Fail
//#define ID_TEXT_Fail			"ID_TEXT_Fail"
//#endif	ID_TEXT_Fail
#ifndef ID_TEXT_EquipName
#define ID_TEXT_EquipName		"ID_TEXT_EquipName"
#endif  ID_TEXT_EquipName
#ifndef ID_TEXT_MaterialName
#define ID_TEXT_MaterialName		"ID_TEXT_MaterialName"
#endif  ID_TEXT_MaterialName

class CUI_ID_FRAME_Hole : public GemBaseUI
{
	// Member
public:	
	 CUI_ID_FRAME_Hole();
	 ~CUI_ID_FRAME_Hole();
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlText*	m_pID_TEXT_HoleTip;
	 ControlText*	m_pID_TEXT_HoleNumber;
	 ControlText*	m_pID_TEXT_SuccessRatio;
	 //ControlText*	m_pID_TEXT_Effect;
	 //ControlText*	m_pID_TEXT_Success;
	 //ControlText*	m_pID_TEXT_Fail;
	 ControlText*	m_pID_TEXT_EquipName;
	 ControlText*	m_pID_TEXT_MaterialName;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_Hole1OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Hole1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Hole1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Hole1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Hole2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Hole2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Hole2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Hole2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Hole3OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Hole3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Hole3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Hole3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Hole4OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Hole4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Hole4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Hole4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	virtual void _SetVisable( const bool bVisable );

private:
	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	//DWORD dwBeginTime;
	//EffectStatus m_status;
	//bool m_bSendMsg;

protected:
	virtual int			GetEvolveType(){return MsgEquipEvolve::ET_Stiletto;}
	virtual int			GetEvolveMaterialType() {return  ItemDefine::ematerial_stiletto;}
	virtual bool		IsEvolveAllDone(ControlIconDrag::S_ListImg * pImg) ;
	virtual bool		ProcessAllDone(ControlIconDrag::S_ListImg * pImg);

	virtual bool		IsMatchOther(ItemDefine::SCreateMaterial* pMaterial);

	virtual char*		GetSlideEffectPath(){return NULL;}
	virtual void		TipVisible(bool IsMaterialExist);
// 	virtual void		SetAtomVisible( bool bVisible );
	virtual void		RefreshNeedMoney();

	virtual void ClearEquip();
	virtual void _RefreshEquipInfo( ControlIconDrag::S_ListImg*  pListImg );
	virtual void		RefreshOkButton();
	
	static void OnVisibleChange( ControlObject* pUIObject ); 

private:
	void RefreshSuccessRatio(int holeIndex_);
public:
	void RefreshMoney();
	void SetOkButtonEnable(bool bEnable){m_pID_BUTTON_Ok->SetEnable(bEnable);}
	//void SetEffectStatus(EffectStatus status){m_status = status;}
	//void SetBeginTime(DWORD time){dwBeginTime = time;}
	//lyh++ 重载
	virtual bool UpdateGem();

	void ShowItemName(ControlText* pText, ControlIconDrag::S_ListImg* pItemDrag);
};
extern CUI_ID_FRAME_Hole s_CUI_ID_FRAME_Hole;
