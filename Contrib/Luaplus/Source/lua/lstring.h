/*
** $Id: lstring.h,v 1.37 2002/08/16 14:45:55 roberto Exp $
** String table (keep all strings handled by Lua)
** See Copyright Notice in lua.h
*/

#ifndef lstring_h
#define lstring_h


#include "lobject.h"
#include "lstate.h"

NAMESPACE_LUA_BEGIN



#define sizestring(l)	(cast(lu_mem, sizeof(union TString))+ \
                         (cast(lu_mem, l)+1)*sizeof(char))
#define sizewstring(l)	(cast(lu_mem, sizeof(union TString))+ \
                         (cast(lu_mem, l)+1)*sizeof(lua_WChar))

#define sizeudata(l)	(cast(lu_mem, sizeof(union Udata))+(l))

#define luaS_new(L, s)	(luaS_newlstr(L, s, strlen(s)))
#define luaWS_new(L, s)	(luaS_newlwstr(L, s, lua_WChar_len(s)))
#define luaS_newliteral(L, s)	(luaS_newlstr(L, "" s, \
                                 (sizeof(s)/sizeof(char))-1))

#if LUA_REFCOUNT
#define luaS_fix(s)	((s)->tsv.marked |= (1<<4), s->tsv.ref = 1)
#else
#define luaS_fix(s)	((s)->tsv.marked |= (1<<4))
#endif /* LUA_REFCOUNT */

void luaS_resize (lua_State *L, int newsize);
Udata *luaS_newudata (lua_State *L, size_t s);
void luaS_freeall (lua_State *L);
TString *luaS_newlstr (lua_State *L, const char *str, size_t l);
TString *luaS_newlwstr (lua_State *L, const lua_WChar *str, size_t l);
NAMESPACE_LUA_END

#endif
