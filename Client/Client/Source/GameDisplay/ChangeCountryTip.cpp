#include "FuncPerformanceLog.h"
#include "tga.h"
#include "MeUi/UIPicture.h"
#include "gamemain.h"
#include "Player.h"
#include "playermgr.h"
#include "CfgFileLoader.h"
#include <math.h>
#include "Meaudio/MeAudio.h"
#include <vector>
#include "ChangeCountryTip.h"
#include "Common.h"
#include "CountryDefine.h"

extern HRSound GSound;
#define	ALPHA_START 0x00ffffff

CChangeCountryTips::CChangeCountryTips(void)
{
	m_shCurrTips = 0;
	m_shCurrRenderStep = 0;
	m_shTipsTexture = -1;
	m_bStopRender = true;
	m_mapTipsInfo.clear();
	m_vRenderTips.clear();
}

CChangeCountryTips::~CChangeCountryTips(void)
{
	m_mapTipsInfo.clear();
	m_vRenderTips.clear();
	UnRegisterTipsTexture();
}

void CChangeCountryTips::InitTips()
{
	RegisterTipsTexture();

	TipsInfo info;
	info.rtImgSrc.left = 96;		//658
	info.rtImgSrc.top = 57;			//12
	info.rtImgSrc.right = 558;		//985
	info.rtImgSrc.bottom = 150;		//127
	info.shWidth = (info.rtImgSrc.right - info.rtImgSrc.left) * 6; 
	info.shHeight = (info.rtImgSrc.bottom - info.rtImgSrc.top) * 6;
	info.shMinWidth = (info.rtImgSrc.right - info.rtImgSrc.left) ; 
	info.shMinHeight = (info.rtImgSrc.bottom - info.rtImgSrc.top) ;
	info.shRenderType = 0;
	info.shFrameNum = 25;
	info.shEndFlashFrame = 15;
	info.shOffsetX = SCREEN_WIDTH / 2;
	info.shOffsetY = SCREEN_HEIGHT / 4 + 50;
	//info.strSound = "Data\\Audio\\Ui\\Duel\\Fight.wav";
	info.bSpeed = false;
	m_mapTipsInfo.insert(std::pair<short, TipsInfo>(CountryDefine::Country_LouLan, info));
	info.rtImgSrc.left = 96;		//12
	info.rtImgSrc.top = 228;			//8
	info.rtImgSrc.right = 558;		//314
	info.rtImgSrc.bottom = 335;		//120
	info.shWidth = (info.rtImgSrc.right - info.rtImgSrc.left) * 4; 
	info.shHeight = (info.rtImgSrc.bottom - info.rtImgSrc.top) * 4;
	info.shMinWidth = (info.rtImgSrc.right - info.rtImgSrc.left) ; 
	info.shMinHeight = (info.rtImgSrc.bottom - info.rtImgSrc.top) ;
	info.shRenderType = 0;
	info.shFrameNum = 25;
	info.shEndFlashFrame = info.shFrameNum;
	info.shOffsetX = SCREEN_WIDTH / 2;
	info.shOffsetY = SCREEN_HEIGHT / 4 + 50;
	//info.strSound = "Data\\Audio\\Ui\\Duel\\One.wav";
	info.bSpeed = true;
	m_mapTipsInfo.insert(std::pair<short, TipsInfo>(CountryDefine::Country_KunLun, info));
	info.rtImgSrc.left = 96;			//12
	info.rtImgSrc.top = 407;			//137
	info.rtImgSrc.right = 558;			//314
	info.rtImgSrc.bottom = 498;			//249
	info.shWidth = (info.rtImgSrc.right - info.rtImgSrc.left) * 4; 
	info.shHeight = (info.rtImgSrc.bottom - info.rtImgSrc.top) * 4;
	info.shMinWidth = (info.rtImgSrc.right - info.rtImgSrc.left) ; 
	info.shMinHeight = (info.rtImgSrc.bottom - info.rtImgSrc.top) ;
	info.shRenderType = 0;
	info.shFrameNum = 25;
	info.shEndFlashFrame = info.shFrameNum;
	info.shOffsetX = SCREEN_WIDTH / 2;
	info.shOffsetY = SCREEN_HEIGHT / 4 + 50;
	//info.strSound = "Data\\Audio\\Ui\\Duel\\Two.wav";
	info.bSpeed = true;
	m_mapTipsInfo.insert(std::pair<short, TipsInfo>(CountryDefine::Country_DunHuang, info));
}

void CChangeCountryTips::RegisterTipsTexture()
{
	char filename[MAX_PATH] = {0};
	MeSprintf_s(filename,sizeof(filename)/sizeof(char) - 1 ,"%s\\Data\\TEXTURE\\country.dds", GetRootPath());
	m_shTipsTexture = GetEngine()->GetTextureManager()->RegisterTexture( filename, FALSE ,TRUE);
	if( m_shTipsTexture != -1 )
	{
		LPDIRECT3DTEXTURE9 pTexture = (LPDIRECT3DTEXTURE9)GetEngine()->GetTextureManager()->GetTexture(m_shTipsTexture)->GetData();
		if( pTexture )
		{
			D3DSURFACE_DESC desc;
			pTexture->GetLevelDesc( 0, &desc );
			m_srcWidth = desc.Width;
			m_srcHeight = desc.Height;
		}
	}
}

void CChangeCountryTips::UnRegisterTipsTexture()
{
	if(m_shTipsTexture != -1)
	{
		//GetEngine()->GetTextureManager()->UnRegisterTexture(m_shTipsTexture);
		m_shTipsTexture = -1;
	}
}

void CChangeCountryTips::AddTips(short shTipsNum)
{
	if(m_mapTipsInfo.find(shTipsNum) != m_mapTipsInfo.end())
	{
		RenderTips tips;
		tips.info = m_mapTipsInfo[shTipsNum];
		tips.shWidth = tips.info.shWidth;
		tips.shHeight = tips.info.shHeight; 
		tips.shMinWidth = tips.info.shMinWidth;
		tips.shMinHeight = tips.info.shMinHeight;
		tips.shCurrFrame = 0;
		tips.nStartTime = HQ_TimeGetTime();
		tips.nAlphaColor = 0xffffffff;
		tips.bFlash = false;
		tips.nFlashNum = 4;
		tips.dwLastFrmTime = 0;
		char temp[MAX_PATH] = {0};
		MeSprintf_s(temp,sizeof(temp)/sizeof(char) - 1,"%s\\%s",GetRootPath(),tips.info.strSound.c_str());
		GSound.PlaySound(temp,false,NULL);
		m_vRenderTips.push_back(tips);
		m_bStopRender = false;
	}
}

void CChangeCountryTips::Render()
{
	if(m_bStopRender)
	{
		return;
	}

	for(std::vector<RenderTips>::iterator itr=m_vRenderTips.begin();itr!=m_vRenderTips.end();itr++)
	{
		int nTime = HQ_TimeGetTime() - (*itr).nStartTime;
		int nFrame = nTime / 50;

		int nPosX = SCREEN_WIDTH / 2 - (*itr).shWidth / 2;
		int nPosY = (SCREEN_HEIGHT / 4 + 50) - (*itr).shHeight / 2;
		if((*itr).bFlash && (*itr).shCurrFrame <= (*itr).info.shEndFlashFrame)
		{
			if((*itr).nFlashNum > 0)
			{
				nPosX += ((rand()%3 - 1)*6);
				nPosY += ((rand()%3 - 1)*6);
				(*itr).nFlashNum --;
			}
		}		

		RECT rDraw = {nPosX, nPosY, nPosX+(*itr).shWidth, nPosY+(*itr).shHeight};
		GetDrawer()->Blt(m_shTipsTexture,&rDraw,&(*itr).info.rtImgSrc,m_srcWidth,m_srcHeight,0,(*itr).nAlphaColor,0);

		if(nFrame >= (*itr).shCurrFrame)
		{
			(*itr).shCurrFrame = nFrame;

			if ((*itr).dwLastFrmTime == 0)
			{
				float fValue = 0.8;
				if((*itr).info.bSpeed)
				{
					fValue = (float)((*itr).info.shFrameNum - (*itr).shCurrFrame) / (float)((*itr).info.shFrameNum);
				}
				(*itr).shWidth = (*itr).shWidth * fValue;
				if((*itr).shWidth < (*itr).shMinWidth)
				{
					(*itr).shWidth = (*itr).shMinWidth;
					(*itr).bFlash = true;
				}
				(*itr).shHeight = (*itr).shHeight * fValue;
				if((*itr).shHeight < (*itr).shMinHeight)
				{
					(*itr).shHeight = (*itr).shMinHeight;
				}
				(*itr).shCurrFrame++;
			}
			if((*itr).shCurrFrame >= (*itr).info.shFrameNum)
			{
				if ((*itr).dwLastFrmTime == 0)
					(*itr).dwLastFrmTime = HQ_TimeGetTime();
				if (HQ_TimeGetTime() - (*itr).dwLastFrmTime < 5000)
					break;

				itr = m_vRenderTips.erase(itr);
				if(m_vRenderTips.empty())
				{
					m_bStopRender = true;					
				}
				if (itr == m_vRenderTips.end())
					break;
			}
		}
	}
}
