#pragma once

#include "MeUi/MeUi.h"
#include "MeUi/UiManager.h"

class CUILoadMgrBase;
class CUIUnit : public MeCommonAllocObj<CUIUnit>
{
public:
				CUIUnit();
				virtual ~CUIUnit();
public:
	bool		IsUILoad() const { return m_bUILoad; }
	virtual bool	IsHoldInMemory() const { return false; }
	virtual bool	LoadUI();									
	virtual bool	UnLoadUI();									// 卸载UI
	virtual bool	IsVisable();								// 是否可见
	virtual void	SetVisable( const bool bVisable );			// 设置是否可视
    virtual void	InitializeAtEnterWorld(){}			        // 每次登陆游戏调用的逻辑
	virtual void	RefreshByItemChange(){}						// 物品改变导致的界面更新
	virtual void	RefreshByMoneyChange(){}			        // 金钱改变导致的界面更新
	DWORD			GetLastVisibleTime() const { return m_LastVisibleTime; }
	void			SetLastVisibleTime(DWORD val) { m_LastVisibleTime = val; }
	virtual void	ResetDevice( ){;}
	
	static			CUILoadMgrBase* GetUIMgr() {return m_uiLoadMgr;}
	static			CUILoadMgrBase* m_uiLoadMgr;
protected:
	bool		m_bUILoad;
	DWORD				m_BornTime;
	DWORD				m_LastVisibleTime;
	virtual bool _LoadUI() = 0;									// 载入UI
	virtual bool	DoControlConnect() = 0;							// 关连控件
	virtual bool	_UnLoadUI() = 0;									// 卸载UI
	virtual bool	_IsVisable() = 0;								// 是否可见
	virtual void	_SetVisable( const bool bVisable );			// 设置是否可视

};

class CUINotManagedByUIMgr : public CUIUnit
{
public:
	CUINotManagedByUIMgr()
	{
	}
	virtual bool	LoadUI(){m_bUILoad = _LoadUI(); return m_bUILoad;}									
	virtual void	SetVisable( const bool bVisable ){_SetVisable(bVisable);}			// 重载这两个函数，为了不接受uimgr的管理
};

class MexAnimCtrl;
#define UI_LAYOUT_1		1
#define UI_LAYOUT_2		2
#define UI_LAYOUT_3		3
#define UI_LAYOUT_4		4
