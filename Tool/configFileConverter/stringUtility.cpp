#include "stdafx.h"
#include <WTypes.h>
#include "stringUtility.h"

//转换成ansi编码
std::string ToAnsi(const TString &src_)
{
#ifdef _UNICODE
	int iLength = WideCharToMultiByte(CP_ACP, 0, src_.c_str(), -1, NULL, 0, NULL, NULL);
	char *dest = new char[iLength+1];
	WideCharToMultiByte(CP_ACP, 0, src_.c_str(), -1, dest, iLength, NULL , NULL);
	std::string ret(dest);
	delete [] dest;
	return ret;
#else
	return src_;
#endif
}

//去除头尾的字符c
void TrimString(TString &src_, TCHAR c/* = _T(' ')*/)
{
	int count = 0;
	for(TString::iterator it= src_.begin(); it != src_.end(); ++it)
	{
		if(*it != c)
			break;

		++count;
	}

	src_.erase(0, count);

	if(src_.empty())
		return;

	int index = (int)src_.length() - 1;
	count = 0;
	while(index >= 0)
	{
		if(src_.at(index) != c)
			break;

		--index;
		++count;
	}

	src_.erase(index, count);
}