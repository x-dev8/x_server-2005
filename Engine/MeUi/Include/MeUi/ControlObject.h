
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

#define OUT	/*�������*/
#define IN	/*�������*/

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
//#define MESSAGE_BOX(sz){if(::MessageBox(NULL,sz,"����!",MB_ABORTRETRYIGNORE)!=IDIGNORE){__asm{int 3}}}
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
	// ��Ⱦ
	virtual void Render();
	// ����
	virtual void Run();
	// �ͷ�
	virtual void ReleaseUI();
	// ��ʼ������
	virtual void InitUIData( IN ControlObject* pFather, IN S_BaseData* pData );
	// ʹ�ý���
	virtual bool UseFocus();
	// �Ƿ���ҪRender
	virtual bool IsNeedRender();
	// �����Ƿ��ڱ�����
	virtual bool PtInObject( const int nX, const int nY ,bool bCheckMsgHold = true);
	virtual bool IsMouseInUI( const int nX, const int nY );
	virtual bool PtInObject( const RECT& rc, const int nX, const int nY);
	// �����Ƿ�ɼ�/����
	virtual void SetVisable( const bool bVisable);
	// ��˸
	virtual void StartFlash( const int nFlashCount,
							const bool bAutoClose = false, const bool bFadeIn = false );

	//������˸�ٶ�
	virtual void SetFlashSpeed( float fFlashSpeed ){ m_fFlashSpeed = fFlashSpeed; }
	//
	virtual void SetRealRect( IN const RECT* prc );
	// ��Ϣ
	virtual bool MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed = false );
	// �����ӿؼ�
	virtual ControlObject*	FindControl( IN const char* szControlID,
										IN const char* szFrameID = NULL)		{ return NULL;  }
	// �����ӿ��
	virtual ControlObject* FindFrame( IN const char *szFrameID )				{ return NULL;  }
	// ȡ������ģʽ
	virtual int	 GetArrayMode()													{ return 0;		}
	// �Ƿ��Ǳ����ӿؼ�
	virtual bool IsChild( IN const ControlObject* pChild )						{ return false; }
	// ����ƶ���Ϣ
	virtual bool OnMouseMove( UINT nFlags, const int nX, const int nY )			{ return false; }
	virtual bool OnMouseLeave( )												{ return false; }
	// ��������Ϣ
	virtual bool OnMouseWheel( bool bUp, const int nX, const int nY )			{ return false; }
	// ������������Ϣ
	virtual bool OnLButtonDown( UINT nFlags, const int nX, const int nY )		{ return false; }
	// ����Ҽ�������Ϣ
	virtual bool OnRButtonDown( UINT nFlags, const int nX, const int nY )		{ return false; }
	// �������ɿ���Ϣ
	virtual bool OnLButtonUp( UINT nFlags, const int nX, const int nY )			{ return false; }
	// ����Ҽ��ɿ���Ϣ
	virtual bool OnRButtonUp( UINT nFlags, const int nX, const int nY )			{ return false; }
	// ������˫����Ϣ
	virtual bool OnLButtonDBClick( UINT nFlags, const int nX, const int nY )	{ return false; }
	// ����Ҽ�˫����Ϣ
	virtual bool OnRButtonDBClick( UINT nFlags, const int nX, const int nY )	{ return false; }
	// ���̰�����Ϣ
	virtual bool OnKeyDown( UINT nChar )										{ return false; }
	// �����ɿ���Ϣ
	virtual bool OnKeyUp( UINT nChar )											{ return false; }
	// �ַ���Ϣ
	virtual bool OnChar( UINT nChar )											{ return false; }
	// �����Ƿ���ק
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
	// ȡ�þ��Ծ���
	void	GetRealRect( OUT RECT* prc );
	void    GetRectSize(OUT RECT* prc);
	// �õ��ؼ�ID
	char*	GetControlID(){ return m_pstData->m_szID;}
	// �õ��ؼ�����
	int		GetControlType(){ return m_pstData->m_nType; }
	//
	int		GetFontSize(){ return m_pstData->m_nFontSize; }
	//
	int		GetFontIndex(){ return m_nFontIndex; }
//	void	SetFontIndex(int nIndex)		{ m_nFontIndex = nIndex; }
	void	SetFont( const ControlObject* pSrc );
	//
	COLORREF GetFontColor(){ return m_pstData->m_colFont; }
	// ȡ�ÿ��
	int		GetWidth(){ return m_nWidth; }
	// ȡ�ø߶�
	int		GetHeight(){ return m_nHeight; }
	// ���õ�ǰ��ʾͼƬ
	bool	SetPic( IN S_BaseData::S_Pic *pPic, bool bCoverData = false );
	//
	void	SetPos( const int nX, const int nY, bool bReal = true );
	// ����X����
	void	SetXPos( const int nX );
	// ����Y����
	void	SetYPos( const int nY );
    // ���ÿ��
    virtual void SetWidth( const int nW );
    // ���ø߶�
    virtual void SetHeight( const int nH );
	// �����Ƿ񱻸�����
	void	SetCovered( const bool bCovered ){ m_bCovered = bCovered; }
	// �Ƿ�ɼ�����
	bool	IsVisable(){ return m_bVisable; }
	// �Ƿ񱻸���
	bool	IsCovered(){ return m_bCovered; }
	// �Ƿ񱻸���
	bool	IsBeCovered( IN ControlObject* pCover );
	// ����
	void	SetActivate( const bool bActivate = true );
	bool	IsActivated();
	// �ƶ�
	void	MoveTo( const int nX, const int nY );
	bool	IsMoving() { return m_bMoving; } //lrt ��ȡ�Ƿ����ƶ���
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
	//���� Bltʱ���
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

    void SetAlpha( float fAlpha );  // ����Alpha    added by zhuomeng.hu		[11/5/2010]
    float GetAlpha();

// 	void SetLostFocusPassive(bool val) { m_bLostFocusPassive = val; }
// 	bool CanLostFocusPassive() const { return m_bLostFocusPassive; }

protected: // Tip ���
	virtual const class S_IconInfoBase* GetTipPointer() const{ return NULL; }
	void CheckTipAndClear();

public:
	// ��ͼ
	void 	BitBlt( IN OUT int* pPicId,
					IN const char* szPicName,
					float nDstX, float nDstY,
					float nDstWidth, float nDstHeight,
					int nSrcX, int nSrcY,
					int nSrcWidth, int nSrcHeight,
					int nDrawMode,
					D3DCOLOR col = 0xffffffff );
	// �õ�������
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
	bool			m_bNeedRelease;				// �Ƿ���Ҫ�ͷ���Դ
	std::string		m_strSound;					// ����

	S_BaseData::S_Pic	*m_pstPic;				// ��ǰͼƬ
	// ���
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

	ControlObject	*m_pFather;					// ���ؼ�
	ControlFrame	*m_pFrameFather;					// ���ڵ�ؼ�
	S_BaseData		*m_pstData;					// �ؼ�����
	std::string		m_strBackPicName;			// ��ǰ����ͼƬ��
	int				m_nPicId;					// ��ǰ����ͼƬID
	unsigned long	m_nQuadId;					// ��ǰ����ͼƬ���Ʋ�����quadid
	int				m_nFontIndex;				// ��������ֵ
	HDC				m_hDC;
	bool			m_bVisable;					// �Ƿ�ɼ�
	bool			m_bCovered;					// �Ƿ񱻸���
	D3DCOLOR		m_colBackColor;				// ������ɫ(��û��ͼƬʱ��ʾ)
	bool			m_bDrawFrame;				// �Ƿ񻭱߿�
	bool			m_bMsgHoldup;
	float			m_fBackPicZ;
	bool			m_bRenderTextWithZ;
	bool			m_bSkipMsg;
	// ����
	float	m_fFlashSpeed;
	int		m_nFlashCurCount;
	int		m_nFlashCount;
	int		m_nFlashCurColorA;
	bool	m_bFlashedAutoClose;
	bool	m_bFlashFade;
	DWORD	m_dwFlashStartTime;
	// ���뵭��
    float   m_fAlpha;           // �ؼ�Alphaֵ  added by zhuomeng.hu		[11/5/2010]
	bool	m_bFadeInorFadeOut;
	bool	m_bInFade;
	int		m_nFadeCurColorA;
	DWORD	m_dwFadeLastTime;
	bool	m_bFadeInval;		//���뵭�����ڴ˶�����Ч false��Ч��true��Ч
	int		m_nMaxFade;
	int		m_nMinFade;
	float			m_FadeSpeed;
	// �ƶ�
	bool	m_bMoving;
	int		m_nMoveToX;
	int		m_nMoveToY;
	DWORD	m_dwMoveStartTime;

	bool	m_bAllVisable;	//���һֱ�ɼ� �������� С��ͼ ������ ��ɫ��Ϣ������dlg�� esc�����Թص��� ƽʱ���ǿɼ���
							//..Ҳ��ֻ�����Ӱģʽ�����ſ�����������

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
	bool m_debug_bHasWarning;		// �Ƿ��о�����Ϣ
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

	// ����ʹ��
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
