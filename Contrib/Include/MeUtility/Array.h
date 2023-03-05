/********************************************************************
    Filename:    Array.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __UTILITY_ARRAY_H__
#define __UTILITY_ARRAY_H__

#include <fstream>
#include <assert.h>
#include <Windows.h>

//-- 目的 : array 下标越界的话取最大的 打印error消息

template< class _T, size_t _length>
class Array
{
public:
	typedef _T value_type;
	enum { LENGTH = _length };

	Array()
	{
		Clear();
	}
	Array(const char* name) : _Name(name)
	{
		Clear();
	}
	~Array()
	{

	}
	//下标超过 打印error 取最大数值
	inline value_type& operator[]( size_t nIndex )
	{
		if( nIndex >= LENGTH )
		{
			//打印错误消息----------------------------

			std::ofstream fErr("err.log", std::ios::app);
			if(fErr.is_open() && _Name )
			{
				std::string szError("Error:下标访问越界.");
				szError += _Name;
				fErr << szError <<std::endl;
				fErr.close();
#ifndef _DEBUG
				throw "Error:下标访问越界";
#endif
			}//---------------------------------------

			assert( false && "Error:下标访问越界." );

			return _Data[LENGTH - 1];
		}
		return _Data[nIndex];
	}

	inline const value_type& operator[]( size_t nIndex ) const
	{
		if( nIndex >= LENGTH )
		{
			//打印错误消息----------------------------

			std::ofstream fErr("err.log", std::ios::app);
			if(fErr.is_open())
			{
				std::string szError("Error:下标访问越界.");
				szError += _Name;
				fErr << szError <<std::endl;
				fErr.close();
#ifndef _DEBUG
				throw "Error:下标访问越界";
#endif
			}//---------------------------------------

			assert( false && "Error:下标访问越界." );
			
			return _Data[LENGTH - 1];
		}
		return _Data[nIndex];
	}
	inline void Clear()
	{
		ZeroMemory(_Data, sizeof(_Data));
	}

public:
	__inline unsigned int GetSize() {return LENGTH;}

protected:
	value_type _Data[LENGTH];	//数据
	const char*	_Name;			//实例名字
};

#endif // __UTILITY_ARRAY_H__
