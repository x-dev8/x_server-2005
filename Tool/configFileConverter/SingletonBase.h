/*------------------------------------------------------------------------
Desc		: singleton模式基类。
Author		: zilong
Version		: 1.0
Date		: 2010-09-02
Revision	:
-------------------------------------------------------------------------*/

#pragma once

template<class T>
class CSingletonBase
{
public:
	static T &GetInstance(void)
	{
		static T instance;
		return instance;
	}

protected:
	CSingletonBase()
	{

	}

	~CSingletonBase()
	{

	}
};