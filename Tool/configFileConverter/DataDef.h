/*------------------------------------------------------------------------
Desc		: 通用数据类型定义。
Author		: zilong
Version		: 1.0
Date		: 2011-03-08
Revision	:
-------------------------------------------------------------------------*/

#pragma once

#include <string>

#ifdef _UNICODE
typedef std::wstring TString;
#else
typedef std::string TString;
#endif