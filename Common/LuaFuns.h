#pragma once

#include <windows.h>
#include "luaScript.h"
//#include "../../client/client/UI/UIMgr.h"

//调用 Lua 的代码
#define LUAEVENT_ON_INIT	"Event_OnInit"
#define LUAEVENT_ON_VISABLE "Event_OnVisable"

#define LUAEVENT_ON_ChatSend "Event_OnChatSend"
#define LUAEVENT_ON_KeyUp "Event_OnKeyUp"
#define LUAGAME_ON_KeyDown	"Game_OnKeyDown"

#define LUAEffectEvent_OnHit "EffectEvent_OnHit"

//extern TLua_Funcs GameScriptFuns[];
//extern int g_GetGameScriptFunNum();

extern TNativeFun GNativeFun[];
extern int g_GetNativeFunNum();
