#pragma once

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")    /* WinSock使用的库函数 */

/* ICMP 类型 */
#define ICMP_TYPE_ECHO          8
#define ICMP_TYPE_ECHO_REPLY    0

#define ICMP_MIN_LEN            8  /* ICMP 最小长度, 只有首部 */
#define ICMP_DEF_COUNT          1  /* 缺省数据次数 */
#define ICMP_DEF_SIZE          32  /* 缺省数据长度 */
#define ICMP_DEF_TIMEOUT     1000  /* 缺省超时时间, 毫秒 */
#define ICMP_MAX_SIZE       65500  /* 最大数据长度 */
#define ICMP_HOST_LENGTH	  128  //最大地址长度

/* IP 首部 -- RFC 791 */
struct ip_hdr
{
	unsigned char vers_len;     /* 版本和首部长度 */
	unsigned char tos;          /* 服务类型 */
	unsigned short total_len;   /* 数据报的总长度 */
	unsigned short id;          /* 标识符 */
	unsigned short frag;        /* 标志和片偏移 */
	unsigned char ttl;          /* 生存时间 */
	unsigned char proto;        /* 协议 */
	unsigned short checksum;    /* 校验和 */
	unsigned int sour;          /* 源 IP 地址 */
	unsigned int dest;          /* 目的 IP 地址 */
};

/* ICMP 首部 -- RFC 792 */
struct icmp_hdr
{   
	unsigned char type;         /* 类型 */
	unsigned char code;         /* 代码 */
	unsigned short checksum;    /* 校验和 */
	unsigned short id;          /* 标识符 */
	unsigned short seq;         /* 序列号 */

	/* 这之后的不是标准 ICMP 首部, 用于记录时间 */
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
	unsigned int  persist;  /* 一直 Ping            */
	unsigned int  count;    /* 发送 ECHO 请求的数量 */
	unsigned int  size;     /* 发送数据的大小       */
	unsigned int  timeout;  /* 等待答复的超时时间   */
	char          host[ICMP_HOST_LENGTH]; /* 主机地址     */
	unsigned int  send;     /* 发送数量     */
	unsigned int  recv;     /* 接收数量     */
	unsigned int  min_t;    /* 最短时间     */
	unsigned int  max_t;    /* 最长时间     */
	unsigned int  total_t;  /* 总的累计时间 */
};

/* 随机数据 */
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
										//1,PING地址 2,持续 Ping 3,发送请求的数量 4,发送数据的大小 5,等待接收的超时时间 
	bool           InitICMP				(char* IpAddr,unsigned int persist = 0,unsigned int count = ICMP_DEF_COUNT,unsigned int size = ICMP_DEF_SIZE,unsigned int outtime = ICMP_DEF_TIMEOUT);

	int			   GetPingTime			(char* IpAddr);

private:
	icmp_user_opt user_opt_g;
};