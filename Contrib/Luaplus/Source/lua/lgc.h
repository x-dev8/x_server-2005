/*
** $Id: lgc.h,v 1.19a 2003/02/28 19:45:15 roberto Exp $
** Garbage Collector
** See Copyright Notice in lua.h
*/

#ifndef lgc_h
#define lgc_h


#include "lobject.h"
#include "lstate.h"

NAMESPACE_LUA_BEGIN

#define luaC_checkGC(L) { lua_assert(!(L->ci->state & CI_CALLING)); \
	if (G(L)->nblocks >= G(L)->GCthreshold) luaC_collectgarbage(L); }

typedef struct GCState {
  GCObject *tmark;  /* list of marked objects to be traversed */
  GCObject *wk;  /* list of traversed key-weak tables (to be cleared) */
  GCObject *wv;  /* list of traversed value-weak tables */
  GCObject *wkv;  /* list of traversed key-value weak tables */
  global_State *g;
  lua_State* L;
} GCState;

size_t luaC_separateudata (lua_State *L);
void luaC_callGCTM (lua_State *L);
void luaC_sweep (lua_State *L, int all);
void luaC_collectgarbage (lua_State *L);
void luaC_link (lua_State *L, GCObject *o, lu_byte tt);

void reallymarkobject (GCState *st, GCObject *o);

NAMESPACE_LUA_END

#endif
