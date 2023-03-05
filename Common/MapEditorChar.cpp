#include "MapEditorChar.h"


CMapEditorChar::CMapEditorChar()
{
	m_nZoneId = -1;
}

CMapEditorChar::~CMapEditorChar()
{
	CMdxAnimCtrl::Destroy();
}

void CMapEditorChar::SetZoneId( int nId )
{
	m_nZoneId = nId;
}

int CMapEditorChar::GetZoneId()
{
	return m_nZoneId;
}

void CMapEditorChar::SetMonsterIndex( int nId )
{
	m_nMonsterIndex = nId;
}

int CMapEditorChar::GetMonsterIndex()
{
	return m_nMonsterIndex;
}