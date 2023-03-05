#pragma once

#include "Me3d/Engine/MeCollector.h"
#include "Me3d/Engine/TextureDX8.h"

/** ����Ч���ռ���
@desc:
	����ʵ��ShimmerЧ�����ռ����崦�����
	�Ӻ�ǰ������
*/
class MeShimmerCollector : public MeCollector
{
public:
	virtual ~MeShimmerCollector();

	/// �Ƿ���shimmer��ʾ
	virtual bool IsCollectible( MeSorter::RenderableBasePtr pkObj );

	/// ��Ⱦ������backbuffer
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
	/// ���ڿ���backbuffer����Ϣ������shimmerЧ��
	static ITexture* ms_pkFrameTexture;
	static short ms_sFrameTexId;
	/// ���ڿ���rendertarget to texture
	static LPDIRECT3DSURFACE9 ms_offScreenSurf;

};