#pragma once
#include <list>
#include "MeUi/MeUi.h"
#include "MessageDefine.h"

#ifndef ID_FRAME_Bull
#define ID_FRAME_Bull		"ID_FRAME_Bull"
#endif  ID_FRAME_Bull
#ifndef ID_PICTURE_WallPaper
#define ID_PICTURE_WallPaper		"ID_PICTURE_WallPaper"
#endif  ID_PICTURE_WallPaper

#include "UiBase.h"
class CUI_ID_FRAME_BULL :public CUIBase
{
	// SGuildMember
private:
	ControlFrame*   m_pID_FRAME_Bull;
	ControlPicture* m_pID_PICTURE_WallPaper;

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
public:


private:
	void SetMoveText( const char *szText, int nCount );

	static bool MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );
	

	struct SMoveText
	{
		SMoveText()
		{
			m_nCount = 0;
			m_nX = m_nY = 0;
			m_fWidth = 0.f;
			m_dwColor = 0xffffffff;
		}
		std::string m_strText;
		int			m_nCount;
		int			m_nX;
		int			m_nY;
		float		m_fWidth;
		float		m_fMoveSpeed;
		DWORD		m_dwStartTime;
		DWORD		m_dwColor;
	};
	std::list<SMoveText>	m_ltMoveText;
	DWORD		m_dwStartTime;
	DWORD		m_dwLimitTime;

public:
	CUI_ID_FRAME_BULL();
};

extern CUI_ID_FRAME_BULL s_CUI_ID_FRAME_BULL;
