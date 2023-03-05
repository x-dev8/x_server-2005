#pragma once

#include "Me3d/Engine/MeCollector.h"
#include "Me3d/Engine/MeRenderObject.h"

struct SEmitterVertex;
class MeAlphaCollector : public MeCollector
{
public:
	struct AlphaRenderableStr
	{
		float m_fDis;
		SortRenderable* m_pObj;
		AlphaRenderableStr( float f, SortRenderable* p )
		{
			m_fDis = f;
			m_pObj = p;
		}
	};

	/// renderlist
	typedef std::vector< AlphaRenderableStr > AlphaRenderableList;	
	typedef AlphaRenderableList::iterator AlphaRenderableListIter;

public:
	MeAlphaCollector();
	virtual ~MeAlphaCollector(){}

	/// �Ƿ���alphablend��ʾ
	virtual bool IsCollectible( MeSorter::RenderableBasePtr pkObj );

	/// render
	virtual void DoRender();

protected:
	void						Sort();
	AlphaRenderableList			m_AlphaItems;
	std::vector< SortRenderable* > 			m_NoSortAlphaItems;
};