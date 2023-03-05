//-----------------------------------------------------------------------------
// File:	SurfaceLayoutMgr.h
// Desc:	灯光图打包到一张贴图里
// Create: 	01/14/2011
// Author:	Qiu Li
//
// Copyright ShenWang 2011 - All Rights Reserved.
//-----------------------------------------------------------------------------
#ifndef SURFACE_LAYOUTMGR_H
#define SURFACE_LAYOUTMGR_H
#include "MeRTLibs.h"
#include <MeFoundation/MeAllocatedObject.h>
#include "MeTerrain/Lighting/LightMapTexture.h"

// 把灯光图打包到一个贴图里
class SurfaceLayout: public MeCommonAllocObj<SurfaceLayoutMgr>
{
public:

	// 构造
	SurfaceLayout(INT InWidth,INT InHeight):
	Width(InWidth)
	,Height(InHeight)
	{
		AllocatedTexels.resize(InHeight, 0);
	}

	BOOL AddSurface(INT* OffsetX,INT* OffsetY,INT SizeX,INT SizeY)
	{
		assert(SizeX > 0 && SizeX <= Width);
		assert(SizeY > 0 && SizeY <= Height);

		INT	BestX = Width,
			BestY = Height,
			BestWaste = Width * Height;

		for(INT Y = 0;Y <= (Height - SizeY); Y++)
		{
			INT	MaxX = 0,
				Waste = 0;

			for(INT Row = 0;Row < SizeY;Row++)
				MaxX = max(AllocatedTexels[Y + Row],MaxX);

			for(INT Row = 0;Row < SizeY;Row++)
				Waste += MaxX - AllocatedTexels[Y + Row];

			if(MaxX <= Width - SizeX && Waste < BestWaste)
			{
				BestX = MaxX;
				BestY = Y;
				BestWaste = Waste;
			}
		}

		if(BestX <= Width - SizeX && BestY <= Height - SizeY)
		{
			*OffsetX = BestX;
			*OffsetY = BestY;

			for(INT Row = 0;Row < SizeY;Row++)
				AllocatedTexels[BestY + Row] = BestX + SizeX;

			return 1;
		}
		else
			return 0;
	}

protected:
	INT	Width, Height;
	std::vector<INT> AllocatedTexels;
};


class SurfaceLayoutMgr: public MeCommonAllocObj<SurfaceLayoutMgr>
{
public:
	SurfaceLayoutMgr(std::vector<LightMapTexture*>& InTextures, UINT Padding = 2) : Textures(InTextures)
	{
		BaseLightMapIndex = InTextures.size();
		BorderPadding = Padding;
	}

	INT AddSurface(INT* OffsetX,INT* OffsetY,INT SizeX,INT SizeY)
	{
		// 处理size + padding超出layout的情况，可以减少padding值使之能放入surface
		INT UsedXPadding = (SizeX + 2 * BorderPadding) > LIGHTMAP_TEXTURE_WIDTH ? (LIGHTMAP_TEXTURE_WIDTH - SizeX)/2 : BorderPadding;
		INT UsedYPadding = (SizeY + 2 * BorderPadding) > LIGHTMAP_TEXTURE_HEIGHT ? (LIGHTMAP_TEXTURE_HEIGHT - SizeY)/2 : BorderPadding;
		assert(UsedXPadding >= 0);
		assert(UsedYPadding >= 0);

		INT PaddedSizeX = SizeX + 2 * UsedXPadding;
		INT PaddedSizeY = SizeY + 2 * UsedYPadding;

		// 是否能放入已有贴图
		for (INT i=0; i < SurfaceLayouts.size(); ++i)
		{
			if (SurfaceLayouts[i].AddSurface(OffsetX, OffsetY, PaddedSizeX, PaddedSizeY))
			{
				*OffsetX += UsedXPadding;
				*OffsetY += UsedYPadding;
				return BaseLightMapIndex +i;
			}
		}

		AllocateSurfaceLayout();
		INT iLayout = SurfaceLayouts.size()-1;

		BOOL Succeeded = SurfaceLayouts[iLayout].AddSurface(OffsetX, OffsetY, PaddedSizeX, PaddedSizeY);
		assert(Succeeded);
		*OffsetX += UsedXPadding;
		*OffsetY += UsedYPadding;

		return BaseLightMapIndex + iLayout;
	}

	LightMapTexture* GetSurface(INT Index)
	{
		if (Index < Textures.size())
			return Textures[Index];

		return 0;
	}

	inline INT GetBorderPadding()
	{
		return BorderPadding;
	}

private:
	void AllocateSurfaceLayout()
	{
		LightMapTexture* tex = new LightMapTexture(-1, Textures.size());
		// 注意这个Textures是Tile类中的成员变量的引用, 这种写法不太推荐, 极其隐晦
		Textures.push_back(tex); //lyh++ 压入光照图

		SurfaceLayout layout(LIGHTMAP_TEXTURE_WIDTH, LIGHTMAP_TEXTURE_HEIGHT);
		SurfaceLayouts.push_back(layout);
	}

	INT								BorderPadding;
	std::vector<LightMapTexture*>&	Textures;
	INT								BaseLightMapIndex;
	std::vector<SurfaceLayout>		SurfaceLayouts;
};

#endif /* SURFACE_LAYOUTMGR_H */
