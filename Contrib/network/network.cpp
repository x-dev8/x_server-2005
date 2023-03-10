#include <string.h>
#include "ossome.h"
#include "net_module.h"
#include "network.h"
#include "net_buf.h"
#include "memory_pool/pool.h"
#include "msg/msgbase.h"
#include "log/log.h"
#include "crosslib.h"

#ifdef WIN32
#define snprintf _snprintf
#endif

enum
{
	enum_netdata_total = 0,
	enum_netdata_now,
	enum_netdata_max,
	enum_netdata_end,
};

struct datainfo
{
	int64 sendmsgnum;
	int64 recvmsgnum;
	int64 sendbytes;
	int64 recvbytes;
};

struct datainfomgr
{
	bool isinit;
	int64 lasttime;
	struct datainfo datatable[enum_netdata_end];
};
static struct datainfomgr s_datamgr = {false};
struct infomgr
{
	bool isinit;
	struct poolmgr *socket_pool;
	LOCK_struct socket_lock;
	
	struct poolmgr *listen_pool;
	LOCK_struct listen_lock;
};
static struct infomgr s_infomgr = {false};

static inline void on_sendmsg (size_t len)
{
	assert(s_datamgr.isinit);
	s_datamgr.datatable[enum_netdata_total].sendmsgnum += 1;
	s_datamgr.datatable[enum_netdata_total].sendbytes += len;

	s_datamgr.datatable[enum_netdata_now].sendmsgnum += 1;
	s_datamgr.datatable[enum_netdata_now].sendbytes += len;
}

static inline void on_recvmsg (size_t len)
{
	assert(s_datamgr.isinit);

	s_datamgr.datatable[enum_netdata_total].recvmsgnum += 1;
	s_datamgr.datatable[enum_netdata_total].recvbytes += len;

	s_datamgr.datatable[enum_netdata_now].recvmsgnum += 1;
	s_datamgr.datatable[enum_netdata_now].recvbytes += len;
}
static void datarun ()
{
	assert(s_datamgr.isinit);
	int64 currenttime = get_millisecond();
	if (currenttime - s_datamgr.lasttime < 1000)
		return;

	s_datamgr.lasttime = currenttime;

	if (s_datamgr.datatable[enum_netdata_max].sendmsgnum < s_datamgr.datatable[enum_netdata_now].sendmsgnum)
		s_datamgr.datatable[enum_netdata_max].sendmsgnum = s_datamgr.datatable[enum_netdata_now].sendmsgnum;

	if (s_datamgr.datatable[enum_netdata_max].recvmsgnum < s_datamgr.datatable[enum_netdata_now].recvmsgnum)
		s_datamgr.datatable[enum_netdata_max].recvmsgnum = s_datamgr.datatable[enum_netdata_now].recvmsgnum;

	if (s_datamgr.datatable[enum_netdata_max].sendbytes < s_datamgr.datatable[enum_netdata_now].sendbytes)
		s_datamgr.datatable[enum_netdata_max].sendbytes = s_datamgr.datatable[enum_netdata_now].sendbytes;

	if (s_datamgr.datatable[enum_netdata_max].recvbytes < s_datamgr.datatable[enum_netdata_now].recvbytes)
		s_datamgr.datatable[enum_netdata_max].recvbytes = s_datamgr.datatable[enum_netdata_now].recvbytes;

	s_datamgr.datatable[enum_netdata_now].sendmsgnum = 0;
	s_datamgr.datatable[enum_netdata_now].recvmsgnum = 0;
	s_datamgr.datatable[enum_netdata_now].sendbytes = 0;
	s_datamgr.datatable[enum_netdata_now].recvbytes = 0;
}
static bool infomgr_init (size_t socketnum, size_t listennum)
{
	if (s_infomgr.isinit)
		return false;
	s_infomgr.socket_pool = poolmgr_create(sizeof(network::Socketer), 8, socketnum, 1, "Socketer obj pool");
	s_infomgr.listen_pool = poolmgr_create(sizeof(network::Listener), 8, listennum, 1, "Listen obj pool");
	if (!s_infomgr.socket_pool || !s_infomgr.listen_pool)
	{
		poolmgr_release(s_infomgr.socket_pool);
		poolmgr_release(s_infomgr.listen_pool);
		return false;
	}
	LOCK_INIT(&s_infomgr.socket_lock);
	LOCK_INIT(&s_infomgr.listen_lock);
	s_infomgr.isinit = true;
	s_datamgr.isinit = true;
	s_datamgr.lasttime = 0;
	for (int i = 0; i < enum_netdata_end; ++i)
	{
		s_datamgr.datatable[i].sendmsgnum = 0;
		s_datamgr.datatable[i].recvmsgnum = 0;
		s_datamgr.datatable[i].sendbytes = 0;
		s_datamgr.datatable[i].recvbytes = 0;
	}
	return true;
}

static void infomgr_release ()
{
	if (!s_infomgr.isinit)
		return;
	s_infomgr.isinit = false;
	s_datamgr.isinit = false;
	poolmgr_release(s_infomgr.socket_pool);
	poolmgr_release(s_infomgr.listen_pool);
	LOCK_DELETE(&s_infomgr.socket_lock);
	LOCK_DELETE(&s_infomgr.listen_lock);
}

namespace network{

/* ????*/
bool Listener::Listen (unsigned short port, int backlog)
{
	return listener_listen(m_self, port, backlog);
}

/* ??????????????????????????????*/
void Listener::Close ()
{
	listener_close(m_self);
}

/* ??????????????*/
bool Listener::IsClose ()
{
	return listener_isclose(m_self);
}

/* ????????????socket??????????*/
Socketer *Listener::Accept (bool bigbuf)
{
	struct socketer *sock = listener_accept(m_self, bigbuf);
	if (!sock)
		return NULL;
	LOCK_LOCK(&s_infomgr.socket_lock);
	Socketer *self = (Socketer *)poolmgr_getobject(s_infomgr.socket_pool);
	LOCK_UNLOCK(&s_infomgr.socket_lock);
	if (!self)
	{
		socketer_release(sock);
		return NULL;
	}
	self->m_self = sock;
	return self;
}

/* ??????????????????*/
bool Listener::CanAccept ()
{
	return listener_can_accept(m_self);
}

/* ??????????????????????????????????????????????????????????0??????????????*/
void Socketer::SetRecvCritical (long size)
{
	socketer_set_recv_critical(m_self, size);
}

/* ??????????????????????????????????????????????????????????????????????0??????????????*/
void Socketer::SetSendCritical (long size)
{
	socketer_set_send_critical(m_self, size);
}

/* ??????????????????????????????????????????????????????????????socket??????????????*/
void Socketer::UseCompress ()
{
	socketer_use_compress(m_self);
}

/* ????????????????????????????????????????????????????????????????????????????????*/
void Socketer::UseUncompress ()
{
	socketer_use_uncompress(m_self);
}

/* ????????/?????????? ??????????????????????/????????????????
 * ??????/??????????NULL??????????????
 * */
void Socketer::SetEncryptDecryptFunction (void (*encryptfunc)(void *logicdata, char *buf, int len), void (*decryptfunc)(void *logicdata, char *buf, int len), void *logicdata)
{
	socketer_set_other_do_function(m_self, encryptfunc, decryptfunc, logicdata);
}

/* ????????????*/
void Socketer::UseEncrypt ()
{
	socketer_use_encrypt(m_self);
}

/* ????????????*/
void Socketer::UseDecrypt ()
{
	socketer_use_decrypt(m_self);
}


/* ??????????????socket????*/
void Socketer::Close ()
{
	socketer_close(m_self);
}

/* ????????????????*/
bool Socketer::Connect (const char *ip, short port,short bind_port)
{
	return socketer_connect(m_self, ip, port,bind_port);
}

/* ????socket????????????????*/
bool Socketer::IsClose ()
{
	return socketer_isclose(m_self);
}
/* ????????????ip????*/
void Socketer::GetIP (char *ip, size_t len)
{
	socketer_getip(m_self, ip, len);
}

/* ????????????????????????????????????adddata????????pMsg??????????????????????????pMsg????????addsize????adddata??????*/
bool Socketer::SendMsg (Msg *pMsg, void *adddata, size_t addsize)
{
	if (!pMsg)
		return false;
	if (adddata && addsize == 0)
	{
		assert(false);
		return false;
	}
	if (!adddata && addsize != 0)
	{
		assert(false);
		return false;
	}
	if (pMsg->GetLength() <= (int)sizeof(int))
		return false;
	if (pMsg->GetLength() + addsize >= _MAX_MSG_LEN)
	{
		assert(false && "if (pMsg->GetLength() + addsize >= _MAX_MSG_LEN)");
		log_error("	if (pMsg->GetLength() + addsize >= _MAX_MSG_LEN)");
		return false;
	}
	if (socketer_send_islimit(m_self, pMsg->GetLength()+addsize))
	{
		Close();
		return false;
	}
	on_sendmsg(pMsg->GetLength() + addsize);
	if (adddata && addsize != 0)
	{
		bool res1, res2;
		int onesend = pMsg->GetLength();
		pMsg->SetLength(onesend + addsize);
		res1 = socketer_sendmsg(m_self, pMsg, onesend);
		
		//???????????????????? ????????????????????????????????????????????????????????????????????????????????????????????
		pMsg->SetLength(onesend);
		res2 = socketer_sendmsg(m_self, adddata, addsize);
		return (res1 && res2);
	}
	else
	{
		return socketer_sendmsg(m_self, pMsg, pMsg->GetLength());
	}
}

/* ??as3???????????? */
bool Socketer::SendPolicyData ()
{
	//as3??????????????
	char buf[512] = "<cross-domain-policy> <allow-access-from domain=\"*\" secure=\"false\" to-ports=\"*\"/> </cross-domain-policy> ";
	size_t datasize = strlen(buf);
	if (socketer_send_islimit(m_self, datasize))
	{
		Close();
		return false;
	}
	on_sendmsg(datasize + 1);
	return socketer_sendmsg(m_self, buf, datasize+1);
}

/* ??????????????????*/
void Socketer::CheckSend ()
{
	socketer_checksend(m_self);
}

/* ????????????????*/
void Socketer::CheckRecv ()
{
	socketer_checkrecv(m_self);
}

/* ????????*/
Msg *Socketer::GetMsg (char *buf, size_t bufsize)
{
	Msg *obj = (Msg *)socketer_getmsg(m_self, buf, bufsize);
	if (obj)
	{
		if (obj->GetLength() < (int)sizeof(Msg))
		{
			Close();
			return NULL;
		}
		on_recvmsg(obj->GetLength());
	}
	return obj;
}

void Socketer::SetFlagName(const char* flagChar)
{
	setflagname(m_self,flagChar);
}



/* ????????????
 * bigbufsize????????????????bigbufnum????????????????
 * smallbufsize????????????????smallbufnum??????????????
 * listen num????????????????????????????socket num????????????????
 * threadnum??????????????????????????????????0??????????cpu??????????????
 */
bool net_init (size_t bigbufsize, size_t bigbufnum, size_t smallbufsize, size_t smallbufnum,
		size_t listenernum, size_t socketnum, int threadnum)
{
	if (!infomgr_init(socketnum, listenernum))
		return false;
	if (!netinit(bigbufsize, bigbufnum, smallbufsize, smallbufnum,
			listenernum, socketnum, threadnum))
	{
		infomgr_release();
		return false;
	}
	return true;
}

/* ??????????????????????*/
Listener *Listener_create ()
{
	if (!s_infomgr.isinit)
	{
		assert(false && "Listener_create not init!");
		return NULL;
	}
	struct listener *ls = listener_create();
	if (!ls)
		return NULL;
	LOCK_LOCK(&s_infomgr.listen_lock);
	Listener *self = (Listener *)poolmgr_getobject(s_infomgr.listen_pool);
	LOCK_UNLOCK(&s_infomgr.listen_lock);
	if (!self)
	{
		listener_release(ls);
		return NULL;
	}
	self->m_self = ls;
	return self;
}

/* ??????????????????????*/
void Listener_release (Listener *self)
{
	if (!self)
		return;
	if (self->m_self)
	{
		listener_release(self->m_self);
		self->m_self = NULL;
	}
	LOCK_LOCK(&s_infomgr.listen_lock);
	poolmgr_freeobject(s_infomgr.listen_pool, self);
	LOCK_UNLOCK(&s_infomgr.listen_lock);
}

/* ????????Socketer????*/
Socketer *Socketer_create (bool bigbuf)
{
	if (!s_infomgr.isinit)
	{
		assert(false && "Csocket_create not init!");
		return NULL;
	}
	struct socketer *so = socketer_create(bigbuf);
	if (!so)
		return NULL;
	LOCK_LOCK(&s_infomgr.socket_lock);
	Socketer *self = (Socketer *)poolmgr_getobject(s_infomgr.socket_pool);
	LOCK_UNLOCK(&s_infomgr.socket_lock);
	if (!self)
	{
		socketer_release(so);
		return NULL;
	}
	self->m_self = so;
	return self;
}

/* ????Socketer??????????????????????????????*/
void Socketer_release (Socketer *self)
{
	if (!self)
		return;
	if (self->m_self)
	{
		socketer_release(self->m_self);
		self->m_self = NULL;
	}
	LOCK_LOCK(&s_infomgr.socket_lock);
	poolmgr_freeobject(s_infomgr.socket_pool, self);
	LOCK_UNLOCK(&s_infomgr.socket_lock);
}

/* ????????????*/
void net_release ()
{
	infomgr_release();
	netrelease();
}

/* ??????????????????????????????????????*/
void net_run ()
{
	datarun();
	netrun();
}

static char s_memory_info[2*1024*1024+1024];
/* ????socket????????listen????????????????????????????????*/
const char *net_memory_info ()
{
	size_t index = 0;

	LOCK_LOCK(&s_infomgr.socket_lock);
	poolmgr_getinfo(s_infomgr.socket_pool, s_memory_info, sizeof(s_memory_info)-1);
	LOCK_UNLOCK(&s_infomgr.socket_lock);
	
	index = strlen(s_memory_info);

	LOCK_LOCK(&s_infomgr.listen_lock);
	poolmgr_getinfo(s_infomgr.listen_pool, &s_memory_info[index], sizeof(s_memory_info)-1-index);
	LOCK_UNLOCK(&s_infomgr.listen_lock);

	index = strlen(s_memory_info);
	netmemory_info(&s_memory_info[index], sizeof(s_memory_info)-1-index);
	return s_memory_info;
}

/* ??????????????????*/
const char *net_datainfo ()
{
	static char infostr[1024*64];
	if (!s_datamgr.isinit)
		return "not init!";

	double numunit = 1000*1000;
	double bytesunit = 1024*1024;
	double totalsendmsgnum = (double)(s_datamgr.datatable[enum_netdata_total].sendmsgnum / numunit);
	double totalsendbytes = double(s_datamgr.datatable[enum_netdata_total].sendbytes / bytesunit);
	double totalrecvmsgnum = (double)(s_datamgr.datatable[enum_netdata_total].recvmsgnum / numunit);
	double totalrecvbytes = double(s_datamgr.datatable[enum_netdata_total].recvbytes / bytesunit);

	double maxsendmsgnum = (double)(s_datamgr.datatable[enum_netdata_max].sendmsgnum);
	double maxsendbytes = double(s_datamgr.datatable[enum_netdata_max].sendbytes / bytesunit);
	double maxrecvmsgnum = (double)(s_datamgr.datatable[enum_netdata_max].recvmsgnum);
	double maxrecvbytes = double(s_datamgr.datatable[enum_netdata_max].recvbytes / bytesunit);

	double nowsendmsgnum = (double)(s_datamgr.datatable[enum_netdata_now].sendmsgnum);
	double nowsendbytes = double(s_datamgr.datatable[enum_netdata_now].sendbytes / bytesunit);
	double nowrecvmsgnum = (double)(s_datamgr.datatable[enum_netdata_now].recvmsgnum);
	double nowrecvbytes = double(s_datamgr.datatable[enum_netdata_now].recvbytes / bytesunit);

	snprintf(infostr, sizeof(infostr) - 1, "total:\nsend msg num:%lfM, send bytes:%lfMB, recv msg num:%lfM, recv bytes:%lfMB\nmax:\nsend msg num:%lf, send bytes:%lfMB, recv msg num:%lf, recv bytes:%lfMB\nnow:\nsend msg num:%lf, send bytes:%lfMB, recv msg num:%lf, recv bytes:%lfMB\n", totalsendmsgnum, totalsendbytes, totalrecvmsgnum, totalrecvbytes, maxsendmsgnum, maxsendbytes, maxrecvmsgnum, maxrecvbytes, nowsendmsgnum, nowsendbytes, nowrecvmsgnum, nowrecvbytes);

	return infostr;
}

}

