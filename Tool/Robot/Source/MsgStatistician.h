/********************************************************************
   Filename:    MsgStatistician.h
   MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __MSGSTATISTICIAN_H__
#define __MSGSTATISTICIAN_H__
#include <vector>
#include <map>
#include "Mutex.h"
using namespace  std;
//#include "Statistician.h
typedef  unsigned short uint16;
//typedef  unsigned __int64 int64 ;
class MsgStatistician // : public CStatistician
{
public:
   struct Msg_Info_
   {
       uint16 dwType;  // 消息类型
       int64  dwCount; // 消息个数
       int64  dwSize;  // 消息大小

       Msg_Info_()
       { dwType = 0; dwCount = 0; dwSize = 0; }

  /*     Msg_Info_& operator = (const Msg_Info_& xMsgInfo)
       {
           if (this == &xMsgInfo)
           { return (*this); }

           dwType  = xMsgInfo.dwType;
           dwCount = xMsgInfo.dwCount;
           dwSize  = xMsgInfo.dwSize;

           return (*this);
       }
*/
       friend bool operator == (const Msg_Info_& xMsgInfo, const DWORD& dwType)
       { return (xMsgInfo.dwType == dwType); }

       friend bool operator > (const Msg_Info_& xLeft, const Msg_Info_& xRight)
       { return (xLeft.dwSize > xRight.dwSize); }
   };

   struct Total_Info_
   {
       int64 dwCount;    // 消息个数
       int64 dwSize;     // 消息大小
       std::vector<Msg_Info_> vecMsgInfo;

       Total_Info_() 
       { dwCount = 0; dwSize = 0; vecMsgInfo.clear(); }

       inline Total_Info_& operator = (const Total_Info_& xTotalInfo)
       {
           if (this == &xTotalInfo)
           { return *this; }

           dwCount = xTotalInfo.dwCount;
           dwSize = xTotalInfo.dwSize;

           vecMsgInfo = xTotalInfo.vecMsgInfo;

           return (*this);
       }

       inline void Clear()
       {
           dwCount = 0;
           dwSize = 0;
           vecMsgInfo.clear();
       }

       void AddMsgInfo(Msg_Info_& xMsgInfo);    
   };

public:
   MsgStatistician();
   virtual ~MsgStatistician();
   MsgStatistician& operator =(const MsgStatistician& xMsgStatistician);


   void SetStartTime(DWORD dwStartTime);
   DWORD GetStartTime();
   DWORD GetStatisticianTimeInt(DWORD dwNowTime);
   char* GetStatisticianTimeString(DWORD dwNowTime);
   
   void SetLoopCount();
   int64 GetLoopCount();

	//设置、获取Monster数目luo.qin 3.18
	void SetMonsterNum(int64 dwMonsterNum);
	int64 GetMonsterNum();

   void SetLoopCount(DWORD dwLoopNum);
   int64 GetLoopCountPerSecond(DWORD dwNowTime);

   void SetMsgSendCount(int64 dwCount);
   int64 GetMsgSendCount();
   int64 GetMsgSendCountPerSecond(DWORD dwNowTime);

   void SetMsgSendSize(int64 dwSize);
   int64 GetMsgSendSize();
   int64 GetMsgSendSizePerSecond(DWORD dwNowTime);

   void SetMsgRecvCount(int64 dwCount);
   int64 GetMsgRecvCount();
   int64 GetMsgRecvCountPerSecond(DWORD dwNowTime);

   void SetMsgRecvSize(int64 dwSize);
   int64 GetMsgRecvSize();
   int64 GetMsgRecvSizePerSecond(DWORD dwNowTime);

   void SetCurrentSendInfo(int64 dwCount, int64 dwSize, Msg_Info_& xMsgInfo);    
   void UpdataMaxAndMinSendInfo();


   void SetCurrentRecvInfo(int64 dwCount, int64 dwSize, Msg_Info_& xMsgInfo);
   void UpdataMaxAndMinRecvInfo();


   //记录每种消息发送的次数
   void AddMapSendMsgCount(DWORD dwType, Msg_Info_ &xMsgInfo);        
   void AddMapRecvMsgCount(DWORD dwType, Msg_Info_ &xMsgInfo);


	void PrintStatLog(std::ostream &ros);            //打印日志

public:
   Total_Info_ m_xMaxSendInfo; // 最大发送消息
   Total_Info_ m_xMinSendInfo; // 最小发送消息
   Total_Info_ m_xMaxRecvInfo; // 最大接受消息
   Total_Info_ m_xMinRecvInfo; // 最小接受消息
	int64	    m_dwMonsterNum;	// 单个机器人创建的Monster数目luo.qin 3.18

	std::map<DWORD, Msg_Info_> m_mapMsgSendCount;    //每一条消息发送了多少次
   std::map<DWORD, Msg_Info_> m_mapMsgRecvCount;    //每一条消息收到了多少次

protected:
   CIntLock m_xIntLock;

private:
   DWORD m_dwStartTime;    //执行的开始时间
   int64 m_dwLoopCount;    //执行Updata的次数
   int64 m_dwMsgSendCount;    //发送消息个数
   int64 m_dwMsgRecvCount;    //接受消息个数
   int64 m_dwMsgSendSize;    //发送的大小
   int64 m_dwMsgRecvSize;    //接受的大小

   Total_Info_ m_xCurrentSendInfo;        //当前轮的信息
   Total_Info_ m_xCurrentRecvInfo;
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

//显示更新的时候直接将统计信息拷贝出去
inline MsgStatistician& MsgStatistician::operator = (const MsgStatistician& xMsgStatistician)
{
   if (this == &xMsgStatistician)
   {
       return (*this);
   }

   //加锁
   m_xIntLock.Lock();

   m_dwStartTime        = xMsgStatistician.m_dwStartTime;
   m_dwLoopCount        = xMsgStatistician.m_dwLoopCount;
   m_dwMsgSendCount    = xMsgStatistician.m_dwMsgSendCount;
   m_dwMsgSendSize        = xMsgStatistician.m_dwMsgSendSize;
   m_dwMsgRecvCount    = xMsgStatistician.m_dwMsgRecvCount;
   m_dwMsgRecvSize        = xMsgStatistician.m_dwMsgRecvSize;

   m_xMaxSendInfo        = xMsgStatistician.m_xMaxSendInfo;
   m_xMinSendInfo        = xMsgStatistician.m_xMinSendInfo;

   m_xMaxRecvInfo        = xMsgStatistician.m_xMaxRecvInfo;
   m_xMinRecvInfo        = xMsgStatistician.m_xMinRecvInfo;

   m_xIntLock.Unlock();

   return (*this);
}

inline void MsgStatistician::SetStartTime(DWORD dwStartTime)
{
   m_xIntLock.Lock();
   m_dwStartTime = dwStartTime;
   m_xIntLock.Unlock();
}

inline DWORD MsgStatistician::GetStartTime()
{
   m_xIntLock.Lock();
   DWORD dwStartTime = m_dwStartTime;
   m_xIntLock.Unlock();

   return dwStartTime;
}

inline DWORD MsgStatistician::GetStatisticianTimeInt(DWORD dwNowTime)
{
   return (dwNowTime - m_dwStartTime) / 1000;
}

inline void MsgStatistician::SetLoopCount()
{
   m_xIntLock.Lock();
   ++m_dwLoopCount;
   m_xIntLock.Unlock();
}

inline int64 MsgStatistician::GetLoopCount()
{
   m_xIntLock.Lock();
   int64 dwLoopCount = m_dwLoopCount;
   m_xIntLock.Unlock();

   return dwLoopCount;
}

inline void MsgStatistician::SetLoopCount(DWORD dwLoopNum)
{
   if (dwLoopNum < 0)
   { m_dwLoopCount = 0;}

   m_dwLoopCount = dwLoopNum;
}

inline int64 MsgStatistician::GetLoopCountPerSecond(DWORD dwNowTime)
{
   DWORD dwSecond = (dwNowTime - m_dwStartTime) / 1000;
   m_xIntLock.Lock();

   int64 dwPerLoopCount = m_dwLoopCount / dwSecond;

   m_xIntLock.Unlock();

   return dwPerLoopCount;
}

inline void MsgStatistician::SetMsgSendCount(int64 dwCount)
{
   m_xIntLock.Lock();    
   m_dwMsgSendCount += dwCount;
   m_xIntLock.Unlock();
}

inline int64 MsgStatistician::GetMsgSendCount()
{
   m_xIntLock.Lock();
   int64 dwMsgSendCount = m_dwMsgSendCount;
   m_xIntLock.Unlock();
   
   return dwMsgSendCount;
}

inline int64 MsgStatistician::GetMsgSendCountPerSecond(DWORD dwNowTime)
{
   DWORD dwSecond = (dwNowTime - m_dwStartTime) / 1000;
   m_xIntLock.Lock();

   int64 dwMsgSendCountPerSecond = m_dwMsgSendCount / dwSecond;

   m_xIntLock.Unlock();

   return dwMsgSendCountPerSecond;
}

inline void MsgStatistician::SetMsgSendSize(int64 dwSize)
{
   m_xIntLock.Lock();
   m_dwMsgSendSize += dwSize;
   m_xIntLock.Unlock();    
}

inline int64 MsgStatistician::GetMsgSendSize()
{
   m_xIntLock.Lock();
   int64 dwMsgSendSize = m_dwMsgSendSize;
   m_xIntLock.Unlock();

   return dwMsgSendSize;
}

inline int64 MsgStatistician::GetMsgSendSizePerSecond(DWORD dwNowTime)
{
   DWORD dwSecond = (dwNowTime - m_dwStartTime) / 1000;
   m_xIntLock.Lock();

   int64 dwMsgSendSizePerSecond = m_dwMsgSendSize / dwSecond;

   m_xIntLock.Unlock();

   return dwMsgSendSizePerSecond;
}

inline void MsgStatistician::SetMsgRecvCount(int64 dwCount)
{
   m_xIntLock.Lock();
   m_dwMsgRecvCount += dwCount;
   m_xIntLock.Unlock();
}

inline int64 MsgStatistician::GetMsgRecvCount()
{
   m_xIntLock.Lock();
   int64 dwMsgRecvCount = m_dwMsgRecvCount;
   m_xIntLock.Unlock();

   return dwMsgRecvCount;
}

inline int64 MsgStatistician::GetMsgRecvCountPerSecond(DWORD dwNowTime)
{
   DWORD dwSecond = (dwNowTime - m_dwStartTime) / 1000;
   m_xIntLock.Lock();

   int64 dwMsgRecvCountPerSecond = m_dwMsgRecvCount / dwSecond;

   m_xIntLock.Unlock();

   return dwMsgRecvCountPerSecond;
}

inline void MsgStatistician::SetMsgRecvSize(int64 dwSize)
{
   m_xIntLock.Lock();
   m_dwMsgRecvSize += dwSize;
   m_xIntLock.Unlock();
}

inline int64 MsgStatistician::GetMsgRecvSize()
{
   m_xIntLock.Lock();
   int64 dwMsgRecvSize = m_dwMsgRecvSize;
   m_xIntLock.Unlock();

   return dwMsgRecvSize;
}

inline int64 MsgStatistician::GetMsgRecvSizePerSecond(DWORD dwNowTime)
{
   DWORD dwSecond = (dwNowTime - m_dwStartTime) / 1000;
   m_xIntLock.Lock();

   int64 dwMsgRecvSizePerSecond = m_dwMsgRecvSize / dwSecond;

   m_xIntLock.Unlock();

   return dwMsgRecvSizePerSecond;
}
//设置、获取Monster数目luo.qin 3.18
inline void MsgStatistician::SetMonsterNum(int64 dwMonsterNum)
{
	m_dwMonsterNum = dwMonsterNum;
}
inline int64 MsgStatistician::GetMonsterNum()
{
	return m_dwMonsterNum;
}

#endif

