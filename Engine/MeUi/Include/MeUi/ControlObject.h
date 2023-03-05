
#pragma once
#include "MeUi/ControlData.h"
#include "MeUi/FontManager.h"
#include "LuaPlus/LuaPlus.h"
//#include "FuncPerformanceLog.h"
//#include "MeFontNew/MeFont.h"

#include <fstream>

extern "C" 
{
#include "Luaplus/lua/lua.h"
#include "Luaplus/lua/lauxlib.h"
#include "Luaplus/lua/lualib.h"
#include "tolua++\tolua++.h"
}

#include <usp10.h>

//#include "LuaScript.h"
using namespace LuaPlus;

#define FONT_OFFSET_X	1
#define FONT_OFFSET_Y	0

#define OUT	/*输出参数*/
#define IN	/*输入参数*/

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)	{if(p) delete p; p=NULL;}
#endif

extern void UiLogInfo( const char* szInfo );

#define MESSAGE_BOX(sz) UiLogInfo(sz);

#define SHOWTIPOFCAPTION( pui, bshow) \
	if( pui ) \
	{\
		pui->SetShowTip( bshow ); \
		if( bshow && pui->GetData() ) \
		{			\
			pui->setTip( pui->GetData()->m_szCaption );\
		} \
	}
		
	

//#ifndef MESSAGE_BOX
//#ifdef _DEBUG
//#define MESSAGE_BOX(sz){if(::MessageBox(NULL,sz,"错误!",MB_ABORTRETRYIGNORE)!=IDIGNORE){__asm{int 3}}}
//#else
//#define MESSAGE_BOX(sz)
//#endif
//#endif

#define UI_FADE_SPEED	0.4f


enum BtnState
{
	MouseEnable,
	MouseOn,
	MouseDown,
	MouseDisable,
};


extern LuaStateOwner state;
void print_error( const char* err );
//extern ControlComposeRender 
class ControlFrame;
class ControlObject : public MeCommonAllocObj<ControlObject> 
{
public:
    typedef bool (*funOnMsgProc)( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed ); 
	typedef bool (*funOnMsgProc2)( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed,ControlObject* pObject ); 
    typedef void (*funOnVisibleChanged)( ControlObject* pUIObject ); 


public:	/*Virtual Function*/
	virtual const char* GetAlias() { return ""; }
	// 渲染
	virtual void Render();
	// 运行
	virtual void Run();
	// 释放
	virtual void ReleaseUI();
	// 初始化数据
	virtual void InitUIData( IN ControlObject* pFather, IN S_BaseData* pData );
	// 使用焦点
	virtual bool UseFocus();
	// 是否需要Render
	virtual bool IsNeedRender();
	// 坐标是否在本身内
	virtual bool PtInObject( const int nX, const int nY ,bool bCheckMsgHold = true);
	virtual bool IsMouseInUI( const int nX, const int nY );
	virtual bool PtInObject( const RECT& rc, const int nX, const int nY);
	// 设置是否可见/可用
	virtual void SetVisable( const bool bVisable);
	// 闪烁
	virtual void StartFlash( const int nFlashCount,
							const bool bAutoClose = false, const bool bFadeIn = false );

	//设置闪烁速度
	virtual void SetFlashSpeed( float fFlashSpeed ){ m_fFlashSpeed = fFlashSpeed; }
	//
	virtual void SetRealRect( IN const RECT* prc );
	// 消息
	virtual bool MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed = false );
	// 查找子控件
	virtual ControlObject*	FindControl( IN const char* szControlID,
										IN const char* szFrameID = NULL)		{ return NULL;  }
	// 查找子框架
	virtual ControlObject* FindFrame( IN const char *szFrameID )				{ return NULL;  }
	// 取得排列模式
	virtual int	 GetArrayMode()													{ return 0;		}
	// 是否是本身子控件
	virtual bool IsChild( IN const ControlObject* pChild )						{ return false; }
	// 鼠标移动消息
	virtual bool OnMouseMove( UINT nFlags, const int nX, const int nY )			{ return false; }
	virtual bool OnMouseLeave( )												{ return false; }
	// 鼠标滚轮消息
	virtual bool OnMouseWheel( bool bUp, const int nX, const int nY )			{ return false; }
	// 鼠标左键按下消息
	virtual bool OnLButtonDown( UINT nFlags, const int nX, const int nY )		{ return false; }
	// 鼠标右键按下消息
	virtual bool OnRButtonDown( UINT nFlags, const int nX, const int nY )		{ return false; }
	// 鼠标左键松开消息
	virtual bool OnLButtonUp( UINT nFlags, const int nX, const int nY )			{ return false; }
	// 鼠标右键松开消息
	virtual bool OnRButtonUp( UINT nFlags, const int nX, const int nY )			{ return false; }
	// 鼠标左键双击消息
	virtual bool OnLButtonDBClick( UINT nFlags, const int nX, const int nY )	{ return false; }
	// 鼠标右键双击消息
	virtual bool OnRButtonDBClick( UINT nFlags, const int nX, const int nY )	{ return false; }
	// 键盘按下消息
	virtual bool OnKeyDown( UINT nChar )										{ return false; }
	// 键盘松开消息
	virtual bool OnKeyUp( UINT nChar )											{ return false; }
	// 字符消息
	virtual bool OnChar( UINT nChar )											{ return false; }
	// 窗口是否被拖拽
	virtual bool IsLButtonDrag(){ return false; }

	/*virtual void SetButtonClickFun_2lua( const char* luaTable, const char* funName )		{ return; }
	virtual void SetButtonMouseOnFun_2lua( const char* luaTable, const char* funName )		{ return; }	
	virtual void SetCheckFun_2lua( const char* luaTable, const char* funName )				{ return; }
	virtual void SetChangeFun_2lua( const char* luaTable, const char* funName )				{ return; }
	virtual void SetShowListFun_2lua( const char* luaTable, const char* funName )			{ return; }
	virtual void SetEnterFun_2lua( const char* luaTable, const char* funName )				{ return; }
	virtual void SetTabFun_2lua( const char* luaTable, const char* funName )				{ return; }
	virtual void SetLBtnDownFun_2lua( const char* luaTable, const char* funName )			{ return; }
	virtual void SetLBtnUpFun_2lua( const char* luaTable, const char* funName )				{ return; }
	virtual void SetDelByteFun_2lua( const char* luaTable, const char* funName )			{ return; }
	virtual void SetRunFun_2lua( const char* luaTable, const char* funName )				{ return; }
	virtual void SetRenderFun_2lua( const char* luaTable, const char* funName )				{ return; }
	virtual void SetOnClickFun_2lua( const char* luaTable, const char* funName )			{ return; }
	virtual void SetOnRBtnDown_2lua( const char* luaTable, const char* funName )			{ return; }
	virtual void SetMouseMoveOn_2lua( const char* luaTable, const char* funName )			{ return; }
	virtual void SetMouseMoveLevel_2lua( const char* luaTable, const char* funName )		{ return; }
	virtual void SetOnTab_2lua( const char* luaTable, const char* funName )					{ return; }
	virtual void SetFrameMove_2lua( const char* luaTable, const char* funName )				{ return; }
	virtual void SetSelectChangeFun_2lua( const char* luaTable, const char* funName )		{ return; }
	virtual void SetRBClickFun_2lua( const char* luaTable, const char* funName )			{ return; }
	virtual void SetShiftRBClickFun_2lua( const char* luaTable, const char* funName )		{ return; }
	virtual void SetShiftLBClickFun_2lua( const char* luaTable, const char* funName )		{ return; }
	virtual void SetLDBClickFun_2lua( const char* luaTable, const char* funName )			{ return; }
	virtual void SetHyberClickFun_2lua( const char* luaTable, const char* funName )			{ return; }
	virtual void SetHyberRBtnDown_2lua( const char* luaTable, const char* funName )			{ return; }
	virtual void SetHyberItemClick_2lua( const char* luaTable, const char* funName )		{ return; }
	virtual void SetDrawInfoFun_2lua( const char* luaTable, const char* funName )			{ return; }
	virtual void SetPlaySoundFun_2lua( const char* luaTable, const char* funName )			{ return; }
	virtual void SetPicClickFun_2lua( const char* luaTable, const char* funName )			{ return; }
	virtual void SetOnMouseOn_2lua( const char* luaTable, const char* funName )				{ return; }
	virtual void SetOnMouseLeave_2lua( const char* luaTable, const char* funName )			{ return; }
	virtual void SetOnLDBClickFun_2lua( const char* luaTable, const char* funName )			{ return; }
	virtual void SetText_HyberClickFun_2lua( const char* luaTable, const char* funName )			{ return; }*/

	virtual void FocusIn() {}
	virtual void FocusOut() {}

public:
	// 取得绝对矩形
	void	GetRealRect( OUT RECT* prc );
	void    GetRectSize(OUT RECT* prc);
	// 得到控件ID
	char*	GetControlID(){ return m_pstData->m_szID;}
	// 得到控件类型
	int		GetControlType(){ return m_pstData->m_nType; }
	//
	int		GetFontSize(){ return m_pstData->m_nFontSize; }
	//
	int		GetFontIndex(){ return m_nFontIndex; }
//	void	SetFontIndex(int nIndex)		{ m_nFontIndex = nIndex; }
	void	SetFont( const ControlObject* pSrc );
	//
	COLORREF GetFontColor(){ return m_pstData->m_colFont; }
	// 取得宽度
	int		GetWidth(){ return m_nWidth; }
	// 取得高度
	int		GetHeight(){ return m_nHeight; }
	// 设置当前显示图片
	bool	SetPic( IN S_BaseData::S_Pic *pPic, bool bCoverData = false );
	//
	void	SetPos( const int nX, const int nY, bool bReal = true );
	// 设置X坐标
	void	SetXPos( const int nX );
	// 设置Y坐标
	void	SetYPos( const int nY );
    // 设置宽度
    virtual void SetWidth( const int nW );
    // 设置高度
    virtual void SetHeight( const int nH );
	// 设置是否被覆盖了
	void	SetCovered( const bool bCovered ){ m_bCovered = bCovered; }
	// 是否可见可用
	bool	IsVisable(){ return m_bVisable; }
	// 是否被覆盖
	bool	IsCovered(){ return m_bCovered; }
	// 是否被覆盖
	bool	IsBeCovered( IN ControlObject* pCover );
	// 激活
	void	SetActivate( const bool bActivate = true );
	bool	IsActivated();
	// 移动
	void	MoveTo( const int nX, const int nY );
	bool	IsMoving() { return m_bMoving; } //lrt 获取是否在移动中
	//
	void	SetMsgProcFun( IN funOnMsgProc pFun ){ m_pOnMsgProc = pFun; }
	void	SetMsgProcFun2( IN funOnMsgProc2 pFun ){ m_pOnMsgProc2 = pFun; }
    //
    void    SetOnVisibleChangedFun( IN funOnVisibleChanged pFun ) { m_pOnVisibleChanged = pFun; }
	funOnVisibleChanged    GetOnVisibleChangedFun( ) { return m_pOnVisibleChanged ; }
	//
	void	SetMsgHoldup( const bool b ){ m_bMsgHoldup = b; }
	//
	bool	IsMsgHoldup(){ return m_bMsgHoldup; }
	//
	void	SetBackPicZValue( const float fZ ){ m_fBackPicZ = fZ; }
	//
	void	SetBackColor( D3DCOLOR col, bool bFrame = false ){ m_colBackColor = col; m_bDrawFrame = bFrame; }
	D3DCOLOR GetBackColor() { return m_colBackColor; }
	//设置 Blt时候的
	void	SetBlendColor( int col ) { m_nFadeCurColorA = col; }
	int		GetBlendColor( void )	{ return m_nFadeCurColorA; }
	//
	bool	PlaySound();
	//
	void	SetFadeInval( bool bInval );
	bool	IsFadeInval();
	void	SetMaxMinFade( const int nMaxFade, const int nMinFade );
	void	SetPicName( const char* szPath );
	S_BaseData::S_Pic* GetPic( );
	S_BaseData* GetData()			{ return m_pstData; }

	void	SetAllVisableDlg( bool bAllVisable = true)			{ m_bAllVisable = bAllVisable; }
	bool	GetAllVisableDlg() const							{ return m_bAllVisable;		   }
	/*{ 
		if(m_pstPic) strncpy( m_pstPic->m_szPicName, szPath.c_str(), 128 );
	}*/
	//	void	SetCaption(char *szText) { if(!szText) strcpy(m_pstData->m_szCaption, szText);}
	//
	virtual void SetEnable( bool b );
	bool IsEnable(){ return m_bEnable; }

	void SetSkipAllMsg( bool bSkip ){ m_bSkipMsg = bSkip; }
	bool IsSkipAllMsg(){ return m_bSkipMsg; }

	void SetRenderTextWithZ( bool bZ ){ m_bRenderTextWithZ = bZ; }
	bool GetRenderTextWithZ(){ return m_bRenderTextWithZ; }

    void SetAlpha( float fAlpha );  // 增加Alpha    added by zhuomeng.hu		[11/5/2010]
    float GetAlpha();

// 	void SetLostFocusPassive(bool val) { m_bLostFocusPassive = val; }
// 	bool CanLostFocusPassive() const { return m_bLostFocusPassive; }

protected: // Tip 相关
	virtual const class S_IconInfoBase* GetTipPointer() const{ return NULL; }
	void CheckTipAndClear();

public:
	// 画图
	void 	BitBlt( IN OUT int* pPicId,
					IN const char* szPicName,
					float nDstX, float nDstY,
					float nDstWidth, float nDstHeight,
					int nSrcX, int nSrcY,
					int nSrcWidth, int nSrcHeight,
					int nDrawMode,
					D3DCOLOR col = 0xffffffff );
	// 得到父区域
	void	GetFatherRect( OUT RECT* prc );
	ControlFrame * GetFrameFather() const { return m_pFrameFather; }

	virtual void SetFather(ControlObject* pFather);
	ControlObject* GetFather(){ return m_pFather; }

    void  setRenderFlag( DWORD flag ) { _renderFlag = flag; }
    DWORD getRenderFlag() const { return _renderFlag; }

	void SetScreenPos(int x, int y);
	void SetScreenPos( float x, float y );

	HDC GetFontHDC() { return m_hDC; }

	bool	IsFadeInorFadeOut() const { return m_bFadeInorFadeOut; }
	void	SetFadeInorFadeOut(bool val) { m_bFadeInorFadeOut = val; }
	int		GetFadeCurColorA() const { return m_nFadeCurColorA; }
	void	SetFadeCurColorA(int val) { m_nFadeCurColorA = val; }
	float	GetFadeSpeed() const { return m_FadeSpeed; }
	void	SetFadeSpeed(float val) { m_FadeSpeed = val; }

public:
	bool			m_bNeedRelease;				// 是否需要释放资源
	std::string		m_strSound;					// 声音

	S_BaseData::S_Pic	*m_pstPic;				// 当前图片
	// 宽高
	int		m_nWidth, m_nHeight;
	int		m_nLeftW, m_nLeftH;
	int		m_nTopW, m_nTopH;
	int		m_nRightW, m_nRightH;
	int		m_nBottomW, m_nBottomH;
	int		m_nLeftTopW, m_nLeftTopH;
	int		m_nRightTopW, m_nRightTopH;
	int		m_nLeftBottomW, m_nLeftBottomH;
	int		m_nRightBottomW, m_nRightBottomH;
	int		m_nMiddleW, m_nMiddleH;

protected:
    funOnMsgProc	m_pOnMsgProc;
	funOnMsgProc2	m_pOnMsgProc2;
    funOnVisibleChanged	m_pOnVisibleChanged;

	ControlObject	*m_pFather;					// 父控件
	ControlFrame	*m_pFrameFather;					// 根节点控件
	S_BaseData		*m_pstData;					// 控件数据
	std::string		m_strBackPicName;			// 当前背景图片名
	int				m_nPicId;					// 当前背景图片ID
	unsigned long	m_nQuadId;					// 当前背景图片绘制产生的quadid
	int				m_nFontIndex;				// 字体索引值
	HDC				m_hDC;
	bool			m_bVisable;					// 是否可见
	bool			m_bCovered;					// 是否被覆盖
	D3DCOLOR		m_colBackColor;				// 背景颜色(当没有图片时显示)
	bool			m_bDrawFrame;				// 是否画边框
	bool			m_bMsgHoldup;
	float			m_fBackPicZ;
	bool			m_bRenderTextWithZ;
	bool			m_bSkipMsg;
	// 闪动
	float	m_fFlashSpeed;
	int		m_nFlashCurCount;
	int		m_nFlashCount;
	int		m_nFlashCurColorA;
	bool	m_bFlashedAutoClose;
	bool	m_bFlashFade;
	DWORD	m_dwFlashStartTime;
	// 淡入淡出
    float   m_fAlpha;           // 控件Alpha值  added by zhuomeng.hu		[11/5/2010]
	bool	m_bFadeInorFadeOut;
	bool	m_bInFade;
	int		m_nFadeCurColorA;
	DWORD	m_dwFadeLastTime;
	bool	m_bFadeInval;		//淡入淡出对于此对象无效 false有效，true无效
	int		m_nMaxFade;
	int		m_nMinFade;
	float			m_FadeSpeed;
	// 移动
	bool	m_bMoving;
	int		m_nMoveToX;
	int		m_nMoveToY;
	DWORD	m_dwMoveStartTime;

	bool	m_bAllVisable;	//这个一直可见 代表着像 小地图 主界面 角色信息这样的dlg， esc不可以关掉它 平时总是可见的
							//..也许只有像电影模式这样才可以隐藏它吧

	UINT		m_unLeftTopVBOffset;
	UINT		m_unRightTopVBOffset;
	UINT		m_unLeftBottomVBOffset;
	UINT		m_unRightBottomVBOffset;
	UINT		m_unLeftVBOffset;
	UINT		m_unTopVBOffset;
	UINT		m_unRightVBOffset;
	UINT		m_unBottomVBOffset;
	UINT		m_unMiddleVBOffset;

    DWORD   _renderFlag;

	int m_nDefaultFontSize;

	bool	m_bEnable;

// 	bool		m_bLostFocusPassive;
	// LeftTop
	// RightTop
	// LeftBottom
	// RightBottom
	// Left
	// Top
	// Right
	// Bottom
	// Middle

public:
	ControlObject(void);

	void ReleaseBackGroundPic();
	virtual ~ControlObject(void);
public:
	static float GetSCALE(ControlObject* pObject);
	static float GetREAL_SCALE(ControlObject* pObject);
	static void SetUIScale(float s)
	{
		UI_SCALE = s;
// 		if( s <= 0.625f ) // 600
// 			UI_REAL_SCALE = s * 0.7f;
// 		else if( s <= 0.93f )
// 			UI_REAL_SCALE = s * 0.6f;
// 		else // s >= 1
			UI_REAL_SCALE = s * 0.6f;		
		//UI_REAL_SCALE = max( 0.8f, UI_REAL_SCALE );
	}
	// added, [9/15/2010 zhangjiayi]
	static void SetFontScale( float s )
	{
		UI_REAL_SCALE = s;
	}
	static void SetAdjustSCALE(float s)
	{
		UI_Adjust_SCALE = s;
	}

#ifdef _DEBUG
public:
	bool m_debug_bHasWarning;		// 是否有警告信息
#endif
	virtual void ResetDevice();
	virtual void LostDevice();
private:
	static float UI_SCALE;
	static float UI_REAL_SCALE;
	static float UI_Adjust_SCALE;

};

#define  ControlObjectGetSCALE(pObj)  ControlObject::GetSCALE(pObj)
#define  ControlObjectGetREAL_SCALE(pObj)  ControlObject::GetREAL_SCALE(pObj)

#define  ReciprocalGetSCALE(pObj)  1/ControlObject::GetSCALE(pObj)
#define  ReciprocalGetREAL_SCALE(pObj)  1/ControlObject::GetREAL_SCALE(pObj)


class ControlHelper
{
	SCRIPT_STRING_ANALYSIS m_Analysis;
	std::wstring m_AnalysisText;

	bool Analyse(const std::wstring& text, HDC fontHDC);

	ControlHelper();
public:
	~ControlHelper();

	static ControlHelper& Get()
	{
		static ControlHelper s;
		return s;
	}

	// 不再使用
	int GetTextWidth(const std::wstring& text, HDC fontHDC, int startCharIndex, int endCharIndex,ControlObject* pObject);

	//## add by pyj
	int GetTextWidth(const std::wstring& text, HDC fontHDC, int startCharIndex, int endCharIndex,ControlObject* pObject, int nFontIndex);

};

class ControlGroup
{
public:
	ControlGroup();
	virtual ~ControlGroup();

	virtual void Clear();
	virtual void AddControl(ControlObject* pControl);
	virtual ControlObject* GetControl(int index) { return m_vecControl[index]; }
	virtual size_t GetControlSize() { return m_vecControl.size(); }

	virtual void SetVisible(bool v);
	bool IsVisible() const { return m_isVisible; }

protected:
	std::vector<ControlObject*> m_vecControl;
	bool m_isVisible;
};
