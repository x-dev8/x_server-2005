#include "MeUi/Animation/AniFunctor.h"


    void CAnimationFunctorBase::InitializeParam(MeXmlElement* pElement)
    {

        const char* pTmp = pElement->Attribute("StartTime");
        if (pTmp)
        {
            SetStartTime(atoi(pTmp));
        }

        pTmp = pElement->Attribute("TotalTime");
        if (pTmp)
        {
            SetTotalTime(atoi(pTmp));
        }
    }

void CConstFunctor::InitializeParam(MeXmlElement* pElement)
{
    CAnimationFunctorBase::InitializeParam(pElement);
    mfA = atof(pElement->Attribute("A"));
}
void CLinearFunctor::InitializeParam(MeXmlElement* pElement)
{
    CConstFunctor::InitializeParam(pElement);
    mfB = atof(pElement->Attribute("B"));
}

float CLinearFunctor::Calculate(int32 nDeltaTime)
{
        return mfA + mfB * (nDeltaTime%m_nTotalTime);
}

void CQuadraticFunctor::InitializeParam(MeXmlElement* pElement)
{
   CLinearFunctor::InitializeParam(pElement);
   mfC = atof(pElement->Attribute("C"));
}

void        CQuadraticFunctor::InitializeByEnd(float fStart,float fSpeed,float fAcc, float fEnd)
{
    mfA = fStart;
    mfB = fSpeed;
    mfC = fAcc;

    int32 nTime = 0;
    float nDeltaX = (fEnd - fStart);
    if (nDeltaX != 0)
    {
        if (abs(fAcc) < 0.00001)
        {
            CLinearFunctor::InitializeBySpeed(fStart,fSpeed,fEnd);
        }
        else
        {
            int32 nTime = (-mfB + sqrt(mfB*mfB + 4 * fAcc * nDeltaX))/(2*fAcc);
            SetTotalTime(nTime );

        }
    }
    else
        SetTotalTime(0);

}

float CQuadraticFunctor::Calculate(int32 nDeltaTime)
{
     return mfA + nDeltaTime * mfB + nDeltaTime * nDeltaTime * mfC;
}

void CSinFunctor::InitializeParam(MeXmlElement* pElement)
{
    CQuadraticFunctor::InitializeParam(pElement);
    mfD = atof(pElement->Attribute("D"));
}

void        CSinFunctor::Initialize(float fA,float fB,float fC, float fD, int32 nTime)
{
    mfA = fA;
    mfB = fB;
    mfC = fC;
    mfD = fD;
    SetTotalTime(nTime );
}


float CSinFunctor::Calculate(int32 nDeltaTime)
{
     return mfA*sin(mfB* (nDeltaTime%m_nTotalTime) + mfC) + mfD;
}


float CIntervalFunctor::Calculate(int32 nDeltaTime)
{
	if (m_nTotalTime != 0 && mfC != 0)
	{
		LONG nIntervalIndex = floor((nDeltaTime%m_nTotalTime) /mfC);
		return mfA + nIntervalIndex * mfB;
	}
	return mfA;
}

float CRandomIntervalFunctor::Calculate(int32 nDeltaTime)
{
    LONG nIntervalIndex = rand()%((int32)mfC);
    return mfA + nIntervalIndex * mfB;
}

void CSegmentFunctor::InitializeParam(MeXmlElement* pElement)
{
    CAnimationFunctorBase::InitializeParam(pElement);
    SetTotalTime(0);
    MeXmlElement* pChild =  pElement->FirstChildElement("Segment");
    while (pChild!= NULL)
    {
        CAnimationFunctorBase* pFunctor = CFunctorMaker::GetInstance()->CreateFunctor(pChild);
        m_arrAniFunctor.push_back(pFunctor);
        SetTotalTime(GetTotalTime()+pFunctor->GetTotalTime());
        pChild = pChild->NextSiblingElement("Segment");
    }
}

float CSegmentFunctor::Calculate(int32 nDeltaTime)
{
    int32 i = m_arrAniFunctor.size() -1;
    for (; i >=0; --i)
    {
        if (m_arrAniFunctor[i]->GetStartTime() <= nDeltaTime)
        {
            return m_arrAniFunctor[i]->Calculate(nDeltaTime - m_arrAniFunctor[i]->GetStartTime()); 
        }
    }
    _ASSERT(0);
    return 0;
}

void CSegmentFunctor::AddAnimationFunctor(CAnimationFunctorBase* pAniFun)
{
	SetTotalTime(GetTotalTime()+pAniFun->GetTotalTime());
	m_arrAniFunctor.push_back(pAniFun);

	std::vector<CAnimationFunctorBase*>::iterator b = m_arrAniFunctor.begin();
	std::vector<CAnimationFunctorBase*>::iterator e = m_arrAniFunctor.end();
	std::vector<CAnimationFunctorBase*>::iterator it = b;
	
	int32 nStart = 0;
	for(;it != e; ++it)
	{
		(*it)->SetStartTime(nStart);
		nStart += (*it)->GetTotalTime();
	}
}

void CSegmentFunctor::ClearFunctor()
{
	m_arrAniFunctor.clear();
	SetStartTime(0);
	SetTotalTime(0);
}

CAnimationFunctorBase* CFunctorMaker::CreateFunctor(MeXmlElement* pElement)
{
    CAnimationFunctorBase* pRet = CreateFunctor(pElement->Attribute("Functor"));
	if (pRet)
	{
		pRet->InitializeParam(pElement);
	}
    return pRet;
}

CAnimationFunctorBase* CFunctorMaker::CreateFunctor(const char* pElementType )
{
	CAnimationFunctorBase* pRet = NULL;
	if (0 == strcmp(pElementType,"Const"))
	{
		pRet = new CConstFunctor;
	}
	else if (0 == strcmp(pElementType,"Linear"))
	{
		pRet = new CLinearFunctor;
	}
	else if (0 == strcmp(pElementType,"Quadratic"))
	{
		pRet = new CQuadraticFunctor;
	}
	else if (0 == strcmp(pElementType,"Sin"))
	{
		pRet = new CSinFunctor;
	}
	else if (0 == strcmp(pElementType,"Interval"))
	{
		pRet = new CIntervalFunctor;
	}
	else if (0 == strcmp(pElementType,"RandomInterval"))
	{
		pRet = new CRandomIntervalFunctor;
	}
	else if (0 == strcmp(pElementType,"Segment"))
	{
		pRet = new CSegmentFunctor;
	}
	m_arrFunctor.push_back(pRet);
	return pRet;

}
CFunctorMaker::~CFunctorMaker()
{
	for(std::list<CAnimationFunctorBase*>::iterator iter = m_arrFunctor.begin(); iter != m_arrFunctor.end(); ++iter)
	{
		delete (*iter);
	}
}
CFunctorMaker *CFunctorMaker::GetInstance()
{
    static CFunctorMaker Instance;
    return&Instance;
}

void CFunctorMaker::DestoryFunctor( CAnimationFunctorBase* pFunctor )
{
	for(std::list<CAnimationFunctorBase*>::iterator iter = m_arrFunctor.begin(); iter != m_arrFunctor.end(); ++iter)
	{
		if (*iter == pFunctor)
		{
			delete pFunctor;
			m_arrFunctor.erase(iter);
			break;
		}
	}
}
