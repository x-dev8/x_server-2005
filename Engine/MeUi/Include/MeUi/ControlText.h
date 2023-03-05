
#pragma once
#include "MeUi/ControlObject.h"
//#include "MeUi/ControlLabel.h"
#include "MeUi/IconManager.h"
#include <vector>
#include <usp10.h>
#include "MeUi/ControlScrollBar.h"
#include "UiDataParsing.h"




/*
	�µ�ControlText����:
	1,֧��Unicode,֧�ֶ������
	2,֧�ַǵȿ�����
				----   (2007.08.08)
*/

class ControlText : public ControlObject
{
public:
	typedef bool (*funOnButtonClick)( OUT ControlObject* pSender );
	typedef void (*funHyberClick)( OUT ControlObject* pSender, OUT const char* szData );
	typedef void (*funHyberRBtnDown)( ControlObject* pSender, const char* szName ,int nHyberType);

public:
	// ��ʼ��UI
	virtual void InitUIData( IN ControlObject* pFather, IN S_BaseData* pData );
	virtual bool PtInObject( const int nX, const int nY ,bool bCheckMsgHold = true);
	virtual bool IsMouseInUI( const int nX, const int nY );

	// ��Ⱦ
	virtual void Render();
	virtual void Run();

	virtual void SetRealRect( IN const RECT* prc );

public:
	// ����ƶ���Ϣ
	virtual bool OnMouseMove( UINT nFlags, const int nX, const int nY );
	// ������������Ϣ
	virtual bool OnLButtonDown( UINT nFlags, const int nX, const int nY );
	// �������ɿ���Ϣ
	virtual bool OnLButtonUp( UINT nFlags, const int nX, const int nY );
	virtual bool OnRButtonUp( UINT nFlags, const int nX, const int nY);

	virtual bool OnMouseWheel( bool bUp, const int nX, const int nY );
public:
	void	SetText( const std::string& szData, DWORD col = 0  ,UiCallbackDataArr* pBase = NULL);
	void	SetText( const int nNum, DWORD col = 0 ,UiCallbackDataArr* pBase = NULL);
	void	SetText( const CHAR* szText, DWORD col = 0 ,UiCallbackDataArr* pBase = NULL);
	void	SetTextW( const WCHAR* wText, DWORD col = 0 ,UiCallbackDataArr* pBase = NULL);
// 	virtual void	AddText( const CHAR* szText );
	void	AddTextW( const WCHAR* wText);
	void	AddNewLine( const WCHAR* wText, DWORD col = 0 ,UiCallbackDataArr* pBase = NULL);
	void	SetCurShowBeginLine( unsigned int nLine );

	virtual const char* GetText(char* pBuffer = NULL,int nBufferLength = 0);//���Ĭ��Ϊ�գ���ʹ�þ�̬�ִ����أ��ҳ������Ϊ10240
	const std::wstring&	GetTextWString();
	const WCHAR *		GetTextW();
	void	Create( IN const RECT* pRect, const D3DCOLOR colText );
    virtual void Clear();

public:
	void SetButtonClickFun( IN funOnButtonClick pFun )	{ m_pFunOnButtonClick = pFun; }
	void SetHyberClickFun( IN funHyberClick pFun )	{ m_pHyberClick = pFun; }
	void SetText_HyberClickFun_2lua( const char* luaTable, const char* funName );
	void	SetHyberRBtnDown( funHyberRBtnDown pFun)	{ m_pFunHyberRBtnDown = pFun; }

	void setDesIconTip( int nID );
	void setShowDesIconTip( bool show = true)  { _bIsDesIconTip = show; }
	void SetIsShowLine(bool bShow = true)		{ _bShowUnderLine = bShow;  }
	void setTip(const char* data);
	void setShowTip(bool show = true) { _bIsShowTip = show; }
	void SetSingleMaxTextCnt( int cnt )			{ _singleMaxTextCnt = cnt;	}
	void SetOffsetY( int oy );
	virtual	void DrawSelectTextForeGround();


public:
	
	struct STextData
	{
		std::wstring	str;		// �ı�����
		int				nTextureID;	// ��ͼID
		void*			pInfo;	// ���鶯������
		RECT			rc;			// ��Ч����
		int				nLine;		// �к�
// 		int				nBeginIndex;	// �ִ����ַ��ڱ��е�λ��ʼ
		STextData()
		{
			nTextureID = -1;
			pInfo = NULL;
			nLine = -1;
		}
	};
	struct SText 
	{
		SText()
		{
			type = eKeyEnd;
			col = 0xffffffff;
			m_pTipInfo = NULL;
			m_callBackData = NULL;
		}
		~SText()
		{
			if( m_pTipInfo == theIconInfoMouseTip.GetIconInfo() )
				theIconInfoMouseTip.Clear();
		}
		EKeyType type;	// ����
		DWORD	col;	// ��ɫ
		std::vector<STextData> vtTextData;
		S_TextTipInfo*   m_pTipInfo;	//tip��ʾ
		STextData* CheckPtInText( int x, int y );
		bool GetTextW( std::wstring *pString );
		bool GetTextA( std::string *pString );
		UiCallbackDataBase*		m_callBackData;
		bool			IsImgType(){return (type == eKeyImg )|| (type == eKeyChatExp );}
	};

public:
	// ����"\n"
	int			GetMaxTextHeight() const { return m_nMaxTextHeight; }
	void		SetMaxTextHeight(int val) { m_nMaxTextHeight = val; }
	bool		WordBreak( std::wstring* pOutText, const WCHAR* wInText );
// 	EKeyType	GetTextData( const std::wstring& strString, unsigned int *pnOff,
// 							std::wstring* pstrText, DWORD *dwKey );
	bool		CalculatePoint();
	EKeyType	PtInHyber( const int nX, const int nY );

	bool		CalculatePointEx();  //## add by pyj [20100829] ʹ��NewFont ��ʱ��ʹ����

	virtual bool		ReCalculatePoint();
	bool		CheckDrawMode();
	bool		CPtoX( const std::wstring &str, int nCP, BOOL bTrail, int *pX,SCRIPT_STRING_ANALYSIS* localAnalysis = NULL);
	bool		XtoCP(const std::wstring &str,
						int nX, int *pCP, int *pnTrail, BOOL *pbEnd );
	bool		MoveTextDataPos( int nLine, int nEndIndex, int nOffsetX, int nOffsetY );

	int			GetTextHeight() { return m_nTextHeight; }
	int			GetTextWidth() { return m_nTextWidth; }

	void		SetColUrl(DWORD val) { m_colUrl = val; }
	DWORD  GetColUrl() { return m_colUrl; } //add by yanli  2010-8-11
    int         GetMaxLines(){return m_nMaxLines;}
    int         GetShowLine();

	void			EnableShortcutKey(bool b) { m_bEnableShortcutKey = b; }
// 	void			ShowScrollBar(int b) { m_bShowScrollBar = b; }
	void			SetUIScrollBlend( const int nBlend ) 
	{	
		m_UIScroll.SetUIScrollBarBlend( nBlend );
	}
	void			SetScrollHeight( const int nHeight )
	{
		m_UIScroll.SetScrollHeight( nHeight );	
	}
	void	SetScrollBarEnable( bool bEnable = true )		{ m_bOldScrollBarEnabled = bEnable; m_UIScroll.SetEnable(bEnable); }

	bool			IsSingleLine(){return ((S_TextData*)m_pstData)->m_bSingleLine;}
	
	//added by zhuomeng.hu		[9/9/2010]
	void				ScrollToTheBegin();
	void				ScrollToTheLast();
    int                 GetScrollValue();
    void                SetScrollValue( int nValue );
	bool				IsScrollBarVisable();
	ControlScrollBar*	GetScrollBar();
    void                SetMaxFontWidth( int nWidth );

	void			RemoveSyntaxFlag(DWORD val) { m_nSyntaxFlag &= (~val); }
	void            RemoveSyntaxUnderLine(DWORD val){m_nSyntaxUnderLine &= (~val);} //ȡ���»���

	int             GetOffsetHeight(){return m_nOffsetHeight;}  //����м��
	void            SetNpcMouseOnColor(DWORD dwColor){m_colUrlMouseOn = dwColor;}  //����Npc����ƶ���ɫ
protected:
// 	std::wstring		m_strSrcText;	// ԭʼ�ı�
	std::vector<SText>	m_vtText;		// �ı�����
	SText&				GetLastText();
	STextData*			GetLastTextData();
	STextData*			GetLastDataByY(int nY);
	int					GetCharacterCount();
	void				ClearInvalidPtInText();
	int					m_nOffsetHeight;// �м��
	DWORD				m_colUrl;		// URL��ɫ
	DWORD				m_colUrlMouseOn;
	int					m_nMaxLines;	// ����
	int					m_nCurShowStartLine;		// ��ǰ��ʾ��һ��
	unsigned int		m_nCurShowMaxLine;		// ��ǰ��ʾ���һ��
	int					m_nCurLineYPos;
	DWORD				m_dwDrawFlags;
	int					m_nRenderOffsetY;//����text�ؼ��ı���ͼ�����б߿���Ҫ��y�����һЩƫ���Ա������帲���ڱ���ͼ�ı߿���
	int					m_nTextHeight;
	int					m_nTextWidth;
	int					m_nMaxTextHeight;
	bool				m_bSingleLine;//��ǩ������ǩ����ζ��û�й��������������ֻ�ܱ���ʼ����������;�ı�
	SCRIPT_STRING_ANALYSIS	m_Analysis;  // Analysis for the current string
	bool			m_bDraging;
    int                 m_nMaxFontWidth;        // Text�ؼ������ֶ������ı���ʾ���     added by zhuomeng.hu		[11/10/2010]
protected:
	struct SSelect 
	{
		SSelect()
		{
			Empty();
		}
		enum {
			eForward = 0,
			eBackward,
			eNone
		};
		inline bool IsEmpty()
		{
			return (nStartIndex == nEndIndex) && (pStartLine == pEndLine);
		}
		inline void Empty()
		{
			pStartLine = 0;
			pEndLine = 0;
			nStartIndex = 0;
			nEndIndex = 0;
			nStartPos = 0;
			nEndPos = 0;
			eOrder = eNone;
		}
		bool IsStartLine(STextData* pTextData)
		{//
			if (eOrder == eNone)
			{
				if (pTextData == pStartLine && pTextData == pEndLine)
				{
					if (nStartIndex < nEndIndex)
					{
						eOrder = eForward;
						return true;
					}
					else
					{
						eOrder = eBackward;
						return true;
					}
				}
				if (pTextData == pStartLine)
				{
					eOrder = eForward;
					return true;
				}
				if (pTextData == pEndLine)
				{
					eOrder = eBackward;
					return true;
				}
			}
			else
			{
				if (eOrder == eForward)
				{
					return pStartLine == pTextData;
				}
				else
				{
					return pEndLine == pTextData;
				}
			}
			return false;
		}
		inline int GetStart()
		{
			assert(eOrder != eNone);
			if (eOrder == eForward)
			{
				return nStartIndex;
			}
			else
			{
				return nEndIndex;
			}
		}
		inline int GetEnd()
		{
			assert(eOrder != eNone);
			if (eOrder == eForward)
			{
				return nEndIndex;
			}
			else
			{
				return nStartIndex;
			}
		}
		inline int GetStartPos()
		{
			assert(eOrder != eNone);
			if (eOrder == eForward)
			{
				return nStartPos;
			}
			else
			{
				return nEndPos;
			}
		}
		inline int GetEndPos()
		{
			assert(eOrder != eNone);
			if (eOrder == eForward)
			{
				return nEndPos;
			}
			else
			{
				return nStartPos;
			}
		}
		inline bool IsEndLine(STextData* pTextData)
		{
			if (eOrder == eForward)
			{
				return pTextData == pEndLine;
			}
			else
			{
				return pTextData == pStartLine;
			}
		}
		STextData*		pStartLine;
		STextData*		pEndLine;
		int		nStartIndex;
		int		nEndIndex;
		int		nStartPos;
		int		nEndPos;
		char	eOrder;
	};

	SSelect			m_stSelect;
	virtual void	SetCurIndex( int nIndex,STextData* pCurLineData);
	DWORD			GetDefaultColor();
private:
	void SetShowTips();

protected:
	funOnButtonClick	m_pFunOnButtonClick;
	funHyberClick		m_pHyberClick;
	funHyberRBtnDown	m_pFunHyberRBtnDown;
	//ICON_INFO_STRUCT	m_DescriptionTip; //��iconһ����tip����
	//S_IconInfoBase* m_pkDescriptionTip;

	bool	_bIsDesIconTip;
	bool	_bShowUnderLine;	//�����Ƿ���ʵ����������ĺ��ߡ��ᵽ�ϲ���������ơ�������Ϊ�����������ʧ��ʱ��ı��ֵ
	S_TextTipInfo		TipInfo;	//tip ��ʾ
	bool	_bIsShowTip;
	int		_singleMaxTextCnt;	//���ڵ�text������ʾ��һ�е�ʱ�������ʾ������ ��������Ļ��� ... ���� (ֻ���ڵ���)

	std::string		_luaTableName;
	std::string		_funHyberClick;

	DWORD				m_dwDefaultColor;

	bool			m_bOldScrollBarEnabled;
	bool			m_bEnableShortcutKey;
// 	bool			m_bShowScrollBar;
	ControlScrollBar	m_UIScroll;

	bool			RetriveAnalysis(const std::wstring &str );
	virtual	void	_setTextW(std::wstring& strSrcText,UiCallbackDataArr* pBase);
	virtual	void	ParseText( std::wstring &strText ); //add by yanli  2010-8-11
	void			ParseTextNew( std::wstring &strText );//add by yanli  2010-8-11
// 	void			ParseTextOld( std::wstring &strText ); //add by yanli  2010-8-11
	bool			IsScrollBarShow();
	int				RefeashByScrollBar();
	int				GetLineTop(int nLine);
	SText*			m_PtInText;	
	STextData*		m_PtInTextData;
	DWORD			m_nSyntaxFlag;
	DWORD           m_nSyntaxUnderLine;  //�����Ƿ���Ҫ��ʾ�»���
	bool			m_bEnableSelected;
	UiCallbackDataArr*			m_CurrCallbackDataArr;
	int				m_nCallbackDataArrIndex;
public:
	const std::string& operator=( const std::string& szData );
	const int& operator=( const int& nNum );

public:
	ControlText(void);
	virtual ~ControlText(void);

	virtual void ResetDevice();

	static DWORD	s_LISTSELECTON_COLOR;
	static DWORD	s_CHAT_HYBER_DOWNLINE_COLOR;
	static DWORD	s_PathFindLinker_COLOR;
	static DWORD	s_CHAT_PLAYERNAME_COLOR;
};

