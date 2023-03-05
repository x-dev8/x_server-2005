/********************************************************************
	Created by UIEditor.exe
	FileName: D:\Tj\Client\UI\exmain.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_Exmain
#define ID_FRAME_Exmain		"ID_FRAME_Exmain"
#endif  ID_FRAME_Exmain
#ifndef ID_LISTIMG_Exmain
#define ID_LISTIMG_Exmain		"ID_LISTIMG_Exmain"
#endif  ID_LISTIMG_Exmain
#ifndef ID_LISTIMG_Exmain2
#define ID_LISTIMG_Exmain2		"ID_LISTIMG_Exmain2"
#endif  ID_LISTIMG_Exmain2

#include "UiBase.h"
struct SCharSkill;

class CUI_ID_FRAME_Exmain :public CUIBase
{
	// SGuildMember
public:	
	CUI_ID_FRAME_Exmain();
private:
	 ControlFrame*	    m_pID_FRAME_Exmain;
	 ControlListImage*	m_pID_LISTIMG_Exmain;
     ControlListImage*	m_pID_LISTIMG_Exmain2;

public:
	 RECT	_rc;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_LISTIMG_ExmainOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ExmainOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ExmainOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ExmainOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    bool ID_LISTIMG_Exmain2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
    bool ID_LISTIMG_Exmain2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    bool ID_LISTIMG_Exmain2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
    bool ID_LISTIMG_Exmain2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	bool ID_LISTIMG_HotkyeOnIconDisableDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_HotkyeOnIconDisableDragOut( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	void RefeashHotNumber();

	virtual bool IsHoldInMemory() const { return true; }
    virtual void InitializeAtEnterWorld();
	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	//static bool UIMain_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );

	void SetCheckBoxLock( bool b );
	bool PtInOnlyFrame( int x,int y );
	ControlListImage* GetpIDListImg();

	int GetItemIndex1( const ControlListImage::S_ListImg *pItem );
	int GetItemIndex2( const ControlListImage::S_ListImg *pItem );
	bool GetOnlyShowItemIcon1();
	bool GetOnlyShowItemIcon2();
	void SetOnlyShowItemIcon1( bool b );
	void SetOnlyShowItemIcon2( bool b );

	ControlListImage* GetpIDListImageExmain1();
	ControlListImage* GetpIDListImageExmain2();

	bool IsListImgExmain1Visable();
	bool IsListImgExmain2Visable();

	int GetItemCnt1();
	int GetItemCnt2();

	void SetPressItemIndex1( int i );
	void SetPressItemIndex2( int i );

	void SetPos(int x,int y);
	void SetPos1(int x,int y);
	void SetPos2(int x,int y);

private:
	void UpdateIconInfo();

public:
	bool SetSkillAutoToListImage(SCharSkill* pSkill_);
	static void IconOnShiftLBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
};

extern CUI_ID_FRAME_Exmain s_CUI_ID_FRAME_Exmain;