/********************************************************************
    Filename:     NetWorkParameterDefine.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

enum eNetWorkParamer
{
	//Client
	eN_Client_BigBufferSize = 128*1024,//指定大块的大小
	eN_Client_BigBufferNum = 10,//指定大块的数目
	eN_Client_SmallBufferSize = 16*1024,//指定小块的大小
	eN_Client_SmallBufferNum = 100,//指定小块的数目
	eN_Client_ListenNum = 1,//指定用于监听的套接字的数目
	eN_Client_SocketNum = 10,//用于连接的总数目
	eN_Client_ThreadNum = -1,//指定网络线程数目，若设置为小于等于0，则会开启cpu个数的线程数目

	//center
	eN_CenterServer_BigBufferSize = 256*1024,//指定大块的大小
	eN_CenterServer_BigBufferNum = 10,//指定大块的数目
	eN_CenterServer_SmallBufferSize = 32*1024,//指定小块的大小
	eN_CenterServer_SmallBufferNum = 100,//指定小块的数目
	eN_CenterServer_ListenNum = 5,//指定用于监听的套接字的数目
	eN_CenterServer_SocketNum = 20,//用于连接的总数目
	eN_CenterServer_ThreadNum = -1,//指定网络线程数目，若设置为小于等于0，则会开启cpu个数的线程数目

	//character and game
	eN_GameServer_BigBufferSize = 256*1024,//指定大块的大小
	eN_GameServer_BigBufferNum = 50,//指定大块的数目
	eN_GameServer_SmallBufferSize = 32*1024,//指定小块的大小
	eN_GameServer_SmallBufferNum = 500,//指定小块的数目
	eN_GameServer_ListenNum = 5,//指定用于监听的套接字的数目
	eN_GameServer_SocketNum = 20,//用于连接的总数目
	eN_GameServer_ThreadNum = -1,//指定网络线程数目，若设置为小于等于0，则会开启cpu个数的线程数目

	//database server
	eN_DBServer_BigBufferSize = 256*1024,//指定大块的大小
	eN_DBServer_BigBufferNum = 10,//指定大块的数目
	eN_DBServer_SmallBufferSize = 32*1024,//指定小块的大小
	eN_DBServer_SmallBufferNum = 100,//指定小块的数目
	eN_DBServer_ListenNum = 5,//指定用于监听的套接字的数目
	eN_DBServer_SocketNum = 10,//用于连接的总数目
	eN_DBServer_ThreadNum = -1,//指定网络线程数目，若设置为小于等于0，则会开启cpu个数的线程数目

	//gate server
	eN_GateServer_BigBufferSize = 256*1024,//指定大块的大小
	eN_GateServer_BigBufferNum = 50,//指定大块的数目
	eN_GateServer_SmallBufferSize = 64*1024,//指定小块的大小
	eN_GateServer_SmallBufferNum = 500,//指定小块的数目
	eN_GateServer_ListenNum = 5,//指定用于监听的套接字的数目
	eN_GateServer_SocketNum = 3000,//用于连接的总数目
	eN_GateServer_ThreadNum = -1,//指定网络线程数目，若设置为小于等于0，则会开启cpu个数的线程数目

	//Login server
	eN_LoginServer_BigBufferSize = 256*1024,//指定大块的大小
	eN_LoginServer_BigBufferNum = 10,//指定大块的数目
	eN_LoginServer_SmallBufferSize = 32*1024,//指定小块的大小
	eN_LoginServer_SmallBufferNum = 100,//指定小块的数目
	eN_LoginServer_ListenNum = 5,//指定用于监听的套接字的数目
	eN_LoginServer_SocketNum = 3000,//用于连接的总数目
	eN_LoginServer_ThreadNum = -1,//指定网络线程数目，若设置为小于等于0，则会开启cpu个数的线程数目

	//over time global define
	eC2S_OverTime = 30000,//客户端与所有服务器之间的超时时间,单位:ms
	eS2C_OverTime = 30000,//所有服务器与客户端之间的超时时间,单位:ms
	eS2S_OverTime = 30000,//服务器与服务器之间的超时时间,单位:ms
	eS2S_PingTime = 10000,//服务器直接的ping帧,单位:ms

	//platform server
	eN_PlatFormCenter_BigBufferSize = 256*1024,//指定大块的大小
	eN_PlatFormCenter_BigBufferNum = 10,//指定大块的数目
	eN_PlatFormCenter_SmallBufferSize = 32*1024,//指定小块的大小
	eN_PlatFormCenter_SmallBufferNum = 100,//指定小块的数目
	eN_PlatFormCenter_ListenNum = 5,//指定用于监听的套接字的数目
	eN_PlatFormCenter_SocketNum = 200,//用于连接的总数目
	eN_PlatFormCenter_ThreadNum = -1,//指定网络线程数目，若设置为小于等于0，则会开启cpu个数的线程数目

	//LogServer server
	eN_LogServer_BigBufferSize = 256*1024,//指定大块的大小
	eN_LogServer_BigBufferNum = 10,//指定大块的数目
	eN_LogServer_SmallBufferSize = 32*1024,//指定小块的大小
	eN_LogServer_SmallBufferNum = 100,//指定小块的数目
	eN_LogServer_ListenNum = 5,//指定用于监听的套接字的数目
	eN_LogServer_SocketNum = 200,//用于连接的总数目
	eN_LogServer_ThreadNum = -1,//指定网络线程数目，若设置为小于等于0，则会开启cpu个数的线程数目
};