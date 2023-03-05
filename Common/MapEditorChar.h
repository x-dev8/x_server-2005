#pragma once
#include "MdxAnimCtrl.h"


class CMapEditorChar:public CMdxAnimCtrl
{
public:
	CMapEditorChar();
	~CMapEditorChar();

public:
	void SetZoneId( int nId );
	int GetZoneId();
	void SetMonsterIndex( int nId );
	int GetMonsterIndex();

private:
	int m_nZoneId;
	int m_nMonsterIndex;
};
