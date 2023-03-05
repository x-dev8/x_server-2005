/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	EditOpt.h
* Date: 	02/08/2007
* Desc:
*
*******************************************************************************/
#ifndef _EDIT_EIDTOPT_H__
#define _EDIT_EIDTOPT_H__
////////////////////////////////////////////////////////////////////////////////
enum znOptType
{
	znOT_Unknown = -1,
	znOT_PaintHeight,
	znOT_Camera,

	znOT_Flight
};

////////////////////////////////////////////////////////////////////////////////
class IOptBase
{
public:
	virtual				~IOptBase(){  };
				
	virtual bool		Undo()				= 0;	// 撤销
	virtual bool		Redo()				= 0;	// 重做
	
	virtual bool		Start()				= 0;	// 记录开始时状态
	virtual bool		End()				= 0;	// 记录结束时状态

	virtual znOptType	GetOptType() const	= 0;

};

class COptStack;
////////////////////////////////////////////////////////////////////////////////
class COptBase	: public IOptBase
{
public:
						COptBase();
	virtual				~COptBase();
	
	virtual	bool		Create( COptStack* stack );

	virtual bool		Undo();
	virtual bool		Redo();
	
	virtual bool		Start();
	virtual bool		End();
	
						// 取消操作，并且销毁自己．
	virtual bool		Cancel();

	const char*			GetOptName() const { return m_optName; };
	virtual znOptType	GetOptType() const { return znOT_Unknown; };
	
protected:
	COptStack*			m_stack;
	char				m_optName[32];
	bool				m_isStart;
};

#endif	// _EDIT_EIDTOPT_H__