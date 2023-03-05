#include "continuoustime.h"
#include <assert.h>


CContinuousTime::CContinuousTime(void)
{
}

CContinuousTime::~CContinuousTime(void)
{
}

//�����û�����
//�û��ṩһ���û����ݵ�buffer
bool CContinuousTime::SetUserData( char* lpDataBegin,size_t datasize,int iDataNum )
{
	if( iDataNum <= 0 )
	{
		// ToLog( false );
		return false;
	}
	if(  iDataNum > const_iMaxData )
		iDataNum = const_iMaxData;
	m_iMaxData = iDataNum;
	m_sizeData = datasize;
	int iLoop;
	m_lpDataBegin = lpDataBegin;
	
	m_iDataNum = 0;

	for( iLoop = 0 ; iLoop < m_iMaxData ; iLoop ++ )
		m_bDataUsed[ iLoop ] = false;
	return true;
}
//���û�����ݣ�����0
//�õ���ʱ��
char* CContinuousTime::GetDataTimeReached( DWORD dwTime )
{
	if( m_iDataNum <= 0 )
		return 0;
	char* lpData;
	int iDataOff;
	if( m_timedatas[0].dwDeathTime <= dwTime )
	{
		iDataOff = m_timedatas[0].iDataOff;

		if( iDataOff < 0 || iDataOff >= m_iMaxData )
		{
			// ToLog( false );
			return 0;
		}

		lpData = m_lpDataBegin;

		lpData += iDataOff * m_sizeData;

		m_bDataUsed[ iDataOff ] = false;
		//���ݸ�����1
		m_iDataNum --;
		//λ������
		int iLoop;
		for( iLoop = 0 ; iLoop < m_iDataNum ; iLoop ++ )
		{
			m_timedatas[ iLoop ] = m_timedatas[ iLoop + 1 ];
		}
		//
		return lpData;
	}
	return 0;
}
//�������ݵĸ���
int CContinuousTime::GetDataNum(void)
{
	return m_iDataNum;
}
//��һ�����ݲ��뵽������
//����memcpy��lpData�������û�������
bool CContinuousTime::AddData( DWORD dwDeathTime,char* lpData )
{
	if( m_iDataNum >= m_iMaxData )
		return false;
	//���ȵõ�һ����λ���洢����
	int iLoop;
	for( iLoop = 0 ; iLoop < m_iMaxData ; iLoop ++ )
	{
		if( !m_bDataUsed[iLoop] )
			break;
	}
	if( iLoop == m_iMaxData )
		return false;
	//�ҵ��˴���û����ݵĵط�
	int iDataOff = iLoop;

	//�ҵ������λ��
	for( iLoop = 0 ; iLoop < m_iDataNum ; iLoop ++ )
	{
		if( dwDeathTime < m_timedatas[iLoop].dwDeathTime )
			break;
	}
	int iInsertPos = iLoop;
	for( iLoop = m_iDataNum ; iLoop > iInsertPos ; iLoop -- )
	{
		m_timedatas[ iLoop ] = m_timedatas[ iLoop - 1 ];
	}
	//
	m_timedatas[ iLoop ].dwDeathTime = dwDeathTime;
	m_timedatas[ iLoop ].iDataOff = iDataOff;
	
	
	char* lpWriteData = m_lpDataBegin;
	lpWriteData += (iDataOff)*m_sizeData;
	memcpy( lpWriteData,lpData,m_sizeData );

	m_bDataUsed[ iDataOff ] = true;
	m_iDataNum ++;
	//	
	//
	return true;
}
//ȡ�߼�������ͬ������
char* CContinuousTime::GetEqualData( char* lpData,UserDataCompareFunc func )
{
	int iLoop = 0;
	char *lpLocalData;
	for( ; iLoop < m_iDataNum ; iLoop ++ )
	{
		lpLocalData = m_lpDataBegin;
		lpLocalData += (m_timedatas[iLoop].iDataOff)*m_sizeData;
		if( 0 == func( lpData,lpLocalData ) )
			return lpLocalData;
	}
	return 0;
}

void  CContinuousTime::DeleteEqualData( char* lpData,UserDataCompareFunc func )
{
	if( m_iDataNum <= 0 )
		return;
	int iLoop = 0;
	char *lpLocalData;
	for( ; iLoop < m_iDataNum ; iLoop ++ )
	{
		lpLocalData = m_lpDataBegin;
		lpLocalData += (m_timedatas[iLoop].iDataOff)*m_sizeData;
		if( 0 == func( lpData,lpLocalData ) )
			break;
	}
	int iDeletePos = iLoop;
	m_iDataNum --;
	for( iLoop = iDeletePos ; iLoop < m_iDataNum ; iLoop ++ )
	{
		m_timedatas[ iLoop ] = m_timedatas[ iLoop + 1 ];
	}	
}

//�õ���iWhich������
char* CContinuousTime::GetData( int iWhich )
{
	if( iWhich < 0 || iWhich >= m_iDataNum )
		return 0;
	char *lpLocalData;	
	lpLocalData = m_lpDataBegin;
	lpLocalData += (m_timedatas[ iWhich ].iDataOff)*m_sizeData;
	return lpLocalData;
}