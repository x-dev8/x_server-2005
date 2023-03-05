/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\StoryTip.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "Font3DManager.h"
#include "wsCamera.h"

#ifndef ID_FRAME_StoryTip
#define ID_FRAME_StoryTip		"ID_FRAME_StoryTip"
#endif  ID_FRAME_StoryTip
#ifndef ID_PICTURE_Bg
#define ID_PICTURE_Bg		"ID_PICTURE_Bg"
#endif  ID_PICTURE_Bg
#ifndef ID_PICTURE_Word
#define ID_PICTURE_Word		"ID_PICTURE_Word"
#endif  ID_PICTURE_Word
// #ifndef ID_TEXT_23250
// #define ID_TEXT_23250		"ID_TEXT_23250"
// #endif  ID_TEXT_23250

class CUI_ID_FRAME_StoryTip :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_StoryTip();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
private:
	ControlFrame*	m_pID_FRAME_StoryTip;
	ControlPicture*	m_pID_PICTURE_Bg;
	ControlPicture*	m_pID_PICTURE_Word;
// 	ControlText*	m_pID_TEXT_23250;
public:
	struct AnimSystem
	{
		std::string strBgPicPath;   //背景图片路径
		std::string strInfo;        //信息文字
		RECT        ShowRect;       //显示宽度
		RECT        OverRect;       //最终大小
		DWORD       dwBeginTime;    //开始时间
		int         dwElapseTime;   //持续时间
		bool        bPlaying;       //播放动画
		int         nFontIndex;     //字号
		DWORD       dwFontColor;    //字体颜色
		DWORD		dwGlobalAlpha;	//全局alpha

		AnimSystem()
		{
			strBgPicPath.clear();
			strInfo.clear();
			ShowRect.left = 0;
			ShowRect.top  = 0;
			ShowRect.right = 0;
			ShowRect.bottom = 0;
			dwBeginTime = 0;
			dwElapseTime = 1000;
			bPlaying = false;
			nFontIndex = 0;
			dwFontColor = 0xffffffff;
			dwGlobalAlpha = 255;
		}

		void Render()
		{
			if(!IsPlaying())
				return;

			//绘制背景
			int nPic = -1;
			DWORD dwPicColor = D3DCOLOR_ARGB( dwGlobalAlpha, 0xff, 0xff, 0xff );
			theControlPictureManager.BitBlt(&nPic,strBgPicPath.c_str(),&ShowRect, 0, dwPicColor );

			//绘制文字
			{
				GetEngine()->GetRenderer()->EndScene();

				LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetDevice();

				IRenderer* r = GetEngine()->GetRenderer();

				D3DVIEWPORT9 ViewPort;
				ViewPort.X = ShowRect.left - 2;
				ViewPort.Y = ShowRect.top - 2;
				ViewPort.Width = ShowRect.right - ShowRect.left;
				ViewPort.Height = ShowRect.right - ShowRect.left;
				ViewPort.MinZ = 0.0f;
				ViewPort.MaxZ = 1.0f;

				r->SetViewport(&ViewPort);
				r->BeginScene();
				r->Clear( 0L, D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 255, 255, 255), 1.0f, 0L );

				FontRender::EFontRenders eOldIdx = FontRender::EFR_FIRST;
				if( FontSystem::IsUseNewFont() )
				{
					eOldIdx = FontRender::getFontRender()->GetDefaultRendererIdx();
					FontRender::getFontRender()->SetDefaultRendererIdx( FontRender::EFR_THIRD );
					FontSystem::ClearRender( FontRender::EFR_THIRD );
				}
				RECT fontRect;
				fontRect.left = OverRect.left + 5;
				fontRect.top  = OverRect.top  + 5;
				fontRect.right = OverRect.right;
				fontRect.bottom = OverRect.bottom;
				DWORD dwFtColor = D3DCOLOR_ARGB( dwGlobalAlpha, (dwFontColor>>16) & 0xff, (dwFontColor>>8)&0xff, (dwFontColor)&0xff );

				FontSystem::DrawTextDirect(strInfo.c_str(),&fontRect, DT_LEFT,dwFtColor,nFontIndex, true );

				if( FontSystem::IsUseNewFont() )
				{
					FontRender::getFontRender()->SetDefaultRendererIdx( eOldIdx );
					FontSystem::DoRender( FontRender::EFR_THIRD );
				}				

				r->EndScene();

				getwsCamera()->ResetViewport();

				GetEngine()->GetRenderer()->BeginScene();
			}
		}

		void Update()
		{
			if(!IsPlaying())
				return;

		    DWORD dwPressTime = HQ_TimeGetTime() - dwBeginTime;
			const DWORD dwStopTime = 2000;//播放完后停顿2秒
			if(dwPressTime <= ( dwElapseTime + dwStopTime ) )
			{
				float t = (float)min( dwPressTime, dwElapseTime )/(float)dwElapseTime;
// #ifdef _DEBUG
// 				char szWord[256] = {0};
// 				sprintf_s(szWord,sizeof(szWord),"%d\n",t * (OverRect.right - OverRect.left));
// 				::OutputDebugString(szWord);
// #endif
				ShowRect.right = t * (float)(OverRect.right - OverRect.left) + ShowRect.left;
				if(ShowRect.right >= OverRect.right)
					ShowRect.right = OverRect.right;
			}
			else
			{
				if( dwGlobalAlpha > 0 && dwGlobalAlpha <= 255 )
				{
					dwGlobalAlpha -= 20;
					if( dwGlobalAlpha > 255 )
						dwGlobalAlpha = 0;
				}
				else
					EndAnim();
			}
		}

		void  BeginAnim(){bPlaying = true;}
		void  EndAnim(){bPlaying = false;}
		bool  IsPlaying(){return bPlaying;}
		bool  InitAnim(const char* pszPath,const char* pszInfo,RECT rc,int nElapseTime,int nFont = 0,int FontColor = 0xffffffff)
		{
			if(!pszPath || !pszInfo)
				return false;

			strBgPicPath = pszPath;
			strInfo      = pszInfo;

			dwBeginTime = HQ_TimeGetTime();
			dwElapseTime = nElapseTime;
			OverRect = rc;
			ShowRect = rc;
			ShowRect.right = 0;
			dwGlobalAlpha = 255;

			nFontIndex = nFont;
			dwFontColor = FontColor;
			return true;
		}
	};

	void ShowAnim(int nTitleId,int nStringId);

private:
	AnimSystem m_pAnim;
};
extern CUI_ID_FRAME_StoryTip s_CUI_ID_FRAME_StoryTip;
