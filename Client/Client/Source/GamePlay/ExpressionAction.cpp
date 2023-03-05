#include "ExpressionAction.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "ChatInfoBox.h"
#include "MeAudio/meaudio.h"
#include "color_config.h"
#include "MessageDefine.h"
#include "NetworkInput.h"
#include "ShowScreenText.h"
#include "core/Name.h"
#include "XmlStringLanguage.h"
#include "Common.h"
#include "Ui/InfoList.h"

extern CHeroGame	theHeroGame;

bool CExpressionAction::CheckAndDoExpressionAction( const char* szChat, ExpAction::ESex sex )
{
	if( !szChat || szChat[0] == '\0' )
		return false;

	CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
	if( !pPlayerMgr )
		return false;

	const ExpAction* pExpAction = GetExpAction(szChat, sex);
	if( !pExpAction )
		return false;

	if( !CanDoExpressionAction() )
		return false;

	SendExpressionAction(pExpAction->GetId(), pPlayerMgr->GetLockPlayerID());

	return true;
}

bool CExpressionAction::CheckAndDoExpressionAction( unsigned short ustActionId )
{
	CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
	if( !pPlayerMgr )
		return false;

	const ExpAction* pAction = GetExpAction(ustActionId);
	if( NULL == pAction )
		return false;

	if( !CanDoExpressionAction() )
		return false;

	SendExpressionAction(ustActionId, pPlayerMgr->GetLockPlayerID());

	return true;
}


bool CExpressionAction::CheckAndDoExpressionActionByItemId( unsigned short ustItemId, ExpAction::ESex sex )
{
	const ExpAction* pAction = CExpressionAction::Instance().GetExpActionByItemId(ustItemId, sex);
	if( pAction )
	{
		return CExpressionAction::Instance().CheckAndDoExpressionAction(pAction->GetId());
	}
	return false;
}

void CExpressionAction::OnSeeExpressionAction( int nPlayerId, int nTargetId, unsigned short ustActionId )
{
	CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
	if( !pPlayerMgr )
		return;

	CPlayer* pSrc = pPlayerMgr->FindByID(nPlayerId);
	if( NULL == pSrc )
		return;

	CPlayer* pDst = NULL;
	if( nTargetId >= 0 )
		pDst = pPlayerMgr->FindByID(nTargetId);

	const ExpAction* pAction = GetExpAction(ustActionId);
	if( NULL == pAction )
		return;

	// 判断性别
	if( pAction->GetSex() != ExpAction::SAll )
	{
		if(!( ( pSrc->GetSex() == Sex_Male && pAction->GetSex() == ExpAction::Male )
			|| ( pSrc->GetSex() == Sex_Female && pAction->GetSex() == ExpAction::Female )))
			return;
	}

	if( pDst && pDst != pSrc )
	{
		// 转向目标
		float fDir = atan2f(pDst->GetPos().y - pSrc->GetPos().y, pDst->GetPos().x - pSrc->GetPos().x);
		if( fDir > D3DX_PI )
			fDir -= D3DX_PI*2;
		if( fDir < 0 )
			fDir += D3DX_PI*2;
		pSrc->SetDir(fDir);
		pSrc->SetCurDir(fDir);
		pSrc->SetUpperDir(fDir);
		pSrc->SetLowerDir(fDir);
		pSrc->SetCurUpperDir(fDir);
		pSrc->SetCurLowerDir(fDir);
	}

	const char* szEndAnim = pAction->GetLoopActionName();
	if( !szEndAnim || szEndAnim[0] == '\0')
	{
		if( pSrc->IsHaveWeapon() )
			szEndAnim = "single_idle";
		else
			szEndAnim = "idle";
	}

	pSrc->SetShowWeapon(false); //lyh添加做表情动作的时候 隐藏武器的显示
	pSrc->PlayAnim(pAction->GetActionName(), 1, szEndAnim);

	char szChat[256] = {0};
	if( !pDst )				// 无目标
	{
		MeSprintf_s( szChat, sizeof(szChat)/sizeof(char) - 1, pAction->GetNoTargetChat(), pSrc->GetName() );
	}
	else if( pDst == pSrc )	// 目标为自己
	{
		MeSprintf_s( szChat, sizeof(szChat)/sizeof(char) - 1, pAction->GetSelfTargetChat(), pSrc->GetName() );
	}
	else					// 目标为他人
	{
		if( pAction->GetOtherTargetSelfFront() )
			MeSprintf_s( szChat, sizeof(szChat)/sizeof(char) - 1, pAction->GetOtherTargetChat(), pSrc->GetName(), pDst->GetName() );
		else
			MeSprintf_s( szChat, sizeof(szChat)/sizeof(char) - 1, pAction->GetOtherTargetChat(), pDst->GetName(), pSrc->GetName() );
	}

	// 聊天泡泡
	std::string strChat = szChat;
	pSrc->SetChatInfo( strChat );

	// 聊天框
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Chat_ChannelTip, strChat, pSrc->GetName() );

	const char* szSound = pAction->GetSound();
	if (szSound != NULL && szSound[0] != '\0')
	{
		char strSoundFullName[MAX_PATH] = {0};
		MeSprintf_s(strSoundFullName, sizeof(strSoundFullName)/sizeof(char) - 1, "%s\\%s", GetRootPath(), szSound);
		GSound.PlaySound( strSoundFullName, false, &pSrc->GetPos() );
	}
}

const ExpAction* CExpressionAction::GetExpAction( const char* szChat, ExpAction::ESex sex )
{
	if( !szChat || szChat[0] == '\0' )
		return NULL;

	const ExpActionConfig::ExpActionMap& mapExpActions = theExpActionConfig.GetExpActions();
	ExpActionConfig::ExpActionMapConstIter iter = mapExpActions.begin();
	for(; iter != mapExpActions.end(); ++iter)
	{
		const ExpAction* pAction = &(iter->second);
		if( !strcmp(pAction->GetCommand(), szChat) && ( pAction->GetSex() == sex || pAction->GetSex() == ExpAction::SAll ))
			return pAction;
	}

	return NULL;
}

const ExpAction* CExpressionAction::GetExpAction( unsigned short ustActionId )
{
	return theExpActionConfig.GetExpAction(ustActionId);
}

const ExpAction* CExpressionAction::GetExpActionByItemId( unsigned short ustItemId, ExpAction::ESex sex )
{
	const ExpActionConfig::ExpActionMap& mapExpActions = theExpActionConfig.GetExpActions();
	ExpActionConfig::ExpActionMapConstIter iter = mapExpActions.begin();
	for(; iter != mapExpActions.end(); ++iter)
	{
		const ExpAction* pAction = &(iter->second);
		if( pAction->GetItemId() == ustItemId && ( pAction->GetSex() == sex || pAction->GetSex() == ExpAction::SAll ) )
			return pAction;
	}

	return NULL;
}

const ExpAction* CExpressionAction::GetExpActionByIndex( unsigned short ustIndex, ExpAction::ESex sex )
{
	if( ustIndex >= GetExpActionNum(sex) )
		return NULL;

	const ExpActionConfig::ExpActionMap& mapExpActions = theExpActionConfig.GetExpActions();
	ExpActionConfig::ExpActionMapConstIter iter = mapExpActions.begin();
	int count = -1;
	for(int cnt = 0; cnt < mapExpActions.size(); ++cnt)
	{
		if( iter->second.GetSex() == sex || iter->second.GetSex() == ExpAction::SAll )
		{
			++count;
			if( count == ustIndex )
				break;
		}
		++iter;
	}
	if( iter == mapExpActions.end() )
		return NULL;

	return &(iter->second);
}

void CExpressionAction::SendExpressionAction( unsigned short ustActionId, int nTargetID )
{
   if(theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->IsMoving())
   {
	   	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_ContThisOp ) );
	   return ;

   }

	MsgQueryExpression msg;
	msg.stTargetID = nTargetID;
	msg.ustActionID = ustActionId;
	GettheNetworkInput().SendMsg(&msg);

	m_nExpressionActionCoolDown = theExpActionConfig.GetExpActionCD();
}

bool CExpressionAction::CanDoExpressionAction( bool bShowInfo /*= true*/ )
{
	CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
	if( !pPlayerMgr )
		return false;

	CPlayer* pMe = pPlayerMgr->GetMe();
	if( !pMe )
		return false;

	if( pMe->IsMounting() )
	{
		if( bShowInfo )
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Player_Action, theXmlString.GetString(eText_ExpActionFailed_InMounting) );
		return false;
	}

	if( pMe->IsInWater() )
	{
		if( bShowInfo )
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Player_Action, theXmlString.GetString(eText_ExpActionFailed_InWater) );
		return false;
	}

	if( pMe->IsOpenPrivateShop() )
	{
		if( bShowInfo )
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Player_Action, theXmlString.GetString(eText_ExpActionFailed_InPrivateShop) );
		return false;
	}

	if( pMe->IsDead() )
	{
		if( bShowInfo )
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Player_Action, theXmlString.GetString(eText_ExpActionFailed_IsDead) );
		return false;
	}

	if( pMe->HasFightFlag(eFighting) )
	{
		if( bShowInfo )
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Player_Action, theXmlString.GetString(eText_ExpActionFailed_InFighting) );
		return false;
	}

	if( pMe->IsLootOrIntonateAnim() )
	{
		if( bShowInfo )
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Player_Action, theXmlString.GetString(eText_ExpActionFailed_InLooting) );
		return false;
	}

	if( m_nExpressionActionCoolDown > 0 )
	{
		if( bShowInfo )
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Player_Action, theXmlString.GetString(eChangeSuitCD) );
		return false;
	}

	if( pPlayerMgr->GetLockPlayerID() >= 0 )
	{
		CPlayer* pTarget = pPlayerMgr->FindByID(pPlayerMgr->GetLockPlayerID());
		if( pTarget && pTarget != pMe )
		{
			float fOffsetX = pMe->GetPos().x - pTarget->GetPos().x;
			float fOffsetY = pMe->GetPos().y - pTarget->GetPos().y;
			float fOffsetZ = pMe->GetPos().z - pTarget->GetPos().z;
			float fDist = sqrt(fOffsetX*fOffsetX + fOffsetY*fOffsetY + fOffsetZ*fOffsetZ);
			if( fDist > theExpActionConfig.GetTargetMaxDist() )
			{
				if( bShowInfo )
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Player_Action, theXmlString.GetString(eText_ExpActionFailed_TargetTooFar) );
				return false;
			}
		}
	}

	return true;
}

void CExpressionAction::UpdateCoolDown()
{
	if( m_nExpressionActionCoolDown > 0 )
	{
		m_nExpressionActionCoolDown -= (int)(theHeroGame.GetFrameElapsedTime() * 1000.f);
		if( m_nExpressionActionCoolDown < 0 )
			m_nExpressionActionCoolDown = 0;
	}
}
