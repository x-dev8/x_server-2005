/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\GemMaterialUp.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_GemMaterialUp
#define ID_FRAME_GemMaterialUp		"ID_FRAME_GemMaterialUp"
#endif  ID_FRAME_GemMaterialUp
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_TEXT_Money
#define ID_TEXT_Money		"ID_TEXT_Money"
#endif  ID_TEXT_Money
#ifndef ID_LISTIMG_Material2
#define ID_LISTIMG_Material2		"ID_LISTIMG_Material2"
#endif  ID_LISTIMG_Material2
#ifndef ID_TEXT_MaterialName1
#define ID_TEXT_MaterialName1		"ID_TEXT_MaterialName1"
#endif  ID_TEXT_MaterialName1
#ifndef ID_TEXT_MaterialName2
#define ID_TEXT_MaterialName2		"ID_TEXT_MaterialName2"
#endif  ID_TEXT_MaterialName2
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok
#ifndef ID_TEXT_Tip
#define ID_TEXT_Tip		"ID_TEXT_Tip"
#endif  ID_TEXT_Tip
#ifndef ID_LISTIMG_Material1
#define ID_LISTIMG_Material1		"ID_LISTIMG_Material1"
#endif  ID_LISTIMG_Material1
#ifndef ID_TEXT_NumCurrent
#define ID_TEXT_NumCurrent		"ID_TEXT_NumCurrent"
#endif  ID_TEXT_NumCurrent
#ifndef ID_TEXT_NumNeed
#define ID_TEXT_NumNeed		"ID_TEXT_NumNeed"
#endif  ID_TEXT_NumNeed
#ifndef ID_PICTURE_StarEffect
#define ID_PICTURE_StarEffect		"ID_PICTURE_StarEffect"
#endif  ID_PICTURE_StarEffect
#ifndef ID_TEXT_TipAllDone
#define ID_TEXT_TipAllDone		"ID_TEXT_TipAllDone"
#endif  ID_TEXT_TipAllDone
#include "EquipEvolve.h"
class CUI_ID_FRAME_GemMaterialUp : public EquipEvolveUI
{
	// Member
public:	
	 CUI_ID_FRAME_GemMaterialUp();
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlListImage*	m_pID_LISTIMG_Target;
	 ControlText*	m_pID_TEXT_MaterialName1;
	 ControlText*	m_pID_TEXT_MaterialName2;
	 ControlText*	m_pID_TEXT_Tip;
	 ControlText*	m_pID_TEXT_NumCurrent;
	 ControlText*	m_pID_TEXT_NumNeed;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_Material2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Material2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_Material1OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Material1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	virtual void	RefreshByItemChange();						// 物品改变导致的界面更新

protected:
	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
protected:

	virtual int			GetEvolveType(){return MsgEquipEvolve::ET_Max;}
	virtual int			GetEvolveMaterialType() {return  ItemDefine::ematerial_gemlevelup;}
	virtual bool		IsEvolveAllDone(ControlIconDrag::S_ListImg * pImg);
	virtual void		TipVisible(bool IsMaterialExist) ;
	virtual bool		ProcessAllDone(ControlIconDrag::S_ListImg * pImg);
	virtual int			GetEvolveMoneyCost(){return m_nNeedMoney;}
	virtual void		ResetUIObjects();
	virtual bool		IsMatchEquipType(ItemDefine::SItemCommon* pItemCommon);
	virtual void		RefreshBeginPic(){;}

	virtual bool		UpdateGem(){return true;}
	virtual void		ClearEquip();
protected:
	static void			OnVisibleChange( ControlObject* pUIObject ); 
	virtual void		_RefreshEquipInfo( ControlIconDrag::S_ListImg*  pListImg );
	virtual void		SendEvolveMsg();
	virtual void		RefreshOkButton();

	void				RetriveGemUpInfo(SCharItem* pItem);
	short				m_TargetId;
	int					m_nNeedCount;
	int					m_nNeedMoney;
};
extern CUI_ID_FRAME_GemMaterialUp s_CUI_ID_FRAME_GemMaterialUp;
