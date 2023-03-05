#include <assert.h>
#include "MeUi/UiManager.h"
#include "Gut.h"
#include "PlayerAnimCtrl.h"
#include "player.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Me3d/ShaderManager.h"
#include "Me3d/Engine/RendererDX.h"
#include "MeTerrain/NiColor.h"
#include "MeTerrain/SwType.h"
#include "MeTerrain/HashTable.h"
#include "MeTerrain/MapFile.h"
#include "MeTerrain/MapUtil.h"
#include "MeTerrain/SwGlobal.h"
#include "MeTerrain/World.h"
#include "MeTerrain/WorldBuffer.h"
#include "MeTerrain/WorldTile.h"
#include "MeTerrain/WorldChunk.h"
#include "MeTerrain/NdlWorldPickerBase.h"
#include "wsRender.h"
#include "wsCamera.h"
#include "Me3d/Engine/MeRenderManager.h"
#include "XmlStringLanguage.h"
#include "NpcTaskDialogBox.h"
#include "Common.h"
#include "script_manager.h"
#include "NpcInfo.h"
#include "ModelConfig.h"
#include "SystemConfig.h"
#include "Cfg.h"
#include "CountryDefine.h"
#include "Ui/MessageBox.h"
#include "ui/Pack.h"
#include "Ui/UIStorage.h"

CUI_ID_FRAME_Gut s_CUI_ID_FRAME_Gut;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Gut, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Gut, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gut, ID_BUTTON_ContinueOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gut, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gut, ID_BUTTON_RefuseOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gut, ID_BUTTON_FinishOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gut, ID_BUTTON_AcceptOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Gut, ID_LISTIMG_4592OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Gut, ID_LISTIMG_4592OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gut, ID_LISTIMG_4592OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Gut, ID_LISTIMG_4592OnIconRButtonUp )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Gut, ID_LIST_PlayerGutOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Gut, ID_BUTTON_1148OnButtonClick )
CUI_ID_FRAME_Gut::CUI_ID_FRAME_Gut()
{
	// Member
	m_pID_FRAME_Gut = NULL;
	m_pID_TEXT_GoOn = NULL;
	m_pID_PICTURE_Backdrop = NULL;
	m_pID_TEXT_TextTitle = NULL;
	m_pID_TEXT_NpcGut = NULL;
	m_pID_BUTTON_Continue = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Refuse = NULL;
	m_pID_BUTTON_Finish = NULL;
	m_pID_BUTTON_Accept = NULL;
	m_pID_PICTURE_NPC = NULL;
	m_pID_LIST_PlayerGut = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_TEXT_EXP = NULL;
	m_pID_LISTIMG_4592 = NULL;
	m_pID_PICTURE_PlayerBase = NULL;
	m_pID_PICTURE_PlayerBase1 = NULL;
	m_pID_PICTURE_Up = NULL;
	m_pID_PICTURE_Down = NULL;
	m_pID_BUTTON_1148 = NULL;
	m_pID_TEXT_CountryMoney = NULL;
	m_nModelId = -1;
	m_nShowType = -1;
	m_nQuestID = -1;
	m_BgPic.clear();

	m_fStature = -1.0f;
}

// Frame
bool CUI_ID_FRAME_Gut::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	if(IsVisable())
		theUiManager.ToTop(m_pID_FRAME_Gut);
	return true;
}

bool CUI_ID_FRAME_Gut::OnFrameRender()
{
	ShowBgPic();

	if (CURRENTTILE == NULL)
		return false;

	CPlayer *player = theHeroGame.GetPlayerMgr()->FindByID(m_nNpcID);
	if (player == NULL)
		return false;

	NpcInfo::Npc *npc = theNpcInfo.GetNpc(player->GetNpcID(),CURRENTTILE->GetMapId());
	if (npc == NULL)
		return false;

	RECT rc;
	m_pID_PICTURE_NPC->GetRealRect(&rc);
	RenderAnim_Update(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, D3DXVECTOR3(0, -20, 5));
	RenderAnim(D3DXVECTOR3(0 + npc->gutUIOffsetX, -14, 0 + npc->gutUIOffsetY), npc->gutUIScale);
	return true;
}

// Button
bool CUI_ID_FRAME_Gut::ID_BUTTON_ContinueOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gut )
		return false;

	ContinueTalk();
	return true;
}

// Button
bool CUI_ID_FRAME_Gut::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gut )
		return false;
	return true;
}

// Button
bool CUI_ID_FRAME_Gut::ID_BUTTON_RefuseOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gut )
		return false;

	EndNpcScript();
	SetVisable(false);
	s_CUI_NpcTaskDialogBox.CloseDialog(false);
	return true;
}

// Button
bool CUI_ID_FRAME_Gut::ID_BUTTON_FinishOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gut )
		return false;
	StartScript(m_nNpcID);
	SetVisable(false);
	//弹出完成任务的界面后，如果玩家走到NPC范围外再点完成任务会导致请求脚本失败，以及以后再次点击npc对话改该npc不鸟你
	s_CUI_NpcTaskDialogBox.SetFinishUI(true);
	return true;
}

// Button
bool CUI_ID_FRAME_Gut::ID_BUTTON_AcceptOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gut )
		return false;

	StartScript(m_nNpcID);
	SetVisable(false);
	s_CUI_NpcTaskDialogBox.CloseDialog(false);
	return true;
}

// ListImg / ListEx
bool CUI_ID_FRAME_Gut::ID_LISTIMG_4592OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
												   ControlIconDrag::S_ListImg* pItemDrag,
												   ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_Gut )
		return false;
	return false;
}

bool CUI_ID_FRAME_Gut::ID_LISTIMG_4592OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Gut )
		return false;
	return false;
}

bool CUI_ID_FRAME_Gut::ID_LISTIMG_4592OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Gut )
		return false;
	return false;
}

bool CUI_ID_FRAME_Gut::ID_LISTIMG_4592OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_Gut )
		return false;
	return false;
}

void CUI_ID_FRAME_Gut::ID_LIST_PlayerGutOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_Gut )
		return;

	ContinueTalk();
}

// Button
bool CUI_ID_FRAME_Gut::ID_BUTTON_1148OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Gut )
		return false;

	//SetVisable(false);
	//s_CUI_NpcTaskDialogBox.CloseDialog(false);
	m_vTalks.clear();
	ContinueTalk();

	return true;
}

// 装载UI
bool CUI_ID_FRAME_Gut::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Gut.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Gut.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}

// 关连控件
bool CUI_ID_FRAME_Gut::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Gut, s_CUI_ID_FRAME_GutOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Gut, s_CUI_ID_FRAME_GutOnFrameRender,true );
	theUiManager.OnButtonClick( ID_FRAME_Gut, ID_BUTTON_Continue, s_CUI_ID_FRAME_GutID_BUTTON_ContinueOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gut, ID_BUTTON_OK, s_CUI_ID_FRAME_GutID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gut, ID_BUTTON_Refuse, s_CUI_ID_FRAME_GutID_BUTTON_RefuseOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gut, ID_BUTTON_Finish, s_CUI_ID_FRAME_GutID_BUTTON_FinishOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Gut, ID_BUTTON_Accept, s_CUI_ID_FRAME_GutID_BUTTON_AcceptOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_Gut, ID_LISTIMG_4592, s_CUI_ID_FRAME_GutID_LISTIMG_4592OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Gut, ID_LISTIMG_4592, s_CUI_ID_FRAME_GutID_LISTIMG_4592OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_Gut, ID_LISTIMG_4592, s_CUI_ID_FRAME_GutID_LISTIMG_4592OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Gut, ID_LISTIMG_4592, s_CUI_ID_FRAME_GutID_LISTIMG_4592OnIconRButtonUp );
	theUiManager.OnListSelectChange( ID_FRAME_Gut, ID_LIST_PlayerGut, s_CUI_ID_FRAME_GutID_LIST_PlayerGutOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_Gut, ID_BUTTON_1148, s_CUI_ID_FRAME_GutID_BUTTON_1148OnButtonClick );

	m_pID_FRAME_Gut = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Gut );
	m_pID_TEXT_GoOn = (ControlText*)theUiManager.FindControl( ID_FRAME_Gut, ID_TEXT_GoOn );
	m_pID_PICTURE_Backdrop = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Gut, ID_PICTURE_Backdrop );
	m_pID_TEXT_TextTitle = (ControlText*)theUiManager.FindControl( ID_FRAME_Gut, ID_TEXT_TextTitle );
	m_pID_TEXT_NpcGut = (ControlText*)theUiManager.FindControl( ID_FRAME_Gut, ID_TEXT_NpcGut );
	m_pID_BUTTON_Continue = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gut, ID_BUTTON_Continue );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gut, ID_BUTTON_OK );
	m_pID_BUTTON_Refuse = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gut, ID_BUTTON_Refuse );
	m_pID_BUTTON_Finish = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gut, ID_BUTTON_Finish );
	m_pID_BUTTON_Accept = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gut, ID_BUTTON_Accept );
	m_pID_PICTURE_NPC = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Gut, ID_PICTURE_NPC );
	m_pID_LIST_PlayerGut = (ControlList*)theUiManager.FindControl( ID_FRAME_Gut, ID_LIST_PlayerGut );
	m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_Gut, ID_TEXT_Money );
	m_pID_TEXT_EXP = (ControlText*)theUiManager.FindControl( ID_FRAME_Gut, ID_TEXT_EXP );
	m_pID_LISTIMG_4592 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Gut, ID_LISTIMG_4592 );
	m_pID_PICTURE_PlayerBase = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Gut, ID_PICTURE_PlayerBase );
	m_pID_PICTURE_PlayerBase1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Gut, ID_PICTURE_PlayerBase1 );
	m_pID_PICTURE_Up = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Gut, ID_PICTURE_Up );
	m_pID_PICTURE_Down = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Gut, ID_PICTURE_Down );
	m_pID_BUTTON_1148 = (ControlButton*)theUiManager.FindControl( ID_FRAME_Gut, ID_BUTTON_1148 );
	m_pID_TEXT_CountryMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_Gut, ID_TEXT_CountryMoney );
	assert( m_pID_FRAME_Gut );
	assert( m_pID_TEXT_GoOn );
	assert( m_pID_PICTURE_Backdrop );
	assert( m_pID_TEXT_TextTitle );
	assert( m_pID_TEXT_NpcGut );
	assert( m_pID_BUTTON_Continue );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_Refuse );
	assert( m_pID_BUTTON_Finish );
	assert( m_pID_BUTTON_Accept );
	assert( m_pID_PICTURE_NPC );
	assert( m_pID_LIST_PlayerGut );
	assert( m_pID_TEXT_Money );
	assert( m_pID_TEXT_EXP );
	assert( m_pID_LISTIMG_4592 );
	assert( m_pID_PICTURE_PlayerBase );
	assert( m_pID_PICTURE_PlayerBase1 );
	assert( m_pID_PICTURE_Up );
	assert( m_pID_PICTURE_Down );
	assert( m_pID_BUTTON_1148 );
	assert( m_pID_TEXT_CountryMoney );
	if( m_pID_FRAME_Gut )
	{
		m_pID_FRAME_Gut->SetMsgProcFun( MsgProc );
	}

    m_GroupAward.Clear();
	m_GroupAward.AddControl(m_pID_TEXT_Money);
	m_GroupAward.AddControl(m_pID_TEXT_EXP);
	m_GroupAward.AddControl(m_pID_LISTIMG_4592);
	m_GroupAward.AddControl(m_pID_PICTURE_PlayerBase);
	m_GroupAward.AddControl(m_pID_TEXT_CountryMoney);
	

	m_GroupMe.Clear();
	m_GroupMe.AddControl(m_pID_LIST_PlayerGut);
	m_GroupMe.AddControl(m_pID_PICTURE_PlayerBase1);

	m_pID_FRAME_Gut->enableEscKey( false );
	m_pID_FRAME_Gut->SetOnEscResponseType( ControlFrame::EscResponse_SkipMe );
	m_BgPic.clear();

	RenderAnim_Create(CUIRenderAnim::RTWUI_GUT_QUEST);

	m_fStature = -1.0f;
	_SetVisable(false);
	return true;
}

// 卸载UI
bool CUI_ID_FRAME_Gut::_UnLoadUI()
{
	m_pID_FRAME_Gut = NULL;
	m_pID_TEXT_GoOn = NULL;
	m_pID_PICTURE_Backdrop = NULL;
	m_pID_TEXT_TextTitle = NULL;
	m_pID_TEXT_NpcGut = NULL;
	m_pID_BUTTON_Continue = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Refuse = NULL;
	m_pID_BUTTON_Finish = NULL;
	m_pID_BUTTON_Accept = NULL;
	m_pID_PICTURE_NPC = NULL;

	if(!m_BgPic.empty())
	{
		theControlPictureManager.UnregisterTexture(m_BgPic.c_str());
		m_BgPic.clear();
	}

	RenderAnim_Destroy();
	return theUiManager.RemoveFrame( "Data\\UI\\Gut.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_Gut::_IsVisable()
{
	if ( !m_pID_FRAME_Gut )
		return false;
	return m_pID_FRAME_Gut->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_Gut::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_Gut )
		return;

	m_pID_FRAME_Gut->SetVisable( bVisable );
	m_vTalks.clear();
	m_nShowType = -1;
    m_nQuestID = -1;
	m_nModelId = -1;
	m_fStature = -1.0f;

	/*
	 * 2012.6.25 wangshuai
	 * 根据策划要求, 在弹出NPC对话框的时候, 不显示任何玩家、怪物、NPC, 关闭对话框时再恢复原来的状态
	 */
	if (bVisable)
	{
		//if(s_CUI_ID_FRAME_MessageBox.IsVisable())
		//{
  //         s_CUI_ID_FRAME_MessageBox.SetVisable(false);
		//}

		if (s_CUI_ID_FRAME_PACK.IsVisable())
		{
			s_CUI_ID_FRAME_PACK.SetVisable(false);
		}

		if (s_CUI_ID_FRAME_Storage.IsVisable())
		{
			s_CUI_ID_FRAME_Storage.SetVisable(false);
		}


		theHeroGame.GetPlayerMgr()->SuspendCurrentRenderFlag();
	}
	else
	{
		theHeroGame.GetPlayerMgr()->ResumeLastRenderFlag();
	}
}

void CUI_ID_FRAME_Gut::SetNpc(int nNpcId)
{
	m_nNpcID = nNpcId;
	CWorldTile *pTile = CURRENTTILE;
	if(!pTile)
		return;

	CPlayer *pPlayer = theHeroGame.GetPlayerMgr()->FindByID(nNpcId);
	if(!pPlayer)
		return;

	NpcInfo::Npc *pNpc = theNpcInfo.GetNpc(pPlayer->GetNpcID(),pTile->GetMapId());
	if(!pNpc)
		return;

	if(m_nModelId == pNpc->modelId)
		return;

	m_nModelId = pNpc->modelId;
	RenderAnim_SetModelID(m_nModelId);
}

void CUI_ID_FRAME_Gut::Show(int nType,const std::string& info,short nQuestId,const std::string& title)
{
	if(!m_pID_FRAME_Gut)
		return;

    ResetControlSize();
	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID(m_nNpcID);
	if(!pPlayer)
		return;

	UpdateQuestBg(pPlayer->GetNpcID());

	m_pID_TEXT_TextTitle->SetText(pPlayer->GetName()); //设置NPC名称
	m_pID_BUTTON_Accept->SetVisable(false);
	m_pID_BUTTON_Refuse->SetVisable(false);
	m_pID_BUTTON_Finish->SetVisable(false);
	m_pID_BUTTON_OK->SetVisable(false);

	m_nShowType = nType;
	m_nQuestID  = nQuestId;

	m_GroupAward.SetVisible(false);
	m_GroupMe.SetVisible(false);

	LoadTalk(nQuestId,nType);
	ContinueTalk();
}

void CUI_ID_FRAME_Gut::UpdateQuestBg(int nNpcId)
{
	if(!m_pID_FRAME_Gut)
		return;

	NpcInfo::Npc *pNpc = theNpcInfo.GetNpcByStaticId(nNpcId);
	if(!pNpc)
		return;

	if(m_BgPic.compare(pNpc->strHeadPicture.c_str()) !=0)
	{
		if(!m_BgPic.empty())
		    theControlPictureManager.UnregisterTexture(m_BgPic.c_str());

		m_BgPic = pNpc->strHeadPicture;

		char szPath[256] = {0};
		MeSprintf_s(szPath,sizeof(szPath),"%s\\Data\\%s",GetRootPath(),m_BgPic.c_str());

		int nPic = -1;
		theControlPictureManager.RegisterTexture(&nPic,szPath);
	}

	//m_pID_PICTURE_Backdrop->SetPicName(pNpc->strHeadPicture.c_str());
}

void CUI_ID_FRAME_Gut::ShowControlByType()
{
	if(m_nShowType == -1)
		return;

	m_pID_BUTTON_Continue->SetVisable(false);
	m_pID_PICTURE_PlayerBase1->SetVisable(false);
	m_pID_LIST_PlayerGut->SetVisable(false);
	m_pID_BUTTON_Accept->SetVisable(false);
	m_pID_BUTTON_Refuse->SetVisable(false);
	m_pID_BUTTON_Finish->SetVisable(false);
	switch(m_nShowType)
	{
	case MsgAckScript::eNDT_AcceptTask:
		{
			m_pID_BUTTON_Accept->SetVisable(true);
			m_pID_BUTTON_Refuse->SetVisable(true);
		}
		break;
	case MsgAckScript::eNDT_FinishTask:
		{
			m_pID_BUTTON_Finish->SetVisable(true);
		}
		break;
	}

	ShowTaskAward();
}

void CUI_ID_FRAME_Gut::InitializeAtEnterWorld()
{
	if( !m_pID_FRAME_Gut )
		return;

	m_pID_FRAME_Gut->SetVisable(false);
}

void CUI_ID_FRAME_Gut::StartScript(int nNpcId)
{
	MsgReqScript msg;
	msg.stNpcId = nNpcId;
	GettheNetworkInput().SendMsg( &msg );
}

void CUI_ID_FRAME_Gut::EndNpcScript()
{
	MsgScriptCancel msg;
	GettheNetworkInput().SendMsg( &msg );
}

bool CUI_ID_FRAME_Gut::LoadTalk(short sQuestId,int nType)
{
	SQuest* pQuest = theQuestManager.GetQuest(sQuestId);
	if(!pQuest)
		return false;

	m_vTalks.clear();
	QuestTalks sTalk = pQuest->vQuestTalks[1];
	for (int i = 0;i < sTalk.size();++i)
	{
	   int nID = sTalk[i].nStringId%sQuestId;
	   switch(nType)
	   {
	    case MsgAckScript::eNDT_AcceptTask:
		{
			if(nID < 40)
				m_vTalks.push_back(sTalk[i]);
		}
		break;
	    case MsgAckScript::eNDT_FinishTask:
		{
			if(nID >= 40)
				m_vTalks.push_back(sTalk[i]);
		}
		break;
	   }
	}

	return true;
}

bool CUI_ID_FRAME_Gut::ContinueTalk()
{
	if(m_vTalks.empty())
	{
		ShowControlByType();
		return true;
	}

	m_pID_LIST_PlayerGut->SetVisable(false);
	m_pID_BUTTON_Continue->SetVisable(false);
	m_pID_PICTURE_PlayerBase1->SetVisable(false);

	SQuestTalk kTalk = (*m_vTalks.begin());
	m_vTalks.erase(m_vTalks.begin());

	UpdateInfo(&kTalk);

	//如果下句为玩家，直接显示
	if(!m_vTalks.empty())
	{
		SQuestTalk kNextTalk = (*m_vTalks.begin());
		if(kNextTalk.nNpcId == -1)
		{
			m_vTalks.erase(m_vTalks.begin());

			UpdateInfo(&kNextTalk);
		}
	}
	else
		ShowControlByType();

	return true;
}

void CUI_ID_FRAME_Gut::UpdateInfo(SQuestTalk *pTalk)
{
	if(!m_pID_FRAME_Gut)
		return;

	if(!pTalk)
		return;

	if(pTalk->nNpcId > 0)
	{
	   m_pID_TEXT_NpcGut->SetText(theXmlString.GetString(pTalk->nStringId));
	   m_pID_BUTTON_Continue->SetVisable(true);
	}
	else
	{
        m_pID_PICTURE_PlayerBase1->SetVisable(true);
		m_pID_LIST_PlayerGut->SetVisable(true);
		m_pID_LIST_PlayerGut->Clear(true);

		ControlList::S_List stItem;
		stItem.SetData(theXmlString.GetString(pTalk->nStringId));
		m_pID_LIST_PlayerGut->AddItem(&stItem);
	}

	if(pTalk->nNpcAnim != 0)
	{
// 		m_pAnim->PlayAnimByActionName( theXmlString.GetString(pTalk->nNpcAnim),
// 			MexAnimCtrl::eNormalPlay,
// 			0,
// 			1,
// 			MexAnimCtrl::eMaxTimeout,
// 			MexAnimCtrl::eDefaultBlendingTime,
// 			"Idle",
// 			MexAnimCtrl::eNormalPlay 
		RenderAnim_PlayAction(theXmlString.GetString(pTalk->nNpcAnim), 1, "Idle");
	}
}

void CUI_ID_FRAME_Gut::ShowTaskAward()
{
	if(!m_pID_FRAME_Gut)
		return;

	SQuest *pQuest = theQuestManager.GetQuest(m_nQuestID);
	if(!pQuest)
		return;

	m_pID_TEXT_Money->SetVisable(false);
	m_pID_TEXT_EXP->SetVisable(false);
	m_pID_TEXT_CountryMoney->SetVisable(false);
	m_pID_LISTIMG_4592->SetVisable(false);
	m_pID_LISTIMG_4592->Clear();
	m_pID_PICTURE_PlayerBase->SetVisable(false);

	SQuestReward *pReward = NULL;
	for (int n = 0;n < pQuest->stReward.size();++n)
	{
		m_pID_PICTURE_PlayerBase->SetVisable(true);
		pReward = &pQuest->stReward[n];
		char szInfo[256] = {0};
		switch(pReward->byType)
		{
		case SQuest::eReward_Money:
			{
				int money = pReward->Value;
				std::string strText = "";
				thePlayerRole.GetGSCStringFromMoney(pReward->Value, strText);
				m_pID_TEXT_Money->SetText(strText.c_str());
				m_pID_TEXT_Money->SetVisable(true);
			}
			break;
		case SQuest::eReward_JiaoZi:
			{
				int nMoney = pReward->Value;
				std::string strText = "";
				thePlayerRole.GetGSCStringFromJiaoZi(pReward->Value,strText);
				m_pID_TEXT_Money->SetText(strText.c_str());
				m_pID_TEXT_Money->SetVisable(true);
			}
			break;
		case SQuest::eReward_ScriptExp://脚本经验
			{
				// 各个值不同 
				char szWord[256] = {0};
				switch(pReward->Value)
				{
				case 1:
					MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_ScriptExp1));
					break;
				case 2:
					MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_ScriptExp2));
					break;
				}
				m_pID_TEXT_EXP->SetText(szWord);
				m_pID_TEXT_EXP->SetVisable(true);
			}
			break;
		case SQuest::eReward_Exp:
			{
				if (0 != pReward->Value)
				{
					//计算经验值加成
					int RewardValue = pReward->Value;
					/*if(thePlayerRole.IsInWeakCountry())
						RewardValue = RewardValue*1.05;
					else if(thePlayerRole.IsInStrongCountry())
						RewardValue = RewardValue;
					else if(thePlayerRole.GetCountry() != CountryDefine::Country_Init)
						RewardValue = RewardValue * 1.1;*/
					MeSprintf_s(szInfo,sizeof(szInfo),"%d",RewardValue);
					m_pID_TEXT_EXP->SetText(szInfo);
					m_pID_TEXT_EXP->SetVisable(true);
				}
				else
				{
					try
					{
						char filename[MAX_PATH];
						MeSprintf_s(filename,sizeof(filename)/sizeof(char) - 1, "%s/Data/Quest/CalculateExp.string", GetRootPath());

						//
						// 经验计算
						//
						LuaFunction<const char*> CalcExp( ScriptManager::instance().getLuaStateOwner(filename), "CalcExp" );
						const char* RewardValue = CalcExp( pQuest->Id, pQuest->RankId, thePlayerRole.GetLevel() );

						// 空指针
						if ( RewardValue && ( std::string("0") != RewardValue ) )
						{
							if(RewardValue != NULL)
							{
								int nValue = 0;
								nValue = atoi(RewardValue);
								MeSprintf_s(szInfo,sizeof(szInfo),"%d",nValue);
								m_pID_TEXT_EXP->SetText(szInfo);
								m_pID_TEXT_EXP->SetVisable(true);
							}
						}
					}
					catch ( const LuaPlus::LuaException& e )
					{
						OutputDebugString( ( std::string( e.GetErrorMessage() ) + "\n" ).c_str() );
					}
				}
			}
			break;
		case SQuest::eReward_CountryMoney:
			{
				int RewardValue = pReward->Value;
				if (0 != RewardValue)
				{
					std::string strText = "";
					thePlayerRole.GetGSCStringFromMoney(RewardValue,strText);
					m_pID_TEXT_CountryMoney->SetText(strText.c_str());
					m_pID_TEXT_CountryMoney->SetVisable(true);
				}
			}
			break;
		case SQuest::eReward_Item:
			{
				ItemDefine::SItemCommon *pItemDetail = NULL;
				pItemDetail = GettheItemDetail().GetItemByID( pReward->Value);
				if( !pItemDetail )
					continue;

				ControlIconDrag::S_ListImg stItem;
				stItem.SetData( pItemDetail->ustItemID, pReward->Number, eIcon_Enable, false, eTipFlag_Normal, false, true );
				if ( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_WEAPON ||
					pItemDetail->ucItemType == ItemDefine::ITEMTYPE_OTHER ||
					pItemDetail->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
				{
					// 过滤职业装
					unsigned char cPro = thePlayerRole.GetProfession();
					if (!(pReward->shProfession & (1 << cPro)))
						continue;

					if (pReward->shSex != 2 && pReward->shSex != thePlayerRole.GetSex())
						continue;
				}

				m_pID_LISTIMG_4592->SetItem(&stItem);
				m_pID_LISTIMG_4592->SetVisable(true);
			}
			break;
		}
	}
}

void CUI_ID_FRAME_Gut::ResetControlSize()
{
	if(!m_pID_FRAME_Gut)
		return;

	m_pID_FRAME_Gut->SetWidth( SCREEN_WIDTH );
	m_pID_FRAME_Gut->SetHeight( SCREEN_HEIGHT );
	m_pID_PICTURE_Backdrop->SetWidth( SCREEN_WIDTH );
	m_pID_PICTURE_Backdrop->SetHeight( SCREEN_HEIGHT );

	m_pID_PICTURE_Up->SetWidth( SCREEN_WIDTH );
	//m_pID_PICTURE_Up->SetHeight( SCREEN_HEIGHT );

	m_pID_PICTURE_Down->SetWidth( SCREEN_WIDTH );
	//m_pID_PICTURE_Down->SetHeight( SCREEN_HEIGHT );
}

void CUI_ID_FRAME_Gut::ResetDevice()
{
	ResetControlSize();
}

void CUI_ID_FRAME_Gut::ShowBgPic()
{
	if(m_BgPic.empty())
		return;


	RECT rc;
	rc.left = 0;
	rc.top  = 0;
	rc.right = SCREEN_WIDTH;
	rc.bottom = SCREEN_HEIGHT;

	char szPath[256] = {0};
	MeSprintf_s(szPath,sizeof(szPath),"%s\\Data\\%s",GetRootPath(),m_BgPic.c_str());
	//绘制背景
	int nPic = -1;
	theControlPictureManager.BitBlt(&nPic,szPath,&rc);
}

bool CUI_ID_FRAME_Gut::MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	if( !s_CUI_ID_FRAME_Gut.IsVisable() )
		return false;

	switch( msg )
	{
	case WM_LBUTTONUP:
		{
			if( s_CUI_ID_FRAME_Gut.ContinueTalk() )
			{
				return true;
			}
		}
		break;
	case WM_KEYUP:
		{
			switch( wParam )
			{
			case VK_SPACE:
				{
					if( s_CUI_ID_FRAME_Gut.ContinueTalk() )
					{
						return true;
					}
				}							
				break;
			case VK_ESCAPE:
				{
					s_CUI_ID_FRAME_Gut.SetVisable(false);
					s_CUI_NpcTaskDialogBox.CloseDialog(false);
					return true;
				}
				break;
			}
		}
		break;
	}

	return false;
}

float CUI_ID_FRAME_Gut::GetNpcHeight()
{
	if(m_nModelId < 0)
		return -1.0f;

	return m_fStature;
}

void CUI_ID_FRAME_Gut::SetNpcHeightModel(float fHeight,float fScale,float fViewHeight)
{
	NpcHeadModel *pModel = gCfg.GetHeadModelByHeight(fHeight);
	pModel->fScale    = fScale;
	pModel->fViewHigh = fViewHeight;
}

void CUI_ID_FRAME_Gut::SetNpcGutText(const char* pszText)
{
	if(!m_pID_FRAME_Gut)
		return;

	m_pID_TEXT_NpcGut->SetText(pszText);
}