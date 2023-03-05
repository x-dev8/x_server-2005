/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolVertex.h
* Date: 	03/02/2007
* Desc:
*
*******************************************************************************/
#ifndef _EDIT_TOOLSELECT_H__
#define _EDIT_TOOLSELECT_H__

#include "BaseTool.h"

////////////////////////////////////////////////////////////////////////////////
enum znVertexEditType {
	znTVT_Unknow	= -1,
	znTVT_UpDown,	// 增加降低高度
	znTVT_Smooth,	// 平滑高度
	znTVT_Plane,	// 斜面
	znTVT_Euqal,	// 推平
	
	znTVT_Flight
};

struct TSelInfo {
	sInt32	vert[2];
	flt32	weight;	// [0,1]
	flt32	dis;	// [0,1]
};
//jiayi [09.02.20]
static const unsigned short s_usInnerSegments = 32;
static const unsigned short s_usOuterSegments = 64;
static const unsigned short s_usBrushShapeVertexCnt = s_usInnerSegments + s_usOuterSegments + 2;
static const unsigned short s_usBrushShapeIdxCnt = 2 * (s_usInnerSegments + s_usOuterSegments);


////////////////////////////////////////////////////////////////////////////////
class CToolVertex	: public CBaseTool
{
friend class				CToolTerrain;
//added by zilong. 2011-01-15
friend class CWorldEditView;
friend class CNpcRes;
friend class CMonsterQuadRes;
public:
							CToolVertex();
	virtual					~CToolVertex();
	
	virtual ToolID			GetToolId()	{ return TOOL_VERTEX; };
	
	virtual bool			Create( CToolManager* toolMgr );
	void						Bind( CToolTerrain* dlg ){m_layerDlg = dlg;}

	virtual bool			OnLMouseDown( UINT nFlags, CPoint point );
	virtual bool			OnLMouseUp( UINT nFlags, CPoint point );
	virtual bool			OnLMouseDblClk( UINT nFlags, CPoint point );
	virtual bool			OnRMouseDown( UINT nFlags, CPoint point );
	virtual bool			OnRMouseUp( UINT nFlags, CPoint point );
	virtual bool			OnMouseMove( UINT nFlags, CPoint point );

	virtual bool			OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	virtual bool			OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );
	virtual bool			OnTimer();

	virtual void			Render();

protected:
	void					SetEditSize( flt32 editSize );
	void					SetEditStrength( flt32 editStrength );
	void					SetEditSpeed( flt32 editSpeed );
	void					SetEditMode( znVertexEditType editType );	
	bool					BuildTerrainPlane( const flt32* beginPos, const flt32* endPos, const flt32* height );

	void		            BuildBrushShape();//jiayi [09.02.20]
	void					UpdateBrushShape( flt32* origin );
	void UpdateBrushShape(const flt32* origin_, float innerRadius_, float outterRadius_);
	
protected:
	bool					m_isLock;
	
	flt32					m_editPos[2];
	flt32					m_editBeginPos[2];
	bool					m_isHeightPicked;
	flt32					m_pickHeight[2];
	sInt32					m_editVertex[2];
	znVertexEditType		m_editType;
	
	flt32					m_editSize;
	flt32					m_editStrength;	
	flt32					m_editSpeed;
	bool					m_isInvEdit;

	//brush shape 's vertex definition
	struct swBrushShapeVertex
	{
		enum
		{
			eFVF = D3DFVF_XYZ|D3DFVF_DIFFUSE
		};
		D3DXVECTOR3 p;
		DWORD		color;
	};
	//brush shape definition
	struct swBrushShape{

		swBrushShapeVertex kVertex[s_usBrushShapeVertexCnt];
		unsigned short kIndex[s_usBrushShapeIdxCnt];

	};

	swBrushShape*			m_brushShape;//jiayi [09.02.20]

	CToolTerrain*			m_layerDlg;
};

#endif	// _EDIT_TOOLVERTEX_H__

