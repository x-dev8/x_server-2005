/********************************************************************
    Filename:     NetWorkParameterDefine.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

enum eNetWorkParamer
{
	//Client
	eN_Client_BigBufferSize = 128*1024,//ָ�����Ĵ�С
	eN_Client_BigBufferNum = 10,//ָ��������Ŀ
	eN_Client_SmallBufferSize = 16*1024,//ָ��С��Ĵ�С
	eN_Client_SmallBufferNum = 100,//ָ��С�����Ŀ
	eN_Client_ListenNum = 1,//ָ�����ڼ������׽��ֵ���Ŀ
	eN_Client_SocketNum = 10,//�������ӵ�����Ŀ
	eN_Client_ThreadNum = -1,//ָ�������߳���Ŀ��������ΪС�ڵ���0����Ὺ��cpu�������߳���Ŀ

	//center
	eN_CenterServer_BigBufferSize = 256*1024,//ָ�����Ĵ�С
	eN_CenterServer_BigBufferNum = 10,//ָ��������Ŀ
	eN_CenterServer_SmallBufferSize = 32*1024,//ָ��С��Ĵ�С
	eN_CenterServer_SmallBufferNum = 100,//ָ��С�����Ŀ
	eN_CenterServer_ListenNum = 5,//ָ�����ڼ������׽��ֵ���Ŀ
	eN_CenterServer_SocketNum = 20,//�������ӵ�����Ŀ
	eN_CenterServer_ThreadNum = -1,//ָ�������߳���Ŀ��������ΪС�ڵ���0����Ὺ��cpu�������߳���Ŀ

	//character and game
	eN_GameServer_BigBufferSize = 256*1024,//ָ�����Ĵ�С
	eN_GameServer_BigBufferNum = 50,//ָ��������Ŀ
	eN_GameServer_SmallBufferSize = 32*1024,//ָ��С��Ĵ�С
	eN_GameServer_SmallBufferNum = 500,//ָ��С�����Ŀ
	eN_GameServer_ListenNum = 5,//ָ�����ڼ������׽��ֵ���Ŀ
	eN_GameServer_SocketNum = 20,//�������ӵ�����Ŀ
	eN_GameServer_ThreadNum = -1,//ָ�������߳���Ŀ��������ΪС�ڵ���0����Ὺ��cpu�������߳���Ŀ

	//database server
	eN_DBServer_BigBufferSize = 256*1024,//ָ�����Ĵ�С
	eN_DBServer_BigBufferNum = 10,//ָ��������Ŀ
	eN_DBServer_SmallBufferSize = 32*1024,//ָ��С��Ĵ�С
	eN_DBServer_SmallBufferNum = 100,//ָ��С�����Ŀ
	eN_DBServer_ListenNum = 5,//ָ�����ڼ������׽��ֵ���Ŀ
	eN_DBServer_SocketNum = 10,//�������ӵ�����Ŀ
	eN_DBServer_ThreadNum = -1,//ָ�������߳���Ŀ��������ΪС�ڵ���0����Ὺ��cpu�������߳���Ŀ

	//gate server
	eN_GateServer_BigBufferSize = 256*1024,//ָ�����Ĵ�С
	eN_GateServer_BigBufferNum = 50,//ָ��������Ŀ
	eN_GateServer_SmallBufferSize = 64*1024,//ָ��С��Ĵ�С
	eN_GateServer_SmallBufferNum = 500,//ָ��С�����Ŀ
	eN_GateServer_ListenNum = 5,//ָ�����ڼ������׽��ֵ���Ŀ
	eN_GateServer_SocketNum = 3000,//�������ӵ�����Ŀ
	eN_GateServer_ThreadNum = -1,//ָ�������߳���Ŀ��������ΪС�ڵ���0����Ὺ��cpu�������߳���Ŀ

	//Login server
	eN_LoginServer_BigBufferSize = 256*1024,//ָ�����Ĵ�С
	eN_LoginServer_BigBufferNum = 10,//ָ��������Ŀ
	eN_LoginServer_SmallBufferSize = 32*1024,//ָ��С��Ĵ�С
	eN_LoginServer_SmallBufferNum = 100,//ָ��С�����Ŀ
	eN_LoginServer_ListenNum = 5,//ָ�����ڼ������׽��ֵ���Ŀ
	eN_LoginServer_SocketNum = 3000,//�������ӵ�����Ŀ
	eN_LoginServer_ThreadNum = -1,//ָ�������߳���Ŀ��������ΪС�ڵ���0����Ὺ��cpu�������߳���Ŀ

	//over time global define
	eC2S_OverTime = 30000,//�ͻ��������з�����֮��ĳ�ʱʱ��,��λ:ms
	eS2C_OverTime = 30000,//���з�������ͻ���֮��ĳ�ʱʱ��,��λ:ms
	eS2S_OverTime = 30000,//�������������֮��ĳ�ʱʱ��,��λ:ms
	eS2S_PingTime = 10000,//������ֱ�ӵ�ping֡,��λ:ms

	//platform server
	eN_PlatFormCenter_BigBufferSize = 256*1024,//ָ�����Ĵ�С
	eN_PlatFormCenter_BigBufferNum = 10,//ָ��������Ŀ
	eN_PlatFormCenter_SmallBufferSize = 32*1024,//ָ��С��Ĵ�С
	eN_PlatFormCenter_SmallBufferNum = 100,//ָ��С�����Ŀ
	eN_PlatFormCenter_ListenNum = 5,//ָ�����ڼ������׽��ֵ���Ŀ
	eN_PlatFormCenter_SocketNum = 200,//�������ӵ�����Ŀ
	eN_PlatFormCenter_ThreadNum = -1,//ָ�������߳���Ŀ��������ΪС�ڵ���0����Ὺ��cpu�������߳���Ŀ

	//LogServer server
	eN_LogServer_BigBufferSize = 256*1024,//ָ�����Ĵ�С
	eN_LogServer_BigBufferNum = 10,//ָ��������Ŀ
	eN_LogServer_SmallBufferSize = 32*1024,//ָ��С��Ĵ�С
	eN_LogServer_SmallBufferNum = 100,//ָ��С�����Ŀ
	eN_LogServer_ListenNum = 5,//ָ�����ڼ������׽��ֵ���Ŀ
	eN_LogServer_SocketNum = 200,//�������ӵ�����Ŀ
	eN_LogServer_ThreadNum = -1,//ָ�������߳���Ŀ��������ΪС�ڵ���0����Ὺ��cpu�������߳���Ŀ
};