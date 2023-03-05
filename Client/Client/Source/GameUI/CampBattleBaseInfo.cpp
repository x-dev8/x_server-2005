/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\CampBattleBaseInfo.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "CampBattleBaseInfo.h"
#include "CampBattleCountry.h"
#include "CampBattleGuild.h"
#include "CampBattleGuildUnion.h"
#include "CampBattleWorld.h"
#include "LoadMap.h"
CUI_ID_FRAME_CampBattleBaseInfo s_CUI_ID_FRAME_CampBattleBaseInfo;
MAP_FRAME_RUN( s_CUI_ID_FRAME_CampBattleBaseInfo, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_CampBattleBaseInfo, OnFrameRender )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CampBattleBaseInfo, ID_CHECKBOX_GuoWangOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CampBattleBaseInfo, ID_CHECKBOX_GuildOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CampBattleBaseInfo, ID_CHECKBOX_UnionOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_CampBattleBaseInfo, ID_CHECKBOX_WorldOnCheckBoxCheck )
CUI_ID_FRAME_CampBattleBaseInfo::CUI_ID_FRAME_CampBattleBaseInfo()
{
	// Member
	m_pID_FRAME_CampBattleBaseInfo = NULL;
	m_pID_CHECKBOX_GuoWang = NULL;
	m_pID_CHECKBOX_Guild = NULL;
	m_pID_CHECKBOX_Union = NULL;
	m_pID_CHECKBOX_World = NULL;

}
// Frame
bool CUI_ID_FRAME_CampBattleBaseInfo::OnFrameRun()
{
	//更新所有提示信息
	if(s_CUI_ID_FRAME_LoadMap.IsMapLoading())
		return true;
	time_t now;
	time(&now);
	s_CUI_ID_FRAME_CampBattleCountry.GetCampBattleInfo().HandleCampBattleInfo(now);
	s_CUI_ID_FRAME_CampBattleGuild.GetCampBattleInfo().HandleCampBattleInfo(now);
	s_CUI_ID_FRAME_CampBattleGuildUnion.GetCampBattleInfo().HandleCampBattleInfo(now);
	s_CUI_ID_FRAME_CampBattleWorld.GetCampBattleInfo().HandleCampBattleInfo(now);
	return true;
}
bool CUI_ID_FRAME_CampBattleBaseInfo::OnFrameRender()
{
	return true;
}
// CheckBox
void CUI_ID_FRAME_CampBattleBaseInfo::ID_CHECKBOX_GuoWangOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_CHECKBOX_GuoWang->IsChecked())
	{
		m_pID_CHECKBOX_GuoWang->SetCheck(true);
		return;
	}
	m_pID_CHECKBOX_Guild->SetCheck(false);
	m_pID_CHECKBOX_Union->SetCheck(false);
	m_pID_CHECKBOX_World->SetCheck(false);
	//设置面板显示
	s_CUI_ID_FRAME_CampBattleCountry.SetVisable(true);
	s_CUI_ID_FRAME_CampBattleGuild.SetVisable(false);
	s_CUI_ID_FRAME_CampBattleGuildUnion.SetVisable(false);
	s_CUI_ID_FRAME_CampBattleWorld.SetVisable(false);
}
// CheckBox
void CUI_ID_FRAME_CampBattleBaseInfo::ID_CHECKBOX_GuildOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_CHECKBOX_Guild->IsChecked())
	{
		m_pID_CHECKBOX_Guild->SetCheck(true);
		return;
	}
	m_pID_CHECKBOX_GuoWang->SetCheck(false);
	m_pID_CHECKBOX_Union->SetCheck(false);
	m_pID_CHECKBOX_World->SetCheck(false);
	s_CUI_ID_FRAME_CampBattleCountry.SetVisable(false);
	s_CUI_ID_FRAME_CampBattleGuild.SetVisable(true);
	s_CUI_ID_FRAME_CampBattleGuildUnion.SetVisable(false);
	s_CUI_ID_FRAME_CampBattleWorld.SetVisable(false);
}
// CheckBox
void CUI_ID_FRAME_CampBattleBaseInfo::ID_CHECKBOX_UnionOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_CHECKBOX_Union->IsChecked())
	{
		m_pID_CHECKBOX_Union->SetCheck(true);
		return;
	}
	m_pID_CHECKBOX_Guild->SetCheck(false);
	m_pID_CHECKBOX_GuoWang->SetCheck(false);
	m_pID_CHECKBOX_World->SetCheck(false);
	s_CUI_ID_FRAME_CampBattleCountry.SetVisable(false);
	s_CUI_ID_FRAME_CampBattleGuild.SetVisable(false);
	s_CUI_ID_FRAME_CampBattleGuildUnion.SetVisable(true);
	s_CUI_ID_FRAME_CampBattleWorld.SetVisable(false);
}
// CheckBox
void CUI_ID_FRAME_CampBattleBaseInfo::ID_CHECKBOX_WorldOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_CHECKBOX_World->IsChecked())
	{
		m_pID_CHECKBOX_World->SetCheck(true);
		return;
	}
	m_pID_CHECKBOX_Guild->SetCheck(false);
	m_pID_CHECKBOX_Union->SetCheck(false);
	m_pID_CHECKBOX_GuoWang->SetCheck(false);
	s_CUI_ID_FRAME_CampBattleCountry.SetVisable(false);
	s_CUI_ID_FRAME_CampBattleGuild.SetVisable(false);
	s_CUI_ID_FRAME_CampBattleGuildUnion.SetVisable(false);
	s_CUI_ID_FRAME_CampBattleWorld.SetVisable(true);
}

	// 装载UI
bool CUI_ID_FRAME_CampBattleBaseInfo::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\CampBattleBaseInfo.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\CampBattleBaseInfo.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_CampBattleBaseInfo::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_CampBattleBaseInfo, s_CUI_ID_FRAME_CampBattleBaseInfoOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_CampBattleBaseInfo, s_CUI_ID_FRAME_CampBattleBaseInfoOnFrameRender );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CampBattleBaseInfo, ID_CHECKBOX_GuoWang, s_CUI_ID_FRAME_CampBattleBaseInfoID_CHECKBOX_GuoWangOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CampBattleBaseInfo, ID_CHECKBOX_Guild, s_CUI_ID_FRAME_CampBattleBaseInfoID_CHECKBOX_GuildOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CampBattleBaseInfo, ID_CHECKBOX_Union, s_CUI_ID_FRAME_CampBattleBaseInfoID_CHECKBOX_UnionOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_CampBattleBaseInfo, ID_CHECKBOX_World, s_CUI_ID_FRAME_CampBattleBaseInfoID_CHECKBOX_WorldOnCheckBoxCheck );

	m_pID_FRAME_CampBattleBaseInfo = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_CampBattleBaseInfo );
	m_pID_CHECKBOX_GuoWang = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CampBattleBaseInfo, ID_CHECKBOX_GuoWang );
	m_pID_CHECKBOX_Guild = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CampBattleBaseInfo, ID_CHECKBOX_Guild );
	m_pID_CHECKBOX_Union = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CampBattleBaseInfo, ID_CHECKBOX_Union );
	m_pID_CHECKBOX_World = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_CampBattleBaseInfo, ID_CHECKBOX_World );
	assert( m_pID_FRAME_CampBattleBaseInfo );

	_SetVisable(false);
	assert( m_pID_CHECKBOX_GuoWang );
	assert( m_pID_CHECKBOX_Guild );
	assert( m_pID_CHECKBOX_Union );
	assert( m_pID_CHECKBOX_World );
	return true;
}
	// 卸载UI
bool CUI_ID_FRAME_CampBattleBaseInfo::_UnLoadUI()
{
	m_pID_FRAME_CampBattleBaseInfo = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\CampBattleBaseInfo.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_CampBattleBaseInfo::_IsVisable()
{
	return m_pID_FRAME_CampBattleBaseInfo->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_CampBattleBaseInfo::_SetVisable( const bool bVisable )
{
	if(bVisable)
	{
		//当Ui显示的时候
		s_CUI_ID_FRAME_CampBattleCountry.OnInit();
		s_CUI_ID_FRAME_CampBattleGuild.OnInit();
		s_CUI_ID_FRAME_CampBattleGuildUnion.OnInit();
		s_CUI_ID_FRAME_CampBattleWorld.OnInit();

		ID_CHECKBOX_GuoWangOnCheckBoxCheck(m_pID_CHECKBOX_GuoWang,0);//优先显示国王战面板
		//ID_CHECKBOX_GuildOnCheckBoxCheck(m_pID_CHECKBOX_Guild,0);
		//ID_CHECKBOX_UnionOnCheckBoxCheck(m_pID_CHECKBOX_Union,0);
		//ID_CHECKBOX_WorldOnCheckBoxCheck(m_pID_CHECKBOX_World,0);
	}
	m_pID_FRAME_CampBattleBaseInfo->SetVisable( bVisable );
}
void CUI_ID_FRAME_CampBattleBaseInfo::InitializeAtEnterWorld()
{
	LoadUI();
	s_CUI_ID_FRAME_CampBattleCountry.OnInit();
	s_CUI_ID_FRAME_CampBattleGuild.OnInit();
	s_CUI_ID_FRAME_CampBattleGuildUnion.OnInit();
	s_CUI_ID_FRAME_CampBattleWorld.OnInit();
}