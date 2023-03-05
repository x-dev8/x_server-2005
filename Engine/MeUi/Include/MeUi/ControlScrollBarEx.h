
#pragma once
#include "MeUi/ControlScrollBar.h"

class ControlScrollBarEx : public ControlScrollBar
{
public:
	virtual bool OnMouseMove( UINT nFlags, const int nX, const int nY );
	virtual bool OnLButtonDown( UINT nFlags, const int nX, const int nY );
	virtual void Render();

public:
	virtual void OnUpdatePos();
	void SetDrawValueText( bool bDrawValueText ){ m_bDrawValueText = bDrawValueText; }
	void SetDrawInCustom( bool bDrawInCustom ){ m_bDrawInCustom = bDrawInCustom; }
	void SetCustomValue( int nCustomValue ){ m_nCustomValue = nCustomValue; }


public:
	ControlScrollBarEx(void);
	virtual ~ControlScrollBarEx(void);

protected:
	void DrawValueText( int nValue );

protected:
	//拖动的时候是否绘制当前数值
	bool	m_bDrawValueText;
	//是否显示自定义数值
	bool	m_bDrawInCustom;
	//自定义数值
	int		m_nCustomValue;

};
