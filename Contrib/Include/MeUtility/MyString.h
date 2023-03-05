#ifndef __COMMON_MYSTRING_H__
#define __COMMON_MYSTRING_H__

#pragma once

#include "MeRTLibs.h"

class CMyString
{
public:
	char* m_pString;

	CMyString(char*p)
	{
		m_pString = p;
	}

	bool operator<(const CMyString& str)const
	{
		return strcmp(m_pString,str.m_pString)<0;
	}
};

#endif // __COMMON_MYSTRING_H__
