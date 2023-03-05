#ifndef _H_NET_SOCKET_H_
#define _H_NET_SOCKET_H_

#include <stddef.h>

struct Msg;
struct socketer;
struct listener;

namespace network {

	class Socketer;

	/* listener����*/
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
		/* ����*/
		bool Listen (unsigned short port, int backlog);

		/* �ر����ڼ������׽��֣�ֹͣ����*/
		void Close ();

		/* �����Ƿ��ѹر�*/
		bool IsClose ();

		/* ��ָ���ļ���socket�Ͻ�������*/
		Socketer *Accept (bool bigbuf=false);

		/* ����Ƿ����µ�����*/
		bool CanAccept ();
	public:
		struct listener *m_self;
	};
	/* socketer����*/
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
		/* ���ý��������ֽڵ��ٽ�ֵ��������ֵ����ֹͣ���գ���С�ڵ���0������Ϊ������*/
		void SetRecvCritical (long size);

		/* ���÷��������ֽڵ��ٽ�ֵ�������������ݳ��ȴ��ڴ�ֵ����Ͽ������ӣ���Ϊ0������Ϊ������*/
		void SetSendCritical (long size);

		/* ���Է������������ã���������ѹ������Ҫ����ѹ������˺����ڴ���socket����󼴿̵���*/
		void UseCompress ();

		/* �����ã����Խ��յ����������ã����ý�ѹ���������Ḻ���ѹ�������������ͻ���ʹ��*/
		void UseUncompress ();

		/* ���ü���/���ܺ����� �Լ�������;�Ĳ������/�����߼������ݡ�
		* ������/���ܺ���ΪNULL���򱣳�Ĭ�ϡ�
		* */
		void SetEncryptDecryptFunction (void (*encryptfunc)(void *logicdata, char *buf, int len), void (*decryptfunc)(void *logicdata, char *buf, int len), void *logicdata);

		/* �����ü��ܣ�*/
		void UseEncrypt ();

		/* �����ý��ܣ�*/
		void UseDecrypt ();


		/* �ر��������ӵ�socket����*/
		void Close ();

		/* ����ָ���ķ�����*/
		bool Connect (const char *ip, short port,short bind_port = 0);

		/* ����socket�׽����Ƿ��ѹر�*/
		bool IsClose ();

		/* ��ȡ�˿ͻ���ip��ַ*/
		void GetIP (char *ip, size_t len);

		/* �������ݣ������ǰ�����ѹ��������У�adddataΪ���ӵ�pMsg��������ݣ���Ȼ���Զ��޸�pMsg�ĳ��ȣ�addsizeָ��adddata�ĳ���*/
		bool SendMsg (Msg *pMsg, void *adddata = 0, size_t addsize = 0);

		/* ��as3���Ͳ����ļ� */
		bool SendPolicyData ();

		/* ���������ķ�������*/
		void CheckSend ();

		/* ����Ͷ�ݽ��ղ���*/
		void CheckRecv ();

		/* ��������*/
		Msg *GetMsg (char *buf = 0, size_t bufsize = 0);

		//�������ӱ��
		void SetFlagName(const char* flagChar);
	public:
		struct socketer *m_self;
	};

	/* ��ʼ�����磬
	* bigbufsizeָ�����Ĵ�С��bigbufnumָ��������Ŀ��
	* smallbufsizeָ��С��Ĵ�С��smallbufnumָ��С�����Ŀ
	* listen numָ�����ڼ������׽��ֵ���Ŀ��socket num�������ӵ�����Ŀ
	* threadnumָ�������߳���Ŀ��������ΪС�ڵ���0����Ὺ��cpu�������߳���Ŀ
	*/
	bool net_init (size_t bigbufsize, size_t bigbufnum, size_t smallbufsize, size_t smallbufnum, size_t listenernum, size_t socketnum, int threadnum);

	/* ����һ�����ڼ����Ķ���*/
	Listener *Listener_create ();

	/* �ͷ�һ�����ڼ����Ķ���*/
	void Listener_release (Listener *self);

	/* ����һ��Socketer����*/
	Socketer *Socketer_create (bool bigbuf = false);

	/* �ͷ�Socketer���󣬻��Զ����ùرյ��ƺ����*/
	void Socketer_release (Socketer *self);

	/* �ͷ��������*/
	void net_release ();

	/* ִ����ز�������Ҫ�����߼��е��ô˺���*/
	void net_run ();

	/* ��ȡsocket����أ�listen����أ����أ�С��ص�ʹ�����*/
	const char *net_memory_info ();

/* ��ȡ�����ͨѶ����*/
const char *net_datainfo ();
}

#endif /*_H_NET_SOCKET_H_*/