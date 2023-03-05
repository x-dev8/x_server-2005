#pragma once
#include "Engine.h"
class CEngineInstance:public IEngine
{
public:
	CEngineInstance(void);
	~CEngineInstance(void);

	ITextureManager*	GetTextureManager(){ return m_pTextureMgr; }
	IRenderer*	GetRenderer(){ return m_pRenderer; }
	//IRenderer*	GetSortedSurfaceRenderer(){ return m_pSortedSurfaceRenderer; }
	IMex*			CreateMex();
	void			UseAbstractPath( BOOL bUse ){ m_bUseAbstrackPath = bUse; }
	BOOL			IsUseAbstractPath(){ return m_bUseAbstrackPath; }
	void			UseTextureMultiThreadLoading( BOOL bUse ){ m_bUseTextureThreadLoading = bUse; }
	BOOL			IsUseTextureMultiThreadLoading(){ return m_bUseTextureThreadLoading; }

	BYTE*			AllocShareBuffer( DWORD dwBufferSize );
	void			Release();

	int				GetMaxPartNum();
	void			SetMaxPartNum( int num );

	BOOL			IsEffectMirror() { return m_bEffectMirror; }
	void			SetEffectMirror(BOOL flag) { m_bEffectMirror = flag; }

protected:
	ITextureManager*	m_pTextureMgr;
	IRenderer*	m_pRenderer;
	BOOL			m_bUseAbstrackPath;
	BOOL			m_bUseTextureThreadLoading;
	
	BYTE*			m_pbyShareBuffer;
	DWORD			m_dwShareBufferSize;

	BOOL			m_bEffectMirror;		// 特效镜像，默认true，非常丑陋的方法，使水浒和轩辕引擎能兼容
};

