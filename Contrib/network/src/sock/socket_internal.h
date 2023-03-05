#ifndef _H_SOCKET_INTERNAL_H_
#define _H_SOCKET_INTERNAL_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "net_common.h"
#include "configtype.h"

#ifdef WIN32
struct overlappedstruct
{
	OVERLAPPED m_overlap;				/* overlap struct. */
	int m_event;						/* event type for iocp. */
};
#endif

struct net_buf;
struct socketer
{
#ifdef WIN32
	struct overlappedstruct recv_event;
	struct overlappedstruct send_event;
#else
	volatile int events;				/* for epoll event.*/
#endif

	net_socket sockfd;					/* socket fd. */
	int64 closetime;					/* close time. */
	struct socketer *next;
	struct net_buf *recvbuf;
	struct net_buf *sendbuf;

	volatile long already_event;		/* if 0, then do not join. if 1, is added. */

	volatile long sendlock;				/* if 0, then not set send event. if 1, already set. */
	volatile long recvlock;				/* if 0, then not set recv event. if 1, already set. */
	volatile bool deleted;				/* delete flag. */
	volatile bool connected;			/* connect flag. */
	bool bigbuf;						/* if true, then is bigbuf */
	volatile long ref;					/* the socketer object reference number */
	char flagname[4];
};

#ifdef __cplusplus
}
#endif
#endif

