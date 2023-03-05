#pragma once

#include <map>
#include "MeUtility/Singleton.h"
#include "MeUi/IconManager.h"
#include "MeUi/ControlIconDrag.h"
#include "MeUi/UIUnit.h"

class CUILoadMgrBase 
{
public:
	virtual void			Init();										    // Init UI Mgr 
	void			Destory();										
	void			AddUI( CUIUnit *pObj );	                        // HoldInMomery 添加 UIBase
	void			DelUI( CUIUnit *pObj );							// Del UI

	void			loadUIs();		// 玩家首次登陆游戏 加载游戏中永久显示界面
	virtual void			clearUIs();		// 退出 或者 重新登陆 清空游戏界面


	virtual void			ShowUIInTimeOfLoadMap(bool bVisible) = 0;


	virtual bool			OnKeyDown( WPARAM wParam, LPARAM lParam ) = 0;
	virtual bool			OnKeyUp( WPARAM wParam, LPARAM lParam ) = 0;
	void			ClearHideUI();
    void            AddUIToList( CUIUnit* pUI ){m_UIList.push_front(pUI);}     // UIList 添加 UIBase
    virtual void            InitAtEnterWorld();
	void			ResetDevice( );
	void			RefreshByItemChange();						// 物品改变导致的界面更新
	void			RefreshByMoneyChange();			        // 金钱改变导致的界面更新
private:
	
	typedef std::list<CUIUnit*>					UIBaseList;	
	typedef UIBaseList::iterator				UIBaseIter;
	UIBaseList						m_HoldInMemoryList;
	UIBaseList						m_OtherList;
	UIBaseList						&GetUIList(CUIUnit* pUi);
    UIBaseList						m_UIList;

	DWORD							m_UILifeTime;
};

//---------------------------------------------------------------------------------------------------------
//以下三个函数用来调整freme的位置
extern void SetContainRect(IN OUT RECT& lhs, IN RECT& rhs);
extern RECT GetBigRect(ControlFrame* pFrame);
extern void ResetWindowPosition(ControlFrame* pLeft, ControlFrame* pRight);
//---------------------------------------------------------------------------------------------------------






