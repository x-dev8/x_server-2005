#pragma once

#include "MeRTLibsServer.h"

//比较函数
typedef INT (*UserDataCompareFunc)( char* lpData0,char* lpData1 );


class CContinuousTime
{
public:
	CContinuousTime(void);
	~CContinuousTime(void);

public:
	enum enumConst
	{
		const_iMaxData = 10
	};
	struct STimeData
	{
		DWORD	dwDeathTime;
		int		iDataOff;
	};
	//设置用户数据
	//用户提供一个用户数据的buffer
	bool SetUserData( char* lpDataBegin,size_t datasize,int iDataNum );
	//如果没有数据，返回0
	//得到比时间
	char* GetDataTimeReached( DWORD dwTime );
	//返回数据的个数
	int GetDataNum(void);
	//将一个数据插入到队列中
	//将用memcpy将lpData拷贝到用户数据中
	bool AddData( DWORD dwDeathTime,char* lpData );
	//取逻辑数据相同的数据
	char* GetEqualData( char* lpData,UserDataCompareFunc func );
	//删除数据
	void  DeleteEqualData( char* lpData,UserDataCompareFunc func );
	//得到第iWhich个数据
	char* GetData( int iWhich );
private:
	//小于const_iMaxData和SetUserData传入的iDataNum
	int m_iMaxData;
	//数据个数		
	int m_iDataNum;
	//数据块的大小
	size_t m_sizeData;
	//数据开始
	char*		m_lpDataBegin;
	STimeData	m_timedatas[const_iMaxData];
	//数据块使用
	bool		m_bDataUsed[ const_iMaxData ];
};
