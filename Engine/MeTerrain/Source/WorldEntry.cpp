/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	WorldEntry.cpp
* Create: 	10/06/2006
* Desc:		±à¼­Æ÷Ê¹ÓÃ
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#include "MeTerrain/stdafx.h"
#include "MeTerrain/WorldPrecompiled.hpp"
#include "MeTerrain/WorldEntry.h"


CWorldEntry::CWorldEntry()
{
	m_pos		= Vector::ZERO;
	m_rot		= Vector::ZERO;
	m_scl		= 1.0f;

}

CWorldEntry::~CWorldEntry()
{

}

const Vector&	CWorldEntry::GetPos() const
{
	return m_pos;
}

Vector& CWorldEntry::GetPos()
{
	return m_pos;
}

const Vector& CWorldEntry::GetRot() const
{
	return m_rot;
}

Vector& CWorldEntry::GetRot()
{
	return m_rot;
}

const flt32& CWorldEntry::GetScl() const
{
	return m_scl;
}

void CWorldEntry::SetPos( const Vector& pos )
{
	m_pos		= pos;
}

void CWorldEntry::SetRot( const Vector& rot )
{
	m_rot		= rot;
}

void CWorldEntry::SetScl( const flt32& scl )
{
	m_scl		= scl;
}

