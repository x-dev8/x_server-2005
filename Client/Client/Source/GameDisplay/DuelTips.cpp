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
#include "DuelTips.h"
#include "Common.h"

extern HRSound GSound;
#define	ALPHA_START 0x00ffffff

CDuelTips::CDuelTips(void)
{
    m_shCurrTips = 0;
    m_shCurrRenderStep = 0;
    m_shTipsTexture = -1;
    m_bStopRender = true;
    m_mapTipsInfo.clear();
    m_vRenderTips.clear();
}

CDuelTips::~CDuelTips(void)
{
    m_mapTipsInfo.clear();
    m_vRenderTips.clear();
    UnRegisterTipsTexture();
}

void CDuelTips::InitTips()
{
    RegisterTipsTexture();

    TipsInfo info;
	info.rtImgSrc.left = 585;		//658
	info.rtImgSrc.top = 45;			//12
	info.rtImgSrc.right = 775;		//985
	info.rtImgSrc.bottom = 190;		//127
	info.shWidth = (info.rtImgSrc.right - info.rtImgSrc.left) * 6; 
	info.shHeight = (info.rtImgSrc.bottom - info.rtImgSrc.top) * 6;
	info.shMinWidth = (info.rtImgSrc.right - info.rtImgSrc.left) ; 
	info.shMinHeight = (info.rtImgSrc.bottom - info.rtImgSrc.top) ;
	info.shRenderType = 0;
	info.shFrameNum = 25;
	info.shEndFlashFrame = 15;
	info.shOffsetX = SCREEN_WIDTH / 2;
	info.shOffsetY = SCREEN_HEIGHT / 4 + 50;
	info.strSound = "Data\\Audio\\Ui\\Duel\\Fight.wav";
	info.bSpeed = false;
	m_mapTipsInfo.insert(std::pair<short, TipsInfo>(Image_START_FIGHT, info));
	info.rtImgSrc.left = 135;		//12
	info.rtImgSrc.top = 75;			//8
	info.rtImgSrc.right = 400;		//314
	info.rtImgSrc.bottom = 320;		//120
    info.shWidth = (info.rtImgSrc.right - info.rtImgSrc.left) * 4; 
    info.shHeight = (info.rtImgSrc.bottom - info.rtImgSrc.top) * 4;
    info.shMinWidth = (info.rtImgSrc.right - info.rtImgSrc.left) ; 
    info.shMinHeight = (info.rtImgSrc.bottom - info.rtImgSrc.top) ;
    info.shRenderType = 0;
    info.shFrameNum = 15;
    info.shEndFlashFrame = info.shFrameNum;
    info.shOffsetX = SCREEN_WIDTH / 2;
    info.shOffsetY = SCREEN_HEIGHT / 4 + 50;
	info.strSound = "Data\\Audio\\Ui\\Duel\\One.wav";
    info.bSpeed = true;
    m_mapTipsInfo.insert(std::pair<short, TipsInfo>(Image_NUMBER_1, info));
	info.rtImgSrc.left = 135;			//12
	info.rtImgSrc.top = 355;			//137
	info.rtImgSrc.right = 400;			//314
	info.rtImgSrc.bottom = 605;			//249
    info.shWidth = (info.rtImgSrc.right - info.rtImgSrc.left) * 4; 
    info.shHeight = (info.rtImgSrc.bottom - info.rtImgSrc.top) * 4;
    info.shMinWidth = (info.rtImgSrc.right - info.rtImgSrc.left) ; 
    info.shMinHeight = (info.rtImgSrc.bottom - info.rtImgSrc.top) ;
    info.shRenderType = 0;
    info.shFrameNum = 15;
    info.shEndFlashFrame = info.shFrameNum;
    info.shOffsetX = SCREEN_WIDTH / 2;
    info.shOffsetY = SCREEN_HEIGHT / 4 + 50;
	info.strSound = "Data\\Audio\\Ui\\Duel\\Two.wav";
    info.bSpeed = true;
    m_mapTipsInfo.insert(std::pair<short, TipsInfo>(Image_NUMBER_2, info));
    info.rtImgSrc.left = 135;			//12
    info.rtImgSrc.top = 635;			//264
    info.rtImgSrc.right = 400;			//314
    info.rtImgSrc.bottom = 885;			//376
    info.shWidth = (info.rtImgSrc.right - info.rtImgSrc.left) * 4; 
    info.shHeight = (info.rtImgSrc.bottom - info.rtImgSrc.top) * 4;
    info.shMinWidth = (info.rtImgSrc.right - info.rtImgSrc.left) ; 
    info.shMinHeight = (info.rtImgSrc.bottom - info.rtImgSrc.top);
    info.shRenderType = 0;
    info.shFrameNum = 15;
    info.shEndFlashFrame = info.shFrameNum;
    info.shOffsetX = SCREEN_WIDTH / 2;
    info.shOffsetY = SCREEN_HEIGHT / 4 + 50;
	info.strSound = "Data\\Audio\\Ui\\Duel\\Three.wav";
    info.bSpeed = true;
    m_mapTipsInfo.insert(std::pair<short, TipsInfo>(Image_NUMBER_3, info));
	info.rtImgSrc.left = 545;			//328
	info.rtImgSrc.top = 420;				//8
	info.rtImgSrc.right = 835;			//638
	info.rtImgSrc.bottom = 685;			//241
    info.shWidth = (info.rtImgSrc.right - info.rtImgSrc.left) * 6; 
    info.shHeight = (info.rtImgSrc.bottom - info.rtImgSrc.top) * 6;
    info.shMinWidth = (info.rtImgSrc.right - info.rtImgSrc.left)  ; 
    info.shMinHeight = (info.rtImgSrc.bottom - info.rtImgSrc.top) ;
    info.shRenderType = 0;
    info.shFrameNum = 60;
    info.shEndFlashFrame = 20;
	info.shOffsetX = SCREEN_WIDTH / 2;
	info.shOffsetY = SCREEN_HEIGHT / 4 + 50;
	info.strSound = "Data\\Audio\\Ui\\Duel\\Win.wav";
    info.bSpeed = false;
    m_mapTipsInfo.insert(std::pair<short, TipsInfo>(Image_FIGHT_WIN, info));
	info.rtImgSrc.left = 555;			//338
	info.rtImgSrc.top = 730;			//248
	info.rtImgSrc.right = 845;			//625
	info.rtImgSrc.bottom = 1000;			//473
	info.shWidth = (info.rtImgSrc.right - info.rtImgSrc.left) * 6; 
	info.shHeight = (info.rtImgSrc.bottom - info.rtImgSrc.top) * 6;
	info.shMinWidth = (info.rtImgSrc.right - info.rtImgSrc.left) ; 
	info.shMinHeight = (info.rtImgSrc.bottom - info.rtImgSrc.top) ;
	info.shRenderType = 0;
	info.shFrameNum = 60;
	info.shEndFlashFrame = 20;
	info.shOffsetX = SCREEN_WIDTH / 2;
	info.shOffsetY = SCREEN_HEIGHT / 4 + 50;
	info.strSound = "Data\\Audio\\Ui\\Duel\\Lose.wav";
	info.bSpeed = false;
	m_mapTipsInfo.insert(std::pair<short, TipsInfo>(Image_FIGHT_LOSE, info));
}

void CDuelTips::RegisterTipsTexture()
{
	char filename[MAX_PATH] = {0};
	MeSprintf_s(filename,sizeof(filename)/sizeof(char) - 1 ,"%s\\Data\\TEXTURE\\duel.tga", GetRootPath());
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
void CDuelTips::UnRegisterTipsTexture()
{
    if(m_shTipsTexture != -1)
    {
        GetEngine()->GetTextureManager()->UnRegisterTexture(m_shTipsTexture);
        m_shTipsTexture = -1;
    }
}

void CDuelTips::AddTips(short shTipsNum)
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
        tips.nAlphaColor = ALPHA_START;
        tips.bFlash = false;
        tips.nFlashNum = 4;
		char temp[MAX_PATH] = {0};
		MeSprintf_s(temp,sizeof(temp)/sizeof(char) - 1,"%s\\%s",GetRootPath(),tips.info.strSound.c_str());
		GSound.PlaySound(temp,false,NULL);
        m_vRenderTips.push_back(tips);
        m_bStopRender = false;
    }
}

void CDuelTips::Render()
{
    if(m_bStopRender)
    {
        return;
    }

    std::vector<RenderTips>::iterator itr;
    for(itr=m_vRenderTips.begin();itr!=m_vRenderTips.end();itr++)
    {
        int nTime = HQ_TimeGetTime() - (*itr).nStartTime;
        int nFrame = nTime / 50;

        int nPosX = (*itr).info.shOffsetX - (*itr).shWidth / 2;
        int nPosY = (*itr).info.shOffsetY - (*itr).shHeight / 2;
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
            
            if((*itr).shCurrFrame < (*itr).info.shFrameNum - 5)
            {
                if((*itr).nAlphaColor < 0xefffffff)
                {
                    (*itr).nAlphaColor += 0x2fffffff;
                }
                else
                {
                    (*itr).nAlphaColor = 0xffffffff;
                }
            }
            else
            {
                if((*itr).nAlphaColor > ALPHA_START)
                {
                    (*itr).nAlphaColor -= 0x2f000000;
                }
            }
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

            if((*itr).shCurrFrame >= (*itr).info.shFrameNum)
            {
                m_vRenderTips.erase(itr);
                if(m_vRenderTips.empty())
                {
                    m_bStopRender = true;
                }
                return;
            }
        }
    }
}
