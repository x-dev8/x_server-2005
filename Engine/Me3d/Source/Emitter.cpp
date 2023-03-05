
#include "Me3d/Vector.h"
#include "Me3d/MathEx.h"
#include "Me3d/Emitter.h"
//#include "shader.h"
#include "Me3d/Config.h"
#include "FuncPerformanceLog.h"
#include <math.h>
#include "Dxsdk/d3dx9.h"
#include "Me3d/Engine/Engine.h"
#include "Me3d/Engine/Renderer.h"
#define MAX_EMITTER_INDEX 1024*6// 16 -> 6 [11/4/2010 zhangjiayi]
static short m_nCWIndexBuffer[MAX_EMITTER_INDEX];
static short m_nCCWIndexBuffer[MAX_EMITTER_INDEX];
static LPDIRECT3DINDEXBUFFER9 m_D9IndexBuffer = NULL;
static bool m_bIndexBufferInitialized = false;
Emitter theEmitter;
Emitter::Emitter()
{
	guardfunc;
	if( !m_bIndexBufferInitialized )
	{
		m_bIndexBufferInitialized = true;
		for( int i = 0; i < MAX_EMITTER_INDEX/6; i++ )
		{
			m_nCWIndexBuffer[i*6+0] = i*4+1;
			m_nCWIndexBuffer[i*6+1] = i*4+0;
			m_nCWIndexBuffer[i*6+2] = i*4+2;

			m_nCWIndexBuffer[i*6+3] = i*4+2;
			m_nCWIndexBuffer[i*6+4] = i*4+3;
			m_nCWIndexBuffer[i*6+5] = i*4+1;

			m_nCCWIndexBuffer[i*6+0] = i*4+0;
			m_nCCWIndexBuffer[i*6+1] = i*4+1;
			m_nCCWIndexBuffer[i*6+2] = i*4+2;

			m_nCCWIndexBuffer[i*6+3] = i*4+3;
			m_nCCWIndexBuffer[i*6+4] = i*4+2;
			m_nCCWIndexBuffer[i*6+5] = i*4+1;
		}

	}
	unguard;
}

Emitter::~Emitter()
{
	guardfunc;
	unguard;
}
short* Emitter::GetCWIndexBuffer()
{
	guardfunc;
	return m_nCWIndexBuffer;
	unguard;
}
short* Emitter:: GetCCWIndexBuffer()
{
	guardfunc;
	return m_nCCWIndexBuffer;
	unguard;
}

LPDIRECT3DINDEXBUFFER9 Emitter::GetD9IndexBuffer()
{
	if (m_D9IndexBuffer == NULL)
	{
		HRESULT hr;
		LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();

		short* shIBFace = NULL;
		if( !m_D9IndexBuffer )
		{
			while(1)
			{
				hr = pDev->CreateIndexBuffer( 1024 * 6 *sizeof(short), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_D9IndexBuffer, NULL );
				if( SUCCEEDED(hr) ) break;
			}
		}

		while(1)
		{
			hr = m_D9IndexBuffer->Lock( 0, 0, (void**)&shIBFace, 0 );
			if( SUCCEEDED(hr) ) break;
		}

		memcpy( shIBFace, m_nCWIndexBuffer, 1024 * 6 *sizeof(short) );

		while(1)
		{
			hr = m_D9IndexBuffer->Unlock();
			if( SUCCEEDED(hr) ) break;
		}
	}
	return m_D9IndexBuffer;
}