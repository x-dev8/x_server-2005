/*----------------------------------------------------------
desc	: 摊位查询系统。
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
	desc	: 重置摊位信息数据。
	----------------------------------------------------------*/
	void Reset(void);

	/*----------------------------------------------------------
	desc	: 增加摊位信息。
	----------------------------------------------------------*/
	void AddStallInfo(StallDefine::SStallInfo *pInfos_, int count_);

	size_t GetStallCount(void){return m_stallInfos.size();}
	const StallDefine::SStallInfo *GetItem(size_t index_);

private:
	TStallInfos m_stallInfos;
};

/*----------------------------------------------------------
desc	: 绑定数据逻辑与UI操作。
----------------------------------------------------------*/
class CStallQueryManager: public Singleton<CStallQueryManager>
{
public:
	enum EDataStatus
	{
		E_Data_Invalid = 0,	//无效数据。原则上只有重新查询才能设置成这种状态。
		E_Data_Uncompleted,	//正在接收中，还不完整。原则上只有接收数据的过程才能设置成这种状态。
		E_Data_Completed,	//数据完整。原则上只有接收数据的过程才能设置成这种状态。
		E_Data_TimeOut,	//超时。原则上只有超时才能设置成这种状态。
	};

	enum EQueryStatus
	{
		E_Query_Status_Succeed = 0,
		E_Query_Status_KeyTooLong,	//搜索的关键字过长
		E_Query_Status_KeyFieldInvalid,	//搜索的关键字段非法
		E_Query_Status_KeyInvalid,	//搜索的关键字无效
	};

public:
	CStallQueryManager();
	~CStallQueryManager();

	/*----------------------------------------------------------
	desc	: 摊位查询系统的数据逻辑部分。
	----------------------------------------------------------*/
	EQueryStatus QueryStall(uint8 fieldType_, char *buf_ = NULL, UINT size_ = 0);

	/*----------------------------------------------------------
	desc	: 增加摊位信息。
			  要考虑丢包情况，如果最后一个包没有收到，应该考虑机制来处理这种情况下UI界面的变化。
	In		: bLastMsg_, true, 最后一个信息包；false, 应该还有后续信息包。
	----------------------------------------------------------*/
	void AddStallInfo(StallDefine::SStallInfo *pInfos_, int count_, bool bLastMsg_);

	void MoveToStall(size_t index_);

	void Reset(void);

	void SetDataStatus(EDataStatus status_){m_dataStatus = status_;}
	EDataStatus GetDataStatus(void){return m_dataStatus;}

private:


private:
	CStallQuerySystem m_data;
	EDataStatus m_dataStatus;	//标志接收数据是否完毕。
};
