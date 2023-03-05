#pragma once
#include <string>
#include <map>
// #include "Tinyxml\tinyxml.h"
#include "MeRTLibs.h"
#include "core/Name.h"

#pragma warning( push, 0 )
#pragma warning( disable : 4239)

#define String_Ext ".string"
#define Encrypt_String_Ext ".stringc"
#define Bin_String_Ext ".stringb"

#define Empty_String_Id -1
#define Empty_String_Value ""

#define STRING_DATA_ID				"M.E.S.T"	// 字符串文件二进制数据格式标识
#define STRING_DATA_VERSION			10000		// 字符串文件二进制数据版本，初始版本号10000，每次调整版本号递增1
#define STRING_DATA_BASE_VERSION	10000		// 字符串文件初始版本号


#define theXmlString XmlString::Instance()

class XmlString
{
public:
	XmlString();
	~XmlString();

	bool LoadStringPath(const char* pszPath, bool bClear = false, bool bEncrypt = false, bool bReplace = false, bool bWarning = true);  //载入文件夹中所有的string文件

	//pszPath = 文件夹路径  pszFile  = FileList索引文件完整路径  里面存放的都是相对于pszFile的文件路径
	bool LoadStringFileList(const char* pszFile, bool bClear = false, bool bReplace = false, bool bWarning = true);  //载入list中所有文件

	//加载String文件 ,是否清空, 相同是否覆盖
	bool LoadStringFile(const char* pszFile, bool bClear = false, bool bReplace = false, bool bWarning = true); 

	//加载二进制stringb文件
	bool LoadBinStringFile(const char* pszFile, bool bClear = false, bool bReplace = false, bool bWarning = true, bool bInsertEmpty = true);

	// 保存成二进制stringb文件
	bool SaveBinStringFile(const char* pszFile);

	//保存文件
	bool SaveStringFile(const char* pszFile, std::vector<int> &vecStringId = std::vector<int>() , bool bSaveEmpty = true);

	const char* GetString(const int nId);
	int GetId(std::string strName);

	int AddString(std::string strName);	//添加，返回该字串索引
	int AddString(int nId, std::string strName, bool Replace = false);

	bool DeleteString(const int nId);

	void ClearString() { m_mapString.clear(); }

    const char* GetStringWithName( int nIndex );
    const char* GetStringWithAccountID( int nIndex );
    const char* GetStringWithAccountIDAndName( int nIndex );

	inline static XmlString& Instance()
	{
		static XmlString s_StringLanguage;

		return s_StringLanguage;
	}

    bool SaveBinFile( const char* pszFileName );

    bool LoadBinFile( const char* pszFileName );

	char*	ParseAtString(const char * szText );

private:
    typedef std::multimap<int, std::string>::iterator mapiter;
    std::multimap<int,std::string> m_mapString;
    std::string strWithNameFormat_;
};

#pragma warning( pop )
