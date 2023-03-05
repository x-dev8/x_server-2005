
#pragma once
#include "MeUi/ControlObject.h"
#include "MeUi/ControlButton.h"

class ControlScrollBar : public ControlObject
{
public:
	typedef void (*funUpdatePos)( OUT ControlObject* pSender, int n );

public:	/*Virtual Function*/
	virtual void Render();
	virtual void InitUIData( IN ControlObject* pFather, IN S_BaseData* pData );
	virtual bool OnMouseMove( UINT nFlags, const int nX, const int nY );
	virtual bool OnLButtonDown( UINT nFlags, const int nX, const int nY );
	virtual bool OnLButtonUp( UINT nFlags, const int nX, const int nY );

public:
	void	Clear();
	void SetUpdatePosFun( IN funUpdatePos pFun )	{ m_pFunUpdatePos = pFun; }
	int  GetValue(){ return m_nValue; }
	void SetValue( const int n );
	bool IsDrag(){ return m_bLButtonDrag; }
	void ClearDrag()	{ m_bLButtonDrag = false; }
	void SetEnable( bool bEnable = true)		{ m_bEnable = bEnable; }
	bool GetEnable()							{ return m_bEnable; }
	void SetUIScrollBarBlend( int nBlend ) 
	{
		this->SetBlendColor( nBlend );
		 m_btnUp.SetBlendColor( nBlend );
		 m_btnDonw.SetBlendColor( nBlend );
		 m_btnBar.SetBlendColor( nBlend );
	}
	void SetScrollHeight( const int nHeight )
	{
		RECT rt = {0};
		GetRealRect( &rt );
		this->SetHeight( nHeight );
		m_btnUp.SetPos( rt.left, rt.top );
		m_btnBar.SetPos( rt.left, rt.top-( (rt.top-rt.bottom)/2) );
		m_btnDonw.SetPos( rt.left, rt.top+nHeight-m_btnDonw.GetHeight() );
	//	nUp = nHeight;
	}
	int		GetMaxValue()			{ return m_nMaxValue; }
	void	SetMaxValue(int nMax)	{ m_nMaxValue = nMax; }
	int		GetStepValue() const	{ return m_nStepValue; }
	void	SetStepValue(int nStep)	{ m_nStepValue = nStep; }
	void    SetPageSize(int pageSize) { m_nPageSize = pageSize; }
	int		GetPageSize() const		{ return m_nPageSize; }

	virtual void SetRealRect( IN const RECT* prc );

	virtual void FocusOut();

public:
	virtual void OnUpdatePos();

protected:
	ControlButton	m_btnUp;
	ControlButton	m_btnDonw;
	ControlButton	m_btnBar;
	int				m_nMaxValue;
	int				m_nStepValue;
	int				m_nValue; // 0~1000
    int             m_nPageSize;
	bool			m_bLButtonDrag;

	bool			m_bEnable;

	funUpdatePos	m_pFunUpdatePos;

	POINT			m_ptMousePos;
	POINT			m_ptBarPos;

public:
	ControlScrollBar(void);
	virtual ~ControlScrollBar(void);

	virtual void ResetDevice();
};
