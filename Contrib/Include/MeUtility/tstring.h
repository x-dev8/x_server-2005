/********************************************************************
	Filename: 	TString.h
	MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

/*
Revision History:
    增加UTF-8编码支持功能

    去除所有函数的Virtual声明，使之不允许被继承
    修改format函数，添加忽略大小写比较函数，大小写转换函数
    添加几个宏方便CHAR与STRING的转换
    去除UTF8转换函数中的线程锁定       
    添加Replace函数                    
    添加Right,Left,Mid,Find,ReverseFind
    添加Base64转换                     
--*/

#ifndef __UTILITY_TSTRING_H__
#define __UTILITY_TSTRING_H__

#include "MeRTLibs.h"

namespace Common
{
#define _tANSICHAR(x)       Common::_tstring(x).toNarrowString().c_str()
#define _tUNICODECHAR(x)    Common::_tstring(x).toWideString().c_str()
#define _tUTF8CHAR(x)       Common::_tstring(x).toUTF8().c_str()

#define _tstringA(x)        Common::_tstring(x).toNarrowString()
#define _tstringW(x)        Common::_tstring(x).toWideString()

#define _tUTF8TOMBYTE(x)    Common::_tstring().fromUTF8(x)

class _tstring
#ifdef _UNICODE
    : public std::wstring
#else
    : public std::string
#endif
{
public:
    _tstring();
    ~_tstring();

public:
    void fromUTF8(const char* pszUTF8);
    std::string toUTF8();

    void fromBASE64(const char* pszBASE64);
    std::string toBASE64();

    std::string toNarrowString();
    std::wstring toWideString();
	
public:
    _tstring& MakeLower();
    _tstring& MakeUpper();

    int CompareNoCase(_tstring str);

    unsigned int Replace(_tstring strOld, _tstring strNew);
    unsigned int Replace(wchar_t chOld, wchar_t chNew);
    unsigned int Replace(char chOld, char chNew);

    _tstring Right(size_t nCount);
    _tstring Left(size_t nCount);
    _tstring Mid(size_t iFirst, size_t nCount);

    size_t Find(const TCHAR ch, unsigned int nStart = 0);
    size_t Find(const TCHAR* pszch, unsigned int nStart = 0);
    size_t ReverseFind(const TCHAR ch);

public:
    //实现sprintf功能
    void Format(const char* pszFormat, ...);
    void Format(const wchar_t* pwszFormat, ...);


//正则表达式匹配功能:
//public:
//
//    //匹配: strPattern为规则字串, strResult为匹配成功的字串
//    virtual bool match(const _tstring& strPattern, _tstring& strResult);
//
//    //匹配: 不需要返回值只获得是否匹配成功
//    virtual bool match(const _tstring& strPattern);
//
//
//    virtual bool match(const char* pStr, _tstring& strResult);
//    virtual bool match(const wchar_t* pwStr, _tstring& strResult);
//    virtual bool match(const std::string& str, _tstring& strResult);
//    virtual bool match(const std::wstring& str, _tstring& strResult);
//
//    virtual bool match(const char* pStr);
//    virtual bool match(const wchar_t* pwStr);
//    virtual bool match(const std::string& str);
//    virtual bool match(const std::wstring& str);

public:

#ifdef _UNICODE
    using std::wstring::operator =;
#else
    using std::string::operator =;
#endif
    //重载=号函数
    _tstring& operator = (char ch);
    _tstring& operator = (wchar_t ch);
    _tstring& operator = (const char* pStr);
    _tstring& operator = (const wchar_t* pwStr);
    _tstring& operator = (const _tstring& Str);
    _tstring& operator = (const std::string& Str);
    _tstring& operator = (const std::wstring& Str);

public:
    //构造函数
    _tstring(wchar_t ch);
    _tstring(char ch);
    _tstring(const char* pStr);
    _tstring(const wchar_t* pwStr);
    _tstring(const _tstring& str);
    _tstring(const std::string& str);
    _tstring(const std::wstring& str);

public:

    //ANSI C串与UNICODE串转换功能
    static std::wstring toWideString(const char* pStr);
    static std::string toNarrowString(const wchar_t* pwStr);

    //UTF-8与UNICODE串转换功能
    static std::string wcstoUTF8(const wchar_t* pwStr);
    static std::wstring UTF8towcs(const char* pStr);

    static std::string cstobase64(const char* pStr, size_t nLength);
    static std::string base64tocs(const char* pStr);
	/*
	* 若trim为真，则不保留分割后的空串(注意不是空白字符)。比如： 
	* Tokenize( "a,bc;,d,", ",;", &out_list, TRUE) 
	* 会返回3个串：a、bc、d。 
	* 若trim为FALSE，则用nullSubst用来替代分割后的空串，比如： 
	*  Tokenize( "a,bc;,d;", ",;", &out_list, FALSE,"[null]" ) 
	* 会返回5个串：a、bc、[null]、d、[null]。 
	* trim默认为FALSE，nullSubst默认为空串。 
	**/
	static std::vector<std::string> tokenize(const std::string& src, std::string tok, bool trim=false, std::string null_subst="");
	//使用一个完整的串delimit（而不是其中的某个字符）来分割src串,没有trim选项，即严格分割。
	static std::vector<std::string> split(const std::string& src, std::string delimit, std::string null_subst="");
};

};

#endif // __UTILITY_TSTRING_H__
