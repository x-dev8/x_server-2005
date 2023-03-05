#pragma once
#include "ExpActionConfig.h"

// ���鶯����Ϸ����߼�
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

	bool				CheckAndDoExpressionAction(const char* szChat, ExpAction::ESex sex);// �ж����������Ƿ���鶯��������ִ��
	bool				CheckAndDoExpressionAction(unsigned short ustActionId);				// ���ݶ���Id����������
	bool				CheckAndDoExpressionActionByItemId(unsigned short ustItemId, ExpAction::ESex sex);// ���ݶ���Id����������

	void				OnSeeExpressionAction(int nPlayerId, int nTargetId, unsigned short ustActionId);// ������ұ��鶯��

	void				UpdateCoolDown();

	const ExpAction*	GetExpActionByItemId(unsigned short ustItemId, ExpAction::ESex sex);
	const ExpAction*	GetExpActionByIndex(unsigned short ustIndex, ExpAction::ESex sex);
	int					GetExpActionCD() { return theExpActionConfig.GetExpActionCD(); }
	unsigned short		GetTargetMaxDist() { return theExpActionConfig.GetTargetMaxDist(); }
	int					GetExpActionNum(ExpAction::ESex sex) { return theExpActionConfig.GetExpActionNum(sex); }

protected:
	const ExpAction*	GetExpAction(const char* szChat, ExpAction::ESex sex);		// ���������ݻ�ȡ���鶯������

	const ExpAction*	GetExpAction(unsigned short ustActionId);					// �Ӷ���Id��ȡ���鶯������

	void				SendExpressionAction(unsigned short ustActionId, int nTargetID);	// ����������Ϣ

	bool				CanDoExpressionAction(bool bShowInfo = true);

	int					m_nExpressionActionCoolDown;		// ��ȴ
};

