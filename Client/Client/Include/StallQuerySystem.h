/*----------------------------------------------------------
desc	: ̯λ��ѯϵͳ��
author	: zilong
version	: 1.0
date	: 2011-02-28
revision:
----------------------------------------------------------*/

#pragma once

#include "Singleton.h"
#include "StallDefine.h"
#include "StallMessage.h"

#include <vector>

class CStallQuerySystem
{
public:
	typedef std::vector<StallDefine::SStallInfo> TStallInfos;

public:
	CStallQuerySystem(void);
	~CStallQuerySystem(void);

	/*----------------------------------------------------------
	desc	: ����̯λ��Ϣ���ݡ�
	----------------------------------------------------------*/
	void Reset(void);

	/*----------------------------------------------------------
	desc	: ����̯λ��Ϣ��
	----------------------------------------------------------*/
	void AddStallInfo(StallDefine::SStallInfo *pInfos_, int count_);

	size_t GetStallCount(void){return m_stallInfos.size();}
	const StallDefine::SStallInfo *GetItem(size_t index_);

private:
	TStallInfos m_stallInfos;
};

/*----------------------------------------------------------
desc	: �������߼���UI������
----------------------------------------------------------*/
class CStallQueryManager: public Singleton<CStallQueryManager>
{
public:
	enum EDataStatus
	{
		E_Data_Invalid = 0,	//��Ч���ݡ�ԭ����ֻ�����²�ѯ�������ó�����״̬��
		E_Data_Uncompleted,	//���ڽ����У�����������ԭ����ֻ�н������ݵĹ��̲������ó�����״̬��
		E_Data_Completed,	//����������ԭ����ֻ�н������ݵĹ��̲������ó�����״̬��
		E_Data_TimeOut,	//��ʱ��ԭ����ֻ�г�ʱ�������ó�����״̬��
	};

	enum EQueryStatus
	{
		E_Query_Status_Succeed = 0,
		E_Query_Status_KeyTooLong,	//�����Ĺؼ��ֹ���
		E_Query_Status_KeyFieldInvalid,	//�����Ĺؼ��ֶηǷ�
		E_Query_Status_KeyInvalid,	//�����Ĺؼ�����Ч
	};

public:
	CStallQueryManager();
	~CStallQueryManager();

	/*----------------------------------------------------------
	desc	: ̯λ��ѯϵͳ�������߼����֡�
	----------------------------------------------------------*/
	EQueryStatus QueryStall(uint8 fieldType_, char *buf_ = NULL, UINT size_ = 0);

	/*----------------------------------------------------------
	desc	: ����̯λ��Ϣ��
			  Ҫ���Ƕ��������������һ����û���յ���Ӧ�ÿ��ǻ������������������UI����ı仯��
	In		: bLastMsg_, true, ���һ����Ϣ����false, Ӧ�û��к�����Ϣ����
	----------------------------------------------------------*/
	void AddStallInfo(StallDefine::SStallInfo *pInfos_, int count_, bool bLastMsg_);

	void MoveToStall(size_t index_);

	void Reset(void);

	void SetDataStatus(EDataStatus status_){m_dataStatus = status_;}
	EDataStatus GetDataStatus(void){return m_dataStatus;}

private:


private:
	CStallQuerySystem m_data;
	EDataStatus m_dataStatus;	//��־���������Ƿ���ϡ�
};
