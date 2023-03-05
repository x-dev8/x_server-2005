/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	EditOptSelect.cpp
* Date: 	03/06/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "EditUtil.h"
#include "OptPaintHeight.h"
#include "OptStack.h"
#include "Ndl/NdlWorldEditor.h"
#include <algorithm>

////////////////////////////////////////////////////////////////////////////////
COptPaintHeight::COptPaintHeight()
{
	strcpy_s( m_optName, "Move vertex" );

	m_vertexList.clear();
}

COptPaintHeight::~COptPaintHeight()
{
	for( size_t i=0; i<m_vertexList.size(); i++ ) {
		SAFE_DELETE( m_vertexList[i] );
	}
	m_vertexList.clear();
}

bool COptPaintHeight::Undo()
{
	
	return true;
}

bool COptPaintHeight::Redo()
{
	
	return true;
}

bool COptPaintHeight::Start()
{
	m_vertexList.clear();
	return COptBase::Start();
}

bool COptPaintHeight::End()
{
	return COptBase::End();
}

bool COptPaintHeight::Cancel()
{
	//for( sInt32 i=0; i<m_vertexList; i++ ) {
	//	TVertOpt* opt		= m_vertexList[i];
	//	Assert( opt->vertId == vertId );
	//	theApp.GetWorldEditor()->ModifyHeight( vertId, -(opt->changeHeight) );
	//}
	//theApp.GetWorldEditor()->UpdateShape();
	
	return COptBase::Cancel();
}

bool COptPaintHeight::MarkAsHole( bool isDelete )
{
	return true;
}

void COptPaintHeight::SetHeight( const sInt32* vertId, flt32 height, flt32 weight )
{
	//theApp.GetWorldEditor()->ModifyHeight( vertId, height, weight, 1.0f, false, false );
}

void COptPaintHeight::SetAveHeight( const sInt32* vertId, flt32 height, flt32 weight, flt32 scale, bool isInv )
{
	//theApp.GetWorldEditor()->ModifyHeight( vertId, height, weight, scale, false, false, true, isInv );
}

void COptPaintHeight::SetDeltaHeight( const sInt32* vertId, flt32 originHeight, flt32 deltaHeight, flt32 weight )
{
	//theApp.GetWorldEditor()->ModifyHeight( vertId, deltaHeight, weight, originHeight );
	//Trace( "(%d,%d) %8.3f \n", vertId[0], vertId[1], deltaHeight );
}

void COptPaintHeight::SetModifyHeight( const sInt32* vertId, flt32 originHeight, flt32 deltaHeight, flt32 weight )
{
	//theApp.GetWorldEditor()->ModifyHeight( vertId, deltaHeight, weight, originHeight, true, true );
}

bool COptPaintHeight::UpdateShape()
{
	//theApp.GetWorldEditor()->UpdateShape();

	return true;
}

