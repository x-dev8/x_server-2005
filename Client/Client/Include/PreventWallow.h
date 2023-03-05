//======================================================================
//
//	������ϵͳ
//
//	��CPlayerRole���Ƴ���Ϊ����ʹ��
//======================================================================
#pragma once
#include <windows.h>
#include "MeRTLibs.h"
#include "MessageDefine.h"

class CPreventWallow
{
public:
	CPreventWallow(void);
	virtual ~CPreventWallow(void) {}

	static CPreventWallow&	Instance()
	{
		static CPreventWallow xPreventWallow;
		return xPreventWallow;
	}

	// ÿ֡���¡�
	void UpdatePreventWallow();

	// ��ɫ��һ�ν���Ϸʱ�������Ϣ��
	void ClearInfo();

	// ������Ϣ���д���
	void ProcessWallowMsg( Msg* pMsg );

	bool IsFCMNotHealthy( bool bShowMsg = true );

private:
	void PrintDebugString(const char *inputstr);

	void ShowText(const char* text);

protected:
	uint8 m_nStatus;

	// û����д��Ϣ��
	bool m_bNotRegister;
};