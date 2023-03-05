/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\法宝资源\法宝\法宝\TaliExercise.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "GlobalDef.h"

#ifndef ID_FRAME_TaliExercise
#define ID_FRAME_TaliExercise		"ID_FRAME_TaliExercise"
#endif  ID_FRAME_TaliExercise
#ifndef ID_LISTIMG_1935
#define ID_LISTIMG_1935		"ID_LISTIMG_1935"
#endif  ID_LISTIMG_1935
#ifndef ID_LISTIMG_Material0
#define ID_LISTIMG_Material0		"ID_LISTIMG_Material0"
#endif  ID_LISTIMG_Material0
#ifndef ID_LISTIMG_Material1
#define ID_LISTIMG_Material1		"ID_LISTIMG_Material1"
#endif  ID_LISTIMG_Material1
#ifndef ID_LISTIMG_Material2
#define ID_LISTIMG_Material2		"ID_LISTIMG_Material2"
#endif  ID_LISTIMG_Material2
#ifndef ID_LISTIMG_Material3
#define ID_LISTIMG_Material3		"ID_LISTIMG_Material3"
#endif  ID_LISTIMG_Material3
#ifndef ID_LISTIMG_Genre
#define ID_LISTIMG_Genre		"ID_LISTIMG_Genre"
#endif  ID_LISTIMG_Genre
#ifndef ID_TEXT_TalismanName
#define ID_TEXT_TalismanName		"ID_TEXT_TalismanName"
#endif  ID_TEXT_TalismanName
#ifndef ID_TEXT_TalismanLv
#define ID_TEXT_TalismanLv		"ID_TEXT_TalismanLv"
#endif  ID_TEXT_TalismanLv
#ifndef ID_TEXT_MaterialName0
#define ID_TEXT_MaterialName0		"ID_TEXT_MaterialName0"
#endif  ID_TEXT_MaterialName0
#ifndef ID_TEXT_MaterialName1
#define ID_TEXT_MaterialName1		"ID_TEXT_MaterialName1"
#endif  ID_TEXT_MaterialName1
#ifndef ID_TEXT_MaterialName2
#define ID_TEXT_MaterialName2		"ID_TEXT_MaterialName2"
#endif  ID_TEXT_MaterialName2
#ifndef ID_TEXT_MaterialName3
#define ID_TEXT_MaterialName3		"ID_TEXT_MaterialName3"
#endif  ID_TEXT_MaterialName3
#ifndef ID_TEXT_MaterialMoment0
#define ID_TEXT_MaterialMoment0		"ID_TEXT_MaterialMoment0"
#endif  ID_TEXT_MaterialMoment0
#ifndef ID_TEXT_MaterialMoment1
#define ID_TEXT_MaterialMoment1		"ID_TEXT_MaterialMoment1"
#endif  ID_TEXT_MaterialMoment1
#ifndef ID_TEXT_MaterialMoment2
#define ID_TEXT_MaterialMoment2		"ID_TEXT_MaterialMoment2"
#endif  ID_TEXT_MaterialMoment2
#ifndef ID_TEXT_MaterialMoment3
#define ID_TEXT_MaterialMoment3		"ID_TEXT_MaterialMoment3"
#endif  ID_TEXT_MaterialMoment3
#ifndef ID_TEXT_Moment
#define ID_TEXT_Moment		"ID_TEXT_Moment"
#endif  ID_TEXT_Moment
#ifndef ID_TEXT_Probability
#define ID_TEXT_Probability		"ID_TEXT_Probability"
#endif  ID_TEXT_Probability
#ifndef ID_TEXT_Introduce
#define ID_TEXT_Introduce		"ID_TEXT_Introduce"
#endif  ID_TEXT_Introduce
#ifndef ID_BUTTON_Confirm
#define ID_BUTTON_Confirm		"ID_BUTTON_Confirm"
#endif  ID_BUTTON_Confirm
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP

class CUI_ID_FRAME_TaliExercise : public CUIBase
{
public:
	 CUI_ID_FRAME_TaliExercise();
	// Member
private:	
	 ControlFrame*	m_pID_FRAME_TaliExercise;
	 ControlListImage*	m_pID_LISTIMG_1935;
	 ControlListImage*	m_pID_LISTIMG_Material0;
	 ControlListImage*	m_pID_LISTIMG_Material1;
	 ControlListImage*	m_pID_LISTIMG_Material2;
	 ControlListImage*	m_pID_LISTIMG_Material3;
	 ControlListImage*	m_pID_LISTIMG_Genre;
	 ControlText*	m_pID_TEXT_TalismanName;
	 ControlText*	m_pID_TEXT_TalismanLv;
	 ControlText*	m_pID_TEXT_MaterialName0;
	 ControlText*	m_pID_TEXT_MaterialName1;
	 ControlText*	m_pID_TEXT_MaterialName2;
	 ControlText*	m_pID_TEXT_MaterialName3;
	 ControlText*	m_pID_TEXT_MaterialMoment0;
	 ControlText*	m_pID_TEXT_MaterialMoment1;
	 ControlText*	m_pID_TEXT_MaterialMoment2;
	 ControlText*	m_pID_TEXT_MaterialMoment3;
	 ControlText*	m_pID_TEXT_Moment;
	 ControlText*	m_pID_TEXT_Probability;
	 ControlText*	m_pID_TEXT_Introduce;
	 ControlButton*	m_pID_BUTTON_Confirm;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlButton*	m_pID_BUTTON_HELP;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_LISTIMG_1935OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_1935OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_1935OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_1935OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material0OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Material0OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material0OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material0OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material1OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Material1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Material2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material3OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Material3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Material3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_GenreOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_GenreOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_GenreOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_GenreOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_ConfirmOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:	
	bool ItemOnIconDragOn(ControlListImage* pImg,ControlIconDrag::S_ListImg* pItemDrag,int nCount = 1);
	bool ItemOnIconDragOut(ControlListImage* pImg);
	void UpdateTaliInfo(SCharItem *pItem);
	void UpdateTaliMaterialInfo(ControlListImage::S_ListImg *pImg,ControlText* pTexName,ControlText* pTexCount);
	void UpdateOtherInfo(SCharItem *pItem);
};
extern CUI_ID_FRAME_TaliExercise s_CUI_ID_FRAME_TaliExercise;
