//////////////////////////////////////////////////////////////////////////
//  Created: Human
//  Data: 2005 / 12/ 30
//#include "MeTerrain/stdafx.h"

#include "LuaFuns.h"
#include "ErrorLog.h"
#include "../../Client/Client/include/Ui/messageBox.h"
#include "funcperformancelog.h"
#include "../../Client/Client/Include/Player.h"
#include "../../Client/Client/Include/PlayerMgr.h"
#include "../../Client/Client/Include/GameMain.h"
#include "../../Client/Client/Include/Ui/ChatInfoBox.h"
#include "../../Client/Client/Include/Ui/Tips.h"
#include "../../Client/Client/Include/Ui/ActionUI.h"
#include "../../Client/Client/Include/Ui/baseProperty.h"
#include "../../Client/Client/Include/Ui/Task.h"
// #include "../../Client/Client/Include/Ui/help.h"
#include "../../Client/Client/Include/Ui/Target.h"
#include "../../Client/Client/Include/Ui/Main.h"
//#include "../../Client/Client/Include/Ui/Guild.h"
#include "../../Client/Client/Include/Ui/Pack.h"
#include "../../Client/Client/Include/Ui/skill.h"
#include "../../Client/Client/Include/Ui/Gang.h"
#include "../../Client/Client/Include/Ui/chat_particular.h"
#include "../../Client/Client/Include/Ui/MainMenu.h"
#include "GlobalDef.h"
#include "FuncPerformanceLog.h"
extern CHeroGame theHeroGame;
extern BOOL DebugCommand( const char* pszCommand );
//int LuaGetSystemTime(lua_State * L)
//{
//	return 1;
//}

//////////////////////////////////////////////////////////////////////////
//UI
int UI_SetVisable(lua_State * L);
int UI_GetPos(lua_State * L);
int UI_IsVisable(lua_State * L);
int UI_SetPos(lua_State * L);
int UI_ChengedImage( lua_State * L );
int UI_Msg( lua_State * L );
int UI_Tips( lua_State *L );
int UI_SetTipText( lua_State *L );
//int UI_ChangeChat( lua_State *L );
int UI_ShortcutPrivate( lua_State *L);
//////////////////////////////////////////////////////////////////////////
// System
int LuaLogger(lua_State * L);
int Sys_GetSrcPos(lua_State * L);
int Lua_Rand( lua_State * L );
int Lua_TimeGetTime( lua_State *L );
int Lua_GetLockObjInfo( lua_State * L);
int Lua_Not( lua_State * L );
// string ..
int Lua_GetChar( lua_State * L);
int Lua_SubStr( lua_State * L);
int Lua_DebugCommand(  lua_State * L );
int Lua_Strlen( lua_State * L);
int Lua_GetChatType( lua_State * L);
// network
int Lua_SendMsgChat( lua_State *L );
//
int Lua_GetRoleProperty( lua_State *L );
int Lua_Atoi( lua_State *L );

//Effect
int Lua_EffectSetModel( lua_State *L );
int Lua_GameControl( lua_State *L );
// Define
//TLua_Funcs GameScriptFuns[] = 
//{
//
//	{"UI_SetVisable",	UI_SetVisable	},
//	{"UI_SetPos",		UI_SetPos		},
//	{"UI_GetPos",		UI_GetPos		},
//	{"UI_IsVisable",	UI_IsVisable	},
//	{"UI_ChengedImage", UI_ChengedImage },
//	{"UI_Msg",			UI_Msg			},
//	{"UI_Tips",			UI_Tips			},
//	{"UI_SetTipText",   UI_SetTipText	},
//	{"Sys_GetSrcPos",	Sys_GetSrcPos	},
//	{"LuaLogger",		LuaLogger		},
//	{"Lua_GetChar",		Lua_GetChar		},
//	{"Lua_SubStr",		Lua_SubStr		},
//	{"Lua_Atoi",		Lua_Atoi		},
//	{"Lua_Not",			Lua_Not		},
//	{"Lua_Rand",		Lua_Rand		},
//	{"Lua_Strlen",		 Lua_Strlen		},
//	{"Lua_TimeGetTime",	Lua_TimeGetTime	},
//	{"Lua_GetLockObjInfo",Lua_GetLockObjInfo},
//	{"Lua_DebugCommand", Lua_DebugCommand },
//	{ "Lua_GetChatType", Lua_GetChatType },
//	{ "Lua_SendMsgChat", Lua_SendMsgChat },
//	{ "Lua_GetRoleProperty", Lua_GetRoleProperty },
//
//	//int Lua_SendMsg( lua_State *L );
//
//};

int Out( lua_State* L );
int ThePut( lua_State* L );
int Log( lua_State *L );



TNativeFun GNativeFun[] = 
{
	{ "Out",		Out		},
	{ "ThePut",		ThePut	},
	{ "Log",		Log		},
	{"UI_SetVisable",	UI_SetVisable	},
	{"UI_SetPos",		UI_SetPos		},
	{"UI_GetPos",		UI_GetPos		},
	{"UI_IsVisable",	UI_IsVisable	},
	{"UI_ChengedImage", UI_ChengedImage },
	{"UI_Msg",			UI_Msg			},
	{"UI_Tips",			UI_Tips			},
	{"UI_SetTipText",   UI_SetTipText	},
	//{"UI_ChangeChat",	UI_ChangeChat	},
	{"UI_ShortcutPrivate", UI_ShortcutPrivate },
	{"Sys_GetSrcPos",	Sys_GetSrcPos	},
	{"LuaLogger",		LuaLogger		},
	{"Lua_GetChar",		Lua_GetChar		},
	{"Lua_SubStr",		Lua_SubStr		},
	{"Lua_Atoi",		Lua_Atoi		},
	{"Lua_Not",			Lua_Not		},
	{"Lua_Rand",		Lua_Rand		},
	{"Lua_Strlen",		 Lua_Strlen		},
	{"Lua_TimeGetTime",	Lua_TimeGetTime	},
	{"Lua_GetLockObjInfo",Lua_GetLockObjInfo},
	{"Lua_DebugCommand", Lua_DebugCommand },
	{ "Lua_GetChatType", Lua_GetChatType },
	{ "Lua_SendMsgChat", Lua_SendMsgChat },
	{ "Lua_GetRoleProperty", Lua_GetRoleProperty },
	{ "Lua_EffectSetModel", Lua_EffectSetModel },
	{ "Lua_GameControl", Lua_GameControl }
};

int g_GetNativeFunNum()
{
	return sizeof(GNativeFun) / sizeof(GNativeFun[0]);
}



int Log( lua_State* L)
{
	printf( "Log \0" );
	return 0;
}

int Out( lua_State* L)
{

	printf( "dflkasjfdlasj \0" );

	lua_pushnumber( L, 0 );

	return 0;
}

int ThePut( lua_State* L )
{
	int nType  = (int)lua_tonumber(L, 1);
	GetErrorLog()->logString( "%d\0", nType);
	return 1;
}
//////////////////////////////////////////////////////////////////////////
//
int Lua_Not( lua_State * L )
{
	if (lua_gettop(L) != 1)
		return 0;

	int b = lua_tonumber(L, 1);
	b = !b;

	lua_pushnumber ( L, b );
	return 1;
}
//////////////////////////////////////////////////////////////////////////
// System Lua_Atoi
int Lua_Atoi( lua_State *L )
{
	if (lua_gettop(L) != 1)
		return 0;
	int nRetA = 0;
	const char *szData = lua_tostring(L, 1);
	if(szData)
	{
		char szA = szData[0];
		nRetA = (int)szA;
	}
	lua_pushnumber ( L, nRetA );
	return 1;
}
//////////////////////////////////////////////////////////////////////////
//
//
int UI_SetTipText( lua_State *L )
{
	//if (lua_gettop(L) != 3)
	//	return 0;
	const char *szData = lua_tostring(L, 1);
	if( szData )
	{
		s_CUI_ID_FRAME_Tips.SetText( szData );
	}

	return 0;
}
//////////////////////////////////////////////////////////////////////////
// 
int UI_Tips ( lua_State *L )
{
	//UI_Tips

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//	获得自己基本属性
//
int Lua_GetRoleProperty( lua_State *L )
{
//	if (lua_gettop(L) != 1)
//		return 0;

	SCharInfoClient* pCharInfo = &thePlayerRole.GetCharInfo2();
	int nRetVal = 0;

	const char *szData = lua_tostring(L, 1);
	string szBuffer = szData;
	if( szBuffer == "Agility" )
	{
		nRetVal = thePlayerRole.GetAgi();
	}
// 	else if( szBuffer == "Charm" )
// 	{
// 		nRetVal = thePlayerRole.GetCharm();
// 	}
	else if( szBuffer == "Inteligence" )
	{
		nRetVal = thePlayerRole.GetIntelligence();
	}
	else if( szBuffer == "Magic" )
	{
		nRetVal = thePlayerRole.GetMag();
	}
	else if( szBuffer == "Constitution" )
	{
		nRetVal = thePlayerRole.GetSta();
	}
	else if( szBuffer == "Strength" )
	{
		nRetVal = thePlayerRole.GetStr();
	}
	else if( szBuffer == "Level" )
	{
		nRetVal = thePlayerRole.GetLevel();
	}
	else if( szBuffer == "Sex" )
	{
		nRetVal = thePlayerRole.GetSex();
	}
	else if( szBuffer == "Profession" )
	{
		nRetVal = thePlayerRole.GetProfession();
	}
	lua_pushnumber( L, nRetVal );

	return 1;
}
//////////////////////////////////////////////////////////////////////////
//SendMsg
int Lua_SendMsgChat( lua_State *L )
{
	const char *szData = lua_tostring(L, 2);

// 	if( s_CUI_ID_FRAME_ChatParticular.IsVisable() )
// 	{
// 		s_CUI_ID_FRAME_ChatParticular.SendMsgChat( szData );
// 	}
// 	else
	{
		s_CUI_ChatInfoBox.SendMsgChatNormal( szData );
	}
	
	return 0;
}
int Lua_GetChatType( lua_State * L)
{
	int nType =	s_CUI_ChatInfoBox.GetCurrentChannel();
	lua_pushnumber( L, nType );
	return 1;
}

int Lua_DebugCommand(  lua_State * L )
{
	string sz;
	sz.substr();
	if (lua_gettop(L) != 1)
		return 0;
	const char *szComp = lua_tostring(L, 1);
	if( szComp )
		DebugCommand( szComp );
	return 1;
}

//////////////////////////////////////////////////////////////////////////
// 计算字符长度
//
int Lua_Strlen( lua_State * L)
{
	if (lua_gettop(L) != 1)
		return 0;
	int nLen = 0;
	const char *szBuf = lua_tostring(L, 1);
	if( szBuf )
		nLen = strlen( szBuf );
	lua_pushnumber( L, nLen );
	return 1;
}
//////////////////////////////////////////////////////////////////////////
// subStr
//
int Lua_SubStr( lua_State * L)
{
	if (lua_gettop(L) != 3)
		return 0;
	string szStr;
	int nBegin = 0;
	int nEnd = 0;
	const char *szBuf = lua_tostring(L, 1);
	nBegin = lua_tonumber(L, 2);
	nEnd = lua_tonumber(L, 3);

	szStr = szBuf;
	string szEnd = szStr.substr( nBegin, nEnd );
	lua_pushstring( L, szEnd.c_str() );
	return 1;
}
//////////////////////////////////////////////////////////////////////////
// 从字符串中的到 第 n个 字符
//
int Lua_GetChar( lua_State * L)
{

	if (lua_gettop(L) != 2)
		return 0;
	char szChar[2] = {0};
	const char *szComp = lua_tostring(L, 1);
	int  nIdx	 = lua_tonumber(L, 2);
	if( szComp )
	{
		if( nIdx < strlen(szComp) )
		{
			szChar[0] = szComp[nIdx];
			szChar[1] = '\0';
		}		
	}
	lua_pushstring( L, szChar );
	return 1;
}

//////////////////////////////////////////////////////////////////////////
// 获得 LockObj的信息
// return Type, Name, level...
int Lua_GetLockObjInfo( lua_State * L)
{
	int nType = 0;
	int nLevel = 0;
	char szName[256] = {0};
	//CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->GetMouseTargetPlayer();
	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID(s_CUI_ID_FRAME_Target.GetPlayerID());
	memset(szName,0,sizeof(szName));
	if( pPlayer )
	{
		nType = pPlayer->GetCharType();
		nLevel = pPlayer->GetLevel();
		strncpy( szName, pPlayer->GetName(), sizeof(szName)-1 );
	}
	else
	{
		strcpy( szName, "NULL" );
	}

	lua_pushnumber( L, nType );
	lua_pushstring( L, szName );
	lua_pushnumber( L, nLevel );
	return 3;
}

//Lua Funtions
//////////////////////////////////////////////////////////////////////////
// 
// return int 
int Lua_Rand( lua_State * L )
{
	/*if (lua_gettop(L) != 0 )
	return 0;*/

	int nRand = rand();
	lua_pushnumber( L, nRand );
	return 1;
}

//////////////////////////////////////////////////////////////////////////
// 获得当前时间
// return int 
int Lua_TimeGetTime( lua_State *L )
{
	DWORD nTime = HQ_TimeGetTime();
	lua_pushnumber( L, nTime );
	return 1;
}
//int UI_ChangeChat(lua_State *L )
//{
//	s_CUI_ChatInfoBox.AutoSwitchChat();
//	return 1;
//}
int UI_ShortcutPrivate(lua_State *L)		//r键 快捷恢复私聊
{
	s_CUI_ChatInfoBox.r_ShortcutPrivate();
	return 1;
}
//////////////////////////////////////////////////////////////////////////
// Param : nType, visable
// return x , y
extern int g_nCharacterDBID;
int UI_SetVisable(lua_State * L)
{
	int nType = (int)lua_tonumber(L, 1);
	int bVis = (int)lua_tonumber(L, 2);

	{
		GetErrorLog()->logString( "UI_SetVisable %d Exec", nType );
// 		switch(nType )
// 		{
// 		case eUI_OBJECT_Task:
// 			{
// 				s_CUI_ID_FRAME_Task.ShowUnderLine( !s_CUI_ID_FRAME_Task.IsVisable() );
// 				s_CUI_ID_FRAME_Task.SetVisable(!s_CUI_ID_FRAME_Task.IsVisable());
// 			}
// 			break;
// 		case eUI_OBJECT_Pack:
// 			{
// 				if( !s_CUI_ID_FRAME_PACK.IsVisable() )
// 					s_CUI_ID_FRAME_PACK.SetVisable( true );
// 				else
// 					s_CUI_ID_FRAME_PACK.SetVisable( false );
// 			}
// 			break;
// 		case eUI_OBJECT_Skill:
// 			{
// 				if( !s_CUI_ID_FRAME_SKILL.IsVisable() )
// 					s_CUI_ID_FRAME_SKILL.SetVisable( true );
// 				else 
// 					s_CUI_ID_FRAME_SKILL.SetVisable( false );
// 			}
// 			break;
// 		case eUI_OBJECT_FriendDlg:
// // 			CUILayout::GetInstance()->SetVisable( dynamic_cast<ControlFrame*>(pObject));
// 			break;
// 		case eUI_OBJECT_DlgGang:
//             {
//                 CGangMgr* theGuild = thePlayerRole.GetGangMgr();
//                 if(theGuild == NULL)
//                 {
//                     break;
//                 }
//                 if(theGuild->m_GangInfo.m_nID == GuildDefine::InitID)
//                 {
//                     break;
//                 }
// 				s_CUI_ID_FRAME_Gang.SetVisable(!s_CUI_ID_FRAME_Gang.IsVisable());
// 			    break;
//             }
// 		case eUI_OBJECT_DlgHelp:
// 			{
// 				s_CUI_ID_FRAME_MainMenu.startHelp();
// 			}
// 			break;
// 		case eUI_OBJECT_BaseProperty:
// 			{
// 				if(s_CUI_ID_FRAME_ActionUI.IsVisable())
// 				{
// 					s_CUI_ID_FRAME_ActionUI.SetVisableLayout();
// 					s_CUI_ID_FRAME_BaseProperty.SetVisable(true);
// 					//s_CUI_ID_FRAME_BaseProperty.SetVisableLayout();
// 				}
// 				else
// 					s_CUI_ID_FRAME_BaseProperty.SetVisable(true);
// 					//s_CUI_ID_FRAME_BaseProperty.SetVisableLayout();
// 			}
// 			break;
// 		default:
// 			CUIBase* pObject = GetUIScriptMgr()->GetUIObject( (UI_OBJECT_TYPE)nType );
// 			if( pObject )
// 			pObject->SetVisable( bVis );
// 			break;
// 		}
		
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
// Param : nType
// return x , y
int UI_GetPos(lua_State * L)
{
	int x = 0,
		y = 0;
	int nType = (int)lua_tonumber(L, 1);
// 	ControlObject* pObject = GetUIScriptMgr()->GetUIObject( (UI_OBJECT_TYPE)nType );
// 	if( pObject )
// 	{
// 		RECT rt = {0};
// 		pObject->GetRealRect(&rt);
// 		x = rt.left;
// 		y = rt.top;
// 	}
// 	lua_pushnumber( L, x );
// 	lua_pushnumber( L, y );
	return 2;
}

//////////////////////////////////////////////////////////////////////////
// Param : nType
// return bVis
int UI_IsVisable(lua_State * L)
{
	int nVis = 0;

	int nType = (int)lua_tonumber(L, 1);
// 	CUIBase* pObject = GetUIScriptMgr()->GetUIObject( (UI_OBJECT_TYPE)nType );
// 	if( pObject )
// 	{
// 		RECT rt = {0};
// 		nVis  = pObject->IsVisable();
// 	}
	lua_pushnumber( L, nVis );
	return 1;
}

//////////////////////////////////////////////////////////////////////////
//	
int LuaLogger(lua_State * L)
{
	const char* szTemp = lua_tostring(L, 1);
	GetErrorLog()->logString( szTemp );
	return 0;
}

//////////////////////////////////////////////////////////////////////////
// Param : nType, x, y
// 
int UI_SetPos(lua_State * L)
{
	if (lua_gettop(L) != 3)
		return 0;

	int nType = (int)lua_tonumber(L, 1);
	int x = (int)lua_tonumber(L, 2);
	int y = (int)lua_tonumber(L, 3);
// 	if( nType < 0 || nType > eUI_OBJECT_Max )
// 		return 0;

	printf( "%d %d", x, y );

// 	ControlObject* pObject = GetUIScriptMgr()->GetUIObject( (UI_OBJECT_TYPE)nType );
// 	if( pObject )
// 	{
// 		pObject->SetPos( x, y );
// 	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
// Param 
// return : width, Height
int Sys_GetSrcPos(lua_State * L)
{
	int nWidht = SCREEN_WIDTH;
	int nHeight = SCREEN_HEIGHT;

	lua_pushnumber( L, nWidht );
	lua_pushnumber( L, nHeight );
	return 2;
}

//////////////////////////////////////////////////////////////////////////
//	UI Image oper
//  Param :  nType, string szPath
//
int UI_ChengedImage( lua_State * L )
{
	if (lua_gettop(L) != 2 )
		return 0;

	int nType = (int)lua_tonumber(L, 1);
	const char* szPath = lua_tostring( L, 2 );

// 	ControlObject* pObject = GetUIScriptMgr()->GetUIObject( (UI_OBJECT_TYPE)nType );
// 	if( pObject )
// 	{
// 		//UI
// 		pObject->SetPicName( szPath );
// 		//pObject->SetI( x, y );
// 	}
	return 2;
}

//////////////////////////////////////////////////////////////////////////
// UI MessageBox
// Param : 
int UI_Msg( lua_State * L )
{
	if (lua_gettop(L) != 2 )
		return 0;

	int nType		= (int)lua_tonumber(L, 1);
	const char* szMsg = lua_tostring( L, 2 );

	if( szMsg )
	{
		s_CUI_ID_FRAME_MessageBox.Show( szMsg );	
	}

	return 0;
}

int Lua_EffectSetModel( lua_State *L )
{
	return 0;
}

int Lua_GameControl( lua_State *L )
{
	int nType = (int)lua_tonumber(L, 1);
	theHeroGame.OnChangeControlType((bool)nType);
	return 0;
}