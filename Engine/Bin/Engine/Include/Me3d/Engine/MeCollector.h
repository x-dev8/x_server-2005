#pragma once

#include <MeFoundation/MeRefObject.h>
#include <MeFoundation/MeSmartPointer.h>
#include "Me3d/Engine/MeRenderObject.h"
#include "Me3d/Engine/MeSorter.h"


/** �ռ�����
@desc:
	��Ⱦʱ��������������Ⱦ��Ԫ�ռ�������
	�ȴ�֮������⴦��
*/
MeSmartPointer( MeCollector );
class MeCollector : public MeRefObject
{
public:
	MeCollector();
	virtual ~MeCollector();

	/// �Ƿ��ǿ��ռ��Ķ���
	virtual bool IsCollectible( MeSorter::RenderableBasePtr pkObj ) = 0;
	virtual bool IsFreshObject( MeSorter::RenderableBasePtr pkObject )
	{
		MeSorter::RenderableListIter iter = m_kItems.begin();
		while (iter != m_kItems.end())
		{
// 			if ((*iter).m_ui64Key != pkObject->GetSortKey())
// 			{
// 				return true;
// 			}
			if ((*iter).m_pRenderable == pkObject)
			{
				return false;
			}
			++iter;
		}
		return true;
	}

	/// ��ӵ�����
	virtual bool AddObject( MeSorter::RenderableBasePtr pkObj ){
		if( IsCollectible( pkObj ) )
		{
			m_kItems.push_back( MeSorter::RenderableStr( pkObj, pkObj->GetSortKey() ) );
			return true;
		}
		return false;
	}

	/// ��Ⱦ
	virtual void DoRender() = 0;	
	void Clear() {
		for( MeSorter::RenderableListIter it = m_kItems.begin();
			it != m_kItems.end(); ++ it )
		{
			if( (*it).m_pRenderable )
			{
				(*it).m_pRenderable->ClearOtherInfo( true, true );
			}
		}
		m_kItems.clear();
	}	

	void SetEnable( bool bEnable );

protected:
	MeSorter::RenderableList m_kItems;
	bool m_bUseCollector;
};