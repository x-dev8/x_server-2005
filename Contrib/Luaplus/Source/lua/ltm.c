/*
** $Id: ltm.c,v 1.105 2002/12/04 17:38:31 roberto Exp $
** Tag methods
** See Copyright Notice in lua.h
*/


#include <string.h>

#define ltm_c

#include "lua.h"

#include "lmem.h"
#include "lobject.h"
#include "lstate.h"
#include "lstring.h"
#include "ltable.h"
#include "ltm.h"

NAMESPACE_LUA_BEGIN

const char *const luaT_typenames[] = {
  "nil", "boolean", "userdata", "number",
  "string", "table", "function", "userdata", "thread",
  "wstring"
};


void luaT_init (lua_State *L) {
  static const char *const luaT_eventname[] = {  /* ORDER TM */
    "__index", "__newindex",
    "__gc", "__mode", "__eq",
    "__add", "__sub", "__mul", "__div",
    "__pow", "__unm", "__lt", "__le",
    "__concat", "__call"
  };
  int i;
  for (i=0; i<TM_N; i++) {
    G(L)->tmname[i] = luaS_new(L, luaT_eventname[i]);
    luaS_fix(G(L)->tmname[i]);  /* never collect these names */
  }
}


/*
** function to be used with macro "fasttm": optimized for absence of
** tag methods
*/
const TObject *luaT_gettm (Table *events, TMS event, TString *ename) {
  const TObject *tm = luaH_getstr(events, ename);
  lua_assert(event <= TM_EQ);
  if (ttisnil(tm)) {  /* no tag method? */
    events->flags |= cast(lu_byte, 1u<<event);  /* cache this fact */
    return NULL;
  }
  else return tm;
}


const TObject *luaT_gettmbyobj (lua_State *L, const TObject *o, TMS event) {
  TString *ename = G(L)->tmname[event];
  switch (ttype(o)) {
    case LUA_TTABLE:
      return luaH_getstr(hvalue(o)->metatable, ename);
    case LUA_TUSERDATA:
      return luaH_getstr(uvalue(o)->uv.metatable, ename);
    default:
      return defaultmetatypes(L, ttype(o));
  }
}


Table* luaT_getmetatable(lua_State *L, const TObject *o)
{
  switch (ttype(o))
  {
    case LUA_TTABLE:
      return hvalue(o)->metatable;
    case LUA_TUSERDATA:
      return uvalue(o)->uv.metatable;
    default:
      return hvalue(defaultmetatypes(L, ttype(o)));
  }
}


void luaT_setmetatable(lua_State *L, StkId o, Table *h)
{
  switch (ttype(o))
  {
    case LUA_TTABLE:
	  if (iscollectable(h))
        lua_addreftable(h);
	  if (hvalue(o)->metatable)
        lua_releasetable(L, hvalue(o)->metatable);
      hvalue(o)->metatable = h;
      break;
    case LUA_TUSERDATA:
	  if (iscollectable(h))
        lua_addreftable(h);
	  if (uvalue(o)->uv.metatable)
	    lua_releasetable(L, uvalue(o)->uv.metatable);
      uvalue(o)->uv.metatable = h;
      break;
    default:
      sethvalue(defaultmetatypes(L, ttype(o)), h);
      break;
  }
}


NAMESPACE_LUA_END
