#pragma once

#include <MeFoundation/MeRefObject.h>
#include <MeFoundation/MeSmartPointer.h>
#include "Me3d/Engine/MeRenderObject.h"


MeSmartPointer( MeSorter );

/**
@desc:
	≈≈–Úª˘¿‡
*/
class MeSorter : public MeRefObject
{
public:
	/// render type
	typedef SortRenderable RenderableBase;
	typedef SortRenderable* RenderableBasePtr;

	struct RenderableStr
	{
		RenderableBasePtr m_pRenderable;
		unsigned __int64 m_ui64Key;
		RenderableStr( RenderableBasePtr p, unsigned __int64 k )
		{
			m_pRenderable = p;
			m_ui64Key = k;
		}
	};

	/// renderlist
	typedef std::vector< RenderableStr > RenderableList;	
	typedef RenderableList::iterator RenderableListIter;

public:
	MeSorter(){
		m_kItems.reserve( 1000 );
	}
	virtual ~MeSorter(){
		Clear();
	}
	
	virtual void StartSorting() = 0;
	virtual void FinishSorting() = 0;

	virtual bool AddObject( MeSorter::RenderableBasePtr pkObj ){		
		//m_kItems.push_back( pkObj );
		m_kItems.push_back( RenderableStr( pkObj, pkObj->GetSortKey() ) );
		return true;
	}
	void	Clear()
	{
		for( MeSorter::RenderableListIter it = m_kItems.begin();
			it != m_kItems.end(); ++ it )
		{
			if( (*it).m_pRenderable )
			{
				(*it).m_pRenderable->ClearOtherInfo();
			}
		}
		m_kItems.clear();
	}
protected:
	MeSorter::RenderableList m_kItems;
};