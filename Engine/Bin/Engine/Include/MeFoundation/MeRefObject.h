#pragma once
#include <MeRTLibs.h>

/**
@desc:��ΪSmartPointer�ṩ֧��
*/
class MEFOUNDATION_ENTRY MeRefObject : public MeRefAlloc<MeRefObject>
{
public:
	inline MeRefObject();
	virtual ~MeRefObject();

	inline void IncRefCount();
	inline void DecRefCount();
	inline uint32 GetRefCount();

protected:
	virtual void DeleteSelf();

private:
	uint32 m_uiRefCount;

};

#include "MeFoundation/MeRefObject.inl"