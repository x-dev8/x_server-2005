#ifndef __EDIT_ACCUMULATOR_H__
#define __EDIT_ACCUMULATOR_H__
#include <NiAccumulator.h>
#include <NiMaterial.h>
#include "Render/SwAccumulator.h"
////////////////////////////////////////////////////////////////////////////////
class CEditAccumulator : public SwAccumulator
{
	NiDeclareRTTI;
	NiDeclareAbstractClone( CEditAccumulator );
	NiDeclareAbstractStream;

public:
							CEditAccumulator();
	virtual					~CEditAccumulator();

	void					SetWireframe( bool isWireframe );
	void					SetVertFrame( bool isVertframe );	
	bool					Wireframe() const { return m_isWireframe; }

	// *** begin Emergent internal use only ***
	virtual void			FinishAccumulating();
	
	void					RegisterSelObjectArray(NiVisibleArray& kArray);

	void					SetDefaultLight();
protected:
	bool					CreatePropertyList();
	bool					CreateLight();

protected:
	NiSortedObjectList		m_alphaItemsSel;

	NiDynamicEffectStatePtr	m_dynamicEffectSelected;

	NiDirectionalLightPtr	m_dirLightSelected;
};

typedef NiPointer<CEditAccumulator> CNdlWorldSorterPtr;



#endif //__EDIT_ACCUMULATOR_H__