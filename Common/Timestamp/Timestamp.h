#ifndef __TIMESTAMP_H__
#define __TIMESTAMP_H__
//ʱ���
//�ṩ����API
#pragma once

class CTimestamp
{
public:
	static CTimestamp& Instance()
	{
		static CTimestamp ctt;
		return ctt;
	}

	//��õ�ǰʱ���ʱ���
	unsigned long GetTimestamp();
	//ͨ��ʱ������߸�����ʱ��
	char* GetTimeByTimestamp(unsigned long tt);

	CTimestamp(void);
	~CTimestamp(void);
};
#define theTimestamp CTimestamp::Instance()

#endif //__TIMESTAMP_H__