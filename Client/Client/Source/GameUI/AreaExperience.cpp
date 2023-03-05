/********************************************************************
Created by UIEditor.exe
FileName: D:\My Documents\桌面\新建文件夹\AreaExperience.cpp
*********************************************************************/
#include <assert.h>
#include "GlobalDef.h"
#include "MeUi/UiManager.h"
#include "AreaExperience.h"
#include "PlayerRole.h"
#include "MeTerrain/WorldPrecompiled.hpp"
#include "Common.h"

extern CPlayerRole thePlayerRole;

#define AssignUIGroup( i, n, w, p, per ) \
									m_pUiGroup[i].m_pAreaName = n; \
									m_pUiGroup[i].m_pWall = w; \
									m_pUiGroup[i].m_pProgress = p; \
									m_pUiGroup[i].m_pAreaPercent = per;\

CUI_ID_FRAME_AreaExperience s_CUI_ID_FRAME_AreaExperience;
MAP_FRAME_RUN( s_CUI_ID_FRAME_AreaExperience, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_AreaExperience, OnFrameRender )
CUI_ID_FRAME_AreaExperience::CUI_ID_FRAME_AreaExperience()
{
	// Member
	m_pID_FRAME_AreaExperience = NULL;
	//m_pID_PICTURE_WallPaper = NULL;
	m_pID_PICTURE_Wall1 = NULL;
	m_pID_PROGRESS_AreaNum1 = NULL;
	m_pID_TEXT_AreaNum1 = NULL;
	m_pID_TEXT_Area1 = NULL;
	m_pID_PICTURE_Wall2 = NULL;
	m_pID_PROGRESS_AreaNum2 = NULL;
	m_pID_TEXT_AreaNum2 = NULL;
	m_pID_TEXT_Area2 = NULL;
	m_pID_PICTURE_Wall3 = NULL;
	m_pID_PROGRESS_AreaNum3 = NULL;
	m_pID_TEXT_AreaNum3 = NULL;
	m_pID_TEXT_Area3 = NULL;
	m_pID_PICTURE_Wall4 = NULL;
	m_pID_PROGRESS_AreaNum4 = NULL;
	m_pID_TEXT_AreaNum4 = NULL;
	m_pID_TEXT_Area4 = NULL;
	m_pID_PICTURE_Wall5 = NULL;
	m_pID_PROGRESS_AreaNum5 = NULL;
	m_pID_TEXT_AreaNum5 = NULL;
	m_pID_TEXT_Area5 = NULL;
	m_pID_PICTURE_Wall6 = NULL;
	m_pID_PROGRESS_AreaNum6 = NULL;
	m_pID_TEXT_AreaNum6 = NULL;
	m_pID_TEXT_Area6 = NULL;
	m_pID_PICTURE_Wall7 = NULL;
	m_pID_PROGRESS_AreaNum7 = NULL;
	m_pID_TEXT_AreaNum7 = NULL;
	m_pID_TEXT_Area7 = NULL;
	m_pID_PICTURE_Wall8 = NULL;
	m_pID_PROGRESS_AreaNum8 = NULL;
	m_pID_TEXT_AreaNum8 = NULL;
	m_pID_TEXT_Area8 = NULL;
	m_pID_PICTURE_Wall9 = NULL;
	m_pID_PROGRESS_AreaNum9 = NULL;
	m_pID_TEXT_AreaNum9 = NULL;
	m_pID_TEXT_Area9 = NULL;
	m_pID_PICTURE_Wall10 = NULL;
	m_pID_PROGRESS_AreaNum10 = NULL;
	m_pID_TEXT_AreaNum10 = NULL;
	m_pID_TEXT_Area10 = NULL;

}
// Frame
bool CUI_ID_FRAME_AreaExperience::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_AreaExperience::OnFrameRender()
{
	return true;
}

// 装载UI
bool CUI_ID_FRAME_AreaExperience::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\AreaExperience.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\AreaExperience.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_AreaExperience::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_AreaExperience, s_CUI_ID_FRAME_AreaExperienceOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_AreaExperience, s_CUI_ID_FRAME_AreaExperienceOnFrameRender );

	m_pID_FRAME_AreaExperience = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_AreaExperience );
//	m_pID_PICTURE_WallPaper = (ControlPicture*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_PICTURE_WallPaper );
	m_pID_PICTURE_Wall1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_PICTURE_Wall1 );
	m_pID_PROGRESS_AreaNum1 = (ControlProgress*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_PROGRESS_AreaNum1 );
	m_pID_TEXT_AreaNum1 = (ControlText*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_TEXT_AreaNum1 );
	m_pID_TEXT_Area1 = (ControlText*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_TEXT_Area1 );
	m_pID_PICTURE_Wall2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_PICTURE_Wall2 );
	m_pID_PROGRESS_AreaNum2 = (ControlProgress*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_PROGRESS_AreaNum2 );
	m_pID_TEXT_AreaNum2 = (ControlText*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_TEXT_AreaNum2 );
	m_pID_TEXT_Area2 = (ControlText*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_TEXT_Area2 );
	m_pID_PICTURE_Wall3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_PICTURE_Wall3 );
	m_pID_PROGRESS_AreaNum3 = (ControlProgress*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_PROGRESS_AreaNum3 );
	m_pID_TEXT_AreaNum3 = (ControlText*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_TEXT_AreaNum3 );
	m_pID_TEXT_Area3 = (ControlText*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_TEXT_Area3 );
	m_pID_PICTURE_Wall4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_PICTURE_Wall4 );
	m_pID_PROGRESS_AreaNum4 = (ControlProgress*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_PROGRESS_AreaNum4 );
	m_pID_TEXT_AreaNum4 = (ControlText*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_TEXT_AreaNum4 );
	m_pID_TEXT_Area4 = (ControlText*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_TEXT_Area4 );
	m_pID_PICTURE_Wall5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_PICTURE_Wall5 );
	m_pID_PROGRESS_AreaNum5 = (ControlProgress*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_PROGRESS_AreaNum5 );
	m_pID_TEXT_AreaNum5 = (ControlText*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_TEXT_AreaNum5 );
	m_pID_TEXT_Area5 = (ControlText*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_TEXT_Area5 );
	m_pID_PICTURE_Wall6 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_PICTURE_Wall6 );
	m_pID_PROGRESS_AreaNum6 = (ControlProgress*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_PROGRESS_AreaNum6 );
	m_pID_TEXT_AreaNum6 = (ControlText*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_TEXT_AreaNum6 );
	m_pID_TEXT_Area6 = (ControlText*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_TEXT_Area6 );
	m_pID_PICTURE_Wall7 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_PICTURE_Wall7 );
	m_pID_PROGRESS_AreaNum7 = (ControlProgress*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_PROGRESS_AreaNum7 );
	m_pID_TEXT_AreaNum7 = (ControlText*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_TEXT_AreaNum7 );
	m_pID_TEXT_Area7 = (ControlText*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_TEXT_Area7 );
	m_pID_PICTURE_Wall8 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_PICTURE_Wall8 );
	m_pID_PROGRESS_AreaNum8 = (ControlProgress*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_PROGRESS_AreaNum8 );
	m_pID_TEXT_AreaNum8 = (ControlText*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_TEXT_AreaNum8 );
	m_pID_TEXT_Area8 = (ControlText*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_TEXT_Area8 );
	m_pID_PICTURE_Wall9 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_PICTURE_Wall9 );
	m_pID_PROGRESS_AreaNum9 = (ControlProgress*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_PROGRESS_AreaNum9 );
	m_pID_TEXT_AreaNum9 = (ControlText*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_TEXT_AreaNum9 );
	m_pID_TEXT_Area9 = (ControlText*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_TEXT_Area9 );
	m_pID_PICTURE_Wall10 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_PICTURE_Wall10 );
	m_pID_PROGRESS_AreaNum10 = (ControlProgress*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_PROGRESS_AreaNum10 );
	m_pID_TEXT_AreaNum10 = (ControlText*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_TEXT_AreaNum10 );
	m_pID_TEXT_Area10 = (ControlText*)theUiManager.FindControl( ID_FRAME_AreaExperience, ID_TEXT_Area10 );
	assert( m_pID_FRAME_AreaExperience );
	//assert( m_pID_PICTURE_WallPaper );
	assert( m_pID_PICTURE_Wall1 );
	assert( m_pID_PROGRESS_AreaNum1 );
	assert( m_pID_TEXT_AreaNum1 );
	assert( m_pID_TEXT_Area1 );
	assert( m_pID_PICTURE_Wall2 );
	assert( m_pID_PROGRESS_AreaNum2 );
	assert( m_pID_TEXT_AreaNum2 );
	assert( m_pID_TEXT_Area2 );
	assert( m_pID_PICTURE_Wall3 );
	assert( m_pID_PROGRESS_AreaNum3 );
	assert( m_pID_TEXT_AreaNum3 );
	assert( m_pID_TEXT_Area3 );
	assert( m_pID_PICTURE_Wall4 );
	assert( m_pID_PROGRESS_AreaNum4 );
	assert( m_pID_TEXT_AreaNum4 );
	assert( m_pID_TEXT_Area4 );
	assert( m_pID_PICTURE_Wall5 );
	assert( m_pID_PROGRESS_AreaNum5 );
	assert( m_pID_TEXT_AreaNum5 );
	assert( m_pID_TEXT_Area5 );
	assert( m_pID_PICTURE_Wall6 );
	assert( m_pID_PROGRESS_AreaNum6 );
	assert( m_pID_TEXT_AreaNum6 );
	assert( m_pID_TEXT_Area6 );
	assert( m_pID_PICTURE_Wall7 );
	assert( m_pID_PROGRESS_AreaNum7 );
	assert( m_pID_TEXT_AreaNum7 );
	assert( m_pID_TEXT_Area7 );
	assert( m_pID_PICTURE_Wall8 );
	assert( m_pID_PROGRESS_AreaNum8 );
	assert( m_pID_TEXT_AreaNum8 );
	assert( m_pID_TEXT_Area8 );
	assert( m_pID_PICTURE_Wall9 );
	assert( m_pID_PROGRESS_AreaNum9 );
	assert( m_pID_TEXT_AreaNum9 );
	assert( m_pID_TEXT_Area9 );
	assert( m_pID_PICTURE_Wall10 );
	assert( m_pID_PROGRESS_AreaNum10 );
	assert( m_pID_TEXT_AreaNum10 );
	assert( m_pID_TEXT_Area10 );
	AssignUIGroup( 0, m_pID_TEXT_Area1, m_pID_PICTURE_Wall1, m_pID_PROGRESS_AreaNum1, m_pID_TEXT_AreaNum1 );
	AssignUIGroup( 1, m_pID_TEXT_Area2, m_pID_PICTURE_Wall2, m_pID_PROGRESS_AreaNum2, m_pID_TEXT_AreaNum2 );
	AssignUIGroup( 2, m_pID_TEXT_Area3, m_pID_PICTURE_Wall3, m_pID_PROGRESS_AreaNum3, m_pID_TEXT_AreaNum3 );
	AssignUIGroup( 3, m_pID_TEXT_Area4, m_pID_PICTURE_Wall4, m_pID_PROGRESS_AreaNum4, m_pID_TEXT_AreaNum4 );
	AssignUIGroup( 4, m_pID_TEXT_Area5, m_pID_PICTURE_Wall5, m_pID_PROGRESS_AreaNum5, m_pID_TEXT_AreaNum5 );
	AssignUIGroup( 5, m_pID_TEXT_Area6, m_pID_PICTURE_Wall6, m_pID_PROGRESS_AreaNum6, m_pID_TEXT_AreaNum6 );
	AssignUIGroup( 6, m_pID_TEXT_Area7, m_pID_PICTURE_Wall7, m_pID_PROGRESS_AreaNum7, m_pID_TEXT_AreaNum7 );
	AssignUIGroup( 7, m_pID_TEXT_Area8, m_pID_PICTURE_Wall8, m_pID_PROGRESS_AreaNum8, m_pID_TEXT_AreaNum8 );
	AssignUIGroup( 8, m_pID_TEXT_Area9, m_pID_PICTURE_Wall9, m_pID_PROGRESS_AreaNum9, m_pID_TEXT_AreaNum9 );
	AssignUIGroup( 9, m_pID_TEXT_Area10, m_pID_PICTURE_Wall10, m_pID_PROGRESS_AreaNum10, m_pID_TEXT_AreaNum10 );

	m_pID_FRAME_AreaExperience->SetMsgHoldup( false );

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_AreaExperience::_UnLoadUI()
{
	m_pID_FRAME_AreaExperience = NULL;
//	m_pID_PICTURE_WallPaper = NULL;
	m_pID_PICTURE_Wall1 = NULL;
	m_pID_PROGRESS_AreaNum1 = NULL;
	m_pID_TEXT_AreaNum1 = NULL;
	m_pID_TEXT_Area1 = NULL;
	m_pID_PICTURE_Wall2 = NULL;
	m_pID_PROGRESS_AreaNum2 = NULL;
	m_pID_TEXT_AreaNum2 = NULL;
	m_pID_TEXT_Area2 = NULL;
	m_pID_PICTURE_Wall3 = NULL;
	m_pID_PROGRESS_AreaNum3 = NULL;
	m_pID_TEXT_AreaNum3 = NULL;
	m_pID_TEXT_Area3 = NULL;
	m_pID_PICTURE_Wall4 = NULL;
	m_pID_PROGRESS_AreaNum4 = NULL;
	m_pID_TEXT_AreaNum4 = NULL;
	m_pID_TEXT_Area4 = NULL;
	m_pID_PICTURE_Wall5 = NULL;
	m_pID_PROGRESS_AreaNum5 = NULL;
	m_pID_TEXT_AreaNum5 = NULL;
	m_pID_TEXT_Area5 = NULL;
	m_pID_PICTURE_Wall6 = NULL;
	m_pID_PROGRESS_AreaNum6 = NULL;
	m_pID_TEXT_AreaNum6 = NULL;
	m_pID_TEXT_Area6 = NULL;
	m_pID_PICTURE_Wall7 = NULL;
	m_pID_PROGRESS_AreaNum7 = NULL;
	m_pID_TEXT_AreaNum7 = NULL;
	m_pID_TEXT_Area7 = NULL;
	m_pID_PICTURE_Wall8 = NULL;
	m_pID_PROGRESS_AreaNum8 = NULL;
	m_pID_TEXT_AreaNum8 = NULL;
	m_pID_TEXT_Area8 = NULL;
	m_pID_PICTURE_Wall9 = NULL;
	m_pID_PROGRESS_AreaNum9 = NULL;
	m_pID_TEXT_AreaNum9 = NULL;
	m_pID_TEXT_Area9 = NULL;
	m_pID_PICTURE_Wall10 = NULL;
	m_pID_PROGRESS_AreaNum10 = NULL;
	m_pID_TEXT_AreaNum10 = NULL;
	m_pID_TEXT_Area10 = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\AreaExperience.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_AreaExperience::_IsVisable()
{
	if(!m_pID_FRAME_AreaExperience)
		return false;

	return m_pID_FRAME_AreaExperience->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_AreaExperience::_SetVisable( const bool bVisable )
{
	if(m_pID_FRAME_AreaExperience)
		m_pID_FRAME_AreaExperience->SetVisable( bVisable );
}

void CUI_ID_FRAME_AreaExperience::Update()
{
	if(!m_pID_FRAME_AreaExperience)
		return;

	for (int i = 0; i < MAX_AREAREPULATION_COUNT; ++i)
	{
		m_pUiGroup[i].SetVisible( false );
	}
	for (int i = 0; i < MAX_AREAREPULATION_COUNT; ++i)
	{
		if ( thePlayerRole.m_pBaseInfo->liveinfo.xArea[i].nMapID != -1) // 有
		{
			m_pUiGroup[i].SetVisible( true );

			char acTemp[256] = {0};
			// area percent
			MeSprintf_s( acTemp, sizeof(acTemp)/sizeof(char) - 1, "%d / %d", thePlayerRole.m_pBaseInfo->liveinfo.xArea[i].nCurrentReputation, 
				thePlayerRole.m_pBaseInfo->liveinfo.xArea[i].nMaxReputation );			
			*m_pUiGroup[i].m_pAreaPercent = acTemp;
			// area name			
			CWorldBuffer* pbuffer = SwGlobal::GetWorld()->GetWorldBuffer();
			if( pbuffer )
			{
				CWorldTile* pActiveTile = pbuffer->GetTileFromMapId(thePlayerRole.m_pBaseInfo->liveinfo.xArea[i].nMapID );
				if( pActiveTile )
					*m_pUiGroup[i].m_pAreaName = pActiveTile->GetTileName();
			}
			// progress
			__int64 n64Max = thePlayerRole.m_pBaseInfo->liveinfo.xArea[i].nMaxReputation;
			m_pUiGroup[i].m_pProgress->SetMaxValue( n64Max );
			m_pUiGroup[i].m_pProgress->SetValue( thePlayerRole.m_pBaseInfo->liveinfo.xArea[i].nCurrentReputation );
			
		}
	}
}

void CUI_ID_FRAME_AreaExperience::SetFrameAreaExperienceFather( ControlObject* pFather )
{
	if(m_pID_FRAME_AreaExperience && pFather )
		m_pID_FRAME_AreaExperience->SetFather( pFather );
	else
		assert(false&&"ui error");
}