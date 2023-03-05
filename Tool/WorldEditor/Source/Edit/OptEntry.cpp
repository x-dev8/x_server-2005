/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	OptCamera.cpp
* Date: 	02/08/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "MeTerrain/WorldEntry.h"
#include "OptEntry.h"


////////////////////////////////////////////////////////////////////////////////
COptEntry::COptEntry( CWorldEntry* entry )
{
	m_worldEntry	= entry;
}

COptEntry::~COptEntry()
{
	m_worldEntry	= NULL;
}

bool COptEntry::Undo()
{
	m_worldEntry->SetPos( m_oldPos );
	m_worldEntry->SetRot( m_oldRot );
	m_worldEntry->SetScl( m_oldScl );

	return true;
}

bool COptEntry::Redo()
{
	m_worldEntry->SetPos( m_newPos );
	m_worldEntry->SetRot( m_newRot );
	m_worldEntry->SetScl( m_newScl );

	return true;
}

bool COptEntry::Start()
{
	m_oldPos = m_worldEntry->GetPos();	
	m_oldRot = m_worldEntry->GetRot();	
	m_oldScl = m_worldEntry->GetScl();

	return true;
}

bool COptEntry::End()
{
	m_newPos = m_worldEntry->GetPos();	
	m_newRot = m_worldEntry->GetRot();
	m_newScl = m_worldEntry->GetScl();
	
	return true;
}



