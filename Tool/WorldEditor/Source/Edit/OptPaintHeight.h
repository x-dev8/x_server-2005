/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	EditOptSelect.h
* Date: 	03/06/2007
* Desc:
*
*******************************************************************************/
#ifndef _EDIT_EDITOPTSELECT_H__
#define _EDIT_EDITOPTSELECT_H__

#include "OptBase.h"

////////////////////////////////////////////////////////////////////////////////
struct TVertexInfo;
class CWorldEntry;

////////////////////////////////////////////////////////////////////////////////
// 因为数据量巨大,所以只记录修改值．
struct TVertOpt
{
	uInt32	vertId;			// id
	bool	changeHole;		// 是否更改删除属性(删除标记是为了产生洞.)
	flt32	changeHeight;	// 高度
};

////////////////////////////////////////////////////////////////////////////////
class COptPaintHeight	: public COptBase
{
public:
							COptPaintHeight();
	virtual					~COptPaintHeight();

	virtual bool			Undo();
	virtual bool			Redo();

	virtual bool			Start();
	virtual bool			End();
	
	virtual bool			Cancel();
	virtual znOptType		GetOptType() const { return znOT_PaintHeight; };

							// 注意操作都是在修改栈上进行的.	
	bool					MarkAsHole( bool isDelete = true );
	void					SetHeight( const sInt32* vertId, flt32 height, flt32 weight );
	void					SetAveHeight( const sInt32* vertId, flt32 height, flt32 weight, flt32 scale, bool isInv );
	void					SetDeltaHeight( const sInt32* vertId, flt32 originHeight, flt32 deltaHeight, flt32 weight );
	void					SetModifyHeight( const sInt32* vertId, flt32 originHeight, flt32 deltaHeight, flt32 weight );

	bool					UpdateShape();

protected:
	std::vector<TVertOpt*>	m_vertexList;

};

#endif	// _EDIT_EDITOPTSELECT_H__

