#pragma once
#include "MeUi/ControlObject.h"
#include "MeUi/IconManager.h"
#include "MeUi/Animation/SmartAnimation.h"

class ControlProgress : public ControlObject
{
public:/*Virtual Function*/
	bool UseFocus()	{ return false; }
	void InitUIData( IN ControlObject* pFather, IN S_BaseData* pData );
	void SetVisable( const bool bVisable, const bool bFadeInorFadeOut = false );

	bool OnMouseMove( UINT nFlags, const int nX, const int nY);

public:
	__int64	GetValue(){ return m_nValue; }
	void	SetValue( const DWORD dwValue );
	void	SetValue( const float fValue );
	void    SetValue( const int n );
	void	SetValue( const __int64 n );	// 0~1000
	__int64		GetMaxValue(){ return m_nMaxValue; }
	void	SetMaxValue( __int64 n ){ m_nMaxValue = n; }

	// 创建
	void	Create( IN const RECT* pRect, const D3DCOLOR colBack);
	void	Create( ControlFrame* pFather,S_ProgressData* pData,const char* pProcessName);
	void	Render( );
	virtual void Run();

	void	setTipName(const char* ch, DWORD dwAlign = DT_CENTER | DT_VCENTER );

	bool	IsShowTip() { return m_bShowTip; }
	void	setShowTip(bool bShow)	{ m_bShowTip = bShow; }
	void SetRealPostion(const RECT& realRect);
	void UpdateAimation(const RECT&);

    // 设置宽度
    virtual void SetWidth( const int nW );
    // 设置高度
    virtual void SetHeight( const int nH );

	void	SetFlicker( bool bFlicker ){ m_bFlicker = bFlicker; }

protected:
	virtual const S_IconInfoBase* GetTipPointer() const{ return &TipInfo; }
    void setTip(const char* data);
    void SetShowTips();
    void UpdateByValueChange();
    void GetProgressWorkingArea( OUT RECT& rcDest );


//------------   动画   added by zhuomeng.hu    [12/8/2010] ------------
public:
    // 创建动画，strPath:XML资源 (特效名必须为 ProgressEffect)， bEffectOnly:本控件是否仅作为特效使用， bAutoStart:是否创建完自动开始
    bool    CreateAnimation( std::string strPath, bool bEffectOnly = false, bool bAutoStart = true );

    // 动画是否已创建
    bool    IsAnimationCreated();

    // 开始动画
    bool    StartAnimation();

    // 停止动画
    bool    StopAnimation();

    // 动画是否已开始
    bool    IsAnimationStarted();

    // 重播动画
    bool    RestartAnimation();

	// 动画是否停止
	bool    IsAnimationStop();

protected:
    void    AnimationRedraw( int nAlpha, int nFade );

private:
    CSmartAnimation*    m_pAnimation;       // 动画
    DWORD               m_dwAniBeginTime;   // 动画开始时间
    bool                m_bAniStart;        // 动画是否开始
//----------------------------------------------------------------------

private:
	bool	m_bShowTip;
	bool	m_bMouseMoveOn;
	__int64	m_nValue;		        // 0~1000
	__int64	m_nMaxValue;
	int		m_bFlicker;             // 是否闪烁

    bool    m_bVertical;            // 是否是竖直的
    bool    m_bReverse;             // 是否反向

	S_TextTipInfo		TipInfo;	//tip 显示
	
public:
	ControlProgress(void);
	~ControlProgress(void);

	virtual void ResetDevice();
};
