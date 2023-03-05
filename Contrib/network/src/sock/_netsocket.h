#ifndef _H__NETSOCKET_H_
#define _H__NETSOCKET_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stddef.h>
#include "span/alway_inline.h"
#include "net_crypt.h"

struct socketer;

/* get socket object size. */
size_t socketer_getsize ();

/* 
 * create socketer. 
 * bigbuf --- if is true, then is bigbuf; or else is smallbuf.
 */
struct socketer *socketer_create (bool bigbuf);

struct socketer *socketer_create_for_accept (bool bigbuf, void *sockfd);

/* release socketer */
void socketer_release (struct socketer *self);

bool socketer_connect (struct socketer *self, const char *ip, short port,short bind_port);

void socketer_close (struct socketer *self);

bool socketer_isclose (struct socketer *self);

void socketer_getip (struct socketer *self, char *ip, size_t len);
bool socketer_gethostname (char *name, size_t len);

bool socketer_sendmsg (struct socketer *self, void *data, int len);

/* 
 * when sending data. test send limit as len.
 * if return true, close this connect.
 */
bool socketer_send_islimit (struct socketer *self, size_t len);

/* set send event. */
void socketer_checksend (struct socketer *self);

void *socketer_getmsg (struct socketer *self, char *buf, size_t bufsize);

/* set recv event. */
void socketer_checkrecv (struct socketer *self);

void setflagname(struct socketer *self,const char* flagname);
//bool logsocketclose(struct socketer *self);

/* set recv data limit. */
void socketer_set_recv_critical (struct socketer *self, long size);

/* set send data limit.*/
void socketer_set_send_critical (struct socketer *self, long size);

void socketer_use_compress (struct socketer *self);

void socketer_use_uncompress (struct socketer *self);

/* set encrypt and decrypt function and logic data. */
void socketer_set_other_do_function (struct socketer *self, dofunc_f encrypt_func, dofunc_f decrypt_func, void *logicdata);

void socketer_use_encrypt (struct socketer *self);

void socketer_use_decrypt (struct socketer *self);

void socketer_use_tgw (struct socketer *self);

void socketer_set_raw_datasize (struct socketer *self, size_t size);
/* interface for event mgr. */

void socketer_on_recv (struct socketer *self, int len);

void socketer_on_send (struct socketer *self, int len);

/* create and init socketer manager. */
bool socketmgr_init ();

/* run socketer manager. */
void socketmgr_run ();

/* release socketer manager. */
void socketmgr_release ();

#ifdef __cplusplus
}
#endif
#endif

