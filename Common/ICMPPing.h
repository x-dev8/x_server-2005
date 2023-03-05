#pragma once

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")    /* WinSockʹ�õĿ⺯�� */

/* ICMP ���� */
#define ICMP_TYPE_ECHO          8
#define ICMP_TYPE_ECHO_REPLY    0

#define ICMP_MIN_LEN            8  /* ICMP ��С����, ֻ���ײ� */
#define ICMP_DEF_COUNT          1  /* ȱʡ���ݴ��� */
#define ICMP_DEF_SIZE          32  /* ȱʡ���ݳ��� */
#define ICMP_DEF_TIMEOUT     1000  /* ȱʡ��ʱʱ��, ���� */
#define ICMP_MAX_SIZE       65500  /* ������ݳ��� */
#define ICMP_HOST_LENGTH	  128  //����ַ����

/* IP �ײ� -- RFC 791 */
struct ip_hdr
{
	unsigned char vers_len;     /* �汾���ײ����� */
	unsigned char tos;          /* �������� */
	unsigned short total_len;   /* ���ݱ����ܳ��� */
	unsigned short id;          /* ��ʶ�� */
	unsigned short frag;        /* ��־��Ƭƫ�� */
	unsigned char ttl;          /* ����ʱ�� */
	unsigned char proto;        /* Э�� */
	unsigned short checksum;    /* У��� */
	unsigned int sour;          /* Դ IP ��ַ */
	unsigned int dest;          /* Ŀ�� IP ��ַ */
};

/* ICMP �ײ� -- RFC 792 */
struct icmp_hdr
{   
	unsigned char type;         /* ���� */
	unsigned char code;         /* ���� */
	unsigned short checksum;    /* У��� */
	unsigned short id;          /* ��ʶ�� */
	unsigned short seq;         /* ���к� */

	/* ��֮��Ĳ��Ǳ�׼ ICMP �ײ�, ���ڼ�¼ʱ�� */
	unsigned long timestamp;
};

struct icmp_user_opt
{
	icmp_user_opt()
	{
		persist = 0;
		count = ICMP_DEF_COUNT;
		size = ICMP_DEF_SIZE;
		timeout = ICMP_DEF_TIMEOUT;
		memset(host,0,ICMP_HOST_LENGTH);
		send = 0;
		recv = 0;
		min_t = 0;
		max_t = 0xFFFF;
		total_t = 0;
	}
	unsigned int  persist;  /* һֱ Ping            */
	unsigned int  count;    /* ���� ECHO ��������� */
	unsigned int  size;     /* �������ݵĴ�С       */
	unsigned int  timeout;  /* �ȴ��𸴵ĳ�ʱʱ��   */
	char          host[ICMP_HOST_LENGTH]; /* ������ַ     */
	unsigned int  send;     /* ��������     */
	unsigned int  recv;     /* ��������     */
	unsigned int  min_t;    /* ���ʱ��     */
	unsigned int  max_t;    /* �ʱ��     */
	unsigned int  total_t;  /* �ܵ��ۼ�ʱ�� */
};

/* ������� */
const char icmp_rand_data[] = "abcdefghigklmnopqrstuvwxyz0123456789"
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

class CICMPPing
{
public:
	CICMPPing(void);
	~CICMPPing(void);


	unsigned short ip_checksum			(unsigned short *buf, int buf_len);
	void		   icmp_make_data		(char *icmp_data, int data_size, int sequence);
	int			   icmp_parse_reply		(char *buf, int buf_len,struct sockaddr_in *from);
	int			   icmp_process_reply	(SOCKET icmp_soc);
	void		   icmp_help			(char *prog_name);
	//void		   icmp_parse_param		(int argc, char **argv);
										//1,PING��ַ 2,���� Ping 3,������������� 4,�������ݵĴ�С 5,�ȴ����յĳ�ʱʱ�� 
	bool           InitICMP				(char* IpAddr,unsigned int persist = 0,unsigned int count = ICMP_DEF_COUNT,unsigned int size = ICMP_DEF_SIZE,unsigned int outtime = ICMP_DEF_TIMEOUT);

	int			   GetPingTime			(char* IpAddr);

private:
	icmp_user_opt user_opt_g;
};