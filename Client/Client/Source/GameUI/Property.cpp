/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Code\RunTime\CLIENT\Data\UI\Property.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Property.h"
#include "ExpStage.h"
#include "PlayerRole.h"
#include "GameMain.h"
#include "../Player.h"
#include "Skill.h"
#include "SystemConfig.h"
#include "ActionUI.h"
#include "Task.h"
#include "baseProperty.h"

CUI_ID_FRAME_Property s_CUI_ID_FRAME_Property;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Property, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Property, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Property, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Property, ID_BUTTON_ActiionOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Property, ID_BUTTON_BaseOnButtonClick )
CUI_ID_FRAME_Property::CUI_ID_FRAME_Property()
// :CUIBase( eUI_OBJECT_Property )
{
	guardfunc;
	// SGuildMember
	ResetMembers();
}
void CUI_ID_FRAME_Property::ResetMembers()
{
	m_pID_FRAME_Property = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	
	m_pID_TEXT_Hp = NULL;
	m_pID_TEXT_Mp = NULL;
	m_pID_TEXT_Str = NULL;
	m_pID_TEXT_Def = NULL;
	m_pID_TEXT_LHandAtt = NULL;
	m_pID_TEXT_Hit = NULL;
	m_pID_TEXT_Frost = NULL;
	m_pID_TEXT_Blaze = NULL;
	m_pID_TEXT_Thunder = NULL;
	m_pID_TEXT_Poison = NULL;
	m_pID_BUTTON_Actiion = NULL;
	m_pID_BUTTON_Base = NULL;
	m_pID_TEXT_FrostAtt = NULL;
	m_pID_TEXT_BlazeAtt = NULL;
	m_pID_TEXT_ThunderAtt = NULL;
	m_pID_TEXT_PoisonAtt = NULL;
	m_pID_TEXT_MpAtk = NULL;

	m_bIsMySafe = true;
	unguard;
}


void CUI_ID_FRAME_Property::Refeash()
{
	guardfunc;
	if( m_bIsMySafe )
	{
		//const SCharBaseInfo	*pBaseInfo = thePlayerRole.m_pBaseInfo;
		char szTemp[eMAX_TEMP_BUFF] = {0};

		//Hp
		sprintf( szTemp, "%d/%d", thePlayerRole.GetData(CPlayerRole::TYPE_HP),thePlayerRole.GetData(CPlayerRole::TYPE_HPMAX)/*pBaseInfo->liveinfo.nHp, pBaseInfo->baseProperty.fightAttr.hpMax.final*/ );
		*m_pID_TEXT_Hp = szTemp;
		//Mp
		sprintf( szTemp, "%d/%d", thePlayerRole.GetData(CPlayerRole::TYPE_MP),thePlayerRole.GetData(CPlayerRole::TYPE_MPMAX) /*pBaseInfo->liveinfo.nMp, pBaseInfo->baseProperty.fightAttr.energyMax.final*/ );
		*m_pID_TEXT_Mp = szTemp;
		// Str
// 		sprintf( szTemp, "%d", pBaseInfo->baseProperty.fight.fPhysicsAttack.fFinal );
// 		*m_pID_TEXT_Str = szTemp;
		
	}
	unguard;
}
// Frame
bool CUI_ID_FRAME_Property::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_Property::OnFrameRender()
{
	guardfunc;
	return true;
	unguard;
}
// Button
bool CUI_ID_FRAME_Property::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Property )
		return false;
	SetVisable( false );
	return true;
}
// Button
bool CUI_ID_FRAME_Property::ID_BUTTON_ActiionOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_Property )
		return false;
	return true;
	unguard;
}
// Button
	bool CUI_ID_FRAME_Property::ID_BUTTON_BaseOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_Property )
		return false;
	s_CUI_ID_FRAME_BaseProperty.SetVisable( true );
	return true;
	unguard;
}


bool CUI_ID_FRAME_Property::_LoadUI()
{
	guardfunc;
	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\Property.meui" );
	if ( dwResult == 0 )
	{
			MESSAGE_BOX("[UI\\Property.UI]");
			return false;
	}
		else if ( dwResult != 357392 )
	{
		MESSAGE_BOX("[UI\\Property.UI]");
	}
	return DoControlConnect();
	unguard;
}

bool CUI_ID_FRAME_Property::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_Property, s_CUI_ID_FRAME_PropertyOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Property, s_CUI_ID_FRAME_PropertyOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_Property, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_PropertyID_BUTTON_CLOSEOnButtonClick );
	
	theUiManager.OnButtonClick( ID_FRAME_Property, ID_BUTTON_Actiion, s_CUI_ID_FRAME_PropertyID_BUTTON_ActiionOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Property, ID_BUTTON_Base, s_CUI_ID_FRAME_PropertyID_BUTTON_BaseOnButtonClick );

	m_pID_FRAME_Property = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Property );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_Property, ID_BUTTON_CLOSE );
	m_pID_TEXT_Hp = (ControlText*)theUiManager.FindControl( ID_FRAME_Property, ID_TEXT_Hp );
	m_pID_TEXT_Mp = (ControlText*)theUiManager.FindControl( ID_FRAME_Property, ID_TEXT_Mp );
	m_pID_TEXT_Str = (ControlText*)theUiManager.FindControl( ID_FRAME_Property, ID_TEXT_Str );
	m_pID_TEXT_Def = (ControlText*)theUiManager.FindControl( ID_FRAME_Property, ID_TEXT_Def );
	m_pID_TEXT_LHandAtt = (ControlText*)theUiManager.FindControl( ID_FRAME_Property, ID_TEXT_LHandAtt );
	m_pID_TEXT_Hit = (ControlText*)theUiManager.FindControl( ID_FRAME_Property, ID_TEXT_Hit );
	m_pID_TEXT_Frost = (ControlText*)theUiManager.FindControl( ID_FRAME_Property, ID_TEXT_Frost );
	m_pID_TEXT_Blaze = (ControlText*)theUiManager.FindControl( ID_FRAME_Property, ID_TEXT_Blaze );
	m_pID_TEXT_Thunder = (ControlText*)theUiManager.FindControl( ID_FRAME_Property, ID_TEXT_Thunder );
	m_pID_TEXT_Poison = (ControlText*)theUiManager.FindControl( ID_FRAME_Property, ID_TEXT_Poison );

	m_pID_BUTTON_Actiion = (ControlButton*)theUiManager.FindControl( ID_FRAME_Property, ID_BUTTON_Actiion );
	m_pID_BUTTON_Base = (ControlButton*)theUiManager.FindControl( ID_FRAME_Property, ID_BUTTON_Base );
	m_pID_TEXT_FrostAtt = (ControlText*)theUiManager.FindControl( ID_FRAME_Property, ID_TEXT_FrostAtt );
	m_pID_TEXT_BlazeAtt = (ControlText*)theUiManager.FindControl( ID_FRAME_Property, ID_TEXT_BlazeAtt );
	m_pID_TEXT_ThunderAtt = (ControlText*)theUiManager.FindControl( ID_FRAME_Property, ID_TEXT_ThunderAtt );
	m_pID_TEXT_PoisonAtt = (ControlText*)theUiManager.FindControl( ID_FRAME_Property, ID_TEXT_PoisonAtt );
	m_pID_TEXT_MpAtk = (ControlText*)theUiManager.FindControl( ID_FRAME_Property, ID_TEXT_MpAtk);
	assert( m_pID_FRAME_Property );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_TEXT_Hp );
	assert( m_pID_TEXT_Mp );
	assert( m_pID_TEXT_Str );
	assert( m_pID_TEXT_Def );
	assert( m_pID_TEXT_LHandAtt );
	assert( m_pID_TEXT_Hit );
	assert( m_pID_TEXT_Frost );
	assert( m_pID_TEXT_Blaze );
	assert( m_pID_TEXT_Thunder );
	assert( m_pID_TEXT_Poison );
	assert( m_pID_BUTTON_Actiion );
	assert( m_pID_BUTTON_Base );
	assert( m_pID_TEXT_FrostAtt );
	assert( m_pID_TEXT_BlazeAtt );
	assert( m_pID_TEXT_ThunderAtt );
	assert( m_pID_TEXT_PoisonAtt );
	assert( m_pID_TEXT_MpAtk );
	
	USE_SCRIPT( eUI_OBJECT_Property, this );

	return true;
	unguard;
}

bool CUI_ID_FRAME_Property::_UnLoadUI()
{
	guardfunc;
	CLOSE_SCRIPT( eUI_OBJECT_Property );
	ResetMembers();
	return theUiManager.RemoveFrame( "data\\ui\\Property.meui" );
	unguard;
}

bool CUI_ID_FRAME_Property::_IsVisable()
{
	guardfunc;
	if( !m_pID_FRAME_Property )
		return false;
	return m_pID_FRAME_Property->IsVisable();
	unguard;
}

void CUI_ID_FRAME_Property::_SetVisable( const bool bVisable )
{
	guardfunc;
	if( !m_pID_FRAME_Property )
		return;
	CUIBase::SetVisable( bVisable );
	m_pID_FRAME_Property->SetVisable( bVisable );
	unguard;
}


























