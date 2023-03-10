#include "MeUi/MeUi.h"
#include "MeUi/IconManager.h"
#include "MeUi/UiPicture.h"
#include "MeUi/FontManager.h"
#include "MeUi/ControlObject.h"
#include "FuncPerformanceLog.h"
//#include "XmlStringLanguage.h"
#include "MeUi/UiManager.h"
#include "FilePath.h"
#include "Me3d/BaseGraphics.h"
#include "MeUi/ExpressionManager.h"
#include <assert.h>
//#include "core/core.h"
#include "Me3d/Engine/Engine.h"

#include "MeFont/MeFontSystem.h"  //##
#include "MeFont/NewFont/MeFontRender.h"
#include "Me3d/Global.h"

#include "TimeEx.h"
#define OFFSET_WIDTH	3
#define OFFSET_HEIGHT	4
#define	FRAME_SIZE		7
#define TILE_SIZE		32
#define TIP_ICON_SIZE	64


const int g_nMouseOffsetWidth = 15;
const int g_nMouseOffsetHeight = 15;

DWORD g_dwColorTip0 = 0xffffffff;
DWORD g_dwColorTip1 = 0xFF8F3200;


DWORD WHITE_COLOR = 0xFFFFFFFF;
DWORD GRAYED_COLOR = 0x7f7f7f7f;
DWORD BLUE_COLOR  = 0xFF0000FF;
DWORD GREEN_COLOR = 0xFF008000;
DWORD GOLD_COLOR = 0xFFA6A600;
DWORD TOP_GOLD_COLOR = 0xFFFF8000;
DWORD YELLOW_COLOR = 0xFF008000;
DWORD RED_COLOR   = 0xFFFF0000;
DWORD LIGHT_YELLOW_COLOR = 0xFFF1D488;

DWORD Orange_COLOR   = 0xFFFF7F00;
DWORD Purple_COLOR   = 0xFF800081;
//////////////////////////////////////////////////////////////////////////
S_IconInfoBase::funcGetItemLevel S_IconInfoBase::ms_pfGetItemLevel = 0;
S_IconInfoBase::funcGetItemName S_IconInfoBase::ms_pfGetItemName = 0;
S_IconInfoBase::funcGetReplacedName S_IconInfoBase::ms_pfGetReplacedName = 0;
S_IconInfoBase::funRetrieveTimeString S_IconInfoBase::ms_pFunRetrieveTimeString = 0;
CIconInfoMouseTip::funRetrieveSpareTimeString CIconInfoMouseTip::ms_pFunRetrieveSpareTimeString = 0;
//////////////////////////////////////////////////////////////////////////
static const int s_nProduceSkillsCount = 7;
static const int s_ProduceSkillIds[s_nProduceSkillsCount] =
{
	2300,
	2301,
	2309,
	2310,
	2311,
	2312,
	2313
};

//////////////////////////////////////////////////////////////////////////
// Parm : dwColor0 Bg dwColor1 
void SetTipColors( DWORD dwColor0, DWORD dwColor1,
				  DWORD dwWhite, 
				  DWORD dwGrayed,
				  DWORD dwBlue,
				  DWORD dwGreen,
				  DWORD dwGold,
				  DWORD dwYellow,
				  DWORD dwRed)
				  //DWORD dwPurple) jiayi
{
	g_dwColorTip0 = dwColor0;
	g_dwColorTip1 = dwColor1;

	WHITE_COLOR = dwWhite;
	GRAYED_COLOR = dwGrayed;
	BLUE_COLOR = dwBlue;
	GREEN_COLOR =  dwGreen;
	GOLD_COLOR =  dwGold;
	YELLOW_COLOR = dwYellow;
	RED_COLOR = dwRed;
	//Purple_COLOR = dwPurple; jiayi
}

S_IconInfoBase::S_IconInfoBase()
{
	//Clear();
	m_nFontSize = 12;
	m_nItemLevel = -1;	
	m_eColorFrameType = eColorFrame_None;
    m_eLastLineType = ELINE_TYPE_NONE;
    m_pLastPicInfo = NULL;
    m_bShowBottomTime = false;
// 	s_ProduceSkillIds.clear();
// 	s_ProduceSkillIds.push_back( 2300 );
// 	s_ProduceSkillIds.push_back( 2301 );
// 	s_ProduceSkillIds.push_back( 2309 );
// 	s_ProduceSkillIds.push_back( 2310 );
// 	s_ProduceSkillIds.push_back( 2311 );
// 	s_ProduceSkillIds.push_back( 2312 );
// 	s_ProduceSkillIds.push_back( 2313 );
}

void S_IconInfoBase::Clear()
{
	m_nIconPicId = -1;
	m_nDisableIconPicId = -1;
	m_nNineGridPic = -1;
	m_nIconLockId = -1;
	m_nIconUnLockId = -1;
	m_nShopPicId = -1;
	//	m_nPicId = -1;
	m_ucIconInfoLine = 0;
	m_ucIconOtherInfoLine = 0;
	m_usByteMaxWidthCount = 0;
	m_usByteOtherInfoMaxWidthCount = 0;
	m_bShowCount = false;
	m_eColorFrameType = eColorFrame_None;

	for ( int n=0; n<MAX_ICON_INFO_EX_LINE_COUNT; n++ )
	{
		if( GetIconInfoByIndex(n) )
			GetIconInfoByIndex(n)->Clear();
	}
	for ( int n=0; n<MAX_ICON_OTHER_INFO_EX_LINE_COUNT; n++ )
	{
		if( GetOtherIconInfoByIndex(n) )
			GetOtherIconInfoByIndex(n)->Clear();
	}

	m_usWidth = 0;
	m_usHeight = 0;

	m_strHotKey = "";
    m_bShowBottomTime  = false;
	//m_nFontSize = 0;
}

void S_IconInfoBase::DisplayIcon( IN RECT* prcDst, COLORREF col, int nFontIndex, int nFontSize, COLORREF colFont,
                                 eIconDrawState eEnable,ControlFrame* pFatherFrame )
{
	if ( IsNull() )
		return;

    // 加载Icon图片     added by zhuomeng.hu		[10/12/2010]
    if ( !IconManager::Get().m_ImageFinder.GetDstByName( m_strIconBigImageFilename.c_str() ) )
    {
    	char filename[256];
    	int nPicId = -1;
    	sprintf_s( filename, sizeof( filename ) / sizeof(char) - 1, "%s/Data/%s", GetRootPath(), m_strIconBigImageFilename.c_str() );
    	ControlPictureManager::S_Pic* pPic = theControlPictureManager.RegisterTexture( &nPicId, filename );
        IconManager::Get().m_ImageFinder.Register( m_strIconBigImageFilename.c_str(), pPic );
    }

	RECT rcSrc = {0,0,TILE_SIZE,TILE_SIZE};
	if (!m_strIconBigImageFilename.empty())
	{
		rcSrc.left = m_usIconImageColumn * m_ucIconSize;
		rcSrc.right = rcSrc.left + m_ucIconSize;
		rcSrc.top = m_usIconImageRow * m_ucIconSize;
		rcSrc.bottom = rcSrc.top + m_ucIconSize;
	}
	if ( eEnable == eIcon_Enable )
	{
		theControlPictureManager.BitBlt( &m_nIconPicId,
			IconFileName().c_str(),
			prcDst, &rcSrc, col );
	}
	if ( eEnable == eIcon_Disable )
	{
		theControlPictureManager.BitBlt( &m_nDisableIconPicId,
			IconFileName().c_str(),
			prcDst, &rcSrc, D3DCOLOR_XRGB(100,100,100) );
	}

	if ( eEnable == eIcon_Shop )
	{
		RECT rcSrcShop = {0,0,TILE_SIZE*2,TILE_SIZE*2};
		theControlPictureManager.BitBlt( &m_nShopPicId,
			ShopIconFileName().c_str(),
			prcDst, &rcSrcShop, col );
	}

	ExpressionManager::ExpressionData* pData = NULL;
	if( ( m_eColorFrameType != eColorFrame_None ) && ( m_nItemLevel >= 2 ) )
	{
		char szFrameFilename[MAX_PATH];
		switch( m_eColorFrameType )
		{
		case eColorFrame_Level:
			{
				sprintf_s( szFrameFilename, MAX_PATH, "#101%d", m_nItemLevel );
				pData =  ExpressionManager::GetInstance().GetExpressionInfo(szFrameFilename);
			}
			break;
		case eColorFrame_Active:
			{
				pData =  ExpressionManager::GetInstance().GetExpressionInfo("#1018");
			}
			break;
		case eColorFrame_Select:
			{
				pData =  ExpressionManager::GetInstance().GetExpressionInfo("#1020");
			}
			break;
		default:
			break;
		}		
	}
	else if (m_eColorFrameType == eColorFrame_Select)
		pData =  ExpressionManager::GetInstance().GetExpressionInfo("#1020");

	if (pData)
	{
		ExpressionManager::GetInstance().DrawExpression( pData, *prcDst );
		if (pFatherFrame)
		{
			pFatherFrame->GetExpressionUpdaterNotNULL()->AddExpress(pData);
		}
	}

    if( m_bShowBottomTime )
    {
        DWORD dwSpareTime =GetSpareTime();
        if( SpareTime() == MAX_SPARETIME )//约定，最大时间的时候为无限时间N/A
        {
            char szBuffer[5] = " ";
            RECT rcCount;
            rcCount = *prcDst;
            int nW = prcDst->right - prcDst->left;

            int nFontW = 0;		
            if( FontSystem::IsUseNewFont() )
            {			
                std::wstring wtext = Common::_tstring::toWideString( szBuffer );
                nFontW = FontSystem::GetTextWidth( nFontIndex, wtext, 0, wtext.length(), false );
            }
            else
                nFontW = nFontSize*(LONG)strlen(szBuffer)/2 * ControlObjectGetREAL_SCALE(NULL);

            rcCount.left += (nW-nFontW)/2;
            rcCount.top = prcDst->bottom - 1;
            rcCount.bottom = rcCount.top + nFontSize * ControlObjectGetREAL_SCALE(NULL);
            FontSystem::DrawTextRGB( szBuffer, &rcCount, DT_NOCLIP, 0xffe3ffff, nFontIndex );
        }
        else if( dwSpareTime > 0 && dwSpareTime < MAX_SPARETIME )
        {//画buf 即玩家受到的状态 显示它的剩余时间(为什么画在这里 策划要求)

            char szBuffer[128];
            RECT rcCount;
            int nSecond = dwSpareTime / 1000;
            int nMinute = nSecond / 60;
            int nHour = nMinute / 60;
            int nDay = nHour / 24;
            COLORREF colTime;
			if (ms_pFunRetrieveTimeString)
			{
				ms_pFunRetrieveTimeString(szBuffer, colTime, nDay, nHour, nMinute, nSecond);
			}
			rcCount = *prcDst;
            int nW = prcDst->right - prcDst->left;
            int nFontW = 0;		
            if( FontSystem::IsUseNewFont() )
            {			
                std::wstring wtext = Common::_tstring::toWideString( szBuffer );
                nFontW = FontSystem::GetTextWidth( nFontIndex, wtext, 0, wtext.length(), false );
            }
            else
                nFontW = nFontSize*(LONG)strlen(szBuffer)/2 * ControlObjectGetREAL_SCALE(NULL);

            rcCount.left += (nW-nFontW)/2;
            //		rcCount.top = prcDst->bottom - nFontSize;
            rcCount.top = prcDst->bottom - 1;
            rcCount.bottom = rcCount.top + nFontSize * ControlObjectGetREAL_SCALE(NULL);
            FontSystem::DrawTextRGB( szBuffer, &rcCount, DT_NOCLIP, colTime, nFontIndex );
            if( pFatherFrame )
                pFatherFrame->SetRedraw();
        }
    }

	if ( Count() > 1 && m_bShowCount )
	{
		static char szCount[16];
		static char szBuffer[128];
		static RECT rcCount;
		itoa( Count(), szCount, 10 );

		rcCount = *prcDst;
		//rcCount.left = prcDst->right - nFontSize*(LONG)strlen(szCount)/2;
		rcCount.right = prcDst->right - 3 * ControlObjectGetSCALE(NULL);
		rcCount.top = prcDst->bottom - nFontSize;
		//UiDrawer::FillRect2D( rcCount, 0x7f000000 );
		if( MaxCount() == -1 )
		{
			//FontSystem::DrawTextRGB( &rcCount, szCount, colFont, nFontIndex );
			FontSystem::DrawTextRGB( szCount, &rcCount, DT_RIGHT|DT_BOTTOM|DT_NOCLIP, colFont, nFontIndex );
		}
		else
		{
			sprintf( szBuffer, "%d/%d", Count(), MaxCount() );
			rcCount.left = prcDst->right - nFontSize*(LONG)strlen(szBuffer)/2;
			//FontSystem::DrawTextRGB( &rcCount, szBuffer, colFont, nFontIndex );
			FontSystem::DrawTextRGB( szBuffer, &rcCount, DT_RIGHT|DT_BOTTOM|DT_NOCLIP, colFont, nFontIndex );
		}

	}

	/*

	@加锁的物品上显示锁字
	*/
	if( IsLocked() )
	{
		//static char szLock[16];
		//static char szBuffer[128];
		//static RECT rcCount;
		//strcpy(szLock, theXmlString.GetString(eText_Lock));
		//rcCount = *prcDst;
		//rcCount.left = prcDst->left;
		//rcCount.top = prcDst->bottom - nFontSize;
		////FontSystem::DrawTextRGB( &rcCount, szLock, colFont, nFontIndex );
		//FontSystem::DrawTextRGB( szLock, &rcCount, 0, colFont, nFontIndex );
	}

	//防盗加锁 显示锁图标
// 	if( IsItemLocked() )
// 	{
// 		RECT rcDest = *prcDst;
// 
// 		int width,height;
// 
// 		width = rcDest.right - rcDest.left;
// 		height = rcDest.bottom - rcDest.top;
// 
// 		width /= 3;
// 		height /= 3;
// 
// 		rcDest.right = rcDest.left+width;
// 		rcDest.bottom = rcDest.top+height;
// 
// 		rcSrc.left = 0;
// 		rcSrc.top = 0;
// 		rcSrc.right = 16;
// 		rcSrc.bottom = 16;
// 
// 		char filename[MAX_PATH];
// 		char fullpath[MAX_PATH];
// 		sprintf( filename, "%s", SHOW_LOCK_PATH );
// 		sprintf( fullpath, "%s\\%s", GetRootPath(), filename );
// 
// 		theControlPictureManager.BitBlt( &m_nIconLockId,
// 			fullpath,
// 			&rcDest, &rcSrc, D3DCOLOR_XRGB(255,255,255) );
// 	}
}

void S_IconInfoBase::SetTextRect(int nFontIndex, int nFontWidth_, IN OUT RECT* pTextRect)
{
	int nFontWidth = nFontWidth_;
	if (FontSystem::IsUseNewFont())
	{
		nFontWidth = FontSystem::GetFontWidth( nFontIndex );
	}

	int nTextWidth = nFontWidth * ( max(m_usByteMaxWidthCount,m_usByteOtherInfoMaxWidthCount) / 2 );
	int RectWidth = pTextRect->right - pTextRect->left;
	pTextRect->left = pTextRect->left + (RectWidth - nTextWidth) / 2;
	pTextRect->right = pTextRect->right - (RectWidth - nTextWidth) / 2;
}

void S_IconInfoBase::DisplayInfo( IN RECT *prc, const bool bIsShop,
								 const int nFontIndex, const int nFontSize, const COLORREF col,
								 const bool bFaveFrame, const bool bShowAllInfo)
{
	//*******************
	//## 由于fontSize和算出来的高度没有多大差别, 所以对于在这个类里面的很多nFontSize不做修改.
	int nFontHeight=FontSystem::GetFontHeight(nFontIndex);
	//*******************

	if ( m_ucIconInfoLine == 0 )
		return;

	assert( prc );
	DWORD DT_Flag = DT_LEFT;
	if ( theIconInfoMouseTip.m_bShopOpen == true && Cost() != 0 )
	{
		prc->top -= nFontHeight;
		prc->bottom += nFontHeight;
	}
	RECT rcText;
	
	if( bShowAllInfo || m_ucIconInfoLine != 1 )
	{
		SetRect( &rcText, prc->left+OFFSET_WIDTH, prc->top+OFFSET_WIDTH +FRAME_SIZE,
		prc->right-OFFSET_WIDTH, 
		prc->top+OFFSET_WIDTH+FRAME_SIZE+nFontHeight
		);
		SetTextRect(nFontIndex, nFontSize, &rcText);
	}
	else
	{
		rcText = *prc;
		rcText.left += OFFSET_HEIGHT;
		rcText.right -= OFFSET_HEIGHT;
		rcText.top += OFFSET_HEIGHT;
		rcText.bottom -= OFFSET_HEIGHT;
	}
	if ( bFaveFrame )
	{
		//UiDrawer::FillRect2D( *prc, g_dwColorTip0  );
		theControlPictureManager.RenderNineGrid(
			m_nNineGridPic,
			TIP_FRAME_FILENAME,
			TIP_FRAME_TOTALWIDTH,
			TIP_FRAME_TOTALHEIGHT,
			TIP_FRAME_GRIDWIDTH,
			TIP_FRAME_GRIDHEIGHT,
			prc
			);
	}

	/*if( bShowAllInfo )
		rcText.left += FRAME_SIZE * 2;*/
	RECT rcIconText = rcText;
	RECT rcTempText = rcText;
	RECT rcImageRightText = rcText;

	int nIconHeightIncrease = 0;
	int nIconLeftSize = rcText.left;
	int nIconRightSize = rcText.right;
	int nIconTopSize = rcText.top;
	int nIconBottomSize = rcText.bottom;

	// commented out, jiayi, [2009/11/10]
	//int nInfoLine = bShowAllInfo ? m_nIconInfoLine : 1;

    // modified by zhuomeng.hu		[11/30/2010]
    m_pLastPicInfo = NULL;
	for( int n = 0; n < m_ucIconInfoLine; ++n )
	{
        if( n == 0 )
            m_eLastLineType = ELINE_TYPE_NONE;

		stIconInfo *pInfo = GetIconInfoByIndex(n);
		if( !pInfo )
			break;
		stIconInfoEx* pInfoEx = dynamic_cast< stIconInfoEx* >( pInfo );
		if( pInfoEx )
		{
            if( pInfoEx->m_bLine )
            {
                DisplayInfo_Line( rcText, pInfoEx, prc );
                m_eLastLineType = ELINE_TYPE_LINE;
                continue;
            }
			else if( pInfoEx->m_bIcon ) // render icon
			{
				DisplayInfo_Icon(rcIconText, rcText, pInfoEx, nFontHeight, nIconLeftSize, nIconRightSize, nIconHeightIncrease);
                m_eLastLineType = ELINE_TYPE_ICON;
                m_pLastPicInfo = pInfoEx;
				continue;			
			}
			else if( pInfoEx->m_bImage )// render image
			{
				DisplayInfo_Image(rcImageRightText, pInfoEx, rcText, nFontHeight, prc);
                m_pLastPicInfo = pInfoEx;
				continue;
			}
			else if( pInfoEx->m_bGif ) //  render gif
			{
				DisplayInfo_Gif(rcImageRightText, rcText, pInfoEx);
                m_eLastLineType = ELINE_TYPE_GIF;
                m_pLastPicInfo = pInfoEx;
				continue;
			}

			if( pInfoEx->m_bIconRightText )//是显示在右面的文字(特指icon右侧的)
			{
				rcIconText.left = nIconLeftSize;
				rcIconText.right = nIconRightSize;
				rcIconText.top += nIconHeightIncrease;
				rcIconText.bottom = rcIconText.top + nIconHeightIncrease;
				rcTempText = rcIconText;
                m_eLastLineType = ELINE_TYPE_ICON_RIGHT_TEXT;
			}
			else if( pInfoEx->m_bRightText )// 右侧文字，出现在最后的一次image的右侧
			{
				rcTempText = rcImageRightText;
// 				rcTempText.top -= ( OFFSET_HEIGHT / 2 );
// 				rcTempText.bottom -= ( OFFSET_HEIGHT / 2 );
                m_eLastLineType = ELINE_TYPE_IMAGE_RIGHT_TEXT;
			}
			else
			{
				rcTempText = rcText;
                m_eLastLineType = ELINE_TYPE_NORMAL_TEXT;
			}
		}
		else
		{
			rcTempText = rcText;
            m_eLastLineType = ELINE_TYPE_NORMAL_TEXT;
		}
		
		if ( pInfo->m_col != 0 )
		{
			//##
			FontSystem::DrawText( pInfo->m_strInfo.c_str(), &rcTempText, pInfo->m_dwTextAlign|DT_NOCLIP,
				pInfo->m_col, nFontIndex );
			
		}
		else
		{
			//##
			FontSystem::DrawTextRGB( pInfo->m_strInfo.c_str(), &rcTempText, pInfo->m_dwTextAlign|DT_NOCLIP,
				col, nFontIndex );
			
		}	
		if( !pInfoEx || ( pInfoEx && !pInfoEx->m_bIconRightText && !pInfoEx->m_bRightText ) )
		{
			rcText.top += nFontHeight+OFFSET_HEIGHT;  
			rcText.bottom += nFontHeight+OFFSET_HEIGHT;
		}
	}
	if ( bShowAllInfo == true )
	{
		for( int n=0; n<m_ucIconOtherInfoLine; n++ )
		{
			if( !GetOtherIconInfoByIndex(n) )
				continue;
			stIconInfo *pInfo = GetOtherIconInfoByIndex(n);
			if ( pInfo->m_col != 0 )
			{
				//##
				FontSystem::DrawText( pInfo->m_strInfo.c_str(), &rcText, pInfo->m_dwTextAlign|DT_NOCLIP,
					pInfo->m_col, nFontIndex );
				
			}
			else
			{
				//##
				FontSystem::DrawTextRGB( pInfo->m_strInfo.c_str(), &rcText,
					pInfo->m_dwTextAlign|DT_NOCLIP, col, nFontIndex );
				
			}
			rcText.top += nFontHeight+OFFSET_HEIGHT;
			rcText.bottom += nFontHeight+OFFSET_HEIGHT;
		}
	}
	if ( theIconInfoMouseTip.m_bShopOpen == true && Cost() > 0 )
	{
		//char szPrice[64];
		//int nGold = Cost()/1000;
		//int nMoney = Cost()%1000;
		//if ( nGold > 0 )
		//{
		//	sprintf( szPrice, 
		//		theXmlString.GetString(eText_ShopOpenPrice),
		//		nGold, nMoney );
		//}
		//else
		//{
		//	sprintf( szPrice, "%s:%ld%s"/*出售单价:5铜*/,
		//		theXmlString.GetString(eText_Sell_Price_0),
		//		nMoney,
		//		theXmlString.GetString(eText_Money),
		//		nMoney );
		//}
		////FontSystem::DrawTextRGB( &rcText, szPrice, col, nFontIndex, DT_Flag );
		//FontSystem::DrawTextRGB( szPrice, &rcText, DT_Flag, col, nFontIndex );
	}
	if ( 0 && bFaveFrame )
	{
		//		UiDrawer::DrawRect2D( *prc, 0xff0000ff );
		UiDrawer::DrawRect2D( *prc, g_dwColorTip1 /*0xFF8F3200*/ );
		//
		RECT rc = *prc;
		rc.left += 1;
		rc.top += 1;
		rc.right -= 1;
		rc.bottom -= 1;
		DWORD dwColorBottom = 0xFF929292;
		DWORD dwColorRight = 0xFF929292;
		DWORD dwColorLeft = 0xFF929292;
		DWORD dwColorTop = 0xFF929292;
		CBaseGraphics *g = GetDrawer();
		// 下
		g->DrawLine2D( rc.left, rc.bottom, rc.right+1, rc.bottom, dwColorBottom );
		// 右
		g->DrawLine2D( rc.right, rc.top, rc.right, rc.bottom, dwColorRight );
		// 左
		g->DrawLine2D( rc.left, rc.bottom, rc.left, rc.top, dwColorLeft );
		// 上
		g->DrawLine2D( rc.left, rc.top, rc.right, rc.top, dwColorTop );
	}
	//**********************************
	// 	Simple2DVertex vertex[4];
	// 
	// 	float z = 0.0f;
	// 
	// 	vertex[0].p = D3DXVECTOR4( rcText.left, rcText.bottom, z, 1 );
	// 	vertex[0].color = 0xffffffff;
	// 	vertex[0].u = 0;
	// 	vertex[0].v = 1;
	// 
	// 	vertex[1].p = D3DXVECTOR4( rcText.left, rcText.top, z, 1 );
	// 	vertex[1].color = 0xffffffff;
	// 	vertex[1].u = 0;
	// 	vertex[1].v = 0;
	// 
	// 	vertex[2].p = D3DXVECTOR4( rcText.right, rcText.bottom, z, 1 );
	// 	vertex[2].color = 0xffffffff;
	// 	vertex[2].u = 1;
	// 	vertex[2].v = 1;
	// 
	// 	vertex[3].p = D3DXVECTOR4( rcText.right, rcText.top, z, 1 );
	// 	vertex[3].color = 0xffffffff;
	// 	vertex[3].u = 1;
	// 	vertex[3].v = 0;
	// 
	// 	static short index[] = { 0, 1, 2, 2, 1, 3 };
	// 	short idx = GetEngine()->GetTextureManager()->RegisterTexture( "Data\\TEXTURE\\AttackEffect\\Number.tga", TRUE, 0, TRUE );	
	// 
	// 	GetEngine()->GetRenderer()->DirectPushSurface(
	// 		idx,
	// 		-1, 
	// 		OBJECT2D_SHADER, 
	// 		Simple2DVertex_FVF,
	// 		sizeof( Simple2DVertex ), 
	// 		(BYTE*)vertex,
	// 		4,
	// 		(BYTE*)index,
	// 		2, eAlphaBlend|eLinearFilter );
	// 	idx = GetEngine()->GetTextureManager()->RegisterTexture( "Data\\TEXTURE\\AttackEffect\\MISS_1.tga", TRUE, 0, TRUE );
	// 	GetEngine()->GetRenderer()->DirectPushSurface(
	// 		idx,
	// 		-1, 
	// 		OBJECT2D_SHADER, 
	// 		Simple2DVertex_FVF,
	// 		sizeof( Simple2DVertex ), 
	// 		(BYTE*)vertex,
	// 		4,
	// 		(BYTE*)index,
	// 		2, eAlphaBlend|eLinearFilter );
	//**********************************
}

void S_IconInfoBase::Clone(S_IconInfoBase *pkInfo)
{
	m_nItemLevel = pkInfo->m_nItemLevel;
	m_eColorFrameType = pkInfo->m_eColorFrameType;
	m_nIconPicId = pkInfo->m_nIconPicId;
	m_nDisableIconPicId = pkInfo->m_nDisableIconPicId;
	m_nShopPicId = pkInfo->m_nShopPicId;
	m_nNineGridPic = pkInfo->m_nNineGridPic;
	m_ucIconInfoLine = pkInfo->m_ucIconInfoLine;
	m_ucIconLine = pkInfo->m_ucIconLine;
	m_ucIconOtherInfoLine = pkInfo->m_ucIconOtherInfoLine;
	m_usByteMaxWidthCount = pkInfo->m_usByteMaxWidthCount;
	m_usByteOtherInfoMaxWidthCount = pkInfo->m_usByteOtherInfoMaxWidthCount;
	m_bShowCount = pkInfo->m_bShowCount;
	m_usWidth = pkInfo->m_usWidth;
	m_usHeight = pkInfo->m_usHeight;
	m_nFontSize = pkInfo->m_nFontSize;
	m_strHotKey = pkInfo->m_strHotKey;
	m_strIconBigImageFilename = pkInfo->m_strIconBigImageFilename;
	m_ucIconSize = pkInfo->m_ucIconSize;
	m_usIconImageRow = pkInfo->m_usIconImageRow;
	m_usIconImageColumn = pkInfo->m_usIconImageColumn;
    m_eLastLineType = pkInfo->m_eLastLineType;
    m_bShowBottomTime = pkInfo->m_bShowBottomTime;
}

int S_IconInfoBase::CaculateWidthHeight( const int nFontSize, int nInfoFontIndex /*= -1*/ )
{
	int nIconStunSize = 0;
	int nInfoLine = m_ucIconInfoLine;
	int nIconCount = 0;
	
	for( int n=0; n<nInfoLine; n++ )
	{
		stIconInfo *pInfo = GetIconInfoByIndex(n);
		if( !pInfo )
			break;
		stIconInfoEx* pInfoEx = dynamic_cast< stIconInfoEx* >(pInfo);
		if( pInfoEx && pInfoEx->m_bIcon ) // render icon
		{
			nIconStunSize += pInfoEx->m_ucRightRowCount;
			++ nIconCount;
		}
	}
	bool bCaculateWidth = true;
	if( max( m_usByteMaxWidthCount, m_usByteOtherInfoMaxWidthCount ) * nFontSize / 2  > TIP_ICON_SIZE * ControlObjectGetSCALE(NULL) )
	{
		bCaculateWidth = false;
	}
	if (FontSystem::IsUseNewFont())
	{
		int nFontWidth=FontSystem::GetFontWidth( nInfoFontIndex )*1.1f;
		m_usWidth = nFontWidth * ( (float)(max(m_usByteMaxWidthCount,m_usByteOtherInfoMaxWidthCount)) / 2 ) +
			OFFSET_HEIGHT * 2 + FRAME_SIZE * 2 + (int)bCaculateWidth * TIP_ICON_SIZE * ControlObjectGetSCALE(NULL) * ( nIconCount != 0 );
		m_usHeight = ( FontSystem::GetRealHeight(nInfoFontIndex) + OFFSET_HEIGHT ) * ( m_ucIconInfoLine + m_ucIconOtherInfoLine - nIconStunSize ) + 
			OFFSET_HEIGHT + FRAME_SIZE * 2 + ( TIP_ICON_SIZE * nIconCount ) * ControlObjectGetSCALE(NULL);
	}
	else
	{
		m_usWidth = nFontSize * ( (float)(max(m_usByteMaxWidthCount,m_usByteOtherInfoMaxWidthCount)) / 2 ) +
			OFFSET_HEIGHT * 2 + FRAME_SIZE * 2 + (int)bCaculateWidth * TIP_ICON_SIZE * ControlObjectGetSCALE(NULL) * ( nIconCount != 0 );

		m_usHeight = ( nFontSize + OFFSET_HEIGHT ) * ( m_ucIconInfoLine + m_ucIconOtherInfoLine - nIconStunSize ) + 
			OFFSET_HEIGHT + FRAME_SIZE * 2 + ( TIP_ICON_SIZE * nIconCount ) * ControlObjectGetSCALE(NULL);
	}	
	return m_usWidth;
}

RECT S_IconInfoBase::DisplayInfo( const int nX, const int nY, const bool bIsShop,
								 const int nFontIndex, const int nFontSize, const COLORREF col,
								 const bool bFaveFrame, const bool bShowAllInfo )
{
	FontRender::EFontRenders eOldIdx = FontRender::EFR_FIRST;
	if( FontSystem::IsUseNewFont() )
	{
		eOldIdx = FontRender::getFontRender()->GetDefaultRendererIdx();
		FontRender::getFontRender()->SetDefaultRendererIdx( FontRender::EFR_FIRST );
		FontSystem::ClearRender( FontRender::EFR_FIRST );
	}

	RECT rc;

	// 不做偏移，直接显示在所传的坐标位置 [11/24/2010 zhangjiayi]
	rc.left = nX;
	rc.top = nY;
// 	if( bFaveFrame )
// 	{
// 		rc.left = nX + 20;
// 		rc.top = nY + 15;
// 	}
// 	else
// 	{
// 		rc.left = nX + 5;
// 		rc.top = nY + 10;
// 	}

	if( !bShowAllInfo )
	{
		rc.top -= ( nFontSize + 25 );
	}

	int nIconStunSize = 0;
	int nInfoLine = bShowAllInfo ? m_ucIconInfoLine : 1;
	int nIconCount = 0;
	bool bHaveImage = false;
	for( int n=0; n<nInfoLine; n++ )
	{
		stIconInfo *pInfo = GetIconInfoByIndex(n);
		if( !pInfo )
			break;
		stIconInfoEx* pInfoEx = dynamic_cast< stIconInfoEx* >(pInfo);
		if( pInfoEx && pInfoEx->m_bIcon ) // render icon
		{
			nIconStunSize += pInfoEx->m_ucRightRowCount;
			++ nIconCount;
		}
		if( pInfoEx && pInfoEx->m_bImage )
		{
			if( bHaveImage )
				++nIconStunSize;
			bHaveImage = true;
		}
	}	
	nIconStunSize = min( 1, nIconStunSize );
	bool bCaculateWidth = true;
	if( max( m_usByteMaxWidthCount, m_usByteOtherInfoMaxWidthCount ) * nFontSize / 2> TIP_ICON_SIZE * ControlObjectGetSCALE(NULL) )
	{
		bCaculateWidth = false;
	}
	if ( bShowAllInfo == true || m_ucIconInfoLine != 1 )
	{			
		//********   //##
		if (FontSystem::IsUseNewFont())
		{
			int nFontWidth=FontSystem::GetFontWidth( nFontIndex )*1.1f;
			rc.right = rc.left + 
				nFontWidth * max(m_usByteMaxWidthCount,m_usByteOtherInfoMaxWidthCount) / 2 +
				OFFSET_HEIGHT * 2 + FRAME_SIZE * 2 + (int)bCaculateWidth * TIP_ICON_SIZE * ControlObjectGetSCALE(NULL) * ( nIconCount != 0 );
			rc.bottom = rc.top +
				( FontSystem::GetRealHeight(nFontIndex) + OFFSET_HEIGHT ) * ( m_ucIconInfoLine + m_ucIconOtherInfoLine - nIconStunSize ) + 
				OFFSET_HEIGHT + FRAME_SIZE * 2 + ( TIP_ICON_SIZE * nIconCount ) * ControlObjectGetSCALE(NULL);

            // 重写了Tip的高度计算 (准确到1像素)      added by zhuomeng.hu		[12/2/2010]
            if( true )
            {
                int nTipHeight = 2 * FRAME_SIZE + OFFSET_HEIGHT + m_ucIconOtherInfoLine *( FontSystem::GetRealHeight( nFontIndex ) + OFFSET_HEIGHT );
                for( int i = 0; i < m_ucIconInfoLine; ++i )
                {
                    stIconInfo *pIconInfo = GetIconInfoByIndex( i );
                    if( !pIconInfo )
                        break;
                    stIconInfoEx* pIconInfoEx = dynamic_cast< stIconInfoEx* >( pIconInfo );
                    // 线
                    if( pIconInfoEx && pIconInfoEx->m_bLine )
                    {
                        if( pIconInfoEx->m_usDestHeight > 0 )
                            nTipHeight += pIconInfoEx->m_usDestHeight;
                        else
                            nTipHeight += pIconInfoEx->m_usImageHeight;
                        nTipHeight += OFFSET_HEIGHT;
                        continue;
                    }
                    // Icon
                    else if( pIconInfoEx && pIconInfoEx->m_bIcon )
                    {
                        nTipHeight += OFFSET_HEIGHT * 2;
                        if( pIconInfoEx->m_usDestHeight > 0 )
                            nTipHeight += pIconInfoEx->m_usDestHeight * ControlObjectGetSCALE( NULL ) + OFFSET_HEIGHT;
                        else
                            nTipHeight += pIconInfoEx->m_usImageHeight * ControlObjectGetSCALE( NULL ) + OFFSET_HEIGHT;
                    }
                    // 图片
                    else if( pIconInfoEx && pIconInfoEx->m_bImage )
                    {
                        if( pIconInfoEx->m_eImageAlignMode == stIconInfoEx::eIIIA_Right )
                            continue;

                        if( pIconInfoEx->m_usDestHeight > 0 )
                            nTipHeight += pIconInfoEx->m_usDestHeight;
                        else
                            nTipHeight += pIconInfoEx->m_usImageHeight;
                        nTipHeight += OFFSET_HEIGHT;
                        continue;
                    }
                    // Gif
                    else if( pIconInfoEx && pIconInfoEx->m_bGif )
                    {
                        if( pIconInfoEx->m_usDestHeight > 0 )
                            nTipHeight += pIconInfoEx->m_usDestHeight * ControlObjectGetSCALE( NULL ) + OFFSET_HEIGHT;
                        else
                            nTipHeight += pIconInfoEx->m_usImageHeight * ControlObjectGetSCALE( NULL ) + OFFSET_HEIGHT;
                    }
                    // 右侧文字
                    else if( pIconInfoEx && ( pIconInfoEx->m_bIconRightText || pIconInfoEx->m_bRightText ) )
                    {
                        continue;
                    }
                    // 其他 (左侧文字)
                    else
                    {
                        nTipHeight += FontSystem::GetRealHeight( nFontIndex ) + OFFSET_HEIGHT;
                    }
                }
                rc.bottom = rc.top + nTipHeight;
            }
		}
		else
		{
			// 原来的代码
			rc.right = rc.left + 
				nFontSize * ( max(m_usByteMaxWidthCount,m_usByteOtherInfoMaxWidthCount) / 2 ) +
				OFFSET_HEIGHT * 2 + FRAME_SIZE * 2 + (int)bCaculateWidth * TIP_ICON_SIZE * ControlObjectGetSCALE(NULL) * ( nIconCount != 0 );
			rc.bottom = rc.top +
				( nFontSize + OFFSET_HEIGHT ) * ( m_ucIconInfoLine + m_ucIconOtherInfoLine - nIconStunSize ) + 
				OFFSET_HEIGHT + FRAME_SIZE * 2 + ( TIP_ICON_SIZE * nIconCount ) * ControlObjectGetSCALE(NULL);
		}

		//********
	}
	else
	{
		int nIconStringLen = 0;
		if( GetIconInfoByIndex(0) )
			nIconStringLen = GetIconInfoByIndex(0)->m_strInfo.size();
		
		//********   //##
		if (FontSystem::IsUseNewFont())
		{
			std::wstring text = Common::_tstring::toWideString( GetIconInfoByIndex(0)->m_strInfo.c_str() );
			int nWidth=FontSystem::GetTextWidth(nFontIndex, text, 0, text.length(), false);
			rc.right = rc.left + nWidth + OFFSET_HEIGHT * 2;
			rc.bottom = rc.top + FontSystem::GetRealHeight(nFontIndex) + OFFSET_HEIGHT * 2;
		}
		else
		{
			rc.right = rc.left + nFontSize/2*nIconStringLen + OFFSET_HEIGHT + 1;  
			rc.bottom = rc.top + nFontSize + OFFSET_HEIGHT + 1;
		}
		//********
		
	}
	int nW = rc.right - rc.left;
	int nH = rc.bottom - rc.top;
	if( rc.left < 0 )
	{
		rc.left = 0;
		rc.right = nW;
	}
	if( rc.right > SCREEN_WIDTH-1 )
	{
		rc.right = SCREEN_WIDTH;
		rc.left = rc.right - nW;
	}
	if( rc.top < 0 )
	{
		rc.top = 0;
		rc.bottom = nH;
	}
	if( rc.bottom > SCREEN_HEIGHT-1 )
	{
		rc.bottom = SCREEN_HEIGHT;
		rc.top = rc.bottom - nH;
	}
	DisplayInfo( &rc, bIsShop, nFontIndex, nFontSize, col, bFaveFrame, bShowAllInfo );

	if( FontSystem::IsUseNewFont() )
	{
		FontRender::getFontRender()->SetDefaultRendererIdx( eOldIdx );
		FontSystem::DoRender( FontRender::EFR_FIRST );
	}	
	return rc;
}

void S_IconInfoBase::SetInfo( IN const char* szInfo, IN DWORD dwAlign /*= DT_CENTER | DT_VCENTER*/ )
{
	assert( szInfo );
	m_ucIconInfoLine = 0;
	m_usByteMaxWidthCount = 0;
	//
	char szTemp[256];
	memset( szTemp, 0, sizeof(szTemp) );
	int nLength = 0;
	int nInfoLength = strlen(szInfo);
	DWORD dwColor = 0;
	for ( UINT n=0; n<nInfoLength; n++ )
	{
		if( !GetIconInfoByIndex(m_ucIconInfoLine) )
			break;
		if ( szInfo[n] != 0 && (szInfo[n] == '\n') )
		{
			GetIconInfoByIndex(m_ucIconInfoLine)->m_strInfo = szTemp;
			GetIconInfoByIndex(m_ucIconInfoLine)->m_col = dwColor;
			GetIconInfoByIndex(m_ucIconInfoLine)->m_dwTextAlign = dwAlign;
			memset( szTemp, 0, sizeof(szTemp) );
			nLength = 0;
			dwColor = 0;
			m_ucIconInfoLine++;
		}
		else if( szInfo[n] == '\\' && szInfo[n+1] == 'n' )
		{
			GetIconInfoByIndex(m_ucIconInfoLine)->m_strInfo = szTemp;
			GetIconInfoByIndex(m_ucIconInfoLine)->m_col = dwColor;
			GetIconInfoByIndex(m_ucIconInfoLine)->m_dwTextAlign = dwAlign;
			memset( szTemp, 0, sizeof(szTemp) );
			nLength = 0;
			dwColor = 0;
			m_ucIconInfoLine ++;
			n++;
		}
		else if ( n < nInfoLength-10 &&
			(szInfo[n] == '{' || szInfo[n] == '<') && szInfo[n+1] == '#' )
		{
			char szColor[10];
			memset( szColor, 0, sizeof(szColor) );
			memcpy( szColor, &szInfo[n+2], 8 );
			sscanf( szColor, "%x", &dwColor );
			n += 10;
		}
		else
		{
			szTemp[nLength++] = szInfo[n];
			if ( n == nInfoLength-1 && strlen(szTemp) > 0 )
			{
				GetIconInfoByIndex(m_ucIconInfoLine)->m_strInfo = szTemp;
				GetIconInfoByIndex(m_ucIconInfoLine)->m_col = dwColor;
				GetIconInfoByIndex(m_ucIconInfoLine)->m_dwTextAlign = dwAlign;
				m_ucIconInfoLine++;
			}
		}
		assert( m_ucIconInfoLine < MAX_ICON_INFO_EX_LINE_COUNT );
	}
	for ( int n=0; n<m_ucIconInfoLine; n++ )
	{
		if( !GetIconInfoByIndex( n ) )
			break;
		int nSize = GetIconInfoByIndex(n)->m_strInfo.size();
		stIconInfoEx* pInfoEx = dynamic_cast< stIconInfoEx* >(GetIconInfoByIndex(n));
		if( pInfoEx && pInfoEx->m_bIconRightText )
			nSize += TIP_ICON_SIZE / m_nFontSize * 2;
		m_usByteMaxWidthCount = max( nSize, m_usByteMaxWidthCount );
	}

	m_usWidth = m_nFontSize/2*max(m_usByteMaxWidthCount,m_usByteOtherInfoMaxWidthCount) + OFFSET_HEIGHT*2 + FRAME_SIZE*2;
	m_usHeight = (m_nFontSize+OFFSET_HEIGHT)*(m_ucIconInfoLine+m_ucIconOtherInfoLine) + OFFSET_HEIGHT + FRAME_SIZE*2;

}

void S_IconInfoBase::ClearOtherInfo()
{
	m_ucIconOtherInfoLine = 0;
	m_usByteOtherInfoMaxWidthCount = 0;
}

void S_IconInfoBase::SetOtherInfo( IN const char* szInfo, DWORD dwAlign /* = DT_LEFT */ )
{
	assert( szInfo );
// 	m_nIconOtherInfoLine = 0;
// 	m_nByteOtherInfoMaxWidthCount = 0;
	//
	char szTemp[256];
	memset( szTemp, 0, sizeof(szTemp) );
	int nLength = 0;
	int nInfoLength = strlen(szInfo);
	DWORD dwColor = 0;
	for ( UINT n=0; n<nInfoLength; n++ )
	{
		if( !GetOtherIconInfoByIndex(m_ucIconOtherInfoLine) )
			break;
		if ( szInfo[n] != 0 && szInfo[n] == '\n' )
		{
			GetOtherIconInfoByIndex(m_ucIconOtherInfoLine)->m_strInfo = szTemp;
			GetOtherIconInfoByIndex(m_ucIconOtherInfoLine)->m_col = dwColor;
			GetOtherIconInfoByIndex(m_ucIconOtherInfoLine)->m_dwTextAlign = dwAlign;
			memset( szTemp, 0, sizeof(szTemp) );
			nLength = 0;
			dwColor = 0;
			m_ucIconOtherInfoLine++;
		}
		else if ( n < nInfoLength-10 &&
			(szInfo[n] == '{' || szInfo[n] == '<') && szInfo[n+1] == '#' )
		{
			char szColor[10];
			memset( szColor, 0, sizeof(szColor) );
			memcpy( szColor, &szInfo[n+2], 8 );
			sscanf( szColor, "%x", &dwColor );
			n += 10;
		}
		else
		{
			szTemp[nLength++] = szInfo[n];
			if ( n == nInfoLength-1 && strlen(szTemp) > 0 )
			{
				GetOtherIconInfoByIndex(m_ucIconOtherInfoLine)->m_strInfo = szTemp;
				GetOtherIconInfoByIndex(m_ucIconOtherInfoLine)->m_col = dwColor;
				GetOtherIconInfoByIndex(m_ucIconOtherInfoLine)->m_dwTextAlign = dwAlign;
				m_ucIconOtherInfoLine++;
			}
		}
		assert( m_ucIconOtherInfoLine < MAX_ICON_OTHER_INFO_EX_LINE_COUNT );
	}
	for ( int n=0; n<m_ucIconOtherInfoLine; n++ )
	{
		if( !GetOtherIconInfoByIndex(n) )
			continue;
		m_usByteOtherInfoMaxWidthCount = max( GetOtherIconInfoByIndex(n)->m_strInfo.size(), m_usByteOtherInfoMaxWidthCount );
	}

	m_usWidth = m_nFontSize/2*max(m_usByteMaxWidthCount,m_usByteOtherInfoMaxWidthCount) + OFFSET_HEIGHT*2 + FRAME_SIZE*2;
	m_usHeight = (m_nFontSize+OFFSET_HEIGHT)*(m_ucIconInfoLine+m_ucIconOtherInfoLine) + OFFSET_HEIGHT + FRAME_SIZE*2;

}

void S_IconInfoBase::DisplayInfo_Icon( RECT &rcIconText, RECT &rcText, stIconInfoEx* pInfo, const int nFontSize, int &nIconLeftSize, int &nIconRightSize, int &nIconHeightIncrease )
{
	rcIconText = rcText;
	rcIconText.top += OFFSET_HEIGHT * 2;
	RECT rcSrc = {0,0,TILE_SIZE,TILE_SIZE};
	if (!pInfo->m_strImage.empty())
	{
		rcSrc.left = pInfo->m_usImageColumn * m_ucIconSize;
		rcSrc.right = rcSrc.left + m_ucIconSize;
		rcSrc.top = pInfo->m_usImageRow * m_ucIconSize;
		rcSrc.bottom = rcSrc.top + m_ucIconSize;
	}
	rcIconText.right = rcIconText.left + pInfo->m_usImageWidth * ControlObjectGetSCALE(NULL);
	rcIconText.bottom = rcIconText.top + pInfo->m_usImageHeight * ControlObjectGetSCALE(NULL);

    if( pInfo->m_usDestWidth > 0 && pInfo->m_usDestHeight > 0 )
    {
        rcIconText.left = rcIconText.right - pInfo->m_usDestWidth * ControlObjectGetSCALE( NULL );
        rcIconText.bottom = rcIconText.top + pInfo->m_usDestHeight * ControlObjectGetSCALE( NULL );
    }
	theControlPictureManager.BitBlt( &pInfo->m_nImageID,
		pInfo->m_strImage.c_str(),
		&rcIconText, &rcSrc, pInfo->m_col );		

	rcText.top += pInfo->m_usImageHeight * ControlObjectGetSCALE(NULL) - nFontSize;
	rcText.bottom += pInfo->m_usImageHeight * ControlObjectGetSCALE(NULL) - nFontSize;

	//if( !pInfo->m_bNewLine ) // ²»»»ÐÐ

	rcIconText.left += pInfo->m_usImageWidth * ControlObjectGetSCALE(NULL) + OFFSET_WIDTH;				
	rcIconText.right += pInfo->m_usImageWidth * ControlObjectGetSCALE(NULL) + OFFSET_WIDTH;

	nIconLeftSize = rcIconText.left;
	nIconRightSize = rcIconText.right;
	if( pInfo->m_ucRightRowCount )
	{
		nIconHeightIncrease = ( pInfo->m_usImageHeight / pInfo->m_ucRightRowCount ) * ControlObjectGetSCALE(NULL);// + OFFSET_HEIGHT;
		rcIconText.top -= nIconHeightIncrease;
		rcIconText.bottom = rcIconText.top;// + ( pInfo->m_nImageHeight / pInfo->m_nRightRowCount - nFontSize ) * ControlObjectGetSCALE(NULL);
	}			

	rcText.top += nFontSize + OFFSET_HEIGHT * 3;
	rcText.bottom += nFontSize + OFFSET_HEIGHT * 3;
}

void S_IconInfoBase::DisplayInfo_Image( RECT& rcRightText, stIconInfoEx* pInfo, RECT &rcText, const int nFontSize, RECT * prc )
{
	RECT rcSrc = {0,0,TILE_SIZE,TILE_SIZE};
	if( !pInfo->m_strImage.empty() )
	{
		rcSrc.left = pInfo->m_usSrcX;
		rcSrc.right = rcSrc.left + pInfo->m_usImageWidth;
		rcSrc.top = pInfo->m_usSrcY;
		rcSrc.bottom = rcSrc.top + pInfo->m_usImageHeight;
	}

	if( pInfo->m_eImageAlignMode == stIconInfoEx::eIIIA_Right )//显示在右面的图片
	{
		RECT rcImage = rcText;

        // 回退到上一行     modified by zhuomeng.hu		[11/30/2010]
        if( m_eLastLineType == ELINE_TYPE_ICON )
        {
            if( m_pLastPicInfo )
                rcImage.top -= OFFSET_HEIGHT + m_pLastPicInfo->m_usImageHeight * ControlObjectGetSCALE( NULL );
            else
                rcImage.top -= nFontSize + OFFSET_HEIGHT;
        }
        else
        {
            rcImage.top -= nFontSize + OFFSET_HEIGHT;
        }

		rcImage.right = prc->right - OFFSET_WIDTH * 3;
		rcImage.left = rcImage.right - pInfo->m_usImageWidth * ControlObjectGetSCALE(NULL);
		rcImage.bottom = rcImage.top + pInfo->m_usImageHeight * ControlObjectGetSCALE(NULL);
        if( pInfo->m_usDestWidth > 0 && pInfo->m_usDestHeight > 0 )
        {
            rcImage.left = rcImage.right - pInfo->m_usDestWidth * ControlObjectGetSCALE( NULL );
            rcImage.bottom = rcImage.top + pInfo->m_usDestHeight * ControlObjectGetSCALE( NULL );
        }
		// render
		theControlPictureManager.BitBlt( &pInfo->m_nImageID,
			pInfo->m_strImage.c_str(),
			&rcImage, &rcSrc, pInfo->m_col );

        m_eLastLineType = ELINE_TYPE_RIGHT_IMAGE;
	}
	else // 显示在左边的图片
	{				
		// 纠正rtext
		rcText.right = rcText.left + rcSrc.right - rcSrc.left;
		rcText.bottom = rcText.top + rcSrc.bottom - rcSrc.top;

        if( pInfo->m_usDestWidth > 0 && pInfo->m_usDestHeight > 0 )
        {
            rcText.right = rcText.left + pInfo->m_usDestWidth * ControlObjectGetSCALE( NULL );
            rcText.bottom = rcText.top + pInfo->m_usDestHeight * ControlObjectGetSCALE( NULL );
        }

		theControlPictureManager.BitBlt( &pInfo->m_nImageID,
			pInfo->m_strImage.c_str(),
			&rcText, &rcSrc, pInfo->m_col );

		// 左侧的图片才会在右侧显示文字
		rcRightText = rcText;
		rcRightText.left = rcText.right + OFFSET_WIDTH;
		rcRightText.right = prc->right;
		rcRightText.top = rcRightText.top + ( ( rcText.bottom - rcText.top ) * ControlObjectGetSCALE(NULL) / 2 )
            - ( ( nFontSize * ControlObjectGetSCALE(NULL) ) / 2 );
		rcRightText.bottom = rcRightText.top + nFontSize * ControlObjectGetSCALE(NULL);

		// 增量
        // modified by ZhuoMeng.Hu		[12/10/2010]
        if( pInfo->m_usDestHeight > 0 )
        {
            rcText.top += pInfo->m_usDestHeight + OFFSET_HEIGHT;
            rcText.bottom += pInfo->m_usDestHeight + OFFSET_HEIGHT;
        }
        else
        {
            rcText.top += pInfo->m_usImageHeight + OFFSET_HEIGHT;
            rcText.bottom += pInfo->m_usImageHeight + OFFSET_HEIGHT;
        }

        m_eLastLineType = ELINE_TYPE_LEFT_IMAGE;
	}
}

void S_IconInfoBase::DisplayInfo_Gif( RECT& rcRightText, RECT &rcText, stIconInfoEx * pInfo )
{
	long lRight = rcText.right;

	rcText.right = rcText.left + pInfo->m_usImageWidth * ControlObjectGetSCALE(NULL);
	rcText.bottom = rcText.top + pInfo->m_usImageHeight * ControlObjectGetSCALE(NULL);

    if( pInfo->m_usDestWidth > 0 && pInfo->m_usDestHeight > 0 )
    {
        rcText.left = rcText.right - pInfo->m_usDestWidth * ControlObjectGetSCALE( NULL );
        rcText.bottom = rcText.top + pInfo->m_usDestHeight * ControlObjectGetSCALE( NULL );
    }
	ExpressionManager::GetInstance().DrawExpression( pInfo->m_strImage, rcText );

	//设置right text的rect
	rcRightText = rcText;
	rcRightText.left = rcText.right + OFFSET_WIDTH;
	rcRightText.right = lRight;

	rcText.top += pInfo->m_usImageHeight * ControlObjectGetSCALE(NULL) + OFFSET_HEIGHT;
	rcText.bottom += pInfo->m_usImageHeight * ControlObjectGetSCALE(NULL) + OFFSET_HEIGHT;
}

void S_IconInfoBase::DisplayInfo_Line( RECT& rcText, stIconInfoEx* pInfo, RECT* prc )
{
    RECT rcSrc;
    if( !pInfo->m_strImage.empty() )
    {
        rcSrc.left = pInfo->m_usSrcX;
        rcSrc.right = rcSrc.left + pInfo->m_usImageWidth;
        rcSrc.top = pInfo->m_usSrcY;
        rcSrc.bottom = rcSrc.top + pInfo->m_usImageHeight;
    }

    RECT rcLine = rcText;
    rcLine.left = prc->left + FRAME_SIZE;
    int nHeight = pInfo->m_usDestHeight > 0 ? pInfo->m_usDestHeight : pInfo->m_usImageHeight;
    rcLine.bottom = rcLine.top + nHeight;
    rcLine.right = prc->right - FRAME_SIZE;

    theControlPictureManager.BitBlt( &pInfo->m_nImageID, pInfo->m_strImage.c_str(), &rcLine, &rcSrc, pInfo->m_col );

    rcText.top += nHeight + OFFSET_HEIGHT;
    rcText.bottom += nHeight + OFFSET_HEIGHT;
}

////////////////////////////////////////////////////////////////////////////
CIconInfoMouseTip theIconInfoMouseTip;
CIconInfoMouseTip::CIconInfoMouseTip(void)
{
	m_pIconInfo = NULL;
	m_pCompareIconInfo = NULL;
	m_nInfoX = m_nInfoY = 0;
	m_nInfoFontIndex = 0;
	m_nInfoFontSize = 0;
	m_colInfo = RGB(0,0,0);
	m_bIsShop = false;
	m_bShopOpen = false;
	m_bShowAllInfo = true;
	m_dwBeginShowTime = 0;
	m_nDelayTime = 0;
	m_pLastIconInfo = 0;
	m_bRedraw = true;
	m_pSecondCompareIconInfo = NULL;
}

void CIconInfoMouseTip::Clear()
{
	m_pIconInfo = NULL;	
	m_pCompareIconInfo = NULL;
	m_pSecondCompareIconInfo = NULL;
	m_bRedraw = true;
}

void CIconInfoMouseTip::SetSpareTimeToTip( S_IconInfoBase* pTip )
{	
	DWORD dwSpareTime =pTip->GetSpareTime();
	if( pTip && pTip->SpareTime() == MAX_SPARETIME )//约定，最大时间的时候为无限时间N/A
	{
		char szResult[256] = {0};	
		pTip->ClearOtherInfo();		
		sprintf_s( szResult, 256, "%s%s%s", "<#ffe3ffff=", "剩余时间：", "N/A" );
		pTip->SetOtherInfo( szResult, DT_LEFT );
	}
	else if( pTip && dwSpareTime > 0 && dwSpareTime < MAX_SPARETIME )
	{
		pTip->ClearOtherInfo();
		char szBufferT[256] = {0};		
		char szBufferS[256] = {0};
		char szBufferF[256] = {0};
		char szBufferM[256] = {0};
		char szResult[256] = {0};		
		int nSecond = dwSpareTime / 1000;		
		int nDay = nSecond / ( 24 * 60 * 60 ) ;	
		int nLeft = nSecond % ( 24 * 60 * 60 );
		int nHour = nLeft / ( 60 * 60 );
		nLeft = nLeft % ( 60 * 60 );
		int nMinute = nLeft / 60;
		nLeft = nLeft % 60;

		if (nDay > 0)		
			sprintf_s( szBufferT, 256, "%d天", nDay );			

		if (nHour > 0)		
			sprintf_s( szBufferS, 256, "%s%d时", szBufferT, nHour );			

		if ( nMinute != 0 )		
			sprintf_s( szBufferF, 256, "%s%d分", szBufferS, nMinute );			

		//if( ( nSecond + 1 ) != 0 )				
		sprintf_s( szBufferM, 256, "%s%d秒", szBufferF, nLeft + 1 );

		// 颜色
		if( nSecond <= 60 )
			sprintf_s( szResult, 256, "%s%s%s", "<#ffff0000=", "剩余时间：", szBufferM );			
		else
			sprintf_s( szResult, 256, "%s%s%s", "<#ffe3ffff=", "剩余时间：", szBufferM );
		pTip->SetOtherInfo( szResult, DT_LEFT );
	}
}
void CIconInfoMouseTip::Render()
{	
	// 延时显示
	if( HQ_TimeGetTime() - m_dwBeginShowTime < m_nDelayTime )
		return;	

	RECT rc;
	if ( m_pIconInfo )
	{
		if (ms_pFunRetrieveSpareTimeString)
		{
			ms_pFunRetrieveSpareTimeString( m_pIconInfo );
		}
		int nHeight = m_pIconInfo->m_usHeight;
		if( m_pCompareIconInfo )
		{
			m_pCompareIconInfo->CaculateWidthHeight( m_nInfoFontSize, m_nInfoFontIndex );
			if( m_pCompareIconInfo->m_usHeight > nHeight )
				nHeight = m_pCompareIconInfo->m_usHeight;
			if( m_nInfoY + nHeight + 15 > SCREEN_HEIGHT )//超
			{
				m_nInfoY = SCREEN_HEIGHT - nHeight - 15;
			}
		}		
		static S_IconInfoBase* s_pLastInfo = 0;
		static int s_nLastX = 0;
		static int s_nLastY = 0;
		static int s_nLastFontIndex = -1;
		static int s_nLastFontSize = 0;		

		if( m_pIconInfo != s_pLastInfo ||
			s_nLastX != m_nInfoX ||
			s_nLastY != m_nInfoY ||
			s_nLastFontIndex != m_nInfoFontIndex ||
			s_nLastFontSize != m_nInfoFontSize )
			m_bRedraw = true;

		rc = m_pIconInfo->DisplayInfo( m_nInfoX, m_nInfoY, m_bIsShop,
			m_nInfoFontIndex, m_nInfoFontSize, m_colInfo,
			true, m_bShowAllInfo );		

		// store last values
		s_pLastInfo = m_pIconInfo;
		s_nLastX = m_nInfoX;
		s_nLastY = m_nInfoY;
		s_nLastFontIndex = m_nInfoFontIndex;
		s_nLastFontSize = m_nInfoFontSize;
	}
	if ( m_pCompareIconInfo )
	{
		int nX = m_nInfoX;
		int nY = rc.top;//m_nInfoY; // y值需修正，使左右框对齐
		//nY -= m_nInfoFontSize + OFFSET_HEIGHT;
		//重新计算宽度
		//m_pCompareIconInfo->CaculateWidthHeight( m_nInfoFontSize );
		//校正x,y值
		if( rc.left - m_pCompareIconInfo->m_usWidth  < 0 )//左边出界，显示在右侧
			nX += rc.right - rc.left ;
		//nX += rc.right - rc.left + 2 * OFFSET_WIDTH;
		else//显示在左侧
		{
			// 			int nWidth = ( m_pCompareIconInfo->m_nWidth - OFFSET_HEIGHT*2 + FRAME_SIZE*2 ) * ControlObjectGetREAL_SCALE(NULL) * 2.f + OFFSET_HEIGHT*2 + FRAME_SIZE*2;
			// 			nX = rc.left - nWidth - 2 * OFFSET_WIDTH ;
			//nX = rc.left - m_pCompareIconInfo->m_nWidth  - m_nInfoFontSize - 3;
			nX = rc.left - m_pCompareIconInfo->m_usWidth ;
		}

		RECT tRc;
		tRc = m_pCompareIconInfo->DisplayInfo( nX, nY, m_bIsShop,
			m_nInfoFontIndex, m_nInfoFontSize, m_colInfo,
			true, m_bShowAllInfo );	

		if(m_pSecondCompareIconInfo)
		{
			int nPosX = 0,nPosY = 0;
			nPosY = tRc.top;

			m_pSecondCompareIconInfo->CaculateWidthHeight( m_nInfoFontSize, m_nInfoFontIndex );
			if(tRc.left < rc.left)
			{
				if(tRc.left - m_pSecondCompareIconInfo->m_usWidth < 0)  //左边出界，显示在右边
					nPosX = m_nInfoX + rc.right - rc.left;
				else //显示左边
					nPosX = tRc.left - m_pSecondCompareIconInfo->m_usWidth;
			}
			else
			{
				if(rc.left - m_pSecondCompareIconInfo->m_usWidth < 0)
					nPosX = m_nInfoX + rc.right - rc.left + tRc.right - tRc.left;
				else
					nPosX = rc.left - m_pSecondCompareIconInfo->m_usWidth;
			}

			m_pSecondCompareIconInfo->DisplayInfo(nPosX,nPosY,m_bIsShop,m_nInfoFontIndex,m_nInfoFontSize,m_colInfo,true,m_bShowAllInfo);
		}
	}

	m_bRedraw = false;
}

void CIconInfoMouseTip::SetDisplayInfo( S_IconInfoBase* pIconInfo, 
									   const int nX, const int nY, 
									   const bool bShowPrice, 
									   const int nFontIndex, 
									   const int nFontSize, 
									   const COLORREF col, 
									   const bool bShowAllInfo,
									   S_IconInfoBase* pCompareIconInfo /* = 0  */, 
									   DWORD dwBeginShowTime /* = 0 */, 
									   int nDelayTime /* = 0 */,
									   bool bForce /*= false*/,
									   S_IconInfoBase* pSecondCompareIconInfo /*= NULL*/
									   )
{
	
	if( m_pLastIconInfo != pIconInfo || bForce )
		m_dwBeginShowTime = dwBeginShowTime;	

	m_pIconInfo = pIconInfo;
	m_pLastIconInfo = m_pIconInfo;
	m_pCompareIconInfo = pCompareIconInfo;
	m_nInfoX = nX + g_nMouseOffsetWidth;
	m_nInfoY = nY + g_nMouseOffsetHeight;
	m_bIsShop = bShowPrice;
	m_nInfoFontIndex = nFontIndex;
	m_nInfoFontSize = nFontSize;
	m_colInfo = col;
	m_bShowAllInfo = bShowAllInfo;
	m_nDelayTime = nDelayTime;
	m_pSecondCompareIconInfo = pSecondCompareIconInfo;
}

//

// void S_IconInfoHero::ShowRand( void* pItemDetail, INT nType, void* pComItemDetail )
// {
// 	if( nType != CItemDetail::ITEMTYPE_WEAPON )
// 		return;
// 
// 	char szTemp [256] = {0};
// 
// 	int nAddPhysicAtt = 0;
// 	int nAddMagicAtt = 0;
// 
// 	int nAddFireAtk = 0;
// 	int nAddFrostAtk = 0;
// 	int nAddThunderAtk = 0;
// 	int nAddPoisonAtk = 0;
// 
// 	int nAddFrostDam = 0;
// 	int nAddFireDam = 0;
// 	int nAddThunderDam = 0;
// 	int nAddPoisonDam = 0;
// 
// 	int iExact = 0;
// 	int iCriticalAttackRate = 0;
// 	float fCriticalAttackMul =0;
// 	int nCriticalAttackMul =0;
// 	int iAttSpeed =0;
// 
// 	int nAddStr =0;
// 	int nAddAgi = 0;
// 	int nAddSta = 0;
// 	int nAddMagic = 0;
// 	int nAddApp = 0;
// 	int nAddLuck = 0;
// 	if ( pItemDetail || pComItemDetail )
// 	{
// 		for (int nloop = 0; nloop < SCharItem::e_Rand;nloop++)
// 		{
// 			CItemDetail::SWeaponRand *pItemWeaponRand;
// 			pItemWeaponRand	= GettheItemDetail().GetWeaponRandByID(m_stItem.equipdata.usRand[nloop]);
// 			if( pComItemDetail )
// 			{
// 				pItemWeaponRand	= GettheItemDetail().GetWeaponRandByID(m_stCompareItem.equipdata.usRand[nloop]);
// 			}
// 			if (!pItemWeaponRand)
// 			{
// 				continue;
// 			}
// 			nAddFrostAtk += pItemWeaponRand->sAtt[ePlayAtt_Ice];
// 			nAddFireAtk += pItemWeaponRand->sAtt[ePlayAtt_Fire];
// 			nAddThunderAtk += pItemWeaponRand->sAtt[ePlayAtt_Thunder];
// 			nAddPoisonAtk += pItemWeaponRand->sAtt[ePlayAtt_Wind];
// 
// 			nAddPhysicAtt += pItemWeaponRand->sAtt[ePlayAtt_Physics];
// 			nAddMagicAtt += pItemWeaponRand->sAtt[ePlayAtt_Magic];
// 
// 			nAddFrostDam += pItemWeaponRand->sDam[ePlayAtt_Ice];
// 			nAddFireDam += pItemWeaponRand->sDam[ePlayAtt_Fire];
// 			nAddThunderDam += pItemWeaponRand->sDam[ePlayAtt_Thunder];
// 			nAddPoisonDam += pItemWeaponRand->sDam[ePlayAtt_Wind];
// 
// 			iExact += pItemWeaponRand->sExact;
// 			iCriticalAttackRate += pItemWeaponRand->sCritical;
// 			fCriticalAttackMul += pItemWeaponRand->fCriticalmultiple;
// 			iAttSpeed += pItemWeaponRand->sChangeAttSpeed;
// 
// 			nAddStr += pItemWeaponRand->stWeaponAddBaseAttr[BA_LiLiang];
// 			nAddAgi += pItemWeaponRand->stWeaponAddBaseAttr[BA_MinJie];
// 			nAddSta += pItemWeaponRand->stWeaponAddBaseAttr[BA_TiZhi];
// 			nAddMagic += pItemWeaponRand->stWeaponAddBaseAttr[BA_JinGu];
// 			nAddApp += pItemWeaponRand->stWeaponAddBaseAttr[BA_ShuFa];
// 			nAddLuck += pItemWeaponRand->stWeaponAddBaseAttr[BATTR_Luck];
// 		}
// 
// 		nCriticalAttackMul = fCriticalAttackMul*100;
// 		
// 		ITEM_SHOW_INT(nAddPhysicAtt ,theXmlString.GetString(eUI_ePlayAtt_Physics),	BLUE_COLOR );
// 		ITEM_SHOW_INT(nAddMagicAtt,theXmlString.GetString(eUI_ePlayAtt_Magic),	BLUE_COLOR );
// 
// 		
// 		ITEM_SHOW_INT(nAddFrostAtk,theXmlString.GetString(eUI_stPlayAtt_Frost),	BLUE_COLOR );
// 		ITEM_SHOW_INT(nAddFireAtk ,theXmlString.GetString(eUI_stPlayAtt_Blaze),	BLUE_COLOR );
// 		ITEM_SHOW_INT(nAddThunderAtk ,theXmlString.GetString(eUI_stPlayAtt_Thunder),	BLUE_COLOR );
// 		ITEM_SHOW_INT(nAddPoisonAtk ,theXmlString.GetString(eUI_stPlayAtt_Poison),	BLUE_COLOR );
// 
// 		ITEM_SHOW_INT(nAddFrostDam ,theXmlString.GetString(eUI_ExHurt_Ice),	BLUE_COLOR );
// 		ITEM_SHOW_INT(nAddFireDam,theXmlString.GetString(eUI_ExHurt_Fire),	BLUE_COLOR );
// 		ITEM_SHOW_INT(nAddThunderDam ,theXmlString.GetString(eUI_ExHurt_Thunder),	BLUE_COLOR );
// 		ITEM_SHOW_INT(nAddPoisonDam ,theXmlString.GetString(eUI_ExHurt_Poison),	BLUE_COLOR );
// 
// 		ITEM_SHOW_INT(iExact ,theXmlString.GetString(eUI_sExact),	BLUE_COLOR );
// 		ITEM_SHOW_INT_PER(iCriticalAttackRate ,theXmlString.GetString(eUI_sCritical),	BLUE_COLOR );
// 		ITEM_SHOW_INT_PER(nCriticalAttackMul,theXmlString.GetString(eUI_fCriticalmultiple),BLUE_COLOR );
// 
// 		float fAttSpeed = (float)iAttSpeed/1000.0f;
// 		if( fAttSpeed > 0 )
// 		{
// 			fAttSpeed = -fAttSpeed;
// 			sprintf( szTemp,
// 				"%s:%0.1f %s",theXmlString.GetString(eUI_stAtkSpeedAdd),
// 				fAttSpeed,theXmlString.GetString(eSystemName_Second));
// 			SHOW_STRING( szTemp, BLUE_COLOR );
// 		}
// 
// 		ITEM_SHOW_INT(nAddStr,			theXmlString.GetString(eText_stStrengthReq), BLUE_COLOR );	//力量
// 		ITEM_SHOW_INT(nAddSta,		theXmlString.GetString(eText_stConstitutionReq), BLUE_COLOR );	//体质
// 		ITEM_SHOW_INT(nAddAgi,			theXmlString.GetString(eText_stAgilityReq), BLUE_COLOR );	//敏捷
// 		ITEM_SHOW_INT(nAddApp,		theXmlString.GetString(eText_stIntelligenceReq), BLUE_COLOR );	//智力
// 		ITEM_SHOW_INT(nAddMagic,				theXmlString.GetString(eText_stMagicReq), BLUE_COLOR );	//魔法
// 		ITEM_SHOW_INT(nAddLuck,				theXmlString.GetString(eText_stCharmReq), BLUE_COLOR );	//魅力
// 	}	
//}

//text_tip_info
S_TextTipInfo::S_TextTipInfo()
{
	guardfunc;
	Clear();
	unguard;
}
void S_TextTipInfo::Clear()
{
	guardfunc;
	S_IconInfoBase::Clear();
	m_nCount = 1;
	m_nCost = 0;
	m_nMaxCount = -1;
	m_bLocked = false;
	m_dwSpareTime = 0;
	m_bNextLvl = false;
	m_nId = 0;
	m_bItemLocked = 0;
	unguard;
}
void S_TextTipInfo::SetInfo( IN const char* szInfo, IN DWORD dwAlign /*= DT_CENTER | DT_VCENTER*/ )
{
	assert( szInfo );
	m_ucIconInfoLine = 0;
	m_stInfo.clear();
	m_usByteMaxWidthCount = 0;
	//
	char szTemp[256];
	memset( szTemp, 0, sizeof(szTemp) );
	int nLength = 0;
	int nInfoLength = strlen(szInfo);
	DWORD dwColor = 0;
	for ( UINT n=0; n<nInfoLength; n++ )
	{
		if ( szInfo[n] != 0 && (szInfo[n] == '\n') )
		{
			stIconInfo stInfo;
			stInfo.m_strInfo = szTemp;
			stInfo.m_col = dwColor;
			stInfo.m_dwTextAlign = dwAlign;
			memset( szTemp, 0, sizeof(szTemp) );
			nLength = 0;
			dwColor = 0;
			m_stInfo.push_back( stInfo );
			m_ucIconInfoLine++;
		}
		else if( szInfo[n] == '\\' && szInfo[n+1] == 'n' )
		{
			stIconInfo stInfo;
			stInfo.m_strInfo = szTemp;
			stInfo.m_col = dwColor;
			stInfo.m_dwTextAlign = dwAlign;
			memset( szTemp, 0, sizeof(szTemp) );
			nLength = 0;
			dwColor = 0;
			m_stInfo.push_back( stInfo );
			m_ucIconInfoLine ++;
			n++;
		}
		else if ( n < nInfoLength-10 &&
			(szInfo[n] == '<' || szInfo[n] == '{') && szInfo[n+1] == '#' )
		{
			char szColor[10];
			memset( szColor, 0, sizeof(szColor) );
			memcpy( szColor, &szInfo[n+2], 8 );
			sscanf( szColor, "%x", &dwColor );
			n += 10;
		}
		else
		{
			szTemp[nLength++] = szInfo[n];
			if ( n == nInfoLength-1 && strlen(szTemp) > 0 )
			{
				stIconInfo stInfo;
				stInfo.m_strInfo = szTemp;
				stInfo.m_col = dwColor;
				stInfo.m_dwTextAlign = dwAlign;
				m_stInfo.push_back( stInfo );
				m_ucIconInfoLine++;
			}
		}
		assert( m_ucIconInfoLine < MAX_ICON_INFO_EX_LINE_COUNT );
	}
	for ( int n=0; n< m_stInfo.size(); n++ )
	{
		int nSize = m_stInfo[n].m_strInfo.size();
// 		if( m_stInfo[n].m_bRightText )
// 			nSize += TIP_ICON_SIZE / m_nFontSize * 2;
		m_usByteMaxWidthCount = max( nSize, m_usByteMaxWidthCount );
	}

	m_usWidth = m_nFontSize/2*max(m_usByteMaxWidthCount,m_usByteOtherInfoMaxWidthCount) + OFFSET_HEIGHT*2 + FRAME_SIZE*2;
	m_usHeight = (m_nFontSize+OFFSET_HEIGHT)*(m_ucIconInfoLine+m_ucIconOtherInfoLine) + OFFSET_HEIGHT + FRAME_SIZE*2;
}


IconManager::IconManager()
{

}

bool IconManager::Load(const std::string& filename)
{
	MeXmlDocument xmlDoc;
	if (!xmlDoc.LoadFile(filename.c_str()))
		return false;

	MeXmlElement* pRoot = xmlDoc.FirstChildElement("Project")->FirstChildElement("Icons");
	if (!pRoot)
		return false;

	MeXmlElement* pIcon = pRoot->FirstChildElement("Icon");
	while (pIcon)
	{
		IconInfo iconSet;
		pIcon->QueryIntAttribute("ItemId", &iconSet.itemId);
		pIcon->QueryIntAttribute("Size", &iconSet.iconSize);
		pIcon->QueryIntAttribute("Row", &iconSet.row);
		pIcon->QueryIntAttribute("Column", &iconSet.column);
		const char* value = pIcon->Attribute("Image");
		if (value)
			iconSet.image = value;

		if (iconSet.itemId != 0)
			m_iconSets.insert(std::make_pair(iconSet.itemId, iconSet));

        // 取消预加载   deleted by zhuomeng.hu		[10/12/2010]
		//if (!m_ImageFinder.GetDstByName(value))
		//{
		//	char filename[256];
		//	int nPicId = -1;
		//	sprintf_s(filename,sizeof(filename)/sizeof(char) - 1, "%s/Data/%s", GetRootPath(), value);
		//	ControlPictureManager::S_Pic* pPic = theControlPictureManager.RegisterTexture(&nPicId, filename);
		//	m_ImageFinder.Register(value,pPic);
		//}
		pIcon = pIcon->NextSiblingElement("Icon");
	}


	return true;
}
