#include "Me3d/Include.h"
#include "Me3d/Engine/RendererDx8.h"

#include "Me3d/Engine/RendererDX.h"
#include "Me3d/Engine/TextureManagerInstance.h"
#include "Me3d/Engine/EngineInstance.h"
//#include "../Include/HRMexDll.h"
#include "Me3d/Model/Mex2.h"

static IEngine* gs_pEngine = NULL;
void SetEngine( IEngine* pEngine )
{
	guardfunc;
	gs_pEngine = pEngine;
	unguard;
}
IEngine* GetEngine()
{
	guardfunc;
	return gs_pEngine;
	unguard;
}
//extern void TextureLoadingThread(void* p);
CEngineInstance::CEngineInstance(void):
m_pTextureMgr(NULL),
m_pRenderer(NULL),
m_bUseAbstrackPath(FALSE),
m_bUseTextureThreadLoading(FALSE),
m_pbyShareBuffer(NULL),
m_dwShareBufferSize(0),
m_bEffectMirror(TRUE)
{
	guardfunc;
	m_pTextureMgr = new CHRTextureManagerInstance;
	m_pRenderer = new RendererDx;

    /*Md5Manager::Instance().Initialize( "DATA/files_info.data" );*/
	
	unguard;
}

CEngineInstance::~CEngineInstance(void)
{
	guardfunc;
	assert( m_pRenderer == NULL );
	assert( m_pTextureMgr == NULL );
	unguard;
}
void CEngineInstance::Release()
{
	guardfunc;
	if( m_pTextureMgr )
	{
		delete m_pTextureMgr;
		m_pTextureMgr = NULL;
	}
	if( m_pRenderer )
	{
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	if( m_pbyShareBuffer )
	{
		delete[] m_pbyShareBuffer;
		m_pbyShareBuffer = NULL;
	}
	delete this;
	unguard;
} 
IMex*	CEngineInstance::CreateMex()
{
	guardfunc;
	return MeNew Mex2;
	unguard;
}
BYTE* CEngineInstance::AllocShareBuffer( DWORD dwBufferSize )
{
	guardfunc;
	if( m_pbyShareBuffer == NULL )
	{
		m_dwShareBufferSize = dwBufferSize;
		m_pbyShareBuffer = MeDefaultNew BYTE[m_dwShareBufferSize];
	}
	else if( dwBufferSize > m_dwShareBufferSize )
	{
		delete[] m_pbyShareBuffer;
		m_dwShareBufferSize = dwBufferSize;
		m_pbyShareBuffer = MeDefaultNew BYTE[m_dwShareBufferSize];
	}
	return m_pbyShareBuffer;
	unguard;
}

int CEngineInstance::GetMaxPartNum()
{
	return Mex2ParticleEmitter::GetMaxPartNum();
}

void CEngineInstance::SetMaxPartNum( int num )
{
	Mex2ParticleEmitter::SetMaxPartNum( num );
}