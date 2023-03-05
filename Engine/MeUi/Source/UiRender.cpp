#include "MeUi/MeUi.h"
#include "FuncPerformanceLog.h"
#include "MeUi/UiRender.h"
#include "Me3d/Global.h"
#include "MeFont/MeFontSystem.h"
#include "Me3d/Engine/Engine.h"
#include "Me3d/BaseGraphics.h"

UiRender* g_uiRenderCurrFrame = NULL;



/*************************************************************************
Constants definitions
*************************************************************************/
const size_t	UiRender::VERTEX_PER_QUAD			= 6;
const size_t	UiRender::VERTEX_PER_TRIANGLE		= 3;
const size_t	UiRender::VERTEXBUFFER_INITIAL_CAPACITY	= 256;
const size_t    UiRender::UNDERUSED_FRAME_THRESHOLD = 50000; // halfs buffer every 8 minutes on 100fps

/*************************************************************************
Utility function to create a render operation and vertex buffer to render quads
*************************************************************************/
void createQuadRenderOp(
						LPDIRECT3DVERTEXBUFFER9 &m_pVB, size_t nquads)
{
	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();

	// create hardware vertex buffer
	if (SUCCEEDED(pd3dDevice->CreateVertexBuffer(nquads * sizeof(UiRender::QuadVertex),
		D3DUSAGE_WRITEONLY, UiRender::QuadVertex::eFVF, D3DPOOL_MANAGED,
		&m_pVB, 0)))
	{
	}
	


	// bind vertex buffer
// 	d_render_op.vertexData->vertexBufferBinding->setBinding(0, m_pVB);

	// complete render operation basic initialisation
// 	d_render_op.operationType = RenderOperation::OT_TRIANGLE_LIST;
// 	d_render_op.useIndexes = false;
}
void destroyQuadRenderOp(
						 LPDIRECT3DVERTEXBUFFER9 &m_pVB)
{
	if (m_pVB)
	{
		m_pVB->Release();
		m_pVB = NULL;
	}

}
unsigned long UiRender::RetriveQuad()
{
	d_sorted = false;
	QuadInfo quad;
	d_quadlist.push_back(quad);
	return d_quadlist.size() - 1;

}
unsigned long UiRender::addQuad( const RECT& dest_rect, const LPDIRECT3DTEXTURE9 tex, const RECT& texture_rect, D3DCOLOR col, QuadAddBy qab, float z/*, QuadSplitMode quad_split_mode */)
{
	{
//processbar绘制会传宽度为0的rect进来
		d_sorted = false;
		RECT destLocalI( dest_rect );
		RECT texture_LocalrcI( texture_rect );
		SliceRECT(dest_rect, texture_rect, destLocalI, texture_LocalrcI);
		RECTF destLocal = {destLocalI.left,destLocalI.top,destLocalI.right,destLocalI.bottom};
		RECTF texture_Localrc = {texture_LocalrcI.left, texture_LocalrcI.top, texture_LocalrcI.right, texture_LocalrcI.bottom};		
		
		QuadInfo quad;

		// set quad position, flipping y co-ordinates, and applying appropriate texel origin offset

		quad.position.left	= destLocal.left - 0.5;
		quad.position.right	= destLocal.right - 0.5;
		quad.position.top		= destLocal.top - 0.5;
		quad.position.bottom	= destLocal.bottom - 0.5;

		quad.z=z;

		D3DSURFACE_DESC texDesc;
		if( !tex || tex->GetLevelDesc( 0, &texDesc ) != D3D_OK )
			return -1;

		quad.texture		= (tex);
		quad.texPosition.left	= (texture_Localrc.left )/(float)texDesc.Width;
		quad.texPosition.right	= (texture_Localrc.right )/(float)texDesc.Width;
		quad.texPosition.top	= (texture_Localrc.top )/(float)texDesc.Height;
		quad.texPosition.bottom	= (texture_Localrc.bottom )/(float)texDesc.Height;

		// covert colours for ogre, note that top / bottom are switched.
		quad.col = col;

		// set quad split mode
// 		quad.splitMode = quad_split_mode;

		// set unique id.
// 		if(++d_uid_counter) d_uid_counter++;
// 		quad.id = d_uid_counter;

// 		quad.id = d_quadlist.size();
		quad.qab=qab;

		d_quadlist.push_back(quad);

		//insert to id map
// 		d_quadIDMap.insert(std::make_pair(quad.id, &(d_quadlist.back())));
		return d_quadlist.size() - 1;
	}

}

// added by zhuomeng.hu		[4/8/2011]
unsigned long UiRender::AddColorizedQuad( const RECT& dest_rect, const LPDIRECT3DTEXTURE9 tex, const RECT& texture_rect,
                               const D3DCOLOR ( &dwVtColorArray )[4], QuadAddBy qab, float z )
{
    d_sorted = false;
    RECT destLocalI( dest_rect );
    RECT texture_LocalrcI( texture_rect );
    SliceRECT( dest_rect, texture_rect, destLocalI, texture_LocalrcI );
    RECTF destLocal = { destLocalI.left, destLocalI.top, destLocalI.right, destLocalI.bottom };
    RECTF texture_Localrc = { texture_LocalrcI.left, texture_LocalrcI.top, texture_LocalrcI.right, texture_LocalrcI.bottom };		

    QuadInfo quad;
    quad.position.left      = destLocal.left - 0.5;
    quad.position.right     = destLocal.right - 0.5;
    quad.position.top       = destLocal.top - 0.5;
    quad.position.bottom    = destLocal.bottom - 0.5;
    quad.z = z;

    D3DSURFACE_DESC texDesc;
    if( !tex || tex->GetLevelDesc( 0, &texDesc ) != D3D_OK )
    {
        return -1;
    }

    quad.texture		    = tex;
    quad.texPosition.left	= texture_Localrc.left    / ( float )texDesc.Width;
    quad.texPosition.right	= texture_Localrc.right   / ( float )texDesc.Width;
    quad.texPosition.top	= texture_Localrc.top     / ( float )texDesc.Height;
    quad.texPosition.bottom	= texture_Localrc.bottom  / ( float )texDesc.Height;
    quad.col = 0;
    quad.bUseVtColor = true;
    for( int i = 0; i < 4; ++i )
    {
        quad.dwVtColor[i] = dwVtColorArray[i];
    }
    quad.qab = qab;
    d_quadlist.push_back( quad );

    return ( d_quadlist.size() - 1 );
}

void UiRender::adjustQuad( unsigned long id,const RECT& dest_rect, const LPDIRECT3DTEXTURE9 tex, const RECT& texture_rect, D3DCOLOR col )
{
	if (id >= d_quadlist.size())
	{
		return;
	}
// 	QuadIDMap::iterator it = d_quadIDMap.find(id);
// 	if(it == d_quadIDMap.end()) return;

// 	QuadInfo& quad = *(it->second);
	RECT destLocalI( dest_rect );
	RECT texture_LocalrcI( texture_rect );
	SliceRECT(dest_rect, texture_rect, destLocalI, texture_LocalrcI);
	RECTF destLocal = {destLocalI.left,destLocalI.top,destLocalI.right,destLocalI.bottom};
	RECTF texture_Localrc = {texture_LocalrcI.left, texture_LocalrcI.top, texture_LocalrcI.right, texture_LocalrcI.bottom};		

	QuadInfo& quad = d_quadlist[id];

	quad.position.left	= destLocal.left - 0.5f;
	quad.position.right	= destLocal.right - 0.5f;
	quad.position.top		= destLocal.top - 0.5f;
	quad.position.bottom	= destLocal.bottom - 0.5f;

	if(tex)
	{
		quad.texture		= (tex);
	}
	assert(quad.texture);
	D3DSURFACE_DESC texDesc;
	if( quad.texture->GetLevelDesc( 0, &texDesc ) != D3D_OK )
		return ;

	quad.texPosition.left	= (texture_Localrc.left )/(float)texDesc.Width;
	quad.texPosition.right	= (texture_Localrc.right )/(float)texDesc.Width;
	quad.texPosition.top	= (texture_Localrc.top )/(float)texDesc.Height;
	quad.texPosition.bottom	= (texture_Localrc.bottom )/(float)texDesc.Height;

	quad.col = col;

	d_sorted = false;

}

void UiRender::adjustQuad( unsigned long id,const RECT& dest_rect, int texId, const RECT& texture_rect, D3DCOLOR col )
{
	IRenderer* r = GetEngine()->GetRenderer();
	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)r->GetRealDevice();
	ITexture* pTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( texId );
	LPDIRECT3DTEXTURE9 pDxTexture = ( LPDIRECT3DTEXTURE9 )pTexture->GetData();

	adjustQuad(id,dest_rect,pDxTexture,texture_rect,col);
}

void UiRender::doRender( bool bOuterStates /* = false */ )
{
	if (!d_queueing)
	{
		return;
	}
	// Render if overlays enabled and the quad list is not empty
	if ( !d_quadlist.empty()
		)
	{
		/// Quad list needs to be sorted and thus the vertex buffer rebuilt. If not, we can
		/// reuse the vertex buffer resulting in a nice speed gain.
// 		if(1)
		if(!d_sorted)
		{
			sortQuads();
			/// Resize vertex buffer if it is too small
			size_t requestedSize = d_quadlist.size()*VERTEX_PER_QUAD;
			if(m_LastSize < requestedSize)
			{
				/// Double buffer size until smaller than requested size
				while(m_LastSize < requestedSize)
					m_LastSize = m_LastSize * 2;
				/// Reallocate the buffer
				destroyQuadRenderOp(m_pVB);
				createQuadRenderOp(m_pVB, m_LastSize);
			}
			else if(requestedSize < m_LastSize/2 && d_underused_framecount >= UNDERUSED_FRAME_THRESHOLD)
			{
				/// Resize vertex buffer if it has been to big for too long
				m_LastSize = m_LastSize / 2;
				destroyQuadRenderOp( m_pVB);
				createQuadRenderOp(m_pVB, m_LastSize);
				/// Reset underused framecount so it takes another UNDERUSED_FRAME_THRESHOLD to half again
				d_underused_framecount = 0;
			}
			/// Fill the buffer
			QuadVertex*	buffmem;
			m_pVB->Lock(0, m_LastSize * sizeof(QuadVertex), (void**)&buffmem, 0);
			// iterate over each quad in the list
			for (QuadList::iterator i = d_quadlist.begin(); i != d_quadlist.end(); ++i)
			{
				const QuadInfo& quad = (*i);
				// setup Vertex 1...
				buffmem->position.x = quad.position.left;
				buffmem->position.y = quad.position.bottom;
				buffmem->position.z = quad.z;
				buffmem->position.w = 1;
                
                // 使用顶点色   modified by zhuomeng.hu		[4/8/2011]
                buffmem->diffuse = AlphaBlend( quad.bUseVtColor ? quad.dwVtColor[0] : quad.col );

				buffmem->tu1 = quad.texPosition.left;
				buffmem->tv1 = quad.texPosition.bottom;
				++buffmem;

				// setup Vertex 2...

				// top-left to bottom-right diagonal
// 				if (quad.splitMode == TopLeftToBottomRight)
				{
					buffmem->position.x = quad.position.right;
					buffmem->position.y = quad.position.bottom;
					buffmem->position.z = quad.z;
					buffmem->position.w = 1;

                    // 使用顶点色   modified by zhuomeng.hu		[4/8/2011]
                    buffmem->diffuse = AlphaBlend( quad.bUseVtColor ? quad.dwVtColor[3] : quad.col );

					buffmem->tu1 = quad.texPosition.right;
					buffmem->tv1 = quad.texPosition.bottom;
				}
				// bottom-left to top-right diagonal
// 				else
// 				{
// 					buffmem->position.x = quad.position.right;
// 					buffmem->position.y = quad.position.top;
// 					buffmem->position.z = quad.z;
// 					buffmem->position.w = 1;
// 					buffmem->diffuse = quad.col;
// 					buffmem->tu1 = quad.texPosition.right;
// 					buffmem->tv1 = quad.texPosition.top;
// 				}
				++buffmem;

				// setup Vertex 3...
				buffmem->position.x = quad.position.left;
				buffmem->position.y = quad.position.top;
				buffmem->position.z = quad.z;
				buffmem->position.w = 1;

                // 使用顶点色   modified by zhuomeng.hu		[4/8/2011]
                buffmem->diffuse = AlphaBlend( quad.bUseVtColor ? quad.dwVtColor[1] : quad.col );

				buffmem->tu1 = quad.texPosition.left;
				buffmem->tv1 = quad.texPosition.top;
				++buffmem;

				// setup Vertex 4...
				buffmem->position.x = quad.position.right;
				buffmem->position.y = quad.position.bottom;
				buffmem->position.z = quad.z;
				buffmem->position.w = 1;
				
                // 使用顶点色   modified by zhuomeng.hu		[4/8/2011]
                buffmem->diffuse = AlphaBlend( quad.bUseVtColor ? quad.dwVtColor[3] : quad.col );

				buffmem->tu1 = quad.texPosition.right;
				buffmem->tv1 = quad.texPosition.bottom;
				++buffmem;

				// setup Vertex 5...
				buffmem->position.x = quad.position.right;
				buffmem->position.y = quad.position.top;
				buffmem->position.z = quad.z;
				buffmem->position.w = 1;
				
                // 使用顶点色   modified by zhuomeng.hu		[4/8/2011]
                buffmem->diffuse = AlphaBlend( quad.bUseVtColor ? quad.dwVtColor[2] : quad.col );

				buffmem->tu1 = quad.texPosition.right;
				buffmem->tv1 = quad.texPosition.top;
				++buffmem;

				// setup Vertex 6...

				// top-left to bottom-right diagonal
// 				if (quad.splitMode == TopLeftToBottomRight)
				{
					buffmem->position.x = quad.position.left;
					buffmem->position.y = quad.position.top;
					buffmem->position.z = quad.z;
					buffmem->position.w = 1;
					
                    // 使用顶点色   modified by zhuomeng.hu		[4/8/2011]
                    buffmem->diffuse = AlphaBlend( quad.bUseVtColor ? quad.dwVtColor[1] : quad.col );

					buffmem->tu1 = quad.texPosition.left;
					buffmem->tv1 = quad.texPosition.top;
				}
// 				// bottom-left to top-right diagonal
// 				else
// 				{
// 					buffmem->position.x = quad.position.left;
// 					buffmem->position.y = quad.position.bottom;
// 					buffmem->position.z = quad.z;
// 					buffmem->position.w = 1;
// 					buffmem->diffuse = quad.col;
// 					buffmem->tu1 = quad.texPosition.left;
// 					buffmem->tv1 = quad.texPosition.bottom;
// 				}
				++buffmem;
			}

			// ensure we leave the buffer in the unlocked state
			m_pVB->Unlock();
			m_AlphaChanged = false;
		}

		if (m_AlphaChanged)
		{
			m_AlphaChanged = false;
			/// Fill the buffer
			QuadVertex*	buffmem;
			m_pVB->Lock(0, m_LastSize * sizeof(QuadVertex), (void**)&buffmem, 0);
			// iterate over each quad in the list
			for (QuadList::iterator i = d_quadlist.begin(); i != d_quadlist.end(); ++i)
			{
				const QuadInfo& quad = (*i);

                // 使用顶点色   modified by zhuomeng.hu		[4/8/2011]
                buffmem->diffuse = AlphaBlend( quad.bUseVtColor ? quad.dwVtColor[0] : quad.col );
                ++buffmem;
                buffmem->diffuse = AlphaBlend( quad.bUseVtColor ? quad.dwVtColor[3] : quad.col );
                ++buffmem;
                buffmem->diffuse = AlphaBlend( quad.bUseVtColor ? quad.dwVtColor[1] : quad.col );
                ++buffmem;
                buffmem->diffuse = AlphaBlend( quad.bUseVtColor ? quad.dwVtColor[3] : quad.col );
                ++buffmem;
                buffmem->diffuse = AlphaBlend( quad.bUseVtColor ? quad.dwVtColor[2] : quad.col );
                ++buffmem;
                buffmem->diffuse = AlphaBlend( quad.bUseVtColor ? quad.dwVtColor[1] : quad.col );
                ++buffmem;
			}

			// ensure we leave the buffer in the unlocked state
			m_pVB->Unlock();
		}
		//??
		IRenderer* r = GetEngine()->GetRenderer();

		/// Render the buffer
		if( !bOuterStates )
			initRenderStates(r);
		else
		{
			r->SetStreamSource( 0, m_pVB,sizeof(QuadVertex) );
			r->SetFVF(QuadVertex::eFVF);
		}
		m_pVBPos = 0;

		// Iterate over each quad in the list and render it
		QuadList::iterator i = d_quadlist.begin();
		int vertexStart = 0;
		while(i != d_quadlist.end())
		{

			const LPDIRECT3DTEXTURE9 currTexture = i->texture;
			if( !bOuterStates )
			{
				if (i->qab==ui_quad)
					SetUiRenderStates(r);
				else
					SetFontRenderStates(r);
			}		
			vertexStart = m_pVBPos;
			for (; i != d_quadlist.end(); ++i)
			{
				const QuadInfo& quad = (*i);
				if (currTexture != quad.texture)
					/// If it has a different texture, render this quad in next operation
					break;
				m_pVBPos += VERTEX_PER_QUAD;
			}
			//IRenderer* r = GetEngine()->GetRenderer();
// 			LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)r->GetRealDevice();
// 			ITexture* pTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( currTexture->m_nTextureId );
			if( currTexture != NULL )
			{
				//LPDIRECT3DTEXTURE9 pd3dTexture = (LPDIRECT3DTEXTURE9)pTexture->GetData();
				r->SetTexture(0, currTexture);
				r->SetTexture(1, NULL );
			}
			r->Commit();

			int vertexCount = (m_pVBPos - vertexStart)/3;
			r->DrawPrimitive( D3DPT_TRIANGLELIST, vertexStart, vertexCount);
// 			/// Set texture, and do the render
// 			d_render_sys->_setTexture(0, true, currTexture->getOgreTexture()->getName());
// 			d_render_sys->_render(d_render_op);
		}

	}
	/// Count frames to check if utilization of vertex buffer was below half the capacity for 500,000 frames
	if(m_pVBPos < m_LastSize/2)
		d_underused_framecount++;
	else
		d_underused_framecount = 0;

}

void UiRender::clearRenderList( void )
{
	d_sorted = true;
	d_quadlist.clear();
// 	d_quadIDMap.clear();
// 	d_uid_counter = 0;

}
void UiRender::SetUiRenderStates(IRenderer* r)
{
	if (GetDrawer()->GetSupportUIZoom())
	{
		r->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		r->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR); 
		r->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	}
	else
	{
		r->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
		r->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT); 
		r->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
	}
	r->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE); //之前是D3DTOP_MODULATE   alpha混合在ControlImageList上面显示数字会有问题, 所以选为Font纹理的alpha值
	r->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	
	r->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);  //之前是D3DTA_CURRENT
}
void UiRender::SetFontRenderStates(IRenderer* r)
{
	r->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	r->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT); 
	r->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE); 
	r->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE); 
	r->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	
	r->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);  //之前是D3DTA_CURRENT
}

void UiRender::initRenderStates( IRenderer* r )
{
	r->SetRenderState(D3DRS_LIGHTING, FALSE);
	// modified, [9/13/2010 zhangjiayi]
	// 为了出现遮挡关系，最简单改法
	r->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE );
	r->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_FALSE );
	r->SetRenderState(D3DRS_FOGENABLE, FALSE);
	r->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	r->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	r->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	r->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE );
	r->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE );

	//r->SetTextureStageState( 0,D3DTSS_ALPHAOP,D3DTOP_MODULATE2X ); 
	//r->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_FALSE );  

	r->SetTextureStageState(0, D3DTSS_COLOROP,   D3DTOP_MODULATE);  // 之前是D3DTOP_MODULATE
	r->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	r->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);   // 之前是D3DTA_CURRENT 
// 	r->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE); //之前是D3DTOP_MODULATE   alpha混合在ControlImageList上面显示数字会有问题, 所以选为Font纹理的alpha值
// 	r->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	
// 	r->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);  //之前是D3DTA_CURRENT

// 	r->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);  
// 	r->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR); 
// 	r->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);  
	r->SetSamplerState(0, D3DSAMP_MIPMAPLODBIAS, 0);

	r->SetStreamSource( 0, m_pVB,sizeof(QuadVertex) );
	r->SetFVF(QuadVertex::eFVF);

}

void UiRender::sortQuads( void )
{
	if (!d_sorted)
	{
		d_sorted = true;
	}

}

UiRender::UiRender()
{
	m_LastSize	=  VERTEXBUFFER_INITIAL_CAPACITY;
	d_queueing = false;   
	d_sorted = true;
	d_underused_framecount = 0;
	m_pVBPos = 0;
// 	d_uid_counter = 0;
	m_cAlpha = 0xFF;
}

UiRender::~UiRender()
{
	destroyQuadRenderOp(m_pVB);
}

void UiRender::Initialize()
{
	m_LastSize	=  VERTEXBUFFER_INITIAL_CAPACITY;
	d_queueing = FontSystem::IsUseNewFont(); //##
	d_sorted = true;
	d_underused_framecount = 0;
	m_pVBPos = 0;

	createQuadRenderOp(m_pVB,m_LastSize);
}

void UiRender::Slice(_TRect& BGRect,_TRect& SrcRect)  
{
	_TRect& tRect = m_workingAreaQue.back();
	if (BGRect.X + BGRect.Width <= tRect.X
		|| BGRect.X >= tRect.X + tRect.Width
		|| BGRect.Y + BGRect.Height <= tRect.Y
		|| BGRect.Y >= tRect.Y + tRect.Height)
	{//out of working Area
		BGRect.Width = 0;
		BGRect.Height = 0;
		return;
	}
	const int32 nEnlargeCoef = 100000;
	if (BGRect.X < tRect.X)
	{
		int32 nCoefficient = SrcRect.Width*nEnlargeCoef/BGRect.Width;
		SrcRect.X = SrcRect.X + (tRect.X - BGRect.X)*nCoefficient/nEnlargeCoef;
		BGRect.Width = BGRect.X + BGRect.Width - tRect.X;
		SrcRect.Width = BGRect.Width*nCoefficient/nEnlargeCoef;
		BGRect.X = tRect.X;
	}
	if (BGRect.X + BGRect.Width> tRect.X + tRect.Width)
	{
		int32 nCoefficient = SrcRect.Width*nEnlargeCoef/BGRect.Width;
		BGRect.Width = (tRect.X + tRect.Width - BGRect.X);
		SrcRect.Width = BGRect.Width*nCoefficient/nEnlargeCoef;
	}

	if (BGRect.Y < tRect.Y)
	{
		int32 nCoefficient = SrcRect.Height*nEnlargeCoef/BGRect.Height;
		SrcRect.Y = SrcRect.Y + (tRect.Y - BGRect.Y)*nCoefficient/nEnlargeCoef;
		BGRect.Height = BGRect.Y + BGRect.Height - tRect.Y;
		SrcRect.Height = BGRect.Height*nCoefficient/nEnlargeCoef;
		BGRect.Y = tRect.Y;
	}
	if (BGRect.Y + BGRect.Height> tRect.Y + tRect.Height)
	{
		int32 nCoefficient = SrcRect.Height*nEnlargeCoef/BGRect.Height;
		BGRect.Height = tRect.Y + tRect.Height - BGRect.Y;
		SrcRect.Height = BGRect.Height*nCoefficient/nEnlargeCoef;
	}

// 	_ASSERT(SrcRect.Width >0);
// 	_ASSERT(SrcRect.Height >0);

}

void UiRender::SliceRECT( const RECT &dest_rect, const RECT &texture_rect, RECT &destLocal, RECT &texture_Localrc )
{
	if (IsEnableWorkingArea())
	{
		if (dest_rect.left != dest_rect.right && dest_rect.top != dest_rect.bottom && texture_rect.left != texture_rect.right && texture_rect.top != texture_rect.bottom)
		{
			_TRect _Dest(destLocal);
			_TRect _Src(texture_Localrc);
			Slice(_Dest,_Src);
			destLocal.left = _Dest.X;
			destLocal.right = _Dest.X + _Dest.Width;
			destLocal.top = _Dest.Y;
			destLocal.bottom = _Dest.Y + _Dest.Height;
			texture_Localrc.left = _Src.X;
			texture_Localrc.right = _Src.X + _Src.Width;
			texture_Localrc.top = _Src.Y;
			texture_Localrc.bottom = _Src.Y + _Src.Height;
		}
	}
}

void UiRender::PushWorkingArea( RECT& rc )
{
	_TRect tRect;
	tRect.X = rc.left;
	tRect.Y = rc.top;
	tRect.Width = rc.right - rc.left;
	tRect.Height = rc.bottom - rc.top;
	if (IsEnableWorkingArea())
	{
		_TRect tTemp(0,0,1024,1024);
		Slice(tRect,tTemp);
	}
	m_workingAreaQue.push_back(tRect);
}
