/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	EditOptStack.cpp
* Date: 	02/08/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "OptPaintHeight.h"
#include "OptStack.h"
#include <algorithm>

////////////////////////////////////////////////////////////////////////////////
COptStack::COptStack()
{
	m_size		= 0;
	m_stack		= NULL;
	m_preOpt	= NULL;

	m_curPos	= 0;
	m_undoStep	= 0;	
	m_redoStep	= 0;
}	

COptStack::~COptStack()
{
	for( sInt32 i=0; i<m_size; i++ ) {
		SAFE_DELETE( m_stack[i] );
	}
	SAFE_DELETE_ARRAY( m_stack );
	SAFE_DELETE_ARRAY( m_preOpt );
}

bool COptStack::Create( sInt32 stackSize )
{
	Assert( (stackSize>0) && (stackSize<256) );
	m_size = stackSize;
	
	m_stack	= new COptBase*[m_size];
	for( sInt32 i=0; i< m_size; i++ ) {
		m_stack[i] = NULL;
	}
	m_curPos	= 0;
	m_undoStep	= 0;
	m_redoStep	= 0;
	
	CollapseAll();
	
	return true;
}

bool COptStack::CollapseAll()
{
	
	return true;
}

sInt32 COptStack::GetNextPos( sInt32 pos )
{
	pos++;
	if( pos == m_size )	{
		pos = 0;
	}
	return pos;
}

sInt32 COptStack::GetPrevPos( sInt32 pos )
{
	pos--;
	if( pos < 0 ) {
		pos = m_size-1;
	}
	return pos;
}

void COptStack::SetPreOpt( COptBase* opt )
{
	m_preOpt = opt;
}

void COptStack::PushOpt( COptBase* opt )
{
	Trace( "²Ù×÷[%s]½øÕ»\n", opt->GetOptName() );
	m_curPos = GetNextPos( m_curPos );
	m_undoStep++;
	if( m_undoStep > m_size ) {
		m_undoStep = m_size;
	}
	m_redoStep = 0;
	
	COptBase* cachePtr = m_stack[m_curPos];
	SAFE_DELETE( cachePtr );

	m_stack[m_curPos] = opt;	
}

COptBase* COptStack::GetCurOpt()
{
	if( m_undoStep>0 )
		return m_stack[m_curPos];
	else
		return NULL;
}

bool COptStack::Undo()
{
	if( m_undoStep<1 )
		return false;
	
	COptBase* opt = m_stack[m_curPos];
	opt->Undo();
	
	m_curPos = GetPrevPos( m_curPos );
	m_undoStep--;
	m_redoStep++;
	Assert( m_redoStep <= m_size );
	
	return true;
}

bool COptStack::Redo()
{
	if( m_redoStep<1 )
		return false;
	
	COptBase* opt = m_stack[m_curPos];
	opt->Redo();

	m_curPos = GetNextPos( m_curPos );
	m_redoStep--;
	m_undoStep++;
	Assert( m_undoStep <= m_size );

	return true;
}

