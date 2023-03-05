#pragma once

#include <map>
#include "GlobalDef.h"
#include "MeUi/ControlObject.h"
#include "IconManagerClient.h"
#include "LuaScript.h"
#include "Singleton.h"
#include "MeUi/IconManager.h"
#include "MeUi/ControlIconDrag.h"
#include "UIBase.h"

class CUIMgr :public Singleton<CUIMgr>
{
public:
	void			Init();										    // Init UI Mgr 
	void			Destory();										
// 	void			AddUI( UI_OBJECT_TYPE eType, CUIBase *pObj );	// 添加 UI Frame Object
	void			AddUI( CUIBase *pObj );	                        // HoldInMomery 添加 UIBase
// 	void			DelUI( UI_OBJECT_TYPE eType );					// Del UI
	void			DelUI( CUIBase *pObj );							// Del UI
// 	CUIBase *		GetUIObject( UI_OBJECT_TYPE eType );			// 得到UI Frame Object
// 	UI_OBJECT_TYPE  GetUIType( CUIBase* pObject);			        // 得到UI Type

	void			loadUIs();		// 玩家首次登陆游戏 加载游戏中永久显示界面
	void			clearUIs();		// 退出 或者 重新登陆 清空游戏界面

//     void            clearUIDatas(); // 清除UI内部使用到的数据。

	void			ShowUIInTimeOfLoadMap(bool bVisible);

	//LuaStateOwner m_LuaScript;

	bool			OnKeyDown( WPARAM wParam, LPARAM lParam );
	bool			OnKeyUp( WPARAM wParam, LPARAM lParam );
	void			setVisableUI(CUIBase *pObj);
	void			ClearHideUI();
    void            AddUIToList( CUIBase* pUI ){m_UIList.push_back(pUI);}     // UIList 添加 UIBase
    void            InitAtEnterWorld();
	void			ResetDevice( );
	void			RefreshByItemChange();						// 物品改变导致的界面更新
	void			RefreshByMoneyChange();			        // 金钱改变导致的界面更新
	static void     RetriveSpareTimeString( S_IconInfoBase* pTip );
	static void     RetriveTimeString( char * szBuffer, COLORREF& colTime, int nDay, int nHour, int nMinute, int nSecond );

	void            ProcessUiShowOrHide(bool bValue,CUIBase *pObject = NULL);

private:
// 	typedef std::map< UI_OBJECT_TYPE, CUIBase* > UIMgr;	
	
	typedef std::list<CUIBase*>					UIBaseList;	
	typedef UIBaseList::iterator				UIBaseIter;
	UIBaseList						m_HoldInMemoryList;
	UIBaseList						m_OtherList;
	UIBaseList						&GetUIList(CUIBase* pUi);
    UIBaseList						m_UIList;

	DWORD							m_UILifeTime;
protected:
	static S_IconInfoBase* CreateIconInfo();
	static bool IconDragGlobalOnMouseMove( ControlIconDrag::S_ListImg* pItem, bool bEnableCompare, const RECT& rcItem, ControlIconDrag* pThis );
// 	static bool FindPlayerHyper(const std::wstring& wstrParse, std::wstring& wstrPlayer);
};

//---------------------------------------------------------------------------------------------------------
//以下三个函数用来调整freme的位置
extern void SetContainRect(IN OUT RECT& lhs, IN RECT& rhs);
extern RECT GetBigRect(ControlFrame* pFrame);
extern void ResetWindowPosition(ControlFrame* pLeft, ControlFrame* pRight);
extern void ResetWindowPositionEx(ControlFrame* pLeft, ControlFrame* pMiddle, ControlFrame* pRight);
//---------------------------------------------------------------------------------------------------------

extern TNativeFun GNativeFun[];
extern int g_GetNativeFunNum();

extern IScript *GetLuaScript();
extern CUIMgr *GetUIScriptMgr();

#define USE_SCRIPT( type, p ) 
#define CLOSE_SCRIPT( pUI ) 

enum UI_Callback_Type
{
	eItem_UI_Callback = 0,
	eMount_UI_Callback,
	eQuestId_UI_Callback,
	eNpcId_UI_Callback,
	eMapId_UI_Callback,
	eExipTip_UI_Callback,
	eMore_UI_Callback,			// ExitTip上点击详情的类型
	eSkill_UI_Callback,			//聊天显示技能回调
	eTask_UI_Callback,
	ePet_UI_Callback
};


















