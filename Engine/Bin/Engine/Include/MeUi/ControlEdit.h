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
	typedef void (*funDelByte)( ControlObject* pSender, int begin, int end );//ɾ���Ŀ�ʼλ�úͽ���λ��
	typedef void (*funOnTextChanged)( OUT ControlObject* pSender, OUT const char *szData );

public:
	// ��ʼ��UI
	virtual void	InitUIData( IN ControlObject* pFather, IN S_BaseData* pData );
	// ��Ⱦ
	virtual void	Render();

	void			DrawFlashBar();
	//
	void Create( IN const RECT* pRect, const D3DCOLOR colText = 0xffffffff,
				const bool bSingleLine = true, const bool bReadOnly = true,
				const D3DCOLOR colBack = 0,
				IN funOnEnter pCallbackFun = NULL );

public:
	// ����ƶ���Ϣ
	virtual bool OnMouseMove( UINT nFlags, const int nX, const int nY );
	// ������������Ϣ
	virtual bool OnLButtonDown( UINT nFlags, const int nX, const int nY );
	//
	virtual bool OnLButtonUp( UINT nFlags, const int nX, const int nY );
	// ������˫����Ϣ
	virtual bool OnLButtonDBClick( UINT nFlags, const int nX, const int nY );
	// �ַ���Ϣ
	virtual bool OnChar( UINT nChar );
	// ���̰�����Ϣ
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
    virtual void    Clear();                    // ���λ���Ľӿڣ�����ΪEdit����Text��Clear�ӿ�ʱ�ᵱ��

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
	bool	OnTab( IN const char* szData );	//return bool: true: ��ʾ�ص��������� return��Ϣ
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
	int				m_nStartIndex;//����eidt����ʾ���Ȳ�����ʱ����ʾ����ʼλ��
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
	int				m_nMaxLength;	//�������������ַ�����
// 	D3DCOLOR		m_dwColor;		//Ĭ�������color ��ǰ�Ǵӱ༭������� ������Ҫ����ı� ��������������ֵ �����������ɫ���������
// 										//������ֵΪ0ʱ �Ա༭��Ϊ׼��


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
	bool			m_bHyberLimit;	//�Ƿ�����[]���� lrt

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

