#include "StdAfx.h"
#include "basecontrol.h"
#include <assert.h>
#include "PicMgr.h"
#include "PropertyDlg.h"
#include "UIObjectDlg.h"

CBaseControl::CBaseControl()
{
	m_nType = Type_Normal;

	m_strID = "ID_";
	m_strCaption = "";
	m_Tips = "";
	m_stFont.SetFont( "宋体", RGB(255,255,255) , 12 );
	m_comboAlign.SetData( ALIGN_MODE_LEFT_TOP, ALIGN_MODE_CONTROL_COMBO );
	m_nOffsetX = 0;
	m_nOffsetY = 0;
	m_nWidth = 100;
	m_nHeight = 100;
	m_comboLeft.SetData( DRAW_MODE_NORMAL, DRAW_MODE_COMBO );
	m_comboTop.SetData( DRAW_MODE_NORMAL, DRAW_MODE_COMBO );
	m_comboRight.SetData( DRAW_MODE_NORMAL, DRAW_MODE_COMBO );
	m_comboBottom.SetData( DRAW_MODE_NORMAL, DRAW_MODE_COMBO );
	m_comboMiddle.SetData( DRAW_MODE_NORMAL, DRAW_MODE_COMBO );

	m_ProItem[Item_Comments_Normal].SetItem( PIT_COMMENTS, "<基本属性>", NULL );
	m_ProItem[Item_ID].SetItem( PIT_EDIT, "ID", &m_strID );
	m_ProItem[Item_BackPic].SetItem( PIT_DIALOG, "背景图片", &m_PicBack );
	m_ProItem[ITEM_DisablePic].SetItem( PIT_DIALOG, "Disable背景", &m_PicDisable );
	m_ProItem[Item_Caption].SetItem( PIT_EDIT, "Caption", &m_strCaption );
	m_ProItem[Item_Tips].SetItem( PIT_EDIT, "Tips", &m_Tips );
	m_ProItem[Item_Font].SetItem( PIT_FONT, "字体", &m_stFont);
	m_ProItem[Item_Comments_Size].SetItem( PIT_COMMENTS, "<坐标/大小>", NULL );
	m_ProItem[Item_Align].SetItem( PIT_COMBO, "对齐方式", &m_comboAlign );
	m_ProItem[Item_X].SetItem( PIT_NUM, "OffsetX", &m_nOffsetX );
	m_ProItem[Item_Y].SetItem( PIT_NUM, "OffsetY", &m_nOffsetY );
	m_ProItem[Item_Width].SetItem( PIT_NUM, "Width", &m_nWidth );
	m_ProItem[Item_Height].SetItem( PIT_NUM, "Height", &m_nHeight );
	m_ProItem[Item_Comments_DrawMode].SetItem( PIT_COMMENTS, "<绘制模式>", NULL );
	m_ProItem[Item_DrawModeLeft].SetItem( PIT_COMBO, "Left", &m_comboLeft );
	m_ProItem[Item_DrawModeTop].SetItem( PIT_COMBO, "Top", &m_comboTop );
	m_ProItem[Item_DrawModeRight].SetItem( PIT_COMBO, "Right", &m_comboRight );
	m_ProItem[Item_DrawModeBottom].SetItem( PIT_COMBO, "Bottom", &m_comboBottom );
	m_ProItem[Item_DrawModeMiddle].SetItem( PIT_COMBO, "Middle", &m_comboMiddle );
}

CBaseControl::~CBaseControl()
{
	Release();
}

void CBaseControl::AddToPropertyDlg()
{
	thePropertyDlg.m_pstControl = this;
//	thePropertyDlg.Clear();
	for( int n=0; n<Item_Max; n++ )
	{
		thePropertyDlg.AddItem( &m_ProItem[n] );
	}
}

void CBaseControl::Release()
{
	if ( thePropertyDlg.m_pstControl == this )
	{
		thePropertyDlg.Clear(); 
	}
}

void CBaseControl::AddToUIObjectDlg()
{
	theUIObjectDlg.UpdateDialogName();
	theUIObjectDlg.AddPictuer( m_PicBack.GetCurSelPicName() );
}

bool CBaseControl::SetData( const S_BaseData* /*[In]*/pData )
{
	assert( pData );
	m_nType = pData->m_nType;
	m_strID = pData->m_szID;
	m_PicBack.SetPicStruct( &pData->m_stBackPic );
	m_strCaption = pData->m_szCaption;
	m_stFont.m_strName = pData->m_szFont;
	m_stFont.m_nSize = pData->m_nFontSize;
	m_Tips = pData->m_szTips;
	m_stFont.m_colColor = pData->m_colFont &  0x00ffffff;
	m_stFont.m_colColor = RGB(GetBValue(m_stFont.m_colColor), GetGValue(m_stFont.m_colColor), GetRValue(m_stFont.m_colColor));
	m_comboAlign.m_curValue = GetAlignMode( pData->m_nAlignMode );
	m_nOffsetX = pData->m_rcRealSize.left;
	m_nOffsetY = pData->m_rcRealSize.top;
	m_nWidth = pData->m_rcRealSize.right - pData->m_rcRealSize.left;
	m_nHeight = pData->m_rcRealSize.bottom - pData->m_rcRealSize.top;
	m_comboLeft.m_curValue = GetDrawMode( pData->m_nDrawMode[S_BaseData::Mode_Left] );
	m_comboTop.m_curValue = GetDrawMode( pData->m_nDrawMode[S_BaseData::Mode_Top] );
	m_comboRight.m_curValue = GetDrawMode( pData->m_nDrawMode[S_BaseData::Mode_Right] );
	m_comboBottom.m_curValue = GetDrawMode( pData->m_nDrawMode[S_BaseData::Mode_Bottom] );
	m_comboMiddle.m_curValue = GetDrawMode( pData->m_nDrawMode[S_BaseData::Mode_Middle] );
	return true;
}

bool CBaseControl::GetData( S_BaseData* /*[Out]*/pData )
{
	assert( pData );
	pData->m_nType = m_nType;
	strcpy( pData->m_szID, m_strID );
	pData->m_stBackPic.SetPicStruct( m_PicBack.GetCurSelPicName(),
									&m_PicBack.GetFrameRect(),
									&m_PicBack.GetClientRect() );
	pData->m_stDisablePic.SetPicStruct( m_PicDisable.GetCurSelPicName(),
									&m_PicDisable.GetFrameRect(),
									&m_PicDisable.GetClientRect() );
	strcpy( pData->m_szCaption, m_strCaption );
	strcpy( pData->m_szFont, m_stFont.m_strName );
	strcpy( pData->m_szTips, m_Tips );
	pData->m_nFontSize = m_stFont.m_nSize;
	pData->m_colFont = /*m_stFont.m_colColor;*/RGB(GetBValue(m_stFont.m_colColor), GetGValue(m_stFont.m_colColor), GetRValue(m_stFont.m_colColor));
	pData->m_nAlignMode = GetAlignMode( &m_comboAlign );
	pData->m_rcRealSize.left = m_nOffsetX;
	pData->m_rcRealSize.top = m_nOffsetY;
	pData->m_rcRealSize.right = pData->m_rcRealSize.left + m_nWidth;
	pData->m_rcRealSize.bottom = pData->m_rcRealSize.top + m_nHeight;
	pData->m_nDrawMode[S_BaseData::Mode_Left] = GetDrawMode( &m_comboLeft );
	pData->m_nDrawMode[S_BaseData::Mode_Top] = GetDrawMode( &m_comboTop );
	pData->m_nDrawMode[S_BaseData::Mode_Right] = GetDrawMode( &m_comboRight );
	pData->m_nDrawMode[S_BaseData::Mode_Bottom] = GetDrawMode( &m_comboBottom );
	pData->m_nDrawMode[S_BaseData::Mode_Middle] = GetDrawMode( &m_comboMiddle );

	return true;
}

int CBaseControl::GetDrawMode( S_Combo* pCombo )
{
	assert( pCombo );
	if ( pCombo->m_curValue == DRAW_MODE_NORMAL )
	{
		return DrawModeNormal;
	}
	else if ( pCombo->m_curValue == DRAW_MODE_TILE )
	{
		return DrawModeTile;
	}
	else if ( pCombo->m_curValue == DRAW_MODE_STRECTCH)
	{
		return DrawModeStrectch;
	}
	else
	{
		assert( false );
		return DrawModeNormal;
	}
}

CString CBaseControl::GetDrawMode( int nMode )
{
	switch( nMode )
	{
	case DrawModeNormal:
		return DRAW_MODE_NORMAL;
		break;
	case DrawModeTile:
		return DRAW_MODE_TILE;
		break;
	case DrawModeStrectch:
		return DRAW_MODE_STRECTCH;
		break;
	default:
		assert( false );
		return DRAW_MODE_NORMAL;
	}
}

int CBaseControl::GetAlignMode( S_Combo* pCombo )
{
	assert( pCombo );
	if ( pCombo->m_curValue == ALIGN_MODE_LEFT_TOP )
	{
		return AlignMode_LeftTop;
	}
	else if ( pCombo->m_curValue == ALIGN_MODE_RIGHT_TOP )
	{
		return AlignMode_RightTop;
	}
	else if ( pCombo->m_curValue == ALIGN_MODE_LEFT_BOTTOM )
	{
		return AlignMode_LeftBottom;
	}
	else if ( pCombo->m_curValue == ALIGN_MODE_RIGHT_BOTTOM )
	{
		return AlignMode_RightBottom;
	}
	else if ( pCombo->m_curValue == ALIGN_MODE_MIDDLE )
	{
		return AlignMode_Middle;
	}
	else if ( pCombo->m_curValue == ALIGN_MODE_LEFE )
	{
		return AlignMode_Left;
	}
	else if ( pCombo->m_curValue == ALIGN_MODE_TOP )
	{
		return AlignMode_Top;
	}
	else if ( pCombo->m_curValue == ALIGN_MODE_RIGHT )
	{
		return AlignMode_Right;
	}
	else if ( pCombo->m_curValue == ALIGN_MODE_BOTTOM )
	{
		return AlignMode_Bottom;
	}
	else if ( pCombo->m_curValue == ALIGN_MODE_LEFT_MIDDLE )
	{
		return AlignMode_LeftMiddle;
	}
	else if ( pCombo->m_curValue == ALIGN_MODE_TOP_MIDDLE )
	{
		return AlignMode_TopMiddle;
	}
	else if ( pCombo->m_curValue == ALIGN_MODE_RIGHT_MIDDLE )
	{
		return AlignMode_RightMiddle;
	}
	else if ( pCombo->m_curValue == ALIGN_MODE_BOTTOM_MIDDLE )
	{
		return AlignMode_BottomMiddle;
	}
	else
	{
		assert( false );
		return AlignMode_LeftTop;
	}
}

CString CBaseControl::GetAlignMode( int nMode )
{
	switch( nMode )
	{
	case AlignMode_LeftTop:
		return ALIGN_MODE_LEFT_TOP;
		break;
	case AlignMode_RightTop:
		return ALIGN_MODE_RIGHT_TOP;
		break;
	case AlignMode_LeftBottom:
		return ALIGN_MODE_LEFT_BOTTOM;
		break;
	case AlignMode_RightBottom:
		return ALIGN_MODE_RIGHT_BOTTOM;
		break;
	case AlignMode_Middle:
		return ALIGN_MODE_MIDDLE;
		break;
	case AlignMode_LeftMiddle:
		return ALIGN_MODE_LEFT_MIDDLE;
		break;
	case AlignMode_TopMiddle:
		return ALIGN_MODE_TOP_MIDDLE;
		break;
	case AlignMode_RightMiddle:
		return ALIGN_MODE_RIGHT_MIDDLE;
		break;
	case AlignMode_BottomMiddle:
		return ALIGN_MODE_BOTTOM_MIDDLE;
		break;
	case AlignMode_Left:
		return ALIGN_MODE_LEFE;
		break;
	case AlignMode_Top:
		return ALIGN_MODE_TOP;
		break;
	case AlignMode_Right:
		return ALIGN_MODE_RIGHT;
		break;
	case AlignMode_Bottom:
		return ALIGN_MODE_BOTTOM;
		break;
	default:
		assert( false );
		return ALIGN_MODE_LEFT_TOP;
	}
}

bool CBaseControl::MouseMove( const POINT point, const RECT* pFatherRc )
{
	m_strPicName = m_PicBack.GetCurSelPicName();
	m_rcDrawFrame = m_PicBack.GetFrameRect();
	m_rcDrawClient = m_PicBack.GetClientRect();
	return false;
}

void CBaseControl::Render( CDC* pDC, const RECT* pFatherRc )
{
	assert( pDC );
	assert( pFatherRc );

	CDC *pPicDC = NULL;
	int nRealX = 0;
	int nRealY = 0;
	GetPos( &nRealX, &nRealY, pFatherRc );

	if ( m_strPicName.IsEmpty() )
	{
		m_strPicName = m_PicBack.GetCurSelPicName();
		m_rcDrawFrame = m_PicBack.GetFrameRect();
		m_rcDrawClient = m_PicBack.GetClientRect();
	}

	if ( !m_strPicName.IsEmpty() )
	{
		pPicDC = thePicMgr.GetDC( m_strPicName, pDC );

		int	nLeftW = m_rcDrawClient.left - m_rcDrawFrame.left;
		int	nLeftH = m_rcDrawClient.bottom - m_rcDrawClient.top;
		int nTopW = m_rcDrawClient.right - m_rcDrawClient.left;
		int nTopH = m_rcDrawClient.top - m_rcDrawFrame.top;
		int nRightW = m_rcDrawFrame.right - m_rcDrawClient.right;
		int nRightH = m_rcDrawClient.bottom - m_rcDrawClient.top;
		int nBottomW = m_rcDrawClient.right - m_rcDrawClient.left;
		int nBottomH = m_rcDrawFrame.bottom - m_rcDrawClient.bottom;
		int nLeftTopW = m_rcDrawClient.left - m_rcDrawFrame.left;
		int nLeftTopH = m_rcDrawClient.top - m_rcDrawFrame.top;
		int nRightTopW = m_rcDrawFrame.right - m_rcDrawClient.right;
		int nRightTopH = m_rcDrawClient.top - m_rcDrawFrame.top;
		int nLeftBottomW = m_rcDrawClient.left - m_rcDrawFrame.left;
		int nLeftBottomH = m_rcDrawFrame.bottom - m_rcDrawClient.bottom;
		int nRightBottomW = m_rcDrawFrame.right - m_rcDrawClient.right;
		int nRightBottomH = m_rcDrawFrame.bottom - m_rcDrawClient.bottom;
		int nMiddleW = m_rcDrawClient.right - m_rcDrawClient.left;
		int nMiddleH = m_rcDrawClient.bottom - m_rcDrawClient.top;

		// LeftTop
		BitBlt( pDC,
			nRealX, nRealY,
			nLeftTopW, nLeftTopH,
			pPicDC,
			m_rcDrawFrame.left, m_rcDrawFrame.top,
			nLeftTopW, nLeftTopH,
			DrawModeNormal );
		// RightTop
		BitBlt( pDC,
			nRealX+m_nWidth-nRightTopW,nRealY,
			nRightTopW, nRightTopH,
			pPicDC,
			m_rcDrawClient.right, m_rcDrawFrame.top,
			nRightTopW, nRightTopH,
			DrawModeNormal );
		// LeftBottom
		BitBlt( pDC,
			nRealX, nRealY+m_nHeight-nLeftBottomH,
			nLeftBottomW, nLeftBottomH,
			pPicDC,
			m_rcDrawFrame.left, m_rcDrawClient.bottom,
			nLeftBottomW, nLeftBottomH,
			DrawModeNormal );
		// RightBottom
		BitBlt( pDC,
			nRealX+m_nWidth-nRightBottomW, nRealY+m_nHeight-nRightBottomH,
			nRightBottomW, nRightBottomH,
			pPicDC,
			m_rcDrawClient.right, m_rcDrawClient.bottom,
			nRightBottomW, nRightBottomH,
			DrawModeNormal );
		// Left
		BitBlt( pDC,
			nRealX, nRealY+nLeftTopH,
			nLeftW, m_nHeight-nLeftTopH-nLeftBottomH,
			pPicDC,
			m_rcDrawFrame.left, m_rcDrawClient.top,
			nLeftW, nLeftH,
			GetDrawMode( &m_comboLeft ) );
		// Top
		BitBlt( pDC,
			nRealX+nLeftTopW, nRealY,
			m_nWidth-nLeftTopW-nRightTopW,nTopH,
			pPicDC,
			m_rcDrawClient.left, m_rcDrawFrame.top,
			nTopW,nTopH,
			GetDrawMode( &m_comboTop) );
		// Right
		BitBlt( pDC,
			nRealX+m_nWidth-nRightW, nRealY+nRightTopH,
			nRightW, m_nHeight-nRightTopH-nRightBottomH,
			pPicDC,
			m_rcDrawClient.right, m_rcDrawClient.top,
			nRightW, nRightH,
			GetDrawMode( &m_comboRight ) );
		// Bottom
		BitBlt( pDC,
			nRealX+nLeftBottomW, nRealY+m_nHeight-nLeftBottomH,
			m_nWidth-nLeftBottomW-nRightBottomW, nBottomH,
			pPicDC,
			m_rcDrawClient.left, m_rcDrawClient.bottom,
			nBottomW,nBottomH,
			GetDrawMode( &m_comboBottom ) );
		// Middle
		BitBlt( pDC,
			nRealX+nLeftTopW, nRealY+nLeftTopH,
			m_nWidth-nLeftW-nRightW, m_nHeight-nTopH-nBottomH,
			pPicDC,
			m_rcDrawClient.left, m_rcDrawClient.top,
			nMiddleW, nMiddleH,
			GetDrawMode( &m_comboMiddle ) );

	}

// 筐
	CBrush	brush( RGB(0,255,0) );
	CBrush	brushSel( RGB(255,0,0) );
	RECT rcFrame;
	rcFrame.left = nRealX;
	rcFrame.top = nRealY;
	rcFrame.right = rcFrame.left + m_nWidth;
	rcFrame.bottom = rcFrame.top + m_nHeight;
	if ( this == theUIObjectDlg.m_pstCurControl )
	{
		pDC->FrameRect( &rcFrame, &brushSel );
	}
	else
	{
		pDC->FrameRect( &rcFrame, &brush );
	}

}

void CBaseControl::BitBlt( CDC* pDst,
						   int nDstX, int nDstY,
						   int nDstWidth, int nDstHeight,
						   CDC* pSrc,
						   int nSrcX, int nSrcY,
						   int nSrcWidth, int nSrcHeight,
						   int nDrawMode )
{
	assert( pSrc && pDst );
	switch( nDrawMode )
	{
	case DrawModeNormal:
		{
			pDst->TransparentBlt( nDstX, nDstY,
				nSrcWidth, nSrcHeight,
				pSrc,
				nSrcX, nSrcY,
				nSrcWidth, nSrcHeight,
				RGB(255,0,255) );
		}
		break;
	case DrawModeTile:
		{
			int nWCount = nDstWidth/nSrcWidth;
			int nHCount = nDstHeight/nSrcHeight;
			for( int h=0; h<nHCount; h++ )
			{
				for( int w=0; w<nWCount; w++ )
				{
					pDst->TransparentBlt( nDstX+w*nSrcWidth, nDstY+h*nSrcHeight,
						nSrcWidth, nSrcHeight,
						pSrc,
						nSrcX, nSrcY,
						nSrcWidth, nSrcHeight,
						RGB(255,0,255) );
				}
			}
			int nWSurplus = nDstWidth%nSrcWidth;
			int nHSurplus = nDstHeight%nSrcHeight;
			if ( nWSurplus != 0 )
			{
				for( int h=0; h<nHCount; h++ )
				{
					pDst->TransparentBlt( nDstX+nWCount*nSrcWidth, nDstY+h*nSrcHeight,
						nWSurplus, nSrcHeight,
						pSrc,
						nSrcX, nSrcY,
						nWSurplus, nSrcHeight,
						RGB(255,0,255) );
				}
			}
			if ( nHSurplus != 0 )
			{
				for( int w=0; w<nWCount; w++ )
				{
					pDst->TransparentBlt( nDstX+w*nSrcWidth, nDstY+nHCount*nSrcHeight,
						nSrcWidth, nHSurplus,
						pSrc,
						nSrcX, nSrcY,
						nSrcWidth, nHSurplus,
						RGB(255,0,255) );
				}
			}
			if ( nWSurplus != 0 && nHSurplus != 0 )
			{
				pDst->TransparentBlt( nDstX+nWCount*nSrcWidth, nDstY+nHCount*nSrcHeight,
					nWSurplus, nHSurplus,
					pSrc,
					nSrcX, nSrcY,
					nWSurplus, nHSurplus,
					RGB(255,0,255) );
			}
		}
		break;
	case DrawModeStrectch:
		{
			pDst->TransparentBlt( nDstX, nDstY,
				nDstWidth, nDstHeight,
				pSrc,
				nSrcX, nSrcY,
				nSrcWidth, nSrcHeight,
				RGB(255,0,255) );
		}
		break;
	default:
		assert( false );
		break;
	}
}

void CBaseControl::GetPos( int* /*[Out]*/pnX, int* /*[Out]*/pnY, const RECT* /*[In]*/pFatherRc )
{
	assert( pnX && pnY );
	assert( pFatherRc );

	if ( this == theUIObjectDlg.m_pstDialog )
	{
		/**pnX = *pnY = 0;
		return;*/
	}

	switch( GetAlignMode( &m_comboAlign ) )
	{
	case AlignMode_LeftTop:
		{
			*pnX = pFatherRc->left + m_nOffsetX;
			*pnY = pFatherRc->top + m_nOffsetY;
		}
		break;
	case AlignMode_RightTop:
		{
			*pnX = pFatherRc->right + m_nOffsetX;
			*pnY = pFatherRc->top + m_nOffsetY;
		}
		break;
	case AlignMode_LeftBottom:
		{
			*pnX = pFatherRc->left + m_nOffsetX;
			*pnY = pFatherRc->bottom + m_nOffsetY;
		}
		break;
	case AlignMode_RightBottom:
		{
			*pnX = pFatherRc->right + m_nOffsetX;
			*pnY = pFatherRc->bottom + m_nOffsetY;
		}
		break;
	case AlignMode_Middle:
		{
			*pnX = (pFatherRc->left+pFatherRc->right)/2 + m_nOffsetX;
			*pnY = (pFatherRc->top+pFatherRc->bottom)/2 + m_nOffsetY;
		}
		break;
	case AlignMode_LeftMiddle:
		{
			*pnX = pFatherRc->left + m_nOffsetX;
			*pnY = (pFatherRc->top+pFatherRc->bottom)/2 + m_nOffsetY;
		}
		break;
	case AlignMode_TopMiddle:
		{
			*pnX = (pFatherRc->left+pFatherRc->right)/2 + m_nOffsetX;
			*pnY = pFatherRc->top + m_nOffsetY;
		}
		break;
	case AlignMode_RightMiddle:
		{
			*pnX = pFatherRc->right + m_nOffsetX;
			*pnY = (pFatherRc->top+pFatherRc->bottom)/2 + m_nOffsetY;
		}
		break;
	case AlignMode_BottomMiddle:
		{
			*pnX = (pFatherRc->left+pFatherRc->right)/2 + m_nOffsetX;
			*pnY = pFatherRc->bottom + m_nOffsetY;
		}
		break;
	default:
		assert( false );
		break;
	}
}

void CBaseControl::SetPos( int nX, int nY, const RECT* pFatherRc )
{
	assert( pFatherRc );

	switch( GetAlignMode( &m_comboAlign ) )
	{
	case AlignMode_LeftTop:
		{
			m_nOffsetX = nX - pFatherRc->left;
			m_nOffsetY = nY - pFatherRc->top;
		}
		break;
	case AlignMode_RightTop:
		{
			m_nOffsetX = nX - pFatherRc->right;
			m_nOffsetY = nY - pFatherRc->top;
		}
		break;
	case AlignMode_LeftBottom:
		{
			m_nOffsetX = nX - pFatherRc->left;
			m_nOffsetY = nY - pFatherRc->bottom;
		}
		break;
	case AlignMode_RightBottom:
		{
			m_nOffsetX = nX - pFatherRc->right;
			m_nOffsetY = nY - pFatherRc->bottom;
		}
		break;
	case AlignMode_Middle:
		{
			m_nOffsetX = nX - (pFatherRc->left+pFatherRc->right)/2;
			m_nOffsetY = nY - (pFatherRc->top+pFatherRc->bottom)/2;
		}
		break;
	case AlignMode_LeftMiddle:
		{
			m_nOffsetX = nX - pFatherRc->left;
			m_nOffsetY = nY - (pFatherRc->top+pFatherRc->bottom)/2;
		}
		break;
	case AlignMode_TopMiddle:
		{
			m_nOffsetX = nX - (pFatherRc->left+pFatherRc->right)/2;
			m_nOffsetY = nY - pFatherRc->top;
		}
		break;
	case AlignMode_RightMiddle:
		{
			m_nOffsetX = nX - pFatherRc->right;
			m_nOffsetY = nY - (pFatherRc->top+pFatherRc->bottom)/2;
		}
		break;
	case AlignMode_BottomMiddle:
		{
			m_nOffsetX = nX - (pFatherRc->left+pFatherRc->right)/2;
			m_nOffsetY = nY - pFatherRc->bottom;
		}
		break;
	default:
		assert( false );
		break;
	}
}




