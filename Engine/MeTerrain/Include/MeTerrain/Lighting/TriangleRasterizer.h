//-----------------------------------------------------------------------------
// File:	TriangleRasterizer.h
// Desc:	计算三角形光栅线，辅助类
// Create: 	01/20/2011
// Author:	Qiu Li
//
// Copyright ShenWang 2011 - All Rights Reserved.
//-----------------------------------------------------------------------------
#ifndef TRIANGLE_RASTERIZER_H
#define TRIANGLE_RASTERIZER_H

template<typename InterpolantFunctor> 
class TriangleRasterizer
{
public:
	TriangleRasterizer(InterpolantFunctor& InFunctor) : Functor(InFunctor), m_uiNormalId(0), m_uiFaceIndex(0) {};

	// DrawTriangleTrapezoid
	typedef typename InterpolantFunctor::InterpolantType InterpolantType;

	template< class T > void Exchange( T& A, T& B )
	{
		const T Temp = A;
		A = B;
		B = Temp;
	}

	void DrawTriangleTrapezoid(
		InterpolantType TopMinInterpolant,
		InterpolantType DeltaMinInterpolant,
		InterpolantType TopMaxInterpolant,
		InterpolantType DeltaMaxInterpolant,
		FLOAT TopMinX,
		FLOAT DeltaMinX,
		FLOAT TopMaxX,
		FLOAT DeltaMaxX,
		FLOAT MinY,
		FLOAT MaxY
		)
	{
		INT	IntMinY = (INT)ceilf(MinY),
			IntMaxY = (INT)ceilf(MaxY);

		for(INT IntY = IntMinY;IntY < IntMaxY;IntY++)
		{
			FLOAT			Y = IntY - MinY,
				MinX = TopMinX + DeltaMinX * Y,
				MaxX = TopMaxX + DeltaMaxX * Y;
			InterpolantType	MinInterpolant = TopMinInterpolant + DeltaMinInterpolant * Y,
				MaxInterpolant = TopMaxInterpolant + DeltaMaxInterpolant * Y;

			if(MinX > MaxX)
			{
				Exchange(MinX,MaxX);
				Exchange(MinInterpolant,MaxInterpolant);
			}

			if(MaxX > MinX)
			{
				INT IntMinX = (INT)ceilf(MinX),
					IntMaxX = (INT)ceilf(MaxX);
				InterpolantType	DeltaInterpolant = (MaxInterpolant - MinInterpolant) / (MaxX - MinX);

				for(INT X = IntMinX;X < IntMaxX;X++)
					Functor.ProcessPixel(X, IntY, MinInterpolant + DeltaInterpolant * (X - MinX), m_uiNormalId, m_uiFaceIndex);
			}
		}
	}

	void DrawTriangle(const InterpolantType& I0,const InterpolantType& I1,const InterpolantType& I2,
					  const Vector2& P0,const Vector2& P1,const Vector2& P2, UINT uiNormalIndex = 0, UINT uiFaceIndex = 0)
	{
		InterpolantType	Interpolants[3] = { I0, I1, I2 };
		Vector2			Points[3] = { P0, P1, P2 };

		m_uiNormalId = uiNormalIndex;
		m_uiFaceIndex = uiFaceIndex;

		// 找到最高点
		if(Points[1].y < Points[0].y && Points[1].y <= Points[2].y)
		{
			Exchange(Points[0],Points[1]);
			Exchange(Interpolants[0],Interpolants[1]);
		}
		else if(Points[2].y < Points[0].y && Points[2].y <= Points[1].y)
		{
			Exchange(Points[0],Points[2]);
			Exchange(Interpolants[0],Interpolants[2]);
		}

		// 找到最低点
		if(Points[1].y > Points[2].y)
		{
			Exchange(Points[2],Points[1]);
			Exchange(Interpolants[2],Interpolants[1]);
		}

		// 计算边的梯度
		FLOAT TopMinDiffX = (Points[1].x - Points[0].x) / (Points[1].y - Points[0].y),
			  TopMaxDiffX = (Points[2].x - Points[0].x) / (Points[2].y - Points[0].y);
		InterpolantType	TopMinDiffInterpolant = (Interpolants[1] - Interpolants[0]) / (Points[1].y - Points[0].y),
						TopMaxDiffInterpolant = (Interpolants[2] - Interpolants[0]) / (Points[2].y - Points[0].y);

		FLOAT BottomMinDiffX = (Points[2].x - Points[1].x) / (Points[2].y - Points[1].y),
			  BottomMaxDiffX = (Points[2].x - Points[0].x) / (Points[2].y - Points[0].y);
		InterpolantType	BottomMinDiffInterpolant = (Interpolants[2] - Interpolants[1]) / (Points[2].y - Points[1].y),
						BottomMaxDiffInterpolant = (Interpolants[2] - Interpolants[0]) / (Points[2].y - Points[0].y);

		DrawTriangleTrapezoid(
			Interpolants[0],
			TopMinDiffInterpolant,
			Interpolants[0],
			TopMaxDiffInterpolant,
			Points[0].x,
			TopMinDiffX,
			Points[0].x,
			TopMaxDiffX,
			Points[0].y,
			Points[1].y
			);

		DrawTriangleTrapezoid(
			Interpolants[1],
			BottomMinDiffInterpolant,
			Interpolants[0] + TopMaxDiffInterpolant * (Points[1].y - Points[0].y),
			BottomMaxDiffInterpolant,
			Points[1].x,
			BottomMinDiffX,
			Points[0].x + TopMaxDiffX * (Points[1].y - Points[0].y),
			BottomMaxDiffX,
			Points[1].y,
			Points[2].y
			);
	}

private:
	InterpolantFunctor Functor;
	UINT m_uiNormalId;
	UINT m_uiFaceIndex;
};


#endif /* TRIANGLE_RASTERIZER_H */
