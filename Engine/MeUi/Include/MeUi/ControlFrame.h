
#pragma once
#include "MeUi/ControlObject.h"

class UiRender;
class CSmartAniManage;
class CExpressionUpdater;
class ControlFrame : public ControlObject
{
public:
	typedef bool (*funOnClick)( OUT ControlObject* pSender );
	typedef bool (*funOnRBtnDown)( OUT ControlObject* pSender );
	typedef void (*funOnMouseMoveOn)( OUT ControlObject* pSender );
	typedef void (*funOnMouseMoveLevel)( OUT ControlObject* pSender );
	typedef void (*funOnFrameMove) ( ControlObject* pSender );
	typedef bool (*funRun)(void);
	typedef bool (*funRender)(void);
	typedef void (*funOnTab)(void);
	typedef bool (*funRunIndexedFrame)(int index);
	typedef bool (*funRenderIndexedFrame)(int index);
    typedef bool (*funOnDBClick)( OUT ControlObject* pSender );

public:	/*Virtual Function*/
	void Render();

	//void _renderCallback(bool bAlwaysRender);
	void Run();
	bool UseFocus()	{ return false; }
	bool PtInObject( const int nX, const int nY ,bool bCheckMsgHold = true);
	virtual bool IsMouseInUI( const int nX, const int nY );
	bool PtInOnlyFrame( const int x, const int y);
	void StartFlash( const int nFlashCount,
					const bool bAutoClose = false, const bool bFadeIn = false );
	int  GetArrayMode(){ return ((S_FrameData*)m_pstData)->m_nArrayMode; }
	bool IsChild( IN const ControlObject* pChild );
	void ReleaseUI();
	ControlObject*	FindControl( IN const char* szControlID,
									IN const char* szFrameID = NULL );
	ControlObject* FindFrame( IN const char *szFrameID );
	bool OnMouseMove( UINT nFlags, const int nX, const int nY );
	bool OnMouseWheel( bool bUp, const int nX, const int nY );
	bool OnLButtonDown( UINT nFlags, const int nX, const int nY );
	bool OnLButtonUp( UINT nFlags, const int nX, const int nY );
	bool OnLButtonDBClick( UINT nFlags, const int nX, const int nY );
	bool OnRButtonDown( UINT nFlags, const int nX, const int nY );
	bool OnRButtonUp( UINT nFlags, const int nX, const int nY );
	bool OnRButtonDBClick( UINT nFlags, const int nX, const int nY );
	bool OnMouseLeave();
	bool OnKeyDown( UINT nChar );
	bool OnKeyUp( UINT nChar );
	bool OnChar( UINT nChar );
    bool IsLButtonDrag(){ return m_bLButtonDrag; }

	enum EOnEscResponse{
		EscResponse_Normal,
		EscResponse_SkipMe,
		EscResponse_SkipAll,
	};

    enum ERenderType
    {
        EBeforeUIRender     = 0,
        EAfterUIRender,
        ERenderTypeMax
    };

public:
	//------- 载入文件    (By   at 2004-6-2)
	DWORD	LoadUIFormFile( IN const char* szFileName, IN ControlObject* pFather = NULL ,int index= -1);

	void		AddPosfixByIndex( int index, char* szID );
	DWORD	LoadUIFormUnit( IN const char* szZipFileName, IN const char* szUnitName, IN ControlObject* pFather = NULL );
	void	SetArrayMode( const int nMode ) { ((S_FrameData*)m_pstData)->m_nArrayMode = nMode; }

	void	SetRunFun( IN funRun pFun ) { m_pRun = pFun; }
	void	SetRenderFun( IN funRender pFun, const bool bBeforeRender = false );
	void	SetRenderNeedRedraw( IN funRender pFun, const bool bBeforeRender = false );
	void	SetIndexedFrameRunFun( IN funRunIndexedFrame pFun ) { m_pRunIndexedFrame = pFun; }
	void	SetIndexedFrameRenderFun( IN funRenderIndexedFrame pFun, const bool bBeforeRender );
	void	SetOnClickFun( IN funOnClick pFun ) { m_pOnClick = pFun; }
	void	SetOnRBtnDown( IN funOnRBtnDown pFun )	{ _pOnRBtnDown = pFun; }
	void	SetMouseMoveOn( IN funOnMouseMoveOn pFun) { _pOnMouseMoveOn = pFun; }
	void	SetMouseMoveLevel( IN funOnMouseMoveLevel pFun) { _pOnMouseMoveLevel = pFun; }
	void	SetOnTab( funOnTab pFun )	{ _pOnTab = pFun; }
	void	SetFrameMove( funOnFrameMove pFun)		{ _pFrameMove = pFun;}
    void    SetMouseDBClickFun( IN funOnDBClick pFun ) { m_pOnDBClick = pFun; }

	void	SetRunFun_2lua( const char* luaTable, const char* funName );
	void	SetRenderFun_2lua( const char* luaTable, const char* funName );
	void	SetOnClickFun_2lua( const char* luaTable, const char* funName );
	void	SetOnRBtnDown_2lua( const char* luaTable, const char* funName );
	void	SetMouseMoveOn_2lua( const char* luaTable, const char* funName );
	void	SetMouseMoveLevel_2lua( const char* luaTable, const char* funName );
	void	SetOnTab_2lua( const char* luaTable, const char* funName );
	void	SetFrameMove_2lua( const char* luaTable, const char* funName );

	// 创建
	void	Create( IN const RECT* pRect, const D3DCOLOR colBack = 0,
					IN funRun pRunFun = NULL,
					IN funRender pRenderFun = NULL );
// 	void	SetAllVisable( const bool bVisable);
// 	void	SetAllFadeVal( const int nMaxFade, const int nMinFade );
// 	void	SetAllBlendColor( const int nColor );

	void	AppendChild(ControlObject* pChild);
	void	RemoveChild(ControlObject* pChild);

    /** 是否使用Esc键退出。
    */
	void    enableEscKey( bool enable ) { _enableEscKey = enable; }

	virtual void SetEnable( bool b );

	std::vector<ControlFrame*>	m_vtChildFrame;
	void AddChildFrame(ControlFrame* pChild) { m_vtChildFrame.push_back(pChild); }
	void RemoveChildFrame(ControlFrame* pChild);

	virtual void SetFather(ControlObject* pFather);
	virtual void SetVisable( const bool bVisable);
	int GetIndex() const { return m_index; }
	char GetOnEscResponseType() const { return m_eOnEscResponseType; }
	void SetOnEscResponseType(char val) { m_eOnEscResponseType = val; }

	void SetSolidScale(bool val) { m_bSolidScale = val; }
	bool IsSolidScale() const { return m_bSolidScale; }

	typedef bool (*NeedTradeViewer)(ControlFrame* pFrame);
	static NeedTradeViewer NeedTradeViewerFunc;

    const std::vector< ControlObject* >* GetChildControlVec() { return &m_vtChild; }

public:
	void  SetWorking(RECT &rc);
private:
	bool m_bSettingWork;
	RECT m_ShowRect;
private:
	std::vector<ControlObject*>	m_vtChild;
	bool	m_bLButtonDrag;
	POINT	m_ptLBDOffset;
	//bool	m_bUseAutoClose;
	RECT	m_rcAutoClose;
	bool	m_bMouseLButtonDown;
	bool	m_bLControlDown;

	char	m_eOnEscResponseType;

	funRun	            m_pRun;
	funRender           m_pRender[ERenderTypeMax];            // 每帧都调用
	funRender           m_pRenderNeedRedraw[ERenderTypeMax];  // 只在重绘的时候调用
	funOnClick          m_pOnClick;
	funOnRBtnDown	    _pOnRBtnDown;
	funOnMouseMoveOn	_pOnMouseMoveOn;
	funOnMouseMoveLevel _pOnMouseMoveLevel;
	funOnTab			_pOnTab;
	funOnFrameMove		_pFrameMove;
    funOnDBClick        m_pOnDBClick;           // 增加双击响应回调     added by zhuomeng.hu		[11/26/2010]

	funRunIndexedFrame	    m_pRunIndexedFrame;
	funRenderIndexedFrame   m_pRenderIndexedFrame[ERenderTypeMax];

	std::string		_luaTableName;

	std::string		_funOnClickName;
	std::string		_funOnRBtnDownName;
	std::string		_funOnMouseMoveOnName;
	std::string		_funOnMouseMoveLevelName;
	std::string		_funOnOnFrameMoveName;
	std::string		_funRunName;
	std::string		_funRenderName;
	std::string		_funOnTabName;

    bool            _enableEscKey;

	int				m_index;

	ControlFrame*	m_pSecondFrame;
	bool			m_bSolidScale;
public:
	ControlFrame(void);
	~ControlFrame(void);

	virtual void ResetDevice();
public:
	void SetRedraw();
	CSmartAniManage*				GetUiAniManage() 
	{
		return m_pUiAniManage;
	}
	CSmartAniManage*				GetUiAniManageNotNULL() ;
	UiRender*						GetFrameRender() ;
	CExpressionUpdater*				GetExpressionUpdater() 
	{
		return m_pExpressionUpdater;
	}
	CExpressionUpdater*				GetExpressionUpdaterNotNULL() ;
private:
	UiRender*						m_pFrameRender;
	CSmartAniManage*				m_pUiAniManage;
	CExpressionUpdater*				m_pExpressionUpdater;
	bool							m_bRedraw;
	void SetFrameRender(UiRender* val) { m_pFrameRender = val; }
};
