#ifndef _H_NET_SOCKET_H_
#define _H_NET_SOCKET_H_

#include <stddef.h>

struct Msg;
struct socketer;
struct listener;

namespace network {

	class Socketer;

	/* listener对象*/
	class Listener
	{
	private:
		Listener (const Listener&);
		Listener &operator = (const Listener&);
		void *operator new[](size_t count);
		void operator delete[](void *p, size_t count);
		Listener();
		~Listener();
		void *operator new(size_t size);
		void operator delete(void *p);
	public:
		/* 监听*/
		bool Listen (unsigned short port, int backlog);

		/* 关闭用于监听的套接字，停止监听*/
		void Close ();

		/* 测试是否已关闭*/
		bool IsClose ();

		/* 在指定的监听socket上接受连接*/
		Socketer *Accept (bool bigbuf=false);

		/* 检测是否有新的连接*/
		bool CanAccept ();
	public:
		struct listener *m_self;
	};
	/* socketer对象*/
	class Socketer
	{
	private:
		Socketer (const Socketer&);
		Socketer &operator = (const Socketer&);
		void *operator new[](size_t count);
		void operator delete[](void *p, size_t count);
		void *operator new(size_t size);
		void operator delete(void *p);
		Socketer();
		~Socketer();
	public:
		/* 设置接收数据字节的临界值，超过此值，则停止接收，若小于等于0，则视为不限制*/
		void SetRecvCritical (long size);

		/* 设置发送数据字节的临界值，若缓冲中数据长度大于此值，则断开此连接，若为0，则视为不限制*/
		void SetSendCritical (long size);

		/* （对发送数据起作用）设置启用压缩，若要启用压缩，则此函数在创建socket对象后即刻调用*/
		void UseCompress ();

		/* （慎用）（对接收的数据起作用）启用解压缩，网络库会负责解压缩操作，仅供客户端使用*/
		void UseUncompress ();

		/* 设置加密/解密函数， 以及特殊用途的参与加密/解密逻辑的数据。
		* 若加密/解密函数为NULL，则保持默认。
		* */
		void SetEncryptDecryptFunction (void (*encryptfunc)(void *logicdata, char *buf, int len), void (*decryptfunc)(void *logicdata, char *buf, int len), void *logicdata);

		/* （启用加密）*/
		void UseEncrypt ();

		/* （启用解密）*/
		void UseDecrypt ();


		/* 关闭用于连接的socket对象*/
		void Close ();

		/* 连接指定的服务器*/
		bool Connect (const char *ip, short port,short bind_port = 0);

		/* 测试socket套接字是否已关闭*/
		bool IsClose ();

		/* 获取此客户端ip地址*/
		void GetIP (char *ip, size_t len);

		/* 发送数据，仅仅是把数据压入包队列中，adddata为附加到pMsg后面的数据，当然会自动修改pMsg的长度，addsize指定adddata的长度*/
		bool SendMsg (Msg *pMsg, void *adddata = 0, size_t addsize = 0);

		/* 对as3发送策略文件 */
		bool SendPolicyData ();

		/* 触发真正的发送数据*/
		void CheckSend ();

		/* 尝试投递接收操作*/
		void CheckRecv ();

		/* 接收数据*/
		Msg *GetMsg (char *buf = 0, size_t bufsize = 0);

		//设置连接标记
		void SetFlagName(const char* flagChar);
	public:
		struct socketer *m_self;
	};

	/* 初始化网络，
	* bigbufsize指定大块的大小，bigbufnum指定大块的数目，
	* smallbufsize指定小块的大小，smallbufnum指定小块的数目
	* listen num指定用于监听的套接字的数目，socket num用于连接的总数目
	* threadnum指定网络线程数目，若设置为小于等于0，则会开启cpu个数的线程数目
	*/
	bool net_init (size_t bigbufsize, size_t bigbufnum, size_t smallbufsize, size_t smallbufnum, size_t listenernum, size_t socketnum, int threadnum);

	/* 创建一个用于监听的对象*/
	Listener *Listener_create ();

	/* 释放一个用于监听的对象*/
	void Listener_release (Listener *self);

	/* 创建一个Socketer对象*/
	Socketer *Socketer_create (bool bigbuf = false);

	/* 释放Socketer对象，会自动调用关闭等善后操作*/
	void Socketer_release (Socketer *self);

	/* 释放网络相关*/
	void net_release ();

	/* 执行相关操作，需要在主逻辑中调用此函数*/
	void net_run ();

	/* 获取socket对象池，listen对象池，大块池，小块池的使用情况*/
	const char *net_memory_info ();

/* 获取网络库通讯详情*/
const char *net_datainfo ();
}

#endif /*_H_NET_SOCKET_H_*/