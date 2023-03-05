#pragma once
#include <Windows.h>
#include <string>
#include "color_config.h"

#define FIGHTHINTMESSAGEROW 0

class CShowScreenText
{
public:
	enum EAlign
	{
		eAlignLeftTop = 0
		,eAlignTop
		,eAlignRightTop
		,eAlignLeft
		,eAlignMiddle
		,eAlignRight
		,eAlignLeftBottom
		,eAlignBottom
		,eAlignRightBottom

		,eAlignMax
	};
	enum EShowState
	{
		eShowNormal = 0
		,eShowFadein
		,eShowFadeNormal
		,eShowFadeout
		,eShowHide
	};

    // eUnRiseTextBegin~eUnRiseTextEnd  换装属性改变提示预留13行
	enum
	{
		eInfoBigTileText = 0,
        eInfoSysText = 1,
		eRiseTextBegin = 2,
		eRiseTextEnd = 7,
        eUnRiseTextBegin = 8,
        eUnRiseTextEnd = 20,
		eInfoMax = 21
	};


private:
    // added by ZhuoMeng.Hu		[11/17/2010]
    // 兼容老接口
    void SetBigTile( const char* szText, DWORD color, DWORD time = 0 );
    void SetTile( const char* szText, DWORD color, DWORD time = 0 );
    void AddInfo( const char* szText, DWORD color, DWORD time = 0, int nInfoIndex = -1, bool IsTopLevel = false, int eShowState = eShowFadein );
    void SetInfo( const char* szText, DWORD color, DWORD time = 0 );    //支持换行符，可能一次添加多行

    void SetUnRiseInfoBegin();
    void SetUnRiseInfoEnd();

public:
	// 渲染
	void	Render(bool isTopLevel = false);
	int		GetFontIndex( int nType );

	void	ReCalYPos();
	static int			m_nSkipSameInfoTime;
	static int			m_nScrollTime;
	static int			m_nPauseTime;

    static int          m_nBigTitleYPos;
    static int          m_nSysInfoYPos;
	static int			m_nRiseUpInfoYPos;
	static int			m_nSmallInfoYPos;

	static int			m_nBigTileFontSize;
    static int			m_nSysInfoFontSize;
	static int			m_nRiseUpInfoFontSize;
	static int			m_nSmallInfoFontSize;

	static char			m_szBigTileFontName[256];
    static char			m_szSysInfoFontName[256];
	static char			m_szRiseUpFontName[256];
	static char			m_szSmallFontName[256];

private:
	struct SText
	{
		SText()
		{
			nFont = 0;
			nX = nY = 0;
			dwStartTime = 0;
			dwShowTime = 0;
			dwColor = 0;
			enShowState = eShowHide;
			fMoveSpeed = 0.f;
		}
		int			nFont;				// 字体索引
		int			nX, nY;				// 坐标
		DWORD		dwStartTime;		// 开始显示时间
		DWORD		dwShowTime;			// 显示时间
		float		fMoveSpeed;			// 移动速度
		DWORD		dwColor;			// 颜色
		std::string	strText;			// 内容
		EShowState	enShowState;		// 状态
		bool		bTopLevel;			//是否最上层显示
		HDC			hDC;
	};

protected:
    // 设置大标题           (原地图名)
    void _AddBigInfo( const char* szText, DWORD color, DWORD time = 0 );
    // 单行系统信息         (原设置标题)
    void _AddSingleLineInfo( const char* szText, DWORD color, DWORD time = 0 );
    // 上顶信息支持换行     (原设置信息)
    void _AddMultiLineRiseInfo( const char* szText, DWORD color, DWORD time = 0, int nInfoIndex = -1,
        bool IsTopLevel = false, int eShowState = eShowFadein );
    // 上顶信息子接口       (原添加信息)
    void _AddRiseInfo( const char* szText, DWORD color, DWORD time = 0, int nInfoIndex = -1 ,
        bool IsTopLevel = false,int eShowState = eShowFadein );
    // 不上顶信息，支持多行 ( New )
    void _AddMultiLineUnRiseInfo( const char* szText, DWORD color, DWORD time = 0, int nInfoIndex = -1,
        bool IsTopLevel = false, int eShowState = eShowFadein );
    // 不上顶信息子接口     ( New )
    void _AddUnRiseInfo( const char* szText, DWORD color, DWORD time = 0, int nInfoIndex = -1 ,
        bool IsTopLevel = false,int eShowState = eShowFadein );

private:
	void	SetText( SText *pText,
					int x, int y, int nFontSize,
					DWORD time,
					DWORD color, const char* szText,
					EAlign eAlign,
					EShowState eShowState,
					bool IsTopLevel = false);

private:
	SText*		m_stText[eInfoMax];
	int			m_nTextYPos[eInfoMax];
	void		MoveTextUp();
	DWORD		dwMoveStartTime;		// 移动开始时间
	DWORD		dwPauseStartTime;		// 停留开始时间
	DWORD		dwLastRenderTime;		// 停留开始时间
    int         m_nUnRiseLines;         // 不上升的信息行数计数

private:
    friend class CScreenInfoManager;

public:
	CShowScreenText(void);
	~CShowScreenText(void);
};

CShowScreenText* GetShowScreenText();

extern bool		g_showPFErrorText;