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
// ��Ϊ�������޴�,����ֻ��¼�޸�ֵ��
struct TVertOpt
{
	uInt32	vertId;			// id
	bool	changeHole;		// �Ƿ����ɾ������(ɾ�������Ϊ�˲�����.)
	flt32	changeHeight;	// �߶�
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

							// ע������������޸�ջ�Ͻ��е�.	
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

