/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\桌面\新建文件夹 (6)\CorpsTask.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_CorpsTask
#define ID_FRAME_CorpsTask		"ID_FRAME_CorpsTask"
#endif  ID_FRAME_CorpsTask
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_True
#define ID_BUTTON_True		"ID_BUTTON_True"
#endif  ID_BUTTON_True
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_LISTIMG_Icon
#define ID_LISTIMG_Icon		"ID_LISTIMG_Icon"
#endif  ID_LISTIMG_Icon

#include "UiBase.h"

class CUI_ID_FRAME_CorpsTask : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_CorpsTask();
	 ControlFrame*	m_pID_FRAME_CorpsTask;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlButton*	m_pID_BUTTON_True;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlListImage*	m_pID_LISTIMG_Icon;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_TrueOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_IconOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_IconOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_IconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_IconOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视


public:
	void SetQuestID( short id );
protected:
	bool IsItemAlreadyIn( __int64 uuid );	//检查是否从背包里面拖过来了
private:	
	std::vector<__int64>	m_vtRequestItemUUID;//暂时测试用，保存要提交的物品
	short m_nQuestID;			//任务ID
	int m_nNpcId;
};
extern CUI_ID_FRAME_CorpsTask s_CUI_ID_FRAME_CorpsTask;
