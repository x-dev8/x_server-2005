/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Users\zhangjiayi.SHENWANG\Desktop\TaskDialog.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Ui/TaskDialog.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "XmlStringLanguage.h"
#include "NpcTaskDialogBox.h"
#include "Common.h"
#include "FilePath.h"

CUI_ID_FRAME_TaskDialog s_CUI_ID_FRAME_TaskDialog;
MAP_FRAME_RUN( s_CUI_ID_FRAME_TaskDialog, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_TaskDialog, OnFrameRender )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_TaskDialog, ID_LIST_OptionOnListSelectChange )

static std::string s_strTalkHeadPicFilename[Sex_Max] = 
{
	"./data/ui/headpicture/HalfLength/Role_Male.dds",
	"./data/ui/headpicture/HalfLength/Role_Female.dds"
};

CUI_ID_FRAME_TaskDialog::CUI_ID_FRAME_TaskDialog()
{
	// Member
	m_pID_FRAME_TaskDialog = NULL;
	m_pID_PICTURE_Player = NULL;
	m_pID_PICTURE_NPC = NULL;
	m_pID_TEXT_Info = NULL;
	m_pID_TEXT_Tips = NULL;
	m_pID_PICTURE_TipsPic = NULL;
	m_pID_LIST_Option = NULL;
	m_bClickToContinue = true;
	m_bDirty= true;
	m_nNpcId = -1;
	m_bShow = false;
	m_vTalks.clear();

}
// Frame
bool CUI_ID_FRAME_TaskDialog::OnFrameRun()
{
 	if( !IsVisable() )
		return false;

	if( m_vTalks.empty() )
	{
		SetVisable( false );
		// �����εĶԻ�����
		m_pID_TEXT_Info->SetText("");
		m_pID_LIST_Option->Clear();
		return false;
	}

	if( !m_bDirty )
		return false;

	SetDirty( false );

	/// ���ã������������Ի�
	m_bClickToContinue = true;

	/// ȡ������
	SQuestTalk kTalk = (*m_vTalks.begin());

	/// ��ʾ���ݣ�����ͷ�����ֻ���ѡ��
	// 1.ͷ��
	std::string strPicFilename;
	m_pID_PICTURE_NPC->SetVisable( false );
	m_pID_PICTURE_Player->SetVisable( false );
	ControlPicture* pHeadPicCtrl = NULL;
	if( kTalk.nNpcId != -1 )//�����Լ�
	{
		strPicFilename = GetBigHeadPicName( m_nNpcId );
		pHeadPicCtrl = m_pID_PICTURE_NPC;
	}
	else // �Լ�
	{
		int nSex = thePlayerRole.GetSex();
		if( nSex >= Sex_Male && nSex < Sex_Max )
		{
			strPicFilename = GetPlayerHeadPicName();
			if ( strPicFilename.empty() )
			{
				strPicFilename = s_strTalkHeadPicFilename[nSex];
			}
			pHeadPicCtrl = m_pID_PICTURE_Player;
		}
	}
	if( pHeadPicCtrl && ( strPicFilename.compare( "" ) != -1 ) )
	{
		// �ж��Ƿ��д�ͷ��û�����������ui
		char acPicFullname[MAX_PATH] = {0};
		MeSprintf_s( acPicFullname, MAX_PATH, "%s\\%s", GetRootPath(), strPicFilename.c_str() );
		if( !CFilePath::IsExist( acPicFullname ) )
			pHeadPicCtrl->SetVisable( false );
		else
		{
			pHeadPicCtrl->SetPicName( strPicFilename.c_str() );
			pHeadPicCtrl->SetVisable( true );
		}		
	}
	// 2.����
	m_pID_TEXT_Info->SetText( theXmlString.GetString( kTalk.nStringId ) );
	// 3.ѡ��
	m_pID_LIST_Option->Clear();
	m_pID_LIST_Option->SetVisable( false );
	for( int i = 0 ; i < kTalk.vOptions.size(); ++ i )
	{
		m_pID_LIST_Option->SetVisable( true );
		m_bClickToContinue = false;
		ControlList::S_List kItem;
		kItem.SetData( theXmlString.GetString( kTalk.vOptions[i].nStringId ), i );
		m_pID_LIST_Option->AddItem( &kItem );
		
	}	

	return true;
}
bool CUI_ID_FRAME_TaskDialog::OnFrameRender()
{
	return true;
}

// List
void CUI_ID_FRAME_TaskDialog::ID_LIST_OptionOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_TaskDialog )
		return;
	if( m_vTalks.empty() )
		return;

	SQuestTalk kTalk = (*m_vTalks.begin());
	m_vTalks.erase(m_vTalks.begin());

	if( (int)kTalk.vOptions.size() < ( pItem->m_nID + 1 ) )
		return;

	m_vTalks = kTalk.vOptions[pItem->m_nID].vTalks;

	SetDirty( true );
}

// װ��UI 
bool CUI_ID_FRAME_TaskDialog::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\TaskDialog.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("��ȡ�ļ�[Data\\UI\\TaskDialog.MEUI]ʧ��")
		return false;
	}
	return DoControlConnect();
}
// �����ؼ�
bool CUI_ID_FRAME_TaskDialog::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_TaskDialog, s_CUI_ID_FRAME_TaskDialogOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_TaskDialog, s_CUI_ID_FRAME_TaskDialogOnFrameRender );
	theUiManager.OnListSelectChange( ID_FRAME_TaskDialog, ID_LIST_Option, s_CUI_ID_FRAME_TaskDialogID_LIST_OptionOnListSelectChange );

	m_pID_FRAME_TaskDialog = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_TaskDialog );
	m_pID_PICTURE_Player = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskDialog, ID_PICTURE_Player );
	m_pID_PICTURE_NPC = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskDialog, ID_PICTURE_NPC );
	m_pID_TEXT_Info = (ControlText*)theUiManager.FindControl( ID_FRAME_TaskDialog, ID_TEXT_Info );
	m_pID_TEXT_Tips = (ControlText*)theUiManager.FindControl( ID_FRAME_TaskDialog, ID_TEXT_Tips );
	m_pID_PICTURE_TipsPic = (ControlPicture*)theUiManager.FindControl( ID_FRAME_TaskDialog, ID_PICTURE_TipsPic );
	m_pID_LIST_Option = (ControlList*)theUiManager.FindControl( ID_FRAME_TaskDialog, ID_LIST_Option );

	assert( m_pID_FRAME_TaskDialog );
	assert( m_pID_PICTURE_Player );
	assert( m_pID_PICTURE_NPC );
	assert( m_pID_TEXT_Info );
	assert( m_pID_TEXT_Tips );
	assert( m_pID_PICTURE_TipsPic );

	if( m_pID_FRAME_TaskDialog )
		m_pID_FRAME_TaskDialog->SetMsgProcFun( MsgProc );

	m_pID_FRAME_TaskDialog->enableEscKey( false );
	m_pID_FRAME_TaskDialog->SetOnEscResponseType( ControlFrame::EscResponse_SkipMe );

	m_pID_PICTURE_Player->SetVisable( false );
	m_pID_PICTURE_NPC->SetVisable( false );

	SetVisable(false);
	return true;
}
// ж��UI
bool CUI_ID_FRAME_TaskDialog::_UnLoadUI()
{
	m_pID_FRAME_TaskDialog = NULL;
	m_pID_PICTURE_Player = NULL;
	m_pID_PICTURE_NPC = NULL;
	m_pID_TEXT_Info = NULL;
	m_pID_TEXT_Tips = NULL;
	m_pID_PICTURE_TipsPic = NULL;
	m_pID_LIST_Option = NULL;
	m_nNpcId = -1;
	m_bShow = false;
	return theUiManager.RemoveFrame( "Data\\UI\\TaskDialog.MEUI" );
}
// �Ƿ����
bool CUI_ID_FRAME_TaskDialog::_IsVisable()
{
	if ( !m_pID_FRAME_TaskDialog )
		return false;
	return m_pID_FRAME_TaskDialog->IsVisable();
}
// �����Ƿ����
void CUI_ID_FRAME_TaskDialog::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_TaskDialog )
		return;
	UiDrawer::StartFillFullScreen( 500, bVisable ); // ��Ļ���
	m_pID_FRAME_TaskDialog->SetVisable( bVisable );
}

bool CUI_ID_FRAME_TaskDialog::PlayTalk( int nNpcId, bool bShow )
{
	CPlayer* pNpc = theHeroGame.GetPlayerMgr()->FindByID( nNpcId );
	if( !pNpc || !pNpc->IsNpc() )
	{
		return false;
	}

	std::vector<SQuest*> vectorQuest;
	std::vector<void*> vtNpcRelateState;
	// �õ���npc��֪��������
	const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoordInCurrTile(pNpc->GetNpcID());
	theHeroGame.GetPlayerMgr()->GetNpcQuests( pInfo, &vectorQuest, &vtNpcRelateState );

	// �鿴��npc���ϵ������Ƿ��пɶԻ���������Ի�������
	QuestTalks* pQuestTalks = NULL;
	for( int i = 0 ; i < vectorQuest.size() && i < vtNpcRelateState.size() ; ++ i )
	{
		SQuest* pQuest = vectorQuest[i];
		for( int eP = QuestManager::HSTT_ToGain; eP < QuestManager::HSTT_Count; ++ eP )
		{
			// �������Ƿ�������Ի�
			if( !pQuest->HaveQuestTalk( eP ) )
				continue;

			// �Ѿ��Թ�����
			if( thePlayerRole.GetTalkStates( pQuest->Id, eP ) )
				continue;

			CPlayerRole::QuestInfo *pNpcQuestInfo = (CPlayerRole::QuestInfo*)vtNpcRelateState[i];

			// �����������Ի��Ƿ��Ѿ�ʹ�ù�
			if( QuestManager::Instance().IsHaveSaw( eP, pNpcQuestInfo->chState ) )
				continue;

			if( QuestManager::Instance().IsQuestNotGain(pNpcQuestInfo->chState) && eP == QuestManager::HSTT_ToGain )//��δ�ӵ�����
			{
				pQuestTalks = &pQuest->vQuestTalks[eP];
				SendRefreshMsg( pQuest->Id, eP );
			}
			else if( QuestManager::Instance().IsQuestActive(pNpcQuestInfo->chState) && eP == QuestManager::HSTT_ToDone )//��û��������
			{
				//�ж��Ƿ�ɽ�
				if( thePlayerRole.IsQuestDone( pQuest ) )
				{
					pQuestTalks = &pQuest->vQuestTalks[eP];
					SendRefreshMsg( pQuest->Id, eP );
				}
			}
		}
	}
	if( !pQuestTalks )
		return false;

	// �жԻ����򿪶Ի��򣬽��жԻ�����
	m_vTalks = *pQuestTalks;
	m_nNpcId = nNpcId;
	m_bShow = bShow;
	
	SetVisable( true );
	
	return true;
}

const std::string& CUI_ID_FRAME_TaskDialog::GetBigHeadPicName( int nNpcId )
{
	static std::string s_final = "";
	s_final = "";
	CPlayer* pNpc = theHeroGame.GetPlayerMgr()->FindByID( nNpcId );
	if( !pNpc )
		return s_final;

	MexResMgr::Record* record = GetMexResMgr()->GetRecord(pNpc->GetModelId());
	if (!record || !pNpc->IsNpc())
		return s_final;
	
	std::string::size_type ddspos = record->headPicture.find( ".dds" );
	if( ddspos == std::string::npos )
		return s_final;
	s_final = record->headPicture.substr( 0, ddspos );
	s_final += "_talk.dds";	

	return s_final;
}

const std::string CUI_ID_FRAME_TaskDialog::GetPlayerHeadPicName()
{
	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->GetMe();
	if ( pPlayer )
	{
		char sex[2][32] = { "Male", "Female" };

		int hairId = pPlayer->GetEquip()[eKeyAll_Hair].iModelID;
		int faceId = pPlayer->GetEquip()[eKeyAll_Face].iModelID;

		char filename[256] = {0};
		MeSprintf_s(filename, sizeof(filename)/sizeof(char) - 1, "%s/Data/Ui/HeadPicture/HalfLength/Role_%s%d%d.dds",
			GetRootPath(), sex[pPlayer->GetSex()], hairId, faceId);

		if ( CFilePath::IsExist( filename ) )
		{
			MeSprintf_s(filename, sizeof(filename)/sizeof(char) - 1, "./Data/Ui/HeadPicture/HalfLength/Role_%s%d%d.dds",
				sex[pPlayer->GetSex()], hairId, faceId);
			return std::string(filename);
		}
	}

	return "";
}

bool CUI_ID_FRAME_TaskDialog::ContinueTalk()
{
	if( IsClickToContinue() )
	{
		if( !m_vTalks.empty() )
		{
			m_vTalks.erase( m_vTalks.begin() );
			SetDirty( true );			
		}		
		if( m_vTalks.empty() )
		{
			if(!s_CUI_NpcTaskDialogBox.LocalShowTask(m_nNpcId,m_bShow,true))   //�����򿪽���
			{
				s_CUI_NpcTaskDialogBox.BeginNpcScript(m_nNpcId);  //����ű�
				LOG_MESSAGE(MEMORY_LOG,LOG_PRIORITY_DEBUG,"SetNpc::BeginNpcScrip");
			}
		}
		// ����ͷ�񣬷�����һ֡����Ⱦ
		m_pID_PICTURE_NPC->SetVisable( false );
		m_pID_PICTURE_Player->SetVisable( false );

		return true;
	}
	return false;
}

bool CUI_ID_FRAME_TaskDialog::MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	if( !s_CUI_ID_FRAME_TaskDialog.IsVisable() )
		return false;

	switch( msg )
	{
	case WM_LBUTTONUP:
		{
			if( s_CUI_ID_FRAME_TaskDialog.ContinueTalk() )
			{
				return true;
			}
		}
		break;
	}

	return false;
}

void CUI_ID_FRAME_TaskDialog::SendRefreshMsg( uint16 questId, uint8 talkType )
{
	MsgSawTalkReq msg;
	msg.questId = questId;
	msg.talkType = talkType;
	GettheNetworkInput().SendMsg( &msg );	
}

void CUI_ID_FRAME_TaskDialog::InitializeAtEnterWorld()
{
	if( !m_pID_FRAME_TaskDialog )
		return;

	m_pID_FRAME_TaskDialog->SetVisable( false );
}