#include "stdafx.h"
#include "MsgStatistician.h"



MsgStatistician::MsgStatistician():m_xIntLock()
{
	m_dwStartTime = 0;
	m_dwLoopCount = 0;
	m_dwMsgSendCount = 0;
	m_dwMsgSendSize = 0;
	m_dwMsgRecvCount = 0;
	m_dwMsgRecvSize = 0;
	m_dwMonsterNum = 0;

	m_xCurrentSendInfo.Clear();
	m_xCurrentRecvInfo.Clear();
	m_xMaxSendInfo.Clear();
	m_xMinSendInfo.Clear();
	m_xMaxRecvInfo.Clear();
	m_xMinRecvInfo.Clear();

	m_xMinSendInfo.dwSize = 10000;
	m_xMinRecvInfo.dwSize = 10000;

	m_mapMsgSendCount.clear();
	m_mapMsgRecvCount.clear();
}

MsgStatistician::~MsgStatistician()
{

}

void MsgStatistician::SetCurrentSendInfo(int64 dwCount, int64 dwSize, Msg_Info_& xMsgInfo)
{
	SetMsgSendCount(dwCount);
	SetMsgSendSize(dwSize);
	AddMapSendMsgCount(xMsgInfo.dwType, xMsgInfo);

	m_xIntLock.Lock();
	
	m_xCurrentSendInfo.dwCount += dwCount;
	m_xCurrentSendInfo.dwSize += dwSize;

	m_xCurrentSendInfo.AddMsgInfo(xMsgInfo);

	m_xIntLock.Unlock();
}


void MsgStatistician::UpdataMaxAndMinSendInfo()
{	
	m_xIntLock.Lock();

	if (m_xCurrentSendInfo.dwSize == 0)
	{
		m_xIntLock.Unlock();
		
		return;
	}

	//判断最大
	if (m_xMaxSendInfo.dwSize <= m_xCurrentSendInfo.dwSize)
	{
		m_xMaxSendInfo = m_xCurrentSendInfo;
	}

	//判断最小
	if (m_xMinSendInfo.dwSize >= m_xCurrentSendInfo.dwSize)
	{
		m_xMinSendInfo = m_xCurrentSendInfo;
	}

	m_xCurrentSendInfo.Clear();

	m_xIntLock.Unlock();
}

void MsgStatistician::SetCurrentRecvInfo(int64 dwCount, int64 dwSize, Msg_Info_ &xMsgInfo)
{
	SetMsgRecvCount(dwCount);
	SetMsgRecvSize(dwSize);
	AddMapRecvMsgCount(xMsgInfo.dwType, xMsgInfo);

	m_xIntLock.Lock();

	m_xCurrentRecvInfo.dwCount += dwCount;
	m_xCurrentRecvInfo.dwSize += dwSize;

	m_xCurrentRecvInfo.AddMsgInfo(xMsgInfo);

	m_xIntLock.Unlock();
}

void MsgStatistician::UpdataMaxAndMinRecvInfo()
{
	m_xIntLock.Lock();

	if (m_xCurrentRecvInfo.dwSize == 0)
	{
		m_xIntLock.Unlock();

		return;
	}

	//判断最大
	if (m_xMaxRecvInfo.dwSize <= m_xCurrentRecvInfo.dwSize)
	{
		m_xMaxRecvInfo = m_xCurrentRecvInfo;
	}

	//判断最小
	if (m_xMinRecvInfo.dwSize >= m_xCurrentRecvInfo.dwSize)
	{
		m_xMinRecvInfo = m_xCurrentRecvInfo;
	}

	m_xCurrentRecvInfo.Clear();

	m_xIntLock.Unlock();
}

void MsgStatistician::AddMapSendMsgCount(DWORD dwType, Msg_Info_ &xMsgInfo)
{
	m_xIntLock.Lock();

	std::map<DWORD, Msg_Info_>::iterator iter = m_mapMsgSendCount.find(dwType);

	if (iter != m_mapMsgSendCount.end())
	{
		(*iter).second.dwCount += xMsgInfo.dwCount;
		(*iter).second.dwSize += xMsgInfo.dwSize;
	}
	else
	{
		m_mapMsgSendCount.insert(make_pair(dwType, xMsgInfo));
	}

	m_xIntLock.Unlock();	
}

void MsgStatistician::AddMapRecvMsgCount(DWORD dwType, Msg_Info_ &xMsgInfo)
{
	m_xIntLock.Lock();

	map<DWORD, Msg_Info_>::iterator iter = m_mapMsgRecvCount.find(dwType);

	if (iter != m_mapMsgRecvCount.end())
	{
		(*iter).second.dwCount += xMsgInfo.dwCount;
		(*iter).second.dwSize += xMsgInfo.dwSize;
	}
	else
	{
		m_mapMsgRecvCount.insert(make_pair(dwType, xMsgInfo));
	}

	m_xIntLock.Unlock();
}



void MsgStatistician::Total_Info_::AddMsgInfo(Msg_Info_& xMsgInfo)
{
	vector<MsgStatistician::Msg_Info_>::iterator iter = find(vecMsgInfo.begin(), vecMsgInfo.end(), xMsgInfo.dwType);
	if (iter != vecMsgInfo.end())
	{
		(*iter).dwCount += xMsgInfo.dwCount;
		(*iter).dwSize += xMsgInfo.dwSize;

		return;
	}

	vecMsgInfo.push_back(xMsgInfo);
}


char* MsgStatistician::GetStatisticianTimeString(DWORD dwNowTime)
{
	DWORD dwTime = dwNowTime - m_dwStartTime;

	DWORD dwHour = dwTime / (60 * 60* 1000);
	DWORD dwMinute = (dwTime - dwHour * 60 * 60 *1000) / (60 * 1000);
	DWORD dwSecond = (dwTime % (60 * 1000)) / 1000;

	static char szTime[50] = "";
	memset(szTime, 0, sizeof(szTime));

	sprintf_s(szTime, sizeof(szTime), "%d小时%d分钟%d秒", dwHour, dwMinute, dwSecond);

	return szTime;	
}

