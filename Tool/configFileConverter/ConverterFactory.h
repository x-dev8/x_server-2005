/*------------------------------------------------------------------------
Desc		: factory模式模板类。
Author		: zilong
Version		: 1.0
Date		: 2011-03-08
Revision	:
-------------------------------------------------------------------------*/

#pragma once

#include <map>

#include "DataDef.h"
#include "SingletonBase.h"

template<class T>
class CObjectFactory: public CSingletonBase<CObjectFactory<T> >
{
public:
	CObjectFactory(void);
	~CObjectFactory(void);

public:
	typedef T *(*TCreateFun)();
	typedef TString TItemID;

public:
	T *CreateObject(TItemID id_);

	bool Register(TItemID id_, TCreateFun fun_);
	bool UnRegister(TItemID id_);

private:
	typedef std::map<TItemID, TCreateFun> TCreateMethods;
private:
	TCreateMethods m_methods;
};

template<class T>
CObjectFactory<T>::CObjectFactory(void)
{
}

template<class T>
CObjectFactory<T>::~CObjectFactory(void)
{
}

template<class T>
T *CObjectFactory<T>::CreateObject(TItemID id_)
{
	TCreateMethods::const_iterator it = m_methods.find(id_);
	if(it != m_methods.end())
	{
		return (it->second)();
	}

	return NULL;
}

template<class T>
bool CObjectFactory<T>::Register(TItemID id_, TCreateFun fun_)
{
	return m_methods.insert(TCreateMethods::value_type(id_, fun_)).second;
}

template<class T>
bool CObjectFactory<T>::UnRegister(TItemID id_)
{
	TCreateMethods::iterator it = m_methods.find(id_);
	if(it != m_methods.end())
	{
		m_methods.erase(it);
		return true;
	}

	return false;
}
