#pragma once

#include "MeRTLibs.h"
#include <windows.h>
#include <string>

class MouseManager
{
public:
	enum E_CursorType
	{
		Type_Arrow = 0,			// 箭头
		Type_Rotate,			// 旋转
		Type_Wait,				// 等待
		Type_LockTarget,		// 锁定目标
		Type_Attack,			// 进攻
		Type_Dialog,			// 对话
		Type_Shop,				// 商店
		Type_Pick,				// 拾起
		Type_Group,				// 组队
		Type_CollectHerb,		// 采草药
		Type_CollectMine,		// 采矿
		Type_CollectWood,		// 采木头
		Type_LockItem,			// 物品加锁
		Type_UnLockItem,		// 物品解锁
		Type_UseItem,			// 使用物品
		Type_PathFinding,		// 可以寻路
		Type_Destroy,			// 删除物品
		Type_Split,				// 拆分物品
		Type_Repair,			// 修理
		Type_LeftDrag,			// 改变UI大小
		Type_CollectMount,		// 捉骑宠
        Type_MoveFollowMouse,	// 跟随鼠标移动，2.5D视角操作
        Type_PickItem,			// 拾取包裹
        Type_NpcItem,			// NPC是item类型
		Type_MoveWindow,        // 移动窗体
        Type_ChatHyper,			// 聊天框里物品超链接
        Type_ChatPlayer,		// 聊天框里玩家名称
        Type_CastBomb,			// 投掷方向型手榴弹
		Type_CheckUp,			// 鉴定
		Type_Decompose,			// 分解物品
		Type_Max
	};

public:
	void LoadCursor();
	void Render();
	void SetCursor( const E_CursorType enType );
	void SetUICursor( const E_CursorType enType );
	void ForceSetCursor() { m_bSetCursor = TRUE; }

	void SetCanSetCursor(bool b) { m_bCanSet = b; }

	E_CursorType GetCursor() { return m_enCurCursor; }
	E_CursorType GetUICursor() { return m_enUICursor; }
	HCURSOR GetCursor( E_CursorType eType ){ return m_hCursor[eType]; }

private:
//	std::string		m_strCursorName[Type_Max];
//	int				m_nCursorPicId[Type_Max];
	HCURSOR			m_hCursor[Type_Max];
	E_CursorType	m_enCurCursor;
	E_CursorType	m_enUICursor;
//	RECT			m_rcDst;
//	RECT			m_rcSrc;
//	int				m_nCurFrame;
	BOOL			m_bSetCursor;

	bool			m_bCanSet;

public:
	MouseManager(void);
	~MouseManager(void);
};

extern MouseManager theMouseManager;
