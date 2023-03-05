#pragma once
#include "Me3d/Me3d.h"
#include <commctrl.h>

#include "mapstrtoid.h"
//#include "ioxml/IOXMLObject.h"
#include <iostream>
using namespace std;
#include "Singleton.h"

class CBowStringBindingList  : public MeCommonAllocObj<CBowStringBindingList>
{
public:
	bool IsNeedBinding(int nFrame);
	void AddBindingInterval(int start, int end);
protected:
	vector<int> m_beginList;
	vector<int> m_endList;
private:
};

class CBowStringBindingMgr : public Singleton<CBowStringBindingMgr>
{
public:
	bool IsNeedBinding(int nModelId,int nFrame);
	bool IsExist(int nModelId);
	void LoadBindingListFromFile(int nModelId,const char* pBindingListFile);
	~CBowStringBindingMgr();
protected:

	map<int,CBowStringBindingList*>			m_BindingListMap;
};

