/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\Hero\Program\trunk\Client\Bin\Data\Ui\Team_Player.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Team_Player.h"
#include "GameMain.h"
#include "RbtnMenu.h"
#include "PlayerRole.h"
#include "PlayerMgr.h"
#include "Target.h"

#include "NetworkInput.h"
#include "ChatInfoBox.h"
#include "../player.h"
#include "XmlStringLanguage.h"
#include "Group.h"
#include "MeUi/ExpressionManager.h"
#include "core/Name.h"
#include "MeTerrain/stdafx.h"
#include "color_config.h"
#include "ui/MiniMapUI.h"
#include "packet_interface.h"
//#include "Launcher/DataLauncher.h"
#include "Common.h"
#include "Create.h"
#include "CountryFunction.h"
#include "ItemHero.h"
#include "PlayerInfoMgr.h"

#define	CHAT_INFO_WIDTH_MAX	32
#define SHOW_TIME_COOLING	10*1000
#ifndef TEAMPLAYER_OFFSET_Y
#define TEAMPLAYER_OFFSET_Y 170
#endif
#ifndef TEAMPLAYER_SPACING
#define TEAMPLAYER_SPACING 70
#endif

extern const char* GetMPTypeString( int nProfession );

Vector2 teamPlayerFramePos[10] = 
{
	Vector2(-20,160),
	Vector2(-20,260),
	Vector2(-20,360),
	Vector2(-20,460),
	Vector2(-20,560),
	Vector2(-20,660),
	Vector2(-20,760),
	Vector2(-20,860),
	Vector2(-20,960),
	Vector2(-20,1060),
};

TeamPlayerFrameMgr TeamPlayerFrameManage;
MAP_FRAME_RUN_INDEX( TeamPlayerFrameManage, OnFrameRunIndexedFrame )
MAP_FRAME_RENDER_INDEX( TeamPlayerFrameManage, OnFrameRenderIndexedFrame )
MAP_ICON_DRAG_ON_CALLBACK( TeamPlayerFrameManage, ID_LISTIMG_StatusOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( TeamPlayerFrameManage, ID_LISTIMG_StatusOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( TeamPlayerFrameManage, ID_LISTIMG_StatusOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( TeamPlayerFrameManage, ID_LISTIMG_StatusOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( TeamPlayerFrameManage, ID_BUTTON_kickOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( TeamPlayerFrameManage, ID_BUTTON_agreeOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( TeamPlayerFrameManage, ID_BUTTON_refuseOnButtonClick )
CUI_ID_FRAME_Team_Player::CUI_ID_FRAME_Team_Player(int frameIndex)
{
	// Member
	ResetMembers();
	m_pObject				= NULL;
	m_FrameIndex			= frameIndex;
	MeSprintf_s(szFrameID,sizeof(szFrameID)/sizeof(char) - 1,"%s%d",ID_FRAME_Team_Player,frameIndex);
}

void CUI_ID_FRAME_Team_Player::ResetMembers()
{
	m_pID_FRAME_Team_Player = NULL;
	m_pID_LISTIMG_Status = NULL;
	m_pID_BUTTON_kick = NULL;
	m_pID_PROGRESS_Hp = NULL;
	m_pID_PROGRESS_Mp = NULL;
	m_pID_TEXT_Name = NULL;
	m_pID_TEXT_LVL = NULL;
	m_pID_PICTURE_talktipPic = NULL;
	m_pID_TEXT_talktip = NULL;
	m_pID_PICTURE_chang_assignmodePic = NULL;
	m_pID_TEXT_chang_assignmode = NULL;
	m_pID_BUTTON_agree = NULL;
	m_pID_PICTURE_Corps = NULL;
	m_pID_PICTURE_Header2 = NULL;
	m_pID_PICTURE_Face = NULL;
	m_pID_PICTURE_choise1 = NULL;
	m_pID_PICTURE_Pt1 = NULL;
	m_pID_PROGRESS_Pt1 = NULL;
	m_pID_PICTURE_choise1pt = NULL;
	m_pID_PICTURE_sword = NULL;
	m_pID_PICTURE_staff = NULL;
	m_pID_PICTURE_spear = NULL;
	m_pID_PICTURE_Fan = NULL;
	m_pID_PICTURE_Bow = NULL;
	m_pID_BUTTON_refuse = NULL;
	m_pID_TEXT_ShowHp = NULL;
	m_pID_PICTURE_Tip = NULL;
	m_pID_TEXT_ShowMp = NULL;
	m_pID_PICTURE_Hair = NULL;

	_nID = -1;		//玩家id
	_nPetID = -1;	// pet id
	tmStartShow = 0;
}
// Frame
bool CUI_ID_FRAME_Team_Player::OnFrameRun()
{
	return true;
}

ControlPicture* CUI_ID_FRAME_Team_Player::GetPICTURE_choise1()
{
	if( !m_pID_FRAME_Team_Player )
		return NULL;
	return m_pID_PICTURE_choise1;
}

ControlPicture* CUI_ID_FRAME_Team_Player::GetPICTURE_choise1pt()
{
	if( !m_pID_FRAME_Team_Player )
		return NULL;
	return m_pID_PICTURE_choise1pt;
}

ControlProgress* CUI_ID_FRAME_Team_Player::GetPROGRESS_Hp()
{
	if( !m_pID_FRAME_Team_Player )
		return NULL;
	return m_pID_PROGRESS_Hp;
}

ControlProgress* CUI_ID_FRAME_Team_Player::GetPROGRESS_Mp()
{
	if( !m_pID_FRAME_Team_Player )
		return NULL;
	return m_pID_PROGRESS_Mp;
}

ControlText* CUI_ID_FRAME_Team_Player::GetTEXT_ShowHp()
{
	if( !m_pID_FRAME_Team_Player )
		return NULL;
	return m_pID_TEXT_ShowHp;
}

ControlText* CUI_ID_FRAME_Team_Player::GetTEXT_ShowMp()
{
	if( !m_pID_FRAME_Team_Player )
		return NULL;
	return m_pID_TEXT_ShowMp;
}

ControlText* CUI_ID_FRAME_Team_Player::GetTEXT_Name()
{
	if( !m_pID_FRAME_Team_Player )
		return NULL;
	return m_pID_TEXT_Name;
}

ControlPicture* CUI_ID_FRAME_Team_Player::GetPICTURE_Header2()
{
	if( !m_pID_FRAME_Team_Player )
		return NULL;
	return m_pID_PICTURE_Header2;
}

ControlText* CUI_ID_FRAME_Team_Player::GetTEXT_LVL()
{
	if( !m_pID_FRAME_Team_Player )
		return NULL;
	return m_pID_TEXT_LVL;
}

ControlListImage* CUI_ID_FRAME_Team_Player::GetLISTIMG_Status()
{
	if( !m_pID_FRAME_Team_Player )
		return NULL;
	return m_pID_LISTIMG_Status;
}

ControlProgress* CUI_ID_FRAME_Team_Player::GetPROGRESS_Pt1()
{
	if( !m_pID_FRAME_Team_Player )
		return NULL;
	return m_pID_PROGRESS_Pt1;
}

ControlText* CUI_ID_FRAME_Team_Player::GetTEXT_talktip()
{
	if( !m_pID_FRAME_Team_Player )
		return NULL;
	return m_pID_TEXT_talktip;
}

ControlPicture* CUI_ID_FRAME_Team_Player::GetPICTURE_talktipPic()
{
	if( !m_pID_FRAME_Team_Player )
		return NULL;
	return m_pID_PICTURE_talktipPic;
}

bool CUI_ID_FRAME_Team_Player::OnFrameRender()
{
	guardfunc;
	RECT rect;
	m_pID_FRAME_Team_Player->GetRealRect(&rect);
	POINT ptMouse = theUiManager.m_ptMoust;
	if(PtInRect(&rect, ptMouse))
	{

		TeamInfo* pInfo = thePlayerRole.GetTeamInfo(_nID);
		if (!pInfo)
		{
			return false;
		}
		if (!pInfo->bOnline)
		{
			m_pID_PICTURE_Tip->setTip(theXmlString.GetString(eText_TeamOffLine), DT_LEFT);
			return true;
		}
		char ShareTip[1024];
		char Tip[2048];
		int stringId = eText_CannotShareExp;
		TeamInfo* pMeInfo = thePlayerRole.GetMeTeamInfo();
		if (pMeInfo && pMeInfo->nMapID == pInfo->nMapID)
		{
			CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
			if( pMe )
			{
				float fx,fy;
				pMe->GetPos(&fx,&fy,NULL);
				float dis = sqrt((pInfo->fx - fx)*(pInfo->fx - fx) + (pInfo->fy - fy)* (pInfo->fy - fy));
				if(dis < TEAM_EXP_DIS)
				{
					stringId = eText_ShareExp;
				}
			}
		}

		{
			int nTeamMapId = EctypeId2MapId(pInfo->nMapID);
			CWorldTile* pTeamerTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(nTeamMapId);

			if( pTeamerTile )
			{
                char szProfession[MAX_PATH] = {0};
                MeSprintf_s( szProfession, sizeof( szProfession ) / sizeof( char ) - 1, theXmlString.GetString( eClient_PlayerTip_Profession ),
                    CountryFunction::GetProfessionByID( pInfo->usProfession ).c_str() );
				MeSprintf_s( ShareTip, sizeof( ShareTip ) /sizeof( char ) - 1, theXmlString.GetString(stringId), pTeamerTile->GetTileName() );
                MeSprintf_s( Tip, sizeof( Tip ) /sizeof(char) - 1,"%s\n%s:%d/%d\n%s:%d/%d\n%s", szProfession, theXmlString.GetString( eTip_sAddHPMax ),
                    pInfo->nHp,pInfo->nMaxHp, GetMPTypeString( pInfo->usProfession ), pInfo->nMp, pInfo->nMaxMp, ShareTip );
				m_pID_PICTURE_Tip->setTip( Tip, DT_LEFT );
			}
		}

	}

	return true;
	unguard;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Team_Player::ID_LISTIMG_StatusOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_Team_Player )
		return false;
	return false;
}
bool CUI_ID_FRAME_Team_Player::ID_LISTIMG_StatusOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Team_Player )
		return false;
	return false;
}
bool CUI_ID_FRAME_Team_Player::ID_LISTIMG_StatusOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Team_Player )
		return false;
	return false;
}
bool CUI_ID_FRAME_Team_Player::ID_LISTIMG_StatusOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_Team_Player )
		return false;
	return false;
}
// Button
bool CUI_ID_FRAME_Team_Player::ID_BUTTON_kickOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_Team_Player )
		return false;
	MsgKickFromTeam msg;
	msg.dwWho = _nID;
	if (msg.dwWho != -1)
	{
		GettheNetworkInput().SendMsg( &msg );
	}

	m_pID_BUTTON_kick->SetVisable(false);
	return true;
	unguard;
}
// Button
bool CUI_ID_FRAME_Team_Player::ID_BUTTON_agreeOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Team_Player )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_Team_Player::ID_BUTTON_refuseOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Team_Player )
		return false;
	return true;
}

// 装载UI
bool CUI_ID_FRAME_Team_Player::_LoadUI()
{
	m_pObject = theUiManager.AddFrameByIndex( "Data\\UI\\Team_Player.MEUI" ,m_FrameIndex,true);
	if ( m_pObject == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Team_Player.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Team_Player::DoControlConnect()
{
	theUiManager.OnFrameRunIndexedFrame( szFrameID, TeamPlayerFrameManageOnFrameRunIndexedFrame );
	theUiManager.OnFrameRenderIndexedFrame( szFrameID, TeamPlayerFrameManageOnFrameRenderIndexedFrame );
	theUiManager.OnIconDragOn( szFrameID, ID_LISTIMG_Status, TeamPlayerFrameManageID_LISTIMG_StatusOnIconDragOn );
	theUiManager.OnIconLDBClick( szFrameID, ID_LISTIMG_Status, TeamPlayerFrameManageID_LISTIMG_StatusOnIconLDBClick );
	theUiManager.OnIconButtonClick( szFrameID, ID_LISTIMG_Status, TeamPlayerFrameManageID_LISTIMG_StatusOnIconButtonClick );
	theUiManager.OnIconRButtonUp( szFrameID, ID_LISTIMG_Status, TeamPlayerFrameManageID_LISTIMG_StatusOnIconRButtonUp );
	theUiManager.OnButtonClick( szFrameID, ID_BUTTON_kick, TeamPlayerFrameManageID_BUTTON_kickOnButtonClick );
	theUiManager.OnButtonClick( szFrameID, ID_BUTTON_agree, TeamPlayerFrameManageID_BUTTON_agreeOnButtonClick );
	theUiManager.OnButtonClick( szFrameID, ID_BUTTON_refuse, TeamPlayerFrameManageID_BUTTON_refuseOnButtonClick );

	m_pID_FRAME_Team_Player = (ControlFrame*)theUiManager.FindFrame( szFrameID );
	m_pID_LISTIMG_Status = (ControlListImage*)theUiManager.FindControl( szFrameID, ID_LISTIMG_Status );
	m_pID_BUTTON_kick = (ControlButton*)theUiManager.FindControl( szFrameID, ID_BUTTON_kick );
	m_pID_PROGRESS_Hp = (ControlProgress*)theUiManager.FindControl( szFrameID, ID_PROGRESS_Hp );
	m_pID_PROGRESS_Mp = (ControlProgress*)theUiManager.FindControl( szFrameID, ID_PROGRESS_Mp );
	m_pID_TEXT_Name = (ControlText*)theUiManager.FindControl( szFrameID, ID_TEXT_Name );
	m_pID_TEXT_LVL = (ControlText*)theUiManager.FindControl( szFrameID, ID_TEXT_LVL );
	m_pID_PICTURE_talktipPic = (ControlPicture*)theUiManager.FindControl( szFrameID, ID_PICTURE_talktipPic );
	m_pID_TEXT_talktip = (ControlText*)theUiManager.FindControl( szFrameID, ID_TEXT_talktip );
	m_pID_PICTURE_chang_assignmodePic = (ControlPicture*)theUiManager.FindControl( szFrameID, ID_PICTURE_chang_assignmodePic );
	m_pID_TEXT_chang_assignmode = (ControlText*)theUiManager.FindControl( szFrameID, ID_TEXT_chang_assignmode );
	m_pID_BUTTON_agree = (ControlButton*)theUiManager.FindControl( szFrameID, ID_BUTTON_agree );
	m_pID_PICTURE_Corps = (ControlPicture*)theUiManager.FindControl( szFrameID, ID_PICTURE_Corps );
	m_pID_PICTURE_Header2 = (ControlPicture*)theUiManager.FindControl( szFrameID, ID_PICTURE_Header2 );
	m_pID_PICTURE_Face = (ControlPicture*)theUiManager.FindControl( szFrameID, ID_PICTURE_Face );
	m_pID_PICTURE_choise1 = (ControlPicture*)theUiManager.FindControl( szFrameID, ID_PICTURE_choise1 );
	m_pID_PICTURE_Pt1 = (ControlPicture*)theUiManager.FindControl( szFrameID, ID_PICTURE_Pt1 );
	m_pID_PROGRESS_Pt1 = (ControlProgress*)theUiManager.FindControl( szFrameID, ID_PROGRESS_Pt1 );
	m_pID_PICTURE_choise1pt = (ControlPicture*)theUiManager.FindControl( szFrameID, ID_PICTURE_choise1pt );
	m_pID_PICTURE_sword = (ControlPicture*)theUiManager.FindControl( szFrameID, ID_PICTURE_sword );
	m_pID_PICTURE_staff = (ControlPicture*)theUiManager.FindControl( szFrameID, ID_PICTURE_staff );
	m_pID_PICTURE_spear = (ControlPicture*)theUiManager.FindControl( szFrameID, ID_PICTURE_spear );
	m_pID_PICTURE_Fan = (ControlPicture*)theUiManager.FindControl( szFrameID, ID_PICTURE_Fan );
	m_pID_PICTURE_Bow = (ControlPicture*)theUiManager.FindControl( szFrameID, ID_PICTURE_Bow );
	m_pID_BUTTON_refuse = (ControlButton*)theUiManager.FindControl( szFrameID, ID_BUTTON_refuse );
	m_pID_TEXT_ShowHp = (ControlText*)theUiManager.FindControl( szFrameID, ID_TEXT_ShowHp );
	m_pID_PICTURE_Tip = (ControlPicture*)theUiManager.FindControl( szFrameID, ID_PICTURE_Tip );
	m_pID_TEXT_ShowMp = (ControlText*)theUiManager.FindControl( szFrameID, ID_TEXT_ShowMp );
	m_pID_PICTURE_Hair = (ControlPicture*)theUiManager.FindControl( szFrameID, ID_PICTURE_Hair );
	assert( m_pID_FRAME_Team_Player );
	assert( m_pID_LISTIMG_Status );
	assert( m_pID_BUTTON_kick );
	assert( m_pID_PROGRESS_Hp );
	assert( m_pID_PROGRESS_Mp );
	assert( m_pID_TEXT_Name );
	assert( m_pID_TEXT_LVL );
	assert( m_pID_PICTURE_talktipPic );
	assert( m_pID_TEXT_talktip );
	assert( m_pID_PICTURE_chang_assignmodePic );
	assert( m_pID_TEXT_chang_assignmode );
	assert( m_pID_BUTTON_agree );
	assert( m_pID_PICTURE_Corps );
	assert( m_pID_PICTURE_Header2 );
	assert( m_pID_PICTURE_Face );
	assert( m_pID_PICTURE_choise1 );
	assert( m_pID_PICTURE_Pt1 );
	assert( m_pID_PROGRESS_Pt1 );
	assert( m_pID_PICTURE_choise1pt );
	assert( m_pID_PICTURE_sword );
	assert( m_pID_PICTURE_staff );
	assert( m_pID_PICTURE_spear );
	assert( m_pID_PICTURE_Fan );
	assert( m_pID_PICTURE_Bow );
	assert( m_pID_BUTTON_refuse );
	assert( m_pID_TEXT_ShowHp );
	assert( m_pID_PICTURE_Tip );
	assert( m_pID_TEXT_ShowMp );
	assert( m_pID_PICTURE_Hair );
	m_pID_BUTTON_kick->SetVisable(false);
	m_pID_PICTURE_choise1->SetVisable(false);
	m_pID_PICTURE_Pt1->SetVisable(false);
	m_pID_PROGRESS_Pt1->SetVisable(false);
	m_pID_PICTURE_choise1pt->SetVisable(false);
	m_pID_PICTURE_sword->SetVisable(false);
	m_pID_PICTURE_staff->SetVisable(false);
	m_pID_PICTURE_spear->SetVisable(false);
	m_pID_PICTURE_Fan->SetVisable(false);
	m_pID_PICTURE_Bow->SetVisable(false);
	m_pID_BUTTON_refuse->SetVisable(false);
	m_pID_BUTTON_agree->SetVisable(false);
	m_pID_PICTURE_chang_assignmodePic->SetVisable(false);
	m_pID_PICTURE_chang_assignmodePic->SetMsgHoldup(false);
	m_pID_TEXT_chang_assignmode->SetVisable(false);
	m_pID_TEXT_chang_assignmode->SetMsgHoldup(false);
	m_pID_TEXT_talktip->SetVisable(false);
	m_pID_PICTURE_talktipPic->SetVisable(false);
	m_pID_PICTURE_Header2->SetVisable( false );

	m_pID_PICTURE_Tip->setShowTip(true);

	m_pID_FRAME_Team_Player->SetOnRBtnDown( OnButtonClickHead );
	m_pID_FRAME_Team_Player->SetOnClickFun( OnSelectLookPlayer );
	m_pID_PICTURE_Pt1->SetButtonClickFun(OnSelectLockPet);

	m_pID_TEXT_talktip->SetText("Talk"); // 计算高度用的

	S_BaseData* pData = m_pID_FRAME_Team_Player->GetData();
	int h = pData->m_rcRealSize.bottom - pData->m_rcRealSize.top;
	pData->m_rcRealSize.top = TEAMPLAYER_OFFSET_Y + m_FrameIndex * TEAMPLAYER_SPACING;
	pData->m_rcRealSize.bottom = pData->m_rcRealSize.top + h;

    CreateProgressAni();

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Team_Player::_UnLoadUI()
{
	ResetMembers();
	bool ret = theUiManager.RemoveFrame( m_pObject );
	m_pObject = NULL;
	return ret;
}
// 是否可视
bool CUI_ID_FRAME_Team_Player::_IsVisable()
{
	if( !m_pID_FRAME_Team_Player )
		return false;
	return m_pID_FRAME_Team_Player->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Team_Player::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_Team_Player )
		return;
	m_pID_FRAME_Team_Player->SetVisable( bVisable );
}

	void CUI_ID_FRAME_Team_Player::showProfessionIcon( int profession )
	{
		if( !m_pID_FRAME_Team_Player )
			return;
		if( profession >= EArmType_MaxSize && profession < 0)
			return; 

	switch( profession )
	{
	case EArmType_Warrior:
		{
			m_pID_PICTURE_spear->SetVisable(true);
			m_pID_PICTURE_staff->SetVisable(false);
			m_pID_PICTURE_Fan->SetVisable(false);
			m_pID_PICTURE_sword->SetVisable(false);
			m_pID_PICTURE_Bow->SetVisable(false);
		}
		break;
	case EArmType_Mage:
		{
			m_pID_PICTURE_spear->SetVisable(false);
			m_pID_PICTURE_staff->SetVisable(true);
			m_pID_PICTURE_Fan->SetVisable(false);
			m_pID_PICTURE_sword->SetVisable(false);
			m_pID_PICTURE_Bow->SetVisable(false);
		}
		break;
	case EArmType_Taoist:
		{
			m_pID_PICTURE_spear->SetVisable(false);
			m_pID_PICTURE_staff->SetVisable(false);
			m_pID_PICTURE_Fan->SetVisable(true);
			m_pID_PICTURE_sword->SetVisable(false);
			m_pID_PICTURE_Bow->SetVisable(false);
		}
		break;
	case EArmType_Assassin:
		{
			m_pID_PICTURE_spear->SetVisable(false);
			m_pID_PICTURE_staff->SetVisable(false);
			m_pID_PICTURE_Fan->SetVisable(false);
			m_pID_PICTURE_sword->SetVisable(true);
			m_pID_PICTURE_Bow->SetVisable(false);
		}
		break;
	case EArmType_Hunter:
		{
			m_pID_PICTURE_spear->SetVisable(false);
			m_pID_PICTURE_staff->SetVisable(false);
			m_pID_PICTURE_Fan->SetVisable(false);
			m_pID_PICTURE_sword->SetVisable(false);
			m_pID_PICTURE_Bow->SetVisable(true);
		}
		break;
	}

}

void CUI_ID_FRAME_Team_Player::SetVisablePetUI( bool v )
{
	if( !m_pID_FRAME_Team_Player )
		return;
	m_pID_PICTURE_Pt1->SetVisable(v);
	m_pID_PROGRESS_Pt1->SetVisable(v);
}

bool CUI_ID_FRAME_Team_Player::Refreah()
{
	if( !m_pID_FRAME_Team_Player )
		return false;
	return true;
}

void CUI_ID_FRAME_Team_Player::setAssignMode_willChange( unsigned char mode )
{
	if( !m_pID_FRAME_Team_Player )
		return;

	switch( mode )
	{
	case AssignMode_FreeMode:
		m_pID_TEXT_chang_assignmode->SetText( theXmlString.GetString(eTextPlayer_Change_AssignMode0) );
		break;
	case AssignMode_Team:
		m_pID_TEXT_chang_assignmode->SetText( theXmlString.GetString(eTextPlayer_Change_AssignMode1) );
		break;
	case AssignMode_Random:
		m_pID_TEXT_chang_assignmode->SetText( theXmlString.GetString(eTextPlayer_Change_AssignMode2) );
		break;
	case AssignMode_Assign:
		m_pID_TEXT_chang_assignmode->SetText( theXmlString.GetString(eTextPlayer_Change_AssignMode3) );
		break;
	}

}

void CUI_ID_FRAME_Team_Player::showChange_assignModeUI( bool bShow )
{
	guardfunc;
	if( !m_pID_FRAME_Team_Player )
		return;
	m_pID_TEXT_chang_assignmode->SetVisable(bShow);
	m_pID_BUTTON_agree->SetVisable(bShow);
	m_pID_BUTTON_refuse->SetVisable(bShow);
	m_pID_PICTURE_chang_assignmodePic->SetVisable(bShow);
	unguard;

}

bool CUI_ID_FRAME_Team_Player::OnAgree_ChangeAssignMode( ControlObject* pSender )
{
	guardfunc;
	//发送同意消息
	MsgAckChangeAssignModeAnswer msg;
	msg.answer = MsgAckChangeAssignModeAnswer::ResultAgree;
	GettheNetworkInput().SendMsg( &msg );

	showChange_assignModeUI(false);
	return true;
	unguard;

}

bool CUI_ID_FRAME_Team_Player::OnRefuse_ChangeAssignMode( ControlObject* pSender )
{
	guardfunc;
	MsgAckChangeAssignModeAnswer msg;
	msg.answer = MsgAckChangeAssignModeAnswer::ResultRefuse;
	GettheNetworkInput().SendMsg( &msg );
	//发送拒绝消息
	showChange_assignModeUI(false);
	return true;
	unguard;
}

void CUI_ID_FRAME_Team_Player::SetPicHeader( bool bHeader )
{
	if( !m_pID_FRAME_Team_Player )
		return;

	m_pID_PICTURE_Hair->SetVisable( true );
	m_pID_PICTURE_Corps->SetVisable( false );

	if( thePlayerRole.m_bCorps )
		m_pID_PICTURE_Hair->SetVisable(false);
	else
		m_pID_PICTURE_Corps->SetVisable( bHeader );

}

void CUI_ID_FRAME_Team_Player::setInfo( int nID, int nSex )
{
	guardfunc;
	if( !m_pID_FRAME_Team_Player )
		return;
	_nID = nID;
	TeamInfo* pInfo = thePlayerRole.GetTeamInfo(_nID);
	if (pInfo ==  NULL)
	{
		return;
	}

	char sex[2][32] = { "Male", "Female" };

	int hairId = pInfo->nHairId;
	int faceId = pInfo->nFaceId;

	char filename[256] = {0};

	bool bGrey = true;
	if (pInfo->bOnline)
	{
		TeamInfo* pMeInfo = thePlayerRole.GetMeTeamInfo();
		if (pMeInfo && ( pMeInfo->nMapID == pInfo->nMapID ) )
		{
			CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
			if( pMe )
			{
				float fx,fy;
				pMe->GetPos(&fx,&fy,NULL);
				float dis = sqrt((pInfo->fx - fx)*(pInfo->fx - fx) + (pInfo->fy - fy)* (pInfo->fy - fy));
				if(dis < TEAM_EXP_DIS)
				{
					bGrey = false;
				}
			}
		}
	}

    //modified by ZhuoMeng.Hu		[9/19/2010]
    //std::string portraitName = s_CUI_ID_FRAME_CREATE.GetPortraitName( nSex, pInfo->nHeadPicId, bGrey );
    //portraitName = "Data\\Ui\\" + portraitName;
    //m_pID_PICTURE_Face->SetPicName( portraitName.c_str() );


	if (!bGrey)
	{
		MeSprintf_s(filename, sizeof(filename)/sizeof(char) - 1, "%s/Data/Ui/HeadPicture/Player/%sHairHead%d.dds",
			GetRootPath(), sex[nSex], hairId);
	}
	else
	{
		MeSprintf_s(filename, sizeof(filename)/sizeof(char) - 1, "%s/Data/Ui/HeadPicture/Player/%sHairHeadGrey%d.dds",
			GetRootPath(), sex[nSex], hairId);
	}

	f_Handle* fp = packet_namespace::w_fopen(filename, "r");
	if (fp)
	{
		m_pID_PICTURE_Hair->SetPicName(filename);
		packet_namespace::w_fclose(fp);
	}
	else
	{	
		if (nSex == 0)
		{
			if (!bGrey)
			{
				m_pID_PICTURE_Hair->SetPicName("Data/Ui/HeadPicture/Player/DefaultMale.dds");
			}
			else
			{
				m_pID_PICTURE_Hair->SetPicName("Data/Ui/HeadPicture/Player/DefaultMaleGrey.dds");
			}
		}
		else
		{
			if (!bGrey)
			{
				m_pID_PICTURE_Hair->SetPicName("Data/Ui/HeadPicture/Player/DefaultFemale.dds");
			}
			else
			{
				m_pID_PICTURE_Hair->SetPicName("Data/Ui/HeadPicture/Player/DefaultFemaleGrey.dds");
			}
		}
	}

	//todo：这里没做头像灰掉的处理
	if (!bGrey)
	{
		
		CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByName( pInfo->szName.c_str() );
		//主将头像不显示
		/*if (pPlayer && pPlayer->GetHeroID() != INVALID_HERO_ID)
		{
			CItemHero::SItemHero *itemHero = theItemHero.FindHeroByHeroID(pPlayer->GetHeroID());
			if (itemHero == NULL)
				MeSprintf_s(filename, sizeof(filename)/sizeof(char) - 1, "%s/Data/Ui/HeadPicture/Player/%sHairHead_%d_%d.dds",
					GetRootPath(), sex[nSex],hairId, faceId);
			else
			{
				PlayerInfoMgr::Instance()->GetPlayerHeadPic(pPlayer, filename);
			}
			
		}
		else*/
		{
			MeSprintf_s(filename, sizeof(filename)/sizeof(char) - 1, "%s/Data/Ui/HeadPicture/Player/%sHairHead_%d_%d.dds",
				GetRootPath(), sex[nSex],hairId, faceId);
		}
	}
	else
	{
		//MeSprintf_s(filename, sizeof(filename)/sizeof(char) - 1, "%s/Data/Ui/HeadPicture/Player/%sHairHead_%d_%d.dds",
		//	GetRootPath(), sex[nSex],hairId, faceId);
		CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByName( pInfo->szName.c_str() );
		//主将头像不显示
		/*if (pPlayer && pPlayer->GetHeroID() != INVALID_HERO_ID)
		{
			CItemHero::SItemHero *itemHero = theItemHero.FindHeroByHeroID(pPlayer->GetHeroID());
			if (itemHero == NULL)
				MeSprintf_s(filename, sizeof(filename)/sizeof(char) - 1, "%s/Data/Ui/HeadPicture/Player/%sHairHead_%d_%d.dds",
					GetRootPath(), sex[nSex],hairId, faceId);
			else
			{
				PlayerInfoMgr::Instance()->GetPlayerHeadPic(pPlayer, filename);
			}
		}
		else*/
		{
			MeSprintf_s(filename, sizeof(filename)/sizeof(char) - 1, "%s/Data/Ui/HeadPicture/Player/%sGreyHairHead_%d_%d.dds", 
				GetRootPath(), sex[nSex],hairId, faceId);
		}
		
	}

	fp = packet_namespace::w_fopen(filename, "r");
	if (fp)
	{
		m_pID_PICTURE_Face->SetPicName(filename);
		packet_namespace::w_fclose(fp);
	}
	else
	{	
		if (nSex == 0)
		{
			if (!bGrey)
			{
				m_pID_PICTURE_Face->SetPicName("Data/Ui/HeadPicture/Player/DefaultMale.dds");
			}
			else
			{
				m_pID_PICTURE_Face->SetPicName("Data/Ui/HeadPicture/Player/DefaultMaleGrey.dds");
			}
		}
		else
		{
			if (!bGrey)
			{
				m_pID_PICTURE_Face->SetPicName("Data/Ui/HeadPicture/Player/DefaultFemale.dds");
			}
			else
			{
				m_pID_PICTURE_Face->SetPicName("Data/Ui/HeadPicture/Player/DefaultFemaleGrey.dds");
			}
		}
	}

	unguard;

}

void CUI_ID_FRAME_Team_Player::updata()
{
	guardfunc;
	if( !m_pID_FRAME_Team_Player )
		return;

	clock_t tmNow = clock();
	if( tmStartShow )
	{
		if( tmNow - tmStartShow > SHOW_TIME_COOLING )
		{
			m_pID_TEXT_talktip->SetVisable(false);
			m_pID_PICTURE_talktipPic->SetVisable(false); 
			tmStartShow = 0;
		}
	}
	unguard;

}

void CUI_ID_FRAME_Team_Player::show_talktip( const char* talk )
{
	guardfunc;
	if( !m_pID_FRAME_Team_Player )
		return;

	std::string strInfo2 = talk;
	std::string strInfo = talk;
	//下面的是在干嘛？先注释掉，把strInfo直接设置为talk内容
	//int off = strInfo2.find( ':');
	//if( off != -1 )
	//	strInfo = strInfo2.substr( off + 1, strInfo2.length() - off - 1);

	m_pID_PICTURE_talktipPic->SetVisable(true);
	m_pID_TEXT_talktip->SetVisable(true);

	static RECT OldPicRC = m_pID_PICTURE_talktipPic->GetData()->m_rcRealSize;
	static RECT OldTextRC = m_pID_TEXT_talktip->GetData()->m_rcRealSize;
	static int nOldHeight = m_pID_TEXT_talktip->GetTextHeight();

	RECT PicRC = OldPicRC;
	RECT TextRC = OldTextRC;

	ExpressionManager::GetInstance().AddExpressionAni(strInfo);

	RECT rc = TextRC;
	rc.bottom = rc.top + m_pID_TEXT_talktip->GetFontSize() * 4;

	m_pID_TEXT_talktip->SetRealRect(&rc);
	m_pID_TEXT_talktip->SetText(strInfo);

	int nTextHeight = m_pID_TEXT_talktip->GetTextHeight();
	if (nTextHeight > nOldHeight)
	{
		int nAddHeight = nTextHeight - nOldHeight + m_pID_TEXT_talktip->GetFontSize();
		PicRC.bottom += nAddHeight;
		TextRC.bottom += nAddHeight;
	}

	m_pID_PICTURE_talktipPic->SetRealRect(&PicRC);

	m_pID_TEXT_talktip->SetRealRect(&TextRC);
	m_pID_TEXT_talktip->SetText(strInfo);

	tmStartShow = clock();

	unguard;

}

int CUI_ID_FRAME_Team_Player::GetTeamPlayerIdFromDBId( DWORD dwDBId )
{
	TeamInfo* pInfo = thePlayerRole.GetTeamInfo(dwDBId);
	if (!pInfo)
	{
		return -1;
	}
	const char* name = pInfo->szName.c_str();
	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByName(name);
	if (pPlayer)
	{
		return pPlayer->GetID();
	}
	return -1;
}

bool CUI_ID_FRAME_Team_Player::OnButtonClickHead( ControlObject* pSender )
{
	guardfunc;
	TeamPlayerFrameManage.HidePicChoise();

	CUI_ID_FRAME_Team_Player* pFrame = TeamPlayerFrameManage.GetTeamFrameByChildWidget(pSender);
	pFrame->SetVisablePetUI(false);

	pFrame->m_pID_PICTURE_choise1pt->SetVisable(false);


	pFrame->m_pID_PICTURE_choise1->SetVisable(true);

	int id = GetTeamPlayerIdFromDBId(pFrame->_nID);
	if (id != -1)
	{
		CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID(id);
		if(pPlayer->GetDistanceToRole() > PLAYER_RENDER_DIST_MAX )
		{
			id = -1;
		}
	}

	theHeroGame.GetPlayerMgr()->SetLockPlayerID(id);  
	s_CUI_ID_FRAME_Target.SetPlayer(id);

	TeamInfo* pInfo = thePlayerRole.GetTeamInfo(pFrame->_nID);
	assert (pInfo);
	{
		s_CUI_ID_FRAME_RBTNMENU.SetPrivateName( pInfo->szName.c_str() );
	}
	if( !s_CUI_ID_FRAME_RBTNMENU.IsVisable() )
		s_CUI_ID_FRAME_RBTNMENU.SetVisable(true,pInfo->bOnline);
	else
		s_CUI_ID_FRAME_RBTNMENU.SetVisable(false);

	RECT rc;
	pSender->GetRealRect(&rc);
	s_CUI_ID_FRAME_RBTNMENU.SetPos( rc.right + 5, rc.top);

	s_CUI_ID_FRAME_RBTNMENU.SetDBID( pFrame->_nID );



	return true;
	unguard;

}

bool CUI_ID_FRAME_Team_Player::OnSelectLookPlayer( ControlObject* pSender )
{
	guardfunc;
	if( !pSender )
		return true;

	CUI_ID_FRAME_Team_Player* pFrame = TeamPlayerFrameManage.GetTeamFrameByChildWidget(pSender);
	if (!pFrame || !pFrame->IsVisable())
		return false;
	TeamPlayerFrameManage.HidePicChoise();
	pFrame->m_pID_PICTURE_choise1pt->SetVisable(false);

	pFrame->m_pID_PICTURE_choise1->SetVisable(true);

	if(theHeroGame.GetPlayerMgr())
	{
		int id = GetTeamPlayerIdFromDBId(pFrame->_nID);
		theHeroGame.GetPlayerMgr()->SetLockPlayerID(id);  
		s_CUI_ID_FRAME_Target.SetPlayer(id);
	}


	return true;
	unguard;
}

bool CUI_ID_FRAME_Team_Player::OnSelectLockPet( ControlObject* pSender )
{
	guardfunc;
	CUI_ID_FRAME_Team_Player* pFrame = TeamPlayerFrameManage.GetTeamFrameByChildWidget(pSender);
	pFrame->m_pID_PICTURE_choise1->SetVisable(false); 

	pFrame->m_pID_PICTURE_Pt1->SetVisable(true);
	pFrame->m_pID_PROGRESS_Pt1->SetVisable(true);
	pFrame->m_pID_PICTURE_choise1pt->SetVisable(true);

	int id = GetTeamPlayerIdFromDBId(pFrame->_nID);
	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID(id);
	if (pPlayer)
	{
		pFrame->_nPetID = pPlayer->GetPetID();
		theHeroGame.GetPlayerMgr()->SetLockPlayerID(pFrame->_nPetID);
	}

	return true;
	unguard;

}

void CUI_ID_FRAME_Team_Player::CreateProgressAni()
{
    if( !IsUILoad() )
        return;

    char fullname[MAX_PATH] = {0};
    MeSprintf_s( fullname, sizeof( fullname ) / sizeof( char ) - 1, "%s\\data\\ui\\UIAni\\PlayerHp.2DAni", GetRootPath() );
    m_pID_PROGRESS_Hp->CreateAnimation( fullname );
}


//----------------------------------------------------------------
bool TeamPlayerFrameMgr::OnFrameRunIndexedFrame( int index )
{
	assert(mTeamFrameArr.size() > index);
	if(index < 0 || index >= mTeamFrameArr.size())
		return true;

	return mTeamFrameArr[index]->OnFrameRun();

}

bool TeamPlayerFrameMgr::OnFrameRenderIndexedFrame( int index )
{
	assert(mTeamFrameArr.size() > index);
	if(index < 0 || index >= mTeamFrameArr.size())
		return true;

	return mTeamFrameArr[index]->OnFrameRender();

}

bool TeamPlayerFrameMgr::ID_LISTIMG_StatusOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc )
{
	if(!pSender)
		return false;

	m_ActiveIndex = GetFrameIndexByChildWidget(pSender);

	if(m_ActiveIndex < 0 || m_ActiveIndex >= mTeamFrameArr.size())
		return false;

	if(!mTeamFrameArr[m_ActiveIndex]->IsVisable())
		return false;

	return mTeamFrameArr[m_ActiveIndex]->ID_LISTIMG_StatusOnIconDragOn(pSender,pMe,pItemDrag,pItemSrc);

}

bool TeamPlayerFrameMgr::ID_LISTIMG_StatusOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!pSender)
		return false;

	m_ActiveIndex = GetFrameIndexByChildWidget(pSender);

	if(m_ActiveIndex < 0 || m_ActiveIndex >= mTeamFrameArr.size())
		return false;

	if(!mTeamFrameArr[m_ActiveIndex]->IsVisable())
		return false;

	return mTeamFrameArr[m_ActiveIndex]->ID_LISTIMG_StatusOnIconLDBClick(pSender,pItem);
}

bool TeamPlayerFrameMgr::ID_LISTIMG_StatusOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!pSender)
		return false;

	m_ActiveIndex = GetFrameIndexByChildWidget(pSender);

	if(m_ActiveIndex < 0 || m_ActiveIndex >= mTeamFrameArr.size())
		return false;

	if(!mTeamFrameArr[m_ActiveIndex]->IsVisable())
		return false;

	return mTeamFrameArr[m_ActiveIndex]->ID_LISTIMG_StatusOnIconButtonClick(pSender,pItem);
}

bool TeamPlayerFrameMgr::ID_LISTIMG_StatusOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!pSender)
		return false;

	m_ActiveIndex = GetFrameIndexByChildWidget(pSender);

	if(m_ActiveIndex < 0 || m_ActiveIndex >= mTeamFrameArr.size())
		return false;

	if(!mTeamFrameArr[m_ActiveIndex]->IsVisable())
		return false;

	return mTeamFrameArr[m_ActiveIndex]->ID_LISTIMG_StatusOnIconRButtonUp(pSender,pItem);

}

bool TeamPlayerFrameMgr::ID_BUTTON_kickOnButtonClick( ControlObject* pSender )
{
	if(!pSender)
		return false;

	m_ActiveIndex = GetFrameIndexByChildWidget(pSender);

	if(m_ActiveIndex < 0 || m_ActiveIndex >= mTeamFrameArr.size())
		return false;

	return mTeamFrameArr[m_ActiveIndex]->ID_BUTTON_kickOnButtonClick(pSender);
}

bool TeamPlayerFrameMgr::ID_BUTTON_agreeOnButtonClick( ControlObject* pSender )
{
	if(!pSender)
		return false;

	m_ActiveIndex = GetFrameIndexByChildWidget(pSender);

	if(m_ActiveIndex < 0 || m_ActiveIndex >= mTeamFrameArr.size())
		return false;

	return mTeamFrameArr[m_ActiveIndex]->ID_BUTTON_agreeOnButtonClick(pSender);
}

bool TeamPlayerFrameMgr::ID_BUTTON_refuseOnButtonClick( ControlObject* pSender )
{
	if(!pSender)
		return false;

	m_ActiveIndex = GetFrameIndexByChildWidget(pSender);

	if(m_ActiveIndex < 0 || m_ActiveIndex >= mTeamFrameArr.size())
		return false;

	return mTeamFrameArr[m_ActiveIndex]->ID_BUTTON_refuseOnButtonClick(pSender);
}

int TeamPlayerFrameMgr::GetFrameIndexByChildWidget( ControlObject* pSender )
{
	if(!pSender)
		return -1;

	ControlObject* pFrame = pSender;
	while(pFrame->GetControlType() != Type_Frame)
	{
		pFrame = pFrame->GetFather();
	}
	assert(pFrame);
	ControlFrame* pConFrame = (ControlFrame*) pFrame;
	return pConFrame->GetIndex();

}

void TeamPlayerFrameMgr::Reset()
{
	for (int i = 0; i < mTeamFrameArr.size();++i)
	{
		mTeamFrameArr[i]->UnLoadUI();
		delete mTeamFrameArr[i];
	}
	mTeamFrameArr.clear();
	m_ActiveIndex = -1;
}

TeamPlayerFrameMgr::TeamPlayerFrameMgr()
{
	Reset();
}

TeamPlayerFrameMgr::~TeamPlayerFrameMgr()
{

}

CUI_ID_FRAME_Team_Player* TeamPlayerFrameMgr::GetActiveTeamFrame()
{
	if (m_ActiveIndex < 0 || m_ActiveIndex >= mTeamFrameArr.size())
	{
		return NULL;
	}
	return mTeamFrameArr[m_ActiveIndex];

}

void TeamPlayerFrameMgr::HidePicChoise()
{
	for (int i = 0; i < mTeamFrameArr.size(); ++i)
	{
		if( mTeamFrameArr[i]->GetPICTURE_choise1() )
			mTeamFrameArr[i]->GetPICTURE_choise1()->SetVisable(false);
	}

}

CUI_ID_FRAME_Team_Player* TeamPlayerFrameMgr::GetTeamFrameByIndex( int index )
{
	if (index < 0 || index >= mTeamFrameArr.size())
	{
		return NULL;
	}
	return mTeamFrameArr[index];

}

void TeamPlayerFrameMgr::SetVisable( const bool bVisable )
{
	for (int i = 0; i < mTeamFrameArr.size(); ++i)
	{
		mTeamFrameArr[i]->SetVisable(bVisable);
	}
}

CUI_ID_FRAME_Team_Player* TeamPlayerFrameMgr::GetTeamFrameById( int id )
{
	for (int i = 0; i < mTeamFrameArr.size(); ++i)
	{
		if (id == CUI_ID_FRAME_Team_Player::GetTeamPlayerIdFromDBId(mTeamFrameArr[i]->GetID()))
		{
			return mTeamFrameArr[i];
		}
	}
	return NULL;
}

CUI_ID_FRAME_Team_Player* TeamPlayerFrameMgr::GetTeamFrameByDBId( int dbid )
{
	for (int i = 0; i < mTeamFrameArr.size(); ++i)
	{
		if (dbid == (mTeamFrameArr[i]->GetID()))
		{
			return mTeamFrameArr[i];
		}
	}
	return NULL;

}

void TeamPlayerFrameMgr::updata()
{
	for (int i = 0; i < mTeamFrameArr.size(); ++i)
	{
		if (mTeamFrameArr[i]->IsVisable())
		{
			mTeamFrameArr[i]->updata();
		}
	}

}

CUI_ID_FRAME_Team_Player* TeamPlayerFrameMgr::CreateFrame( int index )
{
	assert(index == mTeamFrameArr.size());
	CUI_ID_FRAME_Team_Player* pNew = MeNew CUI_ID_FRAME_Team_Player(index);
	pNew->LoadUI();
	mTeamFrameArr.push_back(pNew);
	m_ActiveIndex = index;
	return pNew;
}

void TeamPlayerFrameMgr::HidePicChoisept()
{
	for (int i = 0; i < mTeamFrameArr.size(); ++i)
	{
		if( mTeamFrameArr[i]->GetPICTURE_choise1pt() )
			mTeamFrameArr[i]->GetPICTURE_choise1pt()->SetVisable(false);
	}

}

CUI_ID_FRAME_Team_Player* TeamPlayerFrameMgr::GetTeamFrameByChildWidget( ControlObject* pSender )
{
	ControlObject* pFrame = pSender;
	while(pFrame->GetControlType() != Type_Frame)
	{
		pFrame = pFrame->GetFather();
	}
	assert(pFrame);
	ControlFrame* pTemp = (ControlFrame*)pSender;
	m_ActiveIndex = pTemp->GetIndex();
	assert(m_ActiveIndex != -1);
	return GetTeamFrameByIndex(m_ActiveIndex);
}
