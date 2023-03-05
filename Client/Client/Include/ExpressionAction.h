#pragma once
#include "ExpActionConfig.h"

// 表情动作游戏相关逻辑
class CExpressionAction
{
public:
	CExpressionAction(void): m_nExpressionActionCoolDown( 0 ) {}
	virtual ~CExpressionAction(void) {}

	static CExpressionAction&  Instance()
	{
		static CExpressionAction xExpressionAction;
		return xExpressionAction;
	}

	bool				CheckAndDoExpressionAction(const char* szChat, ExpAction::ESex sex);// 判断聊天内容是否表情动作，是则执行
	bool				CheckAndDoExpressionAction(unsigned short ustActionId);				// 根据动作Id播动作表情
	bool				CheckAndDoExpressionActionByItemId(unsigned short ustItemId, ExpAction::ESex sex);// 根据动作Id播动作表情

	void				OnSeeExpressionAction(int nPlayerId, int nTargetId, unsigned short ustActionId);// 看到玩家表情动作

	void				UpdateCoolDown();

	const ExpAction*	GetExpActionByItemId(unsigned short ustItemId, ExpAction::ESex sex);
	const ExpAction*	GetExpActionByIndex(unsigned short ustIndex, ExpAction::ESex sex);
	int					GetExpActionCD() { return theExpActionConfig.GetExpActionCD(); }
	unsigned short		GetTargetMaxDist() { return theExpActionConfig.GetTargetMaxDist(); }
	int					GetExpActionNum(ExpAction::ESex sex) { return theExpActionConfig.GetExpActionNum(sex); }

protected:
	const ExpAction*	GetExpAction(const char* szChat, ExpAction::ESex sex);		// 从聊天内容获取表情动作数据

	const ExpAction*	GetExpAction(unsigned short ustActionId);					// 从动作Id获取表情动作数据

	void				SendExpressionAction(unsigned short ustActionId, int nTargetID);	// 发送网络消息

	bool				CanDoExpressionAction(bool bShowInfo = true);

	int					m_nExpressionActionCoolDown;		// 冷却
};

