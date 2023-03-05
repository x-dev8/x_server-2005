/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolLayer.h
* Date: 	03/14/2007
* Desc:
*
*******************************************************************************/
#ifndef _EDIT_TOOLLAYER_H__
#define _EDIT_TOOLLAYER_H__

////////////////////////////////////////////////////////////////////////////////
#include "BaseTool.h"


////////////////////////////////////////////////////////////////////////////////
struct TLayerBrush
{
	char	brushName[RES_NAME_LEN];
	sInt32	brushSize;
	uInt8*	brushData;

	TLayerBrush(){ 
		brushSize	= 0;
		brushData	= NULL;
	};
	~TLayerBrush() { 
		brushSize	= 0;
		SAFE_DELETE_ARRAY( brushData );
	};
};

class CNdlDecalRes;
////////////////////////////////////////////////////////////////////////////////
class CToolLayer	: public CBaseTool
{
	friend class				CToolLayerDlg;
public:	
	CToolLayer();
	virtual						~CToolLayer();

	virtual ToolID				GetToolId()				{ return TOOL_LAYER; };

	virtual bool				Create( CToolManager* toolMgr );
	void						Bind( CToolLayerDlg* dlg );

	virtual bool				OnLMouseDown( UINT nFlags, CPoint point );
	virtual bool				OnLMouseUp( UINT nFlags, CPoint point );
	virtual bool				OnLMouseDblClk( UINT nFlags, CPoint point );
	virtual bool				OnRMouseDown( UINT nFlags, CPoint point );
	virtual bool				OnRMouseUp( UINT nFlags, CPoint point );
	virtual bool				OnMouseMove( UINT nFlags, CPoint point );

	void						PaintSth(  UINT nFlags, CPoint point  );

	void						DecalUpdate( flt32 * pt );
	virtual bool				OnMouseWheel( UINT nFlags, short zDelta, CPoint point);

	virtual bool				OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	virtual bool				OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );
	virtual bool				OnWTPacket(PACKET& packet,CPoint& point);

	virtual void				Render();

	TNameInfo*					GetTexNameInfoFromId( sInt32 textureId );
	const TLayerBrush*			GetBrush( size_t brushId ) const;

	flt32						GetBrushDecalScale();
	void						SetPaintShadow(bool val);

	void						setMultiSel( bool b);
protected:
	bool						LoadLayerTexture();
	bool						LoadLayerBrush();
	bool						LoadBrushFromBitmap( LPCTSTR fileName, const char* brushName );

	bool						UpdateLayer( flt32* pt );
	bool						PaintPoint( flt32* pt, bool isInv = false );
	bool						PaintShadow( flt32* pt, bool isAddShadow, uInt8 alpha );
	bool						PaintRoad( flt32* pt, bool isAddShadow, uInt8 alpha );
	bool						PaintVertexColor( flt32* pt,bool isAdd , uInt8 alpha);
	bool						ClearVertexColor( flt32* pt);

	bool						FindTexture( const char* path, const char* fileName );
	void						EnumFile( LPCTSTR strDir );

	void						SetLock( bool isLock )	{ m_isLock = isLock; };
protected:
	bool						m_isLock;
	NiColor						m_NiColor;
	CToolLayerDlg*				m_layerDlg;
	CWorldChunk*				m_selWorldChunk;
	CResEditMgr*					m_selResMgr;
	std::vector<TNameInfo*>		m_texInfoList;
	sInt32						m_paintMode;
	uInt8						m_alpha;
	sInt32						m_textureId;
	sInt32						m_brushId;
	sInt32						m_flow;
	std::vector<TLayerBrush*>	m_brushList;

	CNdlDecalRes*				m_brushDecal;
	bool						m_isPaintShadow;
	bool						m_multiSel;
public:
	vector<CWorldChunk*>       m_vecWorldChunk;
};

#endif	// _EDIT_TOOLLAYER_H__
