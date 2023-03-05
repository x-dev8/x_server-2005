/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	EditOptStack.h
* Date: 	02/08/2007
* Desc:
*
*******************************************************************************/
#ifndef _EDIT_EDITOPTSTATCK_H__
#define _EDIT_EDITOPTSTATCK_H__

#include "OptBase.h"

////////////////////////////////////////////////////////////////////////////////
class COptStack		
{
	friend	class		COptPaintHeight;
public:
						COptStack();
	virtual				~COptStack();
	
	bool				Create( sInt32 stackSize = 128 );

	void				SetPreOpt( COptBase* opt );
	COptBase*			GetPreOpt()	const	{ return m_preOpt; };

	void				PushOpt( COptBase* opt );
	COptBase*			GetCurOpt();

	bool				Undo();
	bool				Redo();
	
	sInt32				GetCanUndoCount()	{ return m_undoStep; };
	sInt32				GetCanRedoCount()	{ return m_redoStep; };

	sInt32				GetNextPos( sInt32 pos );
	sInt32				GetPrevPos( sInt32 pos );

	bool				SetSelectLock( bool isLock = true );
	bool				IsSelectLock() const { return m_isSelectLock; };
	
protected:
	bool				CollapseAll();

protected:
	sInt32				m_size;
	COptBase**			m_stack;			

	COptBase*			m_preOpt;	// Ҫ��ջ,��û�н�ջ�Ĳ���.
	sInt32				m_curPos;
	sInt32				m_undoStep;	// ���� undo �Ĵ���
	sInt32				m_redoStep;	// ���� redo �Ĵ���
	
	bool				m_isSelectLock;
};

#endif	// _EDIT_EDITOPTSTATCK_H__

