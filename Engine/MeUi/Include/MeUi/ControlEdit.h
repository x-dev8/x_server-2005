#pragma once
#include "MeUi/ControlObject.h"
#include <usp10.h>

#include "MeUi/ControlText.h"


class ControlEdit : public ControlText
{
public:
	typedef void (*funOnEnter)( OUT ControlObject* pSender, OUT const char *szData );
	typedef void (*funOnTab)( OUT ControlObject* pSender, OUT const char* szData);
	typedef void (*funOnLBtnDown)( ControlObject* pSender, const char* szData );
	typedef void (*funOnLBtnUp)( ControlObject* pSender, const char* szData );
	typedef void (*funDelByte)( ControlObject* pSender, int begin, int end );//删除的开始位置和结束位置
	typedef void (*funOnTextChanged)( OUT ControlObject* pSender, OUT const char *szData );

public:
	// 初始化UI
	virtual void	InitUIData( IN ControlObject* pFather, IN S_BaseData* pData );
	// 渲染
	virtual void	Render();

	void			DrawFlashBar();
	//
	void Create( IN const RECT* pRect, const D3DCOLOR colText = 0xffffffff,
				const bool bSingleLine = true, const bool bReadOnly = true,
				const D3DCOLOR colBack = 0,
				IN funOnEnter pCallbackFun = NULL );

public:
	// 鼠标移动消息
	virtual bool OnMouseMove( UINT nFlags, const int nX, const int nY );
	// 鼠标左键按下消息
	virtual bool OnLButtonDown( UINT nFlags, const int nX, const int nY );
	//
	virtual bool OnLButtonUp( UINT nFlags, const int nX, const int nY );
	// 鼠标左键双击消息
	virtual bool OnLButtonDBClick( UINT nFlags, const int nX, const int nY );
	// 字符消息
	virtual bool OnChar( UINT nChar );
	// 键盘按下消息
	virtual bool OnKeyDown( UINT nChar );

public:
	bool			addChar( WCHAR wChar );
	bool			DelByte( bool bBack );
	void			addText( const char* text );

private:
	virtual	void	_setTextW(std::wstring& strSrcText,UiCallbackDataArr* pBase);
	virtual void	ParseText( std::wstring &strText );
	bool			GetTextPosByTotalIndex(STextData*& pTextData,int& index,int nCharIndex);
	bool			GetCurrPos(int& nCurrPos);
	bool			RetriveTextDataFromLinePos(STextData*& pTextData,int& index,int nLine, int nPosX);
	virtual	void	DrawSelectTextForeGround();
    virtual void    Clear();                    // 屏蔽基类的接口，是因为Edit调用Text的Clear接口时会当机

public:
	void SetEnterFun( IN funOnEnter pFun )	{ m_pOnEnter = pFun; }
	void SetTabFun( IN funOnTab pFun )		{ _funOnTab = pFun; }
	void SetLBtnDownFun( funOnLBtnDown pFun ) { _funOnLBtnDown = pFun; }
	void SetLBtnUpFun( funOnLBtnUp pFun )	{ _funOnLBtnUp = pFun; }
	void SetDelByteFun( funDelByte pFun)	{ _funOnDelByte = pFun; }
	void SetTextChangedFun( IN funOnTextChanged pFun )	{ _funOnTextChanged = pFun; }

	void SetEnterFun_2lua( const char* luaTable, const char* funName );
	void SetTabFun_2lua( const char* luaTable, const char* funName );
	void SetLBtnDownFun_2lua( const char* luaTable, const char* funName );
	void SetLBtnUpFun_2lua( const char* luaTable, const char* funName );
	void SetDelByteFun_2lua( const char* luaTable, const char* funName );

	bool IsReadOnly(){ return ((S_EditData*)m_pstData)->m_bReadOnly; }
	void SetIsNumber( const bool b ) { ((S_EditData*)m_pstData)->m_bIsNumber = b; }
	void SetMaxLength( const int n ){ m_nMaxLength = n; }
	void SetReadOnly( const bool b ){ ((S_EditData*)m_pstData)->m_bReadOnly = b; }
	void SetIsPassword( bool b ){ ((S_EditData*)m_pstData)->m_bPassword = b; }
	bool IsPassword() { return ((S_EditData*)m_pstData)->m_bPassword; }
	void setNoPitchOn(){}
	void SetMaxCnt(int nMax)	{ m_nMaxLength = nMax; }
	void setDefaultColor(D3DCOLOR color)		{ m_dwDefaultColor = color; }

	void SetNumberLimit(bool limit, int min, int max)
	{
		m_bNumberLimit = limit;
		m_nMinValue = min;
		m_nMaxValue = max;
	}

	void SetRightAlign(bool b) { m_bRightAlign = b; }
	bool IsRightAlign() const  { return m_bRightAlign; }
	bool IsForceNewLine() const { return m_bForceNewLine; }
	void SetForceNewLine(bool val) { m_bForceNewLine = val; }
	void SetHyberLimit() { m_bHyberLimit = true; }

public:
	virtual void	SetCurIndex( int nIndex,STextData* pCurLineData );
	void	ReCalStartIndex();
	void	ReCalStartShowLine();

	void	CopyToClipboard( const char *szText );
	char*	GetTextFromClipboard();
	void	DataChanged();
// 	bool	XtoCP( int nX, int *pCP, int *pnTrail );

public:
	void	OnEnter( );
	bool	OnTab( IN const char* szData );	//return bool: true: 表示回掉函数调用 return消息
	bool	GetSelectAllAfterTab() const { return m_bSelectAllAfterTab; }
	void	SetSelectAllAfterTab(bool val) { m_bSelectAllAfterTab = val; }
	void	SelectAllContext();
	void	ClearSelected();
	static void editVisibleChange(ControlObject* pUIObject);
private:
// 	std::string		m_strMBText;
	DWORD			m_dwFlashBar;
	bool			m_bDrawFlashBar;
	bool			m_bSelectAllAfterTab;
	int				m_nStartIndex;//单行eidt当显示长度不够的时候显示的起始位置
	int				m_nCurIndex;
	STextData*		m_pCurLineData;
	int		GetTolalIndex(int nIndex,STextData* pCurLineData);
	void		SetCurIndex1( int nTotalIndex);
	void		SetShowTips();
	funOnEnter		m_pOnEnter;
	funOnTab		_funOnTab;
	funOnLBtnDown	_funOnLBtnDown;
	funOnLBtnUp		_funOnLBtnUp;
	funDelByte		_funOnDelByte;
	funOnTextChanged _funOnTextChanged;
	int				m_nMaxLength;	//允许输入的最大字符数量
// 	D3DCOLOR		m_dwColor;		//默认输入的color 以前是从编辑器里读的 现在需要程序改变 所以如果设置这个值 输入框字体颜色以这个优先
// 										//如果这个值为0时 以编辑器为准。


	std::string		_luaTableName;

	std::string		_funOnEnterName;
	std::string		_funOnTabName;
	std::string		_funOnLBtnDownName;
	std::string		_funOnLBtnUpName;
	std::string		_funDelByteName;

	int				m_nMinValue;
	int				m_nMaxValue;
	bool			m_bNumberLimit;

	bool			m_bRightAlign;
	bool			m_bForceNewLine;
	bool			m_bHyberLimit;	//是否超链接[]限制 lrt

protected:
	STextData*		GetNextTextData(STextData* pCurLineData);
	virtual bool		ReCalculatePoint();
	std::wstring&	GetSelectString();
public:
	const std::string& operator=( const std::string& stText );
	const int& operator=( const int& nNum );

public:
	ControlEdit(void);
	virtual ~ControlEdit(void);
};

