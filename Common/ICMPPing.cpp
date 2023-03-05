#include "ICMPPing.h"


CICMPPing::CICMPPing(void)
{
}


CICMPPing::~CICMPPing(void)
{
}



/**************************************************************************
 *
 * 函数功能: 计算校验和.
 *
 * 参数说明: [IN] buf, 数据缓冲区;
 *           [IN] buf_len, buf 的字节长度.
 *
 * 返 回 值: 校验和.
 *
 **************************************************************************/
unsigned short CICMPPing::ip_checksum(unsigned short *buf, int buf_len)
{
	unsigned long checksum = 0;

	while (buf_len > 1)
	{
		checksum += *buf++;
		buf_len -= sizeof(unsigned short);
	}

	if (buf_len)
	{
		checksum += *(unsigned char *)buf;
	}

	checksum = (checksum >> 16) + (checksum & 0xffff);
	checksum += (checksum >> 16);

	return (unsigned short)(~checksum);
}

/**************************************************************************
 *
 * 函数功能: 构造 ICMP 数据.
 *
 * 参数说明: [IN, OUT] icmp_data, ICMP 缓冲区;
 *           [IN] data_size, icmp_data 的长度;
 *           [IN] sequence, 序列号.
 *
 * 返 回 值: void.
 *
 **************************************************************************/
void CICMPPing::icmp_make_data(char *icmp_data, int data_size, int sequence)
{   
    struct icmp_hdr *icmp_hdr;
    char *data_buf;
    int data_len;
    int fill_count = sizeof(icmp_rand_data) / sizeof(icmp_rand_data[0]);

    /* 填写 ICMP 数据 */
    data_buf = icmp_data + sizeof(struct icmp_hdr);
    data_len = data_size - sizeof(struct icmp_hdr);
    
    while (data_len > fill_count)
    {
        memcpy(data_buf, icmp_rand_data, fill_count);
        data_len -= fill_count;
    }

    if (data_len > 0)
        memcpy(data_buf, icmp_rand_data, data_len);

    /* 填写 ICMP 首部 */
    icmp_hdr = (struct icmp_hdr *)icmp_data;

    icmp_hdr->type = ICMP_TYPE_ECHO;
    icmp_hdr->code = 0;
    icmp_hdr->id = (unsigned short)GetCurrentProcessId();
    icmp_hdr->checksum = 0;
    icmp_hdr->seq = sequence;
    icmp_hdr->timestamp = GetTickCount();

    icmp_hdr->checksum = ip_checksum((unsigned short*)icmp_data, data_size);
}

/**************************************************************************
 *
 * 函数功能: 解析接收到的数据.
 *
 * 参数说明: [IN] buf, 数据缓冲区;
 *           [IN] buf_len, buf 的长度;
 *           [IN] from, 对方的地址.
 *
 * 返 回 值: 成功返回 0, 失败返回 -1.
 *
 **************************************************************************/
int CICMPPing::icmp_parse_reply(char *buf, int buf_len,struct sockaddr_in *from)
{
    struct ip_hdr *ip_hdr;
    struct icmp_hdr *icmp_hdr;
    unsigned short hdr_len;
    int icmp_len;
    unsigned long trip_t;

    ip_hdr = (struct ip_hdr *)buf;
    hdr_len = (ip_hdr->vers_len & 0xf) << 2 ; /* IP 首部长度 */

    if (buf_len < hdr_len + ICMP_MIN_LEN)
    {    
        //printf("[Ping] Too few bytes from %s\n", inet_ntoa(from->sin_addr));
        return -1;
    }

    icmp_hdr = (struct icmp_hdr *)(buf + hdr_len);
    icmp_len = ntohs(ip_hdr->total_len) - hdr_len;

    /* 检查校验和 */
    if (ip_checksum((unsigned short *)icmp_hdr, icmp_len))
    {
        //printf("[Ping] icmp checksum error!\n");
        return -1;
    }

    /* 检查 ICMP 类型 */
    if (icmp_hdr->type != ICMP_TYPE_ECHO_REPLY)
    {    
        //printf("[Ping] not echo reply : %d\n", icmp_hdr->type);
        return -1;
    }

    /* 检查 ICMP 的 ID */
    if (icmp_hdr->id != (unsigned short)GetCurrentProcessId())
    {    
        //printf("[Ping] someone else's message!\n");
        return -1;    
    } 

    /* 输出响应信息 */
    trip_t = GetTickCount() - icmp_hdr->timestamp;
    buf_len = ntohs(ip_hdr->total_len) - hdr_len - ICMP_MIN_LEN;
    //printf("%d bytes from %s:", buf_len, inet_ntoa(from->sin_addr));
   // printf(" icmp_seq = %d  time: %d ms\n",icmp_hdr->seq, trip_t);

    user_opt_g.recv++;
    user_opt_g.total_t += trip_t;

    /* 记录返回时间 */
    if (user_opt_g.min_t > trip_t)
        user_opt_g.min_t = trip_t;

    if (user_opt_g.max_t < trip_t)
        user_opt_g.max_t = trip_t;

    return trip_t;
}


/**************************************************************************
 *
 * 函数功能: 接收数据, 处理应答.
 *
 * 参数说明: [IN] icmp_soc, 套接口描述符.
 *
 * 返 回 值: 成功返回 0, 失败返回 -1.
 *
 **************************************************************************/
int CICMPPing::icmp_process_reply(SOCKET icmp_soc)
{
    struct sockaddr_in from_addr;
    int result, data_size = user_opt_g.size;
    int from_len = sizeof(from_addr);
    char *recv_buf;

    data_size += sizeof(struct ip_hdr) + sizeof(struct icmp_hdr);
    recv_buf = (char *)malloc(data_size);

    /* 接收数据 */
    result = recvfrom(icmp_soc, recv_buf, data_size, 0,
                      (struct sockaddr*)&from_addr, &from_len);
    if (result == SOCKET_ERROR)
    {    
        //if (WSAGetLastError() == WSAETIMEDOUT)
        //    printf("timed out\n");
        //else
        //    printf("[PING] recvfrom_ failed: %d\n", WSAGetLastError());
        
        return -1;
    } 

    result = icmp_parse_reply(recv_buf, result, &from_addr);
    free(recv_buf);

    return result;
}


/**************************************************************************
 *
 * 函数功能: 显示 ECHO 的帮助信息.
 *
 * 参数说明: [IN] prog_name, 程序名;
 *
 * 返 回 值: void.
 *
 **************************************************************************/
void CICMPPing::icmp_help(char *prog_name)
{
    char *file_name;

    file_name = strrchr(prog_name, '\\');
    if (file_name != NULL)
        file_name++;
    else
        file_name = prog_name;

    /* 显示帮助信息 */
    //printf(" usage:     %s host_address [-t] [-n count] [-l size] "
    //       "[-w timeout]\n", file_name);
    //printf(" -t         Ping the host until stopped.\n");
    //printf(" -n count   the count to send ECHO\n");
    //printf(" -l size    the size to send data\n");
    //printf(" -w timeout timeout to wait the reply\n");
    exit(1);
}

/**************************************************************************
 *
 * 函数功能: 解析命令行选项, 保存到全局变量中.
 *
 * 参数说明: [IN] argc, 参数的个数;
 *           [IN] argv, 字符串指针数组.
 *
 * 返 回 值: void.
 *
 **************************************************************************/
//void CICMPPing::icmp_parse_param(int argc, char **argv)
//{
//    int i;
//
//    for(i = 1; i < argc; i++)
//    {
//        if ((argv[i][0] != '-') && (argv[i][0] != '/'))
//        {   
//            /* 处理主机名 */
//            if (user_opt_g.host)
//                icmp_help(argv[0]);
//            else
//            {
//                user_opt_g.host = argv[i];
//                continue;
//            }
//        }
//
//        switch (tolower(argv[i][1]))
//        {
//        case 't':   /* 持续 Ping */
//            user_opt_g.persist = 1;
//            break;
//
//        case 'n':   /* 发送请求的数量 */
//            i++;    
//            user_opt_g.count = atoi(argv[i]);
//            break;
//
//        case 'l':   /* 发送数据的大小 */
//            i++;
//            user_opt_g.size = atoi(argv[i]);
//            if (user_opt_g.size > ICMP_MAX_SIZE)
//                user_opt_g.size = ICMP_MAX_SIZE;
//            break;
//
//        case 'w':   /* 等待接收的超时时间 */
//            i++;    
//            user_opt_g.timeout = atoi(argv[i]);
//            break;
//
//        default:
//            icmp_help(argv[0]);
//            break;
//        }
//    }
//}

/**************************************************************************
 *
 * 函数功能: 初始化icmp_user_opt
 *
 * 参数说明:1,持续 Ping 2,发送请求的数量 3,发送数据的大小 4,等待接收的超时时间
 *           
 *
 * 返 回 值: bool.
 *
 **************************************************************************/
bool CICMPPing::InitICMP(char* IpAddr,unsigned int persist,unsigned int count,unsigned int size,unsigned int outtime)
{
	if (!IpAddr)
	{
		return false;
	}
	user_opt_g.persist = persist;
	user_opt_g.count = count;
	user_opt_g.size = size;
	if (user_opt_g.size > ICMP_MAX_SIZE)
		user_opt_g.size = ICMP_MAX_SIZE;
	user_opt_g.timeout = outtime;

	strncpy(user_opt_g.host,IpAddr,min(strlen(IpAddr),ICMP_HOST_LENGTH));
	return true;
}

int CICMPPing::GetPingTime(char* IpAddr)
{
	if (!InitICMP(IpAddr))
	{
		return -1;
	}

	WSADATA wsaData;
	SOCKET icmp_soc;
	struct sockaddr_in dest_addr;
	struct hostent *host_ent = NULL;

	int data_size, send_len;
	int result = -1;
	unsigned int i, timeout, lost;
	char *icmp_data;
	unsigned int ip_addr = 0;
	unsigned short seq_no = 0;

	WSAStartup(MAKEWORD(2,0),&wsaData);

	/* 解析主机地址 */
	ip_addr = inet_addr(user_opt_g.host);
	if (ip_addr == INADDR_NONE)
	{
		host_ent = gethostbyname(user_opt_g.host);
		if (!host_ent)
		{
			//printf("[PING] Fail to resolve %s\n", user_opt_g.host);
			return -1;
		}

		memcpy(&ip_addr, host_ent->h_addr_list[0], host_ent->h_length);
	}

	icmp_soc = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (icmp_soc == INVALID_SOCKET)
	{    
		//printf("[PING] socket() failed: %d\n", WSAGetLastError());
		return -1;
	}

	/* 设置选项, 接收和发送的超时时间　*/
	timeout = user_opt_g.timeout;
	result = setsockopt(icmp_soc, SOL_SOCKET, SO_RCVTIMEO,
		(char*)&timeout, sizeof(timeout));
	if (result != 0)
	{
		return -1;
	}

	timeout = 1000;
	result = setsockopt(icmp_soc, SOL_SOCKET, SO_SNDTIMEO,
		(char*)&timeout, sizeof(timeout));
	if (result != 0)
	{
		return -1;
	}

	memset(&dest_addr,0,sizeof(dest_addr));
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_addr.s_addr = ip_addr;

	data_size = user_opt_g.size + sizeof(struct icmp_hdr) - sizeof(long);
	icmp_data = (char *)malloc(data_size);
	//if (host_ent)
		//printf("Ping %s [%s] with %d bytes data\n", user_opt_g.host,
		//inet_ntoa(dest_addr.sin_addr), user_opt_g.size);
	//else
		//printf("Ping [%s] with %d bytes data\n", inet_ntoa(dest_addr.sin_addr),
		//user_opt_g.size);

	/* 发送请求并接收响应 */
	for (i = 0; i < user_opt_g.count; i++)
	{
		icmp_make_data(icmp_data, data_size, seq_no++);

		send_len = sendto(icmp_soc, icmp_data, data_size, 0, 
			(struct sockaddr*)&dest_addr, sizeof(dest_addr));
		if (send_len == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAETIMEDOUT)
			{
				//printf("[PING] sendto is timeout\n");
				continue;
			}

			//printf("[PING] sendto failed: %d\n", WSAGetLastError());
			break;
		} 

		user_opt_g.send++;
		result = icmp_process_reply(icmp_soc);

		user_opt_g.persist ? i-- : i; /* 持续 Ping */
		Sleep(1000); /* 延迟 1 秒 */
	}

	//lost = user_opt_g.send - user_opt_g.recv;
	/* 打印统计数据 */
	//printf("\nStatistic :\n");
	//printf("    Packet : sent = %d, recv = %d, lost = %d (%3.f%% lost)\n", 
		//user_opt_g.send, user_opt_g.recv, lost, (float)lost*100/user_opt_g.send);

	//if (user_opt_g.recv > 0)
	//{
		//printf("Roundtrip time (ms)\n");
		//printf("    min = %d ms, max = %d ms, avg = %d ms\n", user_opt_g.min_t,
			//user_opt_g.max_t, user_opt_g.total_t / user_opt_g.recv);
	//}
	free(icmp_data);
	closesocket(icmp_soc);
	WSACleanup();

	return result;
}