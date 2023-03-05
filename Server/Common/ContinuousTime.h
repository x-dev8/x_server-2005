#pragma once

#include "MeRTLibsServer.h"

//�ȽϺ���
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
	//�����û�����
	//�û��ṩһ���û����ݵ�buffer
	bool SetUserData( char* lpDataBegin,size_t datasize,int iDataNum );
	//���û�����ݣ�����0
	//�õ���ʱ��
	char* GetDataTimeReached( DWORD dwTime );
	//�������ݵĸ���
	int GetDataNum(void);
	//��һ�����ݲ��뵽������
	//����memcpy��lpData�������û�������
	bool AddData( DWORD dwDeathTime,char* lpData );
	//ȡ�߼�������ͬ������
	char* GetEqualData( char* lpData,UserDataCompareFunc func );
	//ɾ������
	void  DeleteEqualData( char* lpData,UserDataCompareFunc func );
	//�õ���iWhich������
	char* GetData( int iWhich );
private:
	//С��const_iMaxData��SetUserData�����iDataNum
	int m_iMaxData;
	//���ݸ���		
	int m_iDataNum;
	//���ݿ�Ĵ�С
	size_t m_sizeData;
	//���ݿ�ʼ
	char*		m_lpDataBegin;
	STimeData	m_timedatas[const_iMaxData];
	//���ݿ�ʹ��
	bool		m_bDataUsed[ const_iMaxData ];
};
