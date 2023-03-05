#pragma once
#include <Windows.h>
#include <deque>
#include "GlobalDef.h"
#include "MsgBase.h"


class CActionManager
{
public:
	enum enumConst
	{
		const_MaxOperationDataSize = 1024
	};

	enum GAME_ACTIONOPERATIONID
	{
		JUMP_ACTION,
		MOVELEFT_ACTION,
		MOVERIGHT_ACTION,
		USESKILL_OPERATION
	};

	struct SUseSkillOperation
	{
		GameObjectId		SkillTargetID;
		int				nSkillID;
		int				nSkillLevel;

		SUseSkillOperation()
		{
			SkillTargetID = -1;
			nSkillID = -1;
			nSkillLevel = -1;
		}
	};

	struct SGameActionOperation
	{
		// ��Ϸ��������
		short stType;

		// ����Ķ���
		int nActionID;

		// ��������ʱ��
		DWORD dwPushTime;

		// �������ݿ�
		char szOperationData[const_MaxOperationDataSize];

		SGameActionOperation()
		{
			stType = 0;
			nActionID = -1;
			dwPushTime = 0;
		}
	};

private:
	std::deque<SGameActionOperation> m_deGameActionOperation;

public:
	CActionManager(void);
	~CActionManager(void);

	bool PopNextAction( SGameActionOperation &gameactionoperation );
	bool Push_ActionBackToDeque( SGameActionOperation gameactionoperation ); //���������·Żض���
	bool Push_OperationBackToDeque( SGameActionOperation gameactionoperation );
	bool Push_NormalAction( int nActionID, DWORD dwPushTime );
	bool Push_UseSkillOperation( GameObjectId TargetID, int nSkillID, int nSkillLevel, DWORD dwPushTime );



	//int g_nKeydownGameAction[DIK_MEDIASELECT+1];


	//int Size();
	void Clear();

	//BOOL PopNextMove( SMove &move );
	//BOOL Push_KeepMovingToPos( float x, float y, float dx, float dy );
};