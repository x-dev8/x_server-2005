/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Code\RunTime\CLIENT\Data\UI\Message.cpp
*********************************************************************/
#include <assert.h>
#include "LoadMap.h"
#include "ui/MessageBox.h"
#include "MeUi/UiManager.h"

#include "FuncPerformanceLog.h"

#include "shortcutkey_configure.h"
#include "color_config.h"
#include "XmlStringLanguage.h"
#include "core/Name.h"
#include "ui/ExitGame.h"
#include "NpcCoord.h"
#include "GameMain.h"
#include "ui/Gut.h"
extern GAME_STATE	g_GameState;


CUI_ID_FRAME_MessageBox s_CUI_ID_FRAME_MessageBox;
MAP_FRAME_RUN( s_CUI_ID_FRAME_MessageBox, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_MessageBox, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MessageBox, ID_BUTTON_YESOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MessageBox, ID_BUTTON_NOOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MessageBox, ID_BUTTON_COMFIRMOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MessageBox, ID_BUTTON_JieShouOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MessageBox, ID_BUTTON_JvJueOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MessageBox, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MessageBox, ID_BUTTON_YES2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MessageBox, ID_BUTTON_NO2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MessageBox, ID_BUTTON_MoveHei2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MessageBox, ID_BUTTON_SeekEquipOnButtonClick )

CUI_ID_FRAME_MessageBox::CUI_ID_FRAME_MessageBox()
{
    m_bUnLoaded = FALSE;

	ResetMembers();

	ClearMessageCache();

    m_bTimeOut = false;
}

void CUI_ID_FRAME_MessageBox::ResetMembers()
{
	// SGuildMember
	m_pID_FRAME_MESSAGE = NULL;
	m_pID_EDIT_INFO = NULL;
	m_pID_BUTTON_YES = NULL;
	m_pID_BUTTON_NO = NULL;
	m_pID_BUTTON_COMFIRM = NULL;
	m_pID_TEXT_CAPTION = NULL;
	m_pID_BUTTON_JieShou = NULL;
	m_pID_BUTTON_JvJue = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pCheckLeft = NULL;
	m_pCheckRight = NULL;
	m_pCheckMiddle = NULL;
	m_pID_TEXT_CHECKRIGHT = NULL;
	m_pID_TEXT_CHECKLeft = NULL;
	m_pID_TEXT_CHECKMiddle = NULL;
	m_pID_EDIT_INFO2 = NULL;
	m_pID_PICTURE_Wall2 = NULL;
	m_pID_PICTURE_Wall = NULL;
	m_pID_BUTTON_YES2 = NULL;
	m_pID_BUTTON_NO2 = NULL;
	m_pID_BUTTON_MoveHei2 = NULL;
	m_pID_BUTTON_SeekEquip = NULL;
}

bool CUI_ID_FRAME_MessageBox::OnButtonClick( char bResult )
{
    guardfunc;
	if(!m_pID_FRAME_MESSAGE)
		return false;

    if ( m_ltMessagBox.size() > 0 )
    {
        S_MessageBox msg = m_ltMessagBox.front();

        if ( msg.m_pCallbackFun )
        {
			if (s_CUI_ID_FRAME_Gut.GetFrame() && s_CUI_ID_FRAME_Gut.IsVisable())
			{
				//在全屏交付任务的时候 ，这时候不管 玩家对 主角进行任何操作 ，比如交易 比武 组队之类的 ，全部以拒绝执行。
				msg.m_pCallbackFun( 0 , msg.m_pData );
			}else
			{
                msg.m_pCallbackFun( bResult , msg.m_pData );
			}
            
        }
        if ( msg.m_pData )
        {
            delete[] msg.m_pData;
            msg.m_pData = NULL;
        }
        m_ltMessagBox.pop_front();
    }
    Refeash();
    return true;
    unguard;
}
// Frame
bool CUI_ID_FRAME_MessageBox::OnFrameRun()
{
    if ( m_ltMessagBox.size() > 0 )
    {
        S_MessageBox* pMsg;
        pMsg = &m_ltMessagBox.front();
        if ( pMsg->dwAutoCloseTime != 0 )
        {
            int n = timeGetTime() - pMsg->dwStartTime;
            int nTime = pMsg->dwAutoCloseTime - n/1000;
            if ( nTime >= 0 )
            {
                //去掉倒计时的提示
//#ifdef _DEBUG
//				char szInfo[512];
//				sprintf( szInfo, theXmlString.GetString(eClient_AddInfo_2slk_122),
//					pMsg->m_strInfo.c_str(),
//					nTime );
//				m_pID_EDIT_INFO->SetText(szInfo, Color_Config.getColor(CC_MESSGEBOX_TEXT) );
//#else
//				m_pID_EDIT_INFO->SetText(pMsg->m_strInfo.c_str(), Color_Config.getColor(CC_MESSGEBOX_TEXT) );
//#endif
				//带倒计时
				char szInfo[512];
				sprintf( szInfo, theXmlString.GetString(eClient_AddInfo_2slk_122),
					pMsg->m_strInfo.c_str(),
					nTime );
				m_pID_EDIT_INFO->SetText(szInfo, Color_Config.getColor(CC_MESSGEBOX_TEXT) );
				//

                m_pID_PICTURE_Wall->SetVisable(true);
                m_pID_EDIT_INFO->SetVisable(true);
                m_pID_EDIT_INFO2->SetVisable(false);
                m_pID_PICTURE_Wall2->SetVisable(false);
				
            }
            if ( timeGetTime() - pMsg->dwStartTime >=
                pMsg->dwAutoCloseTime*1000 )
            {
                m_bTimeOut = true;
                OnButtonClick( pMsg->bDefaultYES );
                m_bTimeOut = false;
            }
        }
    }
    return true;
}
bool CUI_ID_FRAME_MessageBox::OnFrameRender()
{
    return true;
}
// Button
bool CUI_ID_FRAME_MessageBox::ID_BUTTON_YESOnButtonClick( ControlObject* pMe )
{
    guardfunc;
	if( !m_pID_FRAME_MESSAGE )
		return false;
    OnButtonClick( 1 );
    unguard;
    return true;
}
// Button
bool CUI_ID_FRAME_MessageBox::ID_BUTTON_NOOnButtonClick( ControlObject* pMe )
{
    guardfunc;
	if( !m_pID_FRAME_MESSAGE )
		return false;
    OnButtonClick( 0 );
    unguard;
    return true;
}
//buttton
bool CUI_ID_FRAME_MessageBox::ID_BUTTON_COMFIRMOnButtonClick(ControlObject* pMe )
{
    guardfunc;
	if( !m_pID_FRAME_MESSAGE )
		return false;
    OnButtonClick( 1 );
    unguard;
    return true;
}
// Button
bool CUI_ID_FRAME_MessageBox::ID_BUTTON_JieShouOnButtonClick( ControlObject* pSender )
{
    guardfunc;
	if( !m_pID_FRAME_MESSAGE )
		return false;
	OnButtonClick( 1 );
    unguard;
    return true;
}
// Button
bool CUI_ID_FRAME_MessageBox::ID_BUTTON_JvJueOnButtonClick( ControlObject* pSender )
{
    guardfunc;
	if( !m_pID_FRAME_MESSAGE )
		return false;
    OnButtonClick( 0 );
    unguard;
    return true;
}
// Button
bool CUI_ID_FRAME_MessageBox::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
    guardfunc;
	if( !m_pID_FRAME_MESSAGE )
		return false;
    OnButtonClick( 0 );
    unguard;
    return true;
}
// Button
bool CUI_ID_FRAME_MessageBox::ID_BUTTON_YES2OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_MESSAGE )
		return false;
    OnButtonClick( 1 );
    return true;
}
// Button
bool CUI_ID_FRAME_MessageBox::ID_BUTTON_NO2OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_MESSAGE )
		return false;
    OnButtonClick( 0 );
    return true;
}
// Button
bool CUI_ID_FRAME_MessageBox::ID_BUTTON_MoveHei2OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_MESSAGE )
		return false;
    OnButtonClick( 2 );
    return true;
}

//SeekEquip
bool CUI_ID_FRAME_MessageBox::ID_BUTTON_SeekEquipOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_MESSAGE )
		return false;
	OnButtonClick( 2 );
	return true;
}

// 装载UI   
bool CUI_ID_FRAME_MessageBox::_LoadUI()
{
    guardfunc;		
    DWORD dwResult = 0;
    dwResult = theUiManager.AddFrame( "data\\ui\\MessageBox.meui", false, UI_Render_LayerFour );

    if ( dwResult == 0 )
    {
        MESSAGE_BOX("读取文件[UI\\MessageBox.UI]失败")
            return false;
    }
    m_bUnLoaded = FALSE;
    return DoControlConnect();
    unguard;
}
// 关连控件
bool CUI_ID_FRAME_MessageBox::DoControlConnect()
{
    guardfunc;
    theUiManager.OnFrameRun( ID_FRAME_MESSAGE, s_CUI_ID_FRAME_MessageBoxOnFrameRun );
    theUiManager.OnFrameRender( ID_FRAME_MESSAGE, s_CUI_ID_FRAME_MessageBoxOnFrameRender );
    theUiManager.OnButtonClick( ID_FRAME_MESSAGE, ID_BUTTON_YES, s_CUI_ID_FRAME_MessageBoxID_BUTTON_YESOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_MESSAGE, ID_BUTTON_NO, s_CUI_ID_FRAME_MessageBoxID_BUTTON_NOOnButtonClick );
    theUiManager.OnButtonClick(ID_FRAME_MESSAGE,ID_BUTTON_COMFIRM,s_CUI_ID_FRAME_MessageBoxID_BUTTON_COMFIRMOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_MESSAGE, ID_BUTTON_JieShou, s_CUI_ID_FRAME_MessageBoxID_BUTTON_JieShouOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_MESSAGE, ID_BUTTON_JvJue, s_CUI_ID_FRAME_MessageBoxID_BUTTON_JvJueOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_MESSAGE, ID_BUTTON_Cancel, s_CUI_ID_FRAME_MessageBoxID_BUTTON_CancelOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_MESSAGE, ID_BUTTON_YES2, s_CUI_ID_FRAME_MessageBoxID_BUTTON_YES2OnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_MESSAGE, ID_BUTTON_NO2, s_CUI_ID_FRAME_MessageBoxID_BUTTON_NO2OnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_MESSAGE, ID_BUTTON_MoveHei2, s_CUI_ID_FRAME_MessageBoxID_BUTTON_MoveHei2OnButtonClick );

    m_pID_FRAME_MESSAGE = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_MESSAGE );
    m_pID_EDIT_INFO = (ControlText*)theUiManager.FindControl( ID_FRAME_MESSAGE, ID_EDIT_INFO );
    m_pID_BUTTON_YES = (ControlButton*)theUiManager.FindControl( ID_FRAME_MESSAGE, ID_BUTTON_YES );
    m_pID_BUTTON_NO = (ControlButton*)theUiManager.FindControl( ID_FRAME_MESSAGE, ID_BUTTON_NO );
    m_pID_BUTTON_COMFIRM = (ControlButton*)theUiManager.FindControl(ID_FRAME_MESSAGE,ID_BUTTON_COMFIRM);
    m_pID_TEXT_CAPTION = (ControlText*)theUiManager.FindControl( ID_FRAME_MESSAGE, ID_TEXT_CAPTION );
    m_pID_BUTTON_JieShou = (ControlButton*)theUiManager.FindControl( ID_FRAME_MESSAGE, ID_BUTTON_JieShou );
    m_pID_BUTTON_JvJue = (ControlButton*)theUiManager.FindControl( ID_FRAME_MESSAGE, ID_BUTTON_JvJue );
    m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_MESSAGE, ID_BUTTON_Cancel );
    m_pCheckRight = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_MESSAGE, ID_CHECKBOX_CheckRight );   
    m_pCheckLeft = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_MESSAGE, ID_CHECKBOX_CheckLeft );   
    m_pCheckMiddle = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_MESSAGE, ID_CHECKBOX_CheckMiddle );   
    m_pID_TEXT_CHECKRIGHT = (ControlText*)theUiManager.FindControl( ID_FRAME_MESSAGE, ID_TEXT_CHECKRIGHT );
    m_pID_TEXT_CHECKMiddle = (ControlText*)theUiManager.FindControl( ID_FRAME_MESSAGE, ID_TEXT_CHECKMiddle );
    m_pID_TEXT_CHECKLeft = (ControlText*)theUiManager.FindControl( ID_FRAME_MESSAGE, ID_TEXT_CHECKLeft );
    m_pID_EDIT_INFO2 = (ControlText*)theUiManager.FindControl( ID_FRAME_MESSAGE, ID_EDIT_INFO2 );
    m_pID_PICTURE_Wall2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MESSAGE, ID_PICTURE_Wall2 );
    m_pID_PICTURE_Wall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MESSAGE, ID_PICTURE_Wall );
    m_pID_BUTTON_YES2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_MESSAGE, ID_BUTTON_YES2 );
    m_pID_BUTTON_NO2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_MESSAGE, ID_BUTTON_NO2 );
    m_pID_BUTTON_MoveHei2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_MESSAGE, ID_BUTTON_MoveHei2 );
	m_pID_BUTTON_SeekEquip = (ControlButton*)theUiManager.FindControl( ID_FRAME_MESSAGE, ID_BUTTON_SeekEquip);
    assert( m_pID_FRAME_MESSAGE );
    assert( m_pID_EDIT_INFO );
    assert( m_pID_BUTTON_YES );
    assert( m_pID_BUTTON_NO );
    assert(m_pID_BUTTON_COMFIRM);
    assert( m_pID_TEXT_CAPTION );
    assert( m_pID_BUTTON_JieShou );
    assert( m_pID_BUTTON_JvJue );
    assert( m_pID_BUTTON_Cancel );
    assert( m_pCheckRight );
    assert( m_pID_BUTTON_YES2 );
    assert( m_pID_BUTTON_NO2 );
    assert( m_pID_BUTTON_MoveHei2 );
	assert(m_pID_BUTTON_SeekEquip);

    m_pCheckRight->SetCheck(false);
    m_pCheckRight->SetShowTip(true);
    m_pCheckLeft->SetCheck(false);
    m_pCheckLeft->SetShowTip(true);
    m_pCheckMiddle->SetCheck(false);
    m_pCheckMiddle->SetShowTip(true);

    m_pID_TEXT_CHECKRIGHT->SetVisable(false);
    m_pID_TEXT_CHECKLeft->SetVisable(false);
    m_pID_TEXT_CHECKMiddle->SetVisable(false);

    m_pID_BUTTON_YES2->SetVisable(false);
    m_pID_BUTTON_NO2->SetVisable(false);
    m_pID_BUTTON_MoveHei2->SetVisable(false);
	m_pID_BUTTON_SeekEquip->SetVisable(false);

    m_pID_FRAME_MESSAGE->SetMsgProcFun( MessageBox_MsgProc );
    m_pID_FRAME_MESSAGE->enableEscKey( false );
    m_pID_FRAME_MESSAGE->SetOnVisibleChangedFun( OnVisibleChanged );

    _SetVisable( false );
    return true;
    unguard;
}
// 卸载UI
bool CUI_ID_FRAME_MessageBox::_UnLoadUI()
{
    guardfunc;
    m_bUnLoaded = TRUE;

    m_pID_FRAME_MESSAGE = NULL;
	ResetMembers();
    return theUiManager.RemoveFrame( "data\\ui\\MessageBox.meui" );    	
    unguard;
}
// 是否可视
bool CUI_ID_FRAME_MessageBox::_IsVisable()
{
    guardfunc;
    if( !m_pID_FRAME_MESSAGE )
        return false;
    return m_pID_FRAME_MESSAGE->IsVisable();
    unguard;
}
// 设置是否可视
void CUI_ID_FRAME_MessageBox::_SetVisable( const bool bVisable )
{
    guardfunc;
    if( m_pID_FRAME_MESSAGE )
    {
        m_pID_FRAME_MESSAGE->SetVisable( bVisable );
    }
    unguard;
}

void CUI_ID_FRAME_MessageBox::OnVisibleChanged( ControlObject* pSender )
{
    if(!s_CUI_ID_FRAME_MessageBox.IsTimeOut())
    {
        UiDrawer::StartFillFullScreen( 500, false );
    }		
}

void CUI_ID_FRAME_MessageBox::VisableButtons( EType type, S_MessageBox* msgBoxData )
{
	if(!m_pID_FRAME_MESSAGE)
		return;

    m_pID_BUTTON_YES->SetVisable( false );
    m_pID_BUTTON_NO->SetVisable( false );
    m_pID_BUTTON_COMFIRM->SetVisable( false );
    m_pID_BUTTON_JieShou->SetVisable( false );
    m_pID_BUTTON_JvJue->SetVisable( false );
    m_pID_BUTTON_Cancel->SetVisable( false );
    m_pID_BUTTON_Cancel->SetEnable( true );
    m_pID_BUTTON_YES2->SetVisable(false);
    m_pID_BUTTON_NO2->SetVisable(false);
    m_pID_BUTTON_MoveHei2->SetVisable(false);
	m_pID_BUTTON_SeekEquip->SetVisable(false);
    switch( type ) 
    {
    case eTypeYesNo:
        m_pID_BUTTON_YES->SetVisable( true );
        m_pID_BUTTON_NO->SetVisable( true );
        break;
    case eTypeYesNoExternal:
        m_pID_BUTTON_YES2->SetVisable( true );
        m_pID_BUTTON_NO2->SetVisable( true );
        m_pID_BUTTON_MoveHei2->SetVisable(true);
        break;
    case eTypeAcceptReject:
        m_pID_BUTTON_JieShou->SetVisable( true );
        m_pID_BUTTON_JvJue->SetVisable( true );
        break;
    case eTypeConfirm:
        m_pID_BUTTON_COMFIRM->SetVisable( true );
        break;
    case eTypeCancel:
        m_pID_BUTTON_Cancel->SetVisable( true );
        break;
    case eTypeNothing:
        m_pID_BUTTON_Cancel->SetVisable( false );
        m_pID_BUTTON_Cancel->SetEnable( false );
        break;
	case eTypeYesNoSeek:
		m_pID_BUTTON_YES2->SetVisable( true );
		m_pID_BUTTON_NO2->SetVisable( true );
		m_pID_BUTTON_SeekEquip->SetVisable(true);
		break;
    default:
        break;
    }

    if (m_pCheckLeft && m_pID_TEXT_CHECKLeft)
    {
        {
            m_pCheckLeft->SetVisable(false);
            m_pID_TEXT_CHECKLeft->SetVisable(false);
        }
    }

    if (m_pCheckRight && m_pID_TEXT_CHECKRIGHT)
    {
        {
            m_pCheckRight->SetVisable(false);
            m_pID_TEXT_CHECKRIGHT->SetVisable(false);
        }
    }

    if (m_pCheckMiddle && m_pID_TEXT_CHECKMiddle)
    {
        {
            m_pCheckMiddle->SetVisable(false);
            m_pID_TEXT_CHECKMiddle->SetVisable(false);
        }
    }
}


void CUI_ID_FRAME_MessageBox::UpdateMsgInfo(const char* msgInfo)
{
	//m_pID_EDIT_INFO->SetText(msgInfo);
	if ( m_ltMessagBox.size() > 0 )
	{
		S_MessageBox* pMsg = &m_ltMessagBox.front();
		if (pMsg==NULL)
		{
			return;
		}
		//pMsg->dwAutoCloseTime = dwAutoCloseTime;
		pMsg->m_strInfo = msgInfo;
		Refeash();
	}
	
	//pMsg->dwStartTime = timeGetTime();
}

void CUI_ID_FRAME_MessageBox::Refeash()
{
    guardfunc;
	if( !m_pID_FRAME_MESSAGE )
		return;
    if ( m_ltMessagBox.size() > 0 )
    {
		SetVisable( true );
        S_MessageBox *pMessageBox;
        pMessageBox = &m_ltMessagBox.front();
        {
            m_pID_PICTURE_Wall->SetVisable(true);
            m_pID_EDIT_INFO->SetVisable(true);
            m_pID_EDIT_INFO2->SetVisable(false);
            m_pID_PICTURE_Wall2->SetVisable(false);

			std::string msgStr = pMessageBox->m_strInfo;
			std::vector<UiCallbackDataBase*> CallBackDataArr;
			NpcCoord::getInstance()->addNpcHyberForText( msgStr, NpcCoord::eMapId, -1,-1, &CallBackDataArr );

            m_pID_EDIT_INFO->SetText( msgStr, Color_Config.getColor(CC_MESSGEBOX_TEXT) );
        }
        *m_pID_TEXT_CAPTION = pMessageBox->m_strCaption;
        VisableButtons( pMessageBox->m_eType, pMessageBox );
        if ( pMessageBox->m_bModal == true )
        {
            m_pID_FRAME_MESSAGE->SetArrayMode( ArrayMode_Top );
        }
        else
        {
            m_pID_FRAME_MESSAGE->SetArrayMode( ArrayMode_Normal );
        }
        if( !s_CUI_ID_FRAME_LoadMap.IsVisable() || pMessageBox->m_pCallbackFun == &CUI_ID_FRAME_ExitGame::TellExitGameForce )
            theUiManager.ToTop( m_pID_FRAME_MESSAGE );
        else // 使读取地图的UI界面在最顶端
            theUiManager.ToTop( s_CUI_ID_FRAME_LoadMap.GetFrame() );
    }
    else
    {
        SetVisable( false );
    }
    unguard;
}

void CUI_ID_FRAME_MessageBox::Show( const char* szText, const char* szCaption, EType type,
          const bool bModal, const funCallbackFun pFun,
          void *pData, const int nDataLength
          )
{
    guardfunc;
	if(!m_pID_FRAME_MESSAGE)
		return;

    // 判断是否有内容重复的MessageBox
    if( m_ltMessagBox.size() )
    {
        std::list<S_MessageBox>::iterator iter;
        for( iter = m_ltMessagBox.begin(); iter != m_ltMessagBox.end(); )
        {
            S_MessageBox& pMsg = *iter;
            if( pMsg.m_strInfo.compare( szText ) == 0 ) // 有重复则把原先的删除，创建新的，这样MessageBox不会被其他UI挡住
            {
                if ( pMsg.m_pData )
                {
                    delete[] pMsg.m_pData;
                    pMsg.m_pData = NULL;
                }
                iter = m_ltMessagBox.erase(iter);
            }
            else
                ++iter;
        }
    }
    S_MessageBox stMessagBox;
    stMessagBox.dwStartTime = timeGetTime();
    stMessagBox.m_strInfo = szText;
    stMessagBox.m_strCaption = szCaption;
    stMessagBox.m_eType = type;
    stMessagBox.m_pCallbackFun = pFun;
    stMessagBox.m_bModal = bModal;
    if ( pData && nDataLength > 0 )
    {
        stMessagBox.m_pData = MeDefaultNew BYTE[nDataLength];
        memcpy( stMessagBox.m_pData, pData, nDataLength );
    }

    m_ltMessagBox.push_back( stMessagBox );
    Refeash();
    unguard;
}

bool CUI_ID_FRAME_MessageBox::SetAutoClose( DWORD dwSecond, bool bDefaultYES )
{
	if(!m_pID_FRAME_MESSAGE)
		return false;

    if ( m_ltMessagBox.size() > 0 )
    {
        S_MessageBox* pMsg = &m_ltMessagBox.back();
        pMsg->dwAutoCloseTime = dwSecond;
        pMsg->bDefaultYES = bDefaultYES;
        pMsg->dwStartTime = timeGetTime();
    }
    return true;
}

bool CUI_ID_FRAME_MessageBox::IsTimeOut()
{
    return m_bTimeOut;
}

bool CUI_ID_FRAME_MessageBox::MessageBox_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
    guardfunc;
    if( !s_CUI_ID_FRAME_MessageBox.IsVisable() )
        return false;

    switch( msg ) 
    {
    case WM_KEYUP:
        {
            if( wParam == VK_ESCAPE && s_CUI_ID_FRAME_MessageBox.IsEnableOnButCancel() )	//cancle
            {
                s_CUI_ID_FRAME_MessageBox.OnButtonClick(false);
                return true;
            }
            else if( wParam == VK_ESCAPE && !s_CUI_ID_FRAME_MessageBox.IsEnableOnButCancel() )
            {
                return true;
            }
            else if( wParam == VK_RETURN && s_CUI_ID_FRAME_MessageBox.IsEnableOnButCancel() &&
                (!theUiManager.GetFocus() || theUiManager.GetFocus()->GetControlType() != Type_Edit || g_GameState == G_LOGIN) )
            {
                // 当机保护     added by ZhuoMeng.Hu		[1/9/2011]
                if( s_CUI_ID_FRAME_MessageBox.m_ltMessagBox.empty() )
                {
                    return true;
                }

                S_MessageBox* pMsg = &s_CUI_ID_FRAME_MessageBox.m_ltMessagBox.front();
                if (pMsg->useHotKeyCount-- > 0)
                    return true;
                if( pMsg->m_eType == eTypeCancel )
                    s_CUI_ID_FRAME_MessageBox.OnButtonClick(false);
                else
                    s_CUI_ID_FRAME_MessageBox.OnButtonClick(true);
                return true;
            }
        }
        break;
    }
    return false;
    unguard;
}

void CUI_ID_FRAME_MessageBox::closeAll( bool ok )
{
	if(!m_pID_FRAME_MESSAGE)
		return;

    m_pID_BUTTON_Cancel->SetEnable(true);

    while ( !m_ltMessagBox.empty() )
        OnButtonClick( ok );
}

bool CUI_ID_FRAME_MessageBox::HasModaleMessageBox()
{
	if(!m_pID_FRAME_MESSAGE)
		return false;

    if ( m_ltMessagBox.size() > 0 )
    {
        std::list<S_MessageBox>::iterator iter;
        for( iter = m_ltMessagBox.begin(); iter != m_ltMessagBox.end(); ++iter )
        {
            S_MessageBox& pMsg = *iter;
            if( pMsg.m_bModal )
                return true;
        }
    }
    return false;
}

void CUI_ID_FRAME_MessageBox::closeAllMatchString( int nOffset, const char* szText )
{
	if(!m_pID_FRAME_MESSAGE)
		return;

    if( nOffset < 0 )
        return;

    m_pID_BUTTON_Cancel->SetEnable(true);

    if( m_ltMessagBox.size() > nOffset )
    {
        std::list<S_MessageBox>::iterator iter = m_ltMessagBox.begin();
        for(int i=0; i<nOffset; ++i)
            ++iter;
        for( ; iter != m_ltMessagBox.end(); )
        {
            S_MessageBox& pMsg = *iter;
            if( pMsg.m_strInfo.find( szText ) != std::string::npos )
            {
                if ( pMsg.m_pData )
                {
                    delete[] pMsg.m_pData;
                    pMsg.m_pData = NULL;
                }
                iter = m_ltMessagBox.erase(iter);
            }
            else
                ++iter;
        }
    }
    Refeash();
}

bool CUI_ID_FRAME_MessageBox::HasMessageBoxMatchString( const char* szText )
{
	if(!m_pID_FRAME_MESSAGE)
		return false;

    if ( m_ltMessagBox.size() > 0 )
    {
        std::list<S_MessageBox>::iterator iter;
        for( iter = m_ltMessagBox.begin(); iter != m_ltMessagBox.end(); ++iter )
        {
            S_MessageBox& pMsg = *iter;
            if( pMsg.m_strInfo.find( szText ) != std::string::npos )
            {
                return true;
            }
        }
    }
    return false;
}

bool CUI_ID_FRAME_MessageBox::IsEnableOnButCancel()
{
    if(!m_pID_FRAME_MESSAGE)
        return false;

    return m_pID_BUTTON_Cancel->IsEnable();
}

void CUI_ID_FRAME_MessageBox::SetButEnableCancel(bool bValue)
{
    if(!m_pID_FRAME_MESSAGE)
        return;

    m_pID_BUTTON_Cancel->SetEnable(bValue);
}

void CUI_ID_FRAME_MessageBox::SetButVisableCancel(bool bValue)
{
    if(!m_pID_FRAME_MESSAGE)
        return;

    m_pID_BUTTON_Cancel->SetVisable(bValue);
}


const char *CUI_ID_FRAME_MessageBox::GetTextCaption()
{
    if(!m_pID_FRAME_MESSAGE)
        return NULL;

    return m_pID_TEXT_CAPTION->GetText();
}

void CUI_ID_FRAME_MessageBox::SetButYesCaption(const char* pszValue)
{
    if(!m_pID_FRAME_MESSAGE)
        return;

    m_pID_BUTTON_YES->SetCaption(pszValue);
}

void CUI_ID_FRAME_MessageBox::SetButNoCaption(const char *pszValue)
{
    if(!m_pID_FRAME_MESSAGE)
        return;

    m_pID_BUTTON_NO->SetCaption(pszValue);
}

void CUI_ID_FRAME_MessageBox::SetButConfirmVisable(bool bValue)
{
    if(!m_pID_FRAME_MESSAGE)
        return;

    m_pID_BUTTON_COMFIRM->SetVisable(bValue);
}

void CUI_ID_FRAME_MessageBox::SetButConfirmEnable(bool bValue)
{
    if(!m_pID_FRAME_MESSAGE)
        return;

    m_pID_BUTTON_COMFIRM->SetEnable(bValue);
}

bool CUI_ID_FRAME_MessageBox::IsEnableOnButConfirm()
{
    if(!m_pID_FRAME_MESSAGE)
        return false;

    return m_pID_BUTTON_COMFIRM->IsEnable();
}

void CUI_ID_FRAME_MessageBox::ClearMessageCache()
{
	m_ltMessagBox.clear();
}

