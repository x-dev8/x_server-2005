#pragma once

//#include "DllImportorDef.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Renderer.h"
#include "Renderable.h"
#include "Mex.h"
#include <assert.h>
#define FRAMEPERSEC 30.0f
#define ONEFRAMEINTERVAL (1000.0f/FRAMEPERSEC)
class IEngine
{
public:
	virtual ~IEngine(){};

	virtual ITextureManager*	GetTextureManager() = 0;
	virtual IRenderer*	GetRenderer() = 0;
	//virtual IRenderer*	GetSortedSurfaceRenderer() = 0;
	virtual IMex*			CreateMex() = 0;
	virtual void			Release() = 0;
	virtual void			UseAbstractPath( BOOL bUse ) = 0;
	virtual BOOL			IsUseAbstractPath() = 0;
	virtual void			UseTextureMultiThreadLoading( BOOL bUse ) = 0;
	virtual BOOL			IsUseTextureMultiThreadLoading() = 0;
	virtual BYTE*			AllocShareBuffer( DWORD dwBufferSize ) = 0;
	virtual int				GetMaxPartNum() = 0;
	virtual void			SetMaxPartNum( int num ) = 0;
	virtual BOOL			IsEffectMirror() = 0;
	virtual void			SetEffectMirror(BOOL flag) = 0;

};
//DEFINE_DLLIMPORT_CLASS(CEngineImportor,IEngine)


extern void SetEngine( IEngine* pEngine );
extern IEngine* GetEngine();
