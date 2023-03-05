#include "MeUi/ControlCheckBox.h"
#include "MeUi/UiManager.h"
#include "Me3d/BaseGraphics.h"
#include "MeFont/MeFontSystem.h"  //##

const int OFFSET_HEIGHT = 3;

extern DWORD g_dwColorTip0;
extern DWORD g_dwColorTip1;

ControlCheckBox::ControlCheckBox(void) :
m_bMouseMoveOn(false),
m_bShowTip(false)
{
	m_pFunOnCheck = NULL;
	//
	m_strSound = UiManager::m_strCheckBoxSound;

	_luaTableName.clear();
	_funOnClickName.clear();

}

ControlCheckBox::~ControlCheckBox(void)
{
}

void ControlCheckBox::Render()
{
	if ( IsNeedRender() )
	{		
		m_CheckButton.Render();

		if (m_bMouseMoveOn && !IsChecked())
			m_CheckMoveOnButton.Render();

		RECT rc;
		GetRealRect( &rc );
//  		rc.left += m_nHeight+FONT_OFFSET_X;
//  		rc.top += 2;

		//## 
		FontSystem::DrawTextRGB( m_pstData->m_szCaption, &rc, DT_VCENTER|DT_CENTER|DT_NOCLIP,
							m_pstData->m_colFont, m_nFontIndex );

		if( m_pstData->m_szCaption[0] != 0 )
		{
			if( 0 && m_bMouseMoveOn && GetShowTip())
			{
				m_bMouseMoveOn = PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y,false);

				//GetRealRect( &rc );
				//UINT nLength = strlen(m_pstData->m_szCaption);
				//rc.left = theUiManager.m_ptMoust.x;
				//rc.top = theUiManager.m_ptMoust.y-m_pstData->m_nFontSize;
				//if( rc.left < 0 ) rc.left = 0;
				//if( rc.top < 0 ) rc.top = 0;
				//if( rc.left > SCREEN_WIDTH - m_pstData->m_nFontSize*nLength/2 )
				//	rc.left = SCREEN_WIDTH - m_pstData->m_nFontSize*nLength/2;
				//if( rc.top > SCREEN_HEIGHT - m_pstData->m_nFontSize )
				//	rc.top = SCREEN_HEIGHT - m_pstData->m_nFontSize;
				//rc.right = rc.left + m_pstData->m_nFontSize*nLength/2;
				//rc.bottom = rc.top + m_pstData->m_nFontSize;
				//
				//INT nHeight = m_pstData->m_nFontSize;
				//INT nWidth = m_pstData->m_nFontSize*(strlen(m_pstData->m_szCaption))/2;
				//SetRect( &rc, rc.left-OFFSET_HEIGHT, rc.top-OFFSET_HEIGHT, rc.left+nWidth+OFFSET_HEIGHT, rc.top+nHeight+OFFSET_HEIGHT );

				//UiDrawer::FillRect2D( rc, g_dwColorTip0 );
				//FontSystem::DrawTextRGB( &rc, m_pstData->m_szCaption, m_pstData->m_colFont, m_nFontIndex, DT_VCENTER|DT_CENTER );
				//UiDrawer::DrawRect2D( rc, g_dwColorTip1 );

				//theUiManager.ToTop(this);

				const int OFFSET_HEIGHT = 4;

				UINT nLength = strlen(m_pstData->m_szCaption);
				INT nWidth = m_pstData->m_nFontSize * ControlObjectGetREAL_SCALE(this) * nLength/2;
				INT nHeight = m_pstData->m_nFontSize * ControlObjectGetREAL_SCALE(this) ;
				rc.left = theUiManager.m_ptMoust.x-1;
				rc.top = theUiManager.m_ptMoust.y - m_pstData->m_nFontSize * ControlObjectGetREAL_SCALE(this) 
					- OFFSET_HEIGHT*2 - 2;
				if( rc.left < 0 )
					rc.left = 0;
				if( rc.top < 0 )
					rc.top = 0;
				if( rc.left > SCREEN_WIDTH - (nWidth+OFFSET_HEIGHT*2) )
					rc.left = SCREEN_WIDTH - (nWidth+OFFSET_HEIGHT*2);
				if( rc.top > SCREEN_HEIGHT - m_pstData->m_nFontSize * ControlObjectGetREAL_SCALE(this) )
					rc.top = SCREEN_HEIGHT - m_pstData->m_nFontSize * ControlObjectGetREAL_SCALE(this) ;
				rc.right = rc.left + nWidth + OFFSET_HEIGHT+1;
				rc.bottom = rc.top + nHeight + OFFSET_HEIGHT+1;
				RECT rcText = rc;
				rcText.left += OFFSET_HEIGHT;
				rcText.top += 1;

				UiDrawer::FillRect2D( rc, g_dwColorTip0 );
				//FontSystem::DrawTextRGB( &rcText, m_pstData->m_szCaption, /*m_pstData->m_colFont*/RGB(209,195,157),
				//	m_nFontIndex, /*DT_VCENTER|DT_CENTER*/0 );
				FontSystem::DrawTextRGB( m_pstData->m_szCaption, &rcText, DT_VCENTER|DT_CENTER|DT_NOCLIP,
									D3DCOLOR_ARGB(0xff,209,195,157), m_nFontIndex );
				UiDrawer::DrawRect2D( rc, g_dwColorTip1 );
				//
				//
				RECT rcF = rc;
				rcF.left += 1;
				rcF.top += 1;
				rcF.right -= 1;
				rcF.bottom -= 1;
				DWORD dwColorBottom = 0xFF3F2500;
				DWORD dwColorRight = 0xFF3F2500;
				DWORD dwColorLeft = 0xFF8C5500;
				DWORD dwColorTop = 0xFFFFDE6F;
				CBaseGraphics *g = GetDrawer();
				// 下
				g->DrawLine2D( rcF.left, rcF.bottom, rcF.right+1, rcF.bottom, dwColorBottom );
				// 右
				g->DrawLine2D( rcF.right, rcF.top, rcF.right, rcF.bottom, dwColorRight );
				// 左
				g->DrawLine2D( rcF.left, rcF.bottom, rcF.left, rcF.top, dwColorLeft );
				// 上
				g->DrawLine2D( rcF.left, rcF.top, rcF.right, rcF.top, dwColorTop );			}
		}
	}
}

void ControlCheckBox::InitUIData( IN ControlObject* pFather, IN S_BaseData* pData )
{
	ControlObject::InitUIData( pFather, pData );

	S_CheckBoxData *pCheckBoxData = (S_CheckBoxData*)pData;

	m_CheckButton.InitUIData( this, &pCheckBoxData->m_stChecked );
	//m_CheckButton.SetCaption(pData->m_szCaption);
	m_CheckMoveOnButton.InitUIData(this, &pCheckBoxData->m_stChecked);
	m_CheckMoveOnButton.SetPic(&pCheckBoxData->m_stChecked.m_stMoveOnPic);
	if ( pCheckBoxData->m_bChecked == true )
	{
		m_CheckButton.SetPressPic();
	}
	else
	{
		m_CheckButton.SetNormalPic();
	}

	SetShowTips();
}

bool ControlCheckBox::OnLButtonDown( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() )
	{
		if ( PtInObject(nX, nY,true) == true )
		{
			//((S_CheckBoxData*)m_pstData)->m_bChecked = !((S_CheckBoxData*)m_pstData)->m_bChecked;
			//SetActivate();
			//OnCheck();
			//PlaySound();
			return m_bMsgHoldup;
		}
	}
	return false;
}

bool ControlCheckBox::OnLButtonUp( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() )
	{
		if ( PtInObject(nX, nY,true) == true )
		{
			if (IsEnable())
			{
				((S_CheckBoxData*)m_pstData)->m_bChecked = !((S_CheckBoxData*)m_pstData)->m_bChecked;
				SetActivate();
				OnCheck();
				PlaySound();
			}
			return m_bMsgHoldup;
		}
	}
	return false;
}

void ControlCheckBox::OnCheck()
{
	if (!m_bEnable)
		return;

	if( NULL != state.Get() && _luaTableName.length() > 0 &&  _funOnClickName.length() > 0)
	{
		try
		{
			LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
			if( table1Obj.IsTable() )
			{
				LuaFunction<void> function_( table1Obj[_funOnClickName.c_str()] );
				function_();
			}
		}
		catch (LuaPlus::LuaException &e)
		{
			char szErr[256] = {0};
			_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funOnClickName.c_str(), e.GetErrorMessage());
			print_error( szErr );
		}
	}
	else
	{
		if ( m_pFunOnCheck )
		{
			m_pFunOnCheck( this, &((S_CheckBoxData*)m_pstData)->m_bChecked );
		}
	}

#ifdef _DEBUG
	if ( m_debug_bHasWarning )
	{
		char szDebug[128];
		char szFatherID[128] = "";
		if ( m_pFather )
		{
			strcpy( szFatherID, m_pFather->GetControlID() );
		}
		sprintf(szDebug,"[%s]::[%s] OnCheck(void) not defend!!\r\n", szFatherID, GetControlID() );
		//OutputDebugString(szDebug);
	}
#endif

	S_CheckBoxData *pCheckBoxData = (S_CheckBoxData*)m_pstData;
	if ( pCheckBoxData )
	{
		if ( pCheckBoxData->m_bChecked == true )
		{
			m_CheckButton.SetPressPic();
		}
		else
		{
			m_CheckButton.SetNormalPic();
		}
	}

}

void ControlCheckBox::SetCheck( const bool bCheck )
{
	if (!m_bEnable)
		return;

	// commented out, jiayi, [2009/6/29]
// 	if (((S_CheckBoxData*)m_pstData)->m_bChecked == bCheck)
// 		return;

	((S_CheckBoxData*)m_pstData)->m_bChecked = bCheck;

	if ( bCheck == true )
	{
		m_CheckButton.SetPressPic();
	}
	else
	{
		m_CheckButton.SetNormalPic();
	}
}
bool ControlCheckBox::OnMouseMove( UINT nFlags, const int nX, const int nY)
{
	if(IsVisable()&&m_bEnable)
	{
		S_CheckBoxData *pCheckData = (S_CheckBoxData*)m_pstData;
		if( PtInObject(nX, nY,false) )
		{
			m_bMouseMoveOn = true;
		}
		else
		{
			m_bMouseMoveOn = false;
		}
	}
	
	if (PtInObject(nX, nY,false) == true )
	{
		if( m_bShowTip )
		{
			theIconInfoMouseTip.SetDisplayInfo( &TipInfo,
				nX, nY, false,
				m_nFontIndex, FontSystem::GetFontHeight(m_nFontIndex),
				m_pstData->m_colFont,
				false );
		}
	}

	return false;
}

void ControlCheckBox::SetCheckFun_2lua( const char* luaTable, const char* funName )
{
	_luaTableName = luaTable;
	_funOnClickName = funName;
}

void ControlCheckBox::SetEnable( bool b )
{
	m_bEnable = b;
	m_CheckButton.SetEnable(b);
}

void ControlCheckBox::ResetDevice()
{
	ControlObject::ResetDevice();
	m_CheckButton.ResetDevice();
	m_CheckMoveOnButton.ResetDevice();
}

//added by zhuomeng.hu		[8/24/2010]
void ControlCheckBox::SetCheckPic( const char* szPath, const RECT* prcFrame, const RECT* prcClient )
{
	m_CheckButton.m_pstPic = NULL;
	S_BaseData::S_Pic pic;
	pic.SetPicStruct( szPath, prcFrame, prcClient );
	m_CheckButton.setMousePressPic( &pic );
	//m_CheckButton.m_pstPic = m_CheckButton.getMousePressPic();
}

void ControlCheckBox::SetUnCheckPic( const char* szPath, const RECT* prcFrame, const RECT* prcClient )
{
	m_CheckButton.m_pstPic = NULL;
	S_BaseData::S_Pic pic;
	pic.SetPicStruct( szPath, prcFrame, prcClient );
	m_CheckButton.setBgPic( &pic );
	//m_CheckButton.m_pstPic = m_CheckButton.getBgPic();
}

void ControlCheckBox::SetDisablePic( const char* szPath, const RECT* prcFrame, const RECT* prcClient )
{
	m_CheckButton.m_pstPic = NULL;
	S_BaseData::S_Pic pic;
	pic.SetPicStruct( szPath, prcFrame, prcClient );
	m_CheckButton.setDisabledPic( &pic );
	//m_CheckButton.m_pstPic = m_CheckButton.getDisabledPic();
}

void ControlCheckBox::SetMoveOnPic( const char* szPath, const RECT* prcFrame, const RECT* prcClient )
{
	m_CheckMoveOnButton.m_pstPic = NULL;
	m_CheckMoveOnButton.getMouseMovePic()->SetPicStruct( szPath, prcFrame, prcClient );
	m_CheckMoveOnButton.SetPic( m_CheckMoveOnButton.getMouseMovePic() );
}

void ControlCheckBox::SetCaption( const char* szText )
{
	if( szText )
    {
        strcpy( m_pstData->m_szCaption, szText );
    }

	if( GetFrameFather() )
	{
		GetFrameFather()->SetRedraw();
	}
}

void ControlCheckBox::SetCaptionColor( DWORD dwColor )
{
    m_pstData->m_colFont = dwColor;

    if( GetFrameFather() )
    {
        GetFrameFather()->SetRedraw();
    }
}

const char* ControlCheckBox::GetCaption()
{
    return m_pstData->m_szCaption;
}

DWORD ControlCheckBox::GetCaptionColor()
{
    return m_pstData->m_colFont;
}

ControlRadioGroup::ControlRadioGroup()
{
	m_isVisible = false;
	m_pSelectRadio = 0;
}

ControlRadioGroup::~ControlRadioGroup()
{
}

void ControlRadioGroup::AddRadio(ControlCheckBox* pControl)
{
	m_vecRadioGroup.push_back(pControl);
	AddControl(pControl);
}

void ControlRadioGroup::ToggleRadio(ControlCheckBox* pControl)
{
	if (!pControl)
	{
		return;
	}

	pControl->SetCheck(true);
	m_pSelectRadio = pControl;

	for (int i = 0; i < m_vecRadioGroup.size(); ++i)
	{
		if (pControl != m_vecRadioGroup[i])
			m_vecRadioGroup[i]->SetCheck(false);
	}
}

void ControlRadioGroup::Clear()
{
	ControlGroup::Clear();
	m_vecRadioGroup.clear();
}

void ControlCheckBox::setTip(const char* data)
{
	if( NULL == data )
		return;

	TipInfo.SetInfo( data, DT_LEFT | DT_VCENTER );	
}

void ControlCheckBox::SetShowTips()
{
	if (strlen(m_pstData->m_szTips) != 0)
	{
		m_bShowTip = true;
		setTip(m_pstData->m_szTips);
	}
}