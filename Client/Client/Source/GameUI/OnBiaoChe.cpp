/********************************************************************
Created by UIEditor.exe
FileName: E:\sanguo\Data\Ui\OnBiaoChe.cpp
*********************************************************************/
#include <assert.h>
#include <math.h>
#include "MeUi/UiManager.h"
#include "OnBiaoChe.h"
#include "../Player.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "ItemDetailConfig.h"
#include "PlayerInfoMgr.h"
#include "ScreenInfoManager.h"
#include "Target.h"

#define OP_OFFSETTIME 1000

CUI_ID_FRAME_OnBiaoChe s_CUI_ID_FRAME_OnBiaoChe;
MAP_FRAME_RUN( s_CUI_ID_FRAME_OnBiaoChe, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_OnBiaoChe, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_OnBiaoChe, ID_BUTTON_OnVehicleOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_OnBiaoChe, ID_BUTTON_LeaveVehicleOnButtonClick )
CUI_ID_FRAME_OnBiaoChe::CUI_ID_FRAME_OnBiaoChe()
{
	// Member
	m_pID_FRAME_OnBiaoChe = NULL;
	m_pID_BUTTON_OnVehicle = NULL;
	m_pID_BUTTON_LeaveVehicle = NULL;

	mBiaoche = NULL;
	m_OpLastTime = 0;
}

// Frame
bool CUI_ID_FRAME_OnBiaoChe::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_OnBiaoChe::OnFrameRender()
{
	return true;
}

void CUI_ID_FRAME_OnBiaoChe::SetBiaoche(CPlayer *player)
{
	mBiaoche = player;

	if (theHeroGame.GetPlayerMgr()->GetMe()->IsYabiaoState())
	{
		// ֻ��ʾ���ڳ���ť
		m_pID_BUTTON_OnVehicle->SetVisable(false);
		m_pID_BUTTON_LeaveVehicle->SetVisable(true);
	}
	else
	{
		// ֻ��ʾ���ڳ���ť
		m_pID_BUTTON_OnVehicle->SetVisable(true);
		m_pID_BUTTON_LeaveVehicle->SetVisable(false);
	}
}

void CUI_ID_FRAME_OnBiaoChe::ShowBiaocheGetOnButton()
{
	// ֻ��ʾ���ڳ���ť
	m_pID_BUTTON_OnVehicle->SetVisable(true);
	m_pID_BUTTON_LeaveVehicle->SetVisable(false);
}

bool CUI_ID_FRAME_OnBiaoChe::GetCanOp()
{
	if( m_OpLastTime == 0) 
		return true;

	if(timeGetTime() - m_OpLastTime >= OP_OFFSETTIME)
	{
		return true;
	}

	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, theXmlString.GetString( eText_OperateFailedInCD ) );
	return false;
}
// Button
bool CUI_ID_FRAME_OnBiaoChe::ID_BUTTON_OnVehicleOnButtonClick( ControlObject* pSender )
{

	if(!GetCanOp())
	{
      return false;
	}

	CPlayer *playerMe = theHeroGame.GetPlayerMgr()->GetMe();
	if (playerMe == NULL || mBiaoche == NULL)
		return false;

	// �������������ϣ�Ҫ��ʾ��������
	if (playerMe->IsMounting())
	{
		CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Info_ChatSys, theXmlString.GetString(eText_Biaoche_NeedMountOff));
		return false;
	}

	// �������Ծ״̬��������
	if (playerMe->IsJumping())
	{
		CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Info_ChatSys, theXmlString.GetString(eText_Biaoche_NoJump));
		return false;
	}

	// ������ƶ��в�������
	if (playerMe->IsMoving())
	{
		CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Info_ChatSys, theXmlString.GetString(eText_Biaoche_NoMove));
		return false;
	}

	float x_offset = playerMe->GetPos().x - mBiaoche->GetPos().x;
	float y_offset = playerMe->GetPos().y - mBiaoche->GetPos().y;
	float dist = sqrtf(x_offset * x_offset + y_offset * y_offset);
	// �ڳ�����ҵľ���̫Զ���������ڳ�
	if (dist > 6.0)
	{
		CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Info_ChatSys, theXmlString.GetString(eText_Biaoche_OutOfRange));
		return false;
	}

	if (mBiaoche->IsCanRide())
	{
		CPlayer *master = theHeroGame.GetPlayerMgr()->FindByID(mBiaoche->GetMasterID());
		if (master != NULL && master == playerMe)
		{
			ItemDefine::SMonster *biaocheMonster = theItemDetailConfig.GetMonsterById(mBiaoche->GetMonsterID());
			if (biaocheMonster != NULL)
			{
				MsgChangeToBiaocheReq msg;
				msg.monsterID = mBiaoche->GetMonsterID();
				GettheNetworkInput().SendMsg(&msg);
				m_OpLastTime = timeGetTime();

				// �������ڳ���ť
				m_pID_BUTTON_OnVehicle->SetVisable(false);
				m_pID_BUTTON_LeaveVehicle->SetVisable(true);

				// �����ҵ�ǰѡ���Ŀ�����ڳ�����ȡ��ѡ��
				if (theHeroGame.GetPlayerMgr()->GetLockPlayerID() == mBiaoche->GetID())
				{
					theHeroGame.GetPlayerMgr()->SetLockPlayerID(-1);
					s_CUI_ID_FRAME_Target.SetPlayer(-1);
				}
			}
		}
	}
	return true;
}

// Button
bool CUI_ID_FRAME_OnBiaoChe::ID_BUTTON_LeaveVehicleOnButtonClick( ControlObject* pSender )
{
	if(!GetCanOp())
	{
		return false;
	}
	MsgRestoreFromBiaocheReq msg;
	GettheNetworkInput().SendMsg(&msg);
	m_OpLastTime = timeGetTime();

	// �������ڳ���ť
	m_pID_BUTTON_OnVehicle->SetVisable(true);
	m_pID_BUTTON_LeaveVehicle->SetVisable(false);
	return true;
}

// װ��UI
bool CUI_ID_FRAME_OnBiaoChe::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\OnBiaoChe.MEUI", true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("��ȡ�ļ�[Data\\UI\\OnBiaoChe.MEUI]ʧ��")
			return false;
	}
	return DoControlConnect();
}

// �����ؼ�
bool CUI_ID_FRAME_OnBiaoChe::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_OnBiaoChe, s_CUI_ID_FRAME_OnBiaoCheOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_OnBiaoChe, s_CUI_ID_FRAME_OnBiaoCheOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_OnBiaoChe, ID_BUTTON_OnVehicle, s_CUI_ID_FRAME_OnBiaoCheID_BUTTON_OnVehicleOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_OnBiaoChe, ID_BUTTON_LeaveVehicle, s_CUI_ID_FRAME_OnBiaoCheID_BUTTON_LeaveVehicleOnButtonClick );

	m_pID_FRAME_OnBiaoChe = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_OnBiaoChe );
	m_pID_BUTTON_OnVehicle = (ControlButton*)theUiManager.FindControl( ID_FRAME_OnBiaoChe, ID_BUTTON_OnVehicle );
	m_pID_BUTTON_LeaveVehicle = (ControlButton*)theUiManager.FindControl( ID_FRAME_OnBiaoChe, ID_BUTTON_LeaveVehicle );
	assert( m_pID_FRAME_OnBiaoChe );
	assert( m_pID_BUTTON_OnVehicle );
	assert( m_pID_BUTTON_LeaveVehicle );

	SetVisable(false);

	m_pID_FRAME_OnBiaoChe->enableEscKey( false );
	m_pID_FRAME_OnBiaoChe->SetOnEscResponseType( ControlFrame::EscResponse_SkipMe );

	return true;
}

// ж��UI
bool CUI_ID_FRAME_OnBiaoChe::_UnLoadUI()
{
	m_pID_FRAME_OnBiaoChe = NULL;
	m_OpLastTime = 0;
	return theUiManager.RemoveFrame( "Data\\UI\\OnBiaoChe.MEUI" );
}

// �Ƿ����
bool CUI_ID_FRAME_OnBiaoChe::_IsVisable()
{
	if ( !m_pID_FRAME_OnBiaoChe )
		return false;
	return m_pID_FRAME_OnBiaoChe->IsVisable();
}

// �����Ƿ����
void CUI_ID_FRAME_OnBiaoChe::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_OnBiaoChe )
		return ;
	m_pID_FRAME_OnBiaoChe->SetVisable( bVisable );

	if (!bVisable)
		mBiaoche = NULL;
}
