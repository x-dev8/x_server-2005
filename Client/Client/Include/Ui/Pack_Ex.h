/********************************************************************
	Created by UIEditor.exe
	FileName: D:\Tj\Client\UI\Pack_Ex.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_pack_ex
#define ID_FRAME_pack_ex		"ID_FRAME_pack_ex"
#endif  ID_FRAME_pack_ex
#ifndef ID_PICTURE_picBacEnable
#define ID_PICTURE_picBacEnable		"ID_PICTURE_picBacEnable"
#endif  ID_PICTURE_picBacEnable
#ifndef ID_LISTIMG_pack_ex
#define ID_LISTIMG_pack_ex		"ID_LISTIMG_pack_ex"
#endif  ID_LISTIMG_pack_ex
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_PICTURE_picBacDisable
#define ID_PICTURE_picBacDisable		"ID_PICTURE_picBacDisable"
#endif  ID_PICTURE_picBacDisable
#ifndef ID_PICTURE_picBacDisableRow
#define ID_PICTURE_picBacDisableRow		"ID_PICTURE_picBacDisableRow"
#endif  ID_PICTURE_picBacDisableRow

#include "UiBase.h"
class CUI_ID_FRAME_pack_ex :public CUIBase
{
	// SGuildMember
public:	
	CUI_ID_FRAME_pack_ex();
private:
	 ControlFrame*	m_pID_FRAME_pack_ex;
	 ControlPicture*	m_pID_PICTURE_picBacEnable;
	 ControlPicture*	m_pID_PICTURE_picBacDisable;
	 ControlListImage*	m_pID_LISTIMG_pack_ex;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlPicture*	m_pID_PICTURE_picBacDisableRow;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_LISTIMG_pack_exOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_pack_exOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_pack_exOnIconRDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );

	static void OnFrameMoveFun( ControlObject* pSender );
	static bool UIPackEx_FrameClick( ControlObject* pSender );
	static void IconOnShiftLBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	unsigned int GetDstIndex() { return m_ustDstIndex; }
	void SetDstIndex(unsigned int nIndex) { m_ustDstIndex = nIndex; }
	int	GetItemIndexByListImg( ControlIconDrag::S_ListImg* pItem );

private:
	void SetPos(int x, int y );
	void setPicBackgroupPos();

	int packEx_RowCnt;	//默认开放2行
	unsigned int m_ustDstIndex;
};

extern CUI_ID_FRAME_pack_ex s_CUI_ID_FRAME_pack_ex;