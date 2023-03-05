/*
**		过滤字符
*/
#pragma once

#include<vector>

#define WARN_STRING			"您的发言里有不雅字眼！"
#define MARK_CHAR_STAR		'*'
#define MARK_CHAR_X			'X'

#define theChatCheck CChatCheck::getInstance()
class CChatCheck
{
public:
	static CChatCheck* getInstance()
	{
		static CChatCheck instance;
		return &instance;
	}
public:
	bool			LoadUndueString(const char* slkname);
	bool			LoadSpecialCharFilterString(const char* filename);				//特殊字符过滤
	bool			CheckStringInLow(const char* szStr);										//提醒输入不合法
	std::string		CheckStringInLowMark(char* szStr,char cMark);					//将不合法的字符转换为MARK_CHAR符号输出

    bool            CheckStringInForbit(const char* pszStr);    //禁止非法字符
	//static 因为函数通用型 属于字符串检测 位置前是否截断汉字了....
    static bool		CheckPosationInLow(const std::string& str, int nOff );		//检查所替换的位置是否会把中文切断
    static bool		CheckPosationInLow(const std::wstring& str, int nOff );		//检查所替换的位置是否会把中文切断
    
private:
	int lowbyte;
	std::vector<std::wstring> vecUndueStringList;
    std::vector<std::wstring> vecForbitStringList;
};
