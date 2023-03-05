#pragma once

#include "Me3d/Engine/MeSorter.h"

MeSmartPointer( MeTextureSorter );

/** ������ͼ����
@desc:
	��Ⱦʱ����Ҫ�л���ͼ״̬
*/
class MeTextureSorter : public MeSorter
{
public:
	MeTextureSorter(){}
	virtual ~MeTextureSorter(){}

	virtual void StartSorting();
	virtual void FinishSorting();

protected:
	void Sort();
};

/** ������ͼ����ʵ��
*/
struct MeTextureSorterImpl //: public binary_function <IRenderable*, IRenderable*, bool> 
{
	bool operator()(
		const MeSorter::RenderableBase* pLeft, 
		const MeSorter::RenderableBase* pRight
		) const;	
};
