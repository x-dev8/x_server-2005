#include <assert.h>
#include "MeUi/UiManager.h"
#include "NpcTaskDialogBox.h"
#include "NpcChatDialogBox.h"
#include "../Player.h"
#include "PlayerMgr.h"
#include "QuestManager.h"
#include "core/Name.h"
#include "../color_config.h"
#include "XmlStringLanguage.h"
#include "MeUi/ExpressionManager.h"
#include "UIBase.h"
#include "script_manager.h"
#include "TitleConfig.h"
#include "ui/target.h"
#include "GameMain.h"
#include "Common.h"
#include "Progress.h"
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
#include "NpcInfo.h"
#include "WordParser.h"
#include "ScreenInfoManager.h"
#include <string>
#include "ExpressionAction.h"
#include "QuestData.h"
#include "MeFont\MeFontSystem.h"
#include "BgFrame.h"
#include "MeAudio/MeAudio.h"
#include "ui/TaskDialog.h"


//static bool bShowDelay = false;

extern CHeroGame theHeroGame;
CUI_NpcTaskDialogBox s_CUI_NpcTaskDialogBox;
MAP_FRAME_RUN( s_CUI_NpcTaskDialogBox, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_NpcTaskDialogBox, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_NpcTaskDialogBox, ID_BUTTON_EXITOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_NpcTaskDialogBox, ID_BUTTON_FinishOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_NpcTaskDialogBox, ID_BUTTON_AcceptOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_NpcTaskDialogBox, ID_BUTTON_CloseOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_NpcTaskDialogBox, ID_LISTIMG_RewardOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_NpcTaskDialogBox, ID_LISTIMG_RewardOnIconLDBClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_NpcTaskDialogBox, ID_BUTTON_RefuseOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_NpcTaskDialogBox, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_NpcTaskDialogBox, ID_BUTTON_CancelOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_NpcTaskDialogBox, ID_LIST_SELECTOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_NpcTaskDialogBox, ID_BUTTON_NextOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_NpcTaskDialogBox, ID_LISTIMG_SecondItemOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_NpcTaskDialogBox, ID_LISTIMG_SecondItemOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_NpcTaskDialogBox, ID_LISTIMG_SecondItemOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_NpcTaskDialogBox, ID_LISTIMG_SecondItemOnIconRButtonUp )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_NpcTaskDialogBox, ID_LIST_TaskOnListSelectChange )
MAP_SCROLL_BAR_UPDATE_POS_CALLBACK( s_CUI_NpcTaskDialogBox, ID_SCROLLBAR_FRAMEOnScrollBarUpdatePos )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_NpcTaskDialogBox, ID_BUTTON_RETURNOnButtonClick )
CUI_NpcTaskDialogBox::CUI_NpcTaskDialogBox()
{
	ResetAllControlObjects();
	m_shExpHeadId = -1;
}
void CUI_NpcTaskDialogBox::ResetAllControlObjects()
{
	m_pNpcTaskDialogBox = NULL;
	//m_pID_TEXT_Name = NULL;
	//m_pID_BUTTON_EXIT = NULL;
	m_pID_BUTTON_Finish = NULL;
	m_pID_BUTTON_Accept = NULL;
	m_pID_BUTTON_Close = NULL;
	m_pID_LISTIMG_Reward = NULL;
	m_pID_BUTTON_Refuse = NULL;
	m_pID_TEXT_Item = NULL;
	m_pID_TEXT_FinallyItem = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_LIST_SELECT = NULL;
	m_pID_TEXT_W_Wenhao1 = NULL;
	m_pID_TEXT_W_Wenhao2 = NULL;
	m_pID_TEXT_W_Wenhao3 = NULL;
	m_pID_TEXT_W_Wenhao4 = NULL;
	m_pID_TEXT_W_Wenhao5 = NULL;
	m_pID_TEXT_W_Wenhao6 = NULL;
	m_pID_TEXT_W_Wenhao7 = NULL;
	m_pID_TEXT_Info = NULL;
	m_pID_BUTTON_Next = NULL;
	m_pID_LISTIMG_SecondItem = NULL;
	m_pID_LIST_Task = NULL;
	m_pID_SCROLLBAR_FRAME = NULL;
	m_pID_BUTTON_RETURN = NULL;

	m_bPlaySound = false;
	m_bNeedCancel = true;
}

void CUI_NpcTaskDialogBox::RetrieveNpcPic()
{
	if( !m_pNpcTaskDialogBox )
		return;

	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID( m_nNpcId );
	if( !pPlayer )
    {
        //m_pID_PICTURE_NpcHead->SetVisable(false);
		s_CUI_ID_FRAME_BgFrame.SetPicPath(NULL,false);
		s_CUI_ID_FRAME_BgFrame.SetNpcName("");
        return;
    }

	MexResMgr::Record* record = GetMexResMgr()->GetRecord(pPlayer->GetModelId());
	if (record && /*m_pID_PICTURE_NpcHead &&*/ !pPlayer->IsPlayer())
    {
        //m_pID_PICTURE_NpcHead->SetVisable(true);
        //m_pID_PICTURE_NpcHead->SetPicName( record->headPicture.c_str() );
		char szDlgPic[MAX_PATH] = {0};
		s_CUI_ID_FRAME_BgFrame.SetPicPath(NpcCoord::getInstance()->GetNpcDialogPicture(record->headPicture.c_str(), szDlgPic, m_shExpHeadId),true);
		s_CUI_ID_FRAME_BgFrame.SetNpcName(pPlayer->GetName());
	}
    else
	{
        //m_pID_PICTURE_NpcHead->SetVisable(false);
		s_CUI_ID_FRAME_BgFrame.SetPicPath(NULL,false);
		s_CUI_ID_FRAME_BgFrame.SetNpcName("");
	}
}

bool CUI_NpcTaskDialogBox::OnFrameRun()
{
	if(m_TaskProgerss.IsIntonating())
	{
		CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
		if(!pMe)
			return false;

		//lyh++ 添加 移动或者 跳跃的时候 都打断当前执行的脚本，告诉服务器
		if((pMe->IsMoving() || pMe->IsJumping())&& m_TaskProgerss.CanInterrupt() )
		{
			EndIntonateBar();
			return true;
		}

		m_TaskProgerss.Run();
	}

	if(m_Waitting)
	{
		if(HQ_TimeGetTime() - m_LastTaskBuff > 1000)
		{
			Show(m_taskBuff.type,m_taskBuff.info,m_taskBuff.nQuestId,m_taskBuff.title);
			m_Waitting = false;
		}
	}
	return true;
}

bool CUI_NpcTaskDialogBox::OnFrameRender()
{
	ProcessVisualUI();
	if(m_eUIType == UI_Select)
		RefreshSelect();


	if(m_eUIType == UI_NpcTask)
	{
		//RECT rcFrame;
		//m_pNpcTaskDialogBox->GetRealRect(&rcFrame);
		//m_pNpcTaskDialogBox->SetWorking(rcFrame);
		//m_pID_FRAME_Epic->GetFrameFather()->SetRedraw();
	}
	return true;
}

bool CUI_NpcTaskDialogBox::ID_BUTTON_EXITOnButtonClick( ControlObject* pSender )
{
	if( !m_pNpcTaskDialogBox )
		return false;

	m_BuffItemId = -1;
	CloseDialog();
	return true;
}

bool CUI_NpcTaskDialogBox::ID_BUTTON_FinishOnButtonClick( ControlObject* pSender )
{
	if( !m_pNpcTaskDialogBox )
		return false;

	//bShowDelay = true;
	if( IsHaveComQuest( m_BuffItemId ) )
	{
		// 完成任务时包裹满无法领取奖励物品判断     added by ZhuoMeng.Hu		[1/17/2011]
		if( IsPackSpaceEnough( m_BuffItemId ) )
		{
			SendAllMsg();
		}
		else
		{
			return true;
		}
	}
	else
	{
		//if ( m_vtRequestItemUUID.size() > 0 )
		//{
		//	MsgReqDoneQuest msg;
		//	msg.stNpcId = m_nNpcId;
		//	msg.nQuestId = m_nQuestID;
		//	for ( int i = 0; i < m_vtRequestItemUUID.size() && i < MsgReqDoneQuest::EDoneQuest_CommitItemMax; i ++ )
		//	{
		//		msg.nGuid[i] = m_vtRequestItemUUID[i];
		//	}
		//	GettheNetworkInput().SendMsg( &msg );
		//}
		//else
		//{
		BeginNpcScript(m_nNpcId);
		//}
	   LOG_MESSAGE(MEMORY_LOG,LOG_PRIORITY_DEBUG,"Finish::BeginNpcScrip");
	}

	m_bFinishUI = true;
	SetVisable(false);

	//m_nNpcId = -1;

	//else
	//{
	//	CPlayer *pPlayer = theHeroGame.GetPlayerMgr()->FindByID(m_nNpcId);
	//	if(!pPlayer)
	//		return true;

	//	ShowChatDialog("您的任务条件未满足",pPlayer->GetName(),false);
	//}

	return true;
}

// Button
bool CUI_NpcTaskDialogBox::ID_BUTTON_AcceptOnButtonClick( ControlObject* pSender )
{
	if( !m_pNpcTaskDialogBox )
		return false;

	if(m_bReturning)
		return false;

	if(m_BuffItemId != -1)
	   SendAllMsg();
	else
	{
		BeginNpcScript(m_nNpcId);
	   LOG_MESSAGE(MEMORY_LOG,LOG_PRIORITY_DEBUG,"Accept::BeginNpcScrip");
	}
	m_nNpcId = -1;

	m_bFinishUI = true;
	SetVisable(false);
	return true;
}

// Button
bool CUI_NpcTaskDialogBox::ID_BUTTON_CloseOnButtonClick( ControlObject* pSender )
{
	if( !m_pNpcTaskDialogBox )
		return false;

	CloseDialog();
	return true;
}

bool CUI_NpcTaskDialogBox::ID_LISTIMG_RewardOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														 ControlIconDrag::S_ListImg* pItemDrag,
														 ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pNpcTaskDialogBox )
		return false;
	return false;
}

bool CUI_NpcTaskDialogBox::ID_LISTIMG_RewardOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pNpcTaskDialogBox )
		return false;
	return false;
}

bool CUI_NpcTaskDialogBox::ID_BUTTON_RefuseOnButtonClick( ControlObject* pSender )
{
	if( !m_pNpcTaskDialogBox )
		return false;

	if(m_bReturning)
		return false;

	m_BuffItemId = -1;
	CloseDialog();
	return true;
}
extern char* GetFullFileName(const char* filename);
void CUI_NpcTaskDialogBox::PlayNpcSound()
{
	CWorldTile *pTile = CURRENTTILE;
	if(!pTile)
		return;

	CPlayer *pPlayer = theHeroGame.GetPlayerMgr()->FindByID(m_nNpcId);
	if(!pPlayer)
		return;

	NpcInfo::Npc *pNpc = theNpcInfo.GetNpcByName(pPlayer->GetName(),pTile->GetMapId());
	if(!pNpc)
		return;
	const char* pFullFileName = GetFullFileName(pNpc->strSoundPath.c_str());
	if(pFullFileName&&!GSound.IsSoundInPlay(pFullFileName))
	{
		GSound.PlaySound(pFullFileName,false,&pPlayer->GetPos());
	}
}

bool CUI_NpcTaskDialogBox::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if(!m_pNpcTaskDialogBox)
		return true;

	if ( m_pCurCallbackFun )
	{
		bool bCanClose = true;
		bCanClose = m_pCurCallbackFun( m_pID_LIST_SELECT->GetCurSelIndex(), m_pID_LIST_SELECT->GetCurSelItem() );
		if( !bCanClose )
			return true;
	}
	PopSelectBox();
	UpdateSelectBox();
	return true;
	unguard;
	return true;
}

bool CUI_NpcTaskDialogBox::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if( !m_pNpcTaskDialogBox )
		return false;

	CloseDialog();
	return true;
}

void CUI_NpcTaskDialogBox::ID_LIST_SELECTOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{

}

bool CUI_NpcTaskDialogBox::ID_BUTTON_NextOnButtonClick( ControlObject* pSender )
{
	BeginNpcScript(m_nNpcId);
	LOG_MESSAGE(MEMORY_LOG,LOG_PRIORITY_DEBUG,"Next::BeginNpcScrip");
	return true;
}

void CUI_NpcTaskDialogBox::InitializeAtEnterWorld()
{
    m_nNpcId = -1;
    m_BuffItemId = -1;
    m_ShowProgress = false;
    m_eUIType = UI_Select;
    m_vtSelectBox.clear();
	m_bFinishUI = false;
	m_Waitting   = false;
    m_dwButCD    = 0;
	m_bSending   = false;
    m_dwSeleting = false;
    m_nLastQuestId = -1;
	m_nLastNpcId   = -1;
	m_bReturning   = false;

	if( !m_pNpcTaskDialogBox )
        return;

    SortControl();

    m_pNpcTaskDialogBox->SetOnVisibleChangedFun(OnVisibleChanged);
    m_pNpcTaskDialogBox->SetMsgProcFun(UINpcTask_MsgProc);
    m_pNpcTaskDialogBox->SetVisable(false);

    m_pID_LISTIMG_Reward->ShowPressEffect(false);
	m_pID_LISTIMG_SecondItem->ShowPressEffect(false);
    m_pID_TEXT_Info->SetColUrl(Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)));
    
	m_TextFlagSet.clear();
    m_TextFlagSet.push_back(m_pID_TEXT_W_Wenhao1);
    m_TextFlagSet.push_back(m_pID_TEXT_W_Wenhao2);
    m_TextFlagSet.push_back(m_pID_TEXT_W_Wenhao3);
    m_TextFlagSet.push_back(m_pID_TEXT_W_Wenhao4);
    m_TextFlagSet.push_back(m_pID_TEXT_W_Wenhao5);
    m_TextFlagSet.push_back(m_pID_TEXT_W_Wenhao6);
    m_TextFlagSet.push_back(m_pID_TEXT_W_Wenhao7);

    m_pID_LIST_SELECT->SetLBtnDownFun(ID_LIST_SELECTOnListDBClick);
	m_pID_LIST_Task->SetLBtnDownFun(ID_LIST_SELECTTASKOnListDBClient);
	m_pID_LIST_Task->SetChangeColor(false);
	//m_pID_LIST_Task->HaveSelBar( false );	//没有绿色cur选中地图

	//m_pID_SCROLLBAR_FRAME->SetUpdatePosFun(UpdateScollPos);
	m_pID_SCROLLBAR_FRAME->SetStepValue(1);

	m_pID_SCROLLBAR_FRAME->SetStepValue(1);
	m_pID_SCROLLBAR_FRAME->SetPageSize(m_pNpcTaskDialogBox->GetWidth());

	m_pID_LIST_Task->SetVisable(false);
	LoadTaskIcon();
	SetVisable(false);
}

// ListImg / ListEx
bool CUI_NpcTaskDialogBox::ID_LISTIMG_SecondItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															 ControlIconDrag::S_ListImg* pItemDrag,
															 ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}

bool CUI_NpcTaskDialogBox::ID_LISTIMG_SecondItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_NpcTaskDialogBox::ID_LISTIMG_SecondItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_NpcTaskDialogBox::ID_LISTIMG_SecondItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

// List
void CUI_NpcTaskDialogBox::ID_LIST_TaskOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}

// ScrollBar
void CUI_NpcTaskDialogBox::ID_SCROLLBAR_FRAMEOnScrollBarUpdatePos( ControlObject* pSender, int n )
{

}

bool CUI_NpcTaskDialogBox::ID_BUTTON_RETURNOnButtonClick( ControlObject* pSender )
{
	if(m_bReturning)
		return false;

	CWorldTile *pTile = CURRENTTILE;
	if(!pTile)
		return false;

	CPlayer *pPlayer = theHeroGame.GetPlayerMgr()->FindByID(m_nNpcId);
	if(!pPlayer)
		return false;

	NpcInfo::Npc *pNpc = theNpcInfo.GetNpcByName(pPlayer->GetName(),pTile->GetMapId());
	if(!pNpc)
		return false;

	if(pNpc->nTaskMenu > 0)
	{
		LocalShowTask(m_nNpcId,true,true);	
		m_nLastQuestId = -1;
		m_nLastNpcId   = -1;
		m_BuffItemId = -1;
	}
	else
	{
		m_bReturning = true;
		int nNpcID = m_nNpcId;
		m_nNpcId = -1;
		SetNpc(nNpcID);
	}
	return true;
}

bool CUI_NpcTaskDialogBox::_LoadUI()
{
	s_CUI_ID_FRAME_BgFrame.LoadUI();
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\NpcTaskDialogBox.MEUI", false,  UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\NpcTaskDialogBox.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}

bool CUI_NpcTaskDialogBox::DoControlConnect()
{
	theUiManager.OnFrameRun( NpcTaskDialogBox, s_CUI_NpcTaskDialogBoxOnFrameRun );
	theUiManager.OnFrameRender( NpcTaskDialogBox, s_CUI_NpcTaskDialogBoxOnFrameRender ,true);
	theUiManager.OnButtonClick( NpcTaskDialogBox, ID_BUTTON_EXIT, s_CUI_NpcTaskDialogBoxID_BUTTON_EXITOnButtonClick );
	theUiManager.OnButtonClick( NpcTaskDialogBox, ID_BUTTON_Finish, s_CUI_NpcTaskDialogBoxID_BUTTON_FinishOnButtonClick );
	theUiManager.OnButtonClick( NpcTaskDialogBox, ID_BUTTON_Accept, s_CUI_NpcTaskDialogBoxID_BUTTON_AcceptOnButtonClick );
	theUiManager.OnButtonClick( NpcTaskDialogBox, ID_BUTTON_Close, s_CUI_NpcTaskDialogBoxID_BUTTON_CloseOnButtonClick );
	theUiManager.OnIconDragOn( NpcTaskDialogBox, ID_LISTIMG_Reward, s_CUI_NpcTaskDialogBoxID_LISTIMG_RewardOnIconDragOn );
	theUiManager.OnIconLDBClick( NpcTaskDialogBox, ID_LISTIMG_Reward, s_CUI_NpcTaskDialogBoxID_LISTIMG_RewardOnIconLDBClick );
	theUiManager.OnButtonClick( NpcTaskDialogBox, ID_BUTTON_Refuse, s_CUI_NpcTaskDialogBoxID_BUTTON_RefuseOnButtonClick );
	theUiManager.OnButtonClick( NpcTaskDialogBox, ID_BUTTON_OK, s_CUI_NpcTaskDialogBoxID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( NpcTaskDialogBox, ID_BUTTON_Cancel, s_CUI_NpcTaskDialogBoxID_BUTTON_CancelOnButtonClick );
	theUiManager.OnListSelectChange( NpcTaskDialogBox, ID_LIST_SELECT, s_CUI_NpcTaskDialogBoxID_LIST_SELECTOnListSelectChange );
	theUiManager.OnButtonClick( NpcTaskDialogBox, ID_BUTTON_Next, s_CUI_NpcTaskDialogBoxID_BUTTON_NextOnButtonClick );
	theUiManager.OnScrollBarUpdatePos( NpcTaskDialogBox, ID_SCROLLBAR_FRAME, s_CUI_NpcTaskDialogBoxID_SCROLLBAR_FRAMEOnScrollBarUpdatePos );
	theUiManager.OnButtonClick( NpcTaskDialogBox, ID_BUTTON_RETURN, s_CUI_NpcTaskDialogBoxID_BUTTON_RETURNOnButtonClick );

	m_pNpcTaskDialogBox = (ControlFrame*)theUiManager.FindFrame( NpcTaskDialogBox );
	m_pID_BUTTON_Finish = (ControlButton*)theUiManager.FindControl( NpcTaskDialogBox, ID_BUTTON_Finish );
	m_pID_BUTTON_Accept = (ControlButton*)theUiManager.FindControl( NpcTaskDialogBox, ID_BUTTON_Accept );
	m_pID_BUTTON_Close = (ControlButton*)theUiManager.FindControl( NpcTaskDialogBox, ID_BUTTON_Close );
	m_pID_LISTIMG_Reward = (ControlListImage*)theUiManager.FindControl( NpcTaskDialogBox, ID_LISTIMG_Reward );
	m_pID_BUTTON_Refuse = (ControlButton*)theUiManager.FindControl( NpcTaskDialogBox, ID_BUTTON_Refuse );
	m_pID_TEXT_Item = (ControlText*)theUiManager.FindControl( NpcTaskDialogBox, ID_TEXT_Item );
	m_pID_TEXT_FinallyItem = (ControlText*)theUiManager.FindControl( NpcTaskDialogBox, ID_TEXT_FinallyItem );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( NpcTaskDialogBox, ID_BUTTON_OK );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( NpcTaskDialogBox, ID_BUTTON_Cancel );
	m_pID_LIST_SELECT = (ControlList*)theUiManager.FindControl( NpcTaskDialogBox, ID_LIST_SELECT );
	m_pID_TEXT_W_Wenhao1 = (ControlText*)theUiManager.FindControl( NpcTaskDialogBox, ID_TEXT_W_Wenhao1 );
	m_pID_TEXT_W_Wenhao2 = (ControlText*)theUiManager.FindControl( NpcTaskDialogBox, ID_TEXT_W_Wenhao2 );
	m_pID_TEXT_W_Wenhao3 = (ControlText*)theUiManager.FindControl( NpcTaskDialogBox, ID_TEXT_W_Wenhao3 );
	m_pID_TEXT_W_Wenhao4 = (ControlText*)theUiManager.FindControl( NpcTaskDialogBox, ID_TEXT_W_Wenhao4 );
	m_pID_TEXT_W_Wenhao5 = (ControlText*)theUiManager.FindControl( NpcTaskDialogBox, ID_TEXT_W_Wenhao5 );
	m_pID_TEXT_W_Wenhao6 = (ControlText*)theUiManager.FindControl( NpcTaskDialogBox, ID_TEXT_W_Wenhao6 );
	m_pID_TEXT_W_Wenhao7 = (ControlText*)theUiManager.FindControl( NpcTaskDialogBox, ID_TEXT_W_Wenhao7 );
	m_pID_TEXT_Info = (ControlText*)theUiManager.FindControl( NpcTaskDialogBox, ID_TEXT_Info );
	m_pID_BUTTON_Next = (ControlButton*)theUiManager.FindControl( NpcTaskDialogBox, ID_BUTTON_Next );
	m_pID_LISTIMG_SecondItem = (ControlListImage*)theUiManager.FindControl( NpcTaskDialogBox, ID_LISTIMG_SecondItem );
	m_pID_LIST_Task = (ControlList*)theUiManager.FindControl( NpcTaskDialogBox, ID_LIST_Task );
	m_pID_SCROLLBAR_FRAME = (ControlScrollBar*)theUiManager.FindControl( NpcTaskDialogBox, ID_SCROLLBAR_FRAME );
	m_pID_BUTTON_RETURN = (ControlButton*)theUiManager.FindControl( NpcTaskDialogBox, ID_BUTTON_RETURN );
	
	assert( m_pNpcTaskDialogBox );
 	assert( m_pID_BUTTON_Finish );
 	assert( m_pID_BUTTON_Accept );
 	assert( m_pID_BUTTON_Close );
 	assert( m_pID_LISTIMG_Reward );
 	assert( m_pID_BUTTON_Refuse );
 	assert( m_pID_TEXT_Item );
 	assert( m_pID_TEXT_FinallyItem );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_LIST_SELECT );
	assert( m_pID_TEXT_W_Wenhao1 );
	assert( m_pID_TEXT_W_Wenhao2 );
	assert( m_pID_TEXT_W_Wenhao3 );
	assert( m_pID_TEXT_W_Wenhao4 );
	assert( m_pID_TEXT_W_Wenhao5 );
	assert( m_pID_TEXT_W_Wenhao6 );
	assert( m_pID_TEXT_W_Wenhao7 );
	assert( m_pID_TEXT_Info );
	assert( m_pID_BUTTON_Next );
	assert( m_pID_LISTIMG_SecondItem );
	assert( m_pID_LIST_Task );
	assert( m_pID_SCROLLBAR_FRAME );
	assert( m_pID_BUTTON_RETURN );

	m_pID_TEXT_Info->setShowTip(true);
    _SetVisable( false );

	m_pNpcTaskDialogBox->SetFather(s_CUI_ID_FRAME_BgFrame.m_pID_FRAME_BgFrame);

	return true;
}

bool CUI_NpcTaskDialogBox::_UnLoadUI()
{
	//s_CUI_ID_FRAME_BgFrame.UnLoadUI();
	CLOSE_SCRIPT( eUI_OBJECT_NpcTaskDlg );
	ResetAllControlObjects();
    m_pNpcTaskDialogBox = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\NpcTaskDialogBox.MEUI" );
}

bool CUI_NpcTaskDialogBox::_IsVisable()
{
	if( !m_pNpcTaskDialogBox )
		return false;
	return m_pNpcTaskDialogBox->IsVisable();
}

void CUI_NpcTaskDialogBox::_SetVisable( const bool bVisable )
{
	if( !m_pNpcTaskDialogBox )
		return;
	m_pNpcTaskDialogBox->SetVisable( bVisable );
	s_CUI_ID_FRAME_BgFrame.SetVisable( bVisable );
// 	if(!bVisable)
// 	{
// 		m_bPlaySound = true;
// 	}
}

void CUI_NpcTaskDialogBox::SortControl()
{
    if( !m_pNpcTaskDialogBox )
        return;

    m_TaskDialogGroup.Clear();
	m_TaskDialogGroup.AddControl(m_pID_TEXT_Info);
	m_TaskDialogGroup.AddControl(m_pID_TEXT_Item);
	m_TaskDialogGroup.AddControl(m_pID_TEXT_FinallyItem);
	m_TaskDialogGroup.AddControl(m_pID_BUTTON_Finish);
	m_TaskDialogGroup.AddControl(m_pID_BUTTON_Accept);
	m_TaskDialogGroup.AddControl(m_pID_BUTTON_Close);
	m_TaskDialogGroup.AddControl(m_pID_BUTTON_Refuse);
	m_TaskDialogGroup.AddControl(m_pID_LISTIMG_Reward);
	m_TaskDialogGroup.AddControl(m_pID_LISTIMG_SecondItem);
	//m_TaskDialogGroup.AddControl(m_pID_LIST_Task);
	m_TaskDialogGroup.AddControl(m_pID_SCROLLBAR_FRAME);
	m_TaskDialogGroup.AddControl(m_pID_BUTTON_RETURN);
	m_TaskDialogGroup.SetVisible(false);

	m_SelectBoxGroup.AddControl(m_pID_TEXT_Info);
	m_SelectBoxGroup.AddControl(m_pID_BUTTON_OK);
	m_SelectBoxGroup.AddControl(m_pID_BUTTON_Cancel);
	m_SelectBoxGroup.AddControl(m_pID_LIST_SELECT);
	m_SelectBoxGroup.AddControl(m_pID_TEXT_W_Wenhao1);
	m_SelectBoxGroup.AddControl(m_pID_TEXT_W_Wenhao2);
	m_SelectBoxGroup.AddControl(m_pID_TEXT_W_Wenhao3);
	m_SelectBoxGroup.AddControl(m_pID_TEXT_W_Wenhao4);
	m_SelectBoxGroup.AddControl(m_pID_TEXT_W_Wenhao5);
	m_SelectBoxGroup.AddControl(m_pID_TEXT_W_Wenhao6);
	m_SelectBoxGroup.AddControl(m_pID_TEXT_W_Wenhao7);
	m_SelectBoxGroup.SetVisible(false);

	m_ChatDialogGroup.AddControl(m_pID_TEXT_Info);
	m_ChatDialogGroup.AddControl(m_pID_BUTTON_Next);
	m_ChatDialogGroup.AddControl(m_pID_BUTTON_Close);
	//m_ChatDialogGroup.AddControl(m_pID_LIST_Task);
	m_ChatDialogGroup.SetVisible(false);
}

void CUI_NpcTaskDialogBox::Show(int type, const std::string& info, short nQuestId, const std::string& title)
{
	if( !m_pNpcTaskDialogBox )
		return;

// 	if(m_Waitting == false&&bShowDelay == true)
// 	{
// 		m_Waitting = true;
// 		m_LastTaskBuff = HQ_TimeGetTime();
// 		m_taskBuff.type = type;
// 		m_taskBuff.info = info;
// 		m_taskBuff.nQuestId = nQuestId;
// 		m_taskBuff.title    = title;
// 		return;
// 	}


	if(m_bSending)
		return;

	SetUIType(UI_NpcTask);
	RetrieveNpcPic();
	SetVisable(true);

	CWorldTile *pTile = CURRENTTILE;
	if(!pTile)
		return;

	CPlayer *pPlayer = theHeroGame.GetPlayerMgr()->FindByID(m_nNpcId);
	if(!pPlayer)
		return;

	NpcInfo::Npc *pNpc = theNpcInfo.GetNpcByName(pPlayer->GetName(),pTile->GetMapId());
	if(!pNpc)
		return;
	if(m_bPlaySound)
	{
		PlayNpcSound();
		m_bPlaySound = false;
	}

	std::string str = info;
	//NpcCoord::getInstance()->addNpcHyber(str);
	switch (type)
	{
	case MsgAckScript::eNDT_AcceptTask:
		{
			m_pID_BUTTON_Accept->SetVisable(true);
			m_pID_BUTTON_Refuse->SetVisable(true);
			m_pID_BUTTON_Finish->SetVisable(false);
			m_pID_BUTTON_Close->SetVisable(false);
			//if(pNpc->nTaskMenu >0)
				m_pID_BUTTON_RETURN->SetVisable(true);
			//else
			//	m_pID_BUTTON_RETURN->SetVisable(false);
		}
		break;
	case MsgAckScript::eNDT_FinishTask:
		{
			m_pID_BUTTON_Accept->SetVisable(false);
			m_pID_BUTTON_Refuse->SetVisable(false);
			m_pID_BUTTON_Finish->SetVisable(true);
			m_pID_BUTTON_Close->SetVisable(true);
			m_pID_BUTTON_RETURN->SetVisable(false);
		}
		break;
	}

	m_pID_LIST_Task->Clear();
	ControlList::S_List stItem;
	if(type == MsgAckScript::eNDT_AcceptTask)
		stItem.SetData(theXmlString.GetString(eText_Quest_TaskOK),0,NULL,0xff00ff00);
	else
		stItem.SetData(theXmlString.GetString(eText_Quest_TaskOK),1,NULL,0xff00ff00);
	m_pID_LIST_Task->AddItem(&stItem);

	stItem.SetData(theXmlString.GetString(eText_Quest_TaskLevel),-1,NULL,0xff00ff00);
	m_pID_LIST_Task->AddItem(&stItem);

	s_CUI_ID_FRAME_BgFrame.SetNpcName(title.c_str());
	SetTaskInfo(nQuestId,str);

	if(pNpc->nTaskMenu > 0)
	{
		m_nLastNpcId  = m_nNpcId; //记录上次NpcID
		m_nLastQuestId = nQuestId;  //记录上次任务ID
	}
	else
	{
		m_nLastQuestId = -1;
		m_nLastNpcId   = -1;
	}
}

void CUI_NpcTaskDialogBox::SetTaskInfo(short nQuestId,std::string &strInfo)
{
	SQuest *pQuest = theQuestManager.GetQuest( nQuestId );
	if ( !pQuest )
	{
		return;
	}

	CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById( nQuestId );
	if( !pInfo )
		return ;

	// = 0xFFFFFFFF;
	//	蓝（比玩家等级低7级及以上）
	//	绿（比玩家等级低4级及以上）
	//	黄（和玩家等级上下相差3级以内）
	//	橙（比玩家等级高4级及以上）
	//	红（比玩家等级高7级及以上）
	COLORREF col;
	int nDifLevel = pQuest->GetPlayerReceiveQuestLevel() - thePlayerRole.GetLevel();
	if( nDifLevel <= -6 )
	{
		col = Color_Config.getColor(CC_TASK_LESS6);
	}
	else if( nDifLevel <= -3 )
	{
		col = Color_Config.getColor(CC_TASK_LESS3);
	}
	else if( nDifLevel >= 6 )
	{
		col = Color_Config.getColor(CC_TASK_MORE6);
	}
	else if( nDifLevel >= 3 )
	{
		col = Color_Config.getColor(CC_TASK_MORE3);
	}
	else
	{
		col = Color_Config.getColor(CC_TASK_LESS3ANDMORE3);
	}
	ControlList::S_List stList;
	stList.SetData( pQuest->GetQuestName(), pQuest->Id, NULL, col);

	UITask_ShowInfo(&stList, col,strInfo);
}
bool CUI_NpcTaskDialogBox::UITask_ShowInfo( ControlList::S_List* pItem, COLORREF col,std::string &strInfo)
{
	if( !m_pNpcTaskDialogBox )
		return false;

	m_pID_LISTIMG_Reward->Clear();
	m_pID_LISTIMG_Reward->SetVisable(false);
	m_pID_LISTIMG_SecondItem->Clear();
	m_pID_LISTIMG_SecondItem->SetVisable(false);
	m_pID_TEXT_Item->SetVisable(false);
	m_pID_TEXT_FinallyItem->SetVisable(false);

	if ( !pItem )
		return false;
	SQuest *pQuest = theQuestManager.GetQuest( pItem->m_nID );
	CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById( pItem->m_nID );
	if ( !pQuest || !pInfo )
		return false;

	//获得任务目标和任务奖励
	std::string strNeedItemInfo,strRewardInfo;
	GetNeedItemInfo(pQuest,strNeedItemInfo);
	GetRewardItemInfo(pQuest,strRewardInfo);

	std::string strTaskInfo;
	strTaskInfo.clear();

	//strTaskInfo += theXmlString.GetString(eText_Quest_Task);
	//strTaskInfo += pQuest->GetQuestName();
	strTaskInfo += "\n";

	//获得任务目标信息
	bool bHave = false;
	std::string strTarget = pQuest->GetQuestStateInfo();
	if(!strTarget.empty())
	{
		strTaskInfo += "\n";
		strTaskInfo += theXmlString.GetString(eText_Quest_TaskTarget);
		strTaskInfo += "\n";
		strTaskInfo += "    ";
        NpcCoord::getInstance()->addNpcHyberForText(strTarget,NpcCoord::eQuestId,pQuest->Id,pQuest->ReplyTargetId,NULL,true,false);
		strTaskInfo += strTarget;
		bHave = true;
	}
	if(!strNeedItemInfo.empty())
	{
		if(!bHave)
		{
			strTaskInfo += "\n";
			strTaskInfo += theXmlString.GetString(eText_Quest_TaskTarget);
		}
		strTaskInfo += "    ";
		strTaskInfo += strNeedItemInfo;
		strTaskInfo += "\n";
	}
	else
		strTaskInfo += "\n";

	//任务描述
	if(!strInfo.empty())
	{
		std::string strDes = "\n";
		//strDes.clear();
		//strDes += theXmlString.GetString(eText_Quest_TaskDes);
		//strDes += "\n";
		strDes += "    ";
		strDes += strInfo;
		strTaskInfo += strDes;
	}

	if(m_pID_LISTIMG_Reward->GetNullItem() != 0)
	{
		strTaskInfo += "\n";
		strTaskInfo += "\n";
		strTaskInfo += theXmlString.GetString(eText_Quest_TaskReward);
		strTaskInfo += "\n";

		RECT rc;
		int nLeft = 0,nTop = 0,nTextHeight = 0,nListWidth = 0,nListHeight = 0;
		int nTotalLines = 0;
		m_pID_TEXT_Info->SetText(strTaskInfo);
		//总行数
		nTotalLines = m_pID_TEXT_Info->GetMaxLines();

		m_pID_TEXT_Info->GetRectSize(&rc);
		nLeft = rc.left;

		//计算高度
		int nHeight = (nTotalLines + 1) * (FontSystem::GetFontHeight(m_pID_TEXT_Info->GetFontIndex()) + m_pID_TEXT_Info->GetOffsetHeight());
		nTextHeight = rc.top + nHeight;   //字高度
		nTop        = nTextHeight;             //

		ShowRewareItem(nTop,nLeft);
		strTaskInfo += "\n\n";
	}

	//奖励
	if(!strRewardInfo.empty())
	{
		strTaskInfo += "\n";
		strTaskInfo += strRewardInfo;
		strTaskInfo += "\n";
	}

	std::vector<UiCallbackDataBase*> CallBackDataArr;
	NpcCoord::getInstance()->addNpcHyberForText(strTaskInfo,NpcCoord::eMapId,-1,m_nNpcId,&CallBackDataArr);
	m_pID_TEXT_Info->SetVisable(true);
	strTaskInfo.insert(0,pQuest->GetQuestName());
	m_pID_TEXT_Info->SetText(strTaskInfo,Color_Config.getColor(CC_NPCSELECKBOX_INFO),&CallBackDataArr);

	//总行数
	int nTotalLines = m_pID_TEXT_Info->GetMaxLines();
	int nHeight = (nTotalLines + 1) * (FontSystem::GetFontHeight(m_pID_TEXT_Info->GetFontIndex()) + m_pID_TEXT_Info->GetOffsetHeight());

	RECT rc;
	m_pID_TEXT_Info->GetRectSize(&rc);
	ShowTaskList(rc.top + nHeight,rc.left);

	m_ControlSet.Clear();
	m_ControlSet.AddControl(m_pID_TEXT_Info);
	m_ControlSet.AddControl(m_pID_LISTIMG_Reward);
	m_ControlSet.AddControl(m_pID_LISTIMG_SecondItem);
	m_ControlSet.AddControl(m_pID_TEXT_Item);
	m_ControlSet.AddControl(m_pID_TEXT_FinallyItem);
	m_ControlSet.AddControl(m_pID_LIST_Task);

	RECT rcFrame;
	m_pNpcTaskDialogBox->GetRealRect(&rcFrame);

	RECT rcList;
	m_pID_LIST_Task->GetRealRect(&rcList);
	int nCount = rcList.bottom - rcFrame.bottom;

	if(nCount > 0)
	{
		m_pID_SCROLLBAR_FRAME->SetValue(0);
		m_pID_SCROLLBAR_FRAME->SetMaxValue(nCount);
		m_pID_SCROLLBAR_FRAME->SetEnable(true);
	}
	else
	{
		m_pID_SCROLLBAR_FRAME->SetMaxValue(0);
		m_pID_SCROLLBAR_FRAME->SetEnable(false);
	}

	return true;
}

void CUI_NpcTaskDialogBox::ShowIntonateBar(DWORD dwTime,const char* pName /*= NULL*/)
{
	m_ShowProgress = true;
	m_TaskProgerss.ShowTaskProgerss(dwTime,pName);
}

void CUI_NpcTaskDialogBox::EndIntonateBar()
{
	m_ShowProgress = false;
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eClient_AddInfo_2slk_11) );
	m_TaskProgerss.EndIntonating();
	CloseDialog();
}

void CUI_NpcTaskDialogBox::Text_Taskstate_HyberClick( ControlObject* pSender, const char* szData )
{
	if( szData )
		NpcCoord::getInstance()->clickHyberToMiniMap(szData);
}

bool CUI_NpcTaskDialogBox::ScriptSellectCallbackFun( const int nSelectIndex, void *pData )
{
	guardfunc;
	if(!pData)
		return false;

	// 判断能否请求脚本
// 	if( !theHeroGame.GetPlayerMgr() || !theHeroGame.GetPlayerMgr()->CanReqScript() )
// 		return false;

	ControlList::S_List *pItem = (ControlList::S_List*)pData;
	std::string strInfo = pItem->m_szText;
	if(strInfo.find(theXmlString.GetString(eText_QUESTEND)) != std::string::npos && pItem->m_nID == -1)
	{
		s_CUI_NpcTaskDialogBox.CloseDialog();
		return false;
	}
// 	if(stricmp(pItem->m_szText,"离开") == 0)
// 	{
// 		s_CUI_NpcTaskDialogBox.CloseDialog();
// 		return false;
// 	}

	//这两句先注释掉
	if(s_CUI_NpcTaskDialogBox.IsSetSelecting())
		return true;

	s_CUI_NpcTaskDialogBox.SetSelecting(true);

	if (pItem && pItem->m_nID >= dr_MinQuestId)
	{
		//这个有bug，当点未完成任务的时候界面会假死，
		//先简单的做下判断
		CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById( pItem->m_nID );
		if (!pInfo/* || !pInfo->bDone*/)
		{
			/*CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID(s_CUI_NpcTaskDialogBox.GetNpc());
			s_CUI_NpcTaskDialogBox.ShowChatDialog(theXmlString.GetString( eText_TaskNotDone ),pPlayer->GetName(),false);*/
			s_CUI_NpcTaskDialogBox.CloseDialog();
			return false;
		}
		MsgScriptAckShowQuestDlg msg;
		msg.stQuestId = pItem->m_nID;
		//g_selectQuestId = msg.stQuestId;
		GettheNetworkInput().SendMsg( &msg );
	}
	else
	{
		MsgReqScript msg;
		msg.stNpcId = s_CUI_NpcTaskDialogBox.GetNpc();
		msg.chSelItem = pItem->m_nID;
		GettheNetworkInput().SendMsg( &msg );
	}

	return true;
	unguard;
}

bool CUI_NpcTaskDialogBox::ScriptShowQuestDlgCallbackFun( const int nSelectIndex, void *pData )
{
	guardfunc;
	if (!pData)
		return false;

	ControlList::S_List *pItem = (ControlList::S_List*)pData;

	std::string strInfo = pItem->m_szText;
	if(strInfo.find(theXmlString.GetString(eText_QUESTEND)) != std::string::npos && pItem->m_nID == -1)
	{
		s_CUI_NpcTaskDialogBox.CloseDialog();
		return false;
	}

// 	if(stricmp(pItem->m_szText,"离开") == 0)
// 	{
// 		s_CUI_NpcTaskDialogBox.CloseDialog();
// 		return false;
// 	}

	// 判断能否请求脚本
// 	if( !theHeroGame.GetPlayerMgr() || !theHeroGame.GetPlayerMgr()->CanReqScript() )
// 		return false;

	MsgScriptAckShowQuestDlg msg;
	msg.stQuestId = pItem->m_nID;
	//g_selectQuestId = msg.stQuestId;
	GettheNetworkInput().SendMsg( &msg );
	return true;
	unguard;
}

bool CUI_NpcTaskDialogBox::UINpcTask_MsgProc(UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed)
{
	if (!s_CUI_NpcTaskDialogBox.IsVisable())
		return false;


	switch (msg)
	{
	case WM_MOUSEWHEEL:
		{
			if(s_CUI_NpcTaskDialogBox.m_pID_SCROLLBAR_FRAME->IsEnable())
			{
				int delta = 0;
				if (int(wParam) > 0)
					delta = s_CUI_NpcTaskDialogBox.m_pID_SCROLLBAR_FRAME->GetValue() - s_CUI_NpcTaskDialogBox.m_pID_SCROLLBAR_FRAME->GetStepValue() * 3;
				else
					delta = s_CUI_NpcTaskDialogBox.m_pID_SCROLLBAR_FRAME->GetValue() + s_CUI_NpcTaskDialogBox.m_pID_SCROLLBAR_FRAME->GetStepValue() * 3;

				if(delta > 0 && delta <= s_CUI_NpcTaskDialogBox.m_pID_SCROLLBAR_FRAME->GetMaxValue())
					s_CUI_NpcTaskDialogBox.m_pID_SCROLLBAR_FRAME->SetValue(delta);
			}
		}
		break;
	}

	/*switch (msg)
	{
	case WM_KEYUP:
		if (wParam == VK_RETURN)
		{
			switch(s_CUI_NpcTaskDialogBox.GetUIType())
			{
			case UI_Select:
				{
				   s_CUI_NpcTaskDialogBox.ID_BUTTON_OKOnButtonClick(NULL);
				}
				break;
			case UI_NpcTask:
				{
			      s_CUI_NpcTaskDialogBox.ID_BUTTON_FinishOnButtonClick(NULL);
				}
				break;
			case UI_NpcChat:
				{
				  s_CUI_NpcTaskDialogBox.ID_BUTTON_NextOnButtonClick(NULL);
				}
				break;
			}
			return true;
		}
		break;
	}*/

	return false;
}

void CUI_NpcTaskDialogBox::ID_LIST_SELECTOnListDBClick( ControlObject* pSender, ControlList::S_List* pItem )
{
	guardfunc;
	s_CUI_NpcTaskDialogBox.ID_BUTTON_OKOnButtonClick( pSender );
	unguard;
}

void CUI_NpcTaskDialogBox::BeginNpcScript(int nNpcId)
{
	MsgReqScript msg;
	msg.stNpcId = nNpcId;
	GettheNetworkInput().SendMsg( &msg );
}

void CUI_NpcTaskDialogBox::EndNpcScript()
{
	MsgScriptCancel msg;
	GettheNetworkInput().SendMsg( &msg );
}

void CUI_NpcTaskDialogBox::Show( const char* szText, const ControlList::S_List* pItem, const int nItemCount,
		  const char* szCaption/* = ""*/, const bool bModal /*= true*/,
		  const funCallbackFun pFun /*= NULL*/, const int nQuestCount/* = 0*/,
		  const int* questInfos /*= 0*/)
{
	SetUIType(CUI_NpcTaskDialogBox::UI_Select);
	RetrieveNpcPic();
	SetVisable( true );
	if( !pItem || nItemCount <= 0 || nItemCount > MAX_SELECT_ITEM )
		return;
	if(m_bPlaySound)
	{
		PlayNpcSound();
		m_bPlaySound = false;
	}
	S_SelectBox stSelectBox;
	stSelectBox.m_strInfo = szText;
	stSelectBox.m_strCaption = szCaption?szCaption:"";
	stSelectBox.m_pCallbackFun = pFun;
	stSelectBox.m_bModal = bModal;
	memcpy( stSelectBox.m_stItem, pItem, sizeof(ControlList::S_List)*nItemCount );
	stSelectBox.m_nItemCount = nItemCount;
	if (nQuestCount>0 && nQuestCount <= MAX_SELECT_ITEM )
	{
		memcpy( stSelectBox.m_questState, questInfos, sizeof(int) * nQuestCount );
		stSelectBox.m_nQuestCount = nQuestCount;
	}

	for (int i = 0;i < nItemCount;++i)
	{
		if(i >= nQuestCount)
			break;

		std::string strInfo = stSelectBox.m_stItem[i].m_szText;
		if(stSelectBox.m_stItem[i].m_nID < dr_MinQuestId)
		{
			if(stSelectBox.m_questState[i] != 0)
			{
				char szExpress[256] ={0};
				MeSprintf_s(szExpress,sizeof(szExpress)/sizeof(char) - 1,"#%d",stSelectBox.m_questState[i]);
				std::string text = szExpress;
				ExpressionManager::GetInstance().AddExpressionAni(text);
				strInfo.insert(0,text.c_str());
			}
		}
		else
		{
			CPlayerRole::QuestInfo *pInfo = thePlayerRole.FindQuestInfoById(stSelectBox.m_stItem[i].m_nID);
			if(!pInfo)
				continue;

			SQuest* pQuest = theQuestManager.GetQuest(stSelectBox.m_stItem[i].m_nID);
			if(!pQuest)
				continue;

			sTaskIcon tIcon;
			GetTaskIcon(pQuest->chQuestType,tIcon);

			if (theQuestManager.IsQuestDone(stSelectBox.m_questState[i]))
				strInfo.insert(0,tIcon.m_strDone.c_str());								
			else if (theQuestManager.IsQuestActive(stSelectBox.m_questState[i]))
				strInfo.insert(0,tIcon.m_strAct.c_str());								
			else
				strInfo.insert(0,tIcon.m_strNone.c_str());

			SQuestRequirement* pRequire = pQuest->GetReceiveRequirement(SQuest::eRequirement_VarLimit);
			if (pRequire)
			{
				char szWord[256] = {0};
				MeSprintf_s(szWord,sizeof(szWord),"(%d/%d)",thePlayerRole.GetVariableValue( pRequire->wVar ),pRequire->MaxNum);
				strInfo += szWord;
			}
		}

		MeSprintf_s(stSelectBox.m_stItem[i].m_szText,sizeof(stSelectBox.m_stItem[i].m_szText),"%s",strInfo.c_str());		
	}

	m_vtSelectBox.push_back( stSelectBox );
	UpdateSelectBox();
}

void CUI_NpcTaskDialogBox::UpdateSelectBox()
{
	if(!m_pNpcTaskDialogBox)
		return;

	if(m_eUIType != UI_Select)
		return;

	if(m_vtSelectBox.empty())
		return;

	S_SelectBox *pSelectBox;
	pSelectBox = &m_vtSelectBox[0];
	
	NpcCoord::getInstance()->addNpcHyber(pSelectBox->m_strInfo);
	m_pID_TEXT_Info->SetText(pSelectBox->m_strInfo,Color_Config.getColor(CC_NPCDIALOG_INFO));
	//*m_pID_TEXT_Name = pSelectBox->m_strCaption;
	m_pCurCallbackFun = pSelectBox->m_pCallbackFun;

	m_pID_LIST_SELECT->Clear();
	m_pID_LIST_SELECT->AddArrayItem(pSelectBox->m_stItem,pSelectBox->m_nItemCount,false);
	if(pSelectBox->m_nItemCount > 0)
		m_pID_LIST_SELECT->SetCurSelIndex(0);

	RefreshSelect();

	s_CUI_ID_FRAME_BgFrame.SetNpcName(pSelectBox->m_strCaption.c_str());
}

void CUI_NpcTaskDialogBox::RefreshSelect()
{
	if(!m_pNpcTaskDialogBox)
		return;

	if(m_vtSelectBox.empty())
		return;

	S_SelectBox *pSelectBox;
	pSelectBox = &m_vtSelectBox[0];

	for (int i = 0;i < m_TextFlagSet.size();++i)
	{
		m_TextFlagSet[i]->SetText(" ");
		m_TextFlagSet[i]->SetVisable(false);
	}

	int nBegin = m_pID_LIST_SELECT->GetStartIndex();
	int nPicSize = m_TextFlagSet.size();
	int nCount = 0;
	if(nBegin + nPicSize> pSelectBox->m_nItemCount)
		nCount = pSelectBox->m_nItemCount;
	else
	    nCount = nBegin + nPicSize;

	for(int i = nBegin;i < nCount/*pSelectBox->m_nItemCount*/;++i)
	{
		if(pSelectBox->m_stItem[i].m_nID < dr_MinQuestId)
		{
			//int nIndex = i%m_TextFlagSet.size();
			int nIndex = i - nBegin;
			if(pSelectBox->m_questState[i] != 0)
			{
				char szExpress[256] ={0};
				MeSprintf_s(szExpress,sizeof(szExpress)/sizeof(char) - 1,"#%d",pSelectBox->m_questState[i]);
				std::string text = szExpress;
				ExpressionManager::GetInstance().AddExpressionAni(text);

				m_TextFlagSet[nIndex]->SetText(text);
				m_TextFlagSet[nIndex]->SetVisable(true);				
			}
		}
		else
		{
			CPlayerRole::QuestInfo *pInfo = thePlayerRole.FindQuestInfoById(pSelectBox->m_stItem[i].m_nID);
			if(!pInfo)
				continue;

			SQuest* pQuest = theQuestManager.GetQuest(pSelectBox->m_stItem[i].m_nID);
			if(!pQuest)
				continue;

			sTaskIcon tIcon;
			GetTaskIcon(pQuest->chQuestType,tIcon);

			//int nIndex = i%m_TextFlagSet.size();
			int nIndex = i - nBegin;
			if (theQuestManager.IsQuestDone(pSelectBox->m_questState[i]))				
				m_TextFlagSet[nIndex]->SetText(tIcon.m_strDone);//"{#2101}"{#1041}								
			else if (theQuestManager.IsQuestActive(pSelectBox->m_questState[i]))		
				m_TextFlagSet[nIndex]->SetText(tIcon.m_strAct);//"{#2102}"{#1042}								
			else																	
				m_TextFlagSet[nIndex]->SetText(tIcon.m_strNone);//"{#2103}"{#1040}

			m_TextFlagSet[nIndex]->SetVisable(true);
		}
	}

	theUiManager.Compositor();
}

bool CUI_NpcTaskDialogBox::PopSelectBox()
{
#ifdef _DEBUG
	int nCount = m_vtSelectBox.size();
#endif
	if ( m_vtSelectBox.size() <= 0 )
		return false;

	m_vtSelectBox.erase( m_vtSelectBox.begin() );
	return true;
}

void CUI_NpcTaskDialogBox::SetUIType(eUIType eType)
{
	SetSelecting(false);
	m_bReturning = false;
	m_eUIType = eType;
	m_SelectBoxGroup.SetVisible(false);
	m_TaskDialogGroup.SetVisible(false);
	m_ChatDialogGroup.SetVisible(false);
	m_pID_SCROLLBAR_FRAME->SetEnable(false);
	m_pID_SCROLLBAR_FRAME->SetValue(0);
	switch(eType)
	{
	case UI_Select:
		m_SelectBoxGroup.SetVisible(true);
		break;
	case UI_NpcTask:
		m_TaskDialogGroup.SetVisible(true);
		m_pID_SCROLLBAR_FRAME->SetEnable(true);
		break;
	case UI_NpcChat:
		m_ChatDialogGroup.SetVisible(true);
		break;
	default:
		assert(0&&"Task Ui类型错误");
	}
	m_bFinishUI = false;
	//bShowDelay = false;

	m_dwButCD = HQ_TimeGetTime();

	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->GetMe();
	if(!pPlayer)
		return;
	SetVisualPos( *(Vector*)&pPlayer->GetPos());
}

void CUI_NpcTaskDialogBox::SetNpc(int nId,bool bShow/* = true*/)
{
	if(m_nNpcId == nId)
		return;

	if(IsSending())
		return;

	if(m_eUIType == UI_Select)
		PopSelectBox();

	m_BuffItemId = -1;
	EndNpcScript();  //先结束上一个Npc脚本
	LOG_MESSAGE(MEMORY_LOG,LOG_PRIORITY_DEBUG,"SetNpc::EndNpcScript");
	m_nNpcId = nId;
	m_bPlaySound = true;
	if(m_nNpcId == -1)
	{
		SetVisable(false);
		return;
	}

	//********************
	//这里处理特殊对话
	//********************
	const int nMaxListItem = 64;
 	ControlList::S_List pstList[nMaxListItem];
 	int questStates[nMaxListItem];
 	int nQuestCount = 0;
 	theHeroGame.GetPlayerMgr()->RetriveRelationQuestToNpc(m_nNpcId, nQuestCount, questStates, pstList, 0);
	//if( !s_CUI_ID_FRAME_TaskDialog.PlayTalk( m_nNpcId, bShow ) )
	{
		if(!LocalShowTask(m_nNpcId,bShow,true))   //主动打开界面
		{
			BeginNpcScript(m_nNpcId);  //请求脚本
			LOG_MESSAGE(MEMORY_LOG,LOG_PRIORITY_DEBUG,"SetNpc::BeginNpcScrip");
		}
	}
}

void CUI_NpcTaskDialogBox::SetButtonEnable( bool bEnabel )
{
	if( !m_pNpcTaskDialogBox )
		return;

	m_pID_BUTTON_Next->SetEnable( bEnabel );
	m_pID_BUTTON_Close->SetEnable( bEnabel );
}

void CUI_NpcTaskDialogBox::ShowNextQuest(short nQuestId)
{
	SQuest* pQuest = theQuestManager.GetQuest(nQuestId);
	if(!pQuest)
		return;

	CPlayer *pPlayer = theHeroGame.GetPlayerMgr()->FindByID(m_nNpcId);
	if(!pPlayer)
		return;

	int nDlgType = MsgAckScript::eNDT_AcceptTask;
	std::vector<CPlayerRole::QuestInfo*>& vtQuest = thePlayerRole.GetActiveQuestInfo();
	for ( int n=0; n<vtQuest.size(); n++ )
	{
		if (vtQuest[n]->nQuestId >= dr_MaxQuestId)
			break;

		if(vtQuest[n]->nQuestId == nQuestId)
		{
			SQuest *pQuest = theQuestManager.GetQuest(nQuestId);
			if(!pQuest)
				return;

			if(theQuestManager.IsQuestNotGain(vtQuest[n]->chState))
				nDlgType = MsgAckScript::eNDT_AcceptTask;
			else
				nDlgType = MsgAckScript::eNDT_FinishTask;

			break;
		}
	}

	if(nDlgType == MsgAckScript::eNDT_FinishTask&&!IsHaveComQuest(nQuestId))
	{
		int nReplyId = nQuestId * 100 + 12;

		// 表情头像
		std::string strText = "";
		m_shExpHeadId = theHeroGame.GetPlayerMgr()->ProcessExpHead( theXmlString.GetString(nReplyId), strText );
		ShowChatDialog(strText,pPlayer->GetName(),false);
	}
	else
	{
		int nReplyId = nQuestId * 100 + 11;  //接受
		if(nDlgType == MsgAckScript::eNDT_FinishTask)
			nReplyId = nQuestId * 100 + 13;

		// 表情头像
		std::string strText = "";
		m_shExpHeadId = theHeroGame.GetPlayerMgr()->ProcessExpHead( theXmlString.GetString(nReplyId), strText );
		Show(nDlgType,strText,nQuestId,pPlayer->GetName());
	}
}

void CUI_NpcTaskDialogBox::ShowChatDialog(const std::string& strData,const std::string &title, bool bShowNext)
{
	guardfunc;
	if( !m_pNpcTaskDialogBox )
		return;

	SetUIType(UI_NpcChat);
	RetrieveNpcPic();
	SetVisable( true );

	std::string strLink = strData;
	NpcCoord::getInstance()->addNpcHyber(strLink);	// 增加npc的超链接
	m_pID_TEXT_Info->SetText(strData, Color_Config.getColor(CC_NPCSELECKBOX_INFO) );
	//m_pID_TEXT_Name->SetText(title.c_str());
	SetButtonEnable( true );

	s_CUI_ID_FRAME_BgFrame.SetNpcName(title.c_str());

	if ( bShowNext )
	{
		m_pID_BUTTON_Next->SetVisable( true );
		m_pID_BUTTON_Close->SetVisable( true );
	}
	else
	{
		m_pID_BUTTON_Next->SetVisable( false );
		m_pID_BUTTON_Close->SetVisable( true );
	}

	m_pID_LIST_Task->Clear();
	ControlList::S_List stItem;
	stItem.SetData(theXmlString.GetString(eText_Quest_TaskLevel),-1,NULL,0xff00ff00);
	m_pID_LIST_Task->AddItem(&stItem);

	RECT rc;
	int nLeft = 0,nTop = 0,nTextHeight = 0,nListWidth = 0,nListHeight = 0;
	int nTotalLines = 0;
	//总行数
	nTotalLines = m_pID_TEXT_Info->GetMaxLines();
	m_pID_TEXT_Info->GetRectSize(&rc);
	nLeft = rc.left;

	//计算高度
	int nHeight = (nTotalLines + 1) * (FontSystem::GetFontHeight(m_pID_TEXT_Info->GetFontIndex()) + m_pID_TEXT_Info->GetOffsetHeight());
	nTextHeight = rc.top + nHeight;   //字高度
	nTop        = nTextHeight;             //

	ShowTaskList(nTop,nLeft);
	unguard;
}

void CUI_NpcTaskDialogBox::CloseDialog(bool bVisable /*= true*/)
{
	LOG_MESSAGE(MEMORY_LOG,LOG_PRIORITY_DEBUG,"CloseDialog::EndNpcScript");
	EndNpcScript();
	m_nNpcId = -1;
	m_BuffItemId = -1;

	if(m_eUIType == UI_Select)
		PopSelectBox();

	if(bVisable)
	   SetVisable(false);
}

bool CUI_NpcTaskDialogBox::IsButCloseVisable()
{
	if(!m_pNpcTaskDialogBox)
		return false;

    return m_pID_BUTTON_Close->IsVisable();
}

void CUI_NpcTaskDialogBox::ParseExpressText(std::string &strParse,int &nExpressId)
{
	nExpressId = 0;
	//解析字符串
	std::string::size_type nBegin = strParse.find('[');
	std::string::size_type nEnd   =	strParse.find(']');

	if(nBegin != std::string::npos && nEnd != std::string::npos)
	{
		std::string strExpress = strParse.substr(nBegin + 1,nEnd - nBegin - 1);
		std::string strResult  = strParse.substr(nEnd - nBegin + 1); 
		strParse = strResult;

		int nId = 0;
		if(sscanf_s(strExpress.c_str(),"%d",&nId) == 1)
			nExpressId = nId;
	}
}

bool  CUI_NpcTaskDialogBox::LocalShowTask(int nNpcId,bool bShow /*= true*/,bool bReturn /*= false*/)
{
	CWorldTile *pTile = CURRENTTILE;
	if(!pTile)
		return false;

	CPlayer *pPlayer = theHeroGame.GetPlayerMgr()->FindByID(nNpcId);
	if(!pPlayer)
		return false;

	NpcInfo::Npc *pNpc = theNpcInfo.GetNpcByName(pPlayer->GetName(),pTile->GetMapId());
	if(!pNpc)
		return false;

	// 分析表情头像
	std::string strParse = "";
	m_shExpHeadId = theHeroGame.GetPlayerMgr()->ProcessExpHead( theXmlString.GetString(pNpc->nTaskMenu), strParse );

	WordParser words;
	if(words.Parse(strParse.c_str()) == 0)
		return false;

	int nWordCount = words.GetWordCount();
	if(nWordCount <= 0)
		return false;

	const int nMaxListItem = 64;
	ControlList::S_List pstList[nMaxListItem];
	int questStates[nMaxListItem];
	int nQuestCount = 0;

	if(0 == strcmp(theXmlString.GetString(eTitleTypeText_Task),words.GetWord(nWordCount - 1)))
	{
		theHeroGame.GetPlayerMgr()->RetriveRelationQuestToNpc(nNpcId, nQuestCount, questStates, pstList, 0);
		nWordCount -= 1;
	}

	int n = 0;
	for (n = 0; n< nWordCount - 1 ; n++ )
	{
		if( n + nQuestCount >= nMaxListItem )
			break;

		std::string parse = words.GetWord(n + 1);
		int nId = 0;
        ParseExpressText(parse,nId);
		questStates[n + nQuestCount] = nId;
		
		pstList[n + nQuestCount].SetData( parse.c_str(), n );
	}
	if(!bShow&&n + nQuestCount == 0)
	{
		m_nNpcId = -1;
		m_nLastNpcId = -1;
		m_nLastQuestId = -1;
		return true;
	}

	if(!bReturn||!bShow)
	{
		if(n + nQuestCount == 1)
		{
			LocalCallBack(0,(void*)&pstList[0]);
			return true;
		}
	}

	//添加离开
	if(nWordCount + nQuestCount < nMaxListItem)
	{		
		questStates[n + nQuestCount] = 2104;
		pstList[nQuestCount + n].SetData(theXmlString.GetString(eText_QUESTEND),-1);
		++n;
	}

	std::string text = theHeroGame.GetPlayerMgr()->ParseText(words.GetWord(0));

	//SetUIType(CUI_NpcTaskDialogBox::UI_Select);
	//SetNpc(nNpcId);
	Show(text.c_str(), pstList, nWordCount + nQuestCount,
		pNpc->name.c_str(),
		true, LocalCallBack, n + nQuestCount,questStates);

	return true;
}

bool CUI_NpcTaskDialogBox::LocalCallBack( const int nSelectIndex, void *pData )
{
	if(!pData)
		return false;

	ControlList::S_List *pItem = (ControlList::S_List*)pData;
	std::string strInfo = pItem->m_szText;
	if(strInfo.find(theXmlString.GetString(eText_QUESTEND)) != std::string::npos && pItem->m_nID == -1)
	{
		s_CUI_NpcTaskDialogBox.CloseDialog();
		return false;
	}
	s_CUI_NpcTaskDialogBox.SetBuffItemId(pItem->m_nID);
	//如果为任务 
	if (pItem && pItem->m_nID >= dr_MinQuestId)
	{
		s_CUI_NpcTaskDialogBox.ShowNextQuest(pItem->m_nID);
		return true;
	}
	else
	{
		// 	if(HQ_TimeGetTime() - s_CUI_NpcTaskDialogBox.GetButCD() < 1000)
		// 		return true;

		//	s_CUI_NpcTaskDialogBox.UpdateButCD();
		//如果为功能,例如仓库或是商店

		//s_CUI_NpcTaskDialogBox.BeginNpcScript(s_CUI_NpcTaskDialogBox.GetNpc());
		//LOG_MESSAGE(MEMORY_LOG,LOG_PRIORITY_DEBUG,"LocalCallBack::BeginNpcScrip");
	}
	return true;
}

void CUI_NpcTaskDialogBox::SendAllMsg()
{
	if(m_nNpcId == -1)
		return;

	if(m_BuffItemId < dr_MinQuestId || m_BuffItemId> dr_MaxQuestId)
		return;

	m_bSending = true;
	//启动脚本
	//if ( m_vtRequestItemUUID.size() > 0 )
	//{
	//	MsgReqDoneQuest msg;
	//	msg.stNpcId = m_nNpcId;
	//	msg.nQuestId = m_nQuestID;
	//	for ( int i = 0; i < m_vtRequestItemUUID.size() && i < MsgReqDoneQuest::EDoneQuest_CommitItemMax; i ++ )
	//	{
	//		msg.nGuid[i] = m_vtRequestItemUUID[i];
	//	}
	//	GettheNetworkInput().SendMsg( &msg );
	//}
	//else
	//{
	BeginNpcScript(m_nNpcId);
	//}
	
	
	//Dlg3
	MsgScriptAckShowQuestDlg msg;
	msg.stQuestId = m_BuffItemId;
	GettheNetworkInput().SendMsg(&msg);
	BeginNpcScript(m_nNpcId);

	LOG_MESSAGE(MEMORY_LOG,LOG_PRIORITY_DEBUG,"SendAllMsg::BeginNpcScrip");
// 	m_nLastNpcId    = m_nNpcId;
// 	m_nLastQuestId  = m_BuffItemId;
}


bool CUI_NpcTaskDialogBox::SendBuffMsg()
{
	if(m_bSending)
		return true;

	return false;
}

void CUI_NpcTaskDialogBox::ProcessBackEndScript()
{
	//如果脚本结束是进度条Npc调用的
	if(m_ShowProgress)
	{
		m_nNpcId = -1;
		m_ShowProgress = false;
	}
	if(m_bFinishUI)
	{
		m_nNpcId = -1;

		if(m_eUIType == UI_Select)
			PopSelectBox();

		SetVisable(false);
		m_bFinishUI = false;
	}
}

void CUI_NpcTaskDialogBox::OnVisibleChanged(ControlObject *pObject)
{
	if(!pObject->IsVisable()&&!s_CUI_NpcTaskDialogBox.GetFinishUI()&&s_CUI_NpcTaskDialogBox.IsNeedCancel())
	   s_CUI_NpcTaskDialogBox.CloseDialog(false);
}

bool CUI_NpcTaskDialogBox::IsHaveComQuest(short nQuestId)
{
	SQuest *pQuest = theQuestManager.GetQuest( nQuestId );
	if(!pQuest)
		return false;

	CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById( nQuestId );
	if ( !pInfo )
		return false;

	SQuestRequirement *pRequirement = NULL;
	for( int i = 0; i < pQuest->stCommitRequirement.size(); i++ )
	{
		pRequirement = &pQuest->stCommitRequirement[i];
		switch( pRequirement->byType )
		{
		case SQuest::eRequirement_Item:
			{
				ItemDefine::SItemCommon* pItemDetail = NULL;
				pItemDetail = GettheItemDetail().GetItemByID( pRequirement->Value );
				if( !pItemDetail )
					return false;

				int nItemCount = thePlayerRole.m_bag.GetItemCount( pItemDetail->ustItemID );
				if(nItemCount == 0)
				{
					nItemCount = thePlayerRole.m_bagMaterial.GetItemCount(pItemDetail->ustItemID);
					if(nItemCount == 0)
						nItemCount = thePlayerRole.m_bagTask.GetItemCount(pItemDetail->ustItemID);
				}

				if(nItemCount < pRequirement->MaxNum)
					return false;				
			}
			break;
		case SQuest::eRequirement_Monster:
			{
				CPlayerRole::QuestInfo* pVariableInfo = thePlayerRole.FindVariableInfoById( pRequirement->wVar );
				if(!pVariableInfo)
					return false;

				int nVar = pVariableInfo->chState;
				ItemDefine::SMonster* pMonstor = GettheItemDetail().GetMonsterById(pRequirement->Value);
				if (!pMonstor)
					return false;

				if(nVar < pRequirement->MaxNum)
					return false;
			}
			break;
		case SQuest::eRequirement_Action:
			{
				CPlayerRole::QuestInfo* pVariableInfo = thePlayerRole.FindVariableInfoById( pRequirement->wVar );
				if(!pVariableInfo)
					return false;

				int nVar = pVariableInfo->chState;
				if(nVar < pRequirement->MaxNum)
					return false;
			}break;
		case SQuest::eRequirement_Var:
			{
				CPlayerRole::QuestInfo* pVariableInfo = thePlayerRole.FindVariableInfoById( pRequirement->wVar );
				if(!pVariableInfo)
					return false;

				int nVar = pVariableInfo->chState;
				if(nVar < pRequirement->MaxNum)
					return false;
			}break;
		default:
			assert(false);
			break;
		}
	}
	return true;
}

void CUI_NpcTaskDialogBox::RefreshTask(short shQuestId)
{
	if(m_nLastQuestId != shQuestId)
		return;

	m_bSending = false;
	m_BuffItemId = -1;
	CPlayerRole::QuestInfo *pInfo = thePlayerRole.FindQuestInfoById(shQuestId);
	if(!pInfo)
		return;

// 	//未完成不弹出界面
// 	if(!IsHaveComQuest(m_nLastQuestId))
// 		return;
	if(!theQuestManager.IsQuestDone( pInfo->chState ))
		return;

	SetNpc(m_nLastNpcId,false);
}

void CUI_NpcTaskDialogBox::ProcessVisualUI()
{
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
	if (!pMe )
		return;

	Vector vCurPos;
	pMe->GetPos( &vCurPos.x, &vCurPos.y, &vCurPos.z );

	float xoff = vCurPos.x - m_VisualPos.x;
	float yoff = vCurPos.y - m_VisualPos.y;
	float fDist = sqrtf( xoff*xoff + yoff*yoff );
	if(fDist > 8.0f)
	{
		m_bSending = false;
		m_BuffItemId = -1;
		m_bFinishUI = false;
		SetVisable(false);
	}
}

void CUI_NpcTaskDialogBox::GetNeedItemInfo(SQuest *pQuest,std::string &strNeedItem)
{
	//m_vtRequestItemUUID.clear();
	
	strNeedItem.clear();

	if(pQuest->IsSingleRequirement)
		strNeedItem += theXmlString.GetString(eText_Quest_IsSingleRequirement);

	if(!pQuest)
		return;

	//m_nQuestID = pQuest->Id;

	SQuestRequirement *pRequirement = NULL;
	for( int i = 0; i < pQuest->stCommitRequirement.size(); i++ )
	{
		bool bShowMapName = false;

		pRequirement = &pQuest->stCommitRequirement[i];
		char szInfo[256] = "";
		switch( pRequirement->byType )
		{
		case SQuest::eRequirement_Item:
			{
				ItemDefine::SItemCommon* pItemDetail = NULL;
				pItemDetail = GettheItemDetail().GetItemByID( pRequirement->Value );
				if( pItemDetail )
				{
					int nItemCount = thePlayerRole.m_bag.GetItemCount( pItemDetail->ustItemID );
					if(nItemCount == 0)
					{
						nItemCount = thePlayerRole.m_bagMaterial.GetItemCount(pItemDetail->ustItemID);
						if(nItemCount == 0)
							nItemCount = thePlayerRole.m_bagTask.GetItemCount(pItemDetail->ustItemID);
					}
					//else
					//{
					//	SCharItem item;
					//	if(thePlayerRole.m_bag.GetItemByItemID( pItemDetail->ustItemID, &item ))
					//	{
					//		m_vtRequestItemUUID.push_back(item.GetItemGuid());
					//	}
					//	
					//}
					//需要任务物品
					sprintf( szInfo, "\n    %s %s (%ld/%ld)", theXmlString.GetString( eText_NeedItem ),
						pItemDetail->GetItemName(), nItemCount, pRequirement->MaxNum );
				}
			}
			break;
		case SQuest::eRequirement_Monster:
			{
				int nVar = 0;
				CPlayerRole::QuestInfo* pVariableInfo = thePlayerRole.FindVariableInfoById( pRequirement->wVar );
				if( pVariableInfo )
					nVar = pVariableInfo->chState;
				ItemDefine::SMonster* pMonstor = GettheItemDetail().GetMonsterById(pRequirement->Value);
				if (pMonstor)
				{
					//需要
					sprintf( szInfo, "\n    %s %s (%ld/%ld)", theXmlString.GetString(eUI_NeedText),
						pMonstor->GetName(), nVar, pRequirement->MaxNum );

					bShowMapName = true;
				}
			}
			break;
		case SQuest::eRequirement_Action:
			{
				int nVar = 0;
				CPlayerRole::QuestInfo* pVariableInfo = thePlayerRole.FindVariableInfoById( pRequirement->wVar );
				if( pVariableInfo )
					nVar = pVariableInfo->chState;
				sprintf( szInfo, "\n    %s (%ld/%ld)", theXmlString.GetString(pRequirement->Value),
					nVar, pRequirement->MaxNum );
			}break;
		case SQuest::eRequirement_Var:
			{
				int nVar = 0;
				CPlayerRole::QuestInfo* pVariableInfo = thePlayerRole.FindVariableInfoById( pRequirement->wVar );
				if( pVariableInfo )
					nVar = pVariableInfo->chState;
				sprintf(szInfo, "\n    %s%s (%ld/%ld)", theXmlString.GetString(eText_Quest_TaskAim), theXmlString.GetString(pRequirement->nStringID), nVar, pRequirement->MaxNum);
			
				bShowMapName = true;
			}break;
		default:
			//assert(false);
			break;
		}
		std::string strInfo = szInfo;
		NpcCoord::getInstance()->addNpcHyberForText(strInfo,NpcCoord::eQuestId,pQuest->Id,m_nNpcId,NULL,bShowMapName,false);

		strNeedItem += strInfo;
		/*if (pQuest->IsSingleRequirement)
		{
			break;
		}*/
	}
}

void CUI_NpcTaskDialogBox::GetRewardItemInfo(SQuest *pQuest,std::string &strRewardItem)
{
	strRewardItem.clear();
	if(!pQuest)
		return;

		//奖励
	for (int n = 0; n < pQuest->stReward.size();++n)
	{
		SQuestReward *pReward = NULL;
		pReward = &pQuest->stReward[n];
		switch( pReward->byType )
		{
		case SQuest::eReward_Money:
			{
				int money = pReward->Value;
				if (money > 0)
				{
					std::string text = "";
					thePlayerRole.GetGSCStringFromMoney(pReward->Value, text);
					strRewardItem += "\n";
					strRewardItem += theXmlString.GetString(eText_Quest_TaskGold);
					strRewardItem += text.c_str();
				}
			}
			break;
		case SQuest::eReward_CountryMoney:
			{
				//奖励国家资金
				int RewardValue = pReward->Value;
				if (0 != RewardValue)
				{
					std::string text = "";
					thePlayerRole.GetGSCStringFromMoney(RewardValue, text);
					strRewardItem += "\n";
					strRewardItem += theXmlString.GetString(eText_Quest_CountryMoney);
					strRewardItem += text.c_str();
				}
			}
			break;
		case SQuest::eReward_ScriptExp://脚本经验
			{
				// 各个值不同 
				char szWord[256] = {0};
				switch(pReward->Value)
				{
				case 1:
					MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_TaskScriptExp),theXmlString.GetString(eText_Quest_ScriptExp1));
					break;
				case 2:
					MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_TaskScriptExp),theXmlString.GetString(eText_Quest_ScriptExp2));
					break;
				}
				strRewardItem += "\n";
				strRewardItem += szWord;
			}
			break;
		case SQuest::eReward_Exp:
			{
				if (0 != pReward->Value)
				{
					//*m_pID_TEXT_Exp = pReward->Value;

					//计算经验值加成
					int RewardValue = pReward->Value;
					/*if(thePlayerRole.IsInWeakCountry())
						RewardValue = RewardValue*1.05;
					else if(thePlayerRole.IsInStrongCountry())
						RewardValue = RewardValue;
					else if(thePlayerRole.GetCountry() != CountryDefine::Country_Init)
						RewardValue = RewardValue * 1.1;*/

					char szWord[256] = {0};
					MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_TaskExp),RewardValue);
					strRewardItem += "\n";
					strRewardItem += szWord;
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
								//if(sscanf_s(RewardValue,"%d",&nValue) == 1)
								{
									nValue = atoi(RewardValue);
									char szWord[256] = {0};
									MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_TaskExp),nValue);
									strRewardItem += "\n";
									strRewardItem += szWord;
								}
							}
							//*m_pID_TEXT_Exp = RewardValue;
						}
					}
					catch ( const LuaPlus::LuaException& e )
					{
						OutputDebugString( ( std::string( e.GetErrorMessage() ) + "\n" ).c_str() );
					}
				}
			}
			break;
		case SQuest::eReward_SkillExp:
			{

			}
			break;
		case SQuest::eReward_Item:
			{
				ItemDefine::SItemCommon *pItemDetail = NULL;
				pItemDetail = GettheItemDetail().GetItemByID( pReward->Value);
				if( !pItemDetail )
					continue;
				ControlIconDrag::S_ListImg stItem;
				stItem.SetData( pItemDetail->ustItemID, pReward->Number );
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
				if(m_pID_LISTIMG_Reward->GetNullItem() == 0)
				    m_pID_LISTIMG_Reward->SetItem( &stItem );
				else if(m_pID_LISTIMG_SecondItem->GetNullItem() == 0)
				   m_pID_LISTIMG_SecondItem->SetItem( &stItem );
				//m_pID_TEXT_Item->SetVisable(true);
				//m_pID_LISTIMG_Reward->SetVisable( true );
				//m_pID_LISTIMG_SecondItem->SetVisable(true);
			}
			break;
		case SQuest::eReward_Reputation:
			{
				char szWord[256] = {0};
				MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_TaskMingWang),pReward->Value);
				strRewardItem += "\n";
				strRewardItem += szWord;
			}
			break;
		case SQuest::eReward_Exploit:
			{
				char szWord[256] = {0};
				MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_TaskGongXun),pReward->Value);
				strRewardItem += "\n";
				strRewardItem += szWord;
			}
			break;
		case SQuest::eReward_Title:
			{
				TitleConfig::Title* pTitle = theTitleConfig.GetTitleByTitleID( pReward->Value );
				if( pTitle )
				{
					strRewardItem += "\n";
					strRewardItem += theXmlString.GetString(eText_Quest_TaskTitle);
					strRewardItem += pTitle->GetName();
				}
			}
			break;
		case SQuest::eReward_GuildContribute:
			{
				char szWord[256] = {0};
				MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_TaskGuildContribute),pReward->Value);
				strRewardItem += "\n";
				strRewardItem += szWord;
			}
			break;
		case SQuest::eReward_SpecialItem:
			{
				ItemDefine::SItemCommon *pItemDetail = NULL;
				pItemDetail = GettheItemDetail().GetItemByID( pReward->Value);
				if( !pItemDetail )
					continue;
				ControlIconDrag::S_ListImg stItem;
				stItem.SetData( pItemDetail->ustItemID, pReward->Number );
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
// 				if( pSpiecialItemImage )
// 				{
// 					pSpiecialItemImage->SetItem( &stItem );
// 					pSpiecialItemImage->SetVisable( true );
// 				}
// 				pSpiecialItemText->SetVisable(true);

			}
			break;
		case SQuest::eReward_JiaoZi:
			{
				if (pReward->Value > 0)
				{
					std::string text = "";
					thePlayerRole.GetGSCStringFromJiaoZi(pReward->Value, text);

					strRewardItem += "\n";
					strRewardItem += theXmlString.GetString(eText_Quest_TaskJiaozi);
					strRewardItem += text;
				}
			}
			break;
		case SQuest::eReward_Honor:
			{
				char szWord[256] = {0};
				MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_TaskRongYu),pReward->Value);
				strRewardItem += "\n";
				strRewardItem += szWord;
			}
			break;
		default:
			assert(false);
			break;
		}
	}
}

void CUI_NpcTaskDialogBox::ShowRewareItem(int nTop,int nLeft)
{
	if(!m_pNpcTaskDialogBox)
		return;

	//获得实际控件坐标
	RECT rcList,rcText;
	m_pID_LISTIMG_Reward->GetRectSize(&rcList);
	m_pID_TEXT_Item->GetRectSize(&rcText);

	//调整ListImage控件
	int nListHeight = 0,nListWidth = 0;
	nListWidth  = m_pID_LISTIMG_Reward->GetWidth();
	nListHeight = m_pID_LISTIMG_Reward->GetHeight();

	RECT listRect;
	listRect.left = rcList.left;
	listRect.top  = nTop;
	listRect.bottom = listRect.top + nListHeight;
	listRect.right  = listRect.left + nListWidth;
	m_pID_LISTIMG_Reward->SetRealRect(&listRect);

	//设置描述文件
	ControlListImage::S_ListImg *pListImg = m_pID_LISTIMG_Reward->GetItemByIndex(0);
	if(!pListImg)
		return;

	if(pListImg->IsNull())
		return;

	int nTextWidth = 0,nTextHeight = 0;
	nTextWidth  = m_pID_TEXT_Item->GetWidth();
	nTextHeight = m_pID_TEXT_Item->GetHeight();

	RECT desRc;
	desRc.left = rcText.left;
	desRc.top  =  nTop + (nListHeight - nTextHeight)/2;
	desRc.right = desRc.left + nTextWidth;
	desRc.bottom = desRc.top + nTextHeight;
	m_pID_TEXT_Item->SetRealRect(&desRc);

	ItemDefine::SItemCommon *pCommon = GettheItemDetail().GetItemByID(pListImg->m_pkIconInfo->Id());
	if(!pCommon)
		return;

	m_pID_TEXT_Item->SetText(pCommon->GetItemName());

	m_pID_LISTIMG_Reward->SetVisable(true);
	m_pID_TEXT_Item->SetVisable(true);


	//第二个
	int nIndex = m_pID_LISTIMG_SecondItem->GetNullItem();
	if(nIndex == 0)
		return;

	pListImg = m_pID_LISTIMG_SecondItem->GetItemByIndex(0);
	if(!pListImg)
		return;

	if(pListImg->IsNull())
		return;

	m_pID_LISTIMG_SecondItem->GetRectSize(&rcList);
	m_pID_TEXT_FinallyItem->GetRectSize(&rcText);

	nListWidth = m_pID_LISTIMG_SecondItem->GetWidth();
	nListHeight = m_pID_LISTIMG_SecondItem->GetHeight();

	listRect.left = rcList.left;
	listRect.top  = nTop;
	listRect.bottom = listRect.top + nListHeight;
	listRect.right  = listRect.left + nListWidth;
	m_pID_LISTIMG_SecondItem->SetRealRect(&listRect);

	m_pID_TEXT_FinallyItem->GetRectSize(&rcText);
	nTextWidth = m_pID_TEXT_FinallyItem->GetWidth();
	nTextHeight = m_pID_TEXT_FinallyItem->GetHeight();

	RECT rcTextName;
	rcTextName.left = rcText.left;
	rcTextName.top = nTop + (nListHeight - nTextHeight)/2;
	rcTextName.right = rcTextName.left + nTextWidth;
	rcTextName.bottom = rcTextName.top + nTextHeight;
	m_pID_TEXT_FinallyItem->SetRealRect(&rcTextName);

	//设置名称
    pCommon = GettheItemDetail().GetItemByID(pListImg->m_pkIconInfo->Id());
	if(!pCommon)
		return;

	m_pID_TEXT_FinallyItem->SetText(pCommon->GetItemName());


	m_pID_LISTIMG_SecondItem->SetVisable(true);
	m_pID_TEXT_FinallyItem->SetVisable(true);
}

void CUI_NpcTaskDialogBox::ID_LIST_SELECTTASKOnListDBClient(ControlObject *pSender, ControlList::S_List *pItem)
{
	if(!pItem)
		return;

	if(pItem->m_nID == 0)
		s_CUI_NpcTaskDialogBox.ID_BUTTON_AcceptOnButtonClick(pSender);
	else if(pItem->m_nID == 1)
		s_CUI_NpcTaskDialogBox.ID_BUTTON_FinishOnButtonClick(pSender);
	else if(pItem->m_nID == -1)
		s_CUI_NpcTaskDialogBox.ID_BUTTON_RefuseOnButtonClick(pSender);
}

void CUI_NpcTaskDialogBox::ShowTaskList(int nTop,int nLeft)
{
	if(!m_pNpcTaskDialogBox)
		return;

	RECT rc;
	m_pID_LIST_Task->GetRectSize(&rc);

	int nListWidth  = m_pID_LIST_Task->GetWidth();
	int nListHeight = m_pID_LIST_Task->GetHeight();

	RECT rcList;
	rcList.left = rc.left;
	rcList.top  = nTop;
	rcList.right = rcList.left + nListWidth;
	rcList.bottom = rcList.top + nListHeight;

	m_pID_LIST_Task->SetRealRect(&rcList);
}

void CUI_NpcTaskDialogBox::UpdateScollPos(ControlObject *pSender,int n)
{
	s_CUI_NpcTaskDialogBox.UpdatePos(n);
}

void CUI_NpcTaskDialogBox::UpdatePos(int n)
{
	m_ControlSet.ChangePos(n);
}

void CUI_NpcTaskDialogBox::LoadTaskIcon()
{
	MeXmlDocument doc;
	char szWord[256] = {0};
	MeSprintf_s(szWord,sizeof(szWord),"%s\\Data\\ClientConfig\\GameSetting.config",GetRootPath());
	if( !doc.LoadFile(szWord) )
		return;

	m_IconSet.clear();
	MeXmlElement* pRoot = doc.FirstChildElement("Project")->FirstChildElement("TaskType");
	if(pRoot)
	{
		MeXmlElement* pSubElem = pRoot->FirstChildElement("Task");
		for (;pSubElem != NULL;pSubElem = pSubElem->NextSiblingElement())
		{
			sTaskIcon nIcon;

			int nValue = 0;
			pSubElem->Attribute("Type",&nValue);

			const char* pVar = pSubElem->Attribute("None");
			if(pVar)
				nIcon.m_strNone = _tstring::toNarrowString(_tstring::UTF8towcs(pVar).c_str());

			pVar = pSubElem->Attribute("Active");
			if(pVar)
				nIcon.m_strAct = _tstring::toNarrowString(_tstring::UTF8towcs(pVar).c_str());

			pVar = pSubElem->Attribute("Done");
			if(pVar)
				nIcon.m_strDone =  _tstring::toNarrowString(_tstring::UTF8towcs(pVar).c_str());

			m_IconSet.insert(std::make_pair(nValue,nIcon));
		}
	}
	return;
}

void CUI_NpcTaskDialogBox::GetTaskIcon(int nType,sTaskIcon &icon)
{
	std::map<int,sTaskIcon>::iterator it = m_IconSet.find(nType);
	if(it == m_IconSet.end())
		return;

	icon.m_nType = it->second.m_nType;
	icon.m_strDone = it->second.m_strDone;
	icon.m_strAct  = it->second.m_strAct;
	icon.m_strNone = it->second.m_strNone;
}

bool CUI_NpcTaskDialogBox::sTaskProgress::CanInterrupt() const
{
	if( m_nItemID == 0 )
		return true;

	ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID( m_nItemID );
	if( !pItem )
		return true;

	if( !pItem->bCanSingingInterrupt )
		return true;

	return false;
}

// added by ZhuoMeng.Hu		[1/17/2011]
bool CUI_NpcTaskDialogBox::IsPackSpaceEnough( int nQuestId )
{
	SQuest *pQuest = theQuestManager.GetQuest( nQuestId );
	if( !pQuest )
		return false;

	CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById( nQuestId );
	if( !pInfo )
		return false;

	int nNormalCnt( 0 ), nMaterialCnt( 0 ), nTaskCnt( 0 );
	for( int i = 0; i < pQuest->stReward.size(); ++i )
	{
		SQuestReward *pReward = NULL;
		pReward = &pQuest->stReward[i];

		// 这里奖励有领取限制，设计得有点诡异
		// 有性别限制
		if( pReward->shSex >= Sex_Male && pReward->shSex < Sex_Max )
		{
			if( pReward->shSex != thePlayerRole.GetSex() )
				continue;
		}

		// 有职业限制
		if( pReward->shProfession > 0 )
		{
			if( !( pReward->shProfession & 2 << thePlayerRole.GetProfession() ) )
				continue;
		}

		switch( pReward->byType )
		{
		case SQuest::eReward_Item:
		case SQuest::eReward_SpecialItem:
			{
				ItemDefine::SItemCommon *pItemDetail = NULL;
				pItemDetail = GettheItemDetail().GetItemByID( pReward->Value );
				if( !pItemDetail )
					continue;

				SCharItem charItem;
				charItem.itembaseinfo.ustItemID = pItemDetail->ustItemID;
				charItem.itembaseinfo.ustItemCount = pReward->Number;
				charItem.SetBounded( pReward->bIsBound );

				// 记录是否需要新的格子
				bool bNewGrid( false );

				switch( thePlayerRole.GetBagTypeByItemType( pItemDetail->ucItemType ) )
				{
				case BT_NormalItemBag:
					{
						if( !thePlayerRole.m_bag.CanPushItem( charItem, bNewGrid ) )
						{
							CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_TaskError_PackFull,
								theXmlString.GetString( eText_NormalPackFull ) );
							return false;
						}
						if( bNewGrid )
						{
							++nNormalCnt;
						}
					}
					break;
				case BT_MaterialBag:
					{
						if( !thePlayerRole.m_bagMaterial.CanPushItem( charItem, bNewGrid ) )
						{
							CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_TaskError_PackFull,
								theXmlString.GetString( eText_MaterialPackFull ) );
							return false;
						}
						if( bNewGrid )
						{
							++nMaterialCnt;
						}
					}
					break;
				case BT_TaskBag:
					{
						if( !thePlayerRole.m_bagTask.CanPushItem( charItem, bNewGrid ) )
						{
							CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_TaskError_PackFull,
								theXmlString.GetString( eText_TaskPackFull ) );
							return false;
						}
						if( bNewGrid )
						{
							++nTaskCnt;
						}
					}
					break;
				default:
					break;
				}
			}
			break;
		default:
			break;
		}
	}

	if( thePlayerRole.m_bag.GetNullItemCount() < nNormalCnt )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_TaskError_PackFull, theXmlString.GetString( eText_NormalPackFull ) );
		return false;
	}

	if( thePlayerRole.m_bagMaterial.GetNullItemCount() < nMaterialCnt )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_TaskError_PackFull, theXmlString.GetString( eText_MaterialPackFull ) );
		return false;
	}

	if( thePlayerRole.m_bagTask.GetNullItemCount() < nTaskCnt )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_TaskError_PackFull, theXmlString.GetString( eText_TaskPackFull ) );
		return false;
	}

	return true;
}
