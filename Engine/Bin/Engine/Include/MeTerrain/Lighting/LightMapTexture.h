//-----------------------------------------------------------------------------
// File:	LightMapTexture.h
// Desc:	�ƹ�ͼ����ͼ����
// Create: 	01/20/2011
// Author:	Qiu Li
//
// Copyright ShenWang 2011 - All Rights Reserved.
//-----------------------------------------------------------------------------
#ifndef LIGHT_MAP_TEXTURE_H
#define LIGHT_MAP_TEXTURE_H
#include "MeTerrain/NiColor.h"
//
//	Definitions.
//

#define LIGHTMAP_MAX_WIDTH			512
#define LIGHTMAP_MAX_HEIGHT			512

#define LIGHTMAP_TEXTURE_WIDTH		512
#define LIGHTMAP_TEXTURE_HEIGHT		512

//
//	LightMapTexture
//

class LightMapTexture
{
public:
	// Constructors.
	LightMapTexture(): m_nTextureId(-1), m_nLocalId(-1), m_pBitmap(NULL) {}
	LightMapTexture(int InTextureId, int InLocalId): m_nTextureId(InTextureId), m_nLocalId(InLocalId), m_pBitmap(NULL) {}
	virtual ~LightMapTexture()
	{
		if( m_pBitmap )
			delete[] m_pBitmap;
		m_pBitmap = NULL;
	}

	void SetTextureId( int textureid ) { m_nTextureId = textureid; }
	int GetTextureId() { return m_nTextureId; }

	void SetLocalId( int localid ) { m_nLocalId = localid; }
	int GetLocalId() { return m_nLocalId; }

	INT GetWidth() { return LIGHTMAP_TEXTURE_WIDTH; }
	INT GetHeight() { return LIGHTMAP_TEXTURE_HEIGHT; }

	NiColorB* GetBitmap() { return m_pBitmap; }
	void AllocateBitmap()
	{
		if( m_pBitmap )
			delete[] m_pBitmap;

		m_pBitmap = new NiColorB[LIGHTMAP_TEXTURE_WIDTH*LIGHTMAP_TEXTURE_HEIGHT];
		assert(m_pBitmap);
		memset(m_pBitmap, 0, LIGHTMAP_TEXTURE_WIDTH*LIGHTMAP_TEXTURE_HEIGHT*sizeof(NiColorB));
	}
	
protected:
	// ITextureManager��ע���ȡlightmap texture id
	int		m_nTextureId;

	// ��ͼ�� + "_LightMap" + m_nLocalId���ɵƹ�ͼ��
	int		m_nLocalId;

	// λͼ���ݣ��༭��ʹ��
	NiColorB*	m_pBitmap;
};

#endif /* LIGHT_MAP_TEXTURE_H */
