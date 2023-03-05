#pragma once


#include "RapidXml/MeRapidXml.h"
#include "SmartAnimation.h"

class CXmlAnimation : public CSmartAnimation

    {
public:
	CXmlAnimation(UiRender* pRenderCurrFrame);
	~CXmlAnimation(void);
    CXmlAnimation(CXmlAnimation& pSrc, UiRender* pRenderCurrFrame );
    CXmlAnimation(MeXmlElement* pElement, UiRender* pRenderCurrFrame );

    bool Initialize(MeXmlElement* pElement);

    virtual void        InitializeFunctor(EFunctorType eType, float fBaseValue, CAnimationFunctorBase* pFunctor)
    {
        mFunctor[eType].mBaseValue = fBaseValue;
//        mFunctor[eType].m_pFunctor = pFunctor;
    }
};


