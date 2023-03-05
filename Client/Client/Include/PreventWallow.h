//======================================================================
//
//	防沉迷系统
//
//	从CPlayerRole里移出作为单件使用
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

	// 每帧更新。
	void UpdatePreventWallow();

	// 角色第一次进游戏时候清除信息。
	void ClearInfo();

	// 根据消息进行处理。
	void ProcessWallowMsg( Msg* pMsg );

	bool IsFCMNotHealthy( bool bShowMsg = true );

private:
	void PrintDebugString(const char *inputstr);

	void ShowText(const char* text);

protected:
	uint8 m_nStatus;

	// 没有填写信息。
	bool m_bNotRegister;
};