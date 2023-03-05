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

	// ����
	void	Create( IN const RECT* pRect, const D3DCOLOR colBack);
	void	Create( ControlFrame* pFather,S_ProgressData* pData,const char* pProcessName);
	void	Render( );
	virtual void Run();

	void	setTipName(const char* ch, DWORD dwAlign = DT_CENTER | DT_VCENTER );

	bool	IsShowTip() { return m_bShowTip; }
	void	setShowTip(bool bShow)	{ m_bShowTip = bShow; }
	void SetRealPostion(const RECT& realRect);
	void UpdateAimation(const RECT&);

    // ���ÿ��
    virtual void SetWidth( const int nW );
    // ���ø߶�
    virtual void SetHeight( const int nH );

	void	SetFlicker( bool bFlicker ){ m_bFlicker = bFlicker; }

protected:
	virtual const S_IconInfoBase* GetTipPointer() const{ return &TipInfo; }
    void setTip(const char* data);
    void SetShowTips();
    void UpdateByValueChange();
    void GetProgressWorkingArea( OUT RECT& rcDest );


//------------   ����   added by zhuomeng.hu    [12/8/2010] ------------
public:
    // ����������strPath:XML��Դ (��Ч������Ϊ ProgressEffect)�� bEffectOnly:���ؼ��Ƿ����Ϊ��Чʹ�ã� bAutoStart:�Ƿ񴴽����Զ���ʼ
    bool    CreateAnimation( std::string strPath, bool bEffectOnly = false, bool bAutoStart = true );

    // �����Ƿ��Ѵ���
    bool    IsAnimationCreated();

    // ��ʼ����
    bool    StartAnimation();

    // ֹͣ����
    bool    StopAnimation();

    // �����Ƿ��ѿ�ʼ
    bool    IsAnimationStarted();

    // �ز�����
    bool    RestartAnimation();

	// �����Ƿ�ֹͣ
	bool    IsAnimationStop();

protected:
    void    AnimationRedraw( int nAlpha, int nFade );

private:
    CSmartAnimation*    m_pAnimation;       // ����
    DWORD               m_dwAniBeginTime;   // ������ʼʱ��
    bool                m_bAniStart;        // �����Ƿ�ʼ
//----------------------------------------------------------------------

private:
	bool	m_bShowTip;
	bool	m_bMouseMoveOn;
	__int64	m_nValue;		        // 0~1000
	__int64	m_nMaxValue;
	int		m_bFlicker;             // �Ƿ���˸

    bool    m_bVertical;            // �Ƿ�����ֱ��
    bool    m_bReverse;             // �Ƿ���

	S_TextTipInfo		TipInfo;	//tip ��ʾ
	
public:
	ControlProgress(void);
	~ControlProgress(void);

	virtual void ResetDevice();
};
