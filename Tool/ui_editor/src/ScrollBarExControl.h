/********************************************************************
	created:	2006/06/07
	created:	7:6:2006   15:25
	filename: 	e:\TianJi\UIEditor\ScrollBarExControl.h
	file path:	e:\TianJi\UIEditor
	file base:	ScrollBarExControl
	file ext:	h
	author:		WitSun
	
	purpose:	
*********************************************************************/

#pragma once
#include "ScrollbarControl.h"

class CScrollBarExControl : public CScrollBarControl
{
public:
	virtual void OnSize();

public:
	CScrollBarExControl(void);
	virtual ~CScrollBarExControl(void);
};
