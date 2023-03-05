#pragma once

#include "Me3d/Engine/MeSorter.h"

/** ∞¥Œª≈≈–Ú
@desc:
*/
MeSmartPointer( MeBitSorter );
class MeBitSorter : public MeSorter
{
public:
	MeBitSorter(){}
	virtual ~MeBitSorter(){}

	virtual void StartSorting();
	virtual void FinishSorting();

protected:
	void Sort();
};

/** sort implement
*/
 //struct MeBitSorterImpl //: public binary_function <IRenderable*, IRenderable*, bool> 
 //{
 //	bool operator()(
 //		const MeSorter::RenderableList* pLeft, 
 //		const MeSorter::RenderableList* pRight
 //		) const;	
 //};

class MeBitSorterImpl: 
binary_function
<
const MeSorter::RenderableStr, 
const MeSorter::RenderableStr, 
bool
>
{
public:
	bool operator( ) ( first_argument_type a, 
		second_argument_type b )
	{
		return ( a.m_ui64Key < b.m_ui64Key );			
	}
};