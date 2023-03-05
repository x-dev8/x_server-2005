#include "MeUi/MeUi.h"
#include "MeUi/Animation/SlideAnimation.h"
#include "MeUi/UiRender.h"
#include "MeUi/ControlFrame.h"
CSlideAnimation::CSlideAnimation(void) :
m_nStartTick(0)
,m_bRepeat(false)
,m_bStop(true)
,m_nTotalTime(0)
,m_nAlpha(255)
,m_nQuadId(-1)
{
}

CSlideAnimation::~CSlideAnimation(void)
{
}


bool  CSlideAnimation::StartAnimation(DWORD nTimeTick)
{
    m_nStartTick = nTimeTick;
    m_bStop = false;
	m_nQuadId = -1;
    Update(nTimeTick);
    return true;
}

bool  CSlideAnimation::StartAnimation(DWORD nTimeTick,bool bRepeat)
{
    StartAnimation(nTimeTick);
    m_bRepeat = bRepeat;
    return true;
}

bool CSlideAnimation::Update(DWORD nTimeTick,RECT* pDesRect)
{
    if (m_bStop)
    {
        return false;
    }
    int nElapsedTicks = nTimeTick - m_nStartTick;
    if (!m_bRepeat && nElapsedTicks >= m_nTotalTime)
    {
        StopAnimation();
        return false;
    }
	RECT* pThisDesRect = pDesRect;
	if (pThisDesRect == NULL)
	{
		pThisDesRect = &m_DesRect;
	}
	int32 nDeltaTime = nElapsedTicks%m_nTotalTime;
	int32 nCurrFrame = nDeltaTime/((float)m_nTotalTime/m_nTotalPicNumber);
	if (nCurrFrame>= m_nTotalPicNumber)
		nCurrFrame = m_nTotalPicNumber - 1;
	char strFileName[1024];
	sprintf_s(strFileName,"%s%d",m_baseName.c_str(),nCurrFrame);
	D3DCOLOR dwColor = D3DCOLOR_ARGB(m_nAlpha,0xff,0xff,0xff);
	int nPicId = -1;
	if (m_nQuadId != -1)
	{
		ControlPictureManager::S_Pic* pPic = theControlPictureManager.RegisterTexture(&nPicId,strFileName);
		if (pPic)
		{
			D3DSURFACE_DESC texDesc;
			if(!pPic->m_pd3dTexture || pPic->m_pd3dTexture->GetLevelDesc( 0, &texDesc ) != D3D_OK )
				return -1;
			RECT srcRect = {0,0,texDesc.Width,texDesc.Height};
			if (g_uiRenderCurrFrame)
			{
				g_uiRenderCurrFrame->adjustQuad(m_nQuadId,*pThisDesRect,pPic->m_pd3dTexture,srcRect,dwColor);
			}
		}
	}
	else
	{
		m_nQuadId = theControlPictureManager.BitBlt(&nPicId,strFileName,pThisDesRect,NULL,dwColor);
	}

    return true;
}

bool CSlideAnimation::Initialize( char* pBaseName,int nTotalFrame,RECT& DesRect,int nTotalTime )
{
	SetBaseName(pBaseName);
	m_nTotalPicNumber = nTotalFrame;
	m_DesRect = DesRect;
	m_nTotalTime = nTotalTime;
	return true;
}

void CSlideAnimation::UnRelativePicResource()
{
	if (!m_bStop)
	{
		assert(0);
		return;
	}
	for(int i = 0; i < m_nTotalPicNumber; ++i)
	{
		char strFileName[1024];
		sprintf_s(strFileName,"%s%d",m_baseName.c_str(),i);
		theControlPictureManager.UnregisterTexture(strFileName);
	}
}

