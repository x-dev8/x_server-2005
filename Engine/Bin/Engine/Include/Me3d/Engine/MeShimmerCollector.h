#pragma once

#include "Me3d/Engine/MeCollector.h"
#include "Me3d/Engine/TextureDX8.h"

/** 特殊效果收集类
@desc:
	用于实现Shimmer效果，收集后集体处理，配合
	从后到前的排序。
*/
class MeShimmerCollector : public MeCollector
{
public:
	virtual ~MeShimmerCollector();

	/// 是否有shimmer标示
	virtual bool IsCollectible( MeSorter::RenderableBasePtr pkObj );

	/// 渲染，拷贝backbuffer
	virtual void DoRender();

public:
	static void CreateFrameTexture( unsigned int uiWidth, 
		unsigned int uiHeight, LPDIRECT3DTEXTURE9 pQuadTex );

	static void DeleteFrameTexture();

	static short GetFrameTextureId(){ 
		return ms_sFrameTexId;
	}

	static ITexture* GetFrameTexture(){
		return ms_pkFrameTexture;
	}
protected:
	/// 用于拷贝backbuffer的信息，处理shimmer效果
	static ITexture* ms_pkFrameTexture;
	static short ms_sFrameTexId;
	/// 用于拷贝rendertarget to texture
	static LPDIRECT3DSURFACE9 ms_offScreenSurf;

};