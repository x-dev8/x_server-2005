/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	OptPaintLayer.h
* Date: 	03/14/2007
* Desc:
*
*******************************************************************************/
#ifndef _EDIT_OPTPAINTLAYER_H__
#define _EDIT_OPTPAINTLAYER_H__

#include "OptBase.h"
#include <map>

////////////////////////////////////////////////////////////////////////////////
struct TMaskData 
{
	uInt32	chunkId;
	uInt32	data[64*64];		// 64 bit.
};	

typedef std::map<uInt32, TMaskData*, std::less<uInt32> > Id2Mask;

////////////////////////////////////////////////////////////////////////////////
class COptPaintLayer	: public COptBase
{
public:
							COptPaintLayer();
	virtual					~COptPaintLayer();
	
	virtual znOptType		GetOptType() const { return znOT_PaintHeight; };
	
	virtual bool			Undo();
	virtual bool			Redo();
	
	virtual bool			Start();
	virtual bool			End();
	
	virtual bool			Cancel();
	
	
	
};






#endif	// _EDIT_OPTPAINTLAYER_H__




