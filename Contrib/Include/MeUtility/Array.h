/********************************************************************
    Filename:    Array.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __UTILITY_ARRAY_H__
#define __UTILITY_ARRAY_H__

#include <fstream>
#include <assert.h>
#include <Windows.h>

//-- Ŀ�� : array �±�Խ��Ļ�ȡ���� ��ӡerror��Ϣ

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
	//�±곬�� ��ӡerror ȡ�����ֵ
	inline value_type& operator[]( size_t nIndex )
	{
		if( nIndex >= LENGTH )
		{
			//��ӡ������Ϣ----------------------------

			std::ofstream fErr("err.log", std::ios::app);
			if(fErr.is_open() && _Name )
			{
				std::string szError("Error:�±����Խ��.");
				szError += _Name;
				fErr << szError <<std::endl;
				fErr.close();
#ifndef _DEBUG
				throw "Error:�±����Խ��";
#endif
			}//---------------------------------------

			assert( false && "Error:�±����Խ��." );

			return _Data[LENGTH - 1];
		}
		return _Data[nIndex];
	}

	inline const value_type& operator[]( size_t nIndex ) const
	{
		if( nIndex >= LENGTH )
		{
			//��ӡ������Ϣ----------------------------

			std::ofstream fErr("err.log", std::ios::app);
			if(fErr.is_open())
			{
				std::string szError("Error:�±����Խ��.");
				szError += _Name;
				fErr << szError <<std::endl;
				fErr.close();
#ifndef _DEBUG
				throw "Error:�±����Խ��";
#endif
			}//---------------------------------------

			assert( false && "Error:�±����Խ��." );
			
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
	value_type _Data[LENGTH];	//����
	const char*	_Name;			//ʵ������
};

#endif // __UTILITY_ARRAY_H__
