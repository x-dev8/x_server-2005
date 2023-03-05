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

    // eUnRiseTextBegin~eUnRiseTextEnd  ��װ���Ըı���ʾԤ��13��
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
    // �����Ͻӿ�
    void SetBigTile( const char* szText, DWORD color, DWORD time = 0 );
    void SetTile( const char* szText, DWORD color, DWORD time = 0 );
    void AddInfo( const char* szText, DWORD color, DWORD time = 0, int nInfoIndex = -1, bool IsTopLevel = false, int eShowState = eShowFadein );
    void SetInfo( const char* szText, DWORD color, DWORD time = 0 );    //֧�ֻ��з�������һ����Ӷ���

    void SetUnRiseInfoBegin();
    void SetUnRiseInfoEnd();

public:
	// ��Ⱦ
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
		int			nFont;				// ��������
		int			nX, nY;				// ����
		DWORD		dwStartTime;		// ��ʼ��ʾʱ��
		DWORD		dwShowTime;			// ��ʾʱ��
		float		fMoveSpeed;			// �ƶ��ٶ�
		DWORD		dwColor;			// ��ɫ
		std::string	strText;			// ����
		EShowState	enShowState;		// ״̬
		bool		bTopLevel;			//�Ƿ����ϲ���ʾ
		HDC			hDC;
	};

protected:
    // ���ô����           (ԭ��ͼ��)
    void _AddBigInfo( const char* szText, DWORD color, DWORD time = 0 );
    // ����ϵͳ��Ϣ         (ԭ���ñ���)
    void _AddSingleLineInfo( const char* szText, DWORD color, DWORD time = 0 );
    // �϶���Ϣ֧�ֻ���     (ԭ������Ϣ)
    void _AddMultiLineRiseInfo( const char* szText, DWORD color, DWORD time = 0, int nInfoIndex = -1,
        bool IsTopLevel = false, int eShowState = eShowFadein );
    // �϶���Ϣ�ӽӿ�       (ԭ�����Ϣ)
    void _AddRiseInfo( const char* szText, DWORD color, DWORD time = 0, int nInfoIndex = -1 ,
        bool IsTopLevel = false,int eShowState = eShowFadein );
    // ���϶���Ϣ��֧�ֶ��� ( New )
    void _AddMultiLineUnRiseInfo( const char* szText, DWORD color, DWORD time = 0, int nInfoIndex = -1,
        bool IsTopLevel = false, int eShowState = eShowFadein );
    // ���϶���Ϣ�ӽӿ�     ( New )
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
	DWORD		dwMoveStartTime;		// �ƶ���ʼʱ��
	DWORD		dwPauseStartTime;		// ͣ����ʼʱ��
	DWORD		dwLastRenderTime;		// ͣ����ʼʱ��
    int         m_nUnRiseLines;         // ����������Ϣ��������

private:
    friend class CScreenInfoManager;

public:
	CShowScreenText(void);
	~CShowScreenText(void);
};

CShowScreenText* GetShowScreenText();

extern bool		g_showPFErrorText;