/*
** $Id: lzio.c,v 1.24 2003/03/20 16:00:56 roberto Exp $
** a generic input stream interface
** See Copyright Notice in lua.h
*/


#include <string.h>

#define lzio_c

#include "lua.h"

#include "llimits.h"
#include "lmem.h"
#include "lzio.h"
#include "lstate.h"

NAMESPACE_LUA_BEGIN

int luaZ_fill (ZIO *z) {
  size_t size;
  const char *buff = z->reader(NULL, z->data, &size);
  if (buff == NULL || size == 0) return EOZ;
  z->n = size - 1;
  z->p = buff;
  return char2int(*(z->p++));
}


int luaZ_lookahead (ZIO *z) {
  if (z->n == 0) {
    int c = luaZ_fill(z);
    if (c == EOZ) return c;
    z->n++;
    z->p--;
  }
  return char2int(*z->p);
}


int luaZ_lookahead_2 (ZIO *z) {
  union
  {
	lua_WChar w;
	unsigned char b[2];
  } s;
  if (z->n == 0) {
    int c = luaZ_fill(z);
    if (c == EOZ) return c;
    z->n++;
    z->p--;
  }
  s.b[0] = *(z->p);
  s.b[1] = *(z->p + 1);
  return s.w;
}


void luaZ_init (ZIO *z, lua_Chunkreader reader, void *data, const char *name) {
  z->reader = reader;
  z->data = data;
  z->name = name;
  z->n = 0;
  z->p = NULL;
  z->isWide = 0;
}


/* --------------------------------------------------------------- read --- */
size_t luaZ_read (ZIO *z, void *b, size_t n) {
  while (n) {
    size_t m;
    if (z->n == 0) {
      if (luaZ_fill(z) == EOZ)
        return n;  /* return number of missing bytes */
      else {
        ++z->n;  /* filbuf removed first byte; put back it */
        --z->p;
      }
    }
    m = (n <= z->n) ? n : z->n;  /* min. between n and z->n */
    memcpy(b, z->p, m);
    z->n -= m;
    z->p += m;
    b = (char *)b + m;
    n -= m;
  }
  return 0;
}

/* ------------------------------------------------------------------------ */
char *luaZ_openspace (lua_State *L, Mbuffer *buff, size_t n) {
  if (n > buff->buffsize) {
    unsigned long oldAllocFlags = L->allocFlags;
    if (n < LUA_MINBUFFER) n = LUA_MINBUFFER;
	luaM_setname(L, "Lua_buffer");
	L->allocFlags = LUA_ALLOC_TEMP;
    luaM_reallocvector(L, buff->buffer, buff->buffsize, n, char);
	L->allocFlags = oldAllocFlags;
    buff->buffsize = n;
  }
  return buff->buffer;
}

NAMESPACE_LUA_END
