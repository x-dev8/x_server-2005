/********************************************************************
Created by UIEditor.exe
FileName: E:\Work\HeroRuntime\Client\UI\ActionUI.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ActionUI.h"
#include "Task.h"
#include "Property.h"
#include "ChatInfoBox.h"
#include "../Player.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Compound.h"
#include "InputBox.h"
#include "Helper.h"
#include "Pack.h"
#include "baseProperty.h"
#include "XmlStringLanguage.h"
#include "baseProperty.h"
#include "PrivateShop.h"
#include "FriendDlg.h"
#include "MessageBox.h"
#include "Group_Me.h"
#include "ui/Pet.h"
#include "ui/exmain.h"
#include "ui/Main.h"
#include "color_config.h"
#include "Cfg.h"
#include "ui/FriendDlg.h"
#include "ui/PickUp.h"
#include "ui/PrivateShop.h"
#include "WealthProtect.h"
#include "PreventWallow.h"
#include "Ui/InfoList.h"
#include "BargainingMessage.h"
#include "SystemStallage.h"
#include "GameSetting.h"

extern BOOL g_bMouseMoveMode;
extern BOOL	g_bTheRoleAttackLockTarget;
extern int g_nRoleCommonAttackStatus;

CUI_ID_FRAME_ActionUI s_CUI_ID_FRAME_ActionUI;
MAP_FRAME_RUN( s_CUI_ID_FRAME_ActionUI, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ActionUI, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActionUI, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActionUI, ID_BUTTON_PropertyOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActionUI, ID_BUTTON_TeskOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_ActionUI, ID_LISTIMG_DictateOnIconDragOn )
MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_ActionUI, ID_LISTIMG_DictateOnIconDragOff )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_ActionUI, ID_LISTIMG_DictateOnIconLDBClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_ActionUI, ID_LISTIMG_UIOnIconDragOn )
MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_ActionUI, ID_LISTIMG_UIOnIconDragOff )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_ActionUI, ID_LISTIMG_UIOnIconLDBClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_ActionUI, ID_LISTIMG_ActionOnIconDragOn )
MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_ActionUI, ID_LISTIMG_ActionOnIconDragOff )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_ActionUI, ID_LISTIMG_ActionOnIconLDBClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_ActionUI, ID_LISTIMG_UIOnIconRButtonUp );

CUI_ID_FRAME_ActionUI::CUI_ID_FRAME_ActionUI()
// :CUIBase(eUI_OBJECT_ActionUI)
{
	guardfunc;
	// SGuildMember
	m_pID_FRAME_ActionUI = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Property = NULL;
	m_pID_BUTTON_Tesk = NULL;
	m_pID_LISTIMG_Dictate = NULL;
	m_pID_LISTIMG_UI = NULL;
//	m_pID_LISTIMG_Action = NULL;

	m_nCurFunction = -1;
	m_enCursorType = MouseManager::Type_Arrow;
	unguard;
}
// Frame
bool CUI_ID_FRAME_ActionUI::OnFrameRun()
{
	guardfunc;
	return true;
	unguard;
}
bool CUI_ID_FRAME_ActionUI::OnFrameRender()
{
	guardfunc;
	return true;
	unguard;
}
// Button
bool CUI_ID_FRAME_ActionUI::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	SetVisable( false );
	return true;
	unguard;
}
// Button
bool CUI_ID_FRAME_ActionUI::ID_BUTTON_PropertyOnButtonClick( ControlObject* pSender )
{
	guardfunc;
//	SetVisable( false );
// 	SetVisableLayout();
	//s_CUI_ID_FRAME_BaseProperty.SetVisableLayout();
	return true;
	unguard;
}
// Button
bool CUI_ID_FRAME_ActionUI::ID_BUTTON_TeskOnButtonClick( ControlObject* pSender )
{
	guardfunc;
///	SetVisable( false );
// 	SetVisableLayout();
	//s_CUI_ID_FRAME_BaseProperty.SetVisableLayout();
	return true;
	unguard;
}
// ListImg / ListEx
bool CUI_ID_FRAME_ActionUI::ID_LISTIMG_DictateOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														   ControlIconDrag::S_ListImg* pItemDrag,
														   ControlIconDrag::S_ListImg* pItemSrc )
{
	guardfunc;
	return false;
	unguard;
}
bool CUI_ID_FRAME_ActionUI::ID_LISTIMG_DictateOnIconDragOff( ControlObject* pSender, ControlObject* pMe,
															ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
	return false;
	unguard;
}
bool CUI_ID_FRAME_ActionUI::ID_LISTIMG_DictateOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
	return false;
	unguard;
}

// ListImg / ListEx
bool CUI_ID_FRAME_ActionUI::ID_LISTIMG_UIOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													  ControlIconDrag::S_ListImg* pItemDrag,
													  ControlIconDrag::S_ListImg* pItemSrc )
{
	guardfunc;
	return false;
	unguard;
}
bool CUI_ID_FRAME_ActionUI::ID_LISTIMG_UIOnIconDragOff( ControlObject* pSender, ControlObject* pMe,
													   ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
	return false;
	unguard;
}
bool CUI_ID_FRAME_ActionUI::ID_LISTIMG_UIOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
	return false;
	unguard;
}

// ListImg / ListEx
bool CUI_ID_FRAME_ActionUI::ID_LISTIMG_ActionOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														  ControlIconDrag::S_ListImg* pItemDrag,
														  ControlIconDrag::S_ListImg* pItemSrc )
{
	guardfunc;
	return false;
	unguard;
}
bool CUI_ID_FRAME_ActionUI::ID_LISTIMG_ActionOnIconDragOff( ControlObject* pSender, ControlObject* pMe,
														   ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
	return false;
	unguard;
}
bool CUI_ID_FRAME_ActionUI::ID_LISTIMG_ActionOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
	return false;
	unguard;
}

/*
 *	Author 2012-9-24 zhuxincong
 *	DESC: 这个接口是提供给ID_BUTTON_PickOn 按钮的 主要是拾取距离的变更
 */
bool CUI_ID_FRAME_ActionUI::UsePick()
{
	guardfunc;
	switch (m_nCurFunction)
	{
		case CUI_ID_FRAME_BaseProperty::TYPE_PICK_ACTION:
			{
				CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
				CPlayer *pItem = pPlayerMgr->FindNearItemNpc();
				CPlayer *pMe = pPlayerMgr->GetMe();
				if(s_CUI_ID_FRAME_PickUp.IsVisable())
				{
					s_CUI_ID_FRAME_PickUp.PickAll();
				}
				else if ( pItem && pMe )
				{
					float xSrc = pMe->GetPos().x;
					float ySrc = pMe->GetPos().y;
					float xDst = pItem->GetPos().x;
					float yDst = pItem->GetPos().y;
					float x = xDst - xSrc;
					float y = yDst - ySrc;
					float Dist = sqrtf( x*x + y*y );
					float BodyDist = PickAuttonDistance;	//拾取距离
					if( Dist > BodyDist )
					{
						pPlayerMgr->MoveRoleToPlayer( pItem, TRUE, 0.0f, TRUE );
					}
					else
					{
						pMe->TryPickItem( pItem );
					}
				}
				m_nCurFunction = -1;
			}
			break;
		}
	m_nCurFunction = -1;
	return true;
	unguard;

}

bool CUI_ID_FRAME_ActionUI::UseFunction()
{
	guardfunc;
	switch( m_nCurFunction ) 
	{
	case CUI_ID_FRAME_BaseProperty::TYPE_SITDWON_ACTION:
		{
			if( !s_CUI_ID_FRAME_PrivateShop.IsOpening() )
			{
				if( theHeroGame.GetPlayerMgr())
					theHeroGame.GetPlayerMgr()->ProcessCommand("DoSitDown");
			}
			m_nCurFunction = -1;
		}
		break;

	case CUI_ID_FRAME_BaseProperty::TYPE_ATTACK_ACTION:
		{
			CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
			int nID  = pPlayerMgr->GetLockPlayerID();
			
			// 如果没有目标，就找个目标给他打
			if ( !static_cast<bool>( GameSetting::Instance()->GetLevel( GameSetting::eSSC_CLOSE_AUTO_SELECT ) ) && nID == -1)
			{
				pPlayerMgr->TabSelectPlayer();
				nID = pPlayerMgr->GetLockPlayerID();
			}

			if( nID != -1 )
			{	
				CPlayer *pTarget = pPlayerMgr->FindByID( nID );
				CPlayer* pMe = pPlayerMgr->GetMe();
				if( pTarget && pMe && pMe->canAttack(pTarget) )
				{
					pPlayerMgr->MoveRoleToPlayer( pTarget, FALSE, 0.0f, TRUE );

					if( !g_bMouseMoveMode )
					{
						//发消息通知服务器，攻击锁定的目标
						/*if (theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->IsMounting() && theHeroGame.GetPlayerMgr()->GetMe()->GetAutoDismount())
						{
							theHeroGame.GetPlayerMgr()->GetMe()->DisMount();
							theHeroGame.GetPlayerMgr()->DisDrome();
						}*/

						MsgAttackLockTarget	msg;
						g_bTheRoleAttackLockTarget = TRUE;

						if( GettheNetworkInput().SendMsg(&msg) == -1 )
						{
							//UI_MessageBox::Show( theXmlString.GetString(eText_Disconnect) );
						}
						g_nRoleCommonAttackStatus = CAS_ATTACK_AGAIN_WHEN_FAILED;
					}
					else
					{
						g_nRoleCommonAttackStatus = CAS_NEED_AUTO_ATTACK;
					}
				}
				else
				{
					if( pTarget && pTarget->IsNpc() )
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Player_Action, theXmlString.GetString( eClient_AddInfo_2slk_1 ) );
				}
			}
			m_nCurFunction = -1;
		}
		break;
	case CUI_ID_FRAME_BaseProperty::TYPE_PICK_ACTION:
		{
			CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
			CPlayer *pItem = pPlayerMgr->FindNearItemNpc();
			CPlayer *pMe = pPlayerMgr->GetMe();
			if(s_CUI_ID_FRAME_PickUp.IsVisable())
			{
				s_CUI_ID_FRAME_PickUp.PickAll();
			}
			else if ( pItem && pMe )
			{
				float xSrc = pMe->GetPos().x;
				float ySrc = pMe->GetPos().y;
				float xDst = pItem->GetPos().x;
				float yDst = pItem->GetPos().y;
				float x = xDst - xSrc;
				float y = yDst - ySrc;
				float Dist = sqrtf( x*x + y*y );
				float BodyDist = PackagePickDistance;	//拾取距离
				if( Dist > BodyDist )
				{
					pPlayerMgr->MoveRoleToPlayer( pItem, TRUE, 0.0f, TRUE );
				}
				else
				{
					pMe->TryPickItem( pItem );
				}
			}
			//if( pItem )
			//{	
			//	D3DXVECTOR3 vPos = pItem->GetPos();
			//	pPlayerMgr->SetPickItemID( pItem->GetID() );
			//	//pPlayerMgr->ControlLButDownProc( vPos.x, vPos.y, true );
			//	pPlayerMgr->ControlLButUpProc( vPos.x, vPos.y, true );
			//	//CPlayer* pMe = pPlayerMgr->GetMe();
			//	//if( pMe )
			//	//	pMe->SwitchPickAnim();
			//}
			m_nCurFunction = -1;
		}
		break;
	case CUI_ID_FRAME_BaseProperty::TYPE_PETATTACK:
		{
			CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
			if( pPlayerMgr )
			{
				pPlayerMgr->SendPetCommand( MsgPetCommand::eAttackTarget );
			}
			m_nCurFunction = -1;
		}
		break;
	case CUI_ID_FRAME_BaseProperty::TYPE_PETFOLLOW:
		{
			CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
			if( pPlayerMgr )
			{
				pPlayerMgr->SendPetCommand( MsgPetCommand::eFollowMe );
			}
			m_nCurFunction = -1;
		}
		break;
	case CUI_ID_FRAME_BaseProperty::TYPE_PETDISMISS:
		{
			CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
			if( pPlayerMgr )
			{
				pPlayerMgr->SendPetCommand( MsgPetCommand::eDismiss );
			}
			m_nCurFunction = -1;
		}
		break;
	case CUI_ID_FRAME_BaseProperty::TYPE_PETAIATTACK:
		{
			CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
			if( pPlayerMgr && pPlayerMgr->GetMe() && pPlayerMgr->GetMe()->HavePet())
			{
				pPlayerMgr->SendPetCommand( MsgPetCommand::eAttackAI );
				s_CUI_ID_FRAME_BaseProperty.SetPetAIType(CUI_ID_FRAME_BaseProperty::TYPE_PETAIATTACK);
				s_CUI_ID_FRAME_MAIN.RefeashHotKey();
				s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
				s_CUI_ID_FRAME_SKILL.RefreshCommon();
			}
			m_nCurFunction = -1;
		}
		break;
	case CUI_ID_FRAME_BaseProperty::TYPE_PETAIDEFEND:
		{
			CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
			if( pPlayerMgr && pPlayerMgr->GetMe() && pPlayerMgr->GetMe()->HavePet())
			{
				pPlayerMgr->SendPetCommand( MsgPetCommand::eDefendAI );
				s_CUI_ID_FRAME_BaseProperty.SetPetAIType(CUI_ID_FRAME_BaseProperty::TYPE_PETAIDEFEND);
				s_CUI_ID_FRAME_MAIN.RefeashHotKey();
				s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
				s_CUI_ID_FRAME_SKILL.RefreshCommon();
			}
			m_nCurFunction = -1;
		}
		break;
	case CUI_ID_FRAME_BaseProperty::TYPE_PETAICOMMAND:
		{
			CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
			if( pPlayerMgr && pPlayerMgr->GetMe() && pPlayerMgr->GetMe()->HavePet())
			{
				pPlayerMgr->SendPetCommand( MsgPetCommand::eCommandAI );
				s_CUI_ID_FRAME_BaseProperty.SetPetAIType(CUI_ID_FRAME_BaseProperty::TYPE_PETAICOMMAND);
				s_CUI_ID_FRAME_MAIN.RefeashHotKey();
				s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
				s_CUI_ID_FRAME_SKILL.RefreshCommon();
			}
			m_nCurFunction = -1;
		}
		break;
	case CUI_ID_FRAME_BaseProperty::TYPE_DISHITCH:
		{
			CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
			if( pPlayerMgr && pPlayerMgr->GetMe() )
			{
				if( pPlayerMgr->GetMe()->IsMounting() )
				{
					pPlayerMgr->GetMe()->DisMount();
				}

				if( pPlayerMgr->GetMe()->IsUncontrolMoving() && !pPlayerMgr->GetMe()->IsUncontrolFlying())
				{
					pPlayerMgr->DisHitch();
				}
			}
			m_nCurFunction = -1;
		}
		break;
	case CUI_ID_FRAME_BaseProperty::TYPE_PRIVATE_SHOP:
		{
            CSystemStallage::Instance()->OpenStallageWindow2();
			m_nCurFunction = -1;
		}
		break;

	case CUI_ID_FRAME_BaseProperty::TYPE_RUN_WALK:
		{
			extern BOOL g_bAutoRunForward;
			g_bAutoRunForward = !g_bAutoRunForward;
			m_nCurFunction = -1;
		}
		break;
	case CUI_ID_FRAME_BaseProperty::TYPE_COMPOUND:
		s_CUI_ID_FRAME_Compound.SetVisable( true );
		m_nCurFunction = -1;
		break;
		//case 		TYPE_EXCHANGE_UI:
		//	
		//	break;
// 	case		CUI_ID_FRAME_BaseProperty::TYPE_PROPERTY_UI:
// 		s_CUI_ID_FRAME_Property.SetVisable( true );
// 		m_nCurFunction = -1;
// 		break;
	case 		CUI_ID_FRAME_BaseProperty::TYPE_PACK_UI:
		s_CUI_ID_FRAME_PACK.SetVisable( true );
		m_nCurFunction = -1;
		break;
	case 		CUI_ID_FRAME_BaseProperty::TYPE_SKILL_UI:
		s_CUI_ID_FRAME_SKILL.SetVisableWherefore( true,s_CUI_ID_FRAME_SKILL.EWherefore_SkillBagLearn );
		m_nCurFunction = -1;
		break;
	case		CUI_ID_FRAME_BaseProperty::TYPE_SET_UI:
		//UI_ID_FRAME_SKILL::
		break;
	case		CUI_ID_FRAME_BaseProperty::TYPE_MAP_UI:
	//	UI_ID_FRAME_Map::SetVisable( true );
	//	m_nCurFunction = -1;
		break;
		//case TYPE_CREATEROOM:
		//	s_CUI_InputBox.Show( "请输入游戏名称", false, false, InputRoomName );
		//	m_nCurFunction = -1;
		//	break;
		//case TYPE_LEAVEROOM:
		//	LobbyMsg_ReqLeaveRoom msg;
		//	GettheNetworkInput().SendMsg( &msg );
		//	m_nCurFunction = -1;
		//	break;
	case CUI_ID_FRAME_BaseProperty::TYPE_MOUNT:
		{

            //多人坐骑上 ，非司机不能操上下马
			if (theHeroGame.GetPlayerMgr() 
				&& theHeroGame.GetPlayerMgr()->GetMe()  
				&& theHeroGame.GetPlayerMgr()->GetMe()->IsMultiMounting()
				&& theHeroGame.GetPlayerMgr()->GetMe()->GetID() != theHeroGame.GetPlayerMgr()->GetMe()->GetCarrierPlayerID())
			{
				//在多人坐骑上 不能进行 骑乘操作 lyh++duorenzuoji
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_CannotDoIt ) );
				return false;
			}
			if (theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->IsMounting())
				s_CUI_ID_FRAME_Pet.Dismount();
				//s_CUI_ID_FRAME_Pet.Mount();
			else
				s_CUI_ID_FRAME_Pet.Mount();
				//s_CUI_ID_FRAME_Pet.Dismount();
		}
		break;
	case CUI_ID_FRAME_BaseProperty::TYPE_GOBACK: // 回程
		theHeroGame.GetPlayerMgr()->SetCurUseSkill( CUI_ID_FRAME_BaseProperty::TYPE_GOBACK_SKILL_ID, 1 );
		thePlayerRole.UpdateUI();
		theHeroGame.GetPlayerMgr()->OnSkill( false );
		break;
	case CUI_ID_FRAME_BaseProperty::TYPE_GOBACK2: // 回程
		theHeroGame.GetPlayerMgr()->SetCurUseSkill( CUI_ID_FRAME_BaseProperty::TYPE_GOBACK_SKILL_ID2, 1 );
		thePlayerRole.UpdateUI();
		theHeroGame.GetPlayerMgr()->OnSkill( false );
		break;
	case CUI_ID_FRAME_BaseProperty::TYPE_SWITCHSCABBARD:
		theHeroGame.GetPlayerMgr()->SwitchScabbard();
		break;
	default:
		{
			SCharSkill *pSkill = 0;
			pSkill = thePlayerRole.m_SkillBag.GetSkillByID( m_nCurFunction );
			if ( pSkill && pSkill->ustSkillID != InvalidLogicNumber )
			{
				// 判断是否小队技能
				ItemDefine::SItemSkill *pItemSkill = GettheItemDetail().GetSkillByID( pSkill->ustSkillID, pSkill->stSkillLevel );
				if( pItemSkill->specialSkillType >= ItemDefine::ESST_Team && pItemSkill->specialSkillType < ItemDefine::ESST_TeamMax )
				{
					theHeroGame.GetPlayerMgr()->SetCurUseSkill( pSkill->ustSkillID, pSkill->stSkillLevel );
				}
				else
					theHeroGame.GetPlayerMgr()->SetCurUseSkill( pSkill->ustSkillID, 1 );
				thePlayerRole.UpdateUI();
				theHeroGame.GetPlayerMgr()->OnSkill( false );
			}
		}break;
	}
	m_nCurFunction = -1;
	return true;
	unguard;
}

bool CUI_ID_FRAME_ActionUI::ID_LISTIMG_UIOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
	if ( pItem && !pItem->IsNull() )
	{
		SetCurFunction( pItem->m_pkIconInfo->Id() );
	}
	//SetVisable( false );
	UseFunction( );
	return true;
	unguard;
}

// 装载UI
bool CUI_ID_FRAME_ActionUI::_LoadUI()
{
	guardfunc;
	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\ActionUI.meui", false, UI_Render_LayerSecond );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[UI\\ActionUI.UI]失败")
			return false;
	}
// 	else if ( dwResult != 48847/*文件版本号*/ )
// 	{
// 		MESSAGE_BOX("读取文件[UI\\ActionUI.UI]与源代码版本不一样")
// 	}
	return DoControlConnect();
	unguard;
}

// 关连控件
bool CUI_ID_FRAME_ActionUI::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_ActionUI, s_CUI_ID_FRAME_ActionUIOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ActionUI, s_CUI_ID_FRAME_ActionUIOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_ActionUI, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_ActionUIID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ActionUI, ID_BUTTON_Property, s_CUI_ID_FRAME_ActionUIID_BUTTON_PropertyOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ActionUI, ID_BUTTON_Tesk, s_CUI_ID_FRAME_ActionUIID_BUTTON_TeskOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_ActionUI, ID_LISTIMG_Dictate, s_CUI_ID_FRAME_ActionUIID_LISTIMG_DictateOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_ActionUI, ID_LISTIMG_Dictate, s_CUI_ID_FRAME_ActionUIID_LISTIMG_DictateOnIconLDBClick );
	theUiManager.OnIconDragOn( ID_FRAME_ActionUI, ID_LISTIMG_UI, s_CUI_ID_FRAME_ActionUIID_LISTIMG_UIOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_ActionUI, ID_LISTIMG_UI, s_CUI_ID_FRAME_ActionUIID_LISTIMG_UIOnIconLDBClick );
	theUiManager.OnIconDragOn( ID_FRAME_ActionUI, ID_LISTIMG_Action, s_CUI_ID_FRAME_ActionUIID_LISTIMG_ActionOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_ActionUI, ID_LISTIMG_Action, s_CUI_ID_FRAME_ActionUIID_LISTIMG_ActionOnIconLDBClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_ActionUI, ID_LISTIMG_UI, s_CUI_ID_FRAME_ActionUIID_LISTIMG_UIOnIconRButtonUp );

	m_pID_FRAME_ActionUI = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ActionUI );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActionUI, ID_BUTTON_CLOSE );
	m_pID_BUTTON_Property = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActionUI, ID_BUTTON_Property );
	m_pID_BUTTON_Tesk = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActionUI, ID_BUTTON_Tesk );
	m_pID_LISTIMG_Dictate = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActionUI, ID_LISTIMG_Dictate );
	m_pID_LISTIMG_UI = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActionUI, ID_LISTIMG_UI );
//	m_pID_LISTIMG_Action = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ActionUI, ID_LISTIMG_Action );
	assert( m_pID_FRAME_ActionUI );
	m_pID_FRAME_ActionUI->SetVisable(false);
	//CUILayout::GetInstance()->AddFrame(m_pID_FRAME_ActionUI);
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_Property );
	assert( m_pID_BUTTON_Tesk );
	assert( m_pID_LISTIMG_Dictate );
	assert( m_pID_LISTIMG_UI );
//	assert( m_pID_LISTIMG_Action );

	
	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActionUI, ID_BUTTON_help );
	assert( m_pID_BUTTON_help );
	m_pID_BUTTON_help->SetButtonClickFun( helpOnClick );

	USE_SCRIPT( eUI_OBJECT_ActionUI, this );
	m_pID_FRAME_ActionUI->SetOnEscResponseType(ControlFrame::EscResponse_SkipMe);
	
	return true;
	unguard;
}
bool CUI_ID_FRAME_ActionUI::helpOnClick( ControlObject* pSender )
{
	guardfunc;
// 	s_CUI_ID_FRAME_Help.SetVisable( !s_CUI_ID_FRAME_Help.IsVisable() );
	return true;
	unguard;
}
// void CUI_ID_FRAME_ActionUI::SetVisableLayout()
// {
// 	if( !m_pID_FRAME_ActionUI )
// 		return;
// 	CUILayout::GetInstance()->SetVisable(m_pID_FRAME_ActionUI);
// }
// 卸载UI
bool CUI_ID_FRAME_ActionUI::_UnLoadUI()
{
	CLOSE_SCRIPT( eUI_OBJECT_ActionUI );
	m_pID_FRAME_ActionUI = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Property = NULL;
	m_pID_BUTTON_Tesk = NULL;
	m_pID_LISTIMG_Dictate = NULL;
	m_pID_LISTIMG_UI = NULL;
	return theUiManager.RemoveFrame( "data\\ui\\ActionUI.meui" );
}
// 是否可视
bool CUI_ID_FRAME_ActionUI::_IsVisable()
{
	if( !m_pID_FRAME_ActionUI )
		return false;
	return m_pID_FRAME_ActionUI->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_ActionUI::_SetVisable( const bool bVisable)
{
	if( !m_pID_FRAME_ActionUI )
		return;
	CUIBase::SetVisable( bVisable );
	//if( bVisable != IsVisable() )
	//	SetVisableLayout();
	//else
	if( m_pID_FRAME_ActionUI )
		m_pID_FRAME_ActionUI->SetVisable( bVisable );

	//if( s_CUI_ID_FRAME_Task.m_pID_FRAME_Task )
	//{
	//	s_CUI_ID_FRAME_Task.SetVisable(!bVisable);
	//}
	//if( UI_ID_FRAME_Property::m_pID_FRAME_Property )
	//	UI_ID_FRAME_Property::SetVisable( !bVisable );
}

void CUI_ID_FRAME_ActionUI::SetCurFunction( const int nFunction )
{
	m_nCurFunction = nFunction;
	switch( m_nCurFunction )
	{
// 	case CUI_ID_FRAME_BaseProperty::TYPE_BARGAINING:d
// 	case CUI_ID_FRAME_BaseProperty::TYPE_JOINROOM:
	case CUI_ID_FRAME_BaseProperty::TYPE_USEITEM:
		m_enCursorType = MouseManager::Type_UseItem;
		theMouseManager.SetUICursor( m_enCursorType );
		break;
	default:
		m_enCursorType = MouseManager::Type_Arrow;
		break;
	}
	theMouseManager.SetCursor( m_enCursorType );
}

void CUI_ID_FRAME_ActionUI::Process()
{
	guardfunc
	if ( s_CUI_ID_FRAME_ActionUI.GetCurFunction() == -1 )
		return;

	GameObjectId gcPlayerServerID = theHeroGame.GetPlayerMgr()->GetMouseTargetPlayerSeverID();
	CPlayer* pTarget = theHeroGame.GetPlayerMgr()->FindByID( gcPlayerServerID );
	//if( s_CUI_ID_FRAME_FriRBMenu.GetIsAddTeam() )
	//{//zizi add 如果是通过好友界面 邀请组队的话
	//	pTarget = theHeroGame.GetPlayerMgr()->FindByName( s_CUI_ID_FRAME_FriRBMenu.GetName() );
	//}
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if ( !pMe )
		return;
	if ( !pTarget )
	{
		int nID = theHeroGame.GetPlayerMgr()->GetLockPlayerID();
		pTarget = theHeroGame.GetPlayerMgr()->FindByID( nID );
		if( !pTarget || !pTarget->IsPlayer() )
		{
			//s_CUI_ID_FRAME_ActionUI.SetCurFunction( -1 );
			switch( s_CUI_ID_FRAME_ActionUI.GetCurFunction() ) 
			{
			case CUI_ID_FRAME_BaseProperty::TYPE_BARGAINING:
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_Failed, theXmlString.GetString(eTextBargainingError_OutRange) );
				}
				break;
			case CUI_ID_FRAME_BaseProperty::TYPE_REQ_DUEL:
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Dual, theXmlString.GetString(eTextDuelError_OutRange) );   
				}
				break;
			}
			return;
		}
	}		
	switch( s_CUI_ID_FRAME_ActionUI.GetCurFunction() ) 
	{
	case CUI_ID_FRAME_BaseProperty::TYPE_BARGAINING:
		{
			//// 在马上不可交易
			//if ( pMe->IsMounting() || pTarget->IsMounting() )
			//{
			//	s_CUI_ID_FRAME_ActionUI.SetCurFunction( -1 );
			//	UI_MessageBox::Show( theXmlString.GetString(eClient_AddInfo_2slk_25) );
			//	return;
			//}
			//
			if ( !pTarget->IsPlayer() || pTarget == pMe )
			{
				s_CUI_ID_FRAME_ActionUI.SetCurFunction( -1 );
				//发送交易申请失败
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_Failed, theXmlString.GetString(eUI_SendExchange_fail) );
				return;
			}
			if (thePlayerRole.isFrdInBlackList(pTarget->GetName()))
			{
				s_CUI_ID_FRAME_ActionUI.SetCurFunction( -1 );
				//发送交易申请失败
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, theXmlString.GetString(eText_AddFriInBlackList) );
				return;
			}
			// 过远
			float fMeX,fMeY,fMeZ;
			float fPlayerX, fPlayerY, fPlayerZ;
			pMe->GetPos( &fMeX, &fMeY, &fMeZ );
			pTarget->GetPos( &fPlayerX, &fPlayerY, &fPlayerZ );
			float x = fPlayerX - fMeX;
			float y = fPlayerY - fMeY;
			float dist = sqrtf( x*x + y*y );
			if( dist > 10.0f )
			{
				s_CUI_ID_FRAME_ActionUI.SetCurFunction( -1 );
				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_Client_Trade_Faild_Distance) );
				return;
			}

			if ( pTarget->IsMounting() ||
				pMe->IsMounting() )
			{
				s_CUI_ID_FRAME_ActionUI.SetCurFunction( -1 );
				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_Client_Trade_Faild_Ride) );
				return;
			}

			//
			char szInfo[128];
			//您向 发送交易申请
			sprintf( szInfo, "%s ~%s_ %s", theXmlString.GetString( eUI_YouTo ),	pTarget->GetName(), theXmlString.GetString( eUI_SendExchange ) );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_Success, szInfo );

            MsgBargainingReq msg;
			msg.ustPlayerID = pTarget->GetID();
			GettheNetworkInput().SendMsg( &msg );
		}
		break;
	case CUI_ID_FRAME_BaseProperty::TYPE_QUERY_TEAM:// 发送组队申请
		{
			if ( !pTarget->IsPlayer() || pTarget == pMe )
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, theXmlString.GetString(eUI_SendTeam_fail) );
			}
			else
			{
				char szInfo[128] = {0};
				//您向 发送组队申请
				//if( s_CUI_ID_FRAME_Friend.haseRequestPeople( pTarget->GetName() ) )
				//{
				//	sprintf( szInfo, "您已经向%s发送了组队申请", pTarget->GetName() );
				//	s_CUI_ID_FRAME_InfoList. AddInfo( szInfo, 0xFFFFFF00 );
				//	return;
				//}

				//s_CUI_ID_FRAME_Friend.pushRequestPeople( pTarget->GetName() );

				sprintf_s( szInfo, sizeof(szInfo)-1, "%s ~%s_ %s", 
					theXmlString.GetString(eUI_YouTo), pTarget->GetName(),
					theXmlString.GetString(eUI_SendTeam));
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Invite_Team, szInfo );

				//if(thePlayerRole.GetCampType() != CampDefine::NoneCamp)
				//{
				//	//不可以创建队伍
				//	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eClient_CampBattle_Team));
				//	return;
				//}

				MsgRequestTeam msg;
				msg.header.stID = pMe->GetID();
				msg.dwNewbieID = -1;
				strncpy(msg.szNewbieName, pTarget->GetName(), sizeof(msg.szNewbieName)-1);
                msg.AssignMode = thePlayerRole.GetAssignMode();
                msg.AssignItemLevel = thePlayerRole.GetItemRollLevel();
				GettheNetworkInput().SendMsg(&msg);
			}
		}
		break;
	//case CUI_ID_FRAME_BaseProperty::TYPE_JOINROOM:
	//	{
	//		if ( !pTarget->IsPlayer() || pTarget == pMe ||
	//			pTarget->GetRoomID() == -1 )
	//		{
	//			s_CUI_ID_FRAME_InfoList. AddInfo( theXmlString.GetString( eUI_SendAddRoom_fail ), 0xFFFFFF00 );
	//		}
	//		else
	//		{
	//			char szInfo[128];
	//			sprintf( szInfo, "%s %s %s", 
	//				theXmlString.GetString( eUI_YouTo ),
	//				pTarget->GetName(),
	//				theXmlString.GetString( eUI_SendAddRoom ) );
	//			s_CUI_ID_FRAME_InfoList. AddInfo( szInfo, 0xFFFFFF00 );
	//		}
	//		LobbyMsg_ReqJoinRoom msg;
	//		msg.nRoomID = pTarget->GetRoomID();
	//		GettheNetworkInput().SendMsg( &msg );
	//	}
	//	break;
	case CUI_ID_FRAME_BaseProperty::TYPE_REQ_DUEL:
		{
			if( pTarget->IsPlayer() && pTarget != pMe &&
				!pTarget->IsOpenPrivateShop() )
			{
				MsgReqDuel duel;
				duel.shTargetID = pTarget->GetID();
				GettheNetworkInput().SendMsg( &duel );
			}
		}
		break;
	case CUI_ID_FRAME_BaseProperty::TYPE_USEITEM:
		{
			int nIndex = s_CUI_ID_FRAME_PACK.GetForTargetItemIndex();
			if ( nIndex == -1 )
			{
				break;
			}
			SCharItem stItem;
			if( !thePlayerRole.m_bag.GetItem( nIndex, &stItem ) )
			{
				break;
			}
			RestoreColdDown* pRestoreCoolDown = NULL;
			pRestoreCoolDown = thePlayerRole.GetRestoreCoolDown();
			if( pRestoreCoolDown->UseRestore( stItem.itembaseinfo.ustItemID ) )
			{
				MsgUseGoods msg;
				msg.ustItemIndex = nIndex;
				msg.nGuid = stItem.itembaseinfo.nOnlyInt;
				msg.stDstChar = pTarget->GetID();
				GettheNetworkInput().SendMsg( &msg );
				thePlayerRole.UpdateUI();				
			}
		}
		break;
	default:
		break;
	}
	s_CUI_ID_FRAME_ActionUI.SetCurFunction( -1 );
	unguard
}
