#ifndef __TIMESTAMP_H__
#define __TIMESTAMP_H__
//时间戳
//提供几个API
#pragma once

class CTimestamp
{
public:
	static CTimestamp& Instance()
	{
		static CTimestamp ctt;
		return ctt;
	}

	//获得当前时间的时间戳
	unsigned long GetTimestamp();
	//通过时间戳或者该日期时间
	char* GetTimeByTimestamp(unsigned long tt);

	CTimestamp(void);
	~CTimestamp(void);
};
#define theTimestamp CTimestamp::Instance()

#endif //__TIMESTAMP_H__