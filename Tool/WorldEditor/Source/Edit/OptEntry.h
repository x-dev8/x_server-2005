/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	CameraOpt.h
* Date: 	02/08/2007
* Desc:
*
*******************************************************************************/
#ifndef _EDIT_OPTCAMERA_H__
#define _EDIT_OPTCAMERA_H__

#include "OptBase.h"

class CWorldEntry;
////////////////////////////////////////////////////////////////////////////////
// NOTE: 暂时没有把 Camera 操作添加到操作栈中,所以Undo,Redo 不会影响摄像机
class COptEntry	: public COptBase
{
public:
					COptEntry( CWorldEntry* camera );
	virtual			~COptEntry();

	virtual bool	Undo();
	virtual bool	Redo();

	virtual bool	Start();
	virtual bool	End();

protected:
	CWorldEntry*	m_worldEntry;
	
	Vector		m_oldPos;
	Vector		m_oldRot;
	flt32			m_oldScl;

	Vector		m_newPos;
	Vector		m_newRot;
	flt32			m_newScl;
};

#endif	// _EDIT_OPTCAMERA_H__

