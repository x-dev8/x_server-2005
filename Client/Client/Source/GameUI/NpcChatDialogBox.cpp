/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Code\RunTime\CLIENT\Data\UI\NpcChatDialogBox.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "NpcChatDialogBox.h"
#include "../Player.h"
#include "PlayerMgr.h"
#include "Me3d/MoreAction.h"
#include "GameMain.h"
#include "target.h"
#include "MediaPathManager.h"
#include "Progress.h"
#include "SelectBox.h"
#include "Shop.h"
#include "ScreenInfoManager.h"
#include "MessageBox.h"
#include "..\MotionBillBoard.h"
#include "../color_config.h"
#include "XmlStringLanguage.h"
#include "NpcTaskDialogBox.h"
#include "ChatInfoBox.h"
#include "core/Name.h"
#include "ui/target.h"

extern CHeroGame* theApp;

#define QUEST_WAIT_TIME 5000

//hyber
void ID_TEXT_HyberClick(ControlObject* pSender, const char* szData)
{
    guardfunc;
    //目前超链接 只用于小地图有处理 别的还没有 以后增加功能再说 这里只是小地图npc指引的处理  。。。
    NpcCoord::getInstance()->clickHyberToMiniMap(szData);
    unguard;
}

bool UINpcChat_MsgProc(UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed)
{
    if (!s_CUI_ID_FRAME_NpcChatDialogBox.IsVisable())
        return false;

    switch (msg)
    {
    case WM_KEYUP:
        if (wParam == VK_RETURN)
        {
            if (s_CUI_ID_FRAME_NpcChatDialogBox.IsButCloseVisable()/*.m_pID_BUTTON_Close->IsVisable()*/)
                s_CUI_ID_FRAME_NpcChatDialogBox.ID_BUTTON_CloseOnButtonClick(0);
            else
                s_CUI_ID_FRAME_NpcChatDialogBox.ID_BUTTON_NextOnButtonClick(0);
            return true;
        }
        break;
    }
    return false;
}

CUI_ID_FRAME_NpcChatDialogBox s_CUI_ID_FRAME_NpcChatDialogBox;

MAP_FRAME_RUN( s_CUI_ID_FRAME_NpcChatDialogBox, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_NpcChatDialogBox, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_NpcChatDialogBox, ID_BUTTON_NextOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_NpcChatDialogBox, ID_BUTTON_CloseOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_NpcChatDialogBox, ID_BUTTON_EXITOnButtonClick )

CUI_ID_FRAME_NpcChatDialogBox::CUI_ID_FRAME_NpcChatDialogBox()
{
    // SGuildMember
    m_pID_FRAME_NpcChatDialogBox = NULL;
    m_pID_BUTTON_Next = NULL;
    m_pID_BUTTON_Close = NULL;
    m_pID_TEXT_Info = NULL;
    m_pID_TEXT_Name = NULL;
    m_pID_PICTURE_Head = NULL;
    m_pID_BUTTON_EXIT = NULL;
   m_pID_PICTURE_NpcHead = NULL;

    m_szText.clear();

    m_bWaitIntonate = false;
    m_dwLastIntonateTime = 0;
    m_dwIntonatePressTime = 0;
    m_bQuestNpc = false;
    m_dwLastTime = 0;
    m_nNpcId = -1;

    m_bScriptCanceled = true;
}


void CUI_ID_FRAME_NpcChatDialogBox::RetrieveNpcPic()
{
    if( !m_pID_FRAME_NpcChatDialogBox )
        return;

    CPlayer* pPlayer = NULL;
    if( m_nNpcId >= 0 )
        pPlayer = theHeroGame.GetPlayerMgr()->FindByID( m_nNpcId );
    if( !pPlayer )
    {
       m_pID_PICTURE_NpcHead->SetVisable(false);
        return;
    }

    MexResMgr::Record* record = GetMexResMgr()->GetRecord(pPlayer->GetModelId());
    if (record && m_pID_PICTURE_NpcHead && !pPlayer->IsPlayer())
    {
        m_pID_PICTURE_NpcHead->SetVisable(true);
        m_pID_PICTURE_NpcHead->SetPicName( record->headPicture.c_str() );
    }
    else
        m_pID_PICTURE_NpcHead->SetVisable(false);
}

void CUI_ID_FRAME_NpcChatDialogBox::SetScriptCanceled(bool bCanceld)
{
    m_bScriptCanceled = bCanceld;
}
bool CUI_ID_FRAME_NpcChatDialogBox::GetScriptCanceled()
{
    return m_bScriptCanceled;
}

void CUI_ID_FRAME_NpcChatDialogBox::CancelScript()
{
    m_bScriptCanceled = true;

    CloseDialog();
    s_CUI_NpcTaskDialogBox.SetVisable( false );
    //
    m_nNpcId = -1;
    MsgScriptCancel msg;
    GettheNetworkInput().SendMsg( &msg );
}
void CUI_ID_FRAME_NpcChatDialogBox::ReqScript()
{
    MsgReqScript msg;
    msg.stNpcId = m_nNpcId;
    GettheNetworkInput().SendMsg( &msg );
    m_bScriptCanceled = true;
}

void CUI_ID_FRAME_NpcChatDialogBox::ShowIntonateBar( DWORD dwTime, const char* pName )
{
    m_bWaitIntonate = true;
    m_dwLastIntonateTime = HQ_TimeGetTime();
    m_dwIntonatePressTime = dwTime;
    s_CUI_Progress.ShowByTime( m_dwLastIntonateTime,
        m_dwIntonatePressTime,
        true, 1, true, true, pName );
}

// Frame
bool CUI_ID_FRAME_NpcChatDialogBox::OnFrameRun()
{
    guardfunc;
    CPlayer* pMe = theApp->GetPlayerMgr()->GetMe();
    if ( !pMe )
    {
        return false;
    }
    bool bRunScript = true;
    // 客户端准备请求脚本
    if ( m_bQuestNpc && m_nNpcId >= 0 )
    {
        if ( pMe->IsMoving() )
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_NPC_Talk, theXmlString.GetString(eClient_AddInfo_2slk_11) );
            m_bQuestNpc = false;
            s_CUI_Progress.SetVisable( false );
        }
        else
        {
            if ( HQ_TimeGetTime() - m_dwLastTime >= QUEST_WAIT_TIME && theHeroGame.GetPlayerMgr() && theHeroGame.GetPlayerMgr()->CanReqScript() )
            {
                m_bQuestNpc = false;
                MsgReqScript msg;
                msg.stNpcId = m_nNpcId;
                GettheNetworkInput().SendMsg( &msg );
            }
        }
    }
    // 等待呤唱
    else if ( m_bWaitIntonate == true )
    {
        if ( pMe->IsMoving() )
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_NPC_Talk, theXmlString.GetString(eClient_AddInfo_2slk_11) );
            m_bWaitIntonate = false;
            s_CUI_Progress.SetVisable( false );
            CancelScript();
        }
        else
        {
            if ( HQ_TimeGetTime() - m_dwLastIntonateTime >= m_dwIntonatePressTime )
            {
                m_bWaitIntonate = false;
            }
        }
    }
    // 与ＮＰＣ过远
    else if ( m_nNpcId >= 0 )
    {
        CPlayer* pNpc = theHeroGame.GetPlayerMgr()->FindByID( m_nNpcId );
        if ( pNpc )
        {
            float fMeX,fMeY,fMeZ;
            float fNpcX, fNpcY, fNpcZ;
            pMe->GetPos( &fMeX, &fMeY, &fMeZ );
            pNpc->GetPos( &fNpcX, &fNpcY, &fNpcZ );
            float x = fNpcX - fMeX;
            float y = fNpcY - fMeY;
            float dist = sqrtf( x*x + y*y );
            if( dist > 12.0f )
            {
                CancelScript();
            }
        }
    }
    else
    {
        bRunScript = false;
    }
    if ( bRunScript == true )
    {
        // 如果死亡则中止脚本
        if ( pMe->IsDead() )
        {
            CancelScript();
            return true;
        }
    }
    return true;
    unguard;
}

bool CUI_ID_FRAME_NpcChatDialogBox::OnFrameRender()
{
    guardfunc;
    return true;
    unguard;
}
// Button
bool CUI_ID_FRAME_NpcChatDialogBox::ID_BUTTON_NextOnButtonClick( ControlObject* pSender )
{
    guardfunc;
	if(!m_pID_FRAME_NpcChatDialogBox)
		return false;
    ReqScript();
    SetVisable(false);
    return true;
    unguard;
}
// Button
bool CUI_ID_FRAME_NpcChatDialogBox::ID_BUTTON_CloseOnButtonClick( ControlObject* pSender )
{
    guardfunc;
	if(!m_pID_FRAME_NpcChatDialogBox)
		return false;
    CancelScript();
    return true;
    unguard;
}
// Button
bool CUI_ID_FRAME_NpcChatDialogBox::ID_BUTTON_EXITOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_NpcChatDialogBox)
		return false;
    CancelScript();
    return true;
}

// 装载UI
bool CUI_ID_FRAME_NpcChatDialogBox::_LoadUI()
{
    guardfunc;
    DWORD dwResult = theUiManager.AddFrame( "data\\ui\\NpcChatDialogBox.meui", false, UI_Render_LayerThree );
    if ( dwResult == 0 )
    {
        MESSAGE_BOX("读取文件[UI\\NpcChatDialogBox.UI]失败")
            return false;
    }
    return DoControlConnect();
    unguard;
}

void ID_FRAME_NpcChatDialogBox_onVisibleChanged( ControlObject* pObject )
{
    if ( !pObject->IsVisable() )
    {
        if ( !s_CUI_ID_FRAME_NpcChatDialogBox.IsScriptCancel() )
            s_CUI_ID_FRAME_NpcChatDialogBox.CancelScript();
    }
    else
    {
        s_CUI_ID_FRAME_NpcChatDialogBox.RetrieveNpcPic();
    }
}

// 关连控件
bool CUI_ID_FRAME_NpcChatDialogBox::DoControlConnect()
{
    guardfunc;
    theUiManager.OnFrameRun( ID_FRAME_NpcChatDialogBox, s_CUI_ID_FRAME_NpcChatDialogBoxOnFrameRun );
    theUiManager.OnFrameRender( ID_FRAME_NpcChatDialogBox, s_CUI_ID_FRAME_NpcChatDialogBoxOnFrameRender );
    theUiManager.OnButtonClick( ID_FRAME_NpcChatDialogBox, ID_BUTTON_Next, s_CUI_ID_FRAME_NpcChatDialogBoxID_BUTTON_NextOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_NpcChatDialogBox, ID_BUTTON_Close, s_CUI_ID_FRAME_NpcChatDialogBoxID_BUTTON_CloseOnButtonClick );
    theUiManager.OnTextHyberClick( ID_FRAME_NpcChatDialogBox, ID_TEXT_Info, ID_TEXT_HyberClick);
    theUiManager.OnButtonClick( ID_FRAME_NpcChatDialogBox, ID_BUTTON_EXIT, s_CUI_ID_FRAME_NpcChatDialogBoxID_BUTTON_EXITOnButtonClick );

    m_pID_FRAME_NpcChatDialogBox = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_NpcChatDialogBox );
    m_pID_BUTTON_Next = (ControlButton*)theUiManager.FindControl( ID_FRAME_NpcChatDialogBox, ID_BUTTON_Next );
    m_pID_BUTTON_Close = (ControlButton*)theUiManager.FindControl( ID_FRAME_NpcChatDialogBox, ID_BUTTON_Close );
    m_pID_TEXT_Info = (ControlText*)theUiManager.FindControl( ID_FRAME_NpcChatDialogBox, ID_TEXT_Info );
    m_pID_TEXT_Name = (ControlText*)theUiManager.FindControl( ID_FRAME_NpcChatDialogBox, ID_TEXT_Name );
    m_pID_PICTURE_Head = (ControlPicture*)theUiManager.FindControl( ID_FRAME_NpcChatDialogBox, ID_PICTURE_Head );
    m_pID_BUTTON_EXIT = (ControlButton*)theUiManager.FindControl( ID_FRAME_NpcChatDialogBox, ID_BUTTON_EXIT );
    m_pID_PICTURE_NpcHead = (ControlPicture*)theUiManager.FindControl( ID_FRAME_NpcChatDialogBox, ID_PICTURE_NpcHead );
    assert( m_pID_FRAME_NpcChatDialogBox );
    m_pID_FRAME_NpcChatDialogBox->SetVisable(false);
    m_pID_FRAME_NpcChatDialogBox->SetOnVisibleChangedFun( ID_FRAME_NpcChatDialogBox_onVisibleChanged );
    assert( m_pID_BUTTON_Next );
    assert( m_pID_BUTTON_Close );
    assert( m_pID_TEXT_Info );
    assert( m_pID_TEXT_Name );
    assert( m_pID_PICTURE_Head );
    assert( m_pID_BUTTON_EXIT );

    m_pID_FRAME_NpcChatDialogBox->SetMsgProcFun(UINpcChat_MsgProc);

	m_pID_TEXT_Info->SetColUrl(Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)));
// 	m_pID_TEXT_Info->SetHyberClickFun(TextInfo_HyberClick);

    USE_SCRIPT( eUI_OBJECT_NpcChatDlg, this );
    return true;
    unguard;
}

// 卸载UI
bool CUI_ID_FRAME_NpcChatDialogBox::_UnLoadUI()
{
    guardfunc;
    CLOSE_SCRIPT( eUI_OBJECT_NpcChatDlg );
    m_pID_FRAME_NpcChatDialogBox = NULL;
    m_pID_BUTTON_Next = NULL;
    m_pID_BUTTON_Close = NULL;
    m_pID_TEXT_Info = NULL;
    m_pID_TEXT_Name = NULL;
    m_pID_PICTURE_Head = NULL;
    m_pID_BUTTON_EXIT = NULL;
    m_pID_PICTURE_NpcHead = NULL;
    return theUiManager.RemoveFrame( "data\\ui\\NpcChatDialogBox.meui" );
    unguard;
}
// 是否可视
bool CUI_ID_FRAME_NpcChatDialogBox::_IsVisable()
{
    guardfunc;
    if( !m_pID_FRAME_NpcChatDialogBox )
        return false;
    return m_pID_FRAME_NpcChatDialogBox->IsVisable();
    unguard;
}
// 设置是否可视
void CUI_ID_FRAME_NpcChatDialogBox::_SetVisable( const bool bVisable )
{
    guardfunc;
    if( !m_pID_FRAME_NpcChatDialogBox )
        return;
    m_pID_FRAME_NpcChatDialogBox->SetVisable( bVisable );
    theUiManager.Compositor();

    m_bScriptCanceled = false;
    if (bVisable)
    {
        CPlayer* pNpc = theHeroGame.GetPlayerMgr()->FindByID( m_nNpcId );
        if (pNpc && pNpc->IsShowChatPaoPao())
        {
            pNpc->ClearChatPaoPao();
        }

    }
    unguard;
}

const char* CUI_ID_FRAME_NpcChatDialogBox::GetNpcName()
{
    guardfunc;
    if( !m_pID_FRAME_NpcChatDialogBox )
        return NULL;

    return m_pID_TEXT_Name->GetText();
    unguard;
}

void CUI_ID_FRAME_NpcChatDialogBox::SetDialogName( const char* szName )
{
    if( !m_pID_FRAME_NpcChatDialogBox || !szName )
        return;
    *m_pID_TEXT_Name = szName;
}

void CUI_ID_FRAME_NpcChatDialogBox::SetChatNpc( int nId )
{
    m_nNpcId = nId;
}

int CUI_ID_FRAME_NpcChatDialogBox::GetChatNpc()
{
    return m_nNpcId;
}

void CUI_ID_FRAME_NpcChatDialogBox::SetNpc( int nId, UINT nImgID )
{
    guardfunc;

    guard("Test0");

    guard("TestTest1");
    if ( HQ_TimeGetTime() - m_dwLastTime < 1000 ) 
    {
        return;
    }
    else
    {
        m_dwLastTime = HQ_TimeGetTime();
    }
    unguard;

    if (m_nNpcId != nId && !m_bScriptCanceled)
    {
        CancelScript();
    }
    else if (m_nNpcId == nId)
    {
        return;
    }

    // 判断能否请求脚本
    if( !theHeroGame.GetPlayerMgr() || !theHeroGame.GetPlayerMgr()->CanReqScript() )
        return;

    m_nNpcId = nId;
    if ( m_nNpcId >= 0 )
    {
        CPlayer* pPlayer = theApp->GetPlayerMgr()->FindByID(m_nNpcId);
        if (!pPlayer)
        {
            return;
        }
        {
            MsgReqScript msg;
            msg.stNpcId = m_nNpcId;
            GettheNetworkInput().SendMsg( &msg );
        }
    }
    else
    {
        guard("TestTest2");
        m_bQuestNpc = false;
        s_CUI_Progress.SetVisable( false );
        unguard;
    }
    unguard;
    guard( Test1 );
    //
    CPlayer* player = theHeroGame.GetPlayerMgr()->FindByID( m_nNpcId );
    if( player )
    {
        guard("Test1Test0");
        if( m_pID_TEXT_Name )
            *m_pID_TEXT_Name = player->GetName();
        unguard;
    }
    unguard;
    unguard;
}

void CUI_ID_FRAME_NpcChatDialogBox::SetButtonEnable( bool bEnabel )
{
    guardfunc;
    if( !m_pID_FRAME_NpcChatDialogBox )
        return;

    m_pID_BUTTON_Next->SetEnable( bEnabel );
    m_pID_BUTTON_Close->SetEnable( bEnabel );
    unguard;
}

void CUI_ID_FRAME_NpcChatDialogBox::ShowDialog( const std::string& strData , bool bShowNext )
{
    guardfunc;
	SetVisable( true );
    if( !m_pID_FRAME_NpcChatDialogBox )
        return;

    m_szText = strData;

	std::vector<UiCallbackDataBase*> CallBackDataArr;
	NpcCoord::getInstance()->addNpcHyberForText(m_szText,NpcCoord::eMapId,-1,m_nNpcId,&CallBackDataArr);	// 增加npc的超链接
    m_pID_TEXT_Info->SetText(m_szText, Color_Config.getColor(CC_NPCSELECKBOX_INFO),&CallBackDataArr );
    SetButtonEnable( true );
    //
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
    unguard;
}

void CUI_ID_FRAME_NpcChatDialogBox::CloseDialog()
{
    guardfunc;
    m_nNpcId = -1;
    SetVisable( false );
    unguard;
}

//触发ENTER的消息事件*******************************************
bool CUI_ID_FRAME_NpcChatDialogBox::frame_BackmsgClick( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
    guardfunc;
    if(!s_CUI_ID_FRAME_NpcChatDialogBox.IsVisable())
    {
        return false;
    }
    switch( msg ) 
    {
    case WM_KEYUP:
        {
            if( wParam == VK_RETURN )
            {
                s_CUI_ID_FRAME_NpcChatDialogBox.ID_BUTTON_NextOnButtonClick(NULL);
                return true;
            }
        }
        break;
    }
    return false;

    unguard;
}

bool CUI_ID_FRAME_NpcChatDialogBox::IsButCloseVisable()
{
    if(!m_pID_FRAME_NpcChatDialogBox)
        return false;

    return m_pID_BUTTON_Close->IsVisable();
}

void CUI_ID_FRAME_NpcChatDialogBox::TextInfo_HyberClick( ControlObject* pSender, const char* szData )
{
	if( szData )
		NpcCoord::getInstance()->clickHyberToMiniMap(szData);
}