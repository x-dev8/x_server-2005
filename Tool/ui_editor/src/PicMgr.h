/********************************************************************
	created:	2004/06/16
	created:	16:6:2004   10:14
	filename: 	e:\UIEditor\PicMgr.h
	file path:	e:\UIEditor
	file base:	PicMgr
	file ext:	h
	author:		WitSun
	
	purpose:	PicMgr
*********************************************************************/
#pragma once
#include <vector>
#include "TgaCore.h"

class CPicMgr
{
public:
	CDC* GetDC( const char* pszPicName, CDC* pDC );
	void	Clear();

private:
	struct S_Pic
	{
		CDC					m_DC;
		CGraphicsFileData	m_Graphics;
	};

private:
	std::vector<S_Pic*>		m_vtPic;

public:
	CPicMgr(void);
	~CPicMgr(void);
};

extern CPicMgr thePicMgr;
