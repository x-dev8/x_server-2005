
#ifndef UiLua_H_
#define UiLua_H_

#include "MeUi/MeUi.h"

extern "C" 
{
	#include "Luaplus/lua/lua.h"
	#include "Luaplus/lua/lauxlib.h"
	#include "Luaplus/lua/lualib.h"
	#include "tolua++\tolua++.h"
}

int luaopen_IrrLua(lua_State* L);

#endif