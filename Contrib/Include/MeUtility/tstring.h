/********************************************************************
	Filename: 	TString.h
	MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

/*
Revision History:
    ����UTF-8����֧�ֹ���

    ȥ�����к�����Virtual������ʹ֮�������̳�
    �޸�format��������Ӻ��Դ�Сд�ȽϺ�������Сдת������
    ��Ӽ����귽��CHAR��STRING��ת��
    ȥ��UTF8ת�������е��߳�����       
    ���Replace����                    
    ���Right,Left,Mid,Find,ReverseFind
    ���Base64ת��                     
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
    //ʵ��sprintf����
    void Format(const char* pszFormat, ...);
    void Format(const wchar_t* pwszFormat, ...);


//������ʽƥ�书��:
//public:
//
//    //ƥ��: strPatternΪ�����ִ�, strResultΪƥ��ɹ����ִ�
//    virtual bool match(const _tstring& strPattern, _tstring& strResult);
//
//    //ƥ��: ����Ҫ����ֵֻ����Ƿ�ƥ��ɹ�
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
    //����=�ź���
    _tstring& operator = (char ch);
    _tstring& operator = (wchar_t ch);
    _tstring& operator = (const char* pStr);
    _tstring& operator = (const wchar_t* pwStr);
    _tstring& operator = (const _tstring& Str);
    _tstring& operator = (const std::string& Str);
    _tstring& operator = (const std::wstring& Str);

public:
    //���캯��
    _tstring(wchar_t ch);
    _tstring(char ch);
    _tstring(const char* pStr);
    _tstring(const wchar_t* pwStr);
    _tstring(const _tstring& str);
    _tstring(const std::string& str);
    _tstring(const std::wstring& str);

public:

    //ANSI C����UNICODE��ת������
    static std::wstring toWideString(const char* pStr);
    static std::string toNarrowString(const wchar_t* pwStr);

    //UTF-8��UNICODE��ת������
    static std::string wcstoUTF8(const wchar_t* pwStr);
    static std::wstring UTF8towcs(const char* pStr);

    static std::string cstobase64(const char* pStr, size_t nLength);
    static std::string base64tocs(const char* pStr);
	/*
	* ��trimΪ�棬�򲻱����ָ��Ŀմ�(ע�ⲻ�ǿհ��ַ�)�����磺 
	* Tokenize( "a,bc;,d,", ",;", &out_list, TRUE) 
	* �᷵��3������a��bc��d�� 
	* ��trimΪFALSE������nullSubst��������ָ��Ŀմ������磺 
	*  Tokenize( "a,bc;,d;", ",;", &out_list, FALSE,"[null]" ) 
	* �᷵��5������a��bc��[null]��d��[null]�� 
	* trimĬ��ΪFALSE��nullSubstĬ��Ϊ�մ��� 
	**/
	static std::vector<std::string> tokenize(const std::string& src, std::string tok, bool trim=false, std::string null_subst="");
	//ʹ��һ�������Ĵ�delimit�����������е�ĳ���ַ������ָ�src��,û��trimѡ����ϸ�ָ
	static std::vector<std::string> split(const std::string& src, std::string delimit, std::string null_subst="");
};

};

#endif // __UTILITY_TSTRING_H__
