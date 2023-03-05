#include "MessageProcess.h"
#include "ui/Login.h"
#include "XmlStringLanguage.h"
#include "MessageBox.h"
#include "GameMain.h"
#include "ExitGame.h"
#include "PasswordProtect.h"
#include "Select.h"
#include "PlayerMgr.h"
#include "PlayerRole.h"
#include "BaseProperty.h"
#include "cfg.h"
#include "ActivityList.h"
#include "CodeCheck.h"
#include "LoginCheck.h"
#include "softKeyboard_configure.h"
#include "MeTerrain/stdafx.h"
#include "AckEnterWorldPackage.h"
#include "wsCamera.h"
#include "color_config.h"
//#include "Alignment.h"
#include "Guild_Create.h"
#include "SplitItemConfig.h"
//#include "WebAward.h"
#include "ui/SkillEquipUpdate.h"
#include "ui/SkillEquipChange.h"
#include "ui/FiveXingUpdate.h"
#include "ui/FiveXingChange.h"
#include "ui/Search.h"
#include "GivePresent.h"
#include "ui/Create.h"
#include "CountryMessage.h"				//added by zhuomeng.hu		[8/26/2010]
#include "InfoTips.h"					//added by zhuomeng.hu		[9/13/2010]
#include "Ui/InfoList.h"
#include "NpcTaskDialogBox.h"
#include "RelationMessage.h"
#include "Ui/SearchTeacher.h"
#include "ConsignmentMessage.h"
#include "Ui/GuildApply.h"
#include "Ui/Achivement.h"
#include "PasswordMessage.h"
#include "BargainingMessage.h"
#include "CampBattleMessage.h"
#include "StallMessage.h"
#include "FamilyMessage.h"
#include "SystemFamily.h"
#include "Ui/DoubleExp.h"
#include "ui/Team.h"
#include "ui/SuAnimalCardList.h"
#include "ui/FamilyApply.h"
#include "Ui/ActivityTrack.h"
#include "ui/ChangeName.h"
#include "QuestEntrustMessage.h"
#include "GameBattleMessage.h"
#include "CSAuthMessage.h"
#include "ui/PassWordCard.h"
extern bool isShowDisconnetMsg;
extern GAME_STATE		g_GameState;
extern BOOL g_bIsEnteringWorld;
extern bool FocusToNameEdit( char bIsTell,void *pData );
extern int g_nCharacterDBID;
extern BOOL g_bIsShowSceneAndPlayer;
extern std::vector<int> g_vecPendingShowInfo;
extern bool	g_maploaded;

//////////////////////////////////////////////////////////////////////////
//临时这样写   GameMain中的代码
#include <shlwapi.h>

HWND GHackWnd = NULL;

void HookClientLogMsg( const char *string, ... )
{
	guardfunc;

	if(GHackWnd)
	{
		if( !string )
			return;
		va_list	va;
		char data[256];
		va_start( va, string );
		wvnsprintf(data, sizeof(data)-1, string, va );
		va_end( va );

		::SendMessage( GHackWnd, WM_SETTEXT, 0, (LPARAM)(LPCSTR)data );
		GetErrorLog()->logString(
			data
			);
	}

	unguard;
}

static bool CancelEnterWorld(const char bPressYesButton, void *pData)
{
	if (!bPressYesButton)
	{
		if( s_CUI_ID_FRAME_Select.GetFrame() )
		{
            s_CUI_ID_FRAME_Select.SetButEnableOnEnter(true);
		}
		s_CUI_ID_FRAME_Select.SetEnterWorldState(false);
		g_MessageProcess.SetEnterWorldQueue( false );
	}
	return true;
}

static bool ConfirmNotEnterWorld(const char bPressYesButton, void *pData)
{
	if (bPressYesButton)
	{
		if( s_CUI_ID_FRAME_Select.GetFrame() )
		{
			s_CUI_ID_FRAME_Select.SetButEnableOnEnter(true);
		}
		s_CUI_ID_FRAME_Select.SetEnterWorldState(false);
		g_MessageProcess.SetEnterWorldQueue( false );
	}
	return true;
}

CMessageProcess g_MessageProcess;

CMessageProcess::CMessageProcess(void)
{
	isDisconnected = false;
	isReadyEnterGame = false;
	dwEnterWorldQueueStartTime = 0;
	isEnterWorld = false;
	isEnterWorldQueue = false;

	dwStartTime = HQ_TimeGetTime();
}

CMessageProcess::~CMessageProcess(void)
{
}

void CMessageProcess::GetNowTime(struct tm& nowtime)
{
	__time64_t ltime;
	_time64(&ltime);
	_localtime64_s(&nowtime, &ltime);
};

//所有关于网络方面功能的处理更新
void CMessageProcess::UpdateMsg()
{
	network::net_run();
	GettheNetworkInput().CheckRevReq();

	if (g_maploaded)
	{
		g_maploaded = false;

		MsgMapLoaded msg;
		std::string address = "";
		theHeroGame.GetMacAddr(&address);
		strncpy(msg.szMacAddress, address.c_str(), sizeof(msg.szMacAddress)-1);
		GettheNetworkInput().SendMsg( &msg,msg.GetLength() );
	}

	if (isEnterWorld)
	{
		isEnterWorld = false;

		s_CUI_ID_FRAME_MessageBox.closeAll(false);
		s_CUI_ID_FRAME_Select.SetButEnableOnEnter(false);
		LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "Enter World!");
		
		theHeroGame.EnterWorld(&ackEnterWorld);
	}

	isDisconnected = false;

	if (GettheNetworkInput().IsClosed())
	{
		isDisconnected = true;
	}

	// 处理上帧未加载完的Player, NPC和怪物，QL，2009/04/29
	theHeroGame.GetPlayerMgr()->ProcessPendingSawPlayerNPC();

	LoginErrorProcess();

	dwStartTime = HQ_TimeGetTime();

	//
	theHeroGame.GetPlayerMgr()->ResetUpdateRoleUI();

	ProcessMsg();

	if( theHeroGame.GetPlayerMgr()->IsNeedUpdateRoleUI() )
	{
		thePlayerRole.UpdateUI();
		s_CUI_ID_FRAME_BaseProperty.Refresh();
	}

	// 发送Ping
	theHeroGame.GetPlayerMgr()->PingServer();
	
	if (isEnterWorldQueue && HQ_TimeGetTime() - dwEnterWorldQueueStartTime >= 3000 )
	{
		isEnterWorldQueue = false;
		MsgEnterWorld msg;
		msg.nSwitchStageType = SSRT_EnterGameServerMap;
		msg.stWhichSlot = theHeroGame.GetPlayerMgr()->sPlayerSlot;
		msg.dwCharacterID = g_nCharacterDBID;
		msg.dwEnterWorldTime = HQ_TimeGetTime();
		msg.dwAccountId = theHeroGame.GetPlayerMgr()->m_dwAccountID;
		GettheNetworkInput().SendMsg(&msg, msg.GetLength() );
		GettheNetworkInput().CheckSendReq();
		//	s_CUI_ID_FRAME_Select.ID_BUTTON_ENTEROnButtonClick(0);
	}
	if ((isDisconnected || HQ_TimeGetTime() > CUI_ID_FRAME_LOGIN::g_dwSwitchGateTime) && !gCfg.m_bLocalVersion && CUI_ID_FRAME_LOGIN::g_bSwitchGate)
	{
		theHeroGame.SwitchGate(/*!CUI_ID_FRAME_LOGIN::m_bNeedAckAgain*/);
		isShowDisconnetMsg = false;
		isDisconnected = false;
	}

	if (isDisconnected && g_GameState != G_LOGIN && !gCfg.m_bLocalVersion && !CUI_ID_FRAME_LOGIN::g_bSwitchGate )
	{
		if( !isShowDisconnetMsg && !s_CUI_ID_FRAME_ExitGame.GetExit() && s_CUI_ID_FRAME_ExitGame.IsShowDKLJ)
		{
			if (CUI_ID_FRAME_LOGIN::m_bNeedAckAgain&&GettheNetworkInput().ConnectToServer(false))
			{
				MsgReConnect msg;
				msg.nAccountId = theHeroGame.GetPlayerMgr()->m_dwAccountID;
				msg.SessionKey = theHeroGame.GetPlayerMgr()->m_SessionKey;
				GettheNetworkInput().SendMsg(&msg);

				CUI_ID_FRAME_LOGIN::g_bSwitchGate = false;
				CUI_ID_FRAME_LOGIN::g_bEndGetCharacter = false;
				return;
			}
			LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_ERROR, "Socket close Disconnected!");

            // added, [2/4/2010 jiayi],添加错误码
            char acErrorString[256] = {0};
			struct tm nowtime;
			GetNowTime(nowtime);
			MeSprintf_s( acErrorString, sizeof(acErrorString)/sizeof(char) - 1, "%02d:%02d:%02d%s[-]", nowtime.tm_hour, nowtime.tm_min, nowtime.tm_sec, theXmlString.GetString(eText_Disconnect)/*, GettheNetworkInput().GetCriticalError() */); 

            s_CUI_ID_FRAME_MessageBox.closeAll(false);
			s_CUI_ID_FRAME_MessageBox.Show(
				acErrorString,
				acErrorString,
				CUI_ID_FRAME_MessageBox::eTypeConfirm,
				true,
				CUI_ID_FRAME_ExitGame::BackToLogin );
            {
                s_CUI_ID_FRAME_MessageBox.SetButConfirmEnable(true);
                s_CUI_ID_FRAME_MessageBox.SetButConfirmVisable(true);
            }

            isShowDisconnetMsg = true;
			CUI_ID_FRAME_LOGIN::m_bNeedAckAgain = true;
        }
	}

	GettheNetworkInput().CheckSendReq();
}

void CMessageProcess::ProcessMsg()
{
	while( 1 )
	{
		//if( !GettheNetworkInput().RecvMsg( szBuf ) )
		//	break;
		Msg* pMsg = (Msg*)GettheNetworkInput().GetMsg()/*szBuf*/;
		if (!pMsg)
		{
			break;
		}

		//////////////////////////////////////////
		if (pMsg->GetType() == MSG_PING)
		{
			int n =0;
			n++;
		}
		//连接时的消息处理
		if( pMsg->GetType() == MSG_MAPINFOREADY )	// 打log
		{
			LOG_MESSAGE(INFO_LOG, LOG_PRIORITY_INFO, "LogInfo: Get MSG_MAPINFOREADY Message\n");
		}

		if (pMsg->GetType() == MSG_SWITCHGATE)//获取建议连接的GateServer 之后又处理 这里无用
		{
			char szDebugInfo[200] = {0};
			MeSprintf_s( szDebugInfo, sizeof(szDebugInfo)/sizeof(char) - 1, "DebugInfo: ID(%d) Length(%d)\n", pMsg->GetType(), pMsg->GetLength() );
			OutputDebugString( szDebugInfo );
		}
		else if (pMsg->GetType() == MSG_OUT_OF_LONGIN_TIME)//登录超时提示
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eLogin_TimeLongConnectFailed), "", 
				CUI_ID_FRAME_MessageBox::eTypeConfirm, true, CUI_ID_FRAME_LOGIN::connectFailed );
		}

		isDisconnected = false; // 还有包先处理，等待下一次IsClose

#ifdef MSG_DBG
		char	szDebugInfo[200];
		sprintf( szDebugInfo, "DebugInfo: %s (Length:%d)", pMsg->header.szDbg, pMsg->GetLength() );
		OutputDebugString( szDebugInfo );
		//AddChatInfo( szDebugInfo,0xFF0000FF);
#endif

		HookClientLogMsg("Begin: %d (Length:%d) Flag: %d\n", pMsg->GetType(), pMsg->GetLength(), pMsg->header.cMsgFlag  );

		if( pMsg->GetLength() < sizeof(Msg) )
		{
			HookClientLogMsg("error:小于 %d的消息: %d (Length:%d) Flag: %d\n", sizeof(Msg), pMsg->GetType(), pMsg->GetLength(), pMsg->header.cMsgFlag   );

			break;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//在之前处理的
		//特殊消息
		//全部改成Switch case
		SpecialMsg( pMsg );
		/////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////
		//游戏流程消息
		switch( g_GameState )
		{
			/////////////////////////////////////////////////////////////////////////////
			//系统登陆界面 状态
		case G_LOGIN:
			{
				GameLoginMsg( pMsg );
			}
			break;
			/////////////////////////////////////////////////////////////////////////////
			//角色建立界面 状态
		case G_CREATE:
			{
				GameCreateMsg( pMsg );
			}
			break;
			/////////////////////////////////////////////////////////////////////////////
			//角色选择界面 状态
		case G_SELECT: 
			{
				GameSelectMsg( pMsg );
			}
			break;
			/////////////////////////////////////////////////////////////////////////////
			//游戏主循环 状态
		case G_MAIN:
			{
				GameMainMsg( pMsg );
			}
			break;
		};

		HookClientLogMsg("end: %d\n", pMsg->GetType() );

		if (HQ_TimeGetTime() - dwStartTime > 10)
		{
			break;
		}
	}
}

//登陆或账号错误处理
void CMessageProcess::LoginErrorProcess()
{
	//////////////////////////////////////////////////////////////
	if (CUI_ID_FRAME_LOGIN::g_nError > 0 && ( CUI_ID_FRAME_LOGIN::g_nError != 1000 || CUI_ID_FRAME_LOGIN::m_bShowQueue ) )
	{
		/*
		gls异常说明:
		1. get_glsid_version
		1208   该用户没激活
		1210   版本错误
		2. login
		1200   glsid不存在 
		1201   glsid过期
		1202   glsid错误
		1203   用户名或密码错误
		1205   用户已经在online表(重复登录)
		1006   帐号被冻结 
		1207   该用户被block

		60001 账号冻结:玩家认为帐号不安全申请临时停权' 
		60002 账号冻结:特殊流程修改安全信息期间临时停权' 
		60003 账号冻结:帐号存在纠纷进行临时行停权到纠纷解决' 
		60004 账号冻结:使用恶意外挂' 
		60005 账号冻结:使用非法程序' 
		60006 账号冻结:利用BUG谋取利益' 
		60007 账号异常，已经被冻结
		60008 临时冻结账号，请联系客服

		3. query_user_status
		1202   glsid错误
		1204   用户不在online表

		*/
		std::string errMsg;
		std::string strCommonErrorMsg = theXmlString.GetString(eLogin_TimeLongConnectFailed);
		switch (CUI_ID_FRAME_LOGIN::g_nError)
		{
		case 1000: // 排队
			{
				char szBuf[256];
				sprintf(szBuf, theXmlString.GetString(eLogin_LoginQueue), CUI_ID_FRAME_LOGIN::g_nQueueNumber);
				errMsg = szBuf;
			}
			break;
		case 1005: errMsg = theXmlString.GetString(eLogin_AccountsError); break;		// 帐号不存在
		case 1006: errMsg = theXmlString.GetString( eLogin_Error_UserFreezed ); break;  // 账号已被冻结
		case 1007: errMsg = theXmlString.GetString(eLogin_PasswordError); break;		// 密码错误
		case 1203: errMsg = theXmlString.GetString(eLogin_UserPassError);  break;		// 用户名，密码验证失败
		case 1205: errMsg = theXmlString.GetString(eLogin_UserAlreadyOnline); break;	// guid已经在线
		case 1207:	// guid block
			{
				errMsg = theXmlString.GetString(eLogin_LoginHighFrequency);
			}
			break;
		case 1208: errMsg = theXmlString.GetString(eText_NotActiveAccounts); break;		// 您的帐号未激活
		case 1209: errMsg = theXmlString.GetString(eLogin_ServerBusy); break;			// 服务器繁忙
		case 1210: errMsg = theXmlString.GetString(eLogin_VersionError); break;			// 版本错误
		case 1211: errMsg = theXmlString.GetString(eText_LoginNeedPwdProtect); break;	// 需要密保卡 
		case 1212: errMsg = theXmlString.GetString(eText_LoginPwdProtectFailed); break;	// 密保卡校验失败
		case 1213: errMsg = theXmlString.GetString(eText_LoginNoPwdProtect); break;		// 不需要密保卡 
		case 60001: 		// 玩家认为帐号不安全申请临时停权
		case 60002: 		// 特殊流程修改安全信息期间临时停权
		case 60003: 		// 帐号存在纠纷进行临时行停权到纠纷解决
		case 60004: 		// 使用恶意外挂
		case 60005: 		// 使用非法程序
		case 60006: 		// 账号异常冻结，请联系客服
		case 60007: 		// 账号异常，已经被冻结
		case 60008: 		// 临时冻结账号，请联系客服
		case 60009: 
		case 60010:
		case 60011: errMsg = theXmlString.GetString(CUI_ID_FRAME_LOGIN::g_nError); break;		// 利用BUG谋取利益
		case 1206:  errMsg = strCommonErrorMsg + "1206"; break; // guid堵塞
		case 1204:  errMsg = strCommonErrorMsg + "1204"; break; // guid 不存在
		case 1200:  errMsg = strCommonErrorMsg + "1200"; break; // session 不存在
		case 1202:  errMsg = strCommonErrorMsg + "1202"; break; // session 错误
		default: errMsg = theXmlString.GetString(eLogin_TimeLongConnectFailed); break;
		}

		s_CUI_ID_FRAME_MessageBox.closeAll(true);

		if (CUI_ID_FRAME_LOGIN::g_nError == 1207)
		{
			LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_ERROR, "GLS Login Error[%d]", CUI_ID_FRAME_LOGIN::g_nError);

			s_CUI_ID_FRAME_MessageBox.Show( errMsg.c_str(), "", 
				CUI_ID_FRAME_MessageBox::eTypeConfirm, true, CUI_ID_FRAME_LOGIN::connectFailed );
			s_CUI_ID_FRAME_MessageBox.SetAutoClose(CUI_ID_FRAME_LOGIN::g_nQueueNumber);
		}
		else if (CUI_ID_FRAME_LOGIN::g_nError == 1210)
		{
			LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_ERROR, "GLS Login Error[%d]", CUI_ID_FRAME_LOGIN::g_nError);

			s_CUI_ID_FRAME_MessageBox.Show( errMsg.c_str(), "", 
				CUI_ID_FRAME_MessageBox::eTypeConfirm, true, CUI_ID_FRAME_ExitGame::TellExitGame );

			s_CUI_ID_FRAME_LOGIN.m_bLogining = false;
		}
		else if (CUI_ID_FRAME_LOGIN::g_nError != 1000)
		{
			LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_ERROR, "GLS Login Error[%d]", CUI_ID_FRAME_LOGIN::g_nError);

			s_CUI_ID_FRAME_MessageBox.Show( errMsg.c_str(), "", 
				CUI_ID_FRAME_MessageBox::eTypeConfirm, true, CUI_ID_FRAME_LOGIN::connectFailed );

			s_CUI_ID_FRAME_LOGIN.m_bLogining = false;
		}
		else	// 排队中
		{
			s_CUI_ID_FRAME_MessageBox.Show( errMsg.c_str(), "", 
				CUI_ID_FRAME_MessageBox::eTypeCancel, true, CUI_ID_FRAME_LOGIN::CancelLoginQueue );
		}


		InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nError), 0);
	}
	else if (CUI_ID_FRAME_LOGIN::g_nError < 0)
	{
		if (CUI_ID_FRAME_LOGIN::g_nLoginLastStatus != CUI_ID_FRAME_LOGIN::g_nError)
		{
			CUI_ID_FRAME_LOGIN::g_nLoginLastStatus = CUI_ID_FRAME_LOGIN::g_nError; // 保存登陆状态

			switch (CUI_ID_FRAME_LOGIN::g_nError)
			{
			case -1: // gls login 成功，显示 正在进入游戏...
				{
					s_CUI_ID_FRAME_MessageBox.closeAll(true);
					s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eLogin_EnterGame), "", 
						CUI_ID_FRAME_MessageBox::eTypeCancel, true, CUI_ID_FRAME_LOGIN::CancelLogin );
				}
				break;
			case -2: // query_user_status，显示 正在处理...
				{
					s_CUI_ID_FRAME_MessageBox.closeAll(true);
					s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eLogin_Process), "", 
						CUI_ID_FRAME_MessageBox::eTypeCancel, true, CUI_ID_FRAME_LOGIN::CancelLogin );

				}
				break;
			case -3: // query_user_status，显示 连接游戏服务器...
				{
					s_CUI_ID_FRAME_MessageBox.closeAll(true);
					s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eLogin_ConnectGate), "", 
						CUI_ID_FRAME_MessageBox::eTypeCancel, true, CUI_ID_FRAME_LOGIN::CancelLogin );


				}
				break;
			case -4: // 勾选密保卡登录，显示密保卡输入界面
				{
					s_CUI_ID_FRAME_MessageBox.closeAll(true);
					s_CUI_ID_FRAME_PasswordProtect.SetVisable(true);
				}
				break;
			}
		}

		InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nError), 0);
	}
}

void CMessageProcess::SpecialMsg(Msg* pMsg)
{
	switch(pMsg->GetType())
	{
	case MSG_CLIENTSHOWMSG://客户端弹出消息框消息
		{
			MsgClientShowMsg *pSHowMsg = (MsgClientShowMsg *)pMsg;
			if( !s_CUI_ID_FRAME_MessageBox.IsVisable() )
				s_CUI_ID_FRAME_MessageBox.Show( pSHowMsg->szMsg );
			break;
		}
		break;
	case MSG_SEND_REAL_TIME://发送客户端服务器当前时间
		{
			MsgSendRealTime* real_time = (MsgSendRealTime*)pMsg;

			__time64_t serverTime = real_time->time;
			__time64_t ltime;
			_time64(&ltime);
			s_CUI_ID_FRAME_ActivityList.SetServerAndLocalOffsetTime( serverTime - ltime );
			theHeroGame.SetServerAndLocalOffsetTime( s_CUI_ID_FRAME_ActivityList.GetServerAndLocalOffsetTime() );
		}
		break;
	case MSG_BEKICK://你被踢的各种原因处理
		{
			MsgNotifyBeKick *pKickMsg = (MsgNotifyBeKick *)pMsg;
			LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_ERROR, "KickType[%d], Kick the accounts!", pKickMsg->kickType);

			if (pKickMsg->kickType == MsgNotifyBeKick::EKT_AccountKick)
			{
				std::string info = theXmlString.GetString(eText_KickAccounts);
				if (info.empty())
					info = theXmlString.GetString(eText_Disconnect);

				s_CUI_ID_FRAME_MessageBox.closeAll(false);
				s_CUI_ID_FRAME_MessageBox.Show(
					info.c_str(),
					"",
					CUI_ID_FRAME_MessageBox::eTypeConfirm,
					true,
					CUI_ID_FRAME_ExitGame::BackToLogin );
				{
					s_CUI_ID_FRAME_MessageBox.SetButConfirmEnable(true);
					s_CUI_ID_FRAME_MessageBox.SetButConfirmVisable(true);
				}
			}
			else if( pKickMsg->kickType == MsgNotifyBeKick::EKT_GraphicCodeTimeOut )
			{				
				std::string info = theXmlString.GetString(eText_GraphicCodeTimeOut);
				if (info.empty())
					info = theXmlString.GetString(eText_Disconnect);

				s_CUI_ID_FRAME_MessageBox.closeAll(false);
				s_CUI_ID_FRAME_MessageBox.Show(
					info.c_str(),
					"",
					CUI_ID_FRAME_MessageBox::eTypeConfirm,
					true,
					CUI_ID_FRAME_ExitGame::BackToLogin );
				
				{
					s_CUI_ID_FRAME_MessageBox.SetButConfirmEnable(true);
					s_CUI_ID_FRAME_MessageBox.SetButConfirmVisable(true);
				}
			}
			else if (pKickMsg->kickType == MsgNotifyBeKick::EKT_GraphicCodeErrorKick)
			{
				std::string info = theXmlString.GetString(eText_GraphicCodeErrorKick);
				if (info.empty())
					info = theXmlString.GetString(eText_Disconnect);

				s_CUI_ID_FRAME_MessageBox.closeAll(false);
				s_CUI_ID_FRAME_MessageBox.Show(
					info.c_str(),
					"",
					CUI_ID_FRAME_MessageBox::eTypeConfirm,
					true,
					CUI_ID_FRAME_ExitGame::BackToLogin );

				{
					s_CUI_ID_FRAME_MessageBox.SetButConfirmEnable(true);
					s_CUI_ID_FRAME_MessageBox.SetButConfirmVisable(true);
				}
			}
			else if (pKickMsg->kickType == MsgNotifyBeKick::EKT_SystemKick)
			{
				std::string info = theXmlString.GetString(eText_KickAccounts);
				if (info.empty())
					info = theXmlString.GetString(eText_Disconnect);

				s_CUI_ID_FRAME_MessageBox.closeAll(false);
				s_CUI_ID_FRAME_MessageBox.Show(
					info.c_str(),
					"",
					CUI_ID_FRAME_MessageBox::eTypeConfirm,
					true,
					CUI_ID_FRAME_ExitGame::BackToLogin );
				{
					s_CUI_ID_FRAME_MessageBox.SetButConfirmEnable(true);
					s_CUI_ID_FRAME_MessageBox.SetButConfirmVisable(true);
				}
			}
			else if(pKickMsg->kickType == MsgNotifyBeKick::EKT_ChangeNameKick)
			{
				s_CUI_ID_FRAME_MessageBox.closeAll(false);
				s_CUI_ID_FRAME_MessageBox.Show(
					theXmlString.GetString(eText_ChangeNameSuccess),
					"",
					CUI_ID_FRAME_MessageBox::eTypeConfirm,
					true,
					CUI_ID_FRAME_ExitGame::BackToLogin );
				{
					s_CUI_ID_FRAME_MessageBox.SetButConfirmEnable(true);
					s_CUI_ID_FRAME_MessageBox.SetButConfirmVisable(true);
				}
			}
			else
			{
				// added, [2/4/2010 jiayi],添加错误码
				char acErrorString[256] = {0};
				struct tm nowtime;
				GetNowTime(nowtime);
				MeSprintf_s( acErrorString, sizeof(acErrorString)/sizeof(char) - 1, "%02d:%02d:%02d%s[-]", nowtime.tm_hour, nowtime.tm_min, nowtime.tm_sec, theXmlString.GetString(eText_Disconnect)/*, GettheNetworkInput().GetCriticalError() */); 

				s_CUI_ID_FRAME_MessageBox.closeAll(false);
				s_CUI_ID_FRAME_MessageBox.Show(
					acErrorString,
					"",
					CUI_ID_FRAME_MessageBox::eTypeConfirm,
					true,
					CUI_ID_FRAME_ExitGame::BackToLogin );

				{
					s_CUI_ID_FRAME_MessageBox.SetButConfirmEnable(true);
					s_CUI_ID_FRAME_MessageBox.SetButConfirmVisable(true);
				}
			}

			isShowDisconnetMsg = true; // 不用显示断开连接 
		}
		break;
	case MSG_REQGRAPHICCODE://请求客户端检测图片验证码
		{
			MsgReqGraphicCode* pReqMsg = ( MsgReqGraphicCode* )pMsg;	
			s_CUI_ID_FRAME_CodeCheck.SetVisable( true );
			s_CUI_ID_FRAME_CodeCheck.SetStreamInfo( pReqMsg->dwTime, pReqMsg->bitsstream, pReqMsg->glyphBuf );
			S_FrameData* pData = (S_FrameData*)s_CUI_ID_FRAME_CodeCheck.GetData();
			if( g_GameState != G_MAIN )
				pData->m_nArrayMode = ArrayMode_Top;
			else
				pData->m_nArrayMode = ArrayMode_Normal;
			if( g_GameState == G_SELECT )
				g_bIsEnteringWorld = TRUE;
			s_CUI_ID_FRAME_MessageBox.closeAll( false );
		}
		break;
	case MSG_REQNUMBERCODE: // 请求客户端检测图片验证码
		{
			MsgReqNumberCode* pReqMsg = (MsgReqNumberCode*)pMsg;
			s_CUI_ID_FRAME_LoginCheck.SetVisable( true );
			s_CUI_ID_FRAME_LoginCheck.SetStreamInfo( pReqMsg->dwTime, pReqMsg->bitsstream );

			ControlFrame* frame =  s_CUI_ID_FRAME_LoginCheck.GetFrame();
			if(frame)
			{
				S_FrameData* pData = (S_FrameData*)frame->GetData();
				if( g_GameState != G_MAIN )
					pData->m_nArrayMode = ArrayMode_Top;
				else
					pData->m_nArrayMode = ArrayMode_Normal;
			}
			if( g_GameState == G_SELECT )
				g_bIsEnteringWorld = TRUE;
			s_CUI_ID_FRAME_MessageBox.closeAll( false );
		}
		break;
	default:
		break;
	}
}

void CMessageProcess::GameLoginMsg(Msg* pMsg)
{
	isReadyEnterGame = false;

	if ( theHeroGame.GetPlayerMgr()->GetLoginSuccess() )
		return;

	switch(pMsg->GetType())
	{
		//之前有处理了
	case MSG_GWDC2C_GWORLDINFO://发送到客户端的游戏世界的信息
		{
			Msg_GWDC2C_GWorldInfo *pInfo = (Msg_GWDC2C_GWorldInfo *)pMsg;
			char szIP[ 200 ];
			in_addr addr;
			addr.S_un.S_addr = pInfo->dwGateIP;
			sprintf( szIP,"%d.%d.%d.%d",addr.S_un.S_un_b.s_b1
				,addr.S_un.S_un_b.s_b2
				,addr.S_un.S_un_b.s_b3
				,addr.S_un.S_un_b.s_b4 );
			int iPercent;
			iPercent = pInfo->iOnlineNum;
			iPercent *= 100;
			if( pInfo->iOnlineMax > 0 )
				iPercent /= pInfo->iOnlineMax;
			else
				iPercent = -1;

			//隐藏等待框
			s_CUI_ID_FRAME_LOGIN.SetLoginWaitSign(false);
			s_CUI_ID_FRAME_LOGIN.SetLoginWaitShow(false);

		}
		break;
	case MSG_PASSWORDCARDREQ:
		{
			CHECK_MSGLEN( pMsg, MsgPassWordCardReq);
			MsgPassWordCardReq* pReq = (MsgPassWordCardReq*)pMsg;
			//客户端需要输入密保卡
			s_CUI_ID_FRAME_PassWordCard.SetShow(pReq->A,pReq->B,pReq->C,pReq->PwdCardSerialNumber);//显示密保卡界面
		}
		break;
	case MSG_ACKLOGIN://登陆时的回馈
		{
			CHECK_MSGLEN( pMsg, MsgAckLogin );
			s_CUI_Progress.SetVisable( false );

			MsgAckLogin* pAckLogin = (MsgAckLogin*)pMsg;

			LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "Receive MsgAckLogin \tResult[%d]", pAckLogin->stErrorCode);

			char szErrMsg[128]="";
			switch( pAckLogin->stErrorCode)
			{
			case MsgAckLogin::ret_succ:
				{
					theHeroGame.GetPlayerMgr()->m_dwAccountID = pAckLogin->dwAccountID;
					theHeroGame.GetPlayerMgr()->m_SessionKey = pAckLogin->SessionKey;
					return;
				}
				break;
			case MsgAckLogin::ret_FullLoad:
				strcpy( szErrMsg, theXmlString.GetString(eLogin_ServerFull) );
				break;
			case MsgAckLogin::error_invaliduserorpass:
				strcpy( szErrMsg, theXmlString.GetString(eLogin_UserPassError) );
				break;
			case MsgAckLogin::error_invalidversion:
				strcpy( szErrMsg, theXmlString.GetString(eLogin_VersionError) );
				break;
			case MsgAckLogin::ret_invalidusername:
				strcpy( szErrMsg, theXmlString.GetString(eLogin_UserPassError) );
				break;
			case MsgAckLogin::ret_invalidpassword:
				strcpy( szErrMsg, theXmlString.GetString(eLogin_UserPassError) );
				break;
			case MsgAckLogin::ret_alreadyaloginthisaccount:
				strcpy( szErrMsg, theXmlString.GetString(eLogin_UseOnline) );
				break;
			case MsgAckLogin::ret_loginfail:
				strcpy( szErrMsg, theXmlString.GetString(eLogin_UserPassError) );
				break;
			case MsgAckLogin::ret_secondpwderror:
				strcpy( szErrMsg, theXmlString.GetString(eText_GraphicCodeErrorKick) );
				break;
			case MsgAckLogin::ret_noactive:
				strcpy( szErrMsg, theXmlString.GetString(eText_NotActiveAccounts) );
				break;
			case MsgAckLogin::ret_noservice:
				strcpy( szErrMsg, theXmlString.GetString(eError_ServerBusy) );
				break;
			case MsgAckLogin::ret_blocked:
				MeSprintf_s( szErrMsg, sizeof(szErrMsg)/sizeof(char) - 1, theXmlString.GetString(eText_BlockAccount), pAckLogin->blocktime/60 + 1);
				break;
			case MsgAckLogin::ret_FullMac:
				strcpy( szErrMsg, theXmlString.GetString(eText_Login_MacFull) );
				break;
			case MsgAckLogin::ret_PwdCardError:
				strcpy( szErrMsg, theXmlString.GetString(etext_Login_PwdCardError) );
				break;
			default:
				strcpy( szErrMsg, theXmlString.GetString(eLogin_UnKnown) );
				break;
			}
			s_CUI_ID_FRAME_MessageBox.closeAll(true);
			s_CUI_ID_FRAME_MessageBox.Show( szErrMsg );
			s_CUI_ID_FRAME_LOGIN.SetEnable( true );
			s_CUI_ID_FRAME_LOGIN.setBtnDisable( false );
			s_CUI_ID_FRAME_LOGIN.setStartLogin_Time( 0 );
			theUiManager.SetFocus( s_CUI_ID_FRAME_LOGIN.GetEditPas() );
		}
		break;
	case MSG_SWITCHGATE://获取建议连接的GateServer
		{
			theHeroGame.ProcessSwitchGateMsg(pMsg);
		}
		break;
	case MSG_S2CSENDSOFTKEYBOARD://loginServer发送软件盘对应序列给客户端
		{//zizi add
			CHECK_MSGLEN( pMsg, MsgS2CSendSoftKeyboard);
			MsgS2CSendSoftKeyboard* softKeyboard = (MsgS2CSendSoftKeyboard*)pMsg;

			std::map<int, std::string> softKeyboardInfo = g_SoftKeyboard_configure.getKeyInfoMap();
			std::map<int, std::string>::iterator iter = softKeyboardInfo.begin();
			for( int i = 0; iter != softKeyboardInfo.end(); ++iter, ++i )
			{

			}
		}
		break;
	case MSG_ACKCHAR:// 角色信息
		{
			MsgAckChar* pAckChar = (MsgAckChar*)pMsg;
			LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "Receive MsgAckChar \tName[%s]", pAckChar->baseinfo.aptotic.szCharacterName );

			s_CUI_ID_FRAME_Select.AddPlayer(pAckChar, &pAckChar->baseinfo,&pAckChar->visual, pAckChar->stWhichSlot, pAckChar->dwCharacterID, pAckChar->bIsDel,pAckChar->dwDelTimes);
		}
		break;
	
	case MSG_ENDACKCHAR:// 获取角色列表结束
		{
			LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "Receive MsgEndAckChar" );

			if(s_CUI_ID_FRAME_Select.IsHavePlayer())
			{
				s_CUI_ID_FRAME_Select.SetSlotEmpty(0);
			    ChangeGameState( G_LOGIN, G_CREATE);
			}
			else
			    ChangeGameState( G_LOGIN, G_SELECT );
			theUiManager.Compositor();
			theUiManager.SetFocus( s_CUI_ID_FRAME_Select.GetListOnSelect()/*::m_pID_LIST_PLAYER*/ );
			CUI_ID_FRAME_LOGIN::g_bEndGetCharacter = FALSE;

			s_CUI_ID_FRAME_MessageBox.closeAll(true);

			s_CUI_ID_FRAME_LOGIN.m_bLogining = false;

		}
		break;
	case MSG_LOGINWAIT:
		{
			MsgLoginWait* pWait = (MsgLoginWait*)pMsg;
			if (pWait&&pWait->getcharacter)
			{
				//s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_GetingCharacter), "", CUI_ID_FRAME_MessageBox::eTypeCancel, true, s_CUI_ID_FRAME_LOGIN.CancelLogin);
				//// 验证200秒改成60秒
				//s_CUI_ID_FRAME_MessageBox.SetAutoClose(60, false);
				//s_CUI_ID_FRAME_MessageBox.SetButEnableCancel(true);
			}
			else
			{
				s_CUI_Progress.SetVisable( false );
				char szErrMsg[128]="";
				strcpy( szErrMsg, theXmlString.GetString(eLogin_UnKnown) );
				s_CUI_ID_FRAME_MessageBox.closeAll(true);
				s_CUI_ID_FRAME_MessageBox.Show( szErrMsg );
				s_CUI_ID_FRAME_LOGIN.SetEnable( true );
				s_CUI_ID_FRAME_LOGIN.setBtnDisable( false );
				s_CUI_ID_FRAME_LOGIN.setStartLogin_Time( 0 );
				theUiManager.SetFocus( s_CUI_ID_FRAME_LOGIN.GetEditPas() );
			}
		}
		break;
	/*case MSG_TELLC_REASKGATE:
		{
			CUI_ID_FRAME_LOGIN::m_bNeedAckAgain = true;
			CUI_ID_FRAME_LOGIN::g_bSwitchGate = true;
			CUI_ID_FRAME_LOGIN::g_dwSwitchGateTime = HQ_TimeGetTime() + CUI_ID_FRAME_LOGIN::g_dwSwitchGatePeriod;
		}
		break;*/
	}
}

void CMessageProcess::GameCreateMsg(Msg* pMsg)
{
	switch(pMsg->GetType())
	{
	case MSG_ACKCREATECHAR://登陆时的图形验证码
		{
			MsgAckCreateChar* pAckCreateChar = (MsgAckCreateChar*)pMsg;
			s_CUI_ID_FRAME_CREATE.EnableOKBtn();							//added by zhuomeng.hu		[9/3/2010]
			if ( pAckCreateChar->bCreateSucc == true )
			{
				ChangeGameState( G_CREATE, G_SELECT );
				s_CUI_ID_FRAME_Select.m_CurrentSelectIndex = pAckCreateChar->stWhichSlot+1;
			}
			else
			{
				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eCreate_PlayerNameSame) );
			}
		}
		break;
	case MSG_ACKCHAR://角色信息
		{
			MsgAckChar* pAckChar = (MsgAckChar*)pMsg;
			OutputDebugString("Add");
			s_CUI_ID_FRAME_Select.AddPlayer(pAckChar, &pAckChar->baseinfo,&pAckChar->visual, pAckChar->stWhichSlot, pAckChar->dwCharacterID, false,pAckChar->dwDelTimes );
		}
		break;
	case MSG_ACK_CREATECHECKNAME://返回 客户端创建人物发送的请求检测名字是否重复
		{
			MsgAckCreateCheckName* pAck = (MsgAckCreateCheckName*)pMsg;
			if( pAck->bResult )
			{
				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_CreateCheckNameOK), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true );
			}
			else
			{
				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_CreateCheckNameNO), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true, FocusToNameEdit );
			}
		}
		break;
	}
}

DWORD WINAPI ThreadHandLoginWorldQueue(LPVOID lpparam)
{	
	MsgEnterWorld* msg=(MsgEnterWorld *)lpparam;
	Sleep(3000);
	GettheNetworkInput().SendMsg(msg, msg->GetLength() );
	GettheNetworkInput().CheckSendReq();
	delete msg;
	return 0;
}

bool _BackToLogin( char bIsTell,void *pData ) 
{
	if (bIsTell)
	{
		CUI_ID_FRAME_ExitGame::BackToLogin(true,NULL);
	}

	return true;
}

void CMessageProcess::GameSelectMsg(Msg* pMsg)
{
	switch(pMsg->GetType())
	{
	case MSG_ACKCHAR:// 角色信息
		{
			MsgAckChar* pAckChar = (MsgAckChar*)pMsg;
			//pAckChar->baseinfo.liveinfo.hero_id	= INVALID_HERO_ID;
			s_CUI_ID_FRAME_Select.AddPlayer(pAckChar, &pAckChar->baseinfo,&pAckChar->visual, pAckChar->stWhichSlot, pAckChar->dwCharacterID, pAckChar->bIsDel,pAckChar->dwDelTimes);
		}
		break;
	case MSG_ENDACKCHAR:// 获取角色列表结束
		{
			theUiManager.Compositor();
			theUiManager.SetFocus( s_CUI_ID_FRAME_Select.GetListOnSelect() );
			CUI_ID_FRAME_LOGIN::g_bEndGetCharacter = FALSE;
			s_CUI_ID_FRAME_Select.SetCurrSelectPlayer();
			if (isReadyEnterGame)
			{
				MsgEnterWorld msgEnterWorld;
				msgEnterWorld.stWhichSlot = theHeroGame.GetPlayerMgr()->sPlayerSlot;
				msgEnterWorld.dwCharacterID = g_nCharacterDBID;
				msgEnterWorld.dwEnterWorldTime = HQ_TimeGetTime();
				msgEnterWorld.dwAccountId = theHeroGame.GetPlayerMgr()->m_dwAccountID;
				msgEnterWorld.nSwitchStageType = SSRT_EnterGameServerMap;
				GettheNetworkInput().SendMsg(&msgEnterWorld);

				isReadyEnterGame = false;
			}
		}
		break;
	case MSG_ACKENTERWORLDPACK://GateServer优化进入游戏消息(对数据进行压缩)
		{
			SwGlobal::SetLoadProgress( 0 );
			s_CUI_ID_FRAME_LoadMap.SetVisable( true );
			s_CUI_ID_FRAME_LoadMap.randomLoginMap();
			s_CUI_ID_FRAME_LoadMap.SetProcessValue(0);

			static CAckEnterWorldPackage unpacker;
			MsgAckEnterWorld* pAckEnterWorld = unpacker.UnPackageMsg(*static_cast<MsgAckEnterWorldPack*>(pMsg));
			if (pAckEnterWorld == NULL)
			{
				return;
			}
			if ( pAckEnterWorld->nResult == ER_Success )
			{
				memcpy(&ackEnterWorld, pAckEnterWorld, sizeof(MsgAckEnterWorld));
				isEnterWorld = true; // EnterWorld比较慢，先显示Loading界面，下一帧开始EnterWorld
				s_CUI_ID_FRAME_ActivityTrack.ClearAllSpecial();
				return;
			}
			else
			{
				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eLogin_UnKnown) );
			}

			D3DXVECTOR3 vFromPt	 = D3DXVECTOR3( 0.0f, -480.0f, 0.0f );
			D3DXVECTOR3 vLookatPt = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
			D3DXVECTOR3 vUpVec	  = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
			getwsCamera()->GetMeCamera()->SetViewParams( vFromPt, vLookatPt, vUpVec );

			FLOAT fAspect = ((FLOAT)SCREEN_WIDTH) / SCREEN_HEIGHT;
			getwsCamera()->GetMeCamera()->SetProjParams( D3DX_PI*(50/45.0f)/4, fAspect, 1.0f, 120.0f );
			theHeroGame.GetD3DDevice()->SetTransform( D3DTS_PROJECTION, (D3DXMATRIX*)&getwsCamera()->GetMeCamera()->GetProjMatrix() );
		}
		break;
	case MSG_ACKENTERWORLD:// 进入游戏
		{
			MsgAckEnterWorld* pAckEnterWorld = (MsgAckEnterWorld*)pMsg;
			if ( pAckEnterWorld->nResult == ER_Success )
			{
				theHeroGame.EnterWorld(pAckEnterWorld);
				return;
			}
			else
			{
				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eLogin_UnKnown) );
			}

			D3DXVECTOR3 vFromPt	 = D3DXVECTOR3( 0.0f, -480.0f, 0.0f );
			D3DXVECTOR3 vLookatPt = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
			D3DXVECTOR3 vUpVec	  = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
			getwsCamera()->GetMeCamera()->SetViewParams( vFromPt, vLookatPt, vUpVec );

			FLOAT fAspect = ((FLOAT)SCREEN_WIDTH) / SCREEN_HEIGHT;
			getwsCamera()->GetMeCamera()->SetProjParams( D3DX_PI*(50/45.0f)/4, fAspect, 1.0f, 120.0f );
			theHeroGame.GetD3DDevice()->SetTransform( D3DTS_PROJECTION, (D3DXMATRIX*)&getwsCamera()->GetMeCamera()->GetProjMatrix() );
		}
		break;
	case MSG_ACK_RESULT://回馈信息
		{
			MsgAckResult* pResult = (MsgAckResult*)pMsg;
			if( pResult->result != ER_Success )
			{
				//暂时去掉打印,太多了 by vvx 2013.11.22
				/*char szError[255];
				MeSprintf_s( szError, sizeof(szError)/sizeof(char) - 1, "G_SELECT: ACK_RESULT_ERROR_ID: %d", pResult->result );
				LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, szError );*/
			}
			switch( pResult->result )
			{
			case ER_EnterWorldWhithOffineStall:
				{
					s_CUI_ID_FRAME_MessageBox.closeAll(false);

					s_CUI_ID_FRAME_MessageBox.Show(
						theXmlString.GetString(eText_Stall_offLine_login),
						"",
						CUI_ID_FRAME_MessageBox::eTypeConfirm,
						true,
						_BackToLogin );
					{
						s_CUI_ID_FRAME_MessageBox.SetButConfirmEnable(true);
						s_CUI_ID_FRAME_MessageBox.SetButConfirmVisable(true);
					}

					
                   
				}
				break;
			case ER_EnterWorldQueue:
				{
					char szBuf[256]={0};
					sprintf(szBuf, theXmlString.GetString(eLogin_LoginQueue), pResult->value + 1);

					s_CUI_ID_FRAME_MessageBox.closeAll(false);
					s_CUI_ID_FRAME_MessageBox.Show( szBuf, "", 
						CUI_ID_FRAME_MessageBox::eTypeCancel, true, CancelEnterWorld );

					isEnterWorldQueue = true;
					dwEnterWorldQueueStartTime = HQ_TimeGetTime();
					//排队修改,在主循环有发送enter请求,这里就不用多线程发了吧? vvx 2013.7.19
					/*MsgEnterWorld *msg=new MsgEnterWorld;
					msg->nSwitchStageType = SSRT_EnterGameServerMap;
					msg->stWhichSlot = theHeroGame.GetPlayerMgr()->sPlayerSlot;
					msg->dwCharacterID = g_nCharacterDBID;
					msg->dwEnterWorldTime = HQ_TimeGetTime();
					msg->dwAccountId = theHeroGame.GetPlayerMgr()->m_dwAccountID;

					DWORD dwthread;
					::CreateThread(NULL,0,ThreadHandLoginWorldQueue,(LPVOID)msg,0,&dwthread);*/
				}
				break;
			// 服务器繁忙
			case ER_LocusGameServerNotExit:
			case ER_GameServerNotExist:
			case ER_SystemException:
			case ER_CharacterServerCantBeGameServer:
				{
					char str[MAX_PATH] = {0};
					sprintf(str, "%s(%d)", theXmlString.GetString(eText_ChangeMapServerBusy), pResult->result);
					s_CUI_ID_FRAME_MessageBox.closeAll(false);
					s_CUI_ID_FRAME_MessageBox.SetButEnableCancel(true);
					s_CUI_ID_FRAME_MessageBox.SetButVisableCancel(true);
					s_CUI_ID_FRAME_MessageBox.Show( str, "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true );

					isShowDisconnetMsg = true;
				}
				break;
			case ER_ChangeNameItemNotExist:
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_ChangeNameNoItem) );
				}
				break;
			case ER_PetLearnSkill:
				//宠物技能学习失败
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetFailLearnSkill) );
				}
				break;
			case ER_PetLevelSkill:
				//宠物等级不足学习失败
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetLevelSkill) );
				}
				break;
			case ER_PetSkillMoney:
				//金钱不足无法学习
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetSkillMoney) );
				}
				break;
			case ER_PetSavvyUpMoney:
				//金钱不足无法提升悟性
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetSavvyUpMoney) );
				}
				break;
			case ER_PetSavvyBone:
				//根骨不足无法提升悟性
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetSavvyBone) );
				}
				break;
			case ER_PetSavvyUp:
				//宠物提升悟性失败
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetSavvyUp) );
				}
				break;
			case ER_IsActivePet:
				//出战宠物无法进行操作
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetIsActivePet) );
				}
				break;
			case ER_CatchSkillLevel:
				 // 宠物捕捉技能等级不足
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_CatchSkillLevel) );
				}
				break;
			case ER_PetIdentify:
				// 没有宠物图鉴无法捕捉
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetIdentify) );
				}
				break;
			case ER_PetSavvyReduce:
				//宠物不小心悟性降低到了%d
				{
					char temp[64];
					MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eText_PetSavvyReduce),pResult->value);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, temp);
				}
				break;
			default:
				break;
			}
		}
		break;
	case MSG_ACKDELETECHAR:// 删除角色
		{
			if ( MsgAckDeleteChar* pAckDeleteChar = static_cast<MsgAckDeleteChar*>(pMsg) )
			{
				if ( pAckDeleteChar->bDeleteSucc == true )
				{
					UINT nIndex = s_CUI_ID_FRAME_Select.GetCurSelIndex();
					if (nIndex >= 0 && nIndex < MAX_PLAYER_COUNT )
					{
						if( s_CUI_ID_FRAME_Select.GetPlayerAnim(nIndex) )
						{
							s_CUI_ID_FRAME_Select.SetDel(nIndex,true,pAckDeleteChar->dwDelTimes);
						}
						s_CUI_ID_FRAME_Select.Refeash(nIndex);
						s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_DelChar_OK) );
					}	
				}
				else
				{
					switch( pAckDeleteChar->dwReason ) 
					{
					case MsgAckDeleteChar::eYouAreGuildMaster:
						break;
					default:
						break;
					}
				}
			}// End if						
		}
		break;
	case MSG_ACK_CANCELDELCHAR:// 取消删除角色
		{
			if ( MsgAckCancelDelChar* pAck = static_cast<MsgAckCancelDelChar*>(pMsg) )
			{
				if ( pAck->bSucc == true )
				{
					s_CUI_ID_FRAME_Select.SetDel(pAck->stWhichSlot,false,0);
					s_CUI_ID_FRAME_Select.Refeash(pAck->stWhichSlot);
					s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_CancelDel_Success) );
				}
				else
				{
					s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_CancelDel_Fail) );
				}
			}// End if						
		}
		break;
	case MSG_SWITCHGATE://选择GateServer
		{
			theHeroGame.ProcessSwitchGateMsg(pMsg);
			isReadyEnterGame = true;
		}
		break;
	case MSG_SERVERSHUTDOWN://服务器关闭提示
		{
			char szBuf[256]={0};
			char szTime[64]={0};
			MsgShutdownServer *pShutdownMsg = (MsgShutdownServer*)pMsg;
			int minute = pShutdownMsg->delayTime / 60;
			int second = pShutdownMsg->delayTime - minute * 60;
			if( minute > 0 && second > 0 )
				MeSprintf_s(szTime, sizeof(szTime)/sizeof(char)-1, "%d%s%d%s", minute, theXmlString.GetString(eText_Title_Minute),
					second, theXmlString.GetString(eTimeUnit_Second));
			else if( minute > 0 )
				MeSprintf_s(szTime, sizeof(szTime)/sizeof(char)-1, "%d%s", minute, theXmlString.GetString(eText_Title_Minute));
			else if( second > 0 )
				MeSprintf_s(szTime, sizeof(szTime)/sizeof(char)-1, "%d%s", second, theXmlString.GetString(eTimeUnit_Second));

			MeSprintf_s(szBuf, sizeof(szBuf)/sizeof(char)-1, theXmlString.GetString(eText_ServerShutdown2), szTime);

			s_CUI_ID_FRAME_MessageBox.closeAll(false);
			s_CUI_ID_FRAME_MessageBox.Show( szBuf, "", 
				CUI_ID_FRAME_MessageBox::eTypeConfirm, true, ConfirmNotEnterWorld );
		}
		break;
	case MSG_ENTERWORLDCHANGENAMEREQ:
		{
			//弹出UI 让客户端修改名称
			//1.结束客户端的倒计时的状态
			
			//2.弹出UI 最上面
			s_CUI_ID_FRAME_ChangeName.SetVisable(true);
		}
		break;
	case MSG_NEWCHANGENAMEACK:
		{
			MsgNewChangeNameAck * pCN = (MsgNewChangeNameAck *)pMsg;
			bool Result = pCN->Result;
			s_CUI_ID_FRAME_ChangeName.OnChangeNameAck(Result);
		}
		break;
	case MSG_CHANNELSINFO:
		theHeroGame.GetPlayerMgr()->OnMsgSelectChannel(pMsg);
		break;
	case MSG_CHANGE_SKILL:
		{
			theHeroGame.GetPlayerMgr()->OnMsgChangeSkillBySelect( pMsg );
		}	
		break;
	case MSG_ASKGETSALARY_ACK:
		theHeroGame.GetPlayerMgr()->OnMsgAskGetSalaryAck(pMsg);
		break;
	}
}

void CMessageProcess::GameMainMsg(Msg* pMsg)
{
	switch(pMsg->GetType()) 
	{
	case MSG_SETDIALOGNAME://设置对话框名称
		{
			if( sizeof( MsgSetDialogName ) == pMsg->GetLength() )
			{
				MsgSetDialogName* pMsgName = (MsgSetDialogName*)pMsg;
				s_CUI_ID_FRAME_NpcChatDialogBox.SetDialogName( pMsgName->szName );
			}
		}
		break;
	case MSG_SCRIPTEND://脚本结束
		{
			//s_CUI_ID_FRAME_NpcChatDialogBox.CloseDialog();
			s_CUI_NpcTaskDialogBox.ProcessBackEndScript();

			MsgScriptEnd* pScript = ( MsgScriptEnd* )pMsg;
			if ( pScript )
			{
				if ( pScript->type == ST_ScriptSleep )
					s_CUI_Progress.SetProgressComplete();
			}
		}
		break;
	case MSG_ACK_CREATECHECKNAME:// 改名失败
		{
			MsgAckCreateCheckName* pAck = (MsgAckCreateCheckName*)pMsg;
			if( pAck->bResult )
			{
				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_CreateCheckNameOK), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true );
			}
			else
			{
				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_CreateCheckNameNO), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true );
			}
		}
		break;
	case MSG_ACK_RESULT://回馈消息
		{
			MsgAckResult* pResult = (MsgAckResult*)pMsg;
			if( pResult->result != ER_Success )
			{
				char szError[256] = {0};
				MeSprintf_s( szError, sizeof(szError)/sizeof(char) -1, "G_MAIN: ACK_RESULT_ERROR_ID: %d", pResult->result );
				LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, szError );
			}
			switch(pResult->result)
			{
			case ER_NotEnoughEnjoyment:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_MountEnjoymentNotEnough ) );
				break;
			case ER_NotActiveMount:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_Mount_NotActived ) );
				break;
			case ER_TargetNotActiveMount:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_TargetNoActiveMount ) );
				break;
			case ER_InProtectLevel:
				{
					char msg[MAX_PATH] = {0};
					MeSprintf_s(msg, sizeof(msg)/sizeof(char) -1, theXmlString.GetString( eText_PKMode_LevelLimit ), (int)pResult->value);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PKMode_Change, msg );
				}
				break;
			case ER_OrganizeMaxMemberLimit:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, theXmlString.GetString( eErrorGangMaxNumber ) );
				break;	
			case ER_OrganizeHaveExist:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs,theXmlString.GetString( eErrorGangName ) );
				break;
			case ER_OrganizeMemberHaveExist:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs,theXmlString.GetString( eErrorAlreadyInThisGang ) );
				break;
			case ER_TargetOrganizeHaveExist:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs,theXmlString.GetString( eErrorAlreadyInGang ) );
				break;
			case ER_TargetHaveInTheSameOrganize:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs,theXmlString.GetString( eErrorAlreadyInThisGang ) );
				break;
			case ER_MountCantLearnSkill:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Server_Mount_Error,theXmlString.GetString( eText_NoActiveMountSkillHole ) );
				break;
			case ER_HighShoutTimeLimitFail:
				CommonChatFrame::GetActiveChatFrame()->_tmHighShoutColdTime = pResult->value;
				CommonChatFrame::GetActiveChatFrame()->_tmHighShoutLastTime = clock();
				CommonChatFrame::GetActiveChatFrame()->SendChatMessage(MsgChat::CHAT_TYPE_HIGHSHOUT,"0");
				break;
			case ER_HighShoutNotEnoughMoney:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Chat_ChannelTip, theXmlString.GetString( eText_NoMoneyForWorldChat ) );
				break;
			case ER_HighShoutTimeLimitSuccess:
				CommonChatFrame::GetActiveChatFrame()->_tmHighShoutColdTime = pResult->value;
				CommonChatFrame::GetActiveChatFrame()->_tmHighShoutLastTime = clock();
				break;
			case ER_TargetMaxMoneyLimit:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_Failed, theXmlString.GetString( eText_Player_Beyong_Max_Money ) );
				break;
			case ER_InProtectLockTime:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_Failed, theXmlString.GetString( eText_TradeFailed_PlayerInProtect ) );
				break;
			case ER_TeamMemberMustHaveQuest:
				{
					std::vector<TeamInfo> vInfo = thePlayerRole.GetTeamInfo();
					for( int i = 0 ; i < vInfo.size() ; ++ i )
					{
						if( vInfo[i].nID == pResult->value )
						{
							char szBuff[256] = {0};
							MeSprintf_s( szBuff, sizeof(szBuff)/sizeof(char) - 1, theXmlString.GetString( eTellClient_TeamMemberMustHaveQuest ),vInfo[i].szName.c_str() );									
							CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, szBuff );
						}
					}
					
				}						
				break;
			case ER_TeamMemberAlreadyEntryMap:
				{							
					std::vector<TeamInfo> vInfo = thePlayerRole.GetTeamInfo();
					for( int i = 0 ; i < vInfo.size() ; ++ i )
					{
						if( vInfo[i].nID == pResult->value )
						{
							char szBuff[256] = {0};
							MeSprintf_s( szBuff, sizeof(szBuff)/sizeof(char) - 1, theXmlString.GetString( eTellClient_AlreadyEnterOnce ),vInfo[i].szName.c_str() );									
							CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, szBuff );
						}
					}
				}
				break;
			case ER_MapGameServerPlayerIsFull:
				{
					// 提示
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_MapChange_Failed, theXmlString.GetString( eText_ChangeMapFailed_MapFull ) );

					if( thePlayerRole.IsShowingWaitforTransport() )
					{
						thePlayerRole.CloseShowingWaitforTransport();
						s_CUI_ID_FRAME_MessageBox.closeAll(false);
					}
				}
				break;
			case ER_InMyBlacklist:
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, theXmlString.GetString(eText_AddFriInBlackList) );
				}
				break;
			case ER_BanSpeakTime:
				{
					thePlayerRole.SetBanSpeakEndingTime( pResult->value * 60 * 1000 + HQ_TimeGetTime() );
					if( pResult->value > 0 )
					{
						char str[MAX_PATH] = {0};
						MeSprintf_s(str, sizeof(str)/sizeof(char) - 1, theXmlString.GetString(eText_BanSpeak), pResult->value);
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, str );
					}
				}
				break;
			case ER_TargetPkValueFail:
				// 红名不能被玩家复活
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Relive_Belongs, theXmlString.GetString( eText_PKRedNameCannotRelive ) );
				break;
			case ER_LeaveStage:
				// 退出副本倒计时
				if( pResult->value > 0 )
				{
					char str[MAX_PATH] = {0};
					MeSprintf_s(str, sizeof(str)/sizeof(char) - 1, theXmlString.GetString(eClient_WaitLeaveStage), pResult->value);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Ectype_Success, str );
				}
				break;
			case ER_BeReliveTimeOver:
				// 被复活的有效时间过了
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Relive_Belongs, theXmlString.GetString( eText_ReliveTimeOut ) );
				break;
				// 服务器繁忙
			case ER_LocusGameServerNotExit:
			case ER_GameServerNotExist:
			case ER_SystemException:
			case ER_CharacterServerCantBeGameServer:
				{
					char str[MAX_PATH] = {0};
					MeSprintf_s(str, sizeof(str)/sizeof(char) - 1, "%s(%d)", theXmlString.GetString(eText_ChangeMapServerBusy), pResult->result);
					s_CUI_ID_FRAME_MessageBox.closeAll(false);
					s_CUI_ID_FRAME_MessageBox.SetButEnableCancel(true);
					s_CUI_ID_FRAME_MessageBox.SetButVisableCancel(true);
					s_CUI_ID_FRAME_MessageBox.Show( str, "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true );

					isShowDisconnetMsg = true;
				}
				break;
			case ER_ExchangeJinDingLevelLow:
				{
					char str[MAX_PATH] = {0};
					MeSprintf_s(str, sizeof(str)/sizeof(char) - 1, theXmlString.GetString(eText_ExchangeJinDingLevelLow), pResult->value);
					s_CUI_ID_FRAME_MessageBox.Show( str, "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true );
				}
				break;
				// 分解失败提示
			case ER_SplitItemNotExist:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Combine_Failed, theXmlString.GetString( eText_SplitFailed_ItemNotExist ) );
				break;
			case ER_SplitItemIndexGuidError:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Combine_Failed, theXmlString.GetString( eText_SplitFailed_ItemIndexGuidError ) );
				break;
			case ER_SplitItemTypeError:
			case ER_SplitItemLevelError:
			case ER_SplitItemLevelMulError:
			case ER_SplitItemConfigNotExist:
				{
					char str[MAX_PATH] = {0};
					char str_code[MAX_PATH] = {0};
					uint16 level = 0;//theItemSplitConfig.GetLevel();
					MeSprintf_s(str, sizeof(str)/sizeof(char) - 1, theXmlString.GetString(eText_SplitFailed_ItemTypeLevelError), level);
					MeSprintf_s(str_code, sizeof(str_code)/sizeof(char) - 1, "%s(%d)", str, pResult->result);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Combine_Failed, str_code );
				}
				break;
			case ER_SplitItemCantBeSplit:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Combine_Failed, theXmlString.GetString( eText_SplitFailed_CantBeSplit ) );
				break;
			case ER_SplitItemQualityLevelError:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Combine_Failed, theXmlString.GetString( eText_SplitFailed_QualityLevelError ) );
				break;
			case ER_SplitItemProductNotExit:
			case ER_SplitItemCreateFail:
			case ER_SplitItemPopFail:
			case ER_ItemConfigNotExist:
				{
					char str_code[MAX_PATH] = {0};
					MeSprintf_s(str_code, sizeof(str_code)/sizeof(char) - 1, "%s(%d)", theXmlString.GetString( eText_SplitFailed ), pResult->result);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Combine_Failed, str_code );
				}
				break;
			case ER_SplitItemPushFail:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Combine_Failed, theXmlString.GetString( eText_ItemNoPlace ) );
				break;
			case ER_MaxPubQuestCount:
				{
					char str_code[MAX_PATH] = {0};
					MeSprintf_s(str_code, sizeof(str_code)/sizeof(char) - 1, theXmlString.GetString( eText_MaxPubTaskNumber ), pResult->value);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Info_ChatSys, str_code );
				}
				break;
			case ER_MaxConQuestCount:
				{
					char str_code[MAX_PATH] = {0};
					MeSprintf_s(str_code, sizeof(str_code)/sizeof(char) - 1, theXmlString.GetString( 403 ), pResult->value);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Info_ChatSys, str_code );
				}
				break;
			//case ER_MoneyItemExchangePopFail:
			//	{
			//		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, theXmlString.GetString( eRealAward_ItemError ) );
			//		s_CUI_ID_FRAME_WebAward.SetVisable(true);
			//	}
			//	break;
			case ER_TakeMoneyCorrect:
				{
					if( g_bIsShowSceneAndPlayer )
					{
						const char* szMsg = theXmlString.GetString( eText_PackMoneyCorrect );
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, szMsg );
					}
					else
						g_vecPendingShowInfo.push_back(eText_PackMoneyCorrect);
				}
				break;
			case ER_StorageMoneyCorrect:
				{
					if( g_bIsShowSceneAndPlayer )
					{
						const char* szMsg = theXmlString.GetString( eText_StorageMoneyCorrect );
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Pack_Operate, szMsg );
					}
					else
						g_vecPendingShowInfo.push_back(eText_StorageMoneyCorrect);
				}
				break;
			case ER_ChangeNameItemNotExist:
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_ChangeNameNoItem) );
				}
				break;
			case ER_XinShouCardAbout:
				switch( pResult->value )
				{
				case ESR_NotExist:
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_NoXinShouCard) );
					break;
				case ESR_HaveGet:
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_GotXinShouCard) );
					break;
				case ESR_ResourceFail:
				case ESR_BagFull:
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_GetCardGiftFailed) );
					break;
				}
				break;
			case ER_17173CardAbout:
				switch( pResult->value )
				{
				case ESR_NotExist:
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_No17173Card) );
					break;
				case ESR_HaveGet:
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_Got17173Card) );
					break;
				case ESR_ResourceFail:
				case ESR_BagFull:
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_GetCardGiftFailed) );
					break;
				}
				break;
			case ER_ZhiZunCardLevelAbout:
				switch( pResult->value )
				{
				case ESR_NotExist:
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_NoZhiZunCard) );
					break;
				default:
					{
						char str[256] = {0};
						if( pResult->value >= 1 && pResult->value <= 6 )
						{
							MeSprintf_s(str, sizeof(str)/sizeof(char) - 1, theXmlString.GetString(eText_ZhiZunCardLevel), theXmlString.GetString(eText_GetZhiZunCard + pResult->value -1));
						}
						else
						{
							char level[16] = {0};
							MeSprintf_s(level, sizeof(level)/sizeof(char) - 1, "%d", pResult->value);
							MeSprintf_s(str, sizeof(str)/sizeof(char) - 1, theXmlString.GetString(eText_ZhiZunCardLevel), level);
						}
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, str );
					}
					break;
				}
				break;
			case ER_ZhiZunVipGiftAbout:
				switch( pResult->value )
				{
				case ESR_NotExist:
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_NoZhiZunVipGift) );
					break;
				case ESR_HaveGet:
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_GotZhiZunVipGift) );
					break;
				case ESR_ResourceFail:
				case ESR_BagFull:
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_GetCardGiftFailed) );
					break;
				}
				break;
			case ER_HuiGuiGiftAbout:
				switch( pResult->value )
				{
				case ESR_NotExist:
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_NoHuiGuiGift) );
					break;
				case ESR_HaveGet:
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_GotHuiGuiGift) );
					break;
				case ESR_ResourceFail:
				case ESR_BagFull:
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_GetCardGiftFailed) );
					break;
				}
				break;
			case ER_ChongZhiGiftAbout:
				switch( pResult->value )
				{
				case ESR_NotExist:
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_NoChongZhiGift) );
					break;
				case ESR_HaveGet:
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_GotChongZhiGift) );
					break;
				case ESR_ResourceFail:
				case ESR_BagFull:
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_GetCardGiftFailed) );
					break;
				}
				break;
			case ER_ChongZhiBackGiftAbout:
				switch( pResult->value )
				{
				case ESR_NotExist:
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_NoChongZhiBackJinDing) );
					break;
				case ESR_HaveGet:
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_GotChongZhiBackJinDing) );
					break;
				case ESR_ResourceFail:
				case ESR_BagFull:
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_GetCardGiftFailed) );
					break;
				}
				break;
			case ER_IsLocked:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString(eText_IsLocked) );
				break;
			case ER_PrivateShopItemError:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_Private, theXmlString.GetString(eText_PrivateShopItemError) );
				break;
			case ER_JiFengGainNotItem:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_GetCardGiftFailed) );
				break;
			case ER_JiFengGainSuccess:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_GetCardGiftSuccess) );
				break;
			case ER_MaleLevelLimit:                  // 男方必须满足%d级才能结婚
				{
					char szWord[128];
					MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_MarryMenTask),pResult->value);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Marry_Failed, szWord );
				}
				break;
			case ER_MaleLevelLimit1:
				{
					char szWord[256] = {0};
					MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_MaleLevelLimit1),pResult->value);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Marry_Failed, szWord );
				}
				break;
			case ER_MaleLevelLimit2:
				{
					char szWord[256] = {0};
					MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_MaleLevelLimit2),pResult->value);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Marry_Failed, szWord );
				}
				break;
			case ER_FemaleLevelLimit:                // 对方必须为女性,且不低于%d级
				{
					char szWord[128];
					MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_MarryMustMen),pResult->value);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Marry_Failed, szWord );
				}
				break;
			case ER_MustHaveTeam:                    // 双方必须在队伍中才能结婚
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Marry_Failed, theXmlString.GetString(eText_MarryTask) );
				break;
			case ER_MustBeTeamHeader:                // 男方必须是队伍的队长
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Marry_Failed, theXmlString.GetString(eText_MarryIsLeader) );
				break;
			case ER_OnlyTwoTeamMember:               // 队伍中只能有双方两个人
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Marry_Failed, theXmlString.GetString(eText_MarryOnlyTwoPeople) );
				break;
			case ER_TargetMustInTeam:                // 双方必须有且仅有好友关系
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Marry_Failed, theXmlString.GetString(eText_MarryInSameTeam) );
				break;
			case ER_SelfAlreadyHaveMarriage:         // 你已经有妻子了
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Marry_Failed, theXmlString.GetString(eText_MarryHasWift) );
				break;
			case ER_OnlyFriend:                      // 双方必须有且仅有好友关系
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Marry_Failed, theXmlString.GetString(eText_MarryMustIsFriend) );
				break;
			case ER_FriendlyLimit:                   // 双方好友度不足%d点
				{
					char szWord[128];
					MeSprintf_s(szWord,sizeof(szWord) / sizeof(char) - 1,theXmlString.GetString(eText_MarryFriendNoEnough),pResult->value);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Marry_Failed, szWord );
				}
				break;
			case ER_MustInArea:                      // 对方必须在你的身边
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Marry_Failed, theXmlString.GetString(eText_MarryInSameSceen) );
				break;
			case ER_TargetAlreadyHaveMarriage:       // 对方已经有丈夫了
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Marry_Failed, theXmlString.GetString(eText_MarryHasHoushand) );
				break;
			case ER_CreateMustBeMarriage:            // 必须是夫妻才能开启婚庆场景
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Marry_Failed, theXmlString.GetString(eText_MarryRelation) );
				break;
			case ER_MarriageStageCountLimit:         // 婚庆场景已经达到最大数
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Marry_Failed, theXmlString.GetString(eText_MarrySceneMax) );
				break;
			case ER_CreateMarriageStageFailed:       // 婚庆场景创建失败, 请重试
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Marry_Failed, theXmlString.GetString(eText_MarrySceneCreateFailed) );
				break;
			case ER_MarriageStageNotExist:           // 婚庆场景尚未开启 或者 已经关闭 
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Marry_Failed, theXmlString.GetString(eText_MarrySceneNoOpen) );
				break;
			case ER_MarriageStageAlreadyExist: //婚庆场景已经开启
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Marry_Failed, theXmlString.GetString(eText_MarrySceneOpen) );
				break;
			case ER_MarriageMustInTeam:  //只有夫妻双方在同一队伍中才能完成任务
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Marry_Failed, theXmlString.GetString(eText_MarrySexInSameTeam) );
				break;
			case ER_IsInOpenPrivateShop:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_BargainFailed_InPrivateShop) );
				break;
			case ER_LeaveGuildTimeLimit:			// 一天只能加入一次公会
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, theXmlString.GetString(eText_AddGuildFailed_TimeLimit) );
				break;
			case ER_AlreadyMaxMasterLevel:			// 已经是最大师门等级了
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, theXmlString.GetString(eText_BeyondTeacherLevel) );
				break;
			case ER_HaveNotGraduateMaster:           // 你还未完成出师任务
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, theXmlString.GetString(eText_NotFinishTeacherTask) );
				break;
			case ER_NotEnoughMasterValue:            // 你的威望值不够
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_NotEnoughWeiWang) );
				break;
			case ER_MustBeMarriageCanFly:            // 只有夫妻关系才能使用此飞行道具
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Marry_Failed, theXmlString.GetString(eText_CanUseWithWifeHusband) );
				break;
			case ER_ItemFlyNotOnline:                // 对方不在线: 使用飞行道具失败 
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString(eText_CannotUseOtherOffline) );
				break;
			case ER_RemoveRelationNeedMoney:         // 删除师徒关系需要%d金钱( 具体金钱在value 中 )
				{
					char szWord[128] = {0};
					int gold = 0, silver = 0,copper = 0;
					thePlayerRole.GetGSCFromMoney(pResult->value,gold,silver,copper);
					MeSprintf_s(szWord,sizeof(szWord) / sizeof(char) - 1,theXmlString.GetString(eText_NotEnoughMoneyLeaveTeacher),gold);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, szWord );
				}
				break;
			case ER_AddStudentMustInArea:            // 拜师收徒必须在%d米范围内
				{
					char szWord[128];
					MeSprintf_s(szWord,sizeof(szWord) / sizeof(char) - 1,theXmlString.GetString(eText_AddTeacherStudentMaxDist1),pResult->value);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, szWord );
				}
				break;
			case ER_StudentMinLevelLimit:            // 徒弟等级不能低于%d级
				{
					char szWord[128];
					MeSprintf_s(szWord,sizeof(szWord) / sizeof(char) - 1,theXmlString.GetString(eText_StudentLevelLimit),pResult->value);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, szWord );
				}
				break;
			case ER_StudentMaxLevelLimit:            // 徒弟等级不能超过%d级
				{
					char szWord[128];
					MeSprintf_s(szWord,sizeof(szWord) / sizeof(char) - 1,theXmlString.GetString(eText_BeyondStudentLevelMax),pResult->value);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, szWord );
				}
				break;
			case ER_StudentMinLevelSpan:             // 师徒等级相差不能低于%d级
				{
					char szWord[128];
					MeSprintf_s(szWord,sizeof(szWord) / sizeof(char) - 1,theXmlString.GetString(eText_TeacherStudentLevelBeyond),pResult->value);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, szWord );
				}
				break;
			case ER_GraduateMasterMustInTeam:        // 师傅必须在队伍中才能出师
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, theXmlString.GetString(eText_TeacherMustInTeam) );
				break;
			case ER_GraduateMasterMustInArea:        // 师傅必须在%d米范围内才能出师
				{
					char szWord[128];
					MeSprintf_s(szWord,sizeof(szWord) / sizeof(char) - 1,theXmlString.GetString(eText_GraduateDistLimit),pResult->value);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, szWord );
				}
				break;
			case ER_UseItemMustInArea:				// 对方必须在%d米范围内才能使用
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Teacher_Belongs, theXmlString.GetString(eText_GivePresentFailed_TooFar) );
				s_CUI_ID_FRAME_GivePresent.OnFailed();
				break;
			case ER_UseItemOnlyFriend:				// 双方都是好友才可使用物品
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, theXmlString.GetString(eText_GivePresentFailed_ShouldBeFriend) );
				s_CUI_ID_FRAME_GivePresent.OnFailed();
				break;
			case ER_UseItemToFriendTimeLimit:		// 一个好友一天只能赠送一次好友度
				{
					char szWord[256] = {0};
					MeSprintf_s(szWord,sizeof(szWord) / sizeof(char) - 1,theXmlString.GetString(eText_GivePresentFailed_TimeLimit),pResult->value);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, szWord );
					s_CUI_ID_FRAME_GivePresent.OnFailed();
				}
				break;
			case ER_UseItemToFriendCountLimit:		// 一天只能给%d好友赠送好友度
				{
					char szWord[256] = {0};
					MeSprintf_s(szWord,sizeof(szWord) / sizeof(char) - 1,theXmlString.GetString(eText_GivePresentFailed_CountLimit),pResult->value);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, szWord );
					s_CUI_ID_FRAME_GivePresent.OnFailed();
				}
				break;
			case ER_ReceiveFriendlyQuestMustHaveTeam:	// 必须组队才能接好友度任务
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, theXmlString.GetString(eText_ReceiveFriendlyQuestMustHaveTeam) );
				break;
			case ER_ReceiveFriendlyQuestOnlyTwoMember:	// 队伍中只能有2个人才能接好友度任务
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, theXmlString.GetString(eText_ReceiveFriendlyQuestOnlyTwoMember) );
				break;
			case ER_ReceiveFriendlyQuestMustFriend:		// 队伍中的成员必须是好友才能接好友度任务
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, theXmlString.GetString(eText_ReceiveFriendlyQuestMustFriend) );
				break;
			case ER_ReceiveFriendlyCountLimit:			// 同一个好友一天只能接一次好友度任务
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Friend_Belongs, theXmlString.GetString(eText_ReceiveFriendlyCountLimit) );
				break;
			case ER_WaitNextTeamBattle:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, theXmlString.GetString(eText_TeamBattleWaitWorning) );
				break;
			case ER_LevelErrorEnterTeamBattle:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, theXmlString.GetString(eText_TeamBattleLevelWorning) );
				break;
			case ER_PrivateChatLevelLimit:
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Chat_ChannelTip, theXmlString.GetString(eWarning_CanNotPrivateChatToBefore15) );
				break;
            case ER_CannotChangePKMode:         // PK值大于0,无法切换到其他模式
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PKMode_Change, theXmlString.GetString( eText_PKMode_NoChange ) );
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseInfo_RandomTip, theXmlString.GetString( eText_PKMode_NoChange ) );
				break;
            case ER_ChangePKModeOften:          // 3分钟CD才能切换PK模式
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PKMode_Change, theXmlString.GetString( eText_PKMode_TimeLimit ) );
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseInfo_RandomTip, theXmlString.GetString( eText_PKMode_TimeLimit ) );
				break;
            case ER_PKModeCriticalNoTimer:      // 狂暴模式30分钟时限未到
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PKMode_Change, theXmlString.GetString( eText_PKMode_FuryTimeLimit ) );
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseInfo_RandomTip, theXmlString.GetString( eText_PKMode_FuryTimeLimit ) );
				break;
            case ER_NoExpToLevelUp:             // 经验不够，无法升级 
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_ToLearn, theXmlString.GetString( eText_LevelUp_ExpNotEnough ) );
                break;
            case ER_NoLevelToLearnSkill:        // 等级不足无法学习技能 
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_ToLearn, theXmlString.GetString( eText_LearnSkill_LevelNotEnough ) );
                break;
            case ER_NoMoneyToLearnSkill:        // 金钱不足无法学习技能 
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_ToLearn, theXmlString.GetString( eText_LearnSkill_GoldNotEnough ) );
                break;
            case ER_NoExpToLearnSkill:          // 经验不足无法学习技能 
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_ToLearn, theXmlString.GetString( eText_LearnSkill_ExpNotEnough ) );
                break;
            case ER_NoMoneyToMountRestore:           // 金钱不足无法治疗坐骑
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_MountRestore_NoMoney ) );
                break;
            case ER_ErrorMountMasterLevel:           // 坐骑繁殖主坐骑等级小于60级
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_MountBreed_MasterLevel ) );
                break;
            case ER_ErrorMountMasterMoney:           // 坐骑繁殖金钱不足
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_MountBreed_NoMoney ) );
                break;
            case ER_ErrorMountCannotBreed:           // 坐骑无法进行繁殖
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_MountBreed_Unable ) );
                break;
            case ER_ErrorMountNoNextId:              // 无法进行坐骑繁殖，主坐骑没有下一代马
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_MountBreed_NoNext ) );
                break;
            case ER_ErrorMountSkillNumber:           // 已经开启技能槽
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_MountSkill_SlotAlreadyOpen ) );
                break;
            case ER_ErrorMountSkillForget:           // 所在位置没有技能
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_MountSkill_SlotNoSkill ) );
                break;
            case ER_NoPointToLearnSkill:             // 熟练度不足无法提高生活技能
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_ToLearn, theXmlString.GetString( eText_BizSkill_NotEnoughExp ) );
                break;
            case ER_CanLearnMoreRecipeSkill:         // 生活技能已满
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_ToLearn, theXmlString.GetString( eText_BizSkill_AlreadyFull ) );
                break;
            case ER_MountLevelIsOverPlayer5:         // 坐骑等级高于人物等级5级，无法增加经验
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_MountLevel_OverPlayer ) );
                break;
            case ER_HookLevelNotHas:                 // 挂机档次错误
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_HookOffline_Failed, theXmlString.GetString( eText_Hook_NotHasLevel ) );
                break;
            case ER_NoMoneyGetHookExp:               // 金钱不足无法领取经验
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Platform_Belongs, theXmlString.GetString( eText_Hook_NoMoneyToGetExp ) );
                break;
            case ER_MountLevelCannotUseItem:         // 坐骑等级不足无法使用道具
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_UseItem_NotEnoughMountLevel ) );
                break;
            case ER_ErrorMountHuanTongShuLevel:     // 坐骑携带等级小于40级无法使用还童书
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_MountLevel_HuanTongShu ) );
                break;
            case ER_ErrorMountHuanLongShuLevel:     // 坐骑携带等级小于80级无法使用还龙书
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_MountLevel_HuanLongShu ) );
                break;
            case ER_MountCannotUseHuanLongShu:      // 该坐骑无法使用还龙书
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_Mount_CantUseHuanLongShu ) );
                break;
            case ER_EquipPressKeySuit:              // 没有该一键换装的设置
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_EquipChange_Failed, theXmlString.GetString( eText_OneKeySuit_NoSet ) );
                break;
            case ER_HonourTopLimit:                 // 今日荣誉值达到上限
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Honor_Error, theXmlString.GetString( eText_Honour_TopLimit ) );
                break;
            case ER_NoOfflineHookExp:               // 没有离线挂机经验
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_HookOffline_Failed, theXmlString.GetString( eText_NoOffline_HookExp ) );
                break;
            case ER_OfflineHookLevel:               // 离线挂机等级不足
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_HookOffline_Failed, theXmlString.GetString( eText_OfflineHook_LevelLess ) );
                break;
            case ER_NoMoneyReliveOrigin:            // 金钱不足无法原地复活
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Relive_Belongs, theXmlString.GetString( eText_ReliveOrigin_NoMoney ) );
                break;
            case ER_MountTypeCannotBreed:           // 坐骑类型不同无法进行繁殖
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_MountType_CannotBreed ) );
                break;
            case ER_ActiveMountStorage:              // 出战坐骑无法放入仓库
                {
                    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip,
                        theXmlString.GetString( eText_Mount_ActivedNotAdmit ) );
                }
                break;
            case ER_GetStorageMountFail:             // 仓库坐骑无法放入坐骑栏中
                {
                    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip,
                        theXmlString.GetString( eText_Mount_StorageToCharErr ) );
                }
                break;
            case ER_ReelMountTakeLevel:              // 坐骑携带等级不足 无法学习技能
                {
                    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip,
                        theXmlString.GetString( eText_Mount_LearnSkill_CarryLvlLess ) );
                }
                break;
            case ER_ReelMountLevel:                  // 坐骑等级不足 无法学习技能
                {
                    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip,
                        theXmlString.GetString( eText_Mount_LearnSkill_LvlLess ) );
                }
                break;
            case ER_ReelMountPreSkill:               // 无法学习坐骑技能
                {
                    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip,
                        theXmlString.GetString( eText_Mount_LearnSkill_Failed ) );
                }
                break;
			case ER_CatchSkillLevel:
				// 宠物捕捉技能等级不足
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_CatchSkillLevel) );
				}
				break;
			case ER_PetIdentify:
				// 没有宠物图鉴无法捕捉
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetIdentify) );
				}
				break;
			case ER_CallNpcScriptFailDistance:
				{
					s_CUI_NpcTaskDialogBox.SetFinishUI(true);
					s_CUI_NpcTaskDialogBox.SetVisable(false);
					s_CUI_NpcTaskDialogBox.SetFinishUI(false);
					s_CUI_NpcTaskDialogBox.CloseDialog(false);
				}
				break;
			case ER_ProfessionToLearnXinFa:          // 职业不对无法学习心法
				{
					std::string str;
					str = theXmlString.GetString(eText_LearnXinFa_ProfessionNotOk);
					str += theXmlString.GetString(eText_LearnXinFa_Failure);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_ToLearn, str.c_str());
				}
				break;
			case ER_NoLevelToLearnXinFa:            // 等级不足无法学习心法
				{
					std::string str;
					str = theXmlString.GetString(eText_LearnXinFa_LevelNotEnough );
					str += theXmlString.GetString(eText_LearnXinFa_Failure);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_ToLearn, str.c_str());
				}
				break;
			case ER_NoMoneyToLearnXinFa:             // 金钱不足无法学习心法
				{
					std::string str;
					str = theXmlString.GetString(eText_LearnXinFa_GoldNotEnough);
					str += theXmlString.GetString(eText_LearnXinFa_Failure);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_ToLearn, str.c_str());
				}
				break;
			case ER_NoExpToLearnXinFa:               // 经验不足无法学习心法
				{
					std::string str;
					str = theXmlString.GetString(eText_LearnXinFa_ExpNotEnough);
					str += theXmlString.GetString(eText_LearnXinFa_Failure);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_ToLearn, str.c_str());
				}
				break;
			case ER_NoPrevXinFa:                     // 不能越阶学习心法
				{
					std::string str;
					str = theXmlString.GetString(eText_LearnXinFa_PreXinFaNotOk);
					str += theXmlString.GetString(eText_LearnXinFa_Failure);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_ToLearn, str.c_str());
				}
				break;
			case ER_LearnXinFa:                     // 您不能学习这本心法书
				{
					std::string str;
					str = theXmlString.GetString(eText_LearnXinFa_Failure);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Skill_ToLearn, str.c_str());
				}
				break;
			case ER_NoFoundQuestItem:                // 没有找到任务物品
				{
					char szInfo[128];
					MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_NoTaskItem) );
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Info_ChatSys, szInfo );
				}
				break;
			case ER_QuestItemCommit:                 // 提交任务物品不足
				{
					char szInfo[128];
					MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_NotEnoughTaskItem) );
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Info_ChatSys, szInfo );
				}
				break;
			case ER_NotFoundPet:                     // 没有找到宠物数据
				{
					char szInfo[128];
					MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_PetNoData) );
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, szInfo );
				}
				break;
			case ER_PetPotential:                    // 宠物潜力点分配错误
				{
					char szInfo[128];
					MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_PetPointError) );
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, szInfo );
				}
				break;
			case ER_PetNumIsFull:                    // 携带宠物已满
				{
					char szInfo[128];
					MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_PetEnough) );
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, szInfo );
				}
				break;
			case ER_PetTakeLevel:                    // 携带等级不足
				{
					char szInfo[128];
					MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_PetLessTakeLevel), pResult->value);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, szInfo );
				}
				break;
			case ER_InFightNotActivePet:             // 战斗状态宠物无法出战
				{
					char szInfo[128];
					MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_PetNoFight) );
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, szInfo );
				}
				break;
			case ER_InDeadNotActivePet:              // 死亡状态宠物无法出战
				{
					char szInfo[128];
					MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_PetDead) );
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, szInfo );
				}
				break;
			case ER_LifeNotActivePet:               // 寿命不足宠物无法出战
				{
					char szInfo[128];
					MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_PetNoLife) );
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, szInfo );
				}
				break;
			case ER_LoyaltyNotActivePet:            // 快乐度不足宠物无法出战 
				{
					char szInfo[128];
					MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_PetNoHappy) );
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, szInfo );
				}
				break;
			case ER_PetRegenerateTime:               // 重生时间还未到
				{
					char szInfo[128];
					MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_PetNoReLife),(int)pResult->value );
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, szInfo );
				}
				break;
            case ER_PetHasBreed:                     // 繁殖过的宠物无法还童
				{
					char szInfo[128];
					MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_PetReturnLife) );
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, szInfo );
				}
				break;
			case ER_PetIsAberrance:                  // 变异宠物无法还童
				{
					char szInfo[128];
					MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_PetNoReturnLife) );
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, szInfo );
				}
				break;
			case ER_PetLearnSkill:                   // 宠物技能学习失败
				{
					char szInfo[128];
					MeSprintf_s( szInfo,sizeof(szInfo)/sizeof(char) - 1, theXmlString.GetString(eText_PetFailLearnSkill) );
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, szInfo );
				}
				break;
			case ER_PetCatchFail:
				// 捕捉宠物失败
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetCatchFail) );
				}
				break;
			case ER_HasPetSkill:
				{// 宠物已经学习了该技能
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_HasPetSkill) );
				}
				break;
			case ER_PetSkillGroupLevel:
				{// 宠物已经学习高级技能
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, theXmlString.GetString(eText_PetSkillGroupLevel) );
				}
				break;
			case ER_PetSavvyReduce:
				//宠物不小心悟性降低到了%d
				{
					char temp[64];
					MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eText_PetSavvyReduce),pResult->value);
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo, temp);
				}
				break;
			case ER_MountMaxRangeTimer:
				{
					char szInfo[128] = {0};
					MeSprintf_s(szInfo,sizeof(szInfo),theXmlString.GetString(eText_CarryTimeLimit)/*超出最大活动范围,%d秒后离开载具*/,pResult->value);
					CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_PetInfo,szInfo);
				}
				break;
			case ER_MountBackMaxRange:
				{
					char szInfo[128] = {0};
					MeSprintf_s(szInfo,sizeof(szInfo),"%s",theXmlString.GetString(eText_CarryGetBack)/*您回到了活动范围内*/);
					CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_PetInfo,szInfo);
				}
				break;
			case ER_HasRideMultiMount:
				{
					CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString(eText_OnMultiMount) ); 
				}
				break;

			case ER_NameNotExist: // 玩家名字不存在
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Guild_PlayerOffline ) );
				}
				break;
			case ER_ChangePKModeAttact:          //
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PKMode_Change, theXmlString.GetString( eText_PKModeAttact ) );
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_RiseInfo_RandomTip, theXmlString.GetString( eText_PKModeAttact ) );
				break;
			default:
				break;
			}
		}
		break;
	case MSG_SERVERSHUTDOWN://服务器关闭提示
		{
			theHeroGame.OnMsgServerShutdown(pMsg);
		}
		break;
	default:
		{
			if (  InGameMsg( pMsg ) == false )//游戏中消息处理
			{
				HookClientLogMsg("end error: %d\n", pMsg->GetType() );
				return;
			}
		}
		break;
	}
}

bool CMessageProcess::InGameMsg(Msg* pMsg)
{
	guardfunc;

	DWORD dwType = pMsg->GetType();

	CPlayerMgr* playerMgr = theHeroGame.GetPlayerMgr();

	switch(dwType)
	{
	case MSG_CITYINFO:
		playerMgr->OnMsgCityInfo( pMsg );
		break;
	case MSG_PLAYERNAME_CHANGED:
		playerMgr->OnMsgPlayerNameChanged( pMsg );
		break;
	case MSG_TEAM_PLAYERINFO:
		playerMgr->OnMsgTeamPlayerInfo( pMsg );
		break;
	case MSG_BUILDING_SELFDESTROYED:
		playerMgr->OnMsgBuildSelfDestroyed( pMsg );
		break;
	case MSG_BUILDING_BUILDFAILED:
		playerMgr->OnMsgBuildFailed( pMsg );
		break;
	case MSG_BUILDING_DESTROYED:
		playerMgr->OnMsgBuildDestroyed( pMsg );
		break;
	case MSG_BUILDING_BUILDSTATUS:
		playerMgr->OnMsgBuildStatus( pMsg );
		break;
	case MSG_BUILDINGENTERMYSIGHT:
		playerMgr->OnMsgBuildingEnterMySight( pMsg );
		break;
	case MSG_NPC_ENTERMYSIGHT:
		playerMgr->OnMsgNPCEnterMySight(pMsg);
		break;
	case MSG_NPC_ENTERMYSIGHTMOVINGASTEP:
		playerMgr->OnMsgNPCEnterMySightMovingAStep(pMsg);
		break;
	case MSG_PLAYER_ENTERMYSIGHT:
		playerMgr->OnMsgPlayerEnterMySight(pMsg);
		break;
	case MSG_PLAYER_ENTERMYSIGHTMOVINGASTEP:
		playerMgr->OnMsgPlayerEnterMySightMovingAStep(pMsg);
		break;
	case MSG_ENTERMYSIGHTPACK:
		playerMgr->OnMsgPlayerEnterMySightPack(pMsg);
		break;
	case MSG_ACKENTERWORLDPACK:
		playerMgr->OnMsgEnterWorld(pMsg);
		break;
	case MSG_ITEMENTERMYSIGHT:
		playerMgr->OnMsgItemEnterMySight(pMsg);
		break;
	case MSG_EXITMYSIGHT:
		playerMgr->OnMsgExitMySight(pMsg);
		break;
	case MSG_ACKCHARINFO:
		playerMgr->OnMsgAckCharInfo( pMsg );
		break;
 	case MSG_EXIT:
		playerMgr->OnMsgExit(pMsg);
		break;
	case MSG_CHANGEMAP:
		{
			playerMgr->OnMsgChangeMap(pMsg);
			return false;
		}
		break;
	case MSG_CHAT:
		playerMgr->OnMsgChat(pMsg);
		break;
	case MSG_GETLAG:
		playerMgr->OnMsgGetLag(pMsg);
		break;
	case MSG_SEECHARLEVELUP:
		playerMgr->OnMsgCharLevelUp(pMsg);
		break;
	case MSG_SHOWEFF:
		playerMgr->OnMsgCharShowEff(pMsg);
		break;
	case MSG_REFRESHCHAR:
		playerMgr->OnMsgRefreshChar(pMsg);
		break;
	case MSG_ACKDROPITEM:
		playerMgr->OnMsgAckDropItem2(pMsg);
		break;
	case MSG_GETITEM:
		playerMgr->OnMsgGetItem2(pMsg);
		break;
	case MSG_MONEYCHANGE:
		playerMgr->OnMsgMoneyChange(pMsg);
		break;
	case MSG_ACKEQUIP:
		playerMgr->OnMsgEquip( pMsg );
		break;
	case MSG_EQUIPCHANGED:
		playerMgr->OnMsgEquipChanged2(pMsg);
		break;
	case MSG_MOVEASTEP:
		playerMgr->OnMsgMoveAStep(pMsg);
		break;
	case MSG_PERMITMOVE:
		playerMgr->OnMsgPermitMove(pMsg);
		break;
	case MSG_VERIFYPOS:
		playerMgr->OnMsgVerifyPos(pMsg);
		break;
	case MSG_SYNCPOS: //坐标同步
		playerMgr->OnMsgSyncPos(pMsg);
		break;
	case MSG_REMOVEITEM:
		playerMgr->OnMsgRemoveItem(pMsg);
		break;
	case MSG_UPDATECHARABAG:
		playerMgr->OnMsgUpdateBag(pMsg);
		break;
	case MSG_UPDATESHORTCUTBAG:
		playerMgr->OnMsgUpdateShortCutBag(pMsg);
		break;
	case MSG_UPDATEVISUALEQUIP:
		playerMgr->OnMsgUpdateVisualEquip(pMsg);
		break;
	case MSG_UPDATEFIGHTDATA:
		playerMgr->OnMsgUpdateEquipData(pMsg);
		break;
	case MSG_ACKGETSHOP:
		playerMgr->OnMsgGetShop(pMsg);
		break;
	case MSG_ACKBUYORSELLGOODS:
		playerMgr->OnAckMsgBuyOrSellGoods(pMsg);
		break;
	case MSG_CHARATTRCHANGE:
		playerMgr->OnMsgAttrChanged(pMsg);
		break;
	case MSG_ACK_UP_ATTR_LEVEL:
		playerMgr->OnMsgAttrLevelUp(pMsg);
		break;
	case MSG_ACK_PLACESTONE:
		playerMgr->OnMsgPlaceStone(pMsg);
		break;
	case MSG_ACK_REMOVESTONE:
		playerMgr->OnMsgRemoveStone(pMsg);
		break;
	case MSG_ACK_PLACESUBSKILL:
		playerMgr->OnMsgPlaceSubSkill(pMsg);
		break;
	case MSG_ACK_REMOVESUBSKILL:
		playerMgr->OnMsgRemoveSubSkill(pMsg);
		break;
	case MSG_ACK_PRODUCEITEM:
		playerMgr->OnMsgProduceItem(pMsg);
		break;
	case MSG_EFFECTENTERMYSIGHT:
		playerMgr->OnMsgEffectEnterMySight( pMsg );
		break;
	case MSG_DAMAGEOFEFFECT:
		playerMgr->OnMsgDamageOfEffect( pMsg );
		break;
	case MSG_SEEDAMAGE:
		playerMgr->OnMsgSeeDamage(pMsg);
		break;
	case MSG_SEEATTACK3:
		playerMgr->OnMsgSeeAttack( pMsg );
		break;
	case MSG_INTONATE:
		playerMgr->OnMsgSeeIntonate(pMsg);
		break;
	//   added 2004.08.20
	case MSG_INTONATESTART:
		playerMgr->OnMsgIntonateStart(pMsg);
		break;
	case MSG_INTONATEEND:
		playerMgr->OnMsgIntonateEnd(pMsg);
		break;
	case MSG_SKILLCANCELD:
		playerMgr->OnMsgSkillCanceled(pMsg);
		break;
	case MSG_HOLDSKILLEND:
		playerMgr->OnMsgHoldSkillEnd(pMsg);
		break;
	case MSG_SKILLSTATUS:
		playerMgr->OnMsgSkillStatus(pMsg);
		break;
	case MSG_ACKEXPRESSION:
		playerMgr->OnMsgSeeExpression(pMsg);
		break;
	case MSG_ACKQUERYATT2:
		playerMgr->OnMsgAckAttack3(pMsg);
		break;
	case MSG_MAPLOADED:
		playerMgr->OnMsgMapLoaded( pMsg );
		break;
	case MSG_ACKHPINFO:
		playerMgr->OnMsgAckHPInfo( pMsg );
		break;
	case MSG_AGREEUSESPECIALSKILL:
		playerMgr->OnMsgAgreeUseSpecialSkill();
		break;
	case MSG_AGREEREADYTOUSESPECIALSKILL:
		playerMgr->OnMsgAgreeReadytoUseSpecialSkill( pMsg );
		break;
	case MSG_ADDMISSIONINTRO:
		playerMgr->OnMsgAddMissionIntro( pMsg );
		break;
	case MSG_DELMISSIONINTRO:
		playerMgr->OnMsgDelMissionIntro( pMsg );
		break;
	case MSG_SEEACTION:
		playerMgr->OnMsgSeeAction( pMsg );
		break;
	case MSG_SCRIPTSHOW:
		playerMgr->OnMsgScriptShow( pMsg );
		break;
	case MSG_ACKGETPLAYERINFO:
		playerMgr->OnMsgAckGetPlayerInfo( pMsg );
		break;
	case MSG_ACKFRIENDLEAVE:
		playerMgr->OnMsgAckFriendLeave(pMsg);
		break;
	case MSG_PING:
		playerMgr->OnMsgPing(pMsg);
		break;
	case MSG_ACK_SWITCHSITSTATUS:
		playerMgr->OnMsgSitStatusChange(pMsg);
		break;
	case MSG_ACK_SWITCHFIGHTSTATUS:
		playerMgr->OnMsgFightStatusChange(pMsg);
		break;
	case MSG_ACKCREATETEAM://队伍建立的消息..队伍建立的情况
		playerMgr->OnMsgCreateTeam(pMsg);
		break;
	case MSG_ACKJOINTEAM:	//服务器发过来的消息有人加入队伍。。加入是否成功
		playerMgr->OnMsgJoinTeam(pMsg);
		break;
	case MSG_TEAMOUTLINE:		//队员下线了
		playerMgr->OnMsgTeamOutLine(pMsg);
		break;
	case MSG_TEAMINFO:		//取得队伍的信息
		playerMgr->OnMsgTeamInfo(pMsg);
		break;
	case MSG_INQUIRETEAMHEADER:
		playerMgr->OnMsgInquireTeamHeader(pMsg);
		break;
	case MSG_INQUIREINVITEE:
		//modified by zhuomeng.hu		[9/13/2010]
		s_CUI_ID_FRAME_InfoTips.AddTeamInviteTip( pMsg );
		//playerMgr->OnMsgInquireInvitee(pMsg);
		break;
	case MSG_ADDTEAMMEMBER://增加一个队友。。和该队友的信息
		playerMgr->OnMsgAddTeamMember(pMsg);
		break;
	case MSG_DELETETEAMMEMBER://删除一队友
		playerMgr->OnMsgDeleteAMember(pMsg);
		break;
	case MSG_CHANGEMANIPLEFROMTEAM:
		playerMgr->OnChangeManipleFromTeamRet( pMsg );
		break;
	case MSG_EXITTEAM:	//离开队伍的消息
		playerMgr->OnMsgExitTeam(pMsg);
		break;
	case MSG_REQ_ASSIGN_TEAM: //队伍飞配模式2级以上物品提示索取或者放弃
		playerMgr->OnMsgAssign_Item_Team( pMsg );
		break;
	case MSG_FOLLOWTEAMMEMBER:
		s_CUI_ID_FRAME_Team.OnMsgTeamFollowTo(pMsg);
		break;
	case MSG_TEAMMEMBERACK:
		playerMgr->OnMsgTeamMemberAck(pMsg);
		break;
	case MSG_HEADERCANCELTEAMFOLLOW:
		s_CUI_ID_FRAME_Team.OnMsgHeaderCancelTeamFollow(pMsg);
		break;
	case MSG_CANCELTEAMFOLLOW://lyh++ 设置队伍跟随目标位-1
		s_CUI_ID_FRAME_Team.SetTeamFollowID(-1);
		break;
	case MSG_MEMBERCOUNTINTEAMFOLLOW:
		s_CUI_ID_FRAME_Team.OnMsgMemberCountInTeamFollow(pMsg);
		break;
	case MSG_REQTEAMFOLLOW:
		s_CUI_ID_FRAME_Team.OnMsgAskTeamFollow(pMsg);
		break;
	case MSG_BUFFSUPDATE:	
		playerMgr->OnMsgUpdateCharacterBodyStatus(pMsg);
		break;
	case MSG_BUFFSCHANGED:
		playerMgr->OnMsgClearBodyStatus(pMsg);
		break;
	case MSG_CHANGEDIR:
		playerMgr->OnMsgChangeDir(pMsg);
		break;
	case MSG_SKILL_BEGINCOLDDOWN:
		playerMgr->OnSkillBeginCoolDown( pMsg );
		break;
	case MSG_CHANGE_SKILL:
		playerMgr->OnMsgAddSkill( pMsg );
		break;
	case MSG_TELL_EXPLOIT:
		playerMgr->OnMsgTellExploit( pMsg );
		break;
	case MSG_EXPLOIT_CHANGE:
		playerMgr->OnMsgExploitChange( pMsg );
		break;
	case MSG_TELL_OFFICIALLEVEL:
		playerMgr->OnMsgTellOfficialLevel( pMsg );
		break;
	case MSG_TEACHSKILL:
		playerMgr->OnMsgTeachSkill( pMsg );
		break;
	case MSG_CHANGE_PKRECORD:
		playerMgr->OnMsgChangePKRecord( pMsg );
		break;
	case MSG_ALLNPCONTHEMAP:
		playerMgr->OnMsgGetAllNpcOnTheMap( pMsg );
		break;
	case MSG_TELLMAP_NPCQUEST:
		playerMgr->OnMsgTellMapNpcQuest( pMsg );
		break;
	case MSG_TELL_CHAR_VAR:
		playerMgr->OnMsgTellCharVars( pMsg );
		break;
	case MSG_ACK_COMPOUND:
		{
			GetBillBoard()->SetTipCounts(FRIST_COMPOUND);		//sbw		FRIST_COMPOUND
			playerMgr->OnMsgAckCompound( pMsg );
		}
		break;
	case MSG_ACKDISPLAYNAME:
		playerMgr->OnMsgAckDisplayName(pMsg);
		break;
	case MSG_SCRIPT_PLAYERMUSIC:
		playerMgr->OnMsgPlayMusic( pMsg );
		break;
	case MSG_SCRIPT_MAKEITEM:
		playerMgr->OnMsgScriptMakeItem( pMsg );
		break;
	case MSG_SCRIPT_REQ_SHOW_QUEST_DLG:
		playerMgr->OnMsgScriptQuestDlg( pMsg );
		break;
	///////////////////////////////////////////////////
	case MSG_TELLREPUTATION:
		playerMgr->OnMsgTellReputation( pMsg );
		break;
	case MSG_REQYUANBAOCNT:
		playerMgr->OnMsgReqYuanBaoCnt( pMsg );
		break;
	case MSG_RET_RESETTIME:
		playerMgr->OnRetResetTime( pMsg );
		break;
	case MSG_RET_CHANGESUBACTION:
		playerMgr->OnMsgChangeSubAction(pMsg);
		break;
	case MSG_CLOSEITEMFORMIDX:
		playerMgr->OnMsgCloseItemFormIdx( pMsg );
		break;
	case MSG_RETFLAGHEADERFROMTEAM:
		playerMgr->OnRetFlagHeaderFromTeam( pMsg );
		break;
	case MSG_ACK_QUEST_INFO:
		playerMgr->OnMsgAckQuestInfo( pMsg );
		break;
	case MSG_POPMAPNPCLIST:
		playerMgr->OnMsgPopMapNpcList( pMsg );
		break;
	case MSG_PROFESSIONCHANGE:
		playerMgr->OnMsgProfessionChangInfo(pMsg);
		break;
	case MSG_ADDRELATIONACK://添加关系
		thePlayerRole.OnA2CAddFriend(pMsg);
		break;
	case MSG_DELETERELATIONACK://删除关系
		thePlayerRole.OnA2CDelFriend(pMsg);
		break;
	case MSG_RELATIONATTRIBUTE://分组列表
		thePlayerRole.OnA2CRelationAttribute(pMsg);
		break;
	case MSG_RELATIONLIST://好友列表
		thePlayerRole.OnA2CGetFriendList(pMsg);
		break;
	case MSG_TELLRELATIONGROUP://服务器同步分组信息给客户端
		thePlayerRole.OnA2CTellRelationGroup(pMsg);
		break;
	case MSG_RELATIONGROUPCHANGEACK://服务器回应好友分组
		thePlayerRole.OnA2CRelationGroupChange(pMsg);
		break;
	case MSG_FRIENDONLINE:	//好友上线
		thePlayerRole.OnA2CFriendOnline(pMsg);
		break;
	case MSG_FRIENDOUTLINE://好友下线
		thePlayerRole.OnA2CFriendOutline(pMsg);
		break;
	case MSG_UPDATERELATIONACK:	//更新好友信息
		thePlayerRole.OnA2CUpdateFriendInfo(pMsg);
		break;
	case MSG_RELATIONLOCKSTATUS:	//通知锁定状态
		thePlayerRole.OnA2CUpdateLockInfo(pMsg);
		break;
	case MSG_INVITERELATIONREQ:
		thePlayerRole.OnInviteAddRelation(pMsg);
		break;
	case MSG_UPDATEFRIENDLY:
		thePlayerRole.OnUpdateFriendly(pMsg);
		break;
	case MSG_TELLADDREALTION:	//更新好友信息
		//modified by zhuomeng.hu		[9/13/2010]
		s_CUI_ID_FRAME_InfoTips.AddFriendInviteTip( pMsg );
		break;
	case MSG_QUERYATTRIBUTERESULT:	//返回查找好友消息
		s_CUI_ID_FRAME_Search.OnSearchResult( pMsg );
		break;	
	case MSG_REGISTERRELATIONLIST:	//返回师徒信息
		s_CUI_ID_FRAME_SearchTeacher.OnShowSearchResult( pMsg );
		break;	
		//-------------------------------------------------
	case MSG_ACKINQUIREINVITEE:
		playerMgr->OnMsgAddTeamCancel(pMsg);
		break;
	case MSG_ACK_CHANGE_ASSIGNMODE:
		playerMgr->OnMsgChange_AssignMode(pMsg);
		break;
	case MSG_ACK_CHANGE_ASSIGNMODE_RESULT:
		playerMgr->OnMsgChange_AssignMode_Result(pMsg);
		break;
	case MSG_CHANGE_FIGHTSTATE:
		playerMgr->OnMsgChangeFightState(pMsg);
		break;
	case MSG_SHOWTEXT:
		playerMgr->OnShowText( pMsg );
		break;
	case MSG_UPDATEBANK:
		playerMgr->OnShowBank( pMsg );
		break;
	case MSG_UPDATESTORAGE:
		playerMgr->SetStorage( pMsg );
		break;
	case MSG_NPCPLAYANIM:
		playerMgr->OnMsgNpcPlayAnim( pMsg );
		break;
	case MSG_CHARSKILLLEVELUP:
		playerMgr->OnMsgCharSkillLevelUp(pMsg);
		break;
	case MSG_CHANGEDROME:
		playerMgr->OnMsgChangeDrome(pMsg);
		break;
	case MSG_JUMP:
		playerMgr->OnMsgRecevingJump(pMsg);
		break;
	case MSG_DRAWWEAPON:
		playerMgr->OnMsgRecevingDrawWeapon(pMsg);
		break;
	case MSG_DRAWINWEAPON:
		playerMgr->OnMsgRecevingDrawInWeapon(pMsg);
		break;
	case MSG_USESKILLHINTMESSAGE:
		playerMgr->OnMsgUseSkillHintMessage(pMsg);
		break;
	case MSG_SAWSOMEONEDEAD:
		playerMgr->OnMsgSawPlayerDead(pMsg);
		break;
	case MSG_PLAYERMOVINGPOS:
		playerMgr->OnMsgPlayerMovingPos(pMsg);
		break;
	case MSG_PLAYERMOVINGPOSANDDIR:
		playerMgr->OnMsgPlayerMovingPosAndDir(pMsg);
		break;
	case MSG_PLAYERPOS:
		playerMgr->OnMsgPlayerPos(pMsg);
		break;
	case MSG_PLAYERDIR:
		playerMgr->OnMsgPlayerDir(pMsg);
		break;
	case MSG_PLAYERPOSANDDIR:
		playerMgr->OnMsgPlayerPosAndDir(pMsg);
		break;
	case MSG_POSCHANGE:
		playerMgr->OnMsgPosChange(pMsg);
		break;
	case MSG_HITCHMOVETARGETPOS:
		playerMgr->OnMsgHitchMoveTargetPos(pMsg);
		break;
	case MSG_CANCONTROLMOVING:
		playerMgr->OnMsgCanControlMoving(pMsg);
		break;
	case MSG_INTONATEINTERRUPT:
		playerMgr->OnMsgIntonateInterrupt(pMsg);
		break;
	case MSG_SCRIPT_SETHOTKEY:
		playerMgr->OnMsgScriptSetHotkey(pMsg);
		break;
	case MSG_CHANGEQUIPHP:
		playerMgr->OnMsgChangEquipHp(pMsg);
		break;
	case MSG_PLAYERVERIFYPOS:
		playerMgr->OnMsgPlayerVerifyPos(pMsg);
		break;
	case MSG_UNPLAYERVERIFYPOS:
		playerMgr->OnMsgUnPlayerVerifyPos(pMsg);
		break;
	case MSG_UNPLAYERMOVINGTOPOS:
		playerMgr->OnMsgUnPlayerMovingToPos(pMsg);
		break;
	case MSG_UNPLAYERCLOSINGTOLOCKTARGET:
		playerMgr->OnMsgUnPlayerClosingToLockTarget(pMsg);
		break;
	case MSG_UPDATETIME:
		playerMgr->OnMsgUpdateTime(pMsg);
		break;
	case MSG_INTENSIFYEQUIP:
		playerMgr->OnMsgIntensifyEquip(pMsg);
		break;
	case MSG_ITEMCOMPOSEGEMACK:
		playerMgr->OnMsgIITEMCOMPOSEGEM(pMsg);
		break;
	case MSG_EQUIPMAINTAINACK:
		playerMgr->OnMsgEquipMaintainAck(pMsg);
		break;
	case MSG_ITEMRECLAIMACK:
		playerMgr->OnMsgItemReclaim(pMsg);
		break;
	case MSG_MOVEGOODSREQ:
		playerMgr->OnMsgRemoveSomething( pMsg);
		break;
	case MSG_USEGOODS:
		playerMgr->OnMsgUseGood(pMsg);
		break;
	case MSG_REPAIRITEMSERVERTOCLIENT:
		playerMgr->OnMsgRepairItemByServer(pMsg);
		break;
	case MSG_ACK_BANKTRADE:
		playerMgr->OnMsgOperateBank(pMsg);
		break;
	case MSG_CASTINEFFICACYSKILL:
		playerMgr->OnMsgSeeCastInefficacySkill(pMsg);
		break;
	case MSG_SHOWLEVELINFO:
		playerMgr->OnMsgShowLevelUpInfo(pMsg);
		break;
	case MSG_UPHPANDMP://sbw_add HPMP
		playerMgr->OnMsgHPMPModify(pMsg);
		break;
	case MSG_REQ_FIRSTTIP:
		playerMgr->OnMsgFirstEvent(pMsg);
		break;
	case MSG_OPEN_UI:
		playerMgr->OnOpenUI(pMsg);
		break;
	case MSG_ACK_ECTYPEMAP_INFO:
		playerMgr->OnMsgEctypeMapInfo(pMsg);
		break;
	case MSG_CALLINTENSIFYUI:
		playerMgr->OnMsgShowIntensifyUI(pMsg);
		break;
	case MSG_DONE_QUEST:
		playerMgr->OnMsgDoneQuest(pMsg);
		break;
	case MSG_PEEKOTHEREUIP:
		playerMgr->OnMsgSeekEquip( pMsg );
		break;
	case MSG_REQ_DUEL:
		playerMgr->OnMsgReqDuel(pMsg);
		break;
	case MSG_DUEL_START:
		playerMgr->OnMsgDuelStart(pMsg);
		break;
	case MSG_DUEL_END:
		playerMgr->OnMsgDuelEnd(pMsg);
		break;
	case MSG_ACK_DUEL:
		playerMgr->OnMsgAckDuel(pMsg);
		break;
	case MSG_2C_ITEM_ADSCRIPTION:
		playerMgr->OnMsgSetItemAscription( pMsg );
		break;
	case MSG_SKILLEXPUP:
		playerMgr->OnMsgSkillExpChang(pMsg);
		break;
	case MSG_REQ_SKILLEXPFORSKILLID:
		playerMgr->OnMsgReqSkillID(pMsg);
		break;
	case MSG_KILLMONSTER:
		playerMgr->OnMsgKillMonster(pMsg);
		break;
	case MSG_PKSTATE_CHANGE:
		playerMgr->OnMsgPKStateChange(pMsg);
		break;
	case MSG_ACK_CHANGE_PKFLAG:
		playerMgr->OnMsgAckChangePKFlag(pMsg);
		break;
	case MSG_PLAY_EFFECT:
		playerMgr->OnMsgPlayEffect(pMsg);
		break;
	case MSG_SHOW_INTONATE_BAR:
		playerMgr->OnMsgShowIntonateBar(pMsg);
		break;
	case MSG_ISRELIVEYESORNO:
		playerMgr->OnMsgReqRelive(pMsg);
		break;
	case MSG_CHANGEPOWER:
		playerMgr->OnMsgChangPower(pMsg);
		break;
	case MSG_CHANGEPOWERPOINT:
		playerMgr->OnMsgChangPowerPoint(pMsg);
		break;
	case MSG_INTONATINGOVERTIME:
		playerMgr->OnMsgIntonatingOverTime(pMsg);
		break;
	case MSG_RMBGOLDCHANGE:
		playerMgr->OnMsgRMBGoldChange( pMsg );
		break;
	case MSG_CONSUMESCORE_CHANGE: //商城积分改变，购买的是否服务器返回回来的
		playerMgr->OnMsgRMBConsumeScoreChange( pMsg );
		break;
	case MSG_ACKGLODCOVSILVER:
		playerMgr->OnAckGlodCovSilver( pMsg );
		break;
	case MSG_REQCOVCORPS:
		playerMgr->OnReqMsgCovCorps( pMsg );
		break;
	case MSG_CHANGE_BAGSIZE:
		playerMgr->OnMsgChangeBagSize(pMsg);
		break;
	case MSG_REDUCEOFF:
		playerMgr->OnMsgReduceItem(pMsg);
		break;
	//case MSG_GUILD_GIVEEXP:
	//	playerMgr->OnMsgGuildGiveExp(pMsg);
	//	break;
	case MSG_CALLREDUCEUI:
		playerMgr->OnMsgShowReduceUI(pMsg);
		break;
	case MSG_RETSHOPCENTERCNT:
		playerMgr->OnMsgRetShopCenterItemCnt(pMsg);
		break;
	case MSG_ACKGETSHOPCENTER:
		playerMgr->OnMsgAskGetShopCenter(pMsg);
		break;
	case MSG_CALLUNSOULBOUND:
		playerMgr->OnMsgShowUnsoulBoundUI(pMsg);
		break;
	case MSG_UNSOULBOUND:
		playerMgr->OnMsgUnsoulBound(pMsg);
		break;
	case MSG_RELIVENEEDSILVER:
		playerMgr->OnMsgSetReliveSilver(pMsg);
		break;
	case MSG_FARREPAIRCOSTRMB:
		playerMgr->OnMsgCostSilverReqair(pMsg);
		break;
	case MSG_REQ_DELREPUTENAME:
		playerMgr->OnMsgDelReputeName(pMsg);
		break;
	case MSG_TELLC_LOCKNUM:
		playerMgr->OnMsgLockNum(pMsg);
		break;
	case MSG_CALLLOCKINTENSIFYUI:
		playerMgr->OnMsgShowLockIntensifyUI(pMsg);
		break;
	case MSG_LOCKINTENSIFY:
		playerMgr->OnMsgLockIntensifyRec(pMsg);
		break;
	case MSG_ACK_COMPOUND_NEW:
		playerMgr->OnMsgNewCompoound(pMsg);
		break;
	case MSG_REQ_CHANGE_OWNATTRIBUTE:
		playerMgr->OnChange_OwnAttribute(pMsg);
		break;
	case MSG_CHANGE_BATTLEFLAG:
		playerMgr->OnChangeBattleFlag(pMsg);
		break;
	case MSG_TELL_CompoundRateAdd:
		playerMgr->OnMsgCompoundRateAdd(pMsg);
		break;
	case MSG_TELL_IntensifyRateAdd:
		playerMgr->OnMsgIntensifyRateAdd(pMsg);
		break;
	case MSG_TellShopCenterOffSet:
		playerMgr->OnMsgShopCenterOffSell(pMsg);
		break;

		//------------联盟相关
	/*case MSG_GUILD_ACK_GUILDLIST:
		playerMgr->OnMsgAckGuildList(pMsg);
		break;*/
	//case MSG_GUILD_UPDATE:
	//	playerMgr->OnMsgUpdateGuildInfo( pMsg );
	//	break;
	/*case MSG_ACK_GUILD_ICON:
		playerMgr->OnMsgAckGuildIcon( pMsg );
		break;*/
	/*case MSG_ACK_GUILD_RELATION_CHANGED:
		playerMgr->OnMsgAckGuildRelationChanged( pMsg );
		break;*/
	case MSG_INVITE_INFO:
		playerMgr->OnMsgInviteLeague( pMsg );
		break;
	//case MSG_REQ_EMSMrg:
	//	playerMgr->OnMsgReqShowEMSMrg(pMsg);
	//	break;
	case MSG_USE_ANGELL:
		playerMgr->OnMsgUseAngell(pMsg);
		break;
	case MSG_SHOW_HELMET:
		playerMgr->OnMsgShowHelmet(pMsg);
		break;
	case MSG_ACK_SWITCHSUIT:
		playerMgr->OnMsgSwitchSuit(pMsg);
		break;
	case MSG_SHOWTIMETOP:
		playerMgr->OnMsgShowTimeTop(pMsg);
		break;
	case MSG_SHUTDOWNTIMETOP:
		playerMgr->OnMsgShutDownTimeTop(pMsg);
		break;
	case MSG_SWITCHGATE:
		playerMgr->OnMsgSwitchGate(pMsg);
		break;
	case MSG_ENDACKCHAR:
		playerMgr->OnMsgEndGetCharacter(pMsg);
		break;
	case MSG_ACK_SCRIPT:
		playerMgr->OnMsgAckScript(pMsg);
		break;
	/*case MSG_ACK_GUILD_MANIFESTO_INFO:
		playerMgr->OnMsgMANIFESTO_INFO(pMsg);
		break;*/
	/*case MSG_SHOW_GUILD_MEMBER_TITLE:
		playerMgr->OnMsgMEMBER_TITLE(pMsg);
		break;*/
	case MSG_GETMOUNT:
		playerMgr->OnMsgGetMount(pMsg);
		break;
	case MSG_UPDATEMOUNT:
		playerMgr->OnMsgUpdateMount(pMsg);
		break;
		// added, jiayi, [2009/9/21], 称号
	case MSG_TELLCURRENTTITLE:
		playerMgr->OnMsgTellCurrentTitle( pMsg );
		break;
	case MSG_TELLTITLELIST:
		playerMgr->OnMsgTellTitleList( pMsg );
		break;
	case MSG_ADDTITLEACK:
		playerMgr->OnMsgAddTitleAck( pMsg );
		break;
	case MSG_REMOVETITLEACK:
		playerMgr->OnMsgRemoveTitleAck( pMsg );
		break;
	case MSG_MAPINFOREADY:
		playerMgr->OnMsgMapInfoReady( pMsg );
		break;
	case MSG_TELLPACKAGEACCESS:
		playerMgr->OnMsgTellPackageAccess( pMsg );
		break;
	case MSG_PACKAGEVIEWACK:
		playerMgr->OnMsgPackageViewAck( pMsg );
		break;
	case MSG_PICKPACKAGEITEMACK:
		playerMgr->OnMsgPickPackageItemAck( pMsg );
		break;
	case MSG_PICKPACKAGEITEMBOULTREQ:
		playerMgr->OnMsgPackageItemBoultReq( pMsg );
		break;
	case MSG_PICKPACKAGEITEMBOULTNUMBER:
		playerMgr->OnMsgPackageItemBoultNumber( pMsg );
		break;
	case MSG_PICKPACKAGEITEMNEEDTOASSIGN:
		playerMgr->OnMsgPackageItemNeedToAssign( pMsg );
		break;
	case MSG_PICKPACKAGEITEMASSIGNACK:
		playerMgr->OnMsgPackageItemAssignAck( pMsg );
		break;
	case MSG_TELLTEAMASSIGNINFO:
		playerMgr->OnMsgTellTeamAssignInfo( pMsg );
		break;
	case MSG_TEAMCHANGEASSIGNITEMLEVELACK:
		playerMgr->OnMsgChangeAssignItemLevelAck( pMsg );
		break;
	case MSG_PACKAGEITEMACCESSACK:
		playerMgr->OnMsgPackageitemAccessAck( pMsg );
		break;
	case MSG_TELLPICKPACKAGEITEM:
		playerMgr->OnMsgTellPickPackageItem( pMsg );
		break;
	case MSG_STORAGEMONEYACK:
		playerMgr->OnMsgStorageMoneyAck( pMsg );
		break;
	case MSG_ADDRECIPEACK:
		playerMgr->OnMsgAddRecipeAck( pMsg );
		break;
	case MSG_TELLTEAMINFO:
		playerMgr->OnMsgTellTeamInfo( pMsg );
		break;
	case MSG_CHANGEPROTECTLOCKTIMEACK:
		playerMgr->OnMsgChangeProtectLockTimeAck( pMsg );
		break;
	case MSG_TELLTEAMMEMBERLIST:
		playerMgr->OnMsgTellTeamMemberList( pMsg );
		break;
	case MSG_TELLANTIADDICTIONACCOUNTINFO:
		playerMgr->OnMsgTellAntiAddictionAccountInfo( pMsg );
		break;
	case MSG_ECTYPESTAGETIMEREMAIN:
		playerMgr->OnMsgEctypeStageTimeRemain( pMsg );
		break;
	case MSG_CLEARSKILLCOLLDOWN:
		playerMgr->OnMsgClearSkillCollDown( pMsg );
		break;
	case MSG_ACCOUNTPOINT:
		playerMgr->OnMsgAccountPoint( pMsg );
		break;
	case MSG_TELLLUCKREWARD:
		playerMgr->OnMsgTellLuckReward( pMsg );
		break;
	case MSG_LUCKREWARDACK:
		playerMgr->OnMsgLuckRewardAck( pMsg );
		break;
	case MSG_LUCKREWARDRESULT:
		playerMgr->OnMsgLuckRewardResult( pMsg );
		break;
	case MSG_MOVEGOODSACK:
		playerMgr->OnMsgMoveGoodsAck( pMsg );
		break;
	case MSG_LOCK_ITEMACK:
		playerMgr->OnMsgLockItemAck( pMsg );
		break;
	case MSG_UNLOCK_ITEMACK:
		playerMgr->OnMsgUnLockItemAck( pMsg );
		break;
	case MSG_CHECKUNLOCK_ITEMACK:
		playerMgr->OnMsgCheckUnLockItemAck( pMsg );
		break;
	case MSG_SHOWTREASUREBOX:
		playerMgr->OnMsgShowTreasureBox( pMsg );
		break;
	case MSG_TREASUREBOXRESULT:
		playerMgr->OnMsgTreasureBoxResult( pMsg );
		break;
	case MSG_TREASUREBOXACK:
		playerMgr->OnMsgTreasureBoxAck( pMsg );
		break;			
	case MSG_CHECKCHEATREQ:
		playerMgr->OnMsgCheckCheatReq( pMsg );
		break;
	case MSG_GETPROCESSLISTREQ:
		playerMgr->OnMsgGetProcessListReq( pMsg );
		break;
	case MSG_RETPUBQUESTACK:
		playerMgr->OnMsgResetPubQuestAck( pMsg );
		break;
	case MSG_SUITELEMENTCHECKUPACK:
		playerMgr->OnMsgSuitElementCheckupAck( pMsg );
		break;
	//case MSG_MONEYITEMEXCHANGEACK:
	//	playerMgr->OnMsgMoneyItemExchangeAck( pMsg );
	//	break;
	case MSG_TELLGAMESTAGE:
		playerMgr->OnMsgTellGameStage( pMsg );
		break;
	case MSG_MOVESTARACK:
		playerMgr->OnMsgMoveStarAck( pMsg );
		break;
	case MSG_SPECIALREPAIRITEMACK:
		playerMgr->OnMsgSpecialRepairItemAck( pMsg );
		break;
	case MSG_EQUIPUPGRADEACK:
		playerMgr->OnMsgEquipUpdateItemAck( pMsg );
		break;
	case MSG_SUITLEVELUPACK:
		s_CUI_ID_FRAME_SkillEquipUpdate.OnAck( (MsgSuitLevelUpAck*)pMsg );
		s_CUI_ID_FRAME_FiveXingUpdate.OnAck((MsgSuitLevelUpAck*)pMsg );
		break;
	case MSG_SUITCHANGEACK:
		s_CUI_ID_FRAME_SkillEquipChange.OnAck( (MsgSuitChangeAck*)pMsg );
		s_CUI_ID_FRAME_FiveXingChange.OnAck((MsgSuitChangeAck*)pMsg );
		break;
	case MSG_ONLINEREWARDACK:
		playerMgr->OnMsgOnLineRewardAck( pMsg );
		break;
	case MSG_MOVE_STORAGE_ITEMACK:
		playerMgr->OnMsgMoveStorageItemAck( pMsg );
		break;
	case MSG_BUYBACKITEMACK:
		playerMgr->OnMsgBuyBackItemAck( pMsg );
		break;
	case MSG_BUYBACKITEMLISTACK:
		playerMgr->OnMsgBuyBackItemListAck( pMsg );
		break;
	case MSG_SHOWBATTLESIGNUPDLG:
		playerMgr->OnMsgShowBattleSignUpDlg( pMsg );
		break;
	case MSG_BATTLESIGNUPACK:
		playerMgr->OnMsgBattleSignUpAck( pMsg );
		break;
	case MSG_TELLBATTLESIGNUPCOUNT:
		playerMgr->OnMsgTellBattleSignUpCount( pMsg );
		break;
	case MSG_WALLOWABOUT:
		playerMgr->OnMsgWallowAbout( pMsg );
		break;
	case MSG_CHECKSECONDPASSWORDREQ:
		playerMgr->OnMsgCheckSecondPassword( pMsg );
		break;
	case MSG_SETSECONDPASSWORDACK:
		playerMgr->OnMsgSetSecondPassword( pMsg );
		break;
	case MSG_CLEARSECONDEPASSWORDACK:
		playerMgr->OnMsgClearSecondPassword( pMsg );
		break;
	case MSG_CHECKSECONDPASSWORDRESULT:
		playerMgr->OnMsgCheckSecondPasswordResult( pMsg );
		break;
	case MSG_JIFENGSHOPITEMSLISTACK:
		playerMgr->OnMsgJiFengShopItemListAck( pMsg );
		break;
	case MSG_UPDATETRADESHOPCONFIG:
		playerMgr->OnMsgUpdateTradeShopConfig( pMsg );
		break;
	case MSG_NOTIFYTRADESHOPCONFIGRECHANGE:
		playerMgr->OnMsgTradeShopChange( pMsg );
		break;
	case MSG_SHOWCONSIGNMENTMONEYLIST:
		playerMgr->OnMsgReturnSystemAuction( pMsg );
		break;
	case MSG_SHOWCONSIGNMENTACCOUNT:
		playerMgr->OnMsgAckHandleSystemAuctionAccountMoney( pMsg );
		break;
	case MSG_CONSIGNMENTMONEYACK:
		playerMgr->OnMsgAckExcuteSystemAuction( pMsg );
		break;
	case MSG_SHOWCONSIGNMENTHISTROY:
		playerMgr->OnMsgAuctionHistroyList( pMsg ); 
		break;
	case MSG_OPERATEACCOUNTACK:
		playerMgr->OnMsgOperateMoneyAck(pMsg);
		break;
	case MSG_CONSIGNMENTOPERATEACK:
		playerMgr->OnMsgConsignmentOperateAck(pMsg);
		break;
	case MSG_QUERYCONSIGNMENTACK:
		playerMgr->OnMsgQueryConsignmentListAck(pMsg);
		break;
	case MSG_CONSIGNMENTMONEYHISTROYACK:
		playerMgr->OnMsgConsignmentMoneyHistroyAck(pMsg);
		break;
	case MSG_TELLCONSIGNMENTMONEY:
		playerMgr->OnMsgTellConsignmentMoney(pMsg);
		break;
	case MSG_MAILLIST_ACK:
		playerMgr->OnMsgMailList(pMsg);
		break;
	case MSG_SENDMAILACK:
		playerMgr->OnMsgMailOnAck(pMsg);
		break;
	case MSG_NOTIFYMAIL:
		playerMgr->OnMsgMailNotify(pMsg);
		break;
	case MSG_OPMAILACK:
		playerMgr->OnMsgMailOpAck(pMsg);
		break;
	case MSG_MOVESTARLEVELUPACK:
		playerMgr->OnMsgMoveStarLevelUpAck( pMsg );
		break;
	case MSG_ITEMCOMPOSEACK:
		playerMgr->OnMsgItemComposeAck( pMsg );
		break;
    case MSG_NOTIFY_BATTLE_KILLNUM:       //通知玩家杀人公告
        playerMgr->OnMsgKillNumProcess(pMsg);
        break;
	//case MSG_MASTERREPORTACK:
	//	playerMgr->OnMsgMasterReportAck( pMsg );
	//	break;
	/*case MSG_MASTERREPORTRESULT:
		playerMgr->OnMsgMasterReportResult( pMsg );
		break;*/
	/*case MSG_PRENTICERREPORTACK:
		playerMgr->OnMsgPrenticeReportAck( pMsg );
		break;*/
	/*case MSG_PRENTICERREPORTRESULT:
		playerMgr->OnMsgPrenticeReportResult( pMsg );
		break;*/
	case MSG_SHOWVIEWUSEITEMTOPLAYER:
		playerMgr->OnMsgShowViewUseItemToPlayer( pMsg );
		break;
	case MSG_SHOWALLUSEITEMTOPLAYER:
		playerMgr->OnMsgShowAllUseItemToPlayer( pMsg );
		break;
    case MSG_SUITELEMENTMOVEACK:
        playerMgr->OnMsgFiveXingMoveAck(pMsg);
        break;
	case MSG_DELETERELATIONCHECKREQ:				// 收到协议离婚请求
		playerMgr->OnMsgDelFriendCheckReq(pMsg);
		break;
	case MSG_DELETERELATIONCHECKACK:
		playerMgr->OnMsgDelFriendCheckAck(pMsg);		// 请求方收到协议离婚结果
		break;
	case MSG_TELLBATTLERECORD:
		playerMgr->OnMsgTellBattleRecord( pMsg );
		break;
	case MSG_TELLBATTLESIGNUPINFO:
		playerMgr->OnMsgTellBattleSignUpInfo( pMsg );
		break;
	case MSG_ENTERTEAMBATTLEREQ:
		playerMgr->OnMsgEnterTeamBattleReq( pMsg );
		break;
    case MSG_JIAOZI_CHANGE:
        playerMgr->OnMsgJiaoZiChange(pMsg);
        break;
	case MSG_QUERYBATTLETEAMINFOACK:
		playerMgr->OnMsgBattleTeamInfo(pMsg);
		break;
	case MSG_QUERYTEAMRECORDACK:
		playerMgr->OnMsgTellBattleTeamRecord(pMsg);
		break;
	case MSG_QUERYBATTLESIGNUPTIMEACK:
		playerMgr->OnMsgQueryBattleSignUpTimeAck(pMsg);
		break;
	case MSG_TELLHIDESTATUS:
		playerMgr->OnMsgTellHideStatus(pMsg);
		break;
// 	case MSG_TELLTRUNREWARD:
// 		playerMgr->OnMsgTellTurenReward(pMsg);
// 		break;
    
    case MSG_MOUNTACKBREED:
        playerMgr->OnMsgMountAckBreed(pMsg);
        break;
    case MSG_ACKOFFLINEHOOK:
        playerMgr->OnMsgAckOfflineHook(pMsg);
        break;

	//		国家		added by zhuomeng.hu		[8/26/2010]
	//case MSG_TELLCOUNTRYBATTLESIGNUP:
	//	playerMgr->OnMsgTellCountryBattleSignUp( pMsg );
	//	break;
	/*case MSG_TELLCOUNTRYBATTLEENTER:
		playerMgr->OnMsgTellCountryBattleEnter( pMsg );   
		break;
	case MSG_TELLCOUNTRYBATTLEFIGHT:  
		playerMgr->OnMsgTellCountryBattleFight( pMsg );
		break;*/
	/*case MSG_ENTERCOUNTERBATTLEACK:     
		playerMgr->OnMsgEnterCounterBattleAck( pMsg );     
		break;*/
	//case MSG_QUETYCOUNTRYBATTLESIGNUPACK:    
	//	playerMgr->OnMsgQueryCountryBattleSignUpAck( pMsg );  
	//	break;
	case MSG_TELLCOUNTRYTITLEINFO:    
		playerMgr->OnMsgTellCountryTitleInfo( pMsg ); 
		break;
//	case MSG_QUERYCOUNTRYINFOREQ:                                   
	case MSG_QUERYCOUNTRYINFOACK:
		playerMgr->OnMsgQueryCountryInfoAck( pMsg );
		break;
	case MSG_TELLCOUNTRYQUERYSTATUS:  
		playerMgr->OnMsgTellCountryQueryStatus( pMsg ); 
		break;
//	case MSG_COUNTRYNOTICECHANGEREQ:                              
	case MSG_COUNTRYNOTICECHANGEACK:  
		playerMgr->OnMsgCountryNoticeChangeAck( pMsg ); 
		break;
//	case MSG_COUNTRYQUESTSTATECHANGEREQ:                            
	case MSG_COUNTRYQUESTSTATECHANGEACK:  
		playerMgr->OnMsgCountryQuestStateChangeAck( pMsg );
		break;
//	case MSG_COUNTRYOFFICIALAPPOINTREQ:                                
	case MSG_COUNTRYOFFICIALAPPOINTACK:  
		playerMgr->OnMsgCountryOfficialAppointAck( pMsg );  
		break;
//	case MSG_COUNTRYOFFICIALRECALLREQ:                                
	case MSG_COUNTRYOFFICIALRECALLACK:  
		playerMgr->OnMsgCountryOfficialRecallAck( pMsg );
		break;
	case MSG_COUNTRYQUESTSTATUSSTOP:   
		playerMgr->OnMsgCountryQuestStatusStop( pMsg );
		break;
	case MSG_TELLCOUNTRYKILLPOSITION: 
		playerMgr->OnMsgTellCountryKillPosition( pMsg ); 
		break;
//	case MSG_COUNTRYREQUESTRAISEREQ:                                    
	case MSG_COUNTRYREQUESTRAISEACK:
		playerMgr->OnMsgCountryRequestRaiseAck( pMsg );
		break;
	case MSG_COUNTRYRAISETOPLAYERREQ:  //国家募捐
		playerMgr->OnMsgCountryRaiseToPlayerReq( pMsg ); 
		break;
//	case MSG_COUNTRYRAISETOPLAYERACK:
//		playerMgr->OnMsgCountryRaiseToPlayerAck( pMsg ); 
//		break;
	case MSG_COUNTRYRAISETELLPLAYER: 
		playerMgr->OnMsgCountryRaiseTellPlayer( pMsg ); 
		break;
	case MSG_COUNTRYRECEIVEMOUNTACK: 
		playerMgr->OnMsgCountryReceiveMountAck( pMsg );   
		break;
	case MSG_TELLCOUNTRYBORDERSFIGHT:  
		playerMgr->OnMsgTellCountryBordersFight( pMsg ); 
		break;
	case MSG_TELLCOUNTRYKILLENEMY: 
		playerMgr->OnMsgTellCountryKillEnemy( pMsg );   
		break;
//	case MSG_COUNTRYFLYTOBORDERSREQ:                                   
//	case MSG_COUNTRYOPERATETOPLAYERREQ:                               
	case MSG_COUNTRYOPERATETOPLAYERACK:
		playerMgr->OnMsgCountryOperateToPlayerAck( pMsg ); 
		break;
	case MSG_COUNTRYTELLOPERATETOPLAYER:  
		playerMgr->OnMsgCountryTellOperateToPlayer( pMsg );
		break;
    case MSG_TELLOPERATETOCOUNTRY:  
        playerMgr->OnMsgTellOperateToCountry( pMsg );
        break;
	case MSG_COUNTRYCONVENERESULT: 
		playerMgr->OnMsgCountryConveneResult( pMsg ); 
		break;
	case MSG_COUNTRYCONVENEREQ:  
		playerMgr->OnMsgCountryConveneReq( pMsg );
		break;
//	case MSG_COUNTRYCONVENEACK: 
//		playerMgr->OnMsgCountryConveneAck( pMsg ); 
//		break;
	case MSG_COUNTRYCOUNTRYAPPOINT:  
		playerMgr->OnMsgCountryCountryAppoint( pMsg );
		break;
    
    case MSG_COUNTRYTELLCOUNTRYID:
        playerMgr->OnMsgCountryTellCountryID( pMsg );
        break;
    case MSG_COUNTRYTELLWEAK:
        playerMgr->OnMsgCountryTellWeak( pMsg );
        break;
	case MSG_COUNTRYTELLSTRONG:
		playerMgr->OnMsgCountryTellStrong( pMsg );
		break;
    case MSG_COUNTRYBATTLEREPLACE:
        playerMgr->OnMsgCountryBattleReplace( pMsg );
        break;
    case MSG_TELLCOUNTRYNAME:
        playerMgr->OnMsgTellCountryName( pMsg );
        break;
    case MSG_CHANGECOUNTRYNAMEACK:
        playerMgr->OnMsgChangeCountryNameAck( pMsg );
        break;
    case MSG_TELLCOUNTRYNAMECHANGE:
        playerMgr->OnMsgTellCountryNameChange( pMsg );
        break;
    case MSG_TELLCOUNTRYSTATUS:
        {
            playerMgr->OnMsgTellMassacreCountry( pMsg );
        }
        break;
    case MSG_UPDATECOUNTRYWARFIGHTKILL:
        {
            playerMgr->OnMsgUpdateCountryWarFightKill( pMsg );
        }
        break;
    case MSG_TELLCOUNTRYPLAYERRAISE:
        {
            playerMgr->OnMsgTellCountryPlayerRaise( pMsg );
        }
        break;
	case MSG_TELLCOUNTRYPLAYERRAISEITEM:
		{
			playerMgr->OnMsgTellCountryPlayerRaiseItem( pMsg );
		}
		break;
	case MSG_TELLGUILDPLAYERAISEITEM:
		{
			playerMgr->OnMsgTellGuildPlayerRaiseItem( pMsg );
		}
		break;
	//------------------------------------------------------------------------------------------------------
	//帮会
	case MSG_CREATEGUILDACK://返回创建结果
		{
			playerMgr->OnMsgGuildAckCreateNotice(pMsg);
		}
		break;
	case MSG_GUILDCREATEFAMILYACK: //创建家族notice
		{
			playerMgr->OnMsgGuildCreateNotice(pMsg);
		}
		break;
	case MSG_GUILDASSIGNPOSITIONACK://职位任免notice
		{
			playerMgr->OnMsgGuildAssignPositionNotice(pMsg);
		}
		break;
	case MSG_KICKGUILDACK://踢人出帮notice
		{
			playerMgr->OnMsgRemoveGuildMemberNotice(pMsg);
		}
		break;
	case MSG_GUILDTRANSFERACK://转让职务提示信息
		{
			playerMgr->OnMsgGuildTransferAck(pMsg);
		}
		break;
	case MSG_GUILDFAMILYCHANGEREQ: //修改家族名的notice
		{
			playerMgr->OnMsgFamilyNameChangeNotice(pMsg);
		}
		break;
	case MSG_GUILDMEMBERFAMILYCHANGEACK: //转移帮众
		{
			playerMgr->OnMsgGuildMemberMoveNotice(pMsg);
		}
		break;
	case MSG_INVITEGUILDACK:// 回应邀请进入帮派notice
		{
			playerMgr->OnMsgInviteGuildNotice(pMsg);
		}
		break;
	case MSG_JOINGUILDACK:// 回应申请加入帮派notice
		{
			playerMgr->OnMsgJoinGuildNotice(pMsg);
		}
		break;
	case MSG_GUILDSHOPLEVELUPACK:// 回馈帮派商店激活消息
		{
			playerMgr->OnMsgGuildShopLevelUpNotice(pMsg);
		}
		break;
	case MSG_GUILDBUYITEMACK://帮会商店买东西的回馈
		{
			playerMgr->OnMsgGuildBuyItemNotice(pMsg);
		}
		break;
	case MSG_GUILDLEVELUPACK:// 回馈升级帮会消息
		{
			playerMgr->OnMsgGuildLevelUpNotice(pMsg);
		}
		break;
	case MSG_TELLGUILDDATA://返回帮派信息,游戏开始时，有帮派或者创建帮派后
		{
			thePlayerRole.GetGangMgr()->InitGuildData(pMsg);
		}
		break;
	case MSG_TELLCREATEGUILD://通知玩家创建了xxx帮会
		{
			playerMgr->OnMsgAddNewGuild(pMsg);
		}
		break;
	case MSG_TELLGUILDNOTICE://公告
		{
			playerMgr->OnMsgGuildNotice(pMsg);
		}
		break;
	case MSG_GUILDNOTICEACK://帮派公告信息
		{
			playerMgr->OnMsgGuildNoticeAck(pMsg);
		}
		break;
	case MSG_TELLGUILDFAMILYCHANGE: //修改家族名
		{
			playerMgr->OnMsgFamilyNameChange(pMsg);
		}
		break;
	case MSG_INVITEJOINGUILDREQ: //通知某人, 某公会邀请你加入帮派
		{
			playerMgr->OnMsgGuildReqInvite(pMsg);
			//s_CUI_ID_FRAME_InfoTips.AddGuildInviteTip(pMsg);
		}
		break;
	case MSG_MEMBERDATAUPDATE://帮成员信息改变
		{
			playerMgr->OnMsgUpdateMemberData(pMsg);
		}
		break;
	case MSG_GUILDDATAUPDATE://帮会信息改变
		{
			playerMgr->OnMsgUpDateGuildData(pMsg);
		}
		break;
	case MSG_REQUESTJOINGUILDACK://回应申请加入帮派
		{
			playerMgr->OnMsgApplyJoinGuild(pMsg);
		}
		break;
	case MSG_TELLJOINGUILDTOGUILD://通知帮会成员，有人加入
		{
			playerMgr->OnMsgAddGuildMember(pMsg);
		}
		break;
	case MSG_TELLLEAVEGUILDTOGUILD://通知帮会成员，有人离开
		{
			playerMgr->OnMsgDelGuildMember(pMsg);
		}
		break;
	case MSG_TELLJOINGUILDTOVIEW: // 通知附近玩家某人加入帮派了
		{
			playerMgr->OnMsgSomeOneJoinGuild(pMsg);
		}
		break;
	case MSG_TELLLEAVEGUILDTOVIEW:// 通知附近玩家某人离开帮派了
		{
			playerMgr->OnMsgSomeOneLeaveGuild(pMsg);
		}
	case MSG_LEAVEGUILDACK://Me离开帮会
		{
			playerMgr->OnMsgGuildMemberLeave(pMsg);
		}
		break;
	case MSG_TELLGUILDLIST://客户端接收所有帮派列表
		{
			playerMgr->OnMsgReciveGuildList(pMsg);
		}
		break;
	case MSG_GUILDDELATERESULT://弹劾结果
		{
			playerMgr->OnMsgGuildDelateResult(pMsg);
		}
		break;
	case MSG_GUILDDELATEREQUESTACK:// 申请弹劾回馈notice
		{
			playerMgr->OnMsgGuildTanHeNotice(pMsg);
		}
		break;
	case MSG_GUILDOFFERBUILDACK:// 回应帮贡建设notice
		{
			playerMgr->OnMsgGuildOfferbuildNotice(pMsg);
		}
		break;
	case MSG_GUILDRELEASEACK://回馈客户端发布任务notice
		{
			playerMgr->OnMsgGuildReleaseNotice(pMsg);
		}
		break;
	case MSG_GUILDQUESTRELEASESTATUS:// 通知客户端帮派任务发布状态
		{
			playerMgr->OnMsgGuildDutyStatus(pMsg);
		}
		break;
	case MSG_GUILDDONATEREQ:// 发送募捐请求给客户端
		{
			playerMgr->OnMsgGuildDonate(pMsg);
		}
		break;
	case MSG_GUILDDELATEAGREEREQ:// 向所有帮派成员发送是否同意弹劾的消息
		{
			s_CUI_ID_FRAME_InfoTips.AddGuildTanHeTip(pMsg);			
		}
		break;
	case MSG_TELLGUILDDISBANDTIME:// 提示帮主帮会将在某日期解散
		{
			playerMgr->OnMsgGuildDiabandTime(pMsg);
		}
		break;
	case MSG_QUERYGUILDATAACK://查询帮会信息
		{
			s_CUI_ID_FRAME_GuildApply.OnMsgQueryGuildData(pMsg);
		}
		break;
	case MSG_REQUESTJOINGUILDREQ://发送给帮派管理员, 某人申请加入帮派
		{
			s_CUI_ID_FRAME_InfoTips.ProcessGuildApplyingReq(pMsg);
			//s_CUI_ID_FRAME_InfoTips.AddGuildApplyingTip(pMsg);
		}
		break;
	case MSG_TELLDISBANDGUILD:// 通知客户端帮派解散了
		{
			playerMgr->OnMsgGuildDisband(pMsg);
		}
		break;
	case MSG_GUILDCONVENTREQ: // 帮主召集帮众 到某个地图
		{
			playerMgr->OnMsgGuildMasterConvent(pMsg);
		}
		break;
	case MSG_GUILDCLEARMEMBERACTIVITY: // 通知将所有成员本周活跃度设置到上周, 并清除本周的活跃度
		{
			playerMgr->OnMsgResetGuildMemberActive(pMsg);
		}
		break;
		//----------------------------------------------------------------------------------------------------
	case MSG_STUDENTLEVELUP://徒弟升级，师傅威望增加
		{
			playerMgr->OnMsgStudentLevelUp(pMsg);
		}
		break;
	case MSG_TELLWORLDADDRELATION://结婚
		{
			MsgTellWorldAddRelation* pAddRelation = (MsgTellWorldAddRelation*)pMsg ;
			char cBuffer[256] = {0};
			MeSprintf_s(cBuffer,256,theXmlString.GetString(eTellClient_Marriage),pAddRelation->szPlayer1,pAddRelation->szPlayer2);
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Add_Marriage,  cBuffer);
		}
		break;
		//--------------------------------------------------------------------------帮会战
	case MSG_FLYTOCAMPBATTLEREQ:// 服务器通知客户端是否要进入帮派阵营战场
		{
			playerMgr->OnMsgFlyToCampBattleReq(pMsg);
		}
		break;
	case MSG_TELLCAMPBATTLEPLAYER:// 阵营战场的杀人信息
		{
			playerMgr->OnMsgGetCampBattleInfo(pMsg);
		}
		break;
	case MSG_TELLCAMPBATTLEFIGHTCAMP:// 通知客户端阵营消息
		{
			playerMgr->OnMsgGetMyFightCampType(pMsg);
		}
		break;
	case MSG_SHOWCAMPGUILDBATTLEENTER:// 显示帮派争夺战进入窗口
		{
			playerMgr->OnMsgShowCampGuildBattleEnter(pMsg);
		}
		break;
	case MSG_ENTERCAMPBATTLEACK:// 进入战场结果回馈notice
		{
			playerMgr->OnMsgEnterCampBattleNotice(pMsg);
		}
		break;
	case MSG_CAMPGUILDBATTLERESULT:// 帮派争夺战结果
		{
			playerMgr->OnMsgGetGuildBattleResult(pMsg);
		}
		break;
	case MSG_CAMPBATTLESIGNUPACK://报名结果回馈notice
		{
			playerMgr->OnMsgCampBattleSignNotice(pMsg);
		}
		break;
	case MSG_TELLCAMPBATTLESTATUS:// 通知阵营战场状态
		{
			playerMgr->OnMsgGuildBattleStatus(pMsg);
		}
		break;
	case MSG_TELLCAMPBATTLEKILLPLAYER:// 通知阵营战场杀人
		{
			playerMgr->OnMsgGuildFightInfo(pMsg);
		}
		break;
	case MSG_TELLCAMPBATTLERESOURCE:// 同步战场资源分
		{
			playerMgr->OnMsgGetCampBattleResource(pMsg);
		}
		break;
	case MSG_TELLCAMPGUILDBATTLEUNMATCH:// 通知帮主, 你的帮派最后一个报名没有匹配上, 不能参加帮派争夺战
		{
			playerMgr->OnMsgSignGuildCampBattleFailed(pMsg);
		}
		break;
	case MSG_TELLCAMPBATTLEMATCH:// 通知阵营战场对阵列表
		{
			playerMgr->OnMsgGetGuildCampBattleMatch(pMsg);
		}
		break;
	case MSG_TELLCAMPGUILDBATTLEREFRESHMONSTER:// 通知战场内玩家, 某某怪刷出来了
		{
			playerMgr->OnMsgCampGuildMonsterRefresh(pMsg);
		}
		break;
	case MSG_KILLCAMPBATTLEMONSTER:// 战场杀死怪物
		{
			playerMgr->OnMsgKillCampBattleMonster(pMsg);
		}
		break;
	case MSG_TELLCAMPBATTLESIGNUPREPLACE:// 通知帮派帮主, 你的报名中被其他帮派顶替了
		{
			playerMgr->OnMsgCampBattleSignUpReplace(pMsg);
		}
		break;
	//case MSG_TELLCOUNTRYBATTLEEGUILD:// 全国广播某个帮派获得了战场资格
	//	{
	//		playerMgr->OnMsgCountryBattleGuild(pMsg);
	//	}
	//	break;
	//case MSG_TELLCOUNTERBATTLERESULT:// 通知国家战场结果
	//	{
	//		playerMgr->OnMsgCountryBattleResult(pMsg);
	//	}
	//	break;
	case MSG_TELLCOUNTERBATTLERESULT:// 通知国家战场结果
		{
			playerMgr->OnMsgTellCounterBattleResult( pMsg );  
		}
		break;
	case MSG_QUETYCOUNTRYBATTLESIGNUPACK:  // 国家战场查询报名回馈
		{
			playerMgr->OnMsgCountryBattleSignUpAck( pMsg );  
		}
		break;
	case MSG_TELLCOUNTERBATTLEPLAYERCOUNT: // 发送战场队员个数, 以及帮主死亡次数 ( 红方就是守擂方, 蓝方就是抢擂方 )
		{
			playerMgr->OnMsgCountryBattlePlayerCount( pMsg );  
		}
		break;
	case MSG_TELLCOUNTRYBATTLEEGUILD:
		{
			playerMgr->OnMsgTellCountryBattleGuild( pMsg );
		}
		break;
	case MSG_TELLCAMPBATTLEDEATHCOUNT://当前的死亡次数
		{
			playerMgr->OnMsgTellCampBattleDeathCount( pMsg );
		}
		break;
	//------------------------------------------------------------------------------------------------------
	case MSG_TELLADDRELATIONTIMELEFT:// 通知客户端添加某种关系的剩余时间
		{
			playerMgr->OnMsgAddRelationCoolDownTime(pMsg);
		}
		break;
		//--------------------------------------------------成就
	case MSG_ALLACHIEVEDATA: 
		{
			MsgAllAchieveData* pAchieveData = (MsgAllAchieveData*)pMsg;
			s_CUI_ID_FRAME_Achivement.IntializeAchievements(pAchieveData->achieveData);
		}
		break;
	case MSG_UPDATEACHIEVE: 
		{
			MsgUpdateAchieve* pAchieveUpdate = (MsgUpdateAchieve*)pMsg;
			s_CUI_ID_FRAME_Achivement.UpdateAchievement(pAchieveUpdate->nIndex,pAchieveUpdate->xCharAchieve);
		}
		break;
	case MSG_UPDATEACHIEVEVAR: 
		{
			MsgUpdateAchieveVar* pAchieveVar = (MsgUpdateAchieveVar*)pMsg;
			s_CUI_ID_FRAME_Achivement.UpdateAchieveVar(pAchieveVar->nValueType,pAchieveVar->nValue);
		}
		break;
	case MSG_REQACHIEVEREWARDACK: 
		{
			MsgReqAchieveRewardAck* pAward = (MsgReqAchieveRewardAck*)pMsg;
			s_CUI_ID_FRAME_Achivement.SetAchievePoint(pAward->nAchievePoint);
			s_CUI_ID_FRAME_Achivement.UpdateAchievement(pAward->nIndex,pAward->xCharAchieve);
		}
		break;
		//--------------------------------------------------成就

// 	case MSG_ACTIONINTERRUPT:
// 		{
// 			playerMgr->OnMsgActionInterrupt( pMsg );
// 		}
// 		break;
	case MSG_ONOFFNPCSHIP:
		{
			playerMgr->OnMsgOnOffNpcShip(pMsg);
		}
		break;
        //-------------------------新交易-----------------------
    case MSG_BARGAININGACK:
        {
            playerMgr->OnMsgBargainingAck( pMsg );
        }
        break;
    case MSG_BARGAININGREQUESTREQ:
        {
            playerMgr->OnMsgBargainingRequestReq( pMsg );
        }
        break;
    case MSG_BARGAININGSTART:
        {
            playerMgr->OnMsgBargainingStart( pMsg );
        }
        break;
    case MSG_BARGAININGFINISH:
        {
            playerMgr->OnMsgBargainingFinish( pMsg );
        }
        break;
    case MSG_BARGAININGSTATUS:
        {
            playerMgr->OnMsgBargainingStatus( pMsg );
        }
        break;
    case MSG_BARGAININGDATAACK:
        {
            playerMgr->OnMsgBargainingDataAck( pMsg );
        }
        break;
    case MSG_SHOWBARGAININGDATA:
        {
            playerMgr->OnMsgShowBargainingData( pMsg );
        }
        break;
    case MSG_REMOVEBARGAININGDATAACK:
        {
            playerMgr->OnMsgRemoveBargainingDataAck( pMsg );
        }
        break;
    case MSG_BARGAININGDATAERROR:
        {
            playerMgr->OnMsgBargainingDataError( pMsg );
        }
        break;
        //---------------------坐骑仓库----------------------------
    case MSG_UPDATEMOUNTSTORAGE:
        {
            playerMgr->OnMsgUpdateMountStorage( pMsg );
        }
        break;
    case MSG_UPDATECHARMOUNT:
        {
            playerMgr->OnMsgUpdateCharMount( pMsg );
        }
        break;
        //----------------------新的摆摊---------------------------
    case MSG_ADDSELLDATAACK:
        {
            playerMgr->OnMsgAddSellDataAck( pMsg );
        }
        break;
    case MSG_ADDBUYDATAACK:
        {
            playerMgr->OnMsgAddBuyDataAck( pMsg );
        }
        break;
    case MSG_STARTSTALLACK:
        {
            playerMgr->OnMsgStartStallAck( pMsg );
        }
        break;
    case MSG_BUYORSELLSTALLACK:
        {
            playerMgr->OnMsgBuyOrSellStallAck( pMsg );
        }
        break;
    case MSG_UPDATESTALLDATA:
        {
            playerMgr->OnMsgUpdateStallData( pMsg );
        }
        break;
    case MSG_TELLSTARTSTALL:
        {
            playerMgr->OnMsgTellStartStall( pMsg );
        }
        break;
    case MSG_TELLCLOSESTALL:
        {
            playerMgr->OnMsgTellCloseStall( pMsg );
        }
        break;
    case MSG_SHOWSTALLDATA:
        {
            playerMgr->OnMsgShowStallData( pMsg );
        }
        break;
    case MSG_TELLBUYORSELLSTALLDATA:
        {
            playerMgr->OnMsgTellBuyOrSellStallData( pMsg );
        }
        break;
    case MSG_TELLSTALLDATACOUNT:
        {
            playerMgr->OnMsgTellStallDataCount( pMsg );
        }
        break;
    case MSG_TELLSTALLTITLETOVIEW:
        {
            playerMgr->OnMsgTellStallTitleToView( pMsg );
        }
        break;
    case MSG_TELLSTALLPRICE:
        {
            playerMgr->OnMsgTellStallPrice( pMsg );
        }
        break;
    case MSG_TELLTOTALSTALLDATA:
        {
            playerMgr->OnMsgTellTotalStallData( pMsg );
        }
        break;
        //-------------------- 经验倍率调整 -----------------------
    case MSG_TELLSERVEREXPMODULUS:
        {
            playerMgr->OnMsgTellServerExpModulus( pMsg );
        }
        break;
        //------------- 任务计数变量从ShowText里分离 --------------
    case MSG_UPDATEQUESTVAR:
        {
            playerMgr->OnMsgUpdateQuestVar( pMsg );
        }
        break;
	case MSG_DOUBLEEXPACK:
		{
			s_CUI_ID_FRAME_DuobleExp.OnMsgDoubleExp( pMsg );
		}
		break;
	case MSG_OFFLINEFIGHTOPACK:
		{
			playerMgr->OnMsgOfflineFightOpAck( pMsg );
		}
		break;
	case MSG_PROTECTPETPOS://护送怪(镖车，NPC)的地理位置,
		{
			playerMgr->OnMsgTellProtectPetPos(pMsg);
		}
		break;
	case MSG_CHARASSIGNPOTENTIALACK:
		{
			playerMgr->OnMsgCharAssignPotentialAck(pMsg);
		}
		break;
	case MSG_TELLLEAVEECTYPE:
		{
			playerMgr->OnMsgTellLeaveEctype(pMsg);
		}
		break;
	case MSG_CHANGEXINFA:
		{
			playerMgr->On_MSG_CHANGEXINFA(pMsg);
		}
		break;
	case MSG_ACKSTALLQUERY:
		{
			playerMgr->On_MSG_ACKSTALLQUERY(pMsg);
		}
		break;
        //-----------------搭载其他玩家坐骑---------------------
	case MSG_GOTONOFFDROME:		//接收到上下别人宠物的消息
		{
			playerMgr->OnMsgGotOnOffDrome(pMsg);
		}
		break;
	case MSG_REQGOTONDROME:		//接收到邀请或则请求
		{
			playerMgr->OnMsgReqGotOnDrome(pMsg);
		}
		break;
	case MSG_REQGOTONDROMEACK:
		{
			playerMgr->OnMsgReqGotOnDromeAck(pMsg);
		}
		break;
		//------------------------------------------------------
	case MSG_SHOWSIGNATURE:
		{
			playerMgr->On_MSG_SHOWSIGNATURE(pMsg);
		}
		break;
	case MSG_CHANGESIGNATUREREQ:
		{
			playerMgr->On_MSG_CHANGESIGNATUREREQ(pMsg);
		}
		break;
	case MSG_ADDUPDATEPET:
		{
			playerMgr->OnMsgAddUpdatePet(pMsg);
		}
		break;
	case MSG_CHANGEPET:
		{
			playerMgr->OnMsgChangePet(pMsg);
		}
		break;
	case MSG_PETBREEDREQACK:            // 宠物繁殖响应
		{
			playerMgr->OnMsgPetBreedReqAck(pMsg);
		}
		break;
	case MSG_PETBREEDCHOICEACK:         // 选择繁殖宠物响应
		{
			playerMgr->OnMsgPetBreedChoiceAck(pMsg);
		}
		break;
	case MSG_PETBREEDSTATUS:            // 操作状态
		{
			playerMgr->OnMsgPetBreedStatus(pMsg);
		}
		break;
	case MSG_PETBREEDFINISH:            // 完成繁殖操作
		{
			playerMgr->OnMsgPetBreedFinish(pMsg);
		}
		break;
	case MSG_PETBREEDACQUIREACK:        // 领取宠物反馈
		{
			playerMgr->OnMsgPetBreedAcquireAck(pMsg);
		}
		break;
	case MSG_PETBREEDCANCELLOCK:    //宠物繁殖时取消宠物锁定消息
		{
			playerMgr->OnMsgPetBreedCancelLock(pMsg);
		}
		break;
	case MSG_ALLIDENTIFYDATA:				//所有图鉴数据
		{
			playerMgr->OnMsgPetCardListAll(pMsg);
		}
		break;
	case MSG_UPDATEPETIDENTIFY:			//更新图鉴
		{
			playerMgr->OnMsgPetCardList(pMsg);
		}
		break;
	case MSG_REQIDENTIFYDATA:				//请求图鉴数据
		{
			
		}
		break;
	case MSG_PETREGENERATE:
		{//出战宠物死亡信息
			playerMgr->OnMsgPetDead(pMsg);
		}
		break;
	case MSG_PETLEARNSKILL:
		{//宠物得到技能
			playerMgr->OnMsgPetLearnSkill(pMsg);
		}
		break;
 	case MSG_VIEWACTIVEPETACK:
 		{//查看其他人的宠物
 			playerMgr->OnMsgLookOtherPet(pMsg);
 		}
 		break;
	case MSG_TELLGUILDAIM:	//更改帮派宗旨
		{
			playerMgr->OnMsgTellGuildAim(pMsg);
		}
		break;
	case MSG_CHANGEGUILDAIMACK:	//回复请求修改帮派宗旨
		{
			playerMgr->OnMsgChangeGuildAimAck(pMsg);
		}
		break;
	//---------------------------家族------------------------
	case MSG_CREATEFAMILYACK:			// 回复创建家族成功
		{
			playerMgr->OnMsgCreateFamilyAck(pMsg);
		}
		break;
	case MSG_TELLFAMILYINFO:			// 家族成员信息
		{
			//playerMgr->OnMsgTellFamilyInfo(pMsg);
			CSystemFamily::Instance()->OnMsgTellFamilyInfo(pMsg);
		}
		break;
	case MSG_TELLJOINFAMILYTOFAMILY:	// 新成员加入家族
		{
			CSystemFamily::Instance()->OnMsgTellJoinFamilyToFamily(pMsg);
		}
		break;
	case MSG_TELLLEAVEFAMILYTOFAMILY:	// 成员离开家族
		{
			CSystemFamily::Instance()->OnMsgTellLeaveFamilyToFamily(pMsg);
		}
		break;
	case MSG_TELLLEAVEFAMILYTOVIEW:		//通知附近玩家，某人离开了家族
		{
			CSystemFamily::Instance()->OnMsgTellLeaveFamilyToView(pMsg);
		}
		break;
	case MSG_TELLJOINFAMILYTOVIEW:		//通知附近玩家，某人加入了家族
		{
			CSystemFamily::Instance()->OnMsgTellJoinFamilyToView(pMsg);
		}
		break;
	case MSG_QUITFAMILYACK:				//回复退出家族
		{
			CSystemFamily::Instance()->OnMsgQuitFamilyAck(pMsg);
		}
		break;
	case MSG_TELLCREATEFAMILY:			//全服器广播创建家族成功
		{
			playerMgr->OnMsgTellCreateFmily(pMsg);
			CSystemFamily::Instance()->OnMsgTellCreateFmily(pMsg);
		}
		break;
	case MSG_ALLFAMILYINFOLIST:			//玩家登入时候发送 所有家族列表
		{
			CSystemFamily::Instance()->OnMsgAllFamilyInfoList(pMsg);
		}
		break;
	case MSG_REQUESTJOINFAMILYREQ:		//通知族长有人申请加入家族
		{
			playerMgr->OnMsgRequestJoinFamilyReq(pMsg);
		}
		break;
	case MSG_INVITEJOINFAMILYREQ:		//邀请加入家族
		{
			playerMgr->OnMsgInviteJoinFamilyReq(pMsg);
		}
		break;
	case MSG_INVITEFAMILYACK:			//通知队长邀请结果
		{
			playerMgr->OnMsgInviteFamilyAck(pMsg);
		}
		break;
	case MSG_TELLFAMILYNOTICEUPDATE:   // 通知公告更新
		{
			CSystemFamily::Instance()->OnMsgTellFamilyNoticeUpdate(pMsg);
		}
		break;
	case MSG_FAMILYNOTICEACK: //回发家族公告
		{
			CSystemFamily::Instance()->OnMsgFamilyNoticeAck(pMsg);
		}
		break;
	case MSG_FAMILYTRANSFERACK:	//转让族长的结果反馈
		{
			CSystemFamily::Instance()->OnMsgFamilyTransferAck(pMsg);
		}
		break;
	case MSG_TELLFAMILYTRANSFER:  //转让族长消息
		{
			CSystemFamily::Instance()->OnMsgTellFamilyTransfer(pMsg);
		}
		break;
	case MSG_TELLVIEW_POSITIONCHANGE: //向周围玩家同步家族职位信息
		{
			CSystemFamily::Instance()->OnMsgTellViewPositionChange(pMsg);
		}
		break;
	case MSG_FAMILYMEMBERDATAUPDATE:  // 更新家族成员信息到客户端
		{
			CSystemFamily::Instance()->OnMsgFamilyMemberDataUpdate(pMsg);
		}
		break;
	case MSG_FAMILYDONATEACK:		//回复捐献资金
		{
			CSystemFamily::Instance()->OnMsgFamilyDonateAck(pMsg);
		}
		break;
	case MSG_TELLFAMILYDONATE:		//家族内广播捐献资金
		{
			CSystemFamily::Instance()->OnMsgTellFamilyDonate(pMsg);
		} 
		break;
	case MSG_FAMILYUPGRADEACK:		//回复升级家族
		{
			CSystemFamily::Instance()->OnMsgFamilyUpgradeAck(pMsg);
		}
		break;
	case MSG_TELLFAMILYUPGRADE:		//通知家族更新
		{
			CSystemFamily::Instance()->OnMsgTellFamilyUpgrade(pMsg);
		}
		break;
	case MSG_TELLFAMILYDISBAND:		//家族解散
		{
			CSystemFamily::Instance()->OnMsgTellFamilyDisband(pMsg);
		}
		break;
	case MSG_JOINFAMILYACK:			//回复申请加入家族
		{
			CSystemFamily::Instance()->OnMsgJoinFamilyAck(pMsg);
		}
		break;
	case MSG_QUERYFAMILYINFOACK:	//查询家族信息
		{
			s_CUI_ID_FRAME_FamilyApply.OnMsgQueryFamilyInfoAck(pMsg);
		}
		break;
	case MSG_TELLCLIENT_CANINVITE:	//通知队长那些玩家可以邀请了
		{
			CSystemFamily::Instance()->OnMsgTellClientCanInvite(pMsg);
		}
		break;
	case MSG_TELLCLIENTPROSPERITY:	//更新家族繁荣度
		{
			CSystemFamily::Instance()->OnMsgTellClientProsperity(pMsg);
		}
		break;
	case MSG_FAMILYAIMACK:	//回复修改家族宗旨
		{
			playerMgr->OnMsgFamilyAimAck(pMsg);
		}
		break;
	case MSG_EQUIPTALISMANACK:
		{
			playerMgr->OnMsgEquipTalismanAck(pMsg);
		}
		break;
	case MSG_UNEQUIPTALISMANACK:
		{
			playerMgr->OnMsgUnEquipTalismanAck(pMsg);
		}
		break;
	case MSG_TALISMANCHANGE:
		{
			playerMgr->OnMsgChangeTalisman(pMsg);
		}
		break;
	case MSG_PETSAVVYUPACK:
		{
			playerMgr->OnMsgPetSavvyUpack(pMsg);
		}
		break;
	case MSG_UPDATEPETCHAR:
		{
			playerMgr->OnMsgPetUpdateChar(pMsg);
		}
		break;
	case MSG_ACK_RESULT:
		{
			playerMgr->OnMsgAckResult( pMsg );
		}
		break;
	case MSG_SCRIPTEND:
		{
			playerMgr->OnMsgScriptEnd( pMsg );
		}
		break;
	case MSG_UPDATEGUIDEACK:
		{
			playerMgr->OnMsgUpdateGuideAck( pMsg );
		}
		break;
	case MSG_PLAYMOVIEREQ:      // 脚本请求播放视频
		{
			playerMgr->OnMsgPlayMovieReq( pMsg );
		}
		break;
	case MSG_MONSTERTYPESTATUSCHANGE:      // 
		{
			MsgMonsterTypeStatusChange* pStatus = (MsgMonsterTypeStatusChange*)pMsg;
			CPlayer* pMonster = playerMgr->FindByID(pStatus->nMonsterID);
			if (pMonster)
			{
				pMonster->SetTypeStatus(pStatus->nTypeStatus);
			}
		}
		break;
	case MSG_SCENEPLAY:
		{
			playerMgr->OnMsgPlayScene(pMsg);
		}
		break;
	case MSG_BLACKSCREEN:
		{
			playerMgr->OnMsgMoviceScreen(pMsg);
		}
		break;
	case MSG_G2C_REQ_BIANSHEN:
		{
			playerMgr->OnMsgG2CReqBianShen(pMsg);
		}
		break;
	case MSG_TELLTPHJRANK:
		{
			playerMgr->OnMsgTellTPHJRank(pMsg);
		}
		break;
	case MSG_TELLHEROADDATTR:
		{
			playerMgr->OnMsgTellHeroAddAttr(pMsg);
		}
		break;
	case MSG_TELLQUESTTIME:
		{
			playerMgr->OnMsgTellQuestTime(pMsg);
		}
		break;
	case MSG_CHANGE_2_BIAOCHE_ACK:
		{
			playerMgr->OnMsgChangeToBiaocheAck(pMsg);
		}
		break;
	case MSG_RESTORE_FROM_BIAOCHE_ACK:
		{
			playerMgr->OnMsgRestoreFromBiaocheAck(pMsg);
		}
		break;
	case MSG_S2C_PlayerPlayAnim:
		playerMgr->OnMsgPlayerPlayAnim( pMsg );
		break;
	case MSG_COUNTRYCHANGEACK:
		{
			playerMgr->OnMsgCountryChangeAck(pMsg);
		}
		break;
	case MSG_TELLRELIVEBUFF:
		{
			playerMgr->OnMsgTellReliveBuff(pMsg);
		}
		break;
	case MSG_SHOW_HEROSUIT:
		{
			playerMgr->OnMsgReqChangeHero(pMsg);
		}
		break;
	case MSG_REQ_FIRST_LIMITINFO:
		{
			playerMgr->OnMsgInitLevelLimit(pMsg);
		}
		break;
	case MSG_GS2C_LIMITDONE:
		playerMgr->OnMsgDoneLimit(pMsg);
		break;
	case MSG_ZHUJIANGCOMPOSEACK:
		playerMgr->OnMsgZhuJiangCOMPOSE(pMsg);
		break;
	case MSG_TRANSFER_STAR_ACK:
		playerMgr->OnMsgFransferStarAck(pMsg);
		break;
	case MSG_UNBINDEQUIPACK:
		//装备解绑定成功 我们更新装备属性
		playerMgr->OnMsgUnBindEquip(pMsg);
		break;
	case MSG_MOUNT_STRENGTHEN_ACK:
		playerMgr->OnMsgMountStrengthenAck(pMsg);
		break;
	case MSG_KILLPLAYERNUM:
		//更新客户端玩家世界杀人数 和本周杀人数
		playerMgr->OnMsgKillPlayerNum(pMsg);
		break;
	case MSG_CONKILLPLAYER:
		playerMgr->OnMsgConKillPlayer(pMsg);
		break;
	case MSG_REMOVEITEMBYBAGTYPE:
		playerMgr->OnMsgRemoveItemByType(pMsg);
		break;
	case MSG_UPDATECOUNTRYINFOACK:
		playerMgr->OnMsgUpdateCountryDate(pMsg);
		break;
	case MSG_GUILDSQACK:
		playerMgr->OnMsgGuildSQACK(pMsg);
		break;
	case MSG_GUILDADDSQREQ:
		playerMgr->OnMsgGuildAddSQ(pMsg);
		break;
	case MSG_GUILDDELSQREQ:
		playerMgr->OnMsgGuildDElSQ(pMsg);
		break;
	case MSG_COUNTRYFLYMAP:
		playerMgr->OnMsgFlyMap(pMsg);
		break;
	case MSG_PROCTIMESTEPACK:
		playerMgr->OnMsgTimeStep(pMsg);
		break;
	case MSG_REPEATEDLY_PET:
		playerMgr->OnMsgRepeatedlyPet(pMsg);
		break;
	case MSG_PLATFORMERROR:
		playerMgr->OnMsgPlatformModifyError(pMsg);
		break;
	case MSG_CAMPWORLDBATTLEACK:
		playerMgr->OnMsgWorldBattle(pMsg);
		break;
	case MSG_GETGLOBALDBBATTLESUMACK:
		playerMgr->OnMsgBattleSum(pMsg);
		break;
	case MSG_MONSTERBELONGID:
		playerMgr->OnMonsterBeLong(pMsg);
		break;
	case MSG_MONSTERNURTUREINFO:
		playerMgr->OnMonsterNurtureInfo(pMsg);
		break;
	case MSG_SENDMESSAGEEND:
		playerMgr->OnMsgSendMessageEnd(pMsg);
		break;
	case MSG_CHANGEMAPTIMESTEPREQ:
		playerMgr->OnMsgChangeMapTimeStepReq(pMsg);
		break;
	case MSG_RANDATTRIBUTE_ACK:
		playerMgr->OnMsgRandAttributeAck(pMsg);
		break;
	case MSG_TELLCLIENTLEAVETEAM:
		playerMgr->OnMsgTellClientLeaveTeam(pMsg);
		break;
	case MSG_GUILDCLIENUPDATE:
		playerMgr->OnMsgGuildClientUpdate(pMsg);
		break;
	case MSG_CHANGEPETDURATION:
		playerMgr->OnMsgChangePetDuration(pMsg);
		break;
	case MSG_UPDATEPETMODE:
		playerMgr->OnChangePlayerMode(pMsg);
		break;
	case MSG_USEITEM:
		playerMgr->OnMsgTellUseItem(pMsg);
		break;
	case MSG_UPDATECARD:
		playerMgr->OnMsgUpdateCard(pMsg);
		break;
	case MSG_RECARDACHIEVE_ACK:
		playerMgr->OnMsgCardAchieve(pMsg);
		break;
	case MSG_CAMPGUILDBATTLEREWARDINFO:
		playerMgr->OnMsgCampGuildBattleRewardInfo(pMsg);
		break;
	case MSG_CAMPBATTLESIGNUPSECC:
		playerMgr->OnMsgCampBattleSignUpSecc(pMsg);
		break;
	case MSG_CAMPBATTLECHECKCAMPBATTLEVALUESUM:
		playerMgr->OnMsgCampBattleCheckCampBattleValueSum(pMsg);
		break;
	case MSG_ASKSEVENDAYSDATA_ACK:
		playerMgr->OnMsgSevenDaysDataAck(pMsg);
		break;
	case MSG_FRESHSEVENDAYSTATE_VAR:
		playerMgr->OnMsgFreshStateVar(pMsg);
		break;
	case MSG_TRIGGERSEVENDAYS:
		playerMgr->OnMsgTriggerSevenDays(pMsg);
		break;
	case MSG_ASKSEVENDAYSTASK_ACK:
		playerMgr->OnMsgAskSevenDaysTaskAck(pMsg);
		break;
	case MSG_CHANGEGUILDNAMEACK:
		playerMgr->OnMsgChangeGuldNameAck(pMsg);
		break;
	case MSG_CHANNELSINFO:
		playerMgr->OnMsgSelectChannel(pMsg);
		break;
	case MSG_CHANGECHANNEL_ACK:
		playerMgr->OnMsgChangeChannelAck(pMsg);
		break;
	case MSG_CLEARTEAMMAPACK:
		playerMgr->OnMsgClearTeamMapAck(pMsg);
		break;
	case MSG_ASKGETSALARY_ACK:
		playerMgr->OnMsgAskGetSalaryAck(pMsg);
		break;
	case MSG_ASKADVANCEMENT_ACK:
		playerMgr->OnMsgAskAdvancementAck(pMsg);
		break;
	case MSG_SHOWRANKTITLE:
		playerMgr->OnMsgShowRankTitle(pMsg);
		break;
	case MSG_ADDCOUNTRYINFOREQ:
		playerMgr->OnMsgAddCountryInfoReq(pMsg);
		break;
	case MSG_LOADCOUNTRYINFOACK:
		playerMgr->OnMsgLoadCountryInfoAck(pMsg);
		break;
	case MSG_LOADQUESTENTRUSTDATAACK:
		playerMgr->OnMsgLoadQuestEntrustDataAck(pMsg);
		break;
	case MSG_QUESTENTRUSTNEEDUPDATE:
		playerMgr->OnMsgQuestEntrustNeedUpdate(pMsg);
		break;
	case MSG_RECONNECTACK:
		playerMgr->OnMsgReconnectAck(pMsg);
		break;
	case MSG_RECONNECT_RESETSTATE:
		playerMgr->OnMsgReconnectResetState(pMsg);
		break;
	case MSG_GUILDCHANGENAMEACK:
		playerMgr->OnMsgGuildChangeNameAck(pMsg);
		break;
	case MSG_RELATIONUPDATENAMEACK:
		playerMgr->OnMsgRelationUpdateNameAck(pMsg);
		break;
	case MSG_HUNTING_QUEST:
		playerMgr->OnMsgHuntingQuestList(pMsg);
		break;
	case MSG_TELLGAMEBATTLESTATUS:
		playerMgr->OnMsgTellGameBattleStatus(pMsg);
		break;
	case MSG_SHOWGAMEGUILDBATTLEENTER:
		playerMgr->OnMsgShowGameGuildBattleEnter(pMsg);
		break;
	case MSG_ENTERGAMEBATTLEACK:
		playerMgr->OnMsgEnterGameBattleNotice(pMsg);
		break;
	case MSG_TELLGAMEBATTLERESOURCE:
		playerMgr->OnMsgGetGameBattleResource(pMsg);
		break;
	case MSG_TELLGAMEBATTLEKILLPLAYER:
		playerMgr->OnMsgTellGameBattleKillPlayer(pMsg);
		break;
	case MSG_TELLGAMEBATTLEPLAYER:
		playerMgr->OnMsgGetGameBattleInfo(pMsg);
		break;
	case MSG_TELLGAMEBATTLEMATCH:
		playerMgr->OnMsgTellGameBattleMatch(pMsg);
		break;
	case MSG_KILLGAMEBATTLEMONSTER:
		playerMgr->OnMsgKillGameBattleMonster(pMsg);
		break;
	case MSG_GAMEGUILDBATTLERESULT:
		playerMgr->OnMsgGetGameGuildBattleResult(pMsg);
		break;
	case MSG_TELLGAMEBATTLEFIGHTCAMP:
		playerMgr->OnMsgTellGameBattleFightCamp(pMsg);
		break;
	case MSG_CAMPBATTLENEWDATAACK:
		playerMgr->OnMsgCampBattleNewDataAck(pMsg);
		break;
	case MSG_GAMEBATTLEERRORACK:
		playerMgr->OnMsgGameBattleErrorAck(pMsg);
		break;
	case MSG_ADDCAMPBATTLEDATAACK:
		playerMgr->OnMsgAddCampBattleDataAck(pMsg);
		break;
	case MSG_LOADCAMPBATTLEDATAACK:
		playerMgr->OnMsgLoadCampBattleDataAck(pMsg);
		break;
	case MSG_DELCAMPBATTLEDATAACK:
		playerMgr->OnMsgDelCampBattleDataAck(pMsg);
		break;
	case MSG_FLYTOGAMEBATTLEREQ:
		playerMgr->OnMsgFlyToGameBattleReq(pMsg);
		break;
	case MSG_FLYTOPOSITION:
		playerMgr->OnMsgFlyToPosition(pMsg);
		break;	
	case MSG_QUESTENTRUSTINFOACK:
		playerMgr->OnMsgQuestEntrustInfoAck(pMsg);
		break;
	case MSG_SHOWCENTERINFO:
		playerMgr->OnMsgShowCenterInfo(pMsg);
		break;
	case MSG_QUESTENTRUSTSHOWINFO:
		playerMgr->OnMsgQuestEntrustShowInfo(pMsg);
		break;
	case MSG_GETTHREEDAYITEMACK:
		playerMgr->OnMsgGetThreeDayItemAck(pMsg);
		break;
	case MSG_UPDATEYUANBAODATA:
		playerMgr->OnMsgUpdateYuanBaoData(pMsg);
		break;
	case MSG_REMOVEITEMBYGUID:
		playerMgr->OnMsgRemoveItemByGuID(pMsg);
		break;
	case MSG_UPDTECAMPBATTLECD:
		playerMgr->OnMsgUpdateAddCampBattleCD(pMsg);
		break;
	case MSG_UPDATEGUILDMEMBERONLINETIME:
		playerMgr->OnMsgUpdateGuildMemberOnLineTime(pMsg);
		break;
	case MSG_UPDATEPLAYERPOINT:
		playerMgr->OnMsgUpdatePlayerPoint(pMsg);
		break;
	case MSG_CHECKCSAUTHREQ:
		playerMgr->OnMsgCheckCSAuthReq(pMsg);
		break;
	case MSG_COUNTRYBUFFCHANGE:
		playerMgr->OnMsgCountryBuffChange(pMsg);
		break;
	case MSG_LEAVEEXPACK:
		playerMgr->OnMsgLeaveExpAck(pMsg);
		break;
	default:
		break;
	}
	return true;
	unguard;
}	


