#pragma once

#include "Me3d/Engine/MeSorter.h"

MeSmartPointer( MeTextureSorter );

/** °´ÕÕÌùÍ¼ÅÅĞò
@desc:
	äÖÈ¾Ê±²»ĞèÒªÇĞ»»ÌùÍ¼×´Ì¬
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

/** °´ÕÕÌùÍ¼ÅÅĞòÊµÏÖ
*/
struct MeTextureSorterImpl //: public binary_function <IRenderable*, IRenderable*, bool> 
{
	bool operator()(
		const MeSorter::RenderableBase* pLeft, 
		const MeSorter::RenderableBase* pRight
		) const;	
};
