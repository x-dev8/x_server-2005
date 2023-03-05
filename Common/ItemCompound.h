#pragma once

#include <windows.h>
#include <vector>
#include "Array.h"
class CItemCompound
{
public:
	enum
	{
		eMaxCompoundRes = 3
	};
	struct Resource
	{
		short	stId;
		int		nCount;
		Resource()
		{
			stId = -1;
			nCount = 0;
		}
	};
	struct Record
	{
		short	stId;			// 合成道具id
		int		nSuccRate;		// 成功率
		DWORD	dwCostMoney;	// 消耗金钱
		int		nNeedResCount;	// 需要资源种类数量
		//Resource res[eMaxCompoundRes];
		Array<Resource, eMaxCompoundRes>	res;//zizi add
		Record() : res("[ItemCompound.h]Record.res")
		{
			stId = -1;
			nSuccRate = 100;
			dwCostMoney = 0;
			nNeedResCount = 0;
		}
	};
public:
	CItemCompound(void);
	~CItemCompound(void);

	BOOL	LoadFromSlk( const char* pszFilename );
	Record* GetRecordById( short stId );

	short	MakeFromRes( std::vector<Resource>* pvectorRes );
protected:
	std::vector<Record> m_vectorRecord;
};
extern CItemCompound g_itemCompound;