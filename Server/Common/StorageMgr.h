/********************************************************************
    Filename:    StorageMgr.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#pragma once
/*urpose:
�ֿ��Ǵ�����ҵ��ߵĳ���
1	ÿ��������ÿ�����еĲֿ�
2	ÿ�����еĲֿⲻ�ܻ�ͨ
3	������Ϸ����һ��ӵ��30���ֿ�
4	ÿ���ֿ�������ӵ��10������
5	ÿ�������������ۼӴ��99����Ʒ
6	ÿ���ֿ��п�������
7	��ҿ��Զ���Ʒ����������
8	ÿ���ڲֿ��ŵ���Ʒ,���ж�����ʹ������
9	ӵ�ж����������Ʒ����,����,���������뾭������ȷ��
10	��������������Լ��趨
11	���ʹ�ö���������ܶ���Ʒ��������
12	�ֿ��ʼӵ��5������,���ӵ��10������
13	���Ի�Ǯ�����µĸ���
14	ÿ��������Ҫ����1��Ϸ��*(N+1), N=����Ǯ������
*/
#include "MeRTLibsServer.h"

class CStorageMgr
{
public:
	CStorageMgr(void);
	~CStorageMgr(void);
public:
	int GetCityInfo(int nStorageNpcId);
	const char* GetNpcName(int nStorageNpcId);
public:
	int nNpcID;
};

CStorageMgr* GetStorageMgr();
