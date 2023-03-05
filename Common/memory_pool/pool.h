#ifndef _H_C_POOL_C_H_
#define _H_C_POOL_C_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stddef.h>

struct poolmgr;

/*
 * create poolmgr.
 * size is block size,
 * alignment is align number,
 * num is initialize block num,
 * next_multiple is next num, the next num is num * next_multiple, if next_multiple is zero, then only has one sub pool. 
 * name is poolmgr name.
 */
struct poolmgr *poolmgr_create (size_t size, size_t alignment, size_t num, size_t next_multiple, const char *name);

void *poolmgr_getobject (struct poolmgr *self);

void poolmgr_freeobject (struct poolmgr *self, void *bk);

void poolmgr_release (struct poolmgr *self);

void poolmgr_getinfo (struct poolmgr *self, char *buf, size_t bufsize);

#ifdef __cplusplus
}
#endif
#endif


