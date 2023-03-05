#include "MeUi/ControlListImage.h"
#include "MeUi/UiPicture.h"
#include "MeUi/ControlIconDragManager.h"
#include "FuncPerformanceLog.h"
#include "Me3d/Global.h"
#include "MeFont/MeFont.h"
#include "MeUi/UiRender.h"
#include "MeUi/Animation/SmartAnimation.h"
#include "MeUi/UiManager.h"
#include "Me3d/Engine/Engine.h"
#include "MeFont/MeFontSystem.h"  //##

ControlListImage::ControlListImage(void)
:m_nCurLvl(-1),
m_nMaxLvl(-1),
_bOrder(false),
m_bOnlyShowItemIcon(false),
m_bFadeInorFadeOut4NullItem(false),
m_bInFade4NullItem(false),
m_nFadeCurColorA4NullItem(0xff),
m_dwFadeLastTime4NullItem(0)
{
}

ControlListImage::~ControlListImage(void)
{
}

void ControlListImage::SetLvlInfo( INT nCurLvl, INT nMaxLvl )
{
	m_nCurLvl	=	nCurLvl;
	m_nMaxLvl	=	nMaxLvl;
}

void ControlListImage::Render()
{
	if ( IsNeedRender() )
	{
		RECT rcReal;
		GetRealRect( &rcReal );
        if( m_UIScroll.GetEnable() && m_UIScroll.IsVisable() && m_UIScroll.IsEnable() )
        {
            GetFrameFather()->GetFrameRender()->PushWorkingArea(rcReal);
        }
		S_ListImgData *pListImgData = (S_ListImgData*)m_pstData;
		RECT rcFrame;
		DWORD dwCurTime = HQ_TimeGetTime();
		//
// 		RECT rcView;
// 		rcView.left = 0;
// 		rcView.top = m_nShowStartHeight;
// 		rcView.right = m_nWidthShowMaxCount;
// 		rcView.bottom = rcView.top + m_nHeightShowMaxCount;
		//
		int nIconWidth,nIconHeight;
		nIconWidth = GetItemWidth();
		nIconHeight = GetItemHeight();


		S_ListImg *pListImg = NULL;
		int nX, nY;
		//
		int nStartIndex;
		int nEndIndex;

		if( nIconHeight == 0 )
			nIconHeight = 1;
		nStartIndex = (m_nShowStartHeight/ nIconHeight)*m_nWidthShowMaxCount;//rcView.top*m_nWidthShowMaxCount;
		nEndIndex = (nStartIndex + m_nHeightShowMaxCount + 1)*m_nWidthShowMaxCount;

		S_ListImg* pListImgMouse = 0;
		POINT ptMouseItem;
		if (GetTilePt(theIconDragManager.m_ptMouse.x, theIconDragManager.m_ptMouse.y, &ptMouseItem))
			pListImgMouse = GetItem(ptMouseItem.x, ptMouseItem.y);

		// 这里先把原来的闪光动画清除掉，防止滚动时绘制的位置不正确 lrt
		for ( int i = 0; i < m_vtItem.size(); i++ )
		{
			S_ListImg* pImg = &m_vtItem[i];

			if ( pImg )
			{
				if( pImg->m_bSpark )
				{
					// 停止播放
					CSmartAnimation* pAni = pImg->GetSparkAni();
					if( pAni )
					{
						GetFrameFather()->GetUiAniManageNotNULL()->StopAnimation( pAni );
					}
				}

				CSmartAnimation* coolDownAni = pImg->GetCoolDownAni();
				if (coolDownAni)
				{
					GetFrameFather()->GetUiAniManageNotNULL()->StopAnimation(coolDownAni);
				}
				
			}
		}

		for ( int n=nStartIndex; n<nEndIndex; n++ )
		{
			//pListImg = GetItemByIndex( n );
			if (n < m_vtItem.size())
				pListImg = &m_vtItem[n];
			else
				break;

			//if( !pListImg )
			//	continue;
			//if ( pListImg->IsNull() )
			//	continue;

			//if( _bOrder )	//图标从右向左排列
			//{
			//	nX = m_nWidthShowMaxCount - n%m_nWidthShowMaxCount - 1;
			//}
			//else
			{
				nX = n%m_nWidthShowMaxCount;
			}
			nY = n/m_nWidthShowMaxCount;

			rcFrame.left = rcReal.left/* +  pListImgData->m_nOffsetWidth * ControlObjectGetSCALE(this)/2*/ + nX*nIconWidth + 0.5f;
			rcFrame.top = rcReal.top/* + pListImgData->m_nOffsetHeight * ControlObjectGetSCALE(this)/2*/ + (nY*nIconHeight-m_nShowStartHeight) + 0.5f;
			rcFrame.right = rcFrame.left + pListImgData->m_nIconSize * ControlObjectGetSCALE(this) + 0.5f;
			rcFrame.bottom = rcFrame.top + pListImgData->m_nIconSize * ControlObjectGetSCALE(this) + 0.5f;
 			if ( rcFrame.top >= rcReal.bottom || rcFrame.bottom <= rcReal.top )
			{
				continue;
			}
					
			char fullpath[MAX_PATH];

			if (pListImg && pListImg->m_pkIconInfo )
			{
				if (!pListImg->IsNull())
				{
					pListImg->m_pkIconInfo->MaxCount() = m_nMaxLvl;
					//
					pListImg->m_pkIconInfo->DisplayIcon( &rcFrame, 0xffffffff,
						m_nFontIndex, GetFontSize(),
						D3DCOLOR_ARGB(0xff, 0xff,0xff,0xff),
						pListImg->m_eEnable,GetFrameFather() );

					if (!pListImg->m_pkIconInfo->m_strHotKey.empty())
					{
						RECT rcCount;
						rcCount = rcFrame;
						if( FontSystem::IsUseNewFont() )
						{
							rcCount.right -= 2 * ControlObjectGetSCALE( this );
							rcCount.top += 2 * ControlObjectGetSCALE( this ) - 3;
							rcCount.bottom += 2 * ControlObjectGetSCALE( this ) - 3;
						}
						else
						{
							rcCount.right = rcCount.right - 3 * ControlObjectGetSCALE(this);
							rcCount.bottom = rcCount.top + (rcCount.bottom - rcCount.top) * 0.5f - 5 * ControlObjectGetSCALE(this);
							rcCount.top -= 5 * ControlObjectGetSCALE(this);
						}						
						//##
						FontSystem::DrawTextRGB( pListImg->m_pkIconInfo->m_strHotKey.c_str(), &rcCount, DT_RIGHT | DT_NOCLIP,
							D3DCOLOR_ARGB( 0xff, 0xf0, 0xf0, 0xf0 ), m_nFontIndex );
					}

                    // 闪光动画: 如背包新装备       added by zhuomeng.hu		[11/11/2010]
                    if( pListImg->m_bSpark )
                    {
                        // 绘制区域
						CSmartAnimation* pSparkAni = pListImg->GetSparkAniNotNULL( GetFrameFather()->GetUiAniManageNotNULL() );
                        pSparkAni->InitializeFunctor( CSmartAnimation::EFunctorType_X,
                            rcFrame.left + pListImgData->m_nIconSize * ControlObjectGetSCALE( this ) / 2, NULL );
                        pSparkAni->InitializeFunctor( CSmartAnimation::EFunctorType_Y,
                            rcFrame.top + pListImgData->m_nIconSize * ControlObjectGetSCALE( this ) / 2, NULL );
                        pSparkAni->InitializeFunctor( CSmartAnimation::EFunctorType_Width,
                            rcFrame.right - rcFrame.left, NULL );
                        pSparkAni->InitializeFunctor( CSmartAnimation::EFunctorType_Height,
                            rcFrame.bottom - rcFrame.top, NULL );

                        if( !pSparkAni->IsInAnimation() )
                        {
                            if( pListImg->m_dwSparkBeginTime > 0 && dwCurTime >= pListImg->m_dwSparkBeginTime )
                            {
                                GetFrameFather()->GetUiAniManageNotNULL()->AddAnimation( pSparkAni );
                                pSparkAni->StartAnimation( dwCurTime, dwCurTime - pListImg->m_dwSparkBeginTime );
                            }
                            else
                            {
                                pListImg->m_dwSparkBeginTime = dwCurTime;
                                GetFrameFather()->GetUiAniManageNotNULL()->AddAnimation( pSparkAni );
                                pSparkAni->StartAnimation( dwCurTime, 0 );
                            }
                        }
						else
						{
							pSparkAni->Redraw( dwCurTime );
						}
                    }
                    else
                    {
                        // 停止播放
                        CSmartAnimation* pAni = pListImg->GetSparkAni();
						if( pAni )
						{
							GetFrameFather()->GetUiAniManageNotNULL()->StopAnimation( pAni );
						}
                        pListImg->m_dwSparkBeginTime = 0;
                    }

                    // 技能冷却特效
					if (pListImg->m_dwPeriod != 0 )
					{
						int nDegree = 0;
						nDegree = (dwCurTime - pListImg->m_dwStartTime)*360/pListImg->m_dwPeriod;
						if ( nDegree < 360 )
						{
							if (g_uiRenderCurrFrame->isQueueingEnabled())
							{
								CSmartAnimation* coolDownAni = pListImg->GetCoolDownAniNotNULL(GetFrameFather()->GetUiAniManageNotNULL());
								coolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_X, rcFrame.left + pListImgData->m_nIconSize * ControlObjectGetSCALE( this ) / 2, NULL );
								coolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Y, rcFrame.top + pListImgData->m_nIconSize * ControlObjectGetSCALE( this ) / 2, NULL );
								coolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Width, rcFrame.right - rcFrame.left , NULL );
								coolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Height, rcFrame.bottom - rcFrame.top , NULL );
								if (!coolDownAni->IsInAnimation())
								{
									static int nPicId= -1;
                                   CreateAnimation(nPicId, pListImg, rcFrame, "\\data\\UI\\Icon\\SkillCollDown.tga", dwCurTime, false,
									   0,48, pListImg->m_dwPeriod / 36,  pListImg->m_dwPeriod,0,48,48,dwCurTime - pListImg->m_dwStartTime );
								}
								else
								{
									coolDownAni->Redraw(dwCurTime);
								}
							}
							else
							{
								UiDrawer::DrawProgressRect( rcFrame.left+pListImgData->m_nIconSize * ControlObjectGetSCALE(this)/2,
									rcFrame.top+pListImgData->m_nIconSize * ControlObjectGetSCALE(this)/2,
									pListImgData->m_nIconSize * ControlObjectGetSCALE(this), nDegree );
							}
							// 画cd时间在中间
							// added, jiayi, [2009/11/5]
							char szBuffer[256];
							float fSecond = (float)( pListImg->m_dwPeriod - dwCurTime + pListImg->m_dwStartTime ) / 1000.f;									
							int nMinute = fSecond / 60;
							int nHour = nMinute / 60;
							int nDay = nHour / 24;
							COLORREF colTime = 0xffffffff;							
							if (nDay > 0)							
								sprintf( szBuffer, "%dd", nDay );
							else if (nHour > 0)
								sprintf( szBuffer, "%dh", nHour );
							else if ( nMinute != 0 )
								sprintf( szBuffer, "%dm", nMinute );
							else
							{
								sprintf( szBuffer, "%d", (int)fSecond + 1 );
								if( (int)fSecond + 1 <= 3 )
								{
									if( fSecond - (int)fSecond > 0.5f )
										colTime = 0xffff0000;
								}
							}
							float fOldScale = FontSystem::GetFontScale();
							FontSystem::SetFontScale( fOldScale * 1.3f );
							FontSystem::DrawTextRGB( szBuffer, &rcFrame, DT_CENTER | DT_VCENTER | DT_NOCLIP,
								colTime, m_nFontIndex );					
							FontSystem::SetFontScale( fOldScale );

							pListImg->m_bCooldownStart = true;

							if( GetFrameFather() )
								GetFrameFather()->SetRedraw();
						}
						else
						{
							if (g_uiRenderCurrFrame->isQueueingEnabled())
							{
								CSmartAnimation* coolDownAni = pListImg->GetCoolDownAni();
								if (coolDownAni)
								{
									GetFrameFather()->GetUiAniManageNotNULL()->StopAnimation(coolDownAni);
								}
							}
							pListImg->m_dwPeriod = 0;
							if (pListImg->m_bCooldownStart)
							{
								pListImg->m_bCooldownStart = false;
								pListImg->m_dwCooldownFinishStartTime = HQ_TimeGetTime();
							}
						}
					}
				}
				else if (!m_bOnlyShowItemIcon || m_bInFade4NullItem)
				{
					if (pListImg->m_eEnable == eIcon_Lock)
					{
						sprintf( fullpath, "%s\\Data\\Ui\\Icon\\IconLock.dds", GetRootPath() );

						static int picId = -1;
						theControlPictureManager.BitBlt( &picId,
							fullpath,
							&rcFrame, NULL, 0xffffffff );

						continue;
					}
					else if (!m_strBackPicName.empty() && m_pstPic)
					{
#if 1
						if (m_nPicId == -1)
						{
							theControlPictureManager.RegisterTexture(&m_nPicId,m_strBackPicName.c_str());
						}
						int w = rcFrame.right - rcFrame.left;
						int h = rcFrame.bottom - rcFrame.top;

						int nLeftW = (m_pstPic->m_rcClient.left - m_pstPic->m_rcFrame.left) * ControlObjectGetSCALE(this);
						int nLeftH = (m_pstPic->m_rcClient.bottom - m_pstPic->m_rcClient.top) * ControlObjectGetSCALE(this);
						int nTopW = (m_pstPic->m_rcClient.right - m_pstPic->m_rcClient.left) * ControlObjectGetSCALE(this);
						int nTopH = (m_pstPic->m_rcClient.top - m_pstPic->m_rcFrame.top) * ControlObjectGetSCALE(this);
						int nRightW = (m_pstPic->m_rcFrame.right - m_pstPic->m_rcClient.right) * ControlObjectGetSCALE(this);
						int nRightH = (m_pstPic->m_rcClient.bottom - m_pstPic->m_rcClient.top) * ControlObjectGetSCALE(this);
						int nBottomW = (m_pstPic->m_rcClient.right - m_pstPic->m_rcClient.left) * ControlObjectGetSCALE(this);
						int nBottomH = (m_pstPic->m_rcFrame.bottom - m_pstPic->m_rcClient.bottom) * ControlObjectGetSCALE(this);
						int nLeftTopW = (m_pstPic->m_rcClient.left - m_pstPic->m_rcFrame.left) * ControlObjectGetSCALE(this);
						int nLeftTopH = (m_pstPic->m_rcClient.top - m_pstPic->m_rcFrame.top) * ControlObjectGetSCALE(this);
						int nRightTopW = (m_pstPic->m_rcFrame.right - m_pstPic->m_rcClient.right) * ControlObjectGetSCALE(this);
						int nRightTopH = (m_pstPic->m_rcClient.top - m_pstPic->m_rcFrame.top) * ControlObjectGetSCALE(this);
						int nLeftBottomW = (m_pstPic->m_rcClient.left - m_pstPic->m_rcFrame.left) * ControlObjectGetSCALE(this);
						int nLeftBottomH = (m_pstPic->m_rcFrame.bottom - m_pstPic->m_rcClient.bottom) * ControlObjectGetSCALE(this);
						int nRightBottomW = (m_pstPic->m_rcFrame.right - m_pstPic->m_rcClient.right) * ControlObjectGetSCALE(this);
						int nRightBottomH = (m_pstPic->m_rcFrame.bottom - m_pstPic->m_rcClient.bottom) * ControlObjectGetSCALE(this);
						int nMiddleW = (m_pstPic->m_rcClient.right - m_pstPic->m_rcClient.left) * ControlObjectGetSCALE(this);
						int nMiddleH = (m_pstPic->m_rcClient.bottom - m_pstPic->m_rcClient.top) * ControlObjectGetSCALE(this);

						// LeftTop
						D3DCOLOR dwColor = D3DCOLOR_ARGB(m_nFadeCurColorA,0xff,0xff,0xff);
						if(m_bInFade4NullItem)
						{
							dwColor = D3DCOLOR_ARGB(m_nFadeCurColorA4NullItem, 0xff, 0xff, 0xff);
						}

						BitBlt( &m_nPicId, NULL,
							rcFrame.left, rcFrame.top,
							nLeftTopW, nLeftTopH,
							m_pstPic->m_rcFrame.left, m_pstPic->m_rcFrame.top,
							m_nLeftTopW, m_nLeftTopH,
							DrawModeNormal,
							dwColor );
						// RightTop
						BitBlt( &m_nPicId, NULL,
							rcFrame.right-nRightTopW,rcFrame.top,
							nRightTopW, nRightTopH,
							m_pstPic->m_rcClient.right, m_pstPic->m_rcFrame.top,
							m_nRightTopW, m_nRightTopH,
							DrawModeNormal,
							dwColor );
						// LeftBottom
						BitBlt( &m_nPicId, NULL,
							rcFrame.left, rcFrame.bottom-nLeftBottomH,
							nLeftBottomW, nLeftBottomH,
							m_pstPic->m_rcFrame.left, m_pstPic->m_rcClient.bottom,
							m_nLeftBottomW, m_nLeftBottomH,
							DrawModeNormal,
							dwColor );
						// RightBottom
						BitBlt( &m_nPicId, NULL,
							rcFrame.right-nRightBottomW, rcFrame.bottom-nRightBottomH,
							nRightBottomW, nRightBottomH,
							m_pstPic->m_rcClient.right, m_pstPic->m_rcClient.bottom,
							m_nRightBottomW, m_nRightBottomH,
							DrawModeNormal,
							dwColor );
						// Left
						BitBlt( &m_nPicId, NULL,
							rcFrame.left, rcFrame.top+nLeftTopH,
							nLeftW, h-nLeftTopH-nLeftBottomH,
							m_pstPic->m_rcFrame.left, m_pstPic->m_rcClient.top,
							m_nLeftW, m_nLeftH,
							m_pstData->m_nDrawMode[S_BaseData::Mode_Left],
							dwColor );
						// Top
						BitBlt( &m_nPicId, NULL,
							rcFrame.left+nLeftTopW, rcFrame.top,
							w-nLeftTopW-nRightTopW,nTopH,
							m_pstPic->m_rcClient.left, m_pstPic->m_rcFrame.top,
							m_nTopW,m_nTopH,
							m_pstData->m_nDrawMode[S_BaseData::Mode_Top],
							dwColor );
						// Right
						BitBlt( &m_nPicId, NULL,
							rcFrame.right-nRightW, rcFrame.top+nRightTopH,
							nRightW, h-nRightTopH-nRightBottomH,
							m_pstPic->m_rcClient.right, m_pstPic->m_rcClient.top,
							m_nRightW, m_nRightH,
							m_pstData->m_nDrawMode[S_BaseData::Mode_Right],
							dwColor );
						// Bottom
						BitBlt( &m_nPicId, NULL,
							rcFrame.left+nLeftBottomW, rcFrame.bottom-nLeftBottomH,
							w-nLeftBottomW-nRightBottomW, nBottomH,
							m_pstPic->m_rcClient.left, m_pstPic->m_rcClient.bottom,
							m_nBottomW,m_nBottomH,
							m_pstData->m_nDrawMode[S_BaseData::Mode_Bottom],
							dwColor );
						// Middle
						BitBlt( &m_nPicId, NULL,
							rcFrame.left+nLeftTopW, rcFrame.top+nLeftTopH,
							w-nLeftW-nRightW, h-nTopH-nBottomH,
							m_pstPic->m_rcClient.left, m_pstPic->m_rcClient.top,
							m_nMiddleW, m_nMiddleH,
							m_pstData->m_nDrawMode[S_BaseData::Mode_Middle],
							dwColor );
#else
						D3DCOLOR dwColor = D3DCOLOR_ARGB(m_nFadeCurColorA,0xff,0xff,0xff);
						theControlPictureManager.BitBlt( &m_nPicId,
							NULL,
							&rcFrame, NULL, dwColor );
#endif

						if (!pListImg->m_pkIconInfo->m_strHotKey.empty())
						{
							RECT rcCount;
							rcCount = rcFrame;
							if( FontSystem::IsUseNewFont() )
							{
								rcCount.right -= 2 * ControlObjectGetSCALE( this );
								rcCount.top += 2 * ControlObjectGetSCALE( this ) - 3;
								rcCount.bottom += 2 * ControlObjectGetSCALE( this ) - 3;
							}
							else
							{
								rcCount.right = rcCount.right - 3 * ControlObjectGetSCALE(this);
								rcCount.bottom = rcCount.top + (rcCount.bottom - rcCount.top) * 0.5f - 5 * ControlObjectGetSCALE(this);
								rcCount.top -= 5 * ControlObjectGetSCALE(this);
							}	
							float fOldScale = FontSystem::GetFontScale();
							//##
							FontSystem::DrawTextRGB( pListImg->m_pkIconInfo->m_strHotKey.c_str(), &rcCount, DT_RIGHT | DT_NOCLIP,
								D3DCOLOR_ARGB(0xff, 0xff,0xff,0xff), m_nFontIndex );
						}
					}
				}

				if (m_bShowPressEffect && (!m_bOnlyShowItemIcon || !pListImg->IsNull()) && CanbePick() && pListImg->m_eEnable != eIcon_Lock)
				{
					if (m_nPressItemIndex == n || m_nSelectItemIndex == n)
					{
						sprintf( fullpath, "%s\\Data\\Ui\\Icon\\IconPressed.dds", GetRootPath() );

						static int picId = -1;
						theControlPictureManager.BitBlt( &picId,
							fullpath,
							&rcFrame, NULL, 0xffffffff );
					}
					else if (pListImgMouse == pListImg)
					{
						if (m_bShowCursorOnFrameOnNULLItem || !pListImg->IsNull())
						{
							sprintf( fullpath, "%s\\Data\\Ui\\Icon\\IconSelectFrame.dds", GetRootPath() );

							static int picId = -1;
							theControlPictureManager.BitBlt( &picId,
								fullpath,
								&rcFrame, NULL, 0xffffffff );

						}
					}
				}

				static const DWORD FLASH_TIME = 33 * 7;
				DWORD dwElapsedTime = 0;
				if (!pListImg->IsNull() &&
					(dwElapsedTime = HQ_TimeGetTime() - pListImg->m_dwCooldownFinishStartTime) < FLASH_TIME )
				{
					if (g_uiRenderCurrFrame->isQueueingEnabled())
					{
						CSmartAnimation* coolDownAni = pListImg->GetCoolDownAniNotNULL(GetFrameFather()->GetUiAniManageNotNULL());
						coolDownAni->InitializeFunctor(CSmartAnimation::EFunctorType_X,rcFrame.left+pListImgData->m_nIconSize * ControlObjectGetSCALE(this)/2,NULL);
						coolDownAni->InitializeFunctor(CSmartAnimation::EFunctorType_Y,rcFrame.top+pListImgData->m_nIconSize * ControlObjectGetSCALE(this)/2,NULL);
						coolDownAni->InitializeFunctor(CSmartAnimation::EFunctorType_Width,rcFrame.right - rcFrame.left,NULL);
						coolDownAni->InitializeFunctor(CSmartAnimation::EFunctorType_Height,rcFrame.bottom - rcFrame.top,NULL);
						if (!coolDownAni->IsInAnimation())
						{
							GetFrameFather()->GetUiAniManageNotNULL()->AddAnimation(coolDownAni);
							CIntervalFunctor* pSrcXFunctor = (CIntervalFunctor*)coolDownAni->GetFunctorType(CSmartAnimation::EFunctorType_SrcX);
							assert(pSrcXFunctor);
							pSrcXFunctor->SetParamA(0);
							pSrcXFunctor->SetParamB(48);
							pSrcXFunctor->SetParamC(FLASH_TIME/7);
							pSrcXFunctor->SetTotalTime(FLASH_TIME);

							coolDownAni->InitializeFunctor(CSmartAnimation::EFunctorType_SrcY,0,NULL);
							coolDownAni->InitializeFunctor(CSmartAnimation::EFunctorType_SrcWidth,48,NULL);
							coolDownAni->InitializeFunctor(CSmartAnimation::EFunctorType_SrcHeight,48,NULL);

							static int nPicId= -1;
							std::string m_strPicName = GetRootPath();
							m_strPicName += "\\data\\UI\\";
							m_strPicName += "Icon\\IconCooldownFinish.tga";
							ControlPictureManager::S_Pic* pPic = theControlPictureManager.RegisterTexture(&nPicId,m_strPicName.c_str());
							coolDownAni->SetUiPicture(pPic->m_pd3dTexture);

							coolDownAni->StartAnimation(dwCurTime,dwElapsedTime,false);
						}
						else
						{
							coolDownAni->Redraw(dwCurTime);
						}

					}
					else
					{
						int xi = dwElapsedTime / 33 % 3;
						int yi = dwElapsedTime / 33 / 3;

						sprintf( fullpath, "%s\\Data\\Ui\\Icon\\IconCooldownFinish.tga", GetRootPath() );
						static int picId = -1;
						RECT rcSrc = {0,0,40,40};
						rcSrc.left = 40 * xi;
						rcSrc.right = rcSrc.left + 40;
						rcSrc.top = 40 * yi;
						rcSrc.bottom = rcSrc.top + 40;

						theControlPictureManager.BitBlt( &picId,
							fullpath,
							&rcFrame, &rcSrc, D3DCOLOR_ARGB(255,255,255,255) );
					}
				}
			}
		}


		if ( true == ((S_ListImgData*)m_pstData)->m_bShowSelFrame )
		{
			// 选择框
			POINT ptSel = m_ptCurSel;
// 			ptSel.y -= m_nShowStartHeight;
			S_ListImg *pListImg = NULL;
			if ( ptSel.y*nIconHeight >= m_nShowStartHeight && ptSel.y < m_nMaxHeightCount )
			{
				pListImg = GetItem( ptSel.x, ptSel.y );
				RECT rcSel;
				rcSel.left = rcReal.left + pListImgData->m_nOffsetWidth * ControlObjectGetSCALE(this)/2 + ptSel.x*nIconWidth;
				rcSel.top = rcReal.top + pListImgData->m_nOffsetHeight * ControlObjectGetSCALE(this)/2 + ptSel.y*nIconHeight - m_nShowStartHeight;
				rcSel.right = rcSel.left + pListImgData->m_nIconSize * ControlObjectGetSCALE(this);
				rcSel.bottom = rcSel.top + pListImgData->m_nIconSize * ControlObjectGetSCALE(this);
				UiDrawer::DrawRect2D( rcSel, m_colSel );
				rcSel.left--;
				rcSel.right++;
				rcSel.top--;
				rcSel.bottom++;
				UiDrawer::DrawRect2D( rcSel, m_colSel );
			}
			// 选择框
			ptSel = m_ptMouseOnSel;
// 			ptSel.y -= m_nShowStartHeight;
			if ( ptSel.y >= m_nShowStartHeight && ptSel.y < m_nMaxHeightCount )
			{
				pListImg = theIconDragManager.GetCurItem();
				if ( !pListImg )
				{
					pListImg = GetItem( ptSel.x, ptSel.y );
				}
				RECT rcSel;
				//rcSel.left = rcReal.left + pListImgData->m_nOffsetWidth/2 + ptSel.x*nIconWidth;
				//rcSel.top = rcReal.top + pListImgData->m_nOffsetHeight/2 + ptSel.y*nIconHeight;
				rcSel.left = rcReal.left + pListImgData->m_nOffsetWidth * ControlObjectGetSCALE(this)/2 + ptSel.x*nIconWidth;
				rcSel.top = rcReal.top + pListImgData->m_nOffsetHeight * ControlObjectGetSCALE(this)/2 + ptSel.y*nIconHeight - m_nShowStartHeight;
				rcSel.right = rcSel.left + pListImgData->m_nIconSize * ControlObjectGetSCALE(this);
				rcSel.bottom = rcSel.top + pListImgData->m_nIconSize * ControlObjectGetSCALE(this);
				UiDrawer::DrawRect2D( rcSel, m_colMouseOn );
			}
		}
		
		//if( m_nMaxLvl != -1 )
		//{
		//	//DrawText()
		////	FontSystem::DrawTextARGB( &rc, &m_szText[nStart],
		////		dwColoer, m_nFontIndex, m_dwDrawFlags, -1 );
		//	CHAR szTemp[40] = {0};
		//	
		//	sprintf( szTemp, "%d/%d", GetItemByIndex(0)->m_stIcon.Count(), m_nMaxLvl );
		//	RECT rc = rcFrame;

		//	INT nIconHeight = abs( rc.top - rc.bottom );
		//	rc.top = rc.top+nIconHeight-12; 
		//	//rc.left = rc.left + 4;
		//	FontSystem::DrawTextARGB( &rc, szTemp, 0xFFFFFFFF, 0, DT_RIGHT, -1 );
		//}
        if( m_UIScroll.GetEnable() && m_UIScroll.IsVisable() && m_UIScroll.IsEnable() )
        {
            GetFrameFather()->GetFrameRender()->PopWorkingArea();
        }

		if ( m_nMaxHeightCount > m_nHeightShowMaxCount )
		{
			m_UIScroll.Render();
		}
	}
}

void ControlListImage::InitUIData( IN ControlObject* pFather, IN S_BaseData* pData )
{
	ControlObject::InitUIData( pFather, pData );

	S_ListImgData *pListImgData = (S_ListImgData*)pData;
	if( m_nWidth == 0 )
		m_nWidth = 1;
	if( m_nHeight == 0 )
		m_nHeight = 1;
	int nItemWidth = GetItemWidth() != 0 ? GetItemWidth() : m_nWidth;
	int nItemHeight = GetItemHeight() != 0 ? GetItemHeight() : m_nHeight;
	m_nWidthShowMaxCount = m_nWidth/nItemWidth /*+ 0.5f*/;
	m_nHeightShowMaxCount = m_nHeight/nItemHeight /*+ 0.5f*/;
	m_nMaxHeightCount = pListImgData->m_nMaxHeightCount;

	//assert( m_nWidthShowMaxCount < LISTIMG_ITEM_WIDTH_MAX );
	//assert( m_nHeightShowMaxCount < LISTIMG_ITEM_HEIGHT_MAX );
	//assert( m_nMaxHeightCount < LISTIMG_ITEM_HEIGHT_MAX );
	InitItemDate();

	COLORREF Color = pListImgData->m_colSelFrame;
	m_colSel = D3DCOLOR_ARGB(255,GetRValue(Color),GetGValue(Color),GetBValue(Color));
	m_colMouseOn = D3DCOLOR_ARGB(128,GetRValue(Color),GetGValue(Color),GetBValue(Color));

	m_UIScroll.InitUIData( this, &pListImgData->m_stScrollBar );
	m_UIScroll.SetMaxValue((m_nMaxHeightCount - m_nHeightShowMaxCount)*GetItemHeight());
	m_UIScroll.SetStepValue(GetItemHeight());

#ifdef _DEBUG
	m_UIScroll.m_debug_bHasWarning = false;
#endif

	if (strlen(pData->m_szCaption) > 0)
		TipInfo.SetInfo(pData->m_szCaption);
}

//bool ControlListImage::RemoveItem( const int nIndex, const int nCount )
//{
//	assert( nIndex >= 0 && nIndex < m_nWidthShowMaxCount*m_nMaxHeightCount );
//	int nX = nIndex%m_nWidthShowMaxCount;
//	int nY = nIndex/m_nWidthShowMaxCount;
//	return ControlIconDrag::RemoveItem( nX, nY, nCount );
//}

bool ControlListImage::GetTilePt( const int nX, const int nY, OUT POINT *ptTile )
{
	assert( ptTile );

	RECT rc;
	GetRealRect( &rc );

	if (nX >= rc.left && nX <= rc.right &&
				nY >= rc.top && nY <= rc.bottom)
	{

		S_ListImgData *pListImgData = (S_ListImgData*)m_pstData;

		int w = nX - rc.left;
		int h = nY - rc.top;

		int nIconWidth,nIconHeight;
		nIconWidth = GetItemWidth();
		nIconHeight = GetItemHeight();

		// 所在格子的索引
		int xi = w / nIconWidth;
		int yi = (h+m_nShowStartHeight) / nIconHeight;
		if (xi >= m_nWidthShowMaxCount || yi >= m_nMaxHeightCount)
			return false;

		// 所在格子的x, y
		int x = rc.left + xi * nIconWidth + 0.5f;
		int y = rc.top + yi * nIconHeight + 0.5f - m_nShowStartHeight;

		// 不在范围内
		if (nX < x || nY < y ||
			nX > x + pListImgData->m_nIconSize * ControlObjectGetSCALE(this) ||
			nY > y + pListImgData->m_nIconSize * ControlObjectGetSCALE(this))
			return false;

		ptTile->x = xi;
		ptTile->y = yi;

		return true;
	}
	return false;
}
void ControlListImage::SetScrollValue(int nValue)
{
	int nMax = m_UIScroll.GetMaxValue();
	nValue = nValue < 0 ? 0 : nValue > nMax ? nMax : nValue;

	if( m_UIScroll.IsVisable() )
	{
		m_UIScroll.SetValue(nValue);
		Refeash();
	}
}

void ControlListImage::ResetDevice()
{
	ControlIconDrag::ResetDevice();
	m_UIScroll.ResetDevice();

	m_UIScroll.SetMaxValue((m_nMaxHeightCount - m_nHeightShowMaxCount)*GetItemHeight());
	m_UIScroll.SetStepValue(GetItemHeight());
}

void ControlListImage::Run()
{
	ControlIconDrag::Run();

	if(IsVisable())
	{		
		// 淡入淡出
		if(m_bInFade4NullItem)
		{
			if (!GetOnlyShowItemIcon())	//the null item is being visible
			{
				m_nFadeCurColorA4NullItem = m_FadeSpeed * (HQ_TimeGetTime() - m_dwFadeLastTime4NullItem);
				if ( m_nFadeCurColorA4NullItem >= m_nMaxFade )
				{
					m_nFadeCurColorA4NullItem = m_nMaxFade;
					m_bInFade4NullItem = false;
				}
			}
			else
			{//the null item is being invisible
				m_nFadeCurColorA4NullItem = m_FadeSpeed * (HQ_TimeGetTime() - m_dwFadeLastTime4NullItem);
				if ( m_nFadeCurColorA4NullItem <= m_nMinFade )
				{
					m_nFadeCurColorA4NullItem = m_nMinFade;
					m_bInFade4NullItem = false;
				}
			}
		}
	}

}

// added by zhuomeng.hu		[11/11/2010]
void ControlListImage::CreateAnimation(int& nPicId, S_ListImg* pListImg, const RECT& iconRect, std::string strPicPath, DWORD dwCurTime, bool bRepeat, float fSrcXParamA, float fSrcXParamB,
                                       float fSrcXParamC, int32 iSrcXParamT, float fSrcY, float fSrcWidth, float fScrHeight ,DWORD dwElapsedTime)
{
    CSmartAnimation* coolDownAni = pListImg->GetCoolDownAniNotNULL(GetFrameFather()->GetUiAniManageNotNULL());
    GetFrameFather()->GetUiAniManageNotNULL()->AddAnimation( coolDownAni );
    CIntervalFunctor* pSrcXFunctor = ( CIntervalFunctor* )coolDownAni->GetFunctorType( CSmartAnimation::EFunctorType_SrcX );
    assert(pSrcXFunctor);
    pSrcXFunctor->SetParamA( fSrcXParamA );
    pSrcXFunctor->SetParamB( fSrcXParamB );
    pSrcXFunctor->SetParamC( fSrcXParamC );
    pSrcXFunctor->SetTotalTime( iSrcXParamT );

    coolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_SrcY, fSrcY, NULL );
    coolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_SrcWidth, fSrcWidth, NULL );
    coolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_SrcHeight, fScrHeight, NULL );

    std::string m_strPicName = GetRootPath();
    m_strPicName += strPicPath;
    ControlPictureManager::S_Pic* pPic = theControlPictureManager.RegisterTexture( &nPicId, m_strPicName.c_str() );
    coolDownAni->SetUiPicture( pPic->m_pd3dTexture );

    coolDownAni->StartAnimation( dwCurTime,dwElapsedTime, bRepeat );
}

int g_ControlListImageLongDelayTime = 1500;
int g_ControlListImageShortDelayTime = 500;

void ControlListImage::SetNullItemFadeInAndOut(bool enable_)
{
	m_bFadeInorFadeOut4NullItem = enable_;

	InitFadeParam4NullItem();
}

void ControlListImage::InitFadeParam4NullItem()
{
	if (m_bFadeInorFadeOut4NullItem)
	{
		m_bInFade4NullItem = true;
		m_nFadeCurColorA4NullItem = 0;
		m_dwFadeLastTime4NullItem = HQ_TimeGetTime();
	}
	else
	{
		m_nFadeCurColorA4NullItem = 0xff;
		m_bInFade4NullItem = false;
	}
}

void ControlListImage::SetOnlyShowItemIcon(bool b_)
{
	m_bOnlyShowItemIcon = b_; 

	if(m_bFadeInorFadeOut4NullItem)
	{
		m_bInFade4NullItem = true;
		m_dwFadeLastTime4NullItem = HQ_TimeGetTime();
	}
}