
inline void RendererDx::SetGlobalDiffuse( float r, float g, float b )
{
	guardfunc;
	//CSALocker locker(this);

	m_fGlobalDiffuse[0] = r;
	m_fGlobalDiffuse[1] = g;
	m_fGlobalDiffuse[2] = b;
	unguard;
}

inline void RendererDx::SetGlobalUOffset( int nLayer, float u )
{
	guardfunc;
	//CSALocker locker(this);

	m_fGlobalUOffset[nLayer] = u;
	unguard;
}

inline void RendererDx::SetGlobalVOffset( int nLayer, float v )
{
	guardfunc;
	//CSALocker locker(this);

	m_fGlobalVOffset[nLayer] = v;
	unguard;
}

inline void RendererDx::SetFVF( DWORD dwShader )
{
	guardfunc;
	//CSALocker locker(this);

#ifdef USE_MANUAL_RS_MANAGED
	DeferredState.SetFVF( dwShader );
#else
	m_pDevice->SetFVF( dwShader );
#endif
	unguard;
}

inline void RendererDx::SetVertices( void* pVertices )
{
	guardfunc;
	//CSALocker locker(this);

	GetCurrentSurface()->m_pbyVertices = (BYTE*)pVertices;
	unguard;
}

inline void RendererDx::SetNormals( void* pNormals )
{
	guardfunc;
	//CSALocker locker(this);

	GetCurrentSurface()->m_pbyNormals = (BYTE*)pNormals;
	unguard;
}
inline void RendererDx::SetDiffuse( void* pDiffuse )
{
	guardfunc;
	//CSALocker locker(this);

	GetCurrentSurface()->m_pbyDiffuse = (BYTE*)pDiffuse;
	unguard;
}
inline void RendererDx::SetIndices( void* pIndices )
{
	guardfunc;
	//CSALocker locker(this);

	GetCurrentSurface()->m_pbyIndices = (BYTE*)pIndices;
	unguard;
}
inline void RendererDx::SetUVs( void* pUVs, int nLayer )
{
	guardfunc;
	//CSALocker locker(this);

	GetCurrentSurface()->m_pbyUVs[nLayer] = (BYTE*)pUVs;
	unguard;
}

inline void RendererDx::Commit()
{
	guardfunc;
	//CSALocker locker(this);
	//m_pDevice->Commit();
#ifdef USE_MANUAL_RS_MANAGED
	DeferredState.Commit();
#endif
	unguard;
}

inline void RendererDx::MexCommit()
{
	guardfunc;
	//CSALocker locker(this);
	//m_pDevice->MexCommit();
#ifdef USE_MANUAL_RS_MANAGED
	DeferredState.MexCommit();
#endif
	unguard;
}

inline void RendererDx::SetIB( LPDIRECT3DINDEXBUFFER9 pIB )
{
	guardfunc;
	//CSALocker locker(this);
	GetCurrentSurface()->m_pIB = pIB;
	unguard;
}

inline void* RendererDx::GetDevice()
{
	//CSALocker locker(this);
	return NULL;
}
inline void RendererDx::SetMaterial( BYTE* pbyMtl )
{
	guardfunc;
	//CSALocker locker(this);

#ifdef USE_MANUAL_RS_MANAGED
	DeferredState.SetMaterial( (D3DMATERIAL9 *) pbyMtl );
#else
	m_pDevice->SetMaterial( (D3DMATERIAL9 *) pbyMtl );
#endif
	unguard;
}
inline void RendererDx::SetDefaultMaterial( BYTE* pbyMtl )
{
	guardfunc;
	//CSALocker locker(this);

	m_DefaultMaterial = *(D3DMATERIAL9*)pbyMtl;
	unguard;
}
inline void RendererDx::GetDefaultMaterial( BYTE* pbyMtl )
{
	guardfunc;
	//CSALocker locker(this);

	*(D3DMATERIAL9*)pbyMtl = m_DefaultMaterial;
	unguard;
}

//void* RendererDx::GetRealDevice()
//{
//	guardfunc;
////	//CSALocker locker(this);
//	return m_pDevice;
//	unguard;
//}

inline void RendererDx::EnableSpecular( BOOL bEnable )
{
	guardfunc;
	//CSALocker locker(this);

	CHRRenderSurface* pSurface = GetCurrentSurface();
	pSurface->m_bHasSpecular = bEnable;
	unguard;
}

inline void RendererDx::SetMtlSpecular( float power, float a, float r, float g, float b )
{
	guardfunc;
	//CSALocker locker(this);

	CHRRenderSurface* pSurface = GetCurrentSurface();
	D3DMATERIAL9* pMtl = &pSurface->m_mtrl;
	if( !pSurface->m_bHasSelfMtl )
	{
		pSurface->m_mtrl = m_DefaultMaterial;
		pSurface->m_bHasSelfMtl = TRUE;
	}

	//pSurface->m_bHasSpecular = TRUE;
	pMtl->Specular.a = a;
	pMtl->Specular.r = r;
	pMtl->Specular.g = g;
	pMtl->Specular.b = b;
	pMtl->Power = power;
	unguard;
}

inline void RendererDx::SetTextureHardware( DWORD dwStage, void* pTexture )
{
	guardfunc;
	//CSALocker locker(this);
#ifdef USE_MANUAL_RS_MANAGED
	DeferredState.SetTextureHardware( dwStage, (LPDIRECT3DTEXTURE9) pTexture );
#else
	m_pDevice->SetTexture( dwStage, (LPDIRECT3DTEXTURE9) pTexture );
#endif
	unguard;
}

inline void RendererDx::SetTexture( DWORD dwStage, void* pTexture )
{
	guardfunc;
	//CSALocker locker(this);
#ifdef USE_MANUAL_RS_MANAGED
	DeferredState.SetTexture( dwStage, (LPDIRECT3DTEXTURE9) pTexture );
#else
	m_pDevice->SetTexture( dwStage, (LPDIRECT3DTEXTURE9) pTexture );
#endif
	unguard;
}

inline void RendererDx::SetIndices( void* IndexData, DWORD BaseVertexIndex )
{
	guardfunc;
	//CSALocker locker(this);
#ifdef USE_MANUAL_RS_MANAGED
	DeferredState.SetIndices( (LPDIRECT3DINDEXBUFFER9) IndexData, BaseVertexIndex );
#else
	m_pDevice->SetIndices( (LPDIRECT3DINDEXBUFFER9) IndexData );
#endif
	unguard;
}

#ifndef NEW_RESMGR
inline void RendererDx::SetStreamSource( DWORD StreamNumber, void* StreamData, DWORD StreamStride )
{
	guardfunc;
	//CSALocker locker(this);
#ifdef USE_MANUAL_RS_MANAGED
	DeferredState.SetStreamSource( StreamNumber, (LPDIRECT3DVERTEXBUFFER9) StreamData, StreamStride );
#else
	m_pDevice->SetStreamSource( StreamNumber, (LPDIRECT3DVERTEXBUFFER9) StreamData, 0, StreamStride );
#endif
	unguard;
}
#else
void RendererDx::SetStreamSource( DWORD StreamNumber, class FVertexStream* StreamData, DWORD StreamStride )
{
	guardfunc;
	//CSALocker locker(this);


	//m_pDevice->SetStreamSource( StreamNumber, (IDirect3DVertexBuffer9*)StreamData, StreamStride );
	unguard;
}
#endif



inline void RendererDx::SetTextureId( short shTextureId, int nLayer )
{
	guardfunc;
	//CSALocker locker(this);

	GetCurrentSurface()->m_nTextureIds[nLayer] = shTextureId;
	unguard;
}

inline void RendererDx::SetLayerCount( int nLayerCount )
{
	guardfunc;
	//CSALocker locker(this);

	GetCurrentSurface()->m_nLayerCount = nLayerCount;
	unguard;
}

inline void RendererDx::SetShaderId( short shShaderId )
{
	guardfunc;
	//CSALocker locker(this);

	if( shShaderId == -1 )
	{
		int k = 0;
	}
	GetCurrentSurface()->m_nShaderId = shShaderId;
	unguard;
}

inline void RendererDx::SetSurfaceFVF( DWORD dwFVF )
{
	guardfunc;
	//CSALocker locker(this);

	GetCurrentSurface()->m_dwFVF = dwFVF;
	unguard;
}

inline void RendererDx::SetVertexStride( int nStride )
{
	guardfunc;
	//CSALocker locker(this);

	GetCurrentSurface()->m_nVertexStride = nStride;
	unguard;
}

inline void RendererDx::SetViewMatrix( float* pMatrix )
{
	guardfunc;
	//CSALocker locker(this);

	m_matView = *(D3DXMATRIX*)pMatrix;
	unguard;
}

inline void RendererDx::SetEyePt( float* pEyePt )
{
	guardfunc;
	//CSALocker locker(this);

	m_vEyePt.x = pEyePt[0];
	m_vEyePt.y = pEyePt[1];
	m_vEyePt.z = pEyePt[2];
// 	if (m_d3dTerrainEffect)
// 	{
// 		m_d3dTerrainEffect->SetValue( "eye", &m_vEyePt, sizeof(D3DXVECTOR3) );
// 	}
	unguard;
}

inline void RendererDx::SetLookatPt( float* pLookatPt )
{
	guardfunc;
	//CSALocker locker(this);

	m_vLookatPt.x = pLookatPt[0];
	m_vLookatPt.y = pLookatPt[1];
	m_vLookatPt.z = pLookatPt[2];
	unguard;
}

inline void RendererDx::SetGlobalTexture( short shTextureID )
{
	guardfunc;
	//CSALocker locker(this);

	m_shGlobalTextureID = shTextureID;
	unguard;
}

inline short RendererDx::GetGlobalTexture()
{
	guardfunc;
	//CSALocker locker(this);

	return m_shGlobalTextureID;
	unguard;
}

inline void RendererDx::InitTerrainTransform( )
{
	if (m_d3dTerrainEffect)
	{
		D3DXMATRIX world;
		D3DXMatrixIdentity(&world);
		m_d3dTerrainEffect->SetMatrix( "viewMatrix", &m_view ); //lyh++ ÉãÏñ¼ÇµÃÊÓÍ¼¾ØÕó
		m_d3dTerrainEffect->SetMatrix( "world", &world );
		D3DXMATRIXA16 worldViewProj = m_view * m_proj;
		m_d3dTerrainEffect->SetMatrix( "worldViewProj", &worldViewProj );
		m_d3dTerrainEffect->SetValue( "eye", &m_vEyePt, sizeof(D3DXVECTOR3) );
	}
}


inline void RendererDx::SetTransform( DWORD State,CONST FLOAT* pMatrix)
{
	guardfunc;
	//CSALocker locker(this);

	m_pDevice->SetTransform( (D3DTRANSFORMSTATETYPE)State, (CONST D3DMATRIX*)pMatrix );

	// add [5/27/2008 whu]
	if ( D3DTS_WORLD == (D3DTRANSFORMSTATETYPE)State )
	{
		m_world = *((CONST D3DXMATRIX*)pMatrix);
// 		if (m_d3dTerrainEffect)
// 		{
// 			m_d3dTerrainEffect->SetMatrix( "world", &m_world );
// 		}
	}
	else if ( D3DTS_VIEW == (D3DTRANSFORMSTATETYPE)State )
	{
		m_view = *((CONST D3DXMATRIX*)pMatrix);
	}
	else if ( D3DTS_PROJECTION == (D3DTRANSFORMSTATETYPE)State )
	{
		m_proj = *((CONST D3DXMATRIX*)pMatrix);
	}

	// added, [8/12/2010 zhangjiayi]
	m_worldViewProj = m_world * m_view * m_proj;
// 	if (m_d3dTerrainEffect)
// 	{
// 		m_worldViewProj = m_world * m_view * m_proj;
// 		m_d3dTerrainEffect->SetMatrix( "worldViewProj", &m_worldViewProj );
// 	}
	//	m_pDevice->SetTransform( State, (D3DMATRIX*)pMatrix );
	unguard;
}



inline void RendererDx::SetSamplerState( DWORD dwStage, DWORD dwType, DWORD dwValue )
{
	guardfunc;
	//CSALocker locker(this);
#ifdef USE_MANUAL_RS_MANAGED
	DeferredState.SetSamplerState( dwStage, (D3DSAMPLERSTATETYPE) dwType, dwValue );
#else
	m_pDevice->SetSamplerState( dwStage, (D3DSAMPLERSTATETYPE) dwType, dwValue );
#endif
	unguard;
}