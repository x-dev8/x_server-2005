/*
** $Id: ldump.c,v 1.4 2003/02/11 23:52:12 lhf Exp $
** save bytecodes
** See Copyright Notice in lua.h
*/

#include <stddef.h>

#define ldump_c

#include "lua.h"

#include "lobject.h"
#include "lopcodes.h"
#include "lstate.h"
#include "lundump.h"
#include "lmem.h"

NAMESPACE_LUA_BEGIN

//#define DumpVector(b,n,size,D)	DumpBlock(b,(n)*(size),D)
#define DumpLiteral(s,D)	(*D->write)(D->L,"" s,(sizeof(s))-1,D->data)
  
typedef struct {
 lua_State* L;
 lua_Chunkwriter write;
 void* data;
 int swap;
 char endian;
 Mbuffer b;
} DumpState;

static void DumpVector(const void* b, int m, size_t size, DumpState* D)
{
  lua_unlock(D->L);
  if (D->swap)
  {
    char* origSwapBuffer=luaZ_openspace(D->L,&D->b,m*size);
    char* swapBuffer = origSwapBuffer;
    char* q=(char*) b;
	int origm = m;
    while (m--)
    {
      char* p =(char*) q+size-1;
      while (p >= q)
        *swapBuffer++ = *p--;
      q+=size;
	}
    (*D->write)(D->L,origSwapBuffer,origm*size,D->data);
 }
 else
 {
   (*D->write)(D->L,b,m*size,D->data);
 }
 lua_lock(D->L);
}

static void DumpBlock(const void* b, size_t size, DumpState* D)
{
 lua_unlock(D->L);
 if (D->swap)
 {
   char* origSwapBuffer=luaZ_openspace(D->L,&D->b,size);
   char* swapBuffer = origSwapBuffer;
   char* p =(char*) b+size-1;
   while (p >= (char*)b)
     *swapBuffer++ = *p--;
   (*D->write)(D->L,origSwapBuffer,size,D->data);
 }
 else
 {
   (*D->write)(D->L,b,size,D->data);
 }
 lua_lock(D->L);
}

static void DumpByte(int y, DumpState* D)
{
 char x=(char)y;
 DumpBlock(&x,sizeof(x),D);
}

static void DumpInt(int x, DumpState* D)
{
 DumpBlock(&x,sizeof(x),D);
}

static void DumpSize(size_t x, DumpState* D)
{
 DumpBlock(&x,sizeof(x),D);
}

static void DumpNumber(lua_Number x, DumpState* D)
{
 DumpBlock(&x,sizeof(x),D);
}

static void DumpString(TString* s, DumpState* D)
{
 if (s==NULL || getstr(s)==NULL)
  DumpSize(0,D);
 else
 {
  size_t size=s->tsv.len+1;		/* include trailing '\0' */
  DumpSize(size,D);
/*  DumpBlock(getstr(s),size,D); */
  (*D->write)(D->L,getstr(s),size,D->data);
 }
}

static void DumpWString(TString* s, DumpState* D)
{
 if (s==NULL || getwstr(s)==NULL)
  DumpSize(0,D);
 else
 {
  size_t size=s->tsv.len+1;		/* include trailing '\0' */
  DumpSize(size,D);
/*  DumpBlock(getwstr(s),size * 2,D);*/
  DumpVector(getwstr(s),size,2,D);
 }
}

static void DumpCode(const Proto* f, DumpState* D)
{
 DumpInt(f->sizecode,D);
 DumpVector(f->code,f->sizecode,sizeof(*f->code),D);
}

static void DumpLocals(const Proto* f, DumpState* D)
{
 int i,n=f->sizelocvars;
 DumpInt(n,D);
 for (i=0; i<n; i++)
 {
  DumpString(f->locvars[i].varname,D);
  DumpInt(f->locvars[i].startpc,D);
  DumpInt(f->locvars[i].endpc,D);
 }
}

static void DumpLines(const Proto* f, DumpState* D)
{
 DumpInt(f->sizelineinfo,D);
 DumpVector(f->lineinfo,f->sizelineinfo,sizeof(*f->lineinfo),D);
}

static void DumpUpvalues(const Proto* f, DumpState* D)
{
 int i,n=f->sizeupvalues;
 DumpInt(n,D);
 for (i=0; i<n; i++) DumpString(f->upvalues[i],D);
}

static void DumpFunction(const Proto* f, const TString* p, DumpState* D);

static void DumpConstants(const Proto* f, DumpState* D)
{
 int i,n;
 DumpInt(n=f->sizek,D);
 for (i=0; i<n; i++)
 {
  const TObject* o=&f->k[i];
  DumpByte(ttype(o),D);
  switch (ttype(o))
  {
   case LUA_TNUMBER:
	DumpNumber(nvalue(o),D);
	break;
   case LUA_TSTRING:
	DumpString(tsvalue(o),D);
	break;
   case LUA_TWSTRING:
	DumpWString(tsvalue(o),D);
	break;
   case LUA_TNIL:
	break;
   default:
	lua_assert(0);			/* cannot happen */
	break;
  }
 }
 DumpInt(n=f->sizep,D);
 for (i=0; i<n; i++) DumpFunction(f->p[i],f->source,D);
}

static void DumpFunction(const Proto* f, const TString* p, DumpState* D)
{
 DumpString((f->source==p) ? NULL : f->source,D);
 DumpInt(f->lineDefined,D);
 DumpByte(f->nups,D);
 DumpByte(f->numparams,D);
 DumpByte(f->is_vararg,D);
 DumpByte(f->maxstacksize,D);
 DumpLines(f,D);
 DumpLocals(f,D);
 DumpUpvalues(f,D);
 DumpConstants(f,D);
 DumpCode(f,D);
}

static void DumpHeader(DumpState* D)
{
 char endianness = (char)((D->endian == '=') ? luaU_endianness() : ((D->endian == '<') ? 1 : 0));
 DumpLiteral(LUA_SIGNATURE,D);
 DumpByte(VERSION,D);
 DumpByte(endianness,D);
 DumpByte(sizeof(int),D);
 DumpByte(sizeof(unsigned int),D);
 DumpByte(sizeof(Instruction),D);
 DumpByte(SIZE_OP,D);
 DumpByte(SIZE_A,D);
 DumpByte(SIZE_B,D);
 DumpByte(SIZE_C,D);
 DumpByte(sizeof(lua_Number),D);
 DumpNumber(TEST_NUMBER,D);
}

#define	OP_LITTLEENDIAN	'<'		/* little endian */
#define	OP_BIGENDIAN	'>'		/* big endian */
#define	OP_NATIVE	'='		/* native endian */

static int doendian(int c)
{
 int x=1;
 int e=*(char*)&x;
 if (c==OP_LITTLEENDIAN) return !e;
 if (c==OP_BIGENDIAN) return e;
 if (c==OP_NATIVE) return 0;
 return 0;
}

/*
** dump function as precompiled chunk
*/
void luaU_dump (lua_State* L, const Proto* Main, lua_Chunkwriter w, void* data, char endian)
{
 DumpState D;
 D.L=L;
 D.write=w;
 D.data=data;
 D.swap=doendian(endian);
 D.endian=endian;
 luaZ_initbuffer(L, &D.b);
 DumpHeader(&D);
 DumpFunction(Main,NULL,&D);
 luaZ_freebuffer(L, &D.b);
}

NAMESPACE_LUA_END
