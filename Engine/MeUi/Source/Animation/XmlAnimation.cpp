#include "MeUi/MeUi.h"
#include "MeUi/Animation/XmlAnimation.h"
#include "MeUi/Animation/AniFunctor.h"


extern const char* GetRootPath();
    static char* g_AnimationProperty[CXmlAnimation::EFunctorType_Total] = {
        "x",
        "y",
        "width",
        "height",
        "SrcX",
        "SrcY",
        "SrcWidth",
        "SrcHeight",
        "Alpha",
        "Fade",
    };
CXmlAnimation::CXmlAnimation(UiRender* pRenderCurrFrame) : CSmartAnimation( pRenderCurrFrame )
{
}
CXmlAnimation::CXmlAnimation(CXmlAnimation& srcAni, UiRender* pRenderCurrFrame ) : CSmartAnimation( pRenderCurrFrame )
{
    int32 i = EFunctorType_X;
    for (i = EFunctorType_X; i < EFunctorType_Total; i++)
    {
        mFunctor[i].m_pFunctor = srcAni.mFunctor[i].m_pFunctor;
        mFunctor[i].mBaseValue = srcAni.mFunctor[i].mBaseValue;

    }
    m_bRepeat = srcAni.m_bRepeat;
    m_workingArea = srcAni.m_workingArea;
    m_pd3dTexture = srcAni.m_pd3dTexture;
	{
		m_nQuadId = srcAni.m_nQuadId;
	}
}

CXmlAnimation::CXmlAnimation(MeXmlElement* pElement, UiRender* pRenderCurrFrame ) : CSmartAnimation( pRenderCurrFrame )
{
    Initialize(pElement);
}

CXmlAnimation::~CXmlAnimation(void)
{
}



bool  CXmlAnimation::Initialize(MeXmlElement* pElement)
{
    const char* pAttr = NULL;
    MeXmlElement* pTmp = NULL;
    int32 i = EFunctorType_X;
    for (i = EFunctorType_X; i < EFunctorType_Total; i++)
    {
        pAttr = pElement->Attribute(g_AnimationProperty[i]);
        if (pAttr)
        {
            mFunctor[i].mBaseValue = atof(pAttr);
        }
        pTmp = pElement->FirstChildElement(g_AnimationProperty[i]);
        if (pTmp)
        {
            mFunctor[i].m_pFunctor = CFunctorMaker::GetInstance()->CreateFunctor(pTmp);
        }
    }

    pAttr = pElement->Attribute("Repeat");
    if (pAttr)
    {
        if (0 == stricmp(pAttr,"false"))
        {
            m_bRepeat = false;
        }
        else
        {
            m_bRepeat = true;
        }
    }
    pAttr = pElement->Attribute("SrcFile");
    if (pAttr)
    {
		std::string m_strPicName = GetRootPath();
		m_strPicName += "\\data\\UI\\";
		m_strPicName += pAttr;
		int nPicId = -1;
		ControlPictureManager::S_Pic* pPic = theControlPictureManager.RegisterTexture(&nPicId,m_strPicName.c_str());
		if (pPic)
		{
			SetUiPicture(pPic->m_pd3dTexture)  ;
		}
    }
    pTmp = pElement->FirstChildElement("ShowRect");
    if (pTmp)
    {
        m_workingArea.left = atoi(pTmp->Attribute("x"));
        m_workingArea.top = atoi(pTmp->Attribute("y"));
        m_workingArea.right = m_workingArea.left + atoi(pTmp->Attribute("width"));
        m_workingArea.bottom = m_workingArea.top + atoi(pTmp->Attribute("height"));

    }
    return true;
}


