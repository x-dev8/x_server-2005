#include "GivePresentLogic.h"
#include "GameMain.h"
#include "PlayerRole.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "core/Name.h"
#include "XmlStringLanguage.h"
#include "Color_config.h"
#include "ChatInfoBox.h"
#include "ScreenInfoManager.h"
#include "Common.h"
#include "Ui/InfoList.h"

extern CHeroGame theHeroGame;

CGivePresentLogic::CGivePresentLogic( void )
{
	m_bPlayGivePresentEffect = false;
	m_dwGivePresentEffectStartTime = 0;
	m_fGivePresentFlashRate = 0.17;
	m_iGivePresentDuration = 3500;
	m_fGivePresentFlashScale = 1.f;
	m_iFlashNo = 0;
	m_fLastFlashAlpha = -1.f;
	m_fLastFlashFadeOut = false;
	m_bGivePresentFade = false;
}

void CGivePresentLogic::SetPlayGivePresentEffect( bool bPlay )
{
	m_bPlayGivePresentEffect = bPlay;
	if( bPlay )
	{
		m_dwGivePresentEffectStartTime = HQ_TimeGetTime();
		ResetGivePresentFlash();
	}
}

bool CGivePresentLogic::CanGivePresent( const char* szName )
{
	if( !szName || szName[0] == '\0' )
		return false;

	if( !theHeroGame.GetPlayerMgr() )
		return false;

	// 判断距离
	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByName(szName);
	if( !pPlayer || pPlayer->GetDistanceToRole() > GIVE_PRESENT_MAX_DIST )
	{
		char szText[256] = {0};
		sprintf_s(szText, sizeof(szText)-1, theXmlString.GetString(eText_GivePresentFailed_TooFar));
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Present_SendFailed, szText );
		return false;
	}

	// 判断是否好友关系
	if( !thePlayerRole.IsFriend(szName) )
	{
		char szText[256] = {0};
		sprintf_s(szText, sizeof(szText)-1, theXmlString.GetString(eText_GivePresentFailed_ShouldBeFriend));
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Present_SendFailed, szText );
		return false;
	}

	return true;
}

void CGivePresentLogic::ResetGivePresentFlash()
{
	m_iFlashNo = 0;
	m_fLastFlashAlpha = -1.f;
	m_fLastFlashFadeOut = false;
	m_dwGivePresentFlashElapseTime = 0;
}

// 渲染赠送礼物全屏特效
void CGivePresentLogic::RenderPlayerGivePresentEffect()
{
	const int nFlashNum = 10;
	static int picId[nFlashNum] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	char filename[512] = {0};

	DWORD dwElapseTime = HQ_TimeGetTime() - GetGivePresentEffectStartTime();

	float fAlpha = 1.f;
	if( m_bGivePresentFade )	// 淡入淡出方式
	{
		fAlpha = fabs(sin(dwElapseTime * m_fGivePresentFlashRate));
	}
	DWORD dwColor = D3DCOLOR_ARGB((int)(fAlpha * 255), 255, 255, 255);

	int width = 64;
	int height = 64;

	if( m_bGivePresentFade )	// 淡入淡出方式
	{
		if( m_fLastFlashAlpha > 0 && fAlpha > m_fLastFlashAlpha && m_fLastFlashFadeOut )
		{
			++m_iFlashNo;
			if( m_iFlashNo >= nFlashNum )
				m_iFlashNo = 0;
		}
		if( fAlpha > m_fLastFlashAlpha )
			m_fLastFlashFadeOut = false;
		else
			m_fLastFlashFadeOut = true;
		m_fLastFlashAlpha = fAlpha;
	}
	else						// 持续显示
	{
		m_dwGivePresentFlashElapseTime += theHeroGame.GetFrameElapsedTime() * 1000;
		if( m_dwGivePresentFlashElapseTime >= m_fGivePresentFlashRate * 1000 )
		{
			++m_iFlashNo;
			if( m_iFlashNo >= nFlashNum )
				m_iFlashNo = 0;
			m_dwGivePresentFlashElapseTime = 0;
		}
	}
	MeSprintf_s( filename, sizeof(filename)/sizeof(char) - 1, "%s\\Data\\Ui\\Common\\GivePresent\\GivePresent%d.dds", GetRootPath(), m_iFlashNo );

	RECT rcSrc;
	rcSrc.left = 0;
	rcSrc.right = 63;
	rcSrc.top = 0;
	rcSrc.bottom = 63;

	// 渲染位置
	int iStartX = 0;
	int iStartY = 0;
	RECT rcDst;

	width *= m_fGivePresentFlashScale;
	height *= m_fGivePresentFlashScale;
	int iHorizenNum = SCREEN_WIDTH / width;
	int iHorizenOffset = (SCREEN_WIDTH - width * iHorizenNum)/(iHorizenNum-1);
	int iVerticalNum = SCREEN_HEIGHT / height;
	int iVerticalOffset = (SCREEN_HEIGHT - height * iVerticalNum)/(iVerticalNum-1);

	// Top
	iStartY = 0;
	iStartX = 0;
	for(int i=0; i<iHorizenNum; ++i, iStartX += width + iHorizenOffset)
	{
		rcDst.left = iStartX;
		rcDst.right = iStartX + width -1;
		rcDst.top = iStartY;
		rcDst.bottom = iStartY + height -1;

		theControlPictureManager.BitBlt( &picId[m_iFlashNo],
			filename,
			&rcDst, &rcSrc, dwColor );
	}

	// Bottom
	if( iVerticalNum > 1 )
	{
		iStartY = SCREEN_HEIGHT - height;
		iStartX = 0;
		for(int i=0; i<iHorizenNum; ++i, iStartX += width + iHorizenOffset)
		{
			rcDst.left = iStartX;
			rcDst.right = iStartX + width -1;
			rcDst.top = iStartY;
			rcDst.bottom = iStartY + height -1;

			theControlPictureManager.BitBlt( &picId[m_iFlashNo],
				filename,
				&rcDst, &rcSrc, dwColor );
		}
	}

	if( iVerticalNum > 2 )
	{
		// Left
		iStartX = 0;
		iStartY = height + iVerticalOffset;
		for(int i=0; i<iVerticalNum-2; ++i, iStartY += height + iVerticalOffset)
		{
			rcDst.left = iStartX;
			rcDst.right = iStartX + width -1;
			rcDst.top = iStartY;
			rcDst.bottom = iStartY + height -1;

			theControlPictureManager.BitBlt( &picId[m_iFlashNo],
				filename,
				&rcDst, &rcSrc, dwColor );
		}

		// Right
		iStartX = SCREEN_WIDTH - width;
		iStartY = height + iVerticalOffset;
		for(int i=0; i<iVerticalNum-2; ++i, iStartY += height + iVerticalOffset)
		{
			rcDst.left = iStartX;
			rcDst.right = iStartX + width -1;
			rcDst.top = iStartY;
			rcDst.bottom = iStartY + height -1;

			theControlPictureManager.BitBlt( &picId[m_iFlashNo],
				filename,
				&rcDst, &rcSrc, dwColor );
		}
	}

	if (dwElapseTime > m_iGivePresentDuration)
	{
		SetPlayGivePresentEffect(false);
	}
}
