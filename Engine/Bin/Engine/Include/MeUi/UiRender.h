
#pragma once

#include <windows.h>
#include <vector>
#include "Me3d/BaseGraphics.h"
#include "Me3d/Engine/Engine.h"

/*!
\brief   add by pyj at 20100825
Enumerated type that contains the quad is added by font or ui, because their render state is different.
*/
enum QuadAddBy
{
	ui_quad,	      //add by ui
	font_quad		  //add by font
};

class UiRender
{
public:
	UiRender();
	virtual ~UiRender();
	static const size_t    VERTEX_PER_QUAD;						 //!< number of vertices per quad
	static const size_t    VERTEX_PER_TRIANGLE;					 //!< number of vertices for a triangle
	static const size_t    VERTEXBUFFER_INITIAL_CAPACITY;		 //!< initial capacity of the allocated vertex buffer
	static const size_t    UNDERUSED_FRAME_THRESHOLD;            //!< number of frames to wait before shrinking buffer

	/*!
	\brief
	Enumerated type that contains the valid diagonal-mode that specify how a quad is split into triangles when rendered with fx. a 3D API
	*/
	enum QuadSplitMode
	{
		TopLeftToBottomRight,	//!< Diagonal goes from top-left to bottom-right
		BottomLeftToTopRight	//!< Diagonal goes from bottom-left to top-right
	};
	


	typedef struct tagRECTF
	{
		float    left;
		float    top;
		float    right;
		float    bottom;
	} RECTF;

	void				Initialize();
	/*!
	\brief
	Return whether queueing is enabled.

	\return
	true if queueing is enabled, false if queueing is disabled.
	*/
	virtual bool	isQueueingEnabled(void) const	{return d_queueing;}
	void			SetQueueingEnabled(bool val) { d_queueing = val; }
	// add's a quad to the list to be rendered
	//virtual	unsigned long	addQuad(const RECT& dest_rect, const UiPicture* tex, const RECT& texture_rect, D3DCOLOR col, QuadSplitMode quad_split_mode);
	virtual	unsigned long	addQuad(const RECT& dest_rect, const LPDIRECT3DTEXTURE9 tex, const RECT& texture_rect, D3DCOLOR col, QuadAddBy qab=ui_quad, float z=0.0f/*,QuadSplitMode quad_split_mode = TopLeftToBottomRight*/);

    // 顶点多色，目前只用于字体         added by zhuomeng.hu		[4/8/2011]
    virtual unsigned long AddColorizedQuad( const RECT& dest_rect, const LPDIRECT3DTEXTURE9 tex, const RECT& texture_rect,
        const D3DCOLOR ( &dwVtColorArray )[4], QuadAddBy qab = ui_quad, float z = 0.0f );

	virtual	unsigned long	RetriveQuad();//取QuadId，为了下面的adjust

	// adjust a quad in the list
	virtual	void	adjustQuad(unsigned long id,const RECT& dest_rect, const LPDIRECT3DTEXTURE9 tex, const RECT& texture_rect, D3DCOLOR col);
	virtual	void	adjustQuad(unsigned long id,const RECT& dest_rect, int texId, const RECT& texture_rect, D3DCOLOR col);

	void SliceRECT( const RECT &dest_rect, const RECT &texture_rect, RECT &destLocal, RECT &texture_Localrc );

	// perform final rendering for all queued renderable quads.
	virtual	void	doRender( bool bOuterStates = false );

	D3DCOLOR AlphaBlend(const D3DCOLOR &col ) 
	{
		return 	(((((col & 0xFF000000)>>24)*m_cAlpha)/(0xFF)) << 24) | (col & 0x00FFFFFF);
	}
	// add by pyj at 20100825
	virtual void SetUiRenderStates(IRenderer* r);

	virtual void SetFontRenderStates(IRenderer* r);

	// clear the queue
	virtual	void	clearRenderList(void);
	// setup states etc
	void	initRenderStates(IRenderer* r);

	// sort quads list according to texture
	void	sortQuads(void);

	/*!
	\brief
	structure used for all vertices.
	*/
	struct QuadVertex {
		enum
		{
			eFVF = D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1
		};
		D3DXVECTOR4 position;			//!< The position for the vertex.
		D3DCOLOR diffuse;		//!< colour of the vertex
		float tu1, tv1;			//!< texture coordinates
	};

	struct QuadInfo
	{
		LPDIRECT3DTEXTURE9	texture;
		RECTF				position;
		RECTF				texPosition;
		D3DCOLOR			col;
		QuadAddBy			qab;    //## add by pyj [20100826]
		float				z;      //## add by pyj
        bool                bUseVtColor;        // 支持彩色文字     added by zhuomeng.hu		[4/8/2011]
        D3DCOLOR            dwVtColor[4];       //  1  2
                                                //  0  3
		QuadInfo() : texture( NULL ), col( 0 ), qab( ui_quad ), z( 0.0f )
		{
            bUseVtColor = false;
            for( int i = 0; i < 4; ++i )
            {
                dwVtColor[i] = 0;
            }
		}
	};

	class _TRect
	{
	public:

		_TRect()
		{
			X = Y = Width = Height = 0;
		}

		_TRect(IN INT x,
			IN INT y,
			IN INT width,
			IN INT height)
		{
			X = x;
			Y = y;
			Width = width;
			Height = height;
		}
		_TRect(RECT rc)
		{
			X = rc.left;
			Y = rc.top;
			Width = rc.right - rc.left;
			Height = rc.bottom - rc.top;
		}
	public:

		INT X;
		INT Y;
		INT Width;
		INT Height;
	};
	void					PushWorkingArea(RECT& rc);
	void					PopWorkingArea()
	{
		m_workingAreaQue.pop_back();
	}
protected:

	bool						d_sorted;			//!< true when data in quad list is sorted.

	typedef std::vector<QuadInfo>		QuadList;
	QuadList d_quadlist;
	bool	 d_queueing;		//!< setting for queueing control.
// 	unsigned long   d_uid_counter;  //!< Counter used to generate unique quad id.
	typedef std::map< unsigned long, QuadInfo* > QuadIDMap;
// 	QuadIDMap	d_quadIDMap;
	void        Slice(_TRect& BGRect,_TRect& SrcRect);
	std::vector<_TRect>	m_workingAreaQue;
	bool	IsEnableWorkingArea()
	{
		return m_workingAreaQue.size() > 0;
	}


	LPDIRECT3DVERTEXBUFFER9								m_pVB;
	size_t												m_LastSize;
	size_t d_underused_framecount;                  //!< Number of frames elapsed since buffer utilization was above half the capacity
	size_t						m_pVBPos;		//!< index into buffer where next vertex should be put.
public:
	unsigned char			GetAlpha() const { return m_cAlpha; }
	void					SetAlpha(unsigned char val) 
	{
		if (m_cAlpha != val)
		{
			m_cAlpha = val; 
			m_AlphaChanged = true;
		}
	}
protected:
	unsigned char				m_cAlpha;
	bool						m_AlphaChanged;
};


extern UiRender* g_uiRenderCurrFrame;