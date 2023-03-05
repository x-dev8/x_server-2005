#include "MeUi/MeUi.h"
#include "MeUi/Animation/XmlAnimation.h"
#include "MeUi/UiRender.h"
#include "MeUi/ControlFrame.h"
#include "MeUi/UiPicture.h"
CSmartAnimation::CSmartAnimation( UiRender* pRenderCurrFrame ) :
m_pd3dTexture(NULL)
,m_nStartTick(0)
,m_bRepeat(false)
,m_bStop(true)
,m_nTotalTime(0)
,m_nAlpha(255)
,m_nQuadId(-1)
,m_nOffsetTime(0)
,m_bWorkingAreaEnable(false)
{
    m_pRender = pRenderCurrFrame;
    mFunctor[EFunctorType_Alpha].mBaseValue = 255;
    mFunctor[EFunctorType_Fade].mBaseValue = 255;
}

CSmartAnimation::~CSmartAnimation(void)
{
	for (int i = EFunctorType_X; i < EFunctorType_Total; i++)
	{
		if (mFunctor[i].m_pFunctor)
		{
			CFunctorMaker::GetInstance()->DestoryFunctor(mFunctor[i].m_pFunctor);
		}
	}
	if (m_pd3dTexture != NULL)
	{
		theControlPictureManager.UnregisterTexture(m_pd3dTexture);
	}
}


bool  CSmartAnimation::StartAnimation(DWORD nTimeTick,DWORD nDeltaTick)
{
    m_nTotalTime = 0;
    int32 i = EFunctorType_X;
    for (i = EFunctorType_X; i < EFunctorType_Total; i++)
    {
        if (mFunctor[i].m_pFunctor)
        {
            if (mFunctor[i].m_pFunctor->GetTotalTime() > m_nTotalTime)
            {
                m_nTotalTime = mFunctor[i].m_pFunctor->GetTotalTime() ;
            }
        }
    }

    m_nStartTick = nTimeTick;
	m_nOffsetTime = nDeltaTick;
    m_bStop = false;
    Redraw(nTimeTick);
    return true;
}

bool  CSmartAnimation::StartAnimation(DWORD nTimeTick,DWORD nDeltaTick,bool bRepeat)
{
    StartAnimation(nTimeTick,nDeltaTick);
    m_bRepeat = bRepeat;
    return true;
}

bool CSmartAnimation::Update(DWORD nTimeTick)
{
    if (m_bStop)
    {
        return false;
    }
    int nElapsedTicks = nTimeTick - m_nStartTick;
    if (!m_bRepeat && (nElapsedTicks + m_nOffsetTime) >= m_nTotalTime)
    {
        StopAnimation();
        return false;
    }

    DWORD nDeltaTime = (nElapsedTicks + m_nOffsetTime)%m_nTotalTime;

    MeRect DesRect;
    DesRect.Width = mFunctor[EFunctorType_Width].Calculate(nDeltaTime);
    DesRect.Height = mFunctor[EFunctorType_Height].Calculate(nDeltaTime);
    DesRect.X = mFunctor[EFunctorType_X].Calculate(nDeltaTime) - DesRect.Width/2;
    DesRect.Y = mFunctor[EFunctorType_Y].Calculate(nDeltaTime) - DesRect.Height/2;

    MeRect SrcRect;
    SrcRect.X = mFunctor[EFunctorType_SrcX].Calculate(nDeltaTime);
    SrcRect.Y = mFunctor[EFunctorType_SrcY].Calculate(nDeltaTime);
    SrcRect.Width = mFunctor[EFunctorType_SrcWidth].Calculate(nDeltaTime);
    SrcRect.Height = mFunctor[EFunctorType_SrcHeight].Calculate(nDeltaTime);

//     if( m_bWorkingAreaEnable )
//         Slice( DesRect, SrcRect );

    m_DesRect.left = DesRect.X;
    m_DesRect.top = DesRect.Y;
    m_DesRect.right = m_DesRect.left + DesRect.Width;
    m_DesRect.bottom = m_DesRect.top + DesRect.Height;
    m_SrcRect.left = SrcRect.X;
    m_SrcRect.top = SrcRect.Y;
    m_SrcRect.right = m_SrcRect.left + SrcRect.Width;
    m_SrcRect.bottom = m_SrcRect.top + SrcRect.Height;

	m_nAlpha = mFunctor[EFunctorType_Alpha].Calculate(nDeltaTime);
    int nFade = mFunctor[EFunctorType_Fade].Calculate(nDeltaTime);
	if (m_bWorkingAreaEnable)
	{
		m_pRender->PushWorkingArea(m_workingArea);
	}
	D3DCOLOR dwColor = D3DCOLOR_ARGB( m_nAlpha, nFade, nFade, nFade );
	m_pRender->adjustQuad(m_nQuadId,m_DesRect,m_pd3dTexture,m_SrcRect,dwColor);
	if (m_bWorkingAreaEnable)
	{
		m_pRender->PopWorkingArea();
	}

    return true;
}


// void CSmartAnimation::Slice(MeRect& BGRect,MeRect& SrcRect)
// {
//     if (BGRect.X + BGRect.Width <= m_workingArea.X
//         || BGRect.X >= m_workingArea.X + m_workingArea.Width
//         || BGRect.Y + BGRect.Height <= m_workingArea.Y
//         || BGRect.Y >= m_workingArea.Y + m_workingArea.Height)
//     {//out of working Area
//         BGRect.Width = 0;
//         BGRect.Height = 0;
//         return;
//     }
//     const int32 nEnlargeCoef = 100;
//     if (BGRect.X < m_workingArea.X)
//     {
//         int32 nCoefficient = SrcRect.Width*nEnlargeCoef/BGRect.Width;
//         SrcRect.X = SrcRect.X + (m_workingArea.X - BGRect.X)*nCoefficient/nEnlargeCoef;
//         BGRect.Width = BGRect.X + BGRect.Width - m_workingArea.X;
//         SrcRect.Width = BGRect.Width*nCoefficient/nEnlargeCoef;
//         BGRect.X = m_workingArea.X;
//     }
//     if (BGRect.X + BGRect.Width> m_workingArea.X + m_workingArea.Width)
//     {
//         int32 nCoefficient = SrcRect.Width*nEnlargeCoef/BGRect.Width;
//         BGRect.Width = (m_workingArea.X + m_workingArea.Width - BGRect.X);
//         SrcRect.Width = BGRect.Width*nCoefficient/nEnlargeCoef;
//     }
// 
//     if (BGRect.Y < m_workingArea.Y)
//     {
//         int32 nCoefficient = SrcRect.Height*nEnlargeCoef/BGRect.Height;
//         SrcRect.Y = SrcRect.Y + (m_workingArea.Y - BGRect.Y)*nCoefficient/nEnlargeCoef;
//         BGRect.Height = BGRect.Y + BGRect.Height - m_workingArea.Y;
//         SrcRect.Height = BGRect.Height*nCoefficient/nEnlargeCoef;
//         BGRect.Y = m_workingArea.Y;
//     }
//     if (BGRect.Y + BGRect.Height> m_workingArea.Y + m_workingArea.Height)
//     {
//         int32 nCoefficient = SrcRect.Height*nEnlargeCoef/BGRect.Height;
//         BGRect.Height = m_workingArea.Y + m_workingArea.Height - BGRect.Y;
//         SrcRect.Height = BGRect.Height*nCoefficient/nEnlargeCoef;
//     }
// 
//     _ASSERT(SrcRect.Width >0);
//     _ASSERT(SrcRect.Height >0);
// }

void CSmartAnimation::SetUiPicture( LPDIRECT3DTEXTURE9 pd3dTexture )
{
	if (m_pd3dTexture != NULL)
	{
		theControlPictureManager.UnregisterTexture(m_pd3dTexture);
	}
	m_pd3dTexture = pd3dTexture;
}

bool CSmartAnimation::Redraw( DWORD tickCount )
{
	m_nQuadId = m_pRender->RetriveQuad();
	return Update(tickCount);
}

bool CSmartAniManage::AddAnimation( CSmartAnimation* pAnimation)
{
	if(pAnimation != NULL)
	{
		m_listAnimations.push_back(pAnimation);
		return true;
	}
	return false;
}

bool CSmartAniManage::Update(DWORD tickCount)
{
    for(AnimationList::iterator it = m_listAnimations.begin();
        it != m_listAnimations.end();
        )
    {
        CSmartAnimation* pAnimation = *it;
        if(pAnimation != NULL)
        {
            int nResult = pAnimation->Update( tickCount );
            if(!pAnimation->IsInAnimation())
            {
                it = m_listAnimations.erase(it);
				m_pFrame->SetRedraw();
                continue;
            }
        }
        ++it;
    }
    return true;
}

void CSmartAniManage::StopAnimation(CSmartAnimation* pAnimation)
{
    if(pAnimation == NULL)
    {
        return;
    }

    AnimationList::iterator it=m_listAnimations.begin();
    for(; 
        it != m_listAnimations.end(); ++it)
    {
        if(*it == pAnimation)
        {
            break;
        }
    }

    if(it != m_listAnimations.end())
    {
        pAnimation->StopAnimation();
        m_listAnimations.erase(it);

    }
}

void CSmartAniManage::StopAllAnimation()
{
    AnimationList::iterator it=m_listAnimations.begin();
    for(; 
        it != m_listAnimations.end(); ++it)
    {
        (*it)->StopAnimation();
    }
    m_listAnimations.clear();

}

