#include "StdAfx.h"
#include "framecontrol.h"
#include <assert.h>
#include "PropertyDlg.h"

CFrameControl::CFrameControl(void)
{
	m_nType = Type_Frame;

	m_nWidth = 200;
	m_nHeight = 300;
	m_strID.Format( "ID_FRAME_%d", rand() );

	m_comboArray.SetData( ARRAY_MODE_NORMAL, ARRAY_MODE_COMBO );
	m_bMoveable = TRUE;

	m_ProFrame[Item_Frame_Comments_State].SetItem( PIT_COMMENTS, "<Frame>", NULL );
	m_ProFrame[Item_Frame_Array].SetItem( PIT_COMBO, "排列方式", &m_comboArray );
    m_ProFrame[Item_Frame_Moveable].SetItem( PIT_BOOL, "是否可移动", &m_bMoveable );
	m_ProFrame[Item_Frame_Script].SetItem( PIT_FILE, "脚本文件", &m_bScriptName );

	m_ProFrame[Item_Frame_Event].SetItem( PIT_COMMENTS, "<Event>", NULL );
	m_ProFrame[Item_Frame_OnClick].SetItem( PIT_EDIT, "OnClick", &m_OnClickName );
	m_ProFrame[Item_Frame_OnRBtnDown].SetItem( PIT_EDIT, "OnRBtnDown", &m_OnRBtnDownName );
	m_ProFrame[Item_Frame_OnMouseMoveOn].SetItem( PIT_EDIT, "OnMouseMoveOn", &m_OnMouseMoveOnName );
	m_ProFrame[Item_Frame_OnMouseMoveLeave].SetItem( PIT_EDIT, "OnMouseMoveLeave", &m_OnMouseMoveLeaveName );
	m_ProFrame[Item_Frame_OnFrameMove].SetItem( PIT_EDIT, "OnFrameMove", &m_OnFrameMoveName );
	m_ProFrame[Item_Frame_Run].SetItem( PIT_EDIT, "Run", &m_RunName );
	m_ProFrame[Item_Frame_Render].SetItem( PIT_EDIT, "Render", &m_RenderName );
	m_ProFrame[Item_Frame_OnTab].SetItem( PIT_EDIT, "OnTab", &m_OnTabName );
}

CFrameControl::~CFrameControl(void)
{
}

int CFrameControl::GetArrayMode( S_Combo* pCombo )
{
	assert( pCombo );
	if ( pCombo->m_curValue == ARRAY_MODE_NORMAL )
	{
		return ArrayMode_Normal;
	}
	else if ( pCombo->m_curValue == ARRAY_MODE_TOP )
	{
		return ArrayMode_Top;
	}
	else if ( pCombo->m_curValue == ARRAY_MODE_BOTTOM )
	{
		return ArrayMode_Bottom;
	}
	else
	{
		assert( false );
		return ArrayMode_Normal;
	}
}

CString CFrameControl::GetArrayMode( int nMode )
{
	switch( nMode )
	{
	case ArrayMode_Normal:
		return ARRAY_MODE_NORMAL;
		break;
	case ArrayMode_Top:
		return ARRAY_MODE_TOP;
		break;
	case ArrayMode_Bottom:
		return ARRAY_MODE_BOTTOM;
		break;
	default:
		assert( false );
		return ARRAY_MODE_NORMAL;
	}
}


void CFrameControl::AddToPropertyDlg()
{
	CBaseControl::AddToPropertyDlg();
	for( int n=0; n<Item_Frame_Max; n++ )
	{
		thePropertyDlg.AddItem( &m_ProFrame[n] );
	}
}

bool CFrameControl::SetData( const S_BaseData* /*[In]*/pData )
{
	assert( pData );
	S_FrameData *pFrameControl = (S_FrameData*)pData;

	m_comboArray.m_curValue = GetArrayMode( pFrameControl->m_nArrayMode );
	m_bMoveable = pFrameControl->m_bMoveable;

	return CBaseControl::SetData( pData );
}

bool CFrameControl::GetData( S_BaseData* /*[Out]*/pData )
{
	assert( pData );
	S_FrameData *pFrameControl = (S_FrameData*)pData;

	pFrameControl->m_nArrayMode = GetArrayMode( &m_comboArray );
	pFrameControl->m_bMoveable = m_bMoveable==TRUE;

	return CBaseControl::GetData( pData );
}

void CFrameControl::GetData_Event( int index )
{
	stUIData.SetEventFunName( index, EET_Frame_OnClick, m_OnClickName.GetBuffer() );
	stUIData.SetEventFunName( index, EET_Frame_OnRBtnDown, m_OnRBtnDownName.GetBuffer() );
	stUIData.SetEventFunName( index, EET_Frame_OnMouseMoveOn, m_OnMouseMoveOnName.GetBuffer() );
	stUIData.SetEventFunName( index, EET_Frame_OnMouseMoveLeave, m_OnMouseMoveLeaveName.GetBuffer() );
	stUIData.SetEventFunName( index, EET_Frame_OnFrameMove, m_OnFrameMoveName.GetBuffer() );
	stUIData.SetEventFunName( index, EET_Frame_Run, m_RunName.GetBuffer() );
	stUIData.SetEventFunName( index, EET_Frame_Render, m_RenderName.GetBuffer() );
	stUIData.SetEventFunName( index, EET_Frame_OnTab, m_OnTabName.GetBuffer() );
}

