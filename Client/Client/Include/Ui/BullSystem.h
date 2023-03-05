/********************************************************************
	Created by UIEditor.exe
	FileName: D:\My Documents\桌面\bullsys\BullSystem.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "Meui/ExpressionManager.h"
#include "ScreenInfoManager.h"

#ifndef ID_FRAME_BullSystem
#define ID_FRAME_BullSystem		"ID_FRAME_BullSystem"
#endif  ID_FRAME_BullSystem
#ifndef ID_PICTURE_WallPaper
#define ID_PICTURE_WallPaper		"ID_PICTURE_WallPaper"
#endif  ID_PICTURE_WallPaper

#include "UiBase.h"
class CUI_ID_FRAME_BullSystem :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_BullSystem();
private:
	 ControlFrame*	m_pID_FRAME_BullSystem;
	 ControlPicture*	m_pID_PICTURE_WallPaper;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

    void SetMoveText( const char *szText, int nCount, DWORD dwColor, const bool bPushFront = false );

public:
	bool IsHoldInMemory() const { return true; }
	virtual void InitializeAtEnterWorld();
	int  ShowExpression(ExpressionManager::ExpressionData *pInfo,int nLeft,int nTop);  //显示表情，返回表情图片宽度
	static bool MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );

private:
    friend class CScreenInfoManager;

	struct SMoveText
	{
		SMoveText()
		{
			Reset();
		}
		void Reset()
		{
			m_nCount = 0;
			m_nX = m_nY = 0;
			m_fWidth = 0.f;
			m_dwColor = 0xffffffff;
			pInfo     = NULL;
		}
		std::string m_strText;
		int			m_nCount;
		int			m_nX;
		int			m_nY;
		float		m_fWidth;
		float		m_fMoveSpeed;
		DWORD		m_dwStartTime;
		DWORD		m_dwColor;
		ExpressionManager::ExpressionData* pInfo;
	};
	std::list<SMoveText>	m_ltMoveText;
	DWORD		m_dwStartTime;
	DWORD		m_dwLimitTime;
	SMoveText m_currMoveText;
};
extern CUI_ID_FRAME_BullSystem s_CUI_ID_FRAME_BullSystem;
