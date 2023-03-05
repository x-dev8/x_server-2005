/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	EditOpt.cpp
* Date: 	02/08/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "OptBase.h"
#include "OptStack.h"

////////////////////////////////////////////////////////////////////////////////
COptBase::COptBase()
{
	memset( m_optName, 0, 32*sizeof(char) );
	m_isStart	= false;
	m_stack		= NULL;
}

COptBase::~COptBase()
{
	m_stack		= NULL;
}

bool COptBase::Create( COptStack* stack )
{
	Assert( NULL != stack );
	m_stack = stack;

	return true;
}

bool COptBase::Cancel()
{
	delete this;
	return true;
}

bool COptBase::Undo()
{
	return true;
}

bool COptBase::Redo()
{

	return true;
}

bool COptBase::Start() {
	if( false != m_isStart ) {
		Trace( "<<<WARNING>>> 已经开始了一个操作[%s]！ \n", m_optName );
	}

	m_isStart = true;
	m_stack->SetPreOpt( this );

	return true;
}

bool COptBase::End()
{
	if( false == m_isStart ) {
		Trace( "<<<WARNING>>> 操作并没有开始[%s]！ \n", m_optName );
	}
	m_isStart = false;

	Assert( NULL != m_stack );
	m_stack->PushOpt( this );	
	m_stack->SetPreOpt( NULL );

	return true;
}






